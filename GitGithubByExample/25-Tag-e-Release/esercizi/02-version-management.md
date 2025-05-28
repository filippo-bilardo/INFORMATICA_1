# 02 - Esercizio: Gestione Avanzata delle Versioni

Questo esercizio avanzato copre tecniche sofisticate di version management, inclusi pre-releases, hotfix, backporting e gestione di multiple release lines.

## 🎯 Obiettivi

- Gestire versioni complesse con pre-release
- Implementare hotfix e backporting
- Mantenere multiple release lines
- Automatizzare version bumping con conventional commits
- Gestire deprecazioni e breaking changes

## 📋 Prerequisiti

- Completamento dell'esercizio 01
- Conoscenza di Semantic Versioning
- Git avanzato (branching, tagging)
- GitHub Actions (base)

## 🚀 Scenario

Gestisci le versioni di una REST API che deve supportare:
- Multiple versioni in produzione (v1, v2)
- Pre-release per testing (alpha, beta, rc)
- Hotfix per versioni legacy
- Breaking changes tra major versions

## Parte 1: Setup Multi-Version Project

### 1.1 Struttura Repository

```bash
# Crea nuovo progetto API
mkdir advanced-api-versioning
cd advanced-api-versioning

git init
git branch -M main

# Struttura delle directory
mkdir -p {src/v1,src/v2,tests/v1,tests/v2,docs/v1,docs/v2}
```

### 1.2 Base API Setup

**`package.json`**:
```json
{
  "name": "advanced-api",
  "version": "1.0.0",
  "description": "Advanced API with sophisticated version management",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "dev": "nodemon src/app.js",
    "test": "jest",
    "test:v1": "jest tests/v1",
    "test:v2": "jest tests/v2",
    "lint": "eslint src/",
    "version:major": "npm version major --no-git-tag-version",
    "version:minor": "npm version minor --no-git-tag-version",
    "version:patch": "npm version patch --no-git-tag-version",
    "version:prerelease": "npm version prerelease --no-git-tag-version",
    "release:alpha": "npm run version:prerelease -- --preid=alpha",
    "release:beta": "npm run version:prerelease -- --preid=beta",
    "release:rc": "npm run version:prerelease -- --preid=rc"
  },
  "dependencies": {
    "express": "^4.18.0",
    "cors": "^2.8.5"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "supertest": "^6.0.0",
    "nodemon": "^2.0.0",
    "eslint": "^8.0.0"
  }
}
```

### 1.3 API v1 Implementation

**`src/v1/routes.js`**:
```javascript
const express = require('express');
const router = express.Router();

// Users endpoint v1
router.get('/users', (req, res) => {
  res.json({
    version: '1.0',
    users: [
      { id: 1, name: 'John Doe', email: 'john@example.com' },
      { id: 2, name: 'Jane Smith', email: 'jane@example.com' }
    ]
  });
});

router.get('/users/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const user = { id, name: `User ${id}`, email: `user${id}@example.com` };
  res.json({ version: '1.0', user });
});

// Posts endpoint v1 (simple structure)
router.get('/posts', (req, res) => {
  res.json({
    version: '1.0',
    posts: [
      { id: 1, title: 'First Post', content: 'Content 1', author: 'John' },
      { id: 2, title: 'Second Post', content: 'Content 2', author: 'Jane' }
    ]
  });
});

module.exports = router;
```

**`src/v2/routes.js`**:
```javascript
const express = require('express');
const router = express.Router();

// Users endpoint v2 (enhanced with pagination)
router.get('/users', (req, res) => {
  const page = parseInt(req.query.page) || 1;
  const limit = parseInt(req.query.limit) || 10;
  
  res.json({
    version: '2.0',
    data: {
      users: [
        { 
          id: 1, 
          name: 'John Doe', 
          email: 'john@example.com',
          profile: { avatar: 'avatar1.jpg', bio: 'Developer' }
        },
        { 
          id: 2, 
          name: 'Jane Smith', 
          email: 'jane@example.com',
          profile: { avatar: 'avatar2.jpg', bio: 'Designer' }
        }
      ]
    },
    pagination: {
      page,
      limit,
      total: 100,
      pages: Math.ceil(100 / limit)
    }
  });
});

// Posts endpoint v2 (enhanced structure with metadata)
router.get('/posts', (req, res) => {
  res.json({
    version: '2.0',
    data: {
      posts: [
        { 
          id: 1, 
          title: 'First Post', 
          content: 'Enhanced content 1',
          author: { id: 1, name: 'John Doe' },
          metadata: { created: '2025-01-01', updated: '2025-01-01', views: 42 }
        },
        { 
          id: 2, 
          title: 'Second Post', 
          content: 'Enhanced content 2',
          author: { id: 2, name: 'Jane Smith' },
          metadata: { created: '2025-01-02', updated: '2025-01-02', views: 38 }
        }
      ]
    }
  });
});

module.exports = router;
```

**`src/app.js`**:
```javascript
const express = require('express');
const cors = require('cors');
const v1Routes = require('./v1/routes');
const v2Routes = require('./v2/routes');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(cors());
app.use(express.json());

// Health check
app.get('/health', (req, res) => {
  res.json({ 
    status: 'ok', 
    version: process.env.npm_package_version,
    timestamp: new Date().toISOString()
  });
});

// API versioning
app.use('/api/v1', v1Routes);
app.use('/api/v2', v2Routes);

// Default route
app.get('/', (req, res) => {
  res.json({
    message: 'Advanced API with Version Management',
    versions: ['v1', 'v2'],
    endpoints: {
      v1: '/api/v1',
      v2: '/api/v2'
    }
  });
});

// 404 handler
app.use('*', (req, res) => {
  res.status(404).json({ error: 'Endpoint not found' });
});

if (require.main === module) {
  app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
  });
}

module.exports = app;
```

### 1.4 Test Setup

**`tests/v1/api.test.js`**:
```javascript
const request = require('supertest');
const app = require('../../src/app');

describe('API v1', () => {
  describe('GET /api/v1/users', () => {
    test('should return users list', async () => {
      const response = await request(app).get('/api/v1/users');
      expect(response.status).toBe(200);
      expect(response.body.version).toBe('1.0');
      expect(response.body.users).toHaveLength(2);
    });
  });

  describe('GET /api/v1/posts', () => {
    test('should return posts list', async () => {
      const response = await request(app).get('/api/v1/posts');
      expect(response.status).toBe(200);
      expect(response.body.version).toBe('1.0');
      expect(response.body.posts).toHaveLength(2);
    });
  });
});
```

**`tests/v2/api.test.js`**:
```javascript
const request = require('supertest');
const app = require('../../src/app');

describe('API v2', () => {
  describe('GET /api/v2/users', () => {
    test('should return paginated users', async () => {
      const response = await request(app).get('/api/v2/users?page=1&limit=5');
      expect(response.status).toBe(200);
      expect(response.body.version).toBe('2.0');
      expect(response.body.data.users).toHaveLength(2);
      expect(response.body.pagination).toHaveProperty('page', 1);
      expect(response.body.pagination).toHaveProperty('limit', 5);
    });
  });

  describe('GET /api/v2/posts', () => {
    test('should return enhanced posts', async () => {
      const response = await request(app).get('/api/v2/posts');
      expect(response.status).toBe(200);
      expect(response.body.version).toBe('2.0');
      expect(response.body.data.posts[0]).toHaveProperty('metadata');
      expect(response.body.data.posts[0].author).toHaveProperty('id');
    });
  });
});
```

### 1.5 Initial Commit

```bash
# Aggiungi e committa
git add .
git commit -m "feat: initial API implementation with v1 and v2

- Add Express.js REST API with versioning
- Implement v1 endpoints (users, posts)
- Implement v2 endpoints with enhanced features
- Add pagination support in v2
- Add comprehensive test suite for both versions
- Add health check endpoint"

# Push su GitHub
git remote add origin https://github.com/TUO-USERNAME/advanced-api-versioning.git
git push -u origin main
```

## Parte 2: Pre-Release Management

### 2.1 Alpha Release (v1.1.0-alpha.1)

```bash
# Crea branch per feature sperimentale
git checkout -b feature/experimental-search

# Aggiungi feature sperimentale a v2
```

**`src/v2/routes.js` - Aggiungi endpoint search**:
```javascript
// Search endpoint (experimental)
router.get('/search', (req, res) => {
  const query = req.query.q;
  const type = req.query.type || 'all'; // users, posts, all
  
  // Simulazione ricerca
  const results = {
    users: [
      { id: 1, name: 'John Doe', email: 'john@example.com', relevance: 0.9 }
    ],
    posts: [
      { id: 1, title: 'First Post', excerpt: 'Content preview...', relevance: 0.8 }
    ]
  };
  
  res.json({
    version: '2.1.0-alpha',
    experimental: true,
    query,
    type,
    results: type === 'all' ? results : { [type]: results[type] || [] }
  });
});
```

```bash
# Test della feature
npm test

# Commit della feature
git add .
git commit -m "feat: add experimental search endpoint to v2

- Add /search endpoint with query and type parameters
- Support searching users and posts
- Include relevance scoring
- Mark as experimental feature

BREAKING CHANGE: This is an alpha feature and API may change"

# Push branch
git push origin feature/experimental-search

# Merge in main (via PR)
git checkout main
git merge feature/experimental-search
```

### 2.2 Create Alpha Release

```bash
# Bump to alpha version
npm run release:alpha

# Aggiorna changelog
```

**`CHANGELOG.md`**:
```markdown
# Changelog

## [1.1.0-alpha.1] - 2025-01-XX

### Added
- 🧪 **[EXPERIMENTAL]** Search endpoint in API v2
- Query support for users and posts
- Relevance scoring system

### ⚠️ Breaking Changes
- This is an alpha release with experimental features
- Search API may change significantly before stable release
- Not recommended for production use

### Notes
- Alpha features are subject to change
- Feedback welcome on experimental features
- Next: Beta release with stabilized search API

## [1.0.0] - 2025-01-XX

### Added
- Initial API implementation
- v1 endpoints (users, posts)
- v2 enhanced endpoints with pagination
- Comprehensive test suite
```

```bash
# Commit delle modifiche
git add .
git commit -m "chore(release): v1.1.0-alpha.1

- Add experimental search functionality
- Update changelog with alpha release notes
- Mark search API as experimental"

# Crea tag alpha
git tag -a v1.1.0-alpha.1 -m "Release v1.1.0-alpha.1

🧪 ALPHA RELEASE - EXPERIMENTAL FEATURES

This alpha release introduces experimental search functionality:
- Search endpoint for users and posts
- Relevance scoring
- Query filtering by type

⚠️  WARNING: This is an alpha release
- API may change without notice
- Not suitable for production
- Breaking changes expected before stable release

For testing and feedback only."

# Push
git push origin main v1.1.0-alpha.1
```

### 2.3 Beta Release (v1.1.0-beta.1)

```bash
# Migliora la feature basandoti sul feedback
git checkout -b improve/search-api

# Stabilizza l'API di ricerca
```

**Migliora `src/v2/routes.js`**:
```javascript
// Improved search endpoint
router.get('/search', (req, res) => {
  const query = req.query.q;
  const type = req.query.type || 'all';
  const page = parseInt(req.query.page) || 1;
  const limit = parseInt(req.query.limit) || 10;
  
  if (!query) {
    return res.status(400).json({
      error: 'Query parameter q is required'
    });
  }
  
  // Simulazione ricerca migliorata
  const allResults = {
    users: [
      { id: 1, name: 'John Doe', email: 'john@example.com', relevance: 0.95 },
      { id: 3, name: 'John Smith', email: 'jsmith@example.com', relevance: 0.85 }
    ],
    posts: [
      { id: 1, title: 'First Post', excerpt: 'Content preview...', relevance: 0.9 },
      { id: 3, title: 'Post about John', excerpt: 'Another preview...', relevance: 0.7 }
    ]
  };
  
  // Filtra per tipo
  const results = type === 'all' ? allResults : { [type]: allResults[type] || [] };
  
  res.json({
    version: '2.1.0-beta',
    beta: true,
    query,
    type,
    results,
    pagination: {
      page,
      limit,
      total: Object.values(results).reduce((sum, arr) => sum + arr.length, 0)
    },
    meta: {
      search_time: '12ms',
      total_results: Object.values(allResults).reduce((sum, arr) => sum + arr.length, 0)
    }
  });
});
```

```bash
# Test migliorati
git add .
git commit -m "feat: stabilize search API for beta release

- Add input validation for search query
- Improve search results with better relevance
- Add pagination support to search
- Add search metadata (timing, totals)
- Remove experimental warnings"

git push origin improve/search-api
git checkout main
git merge improve/search-api
```

### 2.4 Create Beta Release

```bash
# Bump to beta
npm run release:beta

# Aggiorna changelog
```

**Aggiorna `CHANGELOG.md`**:
```markdown
## [1.1.0-beta.1] - 2025-01-XX

### Improved
- 🔄 **[BETA]** Stabilized search API
- Added input validation for search queries
- Enhanced search results with better relevance scoring
- Added pagination support to search endpoint
- Added search performance metadata

### Fixed
- Search endpoint now properly validates required parameters
- Improved error handling for invalid search queries

### Notes
- API is stabilizing, minimal changes expected before release
- Feedback still welcome but breaking changes unlikely
- Next: Release candidate with final API

## [1.1.0-alpha.1] - 2025-01-XX
...
```

```bash
# Beta release
git add .
git commit -m "chore(release): v1.1.0-beta.1

- Stabilize search API for beta testing
- Add improved validation and error handling
- Update changelog with beta release notes"

git tag -a v1.1.0-beta.1 -m "Release v1.1.0-beta.1

🔄 BETA RELEASE - API STABILIZING

This beta release stabilizes the search functionality:
- Input validation and error handling
- Improved search relevance
- Pagination support
- Performance metadata

✅ Suitable for staging environments
⚠️  Still not recommended for production
🔜 Release candidate coming soon"

git push origin main v1.1.0-beta.1
```

## Parte 3: Hotfix Management

### 3.1 Simula Bug Critico in Produzione

```bash
# Simula che v1.0.0 sia in produzione e ha un bug critico
git checkout -b hotfix/security-fix-v1.0.x v1.0.0

# Simula un fix di sicurezza nel v1
```

**Aggiungi validazione sicurezza in `src/v1/routes.js`**:
```javascript
// Aggiungi all'inizio del file
const validateInput = (req, res, next) => {
  // Previeni SQL injection di base
  const dangerousChars = /[<>'"%;()&+]/;
  
  for (const [key, value] of Object.entries(req.query)) {
    if (typeof value === 'string' && dangerousChars.test(value)) {
      return res.status(400).json({
        error: 'Invalid characters in query parameters',
        code: 'SECURITY_VALIDATION_FAILED'
      });
    }
  }
  next();
};

// Applica middleware a tutte le route
router.use(validateInput);

// Aggiungi anche rate limiting simulato
const rateLimitMap = new Map();

const rateLimit = (req, res, next) => {
  const ip = req.ip || req.connection.remoteAddress;
  const now = Date.now();
  const windowMs = 60000; // 1 minuto
  const maxRequests = 100;
  
  if (!rateLimitMap.has(ip)) {
    rateLimitMap.set(ip, { count: 1, resetTime: now + windowMs });
    return next();
  }
  
  const userData = rateLimitMap.get(ip);
  if (now > userData.resetTime) {
    userData.count = 1;
    userData.resetTime = now + windowMs;
    return next();
  }
  
  if (userData.count >= maxRequests) {
    return res.status(429).json({
      error: 'Too many requests',
      retryAfter: Math.ceil((userData.resetTime - now) / 1000)
    });
  }
  
  userData.count++;
  next();
};

router.use(rateLimit);
```

```bash
# Test del fix
npm run test:v1

# Commit hotfix
git add .
git commit -m "fix: add security validation and rate limiting

SECURITY FIX: Critical security vulnerability patched

- Add input validation to prevent injection attacks
- Add rate limiting to prevent abuse
- Validate query parameters for dangerous characters
- Return appropriate error codes for security violations

This fixes CVE-2025-XXXX reported by security team.

Affects: v1.0.0
Severity: High
Impact: All v1 endpoints vulnerable to injection"
```

### 3.2 Hotfix Release

```bash
# Bump patch version per hotfix
npm version patch --no-git-tag-version

# Update version in package.json to 1.0.1
```

**Aggiorna `CHANGELOG.md`**:
```markdown
## [1.0.1] - 2025-01-XX - SECURITY RELEASE

### Security
- 🔒 **CRITICAL** Fixed injection vulnerability in v1 API endpoints
- Added input validation for all query parameters
- Implemented rate limiting to prevent abuse
- Added security error codes and messaging

### Details
- **CVE**: CVE-2025-XXXX
- **Severity**: High
- **Impact**: All v1 endpoints
- **Affected Versions**: v1.0.0
- **Fixed in**: v1.0.1

### Upgrade Required
- All users of v1.0.0 should upgrade immediately
- No breaking changes in this security patch
- Backward compatible with existing client code
```

```bash
# Commit hotfix release
git add .
git commit -m "chore(release): v1.0.1 - SECURITY RELEASE

Critical security patch for injection vulnerability
- Fix CVE-2025-XXXX in v1 API endpoints  
- Add input validation and rate limiting
- Update changelog with security details

All v1.0.0 users should upgrade immediately."

# Tag hotfix
git tag -a v1.0.1 -m "SECURITY RELEASE v1.0.1

🔒 CRITICAL SECURITY PATCH

This release fixes a critical security vulnerability:
- CVE-2025-XXXX: Injection vulnerability in v1 endpoints
- Added input validation and rate limiting
- No breaking changes

⚠️  IMMEDIATE UPGRADE REQUIRED
All users of v1.0.0 must upgrade to v1.0.1

Vulnerability Details:
- Severity: High
- Impact: Data injection possible
- Fixed: Input validation added
- Mitigation: Rate limiting implemented"

# Push hotfix
git push origin hotfix/security-fix-v1.0.x v1.0.1
```

### 3.3 Backport Security Fix

```bash
# Backport il fix anche alla main branch
git checkout main

# Cherry-pick il security fix
git cherry-pick v1.0.1

# Risolvi eventuali conflitti e aggiorna per v2
```

**Applica il fix anche a `src/v2/routes.js`**:
```javascript
// Stessi middleware di sicurezza
const validateInput = (req, res, next) => {
  const dangerousChars = /[<>'"%;()&+]/;
  
  for (const [key, value] of Object.entries(req.query)) {
    if (typeof value === 'string' && dangerousChars.test(value)) {
      return res.status(400).json({
        error: 'Invalid characters in query parameters',
        code: 'SECURITY_VALIDATION_FAILED',
        version: '2.1.0-beta'
      });
    }
  }
  next();
};

router.use(validateInput);
```

```bash
# Commit backport
git add .
git commit -m "fix: backport security fixes to v2 API

Backport security validation from v1.0.1 hotfix:
- Add input validation middleware to v2 endpoints
- Apply same security measures across all API versions
- Maintain consistency in security posture

Related: v1.0.1 security release"

git push origin main
```

## Parte 4: Release Candidate e Stable

### 4.1 Release Candidate

```bash
# Prepara RC dalla beta
npm version prerelease --preid=rc --no-git-tag-version

# Final testing e documentation
```

**Aggiorna `docs/API.md`**:
```markdown
# API Documentation v2.1.0

## Search Endpoint

### GET /api/v2/search

Search across users and posts with relevance ranking.

#### Parameters

- `q` (required): Search query string
- `type` (optional): Filter by 'users', 'posts', or 'all' (default)
- `page` (optional): Page number for pagination (default: 1)
- `limit` (optional): Items per page (default: 10)

#### Example Request

```bash
GET /api/v2/search?q=john&type=users&page=1&limit=5
```

#### Example Response

```json
{
  "version": "2.1.0",
  "query": "john",
  "type": "users",
  "results": {
    "users": [
      {
        "id": 1,
        "name": "John Doe",
        "email": "john@example.com",
        "relevance": 0.95
      }
    ]
  },
  "pagination": {
    "page": 1,
    "limit": 5,
    "total": 1
  },
  "meta": {
    "search_time": "12ms",
    "total_results": 1
  }
}
```

#### Error Responses

- `400 Bad Request`: Missing or invalid query parameter
- `429 Too Many Requests`: Rate limit exceeded
```

```bash
# RC release
git add .
git commit -m "chore(release): v1.1.0-rc.1

Release candidate for v1.1.0:
- Finalize search API documentation
- Complete testing of all features
- Security fixes applied across all versions
- Ready for production evaluation"

git tag -a v1.1.0-rc.1 -m "Release Candidate v1.1.0-rc.1

🚀 RELEASE CANDIDATE - PRODUCTION READY

Final testing phase for v1.1.0:
- Search API fully documented and tested
- Security patches applied
- All tests passing
- Documentation complete

✅ Suitable for production evaluation
🔜 Stable release pending final validation"

git push origin main v1.1.0-rc.1
```

### 4.2 Stable Release

```bash
# Final stable release
npm version minor --no-git-tag-version

# Update per stable version
```

**`CHANGELOG.md` finale**:
```markdown
## [1.1.0] - 2025-01-XX

### Added
- 🔍 **NEW** Search functionality in API v2
- Search across users and posts with relevance ranking
- Pagination support for search results
- Performance metadata for search operations
- Comprehensive input validation

### Security
- Enhanced security validation across all API versions
- Rate limiting to prevent abuse
- Input sanitization for injection prevention

### Documentation
- Complete API documentation for search endpoints
- Usage examples and error handling guide
- Migration guide for new features

### Performance
- Optimized search relevance algorithm
- Improved response times for paginated results
- Enhanced error handling and validation

## [1.0.1] - 2025-01-XX - SECURITY RELEASE
...
```

```bash
# Stable release
git add .
git commit -m "chore(release): v1.1.0

Stable release with search functionality:
- Search API fully tested and documented
- Security enhancements across all versions
- Complete feature set ready for production
- Breaking changes properly documented"

git tag -a v1.1.0 -m "Release v1.1.0

🎉 STABLE RELEASE

Major new features:
- Search functionality in API v2
- Enhanced security across all versions
- Comprehensive documentation
- Full backward compatibility

✅ Production ready
📖 See CHANGELOG.md for full details
🔄 Upgrade path from v1.0.x available"

git push origin main v1.1.0
```

## Parte 5: Automation Avanzata

### 5.1 Conventional Commits Automation

**`.github/workflows/semantic-release.yml`**:
```yaml
name: Semantic Release

on:
  push:
    branches: [main]

jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          token: ${{ secrets.RELEASE_TOKEN }}
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run tests
        run: npm test
      
      - name: Semantic Release
        uses: cycjimmy/semantic-release-action@v4
        env:
          GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
        with:
          semantic_version: 21
          extra_plugins: |
            @semantic-release/changelog
            @semantic-release/git
            conventional-changelog-conventionalcommits
```

**`release.config.js`**:
```javascript
module.exports = {
  branches: [
    'main',
    { name: 'beta', prerelease: true },
    { name: 'alpha', prerelease: true }
  ],
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
          { breaking: true, release: 'major' },
          // Custom rules for pre-releases
          { type: 'feat', scope: 'experimental', release: 'prerelease' }
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
            { type: 'docs', section: '📚 Documentation' },
            { type: 'style', section: '💎 Styles' },
            { type: 'refactor', section: '♻️ Refactoring' },
            { type: 'test', section: '🧪 Tests' },
            { type: 'build', section: '🏗️ Build' },
            { type: 'ci', section: '⚙️ CI/CD' },
            { type: 'chore', section: '🔧 Chores' }
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
          { path: 'dist/**', label: 'Distribution files' },
          { path: 'docs/**', label: 'Documentation' }
        ]
      }
    ],
    [
      '@semantic-release/git',
      {
        assets: ['CHANGELOG.md', 'package.json', 'package-lock.json'],
        message: 'chore(release): ${nextRelease.version} [skip ci]\n\n${nextRelease.notes}'
      }
    ]
  ]
};
```

### 5.2 Multi-Version Support Workflow

**`.github/workflows/multi-version.yml`**:
```yaml
name: Multi-Version Release

on:
  workflow_dispatch:
    inputs:
      version_line:
        description: 'Version line to release (1.0.x, 1.1.x, 2.0.x)'
        required: true
        type: choice
        options:
          - '1.0.x'
          - '1.1.x'
          - '2.0.x'
      release_type:
        description: 'Type of release'
        required: true
        type: choice
        options:
          - patch
          - minor
          - major
          - prerelease

jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
      
      - name: Determine target branch
        id: target
        run: |
          case "${{ github.event.inputs.version_line }}" in
            "1.0.x") echo "branch=release/1.0.x" >> $GITHUB_OUTPUT ;;
            "1.1.x") echo "branch=release/1.1.x" >> $GITHUB_OUTPUT ;;
            "2.0.x") echo "branch=main" >> $GITHUB_OUTPUT ;;
          esac
      
      - name: Checkout target branch
        run: git checkout ${{ steps.target.outputs.branch }}
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run tests
        run: npm test
      
      - name: Bump version
        run: npm version ${{ github.event.inputs.release_type }} --no-git-tag-version
      
      - name: Create release
        run: |
          VERSION=$(node -p "require('./package.json').version")
          git add package.json
          git commit -m "chore(release): v$VERSION"
          git tag -a "v$VERSION" -m "Release v$VERSION for ${{ github.event.inputs.version_line }}"
          git push origin ${{ steps.target.outputs.branch }} "v$VERSION"
```

## 📝 Verifica e Riflessione

### ✅ Checklist Completamento Avanzato

- [ ] Pre-release workflow (alpha, beta, rc) implementato
- [ ] Hotfix workflow per versioni legacy testato
- [ ] Backporting di security fix eseguito
- [ ] Multiple release lines gestite
- [ ] Automation con semantic-release configurata
- [ ] Documentazione versioning completa
- [ ] Testing multi-versione implementato

### 🤔 Domande di Riflessione Avanzate

1. **Come gestiresti il supporto di 3+ versioni major contemporaneamente?**
2. **Qual è la strategia ottimale per comunicare breaking changes?**
3. **Come automatizzeresti il backporting selettivo di fix?**
4. **Quale criterio useresti per decidere quando deprecare una versione?**

### 🎯 Scenario di Test

**Situazione**: Hai API v1 (production), v2 (staging), v3 (development). Scopri un bug critico che affligge tutte le versioni.

**Compiti**:
1. Crea hotfix per v1 (production emergency)
2. Backporta fix a v2 mantenendo le nuove feature
3. Integra fix in v3 senza rompere development
4. Coordina release di tutte e tre le versioni
5. Comunica l'incident e le patch ai team

### 📈 Competenze Acquisite

Completando questo esercizio avanzato hai acquisito:

1. **Version Management Strategico**
   - Gestione multi-versione complessa
   - Pre-release lifecycle management
   - Hotfix e emergency response

2. **Process Automation**
   - Semantic versioning automatico
   - Conventional commits enforcement
   - Multi-environment release coordination

3. **Quality Assurance**
   - Security patching cross-version
   - Backward compatibility testing
   - Documentation versioning

4. **Team Coordination**
   - Release communication strategies
   - Stakeholder management
   - Emergency response procedures

Queste competenze sono essenziali per gestire progetti software complessi in ambienti enterprise dove multiple versioni devono coesistere e essere mantenute simultaneamente.
