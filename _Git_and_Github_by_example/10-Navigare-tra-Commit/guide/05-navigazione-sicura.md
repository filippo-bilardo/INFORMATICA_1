# 05 - Navigazione Sicura in Git

## 📖 Introduzione

La navigazione sicura in Git non è solo una best practice, ma una necessità per mantenere l'integrità del repository e prevenire perdite di dati. Questa guida ti insegnerà strategie e pattern per esplorare la cronologia Git in modo sicuro ed efficace.

## 🎯 Obiettivi

Al termine di questa guida sarai in grado di:

- ✅ Implementare strategie di navigazione sicura
- ✅ Utilizzare checkpoint e backup temporanei
- ✅ Gestire navigazioni complesse senza rischi
- ✅ Implementare workflow di esplorazione strutturati
- ✅ Recuperare da situazioni problematiche
- ✅ Automatizzare procedure di sicurezza

## 📋 Prerequisiti

- **Comprensione di HEAD e detached HEAD**
- **Familiarità con git stash e git reflog**
- **Conoscenza base di branch e commit**
- **Esperienza con navigazione Git**

## ⏱️ Durata Stimata

**45-60 minuti** (teoria + esercitazioni pratiche)

---

## 🛡️ Principi di Navigazione Sicura

### 1. La Regola del "Checkpoint"

Prima di ogni esplorazione complessa, crea sempre un punto di ritorno sicuro:

```bash
# Checkpoint attuale
git tag checkpoint-$(date +%Y%m%d-%H%M%S)

# Oppure branch temporaneo
git branch backup-exploration
```

### 2. Verifica dello Stato Pulito

Mai navigare con modifiche non committate:

```bash
# Verifica stato
git status

# Se ci sono modifiche
git stash push -m "Navigazione temporanea $(date)"
# oppure
git add . && git commit -m "WIP: checkpoint per navigazione"
```

### 3. Documentazione del Percorso

Mantieni traccia della tua navigazione:

```bash
# Script per logging automatico
echo "$(date): Navigando a $(git rev-parse HEAD)" >> .git/navigation.log
```

---

## 🚦 Workflow di Navigazione Sicura

### Pattern 1: Esplorazione Semplice

```bash
# 1. Checkpoint
git stash push -m "Prima di navigazione"
git branch temp-checkpoint

# 2. Naviga
git checkout <target-commit>

# 3. Esplora (read-only)
git log --oneline -10
git show HEAD
ls -la

# 4. Ritorna
git switch -
git stash pop
git branch -d temp-checkpoint
```

### Pattern 2: Esplorazione con Test

```bash
#!/bin/bash
# safe-explore.sh

# Funzione di esplorazione sicura
safe_explore() {
    local target=$1
    local current_branch=$(git branch --show-current)
    
    # Salva stato
    git stash push -m "Safe exploration backup"
    
    # Naviga
    git checkout "$target"
    
    # Test automatico (se disponibile)
    if [ -f "test.sh" ]; then
        echo "Eseguendo test su commit $target..."
        ./test.sh
    fi
    
    # Prompt per azioni
    echo "Premi ENTER per tornare a $current_branch"
    read
    
    # Ritorna
    git switch "$current_branch"
    git stash pop
}

# Uso
safe_explore HEAD~5
```

### Pattern 3: Esplorazione Multi-Commit

```bash
# Script per esplorare una serie di commit
explore_range() {
    local start=$1
    local end=$2
    
    git log --oneline "$start..$end" | while read hash message; do
        echo "=== Esplorando: $hash - $message ==="
        git checkout "$hash"
        
        # Qui le tue analisi
        echo "File modificati:"
        git show --name-only "$hash"
        
        echo "Statistiche:"
        git show --stat "$hash"
        
        echo "Continua? (y/n)"
        read answer
        [ "$answer" != "y" ] && break
    done
    
    git switch -
}
```

---

## 🔧 Strumenti di Sicurezza

### 1. Alias Sicuri

Configura alias che includono controlli di sicurezza:

```bash
# Checkout sicuro
git config alias.safe-checkout '!f() { 
    if [ -n "$(git status --porcelain)" ]; then 
        echo "Repository non pulito. Commit o stash prima."; 
        exit 1; 
    fi; 
    git checkout "$1"; 
}; f'

# Navigazione con backup
git config alias.nav '!f() { 
    git stash push -m "Nav backup $(date)"; 
    git checkout "$1"; 
    echo "Per tornare: git switch - && git stash pop"; 
}; f'

# Switch sicuro con verifica
git config alias.safe-switch '!f() { 
    if git diff --quiet; then 
        git switch "$1"; 
    else 
        echo "Ci sono modifiche non committate"; 
        git status --short; 
    fi; 
}; f'
```

### 2. Hook di Sicurezza

Crea hook per prevenire azioni pericolose:

```bash
# .git/hooks/pre-checkout
#!/bin/bash

# Previeni checkout accidentale con modifiche
if [ -n "$(git status --porcelain)" ]; then
    echo "ATTENZIONE: Repository non pulito!"
    echo "Modifiche da committare o fare stash:"
    git status --short
    echo ""
    echo "Vuoi continuare? (y/N)"
    read answer
    [ "$answer" != "y" ] && exit 1
fi

# Log della navigazione
echo "$(date): Checkout da $(git rev-parse HEAD) a $3" >> .git/navigation.log
```

### 3. Script di Recupero

Prepara script per situazioni di emergenza:

```bash
#!/bin/bash
# git-rescue.sh

echo "=== Git Rescue Tool ==="
echo "1. Mostra reflog"
echo "2. Trova commit orfani"
echo "3. Ripristina HEAD precedente"
echo "4. Lista branch locali"
echo "5. Torna a main/master"

read -p "Scegli opzione: " choice

case $choice in
    1) git reflog --oneline -20 ;;
    2) git fsck --unreachable ;;
    3) 
        echo "HEAD precedenti:"
        git reflog -5
        read -p "Scegli HEAD@{n}: " ref
        git reset --hard "$ref"
        ;;
    4) git branch -v ;;
    5) 
        git switch main 2>/dev/null || git switch master 2>/dev/null || echo "Nessun branch main/master"
        ;;
esac
```

---

## ⚠️ Situazioni Pericolose e Soluzioni

### 1. Commit in Detached HEAD

**Problema**: Hai fatto commit in detached HEAD

**Soluzione Sicura**:
```bash
# Salva il commit
git branch temp-commit

# Torna al branch originale
git switch main

# Decidi cosa fare
git log --oneline temp-commit  # Vedi il commit
git merge temp-commit          # Includi nel branch
# oppure
git cherry-pick temp-commit    # Applica solo il commit

# Pulisci
git branch -d temp-commit
```

### 2. Navigazione Persa

**Problema**: Non ricordi dove eri

**Soluzione**:
```bash
# Vedi cronologia completa
git reflog

# Trova l'ultimo branch
git reflog | grep "checkout: moving from" | head -1

# Torna indietro di N passi
git checkout HEAD@{3}  # 3 azioni fa
```

### 3. Repository "Rotto"

**Problema**: Stato inconsistente

**Soluzione**:
```bash
# Reset sicuro
git status  # Vedi cosa c'è
git stash   # Salva modifiche
git reset --hard HEAD  # Reset completo
git clean -fd  # Rimuovi file non tracciati

# Verifica integrità
git fsck --full
```

---

## 🔄 Pattern Avanzati

### 1. Esplorazione con Context Switching

```bash
# Funzione per mantenere contesto
git_explore_with_context() {
    local target=$1
    local current=$(git rev-parse HEAD)
    local branch=$(git branch --show-current)
    
    # Salva contesto completo
    echo "Branch: $branch" > .git/explore-context
    echo "Commit: $current" >> .git/explore-context
    echo "Stash: $(git stash list | wc -l)" >> .git/explore-context
    
    # Stash se necessario
    [ -n "$(git status --porcelain)" ] && git stash push -m "Explore context"
    
    # Naviga
    git checkout "$target"
    
    echo "Esplorazione attiva. Per tornare: git_restore_context"
}

git_restore_context() {
    if [ -f .git/explore-context ]; then
        source .git/explore-context
        git switch "$branch"
        [ "$(git stash list | wc -l)" -gt "$stash" ] && git stash pop
        rm .git/explore-context
    fi
}
```

### 2. Navigazione con Breadcrumb

```bash
# Sistema di breadcrumb per navigazione complessa
git_breadcrumb_start() {
    echo "$(git rev-parse HEAD)" > .git/breadcrumb
    echo "Breadcrumb iniziato da $(git branch --show-current)"
}

git_breadcrumb_add() {
    echo "$(git rev-parse HEAD)" >> .git/breadcrumb
    echo "Aggiunto breadcrumb: $(git log --oneline -1)"
}

git_breadcrumb_back() {
    if [ -f .git/breadcrumb ]; then
        local last=$(tail -1 .git/breadcrumb)
        git checkout "$last"
        sed -i '$d' .git/breadcrumb  # Rimuovi ultimo
    fi
}

git_breadcrumb_home() {
    if [ -f .git/breadcrumb ]; then
        local first=$(head -1 .git/breadcrumb)
        git checkout "$first"
        rm .git/breadcrumb
    fi
}
```

---

## 📊 Monitoraggio e Logging

### Sistema di Logging Avanzato

```bash
# .gitconfig
[alias]
    nav-log = "!f() { 
        echo \"$(date '+%Y-%m-%d %H:%M:%S') - FROM: $(git rev-parse HEAD) TO: $1 BY: $(git config user.name)\" >> .git/navigation.log; 
        git checkout \"$1\"; 
    }; f"
    
    nav-history = "!cat .git/navigation.log | tail -20"
    nav-stats = "!echo \"Navigazioni oggi: $(grep $(date +%Y-%m-%d) .git/navigation.log | wc -l)\""
```

### Dashboard di Sicurezza

```bash
#!/bin/bash
# git-safety-dashboard.sh

echo "=== Git Safety Dashboard ==="
echo ""

# Stato generale
echo "📊 STATO GENERALE"
echo "Branch corrente: $(git branch --show-current)"
echo "Commit corrente: $(git log --oneline -1)"
echo "File modificati: $(git status --porcelain | wc -l)"
echo ""

# Sicurezza
echo "🛡️ SICUREZZA"
echo "Stash disponibili: $(git stash list | wc -l)"
echo "Branch di backup: $(git branch | grep -c backup || echo "0")"
echo "Tag di checkpoint: $(git tag | grep -c checkpoint || echo "0")"
echo ""

# Cronologia navigazione
echo "🗺️ NAVIGAZIONE RECENTE"
if [ -f .git/navigation.log ]; then
    echo "Ultime 5 navigazioni:"
    tail -5 .git/navigation.log
else
    echo "Nessuna cronologia disponibile"
fi
echo ""

# Reflog
echo "📝 REFLOG (ultimi 5)"
git reflog --oneline -5
echo ""

# Suggerimenti
echo "💡 SUGGERIMENTI"
[ "$(git status --porcelain | wc -l)" -gt 0 ] && echo "⚠️  Ci sono modifiche non committate"
[ "$(git stash list | wc -l)" -eq 0 ] && echo "💾 Considera di creare uno stash di backup"
[ ! -f .git/navigation.log ] && echo "📊 Attiva il logging di navigazione"
```

---

## 🧪 Laboratorio Pratico

### Esercizio 1: Navigazione Sicura Guidata

```bash
# 1. Setup ambiente sicuro
git stash push -m "Lab navigazione sicura"
git tag lab-start

# 2. Naviga a commit precedente
git checkout HEAD~3

# 3. Esplora senza modificare
git log --oneline -5
git show --stat HEAD

# 4. Prova una modifica (pericolosa!)
echo "test" > temp-file.txt

# 5. Risolvi la situazione
git status
# NON fare git add/commit in detached HEAD!

# 6. Ritorna pulitamente
rm temp-file.txt
git switch -
git stash pop
git tag -d lab-start
```

### Esercizio 2: Recupero da Situazione Problematica

```bash
# Simula problema
git checkout HEAD~5
echo "Modifica pericolosa" > important-file.txt
git add important-file.txt
git commit -m "Commit in detached HEAD - PROBLEMA!"

# Ora recupera...
# (Vedi soluzioni nei pattern sopra)
```

---

## 🎯 Quiz di Verifica

### Domande Teoriche

1. **Qual è la prima cosa da fare prima di una navigazione complessa?**
   - a) Controllare git log
   - b) Creare un checkpoint (stash/tag/branch)
   - c) Verificare git status
   - d) Fare git fetch

2. **Cosa fare se ti trovi in detached HEAD con modifiche importanti?**
   - a) git reset --hard HEAD
   - b) Creare un branch dal commit corrente
   - c) git switch - immediatamente
   - d) git merge main

3. **Quale comando mostra la cronologia di navigazione?**
   - a) git log
   - b) git show
   - c) git reflog
   - d) git status

### Soluzioni Quiz
1. **b** - Creare sempre un punto di ritorno sicuro
2. **b** - git branch new-branch per salvare il lavoro
3. **c** - git reflog mostra tutta la cronologia di HEAD

---

## 🔗 Riferimenti

### Comandi Sicuri Essenziali
- `git stash push -m "descrizione"` - Backup temporaneo
- `git tag checkpoint-<nome>` - Checkpoint permanente  
- `git reflog` - Cronologia completa
- `git switch -` - Torna al branch precedente
- `git branch temp-<nome>` - Branch temporaneo

### Documentazione Ufficiale
- [Git Checkout Safety](https://git-scm.com/docs/git-checkout#_detached_head)
- [Git Reflog](https://git-scm.com/docs/git-reflog)
- [Git Stash](https://git-scm.com/docs/git-stash)

---

## 🔄 Navigazione

- [⬅️ 04 - Riferimenti e Hash](./04-riferimenti-hash.md)
- [🏠 Modulo 09](../README.md)
- [📑 Indice Corso](../../README.md)
- [➡️ Esempi Pratici](../esempi/01-esplorazione-base.md)

---

**Prossimo argomento**: [Esempi Pratici di Navigazione](../esempi/01-esplorazione-base.md) - Applicazioni pratiche dei concetti di navigazione sicura
