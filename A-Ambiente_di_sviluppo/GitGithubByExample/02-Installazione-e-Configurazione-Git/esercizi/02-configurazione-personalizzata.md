# 02 - Configurazione Personalizzata Git

## 🎯 Obiettivo

Creare una configurazione Git personalizzata che rifletta le tue preferenze di lavoro, migliorando produttività e comfort durante lo sviluppo.

## ⏱️ Durata

**20-30 minuti**

## 📋 Prerequisiti

- Git installato e verificato
- Configurazione base completata (nome, email)
- Editor funzionante
- Conoscenza comandi base Git

---

## 🎨 Parte 1: Personalizzazione Estetica

### 1.1 Configurazione Colori Personalizzati

```bash
# Abilita colori personalizzati
git config --global color.ui auto

# Personalizza colori branch
git config --global color.branch.current "yellow bold"
git config --global color.branch.local "green"
git config --global color.branch.remote "cyan"

# Personalizza colori diff
git config --global color.diff.meta "blue bold"
git config --global color.diff.frag "magenta bold"
git config --global color.diff.old "red bold"
git config --global color.diff.new "green bold"

# Personalizza colori status
git config --global color.status.added "green bold"
git config --global color.status.changed "yellow"
git config --global color.status.untracked "red"

# Test colori
git status  # Dovrebbe mostrare output colorato
```

### 1.2 Configurazione Output e Formatting

```bash
# Configurazioni display
git config --global core.pager "less -F -X"
git config --global core.quotepath false
git config --global log.decorate full

# Formato date personalizzato
git config --global log.date iso

# Test formattazione
git log --oneline --decorate --graph --all
```

---

## 🚀 Parte 2: Alias per Produttività

### 2.1 Alias Base (Essenziali)

```bash
# Comandi frequenti abbreviati
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.ci "commit"
git config --global alias.cp "cherry-pick"
git config --global alias.rb "rebase"

# Test alias base
git st      # git status
git br -a   # git branch -a
```

### 2.2 Alias Log Avanzati

```bash
# Log grafico compatto
git config --global alias.lg "log --oneline --decorate --graph --all"

# Log dettagliato con stat
git config --global alias.ll "log --pretty=format:'%C(yellow)%h%C(reset) - %an, %ar : %s' --stat"

# Log con grafico avanzato
git config --global alias.graph "log --graph --pretty=format:'%C(bold red)%h%C(reset) -%C(bold yellow)%d%C(reset) %s %C(bold green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --all"

# Timeline dei commit
git config --global alias.timeline "log --graph --branches --pretty=oneline --decorate"

# Test alias log
git lg
git graph
```

### 2.3 Alias Workflow

```bash
# Commit rapidi
git config --global alias.cmt "commit -m"
git config --global alias.amend "commit --amend --no-edit"

# Branch management
git config --global alias.new "checkout -b"
git config --global alias.del "branch -d"
git config --global alias.delr "push origin --delete"

# Stash shortcuts
git config --global alias.save "stash save"
git config --global alias.pop "stash pop"
git config --global alias.drop "stash drop"

# Diff shortcuts
git config --global alias.staged "diff --staged"
git config --global alias.unstaged "diff"

# Test workflow aliases
git new feature-test    # Crea e switcha a branch
git cmt "Test commit"   # Commit rapido
```

### 2.4 Alias Avanzati (Power User)

```bash
# Visualizza ultimo commit
git config --global alias.last "log -1 HEAD --stat"

# Resetta ultimo commit (soft)
git config --global alias.undo "reset HEAD~1 --mixed"

# Lista file modificati
git config --global alias.changed "whatchanged -1 --format=oneline"

# Trova commit che contiene stringa
git config --global alias.find "log --all --grep"

# Branch cleanup (merged branches)
git config --global alias.cleanup "!git branch --merged | grep -v '\\*\\|main\\|develop' | xargs -n 1 git branch -d"

# Lista tutti gli alias
git config --global alias.aliases "config --get-regexp alias"

# Test alias avanzati
git aliases  # Mostra tutti gli alias configurati
git last     # Mostra ultimo commit
```

---

## ⚙️ Parte 3: Configurazioni Workflow

### 3.1 Configurazioni Push e Pull

```bash
# Comportamento push di default
git config --global push.default simple
git config --global push.followTags true

# Comportamento pull di default
git config --global pull.rebase false  # merge (default)
# git config --global pull.rebase true   # rebase (alternativa)

# Auto-setup remote branch
git config --global branch.autosetupmerge always
git config --global branch.autosetuprebase never
```

### 3.2 Configurazioni Repository

```bash
# Default branch per nuovi repository
git config --global init.defaultBranch main

# Configurazioni sicurezza
git config --global transfer.fsckobjects true
git config --global fetch.fsckobjects true
git config --global receive.fsckObjects true
```

### 3.3 Configurazioni Performance

```bash
# Ottimizzazioni performance
git config --global core.preloadindex true
git config --global core.fscache true
git config --global gc.auto 256

# Parallelizzazione
git config --global submodule.fetchJobs 4
git config --global checkout.workers 0  # auto-detect CPU cores
```

---

## 🛠️ Parte 4: Configurazioni Editor Avanzate

### 4.1 Template Commit Message

```bash
# Crea template commit message
mkdir -p ~/.git_templates
cat > ~/.git_templates/commit_template << 'EOF'
# Title: Summary, imperative, start upper case, don't end with a period
# No more than 50 chars. #### 50 chars is here:  #

# Remember blank line between title and body.

# Body: Explain *what* and *why* (not *how*). Include task ID (Jira issue).
# Wrap at 72 chars. ################################## which is here:  #


# At the end: Include Co-authored-by for all contributors. 
# Include at least one empty line before it. Format: 
# Co-authored-by: name <user@users.noreply.github.com>
#
# How to Write a Git Commit Message:
# https://chris.beams.io/posts/git-commit/
#
# 1. Separate subject from body with a blank line
# 2. Limit the subject line to 50 characters
# 3. Capitalize the subject line
# 4. Do not end the subject line with a period
# 5. Use the imperative mood in the subject line
# 6. Wrap the body at 72 characters
# 7. Use the body to explain what and why vs. how
EOF

# Configura template
git config --global commit.template ~/.git_templates/commit_template

# Test template
echo "test" > template-test.txt
git add template-test.txt
git commit  # Dovrebbe aprire editor con template
```

### 4.2 Configurazioni Editor Specifiche

#### Per VS Code
```bash
# Configurazioni VS Code avanzate
git config --global core.editor "code --wait"
git config --global sequence.editor "code --wait"

# Merge tool VS Code
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.keepBackup false

# Diff tool VS Code
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global difftool.prompt false
```

#### Per Vim
```bash
# Configurazioni Vim avanzate
git config --global core.editor "vim"
git config --global merge.tool vimdiff
git config --global mergetool.vimdiff.path vim

# Aggiungi configurazioni Vim specifiche per Git
cat >> ~/.vimrc << 'EOF'
" Git commit specifiche
autocmd Filetype gitcommit setlocal spell textwidth=72
autocmd Filetype gitcommit setlocal colorcolumn=50,72
autocmd Filetype gitcommit 1 | startinsert

" Git rebase interattivo
autocmd Filetype gitrebase setlocal spell
EOF
```

---

## 🔐 Parte 5: Sicurezza e Privacy

### 5.1 Configurazioni GPG (Opzionale)

```bash
# Solo se hai GPG configurato
# Verifica chiavi GPG
gpg --list-secret-keys --keyid-format LONG

# Se hai una chiave, configurala
# git config --global user.signingkey YOUR_GPG_KEY_ID
# git config --global commit.gpgsign true
# git config --global tag.gpgsign true
```

### 5.2 Configurazioni Privacy

```bash
# Privacy email (GitHub)
# Se usi email privacy di GitHub
# git config --global user.email "123456+username@users.noreply.github.com"

# Blocca commit con email non verificata
git config --global user.useConfigOnly true
```

---

## 📁 Parte 6: .gitignore Globale

### 6.1 Creazione .gitignore Globale

```bash
# Crea .gitignore globale
touch ~/.gitignore_global

# Configura Git per usarlo
git config --global core.excludesfile ~/.gitignore_global
```

### 6.2 Contenuto .gitignore Globale Personalizzato

```bash
# Aggiungi contenuti personalizzati
cat >> ~/.gitignore_global << 'EOF'
# === EDITOR FILES ===
.vscode/
.idea/
*.swp
*.swo
*~
.project
.metadata

# === OS GENERATED FILES ===
# macOS
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
.AppleDouble
.LSOverride

# Windows  
Thumbs.db
ehthumbs.db
Desktop.ini
$RECYCLE.BIN/

# Linux
*~
.directory

# === LOGS ===
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# === TEMPORARY FILES ===
*.tmp
*.temp
.cache/
.sass-cache/

# === ENVIRONMENT FILES ===
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# === NODE.JS ===
node_modules/
.npm
.yarn-integrity

# === PYTHON ===
__pycache__/
*.py[cod]
*$py.class
.Python
.pytest_cache/

# === JAVA ===
*.class
.gradle/
build/
target/

# === CERTIFICATES ===
*.pem
*.key
*.crt

# === BACKUP FILES ===
*.bak
*.backup
*.orig
EOF

# Verifica configurazione
git config --global core.excludesfile
```

---

## 📊 Parte 7: Test Configurazione Personalizzata

### 7.1 Test Repository di Esempio

```bash
# Crea repository per testare configurazioni
mkdir ~/git-config-test
cd ~/git-config-test
git init

# Test template commit
echo "# Test Repository" > README.md
git add README.md
git commit  # Dovrebbe mostrare template

# Test alias
git st
git lg
git graph

# Test ignore globale
touch .DS_Store test.log
git st  # Non dovrebbe mostrare questi file
```

### 7.2 Test Workflow

```bash
# Test branch workflow
git new feature/test-config
echo "Test feature" > feature.txt
git add feature.txt
git cmt "Add test feature"

# Test log aliases
git graph
git last

# Test merge back
git co main
git merge feature/test-config

# Cleanup
git del feature/test-config
```

---

## 📋 Checklist Configurazione Personalizzata

### ✅ Estetica e UI
- [ ] Colori personalizzati configurati
- [ ] Output formattato correttamente
- [ ] Pager configurato
- [ ] Date format impostato

### ✅ Alias e Shortcuts
- [ ] Alias base configurati (st, co, br, ci)
- [ ] Alias log configurati (lg, graph, last)
- [ ] Alias workflow configurati (new, save, amend)
- [ ] Alias avanzati configurati (cleanup, find)

### ✅ Workflow e Performance
- [ ] Push/pull behavior configurato
- [ ] Default branch impostato
- [ ] Performance ottimizzata
- [ ] Sicurezza configurata

### ✅ Editor e Tool
- [ ] Template commit configurato
- [ ] Editor avanzato configurato
- [ ] Merge/diff tool configurati
- [ ] .gitignore globale creato

### ✅ Test Funzionalità
- [ ] Tutti gli alias testati
- [ ] Template commit funzionante
- [ ] .gitignore globale attivo
- [ ] Workflow completo testato

---

## 💾 Backup Configurazione

### Esporta Configurazione

```bash
# Backup configurazione completa
git config --global --list > ~/git-config-backup.txt

# Backup file configurazione
cp ~/.gitconfig ~/gitconfig-backup-$(date +%Y%m%d).gitconfig

# Backup gitignore globale
cp ~/.gitignore_global ~/gitignore_global-backup-$(date +%Y%m%d)

echo "✅ Backup creati in home directory"
```

### Script di Setup Automatico

```bash
# Crea script per replicare configurazione
cat > ~/setup-my-git.sh << 'EOF'
#!/bin/bash
echo "🔧 Setup Git Personalizzato"

# Identità (modifica questi valori)
read -p "Nome: " user_name
read -p "Email: " user_email

git config --global user.name "$user_name"
git config --global user.email "$user_email"

# Configurazioni base
git config --global core.editor "code --wait"
git config --global init.defaultBranch main
git config --global color.ui auto

# Alias essenziali
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.ci "commit"
git config --global alias.lg "log --oneline --decorate --graph --all"

# Performance
git config --global push.default simple
git config --global pull.rebase false

echo "✅ Configurazione Git completata!"
EOF

chmod +x ~/setup-my-git.sh
echo "✅ Script di setup creato: ~/setup-my-git.sh"
```

---

## 🎯 Configurazione Finale Raccomandata

Alla fine di questo esercizio dovresti avere:

✅ **Git personalizzato** secondo le tue preferenze
✅ **Alias produttivi** per comandi frequenti  
✅ **Workflow ottimizzato** per il tuo stile di lavoro
✅ **Template commit** per messaggi consistenti
✅ **Ignore globale** per file non voluti
✅ **Backup delle configurazioni** per sicurezza

---

## 🔗 Prossimi Passi

✅ **Completato**: Configurazione personalizzata
🎯 **Prossimo**: [Primo Repository Git](../../03-Primo-Repository-Git/README.md)

---

## 💡 Suggerimenti Avanzati

### Configurazioni per Team

```bash
# Standardizza configurazioni team
git config --global core.autocrlf input  # Unix line endings
git config --global core.ignorecase false  # Case sensitive
git config --global core.filemode true   # File permissions (Linux/macOS)
```

### Hook Personalizzati

```bash
# Setup hook directory
mkdir -p ~/.git_templates/hooks
git config --global init.templateDir ~/.git_templates

# Crea hook pre-commit di esempio
cat > ~/.git_templates/hooks/pre-commit << 'EOF'
#!/bin/sh
# Hook pre-commit personalizzato
echo "🔍 Running pre-commit checks..."
# Aggiungi qui i tuoi controlli
EOF

chmod +x ~/.git_templates/hooks/pre-commit
```

---

## 📚 Risorse Aggiuntive

- [Git Configuration Docs](https://git-scm.com/docs/git-config)
- [Git Aliases Best Practices](https://git-scm.com/book/en/v2/Git-Basics-Git-Aliases)
- [Git Templates and Hooks](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
