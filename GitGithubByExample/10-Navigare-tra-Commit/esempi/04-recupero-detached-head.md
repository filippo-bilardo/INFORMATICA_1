# 04 - Recupero da Detached HEAD: Missioni di Salvataggio Git

## 📖 Scenario

Sei il **DevOps Engineer** di **TechRescue Inc.**, e ricevi chiamate di emergenza da developer che si sono "persi" in detached HEAD state con lavoro importante non salvato. Devi padroneggiare tutte le tecniche di recupero per salvare situazioni disperate e insegnare ai team come evitare e gestire questi problemi.

## 🎯 Obiettivi dell'Esempio

- ✅ Simulazione realistica di situazioni problematiche
- ✅ Tecniche di recupero da detached HEAD
- ✅ Salvataggio di commit "orfani"
- ✅ Strategie di prevenzione
- ✅ Workflow di emergenza strutturati
- ✅ Training per situazioni critiche

## 📋 Prerequisiti

- Comprensione di HEAD e detached HEAD
- Familiarità con git reflog
- Conoscenza base di branch e commit
- Esperienza con git checkout/switch

## ⏱️ Durata Stimata

**50-70 minuti** (scenari di emergenza + recovery)

---

## 🚨 Setup degli Scenari di Emergenza

### 1. Creazione del Repository "Problematico"

```bash
# Setup ambiente di rescue training
cd ~/progetti
mkdir techrescue-training
cd techrescue-training
git init

echo "# TechRescue Emergency Training Repository" > README.md
git add .
git commit -m "initial: Setup training environment"

# Crea un progetto realistico con storia significativa
mkdir src docs tests
cat > src/app.js << 'EOF'
// TechRescue Main Application
class TechRescueApp {
    constructor() {
        this.version = '1.0.0';
        this.services = [];
    }
    
    start() {
        console.log(`TechRescue v${this.version} starting...`);
        this.loadServices();
    }
    
    loadServices() {
        this.services = ['monitoring', 'alerting', 'logging'];
        console.log('Services loaded:', this.services);
    }
}

module.exports = TechRescueApp;
EOF

echo "# TechRescue Documentation" > docs/README.md
git add .
git commit -m "feat: Initial application structure"

# Aggiungi feature importante
cat > src/monitoring.js << 'EOF'
class MonitoringService {
    constructor() {
        this.alerts = [];
        this.isActive = false;
    }
    
    startMonitoring() {
        this.isActive = true;
        console.log('Monitoring service started');
    }
    
    addAlert(type, message) {
        const alert = {
            id: Date.now(),
            type: type,
            message: message,
            timestamp: new Date()
        };
        this.alerts.push(alert);
        return alert;
    }
}

module.exports = MonitoringService;
EOF

git add .
git commit -m "feat: Monitoring service implementation"

# Branch feature per sviluppo parallelo
git branch feature/advanced-alerts
git switch feature/advanced-alerts

cat >> src/monitoring.js << 'EOF'

    // Advanced alerting methods
    sendCriticalAlert(message) {
        return this.addAlert('CRITICAL', message);
    }
    
    sendWarningAlert(message) {
        return this.addAlert('WARNING', message);
    }
    
    getAlertsCount() {
        return this.alerts.length;
    }
EOF

git add .
git commit -m "feat: Advanced alerting system"

# Torna a main e aggiungi altro sviluppo
git switch main

cat > src/logger.js << 'EOF'
class Logger {
    constructor() {
        this.logs = [];
    }
    
    log(level, message) {
        const logEntry = {
            timestamp: new Date(),
            level: level,
            message: message
        };
        this.logs.push(logEntry);
        console.log(`[${level}] ${message}`);
    }
    
    info(message) { this.log('INFO', message); }
    warn(message) { this.log('WARN', message); }
    error(message) { this.log('ERROR', message); }
}

module.exports = Logger;
EOF

git add .
git commit -m "feat: Logging system implementation"

# Tag per release
git tag v1.0.0

# Più sviluppo
echo "// Version bump" >> src/app.js
git add .
git commit -m "chore: Version preparation for v1.1"

echo "🚨 Training repository setup completato!"
echo "📊 Cronologia:"
git log --oneline --graph --all
```

### 2. Preparazione Scenari di Emergenza

```bash
# Crea script per simulare scenari problematici
cat > emergency-scenarios.sh << 'EOF'
#!/bin/bash

# Emergency Scenario Simulator
# ============================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Scenario 1: Developer perso in detached HEAD con modifiche
scenario_1_lost_with_changes() {
    echo -e "${RED}🚨 EMERGENCY CALL #1${NC}"
    echo "Developer says: 'Ho fatto checkout di un vecchio commit per test,"
    echo "ho fatto modifiche importanti, e ora Git dice che sono in detached HEAD!"
    echo "Come salvo il mio lavoro?'"
    echo ""
    
    # Simula la situazione
    git checkout HEAD~3
    echo "Situazione simulata: siamo in detached HEAD"
    
    # Crea modifiche "importanti"
    cat > src/emergency-fix.js << 'EMERGENCY_EOF'
// CRITICAL EMERGENCY FIX
class EmergencyFix {
    constructor() {
        this.criticalFix = true;
        this.implementedAt = new Date();
    }
    
    applyCriticalFix() {
        console.log('Applying critical security fix...');
        // Importante logica di fix che NON DEVE essere persa
        return this.validateFix();
    }
    
    validateFix() {
        return this.criticalFix && this.implementedAt;
    }
}

module.exports = EmergencyFix;
EMERGENCY_EOF
    
    # Modifica file esistente
    echo "// EMERGENCY: Critical security patch applied" >> src/app.js
    
    echo -e "${YELLOW}📍 STATO ATTUALE:${NC}"
    git status
    echo ""
    echo -e "${RED}⚠️  HELP NEEDED: Come salvare queste modifiche critiche?${NC}"
}

# Scenario 2: Commit fatto in detached HEAD
scenario_2_orphaned_commits() {
    echo -e "${RED}🚨 EMERGENCY CALL #2${NC}"
    echo "Developer says: 'Ho fatto commit in detached HEAD!"
    echo "Ora non riesco più a trovarli. Sono spariti?'"
    echo ""
    
    # Simula commits orfani
    git checkout HEAD~2
    
    # Fa alcuni commit
    echo "// Feature sperimentale importante" > src/experimental.js
    git add .
    git commit -m "feat: Experimental feature prototype"
    
    echo "// Miglioramenti alla feature" >> src/experimental.js
    git add .
    git commit -m "improvement: Enhanced experimental feature"
    
    echo "// Bug fix critico" >> src/experimental.js
    git add .
    git commit -m "fix: Critical bug in experimental feature"
    
    ORPHANED_COMMIT=$(git rev-parse HEAD)
    
    # Torna a main (commit diventano "orfani")
    git switch main
    
    echo -e "${YELLOW}📍 STATO ATTUALE:${NC}"
    echo "Il developer ha fatto 3 commit importanti, ma ora sono 'persi'"
    echo "Hash dell'ultimo commit orfano: $ORPHANED_COMMIT"
    echo ""
    echo -e "${RED}⚠️  HELP NEEDED: Come recuperare questi commit?${NC}"
}

# Scenario 3: Confusione completa
scenario_3_total_confusion() {
    echo -e "${RED}🚨 EMERGENCY CALL #3${NC}"
    echo "Developer says: 'Non so più dove sono, ho fatto checkout,"
    echo "poi commit, poi switch, poi ancora checkout..."
    echo "Il codice è sparito e non ricordo più niente!'"
    echo ""
    
    # Simula navigazione confusa
    git checkout v1.0.0
    echo "// Modifica confusa 1" > src/confused.js
    git add . && git commit -m "confusing change 1"
    
    git checkout HEAD~1
    echo "// Modifica confusa 2" >> src/confused.js
    git add . && git commit -m "confusing change 2"
    
    git checkout main
    git checkout HEAD~1
    echo "// Modifica confusa 3" > src/another-confused.js
    git add . && git commit -m "confusing change 3"
    
    echo -e "${YELLOW}📍 STATO ATTUALE:${NC}"
    echo "Developer completamente perso con multiple modifiche sparse"
    git log --oneline -3
    echo ""
    echo -e "${RED}⚠️  HELP NEEDED: Come fare ordine in questo caos?${NC}"
}

# Export functions
export -f scenario_1_lost_with_changes
export -f scenario_2_orphaned_commits  
export -f scenario_3_total_confusion
EOF

chmod +x emergency-scenarios.sh
echo "🆘 Emergency scenarios ready!"
```

---

## 🛟 Missioni di Salvataggio

### Missione 1: Salvataggio Modifiche in Detached HEAD

```bash
echo "=== MISSIONE 1: SALVATAGGIO MODIFICHE IN DETACHED HEAD ==="

source emergency-scenarios.sh

# Crea checkpoint di sicurezza
git tag rescue-checkpoint-1

echo "🚨 Simulando emergenza #1..."
scenario_1_lost_with_changes

echo ""
echo "🛟 INIZIANDO PROCEDURA DI SALVATAGGIO..."

# Passo 1: Valutazione della situazione
echo "📊 PASSO 1: VALUTAZIONE SITUAZIONE"
echo "Stato HEAD:"
git log --oneline -1
echo ""
echo "Stato working directory:"
git status --short
echo ""
echo "Posizione attuale:"
git log --oneline --graph -5

# Passo 2: Salvare le modifiche 
echo ""
echo "💾 PASSO 2: SALVATAGGIO MODIFICHE"

# Opzione A: Commit locale in detached HEAD
echo "Creando commit di salvataggio..."
git add .
RESCUE_COMMIT=$(git commit -m "RESCUE: Emergency changes in detached HEAD - $(date)" --quiet && git rev-parse HEAD)

echo "✅ Modifiche salvate nel commit: $RESCUE_COMMIT"

# Passo 3: Creare branch di salvataggio
echo ""
echo "🌿 PASSO 3: CREAZIONE BRANCH DI SALVATAGGIO"

RESCUE_BRANCH="rescue/emergency-fix-$(date +%Y%m%d-%H%M%S)"
git branch "$RESCUE_BRANCH"

echo "✅ Branch di salvataggio creato: $RESCUE_BRANCH"

# Passo 4: Tornare al branch principale
echo ""
echo "🏠 PASSO 4: RITORNO AL BRANCH PRINCIPALE"

git switch main
echo "✅ Tornato su main branch"

# Passo 5: Verifica del salvataggio
echo ""
echo "🔍 PASSO 5: VERIFICA SALVATAGGIO"

echo "Commit nel branch di rescue:"
git log --oneline -1 "$RESCUE_BRANCH"

echo ""
echo "File salvati:"
git show --name-only "$RESCUE_BRANCH"

echo ""
echo "Contenuto del fix critico:"
git show "$RESCUE_BRANCH":src/emergency-fix.js | head -10

# Passo 6: Integrazione sicura
echo ""
echo "🔄 PASSO 6: INTEGRAZIONE SICURA"

echo "Opzioni per integrare il lavoro salvato:"
echo "1. Merge del branch rescue: git merge $RESCUE_BRANCH"
echo "2. Cherry-pick del commit: git cherry-pick $RESCUE_COMMIT"
echo "3. Revisione e commit manuale"

echo ""
echo "Procediamo con cherry-pick per sicurezza..."
git cherry-pick "$RESCUE_COMMIT" --no-commit
git status

echo "✅ Modifiche recuperate e pronte per review!"

# Cleanup
git add .
git commit -m "rescue: Recovered emergency fix from detached HEAD

- Critical security patch recovered
- Emergency fix implementation restored  
- Validated fix logic maintained

Original commit: $RESCUE_COMMIT
Rescue branch: $RESCUE_BRANCH"

git branch -d "$RESCUE_BRANCH"
echo "🎉 MISSIONE 1 COMPLETATA CON SUCCESSO!"
```

### Missione 2: Recupero Commit Orfani

```bash
echo "=== MISSIONE 2: RECUPERO COMMIT ORFANI ==="

# Reset per nuova emergenza
git reset --hard rescue-checkpoint-1
git tag rescue-checkpoint-2

echo "🚨 Simulando emergenza #2..."
scenario_2_orphaned_commits

echo ""
echo "🛟 INIZIANDO PROCEDURA DI RECUPERO COMMIT ORFANI..."

# Passo 1: Investigazione reflog
echo "📊 PASSO 1: INVESTIGAZIONE REFLOG"

echo "Cronologia reflog completa:"
git reflog --oneline -15

echo ""
echo "Ricerca di commit orfani:"
git reflog | grep -E "(commit|checkout)" | head -10

# Passo 2: Identificazione commit persi
echo ""
echo "🔍 PASSO 2: IDENTIFICAZIONE COMMIT PERSI"

echo "Cerco commit recenti non raggiungibili..."
git fsck --unreachable | head -10

echo ""
echo "Analizzando reflog per pattern commit..."
LOST_COMMITS=$(git reflog --pretty=format:"%h" | head -10)

echo "Potenziali commit persi:"
for commit in $LOST_COMMITS; do
    if ! git merge-base --is-ancestor "$commit" HEAD 2>/dev/null; then
        echo "🔍 $commit: $(git log --oneline -1 $commit 2>/dev/null || echo 'invalid')"
    fi
done

# Passo 3: Recupero guidato
echo ""
echo "💾 PASSO 3: RECUPERO GUIDATO"

# Trova commit specifici dal reflog
echo "Cerco commit con 'experimental'..."
EXPERIMENTAL_COMMITS=$(git reflog --grep="experimental" --pretty=format:"%h" | head -3)

for commit in $EXPERIMENTAL_COMMITS; do
    if git cat-file -e "$commit" 2>/dev/null; then
        echo "✅ Trovato commit valido: $commit"
        echo "   Messaggio: $(git log --oneline -1 $commit)"
        
        # Crea branch per questo commit
        RECOVERY_BRANCH="recovery/experimental-$(echo $commit | cut -c1-7)"
        git branch "$RECOVERY_BRANCH" "$commit"
        echo "   🌿 Salvato nel branch: $RECOVERY_BRANCH"
    fi
done

# Passo 4: Consolidamento recovery
echo ""
echo "🔄 PASSO 4: CONSOLIDAMENTO RECOVERY"

echo "Branch di recovery creati:"
git branch | grep recovery

# Trova l'ultimo commit della catena sperimentale
LATEST_EXPERIMENTAL=$(git reflog --grep="Critical bug" --pretty=format:"%h" | head -1)

if [ ! -z "$LATEST_EXPERIMENTAL" ] && git cat-file -e "$LATEST_EXPERIMENTAL" 2>/dev/null; then
    echo "🎯 Ultimo commit sperimentale trovato: $LATEST_EXPERIMENTAL"
    
    # Crea branch principale di recovery
    git branch recovery/experimental-complete "$LATEST_EXPERIMENTAL"
    
    echo "📋 Cronologia recuperata:"
    git log --oneline recovery/experimental-complete -3
    
    echo ""
    echo "📁 File recuperati:"
    git show --name-only recovery/experimental-complete
    
    echo ""
    echo "📄 Contenuto del file sperimentale:"
    git show recovery/experimental-complete:src/experimental.js
fi

# Passo 5: Validazione e integrazione
echo ""
echo "✅ PASSO 5: VALIDAZIONE E INTEGRAZIONE"

echo "Opzioni di integrazione:"
echo "1. Merge completo: git merge recovery/experimental-complete"
echo "2. Cherry-pick selettivo di commit specifici"
echo "3. Revisione manuale e nuovo commit"

echo ""
echo "Procediamo con merge controllato..."

# Merge con messaggio dettagliato
git merge recovery/experimental-complete --no-ff -m "recovery: Merge experimental features from orphaned commits

- Recovered 3 commits from detached HEAD development
- Experimental feature prototype and enhancements
- Critical bug fixes included
- All changes reviewed and validated

Recovery branches: recovery/experimental-*
Original development session recovered from reflog"

echo "🎉 MISSIONE 2 COMPLETATA CON SUCCESSO!"
echo "✅ Tutti i commit orfani sono stati recuperati e integrati!"
```

### Missione 3: Risoluzione Caos Totale

```bash
echo "=== MISSIONE 3: RISOLUZIONE CAOS TOTALE ==="

# Reset per nuova emergenza
git reset --hard rescue-checkpoint-2
git tag rescue-checkpoint-3

echo "🚨 Simulando emergenza #3..."
scenario_3_total_confusion

echo ""
echo "🛟 INIZIANDO PROCEDURA DI RISOLUZIONE CAOS..."

# Passo 1: Assessment completo della situazione
echo "📊 PASSO 1: ASSESSMENT COMPLETO"

echo "🗺️ Mappa completa della cronologia:"
git reflog --oneline -20

echo ""
echo "🌿 Branch disponibili:"
git branch -a

echo ""
echo "📍 Posizione attuale:"
git log --oneline -1
git status

# Passo 2: Mappatura delle modifiche
echo ""
echo "🗂️ PASSO 2: MAPPATURA MODIFICHE"

echo "Creando mappa di tutte le modifiche recenti..."

cat > chaos-recovery-map.txt << 'EOF'
# Chaos Recovery Map
# ==================

## Obiettivo
Recuperare tutte le modifiche sparse e riorganizzare logicamente

## Strategia
1. Identificare tutti i commit con modifiche
2. Categorizzare per tipo/feature
3. Consolidare in branch logici
4. Validare e integrare progressivamente

## Timeline Discovery
EOF

echo "📝 Analizzando reflog per modifiche..."
git reflog --pretty=format:"%h %gd %gs" -15 | while read hash ref desc; do
    if git cat-file -e "$hash" 2>/dev/null; then
        files=$(git show --name-only "$hash" 2>/dev/null | tail -n +2)
        if [ ! -z "$files" ]; then
            echo "- $hash: $desc ($files)" >> chaos-recovery-map.txt
        fi
    fi
done

echo "Mappa delle modifiche creata:"
cat chaos-recovery-map.txt

# Passo 3: Recovery strategico
echo ""
echo "🎯 PASSO 3: RECOVERY STRATEGICO"

# Identifica commit per tipo
echo "Categorizzando commit per feature..."

# Recovery branch per confused changes
CONFUSED_COMMITS=$(git reflog --grep="confusing" --pretty=format:"%h")
RECOVERY_BRANCHES=()

for commit in $CONFUSED_COMMITS; do
    if git cat-file -e "$commit" 2>/dev/null; then
        # Determina categoria basata sui file
        files=$(git show --name-only "$commit" 2>/dev/null | grep -v "^$")
        
        if echo "$files" | grep -q "confused.js"; then
            branch_name="recovery/confused-feature"
        elif echo "$files" | grep -q "another-confused.js"; then
            branch_name="recovery/another-feature"
        else
            branch_name="recovery/misc-changes"
        fi
        
        # Crea branch se non esiste
        if ! git show-ref --verify --quiet "refs/heads/$branch_name"; then
            git branch "$branch_name" "$commit"
            RECOVERY_BRANCHES+=("$branch_name")
            echo "✅ Creato branch: $branch_name da $commit"
        fi
    fi
done

# Passo 4: Consolidamento intelligente
echo ""
echo "🔄 PASSO 4: CONSOLIDAMENTO INTELLIGENTE"

echo "Branch di recovery creati:"
for branch in "${RECOVERY_BRANCHES[@]}"; do
    echo "  🌿 $branch"
    echo "     Commit: $(git log --oneline -1 $branch)"
    echo "     File: $(git show --name-only $branch | tail -n +2)"
    echo ""
done

# Strategia di consolidamento
echo "🧩 Strategia di consolidamento:"

# 1. Unisci modifiche simili
echo "1. Consolidando modifiche simili..."

# Crea branch unificato per confused features
git checkout -b recovery/consolidated-features

# Cherry-pick intelligente
for branch in "${RECOVERY_BRANCHES[@]}"; do
    echo "   Integrando $branch..."
    
    # Prova cherry-pick
    if git cherry-pick "$branch" --no-commit 2>/dev/null; then
        echo "   ✅ Integrato automaticamente"
    else
        # Risoluzione manuale per conflitti
        echo "   🔧 Risoluzione manuale necessaria"
        git reset --hard HEAD
        
        # Estrazione manuale dei file
        git checkout "$branch" -- . 2>/dev/null || true
        git add .
    fi
done

# Commit consolidato
git commit -m "recovery: Consolidated all confused/experimental changes

- Recovered multiple detached HEAD sessions
- Consolidated confused.js modifications
- Integrated another-confused.js features
- Resolved conflicts and duplications

Recovery strategy:
- Mapped all reflog entries
- Categorized by file/feature type
- Strategic consolidation in unified branch
- Manual conflict resolution applied

All original work preserved and organized."

# Passo 5: Validazione finale
echo ""
echo "✅ PASSO 5: VALIDAZIONE FINALE"

echo "📊 Stato finale dopo recovery:"
git log --oneline -3

echo ""
echo "📁 File recuperati:"
ls -la src/

echo ""
echo "🔍 Verifica integrità:"
for file in src/*.js; do
    if [ -f "$file" ]; then
        lines=$(wc -l < "$file")
        echo "  ✅ $file: $lines linee"
    fi
done

# Integrazione finale nel main
echo ""
echo "🏠 Integrazione finale nel branch main..."

git switch main
git merge recovery/consolidated-features --no-ff -m "recovery: Integrate all recovered work from chaos resolution

- Successfully recovered all lost/confused modifications
- Consolidated multiple detached HEAD sessions
- Resolved timeline confusion and conflicting changes
- All developer work preserved and organized

Recovery operation completed successfully.
No data loss detected."

echo "🎉 MISSIONE 3 COMPLETATA CON SUCCESSO!"
echo "✅ Caos totale risolto, tutto il lavoro recuperato!"

# Cleanup recovery branches
echo ""
echo "🧹 Cleanup branch temporanei..."
git branch -d recovery/consolidated-features
for branch in "${RECOVERY_BRANCHES[@]}"; do
    git branch -d "$branch" 2>/dev/null || true
done

rm -f chaos-recovery-map.txt
```

---

## 🎓 Training e Prevenzione

### Creazione Kit di Emergency Response

```bash
echo "=== CREAZIONE KIT DI EMERGENCY RESPONSE ==="

# Crea toolkit completo per team
mkdir -p git-rescue-toolkit
cd git-rescue-toolkit

# Script principale di rescue
cat > git-rescue.sh << 'EOF'
#!/bin/bash

# Git Rescue Toolkit
# ==================
# Emergency response script for Git disasters

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🛟 Git Rescue Toolkit${NC}"
echo "===================="

# Menu principale
show_menu() {
    echo ""
    echo "Select emergency type:"
    echo "1. 🚨 Lost in detached HEAD with changes"
    echo "2. 👻 Missing commits (orphaned)"
    echo "3. 🌪️  Total confusion/chaos"
    echo "4. 📊 Assessment mode (diagnosis)"
    echo "5. 🔧 Custom recovery"
    echo "6. 📚 Show rescue guide"
    echo "0. Exit"
    echo ""
    read -p "Enter choice [0-6]: " choice
}

# Funzioni di rescue specifiche
rescue_detached_head() {
    echo -e "${YELLOW}🚨 Detached HEAD Recovery${NC}"
    echo "=========================="
    
    echo "Current situation:"
    git status
    
    echo ""
    echo "Recovery options:"
    echo "1. Save changes and create rescue branch"
    echo "2. Stash changes and return to main"
    echo "3. Commit here and cherry-pick later"
    
    read -p "Choose option [1-3]: " opt
    
    case $opt in
        1)
            echo "Creating rescue branch..."
            git add .
            git commit -m "RESCUE: Changes from detached HEAD - $(date)"
            branch_name="rescue/detached-head-$(date +%Y%m%d-%H%M%S)"
            git branch "$branch_name"
            git switch main
            echo "✅ Created rescue branch: $branch_name"
            ;;
        2)
            echo "Stashing changes..."
            git stash push -m "Detached HEAD rescue - $(date)"
            git switch main
            echo "✅ Changes stashed. Use 'git stash pop' to recover"
            ;;
        3)
            echo "Committing in place..."
            git add .
            commit_hash=$(git commit -m "RESCUE: Detached HEAD work - $(date)" && git rev-parse HEAD)
            git switch main
            echo "✅ Commit created: $commit_hash"
            echo "   Use: git cherry-pick $commit_hash"
            ;;
    esac
}

# Assessment function
assess_situation() {
    echo -e "${BLUE}📊 Git Situation Assessment${NC}"
    echo "============================"
    
    echo "📍 Current Position:"
    git log --oneline -1
    
    echo ""
    echo "📊 Repository Status:"
    git status --short
    
    echo ""
    echo "🗂️ Recent Navigation (reflog):"
    git reflog --oneline -10
    
    echo ""
    echo "🌿 Available Branches:"
    git branch -a
    
    echo ""
    echo "🏷️ Tags:"
    git tag | tail -5
    
    echo ""
    echo "💾 Stashes:"
    git stash list
}

# Main logic
main() {
    while true; do
        show_menu
        case $choice in
            1) rescue_detached_head ;;
            2) echo "Orphaned commits recovery - Feature coming soon" ;;
            3) echo "Chaos resolution - Feature coming soon" ;;
            4) assess_situation ;;
            5) echo "Custom recovery - Feature coming soon" ;;
            6) cat rescue-guide.md 2>/dev/null || echo "Guide not found" ;;
            0) echo "Stay safe! 🛟"; exit 0 ;;
            *) echo "Invalid choice" ;;
        esac
        
        echo ""
        read -p "Press Enter to continue..."
    done
}

main
EOF

chmod +x git-rescue.sh

# Guida di emergenza
cat > rescue-guide.md << 'EOF'
# 🛟 Git Emergency Response Guide

## 🚨 Quick Emergency Actions

### Detached HEAD with Changes
```bash
# IMMEDIATE: Don't panic!
git status  # See what you have

# SAVE WORK:
git add .
git commit -m "RESCUE: Emergency save"
git branch rescue-$(date +%H%M%S)  # Create rescue branch
git switch main  # Return to safety
```

### Lost Commits
```bash
# FIND THEM:
git reflog  # Shows ALL your moves
git fsck --unreachable  # Shows orphaned commits

# RECOVER:
git branch rescue-branch <commit-hash>
```

### Totally Lost
```bash
# ASSESS:
git reflog --oneline -20  # Your recent history
git status  # Current state

# SAFE PLACE:
git switch main  # Or master
git stash  # Save any changes
```

## 🔧 Advanced Recovery

### Cherry-pick Strategy
```bash
# Pick specific commits from anywhere:
git cherry-pick <commit-hash>
git cherry-pick <commit-hash> --no-commit  # Review first
```

### Reflog Navigation
```bash
# Go back in time:
git reset --hard HEAD@{5}  # 5 moves ago
git checkout HEAD@{10}     # Look at 10 moves ago
```

## 🛡️ Prevention

### Before Experimenting
```bash
git tag experiment-start  # Bookmark
git branch backup  # Safety copy
git stash push -m "Before experiment"  # Save changes
```

### Safe Navigation
```bash
git switch -  # Go back to previous branch
git status  # Always check before moving
git log --oneline -5  # See where you are
```

## 📞 Emergency Contacts

When all else fails:
1. Don't force push anything
2. Don't delete branches hastily  
3. Ask for help with exact git status output
4. Reflog is your friend - it keeps everything for 30+ days

Remember: Git rarely loses data permanently!
EOF

# Checklist di prevenzione
cat > prevention-checklist.md << 'EOF'
# ✅ Git Safety Prevention Checklist

## Before Any Risky Operation

- [ ] Current branch is known: `git branch --show-current`
- [ ] Working directory is clean: `git status`
- [ ] Recent work is committed or stashed
- [ ] Know how to get back: remember branch name

## Before Checkout/Switch

- [ ] Save current work: `git stash` or `git commit`
- [ ] Know target: `git log --oneline <target>`
- [ ] Plan return: remember current branch

## Before Experiments

- [ ] Create safety branch: `git branch experiment-backup`
- [ ] Tag current position: `git tag experiment-start`
- [ ] Stash any uncommitted work

## Emergency Preparedness

- [ ] Know git reflog command
- [ ] Know git status command
- [ ] Know git switch - command
- [ ] Have rescue script accessible

## Team Guidelines

- [ ] Never work directly in detached HEAD
- [ ] Always create branch for experiments
- [ ] Use descriptive commit messages
- [ ] Regular git status checks
EOF

cd ..
echo "🎒 Git Rescue Toolkit created in git-rescue-toolkit/"
```

### Workshop di Training

```bash
echo "=== WORKSHOP DI TRAINING PER IL TEAM ==="

cat > team-training-workshop.sh << 'EOF'
#!/bin/bash

# Git Rescue Training Workshop
# ============================

echo "🎓 Git Rescue Training Workshop"
echo "==============================="

# Sessione 1: Comprensione Detached HEAD
training_session_1() {
    echo ""
    echo "📚 SESSION 1: Understanding Detached HEAD"
    echo "=========================================="
    
    echo "What is detached HEAD?"
    echo "- HEAD points to specific commit, not branch"
    echo "- Read-only exploration mode by default"
    echo "- Commits possible but need special handling"
    
    echo ""
    echo "🧪 HANDS-ON: Safe detached HEAD exploration"
    
    # Demo sicuro
    echo "1. Create checkpoint:"
    echo "   git tag training-checkpoint"
    
    echo ""
    echo "2. Navigate to old commit:"
    echo "   git checkout HEAD~3"
    
    echo ""
    echo "3. Explore safely:"
    echo "   git log --oneline -5"
    echo "   ls -la  # See old state"
    
    echo ""
    echo "4. Return safely:"
    echo "   git switch -"
    
    echo ""
    echo "✅ Key takeaway: Detached HEAD is safe for exploration!"
}

# Sessione 2: Recovery Techniques
training_session_2() {
    echo ""
    echo "📚 SESSION 2: Recovery Techniques"
    echo "================================="
    
    echo "Core recovery tools:"
    echo "- git reflog: Your safety net"
    echo "- git branch: Create rescue branches"
    echo "- git cherry-pick: Move commits"
    echo "- git stash: Temporary save"
    
    echo ""
    echo "🧪 HANDS-ON: Recovery simulation"
    echo ""
    echo "Simulate problem → Apply recovery → Verify success"
}

# Sessione 3: Prevention Strategies
training_session_3() {
    echo ""
    echo "📚 SESSION 3: Prevention Strategies"
    echo "==================================="
    
    echo "Best practices:"
    echo "1. Always know where you are: git status"
    echo "2. Create checkpoints: git tag, git branch"
    echo "3. Stash before navigation: git stash"
    echo "4. Use descriptive commits"
    echo "5. Regular git reflog reviews"
    
    echo ""
    echo "🛡️ HANDS-ON: Setup prevention workflow"
}

# Main training flow
echo "Workshop modules:"
echo "1. Understanding Detached HEAD"
echo "2. Recovery Techniques"  
echo "3. Prevention Strategies"
echo ""

read -p "Start workshop? (y/n): " start
if [ "$start" = "y" ]; then
    training_session_1
    read -p "Continue to session 2? (y/n): " cont1
    if [ "$cont1" = "y" ]; then
        training_session_2
        read -p "Continue to session 3? (y/n): " cont2
        if [ "$cont2" = "y" ]; then
            training_session_3
            echo ""
            echo "🎉 Workshop completed! Team is now Git Rescue ready!"
        fi
    fi
fi
EOF

chmod +x team-training-workshop.sh

echo "📚 Team training workshop ready!"
echo "   Run: ./team-training-workshop.sh"
```

---

## 📊 Rescue Success Metrics

### Final Assessment Dashboard

```bash
echo "=== RESCUE SUCCESS METRICS ==="

cat << 'EOF'
# 🏆 Git Rescue Mission Report

## 📊 Mission Statistics
- **Missions Completed**: 3/3 ✅
- **Success Rate**: 100%
- **Data Loss**: 0%
- **Recovery Time**: ~50 minutes
- **Techniques Mastered**: 15+

## 🎯 Skills Acquired

### Core Recovery Skills
- ✅ Detached HEAD navigation and recovery
- ✅ Orphaned commit identification and rescue
- ✅ Chaos resolution and timeline reconstruction  
- ✅ Strategic branch creation for recovery
- ✅ Cherry-pick and merge strategies

### Advanced Techniques
- ✅ Reflog forensic analysis
- ✅ Strategic commit consolidation
- ✅ Conflict resolution during recovery
- ✅ Emergency response automation
- ✅ Team training and prevention

## 🛠️ Tools Mastered

### Emergency Response Commands
```bash
git reflog                    # Timeline investigation
git fsck --unreachable       # Orphaned commit detection
git branch <name> <commit>   # Rescue branch creation
git cherry-pick <commit>     # Selective recovery
git switch -                 # Quick return to safety
git stash push -m "msg"     # Emergency backup
```

### Recovery Patterns
1. **Assess** → Check git status and reflog
2. **Secure** → Create rescue branches/commits
3. **Recover** → Use cherry-pick or merge
4. **Verify** → Confirm all data recovered
5. **Clean** → Remove temporary branches

## 🎓 Certification Level
**Git Rescue Specialist** 🏅

Ready to handle:
- Complex detached HEAD scenarios
- Multi-commit recovery operations  
- Timeline chaos resolution
- Team emergency response
- Prevention strategy implementation

## 🚀 Next Level Objectives
- [ ] Automated recovery scripting
- [ ] CI/CD integration for safety
- [ ] Advanced reflog analysis
- [ ] Cross-repository rescue operations
- [ ] Disaster recovery planning

EOF

# Success verification
echo ""
echo "🔍 FINAL VERIFICATION:"

echo "Repository state:"
git log --oneline -5

echo ""
echo "All emergency branches cleaned:"
git branch | grep -c recovery || echo "0 recovery branches remaining ✅"

echo ""
echo "Reflog shows successful operations:"
git reflog --oneline -10

echo ""
echo "🎉 ALL RESCUE MISSIONS COMPLETED SUCCESSFULLY!"
echo "   💪 You are now a Git Rescue Specialist!"
```

---

## 💡 Key Takeaways

### Essential Recovery Principles

1. **Don't Panic**: Git rarely loses data permanently
2. **Assess First**: Always understand current situation
3. **Create Safety**: Use branches and tags for recovery
4. **Incremental Recovery**: One step at a time
5. **Verify Success**: Confirm all data is recovered

### Master Commands for Rescue

```bash
# Investigation
git reflog --oneline -20     # See all recent movements
git status                   # Current state analysis
git fsck --unreachable      # Find orphaned commits

# Recovery
git branch rescue-name <hash>  # Create rescue branch
git cherry-pick <commit>       # Selective recovery
git switch -                   # Quick escape to safety

# Prevention  
git stash push -m "backup"     # Emergency save
git tag checkpoint-name        # Create recovery point
```

### Recovery Workflow Template

1. **Assess** → `git status` + `git reflog`
2. **Secure** → Create rescue branch/commit
3. **Navigate** → Return to safe branch
4. **Recover** → Cherry-pick or merge work
5. **Verify** → Confirm no data loss
6. **Clean** → Remove temporary artifacts

---

## 🔄 Navigazione

- [⬅️ 03 - Testing Versioni](./03-testing-versioni.md)
- [🏠 Modulo 09](../README.md)
- [➡️ Esercizi di Consolidamento](../esercizi/01-viaggio-nel-tempo.md)
- [📑 Indice Corso](../../README.md)

---

**Prossima sezione**: [Esercizi di Consolidamento](../esercizi/01-viaggio-nel-tempo.md) - Metti in pratica tutte le competenze di navigazione acquisite
