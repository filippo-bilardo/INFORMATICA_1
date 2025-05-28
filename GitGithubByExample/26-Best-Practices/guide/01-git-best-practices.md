# 01 - Git Best Practices Fundamentals

## 📖 Spiegazione Concettuale

Le **Git Best Practices** sono un insieme di convenzioni, strategie e tecniche consolidate che permettono di utilizzare Git in modo efficace, mantenendo un repository pulito, una storia comprensibile e facilitando la collaborazione di team.

## 🎯 Perché le Best Practices Sono Importanti

### Problemi Comuni Senza Best Practices
```
❌ Repository disordinato:
├── Commit message incomprensibili: "fix stuff"
├── Storia frammentata e confusa
├── Branch abbandonati ovunque
├── File temporanei tracciati
├── Merge commits inutili
└── Conflitti ricorrenti

❌ Collaborazione difficile:
├── Non si capisce chi ha fatto cosa
├── Difficile tornare a versioni precedenti
├── Code review impossibili
├── Deploy problematici
└── Rollback complessi
```

### Benefici delle Best Practices
```
✅ Repository professionale:
├── Storia pulita e lineare
├── Commit atomici e meaningful
├── Branch strategy chiara
├── Documentazione sempre aggiornata
├── Automazioni affidabili
└── Collaborazione fluida

✅ Team più produttivo:
├── Onboarding rapido nuovi sviluppatori
├── Debugging più veloce
├── Release più sicure
├── Code quality costante
└── Meno tempo perso in task ripetitive
```

## 📝 Commit Best Practices

### 1. Atomic Commits
**Concetto**: Un commit = una modifica logica completa

```bash
# ❌ BAD: Commit troppo grande
git commit -m "Add user auth, fix navbar bug, update docs"

# ✅ GOOD: Commit atomici
git commit -m "Add user authentication system"
git commit -m "Fix navbar collapse on mobile"
git commit -m "Update API documentation for auth endpoints"
```

### 2. Conventional Commit Messages
**Format**: `<type>(<scope>): <description>`

```bash
# Tipi standard
feat:     # nuova funzionalità
fix:      # bug fix
docs:     # solo documentazione
style:    # formattazione, missing semicolons, etc.
refactor: # refactoring senza cambi funzionali
test:     # aggiungere test mancanti
chore:    # build, tools, configurazioni

# Esempi
git commit -m "feat(auth): add password reset functionality"
git commit -m "fix(api): handle null response in user endpoint"
git commit -m "docs(readme): update installation instructions"
git commit -m "refactor(utils): extract common validation functions"
```

### 3. Descriptive Commit Messages
```bash
# ❌ BAD: Messaggi vaghi
"fix bug"
"update code"
"working version"
"final commit"

# ✅ GOOD: Messaggi descrittivi
"fix: resolve memory leak in image processing"
"feat: add dark mode toggle to user preferences"
"perf: optimize database queries for user dashboard"
"security: sanitize user input in contact form"
```

### 4. Commit Message Structure
```
<type>(<scope>): <short description>

<body: longer explanation if needed>

<footer: breaking changes, issues closed>
```

**Esempio completo**:
```
feat(auth): implement two-factor authentication

Add support for TOTP-based 2FA using Google Authenticator.
Users can enable 2FA in their security settings and are 
required to enter a 6-digit code along with their password.

- Add QR code generation for setup
- Implement backup codes for account recovery
- Add rate limiting for 2FA attempts

Closes #142, #89
BREAKING CHANGE: AuthService constructor now requires totpService parameter
```

## 🌿 Branching Best Practices

### 1. Git Flow Strategy
```
main/master    ←── Production-ready code
├── develop    ←── Integration branch
├── feature/*  ←── New features
├── release/*  ←── Release preparation  
├── hotfix/*   ←── Production fixes
└── bugfix/*   ←── Bug fixes
```

**Naming Conventions**:
```bash
# Feature branches
feature/user-authentication
feature/payment-integration
feature/dark-mode

# Bug fix branches
bugfix/navbar-mobile-issue
bugfix/email-validation-error
hotfix/critical-security-patch

# Release branches
release/v2.1.0
release/v2.2.0-beta
```

### 2. GitHub Flow (Simplified)
```
main     ←── Always deployable
├── feature-branch-1
├── feature-branch-2
└── feature-branch-3
```

**Workflow**:
1. Create branch from main
2. Develop feature
3. Open Pull Request
4. Code review and discussion
5. Merge to main
6. Deploy immediately

### 3. Branch Naming Conventions
```bash
# User story format
<type>/<issue-number>-<short-description>

# Examples
feature/AUTH-123-implement-oauth
bugfix/UI-456-fix-mobile-navigation
hotfix/SEC-789-patch-xss-vulnerability
docs/DOC-321-update-api-guide
```

## 🗂️ Repository Structure Best Practices

### 1. Standard Directory Layout
```
project-root/
├── .github/              # GitHub specific files
│   ├── workflows/        # GitHub Actions
│   ├── ISSUE_TEMPLATE/   # Issue templates
│   ├── PULL_REQUEST_TEMPLATE.md
│   └── CONTRIBUTING.md
├── docs/                 # Documentation
├── src/                  # Source code
├── tests/                # Test files
├── scripts/              # Build/utility scripts
├── config/               # Configuration files
├── public/               # Public assets
├── .gitignore           # Git ignore rules
├── .editorconfig        # Editor configuration
├── package.json         # Dependencies (Node.js)
├── README.md            # Project documentation
├── LICENSE              # License file
└── CHANGELOG.md         # Change log
```

### 2. .gitignore Best Practices
```bash
# ✅ GOOD: Comprehensive .gitignore

# Dependencies
node_modules/
vendor/

# Build outputs
dist/
build/
*.bundle.*

# Environment files
.env
.env.local
.env.*.local

# IDE files
.vscode/
.idea/
*.swp
*.swo

# OS files
.DS_Store
Thumbs.db

# Logs
*.log
logs/

# Cache directories
.cache/
.npm/
.next/

# Runtime data
pids/
*.pid
*.seed
```

### 3. README Structure
```markdown
# Project Name

Brief project description and value proposition.

## 🚀 Quick Start

```bash
# Installation and basic usage
npm install
npm start
```

## 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [API Documentation](#api)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

- Feature 1: Description
- Feature 2: Description
- Feature 3: Description

## 🛠️ Installation

Detailed installation instructions...

## 📖 Usage

Code examples and tutorials...

## 🤝 Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)

## 📄 License

This project is licensed under [MIT License](LICENSE)
```

## 🔐 Security Best Practices

### 1. Sensitive Data Protection
```bash
# ❌ NEVER commit:
- API keys and secrets
- Database passwords
- Private keys
- Personal information
- Configuration with credentials

# ✅ USE instead:
- Environment variables
- External secret managers
- Encrypted configuration files
- .env files (gitignored)
```

### 2. Environment Configuration
```bash
# .env.example (commit this)
DATABASE_URL=postgresql://localhost:5432/myapp
API_KEY=your_api_key_here
JWT_SECRET=your_jwt_secret_here

# .env (gitignored)
DATABASE_URL=postgresql://user:pass@prod.db.com:5432/myapp
API_KEY=real_api_key_12345
JWT_SECRET=super_secret_jwt_key
```

### 3. Git Security Commands
```bash
# Check for accidentally committed secrets
git log --grep="password\|secret\|key" --oneline

# Remove sensitive file from history
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch sensitive-file.txt' \
  --prune-empty --tag-name-filter cat -- --all

# Or use BFG Repo-Cleaner (recommended)
bfg --delete-files sensitive-file.txt
bfg --replace-text passwords.txt
```

## 👥 Collaboration Best Practices

### 1. Pull Request Guidelines
```markdown
# PR Template
## Description
Brief description of changes and motivation.

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Tests pass locally
- [ ] Added tests for new functionality
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No merge conflicts
```

### 2. Code Review Best Practices

**For Reviewers**:
```
✅ DO:
- Review promptly (within 24 hours)
- Be constructive and specific
- Explain the "why" behind suggestions
- Acknowledge good practices
- Test the changes if possible

❌ DON'T:
- Be overly critical or personal
- Block for minor style issues
- Ignore context and requirements
- Review while distracted
```

**For Authors**:
```
✅ DO:
- Keep PRs small and focused
- Provide clear description
- Respond to feedback promptly
- Be open to suggestions
- Test thoroughly before submitting

❌ DON'T:
- Submit massive PRs
- Get defensive about feedback
- Ignore review comments
- Rush the review process
```

### 3. Communication Guidelines
```
# Issue descriptions
- Clear problem statement
- Steps to reproduce
- Expected vs actual behavior
- Environment details
- Screenshots if applicable

# Commit messages
- Present tense ("Add feature" not "Added feature")
- Imperative mood ("Fix bug" not "Fixes bug")
- Reference issues when applicable
- Keep first line under 50 characters

# Documentation
- Keep README up to date
- Document breaking changes
- Provide code examples
- Explain complex decisions
```

## 🏗️ Workflow Best Practices

### 1. Development Workflow
```bash
# Daily workflow
1. git pull origin main          # Get latest changes
2. git checkout -b feature/new   # Create feature branch
3. # Make changes...
4. git add .                     # Stage changes
5. git commit -m "feat: add new feature"
6. git push origin feature/new   # Push branch
7. # Create Pull Request
8. # Address review feedback
9. # Merge when approved
10. git checkout main            # Switch back
11. git pull origin main         # Get merged changes
12. git branch -d feature/new    # Clean up local branch
```

### 2. Release Workflow
```bash
# Semantic versioning
MAJOR.MINOR.PATCH

# Examples
1.0.0  # Initial release
1.0.1  # Bug fix
1.1.0  # New feature (backward compatible)
2.0.0  # Breaking change

# Release process
1. Update version numbers
2. Update CHANGELOG.md
3. Create release branch
4. Final testing
5. Merge to main
6. Tag release
7. Deploy to production
8. Monitor for issues
```

### 3. Maintenance Workflow
```bash
# Regular maintenance tasks
- Clean up merged branches
- Update dependencies
- Review and close stale issues
- Update documentation
- Run security audits
- Optimize repository size

# Commands for cleanup
git branch --merged | grep -v main | xargs -n 1 git branch -d
git remote prune origin
git gc --aggressive
```

## 📊 Quality Control Best Practices

### 1. Automated Checks
```yaml
# .github/workflows/ci.yml
name: CI
on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Setup Node.js
        uses: actions/setup-node@v2
        with:
          node-version: '16'
      - run: npm ci
      - run: npm run lint
      - run: npm run test
      - run: npm run build
```

### 2. Code Quality Gates
```
Quality criteria:
✅ All tests pass
✅ Code coverage > 80%
✅ No linting errors
✅ Security vulnerabilities addressed
✅ Performance benchmarks met
✅ Documentation updated
✅ Breaking changes documented
```

### 3. Monitoring and Metrics
```
Track important metrics:
- Commit frequency
- PR size and review time
- Bug fix rate
- Code coverage trends
- Developer productivity
- Repository health score
```

## 🎯 Team-Specific Best Practices

### Small Teams (2-5 developers)
```
Simplified approach:
- Use GitHub Flow
- Direct commits to main for small fixes
- Informal code reviews
- Regular pair programming
- Weekly retrospectives
```

### Medium Teams (5-15 developers)
```
Structured approach:
- Use Git Flow or GitHub Flow
- Mandatory PR reviews
- Automated testing and deployment
- Sprint planning with GitHub Projects
- Code quality metrics
```

### Large Teams (15+ developers)
```
Enterprise approach:
- Strict Git Flow with release managers
- Multiple review stages
- Comprehensive CI/CD pipelines
- Microservices architecture
- Advanced monitoring and alerting
```

## 🔄 Continuous Improvement

### Regular Review Process
```
Monthly reviews:
- Analyze commit patterns
- Review workflow efficiency
- Gather team feedback
- Update guidelines
- Training for new practices
```

### Learning and Adaptation
```
Stay updated on:
- New Git features
- Industry best practices
- Tool improvements
- Team productivity insights
- Security recommendations
```

---

## 🎯 Punti Chiave da Ricordare

1. **Consistency è cruciale**: Seguire sempre le stesse convenzioni
2. **Commit atomici**: Una modifica logica per commit
3. **Branch strategy chiara**: Scegliere e rispettare un modello
4. **Security first**: Mai committare dati sensibili
5. **Documentation importante**: README e commit messages informativi
6. **Automazione aiuta**: CI/CD per qualità costante
7. **Team communication**: Feedback costruttivo e tempestivo
8. **Continuous improvement**: Adattare pratiche al team

---

**Prossimo**: [Code Quality e Linting](02-code-quality.md) | [Torna alle guide](../README.md)
