# Documentazione Progetto Jekyll

Questo esempio mostra come creare un sito di documentazione professionale utilizzando Jekyll e GitHub Pages.

## 🎯 Caratteristiche

- **Jekyll Static Site Generator**: Generazione automatica di siti statici
- **Markdown Support**: Scrivi documentazione in Markdown
- **Navigazione Automatica**: Menu e sidebar generati automaticamente
- **Ricerca**: Funzionalità di ricerca integrata
- **Responsive Design**: Layout che si adatta a tutti i dispositivi
- **Syntax Highlighting**: Evidenziazione del codice
- **Deploy Automatico**: Deploy automatico su GitHub Pages

## 📁 Struttura del Progetto

```
docs-site/
├── _config.yml             # Configurazione Jekyll
├── Gemfile                 # Dipendenze Ruby
├── index.md                # Homepage
├── _layouts/
│   ├── default.html        # Layout principale
│   ├── page.html          # Layout pagina
│   └── post.html          # Layout articolo
├── _includes/
│   ├── head.html          # Meta tag e CSS
│   ├── header.html        # Header del sito
│   ├── sidebar.html       # Sidebar navigazione
│   └── footer.html        # Footer del sito
├── _sass/
│   ├── _base.scss         # Stili base
│   ├── _layout.scss       # Layout styles
│   └── _syntax.scss       # Syntax highlighting
├── assets/
│   ├── css/
│   │   └── main.scss      # CSS principale
│   ├── js/
│   │   └── search.js      # JavaScript ricerca
│   └── images/
├── docs/
│   ├── getting-started/
│   ├── api/
│   ├── tutorials/
│   └── advanced/
└── _posts/                # Blog posts (opzionale)
```

## 🚀 Setup e Configurazione

### 1. Configurazione Jekyll

File `_config.yml`:
```yaml
title: "Nome Progetto"
description: "Documentazione completa per il progetto"
baseurl: "/nome-repository"
url: "https://tuousername.github.io"

# Build settings
markdown: kramdown
highlighter: rouge
theme: minima

# Collections per organizzare la documentazione
collections:
  docs:
    output: true
    permalink: /:collection/:name/

# Plugins
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag

# Exclude files from build
exclude:
  - Gemfile
  - Gemfile.lock
  - node_modules
  - vendor/
```

### 2. Gemfile per Dipendenze

```ruby
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
gem "jekyll-feed"
gem "jekyll-sitemap"
gem "jekyll-seo-tag"
```

### 3. Layout Principale

File `_layouts/default.html`:
```html
<!DOCTYPE html>
<html lang="{{ page.lang | default: site.lang | default: 'it' }}">
  {% include head.html %}
  <body>
    {% include header.html %}
    
    <div class="page-content">
      <div class="wrapper">
        <div class="content-wrapper">
          {% if page.layout == 'page' or page.layout == 'post' %}
            {% include sidebar.html %}
          {% endif %}
          
          <main class="main-content">
            {{ content }}
          </main>
        </div>
      </div>
    </div>

    {% include footer.html %}
    
    <script src="{{ '/assets/js/search.js' | relative_url }}"></script>
  </body>
</html>
```

## 📝 Creazione della Documentazione

### Struttura delle Pagine

Ogni pagina di documentazione include front matter:
```markdown
---
layout: page
title: "Titolo della Pagina"
permalink: /getting-started/installation/
nav_order: 1
parent: Getting Started
---

# Contenuto della Pagina

Scrivi la tua documentazione in Markdown...
```

### Organizzazione del Contenuto

1. **Getting Started**: Guide introduttive
2. **API Reference**: Documentazione API
3. **Tutorials**: Tutorial passo-passo
4. **Advanced**: Guide avanzate

## 🎨 Personalizzazione del Design

### Variabili SCSS

File `_sass/_base.scss`:
```scss
// Colori
$brand-color: #2E7EE5;
$text-color: #333;
$background-color: #fdfdfd;
$grey-color: #828282;

// Typography
$base-font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
$base-font-size: 16px;
$base-font-weight: 400;
$small-font-size: $base-font-size * 0.875;
$base-line-height: 1.5;

// Layout
$spacing-unit: 30px;
$content-width: 1200px;
$on-palm: 600px;
$on-laptop: 800px;
```

### Responsive Design

```scss
// Mixins per responsive design
@mixin media-query($device) {
  @media screen and (max-width: $device) {
    @content;
  }
}

// Utilizzo
.sidebar {
  width: 250px;
  
  @include media-query($on-palm) {
    width: 100%;
    position: static;
  }
}
```

## 🔍 Funzionalità di Ricerca

File `assets/js/search.js`:
```javascript
// Ricerca semplice basata su JSON
(function() {
  function displaySearchResults(results, store) {
    var searchResults = document.getElementById('search-results');

    if (results.length) {
      var appendString = '';

      for (var i = 0; i < results.length; i++) {
        var item = store[results[i].ref];
        appendString += '<li><a href="' + item.url + '"><h3>' + item.title + '</h3></a>';
        appendString += '<p>' + item.content.substring(0, 150) + '...</p></li>';
      }

      searchResults.innerHTML = appendString;
    } else {
      searchResults.innerHTML = '<li>Nessun risultato trovato</li>';
    }
  }

  function getQueryVariable(variable) {
    var query = window.location.search.substring(1);
    var vars = query.split('&');

    for (var i = 0; i < vars.length; i++) {
      var pair = vars[i].split('=');

      if (pair[0] === variable) {
        return decodeURIComponent(pair[1].replace(/\+/g, '%20'));
      }
    }
  }

  var searchTerm = getQueryVariable('query');

  if (searchTerm) {
    document.getElementById('search-box').setAttribute("value", searchTerm);

    // Inizializza lunr
    var idx = lunr(function () {
      this.field('id');
      this.field('title', { boost: 10 });
      this.field('author');
      this.field('category');
      this.field('content');
    });

    for (var key in window.store) {
      idx.add({
        'id': key,
        'title': window.store[key].title,
        'author': window.store[key].author,
        'category': window.store[key].category,
        'content': window.store[key].content
      });

      var results = idx.search(searchTerm);
      displaySearchResults(results, window.store);
    }
  }
})();
```

## 📊 Analytics e SEO

### Google Analytics

Aggiungi in `_includes/head.html`:
```html
<!-- Google Analytics -->
{% if site.google_analytics %}
<script async src="https://www.googletagmanager.com/gtag/js?id={{ site.google_analytics }}"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());
  gtag('config', '{{ site.google_analytics }}');
</script>
{% endif %}
```

### SEO Optimization

```yaml
# _config.yml
plugins:
  - jekyll-seo-tag

# Front matter delle pagine
---
title: "Titolo della Pagina"
description: "Descrizione per SEO"
image: "/assets/images/page-image.jpg"
---
```

## 🚀 Deploy su GitHub Pages

### 1. Configurazione Repository

1. Crea repository pubblico
2. Push del codice Jekyll
3. Vai in Settings > Pages
4. Seleziona source: GitHub Actions

### 2. GitHub Actions Workflow

File `.github/workflows/jekyll.yml`:
```yaml
name: Build and deploy Jekyll site to GitHub Pages

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  github-pages:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - uses: actions/setup-ruby@v1
        with:
          ruby-version: 3.0
      - name: Install dependencies
        run: |
          gem install bundler
          bundle install
      - name: Build site
        run: bundle exec jekyll build
      - name: Deploy to GitHub Pages
        if: github.ref == 'refs/heads/main'
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./_site
```

## 🔧 Manutenzione e Aggiornamenti

### Aggiornamento Dipendenze

```bash
# Aggiorna Gemfile.lock
bundle update

# Verifica vulnerabilità
bundle audit
```

### Backup e Versioning

1. **Git**: Usa Git per versioning del contenuto
2. **Releases**: Crea release per versioni importanti
3. **Backup**: Backup regolari del repository

## 📈 Metriche e Analytics

### Tracking Utenti

- Pagine più visitate
- Tempo di permanenza
- Bounce rate
- Ricerche più frequenti

### Feedback Utenti

```html
<!-- Form feedback -->
<div class="feedback-section">
  <h4>Questa pagina è stata utile?</h4>
  <button onclick="sendFeedback('yes')">👍 Sì</button>
  <button onclick="sendFeedback('no')">👎 No</button>
</div>
```

## 🤝 Collaborazione

### Workflow per Contributors

1. Fork del repository
2. Creazione branch per modifiche
3. Pull request con review
4. Merge dopo approvazione

### Guidelines per la Documentazione

- Usa un linguaggio chiaro e semplice
- Includi esempi pratici
- Mantieni la documentazione aggiornata
- Verifica la formattazione Markdown

---

**Inizia subito a creare la tua documentazione professionale! 📚**
