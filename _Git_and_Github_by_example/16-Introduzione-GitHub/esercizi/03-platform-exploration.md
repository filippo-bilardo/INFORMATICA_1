# Esercizio: Esplorazione Completa della Piattaforma GitHub

## Obiettivo
Esplorare sistematicamente tutte le funzionalità di GitHub attraverso attività pratiche guidate, sviluppando familiarità con l'ecosistema completo della piattaforma.

## Prerequisiti
- Account GitHub configurato
- Repository di test creati
- Conoscenza base di Git
- Browser web moderno

## Parte 1: Navigazione e Interfaccia

### Task 1.1: Homepage e Discovery
```
1. Vai alla homepage di GitHub (da loggato)
2. Esplora la dashboard principale
3. Analizza le sezioni:
   - Recent activity
   - Repositories you contribute to
   - Recent repositories
   - Recommended for you
```

**Scorciatoie da provare:**
```
g h    → Vai alla homepage
g n    → Vai alle notifiche  
g p    → Vai al profilo
g d    → Vai alla dashboard
```

### Task 1.2: Explore Features
```
1. Clicca su "Explore" nella nav bar
2. Esplora le sezioni:
   - Trending repositories (oggi, settimana, mese)
   - Topics (linguaggi, framework, argomenti)
   - Collections (raccolte curate)
   - Events (eventi GitHub)
```

**Attività pratiche:**
- [ ] Trova 3 repository trending in JavaScript
- [ ] Explora 2 topics di tuo interesse
- [ ] Salva 5 repository interessanti nei tuoi "stars"

### Task 1.3: Search Avanzata
```
Prova queste ricerche avanzate:

1. Repository per linguaggio:
   language:python stars:>1000

2. Repository recenti:
   created:2023-01-01..2023-12-31 language:typescript

3. Issue aperti:
   is:issue is:open label:bug language:javascript

4. Pull request recenti:
   is:pr is:merged merged:2023-01-01..2023-12-31

5. Utenti per location:
   type:user location:italy followers:>100
```

**Challenge:** Trova un repository che soddisfa questi criteri:
- Python
- Più di 500 stars
- Aggiornato negli ultimi 6 mesi
- Con buona documentazione

## Parte 2: Repository Features

### Task 2.1: Code Navigation
Scegli un repository grande (es. Microsoft/vscode) e prova:

```
1. File Explorer:
   - Naviga tra le cartelle
   - Usa la ricerca file (t)
   - Visualizza diversi branch

2. Code Reading:
   - Clicca su funzioni per vedere definizioni
   - Usa "Go to definition"
   - Trova tutti i references di una funzione

3. Blame e History:
   - git blame per vedere chi ha modificato ogni riga
   - History di un file specifico
   - Compare tra branch diversi
```

**Scorciatoie Code Navigation:**
```
t       → Attiva file finder
s       → Focus su search
l       → Vai a una linea specifica
b       → Apri blame view
.       → Apri in github.dev (VS Code web)
```

### Task 2.2: Issues e Project Management
```
1. Repository con Issues attive:
   - Filtra per label
   - Filtra per assignee
   - Filtra per milestone
   - Ordina per data/commenti

2. Crea Issue di test:
   - Usa template se disponibile
   - Aggiungi labels appropriate
   - Menziona utenti con @
   - Collega a milestone

3. Commenta su Issue esistente:
   - Usa markdown per formattazione
   - Aggiungi code snippets
   - Usa emoji reactions
```

**Issue Search Syntax:**
```
is:issue is:open author:username
is:issue is:closed label:bug
is:issue assignee:@me
is:issue milestone:"v2.0"
is:issue involves:username
```

### Task 2.3: Pull Requests e Code Review
```
1. Esplora PR aperti:
   - Leggi description
   - Analizza i file modificati
   - Guarda le conversazioni
   - Verifica i checks automatici

2. Processo di Review:
   - Leggi il codice modificato
   - Comprendi i commenti di review
   - Guarda approved/requested changes
   - Analizza i merge conflicts (se presenti)

3. PR Templates e Automations:
   - Osserva template di PR
   - Verifica checks automatici
   - Guarda integrations (CI/CD)
```

## Parte 3: Social Features

### Task 3.1: Following e Stars
```
1. Sistema di Following:
   - Segui 5 sviluppatori interessanti
   - Analizza i loro profili
   - Guarda cosa stanno sviluppando
   - Osserva i loro contribution patterns

2. Stars Management:
   - Organizza stars per topic
   - Crea lists personalizzate
   - Usa stars come bookmarks
   - Esplora stars di altri utenti

3. Watching Repositories:
   - Configura watching per repository importanti
   - Imposta notifiche personalizzate
   - Gestisci subscription settings
```

### Task 3.2: Community Features
```
1. Discussions:
   - Trova repository con Discussions abilitate
   - Partecipa a Q&A
   - Leggi announcements
   - Condividi in "Show and tell"

2. Sponsor e Support:
   - Esplora GitHub Sponsors
   - Analizza come developers raccolgono fondi
   - Comprendi i tiers di sponsorship

3. Community Standards:
   - Analizza community guidelines
   - Controlla code of conduct
   - Verifica contributing guidelines
```

## Parte 4: Developer Tools

### Task 4.1: GitHub CLI
```bash
# Installazione (se non fatto)
# Windows: winget install GitHub.cli
# macOS: brew install gh
# Linux: apt install gh

# Autenticazione
gh auth login

# Esplorazione comandi
gh repo list                    # Lista i tuoi repo
gh repo view microsoft/vscode   # Info su repository
gh issue list                   # Issues dei tuoi repo
gh pr list                      # Le tue PR

# Repository operations
gh repo create test-cli-repo --public
gh repo clone username/repo-name
gh repo fork popular-repo

# Issues e PR
gh issue create --title "Test issue" --body "Test description"
gh pr create --title "New feature" --body "Feature description"
gh pr checkout 123  # Checkout PR by number

# Avanzato
gh api user  # API calls dirette
gh extension list  # CLI extensions
```

### Task 4.2: GitHub Mobile
```
1. Installa GitHub Mobile
2. Configura notifiche push
3. Prova features:
   - Browse repositories
   - Read e comment su issues
   - Review pull requests
   - Merge PR (se hai permessi)
   - Manage notifications

4. Quick Actions:
   - Star repository
   - Watch/unwatch
   - Follow users
   - Share repository links
```

### Task 4.3: GitHub Desktop
```
1. Installa GitHub Desktop (opzionale)
2. Connetti al tuo account GitHub
3. Clone repository
4. Prova workflow:
   - Visualizza changes
   - Create commits
   - Sync con remote
   - Manage branches

5. Advanced features:
   - Interactive rebase
   - Cherry-pick commits
   - Stash changes
```

## Parte 5: Automation e Integrations

### Task 5.1: GitHub Actions
```
1. Esplora tab Actions:
   - Workflow runs
   - Workflow templates
   - Marketplace actions
   - Runners status

2. Marketplace exploration:
   - Browse per categoria
   - Leggi descriptions e usage
   - Guarda popularity e reviews
   - Analizza code degli actions

3. Workflow examples:
   - CI/CD pipelines
   - Automated testing
   - Code quality checks
   - Deployment automation
```

### Task 5.2: Integrations e Apps
```
1. GitHub Marketplace:
   - Browse apps per categoria
   - Leggi reviews e pricing
   - Analizza permissions richieste
   - Testa free tiers

2. Popular integrations:
   - Slack (notifications)
   - Jira (project management)
   - CodeClimate (code quality)
   - Netlify (deployment)
   - Dependabot (security)

3. Personal access tokens:
   - Crea token per API access
   - Configura scopes appropriati
   - Testa con API calls
```

### Task 5.3: Webhooks e API
```bash
# GitHub API exploration
curl -H "Authorization: token YOUR_TOKEN" \
     https://api.github.com/user

# Repository info
curl -H "Authorization: token YOUR_TOKEN" \
     https://api.github.com/repos/owner/repo

# Issues di un repository
curl https://api.github.com/repos/microsoft/vscode/issues

# User info pubbliche
curl https://api.github.com/users/octocat
```

## Parte 6: Security e Privacy

### Task 6.1: Security Features
```
1. Security tab exploration:
   - Dependabot alerts
   - Code scanning alerts
   - Secret scanning
   - Security advisories

2. Settings di sicurezza:
   - Two-factor authentication
   - SSH keys management
   - Personal access tokens
   - Authorized applications

3. Privacy settings:
   - Profile visibility
   - Email privacy
   - Contribution visibility
   - Block users functionality
```

### Task 6.2: Organization Security
```
Se hai accesso a un'organizzazione:

1. Member management:
   - Team creation e management
   - Permission levels
   - Outside collaborators
   - SAML/SSO settings

2. Repository security:
   - Branch protection rules
   - Required status checks
   - Deployment protection
   - Secret management
```

## Parte 7: Advanced Features

### Task 7.1: GitHub Codespaces
```
1. Crea nuovo Codespace:
   - Scegli repository con dev container
   - Configura machine type
   - Avvia development environment

2. Desenvolvimento nel browser:
   - VS Code interface nel browser
   - Terminal access
   - Extension management
   - File editing e Git operations

3. Management:
   - Stop/start codespaces
   - Configure settings
   - Monitor usage e billing
```

### Task 7.2: GitHub Packages
```
1. Package registry exploration:
   - npm packages
   - Docker containers
   - Maven packages
   - NuGet packages

2. Publishing workflow:
   - Setup package.json per npm
   - Configure GitHub Actions per publishing
   - Version management
   - Download statistics

3. Security scanning:
   - Vulnerability detection
   - Automated security updates
   - Package insights
```

### Task 7.3: GitHub Education e Learning
```
1. GitHub Skills:
   - Complete guided tutorials
   - Interactive learning paths
   - Skill verification

2. GitHub Education:
   - Student Developer Pack (se applicabile)
   - Campus program
   - Teacher benefits

3. Learning resources:
   - GitHub Docs
   - GitHub Blog
   - YouTube channel
   - Community forum
```

## Checklist di Completamento

### Basic Navigation
- [ ] Dashboard e homepage esplorata
- [ ] Search avanzata utilizzata
- [ ] Trending repositories analizzati
- [ ] Scorciatoie da tastiera imparate

### Repository Features
- [ ] Code navigation avanzata utilizzata
- [ ] Issues filtrati e analizzati
- [ ] Pull requests reviewed
- [ ] File history esplorato

### Social Features
- [ ] 5+ utenti seguiti
- [ ] 10+ repository con star
- [ ] Discussions esplorate
- [ ] Community standards compresi

### Developer Tools
- [ ] GitHub CLI installato e testato
- [ ] GitHub Mobile configurato
- [ ] API GitHub testata
- [ ] Personal access token creato

### Advanced Features
- [ ] GitHub Actions esplorato
- [ ] Marketplace apps analizzate
- [ ] Security features configurate
- [ ] Integration testata

### Learning
- [ ] GitHub Skills completato
- [ ] Documentation letta
- [ ] Blog posts letti
- [ ] Community participate

## Quiz di Verifica

### Domande Tecniche
1. Quale scorciatoia apre il file finder?
2. Come cerchi repository Python con più di 1000 stars?
3. Qual è la differenza tra Watch e Star?
4. Come si fa checkout di una PR con GitHub CLI?
5. Dove trovi le security vulnerability alerts?

### Domande Pratiche
1. Come organizzeresti un team di 10 sviluppatori su GitHub?
2. Quale workflow useresti per contribuire a un progetto open source?
3. Come automatizzeresti il deployment di un'app web?
4. Come configureresti le notifiche per non essere sopraffatto?
5. Quale strategia useresti per mantenere un repository sicuro?

## Progetti Post-Esplorazione

### Beginner Projects
1. **Profile README Avanzato**: Con stats, badges, animations
2. **Awesome List**: Lista curata di risorse per un topic
3. **GitHub Pages Portfolio**: Sito professionale con progetti

### Intermediate Projects  
1. **Open Source Contribution**: Contribuisci a 3 progetti
2. **CLI Tool**: Strumento che usa GitHub API
3. **GitHub Action Custom**: Action riutilizzabile

### Advanced Projects
1. **GitHub App**: App che si integra con webhook
2. **Organization Management**: Setup completo per team
3. **DevOps Pipeline**: CI/CD completo con Actions

## Risorse per Approfondimento

### Documentation
- [GitHub Docs](https://docs.github.com) - Documentazione ufficiale
- [GitHub API](https://docs.github.com/en/rest) - Reference API
- [GitHub CLI Manual](https://cli.github.com/manual) - Guida CLI

### Learning Platforms
- [GitHub Skills](https://skills.github.com) - Tutorial interattivi
- [GitHub Training](https://training.github.com) - Corsi ufficiali
- [Git Handbook](https://guides.github.com/introduction/git-handbook/) - Guida Git

### Community
- [GitHub Community](https://github.community) - Forum ufficiale
- [GitHub Blog](https://github.blog) - News e updates
- [GitHub YouTube](https://youtube.com/github) - Video tutorials

### Advanced Topics
- [GitHub Enterprise](https://enterprise.github.com) - Soluzioni enterprise
- [GitHub Security](https://github.com/security) - Best practices sicurezza
- [GitHub Developer](https://developer.github.com) - API e integrazioni

## Conclusione

Hai completato un'esplorazione approfondita di GitHub! Ora dovresti avere:

1. **Familiarità completa** con l'interfaccia e le funzionalità
2. **Competenze pratiche** nell'uso quotidiano della piattaforma
3. **Conoscenza avanzata** di features per collaboration e automation
4. **Preparazione** per utilizzare GitHub professionalmente

### Prossimi Passi
1. **Pratica costante**: Usa GitHub per tutti i tuoi progetti
2. **Contribuzioni open source**: Inizia a contribuire a progetti
3. **Automation**: Implementa GitHub Actions nei tuoi workflow
4. **Community**: Partecipa attivamente alla community GitHub
5. **Continua apprendimento**: Tieni aggiornato con nuove features

Ricorda: GitHub è una piattaforma in continua evoluzione. Mantieni la curiosità e continua ad esplorare nuove funzionalità man mano che vengono rilasciate!
