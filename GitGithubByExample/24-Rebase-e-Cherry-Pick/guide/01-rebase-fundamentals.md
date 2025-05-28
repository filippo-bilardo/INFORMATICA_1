# Rebase Fundamentals

## 📖 Introduzione al Rebase

Il rebase è uno degli strumenti più potenti di Git per la manipolazione della cronologia dei commit. A differenza del merge, che crea un nuovo commit per unire due branch, il rebase "riproduce" i commit di un branch su un altro, mantenendo una cronologia lineare e pulita.

## 🎯 Cosa Imparerai

- La filosofia e i principi del rebase
- Differenze fondamentali tra merge e rebase
- Sintassi e opzioni del comando rebase
- Scenari di utilizzo appropriati
- Precauzioni e limitazioni
- Best practices per un rebase sicuro

## 🔄 Come Funziona il Rebase

### Concetto Base

```
Situazione iniziale:
      A---B---C feature
     /
D---E---F---G main

Dopo git rebase main:
              A'--B'--C' feature
             /
D---E---F---G main
```

Il rebase:
1. **Trova il commit comune** tra i due branch
2. **Salva temporaneamente** tutti i commit del branch corrente
3. **Resetta il branch** alla posizione del branch target
4. **Riapplica uno per uno** i commit salvati
5. **Crea nuovi commit** con lo stesso contenuto ma nuovi hash

### Rebase vs Merge: Confronto Visivo

```bash
# MERGE: Mantiene la cronologia ramificata
*   a1b2c3d Merge pull request #123 from feature/login
|\  
| * d4e5f6g Add password validation
| * g7h8i9j Implement login form
|/  
* j1k2l3m Update main branch

# REBASE: Cronologia lineare
* d4e5f6g' Add password validation (rebase)
* g7h8i9j' Implement login form (rebase)
* j1k2l3m Update main branch
```

## 📋 Sintassi e Comandi Base

### Rebase Semplice

```bash
# Rebase del branch corrente su main
git rebase main

# Rebase specifico di un branch
git rebase main feature-branch

# Rebase su un commit specifico
git rebase abc1234

# Rebase con specifica del commit di partenza
git rebase --onto target start end
```

### Opzioni Principali

```bash
# Rebase interattivo (molto potente)
git rebase -i HEAD~3

# Continua rebase dopo risoluzione conflitti
git rebase --continue

# Salta commit problematico
git rebase --skip

# Abbandona il rebase
git rebase --abort

# Mantiene i merge commit
git rebase --preserve-merges

# Rebase con strategia di merge specifica
git rebase -X theirs main
git rebase -X ours main
```

## 🛠️ Anatomia di un Rebase

### Passo 1: Preparazione

```bash
# Stato iniziale
git log --oneline --graph
* 5a1b2c3 (feature) Add user profile
* 4d5e6f7 Implement authentication
* 3g4h5i6 Setup user model
* 2j7k8l9 (main) Update documentation
* 1m2n3o4 Initial project setup
```

### Passo 2: Esecuzione Rebase

```bash
git checkout feature
git rebase main

# Git internamente esegue:
# 1. git checkout main
# 2. git cherry-pick 3g4h5i6
# 3. git cherry-pick 4d5e6f7
# 4. git cherry-pick 5a1b2c3
```

### Passo 3: Risultato

```bash
git log --oneline --graph
* 8x9y0z1 (feature) Add user profile
* 7w8x9y0 Implement authentication
* 6v7w8x9 Setup user model
* 2j7k8l9 (main) Update documentation
* 1m2n3o4 Initial project setup
```

## ⚠️ Regola d'Oro del Rebase

### ❌ MAI fare rebase su branch pubblici/condivisi

```bash
# PERICOLOSO - Non fare mai questo:
git checkout main
git rebase feature-branch

# Se altri sviluppatori hanno già fatto pull di main,
# il rebase creerà problemi di sincronizzazione!
```

### ✅ Rebase sicuro su branch locali

```bash
# SICURO - Rebase del proprio branch di feature:
git checkout my-feature
git rebase main

# Solo branch su cui lavori tu!
```

## 🎯 Scenari di Utilizzo

### 1. Aggiornamento Branch Feature

```bash
# Situazione: main ha nuovi commit
git checkout feature-login
git rebase main

# Risultato: feature-login ora include le ultime modifiche di main
```

### 2. Pulizia della Cronologia

```bash
# Prima del merge finale, pulisci i commit
git checkout feature-payment
git rebase -i HEAD~5

# Combina/riordina/modifica i commit prima del merge
```

### 3. Sincronizzazione con Upstream

```bash
# Aggiorna il fork con il repository originale
git checkout main
git pull upstream main
git checkout my-feature
git rebase main
```

## 🔧 Risoluzione Conflitti Durante Rebase

### Conflitto Standard

```bash
git rebase main
# Auto-merging file.js
# CONFLICT (content): Merge conflict in file.js
# error: could not apply abc1234... My commit message

# 1. Risolvi i conflitti manualmente
vim file.js

# 2. Aggiungi file risolti
git add file.js

# 3. Continua il rebase
git rebase --continue
```

### Script per Conflitti Complessi

```bash
#!/bin/bash
# rebase-helper.sh - Script per assistere nel rebase

echo "🔄 Stato del rebase:"
git status --porcelain

echo "📝 File in conflitto:"
git diff --name-only --diff-filter=U

echo "🛠️ Per ogni file in conflitto:"
echo "  1. Modifica il file"
echo "  2. git add <file>"
echo "  3. git rebase --continue"

echo "⚠️ Opzioni disponibili:"
echo "  git rebase --continue (dopo risoluzione)"
echo "  git rebase --skip (salta questo commit)"
echo "  git rebase --abort (annulla tutto)"
```

## 📊 Monitoraggio e Debug

### Verifica del Rebase

```bash
# Controlla la cronologia dopo il rebase
git log --oneline --graph --decorate

# Verifica che non ci siano problemi
git fsck --full

# Confronta con backup
git diff backup-branch
```

### Backup Prima del Rebase

```bash
# Crea sempre un backup!
git branch backup-$(date +%Y%m%d-%H%M%S)

# Oppure usa reflog per recuperare
git reflog

# Ripristina da reflog se necessario
git reset --hard HEAD@{5}
```

## 🏆 Best Practices

### ✅ Pratiche Consigliate

1. **Backup sempre**: Crea un branch di backup prima del rebase
2. **Rebase frequente**: Tieni aggiornato il branch feature
3. **Commit atomici**: Un commit = una modifica logica
4. **Messaggi chiari**: Descrizioni precise per ogni commit
5. **Test prima e dopo**: Verifica che tutto funzioni

### ❌ Errori Comuni da Evitare

1. **Rebase su branch condivisi**: Causa problemi a tutto il team
2. **Rebase senza backup**: Rischio perdita di lavoro
3. **Commit troppo grandi**: Difficili da gestire in caso di conflitti
4. **Rebase di merge commit**: Può causare duplicazioni
5. **Force push su main**: Mai fare force push su branch principali

## 🔄 Workflow Rebase Avanzato

### Rebase con Strategia "Onto"

```bash
# Sposta commit da un branch all'altro
git rebase --onto main server client

# Prima:  A---B---E---F---G  client
#        /         /
#       /     C---D  server
#      /     /
# H---I---J---K  main

# Dopo:   A---B---E'--F'--G'  client
#        /
# H---I---J---K  main
#            \
#             C---D  server
```

### Rebase Condizionale

```bash
#!/bin/bash
# smart-rebase.sh

BRANCH=$(git branch --show-current)
MAIN_BRANCH="main"

if [ "$BRANCH" = "$MAIN_BRANCH" ]; then
    echo "❌ Non posso fare rebase su $MAIN_BRANCH"
    exit 1
fi

# Controlla se ci sono modifiche non committate
if ! git diff-index --quiet HEAD --; then
    echo "⚠️ Hai modifiche non committate. Commit prima del rebase."
    exit 1
fi

# Backup automatico
BACKUP_BRANCH="backup-$BRANCH-$(date +%Y%m%d-%H%M%S)"
git branch "$BACKUP_BRANCH"
echo "💾 Backup creato: $BACKUP_BRANCH"

# Esegui rebase
echo "🔄 Eseguendo rebase su $MAIN_BRANCH..."
if git rebase "$MAIN_BRANCH"; then
    echo "✅ Rebase completato con successo!"
    echo "🗑️ Rimuovi backup con: git branch -D $BACKUP_BRANCH"
else
    echo "❌ Rebase fallito. Risolvi i conflitti e usa 'git rebase --continue'"
    echo "🔄 Oppure annulla con 'git rebase --abort'"
fi
```

## 📈 Metriche e Analisi

### Analisi Pre-Rebase

```bash
# Conta commit da mergiare
git rev-list --count main..feature

# Mostra dimensione dei cambiamenti
git diff --stat main..feature

# Identifica file modificati
git diff --name-only main..feature
```

### Verifica Post-Rebase

```bash
# Verifica integrità
git log --oneline --graph | head -20

# Controlla che non ci siano regressioni
git diff main~5..main --name-only

# Test automatico post-rebase
npm test || echo "⚠️ Test falliti dopo rebase!"
```

## 🎓 Quiz di Verifica

### Domanda 1
**Quale comando permette di fare rebase interattivo degli ultimi 3 commit?**

a) `git rebase -i 3`
b) `git rebase -i HEAD~3` ✅
c) `git rebase --interactive 3`
d) `git interactive-rebase 3`

**Spiegazione**: `HEAD~3` indica "3 commit prima del HEAD attuale"

### Domanda 2
**Quando NON dovresti mai fare rebase?**

a) Su un branch feature locale
b) Su commit già pushati e condivisi ✅
c) Prima di un merge
d) Per pulire la cronologia

**Spiegazione**: Il rebase modifica gli hash dei commit, causando problemi di sincronizzazione per altri sviluppatori.

### Domanda 3
**Cosa succede durante un rebase?**

a) Si crea un merge commit
b) I commit vengono copiati con nuovi hash ✅
c) La cronologia rimane invariata
d) Si perdono i commit originali

**Spiegazione**: Il rebase ricrea i commit sulla nuova base, generando nuovi hash SHA.

## 📚 Risorse Aggiuntive

### Documentazione Ufficiale
- [Git Rebase Documentation](https://git-scm.com/docs/git-rebase)
- [Pro Git Book - Chapter 3.6](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)

### Tool e Utilities
- **GitKraken**: Interfaccia grafica per rebase complessi
- **SourceTree**: Visualizzazione grafica della cronologia
- **VS Code Git Graph**: Estensione per visualizzare il grafo dei commit

### Letture Avanzate
- [Rebase vs Merge: Best Practices](https://www.atlassian.com/git/tutorials/merging-vs-rebasing)
- [Interactive Rebase Tutorial](https://thoughtbot.com/blog/git-interactive-rebase-squash-amend-rewriting-history)

---

## 🔄 Navigazione

**Precedente**: [23 - Git Flow e Strategie](../23-Git-Flow-e-Strategie/README.md)  
**Successivo**: [02 - Interactive Rebase](./02-interactive-rebase.md)  
**Indice**: [README principale](../README.md)
