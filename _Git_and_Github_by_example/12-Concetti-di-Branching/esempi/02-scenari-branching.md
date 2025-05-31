# 02 - Scenari di Branching nel Mondo Reale

## 🎯 Obiettivo
Esplorare scenari pratici di branching che riflettono situazioni reali di sviluppo software, dall'individuale al team enterprise.

## 📋 Scenari di Apprendimento

### Scenario 1: Sviluppatore Singolo - Feature Development

#### Contesto del Progetto
Stai sviluppando un'applicazione todo list e vuoi aggiungere una nuova funzionalità di categorizzazione senza compromettere la versione stabile.

```bash
# Setup progetto
mkdir todo-app-branching
cd todo-app-branching
git init

# Versione base stabile
echo "# Todo App v1.0" > README.md
echo "function addTodo(task) { /* basic implementation */ }" > app.js
echo "body { background: white; }" > style.css
git add .
git commit -m "v1.0: Basic todo functionality"
```

#### Branch Strategy per Feature
```bash
# Creiamo branch per nuova feature
git checkout -b feature/categories

# Sviluppo incrementale
echo "function createCategory(name) { /* implementation */ }" >> app.js
git add app.js
git commit -m "Add category creation function"

echo ".category-tag { color: blue; }" >> style.css
git add style.css
git commit -m "Add category styling"

echo "function assignCategory(todoId, categoryId) { /* implementation */ }" >> app.js
git add app.js
git commit -m "Add category assignment"

# Visualizzazione progresso
git log --oneline --graph --all
```

#### Testing e Refinement
```bash
# Branch per testing specifico
git checkout -b feature/categories-testing
echo "/* Test cases for categories */" > tests.js
git add tests.js
git commit -m "Add category tests"

# Torna al feature branch principale
git checkout feature/categories
# Merge dei test se soddisfacenti
git merge feature/categories-testing
git branch -d feature/categories-testing
```

### Scenario 2: Team Piccolo - Hotfix Urgente

#### Contesto Critico
Il team ha rilevato un bug critico in produzione mentre si sta sviluppando la versione 2.0.

```bash
# Setup scenario team
mkdir team-hotfix-scenario
cd team-hotfix-scenario
git init

# Stato produzione attuale (main)
echo "# App v1.5 - Production" > README.md
echo "function calculateTotal(items) { return items.reduce((a,b) => a + b.price, 0); }" > calculator.js
git add .
git commit -m "v1.5: Production release"
git tag v1.5

# Sviluppo v2.0 in corso
git checkout -b develop
echo "// New features for v2.0" >> calculator.js
echo "function advancedCalculation() { /* new feature */ }" >> calculator.js
git add calculator.js
git commit -m "WIP: Advanced calculation features"

# ALERT: Bug critico scoperto in produzione!
# calculateTotal non gestisce array vuoti
```

#### Hotfix Workflow
```bash
# Hotfix direttamente da main (produzione)
git checkout main
git checkout -b hotfix/empty-array-fix

# Fix del bug critico
cat > calculator.js << 'EOF'
function calculateTotal(items) { 
    if (!items || items.length === 0) return 0;
    return items.reduce((a,b) => a + b.price, 0); 
}
EOF
git add calculator.js
git commit -m "hotfix: Handle empty array in calculateTotal"

# Test rapido del fix
echo "console.log(calculateTotal([])); // Should return 0" > quick-test.js
git add quick-test.js
git commit -m "Add test for empty array fix"

# Merge in main (deploy immediato)
git checkout main
git merge hotfix/empty-array-fix
git tag v1.5.1

# Merge anche in develop per mantenere sincronizzazione
git checkout develop
git merge hotfix/empty-array-fix

# Cleanup
git branch -d hotfix/empty-array-fix
```

### Scenario 3: Team Enterprise - Release Branch

#### Contesto Enterprise
Team di 10+ sviluppatori con release programmate ogni 2 settimane.

```bash
# Setup enterprise scenario
mkdir enterprise-release-scenario
cd enterprise-release-scenario
git init

# Main branch (production)
echo "# Enterprise App v2.0" > README.md
echo "const VERSION = '2.0.0';" > version.js
git add .
git commit -m "v2.0.0: Stable release"
git tag v2.0.0

# Develop branch (integrazione features)
git checkout -b develop
echo "const VERSION = '2.1.0-dev';" > version.js
git add version.js
git commit -m "Start v2.1.0 development"
```

#### Multiple Feature Development
```bash
# Feature 1: User Authentication
git checkout -b feature/auth-system
echo "function authenticate(user) { /* OAuth implementation */ }" > auth.js
git add auth.js
git commit -m "Implement OAuth authentication"
git checkout develop
git merge feature/auth-system --no-ff

# Feature 2: Advanced Reporting
git checkout -b feature/advanced-reports
echo "function generateReport(type) { /* reporting logic */ }" > reports.js
git add reports.js
git commit -m "Add advanced reporting system"
git checkout develop
git merge feature/advanced-reports --no-ff

# Feature 3: Performance Optimization
git checkout -b feature/performance-opt
echo "// Optimized algorithms" >> version.js
git add version.js
git commit -m "Optimize core algorithms"
git checkout develop
git merge feature/performance-opt --no-ff
```

#### Release Preparation
```bash
# Creare release branch per stabilizzazione
git checkout -b release/v2.1.0

# Update version
echo "const VERSION = '2.1.0-rc1';" > version.js
git add version.js
git commit -m "Prepare v2.1.0-rc1"

# Bug fixes durante testing
echo "function fixMinorBug() { /* fix implementation */ }" >> version.js
git add version.js
git commit -m "Fix: Minor bug in user interface"

echo "const VERSION = '2.1.0';" > version.js
git add version.js
git commit -m "Bump to v2.1.0 final"

# Release finale
git checkout main
git merge release/v2.1.0 --no-ff
git tag v2.1.0

# Merge back in develop
git checkout develop
git merge release/v2.1.0 --no-ff
git branch -d release/v2.1.0
```

### Scenario 4: Open Source - Fork Contribution

#### Contesto Open Source
Contribuire a un progetto open source esistente.

```bash
# Simuliamo un progetto open source esistente
mkdir opensource-project
cd opensource-project
git init

# Progetto originale (upstream)
echo "# Awesome Open Source Library" > README.md
echo "function coreFunction() { return 'original'; }" > lib.js
git add .
git commit -m "Initial open source project"

# Simula l'aver fatto fork
git remote add upstream $(pwd)
git checkout -b my-contribution

# Contribuzione: aggiungere nuova funzionalità
echo "function newUtilityFunction() { return 'contribution'; }" >> lib.js
git add lib.js
git commit -m "Add new utility function"

# Documentazione della contribuzione
echo "## New Features" >> README.md
echo "- Added newUtilityFunction for enhanced functionality" >> README.md
git add README.md
git commit -m "Document new utility function"

# Test della contribuzione
echo "// Tests for new function" > tests.js
git add tests.js
git commit -m "Add tests for new utility function"
```

## 🔍 Analisi dei Pattern

### Pattern 1: Feature Branch Workflow
**Quando usarlo:**
- Sviluppo di funzionalità isolate
- Team piccoli/medi
- Necessità di code review

**Caratteristiche:**
```
main ──────────────●──────────► (stable)
     \            /
      feature ──●──             (isolated development)
```

### Pattern 2: Gitflow Workflow
**Quando usarlo:**
- Release programmate
- Team grandi
- Prodotti enterprise

**Caratteristiche:**
```
main ──────●─────────●─────────► (production)
           /         /
develop ──●─────●────●─────────► (integration)
         /     /
feature ●─────/                  (features)
       /
hotfix●                          (emergency fixes)
```

### Pattern 3: Hotfix Strategy
**Quando usarlo:**
- Bug critici in produzione
- Fix emergenziali
- Zero downtime requirements

**Caratteristiche:**
- Branch direttamente da main/production
- Merge in tutte le branch attive
- Tag immediato per deployment

## 🏃‍♂️ Esercizio Pratico

### Simulazione Completa: E-commerce Team

#### Setup Iniziale
1. Crea repository per app e-commerce
2. Implementa scenario con:
   - Main branch (produzione)
   - Develop branch (integrazione)
   - 2 feature branch simultane
   - 1 hotfix durante sviluppo

#### Task Specifici
```bash
# 1. Setup base
mkdir ecommerce-simulation
cd ecommerce-simulation
git init
# (implementa struttura base)

# 2. Feature parallele
# - feature/payment-gateway
# - feature/inventory-management

# 3. Hotfix critico
# - hotfix/security-vulnerability

# 4. Release preparation
# - release/v1.2.0
```

## 🎯 Risultati Attesi

Dopo questo esempio dovresti:
- ✅ Riconoscere scenari appropriati per diversi pattern di branching
- ✅ Gestire multiple feature branch simultanee
- ✅ Implementare strategie di hotfix efficaci
- ✅ Coordinare release branch in team
- ✅ Comprendere implicazioni dei merge strategies

## 💡 Tips per Scenari Reali

### Feature Branch Best Practices
```bash
# Naming convention chiaro
feature/JIRA-123-user-authentication
feature/add-shopping-cart
hotfix/critical-payment-bug

# Keep branches small and focused
# Max 1-2 settimane di sviluppo per feature
```

### Team Coordination
```bash
# Sync regolare con develop
git checkout feature/my-feature
git pull origin develop
git merge develop

# Pre-merge testing
git checkout develop
git merge feature/my-feature --no-ff --no-commit
# Test, then commit or abort
```

## 🔗 Prossimi Passi

- [03 - Pianificazione Strategica](./03-pianificazione-strategica.md)
- [Guida: Strategie di Branching](../guide/05-strategie-branching.md)

---

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 01-Visualizzazione Branch](./01-visualizzazione-branch.md)
- [➡️ 03-Pianificazione Strategica](./03-pianificazione-strategica.md)
