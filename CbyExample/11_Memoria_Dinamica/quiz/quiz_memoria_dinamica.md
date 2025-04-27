# Quiz di Autovalutazione sulla Memoria Dinamica in C

Questo quiz ti aiuterà a verificare la tua comprensione dei concetti relativi alla gestione della memoria dinamica in C. Per ogni domanda, scegli la risposta che ritieni corretta e poi controlla le soluzioni alla fine del documento.

## Domande a Scelta Multipla

### 1. Quale funzione viene utilizzata per allocare dinamicamente un blocco di memoria non inizializzata in C?

a) `new()`
b) `malloc()`
c) `alloc()`
d) `memalloc()`

### 2. Quale di queste affermazioni sulla funzione `calloc()` è corretta?

a) Alloca memoria e la inizializza con valori casuali
b) Alloca memoria e la inizializza con tutti zeri
c) Alloca memoria senza inizializzarla
d) Ridimensiona un blocco di memoria precedentemente allocato

### 3. Cosa succede se `malloc()` non riesce ad allocare la memoria richiesta?

a) Il programma termina automaticamente
b) Viene generata un'eccezione
c) Ritorna NULL
d) Alloca una quantità inferiore di memoria

### 4. Quale di queste è una corretta allocazione dinamica di un array di 10 interi?

a) `int array = malloc(10);`
b) `int array = malloc(10 * 4);`
c) `int *array = (int *)malloc(10 * sizeof(int));`
d) `int array[10] = malloc(sizeof(int));`

### 5. Cosa fa la funzione `free()`?

a) Libera tutta la memoria allocata dal programma
b) Libera un blocco di memoria precedentemente allocato con `malloc()`, `calloc()` o `realloc()`
c) Deframmenta la memoria per ottimizzare l'uso dello heap
d) Imposta a NULL tutti i puntatori nel programma

### 6. Cosa succede se si tenta di accedere a memoria già liberata con `free()`?

a) Il programma genera sempre un errore di segmentazione
b) Il puntatore diventa automaticamente NULL
c) Il comportamento è indefinito
d) La memoria viene riallocata automaticamente

### 7. Cos'è un memory leak?

a) Un errore che si verifica quando si tenta di allocare più memoria di quella disponibile
b) Un errore che si verifica quando si accede a memoria non allocata
c) Una situazione in cui la memoria allocata non viene mai liberata
d) Una situazione in cui la memoria viene liberata due volte

### 8. Cos'è un dangling pointer?

a) Un puntatore che punta a memoria non allocata
b) Un puntatore che punta a memoria già liberata
c) Un puntatore che punta a NULL
d) Un puntatore che punta a un'area di memoria protetta

### 9. Quale funzione permette di ridimensionare un blocco di memoria precedentemente allocato?

a) `resize()`
b) `realloc()`
c) `remalloc()`
d) `reallocate()`

### 10. Quale di queste è una buona pratica nella gestione della memoria dinamica?

a) Liberare la memoria solo alla fine del programma
b) Impostare i puntatori a NULL dopo averli liberati con `free()`
c) Allocare sempre più memoria del necessario per sicurezza
d) Evitare di controllare il valore di ritorno di `malloc()` per migliorare le prestazioni

### 11. Dove viene allocata la memoria dinamica in C?

a) Nello stack
b) Nel registro
c) Nello heap
d) Nella memoria statica

### 12. Quale di queste operazioni può causare un buffer overflow?

a) Allocare meno memoria del necessario
b) Liberare memoria già liberata
c) Scrivere dati oltre i limiti di un array allocato dinamicamente
d) Dimenticare di liberare la memoria allocata

### 13. Quale di queste è la corretta sequenza per liberare la memoria di una matrice allocata dinamicamente?

a) Prima liberare la matrice, poi le singole righe
b) Prima liberare le singole righe, poi la matrice
c) Liberare solo la matrice è sufficiente
d) L'ordine non è importante

### 14. Quale strumento può essere utilizzato per rilevare memory leak in un programma C?

a) GDB
b) Valgrind
c) Compiler warnings
d) Visual Studio Debugger

### 15. Quale di queste affermazioni sulla memoria dinamica è FALSA?

a) La memoria dinamica permette di creare strutture dati la cui dimensione può variare durante l'esecuzione
b) La memoria dinamica viene allocata nello heap
c) La memoria dinamica viene liberata automaticamente quando non è più necessaria
d) La memoria dinamica richiede una gestione esplicita da parte del programmatore

## Soluzioni

1. b) `malloc()`
2. b) Alloca memoria e la inizializza con tutti zeri
3. c) Ritorna NULL
4. c) `int *array = (int *)malloc(10 * sizeof(int));`
5. b) Libera un blocco di memoria precedentemente allocato con `malloc()`, `calloc()` o `realloc()`
6. c) Il comportamento è indefinito
7. c) Una situazione in cui la memoria allocata non viene mai liberata
8. b) Un puntatore che punta a memoria già liberata
9. b) `realloc()`
10. b) Impostare i puntatori a NULL dopo averli liberati con `free()`
11. c) Nello heap
12. c) Scrivere dati oltre i limiti di un array allocato dinamicamente
13. b) Prima liberare le singole righe, poi la matrice
14. b) Valgrind
15. c) La memoria dinamica viene liberata automaticamente quando non è più necessaria

## Spiegazioni

1. `malloc()` è la funzione standard in C per allocare memoria dinamicamente.

2. `calloc()` alloca memoria e la inizializza con tutti zeri, a differenza di `malloc()` che non inizializza la memoria.

3. Quando `malloc()` non riesce ad allocare la memoria richiesta, ritorna NULL. È importante controllare sempre questo valore di ritorno.

4. Per allocare un array di 10 interi, dobbiamo moltiplicare la dimensione di un intero per 10 e fare il cast del risultato di `malloc()` al tipo appropriato.

5. `free()` libera un blocco specifico di memoria precedentemente allocato, non tutta la memoria del programma.

6. Accedere a memoria già liberata causa un comportamento indefinito, che può variare da nessun effetto visibile a crash del programma.

7. Un memory leak si verifica quando si alloca memoria che non viene mai liberata, causando un consumo progressivo di memoria.

8. Un dangling pointer è un puntatore che punta a memoria già liberata, il che può causare comportamenti imprevedibili se dereferenziato.

9. `realloc()` permette di ridimensionare un blocco di memoria precedentemente allocato.

10. Impostare i puntatori a NULL dopo `free()` è una buona pratica perché previene l'uso accidentale di dangling pointers.

11. La memoria dinamica viene allocata nello heap, mentre le variabili locali sono allocate nello stack.

12. Scrivere dati oltre i limiti di un array (buffer overflow) può corrompere altre aree di memoria e causare comportamenti imprevedibili.

13. Per liberare una matrice allocata dinamicamente, è necessario prima liberare ogni riga e poi l'array di puntatori alle righe.

14. Valgrind è uno strumento molto potente per rilevare memory leak e altri problemi di gestione della memoria.

15. A differenza di linguaggi con garbage collection, in C la memoria dinamica NON viene liberata automaticamente e richiede una gestione esplicita da parte del programmatore.