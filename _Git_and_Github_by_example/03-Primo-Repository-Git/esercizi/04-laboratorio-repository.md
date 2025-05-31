# Esercizio 4: Laboratorio Repository Completo

## 🎯 Obiettivi
- Consolidare tutti i concetti del primo repository Git
- Gestire un progetto completo dall'inizio alla fine
- Praticare workflow professionale di base
- Comprendere l'anatomia completa di un repository

## 🚀 Progetto: Blog Personale Statico

### Scenario
Creerai un blog personale statico utilizzando Git per tracciare ogni fase di sviluppo. Questo progetto ti permetterà di praticare tutti i concetti appresi sui repository Git in un contesto realistico.

## 📋 Fase 1: Inizializzazione e Setup (20 minuti)

### Attività 1.1 - Creazione Repository
```bash
# Naviga nella directory dei tuoi progetti
cd ~/progetti

# Crea directory del blog
mkdir mio-blog-personale
cd mio-blog-personale

# Inizializza Git repository
git init

# Verifica l'inizializzazione
ls -la
ls -la .git/
```

**❓ Domande di Verifica:**
1. Cosa contiene la directory `.git/` appena creata?
2. Qual è lo stato attuale del repository?
3. Come puoi verificare che Git sia stato inizializzato correttamente?

### Attività 1.2 - Configurazione Repository
```bash
# Configura informazioni autore (se non già fatto globalmente)
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"

# Verifica configurazione
git config --list --local

# Imposta branch principale (opzionale)
git config init.defaultBranch main
```

### Attività 1.3 - Struttura Progetto Base
Crea questa struttura di directory e file:

```
mio-blog-personale/
├── index.html
├── about.html
├── blog/
│   └── .gitkeep
├── assets/
│   ├── css/
│   │   └── style.css
│   ├── js/
│   │   └── main.js
│   └── images/
│       └── .gitkeep
├── posts/
│   └── .gitkeep
└── README.md
```

**Comandi per creare la struttura:**
```bash
# Crea file principali
touch index.html about.html README.md

# Crea directory
mkdir -p blog posts assets/css assets/js assets/images

# Crea file placeholder per directory vuote
touch blog/.gitkeep posts/.gitkeep assets/images/.gitkeep

# Crea file CSS e JS
touch assets/css/style.css assets/js/main.js
```

### Attività 1.4 - Primo Check Status
```bash
# Verifica stato repository
git status

# Analizza l'output
# - Quali file sono "Untracked"?
# - Cosa significa "On branch main"?
# - Cosa indica "No commits yet"?
```

## 📝 Fase 2: Contenuto e Primo Commit (30 minuti)

### Attività 2.1 - Contenuto Base
**README.md:**
```markdown
# Il Mio Blog Personale

## 📖 Descrizione
Blog personale statico per condividere pensieri, esperienze e apprendimenti nel mondo della tecnologia e non solo.

## 🚀 Caratteristiche
- Design minimalista e responsive
- Sistema di navigazione semplice
- Sezione blog per articoli
- Pagina about personale

## 🛠️ Tecnologie
- HTML5 semantico
- CSS3 con design responsive
- JavaScript vanilla per interazioni
- Git per version control

## 📂 Struttura
- `index.html` - Homepage
- `about.html` - Pagina chi sono
- `blog/` - Articoli del blog
- `posts/` - Post in formato markdown
- `assets/` - CSS, JS e immagini

## 📋 TODO
- [ ] Completare homepage
- [ ] Aggiungere sezione blog
- [ ] Implementare design responsive
- [ ] Scrivere primi articoli

---
*Ultima modifica: $(date +%Y-%m-%d)*
```

**index.html:**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Blog - Home</title>
    <meta name="description" content="Blog personale di [Tuo Nome] - Tecnologia, sviluppo e vita digitale">
    <link rel="stylesheet" href="assets/css/style.css">
</head>
<body>
    <header class="main-header">
        <nav class="navigation">
            <div class="logo">
                <h1>Il Mio Blog</h1>
            </div>
            <ul class="nav-menu">
                <li><a href="index.html" class="active">Home</a></li>
                <li><a href="about.html">Chi sono</a></li>
                <li><a href="blog/">Blog</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>

    <main class="main-content">
        <section class="hero">
            <h2>Benvenuto nel mio spazio digitale</h2>
            <p>Qui condivido le mie esperienze, apprendimenti e riflessioni su tecnologia, sviluppo software e molto altro.</p>
            <a href="blog/" class="btn-primary">Leggi il Blog</a>
        </section>

        <section class="latest-posts">
            <h3>Ultimi Articoli</h3>
            <div class="posts-grid">
                <article class="post-preview">
                    <h4>Il mio primo repository Git</h4>
                    <p class="post-meta">Pubblicato il: <time>2025-05-31</time></p>
                    <p>Racconto della mia esperienza nell'apprendimento di Git e version control...</p>
                    <a href="posts/primo-repository-git.html">Leggi tutto</a>
                </article>
                
                <article class="post-preview">
                    <h4>Perché ho scelto di programmare</h4>
                    <p class="post-meta">Pubblicato il: <time>2025-05-30</time></p>
                    <p>La mia storia personale e le motivazioni che mi hanno portato alla programmazione...</p>
                    <a href="posts/perche-programmare.html">Leggi tutto</a>
                </article>
            </div>
        </section>
    </main>

    <footer class="main-footer">
        <p>&copy; 2025 Il Mio Blog. Realizzato con ❤️ e Git.</p>
    </footer>

    <script src="assets/js/main.js"></script>
</body>
</html>
```

### Attività 2.2 - Primo Tracking
```bash
# Aggiungi README al tracking
git add README.md

# Verifica status
git status

# Nota come il file è ora in "Changes to be committed" (staging area)
```

### Attività 2.3 - Primo Commit
```bash
# Primo commit del progetto
git commit -m "Initial project setup

- Created basic project structure
- Added README with project description
- Setup directory structure for blog
- Added placeholder files for organization"

# Verifica il commit
git log
git show HEAD
```

## 🎨 Fase 3: Sviluppo e Tracking (40 minuti)

### Attività 3.1 - Styling CSS
**assets/css/style.css:**
```css
/* Reset e base */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Georgia', 'Times New Roman', serif;
    line-height: 1.6;
    color: #333;
    background-color: #fafafa;
}

/* Header e Navigation */
.main-header {
    background: #2c3e50;
    color: white;
    padding: 1rem 0;
    box-shadow: 0 2px 5px rgba(0,0,0,0.1);
}

.navigation {
    max-width: 1200px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0 2rem;
}

.logo h1 {
    font-size: 1.8rem;
    font-weight: 300;
}

.nav-menu {
    list-style: none;
    display: flex;
}

.nav-menu li {
    margin-left: 2rem;
}

.nav-menu a {
    color: white;
    text-decoration: none;
    transition: color 0.3s ease;
    padding: 0.5rem 1rem;
    border-radius: 4px;
}

.nav-menu a:hover,
.nav-menu a.active {
    background-color: #34495e;
    color: #ecf0f1;
}

/* Main Content */
.main-content {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem;
}

.hero {
    text-align: center;
    padding: 4rem 0;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    border-radius: 8px;
    margin-bottom: 3rem;
}

.hero h2 {
    font-size: 2.5rem;
    margin-bottom: 1rem;
    font-weight: 300;
}

.hero p {
    font-size: 1.2rem;
    margin-bottom: 2rem;
    max-width: 600px;
    margin-left: auto;
    margin-right: auto;
}

.btn-primary {
    display: inline-block;
    background: #e74c3c;
    color: white;
    padding: 1rem 2rem;
    text-decoration: none;
    border-radius: 5px;
    transition: background 0.3s ease;
    font-weight: 500;
}

.btn-primary:hover {
    background: #c0392b;
}

/* Posts Section */
.latest-posts {
    margin-top: 3rem;
}

.latest-posts h3 {
    font-size: 2rem;
    margin-bottom: 2rem;
    color: #2c3e50;
    border-bottom: 3px solid #3498db;
    padding-bottom: 0.5rem;
}

.posts-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
}

.post-preview {
    background: white;
    padding: 2rem;
    border-radius: 8px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
    transition: transform 0.3s ease;
}

.post-preview:hover {
    transform: translateY(-5px);
}

.post-preview h4 {
    color: #2c3e50;
    margin-bottom: 1rem;
    font-size: 1.3rem;
}

.post-meta {
    color: #7f8c8d;
    font-size: 0.9rem;
    margin-bottom: 1rem;
}

.post-preview p {
    margin-bottom: 1rem;
    color: #555;
}

.post-preview a {
    color: #3498db;
    text-decoration: none;
    font-weight: 500;
}

.post-preview a:hover {
    text-decoration: underline;
}

/* Footer */
.main-footer {
    background: #34495e;
    color: white;
    text-align: center;
    padding: 2rem;
    margin-top: 4rem;
}

/* Responsive */
@media (max-width: 768px) {
    .navigation {
        flex-direction: column;
        text-align: center;
    }
    
    .nav-menu {
        margin-top: 1rem;
    }
    
    .nav-menu li {
        margin: 0 1rem;
    }
    
    .hero h2 {
        font-size: 2rem;
    }
    
    .main-content {
        padding: 1rem;
    }
}
```

### Attività 3.2 - Tracking CSS
```bash
# Aggiungi il CSS
git add assets/css/style.css

# Verifica status
git status

# Commit del CSS
git commit -m "Add comprehensive CSS styling

- Implemented responsive design system
- Added header and navigation styling
- Created hero section with gradient background
- Designed post preview cards with hover effects
- Added mobile-responsive breakpoints"
```

### Attività 3.3 - JavaScript Interattività
**assets/js/main.js:**
```javascript
// Blog JavaScript Functionality
document.addEventListener('DOMContentLoaded', function() {
    console.log('Blog loaded successfully!');
    
    // Initialize all functionality
    initNavigation();
    initAnimations();
    initPostPreviews();
    addTimestamps();
});

// Navigation functionality
function initNavigation() {
    const navLinks = document.querySelectorAll('.nav-menu a');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            // Remove active class from all links
            navLinks.forEach(l => l.classList.remove('active'));
            
            // Add active class to clicked link
            this.classList.add('active');
            
            // Smooth scroll for internal links
            if (this.getAttribute('href').startsWith('#')) {
                e.preventDefault();
                const targetId = this.getAttribute('href').substring(1);
                const targetElement = document.getElementById(targetId);
                
                if (targetElement) {
                    targetElement.scrollIntoView({
                        behavior: 'smooth',
                        block: 'start'
                    });
                }
            }
        });
    });
}

// Animation on scroll
function initAnimations() {
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
    
    // Observe post previews
    const posts = document.querySelectorAll('.post-preview');
    posts.forEach(post => {
        post.style.opacity = '0';
        post.style.transform = 'translateY(30px)';
        post.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        observer.observe(post);
    });
}

// Post preview interactions
function initPostPreviews() {
    const postPreviews = document.querySelectorAll('.post-preview');
    
    postPreviews.forEach(post => {
        post.addEventListener('mouseenter', function() {
            this.style.boxShadow = '0 8px 25px rgba(0,0,0,0.15)';
        });
        
        post.addEventListener('mouseleave', function() {
            this.style.boxShadow = '0 2px 10px rgba(0,0,0,0.1)';
        });
    });
}

// Add reading time and word count
function addTimestamps() {
    const posts = document.querySelectorAll('.post-preview');
    
    posts.forEach(post => {
        const text = post.querySelector('p:not(.post-meta)').textContent;
        const wordCount = text.split(' ').length;
        const readingTime = Math.ceil(wordCount / 200); // 200 words per minute
        
        const metaElement = post.querySelector('.post-meta');
        if (metaElement) {
            metaElement.innerHTML += ` • ${wordCount} parole • ${readingTime} min di lettura`;
        }
    });
}

// Utility function for smooth animations
function animateElement(element, animation, duration = 300) {
    element.style.transition = `all ${duration}ms ease`;
    element.style.transform = animation;
    
    setTimeout(() => {
        element.style.transform = '';
    }, duration);
}

// Add search functionality (future enhancement)
function initSearch() {
    // TODO: Implement search functionality
    console.log('Search functionality to be implemented');
}

// Contact form handling (future enhancement)
function initContactForm() {
    // TODO: Implement contact form
    console.log('Contact form to be implemented');
}
```

### Attività 3.4 - Commit Separati
```bash
# Prima aggiungi HTML
git add index.html

git commit -m "Add complete homepage HTML structure

- Created semantic HTML layout
- Added navigation with responsive design
- Implemented hero section with call-to-action
- Added blog post previews section
- Included proper meta tags for SEO"

# Poi aggiungi JavaScript
git add assets/js/main.js

git commit -m "Implement interactive JavaScript features

- Added smooth navigation with active states
- Implemented scroll animations with Intersection Observer
- Created post preview hover effects
- Added automatic reading time calculation
- Included utility functions for future enhancements"
```

## 🔍 Fase 4: Analisi Repository (20 minuti)

### Attività 4.1 - Esplorazione .git
```bash
# Esplora la struttura .git
ls -la .git/
cat .git/HEAD
cat .git/config
ls .git/objects/
ls .git/refs/heads/
```

**❓ Domande di Analisi:**
1. Cosa contiene il file `.git/HEAD`?
2. Dove sono memorizzati i commit?
3. Come Git traccia il branch corrente?

### Attività 4.2 - Stati File Approfonditi
```bash
# Crea un nuovo file
echo "# Blog Ideas" > ideas.txt

# Modifica un file esistente
echo "/* Additional styles coming soon */" >> assets/css/style.css

# Verifica stati diversi
git status

# Analizza gli stati:
# - ideas.txt è "Untracked"
# - style.css è "Modified"
```

### Attività 4.3 - Gestione Staging Area
```bash
# Aggiungi solo il file modificato
git add assets/css/style.css

# Verifica status
git status

# Ora hai:
# - style.css in staging area (Changes to be committed)
# - ideas.txt untracked
```

### Attività 4.4 - Cronologia Completa
```bash
# Visualizza cronologia
git log --oneline
git log --stat
git log --graph --pretty=format:"%h - %an, %ar : %s"

# Analizza un commit specifico
git show HEAD~1
```

## 📝 Fase 5: Completamento e Documentazione (30 minuti)

### Attività 5.1 - Pagina About
**about.html:**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Chi sono - Il Mio Blog</title>
    <meta name="description" content="Scopri chi sono e la mia storia nel mondo della tecnologia">
    <link rel="stylesheet" href="assets/css/style.css">
</head>
<body>
    <header class="main-header">
        <nav class="navigation">
            <div class="logo">
                <h1>Il Mio Blog</h1>
            </div>
            <ul class="nav-menu">
                <li><a href="index.html">Home</a></li>
                <li><a href="about.html" class="active">Chi sono</a></li>
                <li><a href="blog/">Blog</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>

    <main class="main-content">
        <section class="about-hero">
            <h2>Chi sono</h2>
            <p>Studente appassionato di tecnologia e sviluppo software</p>
        </section>

        <section class="about-content">
            <div class="about-text">
                <h3>La mia storia</h3>
                <p>Sono uno studente di informatica con una grande passione per la tecnologia e lo sviluppo software. Ho iniziato questo viaggio di apprendimento con curiosità e determinazione.</p>
                
                <h3>Cosa studio</h3>
                <ul>
                    <li>Programmazione e algoritmi</li>
                    <li>Sviluppo web (HTML, CSS, JavaScript)</li>
                    <li>Version control con Git</li>
                    <li>Database e gestione dati</li>
                </ul>
                
                <h3>I miei obiettivi</h3>
                <p>Attraverso questo blog voglio documentare il mio percorso di apprendimento, condividere scoperte interessanti e crescere insieme alla community di sviluppatori.</p>
            </div>
        </section>
    </main>

    <footer class="main-footer">
        <p>&copy; 2025 Il Mio Blog. Realizzato con ❤️ e Git.</p>
    </footer>

    <script src="assets/js/main.js"></script>
</body>
</html>
```

### Attività 5.2 - Primo Post
**posts/primo-repository-git.html:**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il mio primo repository Git - Il Mio Blog</title>
    <link rel="stylesheet" href="../assets/css/style.css">
</head>
<body>
    <header class="main-header">
        <nav class="navigation">
            <div class="logo">
                <h1>Il Mio Blog</h1>
            </div>
            <ul class="nav-menu">
                <li><a href="../index.html">Home</a></li>
                <li><a href="../about.html">Chi sono</a></li>
                <li><a href="../blog/">Blog</a></li>
            </ul>
        </nav>
    </header>

    <main class="main-content">
        <article class="blog-post">
            <header class="post-header">
                <h1>Il mio primo repository Git</h1>
                <p class="post-meta">Pubblicato il 31 Maggio 2025</p>
            </header>
            
            <div class="post-content">
                <p>Oggi ho creato il mio primo repository Git per questo blog. È stata un'esperienza incredibile vedere come Git traccia ogni modifica e permette di mantenere una cronologia completa del progetto.</p>
                
                <h2>Cosa ho imparato</h2>
                <ul>
                    <li>Come inizializzare un repository con <code>git init</code></li>
                    <li>L'importanza dell'area di staging</li>
                    <li>Come scrivere messaggi di commit chiari</li>
                    <li>La differenza tra file tracked e untracked</li>
                </ul>
                
                <h2>Prossimi passi</h2>
                <p>Ora che ho le basi, voglio esplorare i branch e la collaborazione con altri sviluppatori.</p>
            </div>
        </article>
    </main>

    <footer class="main-footer">
        <p>&copy; 2025 Il Mio Blog. Realizzato con ❤️ e Git.</p>
    </footer>
</body>
</html>
```

### Attività 5.3 - Commit Finali
```bash
# Aggiungi tutto il nuovo contenuto
git add about.html posts/

git commit -m "Add about page and first blog post

- Created comprehensive about page with personal story
- Added first blog post about Git experience
- Included proper navigation and styling
- Established blog post template structure"

# Completa con le idee
git add ideas.txt

git commit -m "Add blog ideas file for future content planning"
```

### Attività 5.4 - Aggiornamento README
```bash
# Aggiorna README con progresso
cat >> README.md << 'EOF'

## 📊 Stato del Progetto
- ✅ Struttura base completata
- ✅ Homepage con design responsive
- ✅ Sistema di navigazione
- ✅ Pagina about personale
- ✅ Primo articolo del blog
- ✅ JavaScript per interazioni
- ✅ CSS completo e responsive

## 📈 Statistiche Git
- Commit totali: $(git rev-list --count HEAD)
- File tracciati: $(git ls-files | wc -l)
- Dimensione repository: $(du -sh .git)

EOF

git add README.md
git commit -m "Update README with project status and Git statistics"
```

## 📊 Deliverables Finali

### 1. Repository Completo
- ✅ Almeno 8 commit significativi
- ✅ Blog funzionante con più pagine
- ✅ Documentazione completa
- ✅ Struttura professionale

### 2. Report Tecnico (500 parole)
Scrivi un'analisi che includa:
- **Anatomia Repository**: Cosa contiene `.git/` e perché
- **Stati File**: Esempi di untracked, staged, committed
- **Workflow**: Come hai organizzato i commit
- **Lezioni Apprese**: Cosa hai capito sui repository Git

### 3. Dimostrazione Pratica
Prepara una demo di 10 minuti che mostri:
- Cronologia di sviluppo tramite `git log`
- Funzionalità del blog creato
- Esempi di stati file diversi
- Uso dell'area di staging

## 🎯 Domande di Auto-Valutazione

1. **Concetti di Base**:
   - Cosa distingue un repository Git da una normale cartella?
   - Qual è la differenza tra working directory e staging area?
   - Perché i commit sono importanti?

2. **Workflow Pratico**:
   - Come verifichi lo stato del tuo repository?
   - Quando usi `git add` vs `git commit`?
   - Come analizzi la cronologia del progetto?

3. **Best Practices**:
   - Come strutturi i tuoi messaggi di commit?
   - Quando fai commit separati vs un commit unico?
   - Come organizzi la struttura dei file?

## 🏆 Criteri di Valutazione

- **Completezza Repository** (30%): Tutti i file e struttura corretta
- **Qualità Commit** (25%): Messaggi chiari e commit logici
- **Funzionalità Blog** (25%): Sito web completo e funzionante
- **Comprensione Concetti** (20%): Report tecnico approfondito

## 🚀 Estensioni Avanzate

### Per Chi Vuole Approfondire
- [ ] Aggiungi un file `.gitignore` appropriato
- [ ] Crea alias Git personalizzati
- [ ] Implementa hook Git per validazione
- [ ] Esplora la struttura degli oggetti Git

### Preparazione Moduli Successivi
- [ ] Sperimenta con `git log` avanzato
- [ ] Prova `git diff` su file modificati
- [ ] Esplora `git show` per commit specifici
- [ ] Familiarizza con `git ls-files`

---

**Tempo stimato:** 2.5-3 ore  
**Difficoltà:** ⭐⭐⭐  
**Prerequisiti:** Esercizi 1-3 completati  
**Tag:** #repository #blog #workflow #complete-project
