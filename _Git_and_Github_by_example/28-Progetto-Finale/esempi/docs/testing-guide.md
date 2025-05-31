# Testing Guide

## 📋 Panoramica

Una strategia di testing completa è fondamentale per garantire la qualità e affidabilità del codice. Questa guida copre approcci, strumenti e best practices per il testing nel progetto Task Manager.

## 🧪 Tipi di Test

### 1. Unit Testing

#### Definizione
Test che verificano il comportamento di singole unità di codice (funzioni, metodi, classi) in isolamento.

#### Setup Base
```javascript
// package.json
{
  "devDependencies": {
    "jest": "^29.0.0",
    "@testing-library/jest-dom": "^5.16.0",
    "@testing-library/dom": "^8.19.0"
  },
  "scripts": {
    "test": "jest",
    "test:watch": "jest --watch",
    "test:coverage": "jest --coverage"
  }
}

// jest.config.js
module.exports = {
  testEnvironment: 'jsdom',
  setupFilesAfterEnv: ['<rootDir>/src/setupTests.js'],
  collectCoverageFrom: [
    'src/**/*.{js,jsx}',
    '!src/index.js',
    '!src/serviceWorker.js'
  ],
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
      statements: 80
    }
  }
};
```

#### Esempi Unit Test
```javascript
// src/utils/taskUtils.test.js
import { 
  generateTaskId, 
  validateTaskData, 
  formatTaskDueDate,
  calculateTaskPriority 
} from './taskUtils';

describe('Task Utilities', () => {
  describe('generateTaskId', () => {
    it('should generate unique IDs', () => {
      const id1 = generateTaskId();
      const id2 = generateTaskId();
      
      expect(id1).toBeDefined();
      expect(id2).toBeDefined();
      expect(id1).not.toBe(id2);
    });

    it('should generate IDs with correct format', () => {
      const id = generateTaskId();
      
      expect(id).toMatch(/^task-\d+-[a-z0-9]+$/);
    });
  });

  describe('validateTaskData', () => {
    it('should accept valid task data', () => {
      const validTask = {
        title: 'Test Task',
        description: 'Test Description',
        priority: 'medium'
      };
      
      expect(() => validateTaskData(validTask)).not.toThrow();
    });

    it('should throw error for missing title', () => {
      const invalidTask = {
        description: 'Test Description'
      };
      
      expect(() => validateTaskData(invalidTask))
        .toThrow('Title is required');
    });

    it('should throw error for invalid priority', () => {
      const invalidTask = {
        title: 'Test Task',
        priority: 'invalid'
      };
      
      expect(() => validateTaskData(invalidTask))
        .toThrow('Invalid priority level');
    });
  });

  describe('formatTaskDueDate', () => {
    it('should format date correctly', () => {
      const date = new Date('2024-01-15T10:30:00Z');
      const formatted = formatTaskDueDate(date);
      
      expect(formatted).toBe('Jan 15, 2024');
    });

    it('should handle invalid dates', () => {
      expect(() => formatTaskDueDate('invalid'))
        .toThrow('Invalid date');
    });
  });
});
```

#### Testing Classes
```javascript
// src/managers/TaskManager.test.js
import TaskManager from './TaskManager';

// Mock dependencies
jest.mock('../api/taskAPI', () => ({
  fetchTasks: jest.fn(),
  saveTask: jest.fn(),
  deleteTask: jest.fn()
}));

describe('TaskManager', () => {
  let taskManager;
  const mockUserId = 'user-123';

  beforeEach(() => {
    taskManager = new TaskManager(mockUserId);
    jest.clearAllMocks();
  });

  describe('constructor', () => {
    it('should initialize with correct user ID', () => {
      expect(taskManager.userId).toBe(mockUserId);
      expect(taskManager.tasks).toEqual([]);
    });
  });

  describe('addTask', () => {
    it('should add task with generated ID', () => {
      const taskData = {
        title: 'New Task',
        description: 'Task description'
      };

      const addedTask = taskManager.addTask(taskData);

      expect(addedTask.id).toBeDefined();
      expect(addedTask.title).toBe(taskData.title);
      expect(addedTask.userId).toBe(mockUserId);
      expect(taskManager.tasks).toContain(addedTask);
    });

    it('should set default values', () => {
      const taskData = { title: 'New Task' };
      const addedTask = taskManager.addTask(taskData);

      expect(addedTask.completed).toBe(false);
      expect(addedTask.priority).toBe('medium');
      expect(addedTask.createdAt).toBeInstanceOf(Date);
    });
  });

  describe('getFilteredTasks', () => {
    beforeEach(() => {
      taskManager.tasks = [
        { id: '1', title: 'Task 1', completed: false, priority: 'high' },
        { id: '2', title: 'Task 2', completed: true, priority: 'low' },
        { id: '3', title: 'Task 3', completed: false, priority: 'medium' }
      ];
    });

    it('should filter by completion status', () => {
      const completed = taskManager.getFilteredTasks({ completed: true });
      const pending = taskManager.getFilteredTasks({ completed: false });

      expect(completed).toHaveLength(1);
      expect(pending).toHaveLength(2);
    });

    it('should filter by priority', () => {
      const highPriority = taskManager.getFilteredTasks({ priority: 'high' });
      
      expect(highPriority).toHaveLength(1);
      expect(highPriority[0].id).toBe('1');
    });
  });
});
```

### 2. Integration Testing

#### Testing API Integration
```javascript
// src/api/taskAPI.test.js
import { setupServer } from 'msw/node';
import { rest } from 'msw';
import TaskAPI from './taskAPI';

// Mock server setup
const server = setupServer(
  rest.get('/api/tasks', (req, res, ctx) => {
    return res(
      ctx.json([
        { id: '1', title: 'Task 1', completed: false },
        { id: '2', title: 'Task 2', completed: true }
      ])
    );
  }),

  rest.post('/api/tasks', (req, res, ctx) => {
    const { title, description } = req.body;
    return res(
      ctx.json({
        id: 'new-task-id',
        title,
        description,
        completed: false,
        createdAt: new Date().toISOString()
      })
    );
  }),

  rest.put('/api/tasks/:id', (req, res, ctx) => {
    const { id } = req.params;
    const updates = req.body;
    
    return res(
      ctx.json({
        id,
        ...updates,
        updatedAt: new Date().toISOString()
      })
    );
  })
);

describe('TaskAPI Integration', () => {
  beforeAll(() => server.listen());
  afterEach(() => server.resetHandlers());
  afterAll(() => server.close());

  describe('fetchTasks', () => {
    it('should fetch tasks from API', async () => {
      const tasks = await TaskAPI.fetchTasks('user-123');
      
      expect(tasks).toHaveLength(2);
      expect(tasks[0]).toEqual({
        id: '1',
        title: 'Task 1',
        completed: false
      });
    });

    it('should handle API errors', async () => {
      server.use(
        rest.get('/api/tasks', (req, res, ctx) => {
          return res(ctx.status(500), ctx.json({ error: 'Server error' }));
        })
      );

      await expect(TaskAPI.fetchTasks('user-123'))
        .rejects.toThrow('Failed to fetch tasks');
    });
  });

  describe('saveTask', () => {
    it('should save task to API', async () => {
      const taskData = {
        title: 'New Task',
        description: 'Task description'
      };

      const savedTask = await TaskAPI.saveTask(taskData);

      expect(savedTask.id).toBe('new-task-id');
      expect(savedTask.title).toBe(taskData.title);
      expect(savedTask.createdAt).toBeDefined();
    });
  });
});
```

#### Testing Component Integration
```javascript
// src/components/TaskList.test.js
import { screen, render, fireEvent, waitFor } from '@testing-library/dom';
import TaskList from './TaskList';
import TaskAPI from '../api/taskAPI';

// Mock the API
jest.mock('../api/taskAPI');

describe('TaskList Component Integration', () => {
  const mockTasks = [
    {
      id: '1',
      title: 'Task 1',
      description: 'Description 1',
      completed: false,
      priority: 'high'
    },
    {
      id: '2',
      title: 'Task 2',
      description: 'Description 2',
      completed: true,
      priority: 'medium'
    }
  ];

  beforeEach(() => {
    TaskAPI.fetchTasks.mockResolvedValue(mockTasks);
    TaskAPI.updateTask.mockResolvedValue({});
    TaskAPI.deleteTask.mockResolvedValue({});
  });

  afterEach(() => {
    jest.clearAllMocks();
  });

  it('should render tasks after loading', async () => {
    const container = document.createElement('div');
    document.body.appendChild(container);

    const taskList = new TaskList(container, 'user-123');
    await taskList.initialize();

    await waitFor(() => {
      expect(screen.getByText('Task 1')).toBeInTheDocument();
      expect(screen.getByText('Task 2')).toBeInTheDocument();
    });

    expect(TaskAPI.fetchTasks).toHaveBeenCalledWith('user-123');
  });

  it('should handle task completion toggle', async () => {
    const container = document.createElement('div');
    document.body.appendChild(container);

    const taskList = new TaskList(container, 'user-123');
    await taskList.initialize();

    const checkbox = screen.getByLabelText('Mark Task 1 as complete');
    fireEvent.click(checkbox);

    await waitFor(() => {
      expect(TaskAPI.updateTask).toHaveBeenCalledWith('1', {
        completed: true
      });
    });
  });

  it('should handle task deletion', async () => {
    const container = document.createElement('div');
    document.body.appendChild(container);

    const taskList = new TaskList(container, 'user-123');
    await taskList.initialize();

    const deleteButton = screen.getByLabelText('Delete Task 1');
    fireEvent.click(deleteButton);

    // Confirm deletion in modal
    const confirmButton = screen.getByText('Confirm Delete');
    fireEvent.click(confirmButton);

    await waitFor(() => {
      expect(TaskAPI.deleteTask).toHaveBeenCalledWith('1');
      expect(screen.queryByText('Task 1')).not.toBeInTheDocument();
    });
  });
});
```

### 3. End-to-End (E2E) Testing

#### Playwright Setup
```javascript
// playwright.config.js
module.exports = {
  testDir: './e2e',
  timeout: 30000,
  fullyParallel: true,
  forbidOnly: !!process.env.CI,
  retries: process.env.CI ? 2 : 0,
  workers: process.env.CI ? 1 : undefined,
  reporter: 'html',
  use: {
    baseURL: 'http://localhost:3000',
    trace: 'on-first-retry',
    screenshot: 'only-on-failure',
    video: 'retain-on-failure'
  },
  projects: [
    {
      name: 'chromium',
      use: { ...devices['Desktop Chrome'] }
    },
    {
      name: 'firefox',
      use: { ...devices['Desktop Firefox'] }
    },
    {
      name: 'webkit',
      use: { ...devices['Desktop Safari'] }
    }
  ],
  webServer: {
    command: 'npm run start',
    port: 3000
  }
};
```

#### E2E Test Examples
```javascript
// e2e/task-management.spec.js
import { test, expect } from '@playwright/test';

test.describe('Task Management', () => {
  test.beforeEach(async ({ page }) => {
    // Login user before each test
    await page.goto('/login');
    await page.fill('[data-testid=email]', 'test@example.com');
    await page.fill('[data-testid=password]', 'password123');
    await page.click('[data-testid=login-button]');
    
    // Wait for dashboard to load
    await expect(page.locator('[data-testid=dashboard]')).toBeVisible();
  });

  test('should create a new task', async ({ page }) => {
    // Navigate to task creation
    await page.click('[data-testid=new-task-button]');
    
    // Fill task form
    await page.fill('[data-testid=task-title]', 'E2E Test Task');
    await page.fill('[data-testid=task-description]', 'This is a test task');
    await page.selectOption('[data-testid=task-priority]', 'high');
    
    // Save task
    await page.click('[data-testid=save-task-button]');
    
    // Verify task appears in list
    await expect(page.locator('[data-testid=task-list]')).toContainText('E2E Test Task');
    
    // Verify task priority indicator
    await expect(
      page.locator('[data-testid=task-item]').filter({ hasText: 'E2E Test Task' })
          .locator('[data-testid=priority-indicator]')
    ).toHaveClass(/priority-high/);
  });

  test('should edit existing task', async ({ page }) => {
    // Create a task first
    await page.click('[data-testid=new-task-button]');
    await page.fill('[data-testid=task-title]', 'Original Task');
    await page.click('[data-testid=save-task-button]');
    
    // Edit the task
    await page.click('[data-testid=task-item] [data-testid=edit-button]');
    await page.fill('[data-testid=task-title]', 'Updated Task');
    await page.click('[data-testid=save-task-button]');
    
    // Verify changes
    await expect(page.locator('[data-testid=task-list]')).toContainText('Updated Task');
    await expect(page.locator('[data-testid=task-list]')).not.toContainText('Original Task');
  });

  test('should filter tasks by status', async ({ page }) => {
    // Create completed and pending tasks
    const tasks = [
      { title: 'Completed Task', completed: true },
      { title: 'Pending Task', completed: false }
    ];

    for (const task of tasks) {
      await page.click('[data-testid=new-task-button]');
      await page.fill('[data-testid=task-title]', task.title);
      await page.click('[data-testid=save-task-button]');
      
      if (task.completed) {
        await page.click(`[data-testid=task-item]:has-text("${task.title}") [data-testid=complete-checkbox]`);
      }
    }
    
    // Filter by completed
    await page.click('[data-testid=filter-completed]');
    await expect(page.locator('[data-testid=task-list]')).toContainText('Completed Task');
    await expect(page.locator('[data-testid=task-list]')).not.toContainText('Pending Task');
    
    // Filter by pending
    await page.click('[data-testid=filter-pending]');
    await expect(page.locator('[data-testid=task-list]')).toContainText('Pending Task');
    await expect(page.locator('[data-testid=task-list]')).not.toContainText('Completed Task');
  });

  test('should handle offline scenario', async ({ page, context }) => {
    // Go offline
    await context.setOffline(true);
    
    // Try to create a task
    await page.click('[data-testid=new-task-button]');
    await page.fill('[data-testid=task-title]', 'Offline Task');
    await page.click('[data-testid=save-task-button]');
    
    // Verify offline message
    await expect(page.locator('[data-testid=offline-message]')).toBeVisible();
    await expect(page.locator('[data-testid=offline-message]')).toContainText('You are offline');
    
    // Go back online
    await context.setOffline(false);
    
    // Verify task is synced
    await expect(page.locator('[data-testid=task-list]')).toContainText('Offline Task');
  });
});
```

## 🎯 Testing Best Practices

### 1. Test Structure (AAA Pattern)

```javascript
describe('Feature/Component', () => {
  it('should behave correctly under specific conditions', () => {
    // Arrange - Setup test data and environment
    const input = 'test input';
    const expected = 'expected output';
    
    // Act - Execute the code under test
    const result = functionUnderTest(input);
    
    // Assert - Verify the results
    expect(result).toBe(expected);
  });
});
```

### 2. Test Naming Conventions

```javascript
// ✅ Good - Descriptive test names
describe('TaskValidator', () => {
  describe('validateTitle', () => {
    it('should accept valid title with alphanumeric characters', () => {});
    it('should reject empty title', () => {});
    it('should reject title longer than 100 characters', () => {});
    it('should reject title with only whitespace', () => {});
  });
});

// ❌ Poor - Vague test names
describe('TaskValidator', () => {
  it('test title validation', () => {});
  it('test edge cases', () => {});
});
```

### 3. Mock Management

```javascript
// Mock external dependencies
jest.mock('../api/taskAPI', () => ({
  fetchTasks: jest.fn(),
  saveTask: jest.fn(),
  deleteTask: jest.fn()
}));

// Partial mocking
jest.mock('../utils/dateUtils', () => ({
  ...jest.requireActual('../utils/dateUtils'),
  getCurrentTimestamp: jest.fn(() => 1640995200000) // Fixed timestamp
}));

// Mock cleanup
afterEach(() => {
  jest.clearAllMocks();
});

beforeEach(() => {
  // Reset mock implementations
  TaskAPI.fetchTasks.mockResolvedValue([]);
});
```

### 4. Test Data Management

```javascript
// Test data factories
const createTaskData = (overrides = {}) => ({
  id: 'task-123',
  title: 'Default Task',
  description: 'Default description',
  completed: false,
  priority: 'medium',
  createdAt: new Date('2024-01-01'),
  ...overrides
});

// Use in tests
describe('TaskProcessor', () => {
  it('should process high priority tasks first', () => {
    const tasks = [
      createTaskData({ priority: 'low', title: 'Low Priority' }),
      createTaskData({ priority: 'high', title: 'High Priority' }),
      createTaskData({ priority: 'medium', title: 'Medium Priority' })
    ];
    
    const processed = processTasksByPriority(tasks);
    
    expect(processed[0].title).toBe('High Priority');
  });
});
```

### 5. Async Testing

```javascript
// Testing async functions
describe('TaskAPI', () => {
  it('should handle API timeout', async () => {
    // Mock API timeout
    TaskAPI.fetchTasks.mockRejectedValue(new Error('Request timeout'));
    
    const taskManager = new TaskManager('user-123');
    
    // Use rejects matcher for async errors
    await expect(taskManager.loadTasks()).rejects.toThrow('Request timeout');
  });

  it('should retry failed requests', async () => {
    // Mock API to fail twice then succeed
    TaskAPI.fetchTasks
      .mockRejectedValueOnce(new Error('Network error'))
      .mockRejectedValueOnce(new Error('Network error'))
      .mockResolvedValue([{ id: '1', title: 'Task 1' }]);
    
    const taskManager = new TaskManager('user-123');
    
    const tasks = await taskManager.loadTasksWithRetry();
    
    expect(tasks).toHaveLength(1);
    expect(TaskAPI.fetchTasks).toHaveBeenCalledTimes(3);
  });
});
```

## 📊 Test Coverage

### Coverage Configuration
```javascript
// jest.config.js
module.exports = {
  collectCoverageFrom: [
    'src/**/*.{js,jsx}',
    '!src/index.js',
    '!src/serviceWorker.js',
    '!src/**/*.config.js',
    '!src/**/*.stories.js'
  ],
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
      statements: 80
    },
    './src/components/': {
      branches: 85,
      statements: 85
    },
    './src/utils/': {
      functions: 95,
      lines: 95
    }
  },
  coverageReporters: ['text', 'lcov', 'html']
};
```

### Coverage Analysis
```bash
# Generate coverage report
npm run test:coverage

# Coverage output example
 PASS  src/utils/taskUtils.test.js
 PASS  src/managers/TaskManager.test.js
 PASS  src/components/TaskList.test.js

----------------------|---------|----------|---------|---------|
File                  | % Stmts | % Branch | % Funcs | % Lines |
----------------------|---------|----------|---------|---------|
All files             |   85.32 |    78.95 |   87.50 |   85.19 |
 src/                 |   90.00 |    85.71 |   88.89 |   89.66 |
  TaskManager.js      |   95.83 |    88.89 |   100.00|   95.45 |
  taskUtils.js        |   87.50 |    83.33 |   85.71 |   86.96 |
 src/components/      |   82.14 |    71.43 |   85.71 |   81.82 |
  TaskList.js         |   85.00 |    75.00 |   87.50 |   84.21 |
  TaskForm.js         |   78.26 |    66.67 |   83.33 |   78.95 |
----------------------|---------|----------|---------|---------|
```

## 🔧 Continuous Integration

### GitHub Actions Setup
```yaml
# .github/workflows/test.yml
name: Test Suite

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    strategy:
      matrix:
        node-version: [16.x, 18.x, 20.x]
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Use Node.js ${{ matrix.node-version }}
      uses: actions/setup-node@v3
      with:
        node-version: ${{ matrix.node-version }}
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run linting
      run: npm run lint
    
    - name: Run unit tests
      run: npm run test:coverage
    
    - name: Run E2E tests
      run: npm run test:e2e
      
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage/lcov.info
        
    - name: Upload test results
      uses: actions/upload-artifact@v3
      if: failure()
      with:
        name: test-results
        path: |
          test-results/
          coverage/
```

## 🎯 Testing Checklist

### Before Writing Tests
- [ ] Understand the requirements clearly
- [ ] Identify edge cases and error scenarios
- [ ] Plan test data and setup requirements
- [ ] Consider dependencies and mocking needs

### Writing Tests
- [ ] Use descriptive test names
- [ ] Follow AAA pattern (Arrange, Act, Assert)
- [ ] Test one thing at a time
- [ ] Include positive and negative test cases
- [ ] Mock external dependencies

### Test Quality
- [ ] Tests are independent and can run in any order
- [ ] Tests are deterministic (no randomness)
- [ ] Tests are fast and focused
- [ ] Tests provide clear failure messages
- [ ] Code coverage meets project standards

### Maintenance
- [ ] Update tests when requirements change
- [ ] Remove or update obsolete tests
- [ ] Refactor tests to reduce duplication
- [ ] Monitor and improve test performance

---

*Un approccio sistematico al testing garantisce codice affidabile, facilita il refactoring e accelera lo sviluppo futuro.*
