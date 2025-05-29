# Esempio 04: Workflow Complesso

## 📖 Descrizione

Questo esempio dimostra l'utilizzo dell'area di staging in scenari di sviluppo reali e complessi, simulando un team di sviluppo che lavora su un'applicazione web con multiple feature, hotfix e gestione di rilasci.

## 🎯 Obiettivi

- Gestire staging in progetti multi-sviluppatore
- Coordinare commit per feature diverse
- Gestire hotfix urgenti durante sviluppo
- Utilizzare staging per preparazione rilasci
- Implementare workflow di staging professionale

## 🏗️ Scenario: Applicazione E-commerce

Simuliamo lo sviluppo di un'applicazione e-commerce con:
- **Feature**: Sistema di pagamento
- **Feature**: Sistema di recensioni
- **Hotfix**: Bug critico nel carrello
- **Refactor**: Ottimizzazione performance

## 🚀 Setup del Progetto

```bash
# Creiamo il progetto di esempio
mkdir ecommerce-staging-workflow && cd ecommerce-staging-workflow
git init

# Struttura iniziale dell'applicazione
mkdir -p {src,tests,docs,config}
mkdir -p src/{components,utils,services,styles}
```

### Struttura File Base

```bash
# File di configurazione
cat > config/database.js << 'EOF'
module.exports = {
    host: 'localhost',
    port: 5432,
    database: 'ecommerce'
};
EOF

# Componente carrello esistente (con bug)
cat > src/components/Cart.js << 'EOF'
class Cart {
    constructor() {
        this.items = [];
        this.total = 0;
    }
    
    addItem(item) {
        this.items.push(item);
        this.calculateTotal(); // Bug: non aggiorna correttamente
    }
    
    calculateTotal() {
        this.total = this.items.reduce((sum, item) => sum + item.price, 0);
    }
    
    removeItem(id) {
        this.items = this.items.filter(item => item.id !== id);
        // Bug: total non viene ricalcolato
    }
}

module.exports = Cart;
EOF

# Test esistenti
cat > tests/cart.test.js << 'EOF'
const Cart = require('../src/components/Cart');

describe('Cart', () => {
    test('should add items correctly', () => {
        const cart = new Cart();
        cart.addItem({ id: 1, price: 10 });
        expect(cart.items.length).toBe(1);
    });
});
EOF

# Commit iniziale
git add .
git commit -m "Initial project setup with basic cart functionality"
```

## 🌟 Feature 1: Sistema di Pagamento

### Sviluppo Incrementale con Staging Strategico

```bash
# Iniziamo la feature di pagamento
cat > src/services/PaymentService.js << 'EOF'
class PaymentService {
    constructor(config) {
        this.apiKey = config.apiKey;
        this.endpoint = config.endpoint;
    }
    
    // Prima implementazione - solo struttura
    async processPayment(amount, cardInfo) {
        // TODO: Implementare logica di pagamento
        throw new Error('Not implemented yet');
    }
}

module.exports = PaymentService;
EOF

# Aggiungiamo solo il file base senza implementazione completa
git add src/services/PaymentService.js
git commit -m "feat: add PaymentService base structure

- Add PaymentService class with constructor
- Define processPayment method interface  
- Ready for implementation in next commits"
```

### Implementazione Graduale

```bash
# Implementiamo validazione input
cat > src/utils/PaymentValidator.js << 'EOF'
class PaymentValidator {
    static validateCardNumber(cardNumber) {
        // Algoritmo di Luhn semplificato
        return cardNumber && cardNumber.length >= 13;
    }
    
    static validateCVV(cvv) {
        return cvv && /^\d{3,4}$/.test(cvv);
    }
    
    static validateAmount(amount) {
        return amount > 0 && amount <= 10000;
    }
}

module.exports = PaymentValidator;
EOF

# Aggiorniamo PaymentService con validazione
cat > src/services/PaymentService.js << 'EOF'
const PaymentValidator = require('../utils/PaymentValidator');

class PaymentService {
    constructor(config) {
        this.apiKey = config.apiKey;
        this.endpoint = config.endpoint;
    }
    
    async processPayment(amount, cardInfo) {
        // Validazione input
        if (!PaymentValidator.validateAmount(amount)) {
            throw new Error('Invalid amount');
        }
        
        if (!PaymentValidator.validateCardNumber(cardInfo.number)) {
            throw new Error('Invalid card number');
        }
        
        if (!PaymentValidator.validateCVV(cardInfo.cvv)) {
            throw new Error('Invalid CVV');
        }
        
        // Simulazione chiamata API
        console.log(`Processing payment of $${amount}`);
        return { success: true, transactionId: Date.now() };
    }
}

module.exports = PaymentService;
EOF

# Staging strategico: aggiungiamo prima validatore, poi service
git add src/utils/PaymentValidator.js
git commit -m "feat: add payment validation utilities

- Implement card number validation with Luhn algorithm
- Add CVV format validation
- Add amount range validation
- Prepare for PaymentService integration"

# Ora committiamo l'aggiornamento del service
git add src/services/PaymentService.js
git commit -m "feat: implement payment processing with validation

- Integrate PaymentValidator into PaymentService
- Add input validation for all payment data
- Implement basic payment processing flow
- Add error handling for invalid inputs"
```

## 🚨 Hotfix Urgente: Bug nel Carrello

### Interruzione per Hotfix Critico

```bash
# Durante lo sviluppo, arriva un bug critico!
# Il total del carrello non si aggiorna quando si rimuovono items

# Creiamo un branch per hotfix (simulato con commit separato)
# Prima salviamo eventuale lavoro in corso
git status  # Verifichiamo se c'è lavoro non committato

# Fixiamo il bug nel carrello
cat > src/components/Cart.js << 'EOF'
class Cart {
    constructor() {
        this.items = [];
        this.total = 0;
    }
    
    addItem(item) {
        this.items.push(item);
        this.calculateTotal(); // Ora funziona correttamente
    }
    
    calculateTotal() {
        this.total = this.items.reduce((sum, item) => sum + item.price, 0);
    }
    
    removeItem(id) {
        this.items = this.items.filter(item => item.id !== id);
        this.calculateTotal(); // FIX: Ricalcola total dopo rimozione
    }
    
    // Nuovo metodo per debug
    getTotal() {
        return this.total;
    }
}

module.exports = Cart;
EOF

# Test per verificare il fix
cat > tests/cart-hotfix.test.js << 'EOF'
const Cart = require('../src/components/Cart');

describe('Cart Hotfix Tests', () => {
    test('should update total when removing items', () => {
        const cart = new Cart();
        cart.addItem({ id: 1, price: 10 });
        cart.addItem({ id: 2, price: 20 });
        expect(cart.getTotal()).toBe(30);
        
        cart.removeItem(1);
        expect(cart.getTotal()).toBe(20); // Questo falliva prima del fix
    });
});
EOF

# Staging del hotfix: priorità massima
git add src/components/Cart.js tests/cart-hotfix.test.js
git commit -m "hotfix: fix cart total calculation on item removal

Critical fix for production issue:
- Add calculateTotal() call in removeItem() method
- Add getTotal() method for better testing
- Add regression test to prevent future issues

Fixes: #BUG-001 - Cart total not updating on item removal"
```

## 🌟 Feature 2: Sistema di Recensioni

### Sviluppo Parallelo con Staging Attento

```bash
# Mentre lavoriamo su pagamenti, aggiungiamo anche recensioni
cat > src/components/ReviewSystem.js << 'EOF'
class ReviewSystem {
    constructor() {
        this.reviews = [];
    }
    
    addReview(productId, userId, rating, comment) {
        const review = {
            id: Date.now(),
            productId,
            userId,
            rating,
            comment,
            timestamp: new Date()
        };
        
        this.reviews.push(review);
        return review;
    }
    
    getReviewsByProduct(productId) {
        return this.reviews.filter(review => review.productId === productId);
    }
    
    calculateAverageRating(productId) {
        const productReviews = this.getReviewsByProduct(productId);
        if (productReviews.length === 0) return 0;
        
        const total = productReviews.reduce((sum, review) => sum + review.rating, 0);
        return total / productReviews.length;
    }
}

module.exports = ReviewSystem;
EOF

# Aggiungiamo validazione per le recensioni
cat > src/utils/ReviewValidator.js << 'EOF'
class ReviewValidator {
    static validateRating(rating) {
        return rating >= 1 && rating <= 5 && Number.isInteger(rating);
    }
    
    static validateComment(comment) {
        return comment && comment.length >= 10 && comment.length <= 500;
    }
    
    static validateProductId(productId) {
        return productId && typeof productId === 'string';
    }
}

module.exports = ReviewValidator;
EOF

# Staging separato per review system
git add src/components/ReviewSystem.js
git commit -m "feat: add basic review system

- Implement ReviewSystem class with CRUD operations
- Add review data structure with metadata
- Implement average rating calculation
- Prepare for validation integration"

# Staging separato per validazione
git add src/utils/ReviewValidator.js
git commit -m "feat: add review validation utilities

- Implement rating validation (1-5 stars)
- Add comment length validation (10-500 chars)
- Add product ID validation
- Ready for ReviewSystem integration"
```

## 🔄 Refactoring con Staging Preciso

### Ottimizzazione Performance

```bash
# Mentre sviluppiamo, notiamo opportunità di refactoring
# Creiamo un utility per performance

cat > src/utils/CacheManager.js << 'EOF'
class CacheManager {
    constructor(ttl = 300000) { // 5 minuti default
        this.cache = new Map();
        this.ttl = ttl;
    }
    
    set(key, value) {
        this.cache.set(key, {
            value,
            timestamp: Date.now()
        });
    }
    
    get(key) {
        const item = this.cache.get(key);
        if (!item) return null;
        
        if (Date.now() - item.timestamp > this.ttl) {
            this.cache.delete(key);
            return null;
        }
        
        return item.value;
    }
    
    clear() {
        this.cache.clear();
    }
}

module.exports = CacheManager;
EOF

# Integriamo cache nel sistema di recensioni
cat >> src/components/ReviewSystem.js << 'EOF'

const CacheManager = require('../utils/CacheManager');

// Aggiungiamo cache al ReviewSystem esistente
ReviewSystem.prototype.initCache = function() {
    this.cache = new CacheManager(300000); // 5 minuti
};

ReviewSystem.prototype.getCachedAverageRating = function(productId) {
    if (!this.cache) this.initCache();
    
    const cacheKey = `avg_rating_${productId}`;
    let avgRating = this.cache.get(cacheKey);
    
    if (avgRating === null) {
        avgRating = this.calculateAverageRating(productId);
        this.cache.set(cacheKey, avgRating);
    }
    
    return avgRating;
};
EOF

# Staging attento: prima il cache manager
git add src/utils/CacheManager.js
git commit -m "feat: add cache manager for performance optimization

- Implement TTL-based caching system
- Add automatic cache invalidation
- Memory-efficient Map-based storage
- Configurable cache timeout"

# Poi l'integrazione
git add src/components/ReviewSystem.js
git commit -m "refactor: add caching to review system

- Integrate CacheManager into ReviewSystem
- Cache average rating calculations
- Improve performance for frequently accessed data
- Maintain backward compatibility"
```

## 🎯 Preparazione Release con Staging Strategico

### Consolidamento Pre-Release

```bash
# Creiamo documentazione e configurazione per release
cat > docs/CHANGELOG.md << 'EOF'
# Changelog

## [1.1.0] - 2024-12-XX

### Features
- Payment processing system with validation
- Review and rating system for products
- Performance caching system

### Bug Fixes
- Fixed cart total calculation on item removal

### Performance
- Added caching for review average calculations
- Optimized data access patterns
EOF

# Aggiorniamo configurazione
cat > config/app.js << 'EOF'
module.exports = {
    version: '1.1.0',
    features: {
        payments: true,
        reviews: true,
        caching: true
    },
    cache: {
        ttl: 300000,
        enabled: true
    }
};
EOF

# Test di integrazione
cat > tests/integration.test.js << 'EOF'
const Cart = require('../src/components/Cart');
const PaymentService = require('../src/services/PaymentService');
const ReviewSystem = require('../src/components/ReviewSystem');

describe('Integration Tests', () => {
    test('complete purchase workflow', () => {
        const cart = new Cart();
        cart.addItem({ id: 1, price: 29.99 });
        
        const paymentService = new PaymentService({
            apiKey: 'test',
            endpoint: 'test'
        });
        
        // Test integrazione
        expect(cart.getTotal()).toBe(29.99);
    });
    
    test('review system integration', () => {
        const reviewSystem = new ReviewSystem();
        reviewSystem.addReview('prod1', 'user1', 5, 'Excellent product!');
        
        expect(reviewSystem.calculateAverageRating('prod1')).toBe(5);
    });
});
EOF

# Staging per release: documenti prima
git add docs/CHANGELOG.md config/app.js
git commit -m "docs: prepare release documentation

- Add CHANGELOG with version 1.1.0 features
- Update app configuration for new features
- Document all changes for release notes"

# Poi test di integrazione
git add tests/integration.test.js
git commit -m "test: add integration tests for release

- Add end-to-end purchase workflow test
- Add review system integration test
- Ensure all components work together
- Prepare for release validation"
```

## 📊 Analisi del Workflow Completo

### Visualizzazione della Storia

```bash
# Vediamo la storia completa del progetto
git log --oneline --graph --all

# Analisi dei commit per tipo
git log --oneline | grep -E "(feat|fix|docs|test|refactor)"

# Statistiche delle modifiche
git log --stat --since="1 hour ago"
```

### Pattern di Staging Utilizzati

1. **Commit Atomici**: Ogni funzionalità in commit separati
2. **Staging Separato**: Utilities prima dell'integrazione  
3. **Hotfix Prioritari**: Fix critici con staging immediato
4. **Documentazione Separata**: Docs e test in commit dedicati

## 🔍 Best Practices Dimostrate

### 1. Staging Strategico per Team
```bash
# ✅ BUONO: Commit piccoli e focalizzati
git add src/utils/PaymentValidator.js
git commit -m "feat: add payment validation"

git add src/services/PaymentService.js  
git commit -m "feat: integrate validation in payment service"

# ❌ CATTIVO: Commit troppo grandi
# git add . && git commit -m "add payment system"
```

### 2. Gestione Hotfix con Staging
```bash
# ✅ BUONO: Fix immediato con test
git add src/components/Cart.js tests/cart-hotfix.test.js
git commit -m "hotfix: fix cart calculation with regression test"

# ❌ CATTIVO: Fix senza test o mescolato con altre feature
```

### 3. Preparazione Release
```bash
# ✅ BUONO: Documentazione e test separati
git add docs/CHANGELOG.md
git commit -m "docs: prepare release notes"

git add tests/integration.test.js
git commit -m "test: add integration tests"
```

## 🎯 Risultati del Workflow

Il nostro workflow complesso ha prodotto:
- **8 commit atomici** ben organizzati
- **Separazione chiara** tra feature, fix, docs e test
- **Tracciabilità completa** delle modifiche
- **Storia pulita** e comprensibile
- **Release preparata** professionalmente

## 📚 Takeaway per Progetti Reali

1. **Pianifica i commit** prima di iniziare a codificare
2. **Usa staging selettivo** per commit atomici
3. **Separa sempre** fix critici da sviluppo normale
4. **Documenta mentre sviluppi**, non alla fine
5. **Testa incrementalmente** con ogni commit significativo

## 🔄 Link Correlati

- [01-Staging Selettivo](./01-staging-selettivo.md) - Fondamenti di staging preciso
- [02-Commit Parziali](./02-commit-parziali.md) - Tecniche avanzate di commit
- [03-Correzione Staging](./03-correzione-staging.md) - Gestione errori di staging

---

**Prossimo**: [Esercizi di Consolidamento](../esercizi/01-pratica-staging-base.md) - Metti in pratica i concetti appresi
