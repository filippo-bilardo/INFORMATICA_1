# Pulizia Repository

Questo esempio dimostra come pulire un repository da file non necessari, build artifacts e contenuti sensibili.

## Scenario: Pulizia di un Progetto Sporco

### Setup: Progetto Disorganizzato

```bash
# Creare progetto con molti file indesiderati
mkdir pulizia-repository
cd pulizia-repository
git init

# Simulare progetto sporco con file misti
mkdir -p {src,build,node_modules,logs,cache,temp}

# File sorgente legittimi
cat > src/app.js << 'EOL'
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.listen(3000, () => {
  console.log('Server running on port 3000');
});
EOL

cat > src/config.js << 'EOL'
module.exports = {
  port: process.env.PORT || 3000,
  database: {
    host: 'localhost',
    port: 5432,
    name: 'myapp'
  }
};
EOL

# File di build (da rimuovere)
echo "console.log('minified app');" > build/app.min.js
echo "body{margin:0;padding:0}" > build/style.min.css
echo "Webpack build output..." > build/bundle.js

# Node modules (simulati)
touch node_modules/package.json
mkdir -p node_modules/{express,lodash,react}
touch node_modules/express/index.js
touch node_modules/lodash/index.js

# File di log
echo "[2024-01-01] Server started" > logs/app.log
echo "[2024-01-01] Database connected" > logs/db.log
echo "[2024-01-01] Error: Connection failed" > logs/error.log

# File temporanei
touch temp/upload_123.tmp
touch temp/session_abc.tmp
echo "Temporary cache data" > cache/data.cache

# File sensibili (aggiunti per errore)
cat > .env << 'EOL'
DATABASE_PASSWORD=super_secret_123
API_KEY=sk-1234567890abcdef
JWT_SECRET=my-jwt-secret-key
EOL

cat > credentials.json << 'EOL'
{
  "database": {
    "username": "admin",
    "password": "admin123"
  },
  "api": {
    "key": "secret-api-key",
    "secret": "ultra-secret-value"
  }
}
EOL

# File di backup dell'editor
echo "Backup content" > src/app.js~
echo "Vim swap file" > src/.app.js.swp
touch src/.DS_Store

# File di OS
touch Thumbs.db
touch desktop.ini

# Committare tutto (simulando errore)
git add .
git commit -m "Initial commit with mixed files (contains errors!)"

echo "✓ Repository sporco creato con file misti"
```

### 1. Analisi dello Stato Iniziale

```bash
echo "=== Analisi Repository Sporco ==="

# Vedere tutti i file tracciati
echo "File attualmente tracciati:"
git ls-files | sort

echo ""
echo "Dimensione repository:"
du -sh .git

echo ""
echo "File per tipo:"
git ls-files | grep -E '\.(js|css|json|log|tmp|cache)$' | \
  awk -F. '{print $NF}' | sort | uniq -c

echo ""
echo "Directory con più file:"
git ls-files | cut -d/ -f1 | sort | uniq -c | sort -nr
```

### 2. Rimozione File di Build

```bash
echo "=== Pulizia File di Build ==="

# Rimuovere directory di build
git rm -r build/
echo "✓ Rimossa directory build/"

# Verificare rimozione
git status

# Aggiungere al .gitignore per prevenire future aggiunte
cat > .gitignore << 'EOL'
# Build artifacts
build/
dist/
*.min.js
*.min.css
bundle.js

# Dependencies
node_modules/
EOL

git add .gitignore
git commit -m "Remove build artifacts and add to gitignore

- Remove build/ directory with minified files
- Add build artifacts to gitignore
- Prevent future inclusion of build files"

echo "✓ File di build rimossi e gitignore aggiornato"
```

### 3. Rimozione Dependencies

```bash
echo "=== Pulizia Dependencies ==="

# Rimuovere node_modules 
git rm -r node_modules/
echo "✓ Rimossa directory node_modules/"

# Aggiornare .gitignore
cat >> .gitignore << 'EOL'

# Package manager files
package-lock.json
yarn.lock
pnpm-lock.yaml
EOL

# Creare package.json appropriato invece di tracciare node_modules
cat > package.json << 'EOL'
{
  "name": "clean-project",
  "version": "1.0.0",
  "description": "Progetto pulito dopo refactoring",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "build": "webpack --mode=production"
  },
  "dependencies": {
    "express": "^4.18.0"
  },
  "devDependencies": {
    "webpack": "^5.70.0"
  }
}
EOL

git add package.json .gitignore
git commit -m "Replace node_modules with package.json

- Remove tracked node_modules directory  
- Add proper package.json with dependencies
- Update gitignore for package manager files"

echo "✓ Dependencies pulite, package.json aggiunto"
```

### 4. Rimozione File Temporanei e Log

```bash
echo "=== Pulizia File Temporanei e Log ==="

# Rimuovere file di log e temporanei
git rm -r logs/ temp/ cache/
echo "✓ Rimossi logs/, temp/, cache/"

# Aggiornare .gitignore
cat >> .gitignore << 'EOL'

# Logs and temporary files  
logs/
*.log
temp/
*.tmp
cache/
*.cache

# Editor backup files
*~
*.swp
*.swo
.DS_Store
Thumbs.db
desktop.ini
EOL

# Rimuovere file di backup dell'editor già tracciati
git rm 'src/app.js~' 'src/.app.js.swp' 'src/.DS_Store' \
       'Thumbs.db' 'desktop.ini' 2>/dev/null || true

git add .gitignore
git commit -m "Remove temporary files and logs

- Remove logs/, temp/, cache/ directories
- Remove editor backup files  
- Add comprehensive ignore patterns
- Prevent future inclusion of temporary files"

echo "✓ File temporanei e log rimossi"
```

### 5. Rimozione File Sensibili

```bash
echo "=== Rimozione File Sensibili ==="

# Rimuovere file con credenziali
git rm .env credentials.json
echo "✓ Rimossi file sensibili"

# Aggiornare .gitignore per file sensibili
cat >> .gitignore << 'EOL'

# Environment and credentials
.env
.env.local
.env.production
credentials.json
secrets.json
config/database.yml
EOL

# Creare file di esempio per configurazione
cat > .env.example << 'EOL'
# Example environment configuration
# Copy to .env and fill with your values

DATABASE_PASSWORD=your_database_password
API_KEY=your_api_key
JWT_SECRET=your_jwt_secret
EOL

cat > config.example.js << 'EOL'
// Example configuration file
// Copy to config.js and customize

module.exports = {
  port: process.env.PORT || 3000,
  database: {
    host: process.env.DB_HOST || 'localhost',
    port: process.env.DB_PORT || 5432,
    name: process.env.DB_NAME || 'myapp',
    password: process.env.DB_PASSWORD // Set in .env file
  },
  apiKey: process.env.API_KEY // Set in .env file
};
EOL

git add .env.example config.example.js .gitignore
git commit -m "Remove sensitive files and add example templates

- Remove .env and credentials.json from tracking
- Add .env.example and config.example.js as templates
- Update gitignore to prevent future credential leaks
- Provide safe configuration examples"

echo "✓ File sensibili rimossi, template aggiunti"
```

### 6. Pulizia Pattern-Based

```bash
echo "=== Pulizia con Pattern ==="

# Creare file con pattern per test
touch {debug.log,trace.log,access.log}
touch {app.o,utils.o,config.o}
touch {test.exe,app.exe}

git add .
git commit -m "Add test files for pattern cleanup demo"

# Rimuovere file per pattern
git rm '*.log' '*.o' '*.exe'
echo "✓ Rimossi file con pattern *.log, *.o, *.exe"

# Aggiornare .gitignore con pattern
cat >> .gitignore << 'EOL'

# Compiled files
*.o
*.exe
*.dll
*.so

# Additional log files
*.log
debug.*
trace.*
EOL

git add .gitignore
git commit -m "Remove files by pattern and update gitignore

- Remove all *.log, *.o, *.exe files
- Add pattern-based ignore rules
- Prevent future inclusion of compiled files"

echo "✓ Pulizia pattern completata"
```

### 7. Rimozione Dalla Storia (Avanzato)

```bash
echo "=== Rimozione Dalla Storia (Simulazione) ==="

# ATTENZIONE: Questi comandi modificano la storia
# In produzione, usare con estrema cautela

echo "Per rimuovere file sensibili dalla storia completa:"
echo ""
echo "# Usando git filter-branch:"
echo "git filter-branch --force --index-filter \\"
echo "  'git rm --cached --ignore-unmatch .env credentials.json' \\"
echo "  --prune-empty --tag-name-filter cat -- --all"
echo ""
echo "# Usando BFG Repo-Cleaner (raccomandato):"
echo "bfg --delete-files '.env,credentials.json'"
echo "bfg --strip-blobs-bigger-than 10M"
echo ""
echo "# Pulizia finale:"
echo "git reflog expire --expire=now --all"
echo "git gc --prune=now --aggressive"

# Creare script per pulizia automatica
cat > scripts/cleanup-repo.sh << 'EOL'
#!/bin/bash
# Repository cleanup script

set -e

echo "🧹 Starting repository cleanup..."

# Remove common build artifacts  
git rm -r build/ dist/ 2>/dev/null || true
git rm '*.min.js' '*.min.css' 2>/dev/null || true

# Remove dependencies
git rm -r node_modules/ vendor/ 2>/dev/null || true

# Remove logs and temporary files
git rm -r logs/ temp/ cache/ 2>/dev/null || true
git rm '*.log' '*.tmp' '*.cache' 2>/dev/null || true

# Remove editor files
git rm '*~' '*.swp' '.DS_Store' 'Thumbs.db' 2>/dev/null || true

# Remove compiled files
git rm '*.o' '*.exe' '*.dll' 2>/dev/null || true

echo "✅ Repository cleanup completed!"
echo "Don't forget to update .gitignore and commit changes."
EOL

mkdir -p scripts
chmod +x scripts/cleanup-repo.sh
git add scripts/
git commit -m "Add automated repository cleanup script"

echo "✓ Script di pulizia automatica aggiunto"
```

### 8. Verifica Finale e Statistiche

```bash
echo "=== Verifica Finale ==="

# Statistiche finali
echo "File rimasti nel repository:"
git ls-files | wc -l

echo ""
echo "Struttura finale:"
tree . 2>/dev/null || find . -type f -not -path './.*' | sort

echo ""
echo "Dimensione repository finale:"
du -sh .git

echo ""
echo "Contenuto .gitignore finale:"
cat .gitignore

echo ""
echo "Ultimi commit:"
git log --oneline -10
```

### 9. Script di Pulizia Completo

```bash
# Creare script completo di pulizia
cat > complete-cleanup.sh << 'EOL'
#!/bin/bash
# Complete repository cleanup script

set -e

echo "🚀 Starting complete repository cleanup..."

# Backup current state
git tag backup-before-cleanup 2>/dev/null || true

# 1. Remove build artifacts
echo "📦 Removing build artifacts..."
git rm -r build/ dist/ out/ 2>/dev/null || true
git rm '*.min.js' '*.min.css' bundle.js 2>/dev/null || true

# 2. Remove dependencies  
echo "📚 Removing dependencies..."
git rm -r node_modules/ vendor/ packages/ 2>/dev/null || true

# 3. Remove logs and temporary files
echo "🗑️ Removing logs and temporary files..."
git rm -r logs/ temp/ cache/ tmp/ 2>/dev/null || true
git rm '*.log' '*.tmp' '*.cache' '*.pid' 2>/dev/null || true

# 4. Remove editor and OS files
echo "✏️ Removing editor and OS files..."
git rm '*~' '*.swp' '*.swo' '.DS_Store' 'Thumbs.db' 'desktop.ini' 2>/dev/null || true
git rm -r '.vscode/' '.idea/' 2>/dev/null || true

# 5. Remove compiled files
echo "⚙️ Removing compiled files..."
git rm '*.o' '*.exe' '*.dll' '*.so' '*.pyc' '*.class' 2>/dev/null || true

# 6. Create comprehensive .gitignore
echo "📝 Creating comprehensive .gitignore..."
cat > .gitignore << 'GITIGNORE'
# Dependencies
node_modules/
vendor/
packages/

# Build artifacts
build/
dist/
out/
*.min.js
*.min.css
bundle.js

# Logs and temporary files
logs/
*.log
temp/
tmp/
cache/
*.tmp
*.cache
*.pid

# Environment and credentials
.env
.env.local
.env.production
credentials.json
secrets.json

# Editor files
*~
*.swp
*.swo
.vscode/
.idea/

# OS files
.DS_Store
Thumbs.db
desktop.ini

# Compiled files
*.o
*.exe
*.dll
*.so
*.pyc
*.class
GITIGNORE

# 7. Commit cleanup
git add .gitignore
git commit -m "Complete repository cleanup

- Remove build artifacts and dependencies
- Remove logs and temporary files  
- Remove editor and OS files
- Remove compiled files
- Add comprehensive .gitignore
- Repository is now clean and organized"

echo "✅ Repository cleanup completed successfully!"
echo "📊 Repository statistics:"
echo "   Files tracked: $(git ls-files | wc -l)"
echo "   Repository size: $(du -sh .git | cut -f1)"
echo ""
echo "🔄 To restore if needed: git checkout backup-before-cleanup"
EOL

chmod +x complete-cleanup.sh
git add complete-cleanup.sh
git commit -m "Add complete cleanup script for future use"
```

## Comandi di Riferimento

```bash
# Rimozione base
git rm file.txt                    # Rimuovi file
git rm -r directory/               # Rimuovi directory  
git rm --cached file.txt           # Rimuovi solo dal tracking

# Rimozione pattern
git rm '*.log'                     # Tutti i file .log
git rm 'temp/*'                    # Tutto in temp/
git rm -r --cached 'node_modules/' # node_modules dal tracking

# Pulizia storia (ATTENZIONE!)
git filter-branch --index-filter 'git rm --cached --ignore-unmatch file'
bfg --delete-files 'file'          # Tool BFG (raccomandato)

# Verifica
git ls-files                       # File tracciati
du -sh .git                        # Dimensione repository
git log --stat                     # Modifiche nei commit
```

## Best Practices Dimostrate

1. **Backup**: Sempre creare tag/branch di backup prima di pulizie massive
2. **Graduale**: Pulire per categorie (build, deps, logs, sensibili)
3. **Gitignore**: Aggiornare .gitignore per prevenire future inclusioni
4. **Template**: Fornire file .example per configurazioni sensibili
5. **Script**: Automatizzare pulizie ricorrenti
6. **Verifica**: Controllare risultati prima di push
7. **Documentazione**: Documentare cosa è stato rimosso e perché

## Risultati della Pulizia

### Prima della pulizia:
```
Files tracked: 45
Repository size: 2.1M
Includes: build/, node_modules/, logs/, .env, *.log, *~
```

### Dopo la pulizia:
```
Files tracked: 8
Repository size: 156K
Includes: src/, package.json, .gitignore, scripts/
Clean, organized, secure repository
```

Questo esempio mostra un processo completo di pulizia repository che rimuove file indesiderati mantenendo funzionalità e sicurezza.
