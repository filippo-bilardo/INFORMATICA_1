# 01 - Git Status e Monitoraggio

## 📖 Spiegazione Concettuale

`git status` è il comando più importante che userai quotidianamente con Git. È il tuo "radar" che ti mostra sempre dove ti trovi e cosa sta succedendo nel tuo repository.

### Perché è Importante?

Prima di qualsiasi operazione Git, dovresti sempre sapere:
- Su quale branch ti trovi
- Quali file sono stati modificati
- Cosa è nell'area di staging
- Se ci sono conflitti o problemi

`git status` risponde a tutte queste domande in modo chiaro e actionable.

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git status
```

### Opzioni Utili
```bash
git status --short          # Output compatto (-s)
git status --branch         # Mostra info branch (-b)
git status --porcelain      # Output machine-readable
git status --ignored        # Mostra anche file ignorati
git status --untracked-files=all  # Mostra tutti i file non tracciati
```

### Formato Output Compatto
```bash
git status -s
# Output:
# M  modified.txt     # Modified in index
#  M workspace.txt    # Modified in working tree
# A  added.txt        # Added to index
# D  deleted.txt      # Deleted from index
# ?? untracked.txt    # Untracked
# !! ignored.txt      # Ignored
```

## 💼 Casi d'Uso Pratici

### 1. **Check-in Quotidiano**
```bash
# Prima di iniziare a lavorare
git status
# Vedi se ci sono modifiche pending o pull necessari
```

### 2. **Prima di Commit**
```bash
# Modifica alcuni file...
echo "new content" >> file.txt

git status
# On branch main
# Changes not staged for commit:
#   modified:   file.txt

git add file.txt
git status
# On branch main
# Changes to be committed:
#   modified:   file.txt
```

### 3. **Debugging Problemi**
```bash
git status
# Ti dice se sei in mezzo a un merge, rebase, etc.
```

### 4. **Monitoring During Merge**
```bash
# Durante un merge con conflitti
git status
# On branch main
# You have unmerged paths.
#   (fix conflicts and run "git commit")
# Unmerged paths:
#   both modified:   conflicted_file.txt
```

## 🚨 Errori Comuni

### 1. **Non Controllare Status Prima di Operazioni**
```bash
# ❌ SBAGLIATO
git checkout other-branch  # Potrebbe avere modifiche non salvate

# ✅ CORRETTO  
git status                 # Controlla prima
git add .                  # Salva modifiche se necessario
git commit -m "WIP"        
git checkout other-branch
```

### 2. **Ignorare Warning di Status**
```bash
# Git status mostra:
# "You have unmerged paths"
# ❌ Non ignorare - risolvi i conflitti!
```

### 3. **Confusion su Working Tree vs Index**
```bash
# Status mostra due sezioni diverse:
# "Changes to be committed" (index/staging)
# "Changes not staged" (working tree)
```

## ✨ Best Practices

### 1. **Habit di Controllo**
```bash
# Sempre prima di:
git status && git pull     # Pull updates
git status && git push     # Push changes  
git status && git merge    # Merge branches
git status && git rebase   # Rebase operations
```

### 2. **Alias Utili**
```bash
# Aggiungi al tuo .gitconfig
git config --global alias.st "status --short --branch"
git config --global alias.stat "status"

# Ora puoi usare:
git st    # Status compatto
git stat  # Status completo
```

### 3. **Script di Automazione**
```bash
#!/bin/bash
# check-repo.sh - Script per check rapido repository

echo "=== Repository Status ==="
git status --short --branch

echo -e "\n=== Unpushed Commits ==="
git log --oneline @{u}..HEAD

echo -e "\n=== Untracked Files ==="
git ls-files --others --exclude-standard
```

### 4. **Interpretazione Rapida**
```bash
# Impara a leggere velocemente:
git status -s
# M  = Modified in index (staged)
#  M = Modified in working tree (unstaged)  
# A  = Added (new file staged)
# D  = Deleted
# R  = Renamed
# C  = Copied
# U  = Unmerged (conflict)
# ?? = Untracked
# !! = Ignored
```

## 🧪 Quiz di Autovalutazione

### Domanda 1
Cosa significa questo output di `git status -s`?
```
M  README.md
 M src/main.js
?? test.txt
```

**A)** README.md è stato modificato ma non staged, main.js è staged, test.txt è ignorato  
**B)** README.md è staged, main.js è modificato ma non staged, test.txt è untracked  
**C)** Tutti i file sono stati modificati  
**D)** Ci sono conflitti in tutti i file  

<details>
<summary>👆 Clicca per la risposta</summary>

**Risposta: B**
- `M ` = README.md modificato e staged (spazio dopo M)
- ` M` = main.js modificato ma non staged (spazio prima di M)  
- `??` = test.txt è untracked (non ancora tracciato da Git)
</details>

### Domanda 2
Quando dovresti SEMPRE usare `git status`?

**A)** Solo quando ci sono errori  
**B)** Una volta al giorno  
**C)** Prima di qualsiasi operazione Git importante  
**D)** Solo dopo aver fatto modifiche  

<details>
<summary>👆 Clicca per la risposta</summary>

**Risposta: C**
`git status` dovrebbe essere il tuo primo comando prima di push, pull, merge, checkout, e qualsiasi altra operazione importante per capire lo stato attuale del repository.
</details>

### Domanda 3
Cosa indica questo messaggio in `git status`?
```
You have unmerged paths.
(fix conflicts and run "git commit")
```

**A)** Hai branch non sincronizzati  
**B)** Sei in mezzo a un merge con conflitti da risolvere  
**C)** Hai file non tracciati  
**D)** Hai modifiche non committate  

<details>
<summary>👆 Clicca per la risposta</summary>

**Risposta: B**
Questo messaggio indica che sei in mezzo a un merge che ha prodotto conflitti. Devi risolvere i conflitti nei file indicati e poi fare commit per completare il merge.
</details>

## 🛠️ Esercizi Pratici

### Esercizio 1: Status Exploration
```bash
# 1. Crea un nuovo repository
mkdir git-status-practice
cd git-status-practice
git init

# 2. Osserva status repository vuoto
git status

# 3. Crea alcuni file
echo "Hello" > file1.txt
echo "World" > file2.txt
mkdir src
echo "console.log('test')" > src/app.js

# 4. Controlla status dopo creazione file
git status
git status -s

# 5. Aggiungi file selettivamente
git add file1.txt
git status

# 6. Modifica file già staged
echo "Hello Git" > file1.txt
git status

# Cosa noti? file1.txt appare sia in staged che unstaged!
```

### Esercizio 2: Status Durante Workflow
```bash
# Continua dall'esercizio precedente

# 1. Commit parte delle modifiche
git add file1.txt  # Staging della versione modificata
git commit -m "Add file1 with Git greeting"

# 2. Modifica file committato
echo "Hello Git and GitHub" > file1.txt

# 3. Aggiungi nuovo file
echo "print('Python')" > script.py

# 4. Analizza status complesso
git status
git status -s

# 5. Usa flag diversi
git status --ignored
git status --untracked-files=all

# Comprendi ogni sezione dell'output
```

### Esercizio 3: Status Alias e Automation
```bash
# 1. Crea alias utili
git config --global alias.st "status --short --branch"
git config --global alias.stat "status"

# 2. Testa i nuovi alias
git st
git stat

# 3. Crea function bash per status esteso
# Aggiungi al tuo .bashrc:
gitstat() {
    echo "=== Git Status ==="
    git status --short --branch
    echo ""
    echo "=== Branch Info ==="
    git branch -v
    echo ""
    echo "=== Recent Commits ==="
    git log --oneline -5
}

# 4. Test della function
gitstat
```

## 📚 Risorse Aggiuntive

- [Git Status Documentation](https://git-scm.com/docs/git-status)
- [Git Status Porcelain Format](https://git-scm.com/docs/git-status#_porcelain_format_version_1)
- [Pro Git Book - Recording Changes](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)

## 🔄 Navigazione del Modulo

- [📑 Indice Modulo](../README.md)
- [⬅️ Modulo Precedente](../../03-Primo-Repository-Git/README.md)
- [➡️ 02-Git Add e Staging Area](./02-git-add.md)

---

**Prossimo**: Impareremo come utilizzare `git add` in modo efficace per controllare precisamente cosa includere nei commit.
