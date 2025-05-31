# 04 - HEAD e Puntatori

## 📖 Spiegazione Concettuale

**HEAD** è uno dei concetti più importanti di Git. È un puntatore che indica dove ti trovi nel repository - quale commit stai visualizzando attualmente. Comprendere HEAD e i puntatori è fondamentale per navigare efficacemente tra branch e commit.

### Cos'è HEAD?

HEAD è semplicemente un **puntatore mobile** che indica:
- **Il commit corrente** su cui stai lavorando
- **Il branch attivo** (nella maggior parte dei casi)
- **La posizione nella cronologia** del progetto

### Visualizzazione Concettuale

```
commit A ← commit B ← commit C ← main
                              ↑
                            HEAD
```

In questo caso, HEAD punta al branch `main`, che a sua volta punta al commit C.

## 🎯 Tipi di HEAD

### 1. HEAD Normale (Attached HEAD)
```bash
# HEAD punta a un branch
git branch
* main    # <- HEAD è qui
  feature
  bugfix
```

### 2. HEAD Scollegato (Detached HEAD)
```bash
# HEAD punta direttamente a un commit
git checkout abc1234
# Sei in "detached HEAD" state
```

## ⚙️ Sintassi e Parametri

### Visualizzare HEAD
```bash
# Mostra dove punta HEAD
git log --oneline -1

# Mostra HEAD in forma simbolica
git symbolic-ref HEAD

# Mostra SHA di HEAD
git rev-parse HEAD

# Mostra ultimo commit di HEAD
git show HEAD
```

### Riferimenti Relativi a HEAD
```bash
# Commit precedente a HEAD
git show HEAD~1
git show HEAD^

# Due commit prima
git show HEAD~2
git show HEAD^^

# Tre commit prima
git show HEAD~3
git show HEAD^^^
```

### Navigazione con HEAD
```bash
# Vai al commit precedente (detached HEAD)
git checkout HEAD~1

# Torna al branch main
git checkout main

# Vai a un commit specifico
git checkout abc1234
```

## 🔄 Casi d'Uso Pratici

### 1. Esplorazione Cronologia
```bash
# Esempio: Esplorare vecchie versioni
git checkout HEAD~3       # Vai 3 commit indietro
git checkout HEAD~5       # Vai 5 commit indietro
git checkout main         # Torna al presente
```

### 2. Confronto Versioni
```bash
# Confronta attuale con versione precedente
git diff HEAD HEAD~1

# Confronta con versione specifica
git diff HEAD abc1234
```

### 3. Reset Temporaneo
```bash
# Annulla le modifiche all'ultimo commit
git reset --hard HEAD

# Torna al commit precedente
git reset --hard HEAD~1
```

### 4. Cherry-pick da HEAD
```bash
# Applica modifiche di HEAD a altro branch
git checkout feature
git cherry-pick main  # (dove HEAD di main era)
```

## ⚠️ Errori Comuni e Soluzioni

### 1. Panico da Detached HEAD
```bash
# ❌ ERRORE: Non sapere cosa fare in detached HEAD
You are in 'detached HEAD' state...

# ✅ SOLUZIONE: Torna al branch
git checkout main
# oppure crea un branch da qui
git checkout -b new-feature
```

### 2. Confusione HEAD vs Branch
```bash
# ❌ ERRORE: Pensare che HEAD sia sempre un branch
git checkout abc1234  # HEAD ora punta al commit

# ✅ SOLUZIONE: Capire la differenza
# HEAD può puntare a branch o commit
```

### 3. Perdita Modifiche
```bash
# ❌ ERRORE: Reset senza backup
git reset --hard HEAD~1  # Perdi modifiche!

# ✅ SOLUZIONE: Verifica prima
git stash                 # Salva modifiche
git reset --hard HEAD~1   # Fai reset
git stash pop             # Recupera se necessario
```

### 4. Riferimenti Errati
```bash
# ❌ ERRORE: Usare ~ e ^ in modo sbagliato
git show HEAD~1^2  # Confuso!

# ✅ SOLUZIONE: Usa riferimenti semplici
git show HEAD~1   # Un commit indietro
git show HEAD~2   # Due commit indietro
```

## 💡 Best Practices

### 1. Verifica Sempre la Posizione
```bash
# Prima di operazioni importanti
git status
git log --oneline -5
```

### 2. Usa Nomi Simbolici
```bash
# ✅ MEGLIO: Usa nomi branch
git checkout main
git checkout feature

# ❌ EVITA: SHA diretti quando possibile
git checkout abc1234
```

### 3. Gestisci Detached HEAD
```bash
# Se ti trovi in detached HEAD e vuoi mantenere modifiche
git checkout -b new-branch-name

# Se vuoi solo esplorare
git checkout main  # quando hai finito
```

### 4. Backup Prima di Reset
```bash
# Sempre fare backup prima di operazioni distruttive
git branch backup-$(date +%Y%m%d)
git reset --hard HEAD~1
```

## 🧪 Quiz di Verifica

### Domanda 1
**Cos'è HEAD in Git?**

<details>
<summary>Risposta</summary>

HEAD è un puntatore mobile che indica il commit corrente su cui stai lavorando. Solitamente punta a un branch, ma può puntare direttamente a un commit (detached HEAD state).
</details>

### Domanda 2
**Cosa significa `HEAD~2`?**

<details>
<summary>Risposta</summary>

`HEAD~2` si riferisce al commit che si trova due posizioni prima dell'attuale HEAD nella cronologia. È un modo per riferirsi a commit precedenti relativamente alla posizione corrente.
</details>

### Domanda 3
**Quando si verifica "detached HEAD"?**

<details>
<summary>Risposta</summary>

Detached HEAD si verifica quando HEAD punta direttamente a un commit anziché a un branch. Succede quando fai checkout di un commit specifico con il suo SHA o usando riferimenti come `HEAD~3`.
</details>

### Domanda 4
**Come torni al branch main da detached HEAD?**

<details>
<summary>Risposta</summary>

Puoi tornare al branch main semplicemente con `git checkout main`. Se hai fatto modifiche che vuoi mantenere, prima crea un nuovo branch con `git checkout -b nuovo-branch`.
</details>

## 🛠️ Esercizio Pratico: Navigazione HEAD

### Parte 1: Esplorazione Base
```bash
# 1. Controlla la posizione attuale di HEAD
git log --oneline -3

# 2. Vai al commit precedente
git checkout HEAD~1

# 3. Verifica lo stato (dovresti essere in detached HEAD)
git status

# 4. Torna al branch main
git checkout main
```

### Parte 2: Navigazione Avanzata
```bash
# 1. Vai 3 commit indietro
git checkout HEAD~3

# 2. Crea un branch da questa posizione
git checkout -b explore-past

# 3. Fai una piccola modifica e commit
echo "Esplorazione del passato" > past.txt
git add past.txt
git commit -m "Esplorazione cronologia"

# 4. Torna a main e controlla la differenza
git checkout main
git log --oneline --all --graph
```

### Parte 3: Uso Riferimenti
```bash
# 1. Confronta versioni
git diff HEAD HEAD~2

# 2. Mostra informazioni commit precedente
git show HEAD~1

# 3. Verifica dove punta HEAD
git symbolic-ref HEAD
```

## 🔗 Navigazione

**Precedente:** [03 - Struttura ad Albero Git](./04-struttura-albero.md)  
**Successivo:** [05 - Branch Locali vs Remoti](./04-locali-vs-remoti.md)  
**Torna all'Indice:** [README del Modulo](../README.md)  
**Corso Principale:** [Git e GitHub by Example](../../README.md)

## 📚 Risorse Aggiuntive

- [Git Documentation - HEAD](https://git-scm.com/docs/gitglossary#Documentation/gitglossary.txt-aiddefHEADaHEAD)
- [Atlassian - Git HEAD](https://www.atlassian.com/git/tutorials/undoing-changes/git-reset)
- [GitHub Docs - About Git](https://docs.github.com/en/get-started/using-git/about-git)
