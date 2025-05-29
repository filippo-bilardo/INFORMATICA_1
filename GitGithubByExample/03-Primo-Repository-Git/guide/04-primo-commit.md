# 03 - Primo Commit

## 📖 Spiegazione Concettuale

Il **commit** è l'operazione fondamentale di Git che salva uno snapshot del tuo progetto nella cronologia. Ogni commit rappresenta un punto stabile e recuperabile nella storia del tuo codice.

### Perché è Importante?

- **Snapshot permanente**: Salva lo stato esatto dei file
- **Cronologia**: Crea una timeline del progetto
- **Recupero**: Permette di tornare a versioni precedenti
- **Collaborazione**: Base per condividere modifiche con altri

### Anatomia di un Commit

Ogni commit contiene:
- **SHA-1 hash**: Identificatore unico (es: `a1b2c3d...`)
- **Autore**: Chi ha fatto il commit
- **Data**: Quando è stato fatto
- **Messaggio**: Descrizione delle modifiche
- **Parent**: Link al commit precedente
- **Tree**: Snapshot dei file

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git commit -m "Messaggio del commit"
```

### Varianti Utili
```bash
# Commit con editor per messaggio lungo
git commit

# Commit di tutti i file modificati (tracked)
git commit -am "Messaggio"

# Commit vuoto (per trigger CI/CD)
git commit --allow-empty -m "Trigger build"

# Modifica ultimo commit
git commit --amend -m "Nuovo messaggio"

# Commit con dettagli autore
git commit --author="Nome <email>" -m "Messaggio"
```

## 🎯 Workflow Primo Commit

### 1. **Preparazione File**
```bash
# Crea file di progetto
echo "# Il Mio Primo Progetto" > README.md
echo "console.log('Hello World');" > app.js
echo "body { font-family: Arial; }" > style.css
```

### 2. **Controllo Status**
```bash
git status
# Output: Untracked files: README.md, app.js, style.css
```

### 3. **Staging Files**
```bash
# Aggiungi tutti i file
git add .
# o selettivamente
git add README.md app.js style.css

git status
# Output: Changes to be committed: new file: README.md...
```

### 4. **Primo Commit**
```bash
git commit -m "Initial commit: Add project foundation"
```

### 5. **Verifica Commit**
```bash
git log --oneline
# Output: a1b2c3d Initial commit: Add project foundation

git show
# Mostra dettagli del commit
```

## 🧐 Messaggi di Commit Efficaci

### Struttura Consigliata
```
Tipo: Breve descrizione (max 50 caratteri)

Descrizione dettagliata opzionale (max 72 caratteri per riga)
Spiega il PERCHÉ, non il COSA.

- Punto importante 1
- Punto importante 2

Fixes #123
```

### Tipi Comuni
- **feat**: Nuova funzionalità
- **fix**: Correzione bug
- **docs**: Documentazione
- **style**: Formattazione codice
- **refactor**: Ristrutturazione codice
- **test**: Aggiunta test
- **chore**: Manutenzione

### Esempi Buoni
```bash
git commit -m "feat: Add user authentication system"
git commit -m "fix: Resolve memory leak in image processing"
git commit -m "docs: Update installation instructions"
git commit -m "refactor: Simplify database connection logic"
```

### Esempi Cattivi
```bash
git commit -m "fix"           # ❌ Troppo vago
git commit -m "changes"       # ❌ Non descrittivo
git commit -m "updates lots of stuff and fixes things and adds features" # ❌ Troppo lungo
```

## 🎯 Casi d'Uso Pratici

### 1. **Commit Atomici**
```bash
# Un commit = una funzionalità
git add login.js auth.css
git commit -m "feat: Add login form with validation"

# Separare fix da feature
git add bugfix.js
git commit -m "fix: Resolve null pointer in user lookup"
```

### 2. **Commit con Dettagli**
```bash
git commit -m "fix: Resolve responsive layout issues

- Fix navbar collapse on mobile devices
- Adjust grid breakpoints for tablet view
- Update media queries for better compatibility

Fixes #45, #67"
```

### 3. **Correzione Ultimo Commit**
```bash
# Hai dimenticato un file?
git add file-dimenticato.js
git commit --amend --no-edit

# Vuoi cambiare il messaggio?
git commit --amend -m "Nuovo messaggio migliorato"
```

## ⚠️ Errori Comuni

### 1. **Commit Troppo Grandi**
```bash
# ERRORE: Commit con troppe modifiche non correlate
git add .
git commit -m "Various updates"  # ❌ Cosa include esattamente?

# CORRETTO: Commit separati
git add user-auth.js
git commit -m "feat: Add user authentication"
git add styles.css
git commit -m "style: Update navigation bar design"
```

### 2. **Messaggi Poco Chiari**
```bash
# ERRORE: Messaggi vaghi
git commit -m "fix"          # ❌ Fix di cosa?
git commit -m "update"       # ❌ Update di cosa?

# CORRETTO: Messaggi specifici
git commit -m "fix: Resolve login validation error for empty fields"
git commit -m "update: Improve error handling in API requests"
```

### 3. **Committare File Sensibili**
```bash
# ERRORE: Commit accidentale di file sensibili
git add .
git commit -m "Add features"  # ⚠️ Include config.json con password!

# PREVENZIONE: Usa .gitignore
echo "config.json" >> .gitignore
echo "*.env" >> .gitignore
git add .gitignore
git commit -m "Add gitignore for sensitive files"
```

## ✅ Best Practices

### 1. **Verifica Prima di Committare**
```bash
# Routine pre-commit
git status              # Cosa sto committando?
git diff --staged      # Come sono le modifiche?
git commit -m "Clear descriptive message"
```

### 2. **Commit Frequenti ma Significativi**
```bash
# Commit quando completi una piccola funzionalità
git commit -m "feat: Add email validation to registration form"
# Non aspettare di completare tutto il modulo
```

### 3. **Template per Messaggi**
```bash
# Configura template globale
git config --global commit.template ~/.gitmessage

# Crea template file
echo "Type: Short description

Detailed explanation:
- 
- 

Related issues: #" > ~/.gitmessage
```

## 🧪 Quiz di Autovalutazione

1. **Cosa rappresenta un commit in Git?**
   - A) Un backup dei file
   - B) Uno snapshot del progetto
   - C) Una copia dei file modificati
   - D) Un collegamento a GitHub

2. **Qual è la lunghezza massima consigliata per il titolo del commit?**
   - A) 25 caratteri
   - B) 50 caratteri
   - C) 100 caratteri
   - D) Nessun limite

3. **Come modifichi l'ultimo commit?**
   - A) `git edit`
   - B) `git commit --amend`
   - C) `git modify`
   - D) `git change`

4. **Un buon messaggio di commit dovrebbe:**
   - A) Descrivere cosa è stato fatto
   - B) Spiegare perché è stato fatto
   - C) Essere il più corto possibile
   - D) Includere tutti i dettagli tecnici

**Risposte:** 1-B, 2-B, 3-B, 4-B

## 🏋️ Esercizi Pratici

### Esercizio 1: Primo Commit Completo
```bash
# 1. Inizializza repository
mkdir primo-commit-test
cd primo-commit-test
git init

# 2. Crea contenuto
echo "# Mio Primo Progetto Git" > README.md
echo "Questo è il mio primo repository Git!" >> README.md

# 3. Staging e commit
git add README.md
git status
git commit -m "Initial commit: Add project README"

# 4. Verifica
git log
git show
```

### Esercizio 2: Commit Multipli
```bash
# 1. Aggiungi più contenuto
echo "function greet() { console.log('Hello!'); }" > app.js
git add app.js
git commit -m "feat: Add greeting function"

echo "body { background: #f0f0f0; }" > style.css
git add style.css
git commit -m "style: Add basic page styling"

# 2. Visualizza cronologia
git log --oneline
```

### Esercizio 3: Correzione Commit
```bash
# 1. Commit con errore nel messaggio
echo "const VERSION = '1.0.0';" > version.js
git add version.js
git commit -m "Add version file"  # Messaggio troppo generico

# 2. Correggi con amend
git commit --amend -m "feat: Add version constant for application"

# 3. Verifica correzione
git log --oneline
```

## 🔗 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 02 - Stati dei File in Git](./02-stati-file-git.md)
- [➡️ 04 - Visualizzare Cronologia](./04-visualizzare-cronologia.md)
