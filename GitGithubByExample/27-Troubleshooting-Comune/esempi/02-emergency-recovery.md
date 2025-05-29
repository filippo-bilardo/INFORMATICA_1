# Emergency Recovery: Procedure di Emergenza Git

## Introduzione

Questo documento fornisce procedure step-by-step per gestire emergenze critiche con Git. Ogni sezione include scenari reali, soluzioni immediate e procedure di rollback.

## 🚨 EMERGENCY PROTOCOLS

### Protocol Alpha: Repository Completamente Corrotto

**Situazione**: Il repository non risponde più, errori di corruzione diffusi.

**Symptoms**:
```bash
git status
# fatal: not a git repository (or any of the parent directories): .git

# oppure
git log
# error: object file .git/objects/... is empty
# fatal: bad object HEAD
```

**IMMEDIATE ACTION**:

```bash
# STEP 1: Ferma tutto e valuta i danni
cd /path/to/your/project
ls -la .git/  # Verifica se .git esiste

# STEP 2: Backup immediato di tutto
cp -r . ../emergency-backup-$(date +%Y%m%d_%H%M%S)

# STEP 3: Tenta diagnosi
git fsck --full 2>&1 | tee fsck-report.txt
git reflog 2>&1 | tee reflog-report.txt

# STEP 4: Recovery from remote (se disponibile)
if [ ! -z "$(git remote -v)" ]; then
    echo "Remote trovato, inizio clonazione pulita..."
    cd ..
    git clone $(git -C emergency-backup-* remote get-url origin) recovered-repo
    
    # Copia file non versionati
    rsync -av --exclude='.git' emergency-backup-*/  recovered-repo/
    cd recovered-repo
    git status  # Verifica stato
fi
```

**RECOVERY PROCEDURE**:

```bash
# Metodo 1: Ricostruzione da oggetti
git init new-repo
cd new-repo

# Importa oggetti dal repository corrotto
cp -r ../emergency-backup-*/.git/objects/* .git/objects/

# Tenta di ricostruire riferimenti
git fsck --full --unreachable > unreachable-objects.txt

# Trova il commit HEAD più recente
grep "commit" unreachable-objects.txt | head -5
# unreachable commit abc123def456...

# Ricrea il branch main
git update-ref refs/heads/main abc123def456
git checkout main

# Metodo 2: Recovery selettivo
# Se hai accesso parziale agli oggetti
git cat-file -p abc123  # Testa se il commit è leggibile
git checkout -b recovery-branch abc123

# Metodo 3: Recovery da reflog backup
if [ -f ../emergency-backup-*/.git/logs/HEAD ]; then
    # Estrai hash dell'ultimo stato noto
    tail -1 ../emergency-backup-*/.git/logs/HEAD | cut -d' ' -f2
    git reset --hard <hash>
fi
```

### Protocol Beta: Lavoro Perso Completamente

**Situazione**: Hai perso giorni di lavoro con operazioni Git sbagliate.

**Symptoms**:
```bash
# Dopo operazioni come:
git reset --hard HEAD~10  # DISASTER!
git branch -D important-feature  # OOPS!
git clean -fdx  # PANIC!
```

**IMMEDIATE ACTION**:

```bash
# STEP 1: STOP! Non fare altre operazioni
# Ogni comando Git può sovrascrivere il reflog

# STEP 2: Backup del repository corrente
cp -r .git .git-emergency-$(date +%Y%m%d_%H%M%S)

# STEP 3: Analisi del reflog
git reflog --all --date=iso > full-reflog.txt
git reflog --graph --oneline --all > visual-reflog.txt

# STEP 4: Ricerca pattern nel reflog
grep -i "important\|feature\|work" full-reflog.txt
grep "commit:" full-reflog.txt | tail -20
```

**RECOVERY PROCEDURE**:

```bash
# Metodo 1: Recovery da reflog
git reflog --all --grep="your-feature-name"
# Se trovi il commit:
git checkout -b recovery-branch <commit-hash>

# Metodo 2: Recovery da oggetti scollegati
git fsck --lost-found --unreachable > lost-objects.txt

# Esamina oggetti persi
grep "commit" lost-objects.txt | while read type hash; do
    echo "=== Commit $hash ==="
    git log --oneline -1 $hash 2>/dev/null || echo "Corrotto"
    git show --stat $hash 2>/dev/null | head -10
done

# Metodo 3: Recovery temporale
# Cerca commit per data
git log --all --since="1 day ago" --until="now" --oneline
git log --all --author="Your Name" --since="1 week ago"

# Metodo 4: Recovery da stash nascosti
git stash list --date=iso
git stash show -p stash@{0}  # Esamina ogni stash
```

### Protocol Gamma: Push Force Disastroso

**Situazione**: Hai fatto `git push --force` e sovrascritto il lavoro del team.

**Symptoms**:
```bash
# Team members getting:
git pull
# + abc123..def456 main -> origin/main (forced update)

# Storia del repository completamente cambiata
```

**IMMEDIATE ACTION**:

```bash
# STEP 1: Notifica immediata al team
echo "EMERGENCY: Force push detected. Stop all work immediately!"

# STEP 2: Identifica l'hash prima del force push
git reflog origin/main
# def456 refs/remotes/origin/main@{0}: fetch: forced-update
# xyz789 refs/remotes/origin/main@{1}: fetch: fast-forward

# STEP 3: Il commit xyz789 è quello che è stato sovrascritto

# STEP 4: Recovery immediato
git push origin xyz789:main --force-with-lease
```

**TEAM COORDINATION PROCEDURE**:

```bash
# Per ogni membro del team:

# 1. Backup del lavoro locale
git stash push -m "Emergency backup before force push recovery"

# 2. Fetch del repository "fixed"
git fetch origin

# 3. Reset del branch locale
git reset --hard origin/main

# 4. Recovery del lavoro locale
git stash pop

# 5. Se ci sono conflitti dopo stash pop
git status
# Risolvi manualmente e ricommit
```

### Protocol Delta: Merge Hell Recovery

**Situazione**: Merge multipli hanno creato uno stato ingestibile del repository.

**Symptoms**:
```bash
# Storia Git completamente caotica
git log --oneline --graph -20
# * a1b2c3d Merge branch 'feature3' into 'feature2'
# |\
# | * d4e5f6g Merge branch 'feature1' into 'feature3'
# | |\
# | | * g7h8i9j Merge branch 'hotfix' into 'feature1'
# [... complete chaos ...]
```

**IMMEDIATE ACTION**:

```bash
# STEP 1: Identifica il "Good Known State"
git log --oneline --first-parent main | head -20
# Trova l'ultimo commit pulito su main

# STEP 2: Backup di tutte le branch
git for-each-ref --format='%(refname:short)' refs/heads/ | while read branch; do
    git show-ref $branch > backup-refs-$(date +%Y%m%d_%H%M%S).txt
done

# STEP 3: Crea branch di recovery
git checkout -b emergency-recovery <last-good-commit>
```

**RECOVERY PROCEDURE**:

```bash
# Metodo 1: Cherry-pick selettivo
# Identifica commit importanti da salvare
git log --oneline --all --grep="feat\|fix" --since="1 week ago"

# Cherry-pick commit specifici
git cherry-pick <important-commit-1>
git cherry-pick <important-commit-2>
# Continue for all important commits

# Metodo 2: Merge pulito con squash
git checkout emergency-recovery

# Per ogni feature branch
git merge --squash feature-branch-1
git commit -m "Merge feature-branch-1 (squashed)"

git merge --squash feature-branch-2  
git commit -m "Merge feature-branch-2 (squashed)"

# Metodo 3: Rebase interattivo massiccio
git rebase -i --root
# Usa l'editor per riorganizzare tutta la cronologia
```

## Emergency Prevention Strategies

### Pre-emptive Backup System

```bash
# Script di backup automatico
cat > git-emergency-backup.sh << 'EOF'
#!/bin/bash

BACKUP_DIR="$HOME/git-emergency-backups"
PROJECT_NAME=$(basename $(pwd))
TIMESTAMP=$(date +%Y%m%d_%H%M%S)

mkdir -p "$BACKUP_DIR/$PROJECT_NAME"

# Backup completo del .git
tar -czf "$BACKUP_DIR/$PROJECT_NAME/git-full-$TIMESTAMP.tar.gz" .git

# Backup del reflog
cp .git/logs/HEAD "$BACKUP_DIR/$PROJECT_NAME/reflog-$TIMESTAMP.txt"

# Backup delle configurazioni
git config --list > "$BACKUP_DIR/$PROJECT_NAME/config-$TIMESTAMP.txt"

# Cleanup vecchi backup (mantieni ultimi 10)
cd "$BACKUP_DIR/$PROJECT_NAME"
ls -t git-full-*.tar.gz | tail -n +11 | xargs rm -f
ls -t reflog-*.txt | tail -n +11 | xargs rm -f
ls -t config-*.txt | tail -n +11 | xargs rm -f

echo "Emergency backup created in $BACKUP_DIR/$PROJECT_NAME"
EOF

chmod +x git-emergency-backup.sh

# Aggiungi al .bashrc per backup automatico
echo 'alias git-backup="./git-emergency-backup.sh"' >> ~/.bashrc
```

### Monitoring e Early Warning

```bash
# Script di monitoraggio repository health
cat > git-health-check.sh << 'EOF'
#!/bin/bash

echo "=== Git Repository Health Check ==="
echo "Repository: $(pwd)"
echo "Date: $(date)"
echo

# Check 1: Repository integrity
echo "🔍 Checking repository integrity..."
if git fsck --quiet; then
    echo "✅ Repository integrity: OK"
else
    echo "❌ Repository integrity: ISSUES FOUND"
    git fsck
fi

# Check 2: Remote connectivity
echo "🌐 Checking remote connectivity..."
if git ls-remote origin &>/dev/null; then
    echo "✅ Remote connectivity: OK"
else
    echo "❌ Remote connectivity: FAILED"
fi

# Check 3: Uncommitted changes
echo "📝 Checking for uncommitted changes..."
if git diff-index --quiet HEAD --; then
    echo "✅ Working directory: Clean"
else
    echo "⚠️  Uncommitted changes detected"
    git status --porcelain
fi

# Check 4: Repository size
echo "💾 Repository size check..."
REPO_SIZE=$(du -sh .git | cut -f1)
echo "Repository size: $REPO_SIZE"

if [ $(du -s .git | cut -f1) -gt 1000000 ]; then  # >1GB
    echo "⚠️  Large repository detected"
fi

# Check 5: Recent activity
echo "⏰ Recent activity..."
echo "Last 5 commits:"
git log --oneline -5

echo
echo "=== Health Check Complete ==="
EOF

chmod +x git-health-check.sh
```

## Emergency Contact Procedures

### Internal Team Escalation

```bash
# Script per notificare emergenze Git al team
cat > git-emergency-notify.sh << 'EOF'
#!/bin/bash

EMERGENCY_TYPE="$1"
DESCRIPTION="$2"
REPO_NAME=$(basename $(pwd))

# Slack notification (se configurato)
if [ ! -z "$SLACK_WEBHOOK" ]; then
    curl -X POST -H 'Content-type: application/json' \
    --data "{\"text\":\"🚨 GIT EMERGENCY 🚨\nRepository: $REPO_NAME\nType: $EMERGENCY_TYPE\nDescription: $DESCRIPTION\nAction required: Stop all work until resolved\"}" \
    $SLACK_WEBHOOK
fi

# Email notification
echo "Subject: GIT EMERGENCY - $REPO_NAME
🚨 GIT EMERGENCY DETECTED 🚨

Repository: $REPO_NAME
Emergency Type: $EMERGENCY_TYPE
Description: $DESCRIPTION
Time: $(date)

IMMEDIATE ACTIONS REQUIRED:
1. Stop all work on this repository
2. Do not push any changes
3. Contact the repository administrator
4. Wait for all-clear before resuming work

Repository Status:
$(git status --porcelain)

Last 5 commits:
$(git log --oneline -5)
" | sendmail team@company.com
EOF

chmod +x git-emergency-notify.sh
```

### Recovery Documentation Template

```markdown
# Git Emergency Report

## Emergency Details
- **Date/Time**: [YYYY-MM-DD HH:MM:SS]
- **Repository**: [Repository Name/URL]
- **Emergency Type**: [Corruption/Data Loss/Force Push/Other]
- **Severity**: [Critical/High/Medium/Low]

## Initial Situation
- **What happened**: [Detailed description]
- **Commands executed**: [List of commands that led to the issue]
- **Error messages**: [Exact error messages received]

## Impact Assessment
- **Data lost**: [What data was lost]
- **Affected team members**: [List of affected people]
- **Project timeline impact**: [How this affects deadlines]

## Recovery Actions Taken
1. [First action taken]
2. [Second action taken]
3. [Continue listing...]

## Current Status
- **Recovery success**: [Complete/Partial/Failed]
- **Data recovered**: [What was successfully recovered]
- **Remaining issues**: [Any ongoing problems]

## Prevention Measures
- **Root cause**: [Why did this happen]
- **Prevention steps**: [How to avoid this in the future]
- **Process improvements**: [Team process changes needed]

## Lessons Learned
- [Key takeaway 1]
- [Key takeaway 2]
- [Continue listing...]
```

## Testing Emergency Procedures

### Emergency Drill Protocol

```bash
# Script per simulare emergenze (solo per test!)
cat > git-emergency-drill.sh << 'EOF'
#!/bin/bash

echo "🚨 GIT EMERGENCY DRILL 🚨"
echo "This will simulate various Git emergencies for training purposes"
echo "ONLY run this in a test repository!"
read -p "Are you sure you want to continue? (type 'YES' to confirm): " confirm

if [ "$confirm" != "YES" ]; then
    echo "Drill cancelled"
    exit 1
fi

# Create test repository
mkdir git-emergency-drill-$(date +%Y%m%d_%H%M%S)
cd git-emergency-drill-*

git init
echo "# Emergency Drill Repository" > README.md
git add README.md
git commit -m "Initial commit"

# Simulate emergencies one by one
echo "Simulating emergency: Accidental hard reset..."
# Add more test scenarios...

echo "Emergency drill completed. Practice your recovery!"
EOF

chmod +x git-emergency-drill.sh
```

---

## Quick Reference: Emergency Commands

### Immediate Damage Control
```bash
git reflog                          # Find lost commits
git fsck --lost-found              # Find disconnected objects
git stash                          # Save current work immediately
cp -r .git .git-backup-$(date +%s) # Emergency backup
```

### Information Gathering
```bash
git status --porcelain             # Machine-readable status
git log --oneline --graph -10      # Recent history visual
git remote -v                      # Remote repositories
git branch -vv                     # Branch tracking info
```

### Safe Undo Operations
```bash
git merge --abort                  # Cancel ongoing merge
git rebase --abort                 # Cancel ongoing rebase
git cherry-pick --abort            # Cancel ongoing cherry-pick
git reset --mixed HEAD             # Undo last commit, keep changes
```

### Nuclear Options (Use with Extreme Caution)
```bash
git reset --hard HEAD~1            # Permanently undo last commit
git push --force-with-lease        # Force push with safety check
git filter-branch                  # Rewrite history (DANGEROUS)
git gc --prune=now                 # Immediate garbage collection
```

---

**⚡ Remember**: In emergencies, speed matters, but accuracy matters more. Take time to understand the situation before acting.

**🔒 Security Note**: Some recovery procedures might expose sensitive data. Always review what you're recovering before sharing or pushing.

**📞 When All Else Fails**: Contact your Git administrator, senior developer, or consider professional Git consulting services for critical business repositories.
