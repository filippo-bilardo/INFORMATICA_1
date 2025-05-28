# Eliminazione File e Directory

## Concetti Fondamentali

### Tipi di Eliminazione in Git
1. **Eliminazione dal Working Directory**: Rimuove il file dal filesystem
2. **Eliminazione dal Staging Area**: Rimuove dal prossimo commit
3. **Eliminazione dalla Storia**: Rimuove completamente dalla cronologia (avanzato)

### Differenza tra `rm` e `git rm`
- **`rm`**: Elimina solo dal filesystem, Git vede il file come "deleted"
- **`git rm`**: Elimina dal filesystem E dal tracciamento Git
- **`git rm --cached`**: Rimuove solo dal tracciamento, mantiene il file locale

## Comandi Principali

### `git rm` - Eliminazione Controllata

```bash
# Eliminare file dal repository e filesystem
git rm file.txt

# Eliminare solo dal tracciamento (mantiene file locale)
git rm --cached file.txt

# Eliminare directory ricorsivamente
git rm -r directory/

# Forzare eliminazione di file modificati
git rm -f file.txt

# Eliminare file con pattern
git rm '*.log'
git rm 'temp/*'
```

### Eliminazione Manuale + Git

```bash
# Metodo manuale
rm file.txt
git add file.txt  # Aggiunge la cancellazione al staging

# O più esplicitamente
rm file.txt
git rm file.txt
```

### Annullare Eliminazioni

```bash
# Prima del commit - recuperare file eliminato
git checkout HEAD file.txt

# Dopo il commit - recuperare da commit precedente
git checkout HEAD~1 file.txt

# Recuperare tutti i file eliminati
git checkout HEAD .
```

## Gestione Avanzata

### Eliminazione Condizionale
```bash
# Eliminare solo se non modificato
git rm file.txt

# Eliminare anche se modificato
git rm -f file.txt

# Eliminare solo se presente nel staging
git rm --cached file.txt
```

### Backup Prima dell'Eliminazione
```bash
# Creare backup prima di eliminare
cp important.txt important.txt.backup
git rm important.txt

# O spostare in directory di backup
mkdir backup
git mv important.txt backup/
```

### Eliminazione Selettiva con Pattern
```bash
# Eliminare tutti i file di log
git rm '*.log'

# Eliminare file temporanei
git rm '*~' '*.tmp' '*.swp'

# Eliminare in directory specifica
git rm 'temp/*.cache'

# Eliminare ricorsivamente con pattern
git rm -r --cached 'node_modules/'
```

## Casi d'Uso Pratici

### 1. Pulizia Repository
```bash
# Rimuovere file di build e cache
git rm -r build/
git rm -r node_modules/
git rm '*.o' '*.exe'

# Aggiungere al .gitignore
echo "build/" >> .gitignore
echo "node_modules/" >> .gitignore
echo "*.o" >> .gitignore

git add .gitignore
git commit -m "Clean up build artifacts and add to gitignore"
```

### 2. Rimozione File Sensibili
```bash
# Rimuovere file con password/API keys
git rm --cached config/database.yml
git rm --cached .env

# Aggiungere al .gitignore
echo "config/database.yml" >> .gitignore
echo ".env" >> .gitignore

# IMPORTANTE: Per rimuovere dalla storia
git filter-branch --force --index-filter \
'git rm --cached --ignore-unmatch config/database.yml' \
--prune-empty --tag-name-filter cat -- --all
```

### 3. Refactoring: Eliminazione File Obsoleti
```bash
# Eliminare vecchi file dopo migrazione
git rm legacy/old-system.js
git rm deprecated/*.php
git rm -r old-components/

git commit -m "Remove legacy and deprecated files after migration"
```

### 4. Eliminazione Temporanea per Test
```bash
# Eliminare temporaneamente per test
git rm test-file.txt
# ... eseguire test ...

# Recuperare se necessario
git checkout HEAD test-file.txt
```

## Recupero File Eliminati

### Recupero Immediato (Prima del Commit)
```bash
# File eliminato con git rm
git rm important.txt
git status  # Mostra "deleted: important.txt"

# Recuperare dal staging
git reset HEAD important.txt
git checkout important.txt
```

### Recupero da Commit Precedenti
```bash
# Vedere quando è stato eliminato
git log --diff-filter=D --summary

# Recuperare file specifico
git checkout <commit-hash>~1 file.txt

# Recuperare da ultimo commit che conteneva il file
git checkout $(git rev-list -n 1 HEAD -- file.txt)~1 -- file.txt
```

### Recupero con git reflog
```bash
# Vedere storia delle operazioni
git reflog

# Recuperare da stato precedente
git checkout HEAD@{5} -- file.txt
```

## Eliminazione dalla Storia (Avanzato)

### Rimuovere File da Tutta la Storia
```bash
# ATTENZIONE: Modifica la storia, da usare con cautela
git filter-branch --force --index-filter \
'git rm --cached --ignore-unmatch path/to/file' \
--prune-empty --tag-name-filter cat -- --all

# Pulire riferimenti
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive
```

### Usando BFG Repo-Cleaner (Raccomandato)
```bash
# Installare BFG
# brew install bfg  # macOS
# apt install bfg   # Ubuntu

# Rimuovere file specifico
bfg --delete-files sensitive.txt repo.git

# Rimuovere file per dimensione
bfg --strip-blobs-bigger-than 50M repo.git

# Pulire
cd repo.git
git reflog expire --expire=now --all && git gc --prune=now --aggressive
```

## Errori Comuni e Soluzioni

### ❌ Problema: File eliminato per errore
```bash
# File eliminato accidentalmente
git rm important.txt
```

**✅ Soluzione:**
```bash
# Prima del commit
git reset HEAD important.txt
git checkout important.txt

# Dopo il commit
git checkout HEAD~1 important.txt
```

### ❌ Problema: Directory non si elimina
```bash
git rm directory/  # Errore: directory non vuota
```

**✅ Soluzione:**
```bash
# Usare flag ricorsivo
git rm -r directory/

# O eliminare contenuto prima
git rm directory/*
git rm directory/
```

### ❌ Problema: File modificato non si elimina
```bash
git rm modified-file.txt  # Errore: file modificato
```

**✅ Soluzione:**
```bash
# Forzare eliminazione
git rm -f modified-file.txt

# O committare prima le modifiche
git add modified-file.txt
git commit -m "Save changes before deletion"
git rm modified-file.txt
```

### ❌ Problema: Eliminazione influisce su altri
```bash
# File condiviso eliminato da un membro del team
git pull  # Conflitti per file eliminati
```

**✅ Soluzione:**
```bash
# Accettare eliminazione
git rm file.txt

# O recuperare il file
git checkout HEAD file.txt

# Risolvere conflitti
git add .
git commit -m "Resolve deletion conflicts"
```

## Best Practices

### ✅ Consigli per Eliminazioni Sicure

1. **Backup prima di eliminazioni massive**
   ```bash
   # Creare branch di backup
   git checkout -b backup-before-cleanup
   git checkout main
   
   # Procedere con eliminazioni
   ```

2. **Usare --cached per file sensibili**
   ```bash
   # Non eliminare dal filesystem
   git rm --cached sensitive.txt
   echo "sensitive.txt" >> .gitignore
   ```

3. **Verificare prima del commit**
   ```bash
   git status
   git diff --cached  # Verificare cosa verrà committato
   git commit -m "Remove obsolete files"
   ```

4. **Documentare eliminazioni importanti**
   ```bash
   git commit -m "Remove legacy authentication system
   
   - Deleted old auth/ directory
   - Removed deprecated login.php
   - Migration complete to new OAuth system"
   ```

### ✅ Checklist per Eliminazioni

- [ ] File è realmente obsoleto?
- [ ] Nessun altro codice dipende da questo file?
- [ ] Backup creato se necessario?
- [ ] File aggiunto al .gitignore se deve rimanere locale?
- [ ] Team informato su eliminazioni importanti?

## Strumenti di Supporto

### Script per Pulizia Automatica
```bash
#!/bin/bash
# cleanup.sh - Script per pulizia repository

echo "Removing build artifacts..."
git rm -r --cached build/ 2>/dev/null || true
git rm --cached '*.o' '*.exe' '*.tmp' 2>/dev/null || true

echo "Removing IDE files..."
git rm --cached '.vscode/' '.idea/' '*.swp' 2>/dev/null || true

echo "Updating .gitignore..."
cat >> .gitignore << EOL
# Build artifacts
build/
*.o
*.exe
*.tmp

# IDE files
.vscode/
.idea/
*.swp
EOL

git add .gitignore
git commit -m "Automated cleanup: remove artifacts and update gitignore"
```

### Alias Git Utili
```bash
# Configurare alias per operazioni comuni
git config --global alias.cleanup "!git rm -r --cached . && git add ."
git config --global alias.undelete "checkout HEAD --"
git config --global alias.purge "rm -rf"
```

## Quiz di Autovalutazione

### Domanda 1
Quale comando elimina un file solo dal tracciamento Git?
- a) `git rm file.txt`
- b) `git rm --cached file.txt` ✅
- c) `git delete file.txt`
- d) `rm file.txt`

### Domanda 2
Come eliminare una directory ricorsivamente?
- a) `git rm directory/`
- b) `git rm -r directory/` ✅
- c) `git delete -r directory/`
- d) `git rmdir directory/`

### Domanda 3
Come recuperare un file eliminato prima del commit?
- a) `git restore file.txt`
- b) `git checkout HEAD file.txt` ✅
- c) `git undo file.txt`
- d) `git recover file.txt`

### Domanda 4
Quale flag forza l'eliminazione di file modificati?
- a) `git rm --force file.txt`
- b) `git rm -f file.txt` ✅
- c) `git rm --ignore file.txt`
- d) Entrambe a e b ✅

### Domanda 5
Come vedere quando un file è stato eliminato?
- a) `git log file.txt`
- b) `git log --diff-filter=D --summary` ✅
- c) `git history --deleted`
- d) `git show --deleted`

## Esercizi Pratici

### Esercizio 1: Eliminazione Base
1. Crea alcuni file di test
2. Elimina uno con `git rm`
3. Elimina uno con `rm` e poi gestisci in Git
4. Recupera un file eliminato

### Esercizio 2: Pulizia Repository
1. Crea file di diversi tipi (temporanei, build, ecc.)
2. Elimina tutti i file temporanei con pattern
3. Aggiorna .gitignore
4. Verifica che la pulizia sia completa

### Esercizio 3: Gestione Errori
1. Elimina accidentalmente un file importante
2. Recuperalo usando diversi metodi
3. Prova a eliminare file modificati
4. Gestisci i conflitti appropriatamente

## Navigazione del Corso
- [📑 Indice](../../README.md)
- [⬅️ Rinominare e Spostare File](./02-rinominare-spostare.md)
- [➡️ Gestione Directory Vuote](./04-directory-vuote.md)
