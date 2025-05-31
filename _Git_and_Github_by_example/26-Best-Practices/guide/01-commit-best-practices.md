# Best Practices per Commit Git

## Obiettivi
- Padroneggiare le best practices per commit efficaci
- Imparare a scrivere messaggi di commit chiari e informativi
- Comprendere l'importanza dei commit atomici
- Sviluppare un workflow di commit professionale

## Introduzione

I commit rappresentano la documentazione vivente del tuo progetto. Seguire best practices appropriate garantisce:
- Storia del progetto leggibile e comprensibile
- Facilità nel debug e nella ricerca di modifiche
- Collaborazione efficace nel team
- Possibilità di rollback precisi

## 1. Messaggi di Commit Efficaci

### Struttura del Messaggio

```
<tipo>[scope opzionale]: <descrizione>

[corpo opzionale]

[footer opzionale]
```

### Linee Guida per il Titolo

**✅ BUONI ESEMPI:**
```bash
# Chiaro e specifico
git commit -m "fix: correggi calcolo totale nel carrello"

# Usa imperative mood
git commit -m "add: implementa autenticazione JWT"

# Includi il contesto
git commit -m "refactor: semplifica logica di validazione form"
```

**❌ ESEMPI DA EVITARE:**
```bash
# Troppo vago
git commit -m "fix bug"

# Non descrittivo
git commit -m "update"

# Grammatica sbagliata
git commit -m "fixed the thing"
```

### Tipi di Commit Comuni

| Tipo | Descrizione | Esempio |
|------|-------------|---------|
| `feat` | Nuova funzionalità | `feat: add user profile page` |
| `fix` | Correzione bug | `fix: resolve login timeout issue` |
| `docs` | Documentazione | `docs: update API documentation` |
| `style` | Formattazione | `style: fix indentation in utils.js` |
| `refactor` | Refactoring | `refactor: extract validation logic` |
| `test` | Test | `test: add unit tests for calculator` |
| `chore` | Manutenzione | `chore: update dependencies` |

## 2. Commit Atomici

### Principio del Commit Atomico

**Un commit = Una modifica logica**

```bash
# ✅ CORRETTO: Ogni commit ha un focus specifico
git commit -m "feat: add user registration form"
git commit -m "fix: validate email format in registration"
git commit -m "style: improve registration form layout"

# ❌ SBAGLIATO: Troppe modifiche insieme
git commit -m "add registration, fix bugs, update styles"
```

### Vantaggi dei Commit Atomici

1. **Rollback Precisi**: Puoi annullare modifiche specifiche
2. **Review Facili**: Ogni commit è auto-contenuto
3. **Debugging Efficace**: Identificazione rapida di problemi
4. **Storia Pulita**: Timeline logica dello sviluppo

### Esempio Pratico

```bash
# Sviluppo di una feature di login
git add src/components/LoginForm.js
git commit -m "feat: create basic login form component"

git add src/utils/validation.js
git commit -m "feat: add email and password validation"

git add src/services/auth.js
git commit -m "feat: implement authentication service"

git add src/components/LoginForm.js
git commit -m "feat: integrate validation in login form"

git add tests/LoginForm.test.js
git commit -m "test: add comprehensive login form tests"
```

## 3. Staging Strategico

### Commit Parziali con `git add -p`

```bash
# Stage solo parti specifiche di un file
git add -p src/calculator.js

# Opzioni disponibili:
# y - stage this hunk
# n - do not stage this hunk
# q - quit; do not stage this hunk or any remaining ones
# a - stage this hunk and all later hunks in the file
# d - do not stage this hunk or any later hunks in the file
# s - split the current hunk into smaller hunks
# e - manually edit the current hunk
```

### Esempio di Staging Selettivo

```javascript
// File: calculator.js - Modifiche multiple
function add(a, b) {
    // BUG FIX: Validazione input
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error('Input must be numbers');
    }
    return a + b;
}

function subtract(a, b) {
    // NUOVA FEATURE: Sottrazione
    return a - b;
}

function multiply(a, b) {
    // REFACTOR: Miglioramento performance
    return a * b;
}
```

```bash
# Commit separati per ogni tipo di modifica
git add -p calculator.js  # Stage solo il bug fix
git commit -m "fix: add input validation to add function"

git add -p calculator.js  # Stage la nuova feature
git commit -m "feat: implement subtract function"

git add calculator.js     # Stage il refactor
git commit -m "refactor: optimize multiply function"
```

## 4. Workflow di Commit Professionale

### Pre-Commit Checklist

```bash
# 1. Verifica stato del repository
git status

# 2. Review delle modifiche
git diff

# 3. Test (se disponibili)
npm test  # o il comando appropriato per il tuo progetto

# 4. Lint e formatting
npm run lint
npm run format

# 5. Stage e commit
git add <files>
git commit -m "type: descriptive message"
```

### Template di Commit

Crea un template personalizzato:

```bash
# Configura un template globale
git config --global commit.template ~/.gitmessage

# Crea il template
echo "
# <tipo>[scope]: <descrizione>
#
# Spiega COSA e PERCHÉ (non come)
#
# Tipi validi:
# feat: nuova funzionalità
# fix: correzione bug
# docs: documentazione
# style: formattazione
# refactor: refactoring
# test: test
# chore: manutenzione
" > ~/.gitmessage
```

## 5. Gestione degli Errori

### Correggere l'Ultimo Commit

```bash
# Modificare il messaggio dell'ultimo commit
git commit --amend -m "nuovo messaggio corretto"

# Aggiungere file all'ultimo commit
git add file-dimenticato.js
git commit --amend --no-edit

# Modificare sia file che messaggio
git add altro-file.js
git commit --amend -m "messaggio aggiornato"
```

### Correggere Commit Precedenti

```bash
# Rebase interattivo per modificare commit specifici
git rebase -i HEAD~3

# Nel editor che si apre:
# pick abc1234 primo commit
# edit def5678 commit da modificare  # cambia 'pick' in 'edit'
# pick ghi9012 terzo commit

# Dopo aver modificato il commit:
git commit --amend -m "messaggio corretto"
git rebase --continue
```

## 6. Convenzioni Avanzate

### Conventional Commits

Formato standardizzato per commit semantici:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

**Esempi Pratici:**

```bash
# Feature con scope
git commit -m "feat(auth): implement OAuth2 integration"

# Fix con body esplicativo
git commit -m "fix(api): handle null responses in user service

Previously, null responses would cause the application to crash.
This commit adds proper null checking and error handling."

# Breaking change
git commit -m "feat!: change API response format

BREAKING CHANGE: The API response structure has been updated.
Update your client code to handle the new format."
```

### Riferimenti e Linking

```bash
# Riferimento a issue
git commit -m "fix: resolve login timeout (#123)"

# Chiusura automatica di issue
git commit -m "feat: add dashboard analytics

Closes #45
Resolves #67"

# Riferimento a commit
git commit -m "revert: undo changes from commit abc1234"
```

## 7. Automatizzazione e Tools

### Git Hooks per Quality Control

```bash
# Pre-commit hook per verificare la qualità
#!/bin/sh
# .git/hooks/pre-commit

echo "Running pre-commit checks..."

# Lint check
npm run lint
if [ $? -ne 0 ]; then
    echo "Lint check failed. Please fix errors before committing."
    exit 1
fi

# Test check
npm test
if [ $? -ne 0 ]; then
    echo "Tests failed. Please fix tests before committing."
    exit 1
fi

echo "All checks passed. Proceeding with commit."
```

### Commit Message Validation

```bash
# Commit-msg hook per validare messaggi
#!/bin/sh
# .git/hooks/commit-msg

commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! grep -qE "$commit_regex" "$1"; then
    echo "Invalid commit message format!"
    echo "Format: type(scope): description"
    echo "Example: feat(auth): add login functionality"
    exit 1
fi
```

## 8. Metriche e Monitoraggio

### Analizzare la Qualità dei Commit

```bash
# Statistiche sui tipi di commit
git log --oneline | grep -E "^[a-f0-9]+ (feat|fix|docs)" | wc -l

# Frequenza di commit per autore
git shortlog -sn

# Commit più grandi (potenzialmente non atomici)
git log --stat --format="%h %s" | head -20

# Analisi delle dimensioni dei commit
git log --oneline --shortstat | grep -E "files? changed"
```

### Dashboard di Qualità

```bash
#!/bin/bash
# Script per analisi qualità commit

echo "=== ANALISI QUALITÀ COMMIT ==="
echo

echo "📊 Statistiche generali:"
echo "Total commits: $(git rev-list --count HEAD)"
echo "Contributors: $(git shortlog -sn | wc -l)"
echo

echo "📝 Tipi di commit (ultimi 100):"
git log --oneline -100 | sed 's/^[a-f0-9]* //' | sed 's/:.*$//' | sort | uniq -c | sort -rn
echo

echo "🔍 Commit con messaggi brevi (<10 caratteri):"
git log --oneline | awk 'length($0) < 20 {print}'
echo

echo "⚠️  Commit potenzialmente problematici:"
git log --oneline | grep -E "(wip|temp|fix|test)" | head -5
```

## Best Practices Riassunto

### ✅ DA FARE

1. **Scrivi messaggi chiari e descrittivi**
2. **Usa il modo imperativo** ("add feature" non "added feature")
3. **Mantieni commit atomici** (una modifica logica per commit)
4. **Testa prima di committare**
5. **Usa convenzioni consistenti** (Conventional Commits)
6. **Rivedi le modifiche** con `git diff` prima del commit
7. **Stage selettivamente** con `git add -p`

### ❌ DA EVITARE

1. **Messaggi vaghi** ("fix", "update", "change")
2. **Commit troppo grandi** (multiple modifiche non correlate)
3. **Commit di file temporanei** (.tmp, logs, cache)
4. **Commit senza test** (quando applicabile)
5. **Messaggi troppo lunghi** nel titolo (>50 caratteri)
6. **Storia confusa** (troppi merge commit)

## Risorse Aggiuntive

- [Conventional Commits Specification](https://www.conventionalcommits.org/)
- [Git Commit Guidelines Angular](https://github.com/angular/angular/blob/main/CONTRIBUTING.md#commit)
- [How to Write Better Git Commit Messages](https://www.freecodecamp.org/news/how-to-write-better-git-commit-messages/)
- [Git Best Practices](https://deepsource.io/blog/git-best-practices/)

---

*Seguire queste best practices migliorerà significativamente la qualità del tuo lavoro con Git e la collaborazione nel team.*
