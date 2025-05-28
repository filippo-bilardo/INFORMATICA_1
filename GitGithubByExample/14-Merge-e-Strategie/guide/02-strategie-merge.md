# 02 - Strategie di Merge in Git

## 📖 Spiegazione Concettuale

Git offre diverse **strategie di merge** per gestire l'integrazione dei branch in modi diversi. Ogni strategia ha vantaggi specifici e si adatta a workflow e situazioni particolari.

### Panoramica delle Strategie

```
1. FAST-FORWARD      → Storia lineare, semplice
2. NO-FAST-FORWARD   → Preserva struttura branch
3. SQUASH            → Compatta commit in uno
4. REBASE-MERGE      → Storia lineare senza merge commit
```

## 🚀 Fast-Forward Strategy

### Caratteristiche
- **Veloce e pulito**: Sposta semplicemente il puntatore
- **Storia lineare**: Non crea merge commit
- **Ideale per**: Hotfix, small features, aggiornamenti semplici

### Quando Usare
```bash
# Scenario ideale per fast-forward
main:    A ← B ← C
              ↖
hotfix:        D ← E

# Risultato fast-forward
main:    A ← B ← C ← D ← E
```

### Implementazione

```bash
# Fast-forward automatico (default quando possibile)
git merge feature-branch

# Forzare fast-forward (fallisce se non possibile)
git merge --ff-only feature-branch

# Verifica se è possibile fast-forward
git merge-base --is-ancestor feature-branch main
echo $?  # 0 = possibile, 1 = non possibile
```

### Esempio Pratico

```bash
# Setup hotfix scenario
git switch main
git switch -c hotfix-typo

echo "Fixed typo in documentation" > fix.txt
git add fix.txt
git commit -m "Fix typo in user manual"

# Fast-forward merge
git switch main
git merge hotfix-typo
# Output: Fast-forward

# Verifica risultato
git log --oneline -3
# Storia lineare senza merge commit
```

## 🌳 No-Fast-Forward Strategy

### Caratteristiche
- **Preserva contesto**: Mantiene visibile la struttura dei branch
- **Tracciabilità**: Chiaro quando feature sono state integrate
- **Merge commit**: Sempre creato, anche se non necessario

### Quando Usare
```bash
# Scenario per no-fast-forward
main:    A ← B ← C ← F (merge commit)
              ↖     ↗
feature:       D ← E

# Vantaggi:
# - Chiaro che D,E erano una feature
# - Facile revert dell'intera feature
# - Tracciabilità del lavoro
```

### Implementazione

```bash
# Forza no-fast-forward
git merge --no-ff feature-branch

# Con messaggio personalizzato
git merge --no-ff feature-branch -m "Merge feature: user authentication"

# Configurazione globale
git config --global merge.ff false
```

### Esempio Pratico

```bash
# Setup feature scenario
git switch main
git switch -c feature-login-form

echo "Login form HTML" > login.html
git add login.html
git commit -m "Add login form structure"

echo "Login form CSS" > login.css
git add login.css
git commit -m "Add login form styles"

# No-fast-forward merge
git switch main
git merge --no-ff feature-login-form -m "Merge feature: login form"

# Verifica risultato
git log --oneline --graph -5
# * abc1234 Merge feature: login form
# |\
# | * def5678 Add login form styles
# | * ghi9012 Add login form structure
# |/
# * jkl3456 Previous main commit
```

## 🗜️ Squash Strategy

### Caratteristiche
- **Storia pulita**: Tutti i commit della feature diventano uno
- **Controllo granulare**: Possibilità di editare il commit message
- **Perdita dettagli**: Storia dettagliata della feature viene persa

### Quando Usare
```bash
# Prima del squash:
feature: D ← E ← F ← G ← H (5 commit messy)

# Dopo squash merge:
main: A ← B ← C ← I (1 commit pulito)
```

### Implementazione

```bash
# Squash merge
git merge --squash feature-branch
git commit -m "Feature: complete user authentication system"

# Nota: dopo squash, devi fare commit manuale
# I commit originali non vengono automaticamente committati
```

### Esempio Pratico

```bash
# Setup feature con commit multipli
git switch main
git switch -c feature-user-settings

echo "Settings page" > settings.html
git add settings.html
git commit -m "WIP: settings page"

echo "Settings form" >> settings.html
git add settings.html
git commit -m "Add settings form"

echo "Validation logic" > settings.js
git add settings.js
git commit -m "Add validation"

echo "Bug fix" >> settings.js
git add settings.js
git commit -m "Fix validation bug"

echo "Final touches" >> settings.html
git add settings.html
git commit -m "Polish UI"

# Squash merge
git switch main
git merge --squash feature-user-settings

# Verifica staging area
git status
# Tutti i cambiamenti sono staged

# Commit con messaggio pulito
git commit -m "feat: implement user settings page

- Add settings page with form
- Implement validation logic
- Polish user interface"

# Verifica risultato
git log --oneline -3
# Solo un commit pulito per tutta la feature
```

## 🔄 Rebase e Merge

### Caratteristiche
- **Storia lineare**: Nessun merge commit
- **Commit preservati**: Mantiene commit individuali
- **Riordino cronologico**: Commit riapplicati cronologicamente

### Workflow Rebase-Merge

```bash
# Invece di merge diretto
git switch feature-branch
git rebase main        # Riapplica feature su main aggiornato
git switch main
git merge feature-branch  # Fast-forward merge
```

### Esempio Pratico

```bash
# Setup scenario con divergenza
git switch main
echo "Main work" > main-work.txt
git add main-work.txt
git commit -m "Work on main"

git switch feature-api
echo "API work" > api-work.txt
git add api-work.txt
git commit -m "API development"

echo "More API work" >> api-work.txt
git add api-work.txt
git commit -m "API refinements"

# Rebase feature su main aggiornato
git rebase main

# Merge pulito (fast-forward)
git switch main
git merge feature-api

# Risultato: storia lineare
git log --oneline --graph -5
```

## 📊 Confronto Strategie

| Strategia | Storia | Tracciabilità | Pulizia | Uso Ideale |
|-----------|--------|---------------|---------|------------|
| **Fast-Forward** | Lineare | Bassa | Alta | Hotfix, piccole feature |
| **No-Fast-Forward** | Branched | Alta | Media | Feature importanti |
| **Squash** | Lineare | Bassa | Molto Alta | Feature sperimentali |
| **Rebase-Merge** | Lineare | Media | Alta | Workflow lineare |

## 🎯 Scegliere la Strategia Giusta

### Per Team Piccoli
```bash
# Strategia semplice: fast-forward quando possibile
git config --global merge.ff true

# Per feature importanti: no-fast-forward
git merge --no-ff feature-major-refactor
```

### Per Team Grandi
```bash
# Strategia strutturata: sempre no-fast-forward
git config --global merge.ff false

# Per cleanup: squash feature sperimentali
git merge --squash experiment-new-ui
```

### Per Open Source
```bash
# Strategia mista:
# - Fast-forward per piccoli fix
# - No-fast-forward per feature
# - Squash per cleanup

# Esempio workflow
if [ "$(git rev-list --count main..feature-branch)" -eq 1 ]; then
    git merge feature-branch  # Fast-forward per single commit
else
    git merge --no-ff feature-branch  # No-FF per multiple commit
fi
```

## 🛠️ Configurazione Avanzata

### Configurazioni Globali

```bash
# Configurazione merge strategy
git config --global merge.ff false           # Sempre no-fast-forward
git config --global merge.ff only            # Solo fast-forward
git config --global merge.ff true            # Auto (default)

# Configurazione merge tool
git config --global merge.tool vscode
git config --global merge.conflictstyle diff3

# Configurazione commit message per merge
git config --global merge.log true           # Include commit list
```

### Alias Utili

```bash
# Alias per strategie diverse
git config --global alias.ffmerge 'merge --ff-only'
git config --global alias.noffmerge 'merge --no-ff'
git config --global alias.squashmerge 'merge --squash'

# Uso degli alias
git ffmerge hotfix-branch
git noffmerge feature-branch
git squashmerge experiment-branch
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale strategia preserva meglio la tracciabilità delle feature?
- A) Fast-forward
- B) No-fast-forward
- C) Squash
- D) Rebase-merge

### Domanda 2
Quando useresti squash merge?
- A) Per hotfix critici
- B) Per feature importanti
- C) Per cleanup di commit messy
- D) Per mantenere storia dettagliata

### Domanda 3
Quale configurazione impedisce fast-forward?
- A) `merge.ff true`
- B) `merge.ff false`
- C) `merge.ff only`
- D) `merge.ff auto`

### Risposte
1. B - No-fast-forward mantiene visibile la struttura dei branch
2. C - Squash è ideale per pulire commit disordinati
3. B - `merge.ff false` forza sempre la creazione di merge commit

## 📚 Approfondimenti

### Workflow Complessi

```bash
# GitHub Flow con squash
git switch -c feature-branch
# ... sviluppo ...
git push origin feature-branch
# ... code review ...
git merge --squash feature-branch  # Localmente

# GitLab Flow con merge commit
git merge --no-ff feature-branch
```

### Automatizzazione

```bash
# Script per scegliere strategia automaticamente
#!/bin/bash
COMMITS=$(git rev-list --count main..feature-branch)

if [ $COMMITS -eq 1 ]; then
    git merge feature-branch  # Fast-forward
elif [ $COMMITS -lt 5 ]; then
    git merge --no-ff feature-branch  # Preserve branch
else
    echo "Consider squash merge for $COMMITS commits"
    git merge --squash feature-branch
fi
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./01-introduzione-merge.md)
- [➡️ Prossima Guida](./03-merge-tool-configurazione.md)

### Risorse Esterne
- [Git Merge Strategies](https://git-scm.com/docs/merge-strategies)
- [Pro Git Book: Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging)

---

**Prossimo passo**: [Configurazione Merge Tool](./03-merge-tool-configurazione.md) - Impara a configurare strumenti per gestire i merge
