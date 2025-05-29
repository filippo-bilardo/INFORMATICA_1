# 04 - Struttura ad Albero Git

## 📖 Spiegazione Concettuale

Git organizza la cronologia dei commit come una **struttura ad albero diretta aciclica** (DAG - Directed Acyclic Graph). Comprendere questa struttura è fondamentale per padroneggiare il branching e il merging.

### Visualizzazione della Struttura
```
      A---B---C---D---E  (main)
           \
            F---G---H    (feature)
                 \
                  I---J  (sub-feature)
```

## 🌳 Anatomia dell'Albero Git

### Nodi e Archi
- **Nodi**: Commit individuali (snapshot del codice)
- **Archi**: Relazioni parent-child tra commit
- **Radice**: Commit iniziale
- **Foglie**: Branch attivi (HEAD dei branch)

### Rappresentazione Interna
```bash
# Ogni commit ha un identificatore unico (SHA-1)
commit a1b2c3d4...
Author: Developer <dev@example.com>
Date: Mon Dec 25 10:00:00 2023 +0100
Parent: f5e6d7c8...

    Add user authentication feature
```

## 🔍 Visualizzazione Pratica

### Comando git log con Grafico
```bash
# Visualizzazione base
git log --oneline --graph --all

# Output esempio:
* d4e5f6g (HEAD -> main) Merge feature branch
|\
| * c3d4e5f (feature) Add validation
| * b2c3d4e Add form handling
|/
* a1b2c3d Initial commit
```

### Visualizzazione Dettagliata
```bash
# Con più informazioni
git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --all

# Output esempio:
* d4e5f6g - (HEAD -> main) Merge feature branch (2 hours ago) <John Doe>
|\
| * c3d4e5f - (feature) Add validation (3 hours ago) <Jane Smith>
| * b2c3d4e - Add form handling (4 hours ago) <Jane Smith>
|/
* a1b2c3d - Initial commit (1 day ago) <John Doe>
```

## 🎭 Tipi di Nodi nell'Albero

### 1. **Commit Normali**
```
A---B---C
```
- Un parent
- Progressione lineare
- Sviluppo sequenziale

### 2. **Merge Commits**
```
A---B---D---E
     \   /
      C-/
```
- Due o più parent
- Uniscono linee di sviluppo
- Conservano la storia parallela

### 3. **Commit Iniziale**
```
A
```
- Nessun parent
- Root del repository
- Primo commit nel progetto

## 🔧 Comandi per Navigare l'Albero

### Esplorare la Storia
```bash
# Mostra tutti i branch
git log --oneline --graph --all --decorate

# Storia di un branch specifico
git log --oneline feature-branch

# Commit raggungibili da un punto
git log --oneline main..feature-branch

# Differenze tra branch
git log --oneline --left-right main...feature-branch
```

### Ispezionare Commit Specifici
```bash
# Dettagli di un commit
git show a1b2c3d

# File modificati in un commit
git show --name-only a1b2c3d

# Differenze introdotte
git show --stat a1b2c3d
```

### Trovare Relazioni
```bash
# Parent di un commit
git show a1b2c3d^

# Nonno (parent del parent)
git show a1b2c3d^^

# Commit figli
git log --ancestry-path a1b2c3d..HEAD
```

## 💡 Casi d'Uso Pratici

### Scenario 1: Analisi Feature Branch
```bash
# Situazione: vuoi vedere cosa ha aggiunto un feature branch
git log --oneline main..feature-login

# Output:
c3d4e5f Add password validation
b2c3d4e Add login form
a1b2c3d Add user model

# Vedere le differenze complete
git diff main...feature-login
```

### Scenario 2: Debugging
```bash
# Situazione: bug introdotto, trova quando
git bisect start
git bisect bad HEAD                  # Commit corrente ha bug
git bisect good v1.0.0              # Versione 1.0.0 era ok
# Git ti guida attraverso l'albero binario

# Trova chi ha modificato un file
git log --follow --patch filename.js
```

### Scenario 3: Cleanup Storia
```bash
# Situazione: branch con troppi commit piccoli
git log --oneline feature-messy

# Output disordinato:
f6g7h8i Fix typo
e5f6g7h Fix another typo  
d4e5f6g WIP: still working
c3d4e5f Actually add the feature
b2c3d4e Add feature (not working)

# Soluzione: interactive rebase per pulire
git rebase -i main
```

## 🌊 Pattern di Branching Comuni

### 1. **Linear History**
```
A---B---C---D---E  (main)
```
- Sviluppo sequenziale
- Semplice da seguire
- Limitato per team

### 2. **Feature Branches**
```
      A---B---E---F  (main)
           \ /
            C---D    (feature)
```
- Branch per funzionalità
- Merge quando completo
- Storia parallela preservata

### 3. **Git Flow**
```
A---B---E---G---I  (main)
     \   \ /   /
      C---D---F    (develop)
           \
            H      (feature)
```
- Branch multipli organizzati
- Workflow strutturato
- Gestione release complessa

## ⚠️ Errori Comuni

### 1. **Confusione Parent-Child**
```bash
# ❌ ERRORE: confondere direzione dell'albero
git show HEAD^    # Parent del commit corrente (corretto)
git show HEAD~1   # Stesso risultato (notazione alternativa)

# Non esiste il "child" diretto di un commit
```

### 2. **Merge vs Rebase Storia**
```bash
# Storia con merge (preserva branching):
A---B---D---E  (main)
     \ /
      C        (feature, merged)

# Storia con rebase (lineare):
A---B---C---D---E  (main, feature rebased)
```

### 3. **Branch Dangling**
```bash
# ❌ PROBLEMA: branch non referenziato diventa inaccessibile
git checkout main
git branch -D feature-important    # Elimina branch senza merge!

# ✅ SOLUZIONE: recovery tramite reflog
git reflog                         # Trova SHA del commit perso
git checkout -b recovered-feature a1b2c3d
```

## 🎯 Best Practices per Struttura Pulita

### 1. **Commit Atomici**
```bash
# ✅ Un commit = una modifica logica
git commit -m "Add user authentication"
git commit -m "Fix login validation bug"

# ❌ Evita commit misti
git commit -m "Add feature, fix bug, update docs"
```

### 2. **Branch di Breve Durata**
```bash
# ✅ Feature branch focalizzato
feature-user-login (5 commits, 2 giorni)

# ❌ Branch che diverge troppo
feature-everything (47 commits, 3 settimane)
```

### 3. **Merge Strategy Consistente**
```bash
# Per team: decide una strategia e mantienila
git merge --no-ff feature-branch    # Preserva branch history
# OPPURE
git rebase feature-branch           # Storia lineare
git merge feature-branch
```

## 🧪 Quiz di Autovalutazione

### Domanda 1
Cos'è un DAG nel contesto di Git?

**A)** Un tipo di commit speciale  
**B)** Directed Acyclic Graph - la struttura dell'albero Git  
**C)** Un comando per visualizzare branch  
**D)** Un file di configurazione  

<details>
<summary>Risposta</summary>
**B)** Directed Acyclic Graph - Git organizza i commit in questa struttura matematica.
</details>

### Domanda 2
Quanti parent ha un merge commit?

**A)** Sempre uno  
**B)** Sempre due  
**C)** Due o più  
**D)** Dipende dal tipo di merge  

<details>
<summary>Risposta</summary>
**C)** Due o più - Un merge commit unisce almeno due linee di sviluppo.
</details>

### Domanda 3
Come vedi i commit del branch "feature" che non sono in "main"?

**A)** `git log feature`  
**B)** `git log main..feature`  
**C)** `git log feature..main`  
**D)** `git diff main feature`  

<details>
<summary>Risposta</summary>
**B)** `git log main..feature` - Mostra commit raggiungibili da feature ma non da main.
</details>

### Domanda 4
Qual è il parent del commit corrente?

**A)** `HEAD^`  
**B)** `HEAD~1`  
**C)** Entrambi A e B  
**D)** `HEAD+1`  

<details>
<summary>Risposta</summary>
**C)** Entrambi A e B - Sono notazioni equivalenti per il parent del commit corrente.
</details>

## 💻 Esercizi Pratici

### Esercizio 1: Visualizzazione Albero
1. Crea un repository con struttura branched:
   - main: 3 commit
   - feature: branch da main, 2 commit
   - hotfix: branch da main, 1 commit
2. Usa `git log --graph --all` per visualizzare l'albero
3. Sperimenta con diverse opzioni di formattazione

### Esercizio 2: Navigazione Storia
1. In un repository esistente:
2. Trova il parent del commit corrente
3. Trova il terzo commit precedente
4. Lista tutti i commit di un branch specifico
5. Trova differenze tra due branch

### Esercizio 3: Analisi Merge
1. Crea un merge commit unendo due branch
2. Esamina il merge commit con `git show`
3. Verifica che abbia due parent
4. Confronta con un commit normale

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [05 - HEAD e Puntatori](./05-head-puntatori.md)  
- **Guida precedente**: [03 - Cos'è un Branch](./03-cos-e-branch.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 03-Cos-è-Branch](./03-cos-e-branch.md)
- [➡️ 05-HEAD-e-Puntatori](./05-head-puntatori.md)
