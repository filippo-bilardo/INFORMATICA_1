# 02 - Stati dei File in Git

## 📖 Spiegazione Concettuale

Git traccia i file attraverso diversi **stati** che rappresentano dove si trova un file nel workflow di Git. Comprendere questi stati è fondamentale per lavorare efficacemente con Git.

### I Tre Stati Principali

1. **Working Directory** (Directory di Lavoro)
2. **Staging Area** (Area di Staging)
3. **Repository** (Repository Git)

E per quanto riguarda i file, Git li classifica in:
- **Untracked** (Non tracciati)
- **Tracked** (Tracciati)
  - **Modified** (Modificati)
  - **Staged** (In staging)
  - **Committed** (Committati)

## 🔧 Visualizzazione Stati

### Comando Principale
```bash
git status
```

### Output Tipico
```bash
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   index.html
        modified:   style.css

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   script.js

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md
```

## 🎯 Ciclo di Vita dei File

### 1. **File Untracked** 
```bash
# File appena creato
echo "Hello World" > nuovo-file.txt
git status
# Output: Untracked files: nuovo-file.txt
```

### 2. **File Staged**
```bash
# Aggiungi all'area di staging
git add nuovo-file.txt
git status
# Output: Changes to be committed: new file: nuovo-file.txt
```

### 3. **File Committed**
```bash
# Commit nella cronologia
git commit -m "Aggiungi nuovo file"
git status
# Output: nothing to commit, working tree clean
```

### 4. **File Modified**
```bash
# Modifica file esistente
echo "Ciao Mondo" >> nuovo-file.txt
git status
# Output: Changes not staged for commit: modified: nuovo-file.txt
```

## 🧐 Dettagli degli Stati

### Untracked Files
- **Cosa sono**: File che Git non conosce ancora
- **Come identificarli**: Elencati in "Untracked files"
- **Prossimo step**: `git add` per iniziare il tracking

### Modified Files
- **Cosa sono**: File tracciati che sono stati modificati
- **Come identificarli**: "Changes not staged for commit"
- **Opzioni**: `git add` per staging o `git restore` per scartare

### Staged Files
- **Cosa sono**: File pronti per il commit
- **Come identificarli**: "Changes to be committed"
- **Opzioni**: `git commit` per salvare o `git restore --staged` per unstage

## 🔍 Comandi per Verificare Stati

### Status Completo
```bash
git status
```

### Status Compatto
```bash
git status -s
# Output:
# M  file-modificato.txt
# A  file-aggiunto.txt
# ?? file-non-tracciato.txt
```

### Differenze Working Directory
```bash
git diff                    # Differenze non staged
git diff --staged          # Differenze staged
git diff HEAD              # Tutte le differenze
```

## 🎯 Casi d'Uso Pratici

### 1. **Preparazione Commit Selettivo**
```bash
# Modifica multipli file
echo "update 1" >> file1.txt
echo "update 2" >> file2.txt
echo "update 3" >> file3.txt

# Staged solo alcuni file
git add file1.txt file2.txt
git status

# Commit parziale
git commit -m "Update file1 and file2"

# file3.txt rimane modified ma non committed
```

### 2. **Controllo Prima del Commit**
```bash
# Verifica cosa stai per committare
git status
git diff --staged

# Se tutto ok, commit
git commit -m "Messaggio descrittivo"
```

### 3. **Ripristino Stati**
```bash
# Scarta modifiche non staged
git restore file-modificato.txt

# Rimuovi da staging area
git restore --staged file-staged.txt

# Rimuovi file untracked (attenzione!)
git clean -f file-indesiderato.txt
```

## ⚠️ Errori Comuni

### 1. **Confondere Modified e Staged**
```bash
# ERRORE: Credere che git add sia permanente
git add file.txt        # File va in staging
echo "change" >> file.txt   # File diventa modified again!
git commit             # Commit solo la versione staged, non le nuove modifiche
```

### 2. **Dimenticare di Verificare Status**
```bash
# ERRORE: Commit senza controllare cosa si sta committando
git add .
git commit -m "Fix"    # ⚠️ Cosa ho committato esattamente?

# CORRETTO:
git add .
git status             # ✅ Verifica prima
git commit -m "Fix login validation and update styles"
```

### 3. **Ignorare File Untracked Importanti**
```bash
# ERRORE: Dimenticare file importanti
git add *.js
git commit -m "Add all JavaScript"
# ⚠️ config.js rimane untracked e non viene committato!
```

## ✅ Best Practices

### 1. **Status Frequente**
```bash
# Controlla status frequentemente
git status

# Usa alias per velocità
git config --global alias.st status
git st
```

### 2. **Commit Atomici**
```bash
# Un commit = una funzionalità/fix
git add specific-files.txt
git commit -m "Fix specific issue"

# Non tutto insieme
# ❌ git add . && git commit -m "Various changes"
```

### 3. **Verifica Prima di Committare**
```bash
# Routine pre-commit
git status              # Cosa sto committando?
git diff --staged      # Come sono le modifiche?
git commit -m "Clear message"
```

## 🧪 Quiz di Autovalutazione

1. **Un file modificato ma non aggiunto con `git add` è in che stato?**
   - A) Staged
   - B) Committed  
   - C) Modified
   - D) Untracked

2. **Cosa mostra `git diff --staged`?**
   - A) Tutte le modifiche
   - B) Solo modifiche non staged
   - C) Solo modifiche staged
   - D) Cronologia commit

3. **Come rimuovi un file dall'area di staging?**
   - A) `git remove`
   - B) `git restore --staged`
   - C) `git unstage`
   - D) `git reset`

4. **Uno status "clean" significa:**
   - A) Nessun file nel progetto
   - B) Tutti file committed, niente da committare
   - C) Solo file staged
   - D) Repository vuoto

**Risposte:** 1-C, 2-C, 3-B, 4-B

## 🏋️ Esercizi Pratici

### Esercizio 1: Ciclo Completo Stati
```bash
# 1. Crea file e osserva stati
echo "Contenuto iniziale" > test.txt
git status      # Untracked

# 2. Aggiungi e osserva
git add test.txt
git status      # Staged

# 3. Commit e osserva
git commit -m "Add test file"
git status      # Clean

# 4. Modifica e osserva
echo "Modifica" >> test.txt
git status      # Modified
```

### Esercizio 2: Stati Multipli
```bash
# 1. Crea e modifica file diversi
echo "File A" > a.txt
echo "File B" > b.txt
echo "File C" > c.txt

# 2. Diversi stati
git add a.txt           # a.txt: staged
echo "update" >> b.txt  # b.txt: untracked
# c.txt: untracked

git status  # Osserva i diversi stati
```

## 🔗 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 01 - Inizializzazione Repository](./01-inizializzazione-repository.md)
- [➡️ 03 - Primo Commit](./03-primo-commit.md)
