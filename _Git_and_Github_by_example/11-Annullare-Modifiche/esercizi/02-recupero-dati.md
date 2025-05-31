# Esercizio: Recupero Dati Complessi

## 📚 Obiettivo dell'Esercizio

Sviluppare competenze avanzate nel recupero di dati Git attraverso scenari complessi che richiedono l'uso combinato di multiple tecniche di recovery, analisi forense, e ricostruzione di repository.

## 🎯 Competenze Sviluppate

- Analisi forense di repository Git
- Recovery da oggetti unreachable
- Ricostruzione di branch complessi
- Gestione di corruzioni parziali
- Tecniche di recovery multi-sorgente
- Automazione di procedure di recovery

## ⚙️ Setup Avanzato

### Fase 1: Creazione Repository Complesso

```bash
# Creare ambiente di test avanzato
mkdir git-advanced-recovery
cd git-advanced-recovery
git init

# Configurazione
git config user.name "Advanced User"
git config user.email "advanced@example.com"

# Creare struttura complessa del progetto
mkdir -p src/{components,utils,services} tests/{unit,integration} docs/{api,guides}

# File del progetto principale
cat > src/main.js << 'EOF'
import { UserService } from './services/user.js';
import { ValidationUtils } from './utils/validation.js';

class Application {
    constructor() {
        this.userService = new UserService();
        this.validator = new ValidationUtils();
    }
    
    async start() {
        console.log('Application starting...');
        await this.userService.initialize();
    }
}

export default Application;
EOF

cat > src/services/user.js << 'EOF'
export class UserService {
    constructor() {
        this.users = new Map();
    }
    
    async initialize() {
        // Load initial data
        console.log('UserService initialized');
    }
    
    async getUser(id) {
        return this.users.get(id);
    }
}
EOF

cat > src/utils/validation.js << 'EOF'
export class ValidationUtils {
    static isValidEmail(email) {
        const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return regex.test(email);
    }
    
    static isValidPassword(password) {
        return password && password.length >= 8;
    }
}
EOF

# Test files
cat > tests/unit/validation.test.js << 'EOF'
import { ValidationUtils } from '../../src/utils/validation.js';

describe('ValidationUtils', () => {
    test('should validate email correctly', () => {
        expect(ValidationUtils.isValidEmail('test@example.com')).toBe(true);
        expect(ValidationUtils.isValidEmail('invalid-email')).toBe(false);
    });
});
EOF

# Documentation
cat > docs/api/README.md << 'EOF'
# API Documentation

## UserService

### Methods
- `initialize()`: Initialize the service
- `getUser(id)`: Get user by ID
EOF

cat > README.md << 'EOF'
# Advanced Recovery Test Project

This project is designed to test advanced Git recovery scenarios.

## Features
- User management system
- Validation utilities
- Comprehensive testing
- Full documentation
EOF

# Package.json
cat > package.json << 'EOF'
{
  "name": "advanced-recovery-test",
  "version": "1.0.0",
  "type": "module",
  "scripts": {
    "test": "jest",
    "start": "node src/main.js"
  }
}
EOF

# Initial commit
git add .
git commit -m "Initial project structure with user management system"

echo "✅ Struttura complessa creata!"
```

### Fase 2: Creazione Storia Complessa

```bash
# Branch feature/authentication
git checkout -b feature/authentication

# Primo commit del feature
cat > src/services/auth.js << 'EOF'
export class AuthService {
    constructor() {
        this.sessions = new Map();
    }
    
    async login(email, password) {
        // Basic authentication logic
        if (!email || !password) {
            throw new Error('Email and password required');
        }
        
        const sessionId = this.generateSessionId();
        this.sessions.set(sessionId, { email, timestamp: Date.now() });
        return sessionId;
    }
    
    generateSessionId() {
        return Math.random().toString(36).substr(2, 9);
    }
}
EOF

git add .
git commit -m "Add basic authentication service"

# Secondo commit - aggiungere test
cat > tests/unit/auth.test.js << 'EOF'
import { AuthService } from '../../src/services/auth.js';

describe('AuthService', () => {
    let authService;
    
    beforeEach(() => {
        authService = new AuthService();
    });
    
    test('should login with valid credentials', async () => {
        const sessionId = await authService.login('test@example.com', 'password123');
        expect(sessionId).toBeDefined();
        expect(typeof sessionId).toBe('string');
    });
    
    test('should throw error for invalid credentials', async () => {
        await expect(authService.login('', '')).rejects.toThrow();
    });
});
EOF

git add .
git commit -m "Add comprehensive authentication tests"

# Terzo commit - integrare con main app
cat > src/main.js << 'EOF'
import { UserService } from './services/user.js';
import { AuthService } from './services/auth.js';
import { ValidationUtils } from './utils/validation.js';

class Application {
    constructor() {
        this.userService = new UserService();
        this.authService = new AuthService();
        this.validator = new ValidationUtils();
    }
    
    async start() {
        console.log('Application starting with authentication...');
        await this.userService.initialize();
        console.log('Authentication service ready');
    }
    
    async authenticate(email, password) {
        if (!this.validator.isValidEmail(email)) {
            throw new Error('Invalid email format');
        }
        
        return await this.authService.login(email, password);
    }
}

export default Application;
EOF

git add .
git commit -m "Integrate authentication service with main application"

# Branch feature/database
git checkout main
git checkout -b feature/database

cat > src/services/database.js << 'EOF'
export class DatabaseService {
    constructor(connectionString) {
        this.connectionString = connectionString;
        this.connected = false;
    }
    
    async connect() {
        console.log('Connecting to database...');
        // Simulate connection delay
        await new Promise(resolve => setTimeout(resolve, 100));
        this.connected = true;
        console.log('Database connected');
    }
    
    async query(sql, params = []) {
        if (!this.connected) {
            throw new Error('Database not connected');
        }
        
        console.log(`Executing query: ${sql}`);
        return { rows: [], count: 0 };
    }
    
    async disconnect() {
        this.connected = false;
        console.log('Database disconnected');
    }
}
EOF

git add .
git commit -m "Add database service for persistent storage"

# Update user service to use database
cat > src/services/user.js << 'EOF'
import { DatabaseService } from './database.js';

export class UserService {
    constructor() {
        this.users = new Map();
        this.db = new DatabaseService('sqlite://users.db');
    }
    
    async initialize() {
        await this.db.connect();
        console.log('UserService initialized with database');
    }
    
    async getUser(id) {
        const result = await this.db.query('SELECT * FROM users WHERE id = ?', [id]);
        return result.rows[0] || null;
    }
    
    async createUser(userData) {
        const query = 'INSERT INTO users (email, name) VALUES (?, ?)';
        return await this.db.query(query, [userData.email, userData.name]);
    }
}
EOF

git add .
git commit -m "Integrate database service with user management"

# Branch feature/api
git checkout main  
git checkout -b feature/api

mkdir -p src/api
cat > src/api/routes.js << 'EOF'
export class ApiRoutes {
    constructor(app, userService, authService) {
        this.app = app;
        this.userService = userService;
        this.authService = authService;
        this.setupRoutes();
    }
    
    setupRoutes() {
        // User routes
        this.app.get('/api/users/:id', this.getUser.bind(this));
        this.app.post('/api/users', this.createUser.bind(this));
        
        // Auth routes
        this.app.post('/api/auth/login', this.login.bind(this));
        this.app.post('/api/auth/logout', this.logout.bind(this));
    }
    
    async getUser(req, res) {
        try {
            const user = await this.userService.getUser(req.params.id);
            res.json(user);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }
    
    async createUser(req, res) {
        try {
            const result = await this.userService.createUser(req.body);
            res.status(201).json(result);
        } catch (error) {
            res.status(400).json({ error: error.message });
        }
    }
    
    async login(req, res) {
        try {
            const { email, password } = req.body;
            const sessionId = await this.authService.login(email, password);
            res.json({ sessionId });
        } catch (error) {
            res.status(401).json({ error: error.message });
        }
    }
    
    async logout(req, res) {
        // Logout logic
        res.json({ message: 'Logged out successfully' });
    }
}
EOF

git add .
git commit -m "Add RESTful API routes for user and auth management"

# Integration tests
cat > tests/integration/api.test.js << 'EOF'
import { ApiRoutes } from '../../src/api/routes.js';
import { UserService } from '../../src/services/user.js';
import { AuthService } from '../../src/services/auth.js';

describe('API Integration Tests', () => {
    let mockApp, userService, authService, apiRoutes;
    
    beforeEach(() => {
        mockApp = { get: jest.fn(), post: jest.fn() };
        userService = new UserService();
        authService = new AuthService();
        apiRoutes = new ApiRoutes(mockApp, userService, authService);
    });
    
    test('should setup all routes correctly', () => {
        expect(mockApp.get).toHaveBeenCalledWith('/api/users/:id', expect.any(Function));
        expect(mockApp.post).toHaveBeenCalledWith('/api/users', expect.any(Function));
        expect(mockApp.post).toHaveBeenCalledWith('/api/auth/login', expect.any(Function));
        expect(mockApp.post).toHaveBeenCalledWith('/api/auth/logout', expect.any(Function));
    });
});
EOF

git add .
git commit -m "Add comprehensive API integration tests"

# Tornare a main e fare merge
git checkout main
git merge feature/authentication --no-edit
git merge feature/database --no-edit
git merge feature/api --no-edit

# Taggare versione stabile
git tag v2.0.0

echo "✅ Storia complessa creata con multiple feature!"
git log --oneline --graph --all
```

### Fase 3: Preparazione Scenari di Recovery

```bash
# Creare branch di backup per reference
git checkout -b backup-reference
git checkout main

# Creare file di configurazione critico
cat > config.json << 'EOF'
{
    "database": {
        "host": "localhost",
        "port": 5432,
        "name": "advanced_app",
        "credentials": {
            "username": "app_user",
            "password": "super_secret_password"
        }
    },
    "api": {
        "port": 3000,
        "jwt_secret": "jwt_super_secret_key_12345",
        "rate_limit": 100
    },
    "features": {
        "authentication": true,
        "database_logging": true,
        "api_caching": false
    }
}
EOF

git add config.json
git commit -m "Add critical application configuration"

# Creare alcuni commit di lavoro in corso
echo "console.log('Debug info');" >> src/main.js
git add .
git commit -m "Add debug logging (work in progress)"

echo "// TODO: implement caching" >> src/services/user.js  
git add .
git commit -m "WIP: caching improvements"

echo "✅ Setup completo! Repository pronto per recovery avanzato."
```

## 🎮 Scenari di Recovery Complessi

### Scenario 1: "Catastrophic History Loss"

#### Situazione
Un problema grave ha corrotto parte della storia Git. Devi ricostruire il più possibile.

```bash
# ATTENZIONE: Fai backup prima di questa simulazione!
cp -r .git .git-backup-scenario1

# Simulare perdita di oggetti critici
rm -rf .git/objects/pack/
find .git/objects -type f | head -10 | xargs rm 2>/dev/null || true

# Verificare il danno
git fsck --full
git log --oneline  # Probabilmente fallirà
```

#### 🎯 Tua Missione
1. **Diagnosi completa**: Determina esattamente cosa è stato perso
2. **Recovery da reflog**: Usa reflog per trovare commit salvabili
3. **Recovery da fsck**: Trova oggetti unreachable utilizzabili
4. **Ricostruzione**: Ricostruisci la storia usando tutti i metodi disponibili
5. **Verifica integrità**: Assicurati che il recovery sia completo

#### 📋 Checklist Recovery
```bash
# 1. Diagnosi
git fsck --full --unreachable > fsck-report.txt
git reflog --all > reflog-dump.txt 2>/dev/null || echo "Reflog damaged"
git for-each-ref > refs-dump.txt 2>/dev/null || echo "Refs damaged"

# 2. Analisi danni
echo "=== DAMAGE ASSESSMENT ==="
wc -l fsck-report.txt reflog-dump.txt refs-dump.txt

# 3. Recovery plan
echo "Recovery strategy needed based on what's available..."
```

#### 💡 Tecniche da Usare
- `git fsck --unreachable --dangling`
- `git reflog --all`
- `git rev-list --all --objects`
- Ricostruzione manual di refs
- Import da backup esterni

### Scenario 2: "Critical File Archaeological Recovery"

#### Situazione
Un file di configurazione critico con password è stato eliminato dalla storia 15 commit fa, e devi recuperarlo senza perdere la cronologia attuale.

```bash
# Setup scenario
echo "Starting archaeological recovery scenario..."

# Il file config.json è nella storia, ma dobbiamo simulare che sia "perso"
# Creiamo una situazione dove non sappiamo dove trovarlo
git log --oneline | head -20  # Tanti commit da analizzare
```

#### 🎯 Tua Missione
1. **Analisi forense**: Trova QUANDO il file esisteva nella storia
2. **Estrazione chirurgica**: Recupera il file senza disturbare la storia attuale
3. **Verifica contenuto**: Assicurati che il contenuto sia quello giusto
4. **Integrazione sicura**: Reintegra il file nel progetto attuale
5. **Documentazione**: Documenta cosa conteneva il file per future referenze

#### 🔍 Strumenti di Ricerca
```bash
# Ricerca avanzata nel repository
git log --all --full-history --follow -- config.json
git log --all --source --grep="config"
git log --all --source -S"password" --pickaxe-regex
git rev-list --all | xargs git grep -l "jwt_secret" 2>/dev/null || true
```

#### 📋 Template Investigation Report
```markdown
## Archaeological Recovery Report
**Target**: config.json
**Search Period**: Last 30 commits
**Methods Used**: 
- [ ] git log --follow
- [ ] git grep across history  
- [ ] Object content analysis
- [ ] Reflog analysis

**Findings**:
- Last seen in commit: [SHA1]
- Content included: [description]
- Reason for removal: [if determinable]

**Recovery Action**:
- Method: [describe approach]
- Commands: [list exact commands]
- Verification: [how you confirmed success]
```

### Scenario 3: "Multi-Source Repository Reconstruction"

#### Situazione
Il repository centrale è danneggiato, ma hai accesso a:
- Un clone locale vecchio di 1 settimana
- Backup parziale degli oggetti
- Working directory di un collega
- Bundle file di 3 giorni fa

```bash
# Preparare fonti multiple per simulazione
echo "=== CREATING MULTI-SOURCE SCENARIO ==="

# Fonte 1: Clone vecchio (simula clone di 1 settimana fa)
cd ..
git clone git-advanced-recovery git-old-clone
cd git-old-clone
git reset --hard HEAD~5  # Simula che sia indietro
cd ../git-advanced-recovery

# Fonte 2: Bundle parziale
git bundle create ../partial-backup.bundle HEAD~3..HEAD

# Fonte 3: Working directory backup
mkdir ../colleague-workdir
cp -r src tests docs ../colleague-workdir/
echo "Additional work from colleague" > ../colleague-workdir/colleague-notes.txt

# Fonte 4: Oggetti parziali
mkdir ../objects-backup
cp -r .git/objects/* ../objects-backup/ 2>/dev/null || true

# Ora simula danno al repository principale
echo "Simulating damage to main repository..."
rm -rf .git/objects/pack/
find .git/objects -name "*.tmp" -delete 2>/dev/null || true

echo "✅ Multi-source scenario ready!"
echo "Available sources:"
echo "- ../git-old-clone (1 week old)"
echo "- ../partial-backup.bundle (3 days old)"  
echo "- ../colleague-workdir (working files)"
echo "- ../objects-backup (partial objects)"
```

#### 🎯 Tua Missione
1. **Analisi fonti**: Valuta cosa è disponibile in ogni fonte
2. **Strategia di merge**: Determina la migliore strategia di combinazione
3. **Ricostruzione**: Combina tutte le fonti per massimizzare il recovery
4. **Validazione**: Verifica che la ricostruzione sia coerente
5. **Ottimizzazione**: Pulisci e ottimizza il repository ricostruito

#### 🔧 Workflow di Ricostruzione
```bash
# Template per approccio sistematico
echo "=== MULTI-SOURCE RECOVERY WORKFLOW ==="
echo "1. Initialize new recovery repository"
echo "2. Import from most complete source"
echo "3. Layer additional sources"  
echo "4. Resolve conflicts and inconsistencies"
echo "5. Validate reconstruction"
echo "6. Document process"
```

### Scenario 4: "Live Repository Forensics"

#### Situazione
Durante lo sviluppo qualcosa è andato storto e il team non sa cosa. Devi fare analisi forense di un repository "live" per capire cosa è successo.

#### 🎯 Tua Missione
1. **Timeline reconstruction**: Ricostruisci esattamente cosa è successo
2. **Impact analysis**: Determina cosa è stato affetto
3. **Root cause**: Trova la causa originale del problema
4. **Recovery plan**: Proponi strategia di recovery
5. **Prevention**: Suggerisci come prevenire in futuro

#### 🕵️ Strumenti Forensi
```bash
#!/bin/bash
# forensic-analysis.sh

echo "=== GIT FORENSIC ANALYSIS ==="
echo "Timestamp: $(date)"

# 1. Repository status
echo "## Current Status" 
git status --porcelain
git branch -a

# 2. Recent activity timeline
echo "## Recent Activity (Last 24 hours)"
git log --since="24 hours ago" --pretty=format:"%h %ad %an %s" --date=iso

# 3. Reflog analysis
echo "## Reference Changes"
git reflog --all --since="24 hours ago"

# 4. Object integrity
echo "## Repository Integrity"
git fsck --full --strict

# 5. Unusual patterns
echo "## Unusual Patterns"
git log --since="7 days ago" --grep="force\|reset\|rebase\|amend" --pretty=format:"%h %ad %an %s"

# 6. File changes analysis
echo "## Significant File Changes"
git log --since="7 days ago" --name-status --pretty=format:"%h %ad %an" | grep -E "^[AMD]"
```

## 🔬 Esercizi di Approfondimento

### Esercizio A: "Automated Recovery System"

Sviluppa un sistema automatizzato per recovery che:
1. Diagnostica automaticamente problemi comuni
2. Suggerisce strategie di recovery appropriate
3. Esegue recovery automatico quando sicuro
4. Documenta tutto il processo

```bash
#!/bin/bash
# advanced-recovery-system.sh
# TUO COMPITO: Implementare questo sistema

auto_diagnose() {
    echo "Performing automated diagnosis..."
    # TODO: Implementare logica di diagnosi
}

suggest_recovery() {
    local issue_type="$1"
    echo "Suggesting recovery for: $issue_type"
    # TODO: Implementare suggerimenti basati su tipo di problema
}

execute_recovery() {
    local strategy="$1"
    echo "Executing recovery strategy: $strategy"
    # TODO: Implementare esecuzione sicura
}

# Main logic
auto_diagnose
# Based on diagnosis, suggest and optionally execute recovery
```

### Esercizio B: "Cross-Platform Recovery"

Testa le tue tecniche di recovery su diversi sistemi operativi e configura soluzioni che funzionano everywhere.

### Esercizio C: "Performance Recovery"

Oltre al recupero funzionale, ottimizza anche le performance del repository recuperato (gc, repack, etc.).

## 📊 Metriche di Successo

### Recovery Completeness Score
```bash
#!/bin/bash
# calculate-recovery-score.sh

ORIGINAL_COMMITS=$(git rev-list --all --count backup-reference 2>/dev/null || echo 0)
RECOVERED_COMMITS=$(git rev-list --all --count 2>/dev/null || echo 0)
ORIGINAL_FILES=$(git ls-tree -r --name-only backup-reference | wc -l 2>/dev/null || echo 0)
RECOVERED_FILES=$(git ls-tree -r --name-only HEAD | wc -l 2>/dev/null || echo 0)

COMMIT_RECOVERY=$(( RECOVERED_COMMITS * 100 / ORIGINAL_COMMITS ))
FILE_RECOVERY=$(( RECOVERED_FILES * 100 / ORIGINAL_FILES ))
OVERALL_SCORE=$(( (COMMIT_RECOVERY + FILE_RECOVERY) / 2 ))

echo "=== RECOVERY SCORE ==="
echo "Commits recovered: $COMMIT_RECOVERY%"
echo "Files recovered: $FILE_RECOVERY%"  
echo "Overall score: $OVERALL_SCORE%"
```

## 📝 Documentation Requirements

Per ogni scenario completato, documenta:

### Scenario Report Template
```markdown
# Recovery Scenario Report: [Name]

## Initial Situation
- **Problem**: [Description]
- **Symptoms**: [What was broken]
- **Available Resources**: [What tools/data you had]

## Analysis Phase
- **Diagnostic Commands**: [Commands used to understand the problem]
- **Findings**: [What you discovered]
- **Damage Assessment**: [Scope of the problem]

## Recovery Strategy
- **Chosen Approach**: [Why this strategy]
- **Alternative Approaches**: [Other options considered]
- **Risk Assessment**: [Potential risks]

## Execution
- **Step-by-step Commands**: [Exact commands executed]
- **Verification**: [How you confirmed success]
- **Complications**: [Any issues encountered]

## Results
- **Recovery Success Rate**: [Percentage of data recovered]
- **Time Taken**: [How long the recovery took]
- **Lessons Learned**: [Key insights]

## Prevention
- **Future Prevention**: [How to avoid this problem]
- **Monitoring**: [Early warning signs]
- **Backup Strategy**: [Recommended backup approach]
```

## ✅ Completion Checklist

### Basic Requirements
- [ ] All 4 main scenarios attempted
- [ ] At least 2 scenarios fully completed
- [ ] Recovery scores calculated for each attempt
- [ ] Complete documentation for each scenario
- [ ] At least 1 automation script developed

### Advanced Requirements  
- [ ] All scenarios completed with >80% recovery rate
- [ ] Custom forensic analysis script developed
- [ ] Multi-source recovery successfully executed
- [ ] Performance optimization implemented
- [ ] Cross-platform testing completed

### Mastery Level
- [ ] 100% recovery rate achieved in at least 2 scenarios
- [ ] Automated recovery system fully functional
- [ ] Original techniques developed and documented
- [ ] Mentored others through the exercises
- [ ] Contributed improvements to the exercise itself

## 🎖️ Certification Achievement

Upon completion, you should be capable of:
- **Forensic Analysis**: Determining what happened in complex Git scenarios
- **Multi-Method Recovery**: Using combined techniques for maximum data recovery
- **Automation**: Creating scripts to handle common recovery scenarios
- **Risk Assessment**: Understanding the implications of different recovery strategies
- **Advanced Prevention**: Implementing comprehensive backup and monitoring strategies

**Next Challenge**: Exercise 3 - "Emergency Response Simulation"
