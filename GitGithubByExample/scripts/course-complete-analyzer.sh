#!/bin/bash

# Script per analizzare la completezza del corso Git e GitHub

echo "🔍 ANALISI COMPLETA CORSO GIT E GITHUB"
echo "======================================"

COURSE_DIR="/home/git-projects/INFORMATICA_1/GitGithubByExample"
cd "$COURSE_DIR"

echo ""
echo "📁 STRUTTURA MODULI E DUPLICAZIONI:"
echo "-----------------------------------"

# Lista tutti i moduli ordinati
find . -maxdepth 1 -type d -name "*-*" | sort | while read module; do
    module_name=$(basename "$module")
    module_num=$(echo "$module_name" | grep -o '^[0-9]\+')
    echo "Modulo: $module_name (Numero: $module_num)"
done

echo ""
echo "⚠️  DUPLICAZIONI TROVATE:"
echo "------------------------"

# Trova duplicazioni nei numeri dei moduli
find . -maxdepth 1 -type d -name "*-*" | sed 's|./||' | sort | while read module; do
    num=$(echo "$module" | grep -o '^[0-9]\+')
    echo "$num|$module"
done | sort -n | awk -F'|' '{
    if ($1 == prev_num) {
        if (!printed[prev_num]) {
            print "DUPLICAZIONE " prev_num ": " prev_module
            printed[prev_num] = 1
        }
        print "DUPLICAZIONE " $1 ": " $2
    }
    prev_num = $1
    prev_module = $2
}'

echo ""
echo "📊 ANALISI COMPLETEZZA CONTENUTI:"
echo "---------------------------------"

total_modules=0
complete_modules=0
incomplete_modules=0

for module_dir in */; do
    if [[ "$module_dir" =~ ^[0-9]+-.*/ ]]; then
        total_modules=$((total_modules + 1))
        module_name="${module_dir%/}"
        
        # Conta file nelle sottocartelle
        guide_files=$(find "$module_dir/guide" -name "*.md" 2>/dev/null | wc -l)
        esempi_files=$(find "$module_dir/esempi" -name "*.md" 2>/dev/null | wc -l)
        esercizi_files=$(find "$module_dir/esercizi" -name "*.md" 2>/dev/null | wc -l)
        
        total_files=$((guide_files + esempi_files + esercizi_files))
        
        status="❌ INCOMPLETO"
        if [[ $guide_files -gt 0 && $esempi_files -gt 0 && $esercizi_files -gt 0 ]]; then
            status="✅ COMPLETO"
            complete_modules=$((complete_modules + 1))
        else
            incomplete_modules=$((incomplete_modules + 1))
        fi
        
        printf "%-40s G:%2d E:%2d Es:%2d Tot:%2d %s\n" \
               "$module_name" "$guide_files" "$esempi_files" "$esercizi_files" "$total_files" "$status"
    fi
done

echo ""
echo "📈 STATISTICHE GENERALI:"
echo "------------------------"
echo "Moduli totali: $total_modules"
echo "Moduli completi: $complete_modules"
echo "Moduli incompleti: $incomplete_modules"
echo "Percentuale completezza: $(( (complete_modules * 100) / total_modules ))%"

echo ""
echo "🔗 VERIFICA LINK NEI README:"
echo "----------------------------"

# Verifica link nei README principali
for module_dir in */; do
    if [[ "$module_dir" =~ ^[0-9]+-.*/ ]]; then
        readme_file="${module_dir}README.md"
        if [[ -f "$readme_file" ]]; then
            module_name="${module_dir%/}"
            
            # Estrai link dai README
            links=$(grep -o '\[.*\](.*\.md)' "$readme_file" 2>/dev/null | grep -o '([^)]*\.md)' | sed 's/[()]//g')
            
            if [[ -n "$links" ]]; then
                echo "Modulo: $module_name"
                while IFS= read -r link; do
                    if [[ -n "$link" ]]; then
                        full_path="${module_dir}${link}"
                        if [[ -f "$full_path" ]]; then
                            echo "  ✅ $link"
                        else
                            echo "  ❌ $link (FILE MANCANTE)"
                        fi
                    fi
                done <<< "$links"
                echo ""
            fi
        fi
    fi
done

echo "🎯 MODULI PRIORITARI DA COMPLETARE:"
echo "-----------------------------------"

# Lista moduli con contenuto zero o molto limitato
for module_dir in */; do
    if [[ "$module_dir" =~ ^[0-9]+-.*/ ]]; then
        module_name="${module_dir%/}"
        
        guide_files=$(find "$module_dir/guide" -name "*.md" 2>/dev/null | wc -l)
        esempi_files=$(find "$module_dir/esempi" -name "*.md" 2>/dev/null | wc -l)
        esercizi_files=$(find "$module_dir/esercizi" -name "*.md" 2>/dev/null | wc -l)
        
        total_files=$((guide_files + esempi_files + esercizi_files))
        
        if [[ $total_files -eq 0 ]]; then
            echo "🔴 PRIORITÀ ALTA: $module_name (0 file)"
        elif [[ $total_files -lt 3 ]]; then
            echo "🟡 PRIORITÀ MEDIA: $module_name ($total_files file)"
        fi
    fi
done
