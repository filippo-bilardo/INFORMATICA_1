# 02 - Release Automatizzate con GitHub Actions

Questo esempio mostra come implementare un sistema di release completamente automatizzato utilizzando GitHub Actions e Conventional Commits.

## Scenario

Sviluppiamo un'API REST in Node.js con release automatiche basate sui commit messages.

## Setup Iniziale

### 1. Struttura del Progetto

```bash
mkdir automated-api-releases
cd automated-api-releases

# Inizializza progetto Node.js
npm init -y

# Installa dipendenze
npm install express cors helmet morgan
npm install --save-dev jest supertest nodemon
```

### 2. Codice Base dell'API

**src/app.js**:
```javascript
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');

const app = express();

// Middleware
app.use(helmet());
app.use(cors());
app.use(morgan('combined'));
app.use(express.json());

// Routes
app.get('/health', (req, res) => {
  res.json({ status: 'ok', timestamp: new Date().toISOString() });
});

app.get('/api/version', (req, res) => {
  const version = process.env.npm_package_version || '1.0.0';
  res.json({ version, name: 'Automated API' });
});

app.get('/api/users', (req, res) => {
  res.json([
    { id: 1, name: 'Alice', email: 'alice@example.com' },
    { id: 2, name: 'Bob', email: 'bob@example.com' }
  ]);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
```

**package.json** (aggiorna gli script):
```json
{
  "scripts": {
    "start": "node src/app.js",
    "dev": "nodemon src/app.js",
    "test": "jest",
    "test:ci": "jest --ci --coverage"
  },
  "jest": {
    "testEnvironment": "node"
  }
}
```

### 3. Test Automatizzati

**tests/app.test.js**:
```javascript
const request = require('supertest');
const app = require('../src/app');

describe('API Tests', () => {
  test('GET /health should return 200', async () => {
    const response = await request(app).get('/health');
    expect(response.status).toBe(200);
    expect(response.body.status).toBe('ok');
  });

  test('GET /api/version should return version info', async () => {
    const response = await request(app).get('/api/version');
    expect(response.status).toBe(200);
    expect(response.body).toHaveProperty('version');
    expect(response.body).toHaveProperty('name');
  });

  test('GET /api/users should return users array', async () => {
    const response = await request(app).get('/api/users');
    expect(response.status).toBe(200);
    expect(Array.isArray(response.body)).toBe(true);
    expect(response.body.length).toBeGreaterThan(0);
  });
});
```

## Configurazione Release Automatiche

### 1. Workflow GitHub Actions

**.github/workflows/release.yml**:
```yaml
name: Automated Release

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run tests
        run: npm run test:ci
      
      - name: Upload coverage
        uses: codecov/codecov-action@v3
        if: success()

  release:
    needs: test
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          token: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Semantic Release
        uses: cycjimmy/semantic-release-action@v4
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
          NPM_TOKEN: ${{ secrets.NPM_TOKEN }}
        with:
          semantic_version: 21
          extra_plugins: |
            @semantic-release/changelog
            @semantic-release/git
```

### 2. Configurazione Semantic Release

**release.config.js**:
```javascript
module.exports = {
  branches: ['main'],
  plugins: [
    [
      '@semantic-release/commit-analyzer',
      {
        preset: 'conventionalcommits',
        releaseRules: [
          { type: 'feat', release: 'minor' },
          { type: 'fix', release: 'patch' },
          { type: 'perf', release: 'patch' },
          { type: 'revert', release: 'patch' },
          { type: 'docs', release: false },
          { type: 'style', release: false },
          { type: 'chore', release: false },
          { type: 'refactor', release: 'patch' },
          { type: 'test', release: false },
          { type: 'build', release: false },
          { type: 'ci', release: false },
          { breaking: true, release: 'major' }
        ]
      }
    ],
    [
      '@semantic-release/release-notes-generator',
      {
        preset: 'conventionalcommits',
        presetConfig: {
          types: [
            { type: 'feat', section: '🚀 Features' },
            { type: 'fix', section: '🐛 Bug Fixes' },
            { type: 'perf', section: '⚡ Performance' },
            { type: 'revert', section: '⏪ Reverts' },
            { type: 'refactor', section: '♻️ Refactoring' }
          ]
        }
      }
    ],
    [
      '@semantic-release/changelog',
      {
        changelogFile: 'CHANGELOG.md'
      }
    ],
    '@semantic-release/npm',
    [
      '@semantic-release/github',
      {
        assets: [
          {
            path: 'dist/**',
            label: 'Distribution files'
          }
        ]
      }
    ],
    [
      '@semantic-release/git',
      {
        assets: ['CHANGELOG.md', 'package.json'],
        message: 'chore(release): ${nextRelease.version} [skip ci]\n\n${nextRelease.notes}'
      }
    ]
  ]
};
```

### 3. Configurazione Conventional Commits

**.gitmessage**:
```
# <type>[optional scope]: <description>
#
# [optional body]
#
# [optional footer(s)]
#
# Types:
# feat:     A new feature
# fix:      A bug fix
# docs:     Documentation only changes
# style:    Changes that do not affect the meaning of the code
# refactor: A code change that neither fixes a bug nor adds a feature
# perf:     A code change that improves performance
# test:     Adding missing tests or correcting existing tests
# build:    Changes that affect the build system or external dependencies
# ci:       Changes to our CI configuration files and scripts
# chore:    Other changes that don't modify src or test files
# revert:   Reverts a previous commit
#
# Breaking changes: add "BREAKING CHANGE:" in the footer
# Issues: reference with "Closes #123" or "Fixes #456"
```

## Workflow di Sviluppo

### 1. Inizializzazione Repository

```bash
# Inizializza Git
git init
git add .
git commit -m "feat: initial API implementation

- Add Express.js REST API
- Add health check endpoint
- Add user management endpoints
- Add comprehensive test suite"

# Collega a GitHub
git remote add origin https://github.com/username/automated-api-releases.git
git branch -M main
git push -u origin main
```

### 2. Sviluppo Feature

```bash
# Crea branch feature
git checkout -b feature/authentication

# Implementa autenticazione
# ... codice ...

# Commit con conventional format
git add .
git commit -m "feat(auth): add JWT authentication

- Add login/logout endpoints
- Add JWT token validation middleware
- Add user session management
- Add authentication tests

Closes #15"

# Push e crea PR
git push origin feature/authentication
```

### 3. Bug Fix

```bash
# Crea branch hotfix
git checkout -b fix/cors-headers

# Implementa fix
# ... codice ...

git add .
git commit -m "fix(cors): resolve CORS headers issue

The API was not properly handling preflight OPTIONS requests
for cross-origin requests from frontend applications.

- Add proper CORS configuration
- Add OPTIONS handler for all routes
- Update CORS tests

Fixes #23"

git push origin fix/cors-headers
```

### 4. Breaking Change

```bash
git checkout -b feat/api-v2

# Implementa breaking changes
# ... codice ...

git add .
git commit -m "feat(api): migrate to v2 API structure

BREAKING CHANGE: API endpoints have been restructured

- Move all endpoints under /api/v2/ prefix
- Change response format to include metadata
- Remove deprecated /users endpoint
- Add pagination to all list endpoints

Migration guide:
- Update all API calls to use /api/v2/ prefix
- Handle new response format with data/meta structure
- Update pagination parameters

Closes #45"

git push origin feat/api-v2
```

## Risultati Automatici

### 1. Semantic Versioning Automatico

- **feat**: incrementa MINOR version (1.0.0 → 1.1.0)
- **fix**: incrementa PATCH version (1.1.0 → 1.1.1)
- **BREAKING CHANGE**: incrementa MAJOR version (1.1.1 → 2.0.0)

### 2. Changelog Automatico

**CHANGELOG.md** generato automaticamente:
```markdown
# Changelog

## [2.0.0](https://github.com/username/automated-api-releases/compare/v1.1.1...v2.0.0) (2025-05-28)

### ⚠ BREAKING CHANGES

* **api:** API endpoints have been restructured

### 🚀 Features

* **api:** migrate to v2 API structure ([abc123](https://github.com/username/automated-api-releases/commit/abc123))
* **auth:** add JWT authentication ([def456](https://github.com/username/automated-api-releases/commit/def456))

### 🐛 Bug Fixes

* **cors:** resolve CORS headers issue ([ghi789](https://github.com/username/automated-api-releases/commit/ghi789))
```

### 3. Release GitHub Automatica

La release viene creata automaticamente con:
- **Tag**: v2.0.0
- **Release Notes**: estratte dal changelog
- **Assets**: file di distribuzione allegati
- **Notifiche**: team notificato automaticamente

## Monitoraggio e Alerting

### 1. Workflow Status Checks

**.github/workflows/monitor.yml**:
```yaml
name: Release Monitor

on:
  release:
    types: [published]

jobs:
  notify:
    runs-on: ubuntu-latest
    steps:
      - name: Notify Slack
        uses: 8398a7/action-slack@v3
        with:
          status: success
          channel: '#releases'
          message: |
            🚀 New release published: ${{ github.event.release.tag_name }}
            📝 Release notes: ${{ github.event.release.html_url }}
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
      
      - name: Update monitoring
        run: |
          curl -X POST "${{ secrets.MONITORING_WEBHOOK }}" \
            -H "Content-Type: application/json" \
            -d "{
              \"version\": \"${{ github.event.release.tag_name }}\",
              \"timestamp\": \"$(date -u +%Y-%m-%dT%H:%M:%S.%3NZ)\",
              \"environment\": \"production\"
            }"
```

### 2. Health Check Post-Release

```yaml
name: Post-Release Validation

on:
  release:
    types: [published]

jobs:
  validate:
    runs-on: ubuntu-latest
    steps:
      - name: Wait for deployment
        run: sleep 60
      
      - name: Health check
        run: |
          for i in {1..5}; do
            if curl -f "${{ secrets.PRODUCTION_URL }}/health"; then
              echo "✅ Health check passed"
              exit 0
            fi
            echo "⏳ Waiting for deployment... ($i/5)"
            sleep 30
          done
          echo "❌ Health check failed"
          exit 1
      
      - name: Rollback on failure
        if: failure()
        run: |
          echo "🚨 Triggering rollback procedure"
          curl -X POST "${{ secrets.ROLLBACK_WEBHOOK }}" \
            -H "Authorization: Bearer ${{ secrets.ROLLBACK_TOKEN }}"
```

## Best Practices Implementate

### 1. Conventional Commits
- Formato standardizzato dei commit
- Categorizzazione automatica delle modifiche
- Generazione automatica del changelog

### 2. Semantic Versioning
- Versioning automatico basato sui commit
- Rispetto delle regole SemVer
- Compatibilità con npm e package managers

### 3. Quality Gates
- Test automatizzati obbligatori
- Code coverage monitoring
- Security scanning
- Performance testing

### 4. Zero-Downtime Deployment
- Health checks post-deployment
- Rollback automatico in caso di errori
- Monitoraggio continuo
- Notifiche team

## Vantaggi del Sistema

1. **Consistenza**: Processo di release standardizzato
2. **Velocità**: Release automatiche senza intervento manuale
3. **Affidabilità**: Quality gates e rollback automatico
4. **Tracciabilità**: Changelog e release notes dettagliate
5. **Collaborazione**: Team sempre informato sulle release

Questo esempio dimostra come implementare un sistema di release completamente automatizzato che scala dalle piccole applicazioni ai progetti enterprise.
