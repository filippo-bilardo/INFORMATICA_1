# Esercizio: Creazione Repository GitHub

## Obiettivo
Imparare a creare e configurare repository GitHub con diverse tipologie e impostazioni, sviluppando competenze nella gestione repository locali e remoti.

## Prerequisiti
- Account GitHub configurato
- Git installato localmente
- SSH keys configurate
- Conoscenze base di Git

## Parte 1: Repository Pubblico Base

### Step 1: Creazione tramite Web Interface
```
1. Vai su github.com
2. Clicca "+" → "New repository"
3. Compila i campi:
   - Repository name: "my-first-repo"
   - Description: "Il mio primo repository di esercitazione"
   - Public/Private: Public
   - ✅ Add a README file
   - ✅ Add .gitignore (scegli "Node" se sviluppi JS)
   - ✅ Choose a license (MIT per progetti open source)
```

### Step 2: Clone e Setup Locale
```bash
# Clone del repository
git clone git@github.com:USERNAME/my-first-repo.git

# Entra nella directory
cd my-first-repo

# Verifica remote
git remote -v

# Output atteso:
# origin  git@github.com:USERNAME/my-first-repo.git (fetch)
# origin  git@github.com:USERNAME/my-first-repo.git (push)
```

### Step 3: Primo Contributo
```bash
# Crea un file di esempio
echo "# My First Project" > project-info.md
echo "Questo è un progetto di esempio per imparare GitHub." >> project-info.md

# Aggiungi e committa
git add project-info.md
git commit -m "Add project information file"

# Push al repository remoto
git push origin main
```

## Parte 2: Repository Privato per Progetto Personale

### Step 1: Creazione Repository Privato
```
Nuovo repository:
- Repository name: "personal-portfolio"
- Description: "Il mio portfolio personale"
- Private: ✅ Selezionato
- Add README: ✅
- .gitignore: None (inizialmente)
- License: None (per repository privati)
```

### Step 2: Struttura Progetto Portfolio
```bash
# Clone e setup
git clone git@github.com:USERNAME/personal-portfolio.git
cd personal-portfolio

# Crea struttura directory
mkdir -p src/{css,js,images}
mkdir docs

# Crea file base
touch src/index.html
touch src/css/style.css
touch src/js/main.js
touch docs/README.md
```

### Step 3: File di Configurazione
```html
<!-- src/index.html -->
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Portfolio</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <header>
        <h1>Il Mio Portfolio</h1>
        <nav>
            <ul>
                <li><a href="#about">Chi Sono</a></li>
                <li><a href="#projects">Progetti</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <section id="about">
            <h2>Chi Sono</h2>
            <p>Sono uno sviluppatore in formazione...</p>
        </section>
        
        <section id="projects">
            <h2>I Miei Progetti</h2>
            <div class="project-grid">
                <!-- Progetti verranno aggiunti qui -->
            </div>
        </section>
        
        <section id="contact">
            <h2>Contattami</h2>
            <p>Email: your-email@example.com</p>
        </section>
    </main>
    
    <script src="js/main.js"></script>
</body>
</html>
```

```css
/* src/css/style.css */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Arial', sans-serif;
    line-height: 1.6;
    color: #333;
}

header {
    background: #2c3e50;
    color: white;
    padding: 1rem 0;
    position: fixed;
    width: 100%;
    top: 0;
    z-index: 1000;
}

nav ul {
    list-style: none;
    display: flex;
    justify-content: center;
    gap: 2rem;
}

nav a {
    color: white;
    text-decoration: none;
    transition: color 0.3s;
}

nav a:hover {
    color: #3498db;
}

main {
    margin-top: 80px;
    padding: 2rem;
}

section {
    margin-bottom: 3rem;
    padding: 2rem 0;
}

.project-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
    margin-top: 2rem;
}
```

### Step 4: Gitignore per Web Development
```bash
# Crea .gitignore appropriato
cat << 'EOF' > .gitignore
# Dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Production builds
dist/
build/

# Environment variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Editor directories and files
.vscode/
.idea/
*.swp
*.swo
*~

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Logs
logs
*.log

# Temporary files
tmp/
temp/
EOF
```

## Parte 3: Repository con Template

### Step 1: Usa Template GitHub
```
1. Vai su github.com/new
2. Cerca "Choose a template"
3. Scegli un template appropriato (es. "Node.js Template")
4. O crea da zero con configurazioni avanzate
```

### Step 2: Repository per Progetto Node.js
```bash
# Dopo il clone del template o creazione nuovo repo
git clone git@github.com:USERNAME/node-project-template.git
cd node-project-template

# Inizializza package.json
npm init -y

# Modifica package.json per info corrette
```

```json
{
  "name": "node-project-template",
  "version": "1.0.0",
  "description": "Template per progetti Node.js",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js",
    "dev": "nodemon src/index.js",
    "test": "jest",
    "lint": "eslint src/**/*.js"
  },
  "keywords": ["nodejs", "template", "express"],
  "author": "Il Tuo Nome <email@example.com>",
  "license": "MIT",
  "dependencies": {
    "express": "^4.18.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0",
    "jest": "^29.0.0",
    "eslint": "^8.0.0"
  }
}
```

### Step 3: Struttura Progetto Node.js
```bash
# Crea struttura directory
mkdir -p src/{controllers,models,routes,middleware}
mkdir -p tests/{unit,integration}
mkdir docs

# File principali
touch src/index.js
touch src/app.js
touch src/config/database.js
touch tests/app.test.js
touch docs/API.md
```

```javascript
// src/index.js
const app = require('./app');

const PORT = process.env.PORT || 3000;

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
```

```javascript
// src/app.js
const express = require('express');
const app = express();

// Middleware
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Routes
app.get('/', (req, res) => {
    res.json({ 
        message: 'Welcome to Node.js Project Template',
        version: '1.0.0'
    });
});

app.get('/api/health', (req, res) => {
    res.json({ 
        status: 'OK',
        timestamp: new Date().toISOString()
    });
});

module.exports = app;
```

## Parte 4: Repository Collaborativo

### Step 1: Impostazioni Collaborazione
```
1. Vai alle Settings del repository
2. Manage access → Invite a collaborator
3. Aggiungi collaboratori via username/email
4. Configura permessi:
   - Read: Solo lettura
   - Write: Può pushare
   - Admin: Controllo completo
```

### Step 2: Branch Protection Rules
```
Settings → Branches → Add rule

Configurazione consigliata:
✅ Require pull request reviews before merging
✅ Require status checks to pass before merging
✅ Require branches to be up to date before merging
✅ Include administrators
✅ Allow force pushes (solo per testing)
```

### Step 3: Issue Templates
```bash
# Crea directory .github
mkdir -p .github/ISSUE_TEMPLATE

# Template per bug report
cat << 'EOF' > .github/ISSUE_TEMPLATE/bug_report.md
---
name: Bug Report
about: Segnala un bug per aiutarci a migliorare
title: '[BUG] '
labels: bug
assignees: ''
---

## Descrizione del Bug
Una descrizione chiara e concisa del bug.

## Per Riprodurre
Passi per riprodurre il comportamento:
1. Vai a '...'
2. Clicca su '....'
3. Scrolla fino a '....'
4. Vedi errore

## Comportamento Atteso
Descrizione di cosa dovrebbe succedere.

## Screenshot
Se applicabile, aggiungi screenshot per spiegare il problema.

## Informazioni Aggiuntive
- OS: [es. iOS]
- Browser [es. chrome, safari]
- Versione [es. 22]
EOF

# Template per feature request
cat << 'EOF' > .github/ISSUE_TEMPLATE/feature_request.md
---
name: Feature Request
about: Suggerisci un'idea per questo progetto
title: '[FEATURE] '
labels: enhancement
assignees: ''
---

## La tua feature request è collegata a un problema?
Una descrizione chiara e concisa del problema. Es. Sono sempre frustrato quando [...]

## Descrivi la soluzione che vorresti
Una descrizione chiara e concisa di cosa vorresti che succedesse.

## Descrivi alternative che hai considerato
Una descrizione di soluzioni o feature alternative che hai considerato.

## Contesto aggiuntivo
Aggiungi qualsiasi altro contesto o screenshot sulla feature request qui.
EOF
```

## Parte 5: Repository con GitHub Pages

### Step 1: Creazione Repository per Sito Statico
```
Nome repository: "USERNAME.github.io"
(Sostituisci USERNAME con il tuo username GitHub)

Questo diventerà il tuo sito principale!
```

### Step 2: Setup GitHub Pages
```bash
# Clone del repository
git clone git@github.com:USERNAME/USERNAME.github.io.git
cd USERNAME.github.io

# Crea index.html
cat << 'EOF' > index.html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Sito</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            margin: 0;
            padding: 40px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        
        .container {
            text-align: center;
            max-width: 600px;
        }
        
        h1 {
            font-size: 3rem;
            margin-bottom: 1rem;
        }
        
        p {
            font-size: 1.2rem;
            margin-bottom: 2rem;
        }
        
        .btn {
            display: inline-block;
            padding: 12px 24px;
            background: rgba(255,255,255,0.2);
            color: white;
            text-decoration: none;
            border-radius: 8px;
            transition: background 0.3s;
        }
        
        .btn:hover {
            background: rgba(255,255,255,0.3);
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Benvenuto nel Mio Sito!</h1>
        <p>Questo è il mio primo sito web su GitHub Pages.</p>
        <a href="https://github.com/USERNAME" class="btn">Visita il mio GitHub</a>
    </div>
</body>
</html>
EOF

# Commit e push
git add index.html
git commit -m "Add initial website"
git push origin main
```

### Step 3: Abilita GitHub Pages
```
1. Vai nelle Settings del repository
2. Scrolle fino a "Pages"
3. Source: Deploy from a branch
4. Branch: main
5. Folder: / (root)
6. Save
```

Il sito sarà disponibile su: `https://USERNAME.github.io`

## Checklist di Completamento

### Repository Base
- [ ] Repository pubblico creato con README
- [ ] Repository clonato localmente
- [ ] Primo file aggiunto e pushato
- [ ] Remote origin configurato correttamente

### Repository Avanzati
- [ ] Repository privato per portfolio creato
- [ ] Struttura directory organizzata
- [ ] File HTML/CSS base creati
- [ ] .gitignore appropriato configurato

### Template e Collaborazione
- [ ] Repository da template utilizzato
- [ ] Package.json configurato per Node.js
- [ ] Issue templates creati
- [ ] Branch protection rules impostate

### GitHub Pages
- [ ] Repository USERNAME.github.io creato
- [ ] Index.html base pubblicato
- [ ] GitHub Pages abilitato
- [ ] Sito accessibile pubblicamente

### Best Practices
- [ ] Nomi repository descrittivi
- [ ] README informativi
- [ ] Commit messages chiare
- [ ] Licenze appropriate
- [ ] .gitignore files appropriati

## Troubleshooting

### Problema: Push Rejected
```bash
# Errore comune: repository non aggiornato
git pull origin main
git push origin main

# Se ci sono conflitti
git status
# Risolvi conflitti e poi:
git add .
git commit -m "Resolve conflicts"
git push origin main
```

### Problema: SSH Issues
```bash
# Verifica connessione SSH
ssh -T git@github.com

# Se fallisce, aggiungi chiave SSH:
ssh-add ~/.ssh/id_ed25519

# Cambia remote da HTTPS a SSH se necessario
git remote set-url origin git@github.com:USERNAME/REPO.git
```

### Problema: GitHub Pages non Funziona
```
Verifiche da fare:
1. Repository pubblico?
2. File index.html nella root?
3. Pages abilitato nelle settings?
4. Aspetta 5-10 minuti per propagazione
5. Controlla Actions tab per build errors
```

## Progetti Suggeriti per Pratica

### Beginner Level
1. **Todo List**: App semplice HTML/CSS/JS
2. **Landing Page**: Pagina business o personale
3. **Gallery**: Galleria immagini responsive

### Intermediate Level
1. **Blog statico**: Con Jekyll o generatore statico
2. **API REST**: Server Node.js con Express
3. **React App**: Applicazione frontend moderna

### Advanced Level
1. **Full Stack App**: Frontend + Backend + Database
2. **CLI Tool**: Strumento command line in Python/Node
3. **Open Source Contribution**: Contribuisci a progetto esistente

## Risorse Aggiuntive

- [GitHub Docs - Repositories](https://docs.github.com/en/repositories)
- [GitHub Pages Documentation](https://docs.github.com/en/pages)
- [Awesome README Templates](https://github.com/matiassingers/awesome-readme)
- [Gitignore Templates](https://github.com/github/gitignore)
- [Choose a License](https://choosealicense.com/)

## Conclusione
La creazione e gestione di repository è una competenza fondamentale per ogni sviluppatore. Attraverso questi esercizi hai imparato a creare diversi tipi di repository, configurarli appropriatamente e utilizzare le features avanzate di GitHub per collaborazione e deployment.
