# Esercizio 1: Mini Progetto di Team

## Obiettivo
Simulare un progetto di team completo utilizzando Git e GitHub per sviluppare una semplice applicazione "Todo List Collaborativa" con 3-4 partecipanti.

## Prerequisiti
- Conoscenza base di Git/GitHub
- Esperienza con HTML, CSS, JavaScript
- Account GitHub per tutti i partecipanti

## Setup del Team
Formate un team di 3-4 persone con i seguenti ruoli:

**Team Leader** (Ruolo A):
- Crea e configura il repository
- Gestisce branch protection e merge
- Coordina milestone e release

**Frontend Developer** (Ruolo B):
- Sviluppa interfaccia utente
- Gestisce styling e UX
- Implementa interazioni DOM

**Backend Developer** (Ruolo C):
- Crea API e logica server
- Gestisce storage (localStorage/API)
- Implementa autenticazione base

**QA/DevOps** (Ruolo D - opzionale):
- Setup testing e CI/CD
- Gestisce documentazione
- Coordina testing e deployment

## Fase 1: Setup Repository (Team Leader)

### 1.1 Creazione Repository
```bash
# Repository: todo-team-project
# Descrizione: Collaborative Todo List Application
# Pubblico con README, .gitignore (Node), licenza MIT
```

### 1.2 Struttura Iniziale del Progetto
Crea la struttura base:

```
todo-team-project/
├── README.md
├── .gitignore
├── package.json
├── src/
│   ├── index.html
│   ├── css/
│   │   └── style.css
│   ├── js/
│   │   ├── app.js
│   │   ├── api.js
│   │   └── auth.js
│   └── tests/
│       └── test.js
├── docs/
│   └── API.md
└── .github/
    ├── ISSUE_TEMPLATE/
    └── workflows/
```

**package.json** iniziale:
```json
{
  "name": "todo-team-project",
  "version": "1.0.0",
  "description": "Collaborative Todo List Application",
  "main": "src/index.html",
  "scripts": {
    "start": "npx live-server src/",
    "test": "npx jest",
    "lint": "npx eslint src/"
  },
  "repository": {
    "type": "git",
    "url": "git+https://github.com/[username]/todo-team-project.git"
  },
  "keywords": ["todo", "collaboration", "javascript"],
  "author": "Team Name",
  "license": "MIT",
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "live-server": "^1.2.2"
  }
}
```

### 1.3 Configurazione Repository
```bash
# Branch protection su main
# Require PR reviews: 1
# Require status checks
# Require branches to be up to date
# Restrict pushes to main
```

### 1.4 Issue Template
Crea `.github/ISSUE_TEMPLATE/task.yml`:
```yaml
name: 📋 Task
description: Task di sviluppo
title: "[TASK] "
labels: ["task"]
body:
  - type: textarea
    id: description
    attributes:
      label: Descrizione Task
      description: Cosa deve essere implementato
    validations:
      required: true
  
  - type: textarea
    id: acceptance
    attributes:
      label: Criteri di Accettazione
      placeholder: |
        - [ ] Criterio 1
        - [ ] Criterio 2
    validations:
      required: true
  
  - type: dropdown
    id: component
    attributes:
      label: Componente
      options:
        - Frontend
        - Backend
        - Testing
        - Documentation
    validations:
      required: true
```

## Fase 2: Planning Sprint (Tutto il Team)

### 2.1 Creazione Milestone
**Milestone: "MVP Todo App"**
- Deadline: 2 settimane da oggi
- Descrizione: Versione base funzionante dell'app

### 2.2 Creazione Issue per Features

**Issue #1: Setup HTML Structure** (Frontend)
```markdown
**Descrizione:** Creare struttura HTML base per l'applicazione

**Criteri di Accettazione:**
- [ ] Header con titolo app
- [ ] Form per aggiungere todo
- [ ] Lista per visualizzare todo
- [ ] Footer con info team
- [ ] Responsive design base
- [ ] Semantic HTML5

**Componente:** Frontend
**Assignee:** [Frontend Developer]
**Labels:** frontend, html, task
**Milestone:** MVP Todo App
```

**Issue #2: CSS Styling and Layout** (Frontend)
```markdown
**Descrizione:** Implementare styling CSS moderno e responsive

**Criteri di Accettazione:**
- [ ] Color scheme professionale
- [ ] Layout responsive (mobile-first)
- [ ] Animations per interazioni
- [ ] Hover effects sui bottoni
- [ ] Form styling
- [ ] List styling con status indicators

**Componente:** Frontend
**Assignee:** [Frontend Developer]
**Labels:** frontend, css, design, task
**Milestone:** MVP Todo App
```

**Issue #3: Todo CRUD Operations** (Backend)
```markdown
**Descrizione:** Implementare operazioni Create, Read, Update, Delete per todo

**Criteri di Accettazione:**
- [ ] Aggiungere nuovo todo
- [ ] Marcare todo come completato
- [ ] Eliminare todo
- [ ] Modificare testo todo
- [ ] Persistenza in localStorage
- [ ] Validation input

**Componente:** Backend
**Assignee:** [Backend Developer]  
**Labels:** backend, javascript, crud, task
**Milestone:** MVP Todo App
```

**Issue #4: User Authentication** (Backend)
```markdown
**Descrizione:** Sistema di autenticazione base con username

**Criteri di Accettazione:**
- [ ] Login/logout functionality
- [ ] User session management
- [ ] Todo separati per utente
- [ ] Welcome message personalizzato
- [ ] Logout button

**Componente:** Backend
**Assignee:** [Backend Developer]
**Labels:** backend, authentication, task
**Milestone:** MVP Todo App
```

**Issue #5: Testing Setup** (QA)
```markdown
**Descrizione:** Configurare testing framework e scrivere test base

**Criteri di Accettazione:**
- [ ] Jest configuration
- [ ] Test per CRUD operations
- [ ] Test per authentication
- [ ] Test per DOM manipulation
- [ ] CI workflow per testing

**Componente:** Testing
**Assignee:** [QA/DevOps]
**Labels:** testing, ci-cd, task
**Milestone:** MVP Todo App
```

## Fase 3: Sviluppo Collaborativo

### 3.1 Workflow di Sviluppo
Ogni developer segue questo processo:

```bash
# 1. Assign issue a se stessi
# 2. Creare branch da main
git checkout main
git pull origin main
git checkout -b feature/issue-[numero]-[nome-breve]

# 3. Sviluppare feature
# 4. Commit regolari con messaggi descrittivi
git add .
git commit -m "feat: implement basic HTML structure for todo app

- Add semantic header with app title
- Create form for adding new todos  
- Add empty list container for todos
- Include responsive footer with team info

Closes #1"

# 5. Push e creare PR
git push origin feature/issue-1-html-structure
```

### 3.2 Pull Request Template
Crea `.github/pull_request_template.md`:
```markdown
## Descrizione
Breve descrizione delle modifiche

## Issue Collegate
Closes #[numero]

## Tipo di Cambiamento
- [ ] Bug fix
- [ ] Nuova feature
- [ ] Breaking change
- [ ] Documentazione

## Testing
- [ ] I miei cambiamenti hanno test
- [ ] Tutti i test passano
- [ ] Ho testato manualmente le modifiche

## Checklist
- [ ] Il mio codice segue le convenzioni del progetto
- [ ] Ho fatto self-review del mio codice
- [ ] Ho commentato parti complesse
- [ ] Ho aggiornato la documentazione se necessario
```

### 3.3 Esempio di Implementazione Frontend

**src/index.html** (Issue #1):
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Todo Team - Collaborative Task Manager</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <header>
        <h1>📝 Todo Team</h1>
        <div id="user-info" class="hidden">
            <span id="welcome-message"></span>
            <button id="logout-btn">Logout</button>
        </div>
    </header>

    <main>
        <!-- Login Section -->
        <section id="login-section">
            <form id="login-form">
                <input type="text" id="username-input" placeholder="Inserisci il tuo nome" required>
                <button type="submit">Accedi</button>
            </form>
        </section>

        <!-- Todo Section -->
        <section id="todo-section" class="hidden">
            <form id="todo-form">
                <input type="text" id="todo-input" placeholder="Aggiungi un nuovo todo..." required>
                <button type="submit">Aggiungi</button>
            </form>

            <div id="todo-stats">
                <span id="total-todos">0</span> totali | 
                <span id="completed-todos">0</span> completati
            </div>

            <ul id="todo-list"></ul>
        </section>
    </main>

    <footer>
        <p>Sviluppato dal Team: [Nomi team members] | 
           <a href="https://github.com/[username]/todo-team-project">GitHub</a>
        </p>
    </footer>

    <script src="js/auth.js"></script>
    <script src="js/api.js"></script>
    <script src="js/app.js"></script>
</body>
</html>
```

### 3.4 Esempio di Implementazione Backend

**src/js/api.js** (Issue #3):
```javascript
// Todo API - gestisce CRUD operations
class TodoAPI {
    constructor() {
        this.currentUser = null;
        this.todos = this.loadTodos();
    }

    // Load todos from localStorage
    loadTodos() {
        const saved = localStorage.getItem('todos');
        return saved ? JSON.parse(saved) : {};
    }

    // Save todos to localStorage
    saveTodos() {
        localStorage.setItem('todos', JSON.stringify(this.todos));
    }

    // Set current user
    setUser(username) {
        this.currentUser = username;
        if (!this.todos[username]) {
            this.todos[username] = [];
        }
    }

    // Get current user's todos
    getUserTodos() {
        return this.currentUser ? this.todos[this.currentUser] || [] : [];
    }

    // Add new todo
    addTodo(text) {
        if (!this.currentUser || !text.trim()) return null;
        
        const todo = {
            id: Date.now().toString(),
            text: text.trim(),
            completed: false,
            createdAt: new Date().toISOString()
        };

        this.todos[this.currentUser].push(todo);
        this.saveTodos();
        return todo;
    }

    // Toggle todo completion
    toggleTodo(id) {
        const userTodos = this.getUserTodos();
        const todo = userTodos.find(t => t.id === id);
        if (todo) {
            todo.completed = !todo.completed;
            this.saveTodos();
            return todo;
        }
        return null;
    }

    // Delete todo
    deleteTodo(id) {
        if (!this.currentUser) return false;
        
        const userTodos = this.todos[this.currentUser];
        const index = userTodos.findIndex(t => t.id === id);
        if (index > -1) {
            userTodos.splice(index, 1);
            this.saveTodos();
            return true;
        }
        return false;
    }

    // Update todo text
    updateTodo(id, newText) {
        const userTodos = this.getUserTodos();
        const todo = userTodos.find(t => t.id === id);
        if (todo && newText.trim()) {
            todo.text = newText.trim();
            this.saveTodos();
            return todo;
        }
        return null;
    }

    // Get stats
    getStats() {
        const userTodos = this.getUserTodos();
        return {
            total: userTodos.length,
            completed: userTodos.filter(t => t.completed).length,
            pending: userTodos.filter(t => !t.completed).length
        };
    }
}

// Export for use in other modules
window.TodoAPI = TodoAPI;
```

## Fase 4: Code Review e Testing

### 4.1 Review Process
Per ogni PR:
1. **Assegnare reviewer** (almeno 1 altro team member)
2. **Review checklist:**
   - [ ] Codice è leggibile e ben commentato
   - [ ] Segue conventions del progetto
   - [ ] Non ci sono hardcoded values
   - [ ] Gestisce edge cases
   - [ ] Non introduce breaking changes

3. **Richieste di modifica** con commenti costruttivi
4. **Approval** e merge solo dopo review positiva

### 4.2 Testing Manuale
Ogni team member testa:
- La propria feature
- L'integrazione con altre feature
- Edge cases e error handling

## Fase 5: Integrazione e Deployment

### 5.1 Merge Strategy
```bash
# Merge con squash per clean history
# Delete branch dopo merge
# Update milestone progress
```

### 5.2 Release Process
Quando tutte le issue del milestone sono complete:
1. Creare release v1.0.0
2. Tag il commit
3. Deploy su GitHub Pages
4. Aggiornare documentazione

## Deliverables

### Cosa Consegnare:
1. **Repository GitHub** con:
   - Codice sorgente completo
   - Almeno 10 commit significativi
   - 5+ issue create e risolte
   - 3+ PR con review
   - 1 milestone completato
   - README completo con setup instructions

2. **Applicazione Funzionante** con:
   - Login utente base
   - CRUD operations per todo
   - UI responsive
   - Persistenza dati
   - Almeno 2 utenti di test

3. **Documentazione** inclusa:
   - Setup e installazione
   - Guida utente base
   - API documentation
   - Team member contributions

### Criteri di Valutazione:
- **Collaborazione Git** (30%): Uso corretto di branch, PR, merge
- **Qualità Codice** (25%): Clean code, conventions, comments
- **Funzionalità App** (25%): Features complete e funzionanti
- **Project Management** (20%): Issue tracking, milestone, organization

### Tempo Stimato:
- Setup: 1-2 ore
- Sviluppo: 8-12 ore totali team
- Testing e integration: 2-3 ore
- Documentazione: 1-2 ore

## Bonus Challenges
Per team che finiscono in anticipo:
- [ ] Implementare filtri todo (all/active/completed)
- [ ] Aggiungere categorie/tag ai todo
- [ ] Dark/light theme toggle
- [ ] Export todo in formato JSON/CSV
- [ ] Search functionality
- [ ] Due dates per todo
- [ ] Drag & drop reordering

Questo esercizio simula realmente l'esperienza di sviluppo in team e insegna pratiche collaborative essenziali per progetti software professionali.
