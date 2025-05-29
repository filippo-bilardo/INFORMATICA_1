# Esercizio 03: Progetto Multi-File

## 🎯 Obiettivo

Applicare le competenze di staging avanzato in un progetto realistico multi-file, simulando lo sviluppo di un'applicazione web completa con gestione professionale dei commit.

## ⏱️ Durata Stimata: 90-120 minuti

## 📋 Prerequisiti

- Completamento degli Esercizi 01 e 02
- Padronanza di `git add -p` e staging interattivo
- Conoscenza di HTML, CSS, JavaScript base

## 🎯 Scenario del Progetto

Svilupperai **"TaskManager Pro"** - un'applicazione web per gestione task con:
- **Frontend**: HTML, CSS, JavaScript
- **Backend**: Node.js con API REST
- **Database**: Configurazione e modelli
- **Testing**: Unit test e integrazione
- **Documentazione**: README e guide

## 🚀 Setup del Progetto

```bash
# Crea la struttura del progetto
mkdir taskmanager-pro && cd taskmanager-pro
git init

# Configura Git
git config user.name "Il Tuo Nome"
git config user.email "tua.email@example.com"

# Crea struttura directory
mkdir -p {frontend/{css,js,html},backend/{controllers,models,routes},tests,docs,config}
```

## 📝 Fase 1: Setup Iniziale e Base del Progetto

### Task 1.1: File di Configurazione Base

```bash
# Package.json per il progetto
cat > package.json << 'EOF'
{
  "name": "taskmanager-pro",
  "version": "1.0.0",
  "description": "Professional task management application",
  "main": "backend/server.js",
  "scripts": {
    "start": "node backend/server.js",
    "test": "jest",
    "dev": "nodemon backend/server.js"
  },
  "dependencies": {
    "express": "^4.18.0",
    "cors": "^2.8.5"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "nodemon": "^2.0.20"
  }
}
EOF

# Configurazione ambiente
cat > config/database.js << 'EOF'
module.exports = {
  development: {
    host: 'localhost',
    port: 5432,
    database: 'taskmanager_dev'
  },
  production: {
    host: process.env.DB_HOST,
    port: process.env.DB_PORT,
    database: process.env.DB_NAME
  }
};
EOF

# Gitignore iniziale
cat > .gitignore << 'EOF'
node_modules/
.env
*.log
.DS_Store
coverage/
dist/
EOF

# README base
cat > README.md << 'EOF'
# TaskManager Pro

Professional task management application built with modern web technologies.

## Features

- Task creation and management
- User authentication
- Real-time updates
- Responsive design

## Setup

```bash
npm install
npm run dev
```

## Testing

```bash
npm test
```
EOF

# Commit setup iniziale
git add package.json config/database.js .gitignore README.md
git commit -m "initial project setup

- Add package.json with dependencies and scripts
- Configure database connection settings
- Add gitignore for Node.js projects
- Create basic README with setup instructions"
```

## 📝 Fase 2: Sviluppo Frontend Base

### Task 2.1: Struttura HTML e CSS Base

```bash
# HTML principale
cat > frontend/html/index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>TaskManager Pro</title>
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/components.css">
</head>
<body>
    <header class="header">
        <h1>TaskManager Pro</h1>
        <nav class="nav">
            <button id="addTaskBtn" class="btn btn-primary">Add Task</button>
            <button id="filterBtn" class="btn btn-secondary">Filter</button>
        </nav>
    </header>
    
    <main class="main">
        <div class="task-container">
            <div id="taskList" class="task-list">
                <!-- Tasks will be loaded here -->
            </div>
        </div>
    </main>
    
    <div id="taskModal" class="modal hidden">
        <div class="modal-content">
            <span class="close">&times;</span>
            <h2>Add New Task</h2>
            <form id="taskForm">
                <input type="text" id="taskTitle" placeholder="Task title" required>
                <textarea id="taskDescription" placeholder="Description"></textarea>
                <select id="taskPriority">
                    <option value="low">Low</option>
                    <option value="medium">Medium</option>
                    <option value="high">High</option>
                </select>
                <button type="submit" class="btn btn-primary">Save Task</button>
            </form>
        </div>
    </div>
    
    <script src="../js/app.js"></script>
    <script src="../js/task-manager.js"></script>
</body>
</html>
EOF

# CSS principale
cat > frontend/css/style.css << 'EOF'
/* Global Styles */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    line-height: 1.6;
    color: #333;
    background-color: #f5f5f5;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
}

/* Header Styles */
.header {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 1rem 0;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

.header h1 {
    display: inline-block;
    margin-right: 2rem;
}

.nav {
    display: inline-block;
    float: right;
}

/* Button Styles */
.btn {
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    font-size: 14px;
    margin: 0 5px;
    transition: all 0.3s ease;
}

.btn-primary {
    background-color: #007bff;
    color: white;
}

.btn-primary:hover {
    background-color: #0056b3;
}

.btn-secondary {
    background-color: #6c757d;
    color: white;
}

.btn-secondary:hover {
    background-color: #5a6268;
}

/* Main Content */
.main {
    padding: 2rem 0;
}

.task-container {
    background: white;
    border-radius: 10px;
    padding: 2rem;
    box-shadow: 0 5px 15px rgba(0,0,0,0.1);
}
EOF

# CSS per componenti
cat > frontend/css/components.css << 'EOF'
/* Task List Styles */
.task-list {
    margin-top: 1rem;
}

.task-item {
    background: #f8f9fa;
    border: 1px solid #dee2e6;
    border-radius: 8px;
    padding: 1rem;
    margin-bottom: 1rem;
    transition: all 0.3s ease;
}

.task-item:hover {
    box-shadow: 0 3px 10px rgba(0,0,0,0.1);
}

.task-item.completed {
    opacity: 0.7;
    text-decoration: line-through;
}

.task-title {
    font-size: 1.2rem;
    font-weight: bold;
    margin-bottom: 0.5rem;
}

.task-description {
    color: #666;
    margin-bottom: 1rem;
}

.task-meta {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.task-priority {
    padding: 3px 8px;
    border-radius: 3px;
    font-size: 0.8rem;
    text-transform: uppercase;
}

.priority-high {
    background-color: #dc3545;
    color: white;
}

.priority-medium {
    background-color: #ffc107;
    color: #333;
}

.priority-low {
    background-color: #28a745;
    color: white;
}

/* Modal Styles */
.modal {
    display: none;
    position: fixed;
    z-index: 1000;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.4);
}

.modal.hidden {
    display: none;
}

.modal-content {
    background-color: white;
    margin: 15% auto;
    padding: 20px;
    border-radius: 10px;
    width: 500px;
    max-width: 90%;
    position: relative;
}

.close {
    position: absolute;
    right: 15px;
    top: 15px;
    font-size: 24px;
    cursor: pointer;
}

/* Form Styles */
form {
    margin-top: 1rem;
}

form input,
form textarea,
form select {
    width: 100%;
    padding: 10px;
    margin-bottom: 1rem;
    border: 1px solid #ddd;
    border-radius: 5px;
    font-size: 14px;
}

form textarea {
    height: 100px;
    resize: vertical;
}
EOF
```

### Task 2.2: Staging Strategico Frontend

**🎯 Obiettivo**: Crea 2 commit separati per HTML e CSS.

```bash
# Staging HTML
git add frontend/html/index.html
git commit -m "feat: add main HTML structure

- Create responsive layout with header and main sections
- Add task modal for creating new tasks
- Include semantic HTML structure
- Prepare for JavaScript integration"

# Staging CSS in due parti
git add frontend/css/style.css
git commit -m "feat: add global styles and layout

- Implement modern design with gradient header
- Add responsive container and grid system  
- Create button components with hover effects
- Establish consistent color scheme and typography"

git add frontend/css/components.css
git commit -m "feat: add component-specific styles

- Style task list items with hover effects
- Implement priority-based color coding
- Add modal styles for task creation
- Create form styling for better UX"
```

## 📝 Fase 3: JavaScript Frontend con Modifiche Complesse

### Task 3.1: File JavaScript con Codice Misto

```bash
# App.js principale con debug e production code
cat > frontend/js/app.js << 'EOF'
// TaskManager Pro - Main Application
console.log("DEBUG: App starting..."); // Debug temporaneo

class TaskManagerApp {
    constructor() {
        this.taskManager = new TaskManager();
        this.modal = document.getElementById('taskModal');
        this.addTaskBtn = document.getElementById('addTaskBtn');
        this.taskForm = document.getElementById('taskForm');
        
        this.initEventListeners();
        this.loadTasks(); // Pronto per commit
        console.log("TEMP: App initialized"); // Debug temporaneo
    }
    
    // Metodo pronto per production
    initEventListeners() {
        this.addTaskBtn.addEventListener('click', () => {
            this.openModal();
        });
        
        this.taskForm.addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleTaskSubmit();
        });
        
        // Close modal on click outside
        window.addEventListener('click', (e) => {
            if (e.target === this.modal) {
                this.closeModal();
            }
        });
        
        // Close modal on escape key
        document.addEventListener('keydown', (e) => {
            if (e.key === 'Escape' && !this.modal.classList.contains('hidden')) {
                this.closeModal();
            }
        });
    }
    
    // Metodo pronto per production
    openModal() {
        this.modal.classList.remove('hidden');
        this.modal.style.display = 'block';
        document.getElementById('taskTitle').focus();
    }
    
    // Metodo pronto per production
    closeModal() {
        this.modal.classList.add('hidden');
        this.modal.style.display = 'none';
        this.taskForm.reset();
    }
    
    // Metodo con debug misto
    handleTaskSubmit() {
        console.log("DEBUG: Handling task submit"); // Debug
        
        const title = document.getElementById('taskTitle').value.trim();
        const description = document.getElementById('taskDescription').value.trim();
        const priority = document.getElementById('taskPriority').value;
        
        if (!title) {
            alert('Please enter a task title');
            return;
        }
        
        const task = {
            id: Date.now(),
            title,
            description,
            priority,
            completed: false,
            createdAt: new Date()
        };
        
        console.log("TEMP: Creating task", task); // Debug temporaneo
        
        this.taskManager.addTask(task);
        this.closeModal();
        this.renderTasks();
    }
    
    // Metodo pronto ma con debug
    loadTasks() {
        console.log("DEBUG: Loading tasks from storage"); // Debug
        const tasks = this.taskManager.getAllTasks();
        this.renderTasks();
        console.log("TEMP: Loaded", tasks.length, "tasks"); // Debug
    }
    
    // Metodo pronto per production
    renderTasks() {
        const taskList = document.getElementById('taskList');
        const tasks = this.taskManager.getAllTasks();
        
        if (tasks.length === 0) {
            taskList.innerHTML = '<p class="no-tasks">No tasks yet. Add your first task!</p>';
            return;
        }
        
        taskList.innerHTML = tasks.map(task => this.createTaskHTML(task)).join('');
        this.attachTaskEventListeners();
    }
    
    // Metodo pronto per production
    createTaskHTML(task) {
        return `
            <div class="task-item ${task.completed ? 'completed' : ''}" data-task-id="${task.id}">
                <div class="task-title">${task.title}</div>
                <div class="task-description">${task.description}</div>
                <div class="task-meta">
                    <span class="task-priority priority-${task.priority}">${task.priority}</span>
                    <div class="task-actions">
                        <button class="btn-complete ${task.completed ? 'btn-uncomplete' : ''}">
                            ${task.completed ? 'Undo' : 'Complete'}
                        </button>
                        <button class="btn-delete">Delete</button>
                    </div>
                </div>
            </div>
        `;
    }
    
    // Metodo pronto ma con debug
    attachTaskEventListeners() {
        console.log("DEBUG: Attaching event listeners"); // Debug
        
        document.querySelectorAll('.btn-complete').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const taskId = parseInt(e.target.closest('.task-item').dataset.taskId);
                this.taskManager.toggleTaskComplete(taskId);
                this.renderTasks();
            });
        });
        
        document.querySelectorAll('.btn-delete').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const taskId = parseInt(e.target.closest('.task-item').dataset.taskId);
                if (confirm('Are you sure you want to delete this task?')) {
                    this.taskManager.deleteTask(taskId);
                    this.renderTasks();
                }
            });
        });
    }
}

// Debug temporaneo
console.log("TEMP: App.js loaded");

// Initialize app when DOM is loaded - PRONTO
document.addEventListener('DOMContentLoaded', () => {
    new TaskManagerApp();
});
EOF

# TaskManager class con codice misto
cat > frontend/js/task-manager.js << 'EOF'
// TaskManager Class - Data Management
console.log("DEBUG: TaskManager module loading"); // Debug temporaneo

class TaskManager {
    constructor() {
        this.tasks = [];
        this.storageKey = 'taskmanager-tasks';
        this.loadFromStorage(); // Pronto
        console.log("TEMP: TaskManager initialized with", this.tasks.length, "tasks"); // Debug
    }
    
    // Metodo pronto per production
    addTask(task) {
        this.tasks.push(task);
        this.saveToStorage();
        return task;
    }
    
    // Metodo pronto per production
    getAllTasks() {
        return [...this.tasks]; // Return copy to prevent mutation
    }
    
    // Metodo pronto per production
    getTaskById(id) {
        return this.tasks.find(task => task.id === id);
    }
    
    // Metodo pronto per production
    deleteTask(id) {
        const index = this.tasks.findIndex(task => task.id === id);
        if (index !== -1) {
            this.tasks.splice(index, 1);
            this.saveToStorage();
            return true;
        }
        return false;
    }
    
    // Metodo pronto per production
    toggleTaskComplete(id) {
        const task = this.getTaskById(id);
        if (task) {
            task.completed = !task.completed;
            task.completedAt = task.completed ? new Date() : null;
            this.saveToStorage();
            return task;
        }
        return null;
    }
    
    // Metodo pronto ma con debug
    loadFromStorage() {
        try {
            console.log("DEBUG: Loading from localStorage"); // Debug
            const stored = localStorage.getItem(this.storageKey);
            if (stored) {
                this.tasks = JSON.parse(stored);
                console.log("TEMP: Loaded", this.tasks.length, "tasks from storage"); // Debug
            }
        } catch (error) {
            console.error('Error loading tasks from storage:', error);
            this.tasks = [];
        }
    }
    
    // Metodo pronto ma con debug
    saveToStorage() {
        try {
            console.log("DEBUG: Saving to localStorage"); // Debug
            localStorage.setItem(this.storageKey, JSON.stringify(this.tasks));
            console.log("TEMP: Saved", this.tasks.length, "tasks to storage"); // Debug
        } catch (error) {
            console.error('Error saving tasks to storage:', error);
        }
    }
    
    // Metodi sperimentali - NON pronti
    experimentalFilter(criteria) {
        console.log("EXPERIMENTAL: Filtering with", criteria); // Non committare
        // TODO: Implementare filtri avanzati
        return this.tasks;
    }
    
    debugInfo() {
        console.log("DEBUG INFO:", {
            totalTasks: this.tasks.length,
            completedTasks: this.tasks.filter(t => t.completed).length,
            pendingTasks: this.tasks.filter(t => !t.completed).length
        });
    }
}

console.log("TEMP: TaskManager module loaded"); // Debug temporaneo
EOF
```

### Task 3.2: Staging Strategico JavaScript

**🎯 Obiettivo**: Crea commit puliti senza debug code usando staging interattivo.

```bash
# Staging App.js senza debug
git add -p frontend/js/app.js

# Durante il processo interattivo:
# ✅ INCLUDI: constructor (senza console.log), initEventListeners, openModal, closeModal, renderTasks, createTaskHTML
# ✅ INCLUDI: handleTaskSubmit (senza console.log), loadTasks (senza console.log), attachTaskEventListeners (senza console.log) 
# ✅ INCLUDI: DOMContentLoaded event listener
# ❌ ESCLUDI: Tutti i console.log con DEBUG/TEMP

git commit -m "feat: add main application controller

- Implement TaskManagerApp class with modal management
- Add event listeners for user interactions
- Create task rendering and HTML generation
- Add task action handlers (complete/delete)
- Integrate with TaskManager for data operations"

# Staging TaskManager.js senza debug
git add -p frontend/js/task-manager.js

# Durante il processo interattivo:
# ✅ INCLUDI: constructor (senza console.log), tutti i metodi CRUD
# ✅ INCLUDI: localStorage methods (senza console.log)
# ❌ ESCLUDI: console.log DEBUG/TEMP, experimentalFilter, debugInfo

git commit -m "feat: add task data management class

- Implement TaskManager with CRUD operations
- Add localStorage persistence for tasks
- Create task state management (complete/pending)
- Add data validation and error handling
- Provide immutable data access methods"
```

## 📝 Fase 4: Backend Development con Staging Complesso

### Task 4.1: Server e Routes con Debug

```bash
# Server principale con codice misto
cat > backend/server.js << 'EOF'
// TaskManager Pro - Backend Server
const express = require('express');
const cors = require('cors');
const path = require('path');

console.log("DEBUG: Starting server..."); // Debug temporaneo

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware - PRONTO
app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, '../frontend')));

// Routes - PRONTO
app.use('/api/tasks', require('./routes/tasks'));
app.use('/api/users', require('./routes/users')); // TODO: Implementare

// Serve frontend - PRONTO
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/html/index.html'));
});

// Error handling - PRONTO
app.use((err, req, res, next) => {
    console.error('Server error:', err); // Questo è OK per production
    res.status(500).json({ error: 'Internal server error' });
});

// 404 handler - PRONTO
app.use((req, res) => {
    res.status(404).json({ error: 'Route not found' });
});

console.log("TEMP: Middleware configured"); // Debug temporaneo

// Start server - PRONTO
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`); // OK per production
    console.log("DEBUG: Server started successfully"); // Debug temporaneo
});

// Graceful shutdown - PRONTO
process.on('SIGINT', () => {
    console.log('Server shutting down gracefully'); // OK per production
    process.exit(0);
});

console.log("TEMP: Server.js loaded"); // Debug temporaneo
EOF

# Routes per tasks
cat > backend/routes/tasks.js << 'EOF'
// Task Routes
const express = require('express');
const router = express.Router();
const TaskController = require('../controllers/TaskController');

console.log("DEBUG: Loading task routes"); // Debug temporaneo

// GET /api/tasks - PRONTO
router.get('/', TaskController.getAllTasks);

// POST /api/tasks - PRONTO  
router.post('/', TaskController.createTask);

// PUT /api/tasks/:id - PRONTO
router.put('/:id', TaskController.updateTask);

// DELETE /api/tasks/:id - PRONTO
router.delete('/:id', TaskController.deleteTask);

// GET /api/tasks/:id - PRONTO
router.get('/:id', TaskController.getTaskById);

// TODO: Route non ancora pronte
router.get('/filter/:criteria', (req, res) => {
    console.log("EXPERIMENTAL: Filter route called"); // Non committare
    res.status(501).json({ error: 'Not implemented yet' });
});

console.log("TEMP: Task routes loaded"); // Debug temporaneo

module.exports = router;
EOF

# Routes per users (placeholder)
cat > backend/routes/users.js << 'EOF'
// User Routes - Placeholder
const express = require('express');
const router = express.Router();

console.log("DEBUG: Loading user routes"); // Debug temporaneo

// TODO: Tutte le routes user non sono pronte
router.get('/', (req, res) => {
    console.log("TODO: Implement user listing"); // Debug
    res.status(501).json({ error: 'User routes not implemented yet' });
});

router.post('/register', (req, res) => {
    console.log("TODO: Implement user registration"); // Debug
    res.status(501).json({ error: 'Registration not implemented yet' });
});

console.log("TEMP: User routes (placeholder) loaded"); // Debug temporaneo

module.exports = router;
EOF
```

### Task 4.2: Controller con Business Logic

```bash
# Task Controller con metodi misti
cat > backend/controllers/TaskController.js << 'EOF'
// Task Controller - Business Logic
const TaskModel = require('../models/Task');

console.log("DEBUG: TaskController loading"); // Debug temporaneo

class TaskController {
    // GET /api/tasks - PRONTO
    static async getAllTasks(req, res) {
        try {
            console.log("DEBUG: Getting all tasks"); // Debug temporaneo
            const tasks = await TaskModel.findAll();
            res.json({
                success: true,
                data: tasks,
                count: tasks.length
            });
        } catch (error) {
            console.error('Error getting tasks:', error); // OK per production
            res.status(500).json({
                success: false,
                error: 'Failed to retrieve tasks'
            });
        }
    }
    
    // POST /api/tasks - PRONTO
    static async createTask(req, res) {
        try {
            console.log("DEBUG: Creating task", req.body); // Debug temporaneo
            
            const { title, description, priority } = req.body;
            
            // Validation - PRONTO
            if (!title || typeof title !== 'string' || title.trim().length === 0) {
                return res.status(400).json({
                    success: false,
                    error: 'Task title is required'
                });
            }
            
            if (priority && !['low', 'medium', 'high'].includes(priority)) {
                return res.status(400).json({
                    success: false,
                    error: 'Invalid priority level'
                });
            }
            
            const taskData = {
                title: title.trim(),
                description: description ? description.trim() : '',
                priority: priority || 'medium',
                completed: false,
                createdAt: new Date()
            };
            
            const task = await TaskModel.create(taskData);
            
            res.status(201).json({
                success: true,
                data: task
            });
            
        } catch (error) {
            console.error('Error creating task:', error); // OK per production
            res.status(500).json({
                success: false,
                error: 'Failed to create task'
            });
        }
    }
    
    // PUT /api/tasks/:id - PRONTO
    static async updateTask(req, res) {
        try {
            const { id } = req.params;
            console.log("DEBUG: Updating task", id, req.body); // Debug temporaneo
            
            const task = await TaskModel.findById(id);
            if (!task) {
                return res.status(404).json({
                    success: false,
                    error: 'Task not found'
                });
            }
            
            const updates = {};
            const { title, description, priority, completed } = req.body;
            
            if (title !== undefined) updates.title = title.trim();
            if (description !== undefined) updates.description = description.trim();
            if (priority !== undefined) {
                if (!['low', 'medium', 'high'].includes(priority)) {
                    return res.status(400).json({
                        success: false,
                        error: 'Invalid priority level'
                    });
                }
                updates.priority = priority;
            }
            if (completed !== undefined) {
                updates.completed = Boolean(completed);
                updates.completedAt = updates.completed ? new Date() : null;
            }
            
            const updatedTask = await TaskModel.update(id, updates);
            
            res.json({
                success: true,
                data: updatedTask
            });
            
        } catch (error) {
            console.error('Error updating task:', error); // OK per production
            res.status(500).json({
                success: false,
                error: 'Failed to update task'
            });
        }
    }
    
    // DELETE /api/tasks/:id - PRONTO
    static async deleteTask(req, res) {
        try {
            const { id } = req.params;
            console.log("DEBUG: Deleting task", id); // Debug temporaneo
            
            const deleted = await TaskModel.delete(id);
            if (!deleted) {
                return res.status(404).json({
                    success: false,
                    error: 'Task not found'
                });
            }
            
            res.json({
                success: true,
                message: 'Task deleted successfully'
            });
            
        } catch (error) {
            console.error('Error deleting task:', error); // OK per production
            res.status(500).json({
                success: false,
                error: 'Failed to delete task'
            });
        }
    }
    
    // GET /api/tasks/:id - PRONTO
    static async getTaskById(req, res) {
        try {
            const { id } = req.params;
            console.log("DEBUG: Getting task by ID", id); // Debug temporaneo
            
            const task = await TaskModel.findById(id);
            if (!task) {
                return res.status(404).json({
                    success: false,
                    error: 'Task not found'
                });
            }
            
            res.json({
                success: true,
                data: task
            });
            
        } catch (error) {
            console.error('Error getting task:', error); // OK per production
            res.status(500).json({
                success: false,
                error: 'Failed to retrieve task'
            });
        }
    }
    
    // Metodo sperimentale - NON pronto
    static async experimentalBulkUpdate(req, res) {
        console.log("EXPERIMENTAL: Bulk update called"); // Non committare
        // TODO: Implementare aggiornamento bulk
        res.status(501).json({
            success: false,
            error: 'Bulk update not implemented yet'
        });
    }
}

console.log("TEMP: TaskController loaded"); // Debug temporaneo

module.exports = TaskController;
EOF

# Task Model
cat > backend/models/Task.js << 'EOF'
// Task Model - Data Access Layer
console.log("DEBUG: Task model loading"); // Debug temporaneo

class Task {
    constructor(data) {
        this.id = data.id || Date.now();
        this.title = data.title;
        this.description = data.description || '';
        this.priority = data.priority || 'medium';
        this.completed = data.completed || false;
        this.createdAt = data.createdAt || new Date();
        this.completedAt = data.completedAt || null;
    }
    
    // Mock database (in memory) - PRONTO per demo
    static tasks = [];
    
    // CRUD Operations - PRONTI
    static async findAll() {
        console.log("DEBUG: Finding all tasks, count:", this.tasks.length); // Debug
        return [...this.tasks]; // Return copy
    }
    
    static async findById(id) {
        console.log("DEBUG: Finding task by ID:", id); // Debug
        return this.tasks.find(task => task.id == id) || null;
    }
    
    static async create(data) {
        console.log("DEBUG: Creating task:", data); // Debug
        const task = new Task(data);
        this.tasks.push(task);
        return task;
    }
    
    static async update(id, updates) {
        console.log("DEBUG: Updating task:", id, updates); // Debug
        const index = this.tasks.findIndex(task => task.id == id);
        if (index === -1) return null;
        
        Object.assign(this.tasks[index], updates);
        return this.tasks[index];
    }
    
    static async delete(id) {
        console.log("DEBUG: Deleting task:", id); // Debug
        const index = this.tasks.findIndex(task => task.id == id);
        if (index === -1) return false;
        
        this.tasks.splice(index, 1);
        return true;
    }
    
    // Metodi sperimentali - NON pronti
    static async experimentalQuery(criteria) {
        console.log("EXPERIMENTAL: Querying with criteria:", criteria); // Non committare
        // TODO: Implementare query avanzate
        return this.tasks;
    }
    
    static debugStats() {
        console.log("DEBUG STATS:", {
            total: this.tasks.length,
            completed: this.tasks.filter(t => t.completed).length,
            byPriority: {
                high: this.tasks.filter(t => t.priority === 'high').length,
                medium: this.tasks.filter(t => t.priority === 'medium').length,
                low: this.tasks.filter(t => t.priority === 'low').length
            }
        });
    }
}

console.log("TEMP: Task model loaded"); // Debug temporaneo

module.exports = Task;
EOF
```

### Task 4.3: Staging Backend Complesso

**🎯 Obiettivo**: Crea commit separati per server, routes e controller+model, escludendo tutto il debug.

```bash
# 1. Staging Server principale (solo production code)
git add -p backend/server.js

# Includi tutto tranne console.log DEBUG/TEMP
git commit -m "feat: add Express server with middleware and routing

- Configure CORS and JSON parsing middleware
- Add static file serving for frontend
- Implement error handling and 404 routes
- Add graceful shutdown handling
- Serve frontend from backend server"

# 2. Staging Routes (solo routes pronte)
git add -p backend/routes/tasks.js

# Includi solo le routes CRUD, escludi experimental e debug
git commit -m "feat: add task API routes

- Implement RESTful routes for task operations
- Add GET, POST, PUT, DELETE endpoints
- Connect routes to TaskController
- Prepare for task CRUD operations"

# NON committare backend/routes/users.js (tutto è TODO/placeholder)

# 3. Staging Controller (solo metodi pronti)
git add -p backend/controllers/TaskController.js

# Includi tutti i metodi CRUD senza console.log DEBUG, escludi experimental
git commit -m "feat: add task controller with business logic

- Implement CRUD operations for tasks
- Add input validation for task data
- Add comprehensive error handling
- Implement proper HTTP status codes
- Add response formatting standards"

# 4. Staging Model (solo CRUD, non experimental)
git add -p backend/models/Task.js

# Includi Task class e CRUD methods senza debug, escludi experimental
git commit -m "feat: add task data model and persistence

- Implement Task class with data validation
- Add in-memory storage for development
- Implement CRUD operations with async interface
- Add proper data structure and constraints
- Prepare for database integration"
```

## 📝 Fase 5: Testing e Documentazione

### Task 5.1: Test Files

```bash
# Test per frontend
cat > tests/frontend.test.js << 'EOF'
// Frontend Tests
describe('TaskManager Frontend', () => {
    // Mock DOM for testing
    beforeEach(() => {
        document.body.innerHTML = `
            <div id="taskList"></div>
            <div id="taskModal" class="hidden"></div>
            <form id="taskForm">
                <input id="taskTitle" />
                <textarea id="taskDescription"></textarea>
                <select id="taskPriority"></select>
            </form>
        `;
    });
    
    test('should create task manager instance', () => {
        // Questo test passa
        expect(typeof TaskManager).toBe('function');
    });
    
    test('should add task to storage', () => {
        const manager = new TaskManager();
        const task = {
            id: 1,
            title: 'Test Task',
            description: 'Test Description',
            priority: 'high'
        };
        
        manager.addTask(task);
        expect(manager.getAllTasks()).toContain(task);
    });
    
    // Test che fallisce - da non committare
    test('experimental feature test', () => {
        console.log("EXPERIMENTAL: This test is not ready");
        // TODO: Implementare test per feature sperimentali
        expect(false).toBe(true); // Questo fallisce volutamente
    });
});
EOF

# Test per backend
cat > tests/backend.test.js << 'EOF'
// Backend Tests
const TaskController = require('../backend/controllers/TaskController');
const Task = require('../backend/models/Task');

describe('Task Controller', () => {
    beforeEach(() => {
        // Reset tasks before each test
        Task.tasks = [];
    });
    
    test('should create task with valid data', async () => {
        const req = {
            body: {
                title: 'Test Task',
                description: 'Test Description',
                priority: 'high'
            }
        };
        
        const res = {
            status: jest.fn().mockReturnThis(),
            json: jest.fn()
        };
        
        await TaskController.createTask(req, res);
        
        expect(res.status).toHaveBeenCalledWith(201);
        expect(res.json).toHaveBeenCalledWith({
            success: true,
            data: expect.objectContaining({
                title: 'Test Task',
                priority: 'high'
            })
        });
    });
    
    test('should validate required fields', async () => {
        const req = {
            body: {} // Missing title
        };
        
        const res = {
            status: jest.fn().mockReturnThis(),
            json: jest.fn()
        };
        
        await TaskController.createTask(req, res);
        
        expect(res.status).toHaveBeenCalledWith(400);
        expect(res.json).toHaveBeenCalledWith({
            success: false,
            error: 'Task title is required'
        });
    });
    
    // Test incompleto - da non committare
    test('experimental bulk operations', () => {
        console.log("TODO: Implement bulk operation tests");
        // Test non completato
        expect(true).toBe(false); // Placeholder che fallisce
    });
});
EOF

# Jest configuration
cat > jest.config.js << 'EOF'
module.exports = {
    testEnvironment: 'node',
    collectCoverageFrom: [
        'backend/**/*.js',
        'frontend/js/*.js',
        '!**/node_modules/**'
    ],
    testMatch: [
        '**/tests/**/*.test.js'
    ]
};
EOF
```

### Task 5.2: Documentazione API

```bash
# API Documentation
cat > docs/API.md << 'EOF'
# TaskManager Pro API Documentation

## Base URL
```
http://localhost:3000/api
```

## Authentication
Currently no authentication required (development mode).

## Endpoints

### Tasks

#### GET /tasks
Get all tasks.

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": 1,
      "title": "Sample Task",
      "description": "Task description",
      "priority": "medium",
      "completed": false,
      "createdAt": "2024-01-01T00:00:00.000Z",
      "completedAt": null
    }
  ],
  "count": 1
}
```

#### POST /tasks
Create a new task.

**Request Body:**
```json
{
  "title": "Task Title",
  "description": "Optional description",
  "priority": "low|medium|high"
}
```

**Response:**
```json
{
  "success": true,
  "data": {
    "id": 1,
    "title": "Task Title",
    "description": "Optional description",
    "priority": "medium",
    "completed": false,
    "createdAt": "2024-01-01T00:00:00.000Z"
  }
}
```

#### PUT /tasks/:id
Update an existing task.

**Request Body:** (all fields optional)
```json
{
  "title": "Updated Title",
  "description": "Updated description",
  "priority": "high",
  "completed": true
}
```

#### DELETE /tasks/:id
Delete a task.

**Response:**
```json
{
  "success": true,
  "message": "Task deleted successfully"
}
```

#### GET /tasks/:id
Get a specific task by ID.

## Error Responses

All endpoints return errors in this format:
```json
{
  "success": false,
  "error": "Error message description"
}
```

### Status Codes
- `200` - Success
- `201` - Created
- `400` - Bad Request (validation error)
- `404` - Not Found
- `500` - Internal Server Error
EOF

# Development Guide
cat > docs/DEVELOPMENT.md << 'EOF'
# Development Guide

## Project Structure

```
taskmanager-pro/
├── frontend/
│   ├── html/           # HTML templates
│   ├── css/            # Stylesheets
│   └── js/             # Client-side JavaScript
├── backend/
│   ├── controllers/    # Business logic
│   ├── models/         # Data models
│   ├── routes/         # API routes
│   └── server.js       # Express server
├── tests/              # Test files
├── docs/               # Documentation
└── config/             # Configuration files
```

## Getting Started

### Prerequisites
- Node.js 16+
- npm 8+

### Installation
```bash
git clone <repository>
cd taskmanager-pro
npm install
```

### Development
```bash
npm run dev  # Start development server with auto-reload
```

### Testing
```bash
npm test     # Run all tests
npm run test:watch  # Run tests in watch mode
```

### Production
```bash
npm start    # Start production server
```

## Code Standards

### Commit Messages
Use conventional commits:
- `feat:` - New features
- `fix:` - Bug fixes
- `docs:` - Documentation changes
- `test:` - Test additions/changes
- `chore:` - Maintenance tasks

### JavaScript Style
- Use ES6+ features
- Prefer `const` and `let` over `var`
- Use arrow functions for callbacks
- Add JSDoc comments for functions

### CSS Conventions
- Use BEM methodology for class names
- Mobile-first responsive design
- Use CSS custom properties for theming

## Git Workflow

1. Create feature branch from main
2. Make atomic commits with clear messages
3. Test thoroughly before committing
4. Use staging area for clean commits
5. Squash related commits before merge
EOF
```

### Task 5.3: Staging Testing e Docs

```bash
# Staging solo i test funzionanti
git add -p tests/frontend.test.js

# Includi solo i test che passano, escludi experimental
git commit -m "test: add frontend unit tests

- Add TaskManager class tests
- Test task creation and storage
- Add DOM manipulation tests
- Ensure test coverage for core functionality"

git add -p tests/backend.test.js

# Includi solo i test che passano, escludi experimental/TODO
git commit -m "test: add backend API tests

- Test task controller CRUD operations
- Add input validation tests
- Test error handling scenarios
- Ensure proper HTTP status codes"

# Staging Jest config
git add jest.config.js
git commit -m "chore: add Jest testing configuration

- Configure test environment for Node.js
- Set coverage collection for relevant files
- Define test file patterns
- Prepare for CI/CD integration"

# Staging documentazione
git add docs/API.md docs/DEVELOPMENT.md
git commit -m "docs: add comprehensive project documentation

- Add complete API documentation with examples
- Create development guide with setup instructions
- Document project structure and conventions
- Add git workflow guidelines"
```

## 📝 Fase 6: Challenge Finale - Integrazione Complessa

### Task 6.1: Feature Integration con Staging Strategico

```bash
# Aggiungi connessione frontend-backend
cat >> frontend/js/app.js << 'EOF'

// API Integration - PRONTO per commit
class ApiService {
    constructor() {
        this.baseUrl = '/api';
    }
    
    async getAllTasks() {
        try {
            const response = await fetch(`${this.baseUrl}/tasks`);
            const data = await response.json();
            return data.success ? data.data : [];
        } catch (error) {
            console.error('Error fetching tasks:', error); // OK per production
            return [];
        }
    }
    
    async createTask(task) {
        try {
            const response = await fetch(`${this.baseUrl}/tasks`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(task)
            });
            const data = await response.json();
            return data.success ? data.data : null;
        } catch (error) {
            console.error('Error creating task:', error); // OK per production
            return null;
        }
    }
    
    // TODO: Metodi non ancora implementati
    async updateTask(id, updates) {
        console.log("TODO: Implement API update"); // Non committare
        return null;
    }
    
    async deleteTask(id) {
        console.log("TODO: Implement API delete"); // Non committare
        return false;
    }
}

console.log("TEMP: API service loaded"); // Debug temporaneo
EOF

# Update package.json con nuovi script
cat > package.json << 'EOF'
{
  "name": "taskmanager-pro",
  "version": "1.2.0",
  "description": "Professional task management application with full-stack integration",
  "main": "backend/server.js",
  "scripts": {
    "start": "node backend/server.js",
    "dev": "nodemon backend/server.js",
    "test": "jest",
    "test:watch": "jest --watch",
    "test:coverage": "jest --coverage",
    "lint": "eslint backend/ frontend/js/",
    "build": "echo 'Build process for production'",
    "deploy": "echo 'Deployment script'"
  },
  "dependencies": {
    "express": "^4.18.0",
    "cors": "^2.8.5",
    "helmet": "^6.0.0"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "nodemon": "^2.0.20",
    "eslint": "^8.0.0"
  },
  "keywords": ["task-management", "productivity", "web-app"],
  "author": "TaskManager Pro Team",
  "license": "MIT"
}
EOF
```

### Task 6.2: Final Challenge - Multi-File Staging

**🎯 Il challenge finale**: Gestisci questi 5 file con modifiche miste e crea 3 commit logici:

1. **"feat: add API integration layer"** - Solo metodi pronti di ApiService
2. **"chore: update project configuration"** - Solo parti di package.json pronte per production  
3. **"docs: update README with new features"** - Aggiorna README

```bash
# Aggiungi anche aggiornamento README
cat >> README.md << 'EOF'

## New Features (v1.2.0)

### Full-Stack Integration
- Frontend now connects to backend API
- Real-time task synchronization
- Persistent data storage

### API Endpoints
- RESTful API for task management
- JSON-based communication
- Error handling and validation

### Development Tools
- Jest testing framework
- ESLint code quality
- Nodemon for development

## Architecture

```
Frontend (Vanilla JS) ↔ Express API ↔ In-Memory Storage
```

### API Usage Example
```javascript
const api = new ApiService();
const tasks = await api.getAllTasks();
```

## Performance
- Responsive design for all devices
- Efficient task rendering
- Local storage fallback

## TODO Features
- User authentication system
- Real database integration (PostgreSQL)
- Advanced filtering and search
- Task categories and tags
- Email notifications
- Mobile app version
EOF

# Ora il challenge: crea i 3 commit usando solo staging interattivo
# 1. ApiService (solo metodi getAllTasks e createTask, non TODO)
# 2. package.json (solo version bump e script production-ready, non TODO)  
# 3. README (tutto il contenuto nuovo è OK)
```

<details>
<summary>💡 Soluzione Challenge Finale</summary>

```bash
# 1. Staging ApiService integration
git add -p frontend/js/app.js
# Includi solo ApiService class con getAllTasks e createTask
# Escludi metodi TODO e console.log TEMP

git commit -m "feat: add API integration layer

- Implement ApiService class for backend communication
- Add getAllTasks API call with error handling
- Add createTask API call with JSON payload
- Prepare for full API integration"

# 2. Staging package.json updates
git add -p package.json
# Includi version bump, script updates, dependencies
# Escludi eventuali TODO o placeholder

git commit -m "chore: update project configuration

- Bump version to 1.2.0 for API integration
- Add comprehensive npm scripts for development
- Add production dependencies (helmet for security)
- Add development tools (eslint, coverage)"

# 3. Staging README completo
git add README.md
git commit -m "docs: update README with new features

- Document API integration capabilities
- Add architecture overview and examples
- Update feature list with latest additions
- Add performance and TODO sections"
```
</details>

## 🎯 Verifica Finale del Progetto

### Checklist Completamento

```bash
# Verifica struttura commit
echo "=== CRONOLOGIA COMMIT COMPLETA ==="
git log --oneline --graph -20

# Verifica che non ci sia debug code nei commit
echo -e "\n=== VERIFICA PULIZIA COMMIT ==="
git log -p --grep="DEBUG\|TEMP\|TODO" | wc -l
# Dovrebbe essere 0

# Verifica file struttura
echo -e "\n=== STRUTTURA PROGETTO ==="
find . -name "*.js" -o -name "*.html" -o -name "*.css" -o -name "*.md" | sort

# Verifica working directory
echo -e "\n=== STATO WORKING DIRECTORY ==="
git status
# Dovrebbe mostrare eventuali file con debug rimanente

# Conteggio commit per categoria
echo -e "\n=== COMMIT PER CATEGORIA ==="
echo "feat: $(git log --oneline --grep="feat:" | wc -l)"
echo "chore: $(git log --oneline --grep="chore:" | wc -l)"
echo "docs: $(git log --oneline --grep="docs:" | wc -l)"
echo "test: $(git log --oneline --grep="test:" | wc -l)"
```

### Risultato Atteso

Al completamento dovresti avere:

- **15-20 commit** ben organizzati
- **Separation of concerns** perfetta
- **Zero debug code** nei commit
- **Documentazione completa**
- **Test coverage** per funzionalità core
- **Architettura full-stack** funzionante

## ✅ Criteri di Eccellenza

### Master Level Skills

- [ ] **Staging chirurgico** con `git add -p`
- [ ] **Commit atomici** per ogni feature/fix
- [ ] **Storia pulita** senza debug code
- [ ] **Gestione multi-file** coordinata
- [ ] **Workflow professionale** simulato
- [ ] **Documentazione sincronizzata** con codice
- [ ] **Testing integrato** nel processo
- [ ] **Architettura scalabile** implementata

## 🎉 Congratulazioni!

Hai completato con successo un progetto complesso usando staging avanzato! Ora hai le competenze per:

- ✅ Gestire progetti multi-sviluppatore
- ✅ Creare cronologie Git professionali
- ✅ Separare debug da production code
- ✅ Coordinare frontend e backend development
- ✅ Implementare workflow di qualità enterprise

## 🔄 Prossimi Passi

- **Applica queste tecniche** ai tuoi progetti reali
- **Condividi il workflow** con il tuo team
- **Continua con** moduli avanzati del corso Git

---

**🏆 Hai padroneggiato lo staging avanzato!** Sei pronto per gestire qualsiasi progetto complesso con Git!
