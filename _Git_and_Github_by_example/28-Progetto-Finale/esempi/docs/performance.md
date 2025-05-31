# Performance Optimization Guide

## JavaScript Performance Best Practices

### 1. Memory Management
```javascript
// ❌ Evitare memory leaks
let globalArray = [];
function addData(data) {
    globalArray.push(data); // Accumula memoria senza limite
}

// ✅ Gestione corretta della memoria
function processData(data) {
    let localArray = [];
    localArray.push(data);
    // La memoria viene liberata alla fine della funzione
    return localArray.filter(item => item.isValid);
}
```

### 2. DOM Performance
```javascript
// ❌ Multiple DOM manipulations
for (let i = 0; i < 1000; i++) {
    document.getElementById('list').innerHTML += `<li>Item ${i}</li>`;
}

// ✅ Batch DOM operations
let html = '';
for (let i = 0; i < 1000; i++) {
    html += `<li>Item ${i}</li>`;
}
document.getElementById('list').innerHTML = html;

// ✅ Oppure usa DocumentFragment
const fragment = document.createDocumentFragment();
for (let i = 0; i < 1000; i++) {
    const li = document.createElement('li');
    li.textContent = `Item ${i}`;
    fragment.appendChild(li);
}
document.getElementById('list').appendChild(fragment);
```

### 3. Event Handling Optimization
```javascript
// ❌ Event listener su ogni elemento
document.querySelectorAll('.button').forEach(btn => {
    btn.addEventListener('click', handleClick);
});

// ✅ Event delegation
document.addEventListener('click', (e) => {
    if (e.target.classList.contains('button')) {
        handleClick(e);
    }
});
```

## Profiling e Monitoring

### 1. Performance Measurement
```javascript
// Misurare performance del codice
function measurePerformance(func, ...args) {
    const start = performance.now();
    const result = func(...args);
    const end = performance.now();
    console.log(`Execution time: ${end - start} milliseconds`);
    return result;
}

// Esempio d'uso
measurePerformance(sortArray, largeArray);
```

### 2. Memory Usage Monitoring
```javascript
// Monitorare uso memoria
function checkMemoryUsage() {
    if (performance.memory) {
        console.log({
            used: Math.round(performance.memory.usedJSHeapSize / 1048576),
            allocated: Math.round(performance.memory.totalJSHeapSize / 1048576),
            limit: Math.round(performance.memory.jsHeapSizeLimit / 1048576)
        });
    }
}
```

## Web Performance

### 1. Resource Loading
```html
<!-- Preload critical resources -->
<link rel="preload" href="critical.css" as="style">
<link rel="preload" href="hero-image.jpg" as="image">

<!-- Lazy loading per immagini -->
<img src="placeholder.jpg" data-src="actual-image.jpg" loading="lazy">
```

### 2. Code Splitting
```javascript
// Dynamic imports per code splitting
async function loadModule() {
    const { heavyFunction } = await import('./heavy-module.js');
    return heavyFunction();
}

// Conditional loading
if (user.isAdmin) {
    const adminPanel = await import('./admin-panel.js');
    adminPanel.init();
}
```

### 3. Caching Strategies
```javascript
// Service Worker per caching
self.addEventListener('fetch', (event) => {
    if (event.request.url.includes('/api/')) {
        // Cache API responses con TTL
        event.respondWith(
            caches.open('api-cache').then(cache => {
                return cache.match(event.request).then(response => {
                    if (response) {
                        // Check se cache è ancora valida
                        const cacheTime = response.headers.get('sw-cache-time');
                        if (Date.now() - cacheTime < 300000) { // 5 minuti
                            return response;
                        }
                    }
                    // Fetch fresh data
                    return fetch(event.request).then(fetchResponse => {
                        const responseClone = fetchResponse.clone();
                        responseClone.headers.set('sw-cache-time', Date.now());
                        cache.put(event.request, responseClone);
                        return fetchResponse;
                    });
                });
            })
        );
    }
});
```

## Database Performance

### 1. Query Optimization
```sql
-- ❌ Query inefficiente
SELECT * FROM users WHERE UPPER(email) = 'USER@EXAMPLE.COM';

-- ✅ Query ottimizzata con indice
CREATE INDEX idx_users_email ON users(email);
SELECT * FROM users WHERE email = 'user@example.com';
```

### 2. Connection Pooling
```javascript
// Connection pooling con Node.js
const mysql = require('mysql2');

const pool = mysql.createPool({
    host: 'localhost',
    user: 'username',
    password: 'password',
    database: 'mydb',
    connectionLimit: 10,
    queueLimit: 0
});

// Uso del pool
function getUser(id) {
    return new Promise((resolve, reject) => {
        pool.execute(
            'SELECT * FROM users WHERE id = ?',
            [id],
            (err, results) => {
                if (err) reject(err);
                else resolve(results[0]);
            }
        );
    });
}
```

## Performance Testing

### 1. Load Testing con Artillery
```yaml
# artillery-config.yml
config:
  target: 'http://localhost:3000'
  phases:
    - duration: 60
      arrivalRate: 10
scenarios:
  - name: "API Load Test"
    requests:
      - get:
          url: "/api/users"
      - post:
          url: "/api/users"
          json:
            name: "Test User"
            email: "test@example.com"
```

### 2. Browser Performance Testing
```javascript
// Lighthouse programmatically
const lighthouse = require('lighthouse');
const chromeLauncher = require('chrome-launcher');

async function runLighthouse(url) {
    const chrome = await chromeLauncher.launch({chromeFlags: ['--headless']});
    const options = {logLevel: 'info', output: 'html', onlyCategories: ['performance']};
    const runnerResult = await lighthouse(url, options);
    
    await chrome.kill();
    
    // Analizza risultati
    const score = runnerResult.lhr.categories.performance.score * 100;
    console.log(`Performance Score: ${score}`);
    
    return runnerResult;
}
```

## Performance Checklist

### Frontend
- [ ] Minify e compress CSS/JS
- [ ] Optimize immagini (WebP, lazy loading)
- [ ] Usa CDN per static assets
- [ ] Implementa caching headers
- [ ] Code splitting per bundles grandi
- [ ] Tree shaking per eliminare dead code
- [ ] Service Worker per offline support

### Backend
- [ ] Database indexing ottimale
- [ ] Connection pooling
- [ ] Caching (Redis/Memcached)
- [ ] Response compression (gzip)
- [ ] Rate limiting
- [ ] Background job processing
- [ ] Monitoring e alerting

### Monitoring Tools
- **Browser**: Chrome DevTools, Lighthouse
- **Application**: New Relic, DataDog
- **Infrastructure**: Prometheus, Grafana
- **Synthetic**: Pingdom, UptimeRobot

## Performance Budget

```javascript
// Definire budget performance
const performanceBudget = {
    'bundle.js': { maxSize: '250KB' },
    'styles.css': { maxSize: '50KB' },
    'images': { maxSize: '500KB' },
    'total': { maxSize: '1MB' },
    'metrics': {
        'First Contentful Paint': '2s',
        'Largest Contentful Paint': '4s',
        'Time to Interactive': '5s'
    }
};

// Webpack performance budget
module.exports = {
    performance: {
        maxAssetSize: 250000,
        maxEntrypointSize: 250000,
        hints: 'error'
    }
};
```

Questo documento fornisce le basi per ottimizzare le performance del progetto finale, dal codice JavaScript alle query database, fino al monitoring in produzione.
