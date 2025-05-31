# Esempio 3: Automazione Commit e Release

Questo esempio mostra come implementare un sistema completo di automazione per commit, validazione e rilasci utilizzando conventional commits e strumenti di CI/CD.

## Scenario: Sistema DevOps per Microservizi

Implementiamo un workflow automatizzato per un'architettura a microservizi con:
- Validazione automatica dei commit
- Generazione automatica dei changelog
- Rilasci automatici basati sui commit
- Integrazione con GitHub Actions

## Setup del Progetto

### 1. Inizializzazione Repository

```bash
# Creare nuovo repository
mkdir microservices-platform && cd microservices-platform
git init

# Struttura del progetto
mkdir -p {services/{auth,api,web},tools/{scripts,configs},docs}

# File di configurazione base
cat > package.json << 'EOF'
{
  "name": "microservices-platform",
  "version": "1.0.0",
  "private": true,
  "workspaces": [
    "services/*"
  ],
  "devDependencies": {
    "@commitlint/cli": "^17.0.0",
    "@commitlint/config-conventional": "^17.0.0",
    "commitizen": "^4.3.0",
    "cz-conventional-changelog": "^3.3.0",
    "husky": "^8.0.0",
    "lint-staged": "^13.0.0",
    "standard-version": "^9.5.0",
    "semantic-release": "^20.0.0"
  },
  "scripts": {
    "commit": "cz",
    "release": "standard-version",
    "semantic-release": "semantic-release"
  },
  "config": {
    "commitizen": {
      "path": "./node_modules/cz-conventional-changelog"
    }
  }
}
EOF
```

### 2. Configurazione Commit Tools

```bash
# Commitlint config
cat > commitlint.config.js << 'EOF'
module.exports = {
  extends: ['@commitlint/config-conventional'],
  rules: {
    'type-enum': [
      2,
      'always',
      [
        'feat',     // nuova funzionalità
        'fix',      // correzione bug
        'docs',     // documentazione
        'style',    // formattazione
        'refactor', // refactoring
        'perf',     // miglioramento performance
        'test',     // test
        'chore',    // task di manutenzione
        'ci',       // continuous integration
        'build',    // build system
        'revert'    // revert commit
      ]
    ],
    'subject-max-length': [2, 'always', 72],
    'subject-case': [2, 'always', 'lower-case'],
    'body-max-line-length': [2, 'always', 100],
    'footer-max-line-length': [2, 'always', 100]
  }
};
EOF

# Semantic Release config
cat > .releaserc.json << 'EOF'
{
  "branches": ["main", "develop"],
  "plugins": [
    "@semantic-release/commit-analyzer",
    "@semantic-release/release-notes-generator",
    "@semantic-release/changelog",
    "@semantic-release/npm",
    "@semantic-release/github",
    "@semantic-release/git"
  ],
  "preset": "conventionalcommits",
  "releaseRules": [
    {"type": "feat", "release": "minor"},
    {"type": "fix", "release": "patch"},
    {"type": "perf", "release": "patch"},
    {"breaking": true, "release": "major"}
  ]
}
EOF
```

### 3. Git Hooks Setup

```bash
# Installare dipendenze
npm install

# Configurare Husky
npx husky install
npx husky add .husky/commit-msg 'npx --no -- commitlint --edit ${1}'
npx husky add .husky/pre-commit 'npx lint-staged'

# Lint-staged config
cat > .lintstagedrc.json << 'EOF'
{
  "*.{js,ts,json,md}": [
    "prettier --write"
  ],
  "*.{js,ts}": [
    "eslint --fix"
  ]
}
EOF
```

## Workflow di Sviluppo Automatizzato

### 1. Feature Development

```bash
# Creare feature branch
git checkout -b feature/user-authentication

# Sviluppare autenticazione utente
mkdir -p services/auth/src
cat > services/auth/src/auth.js << 'EOF'
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');

class AuthService {
  constructor() {
    this.users = new Map();
    this.jwtSecret = process.env.JWT_SECRET || 'dev-secret';
  }

  async register(username, password, email) {
    if (this.users.has(username)) {
      throw new Error('User already exists');
    }

    const hashedPassword = await bcrypt.hash(password, 10);
    const user = {
      username,
      password: hashedPassword,
      email,
      createdAt: new Date(),
      isActive: true
    };

    this.users.set(username, user);
    return this.generateToken(user);
  }

  async login(username, password) {
    const user = this.users.get(username);
    if (!user || !user.isActive) {
      throw new Error('Invalid credentials');
    }

    const isValid = await bcrypt.compare(password, user.password);
    if (!isValid) {
      throw new Error('Invalid credentials');
    }

    return this.generateToken(user);
  }

  generateToken(user) {
    return jwt.sign(
      { username: user.username, email: user.email },
      this.jwtSecret,
      { expiresIn: '24h' }
    );
  }

  validateToken(token) {
    try {
      return jwt.verify(token, this.jwtSecret);
    } catch (error) {
      throw new Error('Invalid token');
    }
  }
}

module.exports = AuthService;
EOF

# Package.json per auth service
cat > services/auth/package.json << 'EOF'
{
  "name": "@platform/auth",
  "version": "1.0.0",
  "main": "src/auth.js",
  "dependencies": {
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0"
  }
}
EOF

# Commit con conventional commits usando Commitizen
npm run commit
# Seguire il prompt interattivo:
# ? Select the type of change: feat
# ? What is the scope: auth
# ? Write a short description: implement user authentication service
# ? Provide a longer description: Add AuthService class with registration, login, and JWT token management
# ? Are there any breaking changes? No
# ? Does this change affect any open issues? No
```

### 2. Bug Fix con Automated Testing

```bash
# Scoprire bug nella validazione
cat > services/auth/src/validation.js << 'EOF'
const EMAIL_REGEX = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
const PASSWORD_MIN_LENGTH = 8;

class ValidationService {
  static validateEmail(email) {
    if (!email || typeof email !== 'string') {
      throw new Error('Email is required and must be a string');
    }
    
    if (!EMAIL_REGEX.test(email)) {
      throw new Error('Invalid email format');
    }
    
    return true;
  }

  static validatePassword(password) {
    if (!password || typeof password !== 'string') {
      throw new Error('Password is required and must be a string');
    }
    
    if (password.length < PASSWORD_MIN_LENGTH) {
      throw new Error(`Password must be at least ${PASSWORD_MIN_LENGTH} characters long`);
    }
    
    // Bug: non controlla caratteri speciali
    const hasUpperCase = /[A-Z]/.test(password);
    const hasLowerCase = /[a-z]/.test(password);
    const hasNumbers = /\d/.test(password);
    
    if (!hasUpperCase || !hasLowerCase || !hasNumbers) {
      throw new Error('Password must contain uppercase, lowercase, and numbers');
    }
    
    return true;
  }

  static validateUsername(username) {
    if (!username || typeof username !== 'string') {
      throw new Error('Username is required and must be a string');
    }
    
    if (username.length < 3 || username.length > 20) {
      throw new Error('Username must be between 3 and 20 characters');
    }
    
    const validPattern = /^[a-zA-Z0-9_]+$/;
    if (!validPattern.test(username)) {
      throw new Error('Username can only contain letters, numbers, and underscores');
    }
    
    return true;
  }
}

module.exports = ValidationService;
EOF

# Commit del bug
git add services/auth/src/validation.js
git commit -m "feat(auth): add password validation service

Add ValidationService class for email, password, and username validation
with comprehensive rules and error handling"

# Creare test per identificare il bug
mkdir -p services/auth/tests
cat > services/auth/tests/validation.test.js << 'EOF'
const ValidationService = require('../src/validation');

describe('ValidationService', () => {
  describe('validatePassword', () => {
    test('should accept strong password with special characters', () => {
      expect(() => {
        ValidationService.validatePassword('MyP@ssw0rd!');
      }).not.toThrow();
    });

    test('should reject password without special characters', () => {
      expect(() => {
        ValidationService.validatePassword('MyPassword123');
      }).toThrow('Password must contain special characters');
    });
  });
});
EOF

# Il test fallisce - identifichiamo il bug
npm test # Fallisce

# Fix del bug
git add services/auth/src/validation.js
# Modify validation.js to include special character check
cat > services/auth/src/validation.js << 'EOF'
const EMAIL_REGEX = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
const PASSWORD_MIN_LENGTH = 8;

class ValidationService {
  static validateEmail(email) {
    if (!email || typeof email !== 'string') {
      throw new Error('Email is required and must be a string');
    }
    
    if (!EMAIL_REGEX.test(email)) {
      throw new Error('Invalid email format');
    }
    
    return true;
  }

  static validatePassword(password) {
    if (!password || typeof password !== 'string') {
      throw new Error('Password is required and must be a string');
    }
    
    if (password.length < PASSWORD_MIN_LENGTH) {
      throw new Error(`Password must be at least ${PASSWORD_MIN_LENGTH} characters long`);
    }
    
    const hasUpperCase = /[A-Z]/.test(password);
    const hasLowerCase = /[a-z]/.test(password);
    const hasNumbers = /\d/.test(password);
    const hasSpecialChars = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password);
    
    if (!hasUpperCase || !hasLowerCase || !hasNumbers || !hasSpecialChars) {
      throw new Error('Password must contain uppercase, lowercase, numbers, and special characters');
    }
    
    return true;
  }

  static validateUsername(username) {
    if (!username || typeof username !== 'string') {
      throw new Error('Username is required and must be a string');
    }
    
    if (username.length < 3 || username.length > 20) {
      throw new Error('Username must be between 3 and 20 characters');
    }
    
    const validPattern = /^[a-zA-Z0-9_]+$/;
    if (!validPattern.test(username)) {
      throw new Error('Username can only contain letters, numbers, and underscores');
    }
    
    return true;
  }
}

module.exports = ValidationService;
EOF

# Commit del fix
npm run commit
# ? Select the type of change: fix
# ? What is the scope: auth
# ? Write a short description: add special characters requirement to password validation
# ? Provide a longer description: Fix password validation to require special characters for enhanced security
```

### 3. GitHub Actions Workflow

```bash
# Creare workflow CI/CD
mkdir -p .github/workflows
cat > .github/workflows/ci-cd.yml << 'EOF'
name: CI/CD Pipeline

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    strategy:
      matrix:
        node-version: [16.x, 18.x, 20.x]
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v3
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run linting
      run: npm run lint
    
    - name: Run tests
      run: npm test -- --coverage
    
    - name: Upload coverage
      uses: codecov/codecov-action@v3
      if: matrix.node-version == '18.x'

  validate-commits:
    runs-on: ubuntu-latest
    if: github.event_name == 'pull_request'
    
    steps:
    - uses: actions/checkout@v3
      with:
        fetch-depth: 0
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18.x'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Validate commit messages
      run: npx commitlint --from ${{ github.event.pull_request.base.sha }} --to ${{ github.event.pull_request.head.sha }} --verbose

  security-scan:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Run security audit
      run: npm audit
    
    - name: Run CodeQL Analysis
      uses: github/codeql-action/init@v2
      with:
        languages: javascript
    
    - name: Perform CodeQL Analysis
      uses: github/codeql-action/analyze@v2

  release:
    needs: [test, validate-commits, security-scan]
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    
    steps:
    - uses: actions/checkout@v3
      with:
        fetch-depth: 0
        token: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18.x'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Semantic Release
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        NPM_TOKEN: ${{ secrets.NPM_TOKEN }}
      run: npx semantic-release

  deploy:
    needs: release
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Deploy to production
      env:
        DEPLOY_TOKEN: ${{ secrets.DEPLOY_TOKEN }}
      run: |
        echo "Deploying to production environment..."
        # Add deployment commands here
EOF
```

### 4. Monitoraggio e Metriche

```bash
# Script per analisi commit
cat > tools/scripts/commit-analysis.js << 'EOF'
#!/usr/bin/env node

const { execSync } = require('child_process');
const fs = require('fs');

class CommitAnalyzer {
  constructor() {
    this.commitTypes = {};
    this.authors = {};
    this.monthlyStats = {};
  }

  analyzeCommits(since = '1 year ago') {
    const gitLog = execSync(`git log --since="${since}" --pretty=format:"%H|%an|%ad|%s" --date=short`, 
      { encoding: 'utf8' });
    
    const commits = gitLog.split('\n').filter(line => line.trim());
    
    commits.forEach(commit => {
      const [hash, author, date, message] = commit.split('|');
      this.processCommit(hash, author, date, message);
    });

    return this.generateReport();
  }

  processCommit(hash, author, date, message) {
    // Analizzare tipo di commit
    const typeMatch = message.match(/^(\w+)(\(.+\))?:/);
    const type = typeMatch ? typeMatch[1] : 'other';
    
    this.commitTypes[type] = (this.commitTypes[type] || 0) + 1;
    
    // Analizzare autore
    if (!this.authors[author]) {
      this.authors[author] = { total: 0, types: {} };
    }
    this.authors[author].total++;
    this.authors[author].types[type] = (this.authors[author].types[type] || 0) + 1;
    
    // Statistiche mensili
    const month = date.substring(0, 7); // YYYY-MM
    if (!this.monthlyStats[month]) {
      this.monthlyStats[month] = { total: 0, types: {} };
    }
    this.monthlyStats[month].total++;
    this.monthlyStats[month].types[type] = (this.monthlyStats[month].types[type] || 0) + 1;
  }

  generateReport() {
    const report = {
      summary: {
        totalCommits: Object.values(this.commitTypes).reduce((a, b) => a + b, 0),
        uniqueAuthors: Object.keys(this.authors).length,
        timespan: Object.keys(this.monthlyStats).length + ' months'
      },
      commitTypes: this.commitTypes,
      topAuthors: Object.entries(this.authors)
        .sort((a, b) => b[1].total - a[1].total)
        .slice(0, 10),
      monthlyTrends: this.monthlyStats,
      compliance: this.calculateCompliance()
    };

    return report;
  }

  calculateCompliance() {
    const total = Object.values(this.commitTypes).reduce((a, b) => a + b, 0);
    const conventional = ['feat', 'fix', 'docs', 'style', 'refactor', 'perf', 'test', 'chore', 'ci', 'build'];
    const compliantCommits = conventional.reduce((sum, type) => sum + (this.commitTypes[type] || 0), 0);
    
    return {
      percentage: ((compliantCommits / total) * 100).toFixed(2),
      compliantCommits,
      totalCommits: total
    };
  }
}

// Utilizzo
if (require.main === module) {
  const analyzer = new CommitAnalyzer();
  const report = analyzer.analyzeCommits();
  
  console.log('📊 COMMIT ANALYSIS REPORT');
  console.log('========================\n');
  
  console.log('📈 Summary:');
  console.log(`   Total Commits: ${report.summary.totalCommits}`);
  console.log(`   Authors: ${report.summary.uniqueAuthors}`);
  console.log(`   Timespan: ${report.summary.timespan}\n`);
  
  console.log('🏷️  Commit Types:');
  Object.entries(report.commitTypes)
    .sort((a, b) => b[1] - a[1])
    .forEach(([type, count]) => {
      console.log(`   ${type}: ${count}`);
    });
  
  console.log('\n✅ Conventional Commits Compliance:');
  console.log(`   ${report.compliance.percentage}% compliant`);
  console.log(`   ${report.compliance.compliantCommits}/${report.compliance.totalCommits} commits`);
  
  // Salvare report JSON
  fs.writeFileSync('commit-analysis.json', JSON.stringify(report, null, 2));
  console.log('\n💾 Report saved to commit-analysis.json');
}

module.exports = CommitAnalyzer;
EOF

chmod +x tools/scripts/commit-analysis.js

# Commit degli strumenti
git add .
npm run commit
# ? Select the type of change: feat
# ? What is the scope: tooling
# ? Write a short description: add automated commit analysis and CI/CD pipeline
# ? Provide a longer description: Implement comprehensive DevOps automation with GitHub Actions, semantic release, and commit analysis tools
```

## Utilizzo Avanzato

### 1. Release Automatico

```bash
# Merge su main per trigger release
git checkout main
git merge feature/user-authentication

# Il workflow GitHub Actions:
# 1. Esegue test automatici
# 2. Valida commit messages
# 3. Esegue security scan
# 4. Genera release automatico
# 5. Aggiorna CHANGELOG
# 6. Crea GitHub release
# 7. Deploy automatico

# Controllare release generato
git tag --list
git show --name-only v1.1.0
```

### 2. Hotfix Process

```bash
# Creare hotfix branch
git checkout -b hotfix/security-patch main

# Fix di sicurezza critico
cat > services/auth/src/security.js << 'EOF'
const rateLimit = require('express-rate-limit');
const helmet = require('helmet');

const authLimiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minuti
  max: 5, // limite tentativi
  message: 'Too many authentication attempts',
  standardHeaders: true,
  legacyHeaders: false,
});

const securityMiddleware = [
  helmet(),
  authLimiter
];

module.exports = { authLimiter, securityMiddleware };
EOF

# Commit hotfix
git add .
npm run commit
# ? Select the type of change: fix
# ? What is the scope: security
# ? Write a short description: implement rate limiting for authentication endpoints
# ? Provide a longer description: Add rate limiting and security headers to prevent brute force attacks
# ? Are there any breaking changes? No
# ? Does this change affect any open issues? Closes #123

# Merge hotfix
git checkout main
git merge hotfix/security-patch

# Release automatico patch (v1.1.1)
```

### 3. Metrics e Monitoring

```bash
# Eseguire analisi commit
node tools/scripts/commit-analysis.js

# Output esempio:
# 📊 COMMIT ANALYSIS REPORT
# ========================
# 
# 📈 Summary:
#    Total Commits: 45
#    Authors: 3
#    Timespan: 6 months
# 
# 🏷️  Commit Types:
#    feat: 18
#    fix: 12
#    docs: 8
#    refactor: 4
#    test: 3
# 
# ✅ Conventional Commits Compliance:
#    95.56% compliant
#    43/45 commits

# Visualizzare trend
cat commit-analysis.json | jq '.monthlyTrends'
```

## Integrazione Enterprise

### 1. Slack Notifications

```bash
# Webhook per notifiche Slack
cat > .github/workflows/notifications.yml << 'EOF'
name: Slack Notifications

on:
  push:
    branches: [ main ]
  release:
    types: [ published ]

jobs:
  notify:
    runs-on: ubuntu-latest
    
    steps:
    - name: Slack Notification - Push
      if: github.event_name == 'push'
      uses: 8398a7/action-slack@v3
      with:
        status: ${{ job.status }}
        text: |
          🚀 New commit pushed to main
          Author: ${{ github.actor }}
          Commit: ${{ github.event.head_commit.message }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}
    
    - name: Slack Notification - Release
      if: github.event_name == 'release'
      uses: 8398a7/action-slack@v3
      with:
        status: success
        text: |
          🎉 New release published!
          Version: ${{ github.event.release.tag_name }}
          Release Notes: ${{ github.event.release.html_url }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}
EOF
```

### 2. JIRA Integration

```bash
# Configurazione per JIRA tickets
cat > .github/workflows/jira-integration.yml << 'EOF'
name: JIRA Integration

on:
  push:
    branches: [ main, develop ]

jobs:
  jira-transition:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Extract JIRA Issue
      id: jira
      run: |
        # Estrarre numero ticket da commit message
        TICKET=$(git log -1 --pretty=%B | grep -oE '[A-Z]+-[0-9]+' | head -1)
        echo "ticket=$TICKET" >> $GITHUB_OUTPUT
    
    - name: Transition JIRA Issue
      if: steps.jira.outputs.ticket
      uses: atlassian/gajira-transition@master
      with:
        issue: ${{ steps.jira.outputs.ticket }}
        transition: "In Review"
      env:
        JIRA_BASE_URL: ${{ secrets.JIRA_BASE_URL }}
        JIRA_USER_EMAIL: ${{ secrets.JIRA_USER_EMAIL }}
        JIRA_API_TOKEN: ${{ secrets.JIRA_API_TOKEN }}
EOF
```

## Conclusioni

Questo esempio dimostra un ecosistema completo di automazione commit che include:

### Caratteristiche Implementate:
- **Conventional Commits** con validazione automatica
- **Semantic Release** per versioning automatico
- **CI/CD Pipeline** completa con GitHub Actions
- **Quality Gates** con test, linting e security scan
- **Automated Changelog** generation
- **Metrics e Analytics** per commit compliance
- **Enterprise Integration** con Slack e JIRA

### Benefici:
- **Consistenza**: Standard uniformi per tutti i commit
- **Automazione**: Release e deploy automatici
- **Qualità**: Quality gates automatici
- **Tracciabilità**: Collegamenti automatici con issue tracker
- **Compliance**: Monitoraggio delle best practices
- **Visibilità**: Notifiche e metriche in tempo reale

### Best Practices:
- Utilizzo di conventional commits per semantic versioning
- Integrazione di quality gates nel workflow
- Automazione completa della release pipeline
- Monitoraggio continuo della code quality
- Documentazione automatica dei cambiamenti

Questo workflow è scalabile e adattabile a progetti di qualsiasi dimensione, dal team di sviluppo singolo alle grandi organizzazioni enterprise.
