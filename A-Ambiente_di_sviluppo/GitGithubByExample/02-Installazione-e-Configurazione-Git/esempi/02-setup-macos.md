# 02 - Setup Completo Git su macOS

## 🎯 Obiettivo

Guida step-by-step per installare e configurare Git su macOS con tutti i tool necessari per iniziare a sviluppare.

## 📋 Prerequisiti

- macOS 10.15 (Catalina) o superiore
- Connessione internet
- Password amministratore
- Terminal.app o iTerm2

## ⏱️ Tempo Richiesto

**30-45 minuti** (installazione + configurazione + test)

---

## 📥 Parte 1: Metodi di Installazione

### Metodo 1: Homebrew (Raccomandato) 🍺

#### Step 1: Installa Homebrew

```bash
# Verifica se Homebrew è già installato
brew --version

# Se non installato, installa Homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Aggiungi Homebrew al PATH (per Apple Silicon)
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

#### Step 2: Installa Git con Homebrew

```bash
# Installa Git (ultima versione)
brew install git

# Verifica installazione
git --version
# Output: git version 2.xx.x

# Verifica percorso
which git
# Output: /opt/homebrew/bin/git (Apple Silicon)
# Output: /usr/local/bin/git (Intel)
```

### Metodo 2: Xcode Command Line Tools

```bash
# Installa Xcode Command Line Tools (include Git)
xcode-select --install

# Verifica installazione
git --version
# Nota: Potrebbe essere una versione più datata

# Percorso tipico
which git
# Output: /usr/bin/git
```

### Metodo 3: Installer Ufficiale

1. **Scarica** da [git-scm.com/download/mac](https://git-scm.com/download/mac)
2. **Esegui** `git-2.xx.x-intel.dmg`
3. **Segui** wizard di installazione

---

## ⚙️ Parte 2: Configurazione Base

### Step 1: Configurazione Identità

```bash
# Configura nome (sostituisci con il tuo nome)
git config --global user.name "Mario Rossi"

# Configura email (sostituisci con la tua email)
git config --global user.email "mario.rossi@example.com"

# Verifica configurazione
git config --global user.name
git config --global user.email
```

### Step 2: Configurazioni macOS-Specifiche

```bash
# Configurazione line endings per macOS/Unix
git config --global core.autocrlf input

# Configurazione case sensitivity (importante su macOS)
git config --global core.ignorecase false

# Configurazione editor di default
git config --global core.editor "nano"  # o "vim" se preferisci

# Default branch name
git config --global init.defaultBranch main
```

---

## 🛠️ Parte 3: Setup Editor

### Option A: VS Code (Raccomandato)

#### 1. Installa VS Code

```bash
# Metodo 1: Homebrew Cask
brew install --cask visual-studio-code

# Metodo 2: Download diretto
# Vai su https://code.visualstudio.com/
# Scarica per macOS
```

#### 2. Configura VS Code per Git

```bash
# Verifica che 'code' sia disponibile da terminal
code --version

# Se non funziona, aggiungi al PATH
echo 'export PATH="/Applications/Visual Studio Code.app/Contents/Resources/app/bin:$PATH"' >> ~/.zprofile
source ~/.zprofile

# Configura VS Code come editor Git
git config --global core.editor "code --wait"

# Configura come diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global difftool.prompt false

# Configura come merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.prompt false
```

### Option B: Sublime Text

```bash
# Installa Sublime Text
brew install --cask sublime-text

# Configura per Git
git config --global core.editor "subl -w"
git config --global diff.tool sublime
git config --global difftool.sublime.cmd 'subl -w $LOCAL $REMOTE'
```

### Option C: Vim (Preinstallato)

```bash
# Configura Vim
git config --global core.editor "vim"

# Configurazione Vim per Git (~/.vimrc)
cat >> ~/.vimrc << 'EOF'
" Git commit message settings
autocmd Filetype gitcommit setlocal spell textwidth=72
autocmd Filetype gitcommit setlocal colorcolumn=73
highlight OverLength ctermbg=red ctermfg=white
match OverLength /\%73v.\+/
EOF
```

---

## 🎨 Parte 4: Personalizzazione Terminal

### Shell Configuration (Zsh - Default su macOS)

#### 1. Prompt Git-Aware

```bash
# Aggiungi al ~/.zshrc
cat >> ~/.zshrc << 'EOF'
# Git branch in prompt
autoload -Uz vcs_info
precmd() { vcs_info }
zstyle ':vcs_info:git:*' formats ' (%b)'
setopt PROMPT_SUBST
PROMPT='%n@%m %F{blue}%~%f%F{yellow}${vcs_info_msg_0_}%f $ '
EOF

# Ricarica configurazione
source ~/.zshrc
```

#### 2. Git Aliases per Shell

```bash
# Aggiungi alias al ~/.zshrc
cat >> ~/.zshrc << 'EOF'

# Git aliases
alias g="git"
alias gs="git status"
alias ga="git add"
alias gc="git commit"
alias gp="git push"
alias gl="git log --oneline"
alias gd="git diff"
alias gco="git checkout"
alias gb="git branch"
alias glog="git log --oneline --decorate --graph --all"
EOF

source ~/.zshrc
```

### Oh My Zsh (Opzionale ma Raccomandato)

```bash
# Installa Oh My Zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Modifica ~/.zshrc per abilitare plugin Git
sed -i '' 's/plugins=(git)/plugins=(git gitfast git-extras brew)/' ~/.zshrc

# Cambia theme (opzionale)
sed -i '' 's/ZSH_THEME="robbyrussell"/ZSH_THEME="agnoster"/' ~/.zshrc

# Ricarica
source ~/.zshrc
```

---

## 🔧 Parte 5: Tool Aggiuntivi

### Homebrew Packages Utili per Git

```bash
# Git extras - comandi aggiuntivi
brew install git-extras

# Git flow - workflow standardizzato
brew install git-flow

# Hub - integrazione GitHub
brew install hub

# Diff tool grafici
brew install --cask meld          # Open source
brew install --cask kaleidoscope  # Commerciale, molto bello

# Git GUI
brew install --cask sourcetree    # GUI completa
brew install --cask github        # GitHub Desktop
```

### Configurazione Diff Tools Grafici

#### Kaleidoscope (se installato)

```bash
git config --global diff.tool ksdiff
git config --global difftool.ksdiff.cmd 'ksdiff --partial-changeset --relative-path "$MERGED" -- "$LOCAL" "$REMOTE"'
git config --global difftool.ksdiff.trustexitcode true

git config --global merge.tool ksdiff
git config --global mergetool.ksdiff.cmd 'ksdiff --merge --output "$MERGED" --base "$BASE" -- "$LOCAL" --snapshot "$REMOTE" --snapshot'
git config --global mergetool.ksdiff.trustexitcode true
```

#### Meld (se installato)

```bash
git config --global diff.tool meld
git config --global difftool.meld.cmd 'meld "$LOCAL" "$REMOTE"'

git config --global merge.tool meld
git config --global mergetool.meld.cmd 'meld "$LOCAL" "$BASE" "$REMOTE" --output "$MERGED"'
```

---

## 🔐 Parte 6: Gestione Credenziali

### Keychain Helper (Raccomandato per macOS)

```bash
# Configura git per usare macOS keychain
git config --global credential.helper osxkeychain

# Verifica configurazione
git config --global credential.helper
# Output: osxkeychain
```

### SSH Key Setup (per GitHub/GitLab)

```bash
# Genera SSH key (sostituisci email)
ssh-keygen -t ed25519 -C "mario.rossi@example.com"

# Aggiungi al ssh-agent
eval "$(ssh-agent -s)"

# Configura ssh-agent (~/.ssh/config)
mkdir -p ~/.ssh
cat >> ~/.ssh/config << 'EOF'
Host *
  AddKeysToAgent yes
  UseKeychain yes
  IdentityFile ~/.ssh/id_ed25519
EOF

# Aggiungi chiave al keychain
ssh-add --apple-use-keychain ~/.ssh/id_ed25519

# Copia chiave pubblica (per aggiungerla a GitHub)
pbcopy < ~/.ssh/id_ed25519.pub
echo "Chiave SSH copiata negli appunti. Aggiungila al tuo account GitHub."
```

---

## 🧪 Parte 7: Test Setup Completo

### Test 1: Comandi Base

```bash
# Crea cartella di test
mkdir -p ~/Desktop/git-test
cd ~/Desktop/git-test

# Inizializza repository
git init
# Output: Initialized empty Git repository in ~/Desktop/git-test/.git/

# Controlla status
git status
# Output: On branch main, No commits yet...
```

### Test 2: Primo Commit

```bash
# Crea file di test
echo "# Test Repository macOS" > README.md

# Aggiungi file
git add README.md

# Verifica status
git status
# Output: Changes to be committed: new file: README.md

# Commit con editor
git commit
# Dovrebbe aprire l'editor configurato
```

### Test 3: Test Diff Tools

```bash
# Modifica file
echo "Contenuto aggiuntivo" >> README.md

# Test diff built-in
git diff README.md

# Test diff tool esterno (se configurato)
git difftool README.md
```

### Test 4: Test Credential Helper

```bash
# Test con repository remoto (opzionale)
# Crea un repository di test su GitHub first

# Clone test (sostituisci con tuo repo)
cd ~/Desktop
git clone https://github.com/tuousername/test-repo.git
# Le credenziali dovrebbero essere salvate automaticamente
```

---

## 🔧 Troubleshooting macOS

### Problema: Git versione datata (da Xcode)

```bash
# Verifica quale Git stai usando
which git
# Se output è /usr/bin/git, stai usando la versione Xcode

# Installa versione più recente via Homebrew
brew install git

# Forza il PATH per usare Homebrew Git
echo 'export PATH="/opt/homebrew/bin:$PATH"' >> ~/.zprofile  # Apple Silicon
# o
echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zprofile     # Intel

source ~/.zprofile

# Verifica
which git
# Output dovrebbe essere /opt/homebrew/bin/git o /usr/local/bin/git
```

### Problema: VS Code non si apre da Git

```bash
# Verifica che code sia nel PATH
code --version

# Se non funziona, reinstalla command line tools di VS Code
# Da VS Code: Command Palette (Cmd+Shift+P) > "Shell Command: Install 'code' command in PATH"

# Oppure aggiungi manualmente al PATH
echo 'export PATH="/Applications/Visual Studio Code.app/Contents/Resources/app/bin:$PATH"' >> ~/.zprofile
source ~/.zprofile
```

### Problema: Permission denied con Homebrew

```bash
# Fix permessi Homebrew
sudo chown -R $(whoami) $(brew --prefix)/*

# Oppure reinstalla Homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/uninstall.sh)"
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Problema: SSH key non funziona

```bash
# Test connessione SSH GitHub
ssh -T git@github.com
# Output atteso: Hi username! You've successfully authenticated...

# Se fallisce, verifica ssh-agent
ssh-add -l
# Dovrebbe mostrare la tua chiave

# Se vuota, riaggingi chiave
ssh-add --apple-use-keychain ~/.ssh/id_ed25519
```

---

## 📋 Checklist Setup macOS

### Installazione Base
- [ ] Git installato (Homebrew preferito)
- [ ] `git --version` mostra versione recente (2.35+)
- [ ] Git nel PATH corretto
- [ ] Command line tools funzionanti

### Configurazione
- [ ] Nome e email configurati
- [ ] Editor configurato e testato
- [ ] Configurazioni Unix (autocrlf input) applicate
- [ ] Prompt terminal con info Git

### Tool e Editor
- [ ] VS Code/Sublime/Vim configurato
- [ ] Diff tool configurato e testato
- [ ] Merge tool configurato e testato
- [ ] Oh My Zsh installato (opzionale)

### Credenziali e SSH
- [ ] Keychain helper configurato
- [ ] SSH key generata e aggiunta a GitHub
- [ ] Test connessione SSH riuscito

### Test Funzionali
- [ ] Repository di test creato
- [ ] Primo commit completato
- [ ] Editor si apre correttamente
- [ ] Diff tools funzionano

---

## 🎯 Risultato Finale

Al termine di questo setup avrai:

✅ **Git ultima versione** installato via Homebrew
✅ **Terminal personalizzato** con branch Git nel prompt
✅ **Editor moderno** integrato (VS Code)
✅ **Diff tools grafici** per confronti visuali
✅ **SSH keys** configurate per GitHub
✅ **Workflow ottimizzato** per sviluppo su macOS

---

## 💡 Tips per Produttività macOS

### Shortcut Utili

```bash
# Apri repository corrente in VS Code
alias vscode='code .'

# Apri Finder nella cartella corrente
alias finder='open .'

# Git log con date
alias glog-date='git log --pretty=format:"%h %ad %s" --date=short'

# Pulizia file .DS_Store
alias cleanup-ds='find . -name ".DS_Store" -delete'
```

### Integrazioni Native

```bash
# Integrazione con macOS Finder (opzionale)
# Installa Git Streaks (mostra status Git in Finder)
brew install --cask git-streaks

# Quick Look per Git (anteprima diff)
brew install --cask qlcolorcode
```

---

## 🔗 Prossimi Passi

✅ **Completato**: Setup macOS
🎯 **Prossimo**: [Primo Repository](../../03-Primo-Repository-Git/README.md)

---

## 📚 Risorse macOS-Specifiche

- [Homebrew Documentation](https://docs.brew.sh/)
- [macOS Terminal Git Integration](https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-Zsh)
- [SSH Keys for GitHub on macOS](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
