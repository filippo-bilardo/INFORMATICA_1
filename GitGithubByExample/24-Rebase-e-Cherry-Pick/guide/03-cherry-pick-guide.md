# Cherry-Pick Guide

## 📖 Introduzione al Cherry-Pick

Il cherry-pick è un comando Git che permette di applicare selettivamente commit specifici da un branch all'altro senza dover fare merge dell'intero branch. È come "raccogliere" una ciliegia (commit) da un albero (branch) e metterla in un altro cesto (branch di destinazione).

## 🎯 Cosa Imparerai

- Concetti fondamentali del cherry-pick
- Sintassi e opzioni avanzate del comando
- Scenari di utilizzo pratico e strategico
- Gestione di conflitti durante cherry-pick
- Cherry-pick multipli e batch operations
- Integrazione con workflow aziendali
- Best practices per evitare problemi

## 🍒 Concetto di Cherry-Pick

### Visualizzazione del Processo

```
Branch Feature:    A---B---C---D---E
                              /
                             /  (cherry-pick C)
                            /
Branch Main:       1---2---3---C'---4
```

Cherry-pick crea un **nuovo commit** (C') con lo stesso contenuto di C ma un hash diverso.

### Differenza con Altri Comandi

| Comando | Cosa fa | Quando usare |
|---------|---------|--------------|
| **merge** | Unisce interi branch | Integrare feature complete |
| **rebase** | Riposiziona serie di commit | Aggiornare branch feature |
| **cherry-pick** | Copia commit specifici | Applicare fix selettivi |

## 📋 Sintassi e Comandi Base

### Cherry-Pick Semplice

```bash
# Cherry-pick di un singolo commit
git cherry-pick <commit-hash>

# Cherry-pick con messaggio personalizzato
git cherry-pick -e <commit-hash>

# Cherry-pick senza committare automaticamente
git cherry-pick -n <commit-hash>

# Cherry-pick da branch specifico
git cherry-pick feature-branch~2
```

### Cherry-Pick Multipli

```bash
# Cherry-pick di un range di commit
git cherry-pick A..B

# Cherry-pick di commit specifici
git cherry-pick commit1 commit2 commit3

# Cherry-pick escludendo commit specifici
git cherry-pick A..B --skip=<excluded-commit>
```

### Opzioni Avanzate

```bash
# Mantieni l'autore originale
git cherry-pick -x <commit-hash>

# Cherry-pick con strategia di merge
git cherry-pick -X theirs <commit-hash>
git cherry-pick -X ours <commit-hash>

# Cherry-pick da mainline in caso di merge commit
git cherry-pick -m 1 <merge-commit>

# Continua dopo risoluzione conflitti
git cherry-pick --continue

# Abbandona il cherry-pick
git cherry-pick --abort

# Salta commit problematico
git cherry-pick --skip
```

## 🎯 Scenari di Utilizzo Pratico

### 1. Hotfix su Produzione

```bash
# Scenario: Bug critico fixato su develop, serve su main
git checkout main
git cherry-pick develop~3  # Il commit con il fix

# Risultato: Fix applicato a main senza merge di develop
```

### 2. Backport di Feature

```bash
# Feature implementata su v2.0, serve anche su v1.5
git checkout release/v1.5
git cherry-pick feature/new-validation~1  # Solo il commit core

# Adatta il fix alla versione precedente
```

### 3. Selezione da Merge Request

```bash
# PR con 10 commit, serve solo 1 specifico
git fetch origin pull/123/head:temp-pr
git cherry-pick temp-pr~5  # Solo il commit interessante
git branch -D temp-pr
```

## 🔄 Workflow Enterprise con Cherry-Pick

### Hotfix Workflow

```bash
#!/bin/bash
# hotfix-workflow.sh

HOTFIX_COMMIT=$1
TARGET_BRANCHES=("main" "release/v2.1" "release/v2.0")

if [ -z "$HOTFIX_COMMIT" ]; then
    echo "❌ Specifica il commit del hotfix"
    echo "Usage: $0 <commit-hash>"
    exit 1
fi

echo "🚨 Applicando hotfix $HOTFIX_COMMIT a tutti i branch di release"

for branch in "${TARGET_BRANCHES[@]}"; do
    echo "🔄 Cherry-pick su $branch"
    
    git checkout "$branch" || {
        echo "❌ Impossibile passare a $branch"
        continue
    }
    
    git pull origin "$branch" || {
        echo "❌ Impossibile aggiornare $branch"
        continue
    }
    
    if git cherry-pick "$HOTFIX_COMMIT"; then
        echo "✅ Cherry-pick completato su $branch"
        
        # Push automatico solo se specificato
        if [ "$AUTO_PUSH" = "true" ]; then
            git push origin "$branch"
            echo "📤 Push completato per $branch"
        fi
    else
        echo "❌ Conflitti su $branch - risoluzione manuale necessaria"
        echo "🛠️ Risolvi i conflitti e usa: git cherry-pick --continue"
        break
    fi
done

echo "🎯 Hotfix workflow completato"
```

### Release Cherry-Pick Manager

```bash
#!/bin/bash
# release-cherry-pick.sh

SOURCE_BRANCH="develop"
TARGET_BRANCH="release/v2.1"
COMMITS_FILE="/tmp/cherry-pick-list.txt"

# Funzione per identificare commit da cherry-pick
identify_commits() {
    echo "🔍 Identificando commit per release..."
    
    # Cerca commit con etichette specifiche
    git log --oneline --grep="release:" --grep="fix:" --grep="feat:" \
        "$TARGET_BRANCH..$SOURCE_BRANCH" > "$COMMITS_FILE"
    
    echo "📋 Commit candidati salvati in $COMMITS_FILE"
    cat "$COMMITS_FILE"
}

# Funzione per review interattiva
interactive_review() {
    echo "📝 Review interattiva dei commit..."
    
    while read line; do
        commit_hash=$(echo "$line" | awk '{print $1}')
        commit_msg=$(echo "$line" | cut -d' ' -f2-)
        
        echo "🔍 Commit: $commit_hash"
        echo "📄 Messaggio: $commit_msg"
        git show --stat "$commit_hash"
        
        echo "❓ Include questo commit? (y/n/s=show diff/q=quit)"
        read decision
        
        case "$decision" in
            y|Y) 
                echo "$commit_hash" >> "/tmp/approved-commits.txt"
                echo "✅ Approvato"
                ;;
            s|S)
                git show "$commit_hash"
                echo "❓ Include dopo aver visto il diff? (y/n)"
                read final_decision
                if [ "$final_decision" = "y" ]; then
                    echo "$commit_hash" >> "/tmp/approved-commits.txt"
                    echo "✅ Approvato"
                fi
                ;;
            q|Q)
                echo "🛑 Review interrotta"
                break
                ;;
            *)
                echo "❌ Rifiutato"
                ;;
        esac
        echo "---"
    done < "$COMMITS_FILE"
}

# Funzione per eseguire cherry-pick batch
execute_cherry_picks() {
    if [ ! -f "/tmp/approved-commits.txt" ]; then
        echo "❌ Nessun commit approvato"
        return 1
    fi
    
    echo "🍒 Eseguendo cherry-pick dei commit approvati..."
    
    git checkout "$TARGET_BRANCH"
    git pull origin "$TARGET_BRANCH"
    
    while read commit_hash; do
        echo "🔄 Cherry-pick di $commit_hash"
        if git cherry-pick "$commit_hash"; then
            echo "✅ Successo: $commit_hash"
        else
            echo "❌ Conflitto in $commit_hash"
            echo "🛠️ Risolvi manualmente e premi ENTER per continuare"
            read
            git cherry-pick --continue
        fi
    done < "/tmp/approved-commits.txt"
    
    echo "🎯 Cherry-pick batch completato"
    
    # Cleanup
    rm -f "/tmp/approved-commits.txt" "/tmp/cherry-pick-list.txt"
}

# Main workflow
echo "🚀 Release Cherry-Pick Manager"
echo "Source: $SOURCE_BRANCH → Target: $TARGET_BRANCH"

identify_commits
interactive_review
execute_cherry_picks
```

## 🐛 Gestione Conflitti Avanzata

### Conflitti Standard

```bash
# Cherry-pick con conflitto
git cherry-pick abc1234
# error: could not apply abc1234... Fix validation bug
# hint: after resolving the conflicts, mark the corrected paths
# hint: with 'git add <paths>' or 'git rm <paths>'
# hint: and commit the result with 'git commit'

# 1. Identifica file in conflitto
git status --porcelain | grep "^UU"

# 2. Risolvi conflitti
git diff --name-only --diff-filter=U | xargs vim

# 3. Continua cherry-pick
git add .
git cherry-pick --continue
```

### Risoluzione Automatizzata

```bash
#!/bin/bash
# auto-resolve-cherry-pick.sh

resolve_conflicts() {
    local strategy=$1  # "ours" o "theirs"
    
    echo "🔧 Risoluzione automatica con strategia: $strategy"
    
    # Ottieni lista file in conflitto
    conflicted_files=$(git diff --name-only --diff-filter=U)
    
    for file in $conflicted_files; do
        echo "🛠️ Risolvendo: $file"
        
        case "$strategy" in
            "ours")
                git checkout --ours "$file"
                ;;
            "theirs")
                git checkout --theirs "$file"
                ;;
            "merge")
                # Usa tool di merge automatico
                git mergetool --no-prompt "$file"
                ;;
        esac
        
        git add "$file"
    done
    
    echo "✅ Conflitti risolti, continuando cherry-pick..."
    git cherry-pick --continue
}

# Verifica se siamo in un cherry-pick
if [ -f ".git/CHERRY_PICK_HEAD" ]; then
    echo "🍒 Cherry-pick in corso con conflitti"
    echo "Strategia di risoluzione:"
    echo "1) ours - mantieni versione corrente"
    echo "2) theirs - usa versione del commit"
    echo "3) merge - usa tool di merge"
    read -p "Scegli strategia (1/2/3): " choice
    
    case "$choice" in
        1) resolve_conflicts "ours" ;;
        2) resolve_conflicts "theirs" ;;
        3) resolve_conflicts "merge" ;;
        *) echo "❌ Strategia non valida" ;;
    esac
else
    echo "❌ Nessun cherry-pick in corso"
fi
```

## 📊 Cherry-Pick Analytics

### Analisi Pre-Cherry-Pick

```bash
#!/bin/bash
# cherry-pick-analyzer.sh

analyze_commit() {
    local commit_hash=$1
    local target_branch=$2
    
    echo "🔍 ANALISI COMMIT: $commit_hash"
    echo "================================="
    
    # Informazioni base
    echo "📝 Messaggio:"
    git log -1 --pretty=format:"%s" "$commit_hash"
    echo -e "\n"
    
    echo "👤 Autore: $(git log -1 --pretty=format:"%an <%ae>" "$commit_hash")"
    echo "📅 Data: $(git log -1 --pretty=format:"%ad" "$commit_hash")"
    
    # Analisi modifiche
    echo -e "\n📊 STATISTICHE MODIFICHE:"
    git show --stat "$commit_hash"
    
    # File modificati
    echo -e "\n📁 FILE INTERESSATI:"
    git show --name-only --pretty=format:"" "$commit_hash" | grep -v "^$"
    
    # Analisi dipendenze
    echo -e "\n🔗 ANALISI DIPENDENZE:"
    local files_changed=$(git show --name-only --pretty=format:"" "$commit_hash")
    
    for file in $files_changed; do
        # Verifica se il file esiste nel target branch
        if git show "$target_branch:$file" >/dev/null 2>&1; then
            echo "✅ $file - esiste nel target"
        else
            echo "❌ $file - NON esiste nel target (possibili conflitti)"
        fi
    done
    
    # Predizione conflitti
    echo -e "\n⚠️ PREDIZIONE CONFLITTI:"
    if git merge-tree "$(git merge-base "$commit_hash" "$target_branch")" "$commit_hash" "$target_branch" | grep -q "<<<<<<< "; then
        echo "🔥 ATTENZIONE: Conflitti probabili"
    else
        echo "✅ Nessun conflitto previsto"
    fi
}

# Analisi batch
analyze_batch() {
    local commits_file=$1
    local target_branch=$2
    
    echo "📊 ANALISI BATCH CHERRY-PICK"
    echo "Target branch: $target_branch"
    echo "============================="
    
    while read commit_hash; do
        analyze_commit "$commit_hash" "$target_branch"
        echo -e "\n" | head -3
    done < "$commits_file"
}

# Uso dello script
if [ $# -eq 2 ]; then
    analyze_commit "$1" "$2"
elif [ $# -eq 1 ] && [ -f "$1" ]; then
    TARGET_BRANCH=$(git branch --show-current)
    analyze_batch "$1" "$TARGET_BRANCH"
else
    echo "Usage: $0 <commit-hash> <target-branch>"
    echo "   or: $0 <commits-file>"
fi
```

## 🛡️ Cherry-Pick Sicuro

### Validazione Pre-Cherry-Pick

```bash
#!/bin/bash
# safe-cherry-pick.sh

safe_cherry_pick() {
    local commit_hash=$1
    local target_branch=${2:-$(git branch --show-current)}
    
    echo "🛡️ CHERRY-PICK SICURO"
    echo "Commit: $commit_hash"
    echo "Target: $target_branch"
    echo "====================="
    
    # 1. Validazioni preliminari
    echo "1️⃣ Validazioni preliminari..."
    
    # Verifica che il commit esista
    if ! git cat-file -e "$commit_hash" 2>/dev/null; then
        echo "❌ Commit $commit_hash non trovato"
        return 1
    fi
    
    # Verifica che il target branch esista
    if ! git show-ref --verify --quiet "refs/heads/$target_branch"; then
        echo "❌ Branch $target_branch non trovato"
        return 1
    fi
    
    # Verifica working directory pulita
    if ! git diff-index --quiet HEAD --; then
        echo "❌ Working directory non pulita"
        echo "💡 Commit o stash le modifiche prima del cherry-pick"
        return 1
    fi
    
    echo "✅ Validazioni preliminari completate"
    
    # 2. Backup
    echo "2️⃣ Creazione backup..."
    local backup_branch="backup-$(date +%Y%m%d-%H%M%S)"
    git branch "$backup_branch"
    echo "💾 Backup creato: $backup_branch"
    
    # 3. Analisi pre-cherry-pick
    echo "3️⃣ Analisi commit..."
    local commit_msg=$(git log -1 --pretty=format:"%s" "$commit_hash")
    local files_count=$(git show --name-only --pretty=format:"" "$commit_hash" | wc -l)
    echo "📝 Messaggio: $commit_msg"
    echo "📁 File modificati: $files_count"
    
    # 4. Test di compatibilità
    echo "4️⃣ Test di compatibilità..."
    if command -v git-merge-tree >/dev/null 2>&1; then
        local base=$(git merge-base "$commit_hash" "$target_branch")
        if git merge-tree "$base" "$commit_hash" "$target_branch" | grep -q "<<<<<<< "; then
            echo "⚠️ ATTENZIONE: Conflitti previsti"
            echo "❓ Continuare comunque? (y/n)"
            read confirm
            [ "$confirm" != "y" ] && return 1
        else
            echo "✅ Nessun conflitto previsto"
        fi
    fi
    
    # 5. Esecuzione cherry-pick
    echo "5️⃣ Esecuzione cherry-pick..."
    if git cherry-pick "$commit_hash"; then
        echo "✅ Cherry-pick completato con successo!"
        
        # 6. Validazione post-cherry-pick
        echo "6️⃣ Validazione post-cherry-pick..."
        
        # Verifica che i test passino (se presenti)
        if [ -f "package.json" ] && grep -q "\"test\"" package.json; then
            echo "🧪 Esecuzione test..."
            if npm test; then
                echo "✅ Test passati"
            else
                echo "❌ Test falliti"
                echo "❓ Vuoi mantenere il cherry-pick? (y/n)"
                read keep_changes
                if [ "$keep_changes" != "y" ]; then
                    git reset --hard HEAD~1
                    echo "🔄 Cherry-pick annullato"
                    return 1
                fi
            fi
        fi
        
        echo "🗑️ Rimuovi backup con: git branch -D $backup_branch"
        return 0
    else
        echo "❌ Cherry-pick fallito"
        echo "🛠️ Risolvi i conflitti manualmente"
        echo "📝 Comandi utili:"
        echo "   git status               # Vedi conflitti"
        echo "   git cherry-pick --continue   # Continua dopo risoluzione"
        echo "   git cherry-pick --abort      # Annulla cherry-pick"
        echo "   git reset --hard $backup_branch  # Ripristina backup"
        return 1
    fi
}

# Esecuzione
if [ $# -eq 0 ]; then
    echo "Usage: $0 <commit-hash> [target-branch]"
    exit 1
fi

safe_cherry_pick "$1" "$2"
```

## 🎯 Best Practices

### ✅ Pratiche Consigliate

1. **Backup sempre**: Crea branch di backup prima di operazioni complesse
2. **Cherry-pick atomici**: Preferisci commit singoli e ben definiti
3. **Messaggi descrittivi**: Usa `-x` per tracciare l'origine del commit
4. **Test dopo cherry-pick**: Verifica che tutto funzioni correttamente
5. **Documentazione**: Tieni traccia di quali commit sono stati cherry-picked

### ❌ Errori da Evitare

1. **Cherry-pick di merge commit**: Può causare duplicazioni
2. **Cherry-pick su branch pubblici**: Modifica la cronologia condivisa
3. **Cherry-pick di commit dipendenti**: Può rompere la funzionalità
4. **Ignorare i conflitti**: Risoluzione frettolosa può introdurre bug
5. **Cherry-pick massivo**: Preferisci merge per grandi set di commit

### 📋 Checklist Pre-Cherry-Pick

```bash
# Checklist per cherry-pick sicuro
echo "🔍 CHECKLIST PRE-CHERRY-PICK"
echo "=============================="

echo "☐ Working directory pulita?"
git status --porcelain | wc -l

echo "☐ Branch target aggiornato?"
git log --oneline HEAD..origin/$(git branch --show-current) | wc -l

echo "☐ Commit esiste e è accessibile?"
git cat-file -e "$1" && echo "✅" || echo "❌"

echo "☐ Backup creato?"
git branch | grep backup | wc -l

echo "☐ Test disponibili?"
[ -f "package.json" ] && grep -q "test" package.json && echo "✅" || echo "❌"

echo "☐ Commit è atomico?"
git show --stat "$1" | tail -1
```

## 🎓 Quiz di Verifica

### Domanda 1
**Quale opzione mantiene un riferimento al commit originale durante cherry-pick?**

a) `git cherry-pick -r <commit>`
b) `git cherry-pick -x <commit>` ✅
c) `git cherry-pick -o <commit>`
d) `git cherry-pick --original <commit>`

**Spiegazione**: L'opzione `-x` aggiunge una riga nel messaggio di commit che identifica il commit originale.

### Domanda 2
**Quando è appropriato usare cherry-pick invece di merge?**

a) Per integrare un intero branch feature
b) Per applicare hotfix specifici a branch diversi ✅
c) Per aggiornare un branch con le ultime modifiche
d) Per combinare più branch simultaneamente

**Spiegazione**: Cherry-pick è ideale per applicare modifiche specifiche senza portare l'intera cronologia del branch.

### Domanda 3
**Cosa fa `git cherry-pick -n <commit>`?**

a) Crea un nuovo branch
b) Applica le modifiche senza committare automaticamente ✅
c) Annulla il cherry-pick
d) Risolve automaticamente i conflitti

**Spiegazione**: L'opzione `-n` (--no-commit) applica le modifiche al working directory senza creare il commit.

## 🔧 Tool e Utilities

### Git Aliases per Cherry-Pick

```bash
# Aggiungi al file ~/.gitconfig
[alias]
    cp = cherry-pick
    cpc = cherry-pick --continue
    cpa = cherry-pick --abort
    cps = cherry-pick --skip
    cpn = cherry-pick --no-commit
    cpx = cherry-pick -x
    
    # Cherry-pick con editing del messaggio
    cpe = cherry-pick -e
    
    # Cherry-pick range
    cpr = "!f() { git cherry-pick $1..$2; }; f"
    
    # Lista commit disponibili per cherry-pick
    cplist = "!f() { git log --oneline ${1:-main}..${2:-HEAD}; }; f"
    
    # Cherry-pick interattivo
    cpi = "!f() { git log --oneline $1..$2 | fzf | cut -d' ' -f1 | xargs git cherry-pick; }; f"
```

### Script di Utilità

```bash
#!/bin/bash
# cherry-pick-manager.sh

# Menu interattivo per operazioni cherry-pick
echo "🍒 CHERRY-PICK MANAGER"
echo "====================="
echo "1) Cherry-pick singolo commit"
echo "2) Cherry-pick range di commit"
echo "3) Cherry-pick interattivo"
echo "4) Analizza commit per cherry-pick"
echo "5) Cherry-pick sicuro con backup"
echo "6) Esci"

read -p "Scegli opzione (1-6): " choice

case $choice in
    1) 
        read -p "Hash del commit: " commit_hash
        git cherry-pick "$commit_hash"
        ;;
    2)
        read -p "Commit iniziale: " start_commit
        read -p "Commit finale: " end_commit
        git cherry-pick "$start_commit..$end_commit"
        ;;
    3)
        # Richiede fzf installato
        git log --oneline | fzf | cut -d' ' -f1 | xargs git cherry-pick
        ;;
    4)
        read -p "Hash del commit da analizzare: " commit_hash
        ./cherry-pick-analyzer.sh "$commit_hash" "$(git branch --show-current)"
        ;;
    5)
        read -p "Hash del commit: " commit_hash
        ./safe-cherry-pick.sh "$commit_hash"
        ;;
    6)
        echo "👋 Arrivederci!"
        exit 0
        ;;
    *)
        echo "❌ Opzione non valida"
        ;;
esac
```

---

## 🔄 Navigazione

**Precedente**: [02 - Interactive Rebase](./02-interactive-rebase.md)  
**Successivo**: [04 - Rebase vs Merge](./04-rebase-vs-merge.md)  
**Indice**: [README del modulo](../README.md)
