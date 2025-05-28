# Scenari di Emergenza e Recovery

## 📚 Introduzione

Questa guida presenta scenari di emergenza reali che possono accadere durante lo sviluppo e le relative soluzioni di recovery. Ogni scenario include la situazione di partenza, il problema, e la soluzione step-by-step.

## 🚨 Scenari di Emergenza

### Scenario 1: "Ho fatto `git reset --hard` per sbaglio!"

#### Situazione
Stavi lavorando da ore su una feature importante, tutto era solo nel working directory (non committato), e hai fatto `git reset --hard` pensando di annullare solo le ultime modifiche.

```bash
# Situazione prima del disastro
echo "Hours of important work" > critical-feature.js
echo "Complex algorithm implementation" >> critical-feature.js
echo "Detailed documentation" > docs.md

# Il fatale comando
git reset --hard HEAD  # ❌ TUTTO È PERDUTO!

git status
# nothing to commit, working tree clean
```

#### ❌ Problema
Tutto il lavoro non committato è sparito definitivamente.

#### ✅ Soluzione Preventiva
```bash
# SEMPRE committare o stash prima di reset
git add .
git commit -m "WIP: save current work"
# POI fare reset se necessario
git reset --soft HEAD~1  # Mantiene modifiche
```

#### 💡 Recovery Possibile (Limitato)
```bash
# Se usi editor come VS Code, controlla:
# 1. Cronologia locale dell'editor
# 2. File di backup automatici
# 3. Cache dell'IDE

# Per Git: purtroppo nessun recovery diretto
# Le modifiche non committate non sono mai nel reflog
```

### Scenario 2: "Ho cancellato il branch sbagliato!"

#### Situazione
Volevi eliminare un branch di test ma hai cancellato il branch con settimane di lavoro.

```bash
# Setup: due branch con lavoro importante
git checkout -b feature-important
echo "Weeks of work" > important-work.js
git add .
git commit -m "Important feature implementation"

git checkout -b test-branch
echo "Test code" > test.js
git add .
git commit -m "Test implementation"

git checkout main

# Volevi eliminare test-branch ma...
git branch -D feature-important  # ❌ BRANCH SBAGLIATO!

git branch
# * main
#   test-branch
# feature-important è sparito!
```

#### ✅ Recovery con Reflog
```bash
# 1. Cercare nel reflog
git reflog | grep "feature-important"
# a1b2c3d HEAD@{3}: checkout: moving from feature-important to test-branch
# d4e5f6g HEAD@{4}: commit: Important feature implementation

# 2. Ricreare il branch
git branch feature-important d4e5f6g

# 3. Verificare recovery
git checkout feature-important
git log --oneline
# d4e5f6g Important feature implementation
```

#### ✅ Recovery con fsck (se reflog non aiuta)
```bash
# Trovare commit "dangling"
git fsck --unreachable | grep commit

# Esaminare ogni commit trovato
git show COMMIT-SHA1

# Quando trovi quello giusto
git branch feature-important COMMIT-SHA1
```

### Scenario 3: "Ho fatto push di informazioni sensibili!"

#### Situazione
Hai committato e pushato accidentalmente password, chiavi API o altri dati sensibili.

```bash
# Il commit problematico
echo "API_KEY=sk-1234567890abcdef" > .env
git add .env
git commit -m "Add configuration"
git push origin main  # ❌ CHIAVE ESPOSTA!
```

#### 🚨 Azioni Immediate (Entro 5 minuti)
```bash
# 1. REVOCA IMMEDIATAMENTE le credenziali esposte
# - Cambia password
# - Disattiva API key
# - Ruota certificati

# 2. Rimuovi il file dalla storia (SE sei sicuro che nessuno ha pullato)
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch .env' \
  --prune-empty --tag-name-filter cat -- --all

# 3. Force push (PERICOLOSO - solo se sicuro)
git push --force-with-lease origin main
```

#### ✅ Soluzione Sicura per Repository Condivisi
```bash
# 1. Creare nuovo commit che rimuove il file
git rm .env
git commit -m "Remove sensitive configuration file"

# 2. Aggiungere .env al .gitignore
echo ".env" >> .gitignore
git add .gitignore
git commit -m "Add .env to gitignore"

# 3. Push normale
git push origin main

# 4. Creare template di configurazione
echo "API_KEY=your-api-key-here" > .env.example
git add .env.example
git commit -m "Add configuration template"
git push origin main
```

### Scenario 4: "Il repository è corrotto!"

#### Situazione
Git restituisce errori di corruzione e non puoi fare checkout, commit o altre operazioni.

```bash
# Errori tipici di corruzione
git status
# error: object file .git/objects/ab/cd1234... is empty
# fatal: loose object abcd1234... is corrupt

git fsck
# error: unable to read sha1 file of blob abcd1234...
# error: HEAD: invalid sha1 pointer in cache-tree
```

#### ✅ Recovery Step-by-Step
```bash
# 1. Backup immediato
cp -r .git .git-backup

# 2. Tentare auto-recovery
git fsck --full --strict
git gc

# 3. Se fsck fallisce, ricostruire index
rm .git/index
git reset

# 4. Se oggetti sono corrotti, cercare backup
# In .git/objects/pack/ potrebbero esserci versioni valide

# 5. Recovery da clone remoto
git fetch origin
git reset --hard origin/main

# 6. Se tutto fallisce, ri-clonare
cd ..
git clone https://github.com/user/repo.git repo-recovered
cd repo-recovered
# Copiare file di lavoro non committati dal repository corrotto
```

### Scenario 5: "Ho fatto rebase sbagliato e ho perso commit!"

#### Situazione
Durante un rebase interattivo hai cancellato commit importanti.

```bash
# Setup: branch con storia complessa
git checkout -b feature
git commit -m "Feature part 1" --allow-empty
git commit -m "Feature part 2" --allow-empty  
git commit -m "Important fix" --allow-empty
git commit -m "Feature part 3" --allow-empty

# Rebase che va male
git rebase -i HEAD~4
# Nell'editor accidentalmente cancelli o sbagli la configurazione
# Risultato: alcuni commit spariscono
```

#### ✅ Recovery con ORIG_HEAD
```bash
# Git salva automaticamente il punto di partenza
git reset --hard ORIG_HEAD

# Verificare recovery
git log --oneline
# Tutti i commit dovrebbero essere tornati
```

#### ✅ Recovery con Reflog
```bash
# Se ORIG_HEAD non funziona
git reflog
# a1b2c3d HEAD@{0}: rebase: returning to refs/heads/feature
# d4e5f6g HEAD@{1}: rebase: Feature part 3
# g7h8i9j HEAD@{2}: rebase: Important fix
# k1l2m3n HEAD@{3}: rebase (start): checkout HEAD~4

# Tornare al punto prima del rebase
git reset --hard HEAD@{3}
```

### Scenario 6: "Ho fatto merge sbagliato che ha rovinato tutto!"

#### Situazione
Hai fatto merge di un branch che conteneva modifiche incompatibili e ora il codice è rotto.

```bash
# Merge problematico appena fatto
git merge problematic-branch
# Auto-merging src/main.js
# CONFLICT (content): Merge conflict in src/main.js
# Hai risolto i conflitti male...
git add .
git commit -m "Merge problematic-branch"

# Il codice ora è completamente rotto
```

#### ✅ Recovery Immediato
```bash
# Se è l'ultima operazione
git reset --hard HEAD~1

# Oppure usare ORIG_HEAD (se merge appena fatto)
git reset --hard ORIG_HEAD
```

#### ✅ Recovery con Revert
```bash
# Se hanno fatto push del merge
git revert -m 1 HEAD

# -m 1 indica di revertire rispetto al primo parent (main branch)
# Il merge viene annullato con un nuovo commit
```

### Scenario 7: "Ho perso giorni di lavoro con `git clean -fdx`!"

#### Situazione
Volevi pulire solo alcuni file generati ma hai perso tutto il lavoro non tracciato.

```bash
# Avevi file importanti non tracciati
echo "Important work not yet added" > temp-work.js
echo "Research notes" > notes.txt
echo "Local configuration" > local-config.ini

# Il comando fatale
git clean -fdx  # ❌ Cancella TUTTO quello non tracciato
```

#### ✅ Recovery Possibile
```bash
# 1. Controlla il Cestino/Trash del sistema operativo
# Su Linux/Mac: ~/.local/share/Trash/ o ~/.Trash/
# Su Windows: Cestino

# 2. Controlla backup automatici dell'editor
# VS Code: .vscode/settings.json potrebbe avere backup
# IntelliJ: .idea/ cartella con backup locali

# 3. Controlla cache del sistema
# Alcuni editor salvano versioni temporanee

# 4. Usa strumenti di recovery del filesystem
# Linux: testdisk, photorec
# Mac: Disk Drill
# Windows: Recuva
```

#### 💡 Prevenzione Futura
```bash
# SEMPRE fare dry-run prima di clean
git clean -fdx --dry-run

# Configurare clean più sicuro
git config --global clean.requireForce true

# Usare clean selettivo
git clean -i  # Interattivo
```

## 🛠️ Kit di Emergency Recovery

### Script di Backup Pre-Operazione
```bash
#!/bin/bash
# emergency-backup.sh
BACKUP_DIR=".git-emergency-$(date +%s)"

echo "Creating emergency backup in $BACKUP_DIR..."
cp -r .git "$BACKUP_DIR"

# Backup working directory
tar -czf "$BACKUP_DIR/working-dir.tar.gz" \
    --exclude=.git \
    --exclude=node_modules \
    --exclude=.env \
    .

echo "Backup created. To restore: cp -r $BACKUP_DIR .git"
```

### Script di Analisi Situazione
```bash
#!/bin/bash
# analyze-situation.sh

echo "=== GIT EMERGENCY ANALYSIS ==="
echo "Repository status:"
git status 2>/dev/null || echo "❌ Git status failed"

echo -e "\nLast 5 commits:"
git log --oneline -5 2>/dev/null || echo "❌ Git log failed"

echo -e "\nReflog (last 10 entries):"
git reflog -10 2>/dev/null || echo "❌ Reflog failed"

echo -e "\nBranches:"
git branch -a 2>/dev/null || echo "❌ Branch listing failed"

echo -e "\nRemote status:"
git remote -v 2>/dev/null || echo "❌ Remote listing failed"

echo -e "\nRepository integrity:"
git fsck --quick 2>/dev/null || echo "❌ Repository may be corrupted"
```

## 📋 Checklist di Emergency Response

### Primo Soccorso (Primi 30 secondi)
- [ ] **STOP** - Non fare altri comandi Git
- [ ] Copia il messaggio di errore completo
- [ ] Verifica se è un repository condiviso (altri potrebbero essere affetti)
- [ ] Fai backup immediato se possibile (`cp -r .git .git-backup`)

### Analisi (Primi 2 minuti)
- [ ] `git status` - Qual è lo stato attuale?
- [ ] `git reflog -10` - Cosa è successo di recente?
- [ ] `git log --oneline -5` - Com'era la storia?
- [ ] `git fsck --quick` - Il repository è integro?

### Recovery (Primi 5 minuti)
- [ ] Prova `git reset --hard ORIG_HEAD` se applicabile
- [ ] Cerca nel reflog il punto di recovery
- [ ] Verifica backup dell'editor/IDE
- [ ] Se dati sensibili esposti: REVOCA CREDENZIALI IMMEDIATAMENTE

### Comunicazione (Se repository condiviso)
- [ ] Avvisa il team dell'emergenza
- [ ] Coordina eventuali force push
- [ ] Documenta la soluzione per il futuro

## 💡 Strategie di Prevenzione

### 1. Backup Automatici
```bash
# Hook pre-commit per backup automatico
#!/bin/sh
# .git/hooks/pre-commit
git bundle create .git/backup-$(date +%s).bundle HEAD
```

### 2. Alias Sicuri
```bash
git config --global alias.safe-reset '!git branch backup-$(date +%s) && git reset'
git config --global alias.safe-clean 'clean --dry-run'
git config --global alias.safe-rebase '!git branch backup-$(date +%s) && git rebase'
```

### 3. Workflow Protettivo
```bash
# Prima di operazioni rischiose
git branch backup-before-dangerous-operation
git tag backup-$(date +%s)

# Dopo verifiche
git branch -D backup-before-dangerous-operation
git tag -d backup-$(date +%s)
```

## 📝 Riassunto

Le emergenze Git più comuni sono:
1. **Reset accidentali** - Recovery con reflog
2. **Branch cancellati** - Recovery con fsck/reflog  
3. **Dati sensibili esposti** - Revoca immediata + history cleanup
4. **Repository corrotti** - Backup + re-clone
5. **Rebase/merge sbagliati** - ORIG_HEAD + reflog
6. **Clean accidentali** - Backup filesystem

**Chiavi del success**o:
- **Agire rapidamente** ma senza panico
- **Verificare sempre** prima di recovery
- **Usare backup** preventivi
- **Comunicare** in team se necessario
- **Documentare** la soluzione per il futuro

Ricorda: Git raramente perde dati definitivamente, ma il recovery richiede calma e metodologia!
