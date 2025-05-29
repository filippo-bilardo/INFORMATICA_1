#!/bin/bash

# 🔍 Missing Content Analyzer - Git & GitHub Course
# Identifica i moduli con contenuti mancanti o insufficienti

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

COURSE_ROOT="/home/git-projects/INFORMATICA_1/GitGithubByExample"

echo "🎯 Missing Content Analysis"
echo "=========================="
echo ""

# Array per raccogliere i moduli con problemi
missing_content_modules=()

# Soglie minime per considerare un modulo completo
MIN_GUIDE_FILES=3
MIN_ESEMPI_FILES=2
MIN_ESERCIZI_FILES=2

echo -e "${BLUE}📊 Content Completeness Analysis${NC}"
echo "Threshold: Guide≥${MIN_GUIDE_FILES}, Esempi≥${MIN_ESEMPI_FILES}, Esercizi≥${MIN_ESERCIZI_FILES}"
echo ""

# Trova tutti i moduli
modules=$(find "$COURSE_ROOT" -maxdepth 1 -type d -name '[0-9][0-9]-*' | sort)

for module in $modules; do
    module_name=$(basename "$module")
    
    # Conta i file in ogni sezione
    guide_count=0
    esempi_count=0
    esercizi_count=0
    
    if [ -d "$module/guide" ]; then
        guide_count=$(find "$module/guide" -name '*.md' -type f | wc -l)
    fi
    
    if [ -d "$module/esempi" ]; then
        esempi_count=$(find "$module/esempi" -name '*.md' -type f | wc -l)
    fi
    
    if [ -d "$module/esercizi" ]; then
        esercizi_count=$(find "$module/esercizi" -name '*.md' -type f | wc -l)
    fi
    
    # Verifica completezza
    needs_attention=false
    issues=()
    
    if [ $guide_count -lt $MIN_GUIDE_FILES ]; then
        issues+=("Guide: $guide_count/$MIN_GUIDE_FILES")
        needs_attention=true
    fi
    
    if [ $esempi_count -lt $MIN_ESEMPI_FILES ]; then
        issues+=("Esempi: $esempi_count/$MIN_ESEMPI_FILES")
        needs_attention=true
    fi
    
    if [ $esercizi_count -lt $MIN_ESERCIZI_FILES ]; then
        issues+=("Esercizi: $esercizi_count/$MIN_ESERCIZI_FILES")
        needs_attention=true
    fi
    
    # Mostra risultato
    if [ "$needs_attention" = true ]; then
        echo -e "${RED}❌ $module_name${NC}"
        for issue in "${issues[@]}"; do
            echo -e "   ${YELLOW}⚠️ $issue${NC}"
        done
        missing_content_modules+=("$module_name")
    else
        echo -e "${GREEN}✅ $module_name${NC} (G:$guide_count, E:$esempi_count, Ex:$esercizi_count)"
    fi
done

echo ""
echo -e "${BLUE}📋 Summary${NC}"
echo "--------"
total_modules=$(echo "$modules" | wc -l)
complete_modules=$((total_modules - ${#missing_content_modules[@]}))
incomplete_modules=${#missing_content_modules[@]}

echo -e "Total Modules: ${BLUE}$total_modules${NC}"
echo -e "Complete Modules: ${GREEN}$complete_modules${NC}"
echo -e "Incomplete Modules: ${RED}$incomplete_modules${NC}"

if [ $incomplete_modules -gt 0 ]; then
    echo ""
    echo -e "${RED}🎯 Priority Modules for Completion:${NC}"
    for module in "${missing_content_modules[@]}"; do
        echo -e "${YELLOW}📝 $module${NC}"
    done
fi

echo ""
echo -e "${BLUE}💡 Next Steps:${NC}"
echo "1. Complete missing content for priority modules"
echo "2. Verify link consistency between README files"
echo "3. Add cross-module navigation"
echo "4. Create learning path progressions"
