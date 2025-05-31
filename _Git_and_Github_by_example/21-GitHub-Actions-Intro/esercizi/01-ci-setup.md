# Esercizio 1: CI Setup - Configurazione Pipeline CI/CD

## Obiettivo

Creare da zero una pipeline CI/CD completa per un'applicazione web, implementando best practices per testing, building, security scanning e deployment automatico.

## Scenario

Sei stato incaricato di implementare una pipeline CI/CD per una nuova applicazione web Node.js con frontend React e backend Express. L'applicazione deve essere deployata su AWS ECS con database PostgreSQL.

## Requisiti del Progetto

### 1. **Struttura dell'Applicazione**
```
my-web-app/
├── frontend/          # React application
├── backend/           # Express.js API
├── database/          # PostgreSQL migrations
├── docker/           # Docker configurations
├── docs/             # Documentation
└── .github/          # GitHub Actions workflows
```

### 2. **Stack Tecnologico**
- **Frontend**: React 18, TypeScript, Vite
- **Backend**: Node.js, Express, TypeScript
- **Database**: PostgreSQL 15
- **Infrastructure**: AWS ECS, RDS, CloudFront
- **Monitoring**: CloudWatch, Datadog

## Task 1: Setup Base del Repository

### Istruzioni
1. Crea la struttura di cartelle richiesta
2. Inizializza package.json per frontend e backend
3. Configura TypeScript per entrambi i progetti
4. Aggiungi file Docker per containerizzazione

### Soluzione Proposta

#### Frontend Package.json
```json
{
  "name": "my-web-app-frontend",
  "version": "1.0.0",
  "type": "module",
  "scripts": {
    "dev": "vite",
    "build": "tsc && vite build",
    "lint": "eslint . --ext ts,tsx --report-unused-disable-directives --max-warnings 0",
    "lint:fix": "eslint . --ext ts,tsx --fix",
    "preview": "vite preview",
    "test": "vitest",
    "test:coverage": "vitest --coverage",
    "test:ui": "vitest --ui",
    "e2e": "playwright test",
    "e2e:headed": "playwright test --headed"
  },
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-router-dom": "^6.8.0",
    "axios": "^1.3.0",
    "@tanstack/react-query": "^4.24.0"
  },
  "devDependencies": {
    "@types/react": "^18.0.27",
    "@types/react-dom": "^18.0.10",
    "@typescript-eslint/eslint-plugin": "^5.54.0",
    "@typescript-eslint/parser": "^5.54.0",
    "@vitejs/plugin-react": "^3.1.0",
    "eslint": "^8.35.0",
    "eslint-plugin-react-hooks": "^4.6.0",
    "eslint-plugin-react-refresh": "^0.3.4",
    "typescript": "^4.9.3",
    "vite": "^4.1.0",
    "vitest": "^0.28.5",
    "@vitest/coverage-c8": "^0.28.5",
    "@vitest/ui": "^0.28.5",
    "@playwright/test": "^1.31.0"
  }
}
```

#### Backend Package.json
```json
{
  "name": "my-web-app-backend",
  "version": "1.0.0",
  "scripts": {
    "dev": "nodemon src/index.ts",
    "build": "tsc",
    "start": "node dist/index.js",
    "lint": "eslint src --ext .ts",
    "lint:fix": "eslint src --ext .ts --fix",
    "test": "jest",
    "test:watch": "jest --watch",
    "test:coverage": "jest --coverage",
    "test:integration": "jest --config jest.integration.config.js",
    "migrate": "npx typeorm migration:run",
    "migrate:revert": "npx typeorm migration:revert"
  },
  "dependencies": {
    "express": "^4.18.2",
    "cors": "^2.8.5",
    "helmet": "^6.0.1",
    "compression": "^1.7.4",
    "winston": "^3.8.2",
    "joi": "^17.7.0",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.0",
    "typeorm": "^0.3.12",
    "pg": "^8.9.0",
    "redis": "^4.6.4",
    "express-rate-limit": "^6.7.0"
  },
  "devDependencies": {
    "@types/express": "^4.17.17",
    "@types/cors": "^2.8.13",
    "@types/compression": "^1.7.2",
    "@types/jsonwebtoken": "^9.0.1",
    "@types/bcrypt": "^5.0.0",
    "@types/pg": "^8.6.6",
    "@types/node": "^18.14.2",
    "@typescript-eslint/eslint-plugin": "^5.54.0",
    "@typescript-eslint/parser": "^5.54.0",
    "eslint": "^8.35.0",
    "typescript": "^4.9.5",
    "nodemon": "^2.0.20",
    "jest": "^29.4.3",
    "@types/jest": "^29.4.0",
    "ts-jest": "^29.0.5",
    "supertest": "^6.3.3",
    "@types/supertest": "^2.0.12"
  }
}
```

## Task 2: Workflow CI/CD Base

### Istruzioni
Crea un workflow GitHub Actions che implementi:
1. Trigger sui push e PR
2. Build paralleli per frontend e backend
3. Test automatizzati
4. Security scanning
5. Deploy condizionale

### Soluzione Proposta

```yaml
# .github/workflows/ci-cd.yml
name: CI/CD Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  workflow_dispatch:

env:
  NODE_VERSION: '18'
  AWS_REGION: us-east-1
  ECR_REGISTRY: 123456789012.dkr.ecr.us-east-1.amazonaws.com

jobs:
  # Detect changes
  changes:
    runs-on: ubuntu-latest
    outputs:
      frontend: ${{ steps.changes.outputs.frontend }}
      backend: ${{ steps.changes.outputs.backend }}
      infrastructure: ${{ steps.changes.outputs.infrastructure }}
    steps:
      - uses: actions/checkout@v4
      - uses: dorny/paths-filter@v2
        id: changes
        with:
          filters: |
            frontend:
              - 'frontend/**'
              - 'package.json'
            backend:
              - 'backend/**'
              - 'package.json'
            infrastructure:
              - 'infrastructure/**'
              - 'docker/**'

  # Lint and security checks
  code-quality:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'

      - name: Install dependencies
        run: |
          npm ci --prefix frontend
          npm ci --prefix backend

      - name: Lint frontend
        if: needs.changes.outputs.frontend == 'true'
        run: npm run lint --prefix frontend

      - name: Lint backend
        if: needs.changes.outputs.backend == 'true'
        run: npm run lint --prefix backend

      - name: Security audit
        run: |
          npm audit --prefix frontend --audit-level moderate
          npm audit --prefix backend --audit-level moderate

      - name: Check for secrets
        uses: trufflesecurity/trufflehog@main
        with:
          path: ./
          base: main
          head: HEAD

  # Frontend tests and build
  frontend-ci:
    needs: [changes, code-quality]
    if: needs.changes.outputs.frontend == 'true'
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
          cache-dependency-path: frontend/package-lock.json

      - name: Install dependencies
        run: npm ci --prefix frontend

      - name: Run unit tests
        run: npm run test:coverage --prefix frontend

      - name: Upload test coverage
        uses: codecov/codecov-action@v3
        with:
          file: ./frontend/coverage/lcov.info
          flags: frontend

      - name: Build application
        run: npm run build --prefix frontend

      - name: Install Playwright
        run: npx playwright install --with-deps

      - name: Run E2E tests
        run: npm run e2e --prefix frontend

      - name: Upload E2E artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: playwright-report
          path: frontend/playwright-report/

      - name: Build Docker image
        run: |
          docker build -f docker/frontend.Dockerfile \
            -t frontend:${{ github.sha }} \
            --build-arg BUILD_ENV=production \
            .

      - name: Save Docker image
        run: docker save frontend:${{ github.sha }} | gzip > frontend-image.tar.gz

      - name: Upload Docker image artifact
        uses: actions/upload-artifact@v3
        with:
          name: frontend-image
          path: frontend-image.tar.gz

  # Backend tests and build
  backend-ci:
    needs: [changes, code-quality]
    if: needs.changes.outputs.backend == 'true'
    runs-on: ubuntu-latest
    services:
      postgres:
        image: postgres:15
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
        image: redis:7
        options: >-
          --health-cmd "redis-cli ping"
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
        ports:
          - 6379:6379

    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: ${{ env.NODE_VERSION }}
          cache: 'npm'
          cache-dependency-path: backend/package-lock.json

      - name: Install dependencies
        run: npm ci --prefix backend

      - name: Run database migrations
        run: npm run migrate --prefix backend
        env:
          DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb

      - name: Run unit tests
        run: npm run test:coverage --prefix backend
        env:
          DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb
          REDIS_URL: redis://localhost:6379

      - name: Run integration tests
        run: npm run test:integration --prefix backend
        env:
          DATABASE_URL: postgresql://postgres:postgres@localhost:5432/testdb
          REDIS_URL: redis://localhost:6379

      - name: Upload test coverage
        uses: codecov/codecov-action@v3
        with:
          file: ./backend/coverage/lcov.info
          flags: backend

      - name: Build application
        run: npm run build --prefix backend

      - name: Build Docker image
        run: |
          docker build -f docker/backend.Dockerfile \
            -t backend:${{ github.sha }} \
            --build-arg BUILD_ENV=production \
            .

      - name: Run security scan
        uses: aquasecurity/trivy-action@master
        with:
          image-ref: backend:${{ github.sha }}
          format: 'sarif'
          output: 'trivy-results.sarif'

      - name: Upload security scan results
        uses: github/codeql-action/upload-sarif@v2
        if: always()
        with:
          sarif_file: 'trivy-results.sarif'

      - name: Save Docker image
        run: docker save backend:${{ github.sha }} | gzip > backend-image.tar.gz

      - name: Upload Docker image artifact
        uses: actions/upload-artifact@v3
        with:
          name: backend-image
          path: backend-image.tar.gz

  # Deploy to staging
  deploy-staging:
    needs: [frontend-ci, backend-ci]
    if: github.ref == 'refs/heads/develop'
    runs-on: ubuntu-latest
    environment:
      name: staging
      url: https://staging.myapp.com
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Configure AWS credentials
        uses: aws-actions/configure-aws-credentials@v2
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: ${{ env.AWS_REGION }}

      - name: Login to Amazon ECR
        id: login-ecr
        uses: aws-actions/amazon-ecr-login@v1

      - name: Download Docker images
        uses: actions/download-artifact@v3
        with:
          name: frontend-image

      - name: Download Docker images
        uses: actions/download-artifact@v3
        with:
          name: backend-image

      - name: Load and push images
        run: |
          docker load < frontend-image.tar.gz
          docker load < backend-image.tar.gz
          
          docker tag frontend:${{ github.sha }} $ECR_REGISTRY/frontend:staging-${{ github.sha }}
          docker tag backend:${{ github.sha }} $ECR_REGISTRY/backend:staging-${{ github.sha }}
          
          docker push $ECR_REGISTRY/frontend:staging-${{ github.sha }}
          docker push $ECR_REGISTRY/backend:staging-${{ github.sha }}

      - name: Deploy to ECS
        run: |
          # Update ECS service with new images
          aws ecs update-service \
            --cluster staging-cluster \
            --service frontend-service \
            --force-new-deployment
          
          aws ecs update-service \
            --cluster staging-cluster \
            --service backend-service \
            --force-new-deployment

      - name: Wait for deployment
        run: |
          aws ecs wait services-stable \
            --cluster staging-cluster \
            --services frontend-service backend-service

      - name: Run smoke tests
        run: |
          curl -f https://staging.myapp.com/health
          curl -f https://staging.myapp.com/api/health

  # Deploy to production
  deploy-production:
    needs: [frontend-ci, backend-ci]
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    environment:
      name: production
      url: https://myapp.com
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Configure AWS credentials
        uses: aws-actions/configure-aws-credentials@v2
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: ${{ env.AWS_REGION }}

      - name: Deploy with blue-green strategy
        run: |
          # Implementation of blue-green deployment
          echo "Implementing blue-green deployment..."
          
          # Get current active environment
          current_env=$(aws elbv2 describe-target-groups \
            --target-group-arns ${{ secrets.TARGET_GROUP_ARN }} \
            --query 'TargetGroups[0].Tags[?Key==`Environment`].Value' \
            --output text)
          
          if [ "$current_env" = "blue" ]; then
            new_env="green"
          else
            new_env="blue"
          fi
          
          echo "Deploying to $new_env environment"
          
          # Update ECS services in new environment
          aws ecs update-service \
            --cluster production-cluster \
            --service $new_env-frontend-service \
            --force-new-deployment
          
          # Wait for deployment to complete
          aws ecs wait services-stable \
            --cluster production-cluster \
            --services $new_env-frontend-service
          
          # Switch load balancer traffic
          aws elbv2 modify-target-group \
            --target-group-arn ${{ secrets.TARGET_GROUP_ARN }} \
            --tags Key=Environment,Value=$new_env

      - name: Post-deployment verification
        run: |
          # Health checks
          for i in {1..10}; do
            if curl -f https://myapp.com/health; then
              echo "Health check passed"
              break
            fi
            sleep 30
          done
          
          # Performance test
          curl -o /dev/null -s -w "%{time_total}\n" https://myapp.com/

  # Notify results
  notify:
    needs: [deploy-staging, deploy-production]
    if: always()
    runs-on: ubuntu-latest
    steps:
      - name: Notify Slack
        uses: 8398a7/action-slack@v3
        with:
          status: ${{ job.status }}
          text: |
            Deployment completed!
            Environment: ${{ github.ref == 'refs/heads/main' && 'production' || 'staging' }}
            Status: ${{ job.status }}
            Commit: ${{ github.sha }}
            Actor: ${{ github.actor }}
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Task 3: Configurazione Docker

### Istruzioni
Crea Dockerfile ottimizzati per frontend e backend con multi-stage builds.

### Soluzione Proposta

#### Frontend Dockerfile
```dockerfile
# docker/frontend.Dockerfile
# Build stage
FROM node:18-alpine AS builder

WORKDIR /app

# Copy package files
COPY frontend/package*.json ./
RUN npm ci --only=production

# Copy source code
COPY frontend/ .

# Build arguments
ARG BUILD_ENV=production
ARG API_URL=https://api.myapp.com

# Set environment variables
ENV NODE_ENV=$BUILD_ENV
ENV VITE_API_URL=$API_URL

# Build application
RUN npm run build

# Production stage
FROM nginx:alpine AS production

# Install security updates
RUN apk update && apk upgrade

# Copy built assets
COPY --from=builder /app/dist /usr/share/nginx/html

# Copy nginx configuration
COPY docker/nginx.conf /etc/nginx/nginx.conf
COPY docker/default.conf /etc/nginx/conf.d/default.conf

# Add healthcheck
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD curl -f http://localhost/ || exit 1

# Expose port
EXPOSE 80

# Start nginx
CMD ["nginx", "-g", "daemon off;"]
```

#### Backend Dockerfile
```dockerfile
# docker/backend.Dockerfile
# Build stage
FROM node:18-alpine AS builder

WORKDIR /app

# Install build dependencies
RUN apk add --no-cache python3 make g++

# Copy package files
COPY backend/package*.json ./
RUN npm ci --only=production

# Copy source code
COPY backend/ .

# Build application
RUN npm run build

# Production stage
FROM node:18-alpine AS production

# Create app user
RUN addgroup -g 1001 -S nodejs
RUN adduser -S nodejs -u 1001

WORKDIR /app

# Install security updates
RUN apk update && apk upgrade

# Copy built application
COPY --from=builder --chown=nodejs:nodejs /app/dist ./dist
COPY --from=builder --chown=nodejs:nodejs /app/node_modules ./node_modules
COPY --from=builder --chown=nodejs:nodejs /app/package.json ./

# Add healthcheck
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD curl -f http://localhost:3000/health || exit 1

# Switch to non-root user
USER nodejs

# Expose port
EXPOSE 3000

# Start application
CMD ["node", "dist/index.js"]
```

## Task 4: Configurazione Infrastructure as Code

### Istruzioni
Crea template Terraform per infrastructure AWS.

### Soluzione Proposta

```hcl
# infrastructure/main.tf
terraform {
  required_version = ">= 1.0"
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
}

# VPC Configuration
module "vpc" {
  source = "terraform-aws-modules/vpc/aws"

  name = "${var.project_name}-vpc"
  cidr = "10.0.0.0/16"

  azs             = ["${var.aws_region}a", "${var.aws_region}b"]
  private_subnets = ["10.0.1.0/24", "10.0.2.0/24"]
  public_subnets  = ["10.0.101.0/24", "10.0.102.0/24"]

  enable_nat_gateway = true
  enable_vpn_gateway = true

  tags = {
    Terraform   = "true"
    Environment = var.environment
  }
}

# ECS Cluster
resource "aws_ecs_cluster" "main" {
  name = "${var.project_name}-cluster"

  configuration {
    execute_command_configuration {
      logging = "OVERRIDE"
      log_configuration {
        cloud_watch_log_group_name = aws_cloudwatch_log_group.ecs.name
      }
    }
  }

  tags = {
    Environment = var.environment
  }
}

# CloudWatch Log Group
resource "aws_cloudwatch_log_group" "ecs" {
  name              = "/ecs/${var.project_name}"
  retention_in_days = 7
}

# Application Load Balancer
resource "aws_lb" "main" {
  name               = "${var.project_name}-alb"
  internal           = false
  load_balancer_type = "application"
  security_groups    = [aws_security_group.alb.id]
  subnets            = module.vpc.public_subnets

  enable_deletion_protection = false

  tags = {
    Environment = var.environment
  }
}

# Security Groups
resource "aws_security_group" "alb" {
  name        = "${var.project_name}-alb-sg"
  description = "Security group for ALB"
  vpc_id      = module.vpc.vpc_id

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Environment = var.environment
  }
}

# ECS Task Definition for Backend
resource "aws_ecs_task_definition" "backend" {
  family                   = "${var.project_name}-backend"
  network_mode             = "awsvpc"
  requires_compatibilities = ["FARGATE"]
  cpu                      = "256"
  memory                   = "512"
  execution_role_arn       = aws_iam_role.ecs_execution_role.arn
  task_role_arn           = aws_iam_role.ecs_task_role.arn

  container_definitions = jsonencode([
    {
      name  = "backend"
      image = "${var.ecr_repository_url}:latest"
      
      portMappings = [
        {
          containerPort = 3000
          hostPort      = 3000
        }
      ]

      environment = [
        {
          name  = "NODE_ENV"
          value = "production"
        },
        {
          name  = "DATABASE_URL"
          value = "postgresql://${aws_db_instance.postgres.username}:${aws_db_instance.postgres.password}@${aws_db_instance.postgres.endpoint}/${aws_db_instance.postgres.db_name}"
        }
      ]

      logConfiguration = {
        logDriver = "awslogs"
        options = {
          awslogs-group         = aws_cloudwatch_log_group.ecs.name
          awslogs-region        = var.aws_region
          awslogs-stream-prefix = "ecs"
        }
      }

      healthCheck = {
        command     = ["CMD-SHELL", "curl -f http://localhost:3000/health || exit 1"]
        interval    = 30
        timeout     = 5
        retries     = 3
        startPeriod = 60
      }
    }
  ])

  tags = {
    Environment = var.environment
  }
}

# RDS PostgreSQL
resource "aws_db_instance" "postgres" {
  identifier             = "${var.project_name}-postgres"
  engine                 = "postgres"
  engine_version         = "15.3"
  instance_class         = "db.t3.micro"
  allocated_storage      = 20
  storage_encrypted      = true
  
  db_name  = var.db_name
  username = var.db_username
  password = var.db_password

  vpc_security_group_ids = [aws_security_group.rds.id]
  db_subnet_group_name   = aws_db_subnet_group.postgres.name

  backup_retention_period = 7
  backup_window          = "03:00-04:00"
  maintenance_window     = "sun:04:00-sun:05:00"

  skip_final_snapshot = true

  tags = {
    Environment = var.environment
  }
}

# Variables
variable "project_name" {
  description = "Name of the project"
  type        = string
  default     = "my-web-app"
}

variable "environment" {
  description = "Environment name"
  type        = string
}

variable "aws_region" {
  description = "AWS region"
  type        = string
  default     = "us-east-1"
}

variable "ecr_repository_url" {
  description = "ECR repository URL"
  type        = string
}

variable "db_name" {
  description = "Database name"
  type        = string
  default     = "myappdb"
}

variable "db_username" {
  description = "Database username"
  type        = string
  default     = "dbuser"
}

variable "db_password" {
  description = "Database password"
  type        = string
  sensitive   = true
}
```

## Task 5: Testing Strategy

### Istruzioni
Implementa una strategia di testing completa con unit, integration e E2E tests.

### Soluzione Proposta

#### Frontend Test Configuration
```typescript
// frontend/vitest.config.ts
import { defineConfig } from 'vitest/config'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
  test: {
    globals: true,
    environment: 'jsdom',
    setupFiles: './src/test/setup.ts',
    coverage: {
      reporter: ['text', 'json', 'html', 'lcov'],
      exclude: [
        'node_modules/',
        'src/test/',
        '**/*.d.ts',
        '**/*.config.*',
        'dist/'
      ],
      thresholds: {
        global: {
          branches: 80,
          functions: 80,
          lines: 80,
          statements: 80
        }
      }
    }
  }
})
```

#### Backend Test Configuration
```javascript
// backend/jest.config.js
module.exports = {
  preset: 'ts-jest',
  testEnvironment: 'node',
  roots: ['<rootDir>/src'],
  testMatch: ['**/__tests__/**/*.ts', '**/?(*.)+(spec|test).ts'],
  collectCoverageFrom: [
    'src/**/*.ts',
    '!src/**/*.d.ts',
    '!src/test/**',
    '!src/migrations/**'
  ],
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
      statements: 80
    }
  },
  setupFilesAfterEnv: ['<rootDir>/src/test/setup.ts']
}
```

## Checklist di Completamento

### ✅ Configurazione Base
- [ ] Struttura repository creata
- [ ] Package.json configurati
- [ ] TypeScript setup completato
- [ ] Docker files creati

### ✅ Pipeline CI/CD
- [ ] Workflow GitHub Actions implementato
- [ ] Build paralleli configurati
- [ ] Testing automatizzato
- [ ] Security scanning attivo
- [ ] Deploy automation implementato

### ✅ Infrastructure
- [ ] Terraform templates creati
- [ ] AWS resources definiti
- [ ] Security groups configurati
- [ ] Monitoring setup

### ✅ Testing
- [ ] Unit tests implementati
- [ ] Integration tests configurati
- [ ] E2E tests setup
- [ ] Coverage reports attivi

## Metriche di Successo

Al completamento dell'esercizio, dovresti avere:

1. **Pipeline Tempo**: < 15 minuti per build completo
2. **Test Coverage**: > 80% per frontend e backend
3. **Security Score**: Zero vulnerabilità critiche
4. **Deployment Time**: < 5 minuti per staging
5. **Uptime**: 99.9% availability target

## Sfide Aggiuntive

### Livello Intermedio
1. Implementa feature flags con LaunchDarkly
2. Aggiungi performance testing con Artillery
3. Configura monitoring con Prometheus/Grafana

### Livello Avanzato
1. Implementa multi-region deployment
2. Aggiungi chaos engineering con Chaos Monkey
3. Configura automated dependency updates

## Soluzioni e Discussione

### Problemi Comuni

**Q: Il workflow impiega troppo tempo**
**A:** Ottimizza utilizzando:
- Matrix builds paralleli
- Docker layer caching
- npm/yarn cache
- Conditional job execution

**Q: I test sono instabili**
**A:** Implementa:
- Retry logic per test flaky
- Seed data consistenti
- Mock per servizi esterni
- Isolation tra test

**Q: Deploy fallisce randomly**
**A:** Aggiungi:
- Health checks più robusti
- Rollback automatico
- Circuit breaker pattern
- Progressive deployment

## Conclusione

Questo esercizio fornisce una base solida per implementare pipeline CI/CD enterprise-grade. Le competenze acquisite includono automation, testing, security, e deployment strategies essenziali per ambienti di produzione moderni.
