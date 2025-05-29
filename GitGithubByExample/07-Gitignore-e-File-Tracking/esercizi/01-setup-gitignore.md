# Esercizio 01: Setup Gitignore

## 🎯 Obiettivo
Configurare correttamente un file `.gitignore` per diversi tipi di progetti e imparare a gestire i file che devono essere ignorati.

## 📋 Prerequisiti
- Git installato e configurato
- Conoscenza base dei comandi Git
- Editor di testo

## 🏁 Scenario
Sei uno sviluppatore che lavora su tre progetti diversi:
1. **Progetto Web** (HTML/CSS/JS)
2. **Progetto Node.js** (Backend JavaScript)
3. **Progetto Python** (Script automazione)

Per ognuno devi configurare un `.gitignore` appropriato.

## 📝 Parte 1: Progetto Web Frontend

### 1.1 Setup Iniziale
```bash
# Crea directory e naviga
mkdir ~/esercizio-gitignore
cd ~/esercizio-gitignore
mkdir web-project
cd web-project

# Inizializza repository
git init
```

### 1.2 Creare File di Test
```bash
# File del progetto web
echo '<!DOCTYPE html><html><head><title>Test</title></head><body><h1>Hello World</h1></body></html>' > index.html

echo 'body { font-family: Arial; }' > style.css

echo 'console.log("Hello from JavaScript");' > script.js

# File che dovrebbero essere ignorati
mkdir logs
echo 'Debug info...' > logs/debug.log
echo 'Error occurred...' > logs/error.log

# File temporanei dell'editor
echo 'temp content' > index.html~
echo 'backup content' > script.js.bak

# File dell'OS
touch .DS_Store
touch Thumbs.db

# Directory build
mkdir dist
echo 'Compiled CSS' > dist/style.min.css
echo 'Minified JS' > dist/script.min.js
```

### 1.3 Creare .gitignore per Web
```bash
# Crea il file .gitignore
cat > .gitignore << 'EOF'
# === FILE TEMPORANEI ===
*~
*.bak
*.tmp
*.swp

# === FILE SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db
ehthumbs.db

# === LOGS ===
logs/
*.log

# === DIRECTORY BUILD ===
dist/
build/
out/

# === CACHE ===
.cache/
.temp/

# === IDE ===
.vscode/
.idea/
*.sublime-*

# === NODE.JS (se usato per build tools) ===
node_modules/
npm-debug.log*
package-lock.json
EOF
```

### 1.4 Test del Gitignore
```bash
# Controlla status prima del commit
git status

# Dovresti vedere solo:
# .gitignore
# index.html
# script.js
# style.css

# Aggiungi i file validi
git add .gitignore index.html script.js style.css
git commit -m "feat: initial web project setup with gitignore"
```

### ✅ Checkpoint 1
Verifica che `git status` non mostri file in `logs/`, `dist/`, file temporanei o file OS.

## 📝 Parte 2: Progetto Node.js

### 2.1 Setup Nuovo Progetto
```bash
# Torna alla directory principale
cd ~/esercizio-gitignore
mkdir node-project
cd node-project

# Inizializza repository e progetto Node
git init
npm init -y
```

### 2.2 Creare Struttura Progetto
```bash
# File del progetto
echo 'const express = require("express");' > server.js
echo 'const config = require("./config");' > app.js

# Directory e file che dovrebbero essere ignorati
mkdir node_modules
mkdir logs
mkdir uploads
echo 'log entry' > logs/app.log

# File di ambiente (sensibili)
echo 'API_KEY=secret123' > .env
echo 'DB_PASSWORD=supersecret' > .env.local

# File di configurazione locale
mkdir config
echo 'module.exports = {db: "localhost"}' > config/database.js
echo 'module.exports = {secret: "local"}' > config/local.js

# Cache e file temporanei
mkdir .npm
mkdir coverage
echo 'coverage data' > coverage/lcov.info
```

### 2.3 Gitignore per Node.js
```bash
cat > .gitignore << 'EOF'
# === DIPENDENZE ===
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# === ENVIRONMENT VARIABLES ===
.env
.env.*
!.env.example

# === LOGS ===
logs/
*.log

# === CACHE ===
.npm/
.eslintcache
.parcel-cache

# === COVERAGE ===
coverage/
.nyc_output

# === BUILD ===
dist/
build/

# === FILE UPLOAD UTENTE ===
uploads/
!uploads/.gitkeep

# === CONFIG LOCALE ===
config/local.js
config/*.local.*

# === SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db

# === IDE ===
.vscode/
.idea/
*.swp
*.swo

# === RUNTIME ===
.pm2/
*.pid
*.seed
*.pid.lock
EOF
```

### 2.4 Aggiungere Gitkeep per Uploads
```bash
# Mantieni la directory uploads ma vuota
touch uploads/.gitkeep
```

### 2.5 Test Node.js Gitignore
```bash
git status
# Dovresti vedere:
# .gitignore
# app.js
# config/database.js
# package.json
# server.js
# uploads/.gitkeep

git add .
git commit -m "feat: setup Node.js project with comprehensive gitignore"
```

### ✅ Checkpoint 2
Verifica che file sensibili (`.env`), dipendenze (`node_modules`), e config locali non siano tracciati.

## 📝 Parte 3: Progetto Python

### 3.1 Setup Progetto Python
```bash
cd ~/esercizio-gitignore
mkdir python-project
cd python-project
git init
```

### 3.2 Creare File Python
```bash
# Script principale
cat > main.py << 'EOF'
#!/usr/bin/env python3
import os
import logging

def main():
    print("Hello from Python!")

if __name__ == "__main__":
    main()
EOF

# Modulo utilitario
echo 'def helper_function(): return "helper"' > utils.py

# File che dovrebbero essere ignorati
mkdir __pycache__
echo 'bytecode' > __pycache__/main.cpython-39.pyc
echo 'bytecode' > utils.pyc

# Virtual environment
mkdir venv
mkdir myenv

# File di log
echo 'Python log' > app.log
echo 'Debug info' > debug.log

# File IDE Python
echo 'PyCharm config' > .idea/workspace.xml

# File Jupyter
echo '{"cells": []}' > notebook.ipynb
mkdir .ipynb_checkpoints
echo 'checkpoint' > .ipynb_checkpoints/notebook-checkpoint.ipynb
```

### 3.3 Gitignore per Python
```bash
cat > .gitignore << 'EOF'
# === BYTECODE ===
__pycache__/
*.py[cod]
*$py.class
*.so

# === DISTRIBUZIONE / PACKAGING ===
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

# === VIRTUAL ENVIRONMENTS ===
venv/
env/
ENV/
env.bak/
venv.bak/
myenv/
.venv/

# === IDE ===
.idea/
.vscode/
*.swp
*.swo

# === JUPYTER NOTEBOOK ===
.ipynb_checkpoints

# === LOGS ===
*.log

# === PYTEST ===
.pytest_cache/
.coverage
htmlcov/

# === MYPY ===
.mypy_cache/
.dmypy.json
dmypy.json

# === SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db
EOF
```

### 3.4 Test Python Gitignore
```bash
git status
# Dovresti vedere solo:
# .gitignore
# main.py
# utils.py

git add .
git commit -m "feat: setup Python project with gitignore"
```

## 📝 Parte 4: Challenge Avanzato

### 4.1 File Già Tracciati
```bash
cd ~/esercizio-gitignore/node-project

# Simula errore: hai già tracciato node_modules
git add -f node_modules/
git commit -m "error: accidentally tracked node_modules"

# Ora rimuovilo dal tracking
git rm -r --cached node_modules/
git commit -m "fix: remove node_modules from tracking"

# Verifica che ora sia ignorato
touch node_modules/new-package
git status  # Non dovrebbe mostrare node_modules
```

### 4.2 Forzare Aggiunta File Ignorato
```bash
# A volte vuoi tracciare un file normalmente ignorato
echo 'important config' > config/local.js

# È ignorato, ma vuoi includerlo
git add -f config/local.js
git commit -m "feat: add important local config"
```

### 4.3 Debug Gitignore
```bash
# Verifica perché un file è ignorato
git check-ignore -v logs/app.log
# Output mostrerà quale riga del .gitignore lo ignora

# Lista tutti i file ignorati
git status --ignored
```

## ✅ Verifica Finale

### Test Checklist
Per ogni progetto, verifica:

1. **✅ File di sistema ignorati**: `.DS_Store`, `Thumbs.db`
2. **✅ File temporanei ignorati**: `*.tmp`, `*.bak`, `*~`
3. **✅ Dipendenze ignorate**: `node_modules/`, `venv/`, `__pycache__/`
4. **✅ File di build ignorati**: `dist/`, `build/`
5. **✅ File sensibili ignorati**: `.env`, config locali
6. **✅ Logs ignorati**: `*.log`, `logs/`
7. **✅ File IDE ignorati**: `.vscode/`, `.idea/`

### Comando di Verifica Globale
```bash
cd ~/esercizio-gitignore

# Per ogni progetto
for project in web-project node-project python-project; do
    echo "=== $project ==="
    cd $project
    echo "File tracciati:"
    git ls-files
    echo "File ignorati:"
    git status --ignored --porcelain | grep '^!!'
    echo ""
    cd ..
done
```

## 🎓 Conclusioni

Hai imparato a:
- ✅ Configurare `.gitignore` per diversi tipi di progetto
- ✅ Rimuovere file già tracciati per errore
- ✅ Forzare l'aggiunta di file normalmente ignorati
- ✅ Debuggare problemi con `.gitignore`
- ✅ Usare pattern avanzati e best practices

## 📚 Risorse Aggiuntive
- [GitHub gitignore templates](https://github.com/github/gitignore)
- [gitignore.io](https://gitignore.io) - Generatore online
- [Git documentation](https://git-scm.com/docs/gitignore)

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Guide teoriche](../guide/01-introduzione-gitignore.md)
- [➡️ Prossimo esercizio](02-pattern-avanzati.md)
