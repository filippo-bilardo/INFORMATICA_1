# Esercizio 1: Configurazione Completa di un Progetto

## Obiettivo
Configurare un progetto GitHub completo con sistema di issue tracking, project board, e workflow automatizzati per un team di sviluppo di un'applicazione web.

## Scenario
Sei il project manager di "WebApp Pro", un'applicazione e-commerce che il tuo team svilupperà nei prossimi 6 mesi. Devi configurare l'ambiente di lavoro GitHub per gestire:
- 5 sviluppatori frontend
- 3 sviluppatori backend  
- 2 QA tester
- 1 designer UI/UX
- 1 product owner

## Passaggi dell'Esercizio

### Fase 1: Creazione del Repository e Configurazione Base

1. **Crea il repository principale**
   ```bash
   # Crea repository "webapp-pro" con:
   - Descrizione dettagliata
   - README.md iniziale
   - .gitignore per Node.js
   - Licenza MIT
   ```

2. **Configura le impostazioni base**
   - [ ] Abilita Issues
   - [ ] Abilita Wiki
   - [ ] Abilita Discussions
   - [ ] Configura branch protection per `main`
   - [ ] Imposta merge requirements (PR review, CI checks)

### Fase 2: Configurazione Sistema Issues

3. **Crea le label personalizzate**
   ```markdown
   # Label di Priorità
   🔴 priority/critical - #d73a49
   🟠 priority/high - #ff9500
   🟡 priority/medium - #fbca04
   🟢 priority/low - #0e8a16

   # Label di Tipo
   🐛 type/bug - #d73a49
   ✨ type/feature - #a2eeef
   📝 type/documentation - #0075ca
   🔧 type/maintenance - #f9d0c4
   ⚡ type/performance - #e4e669

   # Label di Area
   🎨 area/frontend - #1d76db
   ⚙️ area/backend - #0052cc
   📱 area/mobile - #5319e7
   🧪 area/testing - #0e8a16
   🚀 area/deployment - #fbca04

   # Label di Stato
   ⏳ status/in-progress - #f9d0c4
   ✅ status/ready-for-review - #0e8a16
   🔒 status/blocked - #d73a49
   ❓ status/needs-info - #d4c5f9
   ```

4. **Configura i template delle issue**

   **Template Bug Report** (`.github/ISSUE_TEMPLATE/bug_report.yml`):
   ```yaml
   name: 🐛 Bug Report
   description: Segnala un bug nel sistema
   title: "[BUG] "
   labels: ["type/bug", "status/needs-info"]
   body:
     - type: markdown
       value: |
         Grazie per aver segnalato questo bug. Completa tutte le sezioni per aiutarci a risolvere il problema rapidamente.
     
     - type: textarea
       id: description
       attributes:
         label: Descrizione del Bug
         description: Descrivi dettagliatamente il problema riscontrato
         placeholder: Il bug si verifica quando...
       validations:
         required: true
     
     - type: textarea
       id: steps
       attributes:
         label: Passi per Riprodurre
         description: Elenca i passaggi per riprodurre il bug
         placeholder: |
           1. Vai alla pagina...
           2. Clicca su...
           3. Inserisci...
           4. Osserva l'errore...
       validations:
         required: true
     
     - type: textarea
       id: expected
       attributes:
         label: Comportamento Atteso
         description: Cosa ti aspettavi che accadesse?
       validations:
         required: true
     
     - type: textarea
       id: actual
       attributes:
         label: Comportamento Attuale
         description: Cosa è successo invece?
       validations:
         required: true
     
     - type: dropdown
       id: priority
       attributes:
         label: Priorità
         options:
           - Bassa
           - Media
           - Alta
           - Critica
       validations:
         required: true
     
     - type: textarea
       id: environment
       attributes:
         label: Ambiente
         description: Informazioni sull'ambiente (browser, OS, versione app)
         placeholder: |
           - Browser: Chrome 95.0
           - OS: Windows 10
           - Versione App: 1.2.3
   ```

   **Template Feature Request** (`.github/ISSUE_TEMPLATE/feature_request.yml`):
   ```yaml
   name: ✨ Feature Request
   description: Proponi una nuova funzionalità
   title: "[FEATURE] "
   labels: ["type/feature", "status/needs-info"]
   body:
     - type: textarea
       id: problem
       attributes:
         label: Problema da Risolvere
         description: Qual è il problema che questa feature risolverebbe?
       validations:
         required: true
     
     - type: textarea
       id: solution
       attributes:
         label: Soluzione Proposta
         description: Descrivi la soluzione che vorresti implementare
       validations:
         required: true
     
     - type: textarea
       id: alternatives
       attributes:
         label: Alternative Considerate
         description: Hai considerato altre soluzioni?
     
     - type: dropdown
       id: impact
       attributes:
         label: Impatto Stimato
         options:
           - Basso (miglioria minore)
           - Medio (nuova funzionalità utile)
           - Alto (funzionalità core essenziale)
           - Critico (blocca altri sviluppi)
       validations:
         required: true
   ```

### Fase 3: Configurazione Project Board

5. **Crea il Project Board "WebApp Pro Development"**
   
   **Vista Kanban - Sprint Board**:
   ```
   Colonne:
   📋 Backlog
   🏃 Sprint Ready
   ⚡ In Progress
   👀 In Review
   🧪 Testing
   ✅ Done
   ```

   **Custom Fields**:
   ```
   - Story Points (Number): 1, 2, 3, 5, 8, 13
   - Sprint (Select): Sprint 1, Sprint 2, Sprint 3...
   - Epic (Text): User Authentication, Product Catalog, Checkout...
   - Assignee Team (Select): Frontend, Backend, QA, Design
   - Estimate Hours (Number)
   - Business Value (Select): Low, Medium, High, Critical
   ```

6. **Configura automazioni del project board**
   
   ```yaml
   # Automation Rules:
   
   # 1. Auto-add new issues
   - trigger: issue_opened
     action: add_to_project
     column: "📋 Backlog"
   
   # 2. Move to In Progress when assigned
   - trigger: issue_assigned
     action: move_to_column
     column: "⚡ In Progress"
   
   # 3. Move to Done when closed
   - trigger: issue_closed
     action: move_to_column
     column: "✅ Done"
   
   # 4. Auto-assign based on labels
   - trigger: label_added
     condition: label = "area/frontend"
     action: assign_to_team
     team: "frontend-team"
   ```

### Fase 4: Configurazione Team e Permessi

7. **Crea i team GitHub**
   ```
   Organizzazione: webapp-pro-org
   
   Teams:
   - developers (parent team)
     - frontend-developers
     - backend-developers
   - qa-team
   - design-team
   - product-team
   ```

8. **Configura i permessi**
   ```
   Repository permissions:
   - product-team: Admin
   - developers: Write
   - qa-team: Triage
   - design-team: Read
   
   Branch protection rules:
   - main: Require PR reviews (2), Require CI, No force push
   - develop: Require PR reviews (1), Require CI
   - feature/*: No restrictions
   ```

### Fase 5: Workflow di Sviluppo

9. **Configura il workflow Agile**
   
   **Sprint Planning Process**:
   ```markdown
   ## Sprint Planning (ogni 2 settimane)
   
   1. **Sprint Review** (Venerdì)
      - Demo delle feature completate
      - Retrospective del team
      - Aggiornamento metriche
   
   2. **Sprint Planning** (Lunedì)
      - Selezione issue dal backlog
      - Stima story points
      - Assegnazione task ai team member
      - Definizione Definition of Done
   
   3. **Daily Standup** (ogni giorno)
      - Cosa ho fatto ieri
      - Cosa farò oggi
      - Ci sono blocchi?
   ```

10. **Crea le milestone del progetto**
    ```
    Milestone 1: MVP Core (4 settimane)
    - User authentication
    - Basic product catalog
    - Shopping cart functionality
    
    Milestone 2: Enhanced Features (4 settimane)
    - Advanced search
    - User profiles
    - Order management
    
    Milestone 3: Performance & Polish (4 settimane)
    - Performance optimization
    - UI/UX improvements
    - Testing & bug fixes
    ```

### Fase 6: Automation e Integrazione

11. **Configura GitHub Actions per automazione**
    
    **Workflow Auto-Assignment** (`.github/workflows/auto-assign.yml`):
    ```yaml
    name: Auto Assign Issues
    on:
      issues:
        types: [labeled]
    
    jobs:
      auto_assign:
        runs-on: ubuntu-latest
        steps:
          - name: Auto assign based on label
            uses: actions/github-script@v6
            with:
              script: |
                const label = context.payload.label.name;
                const issue = context.payload.issue;
                
                const assignments = {
                  'area/frontend': ['alice', 'bob'],
                  'area/backend': ['charlie', 'david'],
                  'area/testing': ['eve', 'frank'],
                  'area/design': ['grace']
                };
                
                if (assignments[label]) {
                  const assignee = assignments[label][0]; // Round-robin logic can be added
                  await github.rest.issues.addAssignees({
                    owner: context.repo.owner,
                    repo: context.repo.repo,
                    issue_number: issue.number,
                    assignees: [assignee]
                  });
                }
    ```

12. **Integra Slack per notifiche**
    ```yaml
    name: Slack Notifications
    on:
      issues:
        types: [opened, closed]
      pull_request:
        types: [opened, closed, ready_for_review]
    
    jobs:
      notify:
        runs-on: ubuntu-latest
        steps:
          - name: Send Slack notification
            uses: 8398a7/action-slack@v3
            with:
              status: ${{ job.status }}
              channel: '#webapp-dev'
              webhook_url: ${{ secrets.SLACK_WEBHOOK }}
    ```

## Deliverable dell'Esercizio

### Checklist di Completamento

**Configurazione Repository** ✅
- [ ] Repository creato con README, .gitignore, licenza
- [ ] Branch protection configurata
- [ ] Settings ottimizzate per team collaboration

**Sistema Issues** ✅
- [ ] 15+ label personalizzate create
- [ ] 3 template di issue configurati
- [ ] Milestone create per il progetto

**Project Management** ✅
- [ ] Project board con 6 colonne
- [ ] 6 custom fields configurati
- [ ] 4+ automazioni attive

**Team Setup** ✅
- [ ] Team GitHub creati
- [ ] Permessi configurati correttamente
- [ ] Workflow di collaborazione definito

**Automation** ✅
- [ ] GitHub Actions per auto-assignment
- [ ] Slack integration configurata
- [ ] Notification rules attive

### Metriche di Successo

**Setup Metrics**:
```
✅ Template Response Rate: >80%
✅ Auto-assignment Accuracy: >90%
✅ Project Board Usage: >95% delle issue
✅ Team Satisfaction: >4/5 rating
```

**Process Metrics**:
```
📊 Issue Resolution Time: <7 giorni (media)
📊 Sprint Completion Rate: >85%
📊 Code Review Time: <24 ore
📊 Bug Escape Rate: <5%
```

## Troubleshooting

### Problemi Comuni

**1. Permessi Insufficienti**
```bash
# Verifica permessi team
# Settings → Manage access → Teams
# Assicurati che ogni team abbia i permessi corretti
```

**2. Automazioni Non Funzionanti**
```bash
# Controlla GitHub Actions logs
# Actions tab → Select workflow → View logs
# Verifica che i secrets siano configurati
```

**3. Project Board Non Aggiorna**
```bash
# Verifica automation rules
# Project → Settings → Automations
# Test manualmente le regole
```

### Best Practices Implementate

1. **Clear Ownership**: Ogni area ha un team responsabile
2. **Automated Workflows**: Riduce il lavoro manuale
3. **Transparent Communication**: Tutti possono vedere lo stato
4. **Metrics-Driven**: Decisioni basate su dati
5. **Continuous Improvement**: Retrospective regolari

## Estensioni Avanzate

### Integrazione CI/CD
```yaml
# Aggiungi workflow per deployment automatico
# Integra quality gates nel project board
# Setup automated testing su PR
```

### Analytics Dashboard
```javascript
// Script per estrarre metriche del progetto
// Burndown charts automatici
// Performance team tracking
```

### Advanced Automation
```yaml
# Auto-labeling con AI
# Smart assignment basato su expertise
# Predictive sprint planning
```

---

**Tempo stimato**: 4-6 ore  
**Difficoltà**: Intermedio-Avanzato  
**Prerequisiti**: Conoscenza base GitHub, Project Management Agile
