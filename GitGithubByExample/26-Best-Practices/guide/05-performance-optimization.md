# Performance Optimization: Ottimizzare Repository Git

## Obiettivi
- Ottimizzare performance di repository Git di grandi dimensioni
- Implementare strategie per gestire file binari e asset
- Configurare Git per progetti complessi
- Monitorare e migliorare performance del workflow

## Introduzione

L'ottimizzazione delle performance Git è cruciale per:
- **Velocità di operazioni**: Clone, fetch, push più rapidi
- **Efficienza storage**: Riduzione spazio utilizzato
- **Produttività team**: Workflow più fluidi
- **Scalabilità**: Gestione di repository enterprise

## 1. Repository Size Optimization

### Analisi Dimensioni Repository

```bash
#!/bin/bash
# scripts/analyze-repo-size.sh

echo "📊 ANALISI DIMENSIONI REPOSITORY"
echo "================================"
echo

# Dimensione totale repository
echo "📦 Dimensione totale:"
du -sh .git
echo

# Dimensione oggetti Git
echo "🗄️  Dimensione oggetti:"
git count-objects -vH
echo

# File più grandi nella storia
echo "📈 File più grandi nella storia del repository:"
git rev-list --objects --all | \
    git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
    sed -n 's/^blob //p' | \
    sort --numeric-sort --key=2 --reverse | \
    head -20 | \
    while read objectname size path; do
        printf "%s\t%s\t%s\n" "$(numfmt --to=iec $size)" "$objectname" "$path"
    done
echo

# Estensioni file più pesanti
echo "📊 Estensioni file più pesanti:"
git rev-list --objects --all | \
    git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
    sed -n 's/^blob //p' | \
    awk '{
        if ($3 != "") {
            extension = $3
            gsub(/.*\./, "", extension)
            size[extension] += $2
            count[extension]++
        }
    }
    END {
        for (ext in size) {
            printf "%-10s %10s %8d files\n", ext, size[ext], count[ext]
        }
    }' | sort -k2 -nr | head -10
echo

# Directory più pesanti
echo "📁 Directory più pesanti:"
git ls-tree -r -t -l --full-name HEAD | \
    awk '{
        dir = $5
        gsub(/\/[^\/]*$/, "", dir)
        if (dir == $5) dir = "."
        size[dir] += $4
    }
    END {
        for (d in size) printf "%-40s %10s\n", d, size[d]
    }' | sort -k2 -nr | head -10
```

### Git Configuration per Performance

```bash
# .gitconfig ottimizzata per performance
[core]
    # Abilita file system monitor per repository grandi
    fsmonitor = true
    
    # Ottimizza operazioni index
    preloadindex = true
    
    # Usa compression level ottimale
    compression = 9
    
    # Ottimizza pack files
    packedGitLimit = 512m
    packedGitWindowSize = 512m
    
    # Delta compression ottimizzata
    bigFileThreshold = 512m

[gc]
    # Garbage collection automatica
    auto = 6700
    autopacklimit = 50
    
    # Aggressive garbage collection
    aggressive = true

[pack]
    # Ottimizza pack files
    deltaCacheSize = 2047m
    packSizeLimit = 2g
    windowMemory = 2g
    
    # Threads per packing
    threads = 0  # Auto-detect CPU cores

[diff]
    # Algoritmo diff ottimizzato
    algorithm = histogram
    
    # Rename detection
    renames = copies

[merge]
    # Merge strategy ottimizzata
    tool = vimdiff
    renormalize = true

[repack]
    # Repack ottimizzato
    usedeltabaseoffset = true

[feature]
    # Abilita feature sperimentali per performance
    manyFiles = true

[index]
    # Versione index ottimizzata
    version = 4
    
    # Sparse checkout
    sparse = true

[status]
    # Status ottimizzato per repository grandi
    submodulesummary = false
    showUntrackedFiles = normal

[push]
    # Push ottimizzato
    default = simple
    followTags = true

[pull]
    # Pull ottimizzato
    rebase = true

# Configurazioni per protocolli di rete
[url "git@github.com:"]
    insteadOf = https://github.com/

[http]
    # Ottimizza transfer HTTP
    postBuffer = 524288000  # 500MB
    
    # Keepalive per ridurre overhead
    keepalive = true
    
    # Compressione
    compression = 9

[https]
    # SSL ottimizzato
    sslVersion = tlsv1.2

# Git LFS configuration
[lfs]
    # Concurrent transfers
    concurrenttransfers = 8
    
    # Batch size
    batch = true
    
    # Storage ottimizzato
    storage = .git/lfs/objects
```

### Repository Maintenance

```bash
#!/bin/bash
# scripts/maintain-repo.sh

echo "🔧 MANUTENZIONE REPOSITORY"
echo "========================="
echo

# Backup prima della manutenzione
echo "💾 Creazione backup..."
git bundle create backup-$(date +%Y%m%d).bundle --all
echo

# Verifica integrità repository
echo "🔍 Verifica integrità..."
git fsck --full --strict
if [ $? -ne 0 ]; then
    echo "❌ Problemi di integrità rilevati!"
    exit 1
fi
echo

# Pulizia oggetti orfani
echo "🧹 Pulizia oggetti orfani..."
git prune --verbose --expire=now
echo

# Ottimizzazione pack files
echo "📦 Ottimizzazione pack files..."
git repack -a -d --depth=250 --window=250
echo

# Garbage collection aggressiva
echo "🗑️  Garbage collection..."
git gc --aggressive --prune=now
echo

# Aggiornamento index
echo "📋 Aggiornamento index..."
git update-index --refresh
echo

# Statistiche finali
echo "✅ Manutenzione completata!"
echo "📊 Statistiche finali:"
git count-objects -vH
```

## 2. Git LFS per File Binari

### Setup Git LFS

```bash
# Installazione Git LFS
git lfs install

# Configurazione tracking automatico
git lfs track "*.png"
git lfs track "*.jpg"
git lfs track "*.jpeg"
git lfs track "*.gif"
git lfs track "*.bmp"
git lfs track "*.tiff"
git lfs track "*.pdf"
git lfs track "*.zip"
git lfs track "*.tar.gz"
git lfs track "*.mp4"
git lfs track "*.mov"
git lfs track "*.avi"
git lfs track "*.dmg"
git lfs track "*.exe"
git lfs track "*.msi"

# Commit .gitattributes
git add .gitattributes
git commit -m "chore: configure Git LFS tracking"
```

### .gitattributes Ottimizzato

```gitattributes
# Git LFS tracking
*.png filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.jpeg filter=lfs diff=lfs merge=lfs -text
*.gif filter=lfs diff=lfs merge=lfs -text
*.bmp filter=lfs diff=lfs merge=lfs -text
*.tiff filter=lfs diff=lfs merge=lfs -text
*.ico filter=lfs diff=lfs merge=lfs -text
*.svg filter=lfs diff=lfs merge=lfs -text

# Documents
*.pdf filter=lfs diff=lfs merge=lfs -text
*.doc filter=lfs diff=lfs merge=lfs -text
*.docx filter=lfs diff=lfs merge=lfs -text
*.ppt filter=lfs diff=lfs merge=lfs -text
*.pptx filter=lfs diff=lfs merge=lfs -text
*.xls filter=lfs diff=lfs merge=lfs -text
*.xlsx filter=lfs diff=lfs merge=lfs -text

# Archives
*.zip filter=lfs diff=lfs merge=lfs -text
*.rar filter=lfs diff=lfs merge=lfs -text
*.7z filter=lfs diff=lfs merge=lfs -text
*.tar.gz filter=lfs diff=lfs merge=lfs -text
*.tar.bz2 filter=lfs diff=lfs merge=lfs -text

# Audio/Video
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.mp4 filter=lfs diff=lfs merge=lfs -text
*.mov filter=lfs diff=lfs merge=lfs -text
*.avi filter=lfs diff=lfs merge=lfs -text
*.mkv filter=lfs diff=lfs merge=lfs -text

# Executables
*.exe filter=lfs diff=lfs merge=lfs -text
*.msi filter=lfs diff=lfs merge=lfs -text
*.dmg filter=lfs diff=lfs merge=lfs -text
*.pkg filter=lfs diff=lfs merge=lfs -text
*.deb filter=lfs diff=lfs merge=lfs -text
*.rpm filter=lfs diff=lfs merge=lfs -text

# Binary data files
*.db filter=lfs diff=lfs merge=lfs -text
*.sqlite filter=lfs diff=lfs merge=lfs -text
*.dat filter=lfs diff=lfs merge=lfs -text

# Text files optimization
*.txt text eol=lf
*.md text eol=lf
*.json text eol=lf
*.js text eol=lf
*.ts text eol=lf
*.jsx text eol=lf
*.tsx text eol=lf
*.css text eol=lf
*.scss text eol=lf
*.html text eol=lf
*.xml text eol=lf
*.yml text eol=lf
*.yaml text eol=lf

# Source code diff optimization
*.c text diff=c
*.cpp text diff=cpp
*.java text diff=java
*.py text diff=python
*.rb text diff=ruby
*.php text diff=php

# Configuration files
*.ini text
*.cfg text
*.conf text
*.config text

# Shell scripts
*.sh text eol=lf
*.bash text eol=lf
*.zsh text eol=lf
*.fish text eol=lf

# Windows scripts
*.bat text eol=crlf
*.cmd text eol=crlf
*.ps1 text eol=crlf
```

### Migrazione File Esistenti a LFS

```bash
#!/bin/bash
# scripts/migrate-to-lfs.sh

echo "🔄 MIGRAZIONE FILE A GIT LFS"
echo "============================="
echo

# Backup del repository
git bundle create backup-pre-lfs-$(date +%Y%m%d).bundle --all

# Lista file grandi da migrare
echo "📊 File grandi da migrare:"
git rev-list --objects --all | \
    git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
    sed -n 's/^blob //p' | \
    awk '$2 >= 1048576' | \
    sort --numeric-sort --key=2 --reverse | \
    head -20

echo
read -p "Continuare con la migrazione? (y/N): " confirm
if [ "$confirm" != "y" ] && [ "$confirm" != "Y" ]; then
    exit 0
fi

# Migrazione con git lfs migrate
echo "🚀 Inizio migrazione..."

# Migra file immagini
git lfs migrate import --include="*.png,*.jpg,*.jpeg,*.gif,*.bmp,*.tiff" --everything

# Migra file video
git lfs migrate import --include="*.mp4,*.mov,*.avi,*.mkv" --everything

# Migra archivi
git lfs migrate import --include="*.zip,*.rar,*.7z,*.tar.gz" --everything

# Migra documenti
git lfs migrate import --include="*.pdf,*.doc,*.docx,*.ppt,*.pptx" --everything

# Verifica migrazione
echo "✅ Migrazione completata!"
echo "📊 File LFS:"
git lfs ls-files

echo "📈 Statistiche post-migrazione:"
git count-objects -vH
```

## 3. Sparse Checkout per Repository Grandi

### Configurazione Sparse Checkout

```bash
# Abilita sparse checkout
git config core.sparseCheckout true

# Crea file sparse-checkout
cat > .git/info/sparse-checkout << EOF
# Include only specific directories
src/
docs/
tests/

# Include specific files
README.md
package.json
tsconfig.json

# Exclude specific subdirectories
!src/legacy/
!docs/archive/

# Include files with specific extensions in any directory
*.js
*.ts
*.json
*.md
EOF

# Applica sparse checkout
git read-tree -m -u HEAD
```

### Script Automatico per Sparse Checkout

```bash
#!/bin/bash
# scripts/setup-sparse-checkout.sh

echo "🌿 CONFIGURAZIONE SPARSE CHECKOUT"
echo "================================="
echo

# Funzione per mostrare directory disponibili
show_directories() {
    echo "📁 Directory disponibili:"
    git ls-tree -d --name-only HEAD | head -20
}

# Funzione per configurare sparse checkout
configure_sparse() {
    local mode=$1
    
    case $mode in
        "frontend")
            cat > .git/info/sparse-checkout << EOF
src/components/
src/pages/
src/styles/
src/utils/
public/
package.json
tsconfig.json
README.md
EOF
            ;;
        "backend")
            cat > .git/info/sparse-checkout << EOF
src/controllers/
src/models/
src/routes/
src/middleware/
src/services/
src/config/
tests/
package.json
README.md
EOF
            ;;
        "docs")
            cat > .git/info/sparse-checkout << EOF
docs/
README.md
CONTRIBUTING.md
CHANGELOG.md
LICENSE
EOF
            ;;
        "minimal")
            cat > .git/info/sparse-checkout << EOF
README.md
package.json
LICENSE
.gitignore
EOF
            ;;
        "custom")
            echo "📝 Inserisci i pattern per sparse checkout (uno per riga, termina con riga vuota):"
            > .git/info/sparse-checkout
            while IFS= read -r line; do
                [ -z "$line" ] && break
                echo "$line" >> .git/info/sparse-checkout
            done
            ;;
    esac
}

# Menu principale
show_directories
echo
echo "🎯 Seleziona configurazione sparse checkout:"
echo "1) Frontend (components, pages, styles)"
echo "2) Backend (controllers, models, routes)"
echo "3) Documentation only"
echo "4) Minimal (essential files only)"
echo "5) Custom configuration"
echo "6) Disable sparse checkout"
echo

read -p "Scelta (1-6): " choice

case $choice in
    1) configure_sparse "frontend" ;;
    2) configure_sparse "backend" ;;
    3) configure_sparse "docs" ;;
    4) configure_sparse "minimal" ;;
    5) configure_sparse "custom" ;;
    6) 
        git config core.sparseCheckout false
        rm -f .git/info/sparse-checkout
        echo "✅ Sparse checkout disabilitato"
        exit 0
        ;;
    *) echo "❌ Scelta non valida"; exit 1 ;;
esac

# Abilita sparse checkout
git config core.sparseCheckout true

# Applica configurazione
git read-tree -m -u HEAD

echo "✅ Sparse checkout configurato!"
echo "📋 Pattern attivi:"
cat .git/info/sparse-checkout
echo
echo "📊 File in working directory:"
find . -name .git -prune -o -type f -print | wc -l
```

## 4. Parallel Operations

### Git Configuration per Parallelismo

```bash
# Configurazione per operazioni parallele
git config --global pack.threads 0  # Auto-detect CPU cores
git config --global pack.windowMemory 2g
git config --global pack.deltaCacheSize 2047m

# Fetch parallelo
git config --global fetch.parallel 8

# Submodule operations parallel
git config --global submodule.fetchJobs 8

# HTTP transfer ottimizzato
git config --global http.postBuffer 524288000
git config --global http.maxRequestBuffer 100m
git config --global http.lowSpeedLimit 0
git config --global http.lowSpeedTime 999999
```

### Script per Clone Ottimizzato

```bash
#!/bin/bash
# scripts/fast-clone.sh

URL=$1
DIR=$2

if [ -z "$URL" ] || [ -z "$DIR" ]; then
    echo "Uso: $0 <repository-url> <directory>"
    exit 1
fi

echo "🚀 CLONE OTTIMIZZATO"
echo "===================="
echo "Repository: $URL"
echo "Directory: $DIR"
echo

# Clone con ottimizzazioni
git clone \
    --depth 1 \
    --single-branch \
    --recurse-submodules \
    --shallow-submodules \
    --jobs 8 \
    "$URL" "$DIR"

cd "$DIR"

# Configurazioni ottimizzate per il repository
git config core.preloadindex true
git config core.fsmonitor true
git config gc.auto 256
git config pack.threads 0

# Se necessario, fetch completa la storia
read -p "Scaricare la storia completa? (y/N): " fetch_all
if [ "$fetch_all" = "y" ] || [ "$fetch_all" = "Y" ]; then
    echo "📚 Download storia completa..."
    git fetch --unshallow
    git fetch --all
fi

echo "✅ Clone completato!"
```

## 5. Monitoring e Profiling

### Performance Monitoring

```bash
#!/bin/bash
# scripts/git-performance-monitor.sh

echo "📈 GIT PERFORMANCE MONITOR"
echo "=========================="
echo

# Funzione per misurare tempo
time_command() {
    local cmd="$1"
    local desc="$2"
    
    echo "⏱️  $desc..."
    time_start=$(date +%s.%N)
    eval "$cmd" > /dev/null 2>&1
    time_end=$(date +%s.%N)
    duration=$(echo "$time_end - $time_start" | bc)
    printf "   Tempo: %.2f secondi\n" "$duration"
}

# Test operazioni comuni
echo "🧪 Test performance operazioni Git:"
echo

time_command "git status" "Status repository"
time_command "git log --oneline -100" "Log ultimi 100 commit"
time_command "git diff HEAD~1" "Diff ultimo commit"
time_command "git branch -a" "Lista branch"
time_command "git ls-files | wc -l" "Conteggio file tracciati"

echo
echo "📊 Statistiche repository:"
echo "Files tracked: $(git ls-files | wc -l)"
echo "Total commits: $(git rev-list --count HEAD)"
echo "Repository size: $(du -sh .git | cut -f1)"
echo "Objects count: $(git count-objects | grep objects | cut -d' ' -f1)"

echo
echo "🔍 Analisi performance:"

# Check repository health
objects_count=$(git count-objects | grep objects | cut -d' ' -f1)
if [ "$objects_count" -gt 10000 ]; then
    echo "⚠️  Alto numero di oggetti loose ($objects_count) - considera 'git gc'"
fi

# Check large files
large_files=$(git ls-files | xargs ls -la 2>/dev/null | awk '$5 > 1048576' | wc -l)
if [ "$large_files" -gt 0 ]; then
    echo "⚠️  $large_files file grandi rilevati - considera Git LFS"
fi

# Check repository size
repo_size_mb=$(du -sm .git | cut -f1)
if [ "$repo_size_mb" -gt 100 ]; then
    echo "⚠️  Repository grande (${repo_size_mb}MB) - ottimizzazioni disponibili"
fi

echo
echo "💡 Raccomandazioni:"
echo "   - Esegui 'git gc' periodicamente"
echo "   - Usa Git LFS per file binari grandi"
echo "   - Considera sparse checkout per repository grandi"
echo "   - Configura fsmonitor per repository con molti file"
```

### Git Command Profiling

```bash
#!/bin/bash
# scripts/profile-git-commands.sh

echo "🔬 GIT COMMANDS PROFILING"
echo "========================="
echo

# Abilita trace per Git
export GIT_TRACE=1
export GIT_TRACE_PERFORMANCE=1
export GIT_TRACE_SETUP=1

# Funzione per profilare comando
profile_command() {
    local cmd="$1"
    local desc="$2"
    
    echo "📊 Profiling: $desc"
    echo "Command: $cmd"
    echo "----------------------------------------"
    
    # Esegui comando con profiling
    time git $cmd
    
    echo "----------------------------------------"
    echo
}

# Profile comandi comuni
profile_command "status" "Git Status"
profile_command "log --oneline -10" "Git Log (10 entries)"
profile_command "diff HEAD~1" "Git Diff"
profile_command "ls-files" "Git Ls-Files"

# Disabilita trace
unset GIT_TRACE
unset GIT_TRACE_PERFORMANCE
unset GIT_TRACE_SETUP

echo "✅ Profiling completato!"
```

### Repository Health Check

```bash
#!/bin/bash
# scripts/repo-health-check.sh

echo "🏥 REPOSITORY HEALTH CHECK"
echo "=========================="
echo

health_score=100
warnings=0
errors=0

# Check 1: Repository integrity
echo "🔍 Controllo integrità repository..."
if ! git fsck --quiet; then
    echo "❌ Problemi di integrità rilevati"
    errors=$((errors + 1))
    health_score=$((health_score - 20))
else
    echo "✅ Integrità repository OK"
fi

# Check 2: Repository size
repo_size_mb=$(du -sm .git | cut -f1)
echo "📦 Dimensione repository: ${repo_size_mb}MB"
if [ "$repo_size_mb" -gt 500 ]; then
    echo "⚠️  Repository molto grande - considera ottimizzazioni"
    warnings=$((warnings + 1))
    health_score=$((health_score - 10))
elif [ "$repo_size_mb" -gt 100 ]; then
    echo "⚠️  Repository grande - monitoraggio raccomandato"
    warnings=$((warnings + 1))
    health_score=$((health_score - 5))
fi

# Check 3: Loose objects
loose_objects=$(git count-objects | grep objects | cut -d' ' -f1)
echo "🗂️  Oggetti loose: $loose_objects"
if [ "$loose_objects" -gt 5000 ]; then
    echo "⚠️  Molti oggetti loose - esegui 'git gc'"
    warnings=$((warnings + 1))
    health_score=$((health_score - 10))
fi

# Check 4: Large files
echo "📊 Controllo file grandi..."
large_files=$(git ls-files | xargs ls -la 2>/dev/null | awk '$5 > 10485760' | wc -l)
if [ "$large_files" -gt 0 ]; then
    echo "⚠️  $large_files file > 10MB trovati - considera Git LFS"
    warnings=$((warnings + 1))
    health_score=$((health_score - 5))
fi

# Check 5: Stale branches
echo "🌿 Controllo branch stagnanti..."
old_branches=$(git for-each-ref --format='%(refname:short) %(committerdate)' refs/heads | awk '$2 < "'$(date -d '3 months ago' '+%Y-%m-%d')'"' | wc -l)
if [ "$old_branches" -gt 0 ]; then
    echo "⚠️  $old_branches branch non aggiornati da 3+ mesi"
    warnings=$((warnings + 1))
    health_score=$((health_score - 5))
fi

# Check 6: Git LFS usage
if command -v git-lfs >/dev/null 2>&1; then
    lfs_files=$(git lfs ls-files 2>/dev/null | wc -l)
    echo "📎 File Git LFS: $lfs_files"
else
    echo "⚠️  Git LFS non installato - raccomandato per file binari"
    warnings=$((warnings + 1))
    health_score=$((health_score - 5))
fi

# Check 7: Configuration
echo "⚙️  Controllo configurazione..."
if ! git config --get user.name >/dev/null || ! git config --get user.email >/dev/null; then
    echo "⚠️  Configurazione utente incompleta"
    warnings=$((warnings + 1))
    health_score=$((health_score - 5))
fi

# Summary
echo
echo "📋 RIASSUNTO HEALTH CHECK"
echo "========================="
echo "Health Score: $health_score/100"
echo "Errori: $errors"
echo "Avvertimenti: $warnings"
echo

if [ "$health_score" -ge 90 ]; then
    echo "🟢 Repository in ottime condizioni!"
elif [ "$health_score" -ge 70 ]; then
    echo "🟡 Repository in buone condizioni, alcuni miglioramenti possibili"
elif [ "$health_score" -ge 50 ]; then
    echo "🟠 Repository necessita attenzione, ottimizzazioni raccomandate"
else
    echo "🔴 Repository richiede intervento immediato!"
fi

echo
echo "💡 RACCOMANDAZIONI:"
if [ "$loose_objects" -gt 1000 ]; then
    echo "   • Esegui 'git gc --aggressive'"
fi
if [ "$repo_size_mb" -gt 100 ]; then
    echo "   • Considera repository cleanup e Git LFS"
fi
if [ "$large_files" -gt 0 ]; then
    echo "   • Migra file grandi a Git LFS"
fi
if [ "$old_branches" -gt 0 ]; then
    echo "   • Pulisci branch stagnanti"
fi
echo "   • Configura automated maintenance"
echo "   • Monitor repository metrics regolarmente"
```

## Best Practices Riassunto

### ✅ Performance Essentials

1. **Git LFS** per file binari e grandi asset
2. **Sparse checkout** per repository di grandi dimensioni
3. **Configurazione ottimizzata** per operazioni Git
4. **Manutenzione periodica** con garbage collection
5. **Monitoring** delle performance e dimensioni
6. **Parallel operations** per velocizzare transfer
7. **Repository health checks** regolari

### ❌ Performance Anti-Patterns

1. **File binari grandi** nel repository principale
2. **Mancanza di manutenzione** periodica
3. **Configurazione Git** non ottimizzata
4. **Clone completi** quando non necessari
5. **Ignorare avvertimenti** di performance
6. **Repository monolitici** senza organizzazione
7. **Mancanza di monitoring** delle metriche

### ⚡ Quick Wins

```bash
# Configurazione rapida performance
git config --global core.preloadindex true
git config --global core.fsmonitor true
git config --global pack.threads 0
git config --global fetch.parallel 8

# Manutenzione rapida
git gc --aggressive
git repack -a -d

# Setup Git LFS per file comuni
git lfs track "*.{png,jpg,pdf,zip,mp4}"
```

---

*Le ottimizzazioni di performance Git migliorano significativamente l'esperienza di sviluppo, specialmente in team e progetti di grandi dimensioni.*
