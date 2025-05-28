# Esercizio 2: Reset, Revert e Gestione Cronologia

## Obiettivo
Padroneggiare l'uso di `git reset` e `git revert` per gestire situazioni complesse di correzione nella cronologia dei commit, comprendendo le differenze e quando utilizzare ciascun comando.

## Scenario
Stai sviluppando un'applicazione e-commerce e devi gestire varie situazioni problematiche nella cronologia dei commit, sia per correzioni locali che per problemi già pushati.

## Setup Iniziale

```bash
# Creare repository e-commerce
mkdir ecommerce-app && cd ecommerce-app
git init

# Setup struttura progetto
mkdir -p {src/{models,controllers,services},tests,config}

# Configurazione base
cat > package.json << 'EOF'
{
  "name": "ecommerce-app",
  "version": "1.0.0",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^7.0.0",
    "bcrypt": "^5.1.0"
  }
}
EOF

git add package.json
git commit -m "feat: initialize ecommerce project structure"
```

## Parte 1: Gestione Reset (Modifiche Locali)

### Task 1.1: Reset Soft - Preparare Commit Atomici
```bash
# Creare modello prodotto
cat > src/models/Product.js << 'EOF'
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    trim: true
  },
  description: {
    type: String,
    required: true
  },
  price: {
    type: Number,
    required: true,
    min: 0
  },
  category: {
    type: String,
    required: true,
    enum: ['electronics', 'clothing', 'books', 'home']
  },
  stock: {
    type: Number,
    required: true,
    min: 0,
    default: 0
  },
  images: [{
    type: String
  }],
  createdAt: {
    type: Date,
    default: Date.now
  }
});

module.exports = mongoose.model('Product', productSchema);
EOF

# Creare controller prodotto
cat > src/controllers/ProductController.js << 'EOF'
const Product = require('../models/Product');

class ProductController {
  async createProduct(req, res) {
    try {
      const product = new Product(req.body);
      await product.save();
      res.status(201).json(product);
    } catch (error) {
      res.status(400).json({ error: error.message });
    }
  }

  async getProducts(req, res) {
    try {
      const { category, minPrice, maxPrice } = req.query;
      const filter = {};
      
      if (category) filter.category = category;
      if (minPrice) filter.price = { $gte: minPrice };
      if (maxPrice) filter.price = { ...filter.price, $lte: maxPrice };

      const products = await Product.find(filter);
      res.json(products);
    } catch (error) {
      res.status(500).json({ error: error.message });
    }
  }

  async updateProduct(req, res) {
    try {
      const product = await Product.findByIdAndUpdate(
        req.params.id,
        req.body,
        { new: true, runValidators: true }
      );
      
      if (!product) {
        return res.status(404).json({ error: 'Product not found' });
      }
      
      res.json(product);
    } catch (error) {
      res.status(400).json({ error: error.message });
    }
  }

  async deleteProduct(req, res) {
    try {
      const product = await Product.findByIdAndDelete(req.params.id);
      
      if (!product) {
        return res.status(404).json({ error: 'Product not found' });
      }
      
      res.json({ message: 'Product deleted successfully' });
    } catch (error) {
      res.status(500).json({ error: error.message });
    }
  }
}

module.exports = new ProductController();
EOF

# Commit tutto insieme (non atomico)
git add .
git commit -m "feat: add product functionality"

# ❌ Problema: commit troppo grande, non atomico
```

**Compito**: Usa `git reset --soft` per separare questo commit in commit atomici:
1. Solo il modello Product
2. Solo il controller Product

**Soluzione Attesa**:
```bash
# Reset soft per tornare al commit precedente mantenendo changes in staging
git reset --soft HEAD~1

# Verificare stato
git status  # tutti i file sono in staging

# Commit atomico 1: solo modello
git reset HEAD  # unstage tutto
git add src/models/Product.js
git commit -m "feat(models): add Product model with validation

- Add mongoose schema for products
- Include required fields: name, description, price
- Add category enum validation
- Include stock management
- Add timestamps and image support"

# Commit atomico 2: solo controller
git add src/controllers/ProductController.js
git commit -m "feat(controllers): add ProductController with CRUD operations

- Implement create, read, update, delete operations
- Add query filtering by category and price range
- Include proper error handling
- Add validation for required fields"
```

### Task 1.2: Reset Mixed - Correzione Modifiche
```bash
# Aggiungere servizio utenti con errori
cat > src/services/UserService.js << 'EOF'
const bcrypt = require('bcrypt');

class UserService {
  constructor() {
    this.users = new Map();
  }

  async createUser(userData) {
    const { email, password, name } = userData;
    
    // Bug: password non hashata
    const user = {
      id: Date.now().toString(),
      email,
      password: password,  // ❌ password in chiaro
      name,
      createdAt: new Date()
    };
    
    this.users.set(user.id, user);
    return user;
  }

  async authenticateUser(email, password) {
    const user = Array.from(this.users.values())
      .find(u => u.email === email);
    
    if (!user) {
      throw new Error('User not found');
    }
    
    // Bug: confronto password in chiaro
    if (user.password !== password) {  // ❌ no bcrypt
      throw new Error('Invalid password');
    }
    
    return user;
  }
}

module.exports = UserService;
EOF

# Aggiungere anche config database
cat > config/database.js << 'EOF'
const mongoose = require('mongoose');

const connectDB = async () => {
  try {
    // Bug: hardcoded connection string con credenziali
    const conn = await mongoose.connect('mongodb://admin:password123@localhost:27017/ecommerce');  // ❌ credenziali esposte
    console.log(`MongoDB Connected: ${conn.connection.host}`);
  } catch (error) {
    console.error('Database connection error:', error);
    process.exit(1);
  }
};

module.exports = connectDB;
EOF

git add .
git commit -m "feat: add user service and database config"

# Rendersi conto degli errori di sicurezza
```

**Compito**: Usa `git reset --mixed` per correggere i problemi di sicurezza prima di ricommittare.

**Soluzione Attesa**:
```bash
# Reset mixed (default) per tornare indietro
git reset HEAD~1

# Verificare stato
git status  # file modificati ma non in staging

# Correggere UserService
cat > src/services/UserService.js << 'EOF'
const bcrypt = require('bcrypt');

class UserService {
  constructor() {
    this.users = new Map();
  }

  async createUser(userData) {
    const { email, password, name } = userData;
    
    // Validazione input
    if (!email || !password || !name) {
      throw new Error('Email, password, and name are required');
    }
    
    // Hash password
    const saltRounds = 12;
    const hashedPassword = await bcrypt.hash(password, saltRounds);
    
    const user = {
      id: Date.now().toString(),
      email,
      password: hashedPassword,
      name,
      createdAt: new Date()
    };
    
    this.users.set(user.id, user);
    
    // Non restituire password
    const { password: _, ...safeUser } = user;
    return safeUser;
  }

  async authenticateUser(email, password) {
    const user = Array.from(this.users.values())
      .find(u => u.email === email);
    
    if (!user) {
      throw new Error('User not found');
    }
    
    // Usare bcrypt per confronto
    const isValid = await bcrypt.compare(password, user.password);
    if (!isValid) {
      throw new Error('Invalid password');
    }
    
    // Restituire user senza password
    const { password: _, ...safeUser } = user;
    return safeUser;
  }
}

module.exports = UserService;
EOF

# Correggere database config
cat > config/database.js << 'EOF'
const mongoose = require('mongoose');

const connectDB = async () => {
  try {
    // Usare variabili ambiente
    const dbURL = process.env.MONGODB_URL || 'mongodb://localhost:27017/ecommerce';
    
    const conn = await mongoose.connect(dbURL, {
      useNewUrlParser: true,
      useUnifiedTopology: true,
    });
    
    console.log(`MongoDB Connected: ${conn.connection.host}`);
  } catch (error) {
    console.error('Database connection error:', error);
    process.exit(1);
  }
};

module.exports = connectDB;
EOF

# Aggiungere file .env.example
cat > .env.example << 'EOF'
# Database Configuration
MONGODB_URL=mongodb://localhost:27017/ecommerce

# JWT Configuration
JWT_SECRET=your-super-secret-jwt-key
JWT_EXPIRE=24h

# Server Configuration
PORT=3000
NODE_ENV=development
EOF

# Commit corretti
git add src/services/UserService.js
git commit -m "feat(services): add secure UserService with bcrypt

- Implement user creation with password hashing
- Add secure authentication with bcrypt comparison
- Include input validation
- Remove password from response data
- Use 12 rounds for salt generation"

git add config/database.js .env.example
git commit -m "feat(config): add secure database configuration

- Use environment variables for connection string
- Add connection options for stability
- Include .env.example template
- Remove hardcoded credentials"
```

### Task 1.3: Reset Hard - Rimuovere Completamente
```bash
# Aggiungere feature sperimentale problematica
cat > src/services/PaymentService.js << 'EOF'
// ❌ Implementazione sperimentale non sicura
class PaymentService {
  processPayment(amount, cardNumber, cvv) {
    // Simulazione pagamento - NON USARE IN PRODUZIONE
    console.log(`Processing payment: $${amount}`);
    console.log(`Card: ${cardNumber}`);  // ❌ Log dati sensibili
    console.log(`CVV: ${cvv}`);          // ❌ Log dati sensibili
    
    // Simulazione sempre successo
    return {
      success: true,
      transactionId: Math.random().toString(36).substr(2, 9)
    };
  }
}

module.exports = PaymentService;
EOF

cat > tests/payment.test.js << 'EOF'
const PaymentService = require('../src/services/PaymentService');

describe('PaymentService', () => {
  test('should process payment successfully', () => {
    const service = new PaymentService();
    const result = service.processPayment(100, '1234567890123456', '123');
    
    expect(result.success).toBe(true);
    expect(result.transactionId).toBeDefined();
  });
});
EOF

git add .
git commit -m "feat: add experimental payment service"

# Commit aggiuntivo con più problemi
cat >> src/services/PaymentService.js << 'EOF'

  // Metodo di debug - RIMUOVERE
  debugPayment(cardData) {
    console.log('FULL CARD DATA:', cardData);  // ❌ Grave violazione sicurezza
    return cardData;
  }
EOF

git add .
git commit -m "debug: add payment debugging (temporary)"

# Decisione: rimuovere completamente questi commit
```

**Compito**: Usa `git reset --hard` per eliminare completamente gli ultimi due commit problematici.

**Soluzione Attesa**:
```bash
# Verificare cronologia
git log --oneline -5

# Reset hard per rimuovere completamente
git reset --hard HEAD~2

# Verificare che i file siano stati rimossi
ls src/services/  # PaymentService.js non deve essere presente
git log --oneline -5  # ultimi 2 commit rimossi

# Verificare working directory pulita
git status  # nessuna modifica pending
```

## Parte 2: Gestione Revert (Modifiche Pubbliche)

### Task 2.1: Revert Singolo Commit
```bash
# Simulare push e commit pubblico problematico
echo "Simulating pushed commits..."

# Aggiungere feature carrello
cat > src/models/Cart.js << 'EOF'
const mongoose = require('mongoose');

const cartSchema = new mongoose.Schema({
  userId: {
    type: String,
    required: true
  },
  items: [{
    productId: {
      type: mongoose.Schema.Types.ObjectId,
      ref: 'Product',
      required: true
    },
    quantity: {
      type: Number,
      required: true,
      min: 1
    },
    price: {
      type: Number,
      required: true
    }
  }],
  total: {
    type: Number,
    default: 0
  },
  createdAt: {
    type: Date,
    default: Date.now
  },
  updatedAt: {
    type: Date,
    default: Date.now
  }
});

// Metodo per calcolare totale
cartSchema.methods.calculateTotal = function() {
  this.total = this.items.reduce((sum, item) => {
    return sum + (item.price * item.quantity);
  }, 0);
  this.updatedAt = new Date();
  return this.total;
};

module.exports = mongoose.model('Cart', cartSchema);
EOF

git add src/models/Cart.js
git commit -m "feat(models): add Cart model with total calculation"

# Commit problematico - bug nel calcolo sconto
cat > src/services/DiscountService.js << 'EOF'
class DiscountService {
  applyDiscount(cart, discountCode) {
    const discounts = {
      'SAVE10': 0.10,
      'SAVE20': 0.20,
      'WELCOME': 0.15
    };
    
    const discountPercent = discounts[discountCode];
    if (!discountPercent) {
      throw new Error('Invalid discount code');
    }
    
    // ❌ Bug: sottrae invece di moltiplicare
    cart.total = cart.total - discountPercent;  // Dovrebbe essere cart.total * (1 - discountPercent)
    
    return {
      originalTotal: cart.total + discountPercent,
      discountApplied: discountPercent,
      finalTotal: cart.total
    };
  }
}

module.exports = DiscountService;
EOF

git add src/services/DiscountService.js
git commit -m "feat(services): add discount service for promotional codes"

# Il bug viene scoperto dopo il push
echo "🚨 Bug discovered: discount calculation is incorrect!"
```

**Compito**: Il commit con il DiscountService ha un bug critico già pushato. Usa `git revert` per creare un commit che annulla le modifiche problematiche.

**Soluzione Attesa**:
```bash
# Identificare commit problematico
git log --oneline -3

# Revert del commit con bug (penultimo commit)
git revert HEAD~1

# Git aprirà editor per messaggio di revert, personalizzare:
# "revert: remove buggy discount service
# 
# This reverts commit [hash] due to critical bug in discount calculation.
# The service was subtracting percentage instead of applying percentage discount.
# 
# Issue: #123
# Will be reimplemented with proper calculation in next commit."

# Verificare che il file sia stato rimosso
ls src/services/  # DiscountService.js non presente
git log --oneline -4  # nuovo commit di revert presente
```

### Task 2.2: Revert con Conflitti
```bash
# Implementare versione corretta del DiscountService
cat > src/services/DiscountService.js << 'EOF'
class DiscountService {
  applyDiscount(cart, discountCode) {
    const discounts = {
      'SAVE10': 0.10,
      'SAVE20': 0.20,
      'WELCOME': 0.15,
      'STUDENT': 0.25  // Nuovo codice aggiunto
    };
    
    const discountPercent = discounts[discountCode];
    if (!discountPercent) {
      throw new Error('Invalid discount code');
    }
    
    const originalTotal = cart.total;
    // ✅ Calcolo corretto
    cart.total = cart.total * (1 - discountPercent);
    
    return {
      originalTotal,
      discountApplied: discountPercent * 100 + '%',
      discountAmount: originalTotal - cart.total,
      finalTotal: cart.total
    };
  }

  validateDiscountCode(code) {
    const discounts = {
      'SAVE10': 0.10,
      'SAVE20': 0.20,
      'WELCOME': 0.15,
      'STUDENT': 0.25
    };
    
    return discounts.hasOwnProperty(code);
  }
}

module.exports = DiscountService;
EOF

git add src/services/DiscountService.js
git commit -m "feat(services): implement correct discount calculation

- Fix discount calculation to use percentage properly
- Add new STUDENT discount code (25%)
- Add discount validation method
- Include detailed discount information in response"

# Ora qualcuno vuole fare revert del commit originale (quello già revertito)
# Questo creerà conflitti
```

**Compito**: Prova a fare revert del commit originale con DiscountService (quello prima del primo revert). Risolvi i conflitti mantenendo la versione corretta.

**Soluzione Attesa**:
```bash
# Trovare hash del commit originale con DiscountService (3 commit fa)
git log --oneline -5

# Tentare revert del commit originale
git revert HEAD~3

# ❌ Git mostrerà conflitti perché il file è stato modificato
# Aprire DiscountService.js e risolvere conflitti
# Mantenere la versione corretta (quella attuale)

# Dopo risoluzione conflitti
git add src/services/DiscountService.js
git revert --continue

# Messaggio di revert:
# "revert: attempt to revert original discount service
# 
# Resolved conflicts by keeping the corrected implementation.
# This ensures the proper discount calculation remains in place."
```

### Task 2.3: Revert Merge Commit
```bash
# Simulare merge di feature branch
git checkout -b feature/shopping-cart
cat > src/controllers/CartController.js << 'EOF'
const Cart = require('../models/Cart');
const Product = require('../models/Product');

class CartController {
  async addToCart(req, res) {
    try {
      const { userId, productId, quantity } = req.body;
      
      // Verificare prodotto esiste
      const product = await Product.findById(productId);
      if (!product) {
        return res.status(404).json({ error: 'Product not found' });
      }
      
      // Verificare stock disponibile
      if (product.stock < quantity) {
        return res.status(400).json({ error: 'Insufficient stock' });
      }
      
      // Trovare o creare carrello
      let cart = await Cart.findOne({ userId });
      if (!cart) {
        cart = new Cart({ userId, items: [] });
      }
      
      // Aggiungere o aggiornare item
      const existingItem = cart.items.find(item => 
        item.productId.toString() === productId
      );
      
      if (existingItem) {
        existingItem.quantity += quantity;
      } else {
        cart.items.push({
          productId,
          quantity,
          price: product.price
        });
      }
      
      cart.calculateTotal();
      await cart.save();
      
      res.json(cart);
    } catch (error) {
      res.status(500).json({ error: error.message });
    }
  }
}

module.exports = new CartController();
EOF

git add .
git commit -m "feat(cart): add cart controller with item management"

# Merge back to main
git checkout main
git merge feature/shopping-cart

# Scoprire che il merge ha introdotto problemi
echo "🚨 Cart feature has performance issues and needs to be removed!"
```

**Compito**: Il merge della feature carrello ha introdotto problemi di performance. Usa `git revert -m` per fare revert del merge commit.

**Soluzione Attesa**:
```bash
# Identificare merge commit
git log --oneline -3

# Revert merge commit (HEAD è il merge commit)
# -m 1 specifica che vogliamo tornare al primo parent (main branch)
git revert -m 1 HEAD

# Messaggio di revert:
# "revert: remove cart feature due to performance issues
# 
# This reverts merge commit [hash], reversing changes from feature/shopping-cart.
# The cart implementation needs optimization before reintegration.
# 
# Performance issues:
# - N+1 query problem in cart operations
# - Missing database indexes
# - Inefficient stock checking
# 
# Ticket: #456"

# Verificare che i file della feature siano stati rimossi
ls src/controllers/  # CartController.js non presente
```

## Parte 3: Scenari Complessi e Recovery

### Task 3.1: Combinazione Reset + Revert
```bash
# Situazione complessa: alcuni commit locali, alcuni pushati
echo "Creating complex scenario..."

# Commit pushato (sicuro)
cat > src/utils/validation.js << 'EOF'
const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

const validateEmail = (email) => {
  return emailRegex.test(email);
};

const validatePrice = (price) => {
  return typeof price === 'number' && price >= 0;
};

module.exports = { validateEmail, validatePrice };
EOF

git add src/utils/validation.js
git commit -m "feat(utils): add validation utilities"

# Commit locale con bug
cat > src/utils/helpers.js << 'EOF'
// ❌ Utility con bug
const formatPrice = (price) => {
  // Bug: non gestisce null/undefined
  return '$' + price.toFixed(2);
};

const generateId = () => {
  // Bug: non abbastanza random
  return Math.random().toString(36).substr(2, 5);
};

module.exports = { formatPrice, generateId };
EOF

git add src/utils/helpers.js
git commit -m "feat(utils): add helper functions"

# Commit locale che dipende dal precedente
cat > src/utils/index.js << 'EOF'
const { validateEmail, validatePrice } = require('./validation');
const { formatPrice, generateId } = require('./helpers');

module.exports = {
  validateEmail,
  validatePrice,
  formatPrice,
  generateId
};
EOF

git add src/utils/index.js
git commit -m "feat(utils): create utils barrel export"
```

**Compito**: 
1. Il commit di validation.js è già stato pushato (non modificare)
2. Gli ultimi 2 commit sono locali e hanno bug
3. Usa reset per rimuovere i 2 commit locali problematici
4. Reimplementa helpers.js correttamente

**Soluzione Attesa**:
```bash
# Reset per rimuovere ultimi 2 commit locali
git reset --hard HEAD~2

# Verificare stato
git log --oneline -3  # solo validation.js commit presente
ls src/utils/         # solo validation.js presente

# Reimplementare helpers correttamente
cat > src/utils/helpers.js << 'EOF'
/**
 * Format price with proper null/undefined handling
 */
const formatPrice = (price) => {
  if (price === null || price === undefined) {
    return '$0.00';
  }
  
  if (typeof price !== 'number' || isNaN(price)) {
    throw new Error('Price must be a valid number');
  }
  
  return '$' + Math.abs(price).toFixed(2);
};

/**
 * Generate cryptographically secure random ID
 */
const generateId = () => {
  // Use crypto for better randomness
  if (typeof window !== 'undefined' && window.crypto) {
    // Browser environment
    const array = new Uint32Array(8);
    window.crypto.getRandomValues(array);
    return Array.from(array, dec => dec.toString(16)).join('');
  } else {
    // Node.js environment
    const crypto = require('crypto');
    return crypto.randomBytes(16).toString('hex');
  }
};

/**
 * Safe string truncation
 */
const truncateString = (str, maxLength = 50) => {
  if (typeof str !== 'string') {
    return '';
  }
  
  if (str.length <= maxLength) {
    return str;
  }
  
  return str.substring(0, maxLength - 3) + '...';
};

module.exports = { 
  formatPrice, 
  generateId, 
  truncateString 
};
EOF

# Aggiungere test per sicurezza
mkdir -p tests/utils
cat > tests/utils/helpers.test.js << 'EOF'
const { formatPrice, generateId, truncateString } = require('../../src/utils/helpers');

describe('Helper Functions', () => {
  describe('formatPrice', () => {
    test('should format valid price', () => {
      expect(formatPrice(19.99)).toBe('$19.99');
      expect(formatPrice(0)).toBe('$0.00');
    });

    test('should handle null/undefined', () => {
      expect(formatPrice(null)).toBe('$0.00');
      expect(formatPrice(undefined)).toBe('$0.00');
    });

    test('should throw on invalid input', () => {
      expect(() => formatPrice('invalid')).toThrow();
      expect(() => formatPrice(NaN)).toThrow();
    });
  });

  describe('generateId', () => {
    test('should generate unique IDs', () => {
      const id1 = generateId();
      const id2 = generateId();
      expect(id1).not.toBe(id2);
      expect(id1.length).toBeGreaterThan(10);
    });
  });

  describe('truncateString', () => {
    test('should truncate long strings', () => {
      const long = 'This is a very long string that should be truncated';
      const result = truncateString(long, 20);
      expect(result).toBe('This is a very lo...');
      expect(result.length).toBe(20);
    });

    test('should handle edge cases', () => {
      expect(truncateString(null)).toBe('');
      expect(truncateString('short')).toBe('short');
    });
  });
});
EOF

# Commit corretto
git add .
git commit -m "feat(utils): add secure helper functions with validation

- Implement safe formatPrice with null handling
- Add cryptographically secure ID generation
- Include string truncation utility
- Add comprehensive test coverage"

# Creare barrel export corretto
cat > src/utils/index.js << 'EOF'
const { validateEmail, validatePrice } = require('./validation');
const { formatPrice, generateId, truncateString } = require('./helpers');

// Re-export all utilities
module.exports = {
  // Validation utilities
  validateEmail,
  validatePrice,
  
  // Helper utilities
  formatPrice,
  generateId,
  truncateString
};
EOF

git add src/utils/index.js
git commit -m "feat(utils): add comprehensive utils barrel export

- Export all validation and helper functions
- Organize by functional categories
- Provide single entry point for utilities"
```

## Parte 4: Verifica e Documentazione

### Task 4.1: Audit della Cronologia
**Compito**: Analizza la cronologia finale e documenta tutte le operazioni effettuate.

```bash
# Analizzare cronologia completa
git log --oneline --graph

# Verificare che non ci siano problemi
git status

# Controllare integrità repository
git fsck

# Creare report operazioni
cat > OPERATIONS_LOG.md << 'EOF'
# Git Operations Log

## Reset Operations
1. **Reset Soft**: Separated atomic commits for Product model/controller
2. **Reset Mixed**: Fixed security issues in UserService and database config
3. **Reset Hard**: Removed experimental payment service completely

## Revert Operations
1. **Single Revert**: Reverted buggy DiscountService
2. **Conflict Resolution**: Handled revert conflicts properly
3. **Merge Revert**: Reverted problematic cart feature merge

## Recovery Operations
1. **Complex Scenario**: Combined reset for local commits, kept pushed commits
2. **Reimplementation**: Rebuilt helpers with proper error handling and security

## Lessons Learned
- Use reset for local changes only
- Use revert for published commits
- Always test thoroughly before committing
- Atomic commits make history management easier
EOF

git add OPERATIONS_LOG.md
git commit -m "docs: add git operations audit log"
```

## Risultati Attesi

Al termine dell'esercizio dovresti avere:

1. **Cronologia pulita** senza commit problematici
2. **Codice sicuro** senza vulnerabilità
3. **Commit atomici** ben organizzati
4. **Documentazione** delle operazioni effettuate

### Verifica Finale
```bash
git log --oneline -10
# Dovrebbe mostrare cronologia pulita con:
# - Commit atomici ben descritti
# - Nessun commit problematico
# - Operazioni di revert documentate
# - Codice sicuro e testato
```

## Domande di Riflessione

1. **Reset vs Revert**: Quando usare ciascun comando?
2. **Sicurezza**: Come evitare la perdita di dati con reset --hard?
3. **Collaborazione**: Come comunicare operazioni di revert al team?
4. **Best Practices**: Come prevenire la necessità di queste operazioni?

## Estensioni Avanzate

### Git Hooks
- Implementa pre-commit hook per validazione
- Crea pre-push hook per controlli di sicurezza

### Scripting
- Script per backup prima di operazioni rischiose
- Automazione per operazioni di cleanup comuni

### Workflow Enterprise
- Procedure per emergenze in produzione
- Strategie di rollback automatizzate
