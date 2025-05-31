# Interactive Cleanup - Esempio Pratico

## 📖 Scenario

In questo esempio simulerai una situazione tipica di sviluppo: hai lavorato su una feature per diversi giorni, creando molti commit di lavoro intermedio, commit di debug, correzioni di typo e commit sperimentali. Prima di fare il merge finale, devi pulire la cronologia per renderla professionale e leggibile.

## 🎯 Obiettivi dell'Esempio

- Creare una cronologia "sporca" realistica
- Utilizzare interactive rebase per cleanup
- Applicare tutte le operazioni: squash, fixup, reword, edit, drop
- Trasformare commit caotici in una cronologia professionale
- Implementare workflow di cleanup automatizzato

## 🚀 Setup dell'Ambiente "Sporco"

### 1. Creazione Repository con Cronologia Caotica

```bash
#!/bin/bash
# setup-messy-history.sh

echo "🏗️ Creazione cronologia caotica per Interactive Cleanup Demo"

# Pulizia ambiente precedente
rm -rf interactive-cleanup-demo
mkdir interactive-cleanup-demo && cd interactive-cleanup-demo

# Inizializzazione
git init
git config user.name "Developer"
git config user.email "dev@example.com"

echo "📁 SETUP PROGETTO BASE"
echo "====================="

# Struttura iniziale del progetto e-commerce
mkdir -p {src/{components,utils,services},tests,docs,public/{css,js,images}}

cat > package.json << 'EOF'
{
  "name": "ecommerce-cart-demo",
  "version": "1.0.0",
  "description": "E-commerce shopping cart demonstration",
  "main": "src/index.js",
  "scripts": {
    "test": "jest",
    "start": "node src/index.js",
    "lint": "eslint src/",
    "build": "webpack --mode production"
  },
  "dependencies": {
    "express": "^4.18.0",
    "uuid": "^9.0.0"
  },
  "devDependencies": {
    "jest": "^28.0.0",
    "eslint": "^8.0.0",
    "webpack": "^5.0.0"
  }
}
EOF

cat > src/index.js << 'EOF'
// E-commerce application entry point
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use(express.static('public'));

app.get('/', (req, res) => {
    res.send('E-commerce Cart Demo');
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

cat > README.md << 'EOF'
# E-commerce Shopping Cart

Una dimostrazione di sistema di carrello e-commerce.

## Features
- Gestione prodotti
- Carrello della spesa
- Calcolo prezzi e tasse
- Checkout process

## Utilizzo
npm install
npm start
EOF

git add .
git commit -m "feat: initial e-commerce project setup

- Create basic Express server
- Set up project structure
- Add package.json with dependencies
- Create README with project description"

echo "✅ Commit base creato"

echo ""
echo "👨‍💻 SIMULAZIONE SVILUPPO CAOTICO"
echo "==============================="

# Commit 1: Inizio lavoro su prodotti
cat > src/models/product.js << 'EOF'
// Product model
class Product {
    constructor(id, name, price, category) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.category = category;
        this.inStock = true;
    }
    
    getPrice() {
        return this.price;
    }
}

module.exports = Product;
EOF

mkdir -p src/models
git add .
git commit -m "WIP: start working on product model"

# Commit 2: Debug del prodotto
cat > src/models/product.js << 'EOF'
// Product model
class Product {
    constructor(id, name, price, category) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.category = category;
        this.inStock = true;
        console.log('DEBUG: Product created:', this.name); // Debug log
    }
    
    getPrice() {
        console.log('DEBUG: Getting price for', this.name); // Debug log
        return this.price;
    }
}

module.exports = Product;
EOF

git add .
git commit -m "debug: add console logs to debug product creation"

# Commit 3: Typo fix
cat > src/models/product.js << 'EOF'
// Product model
class Product {
    constructor(id, name, price, category) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.category = category;
        this.inStock = true;
        console.log('DEBUG: Product created:', this.name); // Debug log
    }
    
    getPrice() {
        console.log('DEBUG: Getting price for', this.name); // Debug log
        return this.price;
    }
    
    // Fix typo in method name
    isAvailable() {
        return this.inStock;
    }
}

module.exports = Product;
EOF

git add .
git commit -m "fix typo in method name"

# Commit 4: Esperimento con validazione
cat > src/utils/validation.js << 'EOF'
// Experimental validation utilities
const validateProduct = (product) => {
    console.log('EXPERIMENTAL: Validating product', product.id);
    if (!product.name || product.name.length < 2) {
        throw new Error('Product name too short');
    }
    if (product.price < 0) {
        throw new Error('Price cannot be negative');
    }
    return true;
};

// This is just an experiment, might remove later
const experimentalFeature = () => {
    console.log('This is experimental and will be removed');
};

module.exports = { validateProduct, experimentalFeature };
EOF

git add .
git commit -m "experiment: add validation utils (might remove later)"

# Commit 5: Cart service iniziale
cat > src/services/cartService.js << 'EOF'
// Shopping cart service
const { v4: uuidv4 } = require('uuid');

class CartService {
    constructor() {
        this.carts = new Map();
    }
    
    createCart() {
        const cartId = uuidv4();
        this.carts.set(cartId, {
            id: cartId,
            items: [],
            total: 0
        });
        return cartId;
    }
    
    // TODO: implement add item
    addItem(cartId, productId, quantity) {
        // Implementation coming soon
        console.log('TODO: Add item to cart');
    }
}

module.exports = CartService;
EOF

git add .
git commit -m "WIP: initial cart service structure"

# Commit 6: Implementazione addItem
cat > src/services/cartService.js << 'EOF'
// Shopping cart service
const { v4: uuidv4 } = require('uuid');

class CartService {
    constructor() {
        this.carts = new Map();
    }
    
    createCart() {
        const cartId = uuidv4();
        this.carts.set(cartId, {
            id: cartId,
            items: [],
            total: 0
        });
        return cartId;
    }
    
    addItem(cartId, product, quantity = 1) {
        const cart = this.carts.get(cartId);
        if (!cart) {
            throw new Error('Cart not found');
        }
        
        const existingItem = cart.items.find(item => item.productId === product.id);
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            cart.items.push({
                productId: product.id,
                product: product,
                quantity: quantity,
                price: product.getPrice()
            });
        }
        
        this.updateTotal(cartId);
        return cart;
    }
    
    updateTotal(cartId) {
        const cart = this.carts.get(cartId);
        cart.total = cart.items.reduce((sum, item) => {
            return sum + (item.price * item.quantity);
        }, 0);
    }
}

module.exports = CartService;
EOF

git add .
git commit -m "implement addItem method for cart"

# Commit 7: Fix bug nel calcolo totale
cat > src/services/cartService.js << 'EOF'
// Shopping cart service
const { v4: uuidv4 } = require('uuid');

class CartService {
    constructor() {
        this.carts = new Map();
    }
    
    createCart() {
        const cartId = uuidv4();
        this.carts.set(cartId, {
            id: cartId,
            items: [],
            total: 0
        });
        return cartId;
    }
    
    addItem(cartId, product, quantity = 1) {
        const cart = this.carts.get(cartId);
        if (!cart) {
            throw new Error('Cart not found');
        }
        
        const existingItem = cart.items.find(item => item.productId === product.id);
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            cart.items.push({
                productId: product.id,
                product: product,
                quantity: quantity,
                price: product.getPrice()
            });
        }
        
        this.updateTotal(cartId);
        return cart;
    }
    
    updateTotal(cartId) {
        const cart = this.carts.get(cartId);
        if (cart) {  // Fix: add null check
            cart.total = cart.items.reduce((sum, item) => {
                return sum + (item.price * item.quantity);
            }, 0);
        }
    }
    
    removeItem(cartId, productId) {
        const cart = this.carts.get(cartId);
        if (!cart) return null;
        
        cart.items = cart.items.filter(item => item.productId !== productId);
        this.updateTotal(cartId);
        return cart;
    }
}

module.exports = CartService;
EOF

git add .
git commit -m "fix: add null check in updateTotal and add removeItem"

# Commit 8: Oops, typo nel comment
cat > src/services/cartService.js << 'EOF'
// Shopping cart service
const { v4: uuidv4 } = require('uuid');

class CartService {
    constructor() {
        this.carts = new Map();
    }
    
    createCart() {
        const cartId = uuidv4();
        this.carts.set(cartId, {
            id: cartId,
            items: [],
            total: 0
        });
        return cartId;
    }
    
    addItem(cartId, product, quantity = 1) {
        const cart = this.carts.get(cartId);
        if (!cart) {
            throw new Error('Cart not found');
        }
        
        const existingItem = cart.items.find(item => item.productId === product.id);
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            cart.items.push({
                productId: product.id,
                product: product,
                quantity: quantity,
                price: product.getPrice()
            });
        }
        
        this.updateTotal(cartId);
        return cart;
    }
    
    updateTotal(cartId) {
        const cart = this.carts.get(cartId);
        if (cart) {  // Fixed: add null check
            cart.total = cart.items.reduce((sum, item) => {
                return sum + (item.price * item.quantity);
            }, 0);
        }
    }
    
    removeItem(cartId, productId) {
        const cart = this.carts.get(cartId);
        if (!cart) return null;
        
        cart.items = cart.items.filter(item => item.productId !== productId);
        this.updateTotal(cartId);
        return cart;
    }
}

module.exports = CartService;
EOF

git add .
git commit -m "fix comment typo"

# Commit 9: Test temporaneo
cat > temp-test.js << 'EOF'
// Temporary test file to debug cart service
const CartService = require('./src/services/cartService');
const Product = require('./src/models/product');

const cartService = new CartService();
const cart = cartService.createCart();
const product = new Product(1, 'Test Product', 10.99, 'electronics');

console.log('Testing cart functionality...');
cartService.addItem(cart, product, 2);
console.log('Cart total:', cartService.carts.get(cart).total);

// This file will be removed later
EOF

git add .
git commit -m "temp: add temporary test file for debugging"

# Commit 10: Refactor della validation
cat > src/utils/validation.js << 'EOF'
// Product validation utilities
const validateProduct = (product) => {
    if (!product.name || product.name.length < 2) {
        throw new Error('Product name must be at least 2 characters');
    }
    if (product.price < 0) {
        throw new Error('Price cannot be negative');
    }
    if (!product.category || product.category.trim() === '') {
        throw new Error('Product must have a category');
    }
    return true;
};

const validateCartItem = (product, quantity) => {
    validateProduct(product);
    if (!Number.isInteger(quantity) || quantity <= 0) {
        throw new Error('Quantity must be a positive integer');
    }
    return true;
};

module.exports = { validateProduct, validateCartItem };
EOF

git add .
git commit -m "refactor: improve validation with better error messages"

# Commit 11: Clean up experimental code
rm -f temp-test.js
cat > src/models/product.js << 'EOF'
// Product model
class Product {
    constructor(id, name, price, category) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.category = category;
        this.inStock = true;
    }
    
    getPrice() {
        return this.price;
    }
    
    isAvailable() {
        return this.inStock;
    }
    
    setStock(inStock) {
        this.inStock = inStock;
    }
}

module.exports = Product;
EOF

git add .
git commit -m "cleanup: remove debug logs and temp files"

# Commit 12: Aggiunta test appropriati
cat > tests/product.test.js << 'EOF'
const Product = require('../src/models/product');

describe('Product', () => {
    test('should create a product with correct properties', () => {
        const product = new Product(1, 'Test Product', 9.99, 'electronics');
        
        expect(product.id).toBe(1);
        expect(product.name).toBe('Test Product');
        expect(product.price).toBe(9.99);
        expect(product.category).toBe('electronics');
        expect(product.inStock).toBe(true);
    });
    
    test('should return correct price', () => {
        const product = new Product(1, 'Test Product', 15.50, 'books');
        expect(product.getPrice()).toBe(15.50);
    });
    
    test('should check availability correctly', () => {
        const product = new Product(1, 'Test Product', 9.99, 'electronics');
        expect(product.isAvailable()).toBe(true);
        
        product.setStock(false);
        expect(product.isAvailable()).toBe(false);
    });
});
EOF

git add .
git commit -m "test: add comprehensive product model tests"

# Commit 13: API routes
cat > src/routes/products.js << 'EOF'
// Product API routes
const express = require('express');
const Product = require('../models/product');
const { validateProduct } = require('../utils/validation');

const router = express.Router();

// In-memory storage for demo
const products = new Map();
let nextId = 1;

router.get('/', (req, res) => {
    const productList = Array.from(products.values());
    res.json(productList);
});

router.get('/:id', (req, res) => {
    const product = products.get(parseInt(req.params.id));
    if (!product) {
        return res.status(404).json({ error: 'Product not found' });
    }
    res.json(product);
});

router.post('/', (req, res) => {
    try {
        const { name, price, category } = req.body;
        const product = new Product(nextId++, name, price, category);
        
        validateProduct(product);
        products.set(product.id, product);
        
        res.status(201).json(product);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});

module.exports = router;
EOF

mkdir -p src/routes
git add .
git commit -m "feat: add product API routes with validation"

# Commit 14: Ultimo fix
cat > src/index.js << 'EOF'
// E-commerce application entry point
const express = require('express');
const productRoutes = require('./routes/products');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use(express.static('public'));

// API routes
app.use('/api/products', productRoutes);

app.get('/', (req, res) => {
    res.send('E-commerce Cart Demo');
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

git add .
git commit -m "integrate product routes into main server"

echo ""
echo "✅ Cronologia caotica creata!"
echo "📊 Stato attuale:"
git log --oneline

echo ""
echo "🎯 PROBLEMI DA RISOLVERE:"
echo "- Commit 'WIP' non professionali"
echo "- Commit di debug con console.log"
echo "- Fix di typo separati"
echo "- File temporanei committati"
echo "- Messaggi non descrittivi"
echo "- Commit troppo granulari"
```

### 2. Analisi della Cronologia Problematica

```bash
#!/bin/bash
# analyze-messy-history.sh

echo "🔍 ANALISI CRONOLOGIA PROBLEMATICA"
echo "=================================="

echo "📋 Tutti i commit attuali:"
git log --oneline

echo ""
echo "🚨 PROBLEMI IDENTIFICATI:"

# Trova commit problematici
echo ""
echo "1️⃣ Commit WIP/Temporanei:"
git log --oneline --grep="WIP\|temp\|debug\|experiment" --grep="TODO"

echo ""
echo "2️⃣ Commit di fix minori:"
git log --oneline --grep="fix typo\|fix comment\|oops"

echo ""
echo "3️⃣ Commit troppo piccoli:"
echo "Analisi dimensione commit:"
git log --pretty=format:"%h %s" | while read hash message; do
    files_changed=$(git show --name-only --pretty=format:"" "$hash" | wc -l)
    if [ "$files_changed" -le 1 ]; then
        echo "📁 $hash: $files_changed file - $message"
    fi
done

echo ""
echo "4️⃣ Sequenze di commit correlati:"
echo "Commits che dovrebbero essere raggruppati:"
echo "- Product model development (commits 2-4)"
echo "- Cart service implementation (commits 5-8)"
echo "- Validation refactoring (commits 4, 10)"
echo "- Testing and cleanup (commits 9, 11, 12)"

echo ""
echo "🎯 STRATEGIA DI CLEANUP:"
echo "✅ Squash commit WIP relativi"
echo "✅ Fixup correzioni di typo"
echo "✅ Drop commit sperimentali"
echo "✅ Reword messaggi non chiari"
echo "✅ Edit commit da dividere"
echo "✅ Riorganizzare logicamente"

echo ""
echo "📊 OBIETTIVO FINALE:"
echo "Da 14 commit caotici a ~6 commit professionali:"
echo "1. feat: implement product model with validation"
echo "2. feat: implement shopping cart service"
echo "3. feat: add comprehensive test suite"
echo "4. feat: create product API endpoints"
echo "5. feat: integrate all components"
echo "6. docs: update documentation"
```

## 🔄 Interactive Rebase Step-by-Step

### 3. Preparazione per Interactive Rebase

```bash
#!/bin/bash
# prepare-interactive-rebase.sh

echo "💾 PREPARAZIONE INTERACTIVE REBASE"
echo "=================================="

# Backup obbligatorio
BACKUP_BRANCH="backup-cleanup-$(date +%Y%m%d-%H%M%S)"
git branch "$BACKUP_BRANCH"
echo "✅ Backup creato: $BACKUP_BRANCH"

# Verifica working directory
if ! git diff-index --quiet HEAD --; then
    echo "⚠️ Working directory non pulita"
    git stash push -m "Pre-interactive-rebase stash"
    echo "📦 Modifiche salvate in stash"
fi

echo ""
echo "📊 ANALISI PRE-REBASE:"
echo "Commit da main:"
git rev-list --count HEAD~14..HEAD

echo ""
echo "🎯 PIANO DI AZIONE:"
echo "Comando: git rebase -i HEAD~14"
echo ""
echo "📋 STRATEGIA PER OGNI COMMIT:"

# Analizza ogni commit e suggerisce azione
git log --reverse --pretty=format:"%h %s" HEAD~14..HEAD | nl | while read num hash message; do
    case "$message" in
        *"WIP"*|*"temp"*|*"experiment"*)
            echo "$num. $hash - SQUASH: $message"
            ;;
        *"fix typo"*|*"fix comment"*|*"oops"*)
            echo "$num. $hash - FIXUP: $message"
            ;;
        *"debug"*|*"temporary"*)
            echo "$num. $hash - DROP/EDIT: $message"
            ;;
        *"initial"*|*"feat:"*)
            echo "$num. $hash - PICK: $message"
            ;;
        *)
            echo "$num. $hash - REWORD: $message"
            ;;
    esac
done

echo ""
echo "🚀 PRONTO PER INTERACTIVE REBASE!"
echo "Usa: git rebase -i HEAD~14"
```

### 4. Template per Interactive Rebase

```bash
#!/bin/bash
# create-rebase-template.sh

echo "📝 CREAZIONE TEMPLATE INTERACTIVE REBASE"
echo "========================================"

cat > /tmp/interactive-rebase-plan << 'EOF'
# 🎯 INTERACTIVE REBASE CLEANUP PLAN
# ==================================
#
# OBIETTIVO: Trasformare 14 commit caotici in cronologia professionale
#
# STRATEGIA PER TIPO:
# - pick: Commit ben strutturati da mantenere
# - reword: Commit validi ma con messaggi da migliorare
# - edit: Commit da dividere o modificare sostanzialmente
# - squash: Commit correlati da combinare (mantiene entrambi i messaggi)
# - fixup: Piccole correzioni da incorporare (scarta messaggio)
# - drop: Commit sperimentali da eliminare
#
# PIANO SPECIFICO:
#
pick f123abc feat: initial e-commerce project setup
# ✅ Buon commit iniziale, mantenere
#
squash a456def WIP: start working on product model
squash b789ghi debug: add console logs to debug product creation
fixup c012jkl fix typo in method name
# 🔄 Combinare: sviluppo completo product model
#
drop d345mno experiment: add validation utils (might remove later)
# ❌ Codice sperimentale, rimuovere
#
pick e678pqr WIP: initial cart service structure
edit f901stu implement addItem method for cart
squash g234vwx fix: add null check in updateTotal and add removeItem
fixup h567yz1 fix comment typo
# 🔄 Cart service: edit principale per dividere, squash miglioramenti
#
drop i890abc temp: add temporary test file for debugging
# ❌ File temporaneo, rimuovere
#
reword j123def refactor: improve validation with better error messages
# 📝 Buon commit ma messaggio da migliorare
#
pick k456ghi cleanup: remove debug logs and temp files
pick l789jkl test: add comprehensive product model tests
# ✅ Cleanup e test, mantenere
#
squash m012mno feat: add product API routes with validation
pick n345pqr integrate product routes into main server
# 🔄 API: combinare creazione e integrazione
#
# RISULTATO ATTESO: ~6 commit professionali
EOF

echo "📄 Template creato in /tmp/interactive-rebase-plan"
echo ""
echo "💡 UTILIZZO:"
echo "1. Apri editor con: git rebase -i HEAD~14"
echo "2. Sostituisci contenuto con template personalizzato"
echo "3. Salva e procedi con rebase"

echo ""
echo "🎯 Esempio di trasformazione:"
cat /tmp/interactive-rebase-plan | grep -E "^(pick|squash|fixup|drop|reword|edit)" | head -8
```

### 5. Simulazione Interactive Rebase

Dato che l'interactive rebase richiede interazione manuale, creiamo una simulazione che mostra ogni step:

```bash
#!/bin/bash
# simulate-interactive-rebase.sh

echo "🎬 SIMULAZIONE INTERACTIVE REBASE"
echo "================================="

echo "📝 Step 1: Apertura editor interattivo..."
echo "Contenuto originale dell'editor:"

# Simula il contenuto dell'editor interactive rebase
cat << 'EOF'
pick f1a2b3c feat: initial e-commerce project setup
pick a4b5c6d WIP: start working on product model
pick b7c8d9e debug: add console logs to debug product creation
pick c0d1e2f fix typo in method name
pick d3e4f5g experiment: add validation utils (might remove later)
pick e6f7g8h WIP: initial cart service structure
pick f9g0h1i implement addItem method for cart
pick g2h3i4j fix: add null check in updateTotal and add removeItem
pick h5i6j7k fix comment typo
pick i8j9k0l temp: add temporary test file for debugging
pick j1k2l3m refactor: improve validation with better error messages
pick k4l5m6n cleanup: remove debug logs and temp files
pick l7m8n9o test: add comprehensive product model tests
pick m0n1o2p feat: add product API routes with validation
pick n3o4p5q integrate product routes into main server
EOF

echo ""
echo "📝 Step 2: Modifiche applicate (strategia di cleanup):"

cat << 'EOF'
pick f1a2b3c feat: initial e-commerce project setup

# 🔄 PRODUCT MODEL DEVELOPMENT
pick a4b5c6d WIP: start working on product model
squash b7c8d9e debug: add console logs to debug product creation
fixup c0d1e2f fix typo in method name

# ❌ DROP EXPERIMENTAL CODE
drop d3e4f5g experiment: add validation utils (might remove later)

# 🔄 CART SERVICE IMPLEMENTATION
pick e6f7g8h WIP: initial cart service structure
edit f9g0h1i implement addItem method for cart
squash g2h3i4j fix: add null check in updateTotal and add removeItem
fixup h5i6j7k fix comment typo

# ❌ DROP TEMPORARY FILES
drop i8j9k0l temp: add temporary test file for debugging

# 📝 VALIDATION IMPROVEMENTS
reword j1k2l3m refactor: improve validation with better error messages

# ✅ CLEANUP AND TESTING
pick k4l5m6n cleanup: remove debug logs and temp files
pick l7m8n9o test: add comprehensive product model tests

# 🔄 API INTEGRATION
squash m0n1o2p feat: add product API routes with validation
pick n3o4p5q integrate product routes into main server
EOF

echo ""
echo "⚙️ Step 3: Esecuzione delle operazioni..."

simulate_rebase_operations() {
    echo ""
    echo "🔄 Operazione 1: SQUASH Product Model"
    echo "Combinando:"
    echo "  - WIP: start working on product model"
    echo "  - debug: add console logs to debug product creation"
    echo "  - fix typo in method name"
    echo ""
    echo "💬 Nuovo messaggio combinato:"
    echo "feat: implement Product model with validation"
    echo ""
    echo "- Create Product class with id, name, price, category"
    echo "- Add getPrice() and isAvailable() methods"
    echo "- Implement stock management functionality"
    echo "- Add proper error handling and validation"
    
    echo ""
    echo "❌ Operazione 2: DROP experimental validation"
    echo "Commit rimosso: experiment: add validation utils"
    
    echo ""
    echo "✏️ Operazione 3: EDIT cart service implementation"
    echo "Commit arrestato per modifiche: implement addItem method"
    echo ""
    echo "🛠️ Modifiche durante EDIT:"
    echo "- Separare implementazione addItem da removeItem"
    echo "- Migliorare documentazione metodi"
    echo "- Aggiungere gestione errori robusta"
    
    echo ""
    echo "🔄 Operazione 4: SQUASH cart improvements"
    echo "Combinando fix e miglioramenti cart service"
    
    echo ""
    echo "❌ Operazione 5: DROP temporary test file"
    echo "Commit rimosso: temp: add temporary test file"
    
    echo ""
    echo "📝 Operazione 6: REWORD validation message"
    echo "Da: refactor: improve validation with better error messages"
    echo "A:  feat: implement comprehensive input validation"
    echo ""
    echo "- Add product validation with detailed error messages"
    echo "- Implement cart item validation"
    echo "- Add category and price validation rules"
    
    echo ""
    echo "🔄 Operazione 7: SQUASH API routes"
    echo "Combinando creazione e integrazione API routes"
}

simulate_rebase_operations

echo ""
echo "✅ RISULTATO FINALE:"
echo "Cronologia trasformata da 15 commit a 6 commit professionali"
```

### 6. Verifica e Cleanup Post-Rebase

```bash
#!/bin/bash
# post-rebase-verification.sh

echo "🔍 VERIFICA POST-REBASE"
echo "======================="

echo "📊 CRONOLOGIA FINALE:"
git log --oneline --graph

echo ""
echo "📈 CONFRONTO BEFORE/AFTER:"

BACKUP_BRANCH=$(git branch | grep backup-cleanup | head -1 | xargs)

if [ -n "$BACKUP_BRANCH" ]; then
    echo ""
    echo "📋 PRIMA (backup):"
    git log --oneline "$BACKUP_BRANCH" | wc -l | xargs echo "Numero commit:"
    
    echo ""
    echo "📋 DOPO (corrente):"
    git log --oneline HEAD | wc -l | xargs echo "Numero commit:"
    
    echo ""
    echo "🎯 RIDUZIONE:"
    before=$(git log --oneline "$BACKUP_BRANCH" | wc -l)
    after=$(git log --oneline HEAD | wc -l)
    reduction=$((before - after))
    percentage=$((reduction * 100 / before))
    echo "Ridotti $reduction commit ($percentage% in meno)"
fi

echo ""
echo "📊 ANALISI QUALITÀ MESSAGGI:"
echo "Messaggi professionali:"
git log --pretty=format:"%s" | grep -E "^(feat|fix|docs|test|refactor):" | wc -l

echo ""
echo "🔍 VERIFICA INTEGRITÀ:"

# Verifica che non ci siano problemi
if git fsck --full --quiet; then
    echo "✅ Repository integro"
else
    echo "❌ Problemi di integrità rilevati"
fi

# Verifica file importanti
echo ""
echo "📁 VERIFICA FILE CRITICI:"
critical_files=("src/models/product.js" "src/services/cartService.js" "src/routes/products.js" "tests/product.test.js")

for file in "${critical_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file presente"
    else
        echo "❌ $file mancante"
    fi
done

# Verifica che non ci siano file sperimentali/temporanei
echo ""
echo "🧹 VERIFICA PULIZIA:"
if find . -name "temp-*" -o -name "*debug*" -o -name "experimental*" | grep -q .; then
    echo "⚠️ File temporanei ancora presenti:"
    find . -name "temp-*" -o -name "*debug*" -o -name "experimental*"
else
    echo "✅ Nessun file temporaneo presente"
fi

echo ""
echo "🧪 TEST FUNZIONALITÀ:"
if [ -f "package.json" ] && command -v npm >/dev/null; then
    echo "Esecuzione test..."
    if npm test 2>/dev/null; then
        echo "✅ Test passati"
    else
        echo "⚠️ Test falliti o npm non disponibile"
    fi
fi

echo ""
echo "📝 CRONOLOGIA FINALE DETTAGLIATA:"
git log --pretty=format:"%h %s%n%b" -6
```

## 🎨 Tecniche Avanzate di Cleanup

### 7. Cleanup Automatizzato con Script

```bash
#!/bin/bash
# automated-cleanup.sh

echo "🤖 CLEANUP AUTOMATIZZATO"
echo "======================="

# Funzione per identificare pattern di commit da pulire
identify_cleanup_patterns() {
    echo "🔍 Identificazione pattern di cleanup..."
    
    # Trova commit WIP
    local wip_commits=$(git log --oneline --grep="WIP\|TODO\|temp" --grep="debug" | wc -l)
    echo "📊 Commit WIP/temporanei: $wip_commits"
    
    # Trova fix di typo
    local typo_fixes=$(git log --oneline --grep="typo\|fix comment\|oops" | wc -l)
    echo "📊 Fix di typo: $typo_fixes"
    
    # Trova commit molto piccoli
    local small_commits=0
    git log --pretty=format:"%H" | while read hash; do
        files_changed=$(git show --name-only --pretty=format:"" "$hash" | wc -l)
        if [ "$files_changed" -le 1 ]; then
            ((small_commits++))
        fi
    done
    echo "📊 Commit piccoli (1 file): $small_commits"
}

# Funzione per generare script di rebase automatico
generate_cleanup_script() {
    local commits_to_process=$1
    local output_file="/tmp/auto-rebase-script"
    
    echo "📝 Generazione script automatico..."
    
    git log --reverse --pretty=format:"%H %s" HEAD~"$commits_to_process"..HEAD | \
    while read hash message; do
        case "$message" in
            *"WIP"*|*"start working"*|*"initial"*)
                echo "pick $hash $message"
                ;;
            *"debug"*|*"console.log"*|*"temporary"*)
                echo "squash $hash $message"
                ;;
            *"typo"*|*"fix comment"*|*"oops"*)
                echo "fixup $hash $message"
                ;;
            *"experiment"*|*"temp:"*|*"remove later"*)
                echo "drop $hash $message"
                ;;
            *"refactor"*|*"improve"*)
                echo "reword $hash $message"
                ;;
            *)
                echo "pick $hash $message"
                ;;
        esac
    done > "$output_file"
    
    echo "📄 Script generato: $output_file"
    cat "$output_file"
}

# Funzione per cleanup intelligente
intelligent_cleanup() {
    echo "🧠 Cleanup intelligente..."
    
    # Analisi commit correlati
    echo "🔗 Analisi commit correlati per file:"
    
    # Trova file modificati frequentemente
    git log --name-only --pretty=format:"" | sort | uniq -c | sort -nr | head -5 | \
    while read count file; do
        if [ "$count" -gt 3 ] && [ -n "$file" ]; then
            echo "📁 $file: $count modifiche (candidato per squash)"
            
            # Lista commit che modificano questo file
            echo "   Commit correlati:"
            git log --oneline --follow -- "$file" | head -3
        fi
    done
}

# Funzione per suggerimenti di miglioramento
suggest_improvements() {
    echo ""
    echo "💡 SUGGERIMENTI DI MIGLIORAMENTO:"
    
    # Analizza lunghezza messaggi
    echo "📏 Analisi lunghezza messaggi:"
    git log --pretty=format:"%s" | while read message; do
        length=${#message}
        if [ $length -lt 20 ]; then
            echo "⚠️ Messaggio troppo corto: '$message'"
        elif [ $length -gt 72 ]; then
            echo "⚠️ Messaggio troppo lungo: '${message:0:50}...'"
        fi
    done | head -5
    
    # Verifica convenzioni
    echo ""
    echo "📝 Verifica convenzioni commit:"
    unconventional=$(git log --pretty=format:"%s" | grep -v "^(feat|fix|docs|style|refactor|test|chore):" | head -3)
    if [ -n "$unconventional" ]; then
        echo "⚠️ Messaggi non seguono convenzioni:"
        echo "$unconventional"
    else
        echo "✅ Tutti i messaggi seguono le convenzioni"
    fi
}

# Esecuzione delle funzioni
identify_cleanup_patterns
echo ""

# Chiedi quanti commit processare
read -p "📊 Quanti commit vuoi processare? (default: 10): " commits_count
commits_count=${commits_count:-10}

generate_cleanup_script "$commits_count"
echo ""

intelligent_cleanup
suggest_improvements

echo ""
echo "🎯 NEXT STEPS:"
echo "1. Review dello script generato"
echo "2. Backup: git branch backup-auto-cleanup"
echo "3. Esecuzione: git rebase -i HEAD~$commits_count"
echo "4. Usa lo script come riferimento per le operazioni"
```

### 8. Template per Messaggi di Commit Professionali

```bash
#!/bin/bash
# create-professional-templates.sh

echo "📝 CREAZIONE TEMPLATE MESSAGGI PROFESSIONALI"
echo "==========================================="

# Template per diversi tipi di commit
cat > /tmp/commit-templates << 'EOF'
# 🎯 TEMPLATE MESSAGGI COMMIT PROFESSIONALI
# =======================================

# FORMATO GENERALE:
# <type>(<scope>): <subject>
# 
# <body>
# 
# <footer>

# TIPI:
# feat: nuova funzionalità
# fix: correzione bug
# docs: solo documentazione
# style: formatazione, spazi bianchi
# refactor: refactoring senza cambi funzionali
# test: aggiunta o correzione test
# chore: manutenzione, build, configurazione

# ESEMPI SPECIFICI PER IL NOSTRO PROGETTO:

# 1. PRODUCT MODEL
feat(models): implement Product model with validation

- Add Product class with id, name, price, category properties
- Implement getPrice() and isAvailable() methods
- Add setStock() method for inventory management
- Include comprehensive input validation
- Add proper error handling for invalid data

Closes #123

# 2. CART SERVICE
feat(services): implement shopping cart functionality

- Create CartService class with cart management
- Add addItem() method with quantity handling
- Implement removeItem() and updateTotal() methods
- Include UUID-based cart identification
- Add comprehensive error handling for edge cases

# 3. VALIDATION
feat(utils): implement comprehensive input validation

- Add validateProduct() with detailed error messages
- Create validateCartItem() for cart operations
- Include category and price validation rules
- Add quantity validation for positive integers
- Provide clear, user-friendly error messages

# 4. API ROUTES
feat(api): create product management endpoints

- Add GET /api/products for product listing
- Implement GET /api/products/:id for single product
- Create POST /api/products with validation
- Include proper HTTP status codes
- Add comprehensive error handling and responses

# 5. TESTING
test(models): add comprehensive Product model tests

- Test product creation with valid data
- Verify price calculation accuracy
- Test availability checking functionality
- Add edge case testing for invalid inputs
- Include performance testing for large datasets

# 6. INTEGRATION
feat(server): integrate product API with main server

- Add product routes to Express application
- Configure middleware for JSON parsing
- Implement error handling middleware
- Add API versioning support
- Include proper CORS configuration
EOF

echo "📄 Template creati in /tmp/commit-templates"

# Funzione per trasformare messaggi esistenti
transform_existing_messages() {
    echo ""
    echo "🔄 TRASFORMAZIONE MESSAGGI ESISTENTI:"
    echo "====================================="
    
    # Esempi di trasformazione
    echo "PRIMA → DOPO:"
    echo ""
    echo "WIP: start working on product model"
    echo "↓"
    echo "feat(models): implement Product model foundation"
    echo ""
    echo "debug: add console logs to debug product creation"
    echo "↓"
    echo "[SQUASH] - Add debugging and validation improvements"
    echo ""
    echo "fix typo in method name"
    echo "↓"
    echo "[FIXUP] - Fix method naming and documentation"
    echo ""
    echo "experiment: add validation utils (might remove later)"
    echo "↓"
    echo "[DROP] - Remove experimental code"
    echo ""
    echo "refactor: improve validation with better error messages"
    echo "↓"
    echo "refactor(validation): enhance error messaging system"
}

transform_existing_messages

# Creazione di helper per messaggi
cat > /tmp/commit-message-helper.sh << 'EOF'
#!/bin/bash
# commit-message-helper.sh

echo "💬 HELPER MESSAGGI COMMIT"
echo "======================="

# Analizza staging area e suggerisce messaggio
suggest_commit_message() {
    local staged_files=$(git diff --cached --name-only)
    local file_count=$(echo "$staged_files" | wc -l)
    
    echo "📁 File in staging ($file_count):"
    echo "$staged_files"
    echo ""
    
    # Analizza tipo di modifiche
    if echo "$staged_files" | grep -q "test"; then
        echo "🧪 SUGGERIMENTO: test: add/update tests"
    elif echo "$staged_files" | grep -q "model"; then
        echo "📊 SUGGERIMENTO: feat(models): implement/update model"
    elif echo "$staged_files" | grep -q "service"; then
        echo "⚙️ SUGGERIMENTO: feat(services): implement/update service"
    elif echo "$staged_files" | grep -q "route\|api"; then
        echo "🌐 SUGGERIMENTO: feat(api): add/update API endpoints"
    elif echo "$staged_files" | grep -q "README\|doc"; then
        echo "📚 SUGGERIMENTO: docs: update documentation"
    else
        echo "🔄 SUGGERIMENTO: feat: add new functionality"
    fi
    
    echo ""
    echo "📝 Template suggerito:"
    echo "type(scope): brief description"
    echo ""
    echo "- Detailed explanation of changes"
    echo "- List specific improvements"
    echo "- Mention any breaking changes"
    echo ""
    echo "Closes #issue-number"
}

# Verifica messaggio esistente
check_message_quality() {
    local message="$1"
    local score=0
    
    echo "🔍 ANALISI QUALITÀ MESSAGGIO:"
    echo "Messaggio: '$message'"
    echo ""
    
    # Verifica lunghezza
    local length=${#message}
    if [ $length -ge 20 ] && [ $length -le 72 ]; then
        echo "✅ Lunghezza appropriata ($length caratteri)"
        ((score++))
    else
        echo "⚠️ Lunghezza problematica ($length caratteri)"
    fi
    
    # Verifica formato
    if echo "$message" | grep -q "^(feat|fix|docs|style|refactor|test|chore)"; then
        echo "✅ Segue convenzioni di naming"
        ((score++))
    else
        echo "⚠️ Non segue convenzioni (feat:, fix:, etc.)"
    fi
    
    # Verifica descrittività
    if echo "$message" | grep -qv "fix\|update\|change\|modify"; then
        echo "✅ Descrizione specifica"
        ((score++))
    else
        echo "⚠️ Descrizione troppo generica"
    fi
    
    echo ""
    echo "📊 Punteggio qualità: $score/3"
    if [ $score -eq 3 ]; then
        echo "🏆 Messaggio eccellente!"
    elif [ $score -eq 2 ]; then
        echo "👍 Messaggio buono"
    else
        echo "💡 Messaggio da migliorare"
    fi
}

# Menu interattivo
case "${1:-menu}" in
    "suggest")
        suggest_commit_message
        ;;
    "check")
        check_message_quality "$2"
        ;;
    "menu")
        echo "Utilizzo:"
        echo "  $0 suggest     - Suggerisce messaggio per staging area"
        echo "  $0 check 'msg' - Verifica qualità messaggio"
        ;;
esac
EOF

chmod +x /tmp/commit-message-helper.sh

echo ""
echo "🛠️ Helper creato: /tmp/commit-message-helper.sh"
echo ""
echo "💡 UTILIZZO:"
echo "  - Visualizza template: cat /tmp/commit-templates"
echo "  - Suggerimenti: /tmp/commit-message-helper.sh suggest"
echo "  - Verifica qualità: /tmp/commit-message-helper.sh check 'messaggio'"
```

## 🎯 Risultato Finale e Best Practices

### 9. Confronto Finale

```bash
#!/bin/bash
# final-comparison.sh

echo "🏆 CONFRONTO FINALE: PRIMA VS DOPO"
echo "================================="

BACKUP_BRANCH=$(git branch | grep backup-cleanup | head -1 | xargs)

if [ -n "$BACKUP_BRANCH" ]; then
    echo "📊 METRICHE COMPARATIVE:"
    echo ""
    
    # Numero commit
    before_count=$(git rev-list --count "$BACKUP_BRANCH")
    after_count=$(git rev-list --count HEAD)
    reduction=$((before_count - after_count))
    percentage=$((reduction * 100 / before_count))
    
    echo "📈 RIDUZIONE COMMIT:"
    echo "  Prima: $before_count commit"
    echo "  Dopo:  $after_count commit"
    echo "  Riduzione: $reduction commit ($percentage%)"
    
    echo ""
    echo "📋 CRONOLOGIA PRIMA (caotica):"
    git log --oneline "$BACKUP_BRANCH" | head -10
    
    echo ""
    echo "📋 CRONOLOGIA DOPO (pulita):"
    git log --oneline HEAD | head -10
    
    echo ""
    echo "🎯 MIGLIORAMENTI OTTENUTI:"
    echo "✅ Messaggi commit professionali"
    echo "✅ Commit atomici e logici"
    echo "✅ Cronologia lineare leggibile"
    echo "✅ Rimozione codice sperimentale"
    echo "✅ Consolidamento fix correlati"
    echo "✅ Documentazione migliorata"
    
    echo ""
    echo "📊 ANALISI QUALITÀ MESSAGGI:"
    
    # Messaggi professionali (dopo)
    professional_after=$(git log --pretty=format:"%s" HEAD | grep -E "^(feat|fix|docs|test|refactor|chore):" | wc -l)
    total_after=$(git log --oneline HEAD | wc -l)
    prof_percentage_after=$((professional_after * 100 / total_after))
    
    echo "  Messaggi professionali: $professional_after/$total_after ($prof_percentage_after%)"
    
    # Verifica che non ci siano più commit problematici
    problematic_after=$(git log --pretty=format:"%s" HEAD | grep -iE "(wip|temp|debug|oops|typo)" | wc -l)
    echo "  Commit problematici rimanenti: $problematic_after"
    
else
    echo "❌ Branch di backup non trovato"
fi

echo ""
echo "🎉 INTERACTIVE CLEANUP COMPLETATO!"
echo ""
echo "📚 LESSONS LEARNED:"
echo "1. 📝 Interactive rebase è potente per cleanup cronologia"
echo "2. 🔄 Squash/fixup per combinare commit correlati"
echo "3. ❌ Drop per rimuovere commit sperimentali"
echo "4. ✏️ Reword per migliorare messaggi"
echo "5. ✂️ Edit per dividere commit troppo grandi"
echo "6. 💾 Backup sempre prima di operazioni distruttive"
```

### 10. Checklist Best Practices

```bash
echo "📋 CHECKLIST BEST PRACTICES INTERACTIVE REBASE"
echo "=============================================="

echo ""
echo "✅ PRE-REBASE:"
echo "  ☐ Backup branch creato"
echo "  ☐ Working directory pulita"
echo "  ☐ Piano di cleanup definito"
echo "  ☐ Team notificato (se necessario)"
echo "  ☐ Identificati commit da squash/drop"

echo ""
echo "✅ DURANTE REBASE:"
echo "  ☐ Operazioni logiche (squash commit correlati)"
echo "  ☐ Messaggi migliorati (reword)"
echo "  ☐ Codice sperimentale rimosso (drop)"
echo "  ☐ Fix minori incorporati (fixup)"
echo "  ☐ Commit grandi divisi (edit)"

echo ""
echo "✅ POST-REBASE:"
echo "  ☐ Cronologia verificata"
echo "  ☐ Test funzionali passati"
echo "  ☐ Integrità repository controllata"
echo "  ☐ Messaggi commit professionali"
echo "  ☐ Backup rimosso (quando sicuro)"

echo ""
echo "❌ ERRORI DA EVITARE:"
echo "  ✗ Rebase su branch condivisi"
echo "  ✗ Perdita di commit importanti"
echo "  ✗ Messagi commit poco chiari"
echo "  ✗ Test rotti dopo rebase"
echo "  ✗ Mancanza di backup"

echo ""
echo "💡 QUANDO USARE INTERACTIVE REBASE:"
echo "  ✅ Cleanup pre-merge"
echo "  ✅ Consolidamento sviluppo locale"
echo "  ✅ Rimozione commit sperimentali"
echo "  ✅ Miglioramento messaggi"
echo "  ❌ Mai su branch pubblici"
echo "  ❌ Mai senza backup"

echo ""
echo "🎯 OBIETTIVI RAGGIUNTI:"
echo "✅ Cronologia professionale e leggibile"
echo "✅ Commit atomici significativi"
echo "✅ Rimozione codice temporaneo"
echo "✅ Messaggi conformi agli standard"
echo "✅ Facilità di code review"
echo "✅ Debugging e bisect efficaci"
```

---

## 🔄 Navigazione

**Precedente**: [01 - Simple Rebase](./01-simple-rebase.md)  
**Successivo**: [03 - Cherry-Pick Scenarios](./03-cherry-pick-scenarios.md)  
**Indice**: [README del modulo](../README.md)

## 📝 Takeaways

Questo esempio ha dimostrato:

1. **Trasformazione completa** da cronologia caotica a professionale
2. **Uso avanzato** di tutte le operazioni interactive rebase
3. **Workflow systematico** per cleanup di qualità
4. **Automazione** del processo di analisi e suggerimenti
5. **Template e standard** per messaggi commit professionali
6. **Metriche e verifiche** per assicurare qualità del risultato

L'interactive rebase è essenziale per mantenere cronologie Git pulite e professionali, specialmente in ambienti di sviluppo collaborativo.
