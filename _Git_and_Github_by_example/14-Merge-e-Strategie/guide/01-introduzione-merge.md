# 01 - Introduzione al Merge in Git

## 📖 Spiegazione Concettuale

Il **merge** è il processo di combinare i cambiamenti da due o più branch in un unico branch. È una delle operazioni più fondamentali in Git per integrare il lavoro di sviluppo distribuito.

### Cosa Succede Durante un Merge

```
Prima del merge:
main:    A ← B ← C
              ↖
feature:       D ← E

Dopo il merge:
main:    A ← B ← C ← F (merge commit)
              ↖     ↗
feature:       D ← E
```

### Tipi di Merge

Git supporta diverse strategie di merge, ognuna con vantaggi specifici:

1. **Fast-Forward Merge**: Quando non ci sono commit divergenti
2. **Three-Way Merge**: Quando entrambi i branch hanno nuovi commit
3. **Squash Merge**: Combina tutti i commit in uno solo
4. **Rebase Merge**: Riapplica i commit linearmente

## 🔧 Sintassi Base del Merge

### Comando Fondamentale

```bash
# Sintassi generale
git merge <branch-da-mergiare>

# Esempio: merge di feature in main
git switch main
git merge feature-login
```

### Verifica Pre-Merge

```bash
# Controllare lo stato prima del merge
git status

# Vedere le differenze
git diff main feature-login

# Visualizzare i commit che saranno mergeati
git log main..feature-login --oneline
```

## 🎯 Fast-Forward Merge

### Quando Avviene

Un **fast-forward merge** si verifica quando il branch di destinazione non ha nuovi commit rispetto al punto di branching.

```
Situazione iniziale:
main:    A ← B ← C
              ↖
feature:       D ← E

Fast-forward result:
main:    A ← B ← C ← D ← E
feature:             ↑
```

### Esempio Pratico

```bash
# Setup scenario fast-forward
git switch main
git switch -c feature-quick-fix

# Aggiungi commit alla feature
echo "Quick fix applied" > fix.txt
git add fix.txt
git commit -m "Apply quick fix"

# Torna a main (nessun nuovo commit)
git switch main

# Fast-forward merge
git merge feature-quick-fix
# Output: "Fast-forward"
```

### Controllo Fast-Forward

```bash
# Forzare fast-forward (fallisce se non possibile)
git merge --ff-only feature-branch

# Disabilitare fast-forward (crea sempre merge commit)
git merge --no-ff feature-branch
```

## 🎯 Three-Way Merge

### Quando Avviene

Un **three-way merge** si verifica quando entrambi i branch hanno nuovi commit divergenti.

```
Situazione:
main:    A ← B ← C ← F
              ↖     ↗
feature:       D ← E

Three-way merge:
- Commit comune: B
- Tip main: F  
- Tip feature: E
- Nuovo merge commit: G
```

### Esempio Pratico

```bash
# Setup scenario three-way
git switch main
echo "Main work" >> main-file.txt
git add main-file.txt
git commit -m "Work on main branch"

git switch feature-branch
echo "Feature work" >> feature-file.txt
git add feature-file.txt
git commit -m "Work on feature branch"

# Three-way merge
git switch main
git merge feature-branch
# Git creerà automaticamente un merge commit
```

### Personalizzare Merge Commit

```bash
# Merge con messaggio personalizzato
git merge feature-branch -m "Merge feature: user authentication"

# Merge senza aprire editor
git merge feature-branch --no-edit
```

## ⚠️ Situazioni Problematiche

### 1. Modifiche Conflittuali

```bash
# Situazione di conflitto
git merge feature-branch
# Auto-merging file.txt
# CONFLICT (content): Merge conflict in file.txt
# Automatic merge failed; fix conflicts and then commit the result.
```

### 2. Merge di Branch Non Correlati

```bash
# Errore: branch senza storia comune
git merge unrelated-branch
# fatal: refusing to merge unrelated histories

# Soluzione: forzare merge
git merge unrelated-branch --allow-unrelated-histories
```

### 3. Merge su Working Directory Sporco

```bash
# Errore: modifiche non committate
git merge feature-branch
# error: Your local changes would be overwritten by merge.

# Soluzioni:
git stash              # salva temporaneamente
git add . && git commit # committa le modifiche
git checkout -- .      # scarta le modifiche
```

## 💡 Best Practices per Merge

### 1. Preparazione Pre-Merge

```bash
# Workflow consigliato
git switch main
git pull origin main           # Aggiorna main
git switch feature-branch
git merge main                 # Integra ultimi cambiamenti
# Risolvi eventuali conflitti
git switch main
git merge feature-branch       # Merge pulito
```

### 2. Verifica Post-Merge

```bash
# Dopo il merge
git log --oneline -5          # Verifica storia
git diff HEAD~1               # Verifica cambiamenti
npm test                      # Esegui test (se applicabile)
```

### 3. Cleanup Post-Merge

```bash
# Elimina branch mergeato
git branch -d feature-branch

# Elimina branch remoto
git push origin --delete feature-branch
```

## 🧪 Esempi Pratici

### Scenario 1: Feature Completata

```bash
# 1. Sviluppo feature
git switch -c feature-user-profile
echo "User profile page" > profile.html
git add profile.html
git commit -m "Add user profile page"

echo "Profile styles" > profile.css
git add profile.css
git commit -m "Add profile styles"

# 2. Merge in main
git switch main
git merge feature-user-profile

# 3. Cleanup
git branch -d feature-user-profile

echo "✅ Feature integrata con successo!"
```

### Scenario 2: Hotfix Urgente

```bash
# 1. Hotfix da main
git switch main
git switch -c hotfix-security-patch

echo "Security fix applied" > security.patch
git add security.patch
git commit -m "Apply critical security patch"

# 2. Merge urgente (fast-forward)
git switch main
git merge hotfix-security-patch

# 3. Merge anche in develop se esiste
git switch develop
git merge hotfix-security-patch

# 4. Cleanup
git branch -d hotfix-security-patch
```

## 🧠 Quiz di Verifica

### Domanda 1
Quando si verifica un fast-forward merge?
- A) Quando ci sono conflitti da risolvere
- B) Quando il branch target non ha nuovi commit
- C) Quando si usa --no-ff
- D) Quando i branch non sono correlati

### Domanda 2
Quale comando impedisce un fast-forward merge?
- A) `git merge --ff-only`
- B) `git merge --no-ff`
- C) `git merge --three-way`
- D) `git merge --force`

### Domanda 3
Cosa succede se fai merge con modifiche non committate?
- A) Il merge procede normalmente
- B) Le modifiche vengono automaticamente committate
- C) Git restituisce un errore
- D) Le modifiche vengono perse

### Risposte
1. B - Fast-forward quando target non ha nuovi commit
2. B - `--no-ff` forza la creazione di merge commit
3. C - Git impedisce il merge per proteggere le modifiche

## 📚 Approfondimenti

### Merge vs Rebase

```bash
# Merge: mantiene storia branch
git merge feature-branch
# Risultato: storia con branch visibili

# Rebase: storia lineare
git rebase feature-branch
# Risultato: storia pulita, senza branch
```

### Configurazione Merge Tool

```bash
# Configura tool per conflitti
git config --global merge.tool vimdiff
git config --global merge.tool meld
git config --global merge.tool code  # VS Code

# Usa merge tool
git mergetool
```

### Abort Merge

```bash
# Annulla merge in corso
git merge --abort

# Verifica stato
git status
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Modulo Precedente](../../12-Creare-e-Gestire-Branch/README.md)
- [➡️ Prossima Guida](./02-strategie-merge.md)

### Risorse Esterne
- [Git Merge Documentation](https://git-scm.com/docs/git-merge)
- [Understanding Git Merge](https://www.atlassian.com/git/tutorials/using-branches/git-merge)

---

**Prossimo passo**: [Strategie di Merge](./02-strategie-merge.md) - Scopri le diverse strategie di merge disponibili
