# Esercizio 2: Progetto Multi-linguaggio

## Obiettivo
Configurare un .gitignore complesso per un progetto che utilizza multiple tecnologie: Node.js (frontend), Python (backend), database locale, e strumenti di build. Apprendere la gestione di pattern avanzati e configurazioni globali.

## Prerequisiti
- Completamento dell'Esercizio 1
- Conoscenza base di Node.js e Python
- Comprensione dei pattern avanzati .gitignore
- Familiarità con strumenti di build

## Scenario
Stai sviluppando un'applicazione full-stack con:
- **Frontend**: React/Node.js
- **Backend**: Python/Django
- **Database**: PostgreSQL + SQLite per sviluppo
- **Mobile**: React Native
- **DevOps**: Docker, CI/CD
- **Documentation**: Jupyter notebooks

Devi creare un .gitignore che gestisca tutti questi ambienti senza conflitti.

## Parte 1: Setup Progetto Complesso

### Passo 1: Struttura del Progetto
```bash
# Crea il progetto
mkdir fullstack-app
cd fullstack-app

# Inizializza Git
git init

# Crea struttura complessa
mkdir -p {frontend,backend,mobile,docs,devops,database,scripts}
mkdir -p frontend/{src,public,build,tests}
mkdir -p frontend/src/{components,pages,hooks,utils,styles}
mkdir -p backend/{app,tests,migrations,media,static}
mkdir -p mobile/{src,android,ios}
mkdir -p docs/{api,user,notebooks}
mkdir -p devops/{docker,kubernetes,ci}
mkdir -p database/{migrations,seeds,backups}
mkdir -p scripts/{build,deploy,test}
```

### Passo 2: Frontend React/Node.js
```bash
cd frontend

# Package.json
cat > package.json << 'EOF'
{
  "name": "fullstack-frontend",
  "version": "0.1.0",
  "private": true,
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "axios": "^1.6.0",
    "react-router-dom": "^6.8.0"
  },
  "devDependencies": {
    "@testing-library/react": "^13.4.0",
    "@types/react": "^18.0.0",
    "eslint": "^8.57.0",
    "prettier": "^3.0.0",
    "webpack": "^5.88.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test",
    "eject": "react-scripts eject",
    "lint": "eslint src/",
    "format": "prettier --write src/"
  }
}
EOF

# File di ambiente
cat > .env.template << 'EOF'
# API Configuration
REACT_APP_API_URL=http://localhost:8000
REACT_APP_WS_URL=ws://localhost:8001

# Authentication
REACT_APP_AUTH_DOMAIN=dev.example.com
REACT_APP_AUTH_CLIENT_ID=your_client_id

# Feature Flags
REACT_APP_ENABLE_DEBUG=true
REACT_APP_ENABLE_ANALYTICS=false

# External Services
REACT_APP_GOOGLE_MAPS_API_KEY=your_maps_key
REACT_APP_STRIPE_PUBLIC_KEY=pk_test_your_key
EOF

# File React
cat > src/App.js << 'EOF'
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import './App.css';

function App() {
  return (
    <Router>
      <div className="App">
        <header className="App-header">
          <h1>FullStack App</h1>
        </header>
        <Routes>
          <Route path="/" element={<Home />} />
        </Routes>
      </div>
    </Router>
  );
}

const Home = () => <div>Welcome to FullStack App</div>;

export default App;
EOF

# Test file
cat > src/App.test.js << 'EOF'
import { render, screen } from '@testing-library/react';
import App from './App';

test('renders welcome message', () => {
  render(<App />);
  const linkElement = screen.getByText(/Welcome to FullStack App/i);
  expect(linkElement).toBeInTheDocument();
});
EOF

cd ../
```

### Passo 3: Backend Python/Django
```bash
cd backend

# Requirements
cat > requirements.txt << 'EOF'
Django==4.2.7
djangorestframework==3.14.0
django-cors-headers==4.3.1
celery==5.3.4
redis==5.0.1
psycopg2-binary==2.9.9
Pillow==10.1.0
python-decouple==3.8
gunicorn==21.2.0
pytest==7.4.3
pytest-django==4.7.0
coverage==7.3.2
EOF

cat > requirements-dev.txt << 'EOF'
-r requirements.txt
black==23.11.0
flake8==6.1.0
isort==5.12.0
pre-commit==3.5.0
django-debug-toolbar==4.2.0
factory-boy==3.3.0
EOF

# Settings Django
cat > app/settings.py << 'EOF'
import os
from decouple import config
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent.parent

SECRET_KEY = config('SECRET_KEY')
DEBUG = config('DEBUG', default=False, cast=bool)
ALLOWED_HOSTS = config('ALLOWED_HOSTS', default='localhost').split(',')

INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'rest_framework',
    'corsheaders',
]

MIDDLEWARE = [
    'corsheaders.middleware.CorsMiddleware',
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

ROOT_URLCONF = 'app.urls'

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

STATIC_URL = '/static/'
STATIC_ROOT = os.path.join(BASE_DIR, 'staticfiles')

MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')
EOF

# Template environment
cat > .env.template << 'EOF'
# Django Configuration
SECRET_KEY=your-secret-key-here
DEBUG=True
ALLOWED_HOSTS=localhost,127.0.0.1,0.0.0.0

# Database Configuration
DB_NAME=fullstack_db
DB_USER=fullstack_user
DB_PASSWORD=your_secure_password
DB_HOST=localhost
DB_PORT=5432

# Redis Configuration
REDIS_URL=redis://localhost:6379/0

# Email Configuration
EMAIL_HOST=smtp.gmail.com
EMAIL_PORT=587
EMAIL_USE_TLS=True
EMAIL_HOST_USER=your-email@example.com
EMAIL_HOST_PASSWORD=your-app-password

# File Storage (AWS S3)
AWS_ACCESS_KEY_ID=your_access_key
AWS_SECRET_ACCESS_KEY=your_secret_key
AWS_STORAGE_BUCKET_NAME=fullstack-storage
AWS_S3_REGION_NAME=us-east-1

# External APIs
STRIPE_SECRET_KEY=sk_test_your_key
GOOGLE_CLOUD_API_KEY=your_api_key
EOF

# Models
cat > app/models.py << 'EOF'
from django.db import models
from django.contrib.auth.models import User

class Post(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    image = models.ImageField(upload_to='posts/', blank=True, null=True)
    
    class Meta:
        ordering = ['-created_at']
    
    def __str__(self):
        return self.title
EOF

cd ../
```

### Passo 4: Mobile React Native
```bash
cd mobile

# Package.json React Native
cat > package.json << 'EOF'
{
  "name": "FullstackMobile",
  "version": "0.0.1",
  "private": true,
  "scripts": {
    "android": "react-native run-android",
    "ios": "react-native run-ios",
    "start": "react-native start",
    "test": "jest",
    "lint": "eslint . --ext .js,.jsx,.ts,.tsx"
  },
  "dependencies": {
    "react": "18.2.0",
    "react-native": "0.72.6",
    "@react-navigation/native": "^6.1.0",
    "@react-navigation/stack": "^6.3.0",
    "axios": "^1.6.0"
  },
  "devDependencies": {
    "@babel/core": "^7.20.0",
    "@babel/preset-env": "^7.20.0",
    "@babel/runtime": "^7.20.0",
    "@react-native/eslint-config": "^0.72.0",
    "@react-native/metro-config": "^0.72.0",
    "@tsconfig/react-native": "^3.0.0",
    "@types/react": "^18.0.0",
    "@types/react-test-renderer": "^18.0.0",
    "babel-jest": "^29.0.0",
    "eslint": "^8.19.0",
    "jest": "^29.0.0",
    "metro-react-native-babel-preset": "0.76.8",
    "prettier": "^2.4.1",
    "react-test-renderer": "18.2.0",
    "typescript": "4.8.4"
  }
}
EOF

# Android build.gradle
mkdir -p android/app
cat > android/app/build.gradle << 'EOF'
apply plugin: "com.android.application"
apply plugin: "com.facebook.react"

android {
    compileSdkVersion rootProject.ext.compileSdkVersion

    defaultConfig {
        applicationId "com.fullstackapp"
        minSdkVersion rootProject.ext.minSdkVersion
        targetSdkVersion rootProject.ext.targetSdkVersion
        versionCode 1
        versionName "1.0"
    }
    
    signingConfigs {
        release {
            storeFile file('release.keystore')
            storePassword System.getenv("KEYSTORE_PASSWORD")
            keyAlias System.getenv("KEY_ALIAS")
            keyPassword System.getenv("KEY_PASSWORD")
        }
    }
}
EOF

# iOS config template
mkdir -p ios
cat > ios/FullstackApp.xcodeproj.template << 'EOF'
// Template Xcode project configuration
// Copy this file and configure with your Apple Developer settings
{
  "DEVELOPMENT_TEAM": "YOUR_TEAM_ID",
  "CODE_SIGN_IDENTITY": "iPhone Developer",
  "PROVISIONING_PROFILE_SPECIFIER": "YOUR_PROFILE"
}
EOF

cd ../
```

### Passo 5: DevOps e Documentazione
```bash
# Docker
cd devops/docker

cat > Dockerfile.frontend << 'EOF'
FROM node:18-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .
RUN npm run build
EXPOSE 3000
CMD ["npm", "start"]
EOF

cat > Dockerfile.backend << 'EOF'
FROM python:3.11-slim
WORKDIR /app
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
COPY . .
EXPOSE 8000
CMD ["gunicorn", "app.wsgi:application", "--bind", "0.0.0.0:8000"]
EOF

cat > docker-compose.yml.template << 'EOF'
version: '3.8'

services:
  db:
    image: postgres:15
    environment:
      POSTGRES_DB: ${DB_NAME}
      POSTGRES_USER: ${DB_USER}
      POSTGRES_PASSWORD: ${DB_PASSWORD}
    volumes:
      - postgres_data:/var/lib/postgresql/data
    ports:
      - "5432:5432"

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"

  backend:
    build:
      context: ../../backend
      dockerfile: ../devops/docker/Dockerfile.backend
    environment:
      - DATABASE_URL=postgresql://${DB_USER}:${DB_PASSWORD}@db:5432/${DB_NAME}
      - REDIS_URL=redis://redis:6379/0
    depends_on:
      - db
      - redis
    ports:
      - "8000:8000"

  frontend:
    build:
      context: ../../frontend
      dockerfile: ../devops/docker/Dockerfile.frontend
    environment:
      - REACT_APP_API_URL=http://backend:8000
    depends_on:
      - backend
    ports:
      - "3000:3000"

volumes:
  postgres_data:
EOF

cd ../../

# Jupyter notebooks
cd docs/notebooks

cat > data_analysis.ipynb << 'EOF'
{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "# Data Analysis Notebook\n",
    "Analisi dei dati dell'applicazione"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "import pandas as pd\n",
    "import numpy as np\n",
    "import matplotlib.pyplot as plt\n",
    "\n",
    "# Carica i dati\n",
    "df = pd.read_csv('../../database/exports/users.csv')\n",
    "print(f\"Dataset shape: {df.shape}\")"
   ]
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 4
}
EOF

cd ../../
```

## Parte 2: Simulazione File da Ignorare

### Passo 1: File di Sviluppo e Build
```bash
# Frontend - Node.js
cd frontend
mkdir -p node_modules/react
echo "react module" > node_modules/react/index.js
mkdir -p build/static/js
echo "built app.js" > build/static/js/main.js
echo "REACT_APP_API_KEY=secret123" > .env
mkdir -p coverage/lcov-report
echo "coverage report" > coverage/lcov-report/index.html

# File cache e temporanei
mkdir -p .eslintcache
echo "eslint cache" > .eslintcache
echo "debug log" > npm-debug.log

cd ../backend

# Python - Django
echo "SECRET_KEY=real-secret-django-key" > .env
mkdir -p __pycache__
echo "python cache" > __pycache__/models.cpython-311.pyc
mkdir -p .pytest_cache
echo "pytest cache" > .pytest_cache/example
touch db.sqlite3
mkdir -p media/uploads/posts
echo "uploaded image" > media/uploads/posts/test.jpg
mkdir -p staticfiles/admin
echo "collected static" > staticfiles/admin/css/base.css

# Virtual environment
mkdir -p venv/lib/python3.11
echo "virtual env" > venv/lib/python3.11/site-packages

# Coverage e test
mkdir -p htmlcov
echo "coverage html" > htmlcov/index.html
echo "test coverage" > .coverage

cd ../mobile

# React Native
mkdir -p node_modules/react-native
echo "rn module" > node_modules/react-native/index.js
mkdir -p android/.gradle/caches
echo "gradle cache" > android/.gradle/caches/example
mkdir -p android/app/build/outputs
echo "apk file" > android/app/build/outputs/app.apk
mkdir -p ios/build
echo "ios build" > ios/build/example

# Configurazioni sensibili
echo "KEYSTORE_PASSWORD=secret_keystore" > android/gradle.properties
mkdir -p ios/FullstackApp.xcodeproj
echo "sensitive ios config" > ios/FullstackApp.xcodeproj/project.pbxproj

cd ../

# DevOps
cd devops
echo "DB_PASSWORD=real_password" > .env
mkdir -p docker/.docker
echo "docker cache" > docker/.docker/example

cd ../

# Database
cd database
mkdir -p backups
echo "backup data" > backups/db_backup_2024.sql
echo "sensitive data" > connection_string.txt

cd ../

# Documentation
cd docs/notebooks
mkdir -p .ipynb_checkpoints
echo "notebook checkpoint" > .ipynb_checkpoints/data_analysis-checkpoint.ipynb

cd ../../

# Root level
mkdir -p logs
echo "2024-01-15 ERROR: Critical error" > logs/error.log
echo "2024-01-15 INFO: App started" > logs/app.log

# IDE e sistema
mkdir -p .vscode
echo '{"python.defaultInterpreter": "./backend/venv/bin/python"}' > .vscode/settings.json
echo "system file" > .DS_Store
```

## Parte 3: Creazione .gitignore Multi-tecnologia

### Passo 1: Analisi dei Pattern Necessari
Prima di scrivere il .gitignore, analizza:

1. **Node.js patterns**: node_modules, build/, coverage/, .env
2. **Python patterns**: __pycache__, venv/, .coverage, *.pyc
3. **React Native patterns**: android/build/, ios/build/, metro cache
4. **Database patterns**: *.sqlite3, backups/, dumps/
5. **DevOps patterns**: docker volumes, kubernetes secrets
6. **Documentation patterns**: .ipynb_checkpoints/, _build/
7. **IDE patterns**: .vscode/, .idea/, *.swp
8. **System patterns**: .DS_Store, Thumbs.db

### Passo 2: Scrittura .gitignore Strutturato
Crea il file `.gitignore` organizzato per sezioni:

```gitignore
# Il tuo .gitignore qui
# Organizza per sezioni logiche
# Includi commenti esplicativi
```

**Sezioni da includere:**
1. File di sistema e IDE
2. Node.js e JavaScript
3. Python e Django
4. React Native e Mobile
5. Database e dati
6. DevOps e infrastruttura
7. Documentazione
8. Log e file temporanei
9. Configurazioni sensibili

### Passo 3: Pattern Avanzati da Implementare

**Pattern di negazione:**
```gitignore
# Ignora tutti i file di configurazione ma mantieni i template
config/*
!config/*.template
!config/README.md
```

**Pattern condizionali:**
```gitignore
# Ignora build ma mantieni alcune directory strutturali
build/
!build/README.md
!build/.gitkeep
```

**Pattern specifici per path:**
```gitignore
# Pattern specifici per sottoprogetti
frontend/build/
backend/media/uploads/
mobile/android/app/build/
```

## Parte 4: Test Avanzati

### Passo 1: Verifica Sistematica
```bash
# Crea script di test completo
cat > test-gitignore.sh << 'EOF'
#!/bin/bash

echo "🔍 Testing .gitignore patterns..."

# Colori per output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

TESTS_PASSED=0
TESTS_FAILED=0

test_ignored() {
    if git check-ignore "$1" >/dev/null 2>&1; then
        echo -e "${GREEN}✅ $1 is correctly ignored${NC}"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "${RED}❌ $1 should be ignored but isn't!${NC}"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
}

test_tracked() {
    if git check-ignore "$1" >/dev/null 2>&1; then
        echo -e "${RED}❌ $1 is ignored but should be tracked!${NC}"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    else
        echo -e "${GREEN}✅ $1 is correctly tracked${NC}"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    fi
}

echo "Testing ignored files:"
test_ignored "frontend/.env"
test_ignored "frontend/node_modules/react/index.js"
test_ignored "frontend/build/static/js/main.js"
test_ignored "backend/.env"
test_ignored "backend/__pycache__/models.cpython-311.pyc"
test_ignored "backend/db.sqlite3"
test_ignored "backend/media/uploads/posts/test.jpg"
test_ignored "mobile/android/.gradle/caches/example"
test_ignored "mobile/ios/build/example"
test_ignored "logs/error.log"
test_ignored ".vscode/settings.json"
test_ignored ".DS_Store"

echo ""
echo "Testing tracked files:"
test_tracked "frontend/package.json"
test_tracked "frontend/.env.template"
test_tracked "backend/requirements.txt"
test_tracked "backend/.env.template"
test_tracked "mobile/package.json"
test_tracked "devops/docker/docker-compose.yml.template"
test_tracked "README.md"

echo ""
echo "📊 Test Results:"
echo -e "${GREEN}Passed: $TESTS_PASSED${NC}"
echo -e "${RED}Failed: $TESTS_FAILED${NC}"

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}💥 Some tests failed!${NC}"
    exit 1
fi
EOF

chmod +x test-gitignore.sh
```

### Passo 2: Test di Configurazione Globale
```bash
# Test configurazione globale (opzionale)
git config --global core.excludesfile ~/.gitignore_global

# Crea gitignore globale per file di sistema
cat > ~/.gitignore_global << 'EOF'
# Global gitignore for system files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
Desktop.ini

# Editor temp files
*~
*.swp
*.swo
.#*
EOF
```

### Passo 3: Verifica Performance
```bash
# Test di performance con molti file
mkdir -p temp_test
cd temp_test

# Crea molti file che dovrebbero essere ignorati
for i in {1..100}; do
    mkdir -p "node_modules/package$i"
    echo "module $i" > "node_modules/package$i/index.js"
done

# Testa che git li ignori tutti rapidamente
time git status >/dev/null

cd ../
rm -rf temp_test
```

## Parte 5: Automazione e Manutenzione

### Passo 1: Script di Setup
```bash
cat > scripts/setup-environment.sh << 'EOF'
#!/bin/bash

echo "🚀 Setting up development environment..."

# Frontend setup
if [ -d "frontend" ]; then
    cd frontend
    if [ ! -f ".env" ] && [ -f ".env.template" ]; then
        cp .env.template .env
        echo "Created frontend/.env from template"
    fi
    if [ ! -d "node_modules" ]; then
        npm install
    fi
    cd ..
fi

# Backend setup
if [ -d "backend" ]; then
    cd backend
    if [ ! -f ".env" ] && [ -f ".env.template" ]; then
        cp .env.template .env
        echo "Created backend/.env from template"
    fi
    if [ ! -d "venv" ]; then
        python3 -m venv venv
        source venv/bin/activate
        pip install -r requirements.txt
    fi
    cd ..
fi

# Mobile setup
if [ -d "mobile" ]; then
    cd mobile
    if [ ! -d "node_modules" ]; then
        npm install
    fi
    cd ..
fi

# DevOps setup
if [ -d "devops" ]; then
    cd devops
    if [ ! -f ".env" ] && [ -f ".env.template" ]; then
        cp .env.template .env
        echo "Created devops/.env from template"
    fi
    if [ ! -f "docker/docker-compose.yml" ] && [ -f "docker/docker-compose.yml.template" ]; then
        cp docker/docker-compose.yml.template docker/docker-compose.yml
        echo "Created docker-compose.yml from template"
    fi
    cd ..
fi

echo "✅ Environment setup complete!"
echo "Remember to configure your .env files with actual values"
EOF

chmod +x scripts/setup-environment.sh
```

### Passo 2: Script di Pulizia
```bash
cat > scripts/clean-development.sh << 'EOF'
#!/bin/bash

echo "🧹 Cleaning development files..."

# Remove build artifacts
find . -name "build" -type d -not -path "./.git/*" -exec rm -rf {} + 2>/dev/null
find . -name "dist" -type d -not -path "./.git/*" -exec rm -rf {} + 2>/dev/null

# Remove Python cache
find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null
find . -name "*.pyc" -delete
find . -name ".pytest_cache" -type d -exec rm -rf {} + 2>/dev/null

# Remove Node.js cache
find . -name ".eslintcache" -delete
find . -name "npm-debug.log*" -delete
find . -name "yarn-error.log*" -delete

# Remove coverage reports
find . -name "coverage" -type d -not -path "./.git/*" -exec rm -rf {} + 2>/dev/null
find . -name "htmlcov" -type d -exec rm -rf {} + 2>/dev/null
find . -name ".coverage" -delete

# Remove logs
find . -name "*.log" -not -path "./.git/*" -delete

# Remove temporary files
find . -name "*.tmp" -delete
find . -name "*.bak" -delete
find . -name "*~" -delete

echo "✅ Cleanup complete!"
EOF

chmod +x scripts/clean-development.sh
```

## Verifica Finale Completa

### Passo 1: Test Integrato
```bash
# Esegui tutti i test
./test-gitignore.sh

# Verifica git status
git add .
git status

# Dovrebbe mostrare solo i file che vuoi tracciare
```

### Passo 2: Checklist di Completamento
- [ ] .gitignore creato con sezioni per tutte le tecnologie
- [ ] Pattern avanzati implementati (negazione, path specifici)
- [ ] File sensibili correttamente ignorati
- [ ] Template files correttamente tracciati
- [ ] Script di test e automazione creati
- [ ] Performance verificata con molti file
- [ ] Documentazione completa

### Passo 3: Analisi del Git Status Finale
Il comando `git status` dovrebbe mostrare solo:
- File di configurazione template
- File di codice sorgente
- Documentazione (README.md)
- File di progetto (package.json, requirements.txt)
- Script di automazione
- .gitignore stesso

## Domande Avanzate di Riflessione

1. **Come gestiresti un conflitto tra pattern .gitignore di diverse tecnologie?**
2. **Quando useresti un .gitignore globale vs uno locale?**
3. **Come verificheresti che il .gitignore funzioni correttamente in un team?**
4. **Che strategia adotteresti per aggiornare .gitignore su progetti esistenti?**
5. **Come gestiresti file che dovrebbero essere ignorati solo in certi ambienti?**

## Risultati Attesi

### .gitignore Completo (Esempio)
Il tuo .gitignore dovrebbe essere organizzato, commentato e coprire tutti i pattern necessari per un progetto multi-tecnologia professionale.

### Performance
Il comando `git status` dovrebbe essere veloce anche con migliaia di file ignorati.

### Manutenibilità
Il .gitignore dovrebbe essere facile da leggere, modificare e estendere per nuove tecnologie.

Completa questo esercizio per padroneggiare la gestione di .gitignore in ambienti complessi multi-tecnologia.
