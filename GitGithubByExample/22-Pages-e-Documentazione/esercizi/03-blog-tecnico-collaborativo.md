# Esercizio 3: Blog Tecnico Multi-autore

## 🎯 Obiettivo
Creare un blog tecnico collaborativo utilizzando GitHub Pages e Jekyll, con supporto per articoli multi-autore, categorizzazione avanzata, e funzionalità moderne di un blog professionale.

## 📋 Requisiti

### Funzionalità Core
- [ ] Sistema multi-autore con profili
- [ ] Categorizzazione e tagging degli articoli
- [ ] Sistema di commenti (Disqus o GitHalk)
- [ ] Newsletter subscription
- [ ] Feed RSS completo
- [ ] Sitemap XML automatica
- [ ] Ricerca full-text negli articoli
- [ ] Paginazione articoli
- [ ] Articoli correlati

### Contenuti Richiesti
- [ ] Minimo 10 articoli tecnici di qualità
- [ ] Almeno 3 autori diversi
- [ ] 5+ categorie tematiche
- [ ] Pagina About completa
- [ ] Privacy Policy e Cookie Policy
- [ ] Archivio per anno/mese

## 🚀 Fasi di Sviluppo

### Fase 1: Architettura Jekyll (Tempo: 60 minuti)

1. **Setup Iniziale**
   ```bash
   jekyll new tech-blog
   cd tech-blog
   
   # Struttura directory personalizzata
   mkdir -p _authors _data assets/images/authors assets/images/posts
   ```

2. **Configurazione Avanzata (_config.yml)**
   ```yaml
   title: "TechBlog Pro"
   tagline: "Il futuro della tecnologia, oggi"
   description: "Blog tecnico collaborativo su sviluppo web, AI, DevOps e innovazione tecnologica"
   baseurl: "/tech-blog"
   url: "https://username.github.io"
   
   # Author principale
   author:
     name: "Team TechBlog"
     email: "info@techblog.com"
     twitter: "techblogpro"
     github: "techblogpro"
   
   # Build settings
   markdown: kramdown
   highlighter: rouge
   permalink: /:year/:month/:day/:title/
   timezone: Europe/Rome
   
   # Kramdown settings
   kramdown:
     input: GFM
     syntax_highlighter: rouge
     syntax_highlighter_opts:
       css_class: 'highlight'
       block:
         line_numbers: true
   
   # Collections
   collections:
     authors:
       output: true
       permalink: /autori/:name/
   
   # Plugins
   plugins:
     - jekyll-feed
     - jekyll-sitemap
     - jekyll-seo-tag
     - jekyll-paginate
     - jekyll-archives
   
   # Pagination
   paginate: 6
   paginate_path: "/page:num/"
   
   # Jekyll Archives
   jekyll-archives:
     enabled:
       - categories
       - tags
       - year
       - month
     layouts:
       year: archive-year
       month: archive-month
       category: archive-category
       tag: archive-tag
     permalinks:
       year: /archivio/:year/
       month: /archivio/:year/:month/
       category: /categoria/:name/
       tag: /tag/:name/
   
   # Defaults
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
   
   # Social sharing
   social:
     twitter: "techblogpro"
     facebook: "techblogpro"
     linkedin: "company/techblogpro"
     github: "techblogpro"
   
   # Comments (Disqus)
   disqus:
     shortname: "techblogpro"
   
   # Google Analytics
   google_analytics: "UA-XXXXXXXXX-X"
   
   # Newsletter (Mailchimp)
   mailchimp:
     action_url: "https://your-mailchimp-url"
     list_id: "your-list-id"
   
   # Exclude
   exclude:
     - Gemfile
     - Gemfile.lock
     - node_modules
     - vendor
     - .sass-cache
     - .jekyll-cache
   ```

3. **Struttura Autori (_authors/mario-rossi.md)**
   ```markdown
   ---
   name: mario-rossi
   display_name: Mario Rossi
   position: Senior Full Stack Developer
   bio: "Sviluppatore con 8+ anni di esperienza in JavaScript, Python e architetture cloud. Appassionato di AI e machine learning."
   avatar: /assets/images/authors/mario-rossi.jpg
   email: mario.rossi@techblog.com
   website: https://mariorossi.dev
   social:
     twitter: mario_rossi_dev
     github: mariorossi
     linkedin: in/mario-rossi-dev
   expertise:
     - JavaScript
     - React
     - Node.js
     - Python
     - AWS
     - DevOps
   ---
   
   Mario è uno sviluppatore senior con oltre 8 anni di esperienza nello sviluppo di applicazioni web scalabili. Ha lavorato per startup innovative e grandi aziende, specializzandosi in architetture microservizi e sviluppo cloud-native.
   
   Attualmente si occupa di lead technical per progetti enterprise, mentoring di junior developer e ricerca su tecnologie emergenti come Web3 e intelligenza artificiale.
   
   ## Articoli Recenti
   
   {% assign author_posts = site.posts | where: 'author', page.name %}
   {% for post in author_posts limit: 5 %}
   - [{{ post.title }}]({{ post.url | relative_url }}) - {{ post.date | date: "%d %B %Y" }}
   {% endfor %}
   ```

### Fase 2: Design e Layout (Tempo: 90 minuti)

1. **Layout Post (_layouts/post.html)**
   ```html
   ---
   layout: default
   ---
   
   {% assign author = site.authors | where: 'name', page.author | first %}
   
   <article class="post" itemscope itemtype="http://schema.org/BlogPosting">
     <header class="post-header">
       <div class="post-meta">
         <time datetime="{{ page.date | date_to_xmlschema }}" itemprop="datePublished">
           {{ page.date | date: "%d %B %Y" }}
         </time>
         
         {% if page.categories %}
           <span class="post-categories">
             {% for category in page.categories %}
               <a href="{{ site.baseurl }}/categoria/{{ category | slugify }}/" class="category-link">
                 {{ category }}
               </a>
             {% endfor %}
           </span>
         {% endif %}
         
         <span class="reading-time">
           {% assign words = content | number_of_words %}
           {% if words < 360 %}
             Lettura di 1 minuto
           {% else %}
             Lettura di {{ words | divided_by:180 }} minuti
           {% endif %}
         </span>
       </div>
       
       <h1 class="post-title" itemprop="name headline">{{ page.title | escape }}</h1>
       
       {% if page.subtitle %}
         <p class="post-subtitle">{{ page.subtitle }}</p>
       {% endif %}
       
       {% if author %}
         <div class="post-author">
           <img src="{{ author.avatar | relative_url }}" alt="{{ author.display_name }}" class="author-avatar">
           <div class="author-info">
             <span class="author-name">
               <a href="{{ author.url | relative_url }}">{{ author.display_name }}</a>
             </span>
             <span class="author-position">{{ author.position }}</span>
           </div>
         </div>
       {% endif %}
     </header>
     
     {% if page.featured_image %}
       <div class="post-featured-image">
         <img src="{{ page.featured_image | relative_url }}" 
              alt="{{ page.title }}" 
              itemprop="image">
       </div>
     {% endif %}
     
     <div class="post-content" itemprop="articleBody">
       {{ content }}
     </div>
     
     <footer class="post-footer">
       {% if page.tags %}
         <div class="post-tags">
           <span class="tags-label">Tag:</span>
           {% for tag in page.tags %}
             <a href="{{ site.baseurl }}/tag/{{ tag | slugify }}/" class="tag-link">
               #{{ tag }}
             </a>
           {% endfor %}
         </div>
       {% endif %}
       
       {% if page.share %}
         <div class="post-share">
           <span class="share-label">Condividi:</span>
           <a href="https://twitter.com/intent/tweet?text={{ page.title | uri_escape }}&url={{ page.url | absolute_url }}&via={{ site.social.twitter }}" 
              target="_blank" class="share-twitter">Twitter</a>
           <a href="https://www.facebook.com/sharer/sharer.php?u={{ page.url | absolute_url }}" 
              target="_blank" class="share-facebook">Facebook</a>
           <a href="https://www.linkedin.com/sharing/share-offsite/?url={{ page.url | absolute_url }}" 
              target="_blank" class="share-linkedin">LinkedIn</a>
         </div>
       {% endif %}
       
       {% if author %}
         <div class="author-card">
           <img src="{{ author.avatar | relative_url }}" alt="{{ author.display_name }}" class="author-card-avatar">
           <div class="author-card-content">
             <h4>Scritto da <a href="{{ author.url | relative_url }}">{{ author.display_name }}</a></h4>
             <p>{{ author.bio }}</p>
             <div class="author-social">
               {% if author.social.twitter %}
                 <a href="https://twitter.com/{{ author.social.twitter }}" target="_blank">Twitter</a>
               {% endif %}
               {% if author.social.github %}
                 <a href="https://github.com/{{ author.social.github }}" target="_blank">GitHub</a>
               {% endif %}
               {% if author.social.linkedin %}
                 <a href="https://linkedin.com/{{ author.social.linkedin }}" target="_blank">LinkedIn</a>
               {% endif %}
             </div>
           </div>
         </div>
       {% endif %}
     </footer>
   </article>
   
   <!-- Related Posts -->
   {% assign related_posts = site.related_posts | limit: 3 %}
   {% if related_posts.size > 0 %}
     <section class="related-posts">
       <h3>Articoli Correlati</h3>
       <div class="related-posts-grid">
         {% for post in related_posts %}
           <article class="related-post">
             {% if post.featured_image %}
               <img src="{{ post.featured_image | relative_url }}" alt="{{ post.title }}">
             {% endif %}
             <div class="related-post-content">
               <h4><a href="{{ post.url | relative_url }}">{{ post.title }}</a></h4>
               <time>{{ post.date | date: "%d %B %Y" }}</time>
             </div>
           </article>
         {% endfor %}
       </div>
     </section>
   {% endif %}
   
   <!-- Comments -->
   {% if page.comments and site.disqus.shortname %}
     <section class="comments">
       <h3>Commenti</h3>
       <div id="disqus_thread"></div>
       <script>
         var disqus_config = function () {
           this.page.url = '{{ page.url | absolute_url }}';
           this.page.identifier = '{{ page.url }}';
         };
         
         (function() {
           var d = document, s = d.createElement('script');
           s.src = 'https://{{ site.disqus.shortname }}.disqus.com/embed.js';
           s.setAttribute('data-timestamp', +new Date());
           (d.head || d.body).appendChild(s);
         })();
       </script>
       <noscript>
         Abilita JavaScript per vedere i <a href="https://disqus.com/?ref_noscript">commenti powered by Disqus.</a>
       </noscript>
     </section>
   {% endif %}
   ```

2. **Homepage con Featured Posts (index.html)**
   ```html
   ---
   layout: default
   pagination:
     enabled: true
   ---
   
   <!-- Hero Section -->
   <section class="hero">
     <div class="hero-content">
       <h1>{{ site.title }}</h1>
       <p class="hero-tagline">{{ site.tagline }}</p>
       <p class="hero-description">{{ site.description }}</p>
     </div>
   </section>
   
   <!-- Featured Posts -->
   {% assign featured_posts = site.posts | where: 'featured', true | limit: 3 %}
   {% if featured_posts.size > 0 %}
     <section class="featured-posts">
       <h2>Articoli in Evidenza</h2>
       <div class="featured-posts-grid">
         {% for post in featured_posts %}
           <article class="featured-post">
             {% if post.featured_image %}
               <div class="featured-post-image">
                 <img src="{{ post.featured_image | relative_url }}" alt="{{ post.title }}">
               </div>
             {% endif %}
             <div class="featured-post-content">
               <div class="post-meta">
                 <time>{{ post.date | date: "%d %B %Y" }}</time>
                 {% if post.categories.first %}
                   <span class="category">{{ post.categories.first }}</span>
                 {% endif %}
               </div>
               <h3><a href="{{ post.url | relative_url }}">{{ post.title }}</a></h3>
               <p>{{ post.excerpt | strip_html | truncatewords: 25 }}</p>
               
               {% assign author = site.authors | where: 'name', post.author | first %}
               {% if author %}
                 <div class="post-author-mini">
                   <img src="{{ author.avatar | relative_url }}" alt="{{ author.display_name }}">
                   <span>{{ author.display_name }}</span>
                 </div>
               {% endif %}
             </div>
           </article>
         {% endfor %}
       </div>
     </section>
   {% endif %}
   
   <!-- Recent Posts -->
   <section class="recent-posts">
     <h2>Articoli Recenti</h2>
     <div class="posts-grid">
       {% assign recent_posts = paginator.posts | where_exp: "post", "post.featured != true" %}
       {% for post in recent_posts %}
         <article class="post-card">
           {% if post.featured_image %}
             <div class="post-card-image">
               <img src="{{ post.featured_image | relative_url }}" alt="{{ post.title }}">
             </div>
           {% endif %}
           <div class="post-card-content">
             <div class="post-meta">
               <time>{{ post.date | date: "%d %B %Y" }}</time>
               {% if post.categories.first %}
                 <span class="category">{{ post.categories.first }}</span>
               {% endif %}
             </div>
             <h3><a href="{{ post.url | relative_url }}">{{ post.title }}</a></h3>
             <p>{{ post.excerpt | strip_html | truncatewords: 20 }}</p>
             
             <div class="post-card-footer">
               {% assign author = site.authors | where: 'name', post.author | first %}
               {% if author %}
                 <div class="post-author-mini">
                   <img src="{{ author.avatar | relative_url }}" alt="{{ author.display_name }}">
                   <span>{{ author.display_name }}</span>
                 </div>
               {% endif %}
               
               <div class="reading-time">
                 {% assign words = post.content | number_of_words %}
                 {{ words | divided_by:180 | at_least: 1 }} min
               </div>
             </div>
           </div>
         </article>
       {% endfor %}
     </div>
   
     <!-- Pagination -->
     {% if paginator.total_pages > 1 %}
       <nav class="pagination">
         {% if paginator.previous_page %}
           <a href="{{ paginator.previous_page_path | relative_url }}" class="pagination-link pagination-prev">
             ← Articoli più recenti
           </a>
         {% endif %}
         
         <div class="pagination-numbers">
           {% for page in (1..paginator.total_pages) %}
             {% if page == paginator.page %}
               <span class="pagination-number current">{{ page }}</span>
             {% elsif page == 1 %}
               <a href="{{ '/' | relative_url }}" class="pagination-number">{{ page }}</a>
             {% else %}
               <a href="{{ site.paginate_path | relative_url | replace: ':num', page }}" class="pagination-number">{{ page }}</a>
             {% endif %}
           {% endfor %}
         </div>
         
         {% if paginator.next_page %}
           <a href="{{ paginator.next_page_path | relative_url }}" class="pagination-link pagination-next">
             Articoli meno recenti →
           </a>
         {% endif %}
       </nav>
     {% endif %}
   </section>
   
   <!-- Newsletter Signup -->
   {% if site.mailchimp.action_url %}
     <section class="newsletter">
       <div class="newsletter-content">
         <h3>Rimani Aggiornato</h3>
         <p>Ricevi i nostri migliori articoli direttamente nella tua inbox.</p>
         <form action="{{ site.mailchimp.action_url }}" method="post" class="newsletter-form">
           <input type="email" name="EMAIL" placeholder="La tua email" required>
           <input type="hidden" name="b_{{ site.mailchimp.list_id }}" value="">
           <button type="submit">Iscriviti</button>
         </form>
       </div>
     </section>
   {% endif %}
   ```

### Fase 3: Contenuti di Qualità (Tempo: 120 minuti)

1. **Articolo Esempio (_posts/2025-05-28-guida-react-hooks.md)**
   ```markdown
   ---
   layout: post
   title: "Guida Completa ai React Hooks: Da useState a useCallback"
   subtitle: "Tutto quello che devi sapere sui hooks di React per scrivere codice più pulito e performante"
   date: 2025-05-28 10:00:00 +0100
   author: mario-rossi
   categories: [React, JavaScript, Frontend]
   tags: [hooks, useState, useEffect, performance, best-practices]
   featured: true
   featured_image: /assets/images/posts/react-hooks-guide.jpg
   excerpt: "Una guida approfondita ai React Hooks, dalle basi ai pattern avanzati, con esempi pratici e best practices per scrivere componenti più efficienti."
   ---
   
   I React Hooks hanno rivoluzionato il modo in cui scriviamo componenti React. Introdotti nella versione 16.8, permettono di utilizzare lo state e altre funzionalità di React nei functional components, eliminando la necessità di class components nella maggior parte dei casi.
   
   ## Perché i Hooks?
   
   Prima dei hooks, gestire lo state nei functional components era impossibile. Dovevamo convertire i nostri componenti in classi ogni volta che avevamo bisogno di stato locale o lifecycle methods. I hooks risolvono questo problema e molto altro:
   
   - **Riutilizzo della logica**: Condividere logica stateful tra componenti
   - **Componenti più semplici**: Meno boilerplate code
   - **Migliore testing**: Più facile da testare
   - **Performance**: Ottimizzazioni più granulari
   
   ## useState: Il Hook Fondamentale
   
   `useState` è probabilmente il hook che userai più spesso. Permette di aggiungere stato locale a un functional component.
   
   ```javascript
   import React, { useState } from 'react';
   
   function Counter() {
     const [count, setCount] = useState(0);
   
     return (
       <div>
         <p>Hai cliccato {count} volte</p>
         <button onClick={() => setCount(count + 1)}>
           Clicca qui
         </button>
       </div>
     );
   }
   ```
   
   ### Stato con Oggetti e Array
   
   Quando lavori con oggetti o array, ricorda che `useState` non fa merge automatico come `this.setState`:
   
   ```javascript
   function UserProfile() {
     const [user, setUser] = useState({
       name: '',
       email: '',
       age: 0
     });
   
     const updateName = (newName) => {
       setUser(prevUser => ({
         ...prevUser,
         name: newName
       }));
     };
   
     return (
       <form>
         <input 
           value={user.name}
           onChange={(e) => updateName(e.target.value)}
           placeholder="Nome"
         />
         {/* Altri campi... */}
       </form>
     );
   }
   ```
   
   ## useEffect: Gestire Side Effects
   
   `useEffect` combina `componentDidMount`, `componentDidUpdate` e `componentWillUnmount` in un'unica API:
   
   ```javascript
   import React, { useState, useEffect } from 'react';
   
   function UserData({ userId }) {
     const [user, setUser] = useState(null);
     const [loading, setLoading] = useState(true);
   
     useEffect(() => {
       let cancelled = false;
   
       async function fetchUser() {
         try {
           setLoading(true);
           const response = await fetch(`/api/users/${userId}`);
           const userData = await response.json();
           
           if (!cancelled) {
             setUser(userData);
           }
         } catch (error) {
           if (!cancelled) {
             console.error('Errore nel caricamento utente:', error);
           }
         } finally {
           if (!cancelled) {
             setLoading(false);
           }
         }
       }
   
       fetchUser();
   
       // Cleanup function
       return () => {
         cancelled = true;
       };
     }, [userId]); // Dependency array
   
     if (loading) return <div>Caricamento...</div>;
     if (!user) return <div>Utente non trovato</div>;
   
     return (
       <div>
         <h2>{user.name}</h2>
         <p>{user.email}</p>
       </div>
     );
   }
   ```
   
   ### Dependency Array: La Chiave delle Performance
   
   La dependency array è cruciale per le performance. Specifica quando l'effect deve essere rieseguito:
   
   ```javascript
   // Esegue solo al mount
   useEffect(() => {
     // codice
   }, []);
   
   // Esegue ogni render
   useEffect(() => {
     // codice
   });
   
   // Esegue quando userId cambia
   useEffect(() => {
     // codice
   }, [userId]);
   ```
   
   ## useMemo: Ottimizzazione dei Calcoli
   
   `useMemo` memorizza il risultato di un calcolo costoso:
   
   ```javascript
   import React, { useMemo, useState } from 'react';
   
   function ExpensiveComponent({ items, filter }) {
     const [sortOrder, setSortOrder] = useState('asc');
   
     const processedItems = useMemo(() => {
       console.log('Ricalcolo items processati...');
       
       return items
         .filter(item => item.name.includes(filter))
         .sort((a, b) => {
           if (sortOrder === 'asc') {
             return a.name.localeCompare(b.name);
           }
           return b.name.localeCompare(a.name);
         });
     }, [items, filter, sortOrder]);
   
     return (
       <div>
         <button onClick={() => setSortOrder(sortOrder === 'asc' ? 'desc' : 'asc')}>
           Ordine: {sortOrder}
         </button>
         <ul>
           {processedItems.map(item => (
             <li key={item.id}>{item.name}</li>
           ))}
         </ul>
       </div>
     );
   }
   ```
   
   ## useCallback: Ottimizzazione delle Funzioni
   
   `useCallback` memorizza una funzione per evitare re-rendering non necessari:
   
   ```javascript
   import React, { useCallback, useState, memo } from 'react';
   
   const ChildComponent = memo(({ onClick, value }) => {
     console.log('ChildComponent renderizzato');
     return <button onClick={onClick}>{value}</button>;
   });
   
   function ParentComponent() {
     const [count, setCount] = useState(0);
     const [otherState, setOtherState] = useState('');
   
     // Senza useCallback, questa funzione viene ricreata ad ogni render
     const handleClick = useCallback(() => {
       setCount(prev => prev + 1);
     }, []); // Nessuna dipendenza, la funzione è sempre la stessa
   
     return (
       <div>
         <input 
           value={otherState}
           onChange={(e) => setOtherState(e.target.value)}
         />
         <ChildComponent onClick={handleClick} value={count} />
       </div>
     );
   }
   ```
   
   ## Hook Personalizzati: Riutilizzo della Logica
   
   Gli hook personalizzati permettono di estrarre e riutilizzare logica stateful:
   
   ```javascript
   // Custom hook per gestire API calls
   function useApi(url) {
     const [data, setData] = useState(null);
     const [loading, setLoading] = useState(true);
     const [error, setError] = useState(null);
   
     useEffect(() => {
       let cancelled = false;
   
       async function fetchData() {
         try {
           setLoading(true);
           setError(null);
           
           const response = await fetch(url);
           if (!response.ok) {
             throw new Error(`HTTP error! status: ${response.status}`);
           }
           
           const result = await response.json();
           
           if (!cancelled) {
             setData(result);
           }
         } catch (err) {
           if (!cancelled) {
             setError(err.message);
           }
         } finally {
           if (!cancelled) {
             setLoading(false);
           }
         }
       }
   
       fetchData();
   
       return () => {
         cancelled = true;
       };
     }, [url]);
   
     return { data, loading, error };
   }
   
   // Utilizzo del custom hook
   function UsersList() {
     const { data: users, loading, error } = useApi('/api/users');
   
     if (loading) return <div>Caricamento...</div>;
     if (error) return <div>Errore: {error}</div>;
   
     return (
       <ul>
         {users?.map(user => (
           <li key={user.id}>{user.name}</li>
         ))}
       </ul>
     );
   }
   ```
   
   ## Best Practices e Regole
   
   ### 1. Regole dei Hooks
   
   - Chiama gli hooks sempre al top level, mai dentro loop, condizioni o funzioni annidate
   - Chiama gli hooks solo da componenti React o custom hooks
   
   ```javascript
   // ❌ Sbagliato
   function BadComponent({ condition }) {
     if (condition) {
       const [state, setState] = useState(0); // Hook condizionale
     }
     return <div>Bad</div>;
   }
   
   // ✅ Corretto
   function GoodComponent({ condition }) {
     const [state, setState] = useState(0);
     
     if (condition) {
       // Usa state qui
     }
     
     return <div>Good</div>;
   }
   ```
   
   ### 2. Ottimizzazione delle Dipendenze
   
   ```javascript
   // ❌ Dipendenza mancante
   function BadEffect({ userId }) {
     const [user, setUser] = useState(null);
     
     useEffect(() => {
       fetchUser(userId).then(setUser);
     }, []); // userId mancante!
     
     return <div>{user?.name}</div>;
   }
   
   // ✅ Dipendenze corrette
   function GoodEffect({ userId }) {
     const [user, setUser] = useState(null);
     
     useEffect(() => {
       fetchUser(userId).then(setUser);
     }, [userId]); // Dipendenza corretta
     
     return <div>{user?.name}</div>;
   }
   ```
   
   ### 3. Evitare Re-render Inutili
   
   ```javascript
   // ❌ Oggetto ricreato ad ogni render
   function BadComponent() {
     const [name, setName] = useState('');
     
     const config = { // Nuovo oggetto ad ogni render
       apiKey: 'abc123',
       timeout: 5000
     };
   
     return <ApiComponent config={config} />;
   }
   
   // ✅ Oggetto memorizzato
   function GoodComponent() {
     const [name, setName] = useState('');
     
     const config = useMemo(() => ({
       apiKey: 'abc123',
       timeout: 5000
     }), []); // Dipendenze vuote = creato solo una volta
   
     return <ApiComponent config={config} />;
   }
   ```
   
   ## Conclusioni
   
   I React Hooks hanno semplificato enormemente lo sviluppo di componenti React, permettendo di scrivere codice più pulito, testabile e performante. Le chiavi del successo sono:
   
   1. **Comprendere il ciclo di vita**: Come e quando i hooks vengono eseguiti
   2. **Gestire correttamente le dipendenze**: Per evitare bug e problemi di performance  
   3. **Creare hook personalizzati**: Per riutilizzare logica comune
   4. **Ottimizzare quando necessario**: Con useMemo e useCallback
   
   Con questi strumenti a disposizione, potrai creare applicazioni React moderne, efficienti e facilmente manutenibili.
   
   ## Risorse Utili
   
   - [Documentazione ufficiale React Hooks](https://react.dev/reference/react)
   - [Rules of Hooks](https://react.dev/warnings/invalid-hook-call-warning)
   - [Custom Hooks](https://react.dev/learn/reusing-logic-with-custom-hooks)
   - [React DevTools Profiler](https://react.dev/learn/react-developer-tools)
   
   ---
   
   *Hai domande sui React Hooks? Scrivile nei commenti qui sotto! Sarò felice di aiutarti a risolvere qualsiasi dubbio.* 🚀
   ```

### Fase 4: Funzionalità Avanzate (Tempo: 60 minuti)

1. **Sistema di Ricerca (assets/js/search.js)**
   ```javascript
   class BlogSearch {
     constructor() {
       this.searchInput = document.getElementById('search-input');
       this.searchResults = document.getElementById('search-results');
       this.searchOverlay = document.getElementById('search-overlay');
       this.posts = [];
       
       this.init();
     }
   
     async init() {
       await this.loadPosts();
       this.bindEvents();
     }
   
     async loadPosts() {
       try {
         const response = await fetch('/search.json');
         this.posts = await response.json();
       } catch (error) {
         console.error('Errore nel caricamento dei post:', error);
       }
     }
   
     bindEvents() {
       this.searchInput.addEventListener('input', this.debounce(this.handleSearch.bind(this), 300));
       this.searchInput.addEventListener('focus', this.showSearch.bind(this));
       
       // Chiudi con ESC
       document.addEventListener('keydown', (e) => {
         if (e.key === 'Escape') {
           this.hideSearch();
         }
       });
       
       // Chiudi cliccando fuori
       this.searchOverlay.addEventListener('click', (e) => {
         if (e.target === this.searchOverlay) {
           this.hideSearch();
         }
       });
     }
   
     handleSearch(event) {
       const query = event.target.value.toLowerCase().trim();
       
       if (query.length < 2) {
         this.hideResults();
         return;
       }
   
       const results = this.posts.filter(post => 
         post.title.toLowerCase().includes(query) ||
         post.content.toLowerCase().includes(query) ||
         post.tags.some(tag => tag.toLowerCase().includes(query)) ||
         post.categories.some(cat => cat.toLowerCase().includes(query))
       ).slice(0, 8); // Limita a 8 risultati
   
       this.showResults(results, query);
     }
   
     showResults(results, query) {
       if (results.length === 0) {
         this.searchResults.innerHTML = `
           <div class="search-no-results">
             <p>Nessun risultato per "<strong>${query}</strong>"</p>
             <p>Prova a cercare con parole chiave diverse.</p>
           </div>
         `;
       } else {
         this.searchResults.innerHTML = results.map(post => `
           <article class="search-result">
             <div class="search-result-content">
               <h3><a href="${post.url}">${this.highlightQuery(post.title, query)}</a></h3>
               <p>${this.highlightQuery(this.truncate(post.content, 150), query)}</p>
               <div class="search-result-meta">
                 <time>${post.date}</time>
                 ${post.categories.map(cat => `<span class="category">${cat}</span>`).join('')}
               </div>
             </div>
           </article>
         `).join('');
       }
       
       this.searchResults.style.display = 'block';
     }
   
     hideResults() {
       this.searchResults.style.display = 'none';
     }
   
     showSearch() {
       this.searchOverlay.style.display = 'block';
       document.body.style.overflow = 'hidden';
     }
   
     hideSearch() {
       this.searchOverlay.style.display = 'none';
       document.body.style.overflow = '';
       this.searchInput.value = '';
       this.hideResults();
     }
   
     highlightQuery(text, query) {
       const regex = new RegExp(`(${query})`, 'gi');
       return text.replace(regex, '<mark>$1</mark>');
     }
   
     truncate(text, length) {
       return text.length > length ? text.substring(0, length) + '...' : text;
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
   
   // Inizializza quando la pagina è caricata
   document.addEventListener('DOMContentLoaded', () => {
     new BlogSearch();
   });
   ```

2. **JSON Feed per Ricerca (search.json)**
   ```json
   ---
   layout: null
   ---
   [
     {% for post in site.posts %}
       {
         "title": {{ post.title | jsonify }},
         "url": {{ post.url | relative_url | jsonify }},
         "date": {{ post.date | date: "%d %B %Y" | jsonify }},
         "content": {{ post.content | strip_html | truncatewords: 50 | jsonify }},
         "categories": {{ post.categories | jsonify }},
         "tags": {{ post.tags | jsonify }},
         "author": {{ post.author | jsonify }}
       }{% unless forloop.last %},{% endunless %}
     {% endfor %}
   ]
   ```

## ✅ Criteri di Valutazione

### Contenuto e Qualità (40 punti)
- **Articoli Tecnici** (20 pts): Qualità, profondità e accuratezza degli articoli
- **Diversità Contenuti** (10 pts): Varietà di argomenti e autori
- **SEO e Metadata** (10 pts): Ottimizzazione per motori di ricerca

### Funzionalità (35 punti)
- **Sistema Multi-autore** (10 pts): Gestione corretta di autori multipli
- **Ricerca e Navigazione** (15 pts): Sistema di ricerca funzionante e navigazione intuitiva
- **Funzionalità Social** (10 pts): Condivisione, commenti, newsletter

### Design e UX (25 punti)
- **Design Responsive** (15 pts): Layout adattivo e mobile-friendly
- **User Experience** (10 pts): Facilità di navigazione e lettura

## 🎯 Bonus Points (max +20)
- [ ] **Analytics Dashboard**: Pagina con statistiche del blog (+5)
- [ ] **AMP Support**: Versioni AMP degli articoli (+4)
- [ ] **PWA Features**: Service worker e offline reading (+6)
- [ ] **Dark Mode**: Tema scuro/chiaro (+3)
- [ ] **Multi-lingua**: Supporto italiano/inglese (+2)

---

**Tempo stimato totale: 5-6 ore**  
**Difficoltà: ⭐⭐⭐⭐⭐ (Esperto)**

Questo esercizio ti permetterà di creare un blog tecnico professionale che potrai usare come piattaforma per condividere le tue conoscenze e costruire la tua presenza online nel mondo tech! 📝
