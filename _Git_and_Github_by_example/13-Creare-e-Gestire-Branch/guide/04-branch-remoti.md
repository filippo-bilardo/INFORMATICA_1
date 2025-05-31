# 04 - Branch Remoti

## 📖 Spiegazione Concettuale

I **branch remoti** sono riferimenti ai branch che esistono nei repository remoti (come GitHub, GitLab, ecc.). Gestire branch remoti è essenziale per la collaborazione in team e per sincronizzare il lavoro tra diversi sviluppatori.

### Architettura Branch Locali vs Remoti

```
Repository Locale:
main
feature-login
bugfix-header

Repository Remoto (origin):
main
develop
feature-payment
feature-login (pushed)

Tracking Relationships:
main ← → origin/main
feature-login ← → origin/feature-login
```

## 🔧 Visualizzazione Branch Remoti

### Lista Branch Remoti

```bash
# Solo branch remoti
git branch -r
  origin/main
  origin/develop
  origin/feature-payment
  origin/hotfix-security

# Tutti i branch (locali + remoti)
git branch -a
  main
* feature-login
  bugfix-header
  remotes/origin/main
  remotes/origin/develop
  remotes/origin/feature-payment
```

### Informazioni Dettagliate

```bash
# Branch con tracking information
git branch -vv
  main          2a3b4c5 [origin/main: behind 2] Update docs
* feature-login a1b2c3d [origin/feature-login: ahead 3] Add login
  bugfix-header 9x8y7z6 Fix header issues

# Stato di sincronizzazione
git status
# On branch feature-login
# Your branch is ahead of 'origin/feature-login' by 3 commits.
```

## 🔄 Sincronizzazione con Remote

### Fetch: Aggiornare Riferimenti

```bash
# Scarica tutti i riferimenti remoti
git fetch origin

# Fetch con pulizia branch cancellati
git fetch --prune

# Fetch di un branch specifico
git fetch origin feature-payment

# Fetch da tutti i remotes
git fetch --all
```

### Pull: Fetch + Merge

```bash
# Pull del branch corrente
git pull origin main

# Equivale a:
# git fetch origin
# git merge origin/main

# Pull con rebase (mantiene storia lineare)
git pull --rebase origin main
```

## 📤 Push Branch Remoti

### Push Nuovo Branch

```bash
# Crea e pusha nuovo branch
git switch -c feature-newsletter
echo "Newsletter component" > newsletter.js
git add . && git commit -m "Add newsletter feature"

# Push iniziale con tracking
git push --set-upstream origin feature-newsletter
# oppure
git push -u origin feature-newsletter
```

### Push Branch Esistente

```bash
# Push normale
git push origin feature-login

# Push forzato (⚠️ pericoloso in team)
git push --force origin feature-login

# Push forzato sicuro (verifica che nessuno abbia pushato)
git push --force-with-lease origin feature-login
```

### Push di Tutti i Branch

```bash
# Push tutti i branch locali
git push origin --all

# Push tutti i tag
git push origin --tags

# Push completo (branch + tags)
git push origin --all && git push origin --tags
```

## 🔗 Tracking Branch

### Impostare Tracking

```bash
# Durante la creazione
git switch -c feature-api
git push -u origin feature-api

# Per branch esistente
git branch --set-upstream-to=origin/feature-api feature-api

# Sintassi breve
git branch -u origin/feature-api
```

### Verifica Tracking

```bash
# Visualizza relazioni tracking
git branch -vv
  main          2a3b4c5 [origin/main] Latest changes
* feature-api   a1b2c3d [origin/feature-api: ahead 2] API improvements

# Informazioni tracking per branch corrente
git status
# Your branch is ahead of 'origin/feature-api' by 2 commits.
```

## ⬇️ Checkout Branch Remoti

### Checkout Branch Remoto Esistente

```bash
# Metodo moderno (Git 2.23+)
git switch feature-payment
# Git crea automaticamente branch locale che traccia origin/feature-payment

# Metodo tradizionale
git checkout -b feature-payment origin/feature-payment

# Solo checkout senza creazione branch locale
git checkout origin/feature-payment
# (Ti mette in detached HEAD state)
```

### Checkout con Nome Diverso

```bash
# Crea branch locale con nome diverso
git switch -c local-feature-name origin/remote-feature-name

# Metodo tradizionale
git checkout -b local-feature-name origin/remote-feature-name
```

## 🗑️ Cancellazione Branch Remoti

### Cancellare Branch Remote

```bash
# Cancella branch sul remote
git push origin --delete feature-completed

# Sintassi alternativa
git push origin :feature-completed

# Verifica cancellazione
git branch -r
# origin/feature-completed non dovrebbe più apparire
```

### Cleanup Locale dopo Cancellazione Remote

```bash
# Rimuovi riferimenti locali a branch remoti cancellati
git remote prune origin

# Verifica cosa sarà rimosso (dry-run)
git remote prune origin --dry-run

# Fetch con cleanup automatico
git fetch --prune
```

## 🔄 Workflow Collaborativo

### Pattern Feature Branch

```bash
# 1. Sviluppatore A crea feature
git switch main
git pull origin main
git switch -c feature-user-profile
# ... sviluppo ...
git push -u origin feature-user-profile

# 2. Sviluppatore B lavora sulla stessa feature
git fetch origin
git switch feature-user-profile
# ... contributi ...
git push origin feature-user-profile

# 3. Sviluppatore A aggiorna con lavoro di B
git pull origin feature-user-profile
```

### Pattern Hotfix Condiviso

```bash
# 1. Hotfix urgente
git switch main
git pull origin main
git switch -c hotfix-critical-bug
echo "Quick fix" >> app.js
git add . && git commit -m "Fix critical bug"

# 2. Push immediato per team
git push -u origin hotfix-critical-bug

# 3. Altri sviluppatori applicano hotfix
git fetch origin
git switch hotfix-critical-bug
git switch main
git merge hotfix-critical-bug
```

## 🔍 Confronto Branch Remoti

### Differenze con Remote

```bash
# Differenze tra branch locale e remoto
git diff origin/main

# Commits nel remote che non hai localmente
git log HEAD..origin/main --oneline

# Commits locali che non sono nel remote
git log origin/main..HEAD --oneline

# Visualizzazione grafica completa
git log --graph --oneline --all
```

### Stato di Sincronizzazione

```bash
# Verifica tutti i branch
git for-each-ref --format="%(refname:short) %(upstream:track)" refs/heads

# Output esempio:
# main [ahead 1, behind 2]
# feature-login [ahead 3]
# bugfix-header
```

## 🛠️ Configurazione Remote

### Gestione Multiple Remote

```bash
# Visualizza remotes configurati
git remote -v
# origin    https://github.com/user/repo.git (fetch)
# origin    https://github.com/user/repo.git (push)

# Aggiungi remote aggiuntivo
git remote add upstream https://github.com/original/repo.git

# Fetch da remote specifico
git fetch upstream

# Push a remote specifico
git push upstream feature-contribution
```

### Configurazione URL Remote

```bash
# Cambia URL remote
git remote set-url origin https://github.com/newuser/repo.git

# Imposta URL diversi per fetch e push
git remote set-url --push origin https://github.com/myuser/repo.git

# Verifica configurazione
git remote show origin
```

## ⚠️ Problemi Comuni e Soluzioni

### Conflitti con Remote Branch

```bash
# Problema: branch locale e remoto sono divergenti
git push origin feature-branch
# error: failed to push some refs

# Soluzione 1: Pull prima di push
git pull origin feature-branch
# Risolvi eventuali conflitti
git push origin feature-branch

# Soluzione 2: Rebase per storia lineare
git pull --rebase origin feature-branch
git push origin feature-branch
```

### Branch Remote "Fantasma"

```bash
# Problema: branch remoto esiste localmente ma non sul server
git branch -r
# origin/feature-deleted (ma non esiste più su GitHub)

# Soluzione: cleanup
git remote prune origin
git fetch --prune
```

### Tracking Branch Rotto

```bash
# Problema: tracking relationship non configurato
git push
# error: The current branch has no upstream branch

# Soluzione: configura tracking
git push --set-upstream origin current-branch-name

# Oppure
git branch -u origin/current-branch-name
```

## 🎯 Best Practices Remote

### ✅ Buone Pratiche

```bash
# Sempre fetch prima di iniziare nuovo lavoro
git fetch origin
git switch main
git pull origin main
git switch -c new-feature

# Usa force-with-lease invece di force
git push --force-with-lease origin feature-branch

# Cleanup regolare
git fetch --prune
git remote prune origin

# Branch naming consistente con team
git push -u origin feature/user-authentication
```

### ❌ Pratiche da Evitare

```bash
# Non usare --force senza coordinamento team
git push --force origin main  # ⚠️ Pericoloso!

# Non accumulare branch remoti obsoleti
git branch -r  # Lista infinita di branch morti

# Non ignorare warning di Git
# ! [rejected] main -> main (fetch first)
# (Sempre fetch e risolvi conflitti prima)
```

## 🔧 Automation e Scripts

### Script per Cleanup Branch

```bash
#!/bin/bash
# cleanup-branches.sh

echo "🧹 Cleaning up merged branches..."

# Fetch latest state
git fetch --prune

# Delete local branches that are merged and have remote tracking
git for-each-ref --format '%(refname:short) %(upstream:short)' refs/heads | \
while read local remote; do
    if [ "$remote" != "" ] && git merge-base --is-ancestor "$local" origin/main; then
        echo "Deleting merged branch: $local"
        git branch -d "$local"
    fi
done

echo "✅ Cleanup completed!"
```

### Hook per Validazione Push

```bash
#!/bin/bash
# .git/hooks/pre-push

# Previeni push accidentale di branch con WIP
protected_branch='main'
current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')

if [ $protected_branch = $current_branch ]; then
    if git log -1 --pretty=%B | grep -q "WIP"; then
        echo "🚫 Cannot push WIP commits to main branch!"
        exit 1
    fi
fi
```

## 📚 Risorse Aggiuntive

- [Git Remote Documentation](https://git-scm.com/docs/git-remote)
- [Pro Git Book - Remote Branches](https://git-scm.com/book/en/v2/Git-Branching-Remote-Branches)
- [Atlassian Remote Repositories](https://www.atlassian.com/git/tutorials/syncing)

---

## 🔄 Navigazione

- [⬅️ 03 - Gestione Branch](03-gestione-branch.md)
- [➡️ 05 - Best Practices](05-best-practices.md)
- [🏠 README](../README.md)

---

*Prossimo: Scopriremo le best practices per un workflow di branching efficace*
