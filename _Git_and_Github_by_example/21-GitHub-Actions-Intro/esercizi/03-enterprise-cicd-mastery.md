# Esercizio 03 - Mastery: Enterprise CI/CD Pipeline

## 🎯 Obiettivo

Sviluppare un **sistema CI/CD enterprise-grade** completo con testing multi-layer, deployment automatizzato, monitoring, security scanning, e rollback automatici per un'applicazione microservizi.

## 📋 Requisiti Tecnici

- **Repository GitHub** con GitHub Actions abilitato
- **Account cloud provider** (AWS/Azure/GCP) per deployment
- **Docker** e containerization knowledge
- **Conoscenza di frameworks** (Node.js, Python, o Java)
- **Basic DevOps** e security concepts

## ⏱️ Durata Stimata

**240-300 minuti** (setup complesso + implementazione completa)

## 🎬 Scenario dell'Esercizio

Implementerai un **sistema CI/CD completo** per una piattaforma e-commerce microservizi che include:
- **Frontend React** con SSR (Next.js)
- **API Gateway** (Node.js/Express)
- **Service Mesh** con microservizi (User, Product, Payment)
- **Database migrations** e seeding
- **Infrastructure as Code** (Terraform/CloudFormation)

## 🏗️ Fase 1: Project Structure Setup (45 min)

### Step 1: Repository Structure

```bash
# 1. Crea repository su GitHub
# Nome: "enterprise-ecommerce-platform"
# Descrizione: "Enterprise e-commerce platform with full CI/CD"

# 2. Clone e setup struttura
git clone https://github.com/YOUR_USERNAME/enterprise-ecommerce-platform.git
cd enterprise-ecommerce-platform

# 3. Crea struttura progetto
mkdir -p {frontend,api-gateway,services/{user-service,product-service,payment-service},infrastructure,scripts,.github/workflows}
```

### Step 2: Application Code Structure

**Frontend Package.json** - `frontend/package.json`:
```json
{
  "name": "ecommerce-frontend",
  "version": "1.0.0",
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "start": "next start",
    "test": "jest",
    "test:e2e": "cypress run",
    "lint": "eslint . --ext .js,.jsx,.ts,.tsx",
    "type-check": "tsc --noEmit"
  },
  "dependencies": {
    "next": "^14.0.0",
    "react": "^18.0.0",
    "react-dom": "^18.0.0",
    "@emotion/react": "^11.0.0",
    "@emotion/styled": "^11.0.0",
    "@mui/material": "^5.0.0"
  },
  "devDependencies": {
    "@types/node": "^20.0.0",
    "@types/react": "^18.0.0",
    "typescript": "^5.0.0",
    "eslint": "^8.0.0",
    "eslint-config-next": "^14.0.0",
    "jest": "^29.0.0",
    "cypress": "^13.0.0"
  }
}
```

**API Gateway** - `api-gateway/package.json`:
```json
{
  "name": "ecommerce-api-gateway",
  "version": "1.0.0",
  "scripts": {
    "start": "node dist/index.js",
    "dev": "ts-node-dev src/index.ts",
    "build": "tsc",
    "test": "jest",
    "test:integration": "jest --config jest.integration.config.js",
    "lint": "eslint src/**/*.ts",
    "security-scan": "npm audit && snyk test"
  },
  "dependencies": {
    "express": "^4.18.0",
    "helmet": "^7.0.0",
    "cors": "^2.8.0",
    "rate-limiter-flexible": "^3.0.0",
    "winston": "^3.10.0",
    "joi": "^17.9.0"
  },
  "devDependencies": {
    "typescript": "^5.0.0",
    "@types/express": "^4.17.0",
    "@types/node": "^20.0.0",
    "jest": "^29.0.0",
    "supertest": "^6.3.0",
    "ts-node-dev": "^2.0.0"
  }
}
```

**Microservice Template** - `services/user-service/package.json`:
```json
{
  "name": "user-service",
  "version": "1.0.0",
  "scripts": {
    "start": "node dist/index.js",
    "dev": "ts-node-dev src/index.ts",
    "build": "tsc",
    "test": "jest",
    "test:coverage": "jest --coverage",
    "migrate": "knex migrate:latest",
    "seed": "knex seed:run",
    "lint": "eslint src/**/*.ts"
  },
  "dependencies": {
    "express": "^4.18.0",
    "knex": "^2.5.0",
    "pg": "^8.11.0",
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0"
  },
  "devDependencies": {
    "typescript": "^5.0.0",
    "@types/express": "^4.17.0",
    "@types/node": "^20.0.0",
    "jest": "^29.0.0"
  }
}
```

### Step 3: Docker Configuration

**Root Dockerfile** - `Dockerfile.frontend`:
```dockerfile
# Multi-stage build for Next.js frontend
FROM node:18-alpine AS dependencies
WORKDIR /app
COPY frontend/package*.json ./
RUN npm ci --only=production

FROM node:18-alpine AS builder
WORKDIR /app
COPY frontend/package*.json ./
RUN npm ci
COPY frontend/ .
RUN npm run build

FROM node:18-alpine AS runner
WORKDIR /app
ENV NODE_ENV production

RUN addgroup --system --gid 1001 nodejs
RUN adduser --system --uid 1001 nextjs

COPY --from=builder /app/public ./public
COPY --from=builder --chown=nextjs:nodejs /app/.next/standalone ./
COPY --from=builder --chown=nextjs:nodejs /app/.next/static ./.next/static

USER nextjs
EXPOSE 3000
ENV PORT 3000

CMD ["node", "server.js"]
```

**API Gateway Dockerfile** - `Dockerfile.api-gateway`:
```dockerfile
FROM node:18-alpine AS dependencies
WORKDIR /app
COPY api-gateway/package*.json ./
RUN npm ci --only=production

FROM node:18-alpine AS builder
WORKDIR /app
COPY api-gateway/package*.json ./
RUN npm ci
COPY api-gateway/ .
RUN npm run build

FROM node:18-alpine AS runner
WORKDIR /app
ENV NODE_ENV production

RUN addgroup --system --gid 1001 nodejs
RUN adduser --system --uid 1001 apiuser

COPY --from=dependencies /app/node_modules ./node_modules
COPY --from=builder /app/dist ./dist
COPY api-gateway/package*.json ./

USER apiuser
EXPOSE 4000
ENV PORT 4000

HEALTHCHECK --interval=30s --timeout=10s --start-period=40s --retries=3 \
  CMD curl -f http://localhost:4000/health || exit 1

CMD ["node", "dist/index.js"]
```

**Docker Compose** - `docker-compose.yml`:
```yaml
version: '3.8'

services:
  frontend:
    build:
      context: .
      dockerfile: Dockerfile.frontend
    ports:
      - "3000:3000"
    environment:
      - NEXT_PUBLIC_API_URL=http://api-gateway:4000
    depends_on:
      - api-gateway

  api-gateway:
    build:
      context: .
      dockerfile: Dockerfile.api-gateway
    ports:
      - "4000:4000"
    environment:
      - NODE_ENV=production
      - USER_SERVICE_URL=http://user-service:5001
      - PRODUCT_SERVICE_URL=http://product-service:5002
      - PAYMENT_SERVICE_URL=http://payment-service:5003
    depends_on:
      - user-service
      - product-service
      - payment-service

  user-service:
    build:
      context: .
      dockerfile: Dockerfile.microservice
      args:
        SERVICE_NAME: user-service
    ports:
      - "5001:5001"
    environment:
      - NODE_ENV=production
      - DATABASE_URL=postgresql://user:password@postgres-user:5432/userdb
    depends_on:
      - postgres-user

  product-service:
    build:
      context: .
      dockerfile: Dockerfile.microservice
      args:
        SERVICE_NAME: product-service
    ports:
      - "5002:5002"
    environment:
      - NODE_ENV=production
      - DATABASE_URL=postgresql://user:password@postgres-product:5432/productdb
    depends_on:
      - postgres-product

  payment-service:
    build:
      context: .
      dockerfile: Dockerfile.microservice
      args:
        SERVICE_NAME: payment-service
    ports:
      - "5003:5003"
    environment:
      - NODE_ENV=production
      - DATABASE_URL=postgresql://user:password@postgres-payment:5432/paymentdb
    depends_on:
      - postgres-payment

  postgres-user:
    image: postgres:15-alpine
    environment:
      POSTGRES_DB: userdb
      POSTGRES_USER: user
      POSTGRES_PASSWORD: password
    volumes:
      - postgres_user_data:/var/lib/postgresql/data

  postgres-product:
    image: postgres:15-alpine
    environment:
      POSTGRES_DB: productdb
      POSTGRES_USER: user
      POSTGRES_PASSWORD: password
    volumes:
      - postgres_product_data:/var/lib/postgresql/data

  postgres-payment:
    image: postgres:15-alpine
    environment:
      POSTGRES_DB: paymentdb
      POSTGRES_USER: user
      POSTGRES_PASSWORD: password
    volumes:
      - postgres_payment_data:/var/lib/postgresql/data

volumes:
  postgres_user_data:
  postgres_product_data:
  postgres_payment_data:
```

## 🔄 Fase 2: CI Pipeline - Testing & Quality (60 min)

### Step 4: Comprehensive Testing Pipeline

**File: `.github/workflows/ci-testing.yml`**
```yaml
name: 🧪 Comprehensive Testing Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main, develop]
    types: [opened, synchronize, reopened]

env:
  NODE_VERSION: '18'
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}

jobs:
  # Stage 1: Code Quality & Security
  code-quality:
    name: 🔍 Code Quality & Security
    runs-on: ubuntu-latest
    outputs:
      frontend-changed: ${{ steps.changes.outputs.frontend }}
      api-gateway-changed: ${{ steps.changes.outputs.api-gateway }}
      services-changed: ${{ steps.changes.outputs.services }}
      
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4
        with:
          fetch-depth: 0

      - name: 🔍 Detect changes
        uses: dorny/paths-filter@v2
        id: changes
        with:
          filters: |
            frontend:
              - 'frontend/**'
            api-gateway:
              - 'api-gateway/**'
            services:
              - 'services/**'

      - name: 🏗️ Setup Node.js
        if: steps.changes.outputs.frontend == 'true' || steps.changes.outputs.api-gateway == 'true' || steps.changes.outputs.services == 'true'
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 📦 Install root dependencies
        if: steps.changes.outputs.frontend == 'true' || steps.changes.outputs.api-gateway == 'true' || steps.changes.outputs.services == 'true'
        run: |
          npm install -g npm@latest
          npm install -g eslint prettier typescript

      # Frontend Quality Checks
      - name: 📦 Install frontend dependencies
        if: steps.changes.outputs.frontend == 'true'
        working-directory: ./frontend
        run: |
          npm ci

      - name: 🔍 Frontend ESLint
        if: steps.changes.outputs.frontend == 'true'
        working-directory: ./frontend
        run: |
          npm run lint -- --format=json --output-file=eslint-report.json || true
          npm run lint

      - name: 🎨 Frontend Prettier Check
        if: steps.changes.outputs.frontend == 'true'
        working-directory: ./frontend
        run: |
          npx prettier --check "**/*.{js,jsx,ts,tsx,json,css,md}"

      - name: 🔧 Frontend Type Check
        if: steps.changes.outputs.frontend == 'true'
        working-directory: ./frontend
        run: |
          npm run type-check

      # API Gateway Quality Checks  
      - name: 📦 Install API Gateway dependencies
        if: steps.changes.outputs.api-gateway == 'true'
        working-directory: ./api-gateway
        run: |
          npm ci

      - name: 🔍 API Gateway ESLint
        if: steps.changes.outputs.api-gateway == 'true'
        working-directory: ./api-gateway
        run: |
          npm run lint

      - name: 🔧 API Gateway Type Check
        if: steps.changes.outputs.api-gateway == 'true'
        working-directory: ./api-gateway
        run: |
          npx tsc --noEmit

      # Security Scanning
      - name: 🔒 Security Audit - Frontend
        if: steps.changes.outputs.frontend == 'true'
        working-directory: ./frontend
        run: |
          npm audit --audit-level=high
          npx audit-ci --config ../scripts/audit-ci.config.json

      - name: 🔒 Security Audit - API Gateway
        if: steps.changes.outputs.api-gateway == 'true'
        working-directory: ./api-gateway
        run: |
          npm audit --audit-level=high
          npm run security-scan

      # Code Coverage Collection
      - name: 📊 Upload code quality reports
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: code-quality-reports
          path: |
            frontend/eslint-report.json
            api-gateway/coverage/
            **/test-results.xml

  # Stage 2: Unit & Integration Testing
  unit-integration-tests:
    name: 🧪 Unit & Integration Tests
    runs-on: ubuntu-latest
    needs: code-quality
    if: always() && (needs.code-quality.outputs.frontend-changed == 'true' || needs.code-quality.outputs.api-gateway-changed == 'true' || needs.code-quality.outputs.services-changed == 'true')
    
    services:
      postgres:
        image: postgres:15
        env:
          POSTGRES_USER: test
          POSTGRES_PASSWORD: test
          POSTGRES_DB: testdb
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
        ports:
          - 5432:5432

      redis:
        image: redis:7-alpine
        options: >-
          --health-cmd "redis-cli ping"
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
        ports:
          - 6379:6379

    strategy:
      matrix:
        test-group: [frontend, api-gateway, user-service, product-service, payment-service]
        include:
          - test-group: frontend
            working-directory: ./frontend
            test-command: npm run test -- --coverage --watchAll=false
          - test-group: api-gateway
            working-directory: ./api-gateway
            test-command: npm run test && npm run test:integration
          - test-group: user-service
            working-directory: ./services/user-service
            test-command: npm run test:coverage
          - test-group: product-service
            working-directory: ./services/product-service
            test-command: npm run test:coverage
          - test-group: payment-service
            working-directory: ./services/payment-service
            test-command: npm run test:coverage

    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 📦 Install dependencies
        working-directory: ${{ matrix.working-directory }}
        run: |
          npm ci

      - name: 🏃 Run tests
        working-directory: ${{ matrix.working-directory }}
        env:
          DATABASE_URL: postgresql://test:test@localhost:5432/testdb
          REDIS_URL: redis://localhost:6379
          NODE_ENV: test
        run: ${{ matrix.test-command }}

      - name: 📊 Upload test coverage
        uses: codecov/codecov-action@v4
        with:
          file: ${{ matrix.working-directory }}/coverage/lcov.info
          flags: ${{ matrix.test-group }}
          name: ${{ matrix.test-group }}-coverage

  # Stage 3: End-to-End Testing
  e2e-tests:
    name: 🎭 End-to-End Tests
    runs-on: ubuntu-latest
    needs: [code-quality, unit-integration-tests]
    if: always() && needs.code-quality.outputs.frontend-changed == 'true'
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: 🐳 Build Docker images
        run: |
          docker-compose -f docker-compose.test.yml build

      - name: 🚀 Start test environment
        run: |
          docker-compose -f docker-compose.test.yml up -d
          sleep 30  # Wait for services to be ready

      - name: 🔄 Wait for services
        run: |
          ./scripts/wait-for-services.sh

      - name: 📦 Install Cypress dependencies
        working-directory: ./frontend
        run: |
          npm ci

      - name: 🎭 Run Cypress E2E tests
        working-directory: ./frontend
        run: |
          npm run test:e2e
        env:
          CYPRESS_BASE_URL: http://localhost:3000

      - name: 📊 Upload E2E test artifacts
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: cypress-screenshots
          path: frontend/cypress/screenshots

      - name: 📊 Upload E2E test videos
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: cypress-videos
          path: frontend/cypress/videos

      - name: 🧹 Cleanup test environment
        if: always()
        run: |
          docker-compose -f docker-compose.test.yml down -v

  # Stage 4: Performance Testing
  performance-tests:
    name: ⚡ Performance Tests
    runs-on: ubuntu-latest
    needs: [code-quality, unit-integration-tests]
    if: always() && github.event_name == 'push' && github.ref == 'refs/heads/main'
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🐳 Start performance test environment
        run: |
          docker-compose -f docker-compose.perf.yml up -d
          sleep 60  # Wait for full startup

      - name: 📊 Run Lighthouse CI
        run: |
          npm install -g @lhci/cli
          lhci autorun
        env:
          LHCI_GITHUB_APP_TOKEN: ${{ secrets.LHCI_GITHUB_APP_TOKEN }}

      - name: 🚀 Run K6 load tests
        run: |
          docker run --rm -i --network host grafana/k6:latest run - < scripts/load-test.js

      - name: 📊 Upload performance reports
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: performance-reports
          path: |
            .lighthouseci/
            performance-results.json

  # Stage 5: Security Testing
  security-tests:
    name: 🔒 Security Testing
    runs-on: ubuntu-latest
    needs: code-quality
    if: always()
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔍 Run Trivy vulnerability scanner
        uses: aquasecurity/trivy-action@master
        with:
          scan-type: 'fs'
          ignore-unfixed: true
          format: 'sarif'
          output: 'trivy-results.sarif'

      - name: 📊 Upload Trivy scan results
        uses: github/codeql-action/upload-sarif@v3
        with:
          sarif_file: 'trivy-results.sarif'

      - name: 🔍 Run CodeQL Analysis
        uses: github/codeql-action/init@v3
        with:
          languages: javascript, typescript

      - name: 🔍 Perform CodeQL Analysis
        uses: github/codeql-action/analyze@v3

      - name: 🔒 Run OWASP ZAP Baseline Scan
        if: github.event_name == 'push'
        run: |
          docker run -v $(pwd):/zap/wrk/:rw \
            -t owasp/zap2docker-stable:latest \
            zap-baseline.py -t http://localhost:3000 \
            -g gen.conf -r zap-report.html

  # Stage 6: Build Validation
  build-validation:
    name: 🏗️ Build Validation
    runs-on: ubuntu-latest
    needs: [unit-integration-tests]
    if: always() && !cancelled()
    
    strategy:
      matrix:
        component: [frontend, api-gateway, user-service, product-service, payment-service]
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      - name: 🐳 Build Docker image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: Dockerfile.${{ matrix.component }}
          push: false
          tags: test/${{ matrix.component }}:latest
          cache-from: type=gha
          cache-to: type=gha,mode=max

      - name: 🔍 Test Docker image
        run: |
          docker run --rm test/${{ matrix.component }}:latest --version || true
```

### Step 5: Performance Testing Scripts

**File: `scripts/load-test.js`** (K6 Performance Test):
```javascript
import http from 'k6/http';
import { check, sleep } from 'k6';
import { Rate } from 'k6/metrics';

// Custom metrics
export let errorRate = new Rate('errors');

// Test configuration
export let options = {
  stages: [
    { duration: '30s', target: 10 },  // Warm up
    { duration: '60s', target: 50 },  // Ramp up
    { duration: '120s', target: 100 }, // Steady state
    { duration: '60s', target: 50 },  // Ramp down
    { duration: '30s', target: 0 },   // Cool down
  ],
  thresholds: {
    http_req_duration: ['p(95)<2000'], // 95% of requests under 2s
    http_req_failed: ['rate<0.05'],    // Error rate under 5%
    errors: ['rate<0.1'],              // Custom error rate under 10%
  },
};

const BASE_URL = 'http://localhost:4000';

// Test scenarios
export default function () {
  // Test 1: Health Check
  let healthRes = http.get(`${BASE_URL}/health`);
  check(healthRes, {
    'health check status is 200': (r) => r.status === 200,
    'health check response time < 500ms': (r) => r.timings.duration < 500,
  }) || errorRate.add(1);

  sleep(1);

  // Test 2: API Gateway routing
  let apiRes = http.get(`${BASE_URL}/api/v1/products`, {
    headers: { 'Accept': 'application/json' },
  });
  check(apiRes, {
    'API response status is 200': (r) => r.status === 200,
    'API response has products': (r) => JSON.parse(r.body).products !== undefined,
    'API response time < 1000ms': (r) => r.timings.duration < 1000,
  }) || errorRate.add(1);

  sleep(1);

  // Test 3: User authentication flow
  let loginPayload = JSON.stringify({
    email: 'test@example.com',
    password: 'testpassword123'
  });

  let loginRes = http.post(`${BASE_URL}/api/v1/auth/login`, loginPayload, {
    headers: { 'Content-Type': 'application/json' },
  });
  
  check(loginRes, {
    'login response status is 200 or 401': (r) => [200, 401].includes(r.status),
    'login response time < 1500ms': (r) => r.timings.duration < 1500,
  }) || errorRate.add(1);

  sleep(2);

  // Test 4: Database intensive operation
  let productsRes = http.get(`${BASE_URL}/api/v1/products?limit=50&sort=price`);
  check(productsRes, {
    'products query status is 200': (r) => r.status === 200,
    'products query response time < 2000ms': (r) => r.timings.duration < 2000,
  }) || errorRate.add(1);

  sleep(1);
}

// Lifecycle hooks
export function setup() {
  console.log('🚀 Starting performance tests...');
  
  // Warm up the application
  let warmupRes = http.get(`${BASE_URL}/health`);
  if (warmupRes.status !== 200) {
    throw new Error('Application is not ready for performance testing');
  }
  
  return { timestamp: new Date().toISOString() };
}

export function teardown(data) {
  console.log(`✅ Performance tests completed at ${new Date().toISOString()}`);
  console.log(`Started at: ${data.timestamp}`);
}
```

## 🚀 Fase 3: CD Pipeline - Deployment (75 min)

### Step 6: Multi-Environment Deployment Pipeline

**File: `.github/workflows/cd-deployment.yml`**
```yaml
name: 🚀 Continuous Deployment Pipeline

on:
  push:
    branches: [main]
    tags: ['v*']
  workflow_run:
    workflows: ["🧪 Comprehensive Testing Pipeline"]
    types: [completed]
    branches: [main]

env:
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}

jobs:
  # Prerequisite: Ensure all tests pass
  check-tests:
    name: ✅ Verify Test Results
    runs-on: ubuntu-latest
    if: github.event.workflow_run.conclusion == 'success' || github.event_name == 'push'
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: ✅ Tests passed
        run: echo "All tests passed, proceeding with deployment"

  # Stage 1: Build and Push Images
  build-and-push:
    name: 🏗️ Build & Push Images
    runs-on: ubuntu-latest
    needs: check-tests
    outputs:
      image-tag: ${{ steps.meta.outputs.tags }}
      image-digest: ${{ steps.build.outputs.digest }}
      
    strategy:
      matrix:
        component: [frontend, api-gateway, user-service, product-service, payment-service]
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      - name: 🔐 Login to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}

      - name: 📝 Extract metadata
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}/${{ matrix.component }}
          tags: |
            type=ref,event=branch
            type=ref,event=pr
            type=semver,pattern={{version}}
            type=semver,pattern={{major}}.{{minor}}
            type=sha,prefix={{branch}}-
            type=raw,value=latest,enable={{is_default_branch}}

      - name: 🏗️ Build and push Docker image
        id: build
        uses: docker/build-push-action@v5
        with:
          context: .
          file: Dockerfile.${{ matrix.component }}
          push: true
          tags: ${{ steps.meta.outputs.tags }}
          labels: ${{ steps.meta.outputs.labels }}
          cache-from: type=gha
          cache-to: type=gha,mode=max
          platforms: linux/amd64,linux/arm64

      - name: 🔒 Sign container image
        uses: sigstore/cosign-installer@v3
        with:
          cosign-release: 'v2.2.0'

      - name: ✍️ Sign the published Docker image
        env:
          COSIGN_EXPERIMENTAL: 1
        run: |
          echo "${{ steps.meta.outputs.tags }}" | xargs -I {} cosign sign --yes {}@${{ steps.build.outputs.digest }}

  # Stage 2: Security Scanning of Images
  security-scan-images:
    name: 🔍 Security Scan Images
    runs-on: ubuntu-latest
    needs: build-and-push
    
    strategy:
      matrix:
        component: [frontend, api-gateway, user-service, product-service, payment-service]
    
    steps:
      - name: 🔍 Run Trivy vulnerability scanner
        uses: aquasecurity/trivy-action@master
        with:
          image-ref: ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}/${{ matrix.component }}:latest
          format: 'sarif'
          output: 'trivy-results-${{ matrix.component }}.sarif'

      - name: 📊 Upload Trivy scan results
        uses: github/codeql-action/upload-sarif@v3
        with:
          sarif_file: 'trivy-results-${{ matrix.component }}.sarif'

  # Stage 3: Deploy to Staging
  deploy-staging:
    name: 🎭 Deploy to Staging
    runs-on: ubuntu-latest
    needs: [build-and-push, security-scan-images]
    environment:
      name: staging
      url: https://staging.ecommerce.example.com
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔧 Configure kubectl
        uses: azure/setup-kubectl@v3
        with:
          version: 'v1.28.0'

      - name: 🔐 Setup Kubernetes config
        run: |
          mkdir -p $HOME/.kube
          echo "${{ secrets.KUBE_CONFIG_STAGING }}" | base64 -d > $HOME/.kube/config

      - name: 🏗️ Install Helm
        uses: azure/setup-helm@v3
        with:
          version: '3.12.0'

      - name: 🚀 Deploy to staging with Helm
        run: |
          helm upgrade --install ecommerce-staging ./infrastructure/helm \
            --namespace staging \
            --create-namespace \
            --set image.tag=${{ github.sha }} \
            --set image.registry=${{ env.REGISTRY }} \
            --set environment=staging \
            --set ingress.host=staging.ecommerce.example.com \
            --set database.connectionString="${{ secrets.DATABASE_URL_STAGING }}" \
            --set redis.connectionString="${{ secrets.REDIS_URL_STAGING }}" \
            --wait --timeout=600s

      - name: 🔄 Verify deployment
        run: |
          kubectl rollout status deployment/frontend -n staging --timeout=300s
          kubectl rollout status deployment/api-gateway -n staging --timeout=300s
          kubectl rollout status deployment/user-service -n staging --timeout=300s
          kubectl rollout status deployment/product-service -n staging --timeout=300s
          kubectl rollout status deployment/payment-service -n staging --timeout=300s

      - name: 🧪 Run smoke tests
        run: |
          sleep 30  # Wait for services to be fully ready
          curl -f https://staging.ecommerce.example.com/health
          curl -f https://staging.ecommerce.example.com/api/v1/health

  # Stage 4: Integration Tests on Staging
  staging-tests:
    name: 🧪 Staging Integration Tests
    runs-on: ubuntu-latest
    needs: deploy-staging
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🏗️ Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'

      - name: 📦 Install test dependencies
        run: |
          npm install -g newman

      - name: 🧪 Run Postman collection tests
        run: |
          newman run tests/postman/staging-integration-tests.json \
            --environment tests/postman/staging-environment.json \
            --reporters cli,json \
            --reporter-json-export staging-test-results.json

      - name: 📊 Upload test results
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: staging-test-results
          path: staging-test-results.json

  # Stage 5: Production Deployment (with approval)
  deploy-production:
    name: 🏭 Deploy to Production
    runs-on: ubuntu-latest
    needs: [deploy-staging, staging-tests]
    if: github.ref == 'refs/heads/main' && github.event_name == 'push'
    environment:
      name: production
      url: https://ecommerce.example.com
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔧 Configure kubectl
        uses: azure/setup-kubectl@v3
        with:
          version: 'v1.28.0'

      - name: 🔐 Setup Kubernetes config
        run: |
          mkdir -p $HOME/.kube
          echo "${{ secrets.KUBE_CONFIG_PRODUCTION }}" | base64 -d > $HOME/.kube/config

      - name: 🏗️ Install Helm
        uses: azure/setup-helm@v3
        with:
          version: '3.12.0'

      - name: 📊 Pre-deployment health check
        run: |
          kubectl get pods -n production
          kubectl top nodes

      - name: 🚀 Blue-Green Deployment
        run: |
          # Deploy to green environment
          helm upgrade --install ecommerce-green ./infrastructure/helm \
            --namespace production \
            --set image.tag=${{ github.sha }} \
            --set image.registry=${{ env.REGISTRY }} \
            --set environment=production \
            --set deployment.type=green \
            --set ingress.host=green.ecommerce.example.com \
            --set database.connectionString="${{ secrets.DATABASE_URL_PRODUCTION }}" \
            --set redis.connectionString="${{ secrets.REDIS_URL_PRODUCTION }}" \
            --wait --timeout=600s

      - name: 🧪 Production smoke tests
        run: |
          sleep 60  # Wait for full startup
          curl -f https://green.ecommerce.example.com/health
          curl -f https://green.ecommerce.example.com/api/v1/health
          
          # Run quick integration tests
          newman run tests/postman/production-smoke-tests.json \
            --environment tests/postman/green-environment.json

      - name: 🔄 Switch traffic to green
        run: |
          # Update main ingress to point to green deployment
          kubectl patch ingress main-ingress -n production \
            -p '{"spec":{"rules":[{"host":"ecommerce.example.com","http":{"paths":[{"path":"/","pathType":"Prefix","backend":{"service":{"name":"ecommerce-green","port":{"number":80}}}}]}}]}}'

      - name: ⏱️ Monitor deployment
        run: |
          sleep 120  # Monitor for 2 minutes
          kubectl get pods -n production
          kubectl logs -l app=frontend -n production --tail=50

      - name: 🧹 Cleanup old blue deployment
        run: |
          # Remove old blue deployment after successful switch
          helm uninstall ecommerce-blue -n production || true

  # Stage 6: Post-Deployment Monitoring
  post-deployment-monitoring:
    name: 📊 Post-Deployment Monitoring
    runs-on: ubuntu-latest
    needs: deploy-production
    if: always() && needs.deploy-production.result == 'success'
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 📊 Setup monitoring alerts
        run: |
          # Send deployment notification to Slack
          curl -X POST -H 'Content-type: application/json' \
            --data '{"text":"🚀 Production deployment completed successfully for commit ${{ github.sha }}"}' \
            ${{ secrets.SLACK_WEBHOOK_URL }}

      - name: 🔍 Monitor application metrics
        run: |
          # Wait and check metrics for 5 minutes
          for i in {1..5}; do
            echo "Monitoring cycle $i/5"
            curl -s https://ecommerce.example.com/metrics | grep -E "(response_time|error_rate|active_users)"
            sleep 60
          done

      - name: 📊 Generate deployment report
        run: |
          cat > deployment-report.md << EOF
          # 🚀 Deployment Report
          
          **Commit:** ${{ github.sha }}
          **Branch:** ${{ github.ref_name }}
          **Deployed at:** $(date -u +"%Y-%m-%d %H:%M:%S UTC")
          **Environment:** Production
          
          ## ✅ Services Deployed
          - Frontend
          - API Gateway  
          - User Service
          - Product Service
          - Payment Service
          
          ## 📊 Health Checks
          - Application: ✅ Healthy
          - Database: ✅ Connected
          - Cache: ✅ Available
          
          ## 🔗 Links
          - [Production URL](https://ecommerce.example.com)
          - [Monitoring Dashboard](https://grafana.example.com)
          - [Logs](https://logs.example.com)
          EOF

      - name: 📊 Upload deployment report
        uses: actions/upload-artifact@v4
        with:
          name: deployment-report
          path: deployment-report.md

  # Stage 7: Automated Rollback (if needed)
  automated-rollback:
    name: ⏪ Automated Rollback
    runs-on: ubuntu-latest
    needs: [deploy-production, post-deployment-monitoring]
    if: failure() && needs.deploy-production.result == 'success'
    environment:
      name: production-rollback
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔧 Configure kubectl
        uses: azure/setup-kubectl@v3
        with:
          version: 'v1.28.0'

      - name: 🔐 Setup Kubernetes config
        run: |
          mkdir -p $HOME/.kube
          echo "${{ secrets.KUBE_CONFIG_PRODUCTION }}" | base64 -d > $HOME/.kube/config

      - name: ⏪ Rollback deployment
        run: |
          echo "🚨 Issues detected, initiating rollback..."
          
          # Get previous successful deployment
          PREVIOUS_REVISION=$(helm history ecommerce-green -n production --max 2 -o json | jq -r '.[1].revision')
          
          # Rollback to previous version
          helm rollback ecommerce-green $PREVIOUS_REVISION -n production --wait --timeout=300s

      - name: 📢 Notify rollback
        run: |
          curl -X POST -H 'Content-type: application/json' \
            --data '{"text":"🚨 ALERT: Production rollback initiated for commit ${{ github.sha }}"}' \
            ${{ secrets.SLACK_WEBHOOK_URL }}
```

## 🔧 Fase 4: Advanced Features & Monitoring (45 min)

### Step 7: Infrastructure as Code

**File: `infrastructure/helm/Chart.yaml`**
```yaml
apiVersion: v2
name: ecommerce-platform
description: Enterprise e-commerce platform Helm chart
type: application
version: 1.0.0
appVersion: "1.0.0"
keywords:
  - ecommerce
  - microservices
  - nodejs
maintainers:
  - name: DevOps Team
    email: devops@example.com
```

**File: `infrastructure/helm/values.yaml`**
```yaml
# Global configuration
global:
  imageRegistry: ghcr.io
  imagePullSecrets: []
  storageClass: ""

# Environment configuration
environment: production
replicaCount: 3

# Image configuration
image:
  registry: ghcr.io
  repository: your-org/enterprise-ecommerce-platform
  tag: "latest"
  pullPolicy: IfNotPresent

# Service configuration
service:
  type: ClusterIP
  port: 80

# Ingress configuration
ingress:
  enabled: true
  className: nginx
  annotations:
    nginx.ingress.kubernetes.io/rewrite-target: /
    cert-manager.io/cluster-issuer: letsencrypt-prod
  host: ecommerce.example.com
  tls:
    enabled: true
    secretName: ecommerce-tls

# Frontend configuration
frontend:
  replicaCount: 2
  resources:
    limits:
      cpu: 500m
      memory: 512Mi
    requests:
      cpu: 250m
      memory: 256Mi
  nodeSelector: {}
  tolerations: []
  affinity: {}

# API Gateway configuration
apiGateway:
  replicaCount: 3
  resources:
    limits:
      cpu: 1000m
      memory: 1Gi
    requests:
      cpu: 500m
      memory: 512Mi

# Microservices configuration
microservices:
  userService:
    replicaCount: 2
    resources:
      limits:
        cpu: 500m
        memory: 512Mi
      requests:
        cpu: 250m
        memory: 256Mi
  
  productService:
    replicaCount: 3
    resources:
      limits:
        cpu: 750m
        memory: 768Mi
      requests:
        cpu: 375m
        memory: 384Mi
  
  paymentService:
    replicaCount: 2
    resources:
      limits:
        cpu: 500m
        memory: 512Mi
      requests:
        cpu: 250m
        memory: 256Mi

# Database configuration
database:
  enabled: true
  connectionString: ""
  ssl: true
  poolSize: 20

# Redis configuration
redis:
  enabled: true
  connectionString: ""
  maxClients: 1000

# Monitoring configuration
monitoring:
  enabled: true
  prometheus:
    enabled: true
  grafana:
    enabled: true
  alerts:
    enabled: true

# Autoscaling configuration
autoscaling:
  enabled: true
  minReplicas: 2
  maxReplicas: 10
  targetCPUUtilizationPercentage: 70
  targetMemoryUtilizationPercentage: 80

# Security configuration
security:
  networkPolicies:
    enabled: true
  podSecurityPolicy:
    enabled: true
  rbac:
    create: true
```

### Step 8: Monitoring & Alerting Setup

**File: `.github/workflows/monitoring-setup.yml`**
```yaml
name: 📊 Monitoring & Alerting Setup

on:
  workflow_dispatch:
  schedule:
    - cron: '0 */6 * * *'  # Every 6 hours

jobs:
  setup-monitoring:
    name: 📊 Setup Monitoring Stack
    runs-on: ubuntu-latest
    environment: production
    
    steps:
      - name: 📥 Checkout code
        uses: actions/checkout@v4

      - name: 🔧 Configure kubectl
        uses: azure/setup-kubectl@v3
        with:
          version: 'v1.28.0'

      - name: 🔐 Setup Kubernetes config
        run: |
          mkdir -p $HOME/.kube
          echo "${{ secrets.KUBE_CONFIG_PRODUCTION }}" | base64 -d > $HOME/.kube/config

      - name: 🏗️ Install Helm
        uses: azure/setup-helm@v3
        with:
          version: '3.12.0'

      - name: 📊 Install Prometheus
        run: |
          helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
          helm repo update
          
          helm upgrade --install prometheus prometheus-community/kube-prometheus-stack \
            --namespace monitoring \
            --create-namespace \
            --set prometheus.prometheusSpec.retention=30d \
            --set prometheus.prometheusSpec.storageSpec.volumeClaimTemplate.spec.resources.requests.storage=50Gi \
            --set grafana.adminPassword="${{ secrets.GRAFANA_ADMIN_PASSWORD }}" \
            --set alertmanager.config.global.slack_api_url="${{ secrets.SLACK_WEBHOOK_URL }}"

      - name: 📈 Install Grafana Dashboards
        run: |
          kubectl apply -f infrastructure/monitoring/dashboards/ -n monitoring

      - name: 🚨 Setup AlertManager Rules
        run: |
          kubectl apply -f infrastructure/monitoring/alerts/ -n monitoring

      - name: 🔍 Verify monitoring stack
        run: |
          kubectl get pods -n monitoring
          kubectl get svc -n monitoring
```

## ✅ Verifica Completamento

### Checklist Finale

- [ ] **Repository Structure**: Progetto multi-service strutturato
- [ ] **Docker Configuration**: Multi-stage builds ottimizzati
- [ ] **Testing Pipeline**: Unit, integration, E2E, performance, security
- [ ] **Code Quality**: ESLint, Prettier, TypeScript, security scanning
- [ ] **Build Validation**: Multi-platform Docker builds
- [ ] **Deployment Pipeline**: Staging e production con approval
- [ ] **Blue-Green Deployment**: Zero-downtime deployments
- [ ] **Infrastructure as Code**: Helm charts e Kubernetes manifests
- [ ] **Monitoring Setup**: Prometheus, Grafana, AlertManager
- [ ] **Automated Rollback**: Fallback automatico in caso di problemi
- [ ] **Security**: Image scanning, OWASP ZAP, CodeQL
- [ ] **Performance**: K6 load testing, Lighthouse CI

### Advanced CI/CD Features Implementate

1. **Multi-Stage Testing**: Quality gates sequenziali
2. **Matrix Builds**: Testing parallelo su multiple componenti
3. **Performance Testing**: Load testing automatizzato
4. **Security Integration**: Multiple tools di security scanning
5. **Blue-Green Deployment**: Zero-downtime production deployments
6. **Automated Rollback**: Recovery automatico da fallimenti
7. **Infrastructure as Code**: Gestione infrastruttura via Helm
8. **Comprehensive Monitoring**: Stack completo di observability

## 🎯 Obiettivi Raggiunti

Completando questo esercizio hai implementato:

- **Enterprise CI/CD Pipeline** con testing completo
- **Multi-Environment Deployment** con approval workflows
- **Security-First Approach** con scanning automatico
- **Performance Monitoring** e load testing
- **Blue-Green Deployment Strategy** per zero-downtime
- **Infrastructure as Code** con Helm e Kubernetes
- **Automated Recovery** e rollback mechanisms
- **Comprehensive Monitoring** con Prometheus e Grafana

## 🚀 Prossimi Passi

- Implementa canary deployments per release graduali
- Aggiungi chaos engineering per testing resilienza
- Sviluppa custom GitHub Actions per workflow specifici
- Integra feature flags per deployment controlled
- Implementa multi-cloud deployment strategies

## 📚 Risorse Aggiuntive

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Kubernetes Best Practices](https://kubernetes.io/docs/concepts/overview/working-with-objects/common-labels/)
- [Helm Documentation](https://helm.sh/docs/)
- [Prometheus Monitoring](https://prometheus.io/docs/introduction/overview/)
