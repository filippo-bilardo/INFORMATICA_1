# Git Restore - Il Comando Moderno per Ripristini

## 📖 Introduzione

`git restore` è stato introdotto in Git 2.23 (agosto 2019) per semplificare e chiarire le operazioni di ripristino. Sostituisce molti usi di `git checkout` e `git reset`, fornendo un'interfaccia più intuitiva e sicura.

## 🎯 Obiettivi

- Padroneggiare la sintassi moderna di `git restore`
- Comprendere le diverse modalità di ripristino
- Sostituire vecchi pattern con approcci moderni
- Applicare restore in scenari reali

## 📊 Evoluzione da Checkout a Restore

### Prima di Git 2.23 (Confuso)
```bash
# Confusione: checkout faceva troppe cose diverse
git checkout -- file.txt        # Ripristina file
git checkout branch-name         # Cambia branch
git checkout -b new-branch       # Crea branch
git reset HEAD file.txt          # Rimuove da staging
```

### Da Git 2.23+ (Chiaro)
```bash
# Comandi specializzati e chiari
git restore file.txt             # Ripristina file
git switch branch-name           # Cambia branch
git switch -c new-branch         # Crea branch
git restore --staged file.txt    # Rimuove da staging
```

## 🛠️ Sintassi Completa di Git Restore

### Forma Base
```bash
git restore [<options>] [--] <pathspec>...
```

### Opzioni Principali

#### 🔍 `--source=<tree>`
Specifica da dove ripristinare:
```bash
# Ripristina da HEAD (default)
git restore file.txt

# Ripristina da commit specifico
git restore --source=HEAD~2 file.txt

# Ripristina da altro branch
git restore --source=main config.json

# Ripristina da tag
git restore --source=v1.0.0 package.json
```

#### 🔄 `--staged` vs `--worktree`
Controlla dove applicare il ripristino:
```bash
# Solo working directory (default)
git restore file.txt

# Solo staging area
git restore --staged file.txt

# Entrambi
git restore --staged --worktree file.txt
```

#### 📁 `--pathspec-from-file`
Ripristina file elencati in un file:
```bash
# Lista file in restore-list.txt
echo "src/config.js" > restore-list.txt
echo "src/utils.js" >> restore-list.txt

git restore --pathspec-from-file=restore-list.txt
```

## 📝 Scenari Pratici Dettagliati

### Scenario 1: File Modificato per Errore
```bash
# Situazione iniziale
echo "contenuto errato" > important-file.txt
git status
# modified: important-file.txt

# Ripristino
git restore important-file.txt

# Verifica
git status
# nothing to commit, working tree clean

# ⚠️ Attenzione: Le modifiche sono perse definitivamente!
```

### Scenario 2: Rimozione Accidentale dall'Area di Staging
```bash
# Situazione: file aggiunto per errore
git add sensitive-data.txt
git status
# Changes to be committed:
#   new file: sensitive-data.txt

# Rimozione da staging (file rimane in working dir)
git restore --staged sensitive-data.txt

# Verifica
git status
# Untracked files:
#   sensitive-data.txt
```

### Scenario 3: Ripristino Parziale da Versione Precedente
```bash
# Voglio solo la funzione getUser() dal commit precedente
git log --oneline
# abc123 Fix authentication
# def456 Add user management
# ghi789 Initial commit

# Ripristino solo file specifico da commit precedente
git restore --source=def456 src/user-manager.js

# Verifica cosa è cambiato
git diff
```

### Scenario 4: Ripristino Interattivo
```bash
# Ripristino parziale di un file (patch mode)
git restore --patch file.txt

# Git ti mostrerà ogni chunk e chiederà:
# Apply this hunk to index and worktree [y,n,q,a,d,/,s,e,?]?
```

## 🔧 Pattern Avanzati

### Pattern 1: Ripristino Condizionale
```bash
#!/bin/bash
# Script per ripristino sicuro con conferma

file="$1"
if [[ -z "$file" ]]; then
    echo "Uso: restore-safe.sh <filename>"
    exit 1
fi

echo "Ripristinare $file? Questo annullerà tutte le modifiche non committate."
read -p "Continuare? (y/N): " confirm

if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
    git restore "$file"
    echo "✅ $file ripristinato"
else
    echo "❌ Operazione annullata"
fi
```

### Pattern 2: Backup Prima del Ripristino
```bash
# Funzione per backup automatico
safe_restore() {
    local file="$1"
    local backup_dir=".git/backups/$(date +%Y%m%d-%H%M%S)"
    
    # Crea directory backup
    mkdir -p "$backup_dir"
    
    # Copia file se modificato
    if git diff --quiet "$file"; then
        echo "File $file non modificato, no backup necessario"
    else
        cp "$file" "$backup_dir/"
        echo "📁 Backup salvato in $backup_dir/$file"
    fi
    
    # Ripristina
    git restore "$file"
    echo "✅ $file ripristinato"
}

# Uso
safe_restore config.json
```

### Pattern 3: Ripristino Multi-File con Filtri
```bash
# Ripristina tutti i file .js modificati
git restore '*.js'

# Ripristina tutti i file in una directory
git restore src/

# Ripristina tutti i file tranne uno
git restore . ':(exclude)keep-this-file.txt'

# Ripristina solo file tracked modificati
git diff --name-only | xargs git restore
```

## 📊 Confronto con Metodi Precedenti

### Ripristino File Working Directory

| Vecchio Metodo | Nuovo Metodo | Note |
|---------------|--------------|------|
| `git checkout -- file.txt` | `git restore file.txt` | Più chiaro |
| `git checkout HEAD -- file.txt` | `git restore --source=HEAD file.txt` | Esplicito |
| `git checkout .` | `git restore .` | Consistente |

### Rimozione da Staging

| Vecchio Metodo | Nuovo Metodo | Note |
|---------------|--------------|------|
| `git reset HEAD file.txt` | `git restore --staged file.txt` | Intuitivo |
| `git reset file.txt` | `git restore --staged file.txt` | Meno confuso |

## ⚙️ Configurazione e Personalizzazione

### Alias Utili
```bash
# Alias per operazioni comuni
git config --global alias.unstage 'restore --staged'
git config --global alias.discard 'restore'
git config --global alias.restore-all 'restore .'

# Uso degli alias
git unstage file.txt      # invece di git restore --staged file.txt
git discard file.txt      # invece di git restore file.txt
git restore-all           # invece di git restore .
```

### Script Personalizzato
```bash
# ~/.local/bin/git-safe-restore
#!/bin/bash

show_help() {
    echo "Git Safe Restore - Ripristino con backup automatico"
    echo ""
    echo "Uso: git safe-restore [opzioni] <file>"
    echo ""
    echo "Opzioni:"
    echo "  -s, --staged     Rimuovi da staging"
    echo "  -f, --force      Non creare backup"
    echo "  -h, --help       Mostra questo aiuto"
}

# Rendi eseguibile: chmod +x ~/.local/bin/git-safe-restore
# Uso: git safe-restore file.txt
```

## 🔍 Debug e Troubleshooting

### Verifica Prima del Ripristino
```bash
# Vedi cosa verrà ripristinato
git diff file.txt

# Vedi contenuto originale
git show HEAD:file.txt

# Confronta versioni
git diff HEAD~1 file.txt
```

### Recupero dopo Ripristino Accidentale
```bash
# Se hai fatto restore per errore, potresti recuperare da:

# 1. Editor con autosave
ls ~/.vscode/User/History/  # VS Code
ls ~/.emacs.d/auto-save-list/  # Emacs

# 2. Git stash (se avevi fatto stash)
git stash list
git stash apply

# 3. Backup locali
find . -name "*.bak" -o -name "*~"

# 4. Reflog per commit precedenti
git reflog
git show <hash>
```

## 🎓 Esercizi Pratici

### Esercizio 1: Ripristino Base
```bash
# Setup
echo "originale" > test.txt
git add test.txt
git commit -m "Contenuto originale"

# Modifica
echo "modificato" > test.txt

# Compito: Ripristina usando git restore
# Verifica che il contenuto torni "originale"
```

### Esercizio 2: Gestione Staging
```bash
# Setup
echo "file1" > file1.txt
echo "file2" > file2.txt
git add file1.txt file2.txt

# Compito: Rimuovi solo file2.txt dal staging
# Verifica con git status
```

### Esercizio 3: Ripristino Selettivo
```bash
# Setup con multiple versioni
echo -e "linea1\nlinea2\nlinea3" > multi.txt
git add multi.txt
git commit -m "Versione base"

echo -e "linea1\nMODIFICATA\nlinea3" > multi.txt

# Compito: Usa git restore --patch per ripristinare solo linea2
```

## 🚨 Avvertenze e Limitazioni

### Cosa NON Può Fare Git Restore
```bash
# ❌ Non può ripristinare commit cancellati
git restore --source=<hash-inesistente> file.txt

# ❌ Non può recuperare file mai tracciati
git restore never-tracked-file.txt

# ❌ Non può modificare cronologia commit
# (per quello serve git reset o git revert)
```

### Attenzioni Importanti
- `git restore` **cancella** modifiche non committate
- Non c'è conferma di default - sii sicuro!
- File non tracciati non sono toccati
- Le modifiche perse sono molto difficili da recuperare

## 🎯 Quando Usare Git Restore

### ✅ Usa Git Restore Quando:
- Vuoi scartare modifiche locali
- Devi rimuovere file dall'area di staging
- Hai bisogno di una versione precedente di un file
- Vuoi ripristini parziali (patch mode)

### ❌ NON Usare Git Restore Quando:
- Il file non è mai stato tracciato da Git
- Vuoi modificare commit già fatti
- Hai bisogno di preservare cronologia
- Stai lavorando con repository remoti

## 🔄 Integrazione con Workflow

### Pre-Commit Hook
```bash
#!/bin/sh
# .git/hooks/pre-commit

# Controlla se ci sono file da ripristinare accidentalmente
unstaged=$(git diff --name-only)
if [ ! -z "$unstaged" ]; then
    echo "⚠️  Ci sono modifiche non staged:"
    echo "$unstaged"
    echo ""
    echo "Vuoi continuare? (y/N)"
    read response
    if [ "$response" != "y" ]; then
        exit 1
    fi
fi
```

### IDE Integration
```json
// VS Code settings.json
{
    "git.enableCommitSigning": true,
    "git.confirmSync": false,
    "git.autofetch": true,
    "git.decorations.enabled": true
}
```

## 📚 Risorse e Approfondimenti

### Documentazione Ufficiale
- [Git Restore Documentation](https://git-scm.com/docs/git-restore)
- [Git 2.23 Release Notes](https://github.com/git/git/blob/master/Documentation/RelNotes/2.23.0.txt)

### Tutorial Avanzati
- [Atlassian - Git Restore](https://www.atlassian.com/git/tutorials/undoing-changes)
- [GitHub - Restoring files](https://docs.github.com/en/repositories/working-with-files/managing-files/restoring-a-deleted-file)

## 🔄 Prossimi Passi

Ora che padroneggi `git restore`, prosegui con:
- [03 - Git Reset Spiegato](./03-git-reset.md)
- [04 - Git Revert vs Reset](./04-revert-vs-reset.md)
- [05 - Modificare Commit (Amend)](./05-modificare-commit.md)

---

**Pro Tip**: `git restore` è il tuo strumento principale per gestire modifiche non committate. Usalo con confidenza, ma sempre con consapevolezza che le modifiche perse sono difficili da recuperare!
