# Esercizio 04 - Time Travel Mastery e Repository Forensics

## 📋 Scenario

Come senior developer in una software house, devi padroneggiare la navigazione temporale in Git per risolvere problemi complessi: bug introdotti in momenti specifici, performance regression, e analisi forense di repository. Questo esercizio ti metterà alla prova con scenari realistici che richiedono expertise avanzata nella navigazione tra commit.

## 🎯 Obiettivi

- ⭐⭐⭐⭐⭐ **Livello**: Expert
- ⏱️ **Durata**: 90-120 minuti
- 🔧 **Competenze**: Git checkout, switch, detached HEAD, bisect, reflog
- 🎯 **Focus**: Debugging avanzato, analisi forense, recupero dati

---

## 🏗️ Setup Scenario Complesso

### 1. Creazione Repository di Test con Storia Ricca

```bash
# Creare directory di lavoro
mkdir git-time-travel-mastery
cd git-time-travel-mastery
git init

# Configurazione per l'esercizio
git config user.name "Senior Developer"
git config user.email "senior@company.com"

# Creare struttura iniziale del progetto
mkdir -p {src/{components,utils,api},tests,docs,config}

# File di configurazione iniziale
cat > package.json << 'EOF'
{
  "name": "webapp-project",
  "version": "1.0.0",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js",
    "test": "jest",
    "build": "webpack"
  },
  "dependencies": {
    "express": "^4.18.0",
    "lodash": "^4.17.0"
  }
}
EOF

# File principale dell'applicazione
cat > src/index.js << 'EOF'
const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
    res.json({ message: 'Hello World!', version: '1.0.0' });
});

app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});
EOF

# Utility iniziale
cat > src/utils/helper.js << 'EOF'
function calculateSum(a, b) {
    return a + b;
}

function formatDate(date) {
    return date.toISOString();
}

module.exports = { calculateSum, formatDate };
EOF

# Test iniziale
cat > tests/helper.test.js << 'EOF'
const { calculateSum } = require('../src/utils/helper');

test('calculateSum should add two numbers', () => {
    expect(calculateSum(2, 3)).toBe(5);
});
EOF

# README iniziale
cat > README.md << 'EOF'
# WebApp Project

Semplice applicazione web con Express.js

## Setup
npm install
npm start
EOF

git add .
git commit -m "feat: initial project setup with Express server

- Add package.json with dependencies
- Create basic Express server on port 3000
- Add utility functions for calculations
- Add initial test suite
- Create project documentation"
```

### 2. Creazione Storia Complessa con Diversi Branch

```bash
# === FASE 1: Sviluppo Feature Authentication ===
git checkout -b feature/authentication

# Aggiungere sistema auth
cat > src/auth.js << 'EOF'
const jwt = require('jsonwebtoken');

class AuthService {
    constructor() {
        this.secret = 'supersecret123'; // TODO: move to env
        this.users = [
            { id: 1, username: 'admin', password: 'admin123' },
            { id: 2, username: 'user', password: 'user123' }
        ];
    }

    authenticate(username, password) {
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            return jwt.sign({ userId: user.id }, this.secret);
        }
        return null;
    }

    verifyToken(token) {
        try {
            return jwt.verify(token, this.secret);
        } catch (error) {
            return null;
        }
    }
}

module.exports = AuthService;
EOF

# Aggiornare server per auth
cat > src/index.js << 'EOF'
const express = require('express');
const AuthService = require('./auth');

const app = express();
const port = 3000;
const authService = new AuthService();

app.use(express.json());

app.get('/', (req, res) => {
    res.json({ message: 'Hello World!', version: '1.1.0' });
});

app.post('/login', (req, res) => {
    const { username, password } = req.body;
    const token = authService.authenticate(username, password);
    
    if (token) {
        res.json({ token, message: 'Login successful' });
    } else {
        res.status(401).json({ error: 'Invalid credentials' });
    }
});

app.get('/protected', (req, res) => {
    const token = req.headers.authorization?.split(' ')[1];
    const decoded = authService.verifyToken(token);
    
    if (decoded) {
        res.json({ message: 'Protected data', userId: decoded.userId });
    } else {
        res.status(401).json({ error: 'Unauthorized' });
    }
});

app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});
EOF

git add .
git commit -m "feat(auth): implement JWT authentication system

- Add AuthService class with login/verify methods
- Implement /login endpoint for user authentication
- Add /protected route with token verification
- Update version to 1.1.0
- Add temporary hardcoded users (security issue to fix)"

# === BUG INTRODUCE - Security Issue ===
sleep 1
cat > src/auth.js << 'EOF'
const jwt = require('jsonwebtoken');

class AuthService {
    constructor() {
        this.secret = 'supersecret123'; // BUG: hardcoded secret
        this.users = [
            { id: 1, username: 'admin', password: 'admin123' },
            { id: 2, username: 'user', password: 'user123' },
            { id: 3, username: 'guest', password: '' } // BUG: empty password
        ];
    }

    authenticate(username, password) {
        const user = this.users.find(u => u.username === username);
        // BUG: allows empty password
        if (user && (user.password === password || !password)) {
            return jwt.sign({ userId: user.id, role: 'admin' }, this.secret); // BUG: all users get admin role
        }
        return null;
    }

    verifyToken(token) {
        try {
            return jwt.verify(token, this.secret);
        } catch (error) {
            return null;
        }
    }
}

module.exports = AuthService;
EOF

git add .
git commit -m "feat(auth): add guest user support

- Add guest user for demo purposes
- Allow flexible authentication for testing"

# === FASE 2: Feature API Enhancement ===
git checkout main
git merge feature/authentication

git checkout -b feature/api-enhancement

# Aggiungere più endpoint
cat > src/api/users.js << 'EOF'
const express = require('express');
const router = express.Router();

const users = [
    { id: 1, name: 'Alice', email: 'alice@example.com', role: 'admin' },
    { id: 2, name: 'Bob', email: 'bob@example.com', role: 'user' },
    { id: 3, name: 'Charlie', email: 'charlie@example.com', role: 'user' }
];

router.get('/', (req, res) => {
    res.json(users);
});

router.get('/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const user = users.find(u => u.id === id);
    
    if (user) {
        res.json(user);
    } else {
        res.status(404).json({ error: 'User not found' });
    }
});

// BUG: No authentication required
router.delete('/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const index = users.findIndex(u => u.id === id);
    
    if (index !== -1) {
        const deleted = users.splice(index, 1);
        res.json({ message: 'User deleted', user: deleted[0] });
    } else {
        res.status(404).json({ error: 'User not found' });
    }
});

module.exports = router;
EOF

# Aggiornare server principale
cat > src/index.js << 'EOF'
const express = require('express');
const AuthService = require('./auth');
const usersRouter = require('./api/users');

const app = express();
const port = 3000;
const authService = new AuthService();

app.use(express.json());

app.get('/', (req, res) => {
    res.json({ 
        message: 'WebApp API', 
        version: '1.2.0',
        endpoints: ['/login', '/protected', '/api/users']
    });
});

app.post('/login', (req, res) => {
    const { username, password } = req.body;
    const token = authService.authenticate(username, password);
    
    if (token) {
        res.json({ token, message: 'Login successful' });
    } else {
        res.status(401).json({ error: 'Invalid credentials' });
    }
});

app.get('/protected', (req, res) => {
    const token = req.headers.authorization?.split(' ')[1];
    const decoded = authService.verifyToken(token);
    
    if (decoded) {
        res.json({ message: 'Protected data', userId: decoded.userId });
    } else {
        res.status(401).json({ error: 'Unauthorized' });
    }
});

// Performance issue: no rate limiting
app.use('/api/users', usersRouter);

app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});
EOF

git add .
git commit -m "feat(api): add users CRUD endpoints

- Create users router with GET, DELETE operations
- Add user management functionality
- Update main server to include API routes
- Version bump to 1.2.0"

# === PERFORMANCE BUG ===
sleep 1
cat > src/utils/helper.js << 'EOF'
function calculateSum(a, b) {
    return a + b;
}

function formatDate(date) {
    return date.toISOString();
}

// BUG: Performance issue - inefficient algorithm
function processLargeData(data) {
    let result = [];
    for (let i = 0; i < data.length; i++) {
        for (let j = 0; j < data.length; j++) {
            for (let k = 0; k < data.length; k++) {
                if (data[i] === data[j] && data[j] === data[k]) {
                    result.push(data[i]);
                }
            }
        }
    }
    return result;
}

// Memory leak
let cache = {};
function memoize(fn) {
    return function(...args) {
        const key = args.join(',');
        if (cache[key]) {
            return cache[key];
        }
        cache[key] = fn.apply(this, args); // Never cleared
        return cache[key];
    };
}

module.exports = { calculateSum, formatDate, processLargeData, memoize };
EOF

git add .
git commit -m "feat(utils): add data processing and memoization

- Add processLargeData function for batch operations
- Implement memoization for performance optimization
- Enhance utility functions capabilities"

# === HOTFIX BRANCH ===
git checkout main
git merge feature/api-enhancement

git checkout -b hotfix/critical-security

# Fix parziale del security bug
cat > src/auth.js << 'EOF'
const jwt = require('jsonwebtoken');

class AuthService {
    constructor() {
        this.secret = process.env.JWT_SECRET || 'supersecret123'; // Partial fix
        this.users = [
            { id: 1, username: 'admin', password: 'admin123', role: 'admin' },
            { id: 2, username: 'user', password: 'user123', role: 'user' },
            // Removed guest user with empty password
        ];
    }

    authenticate(username, password) {
        if (!username || !password) {
            return null; // Fix: require both username and password
        }
        
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            return jwt.sign({ 
                userId: user.id, 
                role: user.role // Fix: use actual user role
            }, this.secret, { expiresIn: '1h' });
        }
        return null;
    }

    verifyToken(token) {
        try {
            return jwt.verify(token, this.secret);
        } catch (error) {
            return null;
        }
    }
}

module.exports = AuthService;
EOF

git add .
git commit -m "fix(security): patch critical authentication vulnerabilities

- Remove guest user with empty password
- Require both username and password for auth
- Use actual user roles instead of hardcoded admin
- Add token expiration (1 hour)
- Partial environment variable support for JWT secret"

git checkout main
git merge hotfix/critical-security

# === EXPERIMENTAL BRANCH ===
git checkout -b experimental/new-features

# Aggiungere feature sperimentale
cat > src/experimental.js << 'EOF'
// Experimental WebSocket support
const WebSocket = require('ws');

class RealtimeService {
    constructor() {
        this.connections = new Set();
        this.server = null;
    }

    start(port = 8080) {
        this.server = new WebSocket.Server({ port });
        
        this.server.on('connection', (ws) => {
            this.connections.add(ws);
            console.log('New WebSocket connection');
            
            ws.on('message', (message) => {
                // Broadcast to all connections
                this.broadcast(message);
            });
            
            ws.on('close', () => {
                this.connections.delete(ws);
                console.log('WebSocket connection closed');
            });
        });
    }

    broadcast(message) {
        this.connections.forEach(ws => {
            if (ws.readyState === WebSocket.OPEN) {
                ws.send(message);
            }
        });
    }
}

module.exports = RealtimeService;
EOF

git add .
git commit -m "experimental: add WebSocket realtime functionality

- Implement RealtimeService for WebSocket connections
- Add broadcasting capabilities
- Connection management with Set
- Experimental feature for future evaluation"

# === TAG RELEASES ===
git checkout main
git tag v1.0.0 HEAD~3 -m "Release 1.0.0 - Initial stable release"
git tag v1.1.0 HEAD~2 -m "Release 1.1.0 - Authentication system"
git tag v1.2.0 HEAD~1 -m "Release 1.2.0 - API enhancements"
git tag v1.2.1 HEAD -m "Release 1.2.1 - Security hotfix"

echo "✅ Repository setup completo con storia complessa!"
echo "📊 Branches: main, feature/authentication, feature/api-enhancement, hotfix/critical-security, experimental/new-features"
echo "🏷️ Tags: v1.0.0, v1.1.0, v1.2.0, v1.2.1"
echo "🐛 Bug presenti: Security issues, Performance problems, Memory leaks"
```

---

## 🕵️ Parte 1: Analisi Forense e Bug Detection

### Missione 1.1: Security Audit Temporale

**Scenario**: Il security team ha identificato vulnerabilità nel sistema di autenticazione. Devi tracciare quando e come sono state introdotte.

```bash
# 1. Identifica quando è stato introdotto il guest user con password vuota
echo "🔍 ANALISI: Trova il commit che ha introdotto il guest user vulnerability"

# TODO: Usa git log per trovare commit sospetti
# Suggerimento: cerca "guest" nei commit

# 2. Naviga al commit specifico e analizza il codice
echo "📍 Naviga al commit vulnerabile e analizza il codice auth.js"

# TODO: Usa git checkout per andare al commit specifico
# TODO: Esamina il file src/auth.js per vedere il codice vulnerabile

# 3. Confronta con la versione precedente
echo "🔄 Confronta con la versione precedente per vedere le differenze"

# TODO: Usa git diff per vedere cosa è cambiato

# 4. Verifica se la vulnerabilità esiste in tutti i branch
echo "🌿 Controlla se la vulnerabilità è presente in altri branch"

# TODO: Controlla branch feature/api-enhancement
# TODO: Controlla branch experimental/new-features
```

### Missione 1.2: Performance Regression Hunt

**Scenario**: Gli utenti segnalano problemi di performance. Devi identificare quando è stata introdotta la funzione problematica.

```bash
# 1. Trova quando è stata aggiunta la funzione processLargeData
echo "🐌 ANALISI: Trova quando è stata introdotta la performance regression"

# TODO: Cerca nei commit la parola "processLargeData"
# TODO: Naviga al commit che ha introdotto la funzione

# 2. Analizza l'algoritmo problematico
echo "🔬 Analizza l'algoritmo O(n³) problematico"

# TODO: Esamina il codice della funzione processLargeData
# TODO: Identifica perché è inefficiente

# 3. Usa git bisect per trovare il commit esatto (simulazione)
echo "🎯 Simula git bisect per trovare la regression"

# Setup bisect simulation
git bisect start
git bisect bad main  # Versione attuale ha il bug
git bisect good v1.0.0  # Versione 1.0.0 era buona

# TODO: Continua il bisect process
# git bisect run ./test-performance.sh (se avessi uno script di test)
```

### Missione 1.3: Memory Leak Investigation

**Scenario**: Il server si arresta dopo alcune ore di utilizzo. Sospetti un memory leak.

```bash
# 1. Trova quando è stata introdotta la funzione memoize
echo "🧠 ANALISI: Traccia l'introduzione del memory leak"

# TODO: Cerca la funzione memoize nella storia
# TODO: Identifica perché causa memory leak

# 2. Simula il debug del memory leak
cat > debug-memory.js << 'EOF'
const { memoize } = require('./src/utils/helper');

// Simula l'uso che causa memory leak
const expensiveFunction = memoize((x) => x * 2);

// Genera molte chiamate con parametri diversi
for (let i = 0; i < 10000; i++) {
    expensiveFunction(i);
}

console.log('Cache never gets cleared - memory leak!');
EOF

# TODO: Esegui il debug script se vuoi vedere il leak in azione
```

---

## 🔄 Parte 2: Advanced Time Travel Operations

### Missione 2.1: Selective Checkout e Cherry-Pick

**Scenario**: Devi estrarre solo le fix di sicurezza dal hotfix branch senza portare altri cambiamenti.

```bash
# 1. Crea un nuovo branch per test della fix
git checkout main
git checkout -b test/security-fix-only

echo "🍒 CHERRY-PICK: Porta solo le fix di sicurezza"

# TODO: Identifica l'hash del commit di security fix
# TODO: Fai cherry-pick solo di quel commit
# TODO: Verifica che solo le fix siano presenti

# 2. Test selective file checkout
echo "📁 SELECTIVE CHECKOUT: Porta solo file specifici da altri commit"

# TODO: Torna a main
# TODO: Usa git checkout <commit> -- <file> per portare solo auth.js dall'hotfix
```

### Missione 2.2: Detached HEAD Recovery Mastery

**Scenario**: Un junior developer si è perso in detached HEAD state e ha fatto commit importanti che rischia di perdere.

```bash
# 1. Simula lo scenario detached HEAD
echo "😵 SIMULAZIONE: Junior developer perso in detached HEAD"

# Vai a un commit precedente
git checkout HEAD~3

# Crea modifiche "perse"
cat > lost-changes.txt << 'EOF'
Important changes made by junior developer
These changes should not be lost!

Features implemented:
- Critical bug fix for data validation
- Performance improvement for API
- Security enhancement for tokens
EOF

git add lost-changes.txt
git commit -m "fix: critical changes that must not be lost

- Fix data validation bug that caused crashes
- Improve API response time by 50%
- Enhance token security with rotation"

# Salva l'hash del commit "perso"
LOST_COMMIT=$(git rev-parse HEAD)
echo "💀 Commit 'perso': $LOST_COMMIT"

# Simula che il developer torna a main e "perde" il lavoro
git checkout main
echo "😱 Oh no! Il junior developer è tornato a main e ha perso le modifiche!"

echo "🚑 RECOVERY MISSION: Recupera le modifiche perse"

# TODO: Usa git reflog per trovare il commit perso
# TODO: Crea un nuovo branch dal commit perso
# TODO: Verifica che le modifiche siano recuperate
```

### Missione 2.3: Complex Branch Navigation

**Scenario**: Devi navigare tra diversi branch per fare analisi comparative del codice.

```bash
echo "🗺️ NAVIGAZIONE COMPLESSA: Analisi multi-branch"

# 1. Confronta auth.js tra tutti i branch
echo "📊 Compara l'evoluzione di auth.js tra branch"

# TODO: Esamina auth.js su main
# TODO: Esamina auth.js su feature/authentication  
# TODO: Esamina auth.js su hotfix/critical-security
# TODO: Identifica le differenze principali

# 2. Trova il branch più sicuro
echo "🔒 Determina quale branch ha la versione più sicura di auth.js"

# TODO: Analizza ogni versione
# TODO: Identifica pro e contro di ogni implementazione

# 3. Workflow di testing cross-branch
echo "🧪 Testa funzionalità su diversi branch"

# TODO: Vai su ogni branch
# TODO: Simula test delle funzionalità auth
# TODO: Documenta i risultati
```

---

## 🔬 Parte 3: Forensic Git Analysis

### Missione 3.1: Commit Archaeology

**Scenario**: Devi ricostruire la timeline completa dello sviluppo per un audit.

```bash
# 1. Analisi temporale completa
echo "⏰ TIMELINE ANALYSIS: Ricostruisci la cronologia completa"

cat > timeline-analysis.sh << 'EOF'
#!/bin/bash

echo "=== FORENSIC TIMELINE ANALYSIS ==="
echo "=================================="

echo -e "\n📅 CRONOLOGIA COMPLETA:"
git log --all --graph --pretty=format:'%C(red)%h%C(reset) - %C(yellow)%d%C(reset) %s %C(green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --date=relative

echo -e "\n\n🏷️ RELEASES E TAG:"
git tag -l --sort=-version:refname --format='%(refname:short) - %(contents:subject)'

echo -e "\n\n🌿 BRANCH ANALYSIS:"
git branch -a --format='%(refname:short) - %(objectname:short)'

echo -e "\n\n📊 CONTRIBUTOR STATS:"
git shortlog -sn --all

echo -e "\n\n🔍 FILE EVOLUTION:"
echo "File modificati più frequentemente:"
git log --pretty=format: --name-only --all | grep -v '^$' | sort | uniq -c | sort -nr | head -10

echo -e "\n\n⚠️ SECURITY CRITICAL COMMITS:"
echo "Commit che modificano auth.js:"
git log --oneline --all -- src/auth.js

echo -e "\n\n🐛 POTENTIAL ISSUES:"
echo "Commit con parole sospette:"
git log --all --grep="TODO\|FIXME\|BUG\|hack" --oneline
EOF

chmod +x timeline-analysis.sh

# TODO: Esegui lo script di analisi
# TODO: Interpreta i risultati
# TODO: Identifica pattern sospetti
```

### Missione 3.2: Advanced Blame Analysis

**Scenario**: Devi identificare chi ha introdotto specific bug e quando.

```bash
# 1. Blame analysis avanzata
echo "👤 BLAME ANALYSIS: Chi ha introdotto i bug?"

# TODO: Usa git blame su src/auth.js per vedere chi ha scritto ogni riga
# TODO: Identifica chi ha introdotto la vulnerabilità guest user
# TODO: Usa git blame -L per analizzare solo linee specifiche

# 2. Historical blame
echo "📚 HISTORICAL BLAME: Evoluzione del codice"

# TODO: Usa git log -p su src/utils/helper.js
# TODO: Identifica chi ha aggiunto processLargeData
# TODO: Vedi l'evoluzione del file nel tempo

# 3. Cross-branch blame
cat > blame-analysis.sh << 'EOF'
#!/bin/bash

echo "=== ADVANCED BLAME ANALYSIS ==="
echo "==============================="

echo -e "\n🎯 AUTH.JS BLAME ANALYSIS:"
echo "Current version (main):"
git blame src/auth.js | head -20

echo -e "\n🔍 WHO INTRODUCED SECURITY ISSUES:"
# Find the commit that added guest user
echo "Commits that modified authentication logic:"
git log --pretty=format:'%h - %an, %ar : %s' -- src/auth.js

echo -e "\n⚠️ PERFORMANCE ISSUE BLAME:"
echo "Who added the O(n³) algorithm:"
git log --pretty=format:'%h - %an, %ar : %s' -S "processLargeData" -- src/utils/helper.js

echo -e "\n📊 CODE OWNERSHIP:"
echo "Lines of code by author:"
git ls-tree -r -z --name-only HEAD | xargs -0 -n1 git blame --line-porcelain | grep "^author " | sort | uniq -c | sort -nr
EOF

chmod +x blame-analysis.sh

# TODO: Esegui l'analisi blame
# TODO: Documenta i risultati
```

### Missione 3.3: Repository Health Check

**Scenario**: Devi fare un audit completo della salute del repository.

```bash
# 1. Repository health analysis
cat > repo-health-check.sh << 'EOF'
#!/bin/bash

echo "🏥 REPOSITORY HEALTH CHECK"
echo "========================="

echo -e "\n📏 REPOSITORY SIZE:"
du -sh .git
echo "Objects count:"
git count-objects -v

echo -e "\n🔄 BRANCH STATUS:"
echo "Active branches:"
git branch -a

echo "Merged branches:"
git branch --merged main

echo "Unmerged branches:"
git branch --no-merged main

echo -e "\n🏷️ TAGS STATUS:"
echo "Total tags:"
git tag | wc -l
echo "Recent tags:"
git tag --sort=-version:refname | head -5

echo -e "\n⚠️ POTENTIAL ISSUES:"
echo "Large files:"
git rev-list --objects --all | git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | sed -n 's/^blob //p' | sort --numeric-sort --key=2 | tail -10

echo -e "\n📊 COMMIT PATTERNS:"
echo "Commits by day of week:"
git log --format="%ad" --date=format:"%u" | sort | uniq -c

echo "Commits by hour:"
git log --format="%ad" --date=format:"%H" | sort | uniq -c

echo -e "\n🔍 SECURITY ANALYSIS:"
echo "Files with potential secrets:"
git log --all -S "password" --oneline
git log --all -S "secret" --oneline
git log --all -S "token" --oneline

echo -e "\n✅ HEALTH SCORE:"
TOTAL_COMMITS=$(git rev-list --all --count)
TOTAL_AUTHORS=$(git shortlog -sn --all | wc -l)
BRANCHES=$(git branch -a | wc -l)

echo "Total commits: $TOTAL_COMMITS"
echo "Total authors: $TOTAL_AUTHORS"
echo "Total branches: $BRANCHES"

if [ $TOTAL_COMMITS -gt 10 ]; then
    echo "✅ Good commit history"
else
    echo "⚠️ Limited commit history"
fi
EOF

chmod +x repo-health-check.sh

# TODO: Esegui il health check
# TODO: Interpreta i risultati
# TODO: Identifica aree di miglioramento
```

---

## 🎯 Parte 4: Advanced Recovery Scenarios

### Missione 4.1: Disaster Recovery

**Scenario**: Qualcuno ha fatto `git reset --hard` sbagliato e sembra aver perso settimane di lavoro.

```bash
# 1. Simula il disastro
echo "💥 SIMULAZIONE DISASTRO: Reset catastrofico"

# Crea alcuni commit "importanti"
git checkout main
cat > important-work.txt << 'EOF'
CRITICAL WORK - DO NOT LOSE
============================

Week 1: Implemented new payment system
Week 2: Added fraud detection algorithms  
Week 3: Created admin dashboard
Week 4: Security enhancements and testing

This work represents 4 weeks of development!
EOF

git add important-work.txt
git commit -m "feat: 4 weeks of critical payment system work"

cat >> important-work.txt << 'EOF'

Week 5: Final optimizations and bug fixes
Ready for production deployment!
EOF

git add important-work.txt
git commit -m "feat: final payment system - ready for production"

# Salva l'hash prima del disastro
LAST_GOOD_COMMIT=$(git rev-parse HEAD)
echo "💾 Last good commit: $LAST_GOOD_COMMIT"

# DISASTRO: Reset catastrofico
git reset --hard HEAD~5
echo "💥 DISASTER! 4 weeks of work seem lost!"

echo "🚑 RECOVERY MISSION:"
echo "1. Il team è in panico"
echo "2. Devi recuperare tutto il lavoro"
echo "3. Hai solo git reflog per salvare la situazione"

# TODO: Usa git reflog per trovare i commit perduti
# TODO: Recupera i commit using git reset o git checkout
# TODO: Verifica che tutto sia stato recuperato
```

### Missione 4.2: Complex Merge Recovery

**Scenario**: Un merge è andato storto e ha corrotto il codice. Devi separare i cambiamenti buoni da quelli cattivi.

```bash
# 1. Simula merge problematico
echo "🔀 SIMULAZIONE: Merge problematico"

# Crea un branch con modifiche miste (buone e cattive)
git checkout -b problematic-feature

# Aggiunta buona
cat > src/api/good-feature.js << 'EOF'
// Good feature: Input validation
function validateInput(data) {
    if (!data || typeof data !== 'object') {
        throw new Error('Invalid input data');
    }
    
    if (!data.email || !data.email.includes('@')) {
        throw new Error('Invalid email format');
    }
    
    return true;
}

module.exports = { validateInput };
EOF

git add src/api/good-feature.js
git commit -m "feat: add robust input validation (GOOD)"

# Aggiunta problematica
cat > src/api/bad-feature.js << 'EOF'
// Bad feature: SQL injection vulnerability
function getUserData(userId) {
    const query = `SELECT * FROM users WHERE id = ${userId}`; // SQL injection!
    return database.query(query);
}

// Security issue: No authentication
function deleteAllUsers() {
    return database.query('DELETE FROM users'); // Dangerous!
}

module.exports = { getUserData, deleteAllUsers };
EOF

git add src/api/bad-feature.js
git commit -m "feat: add user management (CONTAINS VULNERABILITIES)"

# Merge problematico
git checkout main
git merge problematic-feature --no-edit

echo "🚨 PROBLEMA: Il merge ha introdotto vulnerabilità di sicurezza!"
echo "🎯 MISSION: Devi separare le modifiche buone da quelle cattive"

# TODO: Analizza il merge commit
# TODO: Identifica quali file sono problematici
# TODO: Usa git revert selettivo o refactor per rimuovere solo le parti cattive
```

### Missione 4.3: Branch Reconstruction

**Scenario**: Il repository principale è corrotto. Devi ricostruire la storia da backup parziali.

```bash
# 1. Simula corruzione repository
echo "🗂️ SIMULAZIONE: Repository corrotto, ricostruzioni da backup"

# Crea "backup" simulati (diversi punti nella storia)
mkdir -p backups
git show v1.0.0:package.json > backups/package.json.v1.0.0
git show v1.1.0:src/auth.js > backups/auth.js.v1.1.0  
git show main:README.md > backups/README.md.latest

echo "💾 Backups disponibili:"
ls -la backups/

echo "🔧 RECONSTRUCTION MISSION:"
echo "1. Hai solo backup parziali di file specifici"
echo "2. Devi ricostruire la storia logica"
echo "3. Devi identificare quale versione usare per ogni file"

# TODO: Analizza i backup disponibili
# TODO: Ricostruisci un nuovo branch con la migliore combinazione
# TODO: Documenta le decisioni prese
```

---

## 📝 Parte 5: Documentation e Reporting

### Missione 5.1: Audit Report Generation

Crea un report completo delle tue scoperte:

```bash
cat > AUDIT_REPORT.md << 'EOF'
# Git Repository Forensic Analysis Report

**Date**: $(date)
**Auditor**: Senior Developer
**Repository**: webapp-team-project

## 🔍 Executive Summary

[TODO: Riempi con le tue scoperte]

## 🐛 Security Issues Identified

### 1. Authentication Vulnerabilities
- **Issue**: Guest user with empty password
- **Introduced**: [Commit hash e data]
- **Impact**: High - Allows unauthorized access
- **Status**: Partially fixed in hotfix branch

### 2. Authorization Flaws
- **Issue**: All users receive admin role
- **Introduced**: [Commit hash e data]
- **Impact**: Critical - Privilege escalation
- **Status**: [Status corrente]

## ⚡ Performance Issues

### 1. O(n³) Algorithm
- **Function**: processLargeData
- **Impact**: Server slowdown with large datasets
- **Introduced**: [Commit hash e data]
- **Recommendation**: Implement efficient algorithm

### 2. Memory Leak
- **Function**: memoize
- **Impact**: Memory exhaustion over time
- **Root cause**: Cache never cleared
- **Recommendation**: Implement cache cleanup

## 📊 Repository Statistics

- Total commits: [Numero]
- Active branches: [Numero]
- Contributors: [Numero]
- Security commits: [Numero]

## 🎯 Recommendations

1. **Immediate Actions**:
   - [Lista azioni urgent]

2. **Short-term Improvements**:
   - [Lista miglioramenti]

3. **Long-term Strategy**:
   - [Strategia a lungo termine]

## 🔧 Recovery Procedures Tested

1. **Detached HEAD Recovery**: ✅ Successful
2. **Merge Conflict Resolution**: ✅ Successful  
3. **Cherry-pick Operations**: ✅ Successful
4. **Disaster Recovery**: ✅ Successful

## 📋 Lessons Learned

[TODO: Documenta cosa hai imparato]

EOF

echo "📄 Audit report template creato. Completa con le tue scoperte!"
```

### Missione 5.2: Team Training Documentation

Crea materiale per addestrare il team:

```bash
cat > TEAM_TRAINING.md << 'EOF'
# Git Time Travel - Team Training Guide

## 🎯 Cosa Impareremo

1. Navigazione sicura nella cronologia
2. Tecniche di debugging temporale
3. Procedure di recovery di emergenza
4. Best practices per evitare problemi

## 🛠️ Strumenti Essenziali

### Navigation Commands
```bash
git log --oneline --graph --all    # Vista generale
git checkout <commit>               # Time travel
git switch -                        # Torna al branch precedente
git reflog                          # Cronologia completa
```

### Debugging Commands
```bash
git blame <file>                    # Chi ha scritto cosa
git log -S "text" --all            # Cerca testo nella storia
git bisect start                    # Debug binario
git show <commit>                   # Dettagli commit
```

### Recovery Commands
```bash
git reflog                          # Trova commit "perduti"
git reset --hard <commit>           # Recovery drastico
git checkout <commit> -- <file>     # Recovery selettivo
git cherry-pick <commit>            # Porta modifiche specifiche
```

## ⚠️ Pericoli Comuni

1. **Detached HEAD**: Come riconoscerlo e gestirlo
2. **Reset Disasters**: Come prevenire e recuperare
3. **Merge Conflicts**: Strategie di risoluzione
4. **Data Loss**: Procedure di backup e recovery

## 🏆 Esercizi Pratici

[Lista esercizi per il team]

EOF
```

---

## 🎓 Valutazione Finale

### Checklist Competenze Acquisite

Verifica di aver completato tutti gli obiettivi:

#### 🎯 Navigation Mastery
- [ ] Navigazione fluida tra commit con checkout/switch
- [ ] Gestione sicura di detached HEAD state
- [ ] Uso avanzato di git reflog per recovery
- [ ] Cherry-pick selettivo di modifiche

#### 🔍 Forensic Analysis
- [ ] Analisi timeline completa con git log
- [ ] Identificazione autori con git blame
- [ ] Ricerca nella storia con git log -S
- [ ] Uso di git bisect per debugging

#### 🚑 Emergency Recovery
- [ ] Recovery da reset catastrofici
- [ ] Ricostruzione branch perduti
- [ ] Gestione merge problematici
- [ ] Separazione modifiche buone/cattive

#### 📊 Audit e Reporting
- [ ] Generazione report di sicurezza
- [ ] Documentazione procedure recovery
- [ ] Identificazione pattern problematici
- [ ] Creazione materiale formativo

### 🏆 Sfide Bonus

Se hai completato tutto, prova queste sfide avanzate:

#### Sfida 1: Git Bisect Automation
Crea uno script che automatizzi il git bisect per trovare regressioni di performance.

#### Sfida 2: Forensic Dashboard
Sviluppa uno script che generi un dashboard HTML con statistiche complete del repository.

#### Sfida 3: Advanced Recovery
Simula uno scenario dove il .git directory è parzialmente corrotto e devi recuperare usando solo backup di file.

---

## 📚 Risorse Aggiuntive

### Comandi Git Avanzati
- `git log --follow <file>` - Segue file rinominati
- `git log --reverse` - Cronologia al contrario
- `git shortlog -sn` - Statistiche contributori
- `git for-each-ref` - Informazioni dettagliate ref

### Strumenti Esterni
- **gitk**: Visualizzatore grafico storia
- **tig**: Navigatore testuale avanzato
- **GitKraken**: GUI professionale
- **git-extras**: Comandi aggiuntivi utili

### Best Practices
1. **Commit atomici** per navigazione più facile
2. **Messaggi commit descrittivi** per ricerche
3. **Tag regolari** per punti di riferimento
4. **Branch naming conventions** per organizzazione

---

## 🎯 Prossimi Passi

Dopo aver completato questo esercizio:

1. **Pratica regolare** con repository reali
2. **Condividi conoscenze** con il team
3. **Migliora workflow** di sviluppo
4. **Implementa procedure** di recovery
5. **Monitora sicurezza** repository continuamente

---

*🚀 Congratulazioni! Ora sei un maestro della navigazione temporale Git e sei pronto per gestire qualsiasi scenario complesso che potresti incontrare in un ambiente di sviluppo professionale.*
