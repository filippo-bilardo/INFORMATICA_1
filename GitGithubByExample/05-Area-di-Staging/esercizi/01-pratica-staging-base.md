# Esercizio 01: Pratica Staging Base

## 🎯 Obiettivo

Padroneggiare i concetti fondamentali dell'area di staging attraverso esercizi pratici graduali che simulano scenari di sviluppo reali.

## ⏱️ Durata Stimata: 45-60 minuti

## 📋 Prerequisiti

- Git installato e configurato
- Conoscenza dei comandi base Git
- Editor di testo disponibile

## 🚀 Setup Iniziale

### Parte 1: Preparazione Ambiente

```bash
# Crea directory di lavoro
mkdir staging-practice && cd staging-practice
git init

# Configura Git per l'esercizio (se necessario)
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"
```

## 📝 Esercizio 1: Staging Selettivo Base

### Scenario
Stai lavorando su un piccolo sito web e devi gestire modifiche a file diversi con commit separati.

```bash
# Crea i file del progetto
cat > index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Il Mio Sito</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Benvenuto</h1>
    <p>Questo è il mio sito web.</p>
    <script src="script.js"></script>
</body>
</html>
EOF

cat > style.css << 'EOF'
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
}

h1 {
    color: blue;
}
EOF

cat > script.js << 'EOF'
console.log("Sito caricato!");

function saluta() {
    alert("Ciao!");
}
EOF

# Commit iniziale
git add .
git commit -m "Initial website setup"
```

### Task 1.1: Modifiche Multiple
```bash
# Modifica tutti i file
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <title>Il Mio Fantastico Sito</title>
    <link rel="stylesheet" href="style.css">
    <meta charset="UTF-8">
</head>
<body>
    <h1>Benvenuto nel mio sito!</h1>
    <p>Questo è il mio sito web rinnovato.</p>
    <button onclick="saluta()">Clicca qui</button>
    <script src="script.js"></script>
</body>
</html>
EOF

cat > style.css << 'EOF'
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f0f0f0;
}

h1 {
    color: #333;
    text-align: center;
}

button {
    background-color: #007bff;
    color: white;
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
}
EOF

cat > script.js << 'EOF'
console.log("Sito caricato con successo!");

function saluta() {
    const nome = prompt("Come ti chiami?");
    if (nome) {
        alert(`Ciao ${nome}! Benvenuto nel mio sito!`);
    }
}

// Nuovo: funzione per cambiare colore
function cambiaColore() {
    document.body.style.backgroundColor = 
        document.body.style.backgroundColor === 'lightblue' ? '#f0f0f0' : 'lightblue';
}
EOF
```

### Task 1.2: Staging Strategico

**🎯 Obiettivo**: Fai 3 commit separati per le modifiche HTML, CSS e JavaScript.

```bash
# 1. Prima committa solo le modifiche HTML
git add index.html
git status  # Verifica cosa è staged

# Controlla le differenze staged
git diff --cached

# Commit HTML
git commit -m "improve HTML structure and accessibility

- Add lang attribute for better accessibility
- Update page title to be more descriptive  
- Add meta charset for proper encoding
- Add interactive button for user engagement"

# 2. Poi committa le modifiche CSS
git add style.css
git diff --cached  # Verifica le modifiche CSS
git commit -m "enhance visual design and styling

- Add background color for better visual appeal
- Improve header styling with better color and centering
- Add button styling with modern design
- Enhance overall visual hierarchy"

# 3. Infine committa JavaScript
git add script.js
git diff --cached  # Verifica le modifiche JS
git commit -m "add interactive features and improve UX

- Enhance greeting function with personalization
- Add color change functionality for dynamic interaction
- Improve console logging for better debugging
- Add user input validation"
```

### Task 1.3: Verifica e Analisi

```bash
# Controlla la cronologia
git log --oneline

# Vedi le statistiche dei commit
git log --stat

# Controlla le differenze tra commit
git diff HEAD~2 HEAD~1  # Differenze tra secondo e primo commit precedente
```

## 📝 Esercizio 2: Gestione Errori di Staging

### Scenario
Hai fatto errori nell'area di staging e devi correggerli.

### Task 2.1: Errore - File Aggiunto per Sbaglio

```bash
# Crea file che non dovrebbero essere tracciati
echo "password123" > secret.txt
echo "debug info" > debug.log
cat > config.env << 'EOF'
DATABASE_URL=postgresql://user:pass@localhost/db
API_KEY=secret_key_123456
DEBUG=true
EOF

# ERRORE: Aggiungi tutto senza controllo
git add .
git status  # Ops! Abbiamo aggiunto file sensibili
```

**🎯 Il tuo compito**: Rimuovi i file sensibili dall'area di staging e crea un .gitignore appropriato.

<details>
<summary>💡 Suggerimento</summary>

```bash
# Rimuovi file dall'area di staging
git reset HEAD secret.txt debug.log config.env

# Crea .gitignore
echo "secret.txt" > .gitignore
echo "*.log" >> .gitignore
echo "*.env" >> .gitignore

# Aggiungi solo .gitignore
git add .gitignore
git commit -m "add .gitignore for sensitive files"
```
</details>

### Task 2.2: Reset Strategico

```bash
# Modifica un file esistente
echo "// Questa è una modifica importante" >> script.js
echo "// Questa è solo un test temporaneo" >> script.js
echo "console.log('temporary debug');" >> script.js

# Aggiungi tutto
git add script.js

# PROBLEMA: Vuoi committare solo la modifica importante, non il debug
```

**🎯 Il tuo compito**: Usa staging interattivo per committare solo la parte importante.

<details>
<summary>💡 Suggerimento</summary>

```bash
# Reset del file
git reset HEAD script.js

# Usa staging interattivo
git add -p script.js
# Scegli 'y' per la modifica importante
# Scegli 'n' per il debug temporaneo

git commit -m "add important comment to script"
```
</details>

## 📝 Esercizio 3: Workflow Staging Avanzato

### Scenario
Stai sviluppando una nuova feature ma devi gestire anche un hotfix urgente.

### Task 3.1: Feature in Corso

```bash
# Inizia una nuova feature
cat > newsletter.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Newsletter Signup</title>
</head>
<body>
    <h2>Iscriviti alla Newsletter</h2>
    <form>
        <input type="email" placeholder="La tua email">
        <button type="submit">Iscriviti</button>
    </form>
</body>
</html>
EOF

cat > newsletter.css << 'EOF'
.newsletter-form {
    background: #f8f9fa;
    padding: 20px;
    border-radius: 8px;
    max-width: 400px;
    margin: 0 auto;
}

.newsletter-form input {
    width: 100%;
    padding: 12px;
    margin-bottom: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
}
EOF

# Lavoro parziale - NON committare ancora
git add newsletter.html  # Solo HTML per ora
```

### Task 3.2: Hotfix Urgente

```bash
# URGENTE: Bug trovato nell'index.html
# Il pulsante non ha la funzione collegata correttamente

# Controlla lo stato attuale
git status  # newsletter.html è staged, newsletter.css no

# Salva il lavoro in corso in stash
git stash push newsletter.css -m "WIP: newsletter CSS styling"

# Fixa il bug
sed -i 's/saluta()/saluta(); cambiaColore()/g' index.html

# Staging del fix
git add index.html
git commit -m "hotfix: add missing function call in button

- Fix button click handler to include color change
- Ensures both greeting and color change work together
- Critical fix for user interaction"

# Torna al lavoro sulla feature
git stash pop  # Recupera il CSS
```

### Task 3.3: Completa la Feature

```bash
# Ora completa la feature newsletter
cat >> newsletter.css << 'EOF'

.newsletter-form button {
    background: #007bff;
    color: white;
    padding: 12px 20px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    width: 100%;
}

.newsletter-form button:hover {
    background: #0056b3;
}
EOF

# Update HTML per usare le classi CSS
cat > newsletter.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Newsletter Signup</title>
    <link rel="stylesheet" href="newsletter.css">
</head>
<body>
    <div class="newsletter-form">
        <h2>Iscriviti alla Newsletter</h2>
        <form>
            <input type="email" placeholder="La tua email" required>
            <button type="submit">Iscriviti</button>
        </form>
    </div>
</body>
</html>
EOF

# Staging completo della feature
git add newsletter.html newsletter.css
git commit -m "feat: add newsletter signup component

- Create responsive newsletter signup form
- Add modern styling with hover effects
- Include input validation and accessibility features
- Ready for integration with main site"
```

## 🎯 Esercizio 4: Verifica Competenze

### Task 4.1: Scenario Complesso

Crea questa situazione e risolvila usando solo staging:

1. **File 1** (contact.html): Modifica completa ✅ (da committare)
2. **File 2** (style.css): Modifica parziale (solo metà da committare)
3. **File 3** (temp.txt): File temporaneo ❌ (NON committare)
4. **File 4** (.gitignore): Da aggiornare ✅ (da committare)

```bash
# Setup scenario
echo "<h1>Contattaci</h1><form>...</form>" > contact.html

# CSS con modifiche miste
cat >> style.css << 'EOF'

/* Questo stile è pronto per production */
.contact-form {
    background: white;
    padding: 20px;
}

/* TODO: questo non è ancora pronto */
.debug-border {
    border: 2px solid red;
}
EOF

echo "File temporaneo di test" > temp.txt
echo "temp.txt" >> .gitignore
```

**🎯 Il tuo compito**: Crea due commit:
1. "feat: add contact page with basic styling"
2. "chore: update gitignore for temp files"

### Task 4.2: Auto-Valutazione

Dopo aver completato il task 4.1, rispondi:

1. Quanti commit hai nella cronologia? (dovrebbero essere ~6-7)
2. Tutti i commit hanno messaggi descrittivi?
3. temp.txt è tracciato da Git? (dovrebbe essere NO)
4. L'ultimo commit contiene solo .gitignore?

```bash
# Verifica le tue risposte
git log --oneline
git status
git ls-files | grep temp  # Non dovrebbe mostrare nulla
```

## ✅ Criteri di Successo

### Checklist Completamento

- [ ] Hai creato almeno 5 commit con staging selettivo
- [ ] Hai corretto errori di staging senza perdere lavoro
- [ ] Hai usato `git add -p` per staging interattivo
- [ ] Hai gestito un hotfix durante sviluppo feature
- [ ] Hai creato e utilizzato .gitignore correttamente
- [ ] I tuoi commit hanno messaggi chiari e descrittivi
- [ ] Non hai file temporanei tracciati da Git

### Auto-Test Finale

```bash
# Verifica finale del tuo lavoro
echo "=== CRONOLOGIA COMMIT ==="
git log --oneline

echo -e "\n=== FILE TRACCIATI ==="
git ls-files

echo -e "\n=== STATO REPOSITORY ==="
git status

echo -e "\n=== GITIGNORE ==="
cat .gitignore

# Se tutto è pulito e ben organizzato, hai completato con successo!
```

## 🎉 Risultato Atteso

Al termine di questo esercizio dovresti avere:

1. **Repository organizzato** con cronologia pulita
2. **Competenza nell'uso** di staging selettivo
3. **Capacità di gestire** errori di staging
4. **Workflow efficace** per sviluppo multi-feature
5. **Best practices** per commit atomici

## 🔄 Prossimi Passi

- [02-Staging Interattivo](./02-staging-interattivo.md) - Approfondisci l'uso di `git add -p`
- [03-Progetto Multi-File](./03-progetto-multi-file.md) - Gestisci progetti più complessi

---

**Completato?** Procedi con [02-Staging Interattivo](./02-staging-interattivo.md) per tecniche ancora più avanzate!
