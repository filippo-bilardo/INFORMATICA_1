# 02 - Pattern Avanzati e Casi Specifici

## 🎯 Obiettivo
Padroneggiare i pattern avanzati di `.gitignore` per gestire scenari complessi e casi edge.

## 📋 Prerequisiti
- Completato esercizio 01
- Familiarità con regex di base
- Comprensione dei glob patterns

## ⏱️ Tempo Stimato
45-60 minuti

## 🚀 Setup Iniziale

```bash
mkdir advanced-gitignore-patterns
cd advanced-gitignore-patterns
git init
echo "# Advanced Gitignore Patterns" > README.md
git add README.md
git commit -m "Initial commit"
```

## 📝 Esercizio 1: Pattern con Wildcards

### Crea struttura di test:

```bash
# Crea diversi file con estensioni simili
echo "Code file" > app.js
echo "Minified code" > app.min.js
echo "Source map" > app.js.map
echo "Backup" > app.js.backup

echo "Style file" > style.css
echo "Minified style" > style.min.css
echo "SCSS source" > style.scss
echo "CSS map" > style.css.map

# File con nomi pattern
echo "Test 1" > test_001.log
echo "Test 2" > test_002.log
echo "Test 3" > test_abc.log
echo "Important" > test_final.txt
```

### Crea .gitignore con pattern avanzati:

```gitignore
# Ignora file minificati
*.min.js
*.min.css

# Ignora source maps
*.map

# Ignora file numerici di test
test_[0-9][0-9][0-9].log

# Ignora backup solo con estensione specifica
*.js.backup
```

### Test e verifica:

```bash
git add .gitignore
git commit -m "Add advanced patterns"
git status
```

**Verifica che siano tracciabili**:
- ✅ `app.js`, `style.css`, `style.scss`, `test_final.txt`

**Verifica che siano ignorati**:
- ❌ `app.min.js`, `style.min.css`, `app.js.map`, `style.css.map`
- ❌ `test_001.log`, `test_002.log`, `test_abc.log`
- ❌ `app.js.backup`

## 📝 Esercizio 2: Negazioni e Eccezioni

### Setup:

```bash
# Crea struttura di configurazioni
mkdir config
echo "secret=abc123" > config/database.conf
echo "host=localhost" > config/database.example.conf
echo "debug=true" > config/app.conf
echo "port=3000" > config/app.example.conf

# Crea log di diversi tipi
mkdir logs
echo "Error log" > logs/error.log
echo "Access log" > logs/access.log
echo "Important log" > logs/important.log
echo "Keep this" > logs/keep.log
```

### Pattern con negazioni:

```gitignore
# Ignora tutti i file di config
config/*.conf

# MA mantieni gli esempi
!config/*.example.conf

# Ignora tutti i log
logs/*.log

# MA mantieni file specifici
!logs/important.log
!logs/keep.log
```

### Test:

```bash
git add .
git status
```

**Dovrebbero essere tracciabili**:
- ✅ `config/database.example.conf`, `config/app.example.conf`
- ✅ `logs/important.log`, `logs/keep.log`

**Dovrebbero essere ignorati**:
- ❌ `config/database.conf`, `config/app.conf`
- ❌ `logs/error.log`, `logs/access.log`

## 📝 Esercizio 3: Directory Specifiche

### Setup:

```bash
# Crea struttura multi-progetto
mkdir -p frontend/src
mkdir -p frontend/build
mkdir -p backend/src
mkdir -p backend/target
mkdir -p docs/build
mkdir -p shared/utils

# Crea file in diverse directory
echo "Frontend source" > frontend/src/App.js
echo "Frontend build" > frontend/build/bundle.js
echo "Backend source" > backend/src/Main.java
echo "Backend build" > backend/target/app.jar
echo "Docs build" > docs/build/index.html
echo "Shared utility" > shared/utils/helper.js

# Crea file build anche in root
echo "Root build file" > build.txt
```

### Pattern per directory specifiche:

```gitignore
# Ignora build solo in frontend
frontend/build/

# Ignora target solo in backend
backend/target/

# Ignora build in docs ma NON in altre posizioni
docs/build/

# File build specifici (ovunque)
*.jar

# MA non file build generici
# build.txt sarà tracciato
```

### Test directory patterns:

```bash
git add .
git status
```

## 📝 Esercizio 4: Pattern Complessi per Progetti Reali

### Setup progetto Node.js + Python:

```bash
# Struttura Node.js
mkdir -p nodejs/node_modules/package
echo "dependency" > nodejs/node_modules/package/index.js
echo "module.exports = {}" > nodejs/package.json

# File npm
echo "lock file" > nodejs/package-lock.json
echo "yarn lock" > nodejs/yarn.lock

# Struttura Python
mkdir -p python/__pycache__
echo "cached" > python/__pycache__/module.cpython-39.pyc
echo "print('hello')" > python/app.py
echo "coverage data" > python/.coverage

# Virtual environment
mkdir -p python/venv/lib
echo "venv files" > python/venv/lib/python.so

# IDE files
mkdir -p .vscode
mkdir -p .idea
echo "vscode config" > .vscode/launch.json
echo "idea config" > .idea/workspace.xml
```

### Gitignore completo:

```gitignore
# Dependency directories
node_modules/
*/node_modules/

# Package manager files
package-lock.json
yarn.lock
npm-debug.log*

# Python
__pycache__/
*.pyc
*.pyo
*.pyd
.Python
.coverage
.pytest_cache/

# Virtual environments
venv/
env/
ENV/

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# OS generated files
.DS_Store
Thumbs.db

# Build outputs
build/
dist/
*.egg-info/
```

## 📝 Esercizio 5: Performance e Pattern Ottimizzati

### Test performance con molti file:

```bash
# Crea molti file per test performance
mkdir performance_test
cd performance_test

# Script per creare 1000 file
for i in {1..1000}; do
    echo "content $i" > "file_$i.tmp"
    echo "log entry $i" > "log_$i.log"
    echo "cache $i" > "cache_$i.cache"
done

cd ..
```

### Pattern ottimizzati:

```gitignore
# Pattern ottimizzato per molti file
performance_test/*.tmp
performance_test/*.log
performance_test/*.cache

# INVECE DI pattern più lenti come:
# performance_test/**/temp*
# performance_test/**/*.tmp
```

### Misura performance:

```bash
# Test con gitignore
time git status

# Test senza alcuni pattern (commenta nel .gitignore)
time git status
```

## 📝 Esercizio 6: Troubleshooting Patterns

### Setup problemi comuni:

```bash
# File che causano problemi
echo "already tracked" > tracked_file.log
git add tracked_file.log
git commit -m "Add file that will be ignored later"

# Aggiungi al gitignore
echo "tracked_file.log" >> .gitignore

# Crea spazi nei nomi
touch "file with spaces.tmp"
mkdir "dir with spaces"
echo "content" > "dir with spaces/file.log"
```

### Debug patterns:

```bash
# Controlla se un file è ignorato
git check-ignore -v tracked_file.log
git check-ignore -v "file with spaces.tmp"

# Lista tutti i file ignorati
git ls-files --others --ignored --exclude-standard

# Vedi quali file Git traccia
git ls-files

# Check pattern specifico
git check-ignore -v "dir with spaces/file.log"
```

### Risolvi problemi:

```bash
# Rimuovi file già tracciato dal tracking
git rm --cached tracked_file.log
git commit -m "Remove previously tracked file"

# Pattern per spazi nei nomi
echo '"file with spaces.tmp"' >> .gitignore
echo '"dir with spaces/"' >> .gitignore
```

## 🧪 Test Cases Avanzati

### Test Case 1: Gitignore Nidificati

```bash
# Crea sottodirectory con proprio gitignore
mkdir subproject
echo "*.temp" > subproject/.gitignore
echo "temp content" > subproject/local.temp
echo "other content" > subproject/other.file

# Il gitignore locale sovrascrive quello globale
```

### Test Case 2: Gitignore in Subdirectory

```bash
mkdir -p project/module
echo "module-specific.ignore" > project/module/.gitignore
echo "content" > project/module/module-specific.ignore
echo "content" > project/module/regular.file
```

### Test Case 3: Pattern Order Matters

```gitignore
# L'ordine è importante!
# Questo IGNORA tutto in temp/
temp/

# Questo cerca di INCLUDERE alcuni file, ma non funziona
# perché temp/ li ha già esclusi tutti
!temp/important.txt

# SOLUZIONE corretta:
# temp/*
# !temp/important.txt
```

## ✅ Checklist Competenze Avanzate

- [ ] Pattern con wildcards (`*`, `?`, `[...]`)
- [ ] Negazioni funzionanti (`!pattern`)
- [ ] Directory specifiche vs globali
- [ ] Pattern ottimizzati per performance
- [ ] Debug con `git check-ignore`
- [ ] Gestione file con spazi nei nomi
- [ ] Comprensione dell'ordine dei pattern
- [ ] Gitignore nidificati
- [ ] Risoluzione di file già tracciati

## 🎯 Challenge Finale

Crea un `.gitignore` per un progetto che include:

1. **Frontend React/Vue**: `node_modules`, build artifacts, cache
2. **Backend Java**: `.class`, target directory, IDE files
3. **Database**: dump files, ma mantieni schema examples
4. **Docker**: ignore containers, mantieni Dockerfiles
5. **CI/CD**: ignore pipeline artifacts, mantieni configs
6. **Documentazione**: ignore generated docs, mantieni sources

## 📚 Pattern Reference Quick

```gitignore
# Basic patterns
*.log                # All .log files
temp/               # temp directory and contents
/root-only.txt      # Only in repository root
**/global.txt       # In any subdirectory
dir/**/file.txt     # In any subdirectory of dir

# Character classes
[Tt]emp             # Temp or temp
[0-9]*.log          # Starts with digit
[!0-9]*.log         # Doesn't start with digit

# Negation
build/              # Ignore build directory
!build/README.md    # But keep this file

# Escaping
\#hashtag           # Literal # character
\!important         # Literal ! character
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Creazione e Test Gitignore](01-creazione-test-gitignore.md)
- [➡️ Modulo 08 - Visualizzare Storia Commit](../../08-Visualizzare-Storia-Commit/README.md)
