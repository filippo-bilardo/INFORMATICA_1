# 04 - Squash Merge: Cleanup della Cronologia

## 📖 Cos'è un Squash Merge

Il Squash Merge è una strategia che combina tutti i commit di un feature branch in un singolo commit quando viene integrato nel branch target. Questo crea una cronologia pulita e lineare, eliminando i commit intermedi "work in progress".

## 🔄 Meccanismo Squash Merge

### Situazione Tipica

```bash
# Feature branch con multipli commit
main:     A---B---C
               \
feature:        D---E---F---G
```

Dove i commit in feature potrebbero essere:
- `D`: "Add login component - WIP"
- `E`: "Fix login validation"  
- `F`: "Add tests for login"
- `G`: "Fix typo in login form"

### Processo Squash Merge

```bash
git checkout main
git merge --squash feature
# Git stage tutte le modifiche ma NON fa commit automatico

git commit -m "Add complete login functionality

- Implement login component with validation
- Include comprehensive test suite
- Handle edge cases and error states"

# Risultato:
main:     A---B---C---S
```

Il commit `S` contiene tutte le modifiche di `D+E+F+G` ma come un'unità singola.

## ⚙️ Comandi Squash Merge

### Squash Merge Base

```bash
git checkout main
git merge --squash feature-branch
git commit -m "Meaningful commit message"
```

### Squash con Messaggio Automatico

```bash
# Git genererà automaticamente un messaggio che elenca tutti i commit
git merge --squash feature-branch
git commit  # Apre editor con messaggio auto-generato
```

### Verifica Modifiche Prima del Commit

```bash
git merge --squash feature-branch
git status  # Vedi cosa verrà committato
git diff --cached  # Review delle modifiche staged
git commit -m "Your message"
```

## 🎯 Quando Usare Squash Merge

### ✅ Ideale per:

1. **Branch con WIP Commits**
```bash
# Feature branch disordinato
git log --oneline feature/payment
# f8e7d6c Fix typo
# 5c4b3a2 WIP: payment integration  
# 9e8d7c6 Add payment service
# 2a1b0c9 Another fix
# 7f6e5d4 Payment component

# Squash in commit pulito
git merge --squash feature/payment
git commit -m "Add payment integration

- Implement Stripe payment service
- Add payment component with form validation
- Include error handling and success states
- Add comprehensive test coverage"
```

2. **Experimental Branches**
```bash
# Branch di sperimentazione con molti tentativi
git log --oneline experiment/new-ui
# a1b2c3d Try different approach
# 9f8e7d6 Revert previous attempt
# 5e4d3c2 Another attempt at responsive design
# 1c2b3a4 WIP: mobile layout
# 8d7c6b5 Initial UI experiments

# Squash nel risultato finale
git merge --squash experiment/new-ui  
git commit -m "Implement responsive UI design

- New mobile-first responsive layout
- Improved user experience on tablets
- Enhanced accessibility features
- Optimized for performance"
```

3. **Feature con Commit di Fix Intermedi**
```bash
# Feature development tipico
git log --oneline feature/user-profile
# 3e4f5a6 Add user profile tests
# 9c8b7a6 Fix profile image upload  
# 5d4c3b2 Add user profile component
# 1a2b3c4 Fix validation bug
# 7f8e9d0 Initial user profile work

# Squash in feature completa
git merge --squash feature/user-profile
git commit -m "Add user profile management

- User profile display and editing
- Profile image upload with validation
- Comprehensive form validation
- Full test coverage"
```

4. **Contributi External**
```bash
# Pull request da contributor esterni con cronologia disordinata
git fetch origin pull/123/head:contributor-feature
git checkout main
git merge --squash contributor-feature
git commit -m "Add requested feature from @contributor

Thanks to @contributor for implementing:
- Feature description
- Testing included
- Documentation updated

Closes #123"
```

### ❌ Non Ideale per:

1. **Branch Collaborative Importanti**
2. **Quando cronologia dettagliata è importante per audit**
3. **Branch con commit che devono essere tracciati individualmente**
4. **Situazioni dove bisogna fare rollback granulare**

## 📊 Vantaggi e Svantaggi

### ✅ Vantaggi

**1. Cronologia Main Pulitissima**
```bash
git log --oneline main
# 7a8b9c2 Add user authentication system
# 3e4f5a6 Implement shopping cart functionality  
# 9f8e7d6 Add responsive homepage design
# 5c4b3a2 Initial project setup
```

**2. Commit Semantici e Significativi**
```bash
# Ogni commit rappresenta una feature completa
git show 7a8b9c2
# commit 7a8b9c2
# Author: Developer <dev@company.com>
# Date: Today
#
# Add user authentication system
#
# - JWT token-based authentication
# - Login/logout/register functionality
# - Password recovery system
# - Role-based access control
# - Comprehensive security tests
```

**3. Facile Code Review Post-Merge**
```bash
# Review di una feature completa in un commit
git show 7a8b9c2 --stat
# Review dettagliata di tutti i file modificati per la feature
```

**4. Clean Release Notes**
```bash
# Generazione automatica release notes
git log --oneline v1.0..v1.1
# 7a8b9c2 Add user authentication system
# 3e4f5a6 Implement shopping cart functionality
# 9f8e7d6 Add responsive homepage design
```

### ❌ Svantaggi

**1. Perdita Cronologia Dettagliata**
```bash
# Non puoi più vedere:
# - L'evoluzione del pensiero dello sviluppatore
# - I singoli step di debugging
# - I commit intermedi di testing
```

**2. Rollback Meno Granulare**
```bash
# Se devi rollback parte di una feature, devi:
git revert 7a8b9c2  # Reverte TUTTA la feature
# Non puoi revertire solo una parte specifica
```

**3. Debugging Più Difficile**
```bash
# git bisect meno efficace
# Se un bug è introdotto, devi analizzare tutto il commit squashed
git bisect start
git bisect bad HEAD
git bisect good v1.0
# Meno precision nell'identificare il problema specifico
```

**4. Perdita Authorship Dettagliata**
```bash
# Se multiple persone hanno contribuito al branch:
git log --pretty="%an %s" feature/complex
# Alice Initial implementation
# Bob Add validation  
# Charlie Fix edge cases
# Alice Add tests

# Dopo squash:
git log --pretty="%an %s" main
# Alice Add complete feature  # Solo un autore risulta
```

## 🛠️ Tecniche Avanzate

### 1. Squash Selettivo

```bash
# Squash solo alcuni commit, mantenendo altri
git rebase -i HEAD~5
# Nell'editor:
# pick a1b2c3d Important checkpoint
# squash 4e5f6a7 Small fix
# squash 8b9c0d1 Another small fix  
# pick 2c3d4e5 Another important checkpoint
# squash 6f7a8b9 Final fixes
```

### 2. Squash con Preservazione di Metadata

```bash
# Template per squash commit che preserva informazioni
git merge --squash feature/complex
cat > commit-message.txt << EOF
Implement user authentication system

Squashed from feature/complex branch containing:
- $(git log --oneline main..feature/complex | wc -l) commits
- Development period: $(git log --pretty="%ad" --date=short main..feature/complex | tail -1) to $(git log --pretty="%ad" --date=short main..feature/complex | head -1)

Original contributors:
$(git log --pretty="%an" main..feature/complex | sort | uniq)

Key milestones:
- Initial implementation
- Validation layer added
- Security hardening
- Comprehensive testing

Files changed: $(git diff --name-only main feature/complex | wc -l)
Lines added: +$(git diff --shortstat main feature/complex | grep -o '[0-9]* insertion' | cut -d' ' -f1)
Lines removed: -$(git diff --shortstat main feature/complex | grep -o '[0-9]* deletion' | cut -d' ' -f1)
EOF

git commit -F commit-message.txt
```

### 3. Interactive Squash Workflow

```bash
#!/bin/bash
# smart-squash.sh - Script per squash intelligente

FEATURE_BRANCH=$1
TARGET_BRANCH=${2:-main}

echo "🔄 Analyzing $FEATURE_BRANCH for squash merge..."

# Analizza i commit
COMMIT_COUNT=$(git log --oneline $TARGET_BRANCH..$FEATURE_BRANCH | wc -l)
echo "📊 Found $COMMIT_COUNT commits to squash"

# Mostra preview
echo "📋 Commits that will be squashed:"
git log --oneline $TARGET_BRANCH..$FEATURE_BRANCH

# Mostra file modificati
echo "📁 Files that will be modified:"
git diff --name-status $TARGET_BRANCH..$FEATURE_BRANCH

# Conferma
read -p "Proceed with squash? (y/n): " confirm
if [ "$confirm" = "y" ]; then
    git checkout $TARGET_BRANCH
    git merge --squash $FEATURE_BRANCH
    
    # Template per commit message
    echo "Generated squash commit for $FEATURE_BRANCH" > /tmp/squash-msg
    echo "" >> /tmp/squash-msg
    echo "Original commits:" >> /tmp/squash-msg
    git log --pretty="- %s (%an)" $TARGET_BRANCH..$FEATURE_BRANCH >> /tmp/squash-msg
    
    # Apri editor
    git commit -t /tmp/squash-msg
fi
```

### 4. Squash con Testing Automatico

```bash
#!/bin/bash
# test-squash.sh - Squash con validation

FEATURE_BRANCH=$1

# Pre-squash testing
echo "🧪 Testing feature branch before squash..."
git checkout $FEATURE_BRANCH
npm test || {
    echo "❌ Tests fail on feature branch"
    exit 1
}

# Perform squash
git checkout main
git merge --squash $FEATURE_BRANCH

# Post-squash testing
echo "🧪 Testing after squash..."
npm test || {
    echo "❌ Tests fail after squash, aborting"
    git reset --hard HEAD
    exit 1
}

# If tests pass, commit
git commit -m "Squash merge: $FEATURE_BRANCH

$(git log --oneline main..$FEATURE_BRANCH)

All tests passing ✅"

echo "✅ Squash merge completed successfully"
```

## 🎯 Esempi Pratici Dettagliati

### Esempio 1: Feature Development Tipico

```bash
# 1. Inizio feature branch
git checkout -b feature/shopping-cart
echo "Cart component" > cart.js
git add . && git commit -m "Initial cart component"

# 2. Development iterativo (tipico WIP)
echo "Add item functionality" >> cart.js
git add . && git commit -m "WIP: add items to cart"

echo "Remove item functionality" >> cart.js  
git add . && git commit -m "Add remove item function"

echo "// Fix: quantity validation" >> cart.js
git add . && git commit -m "Fix quantity validation bug"

echo "// Tests added" >> cart.test.js
git add . && git commit -m "Add basic tests"

echo "// More tests" >> cart.test.js
git add . && git commit -m "Add edge case tests"

echo "// Styling" > cart.css
git add . && git commit -m "Add cart styling"

echo "// Fix typo" >> cart.css
git add . && git commit -m "Fix CSS typo"

# 3. Visualizza cronologia disordinata
git log --oneline
# a1b2c3d Fix CSS typo
# 9e8f7d6 Add cart styling  
# 5c4b3a2 Add edge case tests
# 1f2e3d4 Add basic tests
# 7a8b9c0 Fix quantity validation bug
# 3e4f5a6 Add remove item function
# 9c8b7a6 WIP: add items to cart
# 5d4c3b2 Initial cart component

# 4. Squash merge per cronologia pulita
git checkout main
git merge --squash feature/shopping-cart

# 5. Commit semantico e completo
git commit -m "Implement shopping cart functionality

- Add/remove items with quantity controls  
- Client-side validation for quantities
- Responsive cart UI with modern styling
- Comprehensive test suite covering edge cases
- Integration ready for checkout process

Closes #45"

# 6. Risultato: un commit pulito
git log --oneline -1
# f9e8d7c Implement shopping cart functionality
```

### Esempio 2: Bug Investigation e Fix

```bash
# 1. Branch per investigation
git checkout -b debug/memory-leak

# 2. Multiple commit durante debugging
echo "console.log('Debug 1')" >> app.js
git add . && git commit -m "Add debug logging"

echo "console.log('Debug 2')" >> app.js
git add . && git commit -m "More debug info"

echo "// Found the issue" >> app.js
git add . && git commit -m "Identify memory leak source"

# Rimuove debug e implementa fix
git checkout -- app.js
echo "// Memory leak fixed" >> app.js
git add . && git commit -m "Remove debug code"

echo "// Proper cleanup implemented" >> app.js
git add . && git commit -m "Implement proper memory cleanup"

echo "// Tests for memory usage" >> tests/memory.test.js
git add . && git commit -m "Add memory usage tests"

# 3. Squash tutto nel fix finale
git checkout main
git merge --squash debug/memory-leak
git commit -m "Fix memory leak in event handlers

- Identified leak in event listener registration
- Implement proper cleanup on component unmount  
- Add memory usage monitoring tests
- Performance improvement ~40% memory reduction

Fixes #67"
```

### Esempio 3: Experimental Feature

```bash
# 1. Sperimentazione branch
git checkout -b experiment/ai-recommendations

# 2. Multiple tentativi e approcci
echo "Basic recommendation engine" > ai.js
git add . && git commit -m "First attempt at AI recommendations"

echo "// Try different algorithm" >> ai.js
git add . && git commit -m "Try collaborative filtering"

git reset --hard HEAD~1  # Revert attempt
echo "// Matrix factorization approach" > ai.js
git add . && git commit -m "Try matrix factorization"

echo "// Hybrid approach" >> ai.js
git add . && git commit -m "Combine multiple algorithms"

echo "// Performance optimizations" >> ai.js
git add . && git commit -m "Optimize performance"

echo "// A/B testing setup" >> ai.js
git add . && git commit -m "Add A/B testing framework"

# 3. Final working solution
echo "// Production ready" >> ai.js
git add . && git commit -m "Production ready AI recommendations"

# 4. Squash experimental process
git checkout main
git merge --squash experiment/ai-recommendations
git commit -m "Add AI-powered recommendation system

- Hybrid collaborative filtering and content-based algorithm
- Real-time personalized recommendations  
- A/B testing framework for optimization
- Performance optimized for <100ms response time
- Machine learning pipeline for continuous improvement

Implements #89, #92, #95"
```

## 🔧 Configurazioni e Automazioni

### 1. Alias per Squash Workflow

```bash
# .gitconfig aliases
git config --global alias.squash-merge '!f() { 
    git merge --squash "$1" && 
    echo "Squashed $1 - write commit message:" && 
    git commit; 
}; f'

# Uso
git squash-merge feature/my-feature
```

### 2. Git Hook per Squash Validation

```bash
# .git/hooks/pre-commit (per squash commits)
#!/bin/bash

# Verifica se è un squash commit
if git rev-parse --verify HEAD > /dev/null 2>&1; then
    # Non è il commit iniziale
    COMMIT_MSG=$(git log --format=%B -n 1 HEAD)
    
    if [[ $COMMIT_MSG == *"Squashed from"* ]] || git diff --cached --name-only | wc -l -gt 10; then
        echo "🔍 Detected large commit, ensuring quality..."
        
        # Test specifici per squash commits
        npm test || {
            echo "❌ Tests must pass for squash commits"
            exit 1
        }
        
        npm run lint || {
            echo "❌ Linting must pass for squash commits"  
            exit 1
        }
    fi
fi
```

### 3. Template per Squash Messages

```bash
# .gitsquash-template
[TYPE]: [BRIEF DESCRIPTION]

[DETAILED DESCRIPTION]

Squashed from [BRANCH_NAME] containing [N] commits:
[COMMIT_LIST]

Changes:
- [CHANGE_1]
- [CHANGE_2]
- [CHANGE_3]

Testing:
- [TEST_DESCRIPTION]

Closes #[ISSUE_NUMBER]

Co-authored-by: [COLLABORATOR_NAME] <[EMAIL]>
```

## 🚨 Troubleshooting e Recovery

### 1. Squash Accidentale

**Problema**: Hai fatto squash ma volevi preservare cronologia

```bash
# Se non hai pushato
git reset --soft HEAD~1  # Torna ai file staged
git reset HEAD           # Unstage tutto

# Ora puoi fare merge normale
git merge --no-ff feature-branch
```

### 2. Squash Incompleto

**Problema**: Squash merge si ferma prima del commit

```bash
git status
# On branch main
# All conflicts fixed but you are still merging.
#   (use "git commit" to conclude merge)

# Completa il merge
git commit -m "Your squash commit message"
```

### 3. Recovery di Cronologia Squashata

**Problema**: Hai bisogno della cronologia dettagliata dopo squash

```bash
# Il branch originale esiste ancora
git log --oneline feature/lost-history

# Recupera informazioni specifiche
git cherry-pick <specific-commit-from-feature>

# Oppure crea branch di backup
git checkout -b feature-backup feature/lost-history
```

## 📈 Best Practices per Squash Merge

### 1. **Messaggi Commit Strutturati**
```bash
git commit -m "Add user notification system

- Email notifications for important events
- In-app notification center with persistence
- Push notifications for mobile users
- Admin panel for notification management
- Comprehensive delivery tracking

Technical details:
- Uses Redis for real-time delivery
- Async job processing with Bull Queue
- Template system for customizable messages
- Rate limiting to prevent spam

Testing:
- Unit tests for all notification types
- Integration tests for delivery systems
- Load testing for high-volume scenarios

Performance:
- <50ms notification processing time
- Supports 10k+ concurrent users
- Optimized database queries

Closes #123, #124, #125
Fixes #99

Co-authored-by: Jane Doe <jane@company.com>"
```

### 2. **Pre-Squash Checklist**
```bash
# Checklist prima di squash merge
echo "✅ Pre-Squash Checklist:
□ All tests passing
□ Code review completed  
□ Feature fully implemented
□ Documentation updated
□ No merge conflicts
□ Branch ready for cleanup
□ Commit message prepared" > SQUASH_CHECKLIST.md
```

### 3. **Squash Strategy Guidelines**
```bash
# Quando fare squash (team guidelines)
echo "🎯 Squash Merge Guidelines:

✅ USE SQUASH WHEN:
- Feature branch has >5 WIP commits
- Commits include debugging/experimental code
- Branch contains fix commits for previous commits
- External contributor with messy history
- Feature is self-contained unit

❌ AVOID SQUASH WHEN:
- Branch has meaningful commit milestones
- Multiple developers contributed distinct parts
- Commits need individual review/blame tracking
- Complex feature that may need partial rollback
- Branch contains multiple logical features

💡 ALTERNATIVE: Consider interactive rebase for selective squashing" > SQUASH_GUIDELINES.md
```

---

## 🔗 Link Correlati

- **[01 - Tipi di Merge](01-tipi-merge.md)** - Panoramica generale
- **[02 - Fast-Forward Merge](02-fast-forward.md)** - Merge lineari
- **[03 - Recursive Merge](03-recursive-merge.md)** - Merge con conflitti
- **[05 - Merge vs Rebase](05-merge-vs-rebase.md)** - Strategie alternative

---

**💡 Ricorda**: Squash merge è eccellente per mantenere una cronologia main pulita e semantica. Usalo quando la cronologia dettagliata del development non è importante quanto il risultato finale!
