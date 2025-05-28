# Commit Atomici: Principi per Commit Logici e Coerenti

## Introduzione
Un commit atomico rappresenta una singola unità logica di cambiamento. È la pratica di raggruppare modifiche correlate in un singolo commit, rendendo la history più leggibile e facilitando debugging, rollback e code review.

## Principi Fondamentali

### 1. Una Modifica Logica = Un Commit
```bash
# ✅ BUONO - Un commit per ogni modifica logica
git commit -m "feat: aggiungi validazione email"
git commit -m "test: aggiungi test per validazione email"
git commit -m "docs: documenta API validazione"

# ❌ CATTIVO - Tutto in un commit
git commit -m "aggiungi validazione, test e documentazione"
```

### 2. Commit Compilabili e Funzionanti
```bash
# Ogni commit deve lasciare il codice in stato funzionante
git add validation.js
git commit -m "feat: aggiungi classe EmailValidator"

git add validation.test.js  
git commit -m "test: test unit per EmailValidator"

git add email-service.js
git commit -m "feat: integra EmailValidator in EmailService"
```

### 3. Separazione delle Responsabilità
```bash
# ✅ BUONO - Separare logica e presentazione
git commit -m "feat: implementa logica autenticazione JWT"
git commit -m "feat: aggiungi interfaccia login"
git commit -m "style: applica design system al form login"

# ❌ CATTIVO - Mischiare tutto
git commit -m "implementa login con stili e test"
```

## Strategie per Commit Atomici

### 1. Staging Selettivo
```bash
# Scenario: file con modifiche multiple non correlate
git status
# modified: user.js (fix bug + nuova feature)
# modified: style.css (2 modifiche diverse)

# Commit atomico per bug fix
git add -p user.js  # Selezionare solo le righe del bug fix
git commit -m "fix: risolvi null pointer in User.getName()"

# Commit atomico per feature
git add -p user.js  # Selezionare righe della nuova feature
git commit -m "feat: aggiungi metodo User.getFullName()"

# Commit per stili
git add -p style.css  # Prima modifica CSS
git commit -m "style: migliora spaziatura header"

git add style.css  # Resto delle modifiche
git commit -m "style: aggiorna colori tema dark"
```

### 2. Uso di git add --patch
```bash
# Esempio pratico di staging selettivo
cat > example.js << 'EOF'
class User {
    constructor(name, email) {
        this.name = name;
        this.email = email;
        this.isActive = true;  // Nuova feature
    }
    
    getName() {
        // Fix: gestire null
        return this.name || 'Unknown';
    }
    
    // Nuova feature: metodo per status
    getStatus() {
        return this.isActive ? 'Active' : 'Inactive';
    }
}
EOF

# Commit solo il fix del bug
git add -p example.js
# Selezionare solo le righe del fix null
git commit -m "fix: gestisci null in User.getName()"

# Commit per la nuova feature
git add example.js  # Resto delle modifiche
git commit -m "feat: aggiungi sistema status utenti"
```

## Workflow per Commit Atomici

### 1. Pianificazione Pre-Sviluppo
```bash
# Prima di iniziare, definire i commit atomici
echo "📝 Plan per User Authentication Feature:
1. feat: aggiungi classe AuthService
2. feat: implementa JWT token generation  
3. feat: aggiungi middleware authentication
4. test: test unit per AuthService
5. test: test integration per auth middleware
6. docs: documenta API authentication" > commit-plan.md
```

### 2. Sviluppo Incrementale
```bash
# Implementare un pezzo alla volta
# Step 1: AuthService base
cat > auth-service.js << 'EOF'
class AuthService {
    constructor() {
        this.secret = process.env.JWT_SECRET;
    }
}
module.exports = AuthService;
EOF

git add auth-service.js
git commit -m "feat: aggiungi classe AuthService base"

# Step 2: JWT generation
cat >> auth-service.js << 'EOF'

    generateToken(user) {
        return jwt.sign(
            { userId: user.id, email: user.email },
            this.secret,
            { expiresIn: '24h' }
        );
    }
EOF

git add auth-service.js
git commit -m "feat: implementa JWT token generation"
```

### 3. Revisione Pre-Commit
```bash
# Script per verificare atomicità
#!/bin/bash
# check-atomic.sh

echo "🔍 Verifica commit atomico..."

# Controllare file modificati
FILES=$(git diff --cached --name-only)
echo "📁 File modificati: $(echo $FILES | wc -w)"

# Verificare che i file siano correlati
if [ $(echo $FILES | wc -w) -gt 5 ]; then
    echo "⚠️ Troppi file modificati - considerare split"
fi

# Verificare dimensione delle modifiche
LINES=$(git diff --cached --numstat | awk '{sum += $1 + $2} END {print sum}')
if [ "$LINES" -gt 100 ]; then
    echo "⚠️ Troppe righe modificate ($LINES) - considerare split"
fi

# Verificare buildabilità
echo "🔨 Test build..."
npm test --silent || echo "❌ Test falliti"
```

## Tipi di Commit Atomici

### 1. Feature Atomiche
```bash
# Esempio: Sistema di notifiche
git commit -m "feat: aggiungi classe NotificationService"
git commit -m "feat: implementa email notifications"
git commit -m "feat: implementa push notifications"
git commit -m "feat: aggiungi notification templates"
git commit -m "feat: integra notifications in UserService"
```

### 2. Bug Fix Atomici
```bash
# Scenario: bug complesso con multiple cause
git commit -m "fix: correggi validazione input in form registration"
git commit -m "fix: risolvi race condition in user creation"
git commit -m "fix: migliora error handling per duplicate email"
```

### 3. Refactoring Atomici
```bash
# Refactoring graduale
git commit -m "refactor: estrai metodo validateEmail da UserService"
git commit -m "refactor: crea classe EmailValidator"
git commit -m "refactor: migra UserService a EmailValidator"
git commit -m "refactor: rimuovi codice duplicato validazione"
```

## Gestione File Multipli

### 1. File Correlati Logicamente
```bash
# ✅ BUONO - File correlati per la stessa feature
git add user.js user.test.js user-controller.js
git commit -m "feat: implementa gestione profilo utente completa"
```

### 2. Modifiche Cross-File
```bash
# Scenario: rename di metodo in multiple classi
git add user-service.js order-service.js payment-service.js
git commit -m "refactor: rename getUserById to findUserById"

# Applicare pattern consistent in tutto il codebase
git add *.js
git commit -m "style: applica naming convention per metodi find*"
```

### 3. Database + Codice
```bash
# Migrazioni atomiche
git add migration-001-add-user-table.sql
git commit -m "db: aggiungi tabella users"

git add user-model.js user-repository.js
git commit -m "feat: implementa User model e repository"
```

## Commit Atomici Avanzati

### 1. Commit con Dipendenze
```bash
# Gestire dipendenze tra commit
git commit -m "feat: aggiungi interface IUserRepository"
git commit -m "feat: implementa SQLUserRepository"
git commit -m "feat: implementa InMemoryUserRepository per test"
git commit -m "feat: configura dependency injection per repositories"
```

### 2. Breaking Changes Atomici
```bash
# Separare breaking changes da features
git commit -m "feat: aggiungi nuovo parametro required a createUser"
git commit -m "feat!: rendi email field obbligatorio

BREAKING CHANGE: createUser() ora richiede parametro email
- Aggiornare tutte le chiamate esistenti  
- Migrare database per rendere email NOT NULL"

git commit -m "feat: aggiungi validazione email nel frontend"
```

### 3. Performance Improvements
```bash
# Ottimizzazioni incrementali
git commit -m "perf: aggiungi indice database su user.email"
git commit -m "perf: implementa caching per query getUserById"
git commit -m "perf: ottimizza serializzazione JSON user data"
```

## Tools per Commit Atomici

### 1. Git Aliases Utili
```bash
# Configurare alias per workflow atomici
git config --global alias.addp 'add --patch'
git config --global alias.unstage 'reset HEAD --'
git config --global alias.uncommit 'reset --soft HEAD~1'

# Alias per review pre-commit
git config --global alias.ready '!git status && git diff --cached --stat'
```

### 2. Script di Verifica
```bash
#!/bin/bash
# atomic-commit-check.sh

# Verificare che il commit sia atomico
echo "🔍 Atomic Commit Checker"

# Contare file modificati
file_count=$(git diff --cached --name-only | wc -l)
echo "📁 Files changed: $file_count"

# Contare righe modificate
line_count=$(git diff --cached --numstat | awk '{sum += $1 + $2} END {print sum}')
echo "📏 Lines changed: $line_count"

# Verificare tipi di file
extensions=$(git diff --cached --name-only | grep -o '\.[^.]*$' | sort -u)
echo "📋 File types: $extensions"

# Warning se non atomico
if [ $file_count -gt 10 ] || [ $line_count -gt 200 ]; then
    echo "⚠️ Consider splitting this commit"
    echo "Tips:"
    echo "- Use 'git add -p' for selective staging"
    echo "- Separate logic changes from style changes"
    echo "- Split new features from bug fixes"
fi
```

### 3. Pre-commit Hook
```bash
#!/bin/bash
# .git/hooks/pre-commit

# Verificare che ogni commit sia atomico e funzionante
echo "🧪 Running pre-commit checks..."

# Test automatici
npm test --silent
if [ $? -ne 0 ]; then
    echo "❌ Tests failed - commit rejected"
    exit 1
fi

# Linting
npm run lint --silent
if [ $? -ne 0 ]; then
    echo "❌ Linting failed - commit rejected"  
    exit 1
fi

# Verificare atomicità
files=$(git diff --cached --name-only | wc -l)
if [ $files -gt 15 ]; then
    echo "⚠️ Many files changed ($files) - ensure commit is atomic"
    read -p "Continue anyway? (y/N): " confirm
    [[ $confirm =~ ^[Yy]$ ]] || exit 1
fi

echo "✅ Pre-commit checks passed"
```

## Risoluzione Problemi Comuni

### 1. Commit Troppo Grandi
```bash
# Problema: commit con troppe modifiche
git status
# 20 file modificati, troppe features insieme

# Soluzione: reset e ricommit atomicamente
git reset --soft HEAD~1  # Uncommit mantenendo changes
git reset  # Unstage tutto

# Ricommit atomicamente
git add user-service.js user-controller.js
git commit -m "feat: implementa CRUD operations per users"

git add payment-service.js
git commit -m "feat: aggiungi payment processing"
```

### 2. Mix di Bug Fix e Features
```bash
# Problema: bug fix e feature nello stesso file
git diff user.js
# +    validateEmail()  // nuova feature
# -    return null      // bug fix
# +    return ""

# Soluzione: staging selettivo
git add -p user.js
# Selezionare solo le righe del bug fix
git commit -m "fix: return empty string instead of null"

git add user.js
git commit -m "feat: aggiungi validazione email"
```

### 3. Refactoring Incrementale
```bash
# Refactoring grande diviso in step atomici
# Step 1: Extract method
git commit -m "refactor: extract validateUser method"

# Step 2: Move to new class  
git commit -m "refactor: create UserValidator class"

# Step 3: Replace old implementation
git commit -m "refactor: replace inline validation with UserValidator"

# Step 4: Remove dead code
git commit -m "refactor: remove unused validation code"
```

## Metriche e Analisi

### 1. Analisi Dimensione Commit
```bash
#!/bin/bash
# Analizzare se i commit sono atomici
echo "📊 Commit Size Analysis (last 50 commits)"

git log --pretty=format:"%h %s" --numstat -50 | \
awk '
/^[a-f0-9]/ { commit = $0; files = 0; lines = 0; next }
/^[0-9]/ { files++; lines += $1 + $2 }
/^$/ { 
    if (files > 0) {
        printf "%-8s %2d files, %3d lines: %s\n", 
               substr(commit,1,7), files, lines, substr(commit,9)
        if (files > 10) printf "  ⚠️ Consider splitting\n"
    }
}'
```

### 2. Code Review Atomico
```bash
# Template per review di commit atomici
cat > .github/PULL_REQUEST_TEMPLATE.md << 'EOF'
## Atomic Commits Checklist

- [ ] Each commit represents a single logical change
- [ ] All commits are buildable and tests pass
- [ ] Commit messages follow conventional format
- [ ] No mixing of bug fixes and features
- [ ] Related files are committed together
- [ ] Large changes are split into smaller commits

## Commit Strategy Used
- [ ] Feature commits
- [ ] Bug fix commits  
- [ ] Refactoring commits
- [ ] Documentation commits
- [ ] Test commits
EOF
```

## Best Practices Summary

### Do's ✅
- Un commit = una modifica logica
- Commit compilabili e testabili
- Messaggi descrittivi e specifici
- Staging selettivo con `git add -p`
- Separare fix da features
- Test automatici pre-commit

### Don'ts ❌
- Mix di bug fix e features
- Commit di "tutto insieme"
- Commit di codice non funzionante
- Messaggi generici come "fix"
- Commit troppo granulari (typo singoli)
- Ignorare le dipendenze logiche

## Conclusioni
I commit atomici sono la base per una history Git pulita e manutenibile. Richiedono disciplina e pianificazione, ma migliorano significativamente la qualità del progetto e la collaborazione in team.
