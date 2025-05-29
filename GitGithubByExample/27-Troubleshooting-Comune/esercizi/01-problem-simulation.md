# 01 - Problem Simulation

## 🎯 Obiettivo
Simulare e risolvere i problemi Git più comuni in un ambiente controllato per sviluppare competenze di troubleshooting pratiche.

## 📋 Prerequisiti
- Repository Git funzionante
- Backup dei dati importanti
- Tempo dedicato senza interruzioni
- Mentalità sperimentale

## ⏱️ Tempo Stimato
90-120 minuti

## 🚨 IMPORTANTE
Questo esercizio simula problemi reali. Usalo solo in repository di test, MAI in progetti di produzione!

## 🔧 Setup Ambiente di Test

### Crea Repository di Test

```bash
# Crea nuovo repository per simulazioni
mkdir git-troubleshooting-lab
cd git-troubleshooting-lab
git init

# Setup configurazione base
git config user.name "Test User"
git config user.email "test@example.com"

# Crea struttura iniziale
echo "# Git Troubleshooting Lab" > README.md
echo "console.log('Hello World');" > app.js
echo "body { color: blue; }" > style.css

git add .
git commit -m "Initial commit"

# Crea alcuni commit di storia
echo "// Added feature 1" >> app.js
git add app.js
git commit -m "Add feature 1"

echo "// Added feature 2" >> app.js
git add app.js  
git commit -m "Add feature 2"

echo "/* Updated styles */" >> style.css
git add style.css
git commit -m "Update styles"

# Crea branch per testing
git checkout -b feature/testing
echo "// Testing feature" >> app.js
git add app.js
git commit -m "Add testing feature"

git checkout main
```

## 🧪 Simulazione Problemi

### Problema 1: Reset Accidentale

#### Setup del Problema
```bash
# Simula lavoro importante
echo "// IMPORTANT: Critical bugfix" >> app.js
echo "// This took hours to write" >> app.js
git add app.js
git commit -m "CRITICAL: Important bugfix"

# Simula reset accidentale (disaster!)
git reset --hard HEAD~2

# Verifica il "danno"
git log --oneline
cat app.js  # Il bugfix è sparito!
```

#### Diagnosi
```bash
# Step 1: Non panico - valuta la situazione
git status

# Step 2: Controlla reflog
git reflog

# Dovresti vedere qualcosa come:
# a1b2c3d HEAD@{0}: reset: moving to HEAD~2
# e4f5g6h HEAD@{1}: commit: CRITICAL: Important bugfix
```

#### Risoluzione
```bash
# Step 3: Trova il commit perso
git reflog | grep "CRITICAL"

# Step 4: Recupera il commit
git reset --hard e4f5g6h  # Usa hash del commit critico

# Step 5: Verifica recupero
git log --oneline
cat app.js  # Il bugfix dovrebbe essere tornato!
```

### Problema 2: Branch Cancellato per Errore

#### Setup del Problema
```bash
# Crea branch con lavoro importante
git checkout -b important-feature
echo "// Months of work here" > important-feature.js
echo "// Revolutionary algorithm" >> important-feature.js
git add important-feature.js
git commit -m "Months of important work"

# Torna a main
git checkout main

# Simula cancellazione accidentale
git branch -D important-feature

# Verifica il "danno"
git branch  # important-feature non c'è più!
```

#### Diagnosi
```bash
# Step 1: Cerca nel reflog
git reflog | grep "important-feature"

# O cerca per contenuto del commit
git reflog | grep "Months of important"
```

#### Risoluzione
```bash
# Step 2: Identifica hash del commit
# Supponiamo sia h7i8j9k

# Step 3: Ricrea il branch
git branch important-feature h7i8j9k

# Step 4: Verifica recupero
git checkout important-feature
cat important-feature.js  # Dovrebbe essere tutto a posto
```

### Problema 3: Merge Conflict Incasinato

#### Setup del Problema
```bash
# Prepara scenario conflict
git checkout main

# Crea branch 1
git checkout -b feature/conflict-a
echo "Version A implementation" > conflict-file.txt
git add conflict-file.txt
git commit -m "Implement version A"

# Crea branch 2 dallo stesso punto
git checkout main
git checkout -b feature/conflict-b
echo "Version B implementation" > conflict-file.txt
git add conflict-file.txt
git commit -m "Implement version B"

# Merge primo branch
git checkout main
git merge feature/conflict-a

# Tenta merge secondo branch (CONFLICT!)
git merge feature/conflict-b
```

#### Diagnosi
```bash
# Step 1: Analizza situazione
git status
# Should show "both modified: conflict-file.txt"

# Step 2: Vedi il conflitto
cat conflict-file.txt
# Vedrai i markers <<<<<<< ======= >>>>>>>

# Step 3: Opzioni disponibili
echo "Opzioni:"
echo "1. Risolvi manualmente"
echo "2. Abort merge"
echo "3. Usa versione specifica"
```

#### Risoluzione - Opzione 1: Manual Resolution
```bash
# Edita manualmente conflict-file.txt
echo "Merged implementation from both versions" > conflict-file.txt

git add conflict-file.txt
git commit -m "Resolve merge conflict"
```

#### Risoluzione - Opzione 2: Abort
```bash
# Se il merge è troppo complicato
git merge --abort

# Torna a stato pre-merge
git status  # Dovrebbe essere clean
```

### Problema 4: Commit al Branch Sbagliato

#### Setup del Problema
```bash
# Simula lavoro sul branch sbagliato
git checkout main  # Dovevi essere su feature branch!

# Fai lavoro importante
echo "// This should be on feature branch" > wrong-branch-work.js
git add wrong-branch-work.js
git commit -m "Important feature work"

# Ti accorgi dell'errore
echo "OOPS! This should be on feature branch, not main!"
```

#### Diagnosi
```bash
# Step 1: Verifica situazione
git log --oneline -3
git branch
```

#### Risoluzione
```bash
# Step 2: Crea feature branch dal commit corrente
git branch feature/correct-location

# Step 3: Reset main al commit precedente
git reset --hard HEAD~1

# Step 4: Verifica che main sia pulito
git log --oneline -3

# Step 5: Vai al feature branch
git checkout feature/correct-location

# Step 6: Verifica che il lavoro sia nel posto giusto
ls -la  # wrong-branch-work.js dovrebbe essere qui
git log --oneline -3
```

### Problema 5: File Accidentalmente Cancellato

#### Setup del Problema
```bash
# Crea file importante
echo "Critical configuration" > critical-config.json
echo '{"database": "production", "api_key": "secret"}' >> critical-config.json
git add critical-config.json
git commit -m "Add critical configuration"

# Simula cancellazione accidentale
rm critical-config.json

# Panic!
ls -la  # critical-config.json is gone!
```

#### Diagnosi
```bash
# Step 1: Verifica che il file sia tracciato da Git
git status
# Should show "deleted: critical-config.json"

# Step 2: Verifica che sia nel repository
git ls-files | grep critical-config
```

#### Risoluzione
```bash
# Step 3: Recupera dall'ultimo commit
git restore critical-config.json

# Step 4: Verifica recupero
ls -la
cat critical-config.json  # Dovrebbe essere tutto a posto
```

### Problema 6: Repository Sembra Corrotto

#### Setup del Problema
```bash
# Simula corruzione (NON fare questo su repository reali!)
# Corrompi un oggetto Git
echo "corrupted" > .git/objects/$(find .git/objects -name "*.txt" | head -1)

# Oppure simula index corrotto
echo "corrupted" > .git/index
```

#### Diagnosi
```bash
# Step 1: Test integrità
git status  # Potrebbe dare errori

# Step 2: File system check
git fsck --full
```

#### Risoluzione
```bash
# Step 3a: Se index corrotto
rm .git/index
git reset

# Step 3b: Se oggetti corrotti
git gc --aggressive

# Step 4: Verifica riparazione
git status
git fsck --full
```

## 🎯 Esercizi Avanzati

### Challenge 1: Recovery da Multiple Disasters

```bash
# Simula multiple problemi contemporaneamente
git reset --hard HEAD~3    # Perde commits
rm important-file.js       # Cancella file
git checkout nonexistent   # Entra in stato weird

# Tua missione: recupera tutto!
```

### Challenge 2: Team Disaster Simulation

```bash
# Simula repository remoto
mkdir remote-repo.git
cd remote-repo.git
git init --bare

cd ../git-troubleshooting-lab
git remote add origin ../remote-repo.git
git push origin main

# Simula force push disastroso
git reset --hard HEAD~2
git push --force origin main

# Simula altro team member che ha perso lavoro
# Come risolvi?
```

### Challenge 3: History Rewrite Emergency

```bash
# Simula commit con password
echo "password=supersecret123" > .env
git add .env
git commit -m "Add environment config"
git push origin main

# EMERGENCY: Password committed to public repo!
# Rimuovi dalla history completa
```

## ✅ Verifica Competenze

### Checklist Competenze Troubleshooting

```markdown
Dopo aver completato tutti gli esercizi, dovresti essere in grado di:

□ Diagnosticare problemi usando git status, git reflog, git log
□ Recuperare commit "persi" con reset accidentali
□ Ripristinare branch cancellati
□ Risolvere merge conflicts complessi
□ Spostare commit tra branch
□ Recuperare file cancellati
□ Riparare repository con problemi minori
□ Usare git fsck per diagnosticare corruzione
□ Applicare strategie di backup preventive
□ Lavorare metodicamente sotto pressione
```

### Test Finale

```bash
# Scenario complesso finale
# Hai 30 minuti per risolvere:

# 1. Reset ha cancellato 3 commit importanti
git reset --hard HEAD~3

# 2. Branch feature cancellato
git branch -D feature/important

# 3. File critico rimosso
rm critical-data.json

# 4. Merge conflict in corso
# (simula setup conflict e lascialo irrisolto)

# 5. Repository segnala errori fsck
# (corrompi minoremente un file in .git/)

# GO! Risolvi tutto metodicamente.
```

## 📚 Reference Quick

### Emergency Commands Reference

```bash
# RECOVERY ESSENTIALS
git reflog                    # Find lost commits
git reset --hard <hash>       # Recover to specific state
git branch <name> <hash>      # Recreate deleted branch
git restore <file>            # Recover deleted file
git merge --abort             # Cancel problematic merge
git rebase --abort            # Cancel problematic rebase

# DIAGNOSTICS
git status                    # Current state
git fsck --full              # Check integrity
git log --oneline --graph    # Visualize history
git remote -v                # Check remotes

# BACKUP BEFORE FIXES
git branch backup-$(date +%Y%m%d)
cp -r .git ../backup-git
git reflog > ../reflog-backup.txt
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Recovery Strategies](../guide/02-recovery-strategies.md)
- [➡️ Recovery Practice](02-recovery-practice.md)
