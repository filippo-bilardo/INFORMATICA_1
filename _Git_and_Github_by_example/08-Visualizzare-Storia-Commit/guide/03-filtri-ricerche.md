# Filtri e Ricerche

## 📖 Navigazione Intelligente nella Cronologia

La capacità di filtrare e cercare nella cronologia Git è essenziale per trovare rapidamente commit specifici, identificare bug, analizzare contributi e comprendere l'evoluzione del progetto.

## 🔍 Filtri per Autore e Committer

### Ricerca per Autore
```bash
# Commit di un autore specifico
git log --author="Mario Rossi"

# Ricerca parziale (case-insensitive)
git log --author="mario"

# Ricerca con regex
git log --author="mario|luigi"

# Escludere autore specifico
git log --author="^(?!.*Mario Rossi).*$"
```

### Utilizzo dell'Email
```bash
# Ricerca per email completa
git log --author="mario.rossi@email.com"

# Ricerca per dominio
git log --author="@company.com"

# Ricerca per pattern email
git log --author=".*@gmail\.com"
```

### Differenza Autore vs Committer
```bash
# Chi ha scritto il codice
git log --author="Mario Rossi"

# Chi ha committato nel repository
git log --committer="Luigi Verdi"

# Entrambi (quando diversi)
git log --author="Mario" --committer="Luigi"
```

## 📅 Filtri Temporali

### Intervalli di Date
```bash
# Dopo una data specifica
git log --since="2024-01-01"
git log --after="2024-01-01"

# Prima di una data specifica
git log --until="2024-12-31"
git log --before="2024-12-31"

# Intervallo specifico
git log --since="2024-01-01" --until="2024-01-31"
```

### Formati Data Flessibili
```bash
# Date relative
git log --since="2 weeks ago"
git log --since="1 month ago"
git log --since="yesterday"
git log --since="1 year ago"

# Date specifiche
git log --since="January 1, 2024"
git log --since="2024-01-15 14:30"
git log --since="last Monday"

# Combinazioni
git log --since="3 days ago" --until="yesterday"
```

### Filtri per Orario
```bash
# Commit in un giorno specifico
git log --since="2024-01-15 00:00" --until="2024-01-15 23:59"

# Commit nelle ultime ore
git log --since="6 hours ago"

# Commit della settimana lavorativa
git log --since="last Monday" --until="last Friday"
```

## 💬 Ricerca nei Messaggi

### Ricerca Base nei Messaggi
```bash
# Ricerca semplice nel messaggio
git log --grep="bug fix"

# Ricerca case-insensitive
git log --grep="BUG" --regexp-ignore-case

# Ricerca con regex
git log --grep="fix.*login"
```

### Ricerca Avanzata
```bash
# Messaggi che contengono parole specifiche
git log --grep="feature" --grep="login" --all-match

# Messaggi che contengono UNA delle parole (OR)
git log --grep="bug\|fix\|hotfix"

# Escludere commit con certe parole
git log --grep="^(?!.*WIP).*$"
```

### Combinare Ricerche
```bash
# Autore E messaggio
git log --author="Mario" --grep="login"

# In un intervallo di tempo E con messaggio
git log --since="1 week ago" --grep="fix"
```

## 📁 Filtri per File e Directory

### Cronologia di File Specifici
```bash
# Cronologia di un file
git log -- filename.js

# Cronologia di più file
git log -- file1.js file2.js

# Cronologia di una directory
git log -- src/auth/

# Seguire il file anche attraverso rinominazioni
git log --follow -- oldname.js
```

### Pattern e Glob
```bash
# Tutti i file JavaScript
git log -- "*.js"

# File in sottodirectory
git log -- "src/**/*.js"

# Escludere file di test
git log -- "*.js" ":!*test*"

# Solo file specifici modificati
git log --name-only -- "*.css"
```

### Filtri per Tipo di Modifica
```bash
# Solo commit che aggiungono file
git log --diff-filter=A

# Solo commit che modificano file
git log --diff-filter=M

# Solo commit che eliminano file
git log --diff-filter=D

# Combinazioni
git log --diff-filter=AM -- "*.js"
```

## 🔧 Filtri per Contenuto

### Ricerca nel Contenuto delle Modifiche
```bash
# Cercare nel contenuto delle modifiche (pickaxe)
git log -S"function login"

# Ricerca regex nel contenuto
git log -G"def.*login"

# Mostrare le modifiche trovate
git log -S"login" -p
```

### Ricerca di Linee Specifiche
```bash
# Quando una linea è stata aggiunta/rimossa
git log -S"console.log" --source --all

# Combinare con file specifici
git log -S"password" -- "*.js"

# Con contesto delle modifiche
git log -S"validate" -p --all
```

## 🌳 Filtri per Branch e Merge

### Cronologia di Branch Specifici
```bash
# Solo commit di un branch
git log main
git log feature/login

# Commit in un branch ma non in un altro
git log feature/login ^main
git log main..feature/login

# Commit raggiungibili da più branch
git log main feature/login

# Tutti i branch
git log --all
```

### Filtri per Merge
```bash
# Solo merge commit
git log --merges

# Escludere merge commit
git log --no-merges

# Merge in un periodo specifico
git log --merges --since="1 month ago"

# Primo parent di merge (branch principale)
git log --first-parent
```

### Filtri per Range di Commit
```bash
# Tra due commit
git log commit1..commit2

# Tutto tranne un range
git log ^commit1 commit2

# Triple dot (symmetric difference)
git log commit1...commit2

# Dall'ultimo tag
git log v1.0..HEAD
```

## 🎯 Combinazioni Pratiche

### 1. Debug e Bug Hunting
```bash
# Cercare quando è stato introdotto un bug
git log -S"broken_function" --since="1 month ago" -p

# Modifiche recenti di un team member
git log --author="Mario" --since="1 week ago" --stat

# Commit di hotfix recenti
git log --grep="hotfix\|urgent" --since="2 weeks ago"
```

### 2. Analisi delle Prestazioni
```bash
# Commit che modificano file di performance
git log -S"performance" -G"optimize" -- "*.js"

# Grosse modifiche recenti
git log --since="1 month ago" --shortstat | grep -E "(insertion|deletion)"

# Frequenza di commit per autore
git log --since="3 months ago" --format="%an" | sort | uniq -c | sort -nr
```

### 3. Code Review e Audit
```bash
# Commit non ancora in produzione
git log production..main --oneline

# Modifiche a file critici
git log --since="1 month ago" -- "config/*" "security/*"

# Commit senza code review (esempio)
git log --grep="^(?!.*review).*$" --since="1 week ago"
```

### 4. Preparazione Release
```bash
# Nuove feature dall'ultimo rilascio
git log v1.0..HEAD --grep="feat\|feature" --oneline

# Bug fix dall'ultimo rilascio
git log v1.0..HEAD --grep="fix\|bug" --oneline

# Contributori della release
git log v1.0..HEAD --format="%an <%ae>" | sort | uniq
```

## 📊 Combinare Filtri per Analisi Avanzate

### Query Complesse
```bash
# Commit di Mario negli ultimi 30 giorni che modificano file JS
git log --author="Mario" --since="30 days ago" --name-only -- "*.js"

# Bug fix dell'ultimo mese escludendo merge
git log --grep="fix" --since="1 month ago" --no-merges --oneline

# Modifiche a file di configurazione da parte del team DevOps
git log --author="devops" --since="3 months ago" -- "config/" "deploy/" "*.yml"
```

### Statistiche e Reporting
```bash
# Commit per giorno della settimana
git log --format="%ad" --date=format:"%A" | sort | uniq -c

# Attività per mese
git log --format="%ad" --date=format:"%Y-%m" | sort | uniq -c

# File più modificati
git log --name-only --since="6 months ago" | grep -v "^$" | sort | uniq -c | sort -nr | head -10
```

## ⚡ Ottimizzazione delle Ricerche

### Performance Tips
```bash
# Limitare la profondità di ricerca
git log --max-count=100 --grep="pattern"

# Usare filtri temporali per limitare lo scope
git log --since="1 year ago" -S"search_term"

# Combinare filtri per restringere i risultati
git log --author="name" --since="1 month ago" -- "specific/path/"
```

### Cache e Indicizzazione
```bash
# Per repository grandi, considera di usare git-grep per contenuti
git grep "search_term" $(git rev-list --all)

# O tools esterni per ricerche complesse
git log --grep="pattern" --all --source
```

## 🧪 Quiz di Verifica

### Domanda 1
Come cercare commit che contengono "login" nel messaggio degli ultimi 30 giorni?
- A) `git log --grep="login" --since="30 days ago"`
- B) `git log --message="login" --after="1 month"`
- C) `git log --search="login" --date="30 days"`
- D) `git log --find="login" --recent`

<details>
<summary>Risposta</summary>
**A) `git log --grep="login" --since="30 days ago"`**

`--grep` cerca nei messaggi di commit e `--since` filtra per data.
</details>

### Domanda 2
Quale comando mostra solo commit che hanno modificato file JavaScript?
- A) `git log --files="*.js"`
- B) `git log -- "*.js"`
- C) `git log --path="*.js"`
- D) `git log --include="*.js"`

<details>
<summary>Risposta</summary>
**B) `git log -- "*.js"`**

La sintassi `-- <pathspec>` filtra i commit per i file specificati.
</details>

### Domanda 3
Come vedere commit di un autore escludendo i merge commit?
- A) `git log --author="name" --no-merge`
- B) `git log --author="name" --no-merges`
- C) `git log --author="name" --exclude-merges`
- D) `git log --author="name" --skip-merges`

<details>
<summary>Risposta</summary>
**B) `git log --author="name" --no-merges`**

`--no-merges` esclude i commit di merge dalla cronologia.
</details>

## 🚀 Esempi Avanzati

### Script per Analisi Repository
```bash
#!/bin/bash
# Analisi attività repository

echo "=== TOP 10 CONTRIBUTORI ==="
git log --format="%an" | sort | uniq -c | sort -nr | head -10

echo -e "\n=== COMMIT PER MESE (ULTIMI 12) ==="
git log --since="12 months ago" --format="%ad" --date=format:"%Y-%m" | sort | uniq -c

echo -e "\n=== FILE PIÙ MODIFICATI ==="
git log --name-only --since="6 months ago" | grep -v "^$" | sort | uniq -c | sort -nr | head -10

echo -e "\n=== BUG FIX RECENTI ==="
git log --grep="fix\|bug" --since="1 month ago" --oneline
```

## 🔄 Prossimi Passi

Dopo aver appreso filtri e ricerche, puoi:
1. **Utilizzare git show** per analisi dettagliate dei commit trovati
2. **Creare alias** per le tue ricerche più frequenti
3. **Combinare con strumenti grafici** per visualizzazioni complesse
4. **Automatizzare** le ricerche con script

---

**Continua con**: [04-Git-Show-Dettagli](./04-git-show-dettagli.md) - Analizzare commit specifici
