# Esercizio 1: Workflow di Merge - Pratica Completa

## Obiettivo
Padroneggiare i diversi tipi di merge attraverso scenari pratici e workflow realistici.

## Setup Progetto Base

```bash
# Crea repository per praticare merge workflows
mkdir merge-workflow-practice
cd merge-workflow-practice
git init

# Struttura progetto web
mkdir -p src/{css,js,components}
mkdir -p docs tests

# File base
cat > src/index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Merge Workflow Practice</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <header>
        <h1>Merge Workflow Practice</h1>
    </header>
    <main>
        <p>Applicazione per praticare workflow di merge</p>
    </main>
    <script src="js/app.js"></script>
</body>
</html>
EOF

cat > src/css/styles.css << 'EOF'
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: Arial, sans-serif;
    line-height: 1.6;
    color: #333;
}

header {
    background: #f4f4f4;
    padding: 1rem;
    text-align: center;
}

main {
    padding: 2rem;
    max-width: 800px;
    margin: 0 auto;
}
EOF

cat > src/js/app.js << 'EOF'
// Main application
document.addEventListener('DOMContentLoaded', function() {
    console.log('Merge Workflow Practice App loaded');
});
EOF

git add .
git commit -m "Initial project setup with basic structure"
```

## Scenario 1: Fast-Forward Merge

### Feature Semplice - Solo CSS
```bash
# Crea branch per miglioramenti styling
git checkout -b feature/improved-styling

# Miglioramento 1: Colori
cat >> src/css/styles.css << 'EOF'

/* Enhanced color scheme */
:root {
    --primary-color: #3498db;
    --secondary-color: #2c3e50;
    --accent-color: #e74c3c;
}

header {
    background: var(--primary-color);
    color: white;
}

header h1 {
    font-size: 2.5rem;
    margin: 0;
}
EOF

git add src/css/styles.css
git commit -m "Add CSS variables and improve header styling"

# Miglioramento 2: Layout
cat >> src/css/styles.css << 'EOF'

/* Responsive layout */
main {
    padding: 3rem 2rem;
    background: #f9f9f9;
    border-radius: 8px;
    margin: 2rem auto;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

@media (max-width: 768px) {
    main {
        margin: 1rem;
        padding: 2rem 1rem;
    }
    
    header h1 {
        font-size: 2rem;
    }
}
EOF

git add src/css/styles.css
git commit -m "Add responsive design and card layout"

# Verifica storia pre-merge
git log --oneline --graph --all

# Fast-forward merge
git checkout main
git merge feature/improved-styling

# Verifica: dovrebbe essere fast-forward
git log --oneline --graph
```

### Analizza Fast-Forward
```bash
# Verifica tipo di merge
git log --merges  # Non dovrebbe mostrare commit di merge

# Cleanup
git branch -d feature/improved-styling
```

## Scenario 2: Merge Ricorsivo (3-Way)

### Setup Sviluppo Parallelo
```bash
# Sviluppo su main mentre feature in corso
echo "/* Main branch updates */" >> src/css/styles.css
git add src/css/styles.css
git commit -m "Add main branch styling updates"

# Crea feature che diverge
git checkout -b feature/interactive-components

# Sviluppa JavaScript
cat > src/js/components.js << 'EOF'
// Interactive components
class ToggleButton {
    constructor(selector) {
        this.element = document.querySelector(selector);
        this.isActive = false;
        this.init();
    }
    
    init() {
        this.element.addEventListener('click', () => this.toggle());
    }
    
    toggle() {
        this.isActive = !this.isActive;
        this.element.classList.toggle('active', this.isActive);
    }
}

class ModalDialog {
    constructor(triggerSelector, modalSelector) {
        this.trigger = document.querySelector(triggerSelector);
        this.modal = document.querySelector(modalSelector);
        this.init();
    }
    
    init() {
        this.trigger.addEventListener('click', () => this.open());
        this.modal.addEventListener('click', (e) => {
            if (e.target === this.modal) this.close();
        });
    }
    
    open() {
        this.modal.style.display = 'flex';
    }
    
    close() {
        this.modal.style.display = 'none';
    }
}

export { ToggleButton, ModalDialog };
EOF

# Aggiorna HTML per usare componenti
cat > src/index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Merge Workflow Practice</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <header>
        <h1>Merge Workflow Practice</h1>
        <button id="toggle-btn">Toggle Theme</button>
    </header>
    <main>
        <p>Applicazione per praticare workflow di merge</p>
        <button id="modal-trigger">Open Modal</button>
        
        <div id="modal" class="modal">
            <div class="modal-content">
                <h2>Example Modal</h2>
                <p>This is an interactive component!</p>
            </div>
        </div>
    </main>
    <script type="module" src="js/app.js"></script>
</body>
</html>
EOF

git add .
git commit -m "Add interactive components and modal functionality"

# CSS per componenti
cat >> src/css/styles.css << 'EOF'

/* Interactive components */
.toggle-btn {
    background: var(--accent-color);
    color: white;
    border: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    cursor: pointer;
    margin-left: 1rem;
}

.toggle-btn:hover {
    opacity: 0.9;
}

.modal {
    display: none;
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0,0,0,0.5);
    justify-content: center;
    align-items: center;
}

.modal-content {
    background: white;
    padding: 2rem;
    border-radius: 8px;
    max-width: 500px;
    width: 90%;
}

button {
    background: var(--primary-color);
    color: white;
    border: none;
    padding: 0.75rem 1.5rem;
    border-radius: 4px;
    cursor: pointer;
    font-size: 1rem;
}

button:hover {
    opacity: 0.9;
}
EOF

git add src/css/styles.css
git commit -m "Add styling for interactive components"

# Visualizza divergenza
git log --oneline --graph --all
```

### Esegui Merge Ricorsivo
```bash
# Torna su main
git checkout main

# Merge (sarà ricorsivo)
git merge feature/interactive-components -m "Integrate interactive components

- Add ToggleButton and ModalDialog classes
- Update HTML with interactive elements  
- Add component styling
- Maintain main branch updates"

# Analizza merge commit
git log --oneline --graph -5
git show --stat  # Mostra statistiche merge
```

### Cleanup Post-Merge
```bash
# Elimina feature branch
git branch -d feature/interactive-components

# Test funzionalità
echo "Test complete - interactive components integrated!"
```

## Scenario 3: Squash Merge

### Feature Multi-Commit da Squashare
```bash
# Crea feature con molti commit piccoli
git checkout -b feature/documentation

# Commit 1: README base
cat > README.md << 'EOF'
# Merge Workflow Practice

Progetto per imparare i workflow di merge in Git.
EOF

git add README.md
git commit -m "Add basic README"

# Commit 2: Aggiungi installazione
cat >> README.md << 'EOF'

## Installazione

1. Clone repository
2. Apri index.html nel browser
EOF

git add README.md
git commit -m "Add installation instructions"

# Commit 3: Fix typo
sed -i 's/Clone/Clona/' README.md
git add README.md
git commit -m "Fix typo: Clone -> Clona"

# Commit 4: Aggiungi features
cat >> README.md << 'EOF'

## Features

- Responsive design
- Interactive components
- Modal dialogs
- Theme toggle
EOF

git add README.md
git commit -m "Add features list"

# Commit 5: Aggiungi contributing
cat >> README.md << 'EOF'

## Contributing

1. Fork il repository
2. Crea feature branch
3. Committa le modifiche
4. Crea pull request
EOF

git add README.md
git commit -m "Add contributing guidelines"

# Visualizza tutti i piccoli commit
git log --oneline feature/documentation
```

### Squash Merge
```bash
# Torna su main
git checkout main

# Squash merge (combina tutti commit in uno)
git merge --squash feature/documentation

# Crea commit unico per tutto il lavoro
git commit -m "Add comprehensive project documentation

- Add README with project description
- Add installation instructions  
- Add features list
- Add contributing guidelines
- Fix language localization"

# Verifica: non c'è commit di merge, solo un commit pulito
git log --oneline -3

# Cleanup (branch non eliminato automaticamente con squash)
git branch -D feature/documentation
```

## Scenario 4: Merge con Conflitti (Simulazione)

### Setup Conflitto
```bash
# Modifica su main
cat >> src/js/app.js << 'EOF'

// Main branch enhancement
function initMainFeatures() {
    console.log('Main features initialized');
    // Main branch specific code
}

document.addEventListener('DOMContentLoaded', function() {
    console.log('Merge Workflow Practice App loaded');
    initMainFeatures();
});
EOF

git add src/js/app.js
git commit -m "Add main branch features initialization"

# Feature che modifica stesso file
git checkout -b feature/app-enhancement

cat > src/js/app.js << 'EOF'
// Enhanced application with utilities
function initApp() {
    console.log('Enhanced app starting...');
    loadUtilities();
    setupEventListeners();
}

function loadUtilities() {
    console.log('Loading utilities...');
}

function setupEventListeners() {
    console.log('Setting up event listeners...');
}

document.addEventListener('DOMContentLoaded', function() {
    console.log('Merge Workflow Practice App loaded');
    initApp();
});
EOF

git add src/js/app.js
git commit -m "Refactor app.js with enhanced initialization"
```

### Risolvi Conflitto
```bash
# Tenta merge (avrà conflitto)
git checkout main
git merge feature/app-enhancement

# Git mostrerà conflitto - risolvi manualmente
cat > src/js/app.js << 'EOF'
// Enhanced application with utilities and main features
function initApp() {
    console.log('Enhanced app starting...');
    loadUtilities();
    setupEventListeners();
    initMainFeatures();
}

function loadUtilities() {
    console.log('Loading utilities...');
}

function setupEventListeners() {
    console.log('Setting up event listeners...');
}

function initMainFeatures() {
    console.log('Main features initialized');
    // Main branch specific code
}

document.addEventListener('DOMContentLoaded', function() {
    console.log('Merge Workflow Practice App loaded');
    initApp();
});
EOF

# Risolvi conflitto
git add src/js/app.js
git commit -m "Resolve merge conflict: integrate both app enhancements"

# Cleanup
git branch -d feature/app-enhancement
```

## Analisi Workflow Completato

### Confronta Tipi di Merge
```bash
# Visualizza storia completa
git log --oneline --graph

# Identifica tipi di merge
echo "=== MERGE ANALYSIS ==="
echo "Fast-forward: Styling improvements (linear history)"
echo "Recursive: Interactive components (merge commit visible)"  
echo "Squash: Documentation (single clean commit)"
echo "With conflict: App enhancement (conflict resolution)"
```

### Statistiche Progetto
```bash
# File creati/modificati
find . -name "*.html" -o -name "*.css" -o -name "*.js" -o -name "*.md" | wc -l

# Commit totali
git rev-list --count HEAD

# Contributors (simulati)
git shortlog -s -n
```

## Esercizi Aggiuntivi

### Challenge 1: No-FF Policy
```bash
# Imposta policy no fast-forward
git config merge.ff false

# Crea feature semplice e verifica sempre merge commit
git checkout -b test/no-ff-policy
echo "test" > test.txt
git add test.txt
git commit -m "Test no-ff policy"

git checkout main
git merge test/no-ff-policy

# Dovrebbe creare merge commit anche se fast-forward possibile
git log --oneline -3
git branch -d test/no-ff-policy
```

### Challenge 2: Cherry-Pick vs Merge
```bash
# Crea feature con commit multipli
git checkout -b feature/cherry-pick-test
echo "feature1" > feature1.txt
git add feature1.txt
git commit -m "Add feature 1"

echo "feature2" > feature2.txt
git add feature2.txt  
git commit -m "Add feature 2"

# Cherry-pick solo un commit invece di merge completo
git checkout main
git cherry-pick feature/cherry-pick-test~1  # Solo primo commit

# Confronta con merge completo
git log --oneline
git branch -D feature/cherry-pick-test
```

## Valutazione

### Checklist Competenze:
- [ ] Fast-forward merge eseguito
- [ ] Merge ricorsivo completato  
- [ ] Squash merge utilizzato
- [ ] Conflitto risolto manualmente
- [ ] Tipi di merge identificati nella storia
- [ ] Branch cleanup eseguito
- [ ] Policy merge configurate

### Scenari Dimostrati:
- [ ] Feature lineare (fast-forward)
- [ ] Sviluppo parallelo (recursive)
- [ ] Cleanup storia (squash)
- [ ] Gestione conflitti
- [ ] Workflow comparison

---

Questo esercizio copre tutti i principali workflow di merge che incontrerai nello sviluppo reale!
