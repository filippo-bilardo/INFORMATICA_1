# 04 - Git Log e Cronologia

## 📖 Spiegazione Concettuale

`git log` è il comando per **esplorare la cronologia** del repository. Ti permette di vedere tutti i commit, capire l'evoluzione del progetto, trovare quando sono stati introdotti bug o funzionalità, e navigare nella storia del codice.

### Perché è Importante?

La cronologia Git è una risorsa fondamentale per:
- **Debug**: Trovare quando è stato introdotto un bug
- **Documentazione**: Capire l'evoluzione delle funzionalità
- **Collaborazione**: Vedere contributi del team
- **Audit**: Tracciare modifiche per compliance
- **Rollback**: Identificare punti di restore sicuri

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git log
```

### Opzioni di Visualizzazione

#### 1. Formati di Output
```bash
# Log compatto (una riga per commit)
git log --oneline

# Log con grafico ASCII
git log --graph

# Log decorato (mostra branch e tag)
git log --decorate

# Combinazione comune
git log --oneline --graph --decorate
```

#### 2. Informazioni Dettagliate
```bash
# Mostra file modificati
git log --stat

# Mostra differenze complete
git log -p

# Mostra solo nomi file
git log --name-only

# Mostra status modifiche
git log --name-status
```

#### 3. Filtri Temporali
```bash
# Ultimi N commit
git log -3
git log -n 5

# Da una data specifica
git log --since="2025-05-01"
git log --after="2 weeks ago"

# Fino a una data
git log --until="2025-05-29"
git log --before="yesterday"

# Range temporale
git log --since="1 month ago" --until="1 week ago"
```

## 🎯 Esempi Pratici

### Scenario 1: Esplorazione Base
```bash
# Cronologia completa
$ git log

commit a1b2c3d4e5f6789012345678901234567890abcd
Author: Mario Rossi <mario@email.com>
Date:   Wed May 29 10:30:00 2025 +0200

    feat: implement user authentication system
    
    - Add login/logout functionality
    - Implement session management
    - Add password validation
    
commit b2c3d4e5f6789012345678901234567890abcdef
Author: Luigi Verdi <luigi@email.com>
Date:   Tue May 28 15:45:00 2025 +0200

    fix: resolve navigation menu bug on mobile
```

### Scenario 2: Log Compatto per Overview
```bash
$ git log --oneline -10

a1b2c3d feat: implement user authentication system
b2c3d4e fix: resolve navigation menu bug on mobile
c3d4e5f docs: update API documentation
d4e5f6g refactor: optimize database queries
e5f6g7h test: add unit tests for user service
f6g7h8i style: format code with prettier
g7h8i9j feat: add email notification system
h8i9j0k fix: resolve memory leak in image processor
i9j0k1l chore: update dependencies to latest versions
j0k1l2m feat: implement dashboard analytics
```

### Scenario 3: Analisi con Statistiche
```bash
$ git log --stat -3

commit a1b2c3d feat: implement user authentication system
 src/auth/login.js      |  45 +++++++++++++++++++++++++++++
 src/auth/session.js    |  32 ++++++++++++++++++++
 src/utils/validation.js|  28 ++++++++++++++++
 tests/auth.test.js     |  67 +++++++++++++++++++++++++++++++++++++++
 4 files changed, 172 insertions(+)

commit b2c3d4e fix: resolve navigation menu bug on mobile
 src/components/nav.js  |  12 ++++--------
 src/styles/mobile.css  |   8 ++++++++
 2 files changed, 12 insertions(+), 8 deletions(-)
```

## 🎨 Formattazione Personalizzata

### Pretty Formats
```bash
# Format personalizzato
git log --pretty=format:"%h - %an, %ar : %s"

# Output:
# a1b2c3d - Mario Rossi, 2 hours ago : feat: implement user authentication
# b2c3d4e - Luigi Verdi, 1 day ago : fix: resolve navigation menu bug

# Formato con colori
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(green)%an%C(reset), %C(blue)%ar%C(reset) : %s"
```

### Format Placeholders Utili
- `%H` - Hash commit completo
- `%h` - Hash commit abbreviato
- `%an` - Nome autore
- `%ae` - Email autore
- `%ad` - Data autore
- `%ar` - Data autore relativa
- `%s` - Soggetto commit
- `%b` - Corpo messaggio

### Alias Utili
```bash
# Configura alias per log comuni
git config --global alias.lg "log --oneline --graph --decorate"
git config --global alias.lgs "log --stat --graph --decorate"
git config --global alias.lgp "log -p --graph --decorate"

# Ora puoi usare:
git lg
git lgs
git lgp
```

## 🔍 Filtri Avanzati

### 1. Filtri per Autore
```bash
# Commit di un autore specifico
git log --author="Mario Rossi"
git log --author="mario@email.com"

# Pattern matching
git log --author="Mario"  # Trova tutti i "Mario"
git log --grep="feat"     # Commit con "feat" nel messaggio
```

### 2. Filtri per File
```bash
# Cronologia di un file specifico
git log -- src/auth.js

# Cronologia di più file
git log -- src/auth.js src/utils.js

# File in una directory
git log -- src/components/
```

### 3. Filtri per Contenuto
```bash
# Commit che aggiungono/rimuovono una stringa
git log -S "function authenticate"

# Commit che modificano una stringa (più flessibile)
git log -G "authentication"

# Commit che toccano una funzione
git log -L :functionName:file.js
```

## 🎯 Casi d'Uso Pratici

### 1. Debug: Quando è Stato Introdotto un Bug?
```bash
# Trova commit recenti su file problematico
git log --oneline -- src/problem-file.js

# Cerca commit con parole chiave
git log --grep="validation" --grep="password" --oneline

# Analizza modifiche specifiche
git log -p -S "buggy function" -- src/file.js
```

### 2. Code Review: Chi Ha Fatto Cosa?
```bash
# Attività per autore nell'ultimo mese
git log --author="Mario" --since="1 month ago" --stat

# Tutti i contributor
git log --pretty=format:"%an" | sort | uniq -c | sort -nr

# Commit per giorno
git log --pretty=format:"%ad" --date=short | sort | uniq -c
```

### 3. Release Notes: Cosa È Cambiato?
```bash
# Modifiche tra tag
git log v1.0.0..v1.1.0 --oneline

# Modifiche dall'ultimo release
git log --since="2025-05-01" --pretty=format:"- %s (%an)"

# Raggruppare per tipo
git log --grep="feat" --oneline --since="1 month ago"
git log --grep="fix" --oneline --since="1 month ago"
```

## 🎨 Log Grafici e Visuali

### 1. Grafico ASCII
```bash
$ git log --graph --oneline --all

* a1b2c3d (HEAD -> main) feat: implement user auth
*   b2c3d4e Merge branch 'feature/navigation'
|\  
| * c3d4e5f feat: add mobile navigation
| * d4e5f6g style: improve navigation CSS
|/  
* e5f6g7h fix: resolve validation bug
* f6g7h8i Initial commit
```

### 2. Solo Branch Corrente vs Tutti
```bash
# Solo branch corrente
git log --oneline

# Tutti i branch
git log --oneline --all

# Solo branch remoti
git log --oneline --remotes
```

### 3. Visualizzazione Avanzata
```bash
# Log dettagliato con grafico
git log --graph --pretty=format:'%C(red)%h%C(reset) -%C(yellow)%d%C(reset) %s %C(green)(%cr) %C(blue)<%an>%C(reset)' --abbrev-commit --all
```

## 💡 Best Practices

### 1. Alias per Produttività
```bash
# Setup alias utili
git config --global alias.hist "log --oneline --graph --decorate"
git config --global alias.last "log -1 HEAD --stat"
git config --global alias.unstage "reset HEAD --"
```

### 2. Combinazioni Potenti
```bash
# Panoramica progetto
git log --oneline --graph --all --since="2 weeks ago"

# Debug specifico
git log -p --follow -- path/to/file.js

# Analisi performance
git log --stat --since="1 month ago" --author="$(git config user.name)"
```

### 3. Automatizzazione con Script
```bash
#!/bin/bash
# daily-report.sh - Report quotidiano delle modifiche

echo "=== Commit di oggi ==="
git log --since="midnight" --oneline --author="$(git config user.name)"

echo -e "\n=== File più modificati questa settimana ==="
git log --since="1 week ago" --name-only --pretty=format: | sort | uniq -c | sort -nr | head -10
```

## 🚨 Limitazioni e Considerazioni

### 1. Performance con Repository Grandi
```bash
# Limitare risultati per performance
git log -n 100  # Solo ultimi 100 commit
git log --since="3 months ago"  # Limitare temporalmente

# Evitare -p su grandi repository senza filtri
```

### 2. Merge Commits
```bash
# Saltare merge commit per cronologia lineare
git log --no-merges

# Solo merge commit
git log --merges

# Primo parent solo (cronologia principale)
git log --first-parent
```

## 🎓 Quiz di Verifica

1. **Come vedi solo i commit dell'ultimo mese?**
2. **Come trovi chi ha modificato una specifica riga di codice?**
3. **Come visualizzi un grafico della cronologia dei branch?**

### Risposte
1. `git log --since="1 month ago"`
2. `git log -L startline,endline:file` o `git blame file`
3. `git log --graph --oneline --all`

## 🔗 Comandi Correlati

- `git show` - Dettagli commit specifico
- `git blame` - Chi ha modificato ogni riga
- `git shortlog` - Riassunto per autore
- `git reflog` - Cronologia locale completa
- `gitk` - Visualizzatore grafico

## 📚 Risorse Aggiuntive

- [Git Log Documentation](https://git-scm.com/docs/git-log)
- [Pretty Formats](https://git-scm.com/docs/pretty-formats)
- [Git Aliases Guide](https://git-scm.com/book/en/v2/Git-Basics-Git-Aliases)

---

**Prossimo**: [05 - Git Diff e Differenze](./05-git-diff.md) - Analizzare le modifiche in dettaglio
