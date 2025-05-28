# Git Reset Spiegato - Il Comando Più Potente e Pericoloso

## 📖 Introduzione

`git reset` è uno dei comandi più potenti e potenzialmente pericolosi di Git. Permette di spostare il puntatore HEAD, modificare l'area di staging e la working directory. Comprendere le sue tre modalità è essenziale per ogni sviluppatore Git.

## 🎯 Obiettivi

- Comprendere profondamente le tre modalità di reset
- Visualizzare gli effetti su HEAD, staging e working directory
- Applicare reset in sicurezza su repository locali
- Distinguere quando usare reset vs altri metodi
- Padroneggiare tecniche di recupero post-reset

## 📊 I Tre Alberi di Git

Git gestisce tre "alberi" principali:

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│      HEAD       │    │   Staging Area  │    │ Working Directory│
│   (Repository)  │    │    (Index)      │    │   (File System) │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         │ git reset --soft       │ git reset --mixed     │ git reset --hard
         └───────────────────────┼───────────────────────┼─────────────────────
                                 │                       │
                         git add │                       │ editing files
                                 ▼                       ▼
                        ┌─────────────────┐    ┌─────────────────┐
                        │   Staging Area  │    │ Working Directory│
                        │    (Index)      │    │   (File System) │
                        └─────────────────┘    └─────────────────┘
```

## 🛠️ Le Tre Modalità di Reset

### 1. 🟢 `--soft` - Il Reset Gentile

**Effetto**: Sposta solo HEAD, lascia staging e working directory invariati

```bash
# Situazione prima del reset
A --- B --- C (HEAD, main)
          ↑
       ultimo commit

# Dopo git reset --soft HEAD~1
A --- B --- C
     ↑         ↑
   HEAD      modifiche in staging
```

**Esempio Pratico**:
```bash
# Setup iniziale
echo "version 1" > file.txt
git add file.txt
git commit -m "First commit"

echo "version 2" > file.txt
git add file.txt
git commit -m "Second commit"

echo "version 3" > file.txt
git add file.txt
git commit -m "Third commit"

# Reset soft: torna indietro ma mantiene le modifiche staged
git reset --soft HEAD~1

# Verifica stato
git status
# Changes to be committed:
#   modified: file.txt

git log --oneline
# solo primi due commit visibili

# Il file contiene ancora "version 3" ed è staged!
```

**Quando usare --soft**:
- Vuoi rifare l'ultimo commit con modifiche diverse
- Devi correggere il messaggio di commit
- Vuoi combinare più commit in uno solo

### 2. 🟡 `--mixed` - Il Reset Default

**Effetto**: Sposta HEAD e resetta staging, mantiene working directory

```bash
# Situazione prima del reset
A --- B --- C (HEAD, main)
          ↑
   staging + working

# Dopo git reset --mixed HEAD~1 (o solo git reset HEAD~1)
A --- B --- C
     ↑         ↑
   HEAD    modifiche in working dir (non staged)
```

**Esempio Pratico**:
```bash
# Continuando dall'esempio precedente
echo "version 4" > file.txt
git add file.txt
git commit -m "Fourth commit"

# Reset mixed (default)
git reset HEAD~1

# Verifica stato
git status
# Changes not staged for commit:
#   modified: file.txt

# Il file contiene "version 4" ma NON è staged
cat file.txt
# version 4
```

**Quando usare --mixed**:
- Vuoi unstage file ma mantenere le modifiche
- Devi riorganizzare cosa includere nel commit
- Hai aggiunto file per errore al staging

### 3. 🔴 `--hard` - Il Reset Distruttivo

**Effetto**: Sposta HEAD, resetta staging E working directory

```bash
# Situazione prima del reset
A --- B --- C (HEAD, main)
          ↑
   tutto sincronizzato

# Dopo git reset --hard HEAD~1
A --- B
     ↑
   HEAD
   
# C e tutte le modifiche sono PERSE!
```

**Esempio Pratico**:
```bash
# Setup
echo "important work" > important.txt
git add important.txt
git commit -m "Important work"

echo "more changes" >> important.txt
echo "new file" > temp.txt

# ⚠️ ATTENZIONE: Questo cancellerà tutto!
git reset --hard HEAD~1

# Verifica
git status
# working tree clean

cat important.txt
# file potrebbe non esistere più!

ls temp.txt
# ls: temp.txt: No such file or directory
```

**Quando usare --hard**:
- Vuoi tornare completamente a uno stato precedente
- Sei sicuro di non aver bisogno delle modifiche attuali
- Stai facendo cleanup di esperimenti falliti

## 🎯 Sintassi Completa e Varianti

### Forme Base
```bash
# Reset alle varie posizioni
git reset HEAD~1          # Un commit indietro (mixed)
git reset HEAD~3          # Tre commit indietro
git reset abc123          # A commit specifico
git reset origin/main     # All'ultimo commit del remote

# Con modalità esplicite
git reset --soft HEAD~1   # Gentile
git reset --mixed HEAD~1  # Default
git reset --hard HEAD~1   # Distruttivo
```

### Reset di File Specifici
```bash
# Reset solo file specifici (sempre in modalità mixed)
git reset HEAD file.txt           # Unstage un file
git reset HEAD~1 -- file.txt     # Reset file a versione precedente
git reset abc123 -- src/         # Reset directory a commit specifico
```

### Reset con Path
```bash
# Reset di directory
git reset HEAD -- src/           # Unstage tutti i file in src/
git reset --hard HEAD -- .       # Reset tutto (equivale a git reset --hard HEAD)
```

## 📊 Confronto delle Modalità

| Modalità | HEAD | Staging | Working Dir | Sicurezza | Uso Tipico |
|----------|------|---------|-------------|-----------|------------|
| `--soft` | ✅ | ❌ | ❌ | 🟢 Sicuro | Rifare commit |
| `--mixed` | ✅ | ✅ | ❌ | 🟡 Moderato | Unstage file |
| `--hard` | ✅ | ✅ | ✅ | 🔴 Pericoloso | Reset completo |

## 🔧 Scenari Avanzati

### Scenario 1: Correggere Messaggio di Commit
```bash
# Ho fatto un commit con messaggio sbagliato
git commit -m "fix bug"  # Doveva essere "Fix authentication bug"

# Soluzione con reset soft
git reset --soft HEAD~1
git commit -m "Fix authentication bug"

# Alternativa: git commit --amend (più semplice se è l'ultimo commit)
```

### Scenario 2: Combinare Commit
```bash
# Ho fatto 3 commit piccoli che voglio combinare
git log --oneline
# abc123 Fix typo
# def456 Add documentation  
# ghi789 Implement feature

# Combino gli ultimi 3 commit
git reset --soft HEAD~3
git commit -m "Implement feature with documentation"
```

### Scenario 3: Unstage File Selettivi
```bash
# Ho aggiunto troppi file
git add .
git status
# staged: important.txt, temp.txt, debug.log, config.txt

# Rimuovo solo alcuni file dal staging
git reset HEAD temp.txt debug.log

# Ora solo important.txt e config.txt sono staged
```

### Scenario 4: Recovery da Hard Reset
```bash
# Ho fatto un reset --hard per errore!
git reset --hard HEAD~3  # OOPS!

# Recupero usando reflog
git reflog
# abc123 HEAD@{0}: reset: moving to HEAD~3
# def456 HEAD@{1}: commit: My important work
# ...

# Torno al commit perso
git reset --hard HEAD@{1}  # o git reset --hard def456
echo "✅ Recuperato!"
```

## ⚠️ Principi di Sicurezza

### Regole d'Oro per Reset

1. **MAI reset --hard su repository condivisi**
```bash
# ❌ PERICOLOSO se altri hanno questo commit
git reset --hard HEAD~1
git push --force  # Rovina il lavoro degli altri!

# ✅ SICURO: usa revert invece
git revert HEAD
git push  # Sicuro per tutti
```

2. **Sempre backup prima di --hard**
```bash
# Crea branch di backup
git branch backup-$(date +%Y%m%d-%H%M%S)
git reset --hard HEAD~1
```

3. **Verifica lo stato prima del reset**
```bash
# Controlla cosa stai per perdere
git status
git log --oneline -5
git diff HEAD~1

# Poi procedi
git reset --hard HEAD~1
```

### Script di Sicurezza
```bash
#!/bin/bash
# safe-reset.sh - Reset con backup automatico

if [ $# -eq 0 ]; then
    echo "Uso: safe-reset.sh <modalità> <target>"
    echo "Esempio: safe-reset.sh --hard HEAD~1"
    exit 1
fi

# Crea backup
backup_branch="backup-$(date +%Y%m%d-%H%M%S)"
git branch "$backup_branch"
echo "🛡️  Backup creato: $backup_branch"

# Esegui reset
git reset "$@"
echo "✅ Reset completato"
echo "💡 Per annullare: git reset --hard $backup_branch"
```

## 🔍 Debug e Troubleshooting

### Visualizzare Effetti Prima del Reset
```bash
# Vedi cosa cambierà
git show HEAD~1                    # Contenuto commit target
git diff HEAD~1                    # Differenze
git log --oneline HEAD~1..HEAD    # Commit che verranno "persi"

# Simula reset senza eseguirlo
git show HEAD~1:file.txt           # Come sarà il file dopo reset
```

### Comandi di Emergenza
```bash
# Il tuo salvavita: reflog
git reflog --all

# Recupera commit specifico
git reset --hard <hash-da-reflog>

# Vedi cronologia dettagliata
git log --graph --all --decorate --oneline

# Cerca commit persi
git fsck --lost-found
```

## 🎓 Esercizi Pratici

### Esercizio 1: Le Tre Modalità
```bash
# Setup
mkdir reset-test && cd reset-test
git init

echo "V1" > file.txt
git add file.txt
git commit -m "V1"

echo "V2" > file.txt
git add file.txt
git commit -m "V2"

echo "V3" > file.txt
git add file.txt
git commit -m "V3"

# Prova ogni modalità e osserva gli effetti:
# 1. git reset --soft HEAD~1
# 2. git reset --mixed HEAD~1  
# 3. git reset --hard HEAD~1
```

### Esercizio 2: Recovery da Errore
```bash
# Simula errore
git reset --hard HEAD~2  # "Oops, ho perso commit!"

# Compito: Recupera usando reflog
# Hint: git reflog, poi git reset --hard <hash>
```

### Esercizio 3: Unstage Selettivo
```bash
# Setup
echo "A" > a.txt
echo "B" > b.txt  
echo "C" > c.txt
git add *.txt

# Compito: Rimuovi solo b.txt dal staging
# Verifica che a.txt e c.txt rimangano staged
```

## 📈 Pattern Avanzati

### Reset Interattivo
```bash
# Reset con selezione interattiva (Git 2.25+)
git reset --patch HEAD~1

# Ti permette di scegliere cosa resettare chunk per chunk
```

### Reset con Conservazione
```bash
# Reset che conserva modifiche in stash
git stash
git reset --hard HEAD~1
git stash pop  # Riapplica modifiche se necessario
```

### Reset Condizionale
```bash
# Script per reset sicuro
#!/bin/bash
if git diff --quiet && git diff --cached --quiet; then
    git reset --hard HEAD~1
    echo "Reset pulito eseguito"
else
    echo "⚠️  Ci sono modifiche non committate!"
    echo "Esegui 'git stash' prima del reset"
fi
```

## 🔗 Integrazione con Altri Comandi

### Reset + Rebase
```bash
# Combina reset con rebase per riorganizzare cronologia
git reset --soft HEAD~3
git commit -m "Combined commit"
git rebase -i HEAD~1  # Per ulteriori modifiche
```

### Reset + Cherry-pick
```bash
# Reset poi riapplica solo alcuni commit
git log --oneline  # Nota i commit che vuoi mantenere
git reset --hard HEAD~5
git cherry-pick abc123 def456  # Riapplica solo questi
```

## 📚 Cheat Sheet

### Reset Veloce
```bash
# Unstage tutto
git reset

# Unstage file specifico
git reset HEAD file.txt

# Torna a commit precedente (mantieni modifiche)
git reset HEAD~1

# Torna a commit precedente (cancella tutto)
git reset --hard HEAD~1

# Reset a commit specifico
git reset abc123

# Reset a remote branch
git reset --hard origin/main
```

### Alias Utili
```bash
git config --global alias.undo 'reset --soft HEAD~1'
git config --global alias.unstage 'reset HEAD'
git config --global alias.discard 'reset --hard HEAD'
git config --global alias.back 'reset --hard HEAD~1'
```

## 🔄 Prossimi Passi

Ora che comprendi `git reset`, è tempo di esplorare:
- [04 - Git Revert vs Reset](./04-revert-vs-reset.md)
- [05 - Modificare Commit (Amend)](./05-modificare-commit.md)
- [06 - Recupero File](./06-recupero-file.md)

---

**Ricorda**: `git reset` è potente ma pericoloso. Inizia sempre con `--soft`, usa `--mixed` per staging, e `--hard` solo quando sei sicuro. Il reflog è il tuo migliore amico per il recovery!
