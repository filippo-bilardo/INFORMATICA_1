# Troubleshooting Guide - Rebase e Cherry-Pick

## 🚨 Problemi Comuni e Soluzioni

### 1. "Cannot rebase: You have unstaged changes"

**🔍 Problema**: Hai modifiche non committate quando tenti un rebase.

**✅ Soluzioni**:
```bash
# Opzione 1: Stash delle modifiche
git stash
git rebase main
git stash pop

# Opzione 2: Commit temporaneo
git add .
git commit -m "WIP: temporary commit"
git rebase main
# Poi usa interactive rebase per rimuovere il commit WIP

# Opzione 3: Scarta modifiche (ATTENZIONE!)
git reset --hard HEAD
git rebase main
```

### 2. "CONFLICT: Merge conflict in file.txt"

**🔍 Problema**: Git non riesce a mergere automaticamente le modifiche.

**✅ Soluzione Step-by-Step**:
```bash
# 1. Identifica file in conflitto
git status

# 2. Per ogni file, apri in editor e cerca:
#    <<<<<<< HEAD
#    Le nostre modifiche
#    =======
#    Le loro modifiche  
#    >>>>>>> commit-hash

# 3. Risolvi manualmente combinando le modifiche
# 4. Rimuovi tutti i marker di conflitto
# 5. Salva il file

# 6. Aggiungi alla staging area
git add file.txt

# 7. Continua il rebase
git rebase --continue
```

### 3. "fatal: It seems that there is already a rebase-apply directory"

**🔍 Problema**: Rebase precedente non completato o interrotto male.

**✅ Soluzioni**:
```bash
# Opzione 1: Continua rebase precedente
git rebase --continue

# Opzione 2: Annulla rebase in corso
git rebase --abort

# Opzione 3: Pulizia forzata (ULTIMA RISORSA)
rm -rf .git/rebase-apply
git reset --hard HEAD
```

### 4. "error: could not apply abc123... commit message"

**🔍 Problema**: Commit specifico non può essere applicato durante rebase.

**✅ Soluzioni**:
```bash
# Opzione 1: Risolvi conflitti e continua
git status
# ... risolvi conflitti ...
git add .
git rebase --continue

# Opzione 2: Salta il commit problematico
git rebase --skip

# Opzione 3: Modifica il commit durante rebase
git rebase --edit-todo
```

### 5. "fatal: refusing to merge unrelated histories"

**🔍 Problema**: Tentativi di rebase tra repository senza storia comune.

**✅ Soluzioni**:
```bash
# Forza merge di storie non correlate
git rebase --allow-unrelated-histories main

# Alternativa: cherry-pick selettivo
git cherry-pick abc123 def456
```

## 🔧 Problemi di Cherry-Pick

### 1. "error: commit abc123 is a merge but no -m option was given"

**🔍 Problema**: Tentativi di cherry-pick di un merge commit.

**✅ Soluzioni**:
```bash
# Specifica quale parent del merge usare
git cherry-pick -m 1 abc123  # Primo parent (solito main)
git cherry-pick -m 2 abc123  # Secondo parent (branch mergato)

# Alternativa: cherry-pick dei commit individuali
git log abc123
git cherry-pick def456 ghi789  # I commit individuali del merge
```

### 2. "The previous cherry-pick is now empty"

**🔍 Problema**: Il commit da cherry-pick è già presente nel branch target.

**✅ Soluzioni**:
```bash
# Salta il commit vuoto
git cherry-pick --skip

# Continua con il prossimo
git cherry-pick --continue

# Verifica se il commit è già presente
git log --oneline --grep="partial commit message"
```

### 3. "fatal: bad revision 'HEAD'"

**🔍 Problema**: Repository corrotto o senza commit iniziali.

**✅ Soluzioni**:
```bash
# Verifica integrità repository
git fsck

# Verifica se ci sono commit
git log --oneline

# Se repository vuoto, crea commit iniziale
git commit --allow-empty -m "Initial commit"
```

## 🆘 Recovery da Situazioni Critiche

### 1. "Ho perso commit importanti durante rebase"

**🔍 Problema**: Commit spariti dopo rebase fallito.

**✅ Recovery**:
```bash
# 1. Usa reflog per trovare commit perduti
git reflog

# 2. Identifica l'hash del commit perduto
git reflog --all | grep "commit message"

# 3. Recupera commit specifico
git cherry-pick commit-hash

# 4. Oppure ripristina intero branch
git checkout -b recovered-branch commit-hash

# 5. Verifica integrità
git fsck --lost-found
```

### 2. "Repository completamente corrotto"

**🔍 Problema**: Operazioni multiple fallite, repository inutilizzabile.

**✅ Recovery**:
```bash
# 1. Backup di quello che rimane
cp -r .git .git.backup

# 2. Verifica integrità
git fsck --full

# 3. Recupera oggetti dangling
for obj in $(git fsck --lost-found | grep dangling | awk '{print $3}'); do
    git show $obj > /tmp/recovered_$obj.patch
done

# 4. Se troppo corrotto, clona nuovo repository
cd ..
git clone https://github.com/user/repo.git repo-clean
cd repo-clean
# Applica manualmente le modifiche non pushate
```

### 3. "Branch condiviso modificato con rebase"

**🔍 Problema**: Hai fatto rebase su branch pubblico, altri sviluppatori hanno problemi.

**✅ Comunicazione Team**:
```bash
# 1. IMMEDIATA comunicazione al team
echo "⚠️  ALERT: Rebase su branch pubblico!"

# 2. Instruzioni per il team:
# Per ogni sviluppatore:
git fetch origin
git reset --hard origin/branch-name

# 3. Se ci sono modifiche locali da salvare:
git stash
git reset --hard origin/branch-name
git stash pop
# Risolvi conflitti manualmente

# 4. PREVENZIONE futura:
git config --global rebase.missingCommitsCheck error
```

## 🔍 Debug Avanzato

### 1. Analisi Dettagliata Conflitti

```bash
# Vedi tutti i file modificati tra branch
git diff --name-status main...feature-branch

# Analisi dettagliata per file specifico
git diff main...feature-branch -- filename.txt

# Storia del file su entrambi i branch
git log --oneline main -- filename.txt
git log --oneline feature-branch -- filename.txt

# Chi ha modificato cosa (blame)
git blame filename.txt
```

### 2. Trace Operazioni Git

```bash
# Debug dettagliato rebase
GIT_TRACE=1 git rebase main

# Debug merge strategy
GIT_TRACE=1 git rebase -X theirs main

# Log tutte le operazioni
GIT_TRACE_SETUP=1 GIT_TRACE_PACK_ACCESS=1 git rebase main
```

### 3. Stato Interno Repository

```bash
# Verifica stato rebase
cat .git/rebase-apply/next
cat .git/rebase-apply/last

# Vedi patch corrente
cat .git/rebase-apply/patch

# Verifica HEAD e refs
cat .git/HEAD
cat .git/refs/heads/main
```

## 🔧 Tools e Utilities

### 1. Scripts di Automazione

```bash
# Script per backup automatico
#!/bin/bash
create_backup() {
    local branch=$(git branch --show-current)
    local timestamp=$(date +%Y%m%d-%H%M%S)
    git tag "backup-${branch}-${timestamp}"
    echo "✅ Backup creato: backup-${branch}-${timestamp}"
}

# Script per cleanup post-rebase
#!/bin/bash
cleanup_after_rebase() {
    # Rimuovi backup tags vecchi (>30 giorni)
    git tag -l "backup-*" | while read tag; do
        local tag_date=$(git log -1 --format=%ct "$tag")
        local current_date=$(date +%s)
        local age_days=$(( (current_date - tag_date) / 86400 ))
        
        if [ $age_days -gt 30 ]; then
            git tag -d "$tag"
            echo "🗑️  Rimosso backup vecchio: $tag"
        fi
    done
}

# Script per verifica pre-rebase
#!/bin/bash
pre_rebase_check() {
    echo "🔍 Verifica pre-rebase..."
    
    # Verifica working directory pulita
    if ! git diff-index --quiet HEAD --; then
        echo "❌ Working directory non pulita"
        git status --porcelain
        return 1
    fi
    
    # Verifica upstream aggiornato
    git fetch origin
    local behind=$(git rev-list --count HEAD..origin/main)
    if [ $behind -gt 0 ]; then
        echo "⚠️  Branch main locale indietro di $behind commit"
    fi
    
    # Stima conflitti potenziali
    local conflicts=$(git merge-tree $(git merge-base HEAD origin/main) HEAD origin/main | grep -c "<<<<<<< ")
    if [ $conflicts -gt 0 ]; then
        echo "⚠️  $conflicts possibili conflitti rilevati"
    fi
    
    echo "✅ Verifica completata"
}
```

### 2. Configurazioni Debugging

```bash
# Abilita debugging dettagliato
git config --global advice.detachedHead false
git config --global advice.resolveConflict true
git config --global advice.statusHints true

# Configurazioni merge avanzate
git config --global merge.conflictstyle diff3
git config --global rerere.enabled true
```

### 3. Alias per Troubleshooting

```bash
# Alias per situazioni di emergenza
git config --global alias.panic '!git stash && git checkout main && git pull origin main'
git config --global alias.conflicts 'diff --name-only --diff-filter=U'
git config --global alias.abort-all '!git rebase --abort; git merge --abort; git cherry-pick --abort; git am --abort'

# Alias per recovery
git config --global alias.lost 'fsck --lost-found'
git config --global alias.recover 'reflog --all'
git config --global alias.undo 'reset --hard HEAD@{1}'
```

## 📊 Prevenzione Problemi

### 1. Checklist Pre-Operazione

- [ ] Working directory pulita (`git status`)
- [ ] Backup creato (`git tag backup-$(date +%Y%m%d-%H%M%S)`)
- [ ] Branch upstream aggiornato (`git fetch`)
- [ ] Verifica conflitti potenziali (`git merge-tree`)
- [ ] Team informato (se branch condiviso)

### 2. Monitoraggio Continuo

```bash
# Check salute repository (weekly)
#!/bin/bash
weekly_health_check() {
    echo "🏥 Weekly Repository Health Check"
    
    # Dimensione repository
    echo "📊 Repository size: $(du -sh .git)"
    
    # Oggetti non referenziati
    local dangling=$(git fsck --lost-found 2>/dev/null | grep dangling | wc -l)
    echo "🗑️  Dangling objects: $dangling"
    
    # Compressione
    git gc --auto
    
    # Verifica integrità
    git fsck --quiet || echo "❌ Repository integrity issues found"
    
    echo "✅ Health check completed"
}
```

### 3. Training Team

- **Documentazione**: Mantieni questo troubleshooting guide aggiornato
- **Simulazioni**: Praticate scenari di recovery in repository di test  
- **Code Review**: Include controlli pre-rebase nei PR templates
- **Monitoring**: Setup alerts per operazioni Git rischiose

## 🆘 Contatti Emergenza

### Escalation Path

1. **Self-service**: Questa guida + Google/Stack Overflow
2. **Team Lead**: Per decisioni su branch condivisi
3. **DevOps/Admin**: Per problemi infrastruttura Git
4. **Backup Recovery**: Per perdite dati critiche

### Informazioni per Supporto

Quando chiedi aiuto, includi sempre:

```bash
# Informazioni sistema
git --version
git config --list | grep user
git config --list | grep merge
git config --list | grep rebase

# Stato repository
git status
git log --oneline -10
git reflog -10

# Dettagli errore
cat .git/rebase-apply/patch  # Se applicabile
git fsck                     # Output completo
```

---

**⚠️ IMPORTANTE**: In caso di dubbio, sempre fare backup prima di tentare recovery complessi!
