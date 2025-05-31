# Esempio 1: Workflow di Merge Completo

## 📝 Descrizione

Questo esempio dimostra un workflow completo di merge che include la preparazione di branch, diversi tipi di merge e la gestione post-merge. Simula un ambiente di sviluppo reale con feature branch, hotfix e release.

## 🎯 Obiettivi di Apprendimento

- Implementare un workflow Git Flow completo
- Utilizzare diversi tipi di merge appropriati
- Gestire branch paralleli e sincronizzazione
- Applicare best practices per team collaboration

## 🚀 Setup Iniziale

### Creazione del Repository di Test

```bash
# Crea directory di lavoro
mkdir merge-workflow-demo
cd merge-workflow-demo

# Inizializza repository
git init
git config user.name "Developer Team"
git config user.email "team@example.com"

# Crea file iniziale
echo "# Project Management System" > README.md
echo "versione: 1.0.0" >> README.md
git add README.md
git commit -m "feat: initial project setup"

# Crea struttura base
mkdir -p src/{auth,dashboard,api}
echo "console.log('Main app');" > src/app.js
echo "function authenticate() {}" > src/auth/login.js
echo "function renderDashboard() {}" > src/dashboard/main.js
echo "function apiCall() {}" > src/api/client.js

git add src/
git commit -m "feat: add basic project structure"
```

### Configurazione Branch Strategy

```bash
# Crea branch development
git checkout -b develop
echo "// Development environment config" > src/config.dev.js
git add src/config.dev.js
git commit -m "feat: add development configuration"

# Torna a main e configura merge strategies
git checkout main
git config branch.main.mergeoptions "--ff-only"
git config branch.develop.mergeoptions "--no-ff"
```

## 🔧 Scenario 1: Feature Development con Squash Merge

### Sviluppo Feature Authentication

```bash
# Crea feature branch da develop
git checkout develop
git checkout -b feature/advanced-auth

# Simula sviluppo iterativo
echo "function loginWithEmail(email, password) {" > src/auth/email-login.js
echo "  return validateCredentials(email, password);" >> src/auth/email-login.js
echo "}" >> src/auth/email-login.js
git add src/auth/email-login.js
git commit -m "feat: add email login functionality"

# Secondo commit della feature
echo "function loginWithGoogle() {" > src/auth/google-login.js
echo "  return googleOAuth();" >> src/auth/google-login.js
echo "}" >> src/auth/google-login.js
git add src/auth/google-login.js
git commit -m "feat: add Google OAuth login"

# Terzo commit con refactoring
echo "// Updated login logic" >> src/auth/login.js
echo "function validateCredentials(email, pass) { return true; }" >> src/auth/login.js
git add src/auth/login.js
git commit -m "refactor: improve login validation"

# Visualizza storia feature
echo -e "\n📊 Feature branch history:"
git log --oneline --graph feature/advanced-auth ^develop
```

### Merge Feature con Squash

```bash
# Torna a develop per merge
git checkout develop

# Verifica differenze
echo -e "\n📋 Changes to be merged:"
git diff develop..feature/advanced-auth --stat

# Squash merge per storia pulita
git merge --squash feature/advanced-auth
git commit -m "feat: implement advanced authentication system

- Add email/password login
- Add Google OAuth integration  
- Improve validation logic
- Update authentication module

Closes: #123"

# Cleanup feature branch
git branch -d feature/advanced-auth

echo -e "\n✅ Feature merged successfully with clean history"
git log --oneline -3
```

## 🚨 Scenario 2: Hotfix con Fast-Forward

### Problema Critico in Produzione

```bash
# Simula problema urgente in main
git checkout main

# Crea hotfix branch
git checkout -b hotfix/security-patch

# Fix critico
echo "// SECURITY: Fix XSS vulnerability" >> src/api/client.js
echo "function sanitizeInput(input) { return input.replace(/<script>/g, ''); }" >> src/api/client.js
git add src/api/client.js
git commit -m "fix: patch XSS vulnerability in API client

- Add input sanitization
- Prevent script injection
- Critical security update

Priority: HIGH
Affects: All users"

# Verifica che sia fast-forward
echo -e "\n🔍 Checking if fast-forward is possible:"
git checkout main
if git merge-base --is-ancestor hotfix/security-patch main; then
    echo "✅ Fast-forward merge possible"
else
    echo "❌ Fast-forward not possible"
fi
```

### Fast-Forward Merge del Hotfix

```bash
# Merge hotfix con fast-forward
git merge --ff-only hotfix/security-patch

# Verifica merge
echo -e "\n📈 Main branch after hotfix:"
git log --oneline -3

# Tag per versioning
git tag v1.0.1 -m "Security patch release"

# Cleanup
git branch -d hotfix/security-patch

# Sincronizza develop con hotfix
git checkout develop
git merge main --ff-only
echo -e "\n🔄 Develop synchronized with hotfix"
```

## 🎉 Scenario 3: Release Branch con No-FF Merge

### Preparazione Release

```bash
# Crea release branch da develop
git checkout develop
git checkout -b release/v2.0.0

# Preparazione release
echo "version: 2.0.0" > VERSION
echo "release_date: $(date +%Y-%m-%d)" >> VERSION
git add VERSION
git commit -m "release: prepare v2.0.0"

# Update documentation
echo -e "\n## Version 2.0.0\n- Advanced authentication\n- Security improvements\n- Performance optimizations" >> README.md
git add README.md
git commit -m "docs: update changelog for v2.0.0"

# Build optimization
echo "// Production optimizations" > src/config.prod.js
echo "const PRODUCTION = true;" >> src/config.prod.js
git add src/config.prod.js
git commit -m "build: add production configuration"
```

### Merge Release con Tracciabilità

```bash
# Merge in main con no-ff per tracciabilità
git checkout main
git merge --no-ff release/v2.0.0 -m "Release v2.0.0

Features:
- Advanced authentication system
- Google OAuth integration
- Security patches
- Production optimizations

Tested: ✅
QA Approved: ✅
Security Review: ✅"

# Tag release
git tag v2.0.0 -m "Release version 2.0.0"

# Merge back to develop
git checkout develop
git merge --no-ff release/v2.0.0 -m "Merge release v2.0.0 back to develop"

# Cleanup
git branch -d release/v2.0.0

echo -e "\n🎯 Release v2.0.0 completed successfully"
```

## 🔀 Scenario 4: Merge Parallelo con Conflitti

### Sviluppo Parallelo

```bash
# Primo developer - feature UI
git checkout develop
git checkout -b feature/new-ui

echo "function renderNewDashboard() {" > src/dashboard/new-ui.js
echo "  const theme = 'modern';" >> src/dashboard/new-ui.js
echo "  return createLayout(theme);" >> src/dashboard/new-ui.js
echo "}" >> src/dashboard/new-ui.js

# Modifica file condiviso
echo "// Updated for new UI" >> src/dashboard/main.js
echo "const UI_VERSION = '2.0';" >> src/dashboard/main.js
git add src/dashboard/
git commit -m "feat: implement new modern UI"

# Secondo developer - feature API
git checkout develop
git checkout -b feature/api-v2

echo "function apiV2Call() {" > src/api/v2.js
echo "  return fetch('/api/v2/data');" >> src/api/v2.js
echo "}" >> src/api/v2.js

# Modifica stesso file con conflitto
echo "// Updated for API v2" >> src/dashboard/main.js
echo "const API_VERSION = '2.0';" >> src/dashboard/main.js
git add .
git commit -m "feat: implement API v2 integration"
```

### Risoluzione Conflitti e Merge

```bash
# Merge prima feature
git checkout develop
git merge --no-ff feature/new-ui -m "Merge new UI feature"

# Tentativo merge seconda feature (con conflitto)
echo -e "\n⚠️  Attempting merge with potential conflicts:"
git merge feature/api-v2 || {
    echo -e "\n🔥 Conflicts detected! Resolving..."
    
    # Mostra conflitti
    echo -e "\n📋 Conflicted files:"
    git status --porcelain | grep "UU"
    
    # Risoluzione manuale simulata
    cat > src/dashboard/main.js << 'EOF'
function renderDashboard() {
    // Updated for new UI and API v2
    const UI_VERSION = '2.0';
    const API_VERSION = '2.0';
    return createModernDashboard();
}
EOF
    
    git add src/dashboard/main.js
    git commit -m "resolve: merge conflicts between UI and API features

- Combine UI_VERSION and API_VERSION constants
- Integrate new UI with API v2
- Maintain backward compatibility"
}

# Cleanup feature branches
git branch -d feature/new-ui feature/api-v2

echo -e "\n✅ All features merged successfully"
```

## 📊 Analisi Finale del Workflow

### Visualizzazione Storia Completa

```bash
echo -e "\n🌳 Complete project history:"
git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --all

echo -e "\n\n📈 Branch merge statistics:"
git log --merges --pretty=format:'%h - %s (%cr)' -10

echo -e "\n\n🏷️  Available tags:"
git tag -l -n1

echo -e "\n\n📁 Final project structure:"
find . -name "*.js" | sort
```

### Verifica Qualità Merge

```bash
# Verifica integrità
echo -e "\n🔍 Repository integrity check:"
git fsck --full

# Statistiche merge
echo -e "\n📊 Merge statistics:"
echo "Total commits: $(git rev-list --count HEAD)"
echo "Merge commits: $(git rev-list --merges --count HEAD)"
echo "Feature branches merged: $(git log --merges --grep="feat" --oneline | wc -l)"
echo "Hotfixes applied: $(git log --merges --grep="fix" --oneline | wc -l)"
```

## 💡 Lezioni Apprese

### Quando Usare Ogni Strategia

| Scenario | Merge Type | Comando | Beneficio |
|----------|------------|---------|-----------|
| Feature completa | Squash | `git merge --squash` | Storia pulita |
| Hotfix urgente | Fast-forward | `git merge --ff-only` | Tracciabilità lineare |
| Release | No-FF | `git merge --no-ff` | Punto di merge visibile |
| Conflitti | Three-way | `git merge` | Preserva contesto |

### Best Practices Implementate

1. **Branch Naming**: Convenzioni chiare (`feature/`, `hotfix/`, `release/`)
2. **Commit Messages**: Format strutturato con tipo e descrizione
3. **Merge Messages**: Informazioni complete su feature e testing
4. **Tagging**: Versioning semantico per release
5. **Cleanup**: Rimozione branch dopo merge successful

## 🔄 Esercizi di Follow-up

1. Ripeti il workflow con i tuoi progetti
2. Sperimenta con merge tools grafici
3. Implementa hook pre-merge per validazione
4. Crea script di automation per il workflow

## 📚 Riferimenti

- [02-Fast Forward](../guide/02-fast-forward.md) - Dettagli su merge lineari
- [03-Recursive Merge](../guide/03-recursive-merge.md) - Gestione conflitti
- [04-Squash Merge](../guide/04-squash-merge.md) - Pulizia storia

---

**Prossimo**: [02-Gestione Conflitti Avanzata](./02-conflict-resolution-advanced.md)
