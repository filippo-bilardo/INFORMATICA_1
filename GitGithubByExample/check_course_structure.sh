#!/bin/bash

# Script per verificare la struttura completa del corso Git e GitHub by Example

echo "=== ANALISI STRUTTURA CORSO GIT E GITHUB BY EXAMPLE ==="
echo "Data: $(date)"
echo ""

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Contatori
total_modules=0
complete_modules=0
missing_files=0

echo "🔍 VERIFICA CORRISPONDENZA LINK E FILE"
echo "======================================"

# Array dei moduli dal README principale
modules=(
    "01-Introduzione-al-Controllo-di-Versione"
    "02-Installazione-e-Configurazione-Git"
    "03-Primo-Repository-Git"
    "04-Comandi-Base-Git"
    "05-Area-di-Staging"
    "06-Gestione-File-e-Directory"
    "07-Gitignore-e-File-Tracking"
    "08-Visualizzare-Storia-Commit"
    "09-Commit-Avanzati"
    "10-Navigare-tra-Commit"
    "11-Annullare-Modifiche"
    "12-Concetti-di-Branching"
    "13-Creare-e-Gestire-Branch"
    "14-Merge-e-Strategie"
    "15-Risoluzione-Conflitti"
    "16-Introduzione-GitHub"
    "17-Clone-Push-Pull"
    "18-Collaborazione-Base"
    "19-Fork-e-Pull-Request"
    "20-Issues-e-Project-Management"
    "21-GitHub-Actions-Intro"
    "22-Pages-e-Documentazione"
    "23-Git-Flow-e-Strategie"
    "24-Rebase-e-Cherry-Pick"
    "25-Tag-e-Release"
    "26-Best-Practices"
    "27-Troubleshooting-Comune"
    "28-Progetto-Finale"
)

for module in "${modules[@]}"; do
    total_modules=$((total_modules + 1))
    echo ""
    echo "📁 Modulo: $module"
    
    if [ -d "$module" ]; then
        echo -e "  ${GREEN}✓${NC} Directory exists"
        
        # Verifica README.md del modulo
        if [ -f "$module/README.md" ]; then
            echo -e "  ${GREEN}✓${NC} README.md exists"
        else
            echo -e "  ${RED}✗${NC} README.md missing"
            missing_files=$((missing_files + 1))
        fi
        
        # Verifica struttura cartelle
        required_dirs=("guide" "esempi" "esercizi")
        all_dirs_exist=true
        
        for dir in "${required_dirs[@]}"; do
            if [ -d "$module/$dir" ]; then
                echo -e "  ${GREEN}✓${NC} $dir/ directory exists"
                
                # Conta file in ogni directory
                file_count=$(find "$module/$dir" -name "*.md" | wc -l)
                echo "    └── $file_count file .md trovati"
                
                if [ $file_count -eq 0 ]; then
                    echo -e "    ${YELLOW}⚠${NC} Directory vuota!"
                fi
            else
                echo -e "  ${RED}✗${NC} $dir/ directory missing"
                all_dirs_exist=false
                missing_files=$((missing_files + 1))
            fi
        done
        
        if [ "$all_dirs_exist" = true ]; then
            complete_modules=$((complete_modules + 1))
        fi
        
    else
        echo -e "  ${RED}✗${NC} Directory missing"
        missing_files=$((missing_files + 1))
    fi
done

echo ""
echo "📊 RIEPILOGO ANALISI"
echo "===================="
echo "Total modules: $total_modules"
echo -e "Complete modules: ${GREEN}$complete_modules${NC}"
echo -e "Missing elements: ${RED}$missing_files${NC}"

completion_rate=$(( (complete_modules * 100) / total_modules ))
echo "Completion rate: $completion_rate%"

echo ""
echo "🎯 RACCOMANDAZIONI"
echo "=================="

if [ $missing_files -gt 0 ]; then
    echo -e "${YELLOW}⚠ Azioni necessarie:${NC}"
    echo "  1. Completare strutture cartelle mancanti"
    echo "  2. Aggiungere file README.md mancanti"
    echo "  3. Popolare directory vuote con contenuti"
    echo "  4. Verificare link interni nei README"
else
    echo -e "${GREEN}✅ Struttura corso completa!${NC}"
fi

echo ""
echo "🔗 VERIFICA LINK NEL README PRINCIPALE"
echo "====================================="

# Verifica che tutti i link nel README principale funzionino
if [ -f "README.md" ]; then
    echo "Checking links in main README.md..."
    
    # Estrai tutti i link relativi dal README
    grep -o '\[.*\](\.\/.*\/)' README.md | while read -r link; do
        # Estrai il path dal link
        path=$(echo "$link" | sed 's/.*](\.\///' | sed 's/\/)//')
        
        if [ -d "$path" ]; then
            echo -e "${GREEN}✓${NC} Link valid: $path"
        else
            echo -e "${RED}✗${NC} Broken link: $path"
        fi
    done
else
    echo -e "${RED}✗${NC} Main README.md not found!"
fi

echo ""
echo "=== FINE ANALISI ==="
