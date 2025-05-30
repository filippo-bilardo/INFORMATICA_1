# Esercizio 3: Simulazione Lavoro di Team

## Obiettivo
Simulare un ambiente di lavoro collaborativo utilizzando branch multipli e workflow realistici.

## Setup Iniziale

### Crea il Progetto Team
```bash
mkdir team-collaboration-sim
cd team-collaboration-sim
git init
echo "# Team Project Simulator" > README.md
git add README.md
git commit -m "Initial project setup"
```

### Struttura Progetto Simulato
```bash
# Crea struttura base
mkdir -p src/{components,utils,styles}
mkdir -p docs
mkdir -p tests

# File base
echo "console.log('Main app');" > src/app.js
echo "/* Main styles */" > src/styles/main.css
echo "# Documentation" > docs/README.md
git add .
git commit -m "Add project structure"
```

## Scenario: Sviluppo Applicazione Web

### Team Roles
Simulerai 4 sviluppatori con ruoli diversi:

1. **Alex (Frontend Lead)**: Componenti UI
2. **Bob (Backend Dev)**: API e utilities
3. **Charlie (QA)**: Testing e documentazione
4. **Dana (DevOps)**: Build e deployment

## Fase 1: Sviluppo Parallelo

### Alex - Componente Header
```bash
# Alex inizia lavoro su header
git checkout -b feature/header-component

# Simula sviluppo
cat > src/components/header.js << 'EOF'
// Header Component
class Header {
    constructor() {
        this.title = "Team Project";
    }
    
    render() {
        return `<header><h1>${this.title}</h1></header>`;
    }
}

export default Header;
EOF

git add src/components/header.js
git commit -m "Add header component structure"

# Continua sviluppo
cat >> src/components/header.js << 'EOF'

// Navigation functionality
Header.prototype.addNavigation = function(items) {
    this.navItems = items;
};
EOF

git add -u
git commit -m "Add navigation functionality to header"
```

### Bob - Utility Functions
```bash
# Bob lavora su utilities (cambia branch)
git checkout main
git checkout -b feature/utility-functions

# Simula sviluppo API utilities
cat > src/utils/api.js << 'EOF'
// API Utility Functions
class APIClient {
    constructor(baseURL) {
        this.baseURL = baseURL;
    }
    
    async get(endpoint) {
        const response = await fetch(`${this.baseURL}${endpoint}`);
        return response.json();
    }
    
    async post(endpoint, data) {
        const response = await fetch(`${this.baseURL}${endpoint}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(data),
        });
        return response.json();
    }
}

export default APIClient;
EOF

git add src/utils/api.js
git commit -m "Add API client utility"

# Aggiunge validazione
cat > src/utils/validation.js << 'EOF'
// Validation utilities
export const validateEmail = (email) => {
    const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return regex.test(email);
};

export const validatePassword = (password) => {
    return password.length >= 8;
};
EOF

git add src/utils/validation.js
git commit -m "Add validation utilities"
```

### Charlie - Testing Setup
```bash
# Charlie lavora su testing
git checkout main
git checkout -b feature/testing-setup

# Setup test structure
cat > tests/test-utils.js << 'EOF'
// Test utilities
export const createMockElement = (tag) => {
    return {
        tag,
        innerHTML: '',
        children: [],
        appendChild: function(child) {
            this.children.push(child);
        }
    };
};

export const assertContains = (container, text) => {
    return container.innerHTML.includes(text);
};
EOF

git add tests/test-utils.js
git commit -m "Add test utilities"

# Test configuration
cat > tests/config.js << 'EOF'
// Test configuration
export const testConfig = {
    timeout: 5000,
    retries: 3,
    verbose: true
};
EOF

git add tests/config.js
git commit -m "Add test configuration"
```

### Dana - Build Configuration
```bash
# Dana configura build system
git checkout main
git checkout -b feature/build-system

# Package.json simulato
cat > package.json << 'EOF'
{
  "name": "team-project-sim",
  "version": "1.0.0",
  "description": "Team collaboration simulation",
  "main": "src/app.js",
  "scripts": {
    "build": "echo 'Building project...'",
    "test": "echo 'Running tests...'",
    "start": "echo 'Starting dev server...'",
    "deploy": "echo 'Deploying...'",
    "lint": "echo 'Linting code...'"
  },
  "dependencies": {},
  "devDependencies": {}
}
EOF

git add package.json
git commit -m "Add package.json and build scripts"

# Dockerfile
cat > Dockerfile << 'EOF'
FROM node:16-alpine
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
EXPOSE 3000
CMD ["npm", "start"]
EOF

git add Dockerfile
git commit -m "Add Docker configuration"
```

## Fase 2: Gestione Conflitti

### Simula Conflitto
```bash
# Alex e Bob modificano stesso file
git checkout feature/header-component

# Alex aggiunge import in app.js
cat > src/app.js << 'EOF'
import Header from './components/header.js';

console.log('Main app');

const header = new Header();
document.body.appendChild(header.render());
EOF

git add src/app.js
git commit -m "Integrate header component in main app"

# Bob modifica app.js diversamente
git checkout feature/utility-functions

cat > src/app.js << 'EOF'
import APIClient from './utils/api.js';
import { validateEmail } from './utils/validation.js';

console.log('Main app');

const api = new APIClient('https://api.example.com');
console.log('API client initialized');
EOF

git add src/app.js
git commit -m "Integrate API utilities in main app"
```

## Fase 3: Integrazione e Risoluzione

### Merge delle Feature (simula team lead)
```bash
# Torna su main
git checkout main

# Merge Bob per primo (più semplice)
git merge feature/utility-functions
echo "✅ Merged Bob's utilities"

# Merge Charlie
git merge feature/testing-setup
echo "✅ Merged Charlie's testing setup"

# Merge Dana
git merge feature/build-system
echo "✅ Merged Dana's build system"

# Merge Alex (conflitto!)
git merge feature/header-component
```

### Risoluzione Conflitto
```bash
# Git mostrerà conflitto in app.js
# Risolvi manualmente creando versione combinata
cat > src/app.js << 'EOF'
import Header from './components/header.js';
import APIClient from './utils/api.js';
import { validateEmail } from './utils/validation.js';

console.log('Main app');

// Initialize header
const header = new Header();
document.body.innerHTML = header.render();

// Initialize API client
const api = new APIClient('https://api.example.com');
console.log('API client initialized');

// Example usage
if (validateEmail('test@example.com')) {
    console.log('Valid email');
}
EOF

git add src/app.js
git commit -m "Resolve merge conflict: integrate all components"
```

## Fase 4: Cleanup e Documentazione

### Branch Cleanup
```bash
# Elimina branch feature completati
git branch -d feature/header-component
git branch -d feature/utility-functions
git branch -d feature/testing-setup
git branch -d feature/build-system

# Verifica pulizia
git branch
```

### Documentazione Finale
```bash
# Aggiorna README con contributi team
cat > README.md << 'EOF'
# Team Project Simulator

Simulazione di progetto collaborativo con Git.

## Team Contributors
- Alex: Header component and UI integration
- Bob: API utilities and validation
- Charlie: Testing framework setup
- Dana: Build system and deployment config

## Project Structure
```
src/
├── app.js              # Main application
├── components/         # UI components
│   └── header.js      # Header component
└── utils/             # Utility functions
    ├── api.js         # API client
    └── validation.js  # Validation helpers
tests/                 # Test setup
docs/                  # Documentation
```

## Setup
```bash
npm install
npm start
```

## Team Workflow Demonstrated
1. ✅ Parallel feature development
2. ✅ Branch management
3. ✅ Conflict resolution
4. ✅ Integration and cleanup
EOF

git add README.md
git commit -m "Update documentation with team contributions"
```

## Fase 5: Analisi e Riflessione

### Analizza la Storia del Progetto
```bash
# Visualizza storia completa
git log --oneline --graph --all

# Analizza contributori
git shortlog -s -n

# Verifica file modificati
git diff --name-only HEAD~10 HEAD
```

### Report del Team Exercise
Crea un file di analisi:

```bash
cat > TEAM_EXERCISE_REPORT.md << 'EOF'
# Team Exercise Analysis

## Workflow Utilizzato
- [x] Feature branching
- [x] Parallel development
- [x] Merge conflict resolution
- [x] Branch cleanup

## Sfide Affrontate
1. **Conflitti di merge**: Risolti integrando il lavoro di tutti
2. **Coordinamento**: Simulato workflow realistico
3. **Integrazione**: Combinato componenti diversi

## Lessons Learned
- Importanza di comunicazione nel team
- Branch naming conventions
- Conflict resolution strategies
- Integration planning

## Metrics
- Branch creati: 4
- Conflitti risolti: 1
- Commit totali: ~12
- File creati: 8
EOF

git add TEAM_EXERCISE_REPORT.md
git commit -m "Add team exercise analysis report"
```

## Sfide Aggiuntive

### Challenge 1: Hotfix Simulation
```bash
# Simula bug critico in produzione
git checkout -b hotfix/critical-security-fix

# Fix urgente
echo "// Security patch applied" >> src/utils/validation.js
git add -u
git commit -m "HOTFIX: Add security validation"

# Merge urgente
git checkout main
git merge hotfix/critical-security-fix
git branch -d hotfix/critical-security-fix
```

### Challenge 2: Release Branch
```bash
# Prepara release
git checkout -b release/v1.0.0
echo '"version": "1.0.0"' > VERSION
git add VERSION
git commit -m "Prepare release v1.0.0"

git checkout main
git merge release/v1.0.0
git tag v1.0.0
git branch -d release/v1.0.0
```

## Valutazione

### Checklist Completamento:
- [ ] 4 branch feature creati e sviluppati
- [ ] Conflitto risolto correttamente
- [ ] Branch cleanup eseguito
- [ ] Documentazione aggiornata
- [ ] Storia del progetto analizzata
- [ ] Report scritto

### Competenze Dimostrate:
- [ ] Gestione branch paralleli
- [ ] Risoluzione conflitti
- [ ] Workflow collaborativo
- [ ] Best practices Git

---

Questo esercizio simula realisticamente il lavoro di team con Git, preparandoti per collaborazioni reali!
