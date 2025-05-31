# Esercizio 4: Progetto Pratico - Primo Repository

## 🎯 Obiettivi
- Applicare tutti i concetti appresi del controllo di versione
- Creare e gestire un repository Git reale
- Sperimentare con scenari di lavoro comuni
- Consolidare le competenze di base

## 📋 Scenario Progetto
Dovrai creare un **Portfolio Personale Web** che dimostri l'evoluzione delle tue competenze nel tempo. Questo progetto ti permetterà di praticare Git mentre costruisci qualcosa di utile per la tua carriera.

## 🚀 Fase 1: Setup Iniziale (30 minuti)

### Attività 1.1 - Creazione Repository
```bash
# 1. Crea la directory del progetto
mkdir mio-portfolio-web
cd mio-portfolio-web

# 2. Inizializza Git
git init

# 3. Configura le informazioni dell'autore (se non già fatto)
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"
```

### Attività 1.2 - Struttura Iniziale
Crea questa struttura di file:

```
mio-portfolio-web/
├── index.html
├── css/
│   └── style.css
├── js/
│   └── script.js
├── img/
│   └── .gitkeep
├── projects/
│   └── README.md
└── README.md
```

### Attività 1.3 - Contenuto Base
Crea il contenuto base per ogni file:

**index.html:**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Portfolio di [Tuo Nome]</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <header>
        <h1>Portfolio di [Tuo Nome]</h1>
        <nav>
            <a href="#about">Chi sono</a>
            <a href="#projects">Progetti</a>
            <a href="#contact">Contatti</a>
        </nav>
    </header>
    
    <main>
        <section id="about">
            <h2>Chi sono</h2>
            <p>Sono uno studente di informatica appassionato di sviluppo web.</p>
        </section>
        
        <section id="projects">
            <h2>I miei progetti</h2>
            <p>Progetti in arrivo...</p>
        </section>
        
        <section id="contact">
            <h2>Contatti</h2>
            <p>Email: [tua-email]</p>
        </section>
    </main>
    
    <script src="js/script.js"></script>
</body>
</html>
```

### Attività 1.4 - Primo Commit
```bash
# 1. Aggiungi tutti i file
git add .

# 2. Crea il primo commit
git commit -m "Initial commit: basic portfolio structure

- Added HTML structure
- Created CSS and JS directories
- Setup project folders
- Initial README"
```

## 🔄 Fase 2: Sviluppo Iterativo (60 minuti)

### Iterazione 1: Styling Base (15 minuti)

**css/style.css:**
```css
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
    background: #2c3e50;
    color: white;
    padding: 1rem;
}

nav a {
    color: white;
    text-decoration: none;
    margin-right: 1rem;
}

main {
    padding: 2rem;
    max-width: 800px;
    margin: 0 auto;
}

section {
    margin-bottom: 2rem;
}
```

**Commit 2:**
```bash
git add css/style.css
git commit -m "Add basic CSS styling

- Implemented basic layout
- Added header navigation styling
- Set up responsive container"
```

### Iterazione 2: Funzionalità JavaScript (15 minuti)

**js/script.js:**
```javascript
// Smooth scrolling for navigation
document.querySelectorAll('nav a').forEach(link => {
    link.addEventListener('click', function(e) {
        e.preventDefault();
        const targetId = this.getAttribute('href').substring(1);
        const targetSection = document.getElementById(targetId);
        targetSection.scrollIntoView({ behavior: 'smooth' });
    });
});

// Dynamic greeting based on time
function updateGreeting() {
    const hour = new Date().getHours();
    const greetingElement = document.querySelector('#about p');
    
    if (hour < 12) {
        greetingElement.textContent = "Buongiorno! Sono uno studente di informatica appassionato di sviluppo web.";
    } else if (hour < 18) {
        greetingElement.textContent = "Buonpomeriggio! Sono uno studente di informatica appassionato di sviluppo web.";
    } else {
        greetingElement.textContent = "Buonasera! Sono uno studente di informatica appassionato di sviluppo web.";
    }
}

window.addEventListener('load', updateGreeting);
```

**Commit 3:**
```bash
git add js/script.js
git commit -m "Add interactive JavaScript features

- Implemented smooth scrolling navigation
- Added dynamic greeting based on time of day
- Enhanced user experience"
```

### Iterazione 3: Contenuto Progetti (15 minuti)

**projects/README.md:**
```markdown
# I Miei Progetti

## 🚀 Progetti Attuali

### 1. Portfolio Personale
- **Descrizione**: Sito web responsive per presentare le mie competenze
- **Tecnologie**: HTML5, CSS3, JavaScript
- **Status**: In sviluppo
- **Repo**: Questo repository

## 📅 Progetti Futuri

### 2. App Todo List
- **Descrizione**: Applicazione per gestire attività quotidiane
- **Tecnologie**: React, Local Storage
- **Status**: Pianificato

### 3. Blog Personale
- **Descrizione**: Blog tecnico su sviluppo e tecnologia
- **Tecnologie**: Jekyll, GitHub Pages
- **Status**: Idea

## 🎯 Obiettivi di Apprendimento

- [ ] HTML semantico avanzato
- [ ] CSS Grid e Flexbox
- [ ] JavaScript ES6+
- [ ] Framework moderni (React/Vue)
- [ ] Git workflow professionali
- [ ] Testing automatizzato
```

**Aggiorna index.html** (sezione progetti):
```html
<section id="projects">
    <h2>I miei progetti</h2>
    <div class="project">
        <h3>Portfolio Personale</h3>
        <p>Sito web responsive per presentare le mie competenze</p>
        <p><strong>Tecnologie:</strong> HTML5, CSS3, JavaScript</p>
    </div>
</section>
```

**Commit 4:**
```bash
git add .
git commit -m "Add projects content and documentation

- Created projects README with roadmap
- Updated portfolio projects section
- Added learning objectives"
```

### Iterazione 4: Miglioramenti UX (15 minuti)

**Aggiungi a css/style.css:**
```css
.project {
    background: #f8f9fa;
    padding: 1rem;
    border-radius: 5px;
    margin-bottom: 1rem;
    border-left: 4px solid #2c3e50;
}

.project h3 {
    color: #2c3e50;
    margin-bottom: 0.5rem;
}

nav a:hover {
    text-decoration: underline;
}

@media (max-width: 768px) {
    header {
        text-align: center;
    }
    
    nav a {
        display: block;
        margin: 0.5rem 0;
    }
}
```

**Commit 5:**
```bash
git add css/style.css
git commit -m "Improve UI/UX and responsiveness

- Added project card styling
- Implemented hover effects
- Added mobile responsive design"
```

## 🔍 Fase 3: Simulazione Problemi e Soluzioni (30 minuti)

### Scenario 1: Errore Critico
```bash
# Simula un errore: sovrascrivi index.html con contenuto sbagliato
echo "ERRORE: File corrotto!" > index.html

# Ora ripristina la versione precedente
git checkout HEAD -- index.html

# Verifica che il file sia stato ripristinato
cat index.html
```

### Scenario 2: Modifiche Parziali
```bash
# Modifica multipli file
echo "Footer test" >> index.html
echo "/* Test comment */" >> css/style.css

# Aggiungi solo una modifica specifica
git add index.html
git commit -m "Add footer placeholder"

# Scarta le altre modifiche
git checkout -- css/style.css
```

### Scenario 3: Analisi Storia
```bash
# Visualizza la storia completa
git log --oneline --graph

# Mostra le modifiche di un commit specifico
git show <commit-hash>

# Trova chi ha modificato cosa
git blame index.html
```

## 📊 Fase 4: Analisi e Documentazione (30 minuti)

### Attività 4.1 - Documentazione Finale
Aggiorna il **README.md** principale:

```markdown
# Portfolio Personale - Progetto Git

## 📝 Descrizione
Portfolio web personale sviluppato per praticare Git e le tecnologie web moderne.

## 🚀 Tecnologie Utilizzate
- HTML5 semantico
- CSS3 con responsive design
- JavaScript vanilla (ES6+)
- Git per version control

## 📂 Struttura Progetto
```
mio-portfolio-web/
├── index.html          # Pagina principale
├── css/style.css       # Styling responsive
├── js/script.js        # Interattività
├── projects/README.md  # Documentazione progetti
└── README.md          # Questo file
```

## 🎯 Funzionalità
- ✅ Design responsive
- ✅ Navigazione smooth scroll
- ✅ Saluto dinamico
- ✅ Sezione progetti
- ✅ Layout professionale

## 📈 Cronologia Sviluppo
Puoi vedere l'evoluzione del progetto attraverso i commit Git:
```bash
git log --oneline --graph
```

## 🔄 Come Contribuire
1. Fork del repository
2. Crea branch feature (`git checkout -b feature/nuova-funzione`)
3. Commit modifiche (`git commit -m 'Aggiungi nuova funzione'`)
4. Push al branch (`git push origin feature/nuova-funzione`)
5. Apri Pull Request

## 📞 Contatti
- Email: [tua-email]
- GitHub: [tuo-username]
```

### Attività 4.2 - Commit Finale
```bash
git add README.md
git commit -m "Complete project documentation

- Added comprehensive README
- Documented project structure
- Included contribution guidelines
- Added development timeline"
```

## 🏆 Deliverables Finali

### 1. Repository Completo
- ✅ Almeno 6 commit significativi
- ✅ Struttura progetti organizzata
- ✅ Documentazione completa
- ✅ Codice funzionante

### 2. Report Esperienza (300 parole)
Scrivi un breve report che includa:
- Cosa hai imparato usando Git
- Difficoltà incontrate e come le hai risolte
- Come Git ha aiutato nella gestione del progetto
- Prossimi passi per migliorare il workflow

### 3. Presentazione Progetto (5 minuti)
Prepara una demo che mostri:
- Evoluzione del progetto attraverso i commit
- Funzionalità del sito web
- Come Git ha facilitato lo sviluppo
- Lezioni apprese

## 📚 Estensioni Opzionali

### Livello Avanzato
- [ ] Aggiungi file `.gitignore` appropriato
- [ ] Crea branch per nuove feature
- [ ] Implementa workflow con merge
- [ ] Aggiungi tag per versioni
- [ ] Setup GitHub Pages per hosting

### Livello Esperto
- [ ] Integra con GitHub Actions
- [ ] Aggiungi testing automatizzato
- [ ] Implementa semantic versioning
- [ ] Crea script di deployment
- [ ] Setup continuous integration

## 🎯 Criteri di Valutazione

- **Qualità commit** (30%): Messaggi chiari e atomic commits
- **Struttura progetto** (25%): Organizzazione logica e pulita
- **Funzionalità** (25%): Sito web funzionante e responsive
- **Documentazione** (20%): README e commenti chiari

---

**Tempo stimato:** 2-3 ore  
**Difficoltà:** ⭐⭐⭐  
**Prerequisiti:** Conoscenza base HTML/CSS/JS  
**Tag:** #pratico #portfolio #git #web-development
