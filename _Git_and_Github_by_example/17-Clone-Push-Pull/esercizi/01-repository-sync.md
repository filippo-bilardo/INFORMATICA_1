# Esercizio 01: Repository Synchronization Challenge

## 🎯 Obiettivo
Padroneggiare la sincronizzazione repository in scenari collaborativi reali, gestendo multiple remote, conflitti e workflow complessi.

## ⏱️ Durata Stimata
**45-60 minuti**

## 📋 Prerequisiti
- Repository GitHub personale
- Git configurato con SSH
- Comprensione base di clone/push/pull

## 🚀 Scenario
Sei il lead developer di un team che sta sviluppando una web app. Devi gestire sincronizzazione tra sviluppatori, staging e produzione, mantenendo la cronologia pulita e sicura.

## 📝 Task da Completare

### Task 1: Setup Multi-Remote Environment

```bash
# 1.1 Crea repository di test su GitHub
# Nome: team-sync-challenge
# Descrizione: Repository per testing sincronizzazione team

# 1.2 Clone e setup iniziale
git clone https://github.com/tuo-username/team-sync-challenge.git
cd team-sync-challenge

# 1.3 Setup file progetto iniziale
# Crea questi file con contenuto significativo:
```

**File da creare:**

`package.json`:
```json
{
  "name": "team-sync-challenge",
  "version": "1.0.0",
  "description": "App collaborativa per gestione task team",
  "main": "app.js",
  "scripts": {
    "start": "node app.js",
    "dev": "nodemon app.js",
    "test": "jest",
    "lint": "eslint ."
  },
  "dependencies": {
    "express": "^4.18.0",
    "cors": "^2.8.5",
    "helmet": "^6.0.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0",
    "jest": "^29.0.0",
    "eslint": "^8.0.0"
  }
}
```

`app.js`:
```javascript
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware di sicurezza
app.use(helmet());
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

// Simulazione database in memoria
let tasks = [
    { id: 1, title: 'Setup progetto', completed: true, assignee: 'Alice' },
    { id: 2, title: 'Implementare API', completed: false, assignee: 'Bob' },
    { id: 3, title: 'Design UI', completed: false, assignee: 'Carol' }
];

// Routes API
app.get('/api/tasks', (req, res) => {
    res.json({ success: true, data: tasks });
});

app.post('/api/tasks', (req, res) => {
    const { title, assignee } = req.body;
    
    if (!title || !assignee) {
        return res.status(400).json({ 
            success: false, 
            message: 'Title e assignee sono obbligatori' 
        });
    }
    
    const newTask = {
        id: tasks.length + 1,
        title,
        assignee,
        completed: false
    };
    
    tasks.push(newTask);
    res.status(201).json({ success: true, data: newTask });
});

app.listen(PORT, () => {
    console.log(`🚀 Server avviato su porta ${PORT}`);
});
```

`README.md`:
```markdown
# Team Sync Challenge

App collaborativa per gestione task del team di sviluppo.

## Features
- ✅ API REST per task management
- 🔒 Middleware di sicurezza
- 📱 Interfaccia responsive
- 🧪 Suite di test completa

## Quick Start

```bash
npm install
npm run dev
```

## Team
- **Alice**: Backend Developer
- **Bob**: Frontend Developer  
- **Carol**: UI/UX Designer
```

**🏁 Checkpoint 1**: Commit iniziale e push
```bash
git add .
git commit -m "feat: setup iniziale progetto team

- Configurazione Express.js con sicurezza
- API REST per gestione task
- Package.json con dipendenze development
- README con documentazione base"

git push origin main
```

### Task 2: Simulazione Team Collaboration

```bash
# 2.1 Simula sviluppatore "Alice" - Backend focus
git checkout -b feature/enhanced-api

# Migliora l'API con funzionalità avanzate
```

Modifica `app.js` aggiungendo:
```javascript
// Aggiungi dopo le route esistenti

// PUT /api/tasks/:id - Aggiorna task
app.put('/api/tasks/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const { title, assignee, completed } = req.body;
    
    const taskIndex = tasks.findIndex(t => t.id === id);
    
    if (taskIndex === -1) {
        return res.status(404).json({
            success: false,
            message: 'Task non trovato'
        });
    }
    
    // Update task
    if (title !== undefined) tasks[taskIndex].title = title;
    if (assignee !== undefined) tasks[taskIndex].assignee = assignee;
    if (completed !== undefined) tasks[taskIndex].completed = completed;
    
    res.json({ success: true, data: tasks[taskIndex] });
});

// DELETE /api/tasks/:id - Elimina task
app.delete('/api/tasks/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const taskIndex = tasks.findIndex(t => t.id === id);
    
    if (taskIndex === -1) {
        return res.status(404).json({
            success: false,
            message: 'Task non trovato'
        });
    }
    
    const deletedTask = tasks.splice(taskIndex, 1)[0];
    res.json({ success: true, data: deletedTask });
});

// GET /api/tasks/stats - Statistiche task
app.get('/api/tasks/stats', (req, res) => {
    const stats = {
        total: tasks.length,
        completed: tasks.filter(t => t.completed).length,
        pending: tasks.filter(t => !t.completed).length,
        byAssignee: tasks.reduce((acc, task) => {
            acc[task.assignee] = (acc[task.assignee] || 0) + 1;
            return acc;
        }, {})
    };
    
    res.json({ success: true, data: stats });
});
```

```bash
# Commit feature Alice
git add .
git commit -m "feat(api): implementate operazioni CRUD complete

- Endpoint PUT /api/tasks/:id per aggiornamenti
- Endpoint DELETE /api/tasks/:id per eliminazione
- Endpoint GET /api/tasks/stats per statistiche
- Validazione e gestione errori migliorata"

git push -u origin feature/enhanced-api

# 2.2 Torna a main per simulare "Bob" - Frontend
git checkout main
git checkout -b feature/frontend-dashboard
```

Crea `public/index.html`:
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Team Task Dashboard</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #f5f5f5;
            padding: 20px;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        .header {
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            margin-bottom: 20px;
        }
        
        .stats {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin-bottom: 20px;
        }
        
        .stat-card {
            background: white;
            padding: 20px;
            border-radius: 10px;
            text-align: center;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        .stat-number {
            font-size: 2rem;
            font-weight: bold;
            color: #4CAF50;
        }
        
        .tasks-container {
            background: white;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            overflow: hidden;
        }
        
        .tasks-header {
            background: #2196F3;
            color: white;
            padding: 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .task-item {
            padding: 15px 20px;
            border-bottom: 1px solid #eee;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .task-completed {
            background: #f0f8ff;
            text-decoration: line-through;
            opacity: 0.7;
        }
        
        .btn {
            padding: 8px 16px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            margin-left: 5px;
        }
        
        .btn-primary { background: #2196F3; color: white; }
        .btn-success { background: #4CAF50; color: white; }
        .btn-danger { background: #f44336; color: white; }
        
        .loading {
            text-align: center;
            padding: 40px;
            color: #666;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🚀 Team Task Dashboard</h1>
            <p>Gestione collaborativa task di sviluppo</p>
        </div>
        
        <div class="stats" id="stats">
            <div class="loading">Caricamento statistiche...</div>
        </div>
        
        <div class="tasks-container">
            <div class="tasks-header">
                <h2>📋 Task Attivi</h2>
                <button class="btn btn-primary" onclick="loadTasks()">🔄 Ricarica</button>
            </div>
            <div id="tasks-list">
                <div class="loading">Caricamento task...</div>
            </div>
        </div>
    </div>
    
    <script src="dashboard.js"></script>
</body>
</html>
```

Crea `public/dashboard.js`:
```javascript
class TaskDashboard {
    constructor() {
        this.tasks = [];
        this.stats = {};
        this.init();
    }
    
    async init() {
        await this.loadStats();
        await this.loadTasks();
    }
    
    async loadStats() {
        try {
            const response = await fetch('/api/tasks/stats');
            const result = await response.json();
            
            if (result.success) {
                this.stats = result.data;
                this.renderStats();
            }
        } catch (error) {
            console.error('Errore caricamento stats:', error);
        }
    }
    
    async loadTasks() {
        try {
            const response = await fetch('/api/tasks');
            const result = await response.json();
            
            if (result.success) {
                this.tasks = result.data;
                this.renderTasks();
            }
        } catch (error) {
            console.error('Errore caricamento tasks:', error);
        }
    }
    
    renderStats() {
        const statsContainer = document.getElementById('stats');
        
        statsContainer.innerHTML = `
            <div class="stat-card">
                <div class="stat-number">${this.stats.total}</div>
                <div>Task Totali</div>
            </div>
            <div class="stat-card">
                <div class="stat-number">${this.stats.completed}</div>
                <div>Completati</div>
            </div>
            <div class="stat-card">
                <div class="stat-number">${this.stats.pending}</div>
                <div>In Corso</div>
            </div>
            <div class="stat-card">
                <div class="stat-number">${Object.keys(this.stats.byAssignee).length}</div>
                <div>Membri Team</div>
            </div>
        `;
    }
    
    renderTasks() {
        const tasksContainer = document.getElementById('tasks-list');
        
        if (this.tasks.length === 0) {
            tasksContainer.innerHTML = '<div class="loading">Nessun task trovato</div>';
            return;
        }
        
        tasksContainer.innerHTML = this.tasks.map(task => `
            <div class="task-item ${task.completed ? 'task-completed' : ''}">
                <div>
                    <strong>${task.title}</strong><br>
                    <small>Assegnato a: ${task.assignee}</small>
                </div>
                <div>
                    <button class="btn btn-success" onclick="dashboard.toggleTask(${task.id})">
                        ${task.completed ? '↩️ Riapri' : '✅ Completa'}
                    </button>
                    <button class="btn btn-danger" onclick="dashboard.deleteTask(${task.id})">
                        🗑️ Elimina
                    </button>
                </div>
            </div>
        `).join('');
    }
    
    async toggleTask(taskId) {
        const task = this.tasks.find(t => t.id === taskId);
        if (!task) return;
        
        try {
            const response = await fetch(`/api/tasks/${taskId}`, {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ completed: !task.completed })
            });
            
            if (response.ok) {
                await this.loadStats();
                await this.loadTasks();
            }
        } catch (error) {
            console.error('Errore toggle task:', error);
        }
    }
    
    async deleteTask(taskId) {
        if (!confirm('Sei sicuro di voler eliminare questo task?')) return;
        
        try {
            const response = await fetch(`/api/tasks/${taskId}`, {
                method: 'DELETE'
            });
            
            if (response.ok) {
                await this.loadStats();
                await this.loadTasks();
            }
        } catch (error) {
            console.error('Errore eliminazione task:', error);
        }
    }
}

// Inizializza dashboard
let dashboard;
document.addEventListener('DOMContentLoaded', () => {
    dashboard = new TaskDashboard();
});
```

```bash
# Commit feature Bob
git add .
git commit -m "feat(frontend): dashboard interattiva completa

- Interfaccia responsive con CSS Grid
- JavaScript vanilla per gestione stato
- Integrazione completa con API REST
- Operazioni CRUD real-time
- Dashboard statistiche visuale"

git push -u origin feature/frontend-dashboard
```

### Task 3: Gestione Conflitti e Merge

```bash
# 3.1 Simula conflitto: modifica concorrente su main
git checkout main

# Modifica README.md per creare conflitto
cat >> README.md << 'EOF'

## Deployment

### Development
```bash
npm run dev
```

### Production
```bash
npm start
```

## Contributing
Per contribuire al progetto:
1. Fork del repository
2. Crea feature branch
3. Commit con messaggi descrittivi
4. Push e crea Pull Request
EOF

git add README.md
git commit -m "docs: aggiunta sezione deployment e contributing"

# 3.2 Prova merge della feature Alice
git merge feature/enhanced-api
```

**🏁 Checkpoint 2**: Gestisci il merge pulito

```bash
# 3.3 Merge feature Bob (potenziale conflitto)
git merge feature/frontend-dashboard

# Se ci sono conflitti, risolvi manualmente e:
git add .
git commit -m "merge: integrata dashboard frontend con API enhanced"

# 3.4 Test finale applicazione
git push origin main
```

### Task 4: Sync Multi-Remote Challenge

```bash
# 4.1 Simula ambiente staging
git remote add staging https://github.com/tuo-username/team-sync-staging.git

# 4.2 Push su staging per testing
git push staging main

# 4.3 Simula hotfix necessario
git checkout -b hotfix/security-headers

# Modifica app.js per aggiungere security headers
```

Aggiungi in `app.js` dopo le altre middleware:
```javascript
// Security headers aggiuntivi
app.use((req, res, next) => {
    res.setHeader('X-Content-Type-Options', 'nosniff');
    res.setHeader('X-Frame-Options', 'DENY');
    res.setHeader('X-XSS-Protection', '1; mode=block');
    res.setHeader('Strict-Transport-Security', 'max-age=31536000; includeSubDomains');
    next();
});
```

```bash
git add .
git commit -m "security: aggiunta security headers avanzati

- X-Content-Type-Options per prevenire MIME sniffing
- X-Frame-Options per prevenire clickjacking
- X-XSS-Protection per protezione XSS
- HSTS per forzare HTTPS
- Headers conformi OWASP guidelines"

# 4.4 Push hotfix e merge rapido
git push -u origin hotfix/security-headers
git checkout main
git merge hotfix/security-headers
git push origin main
git push staging main

# 4.5 Cleanup branch
git branch -d hotfix/security-headers
git push origin --delete hotfix/security-headers
```

## ✅ Criteri di Valutazione

### Punti (Max 100)

**Setup e Configurazione (25 punti)**
- ✅ Repository creato correttamente (5 pt)
- ✅ File progetto con contenuto significativo (10 pt)
- ✅ Commit iniziale ben strutturato (10 pt)

**Gestione Branch e Collaboration (35 punti)**
- ✅ Feature branch create correttamente (10 pt)
- ✅ Commit messaggi descrittivi e strutturati (10 pt)
- ✅ Push e tracking branch configurati (5 pt)
- ✅ Merge gestiti correttamente (10 pt)

**Gestione Conflitti (20 punti)**
- ✅ Conflitti identificati e risolti (10 pt)
- ✅ Cronologia Git pulita post-merge (10 pt)

**Workflow Avanzato (20 punti)**
- ✅ Multiple remote configurati (5 pt)
- ✅ Hotfix workflow implementato (10 pt)
- ✅ Cleanup branch e repository organization (5 pt)

### Bonus (Max 20 punti extra)
- 🌟 Test automatici implementati (+5 pt)
- 🌟 Git hooks personalizzati (+5 pt)
- 🌟 Documentazione README eccellente (+5 pt)
- 🌟 Implementazione feature aggiuntive (+5 pt)

## 🎯 Deliverable Finali

1. **Repository GitHub** con cronologia completa
2. **Screenshot** della dashboard funzionante
3. **Log Git** pulito e ben organizzato
4. **Documentazione** del processo seguito

## 💡 Suggerimenti

### Comandi Utili
```bash
# Verifica stato repository
git log --oneline --graph --all

# Verifica remote configurati
git remote -v

# Stato branch
git branch -vv

# Cleanup locale
git remote prune origin
```

### Troubleshooting Comune
```bash
# Se merge fallisce
git merge --abort
git status

# Se push viene rejected
git pull --rebase origin main
git push origin main

# Per vedere differenze tra branch
git diff main..feature/nome-branch
```

## 🎮 Challenge Extra

**Scenario Avanzato**: Implementa un sistema di review automatico che:

1. **Pre-push Hook** che verifica:
   - Test passano
   - Linting OK
   - No file grandi (>1MB)

2. **Post-merge Hook** che:
   - Aggiorna automaticamente staging
   - Invia notifica team
   - Genera changelog

3. **Monitoring Script** che:
   - Controlla stato sync ogni 30 secondi
   - Notifica divergenze
   - Auto-fetch da remote multipli

## 🏆 Criteri Successo

**Esercizio SUPERATO se:**
- ✅ Repository funzionante e ben organizzato
- ✅ Workflow collaboration implementato correttamente
- ✅ Conflitti gestiti senza perdere dati
- ✅ Cronologia Git pulita e comprensibile
- ✅ Multiple remote configurati e utilizzati

**Voto finale:** Basato su completezza tecnica, qualità del codice e organizzazione del workflow Git.
