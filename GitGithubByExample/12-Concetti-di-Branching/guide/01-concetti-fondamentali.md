# 01 - Concetti Fondamentali di Branching

## 📖 Spiegazione Concettuale

Il **branching** è una delle funzionalità più potenti di Git. Un branch (ramo) è essenzialmente un puntatore mobile a un commit specifico che permette di sviluppare funzionalità, correggere bug o sperimentare senza influenzare il codice principale.

### Perché i Branch sono Importanti?

Immagina di sviluppare un'applicazione web:
- **Branch main**: Versione stabile in produzione
- **Branch feature/login**: Sviluppo sistema di login
- **Branch bugfix/header**: Correzione bug nell'header
- **Branch experiment/new-ui**: Sperimentazione nuova interfaccia

Ogni sviluppatore può lavorare su aspetti diversi simultaneamente senza conflitti.

## 🌳 Anatomia di un Branch

### Struttura Interna
```
commit A ← commit B ← commit C ← main (branch)
                ↑
              HEAD (puntatore al branch corrente)
```

### Branch come Puntatori
```
commit A ← commit B ← commit C ← main
                ↑
                └── feature/login (nuovo branch)
```

Quando crei un nuovo branch, Git:
1. Crea un nuovo puntatore al commit corrente
2. Non copia i file (efficiente!)
3. Permette sviluppo parallelo

## 🔧 Tipi di Branch

### 1. **Main/Master Branch**
- Branch principale del progetto
- Contiene il codice stabile
- Di solito corrisponde alla versione in produzione

### 2. **Feature Branch**
- Per sviluppare nuove funzionalità
- Naming: `feature/nome-funzionalità`
- Es: `feature/user-authentication`, `feature/shopping-cart`

### 3. **Bugfix Branch**
- Per correggere bug
- Naming: `bugfix/descrizione` o `fix/issue-number`
- Es: `bugfix/login-error`, `fix/issue-123`

### 4. **Hotfix Branch**
- Per correzioni urgenti in produzione
- Naming: `hotfix/descrizione`
- Es: `hotfix/security-patch`, `hotfix/critical-bug`

### 5. **Development Branch**
- Branch di integrazione per lo sviluppo
- Naming: `develop` o `dev`
- Dove confluiscono i feature branch prima di andare in main

### 6. **Release Branch**
- Per preparare una nuova release
- Naming: `release/versione`
- Es: `release/v1.2.0`, `release/2024.1`

## 💡 Casi d'Uso Pratici

### Scenario 1: Sviluppo Feature
```bash
# Situazione: Devo aggiungere un sistema di commenti
git checkout main
git pull origin main
git checkout -b feature/comment-system

# Sviluppo...
git add .
git commit -m "Add comment form HTML structure"
git commit -m "Add comment validation logic"
git commit -m "Add comment persistence to database"

# Quando finito, merge in main
git checkout main
git merge feature/comment-system
```

### Scenario 2: Bug Fix Urgente
```bash
# Bug critico scoperto in produzione
git checkout main
git checkout -b hotfix/payment-error

# Fix rapido...
git add payment.js
git commit -m "Fix payment validation error"

# Deploy immediato
git checkout main
git merge hotfix/payment-error
git tag v1.0.1
git push origin main --tags
```

### Scenario 3: Sperimentazione
```bash
# Voglio provare una nuova libreria UI
git checkout -b experiment/new-ui-library

# Sperimento liberamente...
git add .
git commit -m "Test new UI library integration"

# Se non funziona, posso semplicemente cancellare il branch
git checkout main
git branch -D experiment/new-ui-library
```

### Scenario 4: Collaborazione Team
```bash
# Sviluppatore A lavora su login
git checkout -b feature/login-system

# Sviluppatore B lavora su dashboard  
git checkout -b feature/user-dashboard

# Sviluppatore C corregge bug
git checkout -b bugfix/mobile-layout

# Ognuno lavora indipendentemente, poi si integra
```

## 🏗️ Workflow di Branching

### Git Flow (Workflow Complesso)
```
main ────●────●────●────●─── (produzione)
          \         /
develop ──●─●─●─●─●─●─●─●─── (integrazione)
           \     /   \
feature     ●───●     ●─●─── (funzionalità)
```

### GitHub Flow (Workflow Semplice)
```
main ──●────●────●────●─── (produzione)
        \  /    /    /
feature  ●●    ●●   ●●─── (feature branch)
```

### Forking Workflow
```
Original Repo ──●────●────●──
                 \    \    \
Fork A ──────────●────●────●──
Fork B ──────────●────●────●──
```

## ⚠️ Errori Comuni

### 1. **Branch Troppo Longevi**
```bash
# ❌ CATTIVO: Feature branch che vive per mesi
git checkout -b feature/mega-refactor
# ... 3 mesi dopo, impossibile fare merge

# ✅ BUONO: Feature piccoli e frequenti
git checkout -b feature/update-header
git checkout -b feature/add-footer
git checkout -b feature/improve-navigation
```

### 2. **Naming Inconsistente**
```bash
# ❌ CATTIVI nomi
git checkout -b fix
git checkout -b test123
git checkout -b marco-changes

# ✅ BUONI nomi
git checkout -b feature/user-profile
git checkout -b bugfix/login-validation
git checkout -b hotfix/security-patch
```

### 3. **Non Sincronizzare con Main**
```bash
# ❌ ERRORE: Branch che diverge troppo
git checkout feature/old-branch
# ... main ha 50 commit in più

# ✅ SOLUZIONE: Sync regolare
git checkout feature/my-branch
git rebase main  # Oppure merge main
```

### 4. **Dimenticare di Cambiare Branch**
```bash
# ❌ ERRORE: Committare nel branch sbagliato
git checkout main
git commit -m "Add experimental feature"  # Oops!

# ✅ PREVENZIONE: Sempre verificare
git branch  # Mostra branch corrente
git status  # Mostra anche il branch
```

## 🎯 Best Practices

### 1. **Naming Convention**
```bash
# Struttura: tipo/descrizione-breve
feature/user-authentication
feature/shopping-cart
bugfix/header-responsive
hotfix/security-vulnerability
chore/update-dependencies
docs/api-documentation
```

### 2. **Branch Lifecycle**
```bash
# 1. Crea da main aggiornato
git checkout main
git pull origin main
git checkout -b feature/new-feature

# 2. Sviluppa e commit frequenti
git add .
git commit -m "Clear, descriptive message"

# 3. Tieni sincronizzato
git rebase main  # Oppure merge main

# 4. Push e Pull Request
git push origin feature/new-feature

# 5. Merge e cleanup
git checkout main
git merge feature/new-feature
git branch -d feature/new-feature
git push origin --delete feature/new-feature
```

### 3. **Branch Protection**
```bash
# Su GitHub/GitLab, proteggi main:
# - Richiedi Pull Request
# - Richiedi review del codice
# - Richiedi CI/CD green
# - Non permettere force push
```

### 4. **Commit Message nei Branch**
```bash
# Nel branch, messaggi possono essere più dettagliati
git commit -m "feature/login: Add password validation

- Implement minimum length requirement
- Add special character validation
- Include password strength meter
- Add unit tests for validation logic

Refs: #123"
```

## 🧪 Quiz di Autovalutazione

**1. Cos'è un branch in Git?**
- a) Una copia completa del repository
- b) Un puntatore mobile a un commit specifico
- c) Un file di configurazione
- d) Una cartella separata

**2. Quale naming convention è migliore?**
- a) `branch1`, `branch2`, `branch3`
- b) `feature/user-login`, `bugfix/header-issue`
- c) `giovanni-lavori`, `test-roba`
- d) `fix`, `new`, `update`

**3. Quando dovrei creare un nuovo branch?**
- a) Solo per bug critici
- b) Per ogni nuova funzionalità o bug fix
- c) Una volta al mese
- d) Mai, meglio lavorare su main

**4. Cosa succede quando creo un nuovo branch?**
- a) Git copia tutti i file
- b) Git crea solo un nuovo puntatore
- c) Git rallenta il repository
- d) Git crea un backup automatico

<details>
<summary>🔍 Risposte</summary>

1. **b)** Un puntatore mobile a un commit specifico
2. **b)** `feature/user-login`, `bugfix/header-issue`
3. **b)** Per ogni nuova funzionalità o bug fix
4. **b)** Git crea solo un nuovo puntatore

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Comprensione Branch
1. Crea un repository di test
2. Fai alcuni commit su main
3. Crea un branch `feature/test`
4. Verifica che entrambi i branch puntino allo stesso commit
5. Usa `git log --oneline --graph --all` per visualizzare

### Esercizio 2: Naming Convention
1. Crea branch con nomi appropriati per:
   - Aggiungere sistema login
   - Correggere bug nel footer
   - Sperimentare nuova libreria
   - Correzione urgente di sicurezza
2. Lista tutti i branch creati

### Esercizio 3: Workflow Simulation
1. Simula uno scenario di sviluppo:
   - Main con codice base
   - Feature branch per nuova funzionalità
   - Bugfix branch per correzione
   - Commit su entrambi
2. Visualizza la storia con graph

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [02 - Creare e Gestire Branch](02-creare-gestire-branch.md)
- **Modulo precedente**: [10 - Annullare Modifiche](../../10-Annullare-Modifiche/README.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 10-Annullare-Modifiche](../../10-Annullare-Modifiche/README.md)
- [➡️ 12-Creare-e-Gestire-Branch](../../12-Creare-e-Gestire-Branch/README.md)
