# Tecniche Avanzate di Gestione degli Errori in C

## Introduzione

Oltre alle tecniche di base e all'utilizzo di `errno`, esistono approcci più avanzati per la gestione degli errori in C. Queste tecniche permettono di implementare sistemi di gestione degli errori più sofisticati, simili ai meccanismi di eccezioni presenti in altri linguaggi. In questa guida, esploreremo alcune di queste tecniche avanzate.

## Simulazione delle Eccezioni con setjmp/longjmp

Il C non supporta nativamente le eccezioni come altri linguaggi (C++, Java, Python), ma è possibile simulare un comportamento simile utilizzando le funzioni `setjmp()` e `longjmp()` definite nell'header `<setjmp.h>`.

### Funzionamento di setjmp/longjmp

- `setjmp()` salva lo stato corrente del programma in un buffer (`jmp_buf`) e restituisce 0.
- `longjmp()` ripristina lo stato salvato da `setjmp()` e fa sì che `setjmp()` restituisca un valore diverso da 0 (specificato come parametro di `longjmp()`).

```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;  // Buffer per salvare lo stato del programma

void function_that_throws() {
    printf("Sto per lanciare un'eccezione...\n");
    longjmp(env, 1);  // Salta indietro a setjmp con valore di ritorno 1
    printf("Questo codice non verrà mai eseguito\n");
}

int main() {
    int ret_val = setjmp(env);
    
    if (ret_val == 0) {
        // Prima chiamata a setjmp
        printf("Stato salvato, valore di ritorno: %d\n", ret_val);
        function_that_throws();
    } else {
        // Ritorno da longjmp
        printf("Eccezione catturata, valore di ritorno: %d\n", ret_val);
    }
    
    return 0;
}
```

### Implementazione di un Sistema di Eccezioni

È possibile implementare un sistema di eccezioni più completo utilizzando `setjmp`/`longjmp` insieme a strutture dati per gestire diversi tipi di eccezioni:

```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

// Definizione dei tipi di eccezioni
#define EX_INVALID_ARGUMENT 1
#define EX_OUT_OF_MEMORY 2
#define EX_DIVISION_BY_ZERO 3
#define EX_FILE_ERROR 4

// Struttura per le informazioni sull'eccezione
typedef struct {
    int type;
    char message[256];
} Exception;

// Variabili globali per la gestione delle eccezioni
jmp_buf exception_env;
Exception current_exception;

// Funzione per lanciare un'eccezione
void throw_exception(int type, const char *message) {
    current_exception.type = type;
    strncpy(current_exception.message, message, sizeof(current_exception.message) - 1);
    current_exception.message[sizeof(current_exception.message) - 1] = '\0';
    longjmp(exception_env, type);
}

// Funzione che può generare un'eccezione
int divide(int a, int b) {
    if (b == 0) {
        throw_exception(EX_DIVISION_BY_ZERO, "Tentativo di divisione per zero");
    }
    return a / b;
}

// Funzione per allocare memoria con gestione delle eccezioni
void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        throw_exception(EX_OUT_OF_MEMORY, "Memoria insufficiente");
    }
    return ptr;
}

int main() {
    int result;
    int exception_type = setjmp(exception_env);
    
    if (exception_type == 0) {
        // Codice normale (nessuna eccezione)
        printf("Esecuzione del codice normale...\n");
        
        // Allocazione di memoria
        int *array = (int*)safe_malloc(10 * sizeof(int));
        
        // Divisione che può generare un'eccezione
        result = divide(10, 0);
        
        printf("Risultato: %d\n", result);  // Questo non verrà eseguito
        
        free(array);
    } else {
        // Gestione delle eccezioni
        printf("Eccezione catturata (tipo %d): %s\n", exception_type, current_exception.message);
        
        switch (exception_type) {
            case EX_INVALID_ARGUMENT:
                printf("Azione: Verificare gli argomenti di input\n");
                break;
                
            case EX_OUT_OF_MEMORY:
                printf("Azione: Liberare memoria o ridurre l'utilizzo\n");
                break;
                
            case EX_DIVISION_BY_ZERO:
                printf("Azione: Verificare i divisori prima della divisione\n");
                break;
                
            case EX_FILE_ERROR:
                printf("Azione: Verificare i permessi e l'esistenza dei file\n");
                break;
                
            default:
                printf("Azione: Eccezione sconosciuta, terminazione del programma\n");
                exit(1);
        }
    }
    
    return 0;
}
```

### Limitazioni di setjmp/longjmp

1. **Pulizia delle risorse**: `longjmp()` non chiama i distruttori o esegue altre operazioni di pulizia, quindi è necessario gestire manualmente il rilascio delle risorse.

2. **Ambito limitato**: `setjmp()` e `longjmp()` devono essere utilizzati all'interno dello stesso stack frame o in funzioni chiamate dallo stack frame in cui è stato chiamato `setjmp()`.

3. **Variabili locali**: Le variabili locali non dichiarate come `volatile` potrebbero avere valori imprevedibili dopo un `longjmp()`.

4. **Complessità**: L'utilizzo di `setjmp()`/`longjmp()` può rendere il flusso del programma difficile da seguire e debuggare.

## Gestione degli Errori con Callback

Un approccio alternativo è l'utilizzo di funzioni di callback per la gestione degli errori. Questo permette di personalizzare il comportamento in caso di errore senza modificare il codice delle funzioni che possono generare errori.

```c
#include <stdio.h>
#include <stdlib.h>

// Definizione del tipo di callback per la gestione degli errori
typedef void (*ErrorHandler)(int error_code, const char *message, void *user_data);

// Struttura per il contesto di gestione degli errori
typedef struct {
    ErrorHandler handler;
    void *user_data;
} ErrorContext;

// Funzione per impostare il gestore degli errori
ErrorContext *set_error_handler(ErrorHandler handler, void *user_data) {
    ErrorContext *context = (ErrorContext*)malloc(sizeof(ErrorContext));
    if (context == NULL) {
        return NULL;
    }
    
    context->handler = handler;
    context->user_data = user_data;
    
    return context;
}

// Funzione per segnalare un errore
void report_error(ErrorContext *context, int error_code, const char *message) {
    if (context != NULL && context->handler != NULL) {
        context->handler(error_code, message, context->user_data);
    }
}

// Esempio di gestore degli errori
void my_error_handler(int error_code, const char *message, void *user_data) {
    FILE *log_file = (FILE*)user_data;
    
    if (log_file != NULL) {
        fprintf(log_file, "Errore %d: %s\n", error_code, message);
    }
    
    fprintf(stderr, "Errore %d: %s\n", error_code, message);
}

// Funzione che può generare errori
int process_data(ErrorContext *error_context, const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        report_error(error_context, 1, "Impossibile aprire il file");
        return -1;
    }
    
    // Elaborazione del file...
    
    fclose(file);
    return 0;
}

int main() {
    // Apre un file di log
    FILE *log_file = fopen("errors.log", "w");
    
    // Imposta il gestore degli errori
    ErrorContext *error_context = set_error_handler(my_error_handler, log_file);
    
    // Chiama una funzione che può generare errori
    process_data(error_context, "file_inesistente.txt");
    
    // Pulizia
    if (log_file != NULL) {
        fclose(log_file);
    }
    
    free(error_context);
    
    return 0;
}
```

## Gestione degli Errori con Codici di Ritorno Estesi

Un approccio più strutturato rispetto ai semplici codici di ritorno è l'utilizzo di codici di ritorno estesi, che forniscono informazioni più dettagliate sugli errori.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione della struttura per i codici di ritorno estesi
typedef struct {
    int code;               // Codice di errore
    char message[256];      // Messaggio di errore
    const char *file;       // File in cui si è verificato l'errore
    int line;               // Linea in cui si è verificato l'errore
    const char *function;   // Funzione in cui si è verificato l'errore
} ErrorInfo;

// Macro per segnalare un errore
#define REPORT_ERROR(info, err_code, msg) \
    do { \
        (info)->code = (err_code); \
        strncpy((info)->message, (msg), sizeof((info)->message) - 1); \
        (info)->message[sizeof((info)->message) - 1] = '\0'; \
        (info)->file = __FILE__; \
        (info)->line = __LINE__; \
        (info)->function = __func__; \
        return (err_code); \
    } while (0)

// Funzione che può generare errori
int divide_with_info(int a, int b, int *result, ErrorInfo *error_info) {
    if (error_info == NULL) {
        return -1;  // Errore: error_info non valido
    }
    
    if (b == 0) {
        REPORT_ERROR(error_info, 1, "Divisione per zero");
    }
    
    *result = a / b;
    return 0;  // Successo
}

// Funzione per stampare le informazioni sull'errore
void print_error(const ErrorInfo *error_info) {
    if (error_info == NULL) {
        return;
    }
    
    printf("Errore %d: %s\n", error_info->code, error_info->message);
    printf("  In %s:%d (%s)\n", error_info->file, error_info->line, error_info->function);
}

int main() {
    int a = 10, b = 0, result;
    ErrorInfo error_info = {0};
    
    int ret = divide_with_info(a, b, &result, &error_info);
    
    if (ret != 0) {
        print_error(&error_info);
        return 1;
    }
    
    printf("Risultato: %d\n", result);
    return 0;
}
```

## Gestione degli Errori con Assertion

Le asserzioni sono utili durante lo sviluppo, ma possono essere disabilitate nelle versioni di rilascio. È possibile implementare un sistema di asserzioni personalizzato che rimanga attivo anche nelle versioni di rilascio e fornisca informazioni dettagliate sugli errori.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Funzione di gestione delle asserzioni fallite
void assertion_failed(const char *expression, const char *file, int line, const char *function) {
    fprintf(stderr, "Asserzione fallita: %s\n", expression);
    fprintf(stderr, "  In %s:%d (%s)\n", file, line, function);
    abort();
}

// Macro per le asserzioni
#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            assertion_failed(#expr, __FILE__, __LINE__, __func__); \
        } \
    } while (0)

// Versione che non termina il programma
#define VERIFY(expr) \
    ((expr) ? true : (fprintf(stderr, "Verifica fallita: %s\n  In %s:%d (%s)\n", \
                              #expr, __FILE__, __LINE__, __func__), false))

// Funzione di esempio
int divide(int a, int b) {
    ASSERT(b != 0);  // Termina il programma se b è zero
    return a / b;
}

int main() {
    int result;
    
    // Utilizzo di ASSERT
    result = divide(10, 2);  // OK
    printf("10 / 2 = %d\n", result);
    
    // Utilizzo di VERIFY
    if (VERIFY(5 > 10)) {
        printf("5 è maggiore di 10\n");  // Non verrà eseguito
    } else {
        printf("5 non è maggiore di 10\n");  // Verrà eseguito
    }
    
    // Questo causerà la terminazione del programma
    result = divide(10, 0);
    
    return 0;
}
```

## Best Practices

1. **Scegliere l'approccio appropriato** in base alle esigenze dell'applicazione e al contesto di utilizzo.

2. **Documentare chiaramente** il sistema di gestione degli errori utilizzato, in modo che gli utenti della libreria o del programma sappiano come gestire gli errori.

3. **Essere coerenti** nell'utilizzo delle tecniche di gestione degli errori all'interno dello stesso progetto.

4. **Considerare la pulizia delle risorse** in caso di errore, specialmente quando si utilizzano tecniche come `setjmp`/`longjmp`.

5. **Testare accuratamente** il sistema di gestione degli errori, verificando che tutti i possibili errori vengano gestiti correttamente.

## Conclusione

Le tecniche avanzate di gestione degli errori in C permettono di implementare sistemi più sofisticati e flessibili rispetto ai semplici codici di ritorno. Sebbene il C non supporti nativamente le eccezioni come altri linguaggi, è possibile simulare comportamenti simili utilizzando le funzioni `setjmp`/`longjmp` o implementando sistemi personalizzati basati su callback o codici di ritorno estesi.

La scelta della tecnica più appropriata dipende dalle esigenze specifiche dell'applicazione, dal contesto di utilizzo e dalle preferenze personali. L'importante è implementare un sistema di gestione degli errori coerente, ben documentato e testato accuratamente.

## Esercizi

1. Implementa un sistema di gestione delle eccezioni basato su `setjmp`/`longjmp` che supporti la nidificazione dei blocchi try/catch.

2. Crea una libreria di funzioni per la gestione degli errori che utilizzi callback e permetta di registrare diversi gestori per diversi tipi di errori.

3. Sviluppa un sistema di logging avanzato che registri informazioni dettagliate sugli errori, inclusi stack trace e contesto di esecuzione.