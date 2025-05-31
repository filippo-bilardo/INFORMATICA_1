# Issue Tracking Guide

## GitHub Issues Management

### 1. Issue Templates

#### Bug Report Template
```markdown
<!-- .github/ISSUE_TEMPLATE/bug_report.md -->
---
name: Bug Report
about: Crea un report per aiutarci a migliorare
title: '[BUG] '
labels: 'bug, needs-triage'
assignees: ''
---

## Descrizione Bug
Una descrizione chiara e concisa del bug.

## Passi per Riprodurre
1. Vai a '...'
2. Clicca su '....'
3. Scorri fino a '....'
4. Visualizza errore

## Comportamento Atteso
Una descrizione chiara di cosa ti aspettavi che succedesse.

## Comportamento Attuale
Una descrizione chiara di cosa è successo invece.

## Screenshots
Se applicabile, aggiungi screenshots per spiegare il problema.

## Ambiente
- OS: [e.g. iOS, Windows, Linux]
- Browser: [e.g. chrome, safari]
- Versione: [e.g. 22]
- Device: [e.g. iPhone6, Desktop]

## Contesto Aggiuntivo
Aggiungi qualsiasi altro contesto sul problema qui.

## Checklist
- [ ] Ho controllato che non ci siano issue simili
- [ ] Ho testato con l'ultima versione
- [ ] Ho fornito tutti i dettagli richiesti
```

#### Feature Request Template
```markdown
<!-- .github/ISSUE_TEMPLATE/feature_request.md -->
---
name: Feature Request
about: Suggerisci un'idea per questo progetto
title: '[FEATURE] '
labels: 'enhancement, needs-triage'
assignees: ''
---

## Problema da Risolvere
Descrivi il problema che questa feature risolverebbe.

## Soluzione Proposta
Una descrizione chiara di cosa vorresti che succeda.

## Alternative Considerate
Una descrizione di eventuali soluzioni alternative che hai considerato.

## User Story
Come [tipo di utente], voglio [obiettivo] così da [beneficio].

## Acceptance Criteria
- [ ] Criterio 1
- [ ] Criterio 2
- [ ] Criterio 3

## Mockup/Design
Se disponibili, aggiungi mockup o design della feature.

## Priorità
- [ ] Critica (blocca il rilascio)
- [ ] Alta (importante per il prossimo rilascio)
- [ ] Media (nice to have)
- [ ] Bassa (future enhancement)

## Effort Estimation
- [ ] Small (< 1 giorno)
- [ ] Medium (1-3 giorni)  
- [ ] Large (> 3 giorni)
- [ ] Epic (richiede breakdown)
```

### 2. Label System

```javascript
// GitHub Labels Configuration
const labelSystem = {
    // Type labels
    type: {
        'bug': { color: 'd73a4a', description: 'Qualcosa non funziona' },
        'enhancement': { color: 'a2eeef', description: 'Nuova feature o miglioramento' },
        'documentation': { color: '0075ca', description: 'Miglioramenti alla documentazione' },
        'question': { color: 'd876e3', description: 'Richiesta di informazioni' },
        'help wanted': { color: '008672', description: 'Aiuto extra è benvenuto' }
    },
    
    // Priority labels
    priority: {
        'priority: critical': { color: 'b60205', description: 'Deve essere risolto immediatamente' },
        'priority: high': { color: 'd93f0b', description: 'Importante per il prossimo rilascio' },
        'priority: medium': { color: 'fbca04', description: 'Priorità media' },
        'priority: low': { color: '0e8a16', description: 'Bassa priorità' }
    },
    
    // Status labels
    status: {
        'status: needs-triage': { color: 'ededed', description: 'Necessita valutazione' },
        'status: in-progress': { color: 'c2e0c6', description: 'In lavorazione' },
        'status: blocked': { color: 'b60205', description: 'Bloccato da dipendenze' },
        'status: ready-for-review': { color: '0075ca', description: 'Pronto per review' },
        'status: waiting-for-response': { color: 'fbca04', description: 'In attesa di risposta' }
    },
    
    // Component labels
    component: {
        'frontend': { color: 'e99695', description: 'Frontend/UI issues' },
        'backend': { color: '5319e7', description: 'Backend/API issues' },
        'database': { color: '1d76db', description: 'Database related' },
        'deployment': { color: 'f9d0c4', description: 'Deployment e infrastructure' },
        'testing': { color: 'c5def5', description: 'Testing related' }
    }
};
```

### 3. Issue Workflow Automation

```yaml
# .github/workflows/issue-management.yml
name: Issue Management
on:
  issues:
    types: [opened, edited, closed, reopened]
  issue_comment:
    types: [created]

jobs:
  triage:
    if: github.event.action == 'opened'
    runs-on: ubuntu-latest
    steps:
      - name: Add triage label
        uses: actions/github-script@v6
        with:
          script: |
            github.rest.issues.addLabels({
              owner: context.repo.owner,
              repo: context.repo.repo,
              issue_number: context.issue.number,
              labels: ['status: needs-triage']
            });

  auto-assign:
    if: github.event.action == 'opened'
    runs-on: ubuntu-latest
    steps:
      - name: Auto-assign based on labels
        uses: actions/github-script@v6
        with:
          script: |
            const issue = context.payload.issue;
            const labels = issue.labels.map(l => l.name);
            
            let assignee = null;
            if (labels.includes('frontend')) assignee = 'frontend-lead';
            if (labels.includes('backend')) assignee = 'backend-lead';
            if (labels.includes('database')) assignee = 'db-admin';
            
            if (assignee) {
              github.rest.issues.addAssignees({
                owner: context.repo.owner,
                repo: context.repo.repo,
                issue_number: issue.number,
                assignees: [assignee]
              });
            }

  stale-check:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/stale@v8
        with:
          stale-issue-message: |
            Questa issue è stata automaticamente marcata come stale perché non ha avuto attività recente.
            Verrà chiusa se non ci saranno ulteriori aggiornamenti.
          close-issue-message: |
            Questa issue è stata chiusa automaticamente per inattività.
          stale-issue-label: 'status: stale'
          days-before-stale: 30
          days-before-close: 7
```

### 4. Project Board Integration

```javascript
// Project Board Automation
const projectBoardConfig = {
    columns: {
        'Backlog': { 
            automation: 'newly_added',
            filter: 'is:issue is:open label:"status: needs-triage"'
        },
        'To Do': { 
            automation: 'to_do',
            filter: 'is:issue is:open -label:"status: needs-triage" -label:"status: in-progress"'
        },
        'In Progress': { 
            automation: 'in_progress',
            filter: 'is:issue is:open label:"status: in-progress"'
        },
        'Review': { 
            automation: 'under_review',
            filter: 'is:issue is:open label:"status: ready-for-review"'
        },
        'Done': { 
            automation: 'done',
            filter: 'is:issue is:closed'
        }
    }
};

// Script per sincronizzare issue con project board
function syncIssueToProjectBoard(issue, newStatus) {
    const columnMapping = {
        'opened': 'Backlog',
        'in_progress': 'In Progress',
        'ready_for_review': 'Review',
        'closed': 'Done'
    };
    
    const targetColumn = columnMapping[newStatus];
    if (targetColumn) {
        moveCardToColumn(issue.id, targetColumn);
    }
}
```

### 5. Issue Metrics & Reporting

```javascript
// Issue Analytics
class IssueAnalytics {
    constructor(githubApi) {
        this.github = githubApi;
    }
    
    async getIssueMetrics(repo, timeframe = '30d') {
        const issues = await this.github.issues.listForRepo({
            owner: repo.owner,
            repo: repo.name,
            state: 'all',
            since: this.getDateFromTimeframe(timeframe)
        });
        
        return {
            total: issues.data.length,
            open: issues.data.filter(i => i.state === 'open').length,
            closed: issues.data.filter(i => i.state === 'closed').length,
            avgResolutionTime: this.calculateAvgResolutionTime(issues.data),
            byLabel: this.groupByLabel(issues.data),
            byAssignee: this.groupByAssignee(issues.data)
        };
    }
    
    calculateAvgResolutionTime(issues) {
        const closedIssues = issues.filter(i => i.closed_at);
        const totalTime = closedIssues.reduce((sum, issue) => {
            const created = new Date(issue.created_at);
            const closed = new Date(issue.closed_at);
            return sum + (closed - created);
        }, 0);
        
        return totalTime / closedIssues.length / (1000 * 60 * 60 * 24); // days
    }
    
    generateReport(metrics) {
        return `
# Issue Report

## Summary
- **Total Issues**: ${metrics.total}
- **Open Issues**: ${metrics.open}
- **Closed Issues**: ${metrics.closed}
- **Resolution Rate**: ${((metrics.closed / metrics.total) * 100).toFixed(1)}%
- **Avg Resolution Time**: ${metrics.avgResolutionTime.toFixed(1)} days

## By Priority
${this.formatLabelStats(metrics.byLabel, 'priority')}

## By Component  
${this.formatLabelStats(metrics.byLabel, 'component')}

## Top Contributors
${this.formatAssigneeStats(metrics.byAssignee)}
        `;
    }
}
```

### 6. Issue Templates Avanzati

```markdown
<!-- .github/ISSUE_TEMPLATE/user_story.md -->
---
name: User Story
about: Definisci una nuova user story
title: '[STORY] Come [utente] voglio [obiettivo]'
labels: 'user-story, needs-estimation'
assignees: ''
---

## User Story
**Come** [tipo di utente]
**Voglio** [obiettivo/desiderio]
**Così da** [beneficio/valore]

## Background/Contesto
Perché questa user story è importante? Quale problema risolve?

## Acceptance Criteria
### Scenario: [Nome scenario]
**Dato che** [contesto iniziale]
**Quando** [azione dell'utente]
**Allora** [risultato atteso]
**E** [risultato aggiuntivo]

### Scenario: [Nome scenario alternativo]
**Dato che** [contesto diverso]
**Quando** [azione dell'utente]
**Allora** [risultato atteso]

## Definition of Done
- [ ] Codice sviluppato seguendo coding standards
- [ ] Unit test scritti e passanti (coverage > 80%)
- [ ] Integration test implementati
- [ ] Code review completato
- [ ] Documentazione aggiornata
- [ ] Testato su browser supportati
- [ ] Accessibility requirements verificati
- [ ] Performance requirements verificati
- [ ] Security review completato
- [ ] Deploy in staging successful
- [ ] Product Owner approval

## Dependencies
- [ ] Issue #XXX deve essere completato prima
- [ ] API endpoint YYY deve essere disponibile
- [ ] Design approval per componente ZZZ

## Technical Notes
Note tecniche per gli sviluppatori (architettura, considerazioni, limiti)

## Mockups/Wireframes
Link a design, prototipi, o sketches

## Estimation
Story Points: [ ] 1 [ ] 2 [ ] 3 [ ] 5 [ ] 8 [ ] 13 [ ] 21

## Business Value
- [ ] Critico per il business
- [ ] Alto impatto utente
- [ ] Miglioramento esperienza
- [ ] Technical debt reduction
- [ ] Nice to have
```

### 7. Notification & Escalation

```javascript
// Escalation Rules
const escalationRules = {
    critical: {
        initialResponse: '2h',
        escalationLevels: [
            { after: '4h', notify: ['team-lead', 'product-owner'] },
            { after: '8h', notify: ['engineering-manager'] },
            { after: '24h', notify: ['cto'] }
        ]
    },
    high: {
        initialResponse: '8h',
        escalationLevels: [
            { after: '24h', notify: ['team-lead'] },
            { after: '72h', notify: ['product-owner'] }
        ]
    }
};

// Slack Integration
async function notifySlack(issue, level) {
    const webhook = process.env.SLACK_WEBHOOK;
    const message = {
        text: `🚨 Issue Escalation - Level ${level}`,
        attachments: [{
            color: level === 'critical' ? 'danger' : 'warning',
            fields: [
                { title: 'Issue', value: `#${issue.number}: ${issue.title}`, short: false },
                { title: 'Priority', value: issue.priority, short: true },
                { title: 'Assignee', value: issue.assignee || 'Unassigned', short: true },
                { title: 'Age', value: `${calculateAge(issue.created_at)} hours`, short: true }
            ],
            actions: [{
                type: 'button',
                text: 'View Issue',
                url: issue.html_url
            }]
        }]
    };
    
    await fetch(webhook, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(message)
    });
}
```

Questa guida fornisce un sistema completo per il tracking e la gestione delle issue nel progetto finale, dall'apertura alla risoluzione.
