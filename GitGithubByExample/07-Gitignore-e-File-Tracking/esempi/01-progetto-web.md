# Esempio: Configurazione Progetto Web

## 🎯 Scenario
Stai sviluppando un progetto web moderno con React + Node.js + MongoDB. Devi configurare un `.gitignore` completo che gestisca frontend, backend, database locale, e strumenti di sviluppo.

## 🏗️ Struttura del Progetto
```
my-web-app/
├── frontend/                 # React app
│   ├── src/
│   ├── public/
│   ├── build/               # ❌ Da ignorare
│   ├── node_modules/        # ❌ Da ignorare
│   └── package.json
├── backend/                 # Node.js API
│   ├── src/
│   ├── uploads/             # ❌ Da ignorare
│   ├── node_modules/        # ❌ Da ignorare
│   └── package.json
├── database/
│   └── local_data/          # ❌ Da ignorare
├── docs/
├── .env                     # ❌ Da ignorare
├── docker-compose.yml
└── README.md
```

## 📝 Configurazione .gitignore Passo-Passo

### Step 1: Setup Iniziale
```bash
# Inizializza il progetto
$ mkdir my-web-app
$ cd my-web-app
$ git init

# Crea la struttura base
$ mkdir -p frontend/src backend/src database docs
$ touch frontend/package.json backend/package.json
$ touch README.md docker-compose.yml
```

### Step 2: Crea .gitignore Base
```bash
# Crea file .gitignore
$ touch .gitignore
```

### Step 3: Configurazione per Dipendenze
```gitignore
# ========================================
# DEPENDENCIES - Package Managers
# ========================================

# Node.js dependencies (frontend + backend)
**/node_modules/
node_modules/

# Yarn
yarn-error.log
.yarn/
.pnp.*

# npm
npm-debug.log*
.npm

# pnpm
.pnpm-debug.log*
```

### Step 4: Environment e Secrets
```gitignore
# ========================================
# ENVIRONMENT & SECRETS - CRITICAL!
# ========================================

# Environment files
.env
.env.local
.env.development
.env.staging
.env.production
.env.test

# Database connection strings
config/database.yml
config/secrets.yml

# SSL/TLS certificates
*.pem
*.key
*.crt
*.p12

# API keys and tokens
**/secrets/
api-keys.json
```

### Step 5: Build e Output
```gitignore
# ========================================
# BUILD OUTPUTS & GENERATED FILES
# ========================================

# Frontend builds
frontend/build/
frontend/dist/
frontend/.next/
frontend/out/

# Backend builds
backend/build/
backend/dist/

# Static site generators
.nuxt/
.vuepress/dist
.docusaurus/

# Bundler outputs
*.bundle.js
*.bundle.css
```

### Step 6: Database e Upload
```gitignore
# ========================================
# DATABASE & USER UPLOADS
# ========================================

# Local database files
database/local_data/
*.sqlite
*.sqlite3
*.db

# Database dumps
*.sql
*.dump

# User uploads
backend/uploads/
**/uploads/
public/uploads/

# Media files
media/
assets/uploads/
```

### Step 7: Cache e Temporanei
```gitignore
# ========================================
# CACHE & TEMPORARY FILES
# ========================================

# Build cache
.cache/
.parcel-cache/
.eslintcache
.stylelintcache

# Testing cache
.jest/
.pytest_cache/

# General cache
tmp/
temp/
*.tmp
*.temp

# Logs
*.log
logs/
npm-debug.log*
yarn-debug.log*
```

### Step 8: IDE e Editor
```gitignore
# ========================================
# IDE & DEVELOPMENT TOOLS
# ========================================

# Visual Studio Code
.vscode/
!.vscode/settings.json.example
!.vscode/extensions.json

# IntelliJ IDEA
.idea/
*.iml

# Vim
*.swp
*.swo
*~

# Emacs
*~
\#*\#
/.emacs.desktop
/.emacs.desktop.lock
```

### Step 9: Sistema Operativo
```gitignore
# ========================================
# OPERATING SYSTEM FILES
# ========================================

# macOS
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
.fseventsd
.AppleDouble
.LSOverride

# Windows
Thumbs.db
ehthumbs.db
Desktop.ini
$RECYCLE.BIN/
*.lnk

# Linux
*~
.nfs*
```

### Step 10: Testing e Coverage
```gitignore
# ========================================
# TESTING & QUALITY ASSURANCE
# ========================================

# Test coverage
coverage/
.nyc_output
htmlcov/
.coverage
.coverage.*

# Test results
test-results/
junit.xml
.pytest_cache/

# End-to-end testing
/test-results/
/playwright-report/
/playwright/.cache/

# Performance testing
lighthouse-reports/
```

## 🔧 File .gitignore Completo

<details>
<summary>📄 Visualizza .gitignore completo</summary>

```gitignore
# ========================================
# WEB PROJECT GITIGNORE
# Project: React + Node.js + MongoDB
# Created: 2024
# ========================================

# ========================================
# DEPENDENCIES - Package Managers
# ========================================

# Node.js dependencies
**/node_modules/
node_modules/

# Package manager files
npm-debug.log*
yarn-debug.log*
yarn-error.log*
.yarn/
.pnp.*
.npm
.pnpm-debug.log*

# ========================================
# ENVIRONMENT & SECRETS - CRITICAL!
# ========================================

# Environment files
.env
.env.local
.env.development
.env.staging
.env.production
.env.test

# Database credentials
config/database.yml
config/secrets.yml

# SSL/TLS certificates
*.pem
*.key
*.crt
*.p12

# API keys
**/secrets/
api-keys.json

# ========================================
# BUILD OUTPUTS & GENERATED FILES
# ========================================

# Frontend builds
frontend/build/
frontend/dist/
frontend/.next/
frontend/out/

# Backend builds
backend/build/
backend/dist/

# Bundler outputs
*.bundle.js
*.bundle.css

# Static site generators
.nuxt/
.vuepress/dist

# ========================================
# DATABASE & USER CONTENT
# ========================================

# Local database
database/local_data/
*.sqlite
*.sqlite3
*.db
*.sql
*.dump

# User uploads
backend/uploads/
**/uploads/
public/uploads/
media/

# ========================================
# CACHE & TEMPORARY FILES
# ========================================

# Build cache
.cache/
.parcel-cache/
.eslintcache
.stylelintcache

# Testing cache
.jest/
.pytest_cache/

# General temp
tmp/
temp/
*.tmp
*.temp

# Logs
*.log
logs/

# ========================================
# DEVELOPMENT TOOLS
# ========================================

# IDE
.vscode/
!.vscode/settings.json.example
.idea/
*.iml

# Editors
*.swp
*.swo
*~

# ========================================
# OPERATING SYSTEM
# ========================================

# macOS
.DS_Store
._*
.Spotlight-V100
.Trashes

# Windows
Thumbs.db
Desktop.ini
$RECYCLE.BIN/

# Linux
*~
.nfs*

# ========================================
# TESTING & QA
# ========================================

# Coverage reports
coverage/
.nyc_output
htmlcov/
.coverage

# Test results
test-results/
junit.xml

# E2E testing
/playwright-report/
/playwright/.cache/

# ========================================
# PROJECT SPECIFIC
# ========================================

# Documentation builds
docs/build/
docs/_build/

# Deployment
deploy/
.deployment

# Backup files
*.backup
*.bak
```
</details>

## 🧪 Test della Configurazione

### Crea File di Test
```bash
# Crea file che dovrebbero essere ignorati
$ touch .env
$ mkdir -p frontend/node_modules backend/build
$ touch frontend/node_modules/react.js
$ touch backend/build/server.js
$ touch backend/uploads/photo.jpg
$ touch .DS_Store
$ echo "SECRET=password123" > .env

# Crea file che dovrebbero essere tracciati
$ echo "console.log('frontend');" > frontend/src/index.js
$ echo "console.log('backend');" > backend/src/server.js
$ echo "# My Web App" > README.md
```

### Verifica Funzionamento
```bash
# Verifica cosa vede Git
$ git status
On branch main

Untracked files:
  (use "git add <file>..." to include in what will be committed)
    .gitignore
    README.md
    backend/src/
    docker-compose.yml
    frontend/src/

# ✅ Perfetto! I file sensibili non compaiono

# Verifica file ignorati
$ git status --ignored
Ignored files:
  .DS_Store
  .env
  backend/build/
  backend/uploads/
  frontend/node_modules/
```

### Debug Pattern Specifici
```bash
# Testa pattern specifici
$ git check-ignore -v .env
.gitignore:26:.env    .env

$ git check-ignore -v frontend/node_modules/react.js
.gitignore:15:**/node_modules/    frontend/node_modules/react.js

$ git check-ignore -v backend/uploads/photo.jpg
.gitignore:65:**/uploads/    backend/uploads/photo.jpg
```

## 📋 Script di Verifica Automatica

### Script di Test
```bash
#!/bin/bash
# File: test-gitignore.sh

echo "🧪 Test Configurazione .gitignore"
echo "================================="

# Crea file di test
mkdir -p test-files/{frontend,backend}/{src,build,node_modules,uploads}
touch test-files/.env
touch test-files/frontend/node_modules/react.js
touch test-files/backend/build/server.js
touch test-files/backend/uploads/image.jpg
touch test-files/.DS_Store

# Test ignoramento
IGNORED_FILES=(
    "test-files/.env"
    "test-files/frontend/node_modules/react.js"
    "test-files/backend/build/server.js"
    "test-files/backend/uploads/image.jpg"
    "test-files/.DS_Store"
)

echo "🔍 Verifica file che dovrebbero essere ignorati:"
for file in "${IGNORED_FILES[@]}"; do
    if git check-ignore "$file" >/dev/null 2>&1; then
        echo "✅ $file - IGNORATO"
    else
        echo "❌ $file - NON IGNORATO"
    fi
done

# Cleanup
rm -rf test-files

echo ""
echo "📊 Statistiche:"
echo "Pattern attivi: $(grep -v '^#' .gitignore | grep -v '^$' | wc -l)"
echo "File tracciati: $(git ls-files | wc -l)"
```

## 💡 Best Practices Applicate

### 1. **Organizzazione Logica**
- ✅ Sezioni chiaramente separate
- ✅ Commenti descrittivi
- ✅ Raggruppamento per tipo

### 2. **Sicurezza**
- ✅ File `.env` completamente ignorati
- ✅ Credenziali database protette
- ✅ Certificati SSL esclusi

### 3. **Performance**
- ✅ `node_modules` ignorato
- ✅ File di build esclusi
- ✅ Cache non tracciata

### 4. **Collaborazione**
- ✅ File IDE gestiti correttamente
- ✅ File OS esclusi
- ✅ Pattern universali

## 🚀 Evoluzione del .gitignore

### Fase 1: Progetto Nuovo
```gitignore
# Minimal setup
node_modules/
.env
build/
.DS_Store
```

### Fase 2: Sviluppo Attivo
```gitignore
# Aggiungi mentre sviluppi
node_modules/
.env
build/
dist/
coverage/
*.log
.DS_Store
```

### Fase 3: Produzione
```gitignore
# Configurazione completa
# (Quello che abbiamo creato sopra)
```

## 🔗 Prossimi Passi

1. **Personalizza** per il tuo stack specifico
2. **Testa** con file reali del progetto  
3. **Condividi** il template con il team
4. **Mantieni** aggiornato durante lo sviluppo

---

**Prossimo:** [Progetto Node.js](./02-progetto-nodejs.md) per configurazioni backend specifiche!
