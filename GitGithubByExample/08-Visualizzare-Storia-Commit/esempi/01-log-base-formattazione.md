# Log Base e Formattazione

## 📖 Scenario Pratico

Immagina di essere un nuovo sviluppatore che si unisce a un team che lavora su un'applicazione e-commerce. Devi esplorare la cronologia del progetto per comprendere l'evoluzione delle funzionalità e familiarizzare con il codebase.

## 🎯 Obiettivi dell'Esempio

- Esplorare la cronologia con diversi formati di `git log`
- Applicare formattazioni personalizzate per diverse esigenze
- Creare alias utili per il workflow quotidiano
- Analizzare l'evoluzione del progetto

## 🚀 Setup del Scenario

### Creazione Repository di Esempio
```bash
# Crea directory e inizializza repository
mkdir ecommerce-project
cd ecommerce-project
git init

# Configura utente per l'esempio
git config user.name "Mario Rossi"
git config user.email "mario.rossi@company.com"
```

### Creazione Cronologia Realistica
```bash
# 1. Commit iniziale
echo "# E-commerce Project" > README.md
git add README.md
git commit -m "Initial commit: project setup"

# 2. Struttura base
mkdir -p src/{auth,products,cart,payment}
touch src/auth/login.js src/products/catalog.js src/cart/cart.js src/payment/payment.js
git add .
git commit -m "feat: add basic project structure

- Created authentication module
- Added product catalog structure
- Implemented cart functionality skeleton
- Payment processing foundation"

# 3. Configurazione utente diverso per simulare team
git config user.name "Anna Verdi"
git config user.email "anna.verdi@company.com"

# 4. Implementazione autenticazione
cat > src/auth/login.js << 'EOF'
function validateUser(username, password) {
    if (!username || !password) {
        return false;
    }
    // TODO: Add real validation
    return username.length > 3 && password.length > 6;
}

function login(username, password) {
    if (validateUser(username, password)) {
        sessionStorage.setItem('user', username);
        return true;
    }
    return false;
}

module.exports = { validateUser, login };
EOF

git add src/auth/login.js
git commit -m "feat(auth): implement basic login validation

- Add user validation function
- Implement session management
- Add password length requirements
- Export authentication functions"

# 5. Cambio utente per bug fix
git config user.name "Luigi Blu"
git config user.email "luigi.blu@company.com"

# 6. Bug fix
sed -i 's/username.length > 3/username.length >= 3/' src/auth/login.js
git add src/auth/login.js
git commit -m "fix(auth): correct username length validation

Fixed off-by-one error in username validation.
Minimum username length is now 3 characters instead of 4.

Fixes: #123"

# 7. Ritorno al primo utente
git config user.name "Mario Rossi"
git config user.email "mario.rossi@company.com"

# 8. Feature prodotti
cat > src/products/catalog.js << 'EOF'
class ProductCatalog {
    constructor() {
        this.products = [];
    }

    addProduct(product) {
        this.products.push({
            id: Date.now(),
            ...product,
            createdAt: new Date()
        });
    }

    searchProducts(query) {
        return this.products.filter(p => 
            p.name.toLowerCase().includes(query.toLowerCase()) ||
            p.description.toLowerCase().includes(query.toLowerCase())
        );
    }

    getProductById(id) {
        return this.products.find(p => p.id === id);
    }
}

module.exports = ProductCatalog;
EOF

git add src/products/catalog.js
git commit -m "feat(products): implement product catalog

- Add ProductCatalog class
- Implement add, search, and get methods
- Add automatic ID generation
- Include creation timestamp"

# 9. Hotfix critico
git config user.name "Emergency Bot"
git config user.email "emergency@company.com"

echo "console.log('Security patch applied');" >> src/auth/login.js
git add src/auth/login.js
git commit -m "hotfix: apply security patch for login validation

CRITICAL: Fixes security vulnerability in authentication.
Applied emergency patch as recommended by security team.

CVE-2024-0001"

# 10. Feature carrello
git config user.name "Sara Rosa"
git config user.email "sara.rosa@company.com"

cat > src/cart/cart.js << 'EOF'
class ShoppingCart {
    constructor() {
        this.items = [];
        this.total = 0;
    }

    addItem(product, quantity = 1) {
        const existingItem = this.items.find(item => item.product.id === product.id);
        
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            this.items.push({ product, quantity });
        }
        
        this.calculateTotal();
    }

    removeItem(productId) {
        this.items = this.items.filter(item => item.product.id !== productId);
        this.calculateTotal();
    }

    calculateTotal() {
        this.total = this.items.reduce((sum, item) => {
            return sum + (item.product.price * item.quantity);
        }, 0);
    }

    getItemCount() {
        return this.items.reduce((count, item) => count + item.quantity, 0);
    }
}

module.exports = ShoppingCart;
EOF

git add src/cart/cart.js
git commit -m "feat(cart): implement shopping cart functionality

- Add ShoppingCart class with full functionality
- Implement add/remove items with quantity handling
- Add automatic total calculation
- Include item count method for UI updates"

# 11. Documentazione
cat > CHANGELOG.md << 'EOF'
# Changelog

## [1.0.0] - 2024-01-15

### Added
- Initial project structure
- Authentication system with login validation
- Product catalog with search functionality
- Shopping cart with item management
- Basic security measures

### Fixed
- Username validation length requirement
- Security vulnerability in authentication

### Security
- Applied critical security patch CVE-2024-0001
EOF

git add CHANGELOG.md
git commit -m "docs: add changelog and project documentation

- Document all major features implemented
- Track security fixes and patches
- Prepare for v1.0.0 release"

# 12. Tag per release
git tag -a v1.0.0 -m "Release version 1.0.0

First stable release with core functionality:
- User authentication
- Product catalog
- Shopping cart
- Security patches applied"
```

## 🔍 Esplorazione con Git Log Base

### 1. Vista Cronologia Standard
```bash
# Log completo default
git log

# Analisi output:
# - Ogni commit mostra hash completo, autore, data, messaggio
# - Commits ordinati dal più recente al più vecchio
# - Metadati completi per ogni modifica
```

**Osservazione**: Il log standard è molto dettagliato ma può essere verboso per una vista d'insieme.

### 2. Vista Compatta
```bash
# Log compatto una riga per commit
git log --oneline

# Output esempio:
# a1b2c3d (HEAD -> main, tag: v1.0.0) docs: add changelog and project documentation
# b2c3d4e feat(cart): implement shopping cart functionality
# c3d4e5f hotfix: apply security patch for login validation
# d4e5f6g feat(products): implement product catalog
# e5f6g7h fix(auth): correct username length validation
```

**Vantaggi**: Panoramica rapida di tutti i commit con informazioni essenziali.

### 3. Vista con Grafico
```bash
# Log con rappresentazione grafica dei branch
git log --oneline --graph --decorate

# Output esempio:
# * a1b2c3d (HEAD -> main, tag: v1.0.0) docs: add changelog and project documentation
# * b2c3d4e feat(cart): implement shopping cart functionality
# * c3d4e5f hotfix: apply security patch for login validation
# * d4e5f6g feat(products): implement product catalog
# * e5f6g7h fix(auth): correct username length validation
# * f6g7h8i feat(auth): implement basic login validation
# * g7h8i9j feat: add basic project structure
# * h8i9j0k Initial commit: project setup
```

**Utilità**: Visualizza la struttura lineare del repository e i riferimenti (tag, branch).

## 🎨 Formattazioni Personalizzate

### 1. Format per Code Review
```bash
# Formato dettagliato per revisioni
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(green)%s%C(reset)%n%C(blue)Author: %an <%ae>%C(reset)%n%C(red)Date: %ad%C(reset)%n" --date=short -5

# Output colorato e strutturato:
# a1b2c3d - docs: add changelog and project documentation
# Author: Sara Rosa <sara.rosa@company.com>
# Date: 2024-01-15
#
# b2c3d4e - feat(cart): implement shopping cart functionality
# Author: Sara Rosa <sara.rosa@company.com>
# Date: 2024-01-15
```

**Applicazione**: Perfetto per email di aggiornamento team o documentazione di sprint.

### 2. Format per Release Notes
```bash
# Formato per note di rilascio
git log --pretty=format:"- %s (%h)" --reverse v1.0.0

# Output:
# - Initial commit: project setup (h8i9j0k)
# - feat: add basic project structure (g7h8i9j)
# - feat(auth): implement basic login validation (f6g7h8i)
# - fix(auth): correct username length validation (e5f6g7h)
# - feat(products): implement product catalog (d4e5f6g)
# - hotfix: apply security patch for login validation (c3d4e5f)
# - feat(cart): implement shopping cart functionality (b2c3d4e)
# - docs: add changelog and project documentation (a1b2c3d)
```

**Utilizzo**: Generare automaticamente changelog per rilasci.

### 3. Format per Analisi Team
```bash
# Formato per tracking contributori
git log --pretty=format:"%C(bold blue)%an%C(reset) - %C(green)(%ar)%C(reset) %s" --since="1 month ago"

# Output:
# Sara Rosa - (2 hours ago) docs: add changelog and project documentation
# Sara Rosa - (2 hours ago) feat(cart): implement shopping cart functionality
# Emergency Bot - (3 hours ago) hotfix: apply security patch for login validation
# Mario Rossi - (3 hours ago) feat(products): implement product catalog
# Luigi Blu - (4 hours ago) fix(auth): correct username length validation
```

**Beneficio**: Vedere rapidamente chi ha lavorato su cosa e quando.

## 📊 Analisi con Statistiche

### 1. Log con Statistiche File
```bash
# Vedere quali file sono stati modificati
git log --stat --oneline -5

# Output:
# a1b2c3d docs: add changelog and project documentation
#  CHANGELOG.md | 15 +++++++++++++++
#  1 file changed, 15 insertions(+)
#
# b2c3d4e feat(cart): implement shopping cart functionality
#  src/cart/cart.js | 35 +++++++++++++++++++++++++++++++++++
#  1 file changed, 35 insertions(+)
```

**Insight**: Capire l'impatto di ogni commit in termini di righe di codice.

### 2. Log con Nomi File
```bash
# Solo i nomi dei file modificati
git log --name-only --oneline -3

# Output:
# a1b2c3d docs: add changelog and project documentation
# CHANGELOG.md
#
# b2c3d4e feat(cart): implement shopping cart functionality
# src/cart/cart.js
#
# c3d4e5f hotfix: apply security patch for login validation
# src/auth/login.js
```

**Utilità**: Tracciare quali parti del sistema sono state modificate.

### 3. Log con Status File
```bash
# Status delle modifiche (A=Added, M=Modified, D=Deleted)
git log --name-status --oneline -5

# Output:
# a1b2c3d docs: add changelog and project documentation
# A       CHANGELOG.md
#
# b2c3d4e feat(cart): implement shopping cart functionality
# A       src/cart/cart.js
#
# c3d4e5f hotfix: apply security patch for login validation
# M       src/auth/login.js
```

**Valore**: Distinguere tra file nuovi, modificati e eliminati.

## ⚡ Creazione Alias Utili

### 1. Alias per Uso Quotidiano
```bash
# Alias base per sviluppo
git config --global alias.lg "log --oneline --graph --decorate"
git config --global alias.last "log -1 --stat"
git config --global alias.today "log --since='1 day ago' --oneline --author='$(git config user.name)'"

# Test degli alias
git lg
git last
git today
```

### 2. Alias per Team Management
```bash
# Alias per gestione team
git config --global alias.team "log --pretty=format:'%an - %s (%ar)' --since='1 week ago'"
git config --global alias.activity "log --pretty=format:'%ad %an: %s' --date=short --since='1 month ago'"

# Test
git team
git activity
```

### 3. Alias per Release
```bash
# Alias per preparazione release
git config --global alias.changes "log --pretty=format:'- %s (%h)' --reverse"
git config --global alias.contributors "log --pretty=format:'%an <%ae>' | sort | uniq"

# Test
git changes v1.0.0..HEAD  # Cambiamenti dalla v1.0.0
git contributors
```

## 🔄 Workflow Pratici

### 1. Daily Standup Report
```bash
# Script per report giornaliero
echo "=== DAILY STANDUP REPORT ==="
echo "Yesterday's commits:"
git log --since='1 day ago' --until='now' --pretty=format:'- %s (%an)' --author="$(git config user.name)"

echo -e "\nTeam activity:"
git log --since='1 day ago' --pretty=format:'%an: %s' | head -10
```

### 2. Sprint Review Analysis
```bash
# Analisi dello sprint
echo "=== SPRINT ANALYSIS ==="
echo "Total commits this week:"
git log --since='1 week ago' --oneline | wc -l

echo -e "\nContributors:"
git log --since='1 week ago' --pretty=format:'%an' | sort | uniq -c | sort -nr

echo -e "\nFeatures completed:"
git log --since='1 week ago' --grep='feat' --pretty=format:'- %s'

echo -e "\nBugs fixed:"
git log --since='1 week ago' --grep='fix' --pretty=format:'- %s'
```

### 3. File Change Tracking
```bash
# Tracking modifiche per file critico
echo "=== AUTH MODULE CHANGES ==="
git log --follow --patch -- src/auth/login.js | head -50

echo -e "\n=== WHO MODIFIED AUTH ==="
git log --pretty=format:'%an - %s (%ar)' -- src/auth/
```

## 📈 Analisi dei Risultati

### Osservazioni dal Log
1. **Pattern di Commit**: Il team usa conventional commits (feat:, fix:, docs:)
2. **Frequenza**: Commits regolari con piccole modifiche incrementali
3. **Collaborazione**: Diversi sviluppatori lavorano su moduli separati
4. **Sicurezza**: Hotfix applicati rapidamente quando necessario

### Insights Strategici
- **Code Quality**: Messaggi di commit informativi aiutano la manutenzione
- **Team Coordination**: Diversi sviluppatori evitano conflitti lavorando su file separati
- **Release Management**: Tag e changelog facilitano il deployment

### Best Practices Identificate
- Uso consistente di prefissi nei messaggi commit
- Documentazione tempestiva dei cambiamenti
- Applicazione rapida di patch di sicurezza
- Tracking esplicito di bug fixes con reference agli issue

## 🧪 Esercizi di Consolidamento

### Esercizio 1: Analisi Personalizzata
```bash
# Crea un format personalizzato che mostri:
# - Hash abbreviato in giallo
# - Messaggio in bianco
# - Autore in blu tra parentesi
# - Data relativa in verde

# Soluzione:
git log --pretty=format:"%C(yellow)%h%C(reset) %C(white)%s%C(reset) %C(blue)(%an)%C(reset) %C(green)%ar%C(reset)"
```

### Esercizio 2: Alias Avanzato
```bash
# Crea un alias chiamato 'summary' che mostri:
# - Ultimi 10 commit in formato compatto
# - Con statistiche dei file
# - Solo dal branch corrente

# Soluzione:
git config --global alias.summary "log --oneline --stat -10 --no-merges"
```

### Esercizio 3: Report Automatizzato
```bash
# Scrivi un comando che generi un report con:
# - Numero totale di commit
# - Top 3 contributori
# - File più modificati

# Soluzione parziale:
git log --oneline | wc -l  # Conta commit
git log --pretty=format:'%an' | sort | uniq -c | sort -nr | head -3  # Top contributori
```

## 🔄 Prossimi Passi

Ora che hai familiarità con git log base, puoi:
1. **Esplorare filtri avanzati** per ricerche specifiche
2. **Praticare con repository più complessi** con merge e branch
3. **Automatizzare** report con script personalizzati
4. **Integrare** con strumenti grafici per visualizzazioni avanzate

---

**Continua con**: [02-Ricerca-Cronologia](./02-ricerca-cronologia.md) - Tecniche avanzate di ricerca nella cronologia
