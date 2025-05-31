#!/bin/bash

# Esempio 02 - Git Add Avanzato: Pattern e Selezioni
# Dimostra l'uso avanzato di git add con pattern matching e staging selettivo

echo "🚀 Esempio 02: Git Add Avanzato"
echo "==============================="

# Preparazione ambiente
echo "📁 Preparazione ambiente di test..."
mkdir -p git-add-advanced
cd git-add-advanced
git init
git config user.name "Studente Git"
git config user.email "studente@example.com"

# Creazione struttura progetto complessa
echo ""
echo "1️⃣ Creazione struttura progetto"
mkdir -p src/{components,utils,styles} tests docs

# File JavaScript
cat > src/components/Header.js << 'EOF'
// Componente Header
export function Header() {
    return `
        <header class="header">
            <h1>Il Mio Sito</h1>
            <nav>
                <a href="/">Home</a>
                <a href="/about">About</a>
            </nav>
        </header>
    `;
}
EOF

cat > src/components/Footer.js << 'EOF'
// Componente Footer
export function Footer() {
    return `
        <footer class="footer">
            <p>&copy; 2024 Il Mio Sito</p>
        </footer>
    `;
}
EOF

cat > src/utils/helpers.js << 'EOF'
// Utility functions
export function formatDate(date) {
    return new Intl.DateTimeFormat('it-IT').format(date);
}

export function validateEmail(email) {
    const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return regex.test(email);
}
EOF

cat > src/utils/api.js << 'EOF'
// API utilities
const BASE_URL = 'https://api.example.com';

export async function fetchData(endpoint) {
    const response = await fetch(`${BASE_URL}${endpoint}`);
    return response.json();
}
EOF

# File CSS
cat > src/styles/main.css << 'EOF'
/* Main styles */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
}

.header {
    background: #333;
    color: white;
    padding: 1rem;
}
EOF

cat > src/styles/components.css << 'EOF'
/* Component styles */
.footer {
    background: #f8f9fa;
    text-align: center;
    padding: 2rem;
    margin-top: auto;
}
EOF

# File di test
cat > tests/helpers.test.js << 'EOF'
// Test per helpers
import { validateEmail, formatDate } from '../src/utils/helpers.js';

console.log('Testing validateEmail...');
console.assert(validateEmail('test@example.com') === true);
console.assert(validateEmail('invalid-email') === false);

console.log('Testing formatDate...');
const date = new Date('2024-01-15');
console.log(formatDate(date));
EOF

cat > tests/components.test.js << 'EOF'
// Test per componenti
import { Header, Footer } from '../src/components/Header.js';

console.log('Testing Header component...');
const header = Header();
console.assert(header.includes('<header'));

console.log('Testing Footer component...');
const footer = Footer();
console.assert(footer.includes('<footer'));
EOF

# File di configurazione e documentazione
cat > package.json << 'EOF'
{
  "name": "mio-progetto",
  "version": "1.0.0",
  "description": "Progetto di esempio per Git",
  "main": "src/main.js",
  "scripts": {
    "test": "node tests/*.test.js",
    "start": "node src/main.js"
  },
  "keywords": ["git", "javascript", "esempio"],
  "author": "Studente",
  "license": "MIT"
}
EOF

cat > .gitignore << 'EOF'
# Dependencies
node_modules/
npm-debug.log

# Environment
.env
.env.local

# Build
dist/
build/

# IDE
.vscode/
.idea/

# OS
.DS_Store
Thumbs.db

# Logs
*.log
logs/
EOF

cat > README.md << 'EOF'
# Mio Progetto

Progetto di esempio per imparare Git.

## Installazione
```bash
npm install
```

## Test
```bash
npm test
```
EOF

cat > docs/api.md << 'EOF'
# Documentazione API

## Endpoints disponibili

### GET /users
Restituisce lista utenti

### POST /users
Crea nuovo utente
EOF

# File temporanei (da non committare)
echo "File temporaneo" > temp.log
echo "Cache file" > cache.tmp
echo "Debug info" > debug.log

echo "✅ Struttura progetto creata"

# 2. Verifica status iniziale
echo ""
echo "2️⃣ Status iniziale - tutti i file non tracciati"
git status
echo ""

# 3. Esempio 1: Add per pattern di file
echo "3️⃣ ESEMPIO 1: Add per pattern di file"
echo "Aggiungiamo solo i file JavaScript:"
git add *.js
git status
echo ""

echo "Commit dei file JavaScript principali:"
git commit -m "Add main JavaScript files

- Add package.json configuration
- Create project structure"
echo ""

# 4. Esempio 2: Add per estensione ricorsiva
echo "4️⃣ ESEMPIO 2: Add ricorsivo per estensione"
echo "Aggiungiamo tutti i file .js nelle sottocartelle:"
git add **/*.js
git status
echo ""

echo "Commit di tutti i JavaScript:"
git commit -m "Add all JavaScript modules

- Add Header and Footer components
- Add utility functions for date and email
- Add API utilities
- Add test files"
echo ""

# 5. Esempio 3: Add per directory
echo "5️⃣ ESEMPIO 3: Add per directory"
echo "Aggiungiamo tutti i file CSS:"
git add src/styles/
git status
echo ""

echo "Commit degli stili:"
git commit -m "Add CSS styling

- Add main styles
- Add component-specific styles"
echo ""

# 6. Esempio 4: Add escludendo file
echo "6️⃣ ESEMPIO 4: Add con esclusioni"
echo "Aggiungiamo tutto tranne i file .log:"
git add .
git reset HEAD *.log  # Rimuovi file .log dal staging
git status
echo ""

echo "Commit documentazione e configurazione:"
git commit -m "Add documentation and configuration

- Add README with instructions
- Add API documentation  
- Add .gitignore for common exclusions"
echo ""

# 7. Esempio 5: Add interattivo (simulato)
echo "7️⃣ ESEMPIO 5: Add interattivo"
echo "Modifichiamo un file per dimostrare git add -p"

# Modifichiamo helpers.js
cat >> src/utils/helpers.js << 'EOF'

// Nuova funzione aggiunta
export function capitalizeString(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
}

// Un'altra funzione
export function slugify(text) {
    return text
        .toLowerCase()
        .trim()
        .replace(/[^\w\s-]/g, '')
        .replace(/[\s_-]+/g, '-');
}
EOF

echo "File helpers.js modificato con 2 nuove funzioni"
echo ""
echo "Contenuto delle modifiche:"
git diff src/utils/helpers.js
echo ""

echo "Con git add -p potresti scegliere di aggiungere solo una funzione per volta"
echo "(In questo esempio aggiungiamo tutto)"
git add src/utils/helpers.js
git commit -m "Add string utility functions

- Add capitalizeString function
- Add slugify function for URL-friendly strings"
echo ""

# 8. Dimostrazione di add -u vs add .
echo "8️⃣ ESEMPIO 6: Differenza tra add -u e add ."

# Creiamo un nuovo file
echo "console.log('New feature');" > src/newFeature.js

# Modifichiamo un file esistente
echo "/* Updated styles */" >> src/styles/main.css

echo "Nuovo file creato: src/newFeature.js"
echo "File esistente modificato: src/styles/main.css"
echo ""

echo "git status mostra:"
git status
echo ""

echo "git add -u (solo file già tracciati):"
git add -u
git status
echo ""

echo "Commit delle modifiche ai file esistenti:"
git commit -m "Update existing CSS styles"
echo ""

echo "git add . (anche file nuovi):"
git add .
git status
echo ""

echo "Commit del nuovo file:"
git commit -m "Add new feature module"
echo ""

# 9. Storia finale e statistiche
echo "9️⃣ Storia completa del progetto"
git log --oneline --graph
echo ""

echo "📊 Statistiche progetto:"
echo "File totali tracciati:"
git ls-files | wc -l
echo ""
echo "File per tipo:"
git ls-files | grep -E '\.(js|css|md|json)$' | cut -d. -f2 | sort | uniq -c
echo ""

echo "🎉 Esempio completato!"
echo ""
echo "📝 Tecniche dimostrate:"
echo "   - git add *.ext (pattern per estensione)"
echo "   - git add **/*.ext (pattern ricorsivo)"
echo "   - git add directory/ (intera directory)"
echo "   - git add . vs git add -u"
echo "   - git reset HEAD file (rimuovi dal staging)"
echo "   - Uso di .gitignore per esclusioni automatiche"
echo ""
echo "💡 Comandi utili da ricordare:"
echo "   - git add -p (staging interattivo)"
echo "   - git add -A (tutto il repository)"
echo "   - git ls-files (lista file tracciati)"
echo "   - git status -s (status compatto)"
