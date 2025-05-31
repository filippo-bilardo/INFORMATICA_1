# Git Show e Dettagli

## 📖 Analisi Approfondita dei Commit

`git show` è il comando essenziale per esaminare in dettaglio un commit specifico, mostrando metadati completi e le modifiche esatte introdotte. È lo strumento perfetto per code review, debugging e comprensione delle modifiche.

## 🔧 Sintassi Base

### Comando Fondamentale
```bash
# Mostra l'ultimo commit
git show

# Mostra un commit specifico
git show <commit-hash>

# Mostra usando riferimenti
git show HEAD
git show HEAD~1
git show main
git show tag-name
```

### Output Standard
```bash
git show a1b2c3d

# Output completo:
commit a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0
Author: Mario Rossi <mario.rossi@email.com>
Date:   Mon Jan 15 14:30:25 2024 +0100

    Aggiunta funzionalità di login
    
    - Implementata autenticazione utente
    - Aggiunta validazione password
    - Creato sistema di sessioni

diff --git a/src/auth/login.js b/src/auth/login.js
new file mode 100644
index 0000000..1234567
--- /dev/null
+++ b/src/auth/login.js
@@ -0,0 +1,25 @@
+function validateLogin(username, password) {
+    if (!username || !password) {
+        return false;
+    }
+    // ... resto del codice
+}
```

## 🎯 Opzioni di Visualizzazione

### Controllo del Diff
```bash
# Solo metadati, senza diff
git show --no-patch <commit>
git show -s <commit>

# Solo il diff, senza metadati
git show --pretty="" <commit>

# Statistiche delle modifiche
git show --stat <commit>

# Statistiche compatte
git show --shortstat <commit>
```

### Formattazione dell'Output
```bash
# Formato personalizzato
git show --pretty=format:"%h - %s (%an, %ar)" <commit>

# Con numeri di riga
git show --show-line-numbers <commit>

# Con contesto extra
git show -U10 <commit>  # 10 righe di contesto invece di 3
```

### Filtri per File
```bash
# Solo modifiche a file specifici
git show <commit> -- file1.js file2.css

# Escludere file
git show <commit> -- . ':!*.test.js'

# Solo file in una directory
git show <commit> -- src/auth/
```

## 📁 Mostrare Oggetti Specifici

### File in un Commit Specifico
```bash
# Contenuto di un file in un commit
git show <commit>:path/to/file.js

# File dell'ultimo commit
git show HEAD:src/config.js

# File in un tag specifico
git show v1.0:README.md
```

### Directory e Alberi
```bash
# Struttura directory in un commit
git show <commit> --name-only

# Albero di un commit
git show <commit>^{tree}

# Sottodirectory specifica
git show <commit>:src/
```

### Tag e Annotazioni
```bash
# Dettagli di un tag annotato
git show v1.0

# Solo l'oggetto puntato dal tag
git show v1.0^{}

# Messaggio del tag
git show --pretty="" v1.0
```

## 🔍 Analisi delle Modifiche

### Tipi di Diff
```bash
# Diff normale (default)
git show <commit>

# Diff con informazioni di spostamento
git show --find-renames <commit>

# Diff ignorando spazi bianchi
git show --ignore-space-change <commit>

# Diff word-by-word
git show --word-diff <commit>
```

### Analisi Avanzata
```bash
# Mostra solo file aggiunti
git show --diff-filter=A <commit>

# Mostra solo file modificati
git show --diff-filter=M <commit>

# Mostra solo file eliminati
git show --diff-filter=D <commit>

# Combinazioni
git show --diff-filter=AM <commit>
```

### Statistiche Dettagliate
```bash
# Statistiche complete
git show --stat --summary <commit>

# Con conteggio di righe
git show --numstat <commit>

# Formato machine-readable
git show --raw <commit>
```

## 🎨 Formattazione e Colori

### Controllo Colori
```bash
# Forza colori anche su pipe
git show --color=always <commit>

# Disabilita colori
git show --no-color <commit>

# Colori automatici
git show --color=auto <commit>
```

### Pretty Formats
```bash
# Formato compatto
git show --oneline <commit>

# Formato email
git show --pretty=email <commit>

# Formato personalizzato
git show --pretty=format:"%C(yellow)%h%C(reset) - %C(green)%s%C(reset) (%C(blue)%an%C(reset), %C(red)%ar%C(reset))" <commit>
```

## 🔄 Riferimenti e Navigazione

### Sintassi dei Riferimenti
```bash
# Commit specifico
git show a1b2c3d

# Relativo a HEAD
git show HEAD~1    # Commit precedente
git show HEAD~2    # Due commit fa
git show HEAD^     # Primo parent (equivale a HEAD~1)
git show HEAD^2    # Secondo parent (per merge)

# Branch e tag
git show main
git show origin/main
git show v1.0
```

### Merge Commit
```bash
# Merge commit completo
git show <merge-commit>

# Solo il primo parent
git show <merge-commit>^1

# Solo il secondo parent
git show <merge-commit>^2

# Differenza che il merge introduce
git show <merge-commit>^..<merge-commit>
```

### Range di Commit
```bash
# Mostra più commit
git show commit1 commit2 commit3

# Range di commit (usa git log invece)
git log commit1..commit2

# Ultimo commit di ogni branch
git show --branches --max-count=1
```

## 🎯 Casi d'Uso Pratici

### 1. Code Review
```bash
# Revisione completa di un commit
git show --stat --summary <commit>

# Focus su file specifici
git show <commit> -- src/auth/login.js

# Con contesto extra per capire meglio
git show -U5 <commit>
```

### 2. Debugging
```bash
# Analizzare un commit che potrebbe aver introdotto un bug
git show --name-status <commit>

# Vedere le modifiche esatte
git show <commit> -- problematic-file.js

# Confrontare con la versione precedente
git show <commit>~1:file.js > old-version.js
git show <commit>:file.js > new-version.js
diff old-version.js new-version.js
```

### 3. Documentazione e Changelog
```bash
# Informazioni per note di rilascio
git show --pretty=format:"- %s (%h)" --no-patch <commit>

# Dettagli per documentazione
git show --stat --pretty=format:"%h - %s%n%nAuthor: %an <%ae>%nDate: %ad%n" <commit>
```

### 4. Backup e Estrazione
```bash
# Salvare una versione specifica di un file
git show <commit>:src/config.js > config-backup.js

# Estrarre tutti i file di un commit
git archive <commit> | tar -x
```

## 📊 Combinazioni con Altri Comandi

### Con Git Log
```bash
# Lista commit e mostra dettagli del primo
git log --oneline -5 && git show HEAD

# Script per mostrare dettagli di ogni commit recente
for commit in $(git log --oneline -5 --pretty=format:"%h"); do
    echo "=== Commit $commit ==="
    git show --stat $commit
    echo
done
```

### Con Git Diff
```bash
# Differenza tra commit e working directory
git diff <commit>

# Differenza tra due commit
git diff <commit1>..<commit2>

# Differenza specifica per file
git show <commit> -- file.js
git diff <commit>~1..<commit> -- file.js
```

### Con Grep e Ricerca
```bash
# Cercare nei commit e mostrare dettagli
git log --grep="login" --oneline | head -1 | cut -d' ' -f1 | xargs git show

# Mostrare commit che modificano una funzione
git log -S"validatePassword" --oneline | while read commit; do
    git show --stat $commit
done
```

## ⚙️ Configurazione e Alias

### Alias Utili
```bash
# Configurare alias per git show
git config --global alias.details "show --stat --summary"
git config --global alias.patch "show -p"
git config --global alias.files "show --name-only"

# Uso degli alias
git details <commit>
git patch <commit>
git files <commit>
```

### Configurazione Pretty Default
```bash
# Configurare formato default per show
git config --global show.pretty "format:%C(yellow)%h%C(reset) - %C(green)%s%C(reset)%n%C(blue)Author: %an <%ae>%C(reset)%n%C(red)Date: %ad%C(reset)%n"
```

## 🧩 Script e Automazione

### Script per Analisi Commit
```bash
#!/bin/bash
# Analisi dettagliata di un commit

COMMIT=${1:-HEAD}

echo "=== COMMIT ANALYSIS: $COMMIT ==="
echo

echo "--- Metadata ---"
git show --pretty=format:"Hash: %H%nAuthor: %an <%ae>%nDate: %ad%nSubject: %s%n" --no-patch $COMMIT

echo "--- Statistics ---"
git show --stat $COMMIT

echo "--- Files Changed ---"
git show --name-status $COMMIT

echo "--- Content Changes ---"
git show $COMMIT
```

### Funzione Bash per Quick Show
```bash
# Aggiungere al .bashrc
show_commit() {
    local commit=${1:-HEAD}
    echo "=== Quick View: $commit ==="
    git show --oneline --stat $commit
    echo
    read -p "Show full diff? (y/N): " answer
    if [[ $answer =~ ^[Yy]$ ]]; then
        git show $commit
    fi
}
```

## 🧪 Quiz di Verifica

### Domanda 1
Come mostrare solo i metadati di un commit senza il diff?
- A) `git show --no-diff <commit>`
- B) `git show --no-patch <commit>`
- C) `git show --metadata <commit>`
- D) `git show --info <commit>`

<details>
<summary>Risposta</summary>
**B) `git show --no-patch <commit>`**

L'opzione `--no-patch` (o `-s`) mostra solo i metadati senza le modifiche.
</details>

### Domanda 2
Come vedere il contenuto di un file specifico in un commit?
- A) `git show <commit> <file>`
- B) `git show <commit>:<file>`
- C) `git show <commit>/<file>`
- D) `git show <commit> --file=<file>`

<details>
<summary>Risposta</summary>
**B) `git show <commit>:<file>`**

La sintassi `<commit>:<path>` mostra il contenuto del file in quel commit specifico.
</details>

### Domanda 3
Quale comando mostra statistiche delle modifiche di un commit?
- A) `git show --stats <commit>`
- B) `git show --stat <commit>`
- C) `git show --statistics <commit>`
- D) `git show --summary <commit>`

<details>
<summary>Risposta</summary>
**B) `git show --stat <commit>`**

L'opzione `--stat` mostra le statistiche delle modifiche (file modificati, inserimenti, eliminazioni).
</details>

## 🚀 Tecniche Avanzate

### Analisi di Merge Complessi
```bash
# Vedere cosa un merge ha introdotto realmente
git show <merge-commit>

# Confrontare con entrambi i parent
git diff <merge-commit>^1..<merge-commit>
git diff <merge-commit>^2..<merge-commit>

# Vedere conflitti risolti
git show <merge-commit> --cc
```

### Estrazione Selettiva
```bash
# Estrarre solo le modifiche di una funzione
git show <commit> | grep -A 20 -B 5 "function_name"

# Salvare patch per un file specifico
git show <commit> -- file.js > file-patch.patch
```

## 🔄 Prossimi Passi

Dopo aver padroneggiato `git show`, puoi:
1. **Creare alias personalizzati** per le tue analisi più frequenti
2. **Combinare con strumenti grafici** per visualizzazioni interattive
3. **Automatizzare** l'analisi con script personalizzati
4. **Integrare** con workflow di code review

---

**Continua con**: [05-Alias-Personalizzazione](./05-alias-personalizzazione.md) - Personalizzare i comandi Git
