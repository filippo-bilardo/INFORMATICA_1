# Esercizio 1: Configurazione Base .gitignore

## Obiettivo
Creare e configurare file .gitignore per un progetto web semplice, apprendendo i pattern base e la gestione di file sensibili.

## Prerequisiti
- Conoscenza base di Git
- Comprensione dei concetti di tracking/untracking files
- Familiarità con la struttura di progetti web

## Scenario
Stai iniziando un nuovo progetto web che include HTML, CSS, JavaScript e alcune configurazioni locali. Devi configurare correttamente il .gitignore per evitare di committare file non necessari o sensibili.

## Parte 1: Setup Progetto Base

### Passo 1: Creazione Struttura
```bash
# Crea il progetto
mkdir esercizio-gitignore-base
cd esercizio-gitignore-base

# Inizializza Git
git init

# Crea la struttura del progetto
mkdir -p {src,assets,config,build,logs}
mkdir -p src/{js,css,components}
mkdir -p assets/{images,fonts,icons}
```

### Passo 2: Creazione File di Progetto
Crea i seguenti file:

**src/index.html**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Progetto Web</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <h1>Il mio progetto web</h1>
    <script src="js/app.js"></script>
</body>
</html>
```

**src/css/style.css**
```css
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
```

**src/js/app.js**
```javascript
// Configurazione applicazione
const config = {
    apiUrl: process.env.API_URL || 'http://localhost:3000',
    debug: process.env.DEBUG || false
};

console.log('App inizializzata con configurazione:', config);

// Funzione principale
function init() {
    console.log('Applicazione avviata');
}

// Avvia l'app quando il DOM è pronto
document.addEventListener('DOMContentLoaded', init);
```

**config/database.template.js**
```javascript
// Template di configurazione database
module.exports = {
    host: 'localhost',
    port: 5432,
    database: 'your_database_name',
    username: 'your_username',
    password: 'your_password',
    ssl: false
};
```

**package.json**
```json
{
  "name": "esercizio-gitignore-base",
  "version": "1.0.0",
  "description": "Esercizio base per .gitignore",
  "main": "src/index.html",
  "scripts": {
    "start": "live-server src/",
    "build": "webpack --mode production",
    "dev": "webpack --mode development --watch"
  },
  "devDependencies": {
    "webpack": "^5.0.0",
    "live-server": "^1.2.0"
  }
}
```

### Passo 3: Simulazione File da Ignorare
Crea questi file che dovrebbero essere ignorati:

```bash
# File di configurazione sensibili
echo "API_KEY=12345-secret-key" > .env
echo "DATABASE_PASSWORD=super_secret" > config/database.js

# Directory di build
mkdir -p build/dist
echo "built file" > build/dist/app.min.js
echo "built css" > build/dist/style.min.css

# Log files
echo "2024-01-15 10:30:00 ERROR: Test error" > logs/error.log
echo "2024-01-15 10:30:00 INFO: App started" > logs/app.log

# Node modules (simulato)
mkdir -p node_modules/express
echo "module content" > node_modules/express/index.js

# File temporanei
echo "temp content" > temp.txt
echo "backup content" > backup.bak

# File del sistema
echo "system file" > .DS_Store
echo "thumb cache" > Thumbs.db

# File IDE
mkdir -p .vscode
echo '{"editor.fontSize": 14}' > .vscode/settings.json
```

## Parte 2: Creazione .gitignore

### Passo 1: .gitignore Base
Crea il file `.gitignore` con i pattern base:

```gitignore
# I tuoi pattern qui
# Segui le indicazioni dell'esercizio
```

**Domande guida:**
1. Quali file contengono informazioni sensibili?
2. Quali directory sono generate automaticamente?
3. Quali file sono specifici del tuo sistema operativo?
4. Quali file sono specifici del tuo IDE?

### Passo 2: Pattern da Implementare
Il tuo .gitignore deve includere pattern per:

1. **File di ambiente**: `.env` e simili
2. **Directory di build**: `build/`, `dist/`
3. **Log files**: `logs/`, `*.log`
4. **Dependencies**: `node_modules/`
5. **File temporanei**: `*.tmp`, `*.bak`, `temp.*`
6. **File di sistema**: `.DS_Store`, `Thumbs.db`
7. **IDE files**: `.vscode/`, `.idea/`
8. **File di configurazione locale**: `config/database.js` (ma non il template)

## Parte 3: Test e Verifica

### Passo 1: Test Iniziale
```bash
# Aggiungi tutto e verifica lo status
git add .
git status

# Domanda: Vedi file che non dovrebbero essere tracciati?
```

### Passo 2: Verifica con git check-ignore
Testa i tuoi pattern:

```bash
# Testa file specifici
git check-ignore .env
git check-ignore config/database.js
git check-ignore logs/error.log
git check-ignore build/dist/app.min.js
git check-ignore node_modules/express/index.js

# Ogni comando dovrebbe restituire il nome del file se è ignorato
```

### Passo 3: Verifica File Tracciati
Assicurati che questi file SIANO tracciati:

```bash
# Questi dovrebbero essere tracciati
git check-ignore src/index.html      # Dovrebbe essere vuoto (non ignorato)
git check-ignore config/database.template.js  # Dovrebbe essere vuoto
git check-ignore package.json       # Dovrebbe essere vuoto
```

## Parte 4: Gestione File Già Tracciati

### Scenario Problema
Supponiamo di aver già committato per errore il file `config/database.js`:

```bash
# Simula commit errato
git add config/database.js
git commit -m "Added database config (ERRORE!)"
```

### Passo 1: Rimozione dal Tracking
```bash
# Rimuovi dal tracking ma mantieni il file
git rm --cached config/database.js

# Verifica che non sia più tracciato
git status
```

### Passo 2: Aggiorna .gitignore
Assicurati che il pattern per `config/database.js` sia nel .gitignore.

### Passo 3: Commit della Correzione
```bash
git add .gitignore
git commit -m "Remove database config from tracking and update .gitignore"
```

## Parte 5: Template e Best Practices

### Passo 1: Crea File Template
Crea un file `.env.template`:

```bash
cat > .env.template << 'EOF'
# Template per variabili d'ambiente
# Copia questo file come .env e personalizza i valori

# API Configuration
API_KEY=your_api_key_here
API_URL=http://localhost:3000

# Database
DATABASE_PASSWORD=your_password_here
DATABASE_HOST=localhost

# Debug
DEBUG=false
EOF
```

### Passo 2: Documentazione
Crea un `README.md` con istruzioni:

```markdown
# Progetto Web Base

## Setup
1. Clona il repository
2. Copia `.env.template` in `.env`
3. Personalizza le variabili in `.env`
4. Installa le dipendenze: `npm install`
5. Avvia il progetto: `npm start`

## File di Configurazione
- `.env.template`: Template per variabili d'ambiente
- `config/database.template.js`: Template per configurazione database

**Non committare mai i file di configurazione reali!**
```

## Verifica Finale

### Checklist Completamento
- [ ] File `.gitignore` creato con tutti i pattern richiesti
- [ ] File sensibili correttamente ignorati
- [ ] File di template tracciati
- [ ] Directory di build ignorate
- [ ] File di sistema ignorati
- [ ] Documentazione creata
- [ ] Test con `git check-ignore` completati

### Comando di Verifica Completa
```bash
# Script di verifica automatica
echo "=== VERIFICA GITIGNORE ==="

# File che dovrebbero essere ignorati
echo "File ignorati:"
git check-ignore .env && echo "✅ .env ignored" || echo "❌ .env NOT ignored"
git check-ignore config/database.js && echo "✅ database.js ignored" || echo "❌ database.js NOT ignored"
git check-ignore logs/error.log && echo "✅ logs ignored" || echo "❌ logs NOT ignored"
git check-ignore node_modules/express/index.js && echo "✅ node_modules ignored" || echo "❌ node_modules NOT ignored"

echo ""
echo "File tracciati:"
git check-ignore .env.template || echo "✅ .env.template tracked"
git check-ignore config/database.template.js || echo "✅ database.template.js tracked"
git check-ignore src/index.html || echo "✅ src files tracked"
git check-ignore package.json || echo "✅ package.json tracked"

echo ""
echo "=== STATUS FINALE ==="
git status --short
```

## Domande di Riflessione

1. **Perché è importante non committare file `.env`?**
2. **Qual è la differenza tra `git rm` e `git rm --cached`?**
3. **Come gestiresti un file che è sia necessario al progetto che contiene dati sensibili?**
4. **Cosa succede se aggiungi un pattern al .gitignore dopo aver già committato i file?**
5. **Come potresti automatizzare la verifica del .gitignore in un team?**

## Soluzioni e Risultati Attesi

### .gitignore Corretto
```gitignore
# File di ambiente
.env
.env.local
.env.production

# Configurazioni locali
config/database.js
config/local.js

# Build directory
build/
dist/

# Logs
logs/
*.log

# Dependencies
node_modules/

# Temporary files
*.tmp
*.bak
temp.*

# System files
.DS_Store
Thumbs.db
*.swp
*.swo

# IDE
.vscode/
.idea/
*.sublime-*

# Templates e documentazione INCLUSI
!.env.template
!config/*.template.js
!README.md
```

### Git Status Atteso
```
On branch main
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

    new file:   .env.template
    new file:   .gitignore
    new file:   README.md
    new file:   config/database.template.js
    new file:   package.json
    new file:   src/css/style.css
    new file:   src/index.html
    new file:   src/js/app.js
```

Completa questo esercizio e verifica che tutti i file sensibili siano correttamente ignorati mentre i file necessari al progetto siano tracciati.
