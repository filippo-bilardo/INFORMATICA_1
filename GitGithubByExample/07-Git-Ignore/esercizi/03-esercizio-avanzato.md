# Esercizio 3: Sicurezza e Best Practices Avanzate

## Obiettivo
Implementare una strategia completa di sicurezza per .gitignore, inclusa la gestione di file sensibili già committati, audit di sicurezza, automazione con pre-commit hooks, e strategie per team enterprise. Questo esercizio copre scenari reali di produzione.

## Prerequisiti
- Completamento degli Esercizi 1 e 2
- Conoscenza avanzata di Git
- Comprensione di sicurezza informatica base
- Familiarità con CI/CD e automazione

## Scenario Enterprise
Lavori per un'azienda che ha:
- **30+ sviluppatori** in team distribuiti
- **Progetti legacy** con potenziali problemi di sicurezza
- **Compliance requirements** (GDPR, SOX)
- **Multi-cloud deployment** (AWS, Azure, GCP)
- **Microservizi** con tecnologie diverse
- **CI/CD pipelines** automatizzate

Devi implementare una strategia di sicurezza completa che previene, rileva e corregge problemi di sicurezza relativi ai file committati.

## Parte 1: Audit di Sicurezza del Repository

### Passo 1: Setup Scenario Problematico
```bash
# Crea un repository con problemi di sicurezza (simulazione)
mkdir security-audit-exercise
cd security-audit-exercise
git init

# Simula storia problematica
echo "Initial commit" > README.md
git add README.md
git commit -m "Initial commit"

# Commit problematici (da NON fare in realtà!)
echo "AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE" > .env
echo "AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYzEXAMPLEKEY" >> .env
echo "DATABASE_PASSWORD=super_secret_password123" >> .env
echo "API_KEY=sk_live_51H7xPXXXXXXXXXXXX" >> .env
git add .env
git commit -m "Add configuration"

# Commit di certificati
openssl req -x509 -newkey rsa:2048 -keyout private.key -out certificate.crt -days 365 -nodes -subj "/CN=example.com"
git add private.key certificate.crt
git commit -m "Add SSL certificates"

# Commit di backup database
echo "-- Database backup with sensitive data" > backup.sql
echo "INSERT INTO users (email, password) VALUES ('admin@company.com', 'hashed_password');" >> backup.sql
git add backup.sql
git commit -m "Add database backup"

# Commit di logs con PII
echo "2024-01-15 10:30:00 INFO User login: john.doe@company.com from IP 192.168.1.100" > app.log
echo "2024-01-15 10:31:00 ERROR Credit card validation failed for card 4532-1234-5678-9012" >> app.log
git add app.log
git commit -m "Add application logs"

# Altri file problematici
echo "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQ..." > ~/.ssh/id_rsa.pub
cp ~/.ssh/id_rsa.pub ./deploy_key.pub
git add deploy_key.pub
git commit -m "Add deployment key"

# File di configurazione IDE con path sensibili
mkdir -p .vscode
echo '{"python.defaultInterpreter": "/home/john.doe/secret-project/venv/bin/python"}' > .vscode/settings.json
git add .vscode/settings.json
git commit -m "Add VS Code settings"
```

### Passo 2: Script di Audit Automatico
```bash
cat > security-audit.sh << 'EOF'
#!/bin/bash

set -e

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

ISSUES_FOUND=0
CRITICAL_ISSUES=0

log_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

log_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

log_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
    ISSUES_FOUND=$((ISSUES_FOUND + 1))
}

log_critical() {
    echo -e "${RED}🚨 CRITICAL: $1${NC}"
    CRITICAL_ISSUES=$((CRITICAL_ISSUES + 1))
    ISSUES_FOUND=$((ISSUES_FOUND + 1))
}

echo "🔍 Starting security audit of Git repository..."
echo "Repository: $(pwd)"
echo "Date: $(date)"
echo "==========================================="

# 1. Scan for secrets in current files
log_info "Scanning current files for secrets..."

# AWS Keys
if grep -r "AKIA[0-9A-Z]{16}" . --exclude-dir=.git 2>/dev/null; then
    log_critical "AWS Access Key found in current files"
fi

# Secret patterns
SECRET_PATTERNS=(
    "password.*=.*['\"][^'\"]{8,}['\"]"
    "api[_-]?key.*=.*['\"][^'\"]{16,}['\"]"
    "secret.*=.*['\"][^'\"]{16,}['\"]"
    "token.*=.*['\"][^'\"]{16,}['\"]"
    "private[_-]?key"
    "-----BEGIN.*PRIVATE KEY-----"
    "sk_live_[0-9a-zA-Z]{24,}"
    "pk_live_[0-9a-zA-Z]{24,}"
)

for pattern in "${SECRET_PATTERNS[@]}"; do
    if grep -r -E "$pattern" . --exclude-dir=.git 2>/dev/null; then
        log_critical "Potential secret found matching pattern: $pattern"
    fi
done

# 2. Scan Git history for secrets
log_info "Scanning Git history for secrets..."

# Usa git log per cercare pattern sospetti nei commit
git log --all --full-history --source -- "*" | grep -E "(password|secret|key|token)" && log_warning "Suspicious keywords found in commit history"

# 3. Check for large files
log_info "Checking for large files..."
git rev-list --objects --all | 
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' |
awk '/^blob/ { if ($3 > 1048576) print $3/1048576 "MB", $4 }' |
sort -n | while read size file; do
    if [[ ! -z "$file" ]]; then
        log_warning "Large file found: $file ($size)"
    fi
done

# 4. Check for binary files that might contain secrets
log_info "Checking for suspicious binary files..."
find . -name "*.p12" -o -name "*.pfx" -o -name "*.jks" -o -name "*.keystore" | while read file; do
    if [[ ! -z "$file" ]]; then
        log_warning "Certificate/keystore file found: $file"
    fi
done

# 5. Check .gitignore effectiveness
log_info "Checking .gitignore effectiveness..."

if [[ ! -f ".gitignore" ]]; then
    log_critical ".gitignore file not found!"
else
    # Test common sensitive file patterns
    if ! grep -q "\.env" .gitignore; then
        log_warning ".env files not ignored"
    fi
    
    if ! grep -q "\.key" .gitignore; then
        log_warning ".key files not ignored"
    fi
    
    if ! grep -q "\.pem" .gitignore; then
        log_warning ".pem files not ignored"
    fi
    
    if ! grep -q "\.log" .gitignore; then
        log_warning ".log files not ignored"
    fi
fi

# 6. Check for exposed configuration files
log_info "Checking for exposed configuration files..."

CONFIG_FILES=(
    ".env"
    "config.json"
    "secrets.yml"
    "database.yml"
    "aws.json"
    "google-cloud.json"
    "azure.json"
)

for file in "${CONFIG_FILES[@]}"; do
    if [[ -f "$file" ]] && git ls-files --error-unmatch "$file" >/dev/null 2>&1; then
        log_critical "Configuration file '$file' is tracked by Git"
    fi
done

# 7. Generate report
echo ""
echo "==========================================="
echo "📊 SECURITY AUDIT REPORT"
echo "==========================================="
echo "Issues found: $ISSUES_FOUND"
echo "Critical issues: $CRITICAL_ISSUES"

if [[ $CRITICAL_ISSUES -gt 0 ]]; then
    echo -e "${RED}🚨 CRITICAL ISSUES FOUND! Immediate action required.${NC}"
    exit 1
elif [[ $ISSUES_FOUND -gt 0 ]]; then
    echo -e "${YELLOW}⚠️ Issues found. Review and fix.${NC}"
    exit 1
else
    echo -e "${GREEN}✅ No security issues found.${NC}"
    exit 0
fi
EOF

chmod +x security-audit.sh
```

### Passo 3: Esecuzione Audit
```bash
# Esegui l'audit per vedere i problemi
./security-audit.sh

# Dovrebbe trovare tutti i problemi che abbiamo introdotto
```

## Parte 2: Rimozione Sicura di File Sensibili dalla Storia

### Passo 1: Identificazione File da Rimuovere
```bash
# Script per identificare tutti i file sensibili nella storia
cat > find-sensitive-files.sh << 'EOF'
#!/bin/bash

echo "🔍 Scanning Git history for sensitive files..."

# Cerca file con estensioni sensibili
git log --name-only --pretty=format: --all | grep -E "\.(env|key|pem|p12|pfx|jks|keystore)$" | sort -u

# Cerca file con nomi sospetti
git log --name-only --pretty=format: --all | grep -E "(secret|password|credential|backup\.sql|\.log)$" | sort -u

# Cerca contenuto sensibile nei commit
echo -e "\n🔍 Commits that might contain secrets:"
git log --grep="password\|secret\|key\|credential" --oneline --all
EOF

chmod +x find-sensitive-files.sh
./find-sensitive-files.sh
```

### Passo 2: Strategia di Rimozione con git filter-repo
```bash
# Installa git-filter-repo se non disponibile
# pip install git-filter-repo

# Script di pulizia completa
cat > clean-repository.sh << 'EOF'
#!/bin/bash

set -e

echo "🧹 Starting repository cleanup..."

# ATTENZIONE: Questo script riscrive la storia di Git!
# Crea sempre un backup prima di eseguire

# 1. Backup del repository
echo "📦 Creating backup..."
cd ..
cp -r security-audit-exercise security-audit-exercise-backup
cd security-audit-exercise

# 2. Rimuovi file specifici dalla storia
echo "🗑️ Removing sensitive files from history..."

# Lista di file da rimuovere completamente
SENSITIVE_FILES=(
    ".env"
    "private.key"
    "certificate.crt"
    "backup.sql"
    "app.log"
    "deploy_key.pub"
    ".vscode/settings.json"
)

for file in "${SENSITIVE_FILES[@]}"; do
    echo "Removing $file from history..."
    # Usa git filter-branch come alternativa se git-filter-repo non è disponibile
    git filter-branch --force --index-filter \
        "git rm --cached --ignore-unmatch '$file'" \
        --prune-empty --tag-name-filter cat -- --all
done

# 3. Pulizia dei riferimenti
echo "🔧 Cleaning up references..."
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive

# 4. Verifica che i file siano stati rimossi
echo "✅ Verification..."
for file in "${SENSITIVE_FILES[@]}"; do
    if git log --name-only --pretty=format: --all | grep -q "^$file$"; then
        echo "❌ $file still exists in history!"
    else
        echo "✅ $file successfully removed from history"
    fi
done

echo "🎉 Repository cleanup completed!"
echo "⚠️ Remember to force push: git push --force-with-lease origin --all"
EOF

chmod +x clean-repository.sh
```

### Passo 3: Alternativa con BFG Repo-Cleaner
```bash
# Script alternativo usando BFG (più semplice per file grandi)
cat > clean-with-bfg.sh << 'EOF'
#!/bin/bash

# Scarica BFG se non disponibile
if ! command -v bfg &> /dev/null; then
    echo "📦 Downloading BFG Repo-Cleaner..."
    curl -L -o bfg.jar https://repo1.maven.org/maven2/com/madgag/bfg/1.14.0/bfg-1.14.0.jar
    alias bfg="java -jar bfg.jar"
fi

echo "🧹 Cleaning repository with BFG..."

# 1. Crea file con pattern da rimuovere
cat > patterns-to-remove.txt << 'PATTERNS'
.env
*.key
*.pem
*.p12
*.pfx
backup.sql
*.log
PATTERNS

# 2. Rimuovi file per nome
bfg --delete-files "patterns-to-remove.txt" .

# 3. Rimuovi contenuto sensibile per pattern
echo "Removing content patterns..."
bfg --replace-text <(echo "password=*=>password=REMOVED") .
bfg --replace-text <(echo "secret=*=>secret=REMOVED") .
bfg --replace-text <(echo "key=*=>key=REMOVED") .

# 4. Cleanup finale
git reflog expire --expire=now --all && git gc --prune=now --aggressive

echo "✅ BFG cleanup completed!"
rm patterns-to-remove.txt
EOF

chmod +x clean-with-bfg.sh
```

## Parte 3: Implementazione Pre-commit Hooks

### Passo 1: Setup Pre-commit Framework
```bash
# Installa pre-commit
pip install pre-commit

# Crea configurazione pre-commit
cat > .pre-commit-config.yaml << 'EOF'
# Pre-commit configuration for security and quality
repos:
  # Generic security checks
  - repo: https://github.com/pre-commit/pre-commit-hooks
    rev: v4.5.0
    hooks:
      - id: check-yaml
      - id: check-json
      - id: check-xml
      - id: check-toml
      - id: check-added-large-files
        args: ['--maxkb=1000']
      - id: check-merge-conflict
      - id: detect-private-key
      - id: check-case-conflict
      - id: end-of-file-fixer
      - id: trailing-whitespace

  # Security scanning with detect-secrets
  - repo: https://github.com/Yelp/detect-secrets
    rev: v1.4.0
    hooks:
      - id: detect-secrets
        args: ['--baseline', '.secrets.baseline']
        exclude: '(package-lock\.json|\.git/.*|.*\.ipynb)$'

  # Custom security hook
  - repo: local
    hooks:
      - id: security-check
        name: Custom Security Check
        entry: ./hooks/security-check.sh
        language: script
        pass_filenames: false

  # Check for common configuration files
  - repo: local
    hooks:
      - id: check-env-files
        name: Check for .env files
        entry: 'bash -c "if find . -name \".env\" -not -path \"./.git/*\" | grep -q .; then echo \"Error: .env file found\"; exit 1; fi"'
        language: system
        pass_filenames: false

  # Code quality hooks
  - repo: https://github.com/psf/black
    rev: 23.11.0
    hooks:
      - id: black
        language_version: python3

  - repo: https://github.com/pycqa/flake8
    rev: 6.1.0
    hooks:
      - id: flake8

  - repo: https://github.com/pycqa/isort
    rev: 5.12.0
    hooks:
      - id: isort

  # JavaScript/TypeScript
  - repo: https://github.com/pre-commit/mirrors-eslint
    rev: v8.57.0
    hooks:
      - id: eslint
        files: \.(js|jsx|ts|tsx)$
        additional_dependencies: ['eslint@8.57.0']

  # Docker
  - repo: https://github.com/hadolint/hadolint
    rev: v2.12.0
    hooks:
      - id: hadolint
EOF
```

### Passo 2: Hook di Sicurezza Personalizzato
```bash
mkdir -p hooks

cat > hooks/security-check.sh << 'EOF'
#!/bin/bash

# Custom security check hook
set -e

echo "🔐 Running custom security checks..."

FAILED_CHECKS=0

# Check for common secret patterns
SECRET_PATTERNS=(
    "AKIA[0-9A-Z]{16}"                           # AWS Access Key
    "sk_live_[0-9a-zA-Z]+"                       # Stripe Live Key
    "sk_test_[0-9a-zA-Z]+"                       # Stripe Test Key
    "-----BEGIN [A-Z]+ PRIVATE KEY-----"         # Private Keys
    "password\s*=\s*['\"][^'\"]{8,}['\"]"       # Passwords
    "secret\s*=\s*['\"][^'\"]{8,}['\"]"         # Secrets
    "token\s*=\s*['\"][^'\"]{16,}['\"]"         # Tokens
)

# Files to check (staged files)
STAGED_FILES=$(git diff --cached --name-only)

if [ -z "$STAGED_FILES" ]; then
    echo "No staged files to check"
    exit 0
fi

echo "Checking staged files for secrets:"
for file in $STAGED_FILES; do
    if [ -f "$file" ]; then
        echo "  Checking: $file"
        
        for pattern in "${SECRET_PATTERNS[@]}"; do
            if grep -q -E "$pattern" "$file" 2>/dev/null; then
                echo "❌ SECURITY ALERT: Potential secret found in $file"
                echo "   Pattern matched: $pattern"
                FAILED_CHECKS=$((FAILED_CHECKS + 1))
            fi
        done
    fi
done

# Check for forbidden file types
FORBIDDEN_EXTENSIONS=(
    "*.key"
    "*.pem"
    "*.p12"
    "*.pfx"
    "*.keystore"
    "*.jks"
)

for file in $STAGED_FILES; do
    for ext in "${FORBIDDEN_EXTENSIONS[@]}"; do
        if [[ "$file" == $ext ]]; then
            echo "❌ SECURITY ALERT: Forbidden file type: $file"
            FAILED_CHECKS=$((FAILED_CHECKS + 1))
        fi
    done
done

# Check for large files (> 10MB)
for file in $STAGED_FILES; do
    if [ -f "$file" ]; then
        size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo 0)
        if [ "$size" -gt 10485760 ]; then
            echo "❌ SECURITY ALERT: Large file detected: $file ($(($size / 1024 / 1024))MB)"
            FAILED_CHECKS=$((FAILED_CHECKS + 1))
        fi
    fi
done

if [ $FAILED_CHECKS -gt 0 ]; then
    echo ""
    echo "🚨 Security check failed! $FAILED_CHECKS issues found."
    echo "Please fix the issues above before committing."
    exit 1
else
    echo "✅ Security checks passed!"
    exit 0
fi
EOF

chmod +x hooks/security-check.sh
```

### Passo 3: Setup detect-secrets
```bash
# Inizializza detect-secrets
detect-secrets scan --baseline .secrets.baseline

# Aggiorna baseline escludendo falsi positivi
detect-secrets scan --baseline .secrets.baseline --exclude-files '.*\.git/.*' --exclude-files '.*node_modules/.*'

# Crea configurazione detect-secrets
cat > .secrets.baseline << 'EOF'
{
  "version": "1.4.0",
  "plugins_used": [
    {
      "name": "ArtifactoryDetector"
    },
    {
      "name": "AWSKeyDetector"
    },
    {
      "name": "AzureStorageKeyDetector"
    },
    {
      "name": "Base64HighEntropyString",
      "limit": 4.5
    },
    {
      "name": "BasicAuthDetector"
    },
    {
      "name": "CloudantDetector"
    },
    {
      "name": "DiscordBotTokenDetector"
    },
    {
      "name": "GitHubTokenDetector"
    },
    {
      "name": "HexHighEntropyString",
      "limit": 3.0
    },
    {
      "name": "IbmCloudIamDetector"
    },
    {
      "name": "IbmCosHmacDetector"
    },
    {
      "name": "JwtTokenDetector"
    },
    {
      "name": "KeywordDetector",
      "keyword_exclude": ""
    },
    {
      "name": "MailchimpDetector"
    },
    {
      "name": "NpmDetector"
    },
    {
      "name": "PrivateKeyDetector"
    },
    {
      "name": "SendGridDetector"
    },
    {
      "name": "SlackDetector"
    },
    {
      "name": "SoftlayerDetector"
    },
    {
      "name": "SquareOAuthDetector"
    },
    {
      "name": "StripeDetector"
    },
    {
      "name": "TwilioKeyDetector"
    }
  ],
  "filters_used": [
    {
      "path": "detect_secrets.filters.allowlist.is_line_allowlisted"
    },
    {
      "path": "detect_secrets.filters.common.is_baseline_file"
    },
    {
      "path": "detect_secrets.filters.common.is_ignored_due_to_verification_policies",
      "min_level": 2
    },
    {
      "path": "detect_secrets.filters.heuristic.is_indirect_reference"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_likely_id_string"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_lock_file"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_not_alphanumeric_string"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_potential_uuid"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_prefixed_with_dollar_sign"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_sequential_string"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_swagger_file"
    },
    {
      "path": "detect_secrets.filters.heuristic.is_templated_secret"
    }
  ],
  "results": {},
  "generated_at": "2024-01-15T10:30:00Z"
}
EOF
```

### Passo 4: Installazione e Test Pre-commit
```bash
# Installa i hook
pre-commit install

# Test su tutti i file
pre-commit run --all-files

# Test su file specifici
echo "test_secret=abc123def456" > test_file.txt
git add test_file.txt

# Questo dovrebbe fallire a causa del security check
git commit -m "Test commit" || echo "Commit blocked by security check (expected)"

# Rimuovi il file di test
rm test_file.txt
git reset HEAD test_file.txt
```

## Parte 4: .gitignore Enterprise e Template

### Passo 1: .gitignore Completo e Sicuro
```bash
cat > .gitignore << 'EOF'
#############################################
# ENTERPRISE SECURITY .GITIGNORE
#############################################

# ===========================================
# SECURITY - CREDENTIALS E SECRETS
# ===========================================

# Environment files
.env
.env.*
!.env.template
!.env.example

# Credential files
**/credentials/**
**/secrets/**
secret.*
credential.*

# API Keys e tokens
**/config/keys/**
*.token
*.apikey

# SSL/TLS certificates e private keys
*.key
*.pem
*.p12
*.pfx
*.keystore
*.jks
*.crt
*.cer
*.der

# SSH keys
id_rsa
id_dsa
id_ecdsa
id_ed25519
known_hosts
authorized_keys

# Cloud provider credentials
.aws/credentials
.azure/credentials
.gcloud/credentials
gcloud-service-key.json
aws-credentials.json
azure-credentials.json

# Database connection strings
database.url
connection.string
*.connectionstring

# ===========================================
# SECURITY - DATA E BACKUP
# ===========================================

# Database files
*.sql
*.db
*.sqlite
*.sqlite3
*.mdb
*.accdb

# Backup files
*.backup
*.bak
*.dump
*.tar.gz.gpg
backup_*
*_backup

# Log files con possibili PII
*.log
logs/
log/
app_*.log
access.log
error.log
audit.log

# Cache che potrebbe contenere dati sensibili
*.cache
cache/
.cache/
redis.dump

# ===========================================
# DEVELOPMENT - LINGUAGGI E FRAMEWORKS
# ===========================================

# Node.js
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
.pnpm-debug.log*
.npm
.eslintcache
.node_repl_history
*.tgz
.yarn-integrity

# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
*.egg-info/
.installed.cfg
*.egg
MANIFEST
.venv
env/
venv/
ENV/
env.bak/
venv.bak/
.coverage
.pytest_cache/
.hypothesis/
htmlcov/
.tox/
.nox/

# Java
*.class
*.jar
*.war
*.ear
*.zip
*.tar.gz
*.rar
hs_err_pid*
.gradle/
build/
gradle-app.setting
!gradle-wrapper.jar
.gradletasknamecache
target/
.mvn/timing.properties
.mvn/wrapper/maven-wrapper.jar

# .NET
bin/
obj/
*.user
*.suo
*.userosscache
*.sln.docstates
[Dd]ebug/
[Rr]elease/
x64/
x86/
[Aa][Rr][Mm]/
[Aa][Rr][Mm]64/
bld/
[Bb]in/
[Oo]bj/
[Ll]og/

# Go
*.exe
*.exe~
*.dll
*.so
*.dylib
*.test
*.out
go.work

# Rust
target/
Cargo.lock

# ===========================================
# MOBILE DEVELOPMENT
# ===========================================

# Android
*.iml
.gradle
/local.properties
/.idea/caches
/.idea/libraries
/.idea/modules.xml
/.idea/workspace.xml
/.idea/navEditor.xml
/.idea/assetWizardSettings.xml
.DS_Store
/build
/captures
.externalNativeBuild
.cxx
local.properties
*.apk
*.aab
release.keystore
debug.keystore

# iOS
*.xcodeproj/*
!*.xcodeproj/project.pbxproj
!*.xcodeproj/xcshareddata/
!*.xcworkspace/contents.xcworkspacedata
/*.gcno
DerivedData/
*.hmap
*.ipa
*.dSYM.zip
*.dSYM
build/
*.mobileprovision
*.p12

# React Native
.metro-health-check*

# ===========================================
# DEVOPS E INFRASTRUTTURA
# ===========================================

# Docker
.dockerignore
docker-compose.override.yml
.docker/

# Kubernetes
*.kubeconfig
kube-config

# Terraform
*.tfstate
*.tfstate.*
.terraform/
.terraform.lock.hcl
*.tfvars
*.tfvars.json
crash.log
crash.*.log
terraform.rc

# Vagrant
.vagrant/

# Ansible
*.retry
vault-password

# ===========================================
# CI/CD
# ===========================================

# GitHub Actions secrets (local testing)
.env.local
.secrets

# Jenkins
.jenkins/

# GitLab CI
.gitlab-ci-local/

# ===========================================
# IDE E EDITOR
# ===========================================

# Visual Studio Code
.vscode/
*.code-workspace

# IntelliJ IDEA
.idea/
*.iws
*.iml
*.ipr

# Eclipse
.metadata
bin/
tmp/
*.tmp
*.bak
*.swp
*~.nib
local.properties
.settings/
.loadpath
.recommenders

# Sublime Text
*.sublime-project
*.sublime-workspace

# Vim
[._]*.s[a-v][a-z]
[._]*.sw[a-p]
[._]s[a-rt-v][a-z]
[._]ss[a-gi-z]
[._]sw[a-p]

# ===========================================
# SISTEMA OPERATIVO
# ===========================================

# macOS
.DS_Store
.AppleDouble
.LSOverride
Icon
._*
.DocumentRevisions-V100
.fseventsd
.Spotlight-V100
.TemporaryItems
.Trashes
.VolumeIcon.icns
.com.apple.timemachine.donotpresent

# Windows
Thumbs.db
Thumbs.db:encryptable
ehthumbs.db
ehthumbs_vista.db
*.stackdump
[Dd]esktop.ini
$RECYCLE.BIN/
*.cab
*.msi
*.msix
*.msm
*.msp
*.lnk

# Linux
*~
.fuse_hidden*
.directory
.Trash-*
.nfs*

# ===========================================
# DOCUMENTAZIONE E MEDIA
# ===========================================

# Jupyter Notebooks
.ipynb_checkpoints
*/.ipynb_checkpoints/*

# Documentation builds
docs/_build/
site/
_site/

# Media files (grandi)
*.mp4
*.avi
*.mov
*.wmv
*.flv
*.webm
*.mkv
*.m4v

# Immagini grandi
*.psd
*.ai
*.eps
*.pdf
*.dmg
*.iso

# ===========================================
# TESTING E COVERAGE
# ===========================================

# Test results
test-results/
coverage/
*.lcov
.nyc_output
reports/
allure-results/

# Performance testing
*.jmx
.loadrunner/

# ===========================================
# TEMPORARY E CACHE
# ===========================================

# Temporary files
*.tmp
*.temp
temp/
tmp/
.tmp/

# Cache directories
cache/
.cache/
*.cache

# Lock files (mantenere solo quelli necessari)
# package-lock.json  # Commentato - di solito si mantiene
# yarn.lock          # Commentato - di solito si mantiene
# Pipfile.lock       # Commentato - di solito si mantiene

# ===========================================
# INCLUDE EXCEPTIONS (FILE DA MANTENERE)
# ===========================================

# Template e example files
!**/*.template
!**/*.example
!**/.env.template
!**/.env.example
!**/docker-compose.template.yml

# Documentation
!**/README.md
!**/CHANGELOG.md
!**/LICENSE
!**/CONTRIBUTING.md

# Configuration templates
!**/config/*.template.*
!**/config/template.*

# Gitkeep files
!**/.gitkeep

# Essential project files
!package.json
!requirements.txt
!Gemfile
!composer.json
!go.mod
!Cargo.toml
EOF
```

### Passo 2: Template per Diversi Ambienti
```bash
mkdir -p templates

# Template per microservizi
cat > templates/.gitignore.microservice << 'EOF'
# Microservice specific .gitignore
# Include this in addition to the main .gitignore

# Service-specific secrets
service.key
service.env

# Local development
docker-compose.local.yml
.env.local

# Service logs
service-*.log

# Monitoring data
metrics/
traces/

# Load testing
*.jmx
artillery-reports/
EOF

# Template per frontend
cat > templates/.gitignore.frontend << 'EOF'
# Frontend specific additions

# Build outputs
build/
dist/
out/
.next/
.nuxt/
.vercel/

# Dependencies
node_modules/
bower_components/

# Environment
.env.local
.env.development.local
.env.test.local
.env.production.local

# Testing
coverage/
.nyc_output
screenshots/
videos/

# Storybook
storybook-static/

# Bundle analysis
bundle-analyzer-report.html
EOF

# Template per backend
cat > templates/.gitignore.backend << 'EOF'
# Backend specific additions

# Runtime data
pids
*.pid
*.seed
*.pid.lock

# Database
*.sqlite
*.sqlite3
*.db
migrations/versions/*.py
!migrations/versions/.gitkeep

# Uploads
uploads/
media/uploads/
static/uploads/

# Sessions
sessions/

# Email templates compiled
*.mjml.html

# API documentation
api-docs/
swagger-ui/
EOF
```

## Parte 5: Automazione e Monitoring

### Passo 1: GitHub Actions per Security Scanning
```bash
mkdir -p .github/workflows

cat > .github/workflows/security-scan.yml << 'EOF'
name: Security Scan

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]
  schedule:
    - cron: '0 2 * * 1'  # Weekly on Monday at 2 AM

jobs:
  security-scan:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0  # Full history for better scanning
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.11'
    
    - name: Install security tools
      run: |
        pip install detect-secrets pre-commit
        sudo apt-get update && sudo apt-get install -y git-filter-repo
    
    - name: Run detect-secrets
      run: |
        detect-secrets scan --all-files --baseline .secrets.baseline
        detect-secrets audit .secrets.baseline
    
    - name: Check for large files
      run: |
        # Check for files larger than 10MB
        find . -size +10M -not -path "./.git/*" | head -20
    
    - name: Run custom security audit
      run: |
        chmod +x security-audit.sh
        ./security-audit.sh
    
    - name: Verify .gitignore effectiveness
      run: |
        # Create test sensitive files
        echo "test_secret=12345" > .env.test
        echo "password=secret" > config.local
        
        # Check they would be ignored
        if git check-ignore .env.test && git check-ignore config.local; then
          echo "✅ .gitignore working correctly"
        else
          echo "❌ .gitignore not working correctly"
          exit 1
        fi
        
        # Cleanup
        rm .env.test config.local
    
    - name: Check commit messages for secrets
      run: |
        # Scan commit messages for potential secrets
        git log --oneline --all | grep -E "(password|secret|key|token)" && exit 1 || echo "✅ No secrets in commit messages"
    
    - name: Generate security report
      if: always()
      run: |
        echo "# Security Scan Report" > security-report.md
        echo "Generated: $(date)" >> security-report.md
        echo "" >> security-report.md
        echo "## Repository Stats" >> security-report.md
        echo "- Total commits: $(git rev-list --all --count)" >> security-report.md
        echo "- Contributors: $(git log --format='%an' | sort -u | wc -l)" >> security-report.md
        echo "- Files tracked: $(git ls-files | wc -l)" >> security-report.md
        echo "" >> security-report.md
        echo "## Large Files Check" >> security-report.md
        git rev-list --objects --all | git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | awk '/^blob/ { if ($3 > 1048576) print "- " $4 " (" $3/1048576 "MB)" }' >> security-report.md
    
    - name: Upload security report
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: security-report
        path: security-report.md
EOF
```

### Passo 2: Script di Monitoring Continuo
```bash
cat > monitor-repository.sh << 'EOF'
#!/bin/bash

# Continuous repository monitoring script
# Run this weekly via cron

set -e

LOG_FILE="security-monitor-$(date +%Y%m%d).log"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a "$LOG_FILE"
}

log "Starting repository security monitoring..."

# 1. Check repository size
REPO_SIZE=$(du -sh .git | cut -f1)
log "Repository size: $REPO_SIZE"

# 2. Check for new large files
log "Checking for large files..."
git rev-list --objects --all | 
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' |
awk '/^blob/ { if ($3 > 5242880) print $3/1048576 "MB", $4 }' |
sort -rn | head -10 | while read size file; do
    log "Large file: $file ($size)"
done

# 3. Scan recent commits for secrets
log "Scanning recent commits..."
DAYS_BACK=7
git log --since="$DAYS_BACK days ago" --name-only --pretty=format: | 
grep -E "\.(env|key|pem|p12|pfx)$" | sort -u | while read file; do
    log "WARNING: Sensitive file in recent commits: $file"
done

# 4. Check .gitignore effectiveness
log "Testing .gitignore effectiveness..."
test_files=(".env.test" "secret.key" "backup.sql" "app.log")
for file in "${test_files[@]}"; do
    echo "test" > "$file"
    if git check-ignore "$file" >/dev/null 2>&1; then
        log "✅ $file correctly ignored"
    else
        log "❌ WARNING: $file not ignored!"
    fi
    rm -f "$file"
done

# 5. Check for credential patterns in recent commits
log "Scanning for credential patterns..."
git log --since="$DAYS_BACK days ago" -p | grep -E "(password|secret|key|token|credential)" | head -5 | while read line; do
    log "POTENTIAL CREDENTIAL: $line"
done

# 6. Generate alert if issues found
if grep -q "WARNING\|❌" "$LOG_FILE"; then
    log "🚨 SECURITY ISSUES DETECTED - Review required!"
    # Send alert (email, Slack, etc.)
    # mail -s "Security Alert: Repository Issues" admin@company.com < "$LOG_FILE"
else
    log "✅ No security issues detected"
fi

log "Monitoring completed. Report saved to: $LOG_FILE"
EOF

chmod +x monitor-repository.sh
```

### Passo 3: Setup Cron per Monitoring Automatico
```bash
# Aggiungi al crontab per eseguire ogni lunedì alle 9:00
cat > setup-monitoring-cron.sh << 'EOF'
#!/bin/bash

SCRIPT_PATH="$(pwd)/monitor-repository.sh"
CRON_JOB="0 9 * * 1 cd $(pwd) && ./monitor-repository.sh"

# Aggiungi al crontab se non esiste già
(crontab -l 2>/dev/null; echo "$CRON_JOB") | crontab -

echo "✅ Monitoring cron job added:"
echo "$CRON_JOB"
echo ""
echo "To view current crontab: crontab -l"
echo "To remove cron job: crontab -e"
EOF

chmod +x setup-monitoring-cron.sh
```

## Parte 6: Verifica Finale e Testing

### Passo 1: Test Suite Completo
```bash
cat > run-complete-security-test.sh << 'EOF'
#!/bin/bash

set -e

echo "🔐 Running Complete Security Test Suite"
echo "======================================"

TESTS_PASSED=0
TESTS_FAILED=0

run_test() {
    echo "Running: $1"
    if $2; then
        echo "✅ $1 PASSED"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo "❌ $1 FAILED"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
    echo ""
}

# Test 1: Security Audit
test_security_audit() {
    ./security-audit.sh
}

# Test 2: Pre-commit hooks
test_precommit() {
    pre-commit run --all-files
}

# Test 3: .gitignore effectiveness
test_gitignore() {
    # Create test files
    echo "secret=12345" > .env.test
    echo "password=secret" > config.local
    mkdir -p node_modules/test
    echo "module" > node_modules/test/index.js
    
    # Check if ignored
    git check-ignore .env.test &&
    git check-ignore config.local &&
    git check-ignore node_modules/test/index.js
    
    # Cleanup
    rm -rf .env.test config.local node_modules
}

# Test 4: Template files tracked
test_templates() {
    # Templates should be tracked
    ! git check-ignore .env.template &&
    ! git check-ignore templates/.gitignore.microservice
}

# Test 5: Large file detection
test_large_files() {
    # Create a large file
    dd if=/dev/zero of=large_file.tmp bs=1024 count=11000 >/dev/null 2>&1
    
    # Should be detected as large
    size=$(stat -f%z large_file.tmp 2>/dev/null || stat -c%s large_file.tmp)
    
    # Cleanup
    rm large_file.tmp
    
    [ "$size" -gt 10485760 ]
}

# Run all tests
run_test "Security Audit" test_security_audit
run_test "Pre-commit Hooks" test_precommit
run_test "GitIgnore Effectiveness" test_gitignore
run_test "Template Files Tracking" test_templates
run_test "Large File Detection" test_large_files

# Results
echo "======================================"
echo "📊 Test Results:"
echo "Passed: $TESTS_PASSED"
echo "Failed: $TESTS_FAILED"

if [ $TESTS_FAILED -eq 0 ]; then
    echo "🎉 All security tests passed!"
    exit 0
else
    echo "💥 Some tests failed! Review and fix."
    exit 1
fi
EOF

chmod +x run-complete-security-test.sh
```

### Passo 2: Documentazione di Sicurezza
```bash
cat > SECURITY.md << 'EOF'
# Security Guidelines

## Overview
This repository implements comprehensive security measures to prevent accidental exposure of sensitive information.

## Security Measures Implemented

### 1. .gitignore Protection
- Comprehensive patterns for all supported technologies
- Specific protection for credentials, keys, and secrets
- Template files are tracked while actual configuration files are ignored

### 2. Pre-commit Hooks
- Automatic secret detection using detect-secrets
- Custom security checks for common patterns
- Large file detection
- Code quality enforcement

### 3. Monitoring
- Weekly automated security scans
- Repository size monitoring
- Recent commit analysis for sensitive files
- Continuous .gitignore effectiveness testing

## Sensitive File Patterns

### Never Commit
- `.env` files (use `.env.template` instead)
- Private keys (`.key`, `.pem`, `.p12`, `.pfx`)
- Database files (`.sql`, `.sqlite`, `.db`)
- Backup files (`.backup`, `.bak`, `.dump`)
- Log files with PII (`*.log`)
- SSL certificates
- Cloud provider credentials
- API keys and tokens

### Always Use Templates
Instead of committing actual configuration files, use templates:
- `.env.template` instead of `.env`
- `config.template.json` instead of `config.json`
- `docker-compose.template.yml` for Docker configurations

## Development Workflow

### Setup
1. Clone repository
2. Run `./scripts/setup-environment.sh`
3. Copy template files and configure with your values
4. Install pre-commit hooks: `pre-commit install`

### Before Committing
1. Pre-commit hooks will automatically run
2. Fix any security issues detected
3. Never use `git commit --no-verify` to bypass security checks

### Regular Maintenance
1. Weekly: Run `./run-complete-security-test.sh`
2. Monthly: Review and update .gitignore patterns
3. Quarterly: Audit repository for historical issues

## Incident Response

### If Secrets Are Accidentally Committed
1. **DO NOT** push to remote repository
2. Run `./clean-repository.sh` to remove from history
3. Rotate any exposed credentials immediately
4. Review and update .gitignore patterns

### If Secrets Are Already Pushed
1. Alert security team immediately
2. Rotate exposed credentials
3. Use `git filter-repo` or BFG to clean history
4. Force push cleaned history
5. Notify all team members to re-clone repository

## Security Tools Used

### detect-secrets
- Baseline: `.secrets.baseline`
- Configuration includes all major secret types
- Excludes common false positives

### Pre-commit Hooks
- Configuration: `.pre-commit-config.yaml`
- Custom security check: `hooks/security-check.sh`
- Automatic code formatting and linting

### Custom Scripts
- `security-audit.sh`: Manual security audit
- `monitor-repository.sh`: Continuous monitoring
- `clean-repository.sh`: History cleanup

## Contact
For security issues, contact: security@company.com
EOF
```

## Verifica Finale

### Checklist Completamento
- [ ] Repository audit completato e problemi risolti
- [ ] File sensibili rimossi dalla storia
- [ ] Pre-commit hooks installati e configurati
- [ ] .gitignore enterprise implementato
- [ ] Script di automazione creati e testati
- [ ] Monitoring configurato
- [ ] GitHub Actions per CI/CD security
- [ ] Documentazione di sicurezza completa
- [ ] Test suite completo eseguito con successo

### Test Finale
```bash
# Esegui il test completo
./run-complete-security-test.sh

# Verifica che non ci siano file sensibili tracciati
git ls-files | grep -E "\.(env|key|pem|log|sql)$" && echo "❌ Sensitive files found!" || echo "✅ No sensitive files tracked"

# Verifica dimensione repository
du -sh .git

# Test pre-commit
echo "test_secret=12345" > temp_secret.txt
git add temp_secret.txt
git commit -m "Test" && echo "❌ Security bypass!" || echo "✅ Security working"
rm temp_secret.txt
git reset HEAD temp_secret.txt 2>/dev/null || true
```

## Domande Avanzate di Riflessione

1. **Come implementeresti la rotazione automatica di credenziali dopo un leak?**
2. **Quale strategia useresti per repositories molto grandi (>1GB) con storia lunga?**
3. **Come gestiresti la compliance (GDPR, HIPAA) in progetti open source?**
4. **Come automatizzeresti la sincronizzazione di .gitignore across multiple repositories?**
5. **Quale processo implementeresti per onboarding di nuovi sviluppatori su security practices?**

## Risultati Attesi

Al completamento dell'esercizio dovresti avere:
- Un sistema di sicurezza completo e automatizzato
- Repository pulito senza file sensibili nella storia
- Processo di monitoring continuo
- Documentazione completa per il team
- Prevenzione automatica di future violazioni di sicurezza

Questo esercizio simula un ambiente enterprise reale dove la sicurezza è critica e richiede approcci sistematici e automatizzati.
