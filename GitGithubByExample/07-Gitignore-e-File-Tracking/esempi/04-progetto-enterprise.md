# Esempio 04: Gestione .gitignore per Progetto Multi-Stack Enterprise

> **Scenario**: Configurazione .gitignore complessa per applicazione enterprise con frontend React, backend Node.js, database, Docker e CI/CD  
> **Complessità**: ⭐⭐⭐⭐ (Avanzato)  
> **Tempo**: 40-60 minuti  

## 📖 Descrizione

Questo esempio mostra come configurare un .gitignore sofisticato per un progetto enterprise complesso che include:
- Frontend React/TypeScript
- Backend Node.js/Express
- Database (PostgreSQL, Redis)
- Containerizzazione Docker
- CI/CD con GitHub Actions
- Monitoring e logging
- Documentazione e testing

## 🎯 Obiettivi

- ✅ Configurare .gitignore per architetture multi-stack
- ✅ Gestire file sensibili e configurazioni ambiente
- ✅ Ottimizzare per team di sviluppo enterprise
- ✅ Implementare strategie di sicurezza per repository
- ✅ Configurare per pipeline CI/CD

## 🏗️ Setup del Progetto Enterprise

### 1. Struttura del Progetto

```bash
# Crea la directory principale
mkdir enterprise-multistack-project
cd enterprise-multistack-project

# Inizializza Git
git init

# Crea la struttura enterprise completa
mkdir -p {frontend,backend,database,infrastructure,docs,tools,tests}
mkdir -p frontend/{src,public,build,node_modules}
mkdir -p frontend/src/{components,pages,hooks,utils,assets,styles}
mkdir -p backend/{src,dist,node_modules,logs}
mkdir -p backend/src/{controllers,services,models,middleware,utils,config}
mkdir -p database/{migrations,seeds,backups,scripts}
mkdir -p infrastructure/{docker,kubernetes,terraform,ansible}
mkdir -p docs/{api,architecture,deployment,user-guides}
mkdir -p tools/{scripts,configs,monitoring}
mkdir -p tests/{unit,integration,e2e,performance}

# Strutture specifiche per ambienti
mkdir -p config/{development,staging,production}
mkdir -p logs/{application,access,error,audit}
mkdir -p temp/{uploads,exports,cache}
mkdir -p artifacts/{builds,releases,reports}

echo "✅ Enterprise project structure created"
```

### 2. File di Configurazione Base

```bash
# Package.json per frontend
cat > frontend/package.json << 'EOF'
{
  "name": "enterprise-frontend",
  "version": "1.0.0",
  "private": true,
  "dependencies": {
    "react": "^18.2.0",
    "typescript": "^4.9.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test"
  }
}
EOF

# Package.json per backend
cat > backend/package.json << 'EOF'
{
  "name": "enterprise-backend",
  "version": "1.0.0",
  "main": "dist/index.js",
  "dependencies": {
    "express": "^4.18.0",
    "typescript": "^4.9.0"
  },
  "scripts": {
    "start": "node dist/index.js",
    "build": "tsc",
    "dev": "ts-node src/index.ts"
  }
}
EOF

# File di configurazione vari
cat > config/development/database.env << 'EOF'
DB_HOST=localhost
DB_PORT=5432
DB_NAME=enterprise_dev
DB_USER=dev_user
DB_PASSWORD=dev_password_123
REDIS_URL=redis://localhost:6379
EOF

cat > config/production/app.env << 'EOF'
NODE_ENV=production
PORT=3000
JWT_SECRET=super_secret_production_key
API_KEY=prod_api_key_12345
ENCRYPTION_KEY=prod_encryption_key_67890
EOF

# Docker files
cat > infrastructure/docker/Dockerfile.frontend << 'EOF'
FROM node:18-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .
RUN npm run build
EXPOSE 3000
CMD ["npm", "start"]
EOF

# File temporanei e di build
touch frontend/build/static/js/main.12345.js
touch frontend/build/static/css/main.12345.css
touch backend/dist/index.js
touch backend/logs/application.log
touch logs/access.log
touch temp/upload_12345.tmp

echo "✅ Configuration files created"
```

## 🚫 Configurazione .gitignore Enterprise

### 3. .gitignore Principale Completo

```bash
cat > .gitignore << 'EOF'
# =================================================================
# ENTERPRISE PROJECT .GITIGNORE
# Multi-stack application with React frontend, Node.js backend
# =================================================================

# ===================
# DEPENDENCIES
# ===================

# Node.js dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*
.npm
.yarn-integrity

# Package-lock files (keep only one type)
# Uncomment the one you DON'T use:
# package-lock.json
# yarn.lock

# ===================
# BUILD OUTPUTS
# ===================

# Frontend builds
frontend/build/
frontend/dist/
frontend/.next/
frontend/out/

# Backend builds
backend/dist/
backend/build/
backend/lib/

# General build artifacts
*.tgz
*.tar.gz
artifacts/builds/
artifacts/releases/

# ===================
# ENVIRONMENT & CONFIG
# ===================

# Environment variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local
.env.staging.local

# Sensitive configuration files
config/production/*.env
config/staging/*.env
**/secrets.json
**/private-key.pem
**/ssl-cert.pem

# Database configuration
config/**/database.env
database/backups/*.sql
database/backups/*.dump

# ===================
# CREDENTIALS & SECURITY
# ===================

# API keys and secrets
.secrets/
credentials/
*.key
*.pem
*.p12
*.pfx
*.crt
*.cer
!public.key  # Exception for public keys

# Authentication tokens
.auth-tokens
jwt-secret.txt
oauth-config.json

# ===================
# LOGS & MONITORING
# ===================

# Application logs
logs/
*.log
logs/**/*.log
backend/logs/
frontend/logs/

# Monitoring and metrics
monitoring/data/
metrics/
traces/

# Crash dumps
*.dmp
core.*

# ===================
# TEMPORARY & CACHE
# ===================

# Temporary files
temp/
tmp/
*.tmp
*.temp
.temp/
.cache/

# Cache directories
.next/cache/
.nuxt/
.cache/
.parcel-cache/
.eslintcache
.stylelintcache

# OS temporary files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
desktop.ini

# ===================
# DEVELOPMENT TOOLS
# ===================

# IDE and editors
.vscode/
!.vscode/settings.json
!.vscode/tasks.json
!.vscode/launch.json
!.vscode/extensions.json
.idea/
*.swp
*.swo
*~
.project
.settings/

# Sublime Text
*.sublime-project
*.sublime-workspace

# ===================
# TESTING
# ===================

# Test outputs
coverage/
.nyc_output/
.coverage
htmlcov/
tests/screenshots/
tests/videos/

# Jest
jest.config.local.js

# Cypress
cypress/screenshots/
cypress/videos/
cypress/downloads/

# ===================
# DATABASE
# ===================

# Database files
*.sqlite
*.db
*.db-journal
database/data/
*.mdb
*.accdb

# Database dumps and backups
*.sql.gz
*.dump
database/backups/*.backup
database/local/

# ===================
# CONTAINERIZATION
# ===================

# Docker
.dockerignore.backup
docker-compose.override.yml
.docker/

# Kubernetes secrets
infrastructure/kubernetes/secrets/
k8s-secrets/

# ===================
# CLOUD & DEPLOYMENT
# ===================

# Terraform
infrastructure/terraform/.terraform/
infrastructure/terraform/terraform.tfstate
infrastructure/terraform/terraform.tfstate.backup
infrastructure/terraform/*.tfvars
!infrastructure/terraform/*.tfvars.example

# Ansible
infrastructure/ansible/vault_pass.txt
infrastructure/ansible/host_vars/
infrastructure/ansible/group_vars/production/
infrastructure/ansible/group_vars/staging/

# Cloud provider configs
.aws/
.gcp/
.azure/

# ===================
# CI/CD
# ===================

# Build artifacts from CI
artifacts/ci/
pipeline-cache/
.gitlab-ci-cache/

# Deployment artifacts
deployment/staging/
deployment/production/
!deployment/**/*.example.yml

# ===================
# DOCUMENTATION
# ===================

# Generated documentation
docs/generated/
docs/api/generated/
docs/coverage-report/
docs/build/

# ===================
# ANALYTICS & TRACKING
# ===================

# Analytics data
analytics/data/
tracking/
user-behavior/

# ===================
# BACKUP & ARCHIVE
# ===================

# Backup files
*.backup
*.bak
*.old
backup/
archives/

# ===================
# LARGE FILES & MEDIA
# ===================

# Large data files
*.csv
*.json
data/
datasets/

# Media files (consider Git LFS)
*.mp4
*.avi
*.mov
*.mkv
*.mp3
*.wav
*.flac

# ===================
# PLATFORM SPECIFIC
# ===================

# Windows
*.dll
*.exe
*.msi

# macOS
.AppleDouble
.LSOverride
Icon

# Linux
*.AppImage
*.deb
*.rpm

# ===================
# CUSTOM PROJECT SPECIFIC
# ===================

# Project-specific temporary files
scratch/
sandbox/
playground/
experiments/

# Third-party integrations data
integrations/data/
webhooks/logs/

# Performance testing data
performance/results/
load-test-results/

# Security scan results
security-reports/
vulnerability-scans/

# ===================
# EXCEPTIONS (Keep these files)
# ===================

# Keep important example files
!**/*.example
!**/*.template
!**/*.sample

# Keep important configuration templates
!config/**/*.example.env
!infrastructure/**/*.example.yml
!docker-compose.example.yml

# Keep documentation assets
!docs/images/
!docs/diagrams/

# Keep essential scripts
!tools/scripts/setup.sh
!tools/scripts/install.sh
EOF

echo "✅ Comprehensive .gitignore created"
```

### 4. .gitignore Specifici per Sottodirectory

```bash
# Frontend-specific .gitignore
cat > frontend/.gitignore << 'EOF'
# Frontend-specific ignores

# Production build
/build
/dist

# Development
.env.development.local
.env.local

# Editor directories and files
.vscode/*
!.vscode/settings.json
!.vscode/tasks.json
!.vscode/launch.json
!.vscode/extensions.json

# Temporary folders
.tmp/
.sass-cache/
.connect.lock
.typings/

# System Files
.DS_Store
Thumbs.db

# Runtime data
pids
*.pid
*.seed
*.pid.lock

# Coverage directory used by tools like istanbul
coverage/
.nyc_output/

# Storybook build outputs
.out
.storybook-out

# Temporary folders
.tmp/

# Editor directories and files
.history/
EOF

# Backend-specific .gitignore
cat > backend/.gitignore << 'EOF'
# Backend-specific ignores

# Compiled output
/dist
/build
/lib

# Logs
logs
*.log
npm-debug.log*
pnpm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# Runtime data
pids
*.pid
*.seed
*.pid.lock

# Coverage directory used by tools like istanbul
coverage
*.lcov

# nyc test coverage
.nyc_output

# node-waf configuration
.lock-wscript

# Compiled binary addons (https://nodejs.org/api/addons.html)
build/Release

# Dependency directories
node_modules/
jspm_packages/

# TypeScript cache
*.tsbuildinfo

# Optional npm cache directory
.npm

# Optional eslint cache
.eslintcache

# Microbundle cache
.rpt2_cache/
.rts2_cache_cjs/
.rts2_cache_es/
.rts2_cache_umd/

# Optional REPL history
.node_repl_history

# Output of 'npm pack'
*.tgz

# Yarn Integrity file
.yarn-integrity

# parcel-bundler cache (https://parceljs.org/)
.cache
.parcel-cache

# Next.js build output
.next

# Nuxt.js build / generate output
.nuxt
dist

# Stores VSCode versions used for testing VSCode extensions
.vscode-test

# Application-specific
uploads/
temp/
sessions/
EOF

# Database-specific .gitignore
cat > database/.gitignore << 'EOF'
# Database-specific ignores

# Database files
*.sqlite
*.sqlite3
*.db
*.db-wal
*.db-shm

# Backup files
*.backup
*.bak
*.sql.gz
backups/*.sql
backups/*.dump

# Local database data
data/
local/

# Migration logs
migration.log
seed.log

# Database connection files
connection-local.json
database-config-local.json
EOF

echo "✅ Directory-specific .gitignore files created"
```

## 🔧 Configurazione Avanzata

### 5. File .gitattributes per Gestione Avanzata

```bash
cat > .gitattributes << 'EOF'
# =================================================================
# .GITATTRIBUTES - Advanced file handling configuration
# =================================================================

# ===================
# TEXT FILES
# ===================

# Source code
*.js text eol=lf
*.jsx text eol=lf
*.ts text eol=lf
*.tsx text eol=lf
*.css text eol=lf
*.scss text eol=lf
*.sass text eol=lf
*.html text eol=lf
*.xml text eol=lf
*.json text eol=lf
*.yml text eol=lf
*.yaml text eol=lf

# Documentation
*.md text eol=lf
*.txt text eol=lf
*.rst text eol=lf

# Configuration files
*.conf text eol=lf
*.config text eol=lf
*.ini text eol=lf
*.env text eol=lf

# Shell scripts
*.sh text eol=lf
*.bash text eol=lf
*.zsh text eol=lf

# Batch files
*.bat text eol=crlf
*.cmd text eol=crlf
*.ps1 text eol=crlf

# ===================
# BINARY FILES
# ===================

# Images
*.jpg binary
*.jpeg binary
*.png binary
*.gif binary
*.ico binary
*.svg binary
*.webp binary

# Fonts
*.woff binary
*.woff2 binary
*.eot binary
*.ttf binary
*.otf binary

# Archives
*.zip binary
*.tar binary
*.gz binary
*.rar binary
*.7z binary

# Executables
*.exe binary
*.dll binary
*.so binary
*.dylib binary

# ===================
# LANGUAGE-SPECIFIC DIFFS
# ===================

# JavaScript/TypeScript
*.js diff=javascript
*.jsx diff=javascript
*.ts diff=typescript
*.tsx diff=typescript

# CSS
*.css diff=css
*.scss diff=css
*.sass diff=css

# HTML
*.html diff=html
*.htm diff=html

# JSON
*.json diff=json

# Python
*.py diff=python

# ===================
# SECURITY SENSITIVE FILES
# ===================

# Environment files
*.env filter=clean
config/production/*.env filter=clean
config/staging/*.env filter=clean

# Key files
*.key filter=clean
*.pem filter=clean
private-key.* filter=clean

# ===================
# EXPORT CONTROL
# ===================

# Exclude from exports
.gitignore export-ignore
.gitattributes export-ignore
*.md export-ignore
docs/ export-ignore
tests/ export-ignore
.github/ export-ignore
.vscode/ export-ignore

# ===================
# MERGE STRATEGIES
# ===================

# Don't merge these files, always use ours
package-lock.json merge=ours
yarn.lock merge=ours

# Database migration files - manual merge only
database/migrations/* merge=manual

# Configuration files - manual merge
config/production/* merge=manual
EOF

echo "✅ Advanced .gitattributes configuration created"
```

### 6. Script di Validazione .gitignore

```bash
# Script per validare e testare .gitignore
cat > tools/scripts/gitignore-validator.sh << 'EOF'
#!/bin/bash

# .gitignore Validator Script

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log() { echo -e "${GREEN}[$(date +'%H:%M:%S')]${NC} $1"; }
warn() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
error() { echo -e "${RED}[ERROR]${NC} $1"; }

# Test function
test_gitignore() {
    local test_file="$1"
    local should_ignore="$2"
    
    if [ "$should_ignore" = "true" ]; then
        if git check-ignore "$test_file" >/dev/null 2>&1; then
            echo "✅ PASS: $test_file is correctly ignored"
        else
            echo "❌ FAIL: $test_file should be ignored but isn't"
            return 1
        fi
    else
        if git check-ignore "$test_file" >/dev/null 2>&1; then
            echo "❌ FAIL: $test_file should NOT be ignored but is"
            return 1
        else
            echo "✅ PASS: $test_file is correctly tracked"
        fi
    fi
}

log "🧪 Starting .gitignore validation..."

# Test cases for files that SHOULD be ignored
log "Testing files that should be ignored..."
test_gitignore "node_modules/package.json" true
test_gitignore "frontend/build/index.html" true
test_gitignore "backend/dist/index.js" true
test_gitignore ".env" true
test_gitignore "config/production/database.env" true
test_gitignore "logs/application.log" true
test_gitignore "temp/upload.tmp" true
test_gitignore ".DS_Store" true
test_gitignore "coverage/lcov.info" true

# Test cases for files that should NOT be ignored
log "Testing files that should be tracked..."
test_gitignore "package.json" false
test_gitignore "src/index.js" false
test_gitignore "README.md" false
test_gitignore "config/development/app.example.env" false
test_gitignore ".gitignore" false
test_gitignore "docs/api/endpoints.md" false

# Check for sensitive files that might be tracked
log "🔒 Checking for sensitive files..."
sensitive_patterns=(
    "*.env"
    "*.key"
    "*.pem"
    "*password*"
    "*secret*"
    "*credential*"
)

for pattern in "${sensitive_patterns[@]}"; do
    files=$(git ls-files | grep -i "$pattern" || true)
    if [ -n "$files" ]; then
        warn "Potentially sensitive files found in repository:"
        echo "$files" | while read -r file; do
            warn "  $file"
        done
    fi
done

# Check for large files
log "📊 Checking for large files..."
large_files=$(git ls-files | xargs -I {} find {} -size +10M 2>/dev/null || true)
if [ -n "$large_files" ]; then
    warn "Large files found (consider Git LFS):"
    echo "$large_files" | while read -r file; do
        size=$(du -h "$file" | cut -f1)
        warn "  $file ($size)"
    done
fi

# Generate report
log "📋 Generating .gitignore report..."
cat > gitignore-report.md << 'REPORT_EOF'
# .gitignore Validation Report

Generated: $(date)

## Summary
- Total ignored patterns: $(grep -v '^#' .gitignore | grep -v '^$' | wc -l)
- Total tracked files: $(git ls-files | wc -l)
- Repository size: $(du -sh .git | cut -f1)

## Categories Covered
- ✅ Dependencies (node_modules, package-lock.json)
- ✅ Build outputs (dist/, build/)
- ✅ Environment files (.env, config/)
- ✅ Logs and temporary files
- ✅ IDE and editor files
- ✅ OS-specific files
- ✅ Security-sensitive files
- ✅ CI/CD artifacts
- ✅ Database files and backups

## Recommendations
1. Review sensitive file patterns regularly
2. Consider Git LFS for large binary files
3. Update .gitignore when adding new tools
4. Test .gitignore with team members
REPORT_EOF

log "✅ Validation completed. Report saved to gitignore-report.md"
EOF

chmod +x tools/scripts/gitignore-validator.sh

echo "✅ .gitignore validator script created"
```

## 🧪 Test e Validazione

### 7. Test della Configurazione

```bash
echo "🧪 Testing .gitignore configuration..."

# Aggiunge tutti i file al repository
git add .

# Mostra lo status per verificare cosa viene tracciato
echo "📋 Repository status after adding files:"
git status --short

# Esegui il validator
echo -e "\n🔍 Running .gitignore validator:"
./tools/scripts/gitignore-validator.sh

# Test specifici per verificare che file sensibili siano ignorati
echo -e "\n🔒 Testing sensitive file handling:"

# Crea file sensibili di test
echo "db_password=super_secret" > .env.test
echo "api_key=secret_key_123" > config/production/secrets.env
echo "private_key_data" > backend/private-key.pem

# Verifica che siano ignorati
if git check-ignore .env.test >/dev/null 2>&1; then
    echo "✅ .env.test correctly ignored"
else
    echo "❌ .env.test should be ignored!"
fi

if git check-ignore config/production/secrets.env >/dev/null 2>&1; then
    echo "✅ Production secrets correctly ignored"
else
    echo "❌ Production secrets should be ignored!"
fi

# Cleanup test files
rm -f .env.test config/production/secrets.env backend/private-key.pem

echo "✅ Testing completed"
```

### 8. Commit della Configurazione

```bash
echo "💾 Committing enterprise .gitignore configuration..."

# Commit iniziale con la configurazione completa
git commit -m "feat: implement comprehensive enterprise .gitignore

Features implemented:
- Multi-stack support (React frontend, Node.js backend)
- Environment-specific file handling
- Security-sensitive file protection
- CI/CD artifact exclusion
- Database and backup file management
- IDE and editor configuration
- Performance optimization (cache, logs, temp files)

Categories covered:
- Dependencies and package managers
- Build outputs and artifacts
- Environment variables and configuration
- Credentials and security files
- Logs and monitoring data
- Temporary and cache files
- Development tools and IDEs
- Testing outputs and coverage
- Database files and backups
- Containerization files
- Cloud and deployment configs
- Documentation and media files

Additional features:
- Directory-specific .gitignore files
- Advanced .gitattributes configuration
- Validation script for testing
- Security checks for sensitive files
- Performance considerations"

# Crea tag per la configurazione
git tag -a v1.0.0-gitignore -m "Enterprise .gitignore configuration v1.0.0

Complete .gitignore setup for multi-stack enterprise applications
with security, performance, and team collaboration considerations."

echo "✅ Enterprise .gitignore configuration committed and tagged"
```

## 📊 Monitoraggio e Manutenzione

### 9. Script di Manutenzione

```bash
# Script per mantenere .gitignore aggiornato
cat > tools/scripts/gitignore-maintenance.sh << 'EOF'
#!/bin/bash

# .gitignore Maintenance Script

log() { echo -e "\033[0;32m[$(date +'%H:%M:%S')]\033[0m $1"; }

# Update .gitignore with new patterns
update_patterns() {
    log "🔄 Checking for new ignore patterns..."
    
    # Check for new node_modules patterns
    if [ -f package.json ]; then
        log "📦 Node.js project detected"
        
        # Check for new dependency directories
        if [ -d ".pnpm-store" ] && ! grep -q ".pnpm-store" .gitignore; then
            echo ".pnpm-store/" >> .gitignore
            log "➕ Added .pnpm-store/ to .gitignore"
        fi
        
        if [ -d ".yarn" ] && ! grep -q ".yarn" .gitignore; then
            echo ".yarn/" >> .gitignore
            log "➕ Added .yarn/ to .gitignore"
        fi
    fi
    
    # Check for new IDE files
    for ide_dir in .fleet .nova .vim; do
        if [ -d "$ide_dir" ] && ! grep -q "$ide_dir" .gitignore; then
            echo "$ide_dir/" >> .gitignore
            log "➕ Added $ide_dir/ to .gitignore"
        fi
    done
}

# Clean up ignored files that might be tracked
cleanup_tracked_ignored() {
    log "🧹 Cleaning up tracked files that should be ignored..."
    
    # Find tracked files that should be ignored
    tracked_ignored=$(git ls-files -i --exclude-standard)
    
    if [ -n "$tracked_ignored" ]; then
        log "Found tracked files that should be ignored:"
        echo "$tracked_ignored" | while read -r file; do
            log "  🗑️  $file"
            git rm --cached "$file" 2>/dev/null || true
        done
    else
        log "✅ No tracked files found that should be ignored"
    fi
}

# Generate usage statistics
generate_stats() {
    log "📊 Generating .gitignore statistics..."
    
    total_patterns=$(grep -v '^#' .gitignore | grep -v '^$' | wc -l)
    total_files=$(git ls-files | wc -l)
    ignored_files=$(git status --ignored --porcelain | grep '^!!' | wc -l)
    
    cat > .gitignore-stats.md << STATS_EOF
# .gitignore Statistics

Generated: $(date)

## Overview
- Total ignore patterns: $total_patterns
- Total tracked files: $total_files  
- Currently ignored files: $ignored_files

## Pattern Categories
- Dependencies: $(grep -c "node_modules\|\.npm\|yarn" .gitignore || echo 0)
- Build outputs: $(grep -c "build\|dist\|out" .gitignore || echo 0)
- Environment: $(grep -c "\.env\|config.*env" .gitignore || echo 0)
- Logs: $(grep -c "\.log\|logs" .gitignore || echo 0)
- IDE: $(grep -c "\.vscode\|\.idea\|\.sublime" .gitignore || echo 0)
- OS files: $(grep -c "\.DS_Store\|Thumbs\.db" .gitignore || echo 0)

## Recent Updates
Last modified: $(git log -1 --format="%cd" -- .gitignore)
STATS_EOF
    
    log "✅ Statistics saved to .gitignore-stats.md"
}

case "${1:-all}" in
    "update")
        update_patterns
        ;;
    "cleanup")
        cleanup_tracked_ignored
        ;;
    "stats")
        generate_stats
        ;;
    "all")
        update_patterns
        cleanup_tracked_ignored
        generate_stats
        ;;
    *)
        echo "Usage: $0 {update|cleanup|stats|all}"
        ;;
esac
EOF

chmod +x tools/scripts/gitignore-maintenance.sh

# Test dello script di manutenzione
echo "🔧 Testing maintenance script:"
./tools/scripts/gitignore-maintenance.sh all

echo "✅ Maintenance script created and tested"
```

## 🎯 Risultati e Best Practices

### Configurazione Finale

La configurazione enterprise .gitignore include:

1. **Copertura Completa**: Tutti i tipi di file per stack moderni
2. **Sicurezza**: Protezione automatica di file sensibili
3. **Performance**: Esclusione di file che rallentano Git
4. **Team Collaboration**: Configurazioni condivise ma flessibili
5. **Manutenibilità**: Script per aggiornamenti automatici

### Pattern Chiave Implementati

- **Dependencies**: `node_modules/`, `.npm`, `yarn.lock`
- **Build Outputs**: `dist/`, `build/`, `artifacts/`
- **Environment**: `.env*`, `config/production/`
- **Security**: `*.key`, `*.pem`, `credentials/`
- **Logs**: `logs/`, `*.log`, `monitoring/`
- **Cache**: `.cache/`, `temp/`, `.tmp/`

## 💡 Lezioni Apprese

### Best Practices Enterprise

1. **Layered Approach**: .gitignore globale + directory-specific
2. **Security First**: Sempre escludere file sensibili per default
3. **Performance Consideration**: Escludere file grandi e cache
4. **Team Compatibility**: Considerare tutti gli IDE e OS del team
5. **Automation**: Script per validazione e manutenzione

### Strategie Avanzate

- **Environment Separation**: Pattern diversi per ambienti diversi
- **CI/CD Integration**: Considerare artifact e cache della pipeline
- **Documentation**: Commenti chiari per pattern complessi
- **Validation**: Test automatici per verificare la configurazione

---

> **Nota**: Questa configurazione rappresenta best practices enterprise per progetti multi-stack. Adatta i pattern alle specifiche esigenze del tuo progetto e team.
