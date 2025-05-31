# Concetti di Base dei Puntatori in C

I puntatori sono uno degli aspetti più potenti e distintivi del linguaggio C. Essi permettono di manipolare direttamente la memoria e sono alla base di molte funzionalità avanzate del linguaggio. Questa guida esplora i concetti fondamentali dei puntatori, fornendo esempi pratici e consigli utili.

## Cos'è un Puntatore?

Un puntatore è una variabile che contiene l'indirizzo di memoria di un'altra variabile. In altre parole, un puntatore "punta" a una posizione in memoria dove sono memorizzati i dati.

### Dichiarazione di un Puntatore

Per dichiarare un puntatore, si utilizza l'operatore asterisco (`*`) seguito dal nome della variabile:

```c
#include <stdio.h>

int main() {
    int numero = 42;      // Una variabile intera normale
    int *ptr_numero;      // Un puntatore a un intero
    
    ptr_numero = &numero; // Assegna l'indirizzo di 'numero' al puntatore
    
    printf("Valore di numero: %d\n", numero);
    printf("Indirizzo di numero: %p\n", &numero);
    printf("Valore di ptr_numero (indirizzo): %p\n", ptr_numero);
    printf("Valore puntato da ptr_numero: %d\n", *ptr_numero);
    
    return 0;
}

// Esempio di output:
// Valore di numero: 42
// Indirizzo di numero: 000000000061FE14
// Valore di ptr_numero (indirizzo): 000000000061FE14
// Valore puntato da ptr_numero: 42
```

### Operatori di Indirizzo e Dereferenziazione

In C, ci sono due operatori fondamentali per lavorare con i puntatori:

1. **Operatore di indirizzo (`&`)**: Restituisce l'indirizzo di memoria di una variabile.
2. **Operatore di dereferenziazione (`*`)**: Accede al valore memorizzato all'indirizzo contenuto in un puntatore.

```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;  // p contiene l'indirizzo di a
    
    printf("Valore di a: %d\n", a);
    printf("Indirizzo di a: %p\n", &a);
    printf("Valore di p: %p\n", p);
    printf("Valore puntato da p: %d\n", *p);
    
    // Modifica del valore tramite puntatore
    *p = 20;  // Modifica il valore di 'a' tramite il puntatore
    printf("Nuovo valore di a: %d\n", a);
    
    return 0;
}
```

## Puntatori e Tipi di Dati

I puntatori sono tipizzati, il che significa che un puntatore deve essere dichiarato per puntare a un tipo specifico di dati. Questo è importante perché il compilatore deve sapere quanti byte leggere quando si dereferenzia un puntatore.

```c
#include <stdio.h>

int main() {
    int intero = 10;
    float decimale = 3.14;
    char carattere = 'A';
    
    int *ptr_intero = &intero;
    float *ptr_decimale = &decimale;
    char *ptr_carattere = &carattere;
    
    printf("Dimensione di intero: %zu byte\n", sizeof(intero));
    printf("Dimensione di decimale: %zu byte\n", sizeof(decimale));
    printf("Dimensione di carattere: %zu byte\n", sizeof(carattere));
    
    printf("Dimensione di ptr_intero: %zu byte\n", sizeof(ptr_intero));
    printf("Dimensione di ptr_decimale: %zu byte\n", sizeof(ptr_decimale));
    printf("Dimensione di ptr_carattere: %zu byte\n", sizeof(ptr_carattere));
    
    return 0;
}
```

## Puntatori e Array

In C, esiste una stretta relazione tra puntatori e array. Il nome di un array è essenzialmente un puntatore costante al suo primo elemento.

```c
#include <stdio.h>

int main() {
    int numeri[5] = {10, 20, 30, 40, 50};
    int *ptr = numeri;  // Equivalente a: int *ptr = &numeri[0];
    
    printf("Indirizzo dell'array: %p\n", numeri);
    printf("Indirizzo del primo elemento: %p\n", &numeri[0]);
    printf("Valore di ptr: %p\n\n", ptr);
    
    // Accesso agli elementi dell'array tramite puntatore
    for (int i = 0; i < 5; i++) {
        printf("numeri[%d] = %d  (indirizzo: %p)\n", 
               i, *(ptr + i), ptr + i);
    }
    
    // Notazione alternativa
    printf("\nAccesso alternativo:\n");
    for (int i = 0; i < 5; i++) {
        printf("numeri[%d] = %d  (indirizzo: %p)\n", 
               i, ptr[i], &ptr[i]);
    }
    
    return 0;
}
```

## Puntatori e Stringhe

In C, le stringhe sono array di caratteri terminati da un carattere nullo ('\0'). I puntatori sono spesso utilizzati per manipolare le stringhe.

```c
#include <stdio.h>

int main() {
    // Dichiarazione di stringhe
    char stringa1[] = "Hello";           // Array di caratteri
    char *stringa2 = "World";           // Puntatore a una stringa costante
    
    printf("stringa1: %s\n", stringa1);
    printf("stringa2: %s\n\n", stringa2);
    
    // Accesso ai singoli caratteri
    printf("Caratteri di stringa1:\n");
    for (int i = 0; stringa1[i] != '\0'; i++) {
        printf("stringa1[%d] = %c\n", i, stringa1[i]);
    }
    
    printf("\nCaratteri di stringa2:\n");
    for (int i = 0; *(stringa2 + i) != '\0'; i++) {
        printf("*(stringa2 + %d) = %c\n", i, *(stringa2 + i));
    }
    
    // NOTA: stringa1 può essere modificata, ma stringa2 no (è in memoria costante)
    stringa1[0] = 'h';  // Valido
    // stringa2[0] = 'w';  // NON valido, causerebbe un errore di runtime
    
    printf("\nstringa1 modificata: %s\n", stringa1);
    
    return 0;
}
```

## Puntatori Nulli

Un puntatore nullo è un puntatore che non punta a nessuna posizione di memoria valida. È buona pratica inizializzare i puntatori a NULL quando non si assegna loro immediatamente un indirizzo valido.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = NULL;  // Inizializzazione a NULL
    
    printf("Valore di ptr: %p\n", ptr);
    
    // Verifica se un puntatore è NULL prima di dereferenziarlo
    if (ptr != NULL) {
        printf("Valore puntato: %d\n", *ptr);
    } else {
        printf("Il puntatore è NULL, non può essere dereferenziato!\n");
    }
    
    // Allocazione di memoria
    ptr = malloc(sizeof(int));
    
    if (ptr != NULL) {
        *ptr = 42;
        printf("Memoria allocata. Valore puntato: %d\n", *ptr);
        free(ptr);  // Liberazione della memoria
    } else {
        printf("Allocazione di memoria fallita!\n");
    }
    
    return 0;
}
```

## Puntatori Void

Un puntatore void è un puntatore generico che può puntare a qualsiasi tipo di dato. È utile quando si vuole creare funzioni che possono lavorare con diversi tipi di dati.

```c
#include <stdio.h>

// Funzione che scambia due valori di qualsiasi tipo
void scambia(void *a, void *b, size_t dimensione) {
    // Buffer temporaneo per lo scambio
    unsigned char temp[dimensione];
    
    // Copia il contenuto di 'a' in 'temp'
    for (size_t i = 0; i < dimensione; i++) {
        temp[i] = ((unsigned char*)a)[i];
    }
    
    // Copia il contenuto di 'b' in 'a'
    for (size_t i = 0; i < dimensione; i++) {
        ((unsigned char*)a)[i] = ((unsigned char*)b)[i];
    }
    
    // Copia il contenuto di 'temp' in 'b'
    for (size_t i = 0; i < dimensione; i++) {
        ((unsigned char*)b)[i] = temp[i];
    }
}

int main() {
    int a = 5, b = 10;
    printf("Prima dello scambio: a = %d, b = %d\n", a, b);
    scambia(&a, &b, sizeof(int));
    printf("Dopo lo scambio: a = %d, b = %d\n\n", a, b);
    
    double x = 3.14, y = 2.71;
    printf("Prima dello scambio: x = %.2f, y = %.2f\n", x, y);
    scambia(&x, &y, sizeof(double));
    printf("Dopo lo scambio: x = %.2f, y = %.2f\n\n", x, y);
    
    char c1 = 'A', c2 = 'Z';
    printf("Prima dello scambio: c1 = %c, c2 = %c\n", c1, c2);
    scambia(&c1, &c2, sizeof(char));
    printf("Dopo lo scambio: c1 = %c, c2 = %c\n", c1, c2);
    
    return 0;
}
```

## Errori Comuni con i Puntatori

### 1. Dereferenziare un Puntatore Non Inizializzato

```c
int *ptr;      // Puntatore non inizializzato
*ptr = 10;     // ERRORE: dereferenziazione di un puntatore non inizializzato
```

### 2. Perdita di Memoria (Memory Leak)

```c
int *ptr = malloc(sizeof(int));
*ptr = 10;
// ... codice ...
ptr = malloc(sizeof(int));  // ERRORE: perdita del riferimento alla memoria precedentemente allocata
*ptr = 20;
// ... codice ...
free(ptr);  // Solo la seconda allocazione viene liberata
```

### 3. Accesso a Memoria Liberata

```c
int *ptr = malloc(sizeof(int));
*ptr = 10;
free(ptr);  // Libera la memoria
*ptr = 20;  // ERRORE: accesso a memoria già liberata
```

### 4. Dereferenziare un Puntatore NULL

```c
int *ptr = NULL;
*ptr = 10;  // ERRORE: dereferenziazione di un puntatore NULL
```

## Best Practices

1. **Inizializzazione**: Inizializza sempre i puntatori, preferibilmente a NULL se non hai un indirizzo valido da assegnare.

2. **Controllo NULL**: Verifica sempre che un puntatore non sia NULL prima di dereferenziarlo.

3. **Liberazione della Memoria**: Libera sempre la memoria allocata dinamicamente quando non è più necessaria.

4. **Puntatori Costanti**: Usa puntatori costanti (`const`) quando non intendi modificare i dati puntati.

5. **Evita l'Aritmetica Complessa**: Mantieni l'aritmetica dei puntatori semplice e chiara per evitare errori.

## Domande di Autovalutazione

1. Qual è la differenza tra un puntatore e una variabile normale?

2. Cosa succede quando si dereferenzia un puntatore?

3. Perché è importante inizializzare i puntatori?

4. Qual è la relazione tra puntatori e array in C?

5. Cosa sono i puntatori void e quando è utile utilizzarli?

## Esercizi Proposti

1. Scrivi una funzione che accetti un array di interi e la sua dimensione, e restituisca la somma degli elementi utilizzando l'aritmetica dei puntatori.

2. Implementa una funzione che inverta una stringa utilizzando i puntatori.

3. Crea una funzione che accetti due puntatori a interi e scambi i valori a cui puntano.

4. Scrivi un programma che utilizzi i puntatori per trovare il valore minimo e massimo in un array.

5. Implementa una funzione che copi una stringa in un'altra utilizzando solo puntatori (senza usare funzioni di libreria come `strcpy`).