# Esercizio 2: Refactoring Struttura

## 🎯 Obiettivo
Praticare il refactoring di una struttura esistente utilizzando Git per rinominare, spostare e riorganizzare file mantenendo la tracciabilità completa.

## 📋 Scenario
Hai un progetto legacy con naming inconsistente e struttura confusa. Devi applicare moderne convenzioni di naming e riorganizzare la struttura per renderla più maintainable.

## 🚀 Setup Iniziale

```bash
# Creare directory di lavoro
mkdir refactoring-struttura
cd refactoring-struttura
git init

# Simulare progetto legacy con naming inconsistente
touch {
  HomePage.jsx,
  user_Profile.js,
  API-helpers.JS,
  CONSTANTS.json,
  loginPage.html,
  UserDashboard.CSS,
  utils.js,
  app_CONFIG.js,
  MainLayout.jsx,
  sidebar-component.js
}

# Creare directory legacy disorganizzate
mkdir -p {OldComponents,legacy-styles,JS-Utils,api_helpers}

# Aggiungere contenuto ai file per rendere realistico il refactoring
cat > HomePage.jsx << 'EOL'
import React from 'react';
import UserDashboard from './UserDashboard';
import { API_ENDPOINTS } from './CONSTANTS.json';

const HomePage = () => {
  return (
    <div className="home-page">
      <h1>Welcome to Our Application</h1>
      <UserDashboard />
    </div>
  );
};

export default HomePage;
EOL

cat > user_Profile.js << 'EOL'
// User Profile Component (Legacy naming)
const userProfile = {
  name: '',
  email: '',
  avatar: '',
  
  loadProfile: function(userId) {
    // Load user profile from API
    fetch(`/api/users/${userId}`)
      .then(response => response.json())
      .then(data => {
        this.name = data.name;
        this.email = data.email;
        this.avatar = data.avatar;
      });
  },
  
  updateProfile: function(data) {
    // Update user profile
    return fetch('/api/profile', {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(data)
    });
  }
};

module.exports = userProfile;
EOL

cat > CONSTANTS.json << 'EOL'
{
  "API_ENDPOINTS": {
    "users": "/api/users",
    "profile": "/api/profile",
    "auth": "/api/auth"
  },
  "UI_CONSTANTS": {
    "DEFAULT_AVATAR": "/images/default-avatar.png",
    "THEME_COLORS": {
      "primary": "#007bff",
      "secondary": "#6c757d",
      "success": "#28a745"
    }
  },
  "APP_CONFIG": {
    "VERSION": "1.0.0",
    "DEBUG": false,
    "MAX_FILE_SIZE": 5242880
  }
}
EOL

# Committare stato legacy iniziale
git add .
git commit -m "Initial legacy codebase

- Inconsistent naming conventions
- Mixed case styles (camelCase, snake_case, PascalCase)
- Disorganized file structure
- Legacy directory structure"

echo "✓ Progetto legacy creato con naming inconsistente"
```

## ✅ Task 1: Analisi del Codice Legacy

### Obiettivo:
Analizzare il codice esistente per identificare problemi di naming e struttura.

### Istruzioni:
```bash
# Analizzare naming patterns attuale
echo "=== Analisi Naming Patterns ==="
git ls-files | grep -v '\.git' | while read file; do
  case "$file" in
    *[A-Z]*) echo "PascalCase/Mixed: $file" ;;
    *_*) echo "snake_case: $file" ;;
    *-*) echo "kebab-case: $file" ;;
    *) echo "lowercase: $file" ;;
  esac
done

# Contare tipi di file
echo -e "\n=== Tipi di File ==="
git ls-files | grep -E '\.(js|jsx|css|html|json)$' | \
  awk -F. '{print $NF}' | sort | uniq -c

# Verificare dipendenze tra file
echo -e "\n=== Analisi Dipendenze ==="
grep -r "import\|require\|from" . --include="*.js" --include="*.jsx" | \
  head -10 || echo "Nessuna dipendenza evidente trovata"
```

### Domande di riflessione:
- Quali convenzioni di naming sono utilizzate?
- Ci sono inconsistenze evidenti?
- Come dovrebbe essere organizzata la struttura?

### Verifica:
- [ ] Identificati almeno 3 stili di naming diversi
- [ ] Analizzati i tipi di file presenti
- [ ] Comprese le dipendenze tra componenti

## ✅ Task 2: Piano di Refactoring

### Obiettivo:
Definire un piano sistematico per il refactoring.

### Strategia di naming:
- **JavaScript/JSX**: kebab-case per file, camelCase per variabili
- **CSS**: kebab-case
- **JSON/Config**: kebab-case
- **HTML**: kebab-case

### Struttura target:
```
src/
├── components/
│   ├── layout/
│   │   ├── main-layout.jsx
│   │   └── sidebar-component.js
│   ├── pages/
│   │   ├── home-page.jsx
│   │   └── login-page.html
│   └── user/
│       ├── user-profile.js
│       └── user-dashboard.css
├── utils/
│   ├── api-helpers.js
│   └── utils.js
├── config/
│   ├── constants.json
│   └── app-config.js
└── legacy/
    └── migration-notes.md
```

### Creare piano di migrazione:
```bash
cat > REFACTORING_PLAN.md << 'EOL'
# Piano di Refactoring

## Fase 1: Standardizzazione Naming
- [ ] PascalCase → kebab-case per file
- [ ] snake_case → kebab-case per file
- [ ] Correzione estensioni case-sensitive

## Fase 2: Organizzazione Struttura
- [ ] Creare directory src/
- [ ] Organizzare per funzionalità (components, utils, config)
- [ ] Separare layout, pages, e componenti user

## Fase 3: Aggiornamento Riferimenti
- [ ] Aggiornare import/require statements
- [ ] Verificare funzionalità dopo ogni spostamento
- [ ] Aggiornare documentazione

## Fase 4: Cleanup
- [ ] Rimuovere directory legacy vuote
- [ ] Aggiornare build scripts
- [ ] Documentare nuove convenzioni
EOL

git add REFACTORING_PLAN.md
git commit -m "Add systematic refactoring plan

- Define naming conventions (kebab-case)
- Plan directory structure reorganization
- Create migration checklist"
```

## ✅ Task 3: Fase 1 - Standardizzazione Naming

### Obiettivo:
Applicare convenzioni di naming consistenti usando `git mv`.

### 3.1 Correggere Case-Sensitivity:
```bash
echo "=== Correzione Case-Sensitivity ==="

# JavaScript file con case problems
git mv API-helpers.JS temp-api-helpers.js
git mv temp-api-helpers.js api-helpers.js

git mv UserDashboard.CSS temp-user-dashboard.css  
git mv temp-user-dashboard.css user-dashboard.css

echo "✓ Corrette estensioni case-sensitive"
```

### 3.2 Conversione PascalCase → kebab-case:
```bash
echo "=== Conversione PascalCase → kebab-case ==="

# Componenti React
git mv HomePage.jsx home-page.jsx
git mv MainLayout.jsx main-layout.jsx

# File HTML
git mv loginPage.html login-page.html

echo "✓ PascalCase convertito in kebab-case"
```

### 3.3 Conversione snake_case → kebab-case:
```bash
echo "=== Conversione snake_case → kebab-case ==="

git mv user_Profile.js user-profile.js
git mv app_CONFIG.js app-config.js

echo "✓ snake_case convertito in kebab-case"
```

### 3.4 Standardizzazione file speciali:
```bash
echo "=== Standardizzazione File Speciali ==="

git mv CONSTANTS.json constants.json

echo "✓ File speciali standardizzati"

# Committare standardizzazione naming
git commit -m "Standardize file naming conventions

- Convert PascalCase to kebab-case
- Convert snake_case to kebab-case  
- Fix case-sensitive extensions
- Apply consistent naming throughout project"
```

### Verifica Fase 1:
```bash
# Verificare che tutti i file seguano kebab-case
echo "=== Verifica Naming Standards ==="
git ls-files | grep -v '\.git\|REFACTORING_PLAN.md' | while read file; do
  if [[ "$file" =~ [A-Z_] ]]; then
    echo "❌ Non conforme: $file"
  else
    echo "✅ Conforme: $file"
  fi
done
```

## ✅ Task 4: Fase 2 - Riorganizzazione Struttura

### Obiettivo:
Creare struttura logica organizzata per funzionalità.

### 4.1 Creare struttura directory:
```bash
echo "=== Creazione Struttura Directory ==="

# Creare struttura src/
mkdir -p src/{components/{layout,pages,user},utils,config}

# Aggiungere .gitkeep per preservare directory vuote
find src -type d -empty -exec touch {}/.gitkeep \;

git add src/
echo "✓ Struttura directory creata"
```

### 4.2 Spostare componenti per categoria:
```bash
echo "=== Spostamento Componenti ==="

# Layout components
git mv main-layout.jsx src/components/layout/
git mv sidebar-component.js src/components/layout/

# Page components  
git mv home-page.jsx src/components/pages/
git mv login-page.html src/components/pages/

# User-related components
git mv user-profile.js src/components/user/
git mv user-dashboard.css src/components/user/

echo "✓ Componenti organizzati per categoria"
```

### 4.3 Spostare utilities e configurazioni:
```bash
echo "=== Spostamento Utils e Config ==="

# Utilities
git mv utils.js src/utils/
git mv api-helpers.js src/utils/

# Configuration files
git mv constants.json src/config/
git mv app-config.js src/config/

echo "✓ Utils e config organizzati"

# Committare riorganizzazione
git commit -m "Reorganize project structure by functionality

- Move layout components to src/components/layout/
- Move page components to src/components/pages/
- Move user components to src/components/user/
- Move utilities to src/utils/
- Move configuration to src/config/
- Create scalable directory structure"
```

## ✅ Task 5: Fase 3 - Aggiornamento Riferimenti

### Obiettivo:
Aggiornare tutti i riferimenti nei file per riflettere la nuova struttura.

### 5.1 Aggiornare import in home-page.jsx:
```bash
# Leggere contenuto attuale
cat src/components/pages/home-page.jsx

# Aggiornare import paths
cat > src/components/pages/home-page.jsx << 'EOL'
import React from 'react';
import UserDashboard from '../user/user-profile';
import { API_ENDPOINTS } from '../../config/constants.json';

const HomePage = () => {
  return (
    <div className="home-page">
      <h1>Welcome to Our Application</h1>
      <UserDashboard />
    </div>
  );
};

export default HomePage;
EOL

echo "✓ Import aggiornati in home-page.jsx"
```

### 5.2 Aggiornare configurazione entry points:
```bash
# Creare file di configurazione aggiornato
cat > src/index.js << 'EOL'
// Main application entry point
import HomePage from './components/pages/home-page.jsx';
import MainLayout from './components/layout/main-layout.jsx';
import userProfile from './components/user/user-profile.js';
import apiHelpers from './utils/api-helpers.js';
import utils from './utils/utils.js';
import constants from './config/constants.json';
import appConfig from './config/app-config.js';

// Export main components for application
export {
  HomePage,
  MainLayout,
  userProfile,
  apiHelpers,
  utils,
  constants,
  appConfig
};

console.log('Application modules loaded successfully');
EOL

git add src/index.js
echo "✓ Entry point aggiornato"
```

### 5.3 Creare file di mapping per backward compatibility:
```bash
# Creare file che mappa vecchi percorsi a nuovi
cat > legacy-path-mapping.js << 'EOL'
// Legacy path mapping for backward compatibility
// Use this file to gradually migrate existing code

const pathMapping = {
  // Old path → New path
  'HomePage.jsx': 'src/components/pages/home-page.jsx',
  'user_Profile.js': 'src/components/user/user-profile.js',
  'API-helpers.JS': 'src/utils/api-helpers.js',
  'CONSTANTS.json': 'src/config/constants.json',
  'loginPage.html': 'src/components/pages/login-page.html',
  'UserDashboard.CSS': 'src/components/user/user-dashboard.css',
  'utils.js': 'src/utils/utils.js',
  'app_CONFIG.js': 'src/config/app-config.js',
  'MainLayout.jsx': 'src/components/layout/main-layout.jsx',
  'sidebar-component.js': 'src/components/layout/sidebar-component.js'
};

module.exports = pathMapping;
EOL

git add legacy-path-mapping.js
echo "✓ Mapping legacy paths creato"
```

### 5.4 Aggiornare package.json:
```bash
cat > package.json << 'EOL'
{
  "name": "refactored-project",
  "version": "2.0.0",
  "description": "Refactored project with clean structure and naming",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js",
    "dev": "webpack serve --mode=development",
    "build": "webpack --mode=production",
    "test": "jest",
    "lint": "eslint src/"
  },
  "directories": {
    "src": "src/",
    "components": "src/components/",
    "utils": "src/utils/",
    "config": "src/config/"
  },
  "keywords": ["refactored", "clean-architecture", "maintainable"],
  "devDependencies": {
    "webpack": "^5.70.0",
    "eslint": "^8.0.0",
    "jest": "^27.0.0"
  }
}
EOL

git add package.json

# Committare aggiornamenti riferimenti
git commit -m "Update references and configuration

- Update import paths in React components
- Create main entry point with correct imports
- Add legacy path mapping for backward compatibility
- Update package.json with new structure
- Ensure all references point to new locations"
```

## ✅ Task 6: Fase 4 - Cleanup e Documentazione

### Obiettivo:
Completare il refactoring con cleanup finale e documentazione.

### 6.1 Rimuovere directory legacy vuote:
```bash
echo "=== Cleanup Directory Legacy ==="

# Rimuovere directory legacy vuote se presenti
rmdir OldComponents legacy-styles JS-Utils api_helpers 2>/dev/null || true

# Verificare che tutte le directory legacy siano state rimosse
echo "Directory rimanenti:"
find . -type d -empty | grep -v '\.git' || echo "Nessuna directory vuota"

echo "✓ Directory legacy rimosse"
```

### 6.2 Creare documentazione completa:
```bash
# Aggiornare piano di refactoring con risultati
cat >> REFACTORING_PLAN.md << 'EOL'

## ✅ Risultati Refactoring

### Completato:
- ✅ Standardizzazione naming (kebab-case)
- ✅ Riorganizzazione struttura src/
- ✅ Aggiornamento riferimenti
- ✅ Cleanup directory legacy

### Struttura Finale:
```
src/
├── components/
│   ├── layout/
│   │   ├── main-layout.jsx
│   │   └── sidebar-component.js
│   ├── pages/
│   │   ├── home-page.jsx
│   │   └── login-page.html
│   └── user/
│       ├── user-profile.js
│       └── user-dashboard.css
├── utils/
│   ├── api-helpers.js
│   └── utils.js
├── config/
│   ├── constants.json
│   └── app-config.js
└── index.js
```

### Benefici Ottenuti:
- Naming consistente e prevedibile
- Struttura scalabile e maintainable
- Separazione logica delle funzionalità
- Facilità di navigazione del codice
- Riferimenti aggiornati e funzionanti
EOL

# Creare guida per sviluppatori
cat > src/DEVELOPMENT_GUIDE.md << 'EOL'
# Guida allo Sviluppo

## Convenzioni di Naming

### File e Directory
- **Formato**: kebab-case per tutti i file
- **Esempi**: `user-profile.js`, `main-layout.jsx`, `api-helpers.js`

### Componenti JavaScript/React
- **File**: kebab-case (`home-page.jsx`)
- **Variabili**: camelCase (`userName`, `apiEndpoint`)
- **Costanti**: UPPER_SNAKE_CASE (`API_BASE_URL`)

## Struttura Directory

### `src/components/`
Tutti i componenti React e UI

- **`layout/`**: Componenti di layout (header, sidebar, footer)
- **`pages/`**: Componenti pagina principale
- **`user/`**: Componenti specifici per gestione utenti
- **`common/`**: Componenti riutilizzabili

### `src/utils/`
Funzioni di utilità e helpers

- **`api-helpers.js`**: Funzioni per chiamate API
- **`utils.js`**: Utilità generiche
- **`validators.js`**: Funzioni di validazione

### `src/config/`
File di configurazione

- **`constants.json`**: Costanti applicazione
- **`app-config.js`**: Configurazione runtime
- **`environment.js`**: Variabili ambiente

## Best Practices

1. **Organizzazione**: Raggruppa file per funzionalità
2. **Naming**: Usa convenzioni consistenti
3. **Import**: Usa percorsi relativi consistenti
4. **Documentazione**: Mantieni README aggiornati
5. **Testing**: Organizza test paralleli alla struttura src/

## Migration da Legacy

Usa `legacy-path-mapping.js` per mappare vecchi percorsi:

```javascript
const mapping = require('./legacy-path-mapping.js');
const newPath = mapping['HomePage.jsx']; // src/components/pages/home-page.jsx
```
EOL

git add .
git commit -m "Complete refactoring with cleanup and documentation

- Remove empty legacy directories
- Update refactoring plan with results
- Add comprehensive development guide
- Document naming conventions and structure
- Provide migration guidance for legacy code"
```

## ✅ Task 7: Verifica e Testing

### Obiettivo:
Verificare che il refactoring sia stato completato correttamente.

### 7.1 Verifica struttura finale:
```bash
echo "=== Verifica Struttura Finale ==="

# Mostrare struttura completa
echo "Struttura directory:"
tree src/ 2>/dev/null || find src/ -type f | sort

echo -e "\nFile nella root:"
ls -la | grep -v '^d' | awk '{print $9}' | grep -v '^$'

echo -e "\nTotale file tracciati:"
git ls-files | wc -l
```

### 7.2 Verifica naming conventions:
```bash
echo "=== Verifica Naming Conventions ==="

# Controllare che tutti i file seguano kebab-case
non_compliant=0
git ls-files | grep -E '\.(js|jsx|css|html|json)$' | while read file; do
  basename=$(basename "$file")
  if [[ "$basename" =~ [A-Z_] && "$basename" != "REFACTORING_PLAN.md" ]]; then
    echo "❌ Non conforme: $file"
    non_compliant=$((non_compliant + 1))
  fi
done

if [[ $non_compliant -eq 0 ]]; then
  echo "✅ Tutte le naming conventions rispettate"
fi
```

### 7.3 Verifica funzionalità:
```bash
echo "=== Test Funzionalità ==="

# Verificare che i percorsi di import siano validi
echo "Verificando import in home-page.jsx:"
grep -n "import\|require" src/components/pages/home-page.jsx

echo -e "\nVerificando entry point:"
node -c src/index.js && echo "✅ index.js sintatticamente corretto" || echo "❌ Errori in index.js"

echo -e "\nVerificando JSON config:"
python3 -m json.tool src/config/constants.json > /dev/null && \
  echo "✅ constants.json valido" || echo "❌ JSON non valido"
```

### 7.4 Verifica storia Git:
```bash
echo "=== Verifica Storia Git ==="

# Mostrare storia delle rinominazioni
echo "Storia delle rinominazioni principali:"
git log --follow --oneline src/components/pages/home-page.jsx | head -3
git log --follow --oneline src/components/user/user-profile.js | head -3

echo -e "\nCommit del refactoring:"
git log --oneline --grep="refactor\|rename\|organize" | head -5

# Creare tag per milestone
git tag v2.0-refactored
echo -e "\n✅ Tag v2.0-refactored creato"
```

## ✅ Task 8: Creazione Script di Automazione

### Obiettivo:
Creare script per automatizzare futuri refactoring.

```bash
# Creare script di refactoring automatico
cat > scripts/auto-refactor.sh << 'EOL'
#!/bin/bash
# Automated refactoring script

set -e

echo "🚀 Starting automated refactoring..."

# Function to convert to kebab-case
to_kebab_case() {
  echo "$1" | sed 's/\([A-Z]\)/-\L\1/g' | sed 's/^-//' | sed 's/_/-/g'
}

# Create src structure
mkdir -p src/{components/{layout,pages,user,common},utils,config}

# Backup current state
git tag "backup-before-auto-refactor-$(date +%Y%m%d-%H%M%S)"

# Rename files to kebab-case
for file in *.{js,jsx,css,html,json}; do
  [[ -f "$file" ]] || continue
  
  new_name=$(to_kebab_case "${file}")
  if [[ "$file" != "$new_name" ]]; then
    git mv "$file" "$new_name"
    echo "✓ Renamed: $file → $new_name"
  fi
done

# Organize by file type and content
for file in *.jsx; do
  [[ -f "$file" ]] || continue
  
  # Analyze content to determine category
  if grep -q "Layout\|Sidebar\|Header\|Footer" "$file"; then
    git mv "$file" "src/components/layout/"
  elif grep -q "Page\|Route" "$file"; then
    git mv "$file" "src/components/pages/"
  elif grep -q "User\|Profile\|Auth" "$file"; then
    git mv "$file" "src/components/user/"
  else
    git mv "$file" "src/components/common/"
  fi
done

# Move other file types
git mv *.js src/utils/ 2>/dev/null || true
git mv *.{json,config} src/config/ 2>/dev/null || true
git mv *.css src/components/user/ 2>/dev/null || true
git mv *.html src/components/pages/ 2>/dev/null || true

echo "✅ Automated refactoring completed!"
EOL

mkdir -p scripts
chmod +x scripts/auto-refactor.sh

# Creare script di verifica
cat > scripts/verify-refactor.sh << 'EOL'
#!/bin/bash
# Verification script for refactoring

echo "🔍 Verifying refactoring results..."

# Check naming conventions
echo "=== Naming Convention Check ==="
violations=0
for file in $(git ls-files | grep -E '\.(js|jsx|css|html|json)$'); do
  basename=$(basename "$file")
  if [[ "$basename" =~ [A-Z_] && "$basename" != *".md" ]]; then
    echo "❌ Naming violation: $file"
    violations=$((violations + 1))
  fi
done

if [[ $violations -eq 0 ]]; then
  echo "✅ All naming conventions compliant"
else
  echo "❌ Found $violations naming violations"
fi

# Check directory structure
echo -e "\n=== Directory Structure Check ==="
required_dirs=("src/components" "src/utils" "src/config")
for dir in "${required_dirs[@]}"; do
  if [[ -d "$dir" ]]; then
    echo "✅ $dir exists"
  else
    echo "❌ $dir missing"
  fi
done

# Check file organization
echo -e "\n=== File Organization Check ==="
echo "Components: $(find src/components -name '*.jsx' 2>/dev/null | wc -l)"
echo "Utils: $(find src/utils -name '*.js' 2>/dev/null | wc -l)"
echo "Config: $(find src/config -name '*.json' -o -name '*.js' 2>/dev/null | wc -l)"

echo -e "\n✅ Verification completed!"
EOL

chmod +x scripts/verify-refactor.sh

git add scripts/
git commit -m "Add automation scripts for future refactoring

- Add auto-refactor.sh for automated file organization
- Add verify-refactor.sh for checking refactoring results
- Include backup mechanism and error handling
- Enable consistent refactoring across projects"
```

## 🎯 Risultato Finale

Al termine dell'esercizio avrai:

### ✅ Risultati Ottenuti:

1. **Naming Standardizzato**: Tutti i file seguono kebab-case
2. **Struttura Organizzata**: File organizzati per funzionalità in src/
3. **Riferimenti Aggiornati**: Import e require aggiornati ai nuovi percorsi
4. **Documentazione**: Guide complete per sviluppatori
5. **Automazione**: Script per futuri refactoring
6. **Storia Preservata**: Tutte le modifiche tracciate con git mv

### 📊 Statistiche:

#### Prima del refactoring:
```
- 10 file con naming inconsistente
- 0 directory organizzate
- Riferimenti sparsi
- Nessuna convenzione
```

#### Dopo il refactoring:
```
src/
├── components/     (4 file organizzati)
├── utils/          (2 file)
├── config/         (2 file)
└── index.js        (entry point)

+ Documentazione completa
+ Script di automazione
+ Convenzioni chiare
```

## 💡 Bonus Challenges

### Challenge 1: Linting Rules
Configura ESLint per enforcing naming conventions:
```json
{
  "rules": {
    "camelcase": ["error", { "properties": "never" }],
    "no-underscore-dangle": "error"
  }
}
```

### Challenge 2: Pre-commit Hooks
Crea hook Git per verificare naming prima del commit.

### Challenge 3: Migration Script
Crea script per migrare progetti esistenti automaticamente.

## 📚 Cosa Hai Imparato

1. **Refactoring Sistematico**: Approccio metodico al refactoring
2. **Git per Ristrutturazione**: Uso di git mv per preservare storia
3. **Naming Conventions**: Importanza di convenzioni consistenti
4. **Organizzazione Codice**: Strutture scalabili e maintainable
5. **Automazione**: Script per ripetere processi
6. **Documentazione**: Guide per team development

Eccellente! Hai completato un refactoring completo mantenendo la tracciabilità Git e creando una base solida per lo sviluppo futuro.
