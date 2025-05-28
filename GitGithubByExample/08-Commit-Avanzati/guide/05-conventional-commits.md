# Conventional Commits: Standard per Messaggi Strutturati

## Introduzione
Conventional Commits è una specifica per la scrittura di messaggi di commit strutturati e standardizzati. Facilita l'automazione, la generazione di changelog e il versioning semantico.

## Specifica Conventional Commits

### Formato Base
```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

### Esempio Completo
```
feat(api): add user authentication endpoint

Implement JWT-based authentication with:
- Login/logout functionality
- Token refresh mechanism
- Role-based access control
- Password reset workflow

BREAKING CHANGE: authentication now required for all API endpoints

Closes #123
Refs #456
```

## Tipi di Commit

### Tipi Obbligatori
```bash
# feat: Nuova funzionalità per l'utente
git commit -m "feat: add dark mode toggle"

# fix: Bug fix per l'utente
git commit -m "fix: resolve login form validation error"
```

### Tipi Aggiuntivi (Angular Convention)
```bash
# build: Modifiche al sistema di build
git commit -m "build: update webpack configuration for production"

# chore: Manutenzione del codice (non user-facing)
git commit -m "chore: update dependencies to latest versions"

# ci: Modifiche alla configurazione CI
git commit -m "ci: add automated testing pipeline"

# docs: Solo documentazione
git commit -m "docs: update API documentation for v2.0"

# style: Cambiamenti di formattazione
git commit -m "style: fix indentation in main.css"

# refactor: Refactoring senza cambiamento funzionalità
git commit -m "refactor: extract validation logic to utility class"

# perf: Miglioramenti delle performance
git commit -m "perf: optimize database queries with proper indexing"

# test: Aggiunta o modifica di test
git commit -m "test: add unit tests for authentication service"
```

### Tipi Personalizzati
```bash
# security: Modifiche relative alla sicurezza
git commit -m "security: sanitize user input to prevent XSS"

# a11y: Miglioramenti di accessibilità
git commit -m "a11y: add ARIA labels to navigation menu"

# i18n: Internazionalizzazione
git commit -m "i18n: add Italian translation files"

# seo: Ottimizzazioni SEO
git commit -m "seo: improve meta tags and structured data"
```

## Scope (Ambito)

### Scope per Area Funzionale
```bash
# Frontend components
git commit -m "feat(header): add responsive navigation menu"
git commit -m "fix(sidebar): resolve mobile layout issues"

# Backend modules
git commit -m "feat(auth): implement OAuth2 integration"
git commit -m "fix(database): resolve connection pooling issues"

# API endpoints
git commit -m "feat(api/users): add user profile update endpoint"
git commit -m "fix(api/orders): handle edge case in order processing"
```

### Scope per Componenti
```bash
# React/Vue components
git commit -m "feat(LoginForm): add remember me functionality"
git commit -m "fix(UserCard): resolve avatar image loading"

# Services/Classes
git commit -m "refactor(EmailService): improve error handling"
git commit -m "perf(CacheManager): optimize memory usage"
```

### Scope per Piattaforme
```bash
# Multi-platform projects
git commit -m "fix(ios): resolve push notification registration"
git commit -m "feat(android): add biometric authentication"
git commit -m "style(web): update button hover effects"
```

## Breaking Changes

### Formato per Breaking Changes
```bash
# Option 1: ! dopo il tipo
git commit -m "feat!: change API response format

BREAKING CHANGE: API now returns data in nested structure
Migration guide available at docs/migration.md"

# Option 2: BREAKING CHANGE nel footer
git commit -m "feat: update user authentication

BREAKING CHANGE: login endpoint now requires email instead of username"
```

### Esempi Pratici
```bash
# Database schema changes
git commit -m "feat(db)!: migrate to UUID primary keys

BREAKING CHANGE: all ID fields now use UUID format
- Update client code to handle UUID strings
- Migration script: migrations/001-uuid-migration.sql
- Downtime expected: 5 minutes during deployment"

# API breaking changes
git commit -m "refactor(api)!: standardize error response format

BREAKING CHANGE: error responses now use RFC 7807 format
- Old format: { error: 'message' }
- New format: { type: 'uri', title: 'title', detail: 'detail' }
- Update error handling in client applications"
```

## Footer Metadata

### Issue References
```bash
# Closing issues
git commit -m "fix: resolve payment processing timeout

Closes #123
Closes #456"

# References without closing
git commit -m "feat: add payment gateway integration

Refs #789
Part-of: #234
See-also: #567"
```

### Co-authorship
```bash
git commit -m "feat: implement machine learning recommendation engine

Co-authored-by: Alice Smith <alice@company.com>
Co-authored-by: Bob Johnson <bob@company.com>"
```

### External References
```bash
git commit -m "fix: resolve security vulnerability

CVE-2023-12345
Security-Advisory: SA-2023-001
Reported-by: security@example.com"
```

## Configurazione Tools

### 1. Commitizen Setup
```bash
# Installazione globale
npm install -g commitizen cz-conventional-changelog

# Configurazione globale
echo '{ "path": "cz-conventional-changelog" }' > ~/.czrc

# Configurazione per progetto
npm install --save-dev commitizen cz-conventional-changelog
npx commitizen init cz-conventional-changelog --save-dev --save-exact

# Package.json script
{
  "scripts": {
    "commit": "cz"
  },
  "config": {
    "commitizen": {
      "path": "cz-conventional-changelog"
    }
  }
}
```

### 2. Commitlint Configuration
```bash
# Installazione
npm install --save-dev @commitlint/cli @commitlint/config-conventional

# Configurazione base
cat > .commitlintrc.js << 'EOF'
module.exports = {
  extends: ['@commitlint/config-conventional'],
  rules: {
    'type-enum': [
      2,
      'always',
      [
        'feat', 'fix', 'docs', 'style', 'refactor', 
        'test', 'chore', 'build', 'ci', 'perf',
        'security', 'a11y', 'i18n', 'seo'
      ]
    ],
    'scope-case': [2, 'always', 'lower-case'],
    'subject-case': [2, 'always', 'lower-case'],
    'subject-max-length': [2, 'always', 50],
    'body-max-line-length': [2, 'always', 72],
    'footer-max-line-length': [2, 'always', 72]
  }
}
EOF
```

### 3. Husky Integration
```bash
# Installazione Husky
npm install --save-dev husky

# Setup hooks
npx husky install
npx husky add .husky/commit-msg 'npx commitlint --edit $1'
npx husky add .husky/prepare-commit-msg 'exec < /dev/tty && node_modules/.bin/cz --hook || true'

# Package.json script
{
  "scripts": {
    "prepare": "husky install"
  }
}
```

## Automazione e CI/CD

### 1. Semantic Release
```bash
# Installazione
npm install --save-dev semantic-release

# Configurazione
cat > .releaserc.json << 'EOF'
{
  "branches": ["main"],
  "plugins": [
    "@semantic-release/commit-analyzer",
    "@semantic-release/release-notes-generator",
    "@semantic-release/changelog",
    "@semantic-release/npm",
    "@semantic-release/github"
  ]
}
EOF

# GitHub Actions workflow
cat > .github/workflows/release.yml << 'EOF'
name: Release
on:
  push:
    branches: [main]
jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: actions/setup-node@v3
      - run: npm ci
      - run: npx semantic-release
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
          NPM_TOKEN: ${{ secrets.NPM_TOKEN }}
EOF
```

### 2. Conventional Changelog
```bash
# Installazione
npm install --save-dev conventional-changelog-cli

# Script per generazione changelog
{
  "scripts": {
    "changelog": "conventional-changelog -p angular -i CHANGELOG.md -s",
    "changelog:minor": "conventional-changelog -p angular -i CHANGELOG.md -s -r 0"
  }
}

# Automazione con GitHub Actions
cat > .github/workflows/changelog.yml << 'EOF'
name: Update Changelog
on:
  release:
    types: [created]
jobs:
  changelog:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - run: npm run changelog
      - uses: stefanzweifel/git-auto-commit-action@v4
        with:
          commit_message: 'docs: update CHANGELOG.md'
          file_pattern: CHANGELOG.md
EOF
```

### 3. Version Bumping
```bash
# Script automatico per versioning
cat > scripts/version-bump.js << 'EOF'
const { execSync } = require('child_process');
const fs = require('fs');

// Analizzare commit dalla ultima release
const commits = execSync('git log $(git describe --tags --abbrev=0)..HEAD --pretty=format:"%s"')
  .toString().split('\n').filter(Boolean);

let versionType = 'patch';

for (const commit of commits) {
  if (commit.includes('BREAKING CHANGE') || commit.includes('!:')) {
    versionType = 'major';
    break;
  } else if (commit.startsWith('feat')) {
    versionType = 'minor';
  }
}

console.log(`Bumping ${versionType} version`);
execSync(`npm version ${versionType}`);
EOF

# Usage
node scripts/version-bump.js
```

## Template e Configurazioni

### 1. Commit Template Personalizzato
```bash
# Template per conventional commits
cat > .gitmessage << 'EOF'
# <type>[optional scope]: <description>
# |<----  Using a Maximum Of 50 Characters  ---->|

# Explain why this change is being made
# |<----   Try To Limit Each Line to a Maximum Of 72 Characters   ---->|

# Provide links or keys to any relevant tickets, articles or other resources
# Example: Closes #23

# --- COMMIT END ---
# Type can be 
#    feat     (new feature)
#    fix      (bug fix)
#    refactor (refactoring production code)
#    style    (formatting, missing semi colons, etc; no code change)
#    docs     (changes to documentation)
#    test     (adding or refactoring tests; no production code change)
#    chore    (updating grunt tasks etc; no production code change)
# Scope is just the scope of the change
# Remember to use imperative mood in the subject line
# Remember to capitalize the subject line
# Do not end the subject line with a period
# Separate subject from body with a blank line
# Use the body to explain what and why vs. how
# Can use multiple lines with "-" for bullet points in body
EOF

git config commit.template .gitmessage
```

### 2. VS Code Extension Configuration
```json
// .vscode/settings.json
{
  "conventionalCommits.scopes": [
    "api",
    "ui", 
    "database",
    "auth",
    "payment",
    "notification",
    "admin",
    "mobile",
    "web"
  ],
  "conventionalCommits.showEditor": true,
  "conventionalCommits.emojiFormat": "emoji",
  "conventionalCommits.promptFooter": true
}
```

### 3. Custom Commitizen Adapter
```javascript
// cz-custom-changelog.js
module.exports = {
  prompter: function(cz, commit) {
    cz.prompt([
      {
        type: 'list',
        name: 'type',
        message: 'Select the type of change:',
        choices: [
          { value: 'feat', name: '✨ feat: A new feature' },
          { value: 'fix', name: '🐛 fix: A bug fix' },
          { value: 'docs', name: '📚 docs: Documentation only changes' },
          { value: 'style', name: '💎 style: Changes that do not affect meaning' },
          { value: 'refactor', name: '📦 refactor: A code change that neither fixes a bug nor adds a feature' },
          { value: 'perf', name: '🚀 perf: A code change that improves performance' },
          { value: 'test', name: '🚨 test: Adding missing tests' },
          { value: 'chore', name: '🔧 chore: Changes to the build process' }
        ]
      },
      {
        type: 'input',
        name: 'scope',
        message: 'What is the scope of this change (e.g. component, file name)? (optional)'
      },
      {
        type: 'input',
        name: 'subject',
        message: 'Write a short, imperative tense description:'
      },
      {
        type: 'input',
        name: 'body',
        message: 'Provide a longer description: (optional)'
      },
      {
        type: 'input',
        name: 'breaking',
        message: 'List any breaking changes: (optional)'
      },
      {
        type: 'input',
        name: 'issues',
        message: 'List any issues closed: (optional)'
      }
    ]).then(function(answers) {
      const scope = answers.scope ? `(${answers.scope})` : '';
      const breaking = answers.breaking ? `BREAKING CHANGE: ${answers.breaking}` : '';
      const issues = answers.issues ? `Closes ${answers.issues}` : '';
      
      const body = [answers.body, breaking, issues]
        .filter(Boolean)
        .join('\n\n');
      
      commit(`${answers.type}${scope}: ${answers.subject}\n\n${body}`);
    });
  }
};
```

## Analisi e Metriche

### 1. Script Analisi Conventional Commits
```bash
#!/bin/bash
# analyze-conventional.sh

echo "📊 Conventional Commits Analysis (last 100 commits)"

# Analisi tipi di commit
echo -e "\n📋 Commit Types:"
git log --pretty=format:"%s" -100 | \
  grep -oE '^[a-z]+(\([^)]+\))?' | \
  sed 's/(.*//' | \
  sort | uniq -c | sort -nr

# Verificare compliance
echo -e "\n✅ Conventional Format Compliance:"
total=$(git log --oneline -100 | wc -l)
conventional=$(git log --pretty=format:"%s" -100 | \
  grep -cE '^(feat|fix|docs|style|refactor|test|chore|build|ci|perf)(\(.+\))?: .+')

compliance=$((conventional * 100 / total))
echo "Compliance rate: $compliance% ($conventional/$total)"

# Commit non conformi
echo -e "\n❌ Non-conventional commits:"
git log --pretty=format:"%h %s" -100 | \
  grep -vE '^[a-f0-9]+ (feat|fix|docs|style|refactor|test|chore|build|ci|perf)(\(.+\))?: .+'
```

### 2. Validazione CI
```yaml
# .github/workflows/conventional-commits.yml
name: Validate Conventional Commits
on: [pull_request]
jobs:
  validate:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0
      - uses: wagoid/commitlint-github-action@v5
        with:
          configFile: .commitlintrc.js
```

## Best Practices

### 1. Team Guidelines
```markdown
# Team Conventional Commits Guidelines

## Required Types
- `feat`: New features visible to users
- `fix`: Bug fixes visible to users
- `docs`: Documentation changes
- `chore`: Maintenance tasks

## Scopes (when applicable)
- Component names: `feat(Button): add loading state`
- File/module names: `fix(auth): resolve token expiration`
- Feature areas: `perf(api): optimize query performance`

## Writing Guidelines
- Use lowercase for everything except BREAKING CHANGE
- Keep subject line under 50 characters
- Use imperative mood: "add" not "adds" or "added"
- Don't end subject with period
- Provide body for complex changes
```

### 2. Automation Best Practices
```bash
# Pre-commit hook per conventional commits
#!/bin/bash
# .git/hooks/commit-msg

# Verificare formato conventional
if ! grep -qE '^(feat|fix|docs|style|refactor|test|chore|build|ci|perf)(\(.+\))?: .{1,50}' "$1"; then
    echo "❌ Commit message must follow conventional format"
    echo "Format: <type>[scope]: <description>"
    echo "Example: feat(auth): add two-factor authentication"
    exit 1
fi

# Verificare lunghezza subject
subject=$(head -n1 "$1")
if [ ${#subject} -gt 50 ]; then
    echo "⚠️ Subject line too long (${#subject} chars, max 50)"
    exit 1
fi

echo "✅ Conventional commit format validated"
```

## Conclusioni
Conventional Commits standardizza la comunicazione attraverso commit message, abilitando automazione potente per versioning, changelog e release management. È essenziale per team che vogliono workflow automatizzati e history leggibile.
