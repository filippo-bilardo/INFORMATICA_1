# 01 - Inizializzazione Repository Pratica

## 📋 Obiettivo
Imparare l'inizializzazione di repository Git attraverso scenari pratici reali.

## 🎯 Scenario: Nuovo Progetto Web

Stai iniziando un nuovo progetto per un sito web personale. Devi creare la struttura base e inizializzare il controllo versione.

### Step 1: Preparazione Ambiente
```bash
# Naviga nella directory di lavoro
cd ~/Documents/progetti

# Crea cartella progetto
mkdir mio-sito-web
cd mio-sito-web

# Verifica che non sia già un repository Git
ls -la | grep .git
# Se non mostra nulla, procedi con l'inizializzazione
```

### Step 2: Inizializzazione
```bash
# Inizializza repository Git
git init

# Verifica creazione cartella .git
ls -la
# Dovresti vedere: drwxr-xr-x 7 user user 4096 ... .git

# Controlla status
git status
```

**Output Atteso:**
```
On branch main

No commits yet

nothing to commit (create/copy files and run "git add" to track)
```

### Step 3: Configurazione Branch Principale
```bash
# Se usi Git version < 2.28, potresti avere 'master' come default
# Cambia a 'main' per seguire le convenzioni moderne
git branch -M main

# Verifica branch corrente
git branch
```

### Step 4: Creazione Struttura Progetto
```bash
# Crea struttura base
mkdir css js images
touch index.html css/style.css js/script.js

# Verifica struttura
tree
# o se tree non è disponibile:
find . -type f -o -type d | head -10
```

### Step 5: Verifica Status Post-Creazione
```bash
git status
```

**Output Atteso:**
```
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        css/
        index.html
        js/

nothing added to commit but untracked files present (use "git add" to track)
```

## 🔧 Variazione: Repository con Contenuto Esistente

### Scenario: Progetto JavaScript Esistente
```bash
# Simula progetto esistente
mkdir progetto-esistente
cd progetto-esistente

# Crea contenuto pre-esistente
cat > package.json << 'EOF'
{
  "name": "mio-progetto",
  "version": "1.0.0",
  "description": "Un progetto JavaScript esistente",
  "main": "index.js",
  "scripts": {
    "start": "node index.js"
  }
}
EOF

cat > index.js << 'EOF'
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.listen(3000, () => {
  console.log('Server running on port 3000');
});
EOF

# Ora inizializza Git
git init
git status
```

## 🎯 Variazione: Repository con Template

### Scenario: Usa Template Personalizzato
```bash
# Crea template directory (solo per demo)
mkdir -p ~/.git-templates/hooks

# Crea hook di esempio
cat > ~/.git-templates/hooks/pre-commit << 'EOF'
#!/bin/bash
echo "Eseguendo controlli pre-commit..."
# Qui potresti aggiungere linting, test, etc.
EOF

chmod +x ~/.git-templates/hooks/pre-commit

# Inizializza con template
mkdir progetto-con-template
cd progetto-con-template
git init --template=~/.git-templates

# Verifica hook installato
ls -la .git/hooks/
```

## 📊 Verifica e Debug

### Comandi Diagnostici
```bash
# Informazioni repository
git rev-parse --git-dir        # Mostra path .git
git rev-parse --show-toplevel  # Mostra root del repository
git rev-parse --is-inside-work-tree  # Conferma che sei in un repo

# Configurazione repository
git config --list --local      # Config specifiche di questo repo
git branch -a                  # Mostra tutti i branch
```

### Possibili Problemi e Soluzioni

**Problema 1: Permission Denied**
```bash
# Se ottieni errori di permessi
sudo chown -R $USER:$USER .git
chmod -R 755 .git
```

**Problema 2: Repository Già Esistente**
```bash
# Se inizializzi accidentalmente in repo esistente
# Git mostrerà: "Reinitialized existing Git repository"
# Per verificare se è sicuro:
git status
git log --oneline  # Vedi se hai cronologia esistente
```

**Problema 3: Directory Sbagliata**
```bash
# Se hai inizializzato nella directory sbagliata
rm -rf .git  # ATTENZIONE: Questo elimina tutto il controllo versione!
# Poi naviga nella directory corretta e ripeti git init
```

## 🧪 Esercizi di Consolidamento

### Esercizio A: Progetti Multipli
1. Crea 3 directory separate: `web-app`, `mobile-app`, `api-server`
2. Inizializza ognuna come repository Git separato
3. Verifica che ogni directory abbia la propria `.git`
4. Crea un file README.md in ognuna con contenuto diverso

### Esercizio B: Migrazione Progetto
1. Simula un progetto senza controllo versione con alcuni file
2. Naviga nella directory e inizializza Git
3. Verifica quali file Git considera "untracked"
4. Non fare ancora add/commit (lo faremo nel prossimo esempio)

### Esercizio C: Repository Nested (Anti-pattern)
1. Crea directory `progetto-principale`
2. Inizializza Git in `progetto-principale`
3. Crea subdirectory `sottoprogetto`
4. **NON** inizializzare Git in `sottoprogetto`
5. Verifica che `git status` in `progetto-principale` mostri anche i file di `sottoprogetto`

## 💡 Suggerimenti Pro

### 1. **Alias Utili**
```bash
# Crea alias per inizializzazione rapida
git config --global alias.init-main '!git init && git branch -M main'

# Uso: git init-main invece di git init + git branch -M main
```

### 2. **Script di Setup Progetto**
```bash
# Crea script setup-project.sh
cat > setup-project.sh << 'EOF'
#!/bin/bash
PROJECT_NAME=$1
mkdir $PROJECT_NAME
cd $PROJECT_NAME
git init
git branch -M main
echo "# $PROJECT_NAME" > README.md
echo "Progetto $PROJECT_NAME inizializzato con successo!"
EOF

chmod +x setup-project.sh
# Uso: ./setup-project.sh nome-progetto
```

### 3. **Template README**
```bash
# Dopo git init, crea sempre un README base
cat > README.md << 'EOF'
# Nome Progetto

## Descrizione
Breve descrizione del progetto.

## Installazione
```bash
# Istruzioni di installazione
```

## Uso
```bash
# Esempi di utilizzo
```

## Contribuire
Istruzioni per contribuire al progetto.

## Licenza
Informazioni sulla licenza.
EOF
```

## 🔗 File Collegati
- [Guide 01 - Inizializzazione Repository](../guide/01-inizializzazione-repository.md)
- [Esercizio 01 - Quiz Inizializzazione](../esercizi/01-quiz-inizializzazione.md)
- [Esempio 02 - Primo Add e Commit](./02-primo-add-commit.md)
