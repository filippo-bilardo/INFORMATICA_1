# 01 - Git Flow Fundamentals

## Obiettivi di Apprendimento
- Comprendere la filosofia e i principi di Git Flow
- Configurare Git Flow in un progetto
- Gestire i diversi tipi di branch nel workflow
- Implementare il ciclo di sviluppo completo
- Comprendere vantaggi e svantaggi di Git Flow
- Confrontare Git Flow con altre strategie

## 1. Introduzione a Git Flow

### 1.1 Cos'è Git Flow

Git Flow è un modello di branching sviluppato da Vincent Driessen che definisce un framework rigido per gestire i branch in progetti di sviluppo software. È particolarmente adatto per progetti con release pianificate e team di sviluppo strutturati.

```
Git Flow Philosophy:
┌────────────────────────────────────────────┐
│  "A successful Git branching model"        │
│  - Vincent Driessen                        │
│                                            │
│  🎯 Obiettivi:                             │  
│  • Separazione netta tra sviluppo e prod   │
│  • Release controllate e tracciabili       │
│  • Hotfix immediati per produzione         │ 
│  • Sviluppo parallelo di feature           │
└────────────────────────────────────────────┘
```

### 1.2 Quando Usare Git Flow

**✅ Ideale per:**
- Progetti con release schedulate
- Team di sviluppo medio-grandi (5+ sviluppatori)
- Applicazioni che richiedono alta stabilità
- Progetti con cicli di testing rigorosi
- Software con versioni multiple in produzione

**❌ Non adatto per:**
- Progetti con continuous deployment
- Team piccoli (1-3 sviluppatori)
- Applicazioni web che deployano giornalmente
- Progetti open source con contributi sporadici

### 1.3 Branch Structure Overview

```mermaid
gitgraph
    commit id: "Initial"
    branch develop
    checkout develop
    commit id: "Dev 1"
    
    branch feature/login
    checkout feature/login
    commit id: "Login UI"
    commit id: "Login Logic"
    
    checkout develop
    merge feature/login
    commit id: "Merge login"
    
    branch release/1.0
    checkout release/1.0
    commit id: "Bug fixes"
    commit id: "Version bump"
    
    checkout main
    merge release/1.0
    tag: "v1.0.0"
    
    checkout develop
    merge release/1.0
```

## 2. Tipi di Branch in Git Flow

### 2.1 Main Branches

#### Master/Main Branch
```bash
# Il branch principale - solo codice pronto per produzione
git checkout main
git log --oneline
# * f2a3b4c (tag: v2.1.0) Release 2.1.0
# * a1b2c3d (tag: v2.0.0) Release 2.0.0
# * 9e8f7d6 (tag: v1.0.0) Initial release
```

**Caratteristiche:**
- ✅ Solo codice stabile e testato
- ✅ Ogni commit rappresenta una release
- ✅ Taggato con numeri di versione
- ❌ Mai sviluppo diretto su questo branch

#### Develop Branch
```bash
# Branch di integrazione per lo sviluppo
git checkout develop
git log --oneline
# * e4f5g6h Merge feature/user-profile
# * c2d3e4f Merge feature/payment-system
# * a1b2c3d Latest stable state
```

**Caratteristiche:**
- ✅ Punto di integrazione per tutte le feature
- ✅ Rappresenta lo stato più recente dello sviluppo
- ✅ Base per nuove feature branch
- ✅ Periodicamente mergiato in release branch

### 2.2 Supporting Branches

#### Feature Branches
```bash
# Convenzione naming: feature/nome-feature
feature/user-authentication
feature/payment-gateway
feature/admin-dashboard
feature/mobile-responsive
```

**Workflow Feature Branch:**
```bash
# 1. Crea feature branch da develop
git checkout develop
git pull origin develop
git checkout -b feature/user-profile

# 2. Sviluppa la feature
echo "User profile component" > src/components/UserProfile.js
git add .
git commit -m "Add user profile component"

# 3. Continua sviluppo
echo "Profile validation" >> src/components/UserProfile.js
git commit -am "Add profile validation"

# 4. Push della feature
git push origin feature/user-profile

# 5. Crea Pull Request su develop
# 6. Dopo review e merge, elimina branch
git checkout develop
git pull origin develop
git branch -d feature/user-profile
git push origin --delete feature/user-profile
```

#### Release Branches
```bash
# Convenzione naming: release/versione
release/1.2.0
release/2.0.0-beta
release/hotfix-1.1.1
```

**Workflow Release Branch:**
```bash
# 1. Crea release branch da develop
git checkout develop
git pull origin develop
git checkout -b release/1.2.0

# 2. Preparazione release (bug fixes, version bump)
echo "1.2.0" > VERSION
git commit -am "Bump version to 1.2.0"

# 3. Bug fixes durante stabilizzazione
git commit -am "Fix critical bug in payment module"

# 4. Merge in main e tag
git checkout main
git merge --no-ff release/1.2.0
git tag -a v1.2.0 -m "Release version 1.2.0"

# 5. Merge back in develop
git checkout develop
git merge --no-ff release/1.2.0

# 6. Cleanup
git branch -d release/1.2.0
git push origin main develop --tags
```

#### Hotfix Branches
```bash
# Convenzione naming: hotfix/descrizione
hotfix/critical-security-fix
hotfix/payment-bug
hotfix/login-issue
```

**Workflow Hotfix Branch:**
```bash
# 1. Crea hotfix da main (urgenza!)
git checkout main
git pull origin main
git checkout -b hotfix/payment-critical-fix

# 2. Fix immediato
echo "Fixed payment processing bug" > HOTFIX_NOTES.md
git add .
git commit -m "Fix critical payment processing bug"

# 3. Test del fix
npm test

# 4. Merge in main
git checkout main
git merge --no-ff hotfix/payment-critical-fix
git tag -a v1.1.1 -m "Hotfix v1.1.1 - Payment fix"

# 5. Merge in develop
git checkout develop
git merge --no-ff hotfix/payment-critical-fix

# 6. Deploy immediato e cleanup
git push origin main develop --tags
git branch -d hotfix/payment-critical-fix
```

## 3. Setup e Configurazione

### 3.1 Git Flow Extension

```bash
# Installazione su macOS
brew install git-flow-avh

# Installazione su Ubuntu/Debian
sudo apt-get install git-flow

# Installazione su Windows (Git Bash)
# Download da: https://github.com/petervanderdoes/gitflow-avh
```

### 3.2 Inizializzazione Progetto

```bash
# Inizializza Git Flow in un repository
cd my-project
git flow init

# Configurazione interattiva:
Which branch should be used for bringing forth production releases?
   - main
Branch name for production releases: [main] 

Which branch should be used for integration of the "next release"?
   - develop
Branch name for "next release" development: [develop] 

Feature branches? [feature/] 
Release branches? [release/] 
Hotfix branches? [hotfix/] 
Support branches? [support/] 
Version tag prefix? []
```

### 3.3 Configurazione Automatica

```bash
# Script per setup automatico
#!/bin/bash
# setup-gitflow.sh

echo "🚀 Setting up Git Flow for project..."

# Inizializza Git Flow con defaults
git flow init -d

# Configura branch tracking
git config gitflow.branch.master main
git config gitflow.branch.develop develop
git config gitflow.prefix.feature feature/
git config gitflow.prefix.release release/
git config gitflow.prefix.hotfix hotfix/
git config gitflow.prefix.support support/
git config gitflow.prefix.versiontag ""

# Push initial branches
git push origin main develop

echo "✅ Git Flow configured successfully!"
echo "📝 Main branches:"
echo "   - main (production)"
echo "   - develop (integration)"
```

## 4. Workflow Completo Git Flow

### 4.1 Sviluppo Feature Completa

```bash
# ========================================
# FASE 1: SVILUPPO FEATURE
# ========================================

# Inizio nuova feature
git flow feature start user-authentication

# Sviluppo incrementale
echo "// User authentication module" > src/auth.js
git add src/auth.js
git commit -m "feat: add authentication module skeleton"

echo "function login(username, password) {}" >> src/auth.js
git commit -am "feat: add login function"

echo "function logout() {}" >> src/auth.js
git commit -am "feat: add logout function"

# Test della feature
npm test -- --grep "authentication"
git commit -am "test: add authentication tests"

# ========================================
# FASE 2: REVISIONE E INTEGRAZIONE
# ========================================

# Publish feature per review
git flow feature publish user-authentication

# Dopo review, finisci feature
git flow feature finish user-authentication
# Questo automaticamente:
# 1. Merge feature/user-authentication in develop
# 2. Elimina feature branch
# 3. Switcha a develop

# ========================================
# FASE 3: PREPARAZIONE RELEASE
# ========================================

# Quando develop è pronto per release
git flow release start 1.1.0

# Stabilizzazione e bug fixes
echo "1.1.0" > package.json
git commit -am "chore: bump version to 1.1.0"

# Fix bug minori
git commit -am "fix: resolve authentication edge cases"

# Test completi
npm run test:full
npm run test:e2e

# ========================================
# FASE 4: RELEASE
# ========================================

# Finisci release
git flow release finish 1.1.0
# Questo automaticamente:
# 1. Merge release/1.1.0 in main
# 2. Tag con v1.1.0
# 3. Merge back in develop
# 4. Elimina release branch

# Deploy in produzione
git push origin main develop --tags
```

### 4.2 Gestione Hotfix Urgente

```bash
# ========================================
# SCENARIO: BUG CRITICO IN PRODUZIONE
# ========================================

# Identifica problema
git checkout main
git log --oneline -5
# * a1b2c3d (tag: v1.1.0) Release 1.1.0
# Issue: Payment system down!

# Inizio hotfix
git flow hotfix start payment-critical-fix

# Fix veloce e preciso
echo "// Fixed payment processing timeout" > HOTFIX.md
git add HOTFIX.md
git commit -m "hotfix: fix payment processing timeout"

# Test immediato del fix
npm test -- --grep "payment"

# Deploy hotfix
git flow hotfix finish payment-critical-fix
# Tag automatico: v1.1.1

# Deploy immediato
git push origin main develop --tags

# Notifica team
echo "🚨 HOTFIX DEPLOYED: v1.1.1 - Payment system restored"
```

## 5. Automazione con Scripts

### 5.1 Script Helper per Feature

```bash
#!/bin/bash
# scripts/new-feature.sh

feature_name=$1
if [ -z "$feature_name" ]; then
    echo "Usage: ./scripts/new-feature.sh <feature-name>"
    exit 1
fi

echo "🚀 Starting new feature: $feature_name"

# Assicurati di essere su develop aggiornato
git checkout develop
git pull origin develop

# Inizia feature
git flow feature start "$feature_name"

# Setup iniziale
mkdir -p "src/features/$feature_name"
echo "// Feature: $feature_name" > "src/features/$feature_name/index.js"
echo "# Feature: $feature_name" > "src/features/$feature_name/README.md"

git add .
git commit -m "feat: initialize $feature_name feature"

echo "✅ Feature $feature_name initialized!"
echo "📁 Files created:"
echo "   - src/features/$feature_name/index.js"
echo "   - src/features/$feature_name/README.md"
```

### 5.2 Script Release Automation

```bash
#!/bin/bash
# scripts/prepare-release.sh

version=$1
if [ -z "$version" ]; then
    echo "Usage: ./scripts/prepare-release.sh <version>"
    exit 1
fi

echo "📦 Preparing release: $version"

# Pre-release checks
echo "🔍 Running pre-release checks..."
npm test
npm run lint
npm run build

if [ $? -ne 0 ]; then
    echo "❌ Pre-release checks failed!"
    exit 1
fi

# Start release
git flow release start "$version"

# Update version in files
echo "📝 Updating version in package.json..."
npm version "$version" --no-git-tag-version

# Generate changelog
echo "📋 Generating changelog..."
npx conventional-changelog -p angular -i CHANGELOG.md -s

git add .
git commit -m "chore: prepare release $version"

echo "✅ Release $version prepared!"
echo "🔄 Next steps:"
echo "   1. Review changes"
echo "   2. Run: git flow release finish $version"
echo "   3. Push: git push origin main develop --tags"
```

## 6. Best Practices

### 6.1 Naming Conventions

```bash
# Feature branches
feature/user-authentication     ✅ Descrittivo
feature/fix-login-bug          ✅ Chiaro
feature/JIRA-123-payment       ✅ Con ticket reference
feature/stuff                  ❌ Troppo generico
feature/John-work              ❌ Nome personale

# Release branches
release/1.2.0                  ✅ Semantic versioning
release/2024-Q1                ✅ Date-based
release/sprint-15              ✅ Sprint-based
release/new-version            ❌ Non specifico

# Hotfix branches
hotfix/payment-timeout-fix     ✅ Descrittivo
hotfix/critical-security       ✅ Urgenza chiara
hotfix/URGENT-login-issue      ✅ Priorità evidente
hotfix/bug                     ❌ Troppo generico
```

### 6.2 Commit Message Standards

```bash
# Conventional Commits per Git Flow
feat(auth): add two-factor authentication
fix(payment): resolve timeout in credit card processing
chore(release): bump version to 1.2.0
docs(readme): update Git Flow setup instructions
test(auth): add integration tests for login flow
refactor(api): improve error handling consistency

# Esempi per diversi branch types
# Feature branch commits:
feat: implement user profile editor
test: add unit tests for profile validation
docs: document profile API endpoints

# Release branch commits:
chore: bump version to 1.1.0
fix: resolve minor UI glitches
docs: update release notes

# Hotfix branch commits:
hotfix: fix critical payment processing bug
test: verify payment hotfix works correctly
```

### 6.3 Testing Strategy

```javascript
// tests/git-flow-integration.test.js
describe('Git Flow Integration Tests', () => {
  describe('Feature Branch Tests', () => {
    it('should run all tests before feature finish', async () => {
      // Test che ogni feature deve passare
      await runUnitTests();
      await runIntegrationTests();
      await runLintChecks();
    });
  });

  describe('Release Branch Tests', () => {
    it('should run comprehensive test suite', async () => {
      await runUnitTests();
      await runIntegrationTests();
      await runE2ETests();
      await runPerformanceTests();
      await runSecurityTests();
    });
  });

  describe('Hotfix Branch Tests', () => {
    it('should run focused tests for hotfix area', async () => {
      await runCriticalPathTests();
      await runRegressionTests();
      await runSmokeTests();
    });
  });
});
```

## 7. Problemi Comuni e Soluzioni

### 7.1 Troubleshooting Git Flow

| Problema | Causa | Soluzione |
|----------|-------|-----------|
| `git flow init` fallisce | Repository non inizializzato | `git init` prima di `git flow init` |
| Feature branch non si merge | Conflitti in develop | Risolvi conflitti manualmente |
| Release branch ha troppi change | Develop non stabile | Stabilizza develop prima del release |
| Hotfix non applica in develop | Develop diverged da main | Merge conflicts resolution necessaria |

### 7.2 Recovery da Situazioni Problematiche

```bash
# Scenario: Feature branch corrotta
git checkout develop
git branch -D feature/broken-feature
git flow feature start broken-feature-fixed

# Scenario: Release branch con problemi
git flow release finish --keep  # Mantieni branch per debug
git checkout release/1.2.0
git reset --hard HEAD~3  # Torna indietro di 3 commits
git flow release finish 1.2.0

# Scenario: Hotfix applicato male
git checkout main
git revert HEAD  # Revert dell'ultimo commit (hotfix)
git checkout develop
git revert HEAD  # Revert anche in develop
```

## 8. Monitoraggio e Metriche

### 8.1 Git Flow Metrics

```bash
#!/bin/bash
# scripts/gitflow-metrics.sh

echo "📊 Git Flow Metrics Report"
echo "=========================="

# Feature branch metrics
echo "🔧 Feature Branches:"
git branch -r | grep "feature/" | wc -l
echo "   Active features: $(git branch -r | grep "feature/" | wc -l)"

# Release cycle metrics
echo "📦 Releases:"
git tag | grep -E "^v[0-9]" | tail -5
echo "   Last 5 releases: $(git tag | grep -E "^v[0-9]" | tail -5 | tr '\n' ' ')"

# Hotfix metrics
echo "🚨 Hotfixes:"
git log --grep="hotfix" --oneline | head -5
echo "   Recent hotfixes: $(git log --grep="hotfix" --oneline | wc -l)"

# Branch health
echo "🏥 Branch Health:"
echo "   Main commits: $(git rev-list --count main)"
echo "   Develop commits: $(git rev-list --count develop)"
echo "   Ahead/behind: $(git rev-list --left-right --count main...develop)"
```

## Quiz di Verifica

### Domanda 1
In Git Flow, da quale branch si creano le feature branch?
- a) main
- b) develop
- c) release
- d) master

### Domanda 2
Quale tipo di branch è utilizzato per fix urgenti in produzione?
- a) feature
- b) release
- c) hotfix
- d) support

### Domanda 3
Dopo aver finito una release branch, dove viene mergiata?
- a) Solo in main
- b) Solo in develop
- c) In main e develop
- d) In una nuova branch

### Domanda 4
Quale comando inizializza Git Flow in un repository?
- a) git init flow
- b) git flow start
- c) git flow init
- d) git flow setup

### Domanda 5
In Git Flow, il branch main contiene:
- a) Codice in sviluppo
- b) Solo codice pronto per produzione
- c) Feature sperimentali
- d) Backup del codice

## Esercizi Pratici

### Esercizio 1: Setup Git Flow Base
Inizializza Git Flow in un nuovo progetto e crea la prima feature:
1. Crea repository locale
2. Inizializza Git Flow
3. Crea feature branch
4. Sviluppa semplice funzionalità
5. Completa il ciclo feature

### Esercizio 2: Gestione Release
Simula un ciclo di release completo:
1. Prepara release branch
2. Fix bug di stabilizzazione
3. Completa release con tag
4. Verifica merge in main e develop

### Esercizio 3: Hotfix Emergency
Simula gestione hotfix urgente:
1. Identifica "bug critico" in main
2. Crea hotfix branch
3. Implementa fix
4. Deploya hotfix
5. Verifica propagazione in develop

---

## Navigazione

⬅️ **Precedente**: [22 - Pages e Documentazione](../../22-Pages-e-Documentazione/README.md)

➡️ **Successivo**: [02 - GitHub Flow vs Alternatives](02-github-flow-alternatives.md)

🏠 **Home**: [Indice Generale](../../README.md)
