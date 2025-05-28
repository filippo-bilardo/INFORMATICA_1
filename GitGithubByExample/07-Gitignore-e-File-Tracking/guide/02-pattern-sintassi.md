# Pattern e Sintassi .gitignore

## 📖 Sintassi Base

Il file `.gitignore` utilizza pattern per specificare quali file ignorare. Comprendere questi pattern è essenziale per creare regole efficaci.

### 🎯 Regole Fondamentali

```gitignore
# Una regola per riga
file.txt
another-file.log

# Le righe vuote sono ignorate


# I commenti iniziano con #
# Questo è un commento

# Negazione con !
*.log
!important.log    # Eccezione: NON ignorare questo file
```

## 🔍 Wildcard e Pattern

### 1. **Asterisco (*) - Wildcard Base**
```gitignore
# Ignora tutti i file .log
*.log

# Ignora tutti i file che iniziano con "temp"
temp*

# Ignora tutti i file che finiscono con ".tmp"
*.tmp

# Esempi di file che matchano:
# error.log, debug.log, application.log
# temp1.txt, temporary.js, temp_backup.sql
# data.tmp, cache.tmp, session.tmp
```

### 2. **Doppio Asterisco (**) - Ricorsivo**
```gitignore
# Ignora tutti i .log in qualsiasi subdirectory
**/*.log

# Ignora directory "node_modules" ovunque
**/node_modules/

# Esempi che matchano:
# src/logs/error.log
# tests/unit/debug.log
# frontend/node_modules/
# backend/services/node_modules/
```

### 3. **Punto Interrogativo (?) - Singolo Carattere**
```gitignore
# File con un singolo carattere prima di .log
?.log

# File config seguiti da un numero singolo
config?.ini

# Esempi che matchano:
# a.log, 1.log, x.log (ma non aa.log)
# config1.ini, config2.ini (ma non config10.ini)
```

### 4. **Parentesi Quadre [] - Set di Caratteri**
```gitignore
# File che iniziano con una lettera
[a-z]*.txt

# File che iniziano con un numero
[0-9]*.log

# File con estensioni specifiche
*.[ch]  # .c o .h

# Esempi che matchano:
# report.txt, summary.txt (ma non Report.txt)
# 1_error.log, 5_debug.log
# main.c, header.h
```

## 📁 Pattern per Directory

### 1. **Directory con Slash Finale**
```gitignore
# Ignora SOLO le directory con questo nome
build/
dist/
node_modules/

# Senza slash ignorerebbe anche file con lo stesso nome
build     # Ignora file E directory chiamati "build"
build/    # Ignora SOLO directory chiamate "build"
```

### 2. **Directory Specifiche vs Ovunque**
```gitignore
# Directory nella root del repository
/build/

# Directory ovunque nel repository
build/
**/build/

# Subdirectory specifica
src/build/
```

## 🎯 Pattern Avanzati

### 1. **Combinazioni Complesse**
```gitignore
# Tutti i file .js in directory dist ovunque
**/dist/**/*.js

# File di backup numerati
*_backup_[0-9]*.sql

# File temporanei con timestamp
temp_*_[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9].tmp
```

### 2. **Esclusioni con Negazione (!)**
```gitignore
# Ignora tutti i file .log
*.log

# ECCETTO questi importanti
!error.log
!application.log

# Ignora tutto in tmp/ tranne un file specifico
tmp/*
!tmp/important.txt

# Pattern complesso: ignora tutto in build/ eccetto i .map
build/*
!build/**/*.map
```

### 3. **Pattern Condizionali**
```gitignore
# Directory diverse per ambiente
/development/
/staging/
!/production/

# File di configurazione per ambiente
config.*
!config.production.*
```

## 📝 Esempi Pratici per Linguaggio

### JavaScript/Node.js
```gitignore
# Dipendenze
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# File di build
/dist
/build

# Cache
.npm
.eslintcache

# Environment
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# OS generated
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
```

### Python
```gitignore
# Byte-compiled / optimized / DLL files
__pycache__/
*.py[cod]
*$py.class

# Distribution / packaging
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

# Virtual environments
venv/
env/
ENV/
.venv
.ENV

# IDEs
.vscode/
.idea/
*.swp
*.swo
*~
```

### Java
```gitignore
# Compiled class files
*.class

# Package files
*.jar
*.war
*.ear

# Maven
target/
pom.xml.tag
pom.xml.releaseBackup
pom.xml.versionsBackup
pom.xml.next
release.properties

# Gradle
.gradle
build/

# IDE
.idea/
*.iml
.project
.classpath
.settings/
```

## 🔧 Pattern Debugging

### 1. **Testare Pattern**
```bash
# Verificare se un file è ignorato
$ git check-ignore -v path/to/file.txt
.gitignore:15:*.txt    path/to/file.txt

# Testare pattern specifico
$ git ls-files --others --ignored --exclude-standard
```

### 2. **Pattern Non Funzionanti**
```gitignore
# ❌ PROBLEMI COMUNI

# Spazi in eccesso
*.log   # ← Spazio finale invisibile!

# Slash errata per directory
node_modules\    # ❌ Backslash su Unix
node_modules/    # ✅ Forward slash

# Pattern troppo generale
*                # ❌ Ignora TUTTO!
```

### 3. **Ordine delle Regole**
```gitignore
# L'ORDINE CONTA per le negazioni!

# ✅ CORRETTO
*.log          # Prima ignora tutti i .log
!important.log # Poi riammetti questo

# ❌ SBAGLIATO
!important.log # Non funziona se non c'è nulla da negare
*.log          # Questa sovrascrive la precedente
```

## 🧪 Esercizi Pattern

### Esercizio 1: File Temporanei
Crea pattern per ignorare:
- Tutti i file che finiscono con `.tmp`
- File che iniziano con `temp_` e hanno qualsiasi estensione
- File `.backup` ma non `database.backup`

<details>
<summary>💡 Soluzione</summary>

```gitignore
# File temporanei
*.tmp
temp_*
*.backup
!database.backup
```
</details>

### Esercizio 2: Struttura Progetto
Ignora:
- Directory `build` ovunque nel progetto
- File `.env` solo nella root
- Tutti i `.log` eccetto `application.log`

<details>
<summary>💡 Soluzione</summary>

```gitignore
# Build directories ovunque
**/build/

# Environment solo nella root
/.env

# Log files con eccezione
*.log
!application.log
```
</details>

### Esercizio 3: Pattern Avanzato
Crea pattern per:
- Ignorare tutti i file in `cache/` eccetto i `.json`
- File numerati come `backup_001.sql`, `backup_002.sql`
- Directory `test` ma non il file `test.js`

<details>
<summary>💡 Soluzione</summary>

```gitignore
# Cache directory eccetto JSON
cache/*
!cache/*.json

# Backup numerati
backup_[0-9][0-9][0-9].sql

# Directory test (non il file)
test/
```
</details>

## 🧪 Quiz Avanzato

### Domanda 1
Quale pattern ignora tutti i file `.js` nelle directory `dist` ovunque nel repository?
- A) `dist/*.js`
- B) `**/dist/*.js`
- C) `dist/**/*.js`
- D) `**/dist/**/*.js`

### Domanda 2
Come ignorare tutti i file `.log` eccetto `error.log`?
- A) `*.log && !error.log`
- B) `*.log; !error.log`
- C) `*.log` poi `!error.log` su righe separate
- D) `*.log !error.log`

### Domanda 3
Cosa fa il pattern `build/*`?
- A) Ignora la directory `build`
- B) Ignora tutto dentro `build` ma non `build` stesso
- C) Ignora file che iniziano con `build`
- D) Ignora solo i file nella directory `build`

## 💡 Best Practices Pattern

### 1. **Specifici vs Generali**
```gitignore
# ✅ MEGLIO - Specifico
/node_modules/
/dist/
/.env

# ❌ EVITARE - Troppo generale
node_modules
dist
.env
```

### 2. **Documentazione dei Pattern**
```gitignore
# === DEPENDENCIES ===
node_modules/
vendor/

# === BUILD OUTPUTS ===
dist/
build/
*.min.js

# === ENVIRONMENT ===
.env
.env.local

# === SYSTEM FILES ===
.DS_Store
Thumbs.db
```

### 3. **Pattern Progressivi**
```gitignore
# Inizia generale
*.log

# Aggiungi eccezioni se necessario
!important.log
!error.log

# Affina ulteriormente se serve
temp/*
!temp/README.md
```

---

**Prossimo:** [Template e Best Practices](./03-template-best-practices.md) per configurazioni pronte all'uso!
