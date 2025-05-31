# 01 - CI/CD Concepts

## 📖 Spiegazione Concettuale

**CI/CD** rappresenta una metodologia fondamentale nel software moderno che automatizza il processo di integrazione, testing e deployment del codice. GitHub Actions implementa questi concetti fornendo una piattaforma potente e integrata.

### Continuous Integration (CI)

```
🔄 Continuous Integration Flow:
Developer → Commit → Push → Automated Tests → Build → Feedback
    ↑                                                    ↓
    └────────────── Fix Issues ← Report Results ←────────┘
```

**Continuous Integration** è la pratica di:
- **Integrare** frequentemente le modifiche nel repository principale
- **Automatizzare** tests e builds ad ogni modifica
- **Rilevare** problemi rapidamente e in modo consistente
- **Mantenere** sempre il codice in stato "deployable"

#### Vantaggi CI:
- ✅ **Rilevamento precoce** di bug e conflitti
- ✅ **Riduzione rischi** di integrazione
- ✅ **Feedback rapido** per gli sviluppatori
- ✅ **Qualità code** consistente

### Continuous Deployment (CD)

```
🚀 Continuous Deployment Pipeline:
Code → CI → Staging → Tests → Production → Monitoring
  ↑                                           ↓
  └──────── Rollback if needed ←──────────────┘
```

**Continuous Deployment** estende CI con:
- **Deployment automatico** in staging/production
- **Testing** in ambienti reali
- **Rollback** automatico in caso di problemi
- **Monitoring** continuo delle performance

## 🏗️ Implementazione CI/CD con GitHub Actions

### Workflow CI Tipico

```yaml
name: CI Pipeline
on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run linting
      run: npm run lint
    
    - name: Run unit tests
      run: npm run test:unit
    
    - name: Run integration tests
      run: npm run test:integration
    
    - name: Generate coverage report
      run: npm run test:coverage
    
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage/lcov.info
```

### Workflow CD Completo

```yaml
name: CD Pipeline
on:
  push:
    branches: [main]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    - run: npm ci
    - run: npm test
  
  build:
    needs: test
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    - run: npm ci
    - run: npm run build
    - name: Upload build artifacts
      uses: actions/upload-artifact@v3
      with:
        name: build-files
        path: dist/
  
  deploy-staging:
    needs: build
    runs-on: ubuntu-latest
    environment: staging
    steps:
    - name: Download build artifacts
      uses: actions/download-artifact@v3
      with:
        name: build-files
        path: dist/
    - name: Deploy to staging
      run: |
        echo "Deploying to staging environment..."
        # Deploy logic here
  
  deploy-production:
    needs: deploy-staging
    runs-on: ubuntu-latest
    environment: production
    if: github.event_name == 'push' && github.ref == 'refs/heads/main'
    steps:
    - name: Download build artifacts
      uses: actions/download-artifact@v3
      with:
        name: build-files
        path: dist/
    - name: Deploy to production
      run: |
        echo "Deploying to production environment..."
        # Production deployment logic
```

## 🎯 Best Practices CI/CD

### 1. **Test Strategy**

```yaml
# Multi-level testing approach
jobs:
  unit-tests:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Run unit tests
      run: npm run test:unit
  
  integration-tests:
    runs-on: ubuntu-latest
    services:
      postgres:
        image: postgres:13
        env:
          POSTGRES_PASSWORD: postgres
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
    steps:
    - uses: actions/checkout@v4
    - name: Run integration tests
      run: npm run test:integration
  
  e2e-tests:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Start application
      run: npm start &
    - name: Wait for app to be ready
      run: npx wait-on http://localhost:3000
    - name: Run E2E tests
      run: npm run test:e2e
```

### 2. **Environment Management**

```yaml
name: Multi-Environment Deploy
on:
  push:
    branches: [main, develop]

jobs:
  deploy:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        environment: 
          - ${{ github.ref == 'refs/heads/main' && 'production' || 'staging' }}
    environment: 
      name: ${{ matrix.environment }}
      url: ${{ steps.deploy.outputs.url }}
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Set environment variables
      run: |
        if [ "${{ matrix.environment }}" == "production" ]; then
          echo "API_URL=https://api.myapp.com" >> $GITHUB_ENV
          echo "DB_NAME=myapp_prod" >> $GITHUB_ENV
        else
          echo "API_URL=https://staging-api.myapp.com" >> $GITHUB_ENV
          echo "DB_NAME=myapp_staging" >> $GITHUB_ENV
        fi
    
    - name: Deploy application
      id: deploy
      run: |
        echo "Deploying to ${{ matrix.environment }}"
        echo "API_URL: $API_URL"
        echo "DB_NAME: $DB_NAME"
        # Deployment logic
        echo "url=https://${{ matrix.environment }}.myapp.com" >> $GITHUB_OUTPUT
```

### 3. **Security e Secrets Management**

```yaml
name: Secure Deployment
on:
  push:
    branches: [main]

jobs:
  deploy:
    runs-on: ubuntu-latest
    environment: production
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Configure AWS credentials
      uses: aws-actions/configure-aws-credentials@v2
      with:
        aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
        aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
        aws-region: us-east-1
    
    - name: Login to Amazon ECR
      uses: aws-actions/amazon-ecr-login@v1
    
    - name: Build and push Docker image
      env:
        ECR_REGISTRY: ${{ steps.login-ecr.outputs.registry }}
        ECR_REPOSITORY: myapp
        IMAGE_TAG: ${{ github.sha }}
      run: |
        docker build -t $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG .
        docker push $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG
    
    - name: Deploy to ECS
      run: |
        aws ecs update-service \
          --cluster myapp-cluster \
          --service myapp-service \
          --force-new-deployment
```

## 🔧 Monitoring e Alerting

### Workflow con Notifiche

```yaml
name: CI with Notifications
on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    - name: Run tests
      run: npm test
    
    - name: Notify success
      if: success()
      uses: 8398a7/action-slack@v3
      with:
        status: success
        channel: '#ci-cd'
        webhook_url: ${{ secrets.SLACK_WEBHOOK }}
    
    - name: Notify failure
      if: failure()
      uses: 8398a7/action-slack@v3
      with:
        status: failure
        channel: '#ci-cd'
        webhook_url: ${{ secrets.SLACK_WEBHOOK }}
```

### Health Checks e Rollback

```yaml
name: Deploy with Health Check
on:
  push:
    branches: [main]

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - name: Deploy application
      run: |
        echo "Deploying new version..."
        # Deployment logic
    
    - name: Health check
      run: |
        for i in {1..10}; do
          if curl -f http://myapp.com/health; then
            echo "Health check passed"
            exit 0
          fi
          echo "Health check failed, retrying in 30s..."
          sleep 30
        done
        echo "Health check failed after 10 attempts"
        exit 1
    
    - name: Rollback on failure
      if: failure()
      run: |
        echo "Rolling back to previous version..."
        # Rollback logic
```

## 📊 Metriche e Analisi

### Build Performance Tracking

```yaml
name: Performance Tracking
on: [push]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Track build time
      run: |
        START_TIME=$(date +%s)
        npm run build
        END_TIME=$(date +%s)
        BUILD_TIME=$((END_TIME - START_TIME))
        echo "Build completed in ${BUILD_TIME} seconds"
        echo "build_time=${BUILD_TIME}" >> $GITHUB_OUTPUT
      id: build
    
    - name: Report metrics
      run: |
        curl -X POST https://api.myapp.com/metrics \
          -H "Content-Type: application/json" \
          -d '{
            "metric": "build_time",
            "value": ${{ steps.build.outputs.build_time }},
            "commit": "${{ github.sha }}",
            "branch": "${{ github.ref_name }}"
          }'
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la differenza principale tra Continuous Integration e Continuous Deployment?**

A) CI si occupa solo di testing, CD solo di deployment
B) CI integra frequentemente il codice e automatizza test/build, CD automatizza anche il deployment
C) CI è per frontend, CD per backend
D) Non c'è differenza significativa

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

CI (Continuous Integration) si concentra sull'integrazione frequente del codice con automazione di test e build. CD (Continuous Deployment) estende CI automatizzando anche il deployment in ambienti di staging e produzione.
</details>

### Domanda 2
**Quale strategia è migliore per gestire multiple environment in un pipeline CI/CD?**

A) Un workflow separato per ogni environment
B) Uso di matrix strategy e environment protection rules
C) Deploy sempre solo in produzione
D) Deploy manuale per tutti gli environment

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

L'uso di matrix strategy combinato con environment protection rules permette di gestire multiple environment in modo efficiente, sicuro e scalabile, mantenendo un workflow centralizzato.
</details>

### Domanda 3
**Perché è importante implementare health checks dopo il deployment?**

A) Per rallentare il processo di deployment
B) Per verificare che l'applicazione funzioni correttamente e permettere rollback automatico
C) È obbligatorio per GitHub Actions
D) Solo per applicazioni web

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

Gli health checks verificano che l'applicazione deployata funzioni correttamente e permettono di implementare rollback automatico in caso di problemi, garantendo alta disponibilità del servizio.
</details>

## 📚 Prossimi Passi

Ora che hai compreso i concetti fondamentali di CI/CD, sei pronto per:

1. **[GitHub Actions Basics](./02-actions-basics.md)** - Sintassi e componenti base
2. **[Workflow Configuration](./03-workflow-configuration.md)** - Configurazioni avanzate
3. **[Marketplace Actions](./04-marketplace-actions.md)** - Azioni predefinite e custom

Continua con la prossima guida per approfondire l'implementazione pratica di GitHub Actions!
