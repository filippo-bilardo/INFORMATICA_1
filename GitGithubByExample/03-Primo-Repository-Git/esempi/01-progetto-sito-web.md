# 🌐 Esempio Pratico: Progetto Sito Web

## 📋 Scenario

Sei uno sviluppatore web che deve creare un portfolio personale. Parti da zero e vuoi utilizzare Git fin dall'inizio per tracciare ogni modifica. Questo esempio ti guiderà attraverso la creazione completa del primo repository Git per un progetto web.

---

## 🎯 Obiettivi

- ✅ Creare repository Git per progetto web
- ✅ Strutturare file HTML, CSS e JavaScript
- ✅ Implementare workflow Git corretto
- ✅ Gestire file statici e risorse
- ✅ Preparare per future collaborazioni

---

## 🚀 Setup Iniziale

### 1. **📁 Creazione della Struttura Progetto**

```bash
# Creare directory principale
mkdir portfolio-personale
cd portfolio-personale

# Inizializzare repository Git
git init
echo "✅ Repository Git inizializzato"

# Verificare stato iniziale
git status
```

**Output atteso:**
```
Initialized empty Git repository in /home/user/portfolio-personale/.git/
On branch main

No commits yet

nothing to commit (create/copy files and use "git add" to track)
```

### 2. **🏗️ Struttura Directory del Progetto**

```bash
# Creare struttura cartelle
mkdir -p assets/{css,js,images}
mkdir -p pages
touch index.html
touch assets/css/style.css
touch assets/js/main.js

# Visualizzare struttura creata
tree . 2>/dev/null || find . -type f
```

**Struttura risultante:**
```
portfolio-personale/
├── index.html
├── assets/
│   ├── css/
│   │   └── style.css
│   ├── js/
│   │   └── main.js
│   └── images/
└── pages/
```

---

## 📝 Creazione dei File Base

### 3. **🌐 File HTML Principale**

```bash
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="Portfolio di Mario Rossi - Sviluppatore Web">
    <title>Mario Rossi | Portfolio Sviluppatore Web</title>
    <link rel="stylesheet" href="assets/css/style.css">
</head>
<body>
    <header>
        <nav>
            <div class="logo">
                <h1>Mario Rossi</h1>
            </div>
            <ul class="nav-links">
                <li><a href="#home">Home</a></li>
                <li><a href="#about">Chi Sono</a></li>
                <li><a href="#projects">Progetti</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <section id="home" class="hero">
            <div class="hero-content">
                <h2>Ciao, sono Mario</h2>
                <p>Sviluppatore Web Full-Stack appassionato di tecnologie moderne</p>
                <button class="cta-button">Scopri i miei progetti</button>
            </div>
        </section>

        <section id="about" class="about">
            <h2>Chi Sono</h2>
            <p>Sviluppatore con 3 anni di esperienza in JavaScript, React, Node.js e database.</p>
        </section>

        <section id="projects" class="projects">
            <h2>I Miei Progetti</h2>
            <div class="project-grid">
                <!-- I progetti saranno aggiunti dinamicamente -->
            </div>
        </section>

        <section id="contact" class="contact">
            <h2>Contattami</h2>
            <p>Email: mario.rossi@example.com</p>
            <p>LinkedIn: linkedin.com/in/mario-rossi</p>
        </section>
    </main>

    <footer>
        <p>&copy; 2024 Mario Rossi. Tutti i diritti riservati.</p>
    </footer>

    <script src="assets/js/main.js"></script>
</body>
</html>
EOF

echo "✅ File index.html creato"
```

### 4. **🎨 Stylesheet CSS**

```bash
cat > assets/css/style.css << 'EOF'
/* Reset CSS e variabili */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

:root {
    --primary-color: #2c3e50;
    --secondary-color: #3498db;
    --accent-color: #e74c3c;
    --text-color: #333;
    --bg-color: #f8f9fa;
    --white: #ffffff;
}

/* Typography */
body {
    font-family: 'Arial', sans-serif;
    line-height: 1.6;
    color: var(--text-color);
    background-color: var(--bg-color);
}

/* Header e Navigation */
header {
    background: var(--white);
    box-shadow: 0 2px 5px rgba(0,0,0,0.1);
    position: fixed;
    width: 100%;
    top: 0;
    z-index: 1000;
}

nav {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 1rem 5%;
    max-width: 1200px;
    margin: 0 auto;
}

.logo h1 {
    color: var(--primary-color);
    font-size: 1.5rem;
}

.nav-links {
    display: flex;
    list-style: none;
    gap: 2rem;
}

.nav-links a {
    text-decoration: none;
    color: var(--text-color);
    transition: color 0.3s ease;
}

.nav-links a:hover {
    color: var(--secondary-color);
}

/* Main Content */
main {
    margin-top: 70px;
}

section {
    padding: 4rem 5%;
    max-width: 1200px;
    margin: 0 auto;
}

/* Hero Section */
.hero {
    background: linear-gradient(135deg, var(--primary-color), var(--secondary-color));
    color: var(--white);
    text-align: center;
    min-height: 80vh;
    display: flex;
    align-items: center;
    justify-content: center;
}

.hero-content h2 {
    font-size: 3rem;
    margin-bottom: 1rem;
}

.hero-content p {
    font-size: 1.2rem;
    margin-bottom: 2rem;
}

.cta-button {
    background: var(--accent-color);
    color: var(--white);
    border: none;
    padding: 1rem 2rem;
    font-size: 1.1rem;
    border-radius: 5px;
    cursor: pointer;
    transition: transform 0.3s ease;
}

.cta-button:hover {
    transform: translateY(-2px);
}

/* Sections */
.about, .projects, .contact {
    text-align: center;
}

.about h2, .projects h2, .contact h2 {
    color: var(--primary-color);
    margin-bottom: 2rem;
    font-size: 2.5rem;
}

.project-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
    margin-top: 2rem;
}

/* Footer */
footer {
    background: var(--primary-color);
    color: var(--white);
    text-align: center;
    padding: 2rem;
}

/* Responsive Design */
@media (max-width: 768px) {
    .nav-links {
        gap: 1rem;
    }
    
    .hero-content h2 {
        font-size: 2rem;
    }
    
    nav {
        flex-direction: column;
        gap: 1rem;
    }
}
EOF

echo "✅ File style.css creato"
```

### 5. **⚡ JavaScript Funzionalità**

```bash
cat > assets/js/main.js << 'EOF'
// Portfolio JavaScript Functionality
document.addEventListener('DOMContentLoaded', function() {
    console.log('Portfolio loaded successfully!');
    
    // Smooth scrolling per navigation links
    initSmoothScrolling();
    
    // Animazioni on scroll
    initScrollAnimations();
    
    // Dynamic project loading
    loadProjects();
    
    // Contact form handling (se presente)
    initContactForm();
});

/**
 * Smooth scrolling per i link di navigazione
 */
function initSmoothScrolling() {
    const navLinks = document.querySelectorAll('.nav-links a[href^="#"]');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href').substring(1);
            const targetElement = document.getElementById(targetId);
            
            if (targetElement) {
                targetElement.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });
}

/**
 * Animazioni quando elementi entrano nel viewport
 */
function initScrollAnimations() {
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -50px 0px'
    };
    
    const observer = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, observerOptions);
    
    // Osserva tutte le sezioni
    document.querySelectorAll('section').forEach(section => {
        section.style.opacity = '0';
        section.style.transform = 'translateY(20px)';
        section.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        observer.observe(section);
    });
}

/**
 * Carica progetti dinamicamente
 */
function loadProjects() {
    const projectGrid = document.querySelector('.project-grid');
    
    const projects = [
        {
            title: 'E-commerce Platform',
            description: 'Piattaforma e-commerce completa con React e Node.js',
            tech: ['React', 'Node.js', 'MongoDB'],
            github: 'https://github.com/user/ecommerce',
            live: 'https://myecommerce.com'
        },
        {
            title: 'Task Manager App',
            description: 'Applicazione per gestione tasks con autenticazione',
            tech: ['Vue.js', 'Express', 'PostgreSQL'],
            github: 'https://github.com/user/taskmanager',
            live: 'https://mytasks.com'
        },
        {
            title: 'Weather Dashboard',
            description: 'Dashboard meteo con API integration',
            tech: ['JavaScript', 'API', 'Charts.js'],
            github: 'https://github.com/user/weather',
            live: 'https://myweather.com'
        }
    ];
    
    projects.forEach(project => {
        const projectCard = createProjectCard(project);
        projectGrid.appendChild(projectCard);
    });
}

/**
 * Crea card per singolo progetto
 */
function createProjectCard(project) {
    const card = document.createElement('div');
    card.className = 'project-card';
    
    card.innerHTML = `
        <h3>${project.title}</h3>
        <p>${project.description}</p>
        <div class="tech-stack">
            ${project.tech.map(tech => `<span class="tech-tag">${tech}</span>`).join('')}
        </div>
        <div class="project-links">
            <a href="${project.github}" target="_blank">GitHub</a>
            <a href="${project.live}" target="_blank">Live Demo</a>
        </div>
    `;
    
    return card;
}

/**
 * Gestione form contatti (placeholder)
 */
function initContactForm() {
    const contactButton = document.querySelector('.cta-button');
    
    if (contactButton) {
        contactButton.addEventListener('click', function() {
            // Scroll verso sezione contatti
            document.getElementById('contact').scrollIntoView({
                behavior: 'smooth'
            });
        });
    }
}

// Utility functions
const Utils = {
    // Debounce function per performance
    debounce: function(func, wait) {
        let timeout;
        return function executedFunction(...args) {
            const later = () => {
                clearTimeout(timeout);
                func(...args);
            };
            clearTimeout(timeout);
            timeout = setTimeout(later, wait);
        };
    },
    
    // Check se elemento è visible
    isElementVisible: function(element) {
        const rect = element.getBoundingClientRect();
        return rect.top < window.innerHeight && rect.bottom > 0;
    }
};
EOF

echo "✅ File main.js creato"
```

---

## 📄 File di Configurazione

### 6. **🚫 File .gitignore**

```bash
cat > .gitignore << 'EOF'
# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# IDE files
.vscode/
.idea/
*.swp
*.swo
*~

# Temporary files
*.tmp
*.temp
*.log

# Node.js (se usato per build tools)
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Build outputs
dist/
build/
.cache/

# Environment files
.env
.env.local
.env.production

# Backup files
*.backup
*.bak

# Compressed files (se non necessari)
*.zip
*.tar.gz
*.rar

# Image thumbnails
*.thumbnail.*

# Local server files
.htaccess
.htpasswd
EOF

echo "✅ File .gitignore creato"
```

### 7. **📚 Documentation README.md**

```bash
cat > README.md << 'EOF'
# 🌐 Portfolio Personale - Mario Rossi

Portfolio professionale di Mario Rossi, sviluppatore web full-stack specializzato in tecnologie moderne.

## 🚀 Caratteristiche

- ✅ Design responsive e moderno
- ⚡ Performance ottimizzate
- 🎨 Animazioni smooth
- 📱 Mobile-first approach
- 🔧 Codice pulito e mantenibile

## 🛠️ Tecnologie Utilizzate

- **Frontend**: HTML5, CSS3, JavaScript ES6+
- **Styling**: CSS Custom Properties, Flexbox, Grid
- **Performance**: Intersection Observer API
- **Tools**: Git per version control

## 📁 Struttura Progetto

```
portfolio-personale/
├── index.html              # Pagina principale
├── assets/
│   ├── css/
│   │   └── style.css       # Stili principali
│   ├── js/
│   │   └── main.js         # Funzionalità JavaScript
│   └── images/             # Risorse immagini
├── pages/                  # Pagine aggiuntive (future)
├── .gitignore             # File Git ignore
└── README.md              # Documentazione
```

## 🎯 Funzionalità

### Navigazione
- Smooth scrolling tra sezioni
- Navigation bar fissa
- Menu responsive

### Sezioni
- **Hero**: Introduzione e call-to-action
- **About**: Presentazione personale
- **Projects**: Portfolio progetti
- **Contact**: Informazioni contatto

### Animazioni
- Fade-in on scroll
- Hover effects
- Smooth transitions

## 🚀 Come Utilizzare

1. **Clone del repository**
```bash
git clone https://github.com/username/portfolio-personale.git
cd portfolio-personale
```

2. **Apertura in browser**
```bash
# Aprire index.html nel browser
open index.html  # macOS
start index.html # Windows
xdg-open index.html # Linux
```

3. **Live Server (opzionale)**
```bash
# Con Live Server VS Code extension
# Oppure con Python
python -m http.server 8000
# Aprire http://localhost:8000
```

## 🔧 Personalizzazione

### Colori
Modifica le CSS custom properties in `style.css`:
```css
:root {
    --primary-color: #2c3e50;
    --secondary-color: #3498db;
    --accent-color: #e74c3c;
}
```

### Contenuti
- Modifica i testi in `index.html`
- Aggiorna progetti in `main.js` nell'array `projects`
- Sostituisci immagini nella cartella `assets/images/`

### Aggiungere Pagine
Crea nuovi file HTML nella cartella `pages/` e aggiorna la navigazione.

## 📱 Browser Support

- ✅ Chrome (60+)
- ✅ Firefox (55+)
- ✅ Safari (12+)
- ✅ Edge (79+)

## 🤝 Contribuire

1. Fork del progetto
2. Crea feature branch (`git checkout -b feature/nuova-funzionalita`)
3. Commit delle modifiche (`git commit -m 'Add: nuova funzionalità'`)
4. Push del branch (`git push origin feature/nuova-funzionalita`)
5. Apri Pull Request

## 📄 Licenza

Questo progetto è licenziato sotto la Licenza MIT - vedi file [LICENSE](LICENSE) per dettagli.

## 📞 Contatti

- **Email**: mario.rossi@example.com
- **LinkedIn**: [linkedin.com/in/mario-rossi](https://linkedin.com/in/mario-rossi)
- **GitHub**: [github.com/mario-rossi](https://github.com/mario-rossi)
- **Portfolio**: [mario-rossi.dev](https://mario-rossi.dev)

---

⭐ Se questo progetto ti è stato utile, lascia una stella!
EOF

echo "✅ File README.md creato"
```

---

## 📋 Processo Git Completo

### 8. **🔍 Verifica dello Stato**

```bash
# Verificare tutti i file creati
git status

echo "
📊 STATUS ANALYSIS:"
echo "Files untracked: $(git status --porcelain | grep '^??' | wc -l)"
echo "Total files created: $(find . -type f -not -path './.git/*' | wc -l)"
```

**Output atteso:**
```
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
    .gitignore
    README.md
    assets/
    index.html

nothing added to commit but untracked files present
```

### 9. **📋 Staging dei File**

```bash
# Aggiungere file uno per uno per controllo
echo "📁 Aggiungendo file al staging..."

git add README.md
echo "✅ README.md staged"

git add .gitignore  
echo "✅ .gitignore staged"

git add index.html
echo "✅ index.html staged"

git add assets/
echo "✅ assets/ directory staged"

# Verificare staging
git status --short
```

### 10. **💾 Primo Commit**

```bash
# Commit iniziale strutturato
git commit -m "Initial commit: setup portfolio web completo

Struttura iniziale del portfolio personale con:

🌐 Frontend:
- index.html con struttura semantic HTML5
- style.css con design responsive e CSS Grid/Flexbox
- main.js con smooth scrolling e animazioni

📁 Assets:
- Struttura organizzata css/js/images
- CSS con custom properties per temi
- JavaScript modulare con utilities

📚 Documentation:
- README.md completo con setup e usage
- .gitignore configurato per web development

🎯 Features:
- Design mobile-first responsive
- Smooth scrolling navigation
- Dynamic project loading
- Intersection Observer animations
- Cross-browser compatibility

Ready for development and deployment!"

echo "
🎉 PRIMO COMMIT COMPLETATO!"
echo "Repository: $(pwd)"
echo "Commit SHA: $(git rev-parse HEAD | cut -c1-8)"
echo "Files committed: $(git show --name-only --format= | wc -l)"
```

### 11. **✅ Verifica Finale**

```bash
# Log del commit
echo "
📋 COMMIT LOG:"
git log --oneline --decorate

echo "
📊 REPOSITORY STATS:"
git show --stat

echo "
🗂️ FILE TREE:"
git ls-tree -r --name-only HEAD

echo "
🎯 NEXT STEPS:"
echo "1. Test nel browser: open index.html"
echo "2. Setup remote: git remote add origin <url>"
echo "3. First push: git push -u origin main"
echo "4. Continue development con feature branches"
```

---

## 🎯 Testing e Validazione

### 12. **🌐 Test nel Browser**

```bash
# Aprire il portfolio nel browser
if command -v python3 &> /dev/null; then
    echo "🚀 Starting local server..."
    echo "Portfolio available at: http://localhost:8000"
    echo "Press Ctrl+C to stop"
    python3 -m http.server 8000
else
    echo "📝 Open index.html in your browser to test"
    echo "Or install a local server for better testing"
fi
```

### 13. **🔍 Validation Checklist**

```bash
echo "
✅ VALIDATION CHECKLIST:

🗂️ File Structure:
- [✓] index.html exists and valid
- [✓] style.css with responsive design  
- [✓] main.js with functionality
- [✓] .gitignore configured
- [✓] README.md documentation

📋 Git Status:
- [✓] Repository initialized
- [✓] All files committed
- [✓] Working tree clean
- [✓] Meaningful commit message

🌐 Web Standards:
- [✓] Semantic HTML5
- [✓] Modern CSS with custom properties
- [✓] ES6+ JavaScript
- [✓] Mobile-first responsive design

🚀 Ready for:
- [✓] Browser testing
- [✓] Remote repository setup
- [✓] Continuous development
- [✓] Team collaboration"
```

---

## 🔗 Prossimi Passi

1. **🌐 Test e Refinement**
   - Aprire in browser e testare funzionalità
   - Validare HTML/CSS con tools online
   - Test responsive su dispositivi diversi

2. **📡 Remote Repository**
   - Creare repository GitHub
   - Configurare remote origin
   - Push del codice iniziale

3. **🔄 Development Workflow**
   - Creare branch per nuove features
   - Implementare sistema di build (se necessario)
   - Setup deployment automatico

4. **👥 Collaborazione**
   - Invite collaboratori
   - Setup branch protection rules
   - Configurare issue templates

---

Questo esempio fornisce una base solida per comprendere come Git si integra nel workflow di sviluppo web, dall'inizializzazione fino al primo commit strutturato e documentato.
