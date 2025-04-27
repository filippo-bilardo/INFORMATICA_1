# Funzioni ricorsive in C

La ricorsione è una tecnica di programmazione in cui una funzione richiama se stessa per risolvere un problema. Questo approccio è particolarmente utile per problemi che possono essere suddivisi in sottoproblemi più piccoli e simili al problema originale.

## Concetti di base della ricorsione

Una funzione ricorsiva è composta da due parti fondamentali:

1. **Caso base**: una condizione che determina quando la ricorsione deve terminare
2. **Caso ricorsivo**: la chiamata della funzione a se stessa con parametri modificati

Senza un caso base ben definito, la funzione continuerebbe a chiamare se stessa indefinitamente, causando un errore di stack overflow.

### Struttura di una funzione ricorsiva

```c
tipo_ritorno funzione_ricorsiva(parametri) {
    // Caso base: condizione di terminazione
    if (condizione_terminazione) {
        return valore_caso_base;
    }
    
    // Caso ricorsivo: chiamata alla stessa funzione
    return funzione_ricorsiva(parametri_modificati);
}
```

## Esempio semplice: calcolo del fattoriale

Il fattoriale di un numero naturale n (indicato con n!) è il prodotto di tutti i numeri interi positivi minori o uguali a n. Per definizione, 0! = 1.

Implementazione ricorsiva del fattoriale:

```c
#include <stdio.h>

// Funzione ricorsiva per calcolare il fattoriale
unsigned long fattoriale(int n) {
    // Caso base
    if (n == 0 || n == 1) {
        return 1;
    }
    
    // Caso ricorsivo
    return n * fattoriale(n - 1);
}

int main() {
    int numero = 5;
    printf("%d! = %lu\n", numero, fattoriale(numero));
    return 0;
}
```

Output:
```
5! = 120
```

### Come funziona la ricorsione del fattoriale

Per comprendere meglio il funzionamento della ricorsione, analizziamo passo per passo l'esecuzione di `fattoriale(5)`:

1. `fattoriale(5)` verifica il caso base: 5 non è né 0 né 1, quindi procede con il caso ricorsivo
2. Restituisce `5 * fattoriale(4)`
3. `fattoriale(4)` restituisce `4 * fattoriale(3)`
4. `fattoriale(3)` restituisce `3 * fattoriale(2)`
5. `fattoriale(2)` restituisce `2 * fattoriale(1)`
6. `fattoriale(1)` è un caso base e restituisce 1
7. Risalendo: `2 * 1 = 2`
8. `3 * 2 = 6`
9. `4 * 6 = 24`
10. `5 * 24 = 120`

Quindi, `fattoriale(5)` restituisce 120.

## Esempio classico: sequenza di Fibonacci

La sequenza di Fibonacci è una serie di numeri in cui ogni numero è la somma dei due precedenti. I primi numeri della sequenza sono: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...

Implementazione ricorsiva della sequenza di Fibonacci:

```c
#include <stdio.h>

// Funzione ricorsiva per calcolare il numero di Fibonacci
int fibonacci(int n) {
    // Casi base
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    // Caso ricorsivo
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    printf("I primi 10 numeri della sequenza di Fibonacci:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    return 0;
}
```

Output:
```
I primi 10 numeri della sequenza di Fibonacci:
0 1 1 2 3 5 8 13 21 34 
```

## Ricorsione vs. iterazione

Molti problemi possono essere risolti sia con un approccio ricorsivo che con un approccio iterativo (utilizzando cicli). Ecco un confronto tra le due implementazioni del fattoriale:

### Implementazione ricorsiva

```c
unsigned long fattoriale_ricorsivo(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fattoriale_ricorsivo(n - 1);
}
```

### Implementazione iterativa

```c
unsigned long fattoriale_iterativo(int n) {
    unsigned long risultato = 1;
    for (int i = 2; i <= n; i++) {
        risultato *= i;
    }
    return risultato;
}
```

### Vantaggi della ricorsione

1. **Leggibilità**: Le soluzioni ricorsive sono spesso più eleganti e riflettono meglio la definizione matematica del problema
2. **Semplicità**: Per alcuni problemi, la soluzione ricorsiva è più intuitiva e richiede meno codice
3. **Adatta a strutture ricorsive**: Ideale per problemi che coinvolgono strutture dati ricorsive come alberi e grafi

### Svantaggi della ricorsione

1. **Overhead di memoria**: Ogni chiamata ricorsiva aggiunge un frame allo stack, consumando memoria
2. **Rischio di stack overflow**: Troppe chiamate ricorsive possono esaurire lo spazio dello stack
3. **Efficienza**: Le soluzioni ricorsive possono essere meno efficienti a causa delle chiamate di funzione ripetute

## Ricorsione in coda (tail recursion)

La ricorsione in coda è una forma speciale di ricorsione in cui la chiamata ricorsiva è l'ultima operazione eseguita dalla funzione. Questo tipo di ricorsione può essere ottimizzato dai compilatori moderni per evitare l'overhead dello stack.

### Esempio di ricorsione in coda: fattoriale

```c
#include <stdio.h>

// Funzione ausiliaria con ricorsione in coda
unsigned long fattoriale_coda_aux(int n, unsigned long accumulatore) {
    // Caso base
    if (n == 0 || n == 1) {
        return accumulatore;
    }
    
    // Chiamata ricorsiva in coda
    return fattoriale_coda_aux(n - 1, n * accumulatore);
}

// Funzione principale che avvia la ricorsione
unsigned long fattoriale_coda(int n) {
    return fattoriale_coda_aux(n, 1);
}

int main() {
    int numero = 5;
    printf("%d! = %lu\n", numero, fattoriale_coda(numero));
    return 0;
}
```

## Esempi avanzati di ricorsione

### Torre di Hanoi

Il problema della Torre di Hanoi è un classico esempio di problema che può essere risolto elegantemente con la ricorsione.

```c
#include <stdio.h>

// Funzione ricorsiva per risolvere la Torre di Hanoi
void hanoi(int n, char origine, char destinazione, char ausiliario) {
    if (n == 1) {
        printf("Sposta il disco 1 da %c a %c\n", origine, destinazione);
        return;
    }
    
    hanoi(n - 1, origine, ausiliario, destinazione);
    printf("Sposta il disco %d da %c a %c\n", n, origine, destinazione);
    hanoi(n - 1, ausiliario, destinazione, origine);
}

int main() {
    int n = 3;  // Numero di dischi
    printf("Soluzione per %d dischi:\n", n);
    hanoi(n, 'A', 'C', 'B');  // A=origine, B=ausiliario, C=destinazione
    return 0;
}
```

Output:
```
Soluzione per 3 dischi:
Sposta il disco 1 da A a C
Sposta il disco 2 da A a B
Sposta il disco 1 da C a B
Sposta il disco 3 da A a C
Sposta il disco 1 da B a A
Sposta il disco 2 da B a C
Sposta il disco 1 da A a C
```

### Algoritmo QuickSort

QuickSort è un efficiente algoritmo di ordinamento che utilizza la ricorsione per suddividere l'array in partizioni più piccole.

```c
#include <stdio.h>

// Funzione per scambiare due elementi
void scambia(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per trovare il pivot e partizionare l'array
int partizione(int arr[], int basso, int alto) {
    int pivot = arr[alto];  // Scegliamo l'ultimo elemento come pivot
    int i = (basso - 1);    // Indice dell'elemento più piccolo
    
    for (int j = basso; j <= alto - 1; j++) {
        // Se l'elemento corrente è minore o uguale al pivot
        if (arr[j] <= pivot) {
            i++;  // Incrementa l'indice dell'elemento più piccolo
            scambia(&arr[i], &arr[j]);
        }
    }
    scambia(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Funzione ricorsiva QuickSort
void quickSort(int arr[], int basso, int alto) {
    if (basso < alto) {
        // Trova l'indice di partizione
        int pi = partizione(arr, basso, alto);
        
        // Ordina ricorsivamente gli elementi prima e dopo la partizione
        quickSort(arr, basso, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Funzione per stampare un array
void stampaArray(int arr[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array originale: ");
    stampaArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Array ordinato: ");
    stampaArray(arr, n);
    
    return 0;
}
```

Output:
```
Array originale: 10 7 8 9 1 5 
Array ordinato: 1 5 7 8 9 10 
```

## Ricorsione mutua

La ricorsione mutua si verifica quando due o più funzioni si chiamano a vicenda in modo ciclico.

```c
#include <stdio.h>

// Dichiarazioni anticipate
int è_pari(int n);
int è_dispari(int n);

// Funzione che verifica se un numero è pari
int è_pari(int n) {
    if (n == 0) {
        return 1;  // 0 è pari
    } else {
        return è_dispari(n - 1);
    }
}

// Funzione che verifica se un numero è dispari
int è_dispari(int n) {
    if (n == 0) {
        return 0;  // 0 non è dispari
    } else {
        return è_pari(n - 1);
    }
}

int main() {
    for (int i = 0; i <= 10; i++) {
        if (è_pari(i)) {
            printf("%d è pari\n", i);
        } else {
            printf("%d è dispari\n", i);
        }
    }
    return 0;
}
```

Output:
```
0 è pari
1 è dispari
2 è pari
3 è dispari
4 è pari
5 è dispari
6 è pari
7 è dispari
8 è pari
9 è dispari
10 è pari
```

## Ottimizzazione della ricorsione

### Memoizzazione

La memoizzazione è una tecnica di ottimizzazione che memorizza i risultati delle chiamate di funzione per evitare calcoli ripetuti. È particolarmente utile per problemi con sottoproblemi sovrapposti, come la sequenza di Fibonacci.

```c
#include <stdio.h>
#include <stdlib.h>

// Funzione di Fibonacci con memoizzazione
int fibonacci_memo(int n, int *memo) {
    // Se il risultato è già stato calcolato, lo restituiamo
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // Altrimenti, calcoliamo il risultato e lo memorizziamo
    if (n <= 1) {
        memo[n] = n;
    } else {
        memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);
    }
    
    return memo[n];
}

int fibonacci(int n) {
    // Inizializza l'array per la memoizzazione
    int *memo = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;  // -1 indica che il valore non è ancora stato calcolato
    }
    
    int risultato = fibonacci_memo(n, memo);
    
    // Libera la memoria
    free(memo);
    
    return risultato;
}

int main() {
    printf("I primi 10 numeri della sequenza di Fibonacci (con memoizzazione):\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    return 0;
}
```

Output:
```
I primi 10 numeri della sequenza di Fibonacci (con memoizzazione):
0 1 1 2 3 5 8 13 21 34 
```

## Best practice per l'uso della ricorsione

1. **Identificare chiaramente il caso base**: Assicurarsi che ci sia sempre una condizione di terminazione ben definita.

2. **Evitare la ricorsione eccessiva**: Per problemi con molte chiamate ricorsive, considerare approcci alternativi come l'iterazione o la memoizzazione.

3. **Testare con input piccoli**: Verificare il funzionamento della ricorsione con input di dimensioni ridotte prima di passare a input più grandi.

4. **Considerare i limiti dello stack**: Essere consapevoli dei limiti dello stack e del rischio di stack overflow per ricorsioni profonde.

5. **Utilizzare la ricorsione in coda quando possibile**: Questo tipo di ricorsione può essere ottimizzato dal compilatore.

6. **Applicare tecniche di ottimizzazione**: Utilizzare la memoizzazione o altre tecniche per evitare calcoli ripetuti.

## Domande di autovalutazione

1. Quali sono i due componenti essenziali di una funzione ricorsiva?

2. Perché è importante avere un caso base in una funzione ricorsiva?

3. Qual è la differenza tra ricorsione e iterazione? Quando è preferibile usare l'una rispetto all'altra?

4. Cosa si intende per ricorsione in coda e quali vantaggi offre?

5. Come può la memoizzazione migliorare le prestazioni di una funzione ricorsiva?

## Esercizi proposti

1. Implementa una funzione ricorsiva che calcoli la somma dei primi n numeri naturali.

2. Scrivi una funzione ricorsiva per calcolare il massimo comun divisore (MCD) di due numeri utilizzando l'algoritmo di Euclide.

3. Implementa una funzione ricorsiva che inverta una stringa.

4. Scrivi un programma che utilizzi la ricorsione per risolvere il problema delle N regine (posizionare N regine su una scacchiera NxN in modo che nessuna regina possa attaccare un'altra).

5. Implementa l'algoritmo di ricerca binaria in modo ricorsivo per trovare un elemento in un array ordinato.