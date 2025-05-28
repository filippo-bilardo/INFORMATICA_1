# 02 - GitHub Actions Basics

## 📖 Spiegazione Concettuale

**GitHub Actions** utilizza una sintassi YAML dichiarativa per definire workflows automatizzati. Comprendere i componenti base e la loro sintassi è fondamentale per creare automazioni efficaci.

### Anatomia di un Workflow

```yaml
# .github/workflows/example.yml
name: Example Workflow                    # Nome del workflow (opzionale)

on:                                      # Eventi che triggano il workflow
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]
  schedule:
    - cron: '0 2 * * 1'                 # Ogni lunedì alle 2:00

env:                                     # Variabili d'ambiente globali
  NODE_VERSION: '18'
  APP_NAME: 'my-application'

jobs:                                    # Collezione di jobs
  build:                                 # ID del job
    name: Build Application              # Nome descrittivo (opzionale)
    runs-on: ubuntu-latest              # Ambiente di esecuzione
    
    outputs:                            # Output del job
      version: ${{ steps.version.outputs.version }}
    
    steps:                              # Lista di passi
    - name: Checkout Repository         # Nome del passo
      uses: actions/checkout@v4         # Azione predefinita
      
    - name: Setup Node.js               # Passo personalizzato
      uses: actions/setup-node@v4
      with:                             # Input per l'azione
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
        
    - name: Install Dependencies        # Comando shell
      run: npm install
      
    - name: Get Version                 # Passo con output
      id: version
      run: echo "version=$(npm version --json | jq -r '.version')" >> $GITHUB_OUTPUT
```

## 🎯 Eventi e Triggers

### Push Events

```yaml
on:
  push:
    branches:
      - main
      - 'feature/*'        # Pattern matching
      - '!feature/legacy'   # Esclusione
    paths:
      - 'src/**'           # Solo modifiche in src/
      - '!docs/**'         # Escludi docs
    tags:
      - 'v*.*.*'           # Tag versioning
```

### Pull Request Events

```yaml
on:
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches: [main]
    paths-ignore:
      - '**.md'
      - 'docs/**'

  pull_request_target:    # Per fork esterni (attenzione sicurezza!)
    types: [opened, synchronize]
```

### Schedule Events

```yaml
on:
  schedule:
    - cron: '0 9 * * 1-5'    # Giorni lavorativi alle 9:00
    - cron: '0 0 * * 0'      # Domenica a mezzanotte
    - cron: '*/15 * * * *'   # Ogni 15 minuti
```

### Manual Triggers

```yaml
on:
  workflow_dispatch:         # Trigger manuale
    inputs:
      environment:
        description: 'Environment to deploy'
        required: true
        default: 'staging'
        type: choice
        options:
          - staging
          - production
      debug:
        description: 'Enable debug mode'
        required: false
        default: false
        type: boolean
      version:
        description: 'Version to deploy'
        required: true
        type: string
```

### Repository Events

```yaml
on:
  issues:
    types: [opened, labeled]
  
  release:
    types: [published]
  
  repository_dispatch:       # Webhook personalizzato
    types: [deploy-command]
```

## 🏃‍♂️ Runners e Ambienti

### Runner Types

```yaml
jobs:
  ubuntu-job:
    runs-on: ubuntu-latest    # Ubuntu 22.04
    
  windows-job:
    runs-on: windows-latest   # Windows Server 2022
    
  macos-job:
    runs-on: macos-latest     # macOS 12
    
  specific-version:
    runs-on: ubuntu-20.04     # Versione specifica
    
  self-hosted:
    runs-on: self-hosted      # Runner personalizzato
    
  matrix-job:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
```

### Container Jobs

```yaml
jobs:
  container-job:
    runs-on: ubuntu-latest
    container:
      image: node:18-alpine
      env:
        NODE_ENV: development
      ports:
        - 3000
      volumes:
        - my_docker_volume:/volume_mount
      options: --cpus 1
```

### Service Containers

```yaml
jobs:
  test-with-db:
    runs-on: ubuntu-latest
    
    services:
      postgres:
        image: postgres:13
        env:
          POSTGRES_PASSWORD: postgres
          POSTGRES_DB: testdb
        ports:
          - 5432:5432
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
      
      redis:
        image: redis:6
        ports:
          - 6379:6379
        options: >-
          --health-cmd "redis-cli ping"
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
```

## 🔗 Job Dependencies

### Sequential Jobs

```yaml
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
    - name: Build app
      run: echo "Building..."
  
  test:
    needs: build              # Aspetta che build finisca
    runs-on: ubuntu-latest
    steps:
    - name: Run tests
      run: echo "Testing..."
  
  deploy:
    needs: [build, test]      # Aspetta entrambi i job
    runs-on: ubuntu-latest
    steps:
    - name: Deploy app
      run: echo "Deploying..."
```

### Conditional Dependencies

```yaml
jobs:
  build:
    runs-on: ubuntu-latest
    outputs:
      build-success: ${{ steps.build.outputs.success }}
    steps:
    - name: Build
      id: build
      run: |
        # Build logic
        echo "success=true" >> $GITHUB_OUTPUT
  
  deploy:
    needs: build
    runs-on: ubuntu-latest
    if: needs.build.outputs.build-success == 'true'
    steps:
    - name: Deploy
      run: echo "Deploying successful build..."
```

## 🔧 Variabili e Secrets

### Environment Variables

```yaml
env:
  GLOBAL_VAR: 'global-value'

jobs:
  example:
    runs-on: ubuntu-latest
    env:
      JOB_VAR: 'job-value'
    
    steps:
    - name: Use variables
      env:
        STEP_VAR: 'step-value'
      run: |
        echo "Global: $GLOBAL_VAR"
        echo "Job: $JOB_VAR"
        echo "Step: $STEP_VAR"
        echo "Built-in: $GITHUB_REPOSITORY"
        echo "Built-in: $GITHUB_SHA"
```

### Secrets Management

```yaml
jobs:
  deploy:
    runs-on: ubuntu-latest
    environment: production    # Environment protection
    
    steps:
    - name: Deploy with secrets
      env:
        API_KEY: ${{ secrets.API_KEY }}
        DB_PASSWORD: ${{ secrets.DB_PASSWORD }}
        AWS_ACCESS_KEY: ${{ secrets.AWS_ACCESS_KEY_ID }}
      run: |
        echo "Deploying with API key: ${API_KEY:0:4}***"
        # Deploy logic using secrets
```

### Dynamic Variables

```yaml
jobs:
  dynamic-vars:
    runs-on: ubuntu-latest
    
    steps:
    - name: Set dynamic variables
      run: |
        echo "BUILD_TIME=$(date -u +%Y%m%d-%H%M%S)" >> $GITHUB_ENV
        echo "BRANCH_NAME=${GITHUB_REF#refs/heads/}" >> $GITHUB_ENV
        
        if [ "${{ github.event_name }}" == "pull_request" ]; then
          echo "IS_PR=true" >> $GITHUB_ENV
        else
          echo "IS_PR=false" >> $GITHUB_ENV
        fi
    
    - name: Use dynamic variables
      run: |
        echo "Build time: $BUILD_TIME"
        echo "Branch: $BRANCH_NAME"
        echo "Is PR: $IS_PR"
```

## 📦 Artifacts e Caching

### Artifacts Management

```yaml
jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Build application
      run: |
        mkdir -p dist
        echo "Built application" > dist/app.js
    
    - name: Upload build artifacts
      uses: actions/upload-artifact@v3
      with:
        name: build-artifacts
        path: |
          dist/
          !dist/**/*.map
        retention-days: 5
    
    - name: Upload test results
      uses: actions/upload-artifact@v3
      if: always()           # Upload anche se i test falliscono
      with:
        name: test-results
        path: test-results.xml
  
  deploy:
    needs: build
    runs-on: ubuntu-latest
    
    steps:
    - name: Download artifacts
      uses: actions/download-artifact@v3
      with:
        name: build-artifacts
        path: ./build
    
    - name: List artifacts
      run: ls -la ./build
```

### Caching Strategies

```yaml
jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # Cache NPM dependencies
    - name: Cache Node modules
      uses: actions/cache@v3
      with:
        path: ~/.npm
        key: ${{ runner.os }}-node-${{ hashFiles('**/package-lock.json') }}
        restore-keys: |
          ${{ runner.os }}-node-
    
    # Cache Docker layers
    - name: Cache Docker layers
      uses: actions/cache@v3
      with:
        path: /tmp/.buildx-cache
        key: ${{ runner.os }}-buildx-${{ github.sha }}
        restore-keys: |
          ${{ runner.os }}-buildx-
    
    # Cache Gradle dependencies
    - name: Cache Gradle packages
      uses: actions/cache@v3
      with:
        path: |
          ~/.gradle/caches
          ~/.gradle/wrapper
        key: ${{ runner.os }}-gradle-${{ hashFiles('**/*.gradle*', '**/gradle-wrapper.properties') }}
        restore-keys: |
          ${{ runner.os }}-gradle-
```

## 🎭 Matrix Strategies

### Basic Matrix

```yaml
jobs:
  test:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
        os: [ubuntu-latest, windows-latest, macos-latest]
    
    steps:
    - uses: actions/checkout@v4
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
    - name: Run tests on ${{ matrix.os }}
      run: npm test
```

### Advanced Matrix

```yaml
jobs:
  test:
    runs-on: ${{ matrix.os }}
    strategy:
      fail-fast: false        # Continua anche se un job fallisce
      max-parallel: 4         # Massimo 4 job in parallelo
      matrix:
        include:
          - os: ubuntu-latest
            node-version: 18
            npm-cache: ~/.npm
          - os: windows-latest
            node-version: 18
            npm-cache: ~\AppData\Roaming\npm-cache
          - os: macos-latest
            node-version: 18
            npm-cache: ~/.npm
        exclude:
          - os: windows-latest
            node-version: 16    # Escludi combinazione specifica
    
    steps:
    - uses: actions/checkout@v4
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache-dependency-path: package-lock.json
    - name: Cache dependencies
      uses: actions/cache@v3
      with:
        path: ${{ matrix.npm-cache }}
        key: ${{ runner.os }}-node-${{ matrix.node-version }}-${{ hashFiles('**/package-lock.json') }}
```

## 🔍 Debugging e Troubleshooting

### Debug Mode

```yaml
jobs:
  debug:
    runs-on: ubuntu-latest
    
    steps:
    - name: Enable debug logging
      run: echo "ACTIONS_STEP_DEBUG=true" >> $GITHUB_ENV
    
    - name: Debug information
      run: |
        echo "GitHub Context:"
        echo "Event: ${{ github.event_name }}"
        echo "Ref: ${{ github.ref }}"
        echo "SHA: ${{ github.sha }}"
        echo "Actor: ${{ github.actor }}"
        echo "Repository: ${{ github.repository }}"
        
        echo "Runner Context:"
        echo "OS: ${{ runner.os }}"
        echo "Arch: ${{ runner.arch }}"
        echo "Temp: ${{ runner.temp }}"
        echo "Tool Cache: ${{ runner.tool_cache }}"
```

### Error Handling

```yaml
jobs:
  resilient-job:
    runs-on: ubuntu-latest
    
    steps:
    - name: Step that might fail
      id: risky-step
      continue-on-error: true    # Continua anche se fallisce
      run: |
        exit 1  # Simula errore
    
    - name: Handle failure
      if: steps.risky-step.outcome == 'failure'
      run: |
        echo "Previous step failed, but we're handling it"
        # Recovery logic
    
    - name: Always run cleanup
      if: always()              # Esegui sempre, anche se ci sono errori
      run: |
        echo "Cleaning up resources"
        # Cleanup logic
    
    - name: Only on success
      if: success()
      run: echo "All previous steps succeeded"
    
    - name: Only on failure
      if: failure()
      run: echo "At least one step failed"
```

## 🧪 Quiz di Verifica

### Domanda 1
**Quale sintassi è corretta per eseguire un job solo quando il branch è 'main' e l'evento è push?**

A) `if: github.ref == 'main' && github.event_name == 'push'`
B) `if: github.ref == 'refs/heads/main' && github.event_name == 'push'`
C) `if: branch == 'main' && event == 'push'`
D) `condition: ref=main AND event=push`

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

La sintassi corretta usa `github.ref == 'refs/heads/main'` perché `github.ref` include il prefisso completo del riferimento Git, e `github.event_name` per il tipo di evento.
</details>

### Domanda 2
**Qual è la differenza tra `needs` e `if` in un job?**

A) `needs` definisce dipendenze, `if` condizioni di esecuzione
B) `needs` è per variabili, `if` per dipendenze
C) Non c'è differenza
D) `needs` è obsoleto, usa solo `if`

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: A**

`needs` definisce le dipendenze tra job (quali job devono completarsi prima), mentre `if` definisce condizioni booleane per l'esecuzione del job o step.
</details>

### Domanda 3
**Quale strategia è migliore per testare su multiple versioni di Node.js?**

A) Job separati per ogni versione
B) Matrix strategy con node-version array
C) Script che installa tutte le versioni
D) Usare solo l'ultima versione

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

Matrix strategy con array di versioni Node.js è l'approccio più efficiente, permette test paralleli, configurazione centralizzata e facile manutenzione.
</details>

## 📚 Prossimi Passi

Ora che conosci i componenti base di GitHub Actions, sei pronto per:

1. **[Workflow Configuration](./03-workflow-configuration.md)** - Configurazioni avanzate e best practices
2. **[Marketplace Actions](./04-marketplace-actions.md)** - Azioni predefinite e personalizzate
3. **[Esempi Pratici](../esempi/01-first-workflow.md)** - Implementazioni reali

Continua con la prossima guida per approfondire le configurazioni avanzate!
