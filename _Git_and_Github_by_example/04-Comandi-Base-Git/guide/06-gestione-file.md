# 06 - Gestione File (rm, mv)

## 📖 Spiegazione Concettuale

La gestione dei file in Git richiede comandi specifici per **mantenere la cronologia** e **sincronizzare** le operazioni tra file system e repository. Utilizzare `git rm` e `git mv` invece dei comandi di sistema assicura che Git tracci correttamente le modifiche.

### Perché Usare Git per Gestire File?

Quando usi comandi di sistema (`rm`, `mv`) senza Git:
- Git non sa che hai rinominato/spostato un file
- Perde la cronologia del file
- Devi fare operazioni manuali aggiuntive

Quando usi comandi Git:
- Mantiene la cronologia completa
- Operazioni atomiche (staging automatico)
- Tracciamento intelligente delle modifiche

## 🔧 Git Remove (git rm)

### Sintassi Base
```bash
git rm <file>
```

### Varianti Principali

#### 1. Rimozione Standard
```bash
# Rimuove file da working directory E staging
git rm file.txt

# Equivale a:
rm file.txt
git add file.txt  # (per file già tracciati)
```

#### 2. Rimozione Solo dal Repository
```bash
# Mantiene file localmente ma rimuove dal tracking
git rm --cached file.txt

# Utile per file che non dovevano essere tracciati
git rm --cached secrets.env
echo "secrets.env" >> .gitignore
```

#### 3. Rimozione Forzata
```bash
# Forza rimozione anche se file modificato
git rm -f modified-file.txt

# Rimozione ricorsiva directory
git rm -r old-directory/

# Combinazione comune
git rm -rf temp-folder/
```

## 🔧 Git Move/Rename (git mv)

### Sintassi Base
```bash
git mv <source> <destination>
```

### Operazioni Principali

#### 1. Rinominare File
```bash
# Rinomina file
git mv old-name.js new-name.js

# Equivale a:
mv old-name.js new-name.js
git rm old-name.js
git add new-name.js
```

#### 2. Spostare File
```bash
# Sposta in directory
git mv file.js src/

# Sposta e rinomina
git mv old-file.js src/new-file.js

# Spostare directory
git mv old-folder/ new-folder/
```

#### 3. Operazioni Batch
```bash
# Spostare multipli file
git mv *.js src/
git mv file1.txt file2.txt docs/

# Riorganizzazione struttura
git mv src/components/*.js components/
git mv src/utils/*.js utils/
```

## 🎯 Esempi Pratici

### Scenario 1: Pulizia Repository
```bash
# Situazione: file temporanei tracciati per errore
$ git status
On branch main
Changes to be committed:
  new file:   debug.log
  new file:   temp-data.json
  new file:   .DS_Store

# Rimuovi dal tracking ma mantieni localmente
git rm --cached debug.log temp-data.json .DS_Store

# Aggiungi al .gitignore per il futuro
echo -e "debug.log\ntemp-data.json\n.DS_Store" >> .gitignore
git add .gitignore

$ git status
On branch main
Changes to be committed:
  new file:   .gitignore
  deleted:    debug.log
  deleted:    temp-data.json
  deleted:    .DS_Store

Untracked files:
  debug.log
  temp-data.json
  .DS_Store
```

### Scenario 2: Riorganizzazione Struttura
```bash
# Situazione: riorganizzare struttura progetto
current structure:
├── app.js
├── utils.js
├── api.js
└── styles.css

target structure:
├── src/
│   ├── app.js
│   ├── utils.js
│   └── api.js
└── assets/
    └── styles.css

# Operazioni Git
mkdir src assets
git mv app.js utils.js api.js src/
git mv styles.css assets/

$ git status
On branch main
Changes to be committed:
  renamed:    app.js -> src/app.js
  renamed:    utils.js -> src/utils.js
  renamed:    api.js -> src/api.js
  renamed:    styles.css -> assets/styles.css
```

### Scenario 3: Rinominare per Convenzioni
```bash
# Rinominare file per seguire convenzioni
git mv HomePage.js home-page.js
git mv UserProfile.js user-profile.js
git mv APIHelper.js api-helper.js

# Git mantiene la cronologia
$ git log --follow --oneline src/home-page.js
a1b2c3d (HEAD) refactor: rename files to kebab-case
b2c3d4e feat: add responsive design to homepage
c3d4e5f fix: resolve homepage loading issue
d4e5f6g feat: create HomePage component
```

## 🎨 Pattern di Rimozione Avanzati

### 1. Rimozione Condizionale
```bash
# Rimuovi tutti i file .log
git rm *.log

# Rimuovi file di backup
git rm *~
git rm *.bak

# Rimuovi file compilati
git rm *.o *.class *.pyc
```

### 2. Rimozione con Filtri
```bash
# Rimuovi file più vecchi di X giorni (con find)
find . -name "*.tmp" -mtime +7 -exec git rm {} \;

# Rimuovi file grandi accidentalmente committatі
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch large-file.zip' \
  --prune-empty --tag-name-filter cat -- --all
```

### 3. Rimozione Sicura
```bash
# Controlla cosa rimuoveresti (dry run con find)
find . -name "*.tmp" -print

# Backup prima di rimozioni massive
tar -czf backup-$(date +%Y%m%d).tar.gz .

# Rimozione graduale per evitare errori
git rm temp1.txt
git status  # Verifica
git rm temp2.txt
git status  # Verifica
```

## 💡 Best Practices

### 1. Verifiche Pre-Rimozione
```bash
# Sempre controllare cosa stai rimuovendo
git status
git ls-files | grep pattern  # Cosa matcherebbe il pattern?

# Per rimozioni massive, usa --dry-run se disponibile
find . -name "*.tmp" -print  # Simula rimozione
```

### 2. Backup Strategici
```bash
# Prima di operazioni di massa
git stash push -m "backup before cleanup"

# O crea branch temporaneo
git checkout -b backup-before-cleanup
git checkout main
# Fai le operazioni...
# Se tutto ok: git branch -D backup-before-cleanup
```

### 3. Rimozione con .gitignore
```bash
# Workflow corretto per file da ignorare
# 1. Rimuovi dal tracking
git rm --cached unwanted-file.txt

# 2. Aggiungi al .gitignore
echo "unwanted-file.txt" >> .gitignore

# 3. Commit entrambe le modifiche
git add .gitignore
git commit -m "chore: remove unwanted-file.txt from tracking"
```

## 🚨 Problemi Comuni e Soluzioni

### 1. File Modificato Non si Rimuove
```bash
# Problema: file modificato
$ git rm modified-file.js
error: the following file has local modifications:
    modified-file.js

# Soluzioni:
# A) Commit le modifiche prima
git add modified-file.js
git commit -m "save changes before removal"
git rm modified-file.js

# B) Forza rimozione (perdi modifiche!)
git rm -f modified-file.js

# C) Rimuovi solo dal tracking
git rm --cached modified-file.js
```

### 2. Git Non Rileva Rinomine
```bash
# Problema: usato mv sistema invece di git mv
mv old.js new.js

$ git status
deleted:    old.js
untracked:  new.js

# Soluzioni:
# A) Annulla e rifai con git mv
git checkout old.js  # Ripristina
rm new.js           # Rimuovi copia
git mv old.js new.js

# B) Aiuta Git a rilevare la rinomina
git add new.js
git rm old.js
# Git potrebbe rilevare automaticamente come rename
```

### 3. Rimozione Directory Non Vuota
```bash
# Problema: directory con file non tracciati
$ git rm -r project-folder/
error: the following files have local modifications:
    project-folder/config.local

# Soluzione: rimuovi file non tracciati prima
rm project-folder/config.local  # O sposta se importante
git rm -r project-folder/
```

## 🎯 Casi d'Uso Specializzati

### 1. Migrazione Struttura Progetto
```bash
#!/bin/bash
# Script per migrazione struttura

# Backup
git checkout -b backup-structure

# Torna al main
git checkout main

# Crea nuove directory
mkdir -p src/{components,utils,services}
mkdir -p assets/{images,styles}

# Sposta file preservando cronologia
git mv *.js src/
git mv components/*.js src/components/
git mv utils/*.js src/utils/
git mv *.css assets/styles/
git mv images/* assets/images/

# Commit migrazione
git commit -m "refactor: reorganize project structure"
```

### 2. Pulizia Automatica Repository
```bash
#!/bin/bash
# cleanup-repo.sh

echo "Cleaning repository..."

# Rimuovi file temporanei comuni
git rm --cached --ignore-unmatch *.log *.tmp *~

# Rimuovi file di build se presenti
git rm --cached --ignore-unmatch dist/ build/ node_modules/

# Aggiorna .gitignore
cat >> .gitignore << EOF
# Temporary files
*.log
*.tmp
*~

# Build directories
dist/
build/
node_modules/
EOF

git add .gitignore
git commit -m "chore: cleanup repository and update .gitignore"
```

### 3. Rinomina Batch con Cronologia
```bash
# Rinomina multipli file mantenendo cronologia
for file in *.jsx; do
    newname="${file%.jsx}.js"
    git mv "$file" "$newname"
done

git commit -m "refactor: convert .jsx files to .js extension"
```

## 🎓 Quiz di Verifica

1. **Qual è la differenza tra `rm file.txt` e `git rm file.txt`?**
2. **Come rimuovi un file dal tracking Git ma lo mantieni localmente?**
3. **Perché usare `git mv` invece di `mv` + `git add`?**

### Risposte
1. `rm` rimuove solo dal filesystem, `git rm` rimuove e aggiorna l'indice Git
2. `git rm --cached file.txt`
3. `git mv` è atomico e Git riconosce meglio le rinomine mantenendo la cronologia

## 🔗 Comandi Correlati

- `git status` - Vedere stato file
- `git add` - Staging modifiche
- `git commit` - Confermare rimozioni/spostamenti
- `git log --follow` - Seguire cronologia file rinominati
- `find` - Trovare file per operazioni batch

## 📚 Risorse Aggiuntive

- [Git Remove Documentation](https://git-scm.com/docs/git-rm)
- [Git Move Documentation](https://git-scm.com/docs/git-mv)
- [File Management Best Practices](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)

---

**Completato**: Hai completato le guide teoriche dei comandi base Git! 

**Prossimo**: [Esempi Pratici](../esempi/) - Metti in pratica quello che hai imparato
