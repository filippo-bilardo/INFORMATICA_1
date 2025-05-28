# Best Practices per Rebase e Cherry-Pick

## 🎯 Linee Guida Generali

### ✅ Quando Usare Rebase

| Scenario | Usa Rebase | Perché |
|----------|------------|---------|
| Branch feature privato | ✅ | Storia lineare e pulita |
| Sync con upstream | ✅ | Evita merge commit inutili |
| Cleanup prima di PR | ✅ | Migliore revisione del codice |
| Riorganizzazione commit | ✅ | Storia logica e atomica |

### ❌ Quando NON Usare Rebase

| Scenario | NON Usare | Perché |
|----------|-----------|---------|
| Branch condiviso pubblico | ❌ | Riscrive storia condivisa |
| Main/Master branch | ❌ | Confonde altri sviluppatori |
| Dopo push pubblico | ❌ | Problemi di sincronizzazione |
| Merge commit importanti | ❌ | Perdita contesto temporale |

## 🔧 Preparazione Pre-Rebase

### 1. Checklist di Sicurezza

```bash
# ✅ Verifica stato repository
git status
git stash  # Se ci sono modifiche non committate

# ✅ Crea backup
git tag backup-$(date +%Y%m%d-%H%M%S)
# oppure
git branch backup-feature-branch

# ✅ Verifica commit da rebasare
git log --oneline main..feature-branch

# ✅ Identifica potenziali conflitti
git merge-tree $(git merge-base main feature-branch) main feature-branch
```

### 2. Analisi Pre-Conflitti

```bash
# Vedi differenze che potrebbero confliggere
git diff main...feature-branch

# Controlla file modificati da entrambi i branch
git diff --name-only main...feature-branch | \
    while read file; do
        echo "File: $file"
        git log --oneline main -- "$file"
        git log --oneline feature-branch -- "$file"
        echo "---"
    done
```

## 🎯 Strategie di Rebase

### 1. Rebase Semplice
```bash
# Per feature branch corti e lineari
git checkout feature-branch
git rebase main
```

### 2. Interactive Rebase per Cleanup
```bash
# Per riorganizzare, combinare, modificare commit
git rebase -i HEAD~5

# Comandi disponibili:
# pick   = usa commit così com'è
# reword = usa commit ma modifica messaggio
# edit   = usa commit ma fermati per modifiche
# squash = usa commit e combinalo con precedente
# fixup  = come squash ma scarta messaggio
# drop   = rimuovi commit completamente
```

### 3. Rebase con Strategia di Merge
```bash
# Usa strategia specifica per conflitti
git rebase -X theirs main    # Preferisce modifiche del branch target
git rebase -X ours main      # Preferisce modifiche del branch corrente
git rebase -X patience main  # Algoritmo più accurato per conflitti
```

## 🔍 Gestione Conflitti Avanzata

### 1. Strumenti di Merge

```bash
# Configura merge tool preferito
git config --global merge.tool vimdiff
git config --global merge.tool vscode
git config --global merge.tool meld

# Usa merge tool durante conflitto
git mergetool

# Merge tool personalizzato per VS Code
git config --global mergetool.code.cmd 'code --wait --merge $REMOTE $LOCAL $BASE $MERGED'
```

### 2. Analisi Conflitti Dettagliata

```bash
# Vedi solo file in conflitto
git diff --name-only --diff-filter=U

# Analisi dettagliata conflitto
git show :1:filename    # Common ancestor
git show :2:filename    # HEAD (nostro)
git show :3:filename    # MERGE_HEAD (loro)

# Diff con più contesto
git diff -U10 filename
```

### 3. Risoluzione Step-by-Step

```bash
# 1. Identifica tipo di conflitto
git status

# 2. Per ogni file in conflitto:
#    - Apri in editor
#    - Cerca <<<<<<< HEAD
#    - Analizza sezioni:
#      <<<<<<< HEAD
#      le nostre modifiche
#      =======
#      le loro modifiche
#      >>>>>>> commit-hash
#    - Combina logicamente
#    - Rimuovi marker

# 3. Test il file risolto
# 4. Aggiungi alla staging area
git add filename

# 5. Continua rebase
git rebase --continue
```

## 🍒 Best Practices Cherry-Pick

### 1. Identificazione Commit

```bash
# Trova commit da cherry-pick
git log --oneline --graph feature-branch

# Cherry-pick specifico
git cherry-pick abc123

# Cherry-pick range
git cherry-pick abc123..def456

# Cherry-pick senza commit automatico
git cherry-pick -n abc123
```

### 2. Cherry-Pick Strategico

```bash
# Per hotfix urgenti
git checkout main
git cherry-pick hotfix-commit
git push origin main

# Per backport a versioni precedenti
git checkout release/v1.2
git cherry-pick feature-commit
git push origin release/v1.2
```

### 3. Gestione Conflitti Cherry-Pick

```bash
# Risolvi conflitti durante cherry-pick
git status
# ... risolvi conflitti ...
git add .
git cherry-pick --continue

# Salta commit problematico
git cherry-pick --skip

# Annulla cherry-pick
git cherry-pick --abort
```

## 🚨 Recovery e Emergenze

### 1. Annullamento Operazioni

```bash
# Annulla rebase in corso
git rebase --abort

# Torna a stato precedente
git reset --hard ORIG_HEAD

# Usa reflog per trovare stato perduto
git reflog
git reset --hard HEAD@{5}
```

### 2. Recovery Avanzato

```bash
# Se hai perso commit importanti
git fsck --lost-found
git show dangling-commit-hash

# Recupera branch cancellato accidentalmente
git reflog --all | grep branch-name
git checkout -b recovered-branch commit-hash
```

### 3. Pulizia Repository

```bash
# Dopo operazioni complesse, pulisci
git gc --prune=now
git prune
git repack -ad
```

## 📊 Monitoring e Debug

### 1. Verifica Stato Repository

```bash
# Verifica integrità
git fsck

# Statistiche repository
git count-objects -v

# Vedi divergenze
git show-branch main feature-branch
```

### 2. Analisi Performance

```bash
# Tempo operazioni Git
time git rebase main

# Dimensione repository
du -sh .git

# Log dettagliato operazioni
GIT_TRACE=1 git rebase main
```

## 🔄 Workflow Consigliati

### 1. Feature Development

```bash
# 1. Crea feature branch
git checkout -b feature/new-feature main

# 2. Sviluppa e committa
git add .
git commit -m "feat: implement feature"

# 3. Sync periodico con main
git fetch origin
git rebase origin/main

# 4. Cleanup prima di PR
git rebase -i origin/main

# 5. Push e crea PR
git push origin feature/new-feature
```

### 2. Hotfix Workflow

```bash
# 1. Crea hotfix da main
git checkout -b hotfix/critical-fix main

# 2. Implementa fix
git add .
git commit -m "fix: critical security issue"

# 3. Cherry-pick su main
git checkout main
git cherry-pick hotfix/critical-fix

# 4. Cherry-pick su release branches
git checkout release/v1.2
git cherry-pick hotfix/critical-fix
```

### 3. Release Workflow

```bash
# 1. Crea release branch
git checkout -b release/v2.0 develop

# 2. Bug fixes solo su release
git commit -m "fix: release bug"

# 3. Cherry-pick fixes a develop
git checkout develop  
git cherry-pick release/v2.0

# 4. Merge release a main
git checkout main
git merge --no-ff release/v2.0
git tag v2.0.0
```

## ⚙️ Configurazioni Consigliate

### 1. Configurazione Git Globale

```bash
# Rebase di default per pull
git config --global pull.rebase true

# Editor preferito
git config --global core.editor "code --wait"

# Merge tool
git config --global merge.tool vscode

# Configurazione rebase
git config --global rebase.autoStash true
git config --global rebase.autoSquash true

# Configurazione cherry-pick
git config --global cherry-pick.autoStash true
```

### 2. Alias Utili

```bash
# Rebase aliases
git config --global alias.rb 'rebase'
git config --global alias.rbi 'rebase -i'
git config --global alias.rbc 'rebase --continue'
git config --global alias.rba 'rebase --abort'

# Cherry-pick aliases
git config --global alias.cp 'cherry-pick'
git config --global alias.cpc 'cherry-pick --continue'
git config --global alias.cpa 'cherry-pick --abort'

# Log aliases
git config --global alias.lg 'log --oneline --graph'
git config --global alias.conflicts 'diff --name-only --diff-filter=U'
```

### 3. Scripts Automatici

```bash
# Script per backup automatico prima di rebase
cat > ~/.gitconfig << 'EOF'
[alias]
    safe-rebase = "!f() { \
        git tag backup-$(date +%Y%m%d-%H%M%S) && \
        git rebase $1; \
    }; f"
EOF
```

## 📈 Metriche e KPI

### 1. Misurazione Qualità

```bash
# Numero commit per feature
git rev-list --count main..feature-branch

# Dimensione media commit
git log --shortstat main..feature-branch

# Frequenza conflitti
git log --grep="conflict" --oneline
```

### 2. Team Metrics

- **Frequenza rebase**: Numero rebase per settimana
- **Tempo risoluzione conflitti**: Media tempo per risolvere conflitti
- **Successo rate**: Percentuale rebase completati senza problemi
- **Complessità branch**: Numero commit per feature branch

## 🎓 Training Path

### Livello Principiante
1. Git basics e merge
2. Rebase semplice su branch privati
3. Interactive rebase per cleanup
4. Cherry-pick per hotfix

### Livello Intermedio
1. Gestione conflitti complessi
2. Strategie di merge avanzate
3. Recovery da errori
4. Workflow team standardizzati

### Livello Avanzato
1. Scripting per automazione
2. Performance optimization
3. Repository maintenance
4. Troubleshooting avanzato

---

**💡 Ricorda**: La pratica rende perfetti. Inizia con repository di test prima di applicare queste tecniche su progetti importanti!
