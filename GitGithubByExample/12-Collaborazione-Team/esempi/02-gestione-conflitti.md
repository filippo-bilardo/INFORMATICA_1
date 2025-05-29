# Gestione Avanzata dei Conflitti

## Obiettivi
- Comprendere i diversi tipi di conflitti
- Imparare strategie di risoluzione avanzate
- Utilizzare strumenti per la risoluzione dei conflitti
- Prevenire i conflitti attraverso buone pratiche

## Scenario: Conflitti in un Progetto Web

### Situazione Iniziale
Simuliamo conflitti comuni in un team di sviluppo:

```bash
# Configurazione del repository
mkdir gestione-conflitti
cd gestione-conflitti
git init

# Creazione file base
cat > index.html << EOF
<!DOCTYPE html>
<html>
<head>
    <title>E-commerce Site</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <h1>Shop Online</h1>
        <nav>
            <ul>
                <li><a href="#home">Home</a></li>
                <li><a href="#products">Products</a></li>
                <li><a href="#contact">Contact</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section id="hero">
            <h2>Welcome to our store</h2>
            <p>Find the best products at great prices</p>
        </section>
    </main>
</body>
</html>
EOF

cat > style.css << EOF
/* Base styles */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f5f5f5;
}

header {
    background-color: #333;
    color: white;
    padding: 1rem;
}

nav ul {
    list-style: none;
    display: flex;
    gap: 20px;
    margin: 0;
    padding: 0;
}

nav a {
    color: white;
    text-decoration: none;
}

#hero {
    text-align: center;
    padding: 2rem;
    background-color: white;
    margin: 1rem;
    border-radius: 8px;
}
EOF

git add .
git commit -m "Initial project setup"
```

### 1. Conflitti di Contenuto

#### Developer A - Modifica Header
```bash
# Creazione branch developer-a
git checkout -b feature/header-redesign

# Modifica header
cat > index.html << EOF
<!DOCTYPE html>
<html>
<head>
    <title>Premium E-commerce</title>
    <link rel="stylesheet" href="style.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <header>
        <h1>Premium Shop</h1>
        <nav>
            <ul>
                <li><a href="#home">Home</a></li>
                <li><a href="#products">Products</a></li>
                <li><a href="#about">About Us</a></li>
                <li><a href="#contact">Contact</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section id="hero">
            <h2>Premium Products, Premium Service</h2>
            <p>Discover our exclusive collection of high-quality items</p>
            <button>Shop Now</button>
        </section>
    </main>
</body>
</html>
EOF

git add .
git commit -m "feat: redesign header with premium branding"
```

#### Developer B - Modifica CSS
```bash
# Ritorno al main
git checkout main

# Creazione branch developer-b
git checkout -b feature/responsive-design

# Modifica CSS
cat > style.css << EOF
/* Responsive base styles */
* {
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f8f9fa;
    line-height: 1.6;
}

header {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 1rem;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

header h1 {
    margin: 0;
    font-size: 2rem;
}

nav ul {
    list-style: none;
    display: flex;
    gap: 20px;
    margin: 10px 0 0 0;
    padding: 0;
    flex-wrap: wrap;
}

nav a {
    color: white;
    text-decoration: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    transition: background-color 0.3s;
}

nav a:hover {
    background-color: rgba(255,255,255,0.2);
}

#hero {
    text-align: center;
    padding: 3rem 1rem;
    background: white;
    margin: 2rem;
    border-radius: 12px;
    box-shadow: 0 4px 6px rgba(0,0,0,0.1);
}

#hero h2 {
    color: #333;
    margin-bottom: 1rem;
    font-size: 2.5rem;
}

@media (max-width: 768px) {
    nav ul {
        flex-direction: column;
        gap: 10px;
    }
    
    #hero {
        margin: 1rem;
        padding: 2rem 1rem;
    }
    
    #hero h2 {
        font-size: 2rem;
    }
}
EOF

git add .
git commit -m "feat: implement responsive design with modern styling"
```

### 2. Merge e Risoluzione Conflitti

#### Primo Merge (senza conflitti)
```bash
# Merge del branch CSS
git checkout main
git merge feature/responsive-design
echo "✅ Merge CSS completato senza conflitti"
```

#### Secondo Merge (con conflitti)
```bash
# Tentativo di merge del branch header
git merge feature/header-redesign
echo "❌ Conflitti rilevati!"
```

### 3. Strategie di Risoluzione

#### A. Risoluzione Manuale
```bash
# Visualizzazione dello stato
git status

# Visualizzazione dei conflitti
git diff

# Apertura file per risoluzione manuale
# Il file conterrà marcatori di conflitto:
# <<<<<<< HEAD
# =======
# >>>>>>> feature/header-redesign
```

#### B. Risoluzione con Git Mergetool
```bash
# Configurazione del mergetool (opzionale)
git config --global merge.tool vimdiff  # o code, meld, etc.

# Avvio del mergetool
git mergetool
```

#### C. Risoluzione Strategica
```bash
# Strategia: mantenere la versione di main
git checkout --ours index.html

# Strategia: mantenere la versione del branch
git checkout --theirs index.html

# Strategia: combinare le modifiche
cat > index.html << EOF
<!DOCTYPE html>
<html>
<head>
    <title>Premium E-commerce</title>
    <link rel="stylesheet" href="style.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <header>
        <h1>Premium Shop</h1>
        <nav>
            <ul>
                <li><a href="#home">Home</a></li>
                <li><a href="#products">Products</a></li>
                <li><a href="#about">About Us</a></li>
                <li><a href="#contact">Contact</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section id="hero">
            <h2>Premium Products, Premium Service</h2>
            <p>Discover our exclusive collection of high-quality items</p>
            <button class="cta-button">Shop Now</button>
        </section>
    </main>
</body>
</html>
EOF

# Aggiunta stili per il nuovo button
cat >> style.css << EOF

.cta-button {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    border: none;
    padding: 1rem 2rem;
    font-size: 1.1rem;
    border-radius: 6px;
    cursor: pointer;
    transition: transform 0.2s, box-shadow 0.2s;
    margin-top: 1rem;
}

.cta-button:hover {
    transform: translateY(-2px);
    box-shadow: 0 6px 20px rgba(102, 126, 234, 0.4);
}
EOF
```

#### Completamento del Merge
```bash
# Aggiunta delle modifiche risolte
git add .

# Completamento del merge
git commit -m "resolve: merge header redesign with responsive design

- Combined premium branding with responsive CSS
- Added styled CTA button
- Maintained responsive design features
- Resolved conflicts in index.html"

echo "✅ Conflitti risolti e merge completato"
```

### 4. Prevenzione dei Conflitti

#### A. Comunicazione e Coordinamento
```bash
# Creazione di file per tracciare le modifiche
cat > DEVELOPMENT.md << EOF
# Development Guidelines

## Current Work in Progress

### Active Branches
- \`feature/payment-integration\` - Developer C
- \`feature/user-authentication\` - Developer A
- \`hotfix/css-mobile-fix\` - Developer B

### File Ownership
- \`index.html\` - Currently being modified by Dev A
- \`style.css\` - Available for modification
- \`scripts/\` - Developer C working on payment module

### Merge Schedule
- Daily merges at 5 PM
- Feature freeze on Fridays

## Communication Channels
- Slack: #dev-team
- Daily standups: 9 AM
EOF
```

#### B. Atomic Commits e Feature Branches
```bash
# Creazione branch per feature specifica
git checkout -b feature/search-functionality

# Implementazione incrementale
echo "<!-- Search functionality placeholder -->" >> index.html
git add index.html
git commit -m "feat: add search placeholder in header"

# Aggiunta CSS per search
cat >> style.css << EOF

.search-container {
    margin: 1rem 0;
}

.search-input {
    padding: 0.5rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    width: 300px;
    max-width: 100%;
}
EOF

git add style.css
git commit -m "style: add search input styling"

# JavaScript per la ricerca
cat > search.js << EOF
document.addEventListener('DOMContentLoaded', function() {
    const searchInput = document.querySelector('.search-input');
    
    if (searchInput) {
        searchInput.addEventListener('input', function(e) {
            console.log('Searching for:', e.target.value);
            // TODO: Implement search logic
        });
    }
});
EOF

git add search.js
git commit -m "feat: add basic search functionality"
```

#### C. Rebase per Storia Lineare
```bash
# Aggiornamento del branch con le ultime modifiche
git checkout main
git pull origin main

git checkout feature/search-functionality
git rebase main

# Risoluzione di eventuali conflitti durante rebase
# ...

# Push del branch aggiornato
git push origin feature/search-functionality --force-with-lease
```

### 5. Strumenti Avanzati per Conflitti

#### A. Git Rerere (Reuse Recorded Resolution)
```bash
# Abilitazione di rerere
git config rerere.enabled true

# Git ricorderà le risoluzioni precedenti
echo "✅ Rerere abilitato - le risoluzioni future saranno automatiche"
```

#### B. Custom Merge Drivers
```bash
# Configurazione per file specifici
echo "*.config merge=union" >> .gitattributes

# Driver personalizzato per file di configurazione
git config merge.union.driver true
```

#### C. Conflict Markers Personalizzati
```bash
# Configurazione di marker più descrittivi
git config merge.conflictstyle diff3

# I conflitti mostreranno anche l'antenato comune
```

## Best Practices per la Gestione Conflitti

### 1. **Prevenzione**
- Comunicazione frequente nel team
- Branch di vita breve
- Merge/rebase frequenti
- Atomic commits
- Code review obbligatori

### 2. **Durante la Risoluzione**
- Comprendere il contesto di entrambe le modifiche
- Testare sempre dopo la risoluzione
- Documentare decisioni complesse
- Non avere fretta nelle risoluzioni

### 3. **Dopo la Risoluzione**
- Commit descrittivo della risoluzione
- Test completi del codice unito
- Comunicazione al team delle decisioni prese

## Troubleshooting

### Problemi Comuni

#### "Cannot merge unrelated histories"
```bash
git merge --allow-unrelated-histories feature-branch
```

#### Merge accidentale
```bash
# Annullamento dell'ultimo merge
git reset --hard HEAD~1

# O reset al commit specifico
git reset --hard <commit-hash>
```

#### Conflitti ricorrenti
```bash
# Configurazione di strategie di merge specifiche
git config merge.ours.driver true

# Per file che devono sempre mantenere la versione locale
echo "version.txt merge=ours" >> .gitattributes
```

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ Team Workflow Basics](01-team-workflow.md)
- [➡️ Code Review Workflow](03-code-review.md)
