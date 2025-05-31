# Esercizio 2: Sito di Documentazione Completo

## 🎯 Obiettivi
- Creare un sito di documentazione professionale con Jekyll
- Implementare una struttura di navigazione multi-livello
- Integrare ricerca full-text
- Configurare versioning della documentazione
- Implementare template per diversi tipi di contenuto

## 📋 Prerequisiti
- Progetto software esistente da documentare
- Conoscenza base di Markdown e YAML
- Account GitHub attivo
- Jekyll installato localmente (opzionale per sviluppo)

## 🏗️ Parte 1: Struttura del Progetto

### 1. Configurazione Repository
```bash
# Crea il repository per la documentazione
mkdir my-project-docs
cd my-project-docs
git init
git remote add origin https://github.com/username/my-project-docs.git
```

### 2. Struttura Directory
```
my-project-docs/
├── _config.yml
├── _data/
│   ├── navigation.yml
│   ├── versions.yml
│   └── authors.yml
├── _includes/
│   ├── header.html
│   ├── footer.html
│   ├── sidebar.html
│   ├── search.html
│   └── version-selector.html
├── _layouts/
│   ├── default.html
│   ├── doc.html
│   ├── api.html
│   └── tutorial.html
├── _plugins/
│   └── search-generator.rb
├── _sass/
│   ├── _base.scss
│   ├── _layout.scss
│   ├── _components.scss
│   └── _highlight.scss
├── assets/
│   ├── css/
│   │   └── style.scss
│   ├── js/
│   │   ├── search.js
│   │   └── main.js
│   └── images/
├── docs/
│   ├── getting-started/
│   ├── api-reference/
│   ├── tutorials/
│   ├── guides/
│   └── faq/
├── versions/
│   ├── v1.0/
│   ├── v2.0/
│   └── latest/
├── index.md
├── search.html
└── Gemfile
```

## ⚙️ Parte 2: Configurazione Jekyll

### 1. File di Configurazione (_config.yml)
```yaml
# Site settings
title: "MyProject Documentation"
subtitle: "Complete Guide and API Reference"
description: "Comprehensive documentation for MyProject - a powerful development tool"
baseurl: ""
url: "https://username.github.io/my-project-docs"

# Author/Organization
author:
  name: "MyProject Team"
  email: "docs@myproject.com"
  url: "https://myproject.com"

# Build settings
markdown: kramdown
highlighter: rouge
theme: minima

# Kramdown settings
kramdown:
  input: GFM
  syntax_highlighter: rouge
  syntax_highlighter_opts:
    css_class: 'highlight'
    span:
      line_numbers: false
    block:
      line_numbers: true

# Plugins
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag
  - jekyll-redirect-from
  - jekyll-last-modified-at

# Collections
collections:
  docs:
    output: true
    permalink: /:collection/:path/
  api:
    output: true
    permalink: /:collection/:path/
  tutorials:
    output: true
    permalink: /:collection/:path/
  guides:
    output: true
    permalink: /:collection/:path/

# Defaults
defaults:
  - scope:
      path: ""
      type: "docs"
    values:
      layout: "doc"
      sidebar: true
  - scope:
      path: ""
      type: "api"
    values:
      layout: "api"
      sidebar: true
  - scope:
      path: ""
      type: "tutorials"
    values:
      layout: "tutorial"
      sidebar: true
  - scope:
      path: ""
      type: "guides"
    values:
      layout: "doc"
      sidebar: true

# Search settings
search:
  enabled: true
  provider: "lunr"

# Version settings
version:
  current: "2.1"
  available: ["1.0", "1.5", "2.0", "2.1"]
  warning_days: 90

# Navigation
navigation:
  main:
    - title: "Getting Started"
      url: "/docs/getting-started/"
    - title: "API Reference" 
      url: "/api/"
    - title: "Tutorials"
      url: "/tutorials/"
    - title: "Guides"
      url: "/guides/"
    - title: "FAQ"
      url: "/docs/faq/"

# Social links
social:
  github: "username/my-project"
  twitter: "myproject"
  slack: "myproject-community"

# Google Analytics (optional)
google_analytics: "GA_TRACKING_ID"

# Search exclude
search_exclude:
  - "/versions/"
  - "/404.html"
```

### 2. Dati di Navigazione (_data/navigation.yml)
```yaml
# Main navigation structure
main:
  - title: "Getting Started"
    url: "/docs/getting-started/"
    children:
      - title: "Installation"
        url: "/docs/getting-started/installation/"
      - title: "Quick Start"
        url: "/docs/getting-started/quick-start/"
      - title: "Configuration"
        url: "/docs/getting-started/configuration/"
      - title: "First Project"
        url: "/docs/getting-started/first-project/"

  - title: "User Guide"
    url: "/docs/user-guide/"
    children:
      - title: "Basic Concepts"
        url: "/docs/user-guide/concepts/"
      - title: "Working with Projects"
        url: "/docs/user-guide/projects/"
      - title: "Advanced Features"
        url: "/docs/user-guide/advanced/"
      - title: "Troubleshooting"
        url: "/docs/user-guide/troubleshooting/"

  - title: "API Reference"
    url: "/api/"
    children:
      - title: "Authentication"
        url: "/api/authentication/"
      - title: "Core API"
        url: "/api/core/"
      - title: "Webhooks"
        url: "/api/webhooks/"
      - title: "SDK Libraries"
        url: "/api/sdks/"

  - title: "Tutorials"
    url: "/tutorials/"
    children:
      - title: "Building Your First App"
        url: "/tutorials/first-app/"
      - title: "Integration Examples"
        url: "/tutorials/integrations/"
      - title: "Best Practices"
        url: "/tutorials/best-practices/"
      - title: "Performance Optimization"
        url: "/tutorials/performance/"

  - title: "Deployment"
    url: "/docs/deployment/"
    children:
      - title: "Production Setup"
        url: "/docs/deployment/production/"
      - title: "Docker Deployment"
        url: "/docs/deployment/docker/"
      - title: "Cloud Platforms"
        url: "/docs/deployment/cloud/"
      - title: "Monitoring"
        url: "/docs/deployment/monitoring/"

# Footer navigation
footer:
  - title: "Resources"
    children:
      - title: "Community"
        url: "/community/"
      - title: "Support"
        url: "/support/"
      - title: "Changelog"
        url: "/changelog/"
      - title: "Roadmap"
        url: "/roadmap/"

  - title: "Legal"
    children:
      - title: "Privacy Policy"
        url: "/privacy/"
      - title: "Terms of Service"
        url: "/terms/"
      - title: "License"
        url: "/license/"
```

### 3. Dati Versioni (_data/versions.yml)
```yaml
# Available versions
versions:
  - version: "2.1"
    title: "v2.1 (Latest)"
    status: "current"
    release_date: "2024-01-15"
    url: "/"
    badge: "latest"
    
  - version: "2.0"
    title: "v2.0"
    status: "supported"
    release_date: "2023-09-10"
    url: "/versions/v2.0/"
    badge: "stable"
    
  - version: "1.5"
    title: "v1.5"
    status: "maintenance"
    release_date: "2023-03-20"
    url: "/versions/v1.5/"
    badge: "maintenance"
    
  - version: "1.0"
    title: "v1.0"
    status: "deprecated"
    release_date: "2022-06-15"
    url: "/versions/v1.0/"
    badge: "deprecated"
    end_of_life: "2024-06-15"

# Version support policy
support_policy:
  current: "Full support with new features and bug fixes"
  supported: "Bug fixes and security updates"
  maintenance: "Critical security fixes only"
  deprecated: "No longer supported"
```

## 🎨 Parte 3: Layout e Templates

### 1. Layout Base (_layouts/default.html)
```html
<!DOCTYPE html>
<html lang="{{ site.lang | default: 'en' }}">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{% if page.title %}{{ page.title }} | {% endif %}{{ site.title }}</title>
    
    <!-- SEO Meta Tags -->
    <meta name="description" content="{{ page.description | default: page.excerpt | default: site.description | strip_html | normalize_whitespace | truncate: 160 | escape }}">
    <meta name="author" content="{{ page.author | default: site.author.name }}">
    
    <!-- Open Graph Meta Tags -->
    <meta property="og:title" content="{% if page.title %}{{ page.title }} | {% endif %}{{ site.title }}">
    <meta property="og:description" content="{{ page.description | default: page.excerpt | default: site.description | strip_html | normalize_whitespace | truncate: 300 | escape }}">
    <meta property="og:url" content="{{ page.url | absolute_url }}">
    <meta property="og:site_name" content="{{ site.title }}">
    <meta property="og:type" content="website">
    
    <!-- Twitter Card Meta Tags -->
    <meta name="twitter:card" content="summary_large_image">
    <meta name="twitter:title" content="{% if page.title %}{{ page.title }} | {% endif %}{{ site.title }}">
    <meta name="twitter:description" content="{{ page.description | default: page.excerpt | default: site.description | strip_html | normalize_whitespace | truncate: 200 | escape }}">
    
    <!-- Stylesheets -->
    <link rel="stylesheet" href="{{ '/assets/css/style.css' | relative_url }}">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap">
    
    <!-- Favicon -->
    <link rel="icon" type="image/x-icon" href="{{ '/assets/images/favicon.ico' | relative_url }}">
    
    <!-- Canonical URL -->
    <link rel="canonical" href="{{ page.url | absolute_url }}">
    
    <!-- RSS Feed -->
    <link rel="alternate" type="application/rss+xml" title="{{ site.title }}" href="{{ '/feed.xml' | relative_url }}">
    
    <!-- Jekyll SEO Tag -->
    {% seo %}
</head>
<body class="{% if page.layout %}layout-{{ page.layout }}{% endif %} {% if page.sidebar %}has-sidebar{% endif %}">
    
    <!-- Header -->
    {% include header.html %}
    
    <!-- Main Content -->
    <main class="main-content" role="main">
        {% if page.sidebar %}
        <div class="content-wrapper">
            <aside class="sidebar" role="complementary">
                {% include sidebar.html %}
            </aside>
            <div class="content">
                {{ content }}
            </div>
        </div>
        {% else %}
        <div class="content full-width">
            {{ content }}
        </div>
        {% endif %}
    </main>
    
    <!-- Footer -->
    {% include footer.html %}
    
    <!-- JavaScript -->
    <script src="{{ '/assets/js/main.js' | relative_url }}"></script>
    {% if site.search.enabled %}
    <script src="{{ '/assets/js/search.js' | relative_url }}"></script>
    {% endif %}
    
    <!-- Google Analytics -->
    {% if site.google_analytics %}
    <!-- Global site tag (gtag.js) - Google Analytics -->
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

### 2. Layout Documentazione (_layouts/doc.html)
```html
---
layout: default
---

<article class="doc-content">
    <header class="doc-header">
        {% if page.version and page.version != site.version.current %}
        <div class="version-warning">
            <i class="fas fa-exclamation-triangle"></i>
            <span>You're viewing documentation for version {{ page.version }}. 
            <a href="{{ page.url | replace: '/versions/' + page.version, '' }}">View latest version</a>
            </span>
        </div>
        {% endif %}
        
        {% if page.category %}
        <nav class="breadcrumb" aria-label="Breadcrumb">
            <ol>
                <li><a href="/">Home</a></li>
                {% assign breadcrumbs = page.url | remove: '/index.html' | split: '/' %}
                {% assign url = '' %}
                {% for crumb in breadcrumbs %}
                    {% if forloop.last %}
                        <li aria-current="page">{{ page.title }}</li>
                    {% else %}
                        {% assign url = url | append: '/' | append: crumb %}
                        <li><a href="{{ url }}">{{ crumb | replace: '-', ' ' | capitalize }}</a></li>
                    {% endif %}
                {% endfor %}
            </ol>
        </nav>
        {% endif %}
        
        <div class="doc-title-section">
            <h1 class="doc-title">{{ page.title }}</h1>
            {% if page.subtitle %}
            <p class="doc-subtitle">{{ page.subtitle }}</p>
            {% endif %}
            
            <div class="doc-meta">
                {% if page.author %}
                <span class="meta-item">
                    <i class="fas fa-user"></i>
                    {{ page.author }}
                </span>
                {% endif %}
                
                {% if page.last_modified_at %}
                <span class="meta-item">
                    <i class="fas fa-clock"></i>
                    Updated {{ page.last_modified_at | date: "%B %d, %Y" }}
                </span>
                {% endif %}
                
                {% if page.reading_time %}
                <span class="meta-item">
                    <i class="fas fa-book-open"></i>
                    {{ page.reading_time }} min read
                </span>
                {% endif %}
            </div>
        </div>
        
        {% if page.toc != false %}
        <nav class="table-of-contents">
            <h3>In This Article</h3>
            <div id="toc"></div>
        </nav>
        {% endif %}
    </header>
    
    <div class="doc-body">
        {{ content }}
    </div>
    
    <footer class="doc-footer">
        {% if page.prev or page.next %}
        <nav class="doc-navigation">
            {% if page.prev %}
            <a href="{{ page.prev.url }}" class="nav-prev">
                <span class="nav-direction">Previous</span>
                <span class="nav-title">{{ page.prev.title }}</span>
            </a>
            {% endif %}
            
            {% if page.next %}
            <a href="{{ page.next.url }}" class="nav-next">
                <span class="nav-direction">Next</span>
                <span class="nav-title">{{ page.next.title }}</span>
            </a>
            {% endif %}
        </nav>
        {% endif %}
        
        <div class="doc-actions">
            <a href="https://github.com/{{ site.social.github }}/edit/main/{{ page.path }}" class="edit-link">
                <i class="fas fa-edit"></i>
                Edit this page
            </a>
            
            <a href="https://github.com/{{ site.social.github }}/issues/new?title=Issue%20with%20{{ page.title | url_encode }}&body=Issue%20on%20page:%20{{ page.url | absolute_url }}" class="issue-link">
                <i class="fas fa-bug"></i>
                Report an issue
            </a>
        </div>
        
        {% if page.tags.size > 0 %}
        <div class="doc-tags">
            <span class="tags-label">Tags:</span>
            {% for tag in page.tags %}
            <a href="/tags/{{ tag | slugify }}" class="tag">{{ tag }}</a>
            {% endfor %}
        </div>
        {% endif %}
    </footer>
</article>
```

### 3. Layout API (_layouts/api.html)
```html
---
layout: default
---

<article class="api-content">
    <header class="api-header">
        <div class="api-title-section">
            <h1 class="api-title">{{ page.title }}</h1>
            {% if page.subtitle %}
            <p class="api-subtitle">{{ page.subtitle }}</p>
            {% endif %}
            
            {% if page.endpoint %}
            <div class="endpoint-info">
                <span class="method method-{{ page.method | downcase }}">{{ page.method | upcase }}</span>
                <code class="endpoint">{{ page.endpoint }}</code>
            </div>
            {% endif %}
        </div>
        
        {% if page.description %}
        <div class="api-description">
            {{ page.description | markdownify }}
        </div>
        {% endif %}
    </header>
    
    <div class="api-body">
        {% if page.parameters %}
        <section class="parameters">
            <h2>Parameters</h2>
            <div class="parameter-table">
                <table>
                    <thead>
                        <tr>
                            <th>Name</th>
                            <th>Type</th>
                            <th>Required</th>
                            <th>Description</th>
                        </tr>
                    </thead>
                    <tbody>
                        {% for param in page.parameters %}
                        <tr>
                            <td><code>{{ param.name }}</code></td>
                            <td><span class="type">{{ param.type }}</span></td>
                            <td>
                                {% if param.required %}
                                <span class="required">Required</span>
                                {% else %}
                                <span class="optional">Optional</span>
                                {% endif %}
                            </td>
                            <td>{{ param.description }}</td>
                        </tr>
                        {% endfor %}
                    </tbody>
                </table>
            </div>
        </section>
        {% endif %}
        
        {{ content }}
        
        {% if page.examples %}
        <section class="examples">
            <h2>Examples</h2>
            {% for example in page.examples %}
            <div class="example">
                <h3>{{ example.title }}</h3>
                {% if example.description %}
                <p>{{ example.description }}</p>
                {% endif %}
                
                <div class="code-tabs">
                    {% for code in example.code %}
                    <button class="tab-button" data-tab="{{ code.language }}">{{ code.language | capitalize }}</button>
                    {% endfor %}
                </div>
                
                {% for code in example.code %}
                <div class="tab-content" data-tab="{{ code.language }}">
                    {% highlight {{ code.language }} %}{{ code.content }}{% endhighlight %}
                </div>
                {% endfor %}
                
                {% if example.response %}
                <div class="response">
                    <h4>Response</h4>
                    {% highlight json %}{{ example.response }}{% endhighlight %}
                </div>
                {% endif %}
            </div>
            {% endfor %}
        </section>
        {% endif %}
        
        {% if page.responses %}
        <section class="responses">
            <h2>Responses</h2>
            {% for response in page.responses %}
            <div class="response-item">
                <h3>
                    <span class="status-code status-{{ response.status | slice: 0 }}xx">{{ response.status }}</span>
                    {{ response.description }}
                </h3>
                {% if response.schema %}
                {% highlight json %}{{ response.schema }}{% endhighlight %}
                {% endif %}
            </div>
            {% endfor %}
        </section>
        {% endif %}
    </div>
    
    <footer class="api-footer">
        <div class="api-actions">
            <a href="{{ site.social.github }}/tree/main/{{ page.path }}" class="source-link">
                <i class="fas fa-code"></i>
                View Source
            </a>
            
            {% if page.sdk_links %}
            <div class="sdk-links">
                <span>SDKs:</span>
                {% for sdk in page.sdk_links %}
                <a href="{{ sdk.url }}" class="sdk-link">{{ sdk.name }}</a>
                {% endfor %}
            </div>
            {% endif %}
        </div>
    </footer>
</article>
```

## 🔍 Parte 4: Sistema di Ricerca

### 1. Plugin di Ricerca (_plugins/search-generator.rb)
```ruby
require 'json'

Jekyll::Hooks.register :site, :post_write do |site|
  # Generate search index
  search_index = []
  
  site.collections.each do |name, collection|
    collection.docs.each do |doc|
      next if doc.data['search'] == false
      
      search_index << {
        title: doc.data['title'],
        url: doc.url,
        content: doc.content.gsub(/<\/?[^>]*>/, '').strip,
        category: doc.data['category'] || name,
        tags: doc.data['tags'] || [],
        type: doc.collection.label
      }
    end
  end
  
  # Add pages
  site.pages.each do |page|
    next if page.data['search'] == false
    next if page.url.include?('404')
    
    search_index << {
      title: page.data['title'] || page.name,
      url: page.url,
      content: page.content.gsub(/<\/?[^>]*>/, '').strip,
      category: page.data['category'] || 'page',
      tags: page.data['tags'] || [],
      type: 'page'
    }
  end
  
  # Write search index
  File.open(File.join(site.dest, 'search-index.json'), 'w') do |f|
    f.write(JSON.pretty_generate(search_index))
  end
end
```

### 2. JavaScript per Ricerca (assets/js/search.js)
```javascript
class DocumentationSearch {
    constructor() {
        this.searchIndex = null;
        this.searchInput = null;
        this.searchResults = null;
        this.isLoaded = false;
        
        this.init();
    }
    
    async init() {
        await this.loadSearchIndex();
        this.setupDOM();
        this.bindEvents();
    }
    
    async loadSearchIndex() {
        try {
            const response = await fetch('/search-index.json');
            this.searchIndex = await response.json();
            this.isLoaded = true;
        } catch (error) {
            console.error('Error loading search index:', error);
        }
    }
    
    setupDOM() {
        this.searchInput = document.getElementById('search-input');
        this.searchResults = document.getElementById('search-results');
        
        if (!this.searchInput || !this.searchResults) {
            console.warn('Search elements not found');
            return;
        }
    }
    
    bindEvents() {
        if (!this.searchInput) return;
        
        this.searchInput.addEventListener('input', this.debounce((e) => {
            const query = e.target.value.trim();
            if (query.length >= 2) {
                this.performSearch(query);
            } else {
                this.clearResults();
            }
        }, 300));
        
        // Keyboard navigation
        this.searchInput.addEventListener('keydown', (e) => {
            if (e.key === 'Escape') {
                this.clearResults();
                this.searchInput.blur();
            }
        });
        
        // Close results when clicking outside
        document.addEventListener('click', (e) => {
            if (!e.target.closest('.search-container')) {
                this.clearResults();
            }
        });
    }
    
    performSearch(query) {
        if (!this.isLoaded || !this.searchIndex) {
            return;
        }
        
        const results = this.searchIndex.filter(item => {
            const searchTerms = query.toLowerCase().split(' ');
            const searchableContent = (
                item.title + ' ' + 
                item.content + ' ' + 
                (item.tags || []).join(' ')
            ).toLowerCase();
            
            return searchTerms.every(term => 
                searchableContent.includes(term)
            );
        });
        
        // Sort by relevance
        results.sort((a, b) => {
            const aScore = this.calculateRelevance(a, query);
            const bScore = this.calculateRelevance(b, query);
            return bScore - aScore;
        });
        
        this.displayResults(results.slice(0, 10), query);
    }
    
    calculateRelevance(item, query) {
        const queryLower = query.toLowerCase();
        let score = 0;
        
        // Title matches are more important
        if (item.title.toLowerCase().includes(queryLower)) {
            score += 10;
        }
        
        // Exact word matches
        const words = queryLower.split(' ');
        words.forEach(word => {
            if (item.title.toLowerCase().includes(word)) score += 5;
            if (item.content.toLowerCase().includes(word)) score += 1;
        });
        
        // Type priority (docs > tutorials > api)
        if (item.type === 'docs') score += 2;
        else if (item.type === 'tutorials') score += 1;
        
        return score;
    }
    
    displayResults(results, query) {
        if (!this.searchResults) return;
        
        if (results.length === 0) {
            this.searchResults.innerHTML = `
                <div class="search-no-results">
                    <p>No results found for "<strong>${this.escapeHtml(query)}</strong>"</p>
                    <p>Try different keywords or check the spelling.</p>
                </div>
            `;
        } else {
            this.searchResults.innerHTML = results.map(result => 
                this.renderSearchResult(result, query)
            ).join('');
        }
        
        this.searchResults.style.display = 'block';
    }
    
    renderSearchResult(result, query) {
        const highlightedTitle = this.highlightQuery(result.title, query);
        const snippet = this.createSnippet(result.content, query);
        const typeIcon = this.getTypeIcon(result.type);
        
        return `
            <div class="search-result">
                <div class="result-header">
                    <span class="result-type">
                        <i class="${typeIcon}"></i>
                        ${result.type}
                    </span>
                    <a href="${result.url}" class="result-title">${highlightedTitle}</a>
                </div>
                <p class="result-snippet">${snippet}</p>
                <div class="result-meta">
                    <span class="result-url">${result.url}</span>
                    ${result.tags && result.tags.length > 0 ? 
                        `<div class="result-tags">
                            ${result.tags.slice(0, 3).map(tag => 
                                `<span class="tag">${tag}</span>`
                            ).join('')}
                        </div>` : ''
                    }
                </div>
            </div>
        `;
    }
    
    createSnippet(content, query, maxLength = 150) {
        const queryLower = query.toLowerCase();
        const contentLower = content.toLowerCase();
        const queryIndex = contentLower.indexOf(queryLower);
        
        let snippet;
        if (queryIndex !== -1) {
            const start = Math.max(0, queryIndex - 50);
            const end = Math.min(content.length, queryIndex + maxLength);
            snippet = content.slice(start, end);
            if (start > 0) snippet = '...' + snippet;
            if (end < content.length) snippet = snippet + '...';
        } else {
            snippet = content.slice(0, maxLength);
            if (content.length > maxLength) snippet += '...';
        }
        
        return this.highlightQuery(snippet, query);
    }
    
    highlightQuery(text, query) {
        const words = query.split(' ');
        let highlighted = text;
        
        words.forEach(word => {
            if (word.length > 1) {
                const regex = new RegExp(`(${this.escapeRegExp(word)})`, 'gi');
                highlighted = highlighted.replace(regex, '<mark>$1</mark>');
            }
        });
        
        return highlighted;
    }
    
    getTypeIcon(type) {
        const icons = {
            'docs': 'fas fa-file-alt',
            'api': 'fas fa-code',
            'tutorials': 'fas fa-graduation-cap',
            'guides': 'fas fa-book',
            'page': 'fas fa-file'
        };
        return icons[type] || 'fas fa-file';
    }
    
    clearResults() {
        if (this.searchResults) {
            this.searchResults.style.display = 'none';
            this.searchResults.innerHTML = '';
        }
    }
    
    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }
    
    escapeRegExp(string) {
        return string.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
    }
    
    debounce(func, wait) {
        let timeout;
        return function executedFunction(...args) {
            const later = () => {
                clearTimeout(timeout);
                func(...args);
            };
            clearTimeout(timeout);
            timeout = setTimeout(later, wait);
        };
    }
}

// Initialize search when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new DocumentationSearch();
});
```

### 3. HTML per Ricerca (search.html)
```html
---
layout: default
title: Search
permalink: /search/
---

<div class="search-page">
    <div class="search-header">
        <h1>Search Documentation</h1>
        <p>Search through our comprehensive documentation, API references, and tutorials.</p>
    </div>
    
    <div class="search-container">
        <div class="search-input-wrapper">
            <i class="fas fa-search search-icon"></i>
            <input 
                type="text" 
                id="search-input" 
                placeholder="Search documentation..."
                autocomplete="off"
                spellcheck="false"
            >
            <button class="search-clear" id="search-clear" style="display: none;">
                <i class="fas fa-times"></i>
            </button>
        </div>
        
        <div id="search-results" class="search-results" style="display: none;"></div>
    </div>
    
    <div class="search-suggestions">
        <h3>Popular Searches</h3>
        <div class="suggestion-tags">
            <a href="/search?q=installation" class="suggestion-tag">Installation</a>
            <a href="/search?q=api+authentication" class="suggestion-tag">API Authentication</a>
            <a href="/search?q=getting+started" class="suggestion-tag">Getting Started</a>
            <a href="/search?q=configuration" class="suggestion-tag">Configuration</a>
            <a href="/search?q=troubleshooting" class="suggestion-tag">Troubleshooting</a>
            <a href="/search?q=deployment" class="suggestion-tag">Deployment</a>
        </div>
    </div>
    
    <div class="search-help">
        <h3>Search Tips</h3>
        <ul>
            <li>Use specific keywords for better results</li>
            <li>Try different variations of your search terms</li>
            <li>Use quotes for exact phrase matches: "exact phrase"</li>
            <li>Browse by category using the sidebar navigation</li>
        </ul>
    </div>
</div>

<script>
// Handle URL search parameters
document.addEventListener('DOMContentLoaded', () => {
    const urlParams = new URLSearchParams(window.location.search);
    const query = urlParams.get('q');
    
    if (query) {
        const searchInput = document.getElementById('search-input');
        if (searchInput) {
            searchInput.value = query;
            searchInput.dispatchEvent(new Event('input'));
        }
    }
});
</script>
```

## 🎨 Parte 5: Styling CSS

### 1. CSS Principale (assets/css/style.scss)
```scss
---
---

@import "base";
@import "layout";
@import "components";
@import "highlight";

// Import additional styles
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&family=JetBrains+Mono:wght@400;500&display=swap');
```

### 2. Base Styles (_sass/_base.scss)
```scss
// Variables
:root {
  --primary-color: #2563eb;
  --secondary-color: #64748b;
  --success-color: #10b981;
  --warning-color: #f59e0b;
  --error-color: #ef4444;
  --text-color: #1f2937;
  --text-muted: #6b7280;
  --border-color: #e5e7eb;
  --background-color: #ffffff;
  --surface-color: #f9fafb;
  --code-bg: #f3f4f6;
  --shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  --shadow-lg: 0 10px 15px rgba(0, 0, 0, 0.1);
  --border-radius: 6px;
  --font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  --font-mono: 'JetBrains Mono', 'Monaco', 'Menlo', monospace;
}

// Dark theme
@media (prefers-color-scheme: dark) {
  :root {
    --primary-color: #3b82f6;
    --text-color: #f9fafb;
    --text-muted: #9ca3af;
    --border-color: #374151;
    --background-color: #111827;
    --surface-color: #1f2937;
    --code-bg: #374151;
  }
}

// Reset
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

// Base styles
body {
  font-family: var(--font-family);
  line-height: 1.6;
  color: var(--text-color);
  background-color: var(--background-color);
  font-size: 16px;
}

h1, h2, h3, h4, h5, h6 {
  font-weight: 600;
  line-height: 1.25;
  margin-bottom: 1rem;
  color: var(--text-color);
}

h1 { font-size: 2.25rem; }
h2 { font-size: 1.875rem; }
h3 { font-size: 1.5rem; }
h4 { font-size: 1.25rem; }
h5 { font-size: 1.125rem; }
h6 { font-size: 1rem; }

p {
  margin-bottom: 1rem;
  color: var(--text-muted);
}

a {
  color: var(--primary-color);
  text-decoration: none;
  transition: color 0.2s;
  
  &:hover {
    text-decoration: underline;
  }
}

code {
  font-family: var(--font-mono);
  font-size: 0.875rem;
  background-color: var(--code-bg);
  padding: 0.125rem 0.25rem;
  border-radius: 3px;
  border: 1px solid var(--border-color);
}

pre {
  background-color: var(--code-bg);
  border: 1px solid var(--border-color);
  border-radius: var(--border-radius);
  padding: 1rem;
  overflow-x: auto;
  margin-bottom: 1rem;
  
  code {
    background: none;
    border: none;
    padding: 0;
  }
}

blockquote {
  border-left: 4px solid var(--primary-color);
  padding-left: 1rem;
  margin: 1rem 0;
  font-style: italic;
  color: var(--text-muted);
}

table {
  width: 100%;
  border-collapse: collapse;
  margin-bottom: 1rem;
  
  th, td {
    padding: 0.75rem;
    text-align: left;
    border-bottom: 1px solid var(--border-color);
  }
  
  th {
    font-weight: 600;
    background-color: var(--surface-color);
  }
}

img {
  max-width: 100%;
  height: auto;
  border-radius: var(--border-radius);
}

ul, ol {
  margin-bottom: 1rem;
  padding-left: 1.5rem;
  
  li {
    margin-bottom: 0.25rem;
  }
}
```

## 📖 Parte 6: Contenuto di Esempio

### 1. Pagina Principale (index.md)
```markdown
---
layout: default
title: "MyProject Documentation"
description: "Comprehensive documentation for MyProject - a powerful development tool"
---

# Welcome to MyProject Documentation

MyProject is a powerful development tool designed to streamline your workflow and boost productivity. This documentation will guide you through everything you need to know to get started and become proficient with MyProject.

## Quick Start

<div class="quick-start-grid">
  <div class="quick-start-card">
    <div class="card-icon">
      <i class="fas fa-download"></i>
    </div>
    <h3>Install</h3>
    <p>Get MyProject up and running in minutes</p>
    <a href="/docs/getting-started/installation/" class="card-link">Installation Guide →</a>
  </div>
  
  <div class="quick-start-card">
    <div class="card-icon">
      <i class="fas fa-rocket"></i>
    </div>
    <h3>Quick Start</h3>
    <p>Create your first project in under 5 minutes</p>
    <a href="/docs/getting-started/quick-start/" class="card-link">Quick Start →</a>
  </div>
  
  <div class="quick-start-card">
    <div class="card-icon">
      <i class="fas fa-code"></i>
    </div>
    <h3>API Reference</h3>
    <p>Complete API documentation and examples</p>
    <a href="/api/" class="card-link">API Docs →</a>
  </div>
  
  <div class="quick-start-card">
    <div class="card-icon">
      <i class="fas fa-graduation-cap"></i>
    </div>
    <h3>Tutorials</h3>
    <p>Step-by-step tutorials and best practices</p>
    <a href="/tutorials/" class="card-link">View Tutorials →</a>
  </div>
</div>

## What's New

### Version 2.1 Release
*January 15, 2024*

- **Enhanced Performance**: 40% faster processing speeds
- **New API Endpoints**: Extended functionality for power users
- **Improved Documentation**: Updated examples and clearer explanations
- **Bug Fixes**: Resolved 25+ community-reported issues

[View Full Changelog →](/changelog/)

## Popular Documentation

<div class="popular-docs">
  <div class="doc-category">
    <h3>Getting Started</h3>
    <ul>
      <li><a href="/docs/getting-started/installation/">Installation</a></li>
      <li><a href="/docs/getting-started/configuration/">Configuration</a></li>
      <li><a href="/docs/getting-started/first-project/">Your First Project</a></li>
    </ul>
  </div>
  
  <div class="doc-category">
    <h3>API Reference</h3>
    <ul>
      <li><a href="/api/authentication/">Authentication</a></li>
      <li><a href="/api/core/">Core API</a></li>
      <li><a href="/api/webhooks/">Webhooks</a></li>
    </ul>
  </div>
  
  <div class="doc-category">
    <h3>Advanced Topics</h3>
    <ul>
      <li><a href="/docs/deployment/production/">Production Deployment</a></li>
      <li><a href="/tutorials/performance/">Performance Optimization</a></li>
      <li><a href="/guides/troubleshooting/">Troubleshooting</a></li>
    </ul>
  </div>
</div>

## Community & Support

<div class="community-section">
  <div class="community-card">
    <i class="fab fa-github"></i>
    <h4>GitHub</h4>
    <p>Source code, issues, and contributions</p>
    <a href="https://github.com/{{ site.social.github }}">View Repository</a>
  </div>
  
  <div class="community-card">
    <i class="fab fa-slack"></i>
    <h4>Slack Community</h4>
    <p>Get help from the community</p>
    <a href="https://{{ site.social.slack }}.slack.com">Join Slack</a>
  </div>
  
  <div class="community-card">
    <i class="fas fa-life-ring"></i>
    <h4>Support</h4>
    <p>Professional support options</p>
    <a href="/support/">Get Support</a>
  </div>
</div>

## Example Usage

```javascript
// Initialize MyProject
const myProject = new MyProject({
  apiKey: 'your-api-key',
  environment: 'production'
});

// Create a new project
const project = await myProject.create({
  name: 'My Awesome Project',
  template: 'web-app'
});

console.log('Project created:', project.id);
```

Ready to get started? [Install MyProject →](/docs/getting-started/installation/)
```

### 2. Esempio Documentazione API (_api/authentication.md)
```markdown
---
layout: api
title: "Authentication"
subtitle: "Secure access to the MyProject API"
method: POST
endpoint: "/auth/token"
description: "MyProject API uses token-based authentication for secure access to all endpoints."
parameters:
  - name: "api_key"
    type: "string"
    required: true
    description: "Your API key from the dashboard"
  - name: "expires_in"
    type: "integer"
    required: false
    description: "Token expiration time in seconds (default: 3600)"
examples:
  - title: "Basic Authentication"
    description: "Get an access token using your API key"
    code:
      - language: "curl"
        content: |
          curl -X POST https://api.myproject.com/auth/token \
            -H "Content-Type: application/json" \
            -d '{
              "api_key": "your_api_key_here",
              "expires_in": 3600
            }'
      - language: "javascript"
        content: |
          const response = await fetch('https://api.myproject.com/auth/token', {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({
              api_key: 'your_api_key_here',
              expires_in: 3600
            })
          });
          
          const data = await response.json();
          console.log('Access token:', data.access_token);
      - language: "python"
        content: |
          import requests
          
          response = requests.post('https://api.myproject.com/auth/token', 
            json={
              'api_key': 'your_api_key_here',
              'expires_in': 3600
            }
          )
          
          data = response.json()
          print(f"Access token: {data['access_token']}")
    response: |
      {
        "access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
        "token_type": "Bearer",
        "expires_in": 3600,
        "expires_at": "2024-01-15T15:30:00Z"
      }
responses:
  - status: 200
    description: "Authentication successful"
    schema: |
      {
        "access_token": "string",
        "token_type": "string",
        "expires_in": "integer",
        "expires_at": "string (ISO 8601)"
      }
  - status: 401
    description: "Invalid API key"
    schema: |
      {
        "error": "invalid_api_key",
        "message": "The provided API key is invalid or expired"
      }
sdk_links:
  - name: "JavaScript SDK"
    url: "/api/sdks/javascript/"
  - name: "Python SDK"
    url: "/api/sdks/python/"
tags:
  - authentication
  - security
  - api
---

## Overview

The MyProject API uses **Bearer token authentication** for secure access to all endpoints. This authentication method ensures that your API requests are secure and properly authorized.

## How It Works

1. **Get API Key**: First, obtain your API key from the [MyProject Dashboard](https://dashboard.myproject.com)
2. **Request Token**: Use your API key to request an access token
3. **Use Token**: Include the access token in all subsequent API requests

## Getting Your API Key

1. Log in to your [MyProject Dashboard](https://dashboard.myproject.com)
2. Navigate to **Settings** → **API Keys**
3. Click **Generate New Key**
4. Copy and securely store your API key

<div class="callout callout-warning">
  <strong>Security Note:</strong> Never expose your API key in client-side code or public repositories. Always use environment variables or secure configuration files.
</div>

## Using Access Tokens

Once you have an access token, include it in the `Authorization` header of your API requests:

```http
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

## Token Expiration

Access tokens expire after the specified time (default: 1 hour). When a token expires, you'll receive a `401 Unauthorized` response. Simply request a new token using your API key.

## Best Practices

- **Store Securely**: Keep your API keys secure and never commit them to version control
- **Rotate Regularly**: Regenerate your API keys periodically for enhanced security
- **Use HTTPS**: Always use HTTPS when making API requests
- **Handle Expiration**: Implement token refresh logic in your applications
- **Monitor Usage**: Keep track of your API usage in the dashboard

## Rate Limiting

Authentication requests are subject to rate limiting:
- **Limit**: 100 requests per hour per API key
- **Headers**: Rate limit information is included in response headers

## Error Handling

Common authentication errors and how to handle them:

| Error Code | Description | Solution |
|------------|-------------|----------|
| `invalid_api_key` | API key is invalid or expired | Check your API key and regenerate if necessary |
| `rate_limit_exceeded` | Too many authentication requests | Wait before retrying or contact support |
| `maintenance_mode` | API is in maintenance mode | Check status page for updates |

## SDK Examples

### JavaScript SDK

```javascript
import { MyProjectAPI } from '@myproject/sdk';

const api = new MyProjectAPI({
  apiKey: process.env.MYPROJECT_API_KEY
});

// SDK handles authentication automatically
const projects = await api.projects.list();
```

### Python SDK

```python
from myproject import MyProjectAPI

api = MyProjectAPI(api_key=os.environ['MYPROJECT_API_KEY'])

# SDK handles authentication automatically
projects = api.projects.list()
```

## Next Steps

- [Core API Reference](/api/core/) - Learn about the main API endpoints
- [Webhooks](/api/webhooks/) - Set up real-time notifications
- [SDK Documentation](/api/sdks/) - Use our official SDKs
```

## 🚀 Parte 7: Deploy e Configurazione

### 1. GitHub Actions Workflow (.github/workflows/deploy.yml)
```yaml
name: Build and Deploy Documentation

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
      id: pages
      uses: actions/configure-pages@v3
      
    - name: Build with Jekyll
      run: bundle exec jekyll build --baseurl "${{ steps.pages.outputs.base_path }}"
      env:
        JEKYLL_ENV: production
        
    - name: Upload artifact
      uses: actions/upload-pages-artifact@v2

  deploy:
    if: github.ref == 'refs/heads/main'
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

### 2. Gemfile
```ruby
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
gem "jekyll", "~> 3.9.0"

group :jekyll_plugins do
  gem "jekyll-feed"
  gem "jekyll-sitemap"
  gem "jekyll-seo-tag"
  gem "jekyll-redirect-from"
  gem "jekyll-last-modified-at"
end

gem "webrick", "~> 1.7"
```

## ✅ Checklist Completamento

### Setup Tecnico
- [ ] Repository configurato con Jekyll
- [ ] GitHub Actions configurato per deploy automatico
- [ ] GitHub Pages attivato
- [ ] Dominio personalizzato configurato (opzionale)

### Struttura Contenuto
- [ ] Navigazione multi-livello implementata
- [ ] Sistema di versioning configurato
- [ ] Template per diversi tipi di contenuto
- [ ] Sistema di ricerca funzionante

### Contenuto
- [ ] Documentazione Getting Started completa
- [ ] Riferimenti API dettagliati
- [ ] Tutorial step-by-step
- [ ] Guide per casi d'uso comuni
- [ ] FAQ comprehensive

### Design e UX
- [ ] Design responsive su tutti i dispositivi
- [ ] Navigazione intuitiva
- [ ] Ricerca full-text efficiente
- [ ] Highlighting del codice
- [ ] Breadcrumb navigation

### SEO e Performance
- [ ] Meta tag ottimizzati
- [ ] Sitemap XML generata
- [ ] Schema markup implementato
- [ ] Velocità di caricamento ottimizzata
- [ ] Accessibilità verificata

## 🎯 Estensioni Avanzate

### 1. API Auto-documentation
```yaml
# _config.yml
api_docs:
  openapi_url: "https://api.myproject.com/openapi.json"
  auto_generate: true
  output_dir: "_api"
```

### 2. Multi-language Support
```yaml
# _config.yml
languages: ["en", "it", "es"]
default_lang: "en"
exclude_from_localization: ["assets", "admin"]
```

### 3. Advanced Analytics
```javascript
// Google Analytics 4
gtag('config', 'GA_MEASUREMENT_ID', {
  custom_map: {
    'custom_parameter_1': 'documentation_section',
    'custom_parameter_2': 'user_type'
  }
});

// Track documentation usage
gtag('event', 'documentation_view', {
  'custom_parameter_1': 'api-reference',
  'custom_parameter_2': 'developer'
});
```

---

**🎉 Congratulazioni!** Hai creato un sito di documentazione professionale e completo con Jekyll e GitHub Pages. Il sito include ricerca avanzata, versioning, API documentation, e una struttura scalabile per crescere con il tuo progetto.
