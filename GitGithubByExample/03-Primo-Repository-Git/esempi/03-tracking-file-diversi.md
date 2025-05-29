# Esempio 3: Tracking di File Diversi

## 📋 Scenario
Esploriamo come Git gestisce diversi tipi di file in un progetto misto che include codice, documentazione, risorse multimediali e file di configurazione.

## 🎯 Obiettivi di Apprendimento
- Comprendere come Git traccia diversi tipi di file
- Gestire file binari e di testo
- Configurare il tracking ottimale per progetti complessi
- Utilizzare `.gitignore` efficacemente

## 🛠️ Implementazione Pratica

### Passo 1: Setup del Progetto Misto

```bash
# Creiamo un progetto completo
mkdir webapp-completa
cd webapp-completa
git init

# Creiamo la struttura delle directory
mkdir -p {src/{js,css,components},docs,assets/{images,fonts,data},config,tests}
```

### Passo 2: Creazione di File Diversi

#### File di Codice (Text-based)
```bash
# File HTML
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebApp Completa</title>
    <link rel="stylesheet" href="src/css/main.css">
</head>
<body>
    <h1>Benvenuto nella WebApp</h1>
    <script src="src/js/app.js"></script>
</body>
</html>
EOF

# File JavaScript
cat > src/js/app.js << 'EOF'
// Main application logic
class WebApp {
    constructor() {
        this.version = "1.0.0";
        this.init();
    }
    
    init() {
        console.log(`WebApp v${this.version} initialized`);
        this.setupEventListeners();
    }
    
    setupEventListeners() {
        document.addEventListener('DOMContentLoaded', () => {
            console.log('DOM fully loaded');
        });
    }
}

// Initialize app
const app = new WebApp();
EOF

# File CSS
cat > src/css/main.css << 'EOF'
/* Main stylesheet for WebApp */
:root {
    --primary-color: #007bff;
    --secondary-color: #6c757d;
    --success-color: #28a745;
}

body {
    font-family: 'Arial', sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f8f9fa;
}

h1 {
    color: var(--primary-color);
    text-align: center;
    margin-bottom: 2rem;
}
EOF
```

#### File di Configurazione
```bash
# Package.json (Node.js)
cat > package.json << 'EOF'
{
  "name": "webapp-completa",
  "version": "1.0.0",
  "description": "Un esempio completo di webapp per Git tracking",
  "main": "src/js/app.js",
  "scripts": {
    "start": "node server.js",
    "test": "jest",
    "build": "webpack --mode production"
  },
  "keywords": ["webapp", "git", "esempio"],
  "author": "Team Development",
  "license": "MIT",
  "devDependencies": {
    "jest": "^29.0.0",
    "webpack": "^5.0.0"
  }
}
EOF

# File di configurazione ambiente
cat > config/development.json << 'EOF'
{
  "database": {
    "host": "localhost",
    "port": 5432,
    "name": "webapp_dev"
  },
  "api": {
    "baseUrl": "http://localhost:3000",
    "timeout": 5000
  },
  "logging": {
    "level": "debug",
    "file": "logs/development.log"
  }
}
EOF

# File di produzione (da ignorare)
cat > config/production.json << 'EOF'
{
  "database": {
    "host": "prod-db.example.com",
    "port": 5432,
    "name": "webapp_prod",
    "password": "SECRET_PASSWORD"
  },
  "api": {
    "baseUrl": "https://api.example.com",
    "apiKey": "SECRET_API_KEY"
  }
}
EOF
```

#### File di Documentazione
```bash
# README del progetto
cat > README.md << 'EOF'
# WebApp Completa

## 📋 Descrizione
Un esempio completo di web application per dimostrare il tracking Git di diversi tipi di file.

## 🚀 Quick Start
```bash
npm install
npm start
```

## 📁 Struttura Progetto
- `src/` - Codice sorgente
- `docs/` - Documentazione
- `assets/` - Risorse multimediali
- `config/` - File di configurazione
- `tests/` - Test automatizzati

## 🔧 Tecnologie
- HTML5
- CSS3 (CSS Variables)
- JavaScript (ES6+)
- Node.js
EOF

# Documentazione API
cat > docs/api.md << 'EOF'
# API Documentation

## Endpoints

### GET /api/users
Recupera la lista degli utenti.

**Response:**
```json
{
  "users": [
    {"id": 1, "name": "Mario Rossi"},
    {"id": 2, "name": "Anna Verdi"}
  ]
}
```

### POST /api/users
Crea un nuovo utente.

**Request Body:**
```json
{
  "name": "Nuovo Utente",
  "email": "nuovo@example.com"
}
```
EOF
```

#### File di Test
```bash
# Test JavaScript
cat > tests/app.test.js << 'EOF'
// Test suite for WebApp
describe('WebApp', () => {
    test('should initialize with correct version', () => {
        const app = new WebApp();
        expect(app.version).toBe('1.0.0');
    });
    
    test('should have init method', () => {
        const app = new WebApp();
        expect(typeof app.init).toBe('function');
    });
});
EOF
```

#### File Temporanei e di Build
```bash
# Simula file di build
mkdir -p dist logs temp
echo "/* Minified CSS */" > dist/main.min.css
echo "// Minified JS" > dist/app.min.js
echo "2024-01-15 10:30:00 - App started" > logs/app.log
echo "temp data" > temp/cache.tmp

# File del sistema operativo
touch .DS_Store  # macOS
touch Thumbs.db  # Windows
```

### Passo 3: Configurazione .gitignore

```bash
cat > .gitignore << 'EOF'
# Dependencies
node_modules/
npm-debug.log*

# Build outputs
dist/
build/

# Environment & Secrets
config/production.json
.env
.env.local
.env.production

# Logs
logs/
*.log

# Temporary files
temp/
*.tmp
*.cache

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# IDE files
.vscode/
.idea/
*.swp
*.swo

# Coverage reports
coverage/
*.coverage
EOF
```

### Passo 4: Tracking Selettivo

```bash
# Controlliamo lo stato prima di aggiungere
git status

# Aggiungiamo prima il .gitignore
git add .gitignore
git commit -m "🙈 Add comprehensive .gitignore

- Exclude build outputs and dependencies
- Ignore sensitive configuration files
- Skip temporary and OS files
- Exclude IDE specific files"

# Ora aggiungiamo i file sorgente
git add src/ index.html package.json
git commit -m "✨ Add core application files

- HTML entry point with semantic structure
- JavaScript app class with ES6 features
- CSS with modern variables and responsive design
- Package.json with development dependencies"

# Aggiungiamo documentazione
git add README.md docs/
git commit -m "📚 Add project documentation

- Comprehensive README with quick start
- API documentation with examples
- Clear project structure explanation"

# Aggiungiamo configurazione di sviluppo
git add config/development.json
git commit -m "⚙️ Add development configuration

- Database connection settings
- API configuration for local development
- Logging configuration for debugging"

# Aggiungiamo i test
git add tests/
git commit -m "🧪 Add initial test suite

- Unit tests for WebApp class
- Jest testing framework setup
- Foundation for TDD approach"
```

### Passo 5: Verifica del Tracking

```bash
# Vediamo cosa è tracciato
git ls-files

# Verifichiamo cosa è ignorato
git status --ignored

# Visualizziamo la cronologia
git log --oneline --graph
```

## 🔍 Analisi dei Tipi di File

### File di Testo (Tracciati Efficacemente)
```bash
# Git può mostrare differenze dettagliate
git diff HEAD~1 src/js/app.js

# Le modifiche sono visibili riga per riga
git log -p --follow src/css/main.css
```

### File Binari (Tracciati ma non "diffabili")
```bash
# Se avessimo immagini o font
# git add assets/images/logo.png
# Git li traccia ma mostra solo "binary file changed"
```

### File Ignorati (Non Tracciati)
```bash
# Questi file non appaiono in git status
ls -la logs/  # File esistono
git status    # Ma Git li ignora
```

## 📊 Statistiche del Repository

```bash
# Numero di file tracciati per tipo
git ls-files | grep -E '\.(js|css|html)$' | wc -l
git ls-files | grep -E '\.(md|json)$' | wc -l

# Dimensione del repository
du -sh .git/

# File più modificati
git log --name-only --pretty=format: | sort | uniq -c | sort -nr
```

## 💡 Best Practices Dimostrate

### 1. **Struttura di .gitignore Organizzata**
```bash
# Sezioni logiche con commenti
# Dependencies
# Build outputs
# Environment & Secrets
# Logs
# Temporary files
# OS generated files
# IDE files
```

### 2. **Commit Atomici per Tipo**
- 🙈 Setup (gitignore)
- ✨ Features (codice applicativo)
- 📚 Documentation
- ⚙️ Configuration
- 🧪 Tests

### 3. **Tracking Strategico**
```bash
# ✅ Traccia: Codice sorgente
# ✅ Traccia: Documentazione
# ✅ Traccia: Configurazione di sviluppo
# ❌ Ignora: File di build
# ❌ Ignora: Dati sensibili
# ❌ Ignora: File temporanei
```

## 🎯 Risultati Attesi

Dopo questo esempio:
- Repository organizzato con tracking ottimale
- Comprensione di quando tracciare/ignorare file
- Configurazione `.gitignore` efficace
- Cronologia pulita con commit logici

## 🔧 Comandi Utili per il Debug

```bash
# Verifica cosa è ignorato
git status --ignored

# Vedi tutti i file tracciati
git ls-files

# Controlla perché un file è ignorato
git check-ignore -v filename

# Forza l'aggiunta di un file ignorato
git add -f config/production.json

# Rimuovi file dal tracking (mantieni localmente)
git rm --cached config/production.json
```

## 🚀 Esperimenti da Provare

1. **Modifica i file** e osserva come Git traccia le differenze
2. **Aggiungi nuovi tipi di file** (immagini, PDF) e osserva il comportamento
3. **Testa il .gitignore** aggiungendo file che dovrebbero essere ignorati
4. **Simula errori** aggiungendo accidentalmente file sensibili

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ Esempio Precedente](02-repository-documentazione.md)
- [➡️ Modulo Successivo](../../04-Comandi-Base-Git/README.md)
- [📝 Esercizi](../esercizi/README.md)
