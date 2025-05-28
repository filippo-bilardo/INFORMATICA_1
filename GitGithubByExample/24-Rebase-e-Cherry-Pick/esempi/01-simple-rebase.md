# Simple Rebase - Esempio Pratico

## 📖 Scenario

In questo esempio simuleremo una situazione reale: hai creato un branch feature per implementare un sistema di autenticazione, ma nel frattempo il branch `main` è stato aggiornato con altre modifiche. Dovrai fare rebase del tuo branch per incorporare gli ultimi cambiamenti prima del merge finale.

## 🎯 Obiettivi dell'Esempio

- Creare un ambiente di test con conflitti realistici
- Eseguire rebase step-by-step
- Gestire conflitti durante il rebase
- Verificare il risultato finale
- Implementare best practices per rebase sicuro

## 🚀 Setup dell'Ambiente

### 1. Creazione Repository di Test

```bash
#!/bin/bash
# setup-rebase-demo.sh

echo "🏗️ Creazione ambiente di test per Simple Rebase"

# Pulizia eventuale ambiente precedente
rm -rf rebase-demo
mkdir rebase-demo && cd rebase-demo

# Inizializzazione repository
git init
git config user.name "Demo User"
git config user.email "demo@example.com"

echo "📁 CREAZIONE STRUTTURA PROGETTO"
echo "================================"

# Struttura base del progetto
mkdir -p src/{auth,utils,components}
mkdir -p tests/{unit,integration}
mkdir -p docs

# File principali
cat > README.md << 'EOF'
# Authentication System Demo

Un semplice sistema di autenticazione per dimostrare Git rebase.

## Features
- User login/logout
- Password validation
- Session management

## Setup
npm install
npm test
EOF

cat > package.json << 'EOF'
{
  "name": "auth-system-demo",
  "version": "1.0.0",
  "description": "Demo project for Git rebase",
  "main": "src/index.js",
  "scripts": {
    "test": "echo \"Running tests...\" && exit 0",
    "start": "node src/index.js"
  },
  "dependencies": {
    "express": "^4.18.0",
    "bcryptjs": "^2.4.3"
  },
  "devDependencies": {
    "jest": "^28.0.0"
  }
}
EOF

cat > src/index.js << 'EOF'
// Main application entry point
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Basic health check
app.get('/health', (req, res) => {
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

cat > src/utils/logger.js << 'EOF'
// Simple logging utility
class Logger {
    static info(message) {
        console.log(`[INFO] ${new Date().toISOString()}: ${message}`);
    }
    
    static error(message) {
        console.error(`[ERROR] ${new Date().toISOString()}: ${message}`);
    }
    
    static warn(message) {
        console.warn(`[WARN] ${new Date().toISOString()}: ${message}`);
    }
}

module.exports = Logger;
EOF

# Commit iniziale
git add .
git commit -m "feat: initial project setup

- Add basic Express server
- Create project structure
- Add package.json with dependencies
- Set up logging utility"

echo "✅ Repository inizializzato con commit base"
```

### 2. Simulazione Sviluppo Parallelo

```bash
#!/bin/bash
# simulate-parallel-development.sh

echo "🔄 SIMULAZIONE SVILUPPO PARALLELO"
echo "================================"

# MAIN BRANCH: Altri sviluppatori aggiungono features
echo "👥 Sviluppo su main branch (altri sviluppatori)..."

# Update 1: Aggiunta middleware di sicurezza
cat > src/middleware/security.js << 'EOF'
// Security middleware
const rateLimit = require('express-rate-limit');

const limiter = rateLimit({
    windowMs: 15 * 60 * 1000, // 15 minuti
    max: 100, // limita ogni IP a 100 richieste per windowMs
    message: 'Too many requests from this IP'
});

const securityHeaders = (req, res, next) => {
    res.setHeader('X-Content-Type-Options', 'nosniff');
    res.setHeader('X-Frame-Options', 'DENY');
    res.setHeader('X-XSS-Protection', '1; mode=block');
    next();
};

module.exports = { limiter, securityHeaders };
EOF

# Update package.json per nuova dipendenza
cat > package.json << 'EOF'
{
  "name": "auth-system-demo",
  "version": "1.0.0",
  "description": "Demo project for Git rebase",
  "main": "src/index.js",
  "scripts": {
    "test": "echo \"Running tests...\" && exit 0",
    "start": "node src/index.js"
  },
  "dependencies": {
    "express": "^4.18.0",
    "express-rate-limit": "^6.6.0",
    "bcryptjs": "^2.4.3"
  },
  "devDependencies": {
    "jest": "^28.0.0"
  }
}
EOF

# Update main server per usare middleware
cat > src/index.js << 'EOF'
// Main application entry point
const express = require('express');
const { limiter, securityHeaders } = require('./middleware/security');
const Logger = require('./utils/logger');

const app = express();
const PORT = process.env.PORT || 3000;

// Security middleware
app.use(securityHeaders);
app.use(limiter);
app.use(express.json());

// Basic health check
app.get('/health', (req, res) => {
    Logger.info('Health check requested');
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

app.listen(PORT, () => {
    Logger.info(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

mkdir -p src/middleware
git add .
git commit -m "feat: add security middleware

- Implement rate limiting
- Add security headers
- Update server to use middleware
- Add express-rate-limit dependency"

echo "✅ Main branch: aggiunto security middleware"

# Update 2: Miglioramento logging
cat > src/utils/logger.js << 'EOF'
// Enhanced logging utility
const fs = require('fs');
const path = require('path');

class Logger {
    static logFile = path.join(__dirname, '../../logs/app.log');
    
    static ensureLogDir() {
        const logDir = path.dirname(this.logFile);
        if (!fs.existsSync(logDir)) {
            fs.mkdirSync(logDir, { recursive: true });
        }
    }
    
    static writeToFile(level, message) {
        this.ensureLogDir();
        const timestamp = new Date().toISOString();
        const logEntry = `[${timestamp}] [${level}] ${message}\n`;
        fs.appendFileSync(this.logFile, logEntry);
    }
    
    static info(message) {
        console.log(`[INFO] ${new Date().toISOString()}: ${message}`);
        this.writeToFile('INFO', message);
    }
    
    static error(message) {
        console.error(`[ERROR] ${new Date().toISOString()}: ${message}`);
        this.writeToFile('ERROR', message);
    }
    
    static warn(message) {
        console.warn(`[WARN] ${new Date().toISOString()}: ${message}`);
        this.writeToFile('WARN', message);
    }
}

module.exports = Logger;
EOF

# Aggiunta .gitignore
cat > .gitignore << 'EOF'
# Logs
logs/
*.log

# Dependencies
node_modules/

# Environment
.env
.env.local

# OS
.DS_Store
Thumbs.db
EOF

git add .
git commit -m "feat: enhance logging system

- Add file logging capability
- Create logs directory automatically
- Add comprehensive .gitignore
- Improve error tracking"

echo "✅ Main branch: migliorato sistema di logging"

# Update 3: Aggiunta configurazione
cat > src/config/database.js << 'EOF'
// Database configuration
module.exports = {
    development: {
        host: process.env.DB_HOST || 'localhost',
        port: process.env.DB_PORT || 5432,
        database: process.env.DB_NAME || 'auth_demo',
        username: process.env.DB_USER || 'demo',
        password: process.env.DB_PASSWORD || 'password'
    },
    test: {
        host: 'localhost',
        port: 5432,
        database: 'auth_demo_test',
        username: 'test',
        password: 'test'
    },
    production: {
        host: process.env.DB_HOST,
        port: process.env.DB_PORT,
        database: process.env.DB_NAME,
        username: process.env.DB_USER,
        password: process.env.DB_PASSWORD
    }
};
EOF

mkdir -p src/config
git add .
git commit -m "feat: add database configuration

- Create environment-specific DB config
- Support for development, test, production
- Use environment variables for production"

echo "✅ Main branch: aggiunta configurazione database"

echo "📊 Stato attuale main branch:"
git log --oneline
```

### 3. Creazione Feature Branch

```bash
#!/bin/bash
# create-feature-branch.sh

echo "🌿 CREAZIONE FEATURE BRANCH"
echo "=========================="

# Torna al commit iniziale per simulare sviluppo parallelo
git checkout -b feature/user-authentication HEAD~3

echo "🔄 Ora siamo su feature branch, 3 commit indietro rispetto a main"
git log --oneline

echo "👨‍💻 SVILUPPO FEATURE AUTHENTICATION"
echo "=================================="

# Step 1: Creazione modello User
cat > src/auth/user.js << 'EOF'
// User model and management
const bcrypt = require('bcryptjs');
const Logger = require('../utils/logger');

class User {
    constructor(username, email, passwordHash) {
        this.username = username;
        this.email = email;
        this.passwordHash = passwordHash;
        this.createdAt = new Date();
        this.isActive = true;
    }
    
    static async create(username, email, password) {
        try {
            Logger.info(`Creating new user: ${username}`);
            const saltRounds = 10;
            const passwordHash = await bcrypt.hash(password, saltRounds);
            return new User(username, email, passwordHash);
        } catch (error) {
            Logger.error(`Error creating user: ${error.message}`);
            throw error;
        }
    }
    
    async validatePassword(password) {
        try {
            return await bcrypt.compare(password, this.passwordHash);
        } catch (error) {
            Logger.error(`Error validating password: ${error.message}`);
            return false;
        }
    }
    
    toJSON() {
        return {
            username: this.username,
            email: this.email,
            createdAt: this.createdAt,
            isActive: this.isActive
        };
    }
}

module.exports = User;
EOF

git add .
git commit -m "feat: implement User model

- Add User class with password hashing
- Implement password validation with bcrypt
- Add user creation and JSON serialization
- Include logging for user operations"

echo "✅ Feature: User model implementato"

# Step 2: Servizio di autenticazione
cat > src/auth/authService.js << 'EOF'
// Authentication service
const User = require('./user');
const Logger = require('../utils/logger');

class AuthService {
    constructor() {
        this.users = new Map(); // In memoria per demo
        this.sessions = new Map();
    }
    
    async register(username, email, password) {
        Logger.info(`Registration attempt for user: ${username}`);
        
        if (this.users.has(username)) {
            throw new Error('Username already exists');
        }
        
        if (password.length < 8) {
            throw new Error('Password must be at least 8 characters');
        }
        
        const user = await User.create(username, email, password);
        this.users.set(username, user);
        
        Logger.info(`User registered successfully: ${username}`);
        return user.toJSON();
    }
    
    async login(username, password) {
        Logger.info(`Login attempt for user: ${username}`);
        
        const user = this.users.get(username);
        if (!user || !user.isActive) {
            Logger.warn(`Login failed - user not found: ${username}`);
            throw new Error('Invalid credentials');
        }
        
        const isValid = await user.validatePassword(password);
        if (!isValid) {
            Logger.warn(`Login failed - invalid password: ${username}`);
            throw new Error('Invalid credentials');
        }
        
        // Genera session token (semplificato)
        const sessionToken = this.generateToken();
        this.sessions.set(sessionToken, {
            username: user.username,
            createdAt: new Date()
        });
        
        Logger.info(`User logged in successfully: ${username}`);
        return { token: sessionToken, user: user.toJSON() };
    }
    
    logout(token) {
        if (this.sessions.has(token)) {
            const session = this.sessions.get(token);
            this.sessions.delete(token);
            Logger.info(`User logged out: ${session.username}`);
            return true;
        }
        return false;
    }
    
    validateSession(token) {
        return this.sessions.has(token);
    }
    
    generateToken() {
        return Math.random().toString(36).substring(2, 15) + 
               Math.random().toString(36).substring(2, 15);
    }
}

module.exports = AuthService;
EOF

git add .
git commit -m "feat: implement authentication service

- Add user registration with validation
- Implement login/logout functionality
- Add session management with tokens
- Include comprehensive logging"

echo "✅ Feature: Authentication service implementato"

# Step 3: Route API
cat > src/auth/routes.js << 'EOF'
// Authentication routes
const express = require('express');
const AuthService = require('./authService');
const Logger = require('../utils/logger');

const router = express.Router();
const authService = new AuthService();

// Middleware per validazione session
const requireAuth = (req, res, next) => {
    const token = req.headers.authorization?.replace('Bearer ', '');
    
    if (!token || !authService.validateSession(token)) {
        return res.status(401).json({ error: 'Unauthorized' });
    }
    
    req.token = token;
    next();
};

// POST /auth/register
router.post('/register', async (req, res) => {
    try {
        const { username, email, password } = req.body;
        
        if (!username || !email || !password) {
            return res.status(400).json({ 
                error: 'Username, email and password are required' 
            });
        }
        
        const user = await authService.register(username, email, password);
        res.status(201).json({ user });
        
    } catch (error) {
        Logger.error(`Registration error: ${error.message}`);
        res.status(400).json({ error: error.message });
    }
});

// POST /auth/login
router.post('/login', async (req, res) => {
    try {
        const { username, password } = req.body;
        
        if (!username || !password) {
            return res.status(400).json({ 
                error: 'Username and password are required' 
            });
        }
        
        const result = await authService.login(username, password);
        res.json(result);
        
    } catch (error) {
        Logger.error(`Login error: ${error.message}`);
        res.status(401).json({ error: error.message });
    }
});

// POST /auth/logout
router.post('/logout', requireAuth, (req, res) => {
    const success = authService.logout(req.token);
    if (success) {
        res.json({ message: 'Logged out successfully' });
    } else {
        res.status(400).json({ error: 'Invalid session' });
    }
});

// GET /auth/profile
router.get('/profile', requireAuth, (req, res) => {
    res.json({ message: 'Protected route accessed', token: req.token });
});

module.exports = { router, authService };
EOF

# Update server principale
cat > src/index.js << 'EOF'
// Main application entry point
const express = require('express');
const { router: authRouter } = require('./auth/routes');
const Logger = require('./utils/logger');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Routes
app.use('/auth', authRouter);

// Basic health check
app.get('/health', (req, res) => {
    Logger.info('Health check requested');
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

// 404 handler
app.use('*', (req, res) => {
    res.status(404).json({ error: 'Route not found' });
});

app.listen(PORT, () => {
    Logger.info(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

git add .
git commit -m "feat: add authentication API routes

- Implement /auth/register endpoint
- Add /auth/login with session management
- Create /auth/logout functionality
- Add protected /auth/profile route
- Include input validation and error handling"

echo "✅ Feature: API routes implementate"

# Step 4: Test semplici
cat > tests/auth.test.js << 'EOF'
// Basic authentication tests
const AuthService = require('../src/auth/authService');

describe('AuthService', () => {
    let authService;
    
    beforeEach(() => {
        authService = new AuthService();
    });
    
    test('should register a new user', async () => {
        const user = await authService.register('testuser', 'test@example.com', 'password123');
        expect(user.username).toBe('testuser');
        expect(user.email).toBe('test@example.com');
    });
    
    test('should login with valid credentials', async () => {
        await authService.register('testuser', 'test@example.com', 'password123');
        const result = await authService.login('testuser', 'password123');
        
        expect(result.token).toBeDefined();
        expect(result.user.username).toBe('testuser');
    });
    
    test('should fail login with invalid password', async () => {
        await authService.register('testuser', 'test@example.com', 'password123');
        
        try {
            await authService.login('testuser', 'wrongpassword');
        } catch (error) {
            expect(error.message).toBe('Invalid credentials');
        }
    });
});
EOF

git add .
git commit -m "test: add basic authentication tests

- Add unit tests for AuthService
- Test user registration functionality
- Test login with valid/invalid credentials
- Set up test structure for future expansion"

echo "✅ Feature: Test aggiunti"

echo "📊 Stato feature branch:"
git log --oneline

echo "🎯 PRONTO PER REBASE!"
echo "Feature branch ha 4 commit nuovi"
echo "Main branch ha 3 commit nuovi"
echo "È ora di fare rebase per sincronizzare i branch"
```

## 🔄 Esecuzione del Rebase

### 4. Pre-Rebase Analysis

```bash
#!/bin/bash
# pre-rebase-analysis.sh

echo "🔍 ANALISI PRE-REBASE"
echo "===================="

echo "📊 Stato corrente dei branch:"
echo ""
echo "🌿 Feature branch (corrente):"
git log --oneline feature/user-authentication

echo ""
echo "🔝 Main branch:"
git log --oneline main

echo ""
echo "📈 Divergenza tra i branch:"
echo "Feature ha questi commit nuovi:"
git log --oneline main..feature/user-authentication

echo ""
echo "Main ha questi commit nuovi:"
git log --oneline feature/user-authentication..main

echo ""
echo "📁 File modificati in feature:"
git diff --name-only main...feature/user-authentication

echo ""
echo "📁 File modificati in main:"
git diff --name-only feature/user-authentication...main

echo ""
echo "⚠️ ANALISI CONFLITTI POTENZIALI:"
echo "File modificati in entrambi i branch:"
comm -12 <(git diff --name-only main...feature/user-authentication | sort) \
         <(git diff --name-only feature/user-authentication...main | sort)

echo ""
echo "🎯 STRATEGIA REBASE:"
echo "1. Backup del branch corrente"
echo "2. Rebase interattivo per pulire commit"
echo "3. Rebase su main"
echo "4. Risoluzione conflitti"
echo "5. Verifica funzionalità"
```

### 5. Backup e Preparazione

```bash
#!/bin/bash
# backup-and-prepare.sh

echo "💾 BACKUP E PREPARAZIONE"
echo "======================="

# Backup del branch feature
BACKUP_BRANCH="backup-feature-auth-$(date +%Y%m%d-%H%M%S)"
git branch "$BACKUP_BRANCH"
echo "✅ Backup creato: $BACKUP_BRANCH"

# Verifica working directory pulita
if ! git diff-index --quiet HEAD --; then
    echo "⚠️ Working directory non pulita"
    echo "Stashing modifiche non committate..."
    git stash push -m "Pre-rebase stash $(date)"
fi

echo "🔍 Verifica stato pre-rebase:"
echo "Current branch: $(git branch --show-current)"
echo "Working directory clean: $(git diff-index --quiet HEAD -- && echo "✅" || echo "❌")"
echo "Backup disponibile: $BACKUP_BRANCH"

echo ""
echo "📋 Checklist pre-rebase:"
echo "☐ Branch di backup creato"
echo "☐ Working directory pulita"
echo "☐ Commit tutti salvati"
echo "☐ Team notificato (se branch condiviso)"

echo ""
echo "🚀 Pronto per rebase!"
echo "Comando: git rebase main"
```

### 6. Esecuzione Rebase Step-by-Step

```bash
#!/bin/bash
# execute-rebase.sh

echo "🔄 ESECUZIONE REBASE STEP-BY-STEP"
echo "================================"

# Assicurati di essere sul branch feature
git checkout feature/user-authentication

echo "1️⃣ Aggiornamento main branch..."
git checkout main
git pull origin main 2>/dev/null || echo "Note: pull failed (normale in demo locale)"
git checkout feature/user-authentication

echo ""
echo "2️⃣ Avvio rebase su main..."
echo "Comando: git rebase main"

# Simula l'avvio del rebase
if git rebase main; then
    echo "✅ Rebase completato senza conflitti!"
else
    echo "⚠️ Conflitti rilevati durante rebase"
    echo ""
    echo "🔍 File in conflitto:"
    git status --porcelain | grep "^UU"
    
    echo ""
    echo "📝 GUIDA RISOLUZIONE CONFLITTI:"
    echo "1. Modifica i file in conflitto:"
    git diff --name-only --diff-filter=U
    
    echo ""
    echo "2. Per ogni file risolto:"
    echo "   git add <file>"
    
    echo ""
    echo "3. Continua il rebase:"
    echo "   git rebase --continue"
    
    echo ""
    echo "4. Oppure annulla tutto:"
    echo "   git rebase --abort"
fi
```

### 7. Risoluzione Conflitti (Scenario Realistico)

Poiché in questo esempio avremo conflitti nel file `src/index.js`, creiamo uno script per simulare e risolvere il conflitto:

```bash
#!/bin/bash
# resolve-conflicts.sh

echo "🛠️ RISOLUZIONE CONFLITTI"
echo "======================="

# Questo script simula la risoluzione di conflitti comuni durante rebase

echo "📄 Conflitto tipico in src/index.js:"
echo "Il file è stato modificato sia su main (security middleware) che su feature (auth routes)"

echo ""
echo "🔍 Analisi del conflitto:"
echo "Main branch aggiunge: security middleware"
echo "Feature branch aggiunge: auth routes"

echo ""
echo "✅ Strategia di risoluzione:"
echo "Combinare entrambe le modifiche mantenendo:"
echo "- Security middleware da main"
echo "- Auth routes da feature"
echo "- Ordine logico delle import e middleware"

# Versione risolta di src/index.js
cat > src/index.js << 'EOF'
// Main application entry point
const express = require('express');
const { limiter, securityHeaders } = require('./middleware/security');
const { router: authRouter } = require('./auth/routes');
const Logger = require('./utils/logger');

const app = express();
const PORT = process.env.PORT || 3000;

// Security middleware (from main)
app.use(securityHeaders);
app.use(limiter);
app.use(express.json());

// Routes (from feature)
app.use('/auth', authRouter);

// Basic health check
app.get('/health', (req, res) => {
    Logger.info('Health check requested');
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

// 404 handler (from feature)
app.use('*', (req, res) => {
    res.status(404).json({ error: 'Route not found' });
});

app.listen(PORT, () => {
    Logger.info(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

echo "✅ Conflitto risolto in src/index.js"
echo "Combinati security middleware e auth routes"

# Aggiungi il file risolto
git add src/index.js

echo ""
echo "🔄 Continuazione rebase..."
git rebase --continue

if [ $? -eq 0 ]; then
    echo "✅ Rebase completato con successo!"
else
    echo "⚠️ Altri conflitti rilevati..."
    echo "Ripeti il processo per ogni conflitto"
fi
```

### 8. Verifica Post-Rebase

```bash
#!/bin/bash
# post-rebase-verification.sh

echo "🔍 VERIFICA POST-REBASE"
echo "======================"

echo "1️⃣ Analisi cronologia risultante..."
echo ""
echo "📊 Cronologia completa:"
git log --oneline --graph -10

echo ""
echo "📈 Commit del feature branch (ora rebase su main):"
git log --oneline main..HEAD

echo ""
echo "2️⃣ Verifica integrità repository..."
git fsck --full --quiet && echo "✅ Repository integro" || echo "❌ Problemi di integrità"

echo ""
echo "3️⃣ Verifica che non ci siano commit duplicati..."
duplicate_messages=$(git log --pretty=format:"%s" | sort | uniq -d)
if [ -n "$duplicate_messages" ]; then
    echo "⚠️ Commit duplicati trovati:"
    echo "$duplicate_messages"
else
    echo "✅ Nessun commit duplicato"
fi

echo ""
echo "4️⃣ Test funzionalità..."
if [ -f "package.json" ]; then
    echo "🧪 Esecuzione test..."
    npm test 2>/dev/null && echo "✅ Test passati" || echo "⚠️ Test falliti o npm non disponibile"
fi

echo ""
echo "5️⃣ Verifica applicazione..."
echo "Avvio server di test..."
timeout 5s node src/index.js &
SERVER_PID=$!
sleep 2

# Test health endpoint
if curl -s http://localhost:3000/health > /dev/null 2>&1; then
    echo "✅ Server funzionante"
else
    echo "⚠️ Server non risponde (normale se Node.js non disponibile)"
fi

# Cleanup
kill $SERVER_PID 2>/dev/null || true

echo ""
echo "📊 RISULTATO FINALE:"
echo "✅ Rebase completato con successo"
echo "✅ Feature branch aggiornato con le ultime modifiche di main"
echo "✅ Conflitti risolti correttamente"
echo "✅ Funzionalità preservate"

echo ""
echo "🎯 PROSSIMI PASSI:"
echo "1. Test estensivi dell'applicazione"
echo "2. Code review del branch rebasato"
echo "3. Merge in main se tutto ok"
echo "4. Cleanup dei branch di backup"

echo ""
echo "💡 Comando per merge finale:"
echo "git checkout main && git merge --no-ff feature/user-authentication"
```

## 📊 Analisi dei Risultati

### 9. Confronto Prima/Dopo

```bash
#!/bin/bash
# before-after-comparison.sh

echo "📊 CONFRONTO PRIMA/DOPO REBASE"
echo "============================="

BACKUP_BRANCH=$(git branch | grep backup-feature-auth | head -1 | xargs)

if [ -n "$BACKUP_BRANCH" ]; then
    echo "📋 CRONOLOGIA PRIMA (backup):"
    git log --oneline "$BACKUP_BRANCH" -10
    
    echo ""
    echo "📋 CRONOLOGIA DOPO (rebase):"
    git log --oneline HEAD -10
    
    echo ""
    echo "🔍 DIFFERENZE:"
    echo "Hash commit cambiati (normale dopo rebase):"
    
    # Confronta i messaggi di commit
    echo "Messaggi identici ma hash diversi:"
    git log --pretty=format:"%s" "$BACKUP_BRANCH" > /tmp/backup_messages
    git log --pretty=format:"%s" HEAD > /tmp/current_messages
    
    if diff /tmp/backup_messages /tmp/current_messages > /dev/null; then
        echo "✅ Messaggi di commit identici"
    else
        echo "⚠️ Differenze nei messaggi:"
        diff /tmp/backup_messages /tmp/current_messages
    fi
    
    echo ""
    echo "📁 DIFFERENZE NEI FILE:"
    git diff --stat "$BACKUP_BRANCH" HEAD
    
    if [ $? -eq 0 ]; then
        echo "✅ Contenuto dei file identico"
    else
        echo "⚠️ Differenze nel contenuto (normale se ci sono state modifiche durante risoluzione conflitti)"
    fi
    
    # Cleanup temp files
    rm -f /tmp/backup_messages /tmp/current_messages
else
    echo "❌ Branch di backup non trovato"
fi

echo ""
echo "🎯 BENEFICI DEL REBASE:"
echo "✅ Cronologia lineare e pulita"
echo "✅ Feature branch aggiornato con main"
echo "✅ Conflitti risolti una volta per tutte"
echo "✅ Pronto per merge finale"
```

## 🎓 Best Practices Dimostrate

### 10. Checklist e Lessons Learned

```bash
echo "📚 BEST PRACTICES DIMOSTRATE"
echo "============================"

echo "✅ PRE-REBASE:"
echo "  - Backup del branch (backup-feature-auth-*)"
echo "  - Working directory pulita"
echo "  - Analisi conflitti potenziali"
echo "  - Team notification (se necessario)"

echo ""
echo "✅ DURANTE REBASE:"
echo "  - Risoluzione conflitti metodica"
echo "  - Mantenimento logica di entrambi i branch"
echo "  - Commit atomici preservati"
echo "  - Test dopo ogni risoluzione"

echo ""
echo "✅ POST-REBASE:"
echo "  - Verifica integrità repository"
echo "  - Test funzionalità complete"
echo "  - Confronto con backup"
echo "  - Preparazione per merge finale"

echo ""
echo "❌ ERRORI DA EVITARE:"
echo "  - Rebase su branch condivisi"
echo "  - Risoluzione frettolosa conflitti"
echo "  - Mancanza di backup"
echo "  - Test insufficienti"

echo ""
echo "💡 QUANDO USARE REBASE:"
echo "  ✅ Branch feature personali"
echo "  ✅ Aggiornamento con main"
echo "  ✅ Pulizia cronologia"
echo "  ❌ Branch pubblici/condivisi"
echo "  ❌ Cronologia già pushata"
```

## 🚀 Script di Automazione Completo

Per concludere l'esempio, creiamo uno script che automatizza tutto il workflow:

```bash
#!/bin/bash
# complete-rebase-workflow.sh

echo "🚀 COMPLETE REBASE WORKFLOW AUTOMATION"
echo "======================================"

# Configurazione
FEATURE_BRANCH="feature/user-authentication"
MAIN_BRANCH="main"
BACKUP_PREFIX="backup-rebase"

# Funzioni utility
create_backup() {
    local backup_name="$BACKUP_PREFIX-$(date +%Y%m%d-%H%M%S)"
    git branch "$backup_name"
    echo "💾 Backup creato: $backup_name"
    echo "$backup_name"
}

cleanup_working_dir() {
    if ! git diff-index --quiet HEAD --; then
        git stash push -m "Auto-stash before rebase $(date)"
        echo "📦 Modifiche stash salvate"
    fi
}

pre_rebase_analysis() {
    echo "🔍 Analisi pre-rebase..."
    local conflicts=$(comm -12 \
        <(git diff --name-only "$MAIN_BRANCH"..."$FEATURE_BRANCH" | sort) \
        <(git diff --name-only "$FEATURE_BRANCH"..."$MAIN_BRANCH" | sort))
    
    if [ -n "$conflicts" ]; then
        echo "⚠️ Conflitti potenziali in:"
        echo "$conflicts"
        return 1
    else
        echo "✅ Nessun conflitto previsto"
        return 0
    fi
}

execute_rebase() {
    echo "🔄 Esecuzione rebase..."
    if git rebase "$MAIN_BRANCH"; then
        echo "✅ Rebase completato senza conflitti"
        return 0
    else
        echo "⚠️ Conflitti durante rebase"
        echo "🛠️ Risolvi manualmente e usa: git rebase --continue"
        return 1
    fi
}

post_rebase_verification() {
    echo "🔍 Verifica post-rebase..."
    
    # Integrità repository
    if git fsck --full --quiet; then
        echo "✅ Repository integro"
    else
        echo "❌ Problemi di integrità repository"
        return 1
    fi
    
    # Test se disponibili
    if [ -f "package.json" ] && command -v npm >/dev/null; then
        if npm test >/dev/null 2>&1; then
            echo "✅ Test passati"
        else
            echo "⚠️ Test falliti"
            return 1
        fi
    fi
    
    return 0
}

# Main workflow
main() {
    echo "Inizio workflow rebase per $FEATURE_BRANCH"
    
    # Prerequisiti
    if [ "$(git branch --show-current)" != "$FEATURE_BRANCH" ]; then
        git checkout "$FEATURE_BRANCH" || {
            echo "❌ Impossibile passare a $FEATURE_BRANCH"
            exit 1
        }
    fi
    
    # 1. Backup
    BACKUP_BRANCH=$(create_backup)
    
    # 2. Pulizia
    cleanup_working_dir
    
    # 3. Analisi
    if ! pre_rebase_analysis; then
        echo "⚠️ Conflitti previsti - procedere manualmente"
        exit 1
    fi
    
    # 4. Esecuzione
    if execute_rebase; then
        # 5. Verifica
        if post_rebase_verification; then
            echo ""
            echo "🎉 REBASE COMPLETATO CON SUCCESSO!"
            echo "📊 Stato finale:"
            git log --oneline --graph -5
            echo ""
            echo "🎯 Prossimi passi:"
            echo "1. Code review"
            echo "2. git checkout $MAIN_BRANCH && git merge --no-ff $FEATURE_BRANCH"
            echo "3. git branch -D $BACKUP_BRANCH  # quando sicuro"
        else
            echo "❌ Verifica fallita"
            exit 1
        fi
    else
        echo "❌ Rebase fallito o richiede intervento manuale"
        exit 1
    fi
}

# Esecuzione
main "$@"
```

---

## 🔄 Navigazione

**Precedente**: [04 - Rebase vs Merge](../guide/04-rebase-vs-merge.md)  
**Successivo**: [02 - Interactive Cleanup](./02-interactive-cleanup.md)  
**Indice**: [README del modulo](../README.md)

## 📝 Takeaways

Questo esempio ha dimostrato:

1. **Setup realistico** con conflitti autentici
2. **Workflow step-by-step** per rebase sicuro
3. **Risoluzione conflitti** metodica
4. **Verifica completa** post-rebase
5. **Automazione** del processo
6. **Best practices** consolidate

Il rebase è uno strumento potente che richiede pratica e attenzione, ma quando utilizzato correttamente mantiene una cronologia Git pulita e professionale.
