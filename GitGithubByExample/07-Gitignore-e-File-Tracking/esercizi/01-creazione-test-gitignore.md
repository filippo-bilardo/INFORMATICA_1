# 01 - Creazione e Test File .gitignore

## 🎯 Obiettivo
Creare e testare un file `.gitignore` funzionale per diversi tipi di progetto.

## 📋 Prerequisiti
- Repository Git inizializzato
- Conoscenza dei comandi base Git
- Editor di testo

## ⏱️ Tempo Stimato
30-45 minuti

## 🚀 Esercizio Pratico

### Step 1: Setup Progetto Test

```bash
# Crea una nuova directory per l'esercizio
mkdir test-gitignore
cd test-gitignore

# Inizializza repository Git
git init

# Crea README
echo "# Test Gitignore Project" > README.md
git add README.md
git commit -m "Initial commit"
```

### Step 2: Crea File di Test

Crea diversi tipi di file che tipicamente vanno ignorati:

```bash
# File di log
echo "2024-05-29 10:00:00 - Application started" > app.log
echo "2024-05-29 10:01:00 - User login: admin" > debug.log

# File temporanei
echo "Contenuto temporaneo" > temp.tmp
echo "Cache data" > cache.cache

# File di configurazione sensibili
echo "DATABASE_PASSWORD=supersecret123" > .env
echo "API_KEY=abc123xyz789" > config.ini

# File di backup
cp README.md README.md.bak
cp README.md README.md~

# Directory di build
mkdir build
echo "Built application" > build/app.exe
mkdir dist
echo "Distribution package" > dist/package.zip

# File IDE
mkdir .vscode
echo '{"editor.fontSize": 14}' > .vscode/settings.json

# File sistema
echo "System temp" > .DS_Store
echo "Windows thumb" > Thumbs.db

# File di dipendenze (simula node_modules)
mkdir node_modules
echo "Dependency files" > node_modules/package.txt
```

### Step 3: Verifica Status

```bash
# Controlla lo status attuale
git status
```

**Risultato atteso**: Dovresti vedere TUTTI i file come "Untracked files".

### Step 4: Crea .gitignore Base

```bash
# Crea il file .gitignore
touch .gitignore
```

Aggiungi questo contenuto al file `.gitignore`:

```gitignore
# File di log
*.log

# File temporanei
*.tmp
*.cache

# File di configurazione sensibili
.env
config.ini

# File di backup
*.bak
*~

# Directory di build
build/
dist/

# File IDE
.vscode/
.idea/

# File di sistema
.DS_Store
Thumbs.db

# Dipendenze
node_modules/
```

### Step 5: Test .gitignore

```bash
# Aggiungi .gitignore al repository
git add .gitignore
git commit -m "Add: comprehensive .gitignore file"

# Verifica cosa Git vede ora
git status
```

**Risultato atteso**: Solo `README.md` dovrebbe essere presente, tutti gli altri file dovrebbero essere ignorati.

### Step 6: Test Aggiunta File

```bash
# Prova ad aggiungere un file ignorato
git add app.log
```

**Risultato atteso**: Git dovrebbe avvertire che il file è ignorato.

### Step 7: Override Forzato

```bash
# Forza l'aggiunta di un file ignorato
git add -f app.log
git status
```

**Risultato atteso**: `app.log` dovrebbe ora essere staged.

```bash
# Rimuovi dal staging
git reset app.log
```

### Step 8: Test Pattern Complessi

Aggiungi questi file:

```bash
# File che dovrebbero essere tracciati
echo "Important config" > config.example.ini
echo "Public environment" > .env.example

# File che dovrebbero essere ignorati
echo "Secret config" > config.production.ini
echo "Local environment" > .env.local
```

Aggiorna `.gitignore`:

```gitignore
# ... contenuto precedente ...

# File di configurazione - pattern specifici
config.*.ini
!config.example.ini

.env.*
!.env.example
```

Verifica:

```bash
git status
```

**Risultato atteso**: 
- ✅ `config.example.ini` e `.env.example` dovrebbero essere tracciabili
- ❌ `config.production.ini` e `.env.local` dovrebbero essere ignorati

## 🧪 Test Avanzati

### Test 1: Directory Nidificate

```bash
# Crea struttura complessa
mkdir -p src/main/java
mkdir -p src/test/resources
mkdir -p target/classes

echo "public class Main {}" > src/main/java/Main.java
echo "test.property=value" > src/test/resources/test.properties
echo "compiled.class" > target/classes/Main.class

# Aggiungi pattern per build Java
echo "target/" >> .gitignore

git status
```

### Test 2: File Già Tracciati

```bash
# Crea e traccia un file
echo "Config iniziale" > database.conf
git add database.conf
git commit -m "Add database config"

# Aggiungi al .gitignore
echo "database.conf" >> .gitignore

# Modifica il file
echo "Config modificato" > database.conf

git status
```

**Nota**: Il file continuerà ad essere tracciato. Per ignorarlo:

```bash
git rm --cached database.conf
git commit -m "Remove database.conf from tracking"
```

### Test 3: Gitignore Globale

```bash
# Crea file gitignore globale
git config --global core.excludesfile ~/.gitignore_global

# Aggiungi pattern comuni
echo ".DS_Store" >> ~/.gitignore_global
echo "Thumbs.db" >> ~/.gitignore_global
echo "*.swp" >> ~/.gitignore_global
```

## ✅ Checklist di Verifica

- [ ] `.gitignore` creato e funzionante
- [ ] File di log ignorati correttamente
- [ ] File temporanei ignorati
- [ ] File sensibili (.env) ignorati
- [ ] Directory di build ignorate
- [ ] Pattern di eccezione (!) funzionanti
- [ ] File già tracciati gestiti correttamente
- [ ] Gitignore globale configurato

## 🐛 Troubleshooting

### Problema: File ancora visibili dopo aggiunta a .gitignore

**Soluzione**:
```bash
# Se il file è già tracciato
git rm --cached filename

# Se vuoi rimuovere una directory
git rm -r --cached directory_name

# Commit la rimozione
git commit -m "Remove tracked files now in .gitignore"
```

### Problema: .gitignore non funziona

**Verifiche**:
1. Il file si chiama esattamente `.gitignore`?
2. È nella root del repository?
3. I pattern sono corretti? (no spazi extra)
4. Il file è committato?

### Problema: Pattern non funziona

**Test del pattern**:
```bash
# Testa se un file matcherebbe
git check-ignore -v filename

# Lista tutti i file ignorati
git ls-files --others --ignored --exclude-standard
```

## 🎯 Challenge Extra

### Challenge 1: Gitignore per Progetto Full-Stack

Crea un `.gitignore` per un progetto che include:
- Frontend React (Node.js)
- Backend Python (Django)
- Database (PostgreSQL dumps)
- Docker containers

### Challenge 2: Gitignore Condizionale

Crea pattern che ignorano:
- File .log solo nella directory `logs/`
- File .env tranne `.env.example`
- Tutti i file .pdf tranne quelli in `docs/`

### Challenge 3: Performance Test

Crea 1000 file e testa la performance di Git con e senza `.gitignore` appropriato.

## 📚 Risorse Aggiuntive

- [Gitignore.io](https://gitignore.io) - Generatore online
- [GitHub Gitignore Templates](https://github.com/github/gitignore)
- [Git Documentation - gitignore](https://git-scm.com/docs/gitignore)

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Guida File Tracking](../guide/02-file-tracking.md)
- [➡️ Esercizio Pattern Avanzati](02-pattern-avanzati.md)
