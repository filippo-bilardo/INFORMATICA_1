# Blog Setup con GitHub Pages e Jekyll

## 📝 Panoramica
Esempio completo per creare un blog tecnico professionale utilizzando GitHub Pages e Jekyll, con funzionalità avanzate per un team di sviluppatori.

## 🎯 Obiettivi
- Configurare un blog multi-autore
- Implementare categorizzazione e tagging avanzati
- Aggiungere funzionalità di ricerca e commenti
- Configurare analytics e SEO
- Automatizzare il workflow di pubblicazione

## 🚀 Setup Iniziale

### 1. Repository Configuration

```bash
# Creare il repository del blog
git clone https://github.com/username/dev-blog.git
cd dev-blog

# Struttura base del progetto
mkdir -p _posts/_drafts/_authors/_categories assets/css assets/js images
```

### 2. Gemfile Setup

```ruby
# Gemfile
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
gem "jekyll-paginate"
gem "jekyll-sitemap"
gem "jekyll-feed"
gem "jekyll-seo-tag"
gem "jekyll-archives"
gem "jekyll-tagging"
gem "jekyll-admin"
gem "kramdown-parser-gfm"

group :jekyll_plugins do
  gem "jekyll-github-metadata"
  gem "jekyll-relative-links"
  gem "jekyll-optional-front-matter"
  gem "jekyll-readme-index"
  gem "jekyll-default-layout"
  gem "jekyll-titles-from-headings"
end
```

## ⚙️ Configurazione Jekyll

### _config.yml Completo

```yaml
# Configurazione del sito
title: "DevTeam Blog"
description: "Blog tecnico del team di sviluppo"
baseurl: "/dev-blog"
url: "https://username.github.io"
repository: "username/dev-blog"

# Informazioni autore principale
author:
  name: "Dev Team"
  email: "team@company.com"
  twitter: "devteam"
  github: "username"

# Configurazione blog
permalink: /:categories/:year/:month/:day/:title/
paginate: 10
paginate_path: "/page:num/"

# Plugin Jekyll
plugins:
  - jekyll-paginate
  - jekyll-sitemap
  - jekyll-feed
  - jekyll-seo-tag
  - jekyll-archives
  - jekyll-github-metadata
  - jekyll-relative-links
  - jekyll-optional-front-matter
  - jekyll-readme-index
  - jekyll-default-layout
  - jekyll-titles-from-headings

# Configurazione archivi
jekyll-archives:
  enabled:
    - categories
    - tags
    - year
    - month
  layouts:
    category: archive-category
    tag: archive-tag
    year: archive-year
    month: archive-month
  permalinks:
    category: '/categoria/:name/'
    tag: '/tag/:name/'
    year: '/archivio/:year/'
    month: '/archivio/:year/:month/'

# Configurazione feed RSS
feed:
  posts_limit: 20
  excerpt_only: true

# SEO e social
twitter:
  username: devteam
  card: summary_large_image

facebook:
  app_id: your-facebook-app-id
  publisher: your-facebook-page

social:
  name: Dev Team
  links:
    - https://twitter.com/devteam
    - https://github.com/username
    - https://linkedin.com/company/yourcompany

# Google Analytics
google_analytics: UA-XXXXXXXX-X

# Configurazione commenti (Disqus)
disqus:
  shortname: your-disqus-shortname

# Configurazione search
search: true

# Configurazione markdown
markdown: kramdown
highlighter: rouge
kramdown:
  input: GFM
  hard_wrap: false
  syntax_highlighter: rouge

# Esclusioni
exclude:
  - Gemfile
  - Gemfile.lock
  - node_modules
  - vendor/bundle/
  - vendor/cache/
  - vendor/gems/
  - vendor/ruby/
  - scripts/
  - .sass-cache/
  - .jekyll-cache/
  - gemfiles/

# Collections per autori
collections:
  authors:
    output: true
    permalink: /autore/:name/

# Default layouts
defaults:
  - scope:
      path: ""
      type: "posts"
    values:
      layout: "post"
      comments: true
      share: true
  - scope:
      path: ""
      type: "authors"
    values:
      layout: "author"
  - scope:
      path: ""
    values:
      layout: "default"
```

## 👤 Sistema Multi-Autore

### Configurazione Autori

```yaml
# _authors/mario-rossi.md
---
short_name: mario
name: Mario Rossi
position: Senior Developer
avatar: /images/authors/mario.jpg
bio: "Sviluppatore full-stack con 8 anni di esperienza in JavaScript e Python."
github: mariorossi
twitter: mariorossi_dev
linkedin: mario-rossi-dev
email: mario@company.com
specialties:
  - JavaScript
  - React
  - Node.js
  - Python
  - DevOps
---

Mario è un Senior Developer specializzato in tecnologie web moderne...
```

```yaml
# _authors/anna-verdi.md
---
short_name: anna
name: Anna Verdi
position: Frontend Architect
avatar: /images/authors/anna.jpg
bio: "Esperta in UX/UI e architetture frontend scalabili."
github: annaverdi
twitter: anna_frontend
linkedin: anna-verdi-frontend
specialties:
  - Vue.js
  - TypeScript
  - CSS/SASS
  - Design Systems
  - Performance
---

Anna guida il team frontend con focus su user experience...
```

### Layout Autore

```html
<!-- _layouts/author.html -->
---
layout: default
---

<div class="author-profile">
  <div class="author-header">
    <img src="{{ author.avatar }}" alt="{{ author.name }}" class="author-avatar">
    <div class="author-info">
      <h1>{{ author.name }}</h1>
      <p class="author-position">{{ author.position }}</p>
      <p class="author-bio">{{ author.bio }}</p>
    </div>
  </div>

  <div class="author-specialties">
    <h3>Specializzazioni</h3>
    <ul class="specialty-tags">
      {% for specialty in author.specialties %}
        <li class="tag">{{ specialty }}</li>
      {% endfor %}
    </ul>
  </div>

  <div class="author-social">
    {% if author.github %}
      <a href="https://github.com/{{ author.github }}" target="_blank">
        <i class="fab fa-github"></i> GitHub
      </a>
    {% endif %}
    {% if author.twitter %}
      <a href="https://twitter.com/{{ author.twitter }}" target="_blank">
        <i class="fab fa-twitter"></i> Twitter
      </a>
    {% endif %}
    {% if author.linkedin %}
      <a href="https://linkedin.com/in/{{ author.linkedin }}" target="_blank">
        <i class="fab fa-linkedin"></i> LinkedIn
      </a>
    {% endif %}
  </div>

  <div class="author-posts">
    <h3>Articoli di {{ author.name }}</h3>
    {% assign author_posts = site.posts | where: 'author', author.short_name %}
    {% for post in author_posts limit: 10 %}
      <article class="post-preview">
        <h4><a href="{{ post.url }}">{{ post.title }}</a></h4>
        <p class="post-meta">
          <time>{{ post.date | date: "%d %B %Y" }}</time>
          {% if post.tags.size > 0 %}
            • 
            {% for tag in post.tags limit: 3 %}
              <span class="tag">{{ tag }}</span>
            {% endfor %}
          {% endif %}
        </p>
        <p class="post-excerpt">{{ post.excerpt | strip_html | truncate: 150 }}</p>
      </article>
    {% endfor %}
  </div>
</div>

{{ content }}
```

## 📝 Template per Post

### Post Template Avanzato

```markdown
---
# _posts/2024-01-15-guida-react-hooks.md
title: "Guida Completa ai React Hooks"
date: 2024-01-15 10:00:00 +0100
author: mario
categories: [frontend, react]
tags: [react, hooks, javascript, tutorial]
excerpt: "Impara a utilizzare i React Hooks per creare componenti funzionali potenti e riutilizzabili."
featured_image: /images/posts/react-hooks-cover.jpg
series: "React Avanzato"
difficulty: intermedio
read_time: 12
toc: true
comments: true
share: true
related: true
---

# Guida Completa ai React Hooks

## Introduzione

I React Hooks hanno rivoluzionato il modo di scrivere componenti React...

## Indice
- [useState Hook](#usestate-hook)
- [useEffect Hook](#useeffect-hook)
- [Hooks Personalizzati](#hooks-personalizzati)
- [Best Practices](#best-practices)

## useState Hook

Lo useState hook ci permette di aggiungere stato locale ai componenti funzionali:

```javascript
import React, { useState } from 'react';

function Counter() {
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>Hai cliccato {count} volte</p>
      <button onClick={() => setCount(count + 1)}>
        Click me
      </button>
    </div>
  );
}
```

### Gestione di Stato Complesso

```javascript
function UserProfile() {
  const [user, setUser] = useState({
    name: '',
    email: '',
    preferences: {
      theme: 'light',
      notifications: true
    }
  });

  const updateUserName = (name) => {
    setUser(prevUser => ({
      ...prevUser,
      name
    }));
  };

  const updatePreferences = (newPrefs) => {
    setUser(prevUser => ({
      ...prevUser,
      preferences: {
        ...prevUser.preferences,
        ...newPrefs
      }
    }));
  };

  return (
    // JSX component...
  );
}
```

## useEffect Hook

Il useEffect hook gestisce gli effetti collaterali nei componenti:

```javascript
import React, { useState, useEffect } from 'react';

function DataFetcher({ userId }) {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    let isCancelled = false;

    const fetchUser = async () => {
      try {
        setLoading(true);
        const response = await fetch(`/api/users/${userId}`);
        const userData = await response.json();
        
        if (!isCancelled) {
          setUser(userData);
          setError(null);
        }
      } catch (err) {
        if (!isCancelled) {
          setError(err.message);
        }
      } finally {
        if (!isCancelled) {
          setLoading(false);
        }
      }
    };

    fetchUser();

    return () => {
      isCancelled = true;
    };
  }, [userId]);

  if (loading) return <div>Caricamento...</div>;
  if (error) return <div>Errore: {error}</div>;
  return <div>Benvenuto, {user?.name}!</div>;
}
```

## Hooks Personalizzati

```javascript
// hooks/useLocalStorage.js
import { useState, useEffect } from 'react';

function useLocalStorage(key, initialValue) {
  const [storedValue, setStoredValue] = useState(() => {
    try {
      const item = window.localStorage.getItem(key);
      return item ? JSON.parse(item) : initialValue;
    } catch (error) {
      console.error(`Error reading localStorage key "${key}":`, error);
      return initialValue;
    }
  });

  const setValue = (value) => {
    try {
      const valueToStore = value instanceof Function ? value(storedValue) : value;
      setStoredValue(valueToStore);
      window.localStorage.setItem(key, JSON.stringify(valueToStore));
    } catch (error) {
      console.error(`Error setting localStorage key "${key}":`, error);
    }
  };

  return [storedValue, setValue];
}

export default useLocalStorage;
```

```javascript
// hooks/useApi.js
import { useState, useEffect } from 'react';

function useApi(url, options = {}) {
  const [data, setData] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    let isCancelled = false;

    const fetchData = async () => {
      try {
        setLoading(true);
        setError(null);

        const response = await fetch(url, {
          headers: {
            'Content-Type': 'application/json',
            ...options.headers
          },
          ...options
        });

        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }

        const result = await response.json();

        if (!isCancelled) {
          setData(result);
        }
      } catch (err) {
        if (!isCancelled) {
          setError(err.message);
        }
      } finally {
        if (!isCancelled) {
          setLoading(false);
        }
      }
    };

    fetchData();

    return () => {
      isCancelled = true;
    };
  }, [url, JSON.stringify(options)]);

  return { data, loading, error };
}

export default useApi;
```

## Best Practices

### 1. Dependency Array
```javascript
// ❌ Evitare: dependency array mancante
useEffect(() => {
  fetchData();
}); // Verrà eseguito ad ogni render

// ✅ Corretto: dependency array vuoto per eseguire una sola volta
useEffect(() => {
  fetchData();
}, []);

// ✅ Corretto: includere tutte le dipendenze
useEffect(() => {
  fetchData(userId);
}, [userId]);
```

### 2. Cleanup degli Effect
```javascript
useEffect(() => {
  const interval = setInterval(() => {
    console.log('Timer tick');
  }, 1000);

  // Cleanup function
  return () => {
    clearInterval(interval);
  };
}, []);
```

### 3. Ottimizzazione con useCallback e useMemo
```javascript
import React, { useState, useCallback, useMemo } from 'react';

function ExpensiveComponent({ items, onItemClick }) {
  const [filter, setFilter] = useState('');

  // Memoizza la funzione di callback
  const handleItemClick = useCallback((item) => {
    onItemClick(item);
  }, [onItemClick]);

  // Memoizza il calcolo pesante
  const filteredItems = useMemo(() => {
    return items.filter(item => 
      item.name.toLowerCase().includes(filter.toLowerCase())
    );
  }, [items, filter]);

  return (
    <div>
      <input 
        value={filter} 
        onChange={(e) => setFilter(e.target.value)}
        placeholder="Filtra elementi..."
      />
      {filteredItems.map(item => (
        <div key={item.id} onClick={() => handleItemClick(item)}>
          {item.name}
        </div>
      ))}
    </div>
  );
}
```

## Conclusioni

I React Hooks offrono un modo elegante e potente per gestire stato ed effetti...

---

## 📚 Risorse Aggiuntive

- [Documentazione Ufficiale React Hooks](https://reactjs.org/docs/hooks-intro.html)
- [React Hooks Cheatsheet](https://reactcheatsheet.com/)
- [Awesome React Hooks](https://github.com/rehooks/awesome-react-hooks)

---

*Articolo di [{{ site.authors[page.author].name }}]({{ site.authors[page.author].url }}) - {{ page.date | date: "%d %B %Y" }}*
```

## 🎨 Layout e Design

### Layout Post Avanzato

```html
<!-- _layouts/post.html -->
---
layout: default
---

<article class="post h-entry" itemscope itemtype="http://schema.org/BlogPosting">
  
  <!-- Header del post -->
  <header class="post-header">
    {% if page.featured_image %}
      <div class="post-featured-image">
        <img src="{{ page.featured_image }}" alt="{{ page.title }}" 
             itemprop="image" class="u-photo">
      </div>
    {% endif %}

    <div class="post-meta-header">
      {% if page.series %}
        <div class="post-series">
          <i class="fas fa-book"></i>
          Serie: <a href="/serie/{{ page.series | slugify }}/">{{ page.series }}</a>
        </div>
      {% endif %}

      {% if page.difficulty %}
        <div class="post-difficulty difficulty-{{ page.difficulty }}">
          <i class="fas fa-signal"></i>
          {{ page.difficulty | capitalize }}
        </div>
      {% endif %}

      {% if page.read_time %}
        <div class="post-read-time">
          <i class="fas fa-clock"></i>
          {{ page.read_time }} min lettura
        </div>
      {% endif %}
    </div>

    <h1 class="post-title p-name" itemprop="name headline">{{ page.title | escape }}</h1>
    
    {% if page.excerpt %}
      <p class="post-excerpt p-summary">{{ page.excerpt }}</p>
    {% endif %}

    <div class="post-meta">
      <time class="dt-published" datetime="{{ page.date | date_to_xmlschema }}" 
            itemprop="datePublished">
        {{ page.date | date: "%d %B %Y" }}
      </time>

      {% assign author = site.authors | where: 'short_name', page.author | first %}
      {% if author %}
        <span class="post-author">
          da 
          <a class="p-author h-card" href="{{ author.url }}" 
             itemprop="author" itemscope itemtype="http://schema.org/Person">
            <span itemprop="name">{{ author.name }}</span>
          </a>
        </span>
      {% endif %}

      {% if page.categories.size > 0 %}
        <div class="post-categories">
          {% for category in page.categories %}
            <a href="{{ site.baseurl }}/categoria/{{ category | slugify }}/" 
               class="category-link">{{ category }}</a>
          {% endfor %}
        </div>
      {% endif %}
    </div>
  </header>

  <!-- Indice automatico -->
  {% if page.toc %}
    <nav class="table-of-contents">
      <h3>Indice</h3>
      {{ content | toc_only }}
    </nav>
  {% endif %}

  <!-- Contenuto del post -->
  <div class="post-content e-content" itemprop="articleBody">
    {{ content }}
  </div>

  <!-- Tags -->
  {% if page.tags.size > 0 %}
    <div class="post-tags">
      <h4>Tag:</h4>
      {% for tag in page.tags %}
        <a href="{{ site.baseurl }}/tag/{{ tag | slugify }}/" 
           class="tag p-category">{{ tag }}</a>
      {% endfor %}
    </div>
  {% endif %}

  <!-- Condivisione social -->
  {% if page.share %}
    <div class="post-share">
      <h4>Condividi questo articolo:</h4>
      <div class="share-buttons">
        <a href="https://twitter.com/intent/tweet?text={{ page.title | uri_escape }}&url={{ page.url | absolute_url }}&via={{ site.twitter.username }}" 
           target="_blank" class="share-twitter">
          <i class="fab fa-twitter"></i> Twitter
        </a>
        <a href="https://www.linkedin.com/sharing/share-offsite/?url={{ page.url | absolute_url }}" 
           target="_blank" class="share-linkedin">
          <i class="fab fa-linkedin"></i> LinkedIn
        </a>
        <a href="https://www.facebook.com/sharer/sharer.php?u={{ page.url | absolute_url }}" 
           target="_blank" class="share-facebook">
          <i class="fab fa-facebook"></i> Facebook
        </a>
      </div>
    </div>
  {% endif %}

  <!-- Informazioni autore -->
  {% if author %}
    <div class="post-author-box">
      <img src="{{ author.avatar }}" alt="{{ author.name }}" class="author-avatar">
      <div class="author-info">
        <h4><a href="{{ author.url }}">{{ author.name }}</a></h4>
        <p class="author-position">{{ author.position }}</p>
        <p class="author-bio">{{ author.bio }}</p>
        <div class="author-social-mini">
          {% if author.github %}
            <a href="https://github.com/{{ author.github }}"><i class="fab fa-github"></i></a>
          {% endif %}
          {% if author.twitter %}
            <a href="https://twitter.com/{{ author.twitter }}"><i class="fab fa-twitter"></i></a>
          {% endif %}
          {% if author.linkedin %}
            <a href="https://linkedin.com/in/{{ author.linkedin }}"><i class="fab fa-linkedin"></i></a>
          {% endif %}
        </div>
      </div>
    </div>
  {% endif %}

  <!-- Articoli correlati -->
  {% if page.related %}
    <div class="related-posts">
      <h4>Articoli Correlati</h4>
      {% assign related_posts = site.related_posts | limit: 3 %}
      {% for post in related_posts %}
        <article class="related-post">
          <h5><a href="{{ post.url }}">{{ post.title }}</a></h5>
          <p class="post-meta">{{ post.date | date: "%d %B %Y" }}</p>
        </article>
      {% endfor %}
    </div>
  {% endif %}

  <!-- Commenti -->
  {% if page.comments and site.disqus.shortname %}
    <div class="post-comments">
      {% include disqus_comments.html %}
    </div>
  {% endif %}

</article>
```

## 🔍 Funzionalità di Ricerca

### Search Include

```html
<!-- _includes/search.html -->
<div class="search-container">
  <input type="text" id="search-input" placeholder="Cerca nel blog...">
  <div id="search-results"></div>
</div>

<script>
window.store = {
  {% for post in site.posts %}
    "{{ post.url | slugify }}": {
      "title": "{{ post.title | xml_escape }}",
      "author": "{{ post.author }}",
      "category": "{{ post.categories | join: ', ' }}",
      "tags": "{{ post.tags | join: ', ' }}",
      "content": {{ post.content | strip_html | strip_newlines | jsonify }},
      "url": "{{ post.url | xml_escape }}",
      "date": "{{ post.date | date: '%B %d, %Y' }}",
      "excerpt": {{ post.excerpt | strip_html | strip_newlines | jsonify }}
    }
    {% unless forloop.last %},{% endunless %}
  {% endfor %}
};
</script>

<script src="{{ '/assets/js/lunr.min.js' | relative_url }}"></script>
<script src="{{ '/assets/js/search.js' | relative_url }}"></script>
```

### Search JavaScript

```javascript
// assets/js/search.js
(function() {
  function displaySearchResults(results, store) {
    var searchResults = document.getElementById('search-results');

    if (results.length) {
      var appendString = '';

      for (var i = 0; i < results.length; i++) {
        var item = store[results[i].ref];
        appendString += '<div class="search-result">';
        appendString += '<h3><a href="' + item.url + '">' + item.title + '</a></h3>';
        appendString += '<p class="search-meta">di ' + item.author + ' • ' + item.date;
        if (item.category) {
          appendString += ' • ' + item.category;
        }
        appendString += '</p>';
        appendString += '<p class="search-excerpt">' + item.excerpt + '</p>';
        appendString += '</div>';
      }

      searchResults.innerHTML = appendString;
    } else {
      searchResults.innerHTML = '<p class="no-results">Nessun risultato trovato.</p>';
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
    document.getElementById('search-input').value = searchTerm;

    // Configurazione Lunr
    var idx = lunr(function () {
      this.field('title', { boost: 10 });
      this.field('author', { boost: 5 });
      this.field('category', { boost: 5 });
      this.field('tags', { boost: 3 });
      this.field('content');
      this.ref('id');

      for (var key in window.store) {
        this.add({
          'id': key,
          'title': window.store[key].title,
          'author': window.store[key].author,
          'category': window.store[key].category,
          'tags': window.store[key].tags,
          'content': window.store[key].content
        });
      }
    });

    var results = idx.search(searchTerm);
    displaySearchResults(results, window.store);
  }

  // Live search
  document.getElementById('search-input').addEventListener('keyup', function(e) {
    var searchTerm = e.target.value;
    
    if (searchTerm.length > 2) {
      var results = idx.search(searchTerm);
      displaySearchResults(results, window.store);
    } else if (searchTerm.length === 0) {
      document.getElementById('search-results').innerHTML = '';
    }
  });
})();
```

## 🤖 Workflow di Pubblicazione

### GitHub Actions per Deploy

```yaml
# .github/workflows/blog-deploy.yml
name: Deploy Blog

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]
  schedule:
    - cron: '0 6 * * *'  # Daily build at 6 AM

permissions:
  contents: read
  pages: write
  id-token: write

concurrency:
  group: "pages"
  cancel-in-progress: false

jobs:
  # Build job
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
        with:
          fetch-depth: 0

      - name: Setup Ruby
        uses: ruby/setup-ruby@v1
        with:
          ruby-version: '3.1'
          bundler-cache: true

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'

      - name: Install dependencies
        run: |
          bundle install
          npm install

      - name: Build CSS and JS
        run: |
          npm run build

      - name: Setup Pages
        id: pages
        uses: actions/configure-pages@v4

      - name: Build with Jekyll
        run: bundle exec jekyll build --baseurl "${{ steps.pages.outputs.base_path }}"
        env:
          JEKYLL_ENV: production

      - name: Test site
        run: |
          bundle exec htmlproofer ./_site \
            --check-html \
            --check-img-http \
            --check-opengraph \
            --report-missing-names \
            --log-level :debug \
            --assume-extension \
            --check-external-hash \
            --disable-external

      - name: Upload artifact
        uses: actions/upload-pages-artifact@v2

  # Deployment job
  deploy:
    environment:
      name: github-pages
      url: ${{ steps.deployment.outputs.page_url }}
    runs-on: ubuntu-latest
    needs: build
    if: github.ref == 'refs/heads/main'
    steps:
      - name: Deploy to GitHub Pages
        id: deployment
        uses: actions/deploy-pages@v3

  # SEO and Performance Check
  lighthouse:
    runs-on: ubuntu-latest
    needs: deploy
    if: github.ref == 'refs/heads/main'
    steps:
      - name: Lighthouse CI
        run: |
          npm install -g @lhci/cli@0.12.x
          lhci autorun
        env:
          LHCI_GITHUB_APP_TOKEN: ${{ secrets.LHCI_GITHUB_APP_TOKEN }}
          LHCI_TOKEN: ${{ secrets.LHCI_TOKEN }}

  # Newsletter e notifiche
  notify:
    runs-on: ubuntu-latest
    needs: deploy
    if: github.ref == 'refs/heads/main'
    steps:
      - name: Check for new posts
        run: |
          # Script per controllare nuovi post e inviare newsletter
          echo "Checking for new posts..."
          
      - name: Send Slack notification
        uses: 8398a7/action-slack@v3
        with:
          status: ${{ job.status }}
          channel: '#dev-blog'
          webhook_url: ${{ secrets.SLACK_WEBHOOK }}
        if: always()
```

## 📊 Analytics e Monitoraggio

### Google Analytics 4 Integration

```html
<!-- _includes/analytics.html -->
{% if site.google_analytics and jekyll.environment == 'production' %}
  <!-- Google tag (gtag.js) -->
  <script async src="https://www.googletagmanager.com/gtag/js?id={{ site.google_analytics }}"></script>
  <script>
    window.dataLayer = window.dataLayer || [];
    function gtag(){dataLayer.push(arguments);}
    gtag('js', new Date());

    gtag('config', '{{ site.google_analytics }}', {
      // Enhanced measurement
      enhanced_measurement: true,
      // Custom dimensions
      custom_map: {
        'custom_map.dimension1': 'author',
        'custom_map.dimension2': 'category',
        'custom_map.dimension3': 'reading_time'
      }
    });

    // Track post reading progress
    let scrollTimer = null;
    let scrollPercent = 0;

    window.addEventListener('scroll', function() {
      if (scrollTimer !== null) {
        clearTimeout(scrollTimer);
      }
      
      scrollTimer = setTimeout(function() {
        let scrollTop = window.pageYOffset;
        let docHeight = document.body.offsetHeight;
        let winHeight = window.innerHeight;
        let scrollPercent = Math.round(scrollTop / (docHeight - winHeight) * 100);
        
        if (scrollPercent > 0 && scrollPercent % 25 === 0) {
          gtag('event', 'scroll', {
            'event_category': 'engagement',
            'event_label': '{{ page.title }}',
            'value': scrollPercent
          });
        }
      }, 100);
    });

    // Track reading time
    {% if page.read_time %}
      setTimeout(function() {
        gtag('event', 'timing_complete', {
          'name': 'read_time',
          'value': {{ page.read_time }} * 60 * 1000,
          'event_category': 'engagement'
        });
      }, {{ page.read_time }} * 60 * 1000);
    {% endif %}

    // Track social shares
    document.querySelectorAll('.share-buttons a').forEach(function(link) {
      link.addEventListener('click', function() {
        var platform = this.className.replace('share-', '');
        gtag('event', 'share', {
          'method': platform,
          'content_type': 'article',
          'item_id': '{{ page.url }}'
        });
      });
    });
  </script>
{% endif %}
```

## 🎯 Performance e SEO

### Ottimizzazioni CSS

```scss
// assets/css/blog.scss
---
---

@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');

// Variables
$primary-color: #2563eb;
$secondary-color: #64748b;
$background-color: #ffffff;
$text-color: #1e293b;
$border-color: #e2e8f0;
$code-background: #f8fafc;

// Base styles
* {
  box-sizing: border-box;
}

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, sans-serif;
  line-height: 1.6;
  color: $text-color;
  background-color: $background-color;
  margin: 0;
  padding: 0;
}

// Performance optimizations
img {
  height: auto;
  max-width: 100%;
  loading: lazy;
}

// Code highlighting
pre {
  background-color: $code-background;
  border: 1px solid $border-color;
  border-radius: 6px;
  padding: 1rem;
  overflow-x: auto;
  font-size: 0.875rem;
  
  code {
    background: none;
    padding: 0;
    border: none;
  }
}

code {
  background-color: $code-background;
  padding: 0.2rem 0.4rem;
  border-radius: 3px;
  font-size: 0.875rem;
  font-family: 'SF Mono', Monaco, 'Cascadia Code', monospace;
}

// Responsive design
@media (max-width: 768px) {
  .post-content {
    font-size: 16px;
    
    h1 { font-size: 1.8rem; }
    h2 { font-size: 1.5rem; }
    h3 { font-size: 1.3rem; }
  }
  
  .post-meta-header {
    flex-direction: column;
    gap: 0.5rem;
  }
}

// Dark mode support
@media (prefers-color-scheme: dark) {
  body {
    background-color: #0f172a;
    color: #e2e8f0;
  }
  
  pre, code {
    background-color: #1e293b;
    border-color: #334155;
  }
}

// Print styles
@media print {
  .post-share,
  .post-comments,
  .related-posts {
    display: none;
  }
  
  .post-content {
    font-size: 12pt;
    line-height: 1.4;
  }
}
```

### Schema.org Markup

```html
<!-- _includes/structured-data.html -->
<script type="application/ld+json">
{
  "@context": "https://schema.org",
  "@type": "BlogPosting",
  "headline": "{{ page.title | escape }}",
  "description": "{{ page.excerpt | strip_html | escape }}",
  "image": {
    "@type": "ImageObject",
    "url": "{{ page.featured_image | absolute_url }}",
    "width": 1200,
    "height": 630
  },
  "author": {
    "@type": "Person",
    "name": "{{ site.authors[page.author].name }}",
    "url": "{{ site.authors[page.author].url | absolute_url }}",
    "sameAs": [
      "https://github.com/{{ site.authors[page.author].github }}",
      "https://twitter.com/{{ site.authors[page.author].twitter }}"
    ]
  },
  "publisher": {
    "@type": "Organization",
    "name": "{{ site.title }}",
    "logo": {
      "@type": "ImageObject",
      "url": "{{ '/assets/images/logo.png' | absolute_url }}",
      "width": 200,
      "height": 60
    }
  },
  "datePublished": "{{ page.date | date_to_xmlschema }}",
  "dateModified": "{{ page.last_modified_at | default: page.date | date_to_xmlschema }}",
  "mainEntityOfPage": {
    "@type": "WebPage",
    "@id": "{{ page.url | absolute_url }}"
  },
  "keywords": [
    {% for tag in page.tags %}"{{ tag }}"{% unless forloop.last %},{% endunless %}{% endfor %}
  ],
  "articleSection": [
    {% for category in page.categories %}"{{ category }}"{% unless forloop.last %},{% endunless %}{% endfor %}
  ]
}
</script>
```

## 🔧 Strumenti di Sviluppo

### Development Scripts

```json
{
  "name": "dev-blog",
  "scripts": {
    "dev": "bundle exec jekyll serve --livereload --incremental",
    "build": "npm run css:build && npm run js:build",
    "css:build": "sass assets/scss:assets/css --style=compressed",
    "css:watch": "sass assets/scss:assets/css --watch",
    "js:build": "webpack --mode=production",
    "js:watch": "webpack --mode=development --watch",
    "test": "bundle exec jekyll build && bundle exec htmlproofer ./_site",
    "deploy": "npm run build && bundle exec jekyll build",
    "new-post": "node scripts/new-post.js",
    "new-author": "node scripts/new-author.js"
  },
  "devDependencies": {
    "sass": "^1.69.0",
    "webpack": "^5.89.0",
    "webpack-cli": "^5.1.4"
  }
}
```

### Script per Nuovo Post

```javascript
// scripts/new-post.js
const fs = require('fs');
const path = require('path');
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function askQuestion(question) {
  return new Promise((resolve) => {
    rl.question(question, (answer) => {
      resolve(answer);
    });
  });
}

async function createNewPost() {
  const title = await askQuestion('Titolo del post: ');
  const author = await askQuestion('Autore (short_name): ');
  const categories = await askQuestion('Categorie (separate da virgola): ');
  const tags = await askQuestion('Tags (separati da virgola): ');
  const excerpt = await askQuestion('Riassunto: ');

  const now = new Date();
  const dateStr = now.toISOString().split('T')[0];
  const slug = title.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/(^-|-$)/g, '');
  const filename = `${dateStr}-${slug}.md`;

  const categoriesArray = categories.split(',').map(c => c.trim());
  const tagsArray = tags.split(',').map(t => t.trim());

  const frontMatter = `---
title: "${title}"
date: ${now.toISOString()}
author: ${author}
categories: [${categoriesArray.map(c => `"${c}"`).join(', ')}]
tags: [${tagsArray.map(t => `"${t}"`).join(', ')}]
excerpt: "${excerpt}"
featured_image: /images/posts/${slug}-cover.jpg
toc: true
comments: true
share: true
related: true
---

# ${title}

## Introduzione

Scrivi qui l'introduzione del tuo post...

## Contenuto

Sviluppa qui il contenuto principale...

## Conclusioni

Riassumi i punti chiave...

---

*Articolo di {{ site.authors[page.author].name }} - {{ page.date | date: "%d %B %Y" }}*
`;

  const postsDir = path.join(process.cwd(), '_posts');
  const filePath = path.join(postsDir, filename);

  fs.writeFileSync(filePath, frontMatter);
  console.log(`\n✅ Post creato: ${filePath}`);
  console.log(`📝 Ricordati di aggiungere l'immagine featured: /images/posts/${slug}-cover.jpg`);

  rl.close();
}

createNewPost().catch(console.error);
```

## 📈 Monitoraggio e Analytics

### Dashboard Metrics

```html
<!-- _includes/admin-dashboard.html -->
<div class="admin-dashboard" style="display: none;" id="admin-panel">
  <h3>📊 Dashboard Blog</h3>
  
  <div class="metrics-grid">
    <div class="metric-card">
      <h4>Articoli Totali</h4>
      <span class="metric-value">{{ site.posts.size }}</span>
    </div>
    
    <div class="metric-card">
      <h4>Autori Attivi</h4>
      <span class="metric-value">{{ site.authors.size }}</span>
    </div>
    
    <div class="metric-card">
      <h4>Categorie</h4>
      <span class="metric-value">{{ site.categories.size }}</span>
    </div>
    
    <div class="metric-card">
      <h4>Tag Totali</h4>
      <span class="metric-value">{{ site.tags.size }}</span>
    </div>
  </div>

  <div class="recent-activity">
    <h4>📝 Ultimi Articoli</h4>
    {% for post in site.posts limit: 5 %}
      <div class="activity-item">
        <strong>{{ post.title }}</strong>
        <span>{{ post.date | date: "%d/%m/%Y" }}</span>
        <span>{{ post.author }}</span>
      </div>
    {% endfor %}
  </div>

  <div class="top-authors">
    <h4>👥 Top Autori</h4>
    {% assign author_posts = site.posts | group_by: 'author' | sort: 'size' | reverse %}
    {% for author_group in author_posts limit: 5 %}
      {% assign author = site.authors | where: 'short_name', author_group.name | first %}
      <div class="author-stat">
        <span>{{ author.name | default: author_group.name }}</span>
        <span>{{ author_group.size }} articoli</span>
      </div>
    {% endfor %}
  </div>
</div>

<script>
// Mostra dashboard solo per admin
if (window.location.hash === '#admin' || localStorage.getItem('blog-admin') === 'true') {
  document.getElementById('admin-panel').style.display = 'block';
}
</script>
```

## 🚀 Conclusioni

Questo setup completo per un blog tecnico con GitHub Pages e Jekyll include:

- ✅ **Multi-author system** con profili dettagliati
- ✅ **Sistema di categorizzazione** avanzato
- ✅ **Ricerca full-text** con Lunr.js
- ✅ **SEO ottimizzato** con Schema.org
- ✅ **Performance monitoring** con Lighthouse
- ✅ **Workflow automatizzato** con GitHub Actions
- ✅ **Analytics completi** con GA4
- ✅ **Design responsive** e accessibile
- ✅ **Strumenti di sviluppo** per gestione contenuti

### 📚 Risorse Aggiuntive

- [Jekyll Documentation](https://jekyllrb.com/docs/)
- [GitHub Pages Documentation](https://docs.github.com/en/pages)
- [Liquid Template Language](https://shopify.github.io/liquid/)
- [Jekyll Themes Gallery](https://jekyllrb.com/docs/themes/)
- [Performance Best Practices](https://web.dev/performance/)

---

*Esempio completo per la creazione di un blog tecnico professionale - {{ "now" | date: "%d %B %Y" }}*
