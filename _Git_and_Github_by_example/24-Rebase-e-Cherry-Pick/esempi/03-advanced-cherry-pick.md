# Esempio 3: Advanced Cherry-Pick Scenarios - Gestione Selettiva di Commit

## Introduzione

Cherry-pick è uno strumento potente per applicare selettivamente commit specifici da un branch all'altro. Questo esempio esplora scenari avanzati di cherry-pick, inclusa la gestione di conflitti, cherry-pick multipli, e strategie per mantenere la tracciabilità.

## Obiettivi dell'Esempio

- Comprendere quando utilizzare cherry-pick vs merge
- Gestire cherry-pick di commit multipli
- Risolvere conflitti durante cherry-pick
- Utilizzare cherry-pick con range di commit
- Mantenere tracciabilità e metadati
- Implementare workflow di hotfix con cherry-pick

## Scenario: Sistema E-commerce Multi-Branch

### Setup Iniziale del Progetto

```bash
# Crea nuovo repository per l'esempio
mkdir ecommerce-cherrypick-demo
cd ecommerce-cherrypick-demo
git init

# Configura il repository
git config user.name "Cherry Pick Developer"
git config user.email "dev@ecommerce.com"

# Crea struttura base del progetto
mkdir -p {src/{components,utils,api},tests,docs}

# File principale dell'applicazione
cat << 'EOF' > src/app.js
// E-commerce Application - Main Entry Point
class ECommerceApp {
    constructor() {
        this.version = "1.0.0";
        this.initialized = false;
    }

    init() {
        console.log(`E-commerce App v${this.version} initializing...`);
        this.loadComponents();
        this.initialized = true;
    }

    loadComponents() {
        // Load core components
        console.log("Loading core components...");
    }
}

module.exports = ECommerceApp;
EOF

# Sistema di autenticazione
cat << 'EOF' > src/components/auth.js
// Authentication System
class AuthSystem {
    constructor() {
        this.users = new Map();
        this.sessions = new Map();
    }

    register(username, password, email) {
        if (this.users.has(username)) {
            throw new Error("User already exists");
        }
        
        this.users.set(username, {
            password: this.hashPassword(password),
            email: email,
            createdAt: new Date()
        });
        
        return true;
    }

    login(username, password) {
        const user = this.users.get(username);
        if (!user || !this.verifyPassword(password, user.password)) {
            throw new Error("Invalid credentials");
        }
        
        const sessionId = this.generateSessionId();
        this.sessions.set(sessionId, {
            username: username,
            createdAt: new Date()
        });
        
        return sessionId;
    }

    hashPassword(password) {
        // Simplified hash (in real app use bcrypt)
        return Buffer.from(password).toString('base64');
    }

    verifyPassword(password, hash) {
        return this.hashPassword(password) === hash;
    }

    generateSessionId() {
        return Math.random().toString(36).substring(2, 15);
    }
}

module.exports = AuthSystem;
EOF

# Sistema di pagamento
cat << 'EOF' > src/components/payment.js
// Payment Processing System
class PaymentSystem {
    constructor() {
        this.providers = ['stripe', 'paypal', 'square'];
        this.transactions = new Map();
    }

    processPayment(amount, currency, method, cardDetails) {
        if (amount <= 0) {
            throw new Error("Invalid amount");
        }

        if (!this.providers.includes(method)) {
            throw new Error("Unsupported payment method");
        }

        const transactionId = this.generateTransactionId();
        
        // Simulate payment processing
        const transaction = {
            id: transactionId,
            amount: amount,
            currency: currency,
            method: method,
            status: 'pending',
            createdAt: new Date()
        };

        this.transactions.set(transactionId, transaction);
        
        // Simulate async payment processing
        setTimeout(() => {
            transaction.status = 'completed';
            transaction.completedAt = new Date();
        }, 1000);

        return transactionId;
    }

    getTransactionStatus(transactionId) {
        const transaction = this.transactions.get(transactionId);
        return transaction ? transaction.status : 'not_found';
    }

    generateTransactionId() {
        return 'txn_' + Date.now() + '_' + Math.random().toString(36).substring(2, 8);
    }
}

module.exports = PaymentSystem;
EOF

# Test base
cat << 'EOF' > tests/auth.test.js
// Authentication Tests
const AuthSystem = require('../src/components/auth');

describe('AuthSystem', () => {
    let auth;

    beforeEach(() => {
        auth = new AuthSystem();
    });

    test('should register new user', () => {
        const result = auth.register('testuser', 'password123', 'test@example.com');
        expect(result).toBe(true);
    });

    test('should login with valid credentials', () => {
        auth.register('testuser', 'password123', 'test@example.com');
        const sessionId = auth.login('testuser', 'password123');
        expect(sessionId).toBeDefined();
        expect(typeof sessionId).toBe('string');
    });

    test('should throw error for invalid credentials', () => {
        auth.register('testuser', 'password123', 'test@example.com');
        expect(() => {
            auth.login('testuser', 'wrongpassword');
        }).toThrow('Invalid credentials');
    });
});
EOF

# Commit iniziale
git add .
git commit -m "Initial commit: E-commerce app structure

- Core application framework
- Authentication system with registration/login
- Payment processing system
- Basic test suite"

echo "📦 Repository inizializzato con struttura base e-commerce"
```

### 1. Creazione di Branch per Sviluppo Features

```bash
# Branch per feature autenticazione avanzata
git checkout -b feature/advanced-auth
echo "🔐 Lavorando su autenticazione avanzata..."

# Migliora sistema di autenticazione
cat << 'EOF' > src/components/auth.js
// Enhanced Authentication System
class AuthSystem {
    constructor() {
        this.users = new Map();
        this.sessions = new Map();
        this.failedAttempts = new Map();
        this.maxFailedAttempts = 3;
        this.lockoutDuration = 300000; // 5 minutes
    }

    register(username, password, email) {
        if (this.users.has(username)) {
            throw new Error("User already exists");
        }

        // Password strength validation
        if (!this.validatePasswordStrength(password)) {
            throw new Error("Password does not meet strength requirements");
        }
        
        this.users.set(username, {
            password: this.hashPassword(password),
            email: email,
            createdAt: new Date(),
            isLocked: false,
            lastLogin: null
        });
        
        return true;
    }

    login(username, password) {
        // Check if account is locked
        if (this.isAccountLocked(username)) {
            throw new Error("Account is locked due to multiple failed attempts");
        }

        const user = this.users.get(username);
        if (!user || !this.verifyPassword(password, user.password)) {
            this.recordFailedAttempt(username);
            throw new Error("Invalid credentials");
        }
        
        // Reset failed attempts on successful login
        this.failedAttempts.delete(username);
        user.lastLogin = new Date();
        
        const sessionId = this.generateSessionId();
        this.sessions.set(sessionId, {
            username: username,
            createdAt: new Date(),
            lastActivity: new Date()
        });
        
        return sessionId;
    }

    validatePasswordStrength(password) {
        // At least 8 characters, one uppercase, one lowercase, one number
        const minLength = password.length >= 8;
        const hasUppercase = /[A-Z]/.test(password);
        const hasLowercase = /[a-z]/.test(password);
        const hasNumber = /\d/.test(password);
        
        return minLength && hasUppercase && hasLowercase && hasNumber;
    }

    isAccountLocked(username) {
        const attempts = this.failedAttempts.get(username);
        if (!attempts) return false;
        
        const now = new Date();
        const lockoutEnd = new Date(attempts.lastAttempt.getTime() + this.lockoutDuration);
        
        if (attempts.count >= this.maxFailedAttempts && now < lockoutEnd) {
            return true;
        }
        
        // Reset if lockout period has passed
        if (now >= lockoutEnd) {
            this.failedAttempts.delete(username);
        }
        
        return false;
    }

    recordFailedAttempt(username) {
        const attempts = this.failedAttempts.get(username) || { count: 0, lastAttempt: null };
        attempts.count++;
        attempts.lastAttempt = new Date();
        this.failedAttempts.set(username, attempts);
    }

    validateSession(sessionId) {
        const session = this.sessions.get(sessionId);
        if (!session) return false;
        
        // Check session timeout (1 hour)
        const now = new Date();
        const sessionTimeout = 3600000; // 1 hour
        
        if (now.getTime() - session.lastActivity.getTime() > sessionTimeout) {
            this.sessions.delete(sessionId);
            return false;
        }
        
        // Update last activity
        session.lastActivity = now;
        return true;
    }

    logout(sessionId) {
        return this.sessions.delete(sessionId);
    }

    hashPassword(password) {
        // Simplified hash (in real app use bcrypt)
        return Buffer.from(password).toString('base64');
    }

    verifyPassword(password, hash) {
        return this.hashPassword(password) === hash;
    }

    generateSessionId() {
        return Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);
    }
}

module.exports = AuthSystem;
EOF

git add src/components/auth.js
git commit -m "feat(auth): Add advanced security features

- Account lockout after failed attempts
- Password strength validation
- Session timeout and validation
- Enhanced security logging"

# Aggiungi test per nuove funzionalità
cat << 'EOF' > tests/auth-advanced.test.js
// Advanced Authentication Tests
const AuthSystem = require('../src/components/auth');

describe('Advanced AuthSystem', () => {
    let auth;

    beforeEach(() => {
        auth = new AuthSystem();
    });

    describe('Password Strength Validation', () => {
        test('should reject weak passwords', () => {
            expect(() => {
                auth.register('testuser', 'weak', 'test@example.com');
            }).toThrow('Password does not meet strength requirements');
        });

        test('should accept strong passwords', () => {
            const result = auth.register('testuser', 'StrongPass123', 'test@example.com');
            expect(result).toBe(true);
        });
    });

    describe('Account Lockout', () => {
        beforeEach(() => {
            auth.register('testuser', 'StrongPass123', 'test@example.com');
        });

        test('should lock account after max failed attempts', () => {
            // Simulate failed login attempts
            for (let i = 0; i < 3; i++) {
                try {
                    auth.login('testuser', 'wrongpassword');
                } catch (e) {
                    // Expected to fail
                }
            }

            expect(() => {
                auth.login('testuser', 'StrongPass123');
            }).toThrow('Account is locked');
        });
    });

    describe('Session Management', () => {
        test('should validate active sessions', () => {
            auth.register('testuser', 'StrongPass123', 'test@example.com');
            const sessionId = auth.login('testuser', 'StrongPass123');
            
            expect(auth.validateSession(sessionId)).toBe(true);
        });

        test('should invalidate expired sessions', () => {
            auth.register('testuser', 'StrongPass123', 'test@example.com');
            const sessionId = auth.login('testuser', 'StrongPass123');
            
            // Manually expire session
            const session = auth.sessions.get(sessionId);
            session.lastActivity = new Date(Date.now() - 3700000); // 1 hour + 1 minute ago
            
            expect(auth.validateSession(sessionId)).toBe(false);
        });
    });
});
EOF

git add tests/auth-advanced.test.js
git commit -m "test(auth): Add comprehensive tests for security features

- Password strength validation tests
- Account lockout scenario testing
- Session management validation
- Edge case coverage"

# Branch per feature carrello shopping
git checkout main
git checkout -b feature/shopping-cart

echo "🛒 Sviluppando sistema carrello..."

# Crea sistema carrello
cat << 'EOF' > src/components/cart.js
// Shopping Cart System
class ShoppingCart {
    constructor() {
        this.items = new Map();
        this.discounts = new Map();
        this.taxRate = 0.08; // 8% tax
    }

    addItem(productId, name, price, quantity = 1) {
        if (price <= 0 || quantity <= 0) {
            throw new Error("Invalid price or quantity");
        }

        if (this.items.has(productId)) {
            const existingItem = this.items.get(productId);
            existingItem.quantity += quantity;
        } else {
            this.items.set(productId, {
                name: name,
                price: price,
                quantity: quantity,
                addedAt: new Date()
            });
        }

        return this.getItemCount();
    }

    removeItem(productId, quantity = null) {
        if (!this.items.has(productId)) {
            throw new Error("Item not found in cart");
        }

        const item = this.items.get(productId);
        
        if (quantity === null || quantity >= item.quantity) {
            this.items.delete(productId);
        } else {
            item.quantity -= quantity;
        }

        return this.getItemCount();
    }

    updateQuantity(productId, newQuantity) {
        if (!this.items.has(productId)) {
            throw new Error("Item not found in cart");
        }

        if (newQuantity <= 0) {
            return this.removeItem(productId);
        }

        this.items.get(productId).quantity = newQuantity;
        return this.getItemCount();
    }

    getItems() {
        return Array.from(this.items.entries()).map(([id, item]) => ({
            productId: id,
            ...item
        }));
    }

    getItemCount() {
        return Array.from(this.items.values()).reduce((total, item) => total + item.quantity, 0);
    }

    getSubtotal() {
        return Array.from(this.items.values()).reduce((total, item) => {
            return total + (item.price * item.quantity);
        }, 0);
    }

    applyDiscount(code, percentage) {
        if (percentage <= 0 || percentage > 100) {
            throw new Error("Invalid discount percentage");
        }

        this.discounts.set(code, percentage);
        return this.getTotalWithDiscounts();
    }

    getTotalDiscounts() {
        const subtotal = this.getSubtotal();
        let totalDiscount = 0;

        for (const percentage of this.discounts.values()) {
            totalDiscount += subtotal * (percentage / 100);
        }

        return totalDiscount;
    }

    getTax() {
        const discountedSubtotal = this.getSubtotal() - this.getTotalDiscounts();
        return discountedSubtotal * this.taxRate;
    }

    getTotalWithDiscounts() {
        const subtotal = this.getSubtotal();
        const discounts = this.getTotalDiscounts();
        const tax = this.getTax();
        
        return subtotal - discounts + tax;
    }

    clear() {
        this.items.clear();
        this.discounts.clear();
    }

    toJSON() {
        return {
            items: this.getItems(),
            itemCount: this.getItemCount(),
            subtotal: this.getSubtotal(),
            discounts: Array.from(this.discounts.entries()),
            totalDiscounts: this.getTotalDiscounts(),
            tax: this.getTax(),
            total: this.getTotalWithDiscounts()
        };
    }
}

module.exports = ShoppingCart;
EOF

git add src/components/cart.js
git commit -m "feat(cart): Implement shopping cart system

- Add/remove items with quantity management
- Discount code application
- Tax calculation
- Comprehensive cart operations"

# Test per carrello
cat << 'EOF' > tests/cart.test.js
// Shopping Cart Tests
const ShoppingCart = require('../src/components/cart');

describe('ShoppingCart', () => {
    let cart;

    beforeEach(() => {
        cart = new ShoppingCart();
    });

    describe('Item Management', () => {
        test('should add items to cart', () => {
            const count = cart.addItem('prod1', 'Test Product', 29.99, 2);
            expect(count).toBe(2);
            expect(cart.getSubtotal()).toBe(59.98);
        });

        test('should update existing item quantities', () => {
            cart.addItem('prod1', 'Test Product', 29.99, 1);
            cart.addItem('prod1', 'Test Product', 29.99, 2);
            
            expect(cart.getItemCount()).toBe(3);
            expect(cart.getSubtotal()).toBe(89.97);
        });

        test('should remove items from cart', () => {
            cart.addItem('prod1', 'Test Product', 29.99, 3);
            cart.removeItem('prod1', 1);
            
            expect(cart.getItemCount()).toBe(2);
            expect(cart.getSubtotal()).toBe(59.98);
        });
    });

    describe('Discount System', () => {
        beforeEach(() => {
            cart.addItem('prod1', 'Test Product', 100.00, 1);
        });

        test('should apply discount codes', () => {
            cart.applyDiscount('SAVE10', 10);
            expect(cart.getTotalDiscounts()).toBe(10.00);
        });

        test('should calculate total with discounts and tax', () => {
            cart.applyDiscount('SAVE10', 10);
            const total = cart.getTotalWithDiscounts();
            // 100 - 10 (discount) + 7.2 (8% tax on 90) = 97.2
            expect(total).toBeCloseTo(97.2, 2);
        });
    });
});
EOF

git add tests/cart.test.js
git commit -m "test(cart): Add shopping cart test suite

- Item management testing
- Discount calculation verification
- Tax computation validation"
```

### 2. Cherry-Pick Scenarios Avanzati

```bash
# Torna al main branch
git checkout main

echo "🌟 Scenario 1: Cherry-pick di singoli commit critici"

# Simula una situazione dove serve solo il fix di sicurezza
echo "🔒 Applicando solo il fix di sicurezza da feature/advanced-auth..."

# Lista dei commit nel branch feature
echo "📋 Commit disponibili in feature/advanced-auth:"
git log feature/advanced-auth --oneline --graph

# Cherry-pick del commit specifico per la validazione password
SECURITY_COMMIT=$(git log feature/advanced-auth --oneline --grep="security features" | head -1 | cut -d' ' -f1)
echo "🎯 Cherry-picking commit di sicurezza: $SECURITY_COMMIT"

git cherry-pick $SECURITY_COMMIT

echo "✅ Security features applicate al main branch"

# Verifica lo stato
git log --oneline -5
echo "📊 File modificati nel cherry-pick:"
git show --stat HEAD

echo ""
echo "🌟 Scenario 2: Cherry-pick multipli con range"

# Cherry-pick di una serie di commit dal branch carrello
echo "🛒 Applicando funzionalità carrello complete..."

# Identifica il range di commit
CART_FIRST=$(git log feature/shopping-cart --oneline | tail -1 | cut -d' ' -f1)
CART_LAST=$(git log feature/shopping-cart --oneline | head -1 | cut -d' ' -f1)

echo "📋 Range di commit da cherry-pick: $CART_FIRST..$CART_LAST"

# Cherry-pick del range
git cherry-pick $CART_FIRST^..$CART_LAST

echo "✅ Shopping cart features applicate"

# Verifica il risultato
echo "📊 Struttura finale del progetto:"
find src tests -name "*.js" | sort
```

### 3. Gestione Conflitti durante Cherry-Pick

```bash
echo "🌟 Scenario 3: Risoluzione conflitti durante cherry-pick"

# Crea situazione di conflitto
git checkout feature/advanced-auth

# Modifica lo stesso file in modo conflittuale
cat << 'EOF' > src/app.js
// E-commerce Application - Main Entry Point (Enhanced)
class ECommerceApp {
    constructor() {
        this.version = "2.0.0";
        this.initialized = false;
        this.securityLevel = "high";
        this.features = new Set(['auth', 'security']);
    }

    init() {
        console.log(`E-commerce App v${this.version} initializing with ${this.securityLevel} security...`);
        this.loadComponents();
        this.initializeSecurity();
        this.initialized = true;
    }

    loadComponents() {
        console.log("Loading enhanced security components...");
        this.loadAuthSystem();
    }

    loadAuthSystem() {
        console.log("Initializing advanced authentication system...");
        // Load enhanced auth with security features
    }

    initializeSecurity() {
        console.log("Setting up security monitoring...");
        // Security initialization
    }
}

module.exports = ECommerceApp;
EOF

git add src/app.js
git commit -m "feat(app): Enhanced security integration

- Upgrade to version 2.0.0
- Add security level configuration
- Integrate advanced auth system
- Add security monitoring"

# Ora torna al main e prova cherry-pick che causerà conflitto
git checkout main

# Modifica lo stesso file in modo diverso
cat << 'EOF' > src/app.js
// E-commerce Application - Main Entry Point (Cart Enhanced)
class ECommerceApp {
    constructor() {
        this.version = "1.5.0";
        this.initialized = false;
        this.cartEnabled = true;
        this.features = new Set(['cart', 'payment']);
    }

    init() {
        console.log(`E-commerce App v${this.version} initializing with cart features...`);
        this.loadComponents();
        this.initializeCart();
        this.initialized = true;
    }

    loadComponents() {
        console.log("Loading cart and payment components...");
        this.loadCartSystem();
    }

    loadCartSystem() {
        console.log("Initializing shopping cart system...");
        // Load cart features
    }

    initializeCart() {
        console.log("Setting up cart persistence...");
        // Cart initialization
    }
}

module.exports = ECommerceApp;
EOF

git add src/app.js
git commit -m "feat(app): Cart system integration

- Upgrade to version 1.5.0
- Add cart functionality
- Integrate payment system
- Add cart persistence"

echo "🔥 Tentativo di cherry-pick che causerà conflitto..."

# Identifica il commit che causa conflitto
CONFLICT_COMMIT=$(git log feature/advanced-auth --oneline --grep="Enhanced security integration" | head -1 | cut -d' ' -f1)

echo "⚠️ Cherry-picking commit che causerà conflitto: $CONFLICT_COMMIT"

# Esegui cherry-pick (questo causerà conflitto)
if ! git cherry-pick $CONFLICT_COMMIT; then
    echo "💥 Conflitto rilevato durante cherry-pick!"
    echo ""
    echo "📋 File in conflitto:"
    git status --porcelain
    
    echo ""
    echo "🔍 Dettagli del conflitto in src/app.js:"
    cat src/app.js
    
    echo ""
    echo "🛠️ Risoluzione manuale del conflitto..."
    
    # Risolvi il conflitto manualmente combinando le features
    cat << 'EOF' > src/app.js
// E-commerce Application - Main Entry Point (Full Featured)
class ECommerceApp {
    constructor() {
        this.version = "2.1.0";
        this.initialized = false;
        this.securityLevel = "high";
        this.cartEnabled = true;
        this.features = new Set(['auth', 'security', 'cart', 'payment']);
    }

    init() {
        console.log(`E-commerce App v${this.version} initializing with full features...`);
        this.loadComponents();
        this.initializeSecurity();
        this.initializeCart();
        this.initialized = true;
    }

    loadComponents() {
        console.log("Loading all enhanced components...");
        this.loadAuthSystem();
        this.loadCartSystem();
    }

    loadAuthSystem() {
        console.log("Initializing advanced authentication system...");
        // Load enhanced auth with security features
    }

    loadCartSystem() {
        console.log("Initializing shopping cart system...");
        // Load cart features
    }

    initializeSecurity() {
        console.log("Setting up security monitoring...");
        // Security initialization
    }

    initializeCart() {
        console.log("Setting up cart persistence...");
        // Cart initialization
    }
}

module.exports = ECommerceApp;
EOF
    
    echo "✅ Conflitto risolto - combinando features sicurezza e carrello"
    
    # Continua il cherry-pick
    git add src/app.js
    git cherry-pick --continue
    
    echo "🎉 Cherry-pick completato con successo dopo risoluzione conflitto"
else
    echo "✅ Cherry-pick completato senza conflitti"
fi
```

### 4. Cherry-Pick con Metadati e Tracciabilità

```bash
echo "🌟 Scenario 4: Cherry-pick avanzato con tracciabilità"

# Crea hotfix branch per dimostrare cherry-pick con tracciabilità
git checkout -b hotfix/security-patch

echo "🚨 Creando patch di sicurezza critica..."

# Critical security fix
cat << 'EOF' > src/utils/security.js
// Security Utilities
class SecurityUtils {
    static sanitizeInput(input) {
        if (typeof input !== 'string') {
            return input;
        }
        
        // Remove potentially dangerous characters
        return input
            .replace(/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi, '')
            .replace(/javascript:/gi, '')
            .replace(/on\w+\s*=/gi, '')
            .trim();
    }

    static validateEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }

    static generateSecureToken(length = 32) {
        const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
        let result = '';
        
        for (let i = 0; i < length; i++) {
            result += chars.charAt(Math.floor(Math.random() * chars.length));
        }
        
        return result;
    }

    static hashSensitiveData(data, salt = '') {
        // In production, use a proper hashing library
        return Buffer.from(data + salt).toString('base64');
    }

    static rateLimitCheck(identifier, maxRequests = 100, windowMs = 3600000) {
        // Simplified rate limiting
        const now = Date.now();
        const key = `rate_limit_${identifier}`;
        
        // In real implementation, use Redis or similar
        const requests = this.requestCounts.get(key) || [];
        const windowStart = now - windowMs;
        
        // Remove old requests
        const recentRequests = requests.filter(time => time > windowStart);
        
        if (recentRequests.length >= maxRequests) {
            return false;
        }
        
        recentRequests.push(now);
        this.requestCounts.set(key, recentRequests);
        
        return true;
    }
}

SecurityUtils.requestCounts = new Map();

module.exports = SecurityUtils;
EOF

mkdir -p src/utils
git add src/utils/security.js
git commit -m "SECURITY: Add critical input sanitization and rate limiting

CVE-2024-XXXX: Prevent XSS attacks through input sanitization
- Add comprehensive input sanitization
- Implement secure token generation  
- Add rate limiting functionality
- Add email validation utilities

This is a critical security patch that should be cherry-picked
to all active branches immediately.

Fixes: #SEC-001
Risk Level: HIGH
Affects: All user input handling"

echo "🔒 Patch di sicurezza creato"

# Torna al main e applica con tracciabilità completa
git checkout main

echo "📋 Applicando patch di sicurezza con tracciabilità completa..."

# Cherry-pick con messaggi dettagliati
SECURITY_PATCH=$(git log hotfix/security-patch --oneline | head -1 | cut -d' ' -f1)

# Cherry-pick con opzioni avanzate
git cherry-pick $SECURITY_PATCH \
    --edit \
    --signoff \
    -m 1 2>/dev/null || true

# Se il comando precedente fallisce per mancanza di merge commit, usa comando semplice
if [ $? -ne 0 ]; then
    git cherry-pick $SECURITY_PATCH
fi

echo "✅ Security patch applicata al main branch"

# Applica anche agli altri branch
echo "🔄 Applicando patch anche agli altri branch..."

git checkout feature/advanced-auth
git cherry-pick $SECURITY_PATCH
echo "✅ Patch applicata a feature/advanced-auth"

git checkout feature/shopping-cart  
git cherry-pick $SECURITY_PATCH
echo "✅ Patch applicata a feature/shopping-cart"

git checkout main

echo ""
echo "📊 Riepilogo Cherry-Pick Operations:"
echo "=================================="

# Mostra dove è stato applicato il patch
for branch in main feature/advanced-auth feature/shopping-cart; do
    echo "Branch: $branch"
    git log $branch --oneline --grep="SECURITY" | head -1
    echo ""
done
```

### 5. Cherry-Pick con Strategia di Merge

```bash
echo "🌟 Scenario 5: Cherry-pick con strategia di merge personalizzata"

# Crea scenario complesso con multiple modifiche
git checkout feature/advanced-auth

# Aggiungi feature che richiede strategia specifica
cat << 'EOF' > src/components/audit.js
// Audit and Logging System
class AuditSystem {
    constructor() {
        this.auditLog = [];
        this.maxLogSize = 10000;
        this.logLevel = 'INFO';
    }

    log(level, action, userId, details = {}) {
        const entry = {
            timestamp: new Date().toISOString(),
            level: level,
            action: action,
            userId: userId,
            details: details,
            sessionId: this.getCurrentSessionId()
        };

        this.auditLog.push(entry);
        
        // Rotate log if too large
        if (this.auditLog.length > this.maxLogSize) {
            this.auditLog = this.auditLog.slice(-this.maxLogSize * 0.8);
        }

        // Console output for development
        if (this.shouldLog(level)) {
            console.log(`[AUDIT ${level}] ${action}:`, entry);
        }
    }

    logSecurityEvent(eventType, userId, details) {
        this.log('SECURITY', eventType, userId, {
            ...details,
            severity: 'HIGH',
            requiresReview: true
        });
    }

    logUserAction(action, userId, details) {
        this.log('INFO', action, userId, details);
    }

    getAuditTrail(userId = null, startDate = null, endDate = null) {
        let filtered = this.auditLog;

        if (userId) {
            filtered = filtered.filter(entry => entry.userId === userId);
        }

        if (startDate) {
            filtered = filtered.filter(entry => new Date(entry.timestamp) >= startDate);
        }

        if (endDate) {
            filtered = filtered.filter(entry => new Date(entry.timestamp) <= endDate);
        }

        return filtered.sort((a, b) => new Date(b.timestamp) - new Date(a.timestamp));
    }

    shouldLog(level) {
        const levels = ['DEBUG', 'INFO', 'WARN', 'ERROR', 'SECURITY'];
        const currentIndex = levels.indexOf(this.logLevel);
        const messageIndex = levels.indexOf(level);
        return messageIndex >= currentIndex;
    }

    getCurrentSessionId() {
        // In real implementation, get from current session
        return 'session_' + Math.random().toString(36).substring(2, 8);
    }

    exportAuditLog(format = 'json') {
        switch (format) {
            case 'json':
                return JSON.stringify(this.auditLog, null, 2);
            case 'csv':
                return this.convertToCSV(this.auditLog);
            default:
                throw new Error('Unsupported export format');
        }
    }

    convertToCSV(data) {
        if (data.length === 0) return '';
        
        const headers = Object.keys(data[0]);
        const csvData = data.map(row => 
            headers.map(header => {
                const value = row[header];
                return typeof value === 'object' ? JSON.stringify(value) : value;
            }).join(',')
        );
        
        return [headers.join(','), ...csvData].join('\n');
    }
}

module.exports = AuditSystem;
EOF

git add src/components/audit.js
git commit -m "feat(audit): Add comprehensive audit and logging system

- Track all user actions and security events
- Configurable log levels and retention
- Audit trail with filtering capabilities
- Export functionality (JSON/CSV)
- Security event highlighting"

# Integra audit system con auth
cat << 'EOF' > src/components/auth.js
// Enhanced Authentication System with Audit Integration
const AuditSystem = require('./audit');

class AuthSystem {
    constructor() {
        this.users = new Map();
        this.sessions = new Map();
        this.failedAttempts = new Map();
        this.maxFailedAttempts = 3;
        this.lockoutDuration = 300000; // 5 minutes
        this.audit = new AuditSystem();
    }

    register(username, password, email) {
        if (this.users.has(username)) {
            this.audit.logSecurityEvent('REGISTRATION_FAILED', username, {
                reason: 'User already exists',
                email: email
            });
            throw new Error("User already exists");
        }

        // Password strength validation
        if (!this.validatePasswordStrength(password)) {
            this.audit.logSecurityEvent('WEAK_PASSWORD_ATTEMPT', username, {
                email: email
            });
            throw new Error("Password does not meet strength requirements");
        }
        
        this.users.set(username, {
            password: this.hashPassword(password),
            email: email,
            createdAt: new Date(),
            isLocked: false,
            lastLogin: null
        });

        this.audit.logUserAction('USER_REGISTERED', username, {
            email: email,
            registrationDate: new Date()
        });
        
        return true;
    }

    login(username, password) {
        // Check if account is locked
        if (this.isAccountLocked(username)) {
            this.audit.logSecurityEvent('LOGIN_BLOCKED', username, {
                reason: 'Account locked due to failed attempts'
            });
            throw new Error("Account is locked due to multiple failed attempts");
        }

        const user = this.users.get(username);
        if (!user || !this.verifyPassword(password, user.password)) {
            this.recordFailedAttempt(username);
            this.audit.logSecurityEvent('LOGIN_FAILED', username, {
                attempts: this.failedAttempts.get(username)?.count || 1
            });
            throw new Error("Invalid credentials");
        }
        
        // Reset failed attempts on successful login
        this.failedAttempts.delete(username);
        user.lastLogin = new Date();
        
        const sessionId = this.generateSessionId();
        this.sessions.set(sessionId, {
            username: username,
            createdAt: new Date(),
            lastActivity: new Date()
        });

        this.audit.logUserAction('LOGIN_SUCCESS', username, {
            sessionId: sessionId,
            loginTime: new Date()
        });
        
        return sessionId;
    }

    logout(sessionId) {
        const session = this.sessions.get(sessionId);
        if (session) {
            this.audit.logUserAction('LOGOUT', session.username, {
                sessionId: sessionId,
                sessionDuration: new Date() - session.createdAt
            });
        }
        
        return this.sessions.delete(sessionId);
    }

    validatePasswordStrength(password) {
        // At least 8 characters, one uppercase, one lowercase, one number
        const minLength = password.length >= 8;
        const hasUppercase = /[A-Z]/.test(password);
        const hasLowercase = /[a-z]/.test(password);
        const hasNumber = /\d/.test(password);
        
        return minLength && hasUppercase && hasLowercase && hasNumber;
    }

    isAccountLocked(username) {
        const attempts = this.failedAttempts.get(username);
        if (!attempts) return false;
        
        const now = new Date();
        const lockoutEnd = new Date(attempts.lastAttempt.getTime() + this.lockoutDuration);
        
        if (attempts.count >= this.maxFailedAttempts && now < lockoutEnd) {
            return true;
        }
        
        // Reset if lockout period has passed
        if (now >= lockoutEnd) {
            this.failedAttempts.delete(username);
            this.audit.logSecurityEvent('ACCOUNT_UNLOCKED', username, {
                previousAttempts: attempts.count
            });
        }
        
        return false;
    }

    recordFailedAttempt(username) {
        const attempts = this.failedAttempts.get(username) || { count: 0, lastAttempt: null };
        attempts.count++;
        attempts.lastAttempt = new Date();
        this.failedAttempts.set(username, attempts);

        if (attempts.count >= this.maxFailedAttempts) {
            this.audit.logSecurityEvent('ACCOUNT_LOCKED', username, {
                attempts: attempts.count,
                lockoutUntil: new Date(attempts.lastAttempt.getTime() + this.lockoutDuration)
            });
        }
    }

    validateSession(sessionId) {
        const session = this.sessions.get(sessionId);
        if (!session) return false;
        
        // Check session timeout (1 hour)
        const now = new Date();
        const sessionTimeout = 3600000; // 1 hour
        
        if (now.getTime() - session.lastActivity.getTime() > sessionTimeout) {
            this.audit.logSecurityEvent('SESSION_EXPIRED', session.username, {
                sessionId: sessionId,
                lastActivity: session.lastActivity
            });
            this.sessions.delete(sessionId);
            return false;
        }
        
        // Update last activity
        session.lastActivity = now;
        return true;
    }

    getAuditTrail(userId) {
        return this.audit.getAuditTrail(userId);
    }

    hashPassword(password) {
        // Simplified hash (in real app use bcrypt)
        return Buffer.from(password).toString('base64');
    }

    verifyPassword(password, hash) {
        return this.hashPassword(password) === hash;
    }

    generateSessionId() {
        return Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);
    }
}

module.exports = AuthSystem;
EOF

git add src/components/auth.js
git commit -m "feat(auth): Integrate comprehensive audit logging

- Add audit trail for all authentication events
- Log security events with detailed context
- Track failed login attempts and lockouts
- Monitor session lifecycle events
- Add audit trail export capabilities"

# Ora torna al main per cherry-pick con strategia
git checkout main

echo "🎯 Cherry-pick con strategia di merge theirs per file specifici..."

# Cherry-pick del sistema di audit (dovrebbe andare liscio)
AUDIT_COMMIT=$(git log feature/advanced-auth --oneline --grep="audit and logging" | head -1 | cut -d' ' -f1)

git cherry-pick $AUDIT_COMMIT
echo "✅ Audit system cherry-picked successfully"

# Cherry-pick dell'integrazione (potrebbe avere conflitti)
INTEGRATION_COMMIT=$(git log feature/advanced-auth --oneline --grep="Integrate comprehensive audit" | head -1 | cut -d' ' -f1)

echo "🔄 Cherry-picking audit integration..."

# Per dimostrare strategia di merge, forziamo un conflitto modificando auth.js
cat << 'EOF' > src/components/auth.js
// Simple Auth System (conflicts with advanced version)
class AuthSystem {
    constructor() {
        this.users = new Map();
        this.sessions = new Map();
        this.simpleMode = true;
    }

    register(username, password, email) {
        if (this.users.has(username)) {
            throw new Error("User already exists");
        }
        
        this.users.set(username, {
            password: password, // No hashing in simple mode
            email: email,
            createdAt: new Date()
        });
        
        return true;
    }

    login(username, password) {
        const user = this.users.get(username);
        if (!user || user.password !== password) {
            throw new Error("Invalid credentials");
        }
        
        const sessionId = Math.random().toString(36);
        this.sessions.set(sessionId, {
            username: username,
            createdAt: new Date()
        });
        
        return sessionId;
    }
}

module.exports = AuthSystem;
EOF

git add src/components/auth.js
git commit -m "Temporary: simplified auth for demonstration"

# Ora cherry-pick causerà conflitto
if ! git cherry-pick $INTEGRATION_COMMIT; then
    echo "💥 Conflitto come previsto!"
    
    # Usa strategia theirs per accettare la versione cherry-picked
    git checkout --theirs src/components/auth.js
    git add src/components/auth.js
    git cherry-pick --continue
    
    echo "✅ Conflitto risolto usando strategia 'theirs'"
fi

echo ""
echo "🎉 Cherry-pick completato con strategia di merge avanzata"
```

### 6. Riepilogo e Best Practices

```bash
echo "📋 RIEPILOGO CHERRY-PICK OPERATIONS"
echo "=================================="

echo ""
echo "🌟 Commit applicati tramite cherry-pick:"
git log --oneline --grep="cherry picked" || git log --oneline -10

echo ""
echo "📊 Branch status finale:"
for branch in main feature/advanced-auth feature/shopping-cart hotfix/security-patch; do
    echo ""
    echo "Branch: $branch"
    echo "Commits: $(git rev-list --count $branch)"
    echo "Last commit: $(git log $branch --oneline -1)"
done

echo ""
echo "🏆 BEST PRACTICES DIMOSTRATE:"
echo "============================"
echo "✅ 1. Cherry-pick di commit singoli per fix critici"
echo "✅ 2. Cherry-pick di range per feature complete"  
echo "✅ 3. Risoluzione manuale di conflitti durante cherry-pick"
echo "✅ 4. Cherry-pick con tracciabilità e metadati completi"
echo "✅ 5. Uso di strategie di merge durante cherry-pick"
echo "✅ 6. Applicazione di security patch su multiple branch"
echo "✅ 7. Audit trail per tracking modifiche"

echo ""
echo "⚠️ IMPORTANTE - Quando usare Cherry-Pick:"
echo "- Hotfix critici da applicare a multiple branch"
echo "- Commit specifici senza intero branch"
echo "- Backport di features a versioni precedenti"
echo "- Recovery di commit da branch corrotti"
echo ""
echo "❌ Quando NON usare Cherry-Pick:"
echo "- Per intere feature (usa merge/rebase)"
echo "- Su branch pubblici condivisi"
echo "- Quando la cronologia lineare è importante"
echo "- Per commit che dipendono da altri commit"

echo ""
echo "📚 File dimostrativi creati:"
find . -name "*.js" -not -path "./.git/*" | sort

echo ""
echo "✨ Cherry-pick advanced scenarios demonstration complete!"
