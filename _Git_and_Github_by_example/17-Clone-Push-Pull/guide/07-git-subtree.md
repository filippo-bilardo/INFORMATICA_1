# 07 - Git Subtree: Incorporare Repository come Sottocartelle

## 📖 Spiegazione Concettuale

**Git Subtree** è un'alternativa ai submodules che permette di incorporare un repository esterno direttamente nella cronologia del repository principale. A differenza dei submodules, i subtree diventano parte integrante del progetto, senza mantenere collegamenti esterni visibili.

### Cosa sono i Subtree

Un **subtree** è una funzionalità che permette di unire il contenuto di un repository esterno in una sottocartella del repository principale, mantenendo la possibilità di sincronizzare le modifiche bidirezionalmente.

```
Repository Principale (con Subtree)
├── .git/
├── src/
│   └── main.c
├── docs/
└── vendor/                        ← Subtree da repository esterno
    ├── library.h                  ← Files dal repo esterno
    ├── library.c                  ← Completamente integrati
    └── README.md                  ← Nessun .git separato
```

### Differenze: Subtree vs Submodules

| Caratteristica | Subtree | Submodules |
|---------------|---------|------------|
| **Integrazione** | Completa nella cronologia | Repository separati collegati |
| **Cloning** | Automatico con git clone | Richiede --recursive o init |
| **Complessità** | Più semplice per utenti finali | Più complesso ma più flessibile |
| **Size Repository** | Aumenta dimensioni | Mantiene repository leggeri |
| **Offline Work** | Tutto disponibile localmente | Richiede accesso ai submodules |
| **Tool Support** | Funziona con tutti i tool Git | Richiede supporto specifico |

### Vantaggi dei Subtree

- **Semplicità**: Clone normale, nessuna configurazione speciale
- **Self-contained**: Tutto in un unico repository
- **Tool Compatibility**: Funziona con qualsiasi tool Git
- **History Preservation**: Mantiene cronologia del progetto incorporato
- **Offline Friendly**: Non richiede accesso a repository esterni

### Svantaggi dei Subtree

- **Repository Size**: Aumenta dimensioni del repository principale
- **History Pollution**: Cronologia può diventare confusa
- **Sync Complexity**: Sincronizzazione bidirezionale più complessa
- **Large Files**: Non ideale per repository con molti file binari

## ⚙️ Comandi Fondamentali

### Aggiungere un Subtree

```bash
# Sintassi base
git subtree add --prefix=<directory> <repository> <branch> --squash

# Esempi pratici
git subtree add --prefix=vendor/utils https://github.com/company/utils.git main --squash
git subtree add --prefix=libs/auth git@github.com:company/auth-lib.git develop --squash

# Senza --squash (mantiene cronologia completa)
git subtree add --prefix=vendor/tools https://github.com/company/tools.git main

# Verifica aggiunta
ls vendor/utils/
git log --oneline -5
```

### Aggiornare un Subtree (Pull)

```bash
# Pull aggiornamenti dal repository remoto
git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash

# Con strategia di merge specifica
git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash --strategy=subtree

# Per tutti i subtree (script personalizzato necessario)
#!/bin/bash
git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash
git subtree pull --prefix=libs/auth https://github.com/company/auth-lib.git develop --squash
```

### Contribuire Modifiche (Push)

```bash
# Push modifiche fatte nel subtree al repository originale
git subtree push --prefix=vendor/utils https://github.com/company/utils.git feature-branch

# Esempio workflow completo
# 1. Modifica files nel subtree
echo "// New utility function" >> vendor/utils/helper.js
git add vendor/utils/helper.js
git commit -m "Add new utility function"

# 2. Push al repository del subtree
git subtree push --prefix=vendor/utils https://github.com/company/utils.git feature/new-utility
```

### Rimuovere un Subtree

```bash
# Rimozione semplice (ma mantiene cronologia)
git rm -r vendor/utils
git commit -m "Remove utils subtree"

# Per rimozione completa, necessario rewrite history (pericoloso!)
# Non raccomandato se repository è condiviso
```

## 🔄 Workflow Completi

### Workflow 1: Integrazione Libreria Esterna

```bash
# 1. Setup progetto principale
mkdir webapp-project && cd webapp-project
git init
echo "# WebApp with External Libraries" > README.md
git add README.md
git commit -m "Initial commit"

# 2. Aggiungi libreria UI come subtree
git subtree add --prefix=assets/ui-library \
    https://github.com/company/ui-framework.git main --squash

# 3. Aggiungi utility library
git subtree add --prefix=src/utils \
    https://github.com/company/js-utils.git main --squash

# 4. Usa le librerie nel progetto
cat << 'EOF' > src/app.js
import { Button } from '../assets/ui-library/button.js';
import { formatDate } from './utils/date-helpers.js';

const app = new Button();
console.log(formatDate(new Date()));
EOF

git add src/app.js
git commit -m "Integrate external libraries in main app"

# 5. Setup remotes per updates futuri
git remote add ui-library https://github.com/company/ui-framework.git
git remote add utils-library https://github.com/company/js-utils.git
```

### Workflow 2: Monorepo con Subtree

```bash
# 1. Repository principale del monorepo
mkdir company-monorepo && cd company-monorepo
git init
echo "# Company Monorepo" > README.md
git add README.md && git commit -m "Initial commit"

# 2. Aggiungi progetti esistenti come subtree
git subtree add --prefix=frontend \
    https://github.com/company/frontend-app.git main --squash

git subtree add --prefix=backend \
    https://github.com/company/backend-api.git main --squash

git subtree add --prefix=mobile \
    https://github.com/company/mobile-app.git main --squash

# 3. Struttura risultante
tree -L 2
# .
# ├── README.md
# ├── frontend/
# │   ├── src/
# │   ├── package.json
# │   └── README.md
# ├── backend/
# │   ├── src/
# │   ├── pom.xml
# │   └── README.md
# └── mobile/
#     ├── src/
#     ├── package.json
#     └── README.md

# 4. Setup script per aggiornamenti
cat << 'EOF' > update-projects.sh
#!/bin/bash
echo "🔄 Updating all projects..."

git subtree pull --prefix=frontend \
    https://github.com/company/frontend-app.git main --squash

git subtree pull --prefix=backend \
    https://github.com/company/backend-api.git main --squash

git subtree pull --prefix=mobile \
    https://github.com/company/mobile-app.git main --squash

echo "✅ All projects updated!"
EOF

chmod +x update-projects.sh
```

### Workflow 3: Contribuire a Progetto Upstream

```bash
# 1. Hai modificato una libreria inclusa come subtree
cd vendor/json-parser
echo "// Performance improvement" >> parser.js
cd ../..

git add vendor/json-parser/parser.js
git commit -m "Improve JSON parser performance"

# 2. Contribuisci la modifica al progetto originale
# Crea branch nel repository originale
git subtree push --prefix=vendor/json-parser \
    https://github.com/company/json-parser.git feature/performance-improvement

# 3. Ora puoi creare PR nel repository originale
# Una volta merged, aggiorna il subtree
git subtree pull --prefix=vendor/json-parser \
    https://github.com/company/json-parser.git main --squash
```

## 🎯 Casi d'Uso Pratici

### Caso 1: Plugin System

```bash
# Sistema di plugin dove ogni plugin è un subtree
mkdir cms-with-plugins && cd cms-with-plugins
git init

# Core CMS
echo "# CMS Core" > README.md
mkdir core && echo "<?php // CMS Core" > core/cms.php
git add . && git commit -m "Initial CMS core"

# Aggiungi plugin come subtree
git subtree add --prefix=plugins/seo \
    https://github.com/cms-plugins/seo-plugin.git main --squash

git subtree add --prefix=plugins/cache \
    https://github.com/cms-plugins/cache-plugin.git main --squash

git subtree add --prefix=plugins/analytics \
    https://github.com/cms-plugins/analytics-plugin.git main --squash

# Struttura finale:
# cms-with-plugins/
# ├── core/
# │   └── cms.php
# └── plugins/
#     ├── seo/
#     ├── cache/
#     └── analytics/
```

### Caso 2: Documentation Aggregation

```bash
# Sito documentazione che aggrega docs da vari progetti
mkdir company-docs && cd company-docs
git init

# Setup base
echo "# Company Documentation Portal" > README.md
mkdir templates && echo "<!-- Base template -->" > templates/base.html
git add . && git commit -m "Initial docs setup"

# Aggiungi documentazione da vari progetti
git subtree add --prefix=docs/api \
    https://github.com/company/api-server.git main --squash

git subtree add --prefix=docs/frontend \
    https://github.com/company/webapp.git main --squash

git subtree add --prefix=docs/mobile \
    https://github.com/company/mobile-app.git main --squash

# Script per generare documentazione unificata
cat << 'EOF' > build-docs.sh
#!/bin/bash
echo "📚 Building unified documentation..."

# Update all docs
./update-all-docs.sh

# Build static site
mkdocs build

echo "✅ Documentation built successfully!"
EOF
```

### Caso 3: Vendor Dependencies

```bash
# Progetto che include dipendenze come subtree invece di package manager
mkdir custom-framework && cd custom-framework
git init

# Setup progetto base
echo "# Custom Framework" > README.md
mkdir src && echo "// Framework core" > src/framework.js
git add . && git commit -m "Initial framework"

# Aggiungi dipendenze come subtree
git subtree add --prefix=vendor/lodash \
    https://github.com/lodash/lodash.git 4.17.21 --squash

git subtree add --prefix=vendor/moment \
    https://github.com/moment/moment.git develop --squash

git subtree add --prefix=vendor/axios \
    https://github.com/axios/axios.git v1.6.0 --squash

# Crea script di build che usa le dipendenze
cat << 'EOF' > build.js
const fs = require('fs');
const path = require('path');

console.log('📦 Building framework with vendored dependencies...');

// Concatena tutte le dipendenze
const vendorFiles = [
    'vendor/lodash/lodash.min.js',
    'vendor/moment/min/moment.min.js', 
    'vendor/axios/dist/axios.min.js'
];

const frameworkCore = fs.readFileSync('src/framework.js', 'utf8');
const vendorCode = vendorFiles
    .map(file => fs.readFileSync(file, 'utf8'))
    .join('\n');

const bundle = vendorCode + '\n' + frameworkCore;
fs.writeFileSync('dist/framework-bundle.js', bundle);

console.log('✅ Framework built successfully!');
EOF
```

## 🔧 Comandi Avanzati e Scripting

### Script per Gestione Multiple Subtree

```bash
# subtree-manager.sh - Script completo per gestione subtree
#!/bin/bash

# Configurazione subtree nel repository
declare -A SUBTREES=(
    ["vendor/utils"]="https://github.com/company/utils.git main"
    ["libs/auth"]="https://github.com/company/auth-lib.git develop"
    ["plugins/cache"]="https://github.com/company/cache-plugin.git main"
)

# Funzione per aggiungere tutti i subtree
add_all_subtrees() {
    echo "📦 Adding all subtrees..."
    for prefix in "${!SUBTREES[@]}"; do
        IFS=' ' read -r repo branch <<< "${SUBTREES[$prefix]}"
        echo "Adding $prefix from $repo ($branch)"
        git subtree add --prefix="$prefix" "$repo" "$branch" --squash
    done
    echo "✅ All subtrees added!"
}

# Funzione per aggiornare tutti i subtree
update_all_subtrees() {
    echo "🔄 Updating all subtrees..."
    for prefix in "${!SUBTREES[@]}"; do
        IFS=' ' read -r repo branch <<< "${SUBTREES[$prefix]}"
        echo "Updating $prefix from $repo ($branch)"
        git subtree pull --prefix="$prefix" "$repo" "$branch" --squash
    done
    echo "✅ All subtrees updated!"
}

# Funzione per pushare modifiche a subtree specifico
push_subtree() {
    local prefix=$1
    local target_branch=$2
    
    if [[ -z "$prefix" ]] || [[ -z "$target_branch" ]]; then
        echo "Usage: push_subtree <prefix> <target-branch>"
        return 1
    fi
    
    if [[ -n "${SUBTREES[$prefix]}" ]]; then
        IFS=' ' read -r repo _ <<< "${SUBTREES[$prefix]}"
        echo "🚀 Pushing $prefix to $repo ($target_branch)"
        git subtree push --prefix="$prefix" "$repo" "$target_branch"
    else
        echo "❌ Subtree $prefix not found in configuration"
        return 1
    fi
}

# Funzione per mostrare status dei subtree
status_subtrees() {
    echo "📊 Subtree Status:"
    for prefix in "${!SUBTREES[@]}"; do
        if [[ -d "$prefix" ]]; then
            echo "✅ $prefix - Present"
        else
            echo "❌ $prefix - Missing"
        fi
    done
}

# Parse argomenti comando
case "$1" in
    "add")
        add_all_subtrees
        ;;
    "update")
        update_all_subtrees
        ;;
    "push")
        push_subtree "$2" "$3"
        ;;
    "status")
        status_subtrees
        ;;
    *)
        echo "Usage: $0 {add|update|push <prefix> <branch>|status}"
        exit 1
        ;;
esac
```

### Configurazione Git Aliases

```bash
# Aggiungi aliases utili per subtree
git config --global alias.sbt-add 'subtree add --squash'
git config --global alias.sbt-pull 'subtree pull --squash'
git config --global alias.sbt-push 'subtree push'

# Uso degli aliases
git sbt-add --prefix=vendor/lib https://github.com/company/lib.git main
git sbt-pull --prefix=vendor/lib https://github.com/company/lib.git main
git sbt-push --prefix=vendor/lib https://github.com/company/lib.git feature-branch
```

### Automation con Git Hooks

```bash
# .git/hooks/pre-push - Verifica subtree prima di push
#!/bin/bash

echo "🔍 Checking subtrees before push..."

# Lista dei subtree nel progetto
SUBTREE_DIRS=("vendor/utils" "libs/auth" "plugins/cache")

for dir in "${SUBTREE_DIRS[@]}"; do
    if [[ -d "$dir" ]]; then
        # Verifica che il subtree non abbia modifiche non committate
        if [[ -n "$(git status --porcelain $dir)" ]]; then
            echo "❌ Subtree $dir has uncommitted changes"
            echo "Please commit or stash changes in subtree before pushing"
            exit 1
        fi
    fi
done

echo "✅ All subtrees are clean"
exit 0
```

## ⚠️ Errori Comuni e Soluzioni

### 1. Conflitti durante Subtree Pull

```bash
# ❌ ERRORE: Conflitti durante pull del subtree
git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash
# CONFLICT (content): Merge conflict in vendor/utils/helper.js

# ✅ SOLUZIONE: Risolvi conflitti manualmente
git status
# Edit conflicted files
nano vendor/utils/helper.js
# Risolvi markers <<<< ==== >>>>
git add vendor/utils/helper.js
git commit -m "Resolve conflicts in utils subtree"
```

### 2. Wrong Directory per Subtree Add

```bash
# ❌ ERRORE: Aggiunto subtree nella directory sbagliata
git subtree add --prefix=wrong-dir https://github.com/company/lib.git main --squash

# ✅ SOLUZIONE: Sposta i files e refactor
git mv wrong-dir/ correct-dir/
git commit -m "Move subtree to correct directory"

# Oppure rimuovi e ri-aggiungi (più pulito)
git rm -r wrong-dir/
git commit -m "Remove incorrectly placed subtree"
git subtree add --prefix=correct-dir https://github.com/company/lib.git main --squash
```

### 3. Subtree Push Fallisce

```bash
# ❌ ERRORE: Push subtree fallisce per permessi
git subtree push --prefix=vendor/lib https://github.com/company/lib.git feature-branch
# Permission denied

# ✅ SOLUZIONE: Verifica permessi e branch
# 1. Controlla di avere permessi di push al repo
# 2. Crea il branch nel repo remoto se non esiste
git ls-remote --heads https://github.com/company/lib.git feature-branch

# 3. Usa fork se non hai permessi diretti
git subtree push --prefix=vendor/lib https://github.com/yourusername/lib.git feature-branch
```

### 4. Cronologia Confusa

```bash
# ❌ PROBLEMA: Cronologia troppo confusa con subtree merges
git log --oneline
# Troppi merge commits da subtree

# ✅ SOLUZIONE: Usa --squash per subtree più puliti
# Per nuovi subtree:
git subtree add --prefix=new-lib https://github.com/company/new-lib.git main --squash

# Per cleanup cronologia esistente (se necessario e sicuro):
git rebase -i HEAD~20  # Interactive rebase per pulire
```

## 💡 Best Practices

### 1. Naming Conventions

```bash
# ✅ USA prefissi chiari e consistenti
vendor/          # Dipendenze esterne
libs/            # Librerie interne
plugins/         # Plugin modulari
external/        # Progetti esterni
third-party/     # Codice di terze parti

# ❌ EVITA nomi generici
stuff/
code/
other/
temp/
```

### 2. Documentation Strategy

```markdown
<!-- README.md -->
## Subtree Dependencies

Questo progetto include i seguenti subtree:

| Directory | Repository | Branch | Purpose |
|-----------|------------|--------|---------|
| `vendor/utils` | [company/utils](https://github.com/company/utils) | `main` | Utility functions |
| `libs/auth` | [company/auth-lib](https://github.com/company/auth-lib) | `develop` | Authentication library |
| `plugins/cache` | [company/cache-plugin](https://github.com/company/cache-plugin) | `main` | Caching system |

### Updating Subtrees

```bash
# Update all subtrees
./scripts/update-subtrees.sh

# Update specific subtree
git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash
```

### Contributing Back

```bash
# Make changes in subtree
# Commit changes
# Push to upstream
git subtree push --prefix=vendor/utils https://github.com/company/utils.git feature/improvement
```
```

### 3. Versioning Strategy

```bash
# ✅ USA tag specifici per subtree stabili
git subtree add --prefix=vendor/stable-lib \
    https://github.com/company/stable-lib.git v2.1.0 --squash

# ✅ DOCUMENTA versioni nel commit message
git commit -m "Add stable-lib v2.1.0 as subtree

- Adds vendor/stable-lib from https://github.com/company/stable-lib.git
- Version: v2.1.0
- Includes: Bug fixes and performance improvements"

# ✅ MANTIENI log delle versioni
echo "vendor/stable-lib: v2.1.0 (2023-12-01)" >> SUBTREE_VERSIONS.md
```

### 4. CI/CD Integration

```yaml
# .github/workflows/subtree-sync.yml
name: Sync Subtrees

on:
  schedule:
    - cron: '0 2 * * 1'  # Weekly on Monday at 2 AM
  workflow_dispatch:      # Manual trigger

jobs:
  sync-subtrees:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
      with:
        fetch-depth: 0  # Needed for subtree operations
        
    - name: Update subtrees
      run: |
        git config user.name "github-actions[bot]"
        git config user.email "github-actions[bot]@users.noreply.github.com"
        
        # Update each subtree
        git subtree pull --prefix=vendor/utils https://github.com/company/utils.git main --squash
        git subtree pull --prefix=libs/auth https://github.com/company/auth-lib.git develop --squash
        
    - name: Create PR if changes
      run: |
        if ! git diff-index --quiet HEAD --; then
          git checkout -b update-subtrees-$(date +%Y%m%d)
          git push origin update-subtrees-$(date +%Y%m%d)
          # Create PR using GitHub CLI or API
        fi
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è il principale vantaggio dei subtree rispetto ai submodules?**

<details>
<summary>Risposta</summary>

I **subtree** sono completamente integrati nel repository principale, quindi un semplice `git clone` include tutto il codice necessario. Non serve configurazione speciale o comandi aggiuntivi come con i submodules. Tutti i tool Git standard funzionano senza problemi.
</details>

### Domanda 2
**Quando dovresti usare `--squash` con git subtree?**

<details>
<summary>Risposta</summary>

Usa `--squash` quando vuoi mantenere la cronologia pulita e non hai bisogno della cronologia dettagliata del repository esterno. Senza `--squash`, tutti i commit del repository esterno vengono importati, rendendo la cronologia più confusa ma preservando informazioni complete.
</details>

### Domanda 3
**Come contribuisci modifiche a un repository upstream tramite subtree?**

<details>
<summary>Risposta</summary>

```bash
# 1. Fai modifiche nella directory del subtree
# 2. Commit nel repository principale
git add vendor/library/
git commit -m "Improve library function"

# 3. Push al repository upstream
git subtree push --prefix=vendor/library https://github.com/company/library.git feature-branch

# 4. Crea PR nel repository upstream
```
</details>

### Domanda 4
**Qual è lo svantaggio principale dei subtree?**

<details>
<summary>Risposta</summary>

Il principale svantaggio è l'**aumento delle dimensioni del repository** poiché tutto il codice del subtree viene incorporato completamente. Inoltre, la cronologia può diventare confusa con molti merge commits se non si usa `--squash`.
</details>

## 🛠️ Esercizio Pratico: Progetto con Subtree Dependencies

### Parte 1: Setup Progetto Base

```bash
# 1. Crea progetto principale
mkdir blog-platform && cd blog-platform
git init
echo "# Piattaforma Blog con Librerie Esterne" > README.md

# 2. Struttura base del progetto
mkdir -p src/{frontend,backend} public docs
echo "// Entry point app frontend" > src/frontend/app.js
echo "// Server API backend" > src/backend/server.js
echo "<h1>Piattaforma Blog</h1>" > public/index.html

git add .
git commit -m "Struttura iniziale piattaforma blog"

# 3. Setup repository remoto simulato
git remote add origin https://github.com/company/blog-platform.git
```

### Parte 2: Aggiunta Dependencies come Subtree

```bash
# 4. Aggiungi UI framework come subtree
git subtree add --prefix=src/frontend/ui-framework \
    https://github.com/twbs/bootstrap.git v5.3.0 --squash

# 5. Aggiungi utility library per backend
git subtree add --prefix=src/backend/utils \
    https://github.com/lodash/lodash.git 4.17.21 --squash

# 6. Aggiungi documentazione template
git subtree add --prefix=docs/template \
    https://github.com/docsifyjs/docsify.git develop --squash

# 7. Verifica struttura finale
tree -L 3
```

### Parte 3: Integrazione e Customizzazione

```bash
# 8. Crea file di configurazione che usa i subtree
cat << 'EOF' > src/frontend/config.js
// Import da UI framework subtree
import 'ui-framework/dist/css/bootstrap.min.css';
import 'ui-framework/dist/js/bootstrap.bundle.min.js';

console.log('Blog platform frontend initialized');
EOF

cat << 'EOF' > src/backend/app.js
// Import da utility subtree
const _ = require('./utils/lodash.min.js');

const users = [
    { name: 'Alice', age: 30 },
    { name: 'Bob', age: 25 }
];

const sortedUsers = _.sortBy(users, 'age');
console.log('Sorted users:', sortedUsers);
EOF

git add src/
git commit -m "Integra dipendenze esterne nell'app principale"

# 9. Setup script per aggiornamenti futuri
cat << 'EOF' > update-dependencies.sh
#!/bin/bash
echo "🔄 Aggiornamento tutte le dipendenze..."

# Update UI framework
echo "📦 Aggiornamento UI framework..."
git subtree pull --prefix=src/frontend/ui-framework \
    https://github.com/twbs/bootstrap.git v5.3.0 --squash

# Update utility library  
echo "🛠️  Aggiornamento utility library..."
git subtree pull --prefix=src/backend/utils \
    https://github.com/lodash/lodash.git 4.17.21 --squash

# Update docs template
echo "📚 Aggiornamento documentazione template..."
git subtree pull --prefix=docs/template \
    https://github.com/docsifyjs/docsify.git develop --squash

echo "✅ Tutte le dipendenze aggiornate con successo!"
EOF

chmod +x update-dependencies.sh

# 10. Test script
./update-dependencies.sh
```

### Parte 4: Gestione Updates

```bash
# 11. Simula miglioramento alla UI framework
cd src/frontend/ui-framework
echo "/* Miglioramento per supporto mobile */" >> scss/_variables.scss
cd ../../..

git add src/frontend/ui-framework/scss/_variables.scss
git commit -m "Migliora supporto mobile nella UI framework

- Aggiunti variabili personalizzate per responsività
- Ottimizzazioni per dispositivi mobili"

# 12. Prepara contribuzione (simulata)
echo "# Per contribuire questa modifica a Bootstrap:"
echo "git subtree push --prefix=src/frontend/ui-framework https://github.com/company/bootstrap-fork.git feature/mobile-improvements"

# 13. Documenta le dipendenze
cat << 'EOF' > DEPENDENCIES.md
# Dipendenze Piattaforma Blog

## Subtree Dependencies

### UI Framework
- **Path**: `src/frontend/ui-framework/`
- **Source**: [Bootstrap v5.3.0](https://github.com/twbs/bootstrap/tree/v5.3.0)
- **Purpose**: CSS framework for responsive UI
- **Last Updated**: $(date)

### Utility Library
- **Path**: `src/backend/utils/`
- **Source**: [Lodash 4.17.21](https://github.com/lodash/lodash/tree/4.17.21)
- **Purpose**: JavaScript utility functions
- **Last Updated**: $(date)

### Documentation Template
- **Path**: `docs/template/`
- **Source**: [Docsify](https://github.com/docsifyjs/docsify)
- **Purpose**: Documentation site generator
- **Last Updated**: $(date)

## Updating Dependencies

Run the update script:
```bash
./scripts/update-dependencies.sh
```

## Contributing Back

To contribute improvements to upstream projects:
```bash
git subtree push --prefix=<subtree-path> <upstream-repo> <feature-branch>
```
EOF

git add DEPENDENCIES.md scripts/
git commit -m "Aggiungi documentazione dipendenze e script di aggiornamento"

# 14. Crea script di validazione
cat << 'EOF' > scripts/validate-subtrees.sh
#!/bin/bash

echo "🔍 Validating subtree integrity..."

REQUIRED_SUBTREES=(
    "src/frontend/ui-framework"
    "src/backend/utils" 
    "docs/template"
)

for subtree in "${REQUIRED_SUBTREES[@]}"; do
    if [[ -d "$subtree" ]] && [[ -n "$(ls -A $subtree)" ]]; then
        echo "✅ $subtree - OK"
    else
        echo "❌ $subtree - MISSING or EMPTY"
    fi
done

echo "📊 Repository size:"
du -sh .git/
du -sh .

echo "🎯 Validation complete!"
EOF

chmod +x scripts/validate-subtrees.sh

# 15. Test validazione
./scripts/validate-subtrees.sh

# 16. Final commit
git add scripts/validate-subtrees.sh
git commit -m "Aggiungi script di validazione subtree

- Controlla integrità di tutte le dipendenze subtree
- Riporta impatto sulla dimensione del repository
- Parte del workflow di sviluppo"

# 17. Mostra cronologia finale
git log --oneline --graph -10
```

## 🤖 Esempio Completo: Repository Robotica con Corsi

### Scenario Reale: Robotica Educational Platform

Creeremo un progetto di robotica educativa che integra due corsi specializzati come subtree:
- **Repository principale**: `robotica` - Piattaforma principale con progetti robotici
- **Subtree 1**: `corso-docker` - Corso su containerizzazione per IoT
- **Subtree 2**: `corso-nodejs` - Corso su sviluppo backend per sensori

```
robotica/                           # Repository principale
├── README.md
├── progetti/                       # Progetti robotici principali
│   ├── arduino-sensors/
│   ├── raspberry-pi-gateway/
│   └── esp32-automation/
├── docs/                          # Documentazione generale
├── corsi/                         # Subtree directory
│   ├── docker/                    ← Subtree da corso-docker
│   │   ├── README.md
│   │   ├── esempi/
│   │   ├── laboratori/
│   │   └── dockerfile-templates/
│   └── nodejs/                    ← Subtree da corso-nodejs
│       ├── README.md
│       ├── api/
│       ├── webapp/
│       └── package.json
└── scripts/                       # Script di gestione
    └── setup-environment.sh
```

### Fase 1: Creazione dei Repository GitHub

```bash
# 1. Repository "corso-docker" - Corso containerizzazione
mkdir corso-docker && cd corso-docker
git init
echo "# Corso Docker per Robotica e IoT" > README.md

# Struttura del corso Docker
mkdir -p esempi/{basic,robotics,iot}
mkdir -p laboratori/{lab1,lab2,lab3}

# Dockerfile per ambiente robotica
cat << 'EOF' > esempi/robotics/Dockerfile
FROM ubuntu:22.04

# Installa dipendenze per robotica
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    arduino-cli \
    nodejs \
    npm \
    && rm -rf /var/lib/apt/lists/*

# Librerie Python per sensori
RUN pip3 install pyserial adafruit-circuitpython-motor

WORKDIR /workspace
CMD ["bash"]
EOF

# Docker Compose per stack IoT
cat << 'EOF' > esempi/iot/docker-compose.yml
version: '3.8'
services:
  mqtt-broker:
    image: eclipse-mosquitto:2.0
    ports:
      - "1883:1883"
      - "9001:9001"
    volumes:
      - ./mosquitto.conf:/mosquitto/config/mosquitto.conf

  influxdb:
    image: influxdb:2.0
    ports:
      - "8086:8086"
    environment:
      - INFLUXDB_DB=sensors
      - INFLUXDB_ADMIN_USER=admin
      - INFLUXDB_ADMIN_PASSWORD=password

  grafana:
    image: grafana/grafana:latest
    ports:
      - "3000:3000"
    depends_on:
      - influxdb
EOF

# Laboratorio pratico
cat << 'EOF' > laboratori/lab1/README.md
# Lab 1: Containerizzare un'applicazione Arduino

## Obiettivo
Creare un container per sviluppo Arduino con sensori.

## Istruzioni
1. Costruire l'immagine Docker
2. Configurare accesso ai dispositivi USB
3. Testare compilazione sketch Arduino

## Esercizio
Containerizzare il progetto sensore ultrasuoni + LED.
EOF

git add .
git commit -m "Initial Docker course structure with robotics examples"

# Simula push su GitHub
echo "git remote add origin https://github.com/company/corso-docker.git"
echo "git push -u origin main"

# 2. Repository "corso-nodejs" - Corso API e Web per robotica
cd .. && mkdir corso-nodejs && cd corso-nodejs
git init
echo "# Corso Node.js per Robotica e IoT" > README.md

# Struttura del corso Node.js
mkdir -p api/{mqtt,sensors,database}
mkdir -p webapp/{dashboard,control-panel}
mkdir -p examples/{basic,advanced}

# API per sensori MQTT
cat << 'EOF' > api/mqtt/sensor-listener.js
const mqtt = require('mqtt');
const express = require('express');
const app = express();

// Connessione MQTT broker
const client = mqtt.connect('mqtt://localhost:1883');

let sensorData = {
    temperature: 0,
    humidity: 0,
    distance: 0,
    timestamp: new Date()
};

// Listener per dati sensori
client.on('connect', () => {
    console.log('📡 Connected to MQTT broker');
    client.subscribe('sensors/+/data');
});

client.on('message', (topic, message) => {
    const data = JSON.parse(message.toString());
    const sensorType = topic.split('/')[1];
    
    sensorData[sensorType] = data.value;
    sensorData.timestamp = new Date();
    
    console.log(`📊 ${sensorType}: ${data.value}`);
});

// API REST per dati sensori
app.get('/api/sensors/current', (req, res) => {
    res.json(sensorData);
});

app.get('/api/sensors/history/:type', (req, res) => {
    // Implementare recupero dati storici
    res.json({ message: 'Historical data endpoint' });
});

app.listen(3001, () => {
    console.log('🚀 Sensor API running on port 3001');
});
EOF

# Web dashboard per controllo robot
cat << 'EOF' > webapp/dashboard/index.html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Robot Control Dashboard</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        .sensor-panel { 
            background: #f0f0f0; 
            padding: 20px; 
            margin: 10px 0; 
            border-radius: 8px; 
        }
        .control-btn { 
            background: #007bff; 
            color: white; 
            border: none; 
            padding: 10px 20px; 
            margin: 5px; 
            border-radius: 4px; 
            cursor: pointer; 
        }
        .control-btn:hover { background: #0056b3; }
        .sensor-value { font-size: 24px; font-weight: bold; color: #17a2b8; }
        .position-display { 
            background: #343a40; padding: 15px; border-radius: 8px; 
            display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 10px; text-align: center;
        }
        .log { background: #000; padding: 10px; border-radius: 4px; height: 200px; overflow-y: scroll; font-family: monospace; }
        .emergency-stop { background: #dc3545 !important; font-size: 18px; font-weight: bold; }
    </style>
</head>
<body>
    <h1>🤖 Robot Control Dashboard</h1>
    
    <div class="panel">
        <h3>🔗 Connessione: <span id="connectionStatus" class="status-offline">Disconnesso</span></h3>
        <p>Ultimo aggiornamento: <span id="lastUpdate">--</span></p>
    </div>

    <div class="panel">
        <h3>📍 Posizione Robot</h3>
        <div class="position-display">
            <div>X: <div class="sensor-value" id="posX">0</div></div>
            <div>Y: <div class="sensor-value" id="posY">0</div></div>
            <div>Angolo: <div class="sensor-value" id="posAngle">0°</div></div>
        </div>
    </div>

    <div class="panel">
        <h3>📊 Sensori</h3>
        <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 20px;">
            <div>Distanza: <span class="sensor-value" id="sensorDistance">--</span> cm</div>
            <div>Temperatura: <span class="sensor-value" id="sensorTemp">--</span>°C</div>
        </div>
    </div>

    <div class="panel">
        <h3>🎮 Controllo Robot</h3>
        <div style="text-align: center;">
            <div>
                <button class="control-btn" onclick="sendCommand('forward', {speed: 100})">⬆️ Avanti</button>
            </div>
            <div>
                <button class="control-btn" onclick="sendCommand('left', {speed: 80})">⬅️ Sinistra</button>
                <button class="control-btn emergency-stop" onclick="emergencyStop()">🛑 STOP</button>
                <button class="control-btn" onclick="sendCommand('right', {speed: 80})">➡️ Destra</button>
            </div>
            <div>
                <button class="control-btn" onclick="sendCommand('backward', {speed: 100})">⬇️ Indietro</button>
            </div>
        </div>
        
        <div style="margin-top: 20px; text-align: center;">
            <button class="control-btn" onclick="sendCommand('rotate', {angle: -90})">↺ Ruota SX</button>
            <button class="control-btn" onclick="sendCommand('auto-patrol')">🔄 Pattuglia Auto</button>
            <button class="control-btn" onclick="sendCommand('rotate', {angle: 90})">↻ Ruota DX</button>
        </div>
    </div>

    <div class="panel">
        <h3>📋 Log Attività</h3>
        <div class="log" id="activityLog"></div>
    </div>

    <script>
        // Connessione WebSocket
        const socket = io('http://localhost:3002');
        
        // Elementi DOM
        const connectionStatus = document.getElementById('connectionStatus');
        const lastUpdate = document.getElementById('lastUpdate');
        const activityLog = document.getElementById('activityLog');
        
        // Gestione connessione
        socket.on('connect', () => {
            connectionStatus.textContent = 'Connesso';
            connectionStatus.className = 'status-online';
            log('✅ Connesso al server WebSocket');
        });
        
        socket.on('disconnect', () => {
            connectionStatus.textContent = 'Disconnesso';
            connectionStatus.className = 'status-offline';
            log('❌ Disconnesso dal server');
        });
        
        // Aggiornamenti stato robot
        socket.on('robot-state', (state) => {
            updateRobotDisplay(state);
            lastUpdate.textContent = new Date(state.lastUpdate).toLocaleTimeString();
        });
        
        // Conferma comandi
        socket.on('command-ack', (ack) => {
            if (ack.success) {
                log(`✅ Comando "${ack.command}" eseguito`);
            } else {
                log(`❌ Comando "${ack.command}" fallito: ${ack.error}`);
            }
        });
        
        // Aggiorna display robot
        function updateRobotDisplay(state) {
            document.getElementById('posX').textContent = state.position.x.toFixed(1);
            document.getElementById('posY').textContent = state.position.y.toFixed(1);
            document.getElementById('posAngle').textContent = state.position.angle.toFixed(0) + '°';
            
            document.getElementById('sensorDistance').textContent = state.sensors.distance || '--';
            document.getElementById('sensorTemp').textContent = state.sensors.temperature || '--';
        }
        
        // Invia comando robot
        function sendCommand(action, params = {}) {
            const command = { action, params };
            socket.emit('robot-command', command);
            log(`🤖 Invio comando: ${action}`);
        }
        
        // Stop di emergenza
        function emergencyStop() {
            sendCommand('emergency-stop');
            log('🚨 STOP DI EMERGENZA ATTIVATO');
        }
        
        // Aggiungi messaggio al log
        function log(message) {
            const timestamp = new Date().toLocaleTimeString();
            activityLog.innerHTML += `<div>[${timestamp}] ${message}</div>`;
            activityLog.scrollTop = activityLog.scrollHeight;
        }
        
        // Controllo da tastiera
        document.addEventListener('keydown', (event) => {
            switch(event.key) {
                case 'ArrowUp': 
                case 'w': sendCommand('forward', {speed: 100}); break;
                case 'ArrowDown': 
                case 's': sendCommand('backward', {speed: 100}); break;
                case 'ArrowLeft': 
                case 'a': sendCommand('left', {speed: 80}); break;
                case 'ArrowRight': 
                case 'd': sendCommand('right', {speed: 80}); break;
                case ' ': 
                case 'Escape': emergencyStop(); event.preventDefault(); break;
            }
        });
        
        log('🚀 Dashboard inizializzata - Usa WASD o frecce per controllare il robot');
    </script>
</body>
</html>
EOF

git add .
git commit -m "Add real-time WebSocket control system

- WebSocket server for real-time robot communication
- Enhanced dashboard with live position tracking
- Keyboard control support (WASD + arrows)
- Emergency stop functionality
- Activity logging and connection status
- MQTT bridge for robot commands and status"

# Simula push
echo "git push origin main"

# SCENARIO 3: Aggiornamento nel progetto principale
cd ../robotica

# Aggiorna entrambi i subtree
echo "🔄 Aggiornamento di tutti i corsi..."

git subtree pull --prefix=corsi/docker \
    https://github.com/company/corso-docker.git main --squash

git subtree pull --prefix=corsi/nodejs \
    https://github.com/company/corso-nodejs.git main --squash

# Aggiungi integrazione tra i corsi
cat << 'EOF' > progetti/integrated-demo/docker-compose.yml
version: '3.8'
services:
  # Servizi da corso Docker
  mqtt-broker:
    image: eclipse-mosquitto:2.0
    ports:
      - "1883:1883"
      - "9001:9001"
    volumes:
      - ./mosquitto.conf:/mosquitto/config/mosquitto.conf

  influxdb:
    image: influxdb:2.0
    ports:
      - "8086:8086"
    environment:
      - INFLUXDB_DB=sensors
      - INFLUXDB_ADMIN_USER=admin
      - INFLUXDB_ADMIN_PASSWORD=password

  grafana:
    image: grafana/grafana:latest
    ports:
      - "3000:3000"
    depends_on:
      - influxdb

  # Servizi da corso Node.js
  api-server:
    build: 
      context: ../../corsi/nodejs
      dockerfile: Dockerfile
    ports:
      - "3001:3001"
    environment:
      - MQTT_BROKER=mqtt-broker
      - INFLUX_URL=http://influxdb:8086
    depends_on:
      - mqtt-broker
      - influxdb

  websocket-server:
    build: 
      context: ../../corsi/nodejs
      dockerfile: Dockerfile.websocket
    ports:
      - "3002:3002"
    environment:
      - MQTT_BROKER=mqtt-broker
    depends_on:
      - mqtt-broker

  # Dashboard web
  dashboard:
    image: nginx:alpine
    ports:
      - "8080:80"
    volumes:
      - ../../corsi/nodejs/webapp/dashboard:/usr/share/nginx/html:ro
    depends_on:
      - api-server
      - websocket-server
EOF

# Script di automazione subtree
cat << 'EOF' > scripts/manage-subtrees.sh
#!/bin/bash
set -e

# Configurazione subtree
declare -A SUBTREES=(
    ["corsi/docker"]="https://github.com/company/corso-docker.git main"
    ["corsi/nodejs"]="https://github.com/company/corso-nodejs.git main"
)

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log() {
    echo -e "${BLUE}[$(date +'%H:%M:%S')]${NC} $1"
}

success() {
    echo -e "${GREEN}✅ $1${NC}"
}

warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

error() {
    echo -e "${RED}❌ $1${NC}"
}

# Aggiorna tutti i subtree
update_all_subtrees() {
    log "Aggiornamento di tutti i subtree..."
    
    for prefix in "${!SUBTREES[@]}"; do
        IFS=' ' read -r repo branch <<< "${SUBTREES[$prefix]}"
        
        log "Aggiornamento $prefix da $repo ($branch)"
        
        if git subtree pull --prefix="$prefix" "$repo" "$branch" --squash; then
            success "Subtree $prefix aggiornato"
        else
            error "Errore aggiornamento subtree $prefix"
            
            # Gestione conflitti
            if git status --porcelain | grep -q "^UU"; then
                warning "Conflitti rilevati in $prefix"
                echo "Risolvi i conflitti manualmente e poi esegui:"
                echo "  git add $prefix"
                echo "  git commit -m 'Resolve conflicts in $prefix subtree'"
                return 1
            fi
        fi
    done
    
    success "Tutti i subtree aggiornati!"
}

# Push modifiche a subtree specifico
push_subtree_changes() {
    local prefix=$1
    local target_branch=$2
    
    if [[ -z "$prefix" ]] || [[ -z "$target_branch" ]]; then
        error "Uso: push_subtree_changes <prefix> <target-branch>"
        return 1
    fi
    
    if [[ -n "${SUBTREES[$prefix]}" ]]; then
        IFS=' ' read -r repo _ <<< "${SUBTREES[$prefix]}"
        
        log "Push modifiche da $prefix a $repo ($target_branch)"
        
        if git subtree push --prefix="$prefix" "$repo" "$target_branch"; then
            success "Modifiche pushate a $repo"
            log "Ora puoi creare una PR da $target_branch a main"
        else
            error "Errore durante push a $repo"
        fi
    else
        error "Subtree $prefix non trovato nella configurazione"
        return 1
    fi
}

# Mostra status subtree
show_subtree_status() {
    log "Status dei subtree nel progetto:"
    echo
    
    for prefix in "${!SUBTREES[@]}"; do
        IFS=' ' read -r repo branch <<< "${SUBTREES[$prefix]}"
        
        if [[ -d "$prefix" ]]; then
            local file_count=$(find "$prefix" -type f | wc -l)
            local last_commit=$(git log --oneline -1 --grep="$prefix" || echo "N/A")
            
            success "$prefix"
            echo "  📂 Files: $file_count"
            echo "  🔗 Source: $repo ($branch)"
            echo "  📝 Last subtree commit: ${last_commit:0:50}"
        else
            error "$prefix - Directory non trovata"
        fi
        echo
    done
}

# Backup prima di updates
backup_subtrees() {
    local backup_dir="/tmp/robotica-subtrees-backup-$(date +%Y%m%d-%H%M%S)"
    
    log "Creazione backup subtree in $backup_dir"
    mkdir -p "$backup_dir"
    
    for prefix in "${!SUBTREES[@]}"; do
        if [[ -d "$prefix" ]]; then
            cp -r "$prefix" "$backup_dir/"
            success "Backup di $prefix completato"
        fi
    done
    
    echo "📦 Backup salvato in: $backup_dir"
}

# Verifica integrità subtree
verify_subtree_integrity() {
    log "Verifica integrità subtree..."
    
    for prefix in "${!SUBTREES[@]}"; do
        if [[ -d "$prefix" ]]; then
            # Verifica che non ci siano modifiche uncommitted
            if [[ -n "$(git status --porcelain $prefix)" ]]; then
                warning "$prefix ha modifiche non committate"
                git status --porcelain "$prefix"
            else
                success "$prefix è pulito"
            fi
        fi
    done
}

# Menu interattivo
show_menu() {
    echo
    echo "🤖 Gestione Subtree - Progetto Robotica"
    echo "======================================"
    echo "1. Aggiorna tutti i subtree"
    echo "2. Status subtree"
    echo "3. Verifica integrità"
    echo "4. Backup subtree"
    echo "5. Push modifiche a subtree"
    echo "6. Mostra configurazione"
    echo "0. Esci"
    echo
}

# Parse argomenti
case "${1:-menu}" in
    "update")
        update_all_subtrees
        ;;
    "status")
        show_subtree_status
        ;;
    "verify")
        verify_subtree_integrity
        ;;
    "backup")
        backup_subtrees
        ;;
    "push")
        push_subtree_changes "$2" "$3"
        ;;
    "config")
        echo "📋 Configurazione Subtree:"
        for prefix in "${!SUBTREES[@]}"; do
            echo "  $prefix -> ${SUBTREES[$prefix]}"
        done
        ;;
    "menu")
        while true; do
            show_menu
            read -p "Scegli opzione: " choice
            
            case $choice in
                1) update_all_subtrees ;;
                2) show_subtree_status ;;
                3) verify_subtree_integrity ;;
                4) backup_subtrees ;;
                5) 
                    read -p "Subtree prefix: " prefix
                    read -p "Target branch: " branch
                    push_subtree_changes "$prefix" "$branch"
                    ;;
                6) 
                    echo "📋 Configurazione Subtree:"
                    for prefix in "${!SUBTREES[@]}"; do
                        echo "  $prefix -> ${SUBTREES[$prefix]}"
                    done
                    ;;
                0) exit 0 ;;
                *) error "Opzione non valida" ;;
            esac
            
            echo
            read -p "Premi Enter per continuare..."
        done
        ;;
    *)
        echo "Uso: $0 {update|status|verify|backup|push <prefix> <branch>|config|menu}"
        exit 1
        ;;
esac
EOF

chmod +x scripts/manage-subtrees.sh

git add .
git commit -m "Integrate updated courses and add advanced subtree management

- Updated Docker course with Kubernetes examples
- Updated Node.js course with WebSocket real-time control
- Added integrated demo with full Docker Compose stack
- Advanced subtree management script with backup and conflict resolution
- Interactive menu system for course maintenance
- Complete IoT/robotics educational platform ready for production"

echo "✅ Esempio completo creato!"
echo
echo "🎯 Riepilogo Progetto Robotica:"
echo "  📦 Repository principale: robotica"
echo "  📚 Subtree 1: corsi/docker (Kubernetes, containerizzazione)"
echo "  📚 Subtree 2: corsi/nodejs (WebSocket, API real-time)"
echo "  🛠️  Script gestione: scripts/manage-subtrees.sh"
echo "  🚀 Demo integrata: progetti/integrated-demo/"
```

### Fase 4: Workflow di Manutenzione

```bash
# Script per manutenzione regolare
cat << 'EOF' > scripts/maintenance-workflow.sh
#!/bin/bash

echo "🔧 Workflow Manutenzione Progetto Robotica"

# 1. Verifica repository
echo "📋 1. Verifica stato repository..."
git status --porcelain
if [[ $? -eq 0 ]]; then
    echo "✅ Repository pulito"
else
    echo "⚠️  Repository ha modifiche uncommitted"
fi

# 2. Backup automatico
echo "📦 2. Backup subtree..."
./scripts/manage-subtrees.sh backup

# 3. Aggiornamento subtree
echo "🔄 3. Aggiornamento subtree..."
./scripts/manage-subtrees.sh update

# 4. Test integrazione
echo "🧪 4. Test integrazione..."
if [[ -f "progetti/integrated-demo/docker-compose.yml" ]]; then
    cd progetti/integrated-demo
    docker-compose config --quiet
    if [[ $? -eq 0 ]]; then
        echo "✅ Docker Compose configurazione valida"
    else
        echo "❌ Errore configurazione Docker Compose"
    fi
    cd ../..
fi

# 5. Verifica dipendenze Node.js
echo "📦 5. Verifica dipendenze Node.js..."
if [[ -f "corsi/nodejs/package.json" ]]; then
    cd corsi/nodejs
    npm audit --audit-level moderate
    cd ../..
fi

# 6. Documenta aggiornamenti
echo "📝 6. Documenta aggiornamenti..."
echo "Manutenzione eseguita il $(date)" >> MAINTENANCE.log
git log --oneline -5 --grep="subtree" >> MAINTENANCE.log

echo "🎉 Manutenzione completata!"
EOF

chmod +x scripts/maintenance-workflow.sh
```

Questo esempio completo mostra:

1. **Repository separati** con contenuti realistici per robotica educativa
2. **Integrazione subtree** nel progetto principale  
3. **Scenari di aggiornamento** con esempi concreti
4. **Script di automazione** per gestione semplificata
5. **Workflow di manutenzione** per uso professionale

Il progetto include esempi pratici di:
- Arduino con sensori e MQTT
- Docker per containerizzazione robotica  
- Node.js con WebSocket per controllo real-time
- Dashboard web interattive
- Gateway IoT Python
- Orchestrazione Kubernetes

Gli studenti possono usare questo esempio per comprendere sia i subtree Git che le tecnologie moderne per robotica e IoT.
