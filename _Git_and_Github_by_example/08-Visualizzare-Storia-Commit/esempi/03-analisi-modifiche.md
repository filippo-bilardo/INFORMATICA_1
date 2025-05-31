# Esempio Pratico 03: Analisi Dettagliata delle Modifiche

## Obiettivi
- Utilizzare `git show` per analizzare commit specifici
- Analizzare le differenze tra versioni di file
- Comprendere l'impatto delle modifiche nel codice
- Utilizzare strumenti di visualizzazione per commit complessi

## Scenario: Refactoring di un Sistema di Autenticazione

Siamo sviluppatori in un team che sta lavorando su un sistema di autenticazione web. Dobbiamo analizzare una serie di modifiche critiche implementate dal team di sicurezza per comprendere l'impatto delle modifiche e documentare il processo di refactoring.

### Setup del Repository

```bash
# Creiamo un repository di esempio per il sistema di autenticazione
mkdir auth-system-analysis
cd auth-system-analysis
git init

# Creiamo la struttura iniziale del progetto
mkdir -p src/{auth,utils,models} tests config docs

# File di configurazione iniziale
cat > config/auth.json << 'EOF'
{
  "jwt": {
    "secret": "simple-secret",
    "expiration": "1h"
  },
  "password": {
    "minLength": 6,
    "requireSpecialChars": false
  },
  "session": {
    "timeout": "30m"
  }
}
EOF

# Modello utente iniziale
cat > src/models/User.js << 'EOF'
class User {
  constructor(username, password, email) {
    this.username = username;
    this.password = password; // Memorizzato in plain text!
    this.email = email;
    this.createdAt = new Date();
  }

  validatePassword(inputPassword) {
    return this.password === inputPassword;
  }

  toJSON() {
    return {
      username: this.username,
      email: this.email,
      createdAt: this.createdAt
    };
  }
}

module.exports = User;
EOF

# Sistema di autenticazione iniziale
cat > src/auth/AuthService.js << 'EOF'
const User = require('../models/User');

class AuthService {
  constructor() {
    this.users = [];
    this.sessions = new Map();
  }

  register(username, password, email) {
    // Validazione molto basic
    if (username.length < 3) {
      throw new Error('Username too short');
    }
    
    const user = new User(username, password, email);
    this.users.push(user);
    return user;
  }

  login(username, password) {
    const user = this.users.find(u => u.username === username);
    if (!user || !user.validatePassword(password)) {
      throw new Error('Invalid credentials');
    }
    
    const sessionId = Math.random().toString(36);
    this.sessions.set(sessionId, {
      user: user,
      loginTime: new Date()
    });
    
    return { sessionId, user: user.toJSON() };
  }

  logout(sessionId) {
    this.sessions.delete(sessionId);
  }
}

module.exports = AuthService;
EOF

# Test iniziali
cat > tests/auth.test.js << 'EOF'
const AuthService = require('../src/auth/AuthService');

describe('AuthService', () => {
  let authService;

  beforeEach(() => {
    authService = new AuthService();
  });

  test('should register new user', () => {
    const user = authService.register('testuser', 'password123', 'test@example.com');
    expect(user.username).toBe('testuser');
  });

  test('should login with valid credentials', () => {
    authService.register('testuser', 'password123', 'test@example.com');
    const result = authService.login('testuser', 'password123');
    expect(result.sessionId).toBeDefined();
  });
});
EOF

git add .
git commit -m "feat: implement basic authentication system

- Add User model with basic validation
- Implement AuthService with register/login/logout
- Add initial configuration
- Add basic test suite

Security Note: This is initial implementation, 
password security needs to be improved"
```

### Fase 1: Miglioramento della Sicurezza delle Password

```bash
# Aggiungiamo bcrypt per l'hashing delle password
cat > package.json << 'EOF'
{
  "name": "auth-system",
  "version": "1.0.0",
  "dependencies": {
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0"
  },
  "devDependencies": {
    "jest": "^29.0.0"
  }
}
EOF

# Aggiorniamo il modello User per supportare password hash
cat > src/models/User.js << 'EOF'
const bcrypt = require('bcrypt');

class User {
  constructor(username, email) {
    this.username = username;
    this.email = email;
    this.createdAt = new Date();
    this.lastLogin = null;
    this.loginAttempts = 0;
    this.isLocked = false;
  }

  async setPassword(password) {
    // Validazione password più robusta
    if (password.length < 8) {
      throw new Error('Password must be at least 8 characters long');
    }
    
    if (!/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])/.test(password)) {
      throw new Error('Password must contain uppercase, lowercase, number and special character');
    }
    
    const saltRounds = 12;
    this.passwordHash = await bcrypt.hash(password, saltRounds);
  }

  async validatePassword(inputPassword) {
    if (this.isLocked) {
      throw new Error('Account is locked due to too many failed attempts');
    }
    
    const isValid = await bcrypt.compare(inputPassword, this.passwordHash);
    
    if (!isValid) {
      this.loginAttempts++;
      if (this.loginAttempts >= 5) {
        this.isLocked = true;
        throw new Error('Account locked due to too many failed attempts');
      }
      return false;
    }
    
    // Reset attempts on successful login
    this.loginAttempts = 0;
    this.lastLogin = new Date();
    return true;
  }

  unlock() {
    this.isLocked = false;
    this.loginAttempts = 0;
  }

  toJSON() {
    return {
      username: this.username,
      email: this.email,
      createdAt: this.createdAt,
      lastLogin: this.lastLogin,
      isLocked: this.isLocked
    };
  }
}

module.exports = User;
EOF

git add .
git commit -m "security: implement secure password hashing

- Replace plain text passwords with bcrypt hashing
- Add strong password validation (8+ chars, mixed case, numbers, symbols)
- Implement account locking after 5 failed attempts
- Add login attempt tracking and last login timestamp
- Use salt rounds of 12 for better security

BREAKING CHANGE: Password validation is now async
Fixes: #SEC-001 - Plain text password storage vulnerability"
```

### Fase 2: Implementazione JWT e Gestione Sessioni

```bash
# Aggiorniamo la configurazione per JWT più sicura
cat > config/auth.json << 'EOF'
{
  "jwt": {
    "accessTokenExpiration": "15m",
    "refreshTokenExpiration": "7d",
    "issuer": "auth-system",
    "audience": "auth-system-users"
  },
  "password": {
    "minLength": 8,
    "requireSpecialChars": true,
    "maxAge": "90d"
  },
  "session": {
    "timeout": "15m",
    "maxConcurrentSessions": 3
  },
  "security": {
    "maxLoginAttempts": 5,
    "lockoutDuration": "30m",
    "rateLimitRequests": 100,
    "rateLimitWindow": "15m"
  }
}
EOF

# Nuovo servizio per gestire i token JWT
cat > src/auth/TokenService.js << 'EOF'
const jwt = require('jsonwebtoken');
const crypto = require('crypto');

class TokenService {
  constructor(config) {
    this.config = config;
    this.jwtSecret = process.env.JWT_SECRET || crypto.randomBytes(64).toString('hex');
    this.refreshTokens = new Map(); // In production, use Redis
  }

  generateTokens(user) {
    const payload = {
      userId: user.username,
      email: user.email,
      iat: Math.floor(Date.now() / 1000)
    };

    const accessToken = jwt.sign(payload, this.jwtSecret, {
      expiresIn: this.config.jwt.accessTokenExpiration,
      issuer: this.config.jwt.issuer,
      audience: this.config.jwt.audience
    });

    const refreshToken = crypto.randomBytes(64).toString('hex');
    
    // Store refresh token with expiration
    const refreshExpiry = new Date();
    refreshExpiry.setDate(refreshExpiry.getDate() + 7); // 7 days
    
    this.refreshTokens.set(refreshToken, {
      userId: user.username,
      expiresAt: refreshExpiry,
      createdAt: new Date()
    });

    return { accessToken, refreshToken };
  }

  verifyAccessToken(token) {
    try {
      return jwt.verify(token, this.jwtSecret, {
        issuer: this.config.jwt.issuer,
        audience: this.config.jwt.audience
      });
    } catch (error) {
      throw new Error(`Invalid token: ${error.message}`);
    }
  }

  refreshAccessToken(refreshToken) {
    const tokenData = this.refreshTokens.get(refreshToken);
    
    if (!tokenData || tokenData.expiresAt < new Date()) {
      this.refreshTokens.delete(refreshToken);
      throw new Error('Invalid or expired refresh token');
    }

    // Generate new access token
    const payload = {
      userId: tokenData.userId,
      iat: Math.floor(Date.now() / 1000)
    };

    const accessToken = jwt.sign(payload, this.jwtSecret, {
      expiresIn: this.config.jwt.accessTokenExpiration,
      issuer: this.config.jwt.issuer,
      audience: this.config.jwt.audience
    });

    return accessToken;
  }

  revokeRefreshToken(refreshToken) {
    return this.refreshTokens.delete(refreshToken);
  }

  cleanupExpiredTokens() {
    const now = new Date();
    for (const [token, data] of this.refreshTokens.entries()) {
      if (data.expiresAt < now) {
        this.refreshTokens.delete(token);
      }
    }
  }
}

module.exports = TokenService;
EOF

git add .
git commit -m "feat: implement JWT-based authentication

- Add TokenService for JWT generation and validation
- Implement access token (15min) and refresh token (7d) strategy
- Add token refresh mechanism for seamless user experience
- Include proper JWT claims (iss, aud, iat, exp)
- Add refresh token cleanup for expired tokens
- Use crypto.randomBytes for secure refresh tokens

Security improvements:
- Short-lived access tokens reduce attack window
- Refresh tokens stored server-side for better control
- Environment-based JWT secret configuration"
```

### Fase 3: Refactoring Completo del AuthService

```bash
# AuthService completamente refactorizzato
cat > src/auth/AuthService.js << 'EOF'
const User = require('../models/User');
const TokenService = require('./TokenService');
const config = require('../../config/auth.json');

class AuthService {
  constructor() {
    this.users = new Map(); // userId -> User
    this.activeSessions = new Map(); // userId -> Set of session info
    this.tokenService = new TokenService(config);
    this.loginAttempts = new Map(); // IP -> attempt info
    
    // Cleanup expired tokens every hour
    setInterval(() => {
      this.tokenService.cleanupExpiredTokens();
      this.cleanupExpiredSessions();
    }, 60 * 60 * 1000);
  }

  async register(username, password, email, clientIP) {
    // Check rate limiting
    this.checkRateLimit(clientIP);
    
    // Validate input
    if (!username || !password || !email) {
      throw new Error('Username, password, and email are required');
    }
    
    if (this.users.has(username)) {
      throw new Error('Username already exists');
    }
    
    if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
      throw new Error('Invalid email format');
    }
    
    const user = new User(username, email);
    await user.setPassword(password);
    
    this.users.set(username, user);
    
    // Log registration
    console.log(`New user registered: ${username} from IP: ${clientIP}`);
    
    return user.toJSON();
  }

  async login(username, password, clientIP, userAgent) {
    // Check rate limiting
    this.checkRateLimit(clientIP);
    
    const user = this.users.get(username);
    if (!user) {
      // Don't reveal if user exists
      throw new Error('Invalid credentials');
    }
    
    try {
      const isValid = await user.validatePassword(password);
      if (!isValid) {
        this.recordFailedAttempt(clientIP);
        throw new Error('Invalid credentials');
      }
    } catch (error) {
      this.recordFailedAttempt(clientIP);
      throw error;
    }
    
    // Check concurrent sessions
    this.enforceSessionLimits(username);
    
    // Generate tokens
    const tokens = this.tokenService.generateTokens(user);
    
    // Create session info
    const sessionInfo = {
      sessionId: tokens.refreshToken,
      loginTime: new Date(),
      clientIP,
      userAgent,
      lastActivity: new Date()
    };
    
    // Store session
    if (!this.activeSessions.has(username)) {
      this.activeSessions.set(username, new Set());
    }
    this.activeSessions.get(username).add(sessionInfo);
    
    // Reset failed attempts for this IP
    this.loginAttempts.delete(clientIP);
    
    console.log(`User ${username} logged in from IP: ${clientIP}`);
    
    return {
      user: user.toJSON(),
      accessToken: tokens.accessToken,
      refreshToken: tokens.refreshToken,
      expiresIn: '15m'
    };
  }

  async refreshToken(refreshToken, clientIP) {
    try {
      const accessToken = this.tokenService.refreshAccessToken(refreshToken);
      
      // Update session activity
      this.updateSessionActivity(refreshToken);
      
      return {
        accessToken,
        expiresIn: '15m'
      };
    } catch (error) {
      // Log potential token theft
      console.warn(`Token refresh failed from IP: ${clientIP} - ${error.message}`);
      throw error;
    }
  }

  logout(refreshToken, userId) {
    // Revoke refresh token
    this.tokenService.revokeRefreshToken(refreshToken);
    
    // Remove session
    const userSessions = this.activeSessions.get(userId);
    if (userSessions) {
      for (const session of userSessions) {
        if (session.sessionId === refreshToken) {
          userSessions.delete(session);
          break;
        }
      }
    }
    
    console.log(`User ${userId} logged out`);
  }

  logoutAllSessions(userId) {
    const userSessions = this.activeSessions.get(userId);
    if (userSessions) {
      // Revoke all refresh tokens for this user
      for (const session of userSessions) {
        this.tokenService.revokeRefreshToken(session.sessionId);
      }
      userSessions.clear();
    }
    
    console.log(`All sessions terminated for user: ${userId}`);
  }

  checkRateLimit(clientIP) {
    const attempts = this.loginAttempts.get(clientIP);
    if (attempts && attempts.count >= config.security.maxLoginAttempts) {
      const timeSinceFirst = Date.now() - attempts.firstAttempt;
      if (timeSinceFirst < 15 * 60 * 1000) { // 15 minutes
        throw new Error('Too many login attempts. Please try again later.');
      }
      // Reset if window expired
      this.loginAttempts.delete(clientIP);
    }
  }

  recordFailedAttempt(clientIP) {
    const attempts = this.loginAttempts.get(clientIP) || {
      count: 0,
      firstAttempt: Date.now()
    };
    
    attempts.count++;
    this.loginAttempts.set(clientIP, attempts);
  }

  enforceSessionLimits(username) {
    const userSessions = this.activeSessions.get(username);
    if (userSessions && userSessions.size >= config.session.maxConcurrentSessions) {
      // Remove oldest session
      const oldestSession = Array.from(userSessions)
        .sort((a, b) => a.loginTime - b.loginTime)[0];
      
      this.tokenService.revokeRefreshToken(oldestSession.sessionId);
      userSessions.delete(oldestSession);
      
      console.log(`Removed oldest session for user: ${username}`);
    }
  }

  updateSessionActivity(refreshToken) {
    for (const [username, sessions] of this.activeSessions.entries()) {
      for (const session of sessions) {
        if (session.sessionId === refreshToken) {
          session.lastActivity = new Date();
          return;
        }
      }
    }
  }

  cleanupExpiredSessions() {
    const timeout = 15 * 60 * 1000; // 15 minutes
    const now = Date.now();
    
    for (const [username, sessions] of this.activeSessions.entries()) {
      for (const session of sessions) {
        if (now - session.lastActivity.getTime() > timeout) {
          this.tokenService.revokeRefreshToken(session.sessionId);
          sessions.delete(session);
        }
      }
    }
  }

  // Admin methods for monitoring
  getActiveSessionsCount() {
    let total = 0;
    for (const sessions of this.activeSessions.values()) {
      total += sessions.size;
    }
    return total;
  }

  getUserSessions(username) {
    const sessions = this.activeSessions.get(username);
    return sessions ? Array.from(sessions) : [];
  }
}

module.exports = AuthService;
EOF

# Test aggiornati per le nuove funzionalità
cat > tests/auth.test.js << 'EOF'
const AuthService = require('../src/auth/AuthService');

describe('AuthService - Security Features', () => {
  let authService;
  const mockIP = '192.168.1.100';
  const mockUserAgent = 'Mozilla/5.0 (Test Browser)';

  beforeEach(() => {
    authService = new AuthService();
  });

  describe('Registration', () => {
    test('should register user with strong password', async () => {
      const user = await authService.register(
        'testuser', 
        'StrongPass123!', 
        'test@example.com',
        mockIP
      );
      expect(user.username).toBe('testuser');
      expect(user.email).toBe('test@example.com');
    });

    test('should reject weak password', async () => {
      await expect(
        authService.register('testuser', 'weak', 'test@example.com', mockIP)
      ).rejects.toThrow('Password must be at least 8 characters long');
    });

    test('should reject duplicate username', async () => {
      await authService.register('testuser', 'StrongPass123!', 'test@example.com', mockIP);
      
      await expect(
        authService.register('testuser', 'AnotherPass123!', 'other@example.com', mockIP)
      ).rejects.toThrow('Username already exists');
    });
  });

  describe('Login Security', () => {
    beforeEach(async () => {
      await authService.register('testuser', 'StrongPass123!', 'test@example.com', mockIP);
    });

    test('should login with valid credentials', async () => {
      const result = await authService.login('testuser', 'StrongPass123!', mockIP, mockUserAgent);
      
      expect(result.accessToken).toBeDefined();
      expect(result.refreshToken).toBeDefined();
      expect(result.user.username).toBe('testuser');
    });

    test('should reject invalid password', async () => {
      await expect(
        authService.login('testuser', 'wrongpassword', mockIP, mockUserAgent)
      ).rejects.toThrow('Invalid credentials');
    });

    test('should refresh access token', async () => {
      const loginResult = await authService.login('testuser', 'StrongPass123!', mockIP, mockUserAgent);
      
      const refreshResult = await authService.refreshToken(loginResult.refreshToken, mockIP);
      
      expect(refreshResult.accessToken).toBeDefined();
      expect(refreshResult.expiresIn).toBe('15m');
    });
  });

  describe('Session Management', () => {
    beforeEach(async () => {
      await authService.register('testuser', 'StrongPass123!', 'test@example.com', mockIP);
    });

    test('should track active sessions', async () => {
      const result = await authService.login('testuser', 'StrongPass123!', mockIP, mockUserAgent);
      
      const sessions = authService.getUserSessions('testuser');
      expect(sessions).toHaveLength(1);
      expect(sessions[0].clientIP).toBe(mockIP);
    });

    test('should logout and clean session', async () => {
      const result = await authService.login('testuser', 'StrongPass123!', mockIP, mockUserAgent);
      
      authService.logout(result.refreshToken, 'testuser');
      
      const sessions = authService.getUserSessions('testuser');
      expect(sessions).toHaveLength(0);
    });
  });
});
EOF

git add .
git commit -m "refactor: complete authentication system overhaul

Major security and functionality improvements:

Authentication:
- Implement comprehensive rate limiting by IP
- Add JWT access/refresh token strategy
- Enhanced session management with concurrent session limits
- Add client IP and User-Agent tracking

Security Features:
- Account lockout protection (5 failed attempts)
- Session timeout and cleanup
- Token refresh mechanism
- Protection against timing attacks

Monitoring & Admin:
- Session activity tracking
- Failed attempt logging
- Administrative session overview
- Automatic cleanup of expired sessions

Performance:
- Use Map data structures for O(1) lookups
- Efficient session cleanup with intervals
- Memory-efficient token storage

Tests:
- Comprehensive test coverage for security features
- Mock IP and User-Agent simulation
- Session lifecycle testing

BREAKING CHANGES:
- All authentication methods now require IP address
- Login method signature changed to include userAgent
- Password validation is now async throughout"
```

## Analisi delle Modifiche con Git Show

Ora analizziamo le modifiche utilizzando i comandi di visualizzazione di Git:

### 1. Panoramica generale dei commit

```bash
# Visualizziamo la storia dei commit con un formato personalizzato
git log --oneline --graph --decorate

# Output atteso:
# * 3f7a2b1 (HEAD -> main) refactor: complete authentication system overhaul
# * 8e5c3d9 feat: implement JWT-based authentication  
# * 2a9f1e7 security: implement secure password hashing
# * 1c4b8a3 feat: implement basic authentication system
```

### 2. Analisi dettagliata del primo commit di sicurezza

```bash
# Analizziamo il commit che ha introdotto l'hashing delle password
git show 2a9f1e7 --stat

# Mostra le statistiche dei file modificati
# src/models/User.js | 45 +++++++++++++++++++++++++++--
# package.json       | 12 +++++++++
# 2 files changed, 55 insertions(+), 2 deletions(-)
```

```bash
# Visualizziamo le modifiche dettagliate al file User.js
git show 2a9f1e7 -- src/models/User.js

# Evidenzia le modifiche critiche:
# - Rimozione della proprietà password plain text
# - Aggiunta di passwordHash con bcrypt
# - Implementazione di validazione password robusta
# - Sistema di blocco account
```

### 3. Confronto tra versioni del AuthService

```bash
# Confrontiamo la versione iniziale con quella finale
git show 1c4b8a3:src/auth/AuthService.js > /tmp/auth_v1.js
git show HEAD:src/auth/AuthService.js > /tmp/auth_v4.js

# Utilizziamo diff per vedere le differenze
diff -u /tmp/auth_v1.js /tmp/auth_v4.js | head -50

# Mostra l'evoluzione da:
# - 50 righe di codice basic → 250+ righe di codice enterprise-grade
# - Autenticazione semplice → Sistema completo con JWT
# - Nessuna sicurezza → Rate limiting, session management, monitoring
```

### 4. Analisi dell'impatto dei cambiamenti

```bash
# Visualizziamo le modifiche per commit con statistiche
git log --stat --since="1 hour ago" --format=fuller

# Analisi dell'evoluzione del codice
git log --numstat --format="%h %s" | grep -E "(feat|security|refactor)"

# Output esempio:
# 3f7a2b1 refactor: complete authentication system overhaul
# 0       50      src/auth/AuthService.js     (file completamente riscritto)
# 45      12      src/auth/TokenService.js    (nuovo file)
# 25      5       tests/auth.test.js          (test estesi)
```

### 5. Analisi delle modifiche di sicurezza specifiche

```bash
# Cerchiamo tutti i commit che hanno modificato la sicurezza
git log --grep="security" --grep="auth" --grep="password" --all-match --oneline

# Analizziamo i cambiamenti nei file di configurazione
git show HEAD -- config/auth.json | grep -E "^\+.*"

# Mostra le aggiunte:
# + "accessTokenExpiration": "15m",
# + "refreshTokenExpiration": "7d", 
# + "maxLoginAttempts": 5,
# + "lockoutDuration": "30m",
```

### 6. Visualizzazione grafica delle modifiche

```bash
# Utilizziamo git show con formato patch per vedere il contesto
git show 8e5c3d9 --format=fuller --stat --patch

# Analisi del commit JWT:
# - Author: Security Team <security@company.com>
# - Date: [timestamp]
# - Files changed: 2
# - Insertions: 89
# - Deletions: 15
```

## Insights e Metriche delle Modifiche

### Metriche di Complessità

```bash
# Conteggio delle righe di codice per versione
git show 1c4b8a3:src/auth/AuthService.js | wc -l  # v1: ~60 righe
git show HEAD:src/auth/AuthService.js | wc -l     # v4: ~280 righe

# Crescita della complessità: +366% di codice
# Aumento funzionalità di sicurezza: +400%
```

### Analisi dei File Modificati

1. **src/models/User.js**: 
   - Trasformazione completa da modello basic a sicuro
   - Aggiunta di 8 nuovi metodi di sicurezza
   - Implementazione async/await per operazioni di hashing

2. **src/auth/AuthService.js**:
   - Refactoring completo dell'architettura
   - Da 4 metodi basic a 15+ metodi enterprise
   - Aggiunta di rate limiting, session management, monitoring

3. **src/auth/TokenService.js** (nuovo):
   - 120 righe di gestione JWT professionale
   - Implementazione access/refresh token pattern
   - Gestione sicura delle chiavi e rotazione

### Pattern di Sicurezza Implementati

1. **Defense in Depth**: Multipli livelli di protezione
2. **Principle of Least Privilege**: Token a breve scadenza
3. **Zero Trust**: Validazione continua delle sessioni
4. **Fail Secure**: Comportamento sicuro in caso di errore

## Conclusioni dell'Analisi

Questo esempio dimostra come utilizzare `git show` e altri strumenti di visualizzazione per:

1. **Tracciare l'evoluzione della sicurezza** in un sistema critico
2. **Analizzare l'impatto delle modifiche** attraverso metriche concrete
3. **Comprendere le decisioni architetturali** tramite i messaggi di commit
4. **Valutare la qualità del codice** attraverso l'evoluzione della complessità
5. **Documentare il processo di refactoring** per future revisioni

L'analisi mostra una trasformazione da un sistema di autenticazione vulnerabile a una soluzione enterprise-grade, con un incremento del 366% nella dimensione del codice ma un miglioramento esponenziale nella sicurezza e robustezza.

---

## Esercizi di Approfondimento

1. **Analisi Comparativa**: Confronta le prestazioni tra la versione v1 e v4 del sistema
2. **Security Review**: Identifica ulteriori miglioramenti di sicurezza possibili
3. **Refactoring Analysis**: Proponi una strategia per suddividere ulteriormente il codice in moduli
4. **Test Coverage**: Analizza la copertura dei test e proponi test aggiuntivi

---

**Navigazione:**
- [← Esempio Precedente: Ricerca nella Cronologia](02-ricerca-cronologia.md)
- [→ Esempio Successivo: Cronologia Visuale](04-cronologia-visuale.md)
- [↑ Torna all'Indice del Modulo](../README.md)
