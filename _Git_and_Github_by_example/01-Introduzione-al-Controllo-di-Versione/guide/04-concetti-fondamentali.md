# 04 - Concetti Fondamentali di Git

## 📖 Spiegazione Concettuale

Prima di iniziare ad usare Git praticamente, è fondamentale comprendere i concetti teorici su cui si basa. Questi concetti sono diversi da altri sistemi di controllo versione e comprendedli ti aiuterà ad evitare confusione nelle esercitazioni pratiche.

## 🏗️ Architettura di Git

### Le Tre Aree Principali

```
Working Directory  →  Staging Area  →  Repository
(File modificati)    (File pronti)    (Commit salvati)
```

#### 1. **Working Directory** (Cartella di Lavoro)
- Dove modifichi effettivamente i file
- Contiene la versione attuale dei file
- Può contenere file tracciati e non tracciati

#### 2. **Staging Area** (Area di Staging)
- Buffer temporaneo tra Working Directory e Repository
- Contiene i file preparati per il prossimo commit
- Permette commit selettivi

#### 3. **Repository** (Repository Git)
- Database dei commit e della storia
- Contiene tutti i metadati e gli oggetti Git
- È nella cartella `.git/`

## 📦 Gli Oggetti Git

Git memorizza tutto come oggetti di 4 tipi:

### 1. **Blob** (Binary Large Object)
```
Contenuto: Il contenuto effettivo del file
Hash SHA-1: 2cf24dba4f21d4288b9c7c6e6a31d2a
Dimensione: 342 bytes
```

### 2. **Tree** (Albero)
```
100644 blob 2cf24db   README.md
100644 blob 8ab34ef   index.html
040000 tree 9df12ac   css/
```
Rappresenta la struttura delle directory

### 3. **Commit** (Commit)  
```
tree 9df12ac4f21d4288b9c7c6e6a31d2a
parent 7ab23cd8f21d4288b9c7c6e6a31d2a
author Marco Rossi <marco@email.com>
committer Marco Rossi <marco@email.com>

Aggiunge homepage del sito
```

### 4. **Tag** (Etichetta)
```
object 7ab23cd8f21d4288b9c7c6e6a31d2a
type commit
tag v1.0.0
tagger Marco Rossi <marco@email.com>

Release versione 1.0.0
```

## 🌳 Repository e Working Directory

### Anatomia di un Repository Git

```
progetto/
├── .git/                  ← Repository Git (nascosto)
│   ├── objects/          ← Database oggetti
│   ├── refs/             ← Branch e tag
│   ├── HEAD              ← Puntatore branch corrente
│   ├── config            ← Configurazione locale
│   └── index             ← Staging area
├── README.md             ← Working Directory
├── index.html
└── css/
    └── style.css
```

### Inizializzazione Repository

Quando esegui `git init`:
1. Viene creata la cartella `.git/`
2. Git inizializza la struttura interna
3. Il repository è vuoto ma pronto all'uso

## 🔄 Commit e Hash

### Cosa Sono i Commit

Un commit è uno **snapshot completo** del progetto in un momento specifico.

```
Commit abc123def
├── Metadati
│   ├── Autore: Marco Rossi
│   ├── Data: 2024-01-15 14:30:22
│   ├── Messaggio: "Aggiunge login utente"
│   └── Parent: xyz789ghi
└── Contenuto
    ├── Snapshot completo di tutti i file
    └── Hash SHA-1 per integrità
```

### Hash SHA-1

Ogni commit ha un identificatore unico:

```bash
# Hash completo (40 caratteri)
1a2b3c4d5e6f7890abcdef1234567890abcdef12

# Hash abbreviato (primi 7 caratteri, di solito sufficienti)
1a2b3c4
```

### Caratteristiche degli Hash
- **Deterministici**: Stesso contenuto = stesso hash
- **Unici**: Probabilità di collisione praticamente zero
- **Immutabili**: Modificare un commit cambia il suo hash

## 🌿 Branch (Rami di Sviluppo)

### Concetto di Branch

Un branch è semplicemente un **puntatore mobile** a un commit specifico.

```
main:     A → B → C → D
               ↘
feature:         E → F
```

### Branch Master/Main

```bash
# Branch predefinito (nome storico: master, nuovo standard: main)
main: 1a2b3c4  ← HEAD
```

### Lightweight Branching

In Git, creare un branch significa solo:
1. Creare un nuovo puntatore a un commit
2. Non copia file (come in SVN)
3. Operazione istantanea

## 🔗 HEAD e References

### Cosa è HEAD

HEAD è un puntatore al branch corrente:

```bash
HEAD → main → 1a2b3c4 (commit)
```

### Detached HEAD

Quando HEAD punta direttamente a un commit:

```bash
HEAD → 1a2b3c4 (commit)
# Non su nessun branch!
```

### References (Refs)

Git usa references per tenere traccia di:
- **Branch**: `.git/refs/heads/main`
- **Tag**: `.git/refs/tags/v1.0`
- **Remote**: `.git/refs/remotes/origin/main`

## 🔄 Stati dei File

### I Quattro Stati Possibili

```
Untracked → Unmodified → Modified → Staged
    ↑                                  ↓
    ←←←←←←←← Committed ←←←←←←←←←←←←←←←←←
```

#### 1. **Untracked** (Non Tracciato)
- File nuovo, Git non lo conosce
- Non incluso nei commit fino al primo `git add`

#### 2. **Unmodified** (Non Modificato)  
- File tracciato, identico all'ultimo commit
- Nessuna azione necessaria

#### 3. **Modified** (Modificato)
- File tracciato ma cambiato rispetto all'ultimo commit
- Necessario staging per includerlo nel prossimo commit

#### 4. **Staged** (In Staging)
- File preparato per il prossimo commit
- Sarà incluso quando farai `git commit`

## 📈 Storia Lineare vs Non-Lineare

### Storia Lineare (Semplice)

```
A → B → C → D → E
```
Ogni commit ha un solo parent

### Storia Non-Lineare (Branch e Merge)

```
    A → B → C → F ← merge commit
         ↘     ↗
           D → E
```

Il merge commit F ha due parent: C ed E

## 🌐 Repository Locali vs Remoti

### Repository Locale
- Sul tuo computer
- Dove lavori quotidianamente
- Completo e indipendente

### Repository Remoto
- Su server (GitHub, GitLab, etc.)
- Condiviso dal team
- Sincronizzazione tramite push/pull

```
Local Repo  ←→  Remote Repo
    ↓              ↑
Working Dir    Other Developers
```

## ⚠️ Errori Concettuali Comuni

### 1. **"Git salva solo le differenze"**
❌ **Sbagliato**: Git salva snapshot completi
✅ **Realtà**: Git ottimizza internamente, ma concettualmente sono snapshot

### 2. **"I branch copiano i file"**
❌ **Sbagliato**: I branch sono solo puntatori
✅ **Realtà**: Cambio branch = cambio puntatore HEAD

### 3. **"Il commit salva sul server"**
❌ **Sbagliato**: Il commit è locale
✅ **Realtà**: Serve `git push` per inviare al server

### 4. **"Cancellare un file lo rimuove dalla storia"**
❌ **Sbagliato**: La storia è immutabile
✅ **Realtà**: Il file esiste ancora nei commit precedenti

## 💡 Best Practices Concettuali

### 1. **Pensa in Snapshots**
```bash
# Ogni commit è una "foto" completa del progetto
Commit 1: [foto del progetto]
Commit 2: [foto del progetto]
Commit 3: [foto del progetto]
```

### 2. **Usa Staging Strategicamente**
```bash
# Modifica 3 file, ma committa solo 2
git add file1.js file2.css  # Solo questi due
git commit -m "Fix styling issues"
# file3.js rimane in working directory
```

### 3. **Branch per Features**
```bash
# Un branch per ogni nuova caratteristica
main
├── feature/login
├── feature/payment
└── bugfix/header-menu
```

## 🧠 Quiz di Autovalutazione

### Domanda 1
Quali sono le tre aree principali in Git?
- A) Local, Remote, Server
- B) Working Directory, Staging Area, Repository
- C) Files, Folders, Commits  
- D) Master, Branch, Tag

<details>
<summary>Risposta</summary>
<strong>B) Working Directory, Staging Area, Repository</strong><br>
Queste sono le tre aree fondamentali del workflow Git.
</details>

### Domanda 2
Cos'è un branch in Git?
- A) Una copia di tutti i file
- B) Un puntatore mobile a un commit
- C) Una cartella separata
- D) Un file di configurazione

<details>
<summary>Risposta</summary>
<strong>B) Un puntatore mobile a un commit</strong><br>
I branch in Git sono estremamente leggeri, sono solo puntatori.
</details>

### Domanda 3
Cosa succede quando fai un commit?
- A) I file vengono salvati sul server
- B) Viene creato uno snapshot locale
- C) I file vengono copiati
- D) Il branch viene cambiato

<details>
<summary>Risposta</summary>
<strong>B) Viene creato uno snapshot locale</strong><br>
Il commit crea uno snapshot nel repository locale, non sul server.
</details>

### Domanda 4
Un file può essere in quanti stati diversi?
- A) 2 (modificato/non modificato)
- B) 3 (nuovo/modificato/cancellato)
- C) 4 (untracked/unmodified/modified/staged)
- D) 5 (incluso committed)

<details>
<summary>Risposta</summary>
<strong>C) 4 (untracked/unmodified/modified/staged)</strong><br>
Questi sono i quattro stati possibili per un file in Git.
</details>

## 🏋️ Esercizi Pratici

### Esercizio 1: Disegna il Workflow
Disegna il flusso di un file dalla creazione al commit:

```
Nuovo file → _______ → _______ → _______
             (stato)   (area)    (azione)
```

### Esercizio 2: Identifica gli Stati
Per ogni scenario, identifica lo stato del file:

1. File appena creato: ____________
2. File esistente non modificato: ____________  
3. File esistente modificato: ____________
4. File dopo `git add`: ____________

### Esercizio 3: Analizza la Storia
Data questa storia di commit:
```
A → B → C → D
     ↘     ↗
       E → F
```

- Quali commit sono parent di F? ____________
- Quanti parent ha il commit D? ____________
- È una storia lineare? ____________

### Esercizio 4: Branch Mentale
Immagina di avere:
```
main:    A → B → C
feature:      B → D → E
```

- Se HEAD punta a `feature`, su quale commit sei? ____________
- Se fai checkout di `main`, cosa succede? ____________
- I file di E sono persi? ____________

## 📖 Approfondimenti

### Documentazione Git
- [Git Internals - Pro Git Book](https://git-scm.com/book/en/v2/Git-Internals-Plumbing-and-Porcelain)
- [Git Objects Explained](https://git-scm.com/book/en/v2/Git-Internals-Git-Objects)

### Visualizzazioni Interattive
- [Learn Git Branching](https://learngitbranching.js.org/)
- [Visualizing Git](http://visualizinggit.madebyevan.com/)

### Video Spiegazioni
- [Git Internals - Linus Torvalds](https://www.youtube.com/watch?v=4XpnKHJAok8)

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)  
- [⬅️ Git vs Altri Sistemi](03-git-vs-altri.md)
- [➡️ Prossima Esercitazione](../../02-Installazione-e-Configurazione-Git/)
