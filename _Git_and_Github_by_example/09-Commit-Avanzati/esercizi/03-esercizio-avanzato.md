# Esercizio Avanzato: Workflow di Team e Gestione Avanzata dei Commit

## Obiettivo
Gestire uno scenario complesso di sviluppo in team utilizzando tecniche avanzate di commit, inclusi interactive rebase, squashing, cherry-picking e risoluzione di conflitti complessi.

## Scenario
Stai lavorando in un team di sviluppo su un'applicazione web. Il progetto ha una storia complessa con multiple feature branch, hotfix e commit che necessitano di essere riorganizzati prima del merge finale.

## Setup Iniziale

### 1. Preparazione del Repository
```bash
# Crea la directory del progetto
mkdir team-project-advanced
cd team-project-advanced

# Inizializza il repository
git init

# Configura il repository
git config user.name "Team Lead"
git config user.email "teamlead@company.com"
```

### 2. Creazione della Base del Progetto
```bash
# Crea la struttura del progetto
mkdir -p src/{components,utils,styles}
mkdir -p tests
mkdir docs

# File principale dell'applicazione
cat > src/app.js << 'EOF'
// Main Application
class App {
    constructor() {
        this.version = "1.0.0";
        this.modules = [];
    }

    init() {
        console.log(`Initializing App v${this.version}`);
        this.loadModules();
    }

    loadModules() {
        // TODO: Load application modules
    }
}

export default App;
EOF

# File di configurazione
cat > src/config.js << 'EOF'
export const config = {
    apiUrl: "https://api.example.com",
    timeout: 5000,
    debug: false
};
EOF

# File CSS
cat > src/styles/main.css << 'EOF'
/* Main Styles */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
}
EOF

# README iniziale
cat > README.md << 'EOF'
# Team Project

## Description
A collaborative web application project.

## Installation
```bash
npm install
```

## Usage
```bash
npm start
```
EOF

# Primo commit
git add .
git commit -m "Initial project setup

- Added basic application structure
- Created main app class
- Added configuration file
- Basic CSS styling"
```

## Parte 1: Sviluppo Parallelo con Problemi

### 3. Simulazione di Sviluppo Parallelo Problematico
```bash
# Branch per feature utente
git checkout -b feature/user-management

# Sviluppo del modulo utente (con commit disordinati)
cat > src/components/user.js << 'EOF'
// User Management Component
class UserManager {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        // TODO: Validate user
        this.users.push(user);
    }
}

export default UserManager;
EOF

git add src/components/user.js
git commit -m "WIP: user component"

# Aggiunta funzionalità (commit con typo nel messaggio)
cat >> src/components/user.js << 'EOF'

    removeUser(userId) {
        this.users = this.users.filter(u => u.id !== userId);
    }
EOF

git add src/components/user.js
git commit -m "add remov user method"

# Fix veloce (altro commit problematico)
sed -i 's/remov/remove/' src/components/user.js
git add src/components/user.js
git commit -m "fix typo"

# Aggiunta validazione
cat > src/utils/validation.js << 'EOF'
// Validation utilities
export function validateEmail(email) {
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(email);
}

export function validateUser(user) {
    if (!user.name || user.name.length < 2) {
        return false;
    }
    if (!user.email || !validateEmail(user.email)) {
        return false;
    }
    return true;
}
EOF

git add src/utils/validation.js
git commit -m "Add user validation utilities"

# Update user component per usare validazione
cat > src/components/user.js << 'EOF'
import { validateUser } from '../utils/validation.js';

// User Management Component
class UserManager {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        if (!validateUser(user)) {
            throw new Error('Invalid user data');
        }
        this.users.push({
            ...user,
            id: Date.now(),
            createdAt: new Date()
        });
    }

    removeUser(userId) {
        this.users = this.users.filter(u => u.id !== userId);
    }

    getUsers() {
        return [...this.users];
    }
}

export default UserManager;
EOF

git add src/components/user.js
git commit -m "Integrate validation in user manager"
```

### 4. Branch per API con Conflitti
```bash
# Torna a main e crea branch API
git checkout main

git checkout -b feature/api-client

# Sviluppo client API
cat > src/utils/api.js << 'EOF'
import { config } from '../config.js';

class ApiClient {
    constructor() {
        this.baseUrl = config.apiUrl;
        this.timeout = config.timeout;
    }

    async request(endpoint, options = {}) {
        const url = `${this.baseUrl}${endpoint}`;
        const defaultOptions = {
            headers: {
                'Content-Type': 'application/json'
            },
            timeout: this.timeout
        };

        const response = await fetch(url, { ...defaultOptions, ...options });
        return response.json();
    }
}

export default ApiClient;
EOF

git add src/utils/api.js
git commit -m "Add API client utility"

# Modifica config (creerà conflitto)
cat > src/config.js << 'EOF'
export const config = {
    apiUrl: "https://api.newdomain.com",
    timeout: 10000,
    debug: true,
    retryAttempts: 3
};
EOF

git add src/config.js
git commit -m "Update API configuration for production"

# Aggiunta metodi API specifici
cat >> src/utils/api.js << 'EOF'

    async getUsers() {
        return this.request('/users');
    }

    async createUser(userData) {
        return this.request('/users', {
            method: 'POST',
            body: JSON.stringify(userData)
        });
    }

    async deleteUser(userId) {
        return this.request(`/users/${userId}`, {
            method: 'DELETE'
        });
    }
EOF

git add src/utils/api.js
git commit -m "Add user-specific API methods"
```

### 5. Hotfix Branch
```bash
# Simulazione di hotfix urgente
git checkout main

git checkout -b hotfix/security-fix

# Fix di sicurezza
cat > src/utils/security.js << 'EOF'
// Security utilities
export function sanitizeInput(input) {
    if (typeof input !== 'string') {
        return '';
    }
    return input
        .replace(/[<>]/g, '')
        .replace(/javascript:/gi, '')
        .trim();
}

export function hashPassword(password) {
    // Simplified hashing for demo
    return btoa(password + 'salt123');
}
EOF

git add src/utils/security.js
git commit -m "HOTFIX: Add input sanitization and password hashing"

# Update del config per sicurezza
sed -i 's/debug: false/debug: false, enableSecurity: true/' src/config.js
git add src/config.js
git commit -m "HOTFIX: Enable security features in config"
```

## Parte 2: Compiti di Riorganizzazione

### Compito 1: Cleanup della Feature Branch User Management
**Obiettivo**: Riorganizzare i commit della branch `feature/user-management` usando interactive rebase.

**Passi richiesti**:
1. Checkout della branch `feature/user-management`
2. Eseguire interactive rebase per:
   - Squash dei commit "WIP", "fix typo" nel commit di sviluppo principale
   - Migliorare i messaggi di commit
   - Riordinare logicamente i commit

**Comando base**:
```bash
git checkout feature/user-management
git rebase -i main
```

**Risultato atteso**: Massimo 3 commit puliti e ben organizzati.

### Compito 2: Risoluzione Conflitti e Merge Strategy
**Obiettivo**: Gestire i conflitti tra le diverse branch e integrare le modifiche.

**Passi richiesti**:
1. Merge del hotfix in main
2. Tentativo di merge della feature/api-client (ci saranno conflitti su config.js)
3. Risoluzione manuale dei conflitti mantenendo:
   - L'URL dalla branch API
   - Le impostazioni di sicurezza dal hotfix
   - Timeout aumentato
4. Verifica che tutto funzioni correttamente

### Compito 3: Cherry-picking Selettivo
**Obiettivo**: Estrarre commit specifici dalla branch user-management senza fare merge completo.

**Scenario**: Il team decide di integrare solo la validazione utente in main, senza il resto della feature.

**Passi richiesti**:
1. Identificare il commit che aggiunge `validation.js`
2. Cherry-pick solo questo commit in main
3. Creare un commit che rimuove riferimenti alla validazione da altri file se necessario

### Compito 4: Rebase Complesso e History Rewriting
**Obiettivo**: Pulire completamente la storia prima del merge finale.

**Passi richiesti**:
1. Creare un nuovo branch `feature/user-management-clean`
2. Usare `git rebase -i` per creare una storia lineare perfetta
3. Combinare commit correlati
4. Riscrivere messaggi di commit seguendo convention (feat:, fix:, docs:)
5. Rimuovere commit non necessari

## Parte 3: Scenario Avanzato di Recovery

### Compito 5: Disaster Recovery
**Scenario**: Durante il rebase, hai fatto un errore e perso commit importanti.

**Simulazione del problema**:
```bash
# Simula perdita di commit
git checkout feature/user-management
git reset --hard HEAD~3
```

**Compiti di recovery**:
1. Usare `git reflog` per trovare i commit persi
2. Recuperare i commit usando `git cherry-pick` o `git reset`
3. Ricostruire la branch correttamente

### Compito 6: Merge Conflict Hell
**Scenario**: Merger multipli con conflitti complessi.

**Setup del problema**:
```bash
# Crea conflitti intenzionali modificando lo stesso file in branch diverse
git checkout main
echo "// Main version" >> src/app.js
git add src/app.js
git commit -m "Update main app"

git checkout feature/user-management
echo "// User feature version" >> src/app.js
git add src/app.js
git commit -m "Update app for users"

git checkout feature/api-client
echo "// API feature version" >> src/app.js
git add src/app.js
git commit -m "Update app for API"
```

**Compiti di risoluzione**:
1. Risolvere tutti i conflitti mantenendo funzionalità di entrambe le branch
2. Creare un merge commit che documenti la risoluzione
3. Testare che tutto funzioni dopo il merge

## Parte 4: Automazione e Best Practices

### Compito 7: Git Hooks e Automation
**Obiettivo**: Implementare git hooks per automazione.

**Creare pre-commit hook**:
```bash
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Pre-commit hook per validazione

echo "Running pre-commit checks..."

# Check per commit message format
if ! head -1 "$1" | grep -qE "^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}"; then
    echo "Invalid commit message format!"
    echo "Use: type(scope): description"
    echo "Types: feat, fix, docs, style, refactor, test, chore"
    exit 1
fi

# Check per file grandi
find . -name "*.js" -size +100k -not -path "./.git/*" | head -1 | grep -q . && {
    echo "Warning: Large JavaScript files detected"
    exit 1
}

echo "Pre-commit checks passed!"
EOF

chmod +x .git/hooks/pre-commit
```

### Compito 8: Creazione Release Branch
**Obiettivo**: Preparare una release seguendo Git Flow.

**Passi richiesti**:
1. Creare branch `release/v1.1.0`
2. Aggiornare version numbers
3. Creare changelog
4. Tag della release
5. Merge in main e develop

```bash
git checkout -b release/v1.1.0

# Update version
sed -i 's/1.0.0/1.1.0/' src/app.js

# Create changelog
cat > CHANGELOG.md << 'EOF'
# Changelog

## [1.1.0] - 2024-01-15

### Added
- User management system
- API client utilities
- Input validation
- Security enhancements

### Fixed
- Configuration conflicts
- Input sanitization issues

### Changed
- Updated API endpoints
- Enhanced security settings
EOF

git add .
git commit -m "chore(release): prepare v1.1.0 release"

git tag -a v1.1.0 -m "Release version 1.1.0"
```

## Valutazione e Criteri di Successo

### Criteri di Valutazione

1. **Organizzazione della Storia (25 punti)**
   - Commit logicamente organizzati
   - Messaggi di commit chiari e significativi
   - Storia lineare e comprensibile

2. **Gestione Conflitti (25 punti)**
   - Risoluzione corretta di tutti i conflitti
   - Mantenimento di tutte le funzionalità necessarie
   - Test post-merge

3. **Tecniche Avanzate (25 punti)**
   - Uso corretto di interactive rebase
   - Cherry-picking appropriato
   - Recovery da errori

4. **Best Practices (25 punti)**
   - Implementazione di hooks
   - Seguire convenzioni di naming
   - Documentazione adeguata

### Deliverable Finali

1. **Repository pulito** con storia lineare
2. **Documentazione** delle operazioni eseguite
3. **Script di automazione** funzionanti
4. **Report** delle problematiche incontrate e risolte

### Bonus Challenge (Punti Extra)

1. **Implementare git bisect** per trovare un bug simulato
2. **Creare script di backup** automatico
3. **Implementare workflow CI/CD** base con git hooks
4. **Analisi della storia** con strumenti come `git log --graph --oneline --all`

## Note per l'Istruttore

### Punti di Attenzione
- Verificare che gli studenti comprendano le implicazioni di rewrite della storia
- Enfatizzare l'importanza del backup prima di operazioni distruttive
- Monitorare l'uso di `git reflog` per recovery

### Estensioni Possibili
- Integrazione con sistemi di CI/CD
- Workflow con multiple repository remote
- Gestione di subtree e submodules

### Tempo Stimato
- Setup: 30 minuti
- Esercizi principali: 2-3 ore
- Bonus challenges: 1-2 ore aggiuntive

Questo esercizio avanzato copre scenari realistici che gli sviluppatori incontrano quotidianamente, fornendo esperienza pratica con le tecniche più sofisticate di Git.
