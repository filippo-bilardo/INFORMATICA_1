# Esercizio 05: Risoluzione Avanzata di Conflitti durante Rebase

**🔴 Livello: AVANZATO**  
**⏱️ Tempo stimato: 45-60 minuti**  
**🎯 Focus: Gestione complessa di conflitti durante operazioni rebase**

## 📖 Scenario

Sei il team lead di un progetto web complesso. Durante lo sviluppo parallelo di diverse feature (autenticazione, API, frontend), si sono creati conflitti complessi che richiedono una strategia avanzata di risoluzione.

## 🎯 Obiettivi di Apprendimento

- **Strategia di risoluzione conflitti complessi**
- **Utilizzo di merge tools avanzati**
- **Gestione di conflitti a cascata**
- **Recupero da rebase falliti**
- **Analisi pre-rebase per evitare problemi**

## 🏗️ Setup Iniziale

```bash
#!/bin/bash
# Setup per esercizio avanzato conflitti rebase

# Crea directory per l'esercizio
mkdir -p ~/git-advanced-conflicts
cd ~/git-advanced-conflicts

# Inizializza repository
git init
git config user.name "Advanced Student"
git config user.email "advanced@student.com"

# Crea struttura base del progetto
mkdir -p {src/{auth,api,frontend},tests,docs}

# File principale dell'applicazione
cat > src/app.js << 'EOF'
// Main Application
const express = require('express');
const authModule = require('./auth/auth.js');
const apiModule = require('./api/api.js');
const frontendModule = require('./frontend/frontend.js');

class Application {
    constructor() {
        this.app = express();
        this.port = process.env.PORT || 3000;
        this.setupMiddleware();
    }

    setupMiddleware() {
        this.app.use(express.json());
        this.app.use('/auth', authModule);
        this.app.use('/api', apiModule);
        this.app.use('/', frontendModule);
    }

    start() {
        this.app.listen(this.port, () => {
            console.log(`Server running on port ${this.port}`);
        });
    }
}

module.exports = Application;
EOF

# File di configurazione
cat > src/config.js << 'EOF'
// Application Configuration
const config = {
    database: {
        host: 'localhost',
        port: 5432,
        name: 'myapp'
    },
    auth: {
        secret: 'default-secret',
        timeout: 3600
    },
    api: {
        version: '1.0.0',
        rateLimit: 100
    }
};

module.exports = config;
EOF

# Package.json base
cat > package.json << 'EOF'
{
    "name": "advanced-app",
    "version": "1.0.0",
    "description": "Advanced conflict resolution exercise",
    "main": "src/app.js",
    "scripts": {
        "start": "node src/app.js",
        "test": "jest"
    },
    "dependencies": {
        "express": "^4.18.0"
    }
}
EOF

# Commit iniziale
git add .
git commit -m "🚀 Initial project setup

- Basic Express application structure
- Configuration management
- Module organization for auth, api, frontend"

echo "✅ Setup base completato!"
echo "📁 Struttura creata in: $(pwd)"
echo "🔗 Repository Git inizializzato"
echo ""
echo "🔄 Prossimo passo: Creazione dei branch paralleli..."
```

## 📝 Fase 1: Creazione Sviluppo Parallelo Complesso

```bash
# === BRANCH AUTH TEAM ===
git checkout -b feature/auth-system
echo "🔐 Sviluppo sistema autenticazione..."

# Modifica significativa al sistema auth
cat > src/auth/auth.js << 'EOF'
// Advanced Authentication System
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');
const config = require('../config.js');

class AuthenticationManager {
    constructor() {
        this.secretKey = config.auth.secret;
        this.tokenExpiry = config.auth.timeout;
        this.users = new Map(); // In-memory store for demo
    }

    async register(username, password, email) {
        if (this.users.has(username)) {
            throw new Error('User already exists');
        }

        const hashedPassword = await bcrypt.hash(password, 10);
        const user = {
            username,
            email,
            password: hashedPassword,
            createdAt: new Date(),
            role: 'user'
        };

        this.users.set(username, user);
        return this.generateToken(user);
    }

    async login(username, password) {
        const user = this.users.get(username);
        if (!user) {
            throw new Error('User not found');
        }

        const isValid = await bcrypt.compare(password, user.password);
        if (!isValid) {
            throw new Error('Invalid credentials');
        }

        return this.generateToken(user);
    }

    generateToken(user) {
        return jwt.sign(
            { 
                username: user.username, 
                email: user.email,
                role: user.role 
            },
            this.secretKey,
            { expiresIn: this.tokenExpiry }
        );
    }

    verifyToken(token) {
        try {
            return jwt.verify(token, this.secretKey);
        } catch (error) {
            throw new Error('Invalid token');
        }
    }
}

module.exports = new AuthenticationManager();
EOF

# Aggiorna configurazione per auth
cat > src/config.js << 'EOF'
// Enhanced Configuration with Auth
const config = {
    database: {
        host: 'localhost',
        port: 5432,
        name: 'myapp',
        ssl: true
    },
    auth: {
        secret: process.env.JWT_SECRET || 'super-secure-secret-key',
        timeout: 7200, // 2 hours
        saltRounds: 12,
        requireEmailVerification: true
    },
    api: {
        version: '1.0.0',
        rateLimit: 100
    },
    security: {
        corsEnabled: true,
        allowedOrigins: ['http://localhost:3000']
    }
};

module.exports = config;
EOF

# Aggiorna app principale per auth
sed -i 's/this.setupMiddleware();/this.setupMiddleware();\n        this.setupAuth();/' src/app.js

cat >> src/app.js << 'EOF'

    setupAuth() {
        const authManager = require('./auth/auth.js');
        
        this.app.post('/auth/register', async (req, res) => {
            try {
                const { username, password, email } = req.body;
                const token = await authManager.register(username, password, email);
                res.json({ success: true, token });
            } catch (error) {
                res.status(400).json({ error: error.message });
            }
        });

        this.app.post('/auth/login', async (req, res) => {
            try {
                const { username, password } = req.body;
                const token = await authManager.login(username, password);
                res.json({ success: true, token });
            } catch (error) {
                res.status(401).json({ error: error.message });
            }
        });
    }
EOF

git add .
git commit -m "🔐 Implement advanced authentication system

- JWT-based authentication with bcrypt hashing
- User registration and login endpoints
- Enhanced security configuration
- Token verification middleware ready"

# === BRANCH API TEAM ===
git checkout main
git checkout -b feature/api-v2

echo "🔌 Sviluppo API v2..."

# Sistema API complesso
cat > src/api/api.js << 'EOF'
// Advanced API System v2
const express = require('express');
const config = require('../config.js');

class APIManager {
    constructor() {
        this.router = express.Router();
        this.version = config.api.version;
        this.rateLimit = config.api.rateLimit;
        this.setupRoutes();
        this.setupMiddleware();
    }

    setupMiddleware() {
        // Rate limiting middleware
        this.router.use((req, res, next) => {
            // Simple rate limiting logic
            req.apiUsage = (req.apiUsage || 0) + 1;
            if (req.apiUsage > this.rateLimit) {
                return res.status(429).json({ 
                    error: 'Rate limit exceeded',
                    limit: this.rateLimit 
                });
            }
            next();
        });

        // API versioning
        this.router.use((req, res, next) => {
            res.setHeader('API-Version', this.version);
            next();
        });
    }

    setupRoutes() {
        // Users API
        this.router.get('/users', this.getUsers.bind(this));
        this.router.get('/users/:id', this.getUserById.bind(this));
        this.router.post('/users', this.createUser.bind(this));
        this.router.put('/users/:id', this.updateUser.bind(this));
        this.router.delete('/users/:id', this.deleteUser.bind(this));

        // Data API
        this.router.get('/data', this.getData.bind(this));
        this.router.post('/data', this.createData.bind(this));
        
        // Analytics API
        this.router.get('/analytics', this.getAnalytics.bind(this));
    }

    async getUsers(req, res) {
        try {
            // Mock user data
            const users = [
                { id: 1, name: 'John Doe', email: 'john@example.com' },
                { id: 2, name: 'Jane Smith', email: 'jane@example.com' }
            ];
            res.json({ success: true, data: users, version: this.version });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async getUserById(req, res) {
        try {
            const { id } = req.params;
            const user = { id: parseInt(id), name: 'User ' + id, email: `user${id}@example.com` };
            res.json({ success: true, data: user });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async createUser(req, res) {
        try {
            const userData = req.body;
            // Mock user creation
            const newUser = { id: Date.now(), ...userData };
            res.status(201).json({ success: true, data: newUser });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async updateUser(req, res) {
        try {
            const { id } = req.params;
            const updateData = req.body;
            const updatedUser = { id: parseInt(id), ...updateData };
            res.json({ success: true, data: updatedUser });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async deleteUser(req, res) {
        try {
            const { id } = req.params;
            res.json({ success: true, message: `User ${id} deleted` });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async getData(req, res) {
        try {
            const data = { items: [], total: 0, page: 1 };
            res.json({ success: true, data });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async createData(req, res) {
        try {
            const newData = { id: Date.now(), ...req.body };
            res.status(201).json({ success: true, data: newData });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async getAnalytics(req, res) {
        try {
            const analytics = {
                users: 150,
                activeUsers: 45,
                apiCalls: 1250,
                errors: 12
            };
            res.json({ success: true, data: analytics });
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    getRouter() {
        return this.router;
    }
}

module.exports = new APIManager().getRouter();
EOF

# Aggiorna configurazione per API
cat > src/config.js << 'EOF'
// Enhanced Configuration with API v2
const config = {
    database: {
        host: process.env.DB_HOST || 'localhost',
        port: process.env.DB_PORT || 5432,
        name: process.env.DB_NAME || 'myapp_v2',
        ssl: process.env.NODE_ENV === 'production'
    },
    auth: {
        secret: 'default-secret',
        timeout: 3600
    },
    api: {
        version: '2.0.0', // BREAKING CHANGE
        rateLimit: 200,   // Increased limit
        pagination: {
            defaultSize: 20,
            maxSize: 100
        },
        caching: {
            enabled: true,
            ttl: 300 // 5 minutes
        }
    },
    monitoring: {
        enabled: true,
        logLevel: 'info'
    }
};

module.exports = config;
EOF

git add .
git commit -m "🔌 Implement API v2 with advanced features

- Complete CRUD operations for users and data
- Rate limiting and API versioning
- Analytics endpoints
- Enhanced configuration for monitoring
- Pagination and caching support"

# === BRANCH FRONTEND TEAM ===
git checkout main
git checkout -b feature/frontend-redesign

echo "🎨 Sviluppo frontend redesign..."

# Sistema frontend moderno
cat > src/frontend/frontend.js << 'EOF'
// Modern Frontend System
const express = require('express');
const path = require('path');
const config = require('../config.js');

class FrontendManager {
    constructor() {
        this.router = express.Router();
        this.setupStaticFiles();
        this.setupRoutes();
    }

    setupStaticFiles() {
        // Serve static files
        this.router.use('/assets', express.static('public/assets'));
        this.router.use('/css', express.static('public/css'));
        this.router.use('/js', express.static('public/js'));
    }

    setupRoutes() {
        // Main pages
        this.router.get('/', this.renderHome.bind(this));
        this.router.get('/login', this.renderLogin.bind(this));
        this.router.get('/dashboard', this.renderDashboard.bind(this));
        this.router.get('/profile', this.renderProfile.bind(this));
        this.router.get('/admin', this.renderAdmin.bind(this));
        
        // API integration pages
        this.router.get('/users', this.renderUsers.bind(this));
        this.router.get('/analytics', this.renderAnalytics.bind(this));
    }

    renderHome(req, res) {
        const html = this.generatePage('Home', `
            <div class="hero-section">
                <h1>Welcome to Advanced App</h1>
                <p>Experience our modern, secure platform</p>
                <div class="cta-buttons">
                    <a href="/login" class="btn btn-primary">Login</a>
                    <a href="/dashboard" class="btn btn-secondary">Dashboard</a>
                </div>
            </div>
            <div class="features">
                <div class="feature-card">
                    <h3>🔐 Secure Authentication</h3>
                    <p>JWT-based security with bcrypt encryption</p>
                </div>
                <div class="feature-card">
                    <h3>🔌 RESTful API</h3>
                    <p>Complete CRUD operations with rate limiting</p>
                </div>
                <div class="feature-card">
                    <h3>📊 Real-time Analytics</h3>
                    <p>Monitor your application performance</p>
                </div>
            </div>
        `);
        res.send(html);
    }

    renderLogin(req, res) {
        const html = this.generatePage('Login', `
            <div class="login-container">
                <h2>Login to Your Account</h2>
                <form id="loginForm" class="auth-form">
                    <div class="form-group">
                        <label for="username">Username:</label>
                        <input type="text" id="username" name="username" required>
                    </div>
                    <div class="form-group">
                        <label for="password">Password:</label>
                        <input type="password" id="password" name="password" required>
                    </div>
                    <button type="submit" class="btn btn-primary">Login</button>
                </form>
                <p class="auth-link">Don't have an account? <a href="/register">Register here</a></p>
            </div>
        `);
        res.send(html);
    }

    renderDashboard(req, res) {
        const html = this.generatePage('Dashboard', `
            <div class="dashboard">
                <h2>Dashboard</h2>
                <div class="stats-grid">
                    <div class="stat-card">
                        <h3>Users</h3>
                        <span class="stat-number" id="userCount">Loading...</span>
                    </div>
                    <div class="stat-card">
                        <h3>API Calls</h3>
                        <span class="stat-number" id="apiCount">Loading...</span>
                    </div>
                    <div class="stat-card">
                        <h3>Active Sessions</h3>
                        <span class="stat-number" id="sessionCount">Loading...</span>
                    </div>
                </div>
                <div class="recent-activity">
                    <h3>Recent Activity</h3>
                    <ul id="activityList">
                        <li>Loading activity...</li>
                    </ul>
                </div>
            </div>
        `);
        res.send(html);
    }

    renderProfile(req, res) {
        const html = this.generatePage('Profile', `
            <div class="profile-container">
                <h2>User Profile</h2>
                <div class="profile-section">
                    <h3>Personal Information</h3>
                    <form id="profileForm">
                        <div class="form-group">
                            <label for="displayName">Display Name:</label>
                            <input type="text" id="displayName" name="displayName">
                        </div>
                        <div class="form-group">
                            <label for="email">Email:</label>
                            <input type="email" id="email" name="email">
                        </div>
                        <button type="submit" class="btn btn-primary">Update Profile</button>
                    </form>
                </div>
            </div>
        `);
        res.send(html);
    }

    renderAdmin(req, res) {
        const html = this.generatePage('Admin Panel', `
            <div class="admin-panel">
                <h2>Administration</h2>
                <div class="admin-sections">
                    <div class="admin-card">
                        <h3>User Management</h3>
                        <p>Manage user accounts and permissions</p>
                        <a href="/admin/users" class="btn btn-secondary">Manage Users</a>
                    </div>
                    <div class="admin-card">
                        <h3>System Settings</h3>
                        <p>Configure application settings</p>
                        <a href="/admin/settings" class="btn btn-secondary">Settings</a>
                    </div>
                </div>
            </div>
        `);
        res.send(html);
    }

    renderUsers(req, res) {
        const html = this.generatePage('Users', `
            <div class="users-page">
                <h2>User Management</h2>
                <div class="users-controls">
                    <button class="btn btn-primary" id="addUserBtn">Add New User</button>
                    <input type="search" placeholder="Search users..." id="userSearch">
                </div>
                <div class="users-table">
                    <table id="usersTable">
                        <thead>
                            <tr>
                                <th>ID</th>
                                <th>Name</th>
                                <th>Email</th>
                                <th>Actions</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr><td colspan="4">Loading users...</td></tr>
                        </tbody>
                    </table>
                </div>
            </div>
        `);
        res.send(html);
    }

    renderAnalytics(req, res) {
        const html = this.generatePage('Analytics', `
            <div class="analytics-page">
                <h2>Analytics Dashboard</h2>
                <div class="analytics-grid">
                    <div class="chart-container">
                        <h3>API Usage</h3>
                        <div id="apiChart">Chart will be rendered here</div>
                    </div>
                    <div class="chart-container">
                        <h3>User Activity</h3>
                        <div id="userChart">Chart will be rendered here</div>
                    </div>
                </div>
            </div>
        `);
        res.send(html);
    }

    generatePage(title, content) {
        return `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>${title} - Advanced App</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { 
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            line-height: 1.6; 
            color: #333;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }
        .container { max-width: 1200px; margin: 0 auto; padding: 20px; }
        .header { background: rgba(255,255,255,0.1); padding: 1rem; margin-bottom: 2rem; border-radius: 10px; }
        .nav { display: flex; gap: 1rem; justify-content: center; }
        .nav a { color: white; text-decoration: none; padding: 0.5rem 1rem; border-radius: 5px; background: rgba(255,255,255,0.2); }
        .nav a:hover { background: rgba(255,255,255,0.3); }
        .main-content { background: white; padding: 2rem; border-radius: 10px; box-shadow: 0 10px 30px rgba(0,0,0,0.2); }
        .btn { display: inline-block; padding: 0.75rem 1.5rem; border: none; border-radius: 5px; text-decoration: none; cursor: pointer; transition: all 0.3s; }
        .btn-primary { background: #007bff; color: white; }
        .btn-secondary { background: #6c757d; color: white; }
        .btn:hover { transform: translateY(-2px); box-shadow: 0 5px 15px rgba(0,0,0,0.2); }
        .form-group { margin-bottom: 1rem; }
        .form-group label { display: block; margin-bottom: 0.5rem; font-weight: bold; }
        .form-group input { width: 100%; padding: 0.75rem; border: 1px solid #ddd; border-radius: 5px; }
        .hero-section { text-align: center; padding: 3rem 0; }
        .hero-section h1 { font-size: 3rem; margin-bottom: 1rem; }
        .cta-buttons { margin-top: 2rem; }
        .features { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 2rem; margin-top: 3rem; }
        .feature-card { padding: 2rem; border: 1px solid #eee; border-radius: 10px; text-align: center; }
        .stats-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 1rem; margin-bottom: 2rem; }
        .stat-card { background: #f8f9fa; padding: 1.5rem; border-radius: 10px; text-align: center; }
        .stat-number { font-size: 2rem; font-weight: bold; color: #007bff; }
        .dashboard h2, .profile-container h2, .admin-panel h2 { margin-bottom: 2rem; color: #333; }
        table { width: 100%; border-collapse: collapse; margin-top: 1rem; }
        th, td { padding: 1rem; text-align: left; border-bottom: 1px solid #eee; }
        th { background: #f8f9fa; font-weight: bold; }
    </style>
</head>
<body>
    <div class="container">
        <header class="header">
            <nav class="nav">
                <a href="/">Home</a>
                <a href="/dashboard">Dashboard</a>
                <a href="/users">Users</a>
                <a href="/analytics">Analytics</a>
                <a href="/profile">Profile</a>
                <a href="/admin">Admin</a>
            </nav>
        </header>
        <main class="main-content">
            ${content}
        </main>
    </div>
    <script>
        // Basic frontend JavaScript
        document.addEventListener('DOMContentLoaded', function() {
            // Load dynamic content
            if (document.getElementById('userCount')) {
                loadDashboardStats();
            }
            if (document.getElementById('usersTable')) {
                loadUsersTable();
            }
            
            // Form handling
            const loginForm = document.getElementById('loginForm');
            if (loginForm) {
                loginForm.addEventListener('submit', handleLogin);
            }
        });

        async function loadDashboardStats() {
            try {
                const response = await fetch('/api/analytics');
                const data = await response.json();
                if (data.success) {
                    document.getElementById('userCount').textContent = data.data.users;
                    document.getElementById('apiCount').textContent = data.data.apiCalls;
                    document.getElementById('sessionCount').textContent = data.data.activeUsers;
                }
            } catch (error) {
                console.error('Failed to load stats:', error);
            }
        }

        async function loadUsersTable() {
            try {
                const response = await fetch('/api/users');
                const data = await response.json();
                if (data.success) {
                    const tbody = document.querySelector('#usersTable tbody');
                    tbody.innerHTML = data.data.map(user => `
                        <tr>
                            <td>${user.id}</td>
                            <td>${user.name}</td>
                            <td>${user.email}</td>
                            <td>
                                <button class="btn btn-secondary" onclick="editUser(${user.id})">Edit</button>
                                <button class="btn btn-danger" onclick="deleteUser(${user.id})">Delete</button>
                            </td>
                        </tr>
                    `).join('');
                }
            } catch (error) {
                console.error('Failed to load users:', error);
            }
        }

        async function handleLogin(event) {
            event.preventDefault();
            const formData = new FormData(event.target);
            const credentials = {
                username: formData.get('username'),
                password: formData.get('password')
            };

            try {
                const response = await fetch('/auth/login', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(credentials)
                });
                const data = await response.json();
                
                if (data.success) {
                    localStorage.setItem('token', data.token);
                    window.location.href = '/dashboard';
                } else {
                    alert('Login failed: ' + data.error);
                }
            } catch (error) {
                alert('Login error: ' + error.message);
            }
        }
    </script>
</body>
</html>
        `;
    }

    getRouter() {
        return this.router;
    }
}

module.exports = new FrontendManager().getRouter();
EOF

# Aggiorna configurazione per frontend
cat > src/config.js << 'EOF'
// Complete Configuration with Frontend
const config = {
    database: {
        host: 'localhost',
        port: 5432,
        name: 'myapp'
    },
    auth: {
        secret: 'default-secret',
        timeout: 3600
    },
    api: {
        version: '1.0.0',
        rateLimit: 100
    },
    frontend: {
        theme: 'modern',
        features: {
            userManagement: true,
            analytics: true,
            adminPanel: true
        },
        ui: {
            primaryColor: '#007bff',
            secondaryColor: '#6c757d',
            animations: true
        }
    },
    performance: {
        caching: true,
        compression: true,
        minification: process.env.NODE_ENV === 'production'
    }
};

module.exports = config;
EOF

# Aggiorna app principale per frontend
cat > src/app.js << 'EOF'
// Enhanced Application with Frontend Integration
const express = require('express');
const authModule = require('./auth/auth.js');
const apiModule = require('./api/api.js');
const frontendModule = require('./frontend/frontend.js');

class Application {
    constructor() {
        this.app = express();
        this.port = process.env.PORT || 3000;
        this.setupMiddleware();
        this.setupRoutes();
    }

    setupMiddleware() {
        this.app.use(express.json());
        this.app.use(express.urlencoded({ extended: true }));
        
        // CORS for frontend development
        this.app.use((req, res, next) => {
            res.header('Access-Control-Allow-Origin', '*');
            res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept, Authorization');
            res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
            next();
        });
    }

    setupRoutes() {
        // API routes
        this.app.use('/api', apiModule);
        
        // Authentication routes  
        this.app.use('/auth', authModule);
        
        // Frontend routes (should be last)
        this.app.use('/', frontendModule);
        
        // Error handling
        this.app.use((err, req, res, next) => {
            console.error(err.stack);
            res.status(500).json({ 
                error: 'Internal server error',
                message: process.env.NODE_ENV === 'development' ? err.message : 'Something went wrong'
            });
        });
    }

    start() {
        this.app.listen(this.port, () => {
            console.log(`🚀 Advanced App running on port ${this.port}`);
            console.log(`📱 Frontend: http://localhost:${this.port}`);
            console.log(`🔌 API: http://localhost:${this.port}/api`);
            console.log(`🔐 Auth: http://localhost:${this.port}/auth`);
        });
    }
}

module.exports = Application;
EOF

git add .
git commit -m "🎨 Implement modern frontend redesign

- Complete UI system with modern styling
- User management interface
- Dashboard with real-time stats
- Admin panel for system management
- Responsive design with CSS Grid
- JavaScript integration for API calls"

echo "✅ Sviluppo parallelo completato!"
echo ""
echo "📊 Situazione attuale:"
echo "🌿 main: Versione base"
echo "🔐 feature/auth-system: Sistema autenticazione avanzato"
echo "🔌 feature/api-v2: API v2 con breaking changes"
echo "🎨 feature/frontend-redesign: Frontend moderno"
echo ""
echo "⚠️  CONFLITTI ATTESI durante il rebase!"
echo "🎯 Obiettivo: Gestire conflitti complessi in modo strategico"
```

## 🔥 Fase 2: Creazione Conflitti Strategici

```bash
# Torniamo al main e creiamo modifiche che genereranno conflitti complessi
git checkout main

echo "🔥 Simulazione modifiche urgenti sul main (hotfix critici)..."

# Hotfix critico per sicurezza che modifica config.js
cat > src/config.js << 'EOF'
// HOTFIX: Critical Security Update
const config = {
    database: {
        host: process.env.DB_HOST || 'localhost',
        port: process.env.DB_PORT || 5432,
        name: process.env.DB_NAME || 'myapp_secure',
        ssl: true, // FORCED SSL
        connectionTimeout: 5000
    },
    auth: {
        secret: process.env.JWT_SECRET || 'MUST-CHANGE-IN-PRODUCTION',
        timeout: 1800, // Reduced to 30 minutes for security
        maxLoginAttempts: 3,
        lockoutDuration: 900 // 15 minutes lockout
    },
    api: {
        version: '1.1.0', // Security patch version
        rateLimit: 50,    // Reduced for security
        requireAuth: true // NEW: All API calls require auth
    },
    security: {
        httpOnly: true,
        secure: process.env.NODE_ENV === 'production',
        sameSite: 'strict',
        contentSecurityPolicy: true
    }
};

module.exports = config;
EOF

# Hotfix per app.js - aggiunge middleware di sicurezza
sed -i '/this.setupMiddleware();/a\        this.setupSecurity();' src/app.js

cat >> src/app.js << 'EOF'

    setupSecurity() {
        // Security headers
        this.app.use((req, res, next) => {
            res.setHeader('X-Content-Type-Options', 'nosniff');
            res.setHeader('X-Frame-Options', 'DENY');
            res.setHeader('X-XSS-Protection', '1; mode=block');
            next();
        });
        
        // Request logging for security audit
        this.app.use((req, res, next) => {
            console.log(`${new Date().toISOString()} - ${req.method} ${req.path} - IP: ${req.ip}`);
            next();
        });
    }
EOF

git add .
git commit -m "🚨 HOTFIX: Critical security updates

- Enhanced database security with forced SSL
- Reduced session timeout for security
- API rate limiting reduced
- Security headers middleware
- Request logging for audit trail
- Lockout mechanism for failed logins"

# Altro hotfix che modifica package.json
cat > package.json << 'EOF'
{
    "name": "advanced-app",
    "version": "1.1.1",
    "description": "Advanced conflict resolution exercise - SECURITY PATCHED",
    "main": "src/app.js",
    "scripts": {
        "start": "node src/app.js",
        "test": "jest",
        "security-check": "npm audit",
        "lint": "eslint src/",
        "prod": "NODE_ENV=production node src/app.js"
    },
    "dependencies": {
        "express": "^4.18.2",
        "helmet": "^6.1.5",
        "rate-limiter-flexible": "^2.4.1"
    },
    "devDependencies": {
        "jest": "^29.5.0",
        "eslint": "^8.40.0"
    },
    "engines": {
        "node": ">=16.0.0"
    }
}
EOF

git add .
git commit -m "🔧 Update dependencies and scripts for security

- Added security-focused dependencies
- Enhanced npm scripts for production
- Node.js version requirement for security
- Development tools for code quality"

echo "✅ Hotfix critici applicati al main!"
```

## 🎯 Fase 3: Strategia di Risoluzione Conflitti

**Ora inizia il vero esercizio! Segui questa strategia step-by-step:**

### Step 1: Analisi Pre-Rebase

```bash
echo "🔍 FASE ANALISI: Comprendiamo i conflitti prima di iniziare"

# 1. Analizza le differenze tra branch
echo "📊 Differenze tra main e feature/auth-system:"
git diff main feature/auth-system src/config.js

echo -e "\n📊 Differenze tra main e feature/api-v2:"
git diff main feature/api-v2 src/config.js

echo -e "\n📊 Differenze tra main e feature/frontend-redesign:"
git diff main feature/frontend-redesign src/config.js

# 2. Identifica i file che causeranno conflitti
echo -e "\n🎯 File che causeranno conflitti:"
echo "- src/config.js (modificato da tutti i branch)"
echo "- src/app.js (modificato da auth e frontend)"
echo "- package.json (modificato da main e api)"

# 3. Strategia di merge
echo -e "\n📋 STRATEGIA CONSIGLIATA:"
echo "1. Inizia con feature/auth-system (meno conflitti)"
echo "2. Poi feature/api-v2 (conflitti moderati)"
echo "3. Infine feature/frontend-redesign (possibili cascate)"
echo "4. Usa 'git rebase --interactive' per cleaning"
```

### Step 2: Rebase con Gestione Conflitti Avanzata

```bash
echo -e "\n🚀 INIZIO REBASE STRATEGICO"

# Backup di sicurezza
git tag backup-before-rebase

# Rebase del primo branch (auth)
git checkout feature/auth-system
echo "🔐 Rebase del sistema auth su main aggiornato..."

# QUESTO COMANDO CAUSERÀ CONFLITTI!
git rebase main

# A questo punto Git si fermerà per i conflitti
echo "⚠️  CONFLITTO ATTESO! Ora risolvi manualmente:"
echo ""
echo "📝 ISTRUZIONI PER RISOLUZIONE:"
echo "1. Apri src/config.js in un editor"
echo "2. Cerca i marker di conflitto: <<<<<<< HEAD"
echo "3. Scegli quali configurazioni mantenere"
echo "4. Combina logicamente le funzionalità"
echo "5. Rimuovi tutti i marker di conflitto"
echo "6. git add src/config.js"
echo "7. git rebase --continue"
echo ""
echo "🎯 OBIETTIVO: Mantieni sicurezza del main + funzionalità auth"
```

**⚠️ PAUSA INTERATTIVA**: Risolvi i conflitti manualmente prima di continuare!

### Step 3: Tecniche Avanzate di Risoluzione

```bash
# Dopo aver risolto i conflitti del primo rebase...

echo "🔧 Tecniche avanzate per conflitti complessi:"

# 1. Usa merge tool per conflitti complessi
echo "💡 TIP: Per conflitti molto complessi, usa:"
echo "git mergetool"
echo "# Oppure configura un merge tool specifico:"
echo "git config merge.tool vimdiff"
echo "git config merge.tool code"  # Per VS Code

# 2. Analizza il conflitto con blame
echo -e "\n💡 TIP: Per capire chi ha modificato cosa:"
echo "git blame src/config.js"

# 3. Usa diff con more context
echo -e "\n💡 TIP: Per vedere più contesto:"
echo "git diff -U10"  # 10 righe di contesto invece di 3

# 4. Vedi i cambiamenti in modo più chiaro
echo -e "\n💡 TIP: Per una vista migliore delle differenze:"
echo "git diff --word-diff"
echo "git diff --color-words"

# 5. Strategia per conflitti a cascata
echo -e "\n🔗 STRATEGIA CONFLITTI A CASCATA:"
echo "1. Risolvi i conflitti base (config.js)"
echo "2. Testa che l'applicazione funzioni"
echo "3. Procedi con il prossimo rebase"
echo "4. Se emergono nuovi conflitti, usa 'git show ORIG_HEAD' per vedere lo stato precedente"
```

### Step 4: Rebase del Secondo Branch

```bash
# Procedi con il secondo branch
git checkout feature/api-v2
echo "🔌 Rebase API v2 su feature/auth-system integrato..."

# Rebase sul branch auth già integrato
git rebase feature/auth-system

echo "⚠️  POSSIBILI CONFLITTI PIÙ COMPLESSI!"
echo ""
echo "📝 GUIDA RISOLUZIONE API v2:"
echo "1. I conflitti ora includono ANCHE le modifiche auth"
echo "2. Mantieni la versione API 2.0.0 (breaking change intenzionale)"
echo "3. Integra i nuovi endpoint con il sistema auth"
echo "4. Assicurati che rate limiting sia compatibile"
echo "5. Verifica che pagination e caching funzionino"
echo ""
echo "🎯 OBIETTIVO: API v2 + Auth + Sicurezza main"
```

### Step 5: Rebase Finale e Cleanup

```bash
# Infine il frontend
git checkout feature/frontend-redesign
echo "🎨 Rebase finale del frontend su API v2 + Auth..."

git rebase feature/api-v2

echo "⚠️  CONFLITTI MASSIMI - TUTTI I SISTEMI INTEGRATI!"
echo ""
echo "📝 GUIDA RISOLUZIONE FINALE:"
echo "1. Ora devi integrare TUTTO: Auth + API v2 + Frontend + Sicurezza"
echo "2. Il file app.js potrebbe avere conflitti complessi"
echo "3. Assicurati che le route siano nell'ordine corretto"
echo "4. Verifica che l'auth middleware funzioni con API v2"
echo "5. Test manuale necessario dopo ogni risoluzione"
echo ""
echo "🎯 OBIETTIVO FINALE: Sistema completo e funzionante"

# Dopo tutti i rebase, merge tutto nel main
git checkout main
git merge feature/frontend-redesign --no-ff -m "🚀 Integrate all features: Auth + API v2 + Frontend + Security

- Advanced authentication system with JWT and bcrypt
- API v2 with breaking changes and enhanced features  
- Modern frontend with responsive design
- Critical security updates and monitoring
- Complete integration of all systems"

echo "✅ REBASE COMPLETO!"
```

## 🧪 Fase 4: Test e Validazione

```bash
echo "🧪 FASE TEST: Verifica integrazione completa"

# Test che l'applicazione si avvii
echo "🚀 Test avvio applicazione..."
timeout 10s node src/app.js &
APP_PID=$!
sleep 3

if ps -p $APP_PID > /dev/null; then
    echo "✅ Applicazione avviata correttamente!"
    kill $APP_PID
else
    echo "❌ Errore nell'avvio - debug necessario"
fi

# Verifica struttura finale
echo -e "\n📁 Struttura finale del progetto:"
find src -name "*.js" -exec echo "📄 {}" \;

# Verifica configurazione finale
echo -e "\n⚙️  Configurazione finale:"
node -e "const config = require('./src/config.js'); console.log(JSON.stringify(config, null, 2))"

# Test dei moduli
echo -e "\n🔍 Test import moduli:"
node -e "
try {
    const auth = require('./src/auth/auth.js');
    const api = require('./src/api/api.js');
    const frontend = require('./src/frontend/frontend.js');
    console.log('✅ Tutti i moduli importati correttamente');
} catch (error) {
    console.log('❌ Errore import:', error.message);
}
"
```

## 📚 Fase 5: Analisi e Apprendimento

### Domande di Autovalutazione

1. **🎯 Strategia di Risoluzione**
   - Quale ordine di rebase hai seguito e perché?
   - Come hai gestito i conflitti a cascata?
   - Quali tecniche hai trovato più efficaci?

2. **⚠️ Gestione Errori**
   - Hai dovuto usare `git rebase --abort` in qualche momento?
   - Come hai recuperato da situazioni complicate?
   - Hai usato il backup tag creato all'inizio?

3. **🔧 Tecniche Avanzate**
   - Hai usato merge tool esterni?
   - Come hai analizzato le differenze complesse?
   - Quali comandi Git ti sono stati più utili?

### Comandi di Emergenza

```bash
# Se qualcosa va storto durante l'esercizio:

# 1. Annulla rebase in corso
git rebase --abort

# 2. Torna al backup iniziale
git reset --hard backup-before-rebase

# 3. Vedi lo stato del rebase
git status
git rebase --show-current-patch

# 4. Salta un commit problematico (ATTENZIONE!)
git rebase --skip

# 5. Modifica il commit durante rebase
git rebase --edit-todo

# 6. Visualizza conflitti rimanenti
git diff --name-only --diff-filter=U
```

## 🏆 Obiettivi di Valutazione

Al termine dell'esercizio dovresti aver dimostrato:

- ✅ **Gestione conflitti complessi** - Risoluzione strategica di conflitti multi-file
- ✅ **Analisi pre-rebase** - Capacità di prevedere e preparare i conflitti  
- ✅ **Uso merge tools** - Utilizzo efficace di strumenti di merge avanzati
- ✅ **Recovery da errori** - Gestione di situazioni problematiche durante rebase
- ✅ **Integrazione sistemica** - Mantenimento funzionalità durante merge complessi
- ✅ **Test post-integrazione** - Validazione del sistema finale integrato

## 🎯 Challenges Bonus

Se completi l'esercizio base, prova questi challenges aggiuntivi:

1. **🔄 Interactive Rebase Cleanup**: Usa `git rebase -i` per riorganizzare i commit finali
2. **🌿 Branch Strategy**: Proponi una strategia alternativa di branching per evitare questi conflitti
3. **🤖 Automation**: Scrivi uno script per automatizzare parte del processo di risoluzione
4. **📊 Conflict Analysis**: Crea un report dettagliato dei tipi di conflitti incontrati

---

**💡 Ricorda**: Questo esercizio simula scenari reali di sviluppo team complessi. Le competenze acquisite qui sono direttamente applicabili a progetti professionali!
