# Esempio 1: Creazione di un Portfolio Site Professionale

## Obiettivo
Creare un portfolio site professionale utilizzando GitHub Pages con Jekyll, showcasing progetti, skills e esperienze professionali.

## Scenario
Sei uno sviluppatore full-stack che vuole creare un portfolio online professionale per:
- Mostrare i tuoi progetti migliori
- Condividere il tuo background tecnico
- Attrarre opportunità di lavoro
- Documentare il tuo percorso di crescita

## Struttura del Portfolio

### Repository Setup
```bash
# Nome repository: username.github.io
# Esempio: johnsmith.github.io

repository/
├── _config.yml              # Configurazione Jekyll
├── index.html               # Homepage
├── about.md                 # Pagina About
├── portfolio.md             # Pagina Portfolio
├── blog.md                  # Blog/Articles
├── contact.md               # Contatti
├── resume.md                # CV/Resume
├── _layouts/                # Template layouts
│   ├── default.html
│   ├── post.html
│   ├── project.html
│   └── page.html
├── _includes/               # Componenti riutilizzabili
│   ├── header.html
│   ├── footer.html
│   ├── navigation.html
│   └── project-card.html
├── _sass/                   # Stili SCSS
│   ├── _base.scss
│   ├── _layout.scss
│   ├── _components.scss
│   └── _variables.scss
├── assets/                  # Risorse statiche
│   ├── css/
│   ├── js/
│   ├── images/
│   └── documents/
├── _posts/                  # Blog posts
├── _projects/               # Collection progetti
└── _data/                   # Dati strutturati
    ├── skills.yml
    ├── experience.yml
    └── projects.yml
```

## Implementazione Completa

### 1. Configurazione Jekyll (`_config.yml`)

```yaml
# Site settings
title: "John Smith - Full Stack Developer"
description: "Portfolio professionale di John Smith, Full Stack Developer specializzato in React, Node.js e Cloud Computing"
baseurl: ""
url: "https://johnsmith.github.io"
author: "John Smith"
email: "john.smith@email.com"
github_username: johnsmith
linkedin_username: johnsmith
twitter_username: johnsmith

# Build settings
markdown: kramdown
highlighter: rouge
theme: minima
permalink: pretty

# Plugins
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag
  - jekyll-paginate

# Pagination
paginate: 5
paginate_path: "/blog/page:num/"

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
      author: "John Smith"
  - scope:
      path: ""
      type: "projects"
    values:
      layout: "project"

# SEO and Analytics
google_analytics: "GA_MEASUREMENT_ID"
google_site_verification: "VERIFICATION_CODE"

# Social Media
social:
  - platform: "github"
    url: "https://github.com/johnsmith"
    icon: "fab fa-github"
  - platform: "linkedin"
    url: "https://linkedin.com/in/johnsmith"
    icon: "fab fa-linkedin"
  - platform: "twitter"
    url: "https://twitter.com/johnsmith"
    icon: "fab fa-twitter"

# Contact Information
contact:
  location: "Milano, Italia"
  phone: "+39 123 456 7890"
  availability: "Disponibile per nuove opportunità"
```

### 2. Layout Principale (`_layouts/default.html`)

```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{% if page.title %}{{ page.title }} | {{ site.title }}{% else %}{{ site.title }}{% endif %}</title>
    <meta name="description" content="{% if page.description %}{{ page.description }}{% else %}{{ site.description }}{% endif %}">
    
    <!-- SEO Tags -->
    {% seo %}
    
    <!-- Styles -->
    <link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">
    
    <!-- Favicon -->
    <link rel="apple-touch-icon" sizes="180x180" href="{{ '/assets/images/apple-touch-icon.png' | relative_url }}">
    <link rel="icon" type="image/png" sizes="32x32" href="{{ '/assets/images/favicon-32x32.png' | relative_url }}">
    
    <!-- Open Graph -->
    <meta property="og:title" content="{% if page.title %}{{ page.title }}{% else %}{{ site.title }}{% endif %}">
    <meta property="og:description" content="{% if page.description %}{{ page.description }}{% else %}{{ site.description }}{% endif %}">
    <meta property="og:image" content="{{ '/assets/images/og-image.jpg' | absolute_url }}">
    <meta property="og:url" content="{{ page.url | absolute_url }}">
    <meta property="og:type" content="website">
    
    <!-- Schema.org -->
    <script type="application/ld+json">
    {
      "@context": "https://schema.org",
      "@type": "Person",
      "name": "{{ site.author }}",
      "jobTitle": "Full Stack Developer",
      "url": "{{ site.url }}",
      "image": "{{ '/assets/images/profile.jpg' | absolute_url }}",
      "sameAs": [
        {% for social in site.social %}
        "{{ social.url }}"{% unless forloop.last %},{% endunless %}
        {% endfor %}
      ]
    }
    </script>
</head>
<body class="{% if page.class %}{{ page.class }}{% endif %}">
    {% include header.html %}
    
    <main class="main-content">
        {{ content }}
    </main>
    
    {% include footer.html %}
    
    <!-- Scripts -->
    <script src="{{ '/assets/js/main.js' | relative_url }}"></script>
    
    <!-- Analytics -->
    {% if site.google_analytics %}
    <!-- Google tag (gtag.js) -->
    <script async src="https://www.googletagmanager.com/gtag/js?id={{ site.google_analytics }}"></script>
    <script>
      window.dataLayer = window.dataLayer || [];
      function gtag(){dataLayer.push(arguments);}
      gtag('js', new Date());
      gtag('config', '{{ site.google_analytics }}');
    </script>
    {% endif %}
</body>
</html>
```

### 3. Homepage (`index.html`)

```html
---
layout: default
title: "Home"
description: "Portfolio di John Smith - Full Stack Developer esperto in tecnologie moderne"
class: "homepage"
---

<!-- Hero Section -->
<section class="hero">
    <div class="container">
        <div class="hero-content">
            <div class="hero-text">
                <h1 class="hero-title">
                    Ciao, sono <span class="highlight">John Smith</span>
                </h1>
                <p class="hero-subtitle">
                    Full Stack Developer appassionato di tecnologie moderne
                </p>
                <p class="hero-description">
                    Creo applicazioni web innovative utilizzando React, Node.js e Cloud Computing. 
                    Con oltre 5 anni di esperienza, trasformo idee in soluzioni digitali efficaci.
                </p>
                <div class="hero-actions">
                    <a href="{{ '/portfolio' | relative_url }}" class="btn btn-primary">
                        <i class="fas fa-code"></i>
                        Vedi i miei progetti
                    </a>
                    <a href="{{ '/contact' | relative_url }}" class="btn btn-outline">
                        <i class="fas fa-envelope"></i>
                        Contattami
                    </a>
                </div>
            </div>
            <div class="hero-image">
                <img src="{{ '/assets/images/profile.jpg' | relative_url }}" 
                     alt="John Smith - Full Stack Developer" 
                     class="profile-image">
                <div class="image-decoration"></div>
            </div>
        </div>
        
        <!-- Scroll Indicator -->
        <div class="scroll-indicator">
            <i class="fas fa-chevron-down"></i>
        </div>
    </div>
</section>

<!-- Skills Overview -->
<section class="skills-overview">
    <div class="container">
        <h2 class="section-title">Competenze Principali</h2>
        <div class="skills-grid">
            {% assign skills_data = site.data.skills.main %}
            {% for skill in skills_data %}
            <div class="skill-card">
                <div class="skill-icon">
                    <i class="{{ skill.icon }}"></i>
                </div>
                <h3 class="skill-name">{{ skill.name }}</h3>
                <p class="skill-description">{{ skill.description }}</p>
                <div class="skill-technologies">
                    {% for tech in skill.technologies %}
                    <span class="tech-tag">{{ tech }}</span>
                    {% endfor %}
                </div>
            </div>
            {% endfor %}
        </div>
    </div>
</section>

<!-- Featured Projects -->
<section class="featured-projects">
    <div class="container">
        <div class="section-header">
            <h2 class="section-title">Progetti in Evidenza</h2>
            <a href="{{ '/portfolio' | relative_url }}" class="view-all-link">
                Vedi tutti i progetti <i class="fas fa-arrow-right"></i>
            </a>
        </div>
        
        <div class="projects-grid">
            {% assign featured_projects = site.projects | where: "featured", true | limit: 3 %}
            {% for project in featured_projects %}
            <article class="project-card featured">
                <div class="project-image">
                    <img src="{{ project.image | relative_url }}" 
                         alt="{{ project.title }}" 
                         loading="lazy">
                    <div class="project-overlay">
                        <div class="project-links">
                            {% if project.demo_url %}
                            <a href="{{ project.demo_url }}" 
                               class="project-link demo" 
                               target="_blank" 
                               rel="noopener">
                                <i class="fas fa-external-link-alt"></i>
                                Demo
                            </a>
                            {% endif %}
                            {% if project.github_url %}
                            <a href="{{ project.github_url }}" 
                               class="project-link github" 
                               target="_blank" 
                               rel="noopener">
                                <i class="fab fa-github"></i>
                                Codice
                            </a>
                            {% endif %}
                        </div>
                    </div>
                </div>
                
                <div class="project-content">
                    <div class="project-meta">
                        <span class="project-category">{{ project.category }}</span>
                        <time class="project-date" datetime="{{ project.date }}">
                            {{ project.date | date: "%Y" }}
                        </time>
                    </div>
                    
                    <h3 class="project-title">
                        <a href="{{ project.url | relative_url }}">{{ project.title }}</a>
                    </h3>
                    
                    <p class="project-description">{{ project.excerpt }}</p>
                    
                    <div class="project-technologies">
                        {% for tech in project.technologies %}
                        <span class="tech-tag">{{ tech }}</span>
                        {% endfor %}
                    </div>
                </div>
            </article>
            {% endfor %}
        </div>
    </div>
</section>

<!-- Experience Timeline -->
<section class="experience-timeline">
    <div class="container">
        <h2 class="section-title">Esperienza Professionale</h2>
        <div class="timeline">
            {% assign experiences = site.data.experience %}
            {% for exp in experiences limit:3 %}
            <div class="timeline-item">
                <div class="timeline-marker"></div>
                <div class="timeline-content">
                    <div class="timeline-header">
                        <h3 class="position">{{ exp.position }}</h3>
                        <div class="company">{{ exp.company }}</div>
                        <div class="period">{{ exp.start_date }} - {{ exp.end_date | default: "Presente" }}</div>
                    </div>
                    <p class="timeline-description">{{ exp.description }}</p>
                    <div class="timeline-achievements">
                        {% for achievement in exp.achievements limit:2 %}
                        <div class="achievement">
                            <i class="fas fa-check-circle"></i>
                            {{ achievement }}
                        </div>
                        {% endfor %}
                    </div>
                </div>
            </div>
            {% endfor %}
        </div>
        <div class="timeline-footer">
            <a href="{{ '/about' | relative_url }}" class="btn btn-outline">
                Vedi esperienza completa
            </a>
        </div>
    </div>
</section>

<!-- Blog Preview -->
<section class="blog-preview">
    <div class="container">
        <div class="section-header">
            <h2 class="section-title">Ultimi Articoli</h2>
            <a href="{{ '/blog' | relative_url }}" class="view-all-link">
                Vedi tutti gli articoli <i class="fas fa-arrow-right"></i>
            </a>
        </div>
        
        <div class="blog-grid">
            {% for post in site.posts limit:3 %}
            <article class="blog-card">
                {% if post.image %}
                <div class="blog-image">
                    <img src="{{ post.image | relative_url }}" 
                         alt="{{ post.title }}" 
                         loading="lazy">
                </div>
                {% endif %}
                
                <div class="blog-content">
                    <div class="blog-meta">
                        <time class="blog-date" datetime="{{ post.date }}">
                            {{ post.date | date: "%d %B %Y" }}
                        </time>
                        <span class="blog-category">{{ post.category }}</span>
                    </div>
                    
                    <h3 class="blog-title">
                        <a href="{{ post.url | relative_url }}">{{ post.title }}</a>
                    </h3>
                    
                    <p class="blog-excerpt">{{ post.excerpt | strip_html | truncatewords: 20 }}</p>
                    
                    <div class="blog-tags">
                        {% for tag in post.tags limit:3 %}
                        <span class="tag">{{ tag }}</span>
                        {% endfor %}
                    </div>
                    
                    <a href="{{ post.url | relative_url }}" class="read-more">
                        Leggi di più <i class="fas fa-arrow-right"></i>
                    </a>
                </div>
            </article>
            {% endfor %}
        </div>
    </div>
</section>

<!-- Contact CTA -->
<section class="contact-cta">
    <div class="container">
        <div class="cta-content">
            <h2 class="cta-title">Hai un progetto in mente?</h2>
            <p class="cta-description">
                Sono sempre interessato a nuove opportunità e collaborazioni interessanti.
                Parliamo del tuo prossimo progetto!
            </p>
            <div class="cta-actions">
                <a href="{{ '/contact' | relative_url }}" class="btn btn-primary">
                    <i class="fas fa-envelope"></i>
                    Iniziamo a parlare
                </a>
                <a href="{{ '/assets/documents/john-smith-cv.pdf' | relative_url }}" 
                   class="btn btn-outline" 
                   download>
                    <i class="fas fa-download"></i>
                    Scarica CV
                </a>
            </div>
        </div>
        
        <div class="cta-decoration">
            <div class="decoration-shape"></div>
        </div>
    </div>
</section>

<!-- JavaScript for animations and interactions -->
<script>
document.addEventListener('DOMContentLoaded', function() {
    // Smooth scroll for internal links
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
    
    // Intersection Observer for animations
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -50px 0px'
    };
    
    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.classList.add('animate-in');
            }
        });
    }, observerOptions);
    
    // Observe elements for animation
    document.querySelectorAll('.skill-card, .project-card, .timeline-item, .blog-card').forEach(el => {
        observer.observe(el);
    });
    
    // Typed effect for hero subtitle
    const heroSubtitle = document.querySelector('.hero-subtitle');
    if (heroSubtitle) {
        const text = heroSubtitle.textContent;
        heroSubtitle.textContent = '';
        let i = 0;
        
        function typeWriter() {
            if (i < text.length) {
                heroSubtitle.textContent += text.charAt(i);
                i++;
                setTimeout(typeWriter, 100);
            }
        }
        
        setTimeout(typeWriter, 1000);
    }
});
</script>
```

### 4. Dati Skills (`_data/skills.yml`)

```yaml
main:
  - name: "Frontend Development"
    icon: "fas fa-laptop-code"
    description: "Sviluppo interfacce utente moderne e responsive"
    technologies:
      - "React"
      - "Vue.js"
      - "TypeScript"
      - "Sass/SCSS"
      - "Tailwind CSS"
      - "Next.js"
  
  - name: "Backend Development"
    icon: "fas fa-server"
    description: "Architetture scalabili e API performanti"
    technologies:
      - "Node.js"
      - "Express.js"
      - "Python"
      - "PostgreSQL"
      - "MongoDB"
      - "Redis"
  
  - name: "Cloud & DevOps"
    icon: "fas fa-cloud"
    description: "Deployment e gestione infrastrutture cloud"
    technologies:
      - "AWS"
      - "Docker"
      - "Kubernetes"
      - "CI/CD"
      - "Terraform"
      - "Monitoring"

technical:
  frontend:
    - name: "React"
      level: 95
      years: 4
    - name: "TypeScript"
      level: 90
      years: 3
    - name: "Vue.js"
      level: 85
      years: 2
    - name: "CSS/SASS"
      level: 95
      years: 5
  
  backend:
    - name: "Node.js"
      level: 92
      years: 4
    - name: "Python"
      level: 88
      years: 3
    - name: "PostgreSQL"
      level: 85
      years: 3
    - name: "MongoDB"
      level: 80
      years: 2
  
  tools:
    - name: "Git"
      level: 95
      years: 5
    - name: "Docker"
      level: 88
      years: 3
    - name: "AWS"
      level: 85
      years: 2
    - name: "Jest"
      level: 90
      years: 3

soft_skills:
  - "Problem Solving"
  - "Team Leadership"
  - "Agile/Scrum"
  - "Code Review"
  - "Mentoring"
  - "Technical Writing"
```

### 5. Progetto Example (`_projects/ecommerce-platform.md`)

```yaml
---
title: "E-Commerce Platform"
description: "Piattaforma e-commerce completa con microservizi"
image: "/assets/images/projects/ecommerce-platform.jpg"
category: "Full Stack"
technologies:
  - "React"
  - "Node.js"
  - "PostgreSQL"
  - "Redis"
  - "Docker"
  - "AWS"
demo_url: "https://demo-ecommerce.johnsmith.dev"
github_url: "https://github.com/johnsmith/ecommerce-platform"
featured: true
status: "Completed"
date: 2024-03-15
client: "TechCorp"
duration: "6 mesi"
team_size: 4
role: "Full Stack Lead Developer"
---

## Panoramica del Progetto

Ho sviluppato una piattaforma e-commerce enterprise scalabile per TechCorp, gestendo un team di 4 sviluppatori. La piattaforma supporta oltre 10.000 prodotti e gestisce 1000+ ordini giornalieri.

### Sfide Affrontate

- **Scalabilità**: Necessità di gestire picchi di traffico durante promozioni
- **Performance**: Tempi di caricamento sotto i 2 secondi per tutte le pagine
- **Sicurezza**: Implementazione PCI DSS compliance per pagamenti
- **UX**: Esperienza utente fluida su desktop e mobile

### Soluzioni Implementate

#### Architettura Microservizi
```javascript
// API Gateway con rate limiting
const rateLimit = require('express-rate-limit');
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minuti
  max: 100 // massimo 100 richieste per IP
});

app.use('/api/', limiter);
```

#### Caching Avanzato
```javascript
// Redis per session e cache prodotti
const redis = require('redis');
const client = redis.createClient({
  host: process.env.REDIS_HOST,
  port: process.env.REDIS_PORT
});

// Cache prodotti per 1 ora
const cacheProducts = async (categoryId) => {
  const cacheKey = `products:${categoryId}`;
  const cached = await client.get(cacheKey);
  
  if (cached) {
    return JSON.parse(cached);
  }
  
  const products = await Product.findByCategory(categoryId);
  await client.setex(cacheKey, 3600, JSON.stringify(products));
  return products;
};
```

#### Sistema di Pagamenti Sicuro
```javascript
// Integrazione Stripe con webhook validation
const stripe = require('stripe')(process.env.STRIPE_SECRET_KEY);

const handlePaymentSuccess = async (session) => {
  const order = await Order.findById(session.metadata.order_id);
  await order.updateStatus('paid');
  await sendConfirmationEmail(order);
};
```

### Risultati Ottenuti

- ✅ **Performance**: 98% Google PageSpeed Score
- ✅ **Uptime**: 99.9% availability
- ✅ **Conversione**: +35% rispetto alla piattaforma precedente
- ✅ **Mobile**: 100% responsive design
- ✅ **SEO**: Primo posto per keyword target

### Tecnologie Utilizzate

**Frontend**:
- React 18 con Hooks e Context API
- TypeScript per type safety
- Styled Components per styling
- React Query per state management
- React Testing Library per unit test

**Backend**:
- Node.js con Express.js
- PostgreSQL con Sequelize ORM
- Redis per caching e sessioni
- JWT per autenticazione
- Jest per testing

**Infrastructure**:
- AWS ECS per container orchestration
- AWS RDS per database
- AWS S3 per static assets
- CloudFront CDN
- AWS Lambda per background tasks

### Metrics e Monitoring

```javascript
// Prometheus metrics integration
const prometheus = require('prom-client');

const httpRequestDuration = new prometheus.Histogram({
  name: 'http_request_duration_seconds',
  help: 'Duration of HTTP requests in seconds',
  labelNames: ['method', 'route', 'status']
});

// Middleware per tracking
app.use((req, res, next) => {
  const start = Date.now();
  res.on('finish', () => {
    const duration = (Date.now() - start) / 1000;
    httpRequestDuration
      .labels(req.method, req.route?.path, res.statusCode)
      .observe(duration);
  });
  next();
});
```

### Screenshots

![Homepage]({{ '/assets/images/projects/ecommerce-home.jpg' | relative_url }})
*Homepage responsive con hero section e prodotti in evidenza*

![Product Page]({{ '/assets/images/projects/ecommerce-product.jpg' | relative_url }})
*Pagina prodotto con gallery interattiva e recensioni*

![Checkout Flow]({{ '/assets/images/projects/ecommerce-checkout.jpg' | relative_url }})
*Processo di checkout multi-step ottimizzato*

### Lezioni Apprese

1. **Caching Strategy**: L'implementazione di un sistema di cache multi-livello ha ridotto i tempi di risposta del 60%
2. **Database Optimization**: L'uso di indici compositi ha migliorato le query di ricerca del 80%
3. **Error Handling**: Un sistema robusto di error handling ha ridotto i crash del 95%
4. **Team Communication**: L'uso di daily standup e code review ha migliorato la qualità del codice

### Prossimi Sviluppi

- [ ] Implementazione Progressive Web App (PWA)
- [ ] Sistema di raccomandazioni AI-powered
- [ ] Integrazione con chatbot per customer service
- [ ] Advanced analytics e A/B testing
```

### 6. CSS Moderno (`assets/css/main.scss`)

```scss
// Variables
:root {
  --primary-color: #2563eb;
  --primary-dark: #1d4ed8;
  --secondary-color: #64748b;
  --accent-color: #f59e0b;
  --text-primary: #1e293b;
  --text-secondary: #64748b;
  --text-light: #94a3b8;
  --bg-primary: #ffffff;
  --bg-secondary: #f8fafc;
  --bg-dark: #0f172a;
  --border-color: #e2e8f0;
  --shadow-sm: 0 1px 2px 0 rgba(0, 0, 0, 0.05);
  --shadow-md: 0 4px 6px -1px rgba(0, 0, 0, 0.1);
  --shadow-lg: 0 10px 15px -3px rgba(0, 0, 0, 0.1);
  --radius-sm: 0.375rem;
  --radius-md: 0.5rem;
  --radius-lg: 0.75rem;
}

// Base styles
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

html {
  scroll-behavior: smooth;
}

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, sans-serif;
  font-size: 16px;
  line-height: 1.6;
  color: var(--text-primary);
  background-color: var(--bg-primary);
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

// Typography
h1, h2, h3, h4, h5, h6 {
  font-weight: 600;
  line-height: 1.3;
  margin-bottom: 1rem;
}

h1 { font-size: 3rem; }
h2 { font-size: 2.5rem; }
h3 { font-size: 2rem; }
h4 { font-size: 1.5rem; }
h5 { font-size: 1.25rem; }
h6 { font-size: 1.125rem; }

p {
  margin-bottom: 1rem;
  color: var(--text-secondary);
}

a {
  color: var(--primary-color);
  text-decoration: none;
  transition: color 0.2s ease;
  
  &:hover {
    color: var(--primary-dark);
  }
}

// Utility classes
.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 0 2rem;
  
  @media (max-width: 768px) {
    padding: 0 1rem;
  }
}

.section-title {
  font-size: 2.5rem;
  font-weight: 700;
  text-align: center;
  margin-bottom: 3rem;
  color: var(--text-primary);
  
  @media (max-width: 768px) {
    font-size: 2rem;
    margin-bottom: 2rem;
  }
}

.highlight {
  background: linear-gradient(120deg, var(--primary-color), var(--accent-color));
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  background-clip: text;
}

// Buttons
.btn {
  display: inline-flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.75rem 1.5rem;
  border: none;
  border-radius: var(--radius-md);
  font-weight: 500;
  text-decoration: none;
  cursor: pointer;
  transition: all 0.2s ease;
  
  &.btn-primary {
    background-color: var(--primary-color);
    color: white;
    
    &:hover {
      background-color: var(--primary-dark);
      transform: translateY(-2px);
      box-shadow: var(--shadow-lg);
    }
  }
  
  &.btn-outline {
    background-color: transparent;
    color: var(--primary-color);
    border: 2px solid var(--primary-color);
    
    &:hover {
      background-color: var(--primary-color);
      color: white;
    }
  }
}

// Hero Section
.hero {
  padding: 8rem 0 4rem;
  background: linear-gradient(135deg, var(--bg-primary) 0%, var(--bg-secondary) 100%);
  position: relative;
  overflow: hidden;
  
  &::before {
    content: '';
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background: url('/assets/images/hero-pattern.svg') no-repeat center;
    background-size: cover;
    opacity: 0.05;
  }
  
  .hero-content {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 4rem;
    align-items: center;
    position: relative;
    z-index: 1;
    
    @media (max-width: 968px) {
      grid-template-columns: 1fr;
      gap: 2rem;
      text-align: center;
    }
  }
  
  .hero-title {
    font-size: 4rem;
    font-weight: 800;
    line-height: 1.1;
    margin-bottom: 1rem;
    
    @media (max-width: 768px) {
      font-size: 2.5rem;
    }
  }
  
  .hero-subtitle {
    font-size: 1.5rem;
    color: var(--text-secondary);
    margin-bottom: 1.5rem;
    
    @media (max-width: 768px) {
      font-size: 1.25rem;
    }
  }
  
  .hero-description {
    font-size: 1.125rem;
    color: var(--text-secondary);
    margin-bottom: 2rem;
    line-height: 1.7;
  }
  
  .hero-actions {
    display: flex;
    gap: 1rem;
    
    @media (max-width: 768px) {
      flex-direction: column;
      align-items: center;
    }
  }
  
  .profile-image {
    width: 400px;
    height: 400px;
    border-radius: 50%;
    object-fit: cover;
    border: 8px solid white;
    box-shadow: var(--shadow-lg);
    position: relative;
    z-index: 2;
    
    @media (max-width: 768px) {
      width: 300px;
      height: 300px;
    }
  }
  
  .scroll-indicator {
    position: absolute;
    bottom: 2rem;
    left: 50%;
    transform: translateX(-50%);
    color: var(--text-light);
    animation: bounce 2s infinite;
    
    i {
      font-size: 1.5rem;
    }
  }
}

@keyframes bounce {
  0%, 20%, 50%, 80%, 100% {
    transform: translateX(-50%) translateY(0);
  }
  40% {
    transform: translateX(-50%) translateY(-10px);
  }
  60% {
    transform: translateX(-50%) translateY(-5px);
  }
}

// Skills Section
.skills-overview {
  padding: 5rem 0;
  background-color: var(--bg-secondary);
  
  .skills-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 2rem;
  }
  
  .skill-card {
    background: white;
    padding: 2rem;
    border-radius: var(--radius-lg);
    box-shadow: var(--shadow-sm);
    text-align: center;
    transition: transform 0.2s ease, box-shadow 0.2s ease;
    border: 1px solid var(--border-color);
    
    &:hover {
      transform: translateY(-4px);
      box-shadow: var(--shadow-lg);
    }
    
    .skill-icon {
      width: 80px;
      height: 80px;
      margin: 0 auto 1.5rem;
      background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      
      i {
        font-size: 2rem;
        color: white;
      }
    }
    
    .skill-name {
      font-size: 1.5rem;
      margin-bottom: 1rem;
      color: var(--text-primary);
    }
    
    .skill-description {
      margin-bottom: 1.5rem;
      color: var(--text-secondary);
    }
    
    .tech-tag {
      display: inline-block;
      background-color: var(--bg-secondary);
      color: var(--text-secondary);
      padding: 0.25rem 0.75rem;
      border-radius: var(--radius-sm);
      font-size: 0.875rem;
      margin: 0.25rem;
    }
  }
}

// Projects Section
.featured-projects {
  padding: 5rem 0;
  
  .section-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 3rem;
    
    @media (max-width: 768px) {
      flex-direction: column;
      gap: 1rem;
      text-align: center;
    }
  }
  
  .view-all-link {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    font-weight: 500;
    color: var(--primary-color);
    transition: gap 0.2s ease;
    
    &:hover {
      gap: 1rem;
    }
  }
  
  .projects-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
    gap: 2rem;
  }
  
  .project-card {
    background: white;
    border-radius: var(--radius-lg);
    overflow: hidden;
    box-shadow: var(--shadow-sm);
    transition: transform 0.2s ease, box-shadow 0.2s ease;
    border: 1px solid var(--border-color);
    
    &:hover {
      transform: translateY(-4px);
      box-shadow: var(--shadow-lg);
      
      .project-overlay {
        opacity: 1;
      }
    }
    
    .project-image {
      position: relative;
      height: 200px;
      overflow: hidden;
      
      img {
        width: 100%;
        height: 100%;
        object-fit: cover;
        transition: transform 0.3s ease;
      }
      
      &:hover img {
        transform: scale(1.05);
      }
    }
    
    .project-overlay {
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background: rgba(0, 0, 0, 0.8);
      display: flex;
      align-items: center;
      justify-content: center;
      opacity: 0;
      transition: opacity 0.3s ease;
      
      .project-links {
        display: flex;
        gap: 1rem;
      }
      
      .project-link {
        display: flex;
        align-items: center;
        gap: 0.5rem;
        padding: 0.5rem 1rem;
        background: white;
        color: var(--text-primary);
        border-radius: var(--radius-sm);
        text-decoration: none;
        font-weight: 500;
        transition: transform 0.2s ease;
        
        &:hover {
          transform: scale(1.05);
        }
        
        &.demo {
          background: var(--primary-color);
          color: white;
        }
      }
    }
    
    .project-content {
      padding: 1.5rem;
    }
    
    .project-meta {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 1rem;
      
      .project-category {
        background: var(--primary-color);
        color: white;
        padding: 0.25rem 0.75rem;
        border-radius: var(--radius-sm);
        font-size: 0.875rem;
        font-weight: 500;
      }
      
      .project-date {
        color: var(--text-light);
        font-size: 0.875rem;
      }
    }
    
    .project-title {
      font-size: 1.25rem;
      margin-bottom: 1rem;
      
      a {
        color: var(--text-primary);
        text-decoration: none;
        
        &:hover {
          color: var(--primary-color);
        }
      }
    }
    
    .project-description {
      color: var(--text-secondary);
      margin-bottom: 1rem;
      line-height: 1.6;
    }
    
    .project-technologies {
      display: flex;
      flex-wrap: wrap;
      gap: 0.5rem;
    }
  }
}

// Animations
.animate-in {
  animation: slideInUp 0.6s ease forwards;
}

@keyframes slideInUp {
  from {
    opacity: 0;
    transform: translateY(30px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

// Responsive Design
@media (max-width: 768px) {
  .hero {
    padding: 4rem 0 2rem;
  }
  
  .skills-overview,
  .featured-projects {
    padding: 3rem 0;
  }
  
  .projects-grid {
    grid-template-columns: 1fr;
  }
  
  .skill-card,
  .project-card {
    margin-bottom: 1rem;
  }
}

// Dark mode support
@media (prefers-color-scheme: dark) {
  :root {
    --text-primary: #f1f5f9;
    --text-secondary: #cbd5e1;
    --text-light: #64748b;
    --bg-primary: #0f172a;
    --bg-secondary: #1e293b;
    --border-color: #334155;
  }
  
  .skill-card,
  .project-card {
    background: var(--bg-secondary);
    border-color: var(--border-color);
  }
}
```

## Deployment e SEO

### 7. GitHub Actions per Deployment

```yaml
# .github/workflows/deploy.yml
name: Deploy to GitHub Pages

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build-and-deploy:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout
      uses: actions/checkout@v3
      
    - name: Setup Ruby
      uses: ruby/setup-ruby@v1
      with:
        ruby-version: 3.0
        bundler-cache: true
        
    - name: Install dependencies
      run: bundle install
      
    - name: Build site
      run: bundle exec jekyll build
      env:
        JEKYLL_ENV: production
        
    - name: Test site
      run: |
        bundle exec htmlproofer ./_site --disable-external
        
    - name: Deploy to GitHub Pages
      if: github.ref == 'refs/heads/main'
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./_site
```

### 8. SEO Optimization

```html
<!-- _includes/seo.html -->
<meta property="og:type" content="website">
<meta property="og:title" content="{{ page.title | default: site.title }}">
<meta property="og:description" content="{{ page.description | default: site.description }}">
<meta property="og:url" content="{{ page.url | absolute_url }}">
<meta property="og:site_name" content="{{ site.title }}">
<meta property="og:image" content="{{ page.image | default: '/assets/images/og-default.jpg' | absolute_url }}">

<meta name="twitter:card" content="summary_large_image">
<meta name="twitter:site" content="@{{ site.twitter_username }}">
<meta name="twitter:creator" content="@{{ site.twitter_username }}">

<link rel="canonical" href="{{ page.url | absolute_url }}">

<script type="application/ld+json">
{
  "@context": "https://schema.org",
  "@type": "Person",
  "name": "{{ site.author }}",
  "url": "{{ site.url }}",
  "jobTitle": "Full Stack Developer",
  "worksFor": {
    "@type": "Organization",
    "name": "Freelancer"
  },
  "sameAs": [
    {% for social in site.social %}
    "{{ social.url }}"{% unless forloop.last %},{% endunless %}
    {% endfor %}
  ]
}
</script>
```

## Risultati Attesi

### Performance Metrics
- ✅ **Google PageSpeed**: 95+ score
- ✅ **GTmetrix**: A grade
- ✅ **Load Time**: <2 secondi
- ✅ **Mobile Friendly**: 100% responsive

### SEO Results
- ✅ **Meta Tags**: Complete coverage
- ✅ **Schema Markup**: Structured data
- ✅ **Social Sharing**: OG tags ottimizzati
- ✅ **Sitemap**: Automaticamente generata

### Features Implementate
- ✅ **Responsive Design**: Mobile-first approach
- ✅ **Dark Mode**: Sistema prefers-color-scheme
- ✅ **Animations**: Intersection Observer API
- ✅ **Performance**: Lazy loading, ottimizzazione immagini
- ✅ **Accessibility**: ARIA labels, contrast ottimizzato

---

**Portfolio Live**: https://johnsmith.github.io  
**Repository**: https://github.com/johnsmith/johnsmith.github.io  
**Build Time**: ~2 minuti  
**Update Frequency**: Automatic su push
