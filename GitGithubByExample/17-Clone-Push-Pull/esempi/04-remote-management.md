# Esempio 04: Remote Management Avanzato

## 📋 Scenario
Lavori su progetti complessi con multiple origini remote: repository aziendali, fork personali, mirror di backup e upstream open source. Devi gestire configurazioni remote sofisticate per workflow enterprise e collaborazione open source.

## 🎯 Obiettivi
- Gestire multiple remote in scenari complessi
- Configurare workflow enterprise con sicurezza
- Implementare strategie di backup e mirroring
- Ottimizzare performance con large repositories

## 🚀 Implementazione Pratica

### Fase 1: Setup Repository Multi-Remote

```bash
# 1. Scenario: Contributo a progetto open source
mkdir opensource-contribution
cd opensource-contribution

# Clone del fork personale
git clone https://github.com/tuo-username/awesome-framework.git
cd awesome-framework

# Verifica remote esistenti
git remote -v
# output: origin https://github.com/tuo-username/awesome-framework.git

# 2. Aggiungere upstream originale
git remote add upstream https://github.com/original-maintainer/awesome-framework.git

# 3. Aggiungere mirror di backup aziendale
git remote add company-mirror git@gitlab.company.com:mirrors/awesome-framework.git

# 4. Aggiungere remote per testing
git remote add testing https://github.com/tuo-username/awesome-framework-testing.git

# Verifica configurazione finale
git remote -v
```

**Output atteso:**
```
company-mirror  git@gitlab.company.com:mirrors/awesome-framework.git (fetch)
company-mirror  git@gitlab.company.com:mirrors/awesome-framework.git (push)
origin          https://github.com/tuo-username/awesome-framework.git (fetch)
origin          https://github.com/tuo-username/awesome-framework.git (push)
testing         https://github.com/tuo-username/awesome-framework-testing.git (fetch)
testing         https://github.com/tuo-username/awesome-framework-testing.git (push)
upstream        https://github.com/original-maintainer/awesome-framework.git (fetch)
upstream        https://github.com/original-maintainer/awesome-framework.git (push)
```

### Fase 2: Workflow Enterprise Complesso

```bash
# Scenario aziendale: Development -> Staging -> Production

# 1. Setup repository aziendale
git remote add development git@git.company.com:project/app-development.git
git remote add staging git@git.company.com:project/app-staging.git
git remote add production git@git.company.com:project/app-production.git

# 2. Configurazione specifica per remote
git config remote.production.pushurl git@secure-git.company.com:project/app-production.git
git config remote.production.fetch "+refs/heads/*:refs/remotes/production/*"

# 3. Setup push specifici per ambiente
git config remote.development.push "+refs/heads/feature/*:refs/heads/feature/*"
git config remote.staging.push "+refs/heads/release/*:refs/heads/release/*"
git config remote.production.push "+refs/heads/main:refs/heads/main"

# 4. Fetch da tutti i remote
git fetch --all

# 5. Vedere tutte le branch remote
git branch -r
```

### Fase 3: Gestione Branch Multi-Remote

```bash
# 1. Sincronizzazione con upstream (open source)
git fetch upstream
git checkout main
git merge upstream/main
git push origin main

# 2. Creazione feature con tracking specifico
git checkout -b feature/oauth-integration
git push -u origin feature/oauth-integration

# 3. Cherry-pick da remote diversi
git fetch upstream
git cherry-pick upstream/main~3  # Prendi commit specifico da upstream

# 4. Push su multiple destinazioni
git push origin feature/oauth-integration
git push company-mirror feature/oauth-integration

# 5. Branch tracking per remote specifici
git branch --set-upstream-to=upstream/main main
git branch --set-upstream-to=origin/develop develop
```

### Fase 4: Scripts Automazione Remote

```bash
# Script: sync-all-remotes.sh
cat > sync-all-remotes.sh << 'EOF'
#!/bin/bash

echo "🔄 SINCRONIZZAZIONE TUTTI I REMOTE"
echo "==================================="

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Funzione per log colorato
log_info() { echo -e "${GREEN}ℹ️  $1${NC}"; }
log_warn() { echo -e "${YELLOW}⚠️  $1${NC}"; }
log_error() { echo -e "${RED}❌ $1${NC}"; }

# Verifica se siamo in un repository git
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    log_error "Non siamo in un repository Git!"
    exit 1
fi

# Ottieni lista remote
remotes=($(git remote))

if [ ${#remotes[@]} -eq 0 ]; then
    log_warn "Nessun remote configurato"
    exit 0
fi

log_info "Remote trovati: ${remotes[*]}"

# Fetch da tutti i remote
for remote in "${remotes[@]}"; do
    log_info "Fetching da $remote..."
    
    if git fetch "$remote" 2>/dev/null; then
        log_info "✅ $remote sincronizzato"
    else
        log_error "❌ Errore sincronizzazione $remote"
    fi
done

# Mostra stato branch principali
echo -e "\n📊 STATO BRANCH PRINCIPALI"
echo "=========================="

main_branches=("main" "master" "develop")

for branch in "${main_branches[@]}"; do
    if git show-ref --verify --quiet "refs/heads/$branch"; then
        echo -e "\n🌿 Branch: $branch"
        
        for remote in "${remotes[@]}"; do
            remote_branch="$remote/$branch"
            if git show-ref --verify --quiet "refs/remotes/$remote_branch"; then
                ahead=$(git rev-list --count "$remote_branch..HEAD" 2>/dev/null || echo "0")
                behind=$(git rev-list --count "HEAD..$remote_branch" 2>/dev/null || echo "0")
                
                if [ "$ahead" = "0" ] && [ "$behind" = "0" ]; then
                    echo "  ✅ $remote: sincronizzato"
                else
                    echo "  📊 $remote: $ahead avanti, $behind indietro"
                fi
            fi
        done
    fi
done

echo -e "\n✅ Sincronizzazione completata!"
EOF

chmod +x sync-all-remotes.sh

# Script: backup-to-all.sh
cat > backup-to-all.sh << 'EOF'
#!/bin/bash

echo "💾 BACKUP SU TUTTI I REMOTE"
echo "============================"

current_branch=$(git branch --show-current)
remotes=($(git remote))

echo "📍 Branch corrente: $current_branch"
echo "🎯 Remote disponibili: ${remotes[*]}"

# Verifica se ci sono modifiche non committate
if ! git diff-index --quiet HEAD --; then
    echo "⚠️  Modifiche non committate rilevate!"
    echo "Commit automatico? (y/N)"
    read -r response
    
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        git add .
        git commit -m "auto-backup: $(date +'%Y-%m-%d %H:%M:%S')"
    else
        echo "❌ Backup annullato"
        exit 1
    fi
fi

# Push su tutti i remote
for remote in "${remotes[@]}"; do
    echo "📤 Push su $remote..."
    
    if git push "$remote" "$current_branch" 2>/dev/null; then
        echo "✅ Backup su $remote completato"
    else
        echo "❌ Errore backup su $remote"
        
        # Tentativo di creare branch remoto se non esiste
        if git push -u "$remote" "$current_branch" 2>/dev/null; then
            echo "✅ Branch creato e backup completato su $remote"
        else
            echo "❌ Impossibile fare backup su $remote"
        fi
    fi
done

echo "✅ Processo backup completato!"
EOF

chmod +x backup-to-all.sh
```

## 🔧 Configurazioni Remote Avanzate

### Setup SSH Multi-Account

```bash
# 1. Configurazione SSH per account multipli
cat >> ~/.ssh/config << 'EOF'

# Account personale GitHub
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_rsa_personal

# Account aziendale GitHub
Host github-work
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_rsa_work

# GitLab aziendale
Host gitlab.company.com
    HostName gitlab.company.com
    User git
    IdentityFile ~/.ssh/id_rsa_company
    Port 2222

# Azure DevOps
Host ssh.dev.azure.com
    HostName ssh.dev.azure.com
    User git
    IdentityFile ~/.ssh/id_rsa_azure
EOF

# 2. Setup remote con SSH specifici
git remote set-url origin git@github.com:personal/repo.git
git remote set-url company git@github-work:company/repo.git
git remote set-url gitlab git@gitlab.company.com:team/repo.git
```

### Configurazioni Remote Sicure

```bash
# 1. Configurazione push restrittivo
git config remote.production.pushurl "git@secure-git.company.com:project/app.git"
git config remote.production.push "refs/heads/main:refs/heads/main"

# 2. Configurazione fetch selettivo
git config remote.upstream.fetch "+refs/heads/main:refs/remotes/upstream/main"
git config remote.upstream.fetch "+refs/heads/develop:refs/remotes/upstream/develop"

# 3. Configurazione con proxy aziendale
git config remote.company.proxy "http://proxy.company.com:8080"

# 4. Remote con autenticazione avanzata
git config credential.https://git.company.com.username "mario.rossi"
git config credential.https://git.company.com.helper "cache --timeout=7200"
```

### Large Repository Optimization

```bash
# 1. Clone parziale per repository grandi
git clone --filter=blob:none --origin=upstream \
  https://github.com/large-project/massive-repo.git

cd massive-repo

# 2. Remote con limitazioni specifiche
git remote add origin https://github.com/tuo-fork/massive-repo.git
git config remote.origin.partialclonefilter "blob:none"

# 3. Fetch incrementale
git config remote.upstream.fetch "+refs/heads/main:refs/remotes/upstream/main"
git config fetch.prune true
git config fetch.pruneTags true

# 4. Configurazione maintenance automatica
git config maintenance.auto true
git config maintenance.strategy incremental
```

## 📊 Monitoring e Analytics Remote

### Script Diagnostico Remote

```bash
# diagnose-remotes.sh
cat > diagnose-remotes.sh << 'EOF'
#!/bin/bash

echo "🔍 DIAGNOSTICA REMOTE AVANZATA"
echo "==============================="

# Informazioni base
echo "📍 Repository: $(basename "$(git rev-parse --show-toplevel)")"
echo "📂 Directory: $(pwd)"
echo "🌿 Branch: $(git branch --show-current)"

echo -e "\n📡 CONFIGURAZIONE REMOTE"
echo "========================"

remotes=($(git remote))
for remote in "${remotes[@]}"; do
    echo -e "\n🔗 Remote: $remote"
    echo "   URL: $(git remote get-url "$remote")"
    echo "   Push URL: $(git remote get-url --push "$remote" 2>/dev/null || echo "Non configurato")"
    
    # Test connessione
    if git ls-remote "$remote" HEAD &>/dev/null; then
        echo "   Status: ✅ Connesso"
    else
        echo "   Status: ❌ Non raggiungibile"
    fi
    
    # Branch remoti
    branch_count=$(git branch -r | grep "$remote/" | wc -l)
    echo "   Branch remoti: $branch_count"
    
    # Ultimo fetch
    if [ -f ".git/refs/remotes/$remote/HEAD" ]; then
        last_fetch=$(stat -c %Y ".git/refs/remotes/$remote/HEAD" 2>/dev/null || echo "0")
        if [ "$last_fetch" != "0" ]; then
            echo "   Ultimo fetch: $(date -d @"$last_fetch" '+%Y-%m-%d %H:%M:%S')"
        fi
    fi
done

echo -e "\n📊 STATISTICHE SYNC"
echo "==================="

# Branch tracking
echo "🌿 Branch tracking:"
git for-each-ref --format='%(refname:short) -> %(upstream:short)' refs/heads | \
    while read -r line; do
        if [[ "$line" == *" -> "* ]]; then
            echo "   $line"
        fi
    done

# Commit status
current_branch=$(git branch --show-current)
upstream_branch=$(git rev-parse --abbrev-ref @{u} 2>/dev/null)

if [ -n "$upstream_branch" ]; then
    ahead=$(git rev-list --count HEAD.."$upstream_branch" 2>/dev/null || echo "0")
    behind=$(git rev-list --count "$upstream_branch"..HEAD 2>/dev/null || echo "0")
    echo "📈 Status vs upstream: $ahead commit indietro, $behind commit avanti"
fi

echo -e "\n🔧 CONFIGURAZIONI SPECIALI"
echo "=========================="

# Configurazioni remote specifiche
for remote in "${remotes[@]}"; do
    echo "🔗 $remote:"
    
    # Push URL diverso
    push_url=$(git config "remote.$remote.pushurl" 2>/dev/null)
    if [ -n "$push_url" ]; then
        echo "   Push URL custom: $push_url"
    fi
    
    # Fetch refspec custom
    fetch_spec=$(git config "remote.$remote.fetch" 2>/dev/null)
    if [ -n "$fetch_spec" ]; then
        echo "   Fetch spec: $fetch_spec"
    fi
    
    # Push refspec custom
    push_spec=$(git config "remote.$remote.push" 2>/dev/null)
    if [ -n "$push_spec" ]; then
        echo "   Push spec: $push_spec"
    fi
done

echo -e "\n💾 DIMENSIONI E PERFORMANCE"
echo "============================"

# Dimensione .git
git_size=$(du -sh .git 2>/dev/null | cut -f1)
echo "📁 Dimensione .git: $git_size"

# Numero oggetti
object_count=$(git count-objects -v | grep "count" | cut -d' ' -f2)
echo "🔢 Oggetti Git: $object_count"

# Packed objects
packed_objects=$(git count-objects -v | grep "in-pack" | cut -d' ' -f2)
echo "📦 Oggetti packed: $packed_objects"

echo -e "\n✅ Diagnostica completata!"
EOF

chmod +x diagnose-remotes.sh
```

### Health Check Automatico

```bash
# health-check-remotes.sh
cat > health-check-remotes.sh << 'EOF'
#!/bin/bash

echo "🏥 HEALTH CHECK REMOTE"
echo "======================"

exit_code=0

# Test connettività
echo "🔌 Test connettività remote..."
remotes=($(git remote))

for remote in "${remotes[@]}"; do
    if timeout 10 git ls-remote "$remote" HEAD &>/dev/null; then
        echo "✅ $remote: OK"
    else
        echo "❌ $remote: FAIL"
        exit_code=1
    fi
done

# Verifica branch tracking
echo -e "\n🌿 Verifica branch tracking..."
current_branch=$(git branch --show-current)
upstream=$(git rev-parse --abbrev-ref @{u} 2>/dev/null)

if [ -z "$upstream" ]; then
    echo "⚠️  Branch $current_branch non ha upstream configurato"
    exit_code=1
else
    echo "✅ Branch tracking: $current_branch -> $upstream"
fi

# Verifica stato sync
echo -e "\n🔄 Verifica stato sincronizzazione..."
if [ -n "$upstream" ]; then
    # Fetch silent per aggiornare ref
    git fetch "$(echo "$upstream" | cut -d'/' -f1)" 2>/dev/null
    
    ahead=$(git rev-list --count HEAD.."$upstream" 2>/dev/null || echo "0")
    behind=$(git rev-list --count "$upstream"..HEAD 2>/dev/null || echo "0")
    
    if [ "$ahead" = "0" ] && [ "$behind" = "0" ]; then
        echo "✅ Repository sincronizzato"
    elif [ "$ahead" -gt "0" ] && [ "$behind" = "0" ]; then
        echo "⚠️  $ahead commit da pullare"
    elif [ "$ahead" = "0" ] && [ "$behind" -gt "0" ]; then
        echo "⚠️  $behind commit da pushare"
    else
        echo "⚠️  $ahead da pullare, $behind da pushare (divergenza)"
        exit_code=1
    fi
fi

# Verifica working directory
echo -e "\n📁 Verifica working directory..."
if git diff-index --quiet HEAD --; then
    echo "✅ Working directory pulito"
else
    echo "⚠️  Modifiche non committate presenti"
fi

# Report finale
echo -e "\n📋 REPORT FINALE"
echo "================"

if [ $exit_code -eq 0 ]; then
    echo "✅ Repository in stato ottimale"
else
    echo "⚠️  Attenzione richiesta - controllare i warning sopra"
fi

exit $exit_code
EOF

chmod +x health-check-remotes.sh
```

## 🔄 Workflow Automation

### Git Hooks per Remote Management

```bash
# Pre-push hook per validazione multi-remote
cat > .git/hooks/pre-push << 'EOF'
#!/bin/bash

# Leggi parametri push
remote="$1"
url="$2"

echo "🔍 Pre-push validation per $remote"

# Validazione specifica per remote production
if [ "$remote" = "production" ]; then
    echo "⚠️  Push su PRODUCTION rilevato!"
    
    # Verifica branch
    current_branch=$(git branch --show-current)
    if [ "$current_branch" != "main" ]; then
        echo "❌ Push su production consentito solo da branch main"
        exit 1
    fi
    
    # Verifica test
    if ! npm test >/dev/null 2>&1; then
        echo "❌ Test falliti! Push su production abortito"
        exit 1
    fi
    
    # Conferma manuale
    echo "Confermi push su PRODUCTION? (yes/NO)"
    read -r confirm
    if [ "$confirm" != "yes" ]; then
        echo "❌ Push annullato dall'utente"
        exit 1
    fi
fi

# Validazione dimensione push
commits_count=$(git rev-list --count @{u}..HEAD 2>/dev/null || echo "1")
if [ "$commits_count" -gt 10 ]; then
    echo "⚠️  Push di $commits_count commit. Procedere? (y/N)"
    read -r confirm
    if [[ ! "$confirm" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        exit 1
    fi
fi

echo "✅ Pre-push validation passed"
EOF

chmod +x .git/hooks/pre-push

# Post-merge hook per sync automatico
cat > .git/hooks/post-merge << 'EOF'
#!/bin/bash

echo "🔄 Post-merge: sync automatico backup remotes..."

# Lista remote di backup
backup_remotes=("company-mirror" "backup")

current_branch=$(git branch --show-current)

for remote in "${backup_remotes[@]}"; do
    if git remote | grep -q "^$remote$"; then
        echo "📤 Sync $remote..."
        git push "$remote" "$current_branch" 2>/dev/null && \
            echo "✅ $remote aggiornato" || \
            echo "⚠️  Errore sync $remote"
    fi
done
EOF

chmod +x .git/hooks/post-merge
```

## 💡 Best Practices Remote Management

### 1. **Naming Convention Standardizzata**

```bash
# Convention aziendale consigliata:
origin          # Tuo fork/repository principale
upstream        # Repository originale (open source)
production      # Ambiente produzione
staging         # Ambiente staging  
development     # Ambiente sviluppo
backup          # Mirror di backup
company         # Repository aziendale
testing         # Ambiente test
```

### 2. **Sicurezza e Access Control**

```bash
# Remote con accesso limitato
git config remote.production.pushurl "git@secure.company.com:project.git"
git config remote.production.push "refs/heads/main:refs/heads/main"

# Verifica firme GPG su remote critici
git config remote.production.receivepack "git-receive-pack --verify-signatures"
```

### 3. **Performance Optimization**

```bash
# Configurazioni per repository grandi
git config remote.origin.promisor true
git config remote.origin.partialclonefilter "blob:limit=1m"

# Parallel fetch per multiple remote
git config fetch.parallel 4
```

## 🔄 Prossimi Passi

Dopo aver masterizzato remote management:

1. **[../18-Collaborazione-Base](../18-Collaborazione-Base/README.md)** - Workflow collaborativi
2. **[../19-Fork-e-Pull-Request](../19-Fork-e-Pull-Request/README.md)** - Contribuzioni open source
3. **[../21-GitHub-Actions-Intro](../21-GitHub-Actions-Intro/README.md)** - Automazione CI/CD

## 📚 Risorse Aggiuntive

- [Git Remote Documentation](https://git-scm.com/docs/git-remote)
- [Multi-Remote Workflows](https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes)
- [Enterprise Git Workflows](https://nvie.com/posts/a-successful-git-branching-model/)
