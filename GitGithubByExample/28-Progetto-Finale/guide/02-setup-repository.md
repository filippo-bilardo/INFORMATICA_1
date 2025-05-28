# 02 - Setup Repository del Progetto Finale

## 📖 Spiegazione Concettuale

Il setup del repository è fondamentale per il successo del progetto finale. Non si tratta solo di creare un repository, ma di configurare un ambiente di sviluppo professionale che supporti collaboration, automation, e quality assurance dall'inizio.

### Elementi di un Repository Professionale

#### 1. **Repository Structure**
```
project-name/
├── .github/
│   ├── workflows/          # GitHub Actions
│   ├── ISSUE_TEMPLATE/     # Template per issues
│   ├── PULL_REQUEST_TEMPLATE.md
│   └── CODE_OF_CONDUCT.md
├── docs/                   # Documentazione
├── src/                    # Codice sorgente
├── tests/                  # Test automatizzati
├── .gitignore
├── README.md
├── LICENSE
├── CONTRIBUTING.md
└── CHANGELOG.md
```

#### 2. **Repository Settings Avanzate**
- **Branch protection rules**
- **Required status checks**
- **Merge restrictions**
- **Security settings**

## 🔧 Setup Iniziale del Repository

### Fase 1: Creazione e Configurazione Base

#### 1.1 Creare il Repository
```bash
# Su GitHub (via web interface)
# Nome: task-manager-collaborative
# Descrizione: "A collaborative task management application showcasing advanced Git workflows"
# Visibilità: Public (per showcase)
# Initialize with: README, .gitignore (Node), License (MIT)
```

#### 1.2 Clone e Setup Locale
```bash
# Clone del repository
git clone https://github.com/username/task-manager-collaborative.git
cd task-manager-collaborative

# Configurazione Git per il progetto
git config user.name "Your Name"
git config user.email "your.email@example.com"

# Setup di Git Flow
git flow init
# Accetta tutti i default (main/develop/feature/release/hotfix)
```

#### 1.3 Configurazione Branch Protection
```yaml
# Settings → Branches → Add rule
Branch name pattern: main
☑️ Require a pull request before merging
☑️ Require approvals: 1
☑️ Dismiss stale PR approvals when new commits are pushed
☑️ Require status checks to pass before merging
☑️ Require branches to be up to date before merging
☑️ Require linear history
☑️ Include administrators
```

### Fase 2: Template e Documentation

#### 2.1 Issue Templates
```bash
mkdir -p .github/ISSUE_TEMPLATE
```

**Bug Report Template** (`.github/ISSUE_TEMPLATE/bug_report.yml`):
```yaml
name: 🐛 Bug Report
description: File a bug report to help us improve
title: "[BUG] "
labels: ["bug", "triage"]
body:
  - type: markdown
    attributes:
      value: |
        Thanks for taking the time to fill out this bug report!
  
  - type: input
    id: contact
    attributes:
      label: Contact Details
      description: How can we get in touch with you if we need more info?
      placeholder: ex. email@example.com
    validations:
      required: false
  
  - type: textarea
    id: what-happened
    attributes:
      label: What happened?
      description: Also tell us, what did you expect to happen?
      placeholder: Tell us what you see!
      value: "A bug happened!"
    validations:
      required: true
  
  - type: dropdown
    id: version
    attributes:
      label: Version
      description: What version of our software are you running?
      options:
        - 1.0.0 (Default)
        - 0.9.0
        - 0.8.0
    validations:
      required: true
  
  - type: dropdown
    id: browsers
    attributes:
      label: What browsers are you seeing the problem on?
      multiple: true
      options:
        - Firefox
        - Chrome
        - Safari
        - Microsoft Edge
  
  - type: textarea
    id: logs
    attributes:
      label: Relevant log output
      description: Please copy and paste any relevant log output. This will be automatically formatted into code, so no need for backticks.
      render: shell
  
  - type: checkboxes
    id: terms
    attributes:
      label: Code of Conduct
      description: By submitting this issue, you agree to follow our [Code of Conduct](https://example.com)
      options:
        - label: I agree to follow this project's Code of Conduct
          required: true
```

**Feature Request Template** (`.github/ISSUE_TEMPLATE/feature_request.yml`):
```yaml
name: 🚀 Feature Request
description: Suggest a new feature or enhancement
title: "[FEATURE] "
labels: ["enhancement", "triage"]
body:
  - type: markdown
    attributes:
      value: |
        Thanks for suggesting a new feature!
  
  - type: textarea
    id: feature-description
    attributes:
      label: Feature Description
      description: A clear and concise description of what you want to happen.
      placeholder: Describe the feature...
    validations:
      required: true
  
  - type: textarea
    id: motivation
    attributes:
      label: Motivation
      description: Why is this feature important? What problem does it solve?
      placeholder: Explain the motivation...
    validations:
      required: true
  
  - type: textarea
    id: alternatives
    attributes:
      label: Alternatives Considered
      description: A clear description of any alternative solutions you've considered.
      placeholder: Describe alternatives...
    validations:
      required: false
  
  - type: textarea
    id: additional-context
    attributes:
      label: Additional Context
      description: Add any other context or screenshots about the feature request here.
      placeholder: Any additional context...
    validations:
      required: false
```

#### 2.2 Pull Request Template
**`.github/PULL_REQUEST_TEMPLATE.md`**:
```markdown
## 📋 Description

Brief description of changes

## 🔗 Related Issues

Fixes #(issue)

## 🧪 Type of Change

- [ ] 🐛 Bug fix (non-breaking change which fixes an issue)
- [ ] ✨ New feature (non-breaking change which adds functionality)
- [ ] 💥 Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] 📚 Documentation update
- [ ] 🔧 Refactoring
- [ ] ⚡ Performance improvement
- [ ] 🧪 Test addition or improvement

## 🧪 Testing

- [ ] Tests pass locally with my changes
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] I have added necessary documentation (if appropriate)

## 📝 Testing Instructions

Describe how to test these changes:

1. Step 1
2. Step 2
3. ...

## 📷 Screenshots (if appropriate)

## ✅ Checklist

- [ ] My code follows the code style of this project
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] Any dependent changes have been merged and published

## 🎯 Reviewer Notes

Any specific areas you'd like reviewers to focus on:
```

#### 2.3 Contributing Guidelines
**`CONTRIBUTING.md`**:
```markdown
# Contributing to Task Manager Collaborative

First off, thanks for taking the time to contribute! 🎉

The following is a set of guidelines for contributing to this project.

## Code of Conduct

This project and everyone participating in it is governed by our [Code of Conduct](CODE_OF_CONDUCT.md).

## How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check the existing issues to avoid duplicates.

**How Do I Submit A Good Bug Report?**

Bugs are tracked as [GitHub issues](https://guides.github.com/features/issues/). Use our bug report template and provide:

* **Use a clear and descriptive title**
* **Describe the exact steps which reproduce the problem**
* **Provide specific examples to demonstrate the steps**
* **Describe the behavior you observed and what behavior you expected**

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. Use our feature request template.

### Pull Requests

* Fill in the required template
* Do not include issue numbers in the PR title
* Include screenshots and animated GIFs in your pull request whenever possible
* Follow the [JavaScript](#javascript-styleguide) and [CSS](#css-styleguide) styleguides
* Document new code based on the Documentation Styleguide
* End all files with a newline

## Development Setup

```bash
# Clone the repository
git clone https://github.com/your-username/task-manager-collaborative.git

# Install dependencies
npm install

# Run tests
npm test

# Start development server
npm run dev
```

## Git Workflow

We use **Git Flow** with the following conventions:

### Branch Naming
* `feature/` - New features (e.g., `feature/user-authentication`)
* `bugfix/` - Bug fixes (e.g., `bugfix/login-validation`)
* `hotfix/` - Critical fixes (e.g., `hotfix/security-patch`)
* `release/` - Release preparation (e.g., `release/v1.2.0`)

### Commit Messages

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

**Types:**
* `feat`: A new feature
* `fix`: A bug fix
* `docs`: Documentation only changes
* `style`: Changes that do not affect the meaning of the code
* `refactor`: A code change that neither fixes a bug nor adds a feature
* `perf`: A code change that improves performance
* `test`: Adding missing tests or correcting existing tests
* `chore`: Changes to the build process or auxiliary tools

**Examples:**
```
feat(auth): add user authentication system
fix(api): resolve data validation error
docs: update installation instructions
```

## Code Style

### JavaScript Style Guide

* Use 2 spaces for indentation
* Use semicolons
* Use single quotes for strings
* Prefer `const` over `let`, avoid `var`
* Use meaningful variable names
* Add JSDoc comments for functions

### CSS Style Guide

* Use 2 spaces for indentation
* Use meaningful class names (BEM methodology)
* Group related properties together
* Use CSS custom properties for theming

## Testing

* Write tests for new features
* Ensure all tests pass before submitting PR
* Aim for high test coverage
* Use descriptive test names

## Documentation

* Keep README.md up to date
* Document new features in `/docs`
* Use clear, concise language
* Include code examples where appropriate

## Questions?

Feel free to contact the maintainers or open an issue for discussion.
```

### Fase 3: GitHub Actions Workflow

#### 3.1 CI/CD Pipeline Base
**`.github/workflows/ci.yml`**:
```yaml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    strategy:
      matrix:
        node-version: [16.x, 18.x, 20.x]
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Use Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v3
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run linter
      run: npm run lint
    
    - name: Run tests
      run: npm test
    
    - name: Generate coverage report
      run: npm run coverage
    
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        token: ${{ secrets.CODECOV_TOKEN }}
        file: ./coverage/lcov.info
        flags: unittests
        name: codecov-umbrella

  build:
    runs-on: ubuntu-latest
    needs: test
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Use Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18.x'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: npm run build
    
    - name: Upload build artifacts
      uses: actions/upload-artifact@v3
      with:
        name: build-files
        path: dist/

  security:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Run security audit
      run: npm audit --audit-level high
    
    - name: Run CodeQL Analysis
      uses: github/codeql-action/init@v2
      with:
        languages: javascript
    
    - name: Perform CodeQL Analysis
      uses: github/codeql-action/analyze@v2
```

#### 3.2 Automated Release Workflow
**`.github/workflows/release.yml`**:
```yaml
name: Release

on:
  push:
    branches: [ main ]
    tags: [ 'v*' ]

jobs:
  release:
    runs-on: ubuntu-latest
    if: startsWith(github.ref, 'refs/tags/v')
    
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0
    
    - name: Use Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18.x'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: npm run build
    
    - name: Create GitHub Release
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        tag_name: ${{ github.ref }}
        release_name: Release ${{ github.ref }}
        body: |
          Changes in this Release
          - Feature 1
          - Feature 2
          - Bug fixes
        draft: false
        prerelease: false
    
    - name: Deploy to GitHub Pages
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./dist
```

### Fase 4: Project Configuration

#### 4.1 Package.json Setup
```json
{
  "name": "task-manager-collaborative",
  "version": "1.0.0",
  "description": "A collaborative task management application",
  "main": "src/index.js",
  "scripts": {
    "dev": "webpack serve --mode development",
    "build": "webpack --mode production",
    "test": "jest",
    "test:watch": "jest --watch",
    "coverage": "jest --coverage",
    "lint": "eslint src/",
    "lint:fix": "eslint src/ --fix",
    "format": "prettier --write 'src/**/*.{js,css,html}'",
    "prepare": "husky install"
  },
  "repository": {
    "type": "git",
    "url": "git+https://github.com/username/task-manager-collaborative.git"
  },
  "keywords": [
    "task-management",
    "collaboration",
    "git-workflow",
    "github-actions"
  ],
  "author": "Your Name",
  "license": "MIT",
  "bugs": {
    "url": "https://github.com/username/task-manager-collaborative/issues"
  },
  "homepage": "https://github.com/username/task-manager-collaborative#readme",
  "devDependencies": {
    "@babel/core": "^7.22.0",
    "@babel/preset-env": "^7.22.0",
    "babel-loader": "^9.1.0",
    "css-loader": "^6.8.0",
    "eslint": "^8.42.0",
    "html-webpack-plugin": "^5.5.0",
    "husky": "^8.0.0",
    "jest": "^29.5.0",
    "lint-staged": "^13.2.0",
    "prettier": "^2.8.0",
    "style-loader": "^3.3.0",
    "webpack": "^5.85.0",
    "webpack-cli": "^5.1.0",
    "webpack-dev-server": "^4.15.0"
  },
  "dependencies": {
    "uuid": "^9.0.0"
  }
}
```

#### 4.2 Code Quality Configuration

**`.eslintrc.js`**:
```javascript
module.exports = {
  env: {
    browser: true,
    es2021: true,
    node: true,
    jest: true,
  },
  extends: [
    'eslint:recommended',
  ],
  parserOptions: {
    ecmaVersion: 'latest',
    sourceType: 'module',
  },
  rules: {
    'indent': ['error', 2],
    'linebreak-style': ['error', 'unix'],
    'quotes': ['error', 'single'],
    'semi': ['error', 'always'],
    'no-unused-vars': 'error',
    'no-console': 'warn',
    'prefer-const': 'error',
    'no-var': 'error',
  },
};
```

**`.prettierrc`**:
```json
{
  "semi": true,
  "singleQuote": true,
  "tabWidth": 2,
  "trailingComma": "es5",
  "printWidth": 80
}
```

**`jest.config.js`**:
```javascript
module.exports = {
  testEnvironment: 'jsdom',
  coverageDirectory: 'coverage',
  collectCoverageFrom: [
    'src/**/*.{js,jsx}',
    '!src/index.js',
  ],
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
      statements: 80,
    },
  },
  setupFilesAfterEnv: ['<rootDir>/src/setupTests.js'],
};
```

## 🎯 Setup Checklist

### Repository Configuration
- [ ] Repository creato con nome descrittivo
- [ ] README.md iniziale completo
- [ ] .gitignore appropriato configurato
- [ ] LICENSE file aggiunto
- [ ] Branch protection rules configurate
- [ ] Required status checks attivati

### Templates e Documentation
- [ ] Issue templates configurati
- [ ] Pull request template creato
- [ ] CONTRIBUTING.md dettagliato
- [ ] CODE_OF_CONDUCT.md aggiunto
- [ ] SECURITY.md policy definita

### Automation
- [ ] GitHub Actions CI/CD configurato
- [ ] Automated testing setup
- [ ] Code quality checks attivi
- [ ] Security scanning attivato
- [ ] Automated releases configurato

### Development Environment
- [ ] Package.json configurato
- [ ] ESLint e Prettier setup
- [ ] Jest testing configurato
- [ ] Husky pre-commit hooks attivi
- [ ] Development scripts funzionanti

### Team Collaboration
- [ ] Team members aggiunti come collaboratori
- [ ] Roles e permissions definiti
- [ ] Project board creato
- [ ] Milestone e labels configurati

## ⚠️ Errori Comuni da Evitare

### 1. **Setup Affrettato**
```bash
# ❌ Sbagliato
git init
git add .
git commit -m "initial commit"

# ✅ Corretto
git init
# Setup .gitignore e template prima
git add .gitignore README.md
git commit -m "feat: initial project setup with documentation"
```

### 2. **Branch Protection Mancante**
- Non configurare branch protection su main
- Permettere push diretti senza review
- Non richiedere status checks

### 3. **Template Generici**
- Usare template default senza personalizzazione
- Non includere campi specifici del progetto
- Mancanza di validazione

### 4. **CI/CD Incompleto**
- Non testare su multiple versioni Node.js
- Mancanza di security checks
- Non configurare artifact upload

## 🧪 Testing del Setup

### Test Repository Structure
```bash
# Verifica struttura directory
tree -a -I 'node_modules|.git'

# Verifica configurazione Git
git config --list | grep user
git flow version

# Test lint e format
npm run lint
npm run format

# Test build e deploy
npm run build
npm test
```

### Test GitHub Integration
```bash
# Test issue creation
gh issue create --title "Test issue" --body "Testing issue template"

# Test PR workflow
git checkout -b feature/test-setup
echo "test" > test.txt
git add test.txt
git commit -m "feat: test commit for setup verification"
git push origin feature/test-setup
gh pr create --title "Test PR" --body "Testing PR template"
```

## 📚 Risorse Aggiuntive

### GitHub Features
- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Branch Protection Rules](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/defining-the-mergeability-of-pull-requests/about-protected-branches)
- [Issue Templates](https://docs.github.com/en/communities/using-templates-to-encourage-useful-issues-and-pull-requests/configuring-issue-templates-for-your-repository)

### Code Quality Tools
- [ESLint Rules](https://eslint.org/docs/rules/)
- [Prettier Configuration](https://prettier.io/docs/en/configuration.html)
- [Jest Testing Framework](https://jestjs.io/docs/getting-started)

### Security Best Practices
- [GitHub Security Features](https://docs.github.com/en/code-security)
- [npm Security](https://docs.npmjs.com/auditing-package-dependencies-for-security-vulnerabilities)

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Pianificazione Progetto](01-pianificazione-progetto.md)
- [➡️ Sviluppo Collaborativo](03-sviluppo-collaborativo.md)
