# Esempi Pratici - Git Flow e Strategie

## Esempio 1: Enterprise Git Flow Implementation

### Scenario
Un'azienda di software enterprise con 15 sviluppatori deve implementare Git Flow per un prodotto SaaS con release trimestrali.

### Struttura del Progetto

```
enterprise-saas/
├── .gitflow-config
├── scripts/
│   ├── gitflow-setup.sh
│   ├── feature-workflow.sh
│   ├── release-automation.sh
│   └── hotfix-emergency.sh
├── .github/
│   └── workflows/
│       ├── gitflow-ci.yml
│       ├── release-pipeline.yml
│       └── hotfix-pipeline.yml
├── docs/
│   ├── git-flow-guide.md
│   └── release-process.md
└── package.json
```

### Setup Script Completo

```bash
#!/bin/bash
# scripts/gitflow-setup.sh

set -euo pipefail

PROJECT_NAME="enterprise-saas"
REMOTE_URL="https://github.com/company/enterprise-saas.git"

echo "🚀 Setting up Enterprise Git Flow for $PROJECT_NAME"

# 1. Configura Git Flow
git flow init -d

# 2. Configura branch protection
setup_branch_protection() {
    echo "🛡️ Setting up branch protection rules..."
    
    # Main branch protection
    gh api repos/company/enterprise-saas/branches/main/protection \
        --method PUT \
        --field required_status_checks='{"strict":true,"contexts":["ci/tests","ci/security","ci/build"]}' \
        --field enforce_admins=true \
        --field required_pull_request_reviews='{"required_approving_review_count":2,"dismiss_stale_reviews":true,"require_code_owner_reviews":true}' \
        --field restrictions=null

    # Develop branch protection
    gh api repos/company/enterprise-saas/branches/develop/protection \
        --method PUT \
        --field required_status_checks='{"strict":true,"contexts":["ci/tests","ci/lint"]}' \
        --field enforce_admins=false \
        --field required_pull_request_reviews='{"required_approving_review_count":1,"dismiss_stale_reviews":true}' \
        --field restrictions=null
}

# 3. Configura team permissions
setup_team_permissions() {
    echo "👥 Setting up team permissions..."
    
    # Senior developers can push to develop
    gh api repos/company/enterprise-saas/teams/senior-developers/permissions \
        --method PUT \
        --field permission=push

    # Regular developers can only create PRs
    gh api repos/company/enterprise-saas/teams/developers/permissions \
        --method PUT \
        --field permission=pull

    # DevOps team can push to main (for hotfixes)
    gh api repos/company/enterprise-saas/teams/devops/permissions \
        --method PUT \
        --field permission=admin
}

# 4. Crea template per PR
create_pr_templates() {
    echo "📋 Creating PR templates..."
    
    mkdir -p .github/pull_request_template

    cat > .github/pull_request_template/feature.md << 'EOF'
## Feature Description
Brief description of the feature

## Type of Change
- [ ] New feature
- [ ] Enhancement
- [ ] Bug fix
- [ ] Breaking change

## Testing Checklist
- [ ] Unit tests added/updated
- [ ] Integration tests added/updated
- [ ] Manual testing completed
- [ ] Performance impact assessed

## Code Quality
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No merge conflicts

## Release Notes
Brief description for release notes (if applicable)

## Jira Ticket
Link to Jira ticket: [PROJ-XXX](https://company.atlassian.net/browse/PROJ-XXX)
EOF

    cat > .github/pull_request_template/release.md << 'EOF'
## Release Preparation
Version: 

## Release Checklist
- [ ] All planned features merged
- [ ] Version number updated
- [ ] Changelog updated
- [ ] Database migrations tested
- [ ] Performance regression tests passed
- [ ] Security scan completed
- [ ] Documentation updated
- [ ] Stakeholder approval received

## Deployment Plan
- [ ] Staging deployment scheduled
- [ ] Production deployment scheduled
- [ ] Rollback plan prepared
- [ ] Monitoring alerts configured

## Communication
- [ ] Release notes prepared
- [ ] Customer communication planned
- [ ] Internal team notified
EOF
}

# 5. Configura hooks Git
setup_git_hooks() {
    echo "🪝 Setting up Git hooks..."
    
    mkdir -p .git/hooks

    cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Pre-commit hook for code quality

# Run linting
npm run lint
if [ $? -ne 0 ]; then
    echo "❌ Linting failed. Please fix errors before committing."
    exit 1
fi

# Run tests on changed files
npm run test:changed
if [ $? -ne 0 ]; then
    echo "❌ Tests failed. Please fix tests before committing."
    exit 1
fi

# Check commit message format
commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'
commit_message=$(cat "$1")

if ! [[ $commit_message =~ $commit_regex ]]; then
    echo "❌ Invalid commit message format."
    echo "Format: type(scope): description"
    echo "Types: feat, fix, docs, style, refactor, test, chore"
    exit 1
fi
EOF

    chmod +x .git/hooks/pre-commit
}

# 6. Crea workflow helper scripts
create_workflow_scripts() {
    echo "⚙️ Creating workflow helper scripts..."
    
    cat > scripts/feature-workflow.sh << 'EOF'
#!/bin/bash
# Feature workflow helper

action=$1
feature_name=$2

case $action in
    "start")
        if [ -z "$feature_name" ]; then
            echo "Usage: ./scripts/feature-workflow.sh start <feature-name>"
            exit 1
        fi
        
        echo "🚀 Starting feature: $feature_name"
        git flow feature start "$feature_name"
        
        # Create initial structure
        mkdir -p "src/features/$feature_name"
        echo "# Feature: $feature_name" > "src/features/$feature_name/README.md"
        
        # Commit initial structure
        git add .
        git commit -m "feat: initialize $feature_name feature"
        
        echo "✅ Feature $feature_name initialized"
        echo "📁 Feature directory: src/features/$feature_name"
        ;;
        
    "finish")
        if [ -z "$feature_name" ]; then
            echo "Usage: ./scripts/feature-workflow.sh finish <feature-name>"
            exit 1
        fi
        
        echo "🏁 Finishing feature: $feature_name"
        
        # Run pre-finish checks
        echo "🔍 Running pre-finish checks..."
        npm test
        npm run lint
        npm run build
        
        if [ $? -eq 0 ]; then
            git flow feature finish "$feature_name"
            echo "✅ Feature $feature_name finished and merged to develop"
        else
            echo "❌ Pre-finish checks failed. Please fix issues before finishing."
            exit 1
        fi
        ;;
        
    "publish")
        if [ -z "$feature_name" ]; then
            echo "Usage: ./scripts/feature-workflow.sh publish <feature-name>"
            exit 1
        fi
        
        git flow feature publish "$feature_name"
        echo "📤 Feature $feature_name published for collaboration"
        ;;
        
    *)
        echo "Usage: ./scripts/feature-workflow.sh {start|finish|publish} <feature-name>"
        ;;
esac
EOF

    chmod +x scripts/feature-workflow.sh
}

# Execute setup
setup_branch_protection
setup_team_permissions
create_pr_templates
setup_git_hooks
create_workflow_scripts

echo "✅ Enterprise Git Flow setup completed!"
echo ""
echo "📋 Next steps:"
echo "1. Share git-flow-guide.md with the team"
echo "2. Schedule Git Flow training session"
echo "3. Set up monitoring for branch policies"
echo "4. Configure automated testing pipelines"
```

### CI/CD Pipeline per Git Flow

```yaml
# .github/workflows/gitflow-ci.yml
name: Git Flow CI/CD

on:
  push:
    branches: 
      - develop
      - 'feature/**'
      - 'release/**'
      - 'hotfix/**'
  pull_request:
    branches: 
      - develop
      - main

env:
  NODE_VERSION: '18'
  SONAR_PROJECT_KEY: 'enterprise-saas'

jobs:
  # ====================================
  # FEATURE BRANCH WORKFLOW
  # ====================================
  feature-validation:
    if: startsWith(github.ref, 'refs/heads/feature/')
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0  # Needed for SonarQube
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Lint code
      run: npm run lint
    
    - name: Type check
      run: npm run type-check
    
    - name: Run unit tests
      run: npm run test:unit -- --coverage
    
    - name: Run integration tests
      run: npm run test:integration
    
    - name: SonarQube analysis
      uses: sonarqube-quality-gate-action@master
      env:
        SONAR_TOKEN: ${{ secrets.SONAR_TOKEN }}
        SONAR_HOST_URL: ${{ secrets.SONAR_HOST_URL }}
    
    - name: Build application
      run: npm run build
    
    - name: Feature branch security scan
      run: npm audit --audit-level=moderate

  # ====================================
  # DEVELOP BRANCH WORKFLOW
  # ====================================
  develop-integration:
    if: github.ref == 'refs/heads/develop'
    runs-on: ubuntu-latest
    services:
      postgres:
        image: postgres:15
        env:
          POSTGRES_PASSWORD: postgres
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Setup test database
      run: |
        npm run db:migrate
        npm run db:seed:test
    
    - name: Full test suite
      run: |
        npm run test:unit -- --coverage
        npm run test:integration
        npm run test:e2e
    
    - name: Performance tests
      run: npm run test:performance
    
    - name: Security scan
      run: |
        npm audit --audit-level=high
        npx snyk test
    
    - name: Build and package
      run: |
        npm run build
        npm pack
    
    - name: Deploy to development environment
      run: |
        echo "Deploying to development environment..."
        # Deploy logic here
    
    - name: Integration testing on dev environment
      run: npm run test:integration:dev

  # ====================================
  # RELEASE BRANCH WORKFLOW
  # ====================================
  release-preparation:
    if: startsWith(github.ref, 'refs/heads/release/')
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    
    - name: Extract version from branch
      id: version
      run: |
        BRANCH_NAME=${GITHUB_REF#refs/heads/}
        VERSION=${BRANCH_NAME#release/}
        echo "version=$VERSION" >> $GITHUB_OUTPUT
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Release testing suite
      run: |
        npm run test:all
        npm run test:performance
        npm run test:security
    
    - name: Build production bundle
      run: npm run build:production
    
    - name: Generate changelog
      run: |
        npx conventional-changelog -p angular -i CHANGELOG.md -s -r 0
        git add CHANGELOG.md
        git commit -m "chore: update changelog for ${{ steps.version.outputs.version }}" || true
    
    - name: Deploy to staging
      run: |
        echo "Deploying version ${{ steps.version.outputs.version }} to staging..."
        # Staging deployment logic
    
    - name: Staging validation tests
      run: npm run test:staging
    
    - name: Performance regression tests
      run: npm run test:performance:staging
    
    - name: Security penetration tests
      run: npm run test:security:staging

  # ====================================
  # HOTFIX WORKFLOW
  # ====================================
  hotfix-emergency:
    if: startsWith(github.ref, 'refs/heads/hotfix/')
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    
    - name: Extract hotfix info
      id: hotfix
      run: |
        BRANCH_NAME=${GITHUB_REF#refs/heads/}
        HOTFIX_NAME=${BRANCH_NAME#hotfix/}
        echo "name=$HOTFIX_NAME" >> $GITHUB_OUTPUT
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Critical path testing
      run: |
        npm run test:critical-path
        npm run test:regression
    
    - name: Security scan
      run: npm run test:security
    
    - name: Build hotfix
      run: npm run build
    
    - name: Deploy to staging for hotfix validation
      run: |
        echo "Deploying hotfix ${{ steps.hotfix.outputs.name }} to staging..."
        # Hotfix staging deployment
    
    - name: Hotfix validation
      run: npm run test:hotfix-validation
    
    - name: Notify on-call team
      uses: 8398a7/action-slack@v3
      with:
        status: custom
        custom_payload: |
          {
            "text": "🚨 Hotfix Pipeline: ${{ steps.hotfix.outputs.name }}",
            "attachments": [{
              "color": "warning",
              "fields": [{
                "title": "Hotfix",
                "value": "${{ steps.hotfix.outputs.name }}",
                "short": true
              }, {
                "title": "Status",
                "value": "Ready for production deployment",
                "short": true
              }]
            }]
          }
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}

  # ====================================
  # MAIN BRANCH DEPLOYMENT
  # ====================================
  production-deployment:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    environment:
      name: production
      url: https://app.enterprise-saas.com
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Production build
      run: npm run build:production
    
    - name: Pre-deployment security scan
      run: |
        npm audit --audit-level=critical
        docker run --rm -v $(pwd):/app owasp/zap2docker-stable zap-baseline.py -t http://staging.enterprise-saas.com
    
    - name: Blue-Green Deployment
      run: |
        echo "Starting blue-green deployment..."
        ./scripts/blue-green-deploy.sh
    
    - name: Post-deployment verification
      run: |
        npm run test:smoke:production
        npm run test:health-check:production
    
    - name: Update monitoring dashboards
      run: |
        curl -X POST "${{ secrets.GRAFANA_WEBHOOK }}" \
          -H "Content-Type: application/json" \
          -d '{"deployment": true, "version": "${{ github.sha }}", "environment": "production"}'
    
    - name: Notify stakeholders
      uses: 8398a7/action-slack@v3
      with:
        status: success
        text: |
          🚀 Production Deployment Successful
          Version: ${{ github.sha }}
          Environment: https://app.enterprise-saas.com
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}
```

---

## Esempio 2: GitHub Flow per Startup Agile

### Scenario
Una startup con 5 sviluppatori che deployano multiple volte al giorno utilizzando continuous deployment.

### Configurazione GitHub Flow

```yaml
# .github/workflows/github-flow.yml
name: GitHub Flow - Continuous Deployment

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

env:
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}

jobs:
  # ====================================
  # CONTINUOUS INTEGRATION
  # ====================================
  ci:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [18, 20]
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Lint and format check
      run: |
        npm run lint
        npm run format:check
    
    - name: Type checking
      run: npm run type-check
    
    - name: Unit tests
      run: npm run test:unit -- --coverage
    
    - name: Integration tests
      run: npm run test:integration
    
    - name: Build application
      run: npm run build
    
    - name: E2E tests (on main)
      if: github.ref == 'refs/heads/main'
      run: |
        npm run start:test &
        sleep 30
        npm run test:e2e
        pkill -f "npm run start:test"

  # ====================================
  # PREVIEW DEPLOYMENT (PRs)
  # ====================================
  deploy-preview:
    if: github.event_name == 'pull_request'
    runs-on: ubuntu-latest
    needs: ci
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build for preview
      run: npm run build
      env:
        NODE_ENV: staging
        PREVIEW_MODE: true
    
    - name: Deploy to Vercel Preview
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-args: '--prebuilt'
        vercel-org-id: ${{ secrets.ORG_ID }}
        vercel-project-id: ${{ secrets.PROJECT_ID }}
        scope: ${{ secrets.TEAM_ID }}
    
    - name: Comment PR with preview URL
      uses: actions/github-script@v7
      with:
        script: |
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: `🚀 Preview deployment ready!\n\n🔗 **Preview URL**: https://startup-app-git-${context.payload.pull_request.head.ref}-team.vercel.app\n\n⚡ Auto-deployed from commit ${context.sha.substring(0, 7)}`
          })

  # ====================================
  # PRODUCTION DEPLOYMENT (main)
  # ====================================
  deploy-production:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    needs: ci
    environment:
      name: production
      url: https://startup-app.com
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build for production
      run: npm run build
      env:
        NODE_ENV: production
    
    - name: Deploy to Vercel Production
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-args: '--prebuilt --prod'
        vercel-org-id: ${{ secrets.ORG_ID }}
        vercel-project-id: ${{ secrets.PROJECT_ID }}
        scope: ${{ secrets.TEAM_ID }}
    
    - name: Run post-deployment tests
      run: |
        sleep 30  # Wait for deployment to be ready
        npm run test:smoke -- --url=https://startup-app.com
    
    - name: Update Sentry release
      run: |
        npx sentry-cli releases new ${{ github.sha }}
        npx sentry-cli releases set-commits ${{ github.sha }} --auto
        npx sentry-cli releases finalize ${{ github.sha }}
      env:
        SENTRY_AUTH_TOKEN: ${{ secrets.SENTRY_AUTH_TOKEN }}
        SENTRY_ORG: startup-team
        SENTRY_PROJECT: startup-app
    
    - name: Notify team
      uses: 8398a7/action-slack@v3
      with:
        status: ${{ job.status }}
        text: |
          ${{ job.status == 'success' && '✅' || '❌' }} Production deployment ${{ job.status }}
          🔗 https://startup-app.com
          📝 Commit: ${{ github.event.head_commit.message }}
          👤 By: ${{ github.event.head_commit.author.name }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}

  # ====================================
  # MONITORING & ALERTS
  # ====================================
  setup-monitoring:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    needs: deploy-production
    
    steps:
    - name: Create deployment marker in monitoring
      run: |
        # DataDog deployment marker
        curl -X POST "https://api.datadoghq.com/api/v1/events" \
        -H "Content-Type: application/json" \
        -H "DD-API-KEY: ${{ secrets.DATADOG_API_KEY }}" \
        -d '{
          "title": "Production Deployment",
          "text": "Deployed commit ${{ github.sha }} to production",
          "tags": ["deployment", "production", "github-flow"],
          "alert_type": "info"
        }'
    
    - name: Update status page
      run: |
        # StatusPage.io update
        curl -X POST "https://api.statuspage.io/v1/pages/${{ secrets.STATUSPAGE_PAGE_ID }}/incidents" \
        -H "Authorization: OAuth ${{ secrets.STATUSPAGE_API_KEY }}" \
        -H "Content-Type: application/json" \
        -d '{
          "incident": {
            "name": "Maintenance - New Feature Deployment",
            "status": "completed",
            "impact": "none",
            "body": "Successfully deployed new features to production."
          }
        }'
```

### Helper Scripts per GitHub Flow

```bash
#!/bin/bash
# scripts/github-flow-helpers.sh

# Feature development helper
develop_feature() {
    local feature_name="$1"
    
    if [[ -z "$feature_name" ]]; then
        echo "Usage: develop_feature <feature-name>"
        return 1
    fi
    
    echo "🚀 Starting GitHub Flow feature development: $feature_name"
    
    # Create feature branch from main
    git checkout main
    git pull origin main
    git checkout -b "feature/$feature_name"
    
    # Setup development environment
    echo "📦 Setting up development environment..."
    npm install
    npm run dev &
    DEV_PID=$!
    
    echo "✅ Feature branch created: feature/$feature_name"
    echo "🌐 Development server started (PID: $DEV_PID)"
    echo "📝 Next steps:"
    echo "   1. Develop your feature"
    echo "   2. Commit changes frequently"
    echo "   3. Push early: git push origin feature/$feature_name"
    echo "   4. Create PR when ready"
}

# Quick commit and push
quick_push() {
    local message="$1"
    
    if [[ -z "$message" ]]; then
        echo "Usage: quick_push <commit-message>"
        return 1
    fi
    
    # Pre-commit checks
    echo "🔍 Running pre-commit checks..."
    npm run lint:fix
    npm run format
    npm run test:unit
    
    if [[ $? -eq 0 ]]; then
        git add .
        git commit -m "$message"
        git push origin HEAD
        echo "✅ Changes pushed successfully"
    else
        echo "❌ Pre-commit checks failed"
        return 1
    fi
}

# Create PR helper
create_pr() {
    local title="$1"
    local description="$2"
    
    if [[ -z "$title" ]]; then
        echo "Usage: create_pr <title> [description]"
        return 1
    fi
    
    # Get current branch
    local branch=$(git branch --show-current)
    
    # Push current branch
    git push origin "$branch"
    
    # Create PR using GitHub CLI
    if [[ -n "$description" ]]; then
        gh pr create --title "$title" --body "$description" --base main
    else
        gh pr create --title "$title" --base main --web
    fi
    
    echo "✅ Pull request created"
}

# Deployment status checker
check_deployment() {
    echo "🔍 Checking deployment status..."
    
    # Check main branch status
    local main_status=$(gh run list --branch main --limit 1 --json status --jq '.[0].status')
    echo "Main branch CI status: $main_status"
    
    # Check production URL
    local prod_status=$(curl -s -o /dev/null -w "%{http_code}" https://startup-app.com/health)
    echo "Production health check: $prod_status"
    
    # Check Vercel deployment
    local vercel_status=$(vercel ls --scope team --json | jq -r '.[0].state')
    echo "Vercel deployment status: $vercel_status"
    
    if [[ "$main_status" == "completed" && "$prod_status" == "200" && "$vercel_status" == "READY" ]]; then
        echo "✅ All systems operational"
    else
        echo "⚠️  Some issues detected"
    fi
}

# Rollback helper
emergency_rollback() {
    echo "🚨 Emergency rollback initiated..."
    
    # Get previous successful deployment
    local prev_commit=$(gh run list --branch main --status success --limit 2 --json headSha --jq '.[1].headSha')
    
    if [[ -n "$prev_commit" ]]; then
        echo "Rolling back to commit: $prev_commit"
        
        # Create rollback branch
        git checkout main
        git pull origin main
        git checkout -b "rollback/emergency-$(date +%Y%m%d-%H%M%S)"
        
        # Revert to previous commit
        git revert --no-edit HEAD.."$prev_commit"
        
        # Push and create emergency PR
        git push origin HEAD
        gh pr create --title "🚨 Emergency Rollback" --body "Automatic rollback to $prev_commit" --base main
        
        echo "✅ Emergency rollback PR created"
    else
        echo "❌ Could not find previous successful deployment"
    fi
}

# Feature flag toggle
toggle_feature() {
    local flag_name="$1"
    local enabled="$2"
    
    if [[ -z "$flag_name" || -z "$enabled" ]]; then
        echo "Usage: toggle_feature <flag-name> <true|false>"
        return 1
    fi
    
    # Update feature flag via API
    curl -X PATCH "https://api.startup-app.com/admin/feature-flags/$flag_name" \
        -H "Authorization: Bearer $ADMIN_API_TOKEN" \
        -H "Content-Type: application/json" \
        -d "{\"enabled\": $enabled}"
    
    echo "✅ Feature flag '$flag_name' set to: $enabled"
}

# Setup aliases
alias gf-dev="develop_feature"
alias gf-push="quick_push"
alias gf-pr="create_pr"
alias gf-status="check_deployment"
alias gf-rollback="emergency_rollback"
alias gf-feature="toggle_feature"

echo "🔧 GitHub Flow helpers loaded!"
echo "Available commands:"
echo "  gf-dev <name>     - Start feature development"
echo "  gf-push <msg>     - Quick commit and push"
echo "  gf-pr <title>     - Create pull request"
echo "  gf-status         - Check deployment status"
echo "  gf-rollback       - Emergency rollback"
echo "  gf-feature <flag> <bool> - Toggle feature flag"
```

---

## Esempio 3: Hybrid Workflow per Team Distribuito

### Scenario
Un team distribuito di 12 sviluppatori che lavora su un'applicazione mobile con release mensili e hotfix occasionali.

### Hybrid Workflow Configuration

```yaml
# .github/workflows/hybrid-workflow.yml
name: Hybrid Workflow - Mobile App

on:
  push:
    branches: 
      - main
      - develop
      - 'feature/**'
      - 'release/**'
      - 'hotfix/**'
  pull_request:
    branches: [main, develop]

env:
  FLUTTER_VERSION: '3.13.0'
  ANDROID_API_LEVEL: '33'
  IOS_VERSION: '16.0'

jobs:
  # ====================================
  # BRANCH TYPE DETECTION
  # ====================================
  detect-workflow:
    runs-on: ubuntu-latest
    outputs:
      workflow-type: ${{ steps.detect.outputs.workflow-type }}
      deploy-target: ${{ steps.detect.outputs.deploy-target }}
    steps:
    - name: Detect workflow type
      id: detect
      run: |
        if [[ "${{ github.ref }}" == "refs/heads/main" ]]; then
          echo "workflow-type=production" >> $GITHUB_OUTPUT
          echo "deploy-target=app-store" >> $GITHUB_OUTPUT
        elif [[ "${{ github.ref }}" == "refs/heads/develop" ]]; then
          echo "workflow-type=integration" >> $GITHUB_OUTPUT
          echo "deploy-target=internal-testing" >> $GITHUB_OUTPUT
        elif [[ "${{ github.ref }}" == refs/heads/feature/* ]]; then
          echo "workflow-type=feature" >> $GITHUB_OUTPUT
          echo "deploy-target=simulator" >> $GITHUB_OUTPUT
        elif [[ "${{ github.ref }}" == refs/heads/release/* ]]; then
          echo "workflow-type=release" >> $GITHUB_OUTPUT
          echo "deploy-target=beta-testing" >> $GITHUB_OUTPUT
        elif [[ "${{ github.ref }}" == refs/heads/hotfix/* ]]; then
          echo "workflow-type=hotfix" >> $GITHUB_OUTPUT
          echo "deploy-target=emergency" >> $GITHUB_OUTPUT
        fi

  # ====================================
  # MOBILE CI PIPELINE
  # ====================================
  mobile-ci:
    runs-on: ${{ matrix.os }}
    needs: detect-workflow
    strategy:
      matrix:
        os: [ubuntu-latest, macos-latest]
        include:
          - os: ubuntu-latest
            platform: android
          - os: macos-latest
            platform: ios
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Flutter
      uses: subosito/flutter-action@v2
      with:
        flutter-version: ${{ env.FLUTTER_VERSION }}
        channel: 'stable'
    
    - name: Setup Android SDK (Android only)
      if: matrix.platform == 'android'
      uses: android-actions/setup-android@v2
      with:
        api-level: ${{ env.ANDROID_API_LEVEL }}
    
    - name: Setup Xcode (iOS only)
      if: matrix.platform == 'ios'
      uses: maxim-lobanov/setup-xcode@v1
      with:
        xcode-version: '15.0'
    
    - name: Install dependencies
      run: flutter pub get
    
    - name: Analyze code
      run: flutter analyze
    
    - name: Run unit tests
      run: flutter test --coverage
    
    - name: Run integration tests
      if: needs.detect-workflow.outputs.workflow-type != 'feature'
      run: flutter test integration_test/
    
    - name: Build app (${{ matrix.platform }})
      run: |
        if [[ "${{ matrix.platform }}" == "android" ]]; then
          if [[ "${{ needs.detect-workflow.outputs.workflow-type }}" == "production" ]]; then
            flutter build appbundle --release
          else
            flutter build apk --debug
          fi
        else
          if [[ "${{ needs.detect-workflow.outputs.workflow-type }}" == "production" ]]; then
            flutter build ios --release --no-codesign
          else
            flutter build ios --debug --no-codesign
          fi
        fi
    
    - name: Upload artifacts
      uses: actions/upload-artifact@v4
      with:
        name: mobile-app-${{ matrix.platform }}
        path: |
          build/app/outputs/bundle/release/*.aab
          build/app/outputs/apk/debug/*.apk
          build/ios/iphoneos/*.app

  # ====================================
  # DEPLOYMENT PIPELINE
  # ====================================
  deploy:
    runs-on: ubuntu-latest
    needs: [detect-workflow, mobile-ci]
    if: |
      needs.detect-workflow.outputs.deploy-target != 'simulator' &&
      github.event_name == 'push'
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Download artifacts
      uses: actions/download-artifact@v4
      with:
        path: artifacts
    
    - name: Deploy to ${{ needs.detect-workflow.outputs.deploy-target }}
      run: |
        case "${{ needs.detect-workflow.outputs.deploy-target }}" in
          "internal-testing")
            echo "Deploying to Firebase App Distribution..."
            firebase appdistribution:distribute artifacts/mobile-app-android/*.apk \
              --app ${{ secrets.FIREBASE_APP_ID_ANDROID }} \
              --groups "internal-testers"
            ;;
          "beta-testing")
            echo "Deploying to TestFlight and Play Console Internal Testing..."
            fastlane android beta
            fastlane ios beta
            ;;
          "app-store")
            echo "Deploying to App Store and Play Store..."
            fastlane android deploy
            fastlane ios deploy
            ;;
          "emergency")
            echo "Emergency deployment..."
            fastlane android emergency
            fastlane ios emergency
            ;;
        esac

  # ====================================
  # WORKFLOW-SPECIFIC JOBS
  # ====================================
  feature-workflow:
    if: startsWith(github.ref, 'refs/heads/feature/')
    runs-on: ubuntu-latest
    needs: mobile-ci
    steps:
    - name: Feature branch validation
      run: |
        echo "✅ Feature branch validation completed"
        echo "📱 Simulator builds available in artifacts"
    
    - name: Comment on PR (if exists)
      if: github.event_name == 'pull_request'
      uses: actions/github-script@v7
      with:
        script: |
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: `📱 **Feature Build Ready**
            
            ✅ All tests passed
            📦 Simulator builds available
            🔍 Code analysis completed
            
            Ready for review!`
          })

  release-workflow:
    if: startsWith(github.ref, 'refs/heads/release/')
    runs-on: ubuntu-latest
    needs: [detect-workflow, mobile-ci]
    steps:
    - uses: actions/checkout@v4
    
    - name: Extract version
      id: version
      run: |
        BRANCH_NAME=${GITHUB_REF#refs/heads/}
        VERSION=${BRANCH_NAME#release/}
        echo "version=$VERSION" >> $GITHUB_OUTPUT
    
    - name: Update version in pubspec.yaml
      run: |
        sed -i "s/version: .*/version: ${{ steps.version.outputs.version }}/" pubspec.yaml
        git config user.name "Release Bot"
        git config user.email "release@company.com"
        git add pubspec.yaml
        git commit -m "chore: bump version to ${{ steps.version.outputs.version }}"
        git push origin HEAD
    
    - name: Generate release notes
      run: |
        echo "# Release ${{ steps.version.outputs.version }}" > RELEASE_NOTES.md
        echo "" >> RELEASE_NOTES.md
        echo "## Features" >> RELEASE_NOTES.md
        git log --oneline --grep="feat:" develop..HEAD >> RELEASE_NOTES.md
        echo "" >> RELEASE_NOTES.md
        echo "## Bug Fixes" >> RELEASE_NOTES.md
        git log --oneline --grep="fix:" develop..HEAD >> RELEASE_NOTES.md
    
    - name: Notify QA team
      uses: 8398a7/action-slack@v3
      with:
        status: custom
        custom_payload: |
          {
            "text": "📱 Release ${{ steps.version.outputs.version }} ready for QA testing",
            "attachments": [{
              "color": "good",
              "fields": [{
                "title": "Release Version",
                "value": "${{ steps.version.outputs.version }}",
                "short": true
              }, {
                "title": "Testing Environment",
                "value": "Beta Distribution",
                "short": true
              }]
            }]
          }
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_QA }}

  hotfix-workflow:
    if: startsWith(github.ref, 'refs/heads/hotfix/')
    runs-on: ubuntu-latest
    needs: [detect-workflow, mobile-ci]
    steps:
    - name: Extract hotfix info
      id: hotfix
      run: |
        BRANCH_NAME=${GITHUB_REF#refs/heads/}
        HOTFIX_NAME=${BRANCH_NAME#hotfix/}
        echo "name=$HOTFIX_NAME" >> $GITHUB_OUTPUT
    
    - name: Emergency testing
      run: |
        echo "🚨 Running emergency test suite for hotfix: ${{ steps.hotfix.outputs.name }}"
        flutter test test/critical/
        flutter test test/regression/
    
    - name: Notify on-call team
      uses: 8398a7/action-slack@v3
      with:
        status: custom
        custom_payload: |
          {
            "text": "🚨 HOTFIX ALERT",
            "attachments": [{
              "color": "danger",
              "fields": [{
                "title": "Hotfix",
                "value": "${{ steps.hotfix.outputs.name }}",
                "short": true
              }, {
                "title": "Status",
                "value": "Ready for emergency deployment",
                "short": true
              }, {
                "title": "Action Required",
                "value": "Manual approval needed for production deployment",
                "short": false
              }]
            }]
          }
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_ONCALL }}

  production-workflow:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    needs: [detect-workflow, mobile-ci, deploy]
    environment:
      name: production
    steps:
    - name: Production deployment verification
      run: |
        echo "✅ Production deployment completed"
        echo "📱 Apps published to stores"
    
    - name: Update release tracking
      run: |
        # Update Jira releases
        curl -X POST "${{ secrets.JIRA_API_URL }}/rest/api/3/version" \
          -H "Authorization: Basic ${{ secrets.JIRA_AUTH }}" \
          -H "Content-Type: application/json" \
          -d '{
            "name": "Mobile App ${{ github.sha }}",
            "description": "Production release",
            "released": true,
            "releaseDate": "'$(date -I)'"
          }'
    
    - name: Send release announcement
      uses: 8398a7/action-slack@v3
      with:
        status: success
        text: |
          🚀 **Mobile App Released to Production!**
          
          📱 **iOS**: Available on App Store
          🤖 **Android**: Available on Google Play
          📝 **Version**: ${{ github.sha }}
          
          🎉 Great work team!
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_GENERAL }}
```

Questi esempi mostrano implementazioni complete e realistiche di diversi workflow Git, ognuno ottimizzato per scenari specifici di team e progetti.

---

**File:** `esempi/README.md`

🏠 **Home**: [Indice Generale](../README.md)

⬅️ **Precedente**: [Guide Teoriche](../guide/README.md)

➡️ **Successivo**: [Esercizi Pratici](../esercizi/README.md)
