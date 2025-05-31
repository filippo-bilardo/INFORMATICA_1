# Guida: Team Setup e Configurazione Collaborazione

## Introduzione

La configurazione iniziale di un team è cruciale per garantire un flusso di lavoro collaborativo efficace. Questa guida copre tutti gli aspetti essenziali per impostare un ambiente di collaborazione ottimale su GitHub.

## Configurazione Repository Team

### 1. Creazione del Repository

```bash
# Creare un nuovo repository per il team
git init team-project
cd team-project

# Configurazione iniziale
git config user.name "Team Lead"
git config user.email "teamlead@company.com"

# Setup branch principale
echo "# Team Project" > README.md
git add README.md
git commit -m "feat: initial project setup"
```

### 2. Setup GitHub Repository

```bash
# Collegare al repository remoto
git remote add origin https://github.com/teamname/team-project.git
git branch -M main
git push -u origin main
```

## Gestione Collaboratori

### 1. Invitare Collaboratori

**Via GitHub Web Interface:**
1. Repository → Settings → Manage access
2. Invite a collaborator
3. Inserire username/email
4. Selezionare level di accesso

**Permission Levels:**
- **Read**: Può clonare e leggere il repository
- **Triage**: Read + può gestire issues e PR
- **Write**: Triage + può pushare direttamente
- **Maintain**: Write + può gestire alcune impostazioni
- **Admin**: Full access al repository

### 2. Setup Team Organization

```bash
# Creare team in organization
# Via GitHub: Organization → Teams → New team

# Assegnare repository ai team
# Teams → Repositories → Add repository
```

## Configurazione Branch Protection

### 1. Proteggere Branch Principale

```yaml
# Settings → Branches → Add rule
Branch name pattern: main
Protections:
  - Require pull request reviews before merging
  - Require status checks to pass before merging
  - Restrict pushes to specific teams/users
  - Include administrators
```

### 2. Setup Branch Policies

```bash
# Configurare branch di sviluppo
git checkout -b develop
git push -u origin develop

# Impostare develop come branch di default per PR
# Settings → General → Default branch
```

## Struttura Workflow Team

### 1. Git Flow per Team

```bash
# Branch structure
main         # Production-ready code
develop      # Integration branch
feature/*    # Feature development
hotfix/*     # Emergency fixes
release/*    # Release preparation
```

### 2. Naming Conventions

```bash
# Branch naming
feature/user-authentication
feature/payment-integration
bugfix/login-error
hotfix/security-patch

# Commit message format
type(scope): description

# Examples:
feat(auth): add user login functionality
fix(ui): resolve button alignment issue
docs(readme): update installation instructions
```

## Configurazione Ambiente Locale

### 1. Setup per Tutti i Team Members

```bash
# Clone del repository
git clone https://github.com/teamname/team-project.git
cd team-project

# Configurazione user locale
git config user.name "Your Name"
git config user.email "your.email@company.com"

# Setup remote tracking
git fetch origin
git checkout develop
git checkout -b feature/your-feature
```

### 2. Configurazione Aliases Utili

```bash
# Aliases per collaboration
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual '!gitk'

# Aliases specifici per team workflow
git config --global alias.sync '!git checkout develop && git pull origin develop'
git config --global alias.feature '!git checkout develop && git pull origin develop && git checkout -b'
```

## Templates e Standard

### 1. Issue Templates

```markdown
<!-- .github/ISSUE_TEMPLATE/bug_report.md -->
---
name: Bug report
about: Create a report to help us improve
title: '[BUG] '
labels: 'bug'
assignees: ''
---

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Expected behavior**
A clear and concise description of what you expected to happen.

**Additional context**
Add any other context about the problem here.
```

### 2. Pull Request Template

```markdown
<!-- .github/pull_request_template.md -->
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No breaking changes
```

## Comunicazione e Coordinamento

### 1. Canali di Comunicazione

```bash
# Setup communication channels
- GitHub Discussions per topic generali
- Issues per bug e feature requests
- PR comments per code review
- Wiki per documentazione team
```

### 2. Meeting e Sync Points

```yaml
Daily Standup:
  - What did you do yesterday?
  - What will you do today?
  - Any blockers?

Weekly Planning:
  - Review completed work
  - Plan next sprint
  - Address team issues

Code Review Process:
  - All PR require at least 1 approval
  - Reviewer assignment rotation
  - Review checklist compliance
```

## Monitoraggio e Metriche

### 1. Repository Insights

```bash
# GitHub Insights monitoring
- Contributor activity
- Commit frequency
- PR merge times
- Issue resolution rates
```

### 2. Team Performance Tracking

```yaml
Metrics to Track:
  - Code review turnaround time
  - Bug resolution time
  - Feature delivery rate
  - Team velocity
  - Code quality metrics
```

## Errori Comuni e Soluzioni

### 1. Problemi di Permission

```bash
# Errore: Permission denied
# Soluzione: Verificare access level e SSH keys
git remote set-url origin git@github.com:username/repo.git
ssh -T git@github.com

# Verificare collaborator status
# GitHub: Repository → Settings → Manage access
```

### 2. Conflitti di Configurazione

```bash
# Diversi stili di line ending
git config --global core.autocrlf true  # Windows
git config --global core.autocrlf input # Mac/Linux

# Unificare configurazione team
echo "* text=auto" > .gitattributes
git add .gitattributes
git commit -m "config: standardize line endings"
```

## Best Practices

### 1. Repository Management

- **Mantenere repository puliti**: Rimuovere branch merged
- **Utilizzare .gitignore appropriati**: Per ogni tecnologia
- **Documentazione aggiornata**: README, CONTRIBUTING, CHANGELOG
- **Tagging releases**: Semantic versioning per releases

### 2. Team Workflow

- **Comunicazione proattiva**: Informare team su modifiche importanti
- **Code review approfonditi**: Non solo syntax, ma anche design
- **Testing requirement**: Test per ogni nuova feature
- **Documentazione inline**: Commenti e docstrings appropriati

## Quiz di Verifica

### Domande

1. **Quali sono i principali permission levels in GitHub e le loro differenze?**

2. **Come si configura branch protection per il branch main?**

3. **Qual è la differenza tra organization teams e repository collaborators?**

4. **Come si imposta un workflow GitFlow per un team?**

5. **Quali sono gli elementi essenziali di un PR template?**

### Risposte

1. **Permission Levels**: Read (clone/view), Triage (+issues), Write (+push), Maintain (+settings), Admin (full control)

2. **Branch Protection**: Settings → Branches → Add rule, enable PR reviews, status checks, push restrictions

3. **Teams vs Collaborators**: Teams sono groupings in organizations per gestire permissions multiple repos, collaborators sono individuals con access a specific repo

4. **GitFlow Setup**: main (production), develop (integration), feature/* (development), hotfix/* (emergency), release/* (preparation)

5. **PR Template Elements**: Description, change type, testing checklist, review checklist, documentation updates

## Esercizi Pratici

### Esercizio 1: Setup Team Repository

```bash
# Obiettivo: Configurare un repository per team di 3 persone

# Step 1: Creare repository
git init collaboration-practice
cd collaboration-practice

# Step 2: Setup iniziale
echo "# Team Collaboration Practice" > README.md
mkdir docs src tests
echo "Project documentation" > docs/README.md
echo "Source code" > src/README.md
echo "Test files" > tests/README.md

# Step 3: Commit iniziale
git add .
git commit -m "feat: initial project structure"

# Step 4: Setup GitHub e inviti
# 1. Push to GitHub
# 2. Invite 2 collaborators with Write access
# 3. Setup branch protection on main
```

### Esercizio 2: Configurazione Templates

```bash
# Obiettivo: Setup issue e PR templates

# Step 1: Creare directory templates
mkdir -p .github/ISSUE_TEMPLATE

# Step 2: Creare bug report template
# [Implementare template bug_report.md]

# Step 3: Creare feature request template
# [Implementare template feature_request.md]

# Step 4: Creare PR template
# [Implementare template pull_request_template.md]

# Step 5: Test templates
# 1. Creare issue utilizzando template
# 2. Creare PR utilizzando template
```

## Risorse Aggiuntive

### Documentazione Ufficiale
- [GitHub Team Management](https://docs.github.com/en/organizations/organizing-members-into-teams)
- [Repository Permission Levels](https://docs.github.com/en/organizations/managing-access-to-your-organizations-repositories/repository-permission-levels-for-an-organization)
- [Branch Protection Rules](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/defining-the-mergeability-of-pull-requests/about-protected-branches)

### Tools Utili
- GitHub CLI per automazione
- GitKraken per visualizzazione team
- Jira/Asana per project management integration

---

[⬅️ Indice](../README.md) | [➡️ Workflow Collaborativo](./02-workflow-collaborativo.md)
