/**
 * Test suite per TaskManager class
 * Esempio di testing con Jest
 * 
 * @file taskManager.test.js
 * @author Git Course Team
 * @version 1.0.0
 */

// Mock StorageManager per i test
class MockStorageManager {
  constructor() {
    this.data = { tasks: [] };
  }
  
  saveTasks(tasks) {
    this.data.tasks = [...tasks];
    return { success: true, message: 'Saved' };
  }
  
  loadTasks() {
    return { 
      tasks: [...this.data.tasks], 
      success: true, 
      source: 'mock' 
    };
  }
  
  exportData() {
    return JSON.stringify(this.data);
  }
  
  importData(jsonData) {
    try {
      const data = JSON.parse(jsonData);
      this.data.tasks = data.tasks || [];
      return { success: true, imported: this.data.tasks.length };
    } catch (error) {
      return { success: false, message: error.message };
    }
  }
}

// Import della classe da testare (simulato)
// In un ambiente reale, useresti: import TaskManager from '../js/taskManager.js';
const TaskManager = require('../js/taskManager.js');

describe('TaskManager', () => {
  let taskManager;
  let mockStorage;

  beforeEach(() => {
    mockStorage = new MockStorageManager();
    taskManager = new TaskManager(mockStorage);
  });

  afterEach(() => {
    taskManager = null;
    mockStorage = null;
  });

  describe('Constructor', () => {
    test('should initialize with empty tasks array', () => {
      expect(taskManager.getAllTasks()).toEqual([]);
    });

    test('should set default categories', () => {
      const categories = taskManager.getCategories();
      expect(categories).toContain('Personale');
      expect(categories).toContain('Lavoro');
      expect(categories).toContain('Studio');
    });
  });

  describe('addTask', () => {
    test('should add a new task with required fields', () => {
      const taskData = {
        title: 'Test Task',
        category: 'Personale',
        priority: 'media'
      };

      const result = taskManager.addTask(taskData);
      
      expect(result.success).toBe(true);
      expect(result.task).toMatchObject({
        title: 'Test Task',
        category: 'Personale',
        priority: 'media',
        completed: false
      });
      expect(result.task.id).toBeDefined();
      expect(result.task.createdAt).toBeDefined();
    });

    test('should reject task without title', () => {
      const taskData = {
        category: 'Personale',
        priority: 'media'
      };

      const result = taskManager.addTask(taskData);
      
      expect(result.success).toBe(false);
      expect(result.message).toContain('titolo');
    });

    test('should auto-generate ID for new task', () => {
      const task1 = taskManager.addTask({ title: 'Task 1' });
      const task2 = taskManager.addTask({ title: 'Task 2' });
      
      expect(task1.task.id).not.toBe(task2.task.id);
    });

    test('should set default values for optional fields', () => {
      const result = taskManager.addTask({ title: 'Test Task' });
      
      expect(result.task.category).toBe('Generale');
      expect(result.task.priority).toBe('media');
      expect(result.task.description).toBe('');
      expect(result.task.completed).toBe(false);
    });
  });

  describe('getTask', () => {
    test('should return task by ID', () => {
      const addResult = taskManager.addTask({ title: 'Test Task' });
      const task = taskManager.getTask(addResult.task.id);
      
      expect(task).toMatchObject({
        id: addResult.task.id,
        title: 'Test Task'
      });
    });

    test('should return null for non-existent ID', () => {
      const task = taskManager.getTask('non-existent-id');
      expect(task).toBeNull();
    });
  });

  describe('updateTask', () => {
    test('should update existing task', () => {
      const addResult = taskManager.addTask({ title: 'Original Task' });
      const taskId = addResult.task.id;
      
      const updateResult = taskManager.updateTask(taskId, {
        title: 'Updated Task',
        priority: 'alta'
      });
      
      expect(updateResult.success).toBe(true);
      
      const updatedTask = taskManager.getTask(taskId);
      expect(updatedTask.title).toBe('Updated Task');
      expect(updatedTask.priority).toBe('alta');
      expect(updatedTask.updatedAt).toBeDefined();
    });

    test('should reject update with invalid ID', () => {
      const result = taskManager.updateTask('invalid-id', { title: 'Test' });
      expect(result.success).toBe(false);
    });

    test('should reject update without title', () => {
      const addResult = taskManager.addTask({ title: 'Test Task' });
      const result = taskManager.updateTask(addResult.task.id, { title: '' });
      
      expect(result.success).toBe(false);
      expect(result.message).toContain('titolo');
    });
  });

  describe('deleteTask', () => {
    test('should delete existing task', () => {
      const addResult = taskManager.addTask({ title: 'Task to Delete' });
      const taskId = addResult.task.id;
      
      const deleteResult = taskManager.deleteTask(taskId);
      expect(deleteResult.success).toBe(true);
      
      const task = taskManager.getTask(taskId);
      expect(task).toBeNull();
    });

    test('should reject deletion of non-existent task', () => {
      const result = taskManager.deleteTask('invalid-id');
      expect(result.success).toBe(false);
    });
  });

  describe('toggleTask', () => {
    test('should toggle task completion status', () => {
      const addResult = taskManager.addTask({ title: 'Test Task' });
      const taskId = addResult.task.id;
      
      // Toggle to completed
      let toggleResult = taskManager.toggleTask(taskId);
      expect(toggleResult.success).toBe(true);
      
      let task = taskManager.getTask(taskId);
      expect(task.completed).toBe(true);
      expect(task.completedAt).toBeDefined();
      
      // Toggle back to incomplete
      toggleResult = taskManager.toggleTask(taskId);
      expect(toggleResult.success).toBe(true);
      
      task = taskManager.getTask(taskId);
      expect(task.completed).toBe(false);
      expect(task.completedAt).toBeNull();
    });
  });

  describe('getStatistics', () => {
    beforeEach(() => {
      // Add test tasks
      taskManager.addTask({ title: 'Task 1' });
      taskManager.addTask({ title: 'Task 2' });
      taskManager.addTask({ title: 'Task 3' });
      
      // Complete one task
      const tasks = taskManager.getAllTasks();
      taskManager.toggleTask(tasks[0].id);
    });

    test('should return correct statistics', () => {
      const stats = taskManager.getStatistics();
      
      expect(stats.total).toBe(3);
      expect(stats.completed).toBe(1);
      expect(stats.pending).toBe(2);
      expect(stats.completionRate).toBe(33);
    });

    test('should calculate completion rate correctly', () => {
      // Complete all tasks
      const tasks = taskManager.getAllTasks();
      tasks.forEach(task => {
        if (!task.completed) {
          taskManager.toggleTask(task.id);
        }
      });
      
      const stats = taskManager.getStatistics();
      expect(stats.completionRate).toBe(100);
    });
  });

  describe('searchTasks', () => {
    beforeEach(() => {
      taskManager.addTask({ 
        title: 'JavaScript Development', 
        description: 'Learn React hooks',
        category: 'Studio'
      });
      taskManager.addTask({ 
        title: 'Buy groceries', 
        description: 'Milk and bread',
        category: 'Personale'
      });
      taskManager.addTask({ 
        title: 'Project Meeting', 
        description: 'Discuss JavaScript project',
        category: 'Lavoro'
      });
    });

    test('should search in titles', () => {
      const results = taskManager.searchTasks('JavaScript');
      expect(results).toHaveLength(2);
    });

    test('should search in descriptions', () => {
      const results = taskManager.searchTasks('React');
      expect(results).toHaveLength(1);
      expect(results[0].title).toBe('JavaScript Development');
    });

    test('should search in categories', () => {
      const results = taskManager.searchTasks('Studio');
      expect(results).toHaveLength(1);
    });

    test('should be case insensitive', () => {
      const results = taskManager.searchTasks('javascript');
      expect(results).toHaveLength(2);
    });

    test('should return empty array for no matches', () => {
      const results = taskManager.searchTasks('nonexistent');
      expect(results).toHaveLength(0);
    });
  });

  describe('filterTasks', () => {
    beforeEach(() => {
      taskManager.addTask({ title: 'Task 1', priority: 'alta' });
      taskManager.addTask({ title: 'Task 2', priority: 'media' });
      taskManager.addTask({ title: 'Task 3', priority: 'bassa' });
      
      // Complete first task
      const tasks = taskManager.getAllTasks();
      taskManager.toggleTask(tasks[0].id);
    });

    test('should filter by completion status', () => {
      const completed = taskManager.filterTasks({ completed: true });
      const pending = taskManager.filterTasks({ completed: false });
      
      expect(completed).toHaveLength(1);
      expect(pending).toHaveLength(2);
    });

    test('should filter by priority', () => {
      const highPriority = taskManager.filterTasks({ priority: 'alta' });
      expect(highPriority).toHaveLength(1);
    });

    test('should filter by multiple criteria', () => {
      const results = taskManager.filterTasks({ 
        completed: false, 
        priority: 'media' 
      });
      expect(results).toHaveLength(1);
    });
  });

  describe('Data Persistence', () => {
    test('should save tasks automatically on add', () => {
      const spy = jest.spyOn(mockStorage, 'saveTasks');
      taskManager.addTask({ title: 'Test Task' });
      
      expect(spy).toHaveBeenCalled();
    });

    test('should load tasks on initialization', () => {
      // Add task to mock storage
      mockStorage.data.tasks = [{
        id: 'test-id',
        title: 'Loaded Task',
        completed: false,
        createdAt: new Date().toISOString()
      }];
      
      // Create new TaskManager instance
      const newTaskManager = new TaskManager(mockStorage);
      const tasks = newTaskManager.getAllTasks();
      
      expect(tasks).toHaveLength(1);
      expect(tasks[0].title).toBe('Loaded Task');
    });
  });

  describe('Import/Export', () => {
    test('should export tasks as JSON', () => {
      taskManager.addTask({ title: 'Task 1' });
      taskManager.addTask({ title: 'Task 2' });
      
      const exported = taskManager.exportTasks();
      const data = JSON.parse(exported);
      
      expect(data.tasks).toHaveLength(2);
      expect(data.exportDate).toBeDefined();
      expect(data.version).toBeDefined();
    });

    test('should import tasks from JSON', () => {
      const importData = JSON.stringify({
        tasks: [
          { title: 'Imported Task 1', completed: false },
          { title: 'Imported Task 2', completed: true }
        ]
      });
      
      const result = taskManager.importTasks(importData);
      
      expect(result.success).toBe(true);
      expect(result.imported).toBe(2);
      
      const tasks = taskManager.getAllTasks();
      expect(tasks).toHaveLength(2);
    });

    test('should reject invalid import data', () => {
      const result = taskManager.importTasks('invalid json');
      expect(result.success).toBe(false);
    });
  });

  describe('Error Handling', () => {
    test('should handle storage errors gracefully', () => {
      // Mock storage error
      mockStorage.saveTasks = jest.fn().mockReturnValue({
        success: false,
        message: 'Storage error'
      });
      
      const result = taskManager.addTask({ title: 'Test Task' });
      
      // Task should still be added to memory even if storage fails
      expect(taskManager.getAllTasks()).toHaveLength(1);
    });

    test('should validate task data types', () => {
      const result = taskManager.addTask({
        title: 123, // Invalid type
        priority: 'invalid' // Invalid value
      });
      
      expect(result.success).toBe(false);
    });
  });
});

describe('Integration Tests', () => {
  test('should handle complete task lifecycle', () => {
    const storage = new MockStorageManager();
    const manager = new TaskManager(storage);
    
    // Add task
    const addResult = manager.addTask({
      title: 'Integration Test Task',
      category: 'Studio',
      priority: 'alta',
      description: 'Testing complete lifecycle'
    });
    
    expect(addResult.success).toBe(true);
    const taskId = addResult.task.id;
    
    // Update task
    const updateResult = manager.updateTask(taskId, {
      title: 'Updated Integration Task',
      priority: 'media'
    });
    
    expect(updateResult.success).toBe(true);
    
    // Toggle completion
    const toggleResult = manager.toggleTask(taskId);
    expect(toggleResult.success).toBe(true);
    
    // Verify final state
    const finalTask = manager.getTask(taskId);
    expect(finalTask.title).toBe('Updated Integration Task');
    expect(finalTask.priority).toBe('media');
    expect(finalTask.completed).toBe(true);
    expect(finalTask.completedAt).toBeDefined();
    
    // Delete task
    const deleteResult = manager.deleteTask(taskId);
    expect(deleteResult.success).toBe(true);
    expect(manager.getTask(taskId)).toBeNull();
  });
});
