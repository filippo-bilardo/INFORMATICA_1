# Guida 1: Git Flow Spiegato

## Introduzione a Git Flow

Git Flow è un modello di branching per Git creato da Vincent Driessen che definisce uno strict branching model progettato intorno ai rilasci del progetto.

## Cos'è Git Flow?

### Definizione
Git Flow è:
- **Framework di branching** ben strutturato
- **Set di convenzioni** per organizzare branch
- **Workflow standardizzato** per team development
- **Estensione Git** con comandi semplificati

### Filosofia
- Branch hanno **ruoli specifici** e ben definiti
- **Separazione netta** tra sviluppo e rilasci
- **Parallelizzazione** del lavoro del team
- **Tracciabilità** di feature e release

## Struttura Branch Git Flow

### Branch Principali

#### Main Branch
```
main (o master):
- Contiene SOLO codice in produzione
- Ogni commit è una release
- Sempre stabile e deployabile
- Non si sviluppa mai direttamente qui
```

#### Develop Branch
```
develop:
- Branch principale di sviluppo
- Integra tutte le feature completate
- Base per nuove feature
- Punto di partenza per release
```

### Branch di Supporto

#### Feature Branches
```
Naming: feature/nome-funzionalita
Partono da: develop
Merge in: develop
Scopo: Sviluppo nuove funzionalità
Durata: Temporanei
```

#### Release Branches
```
Naming: release/versione (es. release/1.2.0)
Partono da: develop
Merge in: main E develop
Scopo: Preparazione rilascio
Durata: Breve (stabilizzazione)
```

#### Hotfix Branches
```
Naming: hotfix/descrizione
Partono da: main
Merge in: main E develop
Scopo: Correzioni urgenti produzione
Durata: Molto breve
```

## Workflow Git Flow Dettagliato

### 1. Inizializzazione Repository
```bash
# Setup Git Flow (con git-flow extension)
git flow init

# O manualmente:
git checkout -b develop main
git push -u origin develop
```

### 2. Sviluppo Feature

#### Inizio Feature
```bash
# Con git-flow
git flow feature start nuova-funzionalita

# Manualmente
git checkout develop
git pull origin develop
git checkout -b feature/nuova-funzionalita
```

#### Sviluppo Feature
```bash
# Lavoro normale su feature branch
git add .
git commit -m "Implement core functionality"
git commit -m "Add tests"
git commit -m "Update documentation"

# Push periodici per backup
git push origin feature/nuova-funzionalita
```

#### Completamento Feature
```bash
# Con git-flow
git flow feature finish nuova-funzionalita

# Manualmente
git checkout develop
git pull origin develop
git merge --no-ff feature/nuova-funzionalita
git push origin develop
git branch -d feature/nuova-funzionalita
git push origin --delete feature/nuova-funzionalita
```

### 3. Processo Release

#### Inizio Release
```bash
# Con git-flow
git flow release start 1.2.0

# Manualmente
git checkout develop
git pull origin develop
git checkout -b release/1.2.0
```

#### Preparazione Release
```bash
# Update version numbers
echo "1.2.0" > VERSION
git add VERSION
git commit -m "Bump version to 1.2.0"

# Bug fixes only (no new features!)
git commit -m "Fix critical bug in login"
git commit -m "Update changelog"

# Testing e stabilizzazione
git push origin release/1.2.0
```

#### Completamento Release
```bash
# Con git-flow
git flow release finish 1.2.0

# Manualmente:
# 1. Merge in main
git checkout main
git pull origin main
git merge --no-ff release/1.2.0
git tag -a v1.2.0 -m "Release version 1.2.0"
git push origin main --tags

# 2. Merge back in develop
git checkout develop
git pull origin develop
git merge --no-ff release/1.2.0
git push origin develop

# 3. Cleanup
git branch -d release/1.2.0
git push origin --delete release/1.2.0
```

### 4. Gestione Hotfix

#### Problema Critico in Produzione
```bash
# Con git-flow
git flow hotfix start critical-security-fix

# Manualmente
git checkout main
git pull origin main
git checkout -b hotfix/critical-security-fix
```

#### Risoluzione Hotfix
```bash
# Fix veloce e mirato
git add .
git commit -m "Fix critical security vulnerability"

# Test rapido
git commit -m "Add regression test"

# Update version (patch increment)
echo "1.2.1" > VERSION
git add VERSION
git commit -m "Bump version to 1.2.1"
```

#### Deploy Hotfix
```bash
# Con git-flow
git flow hotfix finish critical-security-fix

# Manualmente:
# 1. Merge in main
git checkout main
git merge --no-ff hotfix/critical-security-fix
git tag -a v1.2.1 -m "Hotfix version 1.2.1"
git push origin main --tags

# 2. Merge in develop
git checkout develop
git merge --no-ff hotfix/critical-security-fix
git push origin develop

# 3. Cleanup
git branch -d hotfix/critical-security-fix
```

## Vantaggi Git Flow

### Per Team
- **Standardizzazione**: Tutti seguono stesso workflow
- **Separazione ruoli**: Feature vs release vs hotfix
- **Parallelizzazione**: Lavoro simultaneo su più feature
- **Stabilità**: Main sempre deployabile

### Per Processo
- **Release planning**: Branch release dedicati
- **Hotfix rapidi**: Processo ben definito
- **Tracciabilità**: Storia pulita e comprensibile
- **Integrazione**: CI/CD può agganciarsi ai branch

### Per Codice
- **Quality gates**: Review obbligatorie
- **Testing**: Tempo per QA su release branch
- **Rollback**: Tag per ogni versione
- **Documentazione**: Changelog automatico

## Svantaggi Git Flow

### Complessità
- **Curva apprendimento** ripida per nuovi team
- **Overhead** per progetti semplici
- **Molti branch** da gestire simultaneamente

### Rigidità
- **Non adatto** a continuous deployment
- **Lento** per rilasci frequenti
- **Overkill** per team piccoli

### Manutenzione
- **Conflitti** potenziali tra develop e main
- **Sincronizzazione** complessa
- **Tool dependency** per git-flow extension

## Quando Usare Git Flow

### Ideale Per:
```
✅ Rilasci programmati (es. mensili/trimestrali)
✅ Team medio-grandi (5+ sviluppatori)
✅ Prodotti con versioning semantico
✅ Processi QA estesi
✅ Multiple versioni in supporto
✅ Compliance e audit trails
```

### Non Adatto Per:
```
❌ Continuous deployment
❌ Team molto piccoli (1-2 persone)
❌ Progetti sperimentali
❌ Rilasci molto frequenti
❌ Applicazioni web semplici
❌ Prototipo o MVP
```

## Varianti e Adattamenti

### Git Flow Semplificato
```
main + develop + feature/*
(senza release/hotfix branch)
```

### Git Flow Hybrid
```
Git Flow + GitHub Flow
Feature flags per release management
```

### Git Flow + CI/CD
```
Automated testing su tutti branch
Deployment automatico da main
Feature branch preview environments
```

## Tool e Estensioni

### Git Flow Extension
```bash
# Installazione
# macOS
brew install git-flow

# Ubuntu
sudo apt-get install git-flow

# Windows
# Scarica da: https://github.com/nvie/gitflow/wiki/Windows
```

### GUI Tools con Git Flow
- **SourceTree**: Support nativo Git Flow
- **GitKraken**: Git Flow integration
- **Tower**: Git Flow workflows
- **VS Code**: Git Flow extension

### Automazione
```bash
# Webhook per auto-deploy da main
# Slack notifications per releases
# Automated changelog generation
# Version bumping scripts
```

## Best Practices Git Flow

### Naming Conventions
```bash
# Feature branches
feature/user-authentication
feature/payment-integration
feature/admin-dashboard

# Release branches  
release/2.1.0
release/2.2.0-beta

# Hotfix branches
hotfix/login-security-fix
hotfix/payment-gateway-error
```

### Commit Messages
```bash
# Feature development
"Add user authentication service"
"Implement password validation"
"Add unit tests for auth service"

# Release preparation
"Bump version to 2.1.0"
"Update changelog for v2.1.0"
"Fix minor UI issues for release"

# Hotfix
"HOTFIX: Fix critical payment processing bug"
"HOTFIX: Add input validation to prevent XSS"
```

### Merge Strategies
```bash
# Feature -> develop: --no-ff sempre
git merge --no-ff feature/nome

# Release -> main: --no-ff + tag
git merge --no-ff release/1.0.0
git tag -a v1.0.0

# Hotfix: --no-ff in entrambi branch
```

## Migrazione a Git Flow

### Da Branch Singolo
```bash
# 1. Crea develop da main
git checkout main
git checkout -b develop
git push origin develop

# 2. Proteggi main branch
# GitHub: Settings > Branches > Add rule

# 3. Migra feature in corso
git checkout feature/existing
git rebase develop
```

### Da GitHub Flow
```bash
# Graduale:
# 1. Introduce develop branch
# 2. Feature branches -> develop
# 3. Aggiungi release process
# 4. Implement hotfix workflow
```

## Esempi Reali

### Startup in Crescita
```
Fase 1: GitHub Flow (team piccolo)
Fase 2: Git Flow semplificato (team cresce)
Fase 3: Git Flow completo (processi maturi)
```

### Enterprise Software
```
main: Produzione
develop: Integrazione continua
release/*: Stabilizzazione pre-rilascio
hotfix/*: Emergenze produzione
support/*: Manutenzione versioni vecchie
```

---

Git Flow fornisce struttura e disciplina per team che necessitano di rilasci controllati e processo robusto.
