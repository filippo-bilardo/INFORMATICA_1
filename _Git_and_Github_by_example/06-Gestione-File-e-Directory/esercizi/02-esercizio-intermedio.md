# Esercizio 2: Riorganizzazione Avanzata dei File

## 🎯 Obiettivo
Praticare la riorganizzazione di un progetto esistente utilizzando `git mv` e gestendo conflitti comuni.

## 📋 Prerequisiti
- Completamento dell'Esercizio 1
- Conoscenza dei comandi `git mv`, `git add`, `git rm`

## 🔧 Scenario
Il tuo progetto web è cresciuto e hai bisogno di riorganizzare la struttura per renderla più professionale e mantenibile.

## 📝 Istruzioni

### Passo 1: Preparazione del Progetto
Parti dal risultato dell'Esercizio 1 o crea una struttura simile:

```bash
mkdir esercizio-riorganizzazione
cd esercizio-riorganizzazione
git init
git config user.name "Il Tuo Nome"
git config user.email "tuo.email@example.com"

# Crea i file di partenza
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Portfolio</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Il Mio Portfolio</h1>
    <p>Benvenuto nel mio sito personale</p>
    <script src="script.js"></script>
</body>
</html>
EOF

cat > style.css << 'EOF'
body { font-family: Arial, sans-serif; margin: 0; padding: 20px; }
h1 { color: #333; text-align: center; }
EOF

cat > script.js << 'EOF'
console.log('Portfolio caricato');
EOF

git add .
git commit -m "Setup iniziale del portfolio"
```

### Passo 2: Creazione della Nuova Struttura
Organizza il progetto secondo questa struttura:
```
portfolio/
├── assets/
│   ├── css/
│   ├── js/
│   └── images/
├── pages/
└── index.html
```

1. Crea le directory:
```bash
mkdir -p assets/css assets/js assets/images pages
```

2. Sposta i file CSS:
```bash
git mv style.css assets/css/main.css
```

3. Sposta i file JavaScript:
```bash
git mv script.js assets/js/portfolio.js
```

### Passo 3: Aggiornamento dei Collegamenti
1. Modifica `index.html` per aggiornare i percorsi:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Portfolio Professionale</title>
    <link rel="stylesheet" href="assets/css/main.css">
</head>
<body>
    <header>
        <h1>Il Mio Portfolio</h1>
        <nav>
            <a href="pages/about.html">Chi Sono</a>
            <a href="pages/projects.html">Progetti</a>
            <a href="pages/contact.html">Contatti</a>
        </nav>
    </header>
    <main>
        <p>Benvenuto nel mio sito personale rinnovato!</p>
    </main>
    <script src="assets/js/portfolio.js"></script>
</body>
</html>
```

### Passo 4: Creazione delle Pagine Secondarie
1. Crea `pages/about.html`:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Chi Sono - Portfolio</title>
    <link rel="stylesheet" href="../assets/css/main.css">
</head>
<body>
    <h1>Chi Sono</h1>
    <p>Sono uno sviluppatore appassionato di tecnologie web.</p>
    <a href="../index.html">← Torna alla Home</a>
</body>
</html>
```

2. Crea `pages/projects.html`:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Progetti - Portfolio</title>
    <link rel="stylesheet" href="../assets/css/main.css">
</head>
<body>
    <h1>I Miei Progetti</h1>
    <ul>
        <li>Progetto 1: Sito Web Responsive</li>
        <li>Progetto 2: App Mobile</li>
        <li>Progetto 3: Sistema di Gestione</li>
    </ul>
    <a href="../index.html">← Torna alla Home</a>
</body>
</html>
```

3. Crea `pages/contact.html`:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Contatti - Portfolio</title>
    <link rel="stylesheet" href="../assets/css/main.css">
</head>
<body>
    <h1>Contatti</h1>
    <p>Email: portfolio@example.com</p>
    <p>LinkedIn: linkedin.com/in/mio-profilo</p>
    <a href="../index.html">← Torna alla Home</a>
</body>
</html>
```

### Passo 5: Miglioramento degli Stili
Aggiorna `assets/css/main.css`:
```css
/* Reset e base */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    line-height: 1.6;
    color: #333;
    background-color: #f8f9fa;
}

/* Header */
header {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 2rem;
    text-align: center;
}

header h1 {
    margin-bottom: 1rem;
    font-size: 2.5rem;
}

nav a {
    color: white;
    text-decoration: none;
    margin: 0 1rem;
    padding: 0.5rem 1rem;
    border-radius: 5px;
    transition: background-color 0.3s;
}

nav a:hover {
    background-color: rgba(255, 255, 255, 0.2);
}

/* Main content */
main {
    max-width: 800px;
    margin: 2rem auto;
    padding: 0 1rem;
}

main p {
    font-size: 1.1rem;
    margin-bottom: 1rem;
}

/* Lists */
ul {
    margin-left: 2rem;
}

li {
    margin-bottom: 0.5rem;
}

/* Links */
a {
    color: #667eea;
    text-decoration: none;
}

a:hover {
    text-decoration: underline;
}
```

### Passo 6: Aggiornamento JavaScript
Modifica `assets/js/portfolio.js`:
```javascript
// Portfolio JavaScript
document.addEventListener('DOMContentLoaded', function() {
    console.log('Portfolio caricato con successo!');
    
    // Aggiungi animazione al caricamento
    const header = document.querySelector('header');
    if (header) {
        header.style.opacity = '0';
        header.style.transform = 'translateY(-20px)';
        
        setTimeout(() => {
            header.style.transition = 'opacity 0.5s, transform 0.5s';
            header.style.opacity = '1';
            header.style.transform = 'translateY(0)';
        }, 100);
    }
    
    // Evidenzia link attivo
    const currentPage = window.location.pathname.split('/').pop();
    const navLinks = document.querySelectorAll('nav a');
    
    navLinks.forEach(link => {
        const linkPage = link.getAttribute('href').split('/').pop();
        if (linkPage === currentPage) {
            link.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
        }
    });
});
```

### Passo 7: Gestione delle Immagini
1. Crea un file placeholder per le immagini:
```bash
echo "# Cartella per le immagini del portfolio" > assets/images/.gitkeep
```

2. Aggiungi tutti i nuovi file:
```bash
git add .
```

### Passo 8: Commit Finale
```bash
git commit -m "Riorganizzazione completa del portfolio

- Spostati CSS e JS in cartelle assets/
- Create pagine secondarie (about, projects, contact)
- Migliorati stili con design responsive
- Aggiunta interattività JavaScript
- Struttura più professionale e mantenibile"
```

## 🔍 Esercizio Bonus: Gestione Errori
Simula alcuni errori comuni e risolvili:

### Errore 1: Spostamento Sbagliato
```bash
# Sposta accidentalmente un file
mv pages/about.html pages/chi-sono.html

# Ripristina usando Git
git checkout pages/about.html
rm pages/chi-sono.html
```

### Errore 2: Conflitto di Rinominazione
```bash
# Prova a rinominare un file modificato
echo "Modifica" >> assets/css/main.css
git mv assets/css/main.css assets/css/styles.css
# Git ti avviserà del conflitto

# Risolvi committando prima la modifica
git add assets/css/main.css
git commit -m "Aggiornamento stili"
git mv assets/css/main.css assets/css/styles.css
git commit -m "Rinominato file CSS"
```

## ✅ Verifiche
Controlla che:
- [ ] La struttura directory sia organizzata correttamente
- [ ] Tutti i collegamenti tra file funzionino
- [ ] Il sito sia navigabile attraverso tutte le pagine
- [ ] Git tracking mostri la cronologia completa
- [ ] `git status` mostri "working tree clean"

## 🧪 Test di Verifica
```bash
# Verifica la struttura
tree . # o ls -la per visualizzare la struttura

# Testa i collegamenti
# Apri index.html in un browser e naviga tra le pagine

# Verifica Git
git log --oneline --name-status
git status
```

## 🤔 Domande di Riflessione
1. Perché è importante usare `git mv` invece di `mv` normale?
2. Come gestisci i riferimenti ai file dopo averli spostati?
3. Quali sono i vantaggi di una struttura directory organizzata?

## 🎯 Risultato Atteso
```
portfolio/
├── assets/
│   ├── css/
│   │   └── main.css
│   ├── js/
│   │   └── portfolio.js
│   └── images/
│       └── .gitkeep
├── pages/
│   ├── about.html
│   ├── projects.html
│   └── contact.html
└── index.html
```

Con un sito web funzionante e navigabile, e una cronologia Git pulita che documenta la riorganizzazione.

---
[← Esercizio Precedente](./01-esercizio-base.md) | [Torna alla Panoramica](../README.md) | [Esercizio Successivo →](./03-esercizio-avanzato.md)
