# 02 - Testing Automation

## 📖 Obiettivo

Implementare una strategia completa di testing automation che copre unit tests, integration tests, E2E tests, performance testing e security testing utilizzando GitHub Actions.

## 🎯 Cosa Imparerai

- Multi-level testing strategy
- Parallel test execution
- Test result reporting
- Coverage analysis
- Performance benchmarking
- Security vulnerability testing
- Cross-platform testing

## 🏗️ Advanced Testing Structure

```
testing-automation/
├── .github/
│   └── workflows/
│       ├── test-comprehensive.yml
│       ├── test-performance.yml
│       ├── test-security.yml
│       └── test-matrix.yml
├── tests/
│   ├── unit/
│   │   ├── components/
│   │   ├── services/
│   │   └── utils/
│   ├── integration/
│   │   ├── api/
│   │   ├── database/
│   │   └── external-services/
│   ├── e2e/
│   │   ├── user-flows/
│   │   ├── smoke/
│   │   └── regression/
│   ├── performance/
│   │   ├── load/
│   │   ├── stress/
│   │   └── benchmarks/
│   └── security/
│       ├── vulnerabilities/
│       ├── penetration/
│       └── compliance/
├── src/
├── docker-compose.test.yml
├── jest.config.js
├── playwright.config.js
└── k6-config.js
```

## 🧪 Comprehensive Testing Workflow

### .github/workflows/test-comprehensive.yml

```yaml
name: Comprehensive Testing Suite

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  schedule:
    - cron: '0 2 * * *'  # Daily at 2 AM

env:
  NODE_VERSION: '18'
  PYTHON_VERSION: '3.11'

jobs:
  # Job 1: Unit Tests
  unit-tests:
    name: Unit Tests
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
        test-suite: [components, services, utils]
    
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
    
    - name: Run unit tests - ${{ matrix.test-suite }}
      run: |
        npm run test:unit -- tests/unit/${{ matrix.test-suite }}
        echo "✅ Unit tests (${{ matrix.test-suite }}) completed"
    
    - name: Generate coverage report
      if: matrix.node-version == '18' && matrix.test-suite == 'components'
      run: |
        npm run test:coverage
        echo "📊 Coverage report generated"
    
    - name: Upload coverage to Codecov
      if: matrix.node-version == '18' && matrix.test-suite == 'components'
      uses: codecov/codecov-action@v3
      with:
        files: ./coverage/lcov.info
        flags: unit-tests
        name: unit-tests-coverage
    
    - name: Upload test results
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: unit-test-results-${{ matrix.node-version }}-${{ matrix.test-suite }}
        path: |
          test-results.xml
          coverage/
        retention-days: 30

  # Job 2: Integration Tests
  integration-tests:
    name: Integration Tests
    runs-on: ubuntu-latest
    
    services:
      postgres:
        image: postgres:13
        env:
          POSTGRES_PASSWORD: postgres
          POSTGRES_DB: testdb
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
        ports:
          - 5432:5432
      
      redis:
        image: redis:6
        options: >-
          --health-cmd "redis-cli ping"
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
        ports:
          - 6379:6379
      
      mongodb:
        image: mongo:5
        env:
          MONGO_INITDB_ROOT_USERNAME: admin
          MONGO_INITDB_ROOT_PASSWORD: password
        ports:
          - 27017:27017
    
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
    
    - name: Setup test databases
      env:
        DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb
        REDIS_URL: redis://localhost:6379
        MONGODB_URL: mongodb://admin:password@localhost:27017
      run: |
        echo "🗄️ Setting up test databases..."
        npm run db:migrate:test
        npm run db:seed:test
        echo "✅ Test databases ready"
    
    - name: Run integration tests
      env:
        DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb
        REDIS_URL: redis://localhost:6379
        MONGODB_URL: mongodb://admin:password@localhost:27017
        NODE_ENV: test
      run: |
        npm run test:integration
        echo "✅ Integration tests completed"
    
    - name: Run API tests
      run: |
        npm start &
        sleep 10
        npm run test:api
        echo "✅ API tests completed"
    
    - name: Upload integration test results
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: integration-test-results
        path: |
          integration-test-results.xml
          api-test-results.xml
        retention-days: 30

  # Job 3: End-to-End Tests
  e2e-tests:
    name: E2E Tests
    runs-on: ubuntu-latest
    strategy:
      matrix:
        browser: [chromium, firefox, webkit]
        test-suite: [smoke, user-flows, regression]
    
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
    
    - name: Install Playwright browsers
      run: npx playwright install --with-deps ${{ matrix.browser }}
    
    - name: Build application
      run: npm run build
    
    - name: Start application
      run: |
        npm start &
        npx wait-on http://localhost:3000 --timeout 60000
        echo "✅ Application started"
    
    - name: Run E2E tests - ${{ matrix.test-suite }} on ${{ matrix.browser }}
      run: |
        npx playwright test \
          --project=${{ matrix.browser }} \
          tests/e2e/${{ matrix.test-suite }}
        echo "✅ E2E tests (${{ matrix.test-suite }}) completed on ${{ matrix.browser }}"
    
    - name: Upload E2E test results
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: e2e-results-${{ matrix.browser }}-${{ matrix.test-suite }}
        path: |
          test-results/
          playwright-report/
        retention-days: 30
    
    - name: Upload screenshots on failure
      if: failure()
      uses: actions/upload-artifact@v3
      with:
        name: e2e-screenshots-${{ matrix.browser }}-${{ matrix.test-suite }}
        path: test-results/
        retention-days: 30

  # Job 4: Cross-platform Tests
  cross-platform-tests:
    name: Cross-platform Tests
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        node-version: [18, 20]
    
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
    
    - name: Run platform-specific tests
      run: |
        npm run test:platform
        echo "✅ Platform tests completed on ${{ matrix.os }}"
    
    - name: Test CLI tools
      shell: bash
      run: |
        if [ "${{ matrix.os }}" == "windows-latest" ]; then
          npm run test:cli:windows
        else
          npm run test:cli:unix
        fi
        echo "✅ CLI tests completed"

  # Job 5: Test Results Aggregation
  test-results:
    name: Aggregate Test Results
    runs-on: ubuntu-latest
    needs: [unit-tests, integration-tests, e2e-tests, cross-platform-tests]
    if: always()
    
    steps:
    - name: Download all test artifacts
      uses: actions/download-artifact@v3
    
    - name: Setup Python for result processing
      uses: actions/setup-python@v4
      with:
        python-version: ${{ env.PYTHON_VERSION }}
    
    - name: Install Python dependencies
      run: |
        pip install pytest-html junitparser
    
    - name: Process test results
      run: |
        python scripts/aggregate-test-results.py
        echo "📊 Test results aggregated"
    
    - name: Generate test report
      run: |
        python scripts/generate-test-report.py
        echo "📋 Test report generated"
    
    - name: Upload aggregated results
      uses: actions/upload-artifact@v3
      with:
        name: aggregated-test-results
        path: |
          test-summary.html
          test-report.json
          coverage-summary.json
    
    - name: Comment PR with test results
      if: github.event_name == 'pull_request'
      uses: actions/github-script@v6
      with:
        script: |
          const fs = require('fs');
          const testResults = JSON.parse(fs.readFileSync('test-report.json', 'utf8'));
          
          const comment = `
          ## 🧪 Test Results Summary
          
          | Test Suite | Status | Passed | Failed | Duration |
          |------------|--------|--------|--------|----------|
          | Unit Tests | ${testResults.unit.status} | ${testResults.unit.passed} | ${testResults.unit.failed} | ${testResults.unit.duration} |
          | Integration | ${testResults.integration.status} | ${testResults.integration.passed} | ${testResults.integration.failed} | ${testResults.integration.duration} |
          | E2E Tests | ${testResults.e2e.status} | ${testResults.e2e.passed} | ${testResults.e2e.failed} | ${testResults.e2e.duration} |
          | Cross-platform | ${testResults.platform.status} | ${testResults.platform.passed} | ${testResults.platform.failed} | ${testResults.platform.duration} |
          
          **Overall Status:** ${testResults.overall.status}
          **Total Coverage:** ${testResults.coverage.percentage}%
          **Total Duration:** ${testResults.overall.duration}
          `;
          
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: comment
          });
```

## 🚀 Performance Testing Workflow

### .github/workflows/test-performance.yml

```yaml
name: Performance Testing

on:
  push:
    branches: [main]
  schedule:
    - cron: '0 3 * * 1'  # Weekly on Monday at 3 AM
  workflow_dispatch:
    inputs:
      test_type:
        description: 'Type of performance test'
        required: true
        default: 'load'
        type: choice
        options:
          - load
          - stress
          - spike
          - volume

jobs:
  performance-tests:
    name: Performance Tests
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: npm run build
    
    - name: Start application
      run: |
        npm start &
        npx wait-on http://localhost:3000
        echo "✅ Application started for performance testing"
    
    - name: Install k6
      run: |
        sudo gpg -k
        sudo gpg --no-default-keyring --keyring /usr/share/keyrings/k6-archive-keyring.gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C5AD17C747E3415A3642D57D77C6C491D6AC1D69
        echo "deb [signed-by=/usr/share/keyrings/k6-archive-keyring.gpg] https://dl.k6.io/deb stable main" | sudo tee /etc/apt/sources.list.d/k6.list
        sudo apt-get update
        sudo apt-get install k6
    
    - name: Run load tests
      if: github.event.inputs.test_type == 'load' || github.event.inputs.test_type == ''
      run: |
        k6 run tests/performance/load-test.js
        echo "📈 Load tests completed"
    
    - name: Run stress tests
      if: github.event.inputs.test_type == 'stress'
      run: |
        k6 run tests/performance/stress-test.js
        echo "🔥 Stress tests completed"
    
    - name: Run spike tests
      if: github.event.inputs.test_type == 'spike'
      run: |
        k6 run tests/performance/spike-test.js
        echo "⚡ Spike tests completed"
    
    - name: Run benchmark tests
      run: |
        npm run benchmark
        echo "🏁 Benchmark tests completed"
    
    - name: Analyze results
      run: |
        python scripts/analyze-performance.py
        echo "📊 Performance analysis completed"
    
    - name: Upload performance results
      uses: actions/upload-artifact@v3
      with:
        name: performance-results
        path: |
          performance-results.json
          benchmark-results.json
          performance-report.html
    
    - name: Performance regression check
      run: |
        python scripts/check-performance-regression.py
        echo "🔍 Performance regression check completed"
    
    - name: Comment performance results
      if: github.event_name == 'pull_request'
      uses: actions/github-script@v6
      with:
        script: |
          const fs = require('fs');
          const perfResults = JSON.parse(fs.readFileSync('performance-results.json', 'utf8'));
          
          const comment = `
          ## 📈 Performance Test Results
          
          | Metric | Current | Baseline | Change | Status |
          |--------|---------|----------|---------|--------|
          | Avg Response Time | ${perfResults.avg_response_time}ms | ${perfResults.baseline.avg_response_time}ms | ${perfResults.changes.response_time} | ${perfResults.status.response_time} |
          | 95th Percentile | ${perfResults.p95_response_time}ms | ${perfResults.baseline.p95_response_time}ms | ${perfResults.changes.p95} | ${perfResults.status.p95} |
          | Throughput | ${perfResults.throughput} req/s | ${perfResults.baseline.throughput} req/s | ${perfResults.changes.throughput} | ${perfResults.status.throughput} |
          | Error Rate | ${perfResults.error_rate}% | ${perfResults.baseline.error_rate}% | ${perfResults.changes.error_rate} | ${perfResults.status.error_rate} |
          
          **Overall Performance:** ${perfResults.overall_status}
          
          [View detailed report](${perfResults.report_url})
          `;
          
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: comment
          });
```

## 🔒 Security Testing Workflow

### .github/workflows/test-security.yml

```yaml
name: Security Testing

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  schedule:
    - cron: '0 4 * * 2'  # Weekly on Tuesday at 4 AM

jobs:
  security-scans:
    name: Security Scans
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run npm audit
      run: |
        npm audit --audit-level moderate --format json > npm-audit.json
        npm audit --audit-level moderate
        echo "🔍 NPM audit completed"
    
    - name: Snyk security scan
      uses: snyk/actions/node@master
      env:
        SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
      with:
        args: --file=package.json --json > snyk-results.json
        command: test
    
    - name: CodeQL Analysis
      uses: github/codeql-action/init@v2
      with:
        languages: javascript
        queries: security-and-quality
    
    - name: Autobuild
      uses: github/codeql-action/autobuild@v2
    
    - name: Perform CodeQL Analysis
      uses: github/codeql-action/analyze@v2
    
    - name: Run Semgrep security scan
      uses: returntocorp/semgrep-action@v1
      with:
        config: >-
          p/security-audit
          p/secrets
          p/owasp-top-ten
    
    - name: Build Docker image for security scan
      run: |
        docker build -t security-test-app .
    
    - name: Run Trivy security scan
      uses: aquasecurity/trivy-action@master
      with:
        image-ref: security-test-app
        format: 'sarif'
        output: 'trivy-results.sarif'
    
    - name: Upload Trivy scan results
      uses: github/codeql-action/upload-sarif@v2
      with:
        sarif_file: 'trivy-results.sarif'
    
    - name: OWASP ZAP security scan
      run: |
        npm start &
        sleep 30
        
        docker run -v $(pwd):/zap/wrk/:rw \
          -t owasp/zap2docker-stable zap-baseline.py \
          -t http://host.docker.internal:3000 \
          -J zap-report.json \
          -r zap-report.html
        echo "🛡️ OWASP ZAP scan completed"
    
    - name: Upload security scan results
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: security-scan-results
        path: |
          npm-audit.json
          snyk-results.json
          trivy-results.sarif
          zap-report.json
          zap-report.html
    
    - name: Security report summary
      if: always()
      run: |
        python scripts/security-summary.py
        echo "📋 Security summary generated"
```

## 📊 Test Configuration Files

### jest.config.js

```javascript
module.exports = {
  testEnvironment: 'node',
  roots: ['<rootDir>/src', '<rootDir>/tests'],
  testMatch: [
    '**/__tests__/**/*.js',
    '**/?(*.)+(spec|test).js'
  ],
  collectCoverageFrom: [
    'src/**/*.js',
    '!src/**/*.test.js',
    '!src/**/index.js'
  ],
  coverageDirectory: 'coverage',
  coverageReporters: [
    'text',
    'lcov',
    'html',
    'json-summary'
  ],
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
      statements: 80
    }
  },
  setupFilesAfterEnv: ['<rootDir>/tests/setup.js'],
  testTimeout: 10000,
  projects: [
    {
      displayName: 'unit',
      testMatch: ['<rootDir>/tests/unit/**/*.test.js']
    },
    {
      displayName: 'integration',
      testMatch: ['<rootDir>/tests/integration/**/*.test.js'],
      setupFilesAfterEnv: ['<rootDir>/tests/integration/setup.js']
    }
  ]
};
```

### playwright.config.js

```javascript
const { defineConfig, devices } = require('@playwright/test');

module.exports = defineConfig({
  testDir: './tests/e2e',
  fullyParallel: true,
  forbidOnly: !!process.env.CI,
  retries: process.env.CI ? 2 : 0,
  workers: process.env.CI ? 1 : undefined,
  reporter: [
    ['html'],
    ['junit', { outputFile: 'test-results/results.xml' }],
    ['json', { outputFile: 'test-results/results.json' }]
  ],
  use: {
    baseURL: 'http://localhost:3000',
    trace: 'on-first-retry',
    screenshot: 'only-on-failure',
    video: 'retain-on-failure'
  },
  projects: [
    {
      name: 'chromium',
      use: { ...devices['Desktop Chrome'] }
    },
    {
      name: 'firefox',
      use: { ...devices['Desktop Firefox'] }
    },
    {
      name: 'webkit',
      use: { ...devices['Desktop Safari'] }
    },
    {
      name: 'mobile-chrome',
      use: { ...devices['Pixel 5'] }
    },
    {
      name: 'mobile-safari',
      use: { ...devices['iPhone 12'] }
    }
  ],
  webServer: {
    command: 'npm start',
    port: 3000,
    reuseExistingServer: !process.env.CI
  }
});
```

### k6 Performance Test

```javascript
// tests/performance/load-test.js
import http from 'k6/http';
import { check, sleep } from 'k6';
import { Rate } from 'k6/metrics';

export let errorRate = new Rate('errors');

export let options = {
  stages: [
    { duration: '2m', target: 100 }, // Ramp up
    { duration: '5m', target: 100 }, // Steady state
    { duration: '2m', target: 200 }, // Ramp up
    { duration: '5m', target: 200 }, // Steady state
    { duration: '2m', target: 0 },   // Ramp down
  ],
  thresholds: {
    http_req_duration: ['p(95)<500'], // 95% of requests under 500ms
    http_req_failed: ['rate<0.1'],    // Error rate under 10%
    errors: ['rate<0.1'],             // Custom error rate
  },
};

export default function () {
  // Test main endpoint
  let response = http.get('http://localhost:3000/');
  check(response, {
    'status is 200': (r) => r.status === 200,
    'response time < 200ms': (r) => r.timings.duration < 200,
  }) || errorRate.add(1);

  // Test API endpoint
  response = http.get('http://localhost:3000/health');
  check(response, {
    'health check ok': (r) => r.status === 200,
  }) || errorRate.add(1);

  // Test POST endpoint
  response = http.post('http://localhost:3000/calculate', 
    JSON.stringify({ numbers: [1, 2, 3, 4, 5] }),
    { headers: { 'Content-Type': 'application/json' } }
  );
  check(response, {
    'calculation ok': (r) => r.status === 200,
  }) || errorRate.add(1);

  sleep(1);
}
```

## 🎯 Next Steps

Con questa configurazione di testing automation avanzata:

1. **[Deploy Automation](./03-deploy-automation.md)** - Deployment strategies
2. **[Esercizi Custom](../esercizi/02-custom-workflow.md)** - Crea i tuoi workflow
3. **[Monitoring Integration](../../23-Git-Flow-e-Strategie/guide/03-advanced-workflow-automation.md)** - Monitoring avanzato

Il tuo testing automation è ora enterprise-ready! 🧪🚀
