# Tecniche Avanzate di Recupero

## 📚 Introduzione

Questa guida esplora tecniche avanzate per situazioni di recovery complesse, inclusi scenari con corruzioni, recovery di dati dal filesystem, e situazioni dove i metodi standard non funzionano.

## 🎯 Scenari Avanzati Trattati

1. **Recovery da filesystem corruption**
2. **Ricostruzione di repository da frammenti**
3. **Recovery cross-platform e cross-sistema**
4. **Tecniche forensi per Git**
5. **Recovery da backup parziali**
6. **Automazione delle procedure di recovery**

## 🔬 Scenario 1: Recovery da Filesystem Corrotto

### Situazione
Il filesystem ha problemi e Git non può accedere a .git/objects.

```bash
# Errori tipici
git status
# fatal: unable to read tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904
# error: unable to read sha1 file of 4b825dc642cb6eb9a060e54bf8d69288fbee4904

ls .git/objects/
# ls: cannot access '.git/objects/': Input/output error
```

### ✅ Recovery Step-by-Step

#### 1. Diagnosi Approfondita
```bash
# Verifica filesystem
fsck /dev/sda1  # Su Linux
# o First Aid su macOS Disk Utility

# Verifica accessibilità Git
git fsck --full --strict 2>errors.log
cat errors.log  # Analizza errori specifici

# Verifica integrità oggetti
find .git/objects -type f -exec file {} \; | grep -v "ASCII text"
```

#### 2. Backup Immediato
```bash
# Backup di tutto quello che è accessibile
mkdir recovery-$(date +%s)
cp -r .git recovery-*/git-backup 2>/dev/null || true
cp -r . recovery-*/working-backup 2>/dev/null || true

# Backup specifico di oggetti salvabili
find .git/objects -type f -readable -exec cp {} recovery-*/objects/ \; 2>/dev/null
```

#### 3. Recovery Selettivo
```bash
# Ricostruire repository da oggetti salvabili
git init temp-recovery
cd temp-recovery

# Importare oggetti salvabili
cp ../recovery-*/objects/* .git/objects/*/

# Tentare ricostruzione
git fsck --unreachable
git for-each-ref  # Vedere cosa è recuperabile
```

#### 4. Recovery da Pack Files
```bash
# Se pack files sono intatti
ls .git/objects/pack/
# pack-a1b2c3d4.idx
# pack-a1b2c3d4.pack

# Verificare integrità pack
git verify-pack -v .git/objects/pack/pack-*.idx

# Estrarre oggetti da pack
git unpack-objects < .git/objects/pack/pack-*.pack
```

## 🔬 Scenario 2: Ricostruzione da Frammenti

### Situazione
Hai solo parti del repository da diverse fonti (backup parziali, cloni locali, ecc.).

```bash
# Fonti disponibili:
# - Backup vecchio di 1 settimana (.git-backup/)
# - Clone locale di collega (../colleague-repo/)  
# - Backup working directory (../work-backup/)
# - Remote repository (origin)
```

### ✅ Strategia di Ricostruzione Completa

#### 1. Analisi delle Fonti
```bash
#!/bin/bash
# analyze-sources.sh

echo "=== ANALYSIS OF AVAILABLE SOURCES ==="

# Analizza backup locale
if [ -d ".git-backup" ]; then
    echo "LOCAL BACKUP:"
    cd .git-backup
    git log --oneline -10 2>/dev/null || echo "  - Corrupted"
    git branch -a 2>/dev/null || echo "  - No branches accessible"
    cd ..
fi

# Analizza clone collega
if [ -d "../colleague-repo" ]; then
    echo "COLLEAGUE REPO:"
    cd ../colleague-repo
    git log --oneline -10 2>/dev/null
    git branch -a 2>/dev/null
    cd ../
fi

# Analizza remote
echo "REMOTE REPOSITORY:"
git ls-remote origin 2>/dev/null || echo "  - Not accessible"
```

#### 2. Merge Strategy
```bash
# Creare repository master per merge
git init recovery-master
cd recovery-master

# Aggiungere remote originale
git remote add origin URL-ORIGINAL

# Aggiungere colleague come remote
git remote add colleague ../colleague-repo

# Aggiungere backup come remote (se possibile)
git remote add backup ../.git-backup

# Fetch da tutte le fonti
git fetch origin 2>/dev/null || echo "Origin fetch failed"
git fetch colleague 2>/dev/null || echo "Colleague fetch failed"  
git fetch backup 2>/dev/null || echo "Backup fetch failed"

# Vedere cosa è disponibile
git branch -a
git log --oneline --all --graph -20
```

#### 3. Ricostruzione Intelligente
```bash
# Identificare il branch più completo
git log --oneline --all --graph | head -50

# Strategia: partire dal più recente e completo
git checkout -b master origin/master 2>/dev/null || \
git checkout -b master colleague/main 2>/dev/null || \
git checkout -b master backup/master

# Merge selettivo da altre fonti
git merge colleague/feature-branch --no-edit 2>/dev/null || true
git merge backup/experimental --no-edit 2>/dev/null || true

# Risolvere conflitti e verificare
git status
# Se ci sono conflitti, risolverli manualmente
```

#### 4. Recovery di Working Directory
```bash
# Se hai backup del working directory ma non .git
if [ -d "../work-backup" ]; then
    # Confrontare con versione ricostruita
    diff -r . ../work-backup/ > changes.diff
    
    # Applicare modifiche mancanti
    rsync -av --ignore-existing ../work-backup/ ./
    
    # Verificare cosa è nuovo/modificato
    git status
    git diff
fi
```

## 🔬 Scenario 3: Recovery Cross-Platform

### Situazione
Devi recuperare un repository Git che è stato sviluppato su sistemi diversi con problemi di encoding, line endings, e path separators.

```bash
# Problemi tipici:
# - Filename encoding (UTF-8 vs Latin1)
# - Line endings (CRLF vs LF)
# - Case sensitivity (Windows vs Linux)
# - Path length limits
```

### ✅ Normalizzazione Cross-Platform

#### 1. Diagnosi Encoding Issues
```bash
# Verificare encoding problematici
find . -name "*.txt" -o -name "*.md" | xargs file
# file.txt: UTF-8 Unicode text
# readme.md: ISO-8859 text

# Verificare line endings
find . -name "*.js" | xargs file | grep CRLF
```

#### 2. Fixing Encoding Problems
```bash
# Convertire encoding problematici
find . -name "*.txt" -exec iconv -f ISO-8859-1 -t UTF-8 {} -o {}.utf8 \;
find . -name "*.txt.utf8" -exec bash -c 'mv "$1" "${1%.utf8}"' _ {} \;

# Git configuration per encoding
git config --local core.precomposeunicode true
git config --local core.quotepath false
```

#### 3. Line Endings Normalization
```bash
# Configurare line endings automatici
echo "* text=auto" > .gitattributes
echo "*.sh text eol=lf" >> .gitattributes
echo "*.bat text eol=crlf" >> .gitattributes

# Normalizzare repository esistente
git add --renormalize .
git commit -m "Normalize line endings"
```

#### 4. Case Sensitivity Issues
```bash
# Su sistemi case-insensitive, trovare conflitti
git config core.ignorecase false

# Trovare file con case conflicts
git ls-files | sort -f | uniq -d -i

# Risolvere rinominando
for file in $(git ls-files | sort -f | uniq -d -i); do
    mv "$file" "${file}.tmp"
    git add "${file}.tmp"
    git rm "$file"
    mv "${file}.tmp" "${file}_fixed"
    git add "${file}_fixed"
done
```

## 🔬 Scenario 4: Git Forensics per Recovery

### Situazione
Devi ricostruire cosa è successo in un repository per capire come recuperare dati persi.

### ✅ Analisi Forense Completa

#### 1. Timeline Reconstruction
```bash
# Ricostruire timeline completa
git log --all --full-history --pretty=format:"%h %ad %an %s" --date=iso > timeline.log

# Includere reflog di tutti i refs
git reflog --all --pretty=format:"%h %ad %an %s" --date=iso >> timeline.log

# Analizzare pattern sospetti
grep -E "(reset|rebase|amend|force)" timeline.log
```

#### 2. Object Archaeology
```bash
# Trovare tutti gli oggetti non referenziati
git fsck --unreachable --dangling > unreachable.log

# Analizzare ogni oggetto unreachable
while read type hash; do
    if [ "$type" = "unreachable" ]; then
        echo "=== $hash ===" 
        git cat-file -t $hash
        git cat-file -p $hash | head -10
        echo ""
    fi
done < unreachable.log
```

#### 3. Branch Archaeology
```bash
# Ricostruire storia dei branch
git for-each-ref --format="%(refname) %(objectname) %(committerdate)" \
    refs/heads/ refs/remotes/ refs/tags/ > refs-history.log

# Cercare pattern di distruzione
git reflog --all | grep -E "(delete|force|reset)" > destruction-events.log

# Analizzare packed-refs per referenze cancellate
if [ -f .git/packed-refs ]; then
    grep -v '^#' .git/packed-refs > packed-refs-analysis.log
fi
```

#### 4. Content Archaeology
```bash
# Cercare contenuto specifico in tutti gli oggetti
git rev-list --all --objects | \
while read hash filename; do
    if git cat-file -e $hash 2>/dev/null; then
        if git cat-file -p $hash 2>/dev/null | grep -q "SEARCH_PATTERN"; then
            echo "Found in: $hash $filename"
        fi
    fi
done
```

## 🔬 Scenario 5: Recovery da Backup Parziali

### Situazione
Hai solo backup parziali e devi ricostruire il massimo possibile.

```bash
# Disponibili:
# - Bundle parziale (bundle-partial.bundle)
# - Oggetti sparsi (objects-backup.tar.gz)
# - Diff files (changes-*.patch)
# - Database backup (db-state.sql)
```

### ✅ Ricostruzione da Componenti

#### 1. Recovery da Bundle
```bash
# Analizzare bundle
git bundle verify bundle-partial.bundle

# Estrarre dal bundle
git clone bundle-partial.bundle recovered-from-bundle
cd recovered-from-bundle

# Vedere cosa contiene
git branch -a
git log --oneline --all --graph
```

#### 2. Integrazione Oggetti Sparsi
```bash
# Estrarre oggetti backup
tar -xzf objects-backup.tar.gz

# Integrarli nel repository
cp -r objects/* .git/objects/

# Verificare nuovi oggetti disponibili
git fsck --unreachable
git cat-file --batch-check --batch-all-objects
```

#### 3. Applicazione Patch Files
```bash
# Ordinare patch files per timestamp
ls changes-*.patch | sort

# Applicare in ordine
for patch in $(ls changes-*.patch | sort); do
    echo "Applying $patch..."
    git apply "$patch" 2>/dev/null || \
    git apply --reject "$patch" 2>/dev/null || \
    echo "Failed: $patch"
done

# Verificare risultato
git status
git diff
```

#### 4. Recovery da Database State
```bash
# Se hai backup del database dell'applicazione
# Ricostruire stato del progetto da DB

# Esempio per applicazione web:
sqlite3 db-state.sql "SELECT filename, content FROM files;" | \
while IFS='|' read filename content; do
    echo "$content" > "$filename"
done

# Aggiungere file ricostruiti
git add .
git commit -m "Reconstruct from database backup"
```

## 🤖 Automazione Recovery

### Script di Recovery Completo
```bash
#!/bin/bash
# advanced-recovery.sh

RECOVERY_DIR="recovery-$(date +%s)"
mkdir -p "$RECOVERY_DIR"

echo "=== ADVANCED GIT RECOVERY TOOL ==="

# 1. Backup stato corrente
echo "1. Creating backup..."
cp -r . "$RECOVERY_DIR/original-state" 2>/dev/null || true

# 2. Diagnosi automatica
echo "2. Running diagnostics..."
{
    echo "=== GIT STATUS ==="
    git status 2>&1
    echo -e "\n=== GIT FSCK ==="
    git fsck --full 2>&1
    echo -e "\n=== REFLOG ==="
    git reflog --all 2>&1
    echo -e "\n=== BRANCHES ==="
    git branch -a 2>&1
} > "$RECOVERY_DIR/diagnostics.log"

# 3. Recovery automatico
echo "3. Attempting automatic recovery..."

# Try ORIG_HEAD recovery
if git show ORIG_HEAD >/dev/null 2>&1; then
    echo "  - ORIG_HEAD available, creating backup branch"
    git branch recovery-orig-head ORIG_HEAD 2>/dev/null || true
fi

# Try reflog recovery
git reflog | head -20 | while read hash rest; do
    if git cat-file -e "$hash" 2>/dev/null; then
        git branch "recovery-$hash" "$hash" 2>/dev/null || true
    fi
done

# Try unreachable objects
git fsck --unreachable | grep commit | head -10 | while read type hash; do
    git branch "recovery-unreachable-${hash:0:8}" "$hash" 2>/dev/null || true
done

# 4. Report
echo "4. Recovery report:"
git branch | grep recovery- | wc -l
echo "Recovery branches created: $(git branch | grep recovery- | wc -l)"
echo "Full diagnostics in: $RECOVERY_DIR/diagnostics.log"
echo "Original state backed up in: $RECOVERY_DIR/original-state"

echo "=== RECOVERY COMPLETE ==="
echo "Review recovery branches and merge as needed."
```

### Recovery Assistant con UI
```bash
#!/bin/bash
# recovery-assistant.sh

show_menu() {
    echo "=== GIT RECOVERY ASSISTANT ==="
    echo "1. Quick diagnosis"
    echo "2. Reflog recovery"
    echo "3. Unreachable objects recovery"
    echo "4. File-specific recovery"
    echo "5. Branch recovery"
    echo "6. Full forensic analysis"
    echo "7. Exit"
    echo -n "Choose option: "
}

quick_diagnosis() {
    echo "=== QUICK DIAGNOSIS ==="
    git status --porcelain
    git log --oneline -5 2>/dev/null || echo "Log not available"
    git reflog -5 2>/dev/null || echo "Reflog not available"
    git fsck --quick 2>/dev/null || echo "Repository may be corrupted"
}

reflog_recovery() {
    echo "=== REFLOG RECOVERY ==="
    git reflog --all | head -20
    echo -n "Enter commit hash to recover: "
    read hash
    if [ -n "$hash" ]; then
        git branch "recovery-$(date +%s)" "$hash"
        echo "Recovery branch created"
    fi
}

# Main loop
while true; do
    show_menu
    read choice
    case $choice in
        1) quick_diagnosis ;;
        2) reflog_recovery ;;
        3) unreachable_recovery ;;
        4) file_recovery ;;
        5) branch_recovery ;;
        6) forensic_analysis ;;
        7) exit 0 ;;
        *) echo "Invalid option" ;;
    esac
    echo -e "\nPress Enter to continue..."
    read
done
```

## 📊 Recovery Success Matrix

| Scenario | Probabilità Recovery | Tempo Stimato | Strumenti Richiesti |
|----------|---------------------|---------------|-------------------|
| Filesystem corruption | 60-80% | 2-4 ore | fsck, backup tools |
| Frammentazione repository | 80-95% | 1-3 ore | Bundle, remote access |
| Cross-platform issues | 95-99% | 30min-2 ore | Encoding tools |
| Forensic reconstruction | 70-90% | 2-8 ore | Scripts custom |
| Backup parziali | 50-85% | 1-4 ore | Multiple tools |
| Object corruption | 60-80% | 1-3 ore | Git internals |

## 💡 Best Practices Avanzate

### 1. Prevenzione Proattiva
```bash
# Backup automatico con metadata
git bundle create "backup-$(date +%s).bundle" --all
git fsck --full > "integrity-$(date +%s).log"
tar -czf "objects-$(date +%s).tar.gz" .git/objects/
```

### 2. Monitoring Continuo
```bash
# Script di monitoring quotidiano
#!/bin/bash
git fsck --quick || echo "ALERT: Repository integrity issue"
git gc --auto
git count-objects -v | grep "size-pack" | awk '{if($2>100000) print "ALERT: Large repository"}'
```

### 3. Recovery Testing
```bash
# Test periodico delle procedure
cp -r .git .git-test-backup
# Simula corruzione
rm .git/objects/*/random-object
# Testa recovery
git fsck --full
# Ripristina
rm -rf .git
mv .git-test-backup .git
```

## 📝 Riassunto

Le tecniche avanzate di recovery includono:

1. **Diagnosi approfondita** con analisi forense
2. **Recovery multi-sorgente** combinando diverse fonti
3. **Normalizzazione cross-platform** per compatibility
4. **Automazione** delle procedure complesse
5. **Ricostruzione intelligente** da frammenti

**Chiavi del successo**:
- **Metodologia sistemática** nell'approccio
- **Backup** di ogni fase del recovery
- **Documentazione** dettagliata del processo
- **Testing** delle soluzioni prima dell'applicazione
- **Patience** - il recovery avanzato richiede tempo

Ricorda: anche nei casi più complessi, Git raramente perde dati definitivamente. Con pazienza e metodologia è quasi sempre possibile recuperare la maggior parte del lavoro!
