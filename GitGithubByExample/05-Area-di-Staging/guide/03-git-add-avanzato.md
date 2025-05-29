# Git Add Avanzato: Staging Selettivo e Controllo Granulare

## 🎯 Obiettivi di Apprendimento
- Padroneggiare le opzioni avanzate di `git add`
- Implementare staging selettivo per commit atomici
- Utilizzare staging interattivo per controllo granulare
- Gestire scenari complessi di staging multiplo

## 🚀 Oltre il `git add` di Base

Mentre `git add <file>` copre le necessità base, Git offre opzioni potenti per uno staging preciso e professionale.

### Richiamo: Comando Base
```bash
git add file.txt        # Aggiungi file singolo
git add .               # Aggiungi tutto nella directory corrente
git add -A              # Aggiungi tutto nel repository
```

## 🎛️ Opzioni Avanzate di Git Add

### 1. Staging per Pattern di File

#### Wildcards e Globbing
```bash
# Aggiungi tutti i file JavaScript
git add *.js

# Aggiungi tutti i file CSS in tutte le sottocartelle
git add **/*.css

# Aggiungi tutti i file di test
git add *test*.js
git add test_*.py

# Aggiungi file con estensioni multiple
git add *.{html,css,js}
```

#### Esempi Pratici di Pattern
```bash
# Frontend development
git add src/**/*.{vue,ts,css}

# Backend Python
git add **/*.py
git add requirements*.txt

# Documentazione
git add *.md
git add docs/**/*.rst

# File di configurazione
git add *.{json,yaml,yml,ini}
```

### 2. Staging Selettivo per Directory

#### Aggiungere Directory Specifiche
```bash
# Aggiungi solo la cartella components
git add src/components/

# Aggiungi multiple directory
git add src/utils/ src/helpers/ src/services/

# Aggiungi directory escludendo sottocartelle
git add src/*.js  # Solo file JS nella root di src
```

#### Gestione Directory Annidate
```bash
# Struttura complessa
project/
├── frontend/
│   ├── src/
│   ├── tests/
│   └── dist/
├── backend/
│   ├── api/
│   ├── models/
│   └── tests/
└── docs/

# Staging strategico
git add frontend/src/          # Solo il codice sorgente frontend
git add backend/api/ backend/models/  # Solo API e modelli backend
git add docs/                  # Tutta la documentazione
```

### 3. Opzioni di Controllo del Comportamento

#### `--dry-run` - Anteprima Sicura
```bash
# Vedere cosa sarebbe aggiunto senza farlo davvero
git add --dry-run .
git add -n .                   # Forma abbreviata

# Esempio di output
# add 'src/components/Header.vue'
# add 'src/styles/main.css'
# add 'tests/unit/header.test.js'
```

#### `--verbose` - Informazioni Dettagliate
```bash
# Mostra dettagli di cosa viene aggiunto
git add --verbose src/
git add -v src/               # Forma abbreviata

# Esempio di output
# add 'src/utils.js'
# add 'src/config.js'
# The following paths are ignored by one of your .gitignore files:
# src/temp.js
```

#### `--force` - Superare .gitignore
```bash
# Forza l'aggiunta di file ignorati
git add --force build/important-config.js
git add -f build/             # Forma abbreviata

# ⚠️ Usare con cautela! Potrebbe aggiungere file che dovrebbero rimanere ignorati
```

## 🎨 Staging Interattivo: Il Potere del `-p`

### Introduzione al Patch Mode
Il **patch mode** (`-p` o `--patch`) permette di scegliere specifiche parti di file da aggiungere:

```bash
git add -p <file>             # Staging interattivo per file
git add --patch <file>        # Forma estesa
git add -p                    # Interattivo per tutti i file modificati
```

### Workflow Staging Interattivo

#### Scenario: File con Multiple Modifiche
```javascript
// utils.js - File con diverse modifiche
function validateEmail(email) {
    // ✅ Modifica 1: Aggiunta validazione email (da committare)
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

function formatDate(date) {
    // ❌ Modifica 2: Debug temporaneo (NON da committare)
    console.log('DEBUG: formatting date', date);
    return date.toLocaleDateString();
}

function calculateAge(birthDate) {
    // ✅ Modifica 3: Nuova funzione (da committare)
    const today = new Date();
    const birth = new Date(birthDate);
    return today.getFullYear() - birth.getFullYear();
}
```

#### Sessione Interattiva
```bash
$ git add -p utils.js

# Git mostra il primo "hunk" (blocco di modifiche)
@@ -1,4 +1,8 @@
 function validateEmail(email) {
+    // Aggiunta validazione email
+    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
+    return emailRegex.test(email);
 }

Stage this hunk [y,n,q,a,d,/,s,e,?]?
```

### Opzioni del Patch Mode

| Comando | Azione | Quando Usare |
|---------|--------|--------------|
| `y` | Yes - Aggiungi questo hunk | Modifica da committare |
| `n` | No - Salta questo hunk | Modifica da non committare |
| `q` | Quit - Esci dal patch mode | Finito con le decisioni |
| `a` | Add all - Aggiungi tutti gli hunk rimanenti | Tutte le altre modifiche sono OK |
| `d` | Don't add - Salta tutti gli hunk rimanenti | Nessuna delle altre modifiche |
| `s` | Split - Dividi hunk in parti più piccole | Hunk troppo grande |
| `e` | Edit - Modifica manualmente l'hunk | Controllo granulare estremo |
| `?` | Help - Mostra opzioni disponibili | Quando sei confuso |

### Splitting e Editing Avanzato

#### Split di Hunk Complessi
```bash
# Quando Git mostra un hunk troppo grande
Stage this hunk [y,n,q,a,d,/,s,e,?]? s

# Git tenta di dividere in parti più piccole
Split into 2 hunks.
@@ -1,2 +1,4 @@
 function validateEmail(email) {
+    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
 }

Stage this hunk [y,n,q,a,d,/,j,J,k,K,s,e,?]? y
```

#### Edit Manuale di Hunk
```bash
# Per controllo granulare estremo
Stage this hunk [y,n,q,a,d,/,s,e,?]? e

# Si apre l'editor con l'hunk:
# Per rimuovere righe: cancellale
# Per aggiungere righe: NON supportato in edit mode
# Salva e chiudi per applicare
```

## 🔄 Staging Incrementale e Iterativo

### Workflow di Staging Graduale

#### Scenario: Refactoring Complesso
```bash
# 1. Prima aggiunta: Solo i test
git add tests/

# 2. Controlla cosa hai aggiunto
git diff --cached

# 3. Aggiungi implementazione correlata
git add src/auth/ src/utils/validation.js

# 4. Rivedi tutto prima del commit
git diff --cached --stat

# 5. Commit atomico
git commit -m "feat: add user authentication with validation

- Add comprehensive auth tests
- Implement login/logout functionality  
- Add email/password validation utilities"
```

### Staging Multi-Fase per Feature Complesse

#### Feature Branch Workflow
```bash
# Fase 1: Database schema
git add migrations/ models/
git commit -m "feat: add user authentication database schema"

# Fase 2: Backend API
git add api/auth/ api/middleware/
git commit -m "feat: implement authentication API endpoints"

# Fase 3: Frontend components
git add components/auth/ pages/login.vue pages/register.vue
git commit -m "feat: add authentication UI components"

# Fase 4: Integration e testing
git add tests/integration/ tests/e2e/
git commit -m "test: add integration tests for authentication flow"
```

## 🎯 Strategie di Staging Professionale

### 1. Staging per Tipo di Modifica

#### Commits Tematici
```bash
# Bug fixes separati
git add src/bugfix/ tests/bugfix/
git commit -m "fix: resolve login timeout issue"

# Feature development separato
git add src/features/ components/
git commit -m "feat: add user profile management"

# Refactoring separato
git add src/utils/ src/helpers/
git commit -m "refactor: optimize utility functions performance"
```

### 2. Staging per Impact Level

#### Modifiche per Criticità
```bash
# Critical fixes first
git add src/security/ src/auth/
git commit -m "security: fix authentication vulnerability"

# Feature additions
git add src/features/ src/components/
git commit -m "feat: add social media integration"

# Styling e polish
git add styles/ assets/
git commit -m "style: update UI with new design system"
```

### 3. Staging per Code Review

#### Preparazione per Review
```bash
# Commit 1: Core logic
git add src/core/ src/models/
git commit -m "feat: implement core business logic"

# Commit 2: Tests
git add tests/ spec/
git commit -m "test: add comprehensive test suite"

# Commit 3: Documentation
git add docs/ README.md
git commit -m "docs: add API documentation and usage examples"
```

## 🔧 Comandi Avanzati Correlati

### Unstaging Selettivo
```bash
# Rimuovi file specifici dalla staging area
git restore --staged <file>
git reset HEAD <file>          # Alternativa

# Unstaging interattivo
git restore --staged -p <file>
git reset -p <file>            # Alternativa
```

### Ispezionare la Staging Area
```bash
# Vedere esattamente cosa è in staging
git diff --cached
git diff --staged

# Lista file in staging
git diff --cached --name-only

# Statistiche delle modifiche in staging
git diff --cached --stat
```

### Staging di Rename e Move
```bash
# Git rileva automaticamente rename/move
mv old-name.js new-name.js
git add old-name.js new-name.js    # Git rileva il rename

# Forza rilevamento rename per file molto modificati
git add -A                         # Cattura moves e renames
```

## 🧪 Laboratorio Pratico

### Esercizio: Staging Complesso
```bash
# Setup scenario
mkdir staging-advanced-lab
cd staging-advanced-lab
git init

# Crea file con contenuti misti
cat > app.js << 'EOF'
// Production code
function calculateTotal(items) {
    return items.reduce((sum, item) => sum + item.price, 0);
}

// Debug code (to remove)
console.log('Debug: app starting');

// New feature (to commit)
function validateInput(input) {
    return input && typeof input === 'string';
}

// Temporary code (to not commit)
function temp() {
    console.log('temporary function');
}
EOF

# Pratica staging selettivo
git add -p app.js
# Seleziona solo production code e new feature
# Escludi debug e temporary code
```

## 🎯 Best Practices per Git Add Avanzato

### 1. Pianificazione pre-Staging
- **Analizza**: Rivedi tutte le modifiche prima di staging
- **Raggruppa**: Identifica modifiche correlate logicamente
- **Prioritizza**: Staging delle modifiche più importanti per prime

### 2. Staging Atomico
- **Un concetto per commit**: Ogni staging dovrebbe rappresentare una singola idea
- **Testabilità**: Ogni commit dovrebbe lasciare il codice in stato funzionante
- **Reversibilità**: Ogni commit dovrebbe essere facilmente revertibile

### 3. Review pre-Commit
```bash
# Sempre rivedi prima di committare
git diff --cached              # Cosa stai per committare
git status                     # Stato generale
git diff                       # Cosa rimane nella working directory
```

## 🔍 Troubleshooting Comune

### Problema: "Staging accidentale di file temporanei"
```bash
# Rimuovi file specifici dalla staging
git restore --staged temp.log debug.txt

# Aggiungi al .gitignore per il futuro
echo "*.log" >> .gitignore
echo "debug.txt" >> .gitignore
```

### Problema: "Hunk troppo grande nel patch mode"
```bash
# Usa split per dividere
git add -p
# Quando appare l'hunk: digita 's'
# Se ancora troppo grande: usa 'e' per edit manuale
```

### Problema: "Non riesco a selezionare specifiche righe"
```bash
# Edit mode per controllo granulare
git add -p <file>
# Digita 'e' quando appare l'hunk
# Rimuovi le righe che non vuoi (con # all'inizio)
# Salva e chiudi
```

## 📚 Recap Concetti Chiave

1. **Pattern matching**: Usa wildcards per staging efficiente
2. **Staging interattivo**: `-p` per controllo granulare
3. **Commit atomici**: Un concetto logico per commit
4. **Review cycle**: Sempre controllare prima di committare
5. **Workflow incrementale**: Build di feature complesse step-by-step

## 🔗 Collegamenti

### Link Interni
- [📖 Tre Aree Git](./02-tre-aree-git.md) - Comprensione del flusso
- [📖 Git Reset Staging](./04-git-reset-staging.md) - Rimozione da staging
- [📖 Staging Interattivo](./05-staging-interattivo.md) - Approfondimento patch mode

### Comandi Essenziali
- `git add -p` - Staging interattivo
- `git add --dry-run` - Anteprima sicura
- `git diff --cached` - Review staging area
- `git restore --staged` - Unstaging

---

> **💡 Pro Tip**: Il staging avanzato è l'arte di raccontare una storia chiara attraverso i commit. Ogni add dovrebbe contribuire a una narrazione logica dello sviluppo del progetto.
