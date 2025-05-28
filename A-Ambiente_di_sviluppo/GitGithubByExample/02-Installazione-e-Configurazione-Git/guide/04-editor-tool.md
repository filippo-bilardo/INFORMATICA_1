# 04 - Editor e Tool per Git

## 🎯 Obiettivo

Configurare e ottimizzare editor di testo e strumenti esterni per massimizzare la produttività quando si lavora con Git.

## 📚 Contenuti

### 1. Scelta dell'Editor per Git

#### 🎨 **Perché Configurare un Editor**
- **Messaggi di commit** dettagliati e ben formattati
- **Risoluzione conflitti** più efficace
- **Editing configurazioni** Git più comodo
- **Integrazione workflow** sviluppo

#### 🏆 **Editor Raccomandati per Principianti**
1. **VS Code** - Più versatile e user-friendly
2. **Nano** - Semplice e sempre disponibile
3. **Sublime Text** - Veloce e intuitivo
4. **Notepad++** - Windows-friendly

---

## 💻 Configurazione VS Code

### Setup Base VS Code

```bash
# Configura VS Code come editor Git
git config --global core.editor "code --wait"

# Verifica configurazione
git config --global core.editor
# Output: code --wait
```

### Estensioni Raccomandate per Git

```bash
# Lista estensioni essenziali da installare in VS Code:
```

#### 📦 **Estensioni Essenziali**
- **GitLens** (`eamodio.gitlens`) - Informazioni Git inline
- **Git History** (`donjayamanne.githistory`) - Visualizza cronologia
- **Git Graph** (`mhutchie.git-graph`) - Grafico branch interattivo
- **Bracket Pair Colorizer** - Migliore leggibilità codice

#### ⚙️ **Configurazione VS Code per Git**

```json
// settings.json di VS Code
{
    // Git configurations
    "git.enableSmartCommit": true,
    "git.confirmSync": false,
    "git.autofetch": true,
    "git.showPushSuccessNotification": true,
    
    // GitLens configurations
    "gitlens.currentLine.enabled": true,
    "gitlens.hovers.currentLine.over": "line",
    "gitlens.blame.compact": false,
    
    // Editor configurations for commit messages
    "git.inputValidationLength": 72,
    "git.inputValidationSubjectLength": 50,
    
    // Terminal integration
    "terminal.integrated.defaultProfile.windows": "Git Bash"
}
```

### Test VS Code Setup

```bash
# Test editor con commit vuoto
cd /tmp && mkdir test-vscode && cd test-vscode
git init
echo "test" > file.txt
git add file.txt

# Questo aprirà VS Code per il messaggio di commit
git commit
# Scrivi un messaggio, salva e chiudi per completare il commit
```

---

## 🖥️ Altri Editor Popolari

### Nano (Semplice)

```bash
# Configura Nano
git config --global core.editor "nano"

# Configurazioni Nano utili
echo 'set tabsize 4' >> ~/.nanorc
echo 'set autoindent' >> ~/.nanorc
echo 'set linenumbers' >> ~/.nanorc
```

**👍 Pro**: Semplice, sempre disponibile, guide a schermo
**👎 Contro**: Funzionalità limitate

### Vim (Avanzato)

```bash
# Configura Vim
git config --global core.editor "vim"

# Configurazioni Vim per Git
cat >> ~/.vimrc << 'EOF'
" Git commit message formatting
autocmd Filetype gitcommit setlocal spell textwidth=72
autocmd Filetype gitcommit setlocal colorcolumn=73

" Highlight commit message guidelines
highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%73v.\+/
EOF
```

**👍 Pro**: Potente, veloce, sempre disponibile
**👎 Contro**: Curva di apprendimento ripida

### Sublime Text

```bash
# Configura Sublime Text
git config --global core.editor "subl -w"

# Su Windows potrebbe essere:
git config --global core.editor "'C:/Program Files/Sublime Text 3/subl.exe' -w"
```

**👍 Pro**: Veloce, bello, estensioni
**👎 Contro**: Non gratuito per uso commerciale

---

## 🛠️ Tool di Diff e Merge

### Configurazione Diff Tool

#### VS Code come Diff Tool

```bash
# Configura VS Code per diff
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global difftool.prompt false

# Uso
git difftool HEAD~1 HEAD              # Confronta ultimo commit
git difftool --staged                 # Confronta staged files
```

#### Altri Diff Tool

```bash
# Meld (Linux/Windows)
git config --global diff.tool meld
git config --global difftool.meld.cmd 'meld $LOCAL $REMOTE'

# Beyond Compare (Windows/macOS)
git config --global diff.tool bc
git config --global difftool.bc.cmd '"C:/Program Files/Beyond Compare 4/BComp.exe" $LOCAL $REMOTE'

# Kaleidoscope (macOS)
git config --global diff.tool ksdiff
git config --global difftool.ksdiff.cmd 'ksdiff --partial-changeset --relative-path $MERGED -- $LOCAL $REMOTE'
```

### Configurazione Merge Tool

#### VS Code come Merge Tool

```bash
# Configura VS Code per merge
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.prompt false
git config --global mergetool.keepBackup false

# Durante un conflitto di merge
git mergetool
```

#### Altri Merge Tool

```bash
# P4Merge (gratuito, multi-platform)
git config --global merge.tool p4merge
git config --global mergetool.p4merge.cmd 'p4merge $BASE $LOCAL $REMOTE $MERGED'

# KDiff3 (gratuito, open source)
git config --global merge.tool kdiff3
```

---

## 🖼️ Interfacce Grafiche Git

### Git GUI Integrate

#### Git GUI (Inclusa con Git)

```bash
# Avvia Git GUI
git gui

# Configura Git GUI
git config --global gui.editor "code --wait"
git config --global gui.historybrowser "gitk"
```

#### Gitk (Browser cronologia)

```bash
# Visualizza cronologia con gitk
gitk --all          # Tutte le branch
gitk main           # Solo branch main
gitk --since="1 week ago"  # Ultima settimana
```

### GUI Esterne Popolari

#### 🆓 **GUI Gratuite**
- **SourceTree** (Atlassian) - Completa e user-friendly
- **GitHub Desktop** - Semplice, ottima per GitHub
- **GitKraken** (versione gratuita) - Bella interfaccia
- **TortoiseGit** (Windows) - Integrazione file manager

#### 💰 **GUI Commerciali**
- **GitKraken Pro** - Funzionalità avanzate
- **Tower** (macOS/Windows) - Professionale
- **SmartGit** - Potente e completa

### GitHub Desktop Setup

```bash
# Dopo installazione GitHub Desktop
# Configura integrazione da terminale

# Su macOS/Linux, aggiungi al PATH
echo 'export PATH="/Applications/GitHub Desktop.app/Contents/Resources/app/static:$PATH"' >> ~/.bashrc

# Uso da terminale
github /path/to/repository
```

---

## 🔧 Configurazioni Terminal

### Miglioramenti Terminal per Git

#### Prompt Git Migliorato

```bash
# Aggiungi al ~/.bashrc o ~/.zshrc
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

export PS1="\u@\h \[\033[32m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\] $ "
```

#### Oh My Zsh (per utenti Zsh)

```bash
# Installa Oh My Zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Abilita plugin Git
# Modifica ~/.zshrc
plugins=(git gitfast git-extras)

# Theme con info Git
ZSH_THEME="robbyrussell"
```

### Alias Shell per Git

```bash
# Aggiungi al ~/.bashrc o ~/.zshrc
alias g="git"
alias gs="git status"
alias ga="git add"
alias gc="git commit"
alias gp="git push"
alias gl="git log --oneline"
alias gd="git diff"
alias gco="git checkout"
alias gb="git branch"

# Alias più avanzati
alias glog="git log --oneline --decorate --graph --all"
alias gstash="git stash save"
alias gunstash="git stash pop"
```

---

## 📱 Tool Mobile e Web

### Interfacce Web

#### GitHub Web Editor

```bash
# Apri repository su GitHub e premi '.' per VS Code web
# Oppure cambia github.com in github.dev
# Esempio: https://github.dev/user/repository
```

#### GitPod

```bash
# Prefissa URL GitHub con gitpod.io
# Esempio: https://gitpod.io/#https://github.com/user/repository
```

### App Mobile

#### 📱 **App Raccomandate**
- **Working Copy** (iOS) - Client Git completo
- **Git2Go** (iOS) - Semplice e efficace
- **Pocket Git** (Android) - Client base
- **MGit** (Android) - Open source

---

## 🔍 Debugging e Ispezione

### Tool di Analisi Repository

#### Git Built-in Tools

```bash
# Analisi size repository
git count-objects -vH

# Trova file più grandi
git rev-list --objects --all | grep "$(git verify-pack -v .git/objects/pack/*.idx | sort -k 3 -nr | head -10 | awk '{print$1}')"

# Analisi contributi
git shortlog -sn --all
```

#### Git Extras (Estensioni Utili)

```bash
# Installa git-extras
# Ubuntu/Debian
sudo apt install git-extras

# macOS
brew install git-extras

# Comandi utili
git summary          # Panoramica repository
git effort           # Effort per file
git authors          # Lista autori
git changelog        # Genera changelog
```

---

## 🔧 Configurazione Completa Raccomandata

### Script di Setup Tool

```bash
#!/bin/bash
# setup-git-tools.sh

echo "🛠️ Configurazione Tool Git"

# Editor principale
git config --global core.editor "code --wait"

# Diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global difftool.prompt false

# Merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.prompt false
git config --global mergetool.keepBackup false

# GUI preferences
git config --global gui.editor "code --wait"

echo "✅ Tool configurati!"
echo "📝 Editor: $(git config core.editor)"
echo "🔍 Diff tool: $(git config diff.tool)"
echo "🔧 Merge tool: $(git config merge.tool)"
```

### Test Setup Completo

```bash
# Test editor
export EDITOR=''  # Reset temporaneo
git config core.editor

# Test diff tool
echo "test1" > file1.txt
echo "test2" > file2.txt
git difftool --no-index file1.txt file2.txt

# Test merge tool (simula conflitto)
mkdir test-merge && cd test-merge
git init
echo "linea originale" > test.txt
git add test.txt && git commit -m "Initial"
git checkout -b feature
echo "linea modificata" > test.txt
git add test.txt && git commit -m "Feature change"
git checkout main
echo "linea diversa" > test.txt
git add test.txt && git commit -m "Main change"
git merge feature  # Creerà conflitto
git mergetool       # Dovrebbe aprire il merge tool configurato
```

---

## 📋 Checklist Editor e Tool

- [ ] Editor configurato e testato con commit
- [ ] Diff tool configurato e testato
- [ ] Merge tool configurato e testato
- [ ] GUI Git installata (opzionale)
- [ ] Prompt terminal con info Git
- [ ] Alias shell configurati
- [ ] Estensioni editor installate

---

## 🔗 Prossimi Passi

✅ **Completato**: Configurazione editor e tool
🎯 **Prossimo**: [Setup Completo Windows](../esempi/01-setup-windows.md)

---

## 📚 Risorse Aggiuntive

- [Git Tools Documentation](https://git-scm.com/book/en/v2/Git-Tools-External-Merge-and-Diff-Tools)
- [VS Code Git Integration](https://code.visualstudio.com/docs/editor/versioncontrol)
- [GitLens Extension Guide](https://gitlens.amod.io/)
