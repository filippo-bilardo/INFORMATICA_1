# 02 - Recovery Strategies

## 📖 Spiegazione Concettuale

Le **strategie di recovery** in Git sono tecniche per recuperare lavoro perso, annullare operazioni sbagliate e riportare il repository a uno stato funzionante. Git offre molteplici livelli di safety net che rendono quasi impossibile perdere lavoro definitivamente.

### Principi del Recovery

#### 1. **Git non cancella mai** (quasi)
- I commit sono immutabili fino al garbage collection
- Il reflog mantiene una cronologia di 90 giorni
- Anche reset "distruttivi" sono spesso reversibili

#### 2. **Recovery progressivo**
- Inizia con le soluzioni meno invasive
- Testa in repository separato quando possibile
- Backup prima di operazioni rischiose

#### 3. **Comprendi prima di agire**
- Identifica esattamente cosa è andato storto
- Capisci lo stato desiderato
- Valuta le implicazioni delle operazioni

## 🔄 Livelli di Recovery

### Livello 1: **Working Directory Recovery**

#### Recupero File Modificati Non Salvati

```bash
# Scarta modifiche in working directory
git restore filename.txt

# Scarta tutte le modifiche
git restore .

# Recupera file specifico da commit precedente
git restore --source=HEAD~1 filename.txt

# Recupera file cancellato (se era tracciato)
git restore filename.txt
```

#### Recupero File da Staging Area

```bash
# Remove file from staging (mantieni modifiche in working)
git restore --staged filename.txt

# Remove all files from staging
git restore --staged .

# Remove e discard modifiche
git restore --staged --worktree filename.txt
```

### Livello 2: **Commit Recovery**

#### Annullare Ultimo Commit (mantenendo modifiche)

```bash
# Soft reset - mantieni modifiche in staging
git reset --soft HEAD~1

# Mixed reset (default) - mantieni modifiche in working directory
git reset HEAD~1

# Verifica stato dopo reset
git status
```

#### Annullare Ultimo Commit (perdendo modifiche)

```bash
# ⚠️ ATTENZIONE: Perdi le modifiche!
git reset --hard HEAD~1

# Solo se sei sicuro al 100%
# Backup prima: git branch backup-$(date +%Y%m%d)
```

#### Recuperare Commit dopo Reset

```bash
# Trova il commit "perso" nel reflog
git reflog

# Output esempio:
# a1b2c3d HEAD@{0}: reset: moving to HEAD~1
# d4e5f6g HEAD@{1}: commit: Important feature (QUESTO!)
# h7i8j9k HEAD@{2}: commit: Previous work

# Recupera il commit
git reset --hard d4e5f6g

# O crea nuovo branch dal commit perso
git branch recovered-work d4e5f6g
```

### Livello 3: **Branch Recovery**

#### Recuperare Branch Cancellato

```bash
# Branch cancellato per errore
git branch -D feature-important

# Trova nel reflog
git reflog | grep feature-important
# o cerca per contenuto
git log --all --grep="feature content"

# Recupera branch
git branch feature-important a1b2c3d
git checkout feature-important
```

#### Recuperare Branch dopo Force Push

```bash
# Qualcuno ha fatto force push e "perso" il tuo lavoro
git reflog origin/main

# Trova stato precedente
git branch backup-main origin/main@{1}

# O reset del branch remoto (se hai permessi)
git push origin backup-main:main
```

### Livello 4: **Merge/Rebase Recovery**

#### Annullare Merge

```bash
# Se merge non ancora pushato
git reset --hard HEAD~1

# Se merge già pushato, usa revert
git revert -m 1 HEAD

# Annullare merge in corso
git merge --abort
```

#### Annullare Rebase

```bash
# Rebase in corso - annulla
git rebase --abort

# Rebase completato - trova stato precedente
git reflog
git reset --hard HEAD@{before-rebase}
```

#### Recuperare da Rebase Disastroso

```bash
# Trova stato pre-rebase nel reflog
git reflog | grep "rebase"

# Output esempio:
# a1b2c3d HEAD@{0}: rebase finished: returning to refs/heads/feature
# d4e5f6g HEAD@{5}: rebase start: checkout main

# Torna a stato pre-rebase
git reset --hard d4e5f6g
```

## 🚨 Scenari di Emergency Recovery

### Scenario 1: "Ho cancellato tutto con reset --hard"

```bash
# PANICO: git reset --hard ha cancellato giorni di lavoro!

# SOLUZIONE:
# 1. NON FARE NIENTE ALTRO
# 2. Cerca nel reflog
git reflog

# 3. Trova ultimo stato buono
git reflog | head -10

# 4. Recupera (sostituisci abc123 con hash corretto)
git reset --hard abc123

# 5. Verifica
git status
git log --oneline -5
```

### Scenario 2: "Repository completamente rotto"

```bash
# Repository sembra corrotto, comandi non funzionano

# DIAGNOSI:
git fsck --full

# RECOVERY STEPS:

# 1. Backup immediate
cp -r .git ../backup-git-$(date +%Y%m%d)

# 2. Tenta repair
git gc --aggressive

# 3. Se ancora rotto, ricostruisci da remoto
cd ..
git clone <repository-url> recovered-repo
cd recovered-repo

# 4. Recupera lavoro locale non pushato
cd ../original-repo
git log --oneline > ../local-commits.txt
# Applica manualmente i commit necessari
```

### Scenario 3: "Force push ha distrutto la history"

```bash
# Qualcuno ha fatto force push e sovrascritto main

# IMMEDIATE ACTIONS:
# 1. NON PULLARE
# 2. Backup stato locale
git branch emergency-backup

# RECOVERY:
# 3. Controlla chi ha accesso e comunica
# 4. Recupera dal reflog del server (se disponibile)
git reflog origin/main

# 5. O da backup locali di team members
# 6. Force push del branch corretto (coordinato con team)
git push --force-with-lease origin emergency-backup:main
```

### Scenario 4: "Commit con dati sensibili"

```bash
# Committato password/API keys per errore

# IMMEDIATE ACTIONS (se non pushato):
git reset --hard HEAD~1

# SE GIÀ PUSHATO - EMERGENCY PROTOCOL:
# 1. Revoca immediatamente credenziali compromesse
# 2. Notifica team/security
# 3. Rewrite history

# Rimuovi file dalla history completa
git filter-branch --force --index-filter \
  "git rm --cached --ignore-unmatch config/secrets.env" \
  --prune-empty --tag-name-filter cat -- --all

# O usa git-filter-repo (più moderno)
pip install git-filter-repo
git filter-repo --path config/secrets.env --invert-paths

# Force push su tutti i branch
git push --force --all origin
git push --force --tags origin
```

## 🛠️ Recovery Tools Avanzati

### 1. **git-filter-repo** - History Rewriting

```bash
# Installazione
pip install git-filter-repo

# Rimuovi file dalla history
git filter-repo --path sensitive-file.txt --invert-paths

# Rimuovi directory
git filter-repo --path secrets/ --invert-paths

# Rimuovi pattern
git filter-repo --path-glob '*.log' --invert-paths

# Rimuovi contenuto specifico
git filter-repo --replace-text expressions.txt
```

### 2. **git-recover** - Automated Recovery

```bash
# Tool per recovery automatico
# Cerca commit orfani
git fsck --unreachable | grep commit

# Recupera automaticamente
for hash in $(git fsck --unreachable | grep commit | cut -d' ' -f3); do
    echo "Found: $hash"
    git show --oneline $hash
done
```

### 3. **git-rescue** - Emergency Procedures

```bash
# Script di emergency rescue
#!/bin/bash
# emergency-recovery.sh

echo "🚨 EMERGENCY RECOVERY STARTING"
echo "Repository: $(pwd)"
echo "Time: $(date)"

# 1. Backup immediato
cp -r .git ../emergency-backup-$(date +%Y%m%d-%H%M%S)
echo "✅ Backup created"

# 2. Reflog backup
git reflog > ../reflog-backup-$(date +%Y%m%d-%H%M%S).txt
echo "✅ Reflog saved"

# 3. Branch backup
git branch > ../branches-backup-$(date +%Y%m%d-%H%M%S).txt
echo "✅ Branches listed"

# 4. Status snapshot
git status > ../status-backup-$(date +%Y%m%d-%H%M%S).txt
echo "✅ Status saved"

echo "🚨 EMERGENCY BACKUP COMPLETE"
echo "You can now attempt recovery safely"
```

## 📊 Recovery Decision Matrix

### Situazione: Modifiche Loss

| Scenario | Soluzione | Risk Level | Recovery Time |
|----------|-----------|------------|---------------|
| File modificato non salvato | `git restore file` | 🟢 Low | 1 min |
| File in staging unwanted | `git restore --staged` | 🟢 Low | 1 min |
| Ultimo commit sbagliato | `git reset --soft HEAD~1` | 🟡 Medium | 5 min |
| Multiple commits sbagliati | `git reset --hard + reflog` | 🔴 High | 15 min |

### Situazione: Branch Issues

| Scenario | Soluzione | Risk Level | Recovery Time |
|----------|-----------|------------|---------------|
| Branch cancellato | `git branch name hash` | 🟢 Low | 2 min |
| Merge sbagliato | `git reset --hard` | 🟡 Medium | 10 min |
| Rebase disastroso | `git reflog + reset` | 🔴 High | 20 min |
| Force push damage | Team coordination | 🔴 Critical | 60 min |

### Situazione: Repository Corruption

| Scenario | Soluzione | Risk Level | Recovery Time |
|----------|-----------|------------|---------------|
| File corrotti | `git fsck + gc` | 🟡 Medium | 15 min |
| Index corrotto | `rm .git/index + reset` | 🟡 Medium | 10 min |
| Complete corruption | `git clone + manual merge` | 🔴 High | 120 min |
| History rewrite needed | `git filter-repo` | 🔴 Critical | 240 min |

## 🎯 Recovery Best Practices

### 1. **Prevention is Better**

```bash
# Setup automatic backups
git config --global alias.backup '!git bundle create ../backup-$(date +%Y%m%d).bundle --all'

# Regular maintenance
git config --global alias.cleanup 'gc --aggressive --prune=now'

# Safe force push
git config --global alias.force-push 'push --force-with-lease'
```

### 2. **Recovery Workflow**

```bash
# Standard recovery procedure:
# 1. STOP - Don't panic
# 2. BACKUP - Current state
# 3. ANALYZE - What went wrong
# 4. PLAN - Recovery strategy
# 5. EXECUTE - Carefully
# 6. VERIFY - Success
# 7. DOCUMENT - For next time
```

### 3. **Team Recovery Protocol**

```markdown
## Emergency Recovery Protocol

### Immediate Actions (< 5 minutes)
1. **STOP** - No more git operations
2. **COMMUNICATE** - Alert team in #git-emergency
3. **BACKUP** - Current state of affected repositories
4. **ASSESS** - Scope of damage

### Investigation Phase (< 30 minutes)
1. **GATHER** - Error messages, logs, reflog
2. **IDENTIFY** - Root cause and affected commits/branches
3. **PLAN** - Recovery strategy with multiple options
4. **APPROVE** - Get lead developer approval

### Recovery Phase (< 2 hours)
1. **EXECUTE** - Recovery plan step by step
2. **VERIFY** - Each step before proceeding
3. **TEST** - Functionality after recovery
4. **DOCUMENT** - What was done

### Post-Recovery (< 24 hours)
1. **RETROSPECTIVE** - What went wrong
2. **IMPROVE** - Update procedures
3. **TRAIN** - Share knowledge with team
4. **MONITOR** - Watch for related issues
```

### 4. **Recovery Testing**

```bash
# Practice recovery in safe environment
mkdir git-recovery-practice
cd git-recovery-practice
git init

# Create test scenario
echo "test" > file.txt
git add file.txt
git commit -m "Initial commit"

# Simulate problems and practice recovery
git reset --hard HEAD~1  # "Lose" the commit
git reflog                # Find it
git reset --hard abc123   # Recover it
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Diagnostica Problemi](01-diagnostica-problemi.md)
- [➡️ Authentication Issues](03-authentication-issues.md)
