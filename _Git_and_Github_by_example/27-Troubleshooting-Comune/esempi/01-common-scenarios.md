# Scenari Comuni di Troubleshooting Git

## Introduzione

Questo documento presenta i problemi più comuni che incontrerai lavorando con Git e GitHub, con soluzioni pratiche e immediate.

## Categoria 1: Problemi di Commit

### Scenario 1.1: Ho fatto commit del file sbagliato

**Problema**: Hai appena fatto commit di `password.txt` invece di `README.txt`.

```bash
# Situazione iniziale
git add password.txt
git commit -m "Add README documentation"

# OOPS! File sbagliato!
```

**Soluzione Immediata**:

```bash
# Opzione A: Modifica l'ultimo commit (se non ancora pushato)
git reset --soft HEAD~1      # Annulla commit, mantieni staging
git reset password.txt       # Rimuovi file dall'area staging
git add README.txt           # Aggiungi file corretto
git commit -m "Add README documentation"

# Opzione B: Se il commit è già stato pushato
git rm --cached password.txt # Rimuovi file dal tracking
echo "password.txt" >> .gitignore
git add .gitignore
git commit -m "Remove password file and add to gitignore"
```

### Scenario 1.2: Messaggio di commit sbagliato

**Problema**: Hai scritto `"Fix bug in payment module"` invece di `"Add user registration feature"`.

```bash
# Ultimo commit con messaggio sbagliato
git log --oneline -1
# a1b2c3d Fix bug in payment module
```

**Soluzione**:

```bash
# Se il commit NON è stato pushato
git commit --amend -m "Add user registration feature"

# Se il commit È GIÀ stato pushato (attenzione: cambia la storia)
git commit --amend -m "Add user registration feature"
git push --force-with-lease origin branch-name

# Alternative sicure se pushato
git revert HEAD
git commit -m "Add user registration feature"
```

### Scenario 1.3: Ho dimenticato di aggiungere file al commit

**Problema**: Hai fatto commit della feature ma dimenticato `styles.css`.

```bash
# Commit incompleto
git add main.js
git commit -m "Implement new feature"

# Ti accorgi che manca styles.css
```

**Soluzione**:

```bash
# Se NON ancora pushato
git add styles.css
git commit --amend --no-edit  # Aggiunge al commit precedente

# Se GIÀ pushato
git add styles.css
git commit -m "Add missing styles for new feature"
```

## Categoria 2: Problemi di Branch e Merge

### Scenario 2.1: Sono nel branch sbagliato

**Problema**: Hai lavorato per ore nel branch `main` invece di `feature/login`.

```bash
# Scopri di essere in main
git branch
# * main
#   feature/login

# Hai fatto modifiche che dovresti avere in feature/login
git status
# Modified: login.js, auth.js, styles.css
```

**Soluzione**:

```bash
# Salva il lavoro corrente
git stash push -m "Work meant for feature/login"

# Vai al branch corretto
git checkout feature/login

# Ripristina il lavoro
git stash pop

# Oppure se hai già fatto commit in main
git checkout main
git reset --soft HEAD~n  # n = numero commit da spostare
git checkout feature/login
git commit -m "Your commit message"
```

### Scenario 2.2: Merge andato male

**Problema**: Dopo un merge hai perso codice importante.

```bash
# Situazione dopo merge problematico
git log --oneline -5
# a1b2c3d Merge branch 'feature/payment'
# e4f5g6h Add payment validation
# h7i8j9k Fix user authentication
```

**Soluzione**:

```bash
# Trova l'hash del commit prima del merge
git reflog
# a1b2c3d HEAD@{0}: merge feature/payment: Merge made by the 'recursive' strategy
# h7i8j9k HEAD@{1}: checkout: moving from feature/payment to main
# e4f5g6h HEAD@{2}: commit: Add payment validation

# Annulla il merge
git reset --hard HEAD~1  # Torna prima del merge

# Alternative: revert del merge
git revert -m 1 a1b2c3d  # -m 1 specifica il parent principale
```

### Scenario 2.3: Conflitti di merge complessi

**Problema**: Merge con 20+ file in conflitto.

```bash
# Durante merge
git merge feature/refactoring
# Auto-merging src/utils.js
# CONFLICT (content): Merge conflict in src/utils.js
# [... 20+ file conflicts ...]
```

**Soluzione Strategica**:

```bash
# Interrompi il merge caotico
git merge --abort

# Strategia alternativa: merge graduale
git checkout feature/refactoring
git rebase main  # Risolvi conflitti un commit alla volta

# Oppure: merge con strategia specifica
git merge -X ours feature/refactoring    # Privilegia il branch corrente
git merge -X theirs feature/refactoring  # Privilegia il branch in merge
```

## Categoria 3: Problemi con Remote Repository

### Scenario 3.1: Push rifiutato

**Problema**: `error: failed to push some refs to origin`.

```bash
git push origin main
# To https://github.com/user/repo.git
# ! [rejected]        main -> main (fetch first)
# error: failed to push some refs to 'https://github.com/user/repo.git'
```

**Soluzione**:

```bash
# Metodo 1: Pull e merge
git pull origin main
# Risolvi eventuali conflitti
git push origin main

# Metodo 2: Pull con rebase (storia più pulita)
git pull --rebase origin main
# Risolvi eventuali conflitti
git push origin main

# Metodo 3: Se sei sicuro delle tue modifiche
git push --force-with-lease origin main
```

### Scenario 3.2: Repository divergenti

**Problema**: Il tuo repository locale e quello remoto hanno cronologie diverse.

```bash
git status
# Your branch and 'origin/main' have diverged,
# and have 3 and 4 different commits each, respectively.
```

**Soluzione**:

```bash
# Visualizza la divergenza
git log --oneline --graph --all

# Opzione A: Merge
git pull origin main  # Crea merge commit

# Opzione B: Rebase (storia lineare)
git pull --rebase origin main

# Opzione C: Reset completo al remote (ATTENZIONE: perdi lavoro locale)
git fetch origin
git reset --hard origin/main
```

### Scenario 3.3: Autenticazione fallita

**Problema**: `fatal: Authentication failed` o problemi SSH.

```bash
git push origin main
# Username for 'https://github.com': username
# Password for 'https://username@github.com': 
# remote: Support for password authentication was removed on August 13, 2021.
```

**Soluzione**:

```bash
# Problema 1: Password non più supportata
# Soluzione: Usa Personal Access Token
git remote set-url origin https://USERNAME:TOKEN@github.com/USERNAME/REPO.git

# Problema 2: SSH key issues
ssh -T git@github.com  # Testa connessione SSH

# Se SSH fallisce
ssh-keygen -t ed25519 -C "your_email@example.com"
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
# Aggiungi la chiave pubblica su GitHub

# Problema 3: Wrong remote URL
git remote -v  # Verifica URL corrente
git remote set-url origin git@github.com:USERNAME/REPO.git
```

## Categoria 4: Problemi di Performance

### Scenario 4.1: Repository molto lento

**Problema**: Operazioni Git impiegano minuti invece di secondi.

```bash
# Operazioni lente
git status  # Impiega 30+ secondi
git log     # Molto lento
```

**Soluzione**:

```bash
# Diagnosi
git count-objects -vH  # Mostra dimensioni repository
du -sh .git/           # Dimensione directory Git

# Pulizia e ottimizzazione
git gc --aggressive    # Garbage collection aggressiva
git prune             # Rimuovi oggetti irraggiungibili
git repack -Ad        # Repack oggetti

# Per repository molto grandi
git config core.preloadindex true
git config core.fscache true
git config gc.auto 256
```

### Scenario 4.2: File giganti nel repository

**Problema**: Hai committed accidentalmente `database.sql` (500MB).

```bash
# File enorme nella cronologia
git log --stat | grep -E "^\s.*\s+\d+\s+\++" | sort -nr -k2
```

**Soluzione**:

```bash
# Rimuovi file da tutta la cronologia (ATTENZIONE: riscrive storia)
git filter-branch --force --index-filter \
'git rm --cached --ignore-unmatch database.sql' \
--prune-empty --tag-name-filter cat -- --all

# Metodo moderno con git-filter-repo
pip install git-filter-repo
git filter-repo --path database.sql --invert-paths

# Pulizia finale
git for-each-ref --format="delete %(refname)" refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now
```

## Categoria 5: Recovery di Emergenza

### Scenario 5.1: Ho cancellato tutto con `git reset --hard`

**Problema**: Hai perso ore di lavoro con un reset aggressivo.

```bash
# DISASTER: tutto il lavoro è sparito
git reset --hard HEAD~5  # OOPS!
```

**Soluzione**:

```bash
# Git reflog è il tuo salvatore
git reflog
# a1b2c3d HEAD@{0}: reset: moving to HEAD~5
# e4f5g6h HEAD@{1}: commit: Important work (this is what we want!)
# h7i8j9k HEAD@{2}: commit: Previous work

# Recupera il commit perso
git reset --hard e4f5g6h

# Se non è in reflog, cerca negli oggetti scollegati
git fsck --lost-found
git show <object-hash>  # Esamina oggetti trovati
```

### Scenario 5.2: Repository corrotto

**Problema**: `error: object file .git/objects/...`

```bash
git status
# error: object file .git/objects/ab/cdef123... is empty
# fatal: loose object abcdef123... (stored in .git/objects/ab/cdef123...) is corrupt
```

**Soluzione**:

```bash
# Tentativo di riparazione automatica
git fsck --full
git gc --aggressive

# Se il repository ha un remote
git fetch origin
git reset --hard origin/main  # Se accettabile perdere lavoro locale

# Backup e clonazione pulita (ultima risorsa)
cp -r .git .git-backup
cd ..
git clone <repository-url> repo-fresh
# Copia i file non committed dal vecchio repo
```

### Scenario 5.3: Branch cancellato per errore

**Problema**: Hai cancellato il branch `feature/important` con tutto il lavoro.

```bash
# Branch cancellato
git branch -D feature/important
# Deleted branch feature/important (was a1b2c3d).
```

**Soluzione**:

```bash
# Se ricordi l'hash (Git te lo dice quando cancelli)
git checkout -b feature/important a1b2c3d

# Se non ricordi l'hash
git reflog --all | grep important
# a1b2c3d refs/heads/feature/important@{0}: commit: Last work on important

# Ricrea il branch
git checkout -b feature/important a1b2c3d
```

## Strumenti di Diagnosi Essenziali

### Quick Diagnostic Commands

```bash
# Stato generale del repository
git status --porcelain          # Formato machine-readable
git log --oneline --graph -10   # Storia recente visuale
git reflog --all --decorate     # Tutti i movimenti recenti

# Informazioni sui remote
git remote -v                   # URL dei remote
git branch -vv                  # Branch con tracking info
git ls-remote origin            # Cosa c'è sul remote

# Performance e dimensioni
git count-objects -vH           # Statistiche oggetti
git gc --dry-run               # Cosa farebbe la garbage collection
git fsck --full --strict       # Controllo integrità completo
```

### Backup di Emergenza

```bash
# Backup completo (prima di operazioni rischiose)
tar -czf git-backup-$(date +%Y%m%d_%H%M%S).tar.gz .git

# Backup solo reflog (lightweight)
cp .git/logs/HEAD .git/HEAD-backup-$(date +%Y%m%d_%H%M%S)

# Backup configurazione
git config --list > git-config-backup.txt
```

## Recovery Workflow Standard

### Prima di Qualsiasi Operazione Rischiosa

1. **Backup**: `git stash` o backup fisico
2. **Documentazione**: Annota hash del commit corrente
3. **Test**: Prova su un clone se possibile
4. **Verifica**: Controlla che tutto sia committed/stashed

### Quando Qualcosa Va Male

1. **STOP**: Non fare altre operazioni
2. **Diagnosi**: `git status`, `git log`, `git reflog`
3. **Backup**: Salva lo stato corrente
4. **Recovery**: Usa la strategia appropriata
5. **Verifica**: Controlla che tutto sia ok
6. **Documentazione**: Annota cosa è successo per il futuro

## Best Practices per Prevenire Problemi

### Workflow Quotidiano

```bash
# Inizia sempre con
git status
git pull --rebase origin main

# Lavora in branch
git checkout -b feature/your-feature

# Commit frequenti
git add .
git commit -m "Descriptive message"

# Push regolari
git push -u origin feature/your-feature
```

### Configurazioni Preventive

```bash
# Abilita rerere (riusa risoluzioni conflitti)
git config rerere.enabled true

# Push safety
git config push.default simple
git config push.followTags true

# Alias utili per recovery
git config alias.unstage 'reset HEAD --'
git config alias.last 'log -1 HEAD'
git config alias.visual '!gitk'
```

---

**💡 Ricorda**: Git raramente perde davvero i dati. La maggior parte dei problemi sono risolvibili con pazienza e i comandi giusti.

**⚠️ Warning**: Comandi come `--force`, `--hard`, e `filter-branch` possono essere distruttivi. Fai sempre backup prima di usarli.

**🆘 Emergency Contacts**: 
- [Git Documentation](https://git-scm.com/docs)
- [GitHub Support](https://support.github.com/)
- [Stack Overflow Git Tag](https://stackoverflow.com/questions/tagged/git)
