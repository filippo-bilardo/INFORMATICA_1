# Professional Setup - Configurazione Professionale Git

## Scenario
Un'azienda di sviluppo software deve configurare un ambiente Git professionale per un team di 25 sviluppatori distribuiti in 4 team (Frontend, Backend, DevOps, QA).

## Obiettivi
- ✅ Standardizzare configurazioni Git
- ✅ Implementare politiche di sicurezza
- ✅ Configurare hook e automazioni
- ✅ Stabilire workflow standardizzati
- ✅ Implementare monitoring e analytics

## Implementazione

### 1. Configurazione Globale Standard

```bash
#!/bin/bash
# scripts/setup-git-config.sh

echo "🔧 Configurazione Git Professionale"

# Configurazione identità (da personalizzare)
read -p "Nome completo: " fullname
read -p "Email aziendale: " email

git config --global user.name "$fullname"
git config --global user.email "$email"

# Configurazioni di sicurezza
git config --global credential.helper "cache --timeout=3600"
git config --global push.default current
git config --global pull.rebase true

# Configurazioni UI e formattazione
git config --global color.ui auto
git config --global core.editor "code --wait"
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'

# Configurazioni performance
git config --global core.preloadindex true
git config --global core.fscache true
git config --global gc.auto 256

# Alias professionali
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual '!gitk'
git config --global alias.graph 'log --oneline --graph --decorate --all'
git config --global alias.conflicts 'diff --name-only --diff-filter=U'

# Configurazioni commit template
git config --global commit.template ~/.gitmessage

echo "✅ Configurazione completata!"
```

### 2. Template Commit Message Aziendale

```bash
# ~/.gitmessage

# Tipo(scope): Breve descrizione (max 50 caratteri)
#
# Corpo del messaggio (max 72 caratteri per riga)
# - Spiegare il "cosa" e il "perché", non il "come"
# - Utilizzare tempo presente imperativo
#
# Footer:
# - Riferimenti a issue: Fixes #123, Closes #456
# - Breaking changes: BREAKING CHANGE: description
# - Co-authored-by: Nome <email@esempio.com>

# Tipi validi:
# feat:     Nuova funzionalità
# fix:      Correzione bug
# docs:     Documentazione
# style:    Formattazione (non cambia logica)
# refactor: Refactoring del codice
# test:     Aggiunta/modifica test
# chore:    Manutenzione/configurazione
# perf:     Miglioramento performance
# ci:       Configurazione CI/CD
# build:    Sistema di build
```

### 3. Git Hooks Aziendali

#### Pre-commit Hook
```bash
#!/bin/bash
# .git/hooks/pre-commit

echo "🔍 Esecuzione controlli pre-commit..."

# Verifica formato commit message
if ! head -1 .git/COMMIT_EDITMSG | grep -qE "^(feat|fix|docs|style|refactor|test|chore|perf|ci|build)(\(.+\))?: .{1,50}$"; then
    echo "❌ Formato commit message non valido!"
    echo "Usa: tipo(scope): descrizione"
    exit 1
fi

# Controllo linting
echo "📝 Controllo linting..."
npm run lint || exit 1

# Controllo test unitari
echo "🧪 Esecuzione test..."
npm test || exit 1

# Controllo sicurezza
echo "🔒 Controllo sicurezza..."
npm audit --audit-level high || exit 1

# Controllo dimensione file
echo "📊 Controllo dimensione file..."
for file in $(git diff --cached --name-only); do
    if [[ -f "$file" && $(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null) -gt 1048576 ]]; then
        echo "❌ File troppo grande: $file (>1MB)"
        exit 1
    fi
done

# Controllo segreti
echo "🔐 Controllo segreti..."
if git diff --cached --name-only | xargs grep -l "password\|secret\|key\|token" >/dev/null 2>&1; then
    echo "⚠️  Possibili credenziali rilevate. Verificare i file prima del commit."
    read -p "Continuare? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

echo "✅ Tutti i controlli superati!"
exit 0
```

#### Pre-push Hook
```bash
#!/bin/bash
# .git/hooks/pre-push

echo "🚀 Controlli pre-push..."

protected_branch='main'
current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')

# Protezione branch main
if [ $protected_branch = $current_branch ]; then
    echo "❌ Push diretto su main non consentito!"
    echo "Utilizzare Pull Request per il merge."
    exit 1
fi

# Controllo se il branch è aggiornato
git fetch origin $current_branch

COMMITS_BEHIND=$(git rev-list --count HEAD..origin/$current_branch)
if [ $COMMITS_BEHIND -gt 0 ]; then
    echo "❌ Il branch locale è indietro di $COMMITS_BEHIND commit"
    echo "Eseguire git pull prima del push"
    exit 1
fi

# Test completi prima del push
echo "🧪 Esecuzione test completi..."
npm run test:full || exit 1

echo "✅ Push autorizzato!"
exit 0
```

### 4. Configurazione Repository Template

#### .gitignore Aziendale
```gitignore
# =============================================================================
# Template .gitignore Aziendale
# =============================================================================

# ===== LOGS =====
logs/
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# ===== RUNTIME DATA =====
pids/
*.pid
*.seed
*.pid.lock
.npm
.eslintcache

# ===== DEPENDENCY DIRECTORIES =====
node_modules/
jspm_packages/
vendor/
.pnp/
.pnp.js

# ===== BUILD OUTPUTS =====
dist/
build/
out/
.next/
.nuxt/
target/
*.tgz
*.tar.gz

# ===== ENVIRONMENT VARIABLES =====
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# ===== CACHE =====
.cache/
.parcel-cache/
.npm
.yarn-integrity
.pnp.*

# ===== IDE/EDITOR =====
.vscode/
.idea/
*.swp
*.swo
*~

# ===== OS =====
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# ===== DATABASE =====
*.sqlite
*.sqlite3
*.db

# ===== CERTIFICATI E CHIAVI (SICUREZZA) =====
*.pem
*.p12
*.key
*.crt
*.csr
*.pfx

# ===== DOCUMENTI SENSIBILI =====
secrets/
private/
confidential/
*.secret
```

#### README Template
```markdown
# [Nome Progetto]

[![Build Status](https://ci.company.com/buildStatus/icon?job=project-name)](https://ci.company.com/job/project-name/)
[![Coverage](https://codecov.io/gh/company/project/branch/main/graph/badge.svg)](https://codecov.io/gh/company/project)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## 📋 Descrizione
[Breve descrizione del progetto]

## 🚀 Quick Start

### Prerequisiti
- Node.js >= 16.0.0
- npm >= 8.0.0
- Git >= 2.30.0

### Installazione
```bash
git clone https://github.com/company/project.git
cd project
npm install
npm run setup
```

### Sviluppo
```bash
npm run dev          # Avvia server sviluppo
npm run test         # Esegue test
npm run test:watch   # Test in modalità watch
npm run lint         # Controllo linting
npm run build        # Build produzione
```

## 🏗️ Architettura
[Diagrammi e spiegazione architettura]

## 🤝 Contribuzione

### Workflow
1. Fork del repository
2. Crea feature branch: `git checkout -b feature/amazing-feature`
3. Commit delle modifiche: `git commit -m 'feat: add amazing feature'`
4. Push del branch: `git push origin feature/amazing-feature`
5. Apri Pull Request

### Standards
- Seguire [Conventional Commits](https://www.conventionalcommits.org/)
- Test coverage minimo: 80%
- Tutti i controlli CI devono passare
- Review obbligatoria da almeno 2 sviluppatori

## 📖 Documentazione
- [API Documentation](docs/api.md)
- [Development Guide](docs/development.md)
- [Deployment Guide](docs/deployment.md)

## 📝 License
Questo progetto è licenziato sotto MIT License - vedi [LICENSE](LICENSE) per dettagli.
```

### 5. Configurazione CI/CD (GitHub Actions)

```yaml
# .github/workflows/ci.yml
name: CI/CD Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main, develop]

env:
  NODE_VERSION: '18'
  CACHE_KEY: v1

jobs:
  lint:
    name: Code Quality
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
          
      - name: Install dependencies
        run: npm ci
        
      - name: Lint
        run: npm run lint
        
      - name: Type check
        run: npm run type-check
        
      - name: Security audit
        run: npm audit --audit-level high

  test:
    name: Tests
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
          cache: 'npm'
          
      - name: Install dependencies
        run: npm ci
        
      - name: Run tests
        run: npm run test:coverage
        
      - name: Upload coverage
        uses: codecov/codecov-action@v3
        if: matrix.node-version == 18

  build:
    name: Build
    runs-on: ubuntu-latest
    needs: [lint, test]
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
          
      - name: Install dependencies
        run: npm ci
        
      - name: Build
        run: npm run build
        
      - name: Upload build artifacts
        uses: actions/upload-artifact@v3
        with:
          name: build-${{ github.sha }}
          path: dist/

  deploy:
    name: Deploy
    runs-on: ubuntu-latest
    needs: build
    if: github.ref == 'refs/heads/main'
    environment: production
    steps:
      - name: Deploy to production
        run: echo "🚀 Deploying to production..."
```

### 6. Monitoraggio e Analytics

#### Script di Analytics Git
```bash
#!/bin/bash
# scripts/git-analytics.sh

echo "📊 ANALYTICS REPOSITORY GIT"
echo "============================"

# Statistiche generali
echo "📈 Statistiche Generali:"
echo "Commit totali: $(git rev-list --all --count)"
echo "Branch attivi: $(git branch -r | wc -l)"
echo "Contributor: $(git shortlog -sn | wc -l)"
echo "Dimensione repository: $(du -sh .git | cut -f1)"

# Top contributor
echo -e "\n👥 Top 10 Contributor:"
git shortlog -sn | head -10

# Attività mensile
echo -e "\n📅 Attività Ultimi 6 Mesi:"
for i in {0..5}; do
    month=$(date -d "$i month ago" +%Y-%m)
    count=$(git log --since="$month-01" --until="$month-31" --oneline | wc -l)
    echo "$month: $count commit"
done

# File più modificati
echo -e "\n📝 File Più Modificati:"
git log --name-only --pretty=format: | sort | uniq -c | sort -rn | head -10

# Linguaggi
echo -e "\n💻 Linguaggi di Programmazione:"
find . -type f -name "*.js" -o -name "*.ts" -o -name "*.py" -o -name "*.java" | \
grep -v node_modules | \
sed 's/.*\.//' | sort | uniq -c | sort -rn

# Health check
echo -e "\n🏥 Health Check Repository:"
orphaned_branches=$(git for-each-ref --format='%(refname:short) %(committerdate)' refs/heads | awk '$2 < "'$(date -d '3 months ago' -I)'"' | wc -l)
echo "Branch orfani (>3 mesi): $orphaned_branches"

large_files=$(find . -size +10M -not -path "./.git/*" | wc -l)
echo "File grandi (>10MB): $large_files"

uncommitted=$(git status --porcelain | wc -l)
echo "File non committati: $uncommitted"
```

### 7. Configurazione Team per Tipo

#### Frontend Team
```bash
# Frontend specific git config
git config --global core.autocrlf false
git config --global merge.tool 'vscode'
git config --global diff.tool 'vscode'

# Alias specifici frontend
git config --global alias.feature-start '!f() { git checkout develop && git pull origin develop && git checkout -b feature/$1; }; f'
git config --global alias.feature-finish '!f() { git checkout develop && git pull origin develop && git merge --no-ff feature/$1 && git branch -d feature/$1; }; f'
```

#### Backend Team
```bash
# Backend specific git config
git config --global core.fileMode false
git config --global core.autocrlf input

# Alias per hotfix
git config --global alias.hotfix-start '!f() { git checkout main && git pull origin main && git checkout -b hotfix/$1; }; f'
git config --global alias.hotfix-finish '!f() { git checkout main && git merge --no-ff hotfix/$1 && git tag -a v$1 -m "Hotfix v$1" && git checkout develop && git merge --no-ff hotfix/$1 && git branch -d hotfix/$1; }; f'
```

### 8. Documentazione e Training

#### Checklist Onboarding
```markdown
# Git Onboarding Checklist

## Setup Iniziale
- [ ] Installazione Git ultima versione
- [ ] Configurazione identità (nome + email aziendale)
- [ ] Setup SSH keys per GitHub
- [ ] Installazione Git LFS (se necessario)
- [ ] Configurazione .gitconfig aziendale

## Formazione
- [ ] Lettura policy Git aziendali
- [ ] Workshop Git Flow (2 ore)
- [ ] Pratica con repository di training
- [ ] Shadowing senior developer (1 settimana)
- [ ] Certificazione Git interna

## Accessi
- [ ] Accesso GitHub Organization
- [ ] Aggiunta ai team repository
- [ ] Configurazione IDE con Git
- [ ] Accesso sistemi CI/CD

## Validazione
- [ ] Primo commit su repository test
- [ ] Prima Pull Request rivista
- [ ] Primo merge su develop
- [ ] Quiz di validazione (>80%)
```

## Risultati Attesi

### Metriche di Successo
- **Standardizzazione**: 100% team utilizza configurazioni uniformi
- **Qualità**: Riduzione bug del 40% attraverso automazioni
- **Velocità**: Tempo setup nuovo sviluppatore < 1 ora
- **Sicurezza**: Zero credenziali in repository
- **Collaborazione**: 95% Pull Request approvate al primo tentativo

### Benefici
- **Consistenza**: Workflow uniformi across team
- **Efficienza**: Automazione controlli qualità
- **Sicurezza**: Prevenzione leak credenziali
- **Scalabilità**: Onboarding rapido nuovi sviluppatori
- **Qualità**: Riduzione errori attraverso standard

### Monitoring
- Dashboard Git analytics settimanale
- Report qualità codice mensile
- Survey soddisfazione team trimestrale
- Audit sicurezza semestrale

---

*Questa configurazione professionale Git garantisce standard elevati di qualità, sicurezza e collaborazione per team enterprise.*
