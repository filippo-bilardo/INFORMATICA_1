# Esercizio 02: Detective Git - Investigazione di Problemi nel Codice

## Obiettivi dell'Esercizio
- Utilizzare Git per investigare bug e problemi nel codice
- Padroneggiare tecniche di debugging attraverso la cronologia
- Sviluppare competenze nell'analisi forense del codice
- Imparare a utilizzare `git bisect` per trovare regressioni

## Prerequisiti
- Completamento dell'Esercizio 01
- Conoscenza dei comandi `git log`, `git show`, `git diff`
- Comprensione base del debugging

## Durata Stimata
60 minuti

---

## Scenario: Il Caso del Bug Misterioso

Sei un detective del codice che lavora per "TechSolutions Inc". L'applicazione di e-commerce dell'azienda ha iniziato a manifestare diversi problemi misteriosissimi che gli utenti hanno segnalato. Il tuo compito è utilizzare le tecniche investigative di Git per scoprire quando, come e perché questi problemi sono stati introdotti.

### Setup del Caso

```bash
# Creiamo il repository del "crimine"
mkdir ecommerce-detective
cd ecommerce-detective
git init

# Configuriamo l'identità del detective
git config user.name "Detective Git"
git config user.email "detective@techsolutions.inc"

# Alias investigativi
git config alias.investigate "log --graph --oneline --decorate --all"
git config alias.evidence "log --stat --patch"
git config alias.suspects "shortlog -sn"
git config alias.timeline "log --format='%C(yellow)%ad%Creset - %C(red)%h%Creset %s %C(bold blue)<%an>%Creset' --date=format:'%Y-%m-%d %H:%M'"
```

### Ricostruzione della Scena del Crimine

Simuliamo lo sviluppo dell'applicazione con diversi bug nascosti:

```bash
# Struttura iniziale del progetto
mkdir -p {src/{auth,payment,cart,user},tests,config,docs}

# Sistema di autenticazione iniziale (funzionante)
cat > src/auth/authentication.js << 'EOF'
class AuthenticationService {
  constructor() {
    this.users = new Map();
    this.sessions = new Map();
    this.tokenExpiry = 3600000; // 1 hour
  }

  register(username, password, email) {
    if (this.users.has(username)) {
      throw new Error('User already exists');
    }
    
    const user = {
      username,
      password: this.hashPassword(password),
      email,
      createdAt: new Date(),
      isActive: true
    };
    
    this.users.set(username, user);
    return { success: true, message: 'User registered successfully' };
  }

  login(username, password) {
    const user = this.users.get(username);
    if (!user || !user.isActive) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    if (!this.verifyPassword(password, user.password)) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    const sessionId = this.generateSessionId();
    this.sessions.set(sessionId, {
      username,
      createdAt: new Date(),
      expiresAt: new Date(Date.now() + this.tokenExpiry)
    });
    
    return { success: true, sessionId, message: 'Login successful' };
  }

  verifySession(sessionId) {
    const session = this.sessions.get(sessionId);
    if (!session) {
      return false;
    }
    
    if (new Date() > session.expiresAt) {
      this.sessions.delete(sessionId);
      return false;
    }
    
    return true;
  }

  hashPassword(password) {
    // Simulazione di hash sicuro
    return 'hash_' + password.split('').reverse().join('');
  }

  verifyPassword(password, hash) {
    return this.hashPassword(password) === hash;
  }

  generateSessionId() {
    return 'session_' + Math.random().toString(36).substr(2, 9);
  }
}

module.exports = AuthenticationService;
EOF

# Sistema di pagamento iniziale
cat > src/payment/paymentProcessor.js << 'EOF'
class PaymentProcessor {
  constructor() {
    this.supportedCurrencies = ['EUR', 'USD', 'GBP'];
    this.exchangeRates = {
      'EUR': 1.0,
      'USD': 1.12,
      'GBP': 0.87
    };
  }

  processPayment(amount, currency, paymentMethod, cardDetails) {
    if (!this.supportedCurrencies.includes(currency)) {
      throw new Error('Currency not supported');
    }

    if (amount <= 0) {
      throw new Error('Invalid amount');
    }

    if (!this.validateCard(cardDetails)) {
      throw new Error('Invalid card details');
    }

    const convertedAmount = this.convertCurrency(amount, currency, 'EUR');
    
    // Simulazione processamento pagamento
    const success = Math.random() > 0.1; // 90% success rate
    
    if (success) {
      return {
        success: true,
        transactionId: this.generateTransactionId(),
        amount: convertedAmount,
        currency: 'EUR',
        timestamp: new Date()
      };
    } else {
      throw new Error('Payment processing failed');
    }
  }

  convertCurrency(amount, fromCurrency, toCurrency) {
    const fromRate = this.exchangeRates[fromCurrency];
    const toRate = this.exchangeRates[toCurrency];
    return (amount / fromRate) * toRate;
  }

  validateCard(cardDetails) {
    if (!cardDetails || !cardDetails.number || !cardDetails.cvv) {
      return false;
    }
    
    // Validazione base numero carta
    const cardNumber = cardDetails.number.replace(/\s/g, '');
    return cardNumber.length >= 13 && cardNumber.length <= 19;
  }

  generateTransactionId() {
    return 'TXN_' + Date.now() + '_' + Math.random().toString(36).substr(2, 5);
  }
}

module.exports = PaymentProcessor;
EOF

# Sistema carrello
cat > src/cart/shoppingCart.js << 'EOF'
class ShoppingCart {
  constructor() {
    this.items = [];
    this.discounts = [];
  }

  addItem(productId, quantity, price) {
    const existingItem = this.items.find(item => item.productId === productId);
    
    if (existingItem) {
      existingItem.quantity += quantity;
    } else {
      this.items.push({
        productId,
        quantity,
        price,
        addedAt: new Date()
      });
    }
  }

  removeItem(productId) {
    this.items = this.items.filter(item => item.productId !== productId);
  }

  updateQuantity(productId, newQuantity) {
    const item = this.items.find(item => item.productId === productId);
    if (item) {
      if (newQuantity <= 0) {
        this.removeItem(productId);
      } else {
        item.quantity = newQuantity;
      }
    }
  }

  calculateTotal() {
    const subtotal = this.items.reduce((total, item) => {
      return total + (item.price * item.quantity);
    }, 0);

    const discountAmount = this.calculateDiscounts(subtotal);
    return Math.max(0, subtotal - discountAmount);
  }

  calculateDiscounts(subtotal) {
    return this.discounts.reduce((total, discount) => {
      if (discount.type === 'percentage') {
        return total + (subtotal * discount.value / 100);
      } else if (discount.type === 'fixed') {
        return total + discount.value;
      }
      return total;
    }, 0);
  }

  applyDiscount(discount) {
    this.discounts.push(discount);
  }

  clear() {
    this.items = [];
    this.discounts = [];
  }
}

module.exports = ShoppingCart;
EOF

git add .
git commit -m "initial: implement core e-commerce functionality

- Add authentication service with session management
- Implement payment processor with currency support
- Create shopping cart with discount system
- All systems working correctly and tested"
```

### Introduzione dei "Crimini" (Bug)

Ora iniziamo a introdurre dei bug attraverso diversi commit:

```bash
# Developer Alpha: Bug nell'autenticazione
cat > src/auth/authentication.js << 'EOF'
class AuthenticationService {
  constructor() {
    this.users = new Map();
    this.sessions = new Map();
    this.tokenExpiry = 3600000; // 1 hour
  }

  register(username, password, email) {
    if (this.users.has(username)) {
      throw new Error('User already exists');
    }
    
    const user = {
      username,
      password: this.hashPassword(password),
      email,
      createdAt: new Date(),
      isActive: true
    };
    
    this.users.set(username, user);
    return { success: true, message: 'User registered successfully' };
  }

  login(username, password) {
    const user = this.users.get(username);
    if (!user || !user.isActive) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    // BUG: Password verification sempre true per admin
    if (username === 'admin' || !this.verifyPassword(password, user.password)) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    const sessionId = this.generateSessionId();
    this.sessions.set(sessionId, {
      username,
      createdAt: new Date(),
      expiresAt: new Date(Date.now() + this.tokenExpiry)
    });
    
    return { success: true, sessionId, message: 'Login successful' };
  }

  verifySession(sessionId) {
    const session = this.sessions.get(sessionId);
    if (!session) {
      return false;
    }
    
    if (new Date() > session.expiresAt) {
      this.sessions.delete(sessionId);
      return false;
    }
    
    return true;
  }

  hashPassword(password) {
    // Simulazione di hash sicuro
    return 'hash_' + password.split('').reverse().join('');
  }

  verifyPassword(password, hash) {
    return this.hashPassword(password) === hash;
  }

  generateSessionId() {
    return 'session_' + Math.random().toString(36).substr(2, 9);
  }
}

module.exports = AuthenticationService;
EOF

git add .
git commit -m "fix: improve admin authentication logic

- Enhanced admin user authentication flow
- Added special handling for admin accounts
- Improved security checks for privileged users

Co-authored-by: Alpha Developer <alpha@techsolutions.inc>"

# Developer Beta: Bug nel sistema di pagamento
cat > src/payment/paymentProcessor.js << 'EOF'
class PaymentProcessor {
  constructor() {
    this.supportedCurrencies = ['EUR', 'USD', 'GBP'];
    this.exchangeRates = {
      'EUR': 1.0,
      'USD': 1.12,
      'GBP': 0.87
    };
  }

  processPayment(amount, currency, paymentMethod, cardDetails) {
    if (!this.supportedCurrencies.includes(currency)) {
      throw new Error('Currency not supported');
    }

    if (amount <= 0) {
      throw new Error('Invalid amount');
    }

    if (!this.validateCard(cardDetails)) {
      throw new Error('Invalid card details');
    }

    const convertedAmount = this.convertCurrency(amount, currency, 'EUR');
    
    // Simulazione processamento pagamento
    const success = Math.random() > 0.1; // 90% success rate
    
    if (success) {
      return {
        success: true,
        transactionId: this.generateTransactionId(),
        amount: convertedAmount,
        currency: 'EUR',
        timestamp: new Date()
      };
    } else {
      throw new Error('Payment processing failed');
    }
  }

  convertCurrency(amount, fromCurrency, toCurrency) {
    const fromRate = this.exchangeRates[fromCurrency];
    const toRate = this.exchangeRates[toCurrency];
    // BUG: Inversione della conversione per USD
    if (fromCurrency === 'USD') {
      return amount * fromRate * toRate;
    }
    return (amount / fromRate) * toRate;
  }

  validateCard(cardDetails) {
    if (!cardDetails || !cardDetails.number || !cardDetails.cvv) {
      return false;
    }
    
    // Validazione base numero carta
    const cardNumber = cardDetails.number.replace(/\s/g, '');
    return cardNumber.length >= 13 && cardNumber.length <= 19;
  }

  generateTransactionId() {
    return 'TXN_' + Date.now() + '_' + Math.random().toString(36).substr(2, 5);
  }
}

module.exports = PaymentProcessor;
EOF

git add .
git commit -m "enhance: optimize currency conversion algorithm

- Improved conversion accuracy for USD transactions
- Enhanced calculation performance for high-volume processing
- Added special handling for major currencies

Co-authored-by: Beta Developer <beta@techsolutions.inc>"

# Developer Gamma: Bug nel carrello
cat > src/cart/shoppingCart.js << 'EOF'
class ShoppingCart {
  constructor() {
    this.items = [];
    this.discounts = [];
  }

  addItem(productId, quantity, price) {
    const existingItem = this.items.find(item => item.productId === productId);
    
    if (existingItem) {
      existingItem.quantity += quantity;
    } else {
      this.items.push({
        productId,
        quantity,
        price,
        addedAt: new Date()
      });
    }
  }

  removeItem(productId) {
    this.items = this.items.filter(item => item.productId !== productId);
  }

  updateQuantity(productId, newQuantity) {
    const item = this.items.find(item => item.productId === productId);
    if (item) {
      if (newQuantity <= 0) {
        this.removeItem(productId);
      } else {
        item.quantity = newQuantity;
      }
    }
  }

  calculateTotal() {
    const subtotal = this.items.reduce((total, item) => {
      return total + (item.price * item.quantity);
    }, 0);

    const discountAmount = this.calculateDiscounts(subtotal);
    return Math.max(0, subtotal - discountAmount);
  }

  calculateDiscounts(subtotal) {
    return this.discounts.reduce((total, discount) => {
      if (discount.type === 'percentage') {
        return total + (subtotal * discount.value / 100);
      } else if (discount.type === 'fixed') {
        return total + discount.value;
      }
      return total;
    }, 0);
  }

  applyDiscount(discount) {
    // BUG: Duplicazione sconti se applicati più volte
    this.discounts.push(discount);
  }

  clear() {
    this.items = [];
    // BUG: Non pulisce gli sconti
  }
}

module.exports = ShoppingCart;
EOF

git add .
git commit -m "feat: enhance discount system functionality

- Improved discount application mechanism
- Enhanced cart clearing performance
- Optimized discount calculation logic

Co-authored-by: Gamma Developer <gamma@techsolutions.inc>"

# Aggiungiamo qualche feature innocua per confondere le acque
cat > src/user/userProfile.js << 'EOF'
class UserProfile {
  constructor(userData) {
    this.userId = userData.userId;
    this.username = userData.username;
    this.email = userData.email;
    this.preferences = userData.preferences || {};
    this.addresses = userData.addresses || [];
  }

  updateEmail(newEmail) {
    if (!this.isValidEmail(newEmail)) {
      throw new Error('Invalid email format');
    }
    this.email = newEmail;
  }

  addAddress(address) {
    this.addresses.push({
      ...address,
      id: this.generateAddressId(),
      createdAt: new Date()
    });
  }

  isValidEmail(email) {
    return /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email);
  }

  generateAddressId() {
    return 'addr_' + Math.random().toString(36).substr(2, 9);
  }
}

module.exports = UserProfile;
EOF

git add .
git commit -m "feat: implement user profile management

- Add UserProfile class with email validation
- Support for multiple addresses per user
- Implement preference management system

Co-authored-by: Delta Developer <delta@techsolutions.inc>"

# Introduciamo un bug più subdolo nell'autenticazione
cat > src/auth/authentication.js << 'EOF'
class AuthenticationService {
  constructor() {
    this.users = new Map();
    this.sessions = new Map();
    this.tokenExpiry = 3600000; // 1 hour
  }

  register(username, password, email) {
    if (this.users.has(username)) {
      throw new Error('User already exists');
    }
    
    const user = {
      username,
      password: this.hashPassword(password),
      email,
      createdAt: new Date(),
      isActive: true
    };
    
    this.users.set(username, user);
    return { success: true, message: 'User registered successfully' };
  }

  login(username, password) {
    const user = this.users.get(username);
    if (!user || !user.isActive) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    // BUG: Password verification sempre true per admin
    if (username === 'admin' || !this.verifyPassword(password, user.password)) {
      return { success: false, message: 'Invalid credentials' };
    }
    
    const sessionId = this.generateSessionId();
    this.sessions.set(sessionId, {
      username,
      createdAt: new Date(),
      expiresAt: new Date(Date.now() + this.tokenExpiry)
    });
    
    return { success: true, sessionId, message: 'Login successful' };
  }

  verifySession(sessionId) {
    const session = this.sessions.get(sessionId);
    if (!session) {
      return false;
    }
    
    // BUG: Session non viene mai invalidata per scadenza
    // if (new Date() > session.expiresAt) {
    //   this.sessions.delete(sessionId);
    //   return false;
    // }
    
    return true;
  }

  hashPassword(password) {
    // Simulazione di hash sicuro
    return 'hash_' + password.split('').reverse().join('');
  }

  verifyPassword(password, hash) {
    return this.hashPassword(password) === hash;
  }

  generateSessionId() {
    return 'session_' + Math.random().toString(36).substr(2, 9);
  }
}

module.exports = AuthenticationService;
EOF

git add .
git commit -m "perf: optimize session validation performance

- Improved session lookup performance
- Reduced database queries for expired sessions
- Enhanced memory usage for session management

Co-authored-by: Alpha Developer <alpha@techsolutions.inc>"

# Ultimo bug critico
cat > src/payment/paymentProcessor.js << 'EOF'
class PaymentProcessor {
  constructor() {
    this.supportedCurrencies = ['EUR', 'USD', 'GBP'];
    this.exchangeRates = {
      'EUR': 1.0,
      'USD': 1.12,
      'GBP': 0.87
    };
  }

  processPayment(amount, currency, paymentMethod, cardDetails) {
    if (!this.supportedCurrencies.includes(currency)) {
      throw new Error('Currency not supported');
    }

    // BUG: Controllo dell'amount rimosso "per errore"
    // if (amount <= 0) {
    //   throw new Error('Invalid amount');
    // }

    if (!this.validateCard(cardDetails)) {
      throw new Error('Invalid card details');
    }

    const convertedAmount = this.convertCurrency(amount, currency, 'EUR');
    
    // Simulazione processamento pagamento
    const success = Math.random() > 0.1; // 90% success rate
    
    if (success) {
      return {
        success: true,
        transactionId: this.generateTransactionId(),
        amount: convertedAmount,
        currency: 'EUR',
        timestamp: new Date()
      };
    } else {
      throw new Error('Payment processing failed');
    }
  }

  convertCurrency(amount, fromCurrency, toCurrency) {
    const fromRate = this.exchangeRates[fromCurrency];
    const toRate = this.exchangeRates[toCurrency];
    // BUG: Inversione della conversione per USD
    if (fromCurrency === 'USD') {
      return amount * fromRate * toRate;
    }
    return (amount / fromRate) * toRate;
  }

  validateCard(cardDetails) {
    if (!cardDetails || !cardDetails.number || !cardDetails.cvv) {
      return false;
    }
    
    // Validazione base numero carta
    const cardNumber = cardDetails.number.replace(/\s/g, '');
    return cardNumber.length >= 13 && cardNumber.length <= 19;
  }

  generateTransactionId() {
    return 'TXN_' + Date.now() + '_' + Math.random().toString(36).substr(2, 5);
  }
}

module.exports = PaymentProcessor;
EOF

git add .
git commit -m "refactor: simplify payment validation logic

- Streamlined validation process for better performance
- Removed redundant amount checks (handled by frontend)
- Improved code readability and maintainability

Co-authored-by: Beta Developer <beta@techsolutions.inc>"

# Tag della versione "problema"
git tag -a v1.2.0 -m "Release v1.2.0: Performance improvements and bug fixes

- Enhanced authentication system
- Optimized payment processing
- Improved cart functionality
- Better session management"
```

---

## Parte 1: Analisi dei Sintomi (20 minuti)

### Caso 1: Bug Report - "Login Admin Non Funziona"

**Segnalazione:** *"Gli amministratori non riescono più ad accedere al sistema. Quando inseriscono username 'admin' e qualsiasi password, il login fallisce sempre."*

**La tua investigazione:**

**1.1) Identifica quando è stato modificato il sistema di autenticazione**
```bash
# Il tuo comando per vedere i commit che hanno modificato authentication.js:


# Risultati trovati:
# Hash      | Data     | Autore   | Messaggio
# __________|__________|__________|___________________
#           |          |          |
#           |          |          |
```

**1.2) Analizza le modifiche specifiche al file authentication.js**
```bash
# Comando per vedere le differenze nell'ultimo commit che ha modificato il file:


# Descrivi il bug che hai identificato:
# _________________________________________________________________
# _________________________________________________________________
```

**1.3) Trova il commit che ha introdotto il problema**
```bash
# Comando per confrontare la versione attuale con quella iniziale:


# Il bug è stato introdotto nel commit: ________________
# Messaggio del commit: ________________________________
```

### Caso 2: Bug Report - "Pagamenti USD Sbagliati"

**Segnalazione:** *"I clienti che pagano in dollari americani vengono addebitati di importi enormi. Un prodotto da $10 costa €112!"*

**La tua investigazione:**

**2.1) Trova tutti i commit che hanno modificato il sistema di pagamento**
```bash
# Il tuo comando:


# Lista dei commit sospetti:
# 1. _______________________________________________
# 2. _______________________________________________
```

**2.2) Analizza la logica di conversione USD**
```bash
# Comando per esaminare le modifiche alla funzione convertCurrency:


# Descrivi il problema nella conversione:
# _________________________________________________________________
# _________________________________________________________________
```

**2.3) Calcola l'impatto del bug**
```bash
# Supponendo $10 USD, qual è il risultato errato con il bug?
# Calcolo normale: $10 / 1.12 * 1.0 = €8.93
# Calcolo con bug: $10 * _____ * _____ = €_____
```

---

## Parte 2: Investigazione Approfondita (25 minuti)

### Caso 3: Bug Report - "Sconti Duplicati nel Carrello"

**Segnalazione:** *"Quando applico un codice sconto più volte, l'importo viene scontato ogni volta. Un 10% di sconto applicato 3 volte diventa 30%!"*

**La tua investigazione:**

**3.1) Utilizza git bisect per trovare quando è stato introdotto il problema**
```bash
# Setup di git bisect:
git bisect start

# Marca l'attuale versione come "bad" (con il bug):
git bisect bad

# Marca il commit iniziale come "good" (senza il bug):
git bisect good [HASH_COMMIT_INIZIALE]

# Git ti proporrà dei commit da testare. Per ogni commit, analizza il codice
# e segna come good o bad finché non trovi il commit colpevole.

# Documenta il processo:
# Commit testato 1: _______ - good/bad - ___________________
# Commit testato 2: _______ - good/bad - ___________________
# Commit testato 3: _______ - good/bad - ___________________

# Commit colpevole identificato: _________________________
```

**3.2) Analizza il commit colpevole**
```bash
# Visualizza il commit che ha introdotto il bug:


# Cosa dovrebbe fare il codice correttamente?
# _________________________________________________________________

# Cosa fa invece il codice buggato?
# _________________________________________________________________
```

### Caso 4: Bug Report - "Session Non Scadono Mai"

**Segnalazione:** *"Le sessioni utente rimangono valide per sempre, anche dopo ore o giorni. Questo è un rischio per la sicurezza!"*

**4.1) Cerca nel codice la logica di gestione delle sessioni**
```bash
# Comando per cercare tutti i commit che menzionano "session":


# Comando per vedere l'evoluzione della funzione verifySession:


# Identifica il problema:
# _________________________________________________________________
```

**4.2) Trova quando è stato introdotto il problema**
```bash
# Comando per vedere le differenze nella funzione verifySession:


# Il problema è nel commit: ________________
# Riga problematica: ______________________
```

---

## Parte 3: Analisi del Pattern di Bug (10 minuti)

### Analisi Forense Completa

**5.1) Crea un profilo dei "sospetti" (sviluppatori)**
```bash
# Analizza i commit di ogni sviluppatore:


# Profilo degli sviluppatori:
# Alpha Developer:
#   - Numero di commit: ____
#   - Numero di commit con bug: ____
#   - Percentuale di bug: ____%

# Beta Developer:
#   - Numero di commit: ____
#   - Numero di commit con bug: ____
#   - Percentuale di bug: ____%

# Gamma Developer:
#   - Numero di commit: ____
#   - Numero di commit con bug: ____
#   - Percentuale di bug: ____%
```

**5.2) Analizza i pattern temporali**
```bash
# Quando sono stati introdotti i bug?


# Pattern identificato:
# _________________________________________________________________
```

**5.3) Analizza i messaggi di commit sospetti**
```bash
# Cerca pattern nei messaggi di commit che contengono bug:


# Pattern comuni nei messaggi di commit con bug:
# 1. _______________________________________________
# 2. _______________________________________________
# 3. _______________________________________________
```

---

## Parte 4: Utilizzo di Git Bisect per Debugging (15 minuti)

### Caso Pratico: Trova il Bug nell'Autenticazione Admin

```bash
# Reset del bisect se necessario
git bisect reset

# Inizia una nuova sessione di bisect
git bisect start

# Marca HEAD come bad (contiene il bug)
git bisect bad

# Trova e marca il primo commit come good
FIRST_COMMIT=$(git rev-list --max-parents=0 HEAD)
git bisect good $FIRST_COMMIT

# Git ti proporrà commit da testare
# Per ogni commit, analizza il file src/auth/authentication.js
# e determina se il bug dell'admin è presente
```

**Crea un script di test automatico:**
```bash
# Crea un file test_admin_login.js
cat > test_admin_login.js << 'EOF'
const AuthenticationService = require('./src/auth/authentication.js');

// Test script per verificare il bug dell'admin login
const auth = new AuthenticationService();

// Registra un admin
auth.register('admin', 'admin123', 'admin@test.com');

// Testa il login con password corretta
const result1 = auth.login('admin', 'admin123');
console.log('Login con password corretta:', result1.success);

// Testa il login con password sbagliata
const result2 = auth.login('admin', 'wrong_password');
console.log('Login con password sbagliata:', result2.success);

// Il bug è presente se il secondo test ritorna false quando dovrebbe essere true
// (o viceversa, dipende dalla natura del bug)
process.exit(result1.success && !result2.success ? 0 : 1);
EOF

# Usa questo script con git bisect run per automazione completa
git bisect run node test_admin_login.js
```

**Documenta il risultato del bisect:**
```
Commit che ha introdotto il bug admin: ____________________
Messaggio del commit: __________________________________
Autore: _______________________________________________
Data: _________________________________________________
```

---

## Parte 5: Rapporto Detective (10 minuti)

### Scrivi il Rapporto di Investigazione

**Modello di Rapporto Forense:**

```
RAPPORTO DI INVESTIGAZIONE TECNICA
===================================

Caso: Bug Multiple nell'Applicazione E-commerce
Detective: [Il tuo nome]
Data: [Data odierna]

SOMMARIO ESECUTIVO:
Durante l'investigazione sono stati identificati 4 bug critici 
introdotti in commit specifici tra [data] e [data].

BUG IDENTIFICATI:

1. Bug Autenticazione Admin
   - Commit: ____________
   - Autore: ____________
   - Impatto: ___________
   - Causa: _____________

2. Bug Conversione USD
   - Commit: ____________
   - Autore: ____________
   - Impatto: ___________
   - Causa: _____________

3. Bug Sconti Duplicati
   - Commit: ____________
   - Autore: ____________
   - Impatto: ___________
   - Causa: _____________

4. Bug Sessioni Infinite
   - Commit: ____________
   - Autore: ____________
   - Impatto: ___________
   - Causa: _____________

PATTERN IDENTIFICATI:
1. _________________________________________________
2. _________________________________________________
3. _________________________________________________

RACCOMANDAZIONI:
1. _________________________________________________
2. _________________________________________________
3. _________________________________________________

COMANDI GIT UTILIZZATI PER L'INVESTIGAZIONE:
1. git log --grep="pattern" (ricerca nei messaggi)
2. git log -S "codice" (ricerca nelle modifiche)
3. git bisect (identificazione automatica bug)
4. git blame (identificazione autore righe)
5. git show (analisi commit specifici)

TEMPO TOTALE INVESTIGAZIONE: _____ minuti
```

---

## Soluzioni di Riferimento

<details>
<summary>Clicca per vedere le soluzioni</summary>

### Bug 1: Autenticazione Admin
**Problema:** Condizione OR invece di AND nel controllo password
```javascript
// Problematico:
if (username === 'admin' || !this.verifyPassword(password, user.password)) {
    return { success: false, message: 'Invalid credentials' };
}

// Corretto:
if (!this.verifyPassword(password, user.password)) {
    return { success: false, message: 'Invalid credentials' };
}
```

### Bug 2: Conversione USD
**Problema:** Formula sbagliata per USD
```javascript
// Problematico:
if (fromCurrency === 'USD') {
    return amount * fromRate * toRate;
}

// Corretto:
return (amount / fromRate) * toRate;
```

### Bug 3: Sconti Duplicati
**Problema:** Push sempre dello sconto senza controllo duplicati

### Bug 4: Sessioni Infinite
**Problema:** Controllo di scadenza commentato
```javascript
// Problematico: il controllo è commentato
// if (new Date() > session.expiresAt) {
//   this.sessions.delete(sessionId);
//   return false;
// }
```

</details>

---

## Criteri di Valutazione

- **Identificazione Corretta dei Bug** (40%): Tutti i 4 bug sono stati identificati correttamente
- **Uso Appropriato degli Strumenti Git** (30%): Utilizzo efficace di log, show, bisect, blame
- **Analisi dei Pattern** (20%): Identificazione di pattern nei bug e nei commit
- **Qualità del Rapporto** (10%): Completezza e chiarezza del rapporto finale

---

**Navigazione:**
- [← Esercizio Precedente: Esplorazione Repository](01-esplorazione-repository.md)
- [→ Prossimo Esercizio: Personalizzazione Log](03-personalizzazione-log.md)
- [↑ Torna all'Indice del Modulo](../README.md)
