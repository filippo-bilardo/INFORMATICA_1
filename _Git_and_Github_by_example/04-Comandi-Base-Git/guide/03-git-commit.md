# 03 - Git Commit e Messaggi

## 📖 Spiegazione Concettuale

`git commit` è il comando che **salva permanentemente** le modifiche dall'area di staging nel repository Git. Ogni commit crea uno snapshot completo del progetto e rappresenta un punto nella cronologia che puoi sempre recuperare.

### Anatomia di un Commit

Un commit Git contiene:
- **Snapshot completo** dei file
- **Metadati**:
  - Autore e data
  - Messaggio descrittivo
  - Hash SHA-1 unico
  - Riferimento al commit precedente (parent)

```
Commit abc123:
├── Tree (snapshot files)
├── Parent: def456
├── Author: Mario Rossi <mario@email.com>
├── Date: 2025-05-29 10:30:00
└── Message: "feat: add user authentication system"
```

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git commit -m "messaggio"
```

### Varianti Principali

#### 1. Commit con Messaggio Inline
```bash
# Messaggio singola riga
git commit -m "fix: resolve login validation bug"

# Messaggio con corpo
git commit -m "feat: add user dashboard" -m "- Display user stats
- Add navigation menu
- Implement responsive design"
```

#### 2. Commit con Editor
```bash
# Apre editor per messaggio dettagliato
git commit

# Con editor specifico
git commit --editor=vim
git commit --editor=code
```

#### 3. Commit Avanzati
```bash
# Commit e add insieme (solo file tracciati)
git commit -am "quick fix for typo"

# Modificare ultimo commit
git commit --amend

# Commit vuoto (utile per trigger CI)
git commit --allow-empty -m "trigger CI rebuild"

# Commit con data specifica
git commit --date="2025-05-28 15:00" -m "backdate commit"
```

## 🎯 Messaggi di Commit Efficaci

### Formato Conventional Commits

Il formato standard per messaggi professionali:

```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

#### Tipi Comuni
- **feat**: Nuova funzionalità
- **fix**: Bug fix
- **docs**: Documentazione
- **style**: Formattazione, spazi bianchi
- **refactor**: Refactoring codice
- **test**: Aggiunta/modifica test
- **chore**: Manutenzione, build, dipendenze

#### Esempi Pratici
```bash
# Funzionalità semplice
git commit -m "feat: add password reset functionality"

# Bug fix con scope
git commit -m "fix(auth): resolve token expiration handling"

# Documentazione
git commit -m "docs: update API documentation for v2.0"

# Refactoring
git commit -m "refactor(utils): simplify date formatting functions"

# Breaking change
git commit -m "feat!: migrate to new authentication API

BREAKING CHANGE: authentication endpoints changed from /auth/* to /api/v2/auth/*"
```

## 🎨 Workflow di Commit

### 1. Workflow Base
```bash
# 1. Controlla stato
git status

# 2. Aggiungi modifiche
git add src/login.js

# 3. Verifica cosa stai committando
git diff --staged

# 4. Commit
git commit -m "feat: implement OAuth login integration"

# 5. Verifica risultato
git log --oneline -1
```

### 2. Workflow con Amend
```bash
# Commit iniziale
git commit -m "fix: resolve navigation bug"

# Oh no, hai dimenticato un file!
git add missed-file.js
git commit --amend --no-edit  # Mantiene stesso messaggio

# O vuoi cambiare il messaggio
git commit --amend -m "fix: resolve navigation and routing bugs"
```

### 3. Workflow Interattivo
```bash
# Commit con editor completo
git commit

# Si apre editor con template:
# Please enter the commit message for your changes...
# 
# On branch feature/user-auth
# Changes to be committed:
#   modified:   src/auth.js
#   new file:   tests/auth.test.js
```

## 💡 Best Practices

### 1. Messaggi Chiari e Descrittivi
```bash
# ❌ Messaggi poveri
git commit -m "fix"
git commit -m "updates"
git commit -m "stuff"

# ✅ Messaggi efficaci
git commit -m "fix: resolve null pointer exception in user validation"
git commit -m "feat: add email verification for new registrations"
git commit -m "docs: add API examples for authentication endpoints"
```

### 2. Commit Atomici
```bash
# ❌ Commit troppo grande
git add .
git commit -m "implement user system, fix bugs, update docs"

# ✅ Commit separati e specifici
git add src/user.js src/auth.js
git commit -m "feat: implement user registration system"

git add tests/user.test.js
git commit -m "test: add user registration test suite"

git add docs/api.md
git commit -m "docs: document user registration endpoints"
```

### 3. Frequenza di Commit
```bash
# ✅ Commit frequenti per funzionalità
git commit -m "feat: add user model structure"
git commit -m "feat: implement user validation logic"
git commit -m "feat: add user persistence layer"
git commit -m "feat: integrate user system with auth flow"
```

## 🎓 Template per Messaggi

### Template Base
Crea `.gitmessage` nella home directory:

```bash
# ~/.gitmessage
<type>(<scope>): <subject>

# Body: Explain what and why vs. how
# - What changes were made?
# - Why were these changes necessary?
# - Any side effects or important notes?

# Footer
# - Issue references: Closes #123
# - Breaking changes: BREAKING CHANGE: description
```

Configura Git per usarlo:
```bash
git config --global commit.template ~/.gitmessage
```

### Template Aziendale
```bash
# Template per team enterprise
<type>(<scope>): <subject> [JIRA-1234]

Detailed explanation of changes:
- Change 1
- Change 2

Testing:
- Unit tests: passed
- Integration tests: passed
- Manual testing: completed

Closes #issue-number
```

## 🚨 Errori Comuni e Soluzioni

### 1. Commit Accidentali
```bash
# Problema: commit con contenuto sbagliato
git commit -m "incomplete feature"

# Soluzioni:
# A) Modificare ultimo commit
git reset --soft HEAD~1  # Torna al pre-commit
git add correct-files.js
git commit -m "feat: complete user authentication"

# B) Amend se non hai fatto push
git add missing-file.js
git commit --amend -m "feat: complete user authentication"
```

### 2. Messaggi di Commit Poveri
```bash
# ❌ Dopo settimane non capisci più cosa hai fatto
git log --oneline
abc123 fix
def456 update
789abc changes

# ✅ Cronologia chiara e utile
git log --oneline
abc123 fix: resolve memory leak in image processor
def456 feat: add batch processing for user imports
789abc docs: update deployment guide with Docker steps
```

### 3. File Dimenticati
```bash
# Hai fatto commit ma dimenticato file importanti
git add forgotten-file.js
git commit --amend --no-edit

# Solo se NON hai già fatto push!
```

## 🎯 Commit Hook e Automazione

### Pre-commit Hook Example
```bash
# .git/hooks/pre-commit
#!/bin/sh
# Esegui test prima di ogni commit
npm test
if [ $? -ne 0 ]; then
    echo "Tests failed. Commit aborted."
    exit 1
fi
```

### Commit Message Validation
```bash
# .git/hooks/commit-msg
#!/bin/sh
# Valida formato conventional commits
commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! grep -qE "$commit_regex" "$1"; then
    echo "Invalid commit message format!"
    echo "Use: <type>(<scope>): <description>"
    exit 1
fi
```

## 🎓 Quiz di Verifica

1. **Qual è la differenza tra `git commit -m` e `git commit`?**
2. **Come modifichi l'ultimo commit senza cambiare il messaggio?**
3. **Cosa contiene un oggetto commit in Git?**

### Risposte
1. `-m` specifica il messaggio inline, senza `-m` apre l'editor
2. `git commit --amend --no-edit`
3. Tree (snapshot), parent commit, metadati autore/data, messaggio

## 🔗 Comandi Correlati

- `git add` - Preparare file per commit
- `git status` - Vedere cosa sarà committato
- `git diff --staged` - Vedere modifiche da committare
- `git log` - Visualizzare cronologia commit
- `git show` - Dettagli commit specifico

## 📚 Risorse Aggiuntive

- [Conventional Commits](https://www.conventionalcommits.org/)
- [Git Commit Best Practices](https://chris.beams.io/posts/git-commit/)
- [Semantic Versioning](https://semver.org/)

---

**Prossimo**: [04 - Git Log e Cronologia](./04-git-log.md) - Esplorare la storia del progetto
