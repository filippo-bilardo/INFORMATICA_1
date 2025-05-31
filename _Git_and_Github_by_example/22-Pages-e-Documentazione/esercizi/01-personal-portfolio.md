# Esercizio 1: Creazione Portfolio Personale

## 🎯 Obiettivi
- Creare un portfolio personale usando GitHub Pages
- Configurare un dominio personalizzato
- Implementare un tema responsive
- Integrare progetti e competenze

## 📋 Prerequisiti
- Account GitHub attivo
- Conoscenza base HTML/CSS
- Repository GitHub esistenti da mostrare

## 🚀 Parte 1: Setup Iniziale

### 1. Creazione Repository Portfolio
```bash
# Crea un nuovo repository chiamato 'username.github.io'
# (sostituisci 'username' con il tuo username GitHub)
git clone https://github.com/username/username.github.io.git
cd username.github.io
```

### 2. Struttura Base del Progetto
Crea la seguente struttura:
```
username.github.io/
├── index.html
├── about.html
├── projects.html
├── contact.html
├── css/
│   ├── style.css
│   └── responsive.css
├── js/
│   └── main.js
├── images/
│   ├── profile.jpg
│   └── projects/
└── _config.yml
```

### 3. Configurazione Jekyll (_config.yml)
```yaml
# Site settings
title: "Il Mio Portfolio"
description: "Sviluppatore Full Stack appassionato di tecnologie moderne"
author: "Il Tuo Nome"
email: "tua-email@example.com"
baseurl: ""
url: "https://username.github.io"

# Build settings
markdown: kramdown
highlighter: rouge
theme: minima

# Plugins
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag

# Collections
collections:
  projects:
    output: true
    permalink: /:collection/:name/

# Defaults
defaults:
  - scope:
      path: ""
      type: "posts"
    values:
      layout: "post"
  - scope:
      path: ""
      type: "projects"
    values:
      layout: "project"
```

## 🎨 Parte 2: Design e Layout

### 1. Homepage (index.html)
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{{ site.title }}</title>
    <link rel="stylesheet" href="css/style.css">
    <link rel="stylesheet" href="css/responsive.css">
    <!-- Font Awesome per le icone -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
</head>
<body>
    <header class="header">
        <nav class="navbar">
            <div class="nav-container">
                <div class="nav-logo">
                    <a href="/">{{ site.author }}</a>
                </div>
                <ul class="nav-menu">
                    <li class="nav-item">
                        <a href="#home" class="nav-link">Home</a>
                    </li>
                    <li class="nav-item">
                        <a href="#about" class="nav-link">Chi Sono</a>
                    </li>
                    <li class="nav-item">
                        <a href="#projects" class="nav-link">Progetti</a>
                    </li>
                    <li class="nav-item">
                        <a href="#contact" class="nav-link">Contatti</a>
                    </li>
                </ul>
                <div class="nav-toggle" id="mobile-menu">
                    <span class="bar"></span>
                    <span class="bar"></span>
                    <span class="bar"></span>
                </div>
            </div>
        </nav>
    </header>

    <main>
        <!-- Hero Section -->
        <section id="home" class="hero">
            <div class="hero-container">
                <div class="hero-content">
                    <h1 class="hero-title">Ciao, sono {{ site.author }}</h1>
                    <p class="hero-subtitle">{{ site.description }}</p>
                    <div class="hero-buttons">
                        <a href="#projects" class="btn btn-primary">Vedi i Progetti</a>
                        <a href="#contact" class="btn btn-secondary">Contattami</a>
                    </div>
                </div>
                <div class="hero-image">
                    <img src="images/profile.jpg" alt="Profilo" class="profile-img">
                </div>
            </div>
        </section>

        <!-- About Section -->
        <section id="about" class="about">
            <div class="container">
                <h2 class="section-title">Chi Sono</h2>
                <div class="about-content">
                    <div class="about-text">
                        <p>Sono uno sviluppatore appassionato con esperienza in sviluppo web full-stack. 
                        Mi piace creare applicazioni che risolvono problemi reali e migliorano l'esperienza utente.</p>
                        
                        <h3>Competenze Tecniche</h3>
                        <div class="skills">
                            <div class="skill-item">
                                <i class="fab fa-html5"></i>
                                <span>HTML5</span>
                            </div>
                            <div class="skill-item">
                                <i class="fab fa-css3-alt"></i>
                                <span>CSS3</span>
                            </div>
                            <div class="skill-item">
                                <i class="fab fa-js-square"></i>
                                <span>JavaScript</span>
                            </div>
                            <div class="skill-item">
                                <i class="fab fa-react"></i>
                                <span>React</span>
                            </div>
                            <div class="skill-item">
                                <i class="fab fa-node-js"></i>
                                <span>Node.js</span>
                            </div>
                            <div class="skill-item">
                                <i class="fab fa-git-alt"></i>
                                <span>Git</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <!-- Projects Section -->
        <section id="projects" class="projects">
            <div class="container">
                <h2 class="section-title">I Miei Progetti</h2>
                <div class="projects-grid">
                    <!-- I progetti verranno popolati dinamicamente -->
                </div>
            </div>
        </section>

        <!-- Contact Section -->
        <section id="contact" class="contact">
            <div class="container">
                <h2 class="section-title">Contattami</h2>
                <div class="contact-content">
                    <div class="contact-info">
                        <div class="contact-item">
                            <i class="fas fa-envelope"></i>
                            <span>{{ site.email }}</span>
                        </div>
                        <div class="contact-item">
                            <i class="fab fa-github"></i>
                            <a href="https://github.com/username">GitHub</a>
                        </div>
                        <div class="contact-item">
                            <i class="fab fa-linkedin"></i>
                            <a href="https://linkedin.com/in/username">LinkedIn</a>
                        </div>
                    </div>
                    <form class="contact-form" action="https://formspree.io/f/your-form-id" method="POST">
                        <div class="form-group">
                            <label for="name">Nome</label>
                            <input type="text" id="name" name="name" required>
                        </div>
                        <div class="form-group">
                            <label for="email">Email</label>
                            <input type="email" id="email" name="email" required>
                        </div>
                        <div class="form-group">
                            <label for="message">Messaggio</label>
                            <textarea id="message" name="message" rows="5" required></textarea>
                        </div>
                        <button type="submit" class="btn btn-primary">Invia Messaggio</button>
                    </form>
                </div>
            </div>
        </section>
    </main>

    <footer class="footer">
        <div class="container">
            <p>&copy; 2024 {{ site.author }}. Tutti i diritti riservati.</p>
        </div>
    </footer>

    <script src="js/main.js"></script>
</body>
</html>
```

### 2. CSS Principale (css/style.css)
```css
/* Reset e Base */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
    line-height: 1.6;
    color: #333;
    overflow-x: hidden;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
}

/* Header e Navigation */
.header {
    background: #fff;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
    position: fixed;
    width: 100%;
    top: 0;
    z-index: 1000;
}

.navbar {
    padding: 1rem 0;
}

.nav-container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.nav-logo a {
    font-size: 1.5rem;
    font-weight: bold;
    color: #2563eb;
    text-decoration: none;
}

.nav-menu {
    display: flex;
    list-style: none;
    gap: 2rem;
}

.nav-link {
    color: #333;
    text-decoration: none;
    transition: color 0.3s;
}

.nav-link:hover {
    color: #2563eb;
}

/* Hero Section */
.hero {
    padding: 120px 0 80px;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    min-height: 100vh;
    display: flex;
    align-items: center;
}

.hero-container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 4rem;
    align-items: center;
}

.hero-title {
    font-size: 3rem;
    margin-bottom: 1rem;
    animation: fadeInUp 1s ease;
}

.hero-subtitle {
    font-size: 1.2rem;
    margin-bottom: 2rem;
    opacity: 0.9;
    animation: fadeInUp 1s ease 0.2s both;
}

.hero-buttons {
    display: flex;
    gap: 1rem;
    animation: fadeInUp 1s ease 0.4s both;
}

.btn {
    padding: 12px 24px;
    border-radius: 6px;
    text-decoration: none;
    font-weight: 500;
    transition: all 0.3s;
    display: inline-block;
}

.btn-primary {
    background: #2563eb;
    color: white;
}

.btn-primary:hover {
    background: #1d4ed8;
    transform: translateY(-2px);
}

.btn-secondary {
    background: transparent;
    color: white;
    border: 2px solid white;
}

.btn-secondary:hover {
    background: white;
    color: #2563eb;
}

.profile-img {
    width: 300px;
    height: 300px;
    border-radius: 50%;
    object-fit: cover;
    border: 5px solid rgba(255,255,255,0.2);
    animation: fadeInRight 1s ease 0.6s both;
}

/* Sections */
.section-title {
    text-align: center;
    font-size: 2.5rem;
    margin-bottom: 3rem;
    color: #1f2937;
}

.about {
    padding: 80px 0;
    background: #f9fafb;
}

.about-content {
    max-width: 800px;
    margin: 0 auto;
    text-align: center;
}

.about-text p {
    font-size: 1.1rem;
    margin-bottom: 2rem;
    color: #6b7280;
}

.skills {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));
    gap: 1.5rem;
    margin-top: 2rem;
}

.skill-item {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 1.5rem;
    background: white;
    border-radius: 12px;
    box-shadow: 0 4px 6px rgba(0,0,0,0.05);
    transition: transform 0.3s;
}

.skill-item:hover {
    transform: translateY(-5px);
}

.skill-item i {
    font-size: 2rem;
    color: #2563eb;
    margin-bottom: 0.5rem;
}

/* Projects */
.projects {
    padding: 80px 0;
}

.projects-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
}

/* Contact */
.contact {
    padding: 80px 0;
    background: #f9fafb;
}

.contact-content {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 4rem;
    max-width: 800px;
    margin: 0 auto;
}

.contact-item {
    display: flex;
    align-items: center;
    gap: 1rem;
    margin-bottom: 1rem;
}

.contact-item i {
    color: #2563eb;
    font-size: 1.2rem;
}

.contact-form {
    background: white;
    padding: 2rem;
    border-radius: 12px;
    box-shadow: 0 4px 6px rgba(0,0,0,0.05);
}

.form-group {
    margin-bottom: 1.5rem;
}

.form-group label {
    display: block;
    margin-bottom: 0.5rem;
    font-weight: 500;
    color: #374151;
}

.form-group input,
.form-group textarea {
    width: 100%;
    padding: 12px;
    border: 1px solid #d1d5db;
    border-radius: 6px;
    font-size: 1rem;
    transition: border-color 0.3s;
}

.form-group input:focus,
.form-group textarea:focus {
    outline: none;
    border-color: #2563eb;
}

/* Footer */
.footer {
    background: #1f2937;
    color: white;
    text-align: center;
    padding: 2rem 0;
}

/* Animations */
@keyframes fadeInUp {
    from {
        opacity: 0;
        transform: translateY(30px);
    }
    to {
        opacity: 1;
        transform: translateY(0);
    }
}

@keyframes fadeInRight {
    from {
        opacity: 0;
        transform: translateX(30px);
    }
    to {
        opacity: 1;
        transform: translateX(0);
    }
}
```

## 🔧 Parte 3: JavaScript Interattivo

### 1. Script Principale (js/main.js)
```javascript
// Smooth scrolling per i link di navigazione
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({
                behavior: 'smooth',
                block: 'start'
            });
        }
    });
});

// Menu mobile toggle
const mobileMenu = document.getElementById('mobile-menu');
const navMenu = document.querySelector('.nav-menu');

mobileMenu.addEventListener('click', () => {
    mobileMenu.classList.toggle('is-active');
    navMenu.classList.toggle('active');
});

// Caricamento dinamico progetti da GitHub API
async function loadGitHubProjects() {
    try {
        const username = 'your-github-username'; // Sostituisci con il tuo username
        const response = await fetch(`https://api.github.com/users/${username}/repos`);
        const repos = await response.json();
        
        const projectsGrid = document.querySelector('.projects-grid');
        
        // Filtra e ordina i repository più interessanti
        const featuredRepos = repos
            .filter(repo => !repo.fork && repo.stargazers_count >= 0)
            .sort((a, b) => b.stargazers_count - a.stargazers_count)
            .slice(0, 6);
        
        featuredRepos.forEach(repo => {
            const projectCard = createProjectCard(repo);
            projectsGrid.appendChild(projectCard);
        });
    } catch (error) {
        console.error('Errore nel caricamento dei progetti:', error);
        // Mostra progetti statici di fallback
        loadStaticProjects();
    }
}

function createProjectCard(repo) {
    const card = document.createElement('div');
    card.className = 'project-card';
    
    const language = repo.language || 'Multiple';
    const description = repo.description || 'Nessuna descrizione disponibile';
    
    card.innerHTML = `
        <div class="project-image">
            <i class="fas fa-code"></i>
        </div>
        <div class="project-content">
            <h3 class="project-title">${repo.name}</h3>
            <p class="project-description">${description}</p>
            <div class="project-tech">
                <span class="tech-tag">${language}</span>
            </div>
            <div class="project-stats">
                <span class="stat">
                    <i class="fas fa-star"></i>
                    ${repo.stargazers_count}
                </span>
                <span class="stat">
                    <i class="fas fa-code-branch"></i>
                    ${repo.forks_count}
                </span>
            </div>
            <div class="project-links">
                <a href="${repo.html_url}" target="_blank" class="btn btn-primary">
                    <i class="fab fa-github"></i>
                    Codice
                </a>
                ${repo.homepage ? `<a href="${repo.homepage}" target="_blank" class="btn btn-secondary">Demo</a>` : ''}
            </div>
        </div>
    `;
    
    // Aggiungi CSS per le card
    if (!document.querySelector('#project-card-styles')) {
        const styles = document.createElement('style');
        styles.id = 'project-card-styles';
        styles.textContent = `
            .project-card {
                background: white;
                border-radius: 12px;
                box-shadow: 0 4px 6px rgba(0,0,0,0.05);
                overflow: hidden;
                transition: transform 0.3s, box-shadow 0.3s;
            }
            
            .project-card:hover {
                transform: translateY(-5px);
                box-shadow: 0 12px 25px rgba(0,0,0,0.15);
            }
            
            .project-image {
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                height: 150px;
                display: flex;
                align-items: center;
                justify-content: center;
                color: white;
            }
            
            .project-image i {
                font-size: 3rem;
            }
            
            .project-content {
                padding: 1.5rem;
            }
            
            .project-title {
                font-size: 1.2rem;
                margin-bottom: 0.5rem;
                color: #1f2937;
            }
            
            .project-description {
                color: #6b7280;
                margin-bottom: 1rem;
                font-size: 0.9rem;
                line-height: 1.4;
            }
            
            .project-tech {
                margin-bottom: 1rem;
            }
            
            .tech-tag {
                background: #e5f3ff;
                color: #2563eb;
                padding: 0.25rem 0.75rem;
                border-radius: 20px;
                font-size: 0.8rem;
                font-weight: 500;
            }
            
            .project-stats {
                display: flex;
                gap: 1rem;
                margin-bottom: 1rem;
                font-size: 0.9rem;
                color: #6b7280;
            }
            
            .stat {
                display: flex;
                align-items: center;
                gap: 0.25rem;
            }
            
            .project-links {
                display: flex;
                gap: 0.5rem;
            }
            
            .project-links .btn {
                padding: 0.5rem 1rem;
                font-size: 0.9rem;
                display: flex;
                align-items: center;
                gap: 0.5rem;
            }
        `;
        document.head.appendChild(styles);
    }
    
    return card;
}

function loadStaticProjects() {
    const staticProjects = [
        {
            name: "Portfolio Website",
            description: "Il mio sito portfolio personale creato con HTML, CSS e JavaScript",
            language: "HTML/CSS",
            html_url: "#",
            stargazers_count: 5,
            forks_count: 2
        },
        {
            name: "Todo App",
            description: "Applicazione per la gestione di task con React e Local Storage",
            language: "React",
            html_url: "#",
            stargazers_count: 3,
            forks_count: 1
        },
        {
            name: "Weather Dashboard",
            description: "Dashboard meteo che utilizza API esterne per mostrare previsioni",
            language: "JavaScript",
            html_url: "#",
            stargazers_count: 8,
            forks_count: 3
        }
    ];
    
    const projectsGrid = document.querySelector('.projects-grid');
    staticProjects.forEach(project => {
        const projectCard = createProjectCard(project);
        projectsGrid.appendChild(projectCard);
    });
}

// Intersection Observer per animazioni
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.style.opacity = '1';
            entry.target.style.transform = 'translateY(0)';
        }
    });
}, observerOptions);

// Osserva elementi per animazioni
document.addEventListener('DOMContentLoaded', () => {
    const animatedElements = document.querySelectorAll('.section-title, .project-card, .skill-item');
    animatedElements.forEach(el => {
        el.style.opacity = '0';
        el.style.transform = 'translateY(20px)';
        el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        observer.observe(el);
    });
    
    // Carica i progetti
    loadGitHubProjects();
});

// Form di contatto
document.querySelector('.contact-form').addEventListener('submit', function(e) {
    const submitBtn = this.querySelector('button[type="submit"]');
    const originalText = submitBtn.textContent;
    
    submitBtn.textContent = 'Invio in corso...';
    submitBtn.disabled = true;
    
    // Ripristina il pulsante dopo 3 secondi (Formspree gestirà l'invio reale)
    setTimeout(() => {
        submitBtn.textContent = originalText;
        submitBtn.disabled = false;
    }, 3000);
});
```

## 📱 Parte 4: CSS Responsive (css/responsive.css)
```css
/* Mobile Navigation Toggle */
.nav-toggle {
    display: none;
    flex-direction: column;
    cursor: pointer;
}

.bar {
    width: 25px;
    height: 3px;
    background: #333;
    margin: 3px 0;
    transition: 0.3s;
}

/* Tablet Styles */
@media screen and (max-width: 768px) {
    .nav-menu {
        position: fixed;
        left: -100%;
        top: 70px;
        flex-direction: column;
        background: white;
        width: 100%;
        text-align: center;
        transition: 0.3s;
        box-shadow: 0 10px 27px rgba(0,0,0,0.05);
        padding: 2rem 0;
    }

    .nav-menu.active {
        left: 0;
    }

    .nav-toggle {
        display: flex;
    }

    .nav-toggle.is-active .bar:nth-child(2) {
        opacity: 0;
    }

    .nav-toggle.is-active .bar:nth-child(1) {
        transform: translateY(8px) rotate(45deg);
    }

    .nav-toggle.is-active .bar:nth-child(3) {
        transform: translateY(-8px) rotate(-45deg);
    }

    .hero-container {
        grid-template-columns: 1fr;
        text-align: center;
    }

    .hero-title {
        font-size: 2.5rem;
    }

    .profile-img {
        width: 250px;
        height: 250px;
    }

    .contact-content {
        grid-template-columns: 1fr;
        gap: 2rem;
    }

    .skills {
        grid-template-columns: repeat(auto-fit, minmax(100px, 1fr));
    }
}

/* Mobile Styles */
@media screen and (max-width: 480px) {
    .container {
        padding: 0 15px;
    }

    .hero {
        padding: 100px 0 60px;
    }

    .hero-title {
        font-size: 2rem;
    }

    .hero-subtitle {
        font-size: 1rem;
    }

    .hero-buttons {
        flex-direction: column;
        align-items: center;
    }

    .profile-img {
        width: 200px;
        height: 200px;
    }

    .section-title {
        font-size: 2rem;
    }

    .projects-grid {
        grid-template-columns: 1fr;
    }

    .skills {
        grid-template-columns: repeat(2, 1fr);
    }

    .skill-item {
        padding: 1rem;
    }

    .about, .projects, .contact {
        padding: 60px 0;
    }
}

/* Large Screens */
@media screen and (min-width: 1400px) {
    .hero-title {
        font-size: 3.5rem;
    }

    .hero-subtitle {
        font-size: 1.3rem;
    }

    .profile-img {
        width: 350px;
        height: 350px;
    }
}
```

## 🚀 Parte 5: Deployment e Personalizzazione

### 1. Comando di Deploy
```bash
# Aggiungi tutto al repository
git add .
git commit -m "✨ Portfolio iniziale con design responsive"
git push origin main

# GitHub Pages sarà automaticamente attivato
```

### 2. Configurazione Dominio Personalizzato
Crea un file `CNAME` nella root:
```
tuodominio.com
```

### 3. Gemfile per Jekyll (opzionale)
```ruby
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
gem "jekyll-feed"
gem "jekyll-sitemap"
gem "jekyll-seo-tag"
```

## ✅ Checklist Completamento

### Setup Tecnico
- [ ] Repository creato con nome corretto (username.github.io)
- [ ] GitHub Pages attivato
- [ ] Dominio personalizzato configurato (opzionale)
- [ ] SSL/HTTPS abilitato

### Contenuto
- [ ] Informazioni personali aggiornate
- [ ] Foto profilo professionale
- [ ] Descrizione competenze accurata
- [ ] Progetti GitHub integrati
- [ ] Form di contatto funzionante

### Design
- [ ] Design responsive su tutti i dispositivi
- [ ] Navigazione mobile funzionante
- [ ] Animazioni fluide
- [ ] Colori e tipografia coerenti
- [ ] Velocità di caricamento ottimizzata

### SEO e Accessibilità
- [ ] Meta tag configurati
- [ ] Alt text per le immagini
- [ ] Struttura HTML semantica
- [ ] Contrasto colori accessibile

## 🎯 Estensioni Avanzate

### Analytics
```html
<!-- Google Analytics -->
<script async src="https://www.googletagmanager.com/gtag/js?id=GA_TRACKING_ID"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());
  gtag('config', 'GA_TRACKING_ID');
</script>
```

### PWA Support
```json
// manifest.json
{
  "name": "Il Mio Portfolio",
  "short_name": "Portfolio",
  "description": "Portfolio personale di [Nome]",
  "start_url": "/",
  "display": "standalone",
  "background_color": "#ffffff",
  "theme_color": "#2563eb",
  "icons": [
    {
      "src": "/images/icon-192.png",
      "sizes": "192x192",
      "type": "image/png"
    }
  ]
}
```

## 📚 Risorse Aggiuntive

- [GitHub Pages Documentation](https://docs.github.com/en/pages)
- [Jekyll Documentation](https://jekyllrb.com/docs/)
- [Formspree - Forms for Static Sites](https://formspree.io/)
- [Font Awesome Icons](https://fontawesome.com/)
- [Google Fonts](https://fonts.google.com/)

---

**🎉 Congratulazioni!** Hai creato un portfolio professionale completamente funzionale con GitHub Pages. Il tuo sito sarà accessibile all'indirizzo `https://username.github.io` e mostrerà i tuoi progetti in modo elegante e professionale.
