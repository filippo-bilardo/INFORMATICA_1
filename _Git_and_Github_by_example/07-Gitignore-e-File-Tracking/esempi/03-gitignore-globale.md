# Esempio 03: Gitignore Globale

## Obiettivo
Configurare un file `.gitignore` globale per ignorare automaticamente file specifici dell'OS e IDE in tutti i repository Git.

## Concetto di Gitignore Globale

Un `.gitignore` globale è un file che viene applicato a **tutti** i repository Git sul tuo sistema, indipendentemente dal progetto specifico.

### Vantaggi
- Evita di ripetere gli stessi pattern in ogni progetto
- Ignora automaticamente file OS/IDE specifici
- Mantiene puliti i `.gitignore` dei progetti

## Configurazione Step-by-Step

### 1. Creare il File Globale
```bash
# Naviga nella home directory
cd ~

# Crea il file .gitignore_global
nano .gitignore_global
```

### 2. Contenuto del File Globale
```gitignore
# =======================
# GITIGNORE GLOBALE
# =======================

# === SISTEMI OPERATIVI ===

# macOS
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Windows
Thumbs.db
ehthumbs.db
Desktop.ini
$RECYCLE.BIN/
*.cab
*.msi
*.msm
*.msp
*.lnk

# Linux
*~
.fuse_hidden*
.directory
.Trash-*
.nfs*

# === IDE E EDITOR ===

# Visual Studio Code
.vscode/
!.vscode/settings.json
!.vscode/tasks.json
!.vscode/launch.json
!.vscode/extensions.json
*.code-workspace

# IntelliJ IDEA
.idea/
*.iws
*.iml
*.ipr
out/

# Sublime Text
*.sublime-project
*.sublime-workspace

# Vim
*.swp
*.swo
*~
.netrwhist

# Emacs
*~
\#*\#
/.emacs.desktop
/.emacs.desktop.lock
*.elc

# Atom
.atom/

# === LINGUAGGI SPECIFICI ===

# Node.js (solo file globali)
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Python (solo file globali)
__pycache__/
*.py[cod]
*$py.class
.Python

# Java (solo file globali)
*.class
*.jar
*.war
*.ear
hs_err_pid*

# === TOOLS E UTILITIES ===

# Git
*.orig

# SSH
.ssh/config.local

# GPG
secring.*

# Backup files
*.bak
*.backup
*.old
*.tmp

# Log files
*.log

# Archive files
*.7z
*.dmg
*.gz
*.iso
*.jar
*.rar
*.tar
*.zip
```

### 3. Configurare Git per Usare il File Globale
```bash
# Configura Git per usare il gitignore globale
git config --global core.excludesfile ~/.gitignore_global

# Verifica la configurazione
git config --global core.excludesfile
```

## Test del Funzionamento

### 1. Creare un Repository di Test
```bash
# Crea directory di test
mkdir ~/test-global-gitignore
cd ~/test-global-gitignore

# Inizializza repository
git init

# Crea alcuni file che dovrebbero essere ignorati
touch .DS_Store
touch Thumbs.db
touch test.log
touch backup.bak
echo "console.log('test')" > test.js
```

### 2. Verificare l'Effetto
```bash
# Controlla lo status
git status

# Output atteso (solo test.js dovrebbe apparire):
# On branch main
# No commits yet
# Untracked files:
#   test.js
```

### 3. Test con Editor
```bash
# Crea file di configurazione VS Code
mkdir .vscode
echo '{"files.autoSave": "afterDelay"}' > .vscode/settings.json
echo '{"version": "0.2.0"}' > .vscode/launch.json
echo 'workspace' > test.code-workspace

# Verifica status
git status
# Solo test.js dovrebbe apparire, non i file .vscode/ o .code-workspace
```

## Gestione Avanzata

### 1. Gitignore Locale vs Globale
```bash
# Nel progetto specifico, crea .gitignore locale
echo "node_modules/" > .gitignore
echo "dist/" >> .gitignore

# Il globale gestisce OS/IDE, il locale gestisce il progetto
git status
```

### 2. Override del Globale
```bash
# Se vuoi tracciare un file normalmente ignorato
echo "!important.log" >> .gitignore

# Forza l'aggiunta di un file ignorato
git add -f special.DS_Store
```

### 3. Backup e Sincronizzazione
```bash
# Crea backup del file globale
cp ~/.gitignore_global ~/.gitignore_global.backup

# Sincronizza su più macchine (esempio con dotfiles)
# Aggiungi al tuo repository dotfiles:
ln -s ~/dotfiles/.gitignore_global ~/.gitignore_global
```

## Template per Diversi Ambienti

### Sviluppatore Frontend
```gitignore
# Frontend specific
node_modules/
.npm
.yarn/
dist/
build/
.cache/
.parcel-cache/
```

### Sviluppatore Backend
```gitignore
# Backend specific
*.log
.env
.env.*
logs/
tmp/
```

### Sviluppatore Mobile
```gitignore
# Mobile specific
*.ipa
*.apk
*.aab
.expo/
ios/build/
android/build/
```

## Best Practices

### 1. Cosa Includere nel Globale
✅ File specifici OS (`.DS_Store`, `Thumbs.db`)
✅ File specifici IDE (`.vscode/`, `.idea/`)
✅ File di backup generici (`*.bak`, `*.tmp`)
✅ File di log generici (`*.log`)

### 2. Cosa NON Includere nel Globale
❌ Dipendenze specifiche progetto (`node_modules/`)
❌ File di build specifici (`dist/`, `target/`)
❌ File di configurazione progetto (`.env`)

### 3. Manutenzione
```bash
# Aggiorna periodicamente
nano ~/.gitignore_global

# Ricarica configurazione se necessario
git config --global core.excludesfile ~/.gitignore_global
```

## Troubleshooting

### File Non Ignorato
```bash
# Verifica che il globale sia configurato
git config --global core.excludesfile

# Verifica contenuto del file
cat ~/.gitignore_global | grep "pattern"

# Forza il refresh della cache
git rm -r --cached .
git add .
```

### Conflitti con .gitignore Locale
```bash
# Il locale ha precedenza sul globale
# Verifica entrambi i file
cat .gitignore
cat ~/.gitignore_global
```

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Modulo Precedente](../06-Gestione-File-e-Directory/README.md)
- [➡️ Modulo Successivo](../08-Visualizzare-Storia-Commit/README.md)
