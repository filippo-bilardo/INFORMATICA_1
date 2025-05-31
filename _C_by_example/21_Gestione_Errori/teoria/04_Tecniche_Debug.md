# Tecniche di Debug in C

## Introduzione

Il debug è una parte essenziale del processo di sviluppo software. Consiste nell'identificare, analizzare e risolvere errori (bug) nei programmi. In C, dove non esistono meccanismi automatici di gestione degli errori come in altri linguaggi, le tecniche di debug assumono un'importanza ancora maggiore. Questa guida esplora varie tecniche e strumenti per il debug efficace dei programmi C.

## Tecniche di Debug di Base

### Stampe di Debug

La tecnica più semplice e immediata è l'inserimento di istruzioni `printf()` strategiche nel codice per visualizzare lo stato del programma durante l'esecuzione.

```c
#include <stdio.h>

int calculate_factorial(int n) {
    printf("DEBUG: Calcolo del fattoriale di %d\n", n);
    
    if (n < 0) {
        printf("DEBUG: Errore - numero negativo\n");
        return -1;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        printf("DEBUG: i = %d, result = %d\n", i, result);
    }
    
    printf("DEBUG: Risultato finale = %d\n", result);
    return result;
}

int main() {
    int num = 5;
    int fact = calculate_factorial(num);
    printf("Il fattoriale di %d è %d\n", num, fact);
    return 0;
}
```

### Macro di Debug

Per evitare di rimuovere manualmente le stampe di debug nella versione finale, è possibile utilizzare macro condizionali:

```c
#include <stdio.h>

// Definizione della macro di debug
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) /* nulla */
#endif

int calculate_factorial(int n) {
    DEBUG_PRINT("Calcolo del fattoriale di %d", n);
    
    if (n < 0) {
        DEBUG_PRINT("Errore - numero negativo");
        return -1;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        DEBUG_PRINT("i = %d, result = %d", i, result);
    }
    
    DEBUG_PRINT("Risultato finale = %d", result);
    return result;
}

int main() {
    int num = 5;
    int fact = calculate_factorial(num);
    printf("Il fattoriale di %d è %d\n", num, fact);
    return 0;
}
```

Per abilitare le stampe di debug, compilare con l'opzione `-DDEBUG`:

```
gcc -DDEBUG -o program program.c
```

### Asserzioni

Le asserzioni sono utili per verificare che determinate condizioni siano soddisfatte durante l'esecuzione del programma:

```c
#include <stdio.h>
#include <assert.h>

int divide(int a, int b) {
    assert(b != 0);  // Verifica che il divisore non sia zero
    return a / b;
}

int main() {
    int result = divide(10, 2);  // OK
    printf("10 / 2 = %d\n", result);
    
    result = divide(10, 0);  // L'asserzione fallirà qui
    printf("10 / 0 = %d\n", result);  // Questa riga non verrà eseguita
    
    return 0;
}
```

Le asserzioni vengono disabilitate quando si compila con l'opzione `-DNDEBUG`.

## Strumenti di Debug

### GDB (GNU Debugger)

GDB è uno dei debugger più potenti e diffusi per i programmi C. Permette di eseguire il programma passo-passo, impostare breakpoint, esaminare variabili e molto altro.

Per utilizzare GDB, è necessario compilare il programma con l'opzione `-g` per includere le informazioni di debug:

```
gcc -g -o program program.c
```

Esempio di sessione di debug con GDB:

```
$ gdb ./program
(gdb) break main
Breakpoint 1 at 0x1149: file program.c, line 15.
(gdb) run
Starting program: ./program

Breakpoint 1, main () at program.c:15
15      int num = 5;
(gdb) next
16      int fact = calculate_factorial(num);
(gdb) step
calculate_factorial (n=5) at program.c:3
3       printf("DEBUG: Calcolo del fattoriale di %d\n", n);
(gdb) print n
$1 = 5
(gdb) continue
Continuing.
DEBUG: Calcolo del fattoriale di 5
DEBUG: i = 2, result = 2
DEBUG: i = 3, result = 6
DEBUG: i = 4, result = 24
DEBUG: i = 5, result = 120
DEBUG: Risultato finale = 120
Il fattoriale di 5 è 120
[Inferior 1 (process 12345) exited normally]
(gdb) quit
```

Comandi GDB comuni:
- `break`: imposta un breakpoint
- `run`: avvia il programma
- `next`: esegue la prossima istruzione senza entrare nelle funzioni
- `step`: esegue la prossima istruzione entrando nelle funzioni
- `print`: visualizza il valore di un'espressione
- `backtrace`: mostra lo stack delle chiamate
- `continue`: continua l'esecuzione fino al prossimo breakpoint
- `quit`: esce da GDB

### Valgrind

Valgrind è uno strumento potente per il rilevamento di errori di memoria, come memory leak, accessi a memoria non allocata o già liberata, e altri problemi simili.

```
valgrind --leak-check=full ./program
```

Esempio di output di Valgrind:

```
==12345== Memcheck, a memory error detector
==12345== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12345== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==12345== Command: ./program
==12345== 
==12345== Invalid read of size 4
==12345==    at 0x109177: main (program.c:10)
==12345==  Address 0x4a4c040 is 0 bytes after a block of size 40 alloc'd
==12345==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    at 0x109156: main (program.c:7)
==12345== 
==12345== HEAP SUMMARY:
==12345==     in use at exit: 40 bytes in 1 blocks
==12345==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==12345== 
==12345== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    at 0x109156: main (program.c:7)
==12345== 
==12345== LEAK SUMMARY:
==12345==    definitely lost: 40 bytes in 1 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==      possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==         suppressed: 0 bytes in 0 blocks
==12345== 
==12345== For lists of detected and suppressed errors, rerun with: -s
==12345== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

### AddressSanitizer

AddressSanitizer è uno strumento di rilevamento di errori di memoria integrato nei compilatori moderni come GCC e Clang. È più veloce di Valgrind ma richiede la ricompilazione del codice.

```
gcc -fsanitize=address -g -o program program.c
```

## Tecniche di Debug Avanzate

### Logging Strutturato

Implementare un sistema di logging strutturato può facilitare il debug, specialmente in applicazioni complesse:

```c
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// Livelli di log
#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_INFO 2
#define LOG_DEBUG 3

// Livello corrente di log (può essere modificato a runtime)
static int current_log_level = LOG_INFO;

// Funzione di logging
void log_message(int level, const char *file, int line, const char *func, const char *format, ...) {
    if (level > current_log_level) {
        return;  // Ignora i messaggi con livello superiore a quello corrente
    }
    
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
    fprintf(stderr, "[%s] [%s] [%s:%d] [%s] ", time_str, level_strings[level], file, line, func);
    
    // Stampa il messaggio formattato
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

// Macro per semplificare l'utilizzo
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) log_message(LOG_WARNING, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

// Funzione per impostare il livello di log
void set_log_level(int level) {
    if (level >= LOG_ERROR && level <= LOG_DEBUG) {
        current_log_level = level;
    }
}

int divide(int a, int b) {
    LOG_DEBUG("Divisione di %d per %d", a, b);
    
    if (b == 0) {
        LOG_ERROR("Tentativo di divisione per zero");
        return -1;
    }
    
    int result = a / b;
    LOG_DEBUG("Risultato: %d", result);
    
    return result;
}

int main() {
    LOG_INFO("Avvio del programma");
    
    // Imposta il livello di log a DEBUG
    set_log_level(LOG_DEBUG);
    LOG_DEBUG("Livello di log impostato a DEBUG");
    
    int result = divide(10, 2);
    LOG_INFO("10 / 2 = %d", result);
    
    result = divide(10, 0);
    if (result == -1) {
        LOG_WARNING("Si è verificato un errore nella divisione");
    }
    
    LOG_INFO("Terminazione del programma");
    return 0;
}
```

### Dump della Memoria

In situazioni complesse, può essere utile esaminare il contenuto della memoria:

```c
#include <stdio.h>
#include <ctype.h>

void memory_dump(const void *addr, size_t size) {
    const unsigned char *p = (const unsigned char *)addr;
    size_t i, j;
    
    // Intestazione
    printf("Memory dump at %p (%zu bytes):\n", addr, size);
    printf("       | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | ASCII\n");
    printf("-------+-------------------------------------------------+-----------------\n");
    
    // Dump esadecimale e ASCII
    for (i = 0; i < size; i += 16) {
        printf("%06zX | ", i);
        
        // Parte esadecimale
        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                printf("%02X ", p[i + j]);
            } else {
                printf("   ");
            }
        }
        
        printf("| ");
        
        // Parte ASCII
        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                printf("%c", isprint(p[i + j]) ? p[i + j] : '.');
            } else {
                printf(" ");
            }
        }
        
        printf("\n");
    }
}

int main() {
    char data[] = "Hello, World! This is a test string for memory dump.";
    memory_dump(data, sizeof(data));
    return 0;
}
```

### Tracciamento delle Allocazioni di Memoria

Implementare un sistema per tracciare le allocazioni di memoria può aiutare a identificare memory leak:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struttura per tenere traccia delle allocazioni
typedef struct MemoryAllocation {
    void *ptr;                  // Puntatore alla memoria allocata
    size_t size;                // Dimensione dell'allocazione
    const char *file;           // File in cui è avvenuta l'allocazione
    int line;                   // Linea in cui è avvenuta l'allocazione
    struct MemoryAllocation *next;  // Puntatore alla prossima allocazione
} MemoryAllocation;

// Lista delle allocazioni
static MemoryAllocation *allocations = NULL;

// Funzione per aggiungere un'allocazione alla lista
void add_allocation(void *ptr, size_t size, const char *file, int line) {
    MemoryAllocation *alloc = (MemoryAllocation*)malloc(sizeof(MemoryAllocation));
    if (alloc == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria per il tracciamento\n");
        return;
    }
    
    alloc->ptr = ptr;
    alloc->size = size;
    alloc->file = file;
    alloc->line = line;
    alloc->next = allocations;
    
    allocations = alloc;
}

// Funzione per rimuovere un'allocazione dalla lista
void remove_allocation(void *ptr) {
    MemoryAllocation *prev = NULL;
    MemoryAllocation *curr = allocations;
    
    while (curr != NULL) {
        if (curr->ptr == ptr) {
            if (prev == NULL) {
                allocations = curr->next;
            } else {
                prev->next = curr->next;
            }
            
            free(curr);
            return;
        }
        
        prev = curr;
        curr = curr->next;
    }
    
    fprintf(stderr, "Errore: tentativo di liberare memoria non allocata (%p)\n", ptr);
}

// Funzione per stampare le allocazioni correnti
void print_allocations() {
    MemoryAllocation *curr = allocations;
    size_t total_size = 0;
    int count = 0;
    
    printf("\nAllocazioni di memoria non liberate:\n");
    printf("%-20s | %-10s | %-30s | %s\n", "Indirizzo", "Dimensione", "File", "Linea");
    printf("--------------------|------------|--------------------------------|-------\n");
    
    while (curr != NULL) {
        printf("%-20p | %-10zu | %-30s | %d\n", curr->ptr, curr->size, curr->file, curr->line);
        
        total_size += curr->size;
        count++;
        curr = curr->next;
    }
    
    printf("\nTotale: %d allocazioni, %zu byte\n", count, total_size);
}

// Sostituzione delle funzioni di allocazione standard
#define malloc(size) tracked_malloc(size, __FILE__, __LINE__)
#define calloc(nmemb, size) tracked_calloc(nmemb, size, __FILE__, __LINE__)
#define realloc(ptr, size) tracked_realloc(ptr, size, __FILE__, __LINE__)
#define free(ptr) tracked_free(ptr)

// Implementazione delle funzioni di allocazione tracciate
void *tracked_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr != NULL) {
        add_allocation(ptr, size, file, line);
    }
    return ptr;
}

void *tracked_calloc(size_t nmemb, size_t size, const char *file, int line) {
    void *ptr = calloc(nmemb, size);
    if (ptr != NULL) {
        add_allocation(ptr, nmemb * size, file, line);
    }
    return ptr;
}

void *tracked_realloc(void *ptr, size_t size, const char *file, int line) {
    void *new_ptr = realloc(ptr, size);
    if (new_ptr != NULL) {
        if (ptr != NULL) {
            remove_allocation(ptr);
        }
        add_allocation(new_ptr, size, file, line);
    }
    return new_ptr;
}

void tracked_free(void *ptr) {
    if (ptr != NULL) {
        remove_allocation(ptr);
        free(ptr);
    }
}

// Funzione per verificare le perdite di memoria alla fine del programma
void check_memory_leaks() {
    if (allocations != NULL) {
        printf("\nRilevate perdite di memoria!\n");
        print_allocations();
    } else {
        printf("\nNessuna perdita di memoria rilevata.\n");
    }
}

// Esempio di utilizzo
int main() {
    // Registra la funzione di verifica delle perdite di memoria
    atexit(check_memory_leaks);
    
    // Allocazioni di test
    int *array1 = (int*)malloc(10 * sizeof(int));
    char *str = (char*)malloc(100);
    
    // Libera solo una delle allocazioni
    free(array1);
    
    // str non viene liberato, causando una perdita di memoria
    
    return 0;
}
```

## Debug di Problemi Specifici

### Segmentation Fault

I segmentation fault sono tra gli errori più comuni nei programmi C. Possono essere causati da:

1. Dereferenziazione di puntatori NULL
2. Accesso a memoria non allocata
3. Accesso a memoria già liberata
4. Overflow di buffer
5. Underflow di buffer

Per debuggare segmentation fault:

1. Utilizzare GDB per identificare la riga esatta in cui si verifica il crash:

```
$ gdb ./program
(gdb) run
...
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555177 in function_name (param=0x0) at program.c:25
25      *ptr = 42;  // Crash qui
(gdb) backtrace
#0  0x0000555555555177 in function_name (param=0x0) at program.c:25
#1  0x0000555555555201 in main () at program.c:35
```

2. Utilizzare Valgrind o AddressSanitizer per rilevare problemi di memoria.

### Memory Leak

I memory leak si verificano quando la memoria allocata dinamicamente non viene mai liberata. Per identificarli:

1. Utilizzare Valgrind:

```
valgrind --leak-check=full ./program
```

2. Implementare un sistema di tracciamento delle allocazioni come mostrato in precedenza.

### Race Condition

Le race condition si verificano in programmi multi-thread quando l'ordine di esecuzione influisce sul risultato. Per debuggarle:

1. Utilizzare strumenti come Helgrind (parte di Valgrind):

```
valgrind --tool=helgrind ./program
```

2. Aggiungere logging dettagliato per tracciare l'ordine di esecuzione.

## Best Practices

1. **Compilare con warning abilitati**:

```
gcc -Wall -Wextra -Werror -o program program.c
```

2. **Utilizzare strumenti di analisi statica** come cppcheck, clang-analyzer o splint.

3. **Implementare test unitari** per verificare il comportamento delle singole componenti.

4. **Adottare un approccio sistematico al debug**:
   - Identificare il problema
   - Isolare il problema
   - Determinare la causa
   - Correggere il problema
   - Verificare la correzione

5. **Documentare i bug e le soluzioni** per riferimento futuro.

## Conclusione

Il debug è un'arte che richiede pazienza, metodicità e una buona conoscenza degli strumenti disponibili. Le tecniche presentate in questa guida forniscono un punto di partenza per affrontare efficacemente i problemi nei programmi C. Ricorda che prevenire i bug attraverso buone pratiche di programmazione è sempre preferibile a doverli correggere in seguito.

## Esercizi

1. Implementa un programma con un bug intenzionale (ad esempio, un memory leak o un segmentation fault) e utilizza gli strumenti di debug per identificarlo e correggerlo.

2. Crea un sistema di logging personalizzato che supporti diversi livelli di verbosità e la redirezione dell'output su file.

3. Implementa un wrapper per le funzioni di allocazione della memoria che tenga traccia delle allocazioni e rilevi memory leak alla fine del programma.