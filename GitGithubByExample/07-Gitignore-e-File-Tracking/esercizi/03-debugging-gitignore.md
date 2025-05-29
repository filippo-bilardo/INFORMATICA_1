# Esercizio 03: Debugging Gitignore

## 🎯 Obiettivo
Imparare a diagnosticare e risolvere problemi comuni con `.gitignore`, inclusi conflitti di pattern, precedenze e debug di file che non vengono ignorati correttamente.

## 📋 Prerequisiti
- Completamento esercizi precedenti
- Conoscenza pattern `.gitignore`
- Familiarità con comandi Git di base

## 🚨 Scenario: Repository con Problemi
Ti è stato assegnato un repository con diversi problemi di `.gitignore`. Alcuni file che dovrebbero essere ignorati vengono tracciati, altri che dovrebbero essere tracciati vengono ignorati.

## 📝 Parte 1: Setup Scenario Problematico

### 1.1 Creare Repository di Test
```bash
mkdir ~/debug-gitignore-exercise
cd ~/debug-gitignore-exercise
git init

# Crea struttura problematica
mkdir -p src/{components,utils,config}
mkdir -p tests/{unit,integration}
mkdir -p logs/{app,debug,error}
mkdir -p node_modules/express
mkdir -p coverage/{lcov,html}
mkdir -p .vscode
```

### 1.2 Creare File di Test
```bash
# File legittimi del progetto
echo 'console.log("main app");' > src/app.js
echo 'export default function Component() {}' > src/components/Header.js
echo 'export const utils = {};' > src/utils/helpers.js
echo 'module.exports = {port: 3000};' > src/config/app.js

# File di test
echo 'test("should work", () => {});' > tests/unit/app.test.js
echo 'test("integration", () => {});' > tests/integration/api.test.js

# File che dovrebbero essere ignorati ma non lo sono
echo 'error log content' > logs/app/error.log
echo 'debug information' > logs/debug/debug.log
echo 'app log content' > logs/error/app.log

# Dipendenze (dovrebbero essere ignorate)
echo 'express module' > node_modules/express/index.js

# Coverage (dovrebbe essere ignorato)
echo 'coverage data' > coverage/lcov/lcov.info
echo '<html>coverage</html>' > coverage/html/index.html

# File IDE (dovrebbero essere ignorati)
echo '{"workspaceFolder": ""}' > .vscode/settings.json

# File di configurazione sensibili
echo 'API_KEY=secret123' > .env
echo 'DB_PASSWORD=secret' > .env.local

# File importanti ma con nomi che potrebbero confondere
echo 'module.exports = {test: true};' > src/config/test.config.js
echo 'module.exports = {prod: true};' > src/config/production.config.js
echo 'module.exports = {local: true};' > src/config/local.config.js  # Questo dovrebbe essere ignorato
```

### 1.3 Gitignore Iniziale (Problematico)
```bash
cat > .gitignore << 'EOF'
# Questo .gitignore ha diversi problemi
node_modules
logs
coverage
.env
*.config.js
.vscode
EOF
```

### 1.4 Commit Iniziale (Problematico)
```bash
# Aggiungi tutto forzatamente (simula errori passati)
git add -A
git commit -m "initial commit with problems"
```

## 📝 Parte 2: Diagnosticare i Problemi

### 2.1 Identificare File Tracciati che Non Dovrebbero
```bash
# Vedi tutti i file tracciati
git ls-files

# Dovresti vedere file problematici come:
# - logs/app/error.log (dovrebbe essere ignorato)
# - coverage/lcov/lcov.info (dovrebbe essere ignorato)
# - .vscode/settings.json (dovrebbe essere ignorato)
# - src/config/test.config.js (dovrebbe essere tracciato!)
```

### 2.2 Identificare File che Dovrebbero Essere Tracciati
```bash
# Crea nuovo file di configurazione importante
echo 'module.exports = {api: "v1"};' > src/config/api.config.js

# Verifica se viene ignorato per errore
git status
# Se non appare, è ignorato per errore dal pattern *.config.js
```

### 2.3 Debug con git check-ignore
```bash
# Verifica perché file specifici sono ignorati
git check-ignore -v src/config/api.config.js
# Output: .gitignore:5:*.config.js    src/config/api.config.js

git check-ignore -v logs/app/error.log
# Non dovrebbe dare output se il file è già tracciato

# Verifica file che dovrebbero essere ignorati
git check-ignore -v .vscode/settings.json
```

## 📝 Parte 3: Correggere i Problemi

### 3.1 Analizzare Pattern Problematici
```bash
# Il problema principale: *.config.js è troppo generico
# Ignora anche file legittimi come test.config.js e api.config.js
```

### 3.2 Correggere .gitignore
```bash
cat > .gitignore << 'EOF'
# === DIPENDENZE ===
node_modules/

# === LOGS ===
logs/

# === COVERAGE ===
coverage/

# === ENVIRONMENT VARIABLES ===
.env
.env.*

# === CONFIG LOCALE (SPECIFICO) ===
src/config/local.config.js
src/config/*.local.js
config/local.*

# === IDE ===
.vscode/
.idea/

# === CACHE ===
.cache/
.npm/
.eslintcache

# === BUILD ===
dist/
build/

# === SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db
*.tmp
*~
EOF
```

### 3.3 Rimuovere File già Tracciati
```bash
# Rimuovi file che ora dovrebbero essere ignorati
git rm --cached logs/app/error.log
git rm --cached logs/debug/debug.log
git rm --cached logs/error/app.log
git rm --cached coverage/lcov/lcov.info
git rm --cached coverage/html/index.html
git rm --cached .vscode/settings.json

# Rimuovi solo il file di config locale (non tutti)
git rm --cached src/config/local.config.js

# Commit le rimozioni
git commit -m "fix: remove incorrectly tracked files from git"
```

### 3.4 Aggiungere File che Ora Dovrebbero Essere Tracciati
```bash
# Ora i file config legittimi possono essere aggiunti
git add src/config/api.config.js
git add src/config/test.config.js
git add src/config/production.config.js
git commit -m "feat: add legitimate config files"
```

## 📝 Parte 4: Test e Verifica

### 4.1 Test Completo
```bash
# Crea nuovi file per testare
echo 'new error' > logs/app/new-error.log
echo 'new debug' > logs/debug/new-debug.log
echo 'new module' > node_modules/express/new-file.js
echo 'new coverage' > coverage/lcov/new.info
echo 'local config' > src/config/another-local.config.js
echo 'test config' > src/config/test2.config.js

# Verifica status
git status

# Dovresti vedere solo src/config/test2.config.js
# Gli altri dovrebbero essere ignorati
```

### 4.2 Verifica Pattern Specifici
```bash
# Test pattern per file config
git check-ignore -v src/config/local.config.js          # Dovrebbe essere ignorato
git check-ignore -v src/config/production.config.js     # NON dovrebbe essere ignorato
git check-ignore -v src/config/api.config.js           # NON dovrebbe essere ignorato

# Test pattern per logs
git check-ignore -v logs/app/any-file.log              # Dovrebbe essere ignorato

# Test pattern per coverage
git check-ignore -v coverage/html/report.html          # Dovrebbe essere ignorato
```

## 📝 Parte 5: Scenario Avanzato - Precedenze

### 5.1 Pattern con Precedenze
```bash
# Crea scenario complesso
mkdir -p docs/important
echo 'important doc' > docs/important/config.md
echo 'regular doc' > docs/readme.md

# Aggiungi pattern con precedenze al .gitignore
cat >> .gitignore << 'EOF'

# === DOCS (con eccezioni) ===
docs/
!docs/important/
!docs/important/*
EOF
```

### 5.2 Test Precedenze
```bash
git status
# docs/important/config.md dovrebbe apparire
# docs/readme.md dovrebbe essere ignorato
```

### 5.3 Debug Precedenze
```bash
git check-ignore -v docs/readme.md
git check-ignore -v docs/important/config.md

# Il secondo comando non dovrebbe dare output (file non ignorato)
```

## 📝 Parte 6: Troubleshooting Avanzato

### 6.1 Cache Git Problems
```bash
# Se i file continuano a essere tracciati dopo aver aggiornato .gitignore
git rm -r --cached .
git add .
git commit -m "fix: refresh git cache for gitignore changes"
```

### 6.2 Gitignore non Funziona
```bash
# Verifica che .gitignore sia tracciato
git ls-files | grep .gitignore

# Se non è tracciato, aggiungilo
git add .gitignore
git commit -m "add .gitignore"
```

### 6.3 Pattern Testing Tool
```bash
# Crea uno script per testare pattern
cat > test-gitignore.sh << 'EOF'
#!/bin/bash
echo "=== TESTING GITIGNORE PATTERNS ==="
for file in $(find . -type f -not -path './.git/*'); do
    if git check-ignore -q "$file"; then
        echo "IGNORED: $file"
    else
        echo "TRACKED: $file"
    fi
done
EOF

chmod +x test-gitignore.sh
./test-gitignore.sh
```

## 📝 Parte 7: Best Practices Debugging

### 7.1 Gitignore Validation
```bash
# Verifica sintassi e pattern
git status --ignored --porcelain | head -10

# Mostra tutti i file ignorati
git ls-files --others --ignored --exclude-standard
```

### 7.2 Documentation dei Pattern
```bash
# Aggiungi commenti esplicativi al .gitignore
cat > .gitignore << 'EOF'
# ===================================
# GITIGNORE DOCUMENTATION
# ===================================

# === DIPENDENZE ===
# Ignora tutte le dipendenze npm
node_modules/

# === CONFIGURAZIONI SENSIBILI ===
# File di environment con credenziali
.env
.env.*

# === CONFIGURAZIONI LOCALI ===
# Solo config locali specifiche, non tutte
src/config/local.config.js
src/config/*.local.js
# NOTA: Non usare *.config.js (troppo generico)

# === GENERATED FILES ===
# Log files generati durante l'esecuzione
logs/

# Coverage reports generati dai test
coverage/

# === IDE E EDITOR ===
.vscode/
.idea/
*.swp
*~

# === SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db
EOF
```

## ✅ Checklist Finale

### Problemi Risolti
- [x] **File config legittimi**: ora tracciati correttamente
- [x] **File config locali**: ora ignorati correttamente  
- [x] **Logs**: completamente ignorati
- [x] **Coverage**: completamente ignorato
- [x] **Node_modules**: completamente ignorato
- [x] **File IDE**: completamente ignorati
- [x] **Env files**: completamente ignorati

### Comandi Utili da Ricordare
```bash
# Debug quale pattern ignora un file
git check-ignore -v <file>

# Lista tutti i file ignorati
git ls-files --others --ignored --exclude-standard

# Rimuovi file dal tracking mantenendoli su disco
git rm --cached <file>

# Refresh completo cache git
git rm -r --cached . && git add .

# Forza aggiunta file ignorato
git add -f <file>

# Verifica file tracciati
git ls-files

# Status con file ignorati
git status --ignored
```

## 🎓 Cosa Hai Imparato
- ✅ Diagnosticare problemi comuni con `.gitignore`
- ✅ Usare `git check-ignore` per debug
- ✅ Gestire precedenze e pattern complessi
- ✅ Rimuovere file già tracciati per errore
- ✅ Creare pattern specifici invece che generici
- ✅ Documentare pattern per il team
- ✅ Troubleshooting avanzato cache Git

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Esercizio precedente](02-pattern-avanzati.md)
- [➡️ Modulo successivo](../../08-Visualizzare-Storia-Commit/README.md)
