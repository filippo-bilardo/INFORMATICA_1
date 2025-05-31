# GitHub Pages Setup: Guida Completa

## Introduzione

GitHub Pages è un servizio di hosting statico gratuito fornito da GitHub che permette di pubblicare siti web direttamente dai repository. È ideale per documentazione, portfolio, blog e siti di progetto.

## Cos'è GitHub Pages

### Definizione
GitHub Pages è un servizio che:
- Converte automaticamente file Markdown in HTML
- Supporta Jekyll per generazione di siti statici
- Fornisce hosting gratuito con dominio `.github.io`
- Si integra perfettamente con il workflow Git
- Supporta domini personalizzati

### Vantaggi Principali
- **Gratuito**: Hosting illimitato per siti pubblici
- **Integrazione Git**: Deploy automatico ad ogni push
- **SSL**: Certificati HTTPS automatici
- **Jekyll**: Supporto nativo per generatori statici
- **Personalizzazione**: Temi e domini custom

## Tipi di GitHub Pages

### 1. User/Organization Pages
```bash
# Repository speciale: username.github.io
# URL finale: https://username.github.io
# Source: branch main o gh-pages
```

### 2. Project Pages
```bash
# Qualsiasi repository pubblico
# URL finale: https://username.github.io/repository-name
# Source: branch main, gh-pages, o cartella /docs
```

## Setup GitHub Pages

### Metodo 1: Repository Settings
1. **Vai nelle Impostazioni**
   ```
   Repository → Settings → Pages
   ```

2. **Seleziona Source**
   - Branch main (cartella root o /docs)
   - Branch gh-pages
   - GitHub Actions (metodo moderno)

3. **Configurazione Base**
   ```markdown
   Source: Deploy from a branch
   Branch: main
   Folder: / (root) o /docs
   ```

### Metodo 2: GitHub Actions (Raccomandato)
```yaml
# .github/workflows/pages.yml
name: Deploy to GitHub Pages

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

permissions:
  contents: read
  pages: write
  id-token: write

concurrency:
  group: "pages"
  cancel-in-progress: false

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
        
      - name: Setup Ruby
        uses: ruby/setup-ruby@v1
        with:
          ruby-version: '3.1'
          bundler-cache: true
          
      - name: Setup Pages
        uses: actions/configure-pages@v3
        
      - name: Build with Jekyll
        run: bundle exec jekyll build --baseurl "${{ steps.pages.outputs.base_path }}"
        env:
          JEKYLL_ENV: production
          
      - name: Upload artifact
        uses: actions/upload-pages-artifact@v2

  deploy:
    environment:
      name: github-pages
      url: ${{ steps.deployment.outputs.page_url }}
    runs-on: ubuntu-latest
    needs: build
    steps:
      - name: Deploy to GitHub Pages
        id: deployment
        uses: actions/deploy-pages@v2
```

## Configurazione di Base

### Struttura Directory
```
my-site/
├── _config.yml          # Configurazione Jekyll
├── index.md             # Homepage
├── about.md             # Pagina About
├── _posts/              # Blog posts
│   └── 2025-01-01-primo-post.md
├── _layouts/            # Template HTML
│   ├── default.html
│   └── post.html
├── _includes/           # Componenti riutilizzabili
│   ├── header.html
│   └── footer.html
├── assets/              # CSS, JS, immagini
│   ├── css/
│   ├── js/
│   └── images/
└── docs/                # Documentazione (opzionale)
```

### File _config.yml Base
```yaml
# Site settings
title: Il Mio Sito
email: esempio@email.com
description: >-
  Descrizione del sito che apparirà nei meta tag
  e nei risultati di ricerca.

baseurl: "" # subpath del sito, es. /blog
url: "https://username.github.io" # URL base

# Build settings
markdown: kramdown
highlighter: rouge
theme: minima

# Jekyll settings
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag

# Navigation
header_pages:
  - about.md
  - portfolio.md
  - blog.md

# Social
github_username: username
twitter_username: username
linkedin_username: username

# Google Analytics (opzionale)
google_analytics: G-MEASUREMENT_ID

# Exclude from processing
exclude:
  - Gemfile
  - Gemfile.lock
  - node_modules
  - README.md
```

### File Gemfile
```ruby
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
gem "webrick", "~> 1.7"

group :jekyll_plugins do
  gem "jekyll-feed"
  gem "jekyll-sitemap"
  gem "jekyll-seo-tag"
end
```

## Creazione Contenuti

### Homepage (index.md)
```markdown
---
layout: home
title: Home
---

# Benvenuto nel Mio Sito

Questo è il mio sito personale costruito con GitHub Pages.

## Ultimi Post

I miei articoli più recenti appariranno qui automaticamente.

## Chi Sono

Breve introduzione su di te e i tuoi progetti.
```

### Pagina About (about.md)
```markdown
---
layout: page
title: About
permalink: /about/
---

# Chi Sono

## La Mia Storia

Racconta la tua storia professionale...

## Skills

- Linguaggi di programmazione
- Framework e tecnologie
- Soft skills

## Contatti

- Email: [email@esempio.com](mailto:email@esempio.com)
- GitHub: [username](https://github.com/username)
- LinkedIn: [profilo](https://linkedin.com/in/username)
```

### Blog Post (_posts/2025-05-28-primo-post.md)
```markdown
---
layout: post
title: "Il Mio Primo Post"
date: 2025-05-28 10:00:00 +0200
categories: blog
tags: [github-pages, jekyll, web-development]
author: Il Tuo Nome
excerpt: "Breve descrizione del post che apparirà negli elenchi"
---

# Il Mio Primo Post

Questo è il contenuto del mio primo post su GitHub Pages.

## Sottosezione

Contenuto della sottosezione...

```python
# Esempio di codice
def hello_world():
    print("Hello, GitHub Pages!")
```

## Conclusioni

Le tue conclusioni qui...
```

## Layout HTML

### Layout Default (_layouts/default.html)
```html
<!DOCTYPE html>
<html lang="{{ site.lang | default: "it" }}">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{{ page.title }} - {{ site.title }}</title>
    
    {% seo %}
    
    <link rel="stylesheet" href="{{ "/assets/css/style.css" | relative_url }}">
    
    {% if site.google_analytics %}
      <!-- Google Analytics -->
      <script async src="https://www.googletagmanager.com/gtag/js?id={{ site.google_analytics }}"></script>
      <script>
        window.dataLayer = window.dataLayer || [];
        function gtag(){dataLayer.push(arguments);}
        gtag('js', new Date());
        gtag('config', '{{ site.google_analytics }}');
      </script>
    {% endif %}
  </head>

  <body>
    {% include header.html %}
    
    <main class="page-content" aria-label="Content">
      <div class="wrapper">
        {{ content }}
      </div>
    </main>
    
    {% include footer.html %}
    
    <script src="{{ "/assets/js/main.js" | relative_url }}"></script>
  </body>
</html>
```

### Header (_includes/header.html)
```html
<header class="site-header">
  <div class="wrapper">
    <a class="site-title" href="{{ "/" | relative_url }}">
      {{ site.title | escape }}
    </a>

    <nav class="site-nav">
      <input type="checkbox" id="nav-trigger" class="nav-trigger">
      <label for="nav-trigger">
        <span class="menu-icon">
          <svg viewBox="0 0 18 15" width="18px" height="15px">
            <path d="m18,1.484c0,0.82-0.665,1.484-1.484,1.484h-15.032c-0.82,0-1.484-0.665-1.484-1.484s0.665-1.484,1.484-1.484h15.032c0.82,0,1.484,0.665,1.484,1.484zm0,5.516c0,0.82-0.665,1.484-1.484,1.484h-15.032c-0.82,0-1.484-0.665-1.484-1.484s0.665-1.484,1.484-1.484h15.032c0.82,0,1.484,0.665,1.484,1.484zm0,5.516c0,0.82-0.665,1.484-1.484,1.484h-15.032c-0.82,0-1.484-0.665-1.484-1.484s0.665-1.484,1.484-1.484h15.032c0.82,0,1.484,0.665,1.484,1.484z"/>
          </svg>
        </span>
      </label>

      <div class="trigger">
        {% for path in site.header_pages %}
          {% assign my_page = site.pages | where: "path", path | first %}
          {% if my_page.title %}
            <a class="page-link" href="{{ my_page.url | relative_url }}">
              {{ my_page.title | escape }}
            </a>
          {% endif %}
        {% endfor %}
      </div>
    </nav>
  </div>
</header>
```

## Testing Locale

### Setup Ambiente Locale
```bash
# Installa Ruby e Bundler
sudo apt update
sudo apt install ruby-full build-essential zlib1g-dev

# Configura gem path
echo '# Install Ruby Gems to ~/gems' >> ~/.bashrc
echo 'export GEM_HOME="$HOME/gems"' >> ~/.bashrc
echo 'export PATH="$HOME/gems/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

# Installa Jekyll
gem install jekyll bundler

# Nel tuo repository
cd my-site
bundle install
bundle exec jekyll serve

# Il sito sarà disponibile su http://localhost:4000
```

### Comandi Utili
```bash
# Serve con auto-reload
bundle exec jekyll serve --livereload

# Build per produzione
bundle exec jekyll build

# Serve su rete locale
bundle exec jekyll serve --host 0.0.0.0

# Incrementale (più veloce)
bundle exec jekyll serve --incremental

# Draft posts
bundle exec jekyll serve --drafts
```

## Troubleshooting Comune

### Errore: "Permission denied"
```bash
# Usa bundle exec
bundle exec jekyll serve

# Non usare sudo con gem install
```

### Errore: "GitHub Pages build failed"
```bash
# Controlla i log nel repository
# Settings → Pages → View deployment history

# File _config.yml malformato
bundle exec jekyll build --verbose
```

### Errore: "404 - File not found"
```bash
# Controlla baseurl in _config.yml
# Assicurati che i link usino {{ site.baseurl }}
```

### Errore: "Jekyll version mismatch"
```bash
# Usa github-pages gem
gem "github-pages", group: :jekyll_plugins

# Update dependencies
bundle update
```

## Best Practices

### 1. Struttura del Progetto
- Usa convenzioni Jekyll standard
- Organizza contenuti per tipo
- Mantieni URL puliti e permanenti

### 2. Performance
- Ottimizza immagini (< 1MB)
- Usa lazy loading per contenuti pesanti
- Minimizza CSS e JavaScript

### 3. SEO
```yaml
# In ogni pagina
---
title: "Titolo Specifico"
description: "Descrizione per motori di ricerca"
keywords: [parola1, parola2, parola3]
author: "Il Tuo Nome"
image: "/assets/images/thumbnail.jpg"
---
```

### 4. Accessibilità
- Usa alt text per immagini
- Mantieni contrasto colori adeguato
- Naviga con tab-key funzionante

## Quiz di Autovalutazione

### Domanda 1
Quale file configura Jekyll per GitHub Pages?
a) config.json
b) _config.yml ✓
c) settings.yaml
d) jekyll.config

### Domanda 2
Dove si trovano i post del blog in Jekyll?
a) /blog/
b) /posts/
c) /_posts/ ✓
d) /content/

### Domanda 3
Quale comando serve il sito localmente?
a) jekyll start
b) bundle exec jekyll serve ✓
c) github-pages serve
d) ruby serve

### Domanda 4
Qual è l'URL per un repository project page?
a) username.github.io
b) username.github.io/repository-name ✓
c) repository-name.github.io
d) github.io/username/repository

### Domanda 5
Quale gem è necessaria per compatibilità GitHub Pages?
a) jekyll
b) github-pages ✓
c) pages-gem
d) gh-pages

## Esercizi Pratici

### Esercizio 1: Setup Base
1. Crea un nuovo repository `username.github.io`
2. Aggiungi `_config.yml` base
3. Crea `index.md` con contenuto di benvenuto
4. Attiva GitHub Pages
5. Verifica il sito online

### Esercizio 2: Blog Post
1. Crea cartella `_posts/`
2. Scrivi il primo post seguendo la convenzione dei nomi
3. Aggiungi front matter completo
4. Testa in locale con Jekyll
5. Pubblica e verifica online

### Esercizio 3: Personalizzazione
1. Crea layout personalizzato
2. Aggiungi CSS custom
3. Implementa navigazione
4. Aggiungi Google Analytics
5. Ottimizza per SEO

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 21-GitHub-Actions-Intro](../../21-GitHub-Actions-Intro/README.md)
- [➡️ 02-Jekyll Basics](./02-jekyll-basics.md)
