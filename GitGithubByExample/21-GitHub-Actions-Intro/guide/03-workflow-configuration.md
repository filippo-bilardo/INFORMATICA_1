# 03 - Workflow Configuration

## 📖 Spiegazione Concettuale

**Workflow Configuration** rappresenta l'arte di orchestrare automazioni complesse attraverso configurazioni avanzate. Questa guida esplora tecniche sofisticate per creare pipeline robuste, scalabili e maintainabili.

### Architettura Workflow Avanzata

```yaml
# .github/workflows/advanced-pipeline.yml
name: Advanced Production Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  schedule:
    - cron: '0 2 * * 1'        # Weekly maintenance
  workflow_dispatch:
    inputs:
      environment:
        type: choice
        options: [staging, production]
        default: staging
      force_deploy:
        type: boolean
        default: false

concurrency:                   # Controllo concorrenza
  group: ${{ github.workflow }}-${{ github.ref }}
  cancel-in-progress: true

permissions:                   # Permessi specifici
  contents: read
  packages: write
  deployments: write
  pull-requests: write

env:
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}
```

## 🎯 Environment Management

### Environment Protection Rules

```yaml
jobs:
  deploy-staging:
    runs-on: ubuntu-latest
    environment:
      name: staging
      url: https://staging.myapp.com
    
    steps:
    - name: Deploy to Staging
      run: echo "Deploying to staging..."

  deploy-production:
    needs: deploy-staging
    runs-on: ubuntu-latest
    environment:
      name: production
      url: https://myapp.com
    if: github.ref == 'refs/heads/main'
    
    steps:
    - name: Deploy to Production
      run: echo "Deploying to production..."
```

### Dynamic Environment Selection

```yaml
jobs:
  deploy:
    runs-on: ubuntu-latest
    environment: 
      name: ${{ github.event_name == 'push' && github.ref == 'refs/heads/main' && 'production' || 'staging' }}
      url: ${{ steps.deploy.outputs.url }}
    
    steps:
    - name: Set environment variables
      run: |
        if [ "${{ github.environment }}" == "production" ]; then
          echo "API_URL=https://api.myapp.com" >> $GITHUB_ENV
          echo "DB_HOST=prod-db.myapp.com" >> $GITHUB_ENV
          echo "REPLICAS=3" >> $GITHUB_ENV
        else
          echo "API_URL=https://staging-api.myapp.com" >> $GITHUB_ENV
          echo "DB_HOST=staging-db.myapp.com" >> $GITHUB_ENV
          echo "REPLICAS=1" >> $GITHUB_ENV
        fi
    
    - name: Deploy application
      id: deploy
      run: |
        echo "Deploying to ${{ github.environment }}"
        echo "API_URL: $API_URL"
        echo "Replicas: $REPLICAS"
        # Deployment logic
        echo "url=https://${{ github.environment }}.myapp.com" >> $GITHUB_OUTPUT
```

## 🔄 Reusable Workflows

### Workflow Template

```yaml
# .github/workflows/reusable-deploy.yml
name: Reusable Deploy Workflow

on:
  workflow_call:
    inputs:
      environment:
        required: true
        type: string
      version:
        required: false
        type: string
        default: 'latest'
      dry_run:
        required: false
        type: boolean
        default: false
    secrets:
      deployment_key:
        required: true
      database_url:
        required: true
    outputs:
      deployment_url:
        description: "The URL of the deployed application"
        value: ${{ jobs.deploy.outputs.url }}

jobs:
  deploy:
    runs-on: ubuntu-latest
    environment: ${{ inputs.environment }}
    outputs:
      url: ${{ steps.deploy.outputs.url }}
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup deployment
      env:
        DEPLOYMENT_KEY: ${{ secrets.deployment_key }}
        DATABASE_URL: ${{ secrets.database_url }}
      run: |
        echo "Setting up deployment for ${{ inputs.environment }}"
        echo "Version: ${{ inputs.version }}"
        echo "Dry run: ${{ inputs.dry_run }}"
    
    - name: Deploy application
      id: deploy
      run: |
        if [ "${{ inputs.dry_run }}" == "true" ]; then
          echo "DRY RUN: Would deploy to ${{ inputs.environment }}"
          echo "url=https://dry-run.example.com" >> $GITHUB_OUTPUT
        else
          echo "Deploying to ${{ inputs.environment }}"
          echo "url=https://${{ inputs.environment }}.myapp.com" >> $GITHUB_OUTPUT
        fi
```

### Using Reusable Workflow

```yaml
# .github/workflows/main-pipeline.yml
name: Main Pipeline

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Run tests
      run: npm test

  deploy-staging:
    needs: test
    uses: ./.github/workflows/reusable-deploy.yml
    with:
      environment: staging
      version: ${{ github.sha }}
      dry_run: false
    secrets:
      deployment_key: ${{ secrets.STAGING_DEPLOY_KEY }}
      database_url: ${{ secrets.STAGING_DB_URL }}

  deploy-production:
    needs: deploy-staging
    if: github.ref == 'refs/heads/main'
    uses: ./.github/workflows/reusable-deploy.yml
    with:
      environment: production
      version: ${{ github.sha }}
      dry_run: false
    secrets:
      deployment_key: ${{ secrets.PROD_DEPLOY_KEY }}
      database_url: ${{ secrets.PROD_DB_URL }}
```

## 🛡️ Security Best Practices

### Secure Secrets Management

```yaml
jobs:
  secure-deployment:
    runs-on: ubuntu-latest
    environment: production
    
    steps:
    - name: Configure AWS Credentials
      uses: aws-actions/configure-aws-credentials@v2
      with:
        role-to-assume: ${{ secrets.AWS_ROLE_ARN }}
        role-session-name: GitHubActions
        aws-region: us-east-1
    
    - name: Get secrets from AWS Secrets Manager
      id: secrets
      run: |
        DB_PASSWORD=$(aws secretsmanager get-secret-value \
          --secret-id prod/database/password \
          --query SecretString --output text)
        echo "::add-mask::$DB_PASSWORD"
        echo "db_password=$DB_PASSWORD" >> $GITHUB_OUTPUT
    
    - name: Deploy with retrieved secrets
      env:
        DATABASE_PASSWORD: ${{ steps.secrets.outputs.db_password }}
      run: |
        echo "Deploying with database password: ${DATABASE_PASSWORD:0:3}***"
        # Deployment logic
```

### OIDC Authentication

```yaml
jobs:
  deploy-with-oidc:
    runs-on: ubuntu-latest
    permissions:
      id-token: write
      contents: read
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Configure AWS credentials with OIDC
      uses: aws-actions/configure-aws-credentials@v2
      with:
        role-to-assume: arn:aws:iam::123456789012:role/GitHubActionsRole
        role-session-name: GitHubActions-${{ github.run_id }}
        aws-region: us-east-1
    
    - name: Deploy to AWS
      run: |
        aws sts get-caller-identity
        aws s3 sync ./dist s3://my-bucket/
```

### Dependency Vulnerability Scanning

```yaml
jobs:
  security-scan:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Run npm audit
      run: |
        npm audit --audit-level high
        npm audit fix --dry-run
    
    - name: Run Snyk security scan
      uses: snyk/actions/node@master
      env:
        SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
      with:
        args: --severity-threshold=high
    
    - name: Upload Snyk report
      uses: github/codeql-action/upload-sarif@v2
      if: always()
      with:
        sarif_file: snyk.sarif
```

## 📊 Advanced Monitoring

### Performance Monitoring

```yaml
jobs:
  performance-test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: |
        START_TIME=$(date +%s)
        npm run build
        END_TIME=$(date +%s)
        BUILD_TIME=$((END_TIME - START_TIME))
        echo "BUILD_TIME=$BUILD_TIME" >> $GITHUB_ENV
        echo "Build completed in ${BUILD_TIME}s"
    
    - name: Bundle size analysis
      run: |
        BUNDLE_SIZE=$(du -b dist/main.js | cut -f1)
        BUNDLE_SIZE_KB=$((BUNDLE_SIZE / 1024))
        echo "BUNDLE_SIZE_KB=$BUNDLE_SIZE_KB" >> $GITHUB_ENV
        echo "Bundle size: ${BUNDLE_SIZE_KB}KB"
    
    - name: Performance regression check
      run: |
        if [ $BUILD_TIME -gt 300 ]; then
          echo "⚠️ Build time regression: ${BUILD_TIME}s (threshold: 300s)"
          exit 1
        fi
        
        if [ $BUNDLE_SIZE_KB -gt 500 ]; then
          echo "⚠️ Bundle size regression: ${BUNDLE_SIZE_KB}KB (threshold: 500KB)"
          exit 1
        fi
        
        echo "✅ Performance checks passed"
    
    - name: Report metrics
      if: always()
      run: |
        curl -X POST https://metrics.myapp.com/github-actions \
          -H "Content-Type: application/json" \
          -H "Authorization: Bearer ${{ secrets.METRICS_TOKEN }}" \
          -d '{
            "workflow": "${{ github.workflow }}",
            "commit": "${{ github.sha }}",
            "branch": "${{ github.ref_name }}",
            "build_time": '$BUILD_TIME',
            "bundle_size_kb": '$BUNDLE_SIZE_KB',
            "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%SZ)'"
          }'
```

### Health Check Integration

```yaml
jobs:
  deploy-with-health-check:
    runs-on: ubuntu-latest
    
    steps:
    - name: Deploy application
      run: |
        echo "Deploying application..."
        # Deployment logic
    
    - name: Wait for deployment
      run: sleep 30
    
    - name: Health check with retry
      run: |
        for i in {1..10}; do
          echo "Health check attempt $i..."
          
          HEALTH_RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" \
            https://myapp.com/health || echo "000")
          
          if [ "$HEALTH_RESPONSE" == "200" ]; then
            echo "✅ Health check passed"
            break
          elif [ $i -eq 10 ]; then
            echo "❌ Health check failed after 10 attempts"
            exit 1
          else
            echo "Health check failed (HTTP $HEALTH_RESPONSE), retrying in 30s..."
            sleep 30
          fi
        done
    
    - name: Smoke tests
      run: |
        # API endpoint tests
        curl -f https://myapp.com/api/version
        curl -f https://myapp.com/api/health
        
        # Performance test
        RESPONSE_TIME=$(curl -o /dev/null -s -w "%{time_total}" https://myapp.com/)
        echo "Response time: ${RESPONSE_TIME}s"
        
        if (( $(echo "$RESPONSE_TIME > 2.0" | bc -l) )); then
          echo "❌ Response time too slow: ${RESPONSE_TIME}s"
          exit 1
        fi
    
    - name: Rollback on failure
      if: failure()
      run: |
        echo "🔄 Rolling back deployment..."
        # Rollback logic
```

## 🎨 Advanced Workflow Patterns

### Approval Workflow

```yaml
name: Production Deployment with Approval

on:
  push:
    branches: [main]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    outputs:
      build-success: ${{ steps.test.outputs.success }}
    
    steps:
    - uses: actions/checkout@v4
    - name: Build and test
      id: test
      run: |
        npm ci
        npm test
        echo "success=true" >> $GITHUB_OUTPUT

  request-approval:
    needs: build-and-test
    runs-on: ubuntu-latest
    if: needs.build-and-test.outputs.build-success == 'true'
    environment: 
      name: production-approval
    
    steps:
    - name: Request deployment approval
      run: echo "Deployment approved by ${{ github.actor }}"

  deploy-production:
    needs: [build-and-test, request-approval]
    runs-on: ubuntu-latest
    environment: production
    
    steps:
    - name: Deploy to production
      run: |
        echo "Deploying to production..."
        echo "Approved by: ${{ github.actor }}"
        echo "Build SHA: ${{ github.sha }}"
```

### Feature Flag Integration

```yaml
jobs:
  deploy-with-feature-flags:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Check feature flags
      id: feature-flags
      run: |
        # Get feature flags from external service
        FLAGS=$(curl -s -H "Authorization: Bearer ${{ secrets.FEATURE_FLAG_TOKEN }}" \
          https://api.featureflags.com/v1/flags?environment=production)
        
        DEPLOY_NEW_UI=$(echo $FLAGS | jq -r '.deploy_new_ui')
        USE_NEW_API=$(echo $FLAGS | jq -r '.use_new_api')
        
        echo "deploy_new_ui=$DEPLOY_NEW_UI" >> $GITHUB_OUTPUT
        echo "use_new_api=$USE_NEW_API" >> $GITHUB_OUTPUT
    
    - name: Deploy with feature flags
      env:
        DEPLOY_NEW_UI: ${{ steps.feature-flags.outputs.deploy_new_ui }}
        USE_NEW_API: ${{ steps.feature-flags.outputs.use_new_api }}
      run: |
        echo "Deploying with feature flags:"
        echo "New UI: $DEPLOY_NEW_UI"
        echo "New API: $USE_NEW_API"
        
        # Conditional deployment based on flags
        if [ "$DEPLOY_NEW_UI" == "true" ]; then
          echo "Deploying new UI components..."
        fi
        
        if [ "$USE_NEW_API" == "true" ]; then
          echo "Configuring new API endpoints..."
        fi
```

### Multi-Region Deployment

```yaml
jobs:
  deploy-multi-region:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        region: [us-east-1, eu-west-1, ap-southeast-1]
        include:
          - region: us-east-1
            env_name: prod-us
            primary: true
          - region: eu-west-1
            env_name: prod-eu
            primary: false
          - region: ap-southeast-1
            env_name: prod-asia
            primary: false
    
    environment: ${{ matrix.env_name }}
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Configure AWS credentials
      uses: aws-actions/configure-aws-credentials@v2
      with:
        aws-region: ${{ matrix.region }}
        role-to-assume: ${{ secrets.AWS_ROLE_ARN }}
    
    - name: Deploy to region
      run: |
        echo "Deploying to ${{ matrix.region }}"
        echo "Environment: ${{ matrix.env_name }}"
        echo "Primary region: ${{ matrix.primary }}"
        
        # Region-specific deployment logic
        if [ "${{ matrix.primary }}" == "true" ]; then
          echo "Deploying as primary region with write capabilities"
        else
          echo "Deploying as secondary region with read-only capabilities"
        fi
    
    - name: Health check
      run: |
        sleep 30
        HEALTH_URL="https://${{ matrix.env_name }}.myapp.com/health"
        curl -f $HEALTH_URL
        echo "✅ Health check passed for ${{ matrix.region }}"
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è il vantaggio principale dei reusable workflows?**

A) Sono più veloci da eseguire
B) Permettono di ridurre duplicazione e centralizzare logica comune
C) Usano meno risorse
D) Sono obbligatori per la produzione

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

I reusable workflows permettono di ridurre la duplicazione di codice e centralizzare logica comune, migliorando la manutenibilità e la consistenza tra progetti.
</details>

### Domanda 2
**Quando è appropriato usare OIDC invece dei secrets tradizionali?**

A) Solo per applicazioni web
B) Per autenticazione temporanea e sicura con servizi cloud
C) Mai, i secrets sono sempre migliori
D) Solo per deployment in produzione

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

OIDC fornisce autenticazione temporanea e sicura con servizi cloud senza dover memorizzare credenziali a lungo termine, riducendo il rischio di compromissione.
</details>

### Domanda 3
**Qual è la strategia migliore per deployment multi-regione?**

A) Un workflow separato per ogni regione
B) Matrix strategy con configurazioni specifiche per regione
C) Deploy sequenziale manuale
D) Usare solo una regione

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

Matrix strategy con configurazioni specifiche per regione permette deployment parallelo, configurazione centralizzata e gestione efficiente di multiple regioni.
</details>

## 📚 Prossimi Passi

Ora che hai padroneggiato le configurazioni avanzate, sei pronto per:

1. **[Marketplace Actions](./04-marketplace-actions.md)** - Azioni predefinite e personalizzate
2. **[Esempi Pratici](../esempi/01-first-workflow.md)** - Implementazioni complete
3. **[Esercizi](../esercizi/01-ci-setup.md)** - Pratica hands-on

Continua con la prossima guida per esplorare il ricco ecosistema di GitHub Actions!
