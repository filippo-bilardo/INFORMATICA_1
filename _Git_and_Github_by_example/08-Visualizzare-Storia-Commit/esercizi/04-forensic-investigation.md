# Forensic Git: Investigazione Avanzata della Storia del Repository

⭐⭐⭐⭐ **Livello**: Avanzato  
🕒 **Tempo**: 45-60 minuti  
🎯 **Obiettivo**: Padroneggiare tecniche avanzate di investigazione della cronologia Git per debugging e analisi forensic

## 📋 Scenario

Sei un senior developer che deve investigare un repository enterprise per risolvere problemi critici, identificare regressioni e condurre analisi forensic su un progetto con centinaia di commit e multipli contributors.

## 🕵️ Situazioni di Investigazione

### Caso 1: Il Bug Misterioso
Un bug critico è apparso in produzione, ma non è chiaro quando è stato introdotto.

### Caso 2: Performance Degradation  
Le performance dell'applicazione sono peggiorate negli ultimi mesi.

### Caso 3: Security Audit
Devi verificare se credenziali sensibili sono mai state committate nella storia.

### Caso 4: Code Quality Analysis
Analisi dettagliata della qualità del codice e dei pattern di sviluppo del team.

## 🎯 Esercizio Completo

### Fase 1: Setup Repository di Investigazione

```bash
# Crea un repository complesso per l'investigazione
mkdir git-forensic-lab && cd git-forensic-lab
git init

# Simula una storia complessa con multipli autori e tipi di commit
# Setup primo autore
git config user.name "Alice Developer"
git config user.email "alice@company.com"

# Crea file iniziali
cat > README.md << 'EOF'
# Enterprise Application

Versione: 1.0.0
Creato: 2023-01-15

## Funzionalità
- Sistema di autenticazione
- Dashboard analytics
- API REST
EOF

git add README.md
git commit -m "feat: initial project setup

- Configurazione base progetto
- Documentazione iniziale
- Struttura repository"

# Crea struttura applicazione
mkdir -p {src/{auth,dashboard,api},tests,docs,config}

# Sistema di autenticazione
cat > src/auth/login.js << 'EOF'
class AuthService {
    constructor() {
        this.apiUrl = 'https://api.company.com';
        this.timeout = 5000;
    }
    
    async login(username, password) {
        // TODO: Implement secure login
        const response = await fetch(`${this.apiUrl}/login`, {
            method: 'POST',
            body: JSON.stringify({ username, password })
        });
        return response.json();
    }
}
EOF

git add src/auth/login.js
git commit -m "feat(auth): implement basic login service

- Basic authentication service
- API integration setup
- Error handling placeholder"

# Simula bug introduce - password leak
cat > src/auth/config.js << 'EOF'
const CONFIG = {
    apiUrl: 'https://api.company.com',
    adminPassword: 'admin123', // TODO: Remove this
    dbPassword: 'secretpass456',
    timeout: 5000
};

module.exports = CONFIG;
EOF

git add src/auth/config.js
git commit -m "feat(auth): add configuration file

- Centralized configuration
- API endpoints
- Default settings"

# Dashboard features
cat > src/dashboard/analytics.js << 'EOF'
class Analytics {
    constructor() {
        this.data = [];
        this.cache = new Map();
    }
    
    // Performance issue: O(n²) complexity
    generateReport() {
        const result = [];
        for (let i = 0; i < this.data.length; i++) {
            for (let j = 0; j < this.data.length; j++) {
                if (this.data[i].category === this.data[j].category) {
                    result.push(this.data[i]);
                }
            }
        }
        return result;
    }
}
EOF

git add src/dashboard/analytics.js
git commit -m "feat(dashboard): analytics report generation

- Basic reporting functionality
- Data processing
- Category filtering"

# Cambia autore per simulare team
git config user.name "Bob Security"
git config user.email "bob@company.com"

# Tenta di fixare il problema di sicurezza
cat > src/auth/config.js << 'EOF'
const CONFIG = {
    apiUrl: process.env.API_URL || 'https://api.company.com',
    timeout: 5000,
    // Removed hardcoded passwords
};

module.exports = CONFIG;
EOF

git add src/auth/config.js
git commit -m "fix(security): remove hardcoded credentials

- Move passwords to environment variables
- Improve security posture
- Follow security best practices

Fixes: #123"

# Altra feature da Charlie
git config user.name "Charlie Performance"
git config user.email "charlie@company.com"

# Fix performance issue
cat > src/dashboard/analytics.js << 'EOF'
class Analytics {
    constructor() {
        this.data = [];
        this.cache = new Map();
    }
    
    // Fixed O(n) complexity using Map
    generateReport() {
        if (this.cache.has('report')) {
            return this.cache.get('report');
        }
        
        const categorized = this.data.reduce((acc, item) => {
            if (!acc[item.category]) {
                acc[item.category] = [];
            }
            acc[item.category].push(item);
            return acc;
        }, {});
        
        const result = Object.values(categorized).flat();
        this.cache.set('report', result);
        return result;
    }
    
    clearCache() {
        this.cache.clear();
    }
}
EOF

git add src/dashboard/analytics.js
git commit -m "perf(dashboard): optimize report generation

- Reduce complexity from O(n²) to O(n)
- Add caching mechanism
- Improve performance by 90%

Benchmark:
- Before: 2.5s for 1000 items
- After: 250ms for 1000 items"

# Crea branch feature
git checkout -b feature/api-v2

# Nuove funzionalità API
cat > src/api/v2.js << 'EOF'
class APIv2 {
    constructor() {
        this.version = '2.0';
        this.endpoints = [
            '/users',
            '/analytics',
            '/reports'
        ];
    }
    
    async processRequest(endpoint, data) {
        // Simulated processing with potential memory leak
        const largeArray = new Array(100000).fill(data);
        return largeArray.map(item => ({
            ...item,
            timestamp: Date.now(),
            processed: true
        }));
    }
}
EOF

git add src/api/v2.js
git commit -m "feat(api): implement API v2

- New REST endpoints
- Enhanced data processing
- Backwards compatibility maintained"

# Torna al main e crea merge problematico
git checkout main
git merge feature/api-v2 -m "Merge branch 'feature/api-v2'

- Integration of new API version
- Enhanced functionality
- Ready for release 2.0"

# Hotfix critico
git config user.name "Diana Hotfix"
git config user.email "diana@company.com"

cat > src/auth/login.js << 'EOF'
class AuthService {
    constructor() {
        this.apiUrl = 'https://api.company.com';
        this.timeout = 5000;
    }
    
    async login(username, password) {
        // CRITICAL FIX: Prevent SQL injection
        if (!username || !password || 
            username.includes("'") || 
            password.includes("'")) {
            throw new Error('Invalid credentials');
        }
        
        const response = await fetch(`${this.apiUrl}/login`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ username, password })
        });
        
        if (!response.ok) {
            throw new Error('Authentication failed');
        }
        
        return response.json();
    }
}
EOF

git add src/auth/login.js
git commit -m "CRITICAL: fix SQL injection vulnerability

- Add input validation
- Prevent malicious queries  
- Sanitize user inputs

CVE: CVE-2023-0001
Severity: HIGH
Reporter: security@company.com"

echo "🏗️ Repository complesso di investigazione creato!"
```

### Fase 2: Investigazione Forensic Avanzata

```bash
# Script per investigazione completa
cat > scripts/forensic-investigation.sh << 'EOF'
#!/bin/bash

# ====================================
# INVESTIGAZIONE FORENSIC REPOSITORY
# ====================================

set -e

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
NC='\033[0m'

print_header() {
    echo -e "\n${BLUE}=====================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}=====================================${NC}\n"
}

print_info() { echo -e "${BLUE}ℹ️  $1${NC}"; }
print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }
print_highlight() { echo -e "${PURPLE}🔍 $1${NC}"; }

# Analisi generale repository
repository_overview() {
    print_header "📊 OVERVIEW GENERALE REPOSITORY"
    
    local total_commits=$(git rev-list --all --count)
    local authors=$(git log --format='%an' | sort -u | wc -l)
    local first_commit=$(git log --reverse --format='%H' | head -1)
    local last_commit=$(git log --format='%H' | head -1)
    local repo_age=$(git log --reverse --format='%ci' | head -1)
    local total_files=$(git ls-files | wc -l)
    
    print_info "Commit totali: $total_commits"
    print_info "Autori unici: $authors"
    print_info "File attuali: $total_files"
    print_info "Primo commit: $first_commit"
    print_info "Età repository: $repo_age"
    
    echo -e "\n📈 Statistiche per autore:"
    git shortlog -sn --all
    
    echo -e "\n📅 Timeline commit (ultimi 10):"
    git log --oneline --format='%C(yellow)%h%C(reset) %C(blue)%ad%C(reset) %C(green)%an%C(reset) %s' --date=short -10
}

# Ricerca vulnerabilità di sicurezza
security_investigation() {
    print_header "🔒 INVESTIGAZIONE SICUREZZA"
    
    # Pattern sensibili da cercare
    local security_patterns=(
        "password"
        "secret"
        "token"
        "api.key"
        "credential"
        "admin123"
        "secretpass"
        "private.key"
    )
    
    print_info "Scansione pattern sensibili nella cronologia..."
    
    for pattern in "${security_patterns[@]}"; do
        print_highlight "Cerca pattern: $pattern"
        
        # Cerca nel contenuto dei commit
        if git log --all --grep="$pattern" --oneline | head -5; then
            print_warning "Pattern trovato nei messaggi di commit!"
        fi
        
        # Cerca nel contenuto dei file nella storia
        if git log --all -p -S"$pattern" --oneline | head -5; then
            print_warning "Pattern trovato nel contenuto dei file!"
            
            # Mostra commit specifici
            echo "Dettagli commit con '$pattern':"
            git log --all -p -S"$pattern" --format='%C(red)%h%C(reset) %s %C(blue)(%an, %ad)%C(reset)' --date=short | head -10
        fi
        
        echo ""
    done
    
    # Cerca file sensibili eliminati
    print_info "Verifica file sensibili eliminati..."
    git log --diff-filter=D --summary | grep -E '\.(key|pem|env|secret)$' | head -10
    
    # Cerca commit di sicurezza
    print_info "Commit correlati alla sicurezza:"
    git log --all --grep="security\|fix\|vulnerability\|CVE" --oneline --format='%C(red)%h%C(reset) %C(yellow)%ad%C(reset) %s' --date=short
}

# Analisi performance regression
performance_analysis() {
    print_header "⚡ ANALISI PERFORMANCE"
    
    print_info "Cerca commit relativi a performance..."
    
    # Commit con keyword performance
    git log --all --grep="perf\|performance\|optimization\|slow\|speed" --oneline --format='%C(green)%h%C(reset) %C(yellow)%ad%C(reset) %s' --date=short
    
    echo -e "\n🔍 Analisi modifiche file critici:"
    
    # File che potrebbero impattare performance
    local perf_files=(
        "*.js"
        "*.java"
        "*.py"
        "package.json"
        "requirements.txt"
    )
    
    for pattern in "${perf_files[@]}"; do
        print_highlight "Modifiche a: $pattern"
        git log --oneline --follow -- "$pattern" | head -5
        echo ""
    done
    
    # Trova commit con molte modifiche (potenziali refactoring)
    print_info "Commit con molte modifiche (possibili refactoring):"
    git log --format='%h %s' --shortstat | awk '
        /^[a-f0-9]+/ { commit = $0; getline; 
        if($1 + $4 > 50) print commit " | " $0 }' | head -10
}

# Hunting per bug specifici
bug_hunting() {
    print_header "🐛 BUG HUNTING"
    
    local bug_keywords=(
        "bug"
        "fix"
        "error"
        "issue"
        "problem"
        "crash"
        "fail"
    )
    
    print_info "Cerca pattern di bug fixing..."
    
    for keyword in "${bug_keywords[@]}"; do
        local count=$(git log --all --grep="$keyword" --oneline | wc -l)
        if [ $count -gt 0 ]; then
            print_highlight "$keyword: $count commit"
        fi
    done
    
    echo -e "\n🔍 Timeline bug fixes:"
    git log --all --grep="fix\|bug" --oneline --format='%C(red)%h%C(reset) %C(yellow)%ad%C(reset) %C(green)%an%C(reset) %s' --date=short | head -15
    
    echo -e "\n🎯 Commit sospetti (CRITICAL, URGENT, HOTFIX):"
    git log --all --grep="CRITICAL\|URGENT\|HOTFIX\|EMERGENCY" --oneline --format='%C(red)%h%C(reset) %s' | head -10
}

# Analisi contribuzioni del team
team_analysis() {
    print_header "👥 ANALISI TEAM"
    
    print_info "Contribuzioni per autore:"
    git shortlog -sn --all
    
    echo -e "\n📊 Statistiche dettagliate per autore:"
    git log --format='%an' | sort | uniq -c | sort -rn | while read count author; do
        echo "👤 $author: $count commit"
        
        # Prime e ultime attività
        local first=$(git log --author="$author" --reverse --format='%ad' --date=short | head -1)
        local last=$(git log --author="$author" --format='%ad' --date=short | head -1)
        echo "   📅 Periodo: $first → $last"
        
        # Linee di codice modificate
        local stats=$(git log --author="$author" --pretty=tformat: --numstat | awk '{add+=$1; del+=$2} END {print add, del}')
        echo "   📝 Linee: +$(echo $stats | cut -d' ' -f1) -$(echo $stats | cut -d' ' -f2)"
        echo ""
    done
    
    print_info "Pattern di collaborazione:"
    echo "Merges e collaborazioni:"
    git log --merges --format='%h %s %an %ad' --date=short | head -10
}

# Code smell detection
code_smell_detection() {
    print_header "👃 RILEVAMENTO CODE SMELLS"
    
    # TODO comments
    print_info "TODO e FIXME nella cronologia:"
    git log --all -p --grep="TODO\|FIXME\|HACK\|XXX" | head -20
    
    # Commit con messaggi sospetti
    print_info "Commit con messaggi sospetti:"
    git log --all --grep="temp\|test\|debug\|wip\|quick" --oneline | head -10
    
    # File che cambiano spesso (hotspot)
    print_info "File che cambiano più frequentemente (hotspot):"
    git log --name-only --format= | sort | uniq -c | sort -rn | head -10
    
    # Commit molto grandi
    print_info "Commit molto grandi (>100 linee):"
    git log --format='%h %s' --shortstat | awk '
        /^[a-f0-9]+/ { commit = $0; getline; 
        if($1 + $4 > 100) print commit " | " $0 }' | head -5
}

# Analisi timeline specifica
timeline_analysis() {
    print_header "📅 ANALISI TIMELINE"
    
    read -p "🔍 Inserisci data di inizio (YYYY-MM-DD) o premi ENTER per ultimi 30 giorni: " start_date
    
    if [ -z "$start_date" ]; then
        start_date=$(date -d "30 days ago" +%Y-%m-%d)
    fi
    
    print_info "Analisi da: $start_date"
    
    echo -e "\n📊 Attività giornaliera:"
    git log --since="$start_date" --format='%ad' --date=short | sort | uniq -c
    
    echo -e "\n🕐 Attività per ora del giorno:"
    git log --since="$start_date" --format='%ad' --date=format:'%H' | sort | uniq -c
    
    echo -e "\n📈 Commit più significativi del periodo:"
    git log --since="$start_date" --oneline --format='%C(yellow)%h%C(reset) %C(blue)%ad%C(reset) %C(green)%an%C(reset) %s' --date=short | head -15
}

# Genera report completo
generate_report() {
    local report_file="forensic-report-$(date +%Y%m%d-%H%M%S).md"
    
    print_header "📄 GENERAZIONE REPORT"
    
    cat > "$report_file" << REPORT_START
# 🕵️ Report Investigazione Forensic Git

**Data**: $(date)  
**Repository**: $(basename $(pwd))  
**Investigatore**: $(git config user.name)  

---

## 📊 Sommario Esecutivo

$(repository_overview 2>&1)

## 🔒 Analisi Sicurezza

$(security_investigation 2>&1)

## ⚡ Performance Analysis

$(performance_analysis 2>&1)

## 🐛 Bug Investigation

$(bug_hunting 2>&1)

## 👥 Team Analysis

$(team_analysis 2>&1)

## 👃 Code Smells

$(code_smell_detection 2>&1)

---

**Report generato da**: forensic-investigation.sh  
**Versione Git**: $(git --version)
REPORT_START

    print_success "Report salvato: $report_file"
    
    # Apri report se possibile
    if command -v code >/dev/null 2>&1; then
        code "$report_file"
        print_info "Report aperto in VS Code"
    fi
}

# Menu interattivo
interactive_menu() {
    while true; do
        print_header "🕵️ GIT FORENSIC INVESTIGATION MENU"
        echo "1. 📊 Overview Repository"
        echo "2. 🔒 Investigazione Sicurezza"
        echo "3. ⚡ Analisi Performance"
        echo "4. 🐛 Bug Hunting"
        echo "5. 👥 Analisi Team"
        echo "6. 👃 Code Smell Detection"
        echo "7. 📅 Timeline Analysis"
        echo "8. 📄 Genera Report Completo"
        echo "9. 🚪 Esci"
        
        read -p "Scegli un'opzione (1-9): " choice
        
        case $choice in
            1) repository_overview ;;
            2) security_investigation ;;
            3) performance_analysis ;;
            4) bug_hunting ;;
            5) team_analysis ;;
            6) code_smell_detection ;;
            7) timeline_analysis ;;
            8) generate_report ;;
            9) print_success "Investigazione completata!"; break ;;
            *) print_error "Opzione non valida" ;;
        esac
        
        echo ""
        read -p "Premi ENTER per continuare..."
    done
}

# Main
main() {
    if [ "$1" = "--auto" ]; then
        print_info "Esecuzione investigazione automatica completa..."
        repository_overview
        security_investigation
        performance_analysis
        bug_hunting
        team_analysis
        code_smell_detection
        generate_report
    else
        interactive_menu
    fi
}

main "$@"
EOF

chmod +x scripts/forensic-investigation.sh

echo "Script di investigazione forensic creato!"
```

### Fase 3: Tecniche Avanzate di Log Analysis

```bash
# Crea comandi alias personalizzati per investigazione
echo "🔧 Configurazione alias per investigazione..."

git config alias.investigate '!bash scripts/forensic-investigation.sh'

# Alias per analisi rapide
git config alias.timeline 'log --graph --oneline --format="%C(yellow)%h%C(reset) %C(blue)%ad%C(reset) %C(green)%an%C(reset) %s" --date=short --all'

git config alias.security 'log --all --grep="security\|password\|secret\|token" --oneline'

git config alias.performance 'log --all --grep="perf\|performance\|optimization" --oneline'

git config alias.bugs 'log --all --grep="fix\|bug\|error" --oneline'

git config alias.authors 'shortlog -sn --all'

git config alias.hotspots '!git log --name-only --format= | sort | uniq -c | sort -rn | head -20'

git config alias.recent 'log --since="7 days ago" --oneline --author="$(git config user.name)"'

git config alias.blame-stats '!f() { git log --format="%an" "$@" | sort | uniq -c | sort -rn; }; f'

git config alias.find-commit 'log --all --grep'

git config alias.when-added 'log --diff-filter=A --follow --format="%h %ad %s" --date=short --'

echo "✅ Alias configurati!"

# Test comandi di investigazione
echo -e "\n🧪 Test investigazione..."

echo -e "\n1. 📊 Timeline generale:"
git timeline | head -10

echo -e "\n2. 🔒 Sicurezza:"
git security

echo -e "\n3. ⚡ Performance:"
git performance

echo -e "\n4. 🐛 Bug fixes:"
git bugs

echo -e "\n5. 👥 Contributors:"
git authors

echo -e "\n6. 🔥 Hotspots (file che cambiano spesso):"
git hotspots

echo -e "\n7. 🕐 Attività recente:"
git recent
```

### Fase 4: Advanced Search e Filtering

```bash
# Crea script per ricerche avanzate
cat > scripts/advanced-search.sh << 'EOF'
#!/bin/bash

# ====================================
# RICERCA AVANZATA NELLA STORIA GIT
# ====================================

print_info() { echo -e "\033[0;34mℹ️  $1\033[0m"; }
print_success() { echo -e "\033[0;32m✅ $1\033[0m"; }

echo "🔍 RICERCA AVANZATA NELLA STORIA GIT"
echo "===================================="

# 1. Ricerca per contenuto specifico
search_content() {
    local search_term="$1"
    print_info "Ricerca contenuto: '$search_term'"
    
    # Cerca nel codice attuale
    echo "📄 Nel codice attuale:"
    git grep "$search_term" || echo "Non trovato nel codice attuale"
    
    # Cerca nella storia
    echo -e "\n📚 Nella storia dei commit:"
    git log -S"$search_term" --oneline || echo "Non trovato nella storia"
    
    # Cerca nei messaggi di commit
    echo -e "\n💬 Nei messaggi di commit:"
    git log --grep="$search_term" --oneline || echo "Non trovato nei messaggi"
}

# 2. Ricerca per autore e periodo
search_author_period() {
    local author="$1"
    local since="$2"
    local until="$3"
    
    print_info "Ricerca per autore '$author' dal $since al $until"
    
    git log --author="$author" --since="$since" --until="$until" \
        --format="%h %ad %s" --date=short
}

# 3. Ricerca modifiche a file specifico
search_file_history() {
    local file="$1"
    print_info "Storia completa del file: $file"
    
    # Storia delle modifiche
    echo "📝 Cronologia modifiche:"
    git log --follow --oneline -- "$file"
    
    # Chi ha modificato di più il file
    echo -e "\n👥 Contributors principali:"
    git log --follow --format="%an" -- "$file" | sort | uniq -c | sort -rn
    
    # Quando è stato aggiunto
    echo -e "\n📅 Primo commit:"
    git log --diff-filter=A --follow --format="%h %ad %s" --date=short -- "$file" | tail -1
}

# 4. Ricerca commit tra due date con pattern
search_pattern_date_range() {
    local pattern="$1"
    local since="$2"
    local until="$3"
    
    print_info "Ricerca pattern '$pattern' dal $since al $until"
    
    git log --grep="$pattern" --since="$since" --until="$until" \
        --format="%C(yellow)%h%C(reset) %C(blue)%ad%C(reset) %C(green)%an%C(reset) %s" \
        --date=short
}

# 5. Analisi modifiche per estensione file
analyze_by_extension() {
    local ext="$1"
    print_info "Analisi file con estensione: $ext"
    
    # File attuali con estensione
    echo "📁 File attuali *.$ext:"
    git ls-files "*.$ext" | wc -l
    
    # Commit che hanno modificato file di questo tipo
    echo -e "\n📊 Commit che hanno modificato *.$ext:"
    git log --name-only --format="%h %s" | grep -A 100 "^[a-f0-9]" | grep "\.$ext$" | wc -l
    
    # Autori principali per questo tipo di file
    echo -e "\n👥 Autori principali per *.$ext:"
    git log --name-only --format="%an%n%N" -- "*.$ext" | grep -v "^$" | sort | uniq -c | sort -rn | head -5
}

# Menu interattivo di ricerca
interactive_search() {
    echo -e "\n🔍 Menu Ricerca Interattiva"
    echo "=========================="
    echo "1. Ricerca per contenuto"
    echo "2. Ricerca per autore e periodo"
    echo "3. Storia file specifico"
    echo "4. Pattern in range di date"
    echo "5. Analisi per estensione file"
    echo "6. Esci"
    
    read -p "Scegli opzione (1-6): " choice
    
    case $choice in
        1)
            read -p "Inserisci termine da cercare: " term
            search_content "$term"
            ;;
        2)
            read -p "Nome autore: " author
            read -p "Data inizio (YYYY-MM-DD): " since
            read -p "Data fine (YYYY-MM-DD): " until
            search_author_period "$author" "$since" "$until"
            ;;
        3)
            read -p "Percorso file: " file
            search_file_history "$file"
            ;;
        4)
            read -p "Pattern da cercare: " pattern
            read -p "Data inizio (YYYY-MM-DD): " since
            read -p "Data fine (YYYY-MM-DD): " until
            search_pattern_date_range "$pattern" "$since" "$until"
            ;;
        5)
            read -p "Estensione file (senza punto): " ext
            analyze_by_extension "$ext"
            ;;
        6)
            print_success "Ricerca completata!"
            return
            ;;
        *)
            echo "Opzione non valida"
            ;;
    esac
    
    echo ""
    read -p "Premi ENTER per continuare..."
    interactive_search
}

# Esempi di ricerca automatica
demo_searches() {
    print_info "🎯 Esempi di ricerca automatica"
    
    echo -e "\n1. Ricerca password nella storia:"
    search_content "password"
    
    echo -e "\n2. Commit di sicurezza:"
    search_pattern_date_range "security\|fix" "2023-01-01" "2024-12-31"
    
    echo -e "\n3. Analisi file JavaScript:"
    analyze_by_extension "js"
    
    echo -e "\n4. Storia file di configurazione:"
    search_file_history "src/auth/config.js"
}

# Main
if [ "$1" = "--demo" ]; then
    demo_searches
elif [ "$1" = "--interactive" ]; then
    interactive_search
else
    echo "Uso: $0 [--demo|--interactive]"
    echo "  --demo: Esegue ricerche di esempio"
    echo "  --interactive: Menu interattivo"
fi
EOF

chmod +x scripts/advanced-search.sh

echo "Script di ricerca avanzata creato!"
```

### Fase 5: Visualizzazione e Reporting

```bash
# Test completo del sistema
echo -e "\n🎯 ESECUZIONE TEST COMPLETO"
echo "============================"

echo -e "\n1. 🕵️ Investigazione forensic automatica:"
./scripts/forensic-investigation.sh --auto

echo -e "\n2. 🔍 Demo ricerche avanzate:"
./scripts/advanced-search.sh --demo

echo -e "\n3. 📊 Test alias personalizzati:"
echo "   📈 Timeline:"
git timeline | head -5

echo -e "\n   🔒 Security issues:"
git security | head -3

echo -e "\n   👥 Top contributors:"
git authors | head -5

echo -e "\n   🔥 File hotspots:"
git hotspots | head -5

echo -e "\n✨ ESERCIZIO FORENSIC COMPLETATO!"
echo -e "\n📋 Strumenti disponibili:"
echo "- ./scripts/forensic-investigation.sh (investigazione completa)"
echo "- ./scripts/advanced-search.sh --interactive (ricerca interattiva)"
echo "- git investigate (alias per investigazione)"
echo "- git timeline (timeline grafica)"
echo "- git security (commit di sicurezza)"
echo "- git bugs (bug fixes)"
echo "- git hotspots (file che cambiano spesso)"

echo -e "\n🎓 Competenze sviluppate:"
echo "✅ Investigazione forensic avanzata"
echo "✅ Ricerca contenuti nella storia"
echo "✅ Analisi pattern di sviluppo"
echo "✅ Detection vulnerabilità di sicurezza"
echo "✅ Performance regression analysis"
echo "✅ Team collaboration analysis"
echo "✅ Code smell detection"
echo "✅ Reporting automatico"
```

## 🎯 Obiettivi dell'Esercizio

### Competenze Avanzate Sviluppate
1. **Investigazione Forensic**: Analisi dettagliata della storia del repository
2. **Security Auditing**: Identificazione problemi di sicurezza nella cronologia
3. **Performance Analysis**: Tracking regressioni e ottimizzazioni
4. **Team Analytics**: Analisi pattern di collaborazione
5. **Advanced Git Searching**: Tecniche di ricerca avanzate
6. **Automated Reporting**: Generazione report investigativi

### Casi d'Uso Reali
- **Debug Production Issues**: Identificare quando bug sono stati introdotti
- **Security Audits**: Verificare se credenziali sono mai state esposte
- **Code Review Retrospectives**: Analizzare qualità del codice nel tempo
- **Team Performance**: Valutare contribuzioni e pattern di sviluppo
- **Compliance Checking**: Verificare aderenza a standard di sviluppo
- **Knowledge Transfer**: Capire evoluzione del progetto per nuovi team member

### Validazione Completamento
- [ ] Repository complesso di test creato
- [ ] Script investigazione forensic funzionante
- [ ] Tecniche di ricerca avanzata implementate
- [ ] Alias personalizzati configurati
- [ ] Sistema di reporting automatico
- [ ] Analisi sicurezza completata
- [ ] Performance regression analysis
- [ ] Team collaboration insights

## 🎓 Conclusioni

Questo esercizio rappresenta il livello più avanzato di analisi della cronologia Git, combinando:

1. **Tecniche Investigative**: Metodologie da detective per esplorare la storia
2. **Automazione Intelligente**: Script per analisi complesse automatizzate
3. **Security Focus**: Identificazione proattiva di problemi di sicurezza
4. **Performance Insights**: Tracking dell'evoluzione delle performance
5. **Team Dynamics**: Comprensione dei pattern di collaborazione

### 💡 Best Practices Apprese

- **Investigazione Sistematica**: Approccio metodico all'analisi della cronologia
- **Automazione Ricerche**: Script riutilizzabili per analisi ricorrenti
- **Security-First Mindset**: Sempre cercare problemi di sicurezza
- **Documentation Through History**: La cronologia Git come documentazione vivente
- **Team Awareness**: Usare la storia per migliorare la collaborazione

Queste competenze sono essenziali per senior developer, tech lead e security engineer che devono mantenere e debuggare sistemi enterprise complessi.
