# 01 - Staging Selettivo: Esempio Pratico

## 📖 Scenario

Stai sviluppando un'applicazione web e-commerce. Durante la giornata hai lavorato su diversi aspetti:
- **Bug fix**: Corretto errore nel calcolo del totale carrello
- **Feature**: Aggiunto sistema di wishlist  
- **Refactoring**: Migliorato naming delle variabili
- **Experiment**: Testato nuovo algoritmo di raccomandazioni (non funziona)

Tutti i cambiamenti sono nello stesso file: `cart-service.js`. Devi creare commit separati e logici.

## 🎯 Obiettivo

Imparare a utilizzare `git add -p` per creare commit atomici e logici anche quando le modifiche sono nello stesso file.

## 🚀 Implementazione Passo-Passo

### Step 1: Setup del Progetto
```bash
# Crea directory di progetto
mkdir ecommerce-staging-demo
cd ecommerce-staging-demo
git init

# Crea struttura base
mkdir src tests docs
touch src/cart-service.js tests/cart.test.js docs/api.md
```

### Step 2: File Iniziale
```bash
# Crea il file cart-service.js con contenuto base
cat > src/cart-service.js << 'EOF'
class CartService {
    constructor() {
        this.cart = [];
        this.total = 0;
    }

    addItem(item) {
        this.cart.push(item);
        this.calculateTotal();
    }

    removeItem(itemId) {
        this.cart = this.cart.filter(item => item.id !== itemId);
        this.calculateTotal();
    }

    calculateTotal() {
        // BUG: Non gestisce correttamente sconti
        this.total = this.cart.reduce((sum, item) => sum + item.price, 0);
    }

    getRecommendations() {
        // TODO: Implement recommendation logic
        return [];
    }
}

module.exports = CartService;
EOF

# Commit iniziale
git add src/cart-service.js
git commit -m "Initial cart service implementation"
```

### Step 3: Modifichiamo il File (Simula Giornata di Lavoro)
```bash
# Sovrascriviamo con versione che contiene tutti i cambiamenti
cat > src/cart-service.js << 'EOF'
class CartService {
    constructor() {
        this.items = [];              // REFACTOR: Renamed from 'cart' to 'items'
        this.totalAmount = 0;         // REFACTOR: Renamed from 'total' to 'totalAmount'
        this.wishlist = [];           // FEATURE: New wishlist functionality
    }

    addItem(product) {                // REFACTOR: Renamed parameter 'item' to 'product'
        this.items.push(product);
        this.calculateTotal();
    }

    removeItem(productId) {           // REFACTOR: Renamed parameter
        this.items = this.items.filter(product => product.id !== productId);
        this.calculateTotal();
    }

    // FEATURE: New wishlist methods
    addToWishlist(product) {
        if (!this.wishlist.find(item => item.id === product.id)) {
            this.wishlist.push(product);
        }
    }

    removeFromWishlist(productId) {
        this.wishlist = this.wishlist.filter(product => product.id !== productId);
    }

    getWishlist() {
        return this.wishlist;
    }

    moveFromWishlistToCart(productId) {
        const product = this.wishlist.find(item => item.id === productId);
        if (product) {
            this.removeFromWishlist(productId);
            this.addItem(product);
        }
    }

    calculateTotal() {
        // BUG FIX: Now properly handles discounts and tax
        this.totalAmount = this.items.reduce((sum, product) => {
            const itemPrice = product.price * (1 - (product.discount || 0));
            return sum + itemPrice;
        }, 0);
        
        // Add tax
        this.totalAmount = this.totalAmount * 1.22; // 22% VAT
    }

    // EXPERIMENT: New recommendation algorithm (doesn't work well)
    getRecommendations() {
        // Complex algorithm that doesn't work as expected
        const categories = this.items.map(item => item.category);
        const uniqueCategories = [...new Set(categories)];
        
        // This algorithm is too simplistic and gives poor results
        return uniqueCategories.map(category => ({
            category: category,
            score: Math.random(), // This is obviously wrong
            items: this.getAllItemsInCategory(category).slice(0, 3)
        }));
    }

    getAllItemsInCategory(category) {
        // Mock implementation - in real app would query database
        return [
            { id: 'mock1', name: 'Mock Item 1', category: category, price: 29.99 },
            { id: 'mock2', name: 'Mock Item 2', category: category, price: 39.99 }
        ];
    }
}

module.exports = CartService;
EOF
```

### Step 4: Analizza le Modifiche
```bash
# Vediamo tutte le modifiche insieme
git diff src/cart-service.js
```

L'output mostrerà tutte le modifiche insieme. Ora dobbiamo separarle logicamente.

### Step 5: Staging Selettivo con Patch Mode

#### Commit 1: Bug Fix del Calcolo Totale
```bash
git add -p src/cart-service.js
```

Quando Git ti mostra le modifiche, dovrai:
1. **Rifiutare** il refactoring (rinominazione variabili)
2. **Rifiutare** la feature wishlist  
3. **Accettare** solo il fix del metodo `calculateTotal()`
4. **Rifiutare** l'algoritmo di raccomandazioni

```bash
# Per ogni hunk, rispondi:
# - 'n' per refactoring
# - 'n' per wishlist features
# - 'y' per calculateTotal() fix
# - 'n' per recommendation algorithm
```

```bash
# Commit del bug fix
git commit -m "Fix cart total calculation

- Handle product discounts correctly
- Add VAT calculation (22%)
- Ensure accurate pricing for checkout

Fixes: #123 - Cart total shows wrong amount"
```

#### Commit 2: Wishlist Feature
```bash
git add -p src/cart-service.js
```

Ora accetta solo le modifiche relative alla wishlist:
- `wishlist = []` nel constructor
- Tutti i metodi wishlist: `addToWishlist`, `removeFromWishlist`, etc.

```bash
git commit -m "Implement wishlist functionality

- Add wishlist property to CartService
- Add/remove items to/from wishlist
- Move items from wishlist to cart
- Prevent duplicate items in wishlist

Features:
- addToWishlist(product)
- removeFromWishlist(productId)  
- getWishlist()
- moveFromWishlistToCart(productId)

Implements: #156 - User wishlist feature"
```

#### Commit 3: Refactoring
```bash
git add -p src/cart-service.js
```

Accetta solo le rinominazioni:
- `cart` → `items`
- `total` → `totalAmount`  
- `item` → `product` nei parametri

```bash
git commit -m "Improve variable naming for clarity

- Rename 'cart' to 'items' for consistency
- Rename 'total' to 'totalAmount' for specificity  
- Rename parameter 'item' to 'product' throughout
- No functional changes, only naming improvements

Improves code readability and consistency."
```

### Step 6: Gestione dell'Esperimento Fallito
```bash
# Vediamo cosa rimane
git status
# modified:   src/cart-service.js

# Vediamo le modifiche rimanenti (dovrebbe essere solo l'algoritmo)
git diff src/cart-service.js
```

Per l'esperimento fallito, abbiamo due opzioni:

#### Opzione A: Scarta l'Esperimento
```bash
# Rimuovi le modifiche dell'algoritmo di raccomandazioni
git checkout -- src/cart-service.js
# L'esperimento viene eliminato
```

#### Opzione B: Commit su Branch Sperimentale
```bash
# Crea branch per esperimenti
git checkout -b experiment/recommendation-algorithm

git add src/cart-service.js
git commit -m "WIP: Experiment with new recommendation algorithm

- Attempt to use category-based recommendations
- Current implementation using random scores
- Algorithm needs significant improvement
- NOT READY FOR PRODUCTION

Notes:
- Poor accuracy with random scoring
- Need to implement proper ML algorithm
- Consider collaborative filtering instead"

# Torna al branch principale
git checkout main
```

### Step 7: Verifica Risultato
```bash
# Verifica cronologia commit
git log --oneline
```

Dovresti vedere:
```
abc1234 Improve variable naming for clarity
def5678 Implement wishlist functionality  
ghi9012 Fix cart total calculation
jkl3456 Initial cart service implementation
```

## 📊 Risultato Finale

### Struttura Commit Ottenuta
```
main branch:
├── Initial implementation
├── Bug fix: cart calculation     ← Hotfixable
├── Feature: wishlist             ← Self-contained
└── Refactor: naming improvements ← Safe to revert

experiment/recommendation-algorithm:
└── WIP: recommendation experiment ← Isolated
```

### Vantaggi di Questo Approccio

1. **Bug Fix Isolato**: Può essere facilmente cherry-picked per hotfix
2. **Feature Completa**: Wishlist è self-contained e testabile
3. **Refactoring Sicuro**: Può essere reverted senza perdere funzionalità
4. **Esperimenti Isolati**: Non inquinano la cronologia principale

## 🔧 Comandi Utili Durante il Processo

### Vedere Staging Area
```bash
git diff --staged              # Cosa è staged ora
git diff                       # Cosa rimane da stagare
git status --short             # Vista compatta
```

### Annullare Scelte Sbagliate
```bash
git reset src/cart-service.js  # Rimuovi tutto dalla staging
git add -p src/cart-service.js # Ricomincia la selezione
```

### Backup Prima di Operazioni Rischiose
```bash
git stash push -m "Backup before staging"  # Salva tutto
# ... fai staging selettivo ...
git stash drop                              # Elimina backup se ok
```

## 💡 Tips Avanzati

### 1. Dividere Hunk Grandi
Se un hunk è troppo grande:
```bash
# Nel patch mode, usa 's' per split
Stage this hunk [y,n,q,a,d,s,e,?]? s
```

### 2. Edit Manuale
Per controllo totale:
```bash
# Nel patch mode, usa 'e' per edit
Stage this hunk [y,n,q,a,d,s,e,?]? e
```

### 3. Visualizzazione Migliorata
```bash
# Diff con più contesto
git diff -U10 src/cart-service.js

# Diff word-level
git diff --word-diff src/cart-service.js
```

## 🧠 Esercizio Pratico

Prova tu stesso:

1. **Crea il setup** seguendo gli step 1-3
2. **Analizza le modifiche** con `git diff`  
3. **Esegui staging selettivo** seguendo gli step 5-6
4. **Verifica il risultato** con `git log --oneline`

### Sfida Extra
Aggiungi anche:
- Test per ogni funzionalità in commit separati
- Documentazione API in doc commit dedicato
- Configurazione linting in commit di setup

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Guide Teoriche](../guide/04-workflow-staging.md)
- [➡️ Prossimo Esempio](./02-gestione-conflitti-staging.md)

---

**Prossimo passo**: [Gestione Conflitti in Staging](./02-gestione-conflitti-staging.md) - Risolvere situazioni complesse
