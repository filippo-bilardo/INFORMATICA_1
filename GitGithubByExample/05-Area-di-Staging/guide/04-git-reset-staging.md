# Git Reset per Staging: Gestione Avanzata dell'Area di Staging

## 🎯 Obiettivi di Apprendimento
- Padroneggiare `git reset` per gestire la staging area
- Distinguere tra reset --soft, --mixed e --hard
- Imparare tecniche di unstaging sicure e precise
- Gestire scenari complessi di correzione staging

## 🔄 Introduzione a Git Reset per Staging

Git Reset è uno strumento potente per **spostare il puntatore HEAD** e **gestire il contenuto delle tre aree**. Per la staging area, ci concentriamo principalmente sui reset "soft" e "mixed".

### Richiamo: Unstaging Base
```bash
# Comando moderno (Git 2.23+)
git restore --staged <file>

# Comando tradizionale (sempre funzionante)
git reset HEAD <file>
```

## 🎛️ Le Tre Modalità di Git Reset

### Panoramica delle Modalità
```
┌─────────────────────────────────────────────────────────────────┐
│                    Git Reset Modes                             │
├─────────────────────────────────────────────────────────────────┤
│ --soft   │ Sposta HEAD        │ Mantiene Staging │ Mantiene Working │
│ --mixed  │ Sposta HEAD        │ Reset Staging    │ Mantiene Working │
│ --hard   │ Sposta HEAD        │ Reset Staging    │ Reset Working    │
└─────────────────────────────────────────────────────────────────┘
```

### Visualizzazione Modalità Reset
```
Stato Iniziale:
HEAD → Commit C    Staging Area: file.txt    Working Directory: file.txt (modified)

git reset --soft HEAD~1:
HEAD → Commit B    Staging Area: file.txt    Working Directory: file.txt (modified)

git reset --mixed HEAD~1:
HEAD → Commit B    Staging Area: vuota       Working Directory: file.txt (modified)

git reset --hard HEAD~1:
HEAD → Commit B    Staging Area: vuota       Working Directory: file.txt (originale)
```

## 🕶️ Reset --soft: Unstaging con Preservazione

### Comportamento
- **Sposta HEAD** al commit specificato
- **Mantiene staging area** inalterata
- **Mantiene working directory** inalterata
- **Risultato**: Modifiche pronte per re-commit

### Casi d'Uso Principali
```bash
# 1. Correggere l'ultimo commit message
git reset --soft HEAD~1
git commit -m "Nuovo messaggio corretto"

# 2. Dividere un commit in più commit
git reset --soft HEAD~1
# Ora tutte le modifiche del commit sono in staging
git add parte1.js
git commit -m "Parte 1: implementazione base"
git add parte2.js  
git commit -m "Parte 2: ottimizzazioni"

# 3. Aggiungere file dimenticati all'ultimo commit
git reset --soft HEAD~1
git add file-dimenticato.js
git commit -m "Commit completo con tutti i file"
```

### Esempio Pratico: Splitting di Commit
```bash
# Scenario: Commit troppo grande da dividere
git log --oneline -1
# abc1234 Add user auth and profile features

# Reset soft per recuperare le modifiche
git reset --soft HEAD~1

# Ora tutto è in staging, dividiamo
git status
# Changes to be committed:
#   new file: auth/login.js
#   new file: auth/register.js  
#   new file: profile/edit.js
#   new file: profile/view.js

# Primo commit: solo auth
git restore --staged profile/
git commit -m "feat: add user authentication system"

# Secondo commit: solo profile
git add profile/
git commit -m "feat: add user profile management"
```

## 🎯 Reset --mixed: La Modalità Predefinita

### Comportamento
- **Sposta HEAD** al commit specificato
- **Reset staging area** (svuota l'index)
- **Mantiene working directory** inalterata
- **Risultato**: Modifiche tornano in working directory (untracked per staging)

### Casi d'Uso Principali
```bash
# 1. Unstaging completo (modalità predefinita)
git reset HEAD~1          # Equivale a git reset --mixed HEAD~1

# 2. Unstaging di file specifici
git reset HEAD file.txt   # Rimuove file.txt dalla staging

# 3. Tornare indietro di N commit mantenendo le modifiche
git reset HEAD~3          # Torna indietro di 3 commit, modifiche in working dir
```

### Esempio Pratico: Staging Cleanup
```bash
# Scenario: Staging disordinato da pulire
git status
# Changes to be committed:
#   new file: feature.js
#   new file: debug.log
#   new file: temp.txt
#   modified: important.js

# Reset staging per riorganizzare
git reset HEAD

# Ora tutto è in working directory, ri-staging selettivo
git add feature.js important.js
git commit -m "feat: implement new feature with improvements"

# Pulisci file temporanei
rm debug.log temp.txt
```

## ⚠️ Reset --hard: Uso con Estrema Cautela

### Comportamento
- **Sposta HEAD** al commit specificato
- **Reset staging area** (svuota l'index)
- **Reset working directory** (perde modifiche non committate)
- **ATTENZIONE**: Può causare perdita di dati!

### Quando Usare (Raramente!)
```bash
# 1. Abbandono completo delle modifiche locali
git reset --hard HEAD     # Torna all'ultimo commit, perde tutto

# 2. Sincronizzazione completa con remote
git fetch origin
git reset --hard origin/main  # ATTENZIONE: Perde tutto il lavoro locale

# 3. Emergenza: cancellare tutto e ricominciare
git reset --hard HEAD~1   # Torna indietro di 1 commit, perde tutto
```

### ⚠️ Protezioni Prima di --hard
```bash
# SEMPRE fare backup prima di --hard
git stash push -m "Backup before hard reset"
# oppure
git branch backup-$(date +%Y%m%d-%H%M%S)

# Poi eventualmente
git reset --hard <target>

# Per recuperare se necessario
git stash pop
# oppure
git checkout backup-<timestamp>
```

## 🎨 Reset Selettivo: File Specifici

### Reset di File Singoli
```bash
# Unstaging di file specifico (mixed mode)
git reset HEAD file.txt

# Equivalente moderno
git restore --staged file.txt

# Reset di directory specifica
git reset HEAD src/components/

# Reset con pattern
git reset HEAD *.js
```

### Reset Parziale con Path
```bash
# Reset di path specifici a commit precedente
git reset HEAD~2 -- src/config/
git reset abc1234 -- package.json

# Questo modifica solo staging area, non working directory
```

## 🔧 Reset con Riferimenti Avanzati

### Reset con Hash di Commit
```bash
# Reset a commit specifico
git reset --mixed abc1234

# Reset relativo a HEAD
git reset HEAD~3         # 3 commit fa
git reset HEAD^^^        # Equivalente a HEAD~3
git reset HEAD@{2}       # Reflog notation
```

### Reset con Branch e Tag
```bash
# Reset a branch
git reset origin/main
git reset --hard feature-branch

# Reset a tag
git reset --soft v1.2.0
git reset v1.1.0         # mixed mode
```

## 🔍 Verificare l'Effetto dei Reset

### Comandi di Diagnostica
```bash
# Prima del reset
git status
git log --oneline -5
git diff --cached

# Dopo il reset
git status               # Vedere il nuovo stato
git log --oneline -5     # Verificare posizione HEAD
git reflog               # Vedere cronologia dei movimenti HEAD
```

### Recovery da Reset Sbagliato
```bash
# Vedere cronologia completa di HEAD
git reflog

# Output esempio:
# abc1234 HEAD@{0}: reset: moving to HEAD~3
# def5678 HEAD@{1}: commit: Add new feature
# ghi9012 HEAD@{2}: commit: Fix bug in auth

# Recuperare commit "perso"
git reset --hard HEAD@{1}   # Torna al commit "Add new feature"
```

## 🧪 Laboratorio Pratico

### Esercizio 1: Reset Modes Comparison
```bash
# Setup
mkdir reset-modes-lab
cd reset-modes-lab
git init

# Crea storia di commit
echo "v1" > file.txt && git add . && git commit -m "Version 1"
echo "v2" > file.txt && git add . && git commit -m "Version 2"  
echo "v3" > file.txt && git add . && git commit -m "Version 3"

# Modifica e staging
echo "v4" > file.txt
git add file.txt

# Testa different reset modes
# 1. Test soft reset
git reset --soft HEAD~1
git status        # Cosa vedi in staging?
cat file.txt      # Cosa c'è in working directory?

# 2. Ripristina e test mixed reset
git commit -m "Version 3 restored"
echo "v4" > file.txt && git add file.txt
git reset --mixed HEAD~1
git status        # Differenza con soft?

# 3. Test hard reset (ATTENZIONE!)
git add file.txt && git commit -m "Version 3 again"
echo "v4" > file.txt && git add file.txt
git stash         # Backup delle modifiche
git reset --hard HEAD~1
git status        # Tutto pulito?
git stash pop     # Recupera le modifiche se necessario
```

### Esercizio 2: Staging Cleanup Workflow
```bash
# Scenario: Staging disordinato
echo "feature" > feature.js
echo "debug info" > debug.log
echo "temp data" > temp.txt
echo "important fix" > fix.js

# Aggiungi tutto per errore
git add .

# Cleanup con reset
git reset HEAD
git add feature.js fix.js
git commit -m "feat: add feature and important fix"

# Pulisci file temporanei
rm debug.log temp.txt
```

## 🎯 Strategie di Reset per Scenari Comuni

### 1. Correzione Ultimo Commit
```bash
# Scenario: Messaggio di commit sbagliato
git reset --soft HEAD~1
git commit -m "Messaggio corretto"

# Scenario: File dimenticato nell'ultimo commit
git reset --soft HEAD~1
git add file-dimenticato.js
git commit -m "Commit completo con file dimenticato"
```

### 2. Riorganizzazione Staging
```bash
# Scenario: Staging caotico da riorganizzare
git reset HEAD              # Svuota staging
git add -p                  # Re-staging interattivo
git commit -m "Commit atomico ben organizzato"
```

### 3. Sincronizzazione con Remote
```bash
# Scenario: Divergenza dal remote (con backup)
git fetch origin
git stash push -m "Local work backup"
git reset --hard origin/main
git stash pop               # Se vuoi mantenere lavoro locale
```

## 🚨 Warning e Best Practices

### ⚠️ Quando NON Usare Reset --hard
- **Mai su commit pubblici** (push già fatto)
- **Mai senza backup** del lavoro locale
- **Mai quando hai modifiche importanti** non committate

### ✅ Best Practices per Reset
1. **Usa reflog**: `git reflog` per tracking dei movimenti
2. **Backup prima di --hard**: `git stash` o `git branch backup-<date>`
3. **Preferisci --soft/--mixed**: Sono reversibili
4. **Verifica sempre**: `git status` dopo ogni reset

### 🛡️ Safety Checks
```bash
# Prima di reset potenzialmente pericoloso
git status                   # Vedere cosa cambierà
git diff                     # Vedere modifiche non committate
git stash push -m "Safety backup before reset"

# Dopo reset
git status                   # Verificare risultato
git reflog                   # Confermare movimento HEAD
```

## 🔧 Comandi Correlati e Alternative

### Alternative Moderne a Reset
```bash
# Invece di: git reset HEAD <file>
git restore --staged <file>

# Invece di: git reset --hard HEAD
git restore .               # Ripristina working directory

# Invece di: git reset --hard HEAD~1
git revert HEAD             # Crea commit che annulla modifiche
```

### Combinazioni Utili
```bash
# Reset con staging interattivo
git reset HEAD
git add -p

# Reset con preview
git diff HEAD~1             # Vedere cosa cambierà
git reset HEAD~1

# Reset selettivo con conferma
git reset --mixed HEAD~1 && git status
```

## 📚 Recap Concetti Chiave

1. **--soft**: Mantiene staging e working directory (correzione commit)
2. **--mixed**: Reset staging, mantiene working directory (riorganizzazione)
3. **--hard**: Reset tutto (emergenza, con backup!)
4. **File specifici**: `git reset HEAD <file>` per unstaging selettivo
5. **Recovery**: `git reflog` per recuperare reset sbagliati

## 🔗 Collegamenti

### Link Interni
- [📖 Tre Aree Git](./02-tre-aree-git.md) - Comprensione del flusso tra aree
- [📖 Git Add Avanzato](./03-git-add-avanzato.md) - Staging strategico
- [📖 Staging Interattivo](./05-staging-interattivo.md) - Controllo granulare

### Moduli Correlati
- [📖 Annullare Modifiche](../11-Annullare-Modifiche/README.md) - Tecniche di recovery avanzate
- [📖 Navigare tra Commit](../10-Navigare-tra-Commit/README.md) - Movimento nella cronologia

---

> **💡 Regola d'Oro**: Reset è come una macchina del tempo per Git. --soft ti porta indietro mantenendo tutto, --mixed ti porta indietro scompattando il bagaglio, --hard ti porta indietro naked (senza niente). Usa con saggezza!
