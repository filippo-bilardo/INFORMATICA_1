# Gitignore Globale e Locale

## 🎯 Tipi di Gitignore

Git supporta diversi livelli di configurazione `.gitignore` per massima flessibilità:

1. **Repository-level** (.gitignore nel progetto)
2. **Global** (configurazione utente globale)
3. **Exclude** (specifico del repository, non condiviso)

## 📂 Gitignore Locale (Repository)

### Posizionamento
```
my-project/
├── .gitignore          ← Principale (root)
├── src/
│   └── .gitignore      ← Specifico per src/
├── docs/
│   └── .gitignore      ← Specifico per docs/
└── tests/
    └── .gitignore      ← Specifico per tests/
```

### Caratteristiche
- ✅ **Condiviso** con tutto il team
- ✅ **Versionato** insieme al codice
- ✅ **Specifico** per il tipo di progetto
- ✅ **Gerarchico** (subdirectory possono avere regole specifiche)

### Esempio Repository Multi-cartella
```gitignore
# Root .gitignore
# Regole generali del progetto
node_modules/
*.log
.env

# Build artifacts
build/
dist/
```

```gitignore
# src/.gitignore
# Regole specifiche per il codice sorgente
*.test.local.js
*.debug.js
temp_*
```

```gitignore
# docs/.gitignore  
# Regole specifiche per la documentazione
.docusaurus/
build/
.cache/
```

## 🌍 Gitignore Globale

### Setup Gitignore Globale
```bash
# Configura il file globale
git config --global core.excludesfile ~/.gitignore_global

# Verifica la configurazione
git config --global core.excludesfile
```

### Creazione del File Globale
```bash
# Crea/modifica il file globale
touch ~/.gitignore_global
nano ~/.gitignore_global  # o vim, code, etc.
```

### Contenuto Tipico del Gitignore Globale
```gitignore
# ~/.gitignore_global

# === SISTEMA OPERATIVO ===
# macOS
.DS_Store
.AppleDouble
.LSOverride
._*

# Windows
Thumbs.db
ehthumbs.db
Desktop.ini
$RECYCLE.BIN/

# Linux
*~
.directory
.Trash-*

# === IDE E EDITOR ===
# Visual Studio Code
.vscode/
*.code-workspace

# IntelliJ IDEA
.idea/
*.iml
*.iws

# Sublime Text
*.sublime-workspace
*.sublime-project

# Vim
*.swp
*.swo
.viminfo

# Emacs
*~
\#*\#
.\#*

# === BACKUP E TEMPORANEI ===
# File di backup
*.bak
*.backup
*.old
*.orig

# File temporanei
*.tmp
*.temp
.cache/
temp/

# === PERSONALI ===
# Note personali
NOTES.md
TODO.txt
.personal/
```

### Vantaggi del Gitignore Globale
- ✅ **Applica a tutti i repository**
- ✅ **Evita ripetizione** di regole comuni
- ✅ **Personalizzabile** per ogni sviluppatore
- ✅ **Non interferisce** con le regole del progetto

## 🔒 File .git/info/exclude

### Caratteristiche
- 📍 **Posizione**: `.git/info/exclude`
- 🚫 **Non condiviso** (locale al repository)
- 🚫 **Non versionato**
- 🎯 **Specifico** per esigenze personali

### Quando Usarlo
```bash
# Modifica .git/info/exclude
nano .git/info/exclude
```

**Casi d'uso:**
- File di configurazione personale
- Tool di sviluppo specifici
- Test temporanei
- File che solo tu usi nel progetto

```gitignore
# .git/info/exclude
# I miei file di sviluppo personali
my-debug-notes.txt
personal-config.json
.my-tools/
```

## 📊 Gerarchia e Precedenza

### Ordine di Applicazione
1. **Command line** (`git add -f`)
2. **.gitignore** (dalla directory più specifica a root)  
3. **~/.gitignore_global**
4. **.git/info/exclude**

### Esempio di Gerarchia
```
project/
├── .gitignore          ← Livello 2: "*.log"
└── src/
    ├── .gitignore      ← Livello 1: "!debug.log"
    └── debug.log       ← RISULTATO: NON ignorato
```

```gitignore
# project/.gitignore
*.log

# project/src/.gitignore  
!debug.log    # Override: mantieni debug.log in src/
```

## 🛠️ Configurazioni per Team

### Setup Automatico per Nuovi Sviluppatori
```bash
#!/bin/bash
# setup-gitignore.sh

echo "🔧 Configurazione Git ignore per il team..."

# Controlla se esiste già un gitignore globale
if git config --global core.excludesfile > /dev/null 2>&1; then
    echo "✅ Gitignore globale già configurato"
    echo "   Posizione: $(git config --global core.excludesfile)"
else
    echo "📝 Configurazione gitignore globale..."
    
    # Crea il file gitignore globale standard del team
    cat > ~/.gitignore_global << 'EOF'
# === SISTEMA ===
.DS_Store
Thumbs.db
*~

# === IDE TEAM ===
.vscode/settings.json
.idea/workspace.xml

# === PERSONALI ===
*.personal.*
.notes/
NOTES.*
EOF

    # Configura Git per usarlo
    git config --global core.excludesfile ~/.gitignore_global
    echo "✅ Gitignore globale configurato!"
fi

echo ""
echo "📋 Configurazione attuale:"
echo "   Globale: $(git config --global core.excludesfile)"
echo "   Locale: $(if [ -f .gitignore ]; then echo 'Presente'; else echo 'Assente'; fi)"
```

### Template di Progetto
```bash
# create-project-template.sh
#!/bin/bash

PROJECT_NAME=$1
if [ -z "$PROJECT_NAME" ]; then
    echo "Uso: $0 <nome-progetto>"
    exit 1
fi

echo "🚀 Creazione progetto $PROJECT_NAME..."

mkdir "$PROJECT_NAME"
cd "$PROJECT_NAME"

# Inizializza Git
git init

# Crea .gitignore base
cat > .gitignore << 'EOF'
# === DIPENDENZE ===
node_modules/
vendor/

# === BUILD ===
build/
dist/
target/

# === LOGS ===
*.log
logs/

# === AMBIENTE ===
.env
.env.local

# === TEMPORANEI ===
*.tmp
temp/
.cache/

# === IDE (aggiunta al globale) ===
.vscode/launch.json
.idea/runConfigurations/
EOF

echo "✅ Progetto $PROJECT_NAME creato con .gitignore configurato!"
```

## 🔍 Debug e Diagnostica

### Comandi di Debug
```bash
# Verifica quale file gitignore sta ignorando un file
git check-ignore -v filename.txt

# Output esempio:
# .gitignore:3:*.txt    filename.txt

# Mostra tutti i gitignore attivi
git status --ignored

# Lista configurazioni ignore
git config --list | grep ignore
```

### Script di Diagnostica
```bash
#!/bin/bash
# gitignore-debug.sh

echo "🔍 Diagnostica Gitignore"
echo "========================"

echo ""
echo "📍 Configurazioni attive:"
echo "   Globale: $(git config --global core.excludesfile || echo 'Non configurato')"
echo "   Locale: $(if [ -f .gitignore ]; then echo 'Presente'; else echo 'Assente'; fi)"
echo "   Exclude: $(if [ -f .git/info/exclude ]; then echo 'Presente'; else echo 'Assente'; fi)"

echo ""
echo "📂 File .gitignore trovati:"
find . -name ".gitignore" -type f | while read file; do
    echo "   $file ($(wc -l < "$file") righe)"
done

echo ""
echo "🧪 Test file comune:"
test_files=("node_modules" "*.log" ".env" ".DS_Store")
for file in "${test_files[@]}"; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "   ✅ $file è ignorato"
    else
        echo "   ❌ $file NON è ignorato"
    fi
done
```

## 🎯 Best Practices per Team

### 1. Separazione delle Responsabilità
```gitignore
# .gitignore (progetto) - SOLO regole del progetto
node_modules/
build/
.env

# ~/.gitignore_global (personale) - SOLO preferenze personali
.DS_Store
.vscode/settings.json
NOTES.md
```

### 2. Documentazione delle Regole
```gitignore
# === DIPENDENZE ===
# Non committare le dipendenze installate
node_modules/
vendor/
__pycache__/

# === CONFIGURAZIONE SENSIBILE ===
# File con credenziali - IMPORTANTE: Non committare mai!
.env
*.key
secrets.json

# === BUILD ARTIFACTS ===
# File generati automaticamente
build/
dist/
*.min.js
*.min.css
```

### 3. Template per Nuovi Progetti
Mantieni template standardizzati:

```bash
# .gitignore-templates/
├── node.gitignore
├── python.gitignore
├── java.gitignore
└── web.gitignore
```

## 🧪 Esercizio Pratico

### Setup Ambiente Completo
```bash
# 1. Configura gitignore globale
git config --global core.excludesfile ~/.gitignore_global

cat > ~/.gitignore_global << 'EOF'
# OS files
.DS_Store
Thumbs.db

# Personal notes
NOTES.md
.personal/
EOF

# 2. Crea progetto di test
mkdir test-multi-ignore
cd test-multi-ignore
git init

# 3. Crea .gitignore locale
cat > .gitignore << 'EOF'
# Project specific
node_modules/
build/
.env
EOF

# 4. Crea subdirectory con proprio .gitignore
mkdir src
cat > src/.gitignore << 'EOF'
# Source specific
*.test.local.js
EOF

# 5. Crea file di test
touch .DS_Store          # Ignorato da globale
touch NOTES.md           # Ignorato da globale  
touch .env               # Ignorato da locale
touch node_modules       # Ignorato da locale
touch src/app.test.local.js  # Ignorato da src/.gitignore

# 6. Verifica
git status
git check-ignore -v .DS_Store
git check-ignore -v .env
git check-ignore -v src/app.test.local.js
```

## 🎯 Quiz di Verifica

1. **Qual è l'ordine di precedenza tra i diversi tipi di .gitignore?**
2. **Quando useresti .git/info/exclude invece di .gitignore?**
3. **Come configuri un .gitignore globale?**

**Risposte:**
1. Locale (più specifico) → Root → Globale → Exclude
2. Per file personali che non vuoi condividere con il team
3. `git config --global core.excludesfile ~/.gitignore_global`

## 🔗 Prossimi Passi

- [← Pattern e Sintassi](./02-pattern-sintassi.md)
- [Gestione File Già Tracciati →](./04-file-tracciati.md)
- [Esempi Pratici →](../esempi/01-setup-nodejs.md)

---

> 💡 **Suggerimento**: Usa il gitignore globale per le tue preferenze personali e quello locale per le regole del progetto!
