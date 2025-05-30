# Esercizio 03: Conventional Commits Workshop

## Obiettivo
Padroneggiare il sistema Conventional Commits attraverso pratica intensiva, esempi reali e implementazione di workflow automatizzati.

## Durata Stimata
60-90 minuti

## Teoria Rapida: Conventional Commits

### Formato Base
```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

### Tipi Principali
- **feat**: Nuova funzionalità
- **fix**: Correzione bug
- **docs**: Modifiche documentazione
- **style**: Modifiche formattazione (non funzionali)
- **refactor**: Refactoring codice
- **test**: Aggiunta/modifica test
- **chore**: Manutenzione/build

### Breaking Changes
- Aggiungi `!` dopo il tipo: `feat!:`
- Oppure nel footer: `BREAKING CHANGE:`

## Setup Progetto Workshop

```bash
# Creare progetto demo
mkdir ecommerce-app
cd ecommerce-app
git init

# Struttura iniziale
mkdir -p src/{components,utils,services}
mkdir -p tests/{unit,integration}
mkdir docs

# File iniziali
echo "# E-commerce Application" > README.md
echo "node_modules/" > .gitignore
echo "dist/" >> .gitignore

git add .
git commit -m "chore: initial project setup

- Create basic folder structure
- Add README and gitignore
- Setup development environment"
```

## Parte 1: Tipi di Commit Fondamentali

### Esercizio 1.1: Feature Commits
Implementa queste funzionalità seguendo conventional commits:

```bash
# 1. Sistema di autenticazione
cat > src/services/auth.js << 'EOF'
export class AuthService {
  constructor() {
    this.users = new Map();
  }

  register(email, password) {
    if (this.users.has(email)) {
      throw new Error('User already exists');
    }
    this.users.set(email, { password, createdAt: new Date() });
    return { success: true, userId: email };
  }

  login(email, password) {
    const user = this.users.get(email);
    if (!user || user.password !== password) {
      throw new Error('Invalid credentials');
    }
    return { success: true, token: 'jwt-token-' + Date.now() };
  }
}
EOF

git add src/services/auth.js
```

**Compito**: Scrivi il commit message seguendo conventional commits.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "feat(auth): add user authentication service

- Implement user registration with email/password
- Add login functionality with credential validation
- Store users in memory Map for demo purposes
- Return JWT-like tokens for successful login
- Throw meaningful errors for edge cases"
```
</details>

### Esercizio 1.2: Bug Fix Commits
Correggi questi bug:

```bash
# Introdurre un bug nel codice precedente
sed -i 's/this.users.set(email, { password, createdAt: new Date() });/this.users.set(email, { password });/' src/services/auth.js

# Poi correggerlo
sed -i 's/this.users.set(email, { password });/this.users.set(email, { password, createdAt: new Date(), isActive: true });/' src/services/auth.js

git add src/services/auth.js
```

**Compito**: Commit della correzione.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "fix(auth): add missing user properties in registration

- Add createdAt timestamp for user tracking
- Add isActive flag for account management
- Ensures complete user object creation"
```
</details>

### Esercizio 1.3: Documentation Commits
Aggiungi documentazione:

```bash
# Creare documentazione API
cat > docs/auth-api.md << 'EOF'
# Authentication API

## Overview
Service for user registration and authentication.

## Methods

### register(email, password)
- **Parameters**: email (string), password (string)
- **Returns**: {success: boolean, userId: string}
- **Throws**: Error if user already exists

### login(email, password)
- **Parameters**: email (string), password (string)  
- **Returns**: {success: boolean, token: string}
- **Throws**: Error for invalid credentials

## Example Usage
```javascript
const auth = new AuthService();
const result = auth.register('user@example.com', 'password123');
```
EOF

git add docs/auth-api.md
```

**Compito**: Commit della documentazione.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "docs(auth): add authentication API documentation

- Document register and login methods
- Include parameter descriptions and return values
- Add usage examples and error handling
- Improve developer experience with clear API docs"
```
</details>

## Parte 2: Scope e Specificità

### Esercizio 2.1: Scope Dettagliati
Aggiungi funzionalità con scope specifici:

```bash
# Componente carrello
cat > src/components/cart.js << 'EOF'
export class ShoppingCart {
  constructor() {
    this.items = [];
    this.total = 0;
  }

  addItem(product, quantity = 1) {
    const existingItem = this.items.find(item => item.id === product.id);
    if (existingItem) {
      existingItem.quantity += quantity;
    } else {
      this.items.push({ ...product, quantity });
    }
    this.calculateTotal();
  }

  removeItem(productId) {
    this.items = this.items.filter(item => item.id !== productId);
    this.calculateTotal();
  }

  calculateTotal() {
    this.total = this.items.reduce((sum, item) => 
      sum + (item.price * item.quantity), 0);
  }
}
EOF

git add src/components/cart.js
```

**Compito**: Commit con scope appropriato.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "feat(cart): implement shopping cart functionality

- Add ShoppingCart class with item management
- Support adding items with quantity control
- Implement item removal by product ID  
- Auto-calculate total price on changes
- Handle duplicate items by updating quantity"
```
</details>

### Esercizio 2.2: Multi-scope Changes
Modifica che tocca più aree:

```bash
# Test per carrello
cat > tests/unit/cart.test.js << 'EOF'
import { ShoppingCart } from '../../src/components/cart.js';

describe('ShoppingCart', () => {
  let cart;

  beforeEach(() => {
    cart = new ShoppingCart();
  });

  test('should add items correctly', () => {
    const product = { id: 1, name: 'Test Product', price: 10.99 };
    cart.addItem(product, 2);
    
    expect(cart.items).toHaveLength(1);
    expect(cart.items[0].quantity).toBe(2);
    expect(cart.total).toBe(21.98);
  });

  test('should remove items correctly', () => {
    const product = { id: 1, name: 'Test Product', price: 10.99 };
    cart.addItem(product);
    cart.removeItem(1);
    
    expect(cart.items).toHaveLength(0);
    expect(cart.total).toBe(0);
  });
});
EOF

# Aggiungere utility per test
cat > src/utils/test-helpers.js << 'EOF'
export function createMockProduct(overrides = {}) {
  return {
    id: Math.floor(Math.random() * 1000),
    name: 'Mock Product',
    price: 9.99,
    category: 'electronics',
    ...overrides
  };
}
EOF

git add tests/unit/cart.test.js src/utils/test-helpers.js
```

**Compito**: Commit che tocca test e utils.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "test(cart): add comprehensive shopping cart tests

- Add unit tests for cart item management
- Test adding items with quantity handling
- Test item removal and total calculation
- Create mock product utility for testing
- Ensure cart functionality reliability"
```
</details>

## Parte 3: Breaking Changes

### Esercizio 3.1: Breaking Change con !
Modifica che rompe l'API esistente:

```bash
# Modificare AuthService per richiedere validazione email
cat > src/services/auth.js << 'EOF'
export class AuthService {
  constructor() {
    this.users = new Map();
  }

  register(userInfo) {  // BREAKING: era register(email, password)
    const { email, password, firstName, lastName } = userInfo;
    
    if (!this.isValidEmail(email)) {
      throw new Error('Invalid email format');
    }
    
    if (this.users.has(email)) {
      throw new Error('User already exists');
    }
    
    this.users.set(email, { 
      password, 
      firstName,
      lastName,
      createdAt: new Date(), 
      isActive: true 
    });
    
    return { success: true, userId: email };
  }

  login(email, password) {
    const user = this.users.get(email);
    if (!user || user.password !== password) {
      throw new Error('Invalid credentials');
    }
    return { 
      success: true, 
      token: 'jwt-token-' + Date.now(),
      user: { email, firstName: user.firstName, lastName: user.lastName }
    };
  }

  isValidEmail(email) {
    return /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email);
  }
}
EOF

git add src/services/auth.js
```

**Compito**: Commit del breaking change.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "feat(auth)!: change register method signature

BREAKING CHANGE: register() now accepts an object instead of separate parameters

- Change register(email, password) to register(userInfo)
- Add firstName and lastName to user registration
- Implement email validation with regex
- Return user info in login response
- Improve API consistency with object parameters

Migration guide:
// Before
auth.register('user@example.com', 'password');

// After  
auth.register({
  email: 'user@example.com',
  password: 'password',
  firstName: 'John',
  lastName: 'Doe'
});"
```
</details>

### Esercizio 3.2: Breaking Change con Footer
Modifica del sistema di prezzi:

```bash
# Modificare ShoppingCart per supportare valute
cat > src/components/cart.js << 'EOF'
export class ShoppingCart {
  constructor(currency = 'USD') {
    this.items = [];
    this.total = 0;
    this.currency = currency;
    this.exchangeRates = { USD: 1, EUR: 0.85, GBP: 0.73 };
  }

  addItem(product, quantity = 1) {
    const existingItem = this.items.find(item => item.id === product.id);
    const convertedPrice = this.convertPrice(product.price, product.currency || 'USD');
    
    if (existingItem) {
      existingItem.quantity += quantity;
    } else {
      this.items.push({ 
        ...product, 
        quantity, 
        price: convertedPrice,
        originalPrice: product.price,
        originalCurrency: product.currency || 'USD'
      });
    }
    this.calculateTotal();
  }

  convertPrice(price, fromCurrency) {
    const usdPrice = price / this.exchangeRates[fromCurrency];
    return usdPrice * this.exchangeRates[this.currency];
  }

  calculateTotal() {
    this.total = this.items.reduce((sum, item) => 
      sum + (item.price * item.quantity), 0);
  }

  getFormattedTotal() {
    const symbols = { USD: '$', EUR: '€', GBP: '£' };
    return `${symbols[this.currency]}${this.total.toFixed(2)}`;
  }
}
EOF

git add src/components/cart.js
```

**Compito**: Commit con breaking change nel footer.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "feat(cart): add multi-currency support

- Add currency parameter to ShoppingCart constructor
- Implement automatic price conversion
- Store original price and currency information
- Add formatted total display with currency symbols
- Support USD, EUR, and GBP currencies

BREAKING CHANGE: ShoppingCart constructor now accepts currency parameter.
Default behavior unchanged (USD), but item objects now include additional
currency-related properties that may affect serialization."
```
</details>

## Parte 4: Workflow Automatizzato

### Esercizio 4.1: Setup Conventional Commits Validation
Creare script per validare commit messages:

```bash
# Script di validazione
cat > scripts/validate-commit.js << 'EOF'
#!/usr/bin/env node
const fs = require('fs');

const commitMsg = fs.readFileSync(process.argv[2], 'utf8').trim();

const conventionalPattern = /^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?!?: .{1,50}/;

if (!conventionalPattern.test(commitMsg)) {
  console.error('❌ Commit message does not follow Conventional Commits format!');
  console.error('Format: <type>[optional scope]: <description>');
  console.error('Example: feat(auth): add user registration');
  process.exit(1);
}

console.log('✅ Commit message follows Conventional Commits format');
EOF

chmod +x scripts/validate-commit.js
git add scripts/validate-commit.js
```

**Compito**: Commit dello script di validazione.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "chore(tools): add conventional commits validation script

- Create Node.js script to validate commit messages
- Check format against conventional commits pattern
- Provide helpful error messages and examples
- Make script executable for hook integration
- Improve development workflow consistency"
```
</details>

### Esercizio 4.2: Generazione Changelog
Creare script per changelog automatico:

```bash
# Script changelog
cat > scripts/generate-changelog.js << 'EOF'
#!/usr/bin/env node
const { execSync } = require('child_process');

function getCommitsSinceLastTag() {
  try {
    const lastTag = execSync('git describe --tags --abbrev=0', { encoding: 'utf8' }).trim();
    return execSync(`git log ${lastTag}..HEAD --oneline`, { encoding: 'utf8' });
  } catch {
    return execSync('git log --oneline', { encoding: 'utf8' });
  }
}

function parseCommits(commits) {
  const lines = commits.trim().split('\n').filter(line => line);
  const parsed = { features: [], fixes: [], others: [] };

  lines.forEach(line => {
    const [hash, ...messageParts] = line.split(' ');
    const message = messageParts.join(' ');
    
    if (message.startsWith('feat')) {
      parsed.features.push({ hash: hash.substring(0, 7), message });
    } else if (message.startsWith('fix')) {
      parsed.fixes.push({ hash: hash.substring(0, 7), message });
    } else {
      parsed.others.push({ hash: hash.substring(0, 7), message });
    }
  });

  return parsed;
}

function generateChangelog(commits) {
  let changelog = `# Changelog\n\n## [Unreleased]\n\n`;
  
  if (commits.features.length > 0) {
    changelog += `### ✨ Features\n\n`;
    commits.features.forEach(({ hash, message }) => {
      changelog += `- ${message} (${hash})\n`;
    });
    changelog += '\n';
  }

  if (commits.fixes.length > 0) {
    changelog += `### 🐛 Bug Fixes\n\n`;
    commits.fixes.forEach(({ hash, message }) => {
      changelog += `- ${message} (${hash})\n`;
    });
    changelog += '\n';
  }

  if (commits.others.length > 0) {
    changelog += `### 🔧 Other Changes\n\n`;
    commits.others.forEach(({ hash, message }) => {
      changelog += `- ${message} (${hash})\n`;
    });
  }

  return changelog;
}

const commits = getCommitsSinceLastTag();
const parsed = parseCommits(commits);
const changelog = generateChangelog(parsed);

console.log(changelog);
EOF

chmod +x scripts/generate-changelog.js
git add scripts/generate-changelog.js
```

**Compito**: Commit del generatore changelog.

<details>
<summary>📋 Soluzione</summary>

```bash
git commit -m "feat(tools): add automatic changelog generation

- Parse git commits since last tag
- Categorize commits by type (feat, fix, others)
- Generate markdown changelog format
- Include commit hashes for reference
- Support projects without existing tags
- Automate release documentation process"
```
</details>

## Parte 5: Validazione e Test

### Test del Workflow Completo
Esegui questi test per verificare la comprensione:

```bash
# 1. Test validazione (dovrebbe fallire)
echo "add new feature" > test-commit-msg.txt
node scripts/validate-commit.js test-commit-msg.txt

# 2. Test validazione (dovrebbe passare)  
echo "feat: add new feature" > test-commit-msg.txt
node scripts/validate-commit.js test-commit-msg.txt

# 3. Generare changelog completo
node scripts/generate-changelog.js > CHANGELOG.md
cat CHANGELOG.md

# 4. Commit finale
git add CHANGELOG.md
git commit -m "docs: add generated project changelog

- Include all features and fixes from development
- Categorize changes by type for clarity
- Provide commit references for traceability"
```

### Verifica Cronologia
```bash
# Vedere tutti i commit con formato conventional
git log --oneline --grep="^feat" --grep="^fix" --grep="^docs" --grep="^chore" --grep="^test" --basic-regexp

# Vedere breaking changes
git log --grep="BREAKING CHANGE" --grep="!:" --basic-regexp

# Contare commit per tipo
echo "Features: $(git log --oneline --grep="^feat" --basic-regexp | wc -l)"
echo "Fixes: $(git log --oneline --grep="^fix" --basic-regexp | wc -l)"
echo "Docs: $(git log --oneline --grep="^docs" --basic-regexp | wc -l)"
```

## Quiz di Verifica

### Domande Pratiche

1. **Quale messaggio è corretto per aggiungere test di sicurezza?**
   - a) `add security tests`
   - b) `test: add security validation tests`
   - c) `test(security): add validation test suite`
   - d) `tests: security validation`

<details>
<summary>Risposta</summary>
**c) test(security): add validation test suite** - Include tipo, scope e descrizione chiara.
</details>

2. **Come indicheresti un breaking change che modifica l'API di pagamento?**
   - a) `feat(payment): change API structure`
   - b) `feat(payment)!: restructure payment API`
   - c) `BREAKING: payment API changes`
   - d) `major(payment): API changes`

<details>
<summary>Risposta</summary>
**b) feat(payment)!: restructure payment API** - Usa il punto esclamativo per indicare breaking change.
</details>

## Risultati Attesi

Alla fine di questo workshop dovresti avere:

### Repository Completo
- ✅ Cronologia pulita con conventional commits
- ✅ Breaking changes ben documentati
- ✅ Scope appropriati per ogni modifica
- ✅ Script di validazione funzionanti
- ✅ Changelog automatico generato

### Competenze Acquisite
- ✅ Padronanza del formato conventional commits
- ✅ Comprensione di quando usare ogni tipo
- ✅ Gestione di breaking changes
- ✅ Automazione del workflow
- ✅ Generazione documentazione automatica

## Prossimi Passi

1. **Integrazione CI/CD**: Setup automatico in GitHub Actions
2. **Semantic Versioning**: Collegare conventional commits alle versioni
3. **Release Automation**: Generazione automatica release
4. **Team Adoption**: Condivisione best practices nel team

## Risorse Aggiuntive

- [Conventional Commits Specification](https://www.conventionalcommits.org/)
- [Guida 05: Conventional Commits](../guide/05-conventional-commits.md)
- [Esempio 03: Automazione Commit](../esempi/03-automazione-commit.md)

---
[⬅️ Esercizio 02](./02-pratica-amend-reset.md) | [🏠 Modulo 09](../README.md) | [➡️ Modulo 10](../../10-Navigare-tra-Commit/README.md)
