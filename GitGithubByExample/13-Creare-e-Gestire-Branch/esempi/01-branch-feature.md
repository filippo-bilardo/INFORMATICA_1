# 01 - Branch Feature Development

## 📖 Scenario

Stai sviluppando un **sistema di autenticazione utenti** per un'applicazione web. Devi implementare login, registrazione e recupero password mantenendo il codice principale stabile durante lo sviluppo.

### Obiettivi Pratici

- ✅ Creare branch feature isolato
- ✅ Sviluppare funzionalità step-by-step
- ✅ Gestire commit atomici e descrittivi
- ✅ Mantenere sincronizzazione con main
- ✅ Preparare per merge finale

## 🚀 Implementazione Pratica

### Setup Iniziale del Progetto

```bash
# Crea cartella progetto
mkdir auth-system-demo
cd auth-system-demo

# Inizializza repository
git init
git config user.name "Developer"
git config user.email "dev@example.com"

# Struttura base applicazione
echo "# Authentication System" > README.md
echo "console.log('App started');" > app.js
mkdir -p src/{auth,components,utils}
echo "// Main app logic" > src/app.js

# Commit iniziale
git add .
git commit -m "Initial commit: basic app structure"

# Crea main branch
git branch -M main
```

### Fase 1: Creazione Branch Feature

```bash
# Verifica stato corrente
git status
git branch

# Crea branch per feature authentication
git switch -c feature/user-authentication

# Verifica creazione
git branch
# * feature/user-authentication
#   main

echo "🎯 Branch feature/user-authentication creato!"
echo "Iniziamo lo sviluppo dell'autenticazione..."
```

### Fase 2: Sviluppo Login Component

```bash
# Crea componente login
cat > src/auth/login.js << 'EOF'
/**
 * Login Component
 * Gestisce autenticazione utenti
 */

class LoginComponent {
    constructor() {
        this.users = [
            { email: 'admin@test.com', password: 'admin123' },
            { email: 'user@test.com', password: 'user123' }
        ];
    }

    validateEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }

    authenticate(email, password) {
        if (!this.validateEmail(email)) {
            return { success: false, error: 'Invalid email format' };
        }

        const user = this.users.find(u => 
            u.email === email && u.password === password
        );

        if (user) {
            return { 
                success: true, 
                message: 'Login successful',
                user: { email: user.email }
            };
        }

        return { success: false, error: 'Invalid credentials' };
    }
}

module.exports = LoginComponent;
EOF

# Commit del login component
git add src/auth/login.js
git commit -m "feat: add login component with email validation

- Implement LoginComponent class
- Add email format validation
- Add user authentication logic
- Include test user accounts"

echo "✅ Login component completato!"
```

### Fase 3: Sviluppo Registration Component

```bash
# Crea componente registrazione
cat > src/auth/register.js << 'EOF'
/**
 * Registration Component
 * Gestisce registrazione nuovi utenti
 */

class RegisterComponent {
    constructor() {
        this.users = [];
    }

    validatePassword(password) {
        // Almeno 8 caratteri, una maiuscola, un numero
        const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/;
        return passwordRegex.test(password);
    }

    validateEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }

    emailExists(email) {
        return this.users.some(user => user.email === email);
    }

    register(email, password, confirmPassword) {
        // Validazione email
        if (!this.validateEmail(email)) {
            return { success: false, error: 'Invalid email format' };
        }

        // Controllo email duplicata
        if (this.emailExists(email)) {
            return { success: false, error: 'Email already registered' };
        }

        // Validazione password
        if (!this.validatePassword(password)) {
            return { 
                success: false, 
                error: 'Password must be 8+ chars with uppercase and number' 
            };
        }

        // Conferma password
        if (password !== confirmPassword) {
            return { success: false, error: 'Passwords do not match' };
        }

        // Registrazione utente
        const newUser = {
            id: Date.now(),
            email: email,
            password: password,
            createdAt: new Date().toISOString()
        };

        this.users.push(newUser);

        return { 
            success: true, 
            message: 'Registration successful',
            user: { id: newUser.id, email: newUser.email }
        };
    }
}

module.exports = RegisterComponent;
EOF

# Commit del registration component
git add src/auth/register.js
git commit -m "feat: add registration component with validation

- Implement RegisterComponent class
- Add password strength validation
- Add email uniqueness check
- Include password confirmation logic"

echo "✅ Registration component completato!"
```

### Fase 4: Sviluppo Password Recovery

```bash
# Crea componente recupero password
cat > src/auth/passwordRecovery.js << 'EOF'
/**
 * Password Recovery Component
 * Gestisce recupero e reset password
 */

class PasswordRecoveryComponent {
    constructor() {
        this.users = [
            { email: 'admin@test.com', password: 'admin123' },
            { email: 'user@test.com', password: 'user123' }
        ];
        this.resetTokens = new Map();
    }

    generateResetToken() {
        return Math.random().toString(36).substring(2, 15) + 
               Math.random().toString(36).substring(2, 15);
    }

    requestPasswordReset(email) {
        const user = this.users.find(u => u.email === email);
        
        if (!user) {
            return { success: false, error: 'Email not found' };
        }

        const resetToken = this.generateResetToken();
        const expiresAt = Date.now() + (15 * 60 * 1000); // 15 minuti

        this.resetTokens.set(resetToken, {
            email: email,
            expiresAt: expiresAt
        });

        // Simula invio email
        console.log(`Password reset email sent to ${email}`);
        console.log(`Reset token: ${resetToken}`);

        return { 
            success: true, 
            message: 'Password reset email sent',
            resetToken: resetToken // In produzione non si restituisce!
        };
    }

    resetPassword(token, newPassword) {
        const tokenData = this.resetTokens.get(token);

        if (!tokenData) {
            return { success: false, error: 'Invalid reset token' };
        }

        if (Date.now() > tokenData.expiresAt) {
            this.resetTokens.delete(token);
            return { success: false, error: 'Reset token expired' };
        }

        // Validazione password
        const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/;
        if (!passwordRegex.test(newPassword)) {
            return { 
                success: false, 
                error: 'Password must be 8+ chars with uppercase and number' 
            };
        }

        // Aggiorna password
        const user = this.users.find(u => u.email === tokenData.email);
        if (user) {
            user.password = newPassword;
            this.resetTokens.delete(token);

            return { 
                success: true, 
                message: 'Password reset successful'
            };
        }

        return { success: false, error: 'User not found' };
    }
}

module.exports = PasswordRecoveryComponent;
EOF

# Commit del password recovery
git add src/auth/passwordRecovery.js
git commit -m "feat: add password recovery component

- Implement password reset request
- Add secure token generation
- Include token expiration (15 min)
- Add password reset validation"

echo "✅ Password recovery completato!"
```

### Fase 5: Integrazione Auth Manager

```bash
# Crea manager principale
cat > src/auth/authManager.js << 'EOF'
/**
 * Authentication Manager
 * Orchestratore principale per autenticazione
 */

const LoginComponent = require('./login');
const RegisterComponent = require('./register');
const PasswordRecoveryComponent = require('./passwordRecovery');

class AuthManager {
    constructor() {
        this.login = new LoginComponent();
        this.register = new RegisterComponent();
        this.passwordRecovery = new PasswordRecoveryComponent();
        this.currentUser = null;
    }

    // Login
    loginUser(email, password) {
        const result = this.login.authenticate(email, password);
        if (result.success) {
            this.currentUser = result.user;
        }
        return result;
    }

    // Registration
    registerUser(email, password, confirmPassword) {
        return this.register.register(email, password, confirmPassword);
    }

    // Password Recovery
    requestPasswordReset(email) {
        return this.passwordRecovery.requestPasswordReset(email);
    }

    resetPassword(token, newPassword) {
        return this.passwordRecovery.resetPassword(token, newPassword);
    }

    // Session Management
    getCurrentUser() {
        return this.currentUser;
    }

    logout() {
        this.currentUser = null;
        return { success: true, message: 'Logged out successfully' };
    }

    isAuthenticated() {
        return this.currentUser !== null;
    }
}

module.exports = AuthManager;
EOF

# Commit del auth manager
git add src/auth/authManager.js
git commit -m "feat: add authentication manager

- Integrate all auth components
- Add session management
- Include logout functionality
- Provide unified auth interface"

echo "✅ Auth Manager completato!"
```

### Fase 6: Demo e Testing

```bash
# Crea demo applicazione
cat > demo.js << 'EOF'
/**
 * Demo Authentication System
 * Test completo delle funzionalità
 */

const AuthManager = require('./src/auth/authManager');

const auth = new AuthManager();

console.log('🔐 === DEMO AUTHENTICATION SYSTEM ===\n');

// Test 1: Registration
console.log('📝 Test Registration:');
let result = auth.registerUser('newuser@test.com', 'Password123', 'Password123');
console.log('Register result:', result);
console.log();

// Test 2: Login con credenziali esistenti
console.log('🔑 Test Login (existing user):');
result = auth.loginUser('admin@test.com', 'admin123');
console.log('Login result:', result);
console.log('Current user:', auth.getCurrentUser());
console.log('Is authenticated:', auth.isAuthenticated());
console.log();

// Test 3: Logout
console.log('🚪 Test Logout:');
result = auth.logout();
console.log('Logout result:', result);
console.log('Is authenticated:', auth.isAuthenticated());
console.log();

// Test 4: Password Recovery
console.log('🔄 Test Password Recovery:');
result = auth.requestPasswordReset('admin@test.com');
console.log('Reset request:', result);

if (result.success && result.resetToken) {
    const resetResult = auth.resetPassword(result.resetToken, 'NewPassword123');
    console.log('Password reset:', resetResult);
}
console.log();

// Test 5: Login con nuova password
console.log('🔑 Test Login (new password):');
result = auth.loginUser('admin@test.com', 'NewPassword123');
console.log('Login with new password:', result);

console.log('\n✅ Demo completato!');
EOF

# Test del sistema
node demo.js

# Commit del demo
git add demo.js
git commit -m "feat: add authentication system demo

- Complete testing suite
- Test all auth components
- Include usage examples
- Verify system integration"

echo "✅ Demo system completato!"
```

### Fase 7: Documentazione e Finalizzazione

```bash
# Aggiorna README con documentazione
cat > README.md << 'EOF'
# Authentication System

Sistema completo di autenticazione utenti con login, registrazione e recupero password.

## 🚀 Features

- ✅ **Login**: Autenticazione con email e password
- ✅ **Registration**: Registrazione nuovi utenti con validazione
- ✅ **Password Recovery**: Reset password con token temporanei
- ✅ **Session Management**: Gestione sessione utente
- ✅ **Validation**: Validazione email e password robusta

## 📁 Struttura

```
src/auth/
├── authManager.js       # Manager principale
├── login.js            # Componente login
├── register.js         # Componente registrazione  
├── passwordRecovery.js # Recupero password
demo.js                 # Demo completo
```

## 🎯 Usage

```javascript
const AuthManager = require('./src/auth/authManager');
const auth = new AuthManager();

// Registration
const registerResult = auth.registerUser(
    'user@example.com', 
    'Password123', 
    'Password123'
);

// Login
const loginResult = auth.loginUser('user@example.com', 'Password123');

// Password Recovery
const resetRequest = auth.requestPasswordReset('user@example.com');
const resetResult = auth.resetPassword(token, 'NewPassword123');
```

## 🧪 Testing

```bash
node demo.js
```

## 📋 Requirements

- Password: 8+ caratteri, almeno una maiuscola e un numero
- Email: formato valido richiesto
- Token reset: scadenza 15 minuti

## 🔒 Security Features

- Password strength validation
- Email format validation
- Token expiration
- Session management
- Duplicate email prevention

---

**Status**: ✅ Feature completa e testata
**Branch**: feature/user-authentication
EOF

# Commit finale
git add README.md
git commit -m "docs: complete authentication system documentation

- Add comprehensive README
- Include usage examples
- Document security features
- Add testing instructions"

echo "✅ Documentazione completata!"
```

### Fase 8: Preparazione per Merge

```bash
# Verifica stato finale del branch
echo "📊 === STATUS FINALE BRANCH ==="
git log --oneline
echo
git status
echo

# Verifica differenze con main
echo "📈 === DIFFERENZE CON MAIN ==="
git diff main --name-only
echo
git log main..HEAD --oneline
echo

# Simulation merge test (senza realmente fare merge)
echo "🧪 === TEST MERGE (DRY RUN) ==="
git switch main
git merge --no-commit --no-ff feature/user-authentication
echo "Merge test successful! Aborting..."
git merge --abort

# Torna al feature branch
git switch feature/user-authentication

echo "✅ Branch feature/user-authentication pronto per merge!"
echo
echo "📋 Summary:"
echo "- 6 commits implementati"
echo "- Sistema autenticazione completo"
echo "- Demo funzionante incluso"  
echo "- Documentazione completa"
echo "- Pronto per code review e merge"
```

## 🎯 Risultati Ottenuti

### Struttura Finale del Branch

```
feature/user-authentication/
├── README.md (aggiornato)
├── app.js
├── demo.js (nuovo)
└── src/
    ├── app.js
    └── auth/
        ├── authManager.js (nuovo)
        ├── login.js (nuovo)
        ├── register.js (nuovo)
        └── passwordRecovery.js (nuovo)
```

### Commit History Pulita

```bash
git log --oneline
# a1b2c3d docs: complete authentication system documentation
# 9x8y7z6 feat: add authentication system demo
# 5u6i7o8 feat: add authentication manager
# 3e4r5t6 feat: add password recovery component
# 7y8u9i0 feat: add registration component with validation
# 1q2w3e4 feat: add login component with email validation
# 9i8u7y6 Initial commit: basic app structure
```

### Features Implementate

- ✅ **Login Component**: Autenticazione con validazione email
- ✅ **Registration Component**: Registrazione con validazione password
- ✅ **Password Recovery**: Sistema di reset con token temporanei
- ✅ **Auth Manager**: Orchestratore centralizzato
- ✅ **Demo System**: Testing completo delle funzionalità
- ✅ **Documentation**: README completo con examples

## 💡 Lezioni Apprese

### Branch Management
- Un branch = una feature specifica
- Commit atomici e descrittivi
- Sviluppo incrementale step-by-step
- Test regolare durante sviluppo

### Development Workflow
- Setup struttura prima dello sviluppo
- Implementazione component-by-component
- Integration testing finale
- Documentazione come parte del processo

### Git Best Practices
- Commit messages seguono conventional commits
- Branch naming descrittivo (`feature/user-authentication`)
- Storia git pulita e leggibile
- Preparazione merge accurata

---

## 🔄 Navigazione

- [⬅️ README](../README.md)
- [➡️ 02 - Hotfix Workflow](02-hotfix-workflow.md)

---

*Prossimo esempio: Gestione hotfix urgenti con branch dedicati*
