# 02 - Push: Inviare Modifiche al Repository Remoto

## 📖 Spiegazione Concettuale

Il **push** è l'operazione che invia i commit locali al repository remoto, sincronizzando il lavoro locale con il server. È l'operazione complementare al clone e pull.

### Cosa Succede Durante un Push

```
Repository Locale              →              Repository Remoto
├── main: A ← B ← C ← D                      ├── main: A ← B ← C ← D
├── feature: A ← B ← E                       ├── feature: A ← B ← E  
└── .git (history locale)                    └── .git (history aggiornata)

Flusso: Commit locale → Staging → Push → Repository remoto
```

### Prerequisiti per Push

1. **Commit locali**: Devi avere commit da inviare
2. **Remote configurato**: Repository deve avere origine remota
3. **Autenticazione**: Credenziali valide per il repository
4. **Permessi**: Accesso in scrittura al repository

## 🔧 Sintassi del Push

### Comando Base

```bash
# Push del branch corrente
git push

# Push esplicito
git push <remote> <branch>
git push origin main

# Push di tutti i branch
git push --all origin
```

### Opzioni Comuni

```bash
# Push con upstream tracking
git push -u origin main
git push --set-upstream origin feature-branch

# Push forzato (ATTENZIONE!)
git push --force
git push --force-with-lease  # Più sicuro

# Push di tag
git push origin --tags
git push origin v1.0.0
```

## 🎯 Tipi di Push

### 1. Push Normale

Il caso più comune: push di nuovi commit al branch remoto.

```bash
# Scenario normale
echo "New feature" > feature.txt
git add feature.txt
git commit -m "Add new feature"

# Push al remote
git push origin main
# Counting objects: 3, done.
# Writing objects: 100% (3/3), 280 bytes | 280.00 KiB/s, done.
# To https://github.com/user/repo.git
#    abc123..def456  main -> main
```

### 2. Push Primo Branch

Quando push un branch per la prima volta, serve il tracking.

```bash
# Crea nuovo branch locale
git switch -c feature-user-auth

echo "Auth system" > auth.js
git add auth.js
git commit -m "Add authentication system"

# Primo push con upstream
git push -u origin feature-user-auth
# Branch 'feature-user-auth' set up to track remote branch 'feature-user-auth' from 'origin'.

# Push successivi possono usare solo:
git push
```

### 3. Push Forzato

Quando la storia locale diverge da quella remota.

```bash
# Scenario: history rewrite locale
git rebase -i HEAD~3  # Modifica storia

# Push normale fallisce
git push origin main
# error: failed to push some refs to 'origin'
# hint: Updates were rejected because the tip of your current branch is behind

# Push forzato (PERICOLOSO!)
git push --force origin main

# Push forzato sicuro (RACCOMANDATO)
git push --force-with-lease origin main
```

## 🚀 Esempi Pratici

### Scenario 1: Workflow Quotidiano

```bash
# 1. Lavoro locale
echo "Daily work" >> project.md
git add project.md
git commit -m "docs: update project documentation"

# 2. Push semplice
git push

# 3. Verifica su GitHub/GitLab
# I cambiamenti sono visibili online
```

### Scenario 2: Nuova Feature Branch

```bash
# 1. Crea e sviluppa feature
git switch -c feature-shopping-cart

echo "Shopping cart functionality" > cart.js
git add cart.js
git commit -m "feat: implement shopping cart"

echo "Cart styles" > cart.css
git add cart.css
git commit -m "style: add shopping cart CSS"

# 2. Push feature per collaborazione
git push -u origin feature-shopping-cart

# 3. Altri possono ora vedere e collaborare
# git switch -c feature-shopping-cart origin/feature-shopping-cart
```

### Scenario 3: Hotfix Urgente

```bash
# 1. Hotfix da main
git switch main
git pull origin main  # Assicurati di essere aggiornato

git switch -c hotfix-security-patch
echo "Security fix" > security-patch.txt
git add security-patch.txt
git commit -m "fix: apply critical security patch"

# 2. Push immediato
git push -u origin hotfix-security-patch

# 3. Push su main dopo merge
git switch main
git merge hotfix-security-patch
git push origin main

# 4. Cleanup
git branch -d hotfix-security-patch
git push origin --delete hotfix-security-patch
```

## ⚠️ Problemi Comuni e Soluzioni

### 1. Push Rejected (Updates Rejected)

```bash
# Problema: branch remoto ha nuovi commit
$ git push origin main
error: failed to push some refs to 'origin'
hint: Updates were rejected because the remote contains work that you do not have locally.

# Soluzione: pull prima di push
git pull origin main
# Risolvi eventuali conflitti
git push origin main
```

### 2. Autenticazione Fallita

```bash
# Problema HTTPS: credenziali scadute
$ git push origin main
fatal: Authentication failed for 'https://github.com/user/repo.git'

# Soluzioni:
# A) Aggiorna credenziali
git config --global credential.helper store
git push origin main  # Inserisci nuove credenziali

# B) Usa Personal Access Token
# GitHub Settings > Developer settings > Personal access tokens
# Usa token come password

# C) Configura SSH
ssh-keygen -t ed25519 -C "your_email@example.com"
# Aggiungi chiave pubblica su GitHub
git remote set-url origin git@github.com:user/repo.git
```

### 3. Permission Denied

```bash
# Problema: non hai permessi di scrittura
$ git push origin main
ERROR: Permission to user/repo.git denied to yourusername.

# Soluzioni:
# A) Verifica di essere collaboratore
# B) Fork il repository e push al tuo fork
# C) Chiedi accesso al proprietario
```

### 4. Non-Fast-Forward Updates

```bash
# Problema: storia divergente
$ git push origin main
error: failed to push some refs to 'origin'
hint: Updates were rejected because a pushed branch tip is behind its remote counterpart.

# Soluzioni:
# A) Pull e merge
git pull origin main
git push origin main

# B) Rebase locale
git pull --rebase origin main
git push origin main

# C) Force push (SOLO se sei sicuro!)
git push --force-with-lease origin main
```

## 💡 Best Practices

### 1. Push Frequency

```bash
# ✅ Push frequenti per backup e collaborazione
git add .
git commit -m "feat: implement user login"
git push origin feature-branch

# ✅ Push atomici (una feature/fix per volta)
git add login.js
git commit -m "feat: add login functionality"
git push

git add login.css  
git commit -m "style: add login form styles"
git push
```

### 2. Branch Naming e Push

```bash
# ✅ Nomi descrittivi per branch
git switch -c feature/user-authentication
git push -u origin feature/user-authentication

# ✅ Cleanup dopo merge
git push origin --delete feature/user-authentication
```

### 3. Sicurezza nel Push

```bash
# ✅ Verifica prima di force push
git log --oneline -5  # Controlla storia
git push --force-with-lease origin main  # Più sicuro di --force

# ✅ Non fare mai force push su branch condivisi
# main, develop, staging, production

# ✅ Usa branch feature per esperimenti
git switch -c experiment/new-algorithm
git push -u origin experiment/new-algorithm
```

## 🧪 Configurazione Avanzata

### Default Push Behavior

```bash
# Configurazione push default
git config --global push.default simple    # Solo branch corrente
git config --global push.default matching  # Tutti i branch corrispondenti
git config --global push.default current   # Branch corrente a remote stesso nome

# Raccomandazione moderna
git config --global push.default simple
git config --global push.autoSetupRemote true  # Auto setup upstream
```

### Aliases Utili

```bash
# Aliases per push comuni
git config --global alias.pushf 'push --force-with-lease'
git config --global alias.pushu 'push -u origin'
git config --global alias.pushall 'push --all origin'

# Uso degli aliases
git pushu feature-branch    # git push -u origin feature-branch
git pushf main              # git push --force-with-lease origin main
```

### Hooks Pre-Push

```bash
# Script pre-push per validazione
# File: .git/hooks/pre-push
#!/bin/bash
echo "Running tests before push..."
npm test
if [ $? -ne 0 ]; then
    echo "Tests failed! Push aborted."
    exit 1
fi
echo "Tests passed. Proceeding with push."

# Rendi eseguibile
chmod +x .git/hooks/pre-push
```

## 🧪 Esercizi Pratici

### Esercizio 1: Push Base

```bash
# 1. Crea repository locale
mkdir push-exercise
cd push-exercise
git init
git config user.name "Tuo Nome"
git config user.email "tua@email.com"

# 2. Crea contenuto
echo "# Push Exercise" > README.md
git add README.md
git commit -m "Initial commit"

# 3. Aggiungi remote (usa repository test)
git remote add origin https://github.com/tuousername/test-repo.git

# 4. Push iniziale
git push -u origin main
```

### Esercizio 2: Feature Branch Push

```bash
# 1. Crea feature branch
git switch -c feature/calculator

# 2. Implementa feature
echo "function add(a, b) { return a + b; }" > calculator.js
git add calculator.js
git commit -m "feat: add calculator function"

echo "Calculator { margin: 10px; }" > calculator.css
git add calculator.css
git commit -m "style: add calculator styles"

# 3. Push feature
git push -u origin feature/calculator

# 4. Verifica branch remoto
git branch -r
```

### Esercizio 3: Gestione Conflitti Push

```bash
# Simula scenario conflitto
# (Richiede repository condiviso o simulazione)

# 1. Modifica locale
echo "Local change" >> shared-file.txt
git add shared-file.txt
git commit -m "Local modification"

# 2. Simula modifica remota (altro utente)
# ... qualcun altro ha fatto push ...

# 3. Tentativo push (fallirà)
git push origin main

# 4. Risoluzione
git pull origin main
# Risolvi conflitti se necessario
git push origin main
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale comando push un nuovo branch e configura il tracking?
- A) `git push origin branch`
- B) `git push -u origin branch`
- C) `git push --track origin branch`
- D) `git push --upstream origin branch`

### Domanda 2
Quando è appropriato usare `--force-with-lease`?
- A) Per il primo push di un branch
- B) Quando il pull fallisce
- C) Dopo aver riscritto la storia locale
- D) Per push più veloce

### Domanda 3
Cosa succede con `git push` senza parametri?
- A) Push di tutti i branch
- B) Push del branch corrente al remote default
- C) Errore - parametri richiesti
- D) Push solo dei file modificati

### Risposte
1. B - `-u` configura upstream tracking per push futuri
2. C - Force with lease è sicuro dopo rebase/amend locali
3. B - Push branch corrente al remote configurato

## 📚 Approfondimenti

### Push e CI/CD

```bash
# Push automatico trigger pipeline
git push origin main
# → Trigger GitHub Actions
# → Run tests
# → Deploy se tests passano
```

### Security Best Practices

```bash
# Verifica repository destination
git remote -v

# Non fare mai force push su branch protetti
git push --force origin main  # ❌ PERICOLOSO

# Usa feature branch per esperimenti
git push -u origin experiment/risky-feature  # ✅ SICURO
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./01-clone-repository.md)
- [➡️ Prossima Guida](./03-pull-aggiornamenti.md)

### Risorse Esterne
- [Git Push Documentation](https://git-scm.com/docs/git-push)
- [GitHub Authentication](https://docs.github.com/en/authentication)

---

**Prossimo passo**: [Pull Aggiornamenti](./03-pull-aggiornamenti.md) - Impara a sincronizzare con le modifiche remote
