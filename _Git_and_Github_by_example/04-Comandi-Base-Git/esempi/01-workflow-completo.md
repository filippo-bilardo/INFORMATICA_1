# 01 - Workflow Completo

## 📋 Scenario

Sei uno sviluppatore che deve implementare una nuova feature "login page" per un'applicazione web. Questo esempio ti guida attraverso un workflow completo utilizzando i comandi Git base.

## 🎯 Obiettivo

Dimostrare l'uso coordinato di `git status`, `git add`, `git commit`, `git log`, e `git diff` in un workflow realistico di sviluppo.

## 🛠️ Setup Iniziale

```bash
# Crea il progetto
mkdir webapp-login
cd webapp-login
git init

# Crea struttura base del progetto
mkdir -p src/{css,js,html}
mkdir tests
mkdir docs

# File base del progetto
cat > src/html/index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>My Web App</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <h1>Welcome to My Web App</h1>
    <div id="app">
        <!-- Content will be loaded here -->
    </div>
    <script src="../js/app.js"></script>
</body>
</html>
EOF

cat > src/css/style.css << 'EOF'
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f4f4f4;
}

h1 {
    color: #333;
    text-align: center;
}

#app {
    max-width: 800px;
    margin: 0 auto;
    background: white;
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}
EOF

cat > src/js/app.js << 'EOF'
// Main application logic
document.addEventListener('DOMContentLoaded', function() {
    console.log('App loaded successfully');
    
    // Initialize app
    initializeApp();
});

function initializeApp() {
    const app = document.getElementById('app');
    app.innerHTML = '<p>App is ready!</p>';
}
EOF

cat > README.md << 'EOF'
# Web App Project

A simple web application with user authentication.

## Features
- Basic HTML structure
- CSS styling
- JavaScript functionality

## Getting Started
Open `src/html/index.html` in your browser.
EOF

# Verifica status iniziale
git status
```

## 📝 Workflow Step-by-Step

### Passo 1: Commit Iniziale del Progetto

```bash
# Controlla lo stato
git status

# Dovrebbe mostrare tutti i file untracked:
# ?? README.md
# ?? docs/
# ?? src/
# ?? tests/

# Aggiungi tutto al staging
git add .

# Verifica cosa è stato staged
git status

# Dovresti vedere:
# Changes to be committed:
#   new file:   README.md
#   new file:   src/css/style.css
#   new file:   src/html/index.html
#   new file:   src/js/app.js

# Commit iniziale
git commit -m "Initial project setup

- Add basic HTML structure
- Add CSS styling
- Add JavaScript application logic
- Add README documentation"

# Verifica il commit
git log --oneline
git status  # Dovrebbe essere clean
```

### Passo 2: Sviluppo Feature Login - CSS

```bash
# Inizia sviluppo login page
echo "Starting login feature development..."

# Aggiungi stili per login form al CSS
cat >> src/css/style.css << 'EOF'

/* Login Form Styles */
.login-container {
    max-width: 400px;
    margin: 50px auto;
    background: white;
    padding: 30px;
    border-radius: 8px;
    box-shadow: 0 4px 6px rgba(0,0,0,0.1);
}

.login-form {
    display: flex;
    flex-direction: column;
}

.form-group {
    margin-bottom: 20px;
}

.form-group label {
    display: block;
    margin-bottom: 5px;
    font-weight: bold;
    color: #555;
}

.form-group input {
    width: 100%;
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 16px;
}

.form-group input:focus {
    outline: none;
    border-color: #007bff;
    box-shadow: 0 0 0 2px rgba(0,123,255,0.25);
}

.btn {
    background-color: #007bff;
    color: white;
    padding: 12px 20px;
    border: none;
    border-radius: 4px;
    font-size: 16px;
    cursor: pointer;
    transition: background-color 0.3s;
}

.btn:hover {
    background-color: #0056b3;
}

.error-message {
    color: #dc3545;
    font-size: 14px;
    margin-top: 5px;
}
EOF

# Controlla status
git status

# Vedi le modifiche
git diff

# Staging delle modifiche CSS
git add src/css/style.css

# Status dopo staging
git status

# Commit delle modifiche CSS
git commit -m "Add login form CSS styles

- Add login container and form styles
- Add form field styling with focus states
- Add button styles with hover effects
- Add error message styling"
```

### Passo 3: Sviluppo Feature Login - HTML

```bash
# Crea la pagina login
cat > src/html/login.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Login - My Web App</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <div class="login-container">
        <h2>Login</h2>
        <form class="login-form" id="loginForm">
            <div class="form-group">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required>
                <div class="error-message" id="usernameError"></div>
            </div>
            
            <div class="form-group">
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required>
                <div class="error-message" id="passwordError"></div>
            </div>
            
            <button type="submit" class="btn">Login</button>
            
            <div class="error-message" id="loginError"></div>
        </form>
        
        <p><a href="index.html">Back to Home</a></p>
    </div>
    
    <script src="../js/login.js"></script>
</body>
</html>
EOF

# Aggiorna index.html per includere link al login
# Sostituisci il contenuto dell'app div
sed -i 's|<p>App is ready!</p>|<p>App is ready!</p>\n        <p><a href="login.html" class="btn">Login</a></p>|' src/html/index.html

# Controlla modifiche
git status
git diff

# Staging solo del file HTML login
git add src/html/login.html

# Controlla status (index.html modificato ma non staged)
git status

# Vedi differenza file non staged
git diff src/html/index.html

# Aggiungi anche index.html
git add src/html/index.html

# Commit delle modifiche HTML
git commit -m "Add login page HTML structure

- Create login.html with form structure
- Add username and password fields
- Add error message containers
- Update index.html with login link"
```

### Passo 4: Sviluppo Feature Login - JavaScript

```bash
# Crea la logica JavaScript per login
cat > src/js/login.js << 'EOF'
// Login page functionality
document.addEventListener('DOMContentLoaded', function() {
    const loginForm = document.getElementById('loginForm');
    const usernameInput = document.getElementById('username');
    const passwordInput = document.getElementById('password');
    const usernameError = document.getElementById('usernameError');
    const passwordError = document.getElementById('passwordError');
    const loginError = document.getElementById('loginError');

    loginForm.addEventListener('submit', function(e) {
        e.preventDefault();
        
        // Clear previous errors
        clearErrors();
        
        // Get form values
        const username = usernameInput.value.trim();
        const password = passwordInput.value.trim();
        
        // Validate form
        if (validateForm(username, password)) {
            // Attempt login
            attemptLogin(username, password);
        }
    });

    function clearErrors() {
        usernameError.textContent = '';
        passwordError.textContent = '';
        loginError.textContent = '';
    }

    function validateForm(username, password) {
        let isValid = true;

        if (!username) {
            usernameError.textContent = 'Username is required';
            isValid = false;
        } else if (username.length < 3) {
            usernameError.textContent = 'Username must be at least 3 characters';
            isValid = false;
        }

        if (!password) {
            passwordError.textContent = 'Password is required';
            isValid = false;
        } else if (password.length < 6) {
            passwordError.textContent = 'Password must be at least 6 characters';
            isValid = false;
        }

        return isValid;
    }

    function attemptLogin(username, password) {
        // Simulate API call delay
        setTimeout(() => {
            // Demo: accept admin/password123
            if (username === 'admin' && password === 'password123') {
                alert('Login successful! Redirecting...');
                window.location.href = 'index.html';
            } else {
                loginError.textContent = 'Invalid username or password';
            }
        }, 1000);
    }
});
EOF

# Aggiorna anche il main app.js per migliorarlo
cat > src/js/app.js << 'EOF'
// Main application logic
document.addEventListener('DOMContentLoaded', function() {
    console.log('App loaded successfully');
    
    // Initialize app
    initializeApp();
    
    // Check if user is logged in (demo)
    checkLoginStatus();
});

function initializeApp() {
    const app = document.getElementById('app');
    app.innerHTML = `
        <p>Welcome to our Web Application!</p>
        <p>Please login to access all features.</p>
        <a href="login.html" class="btn">Login</a>
    `;
}

function checkLoginStatus() {
    // Demo function - in real app would check session/token
    const loggedIn = localStorage.getItem('isLoggedIn');
    
    if (loggedIn === 'true') {
        document.querySelector('#app').innerHTML += 
            '<p style="color: green;">You are logged in!</p>';
    }
}
EOF

# Controlla tutte le modifiche
git status

# Vedi differenze nei file
git diff

# Aggiungi file nuovo
git add src/js/login.js

# Controlla cosa è staged vs unstaged
git status

# Vedi differenze del file modificato
git diff src/js/app.js

# Aggiungi anche il file modificato
git add src/js/app.js

# Commit della funzionalità JavaScript
git commit -m "Implement login functionality

- Add login.js with form validation
- Add authentication logic (demo)
- Update app.js with improved initialization
- Add login status checking functionality"
```

### Passo 5: Testing e Documentazione

```bash
# Crea file di test
cat > tests/login-test.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Login Tests</title>
</head>
<body>
    <h1>Manual Test Cases for Login</h1>
    
    <h2>Test Scenarios:</h2>
    <ol>
        <li><strong>Empty Form:</strong> Submit without filling fields - should show validation errors</li>
        <li><strong>Invalid Username:</strong> Use username less than 3 characters</li>
        <li><strong>Invalid Password:</strong> Use password less than 6 characters</li>
        <li><strong>Wrong Credentials:</strong> Use incorrect username/password combination</li>
        <li><strong>Correct Credentials:</strong> Use "admin" / "password123"</li>
    </ol>
    
    <h2>Expected Results:</h2>
    <ul>
        <li>Validation errors should appear for invalid inputs</li>
        <li>Successful login should redirect to home page</li>
        <li>All form interactions should be smooth</li>
    </ul>
    
    <p><a href="../src/html/login.html">Go to Login Page</a></p>
</body>
</html>
EOF

# Aggiorna la documentazione
cat >> README.md << 'EOF'

## Features Updated

### Login System
- User authentication form
- Client-side validation
- Responsive design
- Error handling

### Demo Credentials
- Username: admin
- Password: password123

## Testing
Open `tests/login-test.html` for manual test scenarios.

## File Structure
```
src/
  html/
    index.html    # Home page
    login.html    # Login page
  css/
    style.css     # All styling
  js/
    app.js        # Main app logic
    login.js      # Login functionality
tests/
  login-test.html # Test scenarios
README.md         # This file
```
EOF

# Aggiungi tutto
git add .

# Status check
git status

# Commit finale
git commit -m "Add testing documentation and update README

- Add manual test cases for login functionality
- Update README with feature documentation
- Add file structure documentation
- Add demo credentials information"
```

### Passo 6: Review del Lavoro Completato

```bash
# Vedi la cronologia completa
git log --oneline

# Vedi cronologia dettagliata
git log --stat

# Vedi le modifiche in un commit specifico
git show HEAD~2  # Mostra il commit 2 passi indietro

# Vedi tutte le modifiche dalla prima versione
git diff HEAD~4  # Confronta con 4 commit fa

# Conta i file nel progetto
find . -type f -not -path './.git/*' | wc -l

# Status finale (dovrebbe essere clean)
git status
```

## 📊 Risultato Finale

Dopo aver completato questo workflow, avrai:

1. **Repository organizzato** con cronologia pulita
2. **Feature login completa** con HTML, CSS, e JavaScript
3. **Documentazione aggiornata** e test cases
4. **Commit atomici** con messaggi descrittivi
5. **Esperienza pratica** con workflow Git reale

### Struttura File Finale
```
webapp-login/
├── README.md
├── src/
│   ├── html/
│   │   ├── index.html
│   │   └── login.html
│   ├── css/
│   │   └── style.css
│   └── js/
│       ├── app.js
│       └── login.js
└── tests/
    └── login-test.html
```

### Cronologia Git
```
* abc1234 Add testing documentation and update README
* def5678 Implement login functionality  
* ghi9012 Add login page HTML structure
* jkl3456 Add login form CSS styles
* mno7890 Initial project setup
```

## 💡 Punti Chiave Appresi

1. **`git status`** è fondamentale prima di ogni operazione
2. **`git add`** può essere usato selettivamente per commit atomici
3. **`git diff`** aiuta a verificare le modifiche prima del commit
4. **Commit messages** descrittivi migliorano la manutenibilità
5. **Workflow incrementale** facilita tracking e debugging

## 🎯 Varianti da Provare

### Variante 1: Selective Staging
```bash
# Modifica multipli file contemporaneamente
echo "/* Additional styles */" >> src/css/style.css
echo "// Additional logic" >> src/js/app.js
echo "More documentation" >> README.md

# Aggiungi solo alcuni file
git add src/css/style.css README.md
git commit -m "Update styles and documentation"

# Commit separato per JS
git add src/js/app.js
git commit -m "Add additional JavaScript logic"
```

### Variante 2: Amend Commit
```bash
# Fai commit
git commit -m "Add new feature"

# Realizzi di aver dimenticato qualcosa
echo "/* Forgot this style */" >> src/css/style.css
git add src/css/style.css

# Modifica l'ultimo commit invece di crearne uno nuovo
git commit --amend -m "Add new feature with complete styling"
```

### Variante 3: Interactive Staging
```bash
# Modifica file con multiple changes
# Usa git add -p per staging selettivo per parti di file
git add -p src/js/app.js

# Questo ti permette di scegliere quali "hunks" del file includere
```

## 🔄 Prossimi Passi

Questo esempio ti ha mostrato un workflow base completo. Nei prossimi moduli approfondiremo:

- **Area di staging** avanzata
- **Branching** per feature development
- **Merge strategies** per integrare lavoro
- **Remote repositories** per collaborazione

---

**Esercizio**: Ripeti questo workflow con un progetto personale per consolidare i concetti!
