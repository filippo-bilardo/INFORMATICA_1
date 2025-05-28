# Esercizio 2: Sito di Documentazione con Jekyll

## 🎯 Obiettivo
Creare un sito di documentazione professionale per un progetto open source utilizzando Jekyll e GitHub Pages, implementando tutte le funzionalità moderne di una documentazione tecnica.

## 📋 Requisiti

### Requisiti Tecnici
- [ ] Jekyll configurato correttamente
- [ ] GitHub Pages con deploy automatico
- [ ] Tema personalizzato (non template preconfezionato)
- [ ] Sistema di navigazione multi-livello
- [ ] Ricerca funzionante
- [ ] Syntax highlighting per codice
- [ ] Responsive design
- [ ] SEO ottimizzato

### Struttura Contenuti
- [ ] **Homepage**: Introduzione e quick start
- [ ] **Getting Started**: Guide per iniziare (min. 3 pagine)
- [ ] **API Reference**: Documentazione API (min. 5 endpoint)
- [ ] **Tutorials**: Tutorial pratici (min. 4 tutorial)
- [ ] **Advanced**: Guide avanzate (min. 3 guide)
- [ ] **Changelog**: Storia delle versioni
- [ ] **Contributing**: Guide per contribuire

## 🚀 Fasi di Sviluppo

### Fase 1: Setup Jekyll (Tempo: 45 minuti)

1. **Ambiente di Sviluppo**
   ```bash
   # Installa Ruby e Jekyll (se necessario)
   gem install bundler jekyll
   
   # Crea nuovo sito Jekyll
   jekyll new project-docs
   cd project-docs
   
   # Inizializza Git
   git init
   git remote add origin https://github.com/username/project-docs.git
   ```

2. **Configurazione _config.yml**
   ```yaml
   title: "Nome Progetto - Docs"
   description: "Documentazione completa per [Nome Progetto]"
   baseurl: "/project-docs"
   url: "https://username.github.io"
   
   markdown: kramdown
   highlighter: rouge
   permalink: pretty
   
   # Collections
   collections:
     docs:
       output: true
       permalink: /:collection/:name/
     api:
       output: true
       permalink: /:collection/:name/
     tutorials:
       output: true
       permalink: /:collection/:name/
   
   # Plugins
   plugins:
     - jekyll-feed
     - jekyll-sitemap
     - jekyll-seo-tag
   
   # Navigation
   nav:
     - title: "Getting Started"
       url: "/docs/getting-started/"
       items:
         - title: "Installation"
           url: "/docs/installation/"
         - title: "Quick Start"
           url: "/docs/quick-start/"
         - title: "Configuration"
           url: "/docs/configuration/"
     
     - title: "API Reference"
       url: "/api/"
       items:
         - title: "Authentication"
           url: "/api/authentication/"
         - title: "Users"
           url: "/api/users/"
         - title: "Projects"
           url: "/api/projects/"
         - title: "Files"
           url: "/api/files/"
         - title: "Webhooks"
           url: "/api/webhooks/"
   ```

3. **Gemfile per Dipendenze**
   ```ruby
   source "https://rubygems.org"
   
   gem "github-pages", group: :jekyll_plugins
   gem "jekyll-feed"
   gem "jekyll-sitemap"  
   gem "jekyll-seo-tag"
   ```

### Fase 2: Layout e Design (Tempo: 90 minuti)

1. **Layout Principale (_layouts/default.html)**
   ```html
   <!DOCTYPE html>
   <html lang="it">
   <head>
       {% include head.html %}
   </head>
   <body>
       {% include header.html %}
       
       <div class="page-content">
           <div class="wrapper">
               <div class="content-grid">
                   {% if page.layout != 'home' %}
                       {% include sidebar.html %}
                   {% endif %}
                   
                   <main class="main-content">
                       {{ content }}
                   </main>
               </div>
           </div>
       </div>
       
       {% include footer.html %}
       {% include scripts.html %}
   </body>
   </html>
   ```

2. **Sidebar Navigation (_includes/sidebar.html)**
   ```html
   <aside class="sidebar">
       <nav class="docs-nav">
           {% for nav_item in site.nav %}
               <div class="nav-section">
                   <h3 class="nav-section-title">
                       <a href="{{ nav_item.url | relative_url }}">
                           {{ nav_item.title }}
                       </a>
                   </h3>
                   {% if nav_item.items %}
                       <ul class="nav-list">
                           {% for sub_item in nav_item.items %}
                               <li class="nav-item">
                                   <a href="{{ sub_item.url | relative_url }}" 
                                      class="nav-link {% if page.url == sub_item.url %}current{% endif %}">
                                       {{ sub_item.title }}
                                   </a>
                               </li>
                           {% endfor %}
                       </ul>
                   {% endif %}
               </div>
           {% endfor %}
       </nav>
       
       <!-- Table of Contents -->
       <div class="toc-container">
           <h4>In questa pagina</h4>
           <nav class="toc" id="toc"></nav>
       </div>
   </aside>
   ```

3. **Stili SCSS (assets/css/main.scss)**
   ```scss
   ---
   # Front matter richiesto
   ---
   
   @import "base";
   @import "layout";
   @import "syntax";
   
   // Variabili
   $primary-color: #2E7EE5;
   $text-color: #333;
   $background-color: #fdfdfd;
   $sidebar-width: 250px;
   
   // Layout principale
   .content-grid {
       display: grid;
       grid-template-columns: $sidebar-width 1fr;
       gap: 2rem;
       
       @media (max-width: 768px) {
           grid-template-columns: 1fr;
       }
   }
   
   // Sidebar
   .sidebar {
       background: #f8f9fa;
       padding: 1.5rem;
       border-radius: 8px;
       height: fit-content;
       position: sticky;
       top: 2rem;
   }
   
   // Responsive
   @media (max-width: 768px) {
       .sidebar {
           position: static;
           margin-bottom: 2rem;
       }
   }
   ```

### Fase 3: Contenuti di Documentazione (Tempo: 120 minuti)

1. **Homepage (index.md)**
   ```markdown
   ---
   layout: home
   title: "Nome Progetto"
   description: "Una libreria potente per [descrizione]"
   ---
   
   # Benvenuto in Nome Progetto
   
   Una descrizione accattivante del progetto che spiega:
   - Cosa fa il progetto
   - Perché è utile
   - Chi dovrebbe usarlo
   
   ## Quick Start
   
   ```bash
   # Installazione
   npm install nome-progetto
   
   # Uso base
   const project = require('nome-progetto');
   project.init();
   ```
   
   ## Caratteristiche Principali
   
   - ✨ **Feature 1**: Descrizione
   - 🚀 **Feature 2**: Descrizione  
   - 🔧 **Feature 3**: Descrizione
   - 📦 **Feature 4**: Descrizione
   
   ## Prossimi Passi
   
   - [Installazione]({%raw%}{{ '/docs/installation/' | relative_url }}{%endraw%})
   - [Quick Start]({%raw%}{{ '/docs/quick-start/' | relative_url }}{%endraw%})
   - [Esempi]({%raw%}{{ '/tutorials/' | relative_url }}{%endraw%})
   ```

2. **Getting Started (_docs/installation.md)**
   ```markdown
   ---
   layout: doc
   title: "Installazione"
   nav_order: 1
   parent: Getting Started
   ---
   
   # Installazione
   
   ## Requisiti di Sistema
   
   - Node.js 14.0 o superiore
   - npm 6.0 o superiore
   - Sistema operativo: Windows, macOS, Linux
   
   ## Installazione via npm
   
   ```bash
   npm install nome-progetto
   ```
   
   ## Installazione via Yarn
   
   ```bash
   yarn add nome-progetto
   ```
   
   ## Verifica Installazione
   
   ```javascript
   const project = require('nome-progetto');
   console.log(project.version); // Dovrebbe stampare la versione
   ```
   
   ## Troubleshooting
   
   ### Errore: Module not found
   
   Se ricevi questo errore, verifica che:
   - Node.js sia installato correttamente
   - Il package sia installato nella directory corretta
   
   ### Problemi di Permissions
   
   Su macOS/Linux potresti dover usare `sudo`:
   
   ```bash
   sudo npm install -g nome-progetto
   ```
   ```

3. **API Reference (_api/authentication.md)**
   ```markdown
   ---
   layout: api
   title: "Authentication"
   nav_order: 1
   parent: API Reference
   ---
   
   # Authentication
   
   L'API utilizza token di autenticazione per proteggere gli endpoint.
   
   ## Ottenere un Token
   
   ### POST `/auth/login`
   
   Autentica un utente e restituisce un token JWT.
   
   **Parametri:**
   
   | Nome | Tipo | Richiesto | Descrizione |
   |------|------|-----------|-------------|
   | email | string | Sì | Email dell'utente |
   | password | string | Sì | Password dell'utente |
   
   **Esempio Request:**
   
   ```bash
   curl -X POST https://api.example.com/auth/login \
     -H "Content-Type: application/json" \
     -d '{
       "email": "user@example.com",
       "password": "password123"
     }'
   ```
   
   **Esempio Response:**
   
   ```json
   {
     "success": true,
     "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
     "user": {
       "id": 123,
       "email": "user@example.com",
       "name": "John Doe"
     }
   }
   ```
   
   ## Usando il Token
   
   Includi il token nell'header Authorization:
   
   ```bash
   curl -H "Authorization: Bearer YOUR_TOKEN" \
     https://api.example.com/protected-endpoint
   ```
   
   ## Errori di Autenticazione
   
   | Codice | Messaggio | Descrizione |
   |--------|-----------|-------------|
   | 401 | Unauthorized | Token mancante o invalido |
   | 403 | Forbidden | Token valido ma permessi insufficienti |
   ```

4. **Tutorial (_tutorials/first-steps.md)**
   ```markdown
   ---
   layout: tutorial
   title: "Primi Passi"
   nav_order: 1
   parent: Tutorials
   ---
   
   # Primi Passi con Nome Progetto
   
   In questo tutorial imparerai a usare le funzionalità base del progetto.
   
   ## Cosa Costruiremo
   
   Creeremo una semplice applicazione che:
   - Si connette all'API
   - Recupera dati utente
   - Mostra i dati in una lista
   
   ## Passo 1: Setup del Progetto
   
   Crea una nuova directory:
   
   ```bash
   mkdir my-first-app
   cd my-first-app
   npm init -y
   npm install nome-progetto
   ```
   
   ## Passo 2: Configurazione Base
   
   Crea `index.js`:
   
   ```javascript
   const project = require('nome-progetto');
   
   // Configurazione
   project.configure({
     apiKey: 'your-api-key',
     baseUrl: 'https://api.example.com'
   });
   
   console.log('Progetto configurato!');
   ```
   
   ## Passo 3: Prima Chiamata API
   
   ```javascript
   async function getUsers() {
     try {
       const users = await project.users.list();
       console.log('Utenti trovati:', users.length);
       return users;
     } catch (error) {
       console.error('Errore:', error.message);
     }
   }
   
   getUsers();
   ```
   
   ## Risultato Atteso
   
   Quando esegui il codice:
   
   ```bash
   node index.js
   ```
   
   Dovresti vedere:
   
   ```
   Progetto configurato!
   Utenti trovati: 5
   ```
   
   ## Prossimi Passi
   
   - [Tutorial Avanzato]({%raw%}{{ '/tutorials/advanced/' | relative_url }}{%endraw%})
   - [Esempi Pratici]({%raw%}{{ '/tutorials/examples/' | relative_url }}{%endraw%})
   ```

### Fase 4: Funzionalità Avanzate (Tempo: 60 minuti)

1. **Ricerca JavaScript (assets/js/search.js)**
   ```javascript
   // Sistema di ricerca semplice
   class DocumentationSearch {
     constructor() {
       this.searchInput = document.getElementById('search-input');
       this.searchResults = document.getElementById('search-results');
       this.searchIndex = [];
       
       this.init();
     }
     
     async init() {
       await this.buildSearchIndex();
       this.bindEvents();
     }
     
     async buildSearchIndex() {
       // Carica tutte le pagine per indicizzazione
       const pages = await fetch('/search-index.json').then(r => r.json());
       this.searchIndex = pages;
     }
     
     bindEvents() {
       this.searchInput.addEventListener('input', (e) => {
         this.performSearch(e.target.value);
       });
     }
     
     performSearch(query) {
       if (query.length < 2) {
         this.hideResults();
         return;
       }
       
       const results = this.searchIndex.filter(page => 
         page.title.toLowerCase().includes(query.toLowerCase()) ||
         page.content.toLowerCase().includes(query.toLowerCase())
       );
       
       this.showResults(results);
     }
     
     showResults(results) {
       const html = results.map(result => `
         <div class="search-result">
           <h4><a href="${result.url}">${result.title}</a></h4>
           <p>${this.highlightQuery(result.excerpt, query)}</p>
         </div>
       `).join('');
       
       this.searchResults.innerHTML = html;
       this.searchResults.style.display = 'block';
     }
     
     hideResults() {
       this.searchResults.style.display = 'none';
     }
   }
   
   // Inizializza quando la pagina è caricata
   document.addEventListener('DOMContentLoaded', () => {
     new DocumentationSearch();
   });
   ```

2. **Table of Contents Generator**
   ```javascript
   // Genera automaticamente TOC dai titoli
   function generateTOC() {
     const content = document.querySelector('.main-content');
     const headings = content.querySelectorAll('h2, h3, h4');
     const toc = document.getElementById('toc');
     
     if (headings.length === 0) {
       toc.style.display = 'none';
       return;
     }
     
     const tocList = document.createElement('ul');
     
     headings.forEach((heading, index) => {
       // Aggiungi ID se non presente
       if (!heading.id) {
         heading.id = `heading-${index}`;
       }
       
       const li = document.createElement('li');
       li.className = `toc-${heading.tagName.toLowerCase()}`;
       
       const link = document.createElement('a');
       link.href = `#${heading.id}`;
       link.textContent = heading.textContent;
       
       li.appendChild(link);
       tocList.appendChild(li);
     });
     
     toc.appendChild(tocList);
   }
   
   document.addEventListener('DOMContentLoaded', generateTOC);
   ```

### Fase 5: Deploy e Ottimizzazione (Tempo: 30 minutes)

1. **GitHub Actions (.github/workflows/jekyll.yml)**
   ```yaml
   name: Build and deploy Jekyll site
   
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
         
         - name: Setup Ruby
           uses: ruby/setup-ruby@v1
           with:
             ruby-version: 3.0
             bundler-cache: true
         
         - name: Build site
           run: bundle exec jekyll build
         
         - name: Deploy to GitHub Pages
           if: github.ref == 'refs/heads/main'
           uses: peaceiris/actions-gh-pages@v3
           with:
             github_token: ${{ secrets.GITHUB_TOKEN }}
             publish_dir: ./_site
   ```

2. **SEO e Performance**
   - Aggiungi meta tag appropriati
   - Ottimizza immagini
   - Comprimi CSS/JS
   - Testa velocità di caricamento

## ✅ Criteri di Valutazione

### Struttura e Organizzazione (25 punti)
- **Collections Jekyll** (10 pts): Uso corretto di collections
- **Navigazione** (10 pts): Sistema di navigazione logico e intuitivo
- **Organizzazione Contenuti** (5 pts): Struttura chiara e logica

### Contenuto e Documentazione (35 punti)
- **Completezza** (15 pts): Tutte le sezioni richieste presenti
- **Qualità Tecnica** (10 pts): Accuratezza tecnica della documentazione
- **Esempi di Codice** (10 pts): Esempi pratici e funzionanti

### Funzionalità (25 punti)
- **Ricerca** (10 pts): Sistema di ricerca funzionante
- **Responsive Design** (10 pts): Layout adattivo per tutti i dispositivi
- **Syntax Highlighting** (5 pts): Evidenziazione codice correttamente implementata

### Aspetto e Usabilità (15 punti)
- **Design** (10 pts): Aspetto professionale e coerente
- **UX** (5 pts): Facilità di navigazione e usabilità

## 🎯 Bonus Points (max +15)
- [ ] **Versioning**: Sistema di versioning della documentazione (+3)
- [ ] **Multi-lingua**: Supporto per più lingue (+4)
- [ ] **API Testing**: Pagina per testare API direttamente (+4)
- [ ] **Feedback System**: Sistema di feedback per le pagine (+2)
- [ ] **Analytics**: Integrazione con Google Analytics (+2)

## 📤 Consegna

### Repository Structure
```
project-docs/
├── _config.yml
├── Gemfile
├── index.md
├── _layouts/
├── _includes/
├── _sass/
├── assets/
├── _docs/
├── _api/
├── _tutorials/
├── .github/workflows/
└── README.md
```

### File di Consegna
1. **URL Sito Live**: https://username.github.io/project-docs
2. **Repository GitHub**: Link al codice sorgente
3. **CONSEGNA.md** con:
   - Link sito e repository
   - Descrizione del progetto documentato
   - Funzionalità implementate
   - Screenshot delle sezioni principali
   - Istruzioni per eseguire localmente

## 💡 Suggerimenti

### Contenuto del Progetto
Documenta un progetto a tua scelta:
- Libreria JavaScript che hai creato
- API REST per un'applicazione
- Tool da riga di comando
- Plugin o estensione
- Anche un progetto ipotetico va bene!

### Best Practices
- Scrivi per il tuo pubblico target
- Usa esempi reali e testati
- Mantieni la documentazione aggiornata
- Includi troubleshooting per problemi comuni
- Usa un linguaggio chiaro e diretto

### Ispirazione
- Documentazione Vue.js
- React Docs
- GitHub API Docs
- Stripe API Docs

## 🆘 Troubleshooting

### Problemi Jekyll Comuni
- **Build fails**: Controlla sintassi YAML in _config.yml
- **CSS non carica**: Verifica percorsi in _sass
- **Liquid errors**: Controlla sintassi template Liquid

### Risorse di Aiuto
- Jekyll Documentation
- GitHub Pages Documentation
- Liquid Template Language
- Kramdown Syntax Guide

---

**Tempo stimato totale: 5-6 ore**  
**Difficoltà: ⭐⭐⭐⭐ (Avanzato)**

Questo esercizio ti darà esperienza pratica nella creazione di documentazione tecnica professionale, una competenza fondamentale per qualsiasi sviluppatore! 📚
