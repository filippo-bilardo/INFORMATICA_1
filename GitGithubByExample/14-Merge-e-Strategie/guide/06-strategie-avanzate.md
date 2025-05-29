# Strategie di Merge Avanzate

## 📖 Introduzione

Le strategie di merge avanzate vanno oltre i concetti base per affrontare scenari complessi in progetti di grandi dimensioni, team distribuiti e workflow sofisticati. Questa guida esplora tecniche avanzate per ottimizzare la collaborazione e mantenere la qualità del codice.

## 🎯 Obiettivi

- Comprendere strategie di merge per progetti enterprise
- Implementare workflow di integrazione continua
- Gestire merge automation e policy
- Utilizzare strategie per team distribuiti
- Ottimizzare performance e qualità

## 🏗️ Architetture di Branch e Merge

### Git Flow Avanzato

```bash
# Configurazione Git Flow con strategie personalizzate
git flow init

# Branch di sviluppo con merge strategy specifica
git config branch.develop.mergeoptions "--no-ff"
git config branch.main.mergeoptions "--ff-only"

# Creazione feature con strategia predefinita
git flow feature start advanced-auth
# Sviluppo...
git flow feature finish advanced-auth --squash
```

### GitHub Flow con Merge Queues

```bash
# Configurazione per merge queues
# .github/merge_queue.yml
cat > .github/merge_queue.yml << 'EOF'
merge_method: merge
merge_commit_title: "auto"
merge_commit_message: "pr_body"
required_checks:
  - "tests"
  - "lint"
  - "security-scan"
batch_size: 3
merge_timeout: 30
EOF
```

## 🔄 Strategie per Team Distribuiti

### Merge Remoto con Conflitti

```bash
# Strategia per merge distribuiti
git config merge.tool vimdiff

# Merge con strategia remota personalizzata
git merge --strategy=recursive --strategy-option=theirs origin/feature
git merge --strategy=octopus HEAD~2 HEAD~1  # Merge multipli

# Merge con custom driver per file specifici
echo "*.config merge=ours" >> .gitattributes
git config merge.ours.driver true
```

### Workflow con Multiple Repositories

```bash
# Subtree merge per dependencies
git remote add library https://github.com/team/shared-library.git
git fetch library
git merge --allow-unrelated-histories library/main

# Submodule con merge automatico
git submodule add https://github.com/team/ui-components.git components
git config submodule.components.update merge
```

## 🤖 Automation e CI/CD Integration

### Merge Automation Scripts

```bash
#!/bin/bash
# auto-merge.sh - Script di merge automatico
set -e

BRANCH=$1
TARGET=${2:-main}

# Verifiche pre-merge
echo "🔍 Running pre-merge checks..."
npm test
npm run lint
npm run security-audit

# Merge condizionale
if git merge-base --is-ancestor $BRANCH $TARGET; then
    echo "✅ Fast-forward merge possible"
    git checkout $TARGET
    git merge --ff-only $BRANCH
else
    echo "🔀 Three-way merge required"
    git checkout $TARGET
    git merge --no-ff $BRANCH -m "Merge $BRANCH into $TARGET"
fi

# Post-merge actions
echo "🚀 Running post-merge hooks..."
npm run build
git tag "auto-merge-$(date +%Y%m%d-%H%M%S)"
```

### GitHub Actions per Merge Strategy

```yaml
# .github/workflows/smart-merge.yml
name: Smart Merge Strategy
on:
  pull_request:
    types: [labeled]

jobs:
  auto-merge:
    if: contains(github.event.label.name, 'auto-merge')
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0
      
      - name: Determine merge strategy
        id: strategy
        run: |
          if git merge-base --is-ancestor ${{ github.head_ref }} main; then
            echo "strategy=fast-forward" >> $GITHUB_OUTPUT
          else
            echo "strategy=three-way" >> $GITHUB_OUTPUT
          fi
      
      - name: Auto merge
        uses: pascalgn/merge-action@v0.15.6
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          merge_method: ${{ steps.strategy.outputs.strategy == 'fast-forward' && 'merge' || 'squash' }}
```

## 📊 Merge Policy e Governance

### Branch Protection Rules Avanzate

```bash
# Configurazione via GitHub CLI
gh api repos/:owner/:repo/branches/main/protection \
  --method PUT \
  --field required_status_checks='{"strict":true,"contexts":["tests","lint"]}' \
  --field enforce_admins=true \
  --field required_pull_request_reviews='{"required_approving_review_count":2}' \
  --field restrictions='{"users":[],"teams":["maintainers"]}'
```

### Custom Merge Hooks

```bash
#!/bin/bash
# .git/hooks/pre-merge-commit
# Validazione pre-merge personalizzata

echo "🔍 Validating merge commit..."

# Verifica dimensione del merge
CHANGED_FILES=$(git diff --cached --name-only | wc -l)
if [ $CHANGED_FILES -gt 50 ]; then
    echo "❌ Merge troppo grande ($CHANGED_FILES files). Considera lo split."
    exit 1
fi

# Verifica presenza di conflitti risolti
if git diff --cached | grep -q "^<<<<<<<\|^=======\|^>>>>>>>"; then
    echo "❌ Conflitti non risolti trovati!"
    exit 1
fi

# Verifica commit message
COMMIT_MSG=$(cat $1)
if ! echo "$COMMIT_MSG" | grep -q "^Merge\|^feat\|^fix\|^docs"; then
    echo "❌ Commit message non conforme agli standard"
    exit 1
fi

echo "✅ Merge validation passed"
```

## 🎛️ Strategie per Scenari Specifici

### Large Binary Files

```bash
# Configurazione Git LFS con merge strategy
git lfs install
echo "*.zip filter=lfs diff=lfs merge=lfs" >> .gitattributes
echo "*.pdf filter=lfs diff=lfs merge=lfs" >> .gitattributes

# Merge con handling speciale per LFS
git config merge.lfs.driver 'git lfs merge-driver --ancestor %O --current %A --other %B --marker-size %L --output %A'
```

### Database Migrations

```bash
# Custom merge driver per migrations
echo "db/migrate/*.sql merge=migrate-driver" >> .gitattributes

# Script per merge di migrations
cat > .git/migrate-merge.sh << 'EOF'
#!/bin/bash
# Merge automatico per file di migrazione
ANCESTOR=$1
CURRENT=$2
OTHER=$3
OUTPUT=$4

# Combina migrations ordinandole per timestamp
cat $CURRENT $OTHER | sort | uniq > $OUTPUT
EOF

git config merge.migrate-driver.driver '.git/migrate-merge.sh %O %A %B %A'
```

### Monorepo Strategies

```bash
# Merge selettivo per monorepo
git config merge.ours.driver true

# Merge solo di directory specifiche
echo "frontend/* merge=frontend-strategy" >> .gitattributes
echo "backend/* merge=backend-strategy" >> .gitattributes

# Script per merge condizionale
#!/bin/bash
# conditional-merge.sh
COMPONENT=$1
BRANCH=$2

if [[ $COMPONENT == "frontend" ]]; then
    git merge $BRANCH --strategy-option=subtree=frontend/
elif [[ $COMPONENT == "backend" ]]; then
    git merge $BRANCH --strategy-option=subtree=backend/
fi
```

## 📈 Performance e Ottimizzazione

### Merge Performance Tuning

```bash
# Configurazioni per repository grandi
git config merge.renameLimit 10000
git config diff.renames true
git config core.preloadindex true
git config core.fscache true

# Merge con parallelizzazione
git config merge.tool meld
git config mergetool.meld.cmd 'meld --auto-merge "$LOCAL" "$BASE" "$REMOTE" --output "$MERGED"'

# Cache per merge ripetuti
git config rerere.enabled true
git config rerere.autoupdate true
```

### Merge Analytics

```bash
#!/bin/bash
# merge-analytics.sh - Analisi delle performance di merge
echo "📊 Merge Analytics Report"
echo "========================="

# Merge più frequenti
echo "🔄 Most frequent merge patterns:"
git log --oneline --merges --since="1 month ago" | \
  grep -o "Merge.*into.*" | sort | uniq -c | sort -nr | head -5

# Dimensione media dei merge
echo -e "\n📏 Average merge size:"
git log --merges --since="1 month ago" --format="%H" | \
while read commit; do
    git diff --stat $commit^1..$commit | tail -1
done | awk '{sum+=$4} END {print "Average:", sum/NR, "lines changed"}'

# Conflitti più comuni
echo -e "\n⚠️  Most conflict-prone files:"
git log --grep="Merge conflict" --since="1 month ago" --format="%b" | \
  grep -o "CONFLICT.*in.*" | sed 's/CONFLICT.*in //' | \
  sort | uniq -c | sort -nr | head -5
```

## 🔧 Troubleshooting Avanzato

### Recovery da Merge Complessi

```bash
# Backup prima di merge rischiosi
git tag backup-before-merge-$(date +%Y%m%d-%H%M%S)

# Merge con recovery point
git merge feature-branch || {
    echo "❌ Merge failed, creating recovery point"
    git merge --abort
    git stash push -m "failed merge attempt"
    exit 1
}

# Analisi post-merge
git log --graph --oneline -10
git diff HEAD~1..HEAD --stat
```

### Debug Merge Issues

```bash
# Verbose merge per debugging
GIT_MERGE_VERBOSITY=2 git merge feature-branch

# Tracciamento dettagliato
git config merge.log true
git config merge.summary true

# Merge con debug completo
git -c merge.verbosity=5 merge --no-commit feature-branch
git status
git diff --cached
```

## 🎯 Best Practices Avanzate

### 1. Merge Strategy Selection Matrix

| Scenario | Strategia | Comando | Quando Usare |
|----------|-----------|---------|--------------|
| Feature completa | Squash | `git merge --squash` | Storia lineare |
| Hotfix critico | Fast-forward | `git merge --ff-only` | Patch rapide |
| Release branch | No-FF | `git merge --no-ff` | Tracciabilità |
| Experimental | Octopus | `git merge A B C` | Test multipli |

### 2. Automation Checklist

```bash
# Pre-merge automation
✅ Tests automatici
✅ Lint e formatting
✅ Security scan
✅ Performance check
✅ Documentation update

# Post-merge automation
✅ Build verification
✅ Deployment staging
✅ Integration tests
✅ Notification team
✅ Metrics collection
```

### 3. Team Guidelines

```markdown
## Merge Guidelines

### Required Checks
- [ ] All tests pass
- [ ] Code review approved
- [ ] Documentation updated
- [ ] Breaking changes documented
- [ ] Performance impact assessed

### Merge Types
- **Feature**: Use squash merge
- **Bugfix**: Use merge commit
- **Hotfix**: Use fast-forward
- **Release**: Use no-ff merge
```

## 📚 Risorse e Tool

### Tool Consigliati

```bash
# Git extensions
git config --global alias.smart-merge '!f() { \
    if git merge-base --is-ancestor $1 HEAD; then \
        git merge --ff-only $1; \
    else \
        git merge --no-ff $1; \
    fi \
}; f'

# Merge visualization
git config --global alias.merge-preview '!f() { \
    git log --graph --oneline $1..HEAD; \
}; f'
```

### Integrazione con IDE

```json
// VSCode settings.json
{
  "git.enableSmartCommit": true,
  "git.smartCommitChanges": true,
  "merge-conflict.autoNavigateNextConflict.enabled": true,
  "merge-conflict.decorators.enabled": true
}
```

## 📋 Riepilogo

Le strategie di merge avanzate includono:

- **Automation**: Script e CI/CD integration
- **Policy**: Branch protection e governance
- **Performance**: Ottimizzazione per repository grandi
- **Team**: Workflow per collaborazione distribuita
- **Quality**: Validazione e controlli automatici

## 🔄 Link Correlati

- [01-Tipi Merge](./01-tipi-merge.md) - Fondamenti dei tipi di merge
- [05-Merge vs Rebase](./05-merge-vs-rebase.md) - Confronto strategie
- [Esercizi Pratici](../esercizi/README.md) - Applicazione pratica

---

**Prossimo**: [Esempi Pratici](../esempi/01-merge-workflow.md) - Implementazione di workflow avanzati
