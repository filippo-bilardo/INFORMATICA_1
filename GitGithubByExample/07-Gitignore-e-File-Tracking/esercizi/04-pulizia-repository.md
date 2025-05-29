# Esercizio 04: Pulizia Repository

## 🎯 Obiettivo
Imparare a pulire un repository esistente rimuovendo file che non dovrebbero essere tracciati, ottimizzando la dimensione del repository e implementando policy di `.gitignore` retroattivamente.

## 📋 Prerequisiti
- Conoscenza avanzata di `.gitignore`
- Familiarità con `git rm`, `git filter-branch`
- Comprensione dei rischi della riscrittura della storia

## 🚨 Scenario: Repository "Inquinato"
Ti viene consegnato un repository che è stato gestito male per mesi. Contiene:
- File di build tracciati per errore
- Dipendenze committate 
- File sensibili (password, chiavi API)
- Log files giganti
- File temporanei dell'IDE

**Il tuo compito:** Pulire tutto mantenendo la storia importante.

## 📝 Parte 1: Analisi del Repository Problematico

### 1.1 Creare Repository di Test "Inquinato"
```bash
mkdir ~/cleanup-repository-exercise
cd ~/cleanup-repository-exercise
git init

# Crea struttura del progetto
mkdir -p src/{components,utils,config}
mkdir -p node_modules/{express,lodash,react}
mkdir -p dist/{js,css,images}
mkdir -p logs/{2023,2024}
mkdir -p .vscode
mkdir -p uploads/documents
```

### 1.2 Popolare con File Problematici
```bash
# ===== FILE LEGITTIMI =====
echo 'console.log("main app");' > src/app.js
echo 'export default Header;' > src/components/Header.js
echo 'export const helpers = {};' > src/utils/helpers.js
echo '{"name": "my-app", "version": "1.0.0"}' > package.json

# ===== DIPENDENZE (NON DOVREBBERO ESSERE TRACCIATI) =====
echo 'express module code' > node_modules/express/index.js
echo 'lodash utilities' > node_modules/lodash/lodash.js
echo 'react library' > node_modules/react/react.js
# Crea file grande per simulare problema di dimensioni
dd if=/dev/zero of=node_modules/react/react.min.js bs=1024 count=5000  # 5MB

# ===== FILE DI BUILD (NON DOVREBBERO ESSERE TRACCIATI) =====
echo 'compiled js' > dist/js/app.min.js
echo 'compiled css' > dist/css/style.min.css
# File build grandi
dd if=/dev/zero of=dist/js/vendor.bundle.js bs=1024 count=3000  # 3MB

# ===== LOG FILES (NON DOVREBBERO ESSERE TRACCIATI) =====
echo 'old logs' > logs/2023/january.log
echo 'old logs' > logs/2023/december.log
echo 'current logs' > logs/2024/january.log
# Log file gigante
dd if=/dev/zero of=logs/2024/application.log bs=1024 count=10000  # 10MB

# ===== FILE SENSIBILI (PERICOLOSI!) =====
echo 'API_KEY=sk_live_51AbCdEfGhIjKlMnOpQrStUvWxYz' > .env
echo 'DB_PASSWORD=super_secret_password_123' > config.secret
echo 'AWS_SECRET_KEY=AKIAIOSFODNN7EXAMPLE' > src/config/aws.keys

# ===== FILE IDE =====
echo '{"workspaceFolder": "my-app"}' > .vscode/settings.json
echo '{"version": "0.2.0"}' > .vscode/launch.json

# ===== FILE UPLOAD UTENTE =====
echo 'user document content' > uploads/documents/resume.pdf
echo 'private file' > uploads/documents/contract.pdf
```

### 1.3 Commit del Disastro
```bash
# Prima di tutto, commit tutto (simula la situazione problematica)
git add .
git commit -m "initial commit - includes everything (BAD PRACTICE)"

# Aggiungi altri commit per simulare storia
echo 'console.log("update");' >> src/app.js
git add src/app.js
git commit -m "update app.js"

# Aggiungi altro contenuto problematico
echo 'more logs' >> logs/2024/application.log
git add logs/2024/application.log
git commit -m "update logs"
```

### 1.4 Analisi Iniziale
```bash
# Vedi dimensione repository
du -sh .git
du -sh .

# Vedi file più grandi
git ls-files | xargs ls -lah | sort -k5 -hr | head -10

# Count file per tipo
echo "=== FILE COUNT BY TYPE ==="
echo "JavaScript files: $(git ls-files | grep '\.js$' | wc -l)"
echo "Log files: $(git ls-files | grep '\.log$' | wc -l)"
echo "Config files: $(git ls-files | grep -E '\.(env|keys|secret)$' | wc -l)"
echo "Total files: $(git ls-files | wc -l)"
```

## 📝 Parte 2: Strategia di Pulizia

### 2.1 Creare .gitignore Corretto
```bash
cat > .gitignore << 'EOF'
# ===================================
# GITIGNORE POST-CLEANUP
# ===================================

# === DIPENDENZE ===
node_modules/

# === BUILD E DIST ===
dist/
build/
*.min.js
*.min.css

# === LOGS ===
logs/
*.log

# === FILE SENSIBILI ===
.env
.env.*
*.secret
*.keys
config/local.*
src/config/*.keys

# === UPLOADS UTENTE ===
uploads/
!uploads/.gitkeep

# === IDE ===
.vscode/
.idea/
*.swp
*~

# === CACHE ===
.cache/
.npm/
.eslintcache

# === SISTEMA OPERATIVO ===
.DS_Store
Thumbs.db
*.tmp

# === COVERAGE ===
coverage/
EOF
```

### 2.2 Backup di Sicurezza
```bash
# Crea backup completo prima della pulizia
cd ..
cp -r cleanup-repository-exercise cleanup-repository-backup
cd cleanup-repository-exercise

# Crea branch di backup
git branch backup-before-cleanup
```

## 📝 Parte 3: Pulizia Progressiva

### 3.1 Rimozione File dal Working Directory
```bash
# Prima fase: rimuovi dal tracking mantenendo su disco
git rm --cached -r node_modules/
git rm --cached -r dist/
git rm --cached -r logs/
git rm --cached .env config.secret src/config/aws.keys
git rm --cached -r .vscode/
git rm --cached -r uploads/

# Commit la rimozione
git commit -m "cleanup: remove inappropriate files from tracking"
```

### 3.2 Verifica Pulizia Immediate
```bash
# Verifica che i file non siano più tracciati
git ls-files | grep -E "(node_modules|dist|logs|\.env|\.secret|\.keys|uploads)"

# Dovrebbe non restituire nulla
echo "Files still tracked that shouldn't be: $(git ls-files | grep -E '(node_modules|dist|logs|\.env|\.secret|\.keys|uploads)' | wc -l)"
```

### 3.3 Pulizia Working Directory
```bash
# Rimuovi fisicamente i file problematici
rm -rf node_modules/
rm -rf dist/
rm -rf logs/
rm -f .env config.secret src/config/aws.keys
rm -rf .vscode/
rm -rf uploads/

# Mantieni directory necessarie vuote
mkdir uploads
touch uploads/.gitkeep
```

## 📝 Parte 4: Pulizia Storia Git (ATTENZIONE!)

### 4.1 Analisi Pre-pulizia
```bash
# Vedi dimensione prima della pulizia storia
git count-objects -vH

# Lista commit che includono file problematici
git log --oneline --name-only | grep -E "(node_modules|logs|\.env)" -B1
```

### 4.2 Pulizia Storia con git filter-branch (Opzione 1)
```bash
# ⚠️  ATTENZIONE: Questo riscrive la storia Git
# Usa solo se necessario e hai backup

# Rimuovi file sensibili dalla storia
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch .env config.secret src/config/aws.keys' \
  --prune-empty --tag-name-filter cat -- --all

# Rimuovi grandi file dalla storia  
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch -r node_modules/ dist/ logs/' \
  --prune-empty --tag-name-filter cat -- --all
```

### 4.3 Pulizia Storia con BFG (Opzione 2 - Più Sicura)
```bash
# Installa BFG Repo-Cleaner (più sicuro di filter-branch)
# Su Ubuntu/Debian:
# sudo apt install bfg

# Esempio comandi BFG (commentati per sicurezza):
# bfg --delete-files "*.log" .
# bfg --delete-folders "node_modules" .
# bfg --delete-files ".env" .
# git reflog expire --expire=now --all && git gc --prune=now --aggressive
```

### 4.4 Cleanup Post-Filter
```bash
# Pulisci riferimenti obsoleti
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive

# Verifica dimensione dopo pulizia
git count-objects -vH
```

## 📝 Parte 5: Implementazione Policy di Prevenzione

### 5.1 Pre-commit Hook
```bash
# Crea hook per prevenire problemi futuri
mkdir -p .git/hooks

cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Pre-commit hook per prevenire file problematici

# Controlla file sensibili
if git diff --cached --name-only | grep -E "\.(env|secret|keys)$"; then
    echo "❌ ERRORE: Tentativo di commit file sensibili!"
    echo "File rilevati:"
    git diff --cached --name-only | grep -E "\.(env|secret|keys)$"
    exit 1
fi

# Controlla file grandi (>1MB)
for file in $(git diff --cached --name-only); do
    if [ -f "$file" ] && [ $(stat -c%s "$file") -gt 1048576 ]; then
        echo "❌ ERRORE: File troppo grande: $file ($(stat -c%s "$file") bytes)"
        echo "Considera se deve essere tracciato da Git"
        exit 1
    fi
done

# Controlla directory che non dovrebbero essere committate
if git diff --cached --name-only | grep -E "^(node_modules|dist|logs)/"; then
    echo "❌ ERRORE: Tentativo di commit directory che dovrebbe essere ignorata!"
    git diff --cached --name-only | grep -E "^(node_modules|dist|logs)/"
    exit 1
fi

echo "✅ Pre-commit checks passed"
EOF

chmod +x .git/hooks/pre-commit
```

### 5.2 Test del Hook
```bash
# Test con file sensibile
echo "API_KEY=test" > test.env
git add test.env
git commit -m "test sensitive file"
# Dovrebbe essere bloccato

# Cleanup
rm test.env
```

### 5.3 Documentazione Policy
```bash
cat > CONTRIBUTING.md << 'EOF'
# Contributing Guidelines

## File che NON devono essere committati

### ❌ File Sensibili
- `.env`, `.env.*` - Variabili ambiente
- `*.secret`, `*.keys` - File con credenziali
- `config/local.*` - Configurazioni locali

### ❌ Dipendenze e Build
- `node_modules/` - Dipendenze npm
- `dist/`, `build/` - File compilati
- `*.min.js`, `*.min.css` - File minificati

### ❌ File Temporanei
- `logs/`, `*.log` - File di log
- `.cache/` - Cache
- `uploads/` - File caricati dagli utenti

### ❌ IDE e OS
- `.vscode/`, `.idea/` - Configurazioni IDE
- `.DS_Store`, `Thumbs.db` - File sistema

## Prevenzione

1. **Pre-commit hook** attivo per bloccare file problematici
2. **Gitignore** completo mantenuto aggiornato
3. **Review** obbligatoria per modifiche sensitive

## Pulizia Repository

Se hai committato file per errore:
```bash
# Rimuovi dal tracking
git rm --cached file-problematico

# Per pulizia storia (PERICOLOSO):
# Contatta il team lead
```
EOF
```

## 📝 Parte 6: Verifica e Monitoraggio

### 6.1 Script di Verifica
```bash
cat > verify-repository-health.sh << 'EOF'
#!/bin/bash
echo "=== REPOSITORY HEALTH CHECK ==="

# Dimensione repository
echo "Repository size: $(du -sh .git | cut -f1)"
echo "Working directory: $(du -sh . --exclude=.git | cut -f1)"

# File tracciati problematici
problematic_files=$(git ls-files | grep -E "(node_modules|dist|logs|\.env|\.secret|\.keys)" | wc -l)
echo "Problematic files tracked: $problematic_files"

if [ $problematic_files -gt 0 ]; then
    echo "❌ Found problematic files:"
    git ls-files | grep -E "(node_modules|dist|logs|\.env|\.secret|\.keys)"
else
    echo "✅ No problematic files found"
fi

# File grandi
echo "=== LARGE FILES (>100KB) ==="
git ls-files | xargs ls -lah 2>/dev/null | awk '$5 ~ /[0-9]+[MK]/ && $5+0 > 100 {print $5, $9}' | sort -hr

# Gitignore validity
if [ -f .gitignore ]; then
    echo "✅ .gitignore present"
    echo "Gitignore rules: $(wc -l < .gitignore)"
else
    echo "❌ .gitignore missing"
fi

# Pre-commit hook
if [ -x .git/hooks/pre-commit ]; then
    echo "✅ Pre-commit hook active"
else
    echo "⚠️  Pre-commit hook not found"
fi
EOF

chmod +x verify-repository-health.sh
./verify-repository-health.sh
```

### 6.2 Setup Monitoring Continuo
```bash
# Aggiungi alias Git utili
git config alias.check-size '!git ls-files | xargs ls -lah | sort -k5 -hr | head -10'
git config alias.check-ignored 'status --ignored --porcelain'
git config alias.check-large '!git ls-files | xargs ls -lah | awk '\''$5+0 > 1048576 {print $5, $9}'\'''

# Test degli alias
git check-size
```

## ✅ Checklist Finale

### Pulizia Completata
- [x] **File sensibili**: rimossi dalla storia
- [x] **Dipendenze**: non più tracciate
- [x] **File build**: rimossi completamente
- [x] **Log files**: rimossi e ignorati
- [x] **File IDE**: rimossi e ignorati
- [x] **Gitignore**: implementato correttamente

### Prevenzione Implementata
- [x] **Pre-commit hook**: attivo e funzionante
- [x] **Policy documentata**: CONTRIBUTING.md creato
- [x] **Script di verifica**: disponibile per controlli periodici
- [x] **Alias Git**: configurati per monitoring

### Metriche di Successo
```bash
# Before vs After
echo "=== CLEANUP RESULTS ==="
echo "Problematic files tracked: 0"
echo "Repository size: $(du -sh .git | cut -f1)"
echo "Working directory: $(du -sh . --exclude=.git | cut -f1)"

# Verifica file tracciati
total_files=$(git ls-files | wc -l)
echo "Total files tracked: $total_files"
echo "Expected: ~5 (app.js, Header.js, helpers.js, package.json, .gitignore, CONTRIBUTING.md)"
```

## 🎓 Competenze Acquisite

- ✅ **Analisi repository**: Identificare file problematici
- ✅ **Pulizia progressiva**: Strategia step-by-step sicura
- ✅ **Storia Git**: Comprensione e pulizia (con cautela)
- ✅ **Prevenzione**: Hook e policy per evitare regressioni
- ✅ **Monitoraggio**: Script e strumenti per controllo continuo
- ✅ **Documentazione**: Policy chiare per il team

## ⚠️  Lezioni Importanti

1. **Backup sempre**: Prima di qualsiasi operazione distruttiva
2. **Filter-branch è pericoloso**: Cambia la storia Git
3. **Prevenzione > Correzione**: Hook e policy salvano tempo
4. **Educazione team**: Policy chiare prevengono problemi
5. **Monitoring continuo**: Verifiche periodiche mantengono la qualità

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Esercizio precedente](03-debugging-gitignore.md)
- [➡️ Modulo successivo](../../08-Visualizzare-Storia-Commit/README.md)
