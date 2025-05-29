# Esercizio 02: Staging Interattivo

## 🎯 Obiettivo

Padroneggiare l'uso di `git add -p` e altre tecniche di staging interattivo per gestire modifiche complesse e creare commit atomici perfetti.

## ⏱️ Durata Stimata: 60-75 minuti

## 📋 Prerequisiti

- Completamento dell'Esercizio 01 (Pratica Staging Base)
- Familiarità con editor di testo
- Conoscenza comandi Git base

## 🚀 Setup Iniziale

```bash
# Crea nuovo progetto per staging interattivo
mkdir interactive-staging && cd interactive-staging
git init

# Configurazione base
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"
```

## 📝 Esercizio 1: Introduzione a git add -p

### Setup del Progetto

```bash
# Crea un file JavaScript con funzioni miste
cat > calculator.js << 'EOF'
// Calculator App
class Calculator {
    constructor() {
        this.result = 0;
    }
    
    add(a, b) {
        return a + b;
    }
    
    subtract(a, b) {
        return a - b;
    }
    
    multiply(a, b) {
        return a * b;
    }
}

module.exports = Calculator;
EOF

# Commit iniziale
git add calculator.js
git commit -m "initial calculator implementation"
```

### Task 1.1: Modifiche Miste al File

```bash
# Aggiungi funzionalità miste: alcune pronte, altre in sviluppo
cat > calculator.js << 'EOF'
// Calculator App - Enhanced Version
class Calculator {
    constructor() {
        this.result = 0;
        this.history = []; // Nuova feature: cronologia
    }
    
    add(a, b) {
        const result = a + b;
        this.history.push(`${a} + ${b} = ${result}`); // Pronto per commit
        return result;
    }
    
    subtract(a, b) {
        const result = a - b;
        this.history.push(`${a} - ${b} = ${result}`); // Pronto per commit
        return result;
    }
    
    multiply(a, b) {
        const result = a * b;
        this.history.push(`${a} * ${b} = ${result}`); // Pronto per commit
        return result;
    }
    
    // TODO: Questa funzione non è ancora pronta
    divide(a, b) {
        console.log("DEBUG: dividing", a, b); // Debug temporaneo
        if (b === 0) {
            throw new Error("Division by zero");
        }
        const result = a / b;
        // TODO: Aggiungere alla cronologia
        return result;
    }
    
    // Metodo pronto per commit
    getHistory() {
        return this.history;
    }
    
    // TODO: Non implementato completamente
    clearHistory() {
        console.log("TEMP: clearing history"); // Debug temporaneo
        this.history = [];
    }
}

module.exports = Calculator;
EOF
```

### Task 1.2: Staging Interattivo Base

**🎯 Obiettivo**: Committa solo le parti "pronte per produzione", escludendo debug e TODO.

```bash
# Inizia staging interattivo
git add -p calculator.js

# Ti verranno mostrati diversi "hunks" (blocchi di modifiche)
# Per ogni hunk dovrai scegliere:
# y = yes (includi nel commit)
# n = no (non includere)
# s = split (dividi il hunk se possibile)
# e = edit (modifica manualmente il hunk)
# q = quit (esci)
# ? = help (mostra aiuto)
```

**🔍 Strategia di Staging**:
1. **Constructor con history**: ✅ SÌ (feature completa)
2. **Metodi add/subtract/multiply con history**: ✅ SÌ (pronti)
3. **Metodo getHistory**: ✅ SÌ (completo)
4. **Metodo divide con DEBUG**: ❌ NO (contiene debug)
5. **Metodo clearHistory con TEMP**: ❌ NO (contiene debug)

```bash
# Dopo il staging interattivo, verifica cosa hai staged
git diff --cached

# Dovrebbe mostrare solo le parti "pulite" senza debug
git commit -m "feat: add operation history tracking

- Add history array to track all calculations
- Update add, subtract, multiply to record operations
- Add getHistory() method for accessing calculation history
- Prepare foundation for advanced calculator features"

# Verifica cosa rimane nel working directory
git diff
# Dovrebbe mostrare solo le parti con debug/TODO non committate
```

## 📝 Esercizio 2: Splitting e Editing di Hunks

### Task 2.1: Setup Scenario Complesso

```bash
# Crea un file con molte modifiche interconnesse
cat > utils.js << 'EOF'
// Utility Functions
const formatNumber = (num) => {
    return num.toString();
};

const validateInput = (input) => {
    return !isNaN(input);
};

module.exports = {
    formatNumber,
    validateInput
};
EOF

git add utils.js
git commit -m "add basic utility functions"

# Ora aggiungi modifiche complesse
cat > utils.js << 'EOF'
// Utility Functions - Enhanced
const formatNumber = (num, decimals = 2) => {
    // Aggiunta: supporto per decimali (PRONTA)
    return Number(num).toFixed(decimals);
};

const validateInput = (input) => {
    // Fix: miglior validazione (PRONTA)
    return typeof input === 'number' && !isNaN(input);
};

// Nuova funzione pronta per commit
const roundNumber = (num, decimals = 0) => {
    const factor = Math.pow(10, decimals);
    return Math.round(num * factor) / factor;
};

// TODO: Questa funzione non è ancora completa
const formatCurrency = (amount) => {
    console.log("DEBUG: formatting", amount); // Debug temporaneo
    // TODO: Aggiungere supporto per diverse valute
    return `$${amount}`;
};

// Funzione sperimentale - non pronta
const experimentalFunction = () => {
    console.log("EXPERIMENTAL: this might break"); // Non committare
    // Codice sperimentale qui
    return "experimental";
};

module.exports = {
    formatNumber,
    validateInput,
    roundNumber,
    formatCurrency, // TODO: rimuovere quando pronta
    experimentalFunction // TEMP: per testing
};
EOF
```

### Task 2.2: Staging con Splitting

```bash
# Inizia staging interattivo
git add -p utils.js

# Quando Git mostra un hunk grande che contiene sia parti buone che cattive:
# 1. Premi 's' per SPLIT (dividere il hunk)
# 2. Se non può dividere automaticamente, premi 'e' per EDIT

# Esempio di editing manuale:
# Quando premi 'e', si aprirà l'editor con il hunk
# Dovrai rimuovere le righe che NON vuoi committare
# Elimina le righe precedute da '+' che contengono debug/TODO
```

**🎯 Obiettivo**: Committa solo:
- Miglioramenti a `formatNumber` e `validateInput`
- Nuova funzione `roundNumber` completa
- Aggiornamento export (solo per funzioni pulite)

**NON committare**:
- `formatCurrency` con debug
- `experimentalFunction`
- Console.log di debug

### Task 2.3: Verifica e Commit

```bash
# Verifica cosa hai staged
git diff --cached

# Il commit dovrebbe contenere solo codice pulito
git commit -m "enhance utility functions with improved formatting

- Add decimal precision support to formatNumber()
- Improve input validation with type checking
- Add roundNumber() function for precise rounding
- Maintain clean, production-ready code"

# Verifica cosa rimane da gestire
git status
git diff
# Dovrebbe mostrare solo le funzioni sperimentali/debug
```

## 📝 Esercizio 3: Gestione File Multipli con -p

### Task 3.1: Scenario Multi-File

```bash
# Crea più file con modifiche miste
cat > config.js << 'EOF'
// Configuration Management
const config = {
    version: "1.0.0",
    debug: false,
    api: {
        baseUrl: "https://api.example.com"
    }
};

module.exports = config;
EOF

cat > logger.js << 'EOF'
// Simple Logger
const log = (message) => {
    console.log(`[LOG] ${message}`);
};

module.exports = { log };
EOF

git add config.js logger.js
git commit -m "add configuration and logging modules"

# Ora modifica entrambi i file con contenuto misto
cat > config.js << 'EOF'
// Configuration Management - Enhanced
const config = {
    version: "1.1.0", // Bump version (PRONTO)
    debug: true, // TODO: Rimuovere per production
    api: {
        baseUrl: "https://api.example.com",
        timeout: 5000 // Nuova configurazione (PRONTA)
    },
    features: {
        caching: true, // Nuova feature (PRONTA)
        analytics: false // TODO: Implementare
    }
};

console.log("DEBUG: Config loaded"); // Debug temporaneo

module.exports = config;
EOF

cat > logger.js << 'EOF'
// Logger - Enhanced
const levels = {
    INFO: 'INFO',
    WARN: 'WARN',
    ERROR: 'ERROR'
}; // Nuovo: livelli di log (PRONTO)

const log = (message, level = levels.INFO) => {
    const timestamp = new Date().toISOString(); // Nuovo: timestamp (PRONTO)
    console.log(`[${timestamp}] [${level}] ${message}`);
};

// TODO: Questa funzione non è ancora completa
const logToFile = (message) => {
    console.log("DEBUG: logging to file"); // Debug temporaneo
    // TODO: Implementare scrittura su file
};

console.log("TEMP: Logger module loaded"); // Debug temporaneo

module.exports = { 
    log,
    levels,
    logToFile // TODO: rimuovere quando pronta
};
EOF
```

### Task 3.2: Staging Selettivo Multi-File

**🎯 Obiettivo**: Fai due commit separati:
1. **Config**: Solo miglioramenti production-ready
2. **Logger**: Solo miglioramenti ai livelli e timestamp

```bash
# Staging config.js (solo parti pulite)
git add -p config.js
# Includi: version bump, timeout, caching
# Escludi: debug=true, analytics, console.log

git commit -m "feat: enhance configuration with production settings

- Bump version to 1.1.0
- Add API timeout configuration
- Add caching feature flag
- Prepare for production deployment"

# Staging logger.js (solo parti pulite)
git add -p logger.js
# Includi: levels enum, timestamp nel log
# Escludi: logToFile con debug, console.log temporaneo

git commit -m "feat: add logging levels and timestamps

- Add log levels enum (INFO, WARN, ERROR)
- Add timestamp to all log messages
- Improve log formatting for better debugging
- Maintain backward compatibility"
```

### Task 3.3: Gestione del Rimanente

```bash
# Ora hai ancora file con debug/TODO nel working directory
git status
git diff

# Opzione 1: Pulisci manualmente e committa le parti completate
# Opzione 2: Usa stash per salvare il lavoro in corso
git stash push -m "WIP: incomplete features with debug code"

# Verifica che tutto sia pulito
git status  # Dovrebbe essere clean
```

## 📝 Esercizio 4: Interactive Staging Avanzato

### Task 4.1: Uso di git add -i (Interactive Mode)

```bash
# Crea modifiche per testare modalità interattiva completa
echo "// New feature in progress" >> calculator.js
echo "// More utilities needed" >> utils.js
echo "// Config updates" >> config.js

# Usa modalità interattiva completa
git add -i

# Esplora le opzioni:
# 1: status           - vedere stato file
# 2: update           - selezionare file da aggiungere
# 3: revert           - rimuovere file dallo staging
# 4: add untracked    - aggiungere file non tracciati
# 5: patch            - modalità patch (come git add -p)
# 6: diff             - vedere differenze
# 7: quit             - uscire
```

### Task 4.2: Combinazione di Tecniche

**Scenario**: Hai modifiche sparse in più file e vuoi creare commit logici.

```bash
# Setup scenario finale
cat >> calculator.js << 'EOF'

// Nuovo metodo pronto
power(base, exponent) {
    const result = Math.pow(base, exponent);
    this.history.push(`${base}^${exponent} = ${result}`);
    return result;
}

// Debug temporaneo
debugInfo() {
    console.log("TEMP: Calculator state", this);
}
EOF

cat >> utils.js << 'EOF'

// Utility pronta
const isEven = (num) => num % 2 === 0;

// Sperimentale
const experimentalMath = (x) => {
    console.log("EXPERIMENTAL:", x);
    return x * 2; // TODO: implementare correttamente
};
EOF

cat > test-runner.js << 'EOF'
// Test Runner - Solo per testing locale
console.log("Running tests...");
// TODO: Implementare test runner vero
const Calculator = require('./calculator');
const calc = new Calculator();
console.log("Test result:", calc.add(2, 3));
EOF
```

**🎯 Il tuo compito**: Crea questi commit logici:
1. "feat: add power calculation with history tracking"  
2. "feat: add number utility functions"
3. NON committare: debug, experimental, test-runner

<details>
<summary>💡 Suggerimento per la soluzione</summary>

```bash
# 1. Staging power method dal calculator
git add -p calculator.js
# Includi solo il metodo power, escludi debugInfo

git commit -m "feat: add power calculation with history tracking

- Add power() method using Math.pow()
- Include power operations in calculation history
- Maintain consistent API with other operations"

# 2. Staging isEven da utils
git add -p utils.js
# Includi solo isEven, escludi experimentalMath

git commit -m "feat: add number utility functions

- Add isEven() utility for number checking
- Extend utility module for mathematical operations
- Maintain clean utility interface"

# 3. Aggiungi test-runner a .gitignore
echo "test-runner.js" >> .gitignore
git add .gitignore
git commit -m "chore: ignore local test files"
```
</details>

## 🎯 Esercizio 5: Master Challenge

### Scenario Complesso Finale

Crea questa situazione e risolvi usando SOLO staging interattivo:

```bash
# File con 5 tipi di modifiche diverse
cat > master-file.js << 'EOF'
// Master File - Complex Changes
class MasterClass {
    constructor() {
        this.data = [];
        console.log("DEBUG: MasterClass created"); // [1] Debug da rimuovere
    }
    
    // [2] Metodo completo e pronto
    addData(item) {
        if (this.validateData(item)) {
            this.data.push(item);
            return true;
        }
        return false;
    }
    
    // [3] Metodo con bug fix pronto
    getData() {
        return [...this.data]; // Fix: return copy instead of reference
    }
    
    // [4] Metodo parzialmente implementato
    validateData(item) {
        console.log("TEMP: validating", item); // Debug temporaneo
        return item !== null && item !== undefined;
        // TODO: Aggiungere validazione più robusta
    }
    
    // [5] Metodo sperimentale
    experimentalMethod() {
        console.log("EXPERIMENTAL: This might change");
        // Codice sperimentale non stabile
        return "experimental";
    }
}

module.exports = MasterClass;
EOF

git add master-file.js
git commit -m "add master class with basic functionality"

# Ora crea la versione modificata con tutti i tipi di cambiamenti
cat > master-file.js << 'EOF'
// Master File - Enhanced Version
class MasterClass {
    constructor() {
        this.data = [];
        this.version = "2.0.0"; // [COMMIT 1] Version bump pronto
        console.log("DEBUG: MasterClass v2 created"); // [NO] Debug da rimuovere
    }
    
    // [COMMIT 1] Metodo completo e pronto
    addData(item) {
        if (this.validateData(item)) {
            this.data.push(item);
            this.onDataAdded(item); // [COMMIT 1] Nuovo: callback
            return true;
        }
        return false;
    }
    
    // [COMMIT 1] Nuovo metodo callback pronto
    onDataAdded(item) {
        // Hook per estensioni future
        console.log(`Data added: ${JSON.stringify(item)}`); // [NO] Debug
    }
    
    // [COMMIT 2] Metodo con bug fix pronto
    getData() {
        return [...this.data]; // Fix: return copy instead of reference
    }
    
    // [COMMIT 2] Nuovo metodo per conteggio
    getCount() {
        return this.data.length;
    }
    
    // [NO] Metodo parzialmente implementato
    validateData(item) {
        console.log("TEMP: validating", item); // Debug temporaneo
        if (item === null || item === undefined) {
            return false;
        }
        // TODO: Aggiungere validazione tipo
        console.log("TODO: implement type validation"); // Debug
        return true;
    }
    
    // [NO] Metodo sperimentale
    experimentalMethod() {
        console.log("EXPERIMENTAL: This might change");
        // Codice sperimentale non stabile
        return "experimental result";
    }
    
    // [NO] Nuovo metodo non finito
    futureFeature() {
        console.log("FUTURE: not ready for production");
        // TODO: Implementare feature futura
    }
}

module.exports = MasterClass;
EOF
```

### Il Challenge

**🎯 Crea esattamente questi 2 commit usando solo staging interattivo**:

1. **"feat: enhance data management with callbacks"**
   - Version bump (2.0.0)
   - onDataAdded callback in addData
   - onDataAdded method (senza debug console.log)

2. **"fix: improve data access methods"**
   - getData fix (già presente)
   - Nuovo getCount method

**NON deve essere committato**:
- Tutti i console.log di debug/temp/experimental
- validateData con TODO
- experimentalMethod
- futureFeature

### Verifica Finale

```bash
# Dopo aver completato il challenge
git log --oneline -5  # Dovrebbero esserci esattamente 2 nuovi commit

git show HEAD --stat  # Secondo commit: dovrebbe mostrare solo getData e getCount
git show HEAD~1 --stat # Primo commit: dovrebbe mostrare version, addData, onDataAdded

# Verifica che non ci sia debug nei commit
git show HEAD | grep -E "(console\.log|DEBUG|TEMP|TODO)"     # Non dovrebbe trovare nulla
git show HEAD~1 | grep -E "(console\.log|DEBUG|TEMP|TODO)"   # Non dovrebbe trovare nulla

# Verifica working directory
git diff  # Dovrebbe mostrare solo debug/experimental rimasto
```

## ✅ Criteri di Successo

### Checklist Mastery

- [ ] Hai usato `git add -p` per staging selettivo
- [ ] Hai diviso hunks grandi con 's' (split)
- [ ] Hai editato hunks manualmente con 'e' (edit)
- [ ] Hai creato commit atomici senza debug code
- [ ] Hai gestito modifiche multi-file con staging separato
- [ ] Hai completato il Master Challenge correttamente
- [ ] Tutti i commit hanno messaggi descrittivi

### Test di Competenza

```bash
# Auto-valutazione finale
echo "=== VERIFICA STAGING INTERATTIVO ==="

echo "1. Numero di commit (dovrebbe essere ~8-10):"
git rev-list --count HEAD

echo -e "\n2. Commit senza debug code:"
git log --grep="DEBUG\|TEMP\|TODO" --oneline | wc -l
# Dovrebbe essere 0

echo -e "\n3. Working directory con solo debug/experimental:"
git diff --name-only | wc -l
# Dovrebbe essere > 0 (file con debug rimanente)

echo -e "\n4. Nessun file temporaneo tracciato:"
git ls-files | grep -E "(temp|test|debug)" | wc -l
# Dovrebbe essere 0

echo -e "\n5. Cronologia pulita:"
git log --oneline --graph -10
```

## 🎉 Risultato Atteso

Al completamento di questo esercizio avrai:

1. **Padronanza completa** di `git add -p`
2. **Abilità di splitting** e editing di hunks
3. **Workflow professionale** per commit atomici
4. **Gestione avanzata** di modifiche complesse
5. **Repository pulito** senza debug code

## 🚀 Skills Sviluppate

- ✅ **Staging granulare** con precisione chirurgica
- ✅ **Commit atomici** per cronologia pulita  
- ✅ **Gestione debug code** separata da production
- ✅ **Workflow multi-file** coordinato
- ✅ **Quality control** automatico dei commit

## 🔄 Prossimi Passi

- [03-Progetto Multi-File](./03-progetto-multi-file.md) - Applica le competenze a progetti reali
- [../guide/05-staging-interattivo.md](../guide/05-staging-interattivo.md) - Approfondimenti teorici

---

**Congratulazioni!** 🎉 Ora padroneggi il staging interattivo come un professionista Git!
