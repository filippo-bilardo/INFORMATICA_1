# Esercizio 1: Feature Development - Sistema di Autenticazione

## 📋 Descrizione
Sviluppare un sistema completo di autenticazione utente utilizzando branch Git per organizzare lo sviluppo di diverse funzionalità. Implementerai login, registrazione, reset password e profilo utente su branch separati.

## 🎯 Obiettivi di Apprendimento
- Creare e gestire branch per feature diverse
- Comprendere il workflow di sviluppo con branch
- Praticare merge e risoluzione conflitti
- Implementare best practices di branching

## ⏱️ Durata Stimata
60-90 minuti

## 🚀 Setup Iniziale

### 1. Creazione Progetto Base
```bash
# Crea directory progetto
mkdir auth-system
cd auth-system
git init

# Configurazione utente (se necessario)
git config user.name "Your Name"
git config user.email "your.email@example.com"

# Struttura base del progetto
mkdir -p {src/{components,services,utils},public,tests}
```

### 2. File Base del Progetto

Crea i seguenti file iniziali:

**package.json**:
```json
{
  "name": "auth-system",
  "version": "1.0.0",
  "description": "Sistema di autenticazione con gestione branch",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "test": "jest",
    "dev": "nodemon src/app.js"
  },
  "dependencies": {
    "express": "^4.18.0",
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0",
    "mongoose": "^7.0.0"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "nodemon": "^3.0.0"
  }
}
```

**src/app.js**:
```javascript
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());
app.use(express.static('public'));

// Base route
app.get('/', (req, res) => {
    res.json({ 
        message: 'Auth System API',
        version: '1.0.0',
        status: 'running'
    });
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

module.exports = app;
```

**README.md**:
```markdown
# Sistema di Autenticazione

Progetto per esercitazione Git branch con sistema di autenticazione completo.

## Features
- [ ] Registrazione utenti
- [ ] Login/Logout
- [ ] Reset password
- [ ] Gestione profilo utente

## Setup
```bash
npm install
npm start
```

## Development
Questo progetto utilizza Git branch per organizzare lo sviluppo delle feature.
```

### 3. Commit Iniziale
```bash
git add .
git commit -m "feat: initial project setup with base structure"
```

## 🔧 Esercizi Pratici

### Esercizio 1.1: Branch Registrazione Utenti (20 minuti)

#### Obiettivo
Implementare la funzionalità di registrazione utenti su un branch dedicato.

#### Tasks
1. **Crea branch feature**:
```bash
git checkout -b feature/user-registration
```

2. **Implementa modello utente** - Crea `src/models/User.js`:
```javascript
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');

const userSchema = new mongoose.Schema({
    username: {
        type: String,
        required: true,
        unique: true,
        trim: true,
        minlength: 3
    },
    email: {
        type: String,
        required: true,
        unique: true,
        lowercase: true
    },
    password: {
        type: String,
        required: true,
        minlength: 6
    },
    isActive: {
        type: Boolean,
        default: true
    }
}, { timestamps: true });

// Hash password prima del salvataggio
userSchema.pre('save', async function(next) {
    if (!this.isModified('password')) return next();
    this.password = await bcrypt.hash(this.password, 12);
    next();
});

module.exports = mongoose.model('User', userSchema);
```

3. **Implementa controller registrazione** - Crea `src/controllers/authController.js`:
```javascript
const User = require('../models/User');
const jwt = require('jsonwebtoken');

const generateToken = (userId) => {
    return jwt.sign({ userId }, process.env.JWT_SECRET || 'secret', {
        expiresIn: '7d'
    });
};

const register = async (req, res) => {
    try {
        const { username, email, password } = req.body;

        // Validazione input
        if (!username || !email || !password) {
            return res.status(400).json({
                error: 'Username, email e password sono richiesti'
            });
        }

        // Verifica se utente esiste già
        const existingUser = await User.findOne({
            $or: [{ email }, { username }]
        });

        if (existingUser) {
            return res.status(400).json({
                error: 'Utente già esistente'
            });
        }

        // Crea nuovo utente
        const user = new User({ username, email, password });
        await user.save();

        // Genera token
        const token = generateToken(user._id);

        res.status(201).json({
            message: 'Utente registrato con successo',
            user: {
                id: user._id,
                username: user.username,
                email: user.email
            },
            token
        });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

module.exports = { register };
```

4. **Crea routes** - Crea `src/routes/auth.js`:
```javascript
const express = require('express');
const { register } = require('../controllers/authController');
const router = express.Router();

router.post('/register', register);

module.exports = router;
```

5. **Aggiorna app.js**:
```javascript
// Aggiungi dopo i middleware esistenti
const authRoutes = require('./routes/auth');
app.use('/api/auth', authRoutes);
```

6. **Commit delle modifiche**:
```bash
git add .
git commit -m "feat: implement user registration functionality"
```

#### ✅ Verifica
- [ ] Branch `feature/user-registration` creato
- [ ] Modello User implementato
- [ ] Controller registrazione funzionante
- [ ] Routes configurate
- [ ] Commit eseguito

### Esercizio 1.2: Branch Login System (20 minuti)

#### Obiettivo
Implementare sistema di login su branch separato e praticare il merge.

#### Tasks
1. **Torna al main e crea nuovo branch**:
```bash
git checkout main
git checkout -b feature/user-login
```

2. **Estendi authController** - Aggiungi a `src/controllers/authController.js`:
```javascript
// Aggiungi dopo la funzione register
const bcrypt = require('bcrypt');

const login = async (req, res) => {
    try {
        const { login, password } = req.body;

        if (!login || !password) {
            return res.status(400).json({
                error: 'Login e password sono richiesti'
            });
        }

        // Trova utente per email o username
        const user = await User.findOne({
            $or: [
                { email: login },
                { username: login }
            ],
            isActive: true
        });

        if (!user) {
            return res.status(401).json({
                error: 'Credenziali non valide'
            });
        }

        // Verifica password
        const isPasswordValid = await bcrypt.compare(password, user.password);
        if (!isPasswordValid) {
            return res.status(401).json({
                error: 'Credenziali non valide'
            });
        }

        // Genera token
        const token = generateToken(user._id);

        res.json({
            message: 'Login effettuato con successo',
            user: {
                id: user._id,
                username: user.username,
                email: user.email
            },
            token
        });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

// Aggiorna export
module.exports = { register, login };
```

3. **Aggiorna routes** - Modifica `src/routes/auth.js`:
```javascript
const { register, login } = require('../controllers/authController');

// Aggiungi route
router.post('/login', login);
```

4. **Crea middleware di autenticazione** - Crea `src/middleware/auth.js`:
```javascript
const jwt = require('jsonwebtoken');
const User = require('../models/User');

const authMiddleware = async (req, res, next) => {
    try {
        const token = req.header('Authorization')?.replace('Bearer ', '');
        
        if (!token) {
            return res.status(401).json({ error: 'Token mancante' });
        }

        const decoded = jwt.verify(token, process.env.JWT_SECRET || 'secret');
        const user = await User.findById(decoded.userId);

        if (!user || !user.isActive) {
            return res.status(401).json({ error: 'Token non valido' });
        }

        req.user = user;
        next();
    } catch (error) {
        res.status(401).json({ error: 'Token non valido' });
    }
};

module.exports = authMiddleware;
```

5. **Commit e merge**:
```bash
git add .
git commit -m "feat: implement user login and auth middleware"

# Merge nel main
git checkout main
git merge feature/user-login
```

#### ⚠️ Gestione Conflitti
Se si verificano conflitti durante il merge:
```bash
# Risolvi conflitti manualmente nei file
# Poi:
git add .
git commit -m "resolve: merge conflicts in auth implementation"
```

#### ✅ Verifica
- [ ] Feature login implementata
- [ ] Middleware autenticazione creato
- [ ] Merge completato senza errori
- [ ] Tests manuali funzionanti

### Esercizio 1.3: Branch Reset Password (15 minuti)

#### Obiettivo
Implementare reset password e gestire branch multipli.

#### Tasks
1. **Crea branch da main aggiornato**:
```bash
git checkout -b feature/password-reset
```

2. **Implementa reset password** - Aggiungi a `authController.js`:
```javascript
const crypto = require('crypto');

// Aggiungi dopo login function
const resetPasswordRequest = async (req, res) => {
    try {
        const { email } = req.body;

        const user = await User.findOne({ email, isActive: true });
        if (!user) {
            // Non rivelare se l'email esiste
            return res.json({
                message: 'Se l\'email esiste, riceverai istruzioni per il reset'
            });
        }

        // Genera token reset
        const resetToken = crypto.randomBytes(32).toString('hex');
        user.resetPasswordToken = resetToken;
        user.resetPasswordExpires = Date.now() + 3600000; // 1 ora
        await user.save();

        // In un'app reale, invieresti email qui
        console.log(`Reset token for ${email}: ${resetToken}`);

        res.json({
            message: 'Se l\'email esiste, riceverai istruzioni per il reset',
            // Solo per development
            ...(process.env.NODE_ENV === 'development' && { resetToken })
        });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

const resetPassword = async (req, res) => {
    try {
        const { token, newPassword } = req.body;

        const user = await User.findOne({
            resetPasswordToken: token,
            resetPasswordExpires: { $gt: Date.now() }
        });

        if (!user) {
            return res.status(400).json({
                error: 'Token non valido o scaduto'
            });
        }

        // Aggiorna password
        user.password = newPassword;
        user.resetPasswordToken = undefined;
        user.resetPasswordExpires = undefined;
        await user.save();

        res.json({ message: 'Password aggiornata con successo' });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

// Aggiorna export
module.exports = { register, login, resetPasswordRequest, resetPassword };
```

3. **Aggiorna User model** - Aggiungi campi reset al schema:
```javascript
// Aggiungi al userSchema
resetPasswordToken: String,
resetPasswordExpires: Date
```

4. **Aggiorna routes**:
```javascript
const { register, login, resetPasswordRequest, resetPassword } = require('../controllers/authController');

router.post('/reset-password-request', resetPasswordRequest);
router.post('/reset-password', resetPassword);
```

5. **Commit**:
```bash
git add .
git commit -m "feat: implement password reset functionality"
```

### Esercizio 1.4: Branch Profilo Utente (15 minuti)

#### Tasks
1. **Nuovo branch**:
```bash
git checkout main
git checkout -b feature/user-profile
```

2. **Implementa profilo** - Crea `src/controllers/profileController.js`:
```javascript
const getProfile = async (req, res) => {
    try {
        const user = req.user;
        res.json({
            user: {
                id: user._id,
                username: user.username,
                email: user.email,
                createdAt: user.createdAt
            }
        });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

const updateProfile = async (req, res) => {
    try {
        const { username, email } = req.body;
        const user = req.user;

        if (username) user.username = username;
        if (email) user.email = email;

        await user.save();

        res.json({
            message: 'Profilo aggiornato con successo',
            user: {
                id: user._id,
                username: user.username,
                email: user.email
            }
        });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

module.exports = { getProfile, updateProfile };
```

3. **Crea routes profilo** - Crea `src/routes/profile.js`:
```javascript
const express = require('express');
const { getProfile, updateProfile } = require('../controllers/profileController');
const authMiddleware = require('../middleware/auth');
const router = express.Router();

router.get('/', authMiddleware, getProfile);
router.put('/', authMiddleware, updateProfile);

module.exports = router;
```

4. **Aggiorna app.js**:
```javascript
const profileRoutes = require('./routes/profile');
app.use('/api/profile', profileRoutes);
```

5. **Commit**:
```bash
git add .
git commit -m "feat: implement user profile management"
```

## 🔄 Integrazione e Merge Finale

### Esercizio 1.5: Merge di Tutte le Feature (10 minuti)

#### Tasks
1. **Visualizza branch attivi**:
```bash
git branch
git log --oneline --graph --all
```

2. **Merge progressivo**:
```bash
# Torna al main
git checkout main

# Merge reset password
git merge feature/password-reset

# Merge profilo utente
git merge feature/user-profile
```

3. **Cleanup branch**:
```bash
git branch -d feature/user-registration
git branch -d feature/user-login
git branch -d feature/password-reset
git branch -d feature/user-profile
```

4. **Test finale del sistema**:
```bash
# Crea file di test
cat > test-auth.js << 'EOF'
// Test manuale delle API
console.log('Testing auth system...');

// Test registration
fetch('/api/auth/register', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
        username: 'testuser',
        email: 'test@example.com',
        password: 'password123'
    })
});

// Test login
fetch('/api/auth/login', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
        login: 'testuser',
        password: 'password123'
    })
});
EOF
```

## 📊 Verifica Competenze

### ✅ Checklist Completamento

#### Branch Management
- [ ] Creato branch per ogni feature
- [ ] Usato naming convention appropriato
- [ ] Eseguito commit atomici e descrittivi
- [ ] Merge completati correttamente

#### Codice Implementato
- [ ] Sistema registrazione funzionante
- [ ] Login/logout implementato
- [ ] Reset password operativo
- [ ] Gestione profilo utente

#### Git Workflow
- [ ] Branch isolati per ogni feature
- [ ] Merge senza conflitti irrisolti
- [ ] Cleanup branch completato
- [ ] History Git pulita e leggibile

### 🔍 Domande di Verifica

1. **Perché usare branch separati per ogni feature?**
2. **Cosa succede se non fai checkout del main prima di creare un nuovo branch?**
3. **Come gestiresti un conflitto di merge nel file authController.js?**
4. **Qual è la differenza tra `git merge` e `git merge --no-ff`?**

### 🎯 Risultati Attesi

Al completamento dovresti avere:
- Sistema autenticazione completo
- Esperienza pratica con Git branching
- Comprensione workflow di sviluppo feature-based
- Competenze in merge e risoluzione conflitti

## 🔗 Navigazione

← [Esempio 4: Gestione Remoti](../esempi/04-gestione-remoti.md) | [Modulo 13](../README.md) | [Esercizio 2: Multi-Branch Project →](02-multi-branch-project.md)

---

**Durata**: 60-90 minuti | **Livello**: Intermedio | **Tipo**: Pratico
