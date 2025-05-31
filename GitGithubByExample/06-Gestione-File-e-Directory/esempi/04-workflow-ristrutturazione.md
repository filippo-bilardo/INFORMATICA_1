# Esempio 04: Workflow Completo di Ristrutturazione Progetto

> **Scenario**: Ristrutturazione di un progetto web esistente con riorganizzazione completa dei file e directory  
> **Complessità**: ⭐⭐⭐⭐ (Avanzato)  
> **Tempo**: 30-45 minuti  

## 📖 Descrizione

Questo esempio mostra come gestire una ristrutturazione completa di un progetto esistente, simulando un caso reale dove dobbiamo:
- Riorganizzare la struttura delle directory
- Spostare e rinominare file esistenti
- Mantenere la cronologia Git durante il processo
- Gestire conflitti e problemi comuni

## 🎯 Obiettivi

- ✅ Comprendere come ristrutturare un progetto mantenendo la cronologia Git
- ✅ Gestire spostamenti complessi di file e directory
- ✅ Utilizzare tecniche avanzate di gestione file in Git
- ✅ Risolvere problemi comuni durante la ristrutturazione

## 🏗️ Setup Iniziale

### 1. Creazione del Progetto "Legacy"

```bash
# Crea la directory per l'esempio
mkdir git-restructure-example
cd git-restructure-example

# Inizializza il repository
git init

# Crea una struttura "legacy" tipica di progetti vecchi
mkdir assets scripts docs
mkdir assets/images assets/css assets/js

# File nella root (struttura disorganizzata)
cat > index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Legacy Project</title>
    <link rel="stylesheet" href="styles.css">
    <link rel="stylesheet" href="assets/css/bootstrap.css">
</head>
<body>
    <h1>Welcome to Legacy Project</h1>
    <script src="app.js"></script>
    <script src="assets/js/utils.js"></script>
</body>
</html>
EOF

cat > styles.css << 'EOF'
/* Main styles - should be in assets/css */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
}

h1 {
    color: #333;
    text-align: center;
}
EOF

cat > app.js << 'EOF'
// Main application logic - should be in assets/js
document.addEventListener('DOMContentLoaded', function() {
    console.log('Legacy app loaded');
    initializeApp();
});

function initializeApp() {
    // App initialization
    console.log('App initialized');
}
EOF

# File negli assets (alcuni mal posizionati)
cat > assets/css/bootstrap.css << 'EOF'
/* Bootstrap CSS */
.container {
    max-width: 1200px;
    margin: 0 auto;
}

.btn {
    padding: 10px 20px;
    border: none;
    border-radius: 4px;
}
EOF

cat > assets/js/utils.js << 'EOF'
// Utility functions
function formatDate(date) {
    return date.toLocaleDateString();
}

function validateEmail(email) {
    return email.includes('@');
}
EOF

# File documentazione sparsi
cat > README.txt << 'EOF'
Legacy Project Documentation
===========================

This is an old project that needs restructuring.
Files are scattered and not well organized.
EOF

cat > docs/api.md << 'EOF'
# API Documentation

## Endpoints

- GET /api/users
- POST /api/users
- PUT /api/users/:id
- DELETE /api/users/:id
EOF

# File di configurazione nella root
cat > config.json << 'EOF'
{
    "app": {
        "name": "Legacy Project",
        "version": "1.0.0",
        "environment": "development"
    },
    "database": {
        "host": "localhost",
        "port": 3306,
        "name": "legacy_db"
    }
}
EOF

# File immagini di test
echo "Fake image content" > assets/images/logo.png
echo "Fake icon content" > favicon.ico

# Script di build nella directory sbagliata
cat > scripts/build.sh << 'EOF'
#!/bin/bash
echo "Building legacy project..."
# Questo script dovrebbe essere in tools/ o scripts/
EOF

chmod +x scripts/build.sh

# Commit iniziale
git add .
git commit -m "Initial commit: legacy project structure

- Mixed file organization
- CSS and JS files scattered
- Documentation not centralized
- Build scripts in wrong location"

echo "✅ Legacy project structure created"
```

### 2. Analisi della Struttura Esistente

```bash
# Visualizza la struttura attuale
echo "📁 Current structure:"
tree -a

# Mostra lo stato del repository
git status

# Analizza la dimensione dei file
echo -e "\n📊 File sizes:"
find . -type f -not -path './.git/*' -exec ls -lh {} \; | awk '{print $5, $9}'
```

## 🔄 Processo di Ristrutturazione

### Fase 1: Pianificazione della Nuova Struttura

```bash
# Documenta la struttura target
cat > RESTRUCTURE_PLAN.md << 'EOF'
# Project Restructuring Plan

## Current Structure Issues
- CSS files scattered between root and assets/css/
- JS files in root and assets/js/
- Documentation files not centralized
- Configuration files mixed with source code
- Build scripts in wrong location

## Target Structure
```
project/
├── src/
│   ├── css/
│   ├── js/
│   └── html/
├── public/
│   ├── images/
│   └── favicon.ico
├── docs/
│   ├── README.md
│   └── api.md
├── config/
│   └── config.json
├── tools/
│   └── build.sh
└── dist/ (generated)
```

## Migration Steps
1. Create new directory structure
2. Move CSS files to src/css/
3. Move JS files to src/js/
4. Move HTML files to src/html/
5. Reorganize assets to public/
6. Centralize documentation
7. Move configuration files
8. Update file references
9. Test and validate
EOF

git add RESTRUCTURE_PLAN.md
git commit -m "docs: add restructuring plan

Planning the migration from legacy structure to modern organization"
```

### Fase 2: Creazione della Nuova Struttura

```bash
# Crea le nuove directory
mkdir -p src/{css,js,html}
mkdir -p public/images
mkdir -p config
mkdir -p tools
mkdir -p dist

echo "✅ New directory structure created"

# Verifica la struttura
echo "📁 New directories:"
find . -type d -not -path './.git*' | sort
```

### Fase 3: Migrazione File CSS

```bash
echo "🎨 Migrating CSS files..."

# Sposta il CSS principale usando git mv (mantiene la cronologia)
git mv styles.css src/css/main.css

# Sposta il CSS di Bootstrap
git mv assets/css/bootstrap.css src/css/bootstrap.css

# Commit della migrazione CSS
git commit -m "refactor: migrate CSS files to src/css/

- Rename styles.css to main.css for clarity
- Move bootstrap.css to consistent location
- Maintain file history with git mv"

echo "✅ CSS migration completed"
```

### Fase 4: Migrazione File JavaScript

```bash
echo "⚡ Migrating JavaScript files..."

# Sposta il file principale
git mv app.js src/js/main.js

# Sposta le utilities
git mv assets/js/utils.js src/js/utils.js

# Commit della migrazione JS
git commit -m "refactor: migrate JavaScript files to src/js/

- Rename app.js to main.js for consistency
- Consolidate all JS in single directory
- Preserve file history"

echo "✅ JavaScript migration completed"
```

### Fase 5: Migrazione File HTML

```bash
echo "🌐 Migrating HTML files..."

# Sposta l'HTML principale (ma prima aggiorniamo i riferimenti)
# Creiamo una versione aggiornata con i nuovi path
cat > temp_index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Restructured Project</title>
    <link rel="stylesheet" href="../src/css/main.css">
    <link rel="stylesheet" href="../src/css/bootstrap.css">
</head>
<body>
    <h1>Welcome to Restructured Project</h1>
    <script src="../src/js/main.js"></script>
    <script src="../src/js/utils.js"></script>
</body>
</html>
EOF

# Sostituisce il file originale e lo sposta
mv temp_index.html src/html/index.html
git rm index.html
git add src/html/index.html

git commit -m "refactor: migrate HTML files to src/html/

- Update asset references to new paths
- Move index.html to organized location"

echo "✅ HTML migration completed"
```

### Fase 6: Migrazione Assets Pubblici

```bash
echo "🖼️ Migrating public assets..."

# Sposta le immagini
git mv assets/images/* public/images/

# Sposta il favicon
git mv favicon.ico public/

# Rimuovi la directory assets vuota
rmdir assets/images assets/css assets/js assets
git add -A

git commit -m "refactor: migrate public assets

- Move images to public/images/
- Move favicon to public/
- Remove empty legacy directories"

echo "✅ Public assets migration completed"
```

### Fase 7: Migrazione Documentazione

```bash
echo "📚 Migrating documentation..."

# Converti e sposta README
cat > docs/README.md << 'EOF'
# Restructured Project

This project has been restructured for better organization and maintainability.

## Structure

- `src/` - Source code (CSS, JS, HTML)
- `public/` - Public assets (images, favicon)
- `docs/` - Documentation
- `config/` - Configuration files
- `tools/` - Build scripts and tools
- `dist/` - Built/compiled files (generated)

## Development

1. Edit source files in `src/`
2. Run build with `tools/build.sh`
3. Output goes to `dist/`

## Migration

This project was migrated from a legacy structure. See git history for migration details.
EOF

# Rimuovi il vecchio README
git rm README.txt

# Il file api.md è già nella posizione corretta
git add docs/README.md

git commit -m "docs: migrate and improve documentation

- Convert README.txt to markdown format
- Add structure explanation
- Document migration process"

echo "✅ Documentation migration completed"
```

### Fase 8: Migrazione Configurazione e Tools

```bash
echo "⚙️ Migrating configuration and tools..."

# Sposta la configurazione
git mv config.json config/

# Sposta gli script di build
git mv scripts/build.sh tools/

# Aggiorna lo script di build
cat > tools/build.sh << 'EOF'
#!/bin/bash

echo "🔨 Building restructured project..."

# Create dist directory if it doesn't exist
mkdir -p dist

# Copy HTML files
cp -r src/html/* dist/

# Process CSS files
echo "📦 Processing CSS..."
cat src/css/bootstrap.css src/css/main.css > dist/styles.min.css

# Process JS files
echo "📦 Processing JavaScript..."
cat src/js/utils.js src/js/main.js > dist/app.min.js

# Copy public assets
cp -r public/* dist/

# Update HTML references
sed -i 's|../src/css/main.css|styles.min.css|g' dist/index.html
sed -i 's|../src/css/bootstrap.css||g' dist/index.html
sed -i 's|../src/js/main.js|app.min.js|g' dist/index.html
sed -i 's|../src/js/utils.js||g' dist/index.html

echo "✅ Build completed! Output in dist/"
EOF

chmod +x tools/build.sh

# Rimuovi la directory scripts vuota
rmdir scripts

git add -A
git commit -m "refactor: migrate configuration and build tools

- Move config.json to config/ directory
- Move build script to tools/
- Update build script for new structure
- Remove empty scripts directory"

echo "✅ Configuration and tools migration completed"
```

## 🧪 Test e Validazione

### Fase 9: Test della Nuova Struttura

```bash
echo "🧪 Testing new structure..."

# Visualizza la struttura finale
echo "📁 Final structure:"
tree -I '.git'

# Test del build script
echo -e "\n🔨 Testing build process:"
./tools/build.sh

# Verifica che il build sia andato a buon fine
echo -e "\n📦 Build output:"
ls -la dist/

# Test del HTML finale
echo -e "\n🌐 Final HTML content:"
cat dist/index.html

echo -e "\n✅ Structure test completed"
```

### Fase 10: Documentazione della Migrazione

```bash
# Crea un report della migrazione
cat > MIGRATION_REPORT.md << 'EOF'
# Migration Report

## Summary
Successfully migrated legacy project structure to modern organization.

## Changes Made

### File Movements
- `styles.css` → `src/css/main.css`
- `app.js` → `src/js/main.js`
- `assets/css/bootstrap.css` → `src/css/bootstrap.css`
- `assets/js/utils.js` → `src/js/utils.js`
- `index.html` → `src/html/index.html`
- `assets/images/*` → `public/images/`
- `favicon.ico` → `public/favicon.ico`
- `config.json` → `config/config.json`
- `scripts/build.sh` → `tools/build.sh`

### Directory Changes
- Removed: `assets/`, `scripts/`
- Added: `src/`, `public/`, `config/`, `tools/`, `dist/`

### File Updates
- Updated asset references in HTML
- Improved build script functionality
- Converted README to markdown

## Benefits
1. **Clear separation of concerns**: Source code, public assets, configuration
2. **Better build process**: Automated concatenation and minification
3. **Improved maintainability**: Logical file organization
4. **Modern structure**: Follows current best practices

## Verification
- ✅ All files preserved
- ✅ Git history maintained
- ✅ Build process works
- ✅ No broken references
EOF

git add MIGRATION_REPORT.md
git commit -m "docs: add migration report

Document complete restructuring process and benefits"

# Crea un tag per la migrazione
git tag -a v2.0.0 -m "Version 2.0.0: Complete project restructuring

- Modern directory organization
- Improved build process
- Better separation of concerns
- Maintained backward compatibility"

echo "✅ Migration completed and documented"
```

## 📊 Verifica della Cronologia

```bash
echo "📚 Reviewing migration history..."

# Mostra la cronologia dei commit
echo "📋 Commit history:"
git log --oneline --graph

# Verifica che la cronologia dei file sia preservata
echo -e "\n🔍 File history verification:"
echo "History of main.css (previously styles.css):"
git log --follow --oneline src/css/main.css

echo -e "\nHistory of main.js (previously app.js):"
git log --follow --oneline src/js/main.js

# Mostra le statistiche della migrazione
echo -e "\n📊 Migration statistics:"
git log --since="1 hour ago" --oneline | wc -l
echo "commits created during migration"

# Verifica l'integrità del repository
echo -e "\n🔍 Repository integrity check:"
git fsck --full
```

## 🎯 Risultati e Benefici

### Struttura Finale

```
project/
├── src/
│   ├── css/
│   │   ├── main.css
│   │   └── bootstrap.css
│   ├── js/
│   │   ├── main.js
│   │   └── utils.js
│   └── html/
│       └── index.html
├── public/
│   ├── images/
│   │   └── logo.png
│   └── favicon.ico
├── docs/
│   ├── README.md
│   └── api.md
├── config/
│   └── config.json
├── tools/
│   └── build.sh
├── dist/           (generated)
│   ├── index.html
│   ├── styles.min.css
│   ├── app.min.js
│   ├── images/
│   └── favicon.ico
├── RESTRUCTURE_PLAN.md
└── MIGRATION_REPORT.md
```

### Benefici Ottenuti

1. **Organizzazione Logica**: File raggruppati per tipo e funzione
2. **Separazione Chiara**: Source code vs. assets pubblici vs. configurazione
3. **Build Process**: Automatizzazione della concatenazione e minificazione
4. **Manutenibilità**: Struttura più facile da navigare e mantenere
5. **Cronologia Preservata**: Tutti i file mantengono la loro cronologia Git
6. **Scalabilità**: Struttura che supporta crescita futura del progetto

## 💡 Lezioni Apprese

### Best Practices per Ristrutturazione

1. **Pianifica Prima**: Documenta sempre la struttura target
2. **Usa `git mv`**: Preserva la cronologia dei file
3. **Commit Frequenti**: Un commit per ogni fase logica
4. **Test Continui**: Verifica che tutto funzioni dopo ogni fase
5. **Documenta**: Mantieni traccia delle modifiche e motivazioni

### Comandi Git Essenziali

- `git mv`: Sposta/rinomina file mantenendo la cronologia
- `git log --follow`: Traccia la cronologia di file spostati
- `git tag`: Marca milestone importanti
- `git fsck`: Verifica l'integrità del repository

## 🚀 Prossimi Passi

Dopo questa ristrutturazione, il progetto è pronto per:

1. **Implementazione CI/CD**: Automatizzazione del build e deploy
2. **Linting e Code Quality**: Integrazione di strumenti di qualità
3. **Testing**: Aggiunta di test automatizzati
4. **Documentazione API**: Espansione della documentazione
5. **Ottimizzazioni**: Performance e bundle optimization

---

> **Nota**: Questo esempio dimostra l'importanza di una buona organizzazione del progetto e come Git possa facilitare ristrutturazioni complesse mantenendo la cronologia del codice.
