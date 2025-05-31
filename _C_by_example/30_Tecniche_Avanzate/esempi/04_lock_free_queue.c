/**
 * File: 04_lock_free_queue.c
 * Descrizione: Esempio di implementazione di una coda lock-free in C
 * 
 * Questo esempio dimostra come implementare una struttura dati concorrente
 * senza l'utilizzo di mutex o altre primitive di sincronizzazione tradizionali,
 * utilizzando invece operazioni atomiche per garantire la correttezza in ambiente multi-thread.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Definizione della struttura del nodo della coda
 */
typedef struct Node {
    int value;                // Valore memorizzato nel nodo
    _Atomic(struct Node*) next; // Puntatore atomico al prossimo nodo
} Node;

/**
 * Definizione della struttura della coda lock-free
 */
typedef struct {
    _Atomic(Node*) head;     // Puntatore atomico alla testa della coda
    _Atomic(Node*) tail;     // Puntatore atomico alla coda della coda
} LockFreeQueue;

/**
 * Inizializza una nuova coda lock-free
 */
void queue_init(LockFreeQueue* queue) {
    // Crea un nodo fittizio (dummy) che sarà sempre presente nella coda
    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = NULL;
    
    // Inizializza head e tail con il nodo dummy
    atomic_store(&queue->head, dummy);
    atomic_store(&queue->tail, dummy);
}

/**
 * Inserisce un nuovo valore nella coda
 * @param queue Puntatore alla coda
 * @param value Valore da inserire
 * @return true se l'inserimento ha successo, false altrimenti
 */
bool queue_enqueue(LockFreeQueue* queue, int value) {
    // Crea un nuovo nodo
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return false; // Fallimento nell'allocazione
    }
    
    new_node->value = value;
    atomic_store(&new_node->next, NULL);
    
    // Inserisci il nuovo nodo alla fine della coda
    Node* tail;
    Node* next;
    while (true) {
        tail = atomic_load(&queue->tail);
        next = atomic_load(&tail->next);
        
        // Verifica che tail sia ancora valido
        if (tail == atomic_load(&queue->tail)) {
            // Se next è NULL, tail punta effettivamente all'ultimo nodo
            if (next == NULL) {
                // Prova ad aggiungere il nuovo nodo
                if (atomic_compare_exchange_weak(&tail->next, &next, new_node)) {
                    break; // Inserimento riuscito
                }
            } else {
                // Tail è rimasto indietro, aiuta ad aggiornarlo
                atomic_compare_exchange_weak(&queue->tail, &tail, next);
            }
        }
    }
    
    // Aggiorna tail per puntare al nuovo nodo
    atomic_compare_exchange_weak(&queue->tail, &tail, new_node);
    return true;
}

/**
 * Rimuove un valore dalla coda
 * @param queue Puntatore alla coda
 * @param result Puntatore dove memorizzare il valore rimosso
 * @return true se la rimozione ha successo, false se la coda è vuota
 */
bool queue_dequeue(LockFreeQueue* queue, int* result) {
    Node* head;
    Node* tail;
    Node* next;
    
    while (true) {
        head = atomic_load(&queue->head);
        tail = atomic_load(&queue->tail);
        next = atomic_load(&head->next);
        
        // Verifica che head sia ancora valido
        if (head == atomic_load(&queue->head)) {
            // Se head e tail sono uguali, la coda potrebbe essere vuota o tail è rimasto indietro
            if (head == tail) {
                // Se next è NULL, la coda è vuota
                if (next == NULL) {
                    return false;
                }
                // Tail è rimasto indietro, aiuta ad aggiornarlo
                atomic_compare_exchange_weak(&queue->tail, &tail, next);
            } else {
                // La coda non è vuota, leggi il valore prima di rimuovere il nodo
                *result = next->value;
                // Prova a rimuovere il nodo
                if (atomic_compare_exchange_weak(&queue->head, &head, next)) {
                    break; // Rimozione riuscita
                }
            }
        }
    }
    
    // Libera il nodo rimosso
    free(head);
    return true;
}

/**
 * Distrugge la coda e libera tutta la memoria
 */
void queue_destroy(LockFreeQueue* queue) {
    Node* current = atomic_load(&queue->head);
    while (current != NULL) {
        Node* next = atomic_load(&current->next);
        free(current);
        current = next;
    }
    
    atomic_store(&queue->head, NULL);
    atomic_store(&queue->tail, NULL);
}

/**
 * Struttura per i parametri del thread
 */
typedef struct {
    LockFreeQueue* queue;
    int thread_id;
    int num_operations;
} ThreadParams;

/**
 * Funzione eseguita dai thread produttori
 */
void* producer_thread(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;
    
    for (int i = 0; i < params->num_operations; i++) {
        int value = (params->thread_id * 1000) + i;
        if (queue_enqueue(params->queue, value)) {
            printf("Producer %d: inserito valore %d\n", params->thread_id, value);
        } else {
            printf("Producer %d: fallimento nell'inserimento del valore %d\n", params->thread_id, value);
        }
        
        // Piccola pausa per simulare lavoro
        usleep(rand() % 1000);
    }
    
    return NULL;
}

/**
 * Funzione eseguita dai thread consumatori
 */
void* consumer_thread(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;
    
    for (int i = 0; i < params->num_operations; i++) {
        int value;
        if (queue_dequeue(params->queue, &value)) {
            printf("Consumer %d: rimosso valore %d\n", params->thread_id, value);
        } else {
            printf("Consumer %d: coda vuota\n", params->thread_id);
            i--; // Riprova
        }
        
        // Piccola pausa per simulare lavoro
        usleep(rand() % 2000);
    }
    
    return NULL;
}

/**
 * Funzione principale
 */
int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    // Crea e inizializza la coda lock-free
    LockFreeQueue queue;
    queue_init(&queue);
    
    // Parametri del test
    const int num_producers = 3;
    const int num_consumers = 2;
    const int operations_per_thread = 5;
    
    // Crea i thread produttori e consumatori
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];
    ThreadParams producer_params[num_producers];
    ThreadParams consumer_params[num_consumers];
    
    printf("Avvio test della coda lock-free con %d produttori e %d consumatori\n\n", 
           num_producers, num_consumers);
    
    // Avvia i thread produttori
    for (int i = 0; i < num_producers; i++) {
        producer_params[i].queue = &queue;
        producer_params[i].thread_id = i + 1;
        producer_params[i].num_operations = operations_per_thread;
        
        pthread_create(&producers[i], NULL, producer_thread, &producer_params[i]);
    }
    
    // Avvia i thread consumatori
    for (int i = 0; i < num_consumers; i++) {
        consumer_params[i].queue = &queue;
        consumer_params[i].thread_id = i + 1;
        consumer_params[i].num_operations = operations_per_thread * num_producers / num_consumers;
        
        pthread_create(&consumers[i], NULL, consumer_thread, &consumer_params[i]);
    }
    
    // Attendi il completamento di tutti i thread
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Distruggi la coda
    queue_destroy(&queue);
    
    printf("\nTest completato con successo!\n");
    printf("\nNota: Questa implementazione utilizza operazioni atomiche per garantire\n");
    printf("la correttezza in ambiente multi-thread senza l'uso di mutex o altre\n");
    printf("primitive di sincronizzazione tradizionali. Questo approccio può offrire\n");
    printf("prestazioni migliori in scenari con alta contesa, ma richiede una\n");
    printf("comprensione approfondita del modello di memoria e delle operazioni atomiche.\n");
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall -std=c11 -pthread 04_lock_free_queue.c -o 04_lock_free_queue
 * ./04_lock_free_queue
 * 
 * Nota: Questo esempio richiede un compilatore che supporti C11 con le estensioni
 * atomiche e la libreria pthread per la gestione dei thread.
 */