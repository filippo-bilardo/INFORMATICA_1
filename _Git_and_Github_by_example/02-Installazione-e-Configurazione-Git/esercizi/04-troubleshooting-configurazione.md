# Esercizio 04: Troubleshooting e Ottimizzazione Configurazione Git

> **Difficoltà**: ⭐⭐⭐⭐ (Avanzato)  
> **Tempo stimato**: 60-90 minuti  
> **Obiettivo**: Diagnosticare e risolvere problemi comuni di configurazione Git, ottimizzando l'ambiente di sviluppo per diverse situazioni lavorative

## 📝 Descrizione

Questo esercizio avanzato ti metterà nei panni di un sistemista/devops che deve risolvere problemi di configurazione Git in diversi scenari aziendali e personali. Imparerai a diagnosticare problemi, ottimizzare performance e gestire configurazioni complesse.

## 🎯 Obiettivi di Apprendimento

Al termine di questo esercizio sarai in grado di:

- ✅ Diagnosticare e risolvere problemi comuni di configurazione Git
- ✅ Ottimizzare le performance di Git per repository grandi
- ✅ Gestire configurazioni multiple per diversi contesti (lavoro/personale)
- ✅ Implementare strategie di backup e recovery delle configurazioni
- ✅ Configurare Git per ambienti enterprise e CI/CD
- ✅ Automatizzare il setup di configurazioni su nuove macchine

## 📋 Prerequisiti

- **Conoscenza solida** dei comandi Git base
- **Esperienza con configurazioni Git** di base
- **Accesso a terminale/shell** avanzato
- **Comprensione dei concetti** di networking e sicurezza

## 🛠️ Scenario 1: Diagnostic Center - Problemi di Configurazione

### Situazione
Sei stato chiamato per risolvere vari problemi di configurazione Git in un team di sviluppo. Ogni sviluppatore ha problemi diversi.

### Task 1.1: Analisi Diagnostica
```bash
# Crea directory di lavoro per il troubleshooting
mkdir ~/git-troubleshooting-lab
cd ~/git-troubleshooting-lab

# Simula problemi comuni
mkdir scenario-1 scenario-2 scenario-3
```

**Problema 1**: Sviluppatore non riesce a fare commit (identità mancante)
```bash
cd scenario-1
git init
echo "console.log('Hello World');" > app.js

# Simula configurazione mancante
git config --unset user.name
git config --unset user.email

# Prova a fare commit e analizza l'errore
git add app.js
git commit -m "Initial commit"
```

**Problema 2**: Performance lente su repository grande
```bash
cd ../scenario-2
git init
# Simula repository con molti file
for i in {1..1000}; do echo "File content $i" > "file_$i.txt"; done
git add .
```

**Problema 3**: Conflitti di configurazione tra progetti
```bash
cd ../scenario-3
git init
# Simula configurazioni in conflitto
git config user.email "personal@email.com"
# Ma il progetto richiede email aziendale
```

### Task 1.2: Risoluzione Sistematica

Crea uno script di diagnostica:

```bash
# Crea script diagnostic.sh
cat > diagnostic.sh << 'EOF'
#!/bin/bash

echo "🔍 GIT DIAGNOSTIC REPORT"
echo "=========================="
echo "Timestamp: $(date)"
echo ""

echo "📊 Git Version:"
git --version
echo ""

echo "🔧 Current Configuration:"
echo "Global configs:"
git config --global --list | head -20
echo ""

echo "🏠 Repository configs (if in git repo):"
if git rev-parse --git-dir > /dev/null 2>&1; then
    git config --local --list
else
    echo "Not in a git repository"
fi
echo ""

echo "📁 Git directories:"
echo "Global config: $(git config --global --get-regexp core.gitconfig || echo 'Default location')"
echo "User home: $HOME"
echo "Current directory: $(pwd)"
echo ""

echo "🌐 Network connectivity:"
timeout 5 git ls-remote https://github.com/git/git.git HEAD > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "✅ GitHub connectivity: OK"
else
    echo "❌ GitHub connectivity: FAILED"
fi
echo ""

echo "🔐 SSH Configuration:"
if [ -f ~/.ssh/id_rsa.pub ] || [ -f ~/.ssh/id_ed25519.pub ]; then
    echo "✅ SSH keys found"
    ls -la ~/.ssh/*.pub 2>/dev/null
else
    echo "⚠️  No SSH keys found"
fi
echo ""

echo "💾 Repository status (if in git repo):"
if git rev-parse --git-dir > /dev/null 2>&1; then
    echo "Repository size: $(du -sh .git 2>/dev/null | cut -f1)"
    echo "Number of commits: $(git rev-list --count HEAD 2>/dev/null || echo '0')"
    echo "Current branch: $(git branch --show-current 2>/dev/null || echo 'None')"
    echo "Uncommitted changes: $(git status --porcelain | wc -l)"
fi

EOF

chmod +x diagnostic.sh
./diagnostic.sh
```

### Task 1.3: Soluzioni per Ogni Scenario

**Soluzione Scenario 1**: Setup identità automatico
```bash
cd scenario-1

# Script per configurazione automatica identità
cat > setup-identity.sh << 'EOF'
#!/bin/bash

# Prompt per informazioni utente
read -p "Nome completo: " name
read -p "Email: " email
read -p "Configurare globalmente? (y/n): " global

if [ "$global" = "y" ]; then
    git config --global user.name "$name"
    git config --global user.email "$email"
    echo "✅ Configurazione globale impostata"
else
    git config --local user.name "$name"
    git config --local user.email "$email"
    echo "✅ Configurazione locale impostata"
fi

# Verifica configurazione
echo "📋 Configurazione attuale:"
echo "Nome: $(git config user.name)"
echo "Email: $(git config user.email)"
EOF

chmod +x setup-identity.sh
./setup-identity.sh
```

**Soluzione Scenario 2**: Ottimizzazione performance
```bash
cd ../scenario-2

# Configurazioni per performance ottimali
git config core.preloadindex true
git config core.fscache true
git config gc.auto 256

# Script di ottimizzazione completo
cat > optimize-git.sh << 'EOF'
#!/bin/bash

echo "🚀 Ottimizzazione Git in corso..."

# Performance configurations
git config core.preloadindex true
git config core.fscache true
git config gc.auto 256

# Large file handling
git config core.bigFileThreshold 512m

# Network optimizations
git config http.postBuffer 524288000

# Parallel operations
git config submodule.fetchJobs 4

# Memory optimizations
git config pack.threads 0
git config pack.windowMemory 256m

echo "✅ Ottimizzazioni applicate!"

# Mostra configurazioni applicate
echo "📊 Configurazioni performance:"
git config --get-regexp "(core|pack|http|gc)\."
EOF

chmod +x optimize-git.sh
./optimize-git.sh
```

**Soluzione Scenario 3**: Gestione configurazioni multiple
```bash
cd ../scenario-3

# Script per gestire profile multipli
cat > profile-manager.sh << 'EOF'
#!/bin/bash

PROFILES_DIR="$HOME/.git-profiles"
mkdir -p "$PROFILES_DIR"

case "$1" in
    "work")
        echo "🏢 Switching to work profile..."
        git config --global user.name "Mario Rossi"
        git config --global user.email "mario.rossi@company.com"
        git config --global core.sshCommand "ssh -i ~/.ssh/id_work"
        echo "work" > "$PROFILES_DIR/current"
        ;;
    "personal")
        echo "🏠 Switching to personal profile..."
        git config --global user.name "Mario Rossi"
        git config --global user.email "mario.personal@gmail.com"
        git config --global core.sshCommand "ssh -i ~/.ssh/id_personal"
        echo "personal" > "$PROFILES_DIR/current"
        ;;
    "show")
        echo "📋 Current profile: $(cat $PROFILES_DIR/current 2>/dev/null || echo 'unknown')"
        echo "Name: $(git config --global user.name)"
        echo "Email: $(git config --global user.email)"
        ;;
    *)
        echo "Usage: $0 {work|personal|show}"
        echo "Current profile: $(cat $PROFILES_DIR/current 2>/dev/null || echo 'unknown')"
        ;;
esac
EOF

chmod +x profile-manager.sh

# Test del profile manager
./profile-manager.sh show
./profile-manager.sh work
./profile-manager.sh show
```

## 🛠️ Scenario 2: Enterprise Setup - Configurazione Aziendale

### Task 2.1: Configurazione Enterprise
```bash
mkdir ~/enterprise-git-setup
cd ~/enterprise-git-setup

# Script per setup enterprise completo
cat > enterprise-setup.sh << 'EOF'
#!/bin/bash

echo "🏢 ENTERPRISE GIT SETUP"
echo "======================="

# Company-wide configurations
echo "📋 Setting up corporate configurations..."

# Security settings
git config --global user.signingkey "YOUR-GPG-KEY-ID"
git config --global commit.gpgsign true
git config --global tag.forceSignAnnotated true

# Corporate email enforcement
git config --global commit.template ~/.git-commit-template

# Network and proxy settings (example)
# git config --global http.proxy http://proxy.company.com:8080
# git config --global https.proxy https://proxy.company.com:8080

# Corporate Git hooks path
git config --global core.hooksPath ~/.git-hooks-corporate

# Large file settings for corporate repos
git config --global filter.lfs.clean 'git-lfs clean -- %f'
git config --global filter.lfs.smudge 'git-lfs smudge -- %f'
git config --global filter.lfs.process 'git-lfs filter-process'
git config --global filter.lfs.required true

# Performance for large teams
git config --global gc.auto 1
git config --global pack.threads 0

echo "✅ Enterprise configuration completed!"
EOF

chmod +x enterprise-setup.sh
```

### Task 2.2: Template di Commit Aziendale
```bash
# Crea template di commit aziendale
cat > ~/.git-commit-template << 'EOF'
# <type>(<scope>): <subject>
#
# <body>
#
# <footer>
#
# Type can be:
#   feat     (new feature)
#   fix      (bug fix)
#   docs     (documentation)
#   style    (formatting, missing semi colons, etc)
#   refactor (refactoring production code)
#   test     (adding tests, refactoring test)
#   chore    (updating build tasks, package manager configs, etc)
#
# Scope is optional and can be anything specifying the place of the commit change
#
# Subject line should be imperative mood and <= 50 characters
# Body should be wrapped at 72 characters
# Footer should contain any issue references or breaking changes
#
# Example:
# feat(auth): add OAuth2 integration
#
# Implement OAuth2 authentication flow with Google and GitHub providers.
# This replaces the previous basic auth system.
#
# Closes #123
# BREAKING CHANGE: Basic auth is no longer supported
EOF
```

### Task 2.3: Hooks Aziendali
```bash
# Crea directory per hooks aziendali
mkdir -p ~/.git-hooks-corporate

# Hook pre-commit per controlli aziendali
cat > ~/.git-hooks-corporate/pre-commit << 'EOF'
#!/bin/bash

# Corporate pre-commit hook

echo "🔍 Running corporate pre-commit checks..."

# Check commit message format
commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

# Check for secrets
echo "🔐 Checking for secrets..."
if grep -r "password\|secret\|token\|key" --include="*.js" --include="*.py" --include="*.java" .; then
    echo "❌ Potential secrets found in code!"
    exit 1
fi

# Check file size
echo "📏 Checking file sizes..."
for file in $(git diff --cached --name-only); do
    if [ -f "$file" ]; then
        size=$(wc -c < "$file")
        if [ $size -gt 1048576 ]; then  # 1MB
            echo "❌ File $file is too large (${size} bytes)"
            exit 1
        fi
    fi
done

echo "✅ All corporate checks passed!"
exit 0
EOF

chmod +x ~/.git-hooks-corporate/pre-commit
```

## 🛠️ Scenario 3: Automated Deployment - Setup Automatico

### Task 3.1: Script di Installazione Automatica
```bash
mkdir ~/auto-git-deployment
cd ~/auto-git-deployment

# Script per deployment automatico di Git su nuove macchine
cat > auto-deploy-git.sh << 'EOF'
#!/bin/bash

# Automated Git deployment script
set -e

LOG_FILE="git-deployment.log"
echo "🚀 Starting automated Git deployment..." | tee -a $LOG_FILE

# Function to log with timestamp
log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a $LOG_FILE
}

# Detect OS
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if [ -f /etc/debian_version ]; then
            echo "debian"
        elif [ -f /etc/redhat-release ]; then
            echo "redhat"
        else
            echo "linux"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macos"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        echo "windows"
    else
        echo "unknown"
    fi
}

# Install Git based on OS
install_git() {
    local os=$(detect_os)
    log "Detected OS: $os"
    
    case $os in
        "debian")
            log "Installing Git on Debian/Ubuntu..."
            sudo apt update
            sudo apt install -y git
            ;;
        "redhat")
            log "Installing Git on RedHat/CentOS..."
            sudo yum install -y git || sudo dnf install -y git
            ;;
        "macos")
            log "Installing Git on macOS..."
            if command -v brew >/dev/null; then
                brew install git
            else
                log "Please install Homebrew first or install Git manually"
                exit 1
            fi
            ;;
        *)
            log "⚠️  OS not supported for automatic installation"
            exit 1
            ;;
    esac
}

# Configure Git with user input
configure_git() {
    log "Configuring Git..."
    
    # Interactive configuration
    read -p "Full Name: " user_name
    read -p "Email: " user_email
    read -p "Default editor (vim/nano/code): " editor
    read -p "Environment (work/personal): " environment
    
    # Basic configuration
    git config --global user.name "$user_name"
    git config --global user.email "$user_email"
    git config --global core.editor "$editor"
    git config --global init.defaultBranch main
    
    # Environment-specific configurations
    if [ "$environment" = "work" ]; then
        log "Applying work environment configurations..."
        git config --global commit.gpgsign true
        git config --global pull.rebase true
        git config --global core.autocrlf input
    else
        log "Applying personal environment configurations..."
        git config --global pull.rebase false
    fi
    
    log "✅ Git configuration completed"
}

# Setup SSH keys
setup_ssh() {
    log "Setting up SSH keys..."
    
    if [ ! -f ~/.ssh/id_ed25519 ]; then
        read -p "Generate new SSH key? (y/n): " generate_key
        if [ "$generate_key" = "y" ]; then
            ssh-keygen -t ed25519 -C "$user_email" -f ~/.ssh/id_ed25519
            eval "$(ssh-agent -s)"
            ssh-add ~/.ssh/id_ed25519
            log "✅ SSH key generated"
            log "📋 Public key:"
            cat ~/.ssh/id_ed25519.pub
        fi
    else
        log "✅ SSH key already exists"
    fi
}

# Create useful aliases
create_aliases() {
    log "Creating useful Git aliases..."
    
    git config --global alias.st status
    git config --global alias.co checkout
    git config --global alias.br branch
    git config --global alias.ci commit
    git config --global alias.unstage "reset HEAD --"
    git config --global alias.last "log -1 HEAD"
    git config --global alias.visual "!gitk"
    git config --global alias.tree "log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
    
    log "✅ Git aliases created"
}

# Main deployment function
main() {
    log "🚀 Starting Git deployment..."
    
    # Check if Git is already installed
    if command -v git >/dev/null; then
        log "Git is already installed: $(git --version)"
        read -p "Reconfigure anyway? (y/n): " reconfigure
        if [ "$reconfigure" != "y" ]; then
            exit 0
        fi
    else
        install_git
    fi
    
    configure_git
    setup_ssh
    create_aliases
    
    log "🎉 Git deployment completed successfully!"
    log "📊 Final configuration:"
    git config --global --list | head -15 | tee -a $LOG_FILE
}

# Run main function
main "$@"
EOF

chmod +x auto-deploy-git.sh
```

### Task 3.2: Script di Backup Configurazioni
```bash
# Script per backup e restore delle configurazioni Git
cat > git-config-backup.sh << 'EOF'
#!/bin/bash

BACKUP_DIR="$HOME/.git-backups"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")

backup_config() {
    echo "💾 Creating Git configuration backup..."
    
    mkdir -p "$BACKUP_DIR/$TIMESTAMP"
    
    # Backup global config
    if [ -f ~/.gitconfig ]; then
        cp ~/.gitconfig "$BACKUP_DIR/$TIMESTAMP/gitconfig"
        echo "✅ Global config backed up"
    fi
    
    # Backup SSH keys
    if [ -d ~/.ssh ]; then
        cp -r ~/.ssh "$BACKUP_DIR/$TIMESTAMP/ssh"
        echo "✅ SSH keys backed up"
    fi
    
    # Backup custom hooks
    if [ -d ~/.git-hooks-corporate ]; then
        cp -r ~/.git-hooks-corporate "$BACKUP_DIR/$TIMESTAMP/hooks"
        echo "✅ Custom hooks backed up"
    fi
    
    # Create backup manifest
    cat > "$BACKUP_DIR/$TIMESTAMP/manifest.txt" << EOL
Git Configuration Backup
========================
Timestamp: $(date)
Git Version: $(git --version)
OS: $(uname -a)
User: $(whoami)

Files backed up:
- Global Git configuration
- SSH keys and config
- Custom Git hooks
- This manifest
EOL
    
    echo "🎉 Backup completed: $BACKUP_DIR/$TIMESTAMP"
}

restore_config() {
    echo "📂 Available backups:"
    ls -la "$BACKUP_DIR" 2>/dev/null || echo "No backups found"
    
    read -p "Enter backup timestamp to restore: " backup_timestamp
    
    if [ -d "$BACKUP_DIR/$backup_timestamp" ]; then
        echo "🔄 Restoring from backup $backup_timestamp..."
        
        # Restore global config
        if [ -f "$BACKUP_DIR/$backup_timestamp/gitconfig" ]; then
            cp "$BACKUP_DIR/$backup_timestamp/gitconfig" ~/.gitconfig
            echo "✅ Global config restored"
        fi
        
        # Restore SSH (with caution)
        if [ -d "$BACKUP_DIR/$backup_timestamp/ssh" ]; then
            read -p "⚠️  Restore SSH keys? This will overwrite current keys (y/n): " restore_ssh
            if [ "$restore_ssh" = "y" ]; then
                cp -r "$BACKUP_DIR/$backup_timestamp/ssh" ~/.ssh
                chmod 700 ~/.ssh
                chmod 600 ~/.ssh/*
                echo "✅ SSH keys restored"
            fi
        fi
        
        echo "🎉 Restore completed!"
    else
        echo "❌ Backup not found"
    fi
}

case "$1" in
    "backup")
        backup_config
        ;;
    "restore")
        restore_config
        ;;
    *)
        echo "Usage: $0 {backup|restore}"
        ;;
esac
EOF

chmod +x git-config-backup.sh
```

## 🧪 Test e Validazione

### Task 4.1: Suite di Test Completa
```bash
# Script di test per validare tutte le configurazioni
cat > test-git-setup.sh << 'EOF'
#!/bin/bash

echo "🧪 TESTING GIT SETUP"
echo "===================="

TESTS_PASSED=0
TESTS_TOTAL=0

# Function to run test
run_test() {
    local test_name="$1"
    local test_command="$2"
    
    TESTS_TOTAL=$((TESTS_TOTAL + 1))
    echo -n "Testing $test_name... "
    
    if eval "$test_command" > /dev/null 2>&1; then
        echo "✅ PASSED"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo "❌ FAILED"
        echo "  Command: $test_command"
    fi
}

# Test Git installation
run_test "Git installation" "git --version"

# Test basic configuration
run_test "User name configured" "git config user.name"
run_test "User email configured" "git config user.email"

# Test repository operations
run_test "Repository initialization" "cd /tmp && mkdir git-test && cd git-test && git init"
run_test "File addition" "cd /tmp/git-test && echo 'test' > test.txt && git add test.txt"
run_test "Commit creation" "cd /tmp/git-test && git commit -m 'Test commit'"

# Test network connectivity
run_test "GitHub connectivity" "timeout 10 git ls-remote https://github.com/git/git.git HEAD"

# Test SSH (if keys exist)
if [ -f ~/.ssh/id_ed25519.pub ] || [ -f ~/.ssh/id_rsa.pub ]; then
    run_test "SSH key exists" "ls ~/.ssh/*.pub"
fi

# Test aliases
run_test "Git aliases work" "git st --help"

# Cleanup
rm -rf /tmp/git-test

echo ""
echo "📊 TEST RESULTS"
echo "==============="
echo "Passed: $TESTS_PASSED/$TESTS_TOTAL"

if [ $TESTS_PASSED -eq $TESTS_TOTAL ]; then
    echo "🎉 All tests passed! Git setup is working correctly."
    exit 0
else
    echo "⚠️  Some tests failed. Please check your Git configuration."
    exit 1
fi
EOF

chmod +x test-git-setup.sh

# Esegui i test
./test-git-setup.sh
```

## 📊 Deliverables

Crea una directory `deliverables` con i seguenti file:

1. **diagnostic-report.md**: Report completo dei problemi trovati e risolti
2. **enterprise-setup-script.sh**: Script finale per setup aziendale
3. **auto-deployment-guide.md**: Guida per deployment automatico
4. **troubleshooting-playbook.md**: Playbook per problemi comuni
5. **performance-optimization-report.md**: Report delle ottimizzazioni applicate

### Template per Diagnostic Report
```bash
mkdir deliverables
cat > deliverables/diagnostic-report.md << 'EOF'
# Git Configuration Diagnostic Report

## Executive Summary
- **Data**: $(date)
- **Ambiente**: [Descrivi l'ambiente testato]
- **Problemi identificati**: [Numero]
- **Problemi risolti**: [Numero]

## Problemi Identificati

### 1. [Nome problema]
- **Gravità**: [Alta/Media/Bassa]
- **Impatto**: [Descrizione impatto]
- **Causa root**: [Analisi della causa]
- **Soluzione applicata**: [Descrizione soluzione]

## Metriche Performance

### Prima dell'ottimizzazione
- Tempo clone repository: X secondi
- Tempo operazioni Git: X secondi
- Uso memoria: X MB

### Dopo l'ottimizzazione
- Tempo clone repository: X secondi
- Tempo operazioni Git: X secondi
- Uso memoria: X MB

## Raccomandazioni Future
1. [Raccomandazione 1]
2. [Raccomandazione 2]

## Script e Tool Sviluppati
- diagnostic.sh: Script diagnostico automatico
- optimize-git.sh: Script ottimizzazione performance
- profile-manager.sh: Gestione profili multipli
EOF
```

## 🎯 Criteri di Valutazione

### Completamento Base (60%)
- [ ] Tutti gli script diagnostici funzionano correttamente
- [ ] Risoluzione di almeno 3 problemi comuni
- [ ] Setup enterprise base implementato

### Livello Intermedio (80%)
- [ ] Script di deployment automatico funzionante
- [ ] Gestione profili multipli implementata
- [ ] Suite di test completa
- [ ] Performance optimizations applicate

### Livello Avanzato (100%)
- [ ] Sistema di backup/restore completo
- [ ] Hooks aziendali personalizzati
- [ ] Documentazione dettagliata di tutti i processi
- [ ] Automazione completa del setup

## 🚀 Sfide Aggiuntive

1. **Monitor Dashboard**: Crea un dashboard per monitorare la salute di Git in team
2. **Migration Tool**: Sviluppa tool per migrare configurazioni tra ambienti
3. **Security Audit**: Implementa audit automatico delle configurazioni di sicurezza
4. **Multi-Platform**: Estendi gli script per supportare tutti i sistemi operativi

## 📚 Risorse Aggiuntive

- [Git Configuration Documentation](https://git-scm.com/docs/git-config)
- [Pro Git Book - Configuration](https://git-scm.com/book/en/v2/Customizing-Git-Git-Configuration)
- [Git Hooks Documentation](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
- [Enterprise Git Best Practices](https://guides.github.com/introduction/git-handbook/)

---

> **Nota**: Questo esercizio è progettato per sviluppatori senior e sistemisti. Se incontri difficoltà, inizia con gli script base e aggiungi complessità gradualmente.
