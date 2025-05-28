/**
 * TaskManager Class - Core business logic for task management
 * 
 * This class handles all task-related operations including:
 * - Creating, reading, updating, deleting tasks
 * - Task filtering and searching
 * - Priority and category management
 * - Statistics calculation
 * 
 * @author Your Team Name
 * @version 1.0.0
 */

class TaskManager {
    constructor() {
        this.tasks = [];
        this.nextId = 1;
        this.storage = new StorageManager();
        this.loadTasks();
    }

    /**
     * Load tasks from storage on initialization
     */
    loadTasks() {
        const savedTasks = this.storage.getTasks();
        if (savedTasks && savedTasks.length > 0) {
            this.tasks = savedTasks;
            this.nextId = Math.max(...this.tasks.map(task => task.id)) + 1;
        }
    }

    /**
     * Create a new task
     * @param {string} title - Task title (required)
     * @param {string} description - Task description (optional)
     * @param {string} priority - Task priority: 'low', 'medium', 'high'
     * @param {string} category - Task category
     * @param {string} dueDate - Due date in YYYY-MM-DD format
     * @returns {Object} Created task object
     */
    createTask(title, description = '', priority = 'medium', category = 'general', dueDate = null) {
        // Validate required fields
        if (!title || title.trim() === '') {
            throw new Error('Task title is required');
        }

        if (!['low', 'medium', 'high'].includes(priority)) {
            throw new Error('Invalid priority level');
        }

        const task = {
            id: this.nextId++,
            title: title.trim(),
            description: description.trim(),
            priority: priority,
            category: category,
            completed: false,
            createdAt: new Date().toISOString(),
            updatedAt: new Date().toISOString(),
            dueDate: dueDate,
            completedAt: null
        };

        this.tasks.push(task);
        this.saveTasks();
        return task;
    }

    /**
     * Get all tasks
     * @returns {Array} Array of all tasks
     */
    getAllTasks() {
        return [...this.tasks];
    }

    /**
     * Get task by ID
     * @param {number} id - Task ID
     * @returns {Object|null} Task object or null if not found
     */
    getTaskById(id) {
        return this.tasks.find(task => task.id === id) || null;
    }

    /**
     * Update existing task
     * @param {number} id - Task ID
     * @param {Object} updates - Object containing fields to update
     * @returns {Object|null} Updated task or null if not found
     */
    updateTask(id, updates) {
        const taskIndex = this.tasks.findIndex(task => task.id === id);
        
        if (taskIndex === -1) {
            return null;
        }

        // Validate updates
        if (updates.title !== undefined && updates.title.trim() === '') {
            throw new Error('Task title cannot be empty');
        }

        if (updates.priority && !['low', 'medium', 'high'].includes(updates.priority)) {
            throw new Error('Invalid priority level');
        }

        // Apply updates
        const task = this.tasks[taskIndex];
        Object.assign(task, {
            ...updates,
            updatedAt: new Date().toISOString()
        });

        // If marking as completed, set completion timestamp
        if (updates.completed === true && !task.completedAt) {
            task.completedAt = new Date().toISOString();
        } else if (updates.completed === false) {
            task.completedAt = null;
        }

        this.saveTasks();
        return task;
    }

    /**
     * Delete task by ID
     * @param {number} id - Task ID
     * @returns {boolean} True if deleted, false if not found
     */
    deleteTask(id) {
        const initialLength = this.tasks.length;
        this.tasks = this.tasks.filter(task => task.id !== id);
        
        if (this.tasks.length < initialLength) {
            this.saveTasks();
            return true;
        }
        return false;
    }

    /**
     * Toggle task completion status
     * @param {number} id - Task ID
     * @returns {Object|null} Updated task or null if not found
     */
    toggleTaskCompletion(id) {
        const task = this.getTaskById(id);
        if (!task) return null;

        return this.updateTask(id, {
            completed: !task.completed
        });
    }

    /**
     * Filter tasks by various criteria
     * @param {Object} filters - Filter criteria
     * @returns {Array} Filtered tasks
     */
    filterTasks(filters = {}) {
        let filteredTasks = [...this.tasks];

        // Filter by completion status
        if (filters.status === 'completed') {
            filteredTasks = filteredTasks.filter(task => task.completed);
        } else if (filters.status === 'pending') {
            filteredTasks = filteredTasks.filter(task => !task.completed);
        }

        // Filter by priority
        if (filters.priority && filters.priority !== 'all') {
            filteredTasks = filteredTasks.filter(task => task.priority === filters.priority);
        }

        // Filter by category
        if (filters.category && filters.category !== 'all') {
            filteredTasks = filteredTasks.filter(task => task.category === filters.category);
        }

        // Search by text
        if (filters.search && filters.search.trim() !== '') {
            const searchTerm = filters.search.trim().toLowerCase();
            filteredTasks = filteredTasks.filter(task =>
                task.title.toLowerCase().includes(searchTerm) ||
                task.description.toLowerCase().includes(searchTerm)
            );
        }

        return filteredTasks;
    }

    /**
     * Search tasks by title or description
     * @param {string} query - Search query
     * @returns {Array} Matching tasks
     */
    searchTasks(query) {
        if (!query || query.trim() === '') {
            return this.getAllTasks();
        }

        const searchTerm = query.trim().toLowerCase();
        return this.tasks.filter(task =>
            task.title.toLowerCase().includes(searchTerm) ||
            task.description.toLowerCase().includes(searchTerm)
        );
    }

    /**
     * Get task statistics
     * @returns {Object} Statistics object
     */
    getStatistics() {
        const total = this.tasks.length;
        const completed = this.tasks.filter(task => task.completed).length;
        const pending = total - completed;
        const highPriority = this.tasks.filter(task => task.priority === 'high' && !task.completed).length;
        const overdue = this.getOverdueTasks().length;

        return {
            total,
            completed,
            pending,
            highPriority,
            overdue,
            completionRate: total > 0 ? Math.round((completed / total) * 100) : 0
        };
    }

    /**
     * Get overdue tasks
     * @returns {Array} Overdue tasks
     */
    getOverdueTasks() {
        const today = new Date().toISOString().split('T')[0];
        return this.tasks.filter(task =>
            !task.completed &&
            task.dueDate &&
            task.dueDate < today
        );
    }

    /**
     * Mark all tasks as completed
     * @returns {number} Number of tasks marked as completed
     */
    markAllCompleted() {
        let count = 0;
        this.tasks.forEach(task => {
            if (!task.completed) {
                task.completed = true;
                task.completedAt = new Date().toISOString();
                task.updatedAt = new Date().toISOString();
                count++;
            }
        });

        if (count > 0) {
            this.saveTasks();
        }
        return count;
    }

    /**
     * Delete all completed tasks
     * @returns {number} Number of tasks deleted
     */
    deleteCompletedTasks() {
        const initialLength = this.tasks.length;
        this.tasks = this.tasks.filter(task => !task.completed);
        const deletedCount = initialLength - this.tasks.length;

        if (deletedCount > 0) {
            this.saveTasks();
        }
        return deletedCount;
    }

    /**
     * Get tasks grouped by category
     * @returns {Object} Tasks grouped by category
     */
    getTasksByCategory() {
        const grouped = {};
        this.tasks.forEach(task => {
            if (!grouped[task.category]) {
                grouped[task.category] = [];
            }
            grouped[task.category].push(task);
        });
        return grouped;
    }

    /**
     * Get tasks due today
     * @returns {Array} Tasks due today
     */
    getTasksDueToday() {
        const today = new Date().toISOString().split('T')[0];
        return this.tasks.filter(task =>
            !task.completed && task.dueDate === today
        );
    }

    /**
     * Export tasks to JSON format
     * @returns {string} JSON string of all tasks
     */
    exportTasks() {
        return JSON.stringify({
            tasks: this.tasks,
            exportDate: new Date().toISOString(),
            totalTasks: this.tasks.length
        }, null, 2);
    }

    /**
     * Import tasks from JSON format
     * @param {string} jsonData - JSON string containing tasks
     * @returns {number} Number of tasks imported
     */
    importTasks(jsonData) {
        try {
            const data = JSON.parse(jsonData);
            if (!data.tasks || !Array.isArray(data.tasks)) {
                throw new Error('Invalid task data format');
            }

            let importedCount = 0;
            data.tasks.forEach(taskData => {
                if (this.validateTaskData(taskData)) {
                    // Assign new ID to avoid conflicts
                    const task = { ...taskData, id: this.nextId++ };
                    this.tasks.push(task);
                    importedCount++;
                }
            });

            if (importedCount > 0) {
                this.saveTasks();
            }
            return importedCount;
        } catch (error) {
            throw new Error('Failed to import tasks: ' + error.message);
        }
    }

    /**
     * Validate task data structure
     * @param {Object} taskData - Task data to validate
     * @returns {boolean} True if valid
     */
    validateTaskData(taskData) {
        return (
            taskData &&
            typeof taskData.title === 'string' &&
            taskData.title.trim() !== '' &&
            ['low', 'medium', 'high'].includes(taskData.priority) &&
            typeof taskData.completed === 'boolean'
        );
    }

    /**
     * Save tasks to storage
     */
    saveTasks() {
        this.storage.saveTasks(this.tasks);
    }

    /**
     * Clear all tasks
     * @returns {number} Number of tasks cleared
     */
    clearAllTasks() {
        const count = this.tasks.length;
        this.tasks = [];
        this.nextId = 1;
        this.saveTasks();
        return count;
    }
}

// Export for Node.js testing environment
if (typeof module !== 'undefined' && module.exports) {
    module.exports = TaskManager;
}
