# Interactive Rebase

## 📖 Introduzione all'Interactive Rebase

L'Interactive Rebase è una delle funzionalità più potenti di Git per la riscrittura della cronologia. Ti permette di modificare, riordinare, combinare, dividere e persino eliminare commit in modo granulare, mantenendo il controllo completo sulla cronologia del tuo progetto.

## 🎯 Cosa Imparerai

- Utilizzo avanzato del rebase interattivo
- Tutte le operazioni disponibili (pick, squash, edit, drop, etc.)
- Tecniche per pulire e ottimizzare la cronologia
- Strategie per commit atomici e significativi
- Automazione del processo di cleanup
- Risoluzione di conflitti complessi

## 🚀 Avvio dell'Interactive Rebase

### Sintassi Base

```bash
# Rebase interattivo degli ultimi N commit
git rebase -i HEAD~N

# Rebase interattivo da un commit specifico
git rebase -i <commit-hash>

# Rebase interattivo fino al root
git rebase -i --root

# Rebase interattivo con editor specifico
GIT_EDITOR=vim git rebase -i HEAD~5
```

### Esempio di Avvio

```bash
# Scenario: ultimi 4 commit da riorganizzare
git log --oneline
a1b2c3d Fix typo in documentation
e4f5g6h Add user validation
i7j8k9l WIP: working on feature
m1n2o3p Add initial feature structure

git rebase -i HEAD~4
```

## 📋 Interfaccia Interactive Rebase

### Editor che Si Apre

```bash
pick m1n2o3p Add initial feature structure
pick i7j8k9l WIP: working on feature  
pick e4f5g6h Add user validation
pick a1b2c3d Fix typo in documentation

# Rebase a1b2c3d..m1n2o3p onto m1n2o3p (4 commands)
#
# Commands:
# p, pick <commit> = use commit
# r, reword <commit> = use commit, but edit the commit message
# e, edit <commit> = use commit, but stop for amending
# s, squash <commit> = use commit, but meld into previous commit
# f, fixup <commit> = like "squash", but discard this commit's log message
# x, exec <command> = run command (the rest of the line) using shell
# b, break = stop here (continue rebase later with 'git rebase --continue')
# d, drop <commit> = remove commit
# l, label <label> = label current HEAD with a name
# t, reset <label> = reset HEAD to a label
# m, merge [-C <commit> | -c <commit>] <label> [# <oneline>]
```

## 🛠️ Operazioni Disponibili

### 1. Pick (p) - Mantieni Commit

```bash
# Mantiene il commit così com'è
pick a1b2c3d Fix typo in documentation

# È l'operazione di default
```

### 2. Reword (r) - Modifica Messaggio

```bash
# Permette di modificare solo il messaggio di commit
reword e4f5g6h Add user validation

# Git aprirà l'editor per modificare il messaggio
```

### 3. Edit (e) - Modifica Commit

```bash
# Ferma il rebase per permettere modifiche al commit
edit i7j8k9l WIP: working on feature

# Dopo le modifiche:
git add .
git commit --amend
git rebase --continue
```

### 4. Squash (s) - Combina con Precedente

```bash
pick m1n2o3p Add initial feature structure
squash i7j8k9l WIP: working on feature

# Combina i due commit mantenendo entrambi i messaggi
```

### 5. Fixup (f) - Combina Scartando Messaggio

```bash
pick e4f5g6h Add user validation  
fixup a1b2c3d Fix typo in documentation

# Combina ma mantiene solo il messaggio del primo commit
```

### 6. Drop (d) - Elimina Commit

```bash
# Rimuove completamente il commit
drop i7j8k9l WIP: working on feature
```

### 7. Exec (x) - Esegui Comando

```bash
pick m1n2o3p Add initial feature structure
exec npm test
pick e4f5g6h Add user validation
exec npm run lint
```

## 🎨 Scenari Pratici di Cleanup

### Scenario 1: Pulizia Branch Feature

**Situazione iniziale:**
```bash
git log --oneline
f1e2d3c Fix linting errors
e4r5t6y Add tests for validation
w7e8r9t Fix typo in test
q1w2e3r Implement user validation
a1s2d3f WIP: validation logic
z1x2c3v Add validation endpoint
```

**Interactive Rebase:**
```bash
git rebase -i HEAD~6

# Editor:
pick z1x2c3v Add validation endpoint
squash a1s2d3f WIP: validation logic
reword q1w2e3r Implement user validation
pick e4r5t6y Add tests for validation
fixup w7e8r9t Fix typo in test
fixup f1e2d3c Fix linting errors
```

**Risultato finale:**
```bash
git log --oneline
a9b8c7d Add comprehensive tests for validation
e5f6g7h Implement robust user validation system
m3n4o5p Add validation endpoint with complete logic
```

### Scenario 2: Riorganizzazione Logica

**Prima:**
```bash
4a5b6c7 Update documentation
3d8e9f1 Fix bug in login
2g1h2i3 Add password reset feature
1j4k5l6 Implement login system
```

**Rebase per logica:**
```bash
git rebase -i HEAD~4

# Riorganizza:
pick 1j4k5l6 Implement login system
pick 3d8e9f1 Fix bug in login
pick 2g1h2i3 Add password reset feature
pick 4a5b6c7 Update documentation
```

## 🔧 Tecniche Avanzate

### 1. Edit per Dividere Commit

```bash
# Commit troppo grande da dividere
edit abc1234 Implement entire authentication system

# Durante l'edit:
git reset HEAD~1

# Crea commit separati
git add auth/login.js
git commit -m "Implement login functionality"

git add auth/register.js
git commit -m "Implement registration"

git add auth/validation.js
git commit -m "Add input validation"

git rebase --continue
```

### 2. Squash Intelligente con Script

```bash
#!/bin/bash
# auto-squash.sh - Squash automatico di commit "fixup"

git log --oneline --grep="fixup\|wip\|temp" --pretty=format:"%h %s" | while read commit; do
    echo "Commit da squash: $commit"
done

echo "Vuoi procedere con il rebase interattivo? (y/n)"
read response

if [ "$response" = "y" ]; then
    # Conta commit da considerare
    COMMIT_COUNT=$(git log --oneline --grep="fixup\|wip\|temp" | wc -l)
    TOTAL_COUNT=$((COMMIT_COUNT + 5)) # Includi qualche commit extra
    
    git rebase -i HEAD~$TOTAL_COUNT
fi
```

### 3. Template per Rebase Complesso

```bash
#!/bin/bash
# rebase-template.sh

cat > /tmp/rebase-template << 'EOF'
# 🎯 Interactive Rebase Guidelines
# 
# 1. PICK: Commit completi e ben formattati
# 2. SQUASH: Commit correlati da combinare
# 3. FIXUP: Piccole correzioni (mantieni solo il primo messaggio)
# 4. EDIT: Commit da dividere o modificare sostanzialmente
# 5. DROP: Commit sperimentali o duplicati
# 6. REWORD: Messaggi da migliorare
#
# ⚠️ REGOLE:
# - Un commit = una funzionalità/fix logico
# - Messaggi chiari e descrittivi
# - Test passano per ogni commit
# - Niente commit "WIP" o "temp"
#
# 🔄 WORKFLOW:
# 1. Raggruppa commit correlati
# 2. Ordina logicamente
# 3. Verifica che ogni commit sia atomico
# 4. Controlla che i test passino

EOF

echo "📋 Template creato in /tmp/rebase-template"
echo "💡 Usa: GIT_EDITOR='cat /tmp/rebase-template && vim' git rebase -i HEAD~N"
```

## 🐛 Risoluzione Problemi Avanzati

### Conflitti Durante Interactive Rebase

```bash
# Conflitto durante squash
git rebase -i HEAD~3
# error: could not apply abc1234... Fix validation

# 1. Risolvi conflitti
git status
# On branch feature
# You are currently rebasing branch 'feature' on 'a1b2c3d'.
#   (fix conflicts and run "git rebase --continue")

# 2. Identifica files in conflitto
git diff --name-only --diff-filter=U

# 3. Risolvi manualmente
vim conflicted-file.js

# 4. Aggiungi e continua
git add conflicted-file.js
git rebase --continue
```

### Recovery da Rebase Danneggiato

```bash
# Se il rebase va storto...

# 1. Controlla il reflog
git reflog
a1b2c3d HEAD@{0}: rebase -i (finish): returning to refs/heads/feature
e4f5g6h HEAD@{1}: rebase -i (pick): Add validation
h7i8j9k HEAD@{2}: rebase -i (start): checkout main
l1m2n3o HEAD@{3}: commit: Original working state

# 2. Ripristina stato precedente
git reset --hard HEAD@{3}

# 3. Ricrea backup prima del retry
git branch backup-$(date +%Y%m%d-%H%M%S)
```

### Debug Interactive Rebase

```bash
#!/bin/bash
# rebase-debug.sh

echo "🔍 Stato attuale del rebase:"
if [ -d ".git/rebase-merge" ]; then
    echo "📍 Rebase in corso"
    echo "Current commit: $(cat .git/rebase-merge/stopped-sha)"
    echo "Next commit: $(cat .git/rebase-merge/onto)"
    echo "Steps remaining: $(wc -l < .git/rebase-merge/git-rebase-todo)"
    
    echo "\n📋 TODO rimanente:"
    cat .git/rebase-merge/git-rebase-todo | head -5
else
    echo "✅ Nessun rebase in corso"
fi

echo "\n📊 Cronologia recente:"
git log --oneline --graph -10
```

## 🎯 Best Practices Interactive Rebase

### ✅ Pratiche Consigliate

1. **Backup sempre**: `git branch backup-before-rebase`
2. **Commit logici**: Un commit = una modifica concettuale
3. **Messaggi chiari**: Descrizioni che spiegano il "perché"
4. **Test ogni commit**: Ogni commit dovrebbe passare i test
5. **Rebase frequente**: Mantieni branch aggiornati

### ❌ Errori da Evitare

1. **Rebase su commit pubblici**: Mai modificare cronologia condivisa
2. **Commit troppo grandi**: Difficili da gestire e rivedere
3. **Messaggi vaghi**: "Fix stuff" non è informativo
4. **Squash eccessivo**: Non eliminare informazioni utili
5. **Ignorare i test**: Commit rotti nella cronologia

## 🎨 Workflow Completo di Cleanup

### Pre-Merge Cleanup

```bash
#!/bin/bash
# pre-merge-cleanup.sh

FEATURE_BRANCH=$(git branch --show-current)
MAIN_BRANCH="main"

echo "🧹 Cleanup del branch $FEATURE_BRANCH prima del merge"

# 1. Backup
BACKUP="backup-$FEATURE_BRANCH-$(date +%Y%m%d-%H%M%S)"
git branch "$BACKUP"
echo "💾 Backup creato: $BACKUP"

# 2. Analisi commit
echo "📊 Analisi commit correnti:"
git log --oneline "$MAIN_BRANCH..$FEATURE_BRANCH"

# 3. Identifica commit da sistemare
FIXUP_COMMITS=$(git log --oneline --grep="fixup\|wip\|temp" "$MAIN_BRANCH..$FEATURE_BRANCH" | wc -l)
echo "⚠️ Trovati $FIXUP_COMMITS commit da sistemare"

# 4. Conta commit totali
TOTAL_COMMITS=$(git rev-list --count "$MAIN_BRANCH..$FEATURE_BRANCH")
echo "📝 Totale commit da rivedere: $TOTAL_COMMITS"

# 5. Suggerimenti
if [ "$FIXUP_COMMITS" -gt 0 ]; then
    echo "💡 Suggerimento: Usa squash/fixup per combinare i commit temporanei"
fi

if [ "$TOTAL_COMMITS" -gt 10 ]; then
    echo "💡 Suggerimento: Considera di dividere in commit più piccoli"
fi

# 6. Avvia rebase interattivo
echo "🔄 Avviando interactive rebase..."
echo "💭 Ricorda: pick -> reword -> edit -> squash -> fixup -> drop"

git rebase -i "$MAIN_BRANCH"

# 7. Verifica post-rebase
if [ $? -eq 0 ]; then
    echo "✅ Rebase completato!"
    echo "🧪 Esegui test: npm test"
    echo "🗑️ Rimuovi backup: git branch -D $BACKUP"
else
    echo "❌ Problemi durante rebase"
    echo "🔄 Risolvi conflitti e usa: git rebase --continue"
fi
```

### Template di Commit Perfetto

```bash
# Crea template per commit messages
git config commit.template ~/.gitmessage

# File ~/.gitmessage:
cat > ~/.gitmessage << 'EOF'
# Tipo(scope): Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento (wrap a 72 caratteri)
# Spiega COSA è cambiato e PERCHÉ, non come.
#
# - Utilizzare presente imperativo: "Add" non "Added" o "Adds"
# - Non capitalizzare la prima lettera dopo il tipo
# - Non aggiungere punto finale alla descrizione breve
#
# Tipi validi:
# feat:     Nuova funzionalità
# fix:      Correzione di bug
# docs:     Solo documentazione
# style:    Formatazione, spazi bianchi
# refactor: Refactoring senza cambi funzionali
# test:     Aggiunta o correzione test
# chore:    Manutenzione, build, configurazione
#
# Esempi:
# feat(auth): add password reset functionality
# fix(api): handle null response in user endpoint  
# docs(readme): update installation instructions
EOF
```

## 📊 Metriche e Analisi

### Analisi Pre-Rebase

```bash
#!/bin/bash
# analyze-commits.sh

MAIN_BRANCH="main"
FEATURE_BRANCH=$(git branch --show-current)

echo "📊 ANALISI COMMIT - $FEATURE_BRANCH"
echo "=================================="

# Commit count
COMMIT_COUNT=$(git rev-list --count "$MAIN_BRANCH..$FEATURE_BRANCH")
echo "📝 Total commits: $COMMIT_COUNT"

# File changes
FILES_CHANGED=$(git diff --name-only "$MAIN_BRANCH..$FEATURE_BRANCH" | wc -l)
echo "📁 Files changed: $FILES_CHANGED"

# Lines changed
STATS=$(git diff --stat "$MAIN_BRANCH..$FEATURE_BRANCH" | tail -1)
echo "📈 Changes: $STATS"

# Commit size analysis
echo -e "\n📏 COMMIT SIZE ANALYSIS:"
git log --pretty=format:"%h %s" "$MAIN_BRANCH..$FEATURE_BRANCH" | while read hash message; do
    lines=$(git show --stat "$hash" | tail -1 | awk '{print $4}')
    printf "%-8s %-50s %s\n" "$hash" "${message:0:50}" "$lines"
done

# Message quality check
echo -e "\n🔍 MESSAGE QUALITY CHECK:"
git log --pretty=format:"%s" "$MAIN_BRANCH..$FEATURE_BRANCH" | while read message; do
    length=${#message}
    if [ $length -gt 50 ]; then
        echo "⚠️  Too long: $message"
    elif [ $length -lt 10 ]; then
        echo "⚠️  Too short: $message"
    elif echo "$message" | grep -q "^[A-Z]"; then
        echo "⚠️  Should not start with capital: $message"
    elif echo "$message" | grep -q "\.$"; then
        echo "⚠️  Should not end with period: $message"
    fi
done
```

## 🎓 Quiz Avanzato

### Domanda 1
**Quale comando permette di dividere un commit durante interactive rebase?**

a) `split abc1234`
b) `edit abc1234` seguito da `git reset HEAD~1` ✅
c) `divide abc1234`
d) `break abc1234`

**Spiegazione**: Utilizzando `edit`, il rebase si ferma permettendo di resettare il commit e ricommittare in parti separate.

### Domanda 2
**Qual è la differenza tra `squash` e `fixup`?**

a) Squash elimina il commit, fixup lo mantiene
b) Squash mantiene entrambi i messaggi, fixup solo il primo ✅
c) Non c'è differenza
d) Fixup elimina entrambi i messaggi

**Spiegazione**: `squash` combina i messaggi di commit, `fixup` mantiene solo il messaggio del commit precedente.

### Domanda 3
**Quando è sicuro modificare commit con rebase interattivo?**

a) Su qualsiasi branch
b) Solo su commit non ancora pushati ✅
c) Solo su branch main
d) Mai

**Spiegazione**: È sicuro modificare solo commit che non sono stati condivisi con altri sviluppatori.

## 🛠️ Tool e Utilities

### Git Aliases per Interactive Rebase

```bash
# Aggiungi al file ~/.gitconfig
[alias]
    ri = rebase -i
    rc = rebase --continue
    ra = rebase --abort
    rs = rebase --skip
    
    # Interactive rebase degli ultimi N commit
    rib = "!f() { git rebase -i HEAD~${1:-5}; }; f"
    
    # Rebase con auto-squash
    rif = rebase -i --autosquash
    
    # Pretty log per identificare commit da riorganizzare
    logi = log --oneline --graph --decorate -20
    
    # Trova commit "problematici"
    fixups = log --oneline --grep="fixup\\|wip\\|temp\\|TODO"
```

### Script di Automazione

```bash
#!/bin/bash
# smart-interactive-rebase.sh

FEATURE_BRANCH=$(git branch --show-current)
MAIN_BRANCH="main"

# Funzione per identificare commit candidati per squash
identify_squash_candidates() {
    echo "🔍 Identificando commit da sistemare..."
    
    # Cerca pattern comuni
    git log --oneline "$MAIN_BRANCH..$FEATURE_BRANCH" --grep="fixup\|wip\|temp\|typo\|fix\s" --perl-regexp
}

# Funzione per generare script di rebase automatico
generate_rebase_script() {
    local commit_count=$1
    local temp_file="/tmp/rebase-script-$(date +%s)"
    
    echo "📝 Generando script di rebase..."
    
    git log --reverse --pretty=format:"%H %s" "$MAIN_BRANCH~$commit_count..$FEATURE_BRANCH" | while read hash message; do
        if echo "$message" | grep -E "(fixup|wip|temp)" > /dev/null; then
            echo "fixup $hash $message"
        elif echo "$message" | grep -E "(typo|fix\s)" > /dev/null; then
            echo "fixup $hash $message"
        else
            echo "pick $hash $message"
        fi
    done > "$temp_file"
    
    echo "📄 Script generato: $temp_file"
    cat "$temp_file"
}

# Main execution
echo "🎯 Smart Interactive Rebase per $FEATURE_BRANCH"

# Analisi preliminare
COMMIT_COUNT=$(git rev-list --count "$MAIN_BRANCH..$FEATURE_BRANCH")
echo "📊 Commit da analizzare: $COMMIT_COUNT"

if [ "$COMMIT_COUNT" -eq 0 ]; then
    echo "✅ Nessun commit da riorganizzare"
    exit 0
fi

# Identifica candidati
identify_squash_candidates

echo -e "\n🤖 Vuoi generare uno script automatico? (y/n)"
read response

if [ "$response" = "y" ]; then
    generate_rebase_script "$COMMIT_COUNT"
    echo -e "\n🔄 Procedere con rebase interattivo? (y/n)"
    read rebase_response
    
    if [ "$rebase_response" = "y" ]; then
        git rebase -i "$MAIN_BRANCH"
    fi
else
    echo "🔄 Avviando rebase interattivo manuale..."
    git rebase -i "$MAIN_BRANCH"
fi
```

---

## 🔄 Navigazione

**Precedente**: [01 - Rebase Fundamentals](./01-rebase-fundamentals.md)  
**Successivo**: [03 - Cherry-Pick Guide](./03-cherry-pick-guide.md)  
**Indice**: [README del modulo](../README.md)
