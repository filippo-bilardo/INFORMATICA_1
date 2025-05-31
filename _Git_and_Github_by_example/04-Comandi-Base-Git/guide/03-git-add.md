# 03 - Git Add: Aggiungere File al Staging

## 📖 Spiegazione Concettuale

Il comando `git add` è fondamentale nel workflow Git. Sposta i file dalla **Working Directory** alla **Staging Area** (anche chiamata Index), preparandoli per essere "fotografati" nel prossimo commit.

### I Tre Stati di Git

```
Working Directory → Staging Area → Repository
     (add) --------→   (commit) --→
```

1. **Working Directory**: I tuoi file attuali con le modifiche
2. **Staging Area**: File preparati per il prossimo commit  
3. **Repository**: Storia permanente dei commit

## 🔧 Sintassi e Parametri

### Sintassi Base
```bash
git add [pathspec]
```

### Parametri Principali

| Comando | Descrizione | Uso Tipico |
|---------|-------------|------------|
| `git add file.txt` | Aggiunge file specifico | File singoli |
| `git add .` | Aggiunge tutti i file nella cartella corrente | Progetti piccoli |
| `git add -A` | Aggiunge tutti i file del repository | Aggiornamento completo |
| `git add *.js` | Aggiunge tutti i file .js | File per tipo |
| `git add -p` | Aggiunge parti di file interattivamente | Commit selettivi |
| `git add -u` | Aggiunge solo file già tracciati | Update esistenti |

### Esempi Dettagliati

**1. Aggiungere singoli file:**
```bash
git add index.html
git add style.css script.js
```

**2. Aggiungere per pattern:**
```bash
git add *.css          # Tutti i CSS
git add src/           # Tutta la cartella src
git add **/*.test.js   # Tutti i file test.js ricorsivi
```

**3. Aggiungere interattivamente:**
```bash
git add -p file.js
# Git ti chiederà per ogni "hunk" di modifiche:
# y = yes, n = no, s = split, q = quit
```

## 💡 Casi d'Uso Pratici

### Scenario 1: Primo Commit
```bash
# Nuovo progetto con alcuni file
echo "<h1>Hello World</h1>" > index.html
echo "body { color: blue; }" > style.css
echo "console.log('Hello');" > script.js

# Aggiungo tutto per il primo commit
git add .
git status  # Verifico cosa è in staging
git commit -m "Primo commit: struttura base"
```

### Scenario 2: Modifiche Selettive
```bash
# Ho modificato 3 file ma voglio commit separati
git add index.html
git commit -m "Fix: correzione HTML"

git add style.css
git commit -m "Style: nuovo tema colori"

# script.js rimane modificato per dopo
```

### Scenario 3: Staging Interattivo
```bash
# Ho fatto molte modifiche in un file
# Ma voglio committare solo alcune parti
git add -p app.js

# Git mostra ogni "chunk" di modifiche:
# @@ -10,7 +10,8 @@
#  function login() {
# -    return false;
# +    validateUser();
# +    return true;
#  }
# Stage this hunk [y,n,q,a,d,s,e,?]? y
```

### Scenario 4: Gestione File Nuovi vs Modificati
```bash
git status
# Changes not staged for commit:
#   modified:   existing.js
# Untracked files:
#   new-feature.js

git add -u        # Solo file già tracciati (existing.js)
git add new-*     # Solo file nuovi che iniziano con "new-"
```

## ⚠️ Errori Comuni

### 1. **Aggiungere File Indesiderati**
```bash
# ERRORE: Aggiunto file temporaneo
git add temp.log
git add node_modules/

# SOLUZIONE: Rimuovere dal staging
git reset HEAD temp.log
git reset HEAD node_modules/
```

### 2. **Dimenticare il .gitignore**
```bash
# ERRORE: File sensibili in staging
git add .
# Aggiunge anche .env, *.log, node_modules/

# SOLUZIONE: Creare .gitignore prima
echo "node_modules/" > .gitignore
echo "*.log" >> .gitignore
echo ".env" >> .gitignore
git add .gitignore
```

### 3. **Confondere -A e .**
```bash
# In una sottocartella:
cd src/
git add .     # Solo file in src/
git add -A    # Tutti i file del repository
```

### 4. **File con Spazi nel Nome**
```bash
# ERRORE: Nome con spazi
git add file con spazi.txt  # Interpreta come 3 file

# SOLUZIONE: Usa virgolette
git add "file con spazi.txt"
```

## 🎯 Best Practices

### 1. **Review Prima di Add**
```bash
# Sempre verificare cosa stai aggiungendo
git status              # Panoramica generale
git diff                # Modifiche dettagliate
git add .
git status              # Verifica staging area
```

### 2. **Commit Atomici**
```bash
# ✅ BUONO: Un concetto per commit
git add user-login.js
git commit -m "Add user login functionality"

git add user-logout.js  
git commit -m "Add user logout functionality"

# ❌ CATTIVO: Tutto insieme
git add .
git commit -m "Varie modifiche"
```

### 3. **Gitignore Strategy**
```bash
# Crea .gitignore PRIMA di git add
# Template comuni:
echo "node_modules/" > .gitignore
echo "*.log" >> .gitignore  
echo ".env" >> .gitignore
echo "dist/" >> .gitignore
echo ".vscode/" >> .gitignore
```

### 4. **Staging Progressivo**
```bash
# Per progetti grandi, aggiungi progressivamente
git add src/components/   # Solo i componenti
git status                # Verifica
git add src/utils/        # Poi le utility
git status                # Verifica ancora
```

## 🧪 Quiz di Autovalutazione

**1. Cosa fa il comando `git add .`?**
- a) Aggiunge tutti i file del repository
- b) Aggiunge tutti i file nella cartella corrente e sottocartelle
- c) Crea un nuovo file chiamato "."
- d) Rimuove tutti i file

**2. Qual è la differenza tra `git add .` e `git add -A`?**
- a) Sono identici
- b) `-A` aggiunge anche file eliminati, `.` no
- c) `.` è più veloce
- d) `-A` funziona solo nella root

**3. Quando uso `git add -p`?**
- a) Per aggiungere file privati
- b) Per aggiungere interattivamente parti di file
- c) Per aggiungere con password
- d) Per aggiungere file Python

**4. Se ho modificato 5 file ma voglio committarne solo 2?**
- a) `git add .` e poi rimuovo 3 file
- b) `git add file1.js file2.js`
- c) Non è possibile
- d) Devo creare branch separati

<details>
<summary>🔍 Risposte</summary>

1. **b)** Aggiunge tutti i file nella cartella corrente e sottocartelle
2. **b)** `-A` aggiunge anche file eliminati, `.` no
3. **b)** Per aggiungere interattivamente parti di file
4. **b)** `git add file1.js file2.js`

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Add Selettivo
1. Crea 3 file: `home.html`, `about.html`, `contact.html`
2. Aggiungi solo `home.html` al staging
3. Verifica lo status
4. Aggiungi gli altri due file uno per volta

### Esercizio 2: Pattern Matching
1. Crea file: `app.js`, `utils.js`, `test.js`, `README.md`
2. Usa `git add` per aggiungere solo i file JavaScript
3. Verifica che `README.md` non sia in staging

### Esercizio 3: Staging Interattivo
1. Crea un file `code.js` con 10 righe di codice
2. Modifica le righe 2, 5 e 8
3. Usa `git add -p` per aggiungere solo la modifica della riga 5
4. Verifica con `git status` e `git diff --staged`

## 🔗 Collegamenti Rapidi

- **Comando successivo**: [04 - Git Commit](04-git-commit.md)
- **Comando precedente**: [02 - Git Init](02-git-init.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 03-Primo-Repository-Git](../../03-Primo-Repository-Git/README.md)
- [➡️ 05-Area-di-Staging](../../05-Area-di-Staging/README.md)
