/**
 * UI Manager per il Task Manager
 * Gestisce tutte le interazioni con l'interfaccia utente
 * 
 * @file ui.js
 * @author Git Course Team
 * @version 1.0.0
 */

class UIManager {
    constructor(taskManager) {
        this.taskManager = taskManager;
        this.currentFilter = 'all';
        this.currentSort = 'date';
        this.isSearchActive = false;
        this.notifications = [];
        
        this.initializeUI();
        this.setupEventListeners();
        this.loadTheme();
    }

    /**
     * Inizializza l'interfaccia utente
     */
    initializeUI() {
        this.elements = {
            // Form elementi
            taskForm: document.getElementById('taskForm'),
            taskInput: document.getElementById('taskInput'),
            categorySelect: document.getElementById('categorySelect'),
            prioritySelect: document.getElementById('prioritySelect'),
            dueDateInput: document.getElementById('dueDateInput'),
            submitButton: document.getElementById('submitTask'),
            
            // Lista task
            taskList: document.getElementById('taskList'),
            emptyState: document.getElementById('emptyState'),
            
            // Filtri e ricerca
            filterButtons: document.querySelectorAll('.filter-btn'),
            sortSelect: document.getElementById('sortSelect'),
            searchInput: document.getElementById('searchInput'),
            searchClear: document.getElementById('searchClear'),
            
            // Statistiche
            totalTasks: document.getElementById('totalTasks'),
            completedTasks: document.getElementById('completedTasks'),
            pendingTasks: document.getElementById('pendingTasks'),
            
            // Modal
            modal: document.getElementById('taskModal'),
            modalTitle: document.getElementById('modalTitle'),
            modalBody: document.getElementById('modalBody'),
            modalClose: document.querySelectorAll('.modal-close'),
            
            // Azioni bulk
            selectAll: document.getElementById('selectAll'),
            bulkActions: document.getElementById('bulkActions'),
            deleteSelected: document.getElementById('deleteSelected'),
            markSelectedComplete: document.getElementById('markSelectedComplete'),
            
            // Import/Export
            exportButton: document.getElementById('exportTasks'),
            importButton: document.getElementById('importTasks'),
            importFile: document.getElementById('importFile'),
            
            // Tema
            themeToggle: document.getElementById('themeToggle'),
            
            // Notifiche
            notificationContainer: document.getElementById('notifications')
        };

        this.populateCategorySelect();
        this.updateStatistics();
    }

    /**
     * Configura gli event listeners
     */
    setupEventListeners() {
        // Form submission
        this.elements.taskForm?.addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleTaskSubmit();
        });

        // Filtri
        this.elements.filterButtons.forEach(btn => {
            btn.addEventListener('click', (e) => {
                this.setFilter(e.target.dataset.filter);
            });
        });

        // Ordinamento
        this.elements.sortSelect?.addEventListener('change', (e) => {
            this.setSorting(e.target.value);
        });

        // Ricerca
        this.elements.searchInput?.addEventListener('input', (e) => {
            this.handleSearch(e.target.value);
        });

        this.elements.searchClear?.addEventListener('click', () => {
            this.clearSearch();
        });

        // Modal
        this.elements.modalClose.forEach(btn => {
            btn.addEventListener('click', () => this.closeModal());
        });

        this.elements.modal?.addEventListener('click', (e) => {
            if (e.target === this.elements.modal) {
                this.closeModal();
            }
        });

        // Azioni bulk
        this.elements.selectAll?.addEventListener('change', (e) => {
            this.handleSelectAll(e.target.checked);
        });

        this.elements.deleteSelected?.addEventListener('click', () => {
            this.handleBulkDelete();
        });

        this.elements.markSelectedComplete?.addEventListener('click', () => {
            this.handleBulkComplete();
        });

        // Import/Export
        this.elements.exportButton?.addEventListener('click', () => {
            this.handleExport();
        });

        this.elements.importButton?.addEventListener('click', () => {
            this.elements.importFile?.click();
        });

        this.elements.importFile?.addEventListener('change', (e) => {
            this.handleImport(e.target.files[0]);
        });

        // Tema
        this.elements.themeToggle?.addEventListener('click', () => {
            this.toggleTheme();
        });

        // Keyboard shortcuts
        document.addEventListener('keydown', (e) => {
            this.handleKeyboardShortcuts(e);
        });

        // Task Manager events
        document.addEventListener('taskAdded', () => this.refreshUI());
        document.addEventListener('taskUpdated', () => this.refreshUI());
        document.addEventListener('taskDeleted', () => this.refreshUI());
    }

    /**
     * Gestisce l'invio del form
     */
    handleTaskSubmit() {
        const title = this.elements.taskInput.value.trim();
        const category = this.elements.categorySelect.value;
        const priority = this.elements.prioritySelect.value;
        const dueDate = this.elements.dueDateInput.value;

        if (!title) {
            this.showNotification('Il titolo della task è obbligatorio', 'error');
            this.elements.taskInput.focus();
            return;
        }

        const taskData = {
            title,
            category,
            priority,
            dueDate: dueDate || null,
            description: ''
        };

        try {
            const result = this.taskManager.addTask(taskData);
            
            if (result.success) {
                this.showNotification('Task aggiunta con successo!', 'success');
                this.resetForm();
                this.refreshUI();
            } else {
                this.showNotification(result.message, 'error');
            }
        } catch (error) {
            this.showNotification('Errore nell\'aggiunta della task', 'error');
            console.error('Errore add task:', error);
        }
    }

    /**
     * Reset del form
     */
    resetForm() {
        this.elements.taskForm.reset();
        this.elements.taskInput.focus();
    }

    /**
     * Aggiorna l'interfaccia utente
     */
    refreshUI() {
        this.renderTasks();
        this.updateStatistics();
        this.updateBulkActions();
    }

    /**
     * Renderizza la lista delle task
     */
    renderTasks() {
        if (!this.elements.taskList) return;

        let tasks = this.taskManager.getAllTasks();
        
        // Applica filtri
        tasks = this.applyCurrentFilters(tasks);
        
        // Applica ordinamento
        tasks = this.applySorting(tasks);

        if (tasks.length === 0) {
            this.showEmptyState();
            return;
        }

        this.hideEmptyState();
        this.elements.taskList.innerHTML = tasks.map(task => this.createTaskElement(task)).join('');
        
        // Aggiungi event listeners alle task renderizzate
        this.attachTaskEventListeners();
    }

    /**
     * Crea l'elemento HTML per una task
     * @param {Object} task - Dati della task
     * @returns {string} HTML della task
     */
    createTaskElement(task) {
        const dueDate = task.dueDate ? new Date(task.dueDate) : null;
        const isOverdue = dueDate && dueDate < new Date() && !task.completed;
        const dueDateFormatted = dueDate ? dueDate.toLocaleDateString('it-IT') : '';

        return `
            <div class="task-item ${task.completed ? 'completed' : ''} ${isOverdue ? 'overdue' : ''}" 
                 data-id="${task.id}">
                <div class="task-checkbox">
                    <input type="checkbox" 
                           id="task-${task.id}" 
                           ${task.completed ? 'checked' : ''}
                           onchange="ui.toggleTask('${task.id}')">
                    <label for="task-${task.id}"></label>
                </div>
                
                <div class="task-content" onclick="ui.openTaskDetails('${task.id}')">
                    <div class="task-title">${this.escapeHtml(task.title)}</div>
                    <div class="task-meta">
                        <span class="task-category category-${task.category.toLowerCase()}">${task.category}</span>
                        <span class="task-priority priority-${task.priority}">${this.getPriorityLabel(task.priority)}</span>
                        ${dueDateFormatted ? `<span class="task-due-date ${isOverdue ? 'overdue' : ''}">${dueDateFormatted}</span>` : ''}
                    </div>
                    ${task.description ? `<div class="task-description">${this.escapeHtml(task.description)}</div>` : ''}
                </div>
                
                <div class="task-actions">
                    <button class="btn-icon edit-task" onclick="ui.editTask('${task.id}')" title="Modifica">
                        <i class="icon-edit"></i>
                    </button>
                    <button class="btn-icon delete-task" onclick="ui.confirmDeleteTask('${task.id}')" title="Elimina">
                        <i class="icon-delete"></i>
                    </button>
                </div>
                
                <div class="task-select">
                    <input type="checkbox" class="task-select-checkbox" data-id="${task.id}">
                </div>
            </div>
        `;
    }

    /**
     * Gestisce il toggle dello stato di una task
     * @param {string} taskId - ID della task
     */
    toggleTask(taskId) {
        try {
            const result = this.taskManager.toggleTask(taskId);
            
            if (result.success) {
                const task = this.taskManager.getTask(taskId);
                const message = task.completed ? 'Task completata!' : 'Task riaperta';
                this.showNotification(message, 'success');
                this.refreshUI();
            } else {
                this.showNotification(result.message, 'error');
            }
        } catch (error) {
            this.showNotification('Errore nell\'aggiornamento della task', 'error');
            console.error('Errore toggle task:', error);
        }
    }

    /**
     * Apre i dettagli di una task
     * @param {string} taskId - ID della task
     */
    openTaskDetails(taskId) {
        const task = this.taskManager.getTask(taskId);
        if (!task) return;

        const modalContent = `
            <div class="task-details">
                <h3>${this.escapeHtml(task.title)}</h3>
                <div class="task-details-meta">
                    <p><strong>Categoria:</strong> ${task.category}</p>
                    <p><strong>Priorità:</strong> ${this.getPriorityLabel(task.priority)}</p>
                    <p><strong>Stato:</strong> ${task.completed ? 'Completata' : 'In corso'}</p>
                    ${task.dueDate ? `<p><strong>Scadenza:</strong> ${new Date(task.dueDate).toLocaleDateString('it-IT')}</p>` : ''}
                    <p><strong>Creata:</strong> ${new Date(task.createdAt).toLocaleDateString('it-IT')}</p>
                    ${task.completedAt ? `<p><strong>Completata:</strong> ${new Date(task.completedAt).toLocaleDateString('it-IT')}</p>` : ''}
                </div>
                ${task.description ? `
                    <div class="task-description-full">
                        <h4>Descrizione:</h4>
                        <p>${this.escapeHtml(task.description)}</p>
                    </div>
                ` : ''}
                <div class="task-details-actions">
                    <button class="btn btn-primary" onclick="ui.editTask('${task.id}'); ui.closeModal();">
                        Modifica Task
                    </button>
                    <button class="btn btn-secondary" onclick="ui.toggleTask('${task.id}');">
                        ${task.completed ? 'Riapri Task' : 'Completa Task'}
                    </button>
                </div>
            </div>
        `;

        this.openModal('Dettagli Task', modalContent);
    }

    /**
     * Modifica una task esistente
     * @param {string} taskId - ID della task
     */
    editTask(taskId) {
        const task = this.taskManager.getTask(taskId);
        if (!task) return;

        // Popola il form con i dati della task
        this.elements.taskInput.value = task.title;
        this.elements.categorySelect.value = task.category;
        this.elements.prioritySelect.value = task.priority;
        this.elements.dueDateInput.value = task.dueDate ? task.dueDate.split('T')[0] : '';

        // Cambia il comportamento del form per l'editing
        this.elements.taskForm.dataset.editingId = taskId;
        this.elements.submitButton.textContent = 'Aggiorna Task';
        this.elements.taskInput.focus();

        this.showNotification('Modalità modifica attivata', 'info');
    }

    /**
     * Conferma l'eliminazione di una task
     * @param {string} taskId - ID della task
     */
    confirmDeleteTask(taskId) {
        const task = this.taskManager.getTask(taskId);
        if (!task) return;

        const modalContent = `
            <div class="confirm-delete">
                <p>Sei sicuro di voler eliminare la task "<strong>${this.escapeHtml(task.title)}</strong>"?</p>
                <p class="warning">Questa azione non può essere annullata.</p>
                <div class="confirm-actions">
                    <button class="btn btn-danger" onclick="ui.deleteTask('${task.id}'); ui.closeModal();">
                        Elimina Task
                    </button>
                    <button class="btn btn-secondary" onclick="ui.closeModal();">
                        Annulla
                    </button>
                </div>
            </div>
        `;

        this.openModal('Conferma Eliminazione', modalContent);
    }

    /**
     * Elimina una task
     * @param {string} taskId - ID della task
     */
    deleteTask(taskId) {
        try {
            const result = this.taskManager.deleteTask(taskId);
            
            if (result.success) {
                this.showNotification('Task eliminata con successo', 'success');
                this.refreshUI();
            } else {
                this.showNotification(result.message, 'error');
            }
        } catch (error) {
            this.showNotification('Errore nell\'eliminazione della task', 'error');
            console.error('Errore delete task:', error);
        }
    }

    /**
     * Applica i filtri correnti
     * @param {Array} tasks - Array delle task
     * @returns {Array} Task filtrate
     */
    applyCurrentFilters(tasks) {
        let filtered = [...tasks];

        // Filtro per stato
        switch (this.currentFilter) {
            case 'completed':
                filtered = filtered.filter(task => task.completed);
                break;
            case 'pending':
                filtered = filtered.filter(task => !task.completed);
                break;
            case 'overdue':
                const now = new Date();
                filtered = filtered.filter(task => 
                    !task.completed && 
                    task.dueDate && 
                    new Date(task.dueDate) < now
                );
                break;
        }

        // Filtro per ricerca
        if (this.isSearchActive && this.searchQuery) {
            const query = this.searchQuery.toLowerCase();
            filtered = filtered.filter(task =>
                task.title.toLowerCase().includes(query) ||
                task.description.toLowerCase().includes(query) ||
                task.category.toLowerCase().includes(query)
            );
        }

        return filtered;
    }

    /**
     * Applica l'ordinamento
     * @param {Array} tasks - Array delle task
     * @returns {Array} Task ordinate
     */
    applySorting(tasks) {
        return [...tasks].sort((a, b) => {
            switch (this.currentSort) {
                case 'title':
                    return a.title.localeCompare(b.title);
                case 'priority':
                    const priorityOrder = { 'alta': 3, 'media': 2, 'bassa': 1 };
                    return priorityOrder[b.priority] - priorityOrder[a.priority];
                case 'dueDate':
                    if (!a.dueDate && !b.dueDate) return 0;
                    if (!a.dueDate) return 1;
                    if (!b.dueDate) return -1;
                    return new Date(a.dueDate) - new Date(b.dueDate);
                case 'category':
                    return a.category.localeCompare(b.category);
                default: // 'date'
                    return new Date(b.createdAt) - new Date(a.createdAt);
            }
        });
    }

    /**
     * Imposta il filtro corrente
     * @param {string} filter - Tipo di filtro
     */
    setFilter(filter) {
        this.currentFilter = filter;
        
        // Aggiorna UI dei bottoni filtro
        this.elements.filterButtons.forEach(btn => {
            btn.classList.toggle('active', btn.dataset.filter === filter);
        });
        
        this.refreshUI();
    }

    /**
     * Imposta l'ordinamento
     * @param {string} sort - Tipo di ordinamento
     */
    setSorting(sort) {
        this.currentSort = sort;
        this.refreshUI();
    }

    /**
     * Gestisce la ricerca
     * @param {string} query - Query di ricerca
     */
    handleSearch(query) {
        this.searchQuery = query.trim();
        this.isSearchActive = this.searchQuery.length > 0;
        
        this.elements.searchClear.style.display = this.isSearchActive ? 'block' : 'none';
        this.refreshUI();
    }

    /**
     * Cancella la ricerca
     */
    clearSearch() {
        this.elements.searchInput.value = '';
        this.searchQuery = '';
        this.isSearchActive = false;
        this.elements.searchClear.style.display = 'none';
        this.refreshUI();
    }

    /**
     * Aggiorna le statistiche
     */
    updateStatistics() {
        const stats = this.taskManager.getStatistics();
        
        if (this.elements.totalTasks) {
            this.elements.totalTasks.textContent = stats.total;
        }
        if (this.elements.completedTasks) {
            this.elements.completedTasks.textContent = stats.completed;
        }
        if (this.elements.pendingTasks) {
            this.elements.pendingTasks.textContent = stats.pending;
        }
    }

    /**
     * Popola il select delle categorie
     */
    populateCategorySelect() {
        if (!this.elements.categorySelect) return;

        const categories = this.taskManager.getCategories();
        this.elements.categorySelect.innerHTML = categories
            .map(cat => `<option value="${cat}">${cat}</option>`)
            .join('');
    }

    /**
     * Mostra lo stato vuoto
     */
    showEmptyState() {
        if (this.elements.taskList) {
            this.elements.taskList.innerHTML = '';
        }
        if (this.elements.emptyState) {
            this.elements.emptyState.style.display = 'block';
        }
    }

    /**
     * Nasconde lo stato vuoto
     */
    hideEmptyState() {
        if (this.elements.emptyState) {
            this.elements.emptyState.style.display = 'none';
        }
    }

    /**
     * Apre un modal
     * @param {string} title - Titolo del modal
     * @param {string} content - Contenuto HTML del modal
     */
    openModal(title, content) {
        if (this.elements.modalTitle) {
            this.elements.modalTitle.textContent = title;
        }
        if (this.elements.modalBody) {
            this.elements.modalBody.innerHTML = content;
        }
        if (this.elements.modal) {
            this.elements.modal.style.display = 'flex';
            document.body.style.overflow = 'hidden';
        }
    }

    /**
     * Chiude il modal
     */
    closeModal() {
        if (this.elements.modal) {
            this.elements.modal.style.display = 'none';
            document.body.style.overflow = '';
        }
    }

    /**
     * Mostra una notifica
     * @param {string} message - Messaggio da mostrare
     * @param {string} type - Tipo di notifica (success, error, info, warning)
     */
    showNotification(message, type = 'info') {
        const notification = {
            id: Date.now(),
            message,
            type,
            timestamp: new Date()
        };

        this.notifications.push(notification);
        this.renderNotification(notification);

        // Rimuovi la notifica dopo 5 secondi
        setTimeout(() => {
            this.removeNotification(notification.id);
        }, 5000);
    }

    /**
     * Renderizza una notifica
     * @param {Object} notification - Dati della notifica
     */
    renderNotification(notification) {
        if (!this.elements.notificationContainer) return;

        const notificationEl = document.createElement('div');
        notificationEl.className = `notification notification-${notification.type}`;
        notificationEl.dataset.id = notification.id;
        notificationEl.innerHTML = `
            <div class="notification-content">
                <span class="notification-message">${this.escapeHtml(notification.message)}</span>
                <button class="notification-close" onclick="ui.removeNotification(${notification.id})">×</button>
            </div>
        `;

        this.elements.notificationContainer.appendChild(notificationEl);
        
        // Animazione di entrata
        setTimeout(() => {
            notificationEl.classList.add('show');
        }, 10);
    }

    /**
     * Rimuove una notifica
     * @param {number} notificationId - ID della notifica
     */
    removeNotification(notificationId) {
        const notificationEl = document.querySelector(`[data-id="${notificationId}"]`);
        if (notificationEl) {
            notificationEl.classList.add('fade-out');
            setTimeout(() => {
                notificationEl.remove();
            }, 300);
        }

        this.notifications = this.notifications.filter(n => n.id !== notificationId);
    }

    /**
     * Gestisce le scorciatoie da tastiera
     * @param {KeyboardEvent} e - Evento tastiera
     */
    handleKeyboardShortcuts(e) {
        // Ctrl/Cmd + N: Nuova task
        if ((e.ctrlKey || e.metaKey) && e.key === 'n') {
            e.preventDefault();
            this.elements.taskInput?.focus();
        }

        // Escape: Chiudi modal o cancella ricerca
        if (e.key === 'Escape') {
            if (this.elements.modal.style.display === 'flex') {
                this.closeModal();
            } else if (this.isSearchActive) {
                this.clearSearch();
            }
        }

        // Ctrl/Cmd + F: Focus su ricerca
        if ((e.ctrlKey || e.metaKey) && e.key === 'f') {
            e.preventDefault();
            this.elements.searchInput?.focus();
        }
    }

    /**
     * Carica il tema dall'storage
     */
    loadTheme() {
        const savedTheme = localStorage.getItem('taskManager_theme') || 'light';
        document.documentElement.setAttribute('data-theme', savedTheme);
        
        if (this.elements.themeToggle) {
            this.elements.themeToggle.textContent = savedTheme === 'light' ? '🌙' : '☀️';
        }
    }

    /**
     * Cambia il tema
     */
    toggleTheme() {
        const currentTheme = document.documentElement.getAttribute('data-theme');
        const newTheme = currentTheme === 'light' ? 'dark' : 'light';
        
        document.documentElement.setAttribute('data-theme', newTheme);
        localStorage.setItem('taskManager_theme', newTheme);
        
        if (this.elements.themeToggle) {
            this.elements.themeToggle.textContent = newTheme === 'light' ? '🌙' : '☀️';
        }
        
        this.showNotification(`Tema ${newTheme === 'light' ? 'chiaro' : 'scuro'} attivato`, 'info');
    }

    /**
     * Escape HTML per prevenire XSS
     * @param {string} text - Testo da escape
     * @returns {string} Testo escaped
     */
    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }

    /**
     * Ottiene l'etichetta della priorità
     * @param {string} priority - Livello di priorità
     * @returns {string} Etichetta tradotta
     */
    getPriorityLabel(priority) {
        const labels = {
            'alta': 'Alta',
            'media': 'Media',
            'bassa': 'Bassa'
        };
        return labels[priority] || priority;
    }

    /**
     * Allega event listeners alle task renderizzate
     */
    attachTaskEventListeners() {
        // Event listeners per selezione multipla
        const checkboxes = document.querySelectorAll('.task-select-checkbox');
        checkboxes.forEach(checkbox => {
            checkbox.addEventListener('change', () => {
                this.updateBulkActions();
            });
        });
    }

    /**
     * Gestisce la selezione di tutte le task
     * @param {boolean} checked - Stato del checkbox
     */
    handleSelectAll(checked) {
        const checkboxes = document.querySelectorAll('.task-select-checkbox');
        checkboxes.forEach(checkbox => {
            checkbox.checked = checked;
        });
        this.updateBulkActions();
    }

    /**
     * Aggiorna le azioni bulk
     */
    updateBulkActions() {
        const selectedCheckboxes = document.querySelectorAll('.task-select-checkbox:checked');
        const hasSelection = selectedCheckboxes.length > 0;
        
        if (this.elements.bulkActions) {
            this.elements.bulkActions.style.display = hasSelection ? 'block' : 'none';
        }
        
        if (this.elements.selectAll) {
            const allCheckboxes = document.querySelectorAll('.task-select-checkbox');
            this.elements.selectAll.indeterminate = selectedCheckboxes.length > 0 && selectedCheckboxes.length < allCheckboxes.length;
            this.elements.selectAll.checked = selectedCheckboxes.length === allCheckboxes.length && allCheckboxes.length > 0;
        }
    }

    /**
     * Gestisce l'eliminazione multipla
     */
    handleBulkDelete() {
        const selectedIds = Array.from(document.querySelectorAll('.task-select-checkbox:checked'))
            .map(checkbox => checkbox.dataset.id);
        
        if (selectedIds.length === 0) return;

        const modalContent = `
            <div class="confirm-delete">
                <p>Sei sicuro di voler eliminare ${selectedIds.length} task selezionate?</p>
                <p class="warning">Questa azione non può essere annullata.</p>
                <div class="confirm-actions">
                    <button class="btn btn-danger" onclick="ui.executeBulkDelete(['${selectedIds.join("','")}']); ui.closeModal();">
                        Elimina Task Selezionate
                    </button>
                    <button class="btn btn-secondary" onclick="ui.closeModal();">
                        Annulla
                    </button>
                </div>
            </div>
        `;

        this.openModal('Conferma Eliminazione Multipla', modalContent);
    }

    /**
     * Esegue l'eliminazione multipla
     * @param {Array} taskIds - Array degli ID delle task da eliminare
     */
    executeBulkDelete(taskIds) {
        let deletedCount = 0;
        let errors = 0;

        taskIds.forEach(id => {
            try {
                const result = this.taskManager.deleteTask(id);
                if (result.success) {
                    deletedCount++;
                } else {
                    errors++;
                }
            } catch (error) {
                errors++;
                console.error('Errore eliminazione task:', error);
            }
        });

        if (deletedCount > 0) {
            this.showNotification(`${deletedCount} task eliminate con successo`, 'success');
        }
        if (errors > 0) {
            this.showNotification(`${errors} errori durante l'eliminazione`, 'error');
        }

        this.refreshUI();
    }

    /**
     * Gestisce il completamento multiplo
     */
    handleBulkComplete() {
        const selectedIds = Array.from(document.querySelectorAll('.task-select-checkbox:checked'))
            .map(checkbox => checkbox.dataset.id);
        
        if (selectedIds.length === 0) return;

        let completedCount = 0;
        let errors = 0;

        selectedIds.forEach(id => {
            try {
                const task = this.taskManager.getTask(id);
                if (task && !task.completed) {
                    const result = this.taskManager.toggleTask(id);
                    if (result.success) {
                        completedCount++;
                    } else {
                        errors++;
                    }
                }
            } catch (error) {
                errors++;
                console.error('Errore completamento task:', error);
            }
        });

        if (completedCount > 0) {
            this.showNotification(`${completedCount} task completate`, 'success');
        }
        if (errors > 0) {
            this.showNotification(`${errors} errori durante il completamento`, 'error');
        }

        this.refreshUI();
    }

    /**
     * Gestisce l'esportazione dei dati
     */
    handleExport() {
        try {
            const data = this.taskManager.exportTasks();
            const blob = new Blob([data], { type: 'application/json' });
            const url = URL.createObjectURL(blob);
            
            const a = document.createElement('a');
            a.href = url;
            a.download = `task-manager-export-${new Date().toISOString().split('T')[0]}.json`;
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);
            
            this.showNotification('Dati esportati con successo', 'success');
        } catch (error) {
            this.showNotification('Errore durante l\'esportazione', 'error');
            console.error('Errore export:', error);
        }
    }

    /**
     * Gestisce l'importazione dei dati
     * @param {File} file - File da importare
     */
    handleImport(file) {
        if (!file) return;

        const reader = new FileReader();
        reader.onload = (e) => {
            try {
                const result = this.taskManager.importTasks(e.target.result);
                
                if (result.success) {
                    this.showNotification(result.message, 'success');
                    this.refreshUI();
                } else {
                    this.showNotification(result.message, 'error');
                }
            } catch (error) {
                this.showNotification('Errore nella lettura del file', 'error');
                console.error('Errore import:', error);
            }
        };
        
        reader.onerror = () => {
            this.showNotification('Errore nella lettura del file', 'error');
        };
        
        reader.readAsText(file);
        
        // Reset input file
        this.elements.importFile.value = '';
    }
}

// Rendi disponibili le funzioni globalmente per gli event handler inline
window.ui = null; // Sarà inizializzato in app.js
