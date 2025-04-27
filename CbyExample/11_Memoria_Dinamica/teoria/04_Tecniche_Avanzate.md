# Tecniche Avanzate di Gestione della Memoria in C

## Allocazione di Array Dinamici

Gli array dinamici sono una delle applicazioni più comuni dell'allocazione dinamica della memoria. A differenza degli array statici, la cui dimensione deve essere conosciuta in fase di compilazione, gli array dinamici possono essere creati con una dimensione determinata durante l'esecuzione del programma.

### Esempio Base di Array Dinamico

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *array;
    
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &n);
    
    // Allocazione dinamica dell'array
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < n; i++) {
        array[i] = i * 10;
    }
    
    // Utilizzo dell'array
    printf("Elementi dell'array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Liberazione della memoria
    free(array);
    
    return 0;
}
```

### Ridimensionamento di un Array Dinamico

Una delle caratteristiche più potenti degli array dinamici è la possibilità di ridimensionarli durante l'esecuzione del programma:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int dimensione_iniziale = 5;
    int nuova_dimensione = 10;
    
    // Allocazione iniziale
    array = (int *)malloc(dimensione_iniziale * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < dimensione_iniziale; i++) {
        array[i] = i * 10;
    }
    
    // Ridimensionamento dell'array
    array = (int *)realloc(array, nuova_dimensione * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: ridimensionamento fallito\n");
        return 1;
    }
    
    // Inizializzazione dei nuovi elementi
    for (int i = dimensione_iniziale; i < nuova_dimensione; i++) {
        array[i] = i * 10;
    }
    
    // Utilizzo dell'array ridimensionato
    printf("Elementi dell'array ridimensionato:\n");
    for (int i = 0; i < nuova_dimensione; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Liberazione della memoria
    free(array);
    
    return 0;
}
```

## Matrici Dinamiche

Le matrici dinamiche (array bidimensionali) possono essere implementate in diversi modi in C.

### Approccio 1: Array di Puntatori

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int righe = 3;
    int colonne = 4;
    int **matrice;
    
    // Allocazione dell'array di puntatori (righe)
    matrice = (int **)malloc(righe * sizeof(int *));
    
    if (matrice == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Allocazione di ogni riga
    for (int i = 0; i < righe; i++) {
        matrice[i] = (int *)malloc(colonne * sizeof(int));
        
        if (matrice[i] == NULL) {
            // Gestione dell'errore: liberare la memoria già allocata
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            printf("Errore: allocazione memoria fallita\n");
            return 1;
        }
    }
    
    // Inizializzazione della matrice
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] = i * colonne + j;
        }
    }
    
    // Utilizzo della matrice
    printf("Elementi della matrice:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Liberazione della memoria
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    free(matrice);
    
    return 0;
}
```

### Approccio 2: Array Contiguo

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int righe = 3;
    int colonne = 4;
    int *matrice;
    
    // Allocazione di un blocco contiguo di memoria
    matrice = (int *)malloc(righe * colonne * sizeof(int));
    
    if (matrice == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione della matrice
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            // Accesso agli elementi con aritmetica dei puntatori
            matrice[i * colonne + j] = i * colonne + j;
        }
    }
    
    // Utilizzo della matrice
    printf("Elementi della matrice:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i * colonne + j]);
        }
        printf("\n");
    }
    
    // Liberazione della memoria
    free(matrice);
    
    return 0;
}
```

## Strutture Dati Dinamiche

Le strutture dati dinamiche sono costruite utilizzando l'allocazione dinamica della memoria e i puntatori. Esempi comuni includono liste concatenate, pile, code, alberi e grafi.

### Lista Concatenata Semplice

```c
#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura del nodo
typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;

// Funzione per creare un nuovo nodo
Nodo *crea_nodo(int dato) {
    Nodo *nuovo_nodo = (Nodo *)malloc(sizeof(Nodo));
    
    if (nuovo_nodo == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        exit(1);
    }
    
    nuovo_nodo->dato = dato;
    nuovo_nodo->next = NULL;
    
    return nuovo_nodo;
}

// Funzione per inserire un nodo all'inizio della lista
Nodo *inserisci_inizio(Nodo *testa, int dato) {
    Nodo *nuovo_nodo = crea_nodo(dato);
    nuovo_nodo->next = testa;
    return nuovo_nodo;
}

// Funzione per inserire un nodo alla fine della lista
Nodo *inserisci_fine(Nodo *testa, int dato) {
    Nodo *nuovo_nodo = crea_nodo(dato);
    
    if (testa == NULL) {
        return nuovo_nodo;
    }
    
    Nodo *corrente = testa;
    while (corrente->next != NULL) {
        corrente = corrente->next;
    }
    
    corrente->next = nuovo_nodo;
    return testa;
}

// Funzione per stampare la lista
void stampa_lista(Nodo *testa) {
    Nodo *corrente = testa;
    
    printf("Lista: ");
    while (corrente != NULL) {
        printf("%d -> ", corrente->dato);
        corrente = corrente->next;
    }
    printf("NULL\n");
}

// Funzione per liberare la memoria della lista
void libera_lista(Nodo *testa) {
    Nodo *corrente = testa;
    Nodo *successivo;
    
    while (corrente != NULL) {
        successivo = corrente->next;
        free(corrente);
        corrente = successivo;
    }
}

int main() {
    Nodo *lista = NULL;
    
    // Inserimento di elementi
    lista = inserisci_inizio(lista, 10);
    lista = inserisci_inizio(lista, 20);
    lista = inserisci_fine(lista, 30);
    lista = inserisci_fine(lista, 40);
    
    // Stampa della lista
    stampa_lista(lista);
    
    // Liberazione della memoria
    libera_lista(lista);
    
    return 0;
}
```

## Gestione degli Errori di Allocazione

Una corretta gestione degli errori di allocazione è fondamentale per creare programmi robusti:

```c
#include <stdio.h>
#include <stdlib.h>

// Funzione di allocazione sicura
void *alloca_sicuro(size_t dimensione) {
    void *ptr = malloc(dimensione);
    
    if (ptr == NULL) {
        fprintf(stderr, "Errore fatale: allocazione memoria fallita\n");
        exit(EXIT_FAILURE);
    }
    
    return ptr;
}

// Funzione per allocare una matrice in modo sicuro
int **alloca_matrice(int righe, int colonne) {
    int **matrice = (int **)alloca_sicuro(righe * sizeof(int *));
    
    for (int i = 0; i < righe; i++) {
        matrice[i] = (int *)alloca_sicuro(colonne * sizeof(int));
    }
    
    return matrice;
}

// Funzione per liberare la memoria di una matrice
void libera_matrice(int **matrice, int righe) {
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

int main() {
    int righe = 3, colonne = 4;
    
    // Allocazione sicura
    int **matrice = alloca_matrice(righe, colonne);
    
    // Utilizzo della matrice
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] = i * colonne + j;
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Liberazione della memoria
    libera_matrice(matrice, righe);
    
    return 0;
}
```

## Conclusione

Le tecniche avanzate di gestione della memoria in C permettono di creare programmi flessibili ed efficienti. Tuttavia, richiedono una comprensione approfondita dei meccanismi di allocazione e deallocazione della memoria, nonché una gestione attenta degli errori. Con la pratica e l'esperienza, queste tecniche diventano strumenti potenti nel toolkit di ogni programmatore C.