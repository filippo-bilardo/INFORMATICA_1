# 04 - Workflow con Staging Area

## 📖 Pattern di Utilizzo

La staging area diventa potente quando la usi come parte di workflow ben definiti. Questa guida presenta pattern professionali per massimizzare la produttività e la qualità del codice.

## 🎯 Workflow Fondamentali

### 1. Feature Development Workflow
```bash
# 1. Inizio feature
git checkout -b feature/user-authentication

# 2. Sviluppo incrementale
echo "login form HTML" > login.html
git add login.html
git commit -m "Add login form structure"

echo "login validation JS" > login.js  
git add login.js
git commit -m "Add login validation logic"

echo "login styles" > login.css
git add login.css
git commit -m "Style login form"

# 3. Integrazione
git checkout main
git merge feature/user-authentication
```

### 2. Bug Fix Workflow
```bash
# 1. Identifica il problema
git checkout -b bugfix/calculation-error

# 2. Fix + Test in un commit
git add calculator.js tests/calculator.test.js
git commit -m "Fix division by zero error

- Add validation in divide function
- Add test cases for edge cases
- Update error messages"

# 3. Deploy rapido
git checkout main
git cherry-pick bugfix-commit-hash
```

### 3. Refactoring Workflow
```bash
# 1. Refactoring graduale
git add -p legacy-code.js    # Solo rename variabili
git commit -m "Rename variables for clarity"

git add -p legacy-code.js    # Solo extract functions
git commit -m "Extract utility functions"

git add -p legacy-code.js    # Solo improve comments
git commit -m "Add documentation comments"
```

## 🚀 Pattern Avanzati

### 1. Atomic Commits Strategy
```bash
# Ogni commit = una unità logica indivisibile

# BAD: commit misto
git add user.js admin.js database.js
git commit -m "Various updates"

# GOOD: commit atomici
git add user.js
git commit -m "Add user profile validation"

git add admin.js  
git commit -m "Implement admin permissions"

git add database.js
git commit -m "Optimize user queries"
```

### 2. Story-Driven Development
```bash
# User Story: "As a user, I want to reset my password"

# Commit 1: Backend
git add src/auth/password-reset.js
git commit -m "Add password reset endpoint

- Generate secure reset tokens
- Send reset email
- Validate token expiration"

# Commit 2: Frontend
git add src/components/PasswordReset.vue
git commit -m "Add password reset form

- Input validation
- Error handling
- Success feedback"

# Commit 3: Integration
git add src/router/auth.js src/api/auth.js
git commit -m "Connect password reset flow

- Add reset route
- Integrate API calls
- Handle edge cases"
```

### 3. Documentation-First Workflow
```bash
# 1. Documenta prima di codificare
echo "# User Authentication API" > docs/auth.md
git add docs/auth.md
git commit -m "Document auth API requirements"

# 2. Implementa seguendo la documentazione
git add src/auth.js
git commit -m "Implement auth API as documented"

# 3. Aggiorna documentazione se necessario
git add docs/auth.md src/auth.js
git commit -m "Update auth docs with implementation details"
```

## 🎨 Tecniche di Staging

### 1. Selective Staging con Patch Mode
```bash
# File con modifiche multiple: user-service.js
# - Bug fix (righe 45-50)
# - Performance improvement (righe 100-120)  
# - New feature (righe 200-250)

# Commit 1: Solo bug fix
git add -p user-service.js
# Seleziona solo righe 45-50
git commit -m "Fix user validation bug"

# Commit 2: Solo performance
git add -p user-service.js  
# Seleziona solo righe 100-120
git commit -m "Optimize user lookup performance"

# Commit 3: Solo feature
git add user-service.js
# Remainder: new feature
git commit -m "Add user preference management"
```

### 2. Cross-File Logical Grouping
```bash
# Feature: Add shopping cart
# Files: cart.js, cart.css, cart.html, cart.test.js

# Commit logico completo
git add src/cart.js src/cart.html
git add styles/cart.css  
git add tests/cart.test.js
git commit -m "Implement shopping cart feature

- Cart component with add/remove items
- Responsive cart styling
- Comprehensive test coverage
- Integration with product catalog"
```

### 3. Progressive Enhancement
```bash
# Sviluppo a layers

# Layer 1: Core functionality
git add core.js
git commit -m "Add core cart functionality"

# Layer 2: UI enhancements  
git add ui-enhancements.js cart.css
git commit -m "Add cart UI improvements"

# Layer 3: Advanced features
git add advanced-features.js
git commit -m "Add cart persistence and sharing"
```

## 🔄 Workflow per Team

### 1. Pre-Push Workflow
```bash
# Prima di push, sempre:
git status                    # Verifica stato locale
git add -p                    # Review selective delle modifiche
git diff --staged             # Review finale
git commit -m "..."           # Commit con messaggio chiaro
git pull --rebase origin main # Integra modifiche remote
git push origin feature-branch
```

### 2. Code Review Preparation
```bash
# Prepara branch per review
git log --oneline main..HEAD  # Vedi commit da revieware

# Se necessario, cleanup commit history
git rebase -i main            # Interactive rebase
# Combina, riordina, migliora commit messages

# Assicurati che ogni commit sia self-contained
git show commit-hash          # Review singoli commit
```

### 3. Collaboration Workflow
```bash
# Sviluppatore A
git add feature-A.js
git commit -m "Implement feature A foundation"
git push origin shared-feature

# Sviluppatore B (in parallelo)
git pull origin shared-feature
git add feature-B.js
git commit -m "Add feature B that extends A"
git push origin shared-feature

# Merge coordination
git add integration.js
git commit -m "Integrate features A and B"
```

## 🛠️ Tools e Automazione

### 1. Pre-commit Hooks
```bash
# .git/hooks/pre-commit
#!/bin/bash
# Automatic checks before commit

# Run linter
npm run lint
if [ $? -ne 0 ]; then
    echo "Linting failed. Fix errors before commit."
    exit 1
fi

# Run tests  
npm test
if [ $? -ne 0 ]; then
    echo "Tests failed. Fix tests before commit."
    exit 1
fi

# Check staged files only
git diff --staged --name-only | grep -E "\.(js|ts)$" | xargs eslint
```

### 2. Smart Add Aliases
```bash
# Aggiungi al .gitconfig
[alias]
    # Add modified files only (no new files)
    addu = add -u
    
    # Interactive add  
    addi = add -i
    
    # Add with patch mode
    addp = add -p
    
    # See what would be added
    addry = add --dry-run
    
    # Smart add (excludes common temp files)
    adds = "!git add . && git reset *.log *.tmp .DS_Store"
```

### 3. Staging Status Monitoring
```bash
# Custom script: staging-status.sh
#!/bin/bash
echo "=== STAGING AREA STATUS ==="
echo "Files staged for commit:"
git diff --staged --name-only

echo -e "\nFiles modified but not staged:"  
git diff --name-only

echo -e "\nUntracked files:"
git ls-files --others --exclude-standard

echo -e "\nCommit readiness:"
if git diff --staged --quiet; then
    echo "❌ Nothing staged for commit"
else
    echo "✅ Ready to commit"
fi
```

## 📊 Metrics e Quality Control

### 1. Commit Quality Metrics
```bash
# Analisi dimensione commit
git log --oneline --shortstat | grep "files changed" | head -10

# Commit con troppi file (code smell)
git log --oneline --numstat | awk '{print NF-2 " " $0}' | sort -nr | head -10

# Frequenza di commit per file
git log --name-only --pretty=format: | sort | uniq -c | sort -nr
```

### 2. Staging Best Practices Check
```bash
# Script di validazione
#!/bin/bash
# staging-check.sh

echo "🔍 Staging Area Quality Check"

# Check 1: Dimensione ragionevole
STAGED_FILES=$(git diff --staged --name-only | wc -l)
if [ $STAGED_FILES -gt 10 ]; then
    echo "⚠️  Warning: $STAGED_FILES files staged (consider smaller commits)"
fi

# Check 2: File types consistency
STAGED_TYPES=$(git diff --staged --name-only | sed 's/.*\.//' | sort | uniq)
echo "📁 File types in staging: $STAGED_TYPES"

# Check 3: Presence di tests
STAGED_SRC=$(git diff --staged --name-only | grep -E "\.(js|ts|py)$" | grep -v test)
STAGED_TESTS=$(git diff --staged --name-only | grep -E "test\.|spec\.")

if [ -n "$STAGED_SRC" ] && [ -z "$STAGED_TESTS" ]; then
    echo "⚠️  Warning: Source files staged without tests"
fi

echo "✅ Staging check complete"
```

## 🎯 Best Practices Riassunte

### 1. **Commit Frequency**
```bash
# GOOD: Commit frequenti e piccoli
git add single-feature.js
git commit -m "Add user validation"    # 30 minuti di lavoro

# AVOID: Commit rari e grandi  
git add .                              # 3 ore di lavoro misto
git commit -m "Various updates"
```

### 2. **Logical Consistency**
```bash
# GOOD: Coerenza logica
git add user-model.js user-controller.js user-routes.js
git commit -m "Implement complete user CRUD operations"

# AVOID: Mix di funzionalità
git add user.js product.js admin.js
git commit -m "Updates"
```

### 3. **Review-Friendly Staging**
```bash
# GOOD: Un concetto per commit
git add authentication.js
git commit -m "Add JWT authentication

- Generate and validate tokens
- Middleware for protected routes  
- Error handling for invalid tokens"

# Facilita il code review
```

## 🧠 Quiz di Controllo

### Domanda 1
Stai lavorando su un file che contiene un bug fix e una nuova feature. Come gestisci il commit?

**A)** `git add file.js && git commit -m "Updates"`  
**B)** `git add -p file.js` e fai due commit separati  
**C)** Aspetti di finire tutto e fai un commit unico  

### Domanda 2
Prima di fare push, quale workflow è migliore?

**A)** `git add . && git commit -m "..." && git push`  
**B)** `git status → git add -p → git diff --staged → git commit → git pull → git push`  
**C)** `git commit -a -m "..." && git push`  

### Domanda 3
Come organizzi commit per una user story complessa?

**A)** Un commit per tutta la story  
**B)** Un commit per ogni file modificato  
**C)** Un commit per ogni componente logico (backend, frontend, tests, docs)  

---

**Risposte**: 1-B, 2-B, 3-C

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./03-git-reset.md)
- [➡️ Esempi Pratici](../esempi/01-staging-selettivo.md)

---

**Prossimo passo**: [Esempi Pratici](../esempi/01-staging-selettivo.md) - Implementazione concreta dei workflow
