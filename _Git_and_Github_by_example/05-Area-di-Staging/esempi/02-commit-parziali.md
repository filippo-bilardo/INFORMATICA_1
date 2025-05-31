# Esempio 02: Commit Parziali - Gestire Modifiche Multiple in un File

## 🎯 Scenario del Progetto
Stai sviluppando un'applicazione di e-commerce e hai un file che contiene sia nuove funzionalità che codice di debug temporaneo. Devi committare solo le funzionalità, mantenendo il debug per ulteriori test.

## 📁 Setup del Progetto
```bash
mkdir commit-parziali-esempio
cd commit-parziali-esempio
git init
git config user.name "Dev E-commerce"
git config user.email "dev@ecommerce.com"
```

## 📄 File Iniziale: Sistema Prodotti Base

### Crea il file base
```javascript
// products.js - Sistema di gestione prodotti
class ProductManager {
    constructor() {
        this.products = [];
        this.categories = new Map();
    }
    
    addProduct(product) {
        this.products.push(product);
        return product.id;
    }
    
    getProduct(id) {
        return this.products.find(p => p.id === id);
    }
    
    getAllProducts() {
        return this.products;
    }
}

module.exports = ProductManager;
```

### Commit iniziale
```bash
git add products.js
git commit -m "feat: add basic product management system

- Implement ProductManager class
- Add basic CRUD operations for products
- Setup category mapping structure"
```

## 🔧 Sviluppo con Modifiche Multiple

### Aggiungi funzionalità e debug al file
```javascript
// products.js - Sistema di gestione prodotti con nuove feature + debug
class ProductManager {
    constructor() {
        this.products = [];
        this.categories = new Map();
        // 🐛 DEBUG: Logging per debugging inizializzazione
        console.log('ProductManager initialized at:', new Date());
        this.debugMode = true;
    }
    
    addProduct(product) {
        // ✅ FEATURE: Validazione prodotto
        if (!product || !product.name || !product.price) {
            throw new Error('Prodotto non valido: nome e prezzo sono obbligatori');
        }
        
        // ✅ FEATURE: Auto-generazione ID se mancante
        if (!product.id) {
            product.id = this.generateId();
        }
        
        // 🐛 DEBUG: Log di aggiunta prodotto
        if (this.debugMode) {
            console.log('Adding product:', product);
            console.log('Current products count:', this.products.length);
        }
        
        this.products.push(product);
        
        // ✅ FEATURE: Aggiorna categoria
        if (product.category) {
            this.updateCategoryCount(product.category);
        }
        
        return product.id;
    }
    
    // ✅ FEATURE: Generazione ID univoci
    generateId() {
        return 'prod_' + Date.now() + '_' + Math.random().toString(36).substr(2, 9);
    }
    
    // ✅ FEATURE: Gestione contatori categoria
    updateCategoryCount(category) {
        const currentCount = this.categories.get(category) || 0;
        this.categories.set(category, currentCount + 1);
        
        // 🐛 DEBUG: Log categoria
        if (this.debugMode) {
            console.log(`Category ${category} now has ${currentCount + 1} products`);
        }
    }
    
    getProduct(id) {
        // 🐛 DEBUG: Log ricerca prodotto
        console.log('DEBUG: Searching for product with ID:', id);
        
        const product = this.products.find(p => p.id === id);
        
        // 🐛 DEBUG: Risultato ricerca
        if (this.debugMode) {
            console.log('DEBUG: Found product:', product ? product.name : 'Not found');
        }
        
        return product;
    }
    
    getAllProducts() {
        // 🐛 DEBUG: Performance monitoring
        console.time('getAllProducts');
        
        const products = this.products;
        
        // 🐛 DEBUG: Performance monitoring
        console.timeEnd('getAllProducts');
        console.log('DEBUG: Total products returned:', products.length);
        
        return products;
    }
    
    // ✅ FEATURE: Ricerca per categoria
    getProductsByCategory(category) {
        if (!category) {
            throw new Error('Categoria richiesta per la ricerca');
        }
        
        // 🐛 DEBUG: Log ricerca categoria
        if (this.debugMode) {
            console.log('Searching products in category:', category);
        }
        
        const results = this.products.filter(p => p.category === category);
        
        // 🐛 DEBUG: Risultati ricerca
        console.log(`DEBUG: Found ${results.length} products in category ${category}`);
        
        return results;
    }
    
    // ✅ FEATURE: Calcolo statistiche
    getStatistics() {
        const totalProducts = this.products.length;
        const averagePrice = this.products.reduce((sum, p) => sum + p.price, 0) / totalProducts;
        
        // 🐛 DEBUG: Calcolo statistiche dettagliato
        console.log('DEBUG: Calculating statistics...');
        console.log('DEBUG: Total products:', totalProducts);
        console.log('DEBUG: Sum of prices:', this.products.reduce((sum, p) => sum + p.price, 0));
        console.log('DEBUG: Average price:', averagePrice);
        
        return {
            totalProducts,
            averagePrice: Math.round(averagePrice * 100) / 100,
            categoriesCount: this.categories.size,
            categories: Object.fromEntries(this.categories)
        };
    }
    
    // 🐛 DEBUG: Metodo di debug da rimuovere
    debugDumpAll() {
        console.log('=== DEBUG DUMP ===');
        console.log('Products:', this.products);
        console.log('Categories:', this.categories);
        console.log('Debug mode:', this.debugMode);
        console.log('==================');
    }
}

module.exports = ProductManager;
```

## 🎯 Obiettivo: Commit Selettivo

Vogliamo creare un commit che includa **SOLO** le nuove funzionalità:
- ✅ Validazione prodotto 
- ✅ Auto-generazione ID
- ✅ Gestione categorie
- ✅ Ricerca per categoria
- ✅ Calcolo statistiche

**ESCLUDENDO** tutto il codice di debug:
- 🐛 Console.log di debug
- 🐛 debugMode property
- 🐛 debugDumpAll method
- 🐛 Performance monitoring

## 🛠️ Processo di Staging Interattivo

### 1. Analisi Preliminare
```bash
# Vedere tutte le modifiche
git diff products.js

# Contare le righe modificate
git diff --stat products.js
```

### 2. Avvio Staging Interattivo
```bash
git add -p products.js
```

### 3. Sessione Interattiva Dettagliata

#### Hunk 1: Constructor con debug initialization
```diff
@@ -1,6 +1,10 @@
 class ProductManager {
     constructor() {
         this.products = [];
         this.categories = new Map();
+        // DEBUG: Logging per debugging inizializzazione
+        console.log('ProductManager initialized at:', new Date());
+        this.debugMode = true;
     }
```

**Decisione**: `n` (Non committare - è tutto debug)

#### Hunk 2: Validazione prodotto (da split)
```diff
@@ -8,6 +12,12 @@
     addProduct(product) {
+        // Validazione prodotto
+        if (!product || !product.name || !product.price) {
+            throw new Error('Prodotto non valido: nome e prezzo sono obbligatori');
+        }
+        
         this.products.push(product);
```

**Decisione**: `s` (Split), poi `y` (Sì alla validazione)

#### Hunk 3: Auto-generazione ID + debug log
```diff
@@ -14,8 +24,18 @@
         }
         
+        // Auto-generazione ID se mancante
+        if (!product.id) {
+            product.id = this.generateId();
+        }
+        
+        // DEBUG: Log di aggiunta prodotto
+        if (this.debugMode) {
+            console.log('Adding product:', product);
+            console.log('Current products count:', this.products.length);
+        }
+        
         this.products.push(product);
```

**Decisione**: `e` (Edit mode)

In edit mode, commenta le righe di debug:
```diff
@@ -14,8 +24,18 @@
         }
         
+        // Auto-generazione ID se mancante
+        if (!product.id) {
+            product.id = this.generateId();
+        }
+        
#        // DEBUG: Log di aggiunta prodotto
#        if (this.debugMode) {
#            console.log('Adding product:', product);
#            console.log('Current products count:', this.products.length);
#        }
+        
         this.products.push(product);
```

### 4. Continuazione Strategica
Continua la sessione applicando la strategia:
- `y` per tutti i metodi di feature (generateId, updateCategoryCount, getProductsByCategory, getStatistics)
- `e` o `n` per rimuovere/saltare tutti i console.log e codice debug
- `n` per il metodo debugDumpAll completo

### 5. Script di Automazione della Sessione

```bash
# Per automatizzare sessioni ripetitive, crea uno script
cat > staging_session.txt << 'EOF'
n
s
y
n
e
y
e
y
n
y
e
y
n
n
EOF

# Usa con: git add -p < staging_session.txt
```

## ✅ Verifica del Risultato

### Controlla cosa è in staging
```bash
git diff --cached products.js
```

### Output atteso (solo features, no debug):
```javascript
// Dovrebbe mostrare solo:
// - Validazione prodotto
// - Auto-generazione ID  
// - generateId method
// - updateCategoryCount method
// - getProductsByCategory method
// - getStatistics method

// SENZA:
// - console.log statements
// - debugMode property
// - debugDumpAll method
// - Performance monitoring
```

### Verifica working directory
```bash
git diff products.js
```

Dovrebbe mostrare solo il codice di debug rimasto nella working directory.

## 📝 Commit delle Features

```bash
git commit -m "feat: enhance product management with advanced features

- Add product validation for required fields (name, price)
- Implement auto-generation of unique product IDs
- Add category management with automatic counting
- Implement search by category functionality  
- Add comprehensive statistics calculation
- Improve error handling with descriptive messages

Breaking changes: none
Affects: ProductManager class"
```

## 🔄 Gestione del Debug Code Rimanente

### Opzione 1: Commit Debug Separato (per testing)
```bash
git add products.js
git commit -m "debug: add temporary logging for development

- Add constructor initialization logging
- Add product addition monitoring
- Add search operation debugging
- Add performance measurement tools
- Add complete debug dump functionality

Note: This debug code should be removed before production"
```

### Opzione 2: Stash Debug Code
```bash
git stash push products.js -m "Debug code for product manager testing"
```

### Opzione 3: Scarta Debug Code
```bash
git restore products.js
```

## 🎯 Risultato Finale

### Cronologia Pulita
```bash
git log --oneline -2
# abc1234 feat: enhance product management with advanced features
# def5678 feat: add basic product management system
```

### File di Produzione Pulito
Il file committato contiene solo codice production-ready senza logging di debug.

### Flessibilità Mantenuta
Il debug code può essere:
- Mantenuto in stash per test futuri
- Committato separatamente per team di QA
- Scartato se non più necessario

## 📚 Lezioni Apprese

### 1. Staging Strategy
- **Pianifica prima**: Identifica cosa committare e cosa no
- **Usa split e edit**: Per controllo granulare massimo
- **Verifica sempre**: `git diff --cached` prima del commit

### 2. Code Organization
- **Separa concerns**: Feature code vs debug code
- **Commenti chiari**: Distingui con commenti il tipo di codice
- **Review sistematica**: Esamina ogni hunk attentamente

### 3. Workflow Professionale
- **Commit semantici**: Messaggi che spiegano il valore business
- **Cronologia pulita**: Solo production code nella storia principale
- **Debug management**: Gestione separata del codice di debug

## 🔗 Scenari Correlati

### Quando Usare Questa Tecnica
- **Development attivo**: Molte modifiche sperimentali
- **Code review**: Preparazione di commit reviewable
- **Hotfix**: Separare fix urgenti da work-in-progress
- **Refactoring**: Commit incrementali di grandi cambiamenti

### Alternative per Scenari Simili
- **Branch strategy**: Feature branch per sperimentazione
- **Stash workflow**: Stash temporaneo di work-in-progress
- **Multiple files**: Separare feature e debug in file diversi

---

> **💡 Insight Professionale**: Il commit parziale non è solo una tecnica tecnica, ma una disciplina di pensiero. Ti costringe a distinguere tra "codice di valore" e "codice di supporto", migliorando la qualità generale del progetto.
