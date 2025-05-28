# Esercizio 3: Cherry-Pick Mastery

## 🎯 Obiettivo
Imparare a utilizzare `git cherry-pick` per selezionare e applicare commit specifici da un branch all'altro, gestendo scenari reali di hotfix, backporting e selective merging.

## 📋 Scenario
Stai gestendo un progetto con multiple versioni in produzione. Hai bisogno di applicare fix critici a versioni diverse, portare feature specifiche da branch sperimentali, e gestire rilasci selettivi senza fare merge completi.

## 🏗️ Setup Iniziale

```bash
#!/bin/bash
# Creazione ambiente multi-branch per cherry-pick
mkdir cherry-pick-exercise && cd cherry-pick-exercise
git init
git config user.name "Release Manager"
git config user.email "release@company.com"

echo "🏗️ Creazione ambiente multi-versione..."

# Setup progetto base
mkdir -p src/{core,features,utils} tests docs
cat > package.json << 'EOF'
{
  "name": "multi-version-app",
  "version": "1.0.0",
  "description": "App with multiple production versions",
  "main": "src/app.js",
  "scripts": {
    "test": "jest",
    "start": "node src/app.js"
  }
}
EOF

cat > src/app.js << 'EOF'
const express = require('express');
const app = express();

// Core functionality
app.get('/', (req, res) => {
  res.json({ message: 'Welcome to Multi-Version App v1.0.0' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', version: '1.0.0' });
});

module.exports = app;
EOF

cat > src/core/auth.js << 'EOF'
// Basic authentication module
const jwt = require('jsonwebtoken');

function validateToken(token) {
  // Basic validation - has security flaw
  return jwt.verify(token, 'weak-secret');
}

function generateToken(user) {
  return jwt.sign(user, 'weak-secret', { expiresIn: '1h' });
}

module.exports = { validateToken, generateToken };
EOF

git add .
git commit -m "Initial release v1.0.0 - Basic app with auth"

# Simulazione versioni di produzione
echo "📦 Creazione branch di produzione..."

# Release v1.1.0
cat > src/features/userProfile.js << 'EOF'
// User profile management
function getUserProfile(userId) {
  // Simulate database query
  return { id: userId, name: 'User' + userId, email: 'user@example.com' };
}

function updateUserProfile(userId, data) {
  // Update user profile
  console.log('Updating profile for user:', userId);
  return { ...getUserProfile(userId), ...data };
}

module.exports = { getUserProfile, updateUserProfile };
EOF

# Update main app
cat > src/app.js << 'EOF'
const express = require('express');
const { getUserProfile } = require('./features/userProfile');
const app = express();

app.use(express.json());

// Core functionality
app.get('/', (req, res) => {
  res.json({ message: 'Welcome to Multi-Version App v1.1.0' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', version: '1.1.0' });
});

// New feature
app.get('/profile/:id', (req, res) => {
  const profile = getUserProfile(req.params.id);
  res.json(profile);
});

module.exports = app;
EOF

# Update package.json version
sed -i 's/"version": "1.0.0"/"version": "1.1.0"/' package.json

git add .
git commit -m "Release v1.1.0 - Add user profile feature"

# Create production branches
git branch production-v1.0 HEAD~1  # Points to v1.0.0
git branch production-v1.1 HEAD    # Points to v1.1.0

# Continue development on main
cat > src/features/notifications.js << 'EOF'
// Notification system
const notifications = [];

function addNotification(userId, message, type = 'info') {
  const notification = {
    id: Date.now(),
    userId,
    message,
    type,
    timestamp: new Date(),
    read: false
  };
  notifications.push(notification);
  return notification;
}

function getNotifications(userId) {
  return notifications.filter(n => n.userId === userId);
}

function markAsRead(notificationId) {
  const notification = notifications.find(n => n.id === notificationId);
  if (notification) {
    notification.read = true;
  }
  return notification;
}

module.exports = { addNotification, getNotifications, markAsRead };
EOF

git add .
git commit -m "Add notification system"

# Critical security fix
cat > src/core/auth.js << 'EOF'
// Authentication module with security fix
const jwt = require('jsonwebtoken');
const crypto = require('crypto');

// Generate secure secret
const SECRET = process.env.JWT_SECRET || crypto.randomBytes(64).toString('hex');

function validateToken(token) {
  try {
    // SECURITY FIX: Use secure secret and proper error handling
    return jwt.verify(token, SECRET);
  } catch (error) {
    throw new Error('Invalid token');
  }
}

function generateToken(user) {
  // SECURITY FIX: Use secure secret
  return jwt.sign(user, SECRET, { expiresIn: '1h' });
}

module.exports = { validateToken, generateToken };
EOF

git add .
git commit -m "SECURITY FIX: Use secure JWT secret instead of hardcoded weak secret"

# Performance improvement
cat > src/utils/cache.js << 'EOF'
// Simple in-memory cache
const cache = new Map();

function get(key) {
  const item = cache.get(key);
  if (item && item.expiry > Date.now()) {
    return item.value;
  }
  cache.delete(key);
  return null;
}

function set(key, value, ttl = 300000) { // 5 minutes default
  cache.set(key, {
    value,
    expiry: Date.now() + ttl
  });
}

function clear() {
  cache.clear();
}

module.exports = { get, set, clear };
EOF

# Update user profile to use cache
cat > src/features/userProfile.js << 'EOF'
// User profile management with caching
const cache = require('../utils/cache');

function getUserProfile(userId) {
  // Check cache first (performance improvement)
  const cached = cache.get(\`profile_\${userId}\`);
  if (cached) {
    return cached;
  }
  
  // Simulate database query
  const profile = { id: userId, name: 'User' + userId, email: 'user@example.com' };
  
  // Cache the result
  cache.set(\`profile_\${userId}\`, profile);
  return profile;
}

function updateUserProfile(userId, data) {
  // Update user profile and invalidate cache
  console.log('Updating profile for user:', userId);
  cache.set(\`profile_\${userId}\`, null); // Invalidate cache
  return { ...getUserProfile(userId), ...data };
}

module.exports = { getUserProfile, updateUserProfile };
EOF

git add .
git commit -m "PERFORMANCE: Add caching to user profile queries"

# Bug fix for notification timestamps
cat > src/features/notifications.js << 'EOF'
// Notification system with timezone fix
const notifications = [];

function addNotification(userId, message, type = 'info') {
  const notification = {
    id: Date.now(),
    userId,
    message,
    type,
    // BUG FIX: Use UTC timestamp for consistency
    timestamp: new Date().toISOString(),
    read: false
  };
  notifications.push(notification);
  return notification;
}

function getNotifications(userId) {
  return notifications.filter(n => n.userId === userId);
}

function markAsRead(notificationId) {
  const notification = notifications.find(n => n.id === notificationId);
  if (notification) {
    notification.read = true;
  }
  return notification;
}

module.exports = { addNotification, getNotifications, markAsRead };
EOF

git add .
git commit -m "BUG FIX: Use UTC timestamps for notification consistency"

# Experimental feature
git checkout -b experimental/realtime-features

cat > src/features/websocket.js << 'EOF'
// WebSocket implementation for real-time features
const WebSocket = require('ws');

class WebSocketManager {
  constructor() {
    this.clients = new Map();
    this.server = null;
  }

  initialize(port = 8080) {
    this.server = new WebSocket.Server({ port });
    
    this.server.on('connection', (ws, req) => {
      const clientId = this.generateClientId();
      this.clients.set(clientId, ws);
      
      ws.on('message', (message) => {
        this.handleMessage(clientId, message);
      });
      
      ws.on('close', () => {
        this.clients.delete(clientId);
      });
    });
  }

  generateClientId() {
    return 'client_' + Date.now() + '_' + Math.random().toString(36).substr(2, 9);
  }

  broadcast(message) {
    this.clients.forEach((client) => {
      if (client.readyState === WebSocket.OPEN) {
        client.send(JSON.stringify(message));
      }
    });
  }

  sendToClient(clientId, message) {
    const client = this.clients.get(clientId);
    if (client && client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(message));
    }
  }

  handleMessage(clientId, message) {
    try {
      const data = JSON.parse(message);
      // Handle different message types
      switch(data.type) {
        case 'ping':
          this.sendToClient(clientId, { type: 'pong' });
          break;
        default:
          console.log('Unknown message type:', data.type);
      }
    } catch (error) {
      console.error('Error parsing message:', error);
    }
  }
}

module.exports = WebSocketManager;
EOF

git add .
git commit -m "EXPERIMENTAL: Add WebSocket manager for real-time features"

# Real-time notifications integration
cat > src/features/realtimeNotifications.js << 'EOF'
// Real-time notification delivery
const { addNotification } = require('./notifications');
const WebSocketManager = require('./websocket');

class RealtimeNotificationService {
  constructor() {
    this.wsManager = new WebSocketManager();
    this.userConnections = new Map(); // userId -> clientId
  }

  initialize() {
    this.wsManager.initialize();
    console.log('Real-time notification service started');
  }

  registerUser(userId, clientId) {
    this.userConnections.set(userId, clientId);
  }

  sendNotificationToUser(userId, message, type = 'info') {
    // Add to database
    const notification = addNotification(userId, message, type);
    
    // Send real-time update if user is connected
    const clientId = this.userConnections.get(userId);
    if (clientId) {
      this.wsManager.sendToClient(clientId, {
        type: 'notification',
        data: notification
      });
    }
    
    return notification;
  }

  broadcastNotification(message, type = 'announcement') {
    this.wsManager.broadcast({
      type: 'broadcast_notification',
      data: { message, type, timestamp: new Date().toISOString() }
    });
  }
}

module.exports = RealtimeNotificationService;
EOF

git add .
git commit -m "EXPERIMENTAL: Add real-time notification delivery via WebSocket"

git checkout main

echo "✅ Ambiente multi-branch creato!"
echo "📊 Stato repository:"
git branch -v
echo -e "\n📈 Log principale:"
git log --oneline --graph --all
```

## 📝 Compiti da Svolgere

### Parte 1: Analisi dell'Ambiente

1. **Esamina la struttura dei branch:**
   ```bash
   git branch -v
   git log --oneline --graph --all
   ```

2. **Identifica i commit per tipo:**
   ```bash
   # Vedi tutti i commit con dettagli
   git log --oneline --all
   
   # Identifica:
   # - Security fixes (da applicare a tutte le versioni)
   # - Bug fixes (da backportare)
   # - Performance improvements (selettivi)
   # - Experimental features (da valutare)
   ```

### Parte 2: Cherry-Pick di Security Fix

3. **CRITICO: Applica il security fix a tutte le versioni di produzione**

   Il commit con messaggio "SECURITY FIX: Use secure JWT secret..." deve essere applicato a:
   - `production-v1.0`
   - `production-v1.1`

   ```bash
   # Prima identifica l'hash del commit del security fix
   git log --oneline | grep "SECURITY FIX"
   
   # Applica a production-v1.0
   git checkout production-v1.0
   git cherry-pick <security-fix-commit-hash>
   
   # Applica a production-v1.1  
   git checkout production-v1.1
   git cherry-pick <security-fix-commit-hash>
   ```

4. **Verifica che il fix sia stato applicato correttamente:**
   ```bash
   # Controlla il contenuto del file auth.js in entrambi i branch
   git checkout production-v1.0
   cat src/core/auth.js | grep "SECRET"
   
   git checkout production-v1.1
   cat src/core/auth.js | grep "SECRET"
   ```

### Parte 3: Cherry-Pick di Bug Fix

5. **Applica il bug fix delle timestamp UTC:**

   Il fix "BUG FIX: Use UTC timestamps..." dovrebbe essere applicato a `production-v1.1` (che ha le notifications):

   ```bash
   git checkout production-v1.1
   
   # Prima verifica se il branch ha il file notifications
   ls src/features/
   
   # Se non ha notifications.js, prima porta quella feature:
   git log --oneline main | grep "Add notification system"
   git cherry-pick <notification-system-commit-hash>
   
   # Poi applica il bug fix
   git log --oneline main | grep "BUG FIX: Use UTC"
   git cherry-pick <bug-fix-commit-hash>
   ```

### Parte 4: Cherry-Pick Selettivo di Performance

6. **Applica il performance improvement solo dove appropriato:**

   Il caching dovrebbe essere applicato solo a `production-v1.1`:

   ```bash
   git checkout production-v1.1
   
   # Identifica entrambi i commit del caching
   git log --oneline main | grep -E "(cache|PERFORMANCE)"
   
   # Applica il cache utility
   git cherry-pick <cache-utility-commit-hash>
   
   # Applica il performance improvement
   git cherry-pick <performance-commit-hash>
   ```

### Parte 5: Cherry-Pick con Risoluzione Conflitti

7. **Gestisci i conflitti che potrebbero emergere:**

   Se durante un cherry-pick ottieni conflitti:

   ```bash
   # Git ti mostrerà i file in conflitto
   git status
   
   # Risolvi manualmente i conflitti nei file indicati
   # Cerca i marker <<<<<<<, =======, >>>>>>>
   
   # Dopo aver risolto:
   git add .
   git cherry-pick --continue
   
   # Se vuoi abbandonare:
   git cherry-pick --abort
   ```

### Parte 6: Cherry-Pick Multipli

8. **Porta feature sperimentali selezionate:**

   Decidi se portare le feature WebSocket da `experimental/realtime-features`:

   ```bash
   # Vedi cosa c'è nel branch sperimentale
   git log --oneline experimental/realtime-features
   
   # Crea un nuovo branch per testare l'integrazione
   git checkout main
   git checkout -b feature/selective-realtime
   
   # Cherry-pick solo il WebSocket manager (non la notifica real-time)
   git cherry-pick <websocket-manager-commit-hash>
   
   # Testa che funzioni senza dipendenze problematiche
   ```

### Parte 7: Cherry-Pick Range

9. **Applica un range di commit:**

   Se vuoi applicare una sequenza di commit:

   ```bash
   # Sintassi per range (esclusive..inclusive)
   git cherry-pick <start-commit-hash>..<end-commit-hash>
   
   # Esempio: porta gli ultimi 2 commit da main a production-v1.1
   git checkout production-v1.1
   git cherry-pick HEAD~2..HEAD
   ```

## ✅ Risultati Attesi

### Alla Fine dell'Esercizio Dovresti Avere:

1. **production-v1.0**: 
   - Codice base originale
   - Security fix applicato

2. **production-v1.1**:
   - Feature user profile
   - Security fix applicato  
   - Bug fix timestamp applicato
   - Performance caching applicato

3. **main**:
   - Tutto lo sviluppo più recente

4. **feature/selective-realtime**:
   - Feature WebSocket selettiva

### Verifica Finale:

```bash
# Controlla che ogni branch abbia quello che dovrebbe
for branch in production-v1.0 production-v1.1 main feature/selective-realtime; do
  echo "=== Branch: $branch ==="
  git checkout $branch
  echo "Files in src/:"
  find src/ -name "*.js" | sort
  echo "Last 3 commits:"
  git log --oneline -3
  echo ""
done
```

## 🤔 Domande di Riflessione

1. **Strategia di Cherry-Pick:**
   - Quando è meglio cherry-pick vs merge completo?
   - Come decidi quali commit applicare a quali branch?

2. **Gestione Conflitti:**
   - Perché ci sono conflitti durante cherry-pick?
   - Come evitare conflitti frequenti?

3. **Sicurezza e Manutenzione:**
   - Come ti assicuri che i security fix arrivino a tutte le versioni?
   - Qual è il workflow per bug fixes critici?

## 🚨 Best Practices Apprese

1. **Order Matters**: L'ordine dei cherry-pick può causare conflitti
2. **Test After Each Pick**: Verifica che ogni commit funzioni nel contesto di destinazione  
3. **Document Changes**: Tieni traccia di quali commit sono stati applicati dove
4. **Automated Testing**: Ogni cherry-pick dovrebbe passare i test

## 🎉 Challenge Avanzato

1. **Automazione**: Scrivi uno script che applica automaticamente security fixes a tutti i branch di produzione
2. **Conflict Resolution**: Crea scenari con conflitti complessi e risolvi sistematicamente
3. **Integration**: Combina cherry-pick con rebase interattivo per ottimizzare il risultato

## 📚 Riferimenti

- [Guida Cherry-Pick](../guide/03-cherry-pick-guide.md)
- [Rebase vs Merge](../guide/04-rebase-vs-merge.md)
- [Esempi Pratici](../esempi/)
