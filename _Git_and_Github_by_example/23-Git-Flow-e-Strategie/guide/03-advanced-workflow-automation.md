# 03 - Advanced Workflow Automation

## Obiettivi di Apprendimento
- Automatizzare completamente i workflow Git
- Implementare policy automation e compliance
- Creare sistemi di continuous integration avanzati
- Gestire automated testing e quality gates
- Implementare automated deployment pipelines
- Configurare monitoring e alerting per workflow

## 1. Automation Strategy Overview

### 1.1 Automation Levels

```
Automation Maturity Levels:
┌─────────────────────────────────────────────┐
│  Level 0: Manual                           │
│  ├─ Manual testing                         │
│  ├─ Manual deployment                      │
│  └─ Manual review process                  │
│                                             │
│  Level 1: Basic CI                         │
│  ├─ Automated testing                      │
│  ├─ Basic build automation                 │
│  └─ Manual deployment                      │
│                                             │
│  Level 2: Full CI/CD                       │
│  ├─ Automated testing                      │
│  ├─ Automated deployment                   │
│  ├─ Automated quality gates                │
│  └─ Basic monitoring                       │
│                                             │
│  Level 3: Advanced Automation              │
│  ├─ Intelligent testing                    │
│  ├─ Automated rollback                     │
│  ├─ Predictive quality gates               │
│  ├─ Self-healing systems                   │
│  └─ Advanced monitoring & AI               │
└─────────────────────────────────────────────┘
```

### 1.2 Automation Architecture

```yaml
# automation-architecture.yml
automation_stack:
  version_control:
    primary: git
    hosting: github/gitlab/bitbucket
    
  ci_cd:
    engines:
      - github_actions
      - gitlab_ci
      - jenkins
      - azure_devops
      
  quality_gates:
    code_analysis:
      - sonarqube
      - codeclimate
      - codebeat
    security_scanning:
      - snyk
      - owasp_zap
      - semgrep
    testing:
      - unit_tests
      - integration_tests
      - e2e_tests
      - performance_tests
      
  deployment:
    strategies:
      - blue_green
      - canary
      - rolling
      - feature_flags
      
  monitoring:
    infrastructure:
      - prometheus
      - grafana
      - datadog
    application:
      - sentry
      - newrelic
      - elastic_apm
```

## 2. Advanced GitHub Actions Workflows

### 2.1 Multi-Stage Production Pipeline

```yaml
# .github/workflows/production-pipeline.yml
name: Production Pipeline

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

env:
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}
  NODE_VERSION: '18'

jobs:
  # ====================================
  # PHASE 1: CODE QUALITY & SECURITY
  # ====================================
  code-quality:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        check: [lint, type-check, security, dependencies]
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run ${{ matrix.check }}
      run: |
        case ${{ matrix.check }} in
          lint)
            npm run lint -- --format json --output-file lint-results.json
            ;;
          type-check)
            npm run type-check
            ;;
          security)
            npm audit --audit-level=high
            npx snyk test
            ;;
          dependencies)
            npm run check-dependencies
            npx license-checker --onlyAllow 'MIT;Apache-2.0;BSD-3-Clause'
            ;;
        esac
    
    - name: Upload ${{ matrix.check }} results
      if: always()
      uses: actions/upload-artifact@v4
      with:
        name: ${{ matrix.check }}-results
        path: "*-results.json"

  # ====================================
  # PHASE 2: COMPREHENSIVE TESTING
  # ====================================
  test-matrix:
    runs-on: ${{ matrix.os }}
    strategy:
      fail-fast: false
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        node-version: [16, 18, 20]
        test-type: [unit, integration]
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v4
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run ${{ matrix.test-type }} tests
      run: |
        case ${{ matrix.test-type }} in
          unit)
            npm run test:unit -- --coverage --coverageReporters=json
            ;;
          integration)
            npm run test:integration
            ;;
        esac
    
    - name: Upload coverage to Codecov
      if: matrix.test-type == 'unit' && matrix.os == 'ubuntu-latest'
      uses: codecov/codecov-action@v3

  e2e-testing:
    runs-on: ubuntu-latest
    services:
      postgres:
        image: postgres:15
        env:
          POSTGRES_PASSWORD: postgres
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: npm run build
    
    - name: Setup test database
      run: |
        npm run db:migrate
        npm run db:seed:test
    
    - name: Install Playwright
      run: npx playwright install --with-deps
    
    - name: Run E2E tests
      run: npm run test:e2e
    
    - name: Upload E2E artifacts
      if: failure()
      uses: actions/upload-artifact@v4
      with:
        name: e2e-screenshots
        path: test-results/

  # ====================================
  # PHASE 3: PERFORMANCE & LOAD TESTING
  # ====================================
  performance-testing:
    runs-on: ubuntu-latest
    needs: [code-quality, test-matrix]
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: ${{ env.NODE_VERSION }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build application
      run: npm run build
    
    - name: Start application
      run: |
        npm start &
        sleep 30
    
    - name: Lighthouse CI
      run: |
        npm install -g lighthouse-ci
        lhci autorun
      env:
        LHCI_GITHUB_APP_TOKEN: ${{ secrets.LHCI_GITHUB_APP_TOKEN }}
    
    - name: Load testing with Artillery
      run: |
        npm install -g artillery
        artillery run load-test-config.yml
    
    - name: Performance budget check
      run: npm run performance:check

  # ====================================
  # PHASE 4: SECURITY SCANNING
  # ====================================
  security-scanning:
    runs-on: ubuntu-latest
    needs: [code-quality]
    steps:
    - uses: actions/checkout@v4
    
    - name: SAST with CodeQL
      uses: github/codeql-action/init@v3
      with:
        languages: javascript
    
    - name: CodeQL analysis
      uses: github/codeql-action/analyze@v3
    
    - name: OWASP ZAP Baseline Scan
      uses: zaproxy/action-baseline@v0.8.0
      with:
        target: 'http://localhost:3000'
    
    - name: Container security scan
      run: |
        docker build -t security-scan .
        docker run --rm -v /var/run/docker.sock:/var/run/docker.sock \
          aquasec/trivy image security-scan

  # ====================================
  # PHASE 5: BUILD & ARTIFACT CREATION
  # ====================================
  build-and-package:
    runs-on: ubuntu-latest
    needs: [test-matrix, e2e-testing, performance-testing]
    outputs:
      image-digest: ${{ steps.build.outputs.digest }}
      version: ${{ steps.version.outputs.version }}
    steps:
    - uses: actions/checkout@v4
    
    - name: Generate version
      id: version
      run: |
        if [[ ${{ github.ref }} == refs/heads/main ]]; then
          VERSION=$(date +%Y.%m.%d.%H%M%S)-${{ github.sha:0:7 }}
        else
          VERSION=pr-${{ github.event.number }}-${{ github.sha:0:7 }}
        fi
        echo "version=$VERSION" >> $GITHUB_OUTPUT
    
    - name: Setup Docker Buildx
      uses: docker/setup-buildx-action@v3
    
    - name: Login to Container Registry
      uses: docker/login-action@v3
      with:
        registry: ${{ env.REGISTRY }}
        username: ${{ github.actor }}
        password: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Build and push image
      id: build
      uses: docker/build-push-action@v5
      with:
        context: .
        push: true
        tags: |
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ steps.version.outputs.version }}
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:latest
        cache-from: type=gha
        cache-to: type=gha,mode=max
    
    - name: Generate SBOM
      run: |
        docker run --rm -v /var/run/docker.sock:/var/run/docker.sock \
          anchore/syft:latest \
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ steps.version.outputs.version }} \
          -o spdx-json=sbom.json
    
    - name: Upload SBOM
      uses: actions/upload-artifact@v4
      with:
        name: sbom
        path: sbom.json

  # ====================================
  # PHASE 6: DEPLOYMENT
  # ====================================
  deploy-staging:
    if: github.event_name == 'pull_request'
    runs-on: ubuntu-latest
    needs: [build-and-package, security-scanning]
    environment:
      name: staging-pr-${{ github.event.number }}
      url: https://staging-pr-${{ github.event.number }}.example.com
    steps:
    - name: Deploy to staging
      run: |
        echo "Deploying ${{ needs.build-and-package.outputs.version }} to staging"
        # Kubernetes deployment
        kubectl set image deployment/app \
          app=${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ needs.build-and-package.outputs.version }}
    
    - name: Wait for deployment
      run: kubectl rollout status deployment/app --timeout=300s
    
    - name: Run smoke tests
      run: |
        curl -f https://staging-pr-${{ github.event.number }}.example.com/health
        npm run test:smoke

  deploy-production:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    needs: [build-and-package, security-scanning]
    environment:
      name: production
      url: https://example.com
    steps:
    - name: Blue-Green Deployment
      run: |
        # Implementa blue-green deployment
        ./scripts/blue-green-deploy.sh \
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ needs.build-and-package.outputs.version }}

  # ====================================
  # PHASE 7: POST-DEPLOYMENT
  # ====================================
  post-deployment:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    needs: [deploy-production]
    steps:
    - name: Update monitoring dashboards
      run: |
        curl -X POST "${{ secrets.GRAFANA_API_URL }}/api/annotations" \
          -H "Authorization: Bearer ${{ secrets.GRAFANA_TOKEN }}" \
          -H "Content-Type: application/json" \
          -d '{
            "text": "Deployment ${{ needs.build-and-package.outputs.version }}",
            "tags": ["deployment", "production"]
          }'
    
    - name: Notify team
      uses: 8398a7/action-slack@v3
      with:
        status: ${{ job.status }}
        text: |
          🚀 Production deployment completed
          Version: ${{ needs.build-and-package.outputs.version }}
          Environment: https://example.com
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

### 2.2 Advanced Quality Gates

```yaml
# .github/workflows/quality-gates.yml
name: Quality Gates

on:
  pull_request:
    types: [opened, synchronize, reopened]

jobs:
  quality-analysis:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0  # Shallow clones disabled for SonarQube
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run tests with coverage
      run: npm run test:coverage
    
    - name: SonarQube Scan
      uses: sonarqube-quality-gate-action@master
      env:
        SONAR_TOKEN: ${{ secrets.SONAR_TOKEN }}
        SONAR_HOST_URL: ${{ secrets.SONAR_HOST_URL }}
    
    - name: Code Climate Coverage
      uses: paambaati/codeclimate-action@v5.0.0
      env:
        CC_TEST_REPORTER_ID: ${{ secrets.CC_TEST_REPORTER_ID }}
      with:
        coverageLocations: coverage/lcov.info:lcov
    
    - name: Quality Gate Check
      run: |
        # Custom quality gate logic
        python scripts/quality-gate-check.py \
          --coverage-threshold 80 \
          --complexity-threshold 10 \
          --duplication-threshold 3 \
          --security-hotspots 0
```

## 3. GitLab CI Advanced Pipelines

### 3.1 Enterprise GitLab Pipeline

```yaml
# .gitlab-ci.yml
stages:
  - validate
  - test
  - security
  - build
  - deploy-dev
  - deploy-staging
  - deploy-production
  - monitor

variables:
  DOCKER_DRIVER: overlay2
  DOCKER_TLS_CERTDIR: "/certs"
  KUBECONFIG: /etc/deploy/config

# ====================================
# TEMPLATES
# ====================================
.node_template: &node_template
  image: node:18-alpine
  cache:
    key: ${CI_COMMIT_REF_SLUG}
    paths:
      - node_modules/
  before_script:
    - npm ci

.deploy_template: &deploy_template
  image: bitnami/kubectl:latest
  before_script:
    - echo $KUBE_CONFIG | base64 -d > ${KUBECONFIG}
    - kubectl config current-context

# ====================================
# VALIDATION STAGE
# ====================================
validate:code-style:
  <<: *node_template
  stage: validate
  script:
    - npm run lint
    - npm run format:check
    - npm run type-check
  artifacts:
    reports:
      junit: lint-results.xml
    paths:
      - lint-results.xml
    expire_in: 1 week

validate:dependencies:
  <<: *node_template
  stage: validate
  script:
    - npm audit --audit-level=moderate
    - npm run check-licenses
    - npm outdated || true
  allow_failure: true

# ====================================
# TESTING STAGE
# ====================================
test:unit:
  <<: *node_template
  stage: test
  parallel:
    matrix:
      - NODE_VERSION: ["16", "18", "20"]
  image: node:${NODE_VERSION}-alpine
  script:
    - npm run test:unit -- --coverage
  coverage: '/Lines\s*:\s*(\d+\.\d+)%/'
  artifacts:
    reports:
      junit: test-results.xml
      coverage_report:
        coverage_format: cobertura
        path: coverage/cobertura-coverage.xml
    paths:
      - coverage/
    expire_in: 1 week

test:integration:
  <<: *node_template
  stage: test
  services:
    - postgres:14
    - redis:7
  variables:
    POSTGRES_DB: testdb
    POSTGRES_USER: testuser
    POSTGRES_PASSWORD: testpass
    DATABASE_URL: postgres://testuser:testpass@postgres:5432/testdb
    REDIS_URL: redis://redis:6379
  script:
    - npm run db:migrate
    - npm run test:integration
  artifacts:
    reports:
      junit: integration-test-results.xml

test:e2e:
  image: mcr.microsoft.com/playwright:v1.40.0-focal
  stage: test
  script:
    - npm ci
    - npm run build
    - npm run start:test &
    - sleep 30
    - npx playwright test
  artifacts:
    when: always
    paths:
      - playwright-report/
    expire_in: 1 week

# ====================================
# SECURITY STAGE
# ====================================
security:sast:
  stage: security
  include:
    - template: Security/SAST.gitlab-ci.yml

security:dependency-scanning:
  stage: security
  include:
    - template: Security/Dependency-Scanning.gitlab-ci.yml

security:container-scanning:
  stage: security
  include:
    - template: Security/Container-Scanning.gitlab-ci.yml
  dependencies:
    - build:docker

security:dast:
  stage: security
  include:
    - template: Security/DAST.gitlab-ci.yml
  variables:
    DAST_WEBSITE: https://staging.example.com
  only:
    - merge_requests

# ====================================
# BUILD STAGE
# ====================================
build:docker:
  stage: build
  image: docker:24.0.5
  services:
    - docker:24.0.5-dind
  variables:
    IMAGE_TAG: $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA
  script:
    - docker login -u $CI_REGISTRY_USER -p $CI_REGISTRY_PASSWORD $CI_REGISTRY
    - docker build --cache-from $CI_REGISTRY_IMAGE:latest -t $IMAGE_TAG .
    - docker tag $IMAGE_TAG $CI_REGISTRY_IMAGE:latest
    - docker push $IMAGE_TAG
    - docker push $CI_REGISTRY_IMAGE:latest
  only:
    - main
    - merge_requests

# ====================================
# DEPLOYMENT STAGES
# ====================================
deploy:dev:
  <<: *deploy_template
  stage: deploy-dev
  environment:
    name: development
    url: https://dev.example.com
  script:
    - envsubst < k8s/deployment.yml | kubectl apply -f -
    - kubectl rollout status deployment/app-dev
  only:
    - main

deploy:staging:
  <<: *deploy_template
  stage: deploy-staging
  environment:
    name: staging
    url: https://staging.example.com
  script:
    - envsubst < k8s/deployment.yml | kubectl apply -f -
    - kubectl rollout status deployment/app-staging
    - ./scripts/run-smoke-tests.sh staging.example.com
  when: manual
  only:
    - main

deploy:production:
  <<: *deploy_template
  stage: deploy-production
  environment:
    name: production
    url: https://example.com
  script:
    - ./scripts/blue-green-deploy.sh $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA
  when: manual
  only:
    - main
  before_script:
    - !reference [.deploy_template, before_script]
    - echo "Deploying to production - approval required"

# ====================================
# MONITORING STAGE
# ====================================
monitor:deployment:
  stage: monitor
  image: alpine/curl:latest
  script:
    - ./scripts/post-deployment-checks.sh
    - ./scripts/update-monitoring-dashboards.sh
  when: on_success
  only:
    - main
  dependencies:
    - deploy:production
```

## 4. Intelligent Testing Automation

### 4.1 Adaptive Test Selection

```javascript
// scripts/intelligent-test-runner.js
const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

class IntelligentTestRunner {
  constructor() {
    this.testHistory = this.loadTestHistory();
    this.changedFiles = this.getChangedFiles();
    this.testImpactMap = this.loadTestImpactMap();
  }

  getChangedFiles() {
    const result = execSync('git diff --name-only HEAD~1 HEAD', { encoding: 'utf8' });
    return result.trim().split('\n').filter(file => file);
  }

  loadTestImpactMap() {
    // Map che connette file di codice a test specifici
    try {
      return JSON.parse(fs.readFileSync('.test-impact-map.json', 'utf8'));
    } catch {
      return {};
    }
  }

  loadTestHistory() {
    try {
      return JSON.parse(fs.readFileSync('.test-history.json', 'utf8'));
    } catch {
      return { failures: [], performance: {} };
    }
  }

  selectTestsToRun() {
    const testsToRun = new Set();

    // 1. Tests direttamente collegati ai file modificati
    this.changedFiles.forEach(file => {
      const relatedTests = this.testImpactMap[file] || [];
      relatedTests.forEach(test => testsToRun.add(test));
    });

    // 2. Tests che falliscono frequentemente
    const flakyTests = this.testHistory.failures
      .filter(failure => failure.count > 3)
      .map(failure => failure.test);
    flakyTests.forEach(test => testsToRun.add(test));

    // 3. Tests lenti che non sono stati eseguiti di recente
    const slowTests = Object.entries(this.testHistory.performance)
      .filter(([test, perf]) => perf.averageTime > 5000) // > 5 secondi
      .filter(([test, perf]) => perf.lastRun < Date.now() - 24 * 60 * 60 * 1000) // > 1 giorno
      .map(([test]) => test);
    
    if (this.changedFiles.length > 10) {
      // Se molti file sono cambiati, aggiungi tests lenti
      slowTests.forEach(test => testsToRun.add(test));
    }

    return Array.from(testsToRun);
  }

  async runTests() {
    const selectedTests = this.selectTestsToRun();
    
    console.log(`🧪 Running ${selectedTests.length} selected tests`);
    console.log('Selected tests:', selectedTests);

    if (selectedTests.length === 0) {
      console.log('📊 No tests selected, running smoke tests only');
      return this.runSmokeTests();
    }

    const testCommand = `npm test -- ${selectedTests.join(' ')}`;
    
    try {
      const startTime = Date.now();
      execSync(testCommand, { stdio: 'inherit' });
      const endTime = Date.now();
      
      this.updateTestHistory(selectedTests, 'passed', endTime - startTime);
      return { success: true, testsRun: selectedTests.length };
    } catch (error) {
      this.updateTestHistory(selectedTests, 'failed', 0);
      throw error;
    }
  }

  runSmokeTests() {
    const smokeTests = [
      'tests/smoke/health-check.test.js',
      'tests/smoke/basic-flow.test.js'
    ];
    
    execSync(`npm test -- ${smokeTests.join(' ')}`, { stdio: 'inherit' });
    return { success: true, testsRun: smokeTests.length };
  }

  updateTestHistory(tests, result, duration) {
    tests.forEach(test => {
      if (result === 'failed') {
        const failure = this.testHistory.failures.find(f => f.test === test);
        if (failure) {
          failure.count++;
          failure.lastFailure = Date.now();
        } else {
          this.testHistory.failures.push({
            test,
            count: 1,
            lastFailure: Date.now()
          });
        }
      }

      if (result === 'passed' && duration > 0) {
        if (!this.testHistory.performance[test]) {
          this.testHistory.performance[test] = {
            averageTime: duration,
            runs: 1,
            lastRun: Date.now()
          };
        } else {
          const perf = this.testHistory.performance[test];
          perf.averageTime = (perf.averageTime * perf.runs + duration) / (perf.runs + 1);
          perf.runs++;
          perf.lastRun = Date.now();
        }
      }
    });

    fs.writeFileSync('.test-history.json', JSON.stringify(this.testHistory, null, 2));
  }

  updateTestImpactMap() {
    // Analizza coverage reports per aggiornare la mappa di impatto
    const coverageData = JSON.parse(fs.readFileSync('coverage/coverage-final.json', 'utf8'));
    
    Object.entries(coverageData).forEach(([file, coverage]) => {
      // Trova tests che toccano questo file
      const testsForFile = this.findTestsForFile(file, coverage);
      this.testImpactMap[file] = testsForFile;
    });

    fs.writeFileSync('.test-impact-map.json', JSON.stringify(this.testImpactMap, null, 2));
  }

  findTestsForFile(file, coverage) {
    // Logica per determinare quali test coprono un file specifico
    // Basata su coverage data e call stack analysis
    return [];
  }
}

// Esecuzione
if (require.main === module) {
  const runner = new IntelligentTestRunner();
  runner.runTests()
    .then(result => {
      console.log('✅ Tests completed:', result);
      process.exit(0);
    })
    .catch(error => {
      console.error('❌ Tests failed:', error.message);
      process.exit(1);
    });
}

module.exports = IntelligentTestRunner;
```

### 4.2 Automated Test Generation

```javascript
// scripts/test-generator.js
const fs = require('fs');
const path = require('path');
const { parse } = require('@babel/parser');
const traverse = require('@babel/traverse').default;

class TestGenerator {
  constructor(sourceDir = 'src', testDir = 'tests') {
    this.sourceDir = sourceDir;
    this.testDir = testDir;
    this.generatedTests = [];
  }

  analyzeFunction(functionNode, filename) {
    const analysis = {
      name: functionNode.id?.name || 'anonymous',
      params: functionNode.params.map(param => ({
        name: param.name,
        type: this.inferType(param),
        optional: param.optional || false
      })),
      returnType: this.inferReturnType(functionNode),
      complexity: this.calculateComplexity(functionNode),
      dependencies: this.findDependencies(functionNode),
      edgeCases: this.identifyEdgeCases(functionNode)
    };

    return analysis;
  }

  generateTestCases(analysis) {
    const testCases = [];

    // Test case per happy path
    testCases.push({
      name: `should work with valid input`,
      type: 'happy-path',
      inputs: this.generateValidInputs(analysis.params),
      expectedBehavior: 'success'
    });

    // Test cases per edge cases
    analysis.edgeCases.forEach(edgeCase => {
      testCases.push({
        name: `should handle ${edgeCase.description}`,
        type: 'edge-case',
        inputs: edgeCase.inputs,
        expectedBehavior: edgeCase.expectedBehavior
      });
    });

    // Test cases per error conditions
    analysis.params.forEach(param => {
      if (!param.optional) {
        testCases.push({
          name: `should throw error when ${param.name} is null`,
          type: 'error-case',
          inputs: this.generateErrorInputs(analysis.params, param.name, null),
          expectedBehavior: 'throw'
        });
      }
    });

    return testCases;
  }

  generateTestCode(functionAnalysis, testCases) {
    const testCode = `
// Auto-generated tests for ${functionAnalysis.name}
// Generated on: ${new Date().toISOString()}

import { ${functionAnalysis.name} } from '../${functionAnalysis.filename}';

describe('${functionAnalysis.name}', () => {
${testCases.map(testCase => this.generateSingleTest(testCase, functionAnalysis)).join('\n\n')}

  // Performance test
  it('should complete within acceptable time', () => {
    const start = performance.now();
    
    // Run function with typical inputs
    ${functionAnalysis.name}(${this.generateTypicalInputs(functionAnalysis.params)});
    
    const end = performance.now();
    const duration = end - start;
    
    // Should complete within 100ms for simple functions
    expect(duration).toBeLessThan(100);
  });

  // Memory usage test (if applicable)
  ${functionAnalysis.complexity > 5 ? this.generateMemoryTest(functionAnalysis) : ''}
});
`;

    return testCode;
  }

  generateSingleTest(testCase, functionAnalysis) {
    switch (testCase.type) {
      case 'happy-path':
        return `  it('${testCase.name}', () => {
    const result = ${functionAnalysis.name}(${testCase.inputs.map(i => JSON.stringify(i)).join(', ')});
    
    expect(result).toBeDefined();
    // Add more specific assertions based on expected behavior
  });`;

      case 'edge-case':
        return `  it('${testCase.name}', () => {
    const result = ${functionAnalysis.name}(${testCase.inputs.map(i => JSON.stringify(i)).join(', ')});
    
    // Verify edge case behavior
    ${this.generateEdgeCaseAssertions(testCase)}
  });`;

      case 'error-case':
        return `  it('${testCase.name}', () => {
    expect(() => {
      ${functionAnalysis.name}(${testCase.inputs.map(i => JSON.stringify(i)).join(', ')});
    }).toThrow();
  });`;

      default:
        return `  it('${testCase.name}', () => {
    // TODO: Implement test case
  });`;
    }
  }

  async generateTestsForFile(filePath) {
    const sourceCode = fs.readFileSync(filePath, 'utf8');
    const ast = parse(sourceCode, {
      sourceType: 'module',
      plugins: ['typescript', 'jsx']
    });

    const functions = [];

    traverse(ast, {
      FunctionDeclaration(path) {
        functions.push(this.analyzeFunction(path.node, filePath));
      },
      ArrowFunctionExpression(path) {
        if (path.parent.type === 'VariableDeclarator') {
          functions.push(this.analyzeFunction(path.node, filePath));
        }
      }
    });

    // Genera test per ogni funzione
    functions.forEach(func => {
      const testCases = this.generateTestCases(func);
      const testCode = this.generateTestCode(func, testCases);
      
      const testFileName = path.basename(filePath, path.extname(filePath)) + '.test.js';
      const testFilePath = path.join(this.testDir, testFileName);
      
      // Solo genera se il test non esiste già
      if (!fs.existsSync(testFilePath)) {
        fs.writeFileSync(testFilePath, testCode);
        this.generatedTests.push(testFilePath);
        console.log(`✅ Generated tests for ${func.name} in ${testFilePath}`);
      }
    });
  }

  async generateAllTests() {
    const sourceFiles = this.findSourceFiles(this.sourceDir);
    
    for (const file of sourceFiles) {
      await this.generateTestsForFile(file);
    }

    console.log(`🎯 Generated ${this.generatedTests.length} test files`);
    return this.generatedTests;
  }

  findSourceFiles(dir) {
    const files = [];
    const items = fs.readdirSync(dir);

    items.forEach(item => {
      const fullPath = path.join(dir, item);
      const stat = fs.statSync(fullPath);

      if (stat.isDirectory()) {
        files.push(...this.findSourceFiles(fullPath));
      } else if (item.match(/\.(js|ts|jsx|tsx)$/) && !item.includes('.test.')) {
        files.push(fullPath);
      }
    });

    return files;
  }

  // Helper methods per analisi del codice
  inferType(param) {
    // Logica per inferire il tipo del parametro
    return 'any';
  }

  inferReturnType(functionNode) {
    // Analizza return statements per inferire il tipo di ritorno
    return 'any';
  }

  calculateComplexity(functionNode) {
    // Calcola complessità ciclomatica
    let complexity = 1;
    
    traverse({
      type: 'File',
      program: {
        type: 'Program',
        body: [functionNode]
      }
    }, {
      IfStatement: () => complexity++,
      WhileStatement: () => complexity++,
      ForStatement: () => complexity++,
      SwitchCase: () => complexity++,
      ConditionalExpression: () => complexity++
    });

    return complexity;
  }

  findDependencies(functionNode) {
    // Trova dipendenze esterne
    return [];
  }

  identifyEdgeCases(functionNode) {
    // Identifica possibili edge cases
    return [];
  }

  generateValidInputs(params) {
    // Genera input validi per i parametri
    return params.map(param => {
      switch (param.type) {
        case 'string': return 'test string';
        case 'number': return 42;
        case 'boolean': return true;
        case 'array': return [];
        case 'object': return {};
        default: return null;
      }
    });
  }

  generateErrorInputs(params, excludeParam, errorValue) {
    return params.map(param => 
      param.name === excludeParam ? errorValue : this.generateValidInputs([param])[0]
    );
  }

  generateTypicalInputs(params) {
    return this.generateValidInputs(params).map(i => JSON.stringify(i)).join(', ');
  }

  generateEdgeCaseAssertions(testCase) {
    return `expect(result).toBe(${JSON.stringify(testCase.expectedBehavior)});`;
  }

  generateMemoryTest(functionAnalysis) {
    return `
  it('should not leak memory', () => {
    const initialMemory = process.memoryUsage().heapUsed;
    
    // Run function multiple times
    for (let i = 0; i < 1000; i++) {
      ${functionAnalysis.name}(${this.generateTypicalInputs(functionAnalysis.params)});
    }
    
    // Force garbage collection if available
    if (global.gc) {
      global.gc();
    }
    
    const finalMemory = process.memoryUsage().heapUsed;
    const memoryIncrease = finalMemory - initialMemory;
    
    // Memory increase should be reasonable (less than 10MB)
    expect(memoryIncrease).toBeLessThan(10 * 1024 * 1024);
  });`;
  }
}

// CLI interface
if (require.main === module) {
  const generator = new TestGenerator();
  
  generator.generateAllTests()
    .then(tests => {
      console.log('🎉 Test generation completed!');
      console.log('Generated tests:', tests);
    })
    .catch(error => {
      console.error('❌ Test generation failed:', error);
      process.exit(1);
    });
}

module.exports = TestGenerator;
```

## 5. Deployment Automation Strategies

### 5.1 Blue-Green Deployment Script

```bash
#!/bin/bash
# scripts/blue-green-deploy.sh

set -euo pipefail

# Configuration
NAMESPACE="production"
APP_NAME="myapp"
NEW_IMAGE="$1"
HEALTH_CHECK_URL="https://api.example.com/health"
ROLLBACK_TIMEOUT=300
HEALTH_CHECK_RETRIES=30

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log() {
    echo -e "${BLUE}[$(date +'%Y-%m-%d %H:%M:%S')]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Verifica prerequisiti
check_prerequisites() {
    log "Checking prerequisites..."
    
    if ! command -v kubectl &> /dev/null; then
        error "kubectl is required but not installed"
        exit 1
    fi
    
    if ! kubectl cluster-info &> /dev/null; then
        error "Cannot connect to Kubernetes cluster"
        exit 1
    fi
    
    if [[ -z "$NEW_IMAGE" ]]; then
        error "New image not specified"
        echo "Usage: $0 <new-image>"
        exit 1
    fi
    
    success "Prerequisites check passed"
}

# Determina quale slot è attualmente attivo
get_current_slot() {
    local current_slot
    current_slot=$(kubectl get service "$APP_NAME" -n "$NAMESPACE" -o jsonpath='{.spec.selector.slot}' 2>/dev/null || echo "blue")
    echo "$current_slot"
}

# Determina lo slot target per il deployment
get_target_slot() {
    local current_slot="$1"
    if [[ "$current_slot" == "blue" ]]; then
        echo "green"
    else
        echo "blue"
    fi
}

# Deploy della nuova versione nello slot target
deploy_to_slot() {
    local slot="$1"
    local image="$2"
    
    log "Deploying $image to $slot slot..."
    
    # Applica deployment configuration
    cat <<EOF | kubectl apply -f -
apiVersion: apps/v1
kind: Deployment
metadata:
  name: ${APP_NAME}-${slot}
  namespace: ${NAMESPACE}
  labels:
    app: ${APP_NAME}
    slot: ${slot}
spec:
  replicas: 3
  selector:
    matchLabels:
      app: ${APP_NAME}
      slot: ${slot}
  template:
    metadata:
      labels:
        app: ${APP_NAME}
        slot: ${slot}
    spec:
      containers:
      - name: ${APP_NAME}
        image: ${image}
        ports:
        - containerPort: 3000
        env:
        - name: SLOT
          value: ${slot}
        - name: VERSION
          value: ${image##*:}
        livenessProbe:
          httpGet:
            path: /health
            port: 3000
          initialDelaySeconds: 30
          periodSeconds: 10
        readinessProbe:
          httpGet:
            path: /ready
            port: 3000
          initialDelaySeconds: 5
          periodSeconds: 5
        resources:
          requests:
            memory: "128Mi"
            cpu: "100m"
          limits:
            memory: "512Mi"
            cpu: "500m"
---
apiVersion: v1
kind: Service
metadata:
  name: ${APP_NAME}-${slot}
  namespace: ${NAMESPACE}
  labels:
    app: ${APP_NAME}
    slot: ${slot}
spec:
  selector:
    app: ${APP_NAME}
    slot: ${slot}
  ports:
  - port: 80
    targetPort: 3000
    protocol: TCP
  type: ClusterIP
EOF

    # Attendi che il deployment sia pronto
    log "Waiting for $slot slot deployment to be ready..."
    kubectl rollout status deployment/"${APP_NAME}-${slot}" -n "$NAMESPACE" --timeout=600s
    
    success "$slot slot deployment completed"
}

# Esegui health check sullo slot target
health_check() {
    local slot="$1"
    local service_url="http://${APP_NAME}-${slot}.${NAMESPACE}.svc.cluster.local"
    
    log "Performing health check on $slot slot..."
    
    # Port forward per test locale
    kubectl port-forward service/"${APP_NAME}-${slot}" 8080:80 -n "$NAMESPACE" &
    local port_forward_pid=$!
    
    sleep 5
    
    local retries=0
    local max_retries="$HEALTH_CHECK_RETRIES"
    
    while [[ $retries -lt $max_retries ]]; do
        if curl -sf "http://localhost:8080/health" &> /dev/null; then
            success "Health check passed for $slot slot"
            kill $port_forward_pid 2>/dev/null || true
            return 0
        fi
        
        ((retries++))
        log "Health check attempt $retries/$max_retries failed, retrying..."
        sleep 10
    done
    
    kill $port_forward_pid 2>/dev/null || true
    error "Health check failed for $slot slot after $max_retries attempts"
    return 1
}

# Esegui smoke tests
run_smoke_tests() {
    local slot="$1"
    
    log "Running smoke tests on $slot slot..."
    
    # Port forward per test
    kubectl port-forward service/"${APP_NAME}-${slot}" 8081:80 -n "$NAMESPACE" &
    local port_forward_pid=$!
    
    sleep 5
    
    # Esegui smoke tests
    if npm run test:smoke -- --baseURL=http://localhost:8081; then
        success "Smoke tests passed for $slot slot"
        kill $port_forward_pid 2>/dev/null || true
        return 0
    else
        error "Smoke tests failed for $slot slot"
        kill $port_forward_pid 2>/dev/null || true
        return 1
    fi
}

# Switch del traffico al nuovo slot
switch_traffic() {
    local new_slot="$1"
    
    log "Switching traffic to $new_slot slot..."
    
    # Aggiorna il main service per puntare al nuovo slot
    kubectl patch service "$APP_NAME" -n "$NAMESPACE" -p "{\"spec\":{\"selector\":{\"slot\":\"$new_slot\"}}}"
    
    # Verifica che il traffico sia switchato
    sleep 10
    
    local current_slot
    current_slot=$(kubectl get service "$APP_NAME" -n "$NAMESPACE" -o jsonpath='{.spec.selector.slot}')
    
    if [[ "$current_slot" == "$new_slot" ]]; then
        success "Traffic successfully switched to $new_slot slot"
        return 0
    else
        error "Failed to switch traffic to $new_slot slot"
        return 1
    fi
}

# Cleanup del vecchio slot
cleanup_old_slot() {
    local old_slot="$1"
    
    log "Cleaning up $old_slot slot..."
    
    # Scala down il vecchio deployment
    kubectl scale deployment "${APP_NAME}-${old_slot}" --replicas=0 -n "$NAMESPACE"
    
    # Opzionalmente, rimuovi completamente il deployment
    # kubectl delete deployment "${APP_NAME}-${old_slot}" -n "$NAMESPACE"
    
    success "$old_slot slot cleaned up"
}

# Rollback in caso di problemi
rollback() {
    local current_slot="$1"
    local previous_slot="$2"
    
    warning "Performing rollback to $previous_slot slot..."
    
    # Switch traffic back
    kubectl patch service "$APP_NAME" -n "$NAMESPACE" -p "{\"spec\":{\"selector\":{\"slot\":\"$previous_slot\"}}}"
    
    # Scala up il vecchio deployment se necessario
    kubectl scale deployment "${APP_NAME}-${previous_slot}" --replicas=3 -n "$NAMESPACE"
    
    error "Deployment rolled back to $previous_slot slot"
    exit 1
}

# Monitoraggio post-deployment
post_deployment_monitoring() {
    local new_slot="$1"
    
    log "Starting post-deployment monitoring..."
    
    # Monitor metrics per 5 minuti
    local monitor_duration=300
    local start_time=$(date +%s)
    local end_time=$((start_time + monitor_duration))
    
    while [[ $(date +%s) -lt $end_time ]]; do
        # Check error rate
        local error_rate
        error_rate=$(curl -s "http://prometheus:9090/api/v1/query?query=rate(http_requests_total{status=~\"5..\"}[5m])" | jq -r '.data.result[0].value[1] // "0"')
        
        if (( $(echo "$error_rate > 0.05" | bc -l) )); then
            error "High error rate detected: $error_rate"
            return 1
        fi
        
        # Check response time
        local response_time
        response_time=$(curl -s "http://prometheus:9090/api/v1/query?query=histogram_quantile(0.95,rate(http_request_duration_seconds_bucket[5m]))" | jq -r '.data.result[0].value[1] // "0"')
        
        if (( $(echo "$response_time > 1.0" | bc -l) )); then
            warning "High response time detected: ${response_time}s"
        fi
        
        log "Monitoring... Error rate: $error_rate, P95 response time: ${response_time}s"
        sleep 30
    done
    
    success "Post-deployment monitoring completed successfully"
}

# Notifica del deployment
notify_deployment() {
    local status="$1"
    local slot="$2"
    local image="$3"
    
    local message
    if [[ "$status" == "success" ]]; then
        message="🚀 Deployment successful! New version deployed to $slot slot: $image"
    else
        message="❌ Deployment failed! Rollback completed."
    fi
    
    # Slack notification
    if [[ -n "${SLACK_WEBHOOK_URL:-}" ]]; then
        curl -X POST -H 'Content-type: application/json' \
            --data "{\"text\":\"$message\"}" \
            "$SLACK_WEBHOOK_URL"
    fi
    
    # Teams notification
    if [[ -n "${TEAMS_WEBHOOK_URL:-}" ]]; then
        curl -X POST -H 'Content-type: application/json' \
            --data "{\"text\":\"$message\"}" \
            "$TEAMS_WEBHOOK_URL"
    fi
    
    log "Deployment notification sent"
}

# Main deployment flow
main() {
    log "Starting Blue-Green Deployment"
    log "Target image: $NEW_IMAGE"
    
    check_prerequisites
    
    local current_slot
    current_slot=$(get_current_slot)
    log "Current active slot: $current_slot"
    
    local target_slot
    target_slot=$(get_target_slot "$current_slot")
    log "Target deployment slot: $target_slot"
    
    # Deploy to target slot
    if ! deploy_to_slot "$target_slot" "$NEW_IMAGE"; then
        error "Deployment to $target_slot slot failed"
        notify_deployment "failed" "$target_slot" "$NEW_IMAGE"
        exit 1
    fi
    
    # Health check
    if ! health_check "$target_slot"; then
        error "Health check failed"
        rollback "$target_slot" "$current_slot"
        notify_deployment "failed" "$target_slot" "$NEW_IMAGE"
        exit 1
    fi
    
    # Smoke tests
    if ! run_smoke_tests "$target_slot"; then
        error "Smoke tests failed"
        rollback "$target_slot" "$current_slot"
        notify_deployment "failed" "$target_slot" "$NEW_IMAGE"
        exit 1
    fi
    
    # Switch traffic
    if ! switch_traffic "$target_slot"; then
        error "Traffic switch failed"
        rollback "$target_slot" "$current_slot"
        notify_deployment "failed" "$target_slot" "$NEW_IMAGE"
        exit 1
    fi
    
    # Post-deployment monitoring
    if ! post_deployment_monitoring "$target_slot"; then
        error "Post-deployment monitoring detected issues"
        rollback "$target_slot" "$current_slot"
        notify_deployment "failed" "$target_slot" "$NEW_IMAGE"
        exit 1
    fi
    
    # Cleanup old slot
    cleanup_old_slot "$current_slot"
    
    success "Blue-Green Deployment completed successfully!"
    notify_deployment "success" "$target_slot" "$NEW_IMAGE"
    
    log "New active slot: $target_slot"
    log "Deployed image: $NEW_IMAGE"
}

# Trap per cleanup in caso di interruzione
trap 'error "Deployment interrupted"; exit 1' INT TERM

# Esegui main function
main "$@"
```

## Quiz di Verifica

### Domanda 1
Quale componente è fondamentale per l'automation Level 3?
- a) Basic CI/CD
- b) Manual testing
- c) AI e machine learning
- d) Version control

### Domanda 2
In una pipeline GitLab CI, quale stage viene tipicamente eseguito per ultimo?
- a) test
- b) build
- c) deploy
- d) monitor

### Domanda 3
Qual è il vantaggio principale dell'intelligent test selection?
- a) Maggiore copertura
- b) Tempi di esecuzione ridotti
- c) Migliore qualità del codice
- d) Facilità di manutenzione

### Domanda 4
Nel blue-green deployment, cosa succede al vecchio slot dopo il deploy?
- a) Viene eliminato immediatamente
- b) Rimane attivo per rollback
- c) Viene scalato down
- d) Diventa il nuovo target

### Domanda 5
Quale metrica è più importante per valutare l'efficacia della pipeline?
- a) Numero di test
- b) Lead time
- c) Dimensione del codice
- d) Numero di deploy

## Esercizi Pratici

### Esercizio 1: Advanced GitHub Actions Pipeline
Crea una pipeline completa con:
1. Multi-stage testing parallelo
2. Security scanning integrato
3. Performance testing automatico
4. Blue-green deployment
5. Post-deployment monitoring

### Esercizio 2: Intelligent Test System
Implementa sistema di test intelligente:
1. Test impact mapping
2. Flaky test detection
3. Performance-based test selection
4. Automated test generation
5. Test result analytics

### Esercizio 3: Multi-Environment Deployment
Configura deployment automation per:
1. Environment progression (dev → staging → prod)
2. Automated rollback capabilities
3. Health checks e monitoring
4. Notification system
5. Compliance reporting

---

## Navigazione

⬅️ **Precedente**: [02 - GitHub Flow vs Alternatives](02-github-flow-alternatives.md)

➡️ **Successivo**: [Esempi Pratici](../esempi/README.md)

🏠 **Home**: [Indice Generale](../../README.md)
