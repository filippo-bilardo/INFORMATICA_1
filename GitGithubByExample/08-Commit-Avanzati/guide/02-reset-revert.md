# Reset e Revert: Annullare e Correggere Commit

## Introduzione
Git offre diversi meccanismi per annullare o correggere commit: `git reset` e `git revert`. Ognuno ha scopi diversi e livelli di sicurezza differenti.

## Git Reset: Tornare Indietro nel Tempo

### Tipi di Reset

#### 1. Soft Reset
```bash
# Mantiene modifiche nello staging area
git reset --soft HEAD~1
```
- **Uso**: Decomorre l'ultimo commit mantenendo le modifiche
- **Sicurezza**: Alta (le modifiche sono preservate)

#### 2. Mixed Reset (Default)
```bash
# Mantiene modifiche nella working directory
git reset HEAD~1
# Equivale a:
git reset --mixed HEAD~1
```
- **Uso**: Annullare commit e staging, mantenere modifiche
- **Sicurezza**: Media (modifiche preservate ma non staged)

#### 3. Hard Reset
```bash
# ⚠️ ATTENZIONE: Cancella tutto
git reset --hard HEAD~1
```
- **Uso**: Cancellare completamente commit e modifiche
- **Sicurezza**: Bassa (perdita di dati possibile)

### Sintassi Avanzata Reset

#### Reset a Commit Specifico
```bash
# Usare hash del commit
git reset --soft a1b2c3d

# Usare reference relativo
git reset --mixed HEAD~3

# Usare branch o tag
git reset --hard origin/main
```

#### Reset di File Specifici
```bash
# Rimuovere file dallo staging area
git reset HEAD file.txt

# Reset di un file a versione specifica
git reset a1b2c3d -- file.txt
```

## Git Revert: Annullamento Sicuro

### Revert Base
```bash
# Creare commit che annulla un commit precedente
git revert a1b2c3d
```

### Revert Multipli
```bash
# Revert di una serie di commit
git revert HEAD~3..HEAD

# Revert senza creare commit automatico
git revert --no-commit HEAD~2..HEAD
git commit -m "Revert: annullate modifiche problematiche"
```

### Revert di Merge
```bash
# Revert di un merge commit
git revert -m 1 merge-commit-hash
# -m 1 specifica il parent principale
```

## Confronto Reset vs Revert

| Aspetto | Reset | Revert |
|---------|-------|--------|
| **Sicurezza** | Può perdere dati | Sicuro |
| **History** | Riscrive storia | Mantiene storia |
| **Collaborazione** | Problematico se pushato | Sicuro per team |
| **Uso** | Repository locale | Repository condiviso |

## Workflow Pratici

### Scenario 1: Errore nell'Ultimo Commit (Locale)
```bash
# Situazione: commit sbagliato non ancora pushato
git log --oneline -3
# a1b2c3d Commit sbagliato
# d4e5f6g Commit precedente OK
# g7h8i9j Altro commit OK

# Soluzione: Reset soft per rielaborare
git reset --soft HEAD~1
git status  # Modifiche nello staging area
# Correggere e ricommittare
git commit -m "Commit corretto"
```

### Scenario 2: Rimozione Commit dal Mezzo
```bash
# Situazione: commit problematico nel mezzo della history
git log --oneline -5
# a1b2c3d Commit recente OK
# d4e5f6g Altro commit OK  
# g7h8i9j Commit PROBLEMATICO ← da rimuovere
# j0k1l2m Commit precedente OK
# m3n4o5p Base OK

# Soluzione: Revert sicuro
git revert g7h8i9j
```

### Scenario 3: Reset Completo a Versione Stabile
```bash
# Situazione: development branch compromesso
git branch backup-current  # Backup di sicurezza
git reset --hard origin/main
git clean -fd  # Rimuovere file non tracciati

# Verificare
git status
git log --oneline -3
```

## Reset Avanzato

### 1. Reset Interattivo
```bash
# Reset parziale con selezione interattiva
git reset -p HEAD~1
# Scegliere quali hunks resettare
```

### 2. Reset con Percorsi
```bash
# Reset di directory specifica
git reset HEAD~1 -- src/
git status  # Solo src/ è stata resettata
```

### 3. Reset con Backup Automatico
```bash
# Script per reset sicuro
#!/bin/bash
BACKUP_TAG="backup-$(date +%Y%m%d-%H%M%S)"
git tag $BACKUP_TAG
echo "Backup creato: $BACKUP_TAG"
git reset --hard $1
echo "Reset completato. Per recuperare: git reset --hard $BACKUP_TAG"
```

## Revert Avanzato

### 1. Revert di File Specifici
```bash
# Revert solo alcuni file da un commit
git show a1b2c3d --name-only  # Vedere file modificati
git checkout a1b2c3d~1 -- file1.txt file2.txt
git commit -m "Revert: ripristinati file1.txt e file2.txt"
```

### 2. Revert Condizionale
```bash
# Script per revert intelligente
#!/bin/bash
COMMIT_HASH=$1
FILES_CHANGED=$(git diff-tree --no-commit-id --name-only -r $COMMIT_HASH)

echo "File modificati nel commit $COMMIT_HASH:"
echo "$FILES_CHANGED"

read -p "Procedere con il revert? (y/N): " confirm
if [[ $confirm =~ ^[Yy]$ ]]; then
    git revert $COMMIT_HASH
else
    echo "Revert annullato"
fi
```

### 3. Revert di Merge con Strategia
```bash
# Revert di merge mantenendo alcuni cambiamenti
git revert -m 1 --no-commit merge-hash
git reset HEAD file-da-mantenere.txt
git checkout HEAD -- file-da-mantenere.txt
git commit -m "Revert parziale: mantenuto file critico"
```

## Recupero da Errori

### 1. Recupero dopo Reset Hard
```bash
# Usare reflog per trovare commit perso
git reflog
# a1b2c3d HEAD@{0}: reset: moving to HEAD~1
# d4e5f6g HEAD@{1}: commit: commit perso

# Recuperare
git reset --hard HEAD@{1}
```

### 2. Recupero File Singoli
```bash
# Recuperare file specifico da commit precedente
git checkout HEAD@{1} -- file-perso.txt
```

### 3. Recupero con git fsck
```bash
# Per casi estremi, cercare oggetti orfani
git fsck --lost-found
# Controllare .git/lost-found/
```

## Best Practices

### 1. Regole di Sicurezza
```bash
# Mai reset hard su branch condivisi
# Prima fare backup
git branch backup-$(date +%Y%m%d)
git reset --hard target-commit

# Usare revert per branch pubblici
git revert problematic-commit
```

### 2. Comunicazione Team
```bash
# Avvisare il team prima di reset su branch condivisi
echo "⚠️ ATTENZIONE: Reset planned su develop branch"
echo "📅 Data: $(date)"
echo "🎯 Target: origin/main"
echo "💾 Backup: backup-$(date +%Y%m%d)"
```

### 3. Automazione Sicura
```bash
# Alias per operazioni comuni
git config --global alias.soft-reset 'reset --soft HEAD~1'
git config --global alias.safe-revert '!f() { git tag backup-$(date +%Y%m%d-%H%M%S) && git revert "$1"; }; f'
```

## Script di Utilità

### Reset Sicuro con Conferma
```bash
#!/bin/bash
# safe-reset.sh
echo "🔍 Current status:"
git log --oneline -5

echo -e "\n📋 You are about to reset to: $1"
echo "⚠️  This will modify git history"

read -p "Are you sure? Type 'yes' to continue: " confirm
if [ "$confirm" != "yes" ]; then
    echo "❌ Reset cancelled"
    exit 1
fi

# Creare backup
BACKUP_TAG="backup-$(date +%Y%m%d-%H%M%S)"
git tag $BACKUP_TAG
echo "💾 Backup created: $BACKUP_TAG"

# Eseguire reset
git reset --hard $1
echo "✅ Reset completed"
echo "🔄 To undo: git reset --hard $BACKUP_TAG"
```

## Conclusioni
Reset e revert sono strumenti complementari:
- **Reset**: Per modifiche locali e riscrittura history
- **Revert**: Per annullamenti sicuri in ambienti collaborativi

La scelta dipende dal contesto e dalla necessità di preservare la history.
