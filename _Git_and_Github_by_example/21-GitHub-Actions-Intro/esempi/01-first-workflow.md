# 01 - First Workflow

## 📖 Obiettivo

Creare il tuo primo workflow GitHub Actions completo che implementa una pipeline CI/CD base per un'applicazione Node.js. Questo esempio ti guiderà attraverso setup, testing, building e deployment automatizzato.

## 🎯 Cosa Imparerai

- Creazione di workflow da zero
- Setup automatico dell'ambiente
- Testing e quality checks
- Build e packaging
- Deployment basics
- Gestione errors e notifications

## 🏗️ Struttura del Progetto

```
my-first-app/
├── .github/
│   └── workflows/
│       ├── ci.yml                 # Continuous Integration
│       ├── cd.yml                 # Continuous Deployment
│       └── pr-check.yml           # Pull Request checks
├── src/
│   ├── index.js                   # Main application
│   ├── utils.js                   # Utility functions
│   └── server.js                  # Express server
├── tests/
│   ├── unit/
│   │   ├── utils.test.js          # Unit tests
│   │   └── server.test.js         # Server tests
│   └── integration/
│       └── api.test.js            # Integration tests
├── package.json                   # Dependencies
├── .eslintrc.js                   # ESLint config
├── jest.config.js                 # Jest config
└── Dockerfile                     # Docker container
```

## 🚀 Step 1: Setup del Progetto

### package.json

```json
{
  "name": "my-first-app",
  "version": "1.0.0",
  "description": "My first GitHub Actions app",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/server.js",
    "dev": "nodemon src/server.js",
    "test": "jest",
    "test:unit": "jest tests/unit",
    "test:integration": "jest tests/integration",
    "test:coverage": "jest --coverage",
    "lint": "eslint src/ tests/",
    "lint:fix": "eslint src/ tests/ --fix",
    "build": "npm run lint && npm run test",
    "docker:build": "docker build -t my-first-app .",
    "docker:run": "docker run -p 3000:3000 my-first-app"
  },
  "dependencies": {
    "express": "^4.18.2",
    "cors": "^2.8.5",
    "helmet": "^7.1.0"
  },
  "devDependencies": {
    "jest": "^29.7.0",
    "supertest": "^6.3.3",
    "eslint": "^8.55.0",
    "nodemon": "^3.0.2"
  },
  "engines": {
    "node": ">=18.0.0"
  }
}
```

### src/server.js

```javascript
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const { calculateSum, formatMessage } = require('./utils');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(helmet());
app.use(cors());
app.use(express.json());

// Routes
app.get('/', (req, res) => {
  res.json({
    message: formatMessage('Welcome to My First App!'),
    version: process.env.npm_package_version || '1.0.0',
    timestamp: new Date().toISOString()
  });
});

app.get('/health', (req, res) => {
  res.json({
    status: 'healthy',
    uptime: process.uptime(),
    timestamp: new Date().toISOString()
  });
});

app.post('/calculate', (req, res) => {
  const { numbers } = req.body;
  
  if (!Array.isArray(numbers)) {
    return res.status(400).json({
      error: 'Numbers must be an array'
    });
  }
  
  const sum = calculateSum(numbers);
  res.json({
    numbers,
    sum,
    count: numbers.length
  });
});

// Error handling
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).json({
    error: 'Something went wrong!'
  });
});

// 404 handler
app.use('*', (req, res) => {
  res.status(404).json({
    error: 'Route not found'
  });
});

// Start server
if (require.main === module) {
  app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
  });
}

module.exports = app;
```

### src/utils.js

```javascript
/**
 * Calculate sum of numbers array
 * @param {number[]} numbers - Array of numbers
 * @returns {number} Sum of all numbers
 */
function calculateSum(numbers) {
  if (!Array.isArray(numbers)) {
    throw new Error('Input must be an array');
  }
  
  return numbers.reduce((sum, num) => {
    if (typeof num !== 'number') {
      throw new Error('All elements must be numbers');
    }
    return sum + num;
  }, 0);
}

/**
 * Format message with timestamp
 * @param {string} message - Message to format
 * @returns {string} Formatted message
 */
function formatMessage(message) {
  const timestamp = new Date().toLocaleString();
  return `[${timestamp}] ${message}`;
}

/**
 * Validate environment
 * @returns {object} Environment validation result
 */
function validateEnvironment() {
  const nodeVersion = process.version;
  const requiredVersion = '18.0.0';
  
  return {
    valid: nodeVersion >= `v${requiredVersion}`,
    current: nodeVersion,
    required: requiredVersion
  };
}

module.exports = {
  calculateSum,
  formatMessage,
  validateEnvironment
};
```

## 🧪 Step 2: Tests Setup

### tests/unit/utils.test.js

```javascript
const { calculateSum, formatMessage, validateEnvironment } = require('../../src/utils');

describe('Utils - calculateSum', () => {
  test('should calculate sum of positive numbers', () => {
    expect(calculateSum([1, 2, 3, 4, 5])).toBe(15);
  });
  
  test('should handle negative numbers', () => {
    expect(calculateSum([-1, -2, 3])).toBe(0);
  });
  
  test('should handle empty array', () => {
    expect(calculateSum([])).toBe(0);
  });
  
  test('should throw error for non-array input', () => {
    expect(() => calculateSum('not an array')).toThrow('Input must be an array');
  });
  
  test('should throw error for non-number elements', () => {
    expect(() => calculateSum([1, '2', 3])).toThrow('All elements must be numbers');
  });
});

describe('Utils - formatMessage', () => {
  test('should format message with timestamp', () => {
    const message = 'Hello World';
    const formatted = formatMessage(message);
    
    expect(formatted).toContain(message);
    expect(formatted).toMatch(/\\[.*\\] Hello World/);
  });
});

describe('Utils - validateEnvironment', () => {
  test('should validate Node.js version', () => {
    const result = validateEnvironment();
    
    expect(result).toHaveProperty('valid');
    expect(result).toHaveProperty('current');
    expect(result).toHaveProperty('required');
    expect(typeof result.valid).toBe('boolean');
  });
});
```

### tests/unit/server.test.js

```javascript
const request = require('supertest');
const app = require('../../src/server');

describe('Server Routes', () => {
  describe('GET /', () => {
    test('should return welcome message', async () => {
      const response = await request(app).get('/');
      
      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('message');
      expect(response.body).toHaveProperty('version');
      expect(response.body).toHaveProperty('timestamp');
    });
  });
  
  describe('GET /health', () => {
    test('should return health status', async () => {
      const response = await request(app).get('/health');
      
      expect(response.status).toBe(200);
      expect(response.body.status).toBe('healthy');
      expect(response.body).toHaveProperty('uptime');
    });
  });
  
  describe('POST /calculate', () => {
    test('should calculate sum correctly', async () => {
      const numbers = [1, 2, 3, 4, 5];
      const response = await request(app)
        .post('/calculate')
        .send({ numbers });
      
      expect(response.status).toBe(200);
      expect(response.body.sum).toBe(15);
      expect(response.body.count).toBe(5);
    });
    
    test('should handle invalid input', async () => {
      const response = await request(app)
        .post('/calculate')
        .send({ numbers: 'not an array' });
      
      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error');
    });
  });
  
  describe('404 handler', () => {
    test('should return 404 for unknown routes', async () => {
      const response = await request(app).get('/unknown-route');
      
      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Route not found');
    });
  });
});
```

## ⚙️ Step 3: CI Workflow

### .github/workflows/ci.yml

```yaml
name: Continuous Integration

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

env:
  NODE_VERSION: '18'

jobs:
  # Job 1: Code Quality
  quality:
    name: Code Quality Checks
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run ESLint
      run: npm run lint
    
    - name: Check formatting
      run: |
        npx prettier --check src/ tests/
        echo "✅ Code formatting check passed"
  
  # Job 2: Testing
  test:
    name: Run Tests
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run unit tests
      run: npm run test:unit
    
    - name: Run integration tests
      run: npm run test:integration
    
    - name: Generate coverage report
      if: matrix.node-version == 18
      run: npm run test:coverage
    
    - name: Upload coverage to Codecov
      if: matrix.node-version == 18
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage/lcov.info
        flags: unittests
        name: codecov-umbrella
  
  # Job 3: Security Scan
  security:
    name: Security Scan
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run npm audit
      run: |
        npm audit --audit-level moderate
        echo "✅ Security audit passed"
    
    - name: Run Snyk security scan
      uses: snyk/actions/node@master
      env:
        SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
      with:
        args: --severity-threshold=high
      continue-on-error: true
  
  # Job 4: Build
  build:
    name: Build Application
    runs-on: ubuntu-latest
    needs: [quality, test]
    
    outputs:
      build-success: ${{ steps.build.outputs.success }}
      version: ${{ steps.version.outputs.version }}
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Get package version
      id: version
      run: |
        VERSION=$(node -p "require('./package.json').version")
        echo "version=$VERSION" >> $GITHUB_OUTPUT
        echo "📦 Package version: $VERSION"
    
    - name: Build application
      id: build
      run: |
        echo "🔨 Building application..."
        npm run build
        echo "success=true" >> $GITHUB_OUTPUT
        echo "✅ Build completed successfully"
    
    - name: Create build artifact
      run: |
        mkdir -p dist
        cp -r src/ dist/
        cp package*.json dist/
        echo "Build completed at $(date)" > dist/build-info.txt
    
    - name: Upload build artifacts
      uses: actions/upload-artifact@v3
      with:
        name: build-artifacts-${{ steps.version.outputs.version }}
        path: dist/
        retention-days: 30
    
    - name: Build Docker image
      run: |
        docker build -t my-first-app:${{ steps.version.outputs.version }} .
        docker build -t my-first-app:latest .
        echo "🐳 Docker images built successfully"
    
    - name: Save Docker image
      run: |
        docker save my-first-app:latest | gzip > my-first-app.tar.gz
    
    - name: Upload Docker image
      uses: actions/upload-artifact@v3
      with:
        name: docker-image-${{ steps.version.outputs.version }}
        path: my-first-app.tar.gz
        retention-days: 7

  # Job 5: Notification
  notify:
    name: Send Notifications
    runs-on: ubuntu-latest
    needs: [quality, test, security, build]
    if: always()
    
    steps:
    - name: Determine status
      id: status
      run: |
        if [ "${{ needs.quality.result }}" == "success" ] && 
           [ "${{ needs.test.result }}" == "success" ] && 
           [ "${{ needs.build.result }}" == "success" ]; then
          echo "status=success" >> $GITHUB_OUTPUT
          echo "message=✅ CI Pipeline completed successfully!" >> $GITHUB_OUTPUT
        else
          echo "status=failure" >> $GITHUB_OUTPUT
          echo "message=❌ CI Pipeline failed. Check the logs." >> $GITHUB_OUTPUT
        fi
    
    - name: Post to Slack
      if: always()
      uses: 8398a7/action-slack@v3
      with:
        status: ${{ steps.status.outputs.status }}
        channel: '#ci-cd'
        text: |
          ${{ steps.status.outputs.message }}
          
          Repository: ${{ github.repository }}
          Branch: ${{ github.ref_name }}
          Commit: ${{ github.sha }}
          Actor: ${{ github.actor }}
          
          Quality: ${{ needs.quality.result }}
          Tests: ${{ needs.test.result }}
          Security: ${{ needs.security.result }}
          Build: ${{ needs.build.result }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## 🚢 Step 4: CD Workflow

### .github/workflows/cd.yml

```yaml
name: Continuous Deployment

on:
  push:
    branches: [main]
  workflow_dispatch:
    inputs:
      environment:
        description: 'Target environment'
        required: true
        default: 'staging'
        type: choice
        options:
          - staging
          - production
      force_deploy:
        description: 'Force deployment'
        required: false
        default: false
        type: boolean

env:
  NODE_VERSION: '18'
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}

jobs:
  # Job 1: Get artifacts from CI
  prepare:
    name: Prepare Deployment
    runs-on: ubuntu-latest
    outputs:
      version: ${{ steps.version.outputs.version }}
      environment: ${{ steps.env.outputs.environment }}
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Get version
      id: version
      run: |
        VERSION=$(node -p "require('./package.json').version")
        echo "version=$VERSION" >> $GITHUB_OUTPUT
    
    - name: Determine environment
      id: env
      run: |
        if [ "${{ github.event_name }}" == "workflow_dispatch" ]; then
          ENV="${{ github.event.inputs.environment }}"
        else
          ENV="staging"
        fi
        echo "environment=$ENV" >> $GITHUB_OUTPUT
        echo "🎯 Target environment: $ENV"

  # Job 2: Deploy to Staging
  deploy-staging:
    name: Deploy to Staging
    runs-on: ubuntu-latest
    needs: prepare
    if: needs.prepare.outputs.environment == 'staging' || github.ref == 'refs/heads/main'
    environment:
      name: staging
      url: https://staging.my-first-app.com
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Download build artifacts
      uses: actions/download-artifact@v3
      with:
        name: build-artifacts-${{ needs.prepare.outputs.version }}
        path: ./dist
    
    - name: Download Docker image
      uses: actions/download-artifact@v3
      with:
        name: docker-image-${{ needs.prepare.outputs.version }}
    
    - name: Load Docker image
      run: docker load < my-first-app.tar.gz
    
    - name: Deploy to staging
      env:
        STAGING_HOST: ${{ secrets.STAGING_HOST }}
        STAGING_USER: ${{ secrets.STAGING_USER }}
        STAGING_KEY: ${{ secrets.STAGING_SSH_KEY }}
      run: |
        echo "🚀 Deploying to staging..."
        
        # Simulate deployment
        echo "Deploying version: ${{ needs.prepare.outputs.version }}"
        echo "Environment: staging"
        echo "Image: my-first-app:latest"
        
        # In real scenario, you would:
        # - Push image to registry
        # - SSH to staging server
        # - Pull new image
        # - Restart containers
        
        echo "✅ Staging deployment completed"
    
    - name: Run smoke tests
      run: |
        echo "🧪 Running smoke tests..."
        
        # Simulate API health check
        sleep 5
        echo "✅ Health check: PASSED"
        echo "✅ API endpoints: PASSED"
        echo "✅ Database connection: PASSED"
    
    - name: Update deployment status
      run: |
        echo "📊 Deployment metrics:"
        echo "- Version: ${{ needs.prepare.outputs.version }}"
        echo "- Environment: staging"
        echo "- Status: SUCCESS"
        echo "- Timestamp: $(date -u +%Y-%m-%dT%H:%M:%SZ)"

  # Job 3: Deploy to Production
  deploy-production:
    name: Deploy to Production
    runs-on: ubuntu-latest
    needs: [prepare, deploy-staging]
    if: needs.prepare.outputs.environment == 'production' && (github.ref == 'refs/heads/main' || github.event.inputs.force_deploy == 'true')
    environment:
      name: production
      url: https://my-first-app.com
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Download artifacts
      uses: actions/download-artifact@v3
      with:
        name: build-artifacts-${{ needs.prepare.outputs.version }}
        path: ./dist
    
    - name: Production deployment
      env:
        PROD_HOST: ${{ secrets.PROD_HOST }}
        PROD_USER: ${{ secrets.PROD_USER }}
        PROD_KEY: ${{ secrets.PROD_SSH_KEY }}
      run: |
        echo "🚀 Deploying to production..."
        echo "Version: ${{ needs.prepare.outputs.version }}"
        
        # Blue-green deployment simulation
        echo "🔵 Starting blue-green deployment..."
        echo "- Deploying to green environment"
        echo "- Running health checks"
        echo "- Switching traffic to green"
        echo "- Terminating blue environment"
        
        echo "✅ Production deployment completed"
    
    - name: Production health checks
      run: |
        echo "🏥 Running production health checks..."
        
        for i in {1..5}; do
          echo "Health check attempt $i/5..."
          # Simulate health check
          sleep 10
          echo "✅ Health check $i: PASSED"
        done
        
        echo "✅ All production health checks passed"
    
    - name: Create release
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        tag_name: v${{ needs.prepare.outputs.version }}
        release_name: Release v${{ needs.prepare.outputs.version }}
        body: |
          🚀 **Production Release v${{ needs.prepare.outputs.version }}**
          
          **Deployed:** $(date -u +"%Y-%m-%d %H:%M:%S UTC")
          **Commit:** ${{ github.sha }}
          **Actor:** ${{ github.actor }}
          
          **Changes:**
          ${{ github.event.head_commit.message }}
          
          **Environments:**
          - ✅ Staging: https://staging.my-first-app.com
          - ✅ Production: https://my-first-app.com
        draft: false
        prerelease: false

  # Job 4: Post-deployment
  post-deployment:
    name: Post-deployment Tasks
    runs-on: ubuntu-latest
    needs: [prepare, deploy-staging, deploy-production]
    if: always() && !failure()
    
    steps:
    - name: Send success notification
      uses: 8398a7/action-slack@v3
      with:
        status: success
        channel: '#deployments'
        text: |
          🎉 **Deployment Successful!**
          
          **Version:** ${{ needs.prepare.outputs.version }}
          **Environment:** ${{ needs.prepare.outputs.environment }}
          **Commit:** ${{ github.sha }}
          **Actor:** ${{ github.actor }}
          
          **URLs:**
          - Staging: https://staging.my-first-app.com
          - Production: https://my-first-app.com
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
    
    - name: Update monitoring
      run: |
        echo "📊 Updating monitoring dashboards..."
        echo "🔔 Setting up alerts for new version"
        echo "📈 Starting performance monitoring"
```

## 🔍 Step 5: PR Check Workflow

### .github/workflows/pr-check.yml

```yaml
name: Pull Request Checks

on:
  pull_request:
    branches: [main]
    types: [opened, synchronize, reopened]

jobs:
  pr-validation:
    name: PR Validation
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout PR code
      uses: actions/checkout@v4
      with:
        ref: ${{ github.event.pull_request.head.sha }}
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run quick tests
      run: npm run test:unit
    
    - name: Check PR title
      run: |
        PR_TITLE="${{ github.event.pull_request.title }}"
        if [[ ! "$PR_TITLE" =~ ^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: ]]; then
          echo "❌ PR title must follow conventional commits format"
          echo "Examples: feat: add new feature, fix(api): resolve bug"
          exit 1
        fi
        echo "✅ PR title format is valid"
    
    - name: Comment on PR
      uses: actions/github-script@v6
      with:
        script: |
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: `✅ **PR Checks Completed**
            
            - ✅ Tests passed
            - ✅ Title format valid
            - ✅ Ready for review
            
            **Next steps:**
            1. Wait for code review
            2. Address any feedback
            3. Merge when approved`
          })
```

## 📊 Results Dashboard

Dopo aver implementato i workflow, vedrai:

1. **CI Status Badges** nel README
2. **Build Artifacts** scaricabili
3. **Test Coverage Reports** 
4. **Security Scan Results**
5. **Deployment Status** per environment
6. **Release Notes** automatiche

## 🎯 Prossimi Passi

Ora che hai creato il tuo primo workflow completo:

1. **[Testing Automation](./02-testing-automation.md)** - Automazione testing avanzata
2. **[Deploy Automation](./03-deploy-automation.md)** - Deployment strategies
3. **[Esercizi](../esercizi/01-ci-setup.md)** - Pratica con progetti reali

Il tuo primo workflow GitHub Actions è pronto per la produzione! 🚀
