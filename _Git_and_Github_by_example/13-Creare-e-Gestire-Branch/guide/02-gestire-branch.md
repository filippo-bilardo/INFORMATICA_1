# 02 - Gestire Branch in Git

## 📖 Spiegazione Concettuale

La **gestione dei branch** comprende tutte le operazioni per visualizzare, modificare, rinominare ed eliminare i branch nel tuo repository. È fondamentale per mantenere un ambiente di sviluppo pulito e organizzato.

### Ciclo di Vita di un Branch

```
Creazione → Sviluppo → Review → Merge → Eliminazione
    ↓           ↓         ↓       ↓         ↓
git branch  git commit  PR/MR  git merge  git branch -d
```

## 🔧 Sintassi e Comandi

### Visualizzare Branch

```bash
# Listare branch locali
git branch

# Listare tutti i branch (locali e remoti)
git branch -a

# Listare solo branch remoti
git branch -r

# Visualizzazione dettagliata con ultimo commit
git branch -v

# Branch già mergeati
git branch --merged

# Branch non ancora mergeati
git branch --no-merged
```

### Cambiare Branch

```bash
# Con git switch (moderno)
git switch <nome-branch>
git switch main
git switch feature-login

# Con git checkout (tradizionale)
git checkout <nome-branch>
git checkout main
```

### Rinominare Branch

```bash
# Rinominare il branch corrente
git branch -m <nuovo-nome>
git branch -m feature-user-management

# Rinominare un altro branch
git branch -m <vecchio-nome> <nuovo-nome>
git branch -m feature-login feature-authentication
```

### Eliminare Branch

```bash
# Eliminazione sicura (solo se mergeato)
git branch -d <nome-branch>
git branch -d feature-completed

# Eliminazione forzata
git branch -D <nome-branch>
git branch -D feature-experimental

# Eliminare branch remoto
git push origin --delete <nome-branch>
git push origin --delete feature-old
```

## 🎯 Casi d'Uso Pratici

### 1. Controllo Branch Attivo

```bash
# Vedere su quale branch stai lavorando
$ git branch
  feature-login
* main
  develop

# L'asterisco (*) indica il branch attivo
```

### 2. Pulizia Branch Obsoleti

```bash
# 1. Vedere branch già mergeati
git branch --merged main

# 2. Eliminare i branch mergeati (tranne main)
git branch --merged main | grep -v "main" | xargs git branch -d

# 3. Verificare il risultato
git branch
```

### 3. Trovare Branch per Feature

```bash
# Cercare branch per pattern
git branch | grep feature
git branch | grep bugfix

# Con informazioni dettagliate
git branch -v | grep feature
```

### 4. Branch Tracking Status

```bash
# Vedere lo stato di tracking
git branch -vv

# Output esempio:
#   feature-api    7a8b9c0 [origin/feature-api: ahead 2] Add API endpoints
# * main           d1e2f3g [origin/main] Latest main commit
#   develop        4h5i6j7 [origin/develop: behind 1] Develop branch
```

## 📋 Pattern di Gestione

### Workflow Feature Branch

```bash
# 1. Creare feature branch
git switch -c feature-new-dashboard

# 2. Sviluppare
git add .
git commit -m "Add dashboard layout"

# 3. Push per backup/collaborazione
git push -u origin feature-new-dashboard

# 4. Quando completato, tornare a main
git switch main

# 5. Merge
git merge feature-new-dashboard

# 6. Cleanup
git branch -d feature-new-dashboard
git push origin --delete feature-new-dashboard
```

### Gestione Branch Multipli

```bash
# Scenario: più feature in sviluppo
git branch
#   feature-authentication
#   feature-payment
# * feature-notifications
#   main

# Passare tra feature rapidamente
git switch feature-payment
# lavora...
git switch feature-authentication
# lavora...
git switch feature-notifications
```

## ⚠️ Errori Comuni

### 1. Eliminare Branch con Lavoro Non Salvato

```bash
# Errore: tentare di eliminare branch non mergeato
$ git branch -d feature-important
error: The branch 'feature-important' is not fully merged.

# Soluzioni:
# A) Fare merge prima
git switch main
git merge feature-important
git branch -d feature-important

# B) Forzare eliminazione (ATTENZIONE!)
git branch -D feature-important
```

### 2. Branch Non Aggiornato

```bash
# Problema: lavorare su branch obsoleto
# Soluzione: aggiornare prima di iniziare
git switch main
git pull origin main
git switch feature-branch
git merge main  # o git rebase main
```

### 3. Nome Branch Confuso

```bash
# ❌ Nomi poco chiari
git branch temp
git branch fix
git branch new

# ✅ Nomi descrittivi
git branch feature-user-profile
git branch bugfix-login-error
git branch refactor-api-layer
```

## 💡 Best Practices

### 1. Pulizia Regolare

```bash
# Script di pulizia settimanale
#!/bin/bash
echo "Aggiornamento main..."
git switch main
git pull origin main

echo "Branch mergeati da eliminare:"
git branch --merged main | grep -v "main"

echo "Eliminazione branch mergeati..."
git branch --merged main | grep -v "main" | xargs git branch -d
```

### 2. Naming Convention Aziendale

```bash
# Convenzione con ticket/issue
git switch -c feature/TICKET-123-user-authentication
git switch -c bugfix/BUG-456-memory-leak
git switch -c hotfix/URGENT-789-security-patch

# Con nome sviluppatore
git switch -c marco/feature/new-dashboard
git switch -c sara/bugfix/validation-error
```

### 3. Branch Protection

```bash
# Non eliminare mai questi branch direttamente
# main, develop, staging, production

# Usa sempre pull request per questi branch
# Mai push diretto su branch protetti
```

## 🧪 Esercizi Pratici

### Esercizio 1: Gestione Branch Base
Crea tre branch, passa tra di essi, e poi elimina quelli non necessari:

```bash
# 1. Crea i branch
git switch -c feature-a
git switch -c feature-b  
git switch -c test-branch

# 2. Passa tra i branch
# Vai a feature-a, poi a main, poi a feature-b

# 3. Elimina test-branch
```

### Esercizio 2: Branch Cleanup
Simula uno scenario di pulizia:

```bash
# 1. Crea alcuni branch di test
# 2. Fai commit su alcuni
# 3. Merge alcuni su main
# 4. Identifica quali possono essere eliminati
# 5. Esegui la pulizia
```

### Esercizio 3: Rinominare Branch
Crea un branch con nome sbagliato e correggilo:

```bash
# 1. Crea branch con nome "temp"
# 2. Rinominalo in "feature-user-settings"
# 3. Verifica che il rename sia riuscito
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale comando mostra i branch che NON sono stati ancora mergeati?
- A) `git branch --merged`
- B) `git branch --no-merged`
- C) `git branch -unmerged`
- D) `git branch --pending`

### Domanda 2
Come elimini un branch remoto?
- A) `git branch -d origin/branch-name`
- B) `git push origin --delete branch-name`
- C) `git remote delete branch-name`
- D) `git branch -r -d branch-name`

### Domanda 3
Cosa indica l'asterisco (*) nell'output di `git branch`?
- A) Il branch più recente
- B) Il branch con più commit
- C) Il branch attualmente attivo
- D) Il branch principale

### Risposte
1. B - `--no-merged` mostra branch non mergeati
2. B - `git push origin --delete` elimina branch remoti
3. C - L'asterisco indica il branch corrente

## 📚 Approfondimenti

### Branch Tracking Dettagliato

```bash
# Informazioni complete sui branch
git for-each-ref --format='%(refname:short) %(upstream:short)' refs/heads

# Branch che traccia un remoto specifico
git branch -u origin/main local-main

# Rimuovere tracking
git branch --unset-upstream
```

### Branch Remoti

```bash
# Sincronizzare branch remoti
git fetch origin

# Vedere branch remoti eliminati
git remote prune origin

# Creare branch locale da remoto
git switch -c local-feature origin/remote-feature
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./01-creare-branch.md)
- [➡️ Prossima Guida](./03-switch-vs-checkout.md)

### Risorse Esterne
- [Git Branch Management](https://git-scm.com/book/en/v2/Git-Branching-Branch-Management)
- [Git Switch vs Checkout](https://stackoverflow.com/questions/57265785/whats-the-difference-between-git-switch-and-git-checkout-branch)

---

**Prossimo passo**: [Switch vs Checkout](./03-switch-vs-checkout.md) - Comprendi le differenze tra i due approcci
