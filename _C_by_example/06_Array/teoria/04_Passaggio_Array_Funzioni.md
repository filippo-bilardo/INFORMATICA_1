# Passaggio di Array alle Funzioni in C

Il passaggio di array alle funzioni è un concetto fondamentale in C che presenta caratteristiche particolari rispetto al passaggio di variabili semplici. Questa guida esplora in dettaglio come passare array monodimensionali e multidimensionali alle funzioni, con esempi pratici e best practices.

## Concetti Fondamentali

In C, quando si passa un array a una funzione, non viene passata una copia dell'intero array, ma piuttosto un puntatore al primo elemento dell'array. Questo comportamento ha importanti implicazioni:

1. **Passaggio per riferimento**: Gli array sono sempre passati per riferimento, il che significa che le modifiche apportate all'array all'interno della funzione si riflettono sull'array originale.

2. **Nessuna informazione sulla dimensione**: Il puntatore all'array non contiene informazioni sulla dimensione dell'array, quindi è spesso necessario passare la dimensione come parametro aggiuntivo.

3. **Decadimento in puntatore**: Un array "decade" in un puntatore quando viene passato a una funzione, perdendo l'informazione sulla sua dimensione originale.

## Passaggio di Array Monodimensionali

### Sintassi di Base

Esistono tre modi equivalenti per dichiarare un parametro di funzione che accetta un array:

```c
void funzione1(int arr[]);
void funzione2(int arr[10]); // La dimensione è ignorata dal compilatore
void funzione3(int *arr);    // Equivalente alle precedenti
```

Tutte queste dichiarazioni sono equivalenti dal punto di vista del compilatore, poiché l'array decade in un puntatore.

### Esempio Completo

```c
#include <stdio.h>

// Funzione che modifica un array
void raddoppia_elementi(int arr[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        arr[i] *= 2; // Modifica l'array originale
    }
}

// Funzione che stampa un array
void stampa_array(const int arr[], int dimensione) {
    printf("[");
    for (int i = 0; i < dimensione; i++) {
        printf("%d", arr[i]);
        if (i < dimensione - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int numeri[5] = {1, 2, 3, 4, 5};
    
    printf("Array originale: ");
    stampa_array(numeri, 5);
    
    raddoppia_elementi(numeri, 5);
    
    printf("Array dopo la modifica: ");
    stampa_array(numeri, 5);
    
    return 0;
}
```

### Utilizzo di `const` per Proteggere gli Array

Quando si passa un array a una funzione che non dovrebbe modificarlo, è buona pratica utilizzare il qualificatore `const`:

```c
void stampa_array(const int arr[], int dimensione) {
    // Il compilatore impedirà qualsiasi modifica all'array
    // arr[0] = 100; // Errore di compilazione
    
    for (int i = 0; i < dimensione; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
```

## Passaggio di Array Multidimensionali

Il passaggio di array multidimensionali è più complesso perché è necessario specificare tutte le dimensioni tranne la prima:

### Sintassi per Array Bidimensionali

```c
// Per un array int matrice[righe][colonne]
void funzione(int arr[][colonne], int righe);
// oppure
void funzione(int (*arr)[colonne], int righe);
```

È obbligatorio specificare il numero di colonne perché il compilatore deve sapere come calcolare l'offset per accedere agli elementi.

### Esempio con Array Bidimensionale

```c
#include <stdio.h>

#define RIGHE 3
#define COLONNE 4

// Funzione che stampa una matrice
void stampa_matrice(int matrice[][COLONNE], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

// Funzione che somma 1 a ogni elemento della matrice
void incrementa_matrice(int matrice[][COLONNE], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            matrice[i][j]++;
        }
    }
}

int main() {
    int matrice[RIGHE][COLONNE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Matrice originale:\n");
    stampa_matrice(matrice, RIGHE);
    
    incrementa_matrice(matrice, RIGHE);
    
    printf("\nMatrice dopo l'incremento:\n");
    stampa_matrice(matrice, RIGHE);
    
    return 0;
}
```

### Array Tridimensionali e Oltre

Per array con più di due dimensioni, è necessario specificare tutte le dimensioni tranne la prima:

```c
// Per un array int cubo[x][y][z]
void funzione(int arr[][y][z], int x);
```

## Tecniche Avanzate

### Utilizzo di VLA (Variable Length Arrays)

A partire dallo standard C99, è possibile utilizzare array a lunghezza variabile come parametri di funzione:

```c
#include <stdio.h>

// Funzione che accetta una matrice con numero di colonne variabile
void stampa_matrice_vla(int righe, int colonne, int matrice[righe][colonne]) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrice[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    stampa_matrice_vla(3, 4, matrice);
    
    return 0;
}
```

**Nota**: I VLA non sono supportati in C++, quindi questa tecnica limita la portabilità del codice.

### Passaggio di Array di Dimensione Arbitraria

Per passare array di qualsiasi dimensione, si può utilizzare un puntatore e gestire l'accesso manualmente:

```c
#include <stdio.h>

// Funzione che tratta una matrice come un array monodimensionale
void stampa_matrice_generica(int *matrice, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            // Calcolo manuale dell'indice
            printf("%3d ", matrice[i * colonne + j]);
        }
        printf("\n");
    }
}

int main() {
    int matrice[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Passaggio dell'array come puntatore al primo elemento
    stampa_matrice_generica((int *)matrice, 3, 4);
    
    return 0;
}
```

## Best Practices

1. **Passa sempre la dimensione**: Quando passi un array a una funzione, passa sempre anche la sua dimensione.

2. **Usa `const` quando appropriato**: Se la funzione non deve modificare l'array, dichiara il parametro come `const`.

3. **Preferisci le macro o le costanti per le dimensioni**: Usa macro o costanti per le dimensioni degli array per migliorare la manutenibilità del codice.

4. **Considera l'uso di strutture dati alternative**: Per casi complessi, considera l'uso di strutture dati che includano sia l'array che la sua dimensione.

5. **Documenta le convenzioni**: Documenta chiaramente come la funzione utilizzerà l'array passato.

## Limitazioni e Considerazioni

1. **Impossibilità di determinare la dimensione**: All'interno della funzione, non è possibile determinare la dimensione dell'array originale senza passarla come parametro aggiuntivo.

2. **Overhead di passaggio**: Anche se viene passato solo un puntatore, per array molto grandi potrebbe essere più efficiente passare un puntatore a una struttura che contiene l'array.

3. **Problemi di portabilità**: Alcune tecniche (come i VLA) non sono supportate in tutti gli standard o compilatori.

## Esempi Pratici

### Esempio 1: Ricerca in un Array

```c
#include <stdio.h>

// Funzione che cerca un valore in un array e restituisce l'indice
int cerca_valore(const int arr[], int dimensione, int valore) {
    for (int i = 0; i < dimensione; i++) {
        if (arr[i] == valore) {
            return i; // Valore trovato, restituisce l'indice
        }
    }
    return -1; // Valore non trovato
}

int main() {
    int numeri[] = {10, 23, 5, 17, 42, 8, 15};
    int dimensione = sizeof(numeri) / sizeof(numeri[0]);
    int valore_da_cercare = 17;
    
    int indice = cerca_valore(numeri, dimensione, valore_da_cercare);
    
    if (indice != -1) {
        printf("Il valore %d è stato trovato all'indice %d\n", valore_da_cercare, indice);
    } else {
        printf("Il valore %d non è stato trovato nell'array\n", valore_da_cercare);
    }
    
    return 0;
}
```

### Esempio 2: Funzione che Restituisce un Array

In C, una funzione non può restituire direttamente un array, ma può restituire un puntatore a un array allocato dinamicamente o modificare un array passato come parametro:

```c
#include <stdio.h>
#include <stdlib.h>

// Funzione che alloca e restituisce un nuovo array
int* crea_array_progressivo(int dimensione) {
    // Allocazione dinamica della memoria
    int* nuovo_array = (int*)malloc(dimensione * sizeof(int));
    
    if (nuovo_array == NULL) {
        printf("Errore: Impossibile allocare memoria\n");
        return NULL;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < dimensione; i++) {
        nuovo_array[i] = i + 1;
    }
    
    return nuovo_array;
}

int main() {
    int dimensione = 10;
    int* mio_array = crea_array_progressivo(dimensione);
    
    if (mio_array != NULL) {
        printf("Array creato: ");
        for (int i = 0; i < dimensione; i++) {
            printf("%d ", mio_array[i]);
        }
        printf("\n");
        
        // Importante: liberare la memoria allocata
        free(mio_array);
    }
    
    return 0;
}
```

## Domande di Autovalutazione

1. Perché in C gli array sono sempre passati per riferimento alle funzioni?
2. Qual è la differenza tra dichiarare un parametro di funzione come `int arr[]` e `int *arr`?
3. Perché è necessario specificare tutte le dimensioni tranne la prima quando si passa un array multidimensionale a una funzione?
4. Come si può proteggere un array da modifiche all'interno di una funzione?
5. Quali sono i vantaggi e gli svantaggi dell'utilizzo dei VLA (Variable Length Arrays)?

## Esercizi Proposti

1. Scrivi una funzione che calcoli la somma di tutti gli elementi di un array di interi.
2. Implementa una funzione che inverta l'ordine degli elementi di un array.
3. Crea una funzione che accetti una matrice e restituisca la sua trasposta.
4. Scrivi una funzione che unisca due array ordinati in un nuovo array ordinato.
5. Implementa una funzione che ruoti gli elementi di un array di n posizioni verso destra o sinistra.

Nel prossimo capitolo, esploreremo le stringhe in C, che sono essenzialmente array di caratteri con alcune caratteristiche speciali.