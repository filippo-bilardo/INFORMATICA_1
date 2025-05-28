# Recupero File e Cronologia Git

## 📚 Introduzione

Uno degli aspetti più potenti di Git è la capacità di recuperare file, commit e modifiche che sembrano perduti. Questa guida esplora le tecniche avanzate per il recupero di dati utilizzando reflog, fsck, e altri strumenti di Git.

## 🎯 Obiettivi di Apprendimento

- Comprendere il funzionamento del reflog di Git
- Recuperare commit cancellati o "persi"
- Ripristinare file eliminati dalla cronologia
- Utilizzare git fsck per il recupero di emergenza
- Gestire situazioni di corruzioni del repository
- Implementare strategie di backup e recovery

## 📖 Teoria: Sistema di Recupero Git

### Il Reflog: La Cronologia Completa

Il reflog (reference log) è la cronologia completa di tutte le modifiche ai riferimenti (HEAD, branch) nel repository locale.

```
Reflog Structure:
SHA1-HASH HEAD@{n}: action: commit message

Esempio:
a1b2c3d HEAD@{0}: commit: Latest commit
d4e5f6g HEAD@{1}: reset: moving to HEAD~1
g7h8i9j HEAD@{2}: commit: Previous commit
```

### Tipi di Recupero

1. **Recupero Commit**: Commit cancellati con reset/rebase
2. **Recupero File**: File eliminati dalla cronologia
3. **Recupero Branch**: Branch cancellati accidentalmente
4. **Recupero Repository**: Corruzioni e danni gravi

## 🔍 Comandi di Diagnosi

### Visualizzare il Reflog

```bash
# Reflog completo di HEAD
git reflog

# Reflog di un branch specifico
git reflog main

# Reflog con timestamp dettagliato
git reflog --date=iso

# Reflog degli ultimi N giorni
git reflog --since="3 days ago"

# Reflog con diff
git reflog -p
```

### Ispezionare Oggetti Git

```bash
# Verificare integrità repository
git fsck --full

# Trovare oggetti non referenziati
git fsck --unreachable

# Visualizzare tutti gli oggetti
git rev-list --objects --all

# Cercare oggetti specifici
git cat-file -t SHA1  # tipo oggetto
git cat-file -p SHA1  # contenuto oggetto
```

## 🔧 Tecniche di Recupero

### 1. Recupero Commit con Reflog

```bash
# Scenario: reset accidentale ha cancellato commit
git reset --hard HEAD~3  # ❌ Cancella 3 commit

# Recupero usando reflog
git reflog
# a1b2c3d HEAD@{0}: reset: moving to HEAD~3
# d4e5f6g HEAD@{1}: commit: Important work  ← Da recuperare
# g7h8i9j HEAD@{2}: commit: More important work
# k1l2m3n HEAD@{3}: commit: Critical feature

# Recuperare i commit persi
git reset --hard HEAD@{1}  # Torna al commit importante

# Oppure creare un branch dal commit perso
git branch recovered-work HEAD@{1}
```

### 2. Recupero File Eliminati

```bash
# Scenario: file eliminato e commit rimosso
git rm important-file.txt
git commit -m "Remove file"

# Trovare quando il file esisteva ancora
git log --oneline --follow -- important-file.txt

# Recuperare il file da un commit specifico
git checkout SHA1-HASH -- important-file.txt

# Oppure dal commit precedente
git checkout HEAD~1 -- important-file.txt
```

### 3. Recupero File da Directory

```bash
# Recuperare intera directory eliminata
git checkout HEAD~1 -- src/deleted-folder/

# Recuperare tutti i file con pattern
git checkout HEAD~1 -- "*.config"

# Recuperare file rinominato
git log --follow --name-status -- old-name.txt
git checkout SHA1-HASH -- old-name.txt
```

### 4. Recupero Branch Cancellati

```bash
# Scenario: branch cancellato accidentalmente
git branch -D feature-branch  # ❌ Branch eliminato

# Trovare l'ultimo commit del branch nel reflog
git reflog | grep "feature-branch"
# a1b2c3d HEAD@{5}: checkout: moving from feature-branch to main

# Ricreare il branch
git branch feature-branch a1b2c3d

# Oppure da reflog specifico
git branch feature-branch HEAD@{5}
```

## 🚨 Recupero di Emergenza

### Usando git fsck

```bash
# Trovare oggetti non referenziati (dangling)
git fsck --unreachable

# Output tipico:
# unreachable commit a1b2c3d4e5f6...
# unreachable blob g7h8i9j0k1l2...

# Esaminare commit unreachable
git show a1b2c3d4e5f6

# Recuperare commit unreachable
git branch recovered-commit a1b2c3d4e5f6
```

### Recupero da Corruzioni

```bash
# Diagnosticare corruzioni
git fsck --full --strict

# Recuperare da backup di oggetti
cp .git/objects/SHA1[0:2]/SHA1[2:] .git/objects/BACKUP/

# Ricostruire index corrotto
rm .git/index
git reset

# Recuperare da clone
git clone --mirror original-repo backup-repo
cd backup-repo
git fsck --full
```

## 📋 Scenari di Recupero Completi

### Scenario 1: Reset Disastroso

```bash
# Situazione: cancellati 10 commit con reset hard
git reset --hard HEAD~10

# Step 1: Analizzare reflog
git reflog --oneline -20

# Step 2: Identificare commit da recuperare
git reflog | head -15
# Output:
# a1b2c3d HEAD@{0}: reset: moving to HEAD~10
# d4e5f6g HEAD@{1}: commit: Feature complete  ← Target
# g7h8i9j HEAD@{2}: commit: Add tests

# Step 3: Recuperare
git reset --hard HEAD@{1}

# Step 4: Verificare recupero
git log --oneline -5
```

### Scenario 2: File Importante Cancellato dalla Storia

```bash
# Situazione: file cancellato 5 commit fa
# e vuoi recuperarlo senza perdere storia

# Step 1: Trovare quando è stato eliminato
git log --oneline --follow -- config/important.yml

# Step 2: Trovare l'ultimo commit che lo conteneva
git log --diff-filter=D --summary | grep important.yml

# Step 3: Recuperare da commit precedente
git show HEAD~5:config/important.yml > config/important.yml

# Step 4: Aggiungere e committare
git add config/important.yml
git commit -m "Recover important configuration file"
```

### Scenario 3: Branch con Lavoro Importante Cancellato

```bash
# Situazione: branch con giorni di lavoro cancellato

# Step 1: Cercare nel reflog generale
git reflog | grep "checkout.*important-feature"

# Step 2: Analizzare log di tutti i branch
git log --all --graph --oneline | grep "important feature"

# Step 3: Usare fsck per trovare commit unreachable
git fsck --unreachable | grep commit

# Step 4: Esaminare commit candidati
for commit in $(git fsck --unreachable | grep commit | cut -d' ' -f3); do
    echo "=== $commit ==="
    git show --oneline -s $commit
done

# Step 5: Recuperare branch trovato
git branch recovered-important-feature SHA1-DEL-COMMIT
```

## 🔄 Automazione del Recupero

### Script di Backup Automatico

```bash
#!/bin/bash
# backup-git.sh
REPO_PATH="$1"
BACKUP_PATH="$2"

cd "$REPO_PATH"

# Backup completo con reflog
git bundle create "$BACKUP_PATH/repo-$(date +%Y%m%d).bundle" --all --reflog

# Backup oggetti
tar -czf "$BACKUP_PATH/objects-$(date +%Y%m%d).tar.gz" .git/objects/

# Log di backup
echo "$(date): Backup completato" >> "$BACKUP_PATH/backup.log"
```

### Script di Recupero Assistito

```bash
#!/bin/bash
# recover-assistant.sh

echo "=== Git Recovery Assistant ==="
echo "1. Analisi reflog..."
git reflog --oneline -20

echo "2. Commit unreachable..."
git fsck --unreachable | grep commit | head -10

echo "3. Branch recenti..."
git branch -a --sort=-committerdate | head -10

echo "Inserisci SHA1 da recuperare:"
read sha1
echo "Inserisci nome branch di recupero:"
read branch_name

git branch "$branch_name" "$sha1"
echo "Branch $branch_name creato da $sha1"
```

## 📊 Strategia di Recovery per Tipo di Problema

| Problema | Strumento Primario | Comando Base | Note |
|----------|-------------------|---------------|------|
| Commit perso | Reflog | `git reflog` → `git reset --hard` | Entro 30-90 giorni |
| File eliminato | Log + Checkout | `git log --follow` → `git checkout` | Se è nella cronologia |
| Branch cancellato | Reflog + Branch | `git reflog` → `git branch` | Se referenziato di recente |
| Repository corrotto | Fsck + Clone | `git fsck` → `git clone` | Backup essenziale |
| Oggetti dangling | Fsck | `git fsck --unreachable` | Per pulizia o recupero |
| Index corrotto | Reset + Status | `rm .git/index` → `git reset` | Rapido da ricostruire |

## ⚠️ Limitazioni del Recupero

### Dati Non Recuperabili

```bash
# ❌ Modifiche mai committate
echo "important data" > file.txt  # Perso se non committato

# ❌ Dati oltre la scadenza reflog (default 30-90 giorni)
git config gc.reflogExpire         # default: 90 giorni
git config gc.reflogExpireUnreachable  # default: 30 giorni

# ❌ Oggetti rimossi da garbage collection
git gc --prune=now  # Rimuove oggetti unreachable
```

### Configurazioni per Massimizzare Recovery

```bash
# Estendere durata reflog
git config gc.reflogExpire "1 year"
git config gc.reflogExpireUnreachable "6 months"

# Disabilitare auto-gc (temporaneamente)
git config gc.auto 0

# Backup automatico prima di operazioni rischiose
git config alias.safe-reset '!f() { git branch backup-$(date +%s) && git reset "$@"; }; f'
```

## 💡 Best Practices per Recovery

### 1. Prevenzione
```bash
# Alias sicuri che creano backup automatici
git config --global alias.safe-reset '!git branch backup-$(date +%s) && git reset'
git config --global alias.safe-rebase '!git branch backup-$(date +%s) && git rebase'
```

### 2. Backup Regolari
```bash
# Backup settimanale con bundle
git bundle create backup-$(date +%Y%m%d).bundle --all --reflog

# Backup oggetti critici
tar -czf objects-backup.tar.gz .git/objects/
```

### 3. Monitoraggio
```bash
# Controllo integrità regolare
git fsck --full > integrity-check.log

# Verifica dimensioni repository
du -sh .git/objects/
```

## 🔗 Comandi di Riferimento Rapido

```bash
# Recupero base
git reflog                          # Cronologia completa
git fsck --unreachable             # Oggetti non referenziati
git branch recovery SHA1           # Creare branch da commit

# Recupero file
git checkout SHA1 -- file          # Recuperare file specifico
git show SHA1:path/file            # Mostrare contenuto file
git log --follow -- file          # Storia completa file

# Diagnostica
git fsck --full                    # Verifica integrità completa
git count-objects -v               # Statistiche oggetti
git gc --dry-run                   # Anteprima garbage collection
```

## 📝 Riassunto

Il sistema di recupero di Git è molto robusto grazie al reflog e alla struttura immutabile degli oggetti. La maggior parte dei dati può essere recuperata entro 30-90 giorni dalla cancellazione, purché si conoscano le tecniche appropriate.

Le chiavi per un recupero efficace sono:
1. **Agire rapidamente** prima che il garbage collector rimuova gli oggetti
2. **Usare il reflog** come prima risorsa per commit e branch
3. **Utilizzare git fsck** per situazioni complesse
4. **Implementare backup regolari** per scenari critici
5. **Configurare alias sicuri** per prevenire perdite future

Ricorda: Git raramente perde dati definitivamente, ma trovarli richiede pazienza e conoscenza degli strumenti giusti.
