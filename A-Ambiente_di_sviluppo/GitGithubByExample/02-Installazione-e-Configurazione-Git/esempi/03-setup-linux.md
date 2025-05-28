# 03 - Setup Completo Git su Linux

## 🎯 Obiettivo

Guida step-by-step per installare e configurare Git su diverse distribuzioni Linux con tutti i tool necessari per iniziare a sviluppare.

## 📋 Prerequisiti

- Distribuzione Linux supportata (Ubuntu, Debian, CentOS, Fedora, Arch)
- Connessione internet
- Accesso sudo/root
- Terminal

## ⏱️ Tempo Richiesto

**20-40 minuti** (installazione + configurazione + test)

---

## 📥 Parte 1: Installazione per Distribuzione

### Ubuntu/Debian 🟠

#### Metodo 1: Repository Ufficiali

```bash
# Aggiorna repository
sudo apt update

# Installa Git e strumenti correlati
sudo apt install git git-extras gitk git-gui -y

# Verifica installazione
git --version
# Output tipico: git version 2.34.1 (potrebbe essere datata)
```

#### Metodo 2: PPA per Ultima Versione (Raccomandato)

```bash
# Aggiungi PPA ufficiale Git
sudo add-apt-repository ppa:git-core/ppa -y
sudo apt update

# Installa Git ultima versione
sudo apt install git -y

# Verifica versione
git --version
# Output: git version 2.40.0+ (versione più recente)
```

#### Pacchetti Aggiuntivi Ubuntu

```bash
# Tool di sviluppo essenziali
sudo apt install curl wget build-essential -y

# Editor moderni
sudo apt install vim nano code -y  # VS Code se nel repository

# Tool diff/merge grafici
sudo apt install meld kdiff3 -y
```

### CentOS/RHEL/Rocky Linux 🔴

#### CentOS/RHEL 8+

```bash
# Installa Git
sudo dnf install git git-extras gitk -y

# Verifica installazione
git --version
```

#### CentOS/RHEL 7

```bash
# Metodo 1: Repository standard (versione datata)
sudo yum install git -y

# Metodo 2: Compilazione per versione recente
sudo yum groupinstall "Development Tools" -y
sudo yum install gettext-devel openssl-devel perl-CPAN perl-devel zlib-devel curl-devel -y

# Download e compila Git
cd /tmp
wget https://github.com/git/git/archive/v2.40.0.tar.gz
tar -xzf v2.40.0.tar.gz
cd git-2.40.0
make configure
./configure --prefix=/usr/local
make all
sudo make install

# Verifica
/usr/local/bin/git --version
```

### Fedora 🔵

```bash
# Installa Git
sudo dnf install git git-extras gitk git-gui -y

# Tool aggiuntivi
sudo dnf install vim nano code meld -y

# Verifica
git --version
```

### Arch Linux 🟣

```bash
# Installa Git
sudo pacman -S git git-extras tk gitk -y

# Tool aggiuntivi
sudo pacman -S vim nano code meld diff-so-fancy -y

# AUR packages (con yay)
yay -S git-flow github-cli -y

# Verifica
git --version
```

### openSUSE 🟢

```bash
# Installa Git
sudo zypper install git git-extras gitk git-gui -y

# Tool aggiuntivi
sudo zypper install vim nano code meld -y

# Verifica
git --version
```

---

## ⚙️ Parte 2: Configurazione Base

### Configurazione Identità

```bash
# Configura nome (sostituisci con il tuo nome)
git config --global user.name "Mario Rossi"

# Configura email (sostituisci con la tua email)
git config --global user.email "mario.rossi@example.com"

# Verifica configurazione
git config --global user.name
git config --global user.email
```

### Configurazioni Linux-Specifiche

```bash
# Configurazione line endings per Linux/Unix
git config --global core.autocrlf input

# Configurazione case sensitivity
git config --global core.ignorecase false

# Configurazione file permissions (mantieni per Linux)
git config --global core.filemode true

# Default branch name
git config --global init.defaultBranch main

# Configurazioni di performance
git config --global core.preloadindex true
git config --global core.fscache true

# Colori nell'output
git config --global color.ui auto
```

---

## 🛠️ Parte 3: Setup Editor

### Option A: VS Code

#### Installazione VS Code

```bash
# Ubuntu/Debian - Download .deb
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
sudo apt update
sudo apt install code -y

# Fedora/CentOS
sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
sudo sh -c 'echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" > /etc/yum.repos.d/vscode.repo'
sudo dnf install code -y

# Arch Linux
yay -S visual-studio-code-bin

# openSUSE
sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
sudo zypper addrepo https://packages.microsoft.com/yumrepos/vscode vscode
sudo zypper install code
```

#### Configurazione VS Code per Git

```bash
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
git config --global mergetool.keepBackup false
```

### Option B: Vim (Preinstallato)

```bash
# Configura Vim come editor Git
git config --global core.editor "vim"

# Configurazione Vim per Git (~/.vimrc)
cat >> ~/.vimrc << 'EOF'
" Git commit message settings
autocmd Filetype gitcommit setlocal spell textwidth=72
autocmd Filetype gitcommit setlocal colorcolumn=73

" Syntax highlighting
syntax on
set number
set autoindent
set tabstop=4
set shiftwidth=4
set expandtab

" Git-specific colors
highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%73v.\+/
EOF
```

### Option C: Nano (User-Friendly)

```bash
# Configura Nano come editor Git
git config --global core.editor "nano"

# Configurazione Nano (~/.nanorc)
cat >> ~/.nanorc << 'EOF'
# Configurazioni base
set tabsize 4
set autoindent
set linenumbers
set mouse
set softwrap

# Syntax highlighting
include /usr/share/nano/*.nanorc

# Git commit template
set speller "aspell -c"
EOF
```

---

## 🎨 Parte 4: Personalizzazione Shell

### Bash Configuration

#### Prompt Git-Aware

```bash
# Aggiungi al ~/.bashrc
cat >> ~/.bashrc << 'EOF'

# Git branch in prompt
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

# Colorful prompt with Git branch
export PS1="\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\]\$ "

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

# Utility aliases
alias ll="ls -la"
alias la="ls -A"
alias l="ls -CF"
EOF

# Ricarica configurazione
source ~/.bashrc
```

### Zsh Configuration (se installato)

```bash
# Installa Zsh se non presente
sudo apt install zsh -y  # Ubuntu/Debian
sudo dnf install zsh -y  # Fedora
sudo pacman -S zsh -y     # Arch

# Cambia shell di default (opzionale)
chsh -s $(which zsh)

# Installa Oh My Zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Configura plugin Git in ~/.zshrc
sed -i 's/plugins=(git)/plugins=(git gitfast git-extras)/' ~/.zshrc

# Theme con informazioni Git
sed -i 's/ZSH_THEME="robbyrussell"/ZSH_THEME="agnoster"/' ~/.zshrc

# Ricarica
source ~/.zshrc
```

---

## 🔧 Parte 5: Tool Avanzati

### Diff e Merge Tools Grafici

#### Meld (Raccomandato per Linux)

```bash
# Installazione
sudo apt install meld -y      # Ubuntu/Debian
sudo dnf install meld -y      # Fedora
sudo pacman -S meld -y        # Arch
sudo zypper install meld -y   # openSUSE

# Configurazione
git config --global diff.tool meld
git config --global difftool.meld.cmd 'meld "$LOCAL" "$REMOTE"'
git config --global difftool.prompt false

git config --global merge.tool meld
git config --global mergetool.meld.cmd 'meld "$LOCAL" "$BASE" "$REMOTE" --output "$MERGED"'
git config --global mergetool.prompt false
```

#### KDiff3

```bash
# Installazione
sudo apt install kdiff3 -y
# Configurazione simile a Meld

git config --global diff.tool kdiff3
git config --global merge.tool kdiff3
```

### Git Extras

```bash
# Se non installato con Git
# Ubuntu/Debian
sudo apt install git-extras -y

# Fedora
sudo dnf install git-extras -y

# Arch
sudo pacman -S git-extras -y

# Manuale (se non disponibile nei repository)
git clone https://github.com/tj/git-extras.git
cd git-extras
sudo make install

# Comandi utili di git-extras
git summary          # Panoramica repository
git effort           # Effort per file
git authors          # Lista autori
git changelog        # Genera changelog
git delete-branch    # Elimina branch locale e remota
git fresh-branch     # Crea e switcha a nuova branch
```

### Hub CLI (GitHub Integration)

```bash
# Ubuntu/Debian
sudo apt install hub -y

# Fedora
sudo dnf install hub -y

# Arch
sudo pacman -S hub -y

# Configurazione
hub api user  # Prima volta chiede credenziali GitHub

# Alias per sostituire git con hub
alias git=hub
```

---

## 🔐 Parte 6: Gestione Credenziali

### Git Credential Store

```bash
# Metodo 1: Store (salva in plaintext)
git config --global credential.helper store

# Metodo 2: Cache (temporaneo)
git config --global credential.helper cache
git config --global credential.helper 'cache --timeout=3600'  # 1 ora

# Metodo 3: GNOME Keyring (Ubuntu/GNOME)
sudo apt install libsecret-1-0 libsecret-1-dev -y
cd /usr/share/doc/git/contrib/credential/libsecret
sudo make
git config --global credential.helper /usr/share/doc/git/contrib/credential/libsecret/git-credential-libsecret
```

### SSH Key Setup

```bash
# Genera SSH key
ssh-keygen -t ed25519 -C "mario.rossi@example.com"

# Aggiungi al ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# Copia chiave pubblica
cat ~/.ssh/id_ed25519.pub
# Copia output e aggiungi a GitHub

# Test connessione
ssh -T git@github.com
```

---

## 🧪 Parte 7: Test Setup Completo

### Test Base

```bash
# Crea cartella di test
mkdir -p ~/Desktop/git-test
cd ~/Desktop/git-test

# Inizializza repository
git init

# Crea file di test
echo "# Test Repository Linux" > README.md
echo "Configurazione Git completata su $(lsb_release -d | cut -f2)" >> README.md

# Primo commit
git add README.md
git commit -m "Initial commit - Setup completato"

# Verifica log
git log --oneline
```

### Test Editor

```bash
# Test editor con commit vuoto
echo "Test content" > test.txt
git add test.txt

# Questo dovrebbe aprire l'editor configurato
git commit
# Scrivi messaggio, salva e chiudi
```

### Test Diff Tools

```bash
# Modifica file
echo "Modifica test" >> test.txt

# Test diff normale
git diff test.txt

# Test diff tool grafico (se configurato)
git difftool test.txt
```

---

## 🚨 Troubleshooting Linux

### Problema: Git versione vecchia

```bash
# Ubuntu - usa PPA
sudo add-apt-repository ppa:git-core/ppa
sudo apt update && sudo apt install git

# CentOS/RHEL - compila da sorgente o usa repo esterni
sudo yum groupinstall "Development Tools"
# Segui istruzioni compilazione nella sezione CentOS
```

### Problema: VS Code non funziona da Git

```bash
# Verifica che code sia nel PATH
which code

# Se non presente, crea symlink
sudo ln -s /usr/share/code/bin/code /usr/local/bin/code

# Oppure usa percorso completo
git config --global core.editor "/usr/share/code/bin/code --wait"
```

### Problema: Diff tool grafico non si apre

```bash
# Verifica che il tool sia installato
which meld

# Installa se necessario
sudo apt install meld

# Test configurazione
git config --global diff.tool
git config --global difftool.meld.cmd
```

### Problema: Credenziali non salvate

```bash
# Verifica credential helper
git config --global credential.helper

# Se vuoto, configura
git config --global credential.helper store

# Per GNOME, verifica libsecret
ls /usr/share/doc/git/contrib/credential/libsecret/git-credential-libsecret
```

---

## 📋 Checklist Setup Linux

### Installazione Base
- [ ] Git installato (versione 2.25+)
- [ ] `git --version` funziona
- [ ] Git-extras installato
- [ ] Tool diff/merge installati

### Configurazione
- [ ] Nome e email configurati
- [ ] Editor configurato e testato
- [ ] Configurazioni Unix applicate
- [ ] Alias shell configurati

### Tool e Integrazione
- [ ] Diff tool grafico configurato
- [ ] Merge tool configurato
- [ ] Credential helper attivo
- [ ] SSH key configurata

### Test e Personalizzazione
- [ ] Prompt shell con branch Git
- [ ] Repository di test creato
- [ ] Primo commit completato
- [ ] Diff tools testati

---

## 🎯 Risultato Finale

Al termine di questo setup avrai:

✅ **Git ultima versione** installato
✅ **Shell personalizzata** con info Git
✅ **Editor moderno** integrato
✅ **Tool grafici** per diff e merge
✅ **Credenziali gestite** automaticamente
✅ **SSH configurato** per GitHub
✅ **Workflow ottimizzato** per Linux

---

## 💡 Tips Specifici per Linux

### Performance Optimization

```bash
# Per repository grandi
git config --global core.preloadindex true
git config --global core.fscache true
git config --global gc.auto 256

# Parallel fetch
git config --global submodule.fetchJobs 4
```

### Sistema di File Case-Sensitive

```bash
# Linux è case-sensitive, utile per progetti cross-platform
git config --global core.ignorecase false

# Verifica differenze case
git mv README.md readme.md
git status  # Mostrerà la modifica
```

### Integrazione Desktop Environment

```bash
# Nautilus (GNOME) - script per aprire terminal in cartella Git
mkdir -p ~/.local/share/nautilus/scripts
cat > ~/.local/share/nautilus/scripts/git-terminal << 'EOF'
#!/bin/bash
cd "$NAUTILUS_SCRIPT_CURRENT_URI"
gnome-terminal
EOF
chmod +x ~/.local/share/nautilus/scripts/git-terminal
```

---

## 🔗 Prossimi Passi

✅ **Completato**: Setup Linux
🎯 **Prossimo**: [Primo Repository](../../03-Primo-Repository-Git/README.md)

---

## 📚 Risorse Linux-Specifiche

- [Git on Linux Documentation](https://git-scm.com/download/linux)
- [Git Extras Documentation](https://github.com/tj/git-extras)
- [Linux Terminal Git Integration](https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-Bash)
