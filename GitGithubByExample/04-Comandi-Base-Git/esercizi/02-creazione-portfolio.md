# Esercizio 02: Creazione Portfolio Personale con Git

## 🎯 Obiettivi
- Applicare i comandi Git fondamentali in un progetto reale
- Creare e gestire un portfolio personale dal design all'implementazione
- Praticare workflow di sviluppo professionale con Git
- Implementare best practices per commit e staging

## 📋 Prerequisiti
- Conoscenza dei comandi base Git (status, add, commit, log, diff)
- Editor di codice installato (VS Code, Sublime Text, etc.)
- Comprensione delle tre aree di Git

## 🛠️ Scenario
Sei uno sviluppatore che deve creare il proprio portfolio personale. Il progetto includerà:
- Sito web HTML/CSS/JavaScript
- Sezione progetti
- CV/Resume scaricabile
- Form di contatto
- Documentazione del progetto

## 📁 Struttura del Progetto
```
portfolio/
├── index.html
├── css/
│   ├── style.css
│   └── responsive.css
├── js/
│   ├── main.js
│   └── animations.js
├── images/
│   ├── profile.jpg
│   └── projects/
├── assets/
│   └── cv.pdf
├── projects/
│   ├── project1.html
│   └── project2.html
├── README.md
└── .gitignore
```

## 🚀 Istruzioni Passo-Passo

### Fase 1: Setup Iniziale del Repository

1. **Crea la directory del progetto**
```bash
mkdir portfolio-git-exercise
cd portfolio-git-exercise
```

2. **Inizializza il repository Git**
```bash
git init
```

3. **Configura Git per il progetto (se necessario)**
```bash
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"
```

4. **Verifica lo stato iniziale**
```bash
git status
```

### Fase 2: Creazione della Struttura Base

5. **Crea le directory principali**
```bash
mkdir css js images assets projects
mkdir images/projects
```

6. **Crea il file index.html**
```html
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
        <nav>
            <h1>Il Mio Portfolio</h1>
            <ul>
                <li><a href="#home">Home</a></li>
                <li><a href="#projects">Progetti</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <section id="home">
            <h2>Benvenuto nel mio Portfolio</h2>
            <p>Sono uno sviluppatore appassionato di tecnologie web.</p>
        </section>
    </main>
    
    <script src="js/main.js"></script>
</body>
</html>
```

7. **Verifica i file non tracciati**
```bash
git status
```

8. **Aggiungi la struttura base**
```bash
git add index.html
git add css/ js/ images/ assets/ projects/
```

9. **Primo commit della struttura**
```bash
git commit -m "feat: add initial project structure

- Add HTML skeleton with navigation
- Create directory structure for assets
- Setup basic semantic HTML layout"
```

### Fase 3: Sviluppo del CSS

10. **Crea il file CSS principale**
```css
/* css/style.css */
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
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 1rem 0;
    position: fixed;
    width: 100%;
    top: 0;
    z-index: 1000;
}

nav {
    display: flex;
    justify-content: space-between;
    align-items: center;
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 2rem;
}

nav ul {
    display: flex;
    list-style: none;
}

nav ul li {
    margin-left: 2rem;
}

nav ul li a {
    color: white;
    text-decoration: none;
    transition: opacity 0.3s;
}

nav ul li a:hover {
    opacity: 0.8;
}

main {
    margin-top: 80px;
    padding: 2rem;
}

#home {
    text-align: center;
    padding: 4rem 0;
}

#home h2 {
    font-size: 3rem;
    margin-bottom: 1rem;
    color: #667eea;
}

#home p {
    font-size: 1.2rem;
    max-width: 600px;
    margin: 0 auto;
}
```

11. **Verifica le modifiche**
```bash
git status
git diff css/style.css
```

12. **Commit del CSS base**
```bash
git add css/style.css
git commit -m "style: add basic CSS styling

- Implement responsive navigation header
- Add gradient background and typography
- Setup modern color scheme
- Add hover effects for navigation"
```

### Fase 4: Aggiunta del JavaScript

13. **Crea il file JavaScript principale**
```javascript
// js/main.js
document.addEventListener('DOMContentLoaded', function() {
    // Smooth scrolling per i link di navigazione
    const navLinks = document.querySelectorAll('nav a[href^="#"]');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const targetId = this.getAttribute('href');
            const targetSection = document.querySelector(targetId);
            
            if (targetSection) {
                targetSection.scrollIntoView({
                    behavior: 'smooth'
                });
            }
        });
    });
    
    // Header scroll effect
    window.addEventListener('scroll', function() {
        const header = document.querySelector('header');
        if (window.scrollY > 100) {
            header.style.background = 'rgba(102, 126, 234, 0.95)';
        } else {
            header.style.background = 'linear-gradient(135deg, #667eea 0%, #764ba2 100%)';
        }
    });
    
    console.log('Portfolio loaded successfully!');
});
```

14. **Testa le modifiche e committa**
```bash
git status
git add js/main.js
git commit -m "feat: add interactive JavaScript functionality

- Implement smooth scrolling navigation
- Add header transparency effect on scroll
- Setup DOM content loaded event handling
- Add console logging for debugging"
```

### Fase 5: Espansione del Contenuto

15. **Espandi l'HTML con più sezioni**
```html
<!-- Aggiungi alla fine del main prima dello script -->
<section id="projects">
    <h2>I Miei Progetti</h2>
    <div class="project-grid">
        <div class="project-card">
            <h3>E-commerce Website</h3>
            <p>Sito di e-commerce sviluppato con HTML, CSS e JavaScript</p>
            <a href="projects/project1.html">Dettagli</a>
        </div>
        <div class="project-card">
            <h3>Weather App</h3>
            <p>Applicazione meteo con API integration</p>
            <a href="projects/project2.html">Dettagli</a>
        </div>
    </div>
</section>

<section id="contact">
    <h2>Contattami</h2>
    <form id="contact-form">
        <input type="text" placeholder="Nome" required>
        <input type="email" placeholder="Email" required>
        <textarea placeholder="Messaggio" required></textarea>
        <button type="submit">Invia Messaggio</button>
    </form>
</section>

<footer>
    <p>&copy; 2024 Il Mio Portfolio. Tutti i diritti riservati.</p>
</footer>
```

16. **Aggiungi CSS per le nuove sezioni**
```css
/* Aggiungi al file css/style.css */
.project-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
    margin-top: 2rem;
}

.project-card {
    background: white;
    padding: 2rem;
    border-radius: 10px;
    box-shadow: 0 5px 15px rgba(0,0,0,0.1);
    transition: transform 0.3s;
}

.project-card:hover {
    transform: translateY(-5px);
}

#contact {
    background: #f8f9fa;
    padding: 4rem 2rem;
    margin-top: 4rem;
}

#contact form {
    max-width: 600px;
    margin: 0 auto;
}

#contact input,
#contact textarea {
    width: 100%;
    padding: 1rem;
    margin-bottom: 1rem;
    border: 1px solid #ddd;
    border-radius: 5px;
}

#contact button {
    background: #667eea;
    color: white;
    padding: 1rem 2rem;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    transition: background 0.3s;
}

#contact button:hover {
    background: #5a6fd8;
}

footer {
    background: #333;
    color: white;
    text-align: center;
    padding: 2rem;
}
```

17. **Verifica le modifiche con git diff**
```bash
git diff index.html
git diff css/style.css
```

18. **Staging selettivo**
```bash
git add index.html
git add css/style.css
```

19. **Commit delle nuove feature**
```bash
git commit -m "feat: add projects and contact sections

- Add responsive project grid layout
- Implement contact form with validation
- Add footer with copyright information
- Enhance CSS with card hover effects
- Improve overall page structure"
```

### Fase 6: Aggiunta della Documentazione

20. **Crea il README.md**
```markdown
# Portfolio Personale

Un portfolio moderno e responsivo realizzato con HTML, CSS e JavaScript vanilla.

## Caratteristiche

- Design moderno e professionale
- Navigazione smooth scroll
- Sezione progetti interattiva
- Form di contatto funzionale
- Layout completamente responsivo

## Tecnologie Utilizzate

- HTML5 semantico
- CSS3 con Flexbox e Grid
- JavaScript ES6+
- Responsive Design

## Struttura del Progetto

```
portfolio/
├── index.html          # Pagina principale
├── css/
│   ├── style.css      # Stili principali
│   └── responsive.css # Media queries
├── js/
│   └── main.js        # Logica JavaScript
├── images/            # Immagini del sito
├── projects/          # Pagine dei progetti
└── assets/           # Asset scaricabili

## Come Contribuire

1. Fork del repository
2. Crea un branch per la tua feature
3. Commit delle modifiche
4. Push al branch
5. Apri una Pull Request

## Licenza

Questo progetto è rilasciato sotto licenza MIT.
```

21. **Crea il .gitignore**
```gitignore
# File di sistema
.DS_Store
Thumbs.db

# Cartelle temporanee
temp/
tmp/

# File di log
*.log

# Dipendenze (se aggiunte in futuro)
node_modules/

# File dell'editor
.vscode/
.idea/

# File di backup
*.bak
*.swp
```

22. **Aggiungi documentazione**
```bash
git add README.md .gitignore
git commit -m "docs: add project documentation and gitignore

- Add comprehensive README with project overview
- Include technology stack and contribution guidelines
- Setup gitignore for common development files
- Document project structure and features"
```

### Fase 7: Verifica e Ottimizzazione

23. **Visualizza la cronologia completa**
```bash
git log --oneline --graph
```

24. **Verifica lo stato finale**
```bash
git status
```

25. **Aggiungi file CSS responsivo**
```css
/* css/responsive.css */
@media (max-width: 768px) {
    nav {
        flex-direction: column;
        padding: 1rem;
    }
    
    nav ul {
        margin-top: 1rem;
    }
    
    nav ul li {
        margin: 0 1rem;
    }
    
    #home h2 {
        font-size: 2rem;
    }
    
    .project-grid {
        grid-template-columns: 1fr;
    }
    
    main {
        padding: 1rem;
    }
}

@media (max-width: 480px) {
    #home h2 {
        font-size: 1.5rem;
    }
    
    nav ul {
        flex-direction: column;
        text-align: center;
    }
    
    nav ul li {
        margin: 0.5rem 0;
    }
}
```

26. **Aggiungi il link al CSS responsivo nell'HTML**
```html
<!-- Nel <head> dopo style.css -->
<link rel="stylesheet" href="css/responsive.css">
```

27. **Commit finale**
```bash
git add css/responsive.css index.html
git commit -m "feat: add responsive design for mobile devices

- Implement mobile-first responsive CSS
- Add media queries for tablet and mobile
- Optimize navigation for small screens
- Ensure proper mobile typography scaling"
```

## ✅ Verifica Finale

### Checklist Completamento:
- [ ] Repository Git inizializzato correttamente
- [ ] Struttura di cartelle organizzata
- [ ] File HTML con contenuto semantico
- [ ] CSS moderno con Flexbox/Grid
- [ ] JavaScript interattivo funzionante
- [ ] Design responsivo implementato
- [ ] Documentazione README completa
- [ ] File .gitignore configurato
- [ ] Cronologia commit pulita e professionale
- [ ] Messaggi commit seguono convention standard

### Comandi di Verifica:
```bash
# Verifica struttura repository
find . -type f -name "*.html" -o -name "*.css" -o -name "*.js" -o -name "*.md"

# Conta totale commit
git rev-list --count HEAD

# Visualizza statistiche del progetto
git log --stat

# Verifica l'ultimo commit
git show --stat
```

## 🏆 Obiettivi Raggiunti

1. **Workflow Git Professionale**: Hai applicato un flusso di lavoro Git realistico
2. **Staging Strategico**: Hai utilizzato staging selettivo per commit logici
3. **Commit Semantici**: Hai scritto messaggi commit chiari e informativi
4. **Gestione Progetto**: Hai organizzato file e cartelle in modo professionale
5. **Documentazione**: Hai creato documentazione di qualità

## 🎯 Bonus Challenge

### Challenge Avanzato:
1. **Aggiungi animazioni CSS**: Implementa transizioni e keyframe animations
2. **JavaScript avanzato**: Aggiungi validazione form lato client
3. **Ottimizzazione**: Implementa lazy loading per le immagini
4. **SEO**: Aggiungi meta tag e structured data
5. **Performance**: Minimizza CSS e JavaScript

### Git Avanzato:
1. **Branch feature**: Crea branch separati per ogni feature
2. **Merge strategico**: Pratica diversi tipi di merge
3. **Tag versioni**: Aggiungi tag per le versioni del portfolio
4. **Hooks Git**: Implementa pre-commit hooks per code quality

## 📚 Risorse Aggiuntive

- [MDN Web Docs](https://developer.mozilla.org/)
- [CSS Grid Guide](https://css-tricks.com/snippets/css/complete-guide-grid/)
- [JavaScript ES6 Features](https://es6-features.org/)
- [Git Best Practices](https://git-scm.com/book/en/v2)

## 🔄 Estensioni Future

Questo portfolio può essere esteso con:
- Framework CSS (Bootstrap, Tailwind)
- Build tools (Webpack, Vite)
- Preprocessing CSS (Sass, Less)
- Testing automatizzato
- Deploy automatico con GitHub Pages
- Integrazione CI/CD

---

**Tempo stimato**: 2-3 ore  
**Difficoltà**: Intermedio  
**Competenze acquisite**: Git workflow, HTML/CSS/JS, Project management
