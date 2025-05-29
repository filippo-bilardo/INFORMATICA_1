# Le Tre Aree di Git: Working Directory, Staging Area e Repository

## 🎯 Obiettivi di Apprendimento
- Comprendere l'architettura a tre aree di Git
- Distinguere chiaramente tra Working Directory, Staging Area e Repository
- Visualizzare il flusso di dati tra le tre aree
- Padroneggiare i comandi per muovere file tra le aree

## 📐 Architettura Git: Le Tre Aree Fondamentali

Git organizza il lavoro in **tre aree distinte**, ognuna con un ruolo specifico nel controllo di versione:

```
┌─────────────────────┐    git add     ┌─────────────────────┐    git commit    ┌─────────────────────┐
│                     │ ────────────▶  │                     │ ──────────────▶  │                     │
│   Working Directory │                │    Staging Area     │                  │     Repository      │
│   (Working Tree)    │ ◀────────────  │     (Index)         │ ◀──────────────  │     (.git)          │
│                     │  git restore   │                     │   git restore    │                     │
└─────────────────────┘                └─────────────────────┘    --staged      └─────────────────────┘
```

## 🏗️ Area 1: Working Directory (Working Tree)

### Definizione
La **Working Directory** è la cartella del progetto dove lavori quotidianamente. Contiene:
- File del progetto visibili nel file system
- Sottocartelle e struttura del progetto
- File modificati, nuovi o eliminati

### Caratteristiche
- **Visibile**: Tutti i file sono accessibili normalmente
- **Modificabile**: Puoi editare, creare, eliminare file
- **Temporanea**: Le modifiche non sono permanenti fino al commit

### Esempio Pratico
```bash
# Nella working directory
ls -la
# Vedi: index.html, style.css, script.js, README.md

# Modifichi un file
echo "Nuova funzionalità" >> script.js

# Il file è cambiato nella working directory
git status
# modified: script.js
```

### Stati dei File nella Working Directory
- **Untracked**: File nuovi mai aggiunti a Git
- **Modified**: File tracciati che sono stati modificati
- **Deleted**: File tracciati che sono stati eliminati

## 🎭 Area 2: Staging Area (Index)

### Definizione
La **Staging Area** (o Index) è un'area intermedia dove prepari le modifiche per il prossimo commit:
- **Buffer temporaneo** tra working directory e repository
- **Snapshot preparatorio** di come sarà il prossimo commit
- **Area di controllo** per commit precisi e atomici

### Caratteristiche
- **Invisibile**: Non vedi direttamente i file nella staging area
- **Controllata**: Solo i file che aggiungi esplicitamente
- **Flessibile**: Puoi aggiungere/rimuovere file prima del commit

### Funzioni Principali
1. **Selezione**: Scegli esattamente cosa committare
2. **Preparazione**: Crea uno snapshot delle modifiche
3. **Revisione**: Controlli cosa sarà incluso nel commit

### Visualizzazione della Staging Area
```bash
# Vedere cosa è in staging
git status
git diff --cached     # Differenze tra staging e ultimo commit
git diff --staged     # Alternativa equivalente

# Vedere i file in staging
git ls-files --stage
```

## 🏛️ Area 3: Repository (.git directory)

### Definizione
Il **Repository** è dove Git salva permanentemente la cronologia del progetto:
- **Database di commit**: Tutti i commit della cronologia
- **Metadati**: Informazioni su branch, tag, remote
- **Storia completa**: Ogni versione mai committata

### Caratteristiche
- **Permanente**: I commit sono salvati definitivamente
- **Immutabile**: I commit non cambiano (hash SHA-1)
- **Completo**: Contiene tutta la storia del progetto

### Contenuto del Repository
- **Oggetti**: Commit, tree, blob
- **Referenze**: Branch, tag, HEAD
- **Configurazione**: Impostazioni locali del repository

## 🔄 Flusso di Lavoro tra le Tre Aree

### 1. Modifiche → Staging (git add)
```bash
# File modificato nella working directory
echo "console.log('Hello');" > app.js

# Sposta nella staging area
git add app.js

# Verifica il movimento
git status
# Changes to be committed:
#   new file: app.js
```

### 2. Staging → Repository (git commit)
```bash
# Dalla staging area al repository
git commit -m "Add app.js with hello function"

# Verifica il commit
git log --oneline -1
# abc1234 Add app.js with hello function
```

### 3. Repository → Working Directory (git checkout/restore)
```bash
# Ripristina file dalla repository alla working directory
git restore app.js

# O da un commit specifico
git restore --source=HEAD~1 app.js
```

### 4. Staging → Working Directory (git restore --staged)
```bash
# Rimuovi file dalla staging area (ma mantieni modifiche)
git restore --staged app.js

# Verifica
git status
# Changes not staged for commit:
#   modified: app.js
```

## 📊 Visualizzazione dello Stato delle Aree

### Comando Diagnostico Completo
```bash
# Status completo
git status

# Differenze tra aree
git diff                    # Working Directory vs Staging
git diff --cached          # Staging vs Repository
git diff HEAD               # Working Directory vs Repository
```

### Esempio di Output Interpretato
```bash
$ git status
On branch main
Changes to be committed:          # ← Staging Area
  modified:   README.md
  new file:   feature.js

Changes not staged for commit:    # ← Working Directory (modifiche non in staging)
  modified:   style.css
  deleted:    old-file.txt

Untracked files:                  # ← Working Directory (file nuovi)
  temp.log
  new-component.js
```

## 🎨 Rappresentazione Visuale delle Tre Aree

### Scenario Completo
```
Working Directory     │    Staging Area      │     Repository
─────────────────     │    ─────────────     │     ─────────────
📄 README.md (mod)    │    📄 README.md      │     📄 README.md
📄 style.css (mod)    │                      │     📄 style.css
📄 app.js (new)       │    📄 feature.js     │     📄 script.js
📄 feature.js         │                      │     
🗑️ old-file.txt (del) │                      │     📄 old-file.txt
```

### Legenda degli Stati
- **(mod)**: File modificato
- **(new)**: File nuovo
- **(del)**: File eliminato
- **Presente senza nota**: File non modificato

## 🔧 Comandi per Gestire le Tre Aree

### Aggiungere alla Staging Area
```bash
git add <file>              # Aggiungi file specifico
git add <directory>         # Aggiungi directory
git add .                   # Aggiungi tutto nella directory corrente
git add -A                  # Aggiungi tutto nel repository
git add *.js                # Aggiungi tutti i file .js
git add -p                  # Aggiungi interattivamente (pezzi)
```

### Rimuovere dalla Staging Area
```bash
git restore --staged <file>     # Nuovo comando (Git 2.23+)
git reset HEAD <file>           # Comando tradizionale
git reset                       # Rimuovi tutto dalla staging
```

### Confrontare le Aree
```bash
git diff                        # Working vs Staging
git diff --staged              # Staging vs Repository
git diff HEAD                  # Working vs Repository
git diff HEAD~1                # Working vs Commit precedente
```

## 🧪 Laboratorio Pratico

### Esercizio: Simulazione delle Tre Aree
```bash
# 1. Setup iniziale
mkdir three-areas-lab
cd three-areas-lab
git init

# 2. Crea file base
echo "Version 1" > file.txt
git add file.txt
git commit -m "Initial commit"

# 3. Modifica e osserva le aree
echo "Version 2" > file.txt    # Working Directory
git add file.txt               # Staging Area
echo "Version 3" > file.txt    # Working Directory nuovamente

# 4. Analizza le tre versioni
git diff file.txt              # Working vs Staging
git diff --staged file.txt     # Staging vs Repository
git diff HEAD file.txt         # Working vs Repository

# 5. Visualizza contenuto delle aree
cat file.txt                   # Working Directory: "Version 3"
git show :file.txt             # Staging Area: "Version 2"
git show HEAD:file.txt         # Repository: "Version 1"
```

## 🎯 Best Practices per le Tre Aree

### 1. Working Directory
- Mantieni la directory pulita
- Elimina file temporanei regolarmente
- Usa .gitignore per file che non devono essere tracciati

### 2. Staging Area
- Aggiungi solo modifiche correlate
- Rivedi sempre prima di committare
- Usa staging interattivo per commit precisi

### 3. Repository
- Commit atomici e ben descritti
- Cronologia pulita e lineare
- Non modificare commit pubblici

## 🔍 Troubleshooting Comune

### Problema: "File in staging non voluto"
```bash
# Rimuovi dalla staging area
git restore --staged unwanted-file.txt
```

### Problema: "Perso modifiche nella working directory"
```bash
# Recupera dall'ultimo commit
git restore lost-file.txt

# Recupera da un commit specifico
git restore --source=abc1234 lost-file.txt
```

### Problema: "Non capisco dove sono le mie modifiche"
```bash
# Diagnostica completa
git status
git diff                    # Working vs Staging
git diff --staged          # Staging vs Repository
```

## 📚 Concetti Chiave da Ricordare

1. **Tre aree distinte**: Working Directory, Staging Area, Repository
2. **Flusso unidirezionale**: Working → Staging → Repository
3. **Controllo granulare**: Scegli esattamente cosa committare
4. **Staging come preparazione**: Rivedi prima di rendere permanente
5. **Repository come storia**: Ogni commit è una snapshot permanente

## 🔗 Collegamenti e Approfondimenti

### Link Interni
- [📖 Concetto Staging](./01-concetto-staging.md) - Introduzione alla staging area
- [📖 Git Add Avanzato](./03-git-add-avanzato.md) - Comandi avanzati per staging
- [📖 Git Reset Staging](./04-git-reset-staging.md) - Gestione avanzata staging area

### Comandi Essenziali Correlati
- `git status` - Stato delle tre aree
- `git add` - Working → Staging
- `git commit` - Staging → Repository
- `git restore` - Movimento tra aree
- `git diff` - Confronto tra aree

---

> **💡 Suggerimento Professionale**: Visualizza sempre le tre aree come spazi fisici separati. Questo modello mentale ti aiuterà a capire esattamente dove si trovano le tue modifiche e come spostarle strategicamente.
