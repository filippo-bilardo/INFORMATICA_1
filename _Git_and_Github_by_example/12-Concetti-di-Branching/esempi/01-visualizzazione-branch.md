# 01 - Visualizzazione e Struttura dei Branch

## 🎯 Obiettivo
Comprendere come visualizzare e interpretare la struttura dei branch in Git attraverso diversi strumenti e rappresentazioni grafiche.

## 📋 Scenari di Apprendimento

### Scenario 1: Repository con Branching Lineare

#### Setup Iniziale
```bash
# Creiamo un repository dimostrativo
git init branch-visualization-demo
cd branch-visualization-demo

# Setup iniziale
echo "# Progetto Demo Branch" > README.md
git add README.md
git commit -m "Initial commit"

echo "console.log('Hello World');" > app.js
git add app.js
git commit -m "Add basic app structure"

echo "body { font-family: Arial; }" > style.css
git add style.css
git commit -m "Add basic styling"
```

#### Visualizzazione Base
```bash
# Visualizzazione cronologia lineare
git log --oneline
# Output atteso:
# abc123f Add basic styling
# def456a Add basic app structure  
# ghi789b Initial commit

# Visualizzazione grafica
git log --graph --oneline
# Mostra la struttura lineare attuale
```

### Scenario 2: Repository con Branch Multipli

#### Creazione Struttura Multi-Branch
```bash
# Creiamo branch per feature
git checkout -b feature/authentication
echo "// Authentication module" > auth.js
git add auth.js
git commit -m "Add authentication scaffold"

echo "// Login form" >> auth.js
git add auth.js
git commit -m "Implement login form"

# Torniamo su main e creiamo altro branch
git checkout main
git checkout -b feature/database
echo "// Database connection" > db.js
git add db.js
git commit -m "Add database module"

# Aggiungiamo commit su main
git checkout main
echo "<!-- Basic HTML structure -->" > index.html
git add index.html
git commit -m "Add HTML template"
```

#### Visualizzazione Avanzata
```bash
# Visualizzazione completa con tutti i branch
git log --graph --oneline --all
# Output simile a:
# * 1a2b3c4 (HEAD -> main) Add HTML template
# | * 5d6e7f8 (feature/database) Add database module
# |/  
# | * 9g0h1i2 (feature/authentication) Implement login form
# | * 3j4k5l6 Add authentication scaffold
# |/  
# * def456a Add basic app structure
# * ghi789b Initial commit

# Visualizzazione dettagliata
git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --all
```

### Scenario 3: Visualizzazione con Tool Grafici

#### Git Log con Formato Personalizzato
```bash
# Alias utili per visualizzazione
git config --global alias.tree "log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
git config --global alias.history "log --graph --oneline --all"

# Utilizzo degli alias
git tree --all
git history
```

#### Strumenti Visual
```bash
# Git GUI integrato
gitk --all &

# Oppure se hai installato tig
tig --all

# Per utenti VS Code
# Installa l'estensione "Git Graph"
code .
# Apri la palette comandi (Ctrl+Shift+P)
# Cerca "Git Graph: View Git Graph"
```

## 🔍 Interpretazione delle Visualizzazioni

### Elementi Chiave nelle Visualizzazioni

#### Simboli e Notazioni
```
* = Commit point
| = Branch line
\ = Branch merge/diverge
/ = Branch merge/diverge
```

#### Esempio di Lettura
```
* 1a2b3c4 (HEAD -> main) Add HTML template
| * 5d6e7f8 (feature/database) Add database module
|/  
| * 9g0h1i2 (feature/authentication) Implement login form
| * 3j4k5l6 Add authentication scaffold
|/  
* def456a Add basic app structure
* ghi789b Initial commit
```

**Interpretazione:**
1. `main` è attualmente su commit `1a2b3c4`
2. `feature/database` si è separato da `main` dopo `def456a`
3. `feature/authentication` ha 2 commit separati dal punto di divergenza
4. Tutti i branch condividono la storia comune fino a `def456a`

### Confronto Branch Status

#### Vedere Differenze tra Branch
```bash
# Lista tutti i branch
git branch -a
# * main
#   feature/authentication  
#   feature/database

# Vedere commit unici per ogni branch
git log main..feature/authentication --oneline
# 9g0h1i2 Implement login form
# 3j4k5l6 Add authentication scaffold

# Vedere commit che main ha ma feature/authentication no
git log feature/authentication..main --oneline
# 1a2b3c4 Add HTML template

# Vedere divergenza
git show-branch main feature/authentication feature/database
```

## 🏃‍♂️ Esercizio Pratico

### Esercizio 1: Analisi Repository Esistente
1. Clona un repository pubblico con branch multipli:
   ```bash
   git clone https://github.com/microsoft/vscode.git vscode-analysis
   cd vscode-analysis
   ```

2. Esplora la struttura dei branch:
   ```bash
   git branch -r | head -10  # Primi 10 branch remoti
   git log --graph --oneline main | head -20
   ```

3. Identifica pattern di branching utilizzati

### Esercizio 2: Creazione Struttura Personalizzata
1. Crea un repository con 3 branch che rappresentano:
   - `main`: versione stabile
   - `develop`: sviluppo in corso
   - `feature/user-profile`: funzionalità specifica

2. Aggiungi commit differenti su ogni branch

3. Utilizza almeno 3 metodi diversi per visualizzare la struttura

## 🎯 Risultati Attesi

Dopo questo esempio dovresti:
- ✅ Saper leggere visualizzazioni Git complesse
- ✅ Comprendere la relazione tra branch
- ✅ Identificare punti di divergenza e convergenza
- ✅ Utilizzare strumenti di visualizzazione appropriati
- ✅ Interpretare simboli e notazioni Git

## 💡 Tips e Best Practices

### Alias Utili
```bash
# Aggiungere al .gitconfig
[alias]
    lg = log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
    tree = log --graph --oneline --all
    branches = branch -a
    remotes = remote -v
```

### Strumenti Consigliati
- **Comando:** `git log --graph --oneline --all`
- **GUI:** GitKraken, SourceTree, Git GUI
- **VS Code:** Git Graph extension
- **Terminal:** tig, lazygit

## 🔗 Prossimi Passi

Ora che comprendi come visualizzare i branch, sei pronto per:
- [02 - Scenari di Branching](./02-scenari-branching.md)
- [Guida: Creazione e Gestione Branch](../guide/03-head-puntatori.md)

---

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 11-Annullare-Modifiche](../../11-Annullare-Modifiche/README.md)
- [➡️ 02-Scenari di Branching](./02-scenari-branching.md)
