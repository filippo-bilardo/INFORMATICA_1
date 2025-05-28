# Esempi Base di Annullamento Modifiche

## 📚 Introduzione

Questa guida presenta esempi pratici per le operazioni di annullamento più comuni in Git. Gli scenari sono pensati per principianti e coprono situazioni quotidiane che ogni sviluppatore incontra.

## 🎯 Scenari Trattati

1. **Annullare modifiche non committate**
2. **Rimuovere file dallo staging**
3. **Annullare l'ultimo commit**
4. **Correggere messaggi di commit**
5. **Recuperare file eliminati accidentalmente**

## 🛠️ Setup Iniziale

Creiamo un repository di esempio per testare gli scenari:

```bash
# Creare repository di test
mkdir git-undo-examples
cd git-undo-examples
git init

# Creare alcuni file di esempio
echo "# My Project" > README.md
echo "console.log('Hello World');" > app.js
echo "body { margin: 0; }" > style.css

# Primo commit
git add .
git commit -m "Initial project setup"

# Creare file di configurazione
echo "DEBUG=true" > .env
echo "node_modules/" > .gitignore

git add .
git commit -m "Add configuration files"
```

## 📋 Esempio 1: Annullare Modifiche nel Working Directory

### Scenario
Hai modificato un file ma vuoi scartare le modifiche e tornare alla versione committata.

```bash
# Modificare un file
echo "console.log('Modified version');" > app.js

# Verificare le modifiche
git status
# modified:   app.js

git diff app.js
# -console.log('Hello World');
# +console.log('Modified version');

# ✅ Annullare le modifiche (Git moderno)
git restore app.js

# ✅ Alternativa (Git classico)
git checkout -- app.js

# Verificare che le modifiche sono state annullate
cat app.js
# console.log('Hello World');
```

### Annullare Modifiche Multiple

```bash
# Modificare più file
echo "Modified README" >> README.md
echo "Modified CSS" >> style.css

# Annullare tutte le modifiche
git restore .

# Oppure annullare file specifici
git restore README.md style.css
```

## 📋 Esempio 2: Rimuovere File dallo Staging

### Scenario
Hai aggiunto file allo staging ma vuoi rimuoverli prima del commit.

```bash
# Modificare e aggiungere file allo staging
echo "New feature code" >> app.js
echo "Updated styles" >> style.css
git add .

# Verificare staging status
git status
# Changes to be committed:
#   modified:   app.js
#   modified:   style.css

# ✅ Rimuovere singolo file dallo staging
git restore --staged app.js

# ✅ Rimuovere tutti i file dallo staging
git restore --staged .

# ✅ Alternativa (Git classico)
git reset HEAD app.js
git reset HEAD  # tutti i file
```

### Combinare Unstaging e Scarto Modifiche

```bash
# Aggiungere modifiche allo staging
echo "Debug code" >> app.js
git add app.js

# Rimuovere dallo staging E scartare modifiche
git restore --staged app.js  # rimuove dallo staging
git restore app.js           # scarta modifiche working directory

# Oppure in un comando (solo per working directory)
git restore --staged --worktree app.js
```

## 📋 Esempio 3: Annullare l'Ultimo Commit

### Scenario A: Mantenere le Modifiche nel Working Directory

```bash
# Fare un commit
echo "Work in progress" >> app.js
git add app.js
git commit -m "WIP: incomplete feature"

# ✅ Annullare commit mantenendo modifiche
git reset --soft HEAD~1

# Verificare stato
git status
# Changes to be committed:
#   modified:   app.js

git log --oneline -3  # Il commit "WIP" è sparito
```

### Scenario B: Annullare Commit e Modifiche

```bash
# Fare un commit sbagliato
echo "Wrong implementation" > app.js
git add app.js
git commit -m "Implement feature wrong way"

# ✅ Annullare tutto (commit + modifiche)
git reset --hard HEAD~1

# Verificare che tutto è tornato allo stato precedente
cat app.js
# console.log('Hello World');  ← versione originale
```

### Scenario C: Annullare Commit con Staging Pulito

```bash
# Commit da annullare
echo "Some changes" >> README.md
git add README.md
git commit -m "Update README"

# ✅ Reset mixed (default) - annulla commit e staging
git reset HEAD~1

# Verificare stato
git status
# Changes not staged for commit:
#   modified:   README.md
```

## 📋 Esempio 4: Correggere Messaggi di Commit

### Scenario A: Correggere Solo il Messaggio

```bash
# Commit con messaggio sbagliato
echo "Fixed bug in logn function" > fix.txt
git add fix.txt
git commit -m "Fix bug in logn function"  # Typo: "logn" invece di "login"

# ✅ Correggere solo il messaggio
git commit --amend -m "Fix bug in login function"

# Verificare correzione
git log --oneline -1
# Fix bug in login function
```

### Scenario B: Aggiungere File Dimenticato

```bash
# Commit principale
echo "function login() {}" > auth.js
git add auth.js
git commit -m "Implement login function"

# Ti accorgi di aver dimenticato i test
echo "test('login should work', () => {});" > auth.test.js

# ✅ Aggiungere al commit precedente
git add auth.test.js
git commit --amend --no-edit

# Verificare che entrambi i file sono nel commit
git show --name-only
# auth.js
# auth.test.js
```

## 📋 Esempio 5: Recuperare File Eliminati

### Scenario A: File Eliminato ma Non Committato

```bash
# Eliminare file accidentalmente
rm style.css

# Verificare che è eliminato
git status
# deleted:    style.css

# ✅ Recuperare il file
git restore style.css

# Verificare recupero
ls style.css  # File è tornato
```

### Scenario B: File Eliminato e Committato

```bash
# Eliminare e committare
git rm .env
git commit -m "Remove environment file"

# Ti accorgi che serviva
# ✅ Recuperare dal commit precedente
git checkout HEAD~1 -- .env

# Aggiungere di nuovo
git add .env
git commit -m "Restore environment file"
```

### Scenario C: File Rinominato per Errore

```bash
# Rinominare file erroneamente
git mv README.md LEGGIMI.md
git commit -m "Rename to Italian"

# Tornare al nome originale
git mv LEGGIMI.md README.md
git commit -m "Restore original filename"
```

## 📋 Esempio 6: Workflow Completo di Correzione

### Scenario: Correzione Multi-Step

```bash
# 1. Situazione iniziale: lavoro in corso
echo "// TODO: implement" > feature.js
echo "Feature documentation" > feature.md
git add .
git commit -m "Start new feature"

# 2. Continuare il lavoro
echo "function newFeature() { return 'done'; }" > feature.js
git add feature.js
git commit -m "Implement feature logic"

# 3. Aggiungere test
echo "test('feature works', () => {});" > feature.test.js
git add feature.test.js
git commit -m "Add feature tests"

# 4. Ti accorgi che il secondo commit aveva un bug
git log --oneline -3
# a1b2c3d Add feature tests
# d4e5f6g Implement feature logic  ← Questo ha un bug
# g7h8i9j Start new feature

# ✅ Strategia di correzione:
# Opzione 1: Revert + correzione
git revert d4e5f6g
echo "function newFeature() { return 'fixed'; }" > feature.js
git add feature.js
git commit -m "Fix feature implementation"

# Opzione 2: Reset + rifare (se non hai pushato)
git reset --hard g7h8i9j  # Torna all'inizio
echo "function newFeature() { return 'correct'; }" > feature.js
git add .
git commit -m "Implement feature correctly"
echo "test('feature works', () => {});" > feature.test.js
git add feature.test.js
git commit -m "Add feature tests"
```

## 🔧 Comandi di Verifica Utili

Durante gli esempi, usa questi comandi per verificare lo stato:

```bash
# Stato generale
git status

# Storia commit
git log --oneline -5

# Differenze
git diff                    # Working directory vs staging
git diff --staged          # Staging vs ultimo commit
git diff HEAD              # Working directory vs ultimo commit

# Mostrare ultimo commit
git show HEAD

# Reflog per vedere tutte le operazioni
git reflog -5
```

## ⚠️ Checklist di Sicurezza

Prima di ogni operazione di annullamento:

### Per Working Directory
- [ ] Verifica `git status` per capire cosa stai annullando
- [ ] Usa `git diff` per vedere le modifiche che perderai
- [ ] Considera di fare backup delle modifiche importanti

### Per Staging
- [ ] Usa `git diff --staged` per vedere cosa rimuovi dallo staging
- [ ] Le modifiche rimarranno nel working directory

### Per Commit
- [ ] Verifica con `git log` quali commit stai modificando
- [ ] Controlla se i commit sono stati pushati (`git log --branches --remotes`)
- [ ] Usa `--soft` se vuoi mantenere le modifiche

## 💡 Tips Pratici

### Alias Utili per Operazioni Comuni

```bash
# Configurare alias pratici
git config --global alias.unstage 'restore --staged'
git config --global alias.discard 'restore'
git config --global alias.undo 'reset --soft HEAD~1'
git config --global alias.amend 'commit --amend --no-edit'

# Uso degli alias
git unstage file.txt    # invece di git restore --staged file.txt
git discard file.txt    # invece di git restore file.txt
git undo               # invece di git reset --soft HEAD~1
git amend              # invece di git commit --amend --no-edit
```

### Verifica Prima dell'Azione

```bash
# Prima di reset hard, verifica cosa perderai
git diff HEAD~1

# Prima di restore, verifica le modifiche
git diff file.txt

# Prima di amend, verifica il commit attuale
git show HEAD
```

## 📝 Riassunto

Questi esempi coprono le operazioni di annullamento più comuni:

- **`git restore`** per working directory e staging
- **`git reset`** per commit e staging  
- **`git commit --amend`** per correggere commit
- **`git checkout`** per recuperare file dalla storia

La chiave è sempre **verificare lo stato** prima di agire e **comprendere la differenza** tra working directory, staging area e commit history.

Pratica questi esempi in un repository di test per acquisire confidenza con le operazioni di annullamento in Git!
