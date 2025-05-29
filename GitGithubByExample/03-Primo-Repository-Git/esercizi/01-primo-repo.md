# Esercizio 1: Il Mio Primo Repository

## 🎯 Obiettivo
Creare e gestire il tuo primo repository Git da zero, applicando i concetti fondamentali appresi nelle guide teoriche.

## ⏱️ Durata Stimata
45-60 minuti

## 📋 Prerequisiti
- Git installato e configurato
- Conoscenza dei comandi base di terminal/command prompt
- Completamento delle guide teoriche del modulo

## 🎮 Scenario di Gioco
Sei un developer junior che ha appena iniziato a lavorare in una software house. Il tuo team leader ti ha assegnato il compito di creare un repository per un nuovo progetto: un **Portfolio Personale**. Devi dimostrare le tue competenze Git partendo da zero!

## 📚 Livelli di Difficoltà

### 🥉 Livello Bronze: Setup Base

#### Passo 1: Preparazione dell'Ambiente
```bash
# Crea una directory per il tuo portfolio
mkdir il-mio-portfolio
cd il-mio-portfolio

# Verifica di essere nella directory corretta
pwd
```

**✅ Checkpoint:** La directory deve esistere e devi trovarti al suo interno.

#### Passo 2: Inizializzazione Repository
```bash
# Inizializza il repository Git
git init

# Verifica che sia stato creato correttamente
ls -la
git status
```

**✅ Checkpoint:** Dovresti vedere la cartella `.git` e il messaggio "On branch main/master"

#### Passo 3: Primo File e Commit
```bash
# Crea il file README
echo "# Il Mio Portfolio" > README.md

# Aggiungi al tracking
git add README.md

# Crea il primo commit
git commit -m "Initial commit: Add README"
```

**✅ Checkpoint:** Il commit deve essere creato con successo.

**🎖️ Badge Ottenuto:** "Repository Creator" 🏗️

### 🥈 Livello Silver: Sviluppo Strutturato

#### Passo 4: Struttura del Portfolio
```bash
# Crea la struttura delle directory
mkdir -p {css,js,images,projects}

# Crea i file base
touch index.html
touch css/style.css
touch js/script.js
```

#### Passo 5: Contenuto HTML
Crea il contenuto di `index.html`:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>[Il Tuo Nome] - Portfolio</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <header>
        <h1>Benvenuto nel mio Portfolio</h1>
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
            <p>Sono uno sviluppatore in formazione con passione per Git e GitHub!</p>
        </section>
        
        <section id="projects">
            <h2>I Miei Progetti</h2>
            <div class="project">
                <h3>Il Mio Primo Repository</h3>
                <p>Un portfolio creato seguendo le best practice Git.</p>
            </div>
        </section>
        
        <section id="contact">
            <h2>Contatti</h2>
            <p>Email: tuoemail@example.com</p>
        </section>
    </main>
    
    <script src="js/script.js"></script>
</body>
</html>
```

#### Passo 6: Stili CSS
Aggiungi contenuto a `css/style.css`:
```css
/* Portfolio Styles */
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
    padding: 1rem;
    text-align: center;
}

nav ul {
    list-style: none;
    display: flex;
    justify-content: center;
    gap: 2rem;
    margin-top: 1rem;
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
    max-width: 800px;
    margin: 2rem auto;
    padding: 0 1rem;
}

section {
    margin-bottom: 2rem;
}

.project {
    background: #f4f4f4;
    padding: 1rem;
    margin: 1rem 0;
    border-radius: 5px;
}
```

#### Passo 7: JavaScript Interattivo
Aggiungi contenuto a `js/script.js`:
```javascript
// Portfolio JavaScript
document.addEventListener('DOMContentLoaded', function() {
    console.log('Portfolio caricato con successo!');
    
    // Smooth scrolling per i link di navigazione
    const navLinks = document.querySelectorAll('nav a');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const targetId = this.getAttribute('href');
            const targetElement = document.querySelector(targetId);
            
            if (targetElement) {
                targetElement.scrollIntoView({
                    behavior: 'smooth'
                });
            }
        });
    });
    
    // Messaggio di benvenuto
    setTimeout(() => {
        alert('Benvenuto nel mio portfolio! 🚀');
    }, 1000);
});
```

#### Passo 8: Commit Strutturato
```bash
# Aggiungi tutto al tracking
git add .

# Verifica cosa stai per committare
git status

# Crea un commit descrittivo
git commit -m "✨ Add complete portfolio structure

- Add semantic HTML structure with navigation
- Implement responsive CSS with modern styling
- Add interactive JavaScript with smooth scrolling
- Create organized directory structure"
```

**🎖️ Badge Ottenuto:** "Structure Master" 🏛️

### 🥇 Livello Gold: Evoluzione Avanzata

#### Passo 9: Miglioramenti Incrementali

**Aggiunta Progetto:**
```bash
# Crea un file per un nuovo progetto
cat > projects/calculator.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Calculator</title>
    <style>
        .calculator {
            max-width: 300px;
            margin: 20px auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 10px;
        }
        .display {
            width: 100%;
            height: 50px;
            font-size: 20px;
            text-align: right;
            margin-bottom: 10px;
        }
        .buttons {
            display: grid;
            grid-template-columns: repeat(4, 1fr);
            gap: 10px;
        }
        button {
            height: 50px;
            font-size: 16px;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div class="calculator">
        <input type="text" class="display" id="display" readonly>
        <div class="buttons">
            <button onclick="clearDisplay()">C</button>
            <button onclick="deleteLast()">⌫</button>
            <button onclick="appendToDisplay('/')">/</button>
            <button onclick="appendToDisplay('*')">*</button>
            <button onclick="appendToDisplay('7')">7</button>
            <button onclick="appendToDisplay('8')">8</button>
            <button onclick="appendToDisplay('9')">9</button>
            <button onclick="appendToDisplay('-')">-</button>
            <button onclick="appendToDisplay('4')">4</button>
            <button onclick="appendToDisplay('5')">5</button>
            <button onclick="appendToDisplay('6')">6</button>
            <button onclick="appendToDisplay('+')">+</button>
            <button onclick="appendToDisplay('1')">1</button>
            <button onclick="appendToDisplay('2')">2</button>
            <button onclick="appendToDisplay('3')">3</button>
            <button onclick="calculate()" rowspan="2">=</button>
            <button onclick="appendToDisplay('0')" colspan="2">0</button>
            <button onclick="appendToDisplay('.')">.</button>
        </div>
    </div>
    
    <script>
        function appendToDisplay(value) {
            document.getElementById('display').value += value;
        }
        
        function clearDisplay() {
            document.getElementById('display').value = '';
        }
        
        function deleteLast() {
            let display = document.getElementById('display');
            display.value = display.value.slice(0, -1);
        }
        
        function calculate() {
            try {
                let result = eval(document.getElementById('display').value);
                document.getElementById('display').value = result;
            } catch (e) {
                alert('Errore nel calcolo!');
            }
        }
    </script>
</body>
</html>
EOF

# Commit della nuova feature
git add projects/calculator.html
git commit -m "🧮 Add interactive calculator project

- Implement basic calculator functionality
- Add responsive grid layout for buttons
- Include error handling for calculations
- Demonstrate JavaScript DOM manipulation"
```

#### Passo 10: Configurazione Avanzata

**Aggiungi .gitignore:**
```bash
cat > .gitignore << 'EOF'
# Development files
.vscode/
.idea/
*.swp
*.swo

# OS generated files
.DS_Store
.DS_Store?
._*
Thumbs.db
ehthumbs.db

# Temporary files
*.tmp
*.cache
*.log

# Dependencies (if using package managers)
node_modules/
npm-debug.log*
EOF

git add .gitignore
git commit -m "🙈 Add gitignore for development environment

- Exclude IDE and editor files
- Ignore OS generated files
- Skip temporary and cache files
- Prepare for future dependency management"
```

**Aggiorna README:**
```markdown
# Il Mio Portfolio

## 🎯 Descrizione
Portfolio personale sviluppato come primo progetto Git, dimostrando competenze di version control e sviluppo web.

## 🚀 Features
- ✅ Design responsive
- ✅ Navigazione smooth scroll
- ✅ Calculator interattiva
- ✅ Struttura semantica HTML5
- ✅ CSS moderno con grid/flexbox

## 📁 Struttura Progetto
```
il-mio-portfolio/
├── index.html          # Homepage principale
├── css/
│   └── style.css       # Stili principali
├── js/
│   └── script.js       # Logica interattiva
├── images/             # Risorse multimediali
├── projects/           # Progetti dimostrativi
│   └── calculator.html # Calculator app
└── README.md           # Documentazione
```

## 🛠️ Tecnologie Utilizzate
- HTML5 (Semantic markup)
- CSS3 (Grid, Flexbox, Transitions)
- JavaScript (ES6+, DOM Manipulation)
- Git (Version Control)

## 📈 Cronologia Sviluppo
Questo progetto dimostra l'evoluzione incrementale tramite commit atomici:
1. **Setup iniziale** - Repository e README
2. **Struttura base** - HTML, CSS, JS foundation
3. **Feature aggiunta** - Calculator project
4. **Configurazione** - .gitignore e documentazione

## 🚀 Come Utilizzare
1. Clona il repository (quando sarà su GitHub)
2. Apri `index.html` nel browser
3. Naviga tra le sezioni
4. Prova la calculator in `projects/calculator.html`

## 📞 Contatti
- **Developer:** [Il Tuo Nome]
- **Email:** tuoemail@example.com
- **GitHub:** [username] (coming soon!)

## 🎖️ Achievement Unlocked
- 🏗️ Repository Creator
- 🏛️ Structure Master  
- 🧮 Feature Developer
- 📚 Documentation Expert

---
**Creato con ❤️ e Git** durante il corso "Git e GitHub by Example"
```

```bash
git add README.md
git commit -m "📚 Enhance README with comprehensive documentation

- Add project description and features list
- Include technology stack and structure overview
- Document development chronology with Git focus
- Add usage instructions and contact information
- Showcase achievement badges system"
```

**🎖️ Badge Ottenuto:** "Documentation Expert" 📚

## 🏆 Verifica Finale

### Comandi di Controllo
```bash
# Verifica la cronologia completa
git log --oneline --graph

# Conta i commit realizzati
git rev-list --count HEAD

# Mostra statistiche del repository
git shortlog -sn

# Verifica tutti i file tracciati
git ls-files

# Controlla lo stato finale
git status
```

### Criteri di Successo ✅

**Bronze Level (Minimo):**
- [x] Repository inizializzato correttamente
- [x] Almeno 1 commit realizzato
- [x] README.md presente

**Silver Level (Buono):**
- [x] Struttura di file organizzata
- [x] File HTML, CSS, JS funzionanti
- [x] Commit con messaggi descrittivi
- [x] Minimo 2-3 commit

**Gold Level (Eccellente):**
- [x] Progetto completo e funzionale
- [x] .gitignore configurato
- [x] README documentato completamente
- [x] Minimo 4-5 commit con logica progressiva
- [x] Utilizzo di convenzioni Git professionali

## 🎯 Risultati Attesi

Al completamento di questo esercizio dovresti avere:

1. **Repository funzionale** con portfolio completo
2. **Cronologia Git pulita** con commit significativi
3. **Comprensione pratica** del workflow Git base
4. **Confident con comandi fondamentali**: init, add, commit, status, log
5. **Best practices** per struttura progetto e messaggi commit

## 🔧 Troubleshooting

### Problema: Git non riconosce i comandi
```bash
# Verifica installazione
git --version

# Verifica configurazione
git config --list
```

### Problema: Commit fallisce
```bash
# Configura identità se non fatto
git config --global user.name "Tuo Nome"
git config --global user.email "tua@email.com"
```

### Problema: File non tracciato
```bash
# Verifica che il file esista
ls -la nomefile

# Aggiungi esplicitamente
git add nomefile

# Controlla .gitignore se il file è ignorato
git status --ignored
```

## 🚀 Sfide Extra

Se vuoi andare oltre:

1. **Aggiungi più progetti** nella cartella `projects/`
2. **Sperimenta con branch** (vedremo nei prossimi moduli)
3. **Modifica file esistenti** e osserva come Git traccia le differenze
4. **Prova comandi avanzati** come `git diff` e `git log -p`

## 📈 Prossimi Passi

Dopo aver completato questo esercizio:
1. Continua con gli esercizi 2 e 3 di questo modulo
2. Procedi al [Modulo 04: Comandi Base Git](../../04-Comandi-Base-Git/README.md)
3. Tieni questo repository come riferimento per i futuri moduli

## Navigazione del Corso
- [📑 Indice](../README.md)
- [📚 Guide Teoriche](../guide/README.md)
- [💡 Esempi](../esempi/README.md)
- [➡️ Esercizio Successivo](02-gestione-stati-file.md)
