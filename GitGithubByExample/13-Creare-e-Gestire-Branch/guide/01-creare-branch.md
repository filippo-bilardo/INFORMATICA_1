# 01 - Creare Branch in Git

## 📖 Spiegazione Concettuale

La **creazione di branch** è una delle operazioni più fondamentali in Git. Un branch rappresenta una linea di sviluppo indipendente che permette di lavorare su feature o fix senza interferire con il codice principale.

### Cosa Succede Quando Crei un Branch

```
Prima della creazione:
main: A ← B ← C (HEAD)

Dopo la creazione di feature-branch:
main:          A ← B ← C
               ↑
feature-branch: (HEAD)
```

## 🔧 Sintassi e Comandi

### Comando Base per Creare Branch

```bash
# Sintassi generale
git branch <nome-branch>

# Esempio
git branch feature-login
```

### Creare e Cambiare Branch Immediatamente

```bash
# Con git checkout (metodo tradizionale)
git checkout -b <nome-branch>

# Con git switch (metodo moderno, Git 2.23+)
git switch -c <nome-branch>

# Esempi
git checkout -b feature-user-profile
git switch -c bugfix-password-reset
```

### Creare Branch da un Commit Specifico

```bash
# Da un commit specifico
git branch <nome-branch> <hash-commit>
git branch feature-legacy a1b2c3d

# Da un tag
git branch release-branch v1.0.0

# Da un altro branch
git branch new-feature existing-branch
```

## 🎯 Casi d'Uso Pratici

### 1. Sviluppare una Nuova Feature

```bash
# Creare branch per nuova funzionalità
git switch -c feature-shopping-cart

# Lavorare sulla feature
echo "Shopping cart functionality" > cart.js
git add cart.js
git commit -m "Add shopping cart component"
```

### 2. Fix di un Bug

```bash
# Creare branch per correzione
git switch -c hotfix-security-issue

# Applicare la correzione
git add .
git commit -m "Fix security vulnerability in authentication"
```

### 3. Sperimentazione

```bash
# Branch per esperimenti
git switch -c experiment-new-algorithm

# Testare liberamente senza rischi
# Se funziona: merge
# Se non funziona: elimina il branch
```

## 📋 Convenzioni per Nomi Branch

### Prefissi Comuni

```bash
# Feature
feature/user-authentication
feature/payment-integration

# Bug fix
bugfix/login-error
hotfix/critical-security-fix

# Rilasci
release/v2.1.0
release/sprint-12

# Sviluppo personale
dev/marco/new-ui
personal/sara/optimization
```

### Regole di Naming

```bash
# ✅ Buone pratiche
feature/add-search-functionality
bugfix/fix-memory-leak
release/v1.2.3

# ❌ Da evitare
feature_branch
my-branch
temp
test123
```

## ⚠️ Errori Comuni

### 1. Nome Branch già Esistente

```bash
# Errore
$ git branch feature-login
fatal: A branch named 'feature-login' already exists.

# Soluzione: controllare branch esistenti
git branch -a
# O usare nome diverso
git branch feature-login-v2
```

### 2. Caratteri Non Validi nel Nome

```bash
# ❌ Caratteri problematici
git branch "feature with spaces"
git branch feature@special#chars

# ✅ Usa invece
git branch feature-with-dashes
git branch feature_with_underscores
```

### 3. Creare Branch senza Commit

```bash
# Se non hai commit nel repository
$ git branch new-branch
fatal: Not a valid object name: 'main'.

# Soluzione: fai almeno un commit iniziale
echo "Initial commit" > README.md
git add README.md
git commit -m "Initial commit"
git branch new-branch
```

## 💡 Best Practices

### 1. Nomi Descriptivi

```bash
# ✅ Buono
git switch -c feature-user-authentication
git switch -c bugfix-payment-validation
git switch -c refactor-database-layer

# ❌ Poco chiaro
git switch -c fix
git switch -c new-stuff
git switch -c temp-branch
```

### 2. Branch di Breve Durata

```bash
# Workflow ideale per feature branch
git switch -c feature-quick-search
# ... sviluppo ...
git push origin feature-quick-search
# ... code review ...
git switch main
git merge feature-quick-search
git branch -d feature-quick-search
```

### 3. Creazione da Base Aggiornata

```bash
# Prima di creare un nuovo branch
git switch main
git pull origin main

# Poi crea il nuovo branch
git switch -c feature-new-dashboard
```

## 🧪 Esercizi Pratici

### Esercizio 1: Creazione Base
Crea un branch chiamato `feature-contact-form`:

```bash
# La tua soluzione qui
```

### Esercizio 2: Branch da Commit Specifico
Trova l'hash del penultimo commit e crea un branch chiamato `hotfix-rollback` da quel punto:

```bash
# Trova il commit
git log --oneline -5

# Crea il branch
```

### Esercizio 3: Naming Convention
Crea tre branch seguendo le convenzioni per:
- Una feature per aggiungere commenti
- Un bugfix per errore di validazione
- Un branch di release per versione 2.0

```bash
# I tuoi branch qui
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale comando crea un branch E ti sposta su di esso immediatamente?
- A) `git branch nome-branch`
- B) `git switch -c nome-branch` 
- C) `git checkout nome-branch`
- D) `git create nome-branch`

### Domanda 2
Qual è il prefisso più appropriato per un branch che corregge un bug critico in produzione?
- A) `fix/`
- B) `bugfix/`
- C) `hotfix/`
- D) `emergency/`

### Domanda 3
Cosa succede quando crei un nuovo branch?
- A) Git copia tutti i file in una nuova directory
- B) Git crea un nuovo puntatore al commit corrente
- C) Git fa il backup del branch principale
- D) Git crea automaticamente un commit

### Risposte
1. B - `git switch -c` crea e cambia branch
2. C - `hotfix/` è lo standard per correzioni critiche
3. B - Un branch è solo un puntatore, molto leggero

## 📚 Approfondimenti

### Differenza tra checkout e switch

```bash
# Metodo tradizionale (ancora valido)
git checkout -b feature-branch

# Metodo moderno (Git 2.23+)
git switch -c feature-branch

# switch è più chiaro e specifico per i branch
# checkout ha molte altre funzionalità
```

### Branch Tracking

```bash
# Creare branch che traccia un branch remoto
git switch -c feature-branch origin/feature-branch

# Equivalente con checkout
git checkout -b feature-branch origin/feature-branch
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Modulo Precedente](../../11-Concetti-di-Branching/README.md)
- [➡️ Prossima Guida](./02-gestire-branch.md)

### Risorse Esterne
- [Git Branch Documentation](https://git-scm.com/docs/git-branch)
- [Git Switch Documentation](https://git-scm.com/docs/git-switch)

---

**Prossimo passo**: [Gestire Branch](./02-gestire-branch.md) - Impara a listare, rinominare ed eliminare branch
