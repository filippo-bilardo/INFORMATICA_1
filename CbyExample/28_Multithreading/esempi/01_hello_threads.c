/**
 * Esempio 01: Hello Threads
 * 
 * Questo esempio mostra come creare e gestire thread in C utilizzando la libreria pthread.
 * Il programma crea più thread che stampano messaggi personalizzati.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // Per la funzione sleep

// Struttura per passare dati al thread
typedef struct {
    int thread_id;
    char* message;
    int sleep_time;
} ThreadData;

// Funzione eseguita da ciascun thread
void* print_message(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    // Simula un'elaborazione
    sleep(data->sleep_time);
    
    // Stampa il messaggio con l'ID del thread
    printf("Thread %d: %s\n", data->thread_id, data->message);
    
    // Libera la memoria allocata per i dati del thread
    free(data);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];  // Array di 5 thread
    int rc;
    
    printf("Programma principale: creazione dei thread\n");
    
    // Crea 5 thread
    for(int i = 0; i < 5; i++) {
        printf("Creazione del thread %d\n", i);
        
        // Alloca memoria per i dati del thread
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        if (data == NULL) {
            fprintf(stderr, "Errore nell'allocazione della memoria\n");
            exit(EXIT_FAILURE);
        }
        
        // Inizializza i dati del thread
        data->thread_id = i;
        data->message = "Ciao dal thread!";
        data->sleep_time = i + 1;  // Tempo di sleep variabile
        
        // Crea il thread
        rc = pthread_create(&threads[i], NULL, print_message, (void*)data);
        
        if (rc) {
            fprintf(stderr, "Errore nella creazione del thread %d: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Programma principale: attesa della terminazione dei thread\n");
    
    // Attende la terminazione di tutti i thread
    for(int i = 0; i < 5; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            fprintf(stderr, "Errore nell'attesa del thread %d: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
        printf("Thread %d terminato\n", i);
    }
    
    printf("Programma principale: tutti i thread sono terminati\n");
    
    return 0;
}

/**
 * Compilazione ed esecuzione:
 * 
 * Su sistemi Linux/Unix:
 *   gcc -o hello_threads 01_hello_threads.c -lpthread
 *   ./hello_threads
 * 
 * Su Windows con MinGW:
 *   gcc -o hello_threads 01_hello_threads.c -lpthread
 *   hello_threads.exe
 * 
 * Note:
 * - L'ordine di esecuzione dei thread non è deterministico
 * - I thread terminano in ordine diverso a causa dei diversi tempi di sleep
 * - Il programma principale attende che tutti i thread terminino prima di concludersi
 */