# 06 - Troubleshooting Branch

## 📖 Problemi Comuni e Soluzioni

Il **troubleshooting dei branch** copre i problemi più frequenti che incontrerai lavorando con Git. Questa guida ti fornisce soluzioni pratiche e testati per ogni scenario problematico.

### Classificazione Problemi

```
🚨 Critici: Perdita potenziale di dati
⚠️  Importanti: Blocco del workflow
💡 Minori: Inconvenienti operativi
🔧 Educativi: Opportunità di apprendimento
```

## 🚨 Problemi Critici

### 1. Branch Cancellato Accidentalmente

**Problema**: Hai cancellato un branch importante con `git branch -D`

```bash
# Errore commesso
git branch -D feature-important
# Deleted branch feature-important (was a1b2c3d).
```

**Soluzioni**:

```bash
# Soluzione 1: Recupero tramite reflog
git reflog
# a1b2c3d HEAD@{1}: commit: Important feature work
# 9x8y7z6 HEAD@{2}: checkout: moving from main to feature-important

# Ricrea branch dal commit
git switch -c feature-important a1b2c3d

# Soluzione 2: Se conosci l'hash del commit
git switch -c feature-important-recovered a1b2c3d

# Soluzione 3: Cerca nell'output di git log
git log --all --grep="Important feature" --oneline
# a1b2c3d Add important feature functionality
git switch -c feature-important a1b2c3d
```

### 2. Modifiche Perse Durante Switch

**Problema**: Hai cambiato branch perdendo modifiche non committate

```bash
# Scenario: modifiche su feature-a
echo "Important work" >> file.txt

# Cambio branch senza commit
git switch main
# error: Your local changes to 'file.txt' would be overwritten
```

**Soluzioni**:

```bash
# Soluzione 1: Stash (se l'errore non è già avvenuto)
git stash push -m "Work in progress on file.txt"
git switch main
# ... lavoro su main ...
git switch feature-a
git stash pop

# Soluzione 2: Se hai già perso le modifiche, verifica stash
git stash list
git stash show -p stash@{0}

# Soluzione 3: Commit temporaneo
git add .
git commit -m "WIP: temporary save"
git switch main
# ... lavoro ...
git switch feature-a
git reset HEAD~1  # Rimuove commit temporaneo
```

### 3. Merge Conflict Complesso

**Problema**: Conflict irrisolvibile durante merge

```bash
# Durante merge
git merge feature-complex
# Auto-merging file.txt
# CONFLICT (content): Merge conflict in file.txt
# Automatic merge failed; fix conflicts and then commit the result.
```

**Soluzioni**:

```bash
# Soluzione 1: Abort e retry
git merge --abort
git status  # Verifica clean state

# Preparazione migliore
git switch feature-complex
git rebase main  # Risolvi conflicts qui
git switch main
git merge feature-complex  # Dovrebbe essere fast-forward

# Soluzione 2: Merge tool
git mergetool
# Apre strumento grafico per risoluzione

# Soluzione 3: Cherry-pick commits specifici
git merge --abort
git log feature-complex --oneline
git cherry-pick a1b2c3d  # Applica commit uno alla volta
git cherry-pick e4f5g6h
```

## ⚠️ Problemi Importanti

### 4. Branch Divergenti

**Problema**: Branch locale e remoto sono divergenti

```bash
git push origin feature-shared
# ! [rejected] feature-shared -> feature-shared (non-fast-forward)
# error: failed to push some refs
```

**Soluzioni**:

```bash
# Soluzione 1: Pull con merge
git pull origin feature-shared
# Risolvi eventuali conflicts
git push origin feature-shared

# Soluzione 2: Pull con rebase (storia più pulita)
git pull --rebase origin feature-shared
# Risolvi conflicts se necessario
git rebase --continue
git push origin feature-shared

# Soluzione 3: Force push (⚠️ solo se sei l'unico sul branch)
git push --force-with-lease origin feature-shared

# Soluzione 4: Reset e re-apply (estrema)
git fetch origin
git reset --hard origin/feature-shared
# ⚠️ Perdi commits locali non pushati!
```

### 5. Detached HEAD State

**Problema**: Ti trovi in stato "detached HEAD"

```bash
git checkout a1b2c3d
# Note: switching to 'a1b2c3d'.
# You are in 'detached HEAD' state.

git status
# HEAD detached at a1b2c3d
```

**Soluzioni**:

```bash
# Soluzione 1: Torna a branch normale
git switch main

# Soluzione 2: Crea branch da questa posizione
git switch -c new-branch-from-here

# Soluzione 3: Se hai fatto commits in detached state
git log --oneline  # Nota gli hash dei commit
git switch main
git switch -c recovery-branch
git cherry-pick commit-hash-1
git cherry-pick commit-hash-2
```

### 6. Branch Tracking Rotto

**Problema**: Branch non traccia correttamente il remote

```bash
git push
# fatal: The current branch feature-local has no upstream branch.

git status
# On branch feature-local
# nothing to commit, working tree clean
# (no upstream tracking info)
```

**Soluzioni**:

```bash
# Soluzione 1: Imposta upstream
git push --set-upstream origin feature-local

# Soluzione 2: Configura tracking per branch esistente
git branch --set-upstream-to=origin/feature-remote feature-local

# Soluzione 3: Verifica e correggi configurazione
git branch -vv  # Mostra tracking status
git config --get branch.feature-local.remote
git config --get branch.feature-local.merge

# Soluzione 4: Ricrea tracking
git branch --unset-upstream feature-local
git push -u origin feature-local
```

## 💡 Problemi Minori

### 7. Branch con Nome Sbagliato

**Problema**: Hai creato branch con nome errato

```bash
git switch -c feature-typo-wrng-name
# Ops! Nome sbagliato
```

**Soluzioni**:

```bash
# Soluzione 1: Rinomina locale
git branch -m feature-correct-name

# Soluzione 2: Se già pushato
git branch -m feature-correct-name
git push origin :feature-typo-wrng-name  # Cancella remoto
git push -u origin feature-correct-name   # Push con nome nuovo

# Soluzione 3: Crea nuovo e cancella vecchio
git switch -c feature-correct-name
git branch -D feature-typo-wrng-name
```

### 8. Troppi Branch Inutili

**Problema**: Repository con decine di branch obsoleti

```bash
git branch
# feature-old-1
# feature-old-2
# ... (20+ branch)
# * main
```

**Soluzioni**:

```bash
# Soluzione 1: Cleanup automatico branch merged
git branch --merged main | grep -v "\* main" | grep -v "main" | xargs -n 1 git branch -d

# Soluzione 2: Script di cleanup interattivo
git branch | grep "feature-" | while read branch; do
    echo "Delete $branch? (y/n)"
    read answer
    if [ "$answer" = "y" ]; then
        git branch -d $branch
    fi
done

# Soluzione 3: Cleanup completo con date
git for-each-ref --format='%(refname:short) %(committerdate)' refs/heads | \
    sort -k2 | head -20  # Mostra 20 branch più vecchi
```

### 9. Commit nel Branch Sbagliato

**Problema**: Hai fatto commit nel branch sbagliato

```bash
# Su main per errore
git status
# On branch main

echo "Feature work" >> feature.txt
git add . && git commit -m "Add feature work"
# Ops! Doveva essere su feature-branch
```

**Soluzioni**:

```bash
# Soluzione 1: Sposta commit al branch corretto
git switch -c feature-branch  # Crea branch da qui
git switch main
git reset --hard HEAD~1       # Rimuovi commit da main

# Soluzione 2: Cherry-pick su branch target
git log --oneline -1  # Nota hash commit
# a1b2c3d Add feature work

git switch feature-target
git cherry-pick a1b2c3d
git switch main
git reset --hard HEAD~1

# Soluzione 3: Reset soft e re-commit
git reset --soft HEAD~1  # Mantiene modifiche staged
git switch feature-branch
git commit -m "Add feature work"
```

## 🔧 Problemi Educativi

### 10. Conflitti di File Binari

**Problema**: Conflict su file binari (immagini, docs, ecc.)

```bash
git merge feature-images
# CONFLICT (content): Merge conflict in image.png
# warning: Cannot merge binary files: image.png (HEAD vs. feature-images)
```

**Soluzioni**:

```bash
# Soluzione 1: Scegli versione specifica
git checkout --theirs image.png  # Usa versione del branch
git checkout --ours image.png    # Usa versione corrente
git add image.png
git commit

# Soluzione 2: Rinomina entrambe le versioni
git show HEAD:image.png > image-main.png
git show feature-images:image.png > image-feature.png
git add .
git commit -m "Keep both versions of image"

# Soluzione 3: Usa tool esterni per merge
git mergetool image.png
```

### 11. Storia Git Confusa

**Problema**: Storia git illeggibile con troppi merge

```bash
git log --graph --oneline
# *   a1b2c3d Merge branch 'feature'
# |\
# | *   9x8y7z6 Merge branch 'main' into feature
# | |\
# | | * 5u6i7o8 Another merge
# | | |\
# (grafico incomprensibile)
```

**Soluzioni**:

```bash
# Soluzione 1: Rebase feature branch
git switch feature-branch
git rebase main  # Storia lineare
git switch main
git merge feature-branch  # Fast-forward

# Soluzione 2: Squash merge
git merge --squash feature-branch
git commit -m "Add complete feature functionality"

# Soluzione 3: Interactive rebase per cleanup
git rebase -i HEAD~5  # Edita ultimi 5 commits
# pick, squash, reword, drop commits
```

### 12. Performance Repository Degradata

**Problema**: Operazioni Git lente

```bash
git status
# (impiega molti secondi)

git log
# (caricamento lento)
```

**Soluzioni**:

```bash
# Soluzione 1: Garbage collection
git gc --aggressive --prune=now

# Soluzione 2: Verifica dimensione repository
git count-objects -vH

# Soluzione 3: Rimuovi file grandi dalla storia
git filter-branch --tree-filter 'rm -f large-file.zip' HEAD
git push origin --force --all

# Soluzione 4: Shallow clone per repository grandi
git clone --depth 1 https://github.com/user/repo.git
```

## 🛠️ Toolkit di Troubleshooting

### Comandi di Diagnostica

```bash
# Stato generale repository
git status
git branch -vv
git remote -v

# Verifica integrità
git fsck
git fsck --unreachable

# Storia e reflog
git log --graph --oneline --all
git reflog

# Configurazione
git config --list
git config --global --list
```

### Script di Recovery

```bash
#!/bin/bash
# git-recovery-toolkit.sh

echo "🔧 Git Recovery Toolkit"
echo "======================"

echo "1. Repository status:"
git status

echo "2. Recent reflog entries:"
git reflog --oneline -10

echo "3. Branch information:"
git branch -vv

echo "4. Stash list:"
git stash list

echo "5. Recent commits:"
git log --oneline -10

echo "6. Unreachable objects:"
git fsck --unreachable | head -10

echo "✅ Diagnostic completed!"
```

### Prevenzione Problemi

```bash
# Pre-commit hook per validazioni
#!/bin/bash
# .git/hooks/pre-commit

# Verifica branch name
branch=$(git rev-parse --abbrev-ref HEAD)
if [[ ! $branch =~ ^(feature|bugfix|hotfix)/.+ ]] && [[ $branch != "main" ]]; then
    echo "🚫 Invalid branch name: $branch"
    echo "Use: feature/name, bugfix/name, or hotfix/name"
    exit 1
fi

# Verifica dimensione file
large_files=$(git diff --cached --name-only | xargs ls -la | awk '$5 > 10485760 {print $9}')
if [ "$large_files" ]; then
    echo "🚫 Large files detected (>10MB):"
    echo "$large_files"
    exit 1
fi
```

## 📋 Checklist Troubleshooting

### ✅ Prima di Panico

- [ ] `git status` - Verifica stato corrente
- [ ] `git branch` - Controlla branch attivo
- [ ] `git log --oneline -5` - Verifica ultimi commits
- [ ] `git stash list` - Controlla stash disponibili

### ✅ Per Recovery

- [ ] `git reflog` - Trova commits "persi"
- [ ] `git fsck --unreachable` - Trova oggetti orfani
- [ ] Backup stato corrente prima di fix rischiosi
- [ ] Test su repository clone prima di fix

### ✅ Dopo Fix

- [ ] Verifica che il problema sia risolto
- [ ] Test funzionalità non compromesse
- [ ] Documenta soluzione per future reference
- [ ] Considera prevenzione del problema

## 🆘 Quando Chiedere Aiuto

### Situazioni che Richiedono Supporto

- **Perdita dati critica** senza backup
- **Repository corrotto** con errori fsck
- **History rewrite** su repository condiviso
- **Performance degradata** persistente

### Informazioni da Fornire

```bash
# Raccogli queste informazioni prima di chiedere aiuto
git --version
git status
git branch -vv
git remote -v
git config --list
git fsck
git reflog --oneline -20
```

## 📚 Risorse Aggiuntive

- [Git Recovery](https://git-scm.com/book/en/v2/Git-Internals-Maintenance-and-Data-Recovery)
- [Oh Shit, Git!](https://ohshitgit.com/)
- [Git Flight Rules](https://github.com/k88hudson/git-flight-rules)
- [Git Tips](https://github.com/git-tips/tips)

---

## 🔄 Navigazione

- [⬅️ 05 - Best Practices](05-best-practices.md)
- [🏠 README](../README.md)
- [➡️ 14 - Merge e Strategie](../../14-Merge-e-Strategie/README.md)

---

*Hai completato la gestione branch! Ora sei pronto per esplorare le strategie di merge*
