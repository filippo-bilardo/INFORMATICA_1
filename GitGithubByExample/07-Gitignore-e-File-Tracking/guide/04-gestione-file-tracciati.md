# Gestione File Tracciati

## 📖 Il Problema: File Già in Tracking

Una situazione comune: hai aggiunto file al repository e **solo dopo** ti rendi conto che dovrebbero essere ignorati. Il file `.gitignore` NON rimuove automaticamente file già tracciati da Git.

### 🚨 Scenario Tipico
```bash
# Hai fatto questo...
$ git add .
$ git commit -m "Initial commit"

# E ora realizzi che hai committato:
$ git ls-files
.env                    # ❌ File con password!
node_modules/package.js # ❌ Dipendenze!
dist/bundle.js         # ❌ File di build!
.DS_Store              # ❌ File di sistema!

# Aggiungi .gitignore DOPO
$ echo ".env" >> .gitignore
$ echo "node_modules/" >> .gitignore

# Ma Git continua a tracciare questi file!
$ git status
Changes not staged for commit:
    modified:   .env    # Ancora tracciato!
```

## 🛠️ Soluzioni per Rimuovere File Tracciati

### 1. **git rm --cached** - Rimozione Singola
```bash
# Rimuove un file dal tracking (ma non dal filesystem)
$ git rm --cached .env
rm '.env'

# Verifica che sia stato rimosso dal tracking
$ git status
Changes to be committed:
    deleted:    .env

Untracked files:
    .env        # Ora è non tracciato

# Committa la rimozione
$ git commit -m "Stop tracking .env file"
```

### 2. **git rm --cached -r** - Rimozione Directory
```bash
# Rimuove una directory completa dal tracking
$ git rm --cached -r node_modules/
rm 'node_modules/package.js'
rm 'node_modules/lodash/index.js'
# ... (tutti i file nella directory)

# Committa la rimozione
$ git commit -m "Stop tracking node_modules directory"
```

### 3. **Pulizia Massiva con grep**
```bash
# Trova tutti i file che dovrebbero essere ignorati
$ git ls-files | grep -E '\.(log|tmp|cache)$'
error.log
debug.log
cache.tmp

# Rimuovili dal tracking
$ git ls-files | grep -E '\.(log|tmp|cache)$' | xargs git rm --cached
```

## 🔄 Processo Completo di Pulizia

### Step 1: Identifica File da Rimuovere
```bash
# Vedi tutti i file tracciati
$ git ls-files

# Filtra per pattern specifici
$ git ls-files | grep node_modules
$ git ls-files | grep '\.log$'
$ git ls-files | grep '\.env'

# Usa git check-ignore per testare il .gitignore attuale
$ git ls-files | git check-ignore --stdin
```

### Step 2: Backup di Sicurezza
```bash
# Crea un branch di backup prima della pulizia
$ git checkout -b backup-before-cleanup
$ git checkout main

# O crea un tag
$ git tag before-gitignore-cleanup
```

### Step 3: Rimozione Sistematica
```bash
# Strategia 1: File specifici
$ git rm --cached .env config/secrets.yml

# Strategia 2: Pattern con find
$ find . -name "*.log" -exec git rm --cached {} \;

# Strategia 3: Directory complete
$ git rm --cached -r node_modules/ dist/ .cache/
```

### Step 4: Aggiorna .gitignore
```bash
# Aggiungi regole per evitare il problema in futuro
$ cat >> .gitignore << EOF
# Environment files
.env
.env.*
!.env.example

# Dependencies
node_modules/

# Build outputs
dist/
build/

# Logs
*.log
logs/

# Cache
.cache/
tmp/
EOF
```

### Step 5: Commit e Verifica
```bash
# Committa le modifiche
$ git add .gitignore
$ git commit -m "Clean up repository and update .gitignore"

# Verifica che i file siano ora ignorati
$ git status --ignored
```

## 📋 Script di Automazione

### Script di Pulizia Universale
```bash
#!/bin/bash
# File: cleanup-git-tracking.sh

echo "🧹 Pulizia Repository Git - Rimozione File Tracciati"
echo "=================================================="

# Backup di sicurezza
echo "📦 Creazione backup..."
git tag "backup-$(date +%Y%m%d-%H%M%S)" 2>/dev/null || echo "⚠️  Impossibile creare tag di backup"

# Lista file da rimuovere
echo "🔍 Identificazione file da rimuovere..."

# File di ambiente
ENV_FILES=$(git ls-files | grep -E '\.(env|key|pem)$')
if [ ! -z "$ENV_FILES" ]; then
    echo "🔐 File di ambiente trovati:"
    echo "$ENV_FILES"
    echo "$ENV_FILES" | xargs git rm --cached
fi

# Directory di dipendenze
DEPS_DIRS=("node_modules" "vendor" "venv" "__pycache__")
for dir in "${DEPS_DIRS[@]}"; do
    if git ls-files | grep -q "^$dir/"; then
        echo "📦 Rimozione directory: $dir/"
        git rm --cached -r "$dir/" 2>/dev/null
    fi
done

# File di build
BUILD_DIRS=("dist" "build" "out" "target")
for dir in "${BUILD_DIRS[@]}"; do
    if git ls-files | grep -q "^$dir/"; then
        echo "🏗️  Rimozione build: $dir/"
        git rm --cached -r "$dir/" 2>/dev/null
    fi
done

# File temporanei
TEMP_FILES=$(git ls-files | grep -E '\.(log|tmp|cache|swp|swo)$')
if [ ! -z "$TEMP_FILES" ]; then
    echo "🗑️  File temporanei trovati:"
    echo "$TEMP_FILES"
    echo "$TEMP_FILES" | xargs git rm --cached
fi

# File di sistema
SYS_FILES=$(git ls-files | grep -E '(\.DS_Store|Thumbs\.db|desktop\.ini)$')
if [ ! -z "$SYS_FILES" ]; then
    echo "💻 File di sistema trovati:"
    echo "$SYS_FILES"
    echo "$SYS_FILES" | xargs git rm --cached
fi

echo "✅ Pulizia completata! Verifica le modifiche e committa."
echo "💡 Comando suggerito: git commit -m 'Clean up tracked files'"
```

### Script di Verifica Post-Pulizia
```bash
#!/bin/bash
# File: verify-gitignore.sh

echo "🔍 Verifica Configurazione .gitignore"
echo "======================================"

# Test file comuni che dovrebbero essere ignorati
TEST_FILES=(
    ".env"
    "node_modules/test.js"
    "dist/bundle.js"
    ".DS_Store"
    "*.log"
    ".cache/test"
)

echo "🧪 Test pattern .gitignore:"
for file in "${TEST_FILES[@]}"; do
    if git check-ignore "$file" &>/dev/null; then
        echo "✅ $file - IGNORATO"
    else
        echo "❌ $file - NON ignorato"
    fi
done

echo ""
echo "📊 Statistiche repository:"
echo "File tracciati: $(git ls-files | wc -l)"
echo "File ignorati: $(git status --ignored --porcelain | grep '^!!' | wc -l)"

echo ""
echo "🔍 File tracciati che potrebbero essere ignorati:"
git ls-files | grep -E '\.(log|tmp|cache|env|key)$|node_modules/|dist/|\.DS_Store' || echo "Nessuno trovato ✅"
```

## ⚠️ Precauzioni e Avvertenze

### 1. **Differenza tra --cached e senza**
```bash
# ✅ SICURO - Rimuove solo dal tracking, file rimane su disco
$ git rm --cached file.txt

# ⚠️  PERICOLOSO - Rimuove dal tracking E cancella dal disco!
$ git rm file.txt
```

### 2. **File Sensibili già Committati**
```bash
# ❌ PROBLEMA: Password già nella storia Git!
$ git log --oneline -p | grep "password"
commit abc123 - database_password = "secret123"

# ✅ SOLUZIONE: Riscrittura della storia (PERICOLOSO!)
# Solo su repository privati, mai su codice condiviso!
$ git filter-branch --tree-filter 'rm -f .env' HEAD
```

### 3. **Collaborazione in Team**
```bash
# ⚠️  ATTENZIONE: Coordinamento necessario
# Comunica al team prima di rimuovere file tracciati

# Dopo la pulizia, i colleghi dovranno:
$ git pull
$ git clean -fd  # Rimuove file non tracciati
```

## 🧪 Esercizio Pratico

### Scenario: Repository Disordinato
Hai ereditato un repository con questi problemi:
```bash
$ git ls-files
.env
.env.production
node_modules/lodash/index.js
dist/bundle.js
dist/bundle.min.js
logs/error.log
logs/access.log
.DS_Store
src/index.js         # ✅ Questo deve rimanere!
package.json         # ✅ Questo deve rimanere!
README.md           # ✅ Questo deve rimanere!
```

**Compito:** Pulisci il repository mantenendo solo i file necessari.

<details>
<summary>💡 Soluzione Completa</summary>

```bash
# 1. Backup di sicurezza
$ git tag backup-before-cleanup

# 2. Rimuovi file di ambiente
$ git rm --cached .env .env.production

# 3. Rimuovi directory dependencies e build
$ git rm --cached -r node_modules/ dist/

# 4. Rimuovi logs
$ git rm --cached -r logs/

# 5. Rimuovi file di sistema
$ git rm --cached .DS_Store

# 6. Crea .gitignore completo
$ cat > .gitignore << EOF
# Environment files
.env
.env.*
!.env.example

# Dependencies
node_modules/

# Build outputs
dist/
build/

# Logs
*.log
logs/

# System files
.DS_Store
Thumbs.db

# Cache
.cache/
tmp/
EOF

# 7. Committa la pulizia
$ git add .gitignore
$ git commit -m "Clean repository: remove tracked files that should be ignored

- Remove environment files (.env, .env.production)
- Remove node_modules/ directory
- Remove dist/ build outputs
- Remove log files
- Remove system files (.DS_Store)
- Add comprehensive .gitignore"

# 8. Verifica
$ git ls-files
src/index.js
package.json
README.md
.gitignore

$ git status --ignored
On branch main
Ignored files:
  .env
  node_modules/
  dist/
  logs/
  .DS_Store
```
</details>

## 💡 Best Practices

### 1. **Sempre Backup Prima**
```bash
# Tag di backup
$ git tag backup-$(date +%Y%m%d)

# Branch di backup
$ git checkout -b backup-branch
$ git checkout main
```

### 2. **Pulizia Graduale**
```bash
# Non tutto insieme - fai piccoli commit
$ git rm --cached .env
$ git commit -m "Stop tracking .env"

$ git rm --cached -r node_modules/
$ git commit -m "Stop tracking node_modules"
```

### 3. **Comunicazione Team**
```bash
# Messaggio commit chiaro
$ git commit -m "BREAKING: Stop tracking build outputs

- Removed dist/ from tracking
- Updated .gitignore
- Team: run 'git clean -fd' after pulling"
```

### 4. **Verifica Post-Pulizia**
```bash
# Script di verifica
$ git ls-files | grep -E '\.(env|log|cache)$|node_modules|dist/' && echo "❌ Cleanup incompleto" || echo "✅ Cleanup ok"
```

---

**Prossimo:** [Esempi Pratici](../esempi/01-progetto-web.md) per vedere .gitignore in azione!
