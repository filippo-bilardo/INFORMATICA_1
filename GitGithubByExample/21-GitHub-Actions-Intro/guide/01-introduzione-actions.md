# 01 - Introduzione alle GitHub Actions

## 📖 Spiegazione Concettuale

**GitHub Actions** è una piattaforma di automazione CI/CD (Continuous Integration/Continuous Deployment) integrata direttamente in GitHub. Permette di automatizzare workflow di sviluppo, testing, building e deployment direttamente dai repository GitHub.

### Cosa Sono le GitHub Actions?

Immagina di avere un assistente digitale che:
- 🔍 **Monitora** il tuo repository 24/7
- ⚡ **Reagisce** automaticamente a eventi (push, PR, issue)
- 🔧 **Esegue** attività programmate (test, build, deploy)
- 📊 **Riporta** risultati e notifiche

### Perché Usare GitHub Actions?

```
Scenario Senza Actions:
1. Sviluppatore push codice
2. Manualmente run tests
3. Manualmente build applicazione
4. Manualmente deploy su server
5. Manualmente notificare team
❌ Processo lento, propenso a errori

Scenario Con Actions:
1. Sviluppatore push codice
2. 🤖 Actions automaticamente:
   - Esegue tests
   - Builda applicazione
   - Deploya se tutto ok
   - Notifica risultati
✅ Processo veloce, affidabile, automatico
```

## 🏗️ Architettura GitHub Actions

### Componenti Fondamentali

```yaml
Repository
├── .github/
│   └── workflows/          # Cartella workflow
│       ├── ci.yml         # Workflow file
│       ├── deploy.yml     # Altro workflow
│       └── release.yml    # Workflow release
├── src/                   # Codice sorgente
└── tests/                 # Test
```

### Anatomia di un Workflow

```yaml
# .github/workflows/ci.yml
name: CI Pipeline                    # Nome workflow

on:                                  # Trigger events
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:                               # Jobs da eseguire
  test:                             # Job name
    runs-on: ubuntu-latest          # Runner environment
    
    steps:                          # Passi del job
    - name: Checkout code           # Step name
      uses: actions/checkout@v4     # Azione predefinita
      
    - name: Setup Node.js           # Custom step
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        
    - name: Install dependencies    # Script personalizzato
      run: npm install
      
    - name: Run tests
      run: npm test
```

### Concetti Chiave

#### 1. **Workflows** 
- File YAML che definiscono automazione
- Posizionati in `.github/workflows/`
- Triggered da eventi specifici

#### 2. **Jobs**
- Unità di lavoro che contengono steps
- Eseguiti su runner (macchine virtuali)
- Possono dipendere da altri jobs

#### 3. **Steps**
- Singole attività dentro un job
- Possono eseguire azioni o comandi shell
- Eseguiti sequenzialmente

#### 4. **Actions**
- Blocchi riutilizzabili di codice
- Disponibili nel GitHub Marketplace
- Possono essere custom o community

#### 5. **Runners**
- Macchine virtuali che eseguono i workflow
- GitHub-hosted (ubuntu, windows, macos)
- Self-hosted (tuoi server)

## 💡 Casi d'Uso Pratici

### Scenario 1: CI/CD per App Web
```yaml
# .github/workflows/webapp-ci-cd.yml
name: Web App CI/CD

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - uses: actions/setup-node@v4
      with:
        node-version: '18'
    - run: npm ci
    - run: npm run test
    - run: npm run build
    
  deploy:
    needs: test
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    steps:
    - uses: actions/checkout@v4
    - name: Deploy to Vercel
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-org-id: ${{ secrets.ORG_ID }}
        vercel-project-id: ${{ secrets.PROJECT_ID }}
```

### Scenario 2: Automazione Release
```yaml
# .github/workflows/release.yml
name: Release

on:
  push:
    tags:
      - 'v*'

jobs:
  release:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    
    - name: Create Release
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        tag_name: ${{ github.ref }}
        release_name: Release ${{ github.ref }}
        draft: false
        prerelease: false
    
    - name: Build and Package
      run: |
        npm install
        npm run build
        tar -czf release.tar.gz dist/
    
    - name: Upload Release Asset
      uses: actions/upload-release-asset@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        upload_url: ${{ steps.create_release.outputs.upload_url }}
        asset_path: ./release.tar.gz
        asset_name: release.tar.gz
        asset_content_type: application/gzip
```

### Scenario 3: Code Quality Checks
```yaml
# .github/workflows/quality.yml
name: Code Quality

on: [push, pull_request]

jobs:
  lint:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - uses: actions/setup-node@v4
      with:
        node-version: '18'
    - run: npm ci
    - run: npm run lint
    
  security:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Run security audit
      run: npm audit --audit-level high
    
  test-coverage:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - uses: actions/setup-node@v4
      with:
        node-version: '18'
    - run: npm ci
    - run: npm run test:coverage
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage/lcov.info
```

### Scenario 4: Multi-Platform Testing
```yaml
# .github/workflows/multi-platform.yml
name: Multi-Platform Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        node-version: [16, 18, 20]
    
    steps:
    - uses: actions/checkout@v4
    - name: Use Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
    - run: npm ci
    - run: npm test
```

## 🔧 Eventi Trigger Comuni

### 1. **Push Events**
```yaml
on:
  push:
    branches: [ main, develop ]    # Solo questi branch
    paths: [ 'src/**' ]           # Solo se cambia src/
    tags: [ 'v*' ]                # Solo tag versione
```

### 2. **Pull Request Events**
```yaml
on:
  pull_request:
    types: [opened, synchronize, reopened]
    branches: [ main ]
    paths-ignore: ['docs/**']     # Ignora modifiche docs
```

### 3. **Schedule Events**
```yaml
on:
  schedule:
    - cron: '0 2 * * *'           # Ogni giorno alle 2:00 AM
    - cron: '0 */6 * * *'         # Ogni 6 ore
```

### 4. **Manual Trigger**
```yaml
on:
  workflow_dispatch:              # Trigger manuale
    inputs:
      environment:
        description: 'Environment to deploy'
        required: true
        default: 'staging'
        type: choice
        options:
        - staging
        - production
```

### 5. **Issue/Comment Events**
```yaml
on:
  issues:
    types: [opened, labeled]
  issue_comment:
    types: [created]
```

## 🎯 Actions Marketplace Popolari

### Development & Testing
```yaml
# Checkout repository
- uses: actions/checkout@v4

# Setup language environments
- uses: actions/setup-node@v4
- uses: actions/setup-python@v4
- uses: actions/setup-java@v4
- uses: actions/setup-go@v4

# Cache dependencies
- uses: actions/cache@v3
  with:
    path: ~/.npm
    key: ${{ runner.os }}-node-${{ hashFiles('**/package-lock.json') }}
```

### Deployment
```yaml
# Deploy to AWS
- uses: aws-actions/configure-aws-credentials@v4
- uses: aws-actions/amazon-ecr-login@v1

# Deploy to Azure
- uses: azure/login@v1
- uses: azure/webapps-deploy@v2

# Deploy to Heroku
- uses: akhileshns/heroku-deploy@v3.12.12
```

### Code Quality
```yaml
# SonarQube analysis
- uses: sonarqube-quality-gate-action@master

# Code coverage
- uses: codecov/codecov-action@v3

# Security scanning
- uses: github/codeql-action/analyze@v2
```

### Notifications
```yaml
# Slack notifications
- uses: 8398a7/action-slack@v3

# Email notifications
- uses: dawidd6/action-send-mail@v3

# Discord notifications
- uses: Ilshidur/action-discord@0.3.2
```

## ⚠️ Errori Comuni

### 1. **Syntax YAML Incorretta**
```yaml
# ❌ ERRORE: Indentazione sbagliata
name: CI
on:
push:                    # Dovrebbe essere indentato
  branches: [main]

# ✅ CORRETTO:
name: CI
on:
  push:
    branches: [main]
```

### 2. **Secrets Non Configurati**
```yaml
# ❌ ERRORE: Secret non esiste
- name: Deploy
  env:
    API_KEY: ${{ secrets.API_KEY }}  # Non configurato

# ✅ SOLUZIONE: Configura in Settings > Secrets
# Repository Settings > Secrets and variables > Actions
```

### 3. **Job Dependencies Incorrette**
```yaml
# ❌ ERRORE: Deploy prima di test
jobs:
  deploy:
    runs-on: ubuntu-latest
    # Manca needs: test
  
  test:
    runs-on: ubuntu-latest

# ✅ CORRETTO:
jobs:
  test:
    runs-on: ubuntu-latest
  
  deploy:
    needs: test              # Deploy dopo test
    runs-on: ubuntu-latest
```

### 4. **Trigger Troppo Ampi**
```yaml
# ❌ CATTIVO: Trigger su qualsiasi modifica
on: [push]

# ✅ MIGLIORE: Trigger specifico
on:
  push:
    branches: [main]
    paths: ['src/**', 'tests/**']
```

## 🎯 Best Practices

### 1. **Organizzazione Workflow**
```bash
.github/workflows/
├── ci.yml              # Continuous Integration
├── cd.yml              # Continuous Deployment  
├── codeql.yml          # Security analysis
├── release.yml         # Release automation
└── schedule.yml        # Scheduled tasks
```

### 2. **Naming Convention**
```yaml
# ✅ Nomi descrittivi
name: "Frontend CI/CD Pipeline"
jobs:
  test-unit:
    name: "Unit Tests"
  test-e2e:
    name: "End-to-End Tests"
  deploy-staging:
    name: "Deploy to Staging"
```

### 3. **Environment Variables e Secrets**
```yaml
env:
  NODE_VERSION: '18'
  REGISTRY: ghcr.io

jobs:
  build:
    env:
      DATABASE_URL: ${{ secrets.DATABASE_URL }}
      API_KEY: ${{ secrets.API_KEY }}
```

### 4. **Caching per Performance**
```yaml
- name: Cache node modules
  uses: actions/cache@v3
  with:
    path: ~/.npm
    key: ${{ runner.os }}-node-${{ hashFiles('**/package-lock.json') }}
    restore-keys: |
      ${{ runner.os }}-node-
```

## 🧪 Quiz di Autovalutazione

**1. Dove vengono posizionati i file workflow?**
- a) `.github/actions/`
- b) `.github/workflows/`
- c) `.actions/workflows/`
- d) `workflows/`

**2. Quale formato usano i file workflow?**
- a) JSON
- b) XML
- c) YAML
- d) TOML

**3. Cosa significa `needs: test` in un job?**
- a) Il job ha bisogno di test
- b) Il job dipende dal job chiamato "test"
- c) Il job esegue i test
- d) Il job può essere skippato

**4. Come si configurano le variabili sensibili?**
- a) Direttamente nel workflow
- b) Tramite GitHub Secrets
- c) In un file .env
- d) Nell'URL del repository

<details>
<summary>🔍 Risposte</summary>

1. **b)** `.github/workflows/`
2. **c)** YAML
3. **b)** Il job dipende dal job chiamato "test"
4. **b)** Tramite GitHub Secrets

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Primo Workflow
1. Crea file `.github/workflows/hello.yml`
2. Configura trigger su push
3. Job che stampa "Hello GitHub Actions"
4. Test con commit

### Esercizio 2: CI per Node.js
1. Crea workflow per progetto Node.js
2. Installa dipendenze
3. Esegui test
4. Builda progetto

### Esercizio 3: Multi-Job Workflow
1. Job per testing
2. Job per build (dipende da test)
3. Job per deploy (dipende da build)
4. Test con branch diversi

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [02 - Workflow e Jobs](02-workflow-jobs.md)
- **Modulo precedente**: [19 - Issues e Project Management](../../19-Issues-e-Project-Management/README.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 19-Issues-e-Project-Management](../../19-Issues-e-Project-Management/README.md)
- [➡️ 21-Pages-e-Documentazione](../../21-Pages-e-Documentazione/README.md)
