#!/bin/bash

# Path di base
BASE_PATH="/home/git-projects/INFORMATICA_1/G-Web_Development_(html,css)/HTML"

# Funzione per aggiungere i link di navigazione
add_navigation_links() {
  local folder=$1
  local files=($(ls $folder/*_*.md | sort))
  
  for (( i=0; i<${#files[@]}; i++ )); do
    local current_file="${files[$i]}"
    local file_basename=$(basename "$current_file")
    
    # Determina il link precedente
    local prev_link="../README.md"
    local prev_text="Indice Principale"
    if [[ $i -gt 0 ]]; then
      prev_link=$(basename "${files[$i-1]}")
      prev_text=$(grep -m 1 "^#" "${files[$i-1]}" | sed 's/^# *//')
      if [[ -z "$prev_text" ]]; then
        prev_text="Guida Precedente"
      fi
    fi
    
    # Determina il link successivo
    local next_link=""
    local next_text=""
    if [[ $i -lt $((${#files[@]} - 1)) ]]; then
      next_link=$(basename "${files[$i+1]}")
      next_text=$(grep -m 1 "^#" "${files[$i+1]}" | sed 's/^# *//')
      if [[ -z "$next_text" ]]; then
        next_text="Guida Successiva"
      fi
    fi
    
    # Controlla se i link di navigazione sono già presenti
    if ! grep -q "### Navigazione" "$current_file"; then
      echo "" >> "$current_file"
      echo "---" >> "$current_file"
      echo "" >> "$current_file"
      echo "### Navigazione" >> "$current_file"
      echo "- [📑 Indice](<$BASE_PATH/README.md>)" >> "$current_file"
      echo "- [⬅️ $prev_text](<$prev_link>)" >> "$current_file"
      if [[ -n "$next_link" ]]; then
        echo "- [➡️ $next_text](<$next_link>)" >> "$current_file"
      fi
    fi
  done
}

# Processa ogni cartella delle guide
for dir in "$BASE_PATH"/{0.*,1.*,2.*,3.*,4.*,5.*,6.*,7.*}; do
  if [ -d "$dir" ]; then
    add_navigation_links "$dir"
  fi
done

echo "Link di navigazione aggiunti o aggiornati in tutte le guide."
