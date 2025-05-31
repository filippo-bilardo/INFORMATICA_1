# 03 - Cos'è un Branch in Git

## 📖 Spiegazione Concettuale

Un **branch** (ramo) in Git è essenzialmente un puntatore mobile a uno specifico commit. È una linea di sviluppo indipendente che ti permette di lavorare su funzionalità diverse senza interferire con il codice principale.

### Metafora dell'Albero
```
main:     A---B---C---D
                   \
feature:            E---F---G
```

- **main**: il ramo principale (tronco)
- **feature**: un ramo laterale per una nuova funzionalità
- **A,B,C,D,E,F,G**: commit individuali

## 🧠 Concetti Fondamentali

### Branch come Puntatori
```bash
# Un branch è solo un file di 40 caratteri con il SHA del commit
$ cat .git/refs/heads/main
a1b2c3d4e5f6789012345678901234567890abcd

# Quando fai un commit, il puntatore si sposta
$ git commit -m "New feature"
$ cat .git/refs/heads/main
b2c3d4e5f67890123456789012345678901abcde
```

### Vantaggi del Branching

#### 1. **Isolamento**
- Lavoro su feature senza rompere main
- Test sicuri di esperimenti
- Rollback facile se qualcosa va storto

#### 2. **Collaborazione**
- Ogni sviluppatore lavora su branch separati
- Merge coordinati quando pronti
- Evita conflitti durante lo sviluppo

#### 3. **Organizzazione**
- Feature branch per nuove funzionalità
- Hotfix branch per correzioni urgenti
- Release branch per preparare versioni

## 🔧 Sintassi e Parametri

### Comandi Fondamentali

#### Creare Branch
```bash
git branch feature-name              # Crea branch senza spostarsi
git checkout -b feature-name         # Crea e si sposta al branch
git switch -c feature-name           # Comando moderno (Git 2.23+)
```

#### Visualizzare Branch
```bash
git branch                           # Lista branch locali
git branch -r                        # Lista branch remoti
git branch -a                        # Lista tutti i branch
git branch -v                        # Con ultimo commit
```

#### Spostarsi tra Branch
```bash
git checkout branch-name             # Metodo tradizionale
git switch branch-name               # Metodo moderno
```

## 💡 Casi d'Uso Pratici

### Scenario 1: Nuova Funzionalità
```bash
# Situazione: devi aggiungere un sistema di login
git checkout -b feature-login
# Lavori sulla feature...
git add .
git commit -m "Add login form"
git commit -m "Add authentication logic"
git checkout main                    # Torna al main
git merge feature-login              # Integra la feature
```

### Scenario 2: Bug Critico
```bash
# Situazione: bug in produzione da fixare subito
git checkout -b hotfix-critical-bug
# Risolvi il bug...
git commit -m "Fix critical security bug"
git checkout main
git merge hotfix-critical-bug
git tag v1.0.1                       # Versione patch
```

### Scenario 3: Esperimento
```bash
# Situazione: vuoi provare una soluzione diversa
git checkout -b experiment-new-algorithm
# Provi l'algoritmo...
# Se non funziona:
git checkout main
git branch -D experiment-new-algorithm  # Elimina l'esperimento
```

## ⚠️ Errori Comuni

### 1. **Modifiche non Committate**
```bash
# ❌ ERRORE: provi a cambiare branch con modifiche uncommitted
$ git checkout feature-branch
error: Your local changes to the following files would be overwritten

# ✅ SOLUZIONE: commit o stash prima
$ git stash                          # Salva temporaneamente
$ git checkout feature-branch
$ git stash pop                      # Recupera le modifiche
```

### 2. **Branch Troppo Lunghi**
```bash
# ❌ PROBLEMA: branch che diverge troppo da main
main:    A---B---C---D---E---F---G
feature:      \
              H---I---J---K---L---M---N

# ✅ SOLUZIONE: rebase frequenti
git checkout feature
git rebase main                      # Riapplica i commit su F-G
```

### 3. **Nomi Branch Confusi**
```bash
# ❌ Nomi poco chiari
git checkout -b fix
git checkout -b temp
git checkout -b new-stuff

# ✅ Nomi descrittivi
git checkout -b feature-user-authentication
git checkout -b bugfix-navigation-crash
git checkout -b refactor-database-layer
```

## 🎯 Best Practices

### 1. **Convenzioni di Naming**
```bash
feature/user-authentication          # Nuove funzionalità
bugfix/login-validation-error       # Correzioni bug
hotfix/security-vulnerability       # Fix critici
release/v2.0.0                      # Preparazione release
```

### 2. **Branch di Breve Durata**
- Feature branch: 1-5 giorni
- Bugfix branch: ore/1 giorno
- Hotfix branch: ore

### 3. **Commit Atomici**
```bash
# ✅ Ogni commit dovrebbe compilare e testare
git commit -m "Add user model"
git commit -m "Add user controller"
git commit -m "Add user view"

# ❌ Evita commit che rompono il build
git commit -m "WIP: half-done feature"
```

## 🧪 Quiz di Autovalutazione

### Domanda 1
Cos'è tecnicamente un branch in Git?

**A)** Una copia completa del codice  
**B)** Un puntatore a un commit specifico  
**C)** Una cartella separata nel filesystem  
**D)** Un file compresso con le modifiche  

<details>
<summary>Risposta</summary>
**B)** Un puntatore a un commit specifico - Un branch è semplicemente un file che contiene il SHA di un commit.
</details>

### Domanda 2
Quale comando crea un nuovo branch E ci si sposta immediatamente?

**A)** `git branch feature-name`  
**B)** `git checkout feature-name`  
**C)** `git checkout -b feature-name`  
**D)** `git switch feature-name`  

<details>
<summary>Risposta</summary>
**C)** `git checkout -b feature-name` - L'opzione -b crea il branch e ci si sposta.
</details>

### Domanda 3
Quando è meglio creare un nuovo branch?

**A)** Solo per bug critici  
**B)** Per ogni singola modifica  
**C)** Per feature logicamente separate  
**D)** Mai, è troppo complicato  

<details>
<summary>Risposta</summary>
**C)** Per feature logicamente separate - Ogni funzionalità o fix significativo dovrebbe avere il suo branch.
</details>

### Domanda 4
Cosa succede se provi a cambiare branch con modifiche non committate?

**A)** Git cambia branch automaticamente  
**B)** Le modifiche vengono perse  
**C)** Git impedisce il cambio di branch  
**D)** Le modifiche vengono committate automaticamente  

<details>
<summary>Risposta</summary>
**C)** Git impedisce il cambio di branch - Devi prima commit o stash le modifiche.
</details>

## 💻 Esercizi Pratici

### Esercizio 1: Primo Branch
1. Crea un nuovo repository
2. Fai almeno 3 commit su main
3. Crea un branch chiamato "experiment"
4. Verifica di essere sul nuovo branch
5. Fai 2 commit sul branch experiment
6. Torna a main e verifica che i commit experiment non ci sono

### Esercizio 2: Branch per Feature
1. Simula lo sviluppo di una feature login
2. Crea branch "feature-login"
3. Aggiungi file: login.html, login.js, login.css
4. Fai commit separati per ogni file
5. Visualizza la storia del branch

### Esercizio 3: Gestione Errori
1. Inizia a modificare un file su main
2. Prova a cambiare branch senza commitare
3. Risolvi l'errore usando stash
4. Completa il cambio di branch
5. Recupera le modifiche

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [04 - Struttura ad Albero Git](./04-struttura-albero.md)
- **Modulo precedente**: [11 - Annullare Modifiche](../../11-Annullare-Modifiche/README.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 11-Annullare-Modifiche](../../11-Annullare-Modifiche/README.md)
- [➡️ 04-Struttura-Albero-Git](./04-struttura-albero.md)
