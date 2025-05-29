# Labels e Organization

## 📖 Introduzione

I **labels** sono uno strumento fondamentale per l'organizzazione e la categorizzazione di Issues e Pull Request su GitHub. Un sistema di labeling ben progettato migliora drasticamente la gestione dei progetti, facilita la ricerca e aiuta i team a prioritizzare il lavoro.

I labels permettono di:
- **Categorizzare** Issues per tipo, priorità, area funzionale
- **Filtrare** rapidamente contenuto rilevante
- **Automatizzare** workflow attraverso GitHub Actions
- **Comunicare** stato e contesto visivamente

## 🏷️ Tipi di Labels

### Labels di Default

GitHub fornisce labels predefiniti che puoi personalizzare:

- **`bug`** - 🐛 Qualcosa non funziona correttamente
- **`enhancement`** - ✨ Nuova funzionalità o miglioramento
- **`documentation`** - 📚 Miglioramenti alla documentazione
- **`good first issue`** - 👶 Buono per newcomers
- **`help wanted`** - 🙋 Aiuto extra benvenuto
- **`question`** - ❓ Richiesta di informazioni

### Sistema di Categorizzazione Avanzato

#### Per Tipo di Issue

```
Type: Bug           🐛 #d73a4a
Type: Feature       ✨ #7057ff
Type: Documentation 📚 #0075ca
Type: Maintenance   🔧 #fbca04
Type: Security      🔒 #b60205
```

#### Per Priorità

```
Priority: Critical  🔥 #b60205
Priority: High      ⚡ #d93f0b
Priority: Medium    📊 #fbca04
Priority: Low       📝 #0e8a16
```

#### Per Area Funzionale

```
Area: Frontend      🎨 #1d76db
Area: Backend       ⚙️ #5319e7
Area: Database      🗄️ #0052cc
Area: Testing       🧪 #d4c5f9
Area: CI/CD         🚀 #0e8a16
```

#### Per Stato

```
Status: In Progress 🔄 #fbca04
Status: Blocked     🚫 #d93f0b
Status: Ready       ✅ #0e8a16
Status: Needs Review 👀 #1d76db
```

## ⚙️ Gestione Labels

### Creare Labels

```bash
# Tramite GitHub CLI
gh label create "Priority: Critical" --color "b60205" --description "Critical priority issues"

# Tramite interfaccia web
# Repository → Issues → Labels → New label
```

### Modificare Labels Esistenti

```bash
# Rinominare label
gh label edit "bug" --name "Type: Bug" --color "d73a4a"

# Cambiare colore
gh label edit "enhancement" --color "7057ff"

# Aggiornare descrizione
gh label edit "documentation" --description "Improvements to documentation"
```

### Eliminare Labels

```bash
# Elimina label (attenzione: rimuove da tutte le issues)
gh label delete "duplicate"

# Lista tutti i labels
gh label list
```

## 🎨 Schema Colori Efficace

### Principi di Design

1. **Consistenza**: Usa famiglie di colori per categorie
2. **Contrasto**: Assicura leggibilità su sfondo chiaro/scuro
3. **Significato**: I colori dovrebbero avere significato intuitivo

### Palette Raccomandata

```css
/* Criticità */
Critical: #b60205    /* Rosso scuro */
High:     #d93f0b    /* Arancione */
Medium:   #fbca04    /* Giallo */
Low:      #0e8a16    /* Verde */

/* Tipologia */
Bug:      #d73a4a    /* Rosso */
Feature:  #7057ff    /* Viola */
Docs:     #0075ca    /* Blu */
Test:     #d4c5f9    /* Lavanda */

/* Stato */
Open:     #28a745    /* Verde */
Progress: #fd7e14    /* Arancione */
Review:   #6f42c1    /* Viola */
Blocked:  #dc3545    /* Rosso */
```

## 📊 Strategie di Organizzazione

### 1. Sistema Gerarchico

```
Category/Subcategory
├── Type/Bug
├── Type/Feature
├── Priority/High
├── Priority/Low
└── Area/Frontend
```

### 2. Sistema di Prefissi

```
bug: Login issue
feat: Add dark mode
docs: Update API reference
test: Add unit tests
```

### 3. Sistema di Emoji

```
🐛 Bug
✨ Enhancement
📚 Documentation
🚀 Feature
🔧 Maintenance
```

## 🔍 Filtri e Ricerche

### Filtri Comuni

```bash
# Issues con label specifico
is:issue label:"Type: Bug"

# Multiple labels (AND)
is:issue label:"Priority: High" label:"Type: Bug"

# Multiple labels (OR)
is:issue label:"Priority: High","Priority: Critical"

# Escludere labels
is:issue -label:"Status: Closed"

# Combina con altri filtri
is:open is:issue assignee:@me label:"Priority: High"
```

### Query Avanzate

```bash
# Issues aperte senza labels
is:issue is:open no:label

# Issues con più di 2 labels
is:issue label:* label:* label:*

# Issues create questa settimana con label bug
is:issue created:>=$(date -d "1 week ago" +%Y-%m-%d) label:bug
```

## 🤖 Automazione con Labels

### GitHub Actions Esempi

#### Auto-labeling per PR

```yaml
name: Auto Label PR
on:
  pull_request:
    types: [opened]

jobs:
  label:
    runs-on: ubuntu-latest
    steps:
    - name: Label based on files
      uses: actions/github-script@v6
      with:
        script: |
          const { data: files } = await github.rest.pulls.listFiles({
            owner: context.repo.owner,
            repo: context.repo.repo,
            pull_number: context.issue.number
          });
          
          const labels = [];
          
          if (files.some(f => f.filename.includes('frontend/'))) {
            labels.push('Area: Frontend');
          }
          if (files.some(f => f.filename.includes('backend/'))) {
            labels.push('Area: Backend');
          }
          if (files.some(f => f.filename.includes('.md'))) {
            labels.push('Type: Documentation');
          }
          
          if (labels.length > 0) {
            await github.rest.issues.addLabels({
              owner: context.repo.owner,
              repo: context.repo.repo,
              issue_number: context.issue.number,
              labels: labels
            });
          }
```

#### Auto-close con Labels

```yaml
name: Auto Close Stale
on:
  schedule:
    - cron: '0 0 * * *'

jobs:
  stale:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/stale@v4
      with:
        stale-issue-label: 'Status: Stale'
        close-issue-label: 'Status: Closed'
        stale-issue-message: 'This issue is stale and will be closed soon'
        days-before-stale: 30
        days-before-close: 7
```

## 📋 Templates con Labels

### Issue Template

```markdown
---
name: Bug Report
about: Create a report to help us improve
title: '[BUG] '
labels: ['Type: Bug', 'Status: Triage']
assignees: ''
---

## Bug Description
<!-- Clear description of the bug -->

## Steps to Reproduce
1. Go to '...'
2. Click on '....'
3. See error

## Expected Behavior
<!-- What you expected to happen -->

## Labels
- [ ] I have added appropriate labels
- [ ] I have set priority level
```

### PR Template

```markdown
---
name: Feature PR
about: Submit a new feature
title: '[FEAT] '
labels: ['Type: Feature', 'Status: Review']
---

## Changes Made
<!-- List of changes -->

## Testing
<!-- How was this tested -->

## Labels Applied
- [ ] Type label added
- [ ] Priority set if applicable
- [ ] Area label added
```

## 📊 Metriche e Reporting

### GitHub CLI Queries

```bash
# Conta issues per label
gh issue list --label "Type: Bug" --state all --json number | jq length

# Issues aperte per priorità
gh issue list --label "Priority: High" --state open --json title,number,labels

# Report mensile
gh issue list --search "created:$(date -d '1 month ago' +%Y-%m-%d)..$(date +%Y-%m-%d)" --json labels,createdAt
```

### Script di Analisi

```javascript
// Analisi distribuzione labels
const issues = await octokit.issues.listForRepo({
  owner: 'user',
  repo: 'repo',
  state: 'all'
});

const labelStats = {};
issues.data.forEach(issue => {
  issue.labels.forEach(label => {
    labelStats[label.name] = (labelStats[label.name] || 0) + 1;
  });
});

console.log('Label Usage:', labelStats);
```

## 🚨 Problemi Comuni e Soluzioni

### Label Sprawl

**Problema**: Troppi labels creati senza strategia

**Soluzione**:
```bash
# Audit periodico
gh label list | wc -l  # Conta labels totali

# Rimuovi labels non utilizzati
gh issue list --label "unused-label" --state all --json number | jq length
# Se 0, considera rimozione
```

### Inconsistenza Naming

**Problema**: Nomi di label inconsistenti

**Soluzione**:
```bash
# Standardizza naming convention
gh label edit "bug" --name "Type: Bug"
gh label edit "enhancement" --name "Type: Enhancement"
gh label edit "priority-high" --name "Priority: High"
```

### Labels Mancanti su Issues

**Problema**: Issues senza categorizzazione

**Soluzione**:
```bash
# Trova issues senza labels
gh issue list --search "no:label is:open" --json number,title

# Template con labels predefiniti
# Automation per auto-labeling
```

## 📋 Best Practices

### 1. Sistema Scalabile

```bash
# Inizia semplice
Type: Bug, Type: Feature, Priority: High, Priority: Low

# Espandi gradualmente
Area: Frontend, Area: Backend
Status: In Progress, Status: Blocked
```

### 2. Documentazione Labels

```markdown
# Label Guide

## Type Labels
- `Type: Bug` - Something isn't working
- `Type: Feature` - New feature or request
- `Type: Documentation` - Improvements to docs

## Priority Labels
- `Priority: Critical` - Blocking/Security issue
- `Priority: High` - Important feature/fix
- `Priority: Medium` - Standard priority
- `Priority: Low` - Nice to have
```

### 3. Training del Team

```markdown
# Onboarding Checklist
- [ ] Read label documentation
- [ ] Understand label hierarchy  
- [ ] Practice filtering issues
- [ ] Know when to create new labels
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la differenza tra usare un sistema di prefissi vs un sistema gerarchico per i labels?**

<details>
<summary>Risposta</summary>

**Sistema di Prefissi**: Usa prefissi come "Type:", "Priority:" per raggruppare logicamente i labels. Più leggibile e organizzato, facilita la ricerca.

**Sistema Gerarchico**: Usa separatori come "/" per creare categorie annidate. Più flessibile ma può diventare complesso.

Raccomandazione: Usa prefissi per la maggior parte dei progetti, gerarchico solo per progetti molto complessi.

</details>

### Domanda 2
**Come creeresti un sistema di auto-labeling per PR che modificano file di test?**

<details>
<summary>Risposta</summary>

```yaml
- name: Auto-label tests
  if: contains(github.event.pull_request.title, 'test') || 
      contains(join(github.event.pull_request.changed_files, ' '), '.test.')
  run: |
    gh pr edit ${{ github.event.number }} --add-label "Type: Test"
```

Oppure usando GitHub Actions con controllo sui file modificati.

</details>

### Domanda 3
**Quale strategia useresti per un progetto con team distribuito su più timezone?**

<details>
<summary>Risposta</summary>

```
Priority: Urgent      (Richiede attenzione immediata)
Priority: Same Day    (Da completare in giornata)
Priority: This Week   (Da completare nella settimana)
Priority: Next Sprint (Per planning futuro)

Region: EMEA, Region: APAC, Region: Americas
```

Questo aiuta a coordinare il lavoro considerando i fusi orari.

</details>

## 🛠️ Esercizio Pratico

### Obiettivo
Implementare un sistema di labeling completo per un progetto web.

### Passi

1. **Analisi Requirements**:
   ```bash
   # Identifica categorie necessarie
   # - Tipi di issue (bug, feature, docs)
   # - Priorità (critical, high, medium, low)  
   # - Aree (frontend, backend, database, ci/cd)
   # - Stati (triage, in-progress, review, done)
   ```

2. **Creazione Labels**:
   ```bash
   # Crea set base
   gh label create "Type: Bug" --color "d73a4a" --description "Something isn't working"
   gh label create "Type: Feature" --color "7057ff" --description "New feature request"
   gh label create "Priority: High" --color "d93f0b" --description "High priority"
   
   # Continua con tutte le categorie
   ```

3. **Template Setup**:
   ```markdown
   # Crea .github/ISSUE_TEMPLATE/bug_report.md
   # Con labels predefiniti nel frontmatter
   ```

4. **Automation**:
   ```yaml
   # Crea workflow per auto-labeling
   # Basato su file modificati, keywords, etc.
   ```

5. **Testing e Refinement**:
   ```bash
   # Crea alcune issues di test
   # Verifica filtri funzionano correttamente
   # Affina sistema basato su feedback
   ```

### Verifica Risultati

Il completamento dell'esercizio dimostra:
- ✅ Sistema di labeling coerente e scalabile
- ✅ Automation funzionante per labeling
- ✅ Templates con labels predefiniti
- ✅ Documentazione del sistema per il team

## 🔗 Link Correlati

- [01 - GitHub Issues](./01-github-issues.md) - Fondamentali degli Issues
- [03 - GitHub Projects](./03-github-projects.md) - Project management avanzato
- [04 - Automation](./04-automation.md) - Automazione workflow

---

### 🧭 Navigazione

- **⬅️ Precedente**: [01 - GitHub Issues](./01-github-issues.md)
- **🏠 Home Modulo**: [README.md](../README.md)
- **➡️ Successivo**: [03 - GitHub Projects](./03-github-projects.md)
