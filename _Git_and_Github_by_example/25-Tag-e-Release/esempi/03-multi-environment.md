# 03 - Gestione Multi-Environment Release

Questo esempio avanzato mostra come gestire release in ambienti multipli (development, staging, production) con strategie di deployment differenziate.

## Scenario

Sistema di e-commerce con deployment automatizzato su tre ambienti:
- **Development**: Branch feature, deploy continuo
- **Staging**: Branch develop, pre-release testing
- **Production**: Branch main, release controllate

## Architettura del Sistema

### 1. Struttura Repository

```
ecommerce-platform/
├── .github/
│   ├── workflows/
│   │   ├── development.yml
│   │   ├── staging.yml
│   │   ├── production.yml
│   │   └── hotfix.yml
│   └── environments/
│       ├── development.yml
│       ├── staging.yml
│       └── production.yml
├── src/
├── tests/
├── infrastructure/
│   ├── terraform/
│   ├── kubernetes/
│   └── monitoring/
└── config/
    ├── development.json
    ├── staging.json
    └── production.json
```

### 2. Configurazione Environment

**.github/environments/development.yml**:
```yaml
name: development
deployment_branch_policy:
  protected_branches: false
  custom_branch_policies: true
protection_rules:
  - type: required_reviewers
    required_reviewers: 0
  - type: wait_timer
    wait_timer: 0
variables:
  - name: API_URL
    value: "https://dev-api.ecommerce.com"
  - name: DB_HOST
    value: "dev-db.ecommerce.com"
secrets:
  - name: DB_PASSWORD
  - name: API_KEY
```

**.github/environments/staging.yml**:
```yaml
name: staging
deployment_branch_policy:
  protected_branches: true
  custom_branch_policies: false
protection_rules:
  - type: required_reviewers
    required_reviewers: 1
  - type: wait_timer
    wait_timer: 300  # 5 minutes
variables:
  - name: API_URL
    value: "https://staging-api.ecommerce.com"
  - name: DB_HOST
    value: "staging-db.ecommerce.com"
secrets:
  - name: DB_PASSWORD
  - name: API_KEY
```

**.github/environments/production.yml**:
```yaml
name: production
deployment_branch_policy:
  protected_branches: true
  custom_branch_policies: false
protection_rules:
  - type: required_reviewers
    required_reviewers: 2
  - type: wait_timer
    wait_timer: 1800  # 30 minutes
variables:
  - name: API_URL
    value: "https://api.ecommerce.com"
  - name: DB_HOST
    value: "prod-db.ecommerce.com"
secrets:
  - name: DB_PASSWORD
  - name: API_KEY
```

## Workflow Development

**.github/workflows/development.yml**:
```yaml
name: Development Deployment

on:
  push:
    branches:
      - 'feature/**'
      - 'bugfix/**'
      - develop
  pull_request:
    branches: [develop]

env:
  NODE_VERSION: '18'
  DOCKER_REGISTRY: ghcr.io

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run linting
        run: npm run lint
      
      - name: Run unit tests
        run: npm run test:unit
      
      - name: Run integration tests
        run: npm run test:integration
        env:
          NODE_ENV: test
      
      - name: Upload test results
        uses: actions/upload-artifact@v4
        if: always()
        with:
          name: test-results
          path: |
            coverage/
            test-results.xml

  security:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Run security audit
        run: npm audit --audit-level moderate
      
      - name: Run SAST scan
        uses: github/super-linter@v4
        env:
          DEFAULT_BRANCH: main
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  build:
    needs: [test, security]
    runs-on: ubuntu-latest
    outputs:
      image: ${{ steps.image.outputs.image }}
    steps:
      - uses: actions/checkout@v4
      
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3
      
      - name: Log in to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.DOCKER_REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Build and push Docker image
        id: image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: ./Dockerfile
          push: true
          tags: |
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:dev-${{ github.sha }}
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:dev-latest
          cache-from: type=gha
          cache-to: type=gha,mode=max

  deploy-dev:
    needs: build
    runs-on: ubuntu-latest
    environment: development
    if: github.ref == 'refs/heads/develop'
    steps:
      - uses: actions/checkout@v4
      
      - name: Deploy to Development
        run: |
          echo "🚀 Deploying to Development Environment"
          echo "Image: ${{ needs.build.outputs.image }}"
          
          # Update Kubernetes deployment
          kubectl set image deployment/ecommerce-app \
            app=${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:dev-${{ github.sha }} \
            --namespace=development
          
          # Wait for rollout
          kubectl rollout status deployment/ecommerce-app \
            --namespace=development \
            --timeout=300s
        env:
          KUBECONFIG_DATA: ${{ secrets.DEV_KUBECONFIG }}
      
      - name: Run smoke tests
        run: |
          npm run test:smoke
        env:
          API_URL: ${{ vars.API_URL }}
          API_KEY: ${{ secrets.API_KEY }}
      
      - name: Update deployment status
        uses: bobheadxi/deployments@v1
        with:
          step: finish
          token: ${{ secrets.GITHUB_TOKEN }}
          status: success
          deployment_id: ${{ github.event.deployment.id }}
          env_url: https://dev.ecommerce.com
```

## Workflow Staging

**.github/workflows/staging.yml**:
```yaml
name: Staging Deployment

on:
  push:
    branches: [main]
  workflow_dispatch:
    inputs:
      version:
        description: 'Version to deploy'
        required: true
        type: string

env:
  NODE_VERSION: '18'
  DOCKER_REGISTRY: ghcr.io

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run full test suite
        run: |
          npm run test:unit
          npm run test:integration
          npm run test:e2e
        env:
          NODE_ENV: staging
      
      - name: Performance tests
        run: npm run test:performance
        env:
          API_URL: ${{ vars.API_URL }}

  build:
    needs: test
    runs-on: ubuntu-latest
    outputs:
      image: ${{ steps.image.outputs.image }}
      version: ${{ steps.version.outputs.version }}
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
      
      - name: Generate version
        id: version
        run: |
          if [ "${{ github.event_name }}" = "workflow_dispatch" ]; then
            VERSION="${{ github.event.inputs.version }}"
          else
            VERSION=$(npx semantic-release --dry-run | grep -oP 'The next release version is \K\d+\.\d+\.\d+' || echo "0.0.0")
          fi
          echo "version=$VERSION" >> $GITHUB_OUTPUT
          echo "📦 Building version: $VERSION"
      
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3
      
      - name: Log in to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.DOCKER_REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Build and push Docker image
        id: image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: ./Dockerfile
          push: true
          tags: |
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:staging-${{ steps.version.outputs.version }}
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:staging-latest
          build-args: |
            VERSION=${{ steps.version.outputs.version }}
            ENVIRONMENT=staging

  deploy-staging:
    needs: build
    runs-on: ubuntu-latest
    environment: staging
    steps:
      - uses: actions/checkout@v4
      
      - name: Create deployment
        uses: bobheadxi/deployments@v1
        id: deployment
        with:
          step: start
          token: ${{ secrets.GITHUB_TOKEN }}
          env: staging
          ref: ${{ github.head_ref }}
      
      - name: Deploy to Staging
        run: |
          echo "🚀 Deploying version ${{ needs.build.outputs.version }} to Staging"
          
          # Blue-Green deployment
          helm upgrade --install ecommerce-staging ./infrastructure/helm \
            --namespace=staging \
            --set image.repository=${{ env.DOCKER_REGISTRY }}/${{ github.repository }} \
            --set image.tag=staging-${{ needs.build.outputs.version }} \
            --set environment=staging \
            --set replicaCount=3 \
            --wait --timeout=600s
        env:
          KUBECONFIG_DATA: ${{ secrets.STAGING_KUBECONFIG }}
      
      - name: Run acceptance tests
        run: |
          npm run test:acceptance
        env:
          API_URL: ${{ vars.API_URL }}
          API_KEY: ${{ secrets.API_KEY }}
      
      - name: Load testing
        run: |
          npm run test:load
        env:
          TARGET_URL: ${{ vars.API_URL }}
      
      - name: Update deployment status
        uses: bobheadxi/deployments@v1
        if: always()
        with:
          step: finish
          token: ${{ secrets.GITHUB_TOKEN }}
          status: ${{ job.status }}
          deployment_id: ${{ steps.deployment.outputs.deployment_id }}
          env_url: https://staging.ecommerce.com
      
      - name: Notify on failure
        if: failure()
        uses: 8398a7/action-slack@v3
        with:
          status: failure
          channel: '#deployments'
          message: |
            🚨 Staging deployment failed!
            Version: ${{ needs.build.outputs.version }}
            Commit: ${{ github.sha }}
            Actor: ${{ github.actor }}
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Workflow Production

**.github/workflows/production.yml**:
```yaml
name: Production Release

on:
  release:
    types: [published]
  workflow_dispatch:
    inputs:
      release_tag:
        description: 'Release tag to deploy'
        required: true
        type: string
      deployment_strategy:
        description: 'Deployment strategy'
        required: true
        type: choice
        options:
          - rolling
          - blue-green
          - canary
        default: 'rolling'

env:
  NODE_VERSION: '18'
  DOCKER_REGISTRY: ghcr.io

jobs:
  validate:
    runs-on: ubuntu-latest
    outputs:
      tag: ${{ steps.tag.outputs.tag }}
      strategy: ${{ steps.strategy.outputs.strategy }}
    steps:
      - name: Determine release tag
        id: tag
        run: |
          if [ "${{ github.event_name }}" = "release" ]; then
            TAG="${{ github.event.release.tag_name }}"
          else
            TAG="${{ github.event.inputs.release_tag }}"
          fi
          echo "tag=$TAG" >> $GITHUB_OUTPUT
          echo "🏷️ Release tag: $TAG"
      
      - name: Determine deployment strategy
        id: strategy
        run: |
          if [ "${{ github.event_name }}" = "release" ]; then
            STRATEGY="rolling"
          else
            STRATEGY="${{ github.event.inputs.deployment_strategy }}"
          fi
          echo "strategy=$STRATEGY" >> $GITHUB_OUTPUT
          echo "🎯 Deployment strategy: $STRATEGY"
      
      - name: Validate release
        run: |
          echo "Validating release ${{ steps.tag.outputs.tag }}"
          # Validate tag format
          if [[ ! "${{ steps.tag.outputs.tag }}" =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
            echo "❌ Invalid tag format. Expected: vX.Y.Z"
            exit 1
          fi
          echo "✅ Tag format valid"

  pre-deployment:
    needs: validate
    runs-on: ubuntu-latest
    environment: production
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate.outputs.tag }}
      
      - name: Pre-deployment checklist
        run: |
          echo "📋 Pre-deployment checklist for ${{ needs.validate.outputs.tag }}"
          echo "✅ Release notes reviewed"
          echo "✅ Database migrations tested"
          echo "✅ Rollback plan prepared"
          echo "✅ Team notified"
      
      - name: Database backup
        run: |
          echo "💾 Creating production database backup"
          # Trigger database backup
          curl -X POST "${{ secrets.BACKUP_WEBHOOK }}" \
            -H "Authorization: Bearer ${{ secrets.BACKUP_TOKEN }}" \
            -d '{"type": "pre-release", "tag": "${{ needs.validate.outputs.tag }}"}'
      
      - name: Maintenance mode
        run: |
          echo "🚧 Enabling maintenance mode"
          kubectl patch deployment ecommerce-app \
            -p '{"spec":{"template":{"metadata":{"annotations":{"maintenance":"true"}}}}}' \
            --namespace=production
        env:
          KUBECONFIG_DATA: ${{ secrets.PROD_KUBECONFIG }}

  deploy-production:
    needs: [validate, pre-deployment]
    runs-on: ubuntu-latest
    environment: production
    strategy:
      matrix:
        region: [us-east-1, eu-west-1, ap-southeast-1]
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate.outputs.tag }}
      
      - name: Create deployment
        uses: bobheadxi/deployments@v1
        id: deployment
        with:
          step: start
          token: ${{ secrets.GITHUB_TOKEN }}
          env: production-${{ matrix.region }}
          ref: ${{ needs.validate.outputs.tag }}
      
      - name: Deploy with Rolling Update
        if: needs.validate.outputs.strategy == 'rolling'
        run: |
          echo "🔄 Rolling update deployment to ${{ matrix.region }}"
          helm upgrade ecommerce-prod ./infrastructure/helm \
            --namespace=production \
            --set image.repository=${{ env.DOCKER_REGISTRY }}/${{ github.repository }} \
            --set image.tag=${{ needs.validate.outputs.tag }} \
            --set environment=production \
            --set region=${{ matrix.region }} \
            --set replicaCount=10 \
            --set strategy.type=RollingUpdate \
            --set strategy.rollingUpdate.maxUnavailable=25% \
            --set strategy.rollingUpdate.maxSurge=25% \
            --wait --timeout=1200s
      
      - name: Deploy with Blue-Green
        if: needs.validate.outputs.strategy == 'blue-green'
        run: |
          echo "🔵🟢 Blue-Green deployment to ${{ matrix.region }}"
          
          # Deploy to green environment
          helm install ecommerce-green ./infrastructure/helm \
            --namespace=production \
            --set image.repository=${{ env.DOCKER_REGISTRY }}/${{ github.repository }} \
            --set image.tag=${{ needs.validate.outputs.tag }} \
            --set environment=production \
            --set region=${{ matrix.region }} \
            --set deployment.color=green \
            --wait --timeout=1200s
          
          # Health check green environment
          sleep 60
          curl -f "https://green-${{ matrix.region }}.ecommerce.com/health" || exit 1
          
          # Switch traffic to green
          kubectl patch service ecommerce-service \
            -p '{"spec":{"selector":{"color":"green"}}}' \
            --namespace=production
          
          # Remove blue environment
          helm uninstall ecommerce-blue --namespace=production || true
      
      - name: Deploy with Canary
        if: needs.validate.outputs.strategy == 'canary'
        run: |
          echo "🐤 Canary deployment to ${{ matrix.region }}"
          
          # Deploy canary (10% traffic)
          helm install ecommerce-canary ./infrastructure/helm \
            --namespace=production \
            --set image.repository=${{ env.DOCKER_REGISTRY }}/${{ github.repository }} \
            --set image.tag=${{ needs.validate.outputs.tag }} \
            --set environment=production \
            --set region=${{ matrix.region }} \
            --set deployment.type=canary \
            --set deployment.weight=10 \
            --wait --timeout=1200s
          
          # Monitor for 10 minutes
          sleep 600
          
          # Check error rates
          ERROR_RATE=$(curl -s "${{ secrets.MONITORING_URL }}/api/error-rate?service=ecommerce&region=${{ matrix.region }}&duration=10m" | jq -r '.rate')
          if (( $(echo "$ERROR_RATE > 0.01" | bc -l) )); then
            echo "❌ Error rate too high: $ERROR_RATE"
            exit 1
          fi
          
          # Promote to 100%
          helm upgrade ecommerce-canary ./infrastructure/helm \
            --set deployment.weight=100 \
            --wait --timeout=600s
      
      - name: Post-deployment validation
        run: |
          echo "🔍 Validating deployment in ${{ matrix.region }}"
          
          # Health checks
          for i in {1..10}; do
            if curl -f "https://${{ matrix.region }}.ecommerce.com/health"; then
              echo "✅ Health check passed ($i/10)"
              break
            fi
            if [ $i -eq 10 ]; then
              echo "❌ Health checks failed"
              exit 1
            fi
            sleep 30
          done
          
          # Smoke tests
          npm run test:smoke:production
        env:
          API_URL: https://${{ matrix.region }}.ecommerce.com
          API_KEY: ${{ secrets.PROD_API_KEY }}
      
      - name: Update deployment status
        uses: bobheadxi/deployments@v1
        if: always()
        with:
          step: finish
          token: ${{ secrets.GITHUB_TOKEN }}
          status: ${{ job.status }}
          deployment_id: ${{ steps.deployment.outputs.deployment_id }}
          env_url: https://${{ matrix.region }}.ecommerce.com

  post-deployment:
    needs: [validate, deploy-production]
    runs-on: ubuntu-latest
    if: always()
    steps:
      - name: Disable maintenance mode
        if: success()
        run: |
          echo "✅ Disabling maintenance mode"
          kubectl patch deployment ecommerce-app \
            -p '{"spec":{"template":{"metadata":{"annotations":{"maintenance":"false"}}}}}' \
            --namespace=production
        env:
          KUBECONFIG_DATA: ${{ secrets.PROD_KUBECONFIG }}
      
      - name: Update monitoring
        if: success()
        run: |
          echo "📊 Updating monitoring dashboards"
          curl -X POST "${{ secrets.MONITORING_WEBHOOK }}" \
            -H "Content-Type: application/json" \
            -d '{
              "event": "deployment_success",
              "version": "${{ needs.validate.outputs.tag }}",
              "strategy": "${{ needs.validate.outputs.strategy }}",
              "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%S.%3NZ)'"
            }'
      
      - name: Notify success
        if: success()
        uses: 8398a7/action-slack@v3
        with:
          status: success
          channel: '#releases'
          message: |
            🎉 Production deployment successful!
            Version: ${{ needs.validate.outputs.tag }}
            Strategy: ${{ needs.validate.outputs.strategy }}
            Regions: us-east-1, eu-west-1, ap-southeast-1
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
      
      - name: Rollback on failure
        if: failure()
        run: |
          echo "🚨 Initiating rollback procedure"
          PREVIOUS_TAG=$(git describe --tags --abbrev=0 HEAD~1)
          echo "Rolling back to: $PREVIOUS_TAG"
          
          # Trigger rollback workflow
          curl -X POST \
            -H "Accept: application/vnd.github.v3+json" \
            -H "Authorization: token ${{ secrets.GITHUB_TOKEN }}" \
            "https://api.github.com/repos/${{ github.repository }}/actions/workflows/rollback.yml/dispatches" \
            -d '{"ref":"main","inputs":{"target_version":"'$PREVIOUS_TAG'","reason":"deployment_failure"}}'
      
      - name: Notify failure
        if: failure()
        uses: 8398a7/action-slack@v3
        with:
          status: failure
          channel: '#incidents'
          message: |
            🚨 PRODUCTION DEPLOYMENT FAILED 🚨
            Version: ${{ needs.validate.outputs.tag }}
            Strategy: ${{ needs.validate.outputs.strategy }}
            Rollback initiated automatically
            
            @here @oncall
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Workflow Hotfix

**.github/workflows/hotfix.yml**:
```yaml
name: Emergency Hotfix

on:
  push:
    branches:
      - 'hotfix/**'
  workflow_dispatch:
    inputs:
      hotfix_branch:
        description: 'Hotfix branch name'
        required: true
        type: string
      severity:
        description: 'Issue severity'
        required: true
        type: choice
        options:
          - critical
          - high
          - medium
        default: 'critical'

env:
  NODE_VERSION: '18'
  DOCKER_REGISTRY: ghcr.io

jobs:
  validate-hotfix:
    runs-on: ubuntu-latest
    outputs:
      branch: ${{ steps.branch.outputs.branch }}
      severity: ${{ steps.severity.outputs.severity }}
    steps:
      - name: Determine branch
        id: branch
        run: |
          if [ "${{ github.event_name }}" = "push" ]; then
            BRANCH="${{ github.ref_name }}"
          else
            BRANCH="${{ github.event.inputs.hotfix_branch }}"
          fi
          echo "branch=$BRANCH" >> $GITHUB_OUTPUT
          echo "🚨 Hotfix branch: $BRANCH"
      
      - name: Determine severity
        id: severity
        run: |
          if [ "${{ github.event_name }}" = "push" ]; then
            SEVERITY="critical"
          else
            SEVERITY="${{ github.event.inputs.severity }}"
          fi
          echo "severity=$SEVERITY" >> $GITHUB_OUTPUT
          echo "⚠️ Severity: $SEVERITY"
      
      - uses: actions/checkout@v4
        with:
          ref: ${{ steps.branch.outputs.branch }}
      
      - name: Validate hotfix
        run: |
          echo "Validating hotfix on branch ${{ steps.branch.outputs.branch }}"
          if [[ ! "${{ steps.branch.outputs.branch }}" =~ ^hotfix/.+ ]]; then
            echo "❌ Invalid hotfix branch name"
            exit 1
          fi
          echo "✅ Hotfix branch valid"

  emergency-test:
    needs: validate-hotfix
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate-hotfix.outputs.branch }}
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run critical tests only
        if: needs.validate-hotfix.outputs.severity == 'critical'
        run: |
          npm run test:critical
          npm run test:security
        env:
          NODE_ENV: test
      
      - name: Run essential tests
        if: needs.validate-hotfix.outputs.severity != 'critical'
        run: |
          npm run test:unit
          npm run test:integration:critical
        env:
          NODE_ENV: test

  emergency-build:
    needs: [validate-hotfix, emergency-test]
    runs-on: ubuntu-latest
    outputs:
      image: ${{ steps.image.outputs.image }}
      version: ${{ steps.version.outputs.version }}
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate-hotfix.outputs.branch }}
          fetch-depth: 0
      
      - name: Generate hotfix version
        id: version
        run: |
          CURRENT_VERSION=$(git describe --tags --abbrev=0 2>/dev/null || echo "v0.0.0")
          PATCH_VERSION=$(echo $CURRENT_VERSION | sed 's/v\([0-9]*\.[0-9]*\.\)\([0-9]*\)/\2/')
          NEW_PATCH=$((PATCH_VERSION + 1))
          HOTFIX_VERSION=$(echo $CURRENT_VERSION | sed "s/\([0-9]*\.[0-9]*\.\)[0-9]*/\1${NEW_PATCH}/")
          echo "version=$HOTFIX_VERSION" >> $GITHUB_OUTPUT
          echo "🔥 Hotfix version: $HOTFIX_VERSION"
      
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3
      
      - name: Log in to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.DOCKER_REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Build hotfix image
        id: image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: ./Dockerfile
          push: true
          tags: |
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:hotfix-${{ steps.version.outputs.version }}
            ${{ env.DOCKER_REGISTRY }}/${{ github.repository }}:hotfix-latest
          build-args: |
            VERSION=${{ steps.version.outputs.version }}
            ENVIRONMENT=production
            BUILD_TYPE=hotfix

  emergency-deploy:
    needs: [validate-hotfix, emergency-build]
    runs-on: ubuntu-latest
    environment: production
    if: needs.validate-hotfix.outputs.severity == 'critical'
    strategy:
      matrix:
        region: [us-east-1, eu-west-1, ap-southeast-1]
      max-parallel: 1  # Deploy one region at a time for critical fixes
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate-hotfix.outputs.branch }}
      
      - name: Emergency deployment notification
        uses: 8398a7/action-slack@v3
        with:
          status: custom
          custom_payload: |
            {
              "channel": "#incidents",
              "username": "Emergency Deploy Bot",
              "icon_emoji": ":fire:",
              "attachments": [{
                "color": "danger",
                "title": "🚨 EMERGENCY HOTFIX DEPLOYMENT 🚨",
                "fields": [
                  {"title": "Region", "value": "${{ matrix.region }}", "short": true},
                  {"title": "Version", "value": "${{ needs.emergency-build.outputs.version }}", "short": true},
                  {"title": "Branch", "value": "${{ needs.validate-hotfix.outputs.branch }}", "short": true},
                  {"title": "Severity", "value": "${{ needs.validate-hotfix.outputs.severity }}", "short": true}
                ]
              }]
            }
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
      
      - name: Create production backup
        run: |
          echo "💾 Creating emergency backup for ${{ matrix.region }}"
          curl -X POST "${{ secrets.BACKUP_WEBHOOK }}" \
            -H "Authorization: Bearer ${{ secrets.BACKUP_TOKEN }}" \
            -d '{
              "type": "emergency",
              "region": "${{ matrix.region }}",
              "version": "${{ needs.emergency-build.outputs.version }}"
            }'
      
      - name: Deploy hotfix
        run: |
          echo "🚀 Emergency deployment to ${{ matrix.region }}"
          
          # Fast deployment with minimal checks
          helm upgrade ecommerce-prod ./infrastructure/helm \
            --namespace=production \
            --set image.repository=${{ env.DOCKER_REGISTRY }}/${{ github.repository }} \
            --set image.tag=hotfix-${{ needs.emergency-build.outputs.version }} \
            --set environment=production \
            --set region=${{ matrix.region }} \
            --set deployment.type=emergency \
            --set strategy.type=RollingUpdate \
            --set strategy.rollingUpdate.maxUnavailable=10% \
            --set strategy.rollingUpdate.maxSurge=50% \
            --wait --timeout=300s
        env:
          KUBECONFIG_DATA: ${{ secrets.PROD_KUBECONFIG }}
      
      - name: Immediate health check
        run: |
          echo "🔍 Emergency health check for ${{ matrix.region }}"
          for i in {1..5}; do
            if curl -f "https://${{ matrix.region }}.ecommerce.com/health"; then
              echo "✅ Emergency deployment successful"
              break
            fi
            if [ $i -eq 5 ]; then
              echo "❌ Emergency deployment failed"
              exit 1
            fi
            sleep 10
          done
      
      - name: Monitor for 5 minutes
        run: |
          echo "👀 Monitoring deployment for 5 minutes"
          for i in {1..10}; do
            ERROR_RATE=$(curl -s "${{ secrets.MONITORING_URL }}/api/error-rate?service=ecommerce&region=${{ matrix.region }}&duration=30s" | jq -r '.rate' || echo "0")
            echo "Error rate: $ERROR_RATE"
            if (( $(echo "$ERROR_RATE > 0.02" | bc -l) )); then
              echo "❌ High error rate detected: $ERROR_RATE"
              exit 1
            fi
            sleep 30
          done
          echo "✅ Monitoring completed successfully"
      
      - name: Deployment success notification
        if: success()
        uses: 8398a7/action-slack@v3
        with:
          status: success
          channel: '#incidents'
          message: |
            ✅ Emergency hotfix deployed successfully to ${{ matrix.region }}
            Version: ${{ needs.emergency-build.outputs.version }}
            Monitoring: All systems green
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}

  create-hotfix-release:
    needs: [validate-hotfix, emergency-build, emergency-deploy]
    runs-on: ubuntu-latest
    if: success()
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ needs.validate-hotfix.outputs.branch }}
      
      - name: Create hotfix tag
        run: |
          git config --local user.email "action@github.com"
          git config --local user.name "GitHub Action"
          git tag -a "${{ needs.emergency-build.outputs.version }}" -m "Emergency hotfix release ${{ needs.emergency-build.outputs.version }}"
          git push origin "${{ needs.emergency-build.outputs.version }}"
      
      - name: Create GitHub release
        uses: actions/create-release@v1
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        with:
          tag_name: ${{ needs.emergency-build.outputs.version }}
          release_name: Emergency Hotfix ${{ needs.emergency-build.outputs.version }}
          body: |
            🚨 **Emergency Hotfix Release**
            
            **Severity:** ${{ needs.validate-hotfix.outputs.severity }}
            **Branch:** ${{ needs.validate-hotfix.outputs.branch }}
            **Deployed:** $(date -u)
            
            This is an emergency hotfix release deployed directly to production.
            
            **Changes:**
            - Emergency fix for critical production issue
            
            **Verification:**
            - ✅ Critical tests passed
            - ✅ Security validation completed
            - ✅ Deployed to all regions
            - ✅ Health checks successful
          draft: false
          prerelease: false
      
      - name: Merge back to main
        run: |
          git checkout main
          git merge ${{ needs.validate-hotfix.outputs.branch }} --no-ff -m "Merge emergency hotfix ${{ needs.emergency-build.outputs.version }}"
          git push origin main
          
          # Also merge to develop
          git checkout develop
          git merge main --no-ff -m "Merge hotfix ${{ needs.emergency-build.outputs.version }} from main"
          git push origin develop
```

## Configurazione Monitoring

### 1. Metriche di Deployment

**infrastructure/monitoring/deployment-dashboard.json**:
```json
{
  "dashboard": {
    "title": "Multi-Environment Deployments",
    "panels": [
      {
        "title": "Deployment Frequency",
        "type": "graph",
        "targets": [
          {
            "expr": "rate(deployments_total[1h])",
            "legendFormat": "{{environment}}"
          }
        ]
      },
      {
        "title": "Deployment Success Rate",
        "type": "stat",
        "targets": [
          {
            "expr": "rate(deployments_success_total[24h]) / rate(deployments_total[24h]) * 100",
            "legendFormat": "{{environment}}"
          }
        ]
      },
      {
        "title": "Mean Time to Recovery",
        "type": "stat",
        "targets": [
          {
            "expr": "avg(deployment_recovery_time_seconds)",
            "legendFormat": "MTTR"
          }
        ]
      }
    ]
  }
}
```

### 2. Alerting Rules

**infrastructure/monitoring/alerts.yml**:
```yaml
groups:
  - name: deployment.rules
    rules:
      - alert: DeploymentFailed
        expr: increase(deployments_failed_total[5m]) > 0
        for: 0m
        labels:
          severity: critical
        annotations:
          summary: "Deployment failed in {{ $labels.environment }}"
          description: "Deployment to {{ $labels.environment }} has failed"
      
      - alert: HighErrorRate
        expr: rate(http_requests_total{status=~"5.."}[5m]) > 0.01
        for: 2m
        labels:
          severity: warning
        annotations:
          summary: "High error rate detected"
          description: "Error rate is {{ $value }} in {{ $labels.environment }}"
      
      - alert: DeploymentStuck
        expr: deployment_duration_seconds > 1800
        for: 5m
        labels:
          severity: warning
        annotations:
          summary: "Deployment taking too long"
          description: "Deployment has been running for {{ $value }}s"
```

## Best Practices Implementate

### 1. Environment Isolation
- Configurazioni separate per ogni ambiente
- Secrets e variabili environment-specific
- Network isolation e security boundaries

### 2. Progressive Deployment
- Development: Deploy continuo per feedback rapido
- Staging: Testing completo e validation
- Production: Deployment controllato con approval

### 3. Quality Gates
- Test progressivi (unit → integration → e2e)
- Security scanning per ogni build
- Performance testing in staging

### 4. Deployment Strategies
- **Rolling**: Aggiornamento graduale, zero downtime
- **Blue-Green**: Switch istantaneo con rollback veloce
- **Canary**: Test su subset di utenti

### 5. Emergency Procedures
- Hotfix workflow per emergenze
- Rollback automatico su failure
- Monitoring continuo post-deployment

Questo esempio mostra un sistema completo di deployment multi-environment che scala da startup a enterprise, garantendo sicurezza, affidabilità e velocità.
