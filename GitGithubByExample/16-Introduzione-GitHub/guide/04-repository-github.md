# Guida: Repository GitHub

## Introduzione
I repository GitHub sono il cuore della piattaforma: spazi centralizzati dove vengono archiviati, gestiti e condivisi progetti di sviluppo software.

## Che cosa è un Repository GitHub

### Definizione
Un repository GitHub è una directory di progetto che contiene:
- **Codice sorgente** del progetto
- **Cronologia completa** delle modifiche (Git history)
- **Documentazione** (README, wiki, docs)
- **Issues e discussioni** per tracking
- **Strumenti di collaborazione** integrati

### Differenza Git vs GitHub Repository

```bash
# Repository Git locale
git init my-project     # Solo sul tuo computer
git add .
git commit -m "initial commit"

# Repository GitHub (remoto)
# Accessibile online, condivisibile, con features aggiuntive
```

## Tipi di Repository

### Repository Pubblici
- **Visibili a tutti** su internet
- **Gratuiti** e illimitati
- Ideali per **open source**
- **Indicizzati** dai motori di ricerca

### Repository Privati
- **Visibili solo** ai collaboratori autorizzati
- **Gratuiti** per account personali (limite collaboratori)
- **A pagamento** per team enterprises
- Per **progetti commerciali** o sensibili

### Repository Template
- **Modelli** per nuovi progetti
- Include struttura, configurazioni, workflow
- Facilita **standardizzazione** team

## Anatomia di un Repository GitHub

### Struttura Base
```
repository-name/
├── README.md              # Documentazione principale
├── .gitignore            # File da ignorare
├── LICENSE               # Licenza del progetto
├── src/                  # Codice sorgente
├── docs/                 # Documentazione
├── tests/                # Test del progetto
├── .github/              # Configurazioni GitHub
│   ├── workflows/        # GitHub Actions
│   ├── ISSUE_TEMPLATE/   # Template per issues
│   └── PULL_REQUEST_TEMPLATE.md
└── package.json          # Dipendenze (Node.js)
```

### File Speciali GitHub

#### README.md
```markdown
# Nome Progetto

## Descrizione
Breve descrizione del progetto e suoi obiettivi.

## Installazione
```bash
npm install
npm start
```

## Utilizzo
Esempi di come utilizzare il progetto.

## Contribuire
Guida per contribuire al progetto.

## Licenza
MIT License
```

#### .gitignore
```gitignore
# Node.js
node_modules/
npm-debug.log*

# Environment variables
.env
.env.local

# Build outputs
dist/
build/

# IDE files
.vscode/
.idea/
```

#### LICENSE
```
MIT License

Copyright (c) 2024 Your Name

Permission is hereby granted, free of charge, to any person obtaining a copy...
```

## Creazione Repository

### Via Interfaccia Web
1. **Login** su GitHub.com
2. Click **"New repository"** (pulsante verde)
3. **Configura repository**:
   - Repository name
   - Description (opzionale)
   - Public/Private
   - Initialize with README
   - Add .gitignore
   - Choose license

### Via GitHub CLI
```bash
# Installa GitHub CLI
# macOS: brew install gh
# Windows: scoop install gh
# Linux: vedi docs ufficiali

# Login
gh auth login

# Crea repository
gh repo create my-project --public --clone
cd my-project

# Setup iniziale
echo "# My Project" > README.md
git add README.md
git commit -m "initial commit"
git push origin main
```

### Via Git Command Line
```bash
# Crea progetto locale
mkdir my-project
cd my-project
git init

# Setup iniziale
echo "# My Project" > README.md
git add README.md
git commit -m "initial commit"

# Collega a GitHub (repository già creato online)
git remote add origin https://github.com/username/my-project.git
git branch -M main
git push -u origin main
```

## Configurazione Repository

### Settings Base
- **Repository name**: Nome del progetto
- **Description**: Descrizione breve
- **Website**: URL progetto live
- **Topics**: Tag per categorizzazione
- **Include in search**: Visibilità ricerche

### Security Settings
```bash
# Branch protection rules
- Require pull request reviews
- Dismiss stale reviews
- Require status checks
- Restrict pushes to main

# Security advisories
- Private vulnerability reporting
- Dependabot alerts
- Code scanning alerts
```

### Collaborators
```bash
# Aggiungere collaboratori
Settings → Manage access → Invite a collaborator

# Livelli di accesso:
- Read: Solo lettura
- Triage: Read + gestione issues
- Write: Read + push (no force push main)
- Maintain: Write + repository settings
- Admin: Controllo completo
```

### GitHub Pages
```bash
# Attiva Pages
Settings → Pages → Source → Deploy from branch

# Configurazione
Branch: main
Folder: / (root) o /docs

# Custom domain (opzionale)
Custom domain: yourdomain.com
```

## Repository Templates

### Creazione Template
```bash
# 1. Crea repository normale
# 2. Settings → Template repository ✓
# 3. Repository diventa template

# Struttura template consigliata:
template-name/
├── README.md             # Con placeholder {{PROJECT_NAME}}
├── .gitignore           # Per linguaggio specifico
├── LICENSE              # Licenza standard
├── .github/
│   ├── workflows/       # CI/CD template
│   └── ISSUE_TEMPLATE/  # Template issues
├── src/                 # Struttura codice base
└── docs/               # Template documentazione
```

### Uso Template
```bash
# Via interfaccia GitHub:
# 1. Va al template repository
# 2. "Use this template" → "Create new repository"
# 3. Configura nuovo repo

# Via GitHub CLI:
gh repo create my-new-project --template username/template-name
```

## Best Practices

### Naming Conventions
```bash
# Repository names
✅ GOOD:
- my-awesome-project
- react-todo-app
- python-data-analyzer

❌ AVOID:
- MyAwesomeProject (camelCase)
- my_awesome_project (underscore)
- project1, project2 (non descriptive)
```

### Repository Structure
```bash
# Organizzazione logica
src/                    # Codice sorgente
├── components/         # Componenti riutilizzabili
├── utils/             # Utilità
├── services/          # Servizi/API
└── tests/             # Test

docs/                  # Documentazione
├── api/               # Documentazione API
├── guides/            # Guide utente
└── architecture/      # Architettura

scripts/               # Script di build/deploy
configs/              # File di configurazione
```

### Security Best Practices
```bash
# .gitignore completo
.env*                  # Environment variables
*.key                  # Private keys
config/secrets.json    # File segreti
node_modules/         # Dependencies
.DS_Store             # System files

# GitHub Secrets per CI/CD
# Settings → Secrets → Actions
API_KEY=your_secret_key
DATABASE_URL=postgres://...
```

## Workflow di Sviluppo

### Solo Developer
```bash
# 1. Clone
git clone https://github.com/username/my-project.git
cd my-project

# 2. Sviluppo
git checkout -b feature/new-feature
# ... sviluppo ...
git add .
git commit -m "feat: implement new feature"

# 3. Push e merge
git push origin feature/new-feature
# Create Pull Request su GitHub
# Merge dopo review
```

### Team Development
```bash
# 1. Fork (per contributor esterni)
# Click "Fork" su GitHub

# 2. Clone del fork
git clone https://github.com/your-username/project-name.git
cd project-name

# 3. Upstream remote
git remote add upstream https://github.com/original-owner/project-name.git

# 4. Feature branch
git checkout -b feature/my-contribution

# 5. Pull Request
# Push to fork → Create PR to original repo
```

## Repository Insights

### Analytics Available
- **Traffic**: Visitor count, popular content
- **Commits**: Activity over time
- **Code frequency**: Additions/deletions
- **Contributors**: Team activity
- **Community**: Health score

### Utilizzo Insights
```bash
# Per project managers:
- Track team productivity
- Identify bottlenecks
- Plan releases

# Per developers:
- Monitor code quality
- Review contribution patterns
- Optimize workflow
```

## Troubleshooting Comune

### Repository Non Trovato
```bash
# Verifica URL
git remote -v

# Aggiorna remote se necessario
git remote set-url origin https://github.com/correct-username/repo-name.git
```

### Permessi Negati
```bash
# Verifica collaborator access
# Owner: Settings → Manage access

# Verifica SSH keys
ssh -T git@github.com

# Switch to HTTPS se SSH problematico
git remote set-url origin https://github.com/username/repo-name.git
```

### Repository Troppo Grande
```bash
# Git LFS per file grandi
git lfs track "*.psd"
git lfs track "*.zip"
git add .gitattributes

# GitHub file size limits:
- Single file: 100MB max
- Repository: 1GB recommended
- LFS: 2GB per file, 1GB per month free
```

## Migrazione Repository

### Da Altro Servizio
```bash
# Backup completo con history
git clone --mirror https://old-service.com/user/repo.git
cd repo.git

# Push a GitHub
git remote set-url origin https://github.com/user/repo.git
git push --mirror origin
```

### Tra Account GitHub
```bash
# Via Transfer ownership
# Settings → Transfer ownership

# O manual migration
git clone --mirror https://github.com/old-user/repo.git
cd repo.git
git remote set-url origin https://github.com/new-user/repo.git
git push --mirror origin
```

## Prossimi Passi

Ora che conosci i repository GitHub:

1. **Crea il tuo primo repository** seguendo questa guida
2. **Configura SSH** per accesso sicuro - [Autenticazione SSH](./05-autenticazione-ssh.md)
3. **Esplora l'ecosistema** GitHub - [Ecosistema GitHub](./06-ecosistema-github.md)
4. **Pratica con gli esempi** - [Setup Account](../esempi/01-setup-account.md)

## Risorse Aggiuntive

- [GitHub Docs - Repositories](https://docs.github.com/en/repositories)
- [Git SCM - Working with Remotes](https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes)
- [GitHub CLI Documentation](https://cli.github.com/manual/)
