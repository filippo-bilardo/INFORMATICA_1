# 02 - Esercizio: Workflow Staging Team

## 📖 Descrizione

Questo esercizio simula un ambiente di team reale dove devi gestire la staging area durante collaborazione, conflitti e situazioni di emergenza. Metterai in pratica tecniche avanzate di staging in scenari complessi.

## 🎯 Obiettivi

- Gestire staging area durante conflitti
- Simulare workflow di team con staging
- Risolvere emergenze preservando lavoro in staging
- Dimostrare padronanza di tecniche avanzate

## 📋 Prerequisiti

- Completamento esercizio precedente
- Comprensione di rebase e merge
- Familiarità con git stash

## ⏱️ Durata Stimata

**60-90 minuti**

## 🚀 Setup: Simulazione Team

### Step 1: Repository Condiviso
```bash
# Crea repository "centrale"
mkdir team-staging-exercise
cd team-staging-exercise
git init

# Crea progetto iniziale: Task Management App
mkdir src tests docs
cat > src/task-manager.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.users = [];
    }

    addTask(task) {
        this.tasks.push(task);
    }

    getTask(id) {
        return this.tasks.find(t => t.id === id);
    }

    addUser(user) {
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(u => u.id === id);
    }
}

module.exports = TaskManager;
EOF

git add .
git commit -m "Initial task manager implementation"

# Simula repository remoto
cd ..
git clone --bare team-staging-exercise team-staging-exercise.git
cd team-staging-exercise
git remote add origin ../team-staging-exercise.git
git push origin main
```

### Step 2: Clone per "Teammate"
```bash
cd ..
git clone team-staging-exercise.git teammate-workspace
cd team-staging-exercise  # Tu torni al tuo workspace
```

## 📝 Parte 1: Lavoro Parallelo con Staging

### Task 1A: Il Tuo Lavoro (Staging Organizzato)

Implementa queste modifiche nel tuo workspace e organizzale in staging **senza committare subito**:

```bash
# Modifica src/task-manager.js con tutte queste modifiche insieme
cat > src/task-manager.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.users = [];
        this.projects = [];        // TUO: nuova feature progetti
        this.nextId = 1;          // TUO: sistema ID automatico
    }

    addTask(taskData) {
        // TUO: validazione input
        if (!taskData.title || taskData.title.trim() === '') {
            throw new Error('Task title is required');
        }

        // TUO: sistema ID automatico
        const task = {
            id: this.nextId++,
            title: taskData.title.trim(),
            description: taskData.description || '',
            assigneeId: taskData.assigneeId,
            projectId: taskData.projectId || null,
            status: 'todo',
            createdAt: new Date().toISOString()
        };

        this.tasks.push(task);
        return task;
    }

    getTask(taskId) {           // TUO: rinominato parametro
        return this.tasks.find(task => task.id === taskId);
    }

    // TUO: nuovi metodi per gestione progetti
    addProject(projectData) {
        if (!projectData.name || projectData.name.trim() === '') {
            throw new Error('Project name is required');
        }

        const project = {
            id: this.nextId++,
            name: projectData.name.trim(),
            description: projectData.description || '',
            createdAt: new Date().toISOString(),
            active: true
        };

        this.projects.push(project);
        return project;
    }

    getProject(projectId) {
        return this.projects.find(project => project.id === projectId);
    }

    getTasksByProject(projectId) {
        return this.tasks.filter(task => task.projectId === projectId);
    }

    addUser(userData) {
        // TUO: validazione utente
        if (!userData.username || userData.username.trim() === '') {
            throw new Error('Username is required');
        }

        const user = {
            id: this.nextId++,
            username: userData.username.trim(),
            email: userData.email || '',
            createdAt: new Date().toISOString()
        };

        this.users.push(user);
        return user;
    }

    getUser(userId) {           // TUO: rinominato parametro
        return this.users.find(user => user.id === userId);
    }

    // TUO: metodi di utilità
    getTasksByUser(userId) {
        return this.tasks.filter(task => task.assigneeId === userId);
    }

    updateTaskStatus(taskId, newStatus) {
        const task = this.getTask(taskId);
        if (!task) {
            throw new Error('Task not found');
        }
        
        const validStatuses = ['todo', 'in-progress', 'done'];
        if (!validStatuses.includes(newStatus)) {
            throw new Error('Invalid status');
        }

        task.status = newStatus;
        task.updatedAt = new Date().toISOString();
        return task;
    }
}

module.exports = TaskManager;
EOF
```

Ora organizza in staging selettivo creando **3 gruppi staged** ma non committare:

```bash
# Gruppo 1: Staging validazione input
git add -p src/task-manager.js
# Stage solo: validazione in addTask() e addUser()

# Gruppo 2: Staging sistema ID
git add -p src/task-manager.js  
# Stage solo: nextId property e uso di this.nextId++

# Gruppo 3: Staging progetti feature
git add -p src/task-manager.js
# Stage solo: projects property, addProject(), getProject(), getTasksByProject()

# Lascia unstaged: rinominazione parametri, metodi utility (getTasksByUser, updateTaskStatus)
```

### Task 1B: Lavoro del Teammate

Mentre tu organizzi staging, il teammate pusha modifiche:

```bash
cd ../teammate-workspace

# Teammate implementa sistema notifiche
cat > src/task-manager.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.users = [];
        this.notifications = [];    // TEAMMATE: sistema notifiche
    }

    addTask(task) {
        this.tasks.push(task);
        
        // TEAMMATE: crea notifica per task
        this.createNotification({
            type: 'task_created',
            message: `New task created: ${task.title}`,
            userId: task.assigneeId,
            createdAt: new Date().toISOString()
        });
    }

    getTask(id) {
        return this.tasks.find(t => t.id === id);
    }

    addUser(user) {
        this.users.push(user);
        
        // TEAMMATE: notifica benvenuto
        this.createNotification({
            type: 'user_welcome',
            message: `Welcome ${user.username}!`,
            userId: user.id,
            createdAt: new Date().toISOString()
        });
    }

    getUser(id) {
        return this.users.find(u => u.id === id);
    }

    // TEAMMATE: sistema notifiche
    createNotification(notificationData) {
        const notification = {
            id: Date.now(),
            type: notificationData.type,
            message: notificationData.message,
            userId: notificationData.userId,
            read: false,
            createdAt: notificationData.createdAt
        };
        
        this.notifications.push(notification);
        return notification;
    }

    getNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId);
    }

    markNotificationRead(notificationId) {
        const notification = this.notifications.find(n => n.id === notificationId);
        if (notification) {
            notification.read = true;
            notification.readAt = new Date().toISOString();
        }
        return notification;
    }

    getUnreadNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId && !n.read);
    }
}

module.exports = TaskManager;
EOF

git add .
git commit -m "Implement notification system

- Add notifications property to constructor
- Create notifications on task/user creation  
- Add methods to manage notifications
- Track read/unread status"

git push origin main
```

## 🔥 Parte 2: Gestione Conflitti con Staging

### Task 2A: Il Conflitto si Manifesta

Torna al tuo workspace e tenta di sincronizzare:

```bash
cd ../team-staging-exercise

# Verifica il tuo stato attuale
git status
# Should show:
# Changes to be committed: (3 staged groups)
# Changes not staged for commit: (remaining changes)

# Tenta fetch e vedi divergenza
git fetch origin
git log --oneline origin/main..HEAD
# (no commits - you haven't committed yet)

git log --oneline HEAD..origin/main  
# abc1234 Implement notification system
```

### Task 2B: Strategia di Risoluzione

**Sfida**: Devi integrare le modifiche del teammate mantenendo la tua organizzazione di staging.

```bash
# 1. Backup completo della situazione staging
git stash push --staged -m "Backup: validation + ID system + projects"
git stash push -m "Backup: remaining unstaged changes"

# 2. Pull delle modifiche teammate  
git pull origin main

# 3. Analizza il nuovo stato
cat src/task-manager.js  # Vedi le modifiche del teammate

# 4. Integra le tue modifiche gradualmente
```

### Task 2C: Integrazione Intelligente

Ora devi re-applicare il tuo lavoro integrandolo con quello del teammate:

```bash
# Prima ripristina le modifiche unstaged
git stash pop  # Le modifiche unstaged (rinominazioni + utility)

# Risolvi conflitti base se necessario, poi:
git add src/task-manager.js
git commit -m "Integrate teammate notifications with utility methods

- Add getTasksByUser() and updateTaskStatus() methods  
- Rename parameters for consistency
- Maintain compatibility with notification system"

# Poi ripristina le modifiche staged più complesse
git stash pop  # Le modifiche staged (validation + ID + projects)

# Questo creerà conflitti - risolvili intelligentemente
```

### Task 2D: Risoluzione Conflitti Avanzata

Il file mostrerà conflitti. Creane una versione che integra tutto:

```bash
# Risolvi manualmente creando una versione che integra:
# - Sistema notifiche del teammate
# - Tue validazioni
# - Tuo sistema ID  
# - Tue funzionalità progetti
# - Tutto compatibile insieme

# Esempio di risoluzione:
cat > src/task-manager.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.users = [];
        this.projects = [];        // TUO
        this.notifications = [];   // TEAMMATE  
        this.nextId = 1;          // TUO
    }

    addTask(taskData) {
        // TUO: validazione input
        if (!taskData.title || taskData.title.trim() === '') {
            throw new Error('Task title is required');
        }

        const task = {
            id: this.nextId++,      // TUO: ID automatico
            title: taskData.title.trim(),
            description: taskData.description || '',
            assigneeId: taskData.assigneeId,
            projectId: taskData.projectId || null,  // TUO
            status: 'todo',         // TUO  
            createdAt: new Date().toISOString()
        };

        this.tasks.push(task);

        // TEAMMATE: notifiche (adattato al tuo sistema)
        if (task.assigneeId) {
            this.createNotification({
                type: 'task_created',
                message: `New task created: ${task.title}`,
                userId: task.assigneeId,
                createdAt: new Date().toISOString()
            });
        }

        return task;
    }

    getTask(taskId) {           // TUO: parametro rinominato
        return this.tasks.find(task => task.id === taskId);
    }

    addUser(userData) {
        // TUO: validazione
        if (!userData.username || userData.username.trim() === '') {
            throw new Error('Username is required');
        }

        const user = {
            id: this.nextId++,      // TUO: ID automatico
            username: userData.username.trim(),
            email: userData.email || '',
            createdAt: new Date().toISOString()
        };

        this.users.push(user);

        // TEAMMATE: notifica benvenuto
        this.createNotification({
            type: 'user_welcome',
            message: `Welcome ${user.username}!`,
            userId: user.id,
            createdAt: new Date().toISOString()
        });

        return user;
    }

    getUser(userId) {           // TUO: parametro rinominato
        return this.users.find(user => user.id === userId);
    }

    // TUO: gestione progetti
    addProject(projectData) {
        if (!projectData.name || projectData.name.trim() === '') {
            throw new Error('Project name is required');
        }

        const project = {
            id: this.nextId++,
            name: projectData.name.trim(),
            description: projectData.description || '',
            createdAt: new Date().toISOString(),
            active: true
        };

        this.projects.push(project);
        return project;
    }

    getProject(projectId) {
        return this.projects.find(project => project.id === projectId);
    }

    getTasksByProject(projectId) {
        return this.tasks.filter(task => task.projectId === projectId);
    }

    // TUO: metodi utility
    getTasksByUser(userId) {
        return this.tasks.filter(task => task.assigneeId === userId);
    }

    updateTaskStatus(taskId, newStatus) {
        const task = this.getTask(taskId);
        if (!task) {
            throw new Error('Task not found');
        }
        
        const validStatuses = ['todo', 'in-progress', 'done'];
        if (!validStatuses.includes(newStatus)) {
            throw new Error('Invalid status');
        }

        const oldStatus = task.status;
        task.status = newStatus;
        task.updatedAt = new Date().toISOString();

        // INTEGRAZIONE: notifica quando status cambia
        if (task.assigneeId && oldStatus !== newStatus) {
            this.createNotification({
                type: 'task_status_changed',
                message: `Task "${task.title}" changed from ${oldStatus} to ${newStatus}`,
                userId: task.assigneeId,
                createdAt: new Date().toISOString()
            });
        }

        return task;
    }

    // TEAMMATE: sistema notifiche (mantenuto invariato)
    createNotification(notificationData) {
        const notification = {
            id: this.nextId++,      // INTEGRAZIONE: usa il tuo sistema ID
            type: notificationData.type,
            message: notificationData.message,
            userId: notificationData.userId,
            read: false,
            createdAt: notificationData.createdAt
        };
        
        this.notifications.push(notification);
        return notification;
    }

    getNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId);
    }

    markNotificationRead(notificationId) {
        const notification = this.notifications.find(n => n.id === notificationId);
        if (notification) {
            notification.read = true;
            notification.readAt = new Date().toISOString();
        }
        return notification;
    }

    getUnreadNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId && !n.read);
    }
}

module.exports = TaskManager;
EOF
```

### Task 2E: Staging Organizzato Post-Conflitto

Ora ri-organizza in staging logico per la versione integrata:

```bash
# Commit 1: Integrazione validazione
git add -p src/task-manager.js
# Stage solo le validazioni integrate (addTask e addUser validation)
git commit -m "Integrate input validation with notification system

- Add validation for task title and user username
- Ensure notifications work with validated inputs
- Maintain backward compatibility"

# Commit 2: Sistema ID unificato  
git add -p src/task-manager.js
# Stage solo: nextId property e tutti gli usi di this.nextId++
git commit -m "Unify ID generation across all entities

- Replace separate ID systems with unified nextId
- Update notifications to use unified ID system
- Ensure consistent ID generation for tasks, users, projects, notifications"

# Commit 3: Feature progetti integrata
git add -p src/task-manager.js  
# Stage solo: projects property, addProject(), getProject(), getTasksByProject()
git commit -m "Add project management with notification integration

- Add projects property and CRUD operations
- Integrate project IDs with task system
- Maintain notification compatibility"

# Commit 4: Utility methods + enhanced integrations
git add src/task-manager.js
git commit -m "Add utility methods and enhance notification integration

- Add getTasksByUser() and updateTaskStatus() methods
- Enhance updateTaskStatus() to trigger notifications
- Rename parameters for consistency (id -> taskId, userId)
- Add status change notifications for better UX"
```

## 🚨 Parte 3: Gestione Emergenze

### Task 3A: Emergenza Hotfix

Mentre hai modifiche in staging, arriva una richiesta di hotfix urgente:

```bash
# Simula: il teammate trova un bug critico in produzione
cd ../teammate-workspace
git pull origin main

# Bug: le notifiche crashano se userId è null
cat > src/task-manager.js << 'EOF'
class TaskManager {
    constructor() {
        this.tasks = [];
        this.users = [];
        this.projects = [];
        this.notifications = [];
        this.nextId = 1;
    }

    addTask(taskData) {
        if (!taskData.title || taskData.title.trim() === '') {
            throw new Error('Task title is required');
        }

        const task = {
            id: this.nextId++,
            title: taskData.title.trim(),
            description: taskData.description || '',
            assigneeId: taskData.assigneeId,
            projectId: taskData.projectId || null,
            status: 'todo',
            createdAt: new Date().toISOString()
        };

        this.tasks.push(task);

        // BUGFIX: Check if assigneeId exists before creating notification
        if (task.assigneeId && this.getUser(task.assigneeId)) {
            this.createNotification({
                type: 'task_created',
                message: `New task created: ${task.title}`,
                userId: task.assigneeId,
                createdAt: new Date().toISOString()
            });
        }

        return task;
    }

    // ... resto del file identico al tuo ultimo commit ...
    // (copia il resto per brevità)

    getTask(taskId) {
        return this.tasks.find(task => task.id === taskId);
    }

    addUser(userData) {
        if (!userData.username || userData.username.trim() === '') {
            throw new Error('Username is required');
        }

        const user = {
            id: this.nextId++,
            username: userData.username.trim(),
            email: userData.email || '',
            createdAt: new Date().toISOString()
        };

        this.users.push(user);

        this.createNotification({
            type: 'user_welcome',
            message: `Welcome ${user.username}!`,
            userId: user.id,
            createdAt: new Date().toISOString()
        });

        return user;
    }

    getUser(userId) {
        return this.users.find(user => user.id === userId);
    }

    addProject(projectData) {
        if (!projectData.name || projectData.name.trim() === '') {
            throw new Error('Project name is required');
        }

        const project = {
            id: this.nextId++,
            name: projectData.name.trim(),
            description: projectData.description || '',
            createdAt: new Date().toISOString(),
            active: true
        };

        this.projects.push(project);
        return project;
    }

    getProject(projectId) {
        return this.projects.find(project => project.id === projectId);
    }

    getTasksByProject(projectId) {
        return this.tasks.filter(task => task.projectId === projectId);
    }

    getTasksByUser(userId) {
        return this.tasks.filter(task => task.assigneeId === userId);
    }

    updateTaskStatus(taskId, newStatus) {
        const task = this.getTask(taskId);
        if (!task) {
            throw new Error('Task not found');
        }
        
        const validStatuses = ['todo', 'in-progress', 'done'];
        if (!validStatuses.includes(newStatus)) {
            throw new Error('Invalid status');
        }

        const oldStatus = task.status;
        task.status = newStatus;
        task.updatedAt = new Date().toISOString();

        // BUGFIX: Check if user exists before creating notification
        if (task.assigneeId && this.getUser(task.assigneeId) && oldStatus !== newStatus) {
            this.createNotification({
                type: 'task_status_changed',
                message: `Task "${task.title}" changed from ${oldStatus} to ${newStatus}`,
                userId: task.assigneeId,
                createdAt: new Date().toISOString()
            });
        }

        return task;
    }

    createNotification(notificationData) {
        const notification = {
            id: this.nextId++,
            type: notificationData.type,
            message: notificationData.message,
            userId: notificationData.userId,
            read: false,
            createdAt: notificationData.createdAt
        };
        
        this.notifications.push(notification);
        return notification;
    }

    getNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId);
    }

    markNotificationRead(notificationId) {
        const notification = this.notifications.find(n => n.id === notificationId);
        if (notification) {
            notification.read = true;
            notification.readAt = new Date().toISOString();
        }
        return notification;
    }

    getUnreadNotifications(userId) {
        return this.notifications.filter(n => n.userId === userId && !n.read);
    }
}

module.exports = TaskManager;
EOF

git add .
git commit -m "HOTFIX: Prevent notification crashes with invalid user IDs

- Add user existence check before creating task notifications
- Add user existence check before creating status change notifications  
- Prevent runtime crashes in production

Critical bug fix for production deployment."

git push origin main
```

### Task 3B: Hotfix Integration con Staging Attiva

Torna al tuo workspace dove hai staging attiva:

```bash
cd ../team-staging-exercise

# Verifica staging attuale
git status
# Potresti avere ancora modifiche in staging o working directory

# Strategia: Salva tutto, applica hotfix, reintegra
git stash push --include-untracked -m "Complete backup before hotfix"

# Pull del hotfix
git pull origin main

# Verifica che il hotfix sia applicato
git log --oneline -2

# Ripristina il tuo lavoro e reintegralo
git stash pop

# Se ci sono conflitti, il hotfix ha la precedenza
# Risolvi manualmente mantenendo le correzioni del hotfix
```

## 🎯 Parte 4: Verifica e Cleanup

### Task 4A: Verifica Integrità

```bash
# Controlla cronologia finale
git log --oneline -10

# Verifica che il codice funzioni
node -e "
const TaskManager = require('./src/task-manager.js');
const tm = new TaskManager();

// Test integrazione completa
const user = tm.addUser({username: 'testuser', email: 'test@example.com'});
console.log('User created:', user.id);

const project = tm.addProject({name: 'Test Project'});
console.log('Project created:', project.id);

const task = tm.addTask({
    title: 'Test Task',
    assigneeId: user.id,
    projectId: project.id
});
console.log('Task created:', task.id);

const notifications = tm.getNotifications(user.id);
console.log('Notifications:', notifications.length);

tm.updateTaskStatus(task.id, 'done');
const updatedNotifications = tm.getNotifications(user.id);
console.log('Updated notifications:', updatedNotifications.length);

console.log('✅ All integrations working!');
"
```

### Task 4B: Final Staging Organization

Organizza eventuali modifiche finali in staging pulito:

```bash
# Se hai modifiche rimanenti, organizzale
git status

# Eventuale ultimo commit di cleanup
git add .
git commit -m "Final integration cleanup and testing

- Ensure all features work together
- Maintain hotfix corrections
- Complete team collaboration integration"

# Push finale
git push origin main
```

## 📊 Criteri di Valutazione

### ✅ Gestione Conflitti (40 punti)
- [ ] Staging preservata durante conflitti
- [ ] Integrazione intelligente delle modifiche
- [ ] Risoluzione corretta dei conflitti
- [ ] Backup/recovery appropriato

### ✅ Workflow Team (30 punti)
- [ ] Collaborazione efficace con modifiche parallele
- [ ] Staging organizzata durante team work
- [ ] Comunicazione attraverso commit messages
- [ ] Gestione di divergenze

### ✅ Gestione Emergenze (20 punti)
- [ ] Hotfix integrato senza perdita lavoro
- [ ] Priorità corretta (hotfix > feature development)
- [ ] Staging preservata durante emergenze

### ✅ Tecnica Avanzata (10 punti)
- [ ] Uso appropriato di stash per backup
- [ ] Staging selettivo in scenari complessi
- [ ] Recovery da situazioni critiche

## 🏆 Sfide Master Level

### Sfida 1: Branch Strategy
```bash
# Implementa workflow con feature branches
git checkout -b feature/advanced-search
# Sviluppa con staging organizzata
# Integra con main mantenendo staging
```

### Sfida 2: Automated Workflow
```bash
# Crea script per automazione
cat > staging-workflow.sh << 'EOF'
#!/bin/bash
# Automated staging workflow with conflict detection
git fetch origin
if git diff --quiet origin/main..HEAD; then
    echo "Safe to continue with staging"
else
    echo "Conflicts detected, backing up staging..."
    git stash push --staged -m "Auto-backup $(date)"
fi
EOF
```

### Sfida 3: Advanced Recovery
```bash
# Simula perdita accidentale di staging
git reset --hard HEAD~2
# Recupera usando reflog e stash
git reflog
git stash list
# Recovery completo
```

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Esercizio Precedente](./01-staging-selettivo.md)
- [➡️ Prossimo Modulo](../../06-Gestione-File-e-Directory/README.md)

---

**Completato!** Hai padroneggiato la staging area in scenari complessi di team collaboration.
