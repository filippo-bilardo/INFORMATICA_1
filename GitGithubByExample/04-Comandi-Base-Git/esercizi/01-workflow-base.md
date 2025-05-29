# Esercizio 01: Workflow Base Git

## 🎯 Obiettivi
- Applicare il workflow base di Git in un progetto pratico
- Praticare i comandi `git add`, `git commit`, `git status`
- Comprendere il ciclo di vita dei file in Git
- Sviluppare buone abitudini per la gestione del repository

## 📋 Prerequisiti
- Git installato e configurato
- Conoscenza base dei comandi Git
- Editor di testo a scelta

## 🚀 Scenario
Sei uno sviluppatore junior che deve creare e gestire un semplice sito web personale utilizzando Git per il controllo versione. Il progetto includerà file HTML, CSS e JavaScript.

## 📝 Istruzioni Passo-Passo

### Fase 1: Inizializzazione del Progetto

1. **Crea una nuova directory per il progetto**
```bash
mkdir mio-sito-web
cd mio-sito-web
```

2. **Inizializza un repository Git**
```bash
git init
```

3. **Verifica lo stato del repository**
```bash
git status
```

### Fase 2: Creazione della Struttura Base

4. **Crea la struttura delle directory**
```bash
mkdir css js img
```

5. **Crea il file HTML principale**
```html
<!-- index.html -->
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Sito Web</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <header>
        <h1>Benvenuto nel Mio Sito</h1>
        <nav>
            <ul>
                <li><a href="#home">Home</a></li>
                <li><a href="#about">Chi Sono</a></li>
                <li><a href="#contact">Contatti</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <section id="home">
            <h2>Home</h2>
            <p>Questo è il mio primo sito web gestito con Git!</p>
        </section>
    </main>
    
    <footer>
        <p>&copy; 2024 Il Mio Sito Web</p>
    </footer>
    
    <script src="js/script.js"></script>
</body>
</html>
```

6. **Verifica lo stato e aggiungi il file**
```bash
git status
git add index.html
git status
```

7. **Fai il primo commit**
```bash
git commit -m "feat: aggiungi struttura HTML base del sito web

- Crea layout base con header, main e footer
- Implementa navigazione semplice
- Aggiungi riferimenti a CSS e JavaScript"
```

### Fase 3: Sviluppo Incrementale

8. **Crea il file CSS**
```css
/* css/style.css */
/* Reset base */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: Arial, sans-serif;
    line-height: 1.6;
    color: #333;
}

header {
    background-color: #4CAF50;
    color: white;
    padding: 1rem;
}

header h1 {
    text-align: center;
    margin-bottom: 1rem;
}

nav ul {
    list-style: none;
    display: flex;
    justify-content: center;
    gap: 2rem;
}

nav a {
    color: white;
    text-decoration: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    transition: background-color 0.3s;
}

nav a:hover {
    background-color: rgba(255, 255, 255, 0.2);
}

main {
    padding: 2rem;
    min-height: 70vh;
}

footer {
    background-color: #333;
    color: white;
    text-align: center;
    padding: 1rem;
}
```

9. **Aggiungi e committa il CSS**
```bash
git add css/style.css
git commit -m "style: aggiungi stili CSS base

- Implementa reset CSS
- Definisce stili per header, nav e footer
- Aggiunge effetti hover per la navigazione
- Utilizza design responsive"
```

### Fase 4: Aggiunta della Logica JavaScript

10. **Crea il file JavaScript**
```javascript
// js/script.js
document.addEventListener('DOMContentLoaded', function() {
    console.log('Sito web caricato con successo!');
    
    // Gestione navigazione smooth scroll
    const links = document.querySelectorAll('nav a[href^="#"]');
    
    links.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            const targetSection = document.querySelector(targetId);
            
            if (targetSection) {
                targetSection.scrollIntoView({
                    behavior: 'smooth'
                });
            }
        });
    });
    
    // Aggiunge data/ora di ultima visita
    const now = new Date().toLocaleString('it-IT');
    const footer = document.querySelector('footer p');
    footer.innerHTML += ` - Ultima visita: ${now}`;
});
```

11. **Verifica le modifiche e committa**
```bash
git status
git add js/script.js
git commit -m "feat: aggiungi funzionalità JavaScript

- Implementa smooth scroll per la navigazione
- Aggiunge timestamp di ultima visita
- Migliora UX con eventi interattivi"
```

### Fase 5: Aggiornamenti e Modifiche

12. **Modifica il file HTML aggiungendo contenuto**
Aggiungi le sezioni mancanti:
```html
<!-- Aggiungi dopo la sezione home, prima del </main> -->
<section id="about">
    <h2>Chi Sono</h2>
    <p>Sono uno sviluppatore in formazione che sta imparando Git e GitHub.</p>
    <ul>
        <li>🎓 Studente di Informatica</li>
        <li>💻 Appassionato di programmazione</li>
        <li>🚀 Sempre pronto a imparare nuove tecnologie</li>
    </ul>
</section>

<section id="contact">
    <h2>Contatti</h2>
    <p>Puoi contattarmi attraverso:</p>
    <ul>
        <li>📧 Email: esempio@email.com</li>
        <li>🐙 GitHub: @username</li>
        <li>💼 LinkedIn: /in/username</li>
    </ul>
</section>
```

13. **Visualizza le differenze**
```bash
git diff
```

14. **Aggiungi le modifiche e committa**
```bash
git add index.html
git commit -m "content: aggiungi sezioni About e Contact

- Completa la struttura della pagina
- Aggiunge informazioni personali
- Implementa sezione contatti con emoji"
```

### Fase 6: Gestione File e Pulizia

15. **Crea un file di configurazione**
```bash
echo "# Configurazione del sito
SITE_NAME=Il Mio Sito Web
VERSION=1.0.0
AUTHOR=Il Tuo Nome" > config.txt
```

16. **Aggiungi il file di configurazione**
```bash
git add config.txt
git commit -m "config: aggiungi file di configurazione del sito"
```

17. **Crea un file .gitignore**
```bash
echo "# File temporanei
*.tmp
*.log
.DS_Store
Thumbs.db

# Directory di build
build/
dist/

# File di configurazione locale
config.local.txt" > .gitignore
```

18. **Committa il .gitignore**
```bash
git add .gitignore
git commit -m "config: aggiungi .gitignore per file temporanei"
```

### Fase 7: Revisione e Verifica

19. **Visualizza la cronologia completa**
```bash
git log --oneline
git log --graph --pretty=format:"%h %s %cr %an"
```

20. **Controlla lo stato finale**
```bash
git status
```

21. **Verifica la struttura del progetto**
```bash
find . -type f -not -path "./.git/*" | sort
```

## 🎯 Obiettivi di Completamento

Al termine dell'esercizio dovresti aver:

- [ ] Creato un repository Git funzionante
- [ ] Effettuato almeno 6 commit con messaggi descrittivi
- [ ] Utilizzato `git add` per staging selettivo
- [ ] Applicato convenzioni per i messaggi di commit
- [ ] Creato una struttura progetto organizzata
- [ ] Implementato un sito web funzionante

## 📋 Checklist Finale

### Verifica Tecnica
- [ ] Il repository contiene almeno 6 commit
- [ ] Ogni commit ha un messaggio descrittivo
- [ ] Il file .gitignore è presente e configurato
- [ ] La struttura del progetto è organizzata

### Verifica Funzionale
- [ ] Il sito web si apre correttamente nel browser
- [ ] La navigazione funziona con smooth scroll
- [ ] Gli stili CSS sono applicati correttamente
- [ ] Il JavaScript esegue senza errori

### Verifica Best Practices
- [ ] I messaggi di commit seguono le convenzioni
- [ ] I file sono organizzati in directory logiche
- [ ] Il codice è ben formattato e leggibile
- [ ] Non ci sono file temporanei nel repository

## 🔧 Comandi di Verifica

```bash
# Verifica numero di commit
git rev-list --count HEAD

# Verifica struttura del progetto
tree -a -I '.git'

# Verifica ultimo commit
git show --stat

# Verifica file tracciati
git ls-files
```

## 💡 Suggerimenti per l'Approfondimento

1. **Sperimenta con git add**:
   - Prova `git add -p` per staging interattivo
   - Usa `git add .` vs `git add -A`

2. **Migliora i messaggi di commit**:
   - Implementa conventional commits
   - Aggiungi corpo ai messaggi per commit complessi

3. **Esplora git log**:
   - Prova diverse opzioni di formattazione
   - Filtra i commit per data o autore

## 🎖️ Sfide Bonus

### Sfida 1: Hotfix
Simula un bug critico e crea un hotfix:
1. Modifica il CSS introducendo un errore
2. Committa l'errore
3. Correggi immediatamente con un nuovo commit
4. Usa un messaggio di commit appropriato per il fix

### Sfida 2: Feature Branch Simulation
Anche se non hai ancora imparato i branch:
1. Pianifica una nuova feature (es. form di contatto)
2. Implementala in più commit piccoli
3. Documenta ogni step nel messaggio di commit

### Sfida 3: Refactoring
1. Migliora il codice esistente senza cambiare la funzionalità
2. Committa ogni refactoring separatamente
3. Usa messaggi di commit che spieghino il miglioramento

## 📚 Risorse Utili

- [Conventional Commits](https://www.conventionalcommits.org/)
- [Git Best Practices](https://git-scm.com/book)
- [Semantic Versioning](https://semver.org/)

## 🏆 Criteri di Valutazione

| Criterio | Punti | Descrizione |
|----------|-------|-------------|
| **Repository Funzionante** | 25 | Inizializzazione corretta e commit validi |
| **Messaggi di Commit** | 25 | Messaggi descrittivi e ben formattati |
| **Organizzazione** | 20 | Struttura logica del progetto |
| **Funzionalità** | 20 | Sito web funzionante e completo |
| **Best Practices** | 10 | Uso di .gitignore e convenzioni |

**Punteggio Minimo**: 70/100 per considerare l'esercizio completato con successo.

---

## 🔄 Navigazione

- [⬅️ Torna alla guida principale](../README.md)
- [📖 Guide teoriche](../guide/)
- [💡 Esempi pratici](../esempi/)
- [➡️ Prossimo esercizio: Creazione Portfolio](02-creazione-portfolio.md)

---

*Questo esercizio è parte del corso "Git e GitHub By Example" - Modulo 04: Comandi Base Git*
