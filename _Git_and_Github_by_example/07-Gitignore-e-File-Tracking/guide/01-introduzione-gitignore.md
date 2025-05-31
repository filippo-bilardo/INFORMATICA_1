# Introduzione a .gitignore

## 📖 Cos'è il file .gitignore

Il file `.gitignore` è uno dei file più importanti in un repository Git. Questo file speciale dice a Git quali file o directory ignorare, ovvero non tracciare nelle modifiche del repository.

### 🎯 Scopo del .gitignore

```bash
# Senza .gitignore - Problemi comuni:
$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
    node_modules/           # Dipendenze (migliaia di file!)
    .env                    # File con password/chiavi
    dist/                   # File generati automaticamente
    .DS_Store              # File di sistema macOS
    *.log                  # File di log temporanei
    coverage/              # Report di test coverage
```

## 💡 Perché usare .gitignore

### 1. **Performance del Repository**
```bash
# Repository senza .gitignore
$ git add .
# Aggiunge migliaia di file non necessari!

# Repository con .gitignore
$ git add .
# Aggiunge solo i file sorgente essenziali
```

### 2. **Sicurezza**
```gitignore
# File da NON committare mai
.env
config/secrets.yml
*.key
*.pem
database.yml
```

### 3. **Collaborazione**
```gitignore
# File specifici del sistema operativo
.DS_Store      # macOS
Thumbs.db      # Windows
*.swp          # Vim
.vscode/       # VS Code settings (opzionale)
```

### 4. **Semplicità**
```bash
# Status pulito grazie a .gitignore
$ git status
On branch main
Changes to be committed:
  modified:   src/index.js
  new file:   src/utils.js
```

## 🗂️ Posizionamento del .gitignore

### .gitignore Principale (Root)
```
mio-progetto/
├── .gitignore          # ← File principale
├── src/
├── tests/
└── package.json
```

### .gitignore in Sottodirectory
```
mio-progetto/
├── .gitignore          # Regole globali
├── src/
│   └── .gitignore      # Regole specifiche per src/
├── docs/
│   └── .gitignore      # Regole specifiche per docs/
└── tests/
    └── .gitignore      # Regole specifiche per tests/
```

## 📝 Creazione del File .gitignore

### Metodo 1: Da Terminale
```bash
# Creare .gitignore vuoto
$ touch .gitignore

# Aggiungere subito alcune regole base
$ echo "node_modules/" >> .gitignore
$ echo ".env" >> .gitignore
$ echo "*.log" >> .gitignore
```

### Metodo 2: Da Editor
```bash
# Aprire con il tuo editor preferito
$ code .gitignore
$ nano .gitignore
$ vim .gitignore
```

### Metodo 3: Da Template Online
```bash
# Usando gitignore.io
$ curl -L https://www.toptal.com/developers/gitignore/api/node,react,vscode > .gitignore
```

## 🎯 Principi Base

### 1. **Cosa NON committare**
- ❌ File temporanei di sistema
- ❌ File di configurazione con credenziali
- ❌ Dipendenze scaricabili (node_modules, vendor/)
- ❌ File generati da build/compilazione
- ❌ File di cache e log
- ❌ File di backup e copie

### 2. **Cosa committare**
- ✅ Codice sorgente
- ✅ File di configurazione pubblici
- ✅ Documentazione
- ✅ Script di build e deploy
- ✅ Test e specifiche
- ✅ File di licenza e README

## 🔍 Verifica Funzionamento

### Controllare cosa viene ignorato
```bash
# Vedere file ignorati nella directory corrente
$ git status --ignored

# Controllare se un file specifico è ignorato
$ git check-ignore -v node_modules/
.gitignore:1:node_modules/    node_modules/

# Vedere tutti i file ignorati
$ git clean -ndX
```

### Debug del .gitignore
```bash
# Perché questo file non viene ignorato?
$ git check-ignore -v src/config.js
# Output vuoto = file NON ignorato

# Testare un pattern specifico
$ git ls-files --others --ignored --exclude-standard
```

## ⚠️ Errori Comuni

### 1. **File già tracciato**
```bash
# Problema: file già in Git prima di aggiungere .gitignore
$ git status
    modified:   .env    # Già tracciato!

# Soluzione: rimuovere dal tracking
$ git rm --cached .env
$ echo ".env" >> .gitignore
$ git commit -m "Stop tracking .env file"
```

### 2. **Sintassi errata**
```gitignore
# ❌ SBAGLIATO
node_modules     # Manca la slash finale per directory
*.log .cache     # Una regola per riga
```

```gitignore
# ✅ CORRETTO  
node_modules/    # Directory con slash
*.log           # Pattern su riga separata
.cache/         # Directory cache
```

### 3. **Pattern troppo aggressivi**
```gitignore
# ❌ PERICOLOSO - ignora TUTTI i .env ovunque
*.env

# ✅ MEGLIO - specifico per il root
/.env

# ✅ ANCORA MEGLIO - con commento
# File di configurazione locale
.env
.env.local
```

## 🧪 Quiz di Verifica

### Domanda 1
Quale comando mostra i file che sono ignorati da Git?
- A) `git status`
- B) `git status --ignored`
- C) `git ignored`
- D) `git show-ignored`

### Domanda 2
Cosa succede se aggiungi una regola `.gitignore` per un file già tracciato?
- A) Il file viene automaticamente rimosso dal repository
- B) Il file continua ad essere tracciato
- C) Git mostra un errore
- D) Il file viene spostato in una directory speciale

### Domanda 3
Dove dovrebbe essere posizionato il file `.gitignore` principale?
- A) Nella directory home dell'utente
- B) Nella directory `.git/`
- C) Nella root del repository
- D) Nella directory `src/`

## 💡 Esercizio Pratico

Crea un nuovo repository e sperimenta:

```bash
# 1. Crea repository di test
$ mkdir test-gitignore
$ cd test-gitignore
$ git init

# 2. Crea alcuni file di test
$ touch importante.txt
$ touch temporaneo.log
$ mkdir node_modules
$ touch node_modules/package.js

# 3. Osserva cosa vede Git
$ git status

# 4. Crea .gitignore
$ echo "*.log" > .gitignore
$ echo "node_modules/" >> .gitignore

# 5. Verifica la differenza
$ git status
```

## 🔗 Link Utili

- [📚 Documentazione Git](https://git-scm.com/docs/gitignore)
- [🛠️ Template Generator](https://www.toptal.com/developers/gitignore)
- [📄 GitHub Templates](https://github.com/github/gitignore)

---

**Prossimo:** [Pattern e Sintassi](./02-pattern-sintassi.md) per imparare le regole avanzate di .gitignore!
