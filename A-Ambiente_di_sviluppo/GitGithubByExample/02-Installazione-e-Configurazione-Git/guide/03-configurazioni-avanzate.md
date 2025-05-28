# 03 - Configurazioni Avanzate Git

## 🎯 Obiettivo

Personalizzare Git per massimizzare produttività e comfort di utilizzo attraverso configurazioni avanzate, alias, e ottimizzazioni del workflow.

## 📚 Contenuti

### 1. Configurazioni di Core

#### 🎨 **Configurazioni dell'Editor**

```bash
# Editor per commit e merge
git config --global core.editor "code --wait"      # VS Code
git config --global core.editor "vim"              # Vim
git config --global core.editor "nano"             # Nano
git config --global core.editor "subl -w"          # Sublime Text

# Editor con parametri specifici
git config --global core.editor "'C:/Program Files/Notepad++/notepad++.exe' -multiInst -notabbar -nosession -noPlugin"
```

#### 📝 **Gestione Line Endings**

```bash
# Linux/macOS - converte CRLF in LF al commit
git config --global core.autocrlf input

# Windows - converte LF in CRLF al checkout, LF al commit
git config --global core.autocrlf true

# Disabilita conversione (non raccomandato)
git config --global core.autocrlf false

# Tratta file come binari se hanno line endings misti
git config --global core.safecrlf true
```

#### 🎨 **Personalizzazione Output**

```bash
# Abilita colori nell'output
git config --global color.ui auto

# Configurazioni colori specifiche
git config --global color.branch.current "yellow reverse"
git config --global color.branch.local "yellow"
git config --global color.branch.remote "green"
git config --global color.diff.meta "yellow bold"
git config --global color.diff.frag "magenta bold"
git config --global color.diff.old "red bold"
git config --global color.diff.new "green bold"
git config --global color.status.added "yellow"
git config --global color.status.changed "green"
git config --global color.status.untracked "cyan"
```

---

## 🔧 Alias Potenti per Git

### Alias Base (Essenziali)

```bash
# Alias per comandi frequenti
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.ci "commit"
git config --global alias.cp "cherry-pick"

# Test degli alias
git st                    # equivale a: git status
git co main              # equivale a: git checkout main
git br -a                # equivale a: git branch -a
```

### Alias Avanzati per il Log

```bash
# Log compatto e colorato
git config --global alias.lg "log --oneline --decorate --graph --all"

# Log dettagliato con statistiche
git config --global alias.ll "log --pretty=format:'%C(yellow)%h%C(reset) - %an, %ar : %s'"

# Log con grafico delle branch
git config --global alias.graph "log --graph --pretty=format:'%C(bold red)%h%C(reset) -%C(bold yellow)%d%C(reset) %s %C(bold green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --all"

# Mostra file modificati nell'ultimo commit
git config --global alias.last "log -1 HEAD --stat"

# Test degli alias log
git lg                    # log compatto grafico
git graph                # log grafico dettagliato
```

### Alias per Workflow Avanzati

```bash
# Ammend rapido ultimo commit
git config --global alias.amend "commit --amend --no-edit"

# Reset soft ultimo commit
git config --global alias.undo "reset HEAD~1 --mixed"

# Stash rapido con messaggio
git config --global alias.save "stash save"

# Lista tutti gli alias configurati
git config --global alias.aliases "config --get-regexp alias"

# Mostra differenze staged
git config --global alias.staged "diff --staged"

# Pulisci branch locali già merged
git config --global alias.cleanup "!git branch --merged | grep -v '\\*\\|main\\|develop' | xargs -n 1 git branch -d"
```

---

## 🚀 Configurazioni di Performance

### Ottimizzazioni Repository

```bash
# Abilita cache per operazioni più veloci
git config --global core.preloadindex true
git config --global core.fscache true

# Parallelizza operazioni
git config --global submodule.fetchJobs 4

# Configurazioni push
git config --global push.default simple
git config --global push.followTags true

# Ottimizza garbage collection
git config --global gc.auto 256
```

### Configurazioni di Sicurezza

```bash
# Default branch per nuovi repository
git config --global init.defaultBranch main

# Rifiuta push non-fast-forward
git config --global receive.denyNonFastForwards true

# Firma commit con GPG (se configurato)
git config --global commit.gpgsign false    # default
git config --global commit.gpgsign true     # se hai GPG

# Configura credential helper
git config --global credential.helper store  # Linux/macOS
git config --global credential.helper manager # Windows
```

---

## 📁 Configurazioni per Progetti Specifici

### Template di Configurazione per Progetti

#### Progetto Web (JavaScript/TypeScript)
```bash
# Naviga nel progetto
cd /path/to/web-project

# Configurazioni specifiche web
git config core.ignorecase false
git config core.filemode false   # Windows, ignore file permissions

# Hook automatici per linting
git config core.hooksPath .githooks
```

#### Progetto Multipiattaforma
```bash
# Per progetti condivisi tra OS diversi
git config core.autocrlf input
git config core.ignorecase false
git config core.filemode false
```

---

## 🔧 Configurazioni Diff e Merge

### Tool di Diff Esterni

```bash
# VS Code come diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global difftool.prompt false

# Uso: git difftool

# Altri editor popolari
# Sublime Text
git config --global diff.tool sublime
git config --global difftool.sublime.cmd 'subl -w $LOCAL $REMOTE'

# Vim
git config --global diff.tool vimdiff
```

### Tool di Merge

```bash
# VS Code come merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.prompt false
git config --global mergetool.keepBackup false

# Uso durante un conflitto: git mergetool
```

---

## 🗂️ Configurazioni .gitignore Globali

### Crea .gitignore Globale

```bash
# Crea file gitignore globale
touch ~/.gitignore_global

# Configura Git per usarlo
git config --global core.excludesfile ~/.gitignore_global
```

### Contenuto .gitignore Globale Raccomandato

```bash
# Aggiungi al file ~/.gitignore_global
cat >> ~/.gitignore_global << 'EOF'
# Editor files
.vscode/
.idea/
*.swp
*.swo
*~

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Logs
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Temporary files
*.tmp
*.temp
.cache/

# Environment files
.env
.env.local
.env.development.local
.env.test.local
.env.production.local
EOF
```

---

## 🛠️ Configurazioni Hook

### Esempio Hook pre-commit

```bash
# Crea cartella hooks nel progetto
mkdir -p .git/hooks

# Crea hook pre-commit
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/sh
# Hook pre-commit per controlli automatici

# Controlla se ci sono file non formattati
if command -v prettier > /dev/null 2>&1; then
    prettier --check .
    if [ $? -ne 0 ]; then
        echo "❌ Files not formatted with Prettier. Run 'prettier --write .'"
        exit 1
    fi
fi

echo "✅ Pre-commit checks passed"
EOF

# Rendi eseguibile
chmod +x .git/hooks/pre-commit
```

---

## 📊 Configurazioni di Logging e Debug

```bash
# Abilita logging dettagliato (debug)
git config --global log.showSignature false
git config --global log.decorate full

# Formato log personalizzato
git config --global pretty.fixes "format:Fixes %h (\"%s\")"

# Abbreviazioni hash più lunghe
git config --global core.abbrev 12

# Mostra sempre full paths
git config --global status.relativePaths false
```

---

## 🔧 Backup e Sync delle Configurazioni

### Esporta Configurazioni

```bash
# Esporta tutte le configurazioni globali
git config --global --list > git-config-backup.txt

# Oppure copia direttamente il file
cp ~/.gitconfig ~/git-config-backup.gitconfig
```

### Importa Configurazioni

```bash
# Da file di configurazione
cp ~/git-config-backup.gitconfig ~/.gitconfig

# Da file di export
while IFS='=' read -r key value; do
    git config --global "$key" "$value"
done < git-config-backup.txt
```

---

## 📋 Template Configurazione Completa

### Script di Setup Automatico

```bash
#!/bin/bash
# setup-git.sh - Script di configurazione Git completa

echo "🔧 Configurazione Git Avanzata"

# Identità (personalizza questi valori)
read -p "Nome completo: " user_name
read -p "Email: " user_email

git config --global user.name "$user_name"
git config --global user.email "$user_email"

# Configurazioni core
git config --global core.editor "code --wait"
git config --global core.autocrlf input
git config --global init.defaultBranch main
git config --global color.ui auto

# Alias essenziali
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.ci "commit"
git config --global alias.lg "log --oneline --decorate --graph --all"
git config --global alias.last "log -1 HEAD --stat"

# Configurazioni push
git config --global push.default simple
git config --global push.followTags true

echo "✅ Configurazione completata!"
echo "🔍 Verifica con: git config --list"
```

---

## 🚨 Troubleshooting Configurazioni

### Reset Configurazioni

```bash
# Reset configurazione specifica
git config --global --unset user.name

# Reset tutte le configurazioni globali (ATTENZIONE!)
rm ~/.gitconfig

# Ripristina configurazioni di default
git config --global --replace-all color.ui auto
```

### Debug Configurazioni

```bash
# Mostra da dove viene una configurazione
git config --show-origin user.name

# Lista tutte le configurazioni con origine
git config --list --show-origin

# Verifica configurazione finale
git config --list --show-scope
```

---

## 📋 Checklist Configurazioni Avanzate

- [ ] Editor configurato e testato
- [ ] Alias base configurati
- [ ] Configurazioni colore attive
- [ ] Line endings configurati per il tuo OS
- [ ] .gitignore globale creato
- [ ] Configurazioni di performance applicate
- [ ] Backup configurazioni creato

---

## 🔗 Prossimi Passi

✅ **Completato**: Configurazioni avanzate
🎯 **Prossimo**: [Editor e Tool](./04-editor-tool.md)

---

## 📚 Risorse Aggiuntive

- [Git Configuration Documentation](https://git-scm.com/docs/git-config)
- [Git Aliases Guide](https://git-scm.com/book/en/v2/Git-Basics-Git-Aliases)
- [Git Hooks Documentation](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
