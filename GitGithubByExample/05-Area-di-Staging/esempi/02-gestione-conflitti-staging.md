# 02 - Gestione Conflitti in Staging

## 📖 Scenario

Ti trovi in una situazione complessa durante lo sviluppo:
- Hai modifiche locali in staging area
- Un collega ha pushato modifiche che confliggono con le tue
- Devi integrare le sue modifiche mantenendo il tuo lavoro in staging
- Vuoi evitare di perdere la tua attenta organizzazione dei commit

## 🎯 Obiettivo

Imparare a gestire conflitti preservando l'organizzazione della staging area e risolvendo situazioni complesse di merge.

## 🚀 Setup Scenario

### Step 1: Crea Repository Condiviso
```bash
# Repository centrale (simula GitHub)
mkdir shared-repo.git
cd shared-repo.git
git init --bare

cd ..

# Clone per sviluppatore A (tu)
git clone shared-repo.git developer-a
cd developer-a

# Setup iniziale
mkdir src tests
cat > src/user-service.js << 'EOF'
class UserService {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(user => user.id === id);
    }
}

module.exports = UserService;
EOF

git add .
git commit -m "Initial user service"
git push origin main

cd ..

# Clone per sviluppatore B (collega)
git clone shared-repo.git developer-b
```

### Step 2: Sviluppatore B fa modifiche e push
```bash
cd developer-b

# Il tuo collega aggiunge validazione
cat > src/user-service.js << 'EOF'
class UserService {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        // Colleague's addition: validation
        if (!user.email || !user.name) {
            throw new Error('User must have email and name');
        }
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(user => user.id === id);
    }

    // Colleague's addition: new method
    deleteUser(id) {
        this.users = this.users.filter(user => user.id !== id);
    }
}

module.exports = UserService;
EOF

git add .
git commit -m "Add user validation and delete functionality"
git push origin main

cd ../developer-a
```

### Step 3: Tu fai modifiche in parallelo (non sai del push del collega)
```bash
# Tu aggiungi features diverse e le organizzi in staging

# Modifica 1: Aggiungi search functionality  
cat > src/user-service.js << 'EOF'
class UserService {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        // Your addition: generate ID
        user.id = this.generateId();
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(user => user.id === id);
    }

    // Your addition: search functionality
    searchUsers(query) {
        return this.users.filter(user => 
            user.name.toLowerCase().includes(query.toLowerCase()) ||
            user.email.toLowerCase().includes(query.toLowerCase())
        );
    }

    // Your addition: helper method
    generateId() {
        return Date.now().toString() + Math.random().toString(36).substr(2, 9);
    }

    // Your addition: statistics
    getUserCount() {
        return this.users.length;
    }
}

module.exports = UserService;
EOF

# Staging selettivo delle tue modifiche
git add -p src/user-service.js
# Scegli solo il metodo generateId()
git commit -m "Add automatic ID generation for users"

# Aggiungi search in staging
git add -p src/user-service.js  
# Scegli solo searchUsers()
git commit -m "Implement user search functionality"

# Rimane getUserCount() non ancora committato, ma staged
git add -p src/user-service.js
# Stage getUserCount() ma non committare ancora
```

## 🔥 Il Conflitto si Manifesta

### Step 4: Tentativo di Push
```bash
git push origin main
```

```
! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'shared-repo.git'
hint: Updates were rejected because the remote contains work that you
hint: do not have locally. You may want to first integrate the remote
hint: changes (e.g., 'git pull ...') before pushing again.
```

### Step 5: Analisi della Situazione
```bash
# Vedi cosa hai in staging
git status
# Changes to be committed:
#   modified:   src/user-service.js    (getUserCount staged)

# Vedi i tuoi commit locali
git log --oneline origin/main..HEAD
# abc1234 Implement user search functionality
# def5678 Add automatic ID generation for users

# Fetch per vedere le modifiche remote
git fetch origin

# Vedi cosa è cambiato nel remote
git log --oneline HEAD..origin/main
# ghi9012 Add user validation and delete functionality
```

## 🛠️ Risoluzione Strategica

### Strategia 1: Preserve Staging con Stash
```bash
# 1. Salva staging area
git stash push --staged -m "Save getUserCount staging"

# 2. Rebase per integrare modifiche remote
git rebase origin/main

# Risolvi conflitti che emergono...
```

### Step 6: Risoluzione Conflitti nel Rebase
```bash
# Durante il rebase, Git si ferma sui conflitti
# Auto-merging src/user-service.js
# CONFLICT (content): Merge conflict in src/user-service.js

# Vedi il file con conflitti
cat src/user-service.js
```

Il file mostrerà:
```javascript
class UserService {
    constructor() {
        this.users = [];
    }

    addUser(user) {
<<<<<<< HEAD (del collega)
        if (!user.email || !user.name) {
            throw new Error('User must have email and name');
        }
=======
        // Your addition: generate ID
        user.id = this.generateId();
>>>>>>> abc1234 (il tuo commit)
        this.users.push(user);
    }

    // ... più conflitti ...
}
```

### Step 7: Risoluzione Intelligente dei Conflitti
```bash
# Modifica manualmente il file per integrare entrambe le modifiche
cat > src/user-service.js << 'EOF'
class UserService {
    constructor() {
        this.users = [];
    }

    addUser(user) {
        // Colleague's validation (integrated)
        if (!user.email || !user.name) {
            throw new Error('User must have email and name');
        }
        
        // Your ID generation (integrated)
        user.id = this.generateId();
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(user => user.id === id);
    }

    // Your addition: search functionality
    searchUsers(query) {
        return this.users.filter(user => 
            user.name.toLowerCase().includes(query.toLowerCase()) ||
            user.email.toLowerCase().includes(query.toLowerCase())
        );
    }

    // Your addition: helper method
    generateId() {
        return Date.now().toString() + Math.random().toString(36).substr(2, 9);
    }

    // Colleague's addition: delete method
    deleteUser(id) {
        this.users = this.users.filter(user => user.id !== id);
    }
}

module.exports = UserService;
EOF

# Marca conflitto come risolto
git add src/user-service.js

# Continua rebase
git rebase --continue
```

### Step 8: Ripristina Staging Area
```bash
# Dopo il rebase completato, ripristina staging
git stash pop

# Risolvi eventuali conflitti nel stash
# Se ci sono conflitti:
git add src/user-service.js

# Ora hai:
# - I tuoi commit rebased su quelli del collega
# - getUserCount() ancora in staging area
# - Tutto integrato correttamente
```

## 🔄 Strategia Alternativa: Merge Workflow

### Alternativa con Merge
```bash
# Invece di rebase, usa merge preservando staging

# 1. Backup staging
git stash push --staged -m "Backup staging"

# 2. Pull con merge
git pull origin main

# 3. Risolvi conflitti simili al rebase
# ... risoluzione ...

# 4. Ripristina staging
git stash pop
```

## 🎯 Situazioni Complesse Avanzate

### Scenario: Conflitti in File Parzialmente Staged
```bash
# Hai un file con:
# - Modifiche staged
# - Modifiche non staged  
# - Conflitti dal pull

# Soluzione step-by-step:
git status
# Changes to be committed:
#   modified:   complex-file.js
# Changes not staged for commit:
#   modified:   complex-file.js

# 1. Salva entrambi gli stati
git stash push --staged -m "Staged changes"
git stash push -m "Unstaged changes"

# 2. Risolvi conflitti base
git pull origin main
# ... risolvi conflitti ...
git add complex-file.js
git commit -m "Merge remote changes"

# 3. Ripristina in ordine
git stash pop                 # Prima unstaged
git stash pop                 # Poi staged
# Risolvi eventuali nuovi conflitti
```

### Scenario: Conflitti Durante Interactive Rebase
```bash
# Durante rebase interattivo con staging attiva
git rebase -i HEAD~3

# Se conflitti:
# 1. Non perdere staging
git status                    # Nota cosa è staged
git stash push --staged -m "Save staging during rebase"

# 2. Risolvi conflitto
# ... edit files ...
git add .
git rebase --continue

# 3. Ripristina staging quando sicuro
git stash pop
```

## 🛡️ Prevenzione e Best Practices

### 1. Check Frequenti
```bash
# Prima di lavorare, sempre:
git fetch origin
git status
git log --oneline origin/main..HEAD    # Vedi se sei avanti
git log --oneline HEAD..origin/main    # Vedi se sei indietro
```

### 2. Workflow Sicuro per Team
```bash
# Pattern giornaliero sicuro:
git fetch origin                       # Update remote refs
git stash push --include-untracked -m "WIP: daily backup"
git pull --rebase origin main          # Integrate cleanly  
git stash pop                          # Restore work
# ... risolvi conflitti se necessario ...
```

### 3. Comunicazione Team
```bash
# Prima di push grandi cambiamenti:
git log --oneline main..HEAD | wc -l   # Conta commit da pushare
# Se > 5 commit, avvisa il team

# Push frequenti di work-in-progress:
git add -A
git commit -m "WIP: checkpoint before major changes"
git push origin feature-branch         # Non su main
```

## 📊 Recovery da Situazioni Critiche

### Recovery: Staging Area Corrotta
```bash
# Se la staging area è in stato inconsistente:
git reset --mixed HEAD                 # Reset soft staging
git status                             # Verifica stato
git add -p                             # Riorganizza tutto
```

### Recovery: Merge Abortito con Staging
```bash
# Se merge fallisce con staging attiva:
git merge --abort                      # Annulla merge
git stash list                         # Trova i tuoi stash
git stash apply stash@{0}              # Ripristina lavoro
```

### Recovery: Rebase Complicato
```bash
# Se rebase si complica:
git rebase --abort                     # Torna allo stato iniziale
git log --oneline                      # Verifica posizione
git pull --no-rebase origin main      # Merge invece di rebase
```

## 🧠 Quiz di Controllo

### Domanda 1
Hai modifiche in staging e devi fare pull. Qual è l'approccio più sicuro?

**A)** `git pull` direttamente  
**B)** `git stash --staged` poi `git pull` poi `git stash pop`  
**C)** `git reset` poi `git pull` poi rifare staging

### Domanda 2
Durante un rebase, Git si ferma per conflitti ma hai lavoro in staging. Cosa fai?

**A)** Continui il rebase ignorando staging  
**B)** `git rebase --abort` e ricomincia  
**C)** Risolvi conflitti mantenendo nota di staging, poi gestisci staging dopo

### Domanda 3
Il pattern più sicuro per evitare conflitti è:

**A)** Push frequenti di tutto  
**B)** `git fetch` + `git stash` + `git pull --rebase` + `git stash pop`  
**C)** Lavorare sempre su branch separati

---

**Risposte**: 1-B, 2-C, 3-B

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Esempio Precedente](./01-staging-selettivo.md)
- [➡️ Prossimo Esempio](./03-team-workflow.md)

---

**Prossimo passo**: [Team Workflow con Staging](./03-team-workflow.md) - Collaborazione avanzata
