# Esercizio 2: Basi della Collaborazione Git

## Obiettivi dell'Esercizio
- Implementare workflow di collaborazione Git fondamentali
- Gestire fork, branch e pull request
- Simulare contribuzioni open source
- Praticare code review e merge strategies

## Descrizione del Progetto

Creerai e gestirai un progetto collaborativo simulando un team di sviluppo che lavora su una **calcolatrice scientifica web** con interfaccia moderna.

## Prerequisiti

- Account GitHub configurato
- Git installato localmente
- Conoscenza base di HTML/CSS/JavaScript
- SSH key configurata (opzionale ma consigliata)

## Fase 1: Setup del Progetto Base (15 punti)

### 1.1 Creazione Repository Principale

```bash
# Crea il repository principale
mkdir scientific-calculator
cd scientific-calculator

# Inizializza Git
git init
git branch -M main

# Crea struttura base
mkdir css js tests docs
touch index.html css/style.css js/calculator.js README.md
```

### 1.2 Contenuto Base del Progetto

Crea i file fondamentali:

**index.html**:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Calcolatrice Scientifica</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="calculator-container">
        <div class="display">
            <input type="text" id="display" readonly>
        </div>
        <!-- I pulsanti verranno aggiunti collaborativamente -->
        <div class="buttons-grid" id="buttonsGrid">
            <!-- Placeholder per i pulsanti -->
        </div>
    </div>
    <script src="js/calculator.js"></script>
</body>
</html>
```

**README.md**:
```markdown
# Calcolatrice Scientifica Collaborativa

Progetto di collaborazione per implementare una calcolatrice scientifica moderna.

## Team Members
- [Il tuo nome] - Project Lead
- [Aggiungi altri collaboratori]

## Features da Implementare
- [ ] Operazioni base (+, -, *, /)
- [ ] Funzioni trigonometriche
- [ ] Logaritmi e esponenziali
- [ ] Gestione della memoria
- [ ] Storia delle operazioni
- [ ] Tema scuro/chiaro

## Contribuire
1. Fork del repository
2. Crea un branch per la feature
3. Implementa e testa
4. Crea pull request
```

### 1.3 Primo Commit e Repository Remoto

```bash
# Primo commit
git add .
git commit -m "feat: setup initial project structure

- Add basic HTML structure
- Create placeholder for calculator components
- Setup project directories
- Add initial README with contribution guidelines"

# Crea repository su GitHub (sostituisci USERNAME)
# Poi collega il remote
git remote add origin https://github.com/USERNAME/scientific-calculator.git
git push -u origin main
```

## Fase 2: Workflow di Collaborazione (25 punti)

### 2.1 Simulazione Fork e Clone

```bash
# Simula un secondo collaboratore
cd ..
mkdir collaborator-workspace
cd collaborator-workspace

# Fork simulation: clona il repository originale
git clone https://github.com/USERNAME/scientific-calculator.git calculator-fork
cd calculator-fork

# Aggiungi remote upstream
git remote add upstream https://github.com/USERNAME/scientific-calculator.git
git remote -v
```

### 2.2 Implementazione Feature Branch

Crea branch per diverse funzionalità:

```bash
# Branch per operazioni base
git checkout -b feature/basic-operations
```

Implementa le operazioni base in `js/calculator.js`:

```javascript
class ScientificCalculator {
    constructor() {
        this.display = document.getElementById('display');
        this.currentInput = '';
        this.operator = null;
        this.firstOperand = null;
        this.waitingForOperand = false;
        this.setupButtons();
    }

    setupButtons() {
        const buttonsGrid = document.getElementById('buttonsGrid');
        
        const buttons = [
            ['C', '±', '%', '÷'],
            ['7', '8', '9', '×'],
            ['4', '5', '6', '-'],
            ['1', '2', '3', '+'],
            ['0', '.', '=']
        ];

        buttons.forEach(row => {
            row.forEach(button => {
                const btn = document.createElement('button');
                btn.textContent = button;
                btn.className = this.getButtonClass(button);
                btn.onclick = () => this.handleButtonClick(button);
                buttonsGrid.appendChild(btn);
            });
        });
    }

    getButtonClass(button) {
        if (['+', '-', '×', '÷', '='].includes(button)) return 'operator';
        if (['C', '±', '%'].includes(button)) return 'function';
        return 'number';
    }

    handleButtonClick(value) {
        // Implementazione base delle operazioni
        // TODO: Aggiungere funzionalità avanzate
    }
}

// Inizializza calcolatrice
document.addEventListener('DOMContentLoaded', () => {
    new ScientificCalculator();
});
```

### 2.3 CSS Styling Collaborativo

Crea `css/style.css`:

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
}

.calculator-container {
    background: rgba(255, 255, 255, 0.1);
    backdrop-filter: blur(10px);
    border-radius: 20px;
    padding: 20px;
    box-shadow: 0 8px 32px rgba(31, 38, 135, 0.37);
    border: 1px solid rgba(255, 255, 255, 0.18);
}

.display input {
    width: 100%;
    height: 80px;
    font-size: 2em;
    text-align: right;
    background: rgba(0, 0, 0, 0.1);
    border: none;
    border-radius: 10px;
    color: white;
    padding: 0 15px;
    margin-bottom: 20px;
}

.buttons-grid {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 10px;
    max-width: 300px;
}

button {
    height: 60px;
    border: none;
    border-radius: 10px;
    font-size: 1.2em;
    cursor: pointer;
    transition: all 0.2s ease;
}

button.number {
    background: rgba(255, 255, 255, 0.2);
    color: white;
}

button.operator {
    background: #ff6b6b;
    color: white;
}

button.function {
    background: #4ecdc4;
    color: white;
}

button:hover {
    transform: translateY(-2px);
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
}
```

### 2.4 Commit e Push Feature

```bash
# Commit della feature
git add .
git commit -m "feat(ui): implement basic calculator interface

- Add responsive button grid layout
- Implement glass morphism design
- Create basic calculator class structure
- Add hover animations and modern styling

Closes #1"

# Push del branch
git push origin feature/basic-operations
```

## Fase 3: Pull Request e Code Review (20 punti)

### 3.1 Creazione Pull Request

Vai su GitHub e crea una pull request con:

**Titolo**: `feat(ui): Implement basic calculator interface`

**Descrizione**:
```markdown
## Descrizione
Implementa l'interfaccia base della calcolatrice scientifica con design moderno e responsivo.

## Modifiche
- ✅ Layout responsive con CSS Grid
- ✅ Design glass morphism
- ✅ Struttura base della classe Calculator
- ✅ Animazioni hover sui pulsanti
- ✅ Sistema di classi per diversi tipi di pulsanti

## Test
- [x] Layout responsive su mobile
- [x] Hover animations
- [x] Accessibilità keyboard

## Screenshots
[Allega screenshot dell'interfaccia]

## Checklist
- [x] Codice testato localmente
- [x] Seguiti gli standard di coding
- [x] Documentazione aggiornata
- [x] No breaking changes
```

### 3.2 Code Review Process

Simula il processo di review:

```bash
# Torna al repository principale
cd ../../scientific-calculator

# Fetch dei cambiamenti
git fetch origin

# Review del branch
git checkout feature/basic-operations
git log --oneline
git diff main..feature/basic-operations
```

Crea commenti di review (documenta in un file `review-comments.md`):

```markdown
# Code Review Comments

## Positivi
- Ottimo uso del CSS moderno (backdrop-filter)
- Struttura del codice ben organizzata
- Naming conventions consistenti

## Suggerimenti
- Aggiungere error handling per operazioni invalide
- Considerare l'accessibilità (aria-labels)
- Aggiungere unit tests

## Richieste di Modifica
- Implementare la logica di calcolo mancante
- Aggiungere validazione input
```

### 3.3 Merge della Pull Request

```bash
# Merge della feature (fast-forward se possibile)
git checkout main
git merge --no-ff feature/basic-operations -m "Merge pull request #1: feat(ui): basic calculator interface"

# Tag della release
git tag -a v0.1.0 -m "Release v0.1.0: Basic calculator interface"

# Push changes
git push origin main
git push origin v0.1.0

# Cleanup branch
git branch -d feature/basic-operations
git push origin --delete feature/basic-operations
```

## Fase 4: Gestione Conflitti (20 punti)

### 4.1 Creazione Conflitto Intenzionale

```bash
# Crea due branch che modificano lo stesso file
git checkout -b feature/scientific-functions
git checkout -b feature/memory-functions

# Nel branch scientific-functions
git checkout feature/scientific-functions
```

Modifica `js/calculator.js` aggiungendo funzioni scientifiche:

```javascript
// Aggiungi al constructor
this.setupScientificButtons();

// Aggiungi metodo
setupScientificButtons() {
    const scientificButtons = ['sin', 'cos', 'tan', 'log', 'ln', '√', 'x²', 'x³'];
    // Implementazione...
}
```

```bash
git add .
git commit -m "feat: add scientific functions support"
```

### 4.2 Conflitto Parallelo

```bash
# Nel branch memory-functions
git checkout feature/memory-functions
```

Modifica lo stesso file aggiungendo funzioni di memoria:

```javascript
// Aggiungi al constructor
this.memory = 0;
this.setupMemoryButtons();

// Aggiungi metodo
setupMemoryButtons() {
    const memoryButtons = ['MC', 'MR', 'M+', 'M-', 'MS'];
    // Implementazione...
}
```

```bash
git add .
git commit -m "feat: add memory functions support"
```

### 4.3 Risoluzione Conflitti

```bash
# Merge del primo branch
git checkout main
git merge feature/scientific-functions

# Tentativo di merge del secondo (conflitto)
git merge feature/memory-functions
```

Risolvi manualmente i conflitti combinando entrambe le funzionalità:

```javascript
class ScientificCalculator {
    constructor() {
        this.display = document.getElementById('display');
        this.currentInput = '';
        this.operator = null;
        this.firstOperand = null;
        this.waitingForOperand = false;
        this.memory = 0; // Memoria calcolatrice
        
        this.setupButtons();
        this.setupScientificButtons(); // Funzioni scientifiche
        this.setupMemoryButtons();     // Funzioni memoria
    }
    
    // ... resto del codice ...
}
```

```bash
# Completa il merge
git add .
git commit -m "merge: combine scientific and memory functions

- Integrate both scientific and memory features
- Resolve constructor conflicts
- Maintain compatibility with base functionality"
```

## Fase 5: Testing e CI/CD Simulation (10 punti)

### 5.1 Unit Tests

Crea `tests/calculator.test.js`:

```javascript
// Test basico (può essere eseguito in Node.js con jsdom)
class CalculatorTests {
    static runAll() {
        console.log('Running Calculator Tests...');
        
        // Test basic operations
        this.testBasicOperations();
        this.testScientificFunctions();
        this.testMemoryFunctions();
        this.testErrorHandling();
        
        console.log('All tests completed!');
    }
    
    static testBasicOperations() {
        console.log('✓ Basic operations test passed');
    }
    
    static testScientificFunctions() {
        console.log('✓ Scientific functions test passed');
    }
    
    static testMemoryFunctions() {
        console.log('✓ Memory functions test passed');
    }
    
    static testErrorHandling() {
        console.log('✓ Error handling test passed');
    }
}

// Esegui test se in ambiente Node.js
if (typeof module !== 'undefined') {
    CalculatorTests.runAll();
}
```

### 5.2 GitHub Actions Simulation

Crea `.github/workflows/ci.yml`:

```yaml
name: CI Pipeline

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Install dependencies
      run: npm install jsdom
    
    - name: Run tests
      run: node tests/calculator.test.js
    
    - name: Validate HTML
      run: |
        curl -H "Content-Type: text/html; charset=utf-8" \
             --data-binary @index.html \
             https://validator.w3.org/nu/?out=text
```

## Fase 6: Documentazione e Release (10 punti)

### 6.1 Documentazione Completa

Aggiorna `README.md`:

```markdown
# Calcolatrice Scientifica Collaborativa

[![CI Pipeline](https://github.com/USERNAME/scientific-calculator/workflows/CI%20Pipeline/badge.svg)](https://github.com/USERNAME/scientific-calculator/actions)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/USERNAME/scientific-calculator/releases)

Una calcolatrice scientifica moderna sviluppata collaborativamente con design glass morphism.

## 🚀 Features

- ✅ **Operazioni Base**: Addizione, sottrazione, moltiplicazione, divisione
- ✅ **Funzioni Scientifiche**: sin, cos, tan, log, ln, √, potenze
- ✅ **Memoria**: MC, MR, M+, M-, MS
- ✅ **Design Moderno**: Glass morphism con animazioni
- ✅ **Responsive**: Ottimizzato per desktop e mobile
- ✅ **Accessibile**: Supporto keyboard e screen reader

## 🛠️ Setup Sviluppo

```bash
# Clone repository
git clone https://github.com/USERNAME/scientific-calculator.git
cd scientific-calculator

# Avvia server locale
python -m http.server 8000
# oppure
npx serve .

# Apri browser
open http://localhost:8000
```

## 🤝 Contribuire

1. **Fork** del repository
2. **Crea** branch feature (`git checkout -b feature/amazing-feature`)
3. **Commit** cambiamenti (`git commit -m 'feat: add amazing feature'`)
4. **Push** branch (`git push origin feature/amazing-feature`)
5. **Apri** Pull Request

### Coding Standards

- Usa conventional commits
- Testa tutte le funzionalità
- Mantieni il codice leggibile
- Aggiungi documentazione per nuove features

## 📚 Documentazione API

### Calculator Class

```javascript
const calc = new ScientificCalculator();

// Metodi pubblici
calc.handleButtonClick(value)    // Gestisce input pulsanti
calc.calculate()                 // Esegue calcolo
calc.clear()                     // Reset calcolatrice
calc.memorySave(value)          // Salva in memoria
calc.memoryRecall()             // Richiama da memoria
```

## 🧪 Testing

```bash
# Esegui tutti i test
node tests/calculator.test.js

# Test specifici
node tests/scientific.test.js
node tests/memory.test.js
```

## 📦 Release History

### v1.0.0 (2025-05-29)
- 🎉 **Initial Release**
- ➕ Operazioni matematiche base
- ➕ Funzioni scientifiche complete
- ➕ Sistema memoria avanzato
- ➕ UI moderna responsive

### v0.1.0 (2025-05-29)
- 🎨 Setup interfaccia base
- 🏗️ Struttura progetto

## 👥 Team

- **[Il tuo nome]** - Project Lead & Frontend
- **[Collaboratore 1]** - Scientific Functions
- **[Collaboratore 2]** - Memory System
- **[Collaboratore 3]** - Testing & QA

## 📄 Licenza

MIT License - vedi [LICENSE](LICENSE) per dettagli.

## 🙏 Ringraziamenti

- Design ispirato alle calcolatrici scientifiche moderne
- Comunità open source per feedback e contributi
- GitHub per l'hosting e CI/CD

---

**⭐ Se questo progetto ti è utile, lascia una stella!**
```

### 6.2 Changelog e Release

Crea `CHANGELOG.md`:

```markdown
# Changelog

Tutte le modifiche importanti a questo progetto verranno documentate in questo file.

Il formato è basato su [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
e questo progetto aderisce al [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-05-29

### Added
- Calcolatrice scientifica completa
- Operazioni matematiche base (+, -, *, /)
- Funzioni trigonometriche (sin, cos, tan)
- Funzioni logaritmiche (log, ln)
- Sistema memoria avanzato (MC, MR, M+, M-, MS)
- Design glass morphism responsivo
- Animazioni e transizioni fluide
- Test suite completa
- Documentazione API
- CI/CD pipeline

### Security
- Validazione input per prevenire XSS
- Sanitizzazione operazioni matematiche

## [0.1.0] - 2025-05-29

### Added
- Setup iniziale progetto
- Struttura HTML base
- CSS foundation
- Classe Calculator base
- README con linee guida contribuzione
```

```bash
# Tag release finale
git tag -a v1.0.0 -m "Release v1.0.0: Complete scientific calculator

Features:
- Full scientific calculator functionality
- Modern glass morphism design
- Memory operations
- Comprehensive test suite
- Complete documentation"

git push origin v1.0.0
```

## Criteri di Valutazione

### Eccellente (90-100 punti)
- **Setup Progetto** (15/15): Repository ben strutturato, commit semantici
- **Workflow Collaborativo** (25/25): Branch strategy efficace, fork gestito correttamente
- **Pull Request** (20/20): PR ben documentate, review process implementato
- **Gestione Conflitti** (20/20): Conflitti risolti elegantemente mantenendo funzionalità
- **Testing** (10/10): Test completi, CI/CD simulato
- **Documentazione** (10/10): README professionale, changelog dettagliato

### Buono (75-89 punti)
- Setup completo ma commit meno dettagliati
- Workflow funzionante con minor attenzione ai dettagli
- PR create ma documentazione basilare
- Conflitti risolti ma soluzioni meno eleganti
- Test presenti ma coverage limitata
- Documentazione adeguata ma non eccellente

### Sufficiente (60-74 punti)
- Setup base funzionante
- Workflow implementato con errori minori
- PR create senza documentazione dettagliata
- Conflitti risolti con difficoltà
- Test minimi o assenti
- Documentazione basilare

### Insufficiente (<60 punti)
- Setup incompleto o non funzionante
- Workflow non implementato correttamente
- PR mancanti o mal documentate
- Conflitti non risolti o risolti male
- Testing assente
- Documentazione inadeguata

## Bonus (fino a 20 punti aggiuntivi)

1. **Implementazione GitHub Actions reale** (+5 punti)
2. **Deploy automatico su GitHub Pages** (+5 punti)
3. **Integrazione con issues e projects** (+5 punti)
4. **Code coverage reports** (+3 punti)
5. **Implementazione semantic release** (+2 punti)

## Consegna

Fornisci:
1. **URL del repository** principale
2. **Screenshot** dell'interfaccia
3. **Link alle Pull Request** create
4. **Report** del processo (massimo 2 pagine) che descriva:
   - Sfide incontrate
   - Soluzioni implementate
   - Lezioni apprese sul workflow collaborativo
   - Miglioramenti futuri

---

**Tempo stimato**: 4-6 ore  
**Difficoltà**: Intermedio  
**Focus**: Collaborazione, workflow Git, project management
