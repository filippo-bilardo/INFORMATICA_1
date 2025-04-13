# D.3. Gestione degli Errori

La gestione degli errori è un aspetto fondamentale della programmazione che consente di creare software robusto e affidabile. In C, la gestione degli errori richiede un'attenzione particolare poiché il linguaggio non fornisce meccanismi integrati come le eccezioni presenti in altri linguaggi.

## Introduzione agli errori runtime

Gli errori runtime sono problemi che si verificano durante l'esecuzione di un programma. A differenza degli errori di compilazione, che vengono rilevati dal compilatore prima dell'esecuzione, gli errori runtime si manifestano solo quando il programma è in esecuzione.

### Tipi comuni di errori runtime in C

1. **Divisione per zero**: Si verifica quando si tenta di dividere un numero per zero.

```c
int a = 10;
int b = 0;
int risultato = a / b; // Errore runtime: divisione per zero
```

2. **Accesso a memoria non valida**: Si verifica quando si tenta di accedere a una posizione di memoria non allocata o fuori dai limiti di un array.

```c
int array[5];
array[10] = 5; // Errore runtime: accesso fuori dai limiti dell'array
```

3. **Dereferenziazione di puntatori nulli**: Si verifica quando si tenta di accedere al valore puntato da un puntatore nullo.

```c
int *ptr = NULL;
*ptr = 10; // Errore runtime: dereferenziazione di un puntatore nullo
```

4. **Overflow aritmetico**: Si verifica quando il risultato di un'operazione aritmetica è troppo grande per essere rappresentato dal tipo di dato utilizzato.

```c
int a = 2147483647; // Valore massimo per un int a 32 bit
int b = a + 1; // Errore runtime: overflow aritmetico
```

5. **Errori di conversione**: Si verificano quando si tenta di convertire un valore in un tipo di dato che non può rappresentarlo correttamente.

```c
float f = 1e40;
int i = (int)f; // Errore runtime: il valore è troppo grande per un int
```

6. **Errori di input/output**: Si verificano quando le operazioni di input/output falliscono, ad esempio quando si tenta di aprire un file che non esiste.

```c
FILE *file = fopen("file_inesistente.txt", "r");
if (file == NULL) {
    // Errore runtime: impossibile aprire il file
}
```

## Verifica delle condizioni e prevenzione degli errori

La prevenzione degli errori è sempre preferibile alla loro gestione. Ecco alcune tecniche per prevenire gli errori runtime:

### 1. Verifica delle condizioni prima di operazioni potenzialmente pericolose

```c
// Prevenzione della divisione per zero
int a = 10;
int b = 0;

if (b != 0) {
    int risultato = a / b;
    printf("Risultato: %d\n", risultato);
} else {
    printf("Errore: divisione per zero\n");
}
```

### 2. Controllo dei limiti degli array

```c
// Prevenzione dell'accesso fuori dai limiti dell'array
int array[5];
int indice = 10;

if (indice >= 0 && indice < 5) {
    array[indice] = 5;
} else {
    printf("Errore: indice fuori dai limiti dell'array\n");
}
```

### 3. Verifica dei puntatori prima della dereferenziazione

```c
// Prevenzione della dereferenziazione di puntatori nulli
int *ptr = NULL;

if (ptr != NULL) {
    *ptr = 10;
} else {
    printf("Errore: puntatore nullo\n");
}
```

### 4. Controllo dell'overflow aritmetico

```c
// Prevenzione dell'overflow aritmetico
#include <limits.h>

int a = 2147483647; // Valore massimo per un int a 32 bit
int b = 1;

if (a > INT_MAX - b) {
    printf("Errore: l'operazione causerebbe un overflow\n");
} else {
    int risultato = a + b;
    printf("Risultato: %d\n", risultato);
}
```

### 5. Validazione dell'input dell'utente

```c
// Validazione dell'input dell'utente
int eta;
printf("Inserisci la tua età: ");

if (scanf("%d", &eta) != 1 || eta < 0 || eta > 150) {
    printf("Errore: età non valida\n");
} else {
    printf("La tua età è: %d\n", eta);
}
```

## Gestione degli errori in C

Poiché C non ha un meccanismo di gestione delle eccezioni integrato, gli errori vengono generalmente gestiti utilizzando codici di ritorno, variabili globali di errore o callback di errore.

### 1. Codici di ritorno

Molte funzioni in C restituiscono un valore che indica se l'operazione è stata completata con successo o se si è verificato un errore.

```c
// Esempio di funzione che utilizza codici di ritorno
int dividi(int a, int b, int *risultato) {
    if (b == 0) {
        return -1; // Codice di errore per divisione per zero
    }
    *risultato = a / b;
    return 0; // Successo
}

int main() {
    int a = 10, b = 0, risultato;
    int codice = dividi(a, b, &risultato);
    
    if (codice == 0) {
        printf("Risultato: %d\n", risultato);
    } else if (codice == -1) {
        printf("Errore: divisione per zero\n");
    }
    
    return 0;
}
```

### 2. Variabile globale `errno`

La libreria standard di C definisce una variabile globale `errno` che viene impostata da alcune funzioni quando si verifica un errore. La variabile `errno` è definita in `<errno.h>`.

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        printf("Errore nell'apertura del file: %s\n", strerror(errno));
    } else {
        // Operazioni sul file
        fclose(file);
    }
    
    return 0;
}
```

### 3. Funzioni di gestione degli errori personalizzate

È possibile definire funzioni personalizzate per gestire gli errori in modo coerente in tutto il programma.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Funzione di gestione degli errori personalizzata
void gestisci_errore(const char *formato, ...) {
    va_list args;
    va_start(args, formato);
    
    fprintf(stderr, "ERRORE: ");
    vfprintf(stderr, formato, args);
    fprintf(stderr, "\n");
    
    va_end(args);
    exit(EXIT_FAILURE);
}

int main() {
    int a = 10, b = 0;
    
    if (b == 0) {
        gestisci_errore("Divisione per zero (a=%d, b=%d)", a, b);
    }
    
    int risultato = a / b; // Questa linea non verrà mai eseguita se b è 0
    printf("Risultato: %d\n", risultato);
    
    return 0;
}
```

## Esempi di gestione degli errori nei programmi

### Esempio 1: Gestione degli errori in un programma di lettura di file

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file;
    char buffer[100];
    
    // Apertura del file
    file = fopen("dati.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Errore nell'apertura del file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // Lettura dal file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    // Verifica di errori durante la lettura
    if (ferror(file)) {
        fprintf(stderr, "Errore durante la lettura del file: %s\n", strerror(errno));
        fclose(file);
        return EXIT_FAILURE;
    }
    
    // Chiusura del file
    if (fclose(file) != 0) {
        fprintf(stderr, "Errore durante la chiusura del file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
```

### Esempio 2: Gestione degli errori in un programma di allocazione dinamica della memoria

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *array;
    int dimensione;
    
    printf("Inserisci la dimensione dell'array: ");
    if (scanf("%d", &dimensione) != 1 || dimensione <= 0) {
        fprintf(stderr, "Errore: dimensione non valida\n");
        return EXIT_FAILURE;
    }
    
    // Allocazione dinamica della memoria
    array = (int *)malloc(dimensione * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria\n");
        return EXIT_FAILURE;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < dimensione; i++) {
        array[i] = i * 2;
    }
    
    // Stampa dell'array
    printf("Array: ");
    for (int i = 0; i < dimensione; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Liberazione della memoria
    free(array);
    
    return EXIT_SUCCESS;
}
```

### Esempio 3: Gestione degli errori in un programma di calcolo

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

// Funzione per calcolare la radice quadrata con gestione degli errori
double radice_quadrata(double x, int *errore) {
    *errore = 0;
    
    if (x < 0) {
        *errore = 1; // Codice di errore per input negativo
        return 0.0;
    }
    
    return sqrt(x);
}

// Funzione per calcolare il logaritmo con gestione degli errori
double logaritmo(double x, int *errore) {
    *errore = 0;
    
    if (x <= 0) {
        *errore = 2; // Codice di errore per input non positivo
        return 0.0;
    }
    
    return log(x);
}

int main() {
    double x;
    int errore;
    
    printf("Inserisci un numero: ");
    if (scanf("%lf", &x) != 1) {
        fprintf(stderr, "Errore: input non valido\n");
        return EXIT_FAILURE;
    }
    
    // Calcolo della radice quadrata
    double risultato1 = radice_quadrata(x, &errore);
    if (errore == 1) {
        fprintf(stderr, "Errore: impossibile calcolare la radice quadrata di un numero negativo\n");
    } else {
        printf("La radice quadrata di %.2f è %.2f\n", x, risultato1);
    }
    
    // Calcolo del logaritmo
    double risultato2 = logaritmo(x, &errore);
    if (errore == 2) {
        fprintf(stderr, "Errore: impossibile calcolare il logaritmo di un numero non positivo\n");
    } else {
        printf("Il logaritmo naturale di %.2f è %.2f\n", x, risultato2);
    }
    
    return EXIT_SUCCESS;
}
```

## Conclusioni

La gestione degli errori è un aspetto cruciale della programmazione in C. Sebbene il linguaggio non fornisca meccanismi integrati come le eccezioni, è possibile implementare strategie efficaci per prevenire e gestire gli errori runtime. Le tecniche presentate in questo documento, come la verifica delle condizioni, l'utilizzo di codici di ritorno e la validazione dell'input, consentono di creare programmi più robusti e affidabili.

Ricorda che la prevenzione degli errori è sempre preferibile alla loro gestione. Verifica sempre le condizioni prima di eseguire operazioni potenzialmente pericolose e valida l'input dell'utente per evitare comportamenti imprevisti del programma.