# Git Flow Workflow

## 📋 Panoramica

Git Flow è un modello di branching Git che definisce un flusso di lavoro strutturato per la gestione di release, feature e hotfix in progetti di sviluppo software.

## 🌿 Branch Structure

### Branch Principali

#### `main` 
- **Scopo**: Codice in produzione
- **Regole**: 
  - Sempre stabile e deployabile
  - Solo merge da `release` e `hotfix`
  - Protetto da push diretti

#### `develop`
- **Scopo**: Integrazione di nuove feature
- **Regole**:
  - Base per nuove feature
  - Contiene le ultime modifiche per la prossima release
  - Merge da `feature` branches

### Branch di Supporto

#### `feature/*`
- **Naming**: `feature/nome-feature`
- **Scopo**: Sviluppo di nuove funzionalità
- **Lifecycle**: 
  ```bash
  git checkout develop
  git checkout -b feature/user-authentication
  # Sviluppo...
  git checkout develop
  git merge feature/user-authentication
  git branch -d feature/user-authentication
  ```

#### `release/*`
- **Naming**: `release/versione` (es. `release/1.2.0`)
- **Scopo**: Preparazione per release
- **Attività**: Bug fix minori, aggiornamento versioni
- **Lifecycle**:
  ```bash
  git checkout develop
  git checkout -b release/1.2.0
  # Preparazione release...
  git checkout main
  git merge release/1.2.0
  git tag v1.2.0
  git checkout develop
  git merge release/1.2.0
  ```

#### `hotfix/*`
- **Naming**: `hotfix/descrizione-fix`
- **Scopo**: Fix urgenti per produzione
- **Lifecycle**:
  ```bash
  git checkout main
  git checkout -b hotfix/critical-security-fix
  # Fix del problema...
  git checkout main
  git merge hotfix/critical-security-fix
  git tag v1.2.1
  git checkout develop
  git merge hotfix/critical-security-fix
  ```

## 🔄 Workflow Completo

### 1. Sviluppo Feature

```bash
# 1. Inizio feature
git checkout develop
git pull origin develop
git checkout -b feature/task-management

# 2. Sviluppo iterativo
git add .
git commit -m "feat: add task creation form"
git add .
git commit -m "feat: implement task validation"
git add .
git commit -m "test: add task creation tests"

# 3. Aggiornamento con develop
git fetch origin
git rebase origin/develop

# 4. Push e PR
git push origin feature/task-management
# Crea Pull Request su GitHub
```

### 2. Preparazione Release

```bash
# 1. Branch release da develop
git checkout develop
git pull origin develop
git checkout -b release/1.1.0

# 2. Aggiornamenti pre-release
echo "1.1.0" > VERSION
npm version 1.1.0 --no-git-tag-version
git commit -am "chore: bump version to 1.1.0"

# 3. Bug fixes (se necessari)
git commit -am "fix: resolve minor UI issues"

# 4. Finalizzazione
git checkout main
git merge release/1.1.0
git tag -a v1.1.0 -m "Release version 1.1.0"
git checkout develop
git merge release/1.1.0
git branch -d release/1.1.0
```

### 3. Hotfix Urgente

```bash
# 1. Branch hotfix da main
git checkout main
git pull origin main
git checkout -b hotfix/login-security-fix

# 2. Implementazione fix
git commit -am "hotfix: fix login security vulnerability"

# 3. Test specifici
npm run test:security
git commit -am "test: verify security fix"

# 4. Merge su main e develop
git checkout main
git merge hotfix/login-security-fix
git tag -a v1.1.1 -m "Hotfix version 1.1.1"
git checkout develop
git merge hotfix/login-security-fix
git branch -d hotfix/login-security-fix
```

## 🎯 Best Practices

### Naming Conventions
```bash
# Feature branches
feature/user-authentication
feature/task-editing
feature/responsive-design

# Release branches
release/1.0.0
release/2.1.0-beta

# Hotfix branches
hotfix/login-timeout-fix
hotfix/data-corruption-patch
```

### Commit Messages
```bash
# Feature development
feat: add task creation functionality
fix: resolve task validation issues
test: add comprehensive task tests
docs: update task management guide

# Release preparation
chore: bump version to 1.1.0
fix: resolve minor pre-release issues
docs: update changelog for v1.1.0

# Hotfix
hotfix: fix critical payment processing bug
test: verify payment hotfix correctness
```

### Pull Request Process

#### Feature PRs
1. **Base**: `develop`
2. **Review**: Required da almeno 1 team member
3. **Tests**: Tutti i test devono passare
4. **Merge**: Squash and merge per storia pulita

#### Release PRs
1. **Base**: `main`
2. **Review**: Required da team lead
3. **Testing**: Test completi inclusi E2E
4. **Merge**: Merge commit per preservare storia

#### Hotfix PRs
1. **Urgenza**: Review accelerata ma non saltata
2. **Testing**: Focus su area impattata
3. **Communication**: Notifica immediata al team

## 🛡️ Branch Protection

### Main Branch
```yaml
protection_rules:
  required_status_checks:
    - continuous-integration
    - security-scan
  required_pull_request_reviews:
    required_approving_review_count: 2
  restrictions:
    - admin_only
  enforce_admins: true
```

### Develop Branch
```yaml
protection_rules:
  required_status_checks:
    - continuous-integration
    - unit-tests
  required_pull_request_reviews:
    required_approving_review_count: 1
  dismiss_stale_reviews: true
```

## 🚀 GitHub Actions Integration

### Feature Workflow
```yaml
name: Feature Branch CI
on:
  pull_request:
    branches: [ develop ]
    types: [ opened, synchronize, reopened ]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run Tests
        run: |
          npm ci
          npm run lint
          npm run test:coverage
          npm run build
```

### Release Workflow
```yaml
name: Release Pipeline
on:
  push:
    branches: [ main ]
    tags: [ 'v*' ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Deploy to Production
        run: |
          npm ci
          npm run build
          npm run deploy:prod
```

## 📊 Vantaggi e Considerazioni

### ✅ Vantaggi
- **Struttura chiara**: Ruoli ben definiti per ogni branch
- **Tracciabilità**: Storia Git organizzata e leggibile
- **Stabilità**: Main branch sempre deployabile
- **Parallelismo**: Sviluppo feature indipendenti
- **Release management**: Processo controllato

### ⚠️ Considerazioni
- **Complessità**: Più complesso di GitHub Flow
- **Overhead**: Merge multipli per ogni feature
- **Learning curve**: Richiede comprensione del modello
- **Tool dependency**: Beneficia di Git Flow tools

## 🔧 Tools Consigliati

### Git Flow Extension
```bash
# Installazione
brew install git-flow-avh

# Inizializzazione
git flow init

# Utilizzo
git flow feature start new-feature
git flow feature finish new-feature
git flow release start 1.1.0
git flow release finish 1.1.0
```

### GitHub CLI Integration
```bash
# Creazione PR per feature
gh pr create --base develop --title "feat: new feature" --body "Description"

# Merge con squash
gh pr merge --squash --delete-branch
```

## 📝 Checklist Git Flow

### Pre-Feature Development
- [ ] Branch `develop` aggiornato
- [ ] Issue/task assegnata
- [ ] Naming convention seguita

### Durante Feature Development
- [ ] Commit frequenti e atomici
- [ ] Test scritti per nuove funzionalità
- [ ] Documentazione aggiornata
- [ ] Rebase regolare con develop

### Pre-Release
- [ ] Tutte le feature integrate in develop
- [ ] Test completi passati
- [ ] Version bump effettuato
- [ ] Changelog aggiornato

### Post-Release
- [ ] Tag creato su main
- [ ] Release notes pubblicate
- [ ] Deploy verificato
- [ ] Develop sincronizzato con main

---

*Questo workflow Git Flow è specificamente adattato per il progetto Task Manager e dovrebbe essere seguito da tutti i membri del team.*
