# Esempio 05: Gestione Avanzata di File Grandi e Repository Performance

> **Scenario**: Ottimizzazione di un repository con file grandi, gestione di binary assets e miglioramento delle performance  
> **Complessità**: ⭐⭐⭐⭐⭐ (Esperto)  
> **Tempo**: 45-60 minuti  

## 📖 Descrizione

Questo esempio avanzato mostra come gestire efficacemente repository che contengono file grandi, binary assets, e come ottimizzare le performance di Git per progetti complessi. Include tecniche per:
- Gestione di file multimediali e assets di grandi dimensioni
- Configurazione di Git LFS (Large File Storage)
- Strategie di organizzazione per repository performanti
- Tecniche di pulizia e ottimizzazione

## 🎯 Obiettivi

- ✅ Configurare Git LFS per file grandi
- ✅ Implementare strategie di gestione binary assets
- ✅ Ottimizzare le performance del repository
- ✅ Utilizzare .gitattributes per configurazioni avanzate
- ✅ Implementare workflow per progetti multimediali

## ⚙️ Setup e Configurazione

### 1. Preparazione dell'Ambiente

```bash
# Crea la directory per l'esempio
mkdir git-large-files-example
cd git-large-files-example

# Inizializza il repository
git init

# Verifica se Git LFS è installato
if ! command -v git-lfs &> /dev/null; then
    echo "⚠️ Git LFS non installato. Installazione..."
    # Su Ubuntu/Debian
    # sudo apt-get install git-lfs
    # Su macOS con Homebrew
    # brew install git-lfs
    # Su Windows, scarica da: https://git-lfs.github.io/
    echo "Installa Git LFS dal sito ufficiale per continuare"
fi

# Inizializza Git LFS nel repository
git lfs install

echo "✅ Environment setup completed"
```

### 2. Configurazione Git LFS

```bash
echo "⚙️ Configuring Git LFS..."

# Configura Git LFS per diversi tipi di file
git lfs track "*.psd"          # Photoshop files
git lfs track "*.ai"           # Adobe Illustrator files
git lfs track "*.sketch"       # Sketch files
git lfs track "*.fig"          # Figma files
git lfs track "*.mp4"          # Video files
git lfs track "*.mov"          # QuickTime videos
git lfs track "*.avi"          # AVI videos
git lfs track "*.wav"          # Audio files
git lfs track "*.mp3"          # MP3 audio
git lfs track "*.flac"         # FLAC audio
git lfs track "*.zip"          # Zip archives
git lfs track "*.tar.gz"       # Compressed archives
git lfs track "*.dmg"          # macOS disk images
git lfs track "*.iso"          # ISO images
git lfs track "*.exe"          # Windows executables
git lfs track "*.dll"          # Windows libraries
git lfs track "*.so"           # Linux libraries
git lfs track "*.dylib"        # macOS libraries

# File di dataset e machine learning
git lfs track "*.csv" --lockable    # Large CSV files (with locking)
git lfs track "*.json" --lockable   # Large JSON files
git lfs track "*.h5"                # HDF5 files
git lfs track "*.hdf5"              # HDF5 files
git lfs track "*.pkl"               # Pickle files
git lfs track "*.model"             # Model files

# Mostra la configurazione LFS
cat .gitattributes

# Commit della configurazione LFS
git add .gitattributes
git commit -m "feat: configure Git LFS for large file types

- Track design files (PSD, AI, Sketch, Figma)
- Track multimedia files (videos, audio)
- Track binary executables and libraries
- Track data science files with locking for CSVs/JSONs"

echo "✅ Git LFS configuration completed"
```

### 3. Simulazione di Progetto Multimediale

```bash
echo "🎬 Creating multimedia project structure..."

# Crea struttura directory per progetto multimediale
mkdir -p {src,assets}/{images,videos,audio,documents,data}
mkdir -p {build,dist,cache,temp}
mkdir -p docs/{api,user-guides,technical}
mkdir -p tools/{scripts,configs}

# Crea file di configurazione avanzato .gitattributes
cat > .gitattributes << 'EOF'
# Git LFS Configuration
*.psd filter=lfs diff=lfs merge=lfs -text
*.ai filter=lfs diff=lfs merge=lfs -text
*.sketch filter=lfs diff=lfs merge=lfs -text
*.fig filter=lfs diff=lfs merge=lfs -text
*.mp4 filter=lfs diff=lfs merge=lfs -text
*.mov filter=lfs diff=lfs merge=lfs -text
*.avi filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.flac filter=lfs diff=lfs merge=lfs -text
*.zip filter=lfs diff=lfs merge=lfs -text
*.tar.gz filter=lfs diff=lfs merge=lfs -text
*.dmg filter=lfs diff=lfs merge=lfs -text
*.iso filter=lfs diff=lfs merge=lfs -text
*.exe filter=lfs diff=lfs merge=lfs -text
*.dll filter=lfs diff=lfs merge=lfs -text
*.so filter=lfs diff=lfs merge=lfs -text
*.dylib filter=lfs diff=lfs merge=lfs -text

# Data files with locking (prevent simultaneous edits)
*.csv filter=lfs diff=lfs merge=lfs -text lockable
*.json filter=lfs diff=lfs merge=lfs -text lockable
*.h5 filter=lfs diff=lfs merge=lfs -text
*.hdf5 filter=lfs diff=lfs merge=lfs -text
*.pkl filter=lfs diff=lfs merge=lfs -text
*.model filter=lfs diff=lfs merge=lfs -text

# Text files - explicit text handling
*.md text
*.txt text
*.js text
*.css text
*.html text
*.py text
*.sh text eol=lf
*.bat text eol=crlf

# Binary files - explicit binary handling
*.jpg binary
*.jpeg binary
*.png binary
*.gif binary
*.ico binary
*.pdf binary

# Line ending configuration
*.js text eol=lf
*.css text eol=lf
*.html text eol=lf
*.md text eol=lf
*.py text eol=lf
*.sh text eol=lf
*.bat text eol=crlf

# Export-ignore (files not included in archives)
.gitignore export-ignore
.gitattributes export-ignore
*.md export-ignore
docs/ export-ignore
tools/ export-ignore
cache/ export-ignore
temp/ export-ignore
.vscode/ export-ignore
.idea/ export-ignore

# Diff configuration for specific file types
*.css diff=css
*.html diff=html
*.js diff=javascript
*.py diff=python
*.json diff=json
EOF

echo "✅ Advanced .gitattributes configuration created"
```

### 4. Simulazione di File Grandi

```bash
echo "📦 Creating simulated large files..."

# Simula file di design (nota: questi sarebbero file reali in un progetto vero)
echo "Simulated Photoshop file content - normally this would be a large binary PSD file" > assets/images/hero-banner.psd
echo "Simulated Adobe Illustrator content - vector graphics file" > assets/images/logo-design.ai
echo "Simulated Sketch file - UI design file" > assets/images/app-mockup.sketch

# Simula file video (normalmente sarebbero file molto grandi)
echo "Simulated MP4 video content - demo video file" > assets/videos/product-demo.mp4
echo "Simulated MOV video content - tutorial video" > assets/videos/tutorial.mov

# Simula file audio
echo "Simulated WAV audio content - high quality audio" > assets/audio/soundtrack.wav
echo "Simulated MP3 audio content - compressed audio" > assets/audio/notification.mp3

# Simula file di dati grandi
cat > assets/data/large-dataset.csv << 'EOF'
id,name,email,age,city,country,salary,department
1,John Doe,john@example.com,30,New York,USA,75000,Engineering
2,Jane Smith,jane@example.com,28,London,UK,68000,Marketing
3,Mike Johnson,mike@example.com,35,Toronto,Canada,82000,Engineering
EOF

# Simula file di configurazione grandi
cat > assets/data/config.json << 'EOF'
{
  "application": {
    "name": "Large Scale App",
    "version": "2.1.0",
    "environment": "production"
  },
  "database": {
    "primary": {
      "host": "db1.example.com",
      "port": 5432,
      "name": "app_production"
    },
    "replica": {
      "host": "db2.example.com",
      "port": 5432,
      "name": "app_production"
    }
  },
  "cache": {
    "redis": {
      "host": "cache.example.com",
      "port": 6379
    }
  }
}
EOF

# File binari simulati
echo "Binary executable content simulation" > tools/deployment-tool.exe
echo "Binary library content simulation" > src/dependencies/core-library.dll

echo "✅ Large files simulation created"
```

### 5. Configurazione .gitignore Ottimizzata

```bash
echo "🚫 Creating optimized .gitignore..."

cat > .gitignore << 'EOF'
# Build and Distribution
/build/
/dist/
/out/
*.build/

# Cache and Temporary Files
/cache/
/temp/
/tmp/
*.tmp
*.temp
.cache/
.temp/

# OS Generated Files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
desktop.ini

# IDE and Editor Files
.vscode/
.idea/
*.swp
*.swo
*~
.project
.settings/
*.sublime-project
*.sublime-workspace

# Language Specific
# Node.js
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
.npm
.yarn-integrity

# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
env/
venv/
.venv/
pip-log.txt

# Java
*.class
*.log
*.jar
!lib/*.jar
target/

# .NET
bin/
obj/
*.user
*.suo

# Database
*.sqlite
*.db

# Logs
logs/
*.log
npm-debug.log*
yarn-debug.log*
lerna-debug.log*

# Environment Variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Large Data Files (not tracked by LFS)
*.backup
*.dump
*.sql
*.bak

# Generated Documentation
docs/generated/
api-docs/

# Test Coverage
coverage/
.nyc_output/
.coverage

# Security
*.pem
*.key
!public.key
*.p12
*.p8
*.cer
*.crt
*.der

# Large temporary exports
exports/
downloads/
uploads/temp/
EOF

echo "✅ Optimized .gitignore created"
```

## 🚀 Workflow Avanzato per File Grandi

### 6. Gestione Intelligente degli Assets

```bash
echo "🎨 Setting up intelligent asset management..."

# Script per gestione automatica degli assets
cat > tools/scripts/asset-manager.sh << 'EOF'
#!/bin/bash

# Asset Management Script for Large Files

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to log with color
log() {
    echo -e "${GREEN}[$(date +'%Y-%m-%d %H:%M:%S')]${NC} $1"
}

warn() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check file sizes and recommend LFS
check_large_files() {
    log "🔍 Checking for large files..."
    
    # Find files larger than 50MB
    large_files=$(find . -type f -size +50M -not -path './.git/*' -not -path './node_modules/*' 2>/dev/null || true)
    
    if [ -n "$large_files" ]; then
        warn "Found large files (>50MB) that should use Git LFS:"
        echo "$large_files" | while read -r file; do
            size=$(du -h "$file" | cut -f1)
            echo "  📦 $file ($size)"
        done
        
        echo ""
        echo "Consider adding these file types to .gitattributes:"
        echo "$large_files" | sed 's/.*\.//' | sort -u | while read -r ext; do
            echo "  *.$ext filter=lfs diff=lfs merge=lfs -text"
        done
    else
        log "✅ No large files found outside of LFS"
    fi
}

# Optimize repository
optimize_repository() {
    log "🚀 Optimizing repository..."
    
    # Git garbage collection
    git gc --aggressive --prune=now
    
    # Show repository size
    repo_size=$(du -sh .git | cut -f1)
    log "📊 Repository size: $repo_size"
    
    # LFS status
    log "📋 Git LFS status:"
    git lfs ls-files | head -10
}

# Validate LFS files
validate_lfs() {
    log "🔍 Validating Git LFS files..."
    
    # Check LFS status
    lfs_files=$(git lfs ls-files | wc -l)
    log "📊 Files tracked by LFS: $lfs_files"
    
    # Check for files that should be in LFS but aren't
    git ls-files | while read -r file; do
        if [ -f "$file" ]; then
            size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo 0)
            if [ "$size" -gt 10485760 ]; then  # 10MB
                if ! git check-attr filter "$file" | grep -q "lfs"; then
                    warn "Large file not in LFS: $file ($(numfmt --to=iec $size))"
                fi
            fi
        fi
    done
}

# Generate asset report
generate_report() {
    log "📊 Generating asset report..."
    
    cat > asset-report.md << 'REPORT_EOF'
# Asset Management Report

Generated: $(date)

## Repository Statistics

### Overall Size
- Repository size: $(du -sh .git | cut -f1)
- Working directory: $(du -sh --exclude=.git . | cut -f1)

### Git LFS Status
- Files tracked by LFS: $(git lfs ls-files | wc -l)
- LFS storage used: $(git lfs ls-files -s | awk '{sum+=$2} END {print sum/1024/1024 " MB"}')

### File Type Distribution
REPORT_EOF

    # Add file type statistics
    echo "| Extension | Count | Total Size |" >> asset-report.md
    echo "|-----------|-------|------------|" >> asset-report.md
    
    git ls-files | sed 's/.*\.//' | sort | uniq -c | sort -nr | head -10 | while read -r count ext; do
        echo "| .$ext | $count | - |" >> asset-report.md
    done
    
    log "✅ Report generated: asset-report.md"
}

# Main menu
case "${1:-help}" in
    "check")
        check_large_files
        ;;
    "optimize")
        optimize_repository
        ;;
    "validate")
        validate_lfs
        ;;
    "report")
        generate_report
        ;;
    "all")
        check_large_files
        validate_lfs
        optimize_repository
        generate_report
        ;;
    *)
        echo "Asset Manager - Large File Management Tool"
        echo ""
        echo "Usage: $0 {check|optimize|validate|report|all}"
        echo ""
        echo "Commands:"
        echo "  check     - Check for large files"
        echo "  optimize  - Optimize repository performance"
        echo "  validate  - Validate LFS configuration"
        echo "  report    - Generate asset management report"
        echo "  all       - Run all checks"
        ;;
esac
EOF

chmod +x tools/scripts/asset-manager.sh

echo "✅ Asset management script created"
```

### 7. Configurazione Performance

```bash
echo "⚡ Configuring performance optimizations..."

# Configurazioni Git per performance ottimali
git config core.preloadindex true
git config core.fscache true
git config gc.auto 256
git config pack.threads 0

# Configurazioni specifiche per file grandi
git config http.postBuffer 524288000  # 500MB buffer for large pushes
git config lfs.concurrenttransfers 10  # Parallel LFS transfers

# Configurazioni per repository grandi
git config feature.manyFiles true
git config index.threads 0

# Log delle configurazioni
echo "📋 Performance configurations applied:"
git config --get-regexp "(core|pack|http|lfs|gc|feature|index)\." | head -15

# Crea file di configurazione per hook pre-commit
cat > tools/scripts/pre-commit-size-check.sh << 'EOF'
#!/bin/bash

# Pre-commit hook to check file sizes

MAX_SIZE=10485760  # 10MB in bytes
large_files=()

# Check staged files
while IFS= read -r -d '' file; do
    if [ -f "$file" ]; then
        size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo 0)
        if [ "$size" -gt $MAX_SIZE ]; then
            large_files+=("$file ($(numfmt --to=iec $size))")
        fi
    fi
done < <(git diff --cached --name-only -z)

if [ ${#large_files[@]} -gt 0 ]; then
    echo "❌ Large files detected in commit:"
    printf '  %s\n' "${large_files[@]}"
    echo ""
    echo "Consider using Git LFS for these files:"
    echo "  git lfs track \"*.extension\""
    echo "  git add .gitattributes"
    echo ""
    exit 1
fi

exit 0
EOF

chmod +x tools/scripts/pre-commit-size-check.sh

echo "✅ Performance optimizations configured"
```

### 8. Commit e Test del Sistema

```bash
echo "💾 Committing asset management system..."

# Add all files
git add .

# Commit con dettagli dell'implementazione
git commit -m "feat: implement advanced large file management system

Features implemented:
- Git LFS configuration for multimedia and binary files
- Intelligent .gitattributes with file type handling
- Optimized .gitignore for build artifacts and cache
- Asset management script with validation and reporting
- Performance optimizations for large repositories
- Pre-commit hooks for size checking

File types configured for LFS:
- Design files: PSD, AI, Sketch, Figma
- Multimedia: MP4, MOV, WAV, MP3, FLAC
- Binary executables and libraries
- Large data files with lockable CSVs/JSONs

Performance optimizations:
- Enabled core.preloadindex and core.fscache
- Configured parallel operations and buffering
- Set up concurrent LFS transfers"

echo "✅ Asset management system committed"
```

### 9. Testing e Validazione

```bash
echo "🧪 Testing asset management system..."

# Test dello script di gestione assets
echo "📊 Running asset manager checks:"
./tools/scripts/asset-manager.sh all

# Test delle performance Git
echo -e "\n⚡ Testing Git performance:"
time git status
time git log --oneline -10

# Verifica LFS tracking
echo -e "\n📋 LFS tracked files:"
git lfs ls-files

# Test del pre-commit hook
echo -e "\n🔍 Testing pre-commit size check:"
./tools/scripts/pre-commit-size-check.sh

# Verifica configurazioni
echo -e "\n⚙️ Current performance configurations:"
git config --get-regexp "(core|lfs|pack|gc)\."

echo -e "\n✅ All tests completed successfully"
```

## 📊 Monitoraggio e Metriche

### 10. Dashboard di Monitoraggio

```bash
echo "📊 Creating monitoring dashboard..."

# Script per dashboard delle metriche
cat > tools/scripts/repo-dashboard.sh << 'EOF'
#!/bin/bash

# Repository Monitoring Dashboard

echo "📊 REPOSITORY DASHBOARD"
echo "======================"
echo "Generated: $(date)"
echo ""

# Basic repository info
echo "📁 REPOSITORY INFO"
echo "------------------"
echo "Working directory: $(pwd)"
echo "Git version: $(git --version)"
echo "Repository size: $(du -sh .git 2>/dev/null | cut -f1)"
echo "Working tree size: $(du -sh --exclude=.git . 2>/dev/null | cut -f1)"
echo ""

# File statistics
echo "📋 FILE STATISTICS"
echo "------------------"
total_files=$(git ls-files | wc -l)
tracked_files=$(git ls-files | wc -l)
lfs_files=$(git lfs ls-files | wc -l)
untracked_files=$(git ls-files --others --exclude-standard | wc -l)

echo "Total tracked files: $tracked_files"
echo "Files in LFS: $lfs_files"
echo "Untracked files: $untracked_files"
echo ""

# LFS statistics
echo "💾 GIT LFS STATISTICS"
echo "--------------------"
if command -v git-lfs &> /dev/null; then
    echo "LFS status: ✅ Installed"
    echo "LFS files: $(git lfs ls-files | wc -l)"
    if [ "$(git lfs ls-files | wc -l)" -gt 0 ]; then
        echo "LFS storage used: $(git lfs ls-files -s | awk '{sum+=$2} END {printf "%.2f MB", sum/1024/1024}')"
        echo ""
        echo "Top 5 largest LFS files:"
        git lfs ls-files -s | sort -k2 -nr | head -5 | while read -r file size _; do
            echo "  $(numfmt --to=iec $size) - $file"
        done
    fi
else
    echo "LFS status: ❌ Not installed"
fi
echo ""

# Performance metrics
echo "⚡ PERFORMANCE METRICS"
echo "---------------------"
echo "Performance configs:"
git config --get-regexp "(core\.preloadindex|core\.fscache|gc\.auto|pack\.threads)" | while read -r config; do
    echo "  $config"
done
echo ""

# Recent activity
echo "📈 RECENT ACTIVITY"
echo "-----------------"
echo "Last commit: $(git log -1 --pretty=format:'%h - %an, %ar : %s')"
echo "Commits today: $(git log --since="today" --oneline | wc -l)"
echo "Commits this week: $(git log --since="1 week ago" --oneline | wc -l)"
echo ""

# Branch information
echo "🌿 BRANCH INFORMATION"
echo "--------------------"
echo "Current branch: $(git branch --show-current)"
echo "Total branches: $(git branch -r | wc -l)"
echo "Uncommitted changes: $(git status --porcelain | wc -l)"
echo ""

# Health check
echo "🏥 HEALTH CHECK"
echo "--------------"
# Check for large uncommitted files
large_uncommitted=$(git status --porcelain | cut -c4- | xargs -I {} find {} -size +10M 2>/dev/null | wc -l)
if [ "$large_uncommitted" -gt 0 ]; then
    echo "⚠️  Large uncommitted files detected: $large_uncommitted"
else
    echo "✅ No large uncommitted files"
fi

# Check repository integrity
if git fsck --quiet 2>/dev/null; then
    echo "✅ Repository integrity: OK"
else
    echo "❌ Repository integrity: Issues detected"
fi

echo ""
echo "📊 Dashboard complete!"
EOF

chmod +x tools/scripts/repo-dashboard.sh

# Test del dashboard
echo "📊 Testing monitoring dashboard:"
./tools/scripts/repo-dashboard.sh

echo "✅ Monitoring dashboard created and tested"
```

## 🎯 Risultati e Best Practices

### Configurazione Finale Ottimizzata

```bash
echo "📋 Final optimized configuration summary:"

echo "Git LFS tracked extensions:"
git lfs track | grep -v "Listing tracked patterns" | head -10

echo -e "\nPerformance configurations:"
git config --get-regexp "(core|lfs|pack|gc)\." | head -10

echo -e "\nRepository health:"
./tools/scripts/repo-dashboard.sh | tail -15
```

### Best Practices Implementate

1. **Git LFS per File Grandi**:
   - File multimediali automaticamente tracciati
   - Lock per file di dati critici
   - Configurazione ottimizzata per trasferimenti paralleli

2. **Gestione Performance**:
   - Cache e preload abilitati
   - Garbage collection ottimizzata
   - Buffer HTTP aumentato per file grandi

3. **Organizzazione Intelligente**:
   - .gitattributes dettagliato per tutti i tipi di file
   - .gitignore ottimizzato per escludere file temporanei
   - Struttura directory logica e scalabile

4. **Monitoraggio Continuo**:
   - Script di verifica automatica
   - Dashboard delle metriche
   - Controlli pre-commit per file grandi

## 💡 Lezioni Apprese

### Configurazioni Critiche
- **Git LFS è essenziale** per repository con file >50MB
- **Le configurazioni di performance** possono ridurre significativamente i tempi di operazione
- **Un .gitattributes ben configurato** previene molti problemi

### Tool e Script Utili
- **Script di monitoraggio** aiutano a mantenere la salute del repository
- **Hook pre-commit** prevengono commit di file troppo grandi
- **Dashboard delle metriche** forniscono visibilità sullo stato del progetto

## 🚀 Applicazioni Avanzate

Questo setup è ideale per:

1. **Progetti Game Development**: Assets 3D, texture, audio
2. **Applicazioni Multimediali**: Video, immagini ad alta risoluzione
3. **Data Science**: Dataset, modelli ML, notebook con output
4. **Design e Creative**: File Photoshop, Illustrator, video demo
5. **Enterprise Software**: Binari, librerie, documentazione estesa

---

> **Nota**: Questa configurazione rappresenta best practices enterprise per gestione di repository con file grandi. Adatta le configurazioni alle specifiche esigenze del tuo progetto.
