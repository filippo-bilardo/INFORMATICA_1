# Esercizio 2: Team Conflict Resolution

## 🎯 Obiettivo
Sviluppare competenze per gestire conflitti in un ambiente di team distribuito, simulando scenari realistici di collaborazione con conflitti multipli e comunicazione asincrona.

## 📋 Scenario

Sei parte di un team di 4 sviluppatori che lavorano simultaneamente su un'applicazione di e-commerce. Ogni membro ha implementato funzionalità diverse che ora devono essere integrate.

## 🚀 Setup Iniziale

### Creazione Repository Team
```bash
mkdir team-conflict-resolution
cd team-conflict-resolution
git init

# Setup progetto base
mkdir -p src/{auth,cart,products,payments} tests docs

# File applicazione principale
cat > src/app.js << 'EOF'
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';

const app = express();
app.use(express.json());

// Base routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);  
app.use('/api/cart', CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`E-commerce API running on port ${PORT}`);
});

export default app;
EOF

# Configurazione base
cat > package.json << 'EOF'
{
  "name": "ecommerce-api",
  "version": "1.0.0",
  "type": "module",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0"
  }
}
EOF

git add .
git commit -m "Initial e-commerce API setup"
```

## 👥 Simulazione Team Members

### Developer 1: Authentication Feature
```bash
git checkout -b feature/auth-system

# Implementazione auth controller
cat > src/auth/authController.js << 'EOF'
import express from 'express';
import jwt from 'jsonwebtoken';
import bcrypt from 'bcrypt';

const router = express.Router();
const users = new Map(); // Simulated database

router.post('/register', async (req, res) => {
    const { email, password, name } = req.body;
    
    if (users.has(email)) {
        return res.status(400).json({ error: 'User already exists' });
    }
    
    const hashedPassword = await bcrypt.hash(password, 10);
    const user = {
        id: Date.now().toString(),
        email,
        name,
        password: hashedPassword,
        createdAt: new Date()
    };
    
    users.set(email, user);
    
    const token = jwt.sign({ userId: user.id }, 'secret-key', { expiresIn: '1h' });
    res.status(201).json({ 
        message: 'User registered successfully',
        token,
        user: { id: user.id, email: user.email, name: user.name }
    });
});

router.post('/login', async (req, res) => {
    const { email, password } = req.body;
    const user = users.get(email);
    
    if (!user || !await bcrypt.compare(password, user.password)) {
        return res.status(401).json({ error: 'Invalid credentials' });
    }
    
    const token = jwt.sign({ userId: user.id }, 'secret-key', { expiresIn: '1h' });
    res.json({ 
        message: 'Login successful',
        token,
        user: { id: user.id, email: user.email, name: user.name }
    });
});

export { router as AuthController };
EOF

# Aggiornamento app.js per auth
cat > src/app.js << 'EOF'
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { authMiddleware } from './auth/middleware.js';

const app = express();
app.use(express.json());

// Auth routes (public)
app.use('/api/auth', AuthController);

// Protected routes
app.use('/api/products', authMiddleware, ProductController);  
app.use('/api/cart', authMiddleware, CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Secure E-commerce API running on port ${PORT}`);
});

export default app;
EOF

# Middleware auth
cat > src/auth/middleware.js << 'EOF'
import jwt from 'jsonwebtoken';

export const authMiddleware = (req, res, next) => {
    const authHeader = req.headers.authorization;
    
    if (!authHeader || !authHeader.startsWith('Bearer ')) {
        return res.status(401).json({ error: 'Access token required' });
    }
    
    const token = authHeader.substring(7);
    
    try {
        const decoded = jwt.verify(token, 'secret-key');
        req.userId = decoded.userId;
        next();
    } catch (error) {
        res.status(401).json({ error: 'Invalid or expired token' });
    }
};
EOF

# Aggiornamento dipendenze
cat > package.json << 'EOF'
{
  "name": "ecommerce-api",
  "version": "1.0.0",
  "type": "module",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.0"
  }
}
EOF

git add .
git commit -m "feat(auth): implement JWT authentication system with registration and login"
```

### Developer 2: Product Management
```bash
git checkout main
git checkout -b feature/product-catalog

# Product controller
cat > src/products/productController.js << 'EOF'
import express from 'express';

const router = express.Router();
const products = new Map([
    ['1', { id: '1', name: 'Laptop Pro', price: 1299.99, category: 'Electronics', stock: 50 }],
    ['2', { id: '2', name: 'Smartphone X', price: 899.99, category: 'Electronics', stock: 30 }],
    ['3', { id: '3', name: 'Coffee Maker', price: 159.99, category: 'Kitchen', stock: 25 }]
]);

router.get('/', (req, res) => {
    const { category, search } = req.query;
    let filteredProducts = Array.from(products.values());
    
    if (category) {
        filteredProducts = filteredProducts.filter(p => p.category.toLowerCase() === category.toLowerCase());
    }
    
    if (search) {
        filteredProducts = filteredProducts.filter(p => 
            p.name.toLowerCase().includes(search.toLowerCase())
        );
    }
    
    res.json({
        products: filteredProducts,
        total: filteredProducts.length
    });
});

router.get('/:id', (req, res) => {
    const product = products.get(req.params.id);
    if (!product) {
        return res.status(404).json({ error: 'Product not found' });
    }
    res.json(product);
});

router.post('/', (req, res) => {
    const { name, price, category, stock } = req.body;
    const id = (products.size + 1).toString();
    
    const product = { id, name, price, category, stock };
    products.set(id, product);
    
    res.status(201).json({
        message: 'Product created successfully',
        product
    });
});

export { router as ProductController };
EOF

# Aggiornamento app.js per products
cat > src/app.js << 'EOF'
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { ProductService } from './products/productService.js';

const app = express();
app.use(express.json());

// Initialize services
const productService = new ProductService();

// Public routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);

// Protected routes
app.use('/api/cart', CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`E-commerce API with Product Catalog running on port ${PORT}`);
});

export default app;
EOF

# Product service
cat > src/products/productService.js << 'EOF'
export class ProductService {
    constructor() {
        this.products = new Map();
        this.categories = new Set();
        this.initializeData();
    }
    
    initializeData() {
        const sampleProducts = [
            { id: '1', name: 'Laptop Pro', price: 1299.99, category: 'Electronics', stock: 50 },
            { id: '2', name: 'Smartphone X', price: 899.99, category: 'Electronics', stock: 30 },
            { id: '3', name: 'Coffee Maker', price: 159.99, category: 'Kitchen', stock: 25 }
        ];
        
        sampleProducts.forEach(product => {
            this.products.set(product.id, product);
            this.categories.add(product.category);
        });
    }
    
    getAllProducts() {
        return Array.from(this.products.values());
    }
    
    getProductsByCategory(category) {
        return this.getAllProducts().filter(p => p.category === category);
    }
}
EOF

git add .
git commit -m "feat(products): implement product catalog with search and filtering"
```

### Developer 3: Shopping Cart
```bash
git checkout main  
git checkout -b feature/shopping-cart

# Cart controller
cat > src/cart/cartController.js << 'EOF'
import express from 'express';

const router = express.Router();
const carts = new Map(); // userId -> cart

router.get('/', (req, res) => {
    const userId = req.userId;
    const cart = carts.get(userId) || { items: [], total: 0 };
    res.json(cart);
});

router.post('/add', (req, res) => {
    const userId = req.userId;
    const { productId, quantity = 1 } = req.body;
    
    let cart = carts.get(userId) || { items: [], total: 0 };
    
    const existingItem = cart.items.find(item => item.productId === productId);
    
    if (existingItem) {
        existingItem.quantity += quantity;
    } else {
        cart.items.push({
            productId,
            quantity,
            addedAt: new Date()
        });
    }
    
    // Recalculate total (simplified)
    cart.total = cart.items.reduce((sum, item) => sum + (item.quantity * 10), 0);
    
    carts.set(userId, cart);
    
    res.json({
        message: 'Item added to cart',
        cart
    });
});

router.delete('/remove/:productId', (req, res) => {
    const userId = req.userId;
    const { productId } = req.params;
    
    let cart = carts.get(userId);
    if (!cart) {
        return res.status(404).json({ error: 'Cart not found' });
    }
    
    cart.items = cart.items.filter(item => item.productId !== productId);
    cart.total = cart.items.reduce((sum, item) => sum + (item.quantity * 10), 0);
    
    carts.set(userId, cart);
    
    res.json({
        message: 'Item removed from cart',
        cart
    });
});

export { router as CartController };
EOF

# Aggiornamento app.js per cart
cat > src/app.js << 'EOF'
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { CartService } from './cart/cartService.js';
import { OrderController } from './orders/orderController.js';

const app = express();
app.use(express.json());

// Initialize services
const cartService = new CartService();

// Routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);
app.use('/api/cart', CartController);
app.use('/api/orders', OrderController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`E-commerce API with Shopping Cart running on port ${PORT}`);
});

export default app;
EOF

# Cart service
cat > src/cart/cartService.js << 'EOF'
export class CartService {
    constructor() {
        this.carts = new Map();
        this.maxItemsPerCart = 50;
    }
    
    getUserCart(userId) {
        return this.carts.get(userId) || this.createEmptyCart();
    }
    
    createEmptyCart() {
        return {
            items: [],
            total: 0,
            createdAt: new Date(),
            updatedAt: new Date()
        };
    }
    
    addItemToCart(userId, productId, quantity) {
        let cart = this.getUserCart(userId);
        
        if (cart.items.length >= this.maxItemsPerCart) {
            throw new Error('Cart is full');
        }
        
        const existingItem = cart.items.find(item => item.productId === productId);
        
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            cart.items.push({ productId, quantity });
        }
        
        cart.updatedAt = new Date();
        this.carts.set(userId, cart);
        
        return cart;
    }
}
EOF

git add .
git commit -m "feat(cart): implement shopping cart with add/remove functionality"
```

### Developer 4: Payment System
```bash
git checkout main
git checkout -b feature/payment-system

# Payment controller
cat > src/payments/paymentController.js << 'EOF'
import express from 'express';
import { PaymentService } from './paymentService.js';

const router = express.Router();
const paymentService = new PaymentService();

router.post('/process', async (req, res) => {
    try {
        const { amount, paymentMethod, cardDetails } = req.body;
        const userId = req.userId;
        
        const payment = await paymentService.processPayment({
            userId,
            amount,
            paymentMethod,
            cardDetails
        });
        
        res.json({
            message: 'Payment processed successfully',
            paymentId: payment.id,
            status: payment.status
        });
    } catch (error) {
        res.status(400).json({
            error: 'Payment failed',
            details: error.message
        });
    }
});

router.get('/history', (req, res) => {
    const userId = req.userId;
    const payments = paymentService.getUserPayments(userId);
    res.json(payments);
});

export { router as PaymentController };
EOF

# Payment service
cat > src/payments/paymentService.js << 'EOF'
export class PaymentService {
    constructor() {
        this.payments = new Map();
        this.supportedMethods = ['credit_card', 'debit_card', 'paypal'];
    }
    
    async processPayment(paymentData) {
        const { userId, amount, paymentMethod, cardDetails } = paymentData;
        
        if (!this.supportedMethods.includes(paymentMethod)) {
            throw new Error('Unsupported payment method');
        }
        
        if (amount <= 0) {
            throw new Error('Invalid amount');
        }
        
        // Simulate payment processing
        await this.simulatePaymentGateway(paymentMethod, amount);
        
        const payment = {
            id: this.generatePaymentId(),
            userId,
            amount,
            paymentMethod,
            status: 'completed',
            processedAt: new Date()
        };
        
        this.payments.set(payment.id, payment);
        return payment;
    }
    
    async simulatePaymentGateway(method, amount) {
        // Simulate external API call
        await new Promise(resolve => setTimeout(resolve, 100));
        
        if (amount > 10000) {
            throw new Error('Amount exceeds daily limit');
        }
    }
    
    generatePaymentId() {
        return `pay_${Date.now()}_${Math.random().toString(36).substring(2, 8)}`;
    }
    
    getUserPayments(userId) {
        return Array.from(this.payments.values())
            .filter(payment => payment.userId === userId);
    }
}
EOF

# Aggiornamento app.js per payments
cat > src/app.js << 'EOF'
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { PaymentController } from './payments/paymentController.js';
import { PaymentService } from './payments/paymentService.js';
import { OrderService } from './orders/orderService.js';

const app = express();
app.use(express.json());

// Initialize services
const paymentService = new PaymentService();
const orderService = new OrderService(paymentService);

// Routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);
app.use('/api/cart', CartController);
app.use('/api/payments', PaymentController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Full E-commerce API with Payments running on port ${PORT}`);
});

export default app;
EOF

# Dependencies update
cat > package.json << 'EOF'
{
  "name": "ecommerce-api",
  "version": "1.0.0",
  "type": "module",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0",
    "stripe": "^11.0.0",
    "uuid": "^9.0.0"
  }
}
EOF

git add .
git commit -m "feat(payments): implement payment processing with multiple methods"
```

## 🔥 Integrazione e Conflitti

### Merge Chain - Scenari Realistici
```bash
# Torna al main branch
git checkout main

# Merge 1: Auth system (di solito va liscio)
git merge feature/auth-system
# Success

# Merge 2: Products (potenziali conflitti in app.js)
git merge feature/product-catalog
```

**Conflitto 1 - app.js:**
```javascript
<<<<<<< HEAD
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { authMiddleware } from './auth/middleware.js';

const app = express();
app.use(express.json());

// Auth routes (public)
app.use('/api/auth', AuthController);

// Protected routes
app.use('/api/products', authMiddleware, ProductController);  
app.use('/api/cart', authMiddleware, CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Secure E-commerce API running on port ${PORT}`);
});
=======
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { ProductService } from './products/productService.js';

const app = express();
app.use(express.json());

// Initialize services
const productService = new ProductService();

// Public routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);

// Protected routes
app.use('/api/cart', CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`E-commerce API with Product Catalog running on port ${PORT}`);
});
>>>>>>> feature/product-catalog
```

### Risoluzione Strategica Conflitto 1
```javascript
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { authMiddleware } from './auth/middleware.js';
import { ProductService } from './products/productService.js';

const app = express();
app.use(express.json());

// Initialize services
const productService = new ProductService();

// Public routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController); // Products pubblici per browsing

// Protected routes
app.use('/api/cart', authMiddleware, CartController);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Secure E-commerce API with Product Catalog running on port ${PORT}`);
});

export default app;
```

### Continuazione Merge Chain
```bash
git add .
git commit -m "resolve: integrate auth system with product catalog"

# Merge 3: Shopping Cart (conflitti multipli)
git merge feature/shopping-cart
```

**Conflitti Multipli:**
- `app.js` - import e routing
- `package.json` - potenziali dipendenze diverse

### Risoluzione Team

**1. Comunicazione Pre-Merge**
```bash
# Crea issue per coordinamento
git log --oneline feature/shopping-cart ^main
git log --oneline feature/payment-system ^main

# Identifica conflitti potenziali
git merge-tree $(git merge-base main feature/shopping-cart) feature/shopping-cart feature/payment-system
```

**2. Risoluzione Collaborativa**
```javascript
// app.js finale dopo discussione team
import express from 'express';
import { AuthController } from './auth/authController.js';
import { ProductController } from './products/productController.js';
import { CartController } from './cart/cartController.js';
import { PaymentController } from './payments/paymentController.js';
import { authMiddleware } from './auth/middleware.js';
import { ProductService } from './products/productService.js';
import { CartService } from './cart/cartService.js';
import { PaymentService } from './payments/paymentService.js';

const app = express();
app.use(express.json());

// Initialize services
const productService = new ProductService();
const cartService = new CartService();
const paymentService = new PaymentService();

// Public routes
app.use('/api/auth', AuthController);
app.use('/api/products', ProductController);

// Protected routes (require authentication)
app.use('/api/cart', authMiddleware, CartController);
app.use('/api/payments', authMiddleware, PaymentController);

// Health check
app.get('/health', (req, res) => {
    res.json({ 
        status: 'healthy',
        services: ['auth', 'products', 'cart', 'payments'],
        timestamp: new Date()
    });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Complete E-commerce API running on port ${PORT}`);
});

export default app;
```

## 📝 Esercizi Pratici

### Esercizio 1: Conflict Detective
**Obiettivo:** Identificare e documentare tutti i conflitti prima della risoluzione.

```bash
# Analizza ogni merge prima di eseguirlo
git checkout main
git merge --no-commit --no-ff feature/shopping-cart

# Documenta conflitti
echo "# Conflict Analysis Report" > conflict-report.md
echo "## Files in conflict:" >> conflict-report.md
git status --porcelain | grep "^UU" >> conflict-report.md

# Analizza natura dei conflitti
for file in $(git status --porcelain | grep "^UU" | cut -c4-); do
    echo "### Conflict in $file" >> conflict-report.md
    git diff HEAD "$file" >> conflict-report.md
done
```

### Esercizio 2: Resolution Strategy Document
**Obiettivo:** Creare strategia documentata prima della risoluzione.

```markdown
# Merge Resolution Strategy

## Conflicting Features
- Authentication system (security priority)
- Product catalog (public access needed)
- Shopping cart (requires auth)
- Payment system (highest security)

## Resolution Decisions
1. **Authentication**: Required for cart and payments, optional for products
2. **Service Integration**: Initialize all services at startup
3. **Route Protection**: Apply middleware selectively
4. **Error Handling**: Unified error responses

## Implementation Order
1. Resolve imports and service initialization
2. Configure route protection
3. Update error handling
4. Test integration points
```

### Esercizio 3: Integration Testing
**Obiettivo:** Verificare che la risoluzione non rompa funzionalità.

```bash
# Test script post-merge
cat > test-integration.js << 'EOF'
import app from './src/app.js';
import request from 'supertest';

// Test basic routes
async function testIntegration() {
    console.log('Testing integrated API...');
    
    // Test health check
    const health = await request(app).get('/health');
    console.log('Health check:', health.body);
    
    // Test public routes
    const products = await request(app).get('/api/products');
    console.log('Products accessible:', products.status === 200);
    
    // Test protected routes (should fail without auth)
    const cart = await request(app).get('/api/cart');
    console.log('Cart protected:', cart.status === 401);
    
    console.log('Integration tests completed');
}

testIntegration().catch(console.error);
EOF

node test-integration.js
```

## 🏆 Valutazione e Learning Points

### Checklist Risoluzione Team
- [ ] Tutti i file in conflitto identificati
- [ ] Strategia di risoluzione documentata e condivisa
- [ ] Funzionalità di sicurezza preservate
- [ ] Performance non compromesse
- [ ] Test di integrazione superati
- [ ] Documentazione aggiornata

### Metrics di Successo
```bash
# Verifica integrazione completa
npm test
npm run lint
npm run build

# Performance check
curl -w "%{time_total}s\n" http://localhost:3000/health

# Security check
npm audit
```

## 📚 Documentazione Post-Merge

### Team Resolution Log
```markdown
# Merge Resolution Log - E-commerce Integration

## Team Members
- Dev1: Authentication system
- Dev2: Product catalog  
- Dev3: Shopping cart
- Dev4: Payment system

## Conflicts Resolved
1. **app.js imports**: Unified all service imports
2. **Route protection**: Selective middleware application
3. **Service initialization**: Centralized at startup
4. **package.json**: Merged all dependencies

## Decisions Made
- Products remain public for SEO/browsing
- Cart and payments require authentication
- Unified error handling across all endpoints
- Health check endpoint for monitoring

## Follow-up Actions
- [ ] Update API documentation
- [ ] Create integration tests
- [ ] Security review
- [ ] Performance testing
```

## 🎯 Risultato Atteso

Al termine di questo esercizio sarai in grado di:
- Coordinare risoluzione conflitti in team
- Bilanciare priorità funzionali diverse
- Documentare decisioni per trasparenza team
- Testare integrazioni complesse post-merge
- Mantenere comunicazione efficace durante conflitti

---

[⬅️ Esercizio Precedente](./01-simulazione-conflitti.md) | [➡️ Esercizio Successivo](./03-emergency-fixes.md)

[🏠 Torna al README](../README.md)
