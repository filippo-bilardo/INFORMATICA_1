# Esempio 4: Conflitti Complessi e Strategici

## Scenario
Gestione di conflitti complessi multi-file con dipendenze, refactoring simultanei e modifiche strutturali che richiedono strategia avanzata.

## Setup Scenario Enterprise

### Inizializzazione Progetto
```bash
mkdir complex-merge-scenario
cd complex-merge-scenario
git init

# Struttura progetto enterprise
mkdir -p src/{components,services,utils} tests docs

# File base application
cat > src/app.js << 'EOF'
// Main Application Entry Point
import { UserService } from './services/userService.js';
import { Logger } from './utils/logger.js';
import { DatabaseConnection } from './services/database.js';

class Application {
    constructor() {
        this.version = '1.0.0';
        this.userService = new UserService();
        this.logger = new Logger('INFO');
        this.database = new DatabaseConnection('mongodb://localhost:27017');
    }

    async start() {
        await this.database.connect();
        this.logger.info('Application started successfully');
        return this;
    }
}

export default Application;
EOF

# Service principale
cat > src/services/userService.js << 'EOF'
import { Logger } from '../utils/logger.js';

export class UserService {
    constructor() {
        this.logger = new Logger('UserService');
        this.users = new Map();
    }

    createUser(userData) {
        const user = {
            id: this.generateId(),
            ...userData,
            createdAt: new Date()
        };
        this.users.set(user.id, user);
        this.logger.info(`User created: ${user.id}`);
        return user;
    }

    generateId() {
        return Math.random().toString(36).substring(2, 15);
    }
}
EOF

# Package.json base
cat > package.json << 'EOF'
{
  "name": "enterprise-app",
  "version": "1.0.0",
  "type": "module",
  "description": "Enterprise application with complex architecture",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^6.10.0"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0"
  }
}
EOF

git add .
git commit -m "Initial enterprise application setup"
```

## Branch Divergenti con Conflitti Multipli

### Branch 1: Security Enhancement
```bash
git checkout -b security/auth-improvements

# Aggiornamento sicurezza in app.js
cat > src/app.js << 'EOF'
// Main Application Entry Point - Security Enhanced
import { UserService } from './services/userService.js';
import { Logger } from './utils/logger.js';
import { DatabaseConnection } from './services/database.js';
import { SecurityManager } from './services/securityManager.js';
import { AuthenticationService } from './services/authService.js';

class Application {
    constructor() {
        this.version = '1.0.1-security';
        this.userService = new UserService();
        this.logger = new Logger('INFO');
        this.database = new DatabaseConnection('mongodb://localhost:27017');
        this.security = new SecurityManager();
        this.auth = new AuthenticationService();
    }

    async start() {
        await this.security.initialize();
        await this.database.connect();
        this.logger.info('Application started with enhanced security');
        return this;
    }

    async authenticateRequest(request) {
        return await this.auth.validateToken(request.headers.authorization);
    }
}

export default Application;
EOF

# Miglioramenti sicurezza in UserService
cat > src/services/userService.js << 'EOF'
import { Logger } from '../utils/logger.js';
import { SecurityValidator } from '../utils/securityValidator.js';

export class UserService {
    constructor() {
        this.logger = new Logger('UserService');
        this.users = new Map();
        this.validator = new SecurityValidator();
    }

    createUser(userData) {
        // Validazione sicurezza
        if (!this.validator.validateUserData(userData)) {
            throw new Error('Invalid user data - security validation failed');
        }

        const user = {
            id: this.generateSecureId(),
            ...this.sanitizeUserData(userData),
            createdAt: new Date(),
            lastModified: new Date(),
            securityHash: this.generateSecurityHash(userData)
        };
        
        this.users.set(user.id, user);
        this.logger.info(`Secure user created: ${user.id.substring(0, 8)}***`);
        return this.stripSensitiveData(user);
    }

    generateSecureId() {
        return crypto.randomUUID();
    }

    sanitizeUserData(userData) {
        // Rimuovi caratteri potenzialmente pericolosi
        const sanitized = {};
        for (const [key, value] of Object.entries(userData)) {
            if (typeof value === 'string') {
                sanitized[key] = value.replace(/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi, '');
            } else {
                sanitized[key] = value;
            }
        }
        return sanitized;
    }

    generateSecurityHash(userData) {
        return `hash_${Date.now()}_${userData.email || 'anonymous'}`;
    }

    stripSensitiveData(user) {
        const {securityHash, ...publicData} = user;
        return publicData;
    }
}
EOF

# Aggiornamento dipendenze sicurezza
cat > package.json << 'EOF'
{
  "name": "enterprise-app",
  "version": "1.0.1-security",
  "type": "module",
  "description": "Enterprise application with enhanced security",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^6.10.0",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.0",
    "helmet": "^6.1.0"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "eslint-config-security": "^1.7.1"
  }
}
EOF

git add .
git commit -m "security: implement enhanced authentication and data validation"
```

### Branch 2: Performance Optimization
```bash
git checkout main
git checkout -b performance/optimization

# Ottimizzazioni performance in app.js
cat > src/app.js << 'EOF'
// Main Application Entry Point - Performance Optimized
import { UserService } from './services/userService.js';
import { Logger } from './utils/logger.js';
import { DatabaseConnection } from './services/database.js';
import { CacheManager } from './services/cacheManager.js';
import { PerformanceMonitor } from './utils/performanceMonitor.js';

class Application {
    constructor() {
        this.version = '1.0.1-performance';
        this.userService = new UserService();
        this.logger = new Logger('WARN'); // Ridotto logging per performance
        this.database = new DatabaseConnection('mongodb://localhost:27017');
        this.cache = new CacheManager();
        this.monitor = new PerformanceMonitor();
    }

    async start() {
        this.monitor.startTiming('application-startup');
        
        await Promise.all([
            this.database.connect(),
            this.cache.initialize()
        ]);
        
        this.monitor.endTiming('application-startup');
        this.logger.warn('Application started - performance optimized');
        return this;
    }

    async healthCheck() {
        return {
            status: 'healthy',
            performance: this.monitor.getStats(),
            cache: this.cache.getStats()
        };
    }
}

export default Application;
EOF

# Performance optimizations in UserService
cat > src/services/userService.js << 'EOF'
import { Logger } from '../utils/logger.js';

export class UserService {
    constructor() {
        this.logger = new Logger('UserService');
        this.users = new Map();
        this.userCache = new Map();
        this.batchOperations = [];
        this.batchSize = 100;
    }

    createUser(userData) {
        const user = {
            id: this.generateOptimizedId(),
            ...userData,
            createdAt: new Date()
        };
        
        // Batch operations per performance
        this.batchOperations.push({
            type: 'create',
            user: user
        });

        if (this.batchOperations.length >= this.batchSize) {
            this.processBatch();
        }

        this.users.set(user.id, user);
        this.userCache.set(user.id, user);
        
        // Ridotto logging per performance
        if (this.users.size % 100 === 0) {
            this.logger.info(`Users created: ${this.users.size}`);
        }
        
        return user;
    }

    generateOptimizedId() {
        // ID più semplice per performance
        return `user_${Date.now()}_${Math.random().toString(36).substring(2, 8)}`;
    }

    processBatch() {
        // Simula batch processing
        this.logger.info(`Processing batch of ${this.batchOperations.length} operations`);
        this.batchOperations = [];
    }

    getUserFromCache(id) {
        return this.userCache.get(id);
    }

    clearCache() {
        this.userCache.clear();
    }
}
EOF

# Dependencies per performance
cat > package.json << 'EOF'
{
  "name": "enterprise-app",
  "version": "1.0.1-performance",
  "type": "module",
  "description": "Enterprise application with performance optimizations",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.1",
    "mongoose": "^7.0.3",
    "redis": "^4.6.0",
    "cluster": "^0.7.7"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "clinic": "^12.0.0",
    "autocannon": "^7.10.0"
  }
}
EOF

git add .
git commit -m "perf: implement caching and batch operations for performance"
```

## Merge Complesso con Conflitti Multipli

### Tentativo di Merge
```bash
git checkout main
git merge security/auth-improvements

# Output: Success - primo merge OK

git merge performance/optimization
```

**Conflitti Risultanti:**
```
Auto-merging package.json
CONFLICT (content): Merge conflict in package.json
Auto-merging src/services/userService.js
CONFLICT (content): Merge conflict in src/services/userService.js
Auto-merging src/app.js  
CONFLICT (content): Merge conflict in src/app.js
Automatic merge failed; fix conflicts and then commit the result.
```

## Analisi e Strategia dei Conflitti

### 1. Conflitto in app.js
```javascript
// File con conflitti multipli
import { UserService } from './services/userService.js';
import { Logger } from './utils/logger.js';
import { DatabaseConnection } from './services/database.js';
<<<<<<< HEAD
import { SecurityManager } from './services/securityManager.js';
import { AuthenticationService } from './services/authService.js';
=======
import { CacheManager } from './services/cacheManager.js';
import { PerformanceMonitor } from './utils/performanceMonitor.js';
>>>>>>> performance/optimization

class Application {
    constructor() {
<<<<<<< HEAD
        this.version = '1.0.1-security';
        this.userService = new UserService();
        this.logger = new Logger('INFO');
        this.database = new DatabaseConnection('mongodb://localhost:27017');
        this.security = new SecurityManager();
        this.auth = new AuthenticationService();
=======
        this.version = '1.0.1-performance';
        this.userService = new UserService();
        this.logger = new Logger('WARN');
        this.database = new DatabaseConnection('mongodb://localhost:27017');
        this.cache = new CacheManager();
        this.monitor = new PerformanceMonitor();
>>>>>>> performance/optimization
    }

    async start() {
<<<<<<< HEAD
        await this.security.initialize();
        await this.database.connect();
        this.logger.info('Application started with enhanced security');
=======
        this.monitor.startTiming('application-startup');
        
        await Promise.all([
            this.database.connect(),
            this.cache.initialize()
        ]);
        
        this.monitor.endTiming('application-startup');
        this.logger.warn('Application started - performance optimized');
>>>>>>> performance/optimization
        return this;
    }
}
```

### Strategia di Risoluzione Intelligente

**Obiettivo:** Combinare sicurezza E performance senza compromessi.

```javascript
// Risoluzione strategica app.js
import { UserService } from './services/userService.js';
import { Logger } from './utils/logger.js';
import { DatabaseConnection } from './services/database.js';
import { SecurityManager } from './services/securityManager.js';
import { AuthenticationService } from './services/authService.js';
import { CacheManager } from './services/cacheManager.js';
import { PerformanceMonitor } from './utils/performanceMonitor.js';

class Application {
    constructor() {
        this.version = '1.1.0'; // Versione unificata
        this.userService = new UserService();
        this.logger = new Logger('INFO'); // Bilanciamento logging
        this.database = new DatabaseConnection('mongodb://localhost:27017');
        
        // Integrazione sicurezza E performance
        this.security = new SecurityManager();
        this.auth = new AuthenticationService();
        this.cache = new CacheManager();
        this.monitor = new PerformanceMonitor();
    }

    async start() {
        this.monitor.startTiming('application-startup');
        
        // Inizializzazione parallela con sicurezza
        await this.security.initialize();
        await Promise.all([
            this.database.connect(),
            this.cache.initialize()
        ]);
        
        this.monitor.endTiming('application-startup');
        this.logger.info('Application started - secure and optimized');
        return this;
    }

    async authenticateRequest(request) {
        // Funzionalità sicurezza mantenuta
        return await this.auth.validateToken(request.headers.authorization);
    }

    async healthCheck() {
        // Funzionalità performance mantenuta
        return {
            status: 'healthy',
            performance: this.monitor.getStats(),
            cache: this.cache.getStats(),
            security: this.security.getStatus()
        };
    }
}

export default Application;
```

### 2. Conflitto in userService.js

**Strategia:** Merge intelligente delle funzionalità.

```javascript
import { Logger } from '../utils/logger.js';
import { SecurityValidator } from '../utils/securityValidator.js';

export class UserService {
    constructor() {
        this.logger = new Logger('UserService');
        this.users = new Map();
        this.userCache = new Map();
        
        // Integrazione sicurezza + performance
        this.validator = new SecurityValidator();
        this.batchOperations = [];
        this.batchSize = 100;
    }

    createUser(userData) {
        // Validazione sicurezza PRIMA della performance
        if (!this.validator.validateUserData(userData)) {
            throw new Error('Invalid user data - security validation failed');
        }

        const user = {
            id: this.generateSecureId(), // Preferenza alla sicurezza per ID
            ...this.sanitizeUserData(userData),
            createdAt: new Date(),
            lastModified: new Date(),
            securityHash: this.generateSecurityHash(userData)
        };
        
        // Batch operations per performance
        this.batchOperations.push({
            type: 'create',
            user: user
        });

        if (this.batchOperations.length >= this.batchSize) {
            this.processBatch();
        }

        // Storage multiplo per sicurezza + performance
        this.users.set(user.id, user);
        this.userCache.set(user.id, user);
        
        // Logging bilanciato
        if (this.users.size % 50 === 0) { // Compromesso tra INFO e performance
            this.logger.info(`Secure users created: ${this.users.size}`);
        }
        
        return this.stripSensitiveData(user);
    }

    // Metodi sicurezza
    generateSecureId() {
        return crypto.randomUUID();
    }

    sanitizeUserData(userData) {
        const sanitized = {};
        for (const [key, value] of Object.entries(userData)) {
            if (typeof value === 'string') {
                sanitized[key] = value.replace(/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi, '');
            } else {
                sanitized[key] = value;
            }
        }
        return sanitized;
    }

    generateSecurityHash(userData) {
        return `hash_${Date.now()}_${userData.email || 'anonymous'}`;
    }

    stripSensitiveData(user) {
        const {securityHash, ...publicData} = user;
        return publicData;
    }

    // Metodi performance
    processBatch() {
        this.logger.info(`Processing secure batch of ${this.batchOperations.length} operations`);
        this.batchOperations = [];
    }

    getUserFromCache(id) {
        return this.userCache.get(id);
    }

    clearCache() {
        this.userCache.clear();
    }
}
```

### 3. Conflitto in package.json

**Strategia:** Unione completa delle dipendenze.

```json
{
  "name": "enterprise-app",
  "version": "1.1.0",
  "type": "module",
  "description": "Enterprise application with security and performance",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^7.0.3",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.0",
    "helmet": "^6.1.0",
    "redis": "^4.6.0",
    "cluster": "^0.7.7"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "eslint-config-security": "^1.7.1",
    "clinic": "^12.0.0",
    "autocannon": "^7.10.0"
  }
}
```

## Processo di Risoluzione Completo

### 1. Identificazione Sistematica
```bash
# Analizza tutti i conflitti
git status

# Per ogni file, analizza la natura del conflitto
git diff HEAD...performance/optimization -- src/app.js
git diff HEAD...security/auth-improvements -- src/app.js
```

### 2. Risoluzione Strategica
```bash
# Risolvi manualmente ogni file seguendo la strategia
# 1. app.js - Unifica funzionalità
# 2. userService.js - Merge intelligente  
# 3. package.json - Combina dipendenze

# Verifica che non ci siano marker residui
grep -r "<<<\|===\|>>>" src/ package.json
```

### 3. Testing Post-Merge
```bash
# Test syntax
node --check src/app.js
node --check src/services/userService.js

# Test dependencies
npm install
npm test

# Test funzionale
node -e "
import App from './src/app.js';
const app = new App();
console.log('App loads successfully:', app.version);
"
```

### 4. Commit Risoluzione
```bash
git add .
git commit -m "
resolve: merge security and performance enhancements

- Integrated security validation with performance optimizations
- Combined authentication services with caching mechanisms  
- Unified logging strategy balancing security and performance
- Merged dependency sets for comprehensive functionality

Features:
- Enhanced security with data validation and sanitization
- Performance optimizations with caching and batch operations
- Unified version 1.1.0 combining both enhancement branches
"
```

## Best Practices per Conflitti Complessi

### 1. Analisi Pre-Merge
```bash
# Confronta branch prima del merge
git log --oneline --graph main..security/auth-improvements
git log --oneline --graph main..performance/optimization

# Identifica file che saranno in conflitto
git merge-tree $(git merge-base main security/auth-improvements) security/auth-improvements performance/optimization
```

### 2. Strategia di Risoluzione
- **Priorità funzionale**: Sicurezza > Performance > Convenienza
- **Compatibilità**: Assicurati che le funzionalità si completino
- **Testing**: Verifica ogni risoluzione prima di procedere

### 3. Documentazione Decisioni
```markdown
## Merge Resolution Decisions

### Security vs Performance
- **ID Generation**: Scelta crypto.randomUUID() per sicurezza
- **Logging Level**: Compromesso INFO level con batch reporting
- **Caching**: Integrato con validazione sicurezza

### Version Strategy
- Bump to 1.1.0 per riflettere funzionalità combinate
- Mantenuto backward compatibility

### Dependencies
- Unified all dependencies da entrambi i branch
- Risolte versioni conflittuali scegliendo la più recente sicura
```

## 🎯 Risultato

Hai imparato a:
- Analizzare conflitti complessi multi-file
- Sviluppare strategie di risoluzione intelligenti
- Bilanciare priorità funzionali contrastanti
- Documentare decisioni di merge per il team
- Testare thoroughly risoluzione di conflitti complessi

---

[⬅️ Esempio Precedente](./03-risoluzione-vscode.md) | [🏠 Torna al README](../README.md)
