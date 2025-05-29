# Esercizio 2: Simulazione e Risoluzione Conflitti

## Obiettivo
Imparare a gestire e risolvere conflitti Git in un ambiente di team simulando scenari realistici di merge conflicts che si verificano durante lo sviluppo collaborativo.

## Setup dell'Esercizio
Formate un team di 2-3 persone e seguite questo esercizio step-by-step per creare e risolvere diversi tipi di conflitti.

## Fase 1: Preparazione Repository

### 1.1 Creazione Repository Base
**Team Leader** crea repository `conflict-simulation`:

```bash
# Crea repository conflict-simulation su GitHub
git clone https://github.com/[username]/conflict-simulation.git
cd conflict-simulation

# Setup struttura iniziale
mkdir src docs
touch README.md src/app.js src/styles.css docs/api.md
```

**Contenuto iniziale `README.md`:**
```markdown
# Conflict Simulation Project

Progetto per imparare la gestione dei conflitti Git.

## Team Members
- Alice (alice@example.com)
- Bob (bob@example.com)
- Charlie (charlie@example.com)

## Features
- Basic web application
- User authentication
- Todo management
- API documentation

## Setup
1. Clone repository
2. Open index.html in browser
3. Start developing!

## Contributing
1. Create feature branch
2. Make changes
3. Submit PR
4. Resolve conflicts if needed
```

**Contenuto iniziale `src/app.js`:**
```javascript
// Main application file
console.log('App starting...');

// Configuration
const config = {
    apiUrl: 'http://localhost:3000',
    appName: 'Conflict Demo',
    version: '1.0.0'
};

// Main app function
function initApp() {
    console.log('Initializing app...');
    setupEventListeners();
    loadUserData();
}

function setupEventListeners() {
    // Event listeners setup
    console.log('Event listeners ready');
}

function loadUserData() {
    // Load user data
    console.log('Loading user data...');
}

// Start app
initApp();
```

**Contenuto iniziale `src/styles.css`:**
```css
/* Main styles */
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f5f5f5;
}

header {
    background-color: #333;
    color: white;
    padding: 1rem;
    text-align: center;
}

main {
    max-width: 800px;
    margin: 0 auto;
    padding: 20px;
}

button {
    background-color: #007bff;
    color: white;
    border: none;
    padding: 10px 20px;
    cursor: pointer;
}
```

### 1.2 Commit e Push Iniziale
```bash
git add .
git commit -m "Initial project setup

- Add basic project structure
- Create README with team info
- Add starter JavaScript and CSS files
- Setup for conflict simulation exercise"

git push origin main
```

## Fase 2: Conflitti di Tipo Contenuto

### 2.1 Scenario: Modifica Simultanea dello Stesso File

**Alice e Bob** clonano il repository e lavorano simultaneamente su `README.md`.

**Alice** (Branch: `feature/alice-readme-update`):
```bash
git checkout -b feature/alice-readme-update
```

Modifica `README.md`:
```markdown
# Conflict Simulation Project

Progetto avanzato per imparare la gestione dei conflitti Git in team.

## Team Members
- Alice Smith (alice@example.com) - Frontend Lead
- Bob Johnson (bob@example.com) - Backend Developer  
- Charlie Brown (charlie@example.com) - Full Stack

## Features
- Modern web application with React
- JWT user authentication
- Advanced todo management with categories
- RESTful API with documentation
- Real-time notifications

## Tech Stack
- Frontend: React, CSS3, HTML5
- Backend: Node.js, Express
- Database: MongoDB
- Testing: Jest, Cypress

## Setup
1. Clone repository: `git clone [repo-url]`
2. Install dependencies: `npm install`
3. Start development server: `npm start`
4. Open http://localhost:3000

## Contributing
1. Create feature branch: `git checkout -b feature/your-feature`
2. Make changes and test thoroughly
3. Submit PR with detailed description
4. Resolve conflicts if needed
5. Wait for code review approval
```

```bash
git add README.md
git commit -m "Update README with detailed project information

- Add comprehensive tech stack details
- Update team member roles and contact info
- Enhance setup instructions with npm commands
- Expand contributing guidelines"

git push origin feature/alice-readme-update
```

**Bob** (Branch: `feature/bob-readme-improvements`):
```bash
git checkout main
git checkout -b feature/bob-readme-improvements
```

Modifica lo stesso `README.md` (partendo dal contenuto originale):
```markdown
# Conflict Simulation Project

Un progetto educativo per imparare la gestione dei conflitti Git.

## Team Members
- Alice (alice@company.com) - UI/UX Designer
- Bob (bob@company.com) - Backend Engineer
- Charlie (charlie@company.com) - DevOps Specialist

## Features
- Single Page Application
- OAuth user authentication  
- Todo management with drag & drop
- GraphQL API documentation
- Dark/Light theme support

## Architecture
- Frontend: Vanilla JavaScript, SCSS
- Backend: Python Flask
- Database: PostgreSQL
- Deployment: Docker, AWS

## Development Setup
1. Clone this repository
2. Run `python -m venv venv`
3. Activate virtual environment
4. Install requirements: `pip install -r requirements.txt`
5. Run application: `python app.py`

## Contributing Guidelines
1. Fork the repository
2. Create feature branch from main
3. Implement changes with tests
4. Submit pull request
5. Address review feedback
6. Merge after approval

## License
MIT License - see LICENSE file for details
```

```bash
git add README.md
git commit -m "Enhance README with architecture details

- Update team member roles and emails
- Add comprehensive architecture section
- Include Python/Flask setup instructions
- Add license information"

git push origin feature/bob-readme-improvements
```

### 2.2 Creazione del Conflitto

**Alice** crea PR e fa merge per prima:
```bash
# Alice crea PR: feature/alice-readme-update → main
# Il merge viene completato senza problemi
```

**Bob** ora cerca di fare merge e incontra conflitto:
```bash
# Bob crea PR: feature/bob-readme-improvements → main
# GitHub mostra conflitto nel README.md
```

### 2.3 Risoluzione Conflitto

**Bob** risolve il conflitto localmente:
```bash
git checkout feature/bob-readme-improvements
git fetch origin
git merge origin/main

# Git mostra conflitto:
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Automatic merge failed; fix conflicts and then commit the result.
```

**File README.md con conflitto:**
```markdown
# Conflict Simulation Project

<<<<<<< HEAD
Un progetto educativo per imparare la gestione dei conflitti Git.

## Team Members
- Alice (alice@company.com) - UI/UX Designer
- Bob (bob@company.com) - Backend Engineer
- Charlie (charlie@company.com) - DevOps Specialist

## Features
- Single Page Application
- OAuth user authentication  
- Todo management with drag & drop
- GraphQL API documentation
- Dark/Light theme support

## Architecture
- Frontend: Vanilla JavaScript, SCSS
- Backend: Python Flask
- Database: PostgreSQL
- Deployment: Docker, AWS
=======
Progetto avanzato per imparare la gestione dei conflitti Git in team.

## Team Members
- Alice Smith (alice@example.com) - Frontend Lead
- Bob Johnson (bob@example.com) - Backend Developer  
- Charlie Brown (charlie@example.com) - Full Stack

## Features
- Modern web application with React
- JWT user authentication
- Advanced todo management with categories
- RESTful API with documentation
- Real-time notifications

## Tech Stack
- Frontend: React, CSS3, HTML5
- Backend: Node.js, Express
- Database: MongoDB
- Testing: Jest, Cypress
>>>>>>> origin/main

## Setup
...resto del file...
```

**Bob risolve manualmente combinando le migliori parti:**
```markdown
# Conflict Simulation Project

Progetto educativo avanzato per imparare la gestione dei conflitti Git in team.

## Team Members
- Alice Smith (alice@example.com) - Frontend Lead & UI/UX Designer
- Bob Johnson (bob@example.com) - Backend Engineer  
- Charlie Brown (charlie@example.com) - Full Stack & DevOps Specialist

## Features
- Modern Single Page Application with React
- JWT/OAuth user authentication
- Advanced todo management with categories and drag & drop
- RESTful/GraphQL API with comprehensive documentation
- Real-time notifications
- Dark/Light theme support

## Tech Stack
### Frontend
- React, CSS3, HTML5, SCSS
- Jest for testing

### Backend  
- Node.js, Express (primary)
- Python Flask (alternative implementation)

### Database & Infrastructure
- MongoDB (primary), PostgreSQL (alternative)
- Docker for containerization
- AWS for deployment

## Development Setup

### Node.js Setup (Primary)
1. Clone repository: `git clone [repo-url]`
2. Install dependencies: `npm install`
3. Start development server: `npm start`
4. Open http://localhost:3000

### Python Setup (Alternative)
1. Clone this repository
2. Run `python -m venv venv`
3. Activate virtual environment
4. Install requirements: `pip install -r requirements.txt`
5. Run application: `python app.py`

## Contributing Guidelines
1. Fork the repository or create feature branch from main
2. Implement changes with comprehensive tests
3. Submit pull request with detailed description
4. Address review feedback promptly
5. Resolve conflicts if needed
6. Wait for code review approval before merge

## License
MIT License - see LICENSE file for details
```

```bash
git add README.md
git commit -m "Resolve merge conflict in README.md

Combined Alice's React/Node.js tech stack with Bob's architecture details:
- Merged team member roles and contact information
- Combined feature lists with best elements from both
- Integrated dual tech stack options (Node.js primary, Python alternative)  
- Unified setup instructions for both environments
- Enhanced contributing guidelines"

git push origin feature/bob-readme-improvements
```

## Fase 3: Conflitti di Tipo Funzionale

### 3.1 Scenario: Modifica Contemporanea della Stessa Funzione

**Alice** (Branch: `feature/auth-system`):
```javascript
// src/app.js - Alice aggiunge autenticazione JWT
console.log('App starting...');

// Configuration
const config = {
    apiUrl: 'http://localhost:3000',
    appName: 'Conflict Demo',
    version: '1.0.0',
    authEnabled: true,
    jwtSecret: 'your-secret-key'
};

// Authentication module
const auth = {
    currentUser: null,
    
    login(username, password) {
        // Simulate API call
        return fetch(`${config.apiUrl}/auth/login`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ username, password })
        })
        .then(response => response.json())
        .then(data => {
            if (data.token) {
                localStorage.setItem('authToken', data.token);
                this.currentUser = data.user;
                return true;
            }
            return false;
        });
    },
    
    logout() {
        localStorage.removeItem('authToken');
        this.currentUser = null;
        window.location.reload();
    },
    
    isAuthenticated() {
        return !!localStorage.getItem('authToken');
    }
};

// Main app function
function initApp() {
    console.log('Initializing app with authentication...');
    
    if (auth.isAuthenticated()) {
        setupEventListeners();
        loadUserData();
    } else {
        showLoginForm();
    }
}

function setupEventListeners() {
    console.log('Event listeners ready');
    
    // Login form handler
    const loginForm = document.getElementById('loginForm');
    if (loginForm) {
        loginForm.addEventListener('submit', handleLogin);
    }
    
    // Logout button handler
    const logoutBtn = document.getElementById('logoutBtn');
    if (logoutBtn) {
        logoutBtn.addEventListener('click', auth.logout);
    }
}

function handleLogin(event) {
    event.preventDefault();
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    
    auth.login(username, password)
        .then(success => {
            if (success) {
                initApp();
            } else {
                alert('Login failed');
            }
        });
}

function showLoginForm() {
    document.body.innerHTML = `
        <div id="loginContainer">
            <h2>Login Required</h2>
            <form id="loginForm">
                <input type="text" id="username" placeholder="Username" required>
                <input type="password" id="password" placeholder="Password" required>
                <button type="submit">Login</button>
            </form>
        </div>
    `;
    setupEventListeners();
}

function loadUserData() {
    console.log('Loading authenticated user data...');
    // Load data for authenticated user
}

// Start app
initApp();
```

**Bob** (Branch: `feature/oauth-integration`):
```javascript
// src/app.js - Bob aggiunge autenticazione OAuth
console.log('App starting...');

// Configuration
const config = {
    apiUrl: 'http://localhost:3000',
    appName: 'Conflict Demo',
    version: '1.0.0',
    googleClientId: 'your-google-client-id',
    githubClientId: 'your-github-client-id'
};

// OAuth Authentication
class OAuthManager {
    constructor() {
        this.providers = {
            google: {
                clientId: config.googleClientId,
                redirectUri: window.location.origin + '/auth/google/callback',
                scope: 'profile email'
            },
            github: {
                clientId: config.githubClientId,
                redirectUri: window.location.origin + '/auth/github/callback',
                scope: 'user:email'
            }
        };
    }
    
    loginWithGoogle() {
        const params = new URLSearchParams({
            client_id: this.providers.google.clientId,
            redirect_uri: this.providers.google.redirectUri,
            response_type: 'code',
            scope: this.providers.google.scope
        });
        
        window.location.href = `https://accounts.google.com/oauth/authorize?${params}`;
    }
    
    loginWithGitHub() {
        const params = new URLSearchParams({
            client_id: this.providers.github.clientId,
            redirect_uri: this.providers.github.redirectUri,
            scope: this.providers.github.scope
        });
        
        window.location.href = `https://github.com/login/oauth/authorize?${params}`;
    }
    
    handleOAuthCallback() {
        const urlParams = new URLSearchParams(window.location.search);
        const code = urlParams.get('code');
        const state = urlParams.get('state');
        
        if (code) {
            return this.exchangeCodeForToken(code);
        }
        return Promise.reject('No authorization code received');
    }
    
    exchangeCodeForToken(code) {
        return fetch(`${config.apiUrl}/auth/oauth/token`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ code })
        })
        .then(response => response.json())
        .then(data => {
            if (data.access_token) {
                localStorage.setItem('oauthToken', data.access_token);
                return this.getUserProfile(data.access_token);
            }
            throw new Error('Token exchange failed');
        });
    }
    
    getUserProfile(token) {
        return fetch(`${config.apiUrl}/auth/profile`, {
            headers: { 'Authorization': `Bearer ${token}` }
        })
        .then(response => response.json());
    }
    
    logout() {
        localStorage.removeItem('oauthToken');
        window.location.href = '/';
    }
    
    isAuthenticated() {
        return !!localStorage.getItem('oauthToken');
    }
}

const oauth = new OAuthManager();

// Main app function
function initApp() {
    console.log('Initializing app with OAuth...');
    
    // Check for OAuth callback
    if (window.location.search.includes('code=')) {
        oauth.handleOAuthCallback()
            .then(user => {
                console.log('OAuth login successful:', user);
                window.history.replaceState({}, document.title, window.location.pathname);
                setupEventListeners();
                loadUserData();
            })
            .catch(error => {
                console.error('OAuth login failed:', error);
                showLoginOptions();
            });
    } else if (oauth.isAuthenticated()) {
        setupEventListeners();
        loadUserData();
    } else {
        showLoginOptions();
    }
}

function setupEventListeners() {
    console.log('OAuth event listeners ready');
    
    // Google login button
    const googleBtn = document.getElementById('googleLogin');
    if (googleBtn) {
        googleBtn.addEventListener('click', () => oauth.loginWithGoogle());
    }
    
    // GitHub login button  
    const githubBtn = document.getElementById('githubLogin');
    if (githubBtn) {
        githubBtn.addEventListener('click', () => oauth.loginWithGitHub());
    }
    
    // Logout button
    const logoutBtn = document.getElementById('logoutBtn');
    if (logoutBtn) {
        logoutBtn.addEventListener('click', () => oauth.logout());
    }
}

function showLoginOptions() {
    document.body.innerHTML = `
        <div id="loginContainer">
            <h2>Choose Login Method</h2>
            <div id="loginOptions">
                <button id="googleLogin" class="oauth-btn google">
                    Login with Google
                </button>
                <button id="githubLogin" class="oauth-btn github">
                    Login with GitHub
                </button>
            </div>
        </div>
    `;
    setupEventListeners();
}

function loadUserData() {
    console.log('Loading OAuth user data...');
    // Load data for OAuth authenticated user
}

// Start app
initApp();
```

### 3.2 Conflitto e Risoluzione Strategica

Quando Bob cerca di fare merge, trova conflitti sostanziali. La risoluzione richiede una strategia:

**Opzione 1: Merge con Sistema Ibrido**
```javascript
// src/app.js - Versione risolta con supporto per entrambi i sistemi
console.log('App starting...');

// Configuration
const config = {
    apiUrl: 'http://localhost:3000',
    appName: 'Conflict Demo',
    version: '1.0.0',
    // JWT Configuration
    authEnabled: true,
    jwtSecret: 'your-secret-key',
    // OAuth Configuration  
    googleClientId: 'your-google-client-id',
    githubClientId: 'your-github-client-id',
    // Authentication strategy: 'jwt', 'oauth', 'both'
    authStrategy: 'both'
};

// Authentication Factory
class AuthManager {
    constructor() {
        this.strategy = config.authStrategy;
        this.currentUser = null;
        
        // Initialize based on strategy
        if (this.strategy === 'jwt' || this.strategy === 'both') {
            this.initJWT();
        }
        if (this.strategy === 'oauth' || this.strategy === 'both') {
            this.initOAuth();
        }
    }
    
    initJWT() {
        this.jwt = {
            login: (username, password) => {
                return fetch(`${config.apiUrl}/auth/login`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ username, password })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.token) {
                        localStorage.setItem('authToken', data.token);
                        this.currentUser = data.user;
                        return { success: true, user: data.user };
                    }
                    return { success: false, error: 'Invalid credentials' };
                });
            },
            
            logout: () => {
                localStorage.removeItem('authToken');
                this.currentUser = null;
            },
            
            isAuthenticated: () => !!localStorage.getItem('authToken')
        };
    }
    
    initOAuth() {
        this.oauth = {
            providers: {
                google: {
                    clientId: config.googleClientId,
                    redirectUri: window.location.origin + '/auth/google/callback',
                    scope: 'profile email'
                },
                github: {
                    clientId: config.githubClientId,
                    redirectUri: window.location.origin + '/auth/github/callback',
                    scope: 'user:email'
                }
            },
            
            loginWithProvider: (provider) => {
                const providerConfig = this.oauth.providers[provider];
                if (!providerConfig) throw new Error(`Provider ${provider} not configured`);
                
                const params = new URLSearchParams({
                    client_id: providerConfig.clientId,
                    redirect_uri: providerConfig.redirectUri,
                    response_type: 'code',
                    scope: providerConfig.scope
                });
                
                const authUrl = provider === 'google' 
                    ? `https://accounts.google.com/oauth/authorize?${params}`
                    : `https://github.com/login/oauth/authorize?${params}`;
                    
                window.location.href = authUrl;
            },
            
            handleCallback: () => {
                const urlParams = new URLSearchParams(window.location.search);
                const code = urlParams.get('code');
                
                if (code) {
                    return fetch(`${config.apiUrl}/auth/oauth/token`, {
                        method: 'POST',
                        headers: { 'Content-Type': 'application/json' },
                        body: JSON.stringify({ code })
                    })
                    .then(response => response.json())
                    .then(data => {
                        if (data.access_token) {
                            localStorage.setItem('oauthToken', data.access_token);
                            this.currentUser = data.user;
                            return { success: true, user: data.user };
                        }
                        return { success: false, error: 'Token exchange failed' };
                    });
                }
                return Promise.reject('No authorization code');
            },
            
            logout: () => {
                localStorage.removeItem('oauthToken');
                this.currentUser = null;
            },
            
            isAuthenticated: () => !!localStorage.getItem('oauthToken')
        };
    }
    
    // Unified authentication interface
    isAuthenticated() {
        if (this.strategy === 'jwt') return this.jwt.isAuthenticated();
        if (this.strategy === 'oauth') return this.oauth.isAuthenticated();
        if (this.strategy === 'both') {
            return this.jwt.isAuthenticated() || this.oauth.isAuthenticated();
        }
        return false;
    }
    
    logout() {
        if (this.jwt) this.jwt.logout();
        if (this.oauth) this.oauth.logout();
        this.currentUser = null;
        window.location.reload();
    }
    
    // Login methods
    loginWithCredentials(username, password) {
        if (!this.jwt) throw new Error('JWT authentication not enabled');
        return this.jwt.login(username, password);
    }
    
    loginWithGoogle() {
        if (!this.oauth) throw new Error('OAuth authentication not enabled');
        return this.oauth.loginWithProvider('google');
    }
    
    loginWithGitHub() {
        if (!this.oauth) throw new Error('OAuth authentication not enabled');
        return this.oauth.loginWithProvider('github');
    }
    
    handleOAuthCallback() {
        if (!this.oauth) throw new Error('OAuth authentication not enabled');
        return this.oauth.handleCallback();
    }
}

const auth = new AuthManager();

// Main app function
function initApp() {
    console.log(`Initializing app with ${config.authStrategy} authentication...`);
    
    // Handle OAuth callback
    if (window.location.search.includes('code=')) {
        auth.handleOAuthCallback()
            .then(result => {
                if (result.success) {
                    console.log('OAuth login successful:', result.user);
                    window.history.replaceState({}, document.title, window.location.pathname);
                    setupMainApp();
                } else {
                    console.error('OAuth login failed:', result.error);
                    showLoginForm();
                }
            })
            .catch(error => {
                console.error('OAuth callback error:', error);
                showLoginForm();
            });
    } else if (auth.isAuthenticated()) {
        setupMainApp();
    } else {
        showLoginForm();
    }
}

function setupMainApp() {
    setupEventListeners();
    loadUserData();
    showMainInterface();
}

function setupEventListeners() {
    console.log('Setting up event listeners...');
    
    // JWT login form
    const loginForm = document.getElementById('loginForm');
    if (loginForm) {
        loginForm.addEventListener('submit', handleJWTLogin);
    }
    
    // OAuth buttons
    const googleBtn = document.getElementById('googleLogin');
    if (googleBtn) {
        googleBtn.addEventListener('click', () => auth.loginWithGoogle());
    }
    
    const githubBtn = document.getElementById('githubLogin');
    if (githubBtn) {
        githubBtn.addEventListener('click', () => auth.loginWithGitHub());
    }
    
    // Logout button
    const logoutBtn = document.getElementById('logoutBtn');
    if (logoutBtn) {
        logoutBtn.addEventListener('click', () => auth.logout());
    }
    
    // Switch between login methods
    const toggleBtn = document.getElementById('toggleAuthMethod');
    if (toggleBtn) {
        toggleBtn.addEventListener('click', toggleAuthMethod);
    }
}

function handleJWTLogin(event) {
    event.preventDefault();
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    
    auth.loginWithCredentials(username, password)
        .then(result => {
            if (result.success) {
                setupMainApp();
            } else {
                alert('Login failed: ' + result.error);
            }
        })
        .catch(error => {
            console.error('Login error:', error);
            alert('Login failed');
        });
}

let showingJWTForm = true;

function toggleAuthMethod() {
    showingJWTForm = !showingJWTForm;
    showLoginForm();
}

function showLoginForm() {
    const jwtEnabled = config.authStrategy === 'jwt' || config.authStrategy === 'both';
    const oauthEnabled = config.authStrategy === 'oauth' || config.authStrategy === 'both';
    
    let loginHTML = '<div id="loginContainer"><h2>Login</h2>';
    
    if (config.authStrategy === 'both') {
        loginHTML += `
            <div id="authMethodToggle">
                <button id="toggleAuthMethod">
                    Switch to ${showingJWTForm ? 'OAuth' : 'Credentials'}
                </button>
            </div>
        `;
    }
    
    if (showingJWTForm && jwtEnabled) {
        loginHTML += `
            <form id="loginForm">
                <input type="text" id="username" placeholder="Username" required>
                <input type="password" id="password" placeholder="Password" required>
                <button type="submit">Login with Credentials</button>
            </form>
        `;
    }
    
    if (!showingJWTForm && oauthEnabled) {
        loginHTML += `
            <div id="oauthOptions">
                <button id="googleLogin" class="oauth-btn google">Login with Google</button>
                <button id="githubLogin" class="oauth-btn github">Login with GitHub</button>
            </div>
        `;
    }
    
    loginHTML += '</div>';
    document.body.innerHTML = loginHTML;
    setupEventListeners();
}

function showMainInterface() {
    document.body.innerHTML = `
        <div id="mainApp">
            <header>
                <h1>${config.appName}</h1>
                <div id="userInfo">
                    Welcome, ${auth.currentUser?.name || 'User'}!
                    <button id="logoutBtn">Logout</button>
                </div>
            </header>
            <main>
                <p>Application content goes here...</p>
            </main>
        </div>
    `;
    setupEventListeners();
}

function loadUserData() {
    console.log('Loading user data...');
    // Load user-specific data based on authentication method
}

// Start app
initApp();
```

### 3.3 Commit della Risoluzione
```bash
git add src/app.js
git commit -m "Resolve authentication conflict by implementing hybrid system

CONFLICT RESOLUTION:
- Combined Alice's JWT authentication with Bob's OAuth system
- Created unified AuthManager class supporting both methods
- Added configuration option to choose auth strategy ('jwt', 'oauth', 'both')
- Implemented seamless switching between authentication methods
- Maintained backward compatibility with both implementations

FEATURES MERGED:
- JWT login with username/password (Alice's implementation)
- OAuth login with Google/GitHub (Bob's implementation)  
- Unified authentication interface
- Configurable authentication strategy
- Dynamic UI based on enabled authentication methods

The hybrid approach allows deployment flexibility and user choice
while preserving the work done by both developers."

git push origin feature/bob-oauth-integration
```

## Fase 4: Conflitti Complessi Multi-File

### 4.1 Scenario: Ristrutturazione Simultanea

**Alice** (Branch: `feature/modular-architecture`):
```bash
# Alice ristruttura in moduli separati
mkdir src/auth src/utils src/components
```

**Struttura Alice:**
```
src/
├── auth/
│   ├── jwt.js
│   ├── oauth.js  
│   └── auth-manager.js
├── utils/
│   ├── api.js
│   ├── storage.js
│   └── constants.js
├── components/
│   ├── login-form.js
│   ├── main-app.js
│   └── user-profile.js
└── app.js (ridotto)
```

**Bob** (Branch: `feature/component-refactor`):
```bash
# Bob ristruttura con approccio diverso
mkdir src/modules src/services src/views
```

**Struttura Bob:**
```
src/
├── modules/
│   ├── authentication.js
│   ├── user-management.js
│   └── app-core.js
├── services/
│   ├── api-service.js
│   ├── auth-service.js
│   └── storage-service.js
├── views/
│   ├── login-view.js
│   ├── dashboard-view.js
│   └── profile-view.js
└── main.js (nuovo entry point)
```

### 4.2 Risoluzione Architetturale

**Strategia di Merge:**
1. **Analisi delle strutture** - confrontare approcci
2. **Scelta architettura unificata** - decidere struttura finale
3. **Migration plan** - pianificare combinazione file
4. **Testing** - verificare funzionalità dopo merge

**Esempio di risoluzione:**
```bash
# Struttura finale unificata
src/
├── auth/                    # Da Alice
│   ├── strategies/          # Combinato
│   │   ├── jwt-strategy.js
│   │   └── oauth-strategy.js
│   ├── auth-manager.js      # Da Alice, migliorato
│   └── auth-service.js      # Da Bob, rinominato
├── services/                # Da Bob
│   ├── api-service.js
│   ├── storage-service.js
│   └── user-service.js      # Nuovo, combinato
├── components/              # Da Alice
│   ├── auth/                # Sottocategoria
│   │   ├── login-form.js
│   │   └── login-view.js    # Da Bob, integrato
│   ├── dashboard/           # Nuovo
│   │   ├── main-app.js      # Da Alice
│   │   └── dashboard-view.js # Da Bob
│   └── user/
│       ├── user-profile.js  # Da Alice
│       └── profile-view.js  # Da Bob, combinato
├── utils/                   # Da Alice
│   ├── constants.js
│   └── helpers.js           # Nuovo
├── app.js                   # Entry point unificato
└── main.js                  # Da Bob, rinominato bootstrap.js
```

## Fase 5: Best Practices per Conflitti

### 5.1 Prevenzione Conflitti
```bash
# 1. Sync frequente con main
git fetch origin
git rebase origin/main

# 2. Commit piccoli e frequenti
git add -p  # Staged commits parziali
git commit -m "Small focused change"

# 3. Comunicazione team
# - Coordinare modifiche ai file condivisi
# - Usare feature flags per modifiche breaking
# - Pianificare refactoring major
```

### 5.2 Strumenti per Risoluzione
```bash
# Git mergetool
git config --global merge.tool vscode
git mergetool

# Diff tools
git config --global diff.tool vscode
git difftool HEAD~1

# Visualizzazione conflitti
git log --oneline --graph --all
git show-branch
```

### 5.3 Checklist Post-Risoluzione
```markdown
## Post-Conflict Resolution Checklist

- [ ] **Codice compila** senza errori
- [ ] **Test passano** tutti
- [ ] **Funzionalità intatte** - nessuna regressione
- [ ] **Performance** non degradate
- [ ] **Documentazione aggiornata** se necessario
- [ ] **Team notificato** della risoluzione
- [ ] **Merge commit** ha messaggio descrittivo
- [ ] **Branch cleanup** - cancellare branch non necessari
```

## Deliverables dell'Esercizio

### Cosa Consegnare:
1. **Repository finale** con:
   - Almeno 5 conflitti risolti
   - Storia commit pulita con risoluzioni documentate
   - Codice funzionante post-risoluzione

2. **Report conflitti** (file `CONFLICT_RESOLUTION.md`):
   - Descrizione di ogni conflitto
   - Strategia di risoluzione scelta
   - Ragionamento dietro le decisioni
   - Lessons learned

3. **Demo funzionante** dell'applicazione finale

### Criteri di Valutazione:
- **Qualità risoluzioni** (40%): Eleganza e correttezza delle soluzioni
- **Documentazione** (30%): Chiarezza nei messaggi di commit e report
- **Teamwork** (20%): Collaborazione e comunicazione durante conflitti
- **Testing** (10%): Verifica che l'app funzioni dopo le risoluzioni

Questo esercizio prepara gli studenti a gestire conflitti reali nel mondo professionale, insegnando sia le competenze tecniche che quelle collaborative necessarie per il successo del team.
