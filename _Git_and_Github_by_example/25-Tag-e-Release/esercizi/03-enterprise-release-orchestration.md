# 03 - Esercizio: Enterprise Release Orchestration

Questo esercizio avanzato simula un ambiente enterprise con orchestrazione di release multi-repository, gestione di dipendenze complesse, deployment coordinato e monitoraggio di release cross-platform.

## 🎯 Obiettivi

- Orchestrare release coordinate tra microservizi
- Implementare dependency management avanzato
- Gestire release matrix multi-platform
- Configurare release gates e quality checks
- Automatizzare rollout graduale e rollback
- Monitorare health e metrics post-release

## 📋 Prerequisiti

- Completamento esercizi 01 e 02
- Conoscenza di microservizi architecture
- Familiarità con CI/CD pipeline avanzate
- Concetti di DevOps e monitoring

## 🚀 Scenario Enterprise

Sei il Release Manager di **TechCorp**, una multinazionale che gestisce:
- **E-commerce Platform**: 8 microservizi interconnessi
- **Mobile Apps**: iOS, Android, Progressive Web App
- **Desktop Applications**: Windows, macOS, Linux
- **Infrastructure**: Kubernetes, databases, caching layers

Devi orchestrare una major release (v3.0.0) che include:
- New payment processing system
- Enhanced security features
- Performance optimizations
- Breaking API changes con backward compatibility

## Parte 1: Multi-Repository Setup

### 1.1 Architettura dei Repository

```bash
# Crea workspace enterprise
mkdir techcorp-release-v3
cd techcorp-release-v3

# Structure enterprise repositories
mkdir -p {orchestrator,services,apps,infrastructure,docs}

# Service repositories
mkdir -p services/{auth-service,payment-service,inventory-service,notification-service}
mkdir -p services/{user-service,order-service,shipping-service,analytics-service}

# Application repositories
mkdir -p apps/{mobile-ios,mobile-android,web-app,desktop-electron}

# Infrastructure repositories
mkdir -p infrastructure/{k8s-configs,terraform,monitoring,security}
```

### 1.2 Release Orchestrator Repository

```bash
cd orchestrator
git init
git branch -M main

# Create orchestrator structure
mkdir -p {scripts,config,templates,pipelines}
```

**`package.json`** (Release Orchestrator):
```json
{
  "name": "techcorp-release-orchestrator",
  "version": "3.0.0-orchestrator",
  "description": "Enterprise release orchestration system",
  "main": "src/orchestrator.js",
  "scripts": {
    "validate-deps": "node scripts/validate-dependencies.js",
    "pre-release-checks": "node scripts/pre-release-checks.js",
    "coordinate-release": "node scripts/coordinate-release.js",
    "monitor-deployment": "node scripts/monitor-deployment.js",
    "rollback-release": "node scripts/rollback-release.js",
    "generate-release-report": "node scripts/generate-report.js"
  },
  "dependencies": {
    "@octokit/rest": "^19.0.0",
    "semver": "^7.5.0",
    "yaml": "^2.3.0",
    "chalk": "^5.3.0",
    "inquirer": "^9.2.0"
  },
  "devDependencies": {
    "jest": "^29.5.0"
  }
}
```

**`config/release-config.yaml`**:
```yaml
# Release Configuration v3.0.0
release:
  version: "3.0.0"
  codename: "Phoenix"
  target_date: "2024-03-15"
  environments:
    - staging
    - canary
    - production
  
# Service Dependencies & Order
dependencies:
  auth-service:
    version: "3.0.0"
    dependencies: []
    critical: true
    rollout_group: 1
  
  payment-service:
    version: "3.0.0"
    dependencies: ["auth-service"]
    critical: true
    rollout_group: 2
  
  inventory-service:
    version: "3.0.0"
    dependencies: ["auth-service"]
    critical: false
    rollout_group: 2
  
  order-service:
    version: "3.0.0"
    dependencies: ["auth-service", "payment-service", "inventory-service"]
    critical: true
    rollout_group: 3
  
  notification-service:
    version: "3.0.0"
    dependencies: ["auth-service"]
    critical: false
    rollout_group: 4
  
  user-service:
    version: "3.0.0"
    dependencies: ["auth-service"]
    critical: false
    rollout_group: 2
  
  shipping-service:
    version: "3.0.0"
    dependencies: ["order-service"]
    critical: false
    rollout_group: 4
  
  analytics-service:
    version: "3.0.0"
    dependencies: ["user-service", "order-service"]
    critical: false
    rollout_group: 5

# Application Dependencies
applications:
  mobile-ios:
    version: "3.0.0"
    platform: "ios"
    requires_services: ["auth-service", "payment-service", "order-service"]
    store_release: true
  
  mobile-android:
    version: "3.0.0"
    platform: "android"
    requires_services: ["auth-service", "payment-service", "order-service"]
    store_release: true
  
  web-app:
    version: "3.0.0"
    platform: "web"
    requires_services: ["auth-service", "payment-service", "order-service"]
    cdn_deployment: true
  
  desktop-electron:
    version: "3.0.0"
    platform: "desktop"
    requires_services: ["auth-service", "payment-service", "order-service"]
    auto_update: true

# Quality Gates
quality_gates:
  - name: "unit_tests"
    required: true
    threshold: 90
  
  - name: "integration_tests"
    required: true
    threshold: 85
  
  - name: "e2e_tests"
    required: true
    threshold: 95
  
  - name: "security_scan"
    required: true
    threshold: 100
  
  - name: "performance_tests"
    required: true
    threshold: 90
  
  - name: "dependency_audit"
    required: true
    threshold: 100

# Rollout Strategy
rollout:
  strategy: "blue-green"
  canary_percentage: 5
  rollout_intervals: "30m"
  auto_rollback: true
  health_check_timeout: "10m"
  
# Monitoring & Alerting
monitoring:
  metrics:
    - "error_rate"
    - "response_time"
    - "throughput"
    - "cpu_usage"
    - "memory_usage"
  
  alerts:
    error_rate_threshold: 1.0
    response_time_threshold: 500
    availability_threshold: 99.9
```

### 1.3 Release Orchestration Script

**`scripts/orchestrator.js`**:
```javascript
#!/usr/bin/env node

const { Octokit } = require('@octokit/rest');
const semver = require('semver');
const yaml = require('yaml');
const fs = require('fs');
const chalk = require('chalk');
const { execSync } = require('child_process');

class ReleaseOrchestrator {
  constructor() {
    this.config = yaml.parse(fs.readFileSync('config/release-config.yaml', 'utf8'));
    this.octokit = new Octokit({
      auth: process.env.GITHUB_TOKEN
    });
    this.releaseState = {
      started: new Date(),
      phase: 'initialized',
      deployedServices: [],
      failedServices: [],
      rollbackNeeded: false
    };
  }

  async validateDependencies() {
    console.log(chalk.blue('🔍 Validating service dependencies...'));
    
    const services = Object.keys(this.config.dependencies);
    const dependencyGraph = this.buildDependencyGraph();
    
    // Check for circular dependencies
    if (this.hasCircularDependencies(dependencyGraph)) {
      throw new Error('Circular dependencies detected!');
    }
    
    // Validate version compatibility
    for (const service of services) {
      await this.validateServiceVersion(service);
    }
    
    console.log(chalk.green('✅ All dependencies validated'));
  }

  buildDependencyGraph() {
    const graph = {};
    Object.entries(this.config.dependencies).forEach(([service, config]) => {
      graph[service] = config.dependencies || [];
    });
    return graph;
  }

  hasCircularDependencies(graph) {
    const visited = new Set();
    const recursionStack = new Set();
    
    const hasCycle = (node) => {
      if (recursionStack.has(node)) return true;
      if (visited.has(node)) return false;
      
      visited.add(node);
      recursionStack.add(node);
      
      for (const neighbor of graph[node] || []) {
        if (hasCycle(neighbor)) return true;
      }
      
      recursionStack.delete(node);
      return false;
    };
    
    for (const node of Object.keys(graph)) {
      if (hasCycle(node)) return true;
    }
    return false;
  }

  async validateServiceVersion(service) {
    const expectedVersion = this.config.dependencies[service].version;
    
    try {
      // Check if service repository has the required version tag
      const { data: tags } = await this.octokit.repos.listTags({
        owner: 'techcorp',
        repo: service,
        per_page: 100
      });
      
      const versionExists = tags.some(tag => tag.name === `v${expectedVersion}`);
      
      if (!versionExists) {
        throw new Error(`Service ${service} missing version ${expectedVersion}`);
      }
      
      console.log(chalk.green(`✅ ${service}: v${expectedVersion}`));
    } catch (error) {
      console.error(chalk.red(`❌ ${service}: ${error.message}`));
      throw error;
    }
  }

  async runQualityGates() {
    console.log(chalk.blue('🧪 Running quality gates...'));
    
    for (const gate of this.config.quality_gates) {
      console.log(chalk.yellow(`Running ${gate.name}...`));
      
      const result = await this.executeQualityGate(gate);
      
      if (result.score < gate.threshold) {
        throw new Error(`Quality gate ${gate.name} failed: ${result.score}% < ${gate.threshold}%`);
      }
      
      console.log(chalk.green(`✅ ${gate.name}: ${result.score}%`));
    }
  }

  async executeQualityGate(gate) {
    // Simulate quality gate execution
    // In real implementation, this would integrate with testing tools
    const baseScore = Math.random() * 100;
    const jitter = (Math.random() - 0.5) * 10;
    const score = Math.max(0, Math.min(100, baseScore + jitter));
    
    // Simulate execution time
    await new Promise(resolve => setTimeout(resolve, 2000));
    
    return { score: Math.round(score) };
  }

  async coordinateRelease() {
    console.log(chalk.blue('🚀 Starting coordinated release...'));
    
    try {
      await this.validateDependencies();
      await this.runQualityGates();
      
      // Deploy in rollout groups
      const rolloutGroups = this.organizeRolloutGroups();
      
      for (const [groupNum, services] of rolloutGroups.entries()) {
        console.log(chalk.cyan(`\n📦 Deploying Group ${groupNum + 1}: ${services.join(', ')}`));
        
        await this.deployServicesGroup(services);
        await this.waitForHealthChecks(services);
        
        this.releaseState.deployedServices.push(...services);
      }
      
      // Deploy applications after all services
      await this.deployApplications();
      
      console.log(chalk.green('\n🎉 Release completed successfully!'));
      await this.generateReleaseReport();
      
    } catch (error) {
      console.error(chalk.red(`\n💥 Release failed: ${error.message}`));
      await this.initiateRollback();
      throw error;
    }
  }

  organizeRolloutGroups() {
    const groups = new Map();
    
    Object.entries(this.config.dependencies).forEach(([service, config]) => {
      const group = config.rollout_group || 1;
      if (!groups.has(group)) {
        groups.set(group, []);
      }
      groups.get(group).push(service);
    });
    
    return Array.from(groups.entries()).sort((a, b) => a[0] - b[0]);
  }

  async deployServicesGroup(services) {
    const deployPromises = services.map(service => this.deployService(service));
    await Promise.all(deployPromises);
  }

  async deployService(service) {
    console.log(chalk.yellow(`  📦 Deploying ${service}...`));
    
    // Simulate deployment
    await new Promise(resolve => setTimeout(resolve, 5000));
    
    // Simulate occasional failure for demonstration
    if (Math.random() < 0.05) {
      throw new Error(`Deployment failed for ${service}`);
    }
    
    console.log(chalk.green(`  ✅ ${service} deployed`));
  }

  async waitForHealthChecks(services) {
    console.log(chalk.yellow('  🏥 Waiting for health checks...'));
    
    for (const service of services) {
      let attempts = 0;
      const maxAttempts = 10;
      
      while (attempts < maxAttempts) {
        const healthy = await this.checkServiceHealth(service);
        
        if (healthy) {
          console.log(chalk.green(`  ✅ ${service} healthy`));
          break;
        }
        
        attempts++;
        if (attempts === maxAttempts) {
          throw new Error(`Health check timeout for ${service}`);
        }
        
        await new Promise(resolve => setTimeout(resolve, 30000));
      }
    }
  }

  async checkServiceHealth(service) {
    // Simulate health check
    return Math.random() > 0.1; // 90% success rate
  }

  async deployApplications() {
    console.log(chalk.cyan('\n📱 Deploying applications...'));
    
    const apps = Object.keys(this.config.applications);
    
    for (const app of apps) {
      await this.deployApplication(app);
    }
  }

  async deployApplication(app) {
    console.log(chalk.yellow(`  📱 Deploying ${app}...`));
    
    const config = this.config.applications[app];
    
    // Platform-specific deployment logic
    switch (config.platform) {
      case 'ios':
        await this.deployToAppStore(app, 'ios');
        break;
      case 'android':
        await this.deployToPlayStore(app);
        break;
      case 'web':
        await this.deploySPA(app);
        break;
      case 'desktop':
        await this.deployElectronApp(app);
        break;
    }
    
    console.log(chalk.green(`  ✅ ${app} deployed`));
  }

  async deployToAppStore(app, platform) {
    // Simulate App Store deployment
    await new Promise(resolve => setTimeout(resolve, 10000));
  }

  async deployToPlayStore(app) {
    // Simulate Play Store deployment
    await new Promise(resolve => setTimeout(resolve, 8000));
  }

  async deploySPA(app) {
    // Simulate SPA deployment to CDN
    await new Promise(resolve => setTimeout(resolve, 3000));
  }

  async deployElectronApp(app) {
    // Simulate Electron app deployment
    await new Promise(resolve => setTimeout(resolve, 5000));
  }

  async initiateRollback() {
    console.log(chalk.red('\n🔄 Initiating rollback procedure...'));
    
    this.releaseState.rollbackNeeded = true;
    
    // Rollback in reverse order
    const servicesToRollback = [...this.releaseState.deployedServices].reverse();
    
    for (const service of servicesToRollback) {
      try {
        await this.rollbackService(service);
        console.log(chalk.yellow(`🔄 Rolled back ${service}`));
      } catch (error) {
        console.error(chalk.red(`❌ Rollback failed for ${service}: ${error.message}`));
      }
    }
  }

  async rollbackService(service) {
    // Simulate service rollback
    await new Promise(resolve => setTimeout(resolve, 3000));
  }

  async generateReleaseReport() {
    const report = {
      release: {
        version: this.config.release.version,
        codename: this.config.release.codename,
        started: this.releaseState.started,
        completed: new Date(),
        status: this.releaseState.rollbackNeeded ? 'ROLLED_BACK' : 'SUCCESS'
      },
      deployed_services: this.releaseState.deployedServices,
      failed_services: this.releaseState.failedServices,
      applications: Object.keys(this.config.applications),
      quality_gates: this.config.quality_gates.map(gate => ({
        name: gate.name,
        status: 'PASSED'
      }))
    };
    
    fs.writeFileSync('release-report.json', JSON.stringify(report, null, 2));
    console.log(chalk.green('\n📄 Release report generated: release-report.json'));
  }
}

// CLI Interface
async function main() {
  const orchestrator = new ReleaseOrchestrator();
  
  const command = process.argv[2];
  
  try {
    switch (command) {
      case 'validate':
        await orchestrator.validateDependencies();
        break;
      case 'quality-gates':
        await orchestrator.runQualityGates();
        break;
      case 'release':
        await orchestrator.coordinateRelease();
        break;
      default:
        console.log('Usage: node orchestrator.js [validate|quality-gates|release]');
    }
  } catch (error) {
    console.error(chalk.red(`Error: ${error.message}`));
    process.exit(1);
  }
}

if (require.main === module) {
  main();
}

module.exports = ReleaseOrchestrator;
```

## Parte 2: Service Repository Setup

### 2.1 Example Service (Auth Service)

```bash
cd ../services/auth-service
git init
git branch -M main

# Create service structure
mkdir -p {src,tests,k8s,docs}
```

**`package.json`** (Auth Service):
```json
{
  "name": "auth-service",
  "version": "3.0.0",
  "description": "Authentication and authorization service",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js",
    "test": "jest",
    "test:integration": "jest --config jest.integration.config.js",
    "lint": "eslint src/",
    "security-audit": "npm audit",
    "build": "npm run test && npm run lint",
    "pre-release": "npm run build && npm run security-audit"
  },
  "dependencies": {
    "express": "^4.18.0",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.0"
  },
  "devDependencies": {
    "jest": "^29.5.0",
    "supertest": "^6.3.0",
    "eslint": "^8.40.0"
  }
}
```

**`k8s/deployment.yaml`**:
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: auth-service
  labels:
    app: auth-service
    version: v3.0.0
spec:
  replicas: 3
  selector:
    matchLabels:
      app: auth-service
  template:
    metadata:
      labels:
        app: auth-service
        version: v3.0.0
    spec:
      containers:
      - name: auth-service
        image: techcorp/auth-service:3.0.0
        ports:
        - containerPort: 3000
        env:
        - name: VERSION
          value: "3.0.0"
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
---
apiVersion: v1
kind: Service
metadata:
  name: auth-service
spec:
  selector:
    app: auth-service
  ports:
  - port: 80
    targetPort: 3000
  type: ClusterIP
```

### 2.2 GitHub Actions for Service

**`.github/workflows/release.yml`** (Auth Service):
```yaml
name: Release Auth Service

on:
  push:
    tags:
      - 'v*'

env:
  REGISTRY: ghcr.io
  IMAGE_NAME: techcorp/auth-service

jobs:
  quality-gates:
    runs-on: ubuntu-latest
    outputs:
      version: ${{ steps.version.outputs.version }}
    steps:
    - uses: actions/checkout@v4
    
    - name: Extract version
      id: version
      run: echo "version=${GITHUB_REF#refs/tags/v}" >> $GITHUB_OUTPUT
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run unit tests
      run: npm test -- --coverage --passWithNoTests
    
    - name: Run integration tests
      run: npm run test:integration
    
    - name: Run linting
      run: npm run lint
    
    - name: Security audit
      run: npm audit --audit-level high
    
    - name: Upload coverage
      uses: codecov/codecov-action@v3

  build-and-push:
    needs: quality-gates
    runs-on: ubuntu-latest
    outputs:
      image-digest: ${{ steps.build.outputs.digest }}
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Docker Buildx
      uses: docker/setup-buildx-action@v3
    
    - name: Login to Registry
      uses: docker/login-action@v3
      with:
        registry: ${{ env.REGISTRY }}
        username: ${{ github.actor }}
        password: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Build and push
      id: build
      uses: docker/build-push-action@v5
      with:
        context: .
        push: true
        tags: |
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ needs.quality-gates.outputs.version }}
          ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:latest
        cache-from: type=gha
        cache-to: type=gha,mode=max

  deploy-staging:
    needs: [quality-gates, build-and-push]
    runs-on: ubuntu-latest
    environment: staging
    steps:
    - uses: actions/checkout@v4
    
    - name: Deploy to staging
      run: |
        echo "Deploying ${{ env.IMAGE_NAME }}:${{ needs.quality-gates.outputs.version }} to staging"
        # kubectl apply -f k8s/ --namespace=staging
    
    - name: Run smoke tests
      run: |
        echo "Running smoke tests against staging"
        # npm run test:smoke -- --env=staging

  security-scan:
    needs: build-and-push
    runs-on: ubuntu-latest
    steps:
    - name: Scan image
      uses: aquasecurity/trivy-action@master
      with:
        image-ref: '${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:${{ needs.quality-gates.outputs.version }}'
        format: 'sarif'
        output: 'trivy-results.sarif'
    
    - name: Upload scan results
      uses: github/codeql-action/upload-sarif@v3
      with:
        sarif_file: 'trivy-results.sarif'

  notify-orchestrator:
    needs: [quality-gates, build-and-push, deploy-staging, security-scan]
    runs-on: ubuntu-latest
    steps:
    - name: Notify release orchestrator
      run: |
        curl -X POST ${{ secrets.ORCHESTRATOR_WEBHOOK_URL }} \
          -H "Content-Type: application/json" \
          -d '{
            "service": "auth-service",
            "version": "${{ needs.quality-gates.outputs.version }}",
            "status": "ready",
            "image_digest": "${{ needs.build-and-push.outputs.image-digest }}"
          }'
```

## Parte 3: Advanced Release Pipeline

### 3.1 GitHub Actions Orchestrator Workflow

**`.github/workflows/coordinate-release.yml`** (Orchestrator):
```yaml
name: Coordinate Enterprise Release

on:
  workflow_dispatch:
    inputs:
      release_version:
        description: 'Release version (e.g., 3.0.0)'
        required: true
        type: string
      environment:
        description: 'Target environment'
        required: true
        type: choice
        options:
        - staging
        - canary
        - production
      force_deployment:
        description: 'Force deployment (skip some checks)'
        required: false
        type: boolean
        default: false

env:
  RELEASE_VERSION: ${{ github.event.inputs.release_version }}
  TARGET_ENV: ${{ github.event.inputs.environment }}

jobs:
  validate-release:
    runs-on: ubuntu-latest
    outputs:
      services-ready: ${{ steps.check.outputs.ready }}
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm install
    
    - name: Validate dependencies
      run: node scripts/orchestrator.js validate
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Check service readiness
      id: check
      run: |
        READY=$(node scripts/check-service-readiness.js)
        echo "ready=$READY" >> $GITHUB_OUTPUT
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  run-quality-gates:
    needs: validate-release
    runs-on: ubuntu-latest
    if: needs.validate-release.outputs.services-ready == 'true'
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm install
    
    - name: Run quality gates
      run: node scripts/orchestrator.js quality-gates
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  coordinate-deployment:
    needs: [validate-release, run-quality-gates]
    runs-on: ubuntu-latest
    environment: ${{ github.event.inputs.environment }}
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm install
    
    - name: Start coordinated release
      run: node scripts/orchestrator.js release
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        ENVIRONMENT: ${{ env.TARGET_ENV }}
    
    - name: Upload release report
      uses: actions/upload-artifact@v4
      with:
        name: release-report-${{ env.RELEASE_VERSION }}
        path: release-report.json

  post-deployment-monitoring:
    needs: coordinate-deployment
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    
    - name: Monitor deployment health
      run: |
        echo "Monitoring deployment for 30 minutes..."
        node scripts/monitor-deployment.js --duration=30m
      env:
        MONITORING_WEBHOOK: ${{ secrets.MONITORING_WEBHOOK }}
    
    - name: Generate health report
      run: |
        node scripts/generate-health-report.js > health-report.json
    
    - name: Upload health report
      uses: actions/upload-artifact@v4
      with:
        name: health-report-${{ env.RELEASE_VERSION }}
        path: health-report.json

  notify-stakeholders:
    needs: [coordinate-deployment, post-deployment-monitoring]
    runs-on: ubuntu-latest
    if: always()
    steps:
    - name: Notify Slack
      uses: 8398a7/action-slack@v3
      with:
        status: ${{ job.status }}
        text: |
          🚀 Release ${{ env.RELEASE_VERSION }} to ${{ env.TARGET_ENV }}
          Status: ${{ job.status }}
          Duration: ${{ needs.coordinate-deployment.outputs.duration }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
    
    - name: Create GitHub Release
      if: success() && github.event.inputs.environment == 'production'
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      with:
        tag_name: v${{ env.RELEASE_VERSION }}
        release_name: Release ${{ env.RELEASE_VERSION }}
        body: |
          ## 🚀 TechCorp Platform v${{ env.RELEASE_VERSION }}
          
          ### 🎯 What's New
          - Enhanced payment processing system
          - Improved security features
          - Performance optimizations
          - Breaking API changes with backward compatibility
          
          ### 📦 Deployed Services
          - auth-service v${{ env.RELEASE_VERSION }}
          - payment-service v${{ env.RELEASE_VERSION }}
          - inventory-service v${{ env.RELEASE_VERSION }}
          - order-service v${{ env.RELEASE_VERSION }}
          - notification-service v${{ env.RELEASE_VERSION }}
          - user-service v${{ env.RELEASE_VERSION }}
          - shipping-service v${{ env.RELEASE_VERSION }}
          - analytics-service v${{ env.RELEASE_VERSION }}
          
          ### 📱 Applications
          - Mobile iOS v${{ env.RELEASE_VERSION }}
          - Mobile Android v${{ env.RELEASE_VERSION }}
          - Web Application v${{ env.RELEASE_VERSION }}
          - Desktop Application v${{ env.RELEASE_VERSION }}
          
          ### 🔗 Links
          - [Release Report](./release-report.json)
          - [Health Monitoring](./health-report.json)
          - [Migration Guide](./docs/migration-v3.md)
        draft: false
        prerelease: false
```

### 3.2 Monitoring and Health Checks

**`scripts/monitor-deployment.js`**:
```javascript
const https = require('https');
const fs = require('fs');

class DeploymentMonitor {
  constructor() {
    this.metrics = {
      error_rates: [],
      response_times: [],
      throughput: [],
      availability: []
    };
    this.thresholds = {
      error_rate: 1.0, // 1%
      response_time: 500, // 500ms
      availability: 99.9 // 99.9%
    };
  }

  async monitorForDuration(duration) {
    const durationMs = this.parseDuration(duration);
    const interval = 60000; // Check every minute
    const checks = Math.floor(durationMs / interval);
    
    console.log(`Starting ${checks} health checks over ${duration}...`);
    
    for (let i = 0; i < checks; i++) {
      try {
        await this.performHealthCheck();
        await new Promise(resolve => setTimeout(resolve, interval));
      } catch (error) {
        console.error(`Health check ${i + 1} failed:`, error.message);
        
        if (this.shouldTriggerRollback()) {
          console.error('🚨 Critical issues detected, triggering rollback!');
          await this.triggerEmergencyRollback();
          throw new Error('Emergency rollback initiated');
        }
      }
    }
    
    console.log('✅ Monitoring completed successfully');
    this.generateReport();
  }

  async performHealthCheck() {
    const services = [
      'auth-service',
      'payment-service',
      'order-service',
      'inventory-service'
    ];
    
    const results = await Promise.all(
      services.map(service => this.checkServiceHealth(service))
    );
    
    const avgErrorRate = results.reduce((sum, r) => sum + r.errorRate, 0) / results.length;
    const avgResponseTime = results.reduce((sum, r) => sum + r.responseTime, 0) / results.length;
    const avgThroughput = results.reduce((sum, r) => sum + r.throughput, 0) / results.length;
    const availability = results.filter(r => r.healthy).length / results.length * 100;
    
    this.metrics.error_rates.push(avgErrorRate);
    this.metrics.response_times.push(avgResponseTime);
    this.metrics.throughput.push(avgThroughput);
    this.metrics.availability.push(availability);
    
    console.log(`Health check: Error Rate: ${avgErrorRate}%, Response Time: ${avgResponseTime}ms, Availability: ${availability}%`);
  }

  async checkServiceHealth(service) {
    // Simulate health check with some realistic variance
    const baseErrorRate = Math.random() * 0.5; // 0-0.5%
    const baseResponseTime = 200 + Math.random() * 100; // 200-300ms
    const baseThroughput = 1000 + Math.random() * 500; // 1000-1500 req/min
    const healthy = Math.random() > 0.01; // 99% uptime
    
    return {
      service,
      errorRate: baseErrorRate,
      responseTime: baseResponseTime,
      throughput: baseThroughput,
      healthy
    };
  }

  shouldTriggerRollback() {
    const recentMetrics = this.metrics.error_rates.slice(-5); // Last 5 checks
    const avgErrorRate = recentMetrics.reduce((sum, rate) => sum + rate, 0) / recentMetrics.length;
    
    return avgErrorRate > this.thresholds.error_rate;
  }

  async triggerEmergencyRollback() {
    console.log('🔄 Initiating emergency rollback...');
    
    // Call rollback webhook
    const rollbackData = {
      trigger: 'automated',
      reason: 'health_check_failure',
      timestamp: new Date().toISOString(),
      metrics: this.metrics
    };
    
    // In real implementation, this would call the orchestrator's rollback endpoint
    console.log('Rollback data:', rollbackData);
  }

  parseDuration(duration) {
    const match = duration.match(/^(\d+)([mh])$/);
    if (!match) throw new Error('Invalid duration format');
    
    const value = parseInt(match[1]);
    const unit = match[2];
    
    return unit === 'm' ? value * 60 * 1000 : value * 60 * 60 * 1000;
  }

  generateReport() {
    const report = {
      summary: {
        total_checks: this.metrics.error_rates.length,
        avg_error_rate: this.average(this.metrics.error_rates),
        avg_response_time: this.average(this.metrics.response_times),
        avg_throughput: this.average(this.metrics.throughput),
        avg_availability: this.average(this.metrics.availability)
      },
      thresholds: this.thresholds,
      status: this.shouldTriggerRollback() ? 'UNHEALTHY' : 'HEALTHY',
      details: this.metrics
    };
    
    fs.writeFileSync('health-report.json', JSON.stringify(report, null, 2));
    console.log('📊 Health report saved to health-report.json');
  }

  average(array) {
    return array.reduce((sum, val) => sum + val, 0) / array.length;
  }
}

// CLI
async function main() {
  const duration = process.argv[2] || '30m';
  const monitor = new DeploymentMonitor();
  
  try {
    await monitor.monitorForDuration(duration);
  } catch (error) {
    console.error('Monitoring failed:', error.message);
    process.exit(1);
  }
}

if (require.main === module) {
  main();
}

module.exports = DeploymentMonitor;
```

## Parte 4: Documentation e Release Notes

### 4.1 Migration Guide

**`docs/migration-v3.md`**:
```markdown
# Migration Guide v2.x → v3.0

## 🚨 Breaking Changes

### Authentication Service
- JWT token structure changed
- New required scopes for API access
- Deprecated `/auth/login` endpoint (use `/auth/authenticate`)

### Payment Service
- Payment webhook payload format updated
- New payment methods (Apple Pay, Google Pay)
- Deprecated legacy credit card tokenization

### API Changes
- All endpoints now require API version header
- Rate limiting implemented (1000 req/hour for free tier)
- New error response format

## 📋 Migration Checklist

### For Frontend Applications
- [ ] Update authentication flow
- [ ] Update payment integration
- [ ] Add API version headers
- [ ] Handle new error responses
- [ ] Test with new rate limits

### For Mobile Applications
- [ ] Update SDK dependencies
- [ ] Test new authentication
- [ ] Update payment flows
- [ ] Test offline capabilities

### For Backend Services
- [ ] Update service dependencies
- [ ] Implement new authentication
- [ ] Update payment webhook handlers
- [ ] Add monitoring for new endpoints

## 🔧 Code Examples

### Authentication (Before)
```javascript
// v2.x
const response = await fetch('/auth/login', {
  method: 'POST',
  body: JSON.stringify({ username, password })
});
```

### Authentication (After)
```javascript
// v3.x
const response = await fetch('/auth/authenticate', {
  method: 'POST',
  headers: {
    'API-Version': '3.0',
    'Content-Type': 'application/json'
  },
  body: JSON.stringify({ 
    username, 
    password,
    scope: ['read:profile', 'write:orders']
  })
});
```

## ⏰ Timeline
- **Preparation Phase**: 2 weeks before release
- **Migration Window**: 4 weeks after release
- **Deprecation**: 12 weeks after release
- **Removal**: 24 weeks after release
```

### 4.2 Release Notes Template

**`templates/release-notes.md`**:
```markdown
# 🚀 TechCorp Platform v{{VERSION}}

**Release Date**: {{DATE}}  
**Codename**: {{CODENAME}}

## 🎯 Highlights

{{HIGHLIGHTS}}

## 📦 What's New

### 🔐 Enhanced Security
- Multi-factor authentication support
- Advanced threat detection
- Improved API security

### 💳 Payment Innovations
- New payment methods (Apple Pay, Google Pay)
- Faster checkout experience
- Enhanced fraud detection

### 📈 Performance Improvements
- 40% faster page load times
- Optimized database queries
- Improved caching strategy

### 🛠️ Developer Experience
- New debugging tools
- Enhanced API documentation
- Improved error messages

## 🔧 Technical Details

### Microservices Updated
{{SERVICES_LIST}}

### Applications Updated  
{{APPLICATIONS_LIST}}

### Infrastructure Changes
- Kubernetes v1.28 upgrade
- New monitoring dashboards
- Enhanced logging

## 🚨 Breaking Changes

{{BREAKING_CHANGES}}

## 📋 Migration Guide

See our comprehensive [Migration Guide](./docs/migration-v{{VERSION}}.md) for detailed upgrade instructions.

## 🐛 Bug Fixes

{{BUG_FIXES}}

## 🙏 Acknowledgments

Special thanks to our amazing team and community contributors who made this release possible.

## 📞 Support

- [Documentation](https://docs.techcorp.com)
- [Community Forum](https://community.techcorp.com)
- [Support Portal](https://support.techcorp.com)
```

## Parte 5: Testing e Validation

### 5.1 Execute Release Orchestration

```bash
# Go to orchestrator directory
cd orchestrator

# Install dependencies
npm install

# Set environment variables
export GITHUB_TOKEN="your_github_token"

# Validate dependencies
node scripts/orchestrator.js validate

# Run quality gates
node scripts/orchestrator.js quality-gates

# Execute coordinated release
node scripts/orchestrator.js release
```

### 5.2 Verify Release Process

```bash
# Check orchestrator state
cat release-report.json

# Monitor deployment health
node scripts/monitor-deployment.js 5m

# View health report
cat health-report.json

# Verify service versions
git tag --list "v3.0.0*"
```

### 5.3 Simulate Rollback Scenario

```bash
# Force a failure scenario
export SIMULATE_FAILURE=true

# Run release (should trigger rollback)
node scripts/orchestrator.js release

# Check rollback report
cat rollback-report.json
```

## Parte 6: Advanced Features

### 6.1 Multi-Region Deployment

**`config/regions.yaml`**:
```yaml
regions:
  us-east-1:
    primary: true
    canary_percentage: 10
    services: ["auth-service", "payment-service", "order-service"]
  
  us-west-2:
    primary: false
    canary_percentage: 5
    services: ["auth-service", "payment-service", "order-service"]
  
  eu-central-1:
    primary: false
    canary_percentage: 5
    services: ["auth-service", "payment-service"]
    
  ap-southeast-1:
    primary: false
    canary_percentage: 3
    services: ["auth-service"]
```

### 6.2 Feature Flag Integration

**`scripts/feature-flags.js`**:
```javascript
class FeatureFlagManager {
  constructor() {
    this.flags = {
      'new-payment-flow': { enabled: false, rollout: 0 },
      'enhanced-auth': { enabled: false, rollout: 0 },
      'analytics-v2': { enabled: false, rollout: 0 }
    };
  }
  
  async enableForRelease(version) {
    if (version === '3.0.0') {
      await this.gradualRollout('new-payment-flow', 100, '30m');
      await this.gradualRollout('enhanced-auth', 100, '45m');
      await this.gradualRollout('analytics-v2', 100, '60m');
    }
  }
  
  async gradualRollout(flag, targetPercentage, duration) {
    console.log(`Rolling out ${flag} to ${targetPercentage}% over ${duration}`);
    // Implementation for gradual feature rollout
  }
}
```

## ✅ Validation Checklist

### Setup Verification
- [ ] All repositories created and configured
- [ ] Orchestrator dependencies installed
- [ ] GitHub Actions workflows configured
- [ ] Service health checks implemented

### Release Process
- [ ] Dependency validation working
- [ ] Quality gates passing
- [ ] Coordinated deployment successful
- [ ] Health monitoring active
- [ ] Rollback capability tested

### Documentation
- [ ] Migration guide created
- [ ] Release notes generated
- [ ] API documentation updated
- [ ] Monitoring dashboards configured

### Advanced Features
- [ ] Multi-region deployment configured
- [ ] Feature flags integrated
- [ ] Security scanning implemented
- [ ] Performance monitoring active

## 🏆 Risultati Attesi

Completando questo esercizio avrai implementato:

1. **Enterprise Release Orchestration**
   - Coordinamento multi-repository
   - Gestione dipendenze complesse
   - Quality gates automatizzati

2. **Advanced Deployment Strategies**
   - Blue-green deployment
   - Canary releases
   - Rollback automatico

3. **Comprehensive Monitoring**
   - Health checks real-time
   - Performance monitoring
   - Alert management

4. **Professional Documentation**
   - Migration guides
   - Release notes automatiche
   - Technical documentation

## 📚 Risorse Aggiuntive

- [GitOps Best Practices](https://docs.github.com/en/actions/deployment/deploying-with-github-actions)
- [Kubernetes Deployment Strategies](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)
- [Microservices Release Patterns](https://microservices.io/patterns/deployment/)
- [Site Reliability Engineering](https://sre.google/books/)

## 🎯 Prossimi Passi

1. **Implementa monitoring avanzato** con Prometheus/Grafana
2. **Aggiungi chaos engineering** per testare resilienza
3. **Integra security scanning** nel pipeline
4. **Implementa cost monitoring** per deployments
5. **Aggiungi compliance checks** per enterprise requirements

Questo esercizio rappresenta lo stato dell'arte per enterprise release management, preparandoti per gestire deployments complessi in ambienti di produzione mission-critical.
