# Esercizio 3: Emergency Fixes

## 🚨 Obiettivo
Sviluppare competenze per gestire conflitti durante situazioni di emergenza in produzione, dove il tempo è critico e le decisioni devono essere rapide ma sicure.

## 📋 Scenario Critico

È venerdì sera alle 18:00. Il sito e-commerce è sotto stress per il Black Friday. Tre sviluppatori hanno pushato hotfix simultaneamente per risolvere bug critici diversi, creando conflitti che bloccano il deploy di emergenza.

**Situazione:**
- 🔥 **Bug critico**: Sistema di pagamento fallisce nel 30% dei casi
- 🔥 **Performance issue**: Homepage carica in 15+ secondi  
- 🔥 **Security flaw**: Possibile SQL injection scoperta
- ⏰ **Deadline**: Fix deve essere live entro 30 minuti

## 🚀 Setup Scenario Emergenza

### Repository in Stato Critico
```bash
mkdir emergency-conflict-resolution
cd emergency-conflict-resolution
git init

# Setup applicazione critica
mkdir -p src/{api,frontend,database} config tests

# Applicazione base (versione attualmente in produzione)
cat > src/api/server.js << 'EOF'
import express from 'express';
import { PaymentProcessor } from './payment.js';
import { DatabaseManager } from '../database/manager.js';

const app = express();
app.use(express.json());

const paymentProcessor = new PaymentProcessor();
const dbManager = new DatabaseManager();

// Payment endpoint (BUGGY)
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        
        // BUG: No validation, causes 30% failures
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        
        res.json({ success: true, transactionId: result.id });
    } catch (error) {
        res.status(500).json({ error: 'Payment failed' });
    }
});

// Product search (SLOW)
app.get('/api/products/search', async (req, res) => {
    const { query } = req.query;
    
    // BUG: Inefficient database query causes 15s+ load times
    const products = await dbManager.slowSearchProducts(query);
    
    res.json(products);
});

// User data endpoint (VULNERABLE)  
app.get('/api/user/:id', async (req, res) => {
    const { id } = req.params;
    
    // SECURITY BUG: Direct SQL injection vulnerability
    const user = await dbManager.getUserById(id);
    
    res.json(user);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Production server running on port ${PORT}`);
});

export default app;
EOF

# Payment processor con bug
cat > src/api/payment.js << 'EOF'
export class PaymentProcessor {
    constructor() {
        this.failureRate = 0.3; // 30% failure rate - BUG
    }
    
    async processPayment(amount, cardNumber) {
        // Simulate random failures
        if (Math.random() < this.failureRate) {
            throw new Error('Payment gateway timeout');
        }
        
        return {
            id: `tx_${Date.now()}`,
            amount,
            status: 'completed'
        };
    }
}
EOF

# Database manager con problemi
cat > src/database/manager.js << 'EOF'
export class DatabaseManager {
    constructor() {
        this.users = new Map([
            ['1', { id: '1', name: 'John Doe', email: 'john@example.com' }],
            ['2', { id: '2', name: 'Jane Smith', email: 'jane@example.com' }]
        ]);
        
        this.products = Array.from({length: 10000}, (_, i) => ({
            id: i.toString(),
            name: `Product ${i}`,
            price: Math.random() * 100
        }));
    }
    
    async slowSearchProducts(query) {
        // BUG: Inefficient search - simulates 15s delay
        await new Promise(resolve => setTimeout(resolve, 15000));
        
        return this.products.filter(p => 
            p.name.toLowerCase().includes(query.toLowerCase())
        );
    }
    
    async getUserById(id) {
        // SECURITY BUG: Vulnerable to SQL injection
        // In real scenario: SELECT * FROM users WHERE id = '${id}'
        return this.users.get(id);
    }
}
EOF

# Package.json produzione
cat > package.json << 'EOF'
{
  "name": "ecommerce-production",
  "version": "2.1.0",
  "type": "module",
  "main": "src/api/server.js",
  "dependencies": {
    "express": "^4.18.0"
  }
}
EOF

git add .
git commit -m "production: current live version with critical bugs"
```

## 🔥 Hotfix Branches Simultanei

### Hotfix 1: Payment Bug Fix
```bash
git checkout -b hotfix/payment-stability

# Fix del sistema di pagamento
cat > src/api/payment.js << 'EOF'
export class PaymentProcessor {
    constructor() {
        this.maxRetries = 3;
        this.timeout = 5000;
    }
    
    async processPayment(amount, cardNumber) {
        // Input validation
        if (!amount || amount <= 0) {
            throw new Error('Invalid amount');
        }
        
        if (!cardNumber || cardNumber.length < 13) {
            throw new Error('Invalid card number');
        }
        
        // Retry logic for stability
        for (let attempt = 1; attempt <= this.maxRetries; attempt++) {
            try {
                return await this.attemptPayment(amount, cardNumber);
            } catch (error) {
                if (attempt === this.maxRetries) {
                    throw error;
                }
                
                // Exponential backoff
                await new Promise(resolve => 
                    setTimeout(resolve, Math.pow(2, attempt) * 1000)
                );
            }
        }
    }
    
    async attemptPayment(amount, cardNumber) {
        // Simulate more reliable payment processing
        const random = Math.random();
        
        // Reduced failure rate to 5%
        if (random < 0.05) {
            throw new Error('Payment gateway temporary error');
        }
        
        return {
            id: `tx_${Date.now()}_${Math.random().toString(36).substring(2, 8)}`,
            amount,
            status: 'completed',
            processedAt: new Date()
        };
    }
}
EOF

# Aggiornamento server per migliore error handling
cat > src/api/server.js << 'EOF'
import express from 'express';
import { PaymentProcessor } from './payment.js';
import { DatabaseManager } from '../database/manager.js';

const app = express();
app.use(express.json());

const paymentProcessor = new PaymentProcessor();
const dbManager = new DatabaseManager();

// Payment endpoint - FIXED
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        
        // Enhanced validation and error handling
        if (!userId) {
            return res.status(400).json({ 
                error: 'User ID required',
                code: 'MISSING_USER_ID'
            });
        }
        
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        
        res.json({ 
            success: true, 
            transactionId: result.id,
            processedAt: result.processedAt
        });
    } catch (error) {
        console.error('Payment error:', error.message);
        res.status(400).json({ 
            error: error.message,
            code: 'PAYMENT_FAILED'
        });
    }
});

// Product search (STILL SLOW - not fixed in this hotfix)
app.get('/api/products/search', async (req, res) => {
    const { query } = req.query;
    const products = await dbManager.slowSearchProducts(query);
    res.json(products);
});

// User data endpoint (STILL VULNERABLE - not fixed in this hotfix)
app.get('/api/user/:id', async (req, res) => {
    const { id } = req.params;
    const user = await dbManager.getUserById(id);
    res.json(user);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Production server with payment fixes running on port ${PORT}`);
});

export default app;
EOF

git add .
git commit -m "hotfix(payment): implement retry logic and validation to fix 30% failure rate"
```

### Hotfix 2: Performance Critical Fix
```bash
git checkout main
git checkout -b hotfix/search-performance

# Fix performance nel database manager
cat > src/database/manager.js << 'EOF'
export class DatabaseManager {
    constructor() {
        this.users = new Map([
            ['1', { id: '1', name: 'John Doe', email: 'john@example.com' }],
            ['2', { id: '2', name: 'Jane Smith', email: 'jane@example.com' }]
        ]);
        
        // Pre-indexed products for fast search
        this.products = Array.from({length: 10000}, (_, i) => ({
            id: i.toString(),
            name: `Product ${i}`,
            price: Math.random() * 100
        }));
        
        // Build search index for performance
        this.searchIndex = this.buildSearchIndex();
    }
    
    buildSearchIndex() {
        const index = new Map();
        
        this.products.forEach(product => {
            const words = product.name.toLowerCase().split(' ');
            words.forEach(word => {
                if (!index.has(word)) {
                    index.set(word, []);
                }
                index.get(word).push(product);
            });
        });
        
        return index;
    }
    
    async fastSearchProducts(query) {
        // PERFORMANCE FIX: Use pre-built index for instant search
        if (!query) {
            return this.products.slice(0, 50); // Return first 50 products
        }
        
        const queryWords = query.toLowerCase().split(' ');
        const results = new Set();
        
        queryWords.forEach(word => {
            const matches = this.searchIndex.get(word) || [];
            matches.forEach(product => results.add(product));
        });
        
        return Array.from(results).slice(0, 100); // Limit results
    }
    
    async getUserById(id) {
        // STILL VULNERABLE - not fixed in this hotfix
        return this.users.get(id);
    }
    
    // Legacy method kept for compatibility
    async slowSearchProducts(query) {
        await new Promise(resolve => setTimeout(resolve, 15000));
        return this.products.filter(p => 
            p.name.toLowerCase().includes(query.toLowerCase())
        );
    }
}
EOF

# Aggiornamento server per performance
cat > src/api/server.js << 'EOF'
import express from 'express';
import { PaymentProcessor } from './payment.js';
import { DatabaseManager } from '../database/manager.js';

const app = express();
app.use(express.json());

const paymentProcessor = new PaymentProcessor();
const dbManager = new DatabaseManager();

// Payment endpoint (STILL BUGGY - not fixed in this hotfix)
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        res.json({ success: true, transactionId: result.id });
    } catch (error) {
        res.status(500).json({ error: 'Payment failed' });
    }
});

// Product search - PERFORMANCE FIXED
app.get('/api/products/search', async (req, res) => {
    const startTime = Date.now();
    const { query } = req.query;
    
    // Use fast search instead of slow search
    const products = await dbManager.fastSearchProducts(query);
    
    const duration = Date.now() - startTime;
    console.log(`Search completed in ${duration}ms`);
    
    res.json({
        products,
        searchTime: duration,
        count: products.length
    });
});

// User data endpoint (STILL VULNERABLE - not fixed in this hotfix)
app.get('/api/user/:id', async (req, res) => {
    const { id } = req.params;
    const user = await dbManager.getUserById(id);
    res.json(user);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Production server with search performance fixes running on port ${PORT}`);
});

export default app;
EOF

git add .
git commit -m "hotfix(performance): implement indexed search to reduce load time from 15s to <100ms"
```

### Hotfix 3: Security Critical Fix
```bash
git checkout main
git checkout -b hotfix/security-injection

# Fix sicurezza nel database manager
cat > src/database/manager.js << 'EOF'
import validator from 'validator';

export class DatabaseManager {
    constructor() {
        this.users = new Map([
            ['1', { id: '1', name: 'John Doe', email: 'john@example.com' }],
            ['2', { id: '2', name: 'Jane Smith', email: 'jane@example.com' }]
        ]);
        
        this.products = Array.from({length: 10000}, (_, i) => ({
            id: i.toString(),
            name: `Product ${i}`,
            price: Math.random() * 100
        }));
    }
    
    async slowSearchProducts(query) {
        // STILL SLOW - not fixed in this hotfix
        await new Promise(resolve => setTimeout(resolve, 15000));
        return this.products.filter(p => 
            p.name.toLowerCase().includes(query.toLowerCase())
        );
    }
    
    async getUserById(id) {
        // SECURITY FIX: Input validation and sanitization
        if (!id) {
            throw new Error('User ID is required');
        }
        
        // Sanitize input to prevent injection
        const sanitizedId = validator.escape(id.toString());
        
        // Additional validation
        if (!validator.isAlphanumeric(sanitizedId)) {
            throw new Error('Invalid user ID format');
        }
        
        const user = this.users.get(sanitizedId);
        
        if (!user) {
            throw new Error('User not found');
        }
        
        // Don't expose sensitive data
        const { password, ...safeUserData } = user;
        return safeUserData;
    }
    
    async getUserByIdSecure(id) {
        // Secure method with audit logging
        console.log(`Secure user access attempt for ID: ${id.substring(0, 3)}***`);
        return this.getUserById(id);
    }
}
EOF

# Aggiornamento server per sicurezza
cat > src/api/server.js << 'EOF'
import express from 'express';
import { PaymentProcessor } from './payment.js';
import { DatabaseManager } from '../database/manager.js';

const app = express();
app.use(express.json());

const paymentProcessor = new PaymentProcessor();
const dbManager = new DatabaseManager();

// Payment endpoint (STILL BUGGY - not fixed in this hotfix)
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        res.json({ success: true, transactionId: result.id });
    } catch (error) {
        res.status(500).json({ error: 'Payment failed' });
    }
});

// Product search (STILL SLOW - not fixed in this hotfix)
app.get('/api/products/search', async (req, res) => {
    const { query } = req.query;
    const products = await dbManager.slowSearchProducts(query);
    res.json(products);
});

// User data endpoint - SECURITY FIXED
app.get('/api/user/:id', async (req, res) => {
    try {
        const { id } = req.params;
        
        // Additional security headers
        res.set({
            'X-Content-Type-Options': 'nosniff',
            'X-Frame-Options': 'DENY',
            'X-XSS-Protection': '1; mode=block'
        });
        
        const user = await dbManager.getUserByIdSecure(id);
        res.json(user);
    } catch (error) {
        console.error('Security error in user endpoint:', error.message);
        res.status(400).json({ 
            error: 'Invalid request',
            code: 'INVALID_USER_REQUEST'
        });
    }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Production server with security fixes running on port ${PORT}`);
});

export default app;
EOF

# Aggiornamento dipendenze per sicurezza
cat > package.json << 'EOF'
{
  "name": "ecommerce-production",
  "version": "2.1.1-security",
  "type": "module",
  "main": "src/api/server.js",
  "dependencies": {
    "express": "^4.18.0",
    "validator": "^13.9.0"
  }
}
EOF

git add .
git commit -m "hotfix(security): fix SQL injection vulnerability in user endpoint with input validation"
```

## 🚨 Situazione di Emergency Merge

### Tentativo di Deploy Rapido
```bash
git checkout main

# Tenta merge veloce - FALLISCE con conflitti
git merge hotfix/payment-stability
# Success

git merge hotfix/search-performance
```

**Conflitto Critico in server.js:**
```javascript
<<<<<<< HEAD
// Payment endpoint - FIXED
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        
        // Enhanced validation and error handling
        if (!userId) {
            return res.status(400).json({ 
                error: 'User ID required',
                code: 'MISSING_USER_ID'
            });
        }
        
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        
        res.json({ 
            success: true, 
            transactionId: result.id,
            processedAt: result.processedAt
        });
    } catch (error) {
        console.error('Payment error:', error.message);
        res.status(400).json({ 
            error: error.message,
            code: 'PAYMENT_FAILED'
        });
    }
});

// Product search (STILL SLOW - not fixed in this hotfix)
app.get('/api/products/search', async (req, res) => {
    const { query } = req.query;
    const products = await dbManager.slowSearchProducts(query);
    res.json(products);
});
=======
// Payment endpoint (STILL BUGGY - not fixed in this hotfix)
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        res.json({ success: true, transactionId: result.id });
    } catch (error) {
        res.status(500).json({ error: 'Payment failed' });
    }
});

// Product search - PERFORMANCE FIXED
app.get('/api/products/search', async (req, res) => {
    const startTime = Date.now();
    const { query } = req.query;
    
    // Use fast search instead of slow search
    const products = await dbManager.fastSearchProducts(query);
    
    const duration = Date.now() - startTime;
    console.log(`Search completed in ${duration}ms`);
    
    res.json({
        products,
        searchTime: duration,
        count: products.length
    });
});
>>>>>>> hotfix/search-performance
```

### 🏃‍♂️ Risoluzione Rapida ma Sicura

**Strategia Emergency (5 minuti):**

1. **Priorità critiche**: Payment > Performance > Sicurezza temporaneamente
2. **Risoluzione veloce**: Mantieni TUTTI i fix

```javascript
// Emergency resolution - server.js
import express from 'express';
import { PaymentProcessor } from './payment.js';
import { DatabaseManager } from '../database/manager.js';

const app = express();
app.use(express.json());

const paymentProcessor = new PaymentProcessor();
const dbManager = new DatabaseManager();

// Payment endpoint - FIXED (priorità massima)
app.post('/api/payment', async (req, res) => {
    try {
        const { amount, cardNumber, userId } = req.body;
        
        // Enhanced validation and error handling
        if (!userId) {
            return res.status(400).json({ 
                error: 'User ID required',
                code: 'MISSING_USER_ID'
            });
        }
        
        const result = await paymentProcessor.processPayment(amount, cardNumber);
        
        res.json({ 
            success: true, 
            transactionId: result.id,
            processedAt: result.processedAt
        });
    } catch (error) {
        console.error('Payment error:', error.message);
        res.status(400).json({ 
            error: error.message,
            code: 'PAYMENT_FAILED'
        });
    }
});

// Product search - PERFORMANCE FIXED
app.get('/api/products/search', async (req, res) => {
    const startTime = Date.now();
    const { query } = req.query;
    
    // Use fast search method
    const products = await dbManager.fastSearchProducts(query);
    
    const duration = Date.now() - startTime;
    console.log(`Search completed in ${duration}ms`);
    
    res.json({
        products,
        searchTime: duration,
        count: products.length
    });
});

// User data endpoint (mantenere versione corrente per ora)
app.get('/api/user/:id', async (req, res) => {
    const { id } = req.params;
    const user = await dbManager.getUserById(id);
    res.json(user);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`EMERGENCY DEPLOY: Critical fixes applied - ${new Date()}`);
});

export default app;
```

### Continuazione Emergency Merge
```bash
# Risolvi rapidamente
git add .
git commit -m "emergency: integrate payment and performance fixes"

# Merge security (ultimo)
git merge hotfix/security-injection
```

**Nuovo conflitto in DatabaseManager:**

**Risoluzione Emergency (database/manager.js):**
```javascript
import validator from 'validator';

export class DatabaseManager {
    constructor() {
        this.users = new Map([
            ['1', { id: '1', name: 'John Doe', email: 'john@example.com' }],
            ['2', { id: '2', name: 'Jane Smith', email: 'jane@example.com' }]
        ]);
        
        this.products = Array.from({length: 10000}, (_, i) => ({
            id: i.toString(),
            name: `Product ${i}`,
            price: Math.random() * 100
        }));
        
        // Build search index for performance (KEEP)
        this.searchIndex = this.buildSearchIndex();
    }
    
    buildSearchIndex() {
        const index = new Map();
        this.products.forEach(product => {
            const words = product.name.toLowerCase().split(' ');
            words.forEach(word => {
                if (!index.has(word)) {
                    index.set(word, []);
                }
                index.get(word).push(product);
            });
        });
        return index;
    }
    
    async fastSearchProducts(query) {
        // PERFORMANCE FIX: Keep indexed search
        if (!query) {
            return this.products.slice(0, 50);
        }
        
        const queryWords = query.toLowerCase().split(' ');
        const results = new Set();
        
        queryWords.forEach(word => {
            const matches = this.searchIndex.get(word) || [];
            matches.forEach(product => results.add(product));
        });
        
        return Array.from(results).slice(0, 100);
    }
    
    async getUserById(id) {
        // SECURITY FIX: Keep input validation
        if (!id) {
            throw new Error('User ID is required');
        }
        
        const sanitizedId = validator.escape(id.toString());
        
        if (!validator.isAlphanumeric(sanitizedId)) {
            throw new Error('Invalid user ID format');
        }
        
        const user = this.users.get(sanitizedId);
        
        if (!user) {
            throw new Error('User not found');
        }
        
        const { password, ...safeUserData } = user;
        return safeUserData;
    }
    
    async getUserByIdSecure(id) {
        console.log(`Secure user access attempt for ID: ${id.substring(0, 3)}***`);
        return this.getUserById(id);
    }
    
    // Remove slow method to prevent accidental usage
    async slowSearchProducts(query) {
        console.warn('DEPRECATED: slowSearchProducts called - redirecting to fast version');
        return this.fastSearchProducts(query);
    }
}
```

### Final Emergency Update
```javascript
// server.js - finale con tutti i fix integrati
// User data endpoint - NOW WITH SECURITY FIX
app.get('/api/user/:id', async (req, res) => {
    try {
        const { id } = req.params;
        
        // Security headers
        res.set({
            'X-Content-Type-Options': 'nosniff',
            'X-Frame-Options': 'DENY',
            'X-XSS-Protection': '1; mode=block'
        });
        
        const user = await dbManager.getUserByIdSecure(id);
        res.json(user);
    } catch (error) {
        console.error('Security error in user endpoint:', error.message);
        res.status(400).json({ 
            error: 'Invalid request',
            code: 'INVALID_USER_REQUEST'
        });
    }
});
```

## 🚀 Deploy di Emergenza

### Pre-Deploy Testing (2 minuti)
```bash
# Test critico veloce
node -e "
import app from './src/api/server.js';
console.log('✅ App loads successfully');

import {PaymentProcessor} from './src/api/payment.js';
const pp = new PaymentProcessor();
pp.processPayment(100, '1234567890123456').then(() => 
    console.log('✅ Payment processor works')
).catch(e => console.log('❌ Payment error:', e.message));

import {DatabaseManager} from './src/database/manager.js';
const db = new DatabaseManager();
console.log('✅ Database manager loads');
console.log('✅ Search index built:', db.searchIndex.size > 0);
"
```

### Deploy Commands
```bash
# Final commit
git add .
git commit -m "EMERGENCY DEPLOY: integrate all critical hotfixes

🔥 FIXES APPLIED:
- Payment: 30% failure rate → 5% with retry logic
- Performance: 15s search → <100ms with indexing  
- Security: SQL injection vulnerability patched

⚡ DEPLOYMENT READY - All tests passed"

# Tag for emergency tracking
git tag -a emergency-v2.1.1 -m "Emergency deployment - Black Friday critical fixes"

# Push to production
git push origin main
git push origin emergency-v2.1.1
```

## 📊 Post-Deploy Monitoring

### Metrics Check (5 minuti dopo deploy)
```bash
# Health check script
cat > monitor-emergency.sh << 'EOF'
#!/bin/bash

echo "🚨 EMERGENCY DEPLOY MONITORING"
echo "================================"

# Payment success rate
echo "Testing payment endpoint..."
for i in {1..10}; do
    curl -s -X POST http://localhost:3000/api/payment \
        -H "Content-Type: application/json" \
        -d '{"amount":100,"cardNumber":"1234567890123456","userId":"test"}' \
        | jq '.success' 2>/dev/null || echo "false"
done | grep -c "true"

# Search performance
echo "Testing search performance..."
start_time=$(date +%s%3N)
curl -s "http://localhost:3000/api/products/search?query=Product" >/dev/null
end_time=$(date +%s%3N)
duration=$((end_time - start_time))
echo "Search completed in ${duration}ms"

# Security test
echo "Testing security fix..."
curl -s "http://localhost:3000/api/user/1" | jq '.error' 2>/dev/null || echo "Security working"

echo "✅ Emergency monitoring completed"
EOF

chmod +x monitor-emergency.sh
./monitor-emergency.sh
```

## 🎯 Learning Points - Emergency Resolution

### ✅ Best Practices Seguiti
- **Prioritizzazione critica**: Payment > Performance > Security
- **Risoluzione rapida ma completa**: Tutti i fix integrati
- **Testing minimo ma essenziale**: Verifica funzionalità core
- **Documentazione immediata**: Commit messages chiari
- **Monitoring post-deploy**: Verifica immediata

### 🚨 Emergency Decision Matrix

| Conflitto | Risoluzione Strategy | Tempo | Rischio |
|-----------|---------------------|-------|---------|
| Payment fixes | MANTIENI TUTTO | 30s | Basso |
| Performance vs Security | PERFORMANCE first | 60s | Medio |
| Dependencies | MERGE + test | 30s | Basso |
| Database methods | KEEP ALL methods | 45s | Basso |

### 📋 Post-Emergency Checklist

```markdown
# Emergency Resolution Checklist ✅

## Immediate (0-30 min)
- [x] Critical bugs fixed (payment, performance, security)
- [x] All hotfixes integrated without data loss
- [x] Basic smoke tests passed
- [x] Deploy successful

## Short-term (30-60 min)  
- [ ] Full integration test suite
- [ ] Performance metrics validation
- [ ] Security scan
- [ ] Customer communication

## Follow-up (1-24 hours)
- [ ] Code review dei hotfix
- [ ] Incident report
- [ ] Process improvement plan
- [ ] Team retrospective
```

## 🏆 Risultato Emergency

**Problemi Risolti:**
- ✅ Payment failure rate: 30% → 5%
- ✅ Search performance: 15s → <100ms  
- ✅ Security vulnerability: Patched
- ✅ Deploy time: <30 minuti
- ✅ Zero downtime durante fix

**Skills Sviluppati:**
- Conflict resolution sotto pressione
- Prioritizzazione decisioni critiche
- Integrazione rapida ma sicura
- Testing emergency protocols
- Communication durante crisi

---

[⬅️ Esercizio Precedente](./02-team-conflict-resolution.md) | [🏠 Torna al README](../README.md)
