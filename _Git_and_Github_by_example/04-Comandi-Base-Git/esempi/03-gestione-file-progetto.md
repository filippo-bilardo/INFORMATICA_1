# 03 - Gestione File in Progetti Complessi

## 📋 Scenario

Stai gestendo un progetto full-stack complesso con frontend React, backend Node.js, database e documentazione. Devi gestire file di vari tipi: codice sorgente, configurazioni, assets, documentazione, file temporanei, e file sensibili.

## 🎯 Obiettivo

Apprendere la gestione avanzata dei file Git in progetti reali:
- **Organizzazione strutturale** di progetti complessi
- **Gestione selettiva** di file e directory
- **File temporanei e build** con .gitignore
- **File sensibili** e configurazioni
- **Riorganizzazione** senza perdere cronologia

## 🛠️ Setup Progetto Full-Stack

```bash
# Crea progetto complesso
mkdir fullstack-task-manager
cd fullstack-task-manager
git init

# Struttura progetto reale
mkdir -p {frontend,backend,database,docs,scripts,deploy}
mkdir -p frontend/{src,public,build,node_modules}
mkdir -p frontend/src/{components,pages,utils,assets}
mkdir -p backend/{src,tests,logs,uploads}
mkdir -p backend/src/{controllers,models,routes,middleware}
mkdir -p database/{migrations,seeds,backups}
mkdir -p docs/{api,user-guide,architecture}

# Configura informazioni sviluppatore
git config user.name "Alice Developer"
git config user.email "alice@taskmanager.com"
```

## 🎯 Gestione File per Categoria

### 1. Codice Sorgente (Tracciato)
```bash
# Frontend React
cat > frontend/src/App.js << 'EOF'
import React from 'react';
import TaskList from './components/TaskList';
import Header from './components/Header';

function App() {
  return (
    <div className="App">
      <Header />
      <TaskList />
    </div>
  );
}

export default App;
EOF

cat > frontend/src/components/TaskList.js << 'EOF'
import React, { useState, useEffect } from 'react';

const TaskList = () => {
  const [tasks, setTasks] = useState([]);
  
  useEffect(() => {
    fetchTasks();
  }, []);
  
  const fetchTasks = async () => {
    try {
      const response = await fetch('/api/tasks');
      const data = await response.json();
      setTasks(data);
    } catch (error) {
      console.error('Error fetching tasks:', error);
    }
  };
  
  return (
    <div className="task-list">
      {tasks.map(task => (
        <div key={task.id} className="task-item">
          <h3>{task.title}</h3>
          <p>{task.description}</p>
        </div>
      ))}
    </div>
  );
};

export default TaskList;
EOF

# Backend Node.js
cat > backend/src/app.js << 'EOF'
const express = require('express');
const cors = require('cors');
const taskRoutes = require('./routes/tasks');

const app = express();

app.use(cors());
app.use(express.json());
app.use('/api/tasks', taskRoutes);

const PORT = process.env.PORT || 3001;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

cat > backend/src/models/Task.js << 'EOF'
const mongoose = require('mongoose');

const taskSchema = new mongoose.Schema({
  title: {
    type: String,
    required: true,
    trim: true
  },
  description: {
    type: String,
    required: true
  },
  completed: {
    type: Boolean,
    default: false
  },
  createdAt: {
    type: Date,
    default: Date.now
  }
});

module.exports = mongoose.model('Task', taskSchema);
EOF

# Aggiungi codice sorgente
git add frontend/src/ backend/src/
git commit -m "feat: implement basic task management functionality

Frontend:
- Add React components for task listing
- Implement task fetching from API
- Add responsive task display

Backend:  
- Setup Express server with CORS
- Create Task model with Mongoose
- Add basic API structure

Architecture: Frontend (React) → Backend (Node.js) → MongoDB"
```

### 2. Configurazioni (Selettive)
```bash
# Configurazioni pubbliche (tracciare)
cat > frontend/package.json << 'EOF'
{
  "name": "task-manager-frontend",
  "version": "1.0.0",
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "axios": "^1.4.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test"
  }
}
EOF

cat > backend/package.json << 'EOF'
{
  "name": "task-manager-backend",
  "version": "1.0.0",
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^7.3.0",
    "cors": "^2.8.5",
    "dotenv": "^16.1.4"
  },
  "scripts": {
    "start": "node src/app.js",
    "dev": "nodemon src/app.js",
    "test": "jest"
  }
}
EOF

# Configurazioni sensibili (NON tracciare)
cat > backend/.env.example << 'EOF'
# Database
MONGODB_URI=mongodb://localhost:27017/taskmanager
DB_NAME=taskmanager

# Server
PORT=3001
NODE_ENV=development

# Security
JWT_SECRET=your-secret-key-here
SESSION_SECRET=your-session-secret

# External APIs
EMAIL_API_KEY=your-email-api-key
STORAGE_API_KEY=your-storage-api-key
EOF

cat > backend/.env << 'EOF'
MONGODB_URI=mongodb://localhost:27017/taskmanager_dev
DB_NAME=taskmanager_dev
PORT=3001
NODE_ENV=development
JWT_SECRET=super-secret-development-key-12345
SESSION_SECRET=dev-session-secret-67890
EMAIL_API_KEY=real-email-api-key-abcdef
STORAGE_API_KEY=real-storage-key-xyz789
EOF

# Aggiungi solo configurazioni pubbliche
git add frontend/package.json backend/package.json backend/.env.example
git commit -m "config: add project dependencies and environment template

- Add frontend React dependencies
- Add backend Node.js dependencies  
- Include environment variables template
- Setup development and production scripts

Note: Actual .env file excluded for security"
```

### 3. .gitignore Completo per Progetti Full-Stack
```bash
cat > .gitignore << 'EOF'
# Dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Build outputs
/frontend/build/
/frontend/dist/
/backend/dist/
*.tgz

# Environment variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Logs
logs/
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# Runtime data
pids/
*.pid
*.seed
*.pid.lock

# Coverage directory used by tools like istanbul
coverage/
*.lcov

# IDEs and editors
.vscode/
.idea/
*.swp
*.swo
*~

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Database
/database/backups/*.sql
/database/backups/*.dump

# Uploads and temporary files
/backend/uploads/
/backend/temp/
*.tmp
*.temp

# Cache directories
.cache/
.parcel-cache/

# Optional npm cache directory
.npm

# Optional REPL history
.node_repl_history

# Output of 'npm pack'
*.tgz

# Yarn Integrity file
.yarn-integrity

# dotenv environment variables file
.env

# SSL certificates
*.pem
*.key
*.crt

# Local development databases
*.sqlite
*.sqlite3
*.db
EOF

git add .gitignore
git commit -m "config: add comprehensive .gitignore for full-stack project

Excludes:
- Dependencies (node_modules)
- Build outputs and distributions
- Environment variables and secrets
- Log files and temporary data
- IDE and OS generated files
- Database backups and uploads
- Cache and development files

Protects sensitive data while allowing collaboration"
```

### 4. Documentazione (Tracciata)
```bash
# README principale
cat > README.md << 'EOF'
# Task Manager Full-Stack Application

## 📖 Overview
Modern task management application with React frontend and Node.js backend.

## 🏗️ Architecture
```
Frontend (React) ←→ Backend (Node.js) ←→ Database (MongoDB)
     :3000              :3001               :27017
```

## 🚀 Quick Start

### Prerequisites
- Node.js 18+ 
- MongoDB 5+
- npm or yarn

### Installation
```bash
# Clone repository
git clone <repository-url>
cd fullstack-task-manager

# Install frontend dependencies
cd frontend
npm install

# Install backend dependencies  
cd ../backend
npm install
cp .env.example .env  # Configure your environment
```

### Development
```bash
# Start backend (in backend/)
npm run dev

# Start frontend (in frontend/)  
npm start
```

## 📁 Project Structure
```
├── frontend/          React application
│   ├── src/
│   ├── public/
│   └── build/
├── backend/           Node.js API server
│   ├── src/
│   ├── tests/
│   └── uploads/
├── database/          Database migrations and seeds
├── docs/             Documentation
└── deploy/           Deployment configurations
```

## 🧪 Testing
```bash
# Frontend tests
cd frontend && npm test

# Backend tests
cd backend && npm test
```

## 🚀 Deployment
See [deployment guide](./docs/deployment.md) for production setup.
EOF

# Documentazione API
cat > docs/api/README.md << 'EOF'
# API Documentation

## Base URL
```
Development: http://localhost:3001
Production: https://api.taskmanager.com
```

## Authentication
All protected endpoints require JWT token in Authorization header:
```
Authorization: Bearer <jwt-token>
```

## Endpoints

### Tasks
- `GET /api/tasks` - List all tasks
- `POST /api/tasks` - Create new task
- `GET /api/tasks/:id` - Get specific task
- `PUT /api/tasks/:id` - Update task
- `DELETE /api/tasks/:id` - Delete task

### Users
- `POST /api/auth/register` - Register new user
- `POST /api/auth/login` - User login
- `GET /api/users/profile` - Get user profile
EOF

# Guida utente
cat > docs/user-guide/getting-started.md << 'EOF'
# Getting Started with Task Manager

## Creating Your First Task
1. Click "Add Task" button
2. Enter task title and description
3. Click "Save" to create

## Managing Tasks
- ✅ Mark complete by clicking checkbox
- ✏️ Edit by clicking task title
- 🗑️ Delete by clicking trash icon

## Organizing Tasks
- Use categories to group related tasks
- Set due dates for time-sensitive items
- Add tags for easy filtering
EOF

git add README.md docs/
git commit -m "docs: add comprehensive project documentation

Added:
- Main README with architecture overview
- Quick start and installation guide
- Project structure documentation
- API endpoint documentation  
- User guide for task management

Includes setup instructions, testing, and deployment info"
```

### 5. Assets e Media (Selective)
```bash
# Crea directory assets
mkdir -p frontend/src/assets/{images,styles,fonts}

# Immagini ottimizzate (tracciare)
echo "<!-- Logo SVG placeholder -->" > frontend/src/assets/images/logo.svg
echo "/* App styles */" > frontend/src/assets/styles/app.css

# Font pubblici (tracciare)
echo "/* Custom fonts */" > frontend/src/assets/fonts/fonts.css

# Immagini grandi non ottimizzate (non tracciare)
mkdir -p frontend/public/uploads
echo "Large unoptimized image" > frontend/public/uploads/large-image.jpg

# Aggiungi al .gitignore
echo -e "\n# Large media files\n/frontend/public/uploads/\n*.jpg\n*.png\n*.gif" >> .gitignore

git add frontend/src/assets/ frontend/public/uploads/.gitkeep .gitignore
git commit -m "assets: add optimized assets and media management

Added:
- Optimized logo and icons (SVG format)
- Base CSS styles and fonts
- Upload directory with .gitkeep
- Updated .gitignore for large media files

Policy: Track optimized assets, exclude large uploads"
```

## 🔄 Riorganizzazione Struttura

### Scenario: Ristrutturazione per Microservizi
```bash
# Situazione: vogliamo separare in microservizi
# Struttura attuale: monolith → Struttura target: microservizi

echo "Ristrutturazione da monolith a microservizi..."

# Crea nuova struttura
mkdir -p services/{auth-service,task-service,notification-service}
mkdir -p services/shared/{utils,models}

# Sposta task logic mantenendo cronologia
git mv backend/src/models/Task.js services/task-service/models/
git mv backend/src/controllers/tasks.js services/task-service/controllers/
git mv backend/src/routes/tasks.js services/task-service/routes/

# Commit riorganizzazione
git commit -m "refactor: restructure backend for microservices architecture

Moved task-related components to dedicated service:
- Task model → services/task-service/models/
- Task controller → services/task-service/controllers/  
- Task routes → services/task-service/routes/

Preparation for:
- Independent service deployment
- Separate scaling of task functionality
- Service-specific testing and monitoring"

# Crea configurazioni per ogni servizio
cat > services/task-service/package.json << 'EOF'
{
  "name": "task-service",
  "version": "1.0.0",
  "description": "Task management microservice",
  "main": "app.js",
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^7.3.0"
  }
}
EOF

cat > services/auth-service/package.json << 'EOF'
{
  "name": "auth-service", 
  "version": "1.0.0",
  "description": "Authentication microservice",
  "main": "app.js",
  "dependencies": {
    "express": "^4.18.2",
    "jsonwebtoken": "^9.0.0"
  }
}
EOF

git add services/
git commit -m "config: add microservice configurations

- Individual package.json for each service
- Service-specific dependencies
- Independent versioning capability

Services:
- task-service: Task CRUD operations
- auth-service: Authentication and authorization
- notification-service: Email and push notifications"
```

## 🎯 Gestione File per Ambiente

### Development vs Production
```bash
# File specifici per ambiente
mkdir -p config/{development,production,testing}

# Configurazione development
cat > config/development/database.js << 'EOF'
module.exports = {
  mongodb: {
    uri: 'mongodb://localhost:27017/taskmanager_dev',
    options: {
      useNewUrlParser: true,
      useUnifiedTopology: true
    }
  },
  redis: {
    host: 'localhost',
    port: 6379,
    db: 1
  }
};
EOF

# Configurazione production
cat > config/production/database.js << 'EOF'
module.exports = {
  mongodb: {
    uri: process.env.MONGODB_URI,
    options: {
      useNewUrlParser: true,
      useUnifiedTopology: true,
      maxPoolSize: 10,
      serverSelectionTimeoutMS: 5000
    }
  },
  redis: {
    host: process.env.REDIS_HOST,
    port: process.env.REDIS_PORT || 6379,
    password: process.env.REDIS_PASSWORD
  }
};
EOF

# Script deployment
cat > deploy/deploy.sh << 'EOF'
#!/bin/bash
# Production deployment script

set -e

echo "🚀 Starting production deployment..."

# Build frontend
cd frontend
npm run build
echo "✅ Frontend built"

# Install backend dependencies
cd ../backend
npm ci --only=production
echo "✅ Backend dependencies installed"

# Run migrations
npm run migrate
echo "✅ Database migrations completed"

# Start services
pm2 restart ecosystem.config.js
echo "✅ Services restarted"

echo "🎉 Deployment completed successfully!"
EOF

chmod +x deploy/deploy.sh

git add config/ deploy/
git commit -m "config: add environment-specific configurations and deployment

Added:
- Development database configuration with local MongoDB
- Production configuration with environment variables
- Deployment script with build and migration steps

Features:
- Environment-specific database connections
- Production optimizations (connection pooling)
- Automated deployment process"
```

## 🎯 Gestione File Temporanei e Cache

```bash
# File temporanei che Git dovrebbe ignorare
mkdir -p {logs,temp,cache}

# Genera file temporanei di esempio
echo "$(date): Server started" > logs/app.log
echo "$(date): Debug info" > logs/debug.log
echo "Temporary data" > temp/processing.tmp
echo "Cache data" > cache/api-cache.json

# Verifica cosa Git vede
git status
# Output dovrebbe mostrare solo file non in .gitignore

# Test .gitignore effectiveness
git add .
git status

# Dovrebbe essere staging solo file non esclusi
git commit -m "test: verify .gitignore exclusions working correctly"

# Cleanup temporaneo
rm -rf logs/*.log temp/*.tmp cache/*.json
echo "✅ Temporary files cleaned up"
```

## 🔍 Analisi e Debug File

### Trovare File Grandi
```bash
# Script per trovare file grandi nel repository
cat > scripts/find-large-files.sh << 'EOF'
#!/bin/bash
# Trova file grandi che potrebbero rallentare il repository

echo "🔍 Analizzando file nel repository..."

echo -e "\n📊 File più grandi (top 10):"
find . -name ".git" -prune -o -type f -exec ls -lh {} \; | \
  sort -k5 -hr | head -10

echo -e "\n⚠️  File che dovrebbero essere in .gitignore:"
find . \( -name "*.log" -o -name "*.tmp" -o -name "node_modules" \
       -o -name "*.sqlite" -o -name ".env" \) -not -path "./.git/*"

echo -e "\n📈 Statistiche directory:"
du -sh */ 2>/dev/null | sort -hr | head -10
EOF

chmod +x scripts/find-large-files.sh
bash scripts/find-large-files.sh
```

### Audit File Tracking
```bash
# Script per audit di cosa è tracciato
cat > scripts/file-audit.sh << 'EOF'
#!/bin/bash
echo "📋 Audit file Git repository"

echo -e "\n📊 File tracciati per categoria:"
git ls-files | grep -E '\.(js|jsx|ts|tsx)$' | wc -l | xargs echo "JavaScript/TypeScript:"
git ls-files | grep -E '\.(css|scss|sass)$' | wc -l | xargs echo "Styles:"
git ls-files | grep -E '\.(md|txt|doc)$' | wc -l | xargs echo "Documentation:"
git ls-files | grep -E '\.(json|yaml|yml)$' | wc -l | xargs echo "Configuration:"

echo -e "\n🔍 File più grandi tracciati:"
git ls-files | xargs ls -lh | sort -k5 -hr | head -5

echo -e "\n⚠️  Potenziali problemi:"
git ls-files | grep -E '\.(log|tmp|cache)$' || echo "✅ Nessun file temporaneo tracciato"
git ls-files | grep -E 'node_modules|\.env$' || echo "✅ Nessun file sensibile tracciato"
EOF

chmod +x scripts/file-audit.sh
git add scripts/
git commit -m "tools: add repository analysis and audit scripts

Added:
- find-large-files.sh: Analyze file sizes and find optimization opportunities
- file-audit.sh: Audit what files are tracked by Git

Usage:
- Run before repository cleanup
- Regular health checks
- Pre-deployment verification"
```

## 🎓 Quiz di Verifica

1. **Come gestisci file che devono esistere ma non essere tracciati?**
2. **Qual è la differenza tra `git rm` e `git rm --cached`?**
3. **Come riorganizzi file mantenendo la cronologia Git?**

### Risposte
1. **`.gitkeep` file per directory vuote, `.gitignore` per esclusioni, `.example` files per template**
2. **`git rm` rimuove da filesystem e Git, `git rm --cached` rimuove solo da Git**
3. **Usa `git mv` per spostamenti, mantiene automaticamente la cronologia**

## 🔗 Comandi Correlati

- `git ls-files` - Lista file tracciati
- `git clean` - Rimuove file non tracciati
- `git mv` - Sposta file mantenendo cronologia
- `git rm --cached` - Rimuove dal tracking
- `find` - Trova file per operazioni batch

## 📚 Risorse Aggiuntive

- [.gitignore Templates](https://github.com/github/gitignore)
- [Git File Management](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)
- [Repository Organization Best Practices](https://docs.github.com/en/repositories/creating-and-managing-repositories)

---

**Prossimo**: [04 - Utilizzo Git Diff](./04-utilizzo-git-diff.md) - Analisi avanzata delle differenze
