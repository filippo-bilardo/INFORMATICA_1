# Marker di Conflitto in Git

## 🎯 Obiettivi
- Comprendere i marker di conflitto di Git
- Interpretare correttamente la struttura
- Navigare file con conflitti multipli

## 📚 Anatomia dei Marker

Quando Git rileva un conflitto, inserisce **marker speciali** nel file per delimitare le sezioni in conflitto:

```text
<<<<<<< HEAD
Contenuto del branch corrente (HEAD)
=======
Contenuto del branch che stai mergendo
>>>>>>> nome-branch
```

## 🔍 Significato dei Simboli

### `<<<<<<< HEAD`
- **Inizio** della sezione in conflitto
- Indica che il contenuto seguente appartiene al **branch corrente**
- "HEAD" si riferisce al commit su cui ti trovi

### `=======`
- **Separatore** tra le due versioni
- Divide il contenuto del branch corrente da quello incoming
- Come una "linea di confine"

### `>>>>>>> nome-branch`
- **Fine** della sezione in conflitto
- Mostra il nome del branch che stai mergendo
- Indica la fine del contenuto incoming

## 📋 Esempio Pratico

### Scenario: Conflitto in package.json
```json
{
  "name": "my-app",
<<<<<<< HEAD
  "version": "1.2.0",
  "description": "App principale del progetto"
=======
  "version": "1.1.5",
  "description": "Applicazione web moderna"
>>>>>>> feature/update-package
}
```

### Interpretazione
- **Branch corrente** (HEAD): versione 1.2.0, descrizione "App principale"
- **Branch incoming** (feature/update-package): versione 1.1.5, descrizione "Applicazione web moderna"
- **Decisione necessaria**: quale versione mantenere

## 🔧 Tipi di Conflitto e Marker

### 1. Conflitto di Contenuto Standard
```javascript
function calculateTotal(items) {
<<<<<<< HEAD
    return items.reduce((sum, item) => sum + item.price, 0);
=======
    return items.reduce((total, item) => total + item.cost, 0);
>>>>>>> feature/update-calculation
}
```

### 2. Conflitto con Eliminazione
```text
<<<<<<< HEAD
// File modificato in HEAD
function newFeature() {
    console.log("Nuova funzionalità");
}
=======
// File eliminato in feature-branch
>>>>>>> feature/cleanup
```

### 3. Conflitti Multipli nello Stesso File
```css
.header {
<<<<<<< HEAD
    background-color: blue;
    padding: 20px;
=======
    background-color: red;
    padding: 15px;
>>>>>>> feature/styling
}

.footer {
<<<<<<< HEAD
    margin-top: 50px;
=======
    margin-top: 30px;
    border-top: 1px solid #ccc;
>>>>>>> feature/styling
}
```

## 🔍 Informazioni Aggiuntive nei Marker

### Marker con Hash di Commit
```text
<<<<<<< HEAD (commit: abc123)
Contenuto HEAD
=======
Contenuto incoming
>>>>>>> feature-branch (commit: def456)
```

### Marker con Percorso File
```text
<<<<<<< HEAD:src/main.js
export default function main() {
=======
function main() {
>>>>>>> feature-branch:src/main.js
```

## 🛠️ Strumenti per Visualizzare Conflitti

### 1. Git Status
```bash
$ git status
Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   src/app.js
        both modified:   package.json
```

### 2. Git Diff
```bash
$ git diff
++<<<<<<< HEAD
 +    version: "1.2.0"
++======= 
 +    version: "1.1.5"
++>>>>>>> feature/update
```

### 3. Editor con Supporto Git

#### VS Code
```text
Accept Current Change | Accept Incoming Change | Accept Both Changes | Compare Changes
```

#### GitKraken
- Vista a tre pannelli
- Highlight delle differenze
- Merge con drag & drop

## 📝 Best Practices per Leggere Marker

### 1. Leggi dall'Alto in Basso
1. Identifica `<<<<<<< HEAD`
2. Leggi il contenuto del branch corrente
3. Trova il separatore `=======`
4. Leggi il contenuto incoming
5. Trova la fine `>>>>>>> branch-name`

### 2. Capisce il Contesto
```javascript
// Sempre guarda il codice circostante
function processData(data) {
    const processed = data.map(item => {
<<<<<<< HEAD
        return item.transform();
=======
        return item.process();
>>>>>>> feature/refactor
    });
    return processed;
}
```

### 3. Considera l'Impatto
- Quale versione mantiene la funzionalità?
- Ci sono dipendenze che cambiano?
- I test passano con entrambe le versioni?

## 🚫 Errori Comuni

### ❌ Lasciare i Marker nel File
```javascript
// SBAGLIATO - marker non rimossi
function test() {
<<<<<<< HEAD
    console.log("test");
=======
    console.log("debug");
>>>>>>> feature-branch
}
```

### ❌ Risoluzione Incompleta
```javascript
// SBAGLIATO - parte del marker rimasta
function test() {
    console.log("risolto");
>>>>>>> feature-branch  // ← Marker rimasto!
}
```

### ✅ Risoluzione Corretta
```javascript
// CORRETTO - marker rimossi, decisione presa
function test() {
    console.log("risolto");
}
```

## 🔍 Verifica Risoluzione

### 1. Controlla Sintassi
```bash
# Per JavaScript/JSON
node -c file.js

# Per Python
python -m py_compile file.py
```

### 2. Cerca Marker Rimasti
```bash
grep -n "<<<<<<\|=====\|>>>>>>" file.js
```

### 3. Test Funzionalità
```bash
npm test
# o
python -m pytest
```

## 💡 Consigli Pratici

### 1. Non Aver Fretta
- Leggi attentamente entrambe le versioni
- Comprendi l'intento di ogni modifica
- Considera l'impatto sul resto del codice

### 2. Comunica con il Team
- Se non capisci una modifica, chiedi
- Documenta decisioni complesse
- Condividi la risoluzione se innovativa

### 3. Testa Sempre
- Compila/interpreta dopo risoluzione
- Esegui test automatici
- Verifica funzionalità manualmente

## ➡️ Prossimo Passo

Nel prossimo modulo impareremo le tecniche per la **risoluzione manuale** dei conflitti passo dopo passo.
