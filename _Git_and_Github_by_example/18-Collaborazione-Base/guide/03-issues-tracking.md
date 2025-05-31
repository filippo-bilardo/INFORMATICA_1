# 03 - Issues e Tracking

## 🎯 Obiettivi del Modulo

In questa guida imparerai:
- Come utilizzare GitHub Issues per project tracking
- Strategie di organizzazione delle issues
- Tecniche di comunicazione attraverso issues
- Best practices per il tracciamento del lavoro di team

## 📖 Spiegazione Concettuale

La gestione efficace di issues e progetti è fondamentale per il successo di qualsiasi team di sviluppo. GitHub fornisce strumenti potenti per organizzare, tracciare e coordinare il lavoro del team attraverso issues, project boards e milestone.

## Gestione Issues

### 1. Anatomia di una Issue

```markdown
# Struttura Issue Efficace
Title: [TYPE] Brief descriptive title
Labels: bug, enhancement, documentation
Assignees: team-member
Milestone: v1.2.0
Projects: Team Sprint Board

Body:
## Description
Clear description of the issue

## Acceptance Criteria
- [ ] Criterion 1
- [ ] Criterion 2
- [ ] Criterion 3

## Additional Context
Screenshots, logs, references
```

### 2. Tipi di Issues

```bash
# Bug Report
Title: [BUG] Login fails with valid credentials
Labels: bug, priority-high, backend

# Feature Request
Title: [FEATURE] Add user profile picture upload
Labels: enhancement, frontend, user-experience

# Task/Chore
Title: [TASK] Update dependencies to latest versions
Labels: maintenance, technical-debt

# Documentation
Title: [DOCS] Add API documentation for authentication
Labels: documentation, api
```

### 3. Lifecycle delle Issues

```yaml
States:
  Open: Initial state
  In Progress: Work started
  Review: Under review/testing
  Closed: Completed or rejected

Transitions:
  Open → In Progress: Assign and start work
  In Progress → Review: Submit for review
  Review → Closed: Approved and merged
  Review → In Progress: Feedback to address
  Open → Closed: Duplicate/invalid/wontfix
```

## Sistema di Labels

### 1. Categories di Labels

```yaml
Type Labels:
  - bug: Something isn't working
  - enhancement: New feature or request
  - documentation: Improvements or additions
  - question: Further information is requested
  - duplicate: This issue already exists
  - wontfix: This will not be worked on

Priority Labels:
  - priority-critical: Blocking production
  - priority-high: Important for next release
  - priority-medium: Normal priority
  - priority-low: Nice to have

Component Labels:
  - frontend: Client-side code
  - backend: Server-side code
  - database: Database related
  - api: API related
  - ui/ux: User interface/experience

Status Labels:
  - status-blocked: Cannot proceed
  - status-in-progress: Currently being worked on
  - status-needs-review: Ready for review
  - status-waiting: Waiting for external input
```

### 2. Setup Label Schema

```bash
# Creare label set standard
# Via GitHub CLI
gh label create "priority-critical" --color "d73a4a" --description "Blocking production"
gh label create "priority-high" --color "ff6b6b" --description "Important for next release"
gh label create "priority-medium" --color "ffa726" --description "Normal priority"
gh label create "priority-low" --color "81c784" --description "Nice to have"

# Bulk label creation script
labels=(
  "bug,d73a4a,Something isn't working"
  "enhancement,a2eeef,New feature or request"
  "frontend,e1f5fe,Client-side code"
  "backend,3f51b5,Server-side code"
)

for label in "${labels[@]}"; do
  IFS=',' read -r name color description <<< "$label"
  gh label create "$name" --color "$color" --description "$description"
done
```

## Templates per Issues

### 1. Bug Report Template

```markdown
<!-- .github/ISSUE_TEMPLATE/bug_report.md -->
---
name: Bug report
about: Create a report to help us improve
title: '[BUG] '
labels: 'bug'
assignees: ''
---

## Bug Description
A clear and concise description of what the bug is.

## Steps to Reproduce
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

## Expected Behavior
A clear and concise description of what you expected to happen.

## Actual Behavior
What actually happened instead.

## Screenshots
If applicable, add screenshots to help explain your problem.

## Environment
- OS: [e.g. Windows 10, macOS Big Sur, Ubuntu 20.04]
- Browser: [e.g. chrome, safari] (if web-related)
- Version: [e.g. 22]

## Additional Context
Add any other context about the problem here.

## Possible Solution
If you have a suggestion for a fix, please describe it here.
```

### 2. Feature Request Template

```markdown
<!-- .github/ISSUE_TEMPLATE/feature_request.md -->
---
name: Feature request
about: Suggest an idea for this project
title: '[FEATURE] '
labels: 'enhancement'
assignees: ''
---

## Is your feature request related to a problem?
A clear and concise description of what the problem is.
Ex. I'm always frustrated when [...]

## Describe the solution you'd like
A clear and concise description of what you want to happen.

## Describe alternatives you've considered
A clear and concise description of any alternative solutions or features you've considered.

## User Stories
As a [type of user], I want [some goal] so that [some reason].

## Acceptance Criteria
- [ ] Criterion 1
- [ ] Criterion 2
- [ ] Criterion 3

## Additional context
Add any other context or screenshots about the feature request here.

## Priority
- [ ] Critical
- [ ] High
- [ ] Medium
- [ ] Low
```

## Project Boards e Kanban

### 1. Setup Project Board

```yaml
# Creare nuovo project
Repository → Projects → New project

Board Structure:
  - Backlog: Issues non prioritized
  - To Do: Ready for development
  - In Progress: Currently being worked
  - Review: Awaiting review/testing
  - Done: Completed

Automation Rules:
  - Auto-move new issues to Backlog
  - Move to "In Progress" when assigned
  - Move to "Review" when PR opened
  - Move to "Done" when PR merged
```

### 2. Advanced Project Management

```yaml
# GitHub Projects (Beta) Features
Views:
  - Board view: Kanban-style
  - Table view: Spreadsheet-like
  - Calendar view: Timeline based

Custom Fields:
  - Priority: Select (Critical, High, Medium, Low)
  - Effort: Number (story points)
  - Component: Select (Frontend, Backend, API)
  - Release: Select (v1.0, v1.1, v2.0)

Workflows:
  - Auto-assign based on component
  - Auto-set milestone based on priority
  - Notify team lead on critical issues
```

## Milestone Management

### 1. Creare Milestone Efficaci

```yaml
# Struttura Milestone
Title: v1.2.0 - User Authentication
Description: |
  Complete user authentication system including:
  - User registration and login
  - Password reset functionality
  - Email verification
  - OAuth integration

Due Date: 2024-03-15
Target: 15 issues, 0 pull requests

Progress Tracking:
  - Completion percentage
  - Remaining issues
  - Time remaining
```

### 2. Planning Sprint con Milestone

```bash
# Sprint Planning Process
1. Create milestone for sprint
   - Set realistic due date
   - Define clear objectives
   - Estimate effort required

2. Assign issues to milestone
   - Prioritize by business value
   - Balance team workload
   - Consider dependencies

3. Track progress
   - Daily standup check-ins
   - Update issue status
   - Adjust scope if needed

4. Sprint review
   - Demo completed features
   - Review what worked/didn't
   - Plan next sprint
```

## Automazione Workflow

### 1. GitHub Actions per Issue Management

```yaml
# .github/workflows/issue-management.yml
name: Issue Management

on:
  issues:
    types: [opened, labeled, assigned]

jobs:
  auto-assign:
    runs-on: ubuntu-latest
    steps:
      - name: Auto-assign by label
        uses: kentaro-m/auto-assign-action@v1.2.1
        with:
          configuration-path: '.github/auto-assign.yml'

  notify-team:
    runs-on: ubuntu-latest
    if: contains(github.event.issue.labels.*.name, 'priority-critical')
    steps:
      - name: Notify team on critical issue
        uses: 8398a7/action-slack@v3
        with:
          status: custom
          custom_payload: |
            {
              text: "🚨 Critical issue opened: ${{ github.event.issue.title }}",
              channel: "#dev-alerts"
            }
```

### 2. Issue Auto-Assignment

```yaml
# .github/auto-assign.yml
assignees:
  - frontend:
      - alice
      - bob
  - backend:
      - charlie
      - diana
  - documentation:
      - eve

labels:
  frontend:
    - alice
    - bob
  backend:
    - charlie
    - diana
  bug:
    - tech-lead
```

## Metrics e Reporting

### 1. Issue Analytics

```bash
# Metriche da trackare
- Issue resolution time
- Response time to new issues
- Number of issues per component
- Team workload distribution
- Sprint completion rate

# GitHub Insights
Repository → Insights → Issues
- Open/closed ratio
- Issue lifetime
- Most active contributors
```

### 2. Custom Reports

```bash
# GitHub CLI per reporting
# Issues by milestone
gh issue list --milestone "v1.2.0" --state open

# Issues by assignee
gh issue list --assignee "alice" --state open

# Issues by label
gh issue list --label "bug" --state open

# Generate sprint report
gh issue list --milestone "Sprint 1" --json number,title,state,assignees
```

## Best Practices

### 1. Issue Creation

- **Titoli descriptivi**: Usare [TYPE] prefix e descrizione chiara
- **Dettagli sufficienti**: Includere context, steps, expected behavior
- **Labels appropriate**: Categorizzare per type, priority, component
- **Assignment immediato**: Assegnare a persona responsible o team
- **Link correlati**: Riferimenti a PR, altre issues, documentation

### 2. Issue Management

- **Triage regolare**: Review nuove issues settimanalmente
- **Status updates**: Commentare progress e blockers
- **Close promptly**: Chiudere issues risolte tempestivamente
- **Archive appropriately**: Utilizzare "wontfix" per issues non actionable
- **Documentation**: Linkare a documentazione rilevante

### 3. Project Board Hygiene

- **Regular grooming**: Pulire board durante sprint planning
- **Accurate status**: Mantenere colonne aggiornate
- **Clear definitions**: Definire criteri per ogni colonna
- **Limit WIP**: Non sovraccaricare "In Progress"
- **Review cadence**: Check board durante daily standups

## Troubleshooting Comune

### 1. Issue Assignment Problems

```bash
# Problema: Issues non assigned automaticamente
# Soluzione: Verificare auto-assign configuration

# Check team permissions
gh api repos/:owner/:repo/teams

# Verify label configuration
cat .github/auto-assign.yml
```

### 2. Project Board Sync Issues

```bash
# Problema: Issues non si muovono automaticamente
# Soluzione: Configurare automation rules

# Via GitHub UI:
# Project → Settings → Automation
# Add rules for state transitions
```

## Quiz di Verifica

### Domande

1. **Quali sono gli elementi essenziali di una issue ben strutturata?**

2. **Come si configura un sistema di labels efficace per un progetto?**

3. **Qual è la differenza tra milestone e project board?**

4. **Come si automatizza l'assignment delle issues basato su labels?**

5. **Quali metriche sono importanti per trackare la salute del progetto?**

### Risposte

1. **Issue Structure**: Title descriptive, labels appropriate, assignee, description chiara, acceptance criteria, additional context

2. **Label System**: Categories (type, priority, component), color coding, clear descriptions, automation rules

3. **Milestone vs Project Board**: Milestone = time-bound goals con due date, Project Board = workflow management tool per tracking progress

4. **Auto-Assignment**: GitHub Actions con configuration file .github/auto-assign.yml, rules basate su labels o file paths

5. **Important Metrics**: Resolution time, response time, completion rate, workload distribution, issue velocity

## Esercizi Pratici

### Esercizio 1: Setup Issue System

```bash
# Obiettivo: Configurare complete issue management system

# Step 1: Creare label schema
# - Type labels (bug, feature, docs)
# - Priority labels (critical, high, medium, low)
# - Component labels (frontend, backend, api)

# Step 2: Creare issue templates
# - Bug report template
# - Feature request template
# - Task template

# Step 3: Setup project board
# - Create columns: Backlog, To Do, In Progress, Review, Done
# - Configure automation rules

# Step 4: Create milestone
# - Set due date 2 weeks from now
# - Add description with objectives
```

### Esercizio 2: Issue Workflow Practice

```bash
# Obiettivo: Praticare complete issue lifecycle

# Step 1: Creare 5 issues diverse types
# - 2 bug reports
# - 2 feature requests  
# - 1 documentation task

# Step 2: Assignare appropriate labels
# Step 3: Aggiungerle al project board
# Step 4: Simulare workflow progression
# Step 5: Chiudere issues con appropriate resolution
```

## Risorse Aggiuntive

### Documentazione Ufficiale
- [GitHub Issues Documentation](https://docs.github.com/en/issues)
- [Project Boards Guide](https://docs.github.com/en/issues/organizing-your-work-with-project-boards)
- [GitHub Projects (Beta)](https://docs.github.com/en/issues/trying-out-the-new-projects-experience)

### Tools e Integrazioni
- Zenhub per advanced project management
- Jira sync per enterprise workflows
- Slack notifications per team alerts

---

[⬅️ Workflow Collaborativo](./02-workflow-collaborativo.md) | [➡️ Comunicazione Efficace](./04-comunicazione-efficace.md)
