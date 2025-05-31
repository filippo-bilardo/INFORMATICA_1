# Esempio 2: Gestione Avanzata dei Conflitti di Merge

## 📝 Descrizione

Questo esempio si concentra sulla gestione avanzata dei conflitti di merge, dalla prevenzione alla risoluzione automatizzata. Include scenari realistici di conflitti complessi e strategie per minimizzare l'impatto sui team.

## 🎯 Obiettivi di Apprendimento

- Identificare e prevenire conflitti comuni
- Utilizzare strumenti avanzati per risoluzione conflitti
- Implementare strategie automatiche di merge
- Gestire conflitti in file binari e speciali

## 🚀 Setup del Laboratorio

### Creazione Environment di Test

```bash
# Setup repository per test conflitti
mkdir conflict-resolution-lab
cd conflict-resolution-lab
git init

# Configurazione per test
git config user.name "Conflict Resolver"
git config user.email "resolver@example.com"
git config merge.tool vimdiff
git config mergetool.vimdiff.path vim

# Abilita rerere per auto-risoluzione
git config rerere.enabled true
git config rerere.autoupdate true

# Crea struttura progetto
mkdir -p src/{components,utils,styles,config}
```

### File Base per Test Conflitti

```bash
# File principale dell'applicazione
cat > src/app.js << 'EOF'
// Main Application File
const config = require('./config/app-config');
const utils = require('./utils/helpers');

class Application {
    constructor() {
        this.version = '1.0.0';
        this.environment = 'development';
        this.features = [];
    }
    
    initialize() {
        console.log('Initializing application...');
        this.loadFeatures();
        this.setupEventListeners();
    }
    
    loadFeatures() {
        // Load application features
        this.features = ['auth', 'dashboard'];
    }
    
    setupEventListeners() {
        // Setup event handling
        document.addEventListener('DOMContentLoaded', this.onReady.bind(this));
    }
    
    onReady() {
        console.log('Application ready');
    }
}

module.exports = Application;
EOF

# File di configurazione
cat > src/config/app-config.js << 'EOF'
module.exports = {
    database: {
        host: 'localhost',
        port: 5432,
        name: 'myapp'
    },
    api: {
        baseUrl: '/api/v1',
        timeout: 5000
    },
    features: {
        auth: true,
        dashboard: true
    }
};
EOF

# File di utilities
cat > src/utils/helpers.js << 'EOF'
function formatDate(date) {
    return date.toISOString().split('T')[0];
}

function validateEmail(email) {
    const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return regex.test(email);
}

function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
        const later = () => {
            clearTimeout(timeout);
            func(...args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    };
}

module.exports = {
    formatDate,
    validateEmail,
    debounce
};
EOF

# Commit iniziale
git add .
git commit -m "feat: initial project setup with base files"
```

## ⚡ Scenario 1: Conflitti di Sviluppo Parallelo

### Branch Team Frontend

```bash
# Team Frontend - Modifiche UI
git checkout -b feature/frontend-improvements

# Modifica app.js per nuove features UI
cat > src/app.js << 'EOF'
// Main Application File - Enhanced UI Version
const config = require('./config/app-config');
const utils = require('./utils/helpers');
const UIManager = require('./components/ui-manager');

class Application {
    constructor() {
        this.version = '1.1.0';
        this.environment = 'development';
        this.features = [];
        this.uiManager = new UIManager();
    }
    
    initialize() {
        console.log('Initializing application with enhanced UI...');
        this.setupUI();
        this.loadFeatures();
        this.setupEventListeners();
    }
    
    setupUI() {
        this.uiManager.initializeTheme();
        this.uiManager.setupComponents();
    }
    
    loadFeatures() {
        // Load application features with UI enhancements
        this.features = ['auth', 'dashboard', 'notifications', 'profile'];
    }
    
    setupEventListeners() {
        // Setup enhanced event handling
        document.addEventListener('DOMContentLoaded', this.onReady.bind(this));
        window.addEventListener('resize', this.onResize.bind(this));
    }
    
    onReady() {
        console.log('Application ready with enhanced UI');
        this.uiManager.showWelcomeAnimation();
    }
    
    onResize() {
        this.uiManager.handleResize();
    }
}

module.exports = Application;
EOF

# Aggiunge componente UI
cat > src/components/ui-manager.js << 'EOF'
class UIManager {
    constructor() {
        this.theme = 'light';
        this.components = [];
    }
    
    initializeTheme() {
        document.body.className = `theme-${this.theme}`;
    }
    
    setupComponents() {
        this.components = ['header', 'sidebar', 'footer'];
    }
    
    showWelcomeAnimation() {
        console.log('Playing welcome animation...');
    }
    
    handleResize() {
        console.log('Handling window resize...');
    }
}

module.exports = UIManager;
EOF

# Modifica configurazione per UI
sed -i 's/"dashboard": true/"dashboard": true,\n        "notifications": true,\n        "profile": true/' src/config/app-config.js

git add .
git commit -m "feat: add enhanced UI components and features

- Add UIManager for theme and component handling
- Enhanced event listeners for better UX
- Add notifications and profile features
- Welcome animation and responsive design"
```

### Branch Team Backend

```bash
# Team Backend - Modifiche API e Database
git checkout main
git checkout -b feature/backend-api-v2

# Modifica app.js per nuove API
cat > src/app.js << 'EOF'
// Main Application File - Enhanced API Version
const config = require('./config/app-config');
const utils = require('./utils/helpers');
const APIManager = require('./utils/api-manager');

class Application {
    constructor() {
        this.version = '1.2.0';
        this.environment = 'development';
        this.features = [];
        this.apiManager = new APIManager();
    }
    
    initialize() {
        console.log('Initializing application with API v2...');
        this.connectDatabase();
        this.loadFeatures();
        this.setupEventListeners();
        this.startBackgroundTasks();
    }
    
    connectDatabase() {
        this.apiManager.initializeConnection();
    }
    
    loadFeatures() {
        // Load application features with API v2
        this.features = ['auth', 'dashboard', 'analytics', 'reporting'];
    }
    
    setupEventListeners() {
        // Setup API event handling
        document.addEventListener('DOMContentLoaded', this.onReady.bind(this));
        this.apiManager.on('error', this.handleAPIError.bind(this));
    }
    
    onReady() {
        console.log('Application ready with API v2');
        this.apiManager.healthCheck();
    }
    
    handleAPIError(error) {
        console.error('API Error:', error);
    }
    
    startBackgroundTasks() {
        this.apiManager.startDataSync();
    }
}

module.exports = Application;
EOF

# Aggiunge API Manager
cat > src/utils/api-manager.js << 'EOF'
class APIManager {
    constructor() {
        this.baseUrl = '/api/v2';
        this.isConnected = false;
    }
    
    initializeConnection() {
        console.log('Connecting to database...');
        this.isConnected = true;
    }
    
    healthCheck() {
        return fetch(`${this.baseUrl}/health`);
    }
    
    startDataSync() {
        setInterval(() => {
            console.log('Syncing data...');
        }, 30000);
    }
    
    on(event, callback) {
        // Event listener setup
        document.addEventListener(`api-${event}`, callback);
    }
}

module.exports = APIManager;
EOF

# Modifica configurazione per API v2
sed -i 's|"baseUrl": "/api/v1"|"baseUrl": "/api/v2"|' src/config/app-config.js
sed -i 's/"dashboard": true/"dashboard": true,\n        "analytics": true,\n        "reporting": true/' src/config/app-config.js

git add .
git commit -m "feat: implement API v2 with enhanced backend features

- Add APIManager for database connectivity
- Implement health checks and data synchronization
- Add analytics and reporting features
- Enhanced error handling and monitoring"
```

## 🔥 Conflitto Complesso e Risoluzione

### Tentativo di Merge con Conflitti

```bash
# Torna a main per preparare merge
git checkout main

# Merge primo branch (Frontend)
echo -e "\n🔀 Merging frontend improvements..."
git merge --no-ff feature/frontend-improvements -m "Merge frontend UI enhancements"

# Tentativo merge secondo branch (conflitti inevitabili)
echo -e "\n⚠️  Attempting backend merge (conflicts expected)..."
git merge feature/backend-api-v2 || {
    echo -e "\n🔥 CONFLICTS DETECTED!"
    echo -e "\n📋 Conflicted files:"
    git status --short | grep "UU"
    
    echo -e "\n🔍 Analyzing conflicts in src/app.js:"
    git diff HEAD:src/app.js feature/backend-api-v2:src/app.js
}
```

### Risoluzione Strategica dei Conflitti

```bash
# Analizza conflitti dettagliatamente
echo -e "\n📊 Conflict analysis:"
git merge-tree $(git merge-base HEAD feature/backend-api-v2) HEAD feature/backend-api-v2

# Strategia: Merge intelligente mantenendo entrambe le funzionalità
cat > src/app.js << 'EOF'
// Main Application File - Unified Frontend & Backend
const config = require('./config/app-config');
const utils = require('./utils/helpers');
const UIManager = require('./components/ui-manager');
const APIManager = require('./utils/api-manager');

class Application {
    constructor() {
        this.version = '2.0.0';  // Versione unificata
        this.environment = 'development';
        this.features = [];
        this.uiManager = new UIManager();
        this.apiManager = new APIManager();
    }
    
    initialize() {
        console.log('Initializing unified application...');
        this.setupUI();
        this.connectDatabase();
        this.loadFeatures();
        this.setupEventListeners();
        this.startBackgroundTasks();
    }
    
    setupUI() {
        this.uiManager.initializeTheme();
        this.uiManager.setupComponents();
    }
    
    connectDatabase() {
        this.apiManager.initializeConnection();
    }
    
    loadFeatures() {
        // Combinazione di tutte le features
        this.features = [
            'auth', 
            'dashboard', 
            'notifications',  // da frontend
            'profile',        // da frontend
            'analytics',      // da backend
            'reporting'       // da backend
        ];
    }
    
    setupEventListeners() {
        // Setup event handling unificato
        document.addEventListener('DOMContentLoaded', this.onReady.bind(this));
        window.addEventListener('resize', this.onResize.bind(this));
        this.apiManager.on('error', this.handleAPIError.bind(this));
    }
    
    onReady() {
        console.log('Unified application ready');
        this.uiManager.showWelcomeAnimation();
        this.apiManager.healthCheck();
    }
    
    onResize() {
        this.uiManager.handleResize();
    }
    
    handleAPIError(error) {
        console.error('API Error:', error);
        this.uiManager.showErrorNotification(error);
    }
    
    startBackgroundTasks() {
        this.apiManager.startDataSync();
    }
}

module.exports = Application;
EOF

# Risolve conflitto in configurazione
cat > src/config/app-config.js << 'EOF'
module.exports = {
    database: {
        host: 'localhost',
        port: 5432,
        name: 'myapp'
    },
    api: {
        baseUrl: '/api/v2',  // Versione aggiornata
        timeout: 5000
    },
    features: {
        // Combinazione di tutte le features
        auth: true,
        dashboard: true,
        notifications: true,   // frontend
        profile: true,         // frontend
        analytics: true,       // backend
        reporting: true        // backend
    }
};
EOF

# Aggiorna UIManager per gestire errori API
cat >> src/components/ui-manager.js << 'EOF'

    showErrorNotification(error) {
        console.log('Showing error notification:', error);
        // Implementation for error display
    }
EOF

# Conferma risoluzione
git add .
git commit -m "resolve: merge frontend and backend features

Unified Features:
✅ UI enhancements from frontend team
✅ API v2 improvements from backend team
✅ Combined feature set (6 total features)
✅ Cross-integration (API errors → UI notifications)

Conflict Resolution Strategy:
- Merged both UIManager and APIManager
- Combined all features from both branches
- Updated version to 2.0.0 (unified release)
- Enhanced error handling between frontend/backend

Technical Changes:
- app.js: Integrated both managers
- config: Combined feature flags
- Added cross-component communication"

echo -e "\n✅ Conflicts resolved successfully!"
```

## 🔧 Scenario 2: Conflitti in File Speciali

### Conflitti in Package.json

```bash
# Simula conflitti in file di configurazione
git checkout -b feature/dependency-update

# Team 1: Aggiorna dipendenze frontend
cat > package.json << 'EOF'
{
  "name": "conflict-resolution-app",
  "version": "2.0.0",
  "description": "Demo app for conflict resolution",
  "main": "src/app.js",
  "dependencies": {
    "react": "^18.0.0",
    "react-dom": "^18.0.0",
    "lodash": "^4.17.21",
    "axios": "^1.0.0"
  },
  "devDependencies": {
    "jest": "^28.0.0",
    "eslint": "^8.0.0"
  },
  "scripts": {
    "start": "node src/app.js",
    "test": "jest",
    "build": "webpack --mode production"
  }
}
EOF

git add package.json
git commit -m "feat: update frontend dependencies (React 18, ESLint 8)"

# Team 2: Aggiorna dipendenze backend
git checkout main
git checkout -b feature/backend-deps

cat > package.json << 'EOF'
{
  "name": "conflict-resolution-app",
  "version": "2.0.0",
  "description": "Demo app for conflict resolution",
  "main": "src/app.js",
  "dependencies": {
    "express": "^4.18.0",
    "mongodb": "^4.5.0",
    "lodash": "^4.17.20",
    "bcrypt": "^5.0.1"
  },
  "devDependencies": {
    "mocha": "^10.0.0",
    "supertest": "^6.2.0"
  },
  "scripts": {
    "start": "node src/app.js",
    "test": "mocha",
    "dev": "nodemon src/app.js"
  }
}
EOF

git add package.json
git commit -m "feat: add backend dependencies (Express, MongoDB)"
```

### Risoluzione Intelligente Package.json

```bash
# Merge con strategia custom per package.json
git checkout main
git merge --no-ff feature/dependency-update -m "Merge frontend dependencies"

# Conflitto nel secondo merge
git merge feature/backend-deps || {
    echo -e "\n📦 Resolving package.json conflicts intelligently..."
    
    # Risoluzione strategica: unione dipendenze
    cat > package.json << 'EOF'
{
  "name": "conflict-resolution-app",
  "version": "2.0.0",
  "description": "Demo app for conflict resolution",
  "main": "src/app.js",
  "dependencies": {
    "react": "^18.0.0",
    "react-dom": "^18.0.0",
    "express": "^4.18.0",
    "mongodb": "^4.5.0",
    "lodash": "^4.17.21",
    "axios": "^1.0.0",
    "bcrypt": "^5.0.1"
  },
  "devDependencies": {
    "jest": "^28.0.0",
    "mocha": "^10.0.0",
    "eslint": "^8.0.0",
    "supertest": "^6.2.0"
  },
  "scripts": {
    "start": "node src/app.js",
    "test": "npm run test:frontend && npm run test:backend",
    "test:frontend": "jest",
    "test:backend": "mocha",
    "build": "webpack --mode production",
    "dev": "nodemon src/app.js"
  }
}
EOF

    git add package.json
    git commit -m "resolve: merge frontend and backend dependencies

- Combined React and Express dependencies
- Unified testing setup (Jest + Mocha)
- Added comprehensive script commands
- Resolved lodash version conflict to latest
- Enhanced development workflow"
}

# Cleanup
git branch -d feature/dependency-update feature/backend-deps
```

## 🤖 Scenario 3: Automazione Risoluzione Conflitti

### Setup Rerere (Reuse Recorded Resolution)

```bash
# Simula conflitto ricorrente
git checkout -b feature/recurring-conflict

# Modifica che genererà conflitto ricorrente
sed -i 's/version.*:.*/version: "2.1.0-beta",/' src/app.js
git add src/app.js
git commit -m "bump: version to 2.1.0-beta"

# Merge con conflitto
git checkout main
git merge feature/recurring-conflict || {
    echo -e "\n🔄 First time conflict - manual resolution"
    
    # Risoluzione manuale
    sed -i 's/version.*:.*/version: "2.1.0",/' src/app.js
    git add src/app.js
    git commit -m "resolve: standardize version format"
}

# Cleanup e prepara per test rerere
git branch -d feature/recurring-conflict
git reset --hard HEAD~2  # Torna indietro per simulare

# Ricrea conflitto identico
git checkout -b feature/recurring-conflict-2
sed -i 's/version.*:.*/version: "2.1.0-beta",/' src/app.js
git add src/app.js
git commit -m "bump: version to 2.1.0-beta (second time)"

# Test rerere - dovrebbe auto-risolvere
git checkout main
echo -e "\n🤖 Testing rerere auto-resolution..."
git merge feature/recurring-conflict-2 && {
    echo -e "✅ Rerere automatically resolved the conflict!"
} || {
    echo -e "ℹ️  Manual resolution needed (rerere learning)"
    sed -i 's/version.*:.*/version: "2.1.0",/' src/app.js
    git add src/app.js
    git commit -m "resolve: auto-resolved via rerere"
}
```

### Script di Merge Automatico

```bash
# Crea script di merge intelligente
cat > scripts/smart-merge.sh << 'EOF'
#!/bin/bash
# Smart Merge Script con auto-risoluzione

set -e

BRANCH=$1
STRATEGY=${2:-auto}

if [ -z "$BRANCH" ]; then
    echo "Usage: $0 <branch> [strategy]"
    echo "Strategies: auto, manual, fast-forward, squash"
    exit 1
fi

echo "🔀 Starting smart merge of branch: $BRANCH"

# Pre-merge checks
echo "🔍 Running pre-merge validations..."

# Check if branch exists
if ! git show-ref --quiet refs/heads/$BRANCH; then
    echo "❌ Branch $BRANCH does not exist"
    exit 1
fi

# Check for uncommitted changes
if ! git diff-index --quiet HEAD --; then
    echo "❌ Uncommitted changes detected. Stash or commit first."
    exit 1
fi

# Determine best merge strategy
if [ "$STRATEGY" == "auto" ]; then
    if git merge-base --is-ancestor $BRANCH HEAD; then
        echo "📈 Fast-forward merge detected"
        STRATEGY="fast-forward"
    elif [ $(git rev-list --count HEAD..$BRANCH) -eq 1 ]; then
        echo "🔄 Single commit merge - using fast-forward"
        STRATEGY="fast-forward"
    else
        echo "🌳 Multiple commits - using three-way merge"
        STRATEGY="three-way"
    fi
fi

# Execute merge based on strategy
case $STRATEGY in
    "fast-forward")
        git merge --ff-only $BRANCH
        ;;
    "squash")
        git merge --squash $BRANCH
        echo "⚠️  Remember to commit the squashed changes"
        ;;
    "three-way")
        git merge --no-ff $BRANCH -m "Automatic merge of $BRANCH" || {
            echo "⚠️  Conflicts detected - attempting auto-resolution..."
            
            # Try common auto-resolutions
            for file in $(git diff --name-only --diff-filter=U); do
                case $file in
                    "package.json")
                        echo "🔧 Auto-resolving package.json..."
                        git checkout --theirs $file
                        ;;
                    "*.md")
                        echo "🔧 Auto-resolving documentation..."
                        git checkout --union $file
                        ;;
                    *)
                        echo "❓ Manual resolution needed for: $file"
                        ;;
                esac
            done
            
            # Check if all conflicts resolved
            if git diff --name-only --diff-filter=U | grep -q .; then
                echo "❌ Some conflicts require manual resolution"
                echo "Conflicted files:"
                git diff --name-only --diff-filter=U
                exit 1
            else
                git add .
                git commit -m "Auto-resolved conflicts in merge of $BRANCH"
            fi
        }
        ;;
    *)
        echo "❌ Unknown strategy: $STRATEGY"
        exit 1
        ;;
esac

# Post-merge validation
echo "✅ Merge completed successfully"
echo "📊 Merge summary:"
git log --oneline -1
git diff --stat HEAD~1..HEAD

# Cleanup
echo "🧹 Cleaning up..."
git branch -d $BRANCH 2>/dev/null || echo "ℹ️  Branch $BRANCH not deleted (remote or protected)"

echo "🎉 Smart merge completed!"
EOF

chmod +x scripts/smart-merge.sh

# Test script
mkdir -p scripts
git add scripts/smart-merge.sh
git commit -m "feat: add smart merge automation script"
```

## 📊 Analisi e Monitoraggio Conflitti

### Script di Analisi Conflitti

```bash
# Script per analizzare pattern di conflitti
cat > scripts/conflict-analysis.sh << 'EOF'
#!/bin/bash
# Conflict Analysis Tool

echo "📊 CONFLICT ANALYSIS REPORT"
echo "=========================="

echo -e "\n🔥 Most conflict-prone files (last 3 months):"
git log --since="3 months ago" --grep="conflict\|resolve" --oneline | \
while read commit; do
    git show --name-only $commit | tail -n +2
done | sort | uniq -c | sort -nr | head -10

echo -e "\n📈 Conflict resolution timeline:"
git log --since="3 months ago" --grep="resolve" --pretty=format:"%h %ad %s" --date=short | head -10

echo -e "\n👥 Top conflict resolvers:"
git log --since="3 months ago" --grep="resolve" --pretty=format:"%an" | \
sort | uniq -c | sort -nr | head -5

echo -e "\n🌳 Merge statistics:"
echo "Total merges: $(git log --merges --oneline | wc -l)"
echo "Conflict merges: $(git log --grep="resolve\|conflict" --oneline | wc -l)"

echo -e "\n💡 Conflict hotspots by file type:"
git log --since="3 months ago" --grep="conflict\|resolve" --name-only --pretty=format:"" | \
grep -E '\.[a-zA-Z]+$' | sed 's/.*\.//' | sort | uniq -c | sort -nr
EOF

chmod +x scripts/conflict-analysis.sh

# Aggiungi al repository
git add scripts/conflict-analysis.sh
git commit -m "feat: add conflict analysis and monitoring tools"

# Esegui analisi
echo -e "\n📊 Running conflict analysis..."
./scripts/conflict-analysis.sh
```

## 💡 Best Practices per Prevenzione Conflitti

### Pre-commit Hooks per Validazione

```bash
# Setup pre-commit hook
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Pre-commit validation to prevent conflicts

echo "🔍 Running pre-commit validations..."

# Check for conflict markers left in code
if grep -r "<<<<<<< \|======= \|>>>>>>> " src/ 2>/dev/null; then
    echo "❌ Conflict markers found in code!"
    echo "Files with conflict markers:"
    grep -r "<<<<<<< \|======= \|>>>>>>> " src/ | cut -d: -f1 | sort | uniq
    exit 1
fi

# Validate JSON files
for file in $(git diff --cached --name-only | grep '\.json$'); do
    if ! python -m json.tool "$file" > /dev/null 2>&1; then
        echo "❌ Invalid JSON in $file"
        exit 1
    fi
done

# Check for large files that might cause merge issues
for file in $(git diff --cached --name-only); do
    if [ -f "$file" ] && [ $(wc -l < "$file") -gt 1000 ]; then
        echo "⚠️  Large file detected: $file ($(wc -l < "$file") lines)"
        echo "Consider splitting or using Git LFS"
    fi
done

echo "✅ Pre-commit validations passed"
EOF

chmod +x .git/hooks/pre-commit
```

### Configurazione Merge Tools

```bash
# Configura merge tools avanzati
git config merge.tool vscode
git config mergetool.vscode.cmd 'code --wait $MERGED'

# Alternative: Configurazione per diversi editor
git config merge.tool meld
git config mergetool.meld.cmd 'meld "$LOCAL" "$MERGED" "$REMOTE" --output "$MERGED"'

# Per IntelliJ IDEA
git config merge.tool idea
git config mergetool.idea.cmd 'idea merge "$LOCAL" "$REMOTE" "$BASE" "$MERGED"'

echo -e "\n🛠️  Merge tool configured. Test with:"
echo "git mergetool"
```

## 📋 Riepilogo e Checklist

### Strategie di Risoluzione Conflitti

| Tipo Conflitto | Strategia | Comando/Tool | Quando Usare |
|----------------|-----------|--------------|--------------|
| Semplice modifiche | Auto-merge | `git merge` | File diversi |
| Stesso file, sezioni diverse | Three-way | `git mergetool` | Modifiche isolate |
| Stesse linee | Manuale | Editor + `git add` | Logica applicativa |
| File configurazione | Custom driver | `.gitattributes` | JSON, XML, etc. |
| Conflitti ricorrenti | Rerere | `git config rerere.enabled` | Pattern ripetuti |

### Checklist Risoluzione Conflitti

```markdown
## Pre-Merge
- [ ] Branch aggiornato con upstream
- [ ] Test passati su entrambi i branch
- [ ] Code review completato
- [ ] Backup creato (tag o branch)

## Durante Risoluzione
- [ ] Analizzato contesto del conflitto
- [ ] Testato entrambe le versioni
- [ ] Mantenuta funzionalità di entrambi i branch
- [ ] Aggiornata documentazione se necessario

## Post-Merge
- [ ] Test completi eseguiti
- [ ] Build verificato
- [ ] Conflitti documentati (se ricorrenti)
- [ ] Team notificato delle modifiche
```

## 🔄 Esercizi Pratici

1. **Simula Conflitti**: Crea conflitti intenzionali e pratica risoluzione
2. **Configura Tools**: Setup dei tuoi merge tools preferiti
3. **Automation**: Implementa script di merge personalizzati
4. **Analisi**: Usa gli script per analizzare conflitti nei tuoi progetti

## 📚 Riferimenti

- [03-Recursive Merge](../guide/03-recursive-merge.md) - Approfondimenti su merge complessi
- [06-Strategie Avanzate](../guide/06-strategie-avanzate.md) - Tecniche enterprise
- [Esercizi](../esercizi/README.md) - Pratica guidata

---

**Prossimo**: [03-Merge in Team Distribuiti](./03-distributed-teams.md)
