# Strumenti Grafici

## 📖 Visualizzazione Avanzata della Cronologia

Gli strumenti grafici offrono una rappresentazione visuale della cronologia Git che può rendere molto più semplice comprendere branch, merge, e l'evoluzione del progetto. Questa guida esplora le opzioni disponibili dai built-in Git agli strumenti esterni avanzati.

## 🎯 Strumenti Built-in Git

### Gitk - Il Visualizzatore Git Nativo
```bash
# Avviare gitk
gitk

# Gitk per tutti i branch
gitk --all

# Gitk per file specifici
gitk filename.js

# Gitk con range di date
gitk --since="2024-01-01" --until="2024-12-31"

# Gitk per autore specifico
gitk --author="Mario Rossi"
```

#### Funzionalità Gitk
- **Vista grafica** della cronologia
- **Diff integrato** per ogni commit
- **Ricerca** nei commit e contenuti
- **Navigazione** tra branch
- **Annotazioni** dei file

### Git GUI - Interface Grafica Nativa
```bash
# Avviare Git GUI
git gui

# Git GUI per repository specifico
git gui --repo /path/to/repo
```

#### Funzionalità Git GUI
- **Staging interattivo**
- **Commit con interface grafica**
- **Diff visuale**
- **Gestione branch** base
- **Push/Pull** operations

## 🖥️ Strumenti Web e Online

### GitHub Desktop
```bash
# Installazione (Ubuntu/Debian)
wget -qO - https://mirror.mwt.me/ghd/gpgkey | sudo apt-key add -
echo "deb [arch=amd64] https://mirror.mwt.me/ghd/deb/ stable main" | sudo tee /etc/apt/sources.list.d/github-desktop.list
sudo apt update && sudo apt install github-desktop

# Uso
github-desktop
```

#### Caratteristiche GitHub Desktop
- **Integrazione GitHub** nativa
- **Diff visuale** avanzato
- **Gestione branch** intuitiva
- **Pull Request** integration
- **Merge conflict** resolution

### GitKraken
```bash
# Download da https://www.gitkraken.com/
# Installazione su Linux
sudo dpkg -i gitkraken-amd64.deb
```

#### Funzionalità GitKraken
- **Grafico cronologia** molto avanzato
- **Diff a 3 vie**
- **Gestione remoti** multipli
- **Integrazione servizi** (GitHub, GitLab, Bitbucket)
- **Tema personalizzabile**

## 💻 Strumenti per Terminale

### Tig - Text-mode Interface for Git
```bash
# Installazione
sudo apt install tig

# Uso base
tig

# Tig per file specifico
tig filename.js

# Tig con filtri
tig --since="1 month ago"
```

#### Comandi Tig Essenziali
```bash
# Navigazione
j/k         # Su/giù nelle righe
Enter       # Mostra dettagli commit
q           # Indietro/esci
h           # Help

# Ricerca
/pattern    # Ricerca in avanti
?pattern    # Ricerca indietro
n           # Prossimo risultato

# Views
m           # Main view (cronologia)
d           # Diff view
l           # Log view
f           # File view
b           # Blame view
```

### Lazygit - Terminal UI for Git
```bash
# Installazione
sudo apt install lazygit

# Uso
lazygit
```

#### Funzionalità Lazygit
- **Interface tutto-in-uno**
- **Staging interattivo**
- **Branch management**
- **Stash operations**
- **Configurabile** con keybindings

## 🔧 Integrazione con IDE

### VS Code
```bash
# Estensioni raccomandate per Git
# - GitLens
# - Git Graph
# - Git History

# Comandi utili VS Code
Ctrl+Shift+G    # Git panel
Ctrl+Shift+P    # Command palette -> Git commands
```

#### GitLens Features
- **Blame annotations** inline
- **Commit details** on hover
- **File history** navigation
- **Repository insights**
- **Compare branches/commits**

### Vim/Neovim con Fugitive
```bash
# Installazione Fugitive (con vim-plug)
# Aggiungere a .vimrc:
# Plug 'tpope/vim-fugitive'

# Comandi in Vim
:Git log --oneline
:Git show
:Git blame
```

## 🌐 Strumenti Web-based

### GitLab/GitHub Web Interface
```bash
# Accesso via browser
# - Cronologia commit
# - Network graph
# - Blame view
# - Compare branches
# - Pull/Merge request view
```

### Gitiles (per server Git)
```bash
# Web interface per repository Git
# Fornisce:
# - Log navigation
# - Diff viewing
# - Branch browsing
# - Search capabilities
```

## 📊 Configurazione e Personalizzazione

### Configurare Git per Strumenti Grafici
```bash
# Impostare editor grafico default
git config --global core.editor "code --wait"

# Impostare diff tool grafico
git config --global diff.tool vimdiff
git config --global difftool.prompt false

# Impostare merge tool grafico
git config --global merge.tool vimdiff
```

### Configurare Diff Tools Esterni
```bash
# VSCode come diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'

# Meld come diff tool
git config --global diff.tool meld
git config --global difftool.meld.cmd 'meld $LOCAL $REMOTE'

# Uso
git difftool
git difftool HEAD~1
```

### Personalizzare Gitk
```bash
# File di configurazione gitk: ~/.gitk

# Esempio configurazione
# geometry 1200x800+100+100
# update
# background white
# foreground black
```

## 🎨 Visualizzazioni Avanzate

### Git Log con ASCII Art
```bash
# Configurare alias per grafico ASCII avanzato
git config --global alias.graph "log --graph --pretty=format:'%C(red)%h%C(reset) -%C(yellow)%d%C(reset) %s %C(green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --all"

# Versione ancora più dettagliata
git config --global alias.tree "log --graph --full-history --all --color --pretty=format:'%x1b[31m%h%x09%x1b[32m%d%x1b[0m%x20%s'"
```

### Combinare con Altri Tools
```bash
# Log con fzf per ricerca interattiva
git log --oneline | fzf --preview 'git show --color=always {+1}'

# Integrare con less per paginazione
git log --graph --color=always | less -R

# Export per tool esterni
git log --pretty=format:"%h,%an,%ad,%s" --date=short > commits.csv
```

## 🔍 Strumenti Specializzati

### Git-forest (Tree-like visualization)
```bash
# Installazione
pip install git-forest

# Uso
git-forest --all
git-forest --since="1 month ago"
```

### Git-big-picture
```bash
# Installazione
pip install git-big-picture

# Genera grafico del repository
git big-picture -o repo-graph.png
git big-picture --format svg
```

### Gource (Animated visualization)
```bash
# Installazione
sudo apt install gource

# Visualizzazione animata della cronologia
gource
gource --max-files 0 --seconds-per-day 0.1

# Export video
gource --output-ppm-stream - | ffmpeg -y -r 30 -f image2pipe -vcodec ppm -i - -vcodec libx264 repo-history.mp4
```

## 📱 Mobile e Cross-platform

### Working Copy (iOS)
- **Full Git client** per iPad/iPhone
- **Diff e merge** capabilities
- **Integrazione** con editor esterni

### Git2Go (iOS)
- **Repository management**
- **Commit e push** da mobile
- **Conflict resolution**

### Termux (Android)
```bash
# Git completo su Android
pkg install git tig
```

## 🧩 Script e Automazione

### Script per Avviare Strumenti
```bash
#!/bin/bash
# git-visual.sh - Script per scegliere tool visuale

echo "Seleziona strumento di visualizzazione:"
echo "1) gitk"
echo "2) tig"
echo "3) lazygit"
echo "4) GitKraken"
echo "5) VS Code"

read -p "Scelta (1-5): " choice

case $choice in
    1) gitk --all & ;;
    2) tig ;;
    3) lazygit ;;
    4) gitkraken . & ;;
    5) code . ;;
    *) echo "Scelta non valida" ;;
esac
```

### Wrapper per Diff Grafici
```bash
#!/bin/bash
# git-diff-visual.sh

if command -v code >/dev/null 2>&1; then
    git difftool --tool=vscode "$@"
elif command -v meld >/dev/null 2>&1; then
    git difftool --tool=meld "$@"
else
    git diff "$@"
fi
```

## 🎯 Quando Usare Quale Strumento

### Per Analisi Rapida
- **tig**: Veloce, leggero, perfetto per server
- **git log --graph**: Built-in, sempre disponibile

### Per Development Quotidiano
- **GitLens in VS Code**: Integrato nell'editor
- **GitHub Desktop**: Per workflow GitHub-centric
- **lazygit**: Terminal users

### Per Analisi Complesse
- **GitKraken**: Visualizzazione avanzata, team collaboration
- **gitk**: Built-in, sempre funziona
- **Gource**: Per presentazioni e overview

### Per Team e Review
- **GitHub/GitLab web**: Centralizzato, accessibile
- **GitKraken**: Collaboration features
- **VS Code Live Share**: Real-time collaboration

## 🧪 Quiz di Verifica

### Domanda 1
Quale comando avvia il visualizzatore grafico nativo di Git?
- A) `git gui`
- B) `gitk`
- C) `git visual`
- D) `git graph`

<details>
<summary>Risposta</summary>
**B) `gitk`**

`gitk` è il visualizzatore grafico della cronologia Git, mentre `git gui` è l'interface per staging e commit.
</details>

### Domanda 2
Come configurare VS Code come diff tool per Git?
- A) `git config diff.tool vscode`
- B) `git config --global diff.tool vscode`
- C) `git config difftool.vscode.cmd 'code --diff'`
- D) Entrambe A e C, ma meglio B

<details>
<summary>Risposta</summary>
**D) Entrambe A e C, ma meglio B**

Serve sia impostare il tool che il comando, e --global lo rende disponibile ovunque.
</details>

### Domanda 3
Quale strumento offre visualizzazione animata della cronologia Git?
- A) gitk
- B) tig
- C) gource
- D) lazygit

<details>
<summary>Risposta</summary>
**C) gource**

Gource crea visualizzazioni animate dell'evoluzione del repository nel tempo.
</details>

## 🚀 Best Practices

### Scegliere lo Strumento Giusto
1. **Contesto**: Terminal vs GUI vs Web
2. **Complessità**: Repository piccoli vs grandi
3. **Team**: Strumenti condivisi e accessibili
4. **Performance**: Velocità vs funzionalità

### Configurazione Ottimale
```bash
# Setup completo per sviluppatori
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'

# Alias per strumenti rapidi
git config --global alias.visual '!gitk --all &'
git config --global alias.tui '!tig'
```

## 🔄 Prossimi Passi

Dopo aver esplorato gli strumenti grafici, puoi:
1. **Praticare** con esempi reali del tuo repository
2. **Sperimentare** con diversi strumenti per trovare il tuo preferito
3. **Integrare** strumenti nel tuo workflow quotidiano
4. **Configurare** l'ambiente di sviluppo ottimale

---

**Continua con**: [Esempi Pratici](../esempi/01-log-base-formattazione.md) - Mettere in pratica le conoscenze acquisite
