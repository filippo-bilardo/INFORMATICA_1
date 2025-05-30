# Guida: Ecosistema GitHub

## Introduzione
GitHub non è solo un hosting per repository Git, ma un ecosistema completo per lo sviluppo software moderno con strumenti integrati per collaborazione, automazione e deployment.

## Panoramica Ecosistema

### Core Platform
- **Repositories**: Storage e versioning del codice
- **Issues**: Tracking di bug e feature requests
- **Pull Requests**: Code review e merge workflow
- **Discussions**: Forum per la community
- **Wiki**: Documentazione collaborativa

### Developer Tools
- **GitHub CLI**: Command line interface
- **GitHub Desktop**: GUI per Git operations
- **GitHub Mobile**: Mobile app per gestione
- **VS Code Integration**: Estensioni ufficiali
- **Codespaces**: Development environment cloud

### Automation & CI/CD
- **GitHub Actions**: Workflow automation
- **GitHub Packages**: Package registry
- **GitHub Pages**: Static site hosting
- **Dependabot**: Dependency security updates

### Enterprise Features
- **GitHub Enterprise**: Versione aziendale
- **GitHub Advanced Security**: Security scanning
- **GitHub Insights**: Analytics avanzati
- **GitHub Copilot**: AI-powered coding assistant

## GitHub CLI (Command Line Interface)

### Installazione
```bash
# macOS
brew install gh

# Windows (Chocolatey)
choco install gh

# Windows (Scoop)
scoop install gh

# Ubuntu/Debian
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
sudo apt update
sudo apt install gh

# Arch Linux
sudo pacman -S github-cli
```

### Setup e Autenticazione
```bash
# Login interattivo
gh auth login

# Login with token
gh auth login --with-token < token.txt

# Status autenticazione
gh auth status

# Lista account
gh auth list
```

### Repository Management
```bash
# Crea repository
gh repo create my-project --public
gh repo create my-project --private --clone

# Clone con extras
gh repo clone username/repo
gh repo clone username/repo --clone

# Fork repository
gh repo fork owner/repo
gh repo fork owner/repo --clone

# Lista repository
gh repo list
gh repo list username

# View repository info
gh repo view
gh repo view owner/repo
```

### Issues Management
```bash
# Lista issues
gh issue list
gh issue list --state open
gh issue list --label bug
gh issue list --assignee @me

# Crea issue
gh issue create --title "Bug in login" --body "Description here"
gh issue create --template bug_report.md

# View e edit issues
gh issue view 123
gh issue edit 123 --title "New title"
gh issue close 123
gh issue reopen 123

# Assign issues
gh issue assign 123 @username
gh issue unassign 123 @username
```

### Pull Requests
```bash
# Crea PR
gh pr create --title "Feature: new login" --body "Description"
gh pr create --draft
gh pr create --base develop

# Lista PR
gh pr list
gh pr list --state open
gh pr list --author @me

# Review PR
gh pr view 456
gh pr review 456 --approve
gh pr review 456 --request-changes
gh pr review 456 --comment "Looks good!"

# Merge PR
gh pr merge 456
gh pr merge 456 --squash
gh pr merge 456 --rebase

# Checkout PR localmente
gh pr checkout 456
```

## GitHub Desktop

### Features Principali
- **Visual Git Interface**: GUI intuitiva per Git
- **Branch Management**: Creazione e switch visuale
- **Commit History**: Timeline grafica
- **Merge Conflict Resolution**: Tool visuale per conflitti
- **GitHub Integration**: Sync automatico

### Workflow Tipico
```bash
# 1. Clone repository
# File → Clone Repository → URL o GitHub.com

# 2. Create branch
# Current Branch → New Branch → "feature/new-feature"

# 3. Make changes
# Files modificati appaiono in "Changes"

# 4. Commit
# Summary: "Add new feature"
# Description: "Detailed description"
# Commit to feature/new-feature

# 5. Publish branch
# Publish branch → Creates remote branch

# 6. Create Pull Request
# Branch → Create Pull Request
```

### Vantaggi
- ✅ Beginner-friendly
- ✅ Visual diff viewer
- ✅ Integrated conflict resolution
- ✅ GitHub integration
- ✅ Cross-platform

### Limitazioni
- ❌ Meno controllo del CLI
- ❌ Non tutti i comandi Git disponibili
- ❌ Performance con repository grandi

## GitHub Mobile

### Funzionalità Available
- **Notifications**: Push notifications in tempo reale
- **Issues & PR**: Creazione e gestione mobile
- **Code Review**: Review di PR in mobilità
- **Repository Browse**: Navigazione codice
- **Basic Git Operations**: Commit e merge semplici

### Use Cases
```bash
# Gestione veloce durante commute
- Review e approve PR
- Respond to comments
- Close issues
- Emergency hotfix review

# Team communication
- @ mentions e notifications
- Quick status updates
- Issue triage
```

## GitHub Codespaces

### Che cosa è
Ambiente di sviluppo cloud completamente configurato e accessibile da browser o VS Code.

### Setup Codespace
```yaml
# .devcontainer/devcontainer.json
{
  "name": "Node.js & TypeScript",
  "image": "mcr.microsoft.com/vscode/devcontainers/typescript-node:16",
  "features": {
    "ghcr.io/devcontainers/features/github-cli:1": {}
  },
  "postCreateCommand": "npm install",
  "customizations": {
    "vscode": {
      "extensions": [
        "ms-vscode.vscode-typescript-next",
        "esbenp.prettier-vscode",
        "ms-vscode.vscode-json"
      ]
    }
  },
  "forwardPorts": [3000, 8080],
  "portsAttributes": {
    "3000": {
      "label": "Dev Server"
    }
  }
}
```

### Vantaggi Codespaces
- ✅ **Zero Setup**: Ambiente pronto all'uso
- ✅ **Consistent**: Stesso ambiente per tutto il team
- ✅ **Powerful**: VM con risorse dedicate
- ✅ **Accessible**: Da qualsiasi device
- ✅ **Integrated**: GitHub workflow nativi

### Pricing
```bash
# Free tier (personal accounts)
- 120 core hours/month
- 15 GB storage

# Usage-based pricing
- $0.18/hour for 2-core machines
- $0.36/hour for 4-core machines
- $0.72/hour for 8-core machines
```

## GitHub Actions

### Overview
Sistema di CI/CD integrato per automazione di workflow di sviluppo.

### Basic Workflow
```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run tests
      run: npm test
    
    - name: Build
      run: npm run build
```

### Marketplace
```bash
# Actions popolari
- actions/checkout@v3         # Clone repository
- actions/setup-node@v3       # Setup Node.js
- actions/setup-python@v4     # Setup Python
- actions/upload-artifact@v3  # Upload build artifacts
- codecov/codecov-action@v3   # Code coverage reports
```

## GitHub Packages

### Package Registry
Registry per hosting packages in diversi linguaggi.

### Supported Ecosystems
- **npm** (Node.js)
- **Docker** (Container images)
- **Maven** (Java)
- **NuGet** (.NET)
- **PyPI** (Python)
- **Gems** (Ruby)

### Esempio npm Package
```json
// package.json
{
  "name": "@username/my-package",
  "version": "1.0.0",
  "publishConfig": {
    "registry": "https://npm.pkg.github.com"
  }
}
```

```bash
# Setup npm per GitHub Packages
echo "@username:registry=https://npm.pkg.github.com" >> .npmrc
echo "//npm.pkg.github.com/:_authToken=TOKEN" >> .npmrc

# Publish
npm publish
```

## GitHub Pages

### Static Site Hosting
Hosting gratuito per siti statici direttamente da repository GitHub.

### Setup Pages
```bash
# Via Settings
Repository → Settings → Pages → Source → Deploy from branch

# Configurazione
Branch: main
Folder: / (root) o /docs

# Custom domain
Custom domain: yourdomain.com
Enforce HTTPS: ✓
```

### Jekyll Integration
```yaml
# _config.yml
title: My GitHub Pages Site
description: A description of my site
baseurl: ""
url: "https://username.github.io"

markdown: kramdown
highlighter: rouge
theme: minima

plugins:
  - jekyll-feed
  - jekyll-sitemap
```

### Actions Deployment
```yaml
# .github/workflows/pages.yml
name: Deploy to GitHub Pages

on:
  push:
    branches: [ main ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Install and Build
      run: |
        npm ci
        npm run build
    
    - name: Deploy to GitHub Pages
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./dist
```

## GitHub Copilot

### AI-Powered Coding Assistant
Strumento che utilizza AI per suggerire codice in tempo reale.

### Features
- **Code Completion**: Suggerimenti intelligenti
- **Function Generation**: Genera funzioni complete
- **Code Explanation**: Spiega codice esistente
- **Test Generation**: Crea test automaticamente
- **Documentation**: Genera commenti e docs

### Esempi di Utilizzo
```javascript
// Commento descrittivo → Copilot genera implementazione
// Function to calculate fibonacci numbers recursively
function fibonacci(n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Generate test cases for the fibonacci function
describe('fibonacci', () => {
    test('should return 0 for n = 0', () => {
        expect(fibonacci(0)).toBe(0);
    });
    
    test('should return 1 for n = 1', () => {
        expect(fibonacci(1)).toBe(1);
    });
});
```

## Integrations & Marketplace

### VS Code Extensions
```bash
# Estensioni ufficiali GitHub
- GitHub Pull Requests and Issues
- GitHub Codespaces
- GitHub Copilot
- GitHub Actions

# Install via command palette
Ctrl+Shift+P → Extensions: Install Extensions → "GitHub"
```

### Third-Party Integrations
- **Slack**: Notifications e bot
- **Jira**: Issue linking
- **Figma**: Design file links
- **Notion**: Documentation sync
- **Discord**: Community management

### Webhooks e API
```bash
# GitHub REST API
curl -H "Authorization: token TOKEN" \
     https://api.github.com/user/repos

# GitHub GraphQL API
curl -H "Authorization: bearer TOKEN" \
     -X POST \
     -d '{"query": "query { viewer { login } }"}' \
     https://api.github.com/graphql

# Webhooks setup
Repository → Settings → Webhooks → Add webhook
Payload URL: https://your-server.com/webhook
Content type: application/json
Events: push, pull_request, issues
```

## Security Features

### Security Overview
- **Dependency Scanning**: Vulnerabilità nelle dipendenze
- **Code Scanning**: Analisi statica del codice
- **Secret Scanning**: Rilevamento credenziali
- **Security Advisories**: Gestione vulnerabilità

### Dependabot
```yaml
# .github/dependabot.yml
version: 2
updates:
  - package-ecosystem: "npm"
    directory: "/"
    schedule:
      interval: "weekly"
    reviewers:
      - "username"
    assignees:
      - "username"
```

### Advanced Security
```yaml
# .github/workflows/codeql.yml
name: "CodeQL"

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  analyze:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout repository
      uses: actions/checkout@v3
    
    - name: Initialize CodeQL
      uses: github/codeql-action/init@v2
      with:
        languages: javascript
    
    - name: Perform CodeQL Analysis
      uses: github/codeql-action/analyze@v2
```

## Best Practices Ecosistema

### Repository Organization
```bash
# Multi-repo vs Monorepo
Multi-repo: Servizi separati, team autonomi
Monorepo: Codice condiviso, deployment coordinato

# Template repositories
Standardizza setup progetti
Include configurazioni CI/CD
Documenta best practices team
```

### Workflow Integration
```bash
# Development workflow
1. Issues per planning
2. Feature branches per sviluppo
3. PR per code review
4. Actions per CI/CD
5. Pages per documentation
6. Packages per artifacts
```

### Security Workflow
```bash
# Security-first approach
1. Dependabot per dipendenze
2. CodeQL per code scanning
3. Secret scanning attivo
4. Branch protection rules
5. Required status checks
6. Signed commits
```

## Ecosystem Evolution

### GitHub Roadmap
- **AI Integration**: Più features Copilot
- **Cloud Development**: Expansion Codespaces
- **Enterprise Features**: Advanced analytics
- **Mobile Experience**: Enhanced mobile app
- **Performance**: Faster large repository handling

### Community Features
- **Discussions**: Forum integrati
- **Sponsors**: Monetizzazione open source
- **Profile README**: Personal branding
- **Achievement Badges**: Gamification
- **Social Features**: Following, stars, watching

## Prossimi Passi

Ora che conosci l'ecosistema GitHub:

1. **Esplora GitHub CLI** - [Setup Account](../esempi/01-setup-account.md)
2. **Prova GitHub Codespaces** - [Configurazione SSH](../esempi/03-configurazione-ssh.md)
3. **Configura GitHub Actions** - [GitHub Actions Intro](../../21-GitHub-Actions-Intro/README.md)
4. **Impara workflow collaborativi** - [Clone Push Pull](../../17-Clone-Push-Pull/README.md)

## Risorse Aggiuntive

- [GitHub Docs](https://docs.github.com/)
- [GitHub CLI Manual](https://cli.github.com/manual/)
- [GitHub Actions Marketplace](https://github.com/marketplace?type=actions)
- [GitHub Skills](https://skills.github.com/)
- [GitHub Community Forum](https://github.community/)
