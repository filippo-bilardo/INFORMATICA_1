# 02 - Comandi Add in Dettaglio

## 📖 Panoramica

Il comando `git add` è il tuo strumento principale per controllare cosa va nel prossimo commit. Esistono molte varianti che ti permettono un controllo preciso su quali modifiche includere.

## 🎯 Varianti del Comando Add

### 1. Add Specifico
```bash
git add filename.txt          # Un file specifico
git add dir/subdir/file.js    # File con percorso completo
git add "file with spaces.txt" # File con spazi (virgolette necessarie)
```

### 2. Add con Pattern
```bash
git add *.js                  # Tutti i file .js nella directory corrente
git add **/*.css              # Tutti i file .css ricorsivamente
git add src/                  # Tutta la directory src/
git add .                     # Tutto nella directory corrente
git add -A                    # Tutto nel repository (anche file cancellati)
```

### 3. Add Selettivo
```bash
git add -p filename.js        # Patch mode - scegli quali righe
git add -i                    # Interactive mode - menu interattivo
git add -u                    # Solo file già tracciati (update)
```

## 🔧 Modalità Interattiva (-i)

### Avvio della Modalità Interattiva
```bash
git add -i
```

### Menu Interattivo
```
           staged     unstaged path
  1:    unchanged        +0/-1 TODO
  2:    unchanged        +1/-1 index.html
  3:    unchanged        +5/-0 README.md

*** Commands ***
  1: status       2: update       3: revert       4: add untracked
  5: patch        6: diff         7: quit         8: help
What now>
```

### Comandi Disponibili
- **1: status** - Mostra lo stato corrente
- **2: update** - Aggiungi file modificati 
- **3: revert** - Rimuovi da staging
- **4: add untracked** - Aggiungi file non tracciati
- **5: patch** - Modalità patch per modifiche parziali
- **6: diff** - Mostra differenze
- **7: quit** - Esci

## 🎨 Modalità Patch (-p)

### Concetto
La modalità patch ti permette di committare solo alcune righe di un file, non tutto il file.

### Esempio Pratico
```bash
# File: calculator.js
function add(a, b) {
    return a + b;  // ← Questa riga è corretta
}

function subtract(a, b) {
    return a - b;  // ← Questa riga ha un bug
}

function multiply(a, b) {
    return a * b;  // ← Questa riga è corretta
}
```

### Uso del Patch Mode
```bash
git add -p calculator.js
```

### Output del Patch Mode
```
@@ -1,9 +1,9 @@
 function add(a, b) {
-    return a + b;
+    return a + b; // Fixed formatting
 }
 
 function subtract(a, b) {
Stage this hunk [y,n,q,a,d,s,e,?]?
```

### Opzioni del Patch Mode
- **y** - yes, aggiungi questo blocco
- **n** - no, salta questo blocco  
- **q** - quit, esci senza salvare
- **a** - all, aggiungi tutti i blocchi rimanenti
- **d** - don't add, non aggiungere nessun blocco rimanente
- **s** - split, dividi il blocco in parti più piccole
- **e** - edit, modifica manualmente il blocco
- **?** - help, mostra aiuto

## 📁 Gestione File e Directory

### Aggiungere Directory
```bash
git add src/                  # Tutta la directory
git add src/components/       # Sottodirectory specifica
git add src/**/*.vue          # Pattern ricorsivo
```

### File con Caratteri Speciali
```bash
git add "file name with spaces.txt"
git add 'file-with-$-symbol.js'
git add file\(with\)parentheses.txt    # Escape dei caratteri speciali
```

### Escludere File Specifici
```bash
# Aggiungi tutto tranne file specifici
git add .
git reset unwanted-file.log             # Rimuovi dalla staging

# Oppure usa patterns più precisi
git add src/ tests/ docs/               # Solo certe directory
```

## ⚡ Opzioni Avanzate

### --dry-run (Simulazione)
```bash
git add --dry-run .           # Simula l'operazione senza eseguirla
git add --dry-run *.js        # Vedi quali file verrebbero aggiunti
```

### --verbose (Dettagliato)
```bash
git add --verbose .           # Mostra ogni file che viene aggiunto
```
```
add 'src/component.js'
add 'tests/component.test.js'
add 'docs/api.md'
```

### --force (Forza)
```bash
git add --force ignored-file.log    # Forza l'aggiunta di file ignorati
```

### --intent-to-add (-N)
```bash
git add -N new-file.js        # Marca il file come "intended to add"
                             # Utile per vedere diff di file nuovi
```

## 🔄 Flussi di Lavoro Comuni

### 1. Review e Add Graduale
```bash
git status                    # Vedi cosa è cambiato
git diff                      # Vedi le modifiche in dettaglio
git add -p                    # Aggiungi selettivamente
git status                    # Verifica cosa hai staged
git diff --staged             # Review finale prima del commit
git commit -m "..."           # Commit
```

### 2. Add Smart per Bug Fix
```bash
# Scenario: hai fixato un bug ma anche aggiunto features
git add -p bug-file.js        # Solo le righe del bug fix
git commit -m "Fix calculation bug"

git add -p bug-file.js        # Aggiungi le righe delle features
git commit -m "Add input validation"
```

### 3. Workflow con Stash
```bash
git add .                     # Stage tutto
git stash --staged            # Stash solo ciò che è staged
# Continua a lavorare...
git stash pop                 # Recupera le modifiche staged
```

## 🚀 Esempi Pratici

### Esempio 1: Progetto Web
```bash
# Struttura:
project/
├── index.html      (modificato)
├── style.css       (nuovo)
├── script.js       (modificato)
├── images/         (nuova directory)
│   └── logo.png    (nuovo)
└── temp.log        (file temporaneo)

# Add strategico:
git add index.html script.js     # Solo file principali
git add style.css images/        # CSS e assets
# temp.log rimane untracked (corretto)

git status
# Changes to be committed:
#   modified:   index.html
#   new file:   style.css
#   modified:   script.js
#   new file:   images/logo.png
# Untracked files:
#   temp.log
```

### Esempio 2: Refactoring Graduale
```bash
# File con molte modifiche: api.js
# - Rinominato variabili (riga 10-20)
# - Fixato bug (riga 45)
# - Aggiunto logging (riga 60-70)

# Commit separati:
git add -p api.js
# Seleziona solo il bug fix (riga 45)
git commit -m "Fix API timeout issue"

git add -p api.js  
# Seleziona il refactoring (riga 10-20)
git commit -m "Improve variable naming"

git add api.js
# Remainder: logging
git commit -m "Add debug logging"
```

## ⚠️ Troubleshooting

### Problema: "Nothing to commit"
```bash
git commit -m "My changes"
# On branch main
# nothing to commit, working tree clean

# Soluzione:
git status                    # Controlla se hai modifiche
git add filename.js           # Aggiungi le modifiche
git commit -m "My changes"
```

### Problema: File non viene aggiunto
```bash
git add myfile.txt
git status
# myfile.txt non appare in "Changes to be committed"

# Possibili cause:
1. File è in .gitignore        # Controlla .gitignore
2. Errore di digitazione       # Verifica nome file
3. File non esiste             # ls -la per verificare

# Soluzioni:
git add --force myfile.txt     # Se è ignorato
git status --ignored           # Vedi file ignorati
```

### Problema: Add troppi file
```bash
git add .
# Hai aggiunto file indesiderati

# Soluzione:
git reset                     # Rimuovi tutto dalla staging
git add filename.js           # Aggiungi solo ciò che vuoi
```

## 🎯 Best Practices

### 1. **Review prima di Add**
```bash
git diff                      # Sempre controlla le modifiche
git add -p                    # Usa patch mode per controllo
```

### 2. **Add Specifico vs Add All**
```bash
# PREFERISCI:
git add src/auth.js tests/auth.test.js    # Specifico

# EVITA:
git add .                                 # Troppo generico
```

### 3. **Commit Logici**
```bash
# Un commit = una funzionalità
git add user-login.js user-login.css
git commit -m "Implement user login"

# Non mescolare funzionalità diverse
git add login.js logout.js profile.js    # EVITA
```

### 4. **Usa .gitignore**
```bash
# Invece di evitare manualmente file temporanei
echo "*.log" >> .gitignore
echo "node_modules/" >> .gitignore
echo ".env" >> .gitignore
```

## 🧠 Quiz di Controllo

### Domanda 1
Vuoi committare solo le prime 10 righe di un file che ne ha 50 modificate. Quale comando usi?

**A)** `git add -p filename.js`  
**B)** `git add -i filename.js`  
**C)** `git add --lines=1:10 filename.js`  

### Domanda 2
Cosa fa `git add -A`?

**A)** Aggiunge solo file nuovi  
**B)** Aggiunge tutti i file modificati e nuovi in tutto il repository  
**C)** Aggiunge solo file nella directory corrente  

### Domanda 3
Come verifichi quali file verrebbero aggiunti senza effettivamente aggiungerli?

**A)** `git add --test .`  
**B)** `git add --dry-run .`  
**C)** `git add --simulate .`  

---

**Risposte**: 1-A, 2-B, 3-B

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)  
- [⬅️ Guida Precedente](./01-concetto-staging.md)
- [➡️ Prossima Guida](./03-git-reset.md)

---

**Prossimo passo**: [Git Reset e Unstaging](./03-git-reset.md) - Come annullare le operazioni add
