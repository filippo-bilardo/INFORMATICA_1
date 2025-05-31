# 04 - Domini Personalizzati e Configurazione Avanzata

## Obiettivi di Apprendimento
- Configurare domini personalizzati per GitHub Pages
- Implementare HTTPS e certificati SSL
- Gestire sottodomini e reindirizzamenti
- Ottimizzare le performance e la sicurezza
- Configurare CDN e caching
- Implementare analytics e monitoraggio

## 1. Configurazione Domini Personalizzati

### 1.1 Tipi di Domini Supportati

GitHub Pages supporta diversi tipi di domini:

```markdown
# Domini Apex (root)
example.com

# Sottodomini
www.example.com
docs.example.com
blog.example.com

# Domini di terzo livello
api.docs.example.com
```

### 1.2 Configurazione DNS

#### Record A per Domini Apex
```dns
# Record A per GitHub Pages
185.199.108.153
185.199.109.153
185.199.110.153
185.199.111.153
```

#### Record CNAME per Sottodomini
```dns
# Record CNAME
www    CNAME    username.github.io.
docs   CNAME    username.github.io.
```

### 1.3 File CNAME nel Repository

Crea un file `CNAME` nella root del repository:

```
www.example.com
```

**Esempio Completo di Configurazione:**
```bash
# 1. Aggiungi il file CNAME
echo "www.miodominio.com" > CNAME
git add CNAME
git commit -m "Add custom domain configuration"
git push origin main

# 2. Configura DNS presso il tuo provider
# A record: @ -> 185.199.108.153 (e gli altri 3 IP)
# CNAME: www -> username.github.io

# 3. Verifica la configurazione
dig www.miodominio.com
nslookup www.miodominio.com
```

## 2. HTTPS e Certificati SSL

### 2.1 Abilitazione HTTPS Automatica

GitHub Pages fornisce certificati SSL automatici:

```yaml
# .github/workflows/pages-ssl.yml
name: SSL Certificate Check
on:
  schedule:
    - cron: '0 0 * * 0'  # Controllo settimanale
  workflow_dispatch:

jobs:
  ssl-check:
    runs-on: ubuntu-latest
    steps:
      - name: Check SSL Certificate
        run: |
          echo "Checking SSL for ${{ github.repository }}"
          curl -I https://www.miodominio.com
          openssl s_client -connect www.miodominio.com:443 -servername www.miodominio.com < /dev/null
```

### 2.2 Configurazione Security Headers

Implementa security headers tramite meta tag o configurazione server:

```html
<!-- Security Meta Tags -->
<meta http-equiv="Content-Security-Policy" content="
  default-src 'self';
  script-src 'self' 'unsafe-inline' https://www.google-analytics.com;
  style-src 'self' 'unsafe-inline' https://fonts.googleapis.com;
  font-src 'self' https://fonts.gstatic.com;
  img-src 'self' data: https:;
">
<meta http-equiv="X-Content-Type-Options" content="nosniff">
<meta http-equiv="X-Frame-Options" content="DENY">
<meta http-equiv="X-XSS-Protection" content="1; mode=block">
<meta http-equiv="Strict-Transport-Security" content="max-age=31536000; includeSubDomains">
```

### 2.3 Redirect HTTP a HTTPS

```javascript
// Redirect automatico a HTTPS
if (location.protocol !== 'https:' && location.hostname !== 'localhost') {
  location.replace('https:' + window.location.href.substring(window.location.protocol.length));
}
```

## 3. Gestione Sottodomini e Reindirizzamenti

### 3.1 Configurazione Multi-Sito

```javascript
// config/domains.js
const domainConfig = {
  'www.example.com': {
    type: 'main',
    theme: 'default',
    analytics: 'GA-MAIN-ID'
  },
  'docs.example.com': {
    type: 'documentation',
    theme: 'docs',
    analytics: 'GA-DOCS-ID'
  },
  'blog.example.com': {
    type: 'blog',
    theme: 'blog',
    analytics: 'GA-BLOG-ID'
  }
};

// Carica configurazione basata sul dominio
const currentDomain = window.location.hostname;
const config = domainConfig[currentDomain] || domainConfig['www.example.com'];
```

### 3.2 Reindirizzamenti Intelligenti

```javascript
// utils/redirects.js
class RedirectManager {
  constructor() {
    this.redirectRules = new Map([
      ['/old-page', '/new-page'],
      ['/blog/2023/', '/blog/'],
      ['/docs/v1/', '/docs/latest/']
    ]);
  }

  checkRedirects() {
    const currentPath = window.location.pathname;
    
    for (const [oldPath, newPath] of this.redirectRules) {
      if (currentPath.startsWith(oldPath)) {
        const redirectUrl = currentPath.replace(oldPath, newPath);
        window.location.replace(redirectUrl);
        return;
      }
    }
  }

  addRedirect(oldPath, newPath) {
    this.redirectRules.set(oldPath, newPath);
    localStorage.setItem('redirectRules', JSON.stringify([...this.redirectRules]));
  }
}

// Inizializza il manager
const redirectManager = new RedirectManager();
redirectManager.checkRedirects();
```

## 4. Ottimizzazione Performance

### 4.1 Configurazione Caching

```javascript
// service-worker.js - Strategia di caching
const CACHE_NAME = 'site-cache-v1';
const urlsToCache = [
  '/',
  '/assets/css/style.css',
  '/assets/js/main.js',
  '/assets/images/logo.png'
];

self.addEventListener('install', event => {
  event.waitUntil(
    caches.open(CACHE_NAME)
      .then(cache => cache.addAll(urlsToCache))
  );
});

self.addEventListener('fetch', event => {
  event.respondWith(
    caches.match(event.request)
      .then(response => {
        // Cache hit - return response
        if (response) {
          return response;
        }
        return fetch(event.request);
      }
    )
  );
});
```

### 4.2 Ottimizzazione Immagini

```javascript
// utils/image-optimizer.js
class ImageOptimizer {
  static createResponsiveImage(src, alt, sizes = '100vw') {
    const img = document.createElement('img');
    
    // Genera srcset per diverse risoluzioni
    const srcset = [
      `${src}?w=320 320w`,
      `${src}?w=640 640w`,
      `${src}?w=1024 1024w`,
      `${src}?w=1920 1920w`
    ].join(', ');
    
    img.src = `${src}?w=640`; // Fallback
    img.srcset = srcset;
    img.sizes = sizes;
    img.alt = alt;
    img.loading = 'lazy';
    
    return img;
  }

  static preloadCriticalImages() {
    const criticalImages = [
      '/assets/images/hero.jpg',
      '/assets/images/logo.png'
    ];
    
    criticalImages.forEach(src => {
      const link = document.createElement('link');
      link.rel = 'preload';
      link.as = 'image';
      link.href = src;
      document.head.appendChild(link);
    });
  }
}
```

## 5. Analytics e Monitoraggio

### 5.1 Google Analytics 4

```javascript
// analytics/ga4-setup.js
class Analytics {
  constructor(measurementId) {
    this.measurementId = measurementId;
    this.initGA4();
  }

  initGA4() {
    // Carica Google Analytics
    const script = document.createElement('script');
    script.async = true;
    script.src = `https://www.googletagmanager.com/gtag/js?id=${this.measurementId}`;
    document.head.appendChild(script);

    window.dataLayer = window.dataLayer || [];
    function gtag(){dataLayer.push(arguments);}
    gtag('js', new Date());
    gtag('config', this.measurementId, {
      page_title: document.title,
      page_location: window.location.href
    });
  }

  trackEvent(eventName, parameters = {}) {
    gtag('event', eventName, {
      event_category: parameters.category || 'engagement',
      event_label: parameters.label,
      value: parameters.value,
      ...parameters
    });
  }

  trackPageView(path = window.location.pathname) {
    gtag('config', this.measurementId, {
      page_path: path
    });
  }
}
```

### 5.2 Monitoraggio Performance

```javascript
// monitoring/performance.js
class PerformanceMonitor {
  constructor() {
    this.metrics = {};
    this.initMonitoring();
  }

  initMonitoring() {
    // Core Web Vitals
    this.measureCLS();
    this.measureFID();
    this.measureLCP();
    
    // Performance Navigation API
    window.addEventListener('load', () => {
      setTimeout(() => {
        this.collectNavigationMetrics();
      }, 0);
    });
  }

  measureCLS() {
    let clsValue = 0;
    let clsEntries = [];

    const observer = new PerformanceObserver((entryList) => {
      for (const entry of entryList.getEntries()) {
        if (!entry.hadRecentInput) {
          clsEntries.push(entry);
          clsValue += entry.value;
        }
      }
      this.metrics.cls = clsValue;
    });

    observer.observe({type: 'layout-shift', buffered: true});
  }

  measureLCP() {
    const observer = new PerformanceObserver((entryList) => {
      const entries = entryList.getEntries();
      const lastEntry = entries[entries.length - 1];
      this.metrics.lcp = lastEntry.startTime;
    });

    observer.observe({type: 'largest-contentful-paint', buffered: true});
  }

  measureFID() {
    const observer = new PerformanceObserver((entryList) => {
      for (const entry of entryList.getEntries()) {
        this.metrics.fid = entry.processingStart - entry.startTime;
      }
    });

    observer.observe({type: 'first-input', buffered: true});
  }

  collectNavigationMetrics() {
    const navigation = performance.getEntriesByType('navigation')[0];
    this.metrics.ttfb = navigation.responseStart - navigation.requestStart;
    this.metrics.domLoad = navigation.domContentLoadedEventEnd - navigation.navigationStart;
    this.metrics.pageLoad = navigation.loadEventEnd - navigation.navigationStart;
  }

  sendMetrics() {
    // Invia metriche al servizio di analytics
    if (window.gtag) {
      Object.entries(this.metrics).forEach(([metric, value]) => {
        gtag('event', 'performance', {
          event_category: 'Web Vitals',
          event_label: metric,
          value: Math.round(value)
        });
      });
    }
  }
}
```

## 6. Configurazione Avanzata

### 6.1 Jekyll Configuration per Domini Personalizzati

```yaml
# _config.yml
url: "https://www.miodominio.com"
baseurl: ""
enforce_ssl: www.miodominio.com

# Plugin per SEO e sitemap
plugins:
  - jekyll-sitemap
  - jekyll-seo-tag
  - jekyll-feed
  - jekyll-redirect-from

# Configurazione SEO
title: "Il Mio Sito"
description: "Descrizione del sito per SEO"
author: "Nome Autore"
twitter:
  username: "@username"
  card: summary_large_image
facebook:
  app_id: "123456789"
  publisher: "https://www.facebook.com/page"

# Sitemap
sitemap:
  exclude:
    - /admin/
    - /private/
```

### 6.2 Automazione Deploy con Actions

```yaml
# .github/workflows/deploy-custom-domain.yml
name: Deploy to Custom Domain
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
      uses: actions/checkout@v4

    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'

    - name: Install dependencies
      run: npm ci

    - name: Build site
      run: npm run build

    - name: Test links
      run: |
        npm install -g html-proofer
        htmlproofer ./_site --disable-external

    - name: Deploy to GitHub Pages
      uses: peaceiris/actions-gh-pages@v3
      if: github.ref == 'refs/heads/main'
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./_site
        cname: www.miodominio.com

    - name: Verify deployment
      run: |
        sleep 30
        curl -f https://www.miodominio.com || exit 1
```

## 7. Troubleshooting Comuni

### 7.1 Problemi DNS

```bash
# Diagnostica DNS
dig +trace www.miodominio.com
nslookup www.miodominio.com 8.8.8.8
host www.miodominio.com

# Verifica propagazione DNS globale
curl -s "https://dns.google/resolve?name=www.miodominio.com&type=A" | jq .
```

### 7.2 Problemi SSL/TLS

```bash
# Test SSL
openssl s_client -connect www.miodominio.com:443 -servername www.miodominio.com
curl -I https://www.miodominio.com

# Verifica certificato
echo | openssl s_client -connect www.miodominio.com:443 2>/dev/null | openssl x509 -text
```

### 7.3 Debugging Common Issues

| Problema | Causa | Soluzione |
|----------|-------|-----------|
| "Domain not found" | DNS non configurato | Verifica record A/CNAME |
| "SSL error" | Certificato non propagato | Attendi 24-48 ore |
| "404 on custom domain" | CNAME file mancante | Aggiungi file CNAME |
| "Mixed content" | HTTP su HTTPS | Usa solo HTTPS URLs |

## 8. Best Practices

### 8.1 Sicurezza
- ✅ Usa sempre HTTPS
- ✅ Implementa security headers
- ✅ Mantieni aggiornate le dipendenze
- ✅ Monitora il certificato SSL

### 8.2 Performance
- ✅ Abilita caching
- ✅ Ottimizza immagini
- ✅ Minimizza CSS/JS
- ✅ Usa CDN quando possibile

### 8.3 SEO
- ✅ Configura sitemap.xml
- ✅ Implementa structured data
- ✅ Ottimizza meta tag
- ✅ Monitora Core Web Vitals

## Quiz di Verifica

### Domanda 1
Quali record DNS sono necessari per configurare un dominio apex su GitHub Pages?
- a) Solo record CNAME
- b) Solo record A
- c) Record A per gli IP di GitHub Pages
- d) Record MX

### Domanda 2
Dove deve essere posizionato il file CNAME nel repository?
- a) Nella cartella `_config`
- b) Nella root del repository
- c) Nella cartella `assets`
- d) Non è necessario

### Domanda 3
Quanto tempo può richiedere la propagazione di un certificato SSL automatico?
- a) 5 minuti
- b) 1 ora
- c) Fino a 24-48 ore
- d) Una settimana

### Domanda 4
Qual è il metodo migliore per reindirizzare HTTP a HTTPS?
- a) Configurazione server
- b) JavaScript redirect
- c) Meta refresh
- d) GitHub Pages lo fa automaticamente

### Domanda 5
Quale strumento è più utile per diagnosticare problemi DNS?
- a) ping
- b) dig
- c) wget
- d) curl

## Esercizi Pratici

### Esercizio 1: Configurazione Dominio Base
Configura un dominio personalizzato per il tuo sito GitHub Pages:
1. Acquista/configura un dominio
2. Imposta i record DNS
3. Aggiungi il file CNAME
4. Verifica il deployment

### Esercizio 2: Implementazione Security Headers
Implementa security headers e verifica la sicurezza:
1. Aggiungi meta tag security
2. Implementa Content Security Policy
3. Testa con SSL Labs
4. Configura HSTS

### Esercizio 3: Monitoraggio Avanzato
Implementa un sistema di monitoraggio completo:
1. Configura Google Analytics 4
2. Implementa Core Web Vitals tracking
3. Crea dashboard di monitoraggio
4. Imposta alerting per downtime

---

## Navigazione

⬅️ **Precedente**: [03 - Documentazione Professionale](03-documentation-practices.md)

➡️ **Successivo**: [Modulo 23 - GitHub Actions](../../23-GitHub-Actions/README.md)

🏠 **Home**: [Indice Generale](../../README.md)
