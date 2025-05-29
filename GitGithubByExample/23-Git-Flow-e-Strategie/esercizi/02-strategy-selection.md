# Esercizio 2: Selezione e Confronto Strategie di Branching

## Obiettivo
Analizzare e confrontare diverse strategie di branching (Git Flow, GitHub Flow, GitLab Flow, e One Flow) implementando lo stesso scenario di sviluppo con ognuna per comprendere vantaggi, svantaggi e casi d'uso appropriati.

## Scenario Base
Il team deve sviluppare "TaskMaster", un'applicazione di project management con i seguenti requisiti:
- **3 developers** di diversa seniority
- **Release every 2 weeks** 
- **Multiple environments**: dev, staging, production
- **Hotfix support** necessario
- **Feature flags** possibili
- **Mobile app** development parallelo

## Parte 1: Implementazione GitHub Flow

### 1.1 Setup GitHub Flow
```bash
# Crea repository taskmaster-github-flow
git init taskmaster-github-flow
cd taskmaster-github-flow

# Struttura semplice - solo main branch
git checkout -b main
echo "# TaskMaster - GitHub Flow Implementation" > README.md
git add README.md
git commit -m "Initial commit - GitHub Flow setup"

# Setup project structure
mkdir -p src/{components,pages,services} docs tests
touch src/app.js package.json .gitignore
```

**Caratteristiche GitHub Flow:**
- **Solo main branch** è permanente
- **Feature branches** create da main
- **Pull requests** per ogni change
- **Deploy da main** sempre

### 1.2 Feature Development con GitHub Flow

**Feature 1: Task Creation**
```bash
# Crea feature branch da main
git checkout main
git pull origin main
git checkout -b add-task-creation

# Sviluppa feature
echo "// Task creation component" > src/components/TaskForm.js
echo "// Task service for API calls" > src/services/taskService.js

git add .
git commit -m "feat: implement task creation functionality

- Add TaskForm component with validation
- Add taskService for API integration
- Add form styling and error handling
- Add tests for task creation flow

Closes #12"

# Push e crea PR
git push origin add-task-creation
# Crea PR: add-task-creation → main
```

**Feature 2: Task List Display**
```bash
# Altro developer lavora in parallelo
git checkout main
git pull origin main
git checkout -b task-list-display

# Sviluppa feature...
git add .
git commit -m "feat: implement task list with filtering

- Add TaskList component with responsive design
- Add filtering by status and priority
- Add pagination for large task lists
- Add sorting functionality
- Add tests for task list operations

Closes #13"

git push origin task-list-display
# Crea PR: task-list-display → main
```

**Processo di Review e Merge:**
```bash
# Code review via PR
# Dopo approval, merge con "Squash and merge"
# Delete feature branch
# Deploy automatico da main
```

### 1.3 Hotfix con GitHub Flow
```bash
# Bug critico in produzione
git checkout main
git pull origin main
git checkout -b hotfix-task-deletion-bug

# Fix veloce
echo "// Fixed task deletion logic" >> src/services/taskService.js
git add .
git commit -m "fix: resolve task deletion race condition

Critical bug where rapid clicks on delete button
caused multiple deletion requests and UI inconsistency.

- Add debounce to delete button
- Add optimistic UI updates
- Add proper error handling for failed deletions

Fixes #45"

# PR urgente
git push origin hotfix-task-deletion-bug
# Immediate review e merge
# Deploy automatico
```

**Vantaggi GitHub Flow:**
- ✅ Semplicità estrema
- ✅ Deploy continuo possibile
- ✅ Meno overhead di branching
- ✅ Feedback rapido

**Svantaggi GitHub Flow:**
- ❌ Difficile gestire release programmate
- ❌ Testing pre-produzione limitato
- ❌ Rollback complessi
- ❌ Coordinazione team difficile per progetti grandi

## Parte 2: Implementazione GitLab Flow

### 2.1 Setup GitLab Flow con Environment Branches
```bash
# Crea repository taskmaster-gitlab-flow
git init taskmaster-gitlab-flow
cd taskmaster-gitlab-flow

# Setup branches per ambienti
git checkout -b main
echo "# TaskMaster - GitLab Flow Implementation" > README.md
git add README.md
git commit -m "Initial commit - GitLab Flow setup"

# Crea environment branches
git checkout -b development
git push origin development

git checkout -b staging  
git push origin staging

git checkout -b production
git push origin production

# Main branch per upstream integration
git push origin main
```

**GitLab Flow Structure:**
```
main (upstream)
├── development (continuous deployment)
├── staging (release candidate testing)
└── production (stable releases)
```

### 2.2 Feature Development con GitLab Flow

**Feature Development:**
```bash
# Feature development da main
git checkout main
git pull origin main
git checkout -b feature/user-authentication

# Sviluppa feature...
echo "// Authentication service" > src/services/authService.js
git add .
git commit -m "feat: implement JWT authentication

- Add login/logout functionality
- Add JWT token management
- Add protected route middleware
- Add user session persistence

Closes #20"

# Merge request: feature/user-authentication → main
git push origin feature/user-authentication
```

**Deployment Pipeline:**
```bash
# Dopo merge in main, promuovi negli ambienti
# 1. main → development (automatico)
git checkout development
git merge main
git push origin development
# Deploy automatico su dev environment

# 2. development → staging (quando pronto)
git checkout staging
git merge development
git push origin staging
# Deploy su staging per QA testing

# 3. staging → production (dopo validation)
git checkout production
git merge staging
git push origin production
# Deploy in produzione
```

### 2.3 Release Features con GitLab Flow

**Release Branch Strategy:**
```bash
# Per release major, usa release branch
git checkout main
git checkout -b release/v2.0.0

# Cherry-pick feature specifiche per release
git cherry-pick feature-commit-1
git cherry-pick feature-commit-2

# Stabilizza release
git add .
git commit -m "release: prepare v2.0.0

- Include user authentication
- Include advanced task management
- Update documentation
- Bump version to 2.0.0"

# Test e deploy attraverso pipeline
git push origin release/v2.0.0
# release/v2.0.0 → staging → production
```

**Vantaggi GitLab Flow:**
- ✅ Environment parity
- ✅ Controlled deployments
- ✅ Easy rollbacks
- ✅ Continuous deployment per environment

**Svantaggi GitLab Flow:**
- ❌ Più complessità di GitHub Flow  
- ❌ Merge conflicts tra environment
- ❌ Overhead di maintenance per multiple branch

## Parte 3: Implementazione One Flow

### 3.1 Setup One Flow
```bash
# Crea repository taskmaster-one-flow
git init taskmaster-one-flow
cd taskmaster-one-flow

# Setup con solo main branch + release tags
git checkout -b main
echo "# TaskMaster - One Flow Implementation" > README.md
git add README.md
git commit -m "Initial commit - One Flow setup"

# No development branch permanenti
# Solo feature branches temporanee
```

**One Flow Principles:**
- **Solo main branch** permanente
- **Feature branches** temporanee da main
- **Release tags** invece di release branches  
- **Rebase invece di merge** per clean history

### 3.2 Feature Development con One Flow

**Feature con Rebase Workflow:**
```bash
# Feature development
git checkout main
git pull origin main
git checkout -b feature/task-comments

# Sviluppa feature in multiple commit
echo "// Comment model" > src/models/Comment.js
git add .
git commit -m "add comment data model"

echo "// Comment API endpoints" > src/api/comments.js
git add .
git commit -m "add comment API endpoints"

echo "// Comment UI component" > src/components/CommentForm.js
git add .
git commit -m "add comment form component"

# Prima di merge, rebase per clean history
git checkout main
git pull origin main
git checkout feature/task-comments
git rebase main

# Squash commit se necessario
git rebase -i HEAD~3
# Combina i 3 commit in uno

# Result: single clean commit
# "feat: implement task comments system"

# Merge con fast-forward
git checkout main
git merge feature/task-comments  # Fast-forward merge
git branch -d feature/task-comments
git push origin main
```

### 3.3 Release Management con One Flow

**Release Tagging:**
```bash
# Quando pronto per release
git checkout main
git pull origin main

# Update version
npm version 1.2.0 --no-git-tag-version
git add package.json
git commit -m "bump version to 1.2.0"

# Create release tag
git tag -a v1.2.0 -m "Release v1.2.0

New Features:
- Task comments system
- Advanced filtering
- Mobile responsive design

Bug Fixes:
- Fixed task deletion issue
- Improved performance
- Fixed mobile layout bugs"

git push origin main --tags

# Deploy from tag
# Deploy v1.2.0 to production
```

**Hotfix con One Flow:**
```bash
# Hotfix da main
git checkout main
git pull origin main
git checkout -b hotfix/critical-security-fix

# Single commit fix
echo "// Security fix" >> src/utils/security.js
git add .
git commit -m "security: fix XSS vulnerability in task titles

Critical security fix for XSS vulnerability that allowed
script injection through task title fields.

- Add input sanitization
- Add CSP headers
- Add HTML encoding for user content

CVE-2024-0123"

# Rebase e merge
git checkout main
git merge hotfix/critical-security-fix
git branch -d hotfix/critical-security-fix

# Immediate release
git tag -a v1.2.1 -m "Hotfix v1.2.1 - Security fix"
git push origin main --tags
```

**Vantaggi One Flow:**
- ✅ Historia pulita e lineare
- ✅ Semplicità massima
- ✅ No merge commits
- ✅ Easy to follow history

**Svantaggi One Flow:**
- ❌ Rebase può essere intimidatorio per beginners
- ❌ Perdita di feature branch context
- ❌ Difficile recovery se rebase va male
- ❌ No parallel release preparation

## Parte 4: Comparison Matrix e Decision Framework

### 4.1 Comparison Matrix

| Criteria | GitHub Flow | Git Flow | GitLab Flow | One Flow |
|----------|-------------|----------|-------------|----------|
| **Complexity** | ⭐ Very Simple | ⭐⭐⭐⭐⭐ Complex | ⭐⭐⭐ Moderate | ⭐⭐ Simple |
| **Learning Curve** | ⭐ Easy | ⭐⭐⭐⭐ Hard | ⭐⭐⭐ Moderate | ⭐⭐⭐ Moderate |
| **Release Management** | ⭐⭐ Limited | ⭐⭐⭐⭐⭐ Excellent | ⭐⭐⭐⭐ Good | ⭐⭐⭐ Good |
| **Hotfix Support** | ⭐⭐⭐ Okay | ⭐⭐⭐⭐⭐ Excellent | ⭐⭐⭐⭐ Good | ⭐⭐⭐ Good |
| **Continuous Deployment** | ⭐⭐⭐⭐⭐ Perfect | ⭐⭐ Limited | ⭐⭐⭐⭐ Good | ⭐⭐⭐⭐ Good |
| **Team Coordination** | ⭐⭐ Basic | ⭐⭐⭐⭐⭐ Excellent | ⭐⭐⭐⭐ Good | ⭐⭐ Basic |
| **History Clarity** | ⭐⭐⭐ Good | ⭐⭐⭐ Good | ⭐⭐⭐ Good | ⭐⭐⭐⭐⭐ Excellent |
| **Rollback Ease** | ⭐⭐ Difficult | ⭐⭐⭐⭐ Easy | ⭐⭐⭐⭐⭐ Excellent | ⭐⭐⭐ Good |
| **Multiple Versions** | ⭐ Poor | ⭐⭐⭐⭐⭐ Excellent | ⭐⭐⭐⭐ Good | ⭐⭐ Limited |

### 4.2 Team Size Recommendations

**Small Team (2-5 developers):**
```markdown
## Recommended: GitHub Flow or One Flow

### GitHub Flow for:
- Web applications with continuous deployment
- MVP development and startups
- Teams comfortable with trunk-based development
- Projects with simple release cycles

### One Flow for:
- Teams that want clean history
- Projects where rebase knowledge exists
- Applications with tagged releases
- Teams that prioritize simplicity over collaboration features
```

**Medium Team (6-15 developers):**
```markdown
## Recommended: GitLab Flow or Light Git Flow

### GitLab Flow for:
- Teams with multiple environments
- Organizations requiring staged deployments
- Projects with complex testing requirements
- Teams wanting balance between simplicity and control

### Light Git Flow for:
- Projects with regular release cycles
- Teams needing feature isolation
- Applications requiring hotfix capabilities
- Organizations with established release processes
```

**Large Team (15+ developers):**
```markdown
## Recommended: Git Flow or Modified GitLab Flow

### Git Flow for:
- Enterprise applications with formal release cycles
- Teams with dedicated release management
- Projects requiring multiple concurrent releases
- Organizations with complex branching requirements

### Modified GitLab Flow for:
- Microservices architectures
- Teams preferring lighter process than Git Flow
- Organizations with strong CI/CD pipelines
- Projects with environment-specific configurations
```

### 4.3 Project Type Decision Tree

**Decision Framework:**
```markdown
1. **What's your deployment frequency?**
   - Multiple times daily → GitHub Flow
   - Weekly → GitLab Flow or One Flow
   - Bi-weekly → Git Flow or GitLab Flow
   - Monthly+ → Git Flow

2. **How many environments do you manage?**
   - 1 (production only) → GitHub Flow or One Flow
   - 2-3 (dev, staging, prod) → GitLab Flow
   - 3+ (multiple staging, prod variants) → Git Flow

3. **How experienced is your team with Git?**
   - Beginners → GitHub Flow
   - Intermediate → GitLab Flow or One Flow
   - Advanced → Git Flow or One Flow

4. **Do you need to support multiple versions?**
   - No → GitHub Flow or One Flow
   - Yes, limited → GitLab Flow
   - Yes, complex → Git Flow

5. **How critical are hotfixes?**
   - Rare/simple → GitHub Flow
   - Occasional → GitLab Flow or One Flow
   - Frequent/complex → Git Flow
```

## Parte 5: Implementation Recommendations

### 5.1 Migration Strategy

**From Simple to Complex:**
```bash
# Phase 1: Start with GitHub Flow
# - Train team on basic PR workflow
# - Establish CI/CD pipeline
# - Build deployment confidence

# Phase 2: Add Environment Management (GitLab Flow)
# - Add staging environment
# - Implement environment-specific testing
# - Add release candidate process

# Phase 3: Add Release Management (Git Flow)
# - Add formal release branches
# - Implement version management
# - Add hotfix procedures
```

### 5.2 Tooling Configuration

**GitHub Actions for All Strategies:**
```yaml
name: Multi-Strategy CI/CD

on:
  push:
    branches: [main, develop, staging, production]
    tags: ['v*']
  pull_request:
    branches: [main, develop]

jobs:
  # GitHub Flow - deploy on main push
  github-flow-deploy:
    if: github.ref == 'refs/heads/main' && !contains(github.repository, 'git-flow')
    runs-on: ubuntu-latest
    steps:
      - name: Deploy to production
        run: echo "GitHub Flow deployment"

  # GitLab Flow - environment-specific deployments
  gitlab-flow-deploy:
    if: contains(github.repository, 'gitlab-flow')
    runs-on: ubuntu-latest
    strategy:
      matrix:
        environment: [development, staging, production]
    steps:
      - name: Deploy to ${{ matrix.environment }}
        run: echo "GitLab Flow deployment to ${{ matrix.environment }}"

  # Git Flow - branch-specific actions
  git-flow-release:
    if: startsWith(github.ref, 'refs/heads/release/')
    runs-on: ubuntu-latest
    steps:
      - name: Release preparation
        run: echo "Git Flow release preparation"

  # One Flow - tag-based deployment
  one-flow-deploy:
    if: startsWith(github.ref, 'refs/tags/v') && contains(github.repository, 'one-flow')
    runs-on: ubuntu-latest
    steps:
      - name: Tag-based deployment
        run: echo "One Flow tag deployment"
```

## Deliverables dell'Esercizio

### Cosa Consegnare:

1. **4 Repository Implementati**:
   - `taskmaster-github-flow`
   - `taskmaster-git-flow` (dall'esercizio precedente)
   - `taskmaster-gitlab-flow`
   - `taskmaster-one-flow`

2. **Comparison Report** contenente:
   - Detailed analysis di ogni strategia
   - Team experience notes durante l'implementazione
   - Performance metrics (tempo di feature delivery, bugs, etc.)
   - Recommendation matrix per diversi scenari

3. **Decision Framework Document**:
   - Team size recommendations
   - Project type decision tree
   - Migration strategies
   - Tooling configurations

4. **Presentation Deck** (15-20 slides):
   - Overview di ogni strategia
   - Live demo delle differenze
   - Real-world case studies
   - Q&A preparazione

### Criteri di Valutazione:

- **Implementation Quality** (30%): Correct implementation of each strategy
- **Analysis Depth** (25%): Understanding of pros/cons and use cases
- **Decision Framework** (20%): Practical applicability of recommendations
- **Documentation** (15%): Clarity and completeness of reports
- **Presentation** (10%): Ability to communicate findings effectively

### Bonus Points:
- Implementation of hybrid approaches
- Custom workflow adaptations
- Tool integrations beyond basic CI/CD
- Real team feedback from strategy testing

Questo esercizio fornisce comprensione pratica delle trade-off tra diverse strategie, preparando gli studenti a prendere decisioni architetturali informate in contesti professionali diversi.
