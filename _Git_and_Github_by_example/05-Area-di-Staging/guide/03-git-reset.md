# 03 - Git Reset e Unstaging

## 📖 Concetto di Reset

Il comando `git reset` è uno strumento potente per "annullare" operazioni add e modificare lo stato della staging area. È essenziale per correggere errori e mantenere un controllo preciso sui commit.

## 🎯 Tipi di Reset

### 1. Reset della Staging Area (Soft)
```bash
git reset filename.js         # Rimuove un file specifico dalla staging
git reset                     # Rimuove tutto dalla staging (mantiene modifiche)
```

### 2. Reset del Working Directory (Hard)
```bash
git reset --hard              # ATTENZIONE: elimina tutte le modifiche!
git reset --hard HEAD         # Torna all'ultimo commit
```

### 3. Reset Misto (Mixed - Default)
```bash
git reset HEAD~1              # Annulla ultimo commit + unstage
git reset commit-hash         # Va a un commit specifico
```

## 🔧 Operazioni di Unstaging

### Rimuovere File Specifici
```bash
# Scenario: hai aggiunto troppi file
git add .                     # Aggiungi tutto (errore!)
git status
# Changes to be committed:
#   new file:   important.js
#   new file:   temp.log       ← Non volevi questo
#   modified:   index.html

# Rimuovi il file indesiderato
git reset temp.log
# Ora temp.log torna a "untracked"
```

### Rimuovere Tutto dalla Staging
```bash
git add file1.js file2.css file3.html
git reset                     # Rimuove tutto, mantiene modifiche
git status
# Changes not staged for commit:
#   modified:   file1.js       ← Modifiche preservate
#   modified:   file2.css
#   modified:   file3.html
```

## ⚠️ Livelli di Reset

### 1. --soft (Solo Repository)
```bash
git reset --soft HEAD~1       # Annulla commit, mantiene staging e working
```
```
Repository: HEAD~1 ← HEAD     (commit annullato)
Staging:    [file.js]         (mantiene file staged)
Working:    [modifiche]       (mantiene modifiche)
```

### 2. --mixed (Default - Repository + Staging)
```bash
git reset HEAD~1              # Annulla commit + unstage
git reset --mixed HEAD~1      # Equivalente al precedente
```
```
Repository: HEAD~1 ← HEAD     (commit annullato)
Staging:    [ ]               (staging svuotata)
Working:    [modifiche]       (mantiene modifiche)
```

### 3. --hard (Repository + Staging + Working)
```bash
git reset --hard HEAD~1       # ELIMINA TUTTO! Torna al commit precedente
```
```
Repository: HEAD~1 ← HEAD     (commit annullato)
Staging:    [ ]               (staging svuotata)  
Working:    [ ]               (modifiche ELIMINATE)
```

## 🚨 Uso Sicuro del Reset

### Sempre Backup Prima di --hard
```bash
# PRIMA di reset --hard
git stash                     # Salva modifiche correnti
git reset --hard HEAD~1      # Ora è sicuro
# Se serve recuperare:
git stash pop                 # Recupera le modifiche
```

### Alternative Sicure
```bash
# Invece di reset --hard, usa:
git checkout HEAD -- filename.js    # Reset singolo file
git clean -fd                       # Rimuovi file untracked
```

## 🔄 Scenari Pratici

### Scenario 1: Commit Sbagliato
```bash
# Hai fatto commit ma vuoi modificare i file
git add file1.js file2.js
git commit -m "Add new feature"
# Oh no! Devo aggiungere altro codice

# Soluzione:
git reset --soft HEAD~1       # Annulla commit, mantiene staging
# Ora i file sono ancora staged, aggiungi altre modifiche
echo "more code" >> file1.js
git add file1.js
git commit -m "Add complete new feature"
```

### Scenario 2: Add Sbagliato
```bash
# Hai aggiunto file che non volevi
git add .                     # Ops! Anche temp files
git status
# Changes to be committed:
#   new file:   feature.js     ← Vuoi questo
#   new file:   debug.log      ← Non vuoi questo
#   new file:   temp.txt       ← Non vuoi questo

# Soluzione: reset selettivo
git reset debug.log temp.txt
# Ora solo feature.js è staged
```

### Scenario 3: Esperimento Fallito
```bash
# Hai sperimentato ma non funziona
git add experiment.js
git commit -m "Try new approach"
# ... più modifiche ...
# L'esperimento non funziona!

# Soluzione: torna indietro completamente
git reset --hard HEAD~1      # Elimina tutto l'esperimento
```

## 📊 Tabella di Confronto

| Comando | Repository | Staging | Working Directory |
|---------|------------|---------|-------------------|
| `git reset --soft HEAD~1` | ← | Mantiene | Mantiene |
| `git reset HEAD~1` | ← | Svuota | Mantiene |
| `git reset --hard HEAD~1` | ← | Svuota | Svuota |
| `git reset filename.js` | - | Rimuove file | Mantiene |

## 🛠️ Comandi di Recovery

### Se hai fatto reset --hard per errore
```bash
# Git mantiene uno storico dei reset
git reflog                    # Vedi la cronologia delle operazioni
# 1a2b3c4 HEAD@{0}: reset: moving to HEAD~1
# 5d6e7f8 HEAD@{1}: commit: My important work ← Eccolo!

git reset --hard 5d6e7f8     # Recupera il commit perduto
```

### Verifica prima di operazioni rischiose
```bash
git log --oneline -3          # Vedi ultimi 3 commit
git stash                     # Backup delle modifiche correnti
git reset --hard HEAD~1      # Ora è sicuro
```

## 🎯 Best Practices

### 1. **Preferisci Reset Selettivo**
```bash
# MEGLIO: specifico
git reset filename.js         # Solo un file

# EVITA: generico
git reset                     # Tutto dalla staging
```

### 2. **Usa Stash per Sicurezza**
```bash
git stash                     # Backup automatico
git reset --hard HEAD~1      # Operazione rischiosa
git stash pop                 # Recupera se necessario
```

### 3. **Controlla Sempre lo Stato**
```bash
git status                    # Prima di reset
git reset filename.js
git status                    # Dopo reset per verificare
```

### 4. **Log Prima di Reset Commit**
```bash
git log --oneline -5          # Vedi dove stai andando
git reset HEAD~2              # Reset informato
```

## 🔍 Comandi di Diagnosi

### Vedere cosa è in staging
```bash
git diff --staged             # Mostra contenuto della staging area
git diff --cached             # Sinonimo del precedente
```

### Vedere differenze tra stati
```bash
git diff                      # Working vs Staging
git diff --staged             # Staging vs Repository
git diff HEAD                 # Working vs Repository
```

### Status dettagliato
```bash
git status --short            # Formato compatto
git status --porcelain        # Formato per script
```

## ⚠️ Errori Comuni e Soluzioni

### Errore: "Cannot reset in middle of merge"
```bash
# Durante un merge in corso
git merge --abort             # Annulla il merge
git reset HEAD~1              # Ora puoi fare reset
```

### Errore: "Ambiguous argument 'HEAD~1'"
```bash
# Nessun commit nel repository
git status                    # Verifica se ci sono commit
# Se è il primo commit, non puoi fare reset
```

### Reset non funziona come aspettato
```bash
# Verifica dove sei
git log --oneline -3
git status
# Potrebbe essere che non hai modifiche da resettare
```

## 🧠 Quiz di Controllo

### Domanda 1
Hai fatto `git add .` ma vuoi rimuovere solo `debug.log` dalla staging area. Cosa fai?

**A)** `git reset --hard debug.log`  
**B)** `git reset debug.log`  
**C)** `git remove debug.log`

### Domanda 2
Qual è la differenza tra `git reset HEAD~1` e `git reset --hard HEAD~1`?

**A)** Nessuna differenza  
**B)** --hard elimina anche le modifiche nel working directory  
**C)** --hard è più veloce  

### Domanda 3
Come recuperi un commit dopo aver fatto `git reset --hard HEAD~1` per errore?

**A)** Non è possibile  
**B)** `git reflog` poi `git reset --hard <commit-hash>`  
**C)** `git undo`  

---

**Risposte**: 1-B, 2-B, 3-B

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./02-comandi-add.md)
- [➡️ Prossima Guida](./04-workflow-staging.md)

---

**Prossimo passo**: [Workflow con Staging](./04-workflow-staging.md) - Pattern e strategie avanzate
