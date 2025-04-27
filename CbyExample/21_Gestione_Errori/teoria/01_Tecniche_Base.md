# Tecniche di Base per la Gestione degli Errori in C

## Introduzione

La gestione degli errori è un aspetto fondamentale della programmazione in C. Un programma robusto deve essere in grado di rilevare situazioni anomale, gestirle appropriatamente e, quando possibile, recuperare da esse. In questa guida, esploreremo le tecniche di base per la gestione degli errori in C.

## Codici di Ritorno delle Funzioni

La tecnica più comune per la gestione degli errori in C è l'utilizzo di codici di ritorno. Le funzioni restituiscono valori che indicano se l'operazione è stata completata con successo o se si è verificato un errore.

### Convenzioni Comuni

- **Funzioni che restituiscono interi**: Spesso restituiscono 0 in caso di successo e un valore diverso da zero (generalmente negativo) in caso di errore.
- **Funzioni che restituiscono puntatori**: Restituiscono NULL in caso di errore.
- **Funzioni di libreria standard**: Molte restituiscono -1 o EOF in caso di errore e impostano la variabile `errno`.

```c
#include <stdio.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;  // Errore: divisione per zero
    }
    *result = a / b;
    return 0;  // Successo
}

int main() {
    int a = 10, b = 0, result;
    
    if (divide(a, b, &result) != 0) {
        printf("Errore: divisione per zero!\n");
        return 1;
    }
    
    printf("Risultato: %d\n", result);
    return 0;
}
```

## Verifica dei Valori Restituiti

È fondamentale verificare sempre i valori restituiti dalle funzioni che possono fallire. Ignorare questi controlli può portare a comportamenti imprevedibili o crash del programma.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("dati.txt", "r");
    
    // Verifica se l'apertura del file è avvenuta con successo
    if (file == NULL) {
        printf("Errore: impossibile aprire il file!\n");
        return 1;
    }
    
    // Utilizzo del file...
    
    fclose(file);
    return 0;
}
```

## Parametri di Output per gli Errori

Un'altra tecnica comune è l'utilizzo di parametri di output per fornire informazioni dettagliate sugli errori.

```c
#include <stdio.h>
#include <string.h>

#define ERR_NONE 0
#define ERR_INVALID_INPUT 1
#define ERR_OUT_OF_RANGE 2

int calculate_square_root(double x, double *result, int *error_code) {
    *error_code = ERR_NONE;
    
    if (x < 0) {
        *error_code = ERR_INVALID_INPUT;
        return 0;
    }
    
    if (x > 1e100) {
        *error_code = ERR_OUT_OF_RANGE;
        return 0;
    }
    
    *result = sqrt(x);
    return 1;  // Successo
}

const char* get_error_message(int error_code) {
    switch (error_code) {
        case ERR_NONE:
            return "Nessun errore";
        case ERR_INVALID_INPUT:
            return "Input non valido (numero negativo)";
        case ERR_OUT_OF_RANGE:
            return "Valore fuori range";
        default:
            return "Errore sconosciuto";
    }
}

int main() {
    double x = -4.0, result;
    int error_code;
    
    if (!calculate_square_root(x, &result, &error_code)) {
        printf("Errore: %s\n", get_error_message(error_code));
        return 1;
    }
    
    printf("La radice quadrata di %.2f è %.2f\n", x, result);
    return 0;
}
```

## Gestione degli Errori con errno

La libreria standard C definisce una variabile globale `errno` (dichiarata in `<errno.h>`) che viene impostata da molte funzioni di libreria quando si verifica un errore.

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        printf("Errore (%d): %s\n", errno, strerror(errno));
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

La funzione `perror()` può essere utilizzata per stampare un messaggio di errore basato sul valore di `errno`:

```c
#include <stdio.h>
#include <errno.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        perror("Errore");  // Stampa "Errore: No such file or directory" o simile
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

## Asserzioni

Le asserzioni sono un meccanismo per verificare che determinate condizioni siano soddisfatte durante l'esecuzione del programma. Sono particolarmente utili durante lo sviluppo e il debug.

```c
#include <stdio.h>
#include <assert.h>

int divide(int a, int b) {
    assert(b != 0);  // Verifica che il divisore non sia zero
    return a / b;
}

int main() {
    int result = divide(10, 0);  // Questa asserzione fallirà
    printf("Risultato: %d\n", result);
    return 0;
}
```

Le asserzioni vengono generalmente disabilitate nelle versioni di rilascio del software utilizzando la macro `NDEBUG`.

## Gestione delle Risorse

Una parte importante della gestione degli errori è assicurarsi che le risorse (come memoria, file, connessioni di rete) vengano rilasciate correttamente anche in caso di errore.

### Approccio con Cleanup

```c
#include <stdio.h>
#include <stdlib.h>

int process_data() {
    FILE *input = NULL;
    FILE *output = NULL;
    char *buffer = NULL;
    int result = -1;  // Valore di default in caso di errore
    
    // Allocazione delle risorse
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Errore nell'apertura del file di input");
        goto cleanup;
    }
    
    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Errore nell'apertura del file di output");
        goto cleanup;
    }
    
    buffer = (char*)malloc(1024);
    if (buffer == NULL) {
        perror("Errore nell'allocazione della memoria");
        goto cleanup;
    }
    
    // Elaborazione dei dati...
    
    result = 0;  // Successo
    
    // Pulizia
cleanup:
    if (buffer) free(buffer);
    if (output) fclose(output);
    if (input) fclose(input);
    
    return result;
}

int main() {
    if (process_data() != 0) {
        printf("Si è verificato un errore durante l'elaborazione dei dati.\n");
        return 1;
    }
    
    printf("Elaborazione completata con successo.\n");
    return 0;
}
```

## Logging degli Errori

Il logging è una tecnica importante per registrare informazioni sugli errori che si verificano durante l'esecuzione del programma.

```c
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_INFO 2
#define LOG_DEBUG 3

void log_message(int level, const char *format, ...) {
    const char *level_strings[] = {
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG"
    };
    
    // Ottiene l'ora corrente
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Stampa l'intestazione del log
    fprintf(stderr, "[%s] [%s] ", time_str, level_strings[level]);
    
    // Stampa il messaggio formattato
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        log_message(LOG_ERROR, "Impossibile aprire il file: %s", strerror(errno));
        return 1;
    }
    
    log_message(LOG_INFO, "File aperto con successo");
    
    fclose(file);
    return 0;
}
```

## Best Practices

1. **Controllare sempre i valori restituiti** dalle funzioni che possono fallire.
2. **Fornire messaggi di errore chiari e informativi** che aiutino a identificare e risolvere il problema.
3. **Implementare una strategia coerente di gestione degli errori** in tutto il programma.
4. **Rilasciare sempre le risorse** in caso di errore per evitare memory leak o altre perdite di risorse.
5. **Utilizzare il logging** per registrare informazioni sugli errori che si verificano durante l'esecuzione.
6. **Considerare l'impatto degli errori sulla sicurezza** del programma.

## Conclusione

La gestione degli errori è un aspetto fondamentale della programmazione in C. Un programma robusto deve essere in grado di rilevare situazioni anomale, gestirle appropriatamente e, quando possibile, recuperare da esse. Le tecniche presentate in questa guida forniscono una base solida per implementare una gestione degli errori efficace nei programmi C.

## Esercizi

1. Implementa una funzione che legga un file di testo e conti il numero di parole, gestendo correttamente tutti i possibili errori.
2. Crea una libreria di funzioni per l'allocazione dinamica della memoria con gestione degli errori integrata.
3. Modifica un programma esistente per aggiungere un sistema di logging che registri informazioni dettagliate sugli errori che si verificano durante l'esecuzione.