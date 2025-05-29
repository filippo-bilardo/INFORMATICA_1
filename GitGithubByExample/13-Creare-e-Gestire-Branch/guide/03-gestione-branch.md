# 03 - Gestione Branch

## 📖 Spiegazione Concettuale

La **gestione dei branch** comprende tutte le operazioni di amministrazione: visualizzazione, rinominazione, cancellazione e organizzazione dei branch nel tuo repository. Una gestione efficace dei branch è cruciale per mantenere un repository pulito e ben organizzato.

### Ciclo di Vita di un Branch

```
1. Creazione      → 2. Sviluppo → 3. Merge → 4. Cancellazione
   git switch -c     commits        git merge   git branch -d
   feature-login     multipli       feature     feature-login
```

## 🔧 Comandi di Visualizzazione

### Lista Branch Locali

```bash
# Lista branch locali
git branch
  main
* feature-login
  bugfix-header
  
# Lista con informazioni dettagliate
git branch -v
  main          2a3b4c5 Update documentation
* feature-login a1b2c3d Add login functionality
  bugfix-header 9x8y7z6 Fix header responsive issues
```

### Lista Branch Remoti

```bash
# Solo branch remoti
git branch -r
  origin/main
  origin/develop
  origin/feature-payment

# Tutti i branch (locali + remoti)
git branch -a
  main
* feature-login
  bugfix-header
  remotes/origin/main
  remotes/origin/develop
  remotes/origin/feature-payment
```

### Informazioni Avanzate

```bash
# Branch con tracking information
git branch -vv
  main          2a3b4c5 [origin/main] Update documentation
* feature-login a1b2c3d [origin/feature-login: ahead 3] Add login
  bugfix-header 9x8y7z6 Fix header responsive issues

# Branch già mergiate in main
git branch --merged main
  bugfix-old-issue
  feature-completed

# Branch non ancora mergiate
git branch --no-merged main
  feature-login
  feature-payment
```

## 🏷️ Rinominazione Branch

### Rinominare Branch Corrente

```bash
# Rinomina il branch su cui ti trovi
git branch -m nuovo-nome

# Esempio pratico
git switch feature-user-auth
git branch -m feature-authentication
# Il branch ora si chiama 'feature-authentication'
```

### Rinominare Branch Non Corrente

```bash
# Rinomina un branch senza switchare
git branch -m vecchio-nome nuovo-nome

# Esempio
git branch -m bugfix-typo bugfix-spelling-errors
```

### Rinominazione con Branch Remoti

```bash
# 1. Rinomina localmente
git branch -m old-name new-name

# 2. Cancella branch remoto con vecchio nome
git push origin --delete old-name

# 3. Pusha branch con nuovo nome
git push origin new-name

# 4. Imposta tracking per il nuovo branch
git push --set-upstream origin new-name
```

## 🗑️ Cancellazione Branch

### Cancellazione Sicura

```bash
# Cancella branch solo se già mergiato
git branch -d feature-completed
# Deleted branch feature-completed (was 3a2b1c4).

# Se non è mergiato, Git ti avverte
git branch -d feature-in-progress
# error: The branch 'feature-in-progress' is not fully merged.
# If you are sure you want to delete it, run 'git branch -D'.
```

### Cancellazione Forzata

```bash
# Cancella branch anche se non mergiato
git branch -D experimental-feature
# Deleted branch experimental-feature (was 7x8y9z0).

# ⚠️ ATTENZIONE: Puoi perdere lavoro non salvato!
```

### Cancellazione Branch Remoti

```bash
# Cancella branch sul remote
git push origin --delete feature-old

# Sintassi alternativa
git push origin :feature-old

# Cleanup dei riferimenti remoti locali
git remote prune origin
```

## 🧹 Pulizia Branch

### Script di Pulizia Automatica

```bash
# Cancella tutti i branch già mergiate in main
git branch --merged main | grep -v "\* main" | xargs -n 1 git branch -d

# Versione più sicura (con conferma)
git branch --merged main | grep -v "\* main" | while read branch; do
    echo "Cancello branch: $branch"
    git branch -d "$branch"
done
```

### Pulizia Branch Remoti Obsoleti

```bash
# Rimuovi riferimenti a branch remoti cancellati
git remote prune origin

# Verifica cosa sarà rimosso (dry-run)
git remote prune origin --dry-run

# Fetch con pulizia automatica
git fetch --prune
```

## 📊 Analisi Branch

### Confronto tra Branch

```bash
# Differenze tra due branch
git diff main..feature-login

# Commits presenti in feature ma non in main
git log main..feature-login --oneline

# Commits presenti in main ma non in feature
git log feature-login..main --oneline

# Visualizzazione grafica
git log --graph --oneline --all
```

### Statistiche Branch

```bash
# Autore dei commit per branch
git shortlog feature-login

# Numero di commit per branch
git rev-list --count feature-login

# Data ultimo commit
git log -1 --format="%cd" feature-login
```

## 🏗️ Organizzazione Branch

### Convenzioni di Naming

```bash
# Per feature
feature/user-authentication
feature/payment-integration
feature/email-notifications

# Per bugfix
bugfix/login-validation
bugfix/payment-timeout
hotfix/security-patch

# Per release
release/v1.2.0
release/v2.0.0-beta

# Per sviluppo personale
dev/mario-experimental
dev/sara-performance-test
```

### Struttura Gerarchica

```bash
# Creazione struttura organizzata
git switch -c feature/frontend/user-profile
git switch -c feature/backend/api-refactor
git switch -c bugfix/mobile/responsive-issues
git switch -c hotfix/security/xss-protection

# Visualizzazione organizzata
git branch | grep "feature/"
git branch | grep "bugfix/"
git branch | grep "hotfix/"
```

## 🔄 Workflow di Gestione

### Pattern Team Development

```bash
# 1. Sviluppatore inizia feature
git switch main
git pull origin main
git switch -c feature/shopping-cart

# 2. Lavora sulla feature
# ... commits multipli ...

# 3. Feature completa, cleanup prima del merge
git switch main
git pull origin main
git switch feature/shopping-cart
git rebase main  # Opzionale: mantiene storia lineare

# 4. Merge e cleanup
git switch main
git merge feature/shopping-cart
git push origin main
git branch -d feature/shopping-cart
git push origin --delete feature/shopping-cart
```

### Pattern Hotfix

```bash
# 1. Bug critico in produzione
git switch main
git pull origin main
git switch -c hotfix/critical-security-fix

# 2. Fix veloce
echo "Security patch" >> security.js
git add . && git commit -m "Fix: patch critical security vulnerability"

# 3. Deploy immediato
git switch main
git merge hotfix/critical-security-fix
git push origin main
git tag v1.2.1  # Tag per la release

# 4. Cleanup
git branch -d hotfix/critical-security-fix
```

## 🛡️ Best Practices Gestione

### ✅ Buone Pratiche

```bash
# Cleanup regolare dei branch mergiate
git branch --merged main | grep -v "\* main" | xargs -n 1 git branch -d

# Nomi descrittivi e coerenti
git switch -c feature/user-profile-settings

# Documenta branch long-running
echo "# Feature: User Profile" > .branch-info

# Verifica sempre prima di cancellare
git log feature-to-delete --oneline
git branch -d feature-to-delete
```

### ❌ Pratiche da Evitare

```bash
# Non cancellare branch senza verificare
git branch -D feature-important  # Rischi di perdere lavoro!

# Non usare nomi generici
git switch -c temp  # Poco descrittivo
git switch -c fix   # Troppo vago

# Non accumulare branch obsolete
git branch  # Lista infinita di branch inutili
```

## 🔧 Troubleshooting Gestione

### Problema: "Cannot delete current branch"

```bash
# Errore
git branch -d feature-current
# error: Cannot delete branch 'feature-current' checked out at...

# Soluzione: cambia branch prima di cancellare
git switch main
git branch -d feature-current
```

### Problema: "Branch not fully merged"

```bash
# Errore
git branch -d feature-incomplete
# error: The branch 'feature-incomplete' is not fully merged.

# Verifica cosa non è mergiato
git log main..feature-incomplete --oneline

# Decidi: merge o force delete
git merge feature-incomplete  # Se vuoi conservare
# oppure
git branch -D feature-incomplete  # Se vuoi scartare
```

### Problema: "Remote branch still exists"

```bash
# Branch locale cancellato ma remote esiste ancora
git branch -d feature-done
git push origin --delete feature-done  # Cancella anche remote

# Cleanup riferimenti locali
git remote prune origin
```

## 🎯 Gestione Avanzata

### Branch con Metadati

```bash
# Aggiungere note ai branch
git notes add -m "Feature per milestone Q2" HEAD

# Branch con date di scadenza (tramite tags)
git tag -a cleanup-$(date +%Y%m%d) -m "Scheduled for cleanup"

# Branch temporanei con naming convention
git switch -c temp/$(date +%Y%m%d)-user-experiment
```

### Automazione con Scripts

```bash
# Script per branch cleanup (.git/hooks/post-merge)
#!/bin/bash
# Cleanup automatico dopo merge
git branch --merged main | grep -v "\* main" | xargs -n 1 git branch -d

# Script per branch naming validation
#!/bin/bash
# Verifica naming convention prima di push
branch=$(git rev-parse --abbrev-ref HEAD)
if [[ ! $branch =~ ^(feature|bugfix|hotfix)/.+ ]]; then
    echo "Branch name must start with feature/, bugfix/, or hotfix/"
    exit 1
fi
```

## 📚 Risorse Aggiuntive

- [Git Branch Documentation](https://git-scm.com/docs/git-branch)
- [Pro Git Book - Branch Management](https://git-scm.com/book/en/v2/Git-Branching-Branch-Management)
- [Atlassian Git Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows)

---

## 🔄 Navigazione

- [⬅️ 02 - Navigazione Branch](02-navigazione-branch.md)
- [➡️ 04 - Branch Remoti](04-branch-remoti.md)
- [🏠 README](../README.md)

---

*Prossimo: Esploreremo la gestione dei branch remoti e la sincronizzazione*
