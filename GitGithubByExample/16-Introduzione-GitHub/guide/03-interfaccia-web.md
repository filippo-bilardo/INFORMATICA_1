# 03 - Interfaccia Web GitHub

## 📖 Spiegazione Concettuale

L'**interfaccia web di GitHub** è il punto di accesso principale per gestire repository, collaborare con altri sviluppatori e utilizzare le funzionalità avanzate della piattaforma. Comprendere come navigare efficacemente l'interfaccia web è fondamentale per sfruttare al massimo GitHub.

### Perché è Importante l'Interfaccia Web?

Mentre Git è principalmente uno strumento da linea di comando, GitHub offre un'interfaccia grafica potente che:
- **Semplifica la collaborazione** attraverso Pull Request e Issues
- **Visualizza la cronologia** del progetto in modo intuitivo  
- **Fornisce strumenti** per il project management
- **Facilita la code review** con diff visuali
- **Integra servizi** come CI/CD e deployment

## 🌐 Anatomia della Home Page

### Navigazione Principale
```
[GitHub Logo] [Search] [Pull requests] [Issues] [Marketplace] [Explore] [Avatar]
└── Barra di navigazione globale sempre presente
```

**Elementi Chiave:**
- **Search Bar**: Ricerca globale per repository, codice, utenti
- **Pull Requests**: Le tue PR attive e assegnate
- **Issues**: Issues aperti su progetti che segui
- **Marketplace**: Actions e Apps di terze parti
- **Explore**: Scopri progetti trending e raccomandazioni

### Dashboard Personale
```
Dashboard Layout:
├── Sidebar (Repository, Teams, Organizations)
├── Recent Activity Feed
├── Repository Overview
└── Contribution Graph
```

## 📁 Anatomia di un Repository

### Header Repository
```
username/repository-name [★ Star] [👁 Watch] [🍴 Fork]
├── 📊 [Insights] [⚙️ Settings] [🔒 Security]
└── [📝 README] [📄 License] [🔗 Website]
```

### Tabs Principali
1. **Code**: Codice sorgente e file del progetto
2. **Issues**: Bug reports e feature requests
3. **Pull Requests**: Proposte di modifica
4. **Actions**: CI/CD workflows
5. **Projects**: Project management boards
6. **Wiki**: Documentazione estesa
7. **Security**: Vulnerabilità e analisi sicurezza
8. **Insights**: Analytics e statistiche
9. **Settings**: Configurazioni repository

## 🔍 Navigazione del Codice

### File Browser
```
Repository Root:
├── 📁 src/
├── 📁 docs/
├── 📄 README.md
├── 📄 package.json
├── 📄 .gitignore
└── 📄 LICENSE
```

**Funzionalità Avanzate:**
- **Keyboard shortcuts**: `t` per file finder, `b` per blame view
- **Permalink**: Link permanenti a righe specifiche
- **Raw view**: Visualizzazione file senza formattazione
- **History**: Cronologia modifiche di ogni file

### Code Navigation
```bash
# Shortcut utili per navigazione codice
t          # File finder (fuzzy search)
b          # Blame view (chi ha modificato cosa)
l          # Vai a riga specifica
w          # Branch/tag switcher
y          # Permalink alla riga corrente
```

## 👥 Features Collaborative

### Issues Interface
```
Issue #123: "Bug in user authentication"
├── 📝 Description (Markdown support)
├── 🏷️ Labels (bug, priority-high, backend)
├── 👤 Assignees (developers responsible)  
├── 📋 Projects (project board association)
├── 🏃 Milestone (release target)
└── 💬 Comments Thread
```

### Pull Request Interface
```
PR #45: "Add user profile feature"  
├── 📊 Overview (Files changed, commits)
├── 💬 Conversation (review comments)
├── 📝 Commits (commit history)
├── 📄 Files changed (diff view)
└── ✅ Checks (CI/CD results)
```

## ⚙️ Repository Settings

### General Settings
- **Repository name** e description
- **Visibility** (public/private)
- **Features** (Wiki, Issues, Projects)
- **Merge options** (merge commits, squash, rebase)

### Branch Protection
```yaml
Branch Protection Rules:
- Require pull request reviews
- Require status checks
- Require branches to be up to date
- Require signed commits
- Restrict pushes to matching branches
```

### Access Control
- **Collaborators**: Aggiungi sviluppatori
- **Teams**: Organizza permessi per gruppi
- **Deploy keys**: SSH keys per deployment
- **Webhooks**: Integrazioni esterne

## 🎨 Personalizzazione Profilo

### Profile README
```markdown
<!-- Special repository: username/username -->
# Hi there 👋

I'm a developer passionate about:
- 🔭 I'm currently working on [Project Name]
- 🌱 I'm currently learning React Native
- 👯 I'm looking to collaborate on open source
- 📫 How to reach me: email@example.com

## My Tech Stack
![JavaScript](https://img.shields.io/badge/-JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black)
![React](https://img.shields.io/badge/-React-61DAFB?style=flat-square&logo=react&logoColor=black)
```

### Contribution Graph
```
Contribution Activity:
[Green squares showing daily contributions]
├── Commits to repositories
├── Issues opened  
├── Pull requests submitted
└── Code reviews given
```

## 🔔 Notifiche e Monitoring

### Notification Center
```
Notifications Types:
├── 👁️ Repository watching (all activity)
├── 🔔 Participating (mentions, assignments)
├── 📧 Email preferences
└── 📱 Mobile notifications
```

### Watch Settings
- **Participating and @mentions**: Solo quando coinvolto
- **All Activity**: Ogni push, issue, PR
- **Ignore**: Nessuna notifica
- **Custom**: Seleziona eventi specifici

## 📊 Analytics e Insights

### Repository Insights
```
Insights Dashboard:
├── 📈 Pulse (activity overview)
├── 👥 Contributors (code contributions)  
├── 🚀 Traffic (page views, clones)
├── 📦 Releases (download statistics)
├── 🌐 Dependency graph
└── 🛡️ Security advisories
```

### Network Graph
Visualizzazione delle biforcazioni e merge del progetto, utile per:
- Comprendere la struttura di branching
- Identificare contributor attivi
- Tracciare origine delle modifiche

## ⚠️ Errori Comuni Interfaccia

### 1. Editing Diretto su Main
```bash
# ❌ ERRORE: Modificare file direttamente su main via web
# Click "Edit" su file in main branch

# ✅ SOLUZIONE: Crea branch o fork
# Use "Create a new branch for this commit"
```

### 2. Commit Messages Poveri
```bash
# ❌ ERRORE: Messaggi generici via web editor
"Update file"
"Fix bug" 
"Changes"

# ✅ SOLUZIONE: Messaggi descrittivi
"feat: add user authentication system
- Implement JWT token validation
- Add login/logout endpoints
- Update middleware for protected routes"
```

### 3. File Troppo Grandi
```bash
# ❌ ERRORE: Upload file >100MB via web
# GitHub rifiuterà il file

# ✅ SOLUZIONE: Git LFS o alternative
git lfs track "*.zip"
git add .gitattributes
git add large-file.zip
git commit -m "Add large file with LFS"
```

### 4. Conflitti di Merge via Web
```bash
# ❌ ERRORE: Tentare merge complessi via web
# Pull Request con molti conflitti

# ✅ SOLUZIONE: Risolvi localmente
git checkout feature-branch
git rebase main
# Risolvi conflitti
git push --force-with-lease
```

## 💡 Tips e Shortcuts

### Keyboard Shortcuts Globali
```bash
s          # Focus search bar
g c        # Go to Code tab
g i        # Go to Issues  
g p        # Go to Pull requests
g b        # Go to Projects
g w        # Go to Wiki
?          # Show all shortcuts
```

### URL Shortcuts
```bash
# Shortcut URLs utili
github.com/user/repo/issues/new
github.com/user/repo/compare/main...feature
github.com/user/repo/releases/new
github.com/user/repo/settings/keys
```

### Advanced Search
```bash
# Sintassi di ricerca avanzata
user:username language:javascript
org:github stars:>1000
created:2023-01-01..2023-12-31
is:issue is:open label:bug
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la differenza tra "Watch" e "Star" su un repository?**

<details>
<summary>Risposta</summary>

**Star** è come un bookmark che mostra apprezzamento per il progetto. **Watch** ti iscrive alle notifiche del repository - riceverai aggiornamenti su Issues, PR e releases. Star è per mostrare interesse, Watch è per rimanere aggiornato.
</details>

### Domanda 2
**Come puoi visualizzare chi ha modificato una riga specifica di codice?**

<details>
<summary>Risposta</summary>

Usa la **Blame view** premendo `b` mentre visualizzi un file, oppure clicca su "Blame" nell'interfaccia. Questo mostra per ogni riga quale commit (e quindi quale autore) l'ha modificata per ultima.
</details>

### Domanda 3
**Quali sono i 3 tipi principali di notifiche su GitHub?**

<details>
<summary>Risposta</summary>

1. **Participating**: Quando sei menzionato o assegnato
2. **Watching**: Attività sui repository che stai seguendo  
3. **Custom**: Eventi specifici che selezioni per repository specifici
</details>

### Domanda 4
**Come crei un link permanente a una riga specifica di codice?**

<details>
<summary>Risposta</summary>

Clicca sul numero della riga per selezionarla, poi premi `y` per generare un permalink con l'hash del commit. Oppure clicca sul numero della riga e copia l'URL che si aggiorna automaticamente.
</details>

## 🛠️ Esercizio Pratico: Esplorazione Interfaccia

### Parte 1: Navigazione Base
```bash
# 1. Esplora un repository popolare (es: facebook/react)
# 2. Identifica i seguenti elementi:
#    - Numero di stars e fork
#    - Ultima data di commit
#    - Linguaggio principale
#    - Numero di contributors

# 3. Naviga nelle seguenti sezioni:
#    - Issues (quanti aperti?)
#    - Pull Requests (pattern nei titoli?)
#    - Actions (workflows attivi?)
#    - Insights (picchi di attività?)
```

### Parte 2: Code Navigation
```bash
# 1. In un repository a scelta:
#    - Usa 't' per il file finder
#    - Cerca un file JavaScript
#    - Usa 'b' per vedere blame view
#    - Identifica la modifica più recente

# 2. Crea un permalink:
#    - Vai a una riga specifica
#    - Premi 'y' per permalink
#    - Condividi l'URL generato
```

### Parte 3: Repository Analysis
```bash
# 1. Scegli 3 repository di tecnologie diverse
# 2. Confronta le loro strutture:
#    - Come è organizzato il README?
#    - Quali labels usano per Issues?
#    - Che template PR hanno?
#    - Come gestiscono le release?

# 3. Identifica best practices comuni
```

## 🔗 Navigazione

**Precedente:** [02 - Account e Configurazione](./02-account-configurazione.md)  
**Successivo:** [04 - Repository su GitHub](./04-repository-github.md)  
**Torna all'Indice:** [README del Modulo](../README.md)  
**Corso Principale:** [Git e GitHub by Example](../../README.md)

## 📚 Risorse Aggiuntive

- [GitHub Web Interface Guide](https://docs.github.com/en/get-started/using-github)
- [GitHub Keyboard Shortcuts](https://docs.github.com/en/get-started/using-github/keyboard-shortcuts)
- [GitHub Search Syntax](https://docs.github.com/en/search-github/searching-on-github)
- [GitHub Notifications](https://docs.github.com/en/account-and-profile/managing-subscriptions-and-notifications-on-github)
