#!/bin/bash

# Script per verificare i link nei file README.md
# Author: GitHub Copilot
# Version: 1.0

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Contatori
TOTAL_FILES=0
TOTAL_LINKS=0
BROKEN_LINKS=0
EXTERNAL_LINKS=0

# Array per memorizzare i link rotti
declare -a BROKEN_LINKS_ARRAY=()

# Funzione per stampare l'header
print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}     README.md Link Checker Script     ${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo ""
}

# Funzione per controllare se un file esiste
check_file_exists() {
    local file_path="$1"
    local base_dir="$2"
    
    # Converti il path relativo in assoluto
    local full_path=""
    
    # Se il path inizia con ./, è relativo alla directory corrente
    if [[ "$file_path" == ./* ]]; then
        full_path="${base_dir}/${file_path#./}"
    # Se il path inizia con ../, va alla directory padre
    elif [[ "$file_path" == ../* ]]; then
        full_path="${base_dir}/${file_path}"
    # Se il path non inizia con ./ o ../, assumiamo sia relativo
    elif [[ "$file_path" != /* ]]; then
        full_path="${base_dir}/${file_path}"
    else
        full_path="$file_path"
    fi
    
    # Normalizza il path
    full_path=$(realpath -m "$full_path" 2>/dev/null || echo "$full_path")
    
    if [[ -f "$full_path" ]] || [[ -d "$full_path" ]]; then
        return 0
    else
        return 1
    fi
}

# Funzione per controllare URL esterni
check_external_url() {
    local url="$1"
    
    # Usa curl per controllare l'URL
    if curl -s --head --request GET --max-time 10 "$url" | grep -q "200 OK\|301\|302"; then
        return 0
    else
        return 1
    fi
}

# Funzione per estrarre link markdown da un file
extract_markdown_links() {
    local file="$1"
    
    # Estrai link nel formato [text](url) usando un pattern più semplice e affidabile
    grep -o '\[.*\](.*[^)])' "$file" 2>/dev/null | while read -r line; do
        # Estrai solo l'URL tra parentesi usando sed
        echo "$line" | sed 's/.*(\([^)]*\)).*/\1/'
    done
}

# Funzione per controllare i link in un file README
check_readme_links() {
    local readme_file="$1"
    local readme_dir=$(dirname "$readme_file")
    
    echo -e "${YELLOW}Controllo: ${readme_file}${NC}"
    
    local file_link_count=0
    local file_broken_count=0
    
    # Estrai tutti i link markdown
    while IFS= read -r link; do
        [[ -z "$link" ]] && continue
        
        ((TOTAL_LINKS++))
        ((file_link_count++))
        
        echo -n "  Controllo link: $link ... "
        
        # Controlla se è un URL esterno
        if [[ "$link" =~ ^https?:// ]]; then
            ((EXTERNAL_LINKS++))
            if check_external_url "$link"; then
                echo -e "${GREEN}OK${NC}"
            else
                echo -e "${RED}BROKEN${NC}"
                ((BROKEN_LINKS++))
                ((file_broken_count++))
                BROKEN_LINKS_ARRAY+=("$readme_file: $link")
            fi
        # Controlla se è un link interno
        else
            if check_file_exists "$link" "$readme_dir"; then
                echo -e "${GREEN}OK${NC}"
            else
                echo -e "${RED}BROKEN${NC}"
                ((BROKEN_LINKS++))
                ((file_broken_count++))
                BROKEN_LINKS_ARRAY+=("$readme_file: $link")
            fi
        fi
    done < <(extract_markdown_links "$readme_file")
    
    if [[ $file_link_count -eq 0 ]]; then
        echo -e "  ${YELLOW}Nessun link trovato${NC}"
    else
        echo -e "  Link trovati: $file_link_count, Rotti: $file_broken_count"
    fi
    echo ""
}

# Funzione per trovare tutti i file README.md
find_readme_files() {
    local search_dir="$1"
    
    find "$search_dir" -name "README.md" -type f | sort
}

# Funzione per stampare il riassunto
print_summary() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}              RIASSUNTO                 ${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo -e "File README controllati: ${TOTAL_FILES}"
    echo -e "Link totali trovati: ${TOTAL_LINKS}"
    echo -e "Link esterni: ${EXTERNAL_LINKS}"
    echo -e "Link interni: $((TOTAL_LINKS - EXTERNAL_LINKS))"
    
    if [[ $BROKEN_LINKS -eq 0 ]]; then
        echo -e "${GREEN}Link rotti: ${BROKEN_LINKS} ✓${NC}"
        echo -e "${GREEN}Tutti i link funzionano correttamente!${NC}"
    else
        echo -e "${RED}Link rotti: ${BROKEN_LINKS} ✗${NC}"
        echo ""
        echo -e "${RED}LINK ROTTI TROVATI:${NC}"
        for broken_link in "${BROKEN_LINKS_ARRAY[@]}"; do
            echo -e "${RED}  ✗ ${broken_link}${NC}"
        done
    fi
    echo ""
}

# Funzione per mostrare l'aiuto
show_help() {
    cat << EOF
Utilizzo: $0 [OPZIONI] [DIRECTORY]

OPZIONI:
    -h, --help          Mostra questo messaggio di aiuto
    -v, --verbose       Output dettagliato
    -e, --external-only Controlla solo i link esterni
    -i, --internal-only Controlla solo i link interni
    -f, --fast          Salta il controllo degli URL esterni (più veloce)

DIRECTORY:
    Directory da controllare (default: directory corrente)

ESEMPI:
    $0                                          # Controlla la directory corrente
    $0 /path/to/project                        # Controlla una directory specifica
    $0 --fast ./GitGithubByExample             # Controllo veloce senza URL esterni
    $0 --external-only ./docs                  # Solo link esterni

EOF
}

# Funzione principale
main() {
    local target_dir="${1:-.}"
    local check_external=true
    local check_internal=true
    local verbose=false
    
    # Parse arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -v|--verbose)
                verbose=true
                shift
                ;;
            -e|--external-only)
                check_internal=false
                shift
                ;;
            -i|--internal-only)
                check_external=false
                shift
                ;;
            -f|--fast)
                check_external=false
                shift
                ;;
            -*)
                echo "Opzione sconosciuta: $1" >&2
                show_help
                exit 1
                ;;
            *)
                target_dir="$1"
                shift
                ;;
        esac
    done
    
    # Controlla se la directory esiste
    if [[ ! -d "$target_dir" ]]; then
        echo -e "${RED}Errore: Directory '$target_dir' non trovata${NC}" >&2
        exit 1
    fi
    
    print_header
    
    echo -e "Directory target: ${BLUE}$(realpath "$target_dir")${NC}"
    echo -e "Controllo link esterni: $([ "$check_external" = true ] && echo -e "${GREEN}SÌ${NC}" || echo -e "${RED}NO${NC}")"
    echo -e "Controllo link interni: $([ "$check_internal" = true ] && echo -e "${GREEN}SÌ${NC}" || echo -e "${RED}NO${NC}")"
    echo ""
    
    # Trova e controlla tutti i file README.md
    while IFS= read -r readme_file; do
        ((TOTAL_FILES++))
        
        # Modifica temporanea della funzione check_readme_links per supportare le opzioni
        if [[ "$check_internal" = true ]] && [[ "$check_external" = true ]]; then
            check_readme_links "$readme_file"
        elif [[ "$check_internal" = true ]]; then
            # Solo link interni
            check_readme_links_internal_only "$readme_file"
        elif [[ "$check_external" = true ]]; then
            # Solo link esterni
            check_readme_links_external_only "$readme_file"
        fi
        
    done < <(find_readme_files "$target_dir")
    
    print_summary
    
    # Exit code
    if [[ $BROKEN_LINKS -eq 0 ]]; then
        exit 0
    else
        exit 1
    fi
}

# Funzione per controllare solo link interni
check_readme_links_internal_only() {
    local readme_file="$1"
    local readme_dir=$(dirname "$readme_file")
    
    echo -e "${YELLOW}Controllo (solo interni): ${readme_file}${NC}"
    
    local file_link_count=0
    local file_broken_count=0
    
    while IFS= read -r link; do
        [[ -z "$link" ]] && continue
        
        # Salta i link esterni
        if [[ "$link" =~ ^https?:// ]]; then
            continue
        fi
        
        ((TOTAL_LINKS++))
        ((file_link_count++))
        
        echo -n "  Controllo link: $link ... "
        
        if check_file_exists "$link" "$readme_dir"; then
            echo -e "${GREEN}OK${NC}"
        else
            echo -e "${RED}BROKEN${NC}"
            ((BROKEN_LINKS++))
            ((file_broken_count++))
            BROKEN_LINKS_ARRAY+=("$readme_file: $link")
        fi
    done < <(extract_markdown_links "$readme_file")
    
    if [[ $file_link_count -eq 0 ]]; then
        echo -e "  ${YELLOW}Nessun link interno trovato${NC}"
    else
        echo -e "  Link interni trovati: $file_link_count, Rotti: $file_broken_count"
    fi
    echo ""
}

# Funzione per controllare solo link esterni
check_readme_links_external_only() {
    local readme_file="$1"
    
    echo -e "${YELLOW}Controllo (solo esterni): ${readme_file}${NC}"
    
    local file_link_count=0
    local file_broken_count=0
    
    while IFS= read -r link; do
        [[ -z "$link" ]] && continue
        
        # Salta i link interni
        if [[ ! "$link" =~ ^https?:// ]]; then
            continue
        fi
        
        ((TOTAL_LINKS++))
        ((EXTERNAL_LINKS++))
        ((file_link_count++))
        
        echo -n "  Controllo link: $link ... "
        
        if check_external_url "$link"; then
            echo -e "${GREEN}OK${NC}"
        else
            echo -e "${RED}BROKEN${NC}"
            ((BROKEN_LINKS++))
            ((file_broken_count++))
            BROKEN_LINKS_ARRAY+=("$readme_file: $link")
        fi
    done < <(extract_markdown_links "$readme_file")
    
    if [[ $file_link_count -eq 0 ]]; then
        echo -e "  ${YELLOW}Nessun link esterno trovato${NC}"
    else
        echo -e "  Link esterni trovati: $file_link_count, Rotti: $file_broken_count"
    fi
    echo ""
}

# Avvia il programma principale
main "$@"
