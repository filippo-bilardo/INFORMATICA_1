# Risoluzione Manuale dei Conflitti

## 🎯 Obiettivi
- Imparare la risoluzione passo-passo
- Padroneggiare le tecniche manuali
- Sviluppare strategie per conflitti complessi

## 📋 Processo di Risoluzione Completo

### 1. Identificazione dei Conflitti
```bash
# Dopo un merge fallito
$ git status
On branch main
You have unmerged paths.
  (fix conflicts and run "git commit")

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   src/app.js
        both modified:   package.json
        both modified:   README.md
```

### 2. Analisi dei File in Conflitto
```bash
# Esamina ogni file
git diff src/app.js
git diff package.json
git diff README.md
```

## 🔧 Strategie di Risoluzione

### 1. Accetta Una Versione Completa

#### Accetta la Versione Corrente (HEAD)
```bash
git checkout --ours conflicted-file.js
git add conflicted-file.js
```

#### Accetta la Versione Incoming
```bash
git checkout --theirs conflicted-file.js
git add conflicted-file.js
```

### 2. Risoluzione Manuale Dettagliata

#### File di Esempio: `src/calculator.js`
```javascript
class Calculator {
    constructor() {
<<<<<<< HEAD
        this.precision = 10;
        this.history = [];
=======
        this.precision = 2;
        this.memory = 0;
>>>>>>> feature/enhanced-calculator
    }

    add(a, b) {
<<<<<<< HEAD
        const result = parseFloat((a + b).toFixed(this.precision));
        this.history.push(`${a} + ${b} = ${result}`);
        return result;
=======
        return Math.round((a + b) * 100) / 100;
>>>>>>> feature/enhanced-calculator
    }
}
```

#### Risoluzione Passo-Passo

**Passo 1**: Analizza il primo conflitto (constructor)
```javascript
// HEAD vuole: precision=10, history=[]
// Incoming vuole: precision=2, memory=0

// Decisione: combinare entrambe le funzionalità
constructor() {
    this.precision = 10;  // Mantieni alta precisione
    this.history = [];    // Mantieni cronologia
    this.memory = 0;      // Aggiungi memoria
}
```

**Passo 2**: Risolvi il secondo conflitto (metodo add)
```javascript
// HEAD: usa precision e salva in history
// Incoming: usa arrotondamento fisso

// Decisione: usa precision ma mantieni history
add(a, b) {
    const result = parseFloat((a + b).toFixed(this.precision));
    this.history.push(`${a} + ${b} = ${result}`);
    return result;
}
```

**Passo 3**: Risultato finale pulito
```javascript
class Calculator {
    constructor() {
        this.precision = 10;
        this.history = [];
        this.memory = 0;
    }

    add(a, b) {
        const result = parseFloat((a + b).toFixed(this.precision));
        this.history.push(`${a} + ${b} = ${result}`);
        return result;
    }
}
```

## 🛠️ Tecniche Avanzate

### 1. Risoluzione Selettiva
Per conflitti complessi, risolvi sezione per sezione:

```bash
# Modifica il file manualmente
nano src/app.js

# Aggiungi ogni sezione risolta
git add src/app.js

# Controlla stato
git status
```

### 2. Uso di Editor di Testo

#### Con nano
```bash
nano conflicted-file.js
# Cerca i marker con Ctrl+W
# Modifica e salva con Ctrl+X
```

#### Con vim
```bash
vim conflicted-file.js
# Cerca marker: /<<<<<<
# Navigazione: n (prossimo), N (precedente)
# Modalità inserimento: i
# Salva e esci: :wq
```

### 3. Verifica Durante Risoluzione

#### Controlla Sintassi
```bash
# Per JavaScript
node -c src/app.js

# Per Python
python -m py_compile src/app.py

# Per CSS
npx stylelint src/styles.css
```

#### Cerca Marker Residui
```bash
grep -rn "<<<<<<\|======\|>>>>>>" src/
```

## 📝 Esempi Pratici di Risoluzione

### Esempio 1: Conflitto in package.json
```json
{
  "name": "my-project",
<<<<<<< HEAD
  "version": "2.1.0",
  "scripts": {
    "start": "node server.js",
    "test": "jest"
  },
  "dependencies": {
    "express": "^4.18.0"
=======
  "version": "2.0.5",
  "scripts": {
    "start": "nodemon server.js",
    "test": "mocha",
    "lint": "eslint ."
  },
  "dependencies": {
    "express": "^4.17.0",
    "cors": "^2.8.5"
>>>>>>> feature/dev-tools
  }
}
```

#### Risoluzione Ragionata
```json
{
  "name": "my-project",
  "version": "2.1.0",           // Versione più alta
  "scripts": {
    "start": "nodemon server.js", // nodemon per sviluppo
    "test": "jest",               // jest più moderno
    "lint": "eslint ."           // aggiungi linting
  },
  "dependencies": {
    "express": "^4.18.0",        // versione più recente
    "cors": "^2.8.5"            // aggiungi cors
  }
}
```

### Esempio 2: Conflitto in CSS
```css
.header {
<<<<<<< HEAD
    background: linear-gradient(45deg, #667eea 0%, #764ba2 100%);
    padding: 2rem;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
=======
    background-color: #3498db;
    padding: 1.5rem;
    border-bottom: 2px solid #2980b9;
>>>>>>> feature/simple-design
}
```

#### Risoluzione con Compromesso
```css
.header {
    background: linear-gradient(45deg, #3498db 0%, #2980b9 100%);
    padding: 1.75rem;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
```

## 🔍 Checklist di Risoluzione

### ✅ Prima della Risoluzione
- [ ] Backup del repository (se importante)
- [ ] Comprensione del contesto di entrambi i branch
- [ ] Identificazione di tutti i file in conflitto

### ✅ Durante la Risoluzione
- [ ] Risoluzione di un file alla volta
- [ ] Rimozione completa di tutti i marker
- [ ] Test della sintassi dopo ogni file
- [ ] Comprensione dell'impatto delle modifiche

### ✅ Dopo la Risoluzione
- [ ] Verifica assenza marker residui
- [ ] Test di compilazione/interpretazione
- [ ] Esecuzione test automatici
- [ ] Add e commit delle risoluzioni

## 🚨 Situazioni Complesse

### 1. Conflitti in File Binari
```bash
# Git non può mergiare automaticamente
$ git status
both modified:   image.png

# Scegli una versione
git checkout --ours image.png    # Mantieni la tua
git checkout --theirs image.png  # Prendi la loro
```

### 2. Conflitti di Rinominazione
```bash
# File rinominato diversamente
CONFLICT (rename/rename): 
file.txt -> document.txt in HEAD
file.txt -> readme.txt in feature-branch

# Risoluzione manuale
git mv document.txt final-name.txt
git rm readme.txt
git add final-name.txt
```

### 3. Conflitti con Eliminazione
```bash
CONFLICT (modify/delete): 
src/old-module.js deleted in feature-branch 
and modified in HEAD.

# Decisione necessaria:
git rm src/old-module.js      # Se vuoi eliminare
# oppure
git add src/old-module.js     # Se vuoi mantenere
```

## 💡 Best Practices

### 1. Approccio Sistematico
- Risolvi un file alla volta
- Testa dopo ogni risoluzione
- Documenta decisioni complesse

### 2. Comunicazione
```bash
# Commit message descrittivo
git commit -m "Resolve merge conflicts in calculator module

- Combined precision control with history tracking
- Merged enhanced arithmetic with logging
- Updated dependencies to latest versions"
```

### 3. Prevenzione Futura
- Merge regolare da main branch
- Feature branch piccoli e focalizzati
- Code review prima del merge

## ➡️ Prossimo Passo

Nel prossimo modulo esploreremo l'uso di **merge tools grafici** per semplificare il processo di risoluzione.
