# 01 - Tipi di Merge in Git

## 📖 Introduzione

Il merge è una delle operazioni fondamentali in Git che consente di unificare il lavoro svolto su branch differenti. Comprendere i diversi tipi di merge e quando utilizzarli è essenziale per mantenere una cronologia del progetto pulita e comprensibile.

## 🔄 I Tre Tipi Principali di Merge

### 1. Fast-Forward Merge

**Quando succede**: Quando il branch target non ha commit aggiuntivi dopo la creazione del feature branch.

```bash
# Situazione prima del merge
main:     A---B---C
               \
feature:        D---E
```

**Comando**:
```bash
git checkout main
git merge feature
```

**Risultato**:
```bash
main:     A---B---C---D---E
```

**Caratteristiche**:
- ✅ Cronologia lineare e pulita
- ✅ Nessun commit di merge aggiuntivo
- ❌ Si perde la traccia del branch feature

### 2. Three-Way Merge (Recursive)

**Quando succede**: Quando sia main che feature hanno commit aggiuntivi dopo la divergenza.

```bash
# Situazione prima del merge
main:     A---B---C---F---G
               \
feature:        D---E
```

**Comando**:
```bash
git checkout main
git merge feature
```

**Risultato**:
```bash
main:     A---B---C---F---G---M
               \             /
feature:        D---E-------/
```

**Caratteristiche**:
- ✅ Preserva la cronologia dei branch
- ✅ Mostra chiaramente l'integrazione
- ❌ Crea un commit di merge aggiuntivo

### 3. Squash Merge

**Quando lo usi**: Quando vuoi unificare tutti i commit di un feature branch in un singolo commit.

```bash
# Situazione prima del merge
main:     A---B---C
               \
feature:        D---E---F
```

**Comando**:
```bash
git checkout main
git merge --squash feature
git commit -m "Add complete feature X"
```

**Risultato**:
```bash
main:     A---B---C---S
```

**Caratteristiche**:
- ✅ Cronologia main molto pulita
- ✅ Un solo commit per feature
- ❌ Si perde la cronologia del feature branch
- ❌ Richiede commit manuale

## 🛠️ Controllo del Tipo di Merge

### Forzare No-Fast-Forward
```bash
git merge --no-ff feature
```
Crea sempre un commit di merge, anche quando è possibile fast-forward.

### Forzare Fast-Forward Only
```bash
git merge --ff-only feature
```
Esegue il merge solo se è possibile fast-forward, altrimenti fallisce.

### Squash Merge
```bash
git merge --squash feature
```
Combina tutti i commit del branch in uno stage pronto per commit.

## 🎯 Quando Usare Quale Strategia

### Fast-Forward: Ideale per
- 🔹 Branch personali di sviluppo
- 🔹 Branch di documentazione
- 🔹 Fix minori o refactoring semplici
- 🔹 Branch che non hanno mai avuto divergenze

### Three-Way Merge: Ideale per
- 🔹 Feature branch collaborative
- 🔹 Branch di lunga durata
- 🔹 Quando vuoi preservare la cronologia
- 🔹 Integration branch

### Squash Merge: Ideale per
- 🔹 Branch con molti commit "work in progress"
- 🔹 Cleanup della cronologia
- 🔹 Feature complete che devono apparire come un'unità
- 🔹 Branch con commit di fixing intermedi

## 📊 Confronto Visivo

```
FAST-FORWARD:
Before: main---A---B    feature---C---D
After:  main---A---B---C---D

THREE-WAY:
Before: main---A---B---E    feature---C---D
After:  main---A---B---E---M
                    \     /
                     C---D

SQUASH:
Before: main---A---B    feature---C---D
After:  main---A---B---S (S contains C+D changes)
```

## 🔍 Verifica del Tipo di Merge

### Controllare la Cronologia
```bash
# Visualizza la cronologia grafica
git log --oneline --graph

# Mostra solo merge commits
git log --merges --oneline

# Dettagli di un merge commit
git show <merge-commit-hash>
```

### Identificare il Tipo di Merge
```bash
# Controlla se un commit è un merge
git log --merges --grep="Merge" --oneline

# Mostra i parent di un merge commit
git log --pretty="%h %p %s" -1 <commit-hash>
```

## ⚡ Best Practices

### 1. **Scegli la Strategia in Base al Contesto**
```bash
# Feature branch semplice
git merge feature-simple

# Feature importante che deve essere tracciata
git merge --no-ff feature-important

# Cleanup di branch disordinato
git merge --squash feature-messy
```

### 2. **Messaggi di Merge Informativi**
```bash
# Per three-way merge
git merge feature-auth -m "Merge authentication system

- Add JWT token handling
- Implement user login/logout
- Add password validation
- Include security tests"
```

### 3. **Pre-Merge Verification**
```bash
# Verifica lo stato prima del merge
git log --oneline main..feature-branch
git diff main...feature-branch

# Test che il merge sarà clean
git merge-base main feature-branch
```

## 🚨 Problemi Comuni

### 1. **Merge Accidentale**
```bash
# Annulla l'ultimo merge (se non ancora pushato)
git reset --hard HEAD~1

# Annulla merge commit specifico
git revert -m 1 <merge-commit-hash>
```

### 2. **Branch Non Aggiornato**
```bash
# Aggiorna il branch prima del merge
git checkout feature
git merge main  # o git rebase main
git checkout main
git merge feature
```

### 3. **Conflitti Durante Merge**
```bash
# Il merge si ferma, risolvi i conflitti
git status
# ... risolvi conflitti ...
git add <file-risolti>
git commit  # completa il merge
```

## 💡 Suggerimenti Avanzati

### 1. **Merge Strategy Options**
```bash
# Usa strategia ricorsiva con opzioni
git merge -X theirs feature    # preferisce feature in caso di conflitto
git merge -X ours feature      # preferisce main in caso di conflitto
git merge -X ignore-space-change feature
```

### 2. **Merge con Hook Personalizzati**
```bash
# .git/hooks/pre-merge-commit
#!/bin/bash
echo "Verifying tests before merge..."
npm test || exit 1
```

### 3. **Merge Condizionale**
```bash
# Script per merge automatico con controlli
#!/bin/bash
if git diff --quiet main..feature; then
    echo "No changes to merge"
    exit 0
fi

if git merge-tree $(git merge-base main feature) main feature | grep -q "<<<<<<< "; then
    echo "Conflicts detected, manual intervention required"
    exit 1
fi

git merge feature
```

## 🎯 Esercizio Pratico

Prova i diversi tipi di merge:

```bash
# 1. Setup
git init merge-practice
cd merge-practice
echo "Initial" > file.txt
git add . && git commit -m "Initial commit"

# 2. Fast-forward merge
git checkout -b feature-ff
echo "Feature Fast Forward" >> file.txt
git add . && git commit -m "Add FF feature"
git checkout main
git merge feature-ff

# 3. Three-way merge
git checkout -b feature-3way
echo "Feature Three Way" >> file.txt
git add . && git commit -m "Add 3way feature"
git checkout main
echo "Main change" >> main.txt
git add . && git commit -m "Main development"
git merge feature-3way

# 4. Squash merge
git checkout -b feature-squash
echo "Squash 1" >> squash.txt && git add . && git commit -m "Squash commit 1"
echo "Squash 2" >> squash.txt && git add . && git commit -m "Squash commit 2"
git checkout main
git merge --squash feature-squash
git commit -m "Complete squash feature"

# 5. Visualizza risultato
git log --oneline --graph --all
```

## 🔗 Risorse di Approfondimento

- [Git Merge Documentation](https://git-scm.com/docs/git-merge)
- [Atlassian Merge Tutorial](https://www.atlassian.com/git/tutorials/using-branches/git-merge)
- [GitHub Flow Guide](https://guides.github.com/introduction/flow/)

---

## 📚 Prossimi Passi

Dopo aver compreso i tipi di merge, esplora:
- **[02 - Fast-Forward Merge](02-fast-forward.md)** - Approfondimento merge lineari
- **[03 - Recursive Merge](03-recursive-merge.md)** - Gestione merge complessi
- **[04 - Squash Merge](04-squash-merge.md)** - Cleanup della cronologia

---

## 📝 Riepilogo

| Tipo Merge | Pro | Contro | Quando Usare |
|------------|-----|---------|--------------|
| **Fast-Forward** | Cronologia lineare | Perde traccia branch | Branch semplici |
| **Three-Way** | Preserva cronologia | Più commit di merge | Feature collaborative |
| **Squash** | Cronologia pulita | Perde dettagli | Cleanup necessario |

**Ricorda**: La scelta del tipo di merge dipende dal contesto del progetto e dalle convenzioni del team. Non esiste una strategia universalmente migliore!
