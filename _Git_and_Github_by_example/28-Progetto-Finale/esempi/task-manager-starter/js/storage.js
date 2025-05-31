/**
 * LocalStorage Manager per il Task Manager
 * Gestisce la persistenza dei dati con backup e recovery
 * 
 * @file storage.js
 * @author Git Course Team
 * @version 1.0.0
 */

class StorageManager {
    constructor() {
        this.storageKey = 'taskManager_data';
        this.backupKey = 'taskManager_backup';
        this.versionKey = 'taskManager_version';
        this.currentVersion = '1.0.0';
        
        this.initializeStorage();
    }

    /**
     * Inizializza il sistema di storage
     */
    initializeStorage() {
        try {
            // Verifica compatibilità localStorage
            if (!this.isLocalStorageAvailable()) {
                console.warn('LocalStorage non disponibile, usando storage temporaneo');
                this.useMemoryStorage();
                return;
            }

            // Verifica e aggiorna versione se necessario
            this.checkAndMigrateVersion();
            
            // Crea backup iniziale se non esiste
            if (!localStorage.getItem(this.backupKey)) {
                this.createBackup();
            }
        } catch (error) {
            console.error('Errore inizializzazione storage:', error);
            this.useMemoryStorage();
        }
    }

    /**
     * Verifica se localStorage è disponibile
     * @returns {boolean}
     */
    isLocalStorageAvailable() {
        try {
            const test = '__storage_test__';
            localStorage.setItem(test, test);
            localStorage.removeItem(test);
            return true;
        } catch (e) {
            return false;
        }
    }

    /**
     * Usa storage in memoria come fallback
     */
    useMemoryStorage() {
        this.memoryStorage = {
            tasks: [],
            categories: ['Personale', 'Lavoro', 'Studio'],
            settings: {
                theme: 'light',
                notifications: true,
                autoSave: true
            }
        };
        this.isMemoryMode = true;
    }

    /**
     * Salva i dati nel localStorage
     * @param {Array} tasks - Array delle task
     * @param {Object} options - Opzioni aggiuntive
     */
    saveTasks(tasks, options = {}) {
        try {
            if (this.isMemoryMode) {
                this.memoryStorage.tasks = [...tasks];
                return { success: true, message: 'Dati salvati in memoria' };
            }

            const data = {
                tasks: tasks,
                timestamp: new Date().toISOString(),
                version: this.currentVersion,
                metadata: {
                    totalTasks: tasks.length,
                    completedTasks: tasks.filter(t => t.completed).length,
                    categories: [...new Set(tasks.map(t => t.category))]
                }
            };

            // Crea backup prima di salvare
            if (options.createBackup !== false) {
                this.createBackup();
            }

            localStorage.setItem(this.storageKey, JSON.stringify(data));
            
            return { 
                success: true, 
                message: 'Dati salvati con successo',
                timestamp: data.timestamp
            };
        } catch (error) {
            console.error('Errore nel salvataggio:', error);
            
            // Tenta il recupero da backup
            if (error.name === 'QuotaExceededError') {
                return this.handleQuotaExceeded();
            }
            
            return { 
                success: false, 
                message: `Errore nel salvataggio: ${error.message}` 
            };
        }
    }

    /**
     * Carica i dati dal localStorage
     * @returns {Object} Dati caricati o struttura vuota
     */
    loadTasks() {
        try {
            if (this.isMemoryMode) {
                return {
                    tasks: this.memoryStorage.tasks,
                    success: true,
                    source: 'memory'
                };
            }

            const data = localStorage.getItem(this.storageKey);
            
            if (!data) {
                return this.getDefaultData();
            }

            const parsedData = JSON.parse(data);
            
            // Verifica integrità dati
            if (!this.validateData(parsedData)) {
                console.warn('Dati corrotti, tentativo di recupero da backup');
                return this.restoreFromBackup();
            }

            return {
                tasks: parsedData.tasks || [],
                metadata: parsedData.metadata || {},
                timestamp: parsedData.timestamp,
                success: true,
                source: 'localStorage'
            };
        } catch (error) {
            console.error('Errore nel caricamento:', error);
            return this.restoreFromBackup();
        }
    }

    /**
     * Valida l'integrità dei dati
     * @param {Object} data - Dati da validare
     * @returns {boolean}
     */
    validateData(data) {
        if (!data || typeof data !== 'object') return false;
        if (!Array.isArray(data.tasks)) return false;
        
        // Verifica che ogni task abbia le proprietà necessarie
        return data.tasks.every(task => 
            task.hasOwnProperty('id') && 
            task.hasOwnProperty('title') && 
            task.hasOwnProperty('completed')
        );
    }

    /**
     * Crea un backup dei dati correnti
     */
    createBackup() {
        try {
            const currentData = localStorage.getItem(this.storageKey);
            if (currentData) {
                const backupData = {
                    data: currentData,
                    timestamp: new Date().toISOString(),
                    version: this.currentVersion
                };
                localStorage.setItem(this.backupKey, JSON.stringify(backupData));
                console.log('Backup creato con successo');
            }
        } catch (error) {
            console.error('Errore nella creazione del backup:', error);
        }
    }

    /**
     * Ripristina i dati dal backup
     * @returns {Object}
     */
    restoreFromBackup() {
        try {
            const backup = localStorage.getItem(this.backupKey);
            
            if (!backup) {
                console.warn('Nessun backup disponibile');
                return this.getDefaultData();
            }

            const backupData = JSON.parse(backup);
            const restoredData = JSON.parse(backupData.data);
            
            if (this.validateData(restoredData)) {
                console.log('Dati ripristinati dal backup');
                return {
                    tasks: restoredData.tasks,
                    success: true,
                    source: 'backup',
                    restored: true,
                    backupTimestamp: backupData.timestamp
                };
            }
        } catch (error) {
            console.error('Errore nel ripristino dal backup:', error);
        }
        
        return this.getDefaultData();
    }

    /**
     * Gestisce il superamento della quota di storage
     * @returns {Object}
     */
    handleQuotaExceeded() {
        try {
            // Tenta di liberare spazio rimuovendo dati vecchi
            this.cleanupOldData();
            
            // Ritenta il salvataggio
            return { 
                success: false, 
                message: 'Quota storage superata. Pulire i dati vecchi e riprovare.',
                action: 'quota_exceeded'
            };
        } catch (error) {
            return { 
                success: false, 
                message: 'Impossibile salvare: storage pieno',
                action: 'storage_full'
            };
        }
    }

    /**
     * Pulisce i dati vecchi per liberare spazio
     */
    cleanupOldData() {
        try {
            // Rimuovi backup vecchi
            const keys = Object.keys(localStorage);
            keys.forEach(key => {
                if (key.startsWith('taskManager_') && key !== this.storageKey && key !== this.backupKey) {
                    localStorage.removeItem(key);
                }
            });
        } catch (error) {
            console.error('Errore nella pulizia dei dati:', error);
        }
    }

    /**
     * Esporta i dati in formato JSON
     * @returns {string}
     */
    exportData() {
        try {
            const data = this.loadTasks();
            
            const exportData = {
                tasks: data.tasks,
                exportDate: new Date().toISOString(),
                version: this.currentVersion,
                metadata: {
                    totalTasks: data.tasks.length,
                    categories: [...new Set(data.tasks.map(t => t.category))]
                }
            };
            
            return JSON.stringify(exportData, null, 2);
        } catch (error) {
            console.error('Errore nell\'esportazione:', error);
            throw new Error('Impossibile esportare i dati');
        }
    }

    /**
     * Importa i dati da JSON
     * @param {string} jsonData - Dati in formato JSON
     * @returns {Object}
     */
    importData(jsonData) {
        try {
            const data = JSON.parse(jsonData);
            
            if (!this.validateImportData(data)) {
                throw new Error('Formato dati non valido');
            }
            
            // Crea backup prima dell'importazione
            this.createBackup();
            
            const result = this.saveTasks(data.tasks, { createBackup: false });
            
            return {
                ...result,
                imported: data.tasks.length,
                message: `${data.tasks.length} task importate con successo`
            };
        } catch (error) {
            return {
                success: false,
                message: `Errore nell'importazione: ${error.message}`
            };
        }
    }

    /**
     * Valida i dati di importazione
     * @param {Object} data - Dati da validare
     * @returns {boolean}
     */
    validateImportData(data) {
        return data && 
               Array.isArray(data.tasks) && 
               data.tasks.every(task => 
                   task.hasOwnProperty('title') && 
                   typeof task.title === 'string'
               );
    }

    /**
     * Verifica e migra la versione dei dati
     */
    checkAndMigrateVersion() {
        const storedVersion = localStorage.getItem(this.versionKey);
        
        if (!storedVersion || storedVersion !== this.currentVersion) {
            console.log('Migrazione dati dalla versione', storedVersion, 'alla', this.currentVersion);
            this.migrateData(storedVersion);
            localStorage.setItem(this.versionKey, this.currentVersion);
        }
    }

    /**
     * Migra i dati da versioni precedenti
     * @param {string} fromVersion - Versione di partenza
     */
    migrateData(fromVersion) {
        try {
            const data = this.loadTasks();
            
            if (data.tasks) {
                // Aggiungi campi mancanti per compatibilità
                data.tasks.forEach(task => {
                    if (!task.createdAt) {
                        task.createdAt = new Date().toISOString();
                    }
                    if (!task.category) {
                        task.category = 'Generale';
                    }
                    if (!task.priority) {
                        task.priority = 'media';
                    }
                });
                
                this.saveTasks(data.tasks, { createBackup: false });
                console.log('Migrazione completata');
            }
        } catch (error) {
            console.error('Errore nella migrazione:', error);
        }
    }

    /**
     * Restituisce la struttura dati di default
     * @returns {Object}
     */
    getDefaultData() {
        return {
            tasks: [],
            success: true,
            source: 'default',
            message: 'Caricati dati di default'
        };
    }

    /**
     * Cancella tutti i dati
     * @returns {Object}
     */
    clearAllData() {
        try {
            if (this.isMemoryMode) {
                this.memoryStorage.tasks = [];
                return { success: true, message: 'Dati in memoria cancellati' };
            }
            
            // Crea backup finale prima della cancellazione
            this.createBackup();
            
            localStorage.removeItem(this.storageKey);
            
            return { 
                success: true, 
                message: 'Tutti i dati sono stati cancellati. Backup conservato.' 
            };
        } catch (error) {
            return { 
                success: false, 
                message: `Errore nella cancellazione: ${error.message}` 
            };
        }
    }

    /**
     * Ottiene informazioni sullo storage
     * @returns {Object}
     */
    getStorageInfo() {
        const info = {
            isMemoryMode: this.isMemoryMode,
            version: this.currentVersion,
            hasBackup: false,
            storageUsed: 0,
            storageAvailable: this.isLocalStorageAvailable()
        };

        try {
            if (!this.isMemoryMode) {
                info.hasBackup = !!localStorage.getItem(this.backupKey);
                
                // Calcola spazio utilizzato (approssimativo)
                let used = 0;
                for (let key in localStorage) {
                    if (localStorage.hasOwnProperty(key)) {
                        used += localStorage[key].length;
                    }
                }
                info.storageUsed = Math.round(used / 1024); // KB
            }
        } catch (error) {
            console.error('Errore nel calcolo info storage:', error);
        }

        return info;
    }
}

// Esporta la classe per l'uso in altri moduli
if (typeof module !== 'undefined' && module.exports) {
    module.exports = StorageManager;
}
