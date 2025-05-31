# Esempio 3: Gestione Issue e Project Board

## Scenario
Il team del Budget Tracker deve organizzare il lavoro per la prossima release utilizzando GitHub Issues e Project Board per coordinare le attività.

## Setup Iniziale

### 1. Creazione Issues Template
Lisa (Project Manager) crea template per standardizzare le issue.

**`.github/ISSUE_TEMPLATE/feature-request.yml`**
```yaml
name: 🚀 Feature Request
description: Richiesta di nuova funzionalità
title: "[FEATURE] "
labels: ["enhancement", "needs-triage"]
assignees: []
body:
  - type: markdown
    attributes:
      value: |
        Grazie per aver proposto una nuova feature!
  
  - type: textarea
    id: description
    attributes:
      label: Descrizione
      description: Descrivi la funzionalità richiesta
      placeholder: |
        Come utente, voglio...
        In modo da...
    validations:
      required: true
  
  - type: textarea
    id: acceptance-criteria
    attributes:
      label: Criteri di Accettazione
      description: Condizioni che devono essere soddisfatte
      placeholder: |
        - [ ] Criterio 1
        - [ ] Criterio 2
    validations:
      required: true
  
  - type: dropdown
    id: priority
    attributes:
      label: Priorità
      options:
        - Low
        - Medium
        - High
        - Critical
    validations:
      required: true
```

**`.github/ISSUE_TEMPLATE/bug-report.yml`**
```yaml
name: 🐛 Bug Report
description: Segnalazione di un bug
title: "[BUG] "
labels: ["bug", "needs-triage"]
body:
  - type: textarea
    id: description
    attributes:
      label: Descrizione del Bug
      description: Descrizione chiara del problema
    validations:
      required: true
  
  - type: textarea
    id: steps
    attributes:
      label: Passi per Riprodurre
      placeholder: |
        1. Vai a '...'
        2. Clicca su '...'
        3. Vedi errore
    validations:
      required: true
  
  - type: textarea
    id: expected
    attributes:
      label: Comportamento Atteso
      description: Cosa dovrebbe succedere
    validations:
      required: true
  
  - type: textarea
    id: actual
    attributes:
      label: Comportamento Attuale
      description: Cosa succede invece
    validations:
      required: true
  
  - type: textarea
    id: environment
    attributes:
      label: Ambiente
      placeholder: |
        - OS: [e.g. iOS]
        - Browser: [e.g. chrome, safari]
        - Version: [e.g. 22]
```

### 2. Creazione Project Board
Lisa crea un project board per organizzare il lavoro.

**Configurazione Project Board:**
```
Nome: Budget Tracker v2.0
Descrizione: Milestone per la release v2.0

Colonne:
- 📋 Backlog
- 🔍 In Review
- 👩‍💻 In Progress  
- ✅ Done
- 🚀 Released

Automation:
- To Do → In Progress (quando issue assegnata)
- In Progress → Done (quando PR merged)
```

## Gestione Issue in Pratica

### 3. Creazione Issue per Nuove Feature

**Issue #45: Dashboard Analytics**
```markdown
**Descrizione:**
Come utente, voglio vedere analytics del mio budget in una dashboard
In modo da avere una visione d'insieme delle mie finanze

**Criteri di Accettazione:**
- [ ] Grafici spese per categoria
- [ ] Trend mensile entrate/uscite  
- [ ] Indicatori KPI (budget remaining, saving rate)
- [ ] Export PDF del report
- [ ] Responsive design

**Priorità:** High

**Epic:** Dashboard Enhancement
**Story Points:** 8
**Milestone:** v2.0

**Tasks:**
- [ ] Design UI mockups
- [ ] Backend API per analytics data
- [ ] Frontend charts con Chart.js
- [ ] PDF export functionality
- [ ] Unit tests
- [ ] Integration tests
```

**Labels:** `enhancement`, `frontend`, `backend`, `high-priority`
**Assignees:** Alex (Backend), Sara (Frontend)
**Projects:** Budget Tracker v2.0

### 4. Issue per Bug Fix

**Issue #46: Login Session Timeout**
```markdown
**Descrizione del Bug:**
L'utente viene disconnesso dopo 5 minuti anche se attivo

**Passi per Riprodurre:**
1. Login nell'app
2. Usa l'app normalmente per 6+ minuti
3. Prova a fare un'azione
4. Viene mostrato errore "Session expired"

**Comportamento Atteso:**
Session dovrebbe durare 30 minuti con auto-refresh se attivo

**Comportamento Attuale:**
Session scade dopo 5 minuti fissi

**Ambiente:**
- OS: Windows 10
- Browser: Chrome 91
- Version: v1.2.0

**Priority:** High
**Severity:** Major
```

**Labels:** `bug`, `authentication`, `high-priority`
**Assignee:** Alex
**Milestone:** v2.0

### 5. Organizzazione con Epic e Milestone

**Epic Issue #47: Mobile App Development**
```markdown
# Epic: Mobile App Development

## Obiettivo
Sviluppare app mobile nativa per iOS e Android

## User Stories incluse:
- [ ] #48 Setup React Native project
- [ ] #49 Authentication mobile
- [ ] #50 Budget overview mobile
- [ ] #51 Add transaction mobile  
- [ ] #52 Settings mobile
- [ ] #53 Offline sync capability

## Criteri di Accettazione Epic:
- [ ] App disponibile su App Store e Google Play
- [ ] Feature parity con web app
- [ ] Offline functionality
- [ ] Push notifications
- [ ] Sync bidirezionale

## Timeline:
- Sprint 1: Setup e Auth (2 settimane)
- Sprint 2: Core features (3 settimane) 
- Sprint 3: Advanced features (2 settimane)
- Sprint 4: Testing e release (1 settimana)

**Story Points totali:** 34
**Team:** Marco (Lead), Sara (Support)
```

### 6. Workflow con Issue

**Processo Standard:**
1. **Triage** - Lisa rivede nuove issue e assegna label/priorità
2. **Planning** - Team decide issue per sprint
3. **Development** - Developer crea branch da issue
4. **Review** - PR review process
5. **Testing** - QA testing su staging
6. **Closure** - Issue chiusa con merge

**Branch Naming Convention:**
```bash
# Per feature
feature/issue-45-dashboard-analytics

# Per bug
bugfix/issue-46-login-session-timeout

# Per hotfix
hotfix/issue-47-critical-payment-bug
```

### 7. Automation con Actions

**`.github/workflows/issue-management.yml`**
```yaml
name: Issue Management

on:
  issues:
    types: [opened, labeled, assigned]
  pull_request:
    types: [opened, closed]

jobs:
  auto-assign-project:
    if: github.event.action == 'opened'
    runs-on: ubuntu-latest
    steps:
      - name: Add to project
        uses: actions/add-to-project@v0.4.0
        with:
          project-url: https://github.com/users/teamleader/projects/1
          github-token: ${{ secrets.GITHUB_TOKEN }}

  auto-label-by-title:
    if: github.event.action == 'opened'
    runs-on: ubuntu-latest
    steps:
      - name: Label by title
        uses: github/issue-labeler@v3.0
        with:
          repo-token: ${{ secrets.GITHUB_TOKEN }}
          configuration-path: .github/labeler.yml

  link-pr-to-issue:
    if: github.event.pull_request.merged == true
    runs-on: ubuntu-latest
    steps:
      - name: Close linked issues
        uses: actions/github-script@v6
        with:
          script: |
            const prBody = context.payload.pull_request.body;
            const issueNumbers = prBody.match(/(?:closes|fixes|resolves)\s+#(\d+)/gi);
            
            if (issueNumbers) {
              for (const match of issueNumbers) {
                const issueNumber = match.match(/\d+/)[0];
                await github.rest.issues.update({
                  owner: context.repo.owner,
                  repo: context.repo.repo,
                  issue_number: issueNumber,
                  state: 'closed'
                });
              }
            }
```

### 8. Metriche e Reporting

**Issue Tracking Dashboard:**
```markdown
## Sprint 3 Metrics

### Velocity
- Story Points completati: 23/25 (92%)
- Issue chiuse: 8/9
- Bugs risolti: 3/3

### Quality Metrics  
- Bug escape rate: 5% (1 bug in produzione)
- Time to resolution: 2.3 giorni media
- Cycle time: 4.1 giorni media

### Team Performance
- Alex: 8 SP completati
- Sara: 7 SP completati  
- Marco: 8 SP completati
- Lisa: Supporto PM

### Burndown
Settimana 1: 25 SP remaining
Settimana 2: 15 SP remaining  
Fine Sprint: 2 SP remaining (carry-over)
```

## Best Practices Issue Management

### 1. **Template Consistency**
- Usa template per standardizzare informazioni
- Richiedi informazioni necessarie per debugging
- Include criteri di accettazione chiari

### 2. **Labeling Strategy**
```
Type: bug, enhancement, documentation, question
Priority: low, medium, high, critical  
Component: frontend, backend, mobile, infrastructure
Status: needs-triage, in-progress, blocked, ready-for-review
```

### 3. **Assignment Rules**
- Una persona per issue principale
- Team per review/support
- Rotation per bilanciare carico

### 4. **Communication**
- Update regolari su issue complesse
- Mention team members quando serve input
- Close con summary di cosa è stato fatto

### 5. **Integration con Development**
- Branch naming collegato a issue number
- PR description che referenzia issue
- Automatic closure con keywords

Questo approccio sistematico alle issue garantisce trasparenza, accountability e efficienza nel processo di sviluppo collaborativo.
