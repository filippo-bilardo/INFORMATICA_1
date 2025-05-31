# 02 - GitHub Flow vs Alternative Strategies

## Obiettivi di Apprendimento
- Comprendere GitHub Flow e la sua semplicità
- Confrontare GitLab Flow con Git Flow
- Analizzare OneFlow e altri workflow alternativi
- Scegliere la strategia appropriata per diversi scenari
- Implementare workflow ibridi personalizzati
- Valutare pro e contro di ogni approccio

## 1. GitHub Flow - Il Workflow Semplificato

### 1.1 Filosofia GitHub Flow

GitHub Flow è una strategia di branching semplificata che privilegia la velocità e la continuous deployment rispetto alla struttura rigida di Git Flow.

```
GitHub Flow Philosophy:
┌─────────────────────────────────────────────┐
│  "Deploy early, deploy often"              │
│  - GitHub Team                             │
│                                             │
│  🎯 Principi:                               │
│  • Semplicità sopra complessità            │
│  • Deploy frequenti                        │
│  • Branch di breve durata                  │
│  • Review obbligatorie                     │
│  • Automatic testing                       │
└─────────────────────────────────────────────┘
```

### 1.2 GitHub Flow Workflow

```mermaid
gitgraph
    commit id: "Initial"
    branch feature/login
    checkout feature/login
    commit id: "Add login"
    commit id: "Fix bugs"
    checkout main
    merge feature/login
    commit id: "Deploy"
    
    branch feature/dashboard
    checkout feature/dashboard
    commit id: "Dashboard"
    checkout main
    merge feature/dashboard
    commit id: "Deploy"
```

**Steps del GitHub Flow:**

```bash
# 1. Crea branch da main
git checkout main
git pull origin main
git checkout -b feature/user-dashboard

# 2. Sviluppa e committa
echo "Dashboard component" > src/Dashboard.js
git add .
git commit -m "feat: add user dashboard component"

# 3. Push early e often
git push origin feature/user-dashboard

# 4. Crea Pull Request appena possibile
# (anche work-in-progress)

# 5. Collabora tramite PR review
git commit -am "address review feedback"
git push origin feature/user-dashboard

# 6. Deploy su staging dal branch feature
# Test in ambiente simile a produzione

# 7. Merge in main solo quando tutto è OK
# 8. Deploy automatico in produzione
# 9. Elimina feature branch
```

### 1.3 Vantaggi GitHub Flow

**✅ Pro:**
- **Semplicità**: Solo main + feature branches
- **Velocità**: Deploy rapidi e frequenti
- **Flessibilità**: Adatto a team di ogni dimensione
- **Continuous Deployment**: Naturalmente compatibile
- **Collaboration**: PR-driven development

**❌ Contro:**
- **Stabilità**: Meno controllo su stabilità main
- **Rollback**: Più complesso gestire rollback
- **Testing**: Richiede excellent test automation
- **Releases**: Non adatto per release schedule rigide

### 1.4 Implementazione GitHub Flow

```yaml
# .github/workflows/github-flow.yml
name: GitHub Flow CI/CD

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
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run tests
      run: npm test
    
    - name: Run integration tests
      run: npm run test:integration

  deploy-staging:
    if: github.event_name == 'pull_request'
    needs: test
    runs-on: ubuntu-latest
    steps:
    - name: Deploy to staging
      run: |
        echo "Deploying PR #${{ github.event.number }} to staging"
        # Deploy logic here
    
    - name: Comment PR with staging URL
      uses: actions/github-script@v7
      with:
        script: |
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: '🚀 Deployed to staging: https://staging-pr-${{ github.event.number }}.example.com'
          })

  deploy-production:
    if: github.ref == 'refs/heads/main'
    needs: test
    runs-on: ubuntu-latest
    steps:
    - name: Deploy to production
      run: |
        echo "Deploying main to production"
        # Production deployment logic
```

## 2. GitLab Flow - Il Compromesso Pratico

### 2.1 GitLab Flow Concepts

GitLab Flow combina la semplicità di GitHub Flow con alcune strutture di Git Flow per ambienti enterprise.

```
GitLab Flow Variants:
┌─────────────────────────────────────────────┐
│  1. Production Branch                       │
│     main → production                       │
│                                             │
│  2. Environment Branches                    │
│     main → staging → production             │
│                                             │
│  3. Release Branches                        │
│     main → release/v1.0 → production        │
└─────────────────────────────────────────────┘
```

### 2.2 GitLab Flow con Environment Branches

```bash
# Setup iniziale
git checkout -b staging
git checkout -b production
git push origin staging production

# Workflow sviluppo
git checkout main
git checkout -b feature/new-api

# Sviluppo
git commit -m "feat: add new API endpoint"
git push origin feature/new-api

# Merge in main dopo PR
git checkout main
git merge feature/new-api

# Promozione attraverso ambienti
git checkout staging
git merge main  # Deploy automatico a staging

# Dopo testing
git checkout production
git merge staging  # Deploy automatico a produzione
```

### 2.3 GitLab Flow Automation

```yaml
# .gitlab-ci.yml
stages:
  - test
  - deploy-staging
  - deploy-production

variables:
  DOCKER_IMAGE: $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA

test:
  stage: test
  script:
    - npm ci
    - npm test
    - npm run test:e2e
  only:
    - merge_requests
    - main

deploy-staging:
  stage: deploy-staging
  script:
    - docker build -t $DOCKER_IMAGE .
    - docker push $DOCKER_IMAGE
    - kubectl set image deployment/app app=$DOCKER_IMAGE
  environment:
    name: staging
    url: https://staging.example.com
  only:
    - main

deploy-production:
  stage: deploy-production
  script:
    - kubectl set image deployment/app app=$DOCKER_IMAGE
  environment:
    name: production
    url: https://example.com
  only:
    - production
  when: manual  # Richiede approvazione manuale
```

## 3. OneFlow - Git Flow Semplificato

### 3.1 OneFlow Philosophy

OneFlow è una variante semplificata di Git Flow che elimina il branch develop mantenendo le release branch.

```
OneFlow Structure:
┌─────────────────────────────────────────────┐
│  main (production)                          │
│  ├── feature/a                             │
│  ├── feature/b                             │
│  └── release/1.0 ────┐                     │
│      ├── hotfix/1.0.1 ─┘                   │
│      └── feature/c (rebase)                │
└─────────────────────────────────────────────┘
```

### 3.2 OneFlow Implementation

```bash
# OneFlow script helper
#!/bin/bash
# oneflow.sh

case $1 in
  "feature")
    git checkout main
    git pull origin main
    git checkout -b "feature/$2"
    echo "✅ Created feature/$2 from main"
    ;;
    
  "release")
    git checkout main
    git pull origin main
    git checkout -b "release/$2"
    echo "$2" > VERSION
    git commit -am "chore: bump version to $2"
    echo "✅ Created release/$2"
    ;;
    
  "finish-release")
    git checkout main
    git merge --no-ff "release/$2"
    git tag -a "v$2" -m "Release $2"
    git branch -d "release/$2"
    echo "✅ Released $2"
    ;;
    
  "hotfix")
    git checkout main
    git pull origin main
    git checkout -b "hotfix/$2"
    echo "✅ Created hotfix/$2"
    ;;
    
  *)
    echo "Usage: oneflow.sh {feature|release|finish-release|hotfix} <name>"
    ;;
esac
```

## 4. Workflow Comparison Matrix

### 4.1 Confronto Dettagliato

| Aspetto | Git Flow | GitHub Flow | GitLab Flow | OneFlow |
|---------|----------|-------------|-------------|---------|
| **Complessità** | Alta | Bassa | Media | Media |
| **Branching** | 5 tipi | 2 tipi | 3 tipi | 3 tipi |
| **Release Control** | Eccellente | Limitato | Buono | Buono |
| **Deploy Frequency** | Schedulato | Continuo | Flessibile | Flessibile |
| **Team Size** | Large (5+) | Any | Medium+ | Medium |
| **Learning Curve** | Ripida | Piatta | Moderata | Moderata |
| **Tool Support** | Eccellente | Nativo | Eccellente | Manuale |

### 4.2 Decision Matrix

```javascript
// workflow-selector.js
class WorkflowSelector {
  static selectWorkflow(projectContext) {
    const {
      teamSize,
      deployFrequency,
      releaseSchedule,
      stabilityRequirement,
      devopsMaturity
    } = projectContext;

    // Git Flow
    if (teamSize > 10 && releaseSchedule === 'planned' && stabilityRequirement === 'high') {
      return {
        workflow: 'Git Flow',
        reason: 'Large team with planned releases and high stability needs',
        setup: this.getGitFlowSetup()
      };
    }

    // GitHub Flow
    if (deployFrequency === 'daily' && devopsMaturity === 'high') {
      return {
        workflow: 'GitHub Flow',
        reason: 'High deployment frequency with mature DevOps practices',
        setup: this.getGitHubFlowSetup()
      };
    }

    // GitLab Flow
    if (teamSize > 5 && stabilityRequirement === 'medium') {
      return {
        workflow: 'GitLab Flow',
        reason: 'Medium team size with moderate stability requirements',
        setup: this.getGitLabFlowSetup()
      };
    }

    // OneFlow (default)
    return {
      workflow: 'OneFlow',
      reason: 'Balanced approach for most scenarios',
      setup: this.getOneFlowSetup()
    };
  }

  static getProjectContext() {
    return {
      teamSize: parseInt(prompt('Team size? (1-5, 6-10, 10+)')),
      deployFrequency: prompt('Deploy frequency? (daily, weekly, monthly)'),
      releaseSchedule: prompt('Release schedule? (planned, continuous)'),
      stabilityRequirement: prompt('Stability requirement? (low, medium, high)'),
      devopsMaturity: prompt('DevOps maturity? (low, medium, high)')
    };
  }
}
```

## 5. Hybrid Workflows

### 5.1 Custom Enterprise Workflow

```bash
# enterprise-flow.sh - Workflow ibrido personalizzato
#!/bin/bash

case $1 in
  "feature")
    # GitHub Flow style per feature
    git checkout main
    git pull origin main
    git checkout -b "feature/$2"
    ;;
    
  "release")
    # Git Flow style per release
    git checkout main
    git checkout -b "release/$2"
    ;;
    
  "emergency")
    # Hotfix immediato con bypass review
    git checkout main
    git checkout -b "emergency/$2"
    echo "⚠️  EMERGENCY BRANCH - Bypass normal review process"
    ;;
    
  "experiment")
    # Branch sperimentale con lifecycle diverso
    git checkout main
    git checkout -b "experiment/$2"
    git config branch.experiment/$2.remote origin
    git config branch.experiment/$2.merge refs/heads/experiment/$2
    echo "🧪 EXPERIMENTAL BRANCH - Will be archived, not merged"
    ;;
esac
```

### 5.2 Multi-Environment GitLab Flow

```yaml
# .gitlab-ci.yml - Multi-environment workflow
stages:
  - test
  - deploy-dev
  - deploy-staging
  - security-scan
  - deploy-production

variables:
  DOCKER_REGISTRY: $CI_REGISTRY_IMAGE
  ENVIRONMENTS: "dev,staging,production"

.deploy_template: &deploy_template
  script:
    - docker build -t $DOCKER_REGISTRY:$CI_COMMIT_SHA .
    - docker push $DOCKER_REGISTRY:$CI_COMMIT_SHA
    - envsubst < k8s/deployment.yml | kubectl apply -f -
  
deploy-dev:
  <<: *deploy_template
  environment:
    name: dev
    url: https://dev.example.com
  only:
    - main
    - /^feature\/.*$/

deploy-staging:
  <<: *deploy_template
  environment:
    name: staging
    url: https://staging.example.com
  only:
    - main
  when: manual

security-scan:
  stage: security-scan
  script:
    - docker run --rm -v $(pwd):/app security-scanner:latest /app
  only:
    - main
  allow_failure: false

deploy-production:
  <<: *deploy_template
  environment:
    name: production
    url: https://example.com
  only:
    - main
  when: manual
  before_script:
    - echo "Deploying to production requires manager approval"
    - slack-notify "Production deployment requested for $CI_COMMIT_SHA"
```

## 6. Workflow Migration Strategies

### 6.1 Da Git Flow a GitHub Flow

```bash
#!/bin/bash
# migrate-to-github-flow.sh

echo "🔄 Migrating from Git Flow to GitHub Flow"

# 1. Merge tutto in main
git checkout main
git merge develop

# 2. Elimina branch non necessari
git branch -d develop
git push origin --delete develop

# 3. Converti feature branch esistenti
for branch in $(git branch -r | grep "feature/" | cut -d'/' -f2-); do
  echo "Converting $branch to GitHub Flow style"
  git checkout "$branch"
  git rebase main
done

# 4. Setup nuovo workflow
cat > .github/workflows/github-flow.yml << 'EOF'
name: GitHub Flow
on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]
jobs:
  ci-cd:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Test and Deploy
      run: |
        npm test
        if [ "${{ github.ref }}" == "refs/heads/main" ]; then
          npm run deploy
        fi
EOF

echo "✅ Migration completed!"
```

### 6.2 Migration Checklist

```markdown
# Migration Checklist

## Pre-Migration
- [ ] Documenta workflow attuale
- [ ] Identifica branch attivi
- [ ] Backup del repository
- [ ] Notifica team del cambio
- [ ] Prepara training materiale

## During Migration
- [ ] Merge pending PR
- [ ] Update CI/CD pipelines
- [ ] Migrate branch protection rules
- [ ] Update documentation
- [ ] Test new workflow

## Post-Migration
- [ ] Training team sul nuovo workflow
- [ ] Monitor primi giorni
- [ ] Collect feedback
- [ ] Adjust processo se necessario
- [ ] Update repository settings
```

## 7. Monitoring e Metriche

### 7.1 Workflow Health Metrics

```javascript
// workflow-analytics.js
class WorkflowAnalytics {
  constructor(repository) {
    this.repo = repository;
    this.metrics = {};
  }

  async calculateMetrics() {
    return {
      // Lead Time: tempo da feature start a deployment
      leadTime: await this.calculateLeadTime(),
      
      // Deployment Frequency
      deploymentFrequency: await this.calculateDeploymentFrequency(),
      
      // Mean Time to Recovery (MTTR)
      mttr: await this.calculateMTTR(),
      
      // Change Failure Rate
      changeFailureRate: await this.calculateChangeFailureRate(),
      
      // Branch Health
      branchHealth: await this.calculateBranchHealth()
    };
  }

  async calculateLeadTime() {
    const pullRequests = await this.repo.getPullRequests();
    const leadTimes = pullRequests.map(pr => {
      const created = new Date(pr.created_at);
      const merged = new Date(pr.merged_at);
      return merged - created;
    });
    
    return {
      average: leadTimes.reduce((a, b) => a + b, 0) / leadTimes.length,
      median: this.median(leadTimes),
      p95: this.percentile(leadTimes, 95)
    };
  }

  async calculateDeploymentFrequency() {
    const deployments = await this.repo.getDeployments();
    const now = new Date();
    const thirtyDaysAgo = new Date(now - 30 * 24 * 60 * 60 * 1000);
    
    const recentDeployments = deployments.filter(
      d => new Date(d.created_at) > thirtyDaysAgo
    );
    
    return {
      deploymentsPerDay: recentDeployments.length / 30,
      totalDeployments: recentDeployments.length
    };
  }

  generateReport() {
    return `
📊 Workflow Analytics Report
=============================

Lead Time:
  Average: ${this.metrics.leadTime.average / (1000 * 60 * 60)} hours
  Median: ${this.metrics.leadTime.median / (1000 * 60 * 60)} hours

Deployment Frequency:
  ${this.metrics.deploymentFrequency.deploymentsPerDay.toFixed(2)} deploys/day

MTTR:
  ${this.metrics.mttr / (1000 * 60)} minutes

Change Failure Rate:
  ${(this.metrics.changeFailureRate * 100).toFixed(1)}%
`;
  }
}
```

## 8. Best Practices per Workflow Selection

### 8.1 Team Assessment Framework

```yaml
# team-assessment.yml
team_assessment:
  size:
    small: 1-5 developers
    medium: 6-15 developers  
    large: 16+ developers
    
  experience_level:
    junior: 0-2 years
    mid: 2-5 years
    senior: 5+ years
    
  deployment_maturity:
    manual: Manual deployment process
    semi_automated: Some automation
    fully_automated: Complete CI/CD pipeline
    
  release_schedule:
    continuous: Deploy when ready
    sprint: Every 1-2 weeks
    scheduled: Monthly/quarterly
    
  stability_requirements:
    high: Financial/medical software
    medium: Business applications
    low: Internal tools/prototypes

workflow_recommendations:
  git_flow:
    conditions:
      - team.size >= medium
      - release_schedule == scheduled
      - stability_requirements == high
      
  github_flow:
    conditions:
      - deployment_maturity == fully_automated
      - release_schedule == continuous
      
  gitlab_flow:
    conditions:
      - team.size >= medium
      - deployment_maturity >= semi_automated
      
  oneflow:
    conditions:
      - default option for balanced requirements
```

### 8.2 Implementation Guidelines

```bash
#!/bin/bash
# workflow-setup.sh

setup_workflow() {
  local workflow=$1
  local project_root=$2
  
  cd "$project_root"
  
  case $workflow in
    "git-flow")
      setup_git_flow
      ;;
    "github-flow")
      setup_github_flow
      ;;
    "gitlab-flow")
      setup_gitlab_flow
      ;;
    "oneflow")
      setup_oneflow
      ;;
    *)
      echo "❌ Unknown workflow: $workflow"
      exit 1
      ;;
  esac
}

setup_git_flow() {
  git flow init -d
  create_git_flow_hooks
  setup_git_flow_ci
  echo "✅ Git Flow configured"
}

setup_github_flow() {
  setup_branch_protection
  create_github_templates
  setup_github_actions
  echo "✅ GitHub Flow configured"
}

create_github_templates() {
  mkdir -p .github/pull_request_template
  cat > .github/pull_request_template.md << 'EOF'
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Tests added/updated
- [ ] All tests passing
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
EOF
}
```

## Quiz di Verifica

### Domanda 1
Quale workflow è più adatto per continuous deployment?
- a) Git Flow
- b) GitHub Flow
- c) OneFlow
- d) SVN Flow

### Domanda 2
GitLab Flow introduce principalmente:
- a) Feature flags
- b) Environment branches
- c) Release cycles
- d) Hotfix automation

### Domanda 3
OneFlow elimina rispetto a Git Flow:
- a) Il branch main
- b) Il branch develop
- c) I feature branch
- d) I release branch

### Domanda 4
Quale metrica è più importante per GitHub Flow?
- a) Lead time
- b) Branch coverage
- c) Code quality
- d) Documentation

### Domanda 5
La scelta del workflow dipende principalmente da:
- a) Strumenti disponibili
- b) Esperienza del team
- c) Contesto del progetto
- d) Linguaggio di programmazione

## Esercizi Pratici

### Esercizio 1: Workflow Comparison
Implementa tutti e 4 i workflow in repository separati:
1. Setup Git Flow completo
2. Implementa GitHub Flow con automation
3. Configura GitLab Flow con environment branches
4. Crea OneFlow personalizzato

### Esercizio 2: Migration Simulation
Simula migrazione da Git Flow a GitHub Flow:
1. Crea repository con Git Flow
2. Sviluppa alcune feature
3. Pianifica strategia di migrazione
4. Esegui migrazione
5. Valida nuovo workflow

### Esercizio 3: Custom Workflow Design
Progetta workflow personalizzato per scenario specifico:
1. Analizza requirements del progetto
2. Identifica vincoli e necessità
3. Progetta workflow ibrido
4. Implementa automation
5. Testa e itera

---

## Navigazione

⬅️ **Precedente**: [01 - Git Flow Fundamentals](01-gitflow-fundamentals.md)

➡️ **Successivo**: [03 - Advanced Workflow Automation](03-advanced-workflow-automation.md)

🏠 **Home**: [Indice Generale](../../README.md)
