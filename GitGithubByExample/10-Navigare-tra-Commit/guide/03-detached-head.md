# Detached HEAD State: Capire e Gestire

## 📖 Obiettivi
- Comprendere cos'è il detached HEAD state
- Imparare quando e perché si verifica
- Gestire sicuramente questa modalità
- Recuperare dal detached HEAD senza perdere lavoro

## 📚 Prerequisiti
- Conoscenza di HEAD e puntatori Git
- Familiarità con git checkout/switch
- Comprensione base della cronologia Git

## ⏱️ Durata Stimata
20-25 minuti

---

## 🎭 Cos'è il Detached HEAD?

### Stato Normale: HEAD Punta a Branch

```
Normale:
HEAD -> main -> [commit C]
                    ↑
                [actual commit]
```

In condizioni normali, HEAD punta a un **branch**, che a sua volta punta all'ultimo commit del branch.

### Detached HEAD: HEAD Punta Direttamente a Commit

```
Detached:
HEAD -> [commit B]
        (nessun branch)

main -> [commit C]
        (separato da HEAD)
```

In detached HEAD, HEAD punta **direttamente a un commit specifico**, non a un branch.

---

## 🚨 Come Entrare in Detached HEAD

### 1. Navigazione a Commit Specifico

```bash
# Vai a commit specifico
git checkout abc123

# Risultato:
# HEAD is now at abc123 Some commit message
# You are in 'detached HEAD' state...
```

### 2. Navigazione a Commit Relativo

```bash
# Vai 3 commit indietro
git checkout HEAD~3

# Vai al commit padre
git checkout HEAD^
```

### 3. Navigazione a Tag

```bash
# I tag puntano a commit specifici
git checkout v1.0.0

# Risultato: detached HEAD al commit del tag
```

### 4. Checkout di File da Commit Remoti

```bash
# Navigazione a commit di branch remoto
git checkout origin/main~5
```

---

## ⚠️ Il Messaggio di Avviso

Quando entri in detached HEAD, Git mostra questo messaggio:

```
You are in 'detached HEAD' state. You can look around, make 
experimental changes and commit them, and you can discard any 
commits you make in this state without impacting any branches 
by switching back to a branch.

If you want to create a new branch to retain commits you create, 
you may do so (now or later) by using -c with the switch command. 

Example:
  git switch -c <new-branch-name>

Or undo this operation with:
  git switch -

Turn off this advice by setting config variable 
advice.detachedHead to false
```

### Traduzione del Messaggio

**Cosa significa**:
- ✅ Puoi guardare il codice
- ✅ Puoi fare modifiche sperimentali  
- ✅ Puoi fare commit
- ⚠️ I commit non appartengono a nessun branch
- ❌ Rischi di perdere i commit quando esci

**Come risolvere**:
- Crea un branch: `git switch -c <nome-branch>`
- Oppure torna indietro: `git switch -`

---

## 🧭 Orientarsi in Detached HEAD

### Verificare lo Stato

```bash
# Status mostra detached HEAD
git status
# HEAD detached at abc123

# Posizione esatta di HEAD
git rev-parse HEAD

# Log dalla posizione attuale
git log --oneline -5

# Vedere tutti i branch
git branch -v
# * (HEAD detached at abc123)
#   main     def456 [ahead 2] Latest work
```

### Capire Dove Sei

```bash
# Confronto con branch
git log --oneline main..HEAD     # Commit in HEAD ma non in main
git log --oneline HEAD..main     # Commit in main ma non in HEAD

# Vedere distanza da branch
git rev-list --count main..HEAD  # Quanti commit avanti
git rev-list --count HEAD..main  # Quanti commit indietro
```

---

## 🔧 Operazioni Sicure in Detached HEAD

### 1. Solo Lettura (Sicuro al 100%)

```bash
# Esplorare il codice
cat file.txt
ls -la
git log --oneline

# Vedere differenze
git diff main
git show HEAD
git show HEAD~1

# Queste operazioni sono completamente sicure
```

### 2. Sperimentazione Temporanea

```bash
# Modifiche temporanee per test
echo "test change" >> file.txt

# Compilare/testare
make test

# Scartare modifiche
git checkout -- file.txt
# O
git restore file.txt
```

### 3. Commit Sperimentali (Attenzione!)

```bash
# Commit in detached HEAD
echo "experimental" > test.txt
git add test.txt
git commit -m "Experimental change"

# ⚠️ Questo commit non appartiene a nessun branch!
# Devi salvarlo in un branch o verrà perso
```

---

## 💾 Salvare Lavoro da Detached HEAD

### Scenario 1: Hai Fatto Modifiche Non Committate

```bash
# Opzione 1: Stash e torna
git stash
git switch main
git stash pop

# Opzione 2: Crea branch e salva
git switch -c experimental-work
git add .
git commit -m "Save experimental work"
```

### Scenario 2: Hai Fatto Commit in Detached HEAD

```bash
# Salvare commit in nuovo branch
git switch -c save-work
# Ora i commit sono al sicuro in 'save-work'

# Alternativa: cherry-pick su branch esistente
git switch main
git cherry-pick <hash-commit-detached>
```

### Scenario 3: Multipli Commit da Salvare

```bash
# Metodo 1: Branch da detached HEAD
git switch -c feature-from-detached

# Metodo 2: Merge in branch esistente
git switch main
git merge <hash-ultimo-commit-detached>

# Metodo 3: Cherry-pick range
git switch main
git cherry-pick <first-hash>..<last-hash>
```

---

## 🚪 Come Uscire da Detached HEAD

### 1. Torna al Branch Precedente

```bash
# Torna a dove eri prima
git switch -

# Equivalente con checkout
git checkout -
```

### 2. Vai a Branch Specifico

```bash
# Vai a main
git switch main

# Vai a develop  
git switch develop

# Vai all'ultimo branch utilizzato
git switch -
```

### 3. Crea Branch da Posizione Attuale

```bash
# Crea e switch a nuovo branch
git switch -c my-new-branch

# Equivalente con checkout
git checkout -b my-new-branch
```

---

## 🗑️ Scartare Lavoro in Detached HEAD

### Scartare Modifiche Non Committate

```bash
# Scarta modifiche ai file
git restore .

# O con checkout
git checkout -- .

# Pulisci file non tracciati
git clean -fd
```

### "Perdere" Commit Intenzionalmente

```bash
# Semplicemente esci senza salvare
git switch main

# I commit rimarranno temporaneamente accessibili
# tramite reflog, ma verranno garbage collected
```

### Recuperare Commit "Persi"

```bash
# Trova commit persi nel reflog
git reflog

# Trova qualcosa come:
# abc123 HEAD@{2}: commit: Experimental work
# def456 HEAD@{3}: checkout: moving from main to HEAD~3

# Recupera il commit
git checkout abc123
git switch -c recovered-work
```

---

## 🎯 Casi d'Uso Pratici

### 1. Debugging: Trovare Quando è Apparso un Bug

```bash
# Vai alla versione stabile
git checkout v1.0.0

# Testa
make test
# OK, bug non presente

# Vai a versione più recente
git checkout v1.1.0

# Testa
make test  
# Bug presente! È apparso tra v1.0.0 e v1.1.0

# Torna a main
git switch main
```

### 2. Confronto Performance

```bash
# Test performance versione attuale
git checkout main
time make benchmark

# Test performance 6 mesi fa
git checkout HEAD~100
time make benchmark

# Confronta risultati, torna a main
git switch main
```

### 3. Verifica Fix Storico

```bash
# Qualcuno riporta bug "riapparso"
# Vai al commit del fix originale
git checkout <hash-del-fix>

# Verifica che il fix funzionasse
make test-specific-case

# Vai al commit attuale
git checkout main

# Verifica se il fix è ancora presente
make test-specific-case
```

---

## 🛡️ Best Practices per Detached HEAD

### ✅ Cose Sicure da Fare

```bash
# Esplorare codice
cat, ls, find, grep

# Vedere cronologia
git log, git show, git diff

# Compilare/testare (senza modifiche)
make, npm test, python test.py

# Modifiche temporanee con restore
echo "test" > temp.txt
git restore temp.txt
```

### ⚠️ Cose da Fare con Attenzione

```bash
# Commit sperimentali
git commit -m "experiment"
# Subito dopo: git switch -c experiment-branch

# Modifiche estensive
# Prima: git switch -c working-branch
```

### ❌ Cose da Evitare

```bash
# Mai fare push da detached HEAD
git push origin HEAD  # ❌ Pericoloso

# Mai operazioni distruttive
git reset --hard       # ❌ Può perdere lavoro

# Non ignorare i warning
git commit && git switch main  # ❌ Perderai il commit
```

---

## 🧪 Laboratorio Pratico

### Setup Repository di Test

```bash
mkdir detached-head-lab
cd detached-head-lab
git init

# Crea cronologia ricca
for i in {1..5}; do
  echo "Version $i" > version.txt
  git add version.txt
  git commit -m "Version $i"
done

# Aggiungi tag
git tag v1.0 HEAD~4
git tag v2.0 HEAD~2
git tag stable HEAD
```

### Esercizi Guidati

#### Esercizio 1: Esplorazione Sicura

```bash
# 1. Vai a v1.0
git checkout v1.0
cat version.txt  # Dovrebbe dire "Version 1"

# 2. Verifica status
git status  # Nota il "detached HEAD"

# 3. Esplora cronologia
git log --oneline  # Vedi solo commit fino a v1.0

# 4. Torna a main
git switch main
cat version.txt  # Dovrebbe dire "Version 5"
```

#### Esercizio 2: Modifiche Temporanee

```bash
# 1. Vai a v2.0
git checkout v2.0

# 2. Modifica temporanea
echo "Temporary test" >> version.txt

# 3. Testa qualcosa
cat version.txt

# 4. Scarta modifiche
git restore version.txt

# 5. Torna a main
git switch main
```

#### Esercizio 3: Commit in Detached HEAD

```bash
# 1. Vai a v1.0
git checkout v1.0

# 2. Crea nuovo file
echo "Experimental feature" > experiment.txt
git add experiment.txt
git commit -m "Add experimental feature"

# 3. Nota l'hash del commit
git rev-parse HEAD

# 4. Salva in branch
git switch -c experiment-branch

# 5. Verifica che il commit sia salvato
git log --oneline -2
```

---

## 🎯 Quiz di Autovalutazione

### Domanda 1
**Cosa succede ai commit fatti in detached HEAD se non li salvi in un branch?**

A) Vengono automaticamente aggiunti a main  
B) Rimangono accessibili per sempre  
C) Vengono eventually garbage collected  
D) Vengono persi immediatamente  

<details>
<summary>Risposta</summary>
<strong>C) Vengono eventually garbage collected</strong>

I commit rimangono accessibili tramite reflog per un periodo (default 30 giorni), poi vengono rimossi dal garbage collector.
</details>

### Domanda 2
**Quale comando usi per salvare commit da detached HEAD?**

A) `git save`  
B) `git switch -c new-branch`  
C) `git branch new-branch`  
D) `git stash`  

<details>
<summary>Risposta</summary>
<strong>B) `git switch -c new-branch`</strong>

Questo comando crea un nuovo branch dalla posizione attuale (detached HEAD) e ci cambia, salvando tutti i commit.
</details>

### Domanda 3
**È sicuro fare modifiche in detached HEAD?**

A) No, mai  
B) Sì, sempre  
C) Sì, ma solo per sperimentazione temporanea  
D) Solo se fai subito commit  

<details>
<summary>Risposta</summary>
<strong>C) Sì, ma solo per sperimentazione temporanea</strong>

Detached HEAD è perfetto per sperimentazione e testing, ma devi salvare il lavoro importante in un branch.
</details>

---

## 📋 Cheat Sheet Detached HEAD

### Entrata

```bash
git checkout <hash>        # Vai a commit specifico
git checkout HEAD~3        # Vai 3 commit indietro  
git checkout v1.0.0        # Vai a tag
```

### Orientamento

```bash
git status                 # Verifica detached HEAD
git rev-parse HEAD         # Hash attuale
git log --oneline -5       # Cronologia da qui
git reflog                 # Dove sei stato
```

### Uscita Sicura

```bash
git switch -               # Torna al branch precedente
git switch main            # Vai a main
git switch -c save-work    # Salva in nuovo branch
```

### Emergenza

```bash
git reflog                 # Trova commit persi
git checkout <hash>        # Recupera commit specifico
git switch -c recovery     # Salva immediatamente
```

---

## 📝 Riassunto

### Concetti Chiave

1. **Detached HEAD è normale** durante l'esplorazione
2. **Non è pericoloso** se usato correttamente
3. **Perfetto per sperimentazione** temporanea
4. **Sempre salvare** lavoro importante in branch
5. **Reflog tiene traccia** di tutto per recupero

### Workflow Consigliato

1. **Entra** con intenzione chiara
2. **Sperimenta** liberamente
3. **Salva** se il lavoro è utile
4. **Esci** quando finito
5. **Usa reflog** se qualcosa va storto

---

## 🔗 Navigazione del Corso

- [📑 Indice](../../README.md)
- [⬅️ Git Checkout vs Switch](./02-checkout-vs-switch.md)
- [➡️ Riferimenti e Hash](./04-riferimenti-hash.md)

---

*🎯 Prossimo: Imparerai tutti i modi per identificare e riferirsi ai commit nella cronologia Git.*
