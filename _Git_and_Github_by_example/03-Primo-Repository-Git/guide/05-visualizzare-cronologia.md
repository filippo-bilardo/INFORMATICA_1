# 04 - Visualizzare Cronologia

## 📖 Spiegazione Concettuale

La **cronologia di Git** è una delle funzionalità più potenti del sistema. Git mantiene una traccia completa di ogni modifica, permettendo di navigare, analizzare e comprendere l'evoluzione del progetto nel tempo.

### Perché è Importante?

- **Debug**: Trovare quando è stato introdotto un bug
- **Auditing**: Vedere chi ha fatto cosa e quando
- **Rollback**: Identificare punti di ripristino sicuri
- **Comprensione**: Capire l'evoluzione del codice
- **Collaborazione**: Tracciare contributi del team

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git log
```

### Varianti Comuni
```bash
# Log compatto (una riga per commit)
git log --oneline

# Log con grafico dei branch
git log --graph

# Log con statistiche file
git log --stat

# Log degli ultimi N commit
git log -n 5

# Log in formato personalizzato
git log --pretty=format:"%h - %an: %s"
```

### Parametri Avanzati
```bash
# Log di un file specifico
git log filename.txt

# Log in un intervallo di date
git log --since="2024-01-01" --until="2024-01-31"

# Log di un autore specifico
git log --author="John Doe"

# Log con ricerca nel messaggio
git log --grep="fix"

# Log con modifiche (patch)
git log -p
```

## 🎯 Visualizzazioni Utili

### 1. **Log Standard**
```bash
git log
```
**Output:**
```
commit a1b2c3d4e5f6... (HEAD -> main)
Author: Mario Rossi <mario@email.com>
Date:   Mon Dec 18 14:30:22 2023 +0100

    feat: Add user authentication system
    
    - Implement login/logout functionality
    - Add password validation
    - Create user session management

commit f6e5d4c3b2a1...
Author: Luigi Verdi <luigi@email.com>
Date:   Sun Dec 17 09:15:10 2023 +0100

    fix: Resolve responsive layout issues
```

### 2. **Log Compatto**
```bash
git log --oneline
```
**Output:**
```
a1b2c3d feat: Add user authentication system
f6e5d4c fix: Resolve responsive layout issues
9e8d7c6 docs: Update installation guide
5b4a3f2 Initial commit: Add project foundation
```

### 3. **Log con Grafico**
```bash
git log --oneline --graph --all
```
**Output:**
```
* a1b2c3d (HEAD -> main) feat: Add user authentication
* f6e5d4c fix: Resolve responsive layout issues
*   9e8d7c6 Merge branch 'feature/docs'
|\  
| * 8c7b6a5 docs: Add API documentation
* | 5b4a3f2 feat: Improve error handling
|/  
* 3f2e1d0 Initial commit
```

### 4. **Log con Statistiche**
```bash
git log --stat
```
**Output:**
```
commit a1b2c3d4e5f6...
Author: Mario Rossi <mario@email.com>
Date:   Mon Dec 18 14:30:22 2023 +0100

    feat: Add user authentication system

 auth.js       | 45 +++++++++++++++++++++++++++++++++++++++++++++
 login.html    | 23 +++++++++++++++++++++++
 styles.css    |  8 ++++++++
 3 files changed, 76 insertions(+)
```

## 🧐 Formattazione Personalizzata

### Placeholder Utili
```bash
# Formato personalizzato
git log --pretty=format:"%h - %an (%ar): %s"
```

**Placeholder Comuni:**
- `%h`: Hash corto del commit
- `%H`: Hash completo del commit
- `%an`: Nome autore
- `%ae`: Email autore
- `%ad`: Data autore
- `%ar`: Data relativa (2 days ago)
- `%s`: Messaggio del commit
- `%b`: Body del messaggio

### Esempi di Formattazione
```bash
# Formato sviluppatore
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(blue)%an%C(reset) (%C(green)%ar%C(reset)): %s"

# Formato dettagliato
git log --pretty=format:"Commit: %H%nAuthor: %an <%ae>%nDate: %ad%nMessage: %s%n"

# Formato tabellare
git log --pretty=format:"%h|%an|%ad|%s" --date=short
```

## 🎯 Casi d'Uso Pratici

### 1. **Trovare Quando è Stato Introdotto un Bug**
```bash
# Cerca commit che menzionano "login"
git log --grep="login" --oneline

# Cerca modifiche a file specifico
git log -p auth.js

# Cerca in un intervallo di tempo
git log --since="1 week ago" --grep="bug"
```

### 2. **Analizzare Contributi del Team**
```bash
# Commit per autore
git log --author="Mario Rossi" --oneline

# Statistiche per autore
git shortlog -s -n

# Contributi nell'ultimo mese
git log --since="1 month ago" --pretty=format:"%an: %s" | sort
```

### 3. **Preparare Release Notes**
```bash
# Commit dalla versione precedente
git log v1.0.0..HEAD --oneline

# Solo feature e fix
git log --grep="feat\|fix" --oneline --since="2023-12-01"

# Con statistiche
git log v1.0.0..HEAD --stat --oneline
```

### 4. **Debug e Investigazione**
```bash
# Mostra modifiche specifiche
git show a1b2c3d

# Confronta due commit
git diff a1b2c3d..f6e5d4c

# Trova ultimo commit che ha modificato un file
git log -1 --oneline filename.txt
```

## ⚠️ Errori Comuni

### 1. **Log Troppo Verboso**
```bash
# ERRORE: Log standard troppo lungo
git log    # ❌ Output infinito in progetti grandi

# CORRETTO: Limita output
git log --oneline -10   # ✅ Ultimi 10 commit
git log --since="1 week ago"  # ✅ Solo recenti
```

### 2. **Non Usare Filtri**
```bash
# ERRORE: Cercare manualmente
git log | grep "user"  # ❌ Inefficiente

# CORRETTO: Usare filtri Git
git log --grep="user"  # ✅ Più efficiente
git log --author="name"  # ✅ Ricerca specifica
```

### 3. **Ignorare Contesto dei Merge**
```bash
# Vedere tutti i commit compresi merge
git log --graph --oneline  # ✅ Mostra struttura branch
```

## ✅ Best Practices

### 1. **Alias Utili**
```bash
# Configura alias per comandi frequenti
git config --global alias.lg "log --oneline --graph --all"
git config --global alias.lstat "log --stat"
git config --global alias.lp "log -p"

# Uso degli alias
git lg    # log grafico
git lstat # log con statistiche
```

### 2. **Combinazioni Potenti**
```bash
# Log ottimizzato per review
git log --oneline --graph --decorate --all -10

# Log per debugging
git log --oneline --grep="fix" --since="1 week ago"

# Log per release notes
git log --pretty=format:"- %s (%h)" v1.0.0..HEAD
```

### 3. **Performance con Repository Grandi**
```bash
# Limita sempre l'output
git log -n 20  # Solo ultimi 20

# Usa --since per limitare range temporale
git log --since="2 weeks ago"

# Filtra per path specifici
git log -- src/components/
```

## 🧪 Quiz di Autovalutazione

1. **Qual è la differenza tra `git log` e `git log --oneline`?**
   - A) Nessuna differenza
   - B) --oneline mostra un commit per riga
   - C) --oneline mostra solo i titoli
   - D) --oneline è più lento

2. **Come vedi i commit di un autore specifico?**
   - A) `git log --user="name"`
   - B) `git log --author="name"`
   - C) `git log --by="name"`
   - D) `git log --from="name"`

3. **Cosa mostra `git log --stat`?**
   - A) Solo i messaggi di commit
   - B) Statistiche sui file modificati
   - C) Solo gli hash dei commit
   - D) Informazioni sui branch

4. **Come limiti il log agli ultimi 5 commit?**
   - A) `git log --limit=5`
   - B) `git log -5`
   - C) `git log --max=5`
   - D) Tutte le precedenti

**Risposte:** 1-B, 2-B, 3-B, 4-B

## 🏋️ Esercizi Pratici

### Esercizio 1: Esplorare Log Base
```bash
# 1. Crea repository con cronologia
mkdir log-test
cd log-test
git init

# Crea diversi commit
echo "# Progetto" > README.md
git add . && git commit -m "docs: Add README"

echo "function main() {}" > app.js
git add . && git commit -m "feat: Add main function"

echo "body { margin: 0; }" > style.css
git add . && git commit -m "style: Add CSS reset"

# 2. Prova diversi formati log
git log
git log --oneline
git log --stat
```

### Esercizio 2: Log Filtrato
```bash
# 1. Aggiungi più commit con pattern
git commit --allow-empty -m "fix: Resolve login issue"
git commit --allow-empty -m "feat: Add logout button"
git commit --allow-empty -m "docs: Update API guide"

# 2. Filtra per tipo
git log --grep="feat" --oneline
git log --grep="fix" --oneline
git log --grep="docs" --oneline
```

### Esercizio 3: Log Personalizzato
```bash
# 1. Crea formato personalizzato
git log --pretty=format:"%h - %an (%ar): %s"

# 2. Log con colori
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(blue)%an%C(reset): %s"

# 3. Salva come alias
git config --global alias.mylog "log --pretty=format:'%h - %an (%ar): %s'"
git mylog
```

## 🔗 Navigazione del Corso

- [📑 Indice](../README.md)  
- [⬅️ 03 - Primo Commit](./03-primo-commit.md)
- [➡️ 04 - Comandi Base Git](../../04-Comandi-Base-Git/README.md)
