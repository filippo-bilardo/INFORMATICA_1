# Team Standards - Standard e Convenzioni di Team

## Scenario
Un'azienda tecnologica con 150 sviluppatori distribuiti in 12 team deve standardizzare le pratiche di sviluppo Git per migliorare collaborazione, qualità del codice e velocità di delivery.

## Obiettivi
- ✅ Definire convenzioni commit uniformi
- ✅ Stabilire workflow branch standardizzati
- ✅ Implementare code review efficaci
- ✅ Automatizzare controlli qualità
- ✅ Creare documentazione accessibile

## Standards Implementati

### 1. Convenzioni Commit

#### Conventional Commits Standard
```yaml
# .gitmessage-template
# Formato: <tipo>[optional scope]: <descrizione>
#
# [optional body]
#
# [optional footer(s)]

# TIPI CONSENTITI:
# feat:     ✨ Nuova funzionalità
# fix:      🐛 Correzione bug
# docs:     📚 Solo documentazione
# style:    💎 Cambi che non influenzano significato
# refactor: ♻️  Refactoring senza nuove funzionalità o fix
# perf:     ⚡ Miglioramento performance
# test:     🧪 Aggiunta o correzione test
# build:    🏗️  Cambi al build system o dipendenze
# ci:       👷 Cambi ai file e script CI
# chore:    🔧 Altri cambi che non modificano src o test
# revert:   ⏪ Ripristino commit precedente

# ESEMPI:
# feat(auth): add OAuth2 integration
# fix(api): resolve null pointer exception in user service
# docs(readme): update installation instructions
# style(components): format code with prettier
# refactor(utils): extract common validation logic
# perf(database): optimize user query performance
# test(auth): add unit tests for login service
# build(deps): bump lodash from 4.17.19 to 4.17.21
# ci(github): add automated deployment workflow
# chore(config): update environment variables
```

#### Commit Message Policy
```bash
#!/bin/bash
# scripts/commit-msg-hook.sh

# Regex per validazione formato
COMMIT_REGEX='^(feat|fix|docs|style|refactor|perf|test|build|ci|chore|revert)(\(.+\))?: .{1,50}'

# Lettura del messaggio di commit
commit_message=$(cat "$1")

# Validazione formato
if ! echo "$commit_message" | grep -qE "$COMMIT_REGEX"; then
    echo "❌ COMMIT MESSAGE NON VALIDO!"
    echo ""
    echo "Formato richiesto:"
    echo "  <tipo>[optional scope]: <descrizione>"
    echo ""
    echo "Tipi validi:"
    echo "  feat, fix, docs, style, refactor, perf, test, build, ci, chore, revert"
    echo ""
    echo "Esempi:"
    echo "  feat(auth): add login functionality"
    echo "  fix: resolve memory leak in worker"
    echo "  docs(api): update endpoint documentation"
    echo ""
    exit 1
fi

# Controllo lunghezza descrizione
description_length=$(echo "$commit_message" | head -n1 | wc -c)
if [ $description_length -gt 72 ]; then
    echo "⚠️  ATTENZIONE: Descrizione commit troppo lunga (>72 caratteri)"
    echo "Considerare di abbreviare o usare il body del commit per dettagli."
fi

# Controllo parole vietate
forbidden_words=("wip" "tmp" "temp" "debug" "test123" "asdf")
for word in "${forbidden_words[@]}"; do
    if echo "$commit_message" | grep -iq "$word"; then
        echo "❌ Parola vietata rilevata: '$word'"
        echo "Utilizzare un messaggio più descrittivo."
        exit 1
    fi
done

echo "✅ Commit message valido!"
```

### 2. Branch Naming Strategy

#### Convenzioni Naming
```yaml
# Branch Naming Convention

# PATTERN GENERALE:
# <tipo>/<ticket-id>/<breve-descrizione>

# TIPI DI BRANCH:
feature:   # Nuove funzionalità
  pattern: "feature/JIRA-123/user-authentication"
  examples:
    - "feature/AUTH-456/oauth2-integration"
    - "feature/PAY-789/stripe-payment-gateway"
    - "feature/UI-321/dark-mode-theme"

bugfix:    # Correzione bug non critici
  pattern: "bugfix/JIRA-123/fix-memory-leak"
  examples:
    - "bugfix/BUG-123/resolve-null-pointer"
    - "bugfix/UI-456/fix-responsive-layout"
    - "bugfix/API-789/handle-timeout-errors"

hotfix:    # Correzioni critiche per produzione
  pattern: "hotfix/v1.2.3/critical-security-fix"
  examples:
    - "hotfix/v2.1.1/sql-injection-patch"
    - "hotfix/v1.5.2/memory-overflow-fix"
    - "hotfix/v3.0.1/authentication-bypass"

release:   # Preparazione release
  pattern: "release/v1.2.0"
  examples:
    - "release/v2.0.0"
    - "release/v1.5.0-beta"
    - "release/v3.1.0-rc1"

support:   # Supporto versioni precedenti
  pattern: "support/v1.x"
  examples:
    - "support/v1.4.x"
    - "support/legacy-api"

experiment: # Spike e prototipi
  pattern: "experiment/performance-optimization"
  examples:
    - "experiment/react18-migration"
    - "experiment/microservices-poc"
    - "experiment/ai-integration"
```

#### Script Validazione Branch
```bash
#!/bin/bash
# scripts/validate-branch-name.sh

branch_name=$(git symbolic-ref --short HEAD)
valid_pattern='^(feature|bugfix|hotfix|release|support|experiment)\/[A-Z]+-[0-9]+\/[a-z0-9-]+$|^(main|develop)$'

if [[ ! $branch_name =~ $valid_pattern ]]; then
    echo "❌ NOME BRANCH NON VALIDO: $branch_name"
    echo ""
    echo "Formati accettati:"
    echo "  feature/TICKET-123/description"
    echo "  bugfix/BUG-456/description"
    echo "  hotfix/v1.2.3/description"
    echo "  release/v1.2.0"
    echo "  support/v1.x"
    echo "  experiment/description"
    echo ""
    echo "Branch speciali: main, develop"
    echo ""
    exit 1
fi

echo "✅ Nome branch valido: $branch_name"
```

### 3. Code Review Standards

#### Pull Request Template
```markdown
<!-- .github/pull_request_template.md -->

## 📋 Descrizione
<!-- Breve descrizione delle modifiche -->

## 🎯 Tipo di Cambiamento
- [ ] 🐛 Bug fix (cambiamento non-breaking che risolve un issue)
- [ ] ✨ Nuova funzionalità (cambiamento non-breaking che aggiunge funzionalità)
- [ ] 💥 Breaking change (fix o funzionalità che causa cambiamenti existing)
- [ ] 📚 Aggiornamento documentazione
- [ ] 🎨 Miglioramento UI/UX
- [ ] ⚡ Ottimizzazione performance
- [ ] 🧪 Aggiunta/modifica test

## 🧪 Testing
- [ ] Test unitari aggiunti/aggiornati
- [ ] Test integrazione verificati
- [ ] Test manuali eseguiti
- [ ] Scenario di errore testati

### Test Cases
<!-- Descrivi i test case principali -->

## 📸 Screenshots/Video
<!-- Se applicabile, aggiungi screenshots o video -->

## 🔗 Link Correlati
- Issue: #
- Documentazione: 
- Design: 

## 📝 Checklist
- [ ] Il codice segue le style guidelines del progetto
- [ ] Ho eseguito self-review del mio codice
- [ ] Ho commentato il codice in aree difficili da comprendere
- [ ] Ho aggiornato la documentazione corrispondente
- [ ] Le mie modifiche non generano nuovi warning
- [ ] Ho aggiunto test che provano che il fix è efficace o la feature funziona
- [ ] Test nuovi ed esistenti passano localmente
- [ ] Eventuali modifiche dipendenti sono state integrate

## 🚀 Deployment Notes
<!-- Note speciali per il deployment -->

## 📊 Performance Impact
<!-- Impatto stimato sulle performance -->

---

### 📋 Review Checklist (per Reviewer)
- [ ] Codice leggibile e ben strutturato
- [ ] Logica di business corretta
- [ ] Gestione errori appropriata
- [ ] Test coverage adeguata
- [ ] Performance accettabili
- [ ] Sicurezza verificata
- [ ] Documentazione aggiornata
```

#### Code Review Guidelines
```yaml
# Code Review Guidelines

OBIETTIVI:
  - Mantenere qualità del codice
  - Condividere conoscenza nel team
  - Identificare bug prima della produzione
  - Assicurare consistenza architetturale

PROCESS:
  1. Autor:
     - Crea PR con descrizione dettagliata
     - Assegna reviewer appropriati
     - Risolve commenti tempestivamente
     - Esegue testing completo
  
  2. Reviewer:
     - Review entro 24 ore
     - Fornisce feedback costruttivo
     - Testa modifiche localmente se necessario
     - Approva solo quando soddisfatto

CRITERI APPROVAL:
  - Almeno 2 approvazioni per main branch
  - 1 approvazione senior developer per feature critiche
  - Tutti i controlli CI devono passare
  - Nessun commento irrisolto

COSA REVIEWARE:
  functional:
    - Logica di business corretta
    - Gestione edge cases
    - Validazione input
    - Gestione errori

  technical:
    - Architettura e design pattern
    - Performance e scalabilità
    - Sicurezza
    - Manutenibilità

  quality:
    - Leggibilità codice
    - Naming conventions
    - Commenti e documentazione
    - Test coverage

FEEDBACK GUIDELINES:
  - Usa tono costruttivo e professionale
  - Spiega il "perché" oltre al "cosa"
  - Suggerisci soluzioni alternative
  - Distingui tra blocking e non-blocking comments
  - Riconosci il buon lavoro
```

### 4. Workflow di Collaborazione

#### Git Flow Aziendale
```bash
#!/bin/bash
# scripts/team-workflow.sh

# Configurazione Git Flow team

echo "🔧 Setup Git Flow Aziendale"

# Inizializzazione Git Flow
git flow init -d

# Configurazione branch protection
echo "🛡️  Configurazione protezione branch..."

# Hook per branch protection
cat > .git/hooks/pre-push << 'EOF'
#!/bin/bash

protected_branches="main develop"
current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')

for branch in $protected_branches; do
    if [ $branch = $current_branch ]; then
        echo "❌ Push diretto su $branch non consentito!"
        echo "Utilizzare Pull Request per il merge."
        exit 1
    fi
done

# Verifica che il branch sia aggiornato
git fetch origin

COMMITS_BEHIND=$(git rev-list --count HEAD..origin/$current_branch 2>/dev/null || echo "0")
if [ $COMMITS_BEHIND -gt 0 ]; then
    echo "❌ Il branch è indietro di $COMMITS_BEHIND commit"
    echo "Eseguire git pull prima del push"
    exit 1
fi

echo "✅ Push autorizzato"
EOF

chmod +x .git/hooks/pre-push

# Script helper per workflow comune
cat > scripts/team-helpers.sh << 'EOF'
#!/bin/bash

# Helper per operazioni team comuni

function start_feature() {
    if [ -z "$1" ]; then
        echo "❌ Specificare ticket ID: start_feature JIRA-123"
        return 1
    fi
    
    if [ -z "$2" ]; then
        echo "❌ Specificare descrizione: start_feature JIRA-123 'user-auth'"
        return 1
    fi
    
    git checkout develop
    git pull origin develop
    git checkout -b "feature/$1/$2"
    echo "✅ Feature branch creato: feature/$1/$2"
}

function finish_feature() {
    current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')
    
    if [[ ! $current_branch =~ ^feature\/ ]]; then
        echo "❌ Non sei su un feature branch"
        return 1
    fi
    
    echo "🔍 Controlli pre-merge..."
    
    # Controllo che tutti i file siano committati
    if [ -n "$(git status --porcelain)" ]; then
        echo "❌ Ci sono modifiche non committate"
        return 1
    fi
    
    # Push del branch
    git push origin $current_branch
    
    echo "✅ Feature branch pronto per PR"
    echo "Crea Pull Request su GitHub per merge in develop"
}

function start_hotfix() {
    if [ -z "$1" ]; then
        echo "❌ Specificare versione: start_hotfix v1.2.3"
        return 1
    fi
    
    git checkout main
    git pull origin main
    git checkout -b "hotfix/$1/$2"
    echo "✅ Hotfix branch creato: hotfix/$1/$2"
}

function sync_with_develop() {
    current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')
    
    echo "🔄 Sincronizzazione con develop..."
    git fetch origin develop
    git merge origin/develop
    
    if [ $? -eq 0 ]; then
        echo "✅ Merge con develop completato"
    else
        echo "❌ Conflitti rilevati, risolverli manualmente"
    fi
}

# Esporta funzioni
export -f start_feature finish_feature start_hotfix sync_with_develop
EOF

echo "✅ Git Flow aziendale configurato!"
echo "Source scripts/team-helpers.sh per usare i comandi helper"
```

### 5. Quality Gates e Automation

#### Pre-commit Configuration
```yaml
# .pre-commit-config.yaml
repos:
  - repo: https://github.com/pre-commit/pre-commit-hooks
    rev: v4.4.0
    hooks:
      - id: trailing-whitespace
      - id: end-of-file-fixer
      - id: check-yaml
      - id: check-json
      - id: check-added-large-files
        args: ['--maxkb=1000']
      - id: check-case-conflict
      - id: check-merge-conflict
      - id: debug-statements
      - id: check-docstring-first

  - repo: https://github.com/psf/black
    rev: 23.1.0
    hooks:
      - id: black
        language_version: python3

  - repo: https://github.com/pycqa/isort
    rev: 5.12.0
    hooks:
      - id: isort

  - repo: https://github.com/pycqa/flake8
    rev: 6.0.0
    hooks:
      - id: flake8

  - repo: https://github.com/pre-commit/mirrors-eslint
    rev: v8.34.0
    hooks:
      - id: eslint
        files: \.(js|ts|jsx|tsx)$

  - repo: https://github.com/pre-commit/mirrors-prettier
    rev: v2.7.1
    hooks:
      - id: prettier
        files: \.(js|ts|jsx|tsx|json|css|md|yml|yaml)$

  - repo: local
    hooks:
      - id: commit-msg-format
        name: Commit message format
        entry: scripts/validate-commit-msg.sh
        language: script
        stages: [commit-msg]
        
      - id: branch-name-check
        name: Branch name check
        entry: scripts/validate-branch-name.sh
        language: script
        stages: [push]

      - id: secrets-check
        name: Secrets check
        entry: scripts/check-secrets.sh
        language: script
        files: .*
```

#### CI/CD Integration
```yaml
# .github/workflows/quality-gates.yml
name: Quality Gates

on:
  pull_request:
    branches: [main, develop]
  push:
    branches: [main, develop]

jobs:
  code-quality:
    name: Code Quality Checks
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0

      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'

      - name: Install dependencies
        run: npm ci

      - name: Lint check
        run: npm run lint

      - name: Type check
        run: npm run type-check

      - name: Format check
        run: npm run format:check

      - name: Security audit
        run: npm audit --audit-level high

  test-coverage:
    name: Test Coverage
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'

      - name: Install dependencies
        run: npm ci

      - name: Run tests with coverage
        run: npm run test:coverage

      - name: Check coverage threshold
        run: |
          COVERAGE=$(npm run test:coverage:json | jq '.total.lines.pct')
          if (( $(echo "$COVERAGE < 80" | bc -l) )); then
            echo "❌ Coverage below threshold: $COVERAGE%"
            exit 1
          fi
          echo "✅ Coverage passed: $COVERAGE%"

      - name: Upload coverage to Codecov
        uses: codecov/codecov-action@v3

  pr-checks:
    name: PR Validation
    runs-on: ubuntu-latest
    if: github.event_name == 'pull_request'
    steps:
      - uses: actions/checkout@v3

      - name: Check PR title format
        run: |
          PR_TITLE="${{ github.event.pull_request.title }}"
          if [[ ! $PR_TITLE =~ ^(feat|fix|docs|style|refactor|perf|test|build|ci|chore|revert)(\(.+\))?: .+ ]]; then
            echo "❌ PR title doesn't follow conventional format"
            exit 1
          fi

      - name: Check branch name
        run: |
          BRANCH_NAME="${{ github.head_ref }}"
          if [[ ! $BRANCH_NAME =~ ^(feature|bugfix|hotfix|release|support|experiment)\/.+ ]]; then
            echo "❌ Branch name doesn't follow naming convention"
            exit 1
          fi

      - name: Check PR size
        run: |
          FILES_CHANGED=$(git diff --name-only origin/${{ github.base_ref }}...HEAD | wc -l)
          LINES_CHANGED=$(git diff --stat origin/${{ github.base_ref }}...HEAD | tail -1 | grep -oE '[0-9]+ insertions|[0-9]+ deletions' | grep -oE '[0-9]+' | paste -sd+ | bc)
          
          if [ $FILES_CHANGED -gt 20 ] || [ $LINES_CHANGED -gt 500 ]; then
            echo "⚠️ Large PR detected: $FILES_CHANGED files, $LINES_CHANGED lines"
            echo "Consider breaking into smaller PRs"
          fi

  security-scan:
    name: Security Scan
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Run Trivy vulnerability scanner
        uses: aquasecurity/trivy-action@master
        with:
          scan-type: 'fs'
          scan-ref: '.'
          format: 'sarif'
          output: 'trivy-results.sarif'

      - name: Upload Trivy scan results
        uses: github/codeql-action/upload-sarif@v2
        with:
          sarif_file: 'trivy-results.sarif'
```

### 6. Documentation Standards

#### README Structure Standard
```markdown
# 📋 README Standard Template

## 🎯 Project Overview
- **Purpose**: [Brief project description]
- **Status**: [Development/Staging/Production]
- **Version**: [Current version]
- **License**: [License type]

## 🚀 Quick Start
```bash
# Installation
git clone [repository-url]
cd [project-name]
npm install

# Development
npm run dev

# Testing
npm test
```

## 📊 Project Status
![Build Status](badge-url)
![Coverage](badge-url)
![Dependencies](badge-url)

## 🏗️ Architecture
[Architecture diagram and explanation]

## 🛠️ Tech Stack
- **Frontend**: [technologies]
- **Backend**: [technologies]
- **Database**: [technologies]
- **Infrastructure**: [technologies]

## 📚 Documentation
- [API Documentation](./docs/api.md)
- [Development Setup](./docs/development.md)
- [Deployment Guide](./docs/deployment.md)
- [Contributing Guidelines](./CONTRIBUTING.md)

## 🤝 Contributing
1. Read [Contributing Guidelines](./CONTRIBUTING.md)
2. Fork the repository
3. Create feature branch: `feature/TICKET-123/description`
4. Commit changes: `feat(scope): description`
5. Push branch and create PR

## 📞 Support
- **Documentation**: [link]
- **Issues**: [GitHub Issues](./issues)
- **Slack**: #team-channel
- **Email**: team@company.com

## 📈 Metrics and Monitoring
- **Performance**: [dashboard-link]
- **Logs**: [logging-system-link]
- **Metrics**: [metrics-dashboard-link]
```

### 7. Team Metrics e KPIs

#### Git Analytics Dashboard
```bash
#!/bin/bash
# scripts/team-metrics.sh

echo "📊 TEAM METRICS DASHBOARD"
echo "========================"

# Periodo di analisi (ultimi 30 giorni)
SINCE_DATE=$(date -d '30 days ago' +%Y-%m-%d)

echo "📅 Periodo analisi: $SINCE_DATE - $(date +%Y-%m-%d)"
echo ""

# Metriche commit
echo "📈 COMMIT METRICS:"
echo "Total commits: $(git rev-list --since="$SINCE_DATE" --count HEAD)"
echo "Authors active: $(git shortlog --since="$SINCE_DATE" -sn | wc -l)"
echo "Avg commits/day: $(echo "scale=1; $(git rev-list --since="$SINCE_DATE" --count HEAD) / 30" | bc)"

# Top contributors
echo -e "\n👥 TOP CONTRIBUTORS (30 days):"
git shortlog --since="$SINCE_DATE" -sn | head -5

# Branch metrics
echo -e "\n🌿 BRANCH METRICS:"
echo "Active branches: $(git branch -r | grep -v HEAD | wc -l)"
echo "Feature branches: $(git branch -r | grep feature | wc -l)"
echo "Bug branches: $(git branch -r | grep bugfix | wc -l)"

# PR metrics (requires GitHub CLI)
if command -v gh &> /dev/null; then
    echo -e "\n🔀 PULL REQUEST METRICS:"
    echo "Open PRs: $(gh pr list --state open | wc -l)"
    echo "Merged PRs (30d): $(gh pr list --state merged --search "merged:>=$SINCE_DATE" | wc -l)"
fi

# Code quality metrics
echo -e "\n🎯 QUALITY METRICS:"
if [ -f "coverage/coverage-summary.json" ]; then
    COVERAGE=$(cat coverage/coverage-summary.json | jq '.total.lines.pct')
    echo "Test coverage: $COVERAGE%"
fi

# Conventional commits compliance
echo -e "\n📝 CONVENTIONAL COMMITS:"
TOTAL_COMMITS=$(git rev-list --since="$SINCE_DATE" --count HEAD)
CONVENTIONAL_COMMITS=$(git log --since="$SINCE_DATE" --oneline | grep -E '^[a-f0-9]+ (feat|fix|docs|style|refactor|perf|test|build|ci|chore|revert)(\(.+\))?: ' | wc -l)
COMPLIANCE_RATE=$(echo "scale=1; $CONVENTIONAL_COMMITS * 100 / $TOTAL_COMMITS" | bc)
echo "Compliance rate: $COMPLIANCE_RATE%"

# File change patterns
echo -e "\n📁 FILE CHANGE PATTERNS:"
git log --since="$SINCE_DATE" --name-only --pretty=format: | sort | uniq -c | sort -rn | head -5

# Team velocity
echo -e "\n⚡ TEAM VELOCITY:"
WEEK1=$(git rev-list --since="7 days ago" --count HEAD)
WEEK2=$(git rev-list --since="14 days ago" --until="7 days ago" --count HEAD)
WEEK3=$(git rev-list --since="21 days ago" --until="14 days ago" --count HEAD)
WEEK4=$(git rev-list --since="28 days ago" --until="21 days ago" --count HEAD)

echo "Week 1 (latest): $WEEK1 commits"
echo "Week 2: $WEEK2 commits"
echo "Week 3: $WEEK3 commits"
echo "Week 4: $WEEK4 commits"

# Health indicators
echo -e "\n🏥 REPOSITORY HEALTH:"
LARGE_FILES=$(find . -size +5M -not -path "./.git/*" | wc -l)
STALE_BRANCHES=$(git for-each-ref --format='%(refname:short) %(committerdate)' refs/remotes/origin | awk '$2 < "'$(date -d '60 days ago' -I)'"' | wc -l)
UNCOMMITTED=$(git status --porcelain | wc -l)

echo "Large files (>5MB): $LARGE_FILES"
echo "Stale branches (>60d): $STALE_BRANCHES"
echo "Uncommitted changes: $UNCOMMITTED"

echo -e "\n✅ Report generato: $(date)"
```

## Risultati e Benefici

### Metriche di Successo
- **Standardizzazione**: 95% conformità convenzioni
- **Qualità**: 40% riduzione bug in produzione
- **Velocità**: 60% riduzione tempo review
- **Collaborazione**: 90% soddisfazione team
- **Onboarding**: Setup nuovo dev in 2 ore

### ROI Aziendale
- **Tempo risparmiato**: 20 ore/settimana team
- **Qualità software**: +35% metriche qualità
- **Time-to-market**: -25% ciclo sviluppo
- **Manutenibilità**: +50% facilità modifiche
- **Knowledge sharing**: +80% trasferimento competenze

### Implementation Timeline
```
Settimana 1-2: Training e setup iniziale
Settimana 3-4: Implementazione graduale
Settimana 5-6: Automazione e monitoring
Settimana 7-8: Fine-tuning e ottimizzazione
```

---

*Questi standard team garantiscono collaborazione efficace, qualità consistente e crescita sostenibile per organizzazioni di qualsiasi dimensione.*
