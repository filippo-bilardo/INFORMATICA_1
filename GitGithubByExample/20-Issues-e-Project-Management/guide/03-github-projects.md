# GitHub Projects

## 📖 Introduzione

**GitHub Projects** è una piattaforma integrata di project management che permette di organizzare, tracciare e gestire il lavoro direttamente dentro GitHub. Con Projects puoi creare board Kanban, tabelle, timeline e grafici per visualizzare il progresso del tuo team.

GitHub Projects (Beta) rappresenta la nuova generazione di strumenti di project management, offrendo:
- **Views multiple**: Kanban, tabelle, timeline, roadmap
- **Custom fields**: Metadati personalizzati per items
- **Automation**: Workflow automatizzati integrati
- **Insights**: Analytics e reporting avanzati

## 🎯 Tipi di Projects

### Classic Projects (Legacy)

I Projects classici offrono board Kanban semplici:

- **Repository Projects**: Legati a un singolo repository
- **Organization Projects**: Span multiple repositories
- **User Projects**: Projects personali

### Projects (Beta) - Raccomandato

La nuova generazione con funzionalità avanzate:

- **Multi-repository**: Gestisce items da repository diversi
- **Custom fields**: Status, priority, dates, text, numbers
- **Multiple views**: Stesso data set, visualizzazioni diverse
- **Advanced automation**: Workflow sofisticati

## 🗂️ Struttura di un Project

### Items

Gli **items** sono gli elementi fondamentali:

```
Issues          🐛 Bug reports, feature requests
Pull Requests   🔀 Code changes
Draft Issues    📝 Ideas non ancora formali
Notes           📋 Documentation, meeting notes
```

### Fields

**Built-in Fields**:
- **Title**: Nome dell'item
- **Assignees**: Chi è responsabile
- **Status**: Stato corrente
- **Repository**: Da quale repo proviene
- **Labels**: Tags di categorizzazione

**Custom Fields**:
- **Select**: Dropdown con opzioni predefinite
- **Text**: Campo testo libero
- **Number**: Valori numerici
- **Date**: Date e deadline
- **Iteration**: Sprint/milestone

## 📊 Views e Visualizzazioni

### Table View

Visualizzazione tabulare per analisi dettagliate:

```
| Title              | Status      | Assignee | Priority | Due Date   |
|--------------------|-------------|----------|----------|------------|
| Fix login bug      | In Progress | @alice   | High     | 2024-01-15 |
| Add dark mode      | Todo        | @bob     | Medium   | 2024-01-30 |
| Update docs        | Done        | @carol   | Low      | 2024-01-10 |
```

### Board View (Kanban)

Visualizzazione Kanban per workflow management:

```
┌─────────────┬─────────────┬─────────────┬─────────────┐
│    Todo     │ In Progress │   Review    │    Done     │
├─────────────┼─────────────┼─────────────┼─────────────┤
│ • Feature A │ • Bug Fix 1 │ • Feature B │ • Bug Fix 2 │
│ • Feature C │ • Docs      │             │ • Feature D │
│ • Bug Fix 3 │             │             │             │
└─────────────┴─────────────┴─────────────┴─────────────┘
```

### Timeline View

Visualizzazione temporale per planning:

```
Jan  │──────────── Feature A ────────────│
     │     │─── Bug Fix ──│              │
     │                    │── Feature B ──│
Feb  │                              │─ Release ─│
```

### Roadmap View

Vista strategica a lungo termine:

```
Q1 2024     Q2 2024     Q3 2024     Q4 2024
│─ MVP ─│   │─ Beta ─│   │─ V1.0 ─│   │─ V2.0 ─│
```

## ⚙️ Configurazione Project

### Creazione Project

#### Via Web Interface

```
1. GitHub.com → Projects → New Project
2. Scegli template o inizia vuoto
3. Configura visibilità (Public/Private)
4. Aggiungi description e README
```

#### Via GitHub CLI

```bash
# Crea nuovo project
gh project create --title "Web App Development" --body "Main development project"

# Lista projects esistenti
gh project list

# View project details
gh project view --id PROJECT_ID
```

### Configurazione Fields

```bash
# Aggiungi custom field
gh project field-create --project-id PROJECT_ID --name "Priority" --data-type SINGLE_SELECT --single-select-option "High" --single-select-option "Medium" --single-select-option "Low"

# Aggiungi date field
gh project field-create --project-id PROJECT_ID --name "Due Date" --data-type DATE

# Lista fields
gh project field-list --project-id PROJECT_ID
```

## 🔧 Gestione Items

### Aggiungere Items

#### Via Web Interface

```
1. In project view → + Add Item
2. Search/select existing issues/PRs
3. Oppure crea new draft issue
4. Set fields (status, assignee, etc.)
```

#### Via GitHub CLI

```bash
# Aggiungi issue esistente
gh project item-add --project-id PROJECT_ID --url "https://github.com/user/repo/issues/123"

# Aggiungi PR
gh project item-add --project-id PROJECT_ID --url "https://github.com/user/repo/pull/456"

# Crea draft issue
gh project item-create --project-id PROJECT_ID --title "New Feature" --body "Description"
```

### Modificare Items

```bash
# Aggiorna status
gh project item-edit --project-id PROJECT_ID --id ITEM_ID --field-id STATUS_FIELD_ID --single-select-option-id OPTION_ID

# Set assignee
gh project item-edit --project-id PROJECT_ID --id ITEM_ID --field-id ASSIGNEE_FIELD_ID --user-id USER_ID

# Set text field
gh project item-edit --project-id PROJECT_ID --id ITEM_ID --field-id TEXT_FIELD_ID --text "Updated text"
```

## 🔄 Automation e Workflows

### Built-in Automation

**Item added to project**:
```
When: New item added
Action: Set status to "Todo"
```

**Pull request merged**:
```
When: PR merged  
Action: Set status to "Done"
```

**Issue closed**:
```
When: Issue closed
Action: Set status to "Done"
```

### Advanced Automation

#### GitHub Actions Integration

```yaml
name: Update Project
on:
  issues:
    types: [opened, closed]
  pull_request:
    types: [opened, closed, merged]

jobs:
  update_project:
    runs-on: ubuntu-latest
    steps:
    - name: Update project item
      uses: actions/github-script@v6
      with:
        github-token: ${{ secrets.GITHUB_TOKEN }}
        script: |
          const query = `
            mutation($projectId: ID!, $itemId: ID!, $fieldId: ID!, $value: String!) {
              updateProjectV2ItemFieldValue(
                input: {
                  projectId: $projectId
                  itemId: $itemId  
                  fieldId: $fieldId
                  value: {singleSelectOptionId: $value}
                }
              ) {
                projectV2Item {
                  id
                }
              }
            }
          `;
          
          // Logic to update project fields based on issue/PR events
```

#### Custom Workflows

```yaml
name: Sprint Planning Automation
on:
  schedule:
    - cron: '0 9 * * MON'  # Every Monday 9am

jobs:
  sprint_planning:
    runs-on: ubuntu-latest
    steps:
    - name: Start new sprint
      run: |
        # Move items from "Sprint Backlog" to "Current Sprint"
        # Update iteration field
        # Notify team
```

## 📊 Views Avanzate e Filtering

### Filtri

```bash
# Filtra per assignee
assignee:@me

# Filtra per status
status:"In Progress"

# Filtra per labels
label:bug,enhancement

# Filtra per repository
repo:user/frontend-repo

# Combina filtri
assignee:@me status:"Todo" label:priority-high
```

### Sorting

```bash
# Sort per priority (custom field)
sort:priority-desc

# Sort per data creazione
sort:created-desc

# Sort per update time
sort:updated-asc
```

### Grouping

```
Group by: Status
├── Todo (5 items)
├── In Progress (3 items)  
├── Review (2 items)
└── Done (12 items)

Group by: Assignee
├── @alice (4 items)
├── @bob (3 items)
├── Unassigned (2 items)
```

## 📈 Insights e Analytics

### Burn-down Charts

```
Story Points Remaining
│
│ \
│  \  
│   \___
│       \___
└─────────────────→ Time
```

### Velocity Tracking

```
Sprint Velocity
│     ████
│   ████████ 
│ ████████████
│████████████████
└─────────────────→ Sprints
```

### Cumulative Flow

```
Items by Status Over Time
│
│ ████████████ Done
│ ████████ Review  
│ ████ In Progress
│ ██ Todo
└─────────────────→ Time
```

## 🎨 Templates e Best Practices

### Software Development Template

```
Columns:
├── 📋 Backlog
├── 🔄 Sprint Planning  
├── 🏗️ In Progress
├── 👀 Code Review
├── 🧪 Testing
└── ✅ Done

Custom Fields:
├── Story Points (Number)
├── Priority (Select: High/Medium/Low)
├── Sprint (Iteration)
├── Feature Area (Select)
└── Due Date (Date)
```

### Bug Tracking Template

```
Columns:
├── 🐛 New Bugs
├── 🔍 Triaged
├── 🔧 In Progress  
├── ✅ Fixed
├── ✅ Verified
└── 🚫 Won't Fix

Custom Fields:
├── Severity (Select: Critical/High/Medium/Low)
├── Browser (Select: Chrome/Firefox/Safari/Edge)
├── OS (Select: Windows/Mac/Linux)
└── Reporter (Text)
```

### Marketing Campaign Template

```
Columns:
├── 💡 Ideas
├── 📝 Planning
├── 🎨 Creative
├── 👀 Review  
├── 🚀 Live
└── 📊 Analysis

Custom Fields:
├── Campaign Type (Select)
├── Budget (Number)
├── Launch Date (Date)
├── Target Audience (Text)
└── Success Metric (Text)
```

## 🚨 Problemi Comuni e Soluzioni

### Performance con Molti Items

**Problema**: Project lento con 1000+ items

**Soluzione**:
```bash
# Usa filtri per ridurre items visualizzati
status:"In Progress","Todo"

# Archivia items completati periodicamente
# Split in multiple projects per area/team
```

### Sincronizzazione Issues/PRs

**Problema**: Items non si aggiornano automaticamente

**Soluzione**:
```yaml
# GitHub Actions per sincronizzazione forzata
- name: Sync project items
  run: |
    gh project item-list --project-id $PROJECT_ID --format json | \
    jq -r '.[] | select(.status != .issue.state) | .id' | \
    xargs -I {} gh project item-edit --id {} --sync-with-issue
```

### Access Control

**Problema**: Gestione permessi complessa

**Soluzione**:
```
Organization Projects: Admin controls access
├── Public: Everyone can view
├── Private: Only org members
└── Team-specific: Custom teams access

Repository Projects: Inherit repo permissions
```

## 📋 Best Practices

### 1. Struttura Consistente

```bash
# Standard column naming
Todo → In Progress → Review → Done

# Consistent field naming
Priority (not Importance)
Due Date (not Deadline)
Story Points (not Complexity)
```

### 2. Automation Strategy

```bash
# Start simple
Basic status transitions

# Add complexity gradually  
Custom field updates
Cross-repository sync
External tool integration
```

### 3. Team Adoption

```markdown
# Training checklist
- [ ] Project overview session
- [ ] Hands-on workshop
- [ ] Document team-specific workflows
- [ ] Regular review meetings
- [ ] Feedback collection
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la differenza principale tra Classic Projects e Projects (Beta)?**

<details>
<summary>Risposta</summary>

**Classic Projects**:
- Board Kanban semplici
- Limited to repository/organization scope
- Basic automation
- No custom fields

**Projects (Beta)**:
- Multiple view types (table, board, timeline, roadmap)
- Cross-repository items
- Custom fields e metadata
- Advanced automation e insights
- Better integration con GitHub ecosystem

</details>

### Domanda 2
**Come implementeresti un workflow di sprint planning automatizzato?**

<details>
<summary>Risposta</summary>

```yaml
# GitHub Action attivata ogni lunedì
1. Query items con status "Sprint Backlog"
2. Filtra per priority e story points
3. Crea new iteration
4. Assegna items al current sprint
5. Update status to "Todo"
6. Notify team via Slack/email
```

Usando custom fields per story points e iteration tracking.

</details>

### Domanda 3
**Quale view useresti per pianificare release quarterly?**

<details>
<summary>Risposta</summary>

**Timeline View** o **Roadmap View**:
- Visualizza feature su time scale
- Identifica dependencies
- Mostra overlap e resource conflicts
- Permette drag-and-drop per re-planning

Con custom fields per:
- Quarter (Q1, Q2, Q3, Q4)
- Epic/Feature area
- Estimated completion date

</details>

## 🛠️ Esercizio Pratico

### Obiettivo
Creare un project completo per gestione di un'applicazione web con team multi-disciplinare.

### Passi

1. **Project Setup**:
   ```bash
   # Crea project con template appropriato
   gh project create --title "Web App v2.0" --body "Main development project"
   
   # Configura custom fields
   # Priority, Story Points, Sprint, Feature Area, Due Date
   ```

2. **View Configuration**:
   ```bash
   # Board view per daily work
   # Table view per planning
   # Timeline view per roadmap
   # Grouping e filtering strategies
   ```

3. **Items Population**:
   ```bash
   # Importa existing issues e PRs
   # Crea epic/milestone items
   # Set initial field values
   ```

4. **Automation Setup**:
   ```yaml
   # Auto-status transitions
   # Sprint assignment automation
   # Notification workflows
   ```

5. **Team Onboarding**:
   ```markdown
   # Crea documentation
   # Training per different roles
   # Feedback collection process
   ```

### Verifica Risultati

Il completamento dell'esercizio dimostra:
- ✅ Project configurato con views multiple appropriate
- ✅ Custom fields che supportano team workflow
- ✅ Automation funzionante per task comuni
- ✅ Team può usare project efficacemente

## 🔗 Link Correlati

- [01 - GitHub Issues](./01-github-issues.md) - Fondamentali degli Issues
- [02 - Labels e Organization](./02-labels-organization.md) - Organizzazione avanzata
- [04 - Automation](./04-automation.md) - Automazione workflow

---

### 🧭 Navigazione

- **⬅️ Precedente**: [02 - Labels e Organization](./02-labels-organization.md)
- **🏠 Home Modulo**: [README.md](../README.md)
- **➡️ Successivo**: [04 - Automation](./04-automation.md)
