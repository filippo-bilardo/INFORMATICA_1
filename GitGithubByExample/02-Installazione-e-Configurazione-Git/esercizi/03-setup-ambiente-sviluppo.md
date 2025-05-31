# Esercizio 3: Setup Ambiente di Sviluppo Completo

## 🎯 Obiettivi
- Configurare un ambiente di sviluppo Git professionale
- Personalizzare Git per massimizzare la produttività
- Integrare Git con editor e strumenti di sviluppo
- Implementare workflow personalizzati

## 🚀 Scenario: Developer Workstation Setup

### Background
Sei un nuovo sviluppatore che sta configurando la propria workstation. Devi creare un ambiente Git ottimizzato che ti supporterà per anni di sviluppo produttivo.

## 📋 Parte 1: Configurazione Git Avanzata (30 minuti)

### Attività 1.1 - Profilo Sviluppatore Completo
```bash
# Informazioni base sviluppatore
git config --global user.name "Il Tuo Nome Completo"
git config --global user.email "tua.email@example.com"

# Informazioni aggiuntive
git config --global user.signingkey "CHIAVE_GPG_ID"  # Se hai GPG
git config --global init.defaultBranch main

# Editor e merge tool preferiti
git config --global core.editor "code --wait"  # VS Code
# git config --global core.editor "vim"        # Vim
# git config --global core.editor "nano"       # Nano

# Merge e diff tools
git config --global merge.tool vimdiff
git config --global diff.tool vimdiff
```

### Attività 1.2 - Configurazioni Workflow
```bash
# Comportamento push/pull
git config --global push.default simple
git config --global pull.rebase false

# Gestione whitespace
git config --global core.autocrlf input   # Linux/Mac
# git config --global core.autocrlf true  # Windows

# Configurazioni sicurezza
git config --global core.filemode false
git config --global help.autocorrect 1

# Performance
git config --global core.preloadindex true
git config --global core.fscache true
git config --global gc.auto 256
```

### Attività 1.3 - Alias Produttività
```bash
# Alias essenziali per sviluppatori
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit

# Alias avanzati
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual '!gitk'

# Log personalizzati
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
git config --global alias.lol "log --graph --decorate --pretty=oneline --abbrev-commit"
git config --global alias.lola "log --graph --decorate --pretty=oneline --abbrev-commit --all"

# Workflow aliases
git config --global alias.up 'pull --rebase --autostash'
git config --global alias.save '!git add -A && git commit -m "SAVEPOINT"'
git config --global alias.wip 'commit -am "WIP"'
git config --global alias.undo 'reset HEAD~1 --mixed'
git config --global alias.amend 'commit -a --amend'

# Utility aliases
git config --global alias.find-merge "log --merges --ancestry-path --oneline"
git config --global alias.cleanup "branch --merged | grep -v '\\*\\|master\\|main' | xargs -n 1 git branch -d"
```

### Attività 1.4 - Configurazioni Specifiche per Progetti
```bash
# Crea directory per progetti di test
mkdir -p ~/git-projects/work-project
mkdir -p ~/git-projects/personal-project

cd ~/git-projects/work-project
git init

# Configurazioni specifiche per progetto lavoro
git config user.email "lavoro@azienda.com"
git config user.name "Nome Cognome"
git config core.autocrlf true

cd ~/git-projects/personal-project
git init

# Configurazioni per progetti personali
git config user.email "personale@gmail.com"
git config user.name "NicknameDev"
git config commit.gpgsign true  # Se usi GPG per progetti personali
```

## 🔧 Parte 2: Integrazione con Strumenti di Sviluppo (45 minuti)

### Attività 2.1 - Setup VS Code per Git
Crea il file di configurazione VS Code `~/.vscode/settings.json`:

```json
{
    "git.enableSmartCommit": true,
    "git.confirmSync": false,
    "git.autofetch": true,
    "git.autofetchPeriod": 180,
    "git.decorations.enabled": true,
    "git.showPushSuccessNotification": true,
    
    "gitlens.currentLine.enabled": true,
    "gitlens.hovers.currentLine.over": "line",
    "gitlens.blame.format": "${message|50?} ${agoOrDate|14-}",
    "gitlens.statusBar.enabled": true,
    
    "terminal.integrated.defaultProfile.linux": "bash",
    "terminal.integrated.profiles.linux": {
        "bash": {
            "path": "bash",
            "args": ["-l"]
        }
    },
    
    "files.watcherExclude": {
        "**/.git/objects/**": true,
        "**/.git/subtree-cache/**": true,
        "**/node_modules/*/**": true
    }
}
```

### Attività 2.2 - Script di Utilità Personalizzati
Crea `~/bin/git-utils.sh`:

```bash
#!/bin/bash

# Script di utilità Git personalizzate

# Funzione per setup rapido nuovo progetto
git-new-project() {
    if [ $# -eq 0 ]; then
        echo "Uso: git-new-project <nome-progetto>"
        return 1
    fi
    
    PROJECT_NAME=$1
    mkdir "$PROJECT_NAME"
    cd "$PROJECT_NAME"
    
    git init
    echo "# $PROJECT_NAME" > README.md
    echo "node_modules/" > .gitignore
    echo ".env" >> .gitignore
    echo "*.log" >> .gitignore
    
    git add .
    git commit -m "Initial commit: project setup

- Added README
- Created .gitignore with common patterns
- Initialized Git repository"
    
    echo "✅ Progetto $PROJECT_NAME creato e inizializzato!"
}

# Funzione per cleanup repository
git-cleanup() {
    echo "🧹 Pulizia repository in corso..."
    
    # Rimuovi branch merged
    git branch --merged | grep -v "\*\|main\|master" | xargs -n 1 git branch -d
    
    # Garbage collection
    git gc --prune=now
    
    # Pulizia oggetti non referenziati
    git fsck --unreachable
    
    echo "✅ Cleanup completato!"
}

# Funzione per statistiche repository
git-stats() {
    echo "📊 Statistiche Repository"
    echo "========================"
    echo "Total commits: $(git rev-list --count HEAD)"
    echo "Total files: $(git ls-files | wc -l)"
    echo "Repository size: $(du -sh .git)"
    echo "Contributors: $(git shortlog -sn | wc -l)"
    echo ""
    echo "Top contributors:"
    git shortlog -sn | head -5
    echo ""
    echo "Recent activity:"
    git log --oneline -10
}

# Funzione per backup configurazioni
git-backup-config() {
    echo "💾 Backup configurazioni Git..."
    
    mkdir -p ~/git-backups
    cp ~/.gitconfig ~/git-backups/gitconfig-$(date +%Y%m%d).backup
    
    echo "✅ Backup salvato in ~/git-backups/"
}

# Esporta le funzioni
export -f git-new-project
export -f git-cleanup
export -f git-stats
export -f git-backup-config
```

Rendi eseguibile e aggiungi al PATH:
```bash
chmod +x ~/bin/git-utils.sh
echo 'source ~/bin/git-utils.sh' >> ~/.bashrc
source ~/.bashrc
```

### Attività 2.3 - Hook Git Personalizzati
Crea hook per validazione automatica. Naviga in un progetto test:

```bash
cd ~/git-projects/work-project

# Crea pre-commit hook
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Pre-commit hook per validazione

echo "🔍 Eseguendo controlli pre-commit..."

# Controlla file di grandi dimensioni
find . -size +10M -not -path "./.git/*" | while read file; do
    echo "⚠️  File di grandi dimensioni trovato: $file"
    echo "Vuoi continuare? (y/n)"
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        exit 1
    fi
done

# Controlla per TODO/FIXME nel codice
if git diff --cached --name-only | xargs grep -l "TODO\|FIXME" > /dev/null 2>&1; then
    echo "⚠️  TODO o FIXME trovati nei file staged:"
    git diff --cached --name-only | xargs grep -n "TODO\|FIXME"
    echo "Vuoi continuare? (y/n)"
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Controlla sintassi JavaScript (se presente)
for file in $(git diff --cached --name-only | grep -E '\.(js|json)$'); do
    if command -v node > /dev/null 2>&1; then
        if ! node -c "$file" > /dev/null 2>&1; then
            echo "❌ Errore di sintassi in $file"
            exit 1
        fi
    fi
done

echo "✅ Controlli pre-commit completati!"
EOF

chmod +x .git/hooks/pre-commit

# Crea commit-msg hook
cat > .git/hooks/commit-msg << 'EOF'
#!/bin/bash
# Valida formato messaggi commit

commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! grep -qE "$commit_regex" "$1"; then
    echo "❌ Formato messaggio commit non valido!"
    echo "Formato richiesto: type(scope): description"
    echo "Tipi validi: feat, fix, docs, style, refactor, test, chore"
    echo "Esempio: feat(auth): add login functionality"
    exit 1
fi

echo "✅ Formato messaggio commit valido!"
EOF

chmod +x .git/hooks/commit-msg
```

### Attività 2.4 - Template Commit Personalizzati
```bash
# Crea template per messaggi commit
cat > ~/.gitmessage << 'EOF'
# <type>(<scope>): <subject>
#
# <body>
#
# <footer>

# Type deve essere uno di:
# feat: Nuova feature
# fix: Bug fix
# docs: Documentazione
# style: Formattazione
# refactor: Refactoring
# test: Aggiunta test
# chore: Manutenzione

# Scope: modulo/componente affetto (opzionale)
# Subject: descrizione concisa (max 50 caratteri)
# Body: spiegazione dettagliata (opzionale)
# Footer: riferimenti issues, breaking changes (opzionale)
EOF

# Configura template
git config --global commit.template ~/.gitmessage
```

## 🔐 Parte 3: Sicurezza e Backup (30 minuti)

### Attività 3.1 - Setup GPG per Signed Commits
```bash
# Genera chiave GPG (se non già fatto)
gpg --full-generate-key

# Lista chiavi disponibili
gpg --list-secret-keys --keyid-format LONG

# Configura Git per usare GPG
GPG_KEY_ID="YOUR_KEY_ID"  # Sostituisci con il tuo ID
git config --global user.signingkey $GPG_KEY_ID
git config --global commit.gpgsign true

# Esporta chiave pubblica per GitHub
gpg --armor --export $GPG_KEY_ID > ~/my-gpg-key.asc
echo "📄 Chiave GPG pubblica salvata in ~/my-gpg-key.asc"
echo "Aggiungila al tuo account GitHub in Settings > SSH and GPG keys"
```

### Attività 3.2 - Backup Strategy
```bash
# Script di backup automatico
cat > ~/bin/git-auto-backup.sh << 'EOF'
#!/bin/bash
# Backup automatico configurazioni e repositories

BACKUP_DIR="$HOME/git-backups/$(date +%Y%m%d)"
mkdir -p "$BACKUP_DIR"

echo "🔄 Avvio backup Git..."

# Backup configurazioni
cp ~/.gitconfig "$BACKUP_DIR/"
cp ~/.gitignore_global "$BACKUP_DIR/" 2>/dev/null || true

# Backup SSH keys
cp -r ~/.ssh "$BACKUP_DIR/" 2>/dev/null || true

# Lista repositories locali
find ~/git-projects -name ".git" -type d | while read git_dir; do
    repo_path=$(dirname "$git_dir")
    repo_name=$(basename "$repo_path")
    
    echo "Backup repository: $repo_name"
    tar -czf "$BACKUP_DIR/$repo_name.tar.gz" -C "$(dirname "$repo_path")" "$repo_name"
done

echo "✅ Backup completato in $BACKUP_DIR"
EOF

chmod +x ~/bin/git-auto-backup.sh

# Programma backup settimanale (opzionale)
(crontab -l 2>/dev/null; echo "0 2 * * 0 ~/bin/git-auto-backup.sh") | crontab -
```

### Attività 3.3 - Gitignore Globale
```bash
# Crea gitignore globale
cat > ~/.gitignore_global << 'EOF'
# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Editor files
.vscode/
.idea/
*.swp
*.swo
*~

# Temporary files
*.tmp
*.temp
.cache/

# Logs
*.log
logs/

# Environment files
.env
.env.local
.env.development
.env.production

# Package managers
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Build outputs
dist/
build/
*.min.js
*.min.css
EOF

# Configura gitignore globale
git config --global core.excludesfile ~/.gitignore_global
```

## 📊 Parte 4: Testing e Validazione (30 minuti)

### Attività 4.1 - Test Configurazioni
```bash
# Script di test configurazioni
cat > ~/bin/git-test-config.sh << 'EOF'
#!/bin/bash

echo "🧪 Test Configurazioni Git"
echo "=========================="

# Test configurazioni base
echo "✓ Nome utente: $(git config --global user.name)"
echo "✓ Email: $(git config --global user.email)"
echo "✓ Editor: $(git config --global core.editor)"
echo "✓ Branch default: $(git config --global init.defaultBranch)"

# Test alias
echo ""
echo "📝 Test Alias:"
git config --global --get-regexp alias | head -5

# Test hook
echo ""
echo "🪝 Test Hook (se disponibili):"
if [ -d ".git/hooks" ]; then
    ls -la .git/hooks/ | grep -v sample || echo "Nessun hook personalizzato"
fi

# Test performance
echo ""
echo "⚡ Test Performance:"
time git status > /dev/null 2>&1
echo "Status check completato"

# Test sicurezza
echo ""
echo "🔐 Test Sicurezza:"
if git config --global commit.gpgsign | grep -q true; then
    echo "✓ GPG signing abilitato"
else
    echo "⚠️ GPG signing disabilitato"
fi

echo ""
echo "✅ Test configurazioni completato!"
EOF

chmod +x ~/bin/git-test-config.sh
~/bin/git-test-config.sh
```

### Attività 4.2 - Progetto Test Completo
```bash
# Crea progetto per testare l'ambiente
cd ~/git-projects
git-new-project test-environment

# Test commit con template
echo "console.log('Hello Git!');" > app.js
git add app.js

# Il commit aprirà l'editor con il template
git commit
# Prova a scrivere: "feat(app): add hello world script"

# Test alias
git st
git lg
git lol

# Test utility functions
git-stats
```

### Attività 4.3 - Documentazione Setup
```bash
# Crea documentazione del setup
cat > ~/git-projects/SETUP-DOCUMENTATION.md << 'EOF'
# Documentazione Setup Git Environment

## 📋 Configurazioni Applicate

### Configurazioni Globali
- User name e email configurati
- Editor predefinito impostato
- Branch default: main
- Autostash e rebase configurati

### Alias Installati
- `git st` = `git status`
- `git co` = `git checkout`
- `git br` = `git branch`
- `git ci` = `git commit`
- `git lg` = log grafico colorato
- `git up` = pull con rebase e autostash

### Strumenti Integrati
- VS Code configurato per Git
- Hook pre-commit per validazione
- Template commit personalizzato
- GPG signing (se configurato)

### Utilities Personalizzate
- `git-new-project`: Crea nuovo progetto
- `git-cleanup`: Pulizia repository
- `git-stats`: Statistiche repository
- `git-backup-config`: Backup configurazioni

### Sicurezza
- Gitignore globale configurato
- GPG signing per commit (opzionale)
- Backup automatico settimanale

## 🔧 Manutenzione

### Comandi di Manutenzione Settimanale
```bash
git-cleanup          # Pulizia branch e oggetti
git-backup-config    # Backup configurazioni
git gc --aggressive  # Garbage collection aggressiva
```

### Aggiornamenti Configurazione
```bash
git config --global --edit  # Modifica configurazioni
source ~/.bashrc            # Ricarica utilities
```

## 📈 Produttività

### Workflow Quotidiano
1. `git st` - Controlla stato
2. `git add .` - Stage modifiche
3. `git ci` - Commit con template
4. `git up` - Sincronizza con remote

### Troubleshooting
- Se hook falliscono: controlla permessi
- Se alias non funzionano: ricarica bashrc
- Se GPG fails: controlla configurazione chiave

EOF

echo "📚 Documentazione setup salvata in ~/git-projects/SETUP-DOCUMENTATION.md"
```

## 🏆 Deliverables Finali

### 1. Ambiente Configurato ✅
- Configurazioni Git complete e personalizzate
- Alias e utilities installati
- Integrazione editor/IDE completata
- Sistema di backup configurato

### 2. Script di Utilità ✅
- Script di creazione progetti
- Hook di validazione automatica
- Sistema di backup e manutenzione
- Template commit personalizzati

### 3. Documentazione ✅
- Setup completo documentato
- Guide di troubleshooting
- Best practices implementate
- Workflow standardizzato

### 4. Report Setup (400 parole)
Scrivi un report che includa:
- Configurazioni applicate e motivazioni
- Vantaggi dell'ambiente personalizzato
- Workflow di sviluppo ottimizzato
- Strategie di backup e sicurezza

## 🎯 Checklist Completamento

### Configurazioni Base
- [ ] User name e email configurati
- [ ] Editor predefinito impostato
- [ ] Branch default configurato
- [ ] Whitespace e CRLF configurati

### Produttività
- [ ] Alias essenziali installati
- [ ] Template commit configurato
- [ ] Hook di validazione attivi
- [ ] Utilities personalizzate funzionanti

### Integrazione Strumenti
- [ ] Editor/IDE configurato per Git
- [ ] Terminal ottimizzato
- [ ] Script utilities installati
- [ ] PATH aggiornato

### Sicurezza
- [ ] Gitignore globale configurato
- [ ] GPG signing (opzionale) configurato
- [ ] Backup strategy implementata
- [ ] Documentazione completa

## 🔧 Risoluzione Problemi Comuni

### Alias Non Funzionano
```bash
git config --global --get-regexp alias
source ~/.bashrc
```

### Hook Non Eseguiti
```bash
chmod +x .git/hooks/*
ls -la .git/hooks/
```

### GPG Issues
```bash
gpg --list-secret-keys
git config --global user.signingkey
```

---

**Tempo stimato:** 2-2.5 ore  
**Difficoltà:** ⭐⭐⭐⭐  
**Prerequisiti:** Git installato, familiarità con terminal  
**Tag:** #setup #configuration #productivity #professional
