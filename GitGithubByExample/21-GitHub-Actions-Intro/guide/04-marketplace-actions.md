# 04 - Marketplace Actions

## 📖 Spiegazione Concettuale

**GitHub Actions Marketplace** è un ecosistema ricco di azioni predefinite che accelerano lo sviluppo di workflow. Questa guida esplora come sfruttare, personalizzare e creare azioni per massimizzare l'efficienza delle pipeline CI/CD.

### Anatomia di un'Azione

```yaml
# Utilizzo di un'azione dal marketplace
- name: Setup Node.js
  uses: actions/setup-node@v4      # azione@versione
  with:                            # parametri di input
    node-version: '18'
    cache: 'npm'
    registry-url: 'https://npm.pkg.github.com'
    scope: '@myorg'
  env:                             # variabili d'ambiente
    NODE_AUTH_TOKEN: ${{ secrets.NPM_TOKEN }}
```

### Versioning delle Azioni

```yaml
# Diverse strategie di versioning
uses: actions/checkout@v4           # Versione major (consigliato)
uses: actions/checkout@v4.1.1       # Versione specifica
uses: actions/checkout@main         # Branch (non consigliato per prod)
uses: actions/checkout@a1b2c3d      # Commit SHA (massima sicurezza)
```

## 🏪 Azioni Marketplace Essenziali

### Setup e Environment

```yaml
jobs:
  multi-language-setup:
    runs-on: ubuntu-latest
    
    steps:
    # Node.js setup
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    # Python setup
    - name: Setup Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.11'
        cache: 'pip'
    
    # Java setup
    - name: Setup Java
      uses: actions/setup-java@v3
      with:
        distribution: 'temurin'
        java-version: '17'
        cache: 'maven'
    
    # Docker setup
    - name: Setup Docker Buildx
      uses: docker/setup-buildx-action@v3
      with:
        platforms: linux/amd64,linux/arm64
    
    # AWS CLI setup
    - name: Configure AWS CLI
      uses: aws-actions/configure-aws-credentials@v2
      with:
        aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
        aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
        aws-region: us-east-1
```

### Code Quality e Testing

```yaml
jobs:
  quality-checks:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # ESLint con auto-fix
    - name: Run ESLint
      uses: github/super-linter@v5
      env:
        DEFAULT_BRANCH: main
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        VALIDATE_JAVASCRIPT_ES: true
        VALIDATE_TYPESCRIPT_ES: true
        FIX_ANSIBLE: true
    
    # SonarCloud analysis
    - name: SonarCloud Scan
      uses: SonarSource/sonarcloud-github-action@master
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        SONAR_TOKEN: ${{ secrets.SONAR_TOKEN }}
    
    # CodeCov coverage
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        files: ./coverage/lcov.info
        flags: unittests
        name: codecov-umbrella
        fail_ci_if_error: true
    
    # Snyk security scan
    - name: Run Snyk to check for vulnerabilities
      uses: snyk/actions/node@master
      env:
        SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
      with:
        args: --severity-threshold=high
```

### Build e Package

```yaml
jobs:
  build-and-package:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # Docker multi-platform build
    - name: Build and push Docker image
      uses: docker/build-push-action@v5
      with:
        context: .
        platforms: linux/amd64,linux/arm64
        push: true
        tags: |
          ghcr.io/${{ github.repository }}:latest
          ghcr.io/${{ github.repository }}:${{ github.sha }}
        cache-from: type=gha
        cache-to: type=gha,mode=max
    
    # NPM package publishing
    - name: Publish to NPM
      uses: JS-DevTools/npm-publish@v3
      with:
        token: ${{ secrets.NPM_TOKEN }}
        access: public
        check-version: true
        greater-version-only: true
    
    # GitHub Release creation
    - name: Create Release
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        tag_name: v${{ github.run_number }}
        release_name: Release v${{ github.run_number }}
        body: |
          Auto-generated release from commit ${{ github.sha }}
          
          Changes in this release:
          ${{ github.event.head_commit.message }}
        draft: false
        prerelease: false
```

### Deployment Actions

```yaml
jobs:
  deploy-to-cloud:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # Deploy to Vercel
    - name: Deploy to Vercel
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-org-id: ${{ secrets.ORG_ID }}
        vercel-project-id: ${{ secrets.PROJECT_ID }}
        vercel-args: '--prod'
    
    # Deploy to Netlify
    - name: Deploy to Netlify
      uses: nwtgck/actions-netlify@v2.1
      with:
        publish-dir: './dist'
        production-branch: main
        github-token: ${{ secrets.GITHUB_TOKEN }}
        deploy-message: 'Deploy from GitHub Actions'
        enable-pull-request-comment: true
        enable-commit-comment: true
      env:
        NETLIFY_AUTH_TOKEN: ${{ secrets.NETLIFY_AUTH_TOKEN }}
        NETLIFY_SITE_ID: ${{ secrets.NETLIFY_SITE_ID }}
    
    # Deploy to AWS S3
    - name: Deploy to AWS S3
      uses: jakejarvis/s3-sync-action@master
      with:
        args: --delete
      env:
        AWS_S3_BUCKET: ${{ secrets.AWS_S3_BUCKET }}
        AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
        AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
        AWS_REGION: 'us-east-1'
        SOURCE_DIR: 'dist'
    
    # Deploy to Kubernetes
    - name: Deploy to Kubernetes
      uses: azure/k8s-deploy@v1
      with:
        manifests: |
          k8s/deployment.yaml
          k8s/service.yaml
        images: |
          ghcr.io/${{ github.repository }}:${{ github.sha }}
        kubectl-version: 'latest'
```

## 🔧 Creazione di Azioni Custom

### Action.yml Configuration

```yaml
# .github/actions/custom-deploy/action.yml
name: 'Custom Deploy Action'
description: 'Deploy application with custom logic'
branding:
  icon: 'upload-cloud'
  color: 'blue'

inputs:
  environment:
    description: 'Target environment'
    required: true
    default: 'staging'
  version:
    description: 'Application version'
    required: true
  dry-run:
    description: 'Perform dry run'
    required: false
    default: 'false'
  config-file:
    description: 'Path to config file'
    required: false
    default: 'deploy.config.yml'

outputs:
  deployment-url:
    description: 'URL of deployed application'
    value: ${{ steps.deploy.outputs.url }}
  deployment-id:
    description: 'Unique deployment identifier'
    value: ${{ steps.deploy.outputs.id }}

runs:
  using: 'composite'
  steps:
    - name: Validate inputs
      shell: bash
      run: |
        if [ -z "${{ inputs.environment }}" ]; then
          echo "❌ Environment is required"
          exit 1
        fi
        
        if [ -z "${{ inputs.version }}" ]; then
          echo "❌ Version is required"
          exit 1
        fi
        
        echo "✅ Input validation passed"
        echo "Environment: ${{ inputs.environment }}"
        echo "Version: ${{ inputs.version }}"
        echo "Dry run: ${{ inputs.dry-run }}"
    
    - name: Load configuration
      shell: bash
      run: |
        if [ -f "${{ inputs.config-file }}" ]; then
          echo "Loading config from ${{ inputs.config-file }}"
          # Parse YAML config
          CONFIG=$(cat ${{ inputs.config-file }})
          echo "config<<EOF" >> $GITHUB_ENV
          echo "$CONFIG" >> $GITHUB_ENV
          echo "EOF" >> $GITHUB_ENV
        else
          echo "⚠️ Config file not found, using defaults"
        fi
    
    - name: Deploy application
      id: deploy
      shell: bash
      env:
        ENVIRONMENT: ${{ inputs.environment }}
        VERSION: ${{ inputs.version }}
        DRY_RUN: ${{ inputs.dry-run }}
      run: |
        echo "🚀 Starting deployment..."
        
        # Generate deployment ID
        DEPLOYMENT_ID="deploy-$(date +%Y%m%d-%H%M%S)-$(openssl rand -hex 4)"
        echo "Deployment ID: $DEPLOYMENT_ID"
        
        if [ "$DRY_RUN" == "true" ]; then
          echo "🔍 DRY RUN MODE - No actual deployment"
          URL="https://dry-run-$ENVIRONMENT.example.com"
        else
          echo "📦 Deploying version $VERSION to $ENVIRONMENT"
          # Actual deployment logic here
          URL="https://$ENVIRONMENT.example.com"
          
          # Simulate deployment time
          sleep 5
          echo "✅ Deployment completed successfully"
        fi
        
        echo "id=$DEPLOYMENT_ID" >> $GITHUB_OUTPUT
        echo "url=$URL" >> $GITHUB_OUTPUT
        echo "🌐 Application available at: $URL"
```

### JavaScript Action

```javascript
// .github/actions/notify-slack/index.js
const core = require('@actions/core');
const github = require('@actions/github');
const axios = require('axios');

async function run() {
  try {
    // Get inputs
    const webhookUrl = core.getInput('webhook-url', { required: true });
    const message = core.getInput('message') || 'GitHub Actions notification';
    const channel = core.getInput('channel') || '#general';
    const username = core.getInput('username') || 'GitHub Actions';
    const iconEmoji = core.getInput('icon-emoji') || ':octocat:';
    
    // Get GitHub context
    const { context } = github;
    const { repo, actor, workflow, runId } = context;
    
    // Build Slack message
    const slackMessage = {
      channel,
      username,
      icon_emoji: iconEmoji,
      text: message,
      attachments: [
        {
          color: core.getInput('status') === 'success' ? 'good' : 'danger',
          fields: [
            {
              title: 'Repository',
              value: `${repo.owner}/${repo.repo}`,
              short: true
            },
            {
              title: 'Workflow',
              value: workflow,
              short: true
            },
            {
              title: 'Actor',
              value: actor,
              short: true
            },
            {
              title: 'Run ID',
              value: `<https://github.com/${repo.owner}/${repo.repo}/actions/runs/${runId}|${runId}>`,
              short: true
            }
          ],
          footer: 'GitHub Actions',
          ts: Math.floor(Date.now() / 1000)
        }
      ]
    };
    
    // Send to Slack
    const response = await axios.post(webhookUrl, slackMessage);
    
    if (response.status === 200) {
      core.info('✅ Slack notification sent successfully');
      core.setOutput('status', 'success');
    } else {
      core.setFailed(`❌ Failed to send Slack notification: ${response.status}`);
    }
    
  } catch (error) {
    core.setFailed(`❌ Action failed: ${error.message}`);
  }
}

run();
```

```yaml
# .github/actions/notify-slack/action.yml
name: 'Slack Notification'
description: 'Send notifications to Slack'
inputs:
  webhook-url:
    description: 'Slack webhook URL'
    required: true
  message:
    description: 'Message to send'
    required: false
    default: 'GitHub Actions notification'
  channel:
    description: 'Slack channel'
    required: false
    default: '#general'
  username:
    description: 'Bot username'
    required: false
    default: 'GitHub Actions'
  icon-emoji:
    description: 'Bot icon emoji'
    required: false
    default: ':octocat:'
  status:
    description: 'Build status'
    required: false
    default: 'success'
outputs:
  status:
    description: 'Notification status'
runs:
  using: 'node16'
  main: 'index.js'
```

### Usage della Custom Action

```yaml
# Utilizzo dell'azione custom
jobs:
  deploy-and-notify:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Deploy application
      id: deploy
      uses: ./.github/actions/custom-deploy
      with:
        environment: 'production'
        version: ${{ github.sha }}
        dry-run: 'false'
        config-file: 'deploy.prod.yml'
    
    - name: Notify success
      if: success()
      uses: ./.github/actions/notify-slack
      with:
        webhook-url: ${{ secrets.SLACK_WEBHOOK }}
        message: |
          🎉 Deployment successful!
          
          Environment: production
          Version: ${{ github.sha }}
          URL: ${{ steps.deploy.outputs.deployment-url }}
        channel: '#deployments'
        status: 'success'
    
    - name: Notify failure
      if: failure()
      uses: ./.github/actions/notify-slack
      with:
        webhook-url: ${{ secrets.SLACK_WEBHOOK }}
        message: |
          ❌ Deployment failed!
          
          Environment: production
          Version: ${{ github.sha }}
          Check logs: ${{ github.server_url }}/${{ github.repository }}/actions/runs/${{ github.run_id }}
        channel: '#deployments'
        status: 'failure'
```

## 🎯 Advanced Action Patterns

### Conditional Action Execution

```yaml
jobs:
  conditional-actions:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # Only run on specific file changes
    - name: Get changed files
      id: changes
      uses: dorny/paths-filter@v2
      with:
        filters: |
          docs:
            - 'docs/**'
          src:
            - 'src/**'
          tests:
            - 'tests/**'
    
    # Run documentation build only if docs changed
    - name: Build documentation
      if: steps.changes.outputs.docs == 'true'
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./docs
    
    # Run tests only if source or tests changed
    - name: Run tests
      if: steps.changes.outputs.src == 'true' || steps.changes.outputs.tests == 'true'
      run: npm test
    
    # Always run security scan
    - name: Security scan
      uses: github/codeql-action/analyze@v2
```

### Matrix Actions

```yaml
jobs:
  test-matrix:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        node-version: [16, 18, 20]
        include:
          - os: ubuntu-latest
            node-version: 20
            coverage: true
        exclude:
          - os: windows-latest
            node-version: 16
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run tests
      run: npm test
    
    - name: Upload coverage
      if: matrix.coverage
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage/lcov.info
```

## 🛡️ Security Best Practices

### Action Security Verification

```yaml
jobs:
  secure-actions:
    runs-on: ubuntu-latest
    
    steps:
    # Pin actions to specific SHA for security
    - name: Checkout code
      uses: actions/checkout@b4ffde65f46336ab88eb53be808477a3936bae11 # v4.1.1
    
    # Verify action signature (if available)
    - name: Setup Node.js with verification
      uses: actions/setup-node@8f152de45cc393bb48ce5d89d36b731f54556e65 # v4.0.0
      with:
        node-version: '18'
    
    # Use official actions when possible
    - name: Cache dependencies
      uses: actions/cache@ab5e6d0c87105b4c9c2047343972218f562e4319 # v4.0.1
      with:
        path: ~/.npm
        key: ${{ runner.os }}-node-${{ hashFiles('**/package-lock.json') }}
    
    # Audit third-party actions
    - name: Audit action usage
      run: |
        echo "Auditing third-party actions..."
        # Check for known vulnerabilities
        # Verify action sources
```

### Secrets Management in Actions

```yaml
jobs:
  secrets-management:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    # Mask sensitive outputs
    - name: Process sensitive data
      run: |
        SENSITIVE_VALUE="${{ secrets.API_KEY }}"
        echo "::add-mask::$SENSITIVE_VALUE"
        echo "Processing with key: ${SENSITIVE_VALUE:0:4}***"
    
    # Use environment-specific secrets
    - name: Deploy to environment
      env:
        API_ENDPOINT: ${{ secrets[format('{0}_API_ENDPOINT', github.ref_name)] }}
        API_KEY: ${{ secrets[format('{0}_API_KEY', github.ref_name)] }}
      run: |
        echo "Deploying to environment: ${{ github.ref_name }}"
        echo "API endpoint: $API_ENDPOINT"
        # Deployment logic
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la pratica migliore per il versioning delle azioni in produzione?**

A) Usare sempre `@main` per avere le ultime features
B) Utilizzare tag major version (es. `@v4`) per stabilità
C) Usare commit SHA specifici per massima sicurezza
D) Non specificare versione

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

Utilizzare tag major version (es. `@v4`) offre il miglior bilanciamento tra stabilità e aggiornamenti di sicurezza automatici. I commit SHA specifici sono per casi con requisiti di sicurezza estremi.
</details>

### Domanda 2
**Quando è appropriato creare un'azione custom invece di usare azioni esistenti?**

A) Sempre, per avere controllo completo
B) Mai, le azioni marketplace sono sempre migliori
C) Quando la logica è specifica al progetto e riutilizzabile
D) Solo per aziende grandi

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: C**

Le azioni custom sono appropriate quando si ha logica specifica al progetto che viene riutilizzata in multiple workflow, o quando le azioni esistenti non soddisfano requisiti specifici.
</details>

### Domanda 3
**Qual è il metodo più sicuro per gestire secrets nelle azioni custom?**

A) Hardcodare i valori nel codice
B) Usare GitHub Secrets con masking e environment-specific naming
C) Passare secrets come parametri in chiaro
D) Memorizzare secrets in file

<details>
<summary>👁️ Mostra Risposta</summary>

**Risposta: B**

Utilizzare GitHub Secrets con masking automatico e naming specifico per environment garantisce sicurezza e flessibilità nella gestione di credenziali sensibili.
</details>

## 📚 Prossimi Passi

Ora che hai esplorato il mondo delle GitHub Actions, sei pronto per:

1. **[Esempi Pratici](../esempi/01-first-workflow.md)** - Implementazioni complete e reali
2. **[Esercizi](../esercizi/01-ci-setup.md)** - Pratica hands-on
3. **[Advanced Automation](../../23-Git-Flow-e-Strategie/guide/03-advanced-workflow-automation.md)** - Automazioni enterprise

Continua con gli esempi pratici per vedere GitHub Actions in azione!
