# 04 - Git Commit: Salvare le Modifiche

## 📖 Spiegazione Concettuale

Il comando `git commit` è il cuore di Git. Crea uno "snapshot" permanente dei file nella Staging Area, salvandoli nella storia del repository con un messaggio descrittivo e metadati univoci.

### Anatomia di un Commit

Ogni commit contiene:
- **Snapshot**: Stato completo dei file
- **Messaggio**: Descrizione delle modifiche  
- **Autore**: Chi ha fatto le modifiche
- **Timestamp**: Quando sono state fatte
- **Hash**: Identificatore univoco (SHA-1)
- **Parent**: Riferimento al commit precedente

```
commit a1b2c3d4e5f6789...
Author: Nome Cognome <email@example.com>
Date: Mon Jan 15 10:30:00 2024 +0100
    
    Add user authentication system
    
    - Implement login form validation
    - Add password encryption
    - Create session management
```

## 🔧 Sintassi e Parametri

### Sintassi Base
```bash
git commit [options]
```

### Parametri Principali

| Comando | Descrizione | Esempio |
|---------|-------------|---------|
| `git commit` | Apre editor per messaggio | Interattivo |
| `git commit -m "msg"` | Messaggio inline | `git commit -m "Fix login bug"` |
| `git commit -a` | Add automatico + commit | Solo file tracciati |
| `git commit -am "msg"` | Add automatico + messaggio | Combo veloce |
| `git commit --amend` | Modifica ultimo commit | Correzione errori |
| `git commit --no-verify` | Salta hook pre-commit | Emergency fix |
| `git commit -v` | Mostra diff nell'editor | Review dettagliata |

### Esempi Dettagliati

**1. Commit Base:**
```bash
git add index.html
git commit -m "Add homepage structure"
```

**2. Commit con Add Automatico:**
```bash
# Solo per file già tracciati
git commit -am "Update styling and fix responsive layout"
```

**3. Commit Interattivo:**
```bash
git commit
# Apre editor (vim/nano) per messaggio dettagliato:
# Add user registration feature
# 
# - Create registration form with validation
# - Implement email verification system  
# - Add password strength requirements
# - Update database schema
```

**4. Correggere Ultimo Commit:**
```bash
# Dimenticato un file
git add forgotten-file.js
git commit --amend -m "Add user registration feature (complete)"
```

## 💡 Casi d'Uso Pratici

### Scenario 1: Feature Development
```bash
# Sviluppo di una nuova feature
git add components/LoginForm.js
git add styles/login.css  
git add tests/login.test.js
git commit -m "Add login form component

- Create responsive login form
- Add client-side validation
- Implement error handling
- Add unit tests for form validation"
```

### Scenario 2: Bug Fix
```bash
# Fix di un bug critico
git add src/utils/validator.js
git commit -m "Fix email validation regex

Fixes #123: Email validation was rejecting valid emails
with plus signs in the local part (user+tag@domain.com)"
```

### Scenario 3: Refactoring
```bash
# Refactoring del codice
git add -A  # Molti file modificati
git commit -m "Refactor authentication module

- Extract validation logic to separate utils
- Simplify error handling
- Improve code readability
- No functional changes"
```

### Scenario 4: Documentation
```bash
git add README.md docs/
git commit -m "Update documentation

- Add installation instructions
- Update API documentation  
- Fix typos in getting started guide"
```

## ⚠️ Errori Comuni

### 1. **Messaggi di Commit Vaghi**
```bash
# ❌ CATTIVI messaggi
git commit -m "fix"
git commit -m "changes"
git commit -m "update"
git commit -m "wip"

# ✅ BUONI messaggi  
git commit -m "Fix null pointer exception in user login"
git commit -m "Update homepage layout for mobile devices"
git commit -m "Add input validation for contact form"
```

### 2. **Commit Troppo Grandi**
```bash
# ❌ CATTIVO: Tutto insieme
git add .
git commit -m "Implement entire user management system"

# ✅ BUONO: Commit atomici
git add models/User.js
git commit -m "Add User model with validation"

git add controllers/auth.js  
git commit -m "Add authentication controller"

git add routes/users.js
git commit -m "Add user routes and middleware"
```

### 3. **Dimenticare File nel Commit**
```bash
# ❌ ERRORE: Commit incompleto
git add script.js
git commit -m "Add new feature"
# Dimenticato style.css necessario per la feature

# ✅ SOLUZIONE: Amend
git add style.css
git commit --amend -m "Add new feature with styling"
```

### 4. **Commit di File Sensibili**
```bash
# ❌ ERRORE: File sensibili committati
git add .env config/secrets.json
git commit -m "Add configuration"

# ✅ PREVENZIONE: .gitignore
echo ".env" >> .gitignore
echo "config/secrets.json" >> .gitignore
```

## 🎯 Best Practices

### 1. **Conventional Commits**
```bash
# Formato: type(scope): description
git commit -m "feat(auth): add user registration"
git commit -m "fix(ui): resolve mobile layout issues"  
git commit -m "docs(api): update authentication endpoints"
git commit -m "refactor(utils): simplify validation helpers"

# Tipi comuni:
# feat: nuova funzionalità
# fix: correzione bug
# docs: documentazione
# style: formattazione
# refactor: ristrutturazione codice
# test: test aggiuntivi
# chore: task di manutenzione
```

### 2. **Messaggio Strutturato**
```bash
git commit -m "Add user profile editing feature

- Create profile edit form with validation
- Implement file upload for profile pictures  
- Add email change confirmation workflow
- Update user settings API endpoints

Resolves: #45, #67
See also: #89"
```

### 3. **Commit Frequency**
```bash
# ✅ BUONO: Commit frequenti e piccoli
git commit -m "Add login form HTML structure"
git commit -m "Style login form with CSS"  
git commit -m "Add client-side form validation"
git commit -m "Connect form to authentication API"

# ❌ CATTIVO: Commit rari e grandi
git commit -m "Complete entire login system"
```

### 4. **Review Prima del Commit**
```bash
# Sempre verificare prima di committare
git status              # Cosa è in staging?
git diff --staged       # Che modifiche sto committando?
git commit -v           # Review nell'editor
```

## 🧪 Quiz di Autovalutazione

**1. Cosa contiene un commit Git?**
- a) Solo i file modificati
- b) Snapshot completo + metadati + messaggio
- c) Solo il messaggio di commit
- d) Un link ai file modificati

**2. Qual è la differenza tra `git commit -m` e `git commit`?**
- a) `-m` è più veloce
- b) `-m` permette messaggio inline, senza `-m` apre editor
- c) Sono identici
- d) `-m` è per messaggi privati

**3. Quando uso `git commit --amend`?**
- a) Per creare un nuovo branch
- b) Per modificare l'ultimo commit
- c) Per annullare tutti i commit
- d) Per sincronizzare con il server

**4. Quale messaggio di commit è migliore?**
- a) "fix"
- b) "updated files"
- c) "Fix null pointer exception in user authentication"
- d) "changes made to login system and other stuff"

<details>
<summary>🔍 Risposte</summary>

1. **b)** Snapshot completo + metadati + messaggio
2. **b)** `-m` permette messaggio inline, senza `-m` apre editor
3. **b)** Per modificare l'ultimo commit
4. **c)** "Fix null pointer exception in user authentication"

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Primi Commit
1. Crea un file `app.js` con una funzione semplice
2. Aggiungilo al staging con `git add`
3. Crea un commit con messaggio descrittivo
4. Visualizza la storia con `git log --oneline`

### Esercizio 2: Commit Progressivi
1. Crea tre file: `index.html`, `style.css`, `script.js`
2. Fai tre commit separati, uno per file
3. Ogni commit deve avere un messaggio specifico
4. Verifica la storia dei commit

### Esercizio 3: Amend Practice
1. Crea un commit con un file
2. Realizza di aver dimenticato di aggiungere un altro file
3. Aggiungi il file dimenticato
4. Usa `--amend` per includere entrambi i file nello stesso commit

### Esercizio 4: Messaggio Strutturato
1. Fai modifiche a più file per una "feature"
2. Scrivi un messaggio di commit strutturato con:
   - Titolo chiaro
   - Descrizione dettagliata  
   - Lista delle modifiche principali

## 🔗 Collegamenti Rapidi

- **Comando successivo**: [05 - Git Log](05-git-log.md)
- **Comando precedente**: [03 - Git Add](03-git-add.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 03-Primo-Repository-Git](../../03-Primo-Repository-Git/README.md)
- [➡️ 05-Area-di-Staging](../../05-Area-di-Staging/README.md)
