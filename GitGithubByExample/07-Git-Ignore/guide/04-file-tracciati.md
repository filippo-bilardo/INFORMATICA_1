# Gestione File Già Tracciati

## 🎯 Il Problema dei File Già Tracciati

Uno dei problemi più comuni con `.gitignore` è che **non influisce sui file già tracciati** da Git. Se un file è già nel repository, aggiungere la sua regola in `.gitignore` non lo rimuoverà automaticamente dal tracking.

## 🤔 Perché Succede?

### Meccanismo di Git
```
File nuovo → Controlla .gitignore → Se match: IGNORA
File tracciato → CONTINUA A TRACCIARE (indipendentemente da .gitignore)
```

### Scenario Comune
```bash
# 1. File committato per errore
git add config.json
git commit -m "Added config"

# 2. Aggiunto a .gitignore
echo "config.json" >> .gitignore

# 3. Il file CONTINUA a essere tracciato!
git status  # Mostra ancora config.json se modificato
```

## 🛠️ Soluzioni per File Già Tracciati

### 1. Rimozione dal Tracking (Consigliata)

#### Rimuovi Singolo File
```bash
# Rimuovi dal tracking ma mantieni il file locale
git rm --cached filename.txt

# Aggiungi a .gitignore se non già presente
echo "filename.txt" >> .gitignore

# Committa la rimozione
git commit -m "Stop tracking filename.txt"
```

#### Rimuovi Directory
```bash
# Rimuovi directory dal tracking
git rm -r --cached directory/

# Aggiungi a .gitignore
echo "directory/" >> .gitignore

# Committa
git commit -m "Stop tracking directory/"
```

#### Rimuovi Multipli File con Pattern
```bash
# Rimuovi tutti i file .log
git rm --cached "*.log"

# O usando find per pattern più complessi
find . -name "*.log" -exec git rm --cached {} \;

# Aggiungi a .gitignore
echo "*.log" >> .gitignore

# Committa
git commit -m "Stop tracking log files"
```

### 2. Reset Completo del Tracking

#### Per Repository Piccoli
```bash
# ⚠️ ATTENZIONE: Questo rimuove TUTTO dal tracking
git rm -r --cached .

# Aggiungi tutto di nuovo (rispettando .gitignore)
git add .

# Committa
git commit -m "Apply .gitignore to all files"
```

#### Script Automatizzato
```bash
#!/bin/bash
# reset-gitignore.sh

echo "🔄 Reset del tracking per applicare .gitignore..."

# Backup dello status attuale
git status --porcelain > /tmp/git-status-backup.txt

# Rimuovi tutto dal tracking
git rm -r --cached . 2>/dev/null

# Aggiungi tutto rispettando .gitignore
git add .

# Mostra cosa è cambiato
echo ""
echo "📊 Cambiamenti nel tracking:"
git status --porcelain

echo ""
read -p "Procedi con il commit? (y/N): " confirm
if [[ $confirm == [yY] ]]; then
    git commit -m "Apply .gitignore rules to existing files"
    echo "✅ Tracking aggiornato!"
else
    echo "❌ Operazione annullata"
    git reset HEAD
fi
```

## 🔒 Gestione File Sensibili

### Problema: Credenziali Committate
```bash
# ❌ PROBLEMA: File sensibile già committato
echo "API_KEY=secret123" > .env
git add .env
git commit -m "Added env"  # ERRORE!

# Ora il secret è nella cronologia di Git
```

### Soluzione 1: Rimozione Semplice
```bash
# Rimuovi dal tracking
git rm --cached .env

# Aggiungi a .gitignore
echo ".env" >> .gitignore

# Committa
git commit -m "Remove .env from tracking"

# ⚠️ ATTENZIONE: Il file rimane nella cronologia!
# Chiunque può ancora accedere ai secret nei commit precedenti
```

### Soluzione 2: Rimozione dalla Cronologia
```bash
# ⚠️ RISCRIVE LA CRONOLOGIA - Usa con cautela!

# Metodo 1: git filter-branch (deprecato ma funziona)
git filter-branch --force --index-filter \
    'git rm --cached --ignore-unmatch .env' \
    --prune-empty --tag-name-filter cat -- --all

# Metodo 2: git filter-repo (moderno, richiede installazione)
git filter-repo --path .env --invert-paths

# Pulizia riferimenti
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive
```

### Soluzione 3: Template Sicuri
```bash
# Crea un template al posto del file sensibile
cp .env .env.template

# Pulisci il template
sed 's/=.*/=your-value-here/' .env.template > .env.template.tmp
mv .env.template.tmp .env.template

# Rimuovi l'originale dal tracking
git rm --cached .env
echo ".env" >> .gitignore

# Traccia il template
git add .env.template .gitignore
git commit -m "Replace .env with template"
```

## 📁 Scenari Comuni di Gestione

### 1. Dipendenze Committate per Errore
```bash
# Problema: node_modules è nel repository
ls -la node_modules/  # Directory presente e tracciata

# Soluzione
git rm -r --cached node_modules/
echo "node_modules/" >> .gitignore
git commit -m "Remove node_modules from tracking"

# Il team dovràò eseguire npm install dopo il pull
```

### 2. File di Build Tracciati
```bash
# Problema: build/ directory tracciata
git ls-files | grep "^build/"

# Soluzione con verifica
echo "📁 File di build attualmente tracciati:"
git ls-files | grep "^build/" | head -5

read -p "Rimuovi tutti i file di build dal tracking? (y/N): " confirm
if [[ $confirm == [yY] ]]; then
    git rm -r --cached build/
    echo "build/" >> .gitignore
    echo "dist/" >> .gitignore
    git commit -m "Remove build artifacts from tracking"
fi
```

### 3. File IDE Personali
```bash
# Problema: file .vscode/ condivisi quando non dovrebbero
# Alcuni file di .vscode/ sono utili al team (tasks.json, launch.json)
# Altri sono personali (settings.json, extensions.json)

# Soluzione granulare
git rm --cached .vscode/settings.json
git rm --cached .vscode/extensions.json

# .gitignore specifico
cat >> .gitignore << 'EOF'
# IDE - File personali
.vscode/settings.json
.vscode/extensions.json

# IDE - File condivisi (non ignorati)
# .vscode/tasks.json
# .vscode/launch.json
EOF

git commit -m "Remove personal IDE files from tracking"
```

## 🧪 Script di Pulizia Automatica

### Script di Diagnosi
```bash
#!/bin/bash
# diagnose-tracking.sh

echo "🔍 Diagnosi File Tracciati vs .gitignore"
echo "========================================"

if [ ! -f .gitignore ]; then
    echo "❌ .gitignore non trovato!"
    exit 1
fi

echo ""
echo "📋 File tracciati che dovrebbero essere ignorati:"

# Trova file tracciati che matchano patterns in .gitignore
git ls-files | while read file; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "   ⚠️  $file"
    fi
done

echo ""
echo "💡 Per risolvere, esegui:"
echo "   git rm --cached <filename>"
echo "   git commit -m 'Remove accidentally tracked files'"
```

### Script di Pulizia Interattiva
```bash
#!/bin/bash
# clean-tracked.sh

echo "🧹 Pulizia File Tracciati Erroneamente"
echo "======================================"

# Array per raccogliere file da rimuovere
files_to_remove=()

# Trova file problematici
while IFS= read -r file; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "❓ Rimuovere dal tracking: $file"
        read -p "   (y/N): " confirm
        if [[ $confirm == [yY] ]]; then
            files_to_remove+=("$file")
        fi
    fi
done < <(git ls-files)

# Rimuovi i file selezionati
if [ ${#files_to_remove[@]} -gt 0 ]; then
    echo ""
    echo "🗑️  Rimozione dal tracking:"
    for file in "${files_to_remove[@]}"; do
        echo "   - $file"
        git rm --cached "$file"
    done
    
    echo ""
    read -p "Committa le modifiche? (y/N): " commit_confirm
    if [[ $commit_confirm == [yY] ]]; then
        git commit -m "Remove accidentally tracked files

Files removed from tracking:
$(printf '- %s\n' "${files_to_remove[@]}")

These files are now properly ignored by .gitignore"
        echo "✅ Pulizia completata!"
    fi
else
    echo "✅ Nessun file da rimuovere trovato!"
fi
```

## ⚠️ Cautele e Best Practices

### 1. Comunicazione con il Team
```bash
# Prima di rimuovere file tracciati, informa il team
cat > MIGRATION.md << 'EOF'
# 🚨 Importante: Cambiamenti al Tracking dei File

## Cosa è cambiato
- Rimossi file sensibili dal tracking
- Applicato .gitignore ai file esistenti

## Azioni richieste dopo il pull
1. Crea il tuo file .env da .env.template
2. Esegui npm install per ripristinare node_modules
3. Rigenera la directory build/ con npm run build

## File che non sono più tracciati
- .env (credenziali)
- node_modules/ (dipendenze)
- build/ (artifacts)
EOF
```

### 2. Backup Prima delle Modifiche
```bash
# Backup automatico prima della pulizia
#!/bin/bash

echo "💾 Creazione backup prima della pulizia..."

# Crea directory di backup
mkdir -p .git-cleanup-backup/$(date +%Y%m%d_%H%M%S)
backup_dir=".git-cleanup-backup/$(date +%Y%m%d_%H%M%S)"

# Backup dei file che saranno rimossi dal tracking
git ls-files | while read file; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        cp "$file" "$backup_dir/" 2>/dev/null || true
    fi
done

echo "✅ Backup creato in $backup_dir"
```

### 3. Verifica Post-Pulizia
```bash
#!/bin/bash
# verify-cleanup.sh

echo "🔍 Verifica Post-Pulizia"
echo "======================="

echo ""
echo "📊 File attualmente tracciati:"
echo "   Totale: $(git ls-files | wc -l)"

echo ""
echo "🚫 File ignorati ma ancora tracciati:"
ignored_count=0
git ls-files | while read file; do
    if git check-ignore "$file" > /dev/null 2>&1; then
        echo "   ❌ $file"
        ((ignored_count++))
    fi
done

if [ $ignored_count -eq 0 ]; then
    echo "   ✅ Nessuno (tutto ok!)"
fi

echo ""
echo "📈 Dimensione repository:"
echo "   .git/: $(du -sh .git/ | cut -f1)"
echo "   Working tree: $(du -sh --exclude=.git . | cut -f1)"
```

## 🎯 Quiz di Verifica

1. **Cosa succede quando aggiungi un file già tracciato a .gitignore?**
   - a) Il file viene automaticamente ignorato
   - b) Il file continua a essere tracciato
   - c) Git rimuove il file dal repository

2. **Quale comando rimuove un file dal tracking ma lo mantiene localmente?**
   - a) `git rm filename`
   - b) `git rm --cached filename`
   - c) `git ignore filename`

3. **Quando è sicuro riscrivere la cronologia per rimuovere file sensibili?**
   - a) Sempre
   - b) Solo su repository privati non condivisi
   - c) Mai

**Risposte:** 1-b, 2-b, 3-b

## 🔗 Prossimi Passi

- [← Gitignore Globale e Locale](./03-globale-locale.md)
- [Template per Progetti Comuni →](./05-template-progetti.md)
- [Esempi Pratici →](../esempi/01-setup-nodejs.md)

---

> ⚠️ **Attenzione**: Rimuovere file dalla cronologia è un'operazione potenzialmente pericolosa. Fallo solo quando necessario e coordina sempre con il team!
