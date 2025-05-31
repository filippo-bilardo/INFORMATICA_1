# 04 - Team Workflow e Coordinamento

## 🎯 Obiettivo
Implementare workflow di branching efficaci per team, includendo coordinamento, comunicazione e risoluzione di conflitti tipici della collaborazione.

## 📋 Setup Team Simulation

### Simulazione Team Multi-Developer

#### Setup Repository Condiviso
```bash
# Creiamo repository per simulazione team
mkdir team-collaboration-demo
cd team-collaboration-demo
git init

# Setup iniziale del progetto
cat > package.json << 'EOF'
{
  "name": "team-collaboration-demo",
  "version": "1.0.0",
  "description": "Demo project for team collaboration",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  }
}
EOF

echo "# Team Collaboration Demo" > README.md
echo "console.log('Hello Team!');" > index.js
git add .
git commit -m "Initial project setup"

# Setup remote (simulato)
echo "# Simulated remote repository setup"
echo "git remote add origin https://github.com/team/collaboration-demo.git"
```

#### Team Members Setup
```bash
# Configurazione per simulare diversi sviluppatori
git config user.name "Alice Developer"
git config user.email "alice@company.com"

# Creiamo branch develop per integrazione
git checkout -b develop
echo "console.log('Development branch ready');" >> index.js
git add index.js
git commit -m "Setup development branch"
git checkout main
```

### Scenario 1: Feature Development Parallelo

#### Developer Alice - Feature Authentication
```bash
# Alice inizia feature authentication
git config user.name "Alice Developer"
git checkout develop
git pull origin develop  # Simulated
git checkout -b feature/auth-system

# Sviluppo graduale con commit significativi
cat > auth.js << 'EOF'
// Authentication Module
class AuthSystem {
    constructor() {
        this.users = [];
        this.currentUser = null;
    }
    
    register(username, password) {
        // Registration logic
        console.log(`Registering user: ${username}`);
        this.users.push({username, password});
        return true;
    }
}

module.exports = AuthSystem;
EOF

git add auth.js
git commit -m "feat: Add user registration functionality"

# Aggiunta login functionality
cat >> auth.js << 'EOF'

    login(username, password) {
        // Login logic  
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            this.currentUser = user;
            console.log(`User ${username} logged in successfully`);
            return true;
        }
        return false;
    }
EOF

git add auth.js
git commit -m "feat: Add user login functionality"

# Update main index.js
echo "const AuthSystem = require('./auth');" >> index.js
echo "const auth = new AuthSystem();" >> index.js
git add index.js
git commit -m "feat: Integrate auth system with main app"
```

#### Developer Bob - Feature Database (Simultaneo)
```bash
# Simuliamo secondo developer
git config user.name "Bob Developer"
git config user.email "bob@company.com"

# Bob lavora su feature database in parallelo
git checkout develop
git checkout -b feature/database-layer

cat > database.js << 'EOF'
// Database Layer
class DatabaseManager {
    constructor() {
        this.connection = null;
        this.tables = new Map();
    }
    
    connect(connectionString) {
        console.log(`Connecting to database: ${connectionString}`);
        this.connection = connectionString;
        return true;
    }
    
    createTable(tableName, schema) {
        console.log(`Creating table: ${tableName}`);
        this.tables.set(tableName, {schema, data: []});
        return true;
    }
}

module.exports = DatabaseManager;
EOF

git add database.js
git commit -m "feat: Add database connection and table management"

# Aggiunta CRUD operations
cat >> database.js << 'EOF'

    insert(tableName, data) {
        const table = this.tables.get(tableName);
        if (table) {
            table.data.push(data);
            console.log(`Inserted data into ${tableName}`);
            return true;
        }
        return false;
    }
    
    select(tableName, conditions = {}) {
        const table = this.tables.get(tableName);
        if (table) {
            return table.data.filter(row => {
                return Object.keys(conditions).every(key => 
                    row[key] === conditions[key]
                );
            });
        }
        return [];
    }
EOF

git add database.js
git commit -m "feat: Add CRUD operations to database layer"
```

#### Developer Carol - Feature API (Terzo parallelo)
```bash
git config user.name "Carol Developer"
git config user.email "carol@company.com"

git checkout develop
git checkout -b feature/api-endpoints

cat > api.js << 'EOF'
// API Endpoints
const express = require('express');

class APIServer {
    constructor() {
        this.app = express();
        this.setupMiddleware();
        this.setupRoutes();
    }
    
    setupMiddleware() {
        this.app.use(express.json());
        this.app.use((req, res, next) => {
            console.log(`${req.method} ${req.path}`);
            next();
        });
    }
    
    setupRoutes() {
        this.app.get('/health', (req, res) => {
            res.json({status: 'OK', timestamp: new Date()});
        });
        
        this.app.get('/api/users', (req, res) => {
            // User endpoint logic
            res.json({users: []});
        });
    }
    
    start(port = 3000) {
        this.app.listen(port, () => {
            console.log(`API Server running on port ${port}`);
        });
    }
}

module.exports = APIServer;
EOF

git add api.js
git commit -m "feat: Add basic API server with health and user endpoints"

# Update package.json dependencies
cat > package.json << 'EOF'
{
  "name": "team-collaboration-demo",
  "version": "1.0.0",
  "description": "Demo project for team collaboration",
  "main": "index.js",
  "scripts": {
    "start": "node index.js",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "dependencies": {
    "express": "^4.18.0"
  }
}
EOF

git add package.json
git commit -m "feat: Add express dependency for API server"
```

### Scenario 2: Integration e Conflict Resolution

#### Integration Manager Workflow
```bash
git config user.name "Diana Manager"
git config user.email "diana@company.com"

# Visualizzazione stato team
echo "=== Team Progress Review ==="
git log --oneline --graph --all

# Integration planning
git checkout develop

# Integrazione feature 1 (Alice - Auth)
echo "Merging Alice's authentication feature..."
git merge feature/auth-system --no-ff
# Potential conflict: both modified index.js

# Risoluzione conflict su index.js
cat > index.js << 'EOF'
console.log('Hello Team!');
console.log('Development branch ready');
const AuthSystem = require('./auth');
const auth = new AuthSystem();

console.log('Application initialized with authentication');
EOF

git add index.js
git commit -m "resolve: Merge auth system integration"

# Integration feature 2 (Bob - Database)
echo "Merging Bob's database feature..."
git merge feature/database-layer --no-ff

# Integration feature 3 (Carol - API)
echo "Merging Carol's API feature..."
git merge feature/api-endpoints --no-ff

# Final integration in index.js
cat > index.js << 'EOF'
console.log('Hello Team!');
console.log('Development branch ready');

const AuthSystem = require('./auth');
const DatabaseManager = require('./database');
const APIServer = require('./api');

// Initialize components
const auth = new AuthSystem();
const db = new DatabaseManager();
const api = new APIServer();

// Setup database
db.connect('mongodb://localhost:27017/teamdemo');
db.createTable('users', {username: 'string', password: 'string'});

// Start API server
api.start(3000);

console.log('Application fully initialized');
EOF

git add index.js
git commit -m "integrate: Complete application with all features"
```

### Scenario 3: Code Review Process

#### Pull Request Simulation
```bash
# Simulazione processo PR per feature aggiuntiva
git checkout develop
git checkout -b feature/user-profile

cat > profile.js << 'EOF'
// User Profile Management
class UserProfile {
    constructor(authSystem, database) {
        this.auth = authSystem;
        this.db = database;
    }
    
    createProfile(userId, profileData) {
        if (!this.auth.currentUser) {
            throw new Error('User must be authenticated');
        }
        
        const profile = {
            userId,
            ...profileData,
            createdAt: new Date(),
            updatedAt: new Date()
        };
        
        return this.db.insert('profiles', profile);
    }
    
    getProfile(userId) {
        return this.db.select('profiles', {userId})[0] || null;
    }
    
    updateProfile(userId, updates) {
        if (!this.auth.currentUser) {
            throw new Error('User must be authenticated');
        }
        
        const profile = this.getProfile(userId);
        if (profile) {
            const updatedProfile = {
                ...profile,
                ...updates,
                updatedAt: new Date()
            };
            // In real implementation, would update existing record
            console.log('Profile updated:', updatedProfile);
            return updatedProfile;
        }
        return null;
    }
}

module.exports = UserProfile;
EOF

git add profile.js
git commit -m "feat: Add user profile management system"

# Self-review process
echo "=== Code Review Checklist ==="
echo "✅ Code follows team conventions"
echo "✅ Error handling implemented"
echo "✅ Dependencies properly managed"
echo "✅ Documentation adequate"
echo "✅ No hardcoded values"

# Address review feedback
cat >> profile.js << 'EOF'

    // Additional method based on review feedback
    validateProfileData(data) {
        const required = ['firstName', 'lastName', 'email'];
        const missing = required.filter(field => !data[field]);
        
        if (missing.length > 0) {
            throw new Error(`Missing required fields: ${missing.join(', ')}`);
        }
        
        if (data.email && !data.email.includes('@')) {
            throw new Error('Invalid email format');
        }
        
        return true;
    }
EOF

git add profile.js
git commit -m "feat: Add profile data validation based on review"
```

### Scenario 4: Hotfix Emergency

#### Production Issue Handling
```bash
# Simulazione bug critico in produzione
git checkout main
git checkout -b hotfix/security-vulnerability

echo "=== CRITICAL: Security vulnerability detected ==="
echo "Issue: Authentication system allows null passwords"

# Fix nel sistema auth
sed -i 's/user.password === password/user.password && user.password === password/' auth.js
git add auth.js
git commit -m "hotfix: Prevent login with null passwords - SECURITY"

# Test del fix
cat > security-test.js << 'EOF'
const AuthSystem = require('./auth');

// Test security fix
const auth = new AuthSystem();
auth.register('testuser', 'password123');
auth.register('vulnerable', null);

console.log('Testing valid login:', auth.login('testuser', 'password123'));
console.log('Testing null password:', auth.login('vulnerable', null));
console.log('Testing undefined password:', auth.login('vulnerable', undefined));
EOF

git add security-test.js
git commit -m "hotfix: Add security tests for null password fix"

# Merge immediato in main
git checkout main
git merge hotfix/security-vulnerability --no-ff
git tag v1.0.1-security

# Merge anche in develop
git checkout develop
git merge hotfix/security-vulnerability --no-ff

# Cleanup
git branch -d hotfix/security-vulnerability
```

## 🔧 Team Coordination Tools

### Branch Protection Rules
```bash
# Simulazione regole di protezione
cat > .github/branch-protection.md << 'EOF'
# Branch Protection Configuration

## Main Branch Protection
- Require pull request reviews (2 reviewers)
- Require status checks to pass
- Require branches to be up to date
- Restrict pushes to specific roles
- Require signed commits

## Develop Branch Protection  
- Require pull request reviews (1 reviewer)
- Require status checks to pass
- Allow force pushes by admins

## Feature Branch Guidelines
- Must branch from develop
- Must include issue number in name
- Must pass CI checks before merge
- Must be deleted after merge
EOF

git add .github/
git commit -m "docs: Add branch protection guidelines"
```

### Communication Templates
```bash
# Template per PR description
cat > .github/pull_request_template.md << 'EOF'
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature  
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No merge conflicts

## Related Issues
Fixes #(issue number)
EOF

git add .github/pull_request_template.md
git commit -m "docs: Add PR template for team coordination"
```

## 🏃‍♂️ Esercizio Pratico: Team Sprint Simulation

### Sprint Planning Workshop
1. **Setup Team Repository**
   - 4 team members
   - 5 user stories
   - 2-week sprint simulation

2. **Parallel Development**
   - Assign features to team members
   - Implement branching strategy
   - Simulate daily standups via commits

3. **Integration Challenges**
   - Intentional conflicts
   - Code review process
   - Hotfix during sprint

4. **Sprint Review**
   - Merge to release branch
   - Deploy simulation
   - Retrospective documentation

## 🎯 Risultati Attesi

Dopo questo esempio dovresti:
- ✅ Coordinare team su repository condiviso
- ✅ Gestire conflitti di merge complessi
- ✅ Implementare processo di code review
- ✅ Gestire hotfix in ambiente di team
- ✅ Utilizzare template e tool di coordinamento

## 💡 Best Practices per Team

### Daily Workflow
```bash
# Morning sync routine
git checkout develop
git pull origin develop
git checkout feature/my-feature
git rebase develop  # Keep feature updated

# Evening pushes
git push origin feature/my-feature
# Create/update PR if ready
```

### Communication Guidelines
- **Commit messages:** Clear, descriptive, follow convention
- **PR descriptions:** Include context, testing notes, screenshots
- **Code reviews:** Constructive, timely, focus on improvement
- **Branch naming:** Consistent, include issue numbers

### Conflict Prevention
```bash
# Regular sync with develop
git fetch origin
git rebase origin/develop

# Small, frequent commits
git add -p  # Stage specific chunks
git commit -m "specific change description"

# Communication before major changes
# Team notification for shared file modifications
```

## 🔗 Prossimi Passi

- [Esercizio: Team Collaboration](../esercizi/01-strategy-selection.md)
- [Guida: Workflow Comuni](../guide/06-workflow-comuni.md)

---

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 03-Pianificazione Strategica](./03-pianificazione-strategica.md)
- [➡️ Esercizi di Consolidamento](../esercizi/README.md)
