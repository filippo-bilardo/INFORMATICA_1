# Riferimenti e Hash: Identificare i Commit

## 📖 Obiettivi
- Padroneggiare tutti i tipi di riferimenti Git
- Comprendere hash completi e abbreviati
- Utilizzare riferimenti relativi e simbolici
- Navigare con precisione nella cronologia

## 📚 Prerequisiti
- Conoscenza di commit e cronologia Git
- Familiarità con HEAD e branch
- Comprensione di tag base

## ⏱️ Durata Stimata
20-25 minuti

---

## 🔑 Tipi di Riferimenti Git

Git offre diversi modi per identificare commit:

1. **Hash SHA-1** (completi e abbreviati)
2. **Riferimenti simbolici** (HEAD, branch, tag)
3. **Riferimenti relativi** (~, ^)
4. **Riferimenti temporali** (@{time})
5. **Riferimenti reflog** (@{n})

---

## 🔢 Hash SHA-1

### Hash Completi

Ogni commit ha un identificatore unico SHA-1 di 40 caratteri:

```bash
# Visualizza hash completi
git log --format="%H %s"
# 2f8a3b1c4d5e6f7g8h9i0j1k2l3m4n5o6p7q8r9s Initial commit
# a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0 Add feature

# Hash del commit attuale
git rev-parse HEAD
# 2f8a3b1c4d5e6f7g8h9i0j1k2l3m4n5o6p7q8r9s
```

### Hash Abbreviati

Git permette hash abbreviati (normalmente 7+ caratteri):

```bash
# Hash abbreviati nel log
git log --oneline
# 2f8a3b1c Initial commit
# a1b2c3d4 Add feature

# Verifica lunghezza hash abbreviato
git config core.abbrev
# 7 (default)

# Personalizza lunghezza
git config core.abbrev 12
git log --oneline
# 2f8a3b1c4d5e Initial commit
# a1b2c3d4e5f6 Add feature
```

### Unicità Hash

```bash
# Git verifica automaticamente unicità
git checkout 2f8a3b1c
# Se univoco, funziona

# Se ambiguo, Git chiede chiarimenti
git checkout 2f8
# error: short SHA1 2f8 is ambiguous
# hint: The candidates are:
# hint:   2f8a3b1c commit
# hint:   2f8b4c5d commit

# Usa hash più lungo per disambiguare
git checkout 2f8a3b1c
```

---

## 🎯 Riferimenti Simbolici

### HEAD: Il Puntatore Attuale

```bash
# HEAD punta sempre alla tua posizione attuale
git checkout HEAD        # Rimani dove sei
git show HEAD           # Mostra commit attuale
git rev-parse HEAD      # Hash di HEAD

# HEAD può essere relativo
git checkout HEAD~1     # Un commit indietro
git checkout HEAD^      # Commit padre
```

### Branch Names

```bash
# Branch sono puntatori mobili
git checkout main       # Vai all'ultimo commit di main
git checkout develop    # Vai all'ultimo commit di develop

# Verifica dove punta un branch
git rev-parse main      # Hash dell'ultimo commit di main
git show-branch main develop  # Confronta branch
```

### Tag Names

```bash
# Tag sono puntatori fissi
git checkout v1.0.0     # Vai al commit taggato v1.0.0
git checkout stable     # Vai al commit taggato stable

# Verifica tag
git tag -l              # Lista tutti i tag
git show v1.0.0         # Dettagli del tag
git rev-parse v1.0.0    # Hash del commit taggato
```

---

## 🧮 Riferimenti Relativi

### Tilde (~): Navigazione Lineare

La tilde indica "n commit indietro nella cronologia lineare":

```bash
# ~ significa "commit precedente"
HEAD~1   # Un commit prima di HEAD
HEAD~2   # Due commit prima di HEAD
HEAD~10  # Dieci commit prima di HEAD

# Equivalente per branch e tag
main~3   # Tre commit prima dell'ultimo commit di main
v1.0~1   # Un commit prima del tag v1.0
```

#### Visualizzazione Tilde

```
A ← B ← C ← D ← E (HEAD)
│   │   │   │   │
│   │   │   │   └── HEAD~0 (HEAD)
│   │   │   └────── HEAD~1
│   │   └────────── HEAD~2
│   └────────────── HEAD~3
└────────────────── HEAD~4
```

### Caret (^): Navigazione Parentale

Il caret indica "n-esimo genitore di un commit":

```bash
# ^ significa "primo genitore"
HEAD^    # Primo genitore di HEAD (= HEAD~1)
HEAD^2   # Secondo genitore di HEAD (per merge)
HEAD^3   # Terzo genitore (per octopus merge)

# Combinabile
HEAD~2^2 # Secondo genitore del commit 2 posizioni fa
```

#### Visualizzazione Caret (con Merge)

```
    A ← B ← C (branch1)
         ╲   ╱
          D ← E ← F (HEAD, main)
          │   │   │
          │   │   └── HEAD^1 = E (primo genitore)
          │   └────── HEAD^2 = C (secondo genitore)
          └────────── HEAD^1^1 = D
```

### Combinazioni Complesse

```bash
# Combinazioni ~ e ^
HEAD~2^2     # Secondo genitore, due commit fa
main~3^      # Primo genitore, tre commit prima di main
v1.0~1^2     # Secondo genitore del commit prima di v1.0

# Verifica con rev-parse
git rev-parse HEAD~2^2
git rev-parse main~3^
```

---

## ⏰ Riferimenti Temporali

### Date Assolute

```bash
# Commit alla data specifica
git checkout 'main@{2023-12-01}'
git checkout 'HEAD@{2023-12-01 15:30}'

# Formati supportati
git checkout 'main@{Dec 1 2023}'
git checkout 'main@{yesterday}'
git checkout 'main@{2.weeks.ago}'
```

### Date Relative

```bash
# Tempo relativo
git checkout 'main@{yesterday}'
git checkout 'main@{2.days.ago}'
git checkout 'main@{1.week.ago}'
git checkout 'main@{1.month.ago}'
git checkout 'main@{6.months.ago}'

# Ore specifiche
git checkout 'main@{2.hours.ago}'
git checkout 'main@{30.minutes.ago}'
```

---

## 📜 Riferimenti Reflog

### Reflog Basics

Reflog traccia dove è stato HEAD:

```bash
# Mostra reflog
git reflog
# abc123 HEAD@{0}: checkout: moving from main to feature
# def456 HEAD@{1}: commit: Add new feature
# ghi789 HEAD@{2}: checkout: moving from feature to main

# Naviga usando reflog
git checkout HEAD@{2}   # Vai dove eri 2 mosse fa
git checkout HEAD@{5}   # Vai dove eri 5 mosse fa
```

### Reflog Specifico per Branch

```bash
# Reflog di branch specifico
git reflog show main
git reflog show feature/auth

# Naviga nel reflog del branch
git checkout 'main@{3}'     # main 3 posizioni fa
git checkout 'feature@{1}'  # feature 1 posizione fa
```

---

## 🔍 Strumenti di Verifica

### Rev-Parse: Il Convertitore Universale

```bash
# Converte qualsiasi riferimento in hash
git rev-parse HEAD           # Hash di HEAD
git rev-parse main           # Hash di main
git rev-parse HEAD~3         # Hash 3 commit fa
git rev-parse v1.0^2         # Hash secondo genitore di v1.0

# Verifica esistenza
git rev-parse --verify HEAD~10 2>/dev/null
# Se esiste, stampa hash; se no, errore
```

### Show: Dettagli del Commit

```bash
# Mostra dettagli di qualsiasi riferimento
git show HEAD~2              # Commit 2 posizioni fa
git show main^2              # Secondo genitore di main
git show v1.0@{1.week.ago}   # v1.0 com'era una settimana fa
```

### Log con Riferimenti

```bash
# Log da riferimento specifico
git log HEAD~5..HEAD         # Ultimi 5 commit
git log main~10..main~5      # Commit da 10 a 5 posizioni fa
git log v1.0..v2.0           # Commit tra due tag
```

---

## 🎮 Esempi Pratici Avanzati

### Scenario 1: Debug Regressione

```bash
# Il bug è apparso di recente
# Test versione di ieri
git checkout 'main@{yesterday}'
make test

# Test versione di 3 giorni fa
git checkout 'main@{3.days.ago}'
make test

# Test commit specifico sospetto
git checkout abc123^         # Commit prima del sospetto
make test
```

### Scenario 2: Confronto Merge

```bash
# Commit di merge
git checkout merge-commit

# Vedi primo genitore (branch di destinazione)
git show HEAD^1

# Vedi secondo genitore (branch mergiato)
git show HEAD^2

# Confronta i due genitori
git diff HEAD^1..HEAD^2
```

### Scenario 3: Navigazione Complessa

```bash
# Trova il merge commit di una feature
git log --oneline --merges

# Vai al commit prima del merge
git checkout <merge-hash>^1

# Vai al commit della feature mergiate
git checkout <merge-hash>^2

# Vai al merge stesso
git checkout <merge-hash>
```

---

## 🧪 Laboratorio Interattivo

### Setup Repository Complesso

```bash
mkdir git-refs-lab
cd git-refs-lab
git init

# Crea cronologia lineare
for i in {1..5}; do
  echo "Line $i" >> file.txt
  git add file.txt
  git commit -m "Commit $i"
done

# Crea branch per merge
git checkout -b feature HEAD~2
echo "Feature work" >> feature.txt
git add feature.txt
git commit -m "Add feature"

# Torna a main e merge
git checkout main
git merge feature
git tag release-1.0

# Più commit su main
echo "Post-merge work" >> file.txt
git add file.txt
git commit -m "Post merge work"
```

### Esercizi con Riferimenti

#### Test 1: Hash e Abbreviazioni

```bash
# 1. Trova hash completo di HEAD
git rev-parse HEAD

# 2. Trova hash abbreviato
git rev-parse --short HEAD

# 3. Testa navigazione con hash abbreviato
git checkout $(git rev-parse --short HEAD~2)

# 4. Torna a main
git checkout main
```

#### Test 2: Riferimenti Relativi

```bash
# 1. Vai 3 commit indietro
git checkout HEAD~3
git log --oneline -1

# 2. Vai al primo genitore del merge
git checkout main
git checkout HEAD~1^1  # Se HEAD~1 è il merge

# 3. Vai al secondo genitore del merge
git checkout HEAD~1^2

# 4. Torna a main
git checkout main
```

#### Test 3: Riferimenti Temporali

```bash
# 1. Simula tempo passato (commit nel passato)
GIT_COMMITTER_DATE="2023-12-01 10:00:00" git commit --amend --no-edit

# 2. Naviga per tempo
git checkout 'main@{1.hour.ago}'

# 3. Verifica reflog
git reflog -5

# 4. Naviga con reflog
git checkout HEAD@{2}
```

---

## 📊 Tabella Riferimenti Quick Reference

| Tipo | Sintassi | Esempio | Descrizione |
|------|----------|---------|-------------|
| **Hash** | `<hash>` | `abc123` | Commit specifico |
| **Branch** | `<branch>` | `main` | Ultimo commit del branch |
| **Tag** | `<tag>` | `v1.0.0` | Commit taggato |
| **Relativo ~** | `<ref>~<n>` | `HEAD~3` | N commit indietro |
| **Relativo ^** | `<ref>^<n>` | `HEAD^2` | N-esimo genitore |
| **Temporale** | `<ref>@{<time>}` | `main@{yesterday}` | Riferimento temporale |
| **Reflog** | `<ref>@{<n>}` | `HEAD@{5}` | N posizioni nel reflog |

---

## 🎯 Casi d'Uso Comuni

### Finding Commits

```bash
# Ultimo commit prima di data
git log --until="2023-12-01" -1 --format="%H"

# Primo commit dopo data  
git log --since="2023-12-01" --reverse -1 --format="%H"

# Commit di un autore specifico
git log --author="John" -1 --format="%H"
```

### Debugging

```bash
# Quando è stato introdotto un file?
git log --follow -- path/to/file.txt

# Ultimo commit che ha toccato un file
git log -1 --format="%H" -- path/to/file.txt

# Commit che ha rimosso un file
git log --diff-filter=D --summary | grep delete
```

### Code Archaeology

```bash
# Chi ha scritto questa riga?
git blame file.txt

# Quando è cambiata questa funzione?
git log -p --follow -S "function_name" -- file.txt

# Commit che hanno cambiato questa area
git log --oneline -p -- src/components/
```

---

## 🎯 Quiz di Autovalutazione

### Domanda 1
**Qual è la differenza tra `HEAD~2` e `HEAD^2`?**

A) Sono identici  
B) `~2` va 2 commit indietro, `^2` va al secondo genitore  
C) `^2` va 2 commit indietro, `~2` va al secondo genitore  
D) Dipende dal tipo di commit  

<details>
<summary>Risposta</summary>
<strong>B) `~2` va 2 commit indietro, `^2` va al secondo genitore</strong>

`~` naviga linearmente nella cronologia, `^` seleziona genitori in commit di merge.
</details>

### Domanda 2
**Come vai al commit com'era 3 giorni fa?**

A) `git checkout HEAD~3`  
B) `git checkout 'main@{3.days.ago}'`  
C) `git checkout HEAD@{3}`  
D) `git checkout --3-days`  

<details>
<summary>Risposta</summary>
<strong>B) `git checkout 'main@{3.days.ago}'`</strong>

I riferimenti temporali usano la sintassi `@{time.ago}` per navigare nel tempo.
</details>

### Domanda 3
**Quanti caratteri servono per un hash abbreviato?**

A) Sempre 7  
B) Almeno 4  
C) Dipende dal repository  
D) Sempre 12  

<details>
<summary>Risposta</summary>
<strong>C) Dipende dal repository</strong>

Git usa automaticamente abbastanza caratteri per garantire unicità nel repository corrente.
</details>

---

## 📝 Riassunto

### Tipi di Riferimenti

1. **Hash**: Identificazione univoca e permanente
2. **Simbolici**: Branch, tag, HEAD (mobili o fissi)
3. **Relativi**: `~` per cronologia, `^` per genitori
4. **Temporali**: `@{time}` per navigazione temporale
5. **Reflog**: `@{n}` per cronologia di movimento

### Best Practices

- **Usa hash** per riferimenti precisi e permanenti
- **Usa branch/tag** per riferimenti logici
- **Usa `~`** per navigazione lineare
- **Usa `^`** per esplorare merge
- **Usa temporali** per debugging
- **Usa reflog** per recupero

---

## 🔗 Navigazione del Corso

- [📑 Indice](../../README.md)
- [⬅️ Detached HEAD State](./03-detached-head.md)
- [➡️ Navigazione Sicura](./05-navigazione-sicura.md)

---

*🛡️ Prossimo: Imparerai le tecniche per navigare in Git senza mai rischiare di perdere lavoro importante.*
