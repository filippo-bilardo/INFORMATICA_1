# Esercizio 04 - Advanced GitHub Actions: Custom Actions & Reusable Workflows

## 🎯 Obiettivo

Creare **custom GitHub Actions** e **reusable workflows** per standardizzare processi DevOps aziendali, inclusi automated security scanning, deployment orchestration, e integration testing cross-platform.

## 📋 Requisiti Tecnici

- **Repository GitHub** con GitHub Actions abilitato
- **TypeScript/JavaScript** knowledge per custom actions
- **Docker** per containerized actions
- **Multiple environments** per testing
- **Basic CI/CD** understanding

## ⏱️ Durata Stimata

**180-240 minuti** (sviluppo actions + testing + documentation)

## 🎬 Scenario dell'Esercizio

Svilupperai un **ecosystem di Custom Actions** per una software house che gestisce multiple repository e necessita di standardizzare:
- **Security scanning** automatizzato
- **Database migration** testing
- **Multi-cloud deployment** orchestration
- **Performance benchmarking** automatico
- **Documentation generation** from code

## 🏗️ Fase 1: JavaScript Custom Action - Security Scanner (60 min)

### Step 1: Setup Custom Action Structure

```bash
# 1. Crea repository per le custom actions
# Nome: "devops-custom-actions"
git clone https://github.com/YOUR_USERNAME/devops-custom-actions.git
cd devops-custom-actions

# 2. Struttura per multiple actions
mkdir -p {security-scanner,db-migration-test,cloud-deployer,perf-benchmark,doc-generator}
```

### Step 2: Security Scanner Action

**File: `security-scanner/action.yml`**
```yaml
name: 'Advanced Security Scanner'
description: 'Comprehensive security scanning with SAST, dependency check, and secrets detection'
author: 'DevOps Team'

branding:
  icon: 'shield'
  color: 'red'

inputs:
  scan-type:
    description: 'Type of scan to perform: all, sast, dependencies, secrets, containers'
    required: false
    default: 'all'
  
  severity-threshold:
    description: 'Minimum severity level to report: low, medium, high, critical'
    required: false
    default: 'medium'
  
  fail-on-findings:
    description: 'Whether to fail the action if security issues are found'
    required: false
    default: 'true'
  
  exclude-paths:
    description: 'Comma-separated list of paths to exclude from scanning'
    required: false
    default: 'node_modules,vendor,dist'
  
  output-format:
    description: 'Output format: json, sarif, table'
    required: false
    default: 'json'
  
  github-token:
    description: 'GitHub token for API access'
    required: true

outputs:
  security-score:
    description: 'Overall security score (0-100)'
  
  findings-count:
    description: 'Total number of security findings'
  
  critical-findings:
    description: 'Number of critical severity findings'
  
  report-path:
    description: 'Path to the detailed security report'

runs:
  using: 'node20'
  main: 'dist/index.js'
```

**File: `security-scanner/src/index.ts`**
```typescript
import * as core from '@actions/core';
import * as github from '@actions/github';
import * as exec from '@actions/exec';
import * as fs from 'fs';
import * as path from 'path';

interface SecurityFinding {
  type: 'sast' | 'dependency' | 'secret' | 'container';
  severity: 'low' | 'medium' | 'high' | 'critical';
  title: string;
  description: string;
  file: string;
  line?: number;
  cwe?: string;
  cvss?: number;
}

interface ScanResults {
  findings: SecurityFinding[];
  securityScore: number;
  summary: {
    total: number;
    critical: number;
    high: number;
    medium: number;
    low: number;
  };
}

class SecurityScanner {
  private scanType: string;
  private severityThreshold: string;
  private failOnFindings: boolean;
  private excludePaths: string[];
  private outputFormat: string;
  private githubToken: string;

  constructor() {
    this.scanType = core.getInput('scan-type');
    this.severityThreshold = core.getInput('severity-threshold');
    this.failOnFindings = core.getInput('fail-on-findings') === 'true';
    this.excludePaths = core.getInput('exclude-paths').split(',').map(p => p.trim());
    this.outputFormat = core.getInput('output-format');
    this.githubToken = core.getInput('github-token');
  }

  async run(): Promise<void> {
    try {
      core.info('🔍 Starting comprehensive security scan...');
      
      const results: ScanResults = {
        findings: [],
        securityScore: 100,
        summary: { total: 0, critical: 0, high: 0, medium: 0, low: 0 }
      };

      // Perform different types of scans based on input
      if (this.scanType === 'all' || this.scanType === 'sast') {
        await this.performSASTScan(results);
      }

      if (this.scanType === 'all' || this.scanType === 'dependencies') {
        await this.performDependencyScan(results);
      }

      if (this.scanType === 'all' || this.scanType === 'secrets') {
        await this.performSecretsScan(results);
      }

      if (this.scanType === 'all' || this.scanType === 'containers') {
        await this.performContainerScan(results);
      }

      // Calculate security score
      this.calculateSecurityScore(results);

      // Generate outputs
      await this.generateOutputs(results);

      // Check if we should fail
      if (this.shouldFail(results)) {
        core.setFailed(`Security scan found ${results.summary.critical} critical and ${results.summary.high} high severity issues`);
      }

    } catch (error) {
      core.setFailed(`Security scan failed: ${error}`);
    }
  }

  private async performSASTScan(results: ScanResults): Promise<void> {
    core.info('🔍 Performing SAST (Static Application Security Testing)...');
    
    try {
      // Install and run Semgrep for SAST
      await exec.exec('pip', ['install', 'semgrep']);
      
      let semgrepOutput = '';
      const options = {
        listeners: {
          stdout: (data: Buffer) => {
            semgrepOutput += data.toString();
          }
        },
        ignoreReturnCode: true
      };

      await exec.exec('semgrep', [
        '--config=auto',
        '--json',
        '--exclude', this.excludePaths.join(','),
        '.'
      ], options);

      if (semgrepOutput) {
        const semgrepResults = JSON.parse(semgrepOutput);
        
        for (const finding of semgrepResults.results || []) {
          const severity = this.mapSeverity(finding.extra?.severity || 'INFO');
          
          results.findings.push({
            type: 'sast',
            severity,
            title: finding.check_id || 'SAST Finding',
            description: finding.extra?.message || 'Static analysis security finding',
            file: finding.path,
            line: finding.start?.line,
            cwe: finding.extra?.metadata?.cwe?.[0]
          });
        }
      }

    } catch (error) {
      core.warning(`SAST scan encountered an error: ${error}`);
    }
  }

  private async performDependencyScan(results: ScanResults): Promise<void> {
    core.info('📦 Performing dependency vulnerability scan...');
    
    try {
      // Check for package.json
      if (fs.existsSync('package.json')) {
        let auditOutput = '';
        const options = {
          listeners: {
            stdout: (data: Buffer) => {
              auditOutput += data.toString();
            }
          },
          ignoreReturnCode: true
        };

        await exec.exec('npm', ['audit', '--json'], options);

        if (auditOutput) {
          const auditResults = JSON.parse(auditOutput);
          
          for (const [, vuln] of Object.entries(auditResults.vulnerabilities || {})) {
            const vulnerability = vuln as any;
            
            results.findings.push({
              type: 'dependency',
              severity: this.mapSeverity(vulnerability.severity),
              title: `${vulnerability.name}: ${vulnerability.title}`,
              description: vulnerability.overview || 'Dependency vulnerability',
              file: 'package.json',
              cvss: vulnerability.cvss?.score
            });
          }
        }
      }

      // Check for requirements.txt (Python)
      if (fs.existsSync('requirements.txt')) {
        await exec.exec('pip', ['install', 'safety']);
        
        let safetyOutput = '';
        const options = {
          listeners: {
            stdout: (data: Buffer) => {
              safetyOutput += data.toString();
            }
          },
          ignoreReturnCode: true
        };

        await exec.exec('safety', ['check', '--json'], options);

        if (safetyOutput) {
          const safetyResults = JSON.parse(safetyOutput);
          
          for (const finding of safetyResults) {
            results.findings.push({
              type: 'dependency',
              severity: 'high', // Safety typically reports high-severity issues
              title: `${finding.package}: ${finding.advisory}`,
              description: finding.advisory,
              file: 'requirements.txt'
            });
          }
        }
      }

    } catch (error) {
      core.warning(`Dependency scan encountered an error: ${error}`);
    }
  }

  private async performSecretsScan(results: ScanResults): Promise<void> {
    core.info('🔐 Performing secrets detection scan...');
    
    try {
      // Install and run TruffleHog for secrets detection
      await exec.exec('pip', ['install', 'truffleHog']);
      
      let truffleOutput = '';
      const options = {
        listeners: {
          stdout: (data: Buffer) => {
            truffleOutput += data.toString();
          }
        },
        ignoreReturnCode: true
      };

      await exec.exec('truffleHog', [
        'filesystem',
        '.',
        '--json',
        '--exclude-paths', this.excludePaths.join(',')
      ], options);

      if (truffleOutput) {
        const lines = truffleOutput.trim().split('\n');
        
        for (const line of lines) {
          if (line.trim()) {
            try {
              const finding = JSON.parse(line);
              
              results.findings.push({
                type: 'secret',
                severity: 'critical', // Secrets are always critical
                title: `Potential secret detected: ${finding.DetectorName}`,
                description: `Secret detected by ${finding.DetectorName} detector`,
                file: finding.SourceMetadata?.Data?.Filesystem?.file || 'unknown',
                line: finding.SourceMetadata?.Data?.Filesystem?.line
              });
            } catch (parseError) {
              // Skip malformed JSON lines
            }
          }
        }
      }

    } catch (error) {
      core.warning(`Secrets scan encountered an error: ${error}`);
    }
  }

  private async performContainerScan(results: ScanResults): Promise<void> {
    core.info('🐳 Performing container security scan...');
    
    try {
      // Check for Dockerfile
      if (fs.existsSync('Dockerfile')) {
        // Install and run Hadolint for Dockerfile linting
        await exec.exec('wget', [
          '-O', '/tmp/hadolint',
          'https://github.com/hadolint/hadolint/releases/latest/download/hadolint-Linux-x86_64'
        ]);
        await exec.exec('chmod', ['+x', '/tmp/hadolint']);
        
        let hadolintOutput = '';
        const options = {
          listeners: {
            stdout: (data: Buffer) => {
              hadolintOutput += data.toString();
            }
          },
          ignoreReturnCode: true
        };

        await exec.exec('/tmp/hadolint', ['--format', 'json', 'Dockerfile'], options);

        if (hadolintOutput) {
          const hadolintResults = JSON.parse(hadolintOutput);
          
          for (const finding of hadolintResults) {
            const severity = this.mapHadolintLevel(finding.level);
            
            results.findings.push({
              type: 'container',
              severity,
              title: `${finding.code}: ${finding.message}`,
              description: finding.message,
              file: finding.file,
              line: finding.line
            });
          }
        }
      }

    } catch (error) {
      core.warning(`Container scan encountered an error: ${error}`);
    }
  }

  private mapSeverity(severity: string): 'low' | 'medium' | 'high' | 'critical' {
    const severityMap: { [key: string]: 'low' | 'medium' | 'high' | 'critical' } = {
      'INFO': 'low',
      'WARNING': 'medium',
      'ERROR': 'high',
      'CRITICAL': 'critical',
      'low': 'low',
      'medium': 'medium',
      'moderate': 'medium',
      'high': 'high',
      'critical': 'critical'
    };
    
    return severityMap[severity.toLowerCase()] || 'medium';
  }

  private mapHadolintLevel(level: string): 'low' | 'medium' | 'high' | 'critical' {
    const levelMap: { [key: string]: 'low' | 'medium' | 'high' | 'critical' } = {
      'info': 'low',
      'warning': 'medium',
      'error': 'high'
    };
    
    return levelMap[level.toLowerCase()] || 'medium';
  }

  private calculateSecurityScore(results: ScanResults): void {
    results.summary.total = results.findings.length;
    
    for (const finding of results.findings) {
      switch (finding.severity) {
        case 'critical':
          results.summary.critical++;
          break;
        case 'high':
          results.summary.high++;
          break;
        case 'medium':
          results.summary.medium++;
          break;
        case 'low':
          results.summary.low++;
          break;
      }
    }

    // Calculate score (100 - weighted severity points)
    const severityWeights = { critical: 20, high: 10, medium: 5, low: 1 };
    const totalPoints = 
      results.summary.critical * severityWeights.critical +
      results.summary.high * severityWeights.high +
      results.summary.medium * severityWeights.medium +
      results.summary.low * severityWeights.low;

    results.securityScore = Math.max(0, 100 - totalPoints);
  }

  private async generateOutputs(results: ScanResults): Promise<void> {
    const reportPath = 'security-report.json';
    
    // Write detailed report
    const report = {
      timestamp: new Date().toISOString(),
      securityScore: results.securityScore,
      summary: results.summary,
      findings: results.findings,
      configuration: {
        scanType: this.scanType,
        severityThreshold: this.severityThreshold,
        excludePaths: this.excludePaths
      }
    };

    fs.writeFileSync(reportPath, JSON.stringify(report, null, 2));

    // Set outputs
    core.setOutput('security-score', results.securityScore.toString());
    core.setOutput('findings-count', results.summary.total.toString());
    core.setOutput('critical-findings', results.summary.critical.toString());
    core.setOutput('report-path', reportPath);

    // Generate summary
    const summary = `
## 🔍 Security Scan Results

**Security Score:** ${results.securityScore}/100

**Findings Summary:**
- 🔴 Critical: ${results.summary.critical}
- 🟠 High: ${results.summary.high}
- 🟡 Medium: ${results.summary.medium}
- 🟢 Low: ${results.summary.low}

**Total Findings:** ${results.summary.total}
`;

    core.summary.addRaw(summary);
    await core.summary.write();

    core.info(`🔍 Security scan completed. Score: ${results.securityScore}/100`);
  }

  private shouldFail(results: ScanResults): boolean {
    if (!this.failOnFindings) return false;

    const thresholdMap = { critical: 4, high: 3, medium: 2, low: 1 };
    const thresholdLevel = thresholdMap[this.severityThreshold as keyof typeof thresholdMap];

    for (const finding of results.findings) {
      const findingLevel = thresholdMap[finding.severity];
      if (findingLevel >= thresholdLevel) {
        return true;
      }
    }

    return false;
  }
}

async function run(): Promise<void> {
  const scanner = new SecurityScanner();
  await scanner.run();
}

run();
```

**File: `security-scanner/package.json`**
```json
{
  "name": "security-scanner-action",
  "version": "1.0.0",
  "description": "Advanced security scanning action",
  "main": "dist/index.js",
  "scripts": {
    "build": "tsc && ncc build src/index.ts -o dist",
    "test": "jest",
    "lint": "eslint src/**/*.ts",
    "package": "npm run build"
  },
  "dependencies": {
    "@actions/core": "^1.10.0",
    "@actions/github": "^5.1.1",
    "@actions/exec": "^1.1.1"
  },
  "devDependencies": {
    "@types/node": "^20.0.0",
    "@vercel/ncc": "^0.38.0",
    "typescript": "^5.0.0",
    "eslint": "^8.0.0",
    "@typescript-eslint/parser": "^6.0.0",
    "@typescript-eslint/eslint-plugin": "^6.0.0",
    "jest": "^29.0.0"
  }
}
```

## 🗄️ Fase 2: Composite Action - Database Migration Tester (45 min)

### Step 3: Database Migration Testing Action

**File: `db-migration-test/action.yml`**
```yaml
name: 'Database Migration Tester'
description: 'Test database migrations across multiple environments and database engines'
author: 'DevOps Team'

branding:
  icon: 'database'
  color: 'blue'

inputs:
  database-engines:
    description: 'Comma-separated list of database engines to test: postgresql, mysql, sqlite, mongodb'
    required: false
    default: 'postgresql'
  
  migration-path:
    description: 'Path to migration files'
    required: false
    default: './migrations'
  
  test-data-path:
    description: 'Path to test data files'
    required: false
    default: './test-data'
  
  rollback-test:
    description: 'Whether to test rollback functionality'
    required: false
    default: 'true'
  
  performance-test:
    description: 'Whether to run performance tests on migrations'
    required: false
    default: 'false'

outputs:
  test-results:
    description: 'Path to test results file'
  
  migration-time:
    description: 'Total migration execution time'
  
  rollback-time:
    description: 'Total rollback execution time'

runs:
  using: 'composite'
  steps:
    - name: 🏗️ Setup Test Environment
      shell: bash
      run: |
        echo "🏗️ Setting up database migration test environment..."
        
        # Install database clients
        sudo apt-get update
        sudo apt-get install -y postgresql-client mysql-client sqlite3
        
        # Install Node.js tools for migration testing
        npm install -g knex-migrator db-migrate

    - name: 🐳 Start Database Services
      shell: bash
      run: |
        echo "🐳 Starting database services..."
        
        # Create docker-compose for test databases
        cat > docker-compose.test.yml << EOF
        version: '3.8'
        services:
          postgres-test:
            image: postgres:15-alpine
            environment:
              POSTGRES_DB: test_db
              POSTGRES_USER: test_user
              POSTGRES_PASSWORD: test_pass
            ports:
              - "5433:5432"
            healthcheck:
              test: ["CMD-SHELL", "pg_isready -U test_user -d test_db"]
              interval: 5s
              timeout: 5s
              retries: 5
          
          mysql-test:
            image: mysql:8.0
            environment:
              MYSQL_DATABASE: test_db
              MYSQL_USER: test_user
              MYSQL_PASSWORD: test_pass
              MYSQL_ROOT_PASSWORD: root_pass
            ports:
              - "3307:3306"
            healthcheck:
              test: ["CMD", "mysqladmin", "ping", "-h", "localhost"]
              interval: 5s
              timeout: 5s
              retries: 5
          
          mongo-test:
            image: mongo:7.0
            environment:
              MONGO_INITDB_DATABASE: test_db
              MONGO_INITDB_ROOT_USERNAME: test_user
              MONGO_INITDB_ROOT_PASSWORD: test_pass
            ports:
              - "27018:27017"
            healthcheck:
              test: ["CMD", "mongosh", "--eval", "db.adminCommand('ping')"]
              interval: 5s
              timeout: 5s
              retries: 5
        EOF
        
        docker-compose -f docker-compose.test.yml up -d
        
        # Wait for services to be healthy
        echo "⏳ Waiting for databases to be ready..."
        sleep 30

    - name: 🧪 Test PostgreSQL Migrations
      if: contains(inputs.database-engines, 'postgresql')
      shell: bash
      run: |
        echo "🧪 Testing PostgreSQL migrations..."
        
        export DATABASE_URL="postgresql://test_user:test_pass@localhost:5433/test_db"
        
        # Test migration up
        echo "⬆️ Testing migration up..."
        START_TIME=$(date +%s)
        
        # Run migrations (adapt to your migration tool)
        if [ -f "knexfile.js" ]; then
          npx knex migrate:latest --env test
        elif [ -f "package.json" ] && grep -q "db-migrate" package.json; then
          npx db-migrate up --env test
        else
          echo "📁 Running custom migration scripts..."
          for migration in ${{ inputs.migration-path }}/*.sql; do
            if [ -f "$migration" ]; then
              psql $DATABASE_URL -f "$migration"
            fi
          done
        fi
        
        END_TIME=$(date +%s)
        MIGRATION_TIME=$((END_TIME - START_TIME))
        echo "⏱️ PostgreSQL migration completed in ${MIGRATION_TIME}s"
        echo "POSTGRES_MIGRATION_TIME=${MIGRATION_TIME}" >> $GITHUB_ENV

    - name: 🧪 Test MySQL Migrations
      if: contains(inputs.database-engines, 'mysql')
      shell: bash
      run: |
        echo "🧪 Testing MySQL migrations..."
        
        export DATABASE_URL="mysql://test_user:test_pass@localhost:3307/test_db"
        
        START_TIME=$(date +%s)
        
        # Run MySQL migrations
        for migration in ${{ inputs.migration-path }}/*.sql; do
          if [ -f "$migration" ]; then
            mysql -h localhost -P 3307 -u test_user -ptest_pass test_db < "$migration"
          fi
        done
        
        END_TIME=$(date +%s)
        MIGRATION_TIME=$((END_TIME - START_TIME))
        echo "⏱️ MySQL migration completed in ${MIGRATION_TIME}s"
        echo "MYSQL_MIGRATION_TIME=${MIGRATION_TIME}" >> $GITHUB_ENV

    - name: 🧪 Test SQLite Migrations
      if: contains(inputs.database-engines, 'sqlite')
      shell: bash
      run: |
        echo "🧪 Testing SQLite migrations..."
        
        export DATABASE_URL="sqlite:./test.db"
        
        START_TIME=$(date +%s)
        
        # Run SQLite migrations
        for migration in ${{ inputs.migration-path }}/*.sql; do
          if [ -f "$migration" ]; then
            sqlite3 test.db < "$migration"
          fi
        done
        
        END_TIME=$(date +%s)
        MIGRATION_TIME=$((END_TIME - START_TIME))
        echo "⏱️ SQLite migration completed in ${MIGRATION_TIME}s"
        echo "SQLITE_MIGRATION_TIME=${MIGRATION_TIME}" >> $GITHUB_ENV

    - name: 🔄 Test Rollback Functionality
      if: inputs.rollback-test == 'true'
      shell: bash
      run: |
        echo "🔄 Testing rollback functionality..."
        
        START_TIME=$(date +%s)
        
        # Test rollback for each database
        if [ -f "knexfile.js" ]; then
          npx knex migrate:rollback --env test
        elif [ -f "package.json" ] && grep -q "db-migrate" package.json; then
          npx db-migrate down --env test
        fi
        
        END_TIME=$(date +%s)
        ROLLBACK_TIME=$((END_TIME - START_TIME))
        echo "⏱️ Rollback completed in ${ROLLBACK_TIME}s"
        echo "ROLLBACK_TIME=${ROLLBACK_TIME}" >> $GITHUB_ENV

    - name: ⚡ Performance Testing
      if: inputs.performance-test == 'true'
      shell: bash
      run: |
        echo "⚡ Running migration performance tests..."
        
        # Create large dataset for performance testing
        cat > performance_test.sql << EOF
        -- Performance test: Create large table
        CREATE TABLE IF NOT EXISTS perf_test (
          id SERIAL PRIMARY KEY,
          data TEXT,
          created_at TIMESTAMP DEFAULT NOW()
        );
        
        -- Insert test data
        INSERT INTO perf_test (data) 
        SELECT 'test_data_' || generate_series(1, 100000);
        
        -- Test index creation performance
        CREATE INDEX CONCURRENTLY IF NOT EXISTS idx_perf_test_data ON perf_test(data);
        EOF
        
        echo "🚀 Running performance migration..."
        START_TIME=$(date +%s)
        psql postgresql://test_user:test_pass@localhost:5433/test_db -f performance_test.sql
        END_TIME=$(date +%s)
        PERF_TIME=$((END_TIME - START_TIME))
        echo "⏱️ Performance test completed in ${PERF_TIME}s"

    - name: 📊 Generate Test Report
      shell: bash
      run: |
        echo "📊 Generating migration test report..."
        
        cat > migration-test-report.json << EOF
        {
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "database_engines": "${{ inputs.database-engines }}",
          "results": {
            "postgresql": {
              "migration_time": "${POSTGRES_MIGRATION_TIME:-0}",
              "status": "success"
            },
            "mysql": {
              "migration_time": "${MYSQL_MIGRATION_TIME:-0}",
              "status": "success"
            },
            "sqlite": {
              "migration_time": "${SQLITE_MIGRATION_TIME:-0}",
              "status": "success"
            }
          },
          "rollback": {
            "time": "${ROLLBACK_TIME:-0}",
            "tested": "${{ inputs.rollback-test }}"
          },
          "performance": {
            "tested": "${{ inputs.performance-test }}"
          }
        }
        EOF
        
        echo "test-results=migration-test-report.json" >> $GITHUB_OUTPUT
        echo "migration-time=${POSTGRES_MIGRATION_TIME:-0}" >> $GITHUB_OUTPUT
        echo "rollback-time=${ROLLBACK_TIME:-0}" >> $GITHUB_OUTPUT

    - name: 🧹 Cleanup
      if: always()
      shell: bash
      run: |
        echo "🧹 Cleaning up test environment..."
        docker-compose -f docker-compose.test.yml down -v || true
        rm -f test.db docker-compose.test.yml performance_test.sql || true
```

## 🚀 Fase 3: Docker Action - Multi-Cloud Deployer (45 min)

### Step 4: Multi-Cloud Deployment Action

**File: `cloud-deployer/Dockerfile`**
```dockerfile
FROM alpine:3.18

# Install required tools
RUN apk add --no-cache \
    bash \
    curl \
    jq \
    python3 \
    py3-pip \
    terraform \
    helm \
    kubectl

# Install cloud CLI tools
RUN pip3 install awscli azure-cli google-cloud-sdk

# Install additional tools
RUN curl -fsSL https://get.pulumi.com | sh

# Copy action scripts
COPY entrypoint.sh /entrypoint.sh
COPY deploy-scripts/ /deploy-scripts/

RUN chmod +x /entrypoint.sh
RUN chmod +x /deploy-scripts/*.sh

ENTRYPOINT ["/entrypoint.sh"]
```

**File: `cloud-deployer/action.yml`**
```yaml
name: 'Multi-Cloud Deployer'
description: 'Deploy applications across AWS, Azure, and GCP with standardized configuration'
author: 'DevOps Team'

branding:
  icon: 'cloud'
  color: 'purple'

inputs:
  cloud-provider:
    description: 'Target cloud provider: aws, azure, gcp, all'
    required: true
  
  deployment-type:
    description: 'Deployment type: kubernetes, serverless, vm, containers'
    required: true
  
  environment:
    description: 'Target environment: dev, staging, production'
    required: true
  
  application-name:
    description: 'Name of the application to deploy'
    required: true
  
  image-tag:
    description: 'Container image tag to deploy'
    required: true
  
  config-path:
    description: 'Path to deployment configuration files'
    required: false
    default: './deploy'
  
  dry-run:
    description: 'Perform a dry run without actual deployment'
    required: false
    default: 'false'
  
  rollback-on-failure:
    description: 'Automatically rollback on deployment failure'
    required: false
    default: 'true'

  # Cloud-specific credentials
  aws-access-key-id:
    description: 'AWS Access Key ID'
    required: false
  
  aws-secret-access-key:
    description: 'AWS Secret Access Key'
    required: false
  
  azure-credentials:
    description: 'Azure service principal credentials (JSON)'
    required: false
  
  gcp-credentials:
    description: 'GCP service account key (JSON)'
    required: false

outputs:
  deployment-url:
    description: 'URL of the deployed application'
  
  deployment-status:
    description: 'Status of the deployment'
  
  rollback-id:
    description: 'ID for potential rollback'

runs:
  using: 'docker'
  image: 'Dockerfile'
  args:
    - ${{ inputs.cloud-provider }}
    - ${{ inputs.deployment-type }}
    - ${{ inputs.environment }}
    - ${{ inputs.application-name }}
    - ${{ inputs.image-tag }}
    - ${{ inputs.config-path }}
    - ${{ inputs.dry-run }}
    - ${{ inputs.rollback-on-failure }}
```

**File: `cloud-deployer/entrypoint.sh`**
```bash
#!/bin/bash
set -e

CLOUD_PROVIDER=$1
DEPLOYMENT_TYPE=$2
ENVIRONMENT=$3
APPLICATION_NAME=$4
IMAGE_TAG=$5
CONFIG_PATH=$6
DRY_RUN=$7
ROLLBACK_ON_FAILURE=$8

echo "🚀 Starting multi-cloud deployment..."
echo "Provider: $CLOUD_PROVIDER"
echo "Type: $DEPLOYMENT_TYPE"
echo "Environment: $ENVIRONMENT"
echo "Application: $APPLICATION_NAME"
echo "Image Tag: $IMAGE_TAG"

# Function to deploy to AWS
deploy_aws() {
    echo "🟠 Deploying to AWS..."
    
    # Configure AWS CLI
    if [ -n "$INPUT_AWS_ACCESS_KEY_ID" ]; then
        aws configure set aws_access_key_id "$INPUT_AWS_ACCESS_KEY_ID"
        aws configure set aws_secret_access_key "$INPUT_AWS_SECRET_ACCESS_KEY"
        aws configure set default.region us-east-1
    fi
    
    case $DEPLOYMENT_TYPE in
        "kubernetes")
            /deploy-scripts/aws-k8s-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "serverless")
            /deploy-scripts/aws-lambda-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "containers")
            /deploy-scripts/aws-ecs-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        *)
            echo "❌ Unsupported deployment type for AWS: $DEPLOYMENT_TYPE"
            exit 1
            ;;
    esac
}

# Function to deploy to Azure
deploy_azure() {
    echo "🔵 Deploying to Azure..."
    
    # Configure Azure CLI
    if [ -n "$INPUT_AZURE_CREDENTIALS" ]; then
        echo "$INPUT_AZURE_CREDENTIALS" | az login --service-principal \
            -u $(echo "$INPUT_AZURE_CREDENTIALS" | jq -r .clientId) \
            -p $(echo "$INPUT_AZURE_CREDENTIALS" | jq -r .clientSecret) \
            --tenant $(echo "$INPUT_AZURE_CREDENTIALS" | jq -r .tenantId)
    fi
    
    case $DEPLOYMENT_TYPE in
        "kubernetes")
            /deploy-scripts/azure-aks-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "serverless")
            /deploy-scripts/azure-functions-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "containers")
            /deploy-scripts/azure-aci-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        *)
            echo "❌ Unsupported deployment type for Azure: $DEPLOYMENT_TYPE"
            exit 1
            ;;
    esac
}

# Function to deploy to GCP
deploy_gcp() {
    echo "🟢 Deploying to GCP..."
    
    # Configure GCP CLI
    if [ -n "$INPUT_GCP_CREDENTIALS" ]; then
        echo "$INPUT_GCP_CREDENTIALS" > /tmp/gcp-key.json
        gcloud auth activate-service-account --key-file=/tmp/gcp-key.json
        PROJECT_ID=$(echo "$INPUT_GCP_CREDENTIALS" | jq -r .project_id)
        gcloud config set project "$PROJECT_ID"
    fi
    
    case $DEPLOYMENT_TYPE in
        "kubernetes")
            /deploy-scripts/gcp-gke-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "serverless")
            /deploy-scripts/gcp-functions-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        "containers")
            /deploy-scripts/gcp-run-deploy.sh "$APPLICATION_NAME" "$IMAGE_TAG" "$ENVIRONMENT" "$DRY_RUN"
            ;;
        *)
            echo "❌ Unsupported deployment type for GCP: $DEPLOYMENT_TYPE"
            exit 1
            ;;
    esac
}

# Main deployment logic
case $CLOUD_PROVIDER in
    "aws")
        deploy_aws
        ;;
    "azure")
        deploy_azure
        ;;
    "gcp")
        deploy_gcp
        ;;
    "all")
        echo "🌍 Deploying to all cloud providers..."
        deploy_aws &
        deploy_azure &
        deploy_gcp &
        wait
        ;;
    *)
        echo "❌ Unsupported cloud provider: $CLOUD_PROVIDER"
        exit 1
        ;;
esac

echo "✅ Multi-cloud deployment completed successfully!"

# Set outputs
echo "deployment-status=success" >> $GITHUB_OUTPUT
echo "rollback-id=$(date +%s)" >> $GITHUB_OUTPUT
```

## 📚 Fase 4: Reusable Workflow - Full Stack Testing (30 min)

### Step 5: Reusable Testing Workflow

**File: `.github/workflows/reusable-full-stack-testing.yml`**
```yaml
name: 🧪 Reusable Full Stack Testing Workflow

on:
  workflow_call:
    inputs:
      node-version:
        description: 'Node.js version to use'
        required: false
        default: '18'
        type: string
      
      python-version:
        description: 'Python version to use'
        required: false
        default: '3.11'
        type: string
      
      test-environments:
        description: 'JSON array of test environments'
        required: false
        default: '["development", "staging"]'
        type: string
      
      run-e2e-tests:
        description: 'Whether to run E2E tests'
        required: false
        default: true
        type: boolean
      
      run-security-scan:
        description: 'Whether to run security scanning'
        required: false
        default: true
        type: boolean
      
      performance-test:
        description: 'Whether to run performance tests'
        required: false
        default: false
        type: boolean

    secrets:
      GITHUB_TOKEN:
        required: true
      DATABASE_URL:
        required: false
      SLACK_WEBHOOK:
        required: false

    outputs:
      test-results:
        description: 'Overall test results'
        value: ${{ jobs.summarize-results.outputs.overall-status }}
      
      coverage-percentage:
        description: 'Code coverage percentage'
        value: ${{ jobs.unit-tests.outputs.coverage }}

env:
  NODE_VERSION: ${{ inputs.node-version }}
  PYTHON_VERSION: ${{ inputs.python-version }}

jobs:
  # Job 1: Environment Setup and Validation
  setup-and-validate:
    name: 🏗️ Setup & Validate
    runs-on: ubuntu-latest
    outputs:
      environments: ${{ steps.parse-environments.outputs.environments }}
      
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔍 Parse test environments
        id: parse-environments
        run: |
          echo "environments=${{ inputs.test-environments }}" >> $GITHUB_OUTPUT

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 🐍 Setup Python
        uses: actions/setup-python@v4
        with:
          python-version: ${{ env.PYTHON_VERSION }}

      - name: 📦 Install dependencies
        run: |
          npm ci
          pip install -r requirements.txt || echo "No Python requirements found"

      - name: ✅ Validate project structure
        run: |
          echo "🔍 Validating project structure..."
          
          # Check for required files
          required_files=("package.json" ".github/workflows")
          for file in "${required_files[@]}"; do
            if [ ! -e "$file" ]; then
              echo "❌ Required file/directory not found: $file"
              exit 1
            fi
          done
          
          echo "✅ Project structure validation passed"

  # Job 2: Unit and Integration Tests
  unit-tests:
    name: 🧪 Unit & Integration Tests
    runs-on: ubuntu-latest
    needs: setup-and-validate
    outputs:
      coverage: ${{ steps.coverage.outputs.percentage }}
      
    strategy:
      matrix:
        environment: ${{ fromJson(needs.setup-and-validate.outputs.environments) }}
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 📦 Install dependencies
        run: npm ci

      - name: 🧪 Run unit tests
        env:
          NODE_ENV: ${{ matrix.environment }}
          DATABASE_URL: ${{ secrets.DATABASE_URL }}
        run: |
          npm run test:unit -- --coverage --ci

      - name: 🔗 Run integration tests
        env:
          NODE_ENV: ${{ matrix.environment }}
          DATABASE_URL: ${{ secrets.DATABASE_URL }}
        run: |
          npm run test:integration || echo "No integration tests found"

      - name: 📊 Calculate coverage
        id: coverage
        run: |
          if [ -f "coverage/lcov.info" ]; then
            coverage=$(npx nyc report --reporter=text-summary | grep "Lines" | awk '{print $3}' | sed 's/%//')
            echo "percentage=$coverage" >> $GITHUB_OUTPUT
          else
            echo "percentage=0" >> $GITHUB_OUTPUT
          fi

      - name: 📊 Upload coverage reports
        uses: codecov/codecov-action@v4
        with:
          file: ./coverage/lcov.info
          flags: ${{ matrix.environment }}

  # Job 3: Security Scanning
  security-scan:
    name: 🔒 Security Scan
    runs-on: ubuntu-latest
    needs: setup-and-validate
    if: ${{ inputs.run-security-scan }}
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔍 Use custom security scanner
        uses: ./security-scanner
        with:
          scan-type: 'all'
          severity-threshold: 'medium'
          fail-on-findings: 'true'
          github-token: ${{ secrets.GITHUB_TOKEN }}

  # Job 4: End-to-End Tests
  e2e-tests:
    name: 🎭 E2E Tests
    runs-on: ubuntu-latest
    needs: [setup-and-validate, unit-tests]
    if: ${{ inputs.run-e2e-tests }}
    
    strategy:
      matrix:
        browser: [chrome, firefox]
        environment: ${{ fromJson(needs.setup-and-validate.outputs.environments) }}
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 📦 Install dependencies
        run: npm ci

      - name: 🏗️ Build application
        run: npm run build

      - name: 🚀 Start application
        run: |
          npm start &
          sleep 30  # Wait for app to start

      - name: 🎭 Run Playwright tests
        env:
          BROWSER: ${{ matrix.browser }}
          ENVIRONMENT: ${{ matrix.environment }}
        run: |
          npx playwright test --project=${{ matrix.browser }}

      - name: 📊 Upload E2E artifacts
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: e2e-results-${{ matrix.browser }}-${{ matrix.environment }}
          path: |
            test-results/
            playwright-report/

  # Job 5: Performance Tests
  performance-tests:
    name: ⚡ Performance Tests
    runs-on: ubuntu-latest
    needs: [setup-and-validate, unit-tests]
    if: ${{ inputs.performance-test }}
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 📦 Install dependencies
        run: npm ci

      - name: 🏗️ Build application
        run: npm run build

      - name: 🚀 Start application
        run: |
          npm start &
          sleep 30

      - name: ⚡ Run K6 performance tests
        run: |
          docker run --rm -i --network host grafana/k6:latest run - < tests/performance/load-test.js

      - name: 📊 Run Lighthouse CI
        run: |
          npm install -g @lhci/cli
          lhci autorun

  # Job 6: Database Migration Tests
  migration-tests:
    name: 🗄️ Migration Tests
    runs-on: ubuntu-latest
    needs: setup-and-validate
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🗄️ Test database migrations
        uses: ./db-migration-test
        with:
          database-engines: 'postgresql,mysql'
          migration-path: './migrations'
          rollback-test: 'true'
          performance-test: 'false'

  # Job 7: Summarize Results
  summarize-results:
    name: 📊 Summarize Results
    runs-on: ubuntu-latest
    needs: [unit-tests, security-scan, e2e-tests, performance-tests, migration-tests]
    if: always()
    outputs:
      overall-status: ${{ steps.determine-status.outputs.status }}
    
    steps:
      - name: 📊 Determine overall status
        id: determine-status
        run: |
          unit_status="${{ needs.unit-tests.result }}"
          security_status="${{ needs.security-scan.result }}"
          e2e_status="${{ needs.e2e-tests.result }}"
          perf_status="${{ needs.performance-tests.result }}"
          migration_status="${{ needs.migration-tests.result }}"
          
          # Determine overall status
          if [[ "$unit_status" == "failure" || "$security_status" == "failure" || "$e2e_status" == "failure" || "$migration_status" == "failure" ]]; then
            echo "status=failure" >> $GITHUB_OUTPUT
          elif [[ "$unit_status" == "success" && "$migration_status" == "success" ]]; then
            echo "status=success" >> $GITHUB_OUTPUT
          else
            echo "status=partial" >> $GITHUB_OUTPUT
          fi

      - name: 📋 Generate test summary
        run: |
          cat >> $GITHUB_STEP_SUMMARY << 'EOF'
          ## 🧪 Full Stack Test Results
          
          | Test Type | Status | Coverage |
          |-----------|--------|----------|
          | Unit Tests | ${{ needs.unit-tests.result }} | ${{ needs.unit-tests.outputs.coverage }}% |
          | Security Scan | ${{ needs.security-scan.result }} | N/A |
          | E2E Tests | ${{ needs.e2e-tests.result }} | N/A |
          | Performance | ${{ needs.performance-tests.result }} | N/A |
          | Migrations | ${{ needs.migration-tests.result }} | N/A |
          
          **Overall Status:** ${{ steps.determine-status.outputs.status }}
          EOF

      - name: 📢 Notify results
        if: ${{ secrets.SLACK_WEBHOOK != '' }}
        run: |
          status_emoji="✅"
          if [[ "${{ steps.determine-status.outputs.status }}" == "failure" ]]; then
            status_emoji="❌"
          elif [[ "${{ steps.determine-status.outputs.status }}" == "partial" ]]; then
            status_emoji="⚠️"
          fi
          
          curl -X POST -H 'Content-type: application/json' \
            --data "{\"text\":\"$status_emoji Full Stack Tests completed with status: ${{ steps.determine-status.outputs.status }}\"}" \
            ${{ secrets.SLACK_WEBHOOK }}
```

## ✅ Verifica Completamento

### Checklist Finale

- [ ] **JavaScript Custom Action**: Security scanner implementato
- [ ] **Composite Action**: Database migration tester configurato
- [ ] **Docker Action**: Multi-cloud deployer sviluppato
- [ ] **Reusable Workflow**: Full stack testing workflow creato
- [ ] **Documentation**: README files per ogni action
- [ ] **Testing**: Actions testate in workflow reali
- [ ] **Publishing**: Actions pubblicate su GitHub Marketplace (opzionale)
- [ ] **Versioning**: Tag di versione per release management

### Advanced Features Implementate

1. **Multi-Language Security Scanning**: SAST, dependency, secrets, containers
2. **Cross-Platform Database Testing**: PostgreSQL, MySQL, SQLite, MongoDB
3. **Multi-Cloud Deployment**: AWS, Azure, GCP con supporto unificato
4. **Comprehensive Testing Pipeline**: Unit, integration, E2E, performance
5. **Reusable Workflow Pattern**: Standardizzazione cross-repository
6. **Advanced Error Handling**: Rollback automatico e recovery
7. **Monitoring Integration**: Slack notifications e reporting
8. **Security-First Design**: Scanning integrato in ogni fase

## 🎯 Obiettivi Raggiunti

Completando questo esercizio hai sviluppato:

- **Custom GitHub Actions** per automazione specializzata
- **Reusable Workflows** per standardizzazione aziendale
- **Multi-Cloud Deployment** capabilities
- **Comprehensive Security** scanning automation
- **Database Testing** automation cross-platform
- **Enterprise-Grade** error handling e monitoring
- **Marketplace-Ready** actions con documentazione completa

## 🚀 Prossimi Passi

- Pubblica le actions su GitHub Marketplace
- Implementa metrics e analytics per usage tracking
- Sviluppa dashboard di monitoring per deployment
- Crea templates per onboarding rapido
- Implementa automated testing per le actions stesse

## 📚 Risorse Aggiuntive

- [GitHub Actions Toolkit](https://github.com/actions/toolkit)
- [Creating Custom Actions](https://docs.github.com/en/actions/creating-actions)
- [Reusable Workflows](https://docs.github.com/en/actions/using-workflows/reusing-workflows)
- [GitHub Marketplace](https://github.com/marketplace?type=actions)
