# Concetti di Navigazione in Git

## 📖 Obiettivi
- Comprendere come Git gestisce la cronologia dei commit
- Imparare il concetto di HEAD e puntatori
- Capire la differenza tra navigazione e modifica
- Acquisire una visione mentale della struttura Git

## 📚 Prerequisiti
- Conoscenza base di git log
- Familiarità con i commit
- Repository con alcuni commit di esempio

## ⏱️ Durata Stimata
15-20 minuti

---

## 🗺️ La Mappa del Repository Git

### Struttura Cronologica

Git memorizza la cronologia come una **catena di commit**, dove ogni commit punta al precedente:

```
A ← B ← C ← D ← E (HEAD -> main)
│   │   │   │   │
│   │   │   │   └── Commit più recente
│   │   │   └────── Commit precedente
│   │   └────────── Altro commit
│   └────────────── Primo commit della serie
└────────────────── Commit iniziale
```

### Il Puntatore HEAD

**HEAD** è il tuo "punto di vista" attuale nel repository:

```bash
# HEAD normalmente punta al branch attuale
HEAD -> main -> [ultimo commit]

# Durante la navigazione, HEAD può puntare direttamente a un commit
HEAD -> [commit specifico]  # "detached HEAD"
```

---

## 🧭 Tipi di Navigazione

### 1. Navigazione di Lettura (Safe)

**Scopo**: Esplorare senza modificare

```bash
# Vedere il codice com'era in passato
git checkout <commit-hash>

# Tornare al presente
git checkout main
```

**Caratteristiche**:
- ✅ Non modifica la cronologia
- ✅ Reversibile al 100%
- ✅ Ideale per debugging

### 2. Navigazione con Branch (Recommended)

**Scopo**: Esplorare e potenzialmente modificare

```bash
# Creare branch da punto specifico
git checkout -b my-exploration <commit-hash>

# Lavorare liberamente
# ... modifiche e commit

# Tornare quando finito
git checkout main
```

**Caratteristiche**:
- ✅ Mantiene tutte le modifiche
- ✅ Non rischi di perdere lavoro
- ✅ Permette sperimentazione

---

## 🎯 Modi per Identificare i Commit

### 1. Hash Completi e Abbreviati

```bash
# Hash completo (40 caratteri)
git checkout 2f8a3b1c4d5e6f7g8h9i0j1k2l3m4n5o6p7q8r9s

# Hash abbreviato (primi 7+ caratteri)
git checkout 2f8a3b1c
```

### 2. Riferimenti Relativi

```bash
# Ultimo commit
git checkout HEAD

# Due commit fa
git checkout HEAD~2

# Tre commit fa
git checkout HEAD~3

# Commit padre del branch main
git checkout main~1
```

### 3. Riferimenti per Data

```bash
# Com'era ieri
git checkout 'main@{yesterday}'

# Com'era 2 giorni fa
git checkout 'main@{2.days.ago}'

# Com'era una settimana fa
git checkout 'main@{1.week.ago}'
```

### 4. Tag e Branch

```bash
# Navigare a un tag
git checkout v1.0.0

# Navigare a un branch
git checkout develop

# Navigare al primo commit di un branch
git checkout main~$(git rev-list --count main)
```

---

## 🔄 Tipi di Puntatori Git

### HEAD: Il Tuo Punto di Vista

```bash
# Dove sei ora
git rev-parse HEAD

# Cronologia di dove sei stato
git reflog

# Il commit che HEAD punta
git show HEAD
```

### Branch: Puntatori Mobili

```bash
# Dove punta un branch
git rev-parse main

# Ultimo commit di ogni branch
git branch -v

# Tutti i branch e dove puntano
git show-branch
```

### Tag: Puntatori Fissi

```bash
# Tag come snapshot fissi
git tag v1.0.0 <commit-hash>

# Navigare a tag
git checkout v1.0.0

# Vedere tutti i tag
git tag -l
```

---

## 🌳 Modello Mentale: L'Albero del Tempo

### Visualizzazione Lineare

```
Past ←────────────────────── Present
 A     B     C     D     E
 │     │     │     │     │
 └─────┴─────┴─────┴─────┴─── main
                           ↑
                         HEAD
```

### Durante la Navigazione

```
Past ←────────────────────── Present
 A     B     C     D     E
 │     │     │     │     │
 └─────┴─────┴─────┴─────┴─── main
           ↑                  
         HEAD                 
       (detached)             
```

---

## 🔍 Comandi di Orientamento

### Dove Sono Ora?

```bash
# Mostra commit attuale
git log --oneline -1

# Mostra posizione HEAD
git rev-parse HEAD

# Status comprensivo
git status

# Se sei in detached HEAD
git branch -v
```

### Come Sono Arrivato Qui?

```bash
# Cronologia completa navigazione
git reflog

# Ultime 10 posizioni HEAD
git reflog -10

# Cronologia branch specifico
git reflog show main
```

### Dove Posso Andare?

```bash
# Tutti i commit raggiungibili
git log --oneline --all

# Branch disponibili
git branch -a

# Tag disponibili
git tag -l

# Remote branch
git branch -r
```

---

## ⚡ Comandi Quick Reference

### Navigazione Base

```bash
# Vai a commit specifico
git checkout <hash>

# Vai a commit relativo
git checkout HEAD~2

# Vai a branch
git checkout <branch-name>

# Torna al branch precedente
git checkout -
```

### Orientamento

```bash
# Dove sono
git rev-parse HEAD

# Come sono arrivato qui
git reflog

# Cosa posso vedere da qui
git log --oneline -10
```

### Sicurezza

```bash
# Salva lavoro corrente
git stash

# Crea branch da posizione attuale
git checkout -b safe-point

# Torna a sicurezza
git checkout main
```

---

## 🧪 Esempio Pratico Guidato

### Setup Repository di Test

```bash
# Crea repository con cronologia
mkdir git-navigation-test
cd git-navigation-test
git init

# Crea alcuni commit
echo "Version 1" > file.txt
git add file.txt
git commit -m "Add initial version"

echo "Version 2" >> file.txt
git add file.txt
git commit -m "Update to version 2"

echo "Version 3" >> file.txt
git add file.txt
git commit -m "Update to version 3"

# Aggiungi tag
git tag v1.0 HEAD~2
git tag v2.0 HEAD~1
git tag v3.0 HEAD
```

### Esplorazione Guidata

```bash
# 1. Vedi dove sei
git log --oneline
# Dovrebbe mostrare 3 commit

# 2. Vai al primo commit
git checkout HEAD~2
# Controlla contenuto file
cat file.txt  # Dovrebbe mostrare solo "Version 1"

# 3. Vai al secondo commit
git checkout HEAD~1
cat file.txt  # Dovrebbe mostrare "Version 1" e "Version 2"

# 4. Torna al presente
git checkout main
cat file.txt  # Dovrebbe mostrare tutto

# 5. Usa i tag
git checkout v1.0
cat file.txt  # Di nuovo solo "Version 1"

# 6. Torna a main
git checkout main
```

---

## 🎯 Quiz di Autovalutazione

### Domanda 1
**Che cosa rappresenta HEAD in Git?**

A) L'ultimo commit di un repository  
B) Il tuo punto di vista attuale nel repository  
C) Il primo commit di un branch  
D) Un tipo speciale di branch  

<details>
<summary>Risposta</summary>
<strong>B) Il tuo punto di vista attuale nel repository</strong>

HEAD indica dove ti trovi attualmente nel repository. Può puntare a un branch (normale) o direttamente a un commit (detached HEAD).
</details>

### Domanda 2
**Quale comando ti dice esattamente dove sei nel repository?**

A) `git status`  
B) `git log`  
C) `git rev-parse HEAD`  
D) Tutti i precedenti  

<details>
<summary>Risposta</summary>
<strong>D) Tutti i precedenti</strong>

Tutti questi comandi forniscono informazioni sulla tua posizione, anche se in modi diversi:
- `git status`: mostra branch e stato file
- `git log`: mostra cronologia da posizione attuale  
- `git rev-parse HEAD`: mostra hash esatto del commit
</details>

### Domanda 3
**Cosa significa `HEAD~3`?**

A) Il terzo commit del repository  
B) Tre commit dopo la posizione attuale  
C) Tre commit prima della posizione attuale  
D) Il commit con hash che inizia per 3  

<details>
<summary>Risposta</summary>
<strong>C) Tre commit prima della posizione attuale</strong>

La notazione `~n` indica "n commit indietro nella cronologia lineare".
</details>

### Domanda 4
**Quale è il modo più sicuro per esplorare un commit precedente?**

A) `git checkout <hash>`  
B) `git checkout -b explore <hash>`  
C) `git reset --hard <hash>`  
D) `git revert <hash>`  

<details>
<summary>Risposta</summary>
<strong>B) `git checkout -b explore <hash>`</strong>

Creare un branch per l'esplorazione permette di fare modifiche senza rischi e mantiene organizzato il lavoro.
</details>

### Domanda 5
**Come torni rapidamente al branch precedente?**

A) `git checkout HEAD`  
B) `git checkout main`  
C) `git checkout -`  
D) `git switch main`  

<details>
<summary>Risposta</summary>
<strong>C) `git checkout -`</strong>

Il simbolo `-` è una scorciatoia che significa "torna alla posizione precedente", simile a `cd -` nella shell.
</details>

---

## 📝 Riassunto Concetti Chiave

### Punti Essenziali

1. **HEAD è il tuo punto di vista** attuale nel repository
2. **La navigazione è sicura** e non modifica la cronologia
3. **Riferimenti multipli** permettono flessibilità (hash, tag, date)
4. **Detached HEAD è normale** durante l'esplorazione
5. **Sempre sapere dove sei** e come tornare indietro

### Workflow Consigliato

1. **Salva il lavoro** (`git stash` o commit)
2. **Naviga liberamente** per esplorare
3. **Crea branch** se vuoi modificare
4. **Torna a main** quando hai finito
5. **Usa `git reflog`** se ti perdi

### Sicurezza

- ✅ La navigazione è reversibile
- ✅ `git reflog` tiene traccia di tutto
- ✅ I commit non vengono mai persi (immediatamente)
- ⚠️ Evita commit in detached HEAD senza branch

---

## 🔗 Navigazione del Corso

- [📑 Indice](../../README.md)
- [⬅️ Torna al Modulo](../README.md)
- [➡️ Git Checkout vs Switch](./02-checkout-vs-switch.md)

---

*🎯 Prossimo: Comprenderai le differenze tra `git checkout` e `git switch` per navigare in modo moderno e sicuro.*
