# Rinominazione e Spostamento

Questo esempio dimostra come gestire rinominazioni e spostamenti di file mantenendo la storia in Git.

## Scenario: Refactoring di un Progetto Web

### Setup Iniziale

```bash
# Creare progetto disorganizzato
mkdir refactoring-esempio
cd refactoring-esempio
git init

# Struttura disorganizzata iniziale
mkdir old-structure
touch {
  HomePage.js,
  userProfile.css,
  API_helpers.js,
  login-page.html,
  CONSTANTS.js,
  utils.JS,
  styles.CSS
}

# Aggiungere contenuto ai file
cat > HomePage.js << 'EOL'
import React from 'react';

function HomePage() {
  return (
    <div className="home-page">
      <h1>Welcome to Our App</h1>
      <p>This is the home page component.</p>
    </div>
  );
}

export default HomePage;
EOL

cat > userProfile.css << 'EOL'
.user-profile {
  background: #f5f5f5;
  padding: 20px;
  border-radius: 8px;
}

.user-profile h2 {
  color: #333;
  margin-bottom: 16px;
}

.profile-avatar {
  width: 80px;
  height: 80px;
  border-radius: 50%;
}
EOL

cat > API_helpers.js << 'EOL'
const API_BASE_URL = 'https://api.example.com';

export const apiHelpers = {
  async fetchUser(id) {
    const response = await fetch(`${API_BASE_URL}/users/${id}`);
    return response.json();
  },
  
  async updateProfile(data) {
    const response = await fetch(`${API_BASE_URL}/profile`, {
      method: 'PUT',
      body: JSON.stringify(data)
    });
    return response.json();
  }
};
EOL

# Primo commit con struttura disorganizzata
git add .
git commit -m "Initial commit - unorganized structure"
```

### 1. Rinominazione per Convenzioni di Naming

```bash
echo "=== Applicazione Convenzioni di Naming ==="

# Da PascalCase a kebab-case per componenti
git mv HomePage.js home-page.js
echo "✓ HomePage.js → home-page.js"

# Correzione estensioni case-sensitive  
git mv utils.JS utils.js
git mv styles.CSS styles.css
echo "✓ Corrette estensioni maiuscole"

# API helpers: da snake_case a camelCase
git mv API_helpers.js api-helpers.js
echo "✓ API_helpers.js → api-helpers.js"

# Constants: da MAIUSCOLO a kebab-case
git mv CONSTANTS.js constants.js
echo "✓ CONSTANTS.js → constants.js"

# Verificare rinominazioni
git status

# Committare rinominazioni
git commit -m "Apply consistent naming conventions

- Use kebab-case for file names
- Fix case-sensitive extensions
- Standardize API helpers naming"
```

### 2. Organizzazione in Directory

```bash
echo "=== Organizzazione in Directory ==="

# Creare struttura organizzata
mkdir -p {
  src/{components,pages,styles,utils,services},
  assets/{images,fonts},
  docs
}

# Spostare file JavaScript/React
git mv home-page.js src/pages/
git mv utils.js src/utils/
git mv api-helpers.js src/services/
git mv constants.js src/utils/

echo "✓ File JavaScript organizzati in src/"

# Spostare file CSS
git mv userProfile.css src/styles/user-profile.css
git mv styles.css src/styles/main.css

echo "✓ File CSS organizzati in src/styles/"

# Spostare file HTML
git mv login-page.html src/pages/

echo "✓ File HTML spostati in src/pages/"

# Verificare struttura
echo "Nuova struttura:"
tree . 2>/dev/null || find . -type f -not -path './.*' | sort

git status
git commit -m "Organize files into logical directory structure

- Move React components to src/pages/
- Move utilities to src/utils/ 
- Move services to src/services/
- Move styles to src/styles/
- Create clean separation of concerns"
```

### 3. Rinominazione + Spostamento Simultaneo

```bash
echo "=== Rinominazione + Spostamento Simultaneo ==="

# Creare nuovo file per esempio
cat > temp-component.jsx << 'EOL'
import React from 'react';

export function TempComponent() {
  return <div>Temporary component</div>;
}
EOL

git add temp-component.jsx
git commit -m "Add temporary component for demo"

# Spostare E rinominare in un comando
git mv temp-component.jsx src/components/user-dashboard.jsx

echo "✓ temp-component.jsx → src/components/user-dashboard.jsx"

# Aggiungere contenuto appropriato
cat > src/components/user-dashboard.jsx << 'EOL'
import React from 'react';

export function UserDashboard({ user }) {
  return (
    <div className="user-dashboard">
      <h2>Dashboard di {user.name}</h2>
      <div className="dashboard-stats">
        <div className="stat">
          <span>Progetti: {user.projects}</span>
        </div>
        <div className="stat">
          <span>Tasks: {user.tasks}</span>
        </div>
      </div>
    </div>
  );
}
EOL

git add src/components/user-dashboard.jsx
git commit -m "Transform temp component into UserDashboard

- Move to components directory
- Rename with descriptive name  
- Add proper dashboard functionality"
```

### 4. Gestione Case-Sensitivity (macOS/Windows)

```bash
echo "=== Gestione Case-Sensitivity ==="

# Simulare problema case-sensitivity
touch readme.txt
echo "# Project README" > readme.txt
git add readme.txt
git commit -m "Add readme file"

# Rinominare con case diverso (problema su macOS/Windows)
echo "Rinominazione case-sensitive richiede due passi:"

# Passo 1: rinominare a nome temporaneo
git mv readme.txt temp-readme.txt
echo "✓ Passo 1: readme.txt → temp-readme.txt"

# Passo 2: rinominare al nome finale
git mv temp-readme.txt README.txt  
echo "✓ Passo 2: temp-readme.txt → README.txt"

git commit -m "Rename readme.txt to README.txt (case-sensitive fix)"
```

### 5. Refactoring Completo con Batch Operations

```bash
echo "=== Refactoring Completo ==="

# Creare più file per batch operations
for i in {1..3}; do
  cat > "Feature${i}.js" << EOL
// Legacy Feature ${i}
export function Feature${i}() {
  console.log('Feature ${i} functionality');
}
EOL
done

git add Feature*.js
git commit -m "Add legacy features for refactoring demo"

# Batch rename e spostamento  
mkdir -p src/features

# Rinominare tutti in batch con loop
for file in Feature*.js; do
  # Convertire da FeatureN.js a feature-N.js
  number=${file//[^0-9]/}  # Estrae solo i numeri
  new_name="feature-${number}.js"
  
  git mv "$file" "src/features/$new_name"
  echo "✓ $file → src/features/$new_name"
done

git commit -m "Refactor: organize and rename feature files

- Move all features to src/features/
- Apply kebab-case naming convention
- Maintain individual file history"
```

### 6. Tracking delle Rinominazioni

```bash
echo "=== Verificare Storia delle Rinominazioni ==="

# Vedere storia di un file rinominato
echo "Storia del file home-page.js (originariamente HomePage.js):"
git log --follow --oneline src/pages/home-page.js

echo ""
echo "Diff che mostra la rinominazione:"
git log --follow --stat src/pages/home-page.js | head -20

echo ""  
echo "Vedere tutte le rinominazioni nell'ultimo commit:"
git diff --stat --find-renames HEAD~1 HEAD

echo ""
echo "Mostrare rinominazioni con soglia personalizzata:"
git diff --find-renames=50% HEAD~1 HEAD
```

### 7. Aggiornamento Riferimenti

```bash
echo "=== Aggiornamento Riferimenti nei File ==="

# Creare file che referenzia altri file
cat > src/pages/app.js << 'EOL'
// File principale dell'applicazione
import HomePage from './home-page.js';
import { apiHelpers } from '../services/api-helpers.js';
import '../styles/main.css';
import '../styles/user-profile.css';

export function App() {
  return {
    HomePage,
    apiHelpers
  };
}
EOL

git add src/pages/app.js

# Aggiornare package.json o file di configurazione
cat > package.json << 'EOL'
{
  "name": "refactored-project",
  "version": "1.0.0",
  "main": "src/pages/app.js",
  "scripts": {
    "start": "node src/pages/app.js",
    "build": "build-tool src/"
  },
  "files": [
    "src/",
    "assets/",
    "README.txt"
  ]
}
EOL

git add package.json
git commit -m "Update references after file reorganization

- Add main app file with correct imports
- Update package.json with new file paths
- Ensure all references point to new locations"
```

### 8. Script di Refactoring Automatico

```bash
# Creare script per automatizzare refactoring
cat > refactor-script.sh << 'EOL'
#!/bin/bash
# Automated refactoring script

set -e

echo "🔄 Starting automated refactoring..."

# Function to convert PascalCase to kebab-case
to_kebab_case() {
  echo "$1" | sed 's/\([A-Z]\)/-\L\1/g' | sed 's/^-//'
}

# Rename all PascalCase files
for file in *.js *.jsx; do
  if [[ -f "$file" && "$file" =~ [A-Z] ]]; then
    new_name=$(to_kebab_case "${file%.*}").${file##*.}
    if [[ "$file" != "$new_name" ]]; then
      git mv "$file" "$new_name"
      echo "✓ Renamed: $file → $new_name"
    fi
  fi
done

# Create organized structure
mkdir -p src/{components,pages,services,utils,styles}

# Move files to appropriate directories
for file in *.js; do
  [[ -f "$file" ]] || continue
  
  case "$file" in
    *component*.js|*Component*.js) git mv "$file" "src/components/" ;;
    *page*.js|*Page*.js) git mv "$file" "src/pages/" ;;
    *service*.js|*Service*.js|*api*.js) git mv "$file" "src/services/" ;;
    *util*.js|*helper*.js|*constant*.js) git mv "$file" "src/utils/" ;;
  esac
done

for file in *.css; do
  [[ -f "$file" ]] && git mv "$file" "src/styles/"
done

echo "✅ Refactoring completed!"
EOL

chmod +x refactor-script.sh
git add refactor-script.sh
git commit -m "Add automated refactoring script"
```

## Comandi di Riferimento

```bash
# Rinominazione base
git mv old-name.txt new-name.txt

# Spostamento in directory
git mv file.txt directory/

# Spostamento + rinominazione
git mv file.txt directory/new-name.txt

# Rinominazione case-sensitive (due passi)
git mv readme.txt temp.txt
git mv temp.txt README.txt

# Vedere storia file rinominato
git log --follow file.txt

# Mostrare rinominazioni nel diff
git diff --find-renames HEAD~1 HEAD

# Configurare soglia rilevamento rinominazioni
git config diff.renames 50
```

## Best Practices Dimostrate

1. **Pianificazione**: Sempre committare prima di refactoring maggiori
2. **Convenzioni**: Applicare naming conventions consistenti
3. **Organizzazione**: Raggruppare file per funzionalità/tipo
4. **Storia**: Usare `--follow` per tracciare file rinominati
5. **Riferimenti**: Aggiornare tutti i riferimenti dopo spostamenti
6. **Automazione**: Script per refactoring ripetitivi
7. **Case-sensitivity**: Gestire problemi su sistemi case-insensitive

## Output di Esempio

### git status dopo rinominazioni:
```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    renamed:    HomePage.js -> src/pages/home-page.js
    renamed:    API_helpers.js -> src/services/api-helpers.js
    renamed:    userProfile.css -> src/styles/user-profile.css
```

### git log --follow output:
```
commit a1b2c3d Refactor: organize and rename feature files
commit e4f5g6h Add legacy features for refactoring demo  
commit i7j8k9l Initial commit - unorganized structure
```

Questo esempio mostra un workflow completo di refactoring che mantiene la storia dei file attraverso rinominazioni e spostamenti.
