# Esempio 2: Risoluzione Conflitti Multi-File

## Scenario
In questo esempio, simulerai una situazione realistica dove due sviluppatori lavorano contemporaneamente su più file di un progetto JavaScript, creando conflitti in diverse parti del codice.

## Setup Iniziale

### 1. Preparazione Repository
```bash
cd ~/git-examples
mkdir conflitti-multi-file
cd conflitti-multi-file
git init
```

### 2. Creazione Struttura Progetto
```bash
# Crea file JavaScript principale
cat > app.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
    }
    
    addTask(title, description) {
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            completed: false,
            createdAt: new Date()
        };
        this.tasks.push(task);
        return task;
    }
    
    getTasks() {
        return this.tasks;
    }
}

module.exports = TaskManager;
EOF

# Crea file di utilità
cat > utils.js << 'EOF'
class DateUtils {
    static formatDate(date) {
        return date.toLocaleDateString();
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
}

module.exports = DateUtils;
EOF

# Crea file di configurazione
cat > config.js << 'EOF'
const config = {
    app: {
        name: "Task Manager",
        version: "1.0.0"
    },
    database: {
        type: "json",
        filename: "tasks.json"
    }
};

module.exports = config;
EOF

git add .
git commit -m "Setup iniziale progetto TaskManager"
```

## Scenario: Due Sviluppatori, Diverse Feature

### 3. Branch Sviluppatore A - Feature "Priorità Task"
```bash
git checkout -b feature/task-priority
```

Modifica `app.js` per aggiungere priorità:
```bash
cat > app.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.priorities = ['low', 'medium', 'high', 'urgent'];
    }
    
    addTask(title, description, priority = 'medium') {
        if (!this.priorities.includes(priority)) {
            throw new Error('Priorità non valida');
        }
        
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            priority: priority,
            completed: false,
            createdAt: new Date()
        };
        this.tasks.push(task);
        return task;
    }
    
    getTasks() {
        return this.tasks.sort((a, b) => {
            const priorityOrder = { urgent: 4, high: 3, medium: 2, low: 1 };
            return priorityOrder[b.priority] - priorityOrder[a.priority];
        });
    }
    
    getTasksByPriority(priority) {
        return this.tasks.filter(task => task.priority === priority);
    }
}

module.exports = TaskManager;
EOF
```

Modifica `utils.js` per supportare priorità:
```bash
cat > utils.js << 'EOF'
class DateUtils {
    static formatDate(date) {
        return date.toLocaleDateString('it-IT');
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
}

class PriorityUtils {
    static getPriorityColor(priority) {
        const colors = {
            low: '#28a745',
            medium: '#ffc107', 
            high: '#fd7e14',
            urgent: '#dc3545'
        };
        return colors[priority] || '#6c757d';
    }
    
    static getPriorityIcon(priority) {
        const icons = {
            low: '🟢',
            medium: '🟡',
            high: '🟠', 
            urgent: '🔴'
        };
        return icons[priority] || '⚪';
    }
}

module.exports = { DateUtils, PriorityUtils };
EOF
```

Modifica `config.js`:
```bash
cat > config.js << 'EOF'
const config = {
    app: {
        name: "Task Manager Pro",
        version: "1.1.0",
        features: ["priorities", "sorting"]
    },
    database: {
        type: "json",
        filename: "tasks.json"
    },
    ui: {
        showPriorities: true,
        defaultPriority: "medium"
    }
};

module.exports = config;
EOF
```

```bash
git add .
git commit -m "Aggiunta sistema priorità task"
```

### 4. Branch Sviluppatore B - Feature "Tag e Categorie"
```bash
git checkout main
git checkout -b feature/task-tags
```

Modifica `app.js` per aggiungere tag:
```bash
cat > app.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.categories = ['work', 'personal', 'study', 'shopping'];
    }
    
    addTask(title, description, category = 'personal', tags = []) {
        if (!this.categories.includes(category)) {
            throw new Error('Categoria non valida');
        }
        
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            category: category,
            tags: Array.isArray(tags) ? tags : [tags],
            completed: false,
            createdAt: new Date(),
            updatedAt: new Date()
        };
        this.tasks.push(task);
        return task;
    }
    
    getTasks() {
        return this.tasks.sort((a, b) => b.updatedAt - a.updatedAt);
    }
    
    getTasksByCategory(category) {
        return this.tasks.filter(task => task.category === category);
    }
    
    getTasksByTag(tag) {
        return this.tasks.filter(task => task.tags.includes(tag));
    }
    
    addTagToTask(taskId, tag) {
        const task = this.tasks.find(t => t.id === taskId);
        if (task && !task.tags.includes(tag)) {
            task.tags.push(tag);
            task.updatedAt = new Date();
        }
        return task;
    }
}

module.exports = TaskManager;
EOF
```

Modifica `utils.js` per supportare tag:
```bash
cat > utils.js << 'EOF'
class DateUtils {
    static formatDate(date) {
        return date.toLocaleDateString('en-US');
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
    
    static getRelativeTime(date) {
        const now = new Date();
        const diffMs = now - date;
        const diffMins = Math.floor(diffMs / 60000);
        
        if (diffMins < 1) return 'ora';
        if (diffMins < 60) return `${diffMins} minuti fa`;
        if (diffMins < 1440) return `${Math.floor(diffMins / 60)} ore fa`;
        return `${Math.floor(diffMins / 1440)} giorni fa`;
    }
}

class TagUtils {
    static formatTags(tags) {
        return tags.map(tag => `#${tag}`).join(' ');
    }
    
    static getTagColor(tag) {
        // Hash del tag per colore consistente
        let hash = 0;
        for (let i = 0; i < tag.length; i++) {
            hash = tag.charCodeAt(i) + ((hash << 5) - hash);
        }
        const hue = hash % 360;
        return `hsl(${hue}, 70%, 50%)`;
    }
}

module.exports = { DateUtils, TagUtils };
EOF
```

Modifica `config.js`:
```bash
cat > config.js << 'EOF'
const config = {
    app: {
        name: "Task Manager Plus",
        version: "1.2.0",
        features: ["tags", "categories", "search"]
    },
    database: {
        type: "json",
        filename: "tasks.json",
        backup: true
    },
    ui: {
        showTags: true,
        maxTagsDisplay: 5,
        categoryColors: {
            work: "#007bff",
            personal: "#28a745", 
            study: "#ffc107",
            shopping: "#17a2b8"
        }
    }
};

module.exports = config;
EOF
```

```bash
git add .
git commit -m "Aggiunta sistema tag e categorie"
```

## 5. Tentativo di Merge - Conflitti Multipli

```bash
git checkout main
git merge feature/task-priority
# Merge successful

git merge feature/task-tags
# CONFLITTI!
```

## Analisi dei Conflitti

### Conflitto in `app.js`
```javascript
<<<<<<< HEAD
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.priorities = ['low', 'medium', 'high', 'urgent'];
    }
    
    addTask(title, description, priority = 'medium') {
        if (!this.priorities.includes(priority)) {
            throw new Error('Priorità non valida');
        }
        
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            priority: priority,
            completed: false,
            createdAt: new Date()
        };
=======
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.categories = ['work', 'personal', 'study', 'shopping'];
    }
    
    addTask(title, description, category = 'personal', tags = []) {
        if (!this.categories.includes(category)) {
            throw new Error('Categoria non valida');
        }
        
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            category: category,
            tags: Array.isArray(tags) ? tags : [tags],
            completed: false,
            createdAt: new Date(),
            updatedAt: new Date()
        };
>>>>>>> feature/task-tags
```

### Conflitto in `utils.js`
```javascript
<<<<<<< HEAD
class DateUtils {
    static formatDate(date) {
        return date.toLocaleDateString('it-IT');
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
}

class PriorityUtils {
    static getPriorityColor(priority) {
        const colors = {
            low: '#28a745',
            medium: '#ffc107', 
            high: '#fd7e14',
            urgent: '#dc3545'
        };
        return colors[priority] || '#6c757d';
    }
    
    static getPriorityIcon(priority) {
        const icons = {
            low: '🟢',
            medium: '🟡',
            high: '🟠', 
            urgent: '🔴'
        };
        return icons[priority] || '⚪';
    }
}

module.exports = { DateUtils, PriorityUtils };
=======
class DateUtils {
    static formatDate(date) {
        return date.toLocaleDateString('en-US');
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
    
    static getRelativeTime(date) {
        const now = new Date();
        const diffMs = now - date;
        const diffMins = Math.floor(diffMs / 60000);
        
        if (diffMins < 1) return 'ora';
        if (diffMins < 60) return `${diffMins} minuti fa`;
        if (diffMins < 1440) return `${Math.floor(diffMins / 60)} ore fa`;
        return `${Math.floor(diffMins / 1440)} giorni fa`;
    }
}

class TagUtils {
    static formatTags(tags) {
        return tags.map(tag => `#${tag}`).join(' ');
    }
    
    static getTagColor(tag) {
        // Hash del tag per colore consistente
        let hash = 0;
        for (let i = 0; i < tag.length; i++) {
            hash = tag.charCodeAt(i) + ((hash << 5) - hash);
        }
        const hue = hash % 360;
        return `hsl(${hue}, 70%, 50%)`;
    }
}

module.exports = { DateUtils, TagUtils };
>>>>>>> feature/task-tags
```

## 6. Risoluzione Strategica dei Conflitti

### Strategia: Integrazione Completa delle Feature

Risolvi `app.js` combinando entrambe le funzionalità:
```bash
cat > app.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.priorities = ['low', 'medium', 'high', 'urgent'];
        this.categories = ['work', 'personal', 'study', 'shopping'];
    }
    
    addTask(title, description, options = {}) {
        const {
            priority = 'medium',
            category = 'personal',
            tags = []
        } = options;
        
        if (!this.priorities.includes(priority)) {
            throw new Error('Priorità non valida');
        }
        
        if (!this.categories.includes(category)) {
            throw new Error('Categoria non valida');
        }
        
        const task = {
            id: this.nextId++,
            title: title,
            description: description,
            priority: priority,
            category: category,
            tags: Array.isArray(tags) ? tags : [tags],
            completed: false,
            createdAt: new Date(),
            updatedAt: new Date()
        };
        this.tasks.push(task);
        return task;
    }
    
    getTasks() {
        return this.tasks.sort((a, b) => {
            // Prima ordina per priorità
            const priorityOrder = { urgent: 4, high: 3, medium: 2, low: 1 };
            const priorityDiff = priorityOrder[b.priority] - priorityOrder[a.priority];
            
            // Se stessa priorità, ordina per data aggiornamento
            if (priorityDiff === 0) {
                return b.updatedAt - a.updatedAt;
            }
            return priorityDiff;
        });
    }
    
    getTasksByPriority(priority) {
        return this.tasks.filter(task => task.priority === priority);
    }
    
    getTasksByCategory(category) {
        return this.tasks.filter(task => task.category === category);
    }
    
    getTasksByTag(tag) {
        return this.tasks.filter(task => task.tags.includes(tag));
    }
    
    addTagToTask(taskId, tag) {
        const task = this.tasks.find(t => t.id === taskId);
        if (task && !task.tags.includes(tag)) {
            task.tags.push(tag);
            task.updatedAt = new Date();
        }
        return task;
    }
    
    updateTaskPriority(taskId, priority) {
        if (!this.priorities.includes(priority)) {
            throw new Error('Priorità non valida');
        }
        
        const task = this.tasks.find(t => t.id === taskId);
        if (task) {
            task.priority = priority;
            task.updatedAt = new Date();
        }
        return task;
    }
}

module.exports = TaskManager;
EOF
```

Risolvi `utils.js` combinando tutte le utilità:
```bash
cat > utils.js << 'EOF'
class DateUtils {
    static formatDate(date, locale = 'it-IT') {
        return date.toLocaleDateString(locale);
    }
    
    static isToday(date) {
        const today = new Date();
        return date.toDateString() === today.toDateString();
    }
    
    static getRelativeTime(date) {
        const now = new Date();
        const diffMs = now - date;
        const diffMins = Math.floor(diffMs / 60000);
        
        if (diffMins < 1) return 'ora';
        if (diffMins < 60) return `${diffMins} minuti fa`;
        if (diffMins < 1440) return `${Math.floor(diffMins / 60)} ore fa`;
        return `${Math.floor(diffMins / 1440)} giorni fa`;
    }
}

class PriorityUtils {
    static getPriorityColor(priority) {
        const colors = {
            low: '#28a745',
            medium: '#ffc107', 
            high: '#fd7e14',
            urgent: '#dc3545'
        };
        return colors[priority] || '#6c757d';
    }
    
    static getPriorityIcon(priority) {
        const icons = {
            low: '🟢',
            medium: '🟡',
            high: '🟠', 
            urgent: '🔴'
        };
        return icons[priority] || '⚪';
    }
    
    static getPriorityWeight(priority) {
        const weights = { urgent: 4, high: 3, medium: 2, low: 1 };
        return weights[priority] || 0;
    }
}

class TagUtils {
    static formatTags(tags) {
        return tags.map(tag => `#${tag}`).join(' ');
    }
    
    static getTagColor(tag) {
        // Hash del tag per colore consistente
        let hash = 0;
        for (let i = 0; i < tag.length; i++) {
            hash = tag.charCodeAt(i) + ((hash << 5) - hash);
        }
        const hue = hash % 360;
        return `hsl(${hue}, 70%, 50%)`;
    }
    
    static validateTag(tag) {
        return typeof tag === 'string' && 
               tag.length >= 2 && 
               tag.length <= 20 && 
               /^[a-zA-Z0-9_-]+$/.test(tag);
    }
}

module.exports = { DateUtils, PriorityUtils, TagUtils };
EOF
```

Risolvi `config.js`:
```bash
cat > config.js << 'EOF'
const config = {
    app: {
        name: "Task Manager Ultimate",
        version: "1.3.0",
        features: ["priorities", "tags", "categories", "sorting", "search"]
    },
    database: {
        type: "json",
        filename: "tasks.json",
        backup: true
    },
    ui: {
        showPriorities: true,
        showTags: true,
        defaultPriority: "medium",
        maxTagsDisplay: 5,
        locale: "it-IT",
        categoryColors: {
            work: "#007bff",
            personal: "#28a745", 
            study: "#ffc107",
            shopping: "#17a2b8"
        }
    },
    validation: {
        maxTitleLength: 100,
        maxDescriptionLength: 500,
        maxTagsPerTask: 10
    }
};

module.exports = config;
EOF
```

### 7. Finalizzazione Merge
```bash
git add .
git commit -m "Merge feature/task-tags: integrazione completa priorità e tag

- Combinato sistema priorità e tag/categorie
- Aggiornato ordinamento tasks (priorità + data)
- Integrato tutte le utilità (Date, Priority, Tag)
- Unificata configurazione con tutte le feature
- Mantenuta retrocompatibilità API"

# Verifica lo stato
git log --oneline --graph -10
```

## 8. Test della Soluzione Integrata

Crea un file di test:
```bash
cat > test.js << 'EOF'
const TaskManager = require('./app.js');
const { DateUtils, PriorityUtils, TagUtils } = require('./utils.js');
const config = require('./config.js');

console.log(`🚀 ${config.app.name} v${config.app.version}`);
console.log(`Features: ${config.app.features.join(', ')}\n`);

const tm = new TaskManager();

// Test integrazione completa
const task1 = tm.addTask('Completare progetto', 'Finire il task manager', {
    priority: 'urgent',
    category: 'work',
    tags: ['javascript', 'git', 'progetto']
});

const task2 = tm.addTask('Spesa settimanale', 'Comprare ingredienti', {
    priority: 'medium',
    category: 'shopping',
    tags: ['casa', 'routine']
});

const task3 = tm.addTask('Studiare Git', 'Approfondire merge conflicts', {
    priority: 'high',
    category: 'study',
    tags: ['git', 'tutorial', 'conflitti']
});

console.log('📋 Tasks creati:');
tm.getTasks().forEach(task => {
    console.log(`${PriorityUtils.getPriorityIcon(task.priority)} [${task.priority.toUpperCase()}] ${task.title}`);
    console.log(`   📂 ${task.category} | 🏷️ ${TagUtils.formatTags(task.tags)}`);
    console.log(`   🕐 ${DateUtils.getRelativeTime(task.createdAt)}\n`);
});

console.log('🔥 Tasks urgenti:', tm.getTasksByPriority('urgent').length);
console.log('💼 Tasks di lavoro:', tm.getTasksByCategory('work').length);
console.log('🏷️ Tasks con tag "git":', tm.getTasksByTag('git').length);
EOF

node test.js
```

## Lezioni Apprese

### 1. **Conflitti Multipli Complessi**
- File multipli con modifiche sovrapposte
- Conflitti semantici oltre che sintattici
- Necessità di integrazione strategica

### 2. **Risoluzione Intelligente**
- Analisi dell'intento di ogni sviluppatore
- Combinazione delle funzionalità invece di scelta
- Mantenimento della coerenza architetturale

### 3. **Best Practices**
- **Comunicazione**: Coordinamento tra sviluppatori
- **API Design**: Parametri opzionali per retrocompatibilità
- **Testing**: Verifica dell'integrazione post-merge
- **Documentation**: Commit messages descrittivi

### 4. **Prevenzione Futura**
- Feature flags per sviluppo incrementale
- Code review pre-merge
- Integrazione continua con test automatici

## Prossimi Passi
1. Implementare test automatici
2. Configurare CI/CD pipeline
3. Stabilire workflow di team development
4. Documentare API unificate
