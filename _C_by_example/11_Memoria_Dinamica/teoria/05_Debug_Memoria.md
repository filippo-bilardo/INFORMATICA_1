# Strumenti di Debug della Memoria in C

## Introduzione

La gestione della memoria è uno degli aspetti più critici della programmazione in C. Errori come memory leak, accessi a memoria non allocata, o doppia deallocazione possono causare comportamenti imprevedibili, crash o vulnerabilità di sicurezza. Fortunatamente, esistono diversi strumenti specializzati che possono aiutare a identificare e risolvere questi problemi.

Questo documento esplora i principali strumenti di debug della memoria disponibili per i programmatori C, con esempi pratici di utilizzo.

## Valgrind

Valgrind è una suite di strumenti per il debug e il profiling di programmi. Il suo strumento più noto, Memcheck, è particolarmente utile per rilevare problemi di gestione della memoria.

### Caratteristiche principali di Memcheck

- Rileva memory leak (perdite di memoria)
- Identifica accessi a memoria non inizializzata
- Segnala accessi a memoria già liberata
- Rileva operazioni di doppia deallocazione (double free)
- Identifica errori di allocazione e deallocazione non corrispondenti (es. malloc/free vs new/delete)
- Segnala sovra/sottoscritture di buffer (buffer overflow/underflow)

### Installazione di Valgrind

Su sistemi Linux basati su Debian/Ubuntu:
```bash
sudo apt-get install valgrind
```

Su sistemi basati su Red Hat/Fedora:
```bash
sudo dnf install valgrind
```

Su macOS (tramite Homebrew):
```bash
brew install valgrind
```

### Utilizzo base di Valgrind

Per eseguire un programma con Valgrind:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./mio_programma
```

Dove:
- `--leak-check=full`: abilita il controllo completo delle perdite di memoria
- `--show-leak-kinds=all`: mostra tutti i tipi di perdite di memoria
- `--track-origins=yes`: traccia l'origine dei valori non inizializzati

### Esempio di output di Valgrind

Consideriamo il seguente programma con un memory leak:

```c
#include <stdlib.h>

int main() {
    int *x = malloc(10 * sizeof(int));
    x[0] = 42;  // Utilizziamo la memoria
    // Manca free(x)
    return 0;
}
```

L'output di Valgrind potrebbe essere simile a:

```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 40 bytes in 1 blocks
==12345==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==12345== 
==12345== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    by 0x400567: main (in ./mio_programma)
==12345== 
==12345== LEAK SUMMARY:
==12345==    definitely lost: 40 bytes in 1 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==      possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==         suppressed: 0 bytes in 0 blocks
```

## AddressSanitizer (ASan)

AddressSanitizer è uno strumento di rilevamento degli errori di memoria integrato nei compilatori moderni come GCC e Clang. È più veloce di Valgrind ma richiede la ricompilazione del codice con flag specifici.

### Caratteristiche principali di AddressSanitizer

- Rileva buffer overflow/underflow (stack, heap, e global)
- Identifica utilizzo di memoria dopo free (use-after-free)
- Rileva doppia deallocazione (double-free)
- Segnala memory leak (con opzioni aggiuntive)
- Ha un overhead di prestazioni inferiore rispetto a Valgrind

### Utilizzo di AddressSanitizer

Per compilare un programma con AddressSanitizer usando GCC:

```bash
gcc -fsanitize=address -g mio_programma.c -o mio_programma
```

Per compilare con Clang:

```bash
clang -fsanitize=address -g mio_programma.c -o mio_programma
```

L'opzione `-g` aggiunge informazioni di debug che rendono più leggibili i report di errore.

### Esempio di output di AddressSanitizer

Consideriamo un programma con un buffer overflow:

```c
#include <stdlib.h>

int main() {
    int *array = malloc(40); // 10 interi
    array[10] = 42; // Accesso fuori dai limiti
    free(array);
    return 0;
}
```

L'output di AddressSanitizer potrebbe essere simile a:

```
==12345==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x614000000068 at pc 0x55555555514d bp 0x7fffffffe350 sp 0x7fffffffe340
WRITE of size 4 at 0x614000000068 thread T0
    #0 0x55555555514c in main (/path/to/mio_programma+0x114c)
    #1 0x7ffff7a6c082 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x27082)
    #2 0x55555555509d in _start (/path/to/mio_programma+0x109d)

0x614000000068 is located 0 bytes to the right of 40-byte region [0x614000000040,0x614000000068)
allocated by thread T0 here:
    #0 0x7ffff7b8d40f in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.6+0x6540f)
    #1 0x555555555131 in main (/path/to/mio_programma+0x1131)
    #2 0x7ffff7a6c082 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x27082)

SUMMARY: AddressSanitizer: heap-buffer-overflow (/path/to/mio_programma+0x114c) in main
```

## Electric Fence

Electric Fence è una libreria più leggera che si concentra sulla rilevazione di accessi a memoria non validi.

### Caratteristiche principali di Electric Fence

- Rileva accessi fuori dai limiti della memoria allocata
- Identifica utilizzo di memoria dopo free
- Semplice da utilizzare (non richiede ricompilazione)
- Overhead di memoria significativo

### Installazione di Electric Fence

Su sistemi Linux basati su Debian/Ubuntu:
```bash
sudo apt-get install electric-fence
```

### Utilizzo di Electric Fence

Per utilizzare Electric Fence con un programma esistente:

```bash
LD_PRELOAD=libefence.so ./mio_programma
```

## Mcheck (GNU C Library)

La libreria standard GNU C include funzionalità di debug della memoria che possono essere abilitate senza strumenti esterni.

### Utilizzo di Mcheck

```c
#include <mcheck.h>
#include <stdlib.h>

int main() {
    mtrace(); // Inizia il tracciamento della memoria
    
    int *array = malloc(10 * sizeof(int));
    // Utilizzo dell'array...
    free(array);
    
    muntrace(); // Termina il tracciamento
    return 0;
}
```

Per abilitare il tracciamento, è necessario impostare la variabile d'ambiente `MALLOC_TRACE`:

```bash
export MALLOC_TRACE=tracefile.txt
./mio_programma
mtrace ./mio_programma tracefile.txt
```

## Tecniche di Debug Manuale

Oltre agli strumenti automatizzati, esistono tecniche manuali che possono aiutare a identificare problemi di memoria:

### Wrapper personalizzati per malloc/free

```c
#include <stdio.h>
#include <stdlib.h>

void *debug_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    printf("Allocati %zu byte a %p (%s:%d)\n", size, ptr, file, line);
    return ptr;
}

void debug_free(void *ptr, const char *file, int line) {
    printf("Liberati %p (%s:%d)\n", ptr, file, line);
    free(ptr);
}

#define malloc(size) debug_malloc(size, __FILE__, __LINE__)
#define free(ptr) debug_free(ptr, __FILE__, __LINE__)
```

### Canary values

Inserire valori speciali (canary) prima e dopo le aree di memoria allocate per rilevare buffer overflow:

```c
#define CANARY_VALUE 0xDEADBEEF

typedef struct {
    unsigned int canary_start;
    // Dati effettivi
    char data[100];
    unsigned int canary_end;
} ProtectedBuffer;

void check_canaries(ProtectedBuffer *buf) {
    if (buf->canary_start != CANARY_VALUE || buf->canary_end != CANARY_VALUE) {
        fprintf(stderr, "Buffer overflow rilevato!\n");
        abort();
    }
}
```

## Best Practices per Evitare Problemi di Memoria

1. **Inizializzare sempre la memoria allocata**: Utilizzare `calloc()` o `memset()` per inizializzare la memoria.

2. **Controllare i valori di ritorno delle funzioni di allocazione**: Verificare sempre che `malloc()` e simili non restituiscano `NULL`.

3. **Impostare i puntatori a NULL dopo free**: Dopo aver liberato un puntatore, impostarlo a `NULL` per evitare utilizzi accidentali.

4. **Utilizzare strumenti di analisi statica**: Strumenti come Cppcheck o Clang Static Analyzer possono identificare potenziali problemi prima dell'esecuzione.

5. **Adottare pattern di gestione della memoria**: Utilizzare pattern come RAII (in C++) o implementare gestori di risorse in C.

6. **Documentare la proprietà della memoria**: Chiarire nelle API chi è responsabile dell'allocazione e della deallocazione.

7. **Eseguire test con strumenti di debug della memoria**: Incorporare l'uso di Valgrind o AddressSanitizer nel processo di test.

## Conclusione

Gli strumenti di debug della memoria sono essenziali per sviluppare software C robusto e privo di errori. Utilizzando una combinazione di strumenti automatizzati e tecniche manuali, è possibile identificare e risolvere problemi di memoria che altrimenti potrebbero causare comportamenti imprevedibili o vulnerabilità di sicurezza.

La scelta dello strumento dipende dalle esigenze specifiche del progetto: Valgrind offre un'analisi completa ma con un overhead significativo, AddressSanitizer è più veloce ma richiede ricompilazione, mentre tecniche manuali possono essere integrate direttamente nel codice per un monitoraggio continuo.

Indipendentemente dagli strumenti utilizzati, la consapevolezza dei potenziali problemi di memoria e l'adozione di best practices sono fondamentali per scrivere codice C di alta qualità.