# 02 - Reset vs Revert: Strategie per Annullare Commit

## 📖 Spiegazione Concettuale

Due comandi fondamentali ma diversi per gestire commit indesiderati: `git reset` e `git revert`. La scelta tra i due dipende dal contesto e dalle implicazioni per la collaborazione. Capire la differenza è cruciale per evitare disastri nel versioning.

## 🔍 Differenze Concettuali

### Git Reset: "Riavvolgi la Storia"
- **Cancella** commit dalla cronologia
- **Modifica** la storia del repository
- **Sicuro** solo per commit non pushati
- **Pericoloso** per il lavoro collaborativo

### Git Revert: "Annulla con Trasparenza"
- **Mantiene** tutti i commit esistenti
- **Aggiunge** un nuovo commit che annulla le modifiche
- **Sicuro** anche per commit pubblici
- **Trasparente** nel processo di annullamento

## 🔧 Git Reset: Sintassi e Modalità

### Modalità di Reset

#### 1. **--soft**: Mantiene Staging e Working Directory
```bash
git reset --soft HEAD~1
# Effetto:
# - Commit rimosso dalla cronologia
# - File rimangono in staging area
# - Working directory invariata
# - Pronto per nuovo commit
```

#### 2. **--mixed** (default): Mantiene Solo Working Directory
```bash
git reset HEAD~1
# oppure
git reset --mixed HEAD~1
# Effetto:
# - Commit rimosso dalla cronologia  
# - Staging area pulita
# - File rimangono modificati in working directory
# - Necessario git add prima di commit
```

#### 3. **--hard**: Cancella Tutto
```bash
git reset --hard HEAD~1
# Effetto:
# - Commit rimosso dalla cronologia
# - Staging area pulita
# - Working directory ripristinata
# - ⚠️ ATTENZIONE: Modifiche perse permanentemente!
```

### Esempi Pratici di Reset

#### Scenario 1: Annullare Ultimo Commit (Soft)
```bash
# Situazione: Commit fatto troppo presto
git log --oneline -3
# abc123 Work in progress commit (voglio annullarlo)
# def456 Previous working commit
# ghi789 Another commit

# Reset soft - mantieni le modifiche in staging
git reset --soft HEAD~1

# Verifica stato
git status
# Output: Changes to be committed: (tutti i file del commit annullato)

# Ora puoi modificare e ricommittare
echo "More work" >> file.txt
git add file.txt
git commit -m "Complete feature implementation"
```

#### Scenario 2: Modificare Ultimi N Commit (Mixed)
```bash
# Situazione: Ultimi 2 commit sono confusi, vuoi riorganizzare
git log --oneline -4
# abc123 Fix typo
# def456 Add feature
# ghi789 Update docs
# jkl012 Previous working commit

# Reset mixed per riorganizzare
git reset HEAD~2

# Ora hai tutti i cambiamenti non staged
git status
# Output: Changes not staged for commit: ...

# Riorganizza e ricommita logicamente
git add feature-files/*
git commit -m "Add complete user authentication feature"

git add docs/*
git commit -m "Update documentation for new auth feature"
```

#### Scenario 3: Eliminare Commit Completamente (Hard)
```bash
# ⚠️ ATTENZIONE: Operazione distruttiva!
# Situazione: Ultimo commit contiene dati sensibili

# Backup di sicurezza
git tag backup-before-reset

# Reset hard - elimina tutto
git reset --hard HEAD~1

# Verifica che il commit sia sparito
git log --oneline -3
# Il commit problematico non c'è più

# Se necessario recupero
# git reset --hard backup-before-reset
```

## 🔄 Git Revert: Annullamento Sicuro

### Sintassi Base
```bash
# Revert di un singolo commit
git revert <commit-hash>

# Revert di multiple commit
git revert <commit1> <commit2> <commit3>

# Revert di un range
git revert HEAD~3..HEAD
```

### Esempi Pratici di Revert

#### Scenario 1: Revert di Singolo Commit
```bash
# Situazione: Un commit ha introdotto un bug in produzione
git log --oneline -5
# abc123 Add new feature (questo ha il bug!)
# def456 Update documentation  
# ghi789 Fix login issue
# jkl012 Update dependencies
# mno345 Initial release

# Revert del commit problematico
git revert abc123

# Git apre l'editor per il messaggio del revert commit
# Messaggio default: "Revert "Add new feature""
# Puoi modificarlo o accettare

# Risultato finale
git log --oneline -6
# pqr678 Revert "Add new feature"  ← Nuovo commit di revert
# abc123 Add new feature          ← Commit originale ancora presente
# def456 Update documentation
# ghi789 Fix login issue
# jkl012 Update dependencies
# mno345 Initial release
```

#### Scenario 2: Revert di Merge Commit
```bash
# Situazione: Un merge ha causato problemi
git log --oneline --graph -5
# * abc123 Merge pull request #42 from feature/new-auth
# |\
# | * def456 Implement OAuth integration
# | * ghi789 Add authentication middleware  
# |/
# * jkl012 Update base configuration

# Revert del merge (specifica il parent)
git revert -m 1 abc123
# -m 1 indica il primo parent (main branch)
# -m 2 indicherebbe il secondo parent (feature branch)
```

#### Scenario 3: Revert di Multipli Commit
```bash
# Situazione: Ultimi 3 commit sono tutti problematici
git log --oneline -5
# abc123 Third problematic commit
# def456 Second problematic commit  
# ghi789 First problematic commit
# jkl012 Last good commit
# mno345 Previous commit

# Opzione 1: Revert individuale (crea 3 commit)
git revert abc123 def456 ghi789

# Opzione 2: Revert con --no-commit, poi commit unico
git revert --no-commit abc123 def456 ghi789
git commit -m "Revert problematic feature implementation"

# Opzione 3: Revert range
git revert HEAD~2..HEAD
```

## 📊 Confronto: Quando Usare Reset vs Revert

### 🔄 Usa Git Reset Quando:

#### ✅ Scenari Appropriati
- **Commit locali** non ancora pushati
- **Riorganizzazione** della cronologia locale
- **Correzione errori** prima della condivisione
- **Squashing** di commit per cleanup

#### 💼 Esempio Pratico
```bash
# Sviluppo locale - commit multipli da organizzare
git log --oneline -4
# abc123 Fix typo
# def456 Add validation  
# ghi789 Implement feature
# jkl012 Start feature work

# Reset per riorganizzare
git reset --soft HEAD~3
# Ora tutti i cambiamenti sono in staging
git commit -m "Implement user validation feature"
# Cronologia più pulita con un singolo commit logico
```

### ↩️ Usa Git Revert Quando:

#### ✅ Scenari Appropriati  
- **Commit pubblici** (già pushati)
- **Ambiente di produzione** con cronologia critica
- **Collaborazione attiva** con altri sviluppatori
- **Audit trail** deve rimanere completo

#### 💼 Esempio Pratico
```bash
# Situazione: Bug scoperto in produzione
git log --oneline -3
# abc123 Deploy new payment system ← Questo ha un bug critico!
# def456 Update user interface
# ghi789 Fix authentication

# Revert sicuro (non modifica storia)
git revert abc123
git push origin main  # Deploy immediato della fix

# La cronologia rimane tracciabile:
# pqr678 Revert "Deploy new payment system"
# abc123 Deploy new payment system  
# def456 Update user interface
# ghi789 Fix authentication
```

## ⚠️ Errori Comuni e Soluzioni

### 1. **Reset Hard su Commit Pubblici**
```bash
# ❌ SBAGLIATO
git reset --hard HEAD~3  # Su commit già pushati
git push --force origin main  # Disastro per il team!

# ✅ CORRETTO
git revert HEAD~2..HEAD  # Mantiene la storia
git push origin main      # Sicuro per tutti
```

### 2. **Perdita di Lavoro con Reset Hard**
```bash
# ❌ PROBLEMA
git reset --hard HEAD~1  # Oops! Ho perso ore di lavoro!

# ✅ SOLUZIONE: Recovery con reflog
git reflog
# abc123 HEAD@{0}: reset: moving to HEAD~1
# def456 HEAD@{1}: commit: My lost work ← Ecco il commit perso!

git reset --hard def456  # Recupera il lavoro
```

### 3. **Revert di Revert**
```bash
# Situazione: Hai revertato, ma ora vuoi ri-applicare
git log --oneline -3  
# abc123 Revert "Add new feature"
# def456 Add new feature
# ghi789 Previous commit

# Per ri-applicare, revert il revert!
git revert abc123
# Ora "Add new feature" è di nuovo attiva
```

## 💡 Best Practices

### 1. **Strategia di Sicurezza**
```bash
# Sempre creare backup prima di operazioni distruttive
git tag backup/before-reset-$(date +%s)
git reset --hard HEAD~3

# Se qualcosa va storto
git reset --hard backup/before-reset-[timestamp]
```

### 2. **Reset per Cleanup Pre-Push**
```bash
# Workflow di cleanup prima del push
# 1. Verifica che i commit non siano stati pushati
if git merge-base --is-ancestor HEAD origin/$(git branch --show-current); then
    echo "Commits already pushed, use revert instead"
    exit 1
fi

# 2. Reset soft per organizzare
git reset --soft HEAD~3

# 3. Ricommit in modo logico
git commit -m "Implement complete user authentication system"
```

### 3. **Revert con Messaggio Dettagliato**
```bash
# Revert con messaggio informativo
git revert abc123 -m "
Revert problematic payment integration

This reverts commit abc123 due to:
- Critical security vulnerability in payment flow
- Data validation bypass discovered in production  
- Immediate rollback required for customer safety

Fix will be implemented in follow-up PR after security review.

Refs: #issues/1234
"
```

## 🧠 Quiz di Autovalutazione

### Domanda 1
Quale comando useresti per annullare un commit che è già stato pushato?
- a) `git reset --hard HEAD~1`
- b) `git revert HEAD`
- c) `git commit --amend`
- d) `git delete HEAD`

<details>
<summary>Risposta</summary>
**b) `git revert HEAD`**

Per commit pubblici, revert è l'unica opzione sicura. Reset modificherebbe la storia causando problemi ai collaboratori.
</details>

### Domanda 2
Che differenza c'è tra `git reset --soft` e `git reset --mixed`?
- a) Nessuna differenza
- b) --soft mantiene staging area, --mixed la pulisce
- c) --mixed è più veloce
- d) --soft è solo per branch

<details>
<summary>Risposta</summary>
**b) --soft mantiene staging area, --mixed la pulisce**

--soft mantiene i file in staging pronti per commit, --mixed li rimette in working directory non staged.
</details>

### Domanda 3
Quando è appropriato usare `git reset --hard`?
- a) Sempre, è il più efficace
- b) Solo su commit non pushati e quando vuoi eliminare completamente le modifiche
- c) Solo su repository personali
- d) Mai, è troppo pericoloso

<details>
<summary>Risposta</summary>
**b) Solo su commit non pushati e quando vuoi eliminare completamente le modifiche**

--hard è distruttivo e appropriato solo quando sei sicuro di voler perdere le modifiche e i commit non sono stati condivisi.
</details>

## 🏋️ Esercizi Pratici

### Esercizio 1: Reset Modes
```bash
# Setup
mkdir test-reset && cd test-reset
git init
echo "line 1" > file.txt
git add file.txt && git commit -m "First commit"
echo "line 2" >> file.txt  
git add file.txt && git commit -m "Second commit"
echo "line 3" >> file.txt
git add file.txt && git commit -m "Third commit"

# Compito 1: Reset soft dell'ultimo commit e verifica stato
# Compito 2: Ricommit con messaggio diverso
# Compito 3: Reset mixed di 2 commit e reorganizza
```

### Esercizio 2: Revert Sicuro
```bash
# Setup (continua dal precedente)
echo "bug line" >> file.txt
git add file.txt && git commit -m "Add feature with bug"

# Simula push (per questo esercizio)
echo "Questo commit è stato pushato - usa revert!"

# Compito: Fai revert del commit con bug usando un messaggio dettagliato
```

### Esercizio 3: Recovery da Reset
```bash
# Setup
git reset --hard HEAD~2  # "Oops, ho perso lavoro importante!"

# Compito: Usa git reflog per recuperare i commit persi
```

## 📖 Approfondimenti

### Reset Internals
Git reset funziona su tre livelli:
1. **HEAD**: Punta a commit diverso
2. **Index** (staging): Aggiornato secondo modalità
3. **Working Directory**: Modificato solo con --hard

### Revert vs Reset Decision Tree
```
È il commit già pushato?
├─ Sì → USA REVERT
│   ├─ Single commit → git revert <hash>
│   ├─ Merge commit → git revert -m 1 <hash>
│   └─ Multiple commits → git revert <hash1> <hash2>
│
└─ No → PUOI USARE RESET
    ├─ Vuoi mantenere modifiche staged? → git reset --soft
    ├─ Vuoi modifiche non staged? → git reset --mixed
    └─ Vuoi eliminare tutto? → git reset --hard
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Commit Amend](01-commit-amend.md)
- [➡️ Messaggi di Commit Professionali](03-messaggi-commit.md)
