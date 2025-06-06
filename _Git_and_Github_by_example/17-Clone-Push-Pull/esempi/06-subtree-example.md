# Esempio Pratico: Git Subtree

## Scenario
Integriamo una libreria di utilità in un progetto esistente usando git subtree, mantenendo la possibilità di contribuire upstream.

## Struttura dell'Esempio
```
main-project/
├── src/
├── docs/
├── utils/              # Subtree da libreria esterna
│   ├── string-helpers/
│   ├── date-helpers/
│   └── validation/
└── tests/
```

## Setup Iniziale

### 1. Creare la Libreria Utilities (Repository Esterno)
```bash
# Creare la libreria di utilità
mkdir js-utilities
cd js-utilities
git init

# Struttura della libreria
mkdir -p string-helpers date-helpers validation

# String helpers
cat > string-helpers/index.js << 'EOF'
export function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
}

export function slugify(str) {
    return str
        .toLowerCase()
        .trim()
        .replace(/[^\w\s-]/g, '')
        .replace(/[\s_-]+/g, '-')
        .replace(/^-+|-+$/g, '');
}

export function truncate(str, length = 100) {
    return str.length <= length ? str : str.slice(0, length) + '...';
}
EOF

# Date helpers
cat > date-helpers/index.js << 'EOF'
export function formatDate(date, format = 'YYYY-MM-DD') {
    const d = new Date(date);
    const year = d.getFullYear();
    const month = String(d.getMonth() + 1).padStart(2, '0');
    const day = String(d.getDate()).padStart(2, '0');
    
    return format
        .replace('YYYY', year)
        .replace('MM', month)
        .replace('DD', day);
}

export function isToday(date) {
    const today = new Date();
    const checkDate = new Date(date);
    return today.toDateString() === checkDate.toDateString();
}

export function daysBetween(date1, date2) {
    const oneDay = 24 * 60 * 60 * 1000;
    return Math.round(Math.abs((new Date(date1) - new Date(date2)) / oneDay));
}
EOF

# Validation helpers
cat > validation/index.js << 'EOF'
export function isEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

export function isPhoneNumber(phone) {
    const phoneRegex = /^[\+]?[1-9][\d]{0,15}$/;
    return phoneRegex.test(phone.replace(/[\s\-\(\)]/g, ''));
}

export function isStrongPassword(password) {
    return password.length >= 8 &&
           /[a-z]/.test(password) &&
           /[A-Z]/.test(password) &&
           /\d/.test(password) &&
           /[!@#$%^&*]/.test(password);
}
EOF

# File principale della libreria
cat > index.js << 'EOF'
export * from './string-helpers/index.js';
export * from './date-helpers/index.js';
export * from './validation/index.js';
EOF

cat > package.json << 'EOF'
{
  "name": "js-utilities",
  "version": "1.0.0",
  "description": "Libreria di utilità JavaScript",
  "main": "index.js",
  "type": "module",
  "author": "Utils Team"
}
EOF

cat > README.md << 'EOF'
# JS Utilities

Libreria di funzioni di utilità per JavaScript.

## Moduli
- **string-helpers**: Manipolazione stringhe
- **date-helpers**: Gestione date
- **validation**: Validazione input
EOF

# Commit iniziale
git add .
git commit -m "Initial utilities library"
git tag v1.0.0

cd ..
```

### 2. Creare il Progetto Principale
```bash
# Creare il progetto principale
mkdir main-project
cd main-project
git init

# Struttura del progetto
mkdir -p src docs tests

cat > src/app.js << 'EOF'
// Questo file userà le utilities dopo l'integrazione
class UserManager {
    constructor() {
        this.users = [];
    }
    
    addUser(userData) {
        // Validation sarà implementata dopo l'integrazione subtree
        this.users.push(userData);
    }
    
    formatUserData(user) {
        // String e date helpers saranno usati qui
        return user;
    }
}

export default UserManager;
EOF

cat > src/config.js << 'EOF'
export const CONFIG = {
    appName: 'Main Project',
    version: '1.0.0',
    apiUrl: 'https://api.example.com'
};
EOF

cat > docs/README.md << 'EOF'
# Main Project

Progetto principale che integra utilities esterne via git subtree.

## Struttura
- `src/`: Codice sorgente principale
- `utils/`: Utilities integrate via subtree
- `tests/`: Test suite
- `docs/`: Documentazione
EOF

git add .
git commit -m "Initial main project structure"
```

## Integrare la Libreria con Subtree

### 1. Aggiungere il Subtree
```bash
# Aggiungere la libreria come subtree
git subtree add --prefix=utils ../js-utilities main --squash

# Verificare l'integrazione
ls utils/
cat utils/package.json

# Lo stato di git mostra i nuovi file
git log --oneline -5
```

### 2. Utilizzare le Utilities nel Progetto
```bash
# Aggiornare l'app per usare le utilities
cat > src/app.js << 'EOF'
import { capitalize, slugify, isEmail, isStrongPassword, formatDate } from '../utils/index.js';

class UserManager {
    constructor() {
        this.users = [];
    }
    
    addUser(userData) {
        // Validazione con le utilities
        if (!this.validateUser(userData)) {
            throw new Error('Dati utente non validi');
        }
        
        // Formattazione con le utilities
        const formattedUser = {
            name: capitalize(userData.name),
            slug: slugify(userData.name),
            email: userData.email.toLowerCase(),
            registrationDate: formatDate(new Date())
        };
        
        this.users.push(formattedUser);
        return formattedUser;
    }
    
    validateUser(userData) {
        return userData.name &&
               isEmail(userData.email) &&
               isStrongPassword(userData.password);
    }
    
    getUserBySlug(slug) {
        return this.users.find(user => user.slug === slug);
    }
}

export default UserManager;
EOF

# Creare un file di test
cat > tests/user-manager.test.js << 'EOF'
import UserManager from '../src/app.js';

const userManager = new UserManager();

// Test di base
try {
    const user = userManager.addUser({
        name: 'john doe',
        email: 'john@example.com',
        password: 'SecurePass123!'
    });
    
    console.log('✅ User created:', user);
    console.log('✅ Slug generated:', user.slug);
    
    // Test ricerca per slug
    const foundUser = userManager.getUserBySlug('john-doe');
    console.log('✅ User found by slug:', foundUser ? 'Yes' : 'No');
    
} catch (error) {
    console.log('❌ Error:', error.message);
}

// Test validazione
try {
    userManager.addUser({
        name: 'Invalid User',
        email: 'not-an-email',
        password: '123'
    });
} catch (error) {
    console.log('✅ Validation working:', error.message);
}
EOF

# Commit delle modifiche
git add .
git commit -m "Integrate and use utilities from subtree"

# Test dell'integrazione
node tests/user-manager.test.js
```

## Workflow di Aggiornamento

### Scenario 1: Aggiornare dal Repository Upstream

```bash
# Simulare un aggiornamento nella libreria originale
cd ../js-utilities

# Aggiungere una nuova utility
cat > array-helpers/index.js << 'EOF'
export function unique(array) {
    return [...new Set(array)];
}

export function groupBy(array, key) {
    return array.reduce((groups, item) => {
        const group = item[key];
        groups[group] = groups[group] || [];
        groups[group].push(item);
        return groups;
    }, {});
}

export function chunk(array, size) {
    const chunks = [];
    for (let i = 0; i < array.length; i += size) {
        chunks.push(array.slice(i, i + size));
    }
    return chunks;
}
EOF

mkdir -p array-helpers

# Aggiornare l'indice principale
cat > index.js << 'EOF'
export * from './string-helpers/index.js';
export * from './date-helpers/index.js';
export * from './validation/index.js';
export * from './array-helpers/index.js';
EOF

# Aggiornare la versione
sed -i 's/"version": "1.0.0"/"version": "1.1.0"/' package.json

git add .
git commit -m "Add array helpers module"
git tag v1.1.0

# Tornare al progetto principale
cd ../main-project

# Aggiornare il subtree
git subtree pull --prefix=utils ../js-utilities main --squash

# Verificare l'aggiornamento
ls utils/
cat utils/package.json
```

### Scenario 2: Contribuire Upstream dal Subtree

```bash
# Aggiungere una nuova funzione nel subtree
cat >> utils/string-helpers/index.js << 'EOF'

export function camelCase(str) {
    return str
        .toLowerCase()
        .replace(/[^a-zA-Z0-9]+(.)/g, (m, chr) => chr.toUpperCase());
}
EOF

# Utilizzare la nuova funzione
cat >> src/app.js << 'EOF'

import { camelCase } from '../utils/index.js';

// Aggiungere metodo alla classe UserManager
UserManager.prototype.generateApiKey = function(userName) {
    return camelCase(`api_key_${userName}_${Date.now()}`);
};
EOF

git add .
git commit -m "Add camelCase function to string helpers"

# Pushare la modifica upstream
git subtree push --prefix=utils ../js-utilities feature/camel-case

# Verificare nel repository originale
cd ../js-utilities
git log --oneline -3
git show HEAD
```

## Gestione Avanzata con Script

Creare script per automatizzare le operazioni:

```bash
# Script per aggiornamenti
cat > scripts/update-utils.sh << 'EOF'
#!/bin/bash

echo "🔄 Updating utilities subtree..."

# Backup del branch corrente
current_branch=$(git branch --show-current)

# Pull dal subtree
if git subtree pull --prefix=utils origin main --squash; then
    echo "✅ Utilities updated successfully"
    
    # Eseguire i test
    echo "🧪 Running tests..."
    if node tests/user-manager.test.js; then
        echo "✅ All tests passed"
    else
        echo "❌ Tests failed - check integration"
    fi
else
    echo "❌ Failed to update utilities"
    exit 1
fi
EOF

# Script per contribuzioni upstream
cat > scripts/contribute-upstream.sh << 'EOF'
#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <branch-name>"
    exit 1
fi

branch_name=$1

echo "🚀 Contributing to upstream: $branch_name"

# Verificare che ci siano modifiche nel subtree
if git diff --quiet HEAD~1 utils/; then
    echo "❌ No changes in utils/ directory"
    exit 1
fi

# Push upstream
if git subtree push --prefix=utils origin "$branch_name"; then
    echo "✅ Changes pushed to upstream branch: $branch_name"
    echo "💡 Don't forget to create a pull request!"
else
    echo "❌ Failed to push upstream"
    exit 1
fi
EOF

mkdir -p scripts
chmod +x scripts/*.sh
```

## Workflow di Team

### Scenario: Sviluppo Coordinato

```bash
# Creare un branch per feature
git checkout -b feature/user-profiles

# Aggiungere funzionalità che usa le utilities
cat > src/profile-manager.js << 'EOF'
import { capitalize, formatDate, isEmail, unique, groupBy } from '../utils/index.js';

class ProfileManager {
    constructor() {
        this.profiles = [];
    }
    
    createProfile(userData) {
        const profile = {
            id: Date.now(),
            name: capitalize(userData.name),
            email: userData.email,
            skills: unique(userData.skills || []),
            createdAt: formatDate(new Date()),
            department: userData.department
        };
        
        this.profiles.push(profile);
        return profile;
    }
    
    getProfilesByDepartment() {
        return groupBy(this.profiles, 'department');
    }
    
    searchProfiles(query) {
        return this.profiles.filter(profile => 
            profile.name.toLowerCase().includes(query.toLowerCase()) ||
            profile.skills.some(skill => 
                skill.toLowerCase().includes(query.toLowerCase())
            )
        );
    }
}

export default ProfileManager;
EOF

# Test della nuova funzionalità
cat > tests/profile-manager.test.js << 'EOF'
import ProfileManager from '../src/profile-manager.js';

const profileManager = new ProfileManager();

// Creare alcuni profili di test
const profiles = [
    {
        name: 'alice johnson',
        email: 'alice@company.com',
        skills: ['JavaScript', 'React', 'Node.js', 'JavaScript'],
        department: 'Frontend'
    },
    {
        name: 'bob smith',
        email: 'bob@company.com',
        skills: ['Python', 'Django', 'PostgreSQL'],
        department: 'Backend'
    },
    {
        name: 'carol white',
        email: 'carol@company.com',
        skills: ['JavaScript', 'Vue', 'CSS'],
        department: 'Frontend'
    }
];

profiles.forEach(profile => {
    const created = profileManager.createProfile(profile);
    console.log('✅ Profile created:', created.name);
});

// Test raggruppamento per dipartimento
const byDepartment = profileManager.getProfilesByDepartment();
console.log('👥 Profiles by department:', Object.keys(byDepartment));

// Test ricerca
const jsProfiles = profileManager.searchProfiles('javascript');
console.log('🔍 JavaScript profiles:', jsProfiles.length);
EOF

git add .
git commit -m "Add ProfileManager with utilities integration"

# Merge nel main
git checkout main
git merge feature/user-profiles

# Test finale
node tests/profile-manager.test.js
```

## Manutenzione e Best Practices

### Monitoring delle Dipendenze
```bash
# Script per verificare lo stato del subtree
cat > scripts/check-subtree-status.sh << 'EOF'
#!/bin/bash

echo "📊 Subtree Status Report"
echo "======================="

# Informazioni sul subtree
echo "📁 Subtree directory: utils/"
echo "📦 Package info:"
cat utils/package.json | grep -E '"name"|"version"'

# Ultimo commit nel subtree
echo "🕒 Last subtree commit:"
git log --oneline -1 --grep="Squashed 'utils/'"

# Verificare se ci sono modifiche non sincronizzate
echo "🔄 Local modifications in utils/:"
if git diff --quiet utils/; then
    echo "   No local modifications"
else
    echo "   ⚠️  Local modifications detected"
    git diff --name-only utils/
fi

# Verificare commit recenti che toccano utils/
echo "📝 Recent commits affecting utils/:"
git log --oneline -5 --pretty=format:"%h %s" -- utils/
EOF

chmod +x scripts/check-subtree-status.sh
```

## Verifica Pratica

Comandi per verificare la comprensione:

1. **Stato del subtree:**
   ```bash
   ./scripts/check-subtree-status.sh
   ```

2. **Test di integrazione:**
   ```bash
   node tests/user-manager.test.js
   node tests/profile-manager.test.js
   ```

3. **Verifica delle utilities:**
   ```bash
   node -e "import('./utils/index.js').then(utils => console.log(Object.keys(utils)))"
   ```

## Risultato Atteso

Al termine dell'esempio dovreste avere:
- Un progetto che integra una libreria esterna via subtree
- Capacità di aggiornare e contribuire upstream
- Script di automazione per la gestione quotidiana
- Comprensione dei workflow di team con subtree
- Esperienza pratica con casi d'uso reali

## Note per l'Istruttore

- Mostrare la differenza con i submoduli durante l'esempio
- Enfatizzare quando usare subtree vs submoduli
- Dimostrare la risoluzione di conflitti durante i pull
- Spiegare l'importanza della flag --squash per la storia pulita
