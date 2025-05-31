/**
 * Applicazione Task Manager
 * File principale che inizializza l'applicazione
 * 
 * @file app.js
 * @author Git Course Team
 * @version 1.0.0
 */

// Variabili globali per l'applicazione
let taskManager;
let storageManager;
let ui;

/**
 * Inizializza l'applicazione
 */
function initializeApp() {
    try {
        console.log('🚀 Inizializzazione Task Manager...');
        
        // Verifica che il DOM sia completamente caricato
        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', initializeApp);
            return;
        }

        // Inizializza i componenti principali
        storageManager = new StorageManager();
        taskManager = new TaskManager(storageManager);
        ui = new UIManager(taskManager);

        // Carica i dati salvati
        loadInitialData();

        // Configura service worker se disponibile
        registerServiceWorker();

        // Setup per la gestione degli errori globali
        setupErrorHandling();

        // Setup per la gestione della connettività
        setupNetworkHandling();

        // Setup per l'auto-save
        setupAutoSave();

        console.log('✅ Task Manager inizializzato con successo');
        
        // Mostra notifica di benvenuto
        setTimeout(() => {
            ui.showNotification('Task Manager caricato con successo!', 'success');
        }, 500);

    } catch (error) {
        console.error('❌ Errore durante l\'inizializzazione:', error);
        showFallbackError('Errore durante l\'inizializzazione dell\'applicazione');
    }
}

/**
 * Carica i dati iniziali
 */
function loadInitialData() {
    try {
        console.log('📊 Caricamento dati iniziali...');
        
        const loadResult = taskManager.loadTasks();
        
        if (loadResult.success) {
            console.log(`✅ Caricati ${loadResult.tasks?.length || 0} task`);
            
            // Mostra informazioni sul caricamento
            if (loadResult.source === 'backup') {
                ui.showNotification('Dati ripristinati dal backup', 'warning');
            } else if (loadResult.source === 'default') {
                ui.showNotification('Benvenuto! Inizia aggiungendo la tua prima task', 'info');
            }
        } else {
            console.warn('⚠️ Problemi nel caricamento dati:', loadResult.message);
            ui.showNotification('Problemi nel caricamento dei dati', 'warning');
        }

        // Aggiorna l'interfaccia
        ui.refreshUI();
        
    } catch (error) {
        console.error('❌ Errore nel caricamento dati:', error);
        ui.showNotification('Errore nel caricamento dei dati', 'error');
    }
}

/**
 * Registra il service worker per il supporto offline
 */
function registerServiceWorker() {
    if ('serviceWorker' in navigator) {
        window.addEventListener('load', () => {
            navigator.serviceWorker.register('/sw.js')
                .then(registration => {
                    console.log('✅ Service Worker registrato:', registration.scope);
                })
                .catch(error => {
                    console.log('❌ Registrazione Service Worker fallita:', error);
                });
        });
    }
}

/**
 * Configura la gestione degli errori globali
 */
function setupErrorHandling() {
    // Gestione errori JavaScript non catturati
    window.addEventListener('error', (event) => {
        console.error('❌ Errore JavaScript:', event.error);
        ui?.showNotification('Si è verificato un errore nell\'applicazione', 'error');
        
        // Invio errore a servizio di monitoring (esempio)
        reportError(event.error, 'javascript_error');
    });

    // Gestione promise rejections non catturate
    window.addEventListener('unhandledrejection', (event) => {
        console.error('❌ Promise rejection non gestita:', event.reason);
        ui?.showNotification('Errore nell\'elaborazione dei dati', 'error');
        
        reportError(event.reason, 'promise_rejection');
        event.preventDefault(); // Previene la stampa della rejection nella console
    });
}

/**
 * Configura la gestione della connettività di rete
 */
function setupNetworkHandling() {
    // Gestione stato online/offline
    window.addEventListener('online', () => {
        console.log('🌐 Connessione ristabilita');
        ui?.showNotification('Connessione ristabilita', 'success');
        document.body.classList.remove('offline');
    });

    window.addEventListener('offline', () => {
        console.log('📵 Connessione persa');
        ui?.showNotification('Modalità offline attiva', 'warning');
        document.body.classList.add('offline');
    });

    // Stato iniziale
    if (!navigator.onLine) {
        document.body.classList.add('offline');
    }
}

/**
 * Configura l'auto-save
 */
function setupAutoSave() {
    let autoSaveInterval;
    
    // Auto-save ogni 30 secondi se ci sono modifiche
    const startAutoSave = () => {
        autoSaveInterval = setInterval(() => {
            if (taskManager?.hasUnsavedChanges()) {
                console.log('💾 Auto-save in corso...');
                const result = taskManager.saveTasks();
                
                if (result.success) {
                    console.log('✅ Auto-save completato');
                } else {
                    console.warn('⚠️ Auto-save fallito:', result.message);
                }
            }
        }, 30000); // 30 secondi
    };

    // Salva quando l'utente lascia la pagina
    window.addEventListener('beforeunload', (event) => {
        if (taskManager?.hasUnsavedChanges()) {
            const result = taskManager.saveTasks();
            
            if (!result.success) {
                event.preventDefault();
                event.returnValue = 'Ci sono modifiche non salvate. Vuoi davvero uscire?';
                return event.returnValue;
            }
        }
    });

    // Salva quando la pagina diventa invisibile (cambio tab, minimizzazione)
    document.addEventListener('visibilitychange', () => {
        if (document.hidden && taskManager?.hasUnsavedChanges()) {
            taskManager.saveTasks();
        }
    });

    // Avvia auto-save
    startAutoSave();

    // Esponi la funzione per fermare l'auto-save se necessario
    window.stopAutoSave = () => {
        if (autoSaveInterval) {
            clearInterval(autoSaveInterval);
            autoSaveInterval = null;
        }
    };
}

/**
 * Invia errore a servizio di monitoring
 * @param {Error} error - Errore da reportare
 * @param {string} type - Tipo di errore
 */
function reportError(error, type) {
    try {
        // Esempio di implementazione per servizio di monitoring
        const errorReport = {
            message: error.message || 'Unknown error',
            stack: error.stack || 'No stack trace',
            type: type,
            url: window.location.href,
            userAgent: navigator.userAgent,
            timestamp: new Date().toISOString()
        };

        // In un'applicazione reale, questo verrebbe inviato a un servizio esterno
        console.log('📊 Error Report:', errorReport);
        
        // Salva localmente per debugging
        localStorage.setItem('lastError', JSON.stringify(errorReport));
        
    } catch (reportingError) {
        console.error('❌ Errore nel reporting:', reportingError);
    }
}

/**
 * Mostra errore di fallback quando l'UI non è disponibile
 * @param {string} message - Messaggio di errore
 */
function showFallbackError(message) {
    // Crea elemento di notifica di base se l'UI non è disponibile
    const errorDiv = document.createElement('div');
    errorDiv.className = 'fallback-error';
    errorDiv.style.cssText = `
        position: fixed;
        top: 20px;
        right: 20px;
        background: #f44336;
        color: white;
        padding: 16px;
        border-radius: 4px;
        box-shadow: 0 2px 8px rgba(0,0,0,0.2);
        z-index: 10000;
        max-width: 300px;
    `;
    errorDiv.innerHTML = `
        <strong>Errore:</strong> ${message}
        <button onclick="this.parentElement.remove()" style="
            background: none;
            border: none;
            color: white;
            float: right;
            cursor: pointer;
            font-size: 18px;
            line-height: 1;
        ">×</button>
    `;
    
    document.body.appendChild(errorDiv);
    
    // Rimuovi automaticamente dopo 10 secondi
    setTimeout(() => {
        if (errorDiv.parentElement) {
            errorDiv.remove();
        }
    }, 10000);
}

/**
 * Funzioni utili per il debugging
 */
window.debug = {
    /**
     * Mostra informazioni sull'applicazione
     */
    info() {
        console.log('📱 Task Manager Debug Info:', {
            version: '1.0.0',
            tasks: taskManager?.getAllTasks()?.length || 0,
            storage: storageManager?.getStorageInfo() || null,
            theme: document.documentElement.getAttribute('data-theme'),
            online: navigator.onLine
        });
    },

    /**
     * Esporta i dati per debugging
     */
    export() {
        try {
            const data = taskManager?.exportTasks();
            console.log('📤 Export Data:', data);
            return data;
        } catch (error) {
            console.error('❌ Errore export debug:', error);
        }
    },

    /**
     * Simula un errore per testare la gestione
     */
    simulateError() {
        throw new Error('Errore simulato per testing');
    },

    /**
     * Cancella tutti i dati (attenzione!)
     */
    clearAll() {
        if (confirm('⚠️ Cancellare TUTTI i dati? Questa azione non può essere annullata!')) {
            localStorage.clear();
            location.reload();
        }
    },

    /**
     * Aggiunge task di esempio per testing
     */
    addSampleTasks() {
        const sampleTasks = [
            {
                title: 'Completare documentazione progetto',
                category: 'Lavoro',
                priority: 'alta',
                dueDate: new Date(Date.now() + 86400000).toISOString().split('T')[0], // domani
                description: 'Scrivere la documentazione tecnica completa'
            },
            {
                title: 'Fare la spesa',
                category: 'Personale',
                priority: 'media',
                description: 'Comprare ingredienti per la cena'
            },
            {
                title: 'Studiare Git avanzato',
                category: 'Studio',
                priority: 'bassa',
                description: 'Rivedere i concetti di merge e rebase'
            }
        ];

        sampleTasks.forEach(task => {
            taskManager?.addTask(task);
        });

        ui?.refreshUI();
        console.log('✅ Task di esempio aggiunte');
    }
};

/**
 * Keyboard shortcuts globali
 */
document.addEventListener('keydown', (e) => {
    // Ctrl/Cmd + Shift + D: Debug info
    if ((e.ctrlKey || e.metaKey) && e.shiftKey && e.key === 'D') {
        e.preventDefault();
        window.debug.info();
    }
    
    // Ctrl/Cmd + Shift + R: Ricarica applicazione
    if ((e.ctrlKey || e.metaKey) && e.shiftKey && e.key === 'R') {
        e.preventDefault();
        if (confirm('Ricaricare l\'applicazione?')) {
            location.reload();
        }
    }
});

/**
 * Gestione installazione PWA
 */
let deferredPrompt;

window.addEventListener('beforeinstallprompt', (e) => {
    // Previeni il prompt automatico
    e.preventDefault();
    deferredPrompt = e;
    
    // Mostra notifica per installazione
    ui?.showNotification('App disponibile per l\'installazione! Controlla il menu.', 'info');
});

/**
 * Funzione per installare l'app come PWA
 */
window.installApp = async () => {
    if (!deferredPrompt) {
        ui?.showNotification('Installazione non disponibile', 'warning');
        return;
    }

    try {
        const result = await deferredPrompt.prompt();
        console.log('📱 Risultato installazione:', result.outcome);
        
        if (result.outcome === 'accepted') {
            ui?.showNotification('App installata con successo!', 'success');
        } else {
            ui?.showNotification('Installazione annullata', 'info');
        }
        
        deferredPrompt = null;
    } catch (error) {
        console.error('❌ Errore installazione:', error);
        ui?.showNotification('Errore durante l\'installazione', 'error');
    }
};

// Avvia l'applicazione
initializeApp();

// Esponi funzioni globali per l'uso negli event handler HTML
window.ui = ui;
window.taskManager = taskManager;
window.storageManager = storageManager;
