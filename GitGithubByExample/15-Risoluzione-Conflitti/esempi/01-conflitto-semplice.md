# Esempio 1: Conflitto Semplice

## 🎯 Obiettivi
- Creare e risolvere un conflitto di base
- Familiarizzare con i marker di conflitto
- Apprendere il workflow di risoluzione manuale

## 📋 Scenario
Due sviluppatori lavorano sulla stessa funzione di calcolo in un'applicazione JavaScript. Il primo sviluppatore implementa una versione semplice, il secondo aggiunge validazione input. Durante il merge si verifica un conflitto.

## ⏱️ Durata Stimata
15-20 minuti

## 🛠️ Setup Iniziale

### 1. Crea Repository di Test
```bash
# Crea nuova directory
mkdir simple-conflict-example
cd simple-conflict-example

# Inizializza repository
git init

# Configura utente (se non già fatto)
git config user.name "Developer Main"
git config user.email "main@example.com"
```

### 2. Crea File Base
```bash
# Crea file JavaScript di base
cat > calculator.js << 'EOF'
// Simple Calculator
function add(a, b) {
    return a + b;
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

module.exports = { add, subtract, multiply, divide };
EOF

# Primo commit
git add calculator.js
git commit -m "Initial calculator implementation"
```

## 🌿 Creazione del Conflitto

### 3. Branch Feature A (Miglioramento Performance)
```bash
# Crea e passa al primo branch
git checkout -b feature/performance-optimization

# Configura utente per simulare developer diverso
git config user.name "Alice Developer"
git config user.email "alice@example.com"

# Modifica funzione add per performance
cat > calculator.js << 'EOF'
// Simple Calculator - Performance Optimized
function add(a, b) {
    // Optimized addition with type conversion
    return Number(a) + Number(b);
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

module.exports = { add, subtract, multiply, divide };
EOF

# Commit del primo branch
git add calculator.js
git commit -m "Optimize add function with type conversion"
```

### 4. Branch Feature B (Validazione Input)
```bash
# Torna a main e crea secondo branch
git checkout main

# Configura utente diverso
git config user.name "Bob Developer"  
git config user.email "bob@example.com"

git checkout -b feature/input-validation

# Modifica funzione add per validazione
cat > calculator.js << 'EOF'
// Simple Calculator - Input Validation
function add(a, b) {
    // Add input validation
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Both arguments must be numbers');
    }
    return a + b;
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

module.exports = { add, subtract, multiply, divide };
EOF

# Commit del secondo branch
git add calculator.js
git commit -m "Add input validation to add function"
```

## ⚡ Trigger del Conflitto

### 5. Merge che Genera Conflitto
```bash
# Torna a main
git checkout main

# Merge primo branch (successo)
git merge feature/performance-optimization
```

**Output atteso:**
```
Updating a1b2c3d..e4f5g6h
Fast-forward
 calculator.js | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

```bash
# Ora merge secondo branch (CONFLITTO!)
git merge feature/input-validation
```

**Output atteso:**
```
Auto-merging calculator.js
CONFLICT (content): Merge conflict in calculator.js
Automatic merge failed; fix conflicts and then commit the result.
```

### 6. Analisi del Conflitto
```bash
# Vedi stato repository
git status
```

**Output:**
```
On branch main
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   calculator.js
```

```bash
# Esamina il file con conflitto
cat calculator.js
```

**Contenuto del file:**
```javascript
// Simple Calculator - Performance Optimized
function add(a, b) {
<<<<<<< HEAD
    // Optimized addition with type conversion
    return Number(a) + Number(b);
=======
    // Add input validation
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Both arguments must be numbers');
    }
    return a + b;
>>>>>>> feature/input-validation
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

module.exports = { add, subtract, multiply, divide };
```

## 🔧 Risoluzione del Conflitto

### 7. Analisi delle Opzioni

**Opzione 1**: Mantenere solo performance optimization
```javascript
function add(a, b) {
    // Optimized addition with type conversion
    return Number(a) + Number(b);
}
```

**Opzione 2**: Mantenere solo input validation
```javascript
function add(a, b) {
    // Add input validation
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Both arguments must be numbers');
    }
    return a + b;
}
```

**Opzione 3**: Combinare entrambe (MIGLIORE)
```javascript
function add(a, b) {
    // Combined: validation + optimization
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Both arguments must be numbers');
    }
    return Number(a) + Number(b);
}
```

### 8. Risoluzione Manuale
```bash
# Apri file con editor preferito
nano calculator.js
# oppure
code calculator.js
```

**Modifica il file per combinare entrambe le funzionalità:**
```javascript
// Simple Calculator - Performance Optimized with Validation
function add(a, b) {
    // Combined: input validation + type conversion optimization
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Both arguments must be numbers');
    }
    return Number(a) + Number(b);
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

module.exports = { add, subtract, multiply, divide };
```

### 9. Verifica della Risoluzione
```bash
# Controlla che non ci siano marker residui
grep -n "<<<<<<\|======\|>>>>>>" calculator.js
# Non deve restituire nulla

# Test sintassi JavaScript
node -c calculator.js
# Nessun errore = sintassi corretta
```

### 10. Finalizzazione
```bash
# Aggiungi file risolto
git add calculator.js

# Verifica stato
git status
```

**Output:**
```
On branch main
All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   calculator.js
```

```bash
# Commit finale del merge
git commit -m "Merge feature/input-validation

Resolved conflict in add function by combining:
- Input validation from feature/input-validation
- Type conversion optimization from feature/performance-optimization

Both features are now active for enhanced reliability and performance."
```

## ✅ Verifica Finale

### 11. Test della Soluzione
```bash
# Crea script di test rapido
cat > test.js << 'EOF'
const calc = require('./calculator');

console.log('Testing calculator after conflict resolution...');

try {
    // Test normale
    console.log('add(5, 3):', calc.add(5, 3)); // 8
    
    // Test type conversion  
    console.log('add("5", "3"):', calc.add("5", "3")); // 8
    
    // Test validation (should throw)
    console.log('add(5, "invalid"):', calc.add(5, "invalid"));
} catch (error) {
    console.log('Validation error:', error.message);
}
EOF

# Esegui test
node test.js
```

**Output atteso:**
```
Testing calculator after conflict resolution...
add(5, 3): 8
add("5", "3"): 8
Validation error: Both arguments must be numbers
```

### 12. Visualizza Storia Final
```bash
# Vedi storia completa
git log --oneline --graph
```

**Output:**
```
*   f1a2b3c Merge feature/input-validation
|\  
| * d4e5f6g Add input validation to add function
* | e4f5g6h Optimize add function with type conversion
|/  
* a1b2c3d Initial calculator implementation
```

## 📚 Punti Chiave Appresi

### ✅ Marker di Conflitto
- `<<<<<<< HEAD`: Inizio contenuto branch corrente
- `=======`: Separatore
- `>>>>>>> branch-name`: Fine contenuto branch incoming

### ✅ Processo di Risoluzione
1. **Identifica** conflitto con `git status`
2. **Analizza** marker nel file
3. **Decidi** strategia di risoluzione
4. **Modifica** file manualmente
5. **Verifica** sintassi e logica
6. **Add** file risolto
7. **Commit** merge finale

### ✅ Strategie di Risoluzione
- **Prendi una versione**: Scegli HEAD o incoming
- **Combina**: Integra logica di entrambi
- **Riscrivi**: Crea soluzione completamente nuova

## 🎯 Sfide Aggiuntive

Prova queste varianti per consolidare l'apprendimento:

### Challenge 1: Risoluzione Alternativa
```bash
# Reset a prima del merge
git reset --hard HEAD~1
git branch -D feature/input-validation
git checkout feature/input-validation

# Prova risoluzione diversa (solo validation)
git checkout main
git merge feature/input-validation
# Risolvi scegliendo solo la validazione
```

### Challenge 2: Tool Grafici
```bash
# Ricrea conflitto
git reset --hard HEAD~1
git merge feature/input-validation

# Usa merge tool
git mergetool
```

### Challenge 3: Multiple Solutions
Sperimenta con diverse combinazioni:
- Solo type conversion
- Solo validation
- Validation con conversione diversa
- Aggiunta logging

## ➡️ Prossimo Passo

Ora che hai padroneggiato i conflitti semplici, passa al [prossimo esempio](./02-conflitti-multi-file.md) per gestire conflitti su multipli file simultaneamente.
