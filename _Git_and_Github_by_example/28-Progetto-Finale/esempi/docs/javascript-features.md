# JavaScript ES6+ Features

## 📋 Panoramica

Questo documento illustra le funzionalità moderne di JavaScript ES6+ utilizzate nel progetto Task Manager, con esempi pratici e best practices.

## 🚀 ES6+ Features Utilizzate

### 1. Arrow Functions

#### Sintassi Base
```javascript
// ES5 - Function declaration
function addTask(title, description) {
  return {
    id: generateId(),
    title: title,
    description: description,
    completed: false
  };
}

// ES6 - Arrow function
const addTask = (title, description) => ({
  id: generateId(),
  title,
  description,
  completed: false
});

// One-liner per funzioni semplici
const double = x => x * 2;
const greet = name => `Hello, ${name}!`;
```

#### Utilizzo nel Progetto
```javascript
// Task filtering
const completedTasks = tasks.filter(task => task.completed);
const taskTitles = tasks.map(task => task.title);

// Event handlers
button.addEventListener('click', () => {
  saveTask();
  updateUI();
});

// Promise handling
fetchTasks()
  .then(tasks => renderTasks(tasks))
  .catch(error => handleError(error));
```

#### ⚠️ Nota sui Context (this)
```javascript
// ❌ Problematico - arrow function perde context
class TaskManager {
  constructor() {
    this.tasks = [];
  }
  
  // ❌ Non fare così
  setupEventListener() {
    document.getElementById('save').addEventListener('click', () => {
      this.saveTasks(); // this funziona qui
    });
  }
}

// ✅ Corretto per metodi di classe
class TaskManager {
  constructor() {
    this.tasks = [];
  }
  
  saveTasks() {
    // Regular function mantiene context
  }
  
  setupEventListener() {
    document.getElementById('save').addEventListener('click', () => {
      this.saveTasks(); // this riferisce alla classe
    });
  }
}
```

### 2. Template Literals

#### Sintassi Base
```javascript
// ES5 - String concatenation
var message = 'Hello ' + user.name + ', you have ' + tasks.length + ' tasks';

// ES6 - Template literals
const message = `Hello ${user.name}, you have ${tasks.length} tasks`;
```

#### Utilizzo nel Progetto
```javascript
// HTML template generation
const taskHTML = (task) => `
  <div class="task ${task.completed ? 'completed' : ''}" data-id="${task.id}">
    <h3>${task.title}</h3>
    <p>${task.description}</p>
    <span class="date">Created: ${formatDate(task.createdAt)}</span>
    <button onclick="toggleTask('${task.id}')">
      ${task.completed ? 'Mark Incomplete' : 'Mark Complete'}
    </button>
  </div>
`;

// API endpoints
const API_ENDPOINTS = {
  tasks: (userId) => `/api/users/${userId}/tasks`,
  task: (userId, taskId) => `/api/users/${userId}/tasks/${taskId}`,
  search: (query) => `/api/search?q=${encodeURIComponent(query)}`
};

// Error messages
const showError = (operation, error) => {
  const errorMessage = `
    Failed to ${operation}. 
    Error: ${error.message}
    Please try again or contact support.
  `;
  displayErrorMessage(errorMessage);
};
```

#### Multi-line Strings
```javascript
// HTML email template
const emailTemplate = `
<!DOCTYPE html>
<html>
<head>
  <title>Task Reminder</title>
</head>
<body>
  <h1>Hi ${user.name}!</h1>
  <p>You have ${pendingTasks.length} pending tasks:</p>
  <ul>
    ${pendingTasks.map(task => `<li>${task.title}</li>`).join('')}
  </ul>
</body>
</html>
`;
```

### 3. Destructuring

#### Object Destructuring
```javascript
// Basic destructuring
const user = {
  id: 1,
  name: 'John Doe',
  email: 'john@example.com',
  preferences: {
    theme: 'dark',
    notifications: true
  }
};

// ES6 - Destructuring
const { id, name, email } = user;
const { theme, notifications } = user.preferences;

// Renaming variables
const { id: userId, name: userName } = user;

// Default values
const { avatar = '/default-avatar.png' } = user;

// Nested destructuring
const { 
  preferences: { 
    theme, 
    notifications = false 
  } 
} = user;
```

#### Array Destructuring
```javascript
// Array destructuring
const colors = ['red', 'green', 'blue', 'yellow'];
const [primary, secondary, ...others] = colors;
// primary = 'red', secondary = 'green', others = ['blue', 'yellow']

// Swapping variables
let a = 1, b = 2;
[a, b] = [b, a]; // a = 2, b = 1

// Function return values
const parseTaskDate = (dateString) => {
  const date = new Date(dateString);
  return [date.getFullYear(), date.getMonth() + 1, date.getDate()];
};

const [year, month, day] = parseTaskDate('2024-01-15');
```

#### Utilizzo nel Progetto
```javascript
// Function parameters
const createTask = ({ title, description, priority = 'medium', dueDate }) => {
  return {
    id: generateId(),
    title,
    description,
    priority,
    dueDate,
    completed: false,
    createdAt: new Date()
  };
};

// API response handling
const fetchTaskDetails = async (taskId) => {
  try {
    const response = await fetch(`/api/tasks/${taskId}`);
    const { data: task, status, message } = await response.json();
    
    if (status === 'success') {
      const { title, description, tags = [] } = task;
      return { title, description, tags };
    }
    
    throw new Error(message);
  } catch (error) {
    console.error('Failed to fetch task:', error);
  }
};

// Event handling
document.addEventListener('click', (event) => {
  const { target } = event;
  const { dataset: { action, taskId } } = target;
  
  if (action === 'delete') {
    deleteTask(taskId);
  }
});
```

### 4. Spread Operator (...)

#### Array Operations
```javascript
// Array concatenation
const completedTasks = [...activeTasks, ...archivedTasks];

// Array cloning
const tasksCopy = [...originalTasks];

// Adding elements
const newTasks = [...existingTasks, newTask];
const tasksWithHeader = [headerTask, ...regularTasks];

// Function arguments
const numbers = [1, 2, 3, 4, 5];
const max = Math.max(...numbers);
```

#### Object Operations
```javascript
// Object cloning
const taskCopy = { ...originalTask };

// Object merging
const updatedTask = {
  ...existingTask,
  completed: true,
  completedAt: new Date()
};

// Conditional properties
const taskWithOptionalDue = {
  ...baseTask,
  ...(dueDate && { dueDate })
};
```

#### Utilizzo nel Progetto
```javascript
// State updates (immutable)
const taskReducer = (state, action) => {
  switch (action.type) {
    case 'ADD_TASK':
      return {
        ...state,
        tasks: [...state.tasks, action.payload]
      };
    
    case 'UPDATE_TASK':
      return {
        ...state,
        tasks: state.tasks.map(task =>
          task.id === action.payload.id
            ? { ...task, ...action.payload.updates }
            : task
        )
      };
    
    case 'DELETE_TASK':
      return {
        ...state,
        tasks: state.tasks.filter(task => task.id !== action.payload.id)
      };
    
    default:
      return state;
  }
};

// API payload construction
const saveTask = async (taskData) => {
  const payload = {
    ...taskData,
    userId: getCurrentUserId(),
    timestamp: Date.now(),
    version: CURRENT_VERSION
  };
  
  return await fetch('/api/tasks', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      ...getAuthHeaders()
    },
    body: JSON.stringify(payload)
  });
};
```

### 5. Default Parameters

#### Basic Usage
```javascript
// ES5 - Manual default handling
function createTask(title, description, priority) {
  title = title || 'Untitled Task';
  description = description || '';
  priority = priority || 'medium';
  
  return { title, description, priority };
}

// ES6 - Default parameters
const createTask = (
  title = 'Untitled Task',
  description = '',
  priority = 'medium'
) => ({ title, description, priority });

// Complex defaults
const formatDate = (date = new Date(), format = 'YYYY-MM-DD') => {
  // formatting logic
};

// Function as default
const logAction = (action, timestamp = Date.now()) => {
  console.log(`[${timestamp}] ${action}`);
};
```

#### Utilizzo nel Progetto
```javascript
// API configuration
const apiRequest = (
  endpoint,
  method = 'GET',
  data = null,
  options = {}
) => {
  const config = {
    method,
    headers: {
      'Content-Type': 'application/json',
      ...getAuthHeaders()
    },
    ...options
  };
  
  if (data) {
    config.body = JSON.stringify(data);
  }
  
  return fetch(endpoint, config);
};

// Component initialization
const initializeTaskList = (
  container = document.getElementById('task-list'),
  sortBy = 'createdAt',
  sortOrder = 'desc'
) => {
  if (!container) {
    throw new Error('Task list container not found');
  }
  
  container.dataset.sortBy = sortBy;
  container.dataset.sortOrder = sortOrder;
  
  setupEventListeners(container);
  loadTasks();
};
```

### 6. Rest Parameters

#### Function Parameters
```javascript
// Collecting remaining arguments
const logMessage = (level, message, ...details) => {
  console.log(`[${level}] ${message}`);
  if (details.length > 0) {
    console.log('Details:', details);
  }
};

logMessage('ERROR', 'Failed to save task', 'Network timeout', 'Retry in 5s');

// Multiple operations
const updateTasks = (operation, ...taskIds) => {
  return taskIds.map(id => applyOperation(operation, id));
};

updateTasks('archive', '1', '2', '3');
```

#### Utilizzo nel Progetto
```javascript
// Batch operations
const deleteTasks = (...taskIds) => {
  const deletePromises = taskIds.map(id => 
    apiRequest(`/api/tasks/${id}`, 'DELETE')
  );
  
  return Promise.all(deletePromises);
};

// Event handling with multiple handlers
const attachEventHandlers = (element, eventType, ...handlers) => {
  handlers.forEach(handler => {
    element.addEventListener(eventType, handler);
  });
};

attachEventHandlers(
  saveButton,
  'click',
  validateForm,
  showLoader,
  saveTask,
  hideLoader
);
```

### 7. Enhanced Object Literals

#### Shorthand Properties
```javascript
// ES5
function createUser(name, email, age) {
  return {
    name: name,
    email: email,
    age: age
  };
}

// ES6 - Shorthand
const createUser = (name, email, age) => ({
  name,
  email,
  age
});
```

#### Method Definitions
```javascript
// ES5
const taskManager = {
  tasks: [],
  
  addTask: function(task) {
    this.tasks.push(task);
  },
  
  removeTask: function(id) {
    this.tasks = this.tasks.filter(task => task.id !== id);
  }
};

// ES6 - Method shorthand
const taskManager = {
  tasks: [],
  
  addTask(task) {
    this.tasks.push(task);
  },
  
  removeTask(id) {
    this.tasks = this.tasks.filter(task => task.id !== id);
  },
  
  // Computed property names
  [`get${capitalize('tasks')}`]() {
    return this.tasks;
  }
};
```

#### Utilizzo nel Progetto
```javascript
// State management
const createAppState = (user, tasks, filters) => ({
  user,
  tasks,
  filters,
  
  // Methods
  getCurrentUser() {
    return this.user;
  },
  
  getFilteredTasks() {
    return this.tasks.filter(task => 
      this.filters.every(filter => filter(task))
    );
  },
  
  // Computed properties
  get taskCount() {
    return this.tasks.length;
  },
  
  get completedCount() {
    return this.tasks.filter(task => task.completed).length;
  }
});
```

### 8. Classes

#### Class Definition
```javascript
class TaskManager {
  constructor(userId) {
    this.userId = userId;
    this.tasks = [];
    this.filters = [];
  }
  
  // Instance methods
  async loadTasks() {
    try {
      const response = await apiRequest(`/api/users/${this.userId}/tasks`);
      this.tasks = await response.json();
      this.render();
    } catch (error) {
      this.handleError('Failed to load tasks', error);
    }
  }
  
  addTask(taskData) {
    const task = {
      id: this.generateId(),
      ...taskData,
      userId: this.userId,
      createdAt: new Date()
    };
    
    this.tasks.push(task);
    this.saveTask(task);
    this.render();
    
    return task;
  }
  
  // Private method (ES2022)
  #generateId() {
    return `task-${Date.now()}-${Math.random().toString(36).substr(2, 9)}`;
  }
  
  // Static methods
  static validateTaskData(data) {
    const required = ['title'];
    const missing = required.filter(field => !data[field]);
    
    if (missing.length > 0) {
      throw new Error(`Missing required fields: ${missing.join(', ')}`);
    }
    
    return true;
  }
  
  // Getters and setters
  get completedTasks() {
    return this.tasks.filter(task => task.completed);
  }
  
  set sortOrder(order) {
    this._sortOrder = order;
    this.render();
  }
}
```

#### Inheritance
```javascript
class PriorityTaskManager extends TaskManager {
  constructor(userId) {
    super(userId);
    this.priorities = ['low', 'medium', 'high', 'urgent'];
  }
  
  addTask(taskData) {
    // Validate priority
    if (taskData.priority && !this.priorities.includes(taskData.priority)) {
      throw new Error('Invalid priority level');
    }
    
    // Set default priority
    const taskWithPriority = {
      priority: 'medium',
      ...taskData
    };
    
    return super.addTask(taskWithPriority);
  }
  
  getTasksByPriority(priority) {
    return this.tasks.filter(task => task.priority === priority);
  }
  
  sortByPriority() {
    const priorityOrder = { urgent: 4, high: 3, medium: 2, low: 1 };
    
    this.tasks.sort((a, b) => 
      priorityOrder[b.priority] - priorityOrder[a.priority]
    );
    
    this.render();
  }
}
```

### 9. Modules (Import/Export)

#### Export Patterns
```javascript
// utils/taskHelpers.js

// Named exports
export const formatDate = (date) => {
  return new Intl.DateTimeFormat('en-US').format(date);
};

export const generateId = () => {
  return `${Date.now()}-${Math.random().toString(36).substr(2, 9)}`;
};

export const validateEmail = (email) => {
  const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return regex.test(email);
};

// Default export
const TaskHelper = {
  formatDate,
  generateId,
  validateEmail,
  
  sortTasks(tasks, sortBy = 'createdAt', order = 'desc') {
    return [...tasks].sort((a, b) => {
      const valueA = a[sortBy];
      const valueB = b[sortBy];
      
      if (order === 'asc') {
        return valueA > valueB ? 1 : -1;
      }
      return valueA < valueB ? 1 : -1;
    });
  }
};

export default TaskHelper;
```

#### Import Patterns
```javascript
// main.js

// Default import
import TaskHelper from './utils/taskHelpers.js';

// Named imports
import { formatDate, generateId } from './utils/taskHelpers.js';

// Mixed imports
import TaskHelper, { validateEmail } from './utils/taskHelpers.js';

// Namespace import
import * as TaskUtils from './utils/taskHelpers.js';

// Dynamic imports (ES2020)
const loadTaskManager = async () => {
  const { TaskManager } = await import('./managers/TaskManager.js');
  return new TaskManager(getCurrentUserId());
};

// Conditional imports
const loadAdvancedFeatures = async () => {
  if (user.isPremium) {
    const { PriorityTaskManager } = await import('./managers/PriorityTaskManager.js');
    return PriorityTaskManager;
  }
  
  const { TaskManager } = await import('./managers/TaskManager.js');
  return TaskManager;
};
```

### 10. Async/Await

#### Basic Usage
```javascript
// Promise-based approach
const loadUserTasks = (userId) => {
  return fetch(`/api/users/${userId}/tasks`)
    .then(response => response.json())
    .then(tasks => {
      return fetch(`/api/users/${userId}/preferences`)
        .then(prefResponse => prefResponse.json())
        .then(preferences => ({ tasks, preferences }));
    })
    .catch(error => {
      console.error('Error loading data:', error);
      throw error;
    });
};

// Async/await approach
const loadUserTasks = async (userId) => {
  try {
    const [tasksResponse, preferencesResponse] = await Promise.all([
      fetch(`/api/users/${userId}/tasks`),
      fetch(`/api/users/${userId}/preferences`)
    ]);
    
    const tasks = await tasksResponse.json();
    const preferences = await preferencesResponse.json();
    
    return { tasks, preferences };
  } catch (error) {
    console.error('Error loading data:', error);
    throw error;
  }
};
```

#### Error Handling
```javascript
const saveTask = async (taskData) => {
  try {
    // Validate data
    TaskManager.validateTaskData(taskData);
    
    // Save to server
    const response = await fetch('/api/tasks', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(taskData)
    });
    
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    
    const savedTask = await response.json();
    
    // Update local state
    updateLocalTasks(savedTask);
    
    return savedTask;
  } catch (error) {
    if (error.name === 'ValidationError') {
      showUserError('Please check your input and try again.');
    } else if (error.name === 'NetworkError') {
      showUserError('Please check your connection and try again.');
    } else {
      showUserError('An unexpected error occurred.');
      console.error('Save task error:', error);
    }
    
    throw error;
  }
};
```

## 🎯 Best Practices

### 1. Code Organization
```javascript
// Group related functionality
const TaskAPI = {
  async getAll(userId) { /* ... */ },
  async getById(taskId) { /* ... */ },
  async create(taskData) { /* ... */ },
  async update(taskId, updates) { /* ... */ },
  async delete(taskId) { /* ... */ }
};

// Use consistent naming
const TaskConstants = {
  PRIORITIES: ['low', 'medium', 'high', 'urgent'],
  STATUSES: ['pending', 'in-progress', 'completed', 'archived'],
  DEFAULT_SORT: 'createdAt'
};
```

### 2. Error Handling
```javascript
// Specific error types
class ValidationError extends Error {
  constructor(field, value) {
    super(`Invalid ${field}: ${value}`);
    this.name = 'ValidationError';
    this.field = field;
    this.value = value;
  }
}

// Centralized error handling
const handleAsyncOperation = async (operation, errorContext) => {
  try {
    return await operation();
  } catch (error) {
    logger.error(`${errorContext}:`, error);
    notificationService.showError(`Failed to ${errorContext.toLowerCase()}`);
    throw error;
  }
};
```

### 3. Performance Considerations
```javascript
// Debounce user input
const debouncedSearch = debounce(async (query) => {
  const results = await searchTasks(query);
  displaySearchResults(results);
}, 300);

// Lazy loading
const loadTaskDetails = async (taskId) => {
  // Only import heavy modules when needed
  const { TaskAnalytics } = await import('./analytics/TaskAnalytics.js');
  return TaskAnalytics.getDetailedStats(taskId);
};

// Memory management
const taskCache = new Map();
const MAX_CACHE_SIZE = 100;

const getCachedTask = (taskId) => {
  if (taskCache.size > MAX_CACHE_SIZE) {
    // Remove oldest entries
    const firstKey = taskCache.keys().next().value;
    taskCache.delete(firstKey);
  }
  
  return taskCache.get(taskId);
};
```

---

*Queste funzionalità ES6+ migliorano significativamente la leggibilità, manutenibilità e performance del codice JavaScript moderno.*
