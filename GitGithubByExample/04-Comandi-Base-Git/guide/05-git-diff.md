# 05 - Git Diff e Analisi Differenze

## 📖 Spiegazione Concettuale

`git diff` è il comando per **visualizzare le differenze** tra diverse versioni di file, commit, branch o aree di lavoro. È essenziale per capire esattamente cosa è cambiato prima di committare, durante code review, o per debug.

### Aree di Confronto in Git

Git ha tre aree principali che puoi confrontare:

```
Working Directory ←→ Staging Area ←→ Repository
      (modifiche)      (git add)      (git commit)
```

`git diff` può confrontare qualsiasi combinazione di queste aree.

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git diff
```

### Confronti Principali

#### 1. Aree di Lavoro
```bash
# Working Directory vs Staging Area
git diff

# Staging Area vs ultimo commit
git diff --staged
git diff --cached  # Alias di --staged

# Working Directory vs ultimo commit
git diff HEAD

# Working Directory vs commit specifico
git diff abc123
```

#### 2. Commit e Branch
```bash
# Tra due commit
git diff commit1 commit2

# Tra branch
git diff main feature-branch

# Tra tag
git diff v1.0 v1.1

# Da commit a branch
git diff abc123 main
```

#### 3. File Specifici
```bash
# Singolo file
git diff -- file.js
git diff HEAD -- file.js

# Multipli file
git diff -- file1.js file2.js

# Directory
git diff -- src/
```

## 🎯 Esempi Pratici

### Scenario 1: Verificare Modifiche Prima del Commit
```bash
# Modifica un file
echo "console.log('debug');" >> app.js

# Vedi cosa è cambiato
$ git diff
diff --git a/app.js b/app.js
index 1234567..abcdefg 100644
--- a/app.js
+++ b/app.js
@@ -10,3 +10,4 @@ function init() {
   setupEventListeners();
   loadUserData();
 }
+console.log('debug');

# Aggiungi al staging
git add app.js

# Vedi cosa stai per committare
$ git diff --staged
```

### Scenario 2: Confronto tra Commit
```bash
# Cosa è cambiato nell'ultimo commit?
$ git diff HEAD~1 HEAD

# Tra due commit specifici
$ git diff a1b2c3d e5f6g7h

# Output mostra tutte le modifiche tra i commit
diff --git a/src/auth.js b/src/auth.js
index 1234567..abcdefg 100644
--- a/src/auth.js
+++ b/src/auth.js
@@ -1,8 +1,12 @@
 function authenticate(user, password) {
-  return user === 'admin' && password === 'secret';
+  if (!user || !password) {
+    return false;
+  }
+  return validateCredentials(user, password);
 }
```

### Scenario 3: Confronto tra Branch
```bash
# Cosa cambierebbe mergendo feature-branch in main?
$ git diff main feature-branch

# Solo i file che differiscono
$ git diff --name-only main feature-branch
src/components/header.js
src/styles/main.css
package.json

# Statistiche delle modifiche
$ git diff --stat main feature-branch
 src/components/header.js | 15 +++++++++++++++
 src/styles/main.css      |  8 +++++---
 package.json             |  2 +-
 3 files changed, 21 insertions(+), 4 deletions(-)
```

## 🎨 Opzioni di Formattazione

### 1. Formati di Output
```bash
# Statistiche riassuntive
git diff --stat

# Solo nomi file modificati
git diff --name-only

# Nomi file con status (M=modificato, A=aggiunto, D=eliminato)
git diff --name-status

# Riassunto compatto
git diff --summary
```

### 2. Controllo Contesto
```bash
# Più linee di contesto (default = 3)
git diff -U10  # 10 linee di contesto

# Nessun contesto
git diff -U0

# Funzione completa che contiene la modifica
git diff -W
```

### 3. Formattazione Colori
```bash
# Forza colori (utile in script)
git diff --color=always

# Disabilita colori
git diff --color=never

# Parole invece di righe (per piccole modifiche)
git diff --word-diff
```

## 🔍 Diff Avanzati

### 1. Filtri per Tipo di File
```bash
# Solo file JavaScript
git diff -- "*.js"

# Escludere file di test
git diff -- . ":(exclude)*test*"

# Solo file in src/
git diff -- src/
```

### 2. Ignorare Whitespace
```bash
# Ignora spazi bianchi
git diff -w
git diff --ignore-all-space

# Ignora cambi a fine riga
git diff --ignore-space-at-eol

# Ignora spazi in più/meno
git diff --ignore-space-change
```

### 3. Diff Semantici
```bash
# Algoritmo di diff migliore per codice
git diff --patience

# Diff per funzioni (per linguaggi supportati)
git diff --function-context

# Mostra quale funzione è stata modificata
git diff -p
```

## 🎯 Casi d'Uso Specializzati

### 1. Code Review
```bash
# Preparazione review: cosa cambierà il merge?
git diff main...feature-branch  # Tre punti!

# Modifiche solo nella feature branch
git diff main..feature-branch   # Due punti

# Con statistiche dettagliate
git diff --stat --summary main...feature-branch
```

### 2. Debug: Quando è Cambiato?
```bash
# Cos'è cambiato in un file specifico da un certo punto?
git diff v1.0..HEAD -- problematic-file.js

# Tracked changes in una funzione
git log -p -S "function problematicFunction" -- file.js
```

### 3. Validazione Pre-commit
```bash
# Script pre-commit per verificare modifiche
#!/bin/bash
# Verifica che non ci siano console.log
if git diff --cached | grep -q "console.log"; then
    echo "Errore: console.log trovato nelle modifiche staged"
    exit 1
fi

# Verifica formato del codice
if ! git diff --cached --name-only | grep "\.js$" | xargs eslint; then
    echo "Errore: problemi di linting"
    exit 1
fi
```

## 🎨 Tool Esterni per Diff

### 1. Configurare Tool Grafici
```bash
# VS Code
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'

# Meld
git config --global diff.tool meld

# Beyond Compare
git config --global diff.tool bc3
```

### 2. Usare Difftool
```bash
# Apri tool grafico per differenze
git difftool

# Per file specifico
git difftool -- file.js

# Tra commit
git difftool commit1 commit2
```

### 3. Merge Tool per Conflitti
```bash
# Configura merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'

# Usa durante conflitti
git mergetool
```

## 💡 Best Practices

### 1. Workflow di Verifica
```bash
# Prima di ogni commit
git status                    # Cosa è staged?
git diff                     # Cosa non è staged?
git diff --staged            # Cosa sto per committare?
git commit -m "message"      # Commit consapevole
```

### 2. Alias Utili
```bash
# Setup alias per diff comuni
git config --global alias.d "diff"
git config --global alias.ds "diff --staged"
git config --global alias.dw "diff --word-diff"
git config --global alias.dn "diff --name-only"
```

### 3. Integrazione con Editor
```bash
# VS Code: mostra diff inline
code --diff file1.js file2.js

# Vim: diff mode
vimdiff file1.js file2.js
```

## 🚨 Limitazioni e Considerazioni

### 1. Performance con File Grandi
```bash
# Limita output per file grandi
git diff --stat  # Solo statistiche

# Per file binari (immagini, etc.)
git diff --binary  # Mostra come binary diff
```

### 2. File Rinominati
```bash
# Rileva rinomine (default threshold 50%)
git diff -M

# Threshold più alto per rilevare rinomine
git diff -M90

# Mostra solo rinomine
git diff --name-status -M
```

### 3. Diff di Merge Commit
```bash
# Diff di merge vs primo parent
git diff HEAD~1 HEAD

# Vs tutti i parent
git diff HEAD~2..HEAD  # Se merge a 3-way
```

## 🎓 Interpretare l'Output di Diff

### Header del Diff
```bash
diff --git a/file.js b/file.js  # File confrontati
index 1234567..abcdefg 100644    # Hash e permessi
--- a/file.js                    # Versione vecchia
+++ b/file.js                    # Versione nuova
```

### Hunks (Blocchi di Modifiche)
```bash
@@ -10,7 +10,8 @@  # Formato: @@ -start,count +start,count @@
 function setup() {              # Linea di contesto
   console.log('Starting...');   # Linea di contesto
-  initDatabase();               # Linea rimossa (-)
+  initDatabase(config);         # Linea aggiunta (+)
+  validateConfig();             # Nuova linea aggiunta
   startServer();                # Linea di contesto
 }                               # Linea di contesto
```

## 🎓 Quiz di Verifica

1. **Qual è la differenza tra `git diff` e `git diff --staged`?**
2. **Come vedi solo i nomi dei file modificati tra due branch?**
3. **Come ignori le differenze di spazi bianchi?**

### Risposte
1. `git diff` mostra working directory vs staging, `git diff --staged` mostra staging vs ultimo commit
2. `git diff --name-only branch1 branch2`
3. `git diff -w` o `git diff --ignore-all-space`

## 🔗 Comandi Correlati

- `git status` - Stato delle modifiche
- `git add` - Staging delle modifiche
- `git log -p` - Log con diff
- `git show` - Diff di commit specifico
- `git blame` - Chi ha modificato ogni riga

## 📚 Risorse Aggiuntive

- [Git Diff Documentation](https://git-scm.com/docs/git-diff)
- [Advanced Diff Techniques](https://git-scm.com/book/en/v2/Git-Tools-Advanced-Merging)
- [Diff Tools Setup](https://git-scm.com/docs/git-difftool)

---

**Prossimo**: [06 - Gestione File (rm, mv)](./06-gestione-file.md) - Gestire file nel repository
