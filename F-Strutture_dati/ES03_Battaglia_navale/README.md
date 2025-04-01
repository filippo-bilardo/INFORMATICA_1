# Array Bidimensionali in C

## Introduzione alle Matrici

Gli array multidimensionali sono una delle strutture dati fondamentali in C che permettono di organizzare le informazioni in modo gerarchico. Mentre gli array monodimensionali possono essere visualizzati come semplici liste lineari, gli array multidimensionali rappresentano tabelle, matrici e strutture ancora più complesse. In questo capitolo esploreremo come il C implementa questi costrutti, le loro caratteristiche, i vantaggi e le limitazioni che presentano.

## Concetti fondamentali

Un array multidimensionale in C può essere concettualmente visualizzato come un "array di array". L'array bidimensionale è il tipo più comune, spesso utilizzato per rappresentare matrici, tabelle o griglie. Possiamo espandere questo concetto a tre o più dimensioni per rappresentare strutture di dati più complesse.

### Dichiarazione di una Matrice
```c
tipo_dato nome_matrice[numero_righe][numero_colonne];

// Esempio
int matrice[5][5];  // Matrice 5x5 di interi
```

### Inizializzazione di una Matrice
```c
// Inizializzazione completa
int matrice[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Inizializzazione con un valore predefinito (es. tutti zero)
int matrice[5][5] = {0};

// Inizializzazione parziale (gli elementi non specificati vengono inizializzati a zero):
int matrice[3][4] = {
    {10, 11},
    {20},
    {30, 31, 32}
};

//Inizializzazione lineare (il compilatore riempie l'array per righe):
int matrice[3][4] = {10, 11, 12, 13, 20, 21, 22, 23, 30, 31, 32, 33};
```
[Esempio 0: Inizializzazione](example0.c)

## Memorizzazione in memoria

Comprendere come gli array multidimensionali sono memorizzati è cruciale per la loro manipolazione efficiente. In C, gli array multidimensionali sono memorizzati in un formato "row-major order" (ordine per righe), il che significa che gli elementi di una riga sono memorizzati in locazioni di memoria contigue.

Per un array bidimensionale `int arr[3][4]`, la disposizione in memoria sarà:
```c
arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[1][0], arr[1][1], ...
```

Questa informazione è importante quando si eseguono operazioni di accesso sequenziale o quando si convertono coordinate multidimensionali in indici lineari.

### Accesso agli Elementi
Per accedere a un elemento specifico, utilizziamo gli indici di riga e colonna:
```c
int valore = matrice[riga][colonna];
matrice[riga][colonna] = nuovo_valore;
```

È importante rispettare i limiti dell'array. In C, gli indici partono da 0, quindi in un array `int arr[3][4]`, gli indici validi sono da `arr[0][0]` a `arr[2][3]`.

### Passaggio di Matrici alle Funzioni
Il passaggio di array multidimensionali alle funzioni in C richiede particolare attenzione. A differenza degli array monodimensionali, è necessario specificare tutte le dimensioni tranne la prima che risulta opzionale:

Questo perché il compilatore C deve conoscere il layout della memoria per calcolare correttamente gli offset quando si accede agli elementi. Infatti quando passi un array a una funzione, questo "decade" (decays) a un puntatore al primo elemento. Per questo motivo Il compilatore deve sapere come calcolare gli offset per accedere agli elementi.

In C, ci sono diversi modi per passare una matrice (array bidimensionale) a una funzione:

#### 1. Specificare entrambe le dimensioni

```c
void funzione(int matrice[RIGHE][COLONNE]) {
    // Accesso agli elementi: matrice[i][j]
}

// Chiamata
int m[5][5];
funzione(m);
```

In questo caso, la funzione accetta solo matrici con esattamente le dimensioni specificate.
[Esempio 1: Dimensioni fisse](example1_fixed_dimensions.c)

#### 2. Specificare solo la seconda dimensione

```c
void funzione(int matrice[][COLONNE], int righe) {
    // La prima dimensione è variabile
    // Accesso agli elementi: matrice[i][j]
}

// Chiamata
int m[5][5];
funzione(m, 5);
```

Qui, il numero di righe può variare ma il numero di colonne deve essere fisso.
[Esempio 2: Righe variabili](example2_variable_rows.c)

#### 3. Usando un puntatore a puntatore
Questo metodo è più flessibile ma richiede un'allocazione dinamica della memoria.
[Esempio 3: Puntatore a puntatore](example3_pointer_to_pointer.c)

#### 4. Usando un array monodimensionale come matrice
Qui la matrice bidimensionale viene trattata come un array lineare in memoria.
[Esempio 4: Memoria lineare](example4_linear_memory.c)

#### Esempio completo

```c
#include <stdio.h>
#define RIGHE 3
#define COLONNE 3

// Metodo 1: Dimensioni fisse
void stampaMatrice1(int m[RIGHE][COLONNE]) {
    for (int i = 0; i < RIGHE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

// Metodo 2: Prima dimensione variabile
void stampaMatrice2(int m[][COLONNE], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrice[RIGHE][COLONNE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("Usando il metodo 1:\n");
    stampaMatrice1(matrice);
    
    printf("\nUsando il metodo 2:\n");
    stampaMatrice2(matrice, RIGHE);
    
    return 0;
}
```

