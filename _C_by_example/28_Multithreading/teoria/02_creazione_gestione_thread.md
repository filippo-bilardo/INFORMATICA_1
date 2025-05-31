# Creazione e Gestione dei Thread in C

## Introduzione

La creazione e la gestione dei thread sono operazioni fondamentali nella programmazione multi-thread. In questo documento, esploreremo come creare, gestire e terminare i thread in C utilizzando le librerie standard.

## Creazione di Thread con POSIX Threads (pthread)

La libreria pthread è lo standard de facto per la programmazione multi-thread in ambienti UNIX/Linux, ma è disponibile anche su Windows attraverso librerie di compatibilità.

### Funzione pthread_create

```c
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
```

Parametri:
- `thread`: puntatore a una variabile di tipo `pthread_t` che conterrà l'ID del thread creato
- `attr`: attributi del thread (NULL per attributi predefiniti)
- `start_routine`: funzione che il thread eseguirà
- `arg`: argomento passato alla funzione del thread

### Esempio di Creazione di Thread

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* print_message(void* arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char* message1 = "Thread 1";
    char* message2 = "Thread 2";
    int ret;

    ret = pthread_create(&thread1, NULL, print_message, (void*)message1);
    if (ret) {
        printf("Errore nella creazione del thread: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&thread2, NULL, print_message, (void*)message2);
    if (ret) {
        printf("Errore nella creazione del thread: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    // Attendere che i thread terminino
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Tutti i thread hanno terminato\n");
    return 0;
}
```

## Attributi dei Thread

Gli attributi dei thread permettono di personalizzare il comportamento dei thread creati.

```c
pthread_attr_t attr;
pthread_attr_init(&attr);  // Inizializzazione degli attributi

// Impostazione degli attributi
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

// Creazione del thread con attributi personalizzati
pthread_create(&thread_id, &attr, thread_function, arg);

// Liberazione delle risorse degli attributi
pthread_attr_destroy(&attr);
```

Attributi comuni:
- `PTHREAD_CREATE_JOINABLE`: il thread può essere "joined" (default)
- `PTHREAD_CREATE_DETACHED`: il thread non può essere "joined"

## Attesa di Terminazione (Joining)

La funzione `pthread_join` permette di attendere la terminazione di un thread.

```c
int pthread_join(pthread_t thread, void **retval);
```

Parametri:
- `thread`: ID del thread da attendere
- `retval`: puntatore dove verrà memorizzato il valore di ritorno del thread

## Thread Detached

I thread "detached" liberano automaticamente le loro risorse quando terminano, senza necessità di essere "joined".

```c
pthread_detach(thread_id);
```

## Terminazione di un Thread

Un thread può terminare in diversi modi:

1. **Ritorno dalla funzione del thread**:
   ```c
   void* thread_function(void* arg) {
       // Codice del thread
       return result;  // Terminazione con valore di ritorno
   }
   ```

2. **Chiamata a pthread_exit**:
   ```c
   void pthread_exit(void *retval);
   ```
   Questa funzione termina il thread chiamante e restituisce il valore `retval`.

3. **Cancellazione del thread**:
   ```c
   int pthread_cancel(pthread_t thread);
   ```
   Questa funzione richiede la terminazione del thread specificato.

## Gestione della Cancellazione

Un thread può controllare come risponde alle richieste di cancellazione:

```c
// Impostazione dello stato di cancellazione
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);  // Default
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

// Impostazione del tipo di cancellazione
pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);  // Default
pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

// Punto di cancellazione esplicito
pthread_testcancel();
```

## Identificazione dei Thread

Ogni thread ha un identificatore unico:

```c
pthread_t pthread_self(void);  // Ottiene l'ID del thread corrente

// Confronto di ID di thread
int pthread_equal(pthread_t t1, pthread_t t2);
```

## Creazione di Thread con Windows API

Su sistemi Windows, si utilizza l'API nativa:

```c
#include <windows.h>

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    // Codice del thread
    return 0;
}

int main() {
    HANDLE hThread;
    DWORD threadId;
    
    hThread = CreateThread(
        NULL,                   // Attributi di sicurezza
        0,                      // Dimensione dello stack
        ThreadFunction,         // Funzione del thread
        NULL,                   // Parametro della funzione
        0,                      // Flag di creazione
        &threadId);             // ID del thread
    
    if (hThread == NULL) {
        printf("Errore nella creazione del thread\n");
        return 1;
    }
    
    // Attesa della terminazione del thread
    WaitForSingleObject(hThread, INFINITE);
    
    // Chiusura dell'handle del thread
    CloseHandle(hThread);
    
    return 0;
}
```

## Best Practices

1. **Gestione degli errori**: Controllare sempre i valori di ritorno delle funzioni di thread.
2. **Liberazione delle risorse**: Assicurarsi che tutti i thread vengano correttamente terminati e le loro risorse liberate.
3. **Limitare il numero di thread**: Creare troppi thread può degradare le prestazioni.
4. **Thread pool**: Considerare l'uso di pool di thread per gestire efficacemente le risorse.
5. **Evitare la terminazione forzata**: Preferire meccanismi di terminazione cooperativa.

## Esercizi di Autovalutazione

1. Scrivi un programma che crea 5 thread, ognuno dei quali stampa il proprio numero identificativo.
2. Modifica il programma precedente per far sì che ogni thread restituisca come valore di ritorno il quadrato del proprio numero identificativo.
3. Implementa un semplice thread pool che gestisce un numero fisso di thread per eseguire attività dalla coda.
4. Scrivi un programma che dimostra l'uso di thread detached.
5. Implementa un meccanismo di terminazione sicura per i thread in risposta a un segnale esterno.