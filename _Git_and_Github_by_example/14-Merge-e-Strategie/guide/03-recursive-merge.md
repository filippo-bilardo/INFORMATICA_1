# 03 - Recursive Merge: Gestione Merge Complessi

## 📖 Cos'è un Recursive Merge

Il Recursive Merge (o Three-Way Merge) è il tipo di merge che Git utilizza quando entrambi i branch hanno commit aggiuntivi dopo la divergenza. Questo crea un commit di merge che unifica le modifiche di entrambi i branch, preservando la cronologia completa.

## 🔄 Meccanismo Three-Way Merge

### Situazione Tipica

```bash
# Situazione che richiede recursive merge
main:     A---B---C---F---G
               \
feature:        D---E
```

**Cosa succede**:
- `main` ha commit `F` e `G` dopo la divergenza
- `feature` ha commit `D` e `E`
- Git deve trovare un modo per unire entrambe le serie di modifiche

### Processo di Three-Way Merge

```bash
# 1. Git identifica il merge base (commit C)
git merge-base main feature  # Output: commit C

# 2. Git confronta tre versioni:
#    - Merge base (C)
#    - HEAD di main (G)  
#    - HEAD di feature (E)

# 3. Git crea il merge commit (M)
git checkout main
git merge feature

# 4. Risultato:
main:     A---B---C---F---G---M
               \             /
feature:        D---E-------/
```

## 🧠 Algoritmo Recursive

### Come Git Risolve i Merge

**1. Find Merge Base**
```bash
# Git trova l'antenato comune più recente
git merge-base main feature
```

**2. Three-Way Comparison**
- **Base**: Stato al momento della divergenza
- **Ours**: Stato attuale di main
- **Theirs**: Stato attuale di feature

**3. Automatic Resolution**
```bash
# Git applica automaticamente:
- Modifiche solo in main → Mantiene versione main
- Modifiche solo in feature → Mantiene versione feature  
- Modifiche uguali → Mantiene la modifica
- Modifiche diverse → CONFLITTO (richiede risoluzione manuale)
```

## ⚙️ Comandi Recursive Merge

### Merge Standard
```bash
git checkout main
git merge feature-branch
# Se fast-forward non è possibile, Git usa recursive automaticamente
```

### Forzare Three-Way Merge
```bash
git merge --no-ff feature-branch
# Crea sempre un merge commit, anche se fast-forward è possibile
```

### Merge con Strategia Specifica
```bash
# Usa la strategia recursive esplicitamente
git merge -s recursive feature-branch

# Opzioni per la strategia recursive
git merge -s recursive -X ours feature-branch    # preferisce main
git merge -s recursive -X theirs feature-branch  # preferisce feature
```

## 🎯 Quando Usare Recursive Merge

### ✅ Ideale per:

1. **Feature Branch Collaborative**
```bash
# Situazione tipica in team
git checkout -b feature/shopping-cart
# Developer A lavora su feature
git commit -m "Add cart component"

# Nel frattempo, main riceve altri commit da altri developer
# Developer B merge altra feature in main
git checkout main
git merge feature/user-profile  # main avanza

# Ora shopping-cart richiede recursive merge
git merge feature/shopping-cart  # Three-way merge automatico
```

2. **Integration Branches**
```bash
# Branch per integrare multiple feature
git checkout -b integration/v2.0
git merge feature/auth
git merge feature/payment
git merge feature/notifications
# Ogni merge potrebbe essere recursive
```

3. **Long-Running Branches**
```bash
# Branch di sviluppo parallelo
git checkout -b develop
# Sviluppo continuo su develop
# Periodici merge da main per sync
git merge main  # Recursive merge per integrare main in develop
```

4. **Maintenance e Hotfix**
```bash
# Main continua a ricevere feature
git checkout main
git merge feature/dashboard

# Hotfix su versione precedente
git checkout -b hotfix/security v1.2.0  
git commit -m "Security fix"

# Merge hotfix back to main
git checkout main
git merge hotfix/security  # Recursive merge necessario
```

## 📊 Vantaggi e Svantaggi

### ✅ Vantaggi

**1. Preserva Cronologia Completa**
```bash
# Puoi vedere chiaramente:
git log --oneline --graph
* 7a8b9c2 (main) Merge feature/auth
|\
| * 3e4f5a6 Add password validation
| * 1c2d3e4 Add login component
* | 9f8e7d6 Update homepage
* | 5c4b3a2 Fix navigation bug
|/
* 0a1b2c3 Initial commit
```

**2. Tracciabilità Features**
```bash
# Facile identificare cosa apparteneva a quale feature
git log --merges --oneline
# 7a8b9c2 Merge feature/auth
# 2b3c4d5 Merge feature/payment
# 8d9e0f1 Merge feature/dashboard
```

**3. Rollback Granulare**
```bash
# Rollback di una feature specifica
git revert -m 1 7a8b9c2  # Reverte il merge commit
# Rimuove tutti i cambiamenti della feature in un colpo
```

**4. Code Review Context**
```bash
# Review del merge commit mostra tutte le modifiche integrate
git show 7a8b9c2
# Chiaro cosa è stato aggiunto dalla feature
```

### ❌ Svantaggi

**1. Cronologia Più Complessa**
```bash
# Più difficile da leggere linearmente
git log --oneline  # Mix di merge commit e feature commit
```

**2. "Merge Commits Noise"**
```bash
# Molti merge commits possono rendere confusa la cronologia
git log --oneline | grep "Merge"
# Merge feature/auth
# Merge feature/payment  
# Merge hotfix/security
# Merge feature/dashboard
```

**3. Conflitti Potenziali**
- Richiede risoluzione manuale dei conflitti
- Processo può essere interrotto
- Necessita competenza per risoluzione

## 🛠️ Gestione Conflitti in Recursive Merge

### Identificare Conflitti

```bash
git merge feature-branch
# Auto-merging file.txt
# CONFLICT (content): Merge conflict in file.txt
# Automatic merge failed; fix conflicts and then commit the result.

git status
# On branch main
# You have unmerged paths.
#   (fix conflicts and run "git commit")
#   (use "git merge --abort" to abort the merge)
# 
# Unmerged paths:
#   (use "git add <file>..." to mark resolution)
#         both modified:   file.txt
```

### Risoluzione Conflitti

```bash
# 1. Esamina i conflitti
cat file.txt
# <<<<<<< HEAD
# Contenuto da main
# =======
# Contenuto da feature
# >>>>>>> feature-branch

# 2. Risolvi manualmente o usa merge tool
git mergetool

# 3. Mark risoluzione
git add file.txt

# 4. Completa il merge
git commit  # Apre editor per messaggio merge
```

### Strategie di Risoluzione

```bash
# Preferisci sempre main
git merge -X ours feature-branch

# Preferisci sempre feature
git merge -X theirs feature-branch

# Ignora whitespace differences
git merge -X ignore-space-change feature-branch

# Usa tool grafico per risoluzione
git config merge.tool vimdiff  # o altro tool
git mergetool
```

## 🔍 Tecniche Avanzate

### 1. Merge Octopus (Multiple Branches)

```bash
# Merge multiple branches simultaneamente
git merge feature1 feature2 feature3
# Git userà la strategia "octopus" per merge a più vie
```

### 2. Subtree Merge

```bash
# Merge un intero repository come subdirectory
git remote add plugin-repo url-to-plugin
git fetch plugin-repo
git merge -s subtree plugin-repo/main
```

### 3. Custom Merge Drivers

```bash
# .gitattributes
*.json merge=json-merge

# .git/config
[merge "json-merge"]
    name = JSON merge driver
    driver = json-merge-tool %O %A %B %L
```

### 4. Merge con Pre/Post Hooks

```bash
# .git/hooks/pre-merge-commit
#!/bin/bash
echo "🔍 Running pre-merge checks..."
npm test || exit 1
npm run lint || exit 1

# .git/hooks/post-merge
#!/bin/bash
echo "📦 Running post-merge tasks..."
npm install  # Update dependencies se package.json è cambiato
```

## 🎯 Esempi Pratici Dettagliati

### Esempio 1: Feature Branch Integration

```bash
# 1. Setup scenario
git init ecommerce-app
cd ecommerce-app

echo "# E-commerce App" > README.md
git add . && git commit -m "Initial commit"

# 2. Main development continua
echo "Basic homepage" > index.html
git add . && git commit -m "Add homepage"

# 3. Feature branch inizia
git checkout -b feature/user-auth
echo "Login page" > login.html
git add . && git commit -m "Add login page"

echo "Register page" > register.html  
git add . && git commit -m "Add registration page"

# 4. Main riceve altri commit
git checkout main
echo "Contact page" > contact.html
git add . && git commit -m "Add contact page"

echo "About page" > about.html
git add . && git commit -m "Add about page"

# 5. Recursive merge necessario
git merge feature/user-auth
# Git creates merge commit automaticamente

# 6. Visualizza risultato
git log --oneline --graph
# * f9e8d7c (HEAD -> main) Merge branch 'feature/user-auth'
# |\
# | * 3c2b1a0 Add registration page
# | * 7f6e5d4 Add login page
# * | 9e8d7c6 Add about page
# * | 5d4c3b2 Add contact page
# |/
# * 1a2b3c4 Add homepage
# * 0f1e2d3 Initial commit
```

### Esempio 2: Conflict Resolution Workflow

```bash
# 1. Setup conflict scenario
git checkout -b feature/update-config
echo "Production settings" > config.json
git add . && git commit -m "Add production config"

# 2. Main modifies same file
git checkout main
echo "Development settings" > config.json
git add . && git commit -m "Add development config"

# 3. Merge with conflict
git merge feature/update-config
# CONFLICT (add/add): Merge conflict in config.json

# 4. Examine conflict
cat config.json
# <<<<<<< HEAD
# Development settings
# =======
# Production settings
# >>>>>>> feature/update-config

# 5. Resolve manually
cat > config.json << EOF
{
  "environment": "configurable",
  "development": {
    "settings": "Development settings"
  },
  "production": {
    "settings": "Production settings"
  }
}
EOF

# 6. Complete merge
git add config.json
git commit -m "Merge configs: combine dev and prod settings"

# 7. Verify resolution
git log --oneline -3
# a8b7c6d Merge configs: combine dev and prod settings
# 9f8e7d6 Add development config
# 3e4f5a6 Add production config
```

### Esempio 3: Complex Multi-Developer Scenario

```bash
# Simula sviluppo team complesso
git init team-project
cd team-project

# Base setup
echo "Project base" > main.js && git add . && git commit -m "Initial project"

# Developer A: Authentication feature
git checkout -b feature/auth
echo "Auth module" > auth.js && git add . && git commit -m "Add auth module"
echo "User model" > user.js && git add . && git commit -m "Add user model"

# Developer B: Database feature (parallelo)
git checkout main
git checkout -b feature/database  
echo "DB connection" > db.js && git add . && git commit -m "Add database connection"
echo "Models setup" > models.js && git add . && git commit -m "Setup models"

# Main receives hotfix
git checkout main
echo "// Security patch" >> main.js && git add . && git commit -m "Apply security patch"

# Team integration day
# Merge database first
git merge feature/database
# Fast-forward possibile

# Merge auth (ora recursive necessario)
git merge feature/auth
# Recursive merge automatico

# Visualizza la cronologia complessa
git log --oneline --graph --all
# *   7c8d9e0 (HEAD -> main) Merge branch 'feature/auth'
# |\
# | * 5a6b7c8 Add user model
# | * 3e4f5a6 Add auth module
# * | 1d2e3f4 Setup models
# * | 9c8b7a6 Add database connection
# |/
# * f8e7d6c Apply security patch
# * 2b3c4d5 Initial project
```

## 🔧 Configurazioni Avanzate

### Merge Tool Configuration

```bash
# Setup merge tool preferito
git config --global merge.tool vimdiff

# Oppure setup custom merge tool
git config --global mergetool.sublime.cmd 'subl -w $MERGED'
git config --global mergetool.sublime.trustExitCode false
git config --global merge.tool sublime
```

### Default Merge Strategy

```bash
# Configure default per il repository
git config merge.defaulttoupstream true
git config merge.tool vimdiff
git config merge.conflictstyle diff3  # Mostra anche il merge base
```

### Merge Message Templates

```bash
# .gitmessage template per merge commits
cat > ~/.gitmessage << EOF
Merge [BRANCH_NAME]: [FEATURE_DESCRIPTION]

[DETAILED_DESCRIPTION]

- Feature highlights:
  - [HIGHLIGHT_1]  
  - [HIGHLIGHT_2]

- Testing completed:
  - [TEST_1]
  - [TEST_2]

Co-authored-by: [COLLABORATOR_NAME] <[EMAIL]>
EOF

git config --global commit.template ~/.gitmessage
```

## 🚨 Troubleshooting

### 1. Merge Bloccato

**Problema**: Merge si interrompe a metà per conflitti

```bash
# Opzioni:
git merge --abort     # Annulla il merge
git reset --hard HEAD # Reset completo (attenzione!)

# Oppure continua dopo risoluzione
git add .
git commit
```

### 2. Merge Commit Accidentale

**Problema**: Hai fatto recursive merge ma volevi fast-forward

```bash
# Se non hai pushato
git reset --hard HEAD~1
git merge --ff-only feature  # Se possibile

# Se hai pushato, crea nuovo commit che "flattens"
git revert HEAD
git merge --squash feature
git commit -m "Flatten feature integration"
```

### 3. History Troppo Complessa

**Problema**: Troppi merge commits rendono cronologia illeggibile

```bash
# Visualizzazione semplificata
git log --oneline --graph --simplify-by-decoration

# Oppure rewrite history (ATTENZIONE!)
git rebase -i --root  # Interattivo per cleanup
```

## 📈 Best Practices

### 1. **Messaggi Merge Informativi**
```bash
git merge feature/payment -m "Merge payment integration

- Add Stripe payment processing
- Implement refund functionality  
- Add payment history tracking
- Include comprehensive tests

Closes #123, #124, #125"
```

### 2. **Pre-Merge Testing**
```bash
# Verifica che il merge sarà pulito
git merge-tree $(git merge-base main feature) main feature

# Test merge su branch temporaneo
git checkout -b test-merge main
git merge feature
# ... test ...
git checkout main
git branch -D test-merge
```

### 3. **Structured Merge Workflow**
```bash
#!/bin/bash
# merge-feature.sh script

FEATURE_BRANCH=$1
TARGET_BRANCH=${2:-main}

echo "🔄 Merging $FEATURE_BRANCH into $TARGET_BRANCH"

# Sync target branch
git checkout $TARGET_BRANCH
git pull origin $TARGET_BRANCH

# Merge with proper message
git merge --no-ff $FEATURE_BRANCH -m "Merge $FEATURE_BRANCH

$(git log --oneline $TARGET_BRANCH..$FEATURE_BRANCH)"

# Push and cleanup
git push origin $TARGET_BRANCH
git branch -d $FEATURE_BRANCH
git push origin --delete $FEATURE_BRANCH
```

---

## 🔗 Link Correlati

- **[01 - Tipi di Merge](01-tipi-merge.md)** - Panoramica generale
- **[02 - Fast-Forward Merge](02-fast-forward.md)** - Merge lineari
- **[04 - Squash Merge](04-squash-merge.md)** - Cleanup cronologia
- **[05 - Merge vs Rebase](05-merge-vs-rebase.md)** - Quando usare quale strategia

---

**💡 Ricorda**: Recursive merge è la scelta predefinita per team collaboration. Impara a gestire i conflitti con confidenza e a scrivere merge commit informativi per mantenere una cronologia progetto chiara!
