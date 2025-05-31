# Performance Problems - Diagnosi e Risoluzione

## Indice
1. [Identificazione dei Problemi di Performance](#identificazione-dei-problemi-di-performance)
2. [Repository Size Problems](#repository-size-problems)
3. [Operazioni Lente](#operazioni-lente)
4. [Network Performance Issues](#network-performance-issues)
5. [Disk I/O Performance](#disk-io-performance)
6. [Memory Usage Optimization](#memory-usage-optimization)
7. [Large File Handling](#large-file-handling)
8. [Git History Optimization](#git-history-optimization)
9. [Monitoring e Profiling](#monitoring-e-profiling)
10. [Prevention Strategies](#prevention-strategies)

---

## Identificazione dei Problemi di Performance

### Sintomi Comuni
```bash
# Repository troppo grande
git count-objects -v
git ls-files | wc -l

# Operazioni Git lente
time git status
time git log --oneline -n 100
time git fetch origin

# Controllo dimensioni cartelle
du -sh .git/
du -sh .git/objects/
find .git/objects/ -type f | wc -l
```

### Strumenti di Diagnostica
```bash
# Analisi oggetti repository
git count-objects -vH

# Verifica integrità
git fsck --full --unreachable

# Analisi performance log
git config --global log.showSignature false
git config --global core.preloadindex true
git config --global core.fscache true

# Profiling operazioni Git
GIT_TRACE=1 git status
GIT_TRACE_PERFORMANCE=1 git log --oneline -n 50
```

---

## Repository Size Problems

### Analisi Dimensioni Repository
```bash
#!/bin/bash
# Script: analyze-repo-size.sh

echo "=== Repository Size Analysis ==="
echo "Total repository size:"
du -sh .

echo -e "\n=== .git directory breakdown ==="
du -sh .git/*

echo -e "\n=== Largest objects in repository ==="
git verify-pack -v .git/objects/pack/*.idx | \
sort -k 3 -n | tail -10

echo -e "\n=== File count by type ==="
find . -name .git -prune -o -type f -print | \
sed 's/.*\.//' | sort | uniq -c | sort -rn | head -10

echo -e "\n=== Largest files in working directory ==="
find . -name .git -prune -o -type f -printf '%s %p\n' | \
sort -rn | head -10 | while read size path; do
    echo "$(numfmt --to=iec $size) $path"
done
```

### Identificazione File Problematici
```bash
# Trova i file più grandi nella storia
git rev-list --objects --all | \
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
sed -n 's/^blob //p' | sort -k2 -nr | head -20

# Script per analisi dettagliata
#!/bin/bash
# Script: find-large-files.sh

echo "=== Large Files in Git History ==="
git rev-list --objects --all | \
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
awk '/^blob/ {print substr($0,6)}' | sort -k2 -nr | head -20 | \
while read sha size path; do
    echo "Size: $(numfmt --to=iec $size), Path: $path, SHA: $sha"
done

echo -e "\n=== Files by extension size ==="
git ls-tree -r -l HEAD | \
awk '{print $4, $5}' | \
sed 's/.*\.//' | \
awk '{ext=$NF; $NF=""; sizes[ext]+=$4; counts[ext]++} 
     END {for(e in sizes) printf "%-10s: %10s (%d files)\n", e, sizes[e], counts[e]}' | \
sort -k2 -nr
```

### Pulizia Repository
```bash
# Rimozione file grandi dalla storia
git filter-branch --tree-filter 'rm -f large-file.bin' HEAD
# O usando git-filter-repo (più veloce)
git filter-repo --path large-file.bin --invert-paths

# Pulizia oggetti orfani
git reflog expire --expire=now --all
git gc --prune=now --aggressive

# Rimozione branch/tag non necessari
git branch -d feature/old-feature
git tag -d v0.1.0-beta

# Pulizia completa
git remote prune origin
git gc --aggressive --prune=now
```

---

## Operazioni Lente

### Ottimizzazione Git Status
```bash
# Configurazioni per performance
git config core.preloadindex true
git config core.fscache true
git config gc.auto 256

# Disabilitare controlli non necessari
git config advice.statusHints false
git config status.showUntrackedFiles no  # temporaneo

# Controllo performance status
time git status
time git status --porcelain

# Status ottimizzato per grandi repository
git status --ignored=no --untracked-files=no
```

### Ottimizzazione Git Log
```bash
# Configurazioni log performance
git config log.decorate false
git config log.showSignature false

# Log con limitazioni per performance
git log --oneline -n 100
git log --oneline --since="1 week ago"
git log --oneline --author="username"

# Evitare operazioni costose
git log --no-merges --oneline
git log --grep="pattern" --oneline
git log --stat --oneline -n 10  # invece di --stat completo
```

### Ottimizzazione Git Diff
```bash
# Diff ottimizzato
git config diff.algorithm patience
git config diff.compactionHeuristic true

# Diff per grandi file
git config core.bigFileThreshold 100m
git diff --no-index --stat

# Diff incrementale
git diff --cached
git diff HEAD~1..HEAD --name-only
```

---

## Network Performance Issues

### Ottimizzazione Fetch/Pull
```bash
# Configurazioni network
git config http.postBuffer 524288000  # 500MB
git config http.maxRequestBuffer 100M
git config core.compression 6

# Fetch ottimizzato
git fetch --depth=1 origin main  # shallow fetch
git fetch --unshallow  # se necessario tutto

# Clone ottimizzato
git clone --depth=1 https://github.com/user/repo.git
git clone --filter=blob:none https://github.com/user/repo.git  # partial clone

# Configurazione SSH per performance
# ~/.ssh/config
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_rsa
    Compression yes
    ServerAliveInterval 60
    ServerAliveCountMax 10
    TCPKeepAlive yes
    ControlMaster auto
    ControlPath ~/.ssh/master-%r@%h:%p
    ControlPersist 600
```

### Gestione Large Repository
```bash
# Partial clone per repository grandi
git clone --filter=blob:limit=1m https://github.com/user/large-repo.git
cd large-repo

# Fetch specifici object quando necessario
git lfs pull
git fetch origin --depth=50

# Configurazione LFS per file grandi
git lfs track "*.psd"
git lfs track "*.zip"
git lfs track "*.tar.gz"
git add .gitattributes
```

### Proxy e Firewall Configuration
```bash
# Configurazione proxy
git config --global http.proxy http://proxy.company.com:8080
git config --global https.proxy https://proxy.company.com:8080

# Proxy con autenticazione
git config --global http.proxy http://username:password@proxy.company.com:8080

# SSL verification per corporate environments
git config --global http.sslVerify false  # solo se necessario
git config --global http.sslCAInfo /path/to/certificate.pem

# Timeout configurations
git config --global http.lowSpeedLimit 1000
git config --global http.lowSpeedTime 300
```

---

## Disk I/O Performance

### Ottimizzazione File System
```bash
# Configurazioni per performance I/O
git config core.autocrlf false  # evita conversioni
git config core.safecrlf false
git config core.trustctime false

# Disabilitare controlli costosi
git config core.checkStat minimal
git config core.ignoreStat true  # se appropriato

# Pack file optimization
git config pack.deltaCacheSize 256m
git config pack.packSizeLimit 2g
git config pack.windowMemory 256m
```

### SSD vs HDD Optimizations
```bash
# Configurazioni per SSD
git config core.preloadindex true
git config core.untrackedCache true
git config feature.manyFiles true

# Configurazioni per HDD
git config pack.useBitmaps true
git config repack.useDeltaBaseOffset true
git config gc.pruneExpire "30 days ago"

# Monitoring I/O
iotop -o  # monitorare I/O Git operations
iostat -x 1  # statistiche I/O
```

### Temporary Files Optimization
```bash
# Configurazione directory temporanee
export TMPDIR=/fast/tmp  # usa SSD per temp
git config core.bigFileThreshold 50m

# Cleanup automatico
git config gc.autoPackLimit 50
git config gc.autoDetach false

# Script pulizia periodica
#!/bin/bash
# Script: git-cleanup.sh
cd /path/to/repo
git reflog expire --expire=30.days --all
git gc --auto
git repack -Ad
git prune
```

---

## Memory Usage Optimization

### Configurazioni Memory
```bash
# Ottimizzazione uso memoria
git config pack.deltaCacheSize 128m
git config pack.packSizeLimit 1g
git config pack.windowMemory 128m
git config pack.threads 2

# Per sistemi con poca memoria
git config pack.window 10
git config pack.depth 50
git config core.bigFileThreshold 20m

# Monitoring memoria Git
ps aux | grep git
top -p $(pgrep git)
```

### Large Repository Strategies
```bash
# Sparse checkout per ridurre working directory
git config core.sparseCheckout true
echo "src/*" > .git/info/sparse-checkout
echo "docs/*" >> .git/info/sparse-checkout
git read-tree -mu HEAD

# Worktree per multiple branch
git worktree add ../feature-branch feature-branch
git worktree add ../hotfix-branch hotfix-branch

# Shallow repository per CI/CD
git clone --depth=1 --single-branch --branch=main https://github.com/user/repo.git
```

---

## Large File Handling

### Git LFS Setup
```bash
# Installazione e configurazione LFS
git lfs install
git lfs track "*.psd"
git lfs track "*.ai"
git lfs track "*.zip"
git lfs track "*.tar.gz"
git lfs track "*.mp4"

# Verifica LFS
git lfs ls-files
git lfs status

# Migrazione file esistenti a LFS
git lfs migrate import --include="*.zip" --everything
git lfs migrate info
```

### Alternative per File Grandi
```bash
# Submodules per dipendenze grandi
git submodule add https://github.com/vendor/large-library.git vendor/library
git submodule update --init --recursive

# Symbolic links per file condivisi
ln -s /shared/storage/large-file.bin large-file.bin
git add large-file.bin

# External storage references
echo "https://storage.company.com/file.zip" > file.url
git add file.url
```

### Performance Monitoring LFS
```bash
# Monitoring LFS transfers
git lfs ls-files --size
git lfs bandwidth

# Cleanup LFS cache
git lfs prune
git lfs clean

# LFS performance tuning
git config lfs.concurrenttransfers 8
git config lfs.transfer.maxretries 3
```

---

## Git History Optimization

### Rewrite History for Performance
```bash
# Squash merge per ridurre history
git rebase -i HEAD~10
# Nel editor, cambia 'pick' in 'squash' per commit da unire

# Rimozione commit vuoti
git filter-branch --prune-empty --tree-filter 'rm -f large-file.bin' HEAD

# Using git-filter-repo (raccomandato)
pip install git-filter-repo
git filter-repo --path large-file.bin --invert-paths
git filter-repo --strip-blobs-bigger-than 10M
```

### Branch Strategy Optimization
```bash
# Cleanup old branches
git branch -r --merged | grep -v main | xargs git push origin --delete
git branch --merged | grep -v main | xargs git branch -d

# Shallow clones per feature branches
git clone --depth=1 --single-branch --branch=feature https://github.com/user/repo.git

# Fast-forward merge strategy
git config merge.ff only
git config pull.ff only
```

---

## Monitoring e Profiling

### Performance Monitoring Scripts
```bash
#!/bin/bash
# Script: git-performance-monitor.sh

echo "=== Git Performance Monitor ==="
echo "Repository: $(pwd)"
echo "Date: $(date)"
echo

echo "=== Repository Statistics ==="
echo "Total size: $(du -sh . | cut -f1)"
echo "Git directory: $(du -sh .git | cut -f1)"
echo "Object count: $(git count-objects -v | grep 'count' | cut -d' ' -f2)"
echo "Pack count: $(git count-objects -v | grep 'packs' | cut -d' ' -f2)"

echo -e "\n=== Performance Tests ==="
echo "Git status timing:"
time git status > /dev/null 2>&1

echo "Git log timing (100 commits):"
time git log --oneline -n 100 > /dev/null 2>&1

echo "Git diff timing:"
time git diff HEAD~1..HEAD > /dev/null 2>&1

echo -e "\n=== Network Performance ==="
echo "Fetch timing:"
time git fetch origin --dry-run 2>&1 | grep -E "(Total|Done)"

echo -e "\n=== Memory Usage ==="
ps aux | grep git | grep -v grep
```

### Automated Performance Alerts
```bash
#!/bin/bash
# Script: git-performance-alert.sh

REPO_SIZE_LIMIT=1000000  # 1GB in KB
OBJECT_COUNT_LIMIT=100000

REPO_SIZE=$(du -sk .git | cut -f1)
OBJECT_COUNT=$(git count-objects | cut -d' ' -f1)

if [ $REPO_SIZE -gt $REPO_SIZE_LIMIT ]; then
    echo "ALERT: Repository size exceeds limit: $(du -sh .git | cut -f1)"
fi

if [ $OBJECT_COUNT -gt $OBJECT_COUNT_LIMIT ]; then
    echo "ALERT: Object count exceeds limit: $OBJECT_COUNT"
fi

# Check for large files
LARGE_FILES=$(git ls-tree -r -l HEAD | awk '$4 > 10485760 {print $4, $5}')
if [ ! -z "$LARGE_FILES" ]; then
    echo "ALERT: Large files detected:"
    echo "$LARGE_FILES"
fi
```

---

## Prevention Strategies

### Repository Hygiene
```bash
# Git hooks per prevenire problemi
# hooks/pre-commit
#!/bin/bash
# Controlla dimensione file prima del commit

max_size=10485760  # 10MB
files=$(git diff --cached --name-only)

for file in $files; do
    if [ -f "$file" ]; then
        size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null)
        if [ $size -gt $max_size ]; then
            echo "Error: $file is too large ($(numfmt --to=iec $size))"
            echo "Consider using Git LFS for large files"
            exit 1
        fi
    fi
done
```

### Automated Maintenance
```bash
# Cron job per manutenzione automatica
# crontab -e
# 0 2 * * 0 /path/to/git-maintenance.sh

#!/bin/bash
# Script: git-maintenance.sh

for repo in /path/to/repos/*; do
    if [ -d "$repo/.git" ]; then
        cd "$repo"
        echo "Maintaining: $repo"
        
        # Cleanup
        git gc --auto
        git remote prune origin
        git reflog expire --expire=30.days --all
        
        # Repack if needed
        if [ $(git count-objects | cut -d' ' -f1) -gt 1000 ]; then
            git repack -Ad
        fi
    fi
done
```

### Performance Configuration Template
```bash
#!/bin/bash
# Script: configure-git-performance.sh

# Core performance settings
git config core.preloadindex true
git config core.fscache true
git config core.autocrlf false
git config core.trustctime false
git config core.checkStat minimal

# Pack and GC settings
git config pack.deltaCacheSize 256m
git config pack.packSizeLimit 2g
git config pack.windowMemory 256m
git config gc.auto 256
git config gc.autoPackLimit 50
git config gc.pruneExpire "30 days ago"

# Network settings
git config http.postBuffer 524288000
git config http.maxRequestBuffer 100M
git config core.compression 6

# Log and diff settings
git config log.decorate false
git config log.showSignature false
git config diff.algorithm patience
git config diff.compactionHeuristic true

echo "Git performance configuration applied!"
```

### Best Practices Checklist
```markdown
## Performance Best Practices Checklist

### Repository Setup
- [ ] Configure Git LFS for files > 100MB
- [ ] Set up appropriate .gitignore
- [ ] Configure sparse-checkout if needed
- [ ] Set up proper pack configurations

### Development Workflow
- [ ] Use shallow clones for CI/CD
- [ ] Implement pre-commit hooks for file size checks
- [ ] Regular cleanup of merged branches
- [ ] Monitor repository size growth

### Maintenance
- [ ] Weekly git gc --auto
- [ ] Monthly cleanup of reflog
- [ ] Quarterly review of large files
- [ ] Annual repository size audit

### Monitoring
- [ ] Set up size alerts
- [ ] Monitor operation timings
- [ ] Track network performance
- [ ] Monitor disk I/O usage
```

---

## Conclusioni

La gestione delle performance in Git richiede:

1. **Monitoraggio proattivo** delle dimensioni e performance
2. **Configurazioni ottimizzate** per l'ambiente specifico
3. **Strategie appropriate** per file grandi e repository complessi
4. **Manutenzione regolare** per prevenire degradazione
5. **Strumenti appropriati** come Git LFS per file grandi

La chiave è trovare il giusto equilibrio tra performance e funzionalità, adattando le configurazioni al caso d'uso specifico.
