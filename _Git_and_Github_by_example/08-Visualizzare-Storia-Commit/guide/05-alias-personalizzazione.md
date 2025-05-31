# Alias e Personalizzazione

## 📖 Ottimizzare il Workflow Git

Gli alias Git permettono di creare comandi personalizzati per semplificare e velocizzare le operazioni più comuni. Una buona configurazione di alias può trasformare radicalmente la tua produttività con Git.

## 🚀 Configurazione degli Alias

### Sintassi Base
```bash
# Configurazione globale (consigliata)
git config --global alias.<nome-alias> "<comando-git>"

# Configurazione locale (solo repository corrente)
git config alias.<nome-alias> "<comando-git>"

# Visualizzare alias esistenti
git config --global --get-regexp alias
```

### Esempi Base
```bash
# Alias semplici
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit

# Utilizzo
git st        # invece di git status
git co main   # invece di git checkout main
git br        # invece di git branch
git ci -m "fix" # invece di git commit -m "fix"
```

## 🎯 Alias per Git Log

### Log Compatti e Grafici
```bash
# Log compatto con grafico
git config --global alias.lg "log --oneline --graph --decorate"

# Log dettagliato con grafico
git config --global alias.lga "log --graph --pretty=format:'%C(red)%h%C(reset) -%C(yellow)%d%C(reset) %s %C(green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --all"

# Log con statistiche
git config --global alias.ls "log --stat --oneline"

# Log ultimi 10 commit
git config --global alias.l10 "log --oneline -10"
```

### Log Specializzati
```bash
# Cronologia di un file con follow
git config --global alias.filelog "log --follow --patch --"

# Log di oggi
git config --global alias.today "log --since='1 day ago' --oneline --author='\$(git config user.name)'"

# Log della settimana
git config --global alias.week "log --since='1 week ago' --oneline --author='\$(git config user.name)'"

# Contributori con conteggio commit
git config --global alias.who "log --pretty=format:'%an' | sort | uniq -c | sort -nr"
```

### Format Personalizzati Avanzati
```bash
# Log stile GitHub
git config --global alias.gh "log --graph --pretty=format:'%C(bold yellow)%h%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset) %C(green)(%cr)%C(reset)%C(auto)%d%C(reset)'"

# Log per release notes
git config --global alias.relnotes "log --pretty=format:'- %s (%h)' --reverse"

# Log con hash completo e date
git config --global alias.detail "log --pretty=format:'%C(yellow)%H%C(reset)%n%C(bold)%s%C(reset)%n%C(blue)Author: %an <%ae>%C(reset)%n%C(green)Date: %ad%C(reset)%n' --date=short"
```

## 🔧 Alias per Git Show

### Show Personalizzati
```bash
# Show con statistiche
git config --global alias.details "show --stat --summary"

# Show solo file modificati
git config --global alias.files "show --name-only"

# Show con patch compatta
git config --global alias.patch "show --pretty=short"

# Show ultimo commit
git config --global alias.last "show --stat HEAD"
```

### Analisi Commit
```bash
# Mostra info commit senza diff
git config --global alias.info "show --no-patch --pretty=format:'%C(yellow)Commit:%C(reset) %H%n%C(yellow)Author:%C(reset) %an <%ae>%n%C(yellow)Date:%C(reset) %ad%n%C(yellow)Subject:%C(reset) %s%n'"

# Mostra commit con contesto
git config --global alias.context "show -U10"
```

## 🔍 Alias per Ricerche e Filtri

### Ricerche Comuni
```bash
# Cerca nei messaggi di commit
git config --global alias.find "log --grep"

# Cerca nel contenuto
git config --global alias.search "log -S"

# Commit di un autore
git config --global alias.by "log --author"

# Commit dell'ultimo mese
git config --global alias.recent "log --since='1 month ago' --oneline"
```

### Filtri Specifici
```bash
# Solo merge commit
git config --global alias.merges "log --merges --oneline"

# Escludere merge commit
git config --global alias.nomerges "log --no-merges --oneline"

# Commit non ancora pushati
git config --global alias.unpushed "log @{u}..HEAD --oneline"

# Commit da pullare
git config --global alias.unpulled "log HEAD..@{u} --oneline"
```

## 🎨 Alias Colorati e Formattatati

### Template Colorati Completi
```bash
# Log multilinea colorato
git config --global alias.ll "log --graph --pretty=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --abbrev-commit --all"

# Log con date complete
git config --global alias.ld "log --graph --pretty=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(bold yellow)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)' --all"

# Log compatto con tutto
git config --global alias.lo "log --oneline --graph --decorate --color=always"
```

### Alias per Debugging
```bash
# Log con path di file
git config --global alias.logp "log --oneline --name-status"

# Log con diff stat
git config --global alias.logstat "log --oneline --stat"

# Log con full diff
git config --global alias.logpatch "log --patch"
```

## 🛠️ Alias per Workflow

### Status e Diff Migliorati
```bash
# Status compatto
git config --global alias.s "status -sb"

# Diff staged
git config --global alias.ds "diff --staged"

# Diff con word-diff
git config --global alias.dw "diff --word-diff"

# Diff tra branch
git config --global alias.db "diff"
```

### Branch e Navigation
```bash
# Lista branch con ultimo commit
git config --global alias.brl "branch -v"

# Branch remoti
git config --global alias.brr "branch -r"

# Branch tutti
git config --global alias.bra "branch -a"

# Switch al branch precedente
git config --global alias.back "checkout -"
```

### Operazioni Comuni
```bash
# Add tutto e commit
git config --global alias.ac "!git add -A && git commit"

# Commit con messaggio rapido
git config --global alias.cm "commit -m"

# Amend rapido
git config --global alias.amend "commit --amend --no-edit"

# Push corrente branch
git config --global alias.pushup "push -u origin HEAD"
```

## 📊 Alias per Analisi e Statistiche

### Statistiche Repository
```bash
# Conteggio commit per autore
git config --global alias.count "!git log --pretty=format:'%an' | sort | uniq -c | sort -nr"

# Statistiche globali
git config --global alias.stats "!git log --stat --oneline | head -20"

# File più modificati
git config --global alias.hot "!git log --name-only --pretty=format: | grep -v '^$' | sort | uniq -c | sort -nr | head -10"
```

### Analisi Temporali
```bash
# Attività per giorno
git config --global alias.daily "log --since='1 day ago' --oneline --author='\$(git config user.name)'"

# Attività settimanale
git config --global alias.weekly "log --since='1 week ago' --pretty=format:'%ad %s' --date=short"

# Commit per mese
git config --global alias.monthly "!git log --pretty=format:'%ad' --date=format:'%Y-%m' | sort | uniq -c"
```

## 🎯 Alias Avanzati con Script

### Alias che Eseguono Script
```bash
# Alias con comandi shell
git config --global alias.ignore "!gi() { curl -L -s https://www.gitignore.io/api/\$@ ;}; gi"

# Alias per cleanup
git config --global alias.cleanup "!git branch --merged | grep -v '\\*\\|main\\|master\\|develop' | xargs -n 1 git branch -d"

# Alias per sync con upstream
git config --global alias.sync "!git checkout main && git pull upstream main && git push origin main"
```

### Alias Interattivi
```bash
# Log interattivo con fzf (se installato)
git config --global alias.flog "!git log --oneline --color=always | fzf --ansi --preview 'git show --color=always {+1}' | cut -d' ' -f1 | xargs git show"

# Checkout interattivo
git config --global alias.fco "!git branch -a | grep -v HEAD | fzf | sed 's/remotes\\/origin\\///g' | xargs git checkout"
```

## 🔧 Configurazione File .gitconfig

### Sezione [alias] Completa
```ini
# File ~/.gitconfig
[alias]
    # Comandi base abbreviati
    st = status -sb
    co = checkout
    br = branch
    ci = commit
    
    # Log migliorati
    lg = log --oneline --graph --decorate
    ll = log --graph --pretty=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --abbrev-commit --all
    
    # Show personalizzati
    last = show --stat HEAD
    details = show --stat --summary
    
    # Ricerche
    find = log --grep
    by = log --author
    
    # Workflow
    ac = !git add -A && git commit
    amend = commit --amend --no-edit
    pushup = push -u origin HEAD
    
    # Analisi
    count = !git log --pretty=format:'%an' | sort | uniq -c | sort -nr
    hot = !git log --name-only --pretty=format: | grep -v '^$' | sort | uniq -c | sort -nr | head -10
```

## 🧪 Testing e Debugging Alias

### Verificare Alias
```bash
# Vedere definizione di un alias
git config --global alias.lg

# Testare alias con dry-run (dove possibile)
git lg --dry-run

# Vedere tutti gli alias
git config --global --get-regexp alias
```

### Debugging Alias Complessi
```bash
# Aggiungere debug agli alias shell
git config --global alias.debug-cleanup "!set -x; git branch --merged | grep -v '\\*\\|main\\|master\\|develop' | xargs -n 1 git branch -d"
```

## 📱 Alias per Diversi Contesti

### Sviluppo Locale
```bash
git config --global alias.wip "commit -am 'WIP: work in progress'"
git config --global alias.unwip "reset HEAD~1"
git config --global alias.save "!git add -A && git commit -m 'SAVEPOINT'"
```

### Collaborazione
```bash
git config --global alias.up "pull --rebase --autostash"
git config --global alias.pub "!git push -u origin \$(git branch --show-current)"
git config --global alias.done "!git checkout main && git pull && git branch -d @{-1}"
```

### Release Management
```bash
git config --global alias.release "!git checkout main && git pull && git tag"
git config --global alias.hotfix "!git checkout main && git pull && git checkout -b hotfix/"
```

## 🧪 Quiz di Verifica

### Domanda 1
Come creare un alias globale chiamato "lg" per "log --oneline --graph"?
- A) `git alias lg "log --oneline --graph"`
- B) `git config alias.lg "log --oneline --graph"`
- C) `git config --global alias.lg "log --oneline --graph"`
- D) `git set-alias lg "log --oneline --graph"`

<details>
<summary>Risposta</summary>
**C) `git config --global alias.lg "log --oneline --graph"`**

La sintassi corretta usa `git config --global alias.<nome>` per alias globali.
</details>

### Domanda 2
Quale simbolo si usa negli alias per eseguire comandi shell?
- A) `$`
- B) `!`
- C) `&`
- D) `#`

<details>
<summary>Risposta</summary>
**B) `!`**

Il punto esclamativo `!` all'inizio di un alias indica che deve essere eseguito come comando shell.
</details>

### Domanda 3
Come vedere tutti gli alias configurati globalmente?
- A) `git alias --list`
- B) `git config --list | grep alias`
- C) `git config --global --get-regexp alias`
- D) Tutte le precedenti

<details>
<summary>Risposta</summary>
**C) `git config --global --get-regexp alias`**

Questo comando mostra specificamente tutti gli alias globali configurati.
</details>

## 🚀 Best Practices

### Principi per Alias Efficaci
1. **Brevità**: Mantieni gli alias corti ma memorabili
2. **Consistenza**: Usa convenzioni di naming coerenti
3. **Sicurezza**: Evita alias che potrebbero sovrascrivere comandi critici
4. **Documentazione**: Commenta alias complessi

### Alias da Evitare
```bash
# NON fare questi alias pericolosi
git config --global alias.rm "reset --hard HEAD"  # Troppo distruttivo
git config --global alias.push "push --force"     # Pericoloso per il team
git config --global alias.clean "clean -fd"       # Può eliminare file importanti
```

## 🔄 Prossimi Passi

Dopo aver configurato i tuoi alias, puoi:
1. **Esplorare strumenti grafici** per visualizzazioni avanzate
2. **Integrare** con editor e IDE
3. **Condividere** configurazioni con il team
4. **Automatizzare** ulteriormente con script

---

**Continua con**: [06-Strumenti-Grafici](./06-strumenti-grafici.md) - GUI e strumenti visuali per Git
