# Esercizio 1: Simulazione Conflitti

## 🎯 Obiettivi
- Creare conflitti controllati per pratica
- Sperimentare diverse strategie di risoluzione
- Sviluppare workflow sistematico di risoluzione

## 📋 Scenario
Stai lavorando su un'applicazione web per gestione task. Durante lo sviluppo, più sviluppatori modificano gli stessi componenti creando conflitti multipli. Devi risolverli mantenendo tutte le funzionalità desiderate.

## ⏱️ Durata Stimata
45-60 minuti

## 🛠️ Setup Iniziale

### 1. Crea Progetto Base
```bash
# Crea directory progetto
mkdir task-manager-conflicts
cd task-manager-conflicts

# Inizializza repository
git init

# Crea struttura base
mkdir -p src css
touch README.md
```

### 2. Crea File HTML Base
```bash
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Manager</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <div class="container">
        <h1>Task Manager</h1>
        <div id="task-form">
            <input type="text" id="task-input" placeholder="Enter task">
            <button id="add-btn">Add Task</button>
        </div>
        <ul id="task-list"></ul>
    </div>
    <script src="src/app.js"></script>
</body>
</html>
EOF
```

### 3. Crea CSS Base
```bash
cat > css/styles.css << 'EOF'
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f5f5f5;
}

.container {
    max-width: 600px;
    margin: 0 auto;
    background: white;
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

h1 {
    text-align: center;
    color: #333;
}

#task-form {
    display: flex;
    margin-bottom: 20px;
}

#task-input {
    flex: 1;
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
}

#add-btn {
    padding: 10px 20px;
    background: #007bff;
    color: white;
    border: none;
    border-radius: 4px;
    margin-left: 10px;
    cursor: pointer;
}

#task-list {
    list-style: none;
    padding: 0;
}

.task-item {
    padding: 10px;
    margin: 5px 0;
    background: #f8f9fa;
    border-radius: 4px;
    border-left: 3px solid #007bff;
}
EOF
```

### 4. Crea JavaScript Base
```bash
cat > src/app.js << 'EOF'
// Task Manager Application
class TaskManager {
    constructor() {
        this.tasks = [];
        this.taskCounter = 0;
        this.init();
    }

    init() {
        const addBtn = document.getElementById('add-btn');
        const taskInput = document.getElementById('task-input');
        
        addBtn.addEventListener('click', () => this.addTask());
        taskInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.addTask();
        });
    }

    addTask() {
        const input = document.getElementById('task-input');
        const taskText = input.value.trim();
        
        if (taskText) {
            const task = {
                id: ++this.taskCounter,
                text: taskText,
                completed: false
            };
            
            this.tasks.push(task);
            this.renderTasks();
            input.value = '';
        }
    }

    renderTasks() {
        const taskList = document.getElementById('task-list');
        taskList.innerHTML = '';
        
        this.tasks.forEach(task => {
            const li = document.createElement('li');
            li.className = 'task-item';
            li.textContent = task.text;
            taskList.appendChild(li);
        });
    }
}

// Initialize app
document.addEventListener('DOMContentLoaded', () => {
    new TaskManager();
});
EOF
```

### 5. Commit Iniziale
```bash
git add .
git commit -m "Initial task manager implementation

- Basic HTML structure
- CSS styling for clean interface
- JavaScript task management functionality"
```

## 🌿 Creazione Branch Conflittuali

### 6. Branch Feature: Enhanced UI
```bash
# Crea branch per miglioramenti UI
git checkout -b feature/enhanced-ui

# Modifica CSS per design moderno
cat > css/styles.css << 'EOF'
body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    margin: 0;
    padding: 20px;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
}

.container {
    max-width: 800px;
    margin: 0 auto;
    background: rgba(255, 255, 255, 0.95);
    padding: 30px;
    border-radius: 16px;
    box-shadow: 0 8px 32px rgba(0,0,0,0.1);
    backdrop-filter: blur(10px);
}

h1 {
    text-align: center;
    color: #333;
    font-size: 2.5em;
    margin-bottom: 30px;
    text-shadow: 2px 2px 4px rgba(0,0,0,0.1);
}

#task-form {
    display: flex;
    margin-bottom: 30px;
    gap: 15px;
}

#task-input {
    flex: 1;
    padding: 15px;
    border: 2px solid #e0e0e0;
    border-radius: 12px;
    font-size: 16px;
    transition: border-color 0.3s ease;
}

#task-input:focus {
    outline: none;
    border-color: #667eea;
}

#add-btn {
    padding: 15px 25px;
    background: linear-gradient(45deg, #667eea, #764ba2);
    color: white;
    border: none;
    border-radius: 12px;
    font-size: 16px;
    cursor: pointer;
    transition: transform 0.2s ease;
}

#add-btn:hover {
    transform: translateY(-2px);
}

#task-list {
    list-style: none;
    padding: 0;
}

.task-item {
    padding: 15px 20px;
    margin: 10px 0;
    background: linear-gradient(45deg, #f8f9fa, #e9ecef);
    border-radius: 12px;
    border-left: 4px solid #667eea;
    transition: transform 0.2s ease;
}

.task-item:hover {
    transform: translateX(5px);
}
EOF

# Modifica HTML per features avanzate
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Manager Pro</title>
    <link rel="stylesheet" href="css/styles.css">
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600&display=swap" rel="stylesheet">
</head>
<body>
    <div class="container">
        <h1>✨ Task Manager Pro</h1>
        <div class="stats">
            <span id="total-tasks">Total: 0</span>
            <span id="completed-tasks">Completed: 0</span>
        </div>
        <div id="task-form">
            <input type="text" id="task-input" placeholder="What needs to be done?">
            <button id="add-btn">➕ Add Task</button>
        </div>
        <div class="filters">
            <button class="filter-btn active" data-filter="all">All</button>
            <button class="filter-btn" data-filter="active">Active</button>
            <button class="filter-btn" data-filter="completed">Completed</button>
        </div>
        <ul id="task-list"></ul>
    </div>
    <script src="src/app.js"></script>
</body>
</html>
EOF

# Commit dei miglioramenti UI
git add .
git commit -m "Enhanced UI with modern design

- Gradient background and glassmorphism effects
- Improved typography and spacing
- Added task statistics display
- Filter buttons for task management
- Hover animations and transitions"
```

### 7. Branch Feature: Local Storage
```bash
# Torna a main e crea nuovo branch
git checkout main
git checkout -b feature/local-storage

# Modifica JavaScript per persistenza
cat > src/app.js << 'EOF'
// Task Manager Application with Local Storage
class TaskManager {
    constructor() {
        this.tasks = [];
        this.taskCounter = 0;
        this.storageKey = 'taskManagerData';
        this.init();
        this.loadFromStorage();
    }

    init() {
        const addBtn = document.getElementById('add-btn');
        const taskInput = document.getElementById('task-input');
        
        addBtn.addEventListener('click', () => this.addTask());
        taskInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.addTask();
        });

        // Auto-save every 30 seconds
        setInterval(() => this.saveToStorage(), 30000);
        
        // Save before page unload
        window.addEventListener('beforeunload', () => this.saveToStorage());
    }

    addTask() {
        const input = document.getElementById('task-input');
        const taskText = input.value.trim();
        
        if (taskText) {
            const task = {
                id: ++this.taskCounter,
                text: taskText,
                completed: false,
                createdAt: new Date().toISOString(),
                priority: 'normal'
            };
            
            this.tasks.push(task);
            this.renderTasks();
            this.saveToStorage();
            input.value = '';
        }
    }

    deleteTask(id) {
        this.tasks = this.tasks.filter(task => task.id !== id);
        this.renderTasks();
        this.saveToStorage();
    }

    toggleTask(id) {
        const task = this.tasks.find(t => t.id === id);
        if (task) {
            task.completed = !task.completed;
            task.completedAt = task.completed ? new Date().toISOString() : null;
            this.renderTasks();
            this.saveToStorage();
        }
    }

    renderTasks() {
        const taskList = document.getElementById('task-list');
        taskList.innerHTML = '';
        
        this.tasks.forEach(task => {
            const li = document.createElement('li');
            li.className = `task-item ${task.completed ? 'completed' : ''}`;
            
            li.innerHTML = `
                <span class="task-text">${task.text}</span>
                <div class="task-actions">
                    <button onclick="taskManager.toggleTask(${task.id})" class="toggle-btn">
                        ${task.completed ? '↶' : '✓'}
                    </button>
                    <button onclick="taskManager.deleteTask(${task.id})" class="delete-btn">🗑️</button>
                </div>
            `;
            
            taskList.appendChild(li);
        });
    }

    saveToStorage() {
        const data = {
            tasks: this.tasks,
            taskCounter: this.taskCounter,
            lastSaved: new Date().toISOString()
        };
        
        try {
            localStorage.setItem(this.storageKey, JSON.stringify(data));
            console.log('Tasks saved to localStorage');
        } catch (error) {
            console.error('Failed to save tasks:', error);
        }
    }

    loadFromStorage() {
        try {
            const stored = localStorage.getItem(this.storageKey);
            if (stored) {
                const data = JSON.parse(stored);
                this.tasks = data.tasks || [];
                this.taskCounter = data.taskCounter || 0;
                this.renderTasks();
                console.log('Tasks loaded from localStorage');
            }
        } catch (error) {
            console.error('Failed to load tasks:', error);
            this.tasks = [];
            this.taskCounter = 0;
        }
    }

    clearAllTasks() {
        if (confirm('Are you sure you want to delete all tasks?')) {
            this.tasks = [];
            this.taskCounter = 0;
            this.renderTasks();
            this.saveToStorage();
        }
    }

    exportTasks() {
        const dataStr = JSON.stringify(this.tasks, null, 2);
        const dataUri = 'data:application/json;charset=utf-8,'+ encodeURIComponent(dataStr);
        
        const exportFileDefaultName = `tasks-${new Date().toISOString().split('T')[0]}.json`;
        
        const linkElement = document.createElement('a');
        linkElement.setAttribute('href', dataUri);
        linkElement.setAttribute('download', exportFileDefaultName);
        linkElement.click();
    }
}

// Global reference for inline event handlers
let taskManager;

// Initialize app
document.addEventListener('DOMContentLoaded', () => {
    taskManager = new TaskManager();
    
    // Add export functionality
    document.addEventListener('keydown', (e) => {
        if (e.ctrlKey && e.key === 'e') {
            e.preventDefault();
            taskManager.exportTasks();
        }
    });
});
EOF

# Aggiorna CSS per nuove funzionalità
cat > css/styles.css << 'EOF'
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f5f5f5;
}

.container {
    max-width: 600px;
    margin: 0 auto;
    background: white;
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

h1 {
    text-align: center;
    color: #333;
}

#task-form {
    display: flex;
    margin-bottom: 20px;
}

#task-input {
    flex: 1;
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
}

#add-btn {
    padding: 10px 20px;
    background: #007bff;
    color: white;
    border: none;
    border-radius: 4px;
    margin-left: 10px;
    cursor: pointer;
}

#task-list {
    list-style: none;
    padding: 0;
}

.task-item {
    padding: 10px;
    margin: 5px 0;
    background: #f8f9fa;
    border-radius: 4px;
    border-left: 3px solid #007bff;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.task-item.completed {
    opacity: 0.6;
    text-decoration: line-through;
    border-left-color: #28a745;
}

.task-text {
    flex: 1;
}

.task-actions {
    display: flex;
    gap: 5px;
}

.toggle-btn, .delete-btn {
    padding: 5px 10px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 12px;
}

.toggle-btn {
    background: #28a745;
    color: white;
}

.delete-btn {
    background: #dc3545;
    color: white;
}

.storage-info {
    text-align: center;
    font-size: 12px;
    color: #666;
    margin-top: 20px;
}
EOF

# Commit del local storage
git add .
git commit -m "Add local storage persistence

- Tasks automatically saved to localStorage
- Auto-save every 30 seconds
- Task completion and deletion functionality
- Export tasks to JSON file (Ctrl+E)
- Improved task item layout with actions"
```

### 8. Branch Feature: Validation & Categories
```bash
# Torna a main e crea terzo branch
git checkout main  
git checkout -b feature/validation-categories

# Modifica JavaScript per validazione e categorie
cat > src/app.js << 'EOF'
// Task Manager Application with Validation and Categories
class TaskManager {
    constructor() {
        this.tasks = [];
        this.taskCounter = 0;
        this.categories = ['Work', 'Personal', 'Shopping', 'Health', 'Other'];
        this.init();
    }

    init() {
        const addBtn = document.getElementById('add-btn');
        const taskInput = document.getElementById('task-input');
        
        addBtn.addEventListener('click', () => this.addTask());
        taskInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.addTask();
        });

        this.renderCategories();
    }

    validateTask(taskText) {
        const errors = [];
        
        // Length validation
        if (taskText.length < 3) {
            errors.push('Task must be at least 3 characters long');
        }
        
        if (taskText.length > 100) {
            errors.push('Task must be less than 100 characters');
        }
        
        // Content validation
        if (!/^[a-zA-Z0-9\s\-.,!?]+$/.test(taskText)) {
            errors.push('Task contains invalid characters');
        }
        
        // Duplicate check
        if (this.tasks.some(task => task.text.toLowerCase() === taskText.toLowerCase())) {
            errors.push('This task already exists');
        }
        
        return errors;
    }

    addTask() {
        const input = document.getElementById('task-input');
        const categorySelect = document.getElementById('task-category');
        const prioritySelect = document.getElementById('task-priority');
        const taskText = input.value.trim();
        
        // Validate input
        const validationErrors = this.validateTask(taskText);
        if (validationErrors.length > 0) {
            this.showError(validationErrors.join(', '));
            return;
        }
        
        const task = {
            id: ++this.taskCounter,
            text: taskText,
            category: categorySelect ? categorySelect.value : 'Other',
            priority: prioritySelect ? prioritySelect.value : 'normal',
            completed: false,
            createdAt: new Date().toISOString()
        };
        
        this.tasks.push(task);
        this.renderTasks();
        this.clearError();
        input.value = '';
    }

    renderCategories() {
        const form = document.getElementById('task-form');
        
        // Add category select
        const categorySelect = document.createElement('select');
        categorySelect.id = 'task-category';
        categorySelect.innerHTML = this.categories.map(cat => 
            `<option value="${cat}">${cat}</option>`
        ).join('');
        
        // Add priority select
        const prioritySelect = document.createElement('select');
        prioritySelect.id = 'task-priority';
        prioritySelect.innerHTML = `
            <option value="low">Low Priority</option>
            <option value="normal" selected>Normal Priority</option>
            <option value="high">High Priority</option>
            <option value="urgent">Urgent</option>
        `;
        
        form.appendChild(categorySelect);
        form.appendChild(prioritySelect);
    }

    renderTasks() {
        const taskList = document.getElementById('task-list');
        taskList.innerHTML = '';
        
        // Sort by priority
        const priorityOrder = { urgent: 4, high: 3, normal: 2, low: 1 };
        const sortedTasks = [...this.tasks].sort((a, b) => 
            priorityOrder[b.priority] - priorityOrder[a.priority]
        );
        
        sortedTasks.forEach(task => {
            const li = document.createElement('li');
            li.className = `task-item priority-${task.priority}`;
            
            const priorityIcon = {
                urgent: '🔥',
                high: '⚡',
                normal: '📋',
                low: '📝'
            };
            
            li.innerHTML = `
                <div class="task-content">
                    <span class="task-text">${task.text}</span>
                    <div class="task-meta">
                        <span class="category">${task.category}</span>
                        <span class="priority">${priorityIcon[task.priority]} ${task.priority}</span>
                    </div>
                </div>
            `;
            
            taskList.appendChild(li);
        });
        
        this.updateStats();
    }

    updateStats() {
        const totalTasks = this.tasks.length;
        const completedTasks = this.tasks.filter(t => t.completed).length;
        const urgentTasks = this.tasks.filter(t => t.priority === 'urgent').length;
        
        // Add stats display if not exists
        let statsDiv = document.getElementById('task-stats');
        if (!statsDiv) {
            statsDiv = document.createElement('div');
            statsDiv.id = 'task-stats';
            document.querySelector('.container').appendChild(statsDiv);
        }
        
        statsDiv.innerHTML = `
            <div class="stats">
                <span>Total: ${totalTasks}</span>
                <span>Completed: ${completedTasks}</span>
                <span>Urgent: ${urgentTasks}</span>
            </div>
        `;
    }

    showError(message) {
        let errorDiv = document.getElementById('error-message');
        if (!errorDiv) {
            errorDiv = document.createElement('div');
            errorDiv.id = 'error-message';
            errorDiv.className = 'error';
            document.getElementById('task-form').after(errorDiv);
        }
        errorDiv.textContent = message;
        errorDiv.style.display = 'block';
    }

    clearError() {
        const errorDiv = document.getElementById('error-message');
        if (errorDiv) {
            errorDiv.style.display = 'none';
        }
    }
}

// Initialize app
document.addEventListener('DOMContentLoaded', () => {
    new TaskManager();
});
EOF

# Aggiorna HTML per nuovi controlli
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Manager - Validated</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <div class="container">
        <h1>📋 Task Manager</h1>
        <form id="task-form">
            <input type="text" id="task-input" placeholder="Enter task (3-100 characters)" required>
            <!-- Category and priority selects added by JavaScript -->
            <button type="button" id="add-btn">Add Task</button>
        </form>
        <ul id="task-list"></ul>
    </div>
    <script src="src/app.js"></script>
</body>
</html>
EOF

# Commit della validazione
git add .
git commit -m "Add task validation and categories

- Input validation for length and content
- Category selection (Work, Personal, etc.)
- Priority levels (Low, Normal, High, Urgent)
- Task sorting by priority
- Statistics display for task overview
- Error handling and user feedback"
```

## ⚡ Generazione Conflitti

### 9. Merge Primo Branch (Successo)
```bash
# Torna a main
git checkout main

# Merge primo branch (dovrebbe essere pulito)
git merge feature/enhanced-ui
```

### 10. Merge Secondo Branch (CONFLITTO!)
```bash
# Merge secondo branch - CSS conflict
git merge feature/local-storage
```

**Output atteso:**
```
Auto-merging css/styles.css
CONFLICT (content): Merge conflict in css/styles.css
Auto-merging src/app.js
CONFLICT (content): Merge conflict in src/app.js
Automatic merge failed; fix conflicts and then commit the result.
```

### 11. Analisi Conflitti
```bash
# Vedi file in conflitto
git status

# Esamina conflitti in CSS
echo "=== CSS CONFLICTS ==="
grep -n "<<<<<<\|======\|>>>>>>" css/styles.css

# Esamina conflitti in JavaScript  
echo "=== JS CONFLICTS ==="
grep -n "<<<<<<\|======\|>>>>>>" src/app.js
```

## 🔧 Risoluzione Sistematica

### 12. Risoluzione CSS
```bash
# Apri CSS per risoluzione
code css/styles.css
```

**Strategia**: Combinare il design moderno (enhanced-ui) con le nuove funzionalità (local-storage)

```css
body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    margin: 0;
    padding: 20px;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
}

.container {
    max-width: 800px;
    margin: 0 auto;
    background: rgba(255, 255, 255, 0.95);
    padding: 30px;
    border-radius: 16px;
    box-shadow: 0 8px 32px rgba(0,0,0,0.1);
    backdrop-filter: blur(10px);
}

h1 {
    text-align: center;
    color: #333;
    font-size: 2.5em;
    margin-bottom: 30px;
    text-shadow: 2px 2px 4px rgba(0,0,0,0.1);
}

.stats {
    display: flex;
    justify-content: center;
    gap: 20px;
    margin-bottom: 20px;
    font-weight: 600;
}

#task-form {
    display: flex;
    margin-bottom: 30px;
    gap: 15px;
}

#task-input {
    flex: 1;
    padding: 15px;
    border: 2px solid #e0e0e0;
    border-radius: 12px;
    font-size: 16px;
    transition: border-color 0.3s ease;
}

#task-input:focus {
    outline: none;
    border-color: #667eea;
}

#add-btn {
    padding: 15px 25px;
    background: linear-gradient(45deg, #667eea, #764ba2);
    color: white;
    border: none;
    border-radius: 12px;
    font-size: 16px;
    cursor: pointer;
    transition: transform 0.2s ease;
}

#add-btn:hover {
    transform: translateY(-2px);
}

.filters {
    display: flex;
    justify-content: center;
    gap: 10px;
    margin-bottom: 20px;
}

.filter-btn {
    padding: 8px 16px;
    border: 2px solid #667eea;
    background: transparent;
    color: #667eea;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.3s ease;
}

.filter-btn.active, .filter-btn:hover {
    background: #667eea;
    color: white;
}

#task-list {
    list-style: none;
    padding: 0;
}

.task-item {
    padding: 15px 20px;
    margin: 10px 0;
    background: linear-gradient(45deg, #f8f9fa, #e9ecef);
    border-radius: 12px;
    border-left: 4px solid #667eea;
    transition: transform 0.2s ease;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.task-item:hover {
    transform: translateX(5px);
}

.task-item.completed {
    opacity: 0.6;
    text-decoration: line-through;
    border-left-color: #28a745;
}

.task-text {
    flex: 1;
}

.task-actions {
    display: flex;
    gap: 5px;
}

.toggle-btn, .delete-btn {
    padding: 8px 12px;
    border: none;
    border-radius: 8px;
    cursor: pointer;
    font-size: 14px;
    transition: transform 0.2s ease;
}

.toggle-btn {
    background: #28a745;
    color: white;
}

.delete-btn {
    background: #dc3545;
    color: white;
}

.toggle-btn:hover, .delete-btn:hover {
    transform: scale(1.1);
}

.storage-info {
    text-align: center;
    font-size: 12px;
    color: #666;
    margin-top: 20px;
}
```

### 13. Risoluzione JavaScript
```bash
# Apri JavaScript per risoluzione
code src/app.js
```

**Strategia**: Combinare funzionalità di storage con design avanzato

```javascript
// Task Manager Application - Combined Features
class TaskManager {
    constructor() {
        this.tasks = [];
        this.taskCounter = 0;
        this.storageKey = 'taskManagerData';
        this.currentFilter = 'all';
        this.init();
        this.loadFromStorage();
    }

    init() {
        const addBtn = document.getElementById('add-btn');
        const taskInput = document.getElementById('task-input');
        
        addBtn.addEventListener('click', () => this.addTask());
        taskInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.addTask();
        });

        // Setup filter buttons
        this.setupFilters();

        // Auto-save every 30 seconds
        setInterval(() => this.saveToStorage(), 30000);
        
        // Save before page unload
        window.addEventListener('beforeunload', () => this.saveToStorage());
    }

    setupFilters() {
        const filters = document.querySelectorAll('.filter-btn');
        filters.forEach(btn => {
            btn.addEventListener('click', (e) => {
                // Remove active class from all
                filters.forEach(f => f.classList.remove('active'));
                // Add to clicked
                e.target.classList.add('active');
                this.currentFilter = e.target.dataset.filter;
                this.renderTasks();
            });
        });
    }

    addTask() {
        const input = document.getElementById('task-input');
        const taskText = input.value.trim();
        
        if (taskText) {
            const task = {
                id: ++this.taskCounter,
                text: taskText,
                completed: false,
                createdAt: new Date().toISOString(),
                priority: 'normal'
            };
            
            this.tasks.push(task);
            this.renderTasks();
            this.updateStats();
            this.saveToStorage();
            input.value = '';
        }
    }

    deleteTask(id) {
        this.tasks = this.tasks.filter(task => task.id !== id);
        this.renderTasks();
        this.updateStats();
        this.saveToStorage();
    }

    toggleTask(id) {
        const task = this.tasks.find(t => t.id === id);
        if (task) {
            task.completed = !task.completed;
            task.completedAt = task.completed ? new Date().toISOString() : null;
            this.renderTasks();
            this.updateStats();
            this.saveToStorage();
        }
    }

    getFilteredTasks() {
        switch(this.currentFilter) {
            case 'active':
                return this.tasks.filter(task => !task.completed);
            case 'completed':
                return this.tasks.filter(task => task.completed);
            default:
                return this.tasks;
        }
    }

    renderTasks() {
        const taskList = document.getElementById('task-list');
        taskList.innerHTML = '';
        
        const filteredTasks = this.getFilteredTasks();
        
        filteredTasks.forEach(task => {
            const li = document.createElement('li');
            li.className = `task-item ${task.completed ? 'completed' : ''}`;
            
            li.innerHTML = `
                <span class="task-text">${task.text}</span>
                <div class="task-actions">
                    <button onclick="taskManager.toggleTask(${task.id})" class="toggle-btn">
                        ${task.completed ? '↶' : '✓'}
                    </button>
                    <button onclick="taskManager.deleteTask(${task.id})" class="delete-btn">🗑️</button>
                </div>
            `;
            
            taskList.appendChild(li);
        });
    }

    updateStats() {
        const totalTasks = this.tasks.length;
        const completedTasks = this.tasks.filter(t => t.completed).length;
        
        document.getElementById('total-tasks').textContent = `Total: ${totalTasks}`;
        document.getElementById('completed-tasks').textContent = `Completed: ${completedTasks}`;
    }

    saveToStorage() {
        const data = {
            tasks: this.tasks,
            taskCounter: this.taskCounter,
            lastSaved: new Date().toISOString()
        };
        
        try {
            localStorage.setItem(this.storageKey, JSON.stringify(data));
            console.log('Tasks saved to localStorage');
        } catch (error) {
            console.error('Failed to save tasks:', error);
        }
    }

    loadFromStorage() {
        try {
            const stored = localStorage.getItem(this.storageKey);
            if (stored) {
                const data = JSON.parse(stored);
                this.tasks = data.tasks || [];
                this.taskCounter = data.taskCounter || 0;
                this.renderTasks();
                this.updateStats();
                console.log('Tasks loaded from localStorage');
            }
        } catch (error) {
            console.error('Failed to load tasks:', error);
            this.tasks = [];
            this.taskCounter = 0;
        }
    }

    exportTasks() {
        const dataStr = JSON.stringify(this.tasks, null, 2);
        const dataUri = 'data:application/json;charset=utf-8,'+ encodeURIComponent(dataStr);
        
        const exportFileDefaultName = `tasks-${new Date().toISOString().split('T')[0]}.json`;
        
        const linkElement = document.createElement('a');
        linkElement.setAttribute('href', dataUri);
        linkElement.setAttribute('download', exportFileDefaultName);
        linkElement.click();
    }
}

// Global reference for inline event handlers
let taskManager;

// Initialize app
document.addEventListener('DOMContentLoaded', () => {
    taskManager = new TaskManager();
    
    // Add export functionality
    document.addEventListener('keydown', (e) => {
        if (e.ctrlKey && e.key === 'e') {
            e.preventDefault();
            taskManager.exportTasks();
        }
    });
});
```

### 14. Finalizzazione Prima Risoluzione
```bash
# Aggiungi file risolti
git add css/styles.css src/app.js

# Commit risoluzione
git commit -m "Resolve merge conflicts: Enhanced UI + Local Storage

Combined features:
- Modern gradient design with glassmorphism effects
- Local storage persistence with auto-save
- Task filtering (All/Active/Completed)
- Enhanced statistics display
- Improved task actions with hover effects

Resolution strategy:
- Kept modern UI design from enhanced-ui branch
- Integrated storage functionality from local-storage branch
- Combined task rendering with filtering capabilities"
```

### 15. Merge Terzo Branch (Nuovo Conflitto!)
```bash
# Merge ultimo branch
git merge feature/validation-categories
```

**Nuovo conflitto in JavaScript!**

### 16. Risoluzione Finale Complessa
Ora dobbiamo integrare anche le funzionalità di validazione e categorie.

```bash
# Analizza nuovo conflitto
git status
grep -n "<<<<<<" src/app.js
```

**Strategia**: Creare una versione finale che combina tutte e tre le funzionalità.

## 📊 Verifica e Testing

### 17. Test della Soluzione Finale
```bash
# Crea file di test
cat > test.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Task Manager Test</title>
    <script>
        function runTests() {
            console.log('Testing Task Manager...');
            
            // Test 1: Add valid task
            try {
                document.getElementById('task-input').value = 'Test task';
                document.getElementById('add-btn').click();
                console.log('✅ Add task test passed');
            } catch (e) {
                console.log('❌ Add task test failed:', e);
            }
            
            // Test 2: Filter functionality
            try {
                const filterBtns = document.querySelectorAll('.filter-btn');
                if (filterBtns.length > 0) {
                    console.log('✅ Filter buttons found');
                } else {
                    console.log('❌ Filter buttons missing');
                }
            } catch (e) {
                console.log('❌ Filter test failed:', e);
            }
            
            // Test 3: Local storage
            try {
                const stored = localStorage.getItem('taskManagerData');
                if (stored) {
                    console.log('✅ Local storage working');
                } else {
                    console.log('⚠️ No data in local storage yet');
                }
            } catch (e) {
                console.log('❌ Local storage test failed:', e);
            }
        }
        
        setTimeout(runTests, 1000);
    </script>
</head>
<body>
    <p>Open console to see test results</p>
    <iframe src="index.html" width="100%" height="600px"></iframe>
</body>
</html>
EOF

# Apri test in browser (se disponibile)
# open test.html
```

## 📋 Checklist Completamento

### ✅ Conflitti Risolti
- [ ] CSS: Design moderno + funzionalità storage
- [ ] JavaScript: UI + Storage + Validazione + Categorie  
- [ ] HTML: Template compatibile con tutte le features

### ✅ Funzionalità Integrate
- [ ] Design moderno con gradienti e glassmorphism
- [ ] Persistenza localStorage con auto-save
- [ ] Filtri task (All/Active/Completed)
- [ ] Statistiche task in tempo reale
- [ ] Validazione input utente
- [ ] Categorie e priorità task
- [ ] Export/import funzionalità

### ✅ Test e Verifica
- [ ] Applicazione si carica senza errori
- [ ] Tutti i feature funzionano correttamente
- [ ] Nessun marker di conflitto rimasto
- [ ] Storia Git pulita e comprensibile

## 🎯 Riflessioni sull'Esercizio

### Strategie Utilizzate
1. **Merge progressivo**: Un branch alla volta
2. **Analisi sistematica**: Comprensione di ogni conflitto
3. **Integrazione intelligente**: Combinazione invece di scelta
4. **Testing continuo**: Verifica dopo ogni risoluzione

### Lezioni Apprese
- Conflitti complessi richiedono comprensione del business logic
- La comunicazione con il team è cruciale
- La documentazione delle decisioni aiuta future modifiche
- Testing immediato previene regressioni

### Prevenzione Futura
- Feature branch più piccoli e focalizzati
- Merge frequente da main/develop
- Code review prima di merge
- Coordinamento sviluppo in aree sovrapposte

## ➡️ Prossimo Passo

Complimenti! Hai gestito conflitti multipli complessi. Procedi con il [secondo esercizio](./02-team-conflict-resolution.md) per simulare scenari di team collaboration più realistici.
