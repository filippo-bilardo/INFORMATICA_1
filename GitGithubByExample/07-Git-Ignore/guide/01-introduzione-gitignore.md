# Introduzione a .gitignore

## 🎯 Cos'è .gitignore

Il file `.gitignore` è un meccanismo di Git che permette di specificare quali file e directory devono essere ignorati dal sistema di controllo versione. È uno strumento fondamentale per mantenere repository puliti e sicuri.

## 🤔 Perché Usare .gitignore

### Problemi Risolti
1. **File temporanei** che cambiano continuamente
2. **Build artifacts** che si rigenerano automaticamente  
3. **Dipendenze** che occupano spazio inutilmente
4. **File sensibili** con credenziali o dati personali
5. **File IDE** specifici dell'ambiente di sviluppo

### Vantaggi
- ✅ Repository più pulito e leggero
- ✅ Migliori prestazioni di Git
- ✅ Evita conflitti su file generati automaticamente
- ✅ Protegge da commit accidentali di file sensibili
- ✅ Migliora la collaborazione in team

## 📋 Come Funziona

### Meccanismo Base
Git controlla se un file corrisponde ai pattern nel `.gitignore` prima di tracciarlo:

```
File nuovo → Controlla .gitignore → Se match: IGNORA, altrimenti: TRACCIA
```

### Ordine di Priorità
1. **Pattern più specifici** hanno precedenza
2. **Esclusioni** (!) sovrascrivono le inclusioni
3. **File già tracciati** non vengono ignorati automaticamente

## 📂 Posizionamento del File

### .gitignore Locale (Raccomandato)
```
my-project/
├── .gitignore     ← File principale del progetto
├── src/
│   └── .gitignore ← Rules specifiche per src/
└── docs/
    └── .gitignore ← Rules specifiche per docs/
```

**Vantaggi:**
- Condiviso con il team
- Versionato con il progetto
- Specifico per il tipo di progetto

### .gitignore Globale
```bash
# Configura gitignore globale
git config --global core.excludesfile ~/.gitignore_global
```

**Uso tipico:**
- File di sistema (.DS_Store, Thumbs.db)
- Configurazioni IDE personali
- File di backup dell'editor

## 🎯 Quando Usare .gitignore

### ✅ DA IGNORARE
```gitignore
# Build outputs
build/
dist/
target/

# Dependencies
node_modules/
vendor/
__pycache__/

# Logs
*.log
logs/

# Environment variables
.env
.env.local

# IDE files
.vscode/
.idea/
*.swp

# OS files
.DS_Store
Thumbs.db

# Temporary files
*.tmp
*.cache
temp/
```

### ❌ DA NON IGNORARE
```gitignore
# Non ignorare questi file importanti:
# !README.md
# !package.json
# !requirements.txt
# !Dockerfile
# !docker-compose.yml
```

## 🔍 Verifica del Funzionamento

### Comandi Utili
```bash
# Verifica se un file è ignorato
git check-ignore -v filename.txt

# Mostra tutti i file ignorati
git status --ignored

# Lista file tracciati
git ls-files

# Debug pattern gitignore
git check-ignore -v **/*
```

### Status Output
```bash
$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        src/important.js

Ignored files:
  (use "git add -f <file>..." to include in what will be committed)
        build/
        node_modules/
        .env
```

## 🛠️ Strumenti e Risorse

### Generator Online
- **gitignore.io**: Genera .gitignore per combinazioni di tecnologie
- **GitHub Templates**: Collezione ufficiale di template

### Command Line Tools
```bash
# Usando npx (Node.js)
npx gitignore node,react,vscode

# Usando curl
curl -sL https://www.toptal.com/developers/gitignore/api/node,react > .gitignore
```

## 📝 Esempi Base

### Progetto Node.js Minimal
```gitignore
# Dependencies
node_modules/

# Logs
npm-debug.log*

# Environment variables
.env

# Build output
dist/
```

### Progetto Python Minimal
```gitignore
# Byte-compiled files
__pycache__/
*.pyc

# Virtual environment
venv/
env/

# Distribution files
dist/
build/
```

## ⚠️ Errori Comuni

### 1. File Già Tracciati
```bash
# ❌ PROBLEMA: .gitignore non funziona su file già committati
echo "config.json" >> .gitignore
# Il file config.json continua a essere tracciato

# ✅ SOLUZIONE: Rimuovi dal tracking
git rm --cached config.json
git commit -m "Remove config.json from tracking"
```

### 2. Pattern Troppo Generici
```gitignore
# ❌ PROBLEMA: Ignora troppi file
*

# ✅ SOLUZIONE: Sii specifico
*.log
*.tmp
```

### 3. Mancanza di Commenti
```gitignore
# ❌ DIFFICILE DA MANTENERE
node_modules/
.env
dist/

# ✅ CHIARO E MANTENIBILE
# Dependencies
node_modules/

# Environment variables
.env

# Build output
dist/
```

## 🧪 Esercizio Pratico

Crea un file `.gitignore` base:

```bash
# 1. Crea un progetto di test
mkdir test-gitignore
cd test-gitignore
git init

# 2. Crea alcuni file
echo "console.log('app');" > app.js
echo "APP_SECRET=12345" > .env
mkdir build
echo "bundled code" > build/app.min.js
mkdir node_modules
echo "{}" > node_modules/package.json

# 3. Verifica status prima di .gitignore
git status

# 4. Crea .gitignore
cat > .gitignore << 'EOF'
# Environment variables
.env

# Dependencies
node_modules/

# Build output
build/
EOF

# 5. Verifica status dopo .gitignore
git status
```

## 🎯 Quiz di Verifica

1. **Dove posizioni il file .gitignore principale del progetto?**
   - a) Nella cartella .git/
   - b) Nella root del repository
   - c) Nella cartella src/

2. **Cosa succede ai file già tracciati quando li aggiungi a .gitignore?**
   - a) Vengono automaticamente ignorati
   - b) Continuano a essere tracciati
   - c) Vengono eliminati dal repository

3. **Quale comando usi per verificare se un file è ignorato?**
   - a) `git ignore filename`
   - b) `git check-ignore filename`
   - c) `git status filename`

**Risposte:** 1-b, 2-b, 3-b

## 🔗 Prossimi Passi

- [Pattern e Sintassi →](./02-pattern-sintassi.md)
- [Esempi Pratici →](../esempi/01-setup-nodejs.md)
- [Torna alla Panoramica ←](../README.md)

---

> 💡 **Suggerimento**: Inizia sempre un nuovo progetto creando un `.gitignore` appropriato prima del primo commit!
