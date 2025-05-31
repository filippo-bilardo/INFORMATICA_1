# Esercizio 3: Pulizia e Gestione Avanzata del Repository

## 🎯 Obiettivo
Masterizzare la gestione avanzata dei file in Git, inclusa la pulizia del repository, la gestione di file sensibili e l'ottimizzazione della struttura.

## 📋 Prerequisiti
- Completamento degli Esercizi 1 e 2
- Conoscenza avanzata di Git
- Familiarità con `.gitignore`

## 🔧 Scenario
Stai lavorando su un progetto che si è "sporcato" nel tempo con file temporanei, build artifacts, credenziali accidentalmente committate e una struttura disordinata. Devi pulire tutto mantenendo la cronologia importante.

## 📝 Istruzioni

### Passo 1: Simulazione di un Progetto "Sporco"
Crea un progetto con vari problemi tipici:

```bash
mkdir esercizio-pulizia-avanzata
cd esercizio-pulizia-avanzata
git init
git config user.name "Il Tuo Nome"
git config user.email "tuo.email@example.com"

# Struttura del progetto con problemi
mkdir -p src/{components,utils,assets} build dist node_modules tests logs

# File sorgente validi
cat > src/index.js << 'EOF'
import { helper } from './utils/helper.js';
import config from './config.js';

console.log('Applicazione avviata');
console.log('API Key:', config.apiKey); // PROBLEMA: espone credenziali
EOF

cat > src/utils/helper.js << 'EOF'
export const helper = {
    formatDate: (date) => date.toISOString(),
    log: (message) => console.log(`[${new Date().toISOString()}] ${message}`)
};
EOF

cat > src/config.js << 'EOF'
// PROBLEMA: file con credenziali sensibili
export default {
    apiKey: 'sk-1234567890abcdef',
    databaseUrl: 'mongodb://admin:password123@localhost:27017/myapp',
    secretKey: 'super-secret-key-12345'
};
EOF

# File di build (non dovrebbero essere nel repository)
echo "var app=function(){console.log('built app')}" > build/app.min.js
echo "body{color:red}" > build/styles.min.css

# Dipendenze (non dovrebbero essere nel repository)
mkdir -p node_modules/lodash
echo "module.exports = {}" > node_modules/lodash/index.js

# File di log (non dovrebbero essere nel repository)
echo "[2024-01-15] App started" > logs/app.log
echo "[2024-01-15] Error occurred" > logs/error.log

# File temporanei
echo "temp data" > temp.txt
echo "temp cache" > .cache
echo "OS file" > .DS_Store

# File di backup
cp src/index.js src/index.js.backup
cp src/config.js src/config.js.old

# Test files con problemi
cat > tests/test.spec.js << 'EOF'
import config from '../src/config.js';

describe('App Tests', () => {
    test('should connect to database', () => {
        expect(config.databaseUrl).toBeDefined();
        // PROBLEMA: test che dipende da credenziali
    });
});
EOF

# File di documentazione valido
cat > README.md << 'EOF'
# Il Mio Progetto

Questo è un progetto di esempio per l'apprendimento di Git.

## Setup
1. npm install
2. npm start

## Test
npm test
EOF

# Package.json
cat > package.json << 'EOF'
{
    "name": "mio-progetto",
    "version": "1.0.0",
    "scripts": {
        "start": "node src/index.js",
        "build": "webpack",
        "test": "jest"
    },
    "dependencies": {
        "lodash": "^4.17.21"
    }
}
EOF

# Commit tutto (simulando errori del passato)
git add .
git commit -m "Initial commit con tutti i file (MALE!)"
```

### Passo 2: Audit del Repository
Analizza cosa c'è di sbagliato:

```bash
# Visualizza tutti i file tracciati
git ls-files

# Controlla la dimensione del repository
du -sh .git

# Trova file grandi
git ls-files | xargs ls -la | sort -k5 -nr | head -10

# Verifica i file sensibili
grep -r "password\|secret\|key" . --exclude-dir=.git
```

### Passo 3: Creazione di .gitignore Appropriato
Crea un `.gitignore` completo:

```bash
cat > .gitignore << 'EOF'
# Dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Build outputs
build/
dist/
*.min.js
*.min.css

# Environment variables e configurazioni sensibili
.env
.env.local
.env.production
config.js
**/config.js

# Logs
logs/
*.log

# Cache e file temporanei
.cache
.tmp
temp.*
*.tmp

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Editor files
.vscode/
.idea/
*.swp
*.swo

# Backup files
*.backup
*.bak
*.old

# Test coverage
coverage/
.nyc_output

# Runtime data
pids
*.pid
*.seed
*.pid.lock
EOF
```

### Passo 4: Rimozione File Sensibili dalla Cronologia
⚠️ **ATTENZIONE**: Queste operazioni riscrivono la cronologia!

```bash
# Rimuovi file sensibili dalla cronologia
git filter-branch --force --index-filter \
    'git rm --cached --ignore-unmatch src/config.js' \
    --prune-empty --tag-name-filter cat -- --all

# Alternativa moderna con git-filter-repo (se disponibile)
# git filter-repo --path src/config.js --invert-paths

# Pulizia dei riferimenti
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive
```

### Passo 5: Pulizia File Attuali
```bash
# Rimuovi file che ora sono in .gitignore
git rm -r --cached build/ dist/ node_modules/ logs/
git rm --cached temp.txt .cache .DS_Store
git rm --cached src/index.js.backup src/config.js.old

# Verifica cosa verrà rimosso
git status
```

### Passo 6: Creazione di Configurazione Template
Crea un file di configurazione template sicuro:

```bash
cat > src/config.template.js << 'EOF'
// Template per la configurazione
// Copia questo file come config.js e inserisci i valori reali

export default {
    apiKey: 'your-api-key-here',
    databaseUrl: 'your-database-url-here',
    secretKey: 'your-secret-key-here',
    
    // Configurazioni non sensibili
    appName: 'Il Mio Progetto',
    version: '1.0.0',
    environment: process.env.NODE_ENV || 'development'
};
EOF

# Aggiorna il README
cat >> README.md << 'EOF'

## Configurazione

1. Copia `src/config.template.js` in `src/config.js`
2. Inserisci le tue credenziali reali nel file `config.js`
3. Non committare mai il file `config.js`!

## Variabili d'ambiente
- `NODE_ENV`: development|production
- `API_KEY`: La tua chiave API
- `DATABASE_URL`: URL del database
EOF
```

### Passo 7: Refactoring del Codice
Aggiorna il codice per non dipendere da file sensibili:

```bash
cat > src/config.js << 'EOF'
// Configurazione che usa variabili d'ambiente
export default {
    apiKey: process.env.API_KEY || 'development-key',
    databaseUrl: process.env.DATABASE_URL || 'mongodb://localhost:27017/myapp-dev',
    secretKey: process.env.SECRET_KEY || 'dev-secret-key',
    
    appName: 'Il Mio Progetto',
    version: '1.0.0',
    environment: process.env.NODE_ENV || 'development'
};
EOF

# Aggiorna i test per non dipendere da credenziali reali
cat > tests/test.spec.js << 'EOF'
import config from '../src/config.js';

describe('App Tests', () => {
    test('should have required config properties', () => {
        expect(config.apiKey).toBeDefined();
        expect(config.databaseUrl).toBeDefined();
        expect(config.appName).toBe('Il Mio Progetto');
    });
    
    test('should use environment variables', () => {
        // Test che non dipende da credenziali reali
        expect(config.environment).toBe('development');
    });
});
EOF
```

### Passo 8: Riorganizzazione Struttura
Migliora l'organizzazione del progetto:

```bash
# Crea una struttura più pulita
mkdir -p src/{config,services,tests}

# Sposta i file di test
git mv tests/test.spec.js src/tests/

# Sposta la configurazione
git mv src/config.template.js src/config/

# Crea file di esempio per servizi
cat > src/services/api.js << 'EOF'
import config from '../config.js';

class ApiService {
    constructor() {
        this.baseUrl = 'https://api.example.com';
        this.apiKey = config.apiKey;
    }
    
    async getData() {
        // Implementazione API
        console.log('Fetching data...');
    }
}

export default ApiService;
EOF

# Aggiorna l'index.js
cat > src/index.js << 'EOF'
import { helper } from './utils/helper.js';
import config from './config.js';
import ApiService from './services/api.js';

helper.log('Applicazione avviata');
helper.log(`Ambiente: ${config.environment}`);

const api = new ApiService();
api.getData();
EOF
```

### Passo 9: Script di Automazione
Crea script per automatizzare la pulizia:

```bash
cat > scripts/clean.sh << 'EOF'
#!/bin/bash

echo "🧹 Pulizia del repository in corso..."

# Rimuovi file temporanei
find . -name "*.tmp" -delete
find . -name "temp.*" -delete
find . -name ".DS_Store" -delete

# Rimuovi directory di build
rm -rf build/ dist/

# Pulizia Git
git clean -fd

echo "✅ Pulizia completata!"
EOF

chmod +x scripts/clean.sh

cat > scripts/setup.sh << 'EOF'
#!/bin/bash

echo "🚀 Setup del progetto..."

# Controlla se esiste config.js
if [ ! -f "src/config.js" ]; then
    echo "⚠️  File config.js mancante!"
    echo "   Copia src/config/config.template.js in src/config.js"
    echo "   e inserisci le tue credenziali."
    exit 1
fi

# Installa dipendenze (se esistono)
if [ -f "package.json" ]; then
    echo "📦 Installazione dipendenze..."
    npm install
fi

echo "✅ Setup completato!"
EOF

chmod +x scripts/setup.sh
```

### Passo 10: Documentazione della Pulizia
Documenta cosa hai fatto:

```bash
cat > CLEANUP.md << 'EOF'
# Log di Pulizia Repository

## Problemi Identificati
- [x] File di configurazione con credenziali committati
- [x] Dipendenze node_modules nel repository
- [x] File di build committati
- [x] File di log e temporanei tracciati
- [x] File di backup duplicati
- [x] Mancanza di .gitignore appropriato

## Azioni Intraprese

### 1. Creazione .gitignore
- Aggiunte regole per node_modules, build, logs
- Esclusi file temporanei e di sistema
- Esclusi file di configurazione sensibili

### 2. Rimozione File Sensibili
- Rimosso src/config.js dalla cronologia con git filter-branch
- Creato template di configurazione sicuro
- Aggiornato codice per usare variabili d'ambiente

### 3. Pulizia Struttura
- Rimossi file di build e dipendenze
- Eliminati file temporanei e backup
- Riorganizzata struttura directory

### 4. Script di Automazione
- Creato script/clean.sh per pulizia automatica
- Creato script/setup.sh per setup progetto

## Risultato
Repository pulito, sicuro e ben organizzato.
EOF
```

### Passo 11: Commit Finale
```bash
# Aggiungi tutti i miglioramenti
git add .

# Commit con messaggio dettagliato
git commit -m "Pulizia completa del repository

- Rimossi file sensibili dalla cronologia
- Aggiunto .gitignore completo
- Creata configurazione template sicura
- Refactoring per usare variabili d'ambiente
- Riorganizzata struttura progetto
- Aggiunti script di automazione
- Documentata la pulizia effettuata

BREAKING CHANGE: Rimosso src/config.js, ora serve setup manuale"

# Verifica il risultato
git status
git log --oneline -5
```

## 🔍 Esercizio Bonus: Audit di Sicurezza

### Scan per Secrets
```bash
# Crea uno script per controllare secrets
cat > scripts/security-scan.sh << 'EOF'
#!/bin/bash

echo "🔍 Scansione sicurezza in corso..."

# Pattern comuni per secrets
patterns=(
    "password"
    "secret"
    "key.*[=:].*['\"][^'\"]{8,}"
    "token"
    "api[_-]?key"
    "auth"
)

found_issues=false

for pattern in "${patterns[@]}"; do
    results=$(grep -r -i "$pattern" src/ --include="*.js" --include="*.json" 2>/dev/null)
    if [ ! -z "$results" ]; then
        echo "⚠️  Pattern '$pattern' trovato:"
        echo "$results"
        found_issues=true
    fi
done

if [ "$found_issues" = false ]; then
    echo "✅ Nessun problema di sicurezza trovato!"
else
    echo "❌ Trovati potenziali problemi di sicurezza!"
    exit 1
fi
EOF

chmod +x scripts/security-scan.sh
./scripts/security-scan.sh
```

### Verifica Dimensioni Repository
```bash
# Script per monitorare dimensioni
cat > scripts/repo-stats.sh << 'EOF'
#!/bin/bash

echo "📊 Statistiche Repository"
echo "========================"

echo "📁 Dimensione totale: $(du -sh . | cut -f1)"
echo "🗂  Dimensione .git: $(du -sh .git | cut -f1)"
echo "📄 Numero file tracciati: $(git ls-files | wc -l)"
echo "🏷  Numero commit: $(git rev-list --count HEAD)"

echo ""
echo "📋 File più grandi:"
git ls-files | xargs ls -la | sort -k5 -nr | head -5 | awk '{print $5, $9}'

echo ""
echo "📂 Directory principali:"
du -sh */ 2>/dev/null | sort -hr | head -5
EOF

chmod +x scripts/repo-stats.sh
./scripts/repo-stats.sh
```

## ✅ Verifiche
Controlla che:
- [ ] Nessun file sensibile sia presente nel repository
- [ ] .gitignore blocchi correttamente i file non desiderati
- [ ] La configurazione usi variabili d'ambiente
- [ ] I test non dipendano da credenziali reali
- [ ] Gli script di automazione funzionino
- [ ] La documentazione sia aggiornata
- [ ] `git status` mostri solo file appropriati

## 🧪 Test di Verifica
```bash
# Test completo
./scripts/security-scan.sh
./scripts/repo-stats.sh
./scripts/clean.sh

# Verifica .gitignore
echo "test" > build/test.min.js
echo "secret=123" > .env
git status  # Non dovrebbe mostrare questi file

# Cleanup test
rm build/test.min.js .env

# Verifica struttura finale
tree -I 'node_modules|.git'
```

## 🤔 Domande di Riflessione
1. Perché è pericoloso committare credenziali in Git?
2. Come puoi automatizzare la prevenzione di questi problemi?
3. Quando è appropriato riscrivere la cronologia Git?
4. Come gestisci la configurazione in ambienti diversi?

## 🎯 Risultato Atteso
```
esercizio-pulizia-avanzata/
├── scripts/
│   ├── clean.sh
│   ├── setup.sh
│   ├── security-scan.sh
│   └── repo-stats.sh
├── src/
│   ├── config/
│   │   └── config.template.js
│   ├── services/
│   │   └── api.js
│   ├── tests/
│   │   └── test.spec.js
│   ├── utils/
│   │   └── helper.js
│   ├── config.js (escluso da .gitignore)
│   └── index.js
├── .gitignore
├── CLEANUP.md
├── README.md
└── package.json
```

Con un repository sicuro, pulito, ben documentato e con automazioni per mantenerlo tale.

---
[← Esercizio Precedente](./02-esercizio-intermedio.md) | [Torna alla Panoramica](../README.md) | [Modulo Successivo →](../../07-Git-Ignore/README.md)
