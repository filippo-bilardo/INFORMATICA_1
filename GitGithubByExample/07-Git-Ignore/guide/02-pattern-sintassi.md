# Pattern e Sintassi di .gitignore

## 🎯 Sintassi Fondamentale

Il file `.gitignore` usa una sintassi basata su pattern glob con alcune estensioni specifiche di Git.

## 📝 Regole Base

### 1. Una Regola per Riga
```gitignore
# Ogni riga è una regola separata
*.log
temp/
.env
```

### 2. Commenti
```gitignore
# Questo è un commento
*.log         # Commento alla fine della riga
# TODO: Aggiungere pattern per IDE
```

### 3. Righe Vuote
```gitignore
# Dependencies
node_modules/

# Logs (riga vuota per organizzazione)
*.log
debug.log
```

### 4. Escape di Caratteri Speciali
```gitignore
# Per file che iniziano con #
\#filename

# Per file che iniziano con !
\!important.txt
```

## 🔍 Tipi di Pattern

### 1. Nome File Esatto
```gitignore
# File specifici
README.txt
config.json
database.db
```

### 2. Estensioni con Wildcard
```gitignore
# Tutti i file con estensione .log
*.log

# Tutti i file .tmp in qualsiasi directory
**/*.tmp

# File che iniziano con "temp"
temp*

# File che finiscono con ".backup"
*.backup
```

### 3. Directory
```gitignore
# Directory (nota la / finale)
logs/
build/
node_modules/

# Equivalente senza /
logs
build
node_modules
```

### 4. Pattern con Directory Specifiche
```gitignore
# Solo nella root del progetto
/logs

# In qualsiasi sottodirectory
logs/

# Pattern combinati
src/build/
**/temp/
```

## 🔧 Caratteri Jolly e Pattern Avanzati

### Asterisco (*) - Wildcard Base
```gitignore
# Qualsiasi carattere eccetto /
*.txt          # tutti i file .txt
temp*          # file che iniziano con "temp"
*debug*        # file che contengono "debug"
```

### Doppio Asterisco (**) - Wildcard Ricorsivo
```gitignore
# Attraversa qualsiasi numero di directory
**/logs        # cartella logs a qualsiasi livello
src/**/*.js    # tutti i file .js sotto src/
**/*.log       # tutti i file .log in tutto il progetto
```

### Punto Interrogativo (?) - Carattere Singolo
```gitignore
# Un singolo carattere
file?.txt      # file1.txt, fileA.txt, ma non file10.txt
log.?          # log.1, log.2, log.a
```

### Parentesi Quadre ([]) - Set di Caratteri
```gitignore
# Qualsiasi carattere nel set
*.[oa]         # file .o e .a
*.[0-9]        # file con numeri finali
log.[a-z]      # log.a, log.b, ... log.z
log.[!0-9]     # log con carattere finale NON numerico
```

## ❗ Pattern di Negazione

### Sintassi con !
```gitignore
# Ignora tutti i file .txt
*.txt

# MA non ignorare important.txt
!important.txt
```

### Esempi Complessi di Negazione
```gitignore
# Ignora tutta la cartella build/
build/

# Ma mantieni build/README.md
!build/README.md

# Ignora tutti i log
*.log

# Ma mantieni i log di produzione
!production.log
!error.log
```

### ⚠️ Limitazioni della Negazione
```gitignore
# ❌ QUESTO NON FUNZIONA
# Se ignori una directory, non puoi "de-ignorare" file al suo interno
logs/
!logs/important.log    # Non funziona!

# ✅ SOLUZIONE: Sii più specifico
logs/*.log             # Ignora solo i file .log
!logs/important.log    # Mantieni questo specifico file
```

## 📂 Pattern per Directory

### Directory vs File
```gitignore
# Ignora la directory "temp"
temp/

# Ignora il file "temp" (senza /)
temp

# Ignora entrambi
temp
temp/
```

### Pattern di Directory Complessi
```gitignore
# Ignora build/ solo nella root
/build/

# Ignora build/ ovunque
build/

# Ignora src/build/ specificamente
src/build/

# Ignora qualsiasi cartella che finisce con _build
*_build/

# Ignora directory a più livelli
**/target/classes/
```

## 🎨 Pattern per Tipi di File Comuni

### File di Codice
```gitignore
# File temporanei di editor
*.swp
*.swo
*~
.#*

# File di backup
*.bak
*.backup
*.orig
```

### File di Sistema
```gitignore
# macOS
.DS_Store
.AppleDouble
.LSOverride

# Windows
Thumbs.db
ehthumbs.db
Desktop.ini

# Linux
*~
.directory
```

### File di Build
```gitignore
# Java
*.class
*.jar
target/

# C/C++
*.o
*.so
*.exe

# Python
*.pyc
__pycache__/
dist/

# JavaScript/Node.js
node_modules/
npm-debug.log
dist/
build/
```

## 🧩 Pattern Combinati Avanzati

### Pattern Multi-livello
```gitignore
# Tutti i file di test tranne quelli in src/
test/**
!src/test/**

# Tutti i file .config tranne quello principale
*.config
!app.config
```

### Pattern Condizionali
```gitignore
# File temporanei solo in certe directory
temp/*.tmp
cache/*.cache
logs/*.log

# Ma non in directory speciali
!docs/temp/*.tmp
!examples/cache/*.cache
```

### Pattern per Ambienti
```gitignore
# File di ambiente
.env
.env.*

# Ma mantieni i template
!.env.template
!.env.example
```

## 🔬 Testing dei Pattern

### Comando check-ignore
```bash
# Testa un singolo file
git check-ignore file.txt

# Testa con dettagli verbose
git check-ignore -v file.txt

# Testa più file
git check-ignore file1.txt file2.log folder/

# Testa tutti i file in una directory
git check-ignore src/**
```

### Script di Test
```bash
#!/bin/bash
# test-gitignore.sh

echo "Testing .gitignore patterns..."

files=(
    "app.log"
    "src/debug.log"
    "build/app.js"
    "node_modules/package.json"
    "important.txt"
)

for file in "${files[@]}"; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "✓ IGNORED: $file"
    else
        echo "✗ TRACKED: $file"
    fi
done
```

## 📊 Esempi Pratici Completi

### Progetto Web Completo
```gitignore
# Dependencies
node_modules/
bower_components/

# Build outputs
build/
dist/
*.min.js
*.min.css

# Logs
logs/
*.log
npm-debug.log*

# Runtime data
pids/
*.pid
*.seed

# Coverage directory used by tools like istanbul
coverage/

# Environment variables
.env
.env.local
.env.development
.env.production

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Temporary files
*.tmp
temp/
.cache/
```

### Progetto Multi-linguaggio
```gitignore
# === JAVA ===
*.class
*.jar
*.war
target/
.gradle/

# === PYTHON ===
__pycache__/
*.pyc
*.pyo
venv/
env/

# === JAVASCRIPT ===
node_modules/
npm-debug.log

# === C/C++ ===
*.o
*.so
*.exe

# === GENERAL ===
# Logs
*.log

# IDE
.vscode/
.idea/

# OS
.DS_Store
Thumbs.db

# Secrets
.env
*.key
credentials.*

# Temp
*.tmp
temp/
cache/
```

## 🧪 Esercizio di Pattern

Crea questi file e testa i pattern:

```bash
# Setup test
mkdir pattern-test
cd pattern-test
git init

# Crea struttura di test
mkdir -p {src,build,logs,temp}
touch {app.js,app.min.js}
touch {debug.log,error.log,important.log}
touch {src/component.js,src/component.test.js}
touch {build/app.js,build/styles.css}
touch .env
touch .env.example

# Crea .gitignore con pattern complessi
cat > .gitignore << 'EOF'
# Build files
*.min.*
build/

# Logs (ma mantieni important.log)
*.log
!important.log

# Environment (ma mantieni example)
.env*
!.env.example

# Test in src/ (ma non altrove)
src/**/*.test.*
EOF

# Testa i pattern
git add .
git status
```

## 🎯 Quiz di Verifica

1. **Qual è la differenza tra `*.log` e `**/*.log`?**
2. **Come ignori tutti i file .env eccetto .env.example?**
3. **Cosa fa il pattern `src/**/test/`?**

**Risposte:**
1. `*.log` ignora file .log solo nella directory corrente, `**/*.log` li ignora ovunque
2. `.env*` e poi `!.env.example`
3. Ignora qualsiasi directory "test" sotto src/ a qualsiasi livello

## 🔗 Prossimi Passi

- [← Introduzione](./01-introduzione-gitignore.md)
- [Gitignore Globale e Locale →](./03-globale-locale.md)
- [Esempi Pratici →](../esempi/01-setup-nodejs.md)

---

> 💡 **Suggerimento**: Usa sempre `git check-ignore -v` per debuggare pattern che non funzionano come aspettato!
