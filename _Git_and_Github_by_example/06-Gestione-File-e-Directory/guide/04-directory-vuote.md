# Gestione Directory Vuote

## Concetti Fondamentali

### Perché Git Non Traccia Directory Vuote
Git è un **content tracker**, non un **file system tracker**. Questo significa:
- Git traccia **file** e il loro **contenuto**
- Le directory sono considerate solo **container** per i file
- Directory vuote non hanno contenuto → non vengono tracciate

### Implicazioni Pratiche
- Le directory vuote spariscono dai clone
- La struttura di directory si crea automaticamente quando si aggiungono file
- Serve una strategia per preservare directory importanti ma vuote

## Soluzioni per Directory Vuote

### 1. File `.gitkeep` (Convenzione Comune)

```bash
# Creare directory vuota con placeholder
mkdir empty-directory
touch empty-directory/.gitkeep
git add empty-directory/.gitkeep

# La directory ora viene tracciata
git commit -m "Add empty directory structure"
```

### 2. File `.gitignore` Vuoto

```bash
# Alternativa: usare .gitignore vuoto
mkdir logs
touch logs/.gitignore
git add logs/.gitignore
```

### 3. File `README.md` Descrittivo

```bash
# Per directory che avranno contenuto futuro
mkdir docs
echo "# Documentation" > docs/README.md
echo "This directory will contain project documentation." >> docs/README.md
git add docs/README.md
```

### 4. File `.placeholder` o `.empty`

```bash
# Altre convenzioni possibili
mkdir cache
touch cache/.placeholder
git add cache/.placeholder
```

## Strategie per Diverse Situazioni

### Struttura di Progetto Standard

```bash
# Creare struttura completa di progetto
mkdir -p {src/{components,utils,services},tests,docs,assets/{images,css,js}}

# Aggiungere placeholder in directory vuote
find . -type d -empty -exec touch {}/.gitkeep \;

# Aggiungere tutti i placeholder
git add **/.gitkeep
git commit -m "Initialize project structure"
```

### Directory di Build/Cache

```bash
# Directory che deve esistere ma rimanere vuota
mkdir build
echo "# Build Directory" > build/README.md
echo "" >> build/README.md
echo "This directory contains build artifacts." >> build/README.md
echo "Contents are generated and ignored by Git." >> build/README.md

# Aggiungere al .gitignore
echo "build/*" >> .gitignore
echo "!build/README.md" >> .gitignore
```

### Directory di Log/Temporanei

```bash
# Directory per file temporanei
mkdir -p {logs,temp,cache}

# Aggiungere .gitignore che preserva la directory
cat > logs/.gitignore << EOL
# Ignore all files in this directory
*

# But keep this file
!.gitignore
EOL

# Copiare negli altre directory
cp logs/.gitignore temp/
cp logs/.gitignore cache/

git add {logs,temp,cache}/.gitignore
```

## Casi d'Uso Pratici

### 1. Progetto Web Standard

```bash
# Struttura tipica progetto web
mkdir -p {
  src/{components,pages,styles,utils},
  public/{images,icons,fonts},
  tests/{unit,integration,e2e},
  docs/{api,guides,examples}
}

# Script per aggiungere .gitkeep ovunque necessario
for dir in $(find . -type d -empty); do
  if [[ ! "$dir" =~ ^\./\. ]]; then  # Esclude directory nascoste
    touch "$dir/.gitkeep"
  fi
done

git add **/.gitkeep
git commit -m "Setup project directory structure"
```

### 2. Progetto Backend/API

```bash
# Struttura backend
mkdir -p {
  src/{controllers,models,services,middleware,routes},
  config/{environments,database},
  storage/{logs,uploads,cache},
  tests/{unit,integration},
  docs/{api,deployment}
}

# .gitkeep per directory di codice vuote
touch src/{controllers,models,services,middleware,routes}/.gitkeep

# .gitignore per directory di storage
for dir in logs uploads cache; do
  cat > storage/$dir/.gitignore << EOL
# Ignore everything in this directory
*

# Except this file
!.gitignore
EOL
done

git add src/**/.gitkeep storage/**/.gitignore
git commit -m "Initialize backend project structure"
```

### 3. Progetto Documentation

```bash
# Struttura documentazione
mkdir -p {
  guides/{user,developer,admin},
  api/{v1,v2},
  examples/{basic,advanced},
  assets/{images,diagrams,videos}
}

# README.md descrittivi invece di .gitkeep
for dir in guides/{user,developer,admin}; do
  echo "# $(basename $dir | tr '[:lower:]' '[:upper:]') Documentation" > $dir/README.md
  echo "" >> $dir/README.md
  echo "This section contains documentation for $(basename $dir)s." >> $dir/README.md
done

git add guides/**/README.md
git commit -m "Initialize documentation structure"
```

## Automazione e Script

### Script per Struttura Automatica

```bash
#!/bin/bash
# create-project-structure.sh

PROJECT_TYPE=${1:-web}

case $PROJECT_TYPE in
  "web")
    DIRS=(
      "src/components"
      "src/pages" 
      "src/styles"
      "src/utils"
      "public/images"
      "public/css"
      "public/js"
      "tests/unit"
      "tests/integration"
      "docs"
    )
    ;;
  "api")
    DIRS=(
      "src/controllers"
      "src/models"
      "src/services"
      "src/routes"
      "config"
      "storage/logs"
      "storage/uploads"
      "tests"
      "docs/api"
    )
    ;;
  "mobile")
    DIRS=(
      "src/screens"
      "src/components"
      "src/services"
      "src/utils"
      "assets/images"
      "assets/fonts"
      "tests"
      "docs"
    )
    ;;
esac

# Creare directory
for dir in "${DIRS[@]}"; do
  mkdir -p "$dir"
  
  # Aggiungere .gitkeep o .gitignore appropriato
  if [[ "$dir" =~ (logs|uploads|cache|build|dist) ]]; then
    cat > "$dir/.gitignore" << EOL
# Ignore all files in this directory
*

# But keep this file
!.gitignore
EOL
  else
    touch "$dir/.gitkeep"
  fi
done

echo "Created $PROJECT_TYPE project structure"
git add . 2>/dev/null || echo "Run 'git add .' to track the structure"
```

### Makefile per Gestione Struttura

```makefile
# Makefile

.PHONY: init-dirs clean-empty check-structure

init-dirs:
	@echo "Initializing project directories..."
	@mkdir -p src/{components,utils,services} tests docs assets/{images,css,js}
	@find . -type d -empty -not -path './.*' -exec touch {}/.gitkeep \;
	@echo "Directory structure created"

clean-empty:
	@echo "Removing empty .gitkeep files..."
	@find . -name ".gitkeep" -type f -exec sh -c 'if [ $$(ls -1A "$$(dirname "{}")" | wc -l) -gt 1 ]; then rm "{}"; fi' \;

check-structure:
	@echo "Current directory structure:"
	@tree -a -I '.git' . 2>/dev/null || find . -type d -not -path './.*' | sort
```

## Best Practices

### ✅ Convenzioni Raccomandate

1. **Usa `.gitkeep` per directory strutturali**
   ```bash
   # Per directory che devono esistere vuote
   touch src/components/.gitkeep
   ```

2. **Usa `.gitignore` per directory di runtime**
   ```bash
   # Per directory che si riempiono durante l'esecuzione
   echo "*" > logs/.gitignore
   echo "!.gitignore" >> logs/.gitignore
   ```

3. **Usa `README.md` per directory documentali**
   ```bash
   # Per directory che ospiteranno documentazione
   echo "# API Documentation" > docs/api/README.md
   ```

4. **Mantieni coerenza nel progetto**
   ```bash
   # Scegli UNA convenzione e usala ovunque
   # Preferibilmente .gitkeep per semplicità
   ```

### ✅ Denominazione File Placeholder

```bash
# Opzioni comuni (scegli una)
.gitkeep      # Più comune, chiaro il proposito
.gitignore    # Per directory che si riempiranno
.placeholder  # Descrittivo ma meno standard
.empty        # Semplice ma ambiguo
README.md     # Per directory documentali
```

### ✅ Documentazione Struttura

```bash
# Documenta la struttura nel README principale
cat >> README.md << EOL

## Project Structure

\`\`\`
project/
├── src/
│   ├── components/     # React components
│   ├── services/       # API services
│   └── utils/          # Utility functions
├── tests/              # Test files
├── docs/               # Documentation
└── assets/             # Static assets
\`\`\`
EOL
```

## Errori Comuni e Soluzioni

### ❌ Problema: Directory sparisce dopo clone
```bash
# Directory vuota creata ma non tracciata
mkdir important-directory
git add .  # Non aggiunge directory vuota
```

**✅ Soluzione:**
```bash
# Aggiungere file placeholder
touch important-directory/.gitkeep
git add important-directory/.gitkeep
```

### ❌ Problema: Troppi file .gitkeep
```bash
# .gitkeep ovunque, anche dove non serve
find . -name ".gitkeep" | wc -l  # 50+ file
```

**✅ Soluzione:**
```bash
# Rimuovere .gitkeep da directory non vuote
for file in $(find . -name ".gitkeep"); do
  dir=$(dirname "$file")
  if [ $(ls -1A "$dir" | wc -l) -gt 1 ]; then
    git rm "$file"
  fi
done
```

### ❌ Problema: Conflitti con .gitkeep
```bash
# Conflitti di merge su file .gitkeep
git merge feature-branch  # Conflitto su .gitkeep
```

**✅ Soluzione:**
```bash
# Accettare sempre la versione locale per .gitkeep
git checkout --ours **/.gitkeep
git add **/.gitkeep
```

## Quiz di Autovalutazione

### Domanda 1
Perché Git non traccia directory vuote?
- a) È un bug di Git
- b) Git traccia contenuto, non strutture ✅
- c) Per risparmiare spazio
- d) Per compatibilità con SVN

### Domanda 2
Quale file è più comunemente usato per preservare directory vuote?
- a) `.placeholder`
- b) `.empty`
- c) `.gitkeep` ✅
- d) `.directory`

### Domanda 3
Come ignorare tutto in una directory tranne il file .gitignore?
- a) `*` e `!.gitignore` nel .gitignore della directory ✅
- b) `**/*` nel .gitignore principale
- c) Non è possibile
- d) Usare .gitkeep invece

### Domanda 4
Quale comando trova tutte le directory vuote?
- a) `find . -type d -empty` ✅
- b) `find . -empty -dir`
- c) `ls -la | grep empty`
- d) `git status --empty`

### Domanda 5
Quando usare README.md invece di .gitkeep?
- a) Mai, .gitkeep è sempre meglio
- b) Per directory documentali ✅
- c) Per directory temporanee
- d) Per directory di build

## Esercizi Pratici

### Esercizio 1: Struttura Base
1. Crea una struttura di directory per un progetto web
2. Usa .gitkeep per preservare directory vuote
3. Verifica che la struttura sia tracciata correttamente
4. Clona in altra directory e verifica che si preservi

### Esercizio 2: Directory Miste
1. Crea directory per diversi scopi (codice, logs, build)
2. Usa strategie diverse (.gitkeep, .gitignore, README.md)
3. Testa il comportamento con file aggiunti
4. Documenta le scelte fatte

### Esercizio 3: Automazione
1. Scrivi script per creare struttura progetto
2. Includi gestione automatica di placeholder
3. Testa con diversi tipi di progetto
4. Aggiungi pulizia automatica di .gitkeep non necessari

## Navigazione del Corso
- [📑 Indice](../../README.md)  
- [⬅️ Eliminazione File e Directory](./03-eliminazione-file.md)
- [➡️ 07 - Gitignore e File Tracking](../../07-Gitignore-e-File-Tracking/)
