# Esercizio 2: Custom Workflow - Creazione di Workflow Personalizzati

## Obiettivo

Sviluppare workflow GitHub Actions personalizzati per scenari specifici, inclusi workflow riutilizzabili, custom actions, e strategie di automazione avanzate per diversi tipi di progetti.

## Scenario

La tua azienda ha diversi team che sviluppano applicazioni con stack tecnologici differenti. Devi creare un sistema di workflow modulari e riutilizzabili che possano essere facilmente adattati per:

1. **Team Mobile**: App React Native per iOS/Android
2. **Team Backend**: Microservizi Python con FastAPI
3. **Team DevOps**: Infrastructure as Code con Terraform
4. **Team Data**: Pipeline ML con Python e Jupyter

## Architettura del Sistema

### Struttura Repository
```
organization/
├── .github/
│   ├── workflows/
│   │   ├── reusable-ci.yml
│   │   ├── reusable-deploy.yml
│   │   ├── reusable-security.yml
│   │   └── template-generator.yml
│   └── actions/
│       ├── setup-environment/
│       ├── run-tests/
│       ├── security-scan/
│       └── deploy-application/
└── templates/
    ├── mobile-app/
    ├── python-api/
    ├── terraform-infrastructure/
    └── ml-pipeline/
```

## Task 1: Workflow Riutilizzabili

### Istruzioni
Crea workflow riutilizzabili che possono essere chiamati da repository diversi con parametri personalizzabili.

### Soluzione: Base Reusable CI Workflow

```yaml
# .github/workflows/reusable-ci.yml
name: Reusable CI Workflow

on:
  workflow_call:
    inputs:
      # Environment configuration
      node-version:
        description: 'Node.js version to use'
        required: false
        type: string
        default: '18'
      python-version:
        description: 'Python version to use'
        required: false
        type: string
        default: '3.11'
      java-version:
        description: 'Java version to use'
        required: false
        type: string
        default: '17'
      
      # Project configuration
      project-type:
        description: 'Type of project (node, python, java, mobile, terraform)'
        required: true
        type: string
      working-directory:
        description: 'Working directory for the project'
        required: false
        type: string
        default: '.'
      
      # Testing configuration
      run-unit-tests:
        description: 'Run unit tests'
        required: false
        type: boolean
        default: true
      run-integration-tests:
        description: 'Run integration tests'
        required: false
        type: boolean
        default: false
      run-e2e-tests:
        description: 'Run E2E tests'
        required: false
        type: boolean
        default: false
      
      # Security configuration
      run-security-scan:
        description: 'Run security scanning'
        required: false
        type: boolean
        default: true
      run-dependency-check:
        description: 'Check for vulnerable dependencies'
        required: false
        type: boolean
        default: true
      
      # Build configuration
      build-artifacts:
        description: 'Build and upload artifacts'
        required: false
        type: boolean
        default: false
      artifact-name:
        description: 'Name for the build artifact'
        required: false
        type: string
        default: 'build-artifacts'
      
      # Docker configuration
      build-docker:
        description: 'Build Docker image'
        required: false
        type: boolean
        default: false
      docker-file:
        description: 'Path to Dockerfile'
        required: false
        type: string
        default: 'Dockerfile'
      docker-context:
        description: 'Docker build context'
        required: false
        type: string
        default: '.'
      
    secrets:
      # Registry secrets
      DOCKER_USERNAME:
        description: 'Docker registry username'
        required: false
      DOCKER_PASSWORD:
        description: 'Docker registry password'
        required: false
      
      # Cloud secrets
      AWS_ACCESS_KEY_ID:
        description: 'AWS Access Key ID'
        required: false
      AWS_SECRET_ACCESS_KEY:
        description: 'AWS Secret Access Key'
        required: false
      
      # Notification secrets
      SLACK_WEBHOOK:
        description: 'Slack webhook URL'
        required: false
      
      # Security scanning
      SNYK_TOKEN:
        description: 'Snyk token for security scanning'
        required: false
    
    outputs:
      test-results:
        description: 'Test execution results'
        value: ${{ jobs.test.outputs.results }}
      security-results:
        description: 'Security scan results'
        value: ${{ jobs.security.outputs.results }}
      build-version:
        description: 'Build version number'
        value: ${{ jobs.build.outputs.version }}
      docker-image:
        description: 'Docker image tag'
        value: ${{ jobs.docker.outputs.image }}

env:
  FORCE_COLOR: 3
  CI: true

jobs:
  # Validate inputs and setup
  validate:
    runs-on: ubuntu-latest
    outputs:
      project-config: ${{ steps.config.outputs.config }}
    steps:
      - name: Validate project type
        run: |
          valid_types="node python java mobile terraform ml-pipeline"
          if [[ ! " $valid_types " =~ " ${{ inputs.project-type }} " ]]; then
            echo "Invalid project type: ${{ inputs.project-type }}"
            echo "Valid types: $valid_types"
            exit 1
          fi

      - name: Generate project configuration
        id: config
        run: |
          case "${{ inputs.project-type }}" in
            "node")
              config='{"package_manager":"npm","test_command":"npm test","build_command":"npm run build","lint_command":"npm run lint"}'
              ;;
            "python")
              config='{"package_manager":"pip","test_command":"pytest","build_command":"python setup.py build","lint_command":"flake8"}'
              ;;
            "java")
              config='{"package_manager":"maven","test_command":"mvn test","build_command":"mvn package","lint_command":"mvn checkstyle:check"}'
              ;;
            "mobile")
              config='{"package_manager":"npm","test_command":"npm test","build_command":"npm run build:mobile","lint_command":"npm run lint"}'
              ;;
            "terraform")
              config='{"package_manager":"terraform","test_command":"terraform plan","build_command":"terraform validate","lint_command":"terraform fmt -check"}'
              ;;
            *)
              config='{"package_manager":"generic","test_command":"echo 'No tests'","build_command":"echo 'No build'","lint_command":"echo 'No lint'"}'
              ;;
          esac
          echo "config=$config" >> $GITHUB_OUTPUT

  # Environment setup
  setup:
    needs: validate
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Setup Node.js
        if: inputs.project-type == 'node' || inputs.project-type == 'mobile'
        uses: actions/setup-node@v4
        with:
          node-version: ${{ inputs.node-version }}
          cache: 'npm'
          cache-dependency-path: ${{ inputs.working-directory }}/package-lock.json

      - name: Setup Python
        if: inputs.project-type == 'python' || inputs.project-type == 'ml-pipeline'
        uses: actions/setup-python@v4
        with:
          python-version: ${{ inputs.python-version }}
          cache: 'pip'

      - name: Setup Java
        if: inputs.project-type == 'java'
        uses: actions/setup-java@v3
        with:
          java-version: ${{ inputs.java-version }}
          distribution: 'temurin'

      - name: Setup Terraform
        if: inputs.project-type == 'terraform'
        uses: hashicorp/setup-terraform@v2
        with:
          terraform_version: '1.5.0'

      - name: Cache dependencies
        uses: actions/cache@v3
        with:
          path: |
            ~/.npm
            ~/.cache/pip
            ~/.m2/repository
            ~/.terraform.d/plugin-cache
          key: ${{ runner.os }}-${{ inputs.project-type }}-${{ hashFiles('**/package-lock.json', '**/requirements.txt', '**/pom.xml', '**/*.tf') }}

  # Code quality and linting
  lint:
    needs: [validate, setup]
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Setup environment
        uses: ./.github/actions/setup-environment
        with:
          project-type: ${{ inputs.project-type }}
          node-version: ${{ inputs.node-version }}
          python-version: ${{ inputs.python-version }}

      - name: Install dependencies
        working-directory: ${{ inputs.working-directory }}
        run: |
          config='${{ needs.validate.outputs.project-config }}'
          package_manager=$(echo $config | jq -r '.package_manager')
          
          case $package_manager in
            "npm")
              npm ci
              ;;
            "pip")
              pip install -r requirements.txt
              pip install -r requirements-dev.txt
              ;;
            "maven")
              mvn dependency:resolve
              ;;
            "terraform")
              terraform init
              ;;
          esac

      - name: Run linting
        working-directory: ${{ inputs.working-directory }}
        run: |
          config='${{ needs.validate.outputs.project-config }}'
          lint_command=$(echo $config | jq -r '.lint_command')
          eval $lint_command

      - name: Run type checking
        if: inputs.project-type == 'node' || inputs.project-type == 'python'
        working-directory: ${{ inputs.working-directory }}
        run: |
          if [ "${{ inputs.project-type }}" = "node" ]; then
            npx tsc --noEmit
          elif [ "${{ inputs.project-type }}" = "python" ]; then
            mypy .
          fi

  # Testing
  test:
    needs: [validate, setup]
    runs-on: ubuntu-latest
    outputs:
      results: ${{ steps.test-summary.outputs.results }}
    strategy:
      matrix:
        test-type: 
          - ${{ inputs.run-unit-tests && 'unit' || '' }}
          - ${{ inputs.run-integration-tests && 'integration' || '' }}
          - ${{ inputs.run-e2e-tests && 'e2e' || '' }}
        exclude:
          - test-type: ''
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Setup environment
        uses: ./.github/actions/setup-environment
        with:
          project-type: ${{ inputs.project-type }}

      - name: Setup test services
        if: matrix.test-type == 'integration'
        run: |
          # Start required services for integration tests
          case "${{ inputs.project-type }}" in
            "python"|"node")
              docker-compose -f docker-compose.test.yml up -d
              ;;
          esac

      - name: Run tests
        uses: ./.github/actions/run-tests
        with:
          project-type: ${{ inputs.project-type }}
          test-type: ${{ matrix.test-type }}
          working-directory: ${{ inputs.working-directory }}

      - name: Upload test results
        uses: actions/upload-artifact@v3
        if: always()
        with:
          name: test-results-${{ matrix.test-type }}
          path: |
            ${{ inputs.working-directory }}/test-results/
            ${{ inputs.working-directory }}/coverage/

      - name: Test summary
        id: test-summary
        if: always()
        run: |
          echo "results={\"type\":\"${{ matrix.test-type }}\",\"status\":\"${{ job.status }}\"}" >> $GITHUB_OUTPUT

  # Security scanning
  security:
    needs: validate
    if: inputs.run-security-scan
    runs-on: ubuntu-latest
    outputs:
      results: ${{ steps.security-summary.outputs.results }}
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Dependency vulnerability scan
        if: inputs.run-dependency-check
        uses: ./.github/actions/security-scan
        with:
          scan-type: 'dependencies'
          project-type: ${{ inputs.project-type }}
          working-directory: ${{ inputs.working-directory }}

      - name: Code security scan
        uses: ./.github/actions/security-scan
        with:
          scan-type: 'code'
          project-type: ${{ inputs.project-type }}
          working-directory: ${{ inputs.working-directory }}

      - name: Infrastructure security scan
        if: inputs.project-type == 'terraform'
        uses: ./.github/actions/security-scan
        with:
          scan-type: 'infrastructure'
          working-directory: ${{ inputs.working-directory }}

      - name: Security summary
        id: security-summary
        run: |
          echo "results={\"status\":\"${{ job.status }}\",\"vulnerabilities\":\"$(cat security-report.json | jq '.vulnerabilities | length')\"}" >> $GITHUB_OUTPUT

  # Build artifacts
  build:
    needs: [validate, lint, test]
    if: inputs.build-artifacts
    runs-on: ubuntu-latest
    outputs:
      version: ${{ steps.version.outputs.version }}
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Setup environment
        uses: ./.github/actions/setup-environment
        with:
          project-type: ${{ inputs.project-type }}

      - name: Generate version
        id: version
        run: |
          version="$(date +%Y%m%d)-${GITHUB_SHA::8}"
          echo "version=$version" >> $GITHUB_OUTPUT

      - name: Build application
        working-directory: ${{ inputs.working-directory }}
        run: |
          config='${{ needs.validate.outputs.project-config }}'
          build_command=$(echo $config | jq -r '.build_command')
          eval $build_command

      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: ${{ inputs.artifact-name }}-${{ steps.version.outputs.version }}
          path: |
            ${{ inputs.working-directory }}/dist/
            ${{ inputs.working-directory }}/build/
            ${{ inputs.working-directory }}/target/

  # Docker build
  docker:
    needs: [validate, build]
    if: inputs.build-docker
    runs-on: ubuntu-latest
    outputs:
      image: ${{ steps.meta.outputs.tags }}
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      - name: Log in to Docker Hub
        if: secrets.DOCKER_USERNAME != ''
        uses: docker/login-action@v3
        with:
          username: ${{ secrets.DOCKER_USERNAME }}
          password: ${{ secrets.DOCKER_PASSWORD }}

      - name: Extract metadata
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ github.repository }}
          tags: |
            type=ref,event=branch
            type=ref,event=pr
            type=sha,prefix={{branch}}-

      - name: Build and push Docker image
        uses: docker/build-push-action@v5
        with:
          context: ${{ inputs.docker-context }}
          file: ${{ inputs.docker-file }}
          push: ${{ secrets.DOCKER_USERNAME != '' }}
          tags: ${{ steps.meta.outputs.tags }}
          labels: ${{ steps.meta.outputs.labels }}
          cache-from: type=gha
          cache-to: type=gha,mode=max

  # Notification
  notify:
    needs: [test, security, build, docker]
    if: always() && secrets.SLACK_WEBHOOK != ''
    runs-on: ubuntu-latest
    steps:
      - name: Send notification
        uses: 8398a7/action-slack@v3
        with:
          status: ${{ job.status }}
          text: |
            🔄 CI Pipeline Results for ${{ inputs.project-type }} project
            
            📊 Tests: ${{ needs.test.result }}
            🔒 Security: ${{ needs.security.result }}
            🏗️ Build: ${{ needs.build.result }}
            🐳 Docker: ${{ needs.docker.result }}
            
            📝 Commit: ${{ github.sha }}
            👤 Author: ${{ github.actor }}
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Task 2: Custom Actions

### Istruzioni
Sviluppa custom actions riutilizzabili per operazioni comuni.

### Soluzione: Setup Environment Action

```yaml
# .github/actions/setup-environment/action.yml
name: 'Setup Development Environment'
description: 'Sets up development environment for different project types'

inputs:
  project-type:
    description: 'Type of project (node, python, java, mobile, terraform)'
    required: true
  node-version:
    description: 'Node.js version'
    required: false
    default: '18'
  python-version:
    description: 'Python version'
    required: false
    default: '3.11'
  java-version:
    description: 'Java version'
    required: false
    default: '17'
  working-directory:
    description: 'Working directory'
    required: false
    default: '.'
  install-dependencies:
    description: 'Install project dependencies'
    required: false
    default: 'true'

outputs:
  environment-info:
    description: 'Information about the setup environment'
    value: ${{ steps.info.outputs.info }}

runs:
  using: 'composite'
  steps:
    - name: Setup Node.js
      if: inputs.project-type == 'node' || inputs.project-type == 'mobile'
      uses: actions/setup-node@v4
      with:
        node-version: ${{ inputs.node-version }}
        cache: 'npm'
        cache-dependency-path: ${{ inputs.working-directory }}/package-lock.json

    - name: Setup Python
      if: inputs.project-type == 'python' || inputs.project-type == 'ml-pipeline'
      uses: actions/setup-python@v4
      with:
        python-version: ${{ inputs.python-version }}
        cache: 'pip'
        cache-dependency-path: ${{ inputs.working-directory }}/requirements.txt

    - name: Setup Java
      if: inputs.project-type == 'java'
      uses: actions/setup-java@v3
      with:
        java-version: ${{ inputs.java-version }}
        distribution: 'temurin'

    - name: Setup Terraform
      if: inputs.project-type == 'terraform'
      uses: hashicorp/setup-terraform@v2

    - name: Setup Android SDK
      if: inputs.project-type == 'mobile'
      uses: android-actions/setup-android@v2

    - name: Setup iOS dependencies
      if: inputs.project-type == 'mobile' && runner.os == 'macOS'
      shell: bash
      run: |
        sudo xcode-select -s /Applications/Xcode_14.2.app
        gem install cocoapods

    - name: Install dependencies
      if: inputs.install-dependencies == 'true'
      shell: bash
      working-directory: ${{ inputs.working-directory }}
      run: |
        case "${{ inputs.project-type }}" in
          "node"|"mobile")
            if [ -f "package-lock.json" ]; then
              npm ci
            elif [ -f "yarn.lock" ]; then
              yarn install --frozen-lockfile
            else
              npm install
            fi
            ;;
          "python"|"ml-pipeline")
            if [ -f "requirements.txt" ]; then
              pip install -r requirements.txt
            fi
            if [ -f "requirements-dev.txt" ]; then
              pip install -r requirements-dev.txt
            fi
            if [ -f "pyproject.toml" ]; then
              pip install -e .
            fi
            ;;
          "java")
            if [ -f "pom.xml" ]; then
              mvn dependency:resolve
            elif [ -f "build.gradle" ]; then
              ./gradlew dependencies
            fi
            ;;
          "terraform")
            terraform init
            ;;
        esac

    - name: Generate environment info
      id: info
      shell: bash
      run: |
        info=$(cat << EOF
        {
          "project_type": "${{ inputs.project-type }}",
          "node_version": "$(node --version 2>/dev/null || echo 'not installed')",
          "python_version": "$(python --version 2>/dev/null || echo 'not installed')",
          "java_version": "$(java -version 2>&1 | head -n 1 || echo 'not installed')",
          "terraform_version": "$(terraform version -json 2>/dev/null | jq -r '.terraform_version' || echo 'not installed')",
          "working_directory": "${{ inputs.working-directory }}",
          "runner_os": "${{ runner.os }}"
        }
        EOF
        )
        echo "info=$info" >> $GITHUB_OUTPUT
```

### Custom Test Runner Action

```javascript
// .github/actions/run-tests/index.js
const core = require('@actions/core');
const exec = require('@actions/exec');
const fs = require('fs');
const path = require('path');

async function run() {
  try {
    const projectType = core.getInput('project-type', { required: true });
    const testType = core.getInput('test-type', { required: true });
    const workingDirectory = core.getInput('working-directory') || '.';
    
    core.info(`Running ${testType} tests for ${projectType} project`);
    
    // Change to working directory
    process.chdir(workingDirectory);
    
    let testCommand = '';
    let testPattern = '';
    
    // Determine test command based on project type and test type
    switch (projectType) {
      case 'node':
      case 'mobile':
        testCommand = getNodeTestCommand(testType);
        break;
      case 'python':
      case 'ml-pipeline':
        testCommand = getPythonTestCommand(testType);
        break;
      case 'java':
        testCommand = getJavaTestCommand(testType);
        break;
      case 'terraform':
        testCommand = getTerraformTestCommand(testType);
        break;
      default:
        throw new Error(`Unsupported project type: ${projectType}`);
    }
    
    core.info(`Executing: ${testCommand}`);
    
    // Execute test command
    let output = '';
    let error = '';
    
    const options = {
      listeners: {
        stdout: (data) => {
          output += data.toString();
        },
        stderr: (data) => {
          error += data.toString();
        }
      }
    };
    
    const exitCode = await exec.exec(testCommand, [], options);
    
    // Parse test results
    const results = parseTestResults(projectType, testType, output, error, exitCode);
    
    // Set outputs
    core.setOutput('results', JSON.stringify(results));
    core.setOutput('success', results.success);
    core.setOutput('test-count', results.testCount);
    core.setOutput('failure-count', results.failureCount);
    
    // Create test summary
    await createTestSummary(results);
    
    if (!results.success && exitCode !== 0) {
      core.setFailed(`Tests failed with exit code ${exitCode}`);
    }
    
  } catch (error) {
    core.setFailed(error.message);
  }
}

function getNodeTestCommand(testType) {
  const commands = {
    'unit': 'npm run test:unit',
    'integration': 'npm run test:integration',
    'e2e': 'npm run test:e2e'
  };
  return commands[testType] || 'npm test';
}

function getPythonTestCommand(testType) {
  const commands = {
    'unit': 'pytest tests/unit/ --cov=src --cov-report=xml',
    'integration': 'pytest tests/integration/',
    'e2e': 'pytest tests/e2e/'
  };
  return commands[testType] || 'pytest';
}

function getJavaTestCommand(testType) {
  const commands = {
    'unit': 'mvn test',
    'integration': 'mvn integration-test',
    'e2e': 'mvn verify'
  };
  return commands[testType] || 'mvn test';
}

function getTerraformTestCommand(testType) {
  const commands = {
    'unit': 'terraform validate',
    'integration': 'terraform plan',
    'e2e': 'terratest'
  };
  return commands[testType] || 'terraform validate';
}

function parseTestResults(projectType, testType, output, error, exitCode) {
  let results = {
    projectType,
    testType,
    success: exitCode === 0,
    testCount: 0,
    failureCount: 0,
    duration: 0,
    coverage: null
  };
  
  // Parse based on project type
  switch (projectType) {
    case 'node':
    case 'mobile':
      results = parseJestResults(output, results);
      break;
    case 'python':
    case 'ml-pipeline':
      results = parsePytestResults(output, results);
      break;
    case 'java':
      results = parseMavenResults(output, results);
      break;
  }
  
  return results;
}

function parseJestResults(output, results) {
  // Parse Jest output
  const testMatch = output.match(/Tests:\s+(\d+) failed, (\d+) passed, (\d+) total/);
  if (testMatch) {
    results.failureCount = parseInt(testMatch[1]);
    results.testCount = parseInt(testMatch[3]);
  }
  
  const timeMatch = output.match(/Time:\s+([\d.]+)s/);
  if (timeMatch) {
    results.duration = parseFloat(timeMatch[1]);
  }
  
  // Parse coverage
  const coverageMatch = output.match(/All files\s+\|\s+([\d.]+)/);
  if (coverageMatch) {
    results.coverage = parseFloat(coverageMatch[1]);
  }
  
  return results;
}

function parsePytestResults(output, results) {
  // Parse pytest output
  const testMatch = output.match(/(\d+) failed, (\d+) passed/);
  if (testMatch) {
    results.failureCount = parseInt(testMatch[1]);
    results.testCount = parseInt(testMatch[1]) + parseInt(testMatch[2]);
  }
  
  return results;
}

function parseMavenResults(output, results) {
  // Parse Maven surefire results
  const testMatch = output.match(/Tests run: (\d+), Failures: (\d+), Errors: (\d+)/);
  if (testMatch) {
    results.testCount = parseInt(testMatch[1]);
    results.failureCount = parseInt(testMatch[2]) + parseInt(testMatch[3]);
  }
  
  return results;
}

async function createTestSummary(results) {
  const summary = core.summary
    .addHeading(`${results.testType} Test Results`, 2)
    .addTable([
      ['Metric', 'Value'],
      ['Project Type', results.projectType],
      ['Test Type', results.testType],
      ['Status', results.success ? '✅ Passed' : '❌ Failed'],
      ['Total Tests', results.testCount.toString()],
      ['Failed Tests', results.failureCount.toString()],
      ['Duration', `${results.duration}s`],
      ['Coverage', results.coverage ? `${results.coverage}%` : 'N/A']
    ]);
  
  await summary.write();
}

run();
```

### Package.json per Custom Action

```json
{
  "name": "run-tests-action",
  "version": "1.0.0",
  "description": "Custom action to run tests for different project types",
  "main": "index.js",
  "dependencies": {
    "@actions/core": "^1.10.0",
    "@actions/exec": "^1.1.1"
  }
}
```

## Task 3: Workflow Templates per Team

### Istruzioni
Crea template specifici per ogni team con configurazioni pre-definite.

### Soluzione: Mobile App Workflow

```yaml
# templates/mobile-app/.github/workflows/mobile-ci.yml
name: Mobile App CI/CD

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

jobs:
  mobile-ci:
    uses: organization/.github/.github/workflows/reusable-ci.yml@main
    with:
      project-type: 'mobile'
      node-version: '18'
      run-unit-tests: true
      run-integration-tests: true
      run-e2e-tests: false
      run-security-scan: true
      build-artifacts: true
      artifact-name: 'mobile-app'
    secrets:
      SLACK_WEBHOOK: ${{ secrets.SLACK_WEBHOOK }}

  ios-build:
    needs: mobile-ci
    if: github.ref == 'refs/heads/main'
    runs-on: macos-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup React Native
        uses: ./.github/actions/setup-environment
        with:
          project-type: 'mobile'
      
      - name: Setup iOS certificates
        uses: apple-actions/import-codesign-certs@v1
        with:
          p12-file-base64: ${{ secrets.IOS_DIST_CERT }}
          p12-password: ${{ secrets.IOS_DIST_CERT_PASSWORD }}
      
      - name: Setup provisioning profile
        uses: apple-actions/download-provisioning-profiles@v1
        with:
          bundle-id: com.company.app
          issuer-id: ${{ secrets.APPSTORE_ISSUER_ID }}
          api-key-id: ${{ secrets.APPSTORE_KEY_ID }}
          api-private-key: ${{ secrets.APPSTORE_PRIVATE_KEY }}
      
      - name: Build iOS app
        run: |
          cd ios
          xcodebuild -workspace MyApp.xcworkspace \
            -scheme MyApp \
            -configuration Release \
            -archivePath MyApp.xcarchive \
            archive
      
      - name: Export IPA
        run: |
          cd ios
          xcodebuild -exportArchive \
            -archivePath MyApp.xcarchive \
            -exportPath export \
            -exportOptionsPlist exportOptions.plist
      
      - name: Upload to TestFlight
        uses: apple-actions/upload-testflight-build@v1
        with:
          app-path: ios/export/MyApp.ipa
          issuer-id: ${{ secrets.APPSTORE_ISSUER_ID }}
          api-key-id: ${{ secrets.APPSTORE_KEY_ID }}
          api-private-key: ${{ secrets.APPSTORE_PRIVATE_KEY }}

  android-build:
    needs: mobile-ci
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup React Native
        uses: ./.github/actions/setup-environment
        with:
          project-type: 'mobile'
      
      - name: Setup Android keystore
        run: |
          echo "${{ secrets.ANDROID_KEYSTORE }}" | base64 -d > android/app/keystore.jks
      
      - name: Build Android APK
        run: |
          cd android
          ./gradlew assembleRelease
        env:
          KEYSTORE_PASSWORD: ${{ secrets.KEYSTORE_PASSWORD }}
          KEY_ALIAS: ${{ secrets.KEY_ALIAS }}
          KEY_PASSWORD: ${{ secrets.KEY_PASSWORD }}
      
      - name: Upload to Google Play
        uses: r0adkll/upload-google-play@v1
        with:
          serviceAccountJsonPlainText: ${{ secrets.GOOGLE_PLAY_SERVICE_ACCOUNT }}
          packageName: com.company.app
          releaseFiles: android/app/build/outputs/apk/release/app-release.apk
          track: internal
```

### Python API Workflow

```yaml
# templates/python-api/.github/workflows/python-api.yml
name: Python API CI/CD

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

jobs:
  python-ci:
    uses: organization/.github/.github/workflows/reusable-ci.yml@main
    with:
      project-type: 'python'
      python-version: '3.11'
      run-unit-tests: true
      run-integration-tests: true
      run-security-scan: true
      build-docker: true
      docker-file: 'Dockerfile'
    secrets:
      DOCKER_USERNAME: ${{ secrets.DOCKER_USERNAME }}
      DOCKER_PASSWORD: ${{ secrets.DOCKER_PASSWORD }}
      SLACK_WEBHOOK: ${{ secrets.SLACK_WEBHOOK }}

  performance-test:
    needs: python-ci
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
      
      - name: Setup Python
        uses: actions/setup-python@v4
        with:
          python-version: '3.11'
      
      - name: Install dependencies
        run: |
          pip install -r requirements.txt
          pip install locust
      
      - name: Start API server
        run: |
          uvicorn main:app --host 0.0.0.0 --port 8000 &
          sleep 10
        env:
          DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb
      
      - name: Run performance tests
        run: |
          locust -f tests/performance/locustfile.py \
            --host http://localhost:8000 \
            --users 10 \
            --spawn-rate 2 \
            --run-time 60s \
            --headless \
            --html performance-report.html
      
      - name: Upload performance report
        uses: actions/upload-artifact@v3
        with:
          name: performance-report
          path: performance-report.html

  deploy-api:
    needs: [python-ci, performance-test]
    if: github.ref == 'refs/heads/main'
    uses: organization/.github/.github/workflows/reusable-deploy.yml@main
    with:
      environment: 'production'
      service-name: 'python-api'
      health-check-url: 'https://api.company.com/health'
    secrets:
      AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
      AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
```

## Task 4: Template Generator

### Istruzioni
Crea un workflow che generi automaticamente template per nuovi progetti.

### Soluzione: Template Generator

```yaml
# .github/workflows/template-generator.yml
name: Generate Project Template

on:
  workflow_dispatch:
    inputs:
      project-name:
        description: 'Name of the new project'
        required: true
        type: string
      project-type:
        description: 'Type of project'
        required: true
        type: choice
        options:
          - node
          - python
          - java
          - mobile
          - terraform
          - ml-pipeline
      team:
        description: 'Team name'
        required: true
        type: string
      repository-url:
        description: 'Target repository URL'
        required: true
        type: string

jobs:
  generate-template:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout templates
        uses: actions/checkout@v4

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'

      - name: Install template generator
        run: npm install -g cookiecutter

      - name: Generate project structure
        run: |
          mkdir -p generated-project
          
          # Copy base template
          cp -r templates/${{ inputs.project-type }}/* generated-project/
          
          # Replace placeholders
          find generated-project -type f -name "*.yml" -o -name "*.yaml" -o -name "*.json" -o -name "*.md" | \
          xargs sed -i "s/{{PROJECT_NAME}}/${{ inputs.project-name }}/g"
          
          find generated-project -type f -name "*.yml" -o -name "*.yaml" -o -name "*.json" -o -name "*.md" | \
          xargs sed -i "s/{{TEAM}}/${{ inputs.team }}/g"
          
          find generated-project -type f -name "*.yml" -o -name "*.yaml" -o -name "*.json" -o -name "*.md" | \
          xargs sed -i "s/{{PROJECT_TYPE}}/${{ inputs.project-type }}/g"

      - name: Generate README
        run: |
          cat > generated-project/README.md << EOF
          # ${{ inputs.project-name }}
          
          A ${{ inputs.project-type }} project for the ${{ inputs.team }} team.
          
          ## Quick Start
          
          This project was generated using the organization's workflow templates.
          
          ### Development Setup
          
          1. Clone the repository
          2. Install dependencies
          3. Run tests
          4. Start development server
          
          ### CI/CD Pipeline
          
          The project includes pre-configured GitHub Actions workflows for:
          
          - ✅ Automated testing
          - 🔒 Security scanning
          - 🏗️ Build automation
          - 🚀 Deployment pipeline
          - 📊 Performance monitoring
          
          ### Team: ${{ inputs.team }}
          
          Contact the ${{ inputs.team }} team for questions about this project.
          EOF

      - name: Generate workflow documentation
        run: |
          cat > generated-project/docs/workflows.md << EOF
          # Workflow Documentation
          
          ## Available Workflows
          
          ### CI/CD Pipeline
          - **Trigger**: Push to main/develop, PR to main
          - **Features**: Testing, security scanning, building
          - **Deployment**: Automatic to staging/production
          
          ### Manual Deployment
          - **Trigger**: Manual workflow dispatch
          - **Target**: Any environment
          - **Options**: Custom deployment strategies
          
          ## Configuration
          
          ### Required Secrets
          - \`DOCKER_USERNAME\`: Docker registry username
          - \`DOCKER_PASSWORD\`: Docker registry password
          - \`SLACK_WEBHOOK\`: Slack notifications
          
          ### Environment Variables
          - \`NODE_VERSION\`: Node.js version (default: 18)
          - \`PYTHON_VERSION\`: Python version (default: 3.11)
          
          ## Customization
          
          Edit \`.github/workflows/ci-cd.yml\` to customize the pipeline for your needs.
          EOF

      - name: Create deployment scripts
        run: |
          mkdir -p generated-project/scripts
          
          cat > generated-project/scripts/deploy.sh << 'EOF'
          #!/bin/bash
          set -e
          
          ENVIRONMENT=${1:-staging}
          PROJECT_NAME="${{ inputs.project-name }}"
          
          echo "Deploying $PROJECT_NAME to $ENVIRONMENT"
          
          # Add deployment logic here
          case $ENVIRONMENT in
            "staging")
              echo "Deploying to staging environment"
              ;;
            "production")
              echo "Deploying to production environment"
              ;;
            *)
              echo "Unknown environment: $ENVIRONMENT"
              exit 1
              ;;
          esac
          EOF
          
          chmod +x generated-project/scripts/deploy.sh

      - name: Package template
        run: |
          cd generated-project
          tar -czf ../${{ inputs.project-name }}-template.tar.gz .

      - name: Upload template
        uses: actions/upload-artifact@v3
        with:
          name: ${{ inputs.project-name }}-template
          path: ${{ inputs.project-name }}-template.tar.gz

      - name: Create repository
        uses: actions/github-script@v6
        with:
          github-token: ${{ secrets.PAT_TOKEN }}
          script: |
            const repoUrl = '${{ inputs.repository-url }}';
            const [owner, repo] = repoUrl.replace('https://github.com/', '').split('/');
            
            try {
              await github.rest.repos.createForOrg({
                org: owner,
                name: repo,
                description: 'Generated from organization workflow template',
                private: true,
                auto_init: false
              });
              
              console.log(`Repository ${owner}/${repo} created successfully`);
            } catch (error) {
              console.log(`Repository might already exist: ${error.message}`);
            }

      - name: Push template to repository
        run: |
          git config --global user.name "Workflow Template Generator"
          git config --global user.email "workflows@company.com"
          
          cd generated-project
          git init
          git add .
          git commit -m "Initial commit from template generator"
          git branch -M main
          git remote add origin ${{ inputs.repository-url }}
          git push -u origin main
        env:
          GITHUB_TOKEN: ${{ secrets.PAT_TOKEN }}

      - name: Create initial issues
        uses: actions/github-script@v6
        with:
          github-token: ${{ secrets.PAT_TOKEN }}
          script: |
            const repoUrl = '${{ inputs.repository-url }}';
            const [owner, repo] = repoUrl.replace('https://github.com/', '').split('/');
            
            const issues = [
              {
                title: '🔧 Setup Development Environment',
                body: 'Configure development environment and dependencies'
              },
              {
                title: '🧪 Configure Testing Framework',
                body: 'Set up unit and integration tests'
              },
              {
                title: '🔒 Security Configuration',
                body: 'Review and configure security scanning settings'
              },
              {
                title: '🚀 Production Deployment Setup',
                body: 'Configure production deployment pipeline'
              }
            ];
            
            for (const issue of issues) {
              await github.rest.issues.create({
                owner,
                repo,
                title: issue.title,
                body: issue.body,
                labels: ['setup', 'template-generated']
              });
            }

  notify-team:
    needs: generate-template
    runs-on: ubuntu-latest
    steps:
      - name: Notify team
        uses: 8398a7/action-slack@v3
        with:
          status: success
          text: |
            🎉 New project template generated!
            
            📝 **Project**: ${{ inputs.project-name }}
            🏗️ **Type**: ${{ inputs.project-type }}
            👥 **Team**: ${{ inputs.team }}
            🔗 **Repository**: ${{ inputs.repository-url }}
            
            The project is ready for development with pre-configured workflows!
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Task 5: Advanced Workflow Patterns

### Istruzioni
Implementa pattern avanzati come matrix builds, conditional workflows, e parallel execution.

### Soluzione: Cross-Platform Testing

```yaml
# .github/workflows/cross-platform-testing.yml
name: Cross-Platform Testing

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  matrix-testing:
    strategy:
      fail-fast: false
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        node-version: [16, 18, 20]
        python-version: [3.9, 3.10, 3.11]
        include:
          # Special configurations
          - os: ubuntu-latest
            node-version: 18
            python-version: 3.11
            run-integration: true
          - os: windows-latest
            node-version: 18
            python-version: 3.11
            run-windows-specific: true
        exclude:
          # Skip certain combinations
          - os: windows-latest
            python-version: 3.9
          - os: macos-latest
            node-version: 16

    runs-on: ${{ matrix.os }}
    
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Setup Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v4
        with:
          node-version: ${{ matrix.node-version }}

      - name: Setup Python ${{ matrix.python-version }}
        uses: actions/setup-python@v4
        with:
          python-version: ${{ matrix.python-version }}

      - name: Install dependencies
        shell: bash
        run: |
          npm ci
          pip install -r requirements.txt

      - name: Run tests
        shell: bash
        run: |
          npm test
          python -m pytest

      - name: Run integration tests
        if: matrix.run-integration
        shell: bash
        run: |
          npm run test:integration

      - name: Run Windows-specific tests
        if: matrix.run-windows-specific
        shell: powershell
        run: |
          .\scripts\test-windows.ps1

      - name: Upload test results
        uses: actions/upload-artifact@v3
        if: always()
        with:
          name: test-results-${{ matrix.os }}-node${{ matrix.node-version }}-py${{ matrix.python-version }}
          path: |
            test-results/
            coverage/

  conditional-deployment:
    needs: matrix-testing
    if: github.ref == 'refs/heads/main' && success()
    strategy:
      matrix:
        environment: [staging, production]
    runs-on: ubuntu-latest
    environment: ${{ matrix.environment }}
    
    steps:
      - name: Deploy to ${{ matrix.environment }}
        run: |
          echo "Deploying to ${{ matrix.environment }}"
          # Add deployment logic

  parallel-workflows:
    runs-on: ubuntu-latest
    
    steps:
      - name: Start parallel jobs
        uses: actions/github-script@v6
        with:
          script: |
            const workflows = [
              'security-scan.yml',
              'performance-test.yml',
              'documentation-build.yml'
            ];
            
            for (const workflow of workflows) {
              await github.rest.actions.createWorkflowDispatch({
                owner: context.repo.owner,
                repo: context.repo.repo,
                workflow_id: workflow,
                ref: context.ref
              });
            }
```

## Quiz di Verifica

### Domanda 1
Qual è il vantaggio principale dei workflow riutilizzabili?

A) Sono più veloci da eseguire
B) Riducono la duplicazione di codice
C) Usano meno risorse
D) Sono più sicuri

**Risposta: B) Riducono la duplicazione di codice**

I workflow riutilizzabili permettono di centralizzare la logica comune e riutilizzarla in multiple repository.

### Domanda 2
Quando è appropriato utilizzare una custom action?

A) Per operazioni semplici
B) Per logica complessa riutilizzabile
C) Solo per JavaScript
D) Mai, meglio usare step inline

**Risposta: B) Per logica complessa riutilizzabile**

Le custom action sono ideali per incapsulare logica complessa che può essere riutilizzata in multiple workflow.

### Domanda 3
Qual è la differenza tra `workflow_call` e `workflow_dispatch`?

A) Non c'è differenza
B) workflow_call è per chiamate automatiche, workflow_dispatch per trigger manuali
C) workflow_dispatch è deprecato
D) workflow_call non supporta parametri

**Risposta: B) workflow_call è per chiamate automatiche, workflow_dispatch per trigger manuali**

workflow_call permette di creare workflow riutilizzabili, workflow_dispatch permette trigger manuali.

## Conclusione

Questo esercizio dimostra come creare un ecosistema completo di workflow personalizzati e riutilizzabili. Le competenze acquisite includono modularità, riutilizzabilità, automazione avanzata e gestione di workflow enterprise-scale.
