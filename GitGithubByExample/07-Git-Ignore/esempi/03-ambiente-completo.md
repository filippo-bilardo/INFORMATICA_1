# Esempio 3: Ambiente di Sviluppo Completo Multi-linguaggio

## Scenario
Configureremo un ambiente di sviluppo completo che include progetti Node.js, Python, Java, e strumenti Docker, con gestione centralizzata del .gitignore e automazione completa.

## Setup Progetto Multi-tecnologia

### 1. Struttura del Progetto
```bash
# Creiamo la struttura completa
mkdir fullstack-platform
cd fullstack-platform

# Inizializziamo Git
git init

# Creiamo la struttura multi-tecnologia
mkdir -p {frontend,backend,mobile,devops,docs,scripts}
mkdir -p frontend/{web,admin}
mkdir -p backend/{api,workers,auth}
mkdir -p mobile/{android,ios}
mkdir -p devops/{docker,kubernetes,terraform}
mkdir -p tools/{scripts,configs,templates}
mkdir -p data/{seeds,migrations,fixtures}
mkdir -p tests/{unit,integration,e2e}
```

### 2. .gitignore Universale e Modulare
```bash
# Creiamo il .gitignore principale
cat > .gitignore << 'EOF'
#########################################
# GITIGNORE UNIVERSALE MULTI-LINGUAGGIO
#########################################

# ===========================================
# FILE DI SISTEMA E IDE
# ===========================================

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
Desktop.ini

# IDE e Editor
.vscode/
.idea/
*.swp
*.swo
*~
.sublime-project
.sublime-workspace
*.code-workspace

# Logs
logs/
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# ===========================================
# LINGUAGGI DI PROGRAMMAZIONE
# ===========================================

# Node.js
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
.pnpm-debug.log*
.npm
.eslintcache
.node_repl_history
*.tgz
.yarn-integrity
.env.local
.env.development.local
.env.test.local
.env.production.local

# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
*.egg-info/
.installed.cfg
*.egg
MANIFEST
.env
.venv
env/
venv/
ENV/
env.bak/
venv.bak/
.coverage
.pytest_cache/
.hypothesis/

# Java
*.class
*.jar
*.war
*.ear
*.zip
*.tar.gz
*.rar
hs_err_pid*
.gradle/
build/
gradle-app.setting
!gradle-wrapper.jar
.gradletasknamecache
target/
.mvn/timing.properties
.mvn/wrapper/maven-wrapper.jar

# ===========================================
# FRAMEWORK SPECIFICI
# ===========================================

# React/Next.js
.next/
out/
build/
dist/
.vercel/

# Vue.js
dist/
node_modules/
.nuxt/

# Angular
dist/
tmp/
out-tsc/
.angular/

# Django
*.log
local_settings.py
db.sqlite3
db.sqlite3-journal
media/
staticfiles/

# Spring Boot
HELP.md
target/
!.mvn/wrapper/maven-wrapper.jar
!**/src/main/**/target/
!**/src/test/**/target/

# ===========================================
# MOBILE DEVELOPMENT
# ===========================================

# Android
*.iml
.gradle
/local.properties
/.idea/caches
/.idea/libraries
/.idea/modules.xml
/.idea/workspace.xml
/.idea/navEditor.xml
/.idea/assetWizardSettings.xml
.DS_Store
/build
/captures
.externalNativeBuild
.cxx
local.properties

# iOS
*.xcodeproj/*
!*.xcodeproj/project.pbxproj
!*.xcodeproj/xcshareddata/
!*.xcworkspace/contents.xcworkspacedata
/*.gcno
DerivedData/
*.hmap
*.ipa
*.dSYM.zip
*.dSYM

# React Native
.metro-health-check*

# ===========================================
# DEVOPS E INFRASTRUTTURA
# ===========================================

# Docker
.dockerignore
docker-compose.override.yml

# Terraform
*.tfstate
*.tfstate.*
.terraform/
.terraform.lock.hcl
*.tfvars
crash.log
crash.*.log

# Kubernetes
*.kubeconfig

# ===========================================
# DATABASE E CACHE
# ===========================================

# Database files
*.sqlite
*.sqlite3
*.db
*.sql

# Redis
dump.rdb

# MongoDB
*.bson

# ===========================================
# SICUREZZA E CONFIGURAZIONI
# ===========================================

# File sensibili
.env
.env.local
.env.production
.env.staging
*.pem
*.key
*.crt
*.p12
*.pfx
secrets/
credentials/

# Configurazioni locali
config/local.js
config/local.json
config/local.yml
local_settings.py
application-local.yml

# ===========================================
# BUILD E DEPENDENCY
# ===========================================

# Coverage reports
coverage/
*.lcov
.nyc_output

# Package managers
.pnpm-store/
.yarn/cache
.yarn/unplugged
.yarn/build-state.yml
.yarn/install-state.gz

# ===========================================
# CUSTOM PROJECT FILES
# ===========================================

# Temporary files
temp/
tmp/
.tmp/

# Documentation build
docs/_build/
site/

# Media e uploads
uploads/
media/uploads/
public/uploads/

# Backup files
*.backup
*.bak
*.orig

# Performance monitoring
.lighthouseci/

# ===========================================
# INCLUDE IMPORTANT FILES
# ===========================================
# Manteniamo i file di configurazione template
!**/config/template.*
!**/config/*.template
!**/.env.template
!**/.env.example
!**/docker-compose.template.yml

# Manteniamo le directory con .gitkeep
!**/.gitkeep

# Manteniamo i file README
!**/README.md
EOF
```

### 3. Configurazione Frontend (React + Next.js)
```bash
# Setup Frontend Web
cd frontend/web

# Simula creazione progetto Next.js
cat > package.json << 'EOF'
{
  "name": "platform-web",
  "version": "0.1.0",
  "private": true,
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "start": "next start",
    "lint": "next lint",
    "test": "jest",
    "test:coverage": "jest --coverage"
  },
  "dependencies": {
    "next": "14.0.0",
    "react": "^18",
    "react-dom": "^18"
  },
  "devDependencies": {
    "@types/node": "^20",
    "@types/react": "^18",
    "@types/react-dom": "^18",
    "eslint": "^8",
    "eslint-config-next": "14.0.0",
    "typescript": "^5"
  }
}
EOF

# File di configurazione Next.js
cat > next.config.js << 'EOF'
/** @type {import('next').NextConfig} */
const nextConfig = {
  experimental: {
    appDir: true,
  },
  images: {
    domains: ['localhost', 'api.platform.com'],
  },
  env: {
    CUSTOM_KEY: process.env.CUSTOM_KEY,
  },
}

module.exports = nextConfig
EOF

# Template ambiente
cat > .env.template << 'EOF'
# API Configuration
NEXT_PUBLIC_API_URL=http://localhost:3001
NEXT_PUBLIC_APP_NAME=Platform Web

# Authentication
NEXTAUTH_URL=http://localhost:3000
NEXTAUTH_SECRET=your-secret-here

# External Services
NEXT_PUBLIC_GOOGLE_ANALYTICS_ID=GA_MEASUREMENT_ID
NEXT_PUBLIC_STRIPE_PUBLISHABLE_KEY=pk_test_...

# Database
DATABASE_URL=postgresql://user:pass@localhost:5432/platform
EOF

# Creiamo file di esempio che dovrebbero essere ignorati
mkdir -p node_modules/.cache
echo "cache file" > node_modules/.cache/example
mkdir -p .next/static
echo "build file" > .next/static/build.js
echo "NEXTAUTH_SECRET=real-secret-123" > .env.local

cd ../../
```

### 4. Configurazione Backend (Python Django + API)
```bash
# Setup Backend API
cd backend/api

# Requirements Python
cat > requirements.txt << 'EOF'
Django==4.2.7
djangorestframework==3.14.0
celery==5.3.4
redis==5.0.1
psycopg2-binary==2.9.9
python-decouple==3.8
django-cors-headers==4.3.1
gunicorn==21.2.0
EOF

# Settings template
cat > settings_template.py << 'EOF'
import os
from decouple import config

BASE_DIR = Path(__file__).resolve().parent.parent

SECRET_KEY = config('SECRET_KEY')
DEBUG = config('DEBUG', default=False, cast=bool)
ALLOWED_HOSTS = config('ALLOWED_HOSTS', default='localhost').split(',')

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': config('DB_NAME'),
        'USER': config('DB_USER'),
        'PASSWORD': config('DB_PASSWORD'),
        'HOST': config('DB_HOST', default='localhost'),
        'PORT': config('DB_PORT', default='5432'),
    }
}

# Celery Configuration
CELERY_BROKER_URL = config('REDIS_URL', default='redis://localhost:6379/0')
CELERY_RESULT_BACKEND = config('REDIS_URL', default='redis://localhost:6379/0')

# CORS settings
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://127.0.0.1:3000",
]
EOF

# Template ambiente
cat > .env.template << 'EOF'
# Django Configuration
SECRET_KEY=your-django-secret-key
DEBUG=True
ALLOWED_HOSTS=localhost,127.0.0.1

# Database
DB_NAME=platform_db
DB_USER=platform_user
DB_PASSWORD=secure_password
DB_HOST=localhost
DB_PORT=5432

# Redis
REDIS_URL=redis://localhost:6379/0

# Email
EMAIL_HOST=smtp.gmail.com
EMAIL_PORT=587
EMAIL_HOST_USER=noreply@platform.com
EMAIL_HOST_PASSWORD=app_password

# AWS S3 (for file storage)
AWS_ACCESS_KEY_ID=your_access_key
AWS_SECRET_ACCESS_KEY=your_secret_key
AWS_STORAGE_BUCKET_NAME=platform-storage
EOF

# Creiamo file che dovrebbero essere ignorati
echo "SECRET_KEY=real-django-secret" > .env
mkdir -p __pycache__
echo "cache" > __pycache__/settings.cpython-311.pyc
touch db.sqlite3
mkdir -p media/uploads
echo "uploaded file" > media/uploads/test.jpg

cd ../../
```

### 5. Configurazione Mobile (Android)
```bash
# Setup Mobile Android
cd mobile/android

# Gradle properties template
cat > gradle.properties.template << 'EOF'
# Project-wide Gradle settings
org.gradle.jvmargs=-Xmx2048m -Dfile.encoding=UTF-8
org.gradle.parallel=true
org.gradle.caching=true
org.gradle.configureondemand=true

# Android settings
android.useAndroidX=true
android.enableJetifier=true

# Signing configs (replace with your values)
RELEASE_STORE_FILE=your-release-key.keystore
RELEASE_STORE_PASSWORD=your_store_password
RELEASE_KEY_ALIAS=your_key_alias
RELEASE_KEY_PASSWORD=your_key_password

# API endpoints
API_BASE_URL=https://api.platform.com
API_VERSION=v1
EOF

# Creiamo file che dovrebbero essere ignorati
mkdir -p .gradle/caches
echo "gradle cache" > .gradle/caches/example
mkdir -p build/outputs
echo "apk file" > build/outputs/app.apk
echo "RELEASE_STORE_PASSWORD=real_password" > gradle.properties

cd ../../
```

### 6. Configurazione DevOps
```bash
# Setup DevOps
cd devops

# Docker Compose template
cat > docker/docker-compose.template.yml << 'EOF'
version: '3.8'

services:
  web:
    build: 
      context: ../../frontend/web
      dockerfile: Dockerfile
    ports:
      - "3000:3000"
    environment:
      - NEXT_PUBLIC_API_URL=http://api:3001
    depends_on:
      - api
      - redis

  api:
    build:
      context: ../../backend/api
      dockerfile: Dockerfile
    ports:
      - "3001:3001"
    environment:
      - DATABASE_URL=${DATABASE_URL}
      - REDIS_URL=redis://redis:6379/0
    depends_on:
      - db
      - redis

  db:
    image: postgres:15
    environment:
      - POSTGRES_DB=${DB_NAME}
      - POSTGRES_USER=${DB_USER}
      - POSTGRES_PASSWORD=${DB_PASSWORD}
    volumes:
      - postgres_data:/var/lib/postgresql/data
    ports:
      - "5432:5432"

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"

volumes:
  postgres_data:
EOF

# Kubernetes deployment template
cat > kubernetes/deployment.template.yml << 'EOF'
apiVersion: apps/v1
kind: Deployment
metadata:
  name: platform-api
spec:
  replicas: 3
  selector:
    matchLabels:
      app: platform-api
  template:
    metadata:
      labels:
        app: platform-api
    spec:
      containers:
      - name: api
        image: platform/api:latest
        ports:
        - containerPort: 3001
        env:
        - name: DATABASE_URL
          valueFrom:
            secretKeyRef:
              name: platform-secrets
              key: database-url
        - name: REDIS_URL
          value: "redis://redis-service:6379/0"
EOF

# Terraform template
cat > terraform/main.tf.template << 'EOF'
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

# S3 bucket for file storage
resource "aws_s3_bucket" "platform_storage" {
  bucket = var.s3_bucket_name
}

# RDS instance
resource "aws_db_instance" "platform_db" {
  identifier = "platform-db"
  engine     = "postgres"
  engine_version = "15.4"
  instance_class = var.db_instance_class
  allocated_storage = 20
  storage_encrypted = true
  
  db_name  = var.db_name
  username = var.db_username
  password = var.db_password
  
  skip_final_snapshot = true
}
EOF

# Creiamo file che dovrebbero essere ignorati
echo "docker-compose.override.yml content" > docker/docker-compose.override.yml
mkdir -p terraform/.terraform
echo "terraform state" > terraform/.terraform/example
echo "db_password = \"real_password\"" > terraform/terraform.tfvars

cd ../
```

## 7. Scripts di Automazione Avanzati

```bash
# Script di setup completo
cat > scripts/setup-dev.sh << 'EOF'
#!/bin/bash

set -e

echo "🚀 Setting up full development environment..."

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${GREEN}ℹ️  $1${NC}"
}

log_warn() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

log_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Verifica prerequisiti
check_requirements() {
    log_info "Checking requirements..."
    
    command -v node >/dev/null 2>&1 || { log_error "Node.js is required but not installed."; exit 1; }
    command -v python3 >/dev/null 2>&1 || { log_error "Python 3 is required but not installed."; exit 1; }
    command -v docker >/dev/null 2>&1 || { log_error "Docker is required but not installed."; exit 1; }
    
    log_info "All requirements satisfied!"
}

# Setup Frontend
setup_frontend() {
    log_info "Setting up frontend..."
    
    cd frontend/web
    
    if [ ! -f ".env" ]; then
        cp .env.template .env
        log_warn "Created .env from template. Please configure it."
    fi
    
    if [ ! -d "node_modules" ]; then
        npm install
    fi
    
    cd ../../
}

# Setup Backend
setup_backend() {
    log_info "Setting up backend..."
    
    cd backend/api
    
    if [ ! -d "venv" ]; then
        python3 -m venv venv
    fi
    
    source venv/bin/activate
    pip install -r requirements.txt
    
    if [ ! -f ".env" ]; then
        cp .env.template .env
        log_warn "Created .env from template. Please configure it."
    fi
    
    cd ../../
}

# Setup DevOps
setup_devops() {
    log_info "Setting up DevOps configurations..."
    
    cd devops
    
    if [ ! -f "docker/docker-compose.yml" ]; then
        cp docker/docker-compose.template.yml docker/docker-compose.yml
        log_warn "Created docker-compose.yml from template."
    fi
    
    if [ ! -f "terraform/main.tf" ]; then
        cp terraform/main.tf.template terraform/main.tf
        log_warn "Created main.tf from template."
    fi
    
    cd ../
}

# Crea file .gitkeep per directory vuote
create_gitkeep() {
    log_info "Creating .gitkeep files for empty directories..."
    
    find . -type d -empty -not -path "./.git/*" -exec touch {}/.gitkeep \;
}

# Main execution
main() {
    check_requirements
    setup_frontend
    setup_backend
    setup_devops
    create_gitkeep
    
    log_info "Development environment setup complete!"
    echo ""
    log_warn "Next steps:"
    echo "1. Configure .env files in frontend/web and backend/api"
    echo "2. Run 'docker-compose up' in devops/docker to start services"
    echo "3. Run tests with './scripts/test-all.sh'"
}

main "$@"
EOF

chmod +x scripts/setup-dev.sh
```

```bash
# Script di test completo
cat > scripts/test-all.sh << 'EOF'
#!/bin/bash

set -e

echo "🧪 Running comprehensive test suite..."

# Colori
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

FAILED_TESTS=0

run_test() {
    echo -e "${YELLOW}Running: $1${NC}"
    if $2; then
        echo -e "${GREEN}✅ $1 passed${NC}"
    else
        echo -e "${RED}❌ $1 failed${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# Test Frontend
test_frontend() {
    cd frontend/web
    npm test -- --watchAll=false --coverage
    cd ../../
}

# Test Backend
test_backend() {
    cd backend/api
    source venv/bin/activate
    python -m pytest tests/ --cov=. --cov-report=html
    cd ../../
}

# Test Linting
test_linting() {
    echo "Running linting checks..."
    
    # Frontend linting
    cd frontend/web
    npm run lint
    cd ../../
    
    # Backend linting
    cd backend/api
    source venv/bin/activate
    flake8 . --max-line-length=88 --exclude=venv,migrations
    cd ../../
}

# Test Docker builds
test_docker() {
    echo "Testing Docker builds..."
    
    cd devops/docker
    docker-compose -f docker-compose.yml config
    cd ../../
}

# Test .gitignore effectiveness
test_gitignore() {
    echo "Testing .gitignore patterns..."
    
    # Create test files that should be ignored
    echo "test" > .env
    mkdir -p temp_test/node_modules
    echo "module" > temp_test/node_modules/test.js
    echo "cache" > temp_test/__pycache__/test.pyc
    
    # Check if they're ignored
    git add . 2>/dev/null || true
    
    if git status --porcelain | grep -q ".env"; then
        echo "❌ .env file is not ignored!"
        return 1
    fi
    
    if git status --porcelain | grep -q "node_modules"; then
        echo "❌ node_modules is not ignored!"
        return 1
    fi
    
    if git status --porcelain | grep -q "__pycache__"; then
        echo "❌ __pycache__ is not ignored!"
        return 1
    fi
    
    # Cleanup
    rm -f .env
    rm -rf temp_test
    
    echo "✅ .gitignore working correctly!"
}

# Main execution
main() {
    run_test "Frontend Tests" test_frontend
    run_test "Backend Tests" test_backend
    run_test "Linting" test_linting
    run_test "Docker Configuration" test_docker
    run_test "GitIgnore Patterns" test_gitignore
    
    echo "📊 Test Summary:"
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}All tests passed! 🎉${NC}"
        exit 0
    else
        echo -e "${RED}$FAILED_TESTS tests failed ❌${NC}"
        exit 1
    fi
}

main "$@"
EOF

chmod +x scripts/test-all.sh
```

## 8. Verifica Completa del .gitignore

```bash
# Script di verifica
cat > scripts/verify-gitignore.sh << 'EOF'
#!/bin/bash

echo "🔍 Verifying .gitignore effectiveness..."

# File che dovrebbero essere ignorati
IGNORED_FILES=(
    ".env"
    "frontend/web/node_modules/test.js"
    "frontend/web/.next/build.js"
    "backend/api/__pycache__/test.pyc"
    "backend/api/db.sqlite3"
    "mobile/android/.gradle/cache"
    "devops/terraform/.terraform/state"
    "logs/app.log"
)

# File che dovrebbero essere tracciati
TRACKED_FILES=(
    ".env.template"
    "frontend/web/.env.template"
    "backend/api/.env.template"
    "devops/docker/docker-compose.template.yml"
    "README.md"
)

# Testa file ignorati
echo "Testing ignored files:"
for file in "${IGNORED_FILES[@]}"; do
    mkdir -p "$(dirname "$file")"
    echo "test content" > "$file"
    
    if git check-ignore "$file" >/dev/null 2>&1; then
        echo "✅ $file is correctly ignored"
    else
        echo "❌ $file should be ignored but isn't!"
    fi
done

# Testa file tracciati
echo -e "\nTesting tracked files:"
for file in "${TRACKED_FILES[@]}"; do
    if [ -f "$file" ]; then
        if git check-ignore "$file" >/dev/null 2>&1; then
            echo "❌ $file is ignored but should be tracked!"
        else
            echo "✅ $file is correctly tracked"
        fi
    fi
done

# Cleanup
for file in "${IGNORED_FILES[@]}"; do
    rm -f "$file"
    rmdir "$(dirname "$file")" 2>/dev/null || true
done

echo -e "\n✅ GitIgnore verification complete!"
EOF

chmod +x scripts/verify-gitignore.sh
```

## Commit e Test Finale

```bash
# Aggiungiamo tutto
git add .

# Verifichiamo cosa stiamo committando
git status

# Eseguiamo la verifica
./scripts/verify-gitignore.sh

# Commit finale
git commit -m "feat: complete multi-language development environment

- Add comprehensive .gitignore for Node.js, Python, Java, Android, iOS
- Include Docker, Kubernetes, and Terraform configurations
- Create template files for all environments (.env.template, etc.)
- Add automated setup and testing scripts
- Implement verification scripts for .gitignore effectiveness
- Support for React/Next.js, Django, Android, and DevOps tools
- Comprehensive coverage of build files, dependencies, and secrets"
```

## Punti Chiave Appresi

1. **Modularità**: .gitignore organizzato per sezioni tecnologiche
2. **Template System**: File di configurazione separati per sicurezza
3. **Automazione Completa**: Script per setup, test e verifica
4. **Multi-tecnologia**: Supporto per stack completo
5. **Security First**: Gestione rigorosa di credenziali e segreti
6. **Team Collaboration**: Configurazioni condivise e documentate

Questo esempio mostra una configurazione enterprise-level per progetti complessi multi-tecnologia.
