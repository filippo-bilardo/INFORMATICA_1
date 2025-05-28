# Esercizio 4: Rebase vs Merge - Scenario Decisionale

## 🎯 Obiettivo
Sviluppare il giudizio critico per scegliere tra rebase e merge in diversi scenari di sviluppo, comprendendo profondamente le implicazioni di ogni approccio.

## 📋 Scenario
Sei il team lead di un progetto software con diversi sviluppatori. Devi gestire multiple feature branches, hotfix, release branches e stabilire le policy del team per l'integrazione del codice.

## 🏗️ Setup Iniziale - Ambiente Multi-Developer

```bash
#!/bin/bash
# Creazione ambiente multi-developer per confronto rebase vs merge
mkdir rebase-vs-merge-exercise && cd rebase-vs-merge-exercise
git init
git config user.name "Team Lead"
git config user.email "lead@company.com"

echo "🏗️ Creazione ambiente collaborativo..."

# Setup progetto base
mkdir -p src/{api,frontend,shared} tests docs
cat > package.json << 'EOF'
{
  "name": "collaborative-project",
  "version": "1.0.0",
  "description": "Multi-developer project for rebase vs merge analysis",
  "main": "src/api/server.js",
  "scripts": {
    "start": "node src/api/server.js",
    "test": "jest",
    "lint": "eslint src/",
    "build": "webpack --mode production"
  },
  "dependencies": {
    "express": "^4.18.0",
    "lodash": "^4.17.21"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "webpack": "^5.0.0"
  }
}
EOF

# Base API structure
cat > src/api/server.js << 'EOF'
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Basic routes
app.get('/', (req, res) => {
  res.json({ message: 'API Server v1.0.0', status: 'running' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', timestamp: new Date().toISOString() });
});

app.listen(PORT, () => {
  console.log(\`Server running on port \${PORT}\`);
});

module.exports = app;
EOF

# Shared utilities
cat > src/shared/utils.js << 'EOF'
// Shared utility functions
function formatDate(date) {
  return new Date(date).toLocaleDateString();
}

function validateEmail(email) {
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
}

function generateId() {
  return Math.random().toString(36).substr(2, 9);
}

module.exports = { formatDate, validateEmail, generateId };
EOF

# Basic frontend
cat > src/frontend/app.js << 'EOF'
// Basic frontend application
class App {
  constructor() {
    this.apiBase = '/api';
    this.init();
  }

  init() {
    this.setupEventListeners();
    this.loadInitialData();
  }

  setupEventListeners() {
    // Setup DOM event listeners
    console.log('Event listeners setup complete');
  }

  async loadInitialData() {
    try {
      const response = await fetch(this.apiBase + '/');
      const data = await response.json();
      console.log('Initial data loaded:', data);
    } catch (error) {
      console.error('Failed to load initial data:', error);
    }
  }
}

// Initialize app when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
  new App();
});
EOF

git add .
git commit -m "Initial project setup - API server, frontend app, shared utilities"

echo "👥 Simulazione sviluppo multi-developer..."

# === DEVELOPER A: Feature Branch ===
echo "Developer A: Working on user authentication"
git checkout -b feature/user-auth
git config user.name "Developer A"
git config user.email "dev-a@company.com"

# Auth API endpoints
cat > src/api/auth.js << 'EOF'
const { validateEmail, generateId } = require('../shared/utils');

// In-memory user store (for demo)
const users = new Map();
const sessions = new Map();

function registerUser(email, password) {
  if (!validateEmail(email)) {
    throw new Error('Invalid email format');
  }
  
  if (users.has(email)) {
    throw new Error('User already exists');
  }
  
  const userId = generateId();
  users.set(email, { id: userId, email, password });
  return { id: userId, email };
}

function loginUser(email, password) {
  const user = users.get(email);
  if (!user || user.password !== password) {
    throw new Error('Invalid credentials');
  }
  
  const sessionId = generateId();
  sessions.set(sessionId, { userId: user.id, email: user.email });
  return { sessionId, user: { id: user.id, email: user.email } };
}

function validateSession(sessionId) {
  return sessions.get(sessionId) || null;
}

module.exports = { registerUser, loginUser, validateSession };
EOF

git add .
git commit -m "Add user authentication module with register/login functions"

# Update server to include auth routes
cat > src/api/server.js << 'EOF'
const express = require('express');
const { registerUser, loginUser, validateSession } = require('./auth');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Basic routes
app.get('/', (req, res) => {
  res.json({ message: 'API Server v1.1.0', status: 'running' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', timestamp: new Date().toISOString() });
});

// Authentication routes
app.post('/auth/register', async (req, res) => {
  try {
    const { email, password } = req.body;
    const user = registerUser(email, password);
    res.status(201).json({ success: true, user });
  } catch (error) {
    res.status(400).json({ success: false, error: error.message });
  }
});

app.post('/auth/login', async (req, res) => {
  try {
    const { email, password } = req.body;
    const result = loginUser(email, password);
    res.json({ success: true, ...result });
  } catch (error) {
    res.status(401).json({ success: false, error: error.message });
  }
});

app.listen(PORT, () => {
  console.log(\`Server running on port \${PORT}\`);
});

module.exports = app;
EOF

git add .
git commit -m "Integrate authentication routes into main server"

# Auth frontend components
cat > src/frontend/auth.js << 'EOF'
// Authentication frontend components
class AuthManager {
  constructor() {
    this.currentUser = null;
    this.sessionId = localStorage.getItem('sessionId');
  }

  async register(email, password) {
    try {
      const response = await fetch('/auth/register', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password })
      });
      
      const data = await response.json();
      if (data.success) {
        console.log('User registered successfully:', data.user);
        return data.user;
      } else {
        throw new Error(data.error);
      }
    } catch (error) {
      console.error('Registration failed:', error);
      throw error;
    }
  }

  async login(email, password) {
    try {
      const response = await fetch('/auth/login', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password })
      });
      
      const data = await response.json();
      if (data.success) {
        this.currentUser = data.user;
        this.sessionId = data.sessionId;
        localStorage.setItem('sessionId', this.sessionId);
        console.log('Login successful:', data.user);
        return data.user;
      } else {
        throw new Error(data.error);
      }
    } catch (error) {
      console.error('Login failed:', error);
      throw error;
    }
  }

  logout() {
    this.currentUser = null;
    this.sessionId = null;
    localStorage.removeItem('sessionId');
    console.log('User logged out');
  }

  isAuthenticated() {
    return !!this.currentUser && !!this.sessionId;
  }
}

// Export for use in main app
window.AuthManager = AuthManager;
EOF

git add .
git commit -m "Add frontend authentication manager with login/register UI integration"

# === PARALLELO: DEVELOPER B: Feature Branch ===
echo "Developer B: Working on product catalog (parallel development)"
git checkout main
git checkout -b feature/product-catalog
git config user.name "Developer B"
git config user.email "dev-b@company.com"

# Product catalog API
cat > src/api/products.js << 'EOF'
// Product catalog management
const { generateId } = require('../shared/utils');

// In-memory product store
const products = new Map();

// Sample data
const sampleProducts = [
  { name: 'Laptop Pro', category: 'Electronics', price: 1299.99, stock: 10 },
  { name: 'Wireless Mouse', category: 'Electronics', price: 29.99, stock: 50 },
  { name: 'Office Chair', category: 'Furniture', price: 299.99, stock: 5 },
  { name: 'Notebook Set', category: 'Stationery', price: 19.99, stock: 100 }
];

// Initialize with sample data
sampleProducts.forEach(product => {
  const id = generateId();
  products.set(id, { ...product, id });
});

function getAllProducts() {
  return Array.from(products.values());
}

function getProductById(id) {
  return products.get(id) || null;
}

function getProductsByCategory(category) {
  return Array.from(products.values()).filter(p => p.category === category);
}

function addProduct(productData) {
  const id = generateId();
  const product = { ...productData, id };
  products.set(id, product);
  return product;
}

function updateProduct(id, updates) {
  const product = products.get(id);
  if (!product) return null;
  
  const updatedProduct = { ...product, ...updates };
  products.set(id, updatedProduct);
  return updatedProduct;
}

function deleteProduct(id) {
  return products.delete(id);
}

module.exports = {
  getAllProducts,
  getProductById,
  getProductsByCategory,
  addProduct,
  updateProduct,
  deleteProduct
};
EOF

git add .
git commit -m "Add product catalog API with CRUD operations"

# Update main server with product routes
cat > src/api/server.js << 'EOF'
const express = require('express');
const {
  getAllProducts,
  getProductById,
  getProductsByCategory,
  addProduct,
  updateProduct,
  deleteProduct
} = require('./products');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Basic routes
app.get('/', (req, res) => {
  res.json({ message: 'API Server v1.1.0', status: 'running' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', timestamp: new Date().toISOString() });
});

// Product routes
app.get('/products', (req, res) => {
  const { category } = req.query;
  const products = category ? getProductsByCategory(category) : getAllProducts();
  res.json({ success: true, products });
});

app.get('/products/:id', (req, res) => {
  const product = getProductById(req.params.id);
  if (product) {
    res.json({ success: true, product });
  } else {
    res.status(404).json({ success: false, error: 'Product not found' });
  }
});

app.post('/products', (req, res) => {
  try {
    const product = addProduct(req.body);
    res.status(201).json({ success: true, product });
  } catch (error) {
    res.status(400).json({ success: false, error: error.message });
  }
});

app.listen(PORT, () => {
  console.log(\`Server running on port \${PORT}\`);
});

module.exports = app;
EOF

git add .
git commit -m "Integrate product catalog routes into main server"

# Product frontend
cat > src/frontend/products.js << 'EOF'
// Product catalog frontend components
class ProductCatalog {
  constructor() {
    this.products = [];
    this.currentCategory = null;
  }

  async loadProducts(category = null) {
    try {
      const url = category ? \`/products?category=\${category}\` : '/products';
      const response = await fetch(url);
      const data = await response.json();
      
      if (data.success) {
        this.products = data.products;
        this.currentCategory = category;
        this.renderProducts();
        return this.products;
      } else {
        throw new Error(data.error);
      }
    } catch (error) {
      console.error('Failed to load products:', error);
      throw error;
    }
  }

  async getProduct(id) {
    try {
      const response = await fetch(\`/products/\${id}\`);
      const data = await response.json();
      
      if (data.success) {
        return data.product;
      } else {
        throw new Error(data.error);
      }
    } catch (error) {
      console.error('Failed to get product:', error);
      throw error;
    }
  }

  renderProducts() {
    console.log('Rendering products:', this.products.length);
    // In a real app, this would update the DOM
    this.products.forEach(product => {
      console.log(\`- \${product.name} (\${product.category}): $\${product.price}\`);
    });
  }

  filterByCategory(category) {
    return this.loadProducts(category);
  }

  getCategories() {
    const categories = [...new Set(this.products.map(p => p.category))];
    return categories;
  }
}

// Export for use in main app
window.ProductCatalog = ProductCatalog;
EOF

git add .
git commit -m "Add product catalog frontend with category filtering and product display"

# === MAIN BRANCH: Hotfix ===
echo "Hotfix needed on main branch (critical bug)"
git checkout main
git config user.name "Team Lead"
git config user.email "lead@company.com"

# Critical bug fix in utils
cat > src/shared/utils.js << 'EOF'
// Shared utility functions
function formatDate(date) {
  // HOTFIX: Handle null/undefined dates
  if (!date) return 'Unknown Date';
  return new Date(date).toLocaleDateString();
}

function validateEmail(email) {
  // HOTFIX: Handle null/undefined email
  if (!email || typeof email !== 'string') return false;
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
}

function generateId() {
  // HOTFIX: Ensure ID uniqueness with timestamp
  return Date.now().toString(36) + Math.random().toString(36).substr(2, 9);
}

module.exports = { formatDate, validateEmail, generateId };
EOF

git add .
git commit -m "HOTFIX: Add null checks and improve ID generation for production stability"

# Update version
sed -i 's/"version": "1.0.0"/"version": "1.0.1"/' package.json
git add package.json
git commit -m "Bump version to 1.0.1 for hotfix release"

echo "✅ Multi-developer ambiente creato!"
echo "📊 Stato repository:"
git branch -v
echo -e "\n📈 Log di tutti i branch:"
git log --oneline --graph --all
```

## 📝 Compiti da Svolgere

### Parte 1: Analisi dei Scenari

1. **Esamina la situazione attuale:**
   ```bash
   git log --oneline --graph --all
   git branch -v
   
   # Analizza le divergenze
   git log --oneline main..feature/user-auth
   git log --oneline main..feature/product-catalog
   git log --oneline feature/user-auth..main
   git log --oneline feature/product-catalog..main
   ```

2. **Identifica i tipi di cambiamenti:**
   - Hotfix critici
   - Feature indipendenti
   - Modifiche ai file condivisi
   - Potenziali conflitti

### Parte 2: Scenario 1 - Rebase Strategy

3. **Implementa una strategia basata su REBASE:**

   **Obiettivo:** Cronologia lineare e pulita

   ```bash
   # Prima applica gli hotfix a entrambe le feature (cherry-pick)
   git checkout feature/user-auth
   git cherry-pick main  # Applica l'hotfix
   
   git checkout feature/product-catalog  
   git cherry-pick main  # Applica l'hotfix
   
   # Poi fai rebase di una feature su main
   git checkout feature/user-auth
   git rebase main
   
   # Merge fast-forward in main
   git checkout main
   git merge feature/user-auth  # Dovrebbe essere fast-forward
   
   # Rebase della seconda feature
   git checkout feature/product-catalog
   git rebase main
   
   # Merge fast-forward
   git checkout main
   git merge feature/product-catalog
   ```

4. **Documenta il risultato del rebase strategy:**
   ```bash
   git log --oneline --graph
   echo "Rebase Strategy Result:" > rebase-strategy-result.md
   git log --oneline >> rebase-strategy-result.md
   git add rebase-strategy-result.md
   git commit -m "Document rebase strategy results"
   ```

### Parte 3: Reset e Scenario 2 - Merge Strategy

5. **Reset dell'ambiente per testare merge strategy:**

   ```bash
   # Salva il risultato rebase
   git branch rebase-strategy-result
   
   # Torna allo stato iniziale
   git reset --hard HEAD~3  # Torna prima dei merge
   git branch -D feature/user-auth feature/product-catalog
   
   # Ricrea i branch dalle posizioni originali
   git branch feature/user-auth rebase-strategy-result~2
   git branch feature/product-catalog rebase-strategy-result~1
   ```

6. **Implementa una strategia basata su MERGE:**

   **Obiettivo:** Preservare la cronologia delle feature

   ```bash
   # Applica hotfix a main se necessario
   git checkout main
   
   # Merge delle feature con commit espliciti
   git merge --no-ff feature/user-auth -m "Merge feature/user-auth - User authentication system"
   
   git merge --no-ff feature/product-catalog -m "Merge feature/product-catalog - Product catalog system"
   ```

7. **Documenta il risultato merge strategy:**
   ```bash
   git log --oneline --graph
   echo "Merge Strategy Result:" > merge-strategy-result.md
   git log --oneline --graph >> merge-strategy-result.md
   git add merge-strategy-result.md
   git commit -m "Document merge strategy results"
   ```

### Parte 4: Comparison Analysis

8. **Confronta i due approcci:**

   ```bash
   # Vedi i due risultati
   git log --oneline --graph rebase-strategy-result
   echo "---"
   git log --oneline --graph main
   ```

9. **Crea un'analisi dettagliata:**

   Crea il file `strategy-analysis.md`:

   ```markdown
   # Rebase vs Merge Strategy Analysis
   
   ## Scenario Testato
   - 2 feature branch paralleli
   - 1 hotfix critico su main
   - File condivisi modificati
   
   ## Rebase Strategy Results
   ### Vantaggi:
   - [ ] Cronologia lineare
   - [ ] Facilità di reading
   - [ ] Bisect funziona meglio
   
   ### Svantaggi:
   - [ ] Perdita context delle feature
   - [ ] SHA commit modificati
   - [ ] Risoluzione conflitti multipla
   
   ## Merge Strategy Results
   ### Vantaggi:
   - [ ] Cronologia preservata
   - [ ] Context delle feature visibile
   - [ ] SHA commit stabili
   
   ### Svantaggi:
   - [ ] Cronologia più complessa
   - [ ] Merge commit aggiuntivi
   - [ ] Bisect più difficile
   
   ## Raccomandazioni per Scenari Specifici
   - **Feature branches**: Merge
   - **Hotfix**: Cherry-pick + Rebase
   - **Release branches**: Merge
   - **Personal branches**: Rebase
   ```

### Parte 5: Scenari Specifici

10. **Testa scenari specifici:**

**a) Hotfix Strategy:**
```bash
# Crea situazione di hotfix critico
git checkout main
echo "CRITICAL: Security patch" > security-patch.txt
git add security-patch.txt
git commit -m "CRITICAL: Security vulnerability patch"

# Applica a tutti i branch attivi
git checkout feature/user-auth
git cherry-pick main

git checkout feature/product-catalog  
git cherry-pick main
```

**b) Release Branch Strategy:**
```bash
# Crea release branch
git checkout main
git checkout -b release/v1.1.0

# Fai merge solo delle feature pronte
git merge --no-ff feature/user-auth
# Test, bug fixes, etc.

# Final merge in main con tag
git checkout main
git merge --no-ff release/v1.1.0
git tag v1.1.0
```

**c) Personal Development Strategy:**
```bash
# Simula sviluppo personale con molti commit intermedi
git checkout -b personal/experiment
for i in {1..5}; do
  echo "Experiment step $i" > experiment-$i.txt
  git add experiment-$i.txt
  git commit -m "WIP: Experiment step $i"
done

# Cleanup con interactive rebase prima del merge
git rebase -i HEAD~5
# Squash dei commit intermedi

# Poi merge o rebase finale
```

## ✅ Risultati Attesi

### Alla Fine dell'Esercizio:

1. **Comprensione delle differenze:**
   - Quando ogni strategia è appropriata
   - Implicazioni di team e workflow
   - Effetti sui tool (bisect, blame, etc.)

2. **Policy recommendation documento:**
   - Linee guida per il team
   - Workflow standardizzato
   - Exception handling

3. **Hands-on experience:**
   - Risoluzione conflitti in entrambi i modi
   - Tool e comandi per ogni scenario
   - Recovery da situazioni problematiche

### Domande Finali di Analisi:

1. **Quale strategia preferiresti per:**
   - Feature development a lungo termine?
   - Hotfix critici?
   - Release preparation?
   - Personal experimentation?

2. **Come gestiresti:**
   - Un team di 10+ sviluppatori?
   - Release frequenti (CI/CD)?
   - Rollback di emergenza?
   - Code review workflow?

3. **Quali tool e automation implementeresti:**
   - Pre-commit hooks?
   - Automated testing per ogni strategia?
   - Branch protection rules?
   - Merge vs rebase automation?

## 🎉 Challenge Finale

**Crea la Git Policy del Team:**

Scrivi un documento `team-git-policy.md` che definisce:

1. **Branch Naming Conventions**
2. **Merge vs Rebase Decision Tree**
3. **Hotfix Procedure**
4. **Release Workflow**
5. **Code Review Requirements**
6. **Conflict Resolution Guidelines**
7. **Tool Configuration Standards**

## 📚 Riferimenti

- [Rebase vs Merge Guide](../guide/04-rebase-vs-merge.md)
- [Rebase Fundamentals](../guide/01-rebase-fundamentals.md)
- [Cherry-Pick Guide](../guide/03-cherry-pick-guide.md)
