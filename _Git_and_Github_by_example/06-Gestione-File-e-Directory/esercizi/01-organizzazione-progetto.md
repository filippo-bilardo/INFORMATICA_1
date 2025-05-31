# Esercizio 1: Organizzazione Progetto Web

## 🎯 Obiettivo
Organizzare un progetto web disordinato utilizzando i comandi Git per gestione file, mantenendo la storia delle modifiche.

## 📋 Scenario
Hai ereditato un progetto web disorganizzato dove i file sono sparsi senza una struttura logica. Il tuo compito è riorganizzarlo seguendo le best practices moderne.

## 🚀 Setup Iniziale

```bash
# Creare directory di lavoro
mkdir organizzazione-progetto-web
cd organizzazione-progetto-web
git init

# Creare i file disorganizzati del progetto
touch {
  index.html,
  about.html,
  contact.html,
  main.css,
  responsive.css,
  app.js,
  utils.js,
  jquery.min.js,
  bootstrap.css,
  logo.png,
  hero-image.jpg,
  favicon.ico
}

# Aggiungere contenuto ai file principali
cat > index.html << 'EOL'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Sito Web</title>
    <link rel="stylesheet" href="bootstrap.css">
    <link rel="stylesheet" href="main.css">
    <link rel="stylesheet" href="responsive.css">
    <link rel="icon" href="favicon.ico">
</head>
<body>
    <header>
        <img src="logo.png" alt="Logo">
        <nav>
            <a href="index.html">Home</a>
            <a href="about.html">Chi Siamo</a>
            <a href="contact.html">Contatti</a>
        </nav>
    </header>
    
    <main>
        <section class="hero">
            <img src="hero-image.jpg" alt="Hero Image">
            <h1>Benvenuto nel nostro sito</h1>
        </section>
    </main>
    
    <script src="jquery.min.js"></script>
    <script src="app.js"></script>
    <script src="utils.js"></script>
</body>
</html>
EOL

cat > main.css << 'EOL'
/* Stili principali */
body {
    font-family: 'Arial', sans-serif;
    margin: 0;
    padding: 0;
    line-height: 1.6;
}

header {
    background: #333;
    color: white;
    padding: 1rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

header img {
    height: 40px;
}

nav a {
    color: white;
    text-decoration: none;
    margin: 0 1rem;
}

.hero {
    text-align: center;
    padding: 2rem;
}

.hero img {
    max-width: 100%;
    height: auto;
}
EOL

cat > app.js << 'EOL'
// Applicazione principale
document.addEventListener('DOMContentLoaded', function() {
    console.log('App inizializzata');
    
    // Gestione navigazione
    const navLinks = document.querySelectorAll('nav a');
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            console.log('Navigazione a:', this.href);
        });
    });
    
    // Caricamento dinamico contenuti
    loadDynamicContent();
});

function loadDynamicContent() {
    // Simulazione caricamento dati
    fetch('/api/content')
        .then(response => response.json())
        .then(data => {
            console.log('Contenuto caricato:', data);
        })
        .catch(error => {
            console.error('Errore caricamento:', error);
        });
}
EOL

# Committare stato iniziale disorganizzato
git add .
git commit -m "Initial commit - unorganized project structure"
```

## ✅ Task 1: Analisi Stato Iniziale

### Istruzioni:
1. Analizza la struttura attuale del progetto
2. Identifica i problemi di organizzazione
3. Pianifica la nuova struttura

### Comandi da eseguire:
```bash
# Vedere tutti i file tracciati
git ls-files

# Analizzare tipi di file
git ls-files | grep -E '\.(html|css|js|png|jpg|ico)$' | \
  awk -F. '{print $NF}' | sort | uniq -c

# Verificare dimensioni file
ls -lah
```

### Domande di riflessione:
- Quali tipi di file ci sono nel progetto?
- Come dovrebbero essere organizzati logicamente?
- Quali problemi vedi nella struttura attuale?

## ✅ Task 2: Creazione Struttura Directory

### Obiettivo:
Creare una struttura di directory logica per un progetto web moderno.

### Struttura target:
```
project/
├── index.html
├── pages/
│   ├── about.html
│   └── contact.html
├── assets/
│   ├── css/
│   │   ├── main.css
│   │   ├── responsive.css
│   │   └── vendor/
│   │       └── bootstrap.css
│   ├── js/
│   │   ├── app.js
│   │   ├── utils.js
│   │   └── vendor/
│   │       └── jquery.min.js
│   └── images/
│       ├── logo.png
│       ├── hero-image.jpg
│       └── favicon.ico
└── docs/
    └── README.md
```

### Istruzioni:
```bash
# 1. Creare la struttura di directory
mkdir -p {pages,assets/{css/vendor,js/vendor,images},docs}

# 2. Aggiungere .gitkeep per preservare directory vuote
touch pages/.gitkeep assets/css/vendor/.gitkeep assets/js/vendor/.gitkeep
git add **/.gitkeep

# 3. Verificare struttura creata
find . -type d | sort
```

### Verifica:
- [ ] Directory `pages/` creata
- [ ] Directory `assets/` con sottocartelle create
- [ ] Directory `docs/` creata
- [ ] File `.gitkeep` aggiunti dove necessario

## ✅ Task 3: Spostamento File HTML

### Obiettivo:
Spostare le pagine secondarie nella directory `pages/` mantenendo `index.html` nella root.

### Istruzioni:
```bash
# Spostare pagine secondarie
git mv about.html pages/
git mv contact.html pages/

# Verificare spostamenti
git status

# Committare spostamenti
git commit -m "Organize HTML pages

- Move secondary pages to pages/ directory
- Keep index.html in root as main entry point
- Maintain clean project root"
```

### Aggiornamento riferimenti:
Modifica `index.html` per aggiornare i link:
```html
<!-- Cambiare da: -->
<a href="about.html">Chi Siamo</a>
<a href="contact.html">Contatti</a>

<!-- A: -->
<a href="pages/about.html">Chi Siamo</a>
<a href="pages/contact.html">Contatti</a>
```

### Verifica:
- [ ] `about.html` e `contact.html` spostati in `pages/`
- [ ] Link in `index.html` aggiornati
- [ ] Test: aprire `index.html` nel browser per verificare i link

## ✅ Task 4: Organizzazione Asset CSS

### Obiettivo:
Organizzare i file CSS distinguendo tra codice proprio e librerie esterne.

### Istruzioni:
```bash
# Spostare CSS personalizzati
git mv main.css assets/css/
git mv responsive.css assets/css/

# Spostare CSS di librerie esterne
git mv bootstrap.css assets/css/vendor/

# Verificare spostamenti
git status

# Committare organizzazione CSS
git commit -m "Organize CSS files

- Move custom CSS to assets/css/
- Move vendor CSS to assets/css/vendor/
- Separate custom code from external libraries"
```

### Aggiornamento riferimenti in `index.html`:
```html
<!-- Aggiornare i link CSS -->
<link rel="stylesheet" href="assets/css/vendor/bootstrap.css">
<link rel="stylesheet" href="assets/css/main.css">
<link rel="stylesheet" href="assets/css/responsive.css">
```

### Verifica:
- [ ] CSS personalizzati in `assets/css/`
- [ ] CSS vendor in `assets/css/vendor/`
- [ ] Link aggiornati in `index.html`

## ✅ Task 5: Organizzazione Asset JavaScript

### Obiettivo:
Organizzare i file JavaScript seguendo la stessa logica dei CSS.

### Istruzioni:
```bash
# Spostare JavaScript personalizzati
git mv app.js assets/js/
git mv utils.js assets/js/

# Spostare librerie JavaScript
git mv jquery.min.js assets/js/vendor/

# Verificare spostamenti
git status

# Committare organizzazione JavaScript
git commit -m "Organize JavaScript files

- Move custom JS to assets/js/
- Move vendor JS to assets/js/vendor/
- Maintain consistent asset organization"
```

### Aggiornamento riferimenti in `index.html`:
```html
<!-- Aggiornare i link JavaScript -->
<script src="assets/js/vendor/jquery.min.js"></script>
<script src="assets/js/app.js"></script>
<script src="assets/js/utils.js"></script>
```

### Verifica:
- [ ] JavaScript personalizzati in `assets/js/`
- [ ] JavaScript vendor in `assets/js/vendor/`
- [ ] Script tag aggiornati in `index.html`

## ✅ Task 6: Organizzazione Immagini

### Obiettivo:
Spostare tutte le immagini e icone nella directory `assets/images/`.

### Istruzioni:
```bash
# Spostare immagini
git mv logo.png assets/images/
git mv hero-image.jpg assets/images/
git mv favicon.ico assets/images/

# Verificare spostamenti
git status

# Committare organizzazione immagini
git commit -m "Organize image assets

- Move all images to assets/images/
- Centralize media files
- Complete asset organization"
```

### Aggiornamento riferimenti in `index.html`:
```html
<!-- Aggiornare percorsi immagini -->
<link rel="icon" href="assets/images/favicon.ico">

<!-- Nel body -->
<img src="assets/images/logo.png" alt="Logo">
<img src="assets/images/hero-image.jpg" alt="Hero Image">
```

### Verifica:
- [ ] Tutte le immagini in `assets/images/`
- [ ] Percorsi aggiornati in `index.html`
- [ ] Favicon funzionante

## ✅ Task 7: Aggiunta Documentazione

### Obiettivo:
Creare documentazione per il progetto riorganizzato.

### Istruzioni:
```bash
# Creare documentazione principale
cat > docs/README.md << 'EOL'
# Progetto Web Organizzato

## Struttura del Progetto

```
project/
├── index.html              # Pagina principale
├── pages/                  # Pagine secondarie
│   ├── about.html         # Pagina chi siamo
│   └── contact.html       # Pagina contatti
├── assets/                # Risorse statiche
│   ├── css/               # Fogli di stile
│   │   ├── main.css       # Stili principali
│   │   ├── responsive.css # Stili responsive
│   │   └── vendor/        # CSS di librerie esterne
│   ├── js/                # File JavaScript
│   │   ├── app.js         # Applicazione principale
│   │   ├── utils.js       # Utilità
│   │   └── vendor/        # JS di librerie esterne
│   └── images/            # Immagini e icone
└── docs/                  # Documentazione
```

## Come Utilizzare

1. Aprire `index.html` nel browser
2. Navigare tra le pagine usando il menu
3. Tutti gli asset sono organizzati logicamente

## Sviluppo

- CSS personalizzati: `assets/css/`
- JavaScript personalizzati: `assets/js/`
- Librerie esterne: `assets/*/vendor/`
- Immagini: `assets/images/`

## Best Practices Implementate

- Separazione di codice personalizzato da librerie
- Struttura scalabile e mantenibile
- Asset organizzati per tipo
- Documentazione chiara
EOL

# Aggiungere documentazione tecnica
cat > docs/development.md << 'EOL'
# Guida allo Sviluppo

## Struttura Asset

### CSS
- `main.css`: Stili base dell'applicazione
- `responsive.css`: Media queries e layout responsive
- `vendor/`: Librerie CSS esterne (Bootstrap, etc.)

### JavaScript
- `app.js`: Logica principale dell'applicazione
- `utils.js`: Funzioni di utilità riutilizzabili
- `vendor/`: Librerie JS esterne (jQuery, etc.)

### Immagini
- Logo e branding
- Immagini di contenuto
- Icone e favicon

## Convenzioni

1. **Naming**: Usa kebab-case per file e directory
2. **Organizzazione**: Separa codice personalizzato da vendor
3. **Percorsi**: Usa percorsi relativi consistenti
4. **Documentazione**: Mantieni docs/ aggiornato

## Workflow Git

1. Usa `git mv` per spostare file
2. Mantieni commit atomici e descrittivi
3. Aggiorna riferimenti dopo spostamenti
4. Testa sempre dopo riorganizzazioni
EOL

# Aggiungere documentazione al repository
git add docs/
git commit -m "Add project documentation

- Add comprehensive README.md
- Add development guidelines
- Document project structure and conventions
- Provide clear usage instructions"
```

### Verifica:
- [ ] `docs/README.md` creato con struttura progetto
- [ ] `docs/development.md` creato con linee guida
- [ ] Documentazione committata

## ✅ Task 8: Test e Verifica Finale

### Obiettivo:
Verificare che il progetto riorganizzato funzioni correttamente.

### Istruzioni di test:
```bash
# 1. Verificare struttura finale
echo "=== Struttura Finale ==="
tree . 2>/dev/null || find . -type f -not -path './.*' | sort

# 2. Verificare tutti i file sono tracciati
echo "=== File Tracciati ==="
git ls-files | sort

# 3. Verificare la storia è preservata
echo "=== Storia Modifiche ==="
git log --oneline --stat

# 4. Test funzionalità
echo "=== Test Funzionalità ==="
echo "Aprire index.html nel browser e verificare:"
echo "- ✓ Pagina si carica correttamente"
echo "- ✓ CSS applicati correttamente"  
echo "- ✓ JavaScript funzionante"
echo "- ✓ Immagini visibili"
echo "- ✓ Link di navigazione funzionanti"
echo "- ✓ Favicon visibile"

# 5. Creare tag per milestone
git tag v1.0-organized
echo "✓ Tag v1.0-organized creato"
```

### Checklist finale:
- [ ] Struttura directory logica e consistente
- [ ] Tutti i file spostati correttamente con `git mv`
- [ ] Tutti i riferimenti nei file aggiornati
- [ ] Sito web funzionante dopo riorganizzazione
- [ ] Documentazione completa
- [ ] Storia Git preservata
- [ ] Commit descrittivi e atomici

## 🎯 Risultato Atteso

Al termine dell'esercizio avrai:

1. **Struttura Organizzata**: Progetto web con struttura logica e scalabile
2. **Asset Separati**: Codice personalizzato separato da librerie esterne
3. **Documentazione**: README e guide per sviluppatori
4. **Storia Preservata**: Tutte le modifiche tracciate correttamente in Git
5. **Funzionalità Intatta**: Sito web completamente funzionante

## 💡 Bonus Challenge

Se vuoi andare oltre:

### Challenge 1: Automazione
Crea uno script che automatizzi l'organizzazione:
```bash
# Creare organize-project.sh
cat > organize-project.sh << 'EOL'
#!/bin/bash
# Script per organizzare progetto web

echo "🚀 Organizing web project..."

# Creare struttura
mkdir -p {pages,assets/{css/vendor,js/vendor,images},docs}

# Spostare file per tipo
git mv *.html pages/ 2>/dev/null || true
git mv index.html . 2>/dev/null || true  # Index rimane in root
git mv *.css assets/css/ 2>/dev/null || true
git mv *.js assets/js/ 2>/dev/null || true
git mv *.{png,jpg,jpeg,gif,ico} assets/images/ 2>/dev/null || true

echo "✅ Project organized!"
EOL

chmod +x organize-project.sh
```

### Challenge 2: Configuration
Aggiungi file di configurazione del progetto:
- `package.json` per dependencies
- `.editorconfig` per editor settings
- `.gitignore` migliorato

### Challenge 3: Build Process
Implementa un processo di build:
- Minificazione CSS/JS
- Ottimizzazione immagini
- Build directory automatica

## 📚 Cosa Hai Imparato

1. **Gestione File Git**: Come usare `git mv` per preservare storia
2. **Organizzazione Progetti**: Strutture standard per progetti web
3. **Asset Management**: Separazione codice personalizzato da vendor
4. **Documentazione**: Importanza di documentare struttura e convenzioni
5. **Testing**: Verificare funzionalità dopo riorganizzazione
6. **Best Practices**: Commit atomici e descrittivi

Ottimo lavoro! Hai completato la riorganizzazione di un progetto web mantenendo la storia Git e migliorando drasticamente la manutenibilità del codice.
