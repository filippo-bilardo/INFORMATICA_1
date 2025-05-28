# Jekyll Basics: Guida Completa al Generatore di Siti Statici

## Introduzione

Jekyll è un generatore di siti statici scritto in Ruby che è il motore dietro GitHub Pages. Trasforma file Markdown e HTML in siti web completamente statici, perfetti per blog, documentazione e portfolio.

## Cos'è Jekyll

### Definizione
Jekyll è un generatore che:
- Converte Markdown in HTML
- Elabora template Liquid
- Gestisce temi e layout
- Supporta plugin e estensioni
- Genera siti ottimizzati per le performance

### Filosofia "Convention over Configuration"
Jekyll funziona con convenzioni predefinite:
- `_posts/` per articoli del blog
- `_layouts/` per template HTML
- `_includes/` per componenti riutilizzabili
- `_sass/` per file SCSS/Sass
- `_config.yml` per configurazioni globali

## Struttura di un Progetto Jekyll

### Directory Structure
```
mio-sito-jekyll/
├── _config.yml                    # Configurazione principale
├── _data/                         # File di dati (YAML, JSON, CSV)
│   ├── navigation.yml
│   └── team.yml
├── _drafts/                       # Bozze dei post
│   └── post-in-lavorazione.md
├── _includes/                     # Componenti HTML riutilizzabili
│   ├── head.html
│   ├── header.html
│   ├── footer.html
│   └── analytics.html
├── _layouts/                      # Template HTML
│   ├── default.html
│   ├── page.html
│   ├── post.html
│   └── home.html
├── _posts/                        # Articoli del blog
│   ├── 2025-05-28-primo-post.md
│   └── 2025-05-27-secondo-post.md
├── _sass/                         # File SCSS/Sass
│   ├── _base.scss
│   ├── _layout.scss
│   └── _syntax-highlighting.scss
├── _site/                         # Output generato (auto-generato)
├── assets/                        # Risorse statiche
│   ├── css/
│   │   └── style.scss
│   ├── js/
│   │   └── main.js
│   └── images/
│       └── logo.png
├── _pages/                        # Pagine extra (opzionale)
│   ├── about.md
│   └── contact.md
├── index.html                     # Homepage
├── Gemfile                        # Dipendenze Ruby
├── Gemfile.lock                   # Lock delle versioni
└── README.md                      # Documentazione
```

## Front Matter

### Cos'è il Front Matter
Il Front Matter è metadata YAML che appare all'inizio dei file:
```markdown
---
layout: post
title: "Titolo del Post"
date: 2025-05-28 14:30:00 +0200
categories: [blog, tutorial]
tags: [jekyll, github-pages]
author: Il Mio Nome
permalink: /blog/titolo-del-post/
excerpt: "Breve descrizione del post"
image: /assets/images/post-cover.jpg
published: true
---

# Contenuto del post inizia qui

Il resto del contenuto in Markdown...
```

### Variabili Front Matter Standard
```yaml
---
# Layout e template
layout: post                    # Layout da usare
permalink: /custom-url/         # URL personalizzato

# Metadati contenuto
title: "Titolo Pagina"         # Titolo della pagina
date: 2025-05-28 10:00:00      # Data pubblicazione
author: "Nome Autore"          # Autore del contenuto

# Categorizzazione
categories: [cat1, cat2]       # Categorie (influenzano URL)
tags: [tag1, tag2, tag3]       # Tag per classificazione

# SEO e social
description: "Meta description"  # Descrizione per SEO
keywords: [word1, word2]        # Keywords per SEO
image: /path/to/image.jpg       # Immagine social media
excerpt: "Riassunto breve"      # Estratto per liste

# Controllo pubblicazione
published: true                 # false per nascondere
draft: false                   # true per bozze

# Variabili custom
reading_time: 5                # Tempo lettura stimato
difficulty: intermediate        # Livello difficoltà
---
```

## Liquid Template Engine

### Sintassi Base
Jekyll usa Liquid per template dinamici:

```liquid
<!-- Variabili -->
{{ site.title }}               <!-- Titolo del sito -->
{{ page.title }}               <!-- Titolo della pagina -->
{{ content }}                  <!-- Contenuto della pagina -->

<!-- Filtri -->
{{ page.date | date: "%B %d, %Y" }}           <!-- Formato data -->
{{ page.title | upcase }}                     <!-- Maiuscolo -->
{{ content | strip_html | truncate: 150 }}    <!-- Testo senza HTML -->

<!-- Condizioni -->
{% if page.layout == "post" %}
  <p>Questo è un post del blog</p>
{% endif %}

{% unless page.published %}
  <p>Questa pagina non è pubblicata</p>
{% endunless %}

<!-- Loop -->
{% for post in site.posts %}
  <h3>{{ post.title }}</h3>
  <p>{{ post.excerpt }}</p>
{% endfor %}

<!-- Include -->
{% include header.html %}
{% include footer.html param="valore" %}
```

### Variabili Globali Jekyll
```liquid
<!-- Variabili del sito -->
{{ site.title }}               <!-- Da _config.yml -->
{{ site.description }}         <!-- Da _config.yml -->
{{ site.url }}                 <!-- URL base del sito -->
{{ site.posts }}               <!-- Tutti i post -->
{{ site.pages }}               <!-- Tutte le pagine -->
{{ site.time }}                <!-- Timestamp build -->

<!-- Variabili della pagina -->
{{ page.title }}               <!-- Titolo pagina corrente -->
{{ page.content }}             <!-- Contenuto pagina -->
{{ page.url }}                 <!-- URL pagina -->
{{ page.date }}                <!-- Data pagina -->
{{ page.categories }}          <!-- Categorie pagina -->
{{ page.tags }}                <!-- Tag pagina -->

<!-- Variabili del post -->
{{ post.title }}               <!-- In loop sui post -->
{{ post.excerpt }}             <!-- Estratto automatico -->
{{ post.previous }}            <!-- Post precedente -->
{{ post.next }}                <!-- Post successivo -->
```

## Layouts e Template

### Layout Base (default.html)
```html
<!DOCTYPE html>
<html lang="{{ site.lang | default: 'it' }}">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <title>
      {% if page.title %}{{ page.title }} - {% endif %}{{ site.title }}
    </title>
    
    <meta name="description" content="{{ page.excerpt | default: site.description | strip_html | normalize_whitespace | truncate: 160 | escape }}">
    
    {% if page.tags %}
      <meta name="keywords" content="{{ page.tags | join: ', ' | escape }}">
    {% endif %}
    
    <link rel="canonical" href="{{ page.url | replace:'index.html','' | absolute_url }}">
    
    <!-- Open Graph -->
    <meta property="og:type" content="{% if page.layout == 'post' %}article{% else %}website{% endif %}">
    <meta property="og:title" content="{{ page.title | default: site.title | escape }}">
    <meta property="og:description" content="{{ page.excerpt | default: site.description | strip_html | normalize_whitespace | truncate: 160 | escape }}">
    <meta property="og:url" content="{{ page.url | absolute_url }}">
    <meta property="og:site_name" content="{{ site.title | escape }}">
    
    {% if page.image %}
      <meta property="og:image" content="{{ page.image | absolute_url }}">
    {% endif %}
    
    <!-- CSS -->
    <link rel="stylesheet" href="{{ "/assets/css/style.css" | relative_url }}">
    
    <!-- Favicon -->
    <link rel="icon" type="image/x-icon" href="{{ "/assets/images/favicon.ico" | relative_url }}">
    
    <!-- RSS Feed -->
    {% feed_meta %}
  </head>

  <body class="{{ page.layout | default: layout.layout }}">
    {% include header.html %}
    
    <main class="main-content" role="main">
      {{ content }}
    </main>
    
    {% include footer.html %}
    
    <!-- JavaScript -->
    <script src="{{ "/assets/js/main.js" | relative_url }}"></script>
    
    {% if site.google_analytics %}
      {% include analytics.html %}
    {% endif %}
  </body>
</html>
```

### Layout Post (post.html)
```html
---
layout: default
---

<article class="post" itemscope itemtype="http://schema.org/BlogPosting">
  <header class="post-header">
    <h1 class="post-title" itemprop="name headline">{{ page.title | escape }}</h1>
    
    <div class="post-meta">
      <time datetime="{{ page.date | date_to_xmlschema }}" itemprop="datePublished">
        {{ page.date | date: "%B %d, %Y" }}
      </time>
      
      {% if page.author %}
        <span itemprop="author" itemscope itemtype="http://schema.org/Person">
          <span itemprop="name">{{ page.author }}</span>
        </span>
      {% endif %}
      
      {% if page.reading_time %}
        <span class="reading-time">{{ page.reading_time }} min di lettura</span>
      {% endif %}
    </div>
    
    {% if page.categories.size > 0 %}
      <div class="post-categories">
        {% for category in page.categories %}
          <span class="category">{{ category }}</span>
        {% endfor %}
      </div>
    {% endif %}
  </header>

  <div class="post-content" itemprop="articleBody">
    {{ content }}
  </div>

  {% if page.tags.size > 0 %}
    <div class="post-tags">
      <strong>Tag:</strong>
      {% for tag in page.tags %}
        <span class="tag">#{{ tag }}</span>
      {% endfor %}
    </div>
  {% endif %}

  <!-- Navigazione tra post -->
  <nav class="post-navigation">
    {% if page.previous %}
      <a href="{{ page.previous.url | relative_url }}" class="prev-post">
        ← {{ page.previous.title }}
      </a>
    {% endif %}
    
    {% if page.next %}
      <a href="{{ page.next.url | relative_url }}" class="next-post">
        {{ page.next.title }} →
      </a>
    {% endif %}
  </nav>
</article>
```

### Include Header (header.html)
```html
<header class="site-header">
  <div class="wrapper">
    <div class="header-content">
      <a class="site-title" href="{{ "/" | relative_url }}">
        {% if site.logo %}
          <img src="{{ site.logo | relative_url }}" alt="{{ site.title }}" class="site-logo">
        {% else %}
          {{ site.title | escape }}
        {% endif %}
      </a>

      <nav class="site-nav">
        <input type="checkbox" id="nav-trigger" class="nav-trigger">
        <label for="nav-trigger" class="menu-icon">
          <span></span>
          <span></span>
          <span></span>
        </label>

        <div class="trigger">
          {% assign pages = site.pages | where: "layout", "page" | sort: "order" %}
          {% for page in pages %}
            {% if page.title %}
              <a class="page-link" href="{{ page.url | relative_url }}">
                {{ page.title | escape }}
              </a>
            {% endif %}
          {% endfor %}
          
          <!-- Link esterni -->
          <a class="page-link" href="{{ site.github_url }}" target="_blank">GitHub</a>
        </div>
      </nav>
    </div>
  </div>
</header>
```

## Data Files

### Uso dei Data Files
I file in `_data/` permettono di separare contenuto da template:

#### _data/navigation.yml
```yaml
main:
  - title: "Home"
    url: "/"
  - title: "About"
    url: "/about/"
  - title: "Portfolio"
    url: "/portfolio/"
  - title: "Blog"
    url: "/blog/"
  - title: "Contatti"
    url: "/contact/"

social:
  - name: "GitHub"
    url: "https://github.com/username"
    icon: "github"
  - name: "Twitter"
    url: "https://twitter.com/username"
    icon: "twitter"
  - name: "LinkedIn"
    url: "https://linkedin.com/in/username"
    icon: "linkedin"
```

#### _data/projects.yml
```yaml
featured:
  - title: "E-commerce Platform"
    description: "Piattaforma e-commerce completa con React e Node.js"
    image: "/assets/images/projects/ecommerce.jpg"
    tech: [React, Node.js, MongoDB, Stripe]
    github: "https://github.com/username/ecommerce"
    demo: "https://demo.example.com"
    featured: true
    
  - title: "Mobile App"
    description: "App mobile per gestione produttività"
    image: "/assets/images/projects/mobile-app.jpg"
    tech: [React Native, Firebase, Redux]
    github: "https://github.com/username/mobile-app"
    store: "https://play.google.com/store/apps/details?id=com.example.app"
    featured: true

others:
  - title: "Portfolio Website"
    description: "Sito portfolio personale con Jekyll"
    tech: [Jekyll, SCSS, JavaScript]
    github: "https://github.com/username/portfolio"
```

#### Utilizzo nei Template
```liquid
<!-- Navigazione da _data/navigation.yml -->
<nav>
  {% for item in site.data.navigation.main %}
    <a href="{{ item.url | relative_url }}">{{ item.title }}</a>
  {% endfor %}
</nav>

<!-- Social links -->
<div class="social-links">
  {% for social in site.data.navigation.social %}
    <a href="{{ social.url }}" target="_blank" class="social-link">
      <i class="icon-{{ social.icon }}"></i>
      {{ social.name }}
    </a>
  {% endfor %}
</div>

<!-- Progetti featured -->
<section class="featured-projects">
  {% for project in site.data.projects.featured %}
    <div class="project-card">
      <h3>{{ project.title }}</h3>
      <p>{{ project.description }}</p>
      
      <div class="tech-stack">
        {% for tech in project.tech %}
          <span class="tech-tag">{{ tech }}</span>
        {% endfor %}
      </div>
      
      <div class="project-links">
        <a href="{{ project.github }}" target="_blank">Codice</a>
        {% if project.demo %}
          <a href="{{ project.demo }}" target="_blank">Demo</a>
        {% endif %}
      </div>
    </div>
  {% endfor %}
</section>
```

## Collections

### Definizione Collections
Le Collections permettono di gestire contenuti simili oltre ai post:

#### _config.yml
```yaml
collections:
  projects:
    output: true
    permalink: /:collection/:name/
  tutorials:
    output: true
    permalink: /:collection/:title/
  team:
    output: false

defaults:
  - scope:
      path: ""
      type: "projects"
    values:
      layout: "project"
  - scope:
      path: ""
      type: "tutorials"
    values:
      layout: "tutorial"
```

#### _projects/ecommerce-site.md
```markdown
---
title: "E-commerce Platform"
description: "Piattaforma completa per vendite online"
tech_stack: [React, Node.js, MongoDB, Stripe]
github_url: "https://github.com/username/ecommerce"
demo_url: "https://demo.example.com"
image: "/assets/images/projects/ecommerce.jpg"
featured: true
status: "completed"
year: 2025
---

# E-commerce Platform

## Descrizione del Progetto

Questa piattaforma e-commerce completa include...

## Tecnologie Utilizzate

- **Frontend**: React, Redux, SCSS
- **Backend**: Node.js, Express, MongoDB
- **Pagamenti**: Stripe API
- **Deploy**: Heroku, Netlify

## Caratteristiche Principali

1. Gestione prodotti
2. Carrello della spesa
3. Sistema di pagamento
4. Dashboard amministrativa

## Sfide e Soluzioni

Descrivi le sfide tecniche affrontate...
```

#### Utilizzo delle Collections
```liquid
<!-- Lista progetti -->
{% assign featured_projects = site.projects | where: "featured", true %}
{% for project in featured_projects %}
  <div class="project-preview">
    <h3><a href="{{ project.url | relative_url }}">{{ project.title }}</a></h3>
    <p>{{ project.description }}</p>
    
    <div class="tech-stack">
      {% for tech in project.tech_stack %}
        <span class="tech">{{ tech }}</span>
      {% endfor %}
    </div>
  </div>
{% endfor %}

<!-- Filtro per anno -->
{% assign projects_2025 = site.projects | where: "year", 2025 %}
{% for project in projects_2025 %}
  <!-- Mostra progetti del 2025 -->
{% endfor %}
```

## Plugin e Estensioni

### Plugin Essenziali
```ruby
# Gemfile
group :jekyll_plugins do
  gem "jekyll-feed"              # RSS feed automatico
  gem "jekyll-sitemap"           # Sitemap XML
  gem "jekyll-seo-tag"           # Meta tag SEO
  gem "jekyll-paginate"          # Paginazione post
  gem "jekyll-archives"          # Archivi per categorie/tag
  gem "jekyll-redirect-from"     # Redirect URL
  gem "jekyll-last-modified-at"  # Data ultima modifica
end
```

### Configurazione Plugin
```yaml
# _config.yml
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag
  - jekyll-paginate
  - jekyll-archives

# Configurazione paginazione
paginate: 5
paginate_path: "/blog/page:num/"

# Configurazione archivi
jekyll-archives:
  enabled:
    - categories
    - tags
  layout: archive
  permalinks:
    category: '/category/:name/'
    tag: '/tag/:name/'

# Feed RSS
feed:
  excerpt_only: true
  collections:
    - projects
```

## Sass/SCSS Integration

### Struttura CSS
```scss
// assets/css/style.scss
---
---

@import "variables";
@import "base";
@import "layout";
@import "components";
@import "utilities";
```

#### _sass/_variables.scss
```scss
// Colori
$primary-color: #2c3e50;
$secondary-color: #3498db;
$accent-color: #e74c3c;
$text-color: #333;
$light-gray: #f8f9fa;
$medium-gray: #6c757d;
$dark-gray: #343a40;

// Typography
$font-family-base: 'Roboto', -apple-system, BlinkMacSystemFont, sans-serif;
$font-family-mono: 'Source Code Pro', monospace;
$font-size-base: 16px;
$line-height-base: 1.6;

// Spacing
$spacing-unit: 1rem;
$spacing-xs: $spacing-unit * 0.25;  // 4px
$spacing-sm: $spacing-unit * 0.5;   // 8px
$spacing-md: $spacing-unit;         // 16px
$spacing-lg: $spacing-unit * 2;     // 32px
$spacing-xl: $spacing-unit * 3;     // 48px

// Breakpoints
$mobile: 480px;
$tablet: 768px;
$desktop: 1024px;
$wide: 1200px;

// Border radius
$border-radius-sm: 4px;
$border-radius-md: 8px;
$border-radius-lg: 12px;
```

## Deployment e Ottimizzazioni

### Build Ottimizzato
```yaml
# _config.yml per produzione
markdown: kramdown
highlighter: rouge
kramdown:
  input: GFM
  syntax_highlighter: rouge

sass:
  style: compressed
  
compress_html:
  clippings: all
  comments: ["<!-- ", " -->"]
  endings: [html, head, body]
  
exclude:
  - Gemfile
  - Gemfile.lock
  - node_modules
  - vendor/bundle/
  - vendor/cache/
  - vendor/gems/
  - vendor/ruby/
  - package.json
  - package-lock.json
  - README.md
  - .gitignore
```

### Script Build Personalizzato
```bash
#!/bin/bash
# build.sh

echo "🏗️  Building Jekyll site..."

# Clean previous build
bundle exec jekyll clean

# Build for production
JEKYLL_ENV=production bundle exec jekyll build

# Optimize images (se hai imagemin installato)
if command -v imagemin &> /dev/null; then
  echo "🖼️  Optimizing images..."
  imagemin _site/assets/images/* --out-dir=_site/assets/images/
fi

# Generate sitemap timestamp
echo "📄 Updating sitemap timestamp..."
sed -i "s/<lastmod>.*<\/lastmod>/<lastmod>$(date -u +%Y-%m-%dT%H:%M:%S+00:00)<\/lastmod>/g" _site/sitemap.xml

echo "✅ Build complete!"
```

## Troubleshooting Comune

### Errore: "Liquid Exception"
```bash
# Escape caratteri speciali in Liquid
{{ "{{ questo verrà mostrato }}" }}

# Usa raw per blocchi di codice
{% raw %}
  {{ codice_senza_processing }}
{% endraw %}
```

### Errore: "Build failed - incompatible versions"
```bash
# Update gem dependencies
bundle update
bundle exec jekyll clean
bundle exec jekyll build
```

### Problemi di Performance
```yaml
# _config.yml - ottimizzazioni
incremental: true
profile: true
liquid:
  error_mode: strict
  strict_filters: true
  strict_variables: true
```

## Quiz di Autovalutazione

### Domanda 1
Qual è la convenzione per i nomi dei file post in Jekyll?
a) post-title.md
b) YYYY-MM-DD-title.md ✓
c) YYYY/MM/DD/title.md
d) title-YYYY-MM-DD.md

### Domanda 2
Dove si trova il contenuto in un layout Jekyll?
a) {{ page.content }}
b) {{ content }} ✓
c) {{ site.content }}
d) {{ layout.content }}

### Domanda 3
Quale directory contiene i file di dati in Jekyll?
a) /data/
b) /_data/ ✓
c) /assets/data/
d) /_content/

### Domanda 4
Come si include un file parziale in Jekyll?
a) {{ include "header.html" }}
b) {% include header.html %} ✓
c) {% import header.html %}
d) {{ render "header.html" }}

### Domanda 5
Quale plugin genera automaticamente un RSS feed?
a) jekyll-rss
b) jekyll-feed ✓
c) jekyll-xml
d) jekyll-atom

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 01-Pages Setup](./01-pages-setup.md)
- [➡️ 03-Documentation Practices](./03-documentation-practices.md)
