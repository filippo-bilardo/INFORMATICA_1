# Gestione Avanzata File Tracking con Git Hooks e Automazione

⭐⭐⭐⭐⭐ **Livello**: Esperto  
🕒 **Tempo**: 45-60 minuti  
🎯 **Obiettivo**: Implementare un sistema completo di tracking intelligente con automazione e validazione

## 📋 Scenario

Sei il lead developer di un team che lavora su un progetto open source con centinaia di contributors. Devi implementare un sistema intelligente che:
- Gestisca automaticamente il tracking dei file
- Validi la conformità dei .gitignore
- Monitorizzi le violazioni di sicurezza
- Ottimizzi le performance del repository

## 🏗️ Architettura Sistema di Tracking

```
smart-tracking-system/
├── .gitignore                    # Configurazione principale
├── .gitignore-templates/         # Template modulari
├── tracking-rules/               # Regole personalizzate
├── hooks/                       # Git hooks avanzati
├── scripts/                     # Automazione
├── monitoring/                  # Sistema monitoraggio
└── validation/                  # Suite di test
```

## 🎯 Implementazione Completa

### Fase 1: Sistema di Template Modulari

```bash
# Setup progetto
mkdir smart-tracking-system && cd smart-tracking-system
git init

# Struttura per template modulari
mkdir -p .gitignore-templates/{base,languages,frameworks,tools,security}

# Template base sicurezza
cat > .gitignore-templates/security/credentials.gitignore << 'EOF'
# ====================================
# 🔒 SICUREZZA E CREDENTIALS
# ====================================

# Chiavi private e certificati
*.key
*.pem
*.p12
*.pfx
*.crt
*.der
*.cer
*.csr
*.keystore
*.jks
*.ppk

# File di configurazione sensibili
.env
.env.*
!.env.example
!.env.template
.secrets
secrets.json
credentials.json
service-account*.json

# Backup database sensibili
*.sql.gz
*.dump
database-backup*.sql

# Configurazioni AWS/Cloud
.aws/credentials
.aws/config
.azure/
.gcp/
terraform.tfstate
terraform.tfstate.backup

# Licenze software
license.key
*.lic
activation.key
EOF

# Template per performance
cat > .gitignore-templates/base/performance.gitignore << 'EOF'
# ====================================
# 🚀 PERFORMANCE E OTTIMIZZAZIONE
# ====================================

# File grandi (>100MB)
*.iso
*.dmg
*.pkg
*.exe
*.msi
*.zip
*.tar.gz
*.7z
*.rar

# Cache e file temporanei
cache/
.cache/
tmp/
temp/
*.tmp
*.temp
*.bak
*.backup

# Database locali
*.sqlite
*.sqlite3
*.db
*.rdb

# File di sistema
.DS_Store
Thumbs.db
*.swp
*.swo
*~

# Logs voluminosi
*.log
logs/
*.pid
*.seed
*.pid.lock
EOF

# Template per sviluppo
cat > .gitignore-templates/tools/development.gitignore << 'EOF'
# ====================================
# 🛠️ STRUMENTI DI SVILUPPO
# ====================================

# IDE e editor
.vscode/
!.vscode/settings.json
!.vscode/tasks.json
!.vscode/launch.json
!.vscode/extensions.json
.idea/
*.sublime-project
*.sublime-workspace

# Dipendenze
node_modules/
vendor/
bower_components/
.bundle/

# Build artifacts
build/
dist/
out/
target/
bin/
obj/

# Testing
coverage/
.nyc_output/
test-results/
.pytest_cache/
EOF

echo "Template modulari creati!"
```

### Fase 2: Generatore Intelligente .gitignore

```bash
# Script per generare .gitignore personalizzato
cat > scripts/generate-gitignore.sh << 'EOF'
#!/bin/bash

# ====================================
# GENERATORE INTELLIGENTE .GITIGNORE
# ====================================

set -e

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_info() { echo -e "${BLUE}ℹ️  $1${NC}"; }
print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }

# Rilevamento automatico tipo progetto
detect_project_type() {
    local project_types=()
    
    # Rileva linguaggi
    [ -f "package.json" ] && project_types+=("node")
    [ -f "requirements.txt" ] && project_types+=("python")
    [ -f "pom.xml" ] && project_types+=("java")
    [ -f "Cargo.toml" ] && project_types+=("rust")
    [ -f "go.mod" ] && project_types+=("go")
    
    # Rileva framework
    [ -f "package.json" ] && grep -q "react" package.json && project_types+=("react")
    [ -f "package.json" ] && grep -q "vue" package.json && project_types+=("vue")
    [ -f "package.json" ] && grep -q "angular" package.json && project_types+=("angular")
    [ -f "composer.json" ] && project_types+=("php")
    
    # Rileva tools
    [ -f "Dockerfile" ] && project_types+=("docker")
    [ -f "docker-compose.yml" ] && project_types+=("docker")
    [ -d ".git" ] && project_types+=("git")
    [ -f "terraform.tf" ] && project_types+=("terraform")
    
    echo "${project_types[@]}"
}

# Generazione .gitignore basata su tipo progetto
generate_gitignore() {
    local project_types=("$@")
    local output_file=".gitignore.generated"
    
    print_info "Generazione .gitignore per: ${project_types[*]}"
    
    # Header del file
    cat > "$output_file" << HEADER
# ====================================
# GITIGNORE GENERATO AUTOMATICAMENTE
# ====================================
# Generato: $(date)
# Tipi progetto: ${project_types[*]}
# Versione: 1.0
# 
# 🚨 Questo file è stato generato automaticamente
# 🔧 Per modifiche personalizzate, edita la sezione CUSTOM
# 📝 Rigenera con: ./scripts/generate-gitignore.sh

HEADER

    # Includi sempre sicurezza e performance
    echo "# ==== SICUREZZA (sempre inclusa) ====" >> "$output_file"
    cat .gitignore-templates/security/credentials.gitignore >> "$output_file"
    echo "" >> "$output_file"
    
    echo "# ==== PERFORMANCE (sempre inclusa) ====" >> "$output_file"
    cat .gitignore-templates/base/performance.gitignore >> "$output_file"
    echo "" >> "$output_file"
    
    echo "# ==== SVILUPPO (sempre incluso) ====" >> "$output_file"
    cat .gitignore-templates/tools/development.gitignore >> "$output_file"
    echo "" >> "$output_file"
    
    # Includi template specifici per linguaggio/framework
    for type in "${project_types[@]}"; do
        local template_file=""
        
        case "$type" in
            "node"|"javascript"|"typescript")
                template_file=".gitignore-templates/languages/node.gitignore"
                ;;
            "python")
                template_file=".gitignore-templates/languages/python.gitignore"
                ;;
            "java")
                template_file=".gitignore-templates/languages/java.gitignore"
                ;;
            "react")
                template_file=".gitignore-templates/frameworks/react.gitignore"
                ;;
            "docker")
                template_file=".gitignore-templates/tools/docker.gitignore"
                ;;
        esac
        
        if [ -n "$template_file" ] && [ -f "$template_file" ]; then
            echo "# ==== $(echo $type | tr '[:lower:]' '[:upper:]') ====" >> "$output_file"
            cat "$template_file" >> "$output_file"
            echo "" >> "$output_file"
        fi
    done
    
    # Sezione custom
    cat >> "$output_file" << 'CUSTOM'
# ====================================
# 🎨 CONFIGURAZIONI CUSTOM
# ====================================
# Aggiungi qui le tue regole personalizzate

# File specifici del progetto
# /my-custom-folder/

# Configurazioni locali
# local-config.*

# ====================================
# 📝 FINE CONFIGURAZIONI
# ====================================
CUSTOM
    
    print_success "File $output_file generato"
}

# Funzione per merge intelligente
merge_with_existing() {
    if [ -f ".gitignore" ]; then
        print_info "Backup .gitignore esistente..."
        cp ".gitignore" ".gitignore.backup.$(date +%Y%m%d_%H%M%S)"
        
        # Estrai sezioni custom esistenti
        if grep -q "CUSTOM" ".gitignore"; then
            print_info "Preservo configurazioni custom..."
            sed -n '/# CUSTOM/,$p' ".gitignore" > ".custom_rules.tmp"
            
            # Sostituisci sezione custom nel nuovo file
            sed -i '/# CONFIGURAZIONI CUSTOM/,$d' ".gitignore.generated"
            cat ".custom_rules.tmp" >> ".gitignore.generated"
            rm ".custom_rules.tmp"
        fi
    fi
    
    mv ".gitignore.generated" ".gitignore"
    print_success "Nuovo .gitignore installato"
}

# Validazione del .gitignore generato
validate_gitignore() {
    print_info "Validazione .gitignore..."
    
    local errors=0
    
    # Test pattern comuni
    test_patterns=(
        "node_modules/test"
        ".env.test"
        "*.log"
        "build/test"
        ".DS_Store"
    )
    
    for pattern in "${test_patterns[@]}"; do
        if git check-ignore "$pattern" >/dev/null 2>&1; then
            print_success "Pattern '$pattern' correttamente ignorato"
        else
            print_warning "Pattern '$pattern' potrebbe non essere ignorato"
            ((errors++))
        fi
    done
    
    if [ $errors -eq 0 ]; then
        print_success "Validazione completata senza errori"
    else
        print_warning "Validazione completata con $errors warning"
    fi
}

# Menu interattivo
interactive_mode() {
    echo -e "\n🎯 GENERATORE GITIGNORE INTERATTIVO"
    echo "=================================="
    
    echo -e "\nSeleziona componenti da includere:"
    echo "1) Node.js/JavaScript"
    echo "2) Python"
    echo "3) Java"
    echo "4) React"
    echo "5) Docker"
    echo "6) Auto-detect"
    echo "7) Tutti i template"
    
    read -p "Scelta (1-7): " choice
    
    case $choice in
        1) generate_gitignore "node" ;;
        2) generate_gitignore "python" ;;
        3) generate_gitignore "java" ;;
        4) generate_gitignore "react" "node" ;;
        5) generate_gitignore "docker" ;;
        6) 
            detected=($(detect_project_type))
            if [ ${#detected[@]} -eq 0 ]; then
                print_warning "Nessun tipo progetto rilevato, uso template base"
                generate_gitignore "base"
            else
                print_info "Rilevati: ${detected[*]}"
                generate_gitignore "${detected[@]}"
            fi
            ;;
        7) generate_gitignore "node" "python" "java" "react" "docker" ;;
        *) print_error "Scelta non valida" && exit 1 ;;
    esac
}

# Main
main() {
    if [ "$1" = "--interactive" ] || [ "$1" = "-i" ]; then
        interactive_mode
    elif [ "$1" = "--auto" ] || [ "$1" = "-a" ]; then
        detected=($(detect_project_type))
        if [ ${#detected[@]} -eq 0 ]; then
            print_warning "Auto-detect: nessun tipo rilevato, uso template base"
            generate_gitignore "base"
        else
            generate_gitignore "${detected[@]}"
        fi
    else
        print_info "Uso: $0 [--interactive|-i] [--auto|-a]"
        print_info "Senza parametri: esegue auto-detect"
        detected=($(detect_project_type))
        generate_gitignore "${detected[@]}"
    fi
    
    merge_with_existing
    validate_gitignore
    
    print_success "Generazione .gitignore completata!"
    print_info "📁 Backup precedente disponibile (se esistente)"
    print_info "🔍 Esegui './scripts/validate-tracking.sh' per verifica completa"
}

main "$@"
EOF

chmod +x scripts/generate-gitignore.sh

echo "Generatore intelligente creato!"
```

### Fase 3: Sistema di Validazione Avanzato

```bash
# Script di validazione completa
cat > scripts/validate-tracking.sh << 'EOF'
#!/bin/bash

# ====================================
# VALIDATORE AVANZATO FILE TRACKING
# ====================================

set -e

# Configurazione
REPORT_FILE="tracking-report.md"
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

# Colori
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_header() {
    echo -e "\n${BLUE}=====================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}=====================================${NC}\n"
}

print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }

# Inizio report
cat > "$REPORT_FILE" << 'REPORT_START'
# 📊 Report Validazione File Tracking

**Data generazione**: $(date)  
**Repository**: $(basename $(pwd))  
**Branch**: $(git branch --show-current 2>/dev/null || echo "N/A")

---

## 🎯 Sommario Esecutivo

REPORT_START

# Analisi dimensioni repository
analyze_repository_size() {
    print_header "📊 ANALISI DIMENSIONI REPOSITORY"
    
    local total_files=$(find . -type f | wc -l)
    local tracked_files=$(git ls-files | wc -l)
    local ignored_files=$((total_files - tracked_files))
    local repo_size=$(du -sh . | cut -f1)
    local git_size=$(du -sh .git | cut -f1)
    
    echo "📁 **File totali**: $total_files" >> "$REPORT_FILE"
    echo "📋 **File tracciati**: $tracked_files" >> "$REPORT_FILE"
    echo "🚫 **File ignorati**: $ignored_files" >> "$REPORT_FILE"
    echo "💾 **Dimensione repository**: $repo_size" >> "$REPORT_FILE"
    echo "🗂️  **Dimensione .git**: $git_size" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    print_success "File totali: $total_files"
    print_success "File tracciati: $tracked_files"
    print_success "File ignorati: $ignored_files"
    
    # Calcola percentuale efficienza
    local efficiency=$((ignored_files * 100 / total_files))
    if [ $efficiency -gt 50 ]; then
        print_success "Efficienza tracking: $efficiency% (Ottima)"
    elif [ $efficiency -gt 30 ]; then
        print_warning "Efficienza tracking: $efficiency% (Buona)"
    else
        print_warning "Efficienza tracking: $efficiency% (Da migliorare)"
    fi
}

# Analisi file grandi
analyze_large_files() {
    print_header "🐘 ANALISI FILE GRANDI"
    
    echo "## 🐘 File Grandi (>1MB)" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # File tracciati grandi
    local large_tracked_found=false
    git ls-files | while read file; do
        if [ -f "$file" ]; then
            local size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo "0")
            if [ "$size" -gt 1048576 ]; then  # 1MB
                local size_mb=$((size / 1048576))
                echo "❌ **$file**: ${size_mb}MB (TRACCIATO)" >> "$REPORT_FILE"
                print_error "File grande tracciato: $file (${size_mb}MB)"
                large_tracked_found=true
            fi
        fi
    done
    
    if [ "$large_tracked_found" != true ]; then
        echo "✅ Nessun file grande inappropriatamente tracciato" >> "$REPORT_FILE"
        print_success "Nessun file grande inappropriatamente tracciato"
    fi
    
    echo "" >> "$REPORT_FILE"
}

# Analisi file sensibili
analyze_sensitive_files() {
    print_header "🔒 ANALISI SICUREZZA"
    
    echo "## 🔒 Controllo File Sensibili" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Pattern sensibili
    local sensitive_patterns=(
        "password"
        "secret"
        "token"
        "api.key"
        "private.key"
        "credential"
    )
    
    local sensitive_extensions=(
        ".key"
        ".pem"
        ".p12"
        ".pfx"
        ".env"
    )
    
    local security_issues=0
    
    # Controllo contenuti
    for pattern in "${sensitive_patterns[@]}"; do
        if git grep -i "$pattern" >/dev/null 2>&1; then
            echo "⚠️ **Pattern sospetto**: $pattern" >> "$REPORT_FILE"
            git grep -i "$pattern" --name-only | head -3 | while read file; do
                echo "   - $file" >> "$REPORT_FILE"
            done
            print_warning "Pattern sospetto trovato: $pattern"
            ((security_issues++))
        fi
    done
    
    # Controllo estensioni
    for ext in "${sensitive_extensions[@]}"; do
        if git ls-files | grep -E "\$ext$" >/dev/null 2>&1; then
            echo "❌ **File sensibile tracciato**: $ext" >> "$REPORT_FILE"
            git ls-files | grep -E "\$ext$" | while read file; do
                echo "   - $file" >> "$REPORT_FILE"
            done
            print_error "File sensibile tracciato: $ext"
            ((security_issues++))
        fi
    done
    
    if [ $security_issues -eq 0 ]; then
        echo "✅ Nessun problema di sicurezza rilevato" >> "$REPORT_FILE"
        print_success "Nessun problema di sicurezza rilevato"
    else
        echo "⚠️ **$security_issues problemi di sicurezza rilevati**" >> "$REPORT_FILE"
        print_error "$security_issues problemi di sicurezza rilevati"
    fi
    
    echo "" >> "$REPORT_FILE"
}

# Analisi performance .gitignore
analyze_gitignore_performance() {
    print_header "⚡ ANALISI PERFORMANCE .GITIGNORE"
    
    echo "## ⚡ Performance .gitignore" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    if [ ! -f ".gitignore" ]; then
        echo "❌ **Nessun file .gitignore trovato**" >> "$REPORT_FILE"
        print_error "Nessun file .gitignore trovato"
        return
    fi
    
    local lines=$(wc -l < .gitignore)
    local patterns=$(grep -v '^#' .gitignore | grep -v '^$' | wc -l)
    
    echo "📏 **Righe totali**: $lines" >> "$REPORT_FILE"
    echo "🎯 **Pattern attivi**: $patterns" >> "$REPORT_FILE"
    
    # Test performance pattern
    local start_time=$(date +%s%N)
    git status >/dev/null 2>&1
    local end_time=$(date +%s%N)
    local duration=$(((end_time - start_time) / 1000000))  # ms
    
    echo "⏱️ **Tempo git status**: ${duration}ms" >> "$REPORT_FILE"
    
    if [ $duration -lt 100 ]; then
        print_success "Performance .gitignore: Eccellente (${duration}ms)"
    elif [ $duration -lt 500 ]; then
        print_success "Performance .gitignore: Buona (${duration}ms)"
    else
        print_warning "Performance .gitignore: Da ottimizzare (${duration}ms)"
    fi
    
    echo "" >> "$REPORT_FILE"
}

# Verifica copertura .gitignore
verify_gitignore_coverage() {
    print_header "🎯 VERIFICA COPERTURA .GITIGNORE"
    
    echo "## 🎯 Copertura Pattern Standard" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Pattern che dovrebbero essere coperti
    local standard_patterns=(
        "node_modules/"
        "*.log"
        ".env"
        "build/"
        "dist/"
        "coverage/"
        ".DS_Store"
        "Thumbs.db"
        "*.tmp"
        "*.swp"
    )
    
    local missing_patterns=()
    
    for pattern in "${standard_patterns[@]}"; do
        if grep -q "$pattern" .gitignore 2>/dev/null; then
            echo "✅ $pattern" >> "$REPORT_FILE"
            print_success "Pattern coperto: $pattern"
        else
            echo "❌ $pattern" >> "$REPORT_FILE"
            print_warning "Pattern mancante: $pattern"
            missing_patterns+=("$pattern")
        fi
    done
    
    if [ ${#missing_patterns[@]} -gt 0 ]; then
        echo "" >> "$REPORT_FILE"
        echo "### 🔧 Pattern Consigliati da Aggiungere" >> "$REPORT_FILE"
        echo "" >> "$REPORT_FILE"
        echo '```gitignore' >> "$REPORT_FILE"
        for pattern in "${missing_patterns[@]}"; do
            echo "$pattern" >> "$REPORT_FILE"
        done
        echo '```' >> "$REPORT_FILE"
    fi
    
    echo "" >> "$REPORT_FILE"
}

# Genera raccomandazioni
generate_recommendations() {
    print_header "💡 GENERAZIONE RACCOMANDAZIONI"
    
    echo "## 💡 Raccomandazioni" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Raccomandazioni basate su analisi
    local recommendations=()
    
    # Controlla se ci sono file grandi
    if git ls-files | xargs ls -la 2>/dev/null | awk '$5 > 1048576 {print}' | grep -q .; then
        recommendations+=("Configura Git LFS per file grandi")
    fi
    
    # Controlla struttura repository
    if [ -d "node_modules" ] && ! grep -q "node_modules" .gitignore 2>/dev/null; then
        recommendations+=("Aggiungi node_modules/ a .gitignore")
    fi
    
    if [ -f ".env" ] && ! grep -q ".env" .gitignore 2>/dev/null; then
        recommendations+=("Aggiungi .env a .gitignore per sicurezza")
    fi
    
    # Verifica hook Git
    if [ ! -f ".git/hooks/pre-commit" ]; then
        recommendations+=("Installa pre-commit hook per validazione")
    fi
    
    # Output raccomandazioni
    if [ ${#recommendations[@]} -gt 0 ]; then
        for rec in "${recommendations[@]}"; do
            echo "- 🎯 $rec" >> "$REPORT_FILE"
            print_warning "Raccomandazione: $rec"
        done
    else
        echo "✅ Configurazione ottimale, nessuna raccomandazione" >> "$REPORT_FILE"
        print_success "Configurazione ottimale"
    fi
    
    echo "" >> "$REPORT_FILE"
}

# Report finale
finalize_report() {
    echo "---" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    echo "**Report generato da**: \`validate-tracking.sh\`  " >> "$REPORT_FILE"
    echo "**Repository**: $(git remote get-url origin 2>/dev/null || echo "Local repository")  " >> "$REPORT_FILE"
    echo "**Ultimo commit**: $(git log -1 --oneline 2>/dev/null || echo "N/A")  " >> "$REPORT_FILE"
    
    print_success "Report salvato in: $REPORT_FILE"
    
    # Apri report se possibile
    if command -v code >/dev/null 2>&1; then
        code "$REPORT_FILE"
    elif command -v open >/dev/null 2>&1; then
        open "$REPORT_FILE"
    fi
}

# Main execution
main() {
    print_header "🔍 VALIDAZIONE COMPLETA FILE TRACKING"
    
    analyze_repository_size
    analyze_large_files
    analyze_sensitive_files
    analyze_gitignore_performance
    verify_gitignore_coverage
    generate_recommendations
    finalize_report
    
    print_header "✨ VALIDAZIONE COMPLETATA"
    echo "📊 Report dettagliato disponibile in: $REPORT_FILE"
}

main "$@"
EOF

chmod +x scripts/validate-tracking.sh

echo "Sistema di validazione avanzato creato!"
```

### Fase 4: Git Hooks Intelligenti

```bash
# Directory per hooks
mkdir -p hooks/templates

# Pre-commit hook avanzato
cat > hooks/templates/pre-commit << 'EOF'
#!/bin/bash

# ====================================
# PRE-COMMIT HOOK AVANZATO
# ====================================

set -e

# Configurazione
MAX_FILE_SIZE=10485760  # 10MB
SECURITY_SCAN=true
PERFORMANCE_CHECK=true

# Colori
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }

echo "🔍 Pre-commit validation..."

# Controllo file grandi
check_large_files() {
    local large_files_found=false
    
    git diff --cached --name-only | while read file; do
        if [ -f "$file" ]; then
            local size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo "0")
            if [ "$size" -gt "$MAX_FILE_SIZE" ]; then
                local size_mb=$((size / 1048576))
                print_error "File troppo grande: $file (${size_mb}MB)"
                large_files_found=true
            fi
        fi
    done
    
    if [ "$large_files_found" = true ]; then
        print_error "File grandi rilevati. Usa Git LFS per file >10MB"
        echo "💡 Configura Git LFS: git lfs track '*.{ext}'"
        return 1
    fi
    
    return 0
}

# Controllo file sensibili
check_sensitive_files() {
    local sensitive_patterns=(
        "password"
        "secret"
        "token"
        "api.key"
        "private"
    )
    
    local sensitive_extensions=(
        ".key"
        ".pem"
        ".env"
        ".p12"
    )
    
    local issues_found=false
    
    # Controllo estensioni
    for ext in "${sensitive_extensions[@]}"; do
        if git diff --cached --name-only | grep -E "\$ext$" >/dev/null; then
            print_error "File sensibile in staging: *$ext"
            issues_found=true
        fi
    done
    
    # Controllo contenuti
    for pattern in "${sensitive_patterns[@]}"; do
        if git diff --cached | grep -i "$pattern" >/dev/null; then
            print_warning "Pattern sensibile rilevato: $pattern"
            echo "💡 Verifica che non siano esposti dati sensibili"
        fi
    done
    
    if [ "$issues_found" = true ]; then
        print_error "File sensibili rilevati in staging area"
        print_error "Aggiungi a .gitignore o usa git rm --cached"
        return 1
    fi
    
    return 0
}

# Controllo conformità .gitignore
check_gitignore_compliance() {
    local violations_found=false
    
    # File che dovrebbero essere ignorati ma sono tracciati
    local should_ignore=(
        "node_modules"
        ".DS_Store"
        "Thumbs.db"
        "*.log"
        ".env"
    )
    
    for pattern in "${should_ignore[@]}"; do
        if git ls-files | grep -E "$pattern" >/dev/null 2>&1; then
            print_warning "File che dovrebbe essere ignorato: $pattern"
            violations_found=true
        fi
    done
    
    if [ "$violations_found" = true ]; then
        print_warning "Alcune violazioni .gitignore rilevate"
        echo "💡 Esegui './scripts/validate-tracking.sh' per analisi completa"
    fi
    
    return 0
}

# Performance check
check_performance() {
    local staged_files=$(git diff --cached --name-only | wc -l)
    
    if [ "$staged_files" -gt 100 ]; then
        print_warning "Molti file in staging ($staged_files)"
        echo "💡 Considera commit più piccoli e atomici"
    fi
    
    # Test velocità git status
    local start_time=$(date +%s%N)
    git status >/dev/null 2>&1
    local end_time=$(date +%s%N)
    local duration=$(((end_time - start_time) / 1000000))
    
    if [ "$duration" -gt 1000 ]; then  # 1 secondo
        print_warning "Git status lento (${duration}ms)"
        echo "💡 Repository potrebbe necessitare ottimizzazione"
    fi
}

# Esecuzione controlli
main() {
    local errors=0
    
    # Controlli obbligatori
    if ! check_large_files; then
        ((errors++))
    fi
    
    if [ "$SECURITY_SCAN" = true ] && ! check_sensitive_files; then
        ((errors++))
    fi
    
    # Controlli informativi
    check_gitignore_compliance
    
    if [ "$PERFORMANCE_CHECK" = true ]; then
        check_performance
    fi
    
    if [ $errors -gt 0 ]; then
        print_error "Pre-commit validation failed with $errors errors"
        echo ""
        echo "🔧 Azioni suggerite:"
        echo "- Rimuovi file grandi: git rm --cached <file>"
        echo "- Aggiungi a .gitignore: echo '<pattern>' >> .gitignore"
        echo "- Configura Git LFS: git lfs track '<pattern>'"
        echo ""
        exit 1
    fi
    
    print_success "Pre-commit validation passed"
    exit 0
}

main "$@"
EOF

# Post-commit hook per statistiche
cat > hooks/templates/post-commit << 'EOF'
#!/bin/bash

# ====================================
# POST-COMMIT HOOK - STATISTICHE
# ====================================

# Aggiorna statistiche repository
update_stats() {
    local stats_file=".git-stats.json"
    local commit_hash=$(git rev-parse HEAD)
    local commit_date=$(git log -1 --format="%ci")
    local files_changed=$(git diff --name-only HEAD~1 2>/dev/null | wc -l || echo "0")
    local repo_size=$(du -sk . | cut -f1)
    
    # Crea/aggiorna file statistiche
    cat > "$stats_file" << STATS
{
  "last_commit": "$commit_hash",
  "last_commit_date": "$commit_date",
  "files_changed": $files_changed,
  "repository_size_kb": $repo_size,
  "tracked_files": $(git ls-files | wc -l),
  "total_commits": $(git rev-list --all --count),
  "updated": "$(date -Iseconds)"
}
STATS
    
    echo "📊 Statistiche repository aggiornate"
}

# Controllo salute repository
health_check() {
    local warnings=0
    
    # Controlla dimensioni .git
    local git_size=$(du -sk .git | cut -f1)
    local repo_size=$(du -sk . | cut -f1)
    local git_ratio=$((git_size * 100 / repo_size))
    
    if [ $git_ratio -gt 50 ]; then
        echo "⚠️  Directory .git molto grande ($git_ratio% del repository)"
        echo "💡 Considera 'git gc' o 'git lfs migrate'"
        ((warnings++))
    fi
    
    # Controlla file non tracciati
    local untracked=$(git ls-files --others --exclude-standard | wc -l)
    if [ $untracked -gt 50 ]; then
        echo "⚠️  Molti file non tracciati ($untracked)"
        echo "💡 Verifica .gitignore configuration"
        ((warnings++))
    fi
    
    if [ $warnings -eq 0 ]; then
        echo "✅ Repository health check OK"
    fi
}

update_stats
health_check
EOF

# Script di installazione hooks
cat > scripts/install-hooks.sh << 'EOF'
#!/bin/bash

# ====================================
# INSTALLATORE GIT HOOKS
# ====================================

set -e

echo "🔧 Installazione Git hooks..."

# Copia hooks
for hook in hooks/templates/*; do
    if [ -f "$hook" ]; then
        hook_name=$(basename "$hook")
        cp "$hook" ".git/hooks/$hook_name"
        chmod +x ".git/hooks/$hook_name"
        echo "✅ Hook installato: $hook_name"
    fi
done

# Configura hooks personalizzabili
git config core.hooksPath .git/hooks

echo "✅ Git hooks installati e configurati!"
echo "💡 Modifica hooks in .git/hooks/ per personalizzazioni"
EOF

chmod +x scripts/install-hooks.sh
chmod +x hooks/templates/*

echo "Git hooks intelligenti creati!"
```

### Fase 5: Sistema di Monitoraggio

```bash
# Script di monitoraggio continuo
cat > scripts/monitor-tracking.sh << 'EOF'
#!/bin/bash

# ====================================
# MONITORAGGIO CONTINUO TRACKING
# ====================================

set -e

MONITOR_DIR=".tracking-monitor"
LOG_FILE="$MONITOR_DIR/tracking.log"
ALERT_FILE="$MONITOR_DIR/alerts.log"

# Setup monitoraggio
setup_monitoring() {
    mkdir -p "$MONITOR_DIR"
    
    # Configura baseline
    if [ ! -f "$MONITOR_DIR/baseline.json" ]; then
        cat > "$MONITOR_DIR/baseline.json" << BASELINE
{
  "max_file_size": 10485760,
  "max_repo_size": 104857600,
  "max_untracked_files": 50,
  "security_patterns": [
    "password",
    "secret",
    "token",
    "api.key"
  ],
  "performance_threshold_ms": 1000
}
BASELINE
        echo "📋 Baseline configurazione creata"
    fi
}

# Funzione di logging
log_event() {
    local level="$1"
    local message="$2"
    local timestamp=$(date -Iseconds)
    
    echo "[$timestamp] [$level] $message" >> "$LOG_FILE"
    
    if [ "$level" = "ALERT" ]; then
        echo "[$timestamp] $message" >> "$ALERT_FILE"
        echo "🚨 ALERT: $message"
    fi
}

# Monitoraggio dimensioni
monitor_size() {
    local repo_size=$(du -sk . | cut -f1)
    local git_size=$(du -sk .git | cut -f1)
    local max_size=$(jq -r '.max_repo_size' "$MONITOR_DIR/baseline.json")
    
    if [ $repo_size -gt $((max_size / 1024)) ]; then
        log_event "ALERT" "Repository size exceeded: ${repo_size}KB > ${max_size}KB"
    fi
    
    log_event "INFO" "Repository size: ${repo_size}KB, .git size: ${git_size}KB"
}

# Monitoraggio sicurezza
monitor_security() {
    local patterns=($(jq -r '.security_patterns[]' "$MONITOR_DIR/baseline.json"))
    
    for pattern in "${patterns[@]}"; do
        if git grep -i "$pattern" >/dev/null 2>&1; then
            local files=$(git grep -i "$pattern" --name-only | wc -l)
            log_event "ALERT" "Security pattern '$pattern' found in $files files"
        fi
    done
    
    # File sensibili tracciati
    local sensitive_tracked=$(git ls-files | grep -E '\.(key|pem|env)$' | wc -l)
    if [ $sensitive_tracked -gt 0 ]; then
        log_event "ALERT" "$sensitive_tracked sensitive files tracked"
    fi
}

# Monitoraggio performance
monitor_performance() {
    local start_time=$(date +%s%N)
    git status >/dev/null 2>&1
    local end_time=$(date +%s%N)
    local duration=$(((end_time - start_time) / 1000000))
    
    local threshold=$(jq -r '.performance_threshold_ms' "$MONITOR_DIR/baseline.json")
    
    if [ $duration -gt $threshold ]; then
        log_event "ALERT" "Performance degraded: git status took ${duration}ms"
    fi
    
    log_event "INFO" "Git status performance: ${duration}ms"
}

# Report giornaliero
generate_daily_report() {
    local report_file="$MONITOR_DIR/daily-report-$(date +%Y%m%d).md"
    
    cat > "$report_file" << REPORT
# 📊 Daily Tracking Report - $(date +%Y-%m-%d)

## 📈 Statistiche

- **Repository size**: $(du -sh . | cut -f1)
- **Tracked files**: $(git ls-files | wc -l)
- **Untracked files**: $(git ls-files --others --exclude-standard | wc -l)
- **Git directory size**: $(du -sh .git | cut -f1)

## 🚨 Alerts Today

$(grep "$(date +%Y-%m-%d)" "$ALERT_FILE" 2>/dev/null || echo "No alerts today")

## 📋 Activity Log

$(tail -20 "$LOG_FILE" | grep "$(date +%Y-%m-%d)" || echo "No activity logged")

---
*Report generated by tracking monitor*
REPORT

    echo "📊 Daily report: $report_file"
}

# Modalità daemon
daemon_mode() {
    echo "🔄 Starting tracking monitor daemon..."
    
    while true; do
        monitor_size
        monitor_security
        monitor_performance
        
        # Report giornaliero alle 00:00
        if [ "$(date +%H%M)" = "0000" ]; then
            generate_daily_report
        fi
        
        sleep 3600  # Check ogni ora
    done
}

# Main
main() {
    setup_monitoring
    
    case "${1:-once}" in
        "daemon")
            daemon_mode
            ;;
        "report")
            generate_daily_report
            ;;
        "once"|*)
            echo "🔍 Single monitoring check..."
            monitor_size
            monitor_security
            monitor_performance
            echo "✅ Monitoring check completed"
            ;;
    esac
}

main "$@"
EOF

chmod +x scripts/monitor-tracking.sh

echo "Sistema di monitoraggio creato!"
```

### Fase 6: Testing e Validazione Finale

```bash
# Crea template necessari per il generatore
mkdir -p .gitignore-templates/languages

cat > .gitignore-templates/languages/node.gitignore << 'EOF'
# Node.js dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
.npm
.yarn/cache

# Build outputs
build/
dist/
lib/

# Environment files
.env
.env.local
.env.development
.env.test
.env.production
EOF

# Test del sistema completo
echo -e "\n🧪 Testing sistema completo..."

# Test 1: Generazione .gitignore
echo "📝 Test 1: Generazione .gitignore automatica"
./scripts/generate-gitignore.sh --auto

# Test 2: Validazione
echo -e "\n📊 Test 2: Validazione tracking"
./scripts/validate-tracking.sh

# Test 3: Installazione hooks
echo -e "\n🔧 Test 3: Installazione hooks"
./scripts/install-hooks.sh

# Test 4: Monitoraggio
echo -e "\n🔍 Test 4: Monitoraggio singolo"
./scripts/monitor-tracking.sh once

# Crea file di test per validare il sistema
echo "Test content" > test.log
echo "secret=api_key_123" > .env.test
mkdir -p node_modules/test
echo "test" > node_modules/test/file.js

echo -e "\n🎯 Test finale: Verifica che i file di test siano ignorati"
ignored_count=0
test_files=("test.log" ".env.test" "node_modules/test/file.js")

for file in "${test_files[@]}"; do
    if git check-ignore "$file" >/dev/null 2>&1; then
        echo "✅ $file correttamente ignorato"
        ((ignored_count++))
    else
        echo "❌ $file NON ignorato"
    fi
done

# Cleanup file di test
rm -f test.log .env.test
rm -rf node_modules/test

echo -e "\n✨ Sistema di tracking intelligente implementato!"
echo -e "\n📋 Funzionalità disponibili:"
echo "- 🤖 Generazione automatica .gitignore: ./scripts/generate-gitignore.sh"
echo "- 📊 Validazione completa: ./scripts/validate-tracking.sh"
echo "- 🔧 Git hooks intelligenti: ./scripts/install-hooks.sh"
echo "- 🔍 Monitoraggio continuo: ./scripts/monitor-tracking.sh"
echo -e "\n🎓 Sistema pronto per uso enterprise!"
```

## 🎯 Obiettivi dell'Esercizio

### Competenze Avanzate Sviluppate
1. **Automazione Completa**: Sistema self-managing per .gitignore
2. **Monitoraggio Proattivo**: Rilevamento automatico problemi
3. **Sicurezza Integrata**: Prevenzione commit file sensibili
4. **Performance Optimization**: Analisi e ottimizzazione repository
5. **Enterprise Ready**: Scalabile per team e progetti grandi

### Validazione Completamento
- [ ] Sistema generazione .gitignore automatico
- [ ] Validatore completo implementato
- [ ] Git hooks intelligenti installati
- [ ] Sistema monitoraggio attivo
- [ ] Report automatici configurati
- [ ] Test di sicurezza funzionanti
- [ ] Performance monitoring attivo
- [ ] Documentazione generata automaticamente

## 🎓 Conclusioni

Questo esercizio rappresenta l'implementazione di un sistema enterprise-grade per la gestione intelligente del file tracking in Git, combinando:

1. **Automazione Intelligente**: Rilevamento automatico tipo progetto e generazione .gitignore
2. **Sicurezza Proattiva**: Monitoraggio continuo e prevenzione leak dati sensibili  
3. **Performance Optimization**: Analisi e ottimizzazione delle performance Git
4. **Reporting Avanzato**: Generazione automatica report e statistiche
5. **Extensibilità**: Sistema modulare e configurabile per diverse esigenze

### 💡 Applicazioni Reali

Questo sistema è ideale per:
- **Progetti Open Source**: Gestione automatica contributors multipli
- **Team Enterprise**: Standardizzazione e compliance automatica  
- **CI/CD Pipeline**: Integrazione con sistemi di automazione
- **Audit e Compliance**: Tracking automatico conformità sicurezza
- **Performance Monitoring**: Ottimizzazione continua repository

Un sistema di questo tipo in produzione può prevenire leak di dati, ottimizzare le performance e ridurre significativamente il carico di manutenzione manuale dei repository Git.
