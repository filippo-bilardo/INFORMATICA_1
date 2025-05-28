# 01 - Il Concetto di Staging Area

## 📖 Spiegazione Concettuale

La **Staging Area** (anche chiamata "Index") è una delle caratteristiche più distintive di Git. È un'area intermedia tra la tua directory di lavoro e il repository.

### I Tre Stati di Git

```
Working Directory  →  Staging Area  →  Repository
     (modified)         (staged)        (committed)
```

1. **Working Directory**: I file su cui stai lavorando
2. **Staging Area**: I file preparati per il prossimo commit
3. **Repository**: I file salvati definitivamente nella storia di Git

## 🎯 Perché Esiste la Staging Area?

### Controllo Granulare
```bash
# Scenario: hai modificato 5 file ma vuoi committare solo 2
git add file1.js file2.css    # Solo questi vanno in staging
git commit -m "Fix navigation bug"
```

### Commit Logici
La staging area permette di creare commit che hanno senso logico:
- Un commit = una funzionalità completa
- Un commit = un bug fix specifico
- Un commit = una refactoring ben definita

## 🔧 Comandi Fondamentali

### Aggiungere alla Staging Area
```bash
git add filename.ext          # File specifico
git add *.js                  # Tutti i file .js
git add .                     # Tutto nella directory corrente
git add -A                    # Tutto nel repository
```

### Rimuovere dalla Staging Area
```bash
git reset filename.ext        # Rimuove un file specifico
git reset                     # Rimuove tutto (mantiene modifiche)
```

### Vedere lo Stato
```bash
git status                    # Stato completo
git status --short            # Versione compatta
```

## 🔍 Stati dei File

### Output di git status
```bash
$ git status
On branch main
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)
    modified:   index.html     # STAGED
    new file:   style.css      # STAGED

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
    modified:   script.js      # MODIFIED (not staged)

Untracked files:
  (use "git add <file>..." to include in what will be committed)
    README.md                  # UNTRACKED
```

### Codici di Stato
```bash
M  file.txt    # Modified (staged)
 M file.txt    # Modified (not staged)
MM file.txt    # Modified in both areas
A  file.txt    # Added (new file staged)
?? file.txt    # Untracked
```

## 💡 Workflow Tipico

### 1. Modifica i File
```bash
# Lavori sui tuoi file...
echo "console.log('Hello');" > app.js
echo "body { margin: 0; }" > style.css
```

### 2. Controlla lo Stato
```bash
git status
# ?? app.js
# ?? style.css
```

### 3. Aggiungi Selettivamente
```bash
git add app.js              # Solo app.js va in staging
git status
# A  app.js                 # Staged
# ?? style.css              # Still untracked
```

### 4. Commit
```bash
git commit -m "Add main application logic"
# Solo app.js viene committato
```

### 5. Continua il Lavoro
```bash
git add style.css
git commit -m "Add basic styling"
```

## 🎨 Vantaggi Pratici

### Commit Puliti
```bash
# BAD: tutto insieme
git add .
git commit -m "Various changes"

# GOOD: commit separati e logici
git add src/auth/login.js
git commit -m "Fix login validation bug"

git add src/ui/button.css
git commit -m "Update button styling"
```

### Review Prima del Commit
```bash
git add file1.js
git diff --staged            # Vedi cosa stai per committare
git commit -m "..."          # Solo se soddisfatto
```

### Backup Incrementale
```bash
git add .                    # Salva tutto in staging
# Ora hai un backup anche senza commit
git stash                    # Se necessario
```

## 🔍 Comandi Avanzati

### Add Interattivo
```bash
git add -i                   # Menu interattivo
git add -p                   # Patch mode (commit parziale di file)
```

### Staging Parziale
```bash
# Commit solo alcune righe di un file
git add -p filename.js
# Git ti mostrerà ogni modifica e chiederà cosa fare
```

## ⚠️ Errori Comuni

### 1. **Dimenticare git add**
```bash
git commit -m "Fix bug"      # ERROR: nothing to commit
# Soluzione:
git add filename.js
git commit -m "Fix bug"
```

### 2. **Add tutto senza controllo**
```bash
git add .                    # Potresti aggiungere file indesiderati
# Meglio:
git status                   # Prima controlla
git add filename.js          # Aggiungi specificamente
```

### 3. **Confondere gli stati**
```bash
# File modificato ma non staged
git commit -m "Update file"  # Non committa nulla!
# Soluzione:
git add filename.js
git commit -m "Update file"
```

## 🎯 Best Practices

### 1. **Sempre git status prima di commit**
```bash
git status
git add filename.js
git status                   # Verifica cosa stai committando
git commit -m "..."
```

### 2. **Commit frequenti e piccoli**
```bash
# Ogni volta che completi una micro-funzionalità
git add component.js
git commit -m "Add user validation"

git add styles.css
git commit -m "Style validation messages"
```

### 3. **Usa --dry-run per testare**
```bash
git add --dry-run .          # Vedi cosa verrebbe aggiunto
```

## 📊 Diagramma del Workflow

```
┌─────────────────┐    git add    ┌─────────────────┐    git commit    ┌─────────────────┐
│  Working        │ ──────────────→ │  Staging        │ ─────────────────→ │  Repository     │
│  Directory      │               │  Area           │                  │  (.git)         │
│                 │               │                 │                  │                 │
│  file.txt (M)   │               │  file.txt (S)   │                  │  file.txt (C)   │
└─────────────────┘               └─────────────────┘                  └─────────────────┘
       ↑                                   ↑                                   ↑
    Modifichi                         Prepari per                         Salvi nella
     i file                           il commit                          storia Git
```

## 🧠 Quiz di Controllo

### Domanda 1
Hai modificato 3 file: `index.html`, `style.css`, `script.js`. Vuoi committare solo `index.html`. Quale sequenza di comandi usi?

**A)** 
```bash
git add .
git commit -m "Update index"
```

**B)**
```bash
git add index.html
git commit -m "Update index"
```

**C)**
```bash
git commit -m "Update index" index.html
```

### Domanda 2
Cosa significa questo output di `git status`?
```
Changes to be committed:
    modified:   app.js
Changes not staged for commit:
    modified:   app.js
```

**A)** C'è un errore in Git  
**B)** app.js è stato modificato in staging e poi modificato di nuovo nel working directory  
**C)** app.js non può essere committato  

### Domanda 3
Come rimuovi un file dalla staging area senza perdere le modifiche?

**A)** `git rm filename.js`  
**B)** `git reset filename.js`  
**C)** `git delete filename.js`  

---

## 🔗 Risorse Aggiuntive

- [Pro Git - Staging Area](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)
- [Interactive Staging](https://git-scm.com/book/en/v2/Git-Tools-Interactive-Staging)

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Modulo Precedente](../../04-Comandi-Base-Git/README.md)
- [➡️ Prossima Guida](./02-comandi-add.md)

---

**Prossimo passo**: [Comandi Add in Dettaglio](./02-comandi-add.md) - Approfondisci l'uso di git add
