# Correzioni Sicure per Repository Condivisi

## 📚 Introduzione

Quando lavori in team, le operazioni di annullamento e correzione richiedono particolare attenzione per non interferire con il lavoro degli altri. Questa guida presenta strategie sicure per correggere errori in repository condivisi.

## 🎯 Principi Fondamentali per Team

### ✅ Operazioni Sempre Sicure
- **Nuovi commit** di correzione
- **Revert** di commit problematici  
- **Forward-only** corrections
- **Comunicazione** preventiva

### ❌ Operazioni Pericolose in Team
- **Rewrite history** di commit pushati
- **Force push** senza coordinamento
- **Reset hard** su branch condivisi
- **Amend** di commit pubblici

## 🛡️ Strategia: "Avanti, Non Indietro"

Il principio fondamentale è **non modificare mai la storia già condivisa**, ma aggiungere correzioni andando avanti.

## 📋 Scenario 1: Correggere un Bug in Commit Pushato

### Situazione
Hai pushato un commit con un bug e altri hanno già pullato.

```bash
# Setup: commit con bug già pushato
echo "function calculate(a, b) { return a - b; }" > math.js  # Bug: dovrebbe essere +
git add math.js
git commit -m "Add calculation function"
git push origin main

# Altri sviluppatori hanno già pullato
# Il tuo collega ha già basato lavoro su questo commit
```

### ❌ Soluzione Sbagliata (Pericolosa)
```bash
# NON FARE MAI questo se il commit è pushato
echo "function calculate(a, b) { return a + b; }" > math.js
git add math.js
git commit --amend -m "Add calculation function (fixed)"
git push --force origin main  # ❌ DANNEGGERÀ il lavoro dei colleghi
```

### ✅ Soluzione Sicura: Nuovo Commit di Fix
```bash
# Creare nuovo commit che corregge il bug
echo "function calculate(a, b) { return a + b; }" > math.js
git add math.js
git commit -m "Fix calculation function: use addition instead of subtraction"
git push origin main

# Storia risultante:
# * Fix calculation function: use addition instead of subtraction
# * Add calculation function
```

### ✅ Soluzione Avanzata: Fix + Squash nel Merge
```bash
# Su feature branch
git checkout -b fix-calculation
echo "function calculate(a, b) { return a + b; }" > math.js
git add math.js
git commit -m "Fix calculation bug"
git push origin fix-calculation

# Merge squash per pulire la storia
git checkout main
git merge --squash fix-calculation
git commit -m "Fix calculation function bug"
git push origin main
git branch -d fix-calculation
git push origin --delete fix-calculation
```

## 📋 Scenario 2: Rimuovere File Sensibili già Pushati

### Situazione
Hai pushato accidentalmente file con password o API keys.

```bash
# Il disastro è già successo
echo "API_KEY=sk-secret123456" > config.env
git add config.env
git commit -m "Add configuration"
git push origin main  # ❌ Credenziali esposte!
```

### 🚨 Azioni Immediate (Ordine Critico)

#### 1. Revoca Credenziali (ENTRO 5 MINUTI)
```bash
# PRIMA COSA: invalida le credenziali esposte
# - Cambia password immediatamente
# - Disattiva API keys
# - Ruota certificati
# - Notifica il team di sicurezza
```

#### 2. Valuta la Situazione
```bash
# Chi ha accesso al repository?
git log --pretty=format:"%h %an %ad" --since="1 hour ago"

# Il commit è già stato pullato da altri?
git branch -r --contains HEAD  # Verifica branch remoti
```

#### 3A. Se Nessuno Ha Pullato (Raro, ma possibile)
```bash
# Verifica che il commit non sia referenziato altrove
git for-each-ref --format="%(refname) %(objectname)" | grep COMMIT-SHA

# Se sicuro, rimuovi dalla storia
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch config.env' \
  --prune-empty --tag-name-filter cat -- --all

# Force push con protezione
git push --force-with-lease origin main

# Notifica il team
echo "ALERT: Removed sensitive file from git history. Please re-clone."
```

#### 3B. Se Altri Hanno Pullato (Caso Normale)
```bash
# Rimuovi il file e committa
git rm config.env
git commit -m "Remove sensitive configuration file"

# Aggiorna .gitignore
echo "config.env" >> .gitignore
echo "*.env" >> .gitignore
git add .gitignore
git commit -m "Add environment files to gitignore"

# Crea template sicuro
echo "API_KEY=your-api-key-here" > config.env.template
git add config.env.template
git commit -m "Add safe configuration template"

git push origin main

# Notifica il team
echo "ALERT: Sensitive file removed. Use config.env.template as base."
```

## 📋 Scenario 3: Annullare Merge Problematico

### Situazione
Hai fatto merge di un branch che ha rotto il codice principale.

```bash
# Setup: merge problematico
git checkout main
git merge feature-problematic  # Questo merge rompe tutto
git push origin main

# Il build è rotto, i test falliscono
```

### ✅ Soluzione: Revert del Merge
```bash
# Identificare il commit di merge
git log --oneline -5
# a1b2c3d (HEAD, origin/main) Merge branch 'feature-problematic'
# d4e5f6g Add feature X
# g7h8i9j Last working commit
# ...

# Revert del merge
git revert -m 1 a1b2c3d

# -m 1 specifica di revertire verso il primo parent (main branch)
git push origin main

# Comunicare il fix
git commit --amend -m "Revert problematic merge that broke build

This reverts commit a1b2c3d.
- Build was failing due to incompatible dependencies
- Feature needs rework before re-merge
- Main branch is now stable again"

git push origin main
```

### ✅ Fix del Branch e Re-Merge
```bash
# Dopo aver risolto i problemi nel branch
git checkout feature-problematic
# Applica le correzioni necessarie...
git add .
git commit -m "Fix compatibility issues"
git push origin feature-problematic

# Re-merge quando pronto
git checkout main
git merge feature-problematic
git push origin main
```

## 📋 Scenario 4: Correggere Messaggio di Commit Pushato

### Situazione
Hai pushato un commit con messaggio confuso o con errori.

```bash
# Commit con messaggio sbagliato già pushato
git commit -m "fix stuf"  # Typo + vago
git push origin main
```

### ❌ Soluzione Sbagliata
```bash
# NON FARE
git commit --amend -m "Fix authentication bug in login module"
git push --force origin main  # ❌ Pericoloso per il team
```

### ✅ Soluzione Sicura: Commit di Chiarimento
```bash
# Aggiungere commit che chiarisce
git commit --allow-empty -m "Previous commit: Fix authentication bug in login module

The previous commit 'fix stuf' addressed:
- Null pointer exception in login validation
- Session timeout not being handled correctly
- Added proper error logging for debugging"

git push origin main
```

### ✅ Alternativa: Note del Commit
```bash
# Aggiungere note al commit esistente
git notes add -m "Clarification: This commit fixed authentication bugs in login module" HEAD~1
git push origin refs/notes/commits
```

## 📋 Scenario 5: Coordinare Correzioni in Team

### Workflow di Comunicazione

#### 1. Pre-Correzione: Avviso Team
```bash
# Creare issue o ticket
echo "ALERT: Need to fix critical bug in commit a1b2c3d
- Authentication is broken
- Planning revert + fix
- Please pause pulls for 30 minutes
- Will update when safe to continue"

# Comunicare su chat team
# Taggare stakeholders rilevanti
```

#### 2. Durante Correzione: Status Updates
```bash
# Aggiornamenti regolari
echo "UPDATE 10:15 - Reverting problematic commit"
echo "UPDATE 10:20 - Working on fix in feature branch"  
echo "UPDATE 10:30 - Fix ready, testing locally"
echo "UPDATE 10:35 - Fix pushed, safe to pull"
```

#### 3. Post-Correzione: Documentazione
```bash
# Commit dettagliato con spiegazione
git commit -m "Fix authentication module crash

Problem:
- Commit a1b2c3d introduced null pointer exception
- Login was failing for users with special characters in username
- Session cleanup was not working correctly

Solution:
- Added null checks in validateUser()
- Escaped special characters in username processing  
- Fixed session cleanup timeout handling

Testing:
- All existing tests pass
- Added regression test for special character usernames
- Manual testing completed for edge cases

Impact:
- Authentication now works for all username types
- Session management is more robust
- No breaking changes to existing API"
```

## 🔧 Tools per Repository Condivisi

### 1. Pre-Push Hooks per Sicurezza
```bash
#!/bin/sh
# .git/hooks/pre-push

# Verifica che non si stia pushando su main senza PR
branch=$(git rev-parse --abbrev-ref HEAD)
if [ "$branch" = "main" ]; then
    echo "❌ Direct push to main is not allowed"
    echo "Please use Pull Request workflow"
    exit 1
fi

# Verifica che non ci siano file sensibili
if git diff --cached --name-only | grep -E "\.(env|key|pem|p12)$"; then
    echo "❌ Potential sensitive files detected"
    echo "Please review before pushing"
    exit 1
fi
```

### 2. Alias per Operazioni Sicure
```bash
# Configurazioni globali per team safety
git config --global alias.safe-push '!git push --force-with-lease'
git config --global alias.team-revert 'revert -m 1'
git config --global alias.fix-commit 'commit --allow-empty'

# Workflow protetto
git config --global alias.safe-fix '!f() { 
    echo "Creating fix for: $1"; 
    git checkout -b "fix-$(date +%s)"; 
    echo "Make your changes and commit"; 
    echo "Then: git checkout main && git merge --no-ff fix-*"; 
}; f'
```

### 3. Script di Verifica Pre-Operazione
```bash
#!/bin/bash
# team-safety-check.sh

echo "=== TEAM SAFETY CHECK ==="

# Verifica stato remoto
git fetch origin
BEHIND=$(git rev-list --count HEAD..origin/main)
if [ $BEHIND -gt 0 ]; then
    echo "⚠️  You are $BEHIND commits behind origin/main"
    echo "Consider pulling latest changes first"
fi

# Verifica commit non pushati
AHEAD=$(git rev-list --count origin/main..HEAD)
if [ $AHEAD -gt 0 ]; then
    echo "📝 You have $AHEAD unpushed commits:"
    git log --oneline origin/main..HEAD
fi

# Verifica branch tracking
TRACKING=$(git rev-parse --abbrev-ref --symbolic-full-name @{u} 2>/dev/null)
if [ -z "$TRACKING" ]; then
    echo "⚠️  Current branch is not tracking a remote branch"
fi

echo "✅ Safety check completed"
```

## 📊 Decision Matrix per Repository Condivisi

| Situazione | Commit Pushato? | Altri Hanno Pullato? | Soluzione Sicura |
|------------|----------------|---------------------|------------------|
| Bug fix | ❌ No | - | Amend o nuovo commit |
| Bug fix | ✅ Sì | ❌ No certo | Force-with-lease (con cautela) |
| Bug fix | ✅ Sì | ✅ Sì | Nuovo commit fix |
| Messaggio sbagliato | ✅ Sì | ✅ Sì | Commit chiarimento o note |
| File sensibili | ✅ Sì | ❓ Forse | Revoca credenziali + rimozione |
| Merge problematico | ✅ Sì | ✅ Sì | Revert merge |
| Storia complessa | ✅ Sì | ✅ Sì | Squash in PR futuro |

## 💡 Best Practices per Team

### 1. Comunicazione Proattiva
- **Avvisa sempre** prima di operazioni rischiose
- **Documenta** ogni correzione importante
- **Coordina** i tempi con il team
- **Condividi** le lezioni apprese

### 2. Workflow Protettivo
- **Pull Request** obbligatorie per main
- **Review** per tutte le correzioni critiche
- **Testing** automatico prima del merge
- **Rollback plan** per ogni deploy

### 3. Recovery Preparedness
- **Backup** automatici regolari
- **Documentation** delle procedure di emergency
- **Training** del team su recovery
- **Contact list** per emergenze

## 📝 Riassunto

Per repository condivisi la regola è: **"Forward, not backward"**

**Operazioni sicure**:
- Nuovi commit di correzione
- Revert di merge problematici
- Comunicazione preventiva
- Documentazione dettagliata

**Da evitare**:
- Rewrite history di commit pushati
- Force push senza coordinamento  
- Correzioni silenti senza comunicazione
- Operazioni rischiose negli orari di punta

**Chiavi del successo**:
1. **Comunicazione** costante con il team
2. **Documentazione** di ogni correzione
3. **Testing** prima di ogni push
4. **Backup** e rollback plan pronti
5. **Training** continuo sulle best practices

Ricorda: in un team è meglio essere **trasparenti e lenti** che **veloci e rischiosi**!
