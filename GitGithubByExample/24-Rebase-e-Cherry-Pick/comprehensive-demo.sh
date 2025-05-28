#!/bin/bash

# =============================================================================
# COMPREHENSIVE GIT REBASE & CHERRY-PICK DEMONSTRATION
# =============================================================================
# 
# Questo script dimostra tutti i concetti avanzati di Git in un unico scenario
# realistico che combina sviluppo multi-team, hotfix, release management e
# best practices per rebase e cherry-pick.
#
# DURATA: 15-20 minuti per l'esecuzione completa
# SCOPO: Vedere in azione tutti i concetti prima di praticare negli esercizi
#
# =============================================================================

set -e  # Exit on any error

# Colors for better output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Function to print section headers
print_section() {
    echo -e "\n${BLUE}============================================${NC}"
    echo -e "${BLUE} $1${NC}"
    echo -e "${BLUE}============================================${NC}\n"
}

# Function to print step headers
print_step() {
    echo -e "\n${GREEN}🔸 $1${NC}\n"
}

# Function to print warnings
print_warning() {
    echo -e "\n${YELLOW}⚠️  $1${NC}\n"
}

# Function to print info
print_info() {
    echo -e "${CYAN}ℹ️  $1${NC}"
}

# Function to pause execution
pause_execution() {
    echo -e "\n${PURPLE}Press Enter to continue to next step...${NC}"
    read -r
}

# Function to show git log nicely
show_git_log() {
    echo -e "${CYAN}Current Git Log:${NC}"
    git log --oneline --graph --all --decorate
    echo ""
}

# Cleanup function
cleanup() {
    cd ..
    rm -rf comprehensive-git-demo 2>/dev/null || true
}

# =============================================================================
# MAIN DEMONSTRATION SCRIPT
# =============================================================================

print_section "COMPREHENSIVE GIT REBASE & CHERRY-PICK DEMO"

echo -e "${GREEN}Questo script dimostrerà:${NC}"
echo "✅ Setup ambiente multi-team"
echo "✅ Sviluppo parallelo su feature branches"
echo "✅ Gestione hotfix critici"
echo "✅ Interactive rebase per cleanup"
echo "✅ Cherry-pick strategico"
echo "✅ Confronto rebase vs merge"
echo "✅ Best practices per team"

echo -e "\n${YELLOW}Nota: Lo script creerà una cartella 'comprehensive-git-demo' nella directory corrente${NC}"

pause_execution

# =============================================================================
# PHASE 1: ENVIRONMENT SETUP
# =============================================================================

print_section "PHASE 1: SETUP AMBIENTE MULTI-TEAM"

print_step "Cleaning up any existing demo directory"
cleanup

print_step "Creating fresh demo environment"
mkdir comprehensive-git-demo && cd comprehensive-git-demo
git init
git config user.name "Demo Master"
git config user.email "demo@company.com"

print_step "Setting up initial project structure"
mkdir -p src/{auth,api,frontend} tests docs
cat > package.json << 'EOF'
{
  "name": "enterprise-app",
  "version": "1.0.0",
  "description": "Enterprise application demonstrating Git workflows",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "test": "jest",
    "build": "webpack --mode production"
  },
  "dependencies": {
    "express": "^4.18.0",
    "jsonwebtoken": "^9.0.0"
  }
}
EOF

cat > src/app.js << 'EOF'
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  res.json({ message: 'Enterprise App v1.0.0', status: 'running' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', version: '1.0.0' });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

cat > README.md << 'EOF'
# Enterprise Application

A comprehensive enterprise application demonstrating advanced Git workflows.

## Features
- Authentication system
- RESTful API
- Frontend interface
- Comprehensive testing

## Installation
```bash
npm install
```

## Usage
```bash
npm start
```
EOF

git add .
git commit -m "Initial enterprise application setup"

print_info "Base project created"
show_git_log
pause_execution

# =============================================================================
# PHASE 2: PARALLEL FEATURE DEVELOPMENT
# =============================================================================

print_section "PHASE 2: SVILUPPO PARALLELO FEATURE"

print_step "Team A: Developing Authentication System"
git checkout -b feature/auth-system
git config user.name "Developer A"
git config user.email "dev-a@company.com"

cat > src/auth/middleware.js << 'EOF'
const jwt = require('jsonwebtoken');

const authenticateToken = (req, res, next) => {
  const authHeader = req.headers['authorization'];
  const token = authHeader && authHeader.split(' ')[1]; // Bearer TOKEN

  if (!token) {
    return res.sendStatus(401);
  }

  jwt.verify(token, process.env.ACCESS_TOKEN_SECRET, (err, user) => {
    if (err) return res.sendStatus(403);
    req.user = user;
    next();
  });
};

module.exports = { authenticateToken };
EOF

git add .
git commit -m "Add JWT authentication middleware"

cat > src/auth/controller.js << 'EOF'
const jwt = require('jsonwebtoken');

// Mock user database
const users = [
  { id: 1, username: 'admin', password: 'admin123' },
  { id: 2, username: 'user', password: 'user123' }
];

const login = async (req, res) => {
  const { username, password } = req.body;
  
  const user = users.find(u => u.username === username && u.password === password);
  if (!user) {
    return res.status(401).json({ message: 'Invalid credentials' });
  }

  const accessToken = jwt.sign(
    { userId: user.id, username: user.username },
    process.env.ACCESS_TOKEN_SECRET || 'secret',
    { expiresIn: '1h' }
  );

  res.json({ accessToken, user: { id: user.id, username: user.username } });
};

const register = async (req, res) => {
  const { username, password } = req.body;
  
  if (users.find(u => u.username === username)) {
    return res.status(400).json({ message: 'User already exists' });
  }

  const newUser = { id: users.length + 1, username, password };
  users.push(newUser);
  
  res.status(201).json({ message: 'User registered successfully', user: { id: newUser.id, username } });
};

module.exports = { login, register };
EOF

git add .
git commit -m "Implement authentication controller with login/register"

# Add some debugging commits (that will need cleanup later)
echo "console.log('Debug: Auth middleware loaded');" >> src/auth/middleware.js
git add .
git commit -m "debug: add logging to middleware"

echo "// TODO: Add password hashing" >> src/auth/controller.js
git add .
git commit -m "TODO: remember to hash passwords"

print_step "Team B: Developing API Endpoints (parallel development)"
git checkout main
git checkout -b feature/api-endpoints
git config user.name "Developer B"
git config user.email "dev-b@company.com"

cat > src/api/routes.js << 'EOF'
const express = require('express');
const router = express.Router();

// Mock data store
let resources = [
  { id: 1, name: 'Resource 1', type: 'document', created: new Date().toISOString() },
  { id: 2, name: 'Resource 2', type: 'image', created: new Date().toISOString() }
];

// GET all resources
router.get('/resources', (req, res) => {
  res.json({ success: true, data: resources, count: resources.length });
});

// GET resource by ID
router.get('/resources/:id', (req, res) => {
  const resource = resources.find(r => r.id === parseInt(req.params.id));
  if (!resource) {
    return res.status(404).json({ success: false, message: 'Resource not found' });
  }
  res.json({ success: true, data: resource });
});

// POST new resource
router.post('/resources', (req, res) => {
  const { name, type } = req.body;
  const newResource = {
    id: resources.length + 1,
    name,
    type,
    created: new Date().toISOString()
  };
  resources.push(newResource);
  res.status(201).json({ success: true, data: newResource });
});

// PUT update resource
router.put('/resources/:id', (req, res) => {
  const resourceIndex = resources.findIndex(r => r.id === parseInt(req.params.id));
  if (resourceIndex === -1) {
    return res.status(404).json({ success: false, message: 'Resource not found' });
  }
  
  resources[resourceIndex] = { ...resources[resourceIndex], ...req.body };
  res.json({ success: true, data: resources[resourceIndex] });
});

// DELETE resource
router.delete('/resources/:id', (req, res) => {
  const resourceIndex = resources.findIndex(r => r.id === parseInt(req.params.id));
  if (resourceIndex === -1) {
    return res.status(404).json({ success: false, message: 'Resource not found' });
  }
  
  resources.splice(resourceIndex, 1);
  res.json({ success: true, message: 'Resource deleted' });
});

module.exports = router;
EOF

git add .
git commit -m "Implement CRUD API endpoints for resources"

cat > src/api/validation.js << 'EOF'
const validateResource = (req, res, next) => {
  const { name, type } = req.body;
  
  if (!name || !type) {
    return res.status(400).json({ 
      success: false, 
      message: 'Name and type are required fields' 
    });
  }
  
  if (name.length < 3) {
    return res.status(400).json({ 
      success: false, 
      message: 'Name must be at least 3 characters long' 
    });
  }
  
  const validTypes = ['document', 'image', 'video', 'audio'];
  if (!validTypes.includes(type)) {
    return res.status(400).json({ 
      success: false, 
      message: `Type must be one of: ${validTypes.join(', ')}` 
    });
  }
  
  next();
};

module.exports = { validateResource };
EOF

git add .
git commit -m "Add validation middleware for API endpoints"

print_info "Two feature branches created with parallel development"
show_git_log
pause_execution

# =============================================================================
# PHASE 3: CRITICAL HOTFIX ON MAIN
# =============================================================================

print_section "PHASE 3: CRITICAL HOTFIX SCENARIO"

print_warning "CRITICAL BUG DISCOVERED IN PRODUCTION!"

print_step "Applying critical security fix to main branch"
git checkout main
git config user.name "Security Team"
git config user.email "security@company.com"

# Create a critical security issue
cat > src/app.js << 'EOF'
const express = require('express');
const app = express();

// SECURITY FIX: Add security headers
app.use((req, res, next) => {
  res.setHeader('X-Content-Type-Options', 'nosniff');
  res.setHeader('X-Frame-Options', 'DENY');
  res.setHeader('X-XSS-Protection', '1; mode=block');
  next();
});

// SECURITY FIX: Add request logging
app.use((req, res, next) => {
  console.log(`${new Date().toISOString()} - ${req.method} ${req.path} - ${req.ip}`);
  next();
});

app.use(express.json({ limit: '10mb' })); // SECURITY FIX: Add body size limit

app.get('/', (req, res) => {
  res.json({ message: 'Enterprise App v1.0.1', status: 'running' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', version: '1.0.1' });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

# Update package.json version
sed -i 's/"version": "1.0.0"/"version": "1.0.1"/' package.json

git add .
git commit -m "CRITICAL SECURITY FIX: Add security headers and request logging"

print_info "Critical fix applied to main branch"
show_git_log
pause_execution

# =============================================================================
# PHASE 4: CHERRY-PICK SECURITY FIX TO FEATURE BRANCHES
# =============================================================================

print_section "PHASE 4: CHERRY-PICK SECURITY FIX"

print_step "Applying security fix to feature/auth-system branch"
git checkout feature/auth-system
git cherry-pick main

print_step "Applying security fix to feature/api-endpoints branch"
git checkout feature/api-endpoints  
git cherry-pick main

print_info "Security fix cherry-picked to both feature branches"
show_git_log
pause_execution

# =============================================================================
# PHASE 5: INTERACTIVE REBASE CLEANUP
# =============================================================================

print_section "PHASE 5: INTERACTIVE REBASE CLEANUP"

print_step "Cleaning up feature/auth-system branch history"
git checkout feature/auth-system

print_info "Before cleanup - messy history with debug commits:"
git log --oneline

print_warning "In real scenario, you would run: git rebase -i HEAD~4"
print_info "We'll simulate the cleanup by creating clean commits..."

# Reset to simulate interactive rebase cleanup
git reset --soft HEAD~3  # Keep changes but reset commits

# Create clean, professional commits
git add src/auth/middleware.js
git commit -m "Add JWT authentication middleware with security logging"

git add src/auth/controller.js  
git commit -m "Implement user authentication with login and registration"

print_info "After cleanup - clean, professional history:"
git log --oneline
pause_execution

# =============================================================================
# PHASE 6: REBASE VS MERGE COMPARISON
# =============================================================================

print_section "PHASE 6: REBASE VS MERGE COMPARISON"

print_step "Scenario A: Using MERGE strategy"
git checkout main
git checkout -b integration-merge

print_info "Merging feature branches with merge commits..."
git merge --no-ff feature/auth-system -m "Merge feature/auth-system - Authentication system implementation"
git merge --no-ff feature/api-endpoints -m "Merge feature/api-endpoints - RESTful API implementation"

print_info "Result with MERGE strategy:"
show_git_log

print_step "Scenario B: Using REBASE strategy"
git checkout main
git checkout -b integration-rebase

print_info "Rebasing feature branches for linear history..."

# Rebase auth system
git checkout feature/auth-system
git rebase main
git checkout integration-rebase
git merge feature/auth-system  # Fast-forward merge

# Rebase API endpoints
git checkout feature/api-endpoints
git rebase main  
git checkout integration-rebase
git merge feature/api-endpoints  # Fast-forward merge

print_info "Result with REBASE strategy:"
show_git_log
pause_execution

# =============================================================================
# PHASE 7: ADVANCED CHERRY-PICK SCENARIOS
# =============================================================================

print_section "PHASE 7: ADVANCED CHERRY-PICK SCENARIOS"

print_step "Creating experimental branch with selective features"
git checkout main
git checkout -b experimental/advanced-features

cat > src/experimental.js << 'EOF'
// Experimental advanced features
class AdvancedAnalytics {
  constructor() {
    this.metrics = [];
  }
  
  track(event, data) {
    this.metrics.push({
      event,
      data,
      timestamp: new Date().toISOString()
    });
  }
  
  getMetrics() {
    return this.metrics;
  }
}

module.exports = AdvancedAnalytics;
EOF

git add .
git commit -m "EXPERIMENTAL: Add advanced analytics tracking"

cat > src/cache.js << 'EOF'
// Simple caching system
class SimpleCache {
  constructor(ttl = 300000) { // 5 minutes default
    this.cache = new Map();
    this.ttl = ttl;
  }
  
  set(key, value) {
    this.cache.set(key, {
      value,
      timestamp: Date.now()
    });
  }
  
  get(key) {
    const item = this.cache.get(key);
    if (!item) return null;
    
    if (Date.now() - item.timestamp > this.ttl) {
      this.cache.delete(key);
      return null;
    }
    
    return item.value;
  }
  
  clear() {
    this.cache.clear();
  }
}

module.exports = SimpleCache;
EOF

git add .
git commit -m "Add simple caching system for performance"

cat > src/monitoring.js << 'EOF'
// Basic monitoring capabilities
class Monitor {
  constructor() {
    this.alerts = [];
  }
  
  checkHealth() {
    return {
      status: 'healthy',
      timestamp: new Date().toISOString(),
      uptime: process.uptime()
    };
  }
  
  addAlert(level, message) {
    this.alerts.push({
      level,
      message,
      timestamp: new Date().toISOString()
    });
  }
  
  getAlerts() {
    return this.alerts;
  }
}

module.exports = Monitor;
EOF

git add .
git commit -m "Add basic monitoring and alerting system"

print_step "Selectively cherry-picking only the caching feature"
git checkout integration-rebase
git cherry-pick experimental/advanced-features~1  # Cherry-pick only the cache commit

print_info "Selective cherry-pick completed - only cache feature added"
show_git_log
pause_execution

# =============================================================================
# PHASE 8: FINAL COMPARISON AND BEST PRACTICES
# =============================================================================

print_section "PHASE 8: FINAL ANALYSIS AND BEST PRACTICES"

print_step "Comparing final results"

echo -e "${CYAN}MERGE Strategy Result:${NC}"
git log --oneline --graph integration-merge

echo -e "\n${CYAN}REBASE Strategy Result:${NC}"  
git log --oneline --graph integration-rebase

echo -e "\n${CYAN}Experimental Branch:${NC}"
git log --oneline experimental/advanced-features

print_step "Demonstrating Git Workflow Best Practices"

echo -e "${GREEN}✅ BEST PRACTICES DEMONSTRATED:${NC}"
echo "1. 🔒 Security fixes applied immediately with cherry-pick"
echo "2. 🧹 Interactive rebase for clean commit history"
echo "3. 🔀 Strategic choice between merge and rebase"
echo "4. 🎯 Selective feature integration with cherry-pick"
echo "5. 📦 Feature branch isolation and testing"
echo "6. 🏷️  Clear commit messages and documentation"

echo -e "\n${YELLOW}⚠️  SAFETY REMINDERS:${NC}"
echo "• Never rebase commits that have been pushed and shared"
echo "• Always backup important branches before rebase operations"
echo "• Use interactive rebase only on private feature branches"
echo "• Cherry-pick is safer than rebase for shared repositories"
echo "• Test thoroughly after any history-modifying operation"

print_step "Creating summary documentation"
cat > WORKFLOW_SUMMARY.md << 'EOF'
# Git Workflow Demonstration Summary

## What Was Demonstrated

### 1. Parallel Feature Development
- Two teams working simultaneously on different features
- Isolated development in feature branches
- Independent commit histories

### 2. Critical Hotfix Management
- Security vulnerability discovered in production
- Immediate fix applied to main branch
- Cherry-pick to propagate fix to all active branches

### 3. Interactive Rebase Cleanup
- Messy development history with debug commits
- Interactive rebase to create professional commit history
- Squashing, reordering, and improving commit messages

### 4. Strategic Integration Approaches

#### Merge Strategy
- Preserves complete development history
- Shows when features were integrated
- Creates merge commits for context
- Better for collaborative environments

#### Rebase Strategy  
- Creates linear, clean history
- Easier to follow project progression
- Simpler for bisecting and debugging
- Better for solo development or small teams

### 5. Selective Feature Integration
- Cherry-pick specific commits from experimental branches
- Controlled feature rollout
- Risk mitigation for experimental code

## Key Takeaways

1. **Choose the right tool for the situation**
   - Use merge for collaborative feature integration
   - Use rebase for local cleanup and linear history
   - Use cherry-pick for selective feature adoption

2. **Safety first**
   - Never rewrite shared/published history
   - Always backup before destructive operations
   - Test after every major history change

3. **Communication is key**
   - Clear commit messages
   - Document workflow decisions
   - Coordinate with team on rebase policies

## Recommended Workflow

1. **Feature Development**: Work in isolated branches
2. **Local Cleanup**: Use interactive rebase before sharing
3. **Integration**: Choose merge vs rebase based on team policy
4. **Hotfixes**: Use cherry-pick for critical fixes
5. **Release**: Tag and document major milestones
EOF

git add WORKFLOW_SUMMARY.md
git commit -m "Add comprehensive workflow documentation and best practices"

print_info "Demonstration completed successfully!"
show_git_log

# =============================================================================
# CLEANUP AND FINAL MESSAGE
# =============================================================================

print_section "DEMONSTRATION COMPLETE!"

echo -e "${GREEN}🎉 Congratulations! You've seen a complete Git workflow in action.${NC}\n"

echo -e "${BLUE}What you've learned:${NC}"
echo "✅ Multi-team parallel development"
echo "✅ Critical hotfix management with cherry-pick"
echo "✅ Interactive rebase for professional commit history"
echo "✅ Strategic comparison of merge vs rebase approaches"
echo "✅ Selective feature integration techniques"
echo "✅ Safety practices and best practices"

echo -e "\n${YELLOW}Next Steps:${NC}"
echo "1. 📚 Study the generated WORKFLOW_SUMMARY.md"
echo "2. 🏋️  Practice with the individual exercises"
echo "3. 🛠️  Apply these techniques in your own projects"
echo "4. 👥 Discuss workflow policies with your team"

echo -e "\n${PURPLE}Demo environment created in: $(pwd)${NC}"
echo -e "${PURPLE}Feel free to explore the branches and commit history!${NC}"

echo -e "\n${CYAN}Useful commands to explore:${NC}"
echo "git log --oneline --graph --all"
echo "git branch -v"
echo "git show <commit-hash>"
echo "git diff <branch1>..<branch2>"

echo -e "\n${GREEN}Happy coding with Git! 🚀${NC}\n"
