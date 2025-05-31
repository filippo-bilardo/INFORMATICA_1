# Esempio 2: Integrazione Feature - Merge Ricorsivo

## Scenario
Integrazione di una feature complessa sviluppata in parallelo al main branch, dimostrando merge ricorsivo e gestione di modifiche concorrenti.

## Setup Progetto

```bash
# Crea repository per feature integration
mkdir feature-integration-example
cd feature-integration-example
git init

# Struttura progetto base
mkdir -p src/{components,utils,styles}
mkdir tests

# File iniziali
cat > src/app.js << 'EOF'
// Main Application
class App {
    constructor() {
        this.version = "1.0.0";
        this.components = [];
    }
    
    init() {
        console.log(`App v${this.version} starting...`);
    }
}

export default App;
EOF

cat > src/styles/main.css << 'EOF'
/* Main Application Styles */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
}
EOF

git add .
git commit -m "Initial project setup with app structure"

# Secondo commit su main
cat > README.md << 'EOF'
# Feature Integration Example

This project demonstrates complex feature integration with Git merging.

## Setup
npm install
npm start

## Features
- Base application framework
EOF

git add README.md
git commit -m "Add project documentation"
```

## Sviluppo Feature Branch

### Inizia Feature: Sistema di Autenticazione
```bash
# Crea branch per feature di autenticazione
git checkout -b feature/authentication-system

# Commit 1: Struttura base auth
cat > src/components/auth.js << 'EOF'
// Authentication Component
class AuthSystem {
    constructor() {
        this.isAuthenticated = false;
        this.currentUser = null;
    }
    
    login(username, password) {
        // Simulate authentication
        if (username && password) {
            this.isAuthenticated = true;
            this.currentUser = { username, id: Date.now() };
            return true;
        }
        return false;
    }
    
    logout() {
        this.isAuthenticated = false;
        this.currentUser = null;
    }
    
    getCurrentUser() {
        return this.currentUser;
    }
}

export default AuthSystem;
EOF

git add src/components/auth.js
git commit -m "Add authentication system base structure"

# Commit 2: Utility functions per auth
cat > src/utils/crypto.js << 'EOF'
// Crypto utilities for authentication
export const hashPassword = (password) => {
    // Simple hash simulation (don't use in production!)
    return btoa(password + "salt123");
};

export const validatePassword = (password) => {
    const requirements = {
        minLength: password.length >= 8,
        hasUpper: /[A-Z]/.test(password),
        hasLower: /[a-z]/.test(password),
        hasNumber: /\d/.test(password)
    };
    
    return Object.values(requirements).every(req => req);
};

export const generateToken = () => {
    return Math.random().toString(36).substr(2) + Date.now().toString(36);
};
EOF

git add src/utils/crypto.js
git commit -m "Add crypto utilities for authentication"

# Commit 3: Styling per componenti auth
cat > src/styles/auth.css << 'EOF'
/* Authentication Styles */
.auth-container {
    max-width: 400px;
    margin: 50px auto;
    padding: 30px;
    border: 1px solid #ddd;
    border-radius: 8px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

.auth-form {
    display: flex;
    flex-direction: column;
    gap: 15px;
}

.auth-input {
    padding: 12px;
    border: 1px solid #ccc;
    border-radius: 4px;
    font-size: 16px;
}

.auth-button {
    padding: 12px;
    background-color: #007bff;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 16px;
}

.auth-button:hover {
    background-color: #0056b3;
}

.auth-error {
    color: #dc3545;
    font-size: 14px;
    margin-top: 5px;
}
EOF

git add src/styles/auth.css
git commit -m "Add authentication component styling"

# Commit 4: Test per auth system
cat > tests/auth.test.js << 'EOF'
// Authentication System Tests
import AuthSystem from '../src/components/auth.js';
import { validatePassword, hashPassword } from '../src/utils/crypto.js';

// Mock test framework
const assert = (condition, message) => {
    if (!condition) {
        throw new Error(`Test failed: ${message}`);
    }
    console.log(`✅ ${message}`);
};

// Test AuthSystem
const testAuthSystem = () => {
    const auth = new AuthSystem();
    
    // Test initial state
    assert(!auth.isAuthenticated, "Initial state should be unauthenticated");
    assert(auth.getCurrentUser() === null, "Initial user should be null");
    
    // Test login
    const loginSuccess = auth.login("testuser", "password123");
    assert(loginSuccess, "Login with valid credentials should succeed");
    assert(auth.isAuthenticated, "Should be authenticated after login");
    assert(auth.getCurrentUser().username === "testuser", "Should store correct username");
    
    // Test logout
    auth.logout();
    assert(!auth.isAuthenticated, "Should be unauthenticated after logout");
    assert(auth.getCurrentUser() === null, "User should be null after logout");
};

// Test crypto utilities
const testCryptoUtils = () => {
    // Test password validation
    assert(validatePassword("Password123"), "Valid password should pass validation");
    assert(!validatePassword("weak"), "Weak password should fail validation");
    
    // Test password hashing
    const hash1 = hashPassword("test123");
    const hash2 = hashPassword("test123");
    assert(hash1 === hash2, "Same password should produce same hash");
    assert(hash1 !== "test123", "Hash should be different from original password");
};

// Run tests
console.log("Running Authentication Tests...");
testAuthSystem();
testCryptoUtils();
console.log("All tests passed!");
EOF

git add tests/auth.test.js
git commit -m "Add comprehensive authentication tests"
```

## Sviluppo Parallelo su Main

### Nel Frattempo su Main Branch
```bash
# Simula sviluppo parallelo su main
git checkout main

# Aggiornamento 1: Miglioramento app principale
cat > src/app.js << 'EOF'
// Main Application - Enhanced Version
class App {
    constructor() {
        this.version = "1.1.0";
        this.components = [];
        this.config = {
            debug: false,
            apiEndpoint: "/api/v1"
        };
    }
    
    init() {
        console.log(`App v${this.version} starting...`);
        this.loadConfiguration();
        this.initializeComponents();
    }
    
    loadConfiguration() {
        console.log("Loading configuration...");
        // Load app configuration
    }
    
    initializeComponents() {
        console.log("Initializing components...");
        this.components.forEach(component => component.init());
    }
    
    addComponent(component) {
        this.components.push(component);
    }
}

export default App;
EOF

git add src/app.js
git commit -m "Enhance main app with configuration and component management"

# Aggiornamento 2: Nuovo component principale
cat > src/components/dashboard.js << 'EOF'
// Dashboard Component
class Dashboard {
    constructor() {
        this.widgets = [];
        this.layout = "grid";
    }
    
    init() {
        console.log("Dashboard initializing...");
        this.render();
    }
    
    render() {
        console.log("Rendering dashboard...");
        // Dashboard rendering logic
    }
    
    addWidget(widget) {
        this.widgets.push(widget);
    }
}

export default Dashboard;
EOF

git add src/components/dashboard.js
git commit -m "Add dashboard component to main application"

# Aggiornamento 3: Update styles
cat >> src/styles/main.css << 'EOF'

/* Dashboard Styles */
.dashboard {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 20px;
    margin-top: 20px;
}

.widget {
    background: white;
    border: 1px solid #e0e0e0;
    border-radius: 8px;
    padding: 20px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.widget-header {
    font-size: 18px;
    font-weight: bold;
    margin-bottom: 15px;
    color: #333;
}
EOF

git add src/styles/main.css
git commit -m "Add dashboard styling to main CSS"
```

## Merge Ricorsivo: Integrazione Feature

### Visualizza Stato Pre-Merge
```bash
# Mostra divergenza tra branch
git log --oneline --graph --all

# Mostra differenze
git diff main feature/authentication-system
```

### Esegui Merge Ricorsivo
```bash
# Torna su main per merge
git checkout main

# Esegui merge (sarà ricorsivo automaticamente)
git merge feature/authentication-system -m "Integrate authentication system

- Add AuthSystem component with login/logout functionality
- Add crypto utilities for password handling and validation
- Add authentication styling and user interface
- Add comprehensive test suite for authentication
- Maintains compatibility with enhanced main app structure"
```

### Analizza Risultato Merge
```bash
# Visualizza storia post-merge
git log --oneline --graph -10

# Mostra commit di merge dettagliatamente
git show --stat

# Verifica file integrati
find src -name "*.js" -o -name "*.css" | sort
```

## Integrazione Completa: Connessione Components

### Integra Authentication con App Principale
```bash
# Modifica app.js per includere authentication
cat > src/app.js << 'EOF'
// Main Application - With Authentication Integration
import AuthSystem from './components/auth.js';
import Dashboard from './components/dashboard.js';

class App {
    constructor() {
        this.version = "1.2.0";
        this.components = [];
        this.config = {
            debug: false,
            apiEndpoint: "/api/v1"
        };
        this.auth = new AuthSystem();
        this.dashboard = new Dashboard();
    }
    
    init() {
        console.log(`App v${this.version} starting...`);
        this.loadConfiguration();
        this.initializeAuthentication();
        this.initializeComponents();
    }
    
    loadConfiguration() {
        console.log("Loading configuration...");
        // Load app configuration
    }
    
    initializeAuthentication() {
        console.log("Setting up authentication...");
        this.addComponent(this.auth);
    }
    
    initializeComponents() {
        console.log("Initializing components...");
        this.components.forEach(component => {
            if (component.init) component.init();
        });
        
        // Initialize dashboard only if authenticated
        if (this.auth.isAuthenticated) {
            this.dashboard.init();
        }
    }
    
    addComponent(component) {
        this.components.push(component);
    }
    
    getAuthSystem() {
        return this.auth;
    }
}

export default App;
EOF

git add src/app.js
git commit -m "Integrate authentication system with main application"

# Aggiungi CSS imports
cat > src/styles/index.css << 'EOF'
/* Main CSS Import File */
@import url('./main.css');
@import url('./auth.css');

/* Global Integration Styles */
.app-container {
    min-height: 100vh;
    display: flex;
    flex-direction: column;
}

.app-header {
    background-color: #f8f9fa;
    padding: 15px;
    border-bottom: 1px solid #dee2e6;
}

.app-content {
    flex: 1;
    padding: 20px;
}

.user-info {
    display: flex;
    align-items: center;
    gap: 10px;
    margin-left: auto;
}

.logout-button {
    background-color: #6c757d;
    color: white;
    border: none;
    padding: 8px 16px;
    border-radius: 4px;
    cursor: pointer;
}
EOF

git add src/styles/index.css
git commit -m "Add integrated CSS imports and app-wide styling"
```

### Test Integrazione
```bash
# Crea test di integrazione
cat > tests/integration.test.js << 'EOF'
// Integration Tests
import App from '../src/app.js';

const assert = (condition, message) => {
    if (!condition) {
        throw new Error(`Integration test failed: ${message}`);
    }
    console.log(`✅ ${message}`);
};

const testAppIntegration = () => {
    const app = new App();
    
    // Test app initialization
    app.init();
    assert(app.version === "1.2.0", "App should have correct version");
    
    // Test auth integration
    const auth = app.getAuthSystem();
    assert(auth !== null, "App should have auth system");
    assert(!auth.isAuthenticated, "Should start unauthenticated");
    
    // Test login flow
    const loginResult = auth.login("testuser", "password123");
    assert(loginResult, "Login should succeed");
    assert(auth.isAuthenticated, "Should be authenticated after login");
    
    // Test component integration
    assert(app.components.length > 0, "App should have registered components");
    
    console.log("Authentication integrated successfully!");
};

console.log("Running Integration Tests...");
testAppIntegration();
console.log("All integration tests passed!");
EOF

git add tests/integration.test.js
git commit -m "Add integration tests for authentication feature"
```

## Analisi del Merge Ricorsivo

### Caratteristiche del Merge Ricorsivo
```bash
# Analizza commit di merge
git show --format=fuller

# Mostra albero di merge
git log --graph --pretty=format:'%h -%d %s (%cr) <%an>' --abbrev-commit -15
```

### Comprendi la Strategia Ricorsiva
Il merge ricorsivo ha:
1. **Trovato base comune** tra main e feature branch
2. **Creato merge automatico** dei file non conflittuali
3. **Preservato storia** di entrambi i branch
4. **Generato commit di merge** con due parent

### Cleanup Post-Merge
```bash
# Elimina feature branch completato
git branch -d feature/authentication-system

# Verifica stato finale
git log --oneline -5
git branch
```

## Vantaggi del Merge Ricorsivo

### Pro:
- **Preserva storia completa** di sviluppo
- **Gestisce automaticamente** modifiche non conflittuali
- **Tracciabilità** di quando la feature è stata integrata
- **Rollback facile** dell'intera feature

### Contro:
- **Storia più complessa** con branch multipli
- **Commit di merge** aggiuntivi
- **Possibili conflitti** da risolvere manualmente

## Script Demo Merge Ricorsivo

```bash
#!/bin/bash
# demo-recursive-merge.sh

echo "=== Demo Recursive Merge ==="

# Setup
rm -rf recursive-demo
mkdir recursive-demo && cd recursive-demo
git init

# Base setup
echo "base content" > file.txt
git add file.txt
git commit -m "Initial commit"

# Main development
echo "main enhancement" >> file.txt
git add file.txt
git commit -m "Main branch enhancement"

# Feature development
git checkout -b feature/new-feature
echo "feature content" > feature.txt
git add feature.txt
git commit -m "Add feature file"

echo "feature enhancement" >> file.txt
git add file.txt
git commit -m "Enhance base file in feature"

# Show divergence
echo "Before merge:"
git log --oneline --graph --all

# Recursive merge
git checkout main
git merge feature/new-feature -m "Integrate new feature"

echo -e "\nAfter recursive merge:"
git log --oneline --graph

echo -e "\nMerge commit details:"
git show --stat

echo -e "\nDemo complete!"
```

## Esercizi Pratici

1. **Simula sviluppo parallelo** con modifiche a file diversi
2. **Crea merge ricorsivo** con modifiche allo stesso file (senza conflitti)
3. **Analizza storia** di progetti open source per trovare merge ricorsivi
4. **Confronta dimensione** di commit di merge vs squash merge

---

Il merge ricorsivo è la strategia più comune per integrare feature complesse sviluppate in parallelo!
