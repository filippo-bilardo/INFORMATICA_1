# 02 - Messaggi di Commit Efficaci

## 📋 Scenario

Stai lavorando su un e-commerce e devi implementare varie funzionalità. Questo esempio dimostra come scrivere messaggi di commit chiari, informativi e seguire le convenzioni professionali.

## 🎯 Obiettivo

Apprendere le best practices per:
- **Conventional Commits** per team professionali
- **Messaggi descrittivi** che aiutano il debug futuro
- **Struttura dei commit** per release notes automatiche
- **Evitare errori comuni** nei messaggi

## 🛠️ Setup del Progetto

```bash
# Setup progetto e-commerce
mkdir ecommerce-platform
cd ecommerce-platform
git init

# Configura autore (importante per messaggi professionali)
git config user.name "Mario Rossi"
git config user.email "mario.rossi@company.com"

# Struttura iniziale
mkdir -p src/{components,utils,services}
mkdir -p tests docs

# Primo commit di setup
touch README.md
echo "# E-commerce Platform" > README.md
git add README.md
git commit -m "feat: initialize e-commerce platform project

- Setup basic project structure
- Add initial README
- Configure Git repository

Refs: ECOM-001"
```

## ✅ Esempi di Messaggi Corretti

### 1. Nuove Funzionalità (feat)
```bash
# Feature semplice
git commit -m "feat: add product search functionality"

# Feature con dettagli
git commit -m "feat(search): implement advanced product filtering

- Add filters by category, price range, brand
- Implement debounced search input
- Add sorting options (price, rating, date)
- Include pagination for large result sets

Performance: Search results load 40% faster
Tested: Chrome, Firefox, Safari
Closes: ECOM-123"

# Feature con breaking change
git commit -m "feat!: migrate to new payment API

BREAKING CHANGE: Payment configuration now requires API v3 format.
Update config files from payment.v2.json to payment.v3.json

Migration guide: docs/payment-migration.md
Refs: ECOM-456"
```

### 2. Bug Fix (fix)
```bash
# Bug fix semplice
git commit -m "fix: resolve checkout button not responding on mobile"

# Bug fix dettagliato
git commit -m "fix(cart): prevent duplicate items when adding products quickly

Issue: Double-clicking 'Add to Cart' created duplicate entries
Root cause: Missing debounce on click handler
Solution: Added 300ms debounce and loading state

Testing:
- Verified on mobile devices
- Tested with slow network conditions
- Confirmed cart state consistency

Fixes: #892
Tested-by: QA Team"

# Hotfix critico
git commit -m "fix!: resolve payment processing security vulnerability

SECURITY: Fixed SQL injection in payment validation
Impact: High - affects all payment transactions
Action: Immediate deployment required

Details:
- Sanitized all payment form inputs
- Added prepared statements for database queries
- Implemented additional validation layer

CVE: Pending
Reviewed-by: Security Team
Priority: Critical"
```

### 3. Documentazione (docs)
```bash
# Documentazione API
git commit -m "docs: add comprehensive API documentation for checkout process

- Document all checkout endpoints
- Include request/response examples
- Add error handling scenarios
- Include rate limiting information

Format: OpenAPI 3.0 specification
Location: docs/api/checkout.yaml"

# README update
git commit -m "docs(readme): update installation and setup instructions

- Add Node.js version requirements
- Include Docker setup steps
- Update environment variables list
- Add troubleshooting section

Tested on: Ubuntu 20.04, macOS Big Sur, Windows 10"
```

### 4. Refactoring (refactor)
```bash
# Refactoring di codice
git commit -m "refactor(auth): simplify user authentication flow

- Consolidated login/register components
- Extracted common validation logic
- Reduced code duplication by 35%
- Improved type safety with TypeScript

Performance: 15% faster authentication
No functional changes
Maintains backward compatibility"

# Riorganizzazione file
git commit -m "refactor: reorganize component structure for better maintainability

src/components/
├── common/        (shared components)
├── pages/         (page-level components)
├── forms/         (form components)
└── layout/        (layout components)

- Improved import paths
- Better logical grouping
- Easier component discovery"
```

### 5. Styling (style)
```bash
# Formattazione codice
git commit -m "style: format code with Prettier and ESLint

- Apply consistent formatting across all JS files
- Fix ESLint warnings and errors
- Update .prettierrc configuration
- Add pre-commit hooks for automatic formatting

No functional changes"

# Aggiornamenti CSS
git commit -m "style(ui): improve responsive design for mobile checkout

- Optimize button sizes for touch interaction
- Improve form spacing on small screens
- Enhance color contrast for accessibility
- Add smooth transitions for better UX

Tested: iPhone 12, Samsung Galaxy S21, iPad Air"
```

### 6. Test (test)
```bash
# Aggiunta test
git commit -m "test: add comprehensive unit tests for shopping cart logic

Coverage increased from 65% to 85%

Added tests for:
- Add/remove items functionality
- Price calculation with discounts
- Inventory validation
- Cart persistence across sessions

Framework: Jest + React Testing Library"

# Fix test
git commit -m "test(e2e): fix flaky checkout process test

- Added proper wait conditions for payment processing
- Increased timeout for slow network scenarios
- Mock external payment API calls
- Stabilized CI pipeline (0 flaky failures in 50 runs)"
```

### 7. Manutenzione (chore)
```bash
# Aggiornamento dipendenze
git commit -m "chore: update dependencies to latest stable versions

- React 18.2.0 → 18.3.1
- Next.js 13.4.1 → 13.5.2
- TypeScript 5.0.4 → 5.1.6

Security updates:
- Fixed 3 high-severity vulnerabilities
- No breaking changes detected

Tested: All existing functionality works correctly"

# Configurazione build
git commit -m "chore(build): optimize webpack configuration for production

- Enable tree shaking for smaller bundles
- Add compression plugins
- Configure code splitting for better caching
- Bundle size reduced by 25%

Build time: 45s → 32s
Bundle size: 2.1MB → 1.6MB"
```

## ❌ Esempi di Messaggi Scorretti

### Messaggi Troppo Vaghi
```bash
# ❌ Non informativi
git commit -m "fix"
git commit -m "update"
git commit -m "changes"
git commit -m "stuff"
git commit -m "wip"

# ✅ Specifici e informativi
git commit -m "fix: resolve product image loading on Safari"
git commit -m "feat: update user profile validation rules"
git commit -m "refactor: restructure payment processing logic"
```

### Messaggi Troppo Tecnici
```bash
# ❌ Solo dettagli tecnici
git commit -m "changed line 42 in user.js from === to =="
git commit -m "moved function from utils.js to helpers.js"

# ✅ Spiegano il "perché"
git commit -m "fix: use loose equality for form validation compatibility
  
Changed === to == for form validation to handle string/number conversion
automatically. This resolves validation failures when comparing form 
inputs (strings) with numeric values."

git commit -m "refactor: relocate validation helpers for better organization

Moved validation functions to helpers.js to create logical separation
between data utilities and validation logic."
```

### Messaggi con Typo/Errori
```bash
# ❌ Errori grammaticali e typo
git commit -m "fixs user cant login"
git commit -m "add new fature for shopping"
git commit -m "BREAKING: login system"

# ✅ Corretti e professionali  
git commit -m "fix: resolve user login authentication issues"
git commit -m "feat: add new shopping cart management features"
git commit -m "feat!: implement new secure login system

BREAKING CHANGE: Old authentication tokens no longer valid."
```

## 🎨 Template e Convenzioni

### Template Personale
Crea un template in `~/.gitmessage`:

```bash
# Tipo(scope): Descrizione breve (max 50 caratteri)
#
# Corpo del messaggio (wrappa a 72 caratteri)
# - Spiega cosa e perché, non come
# - Usa presente imperativo: "add" non "added" o "adds"
# - Include contesto necessario per comprendere la modifica
#
# Footer (opzionale)
# - Breaking changes: BREAKING CHANGE: description
# - Issues: Closes #123, Fixes #456
# - Reviewed-by: Name <email>

# Tipi validi:
# feat:     Nuova funzionalità
# fix:      Bug fix
# docs:     Solo documentazione
# style:    Formattazione (nessun cambio funzionale)
# refactor: Refactoring (nessun bug fix o nuova feature)
# test:     Aggiunta/modifica test
# chore:    Manutenzione/build/dipendenze
```

Attiva il template:
```bash
git config --global commit.template ~/.gitmessage
```

### Hook per Validazione
Crea `.git/hooks/commit-msg`:

```bash
#!/bin/sh
# Valida formato conventional commits

commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! head -1 "$1" | grep -qE "$commit_regex"; then
    echo "❌ Formato commit non valido!"
    echo ""
    echo "Usa il formato: <tipo>(<scope>): <descrizione>"
    echo ""
    echo "Tipi validi: feat, fix, docs, style, refactor, test, chore"
    echo "Esempio: feat(auth): add OAuth login support"
    echo ""
    exit 1
fi

# Verifica lunghezza prima riga
if [ $(head -1 "$1" | wc -c) -gt 51 ]; then
    echo "❌ Prima riga troppo lunga (max 50 caratteri)"
    exit 1
fi

echo "✅ Formato commit valido"
```

Rendi eseguibile:
```bash
chmod +x .git/hooks/commit-msg
```

## 💡 Workflow con Messaggi Efficaci

### 1. Pianificazione Pre-Commit
```bash
# Prima di committare, rispondi a queste domande:
# - Cosa cambia questa modifica?
# - Perché è necessaria?
# - Quali effetti ha sugli utenti?
# - Rompe qualcosa (breaking change)?

# Esempio di workflow
git status  # Cosa stai committando?
git diff --staged  # Verifica le modifiche
# Scrivi messaggio seguendo conventional commits
git commit -m "feat(cart): add persistent shopping cart functionality

- Cart items now persist across browser sessions
- Implemented localStorage with encryption
- Added automatic cleanup after 30 days
- Improved cart performance by 25%

Closes: #234"
```

### 2. Commit Multipli Logici
```bash
# ❌ Un singolo commit gigante
git add .
git commit -m "implement user system"

# ✅ Commit logicamente separati
git add src/models/user.js
git commit -m "feat(models): add User model with validation"

git add src/controllers/auth.js  
git commit -m "feat(auth): implement user authentication controller"

git add src/routes/users.js
git commit -m "feat(routes): add user management API endpoints"

git add tests/user.test.js
git commit -m "test(user): add comprehensive user model tests"
```

### 3. Messaggi per Team
```bash
# Include informazioni utili per il team
git commit -m "fix(payment): resolve Stripe webhook timeout issues

Issue: Webhook processing taking >30s causing timeouts
Solution: Implemented background job processing with Redis
Impact: 99.9% webhook success rate (was 85%)

Performance:
- Webhook response: 30s → 200ms  
- Background processing: <5s average

Monitoring: Added CloudWatch alerts for queue depth
Rollback plan: Feature flag 'async_webhooks' for instant disable

Tested-by: @qa-team
Reviewed-by: @payment-team-lead
Closes: PAYMENT-567"
```

## 🎓 Quiz di Verifica

1. **Qual è la lunghezza massima consigliata per la prima riga del commit?**
2. **Quando usi "feat!" invece di "feat"?**
3. **Cosa va nel footer di un messaggio di commit?**

### Risposte
1. **50 caratteri** per compatibilità con interfacce Git
2. **Breaking change** - quando la modifica rompe compatibilità
3. **Issue references, breaking changes, reviewer tags, metadata**

## 🔗 Comandi Correlati

- `git log --oneline` - Vedere cronologia messaggi
- `git commit --amend` - Modificare ultimo messaggio
- `git rebase -i` - Modificare messaggi storici
- `git show --stat` - Vedere dettagli commit

## 📚 Risorse Aggiuntive

- [Conventional Commits](https://www.conventionalcommits.org/)
- [How to Write Good Commit Messages](https://chris.beams.io/posts/git-commit/)
- [Semantic Versioning](https://semver.org/)
- [Git Hooks Documentation](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)

---

**Prossimo**: [03 - Gestione File Progetto](./03-gestione-file-progetto.md) - Gestire file in progetti complessi
