# Setup Progetto Node.js con .gitignore

## 🎯 Scenario

Stai iniziando un nuovo progetto Node.js e vuoi configurare correttamente il `.gitignore` per evitare di committare file indesiderati come `node_modules`, file di log, e configurazioni sensibili.

## 📋 Obiettivi

- Configurare `.gitignore` per un progetto Node.js
- Gestire dipendenze e build artifacts
- Proteggere file di configurazione sensibili
- Ottimizzare le performance del repository

## 🚀 Setup Progetto

### Passo 1: Inizializzazione del Progetto

```bash
# Crea il progetto
mkdir node-gitignore-example
cd node-gitignore-example

# Inizializza Git (PRIMA di npm init!)
git init
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"

# Inizializza Node.js
npm init -y
```

### Passo 2: Creazione .gitignore Base

```bash
# Crea .gitignore PRIMA di installare dipendenze
cat > .gitignore << 'EOF'
# === NODE.JS ===
# Dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# Runtime data
pids
*.pid
*.seed
*.pid.lock

# Coverage directory used by tools like istanbul
coverage/
*.lcov

# nyc test coverage
.nyc_output

# Grunt intermediate storage
.grunt

# Bower dependency directory
bower_components

# node-waf configuration
.lock-wscript

# Compiled binary addons
build/Release

# Dependency directories
node_modules/
jspm_packages/

# Snowpack dependency directory
web_modules/

# TypeScript cache
*.tsbuildinfo

# Optional npm cache directory
.npm

# Optional eslint cache
.eslintcache

# Optional stylelint cache
.stylelintcache

# Microbundle cache
.rpt2_cache/
.rts2_cache_cjs/
.rts2_cache_es/
.rts2_cache_umd/

# Optional REPL history
.node_repl_history

# Output of 'npm pack'
*.tgz

# Yarn Integrity file
.yarn-integrity

# dotenv environment variables file
.env
.env.test
.env.production
.env.local
.env.development.local
.env.test.local
.env.production.local

# parcel-bundler cache
.cache
.parcel-cache

# Next.js build output
.next

# Nuxt.js build / generate output
.nuxt
dist

# Gatsby files
.cache/
public

# Vuepress build output
.vuepress/dist

# Serverless directories
.serverless/

# FuseBox cache
.fusebox/

# DynamoDB Local files
.dynamodb/

# TernJS port file
.tern-port

# Stores VSCode versions used for testing VSCode extensions
.vscode-test

# yarn v2
.yarn/cache
.yarn/unplugged
.yarn/build-state.yml
.yarn/install-state.gz
.pnp.*
EOF
```

### Passo 3: Installazione Dipendenze

```bash
# Installa dipendenze di sviluppo
npm install --save-dev nodemon eslint prettier

# Installa dipendenze di produzione
npm install express dotenv cors helmet

# Verifica che node_modules non sia tracciato
git status
# Dovrebbe mostrare solo package.json e package-lock.json
```

## 📁 Struttura del Progetto

### Passo 4: Creazione Struttura File

```bash
# Crea struttura directory
mkdir -p {src,tests,docs,scripts,config}

# File principale
cat > src/app.js << 'EOF'
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(helmet());
app.use(cors());
app.use(express.json());

// Routes
app.get('/', (req, res) => {
    res.json({
        message: 'Hello World!',
        environment: process.env.NODE_ENV || 'development',
        version: process.env.npm_package_version
    });
});

app.get('/health', (req, res) => {
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

// Error handling
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ error: 'Something went wrong!' });
});

// Start server
if (require.main === module) {
    app.listen(PORT, () => {
        console.log(`Server running on port ${PORT}`);
        console.log(`Environment: ${process.env.NODE_ENV || 'development'}`);
    });
}

module.exports = app;
EOF

# File di configurazione ambiente (TEMPLATE)
cat > .env.template << 'EOF'
# Server Configuration
PORT=3000
NODE_ENV=development

# Database
DATABASE_URL=mongodb://localhost:27017/myapp

# API Keys (NON committare i valori reali!)
API_KEY=your-api-key-here
JWT_SECRET=your-jwt-secret-here

# External Services
REDIS_URL=redis://localhost:6379
MAIL_SERVICE_API_KEY=your-mail-api-key
EOF

# File di configurazione reale (sarà ignorato)
cp .env.template .env
```

### Passo 5: Test e Script

```bash
# Test file
cat > tests/app.test.js << 'EOF'
const request = require('supertest');
const app = require('../src/app');

describe('App', () => {
    test('GET / should return hello message', async () => {
        const response = await request(app).get('/');
        expect(response.status).toBe(200);
        expect(response.body.message).toBe('Hello World!');
    });

    test('GET /health should return OK', async () => {
        const response = await request(app).get('/health');
        expect(response.status).toBe(200);
        expect(response.body.status).toBe('OK');
    });
});
EOF

# Package.json scripts
npm pkg set scripts.start="node src/app.js"
npm pkg set scripts.dev="nodemon src/app.js"
npm pkg set scripts.test="jest"
npm pkg set scripts.lint="eslint src/"
npm pkg set scripts.format="prettier --write src/"

# Installa Jest per i test
npm install --save-dev jest supertest
```

## 🔧 Configurazione Avanzata

### Passo 6: File di Build e Cache

```bash
# Simula file di build (saranno ignorati)
mkdir -p build dist .cache temp

echo "// Compiled code" > build/app.min.js
echo "/* Compiled styles */" > build/styles.min.css
echo "Cache data" > .cache/build-cache.json
echo "Temporary file" > temp/processing.tmp

# Crea log files (saranno ignorati)
mkdir -p logs
echo "[2024-01-15] App started" > logs/app.log
echo "[2024-01-15] Error occurred" > logs/error.log
echo "Debug info" > debug.log

# Verifica che questi file siano ignorati
git status
# Non dovrebbero apparire nei file untracked
```

### Passo 7: Configurazione IDE

```bash
# Configurazione VSCode (parzialmente ignorata)
mkdir -p .vscode

# File condivisi con il team
cat > .vscode/tasks.json << 'EOF'
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "npm: start",
            "type": "npm",
            "script": "start",
            "group": "build"
        },
        {
            "label": "npm: test",
            "type": "npm",
            "script": "test",
            "group": "test"
        }
    ]
}
EOF

cat > .vscode/launch.json << 'EOF'
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Launch App",
            "type": "node",
            "request": "launch",
            "program": "${workspaceFolder}/src/app.js",
            "env": {
                "NODE_ENV": "development"
            }
        }
    ]
}
EOF

# File personali (saranno ignorati dal gitignore globale)
cat > .vscode/settings.json << 'EOF'
{
    "editor.tabSize": 2,
    "editor.insertSpaces": true,
    "editor.formatOnSave": true,
    "eslint.autoFixOnSave": true
}
EOF
```

## 🧪 Test del .gitignore

### Passo 8: Verifica Funzionamento

```bash
# Controlla stato Git
echo "📊 Status Git:"
git status

echo ""
echo "🔍 Verifica file ignorati:"

# Test specifici
test_files=(
    "node_modules"
    ".env"
    "logs/app.log"
    "build/app.min.js"
    ".cache/build-cache.json"
    "debug.log"
)

for file in "${test_files[@]}"; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "   ✅ $file è correttamente ignorato"
    else
        echo "   ❌ $file NON è ignorato (verificare .gitignore)"
    fi
done

echo ""
echo "📁 File da tracciare:"
git ls-files 2>/dev/null || echo "Nessun file ancora tracciato"
```

### Passo 9: Primo Commit

```bash
# Aggiungi file appropriati
git add .

# Verifica cosa verrà committato
echo "📋 File da committare:"
git diff --cached --name-only

# Commit iniziale
git commit -m "Initial Node.js project setup

- Configured comprehensive .gitignore
- Added Express.js server with basic routes
- Environment variables template
- VSCode configuration for team
- Test setup with Jest
- Development scripts with nodemon

Project structure:
- src/ - Source code
- tests/ - Test files  
- config/ - Configuration files
- .env.template - Environment template"

echo "✅ Progetto committato!"
```

## 📊 Analisi Performance

### Passo 10: Verifica Dimensioni

```bash
# Script per analizzare le dimensioni
cat > scripts/analyze-repo.sh << 'EOF'
#!/bin/bash

echo "📊 Analisi Repository"
echo "===================="

echo ""
echo "📁 Dimensioni directory:"
echo "   Repository totale: $(du -sh . | cut -f1)"
echo "   .git directory: $(du -sh .git | cut -f1)"
echo "   node_modules: $(du -sh node_modules 2>/dev/null | cut -f1 || echo 'Non presente')"

echo ""
echo "📄 Conteggio file:"
echo "   File tracciati: $(git ls-files | wc -l)"
echo "   File totali (con ignore): $(find . -type f | wc -l)"
echo "   File ignorati: $(($(find . -type f | wc -l) - $(git ls-files | wc -l)))"

echo ""
echo "🎯 File ignorati più grandi:"
find . -name "node_modules" -prune -o -type f -exec du -h {} \; 2>/dev/null | \
    sort -hr | head -5 | while read size file; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "   $size $file"
    fi
done
EOF

chmod +x scripts/analyze-repo.sh
./scripts/analyze-repo.sh
```

## 🔄 Workflow di Sviluppo

### Passo 11: Script di Utilità

```bash
# Script di pulizia
cat > scripts/clean.sh << 'EOF'
#!/bin/bash

echo "🧹 Pulizia ambiente di sviluppo..."

# Rimuovi file temporanei
rm -rf temp/
rm -rf .cache/
rm -rf build/
rm -rf dist/
rm -f *.log
rm -rf logs/

# Pulisci cache npm
npm cache clean --force

echo "✅ Pulizia completata!"
EOF

# Script di setup per nuovi sviluppatori
cat > scripts/setup.sh << 'EOF'
#!/bin/bash

echo "🚀 Setup ambiente di sviluppo..."

# Verifica Node.js
if ! command -v node &> /dev/null; then
    echo "❌ Node.js non installato!"
    exit 1
fi

echo "✅ Node.js $(node --version)"

# Verifica file .env
if [ ! -f ".env" ]; then
    echo "📝 Creazione file .env da template..."
    cp .env.template .env
    echo "⚠️  IMPORTANTE: Configura le variabili in .env"
fi

# Installa dipendenze
echo "📦 Installazione dipendenze..."
npm install

# Verifica setup
echo "🧪 Test configurazione..."
npm test

echo "✅ Setup completato!"
echo ""
echo "📋 Comandi disponibili:"
echo "   npm start     - Avvia server produzione"
echo "   npm run dev   - Avvia server sviluppo"
echo "   npm test      - Esegui test"
echo "   npm run lint  - Controlla codice"
EOF

chmod +x scripts/clean.sh scripts/setup.sh
```

## 📝 Documentazione

### Passo 12: README Completo

```bash
cat > README.md << 'EOF'
# Node.js Project with Proper .gitignore

Un progetto Node.js di esempio che dimostra la configurazione corretta di `.gitignore` per evitare problemi comuni.

## 🚀 Quick Start

```bash
# Clone e setup
git clone <repository-url>
cd node-gitignore-example
./scripts/setup.sh

# Avvia in sviluppo
npm run dev
```

## 📁 Struttura Progetto

```
node-gitignore-example/
├── src/                    # Codice sorgente
│   └── app.js             # Server Express
├── tests/                 # Test unitari
│   └── app.test.js
├── scripts/               # Script di utilità
│   ├── setup.sh          # Setup sviluppatori
│   ├── clean.sh          # Pulizia ambiente
│   └── analyze-repo.sh   # Analisi repository
├── .vscode/              # Configurazione IDE
│   ├── tasks.json        # Task condivisi
│   └── launch.json       # Debug config
├── .env.template         # Template variabili ambiente
├── .gitignore           # Regole ignore (IMPORTANTE!)
└── package.json         # Configurazione Node.js
```

## 🔒 File Ignorati

Il `.gitignore` è configurato per ignorare:

- **node_modules/** - Dipendenze (riinstallare con npm install)
- **.env** - Variabili ambiente sensibili
- **logs/*.log** - File di log
- **build/**, **dist/** - Artifact di build
- **.cache/** - File di cache
- **coverage/** - Report coverage test

## 🛠️ Configurazione Ambiente

1. Copia `.env.template` in `.env`
2. Configura le variabili necessarie:
   ```bash
   cp .env.template .env
   # Modifica .env con i tuoi valori
   ```

## 📊 Comandi Disponibili

- `npm start` - Avvia server produzione
- `npm run dev` - Avvia server sviluppo (nodemon)
- `npm test` - Esegui test
- `npm run lint` - Controlla codice con ESLint
- `npm run format` - Formatta codice con Prettier

## 🧪 Testing

```bash
# Esegui tutti i test
npm test

# Test in watch mode
npm test -- --watch
```

## 🚨 Problemi Comuni

### node_modules tracciato per errore
```bash
git rm -r --cached node_modules/
git commit -m "Remove node_modules from tracking"
```

### File .env committato per errore
```bash
git rm --cached .env
git commit -m "Remove .env from tracking"
# Poi aggiungi .env al .gitignore se non già presente
```

## 📈 Performance

Repository ottimizzato:
- ✅ Solo file sorgente tracciati
- ✅ Dipendenze escluse (risparmio GB)
- ✅ File temporanei ignorati
- ✅ Configurazioni sensibili protette

## 🤝 Contribuire

1. Fork del repository
2. Crea feature branch
3. Configura ambiente: `./scripts/setup.sh`
4. Sviluppa e testa
5. Commit con messaggi descrittivi
6. Push e Pull Request
EOF
```

## ✅ Verifica Finale

```bash
# Test completo del setup
echo "🎯 Verifica finale del progetto..."

# 1. Verifica Git status
echo "📊 Git status:"
git status

# 2. Test applicazione
echo ""
echo "🧪 Test applicazione:"
npm test

# 3. Verifica ignore
echo ""
echo "🔍 Verifica .gitignore:"
./scripts/analyze-repo.sh

# 4. Test server
echo ""
echo "🌐 Test server (5 secondi):"
npm start &
SERVER_PID=$!
sleep 2
curl -s http://localhost:3000/health | jq .
kill $SERVER_PID

echo ""
echo "✅ Setup Node.js con .gitignore completato!"
echo "📚 Vedi README.md per ulteriori dettagli"
```

## 🎯 Risultato Atteso

Al termine dovresti avere:

- ✅ Repository pulito con solo file necessari tracciati
- ✅ node_modules/ completamente ignorato  
- ✅ File .env protetto ma template condiviso
- ✅ Build artifacts ignorati
- ✅ Configurazione IDE bilanciata (condivisa/personale)
- ✅ Script di automazione per il team
- ✅ Documentazione completa

**Dimensioni tipiche:**
- **Con .gitignore**: ~50KB repository Git
- **Senza .gitignore**: ~100MB+ (con node_modules)

---

> 💡 **Lesson Learned**: Un `.gitignore` ben configurato fin dall'inizio previene problemi, migliora le performance e protegge dati sensibili!
