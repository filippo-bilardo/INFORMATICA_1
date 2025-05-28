# 02 - Setup Repository e Ambiente

## 📖 Spiegazione Concettuale

Il setup iniziale del repository è cruciale per il successo del progetto. Un repository ben configurato stabilisce le fondamenta per collaborazione efficace, automation, e maintainability a lungo termine. Questa fase determina la qualità di tutto il processo di sviluppo.

## 🏗️ Architettura Repository

### Repository Structure Standard

```
progetto-finale/
├── .github/                    # GitHub-specific configuration
│   ├── workflows/             # GitHub Actions
│   ├── ISSUE_TEMPLATE/        # Issue templates
│   ├── PULL_REQUEST_TEMPLATE/ # PR templates
│   └── SECURITY.md            # Security policy
├── docs/                      # Documentation
│   ├── API.md                # API documentation
│   ├── CONTRIBUTING.md       # Contribution guidelines
│   └── DEPLOYMENT.md         # Deployment guide
├── src/                       # Source code
├── tests/                     # Test files
├── .gitignore                # Git ignore rules
├── README.md                 # Project overview
├── LICENSE                   # Project license
└── package.json              # Project dependencies (example)
```

## 🚀 Step-by-Step Setup

### Step 1: Repository Creation

#### 1.1 GitHub Repository Setup
```bash
# Opzione A: Crea via GitHub UI
# 1. Vai su github.com/new
# 2. Nome repository: "progetto-finale-git-corso"
# 3. Descrizione: "Progetto finale del corso Git e GitHub"
# 4. Visibilità: Public (per portfolio)
# 5. Initialize with README: ✓
# 6. Add .gitignore: Scegli template appropriato
# 7. Choose license: MIT (consigliato)

# Opzione B: Crea via GitHub CLI
gh repo create progetto-finale-git-corso \
  --public \
  --description "Progetto finale del corso Git e GitHub" \
  --gitignore Node \
  --license MIT \
  --clone
```

#### 1.2 Clone e Setup Locale
```bash
# Clone del repository
git clone https://github.com/TUO_USERNAME/progetto-finale-git-corso.git
cd progetto-finale-git-corso

# Configurazione locale (se non già fatto)
git config user.name "Il Tuo Nome"
git config user.email "tuo.email@example.com"

# Verifica configurazione
git config --list --local
```

### Step 2: Branch Strategy Setup

#### 2.1 GitHub Flow Setup (Consigliato per principianti)
```bash
# Il branch main è già il default
# Feature branches saranno create quando necessario
# Nessun setup addizionale richiesto

echo "Usando GitHub Flow - branch main + feature branches"
```

#### 2.2 Git Flow Setup (Opzionale per utenti avanzati)
```bash
# Installa git-flow se non presente
# Ubuntu/Debian: sudo apt install git-flow
# macOS: brew install git-flow

# Inizializza git-flow
git flow init

# Configura branch protection per develop e main
echo "Configurare branch protection via GitHub UI"
```

### Step 3: GitHub Configuration

#### 3.1 Branch Protection Rules
```yaml
# Configurazione via GitHub UI: Settings > Branches
Branch: main
Protection Rules:
  ✓ Require pull request reviews before merging
  ✓ Require status checks to pass before merging
  ✓ Require branches to be up to date before merging
  ✓ Include administrators
  ✓ Allow force pushes (solo per progetti educativi)
  ✓ Allow deletions (solo per progetti educativi)
```

#### 3.2 Repository Settings
```yaml
# Settings > General
Repository Name: progetto-finale-git-corso
Description: "Progetto finale del corso Git e GitHub - [TUA SCELTA PROGETTO]"
Topics: git, github, course-project, web-development
Website: https://TUO_USERNAME.github.io/progetto-finale-git-corso

# Features
✓ Wikis
✓ Issues  
✓ Sponsorships (opzionale)
✓ Projects
✓ Preserve this repository (opzionale)

# Danger Zone
Delete this repository: [Leave as is]
```

## 📋 GitHub Templates Setup

### Issue Templates

#### Bug Report Template
<function_calls>
<invoke name="create_file">
<parameter name="content">---
name: Bug Report
about: Crea un report per aiutarci a migliorare
title: '[BUG] '
labels: bug
assignees: ''
---

## 🐛 Descrizione del Bug
Una descrizione chiara e concisa del bug.

## 🔄 Passi per Riprodurre
Passi per riprodurre il comportamento:
1. Vai a '...'
2. Clicca su '....'
3. Scorri verso il basso fino a '....'
4. Vedi l'errore

## ✅ Comportamento Atteso
Una descrizione chiara e concisa di cosa ti aspettavi che accadesse.

## 📱 Screenshots
Se applicabile, aggiungi screenshots per spiegare il problema.

## 🖥️ Informazioni Desktop
- OS: [es. iOS]
- Browser: [es. chrome, safari]
- Versione: [es. 22]

## 📱 Informazioni Smartphone
- Device: [es. iPhone6]
- OS: [es. iOS8.1]
- Browser: [es. stock browser, safari]
- Versione: [es. 22]

## 📝 Contesto Aggiuntivo
Aggiungi qualsiasi altro contesto sul problema qui.
