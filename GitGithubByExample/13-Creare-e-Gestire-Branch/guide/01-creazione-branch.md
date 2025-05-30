# Guida 1: Creazione e Gestione Branch

## Introduzione
I branch sono una delle funzionalità più potenti di Git, permettendo di sviluppare feature in parallelo, sperimentare e collaborare efficacemente.

## Creazione Branch

### Comando Base
```bash
# Crea un nuovo branch
git branch nome-branch

# Crea e passa immediatamente al nuovo branch
git checkout -b nome-branch

# Con Git 2.23+: approccio moderno
git switch -c nome-branch
```

### Esempi Pratici

**Creazione branch per nuova feature:**
```bash
# Partendo da main
git checkout main
git pull origin main
git checkout -b feature/login-system

# Verifica branch attuale
git branch
```

**Creazione branch da commit specifico:**
```bash
# Da hash commit
git checkout -b hotfix/critical-bug abc1234

# Da tag
git checkout -b release/v2.0 v1.9.0
```

## Navigazione tra Branch

### Switch vs Checkout
```bash
# Metodo tradizionale
git checkout nome-branch

# Metodo moderno (Git 2.23+)
git switch nome-branch

# Tornare al branch precedente
git switch -
```

### Controllo Stato
```bash
# Lista branch locali
git branch

# Lista tutti i branch (locali e remoti)
git branch -a

# Branch con ultimo commit
git branch -v

# Branch mergiati in main
git branch --merged main
```

## Gestione Branch

### Rinominare Branch
```bash
# Rinomina branch corrente
git branch -m nuovo-nome

# Rinomina branch specifico
git branch -m vecchio-nome nuovo-nome
```

### Eliminazione Branch
```bash
# Elimina branch mergiato (sicuro)
git branch -d nome-branch

# Forza eliminazione (attenzione!)
git branch -D nome-branch

# Elimina branch remoto
git push origin --delete nome-branch
```

## Branch Remoti

### Tracking Branch
```bash
# Crea branch che traccia remote
git checkout -b local-branch origin/remote-branch

# Imposta tracking per branch esistente
git branch -u origin/remote-branch

# Verifica tracking
git branch -vv
```

### Sincronizzazione
```bash
# Aggiorna riferimenti remoti
git fetch origin

# Pull del branch corrente
git pull

# Push primo push di branch
git push -u origin nome-branch

# Push successivi
git push
```

## Workflow Tipici

### Feature Branch Workflow
```bash
# 1. Inizia nuova feature
git checkout main
git pull origin main
git checkout -b feature/user-profile

# 2. Sviluppa e committa
git add .
git commit -m "Add user profile component"

# 3. Push per backup/collaborazione
git push -u origin feature/user-profile

# 4. Merge quando pronto
git checkout main
git merge feature/user-profile
git push origin main

# 5. Cleanup
git branch -d feature/user-profile
git push origin --delete feature/user-profile
```

### Hotfix Workflow
```bash
# 1. Crea hotfix da produzione
git checkout main
git checkout -b hotfix/security-patch

# 2. Risolvi problema
git add .
git commit -m "Fix security vulnerability"

# 3. Merge urgente
git checkout main
git merge hotfix/security-patch
git push origin main

# 4. Merge anche in develop se usi Git Flow
git checkout develop
git merge hotfix/security-patch
git push origin develop

# 5. Cleanup
git branch -d hotfix/security-patch
```

## Best Practices

### Naming Convention
```bash
# Tipi di branch comuni
feature/nome-funzionalita
bugfix/descrizione-bug
hotfix/correzione-urgente
release/versione
experiment/nome-esperimento
docs/aggiornamento-documentazione
```

### Regole Generali
1. **Branch di vita breve**: Evita branch che vivono troppo a lungo
2. **Nomi descrittivi**: `feature/user-authentication` > `feature/auth`
3. **Sync frequente**: Aggiorna spesso da main/develop
4. **Cleanup regolare**: Elimina branch non più necessari

### Protezione Branch
```bash
# Configura branch protetti su GitHub
# - Require pull request reviews
# - Require status checks
# - Restrict pushes to specific people
```

## Troubleshooting Comune

### Branch "Stuck" su Commit Vecchio
```bash
# Aggiorna branch con main
git checkout feature-branch
git merge main
# o
git rebase main
```

### Branch Non Sincronizzato
```bash
# Forza sync con remote
git fetch origin
git reset --hard origin/nome-branch
```

### Branch Accidentalmente Eliminato
```bash
# Recupera da reflog
git reflog
git checkout -b recovered-branch HEAD@{n}
```

## Comandi Utili

### Visualizzazione Grafica
```bash
# Storia branch grafica
git log --oneline --graph --all

# Tool grafico integrato
gitk --all
```

### Informazioni Branch
```bash
# Ultimo commit di ogni branch
git for-each-ref --format='%(refname:short) %(committerdate) %(authorname) %(contents:subject)' refs/heads/

# Branch non mergiati
git branch --no-merged main

# Statistiche branch
git shortlog -s -n --all
```

## Esercizi Pratici

1. **Crea un branch feature** e sviluppa una piccola funzionalità
2. **Simula un hotfix** partendo da main
3. **Pratica il cleanup** eliminando branch non necessari
4. **Sperimenta con tracking** di branch remoti

---

La gestione dei branch è fondamentale per un workflow Git efficace. Pratica questi comandi finché non diventano naturali!
