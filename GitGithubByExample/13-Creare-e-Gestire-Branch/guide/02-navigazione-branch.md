# 02 - Navigazione tra Branch

## 📖 Spiegazione Concettuale

La **navigazione tra branch** è l'operazione che ti permette di spostarti da un branch all'altro nel tuo repository. È come cambiare cartella di lavoro, ma ogni "cartella" rappresenta una versione diversa del tuo progetto.

### Cosa Succede Durante la Navigazione

```
Stato iniziale:
main:          A ← B ← C (HEAD)
feature-login: A ← B ← C ← D

Dopo git switch feature-login:
main:          A ← B ← C
feature-login: A ← B ← C ← D (HEAD)
```

Quando cambi branch:
1. **Working Directory** viene aggiornata ai file del branch destinazione
2. **HEAD** viene spostato sul branch selezionato
3. **Index/Staging** viene resettato al contenuto del nuovo branch

## 🔧 Sintassi e Comandi

### Comando Moderno: git switch

```bash
# Cambia al branch specificato
git switch <nome-branch>

# Cambia al branch precedente
git switch -

# Crea e cambia in un colpo solo
git switch -c <nuovo-branch>

# Cambia forzatamente (scarta modifiche locali)
git switch --force <nome-branch>
```

### Comando Tradizionale: git checkout

```bash
# Cambia al branch specificato
git checkout <nome-branch>

# Cambia al branch precedente
git checkout -

# Crea e cambia branch
git checkout -b <nuovo-branch>

# Forza il cambio
git checkout --force <nome-branch>
```

## 🎯 Esempi Pratici

### Scenario 1: Navigazione Base

```bash
# Verifica branch corrente
git branch
* main
  feature-header
  bugfix-404

# Cambia a feature-header
git switch feature-header
# Switched to branch 'feature-header'

# Verifica cambio
git branch
  main
* feature-header
  bugfix-404
```

### Scenario 2: Navigazione Rapida

```bash
# Lavora su main
git switch main
echo "Fix urgente" >> README.md
git add . && git commit -m "Hotfix critico"

# Torna velocemente al branch precedente
git switch -
# Switched to branch 'feature-header'

# Continua sviluppo feature
echo "Nuovo contenuto" >> header.html
```

### Scenario 3: Navigazione con Creazione

```bash
# Crea e cambia a nuovo branch da main
git switch main
git switch -c feature-footer

# Equivale a:
# git branch feature-footer
# git switch feature-footer
```

## ⚠️ Gestione delle Modifiche Uncommitted

### Problema: Modifiche Non Salvate

```bash
# Modifica file su main
echo "Lavoro in corso" >> index.html

# Tenta di cambiare branch
git switch feature-header
# error: Your local changes would be overwritten by checkout.
```

### Soluzioni Disponibili

#### Soluzione 1: Commit Temporaneo
```bash
git add .
git commit -m "WIP: lavoro in corso"
git switch feature-header
# ... lavori su feature-header
git switch main
git reset HEAD~1  # Annulla commit temporaneo
```

#### Soluzione 2: Stash (Consigliato)
```bash
git stash push -m "Lavoro temporaneo su main"
git switch feature-header
# ... lavori su feature-header
git switch main
git stash pop  # Recupera modifiche
```

#### Soluzione 3: Force Switch (Pericoloso)
```bash
git switch --force feature-header
# ⚠️ ATTENZIONE: Perdi le modifiche non salvate!
```

## 🔍 Verifica Stato Branch

### Comando git status
```bash
git status
# On branch feature-header
# Your branch is up to date with 'origin/feature-header'.
# 
# Changes not staged for commit:
#   modified:   header.html
```

### Comando git branch
```bash
# Lista branch locali con indicazione corrente
git branch
  main
* feature-header
  bugfix-404

# Lista tutti i branch (inclusi remoti)
git branch -a
  main
* feature-header
  bugfix-404
  remotes/origin/main
  remotes/origin/develop
```

### Informazioni Dettagliate
```bash
# Mostra ultimo commit per ogni branch
git branch -v
  main           3a2b1c4 Fix homepage layout
* feature-header a1b2c3d Add responsive header
  bugfix-404     7x8y9z0 Fix 404 page styling

# Mostra relazione con branch remoti
git branch -vv
  main           3a2b1c4 [origin/main] Fix homepage layout
* feature-header a1b2c3d [origin/feature-header: ahead 2] Add responsive header
  bugfix-404     7x8y9z0 Fix 404 page styling
```

## 🚀 Workflow di Navigazione

### Pattern Tipico di Sviluppo

```bash
# 1. Inizia sempre da main aggiornato
git switch main
git pull origin main

# 2. Crea branch per nuova feature
git switch -c feature-user-profile

# 3. Sviluppa e commit
echo "Profile component" > profile.js
git add . && git commit -m "Add user profile component"

# 4. Se serve hotfix urgente su main
git switch main
git switch -c hotfix-critical-bug
echo "Bug fix" >> app.js
git add . && git commit -m "Fix critical security bug"

# 5. Torna alla feature dopo hotfix
git switch feature-user-profile
```

## 💡 Best Practices per Navigazione

### ✅ Buone Pratiche

```bash
# Sempre verifica branch corrente prima di lavorare
git branch

# Usa nomi descrittivi per identificare facilmente
git switch feature-shopping-cart
git switch bugfix-payment-validation

# Commitment frequenti per evitare conflitti di switch
git add . && git commit -m "Checkpoint: work in progress"

# Usa stash per modifiche temporanee
git stash push -m "Temporary work"
```

### ❌ Pratiche da Evitare

```bash
# Non cambiare branch con modifiche uncommitted critiche
git switch other-branch  # Rischi di perdere lavoro!

# Non usare force senza necessità
git switch --force  # Può causare perdita dati

# Non ignorare warning di Git
# error: Your local changes would be overwritten
# (Leggi sempre i messaggi di errore!)
```

## 🔧 Troubleshooting Navigazione

### Problema: "Cannot switch, uncommitted changes"

```bash
# Errore
git switch feature-branch
# error: Your local changes to 'file.txt' would be overwritten

# Soluzioni
git status  # Verifica cosa è modificato
git stash   # Salva temporaneamente
# oppure
git add . && git commit -m "Save current work"
```

### Problema: "Branch does not exist"

```bash
# Errore
git switch non-existent-branch
# error: pathspec 'non-existent-branch' did not match any file(s)

# Soluzione: verifica branch disponibili
git branch -a
# Crea se necessario
git switch -c non-existent-branch
```

### Problema: "Detached HEAD state"

```bash
# Se finisci in detached HEAD
git status
# HEAD detached at 1a2b3c4

# Soluzioni
git switch main          # Torna a branch normale
# oppure
git switch -c new-branch # Crea branch da qui
```

## 🎯 Switch vs Checkout: Quando Usare Cosa

### Usa `git switch` quando:
- **Navigazione semplice** tra branch esistenti
- **Creazione di nuovi branch** (`-c` flag)
- **Operazioni moderne** e chiare
- **Evitare ambiguità** con file/commit

### Usa `git checkout` quando:
- **Checkout di file specifici** da altri commit
- **Checkout di commit specifici** (detached HEAD)
- **Script legacy** che lo richiedono
- **Operazioni complesse** che richiedono la sua flessibilità

```bash
# Switch: solo per branch
git switch feature-branch

# Checkout: più versatile
git checkout feature-branch        # branch
git checkout 1a2b3c4              # commit specifico
git checkout main -- file.txt     # file da altro branch
```

## 📚 Risorse Aggiuntive

- [Git Switch Documentation](https://git-scm.com/docs/git-switch)
- [Git Checkout Documentation](https://git-scm.com/docs/git-checkout)
- [Pro Git Book - Branching](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging)

---

## 🔄 Navigazione

- [⬅️ 01 - Creazione Branch](01-creare-branch.md)
- [➡️ 03 - Gestione Branch](03-gestione-branch.md)
- [🏠 README](../README.md)

---

*Prossimo: Impareremo a gestire, rinominare e cancellare branch efficacemente*
