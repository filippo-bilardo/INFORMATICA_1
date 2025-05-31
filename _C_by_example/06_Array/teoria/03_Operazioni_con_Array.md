# Operazioni con Array in C

Gli array sono strutture dati versatili che permettono di eseguire numerose operazioni sui dati. Questa guida esplora le operazioni più comuni che si possono effettuare con gli array in C, fornendo esempi pratici e best practices.

## Operazioni di Base

### 1. Inizializzazione e Popolamento

Prima di utilizzare un array, è necessario inizializzarlo e popolarlo con dati. Ci sono diversi modi per farlo:

```c
// Inizializzazione al momento della dichiarazione
int numeri[5] = {10, 20, 30, 40, 50};

// Popolamento tramite assegnazione
int valori[5];
for (int i = 0; i < 5; i++) {
    valori[i] = i * 10;
}

// Popolamento con input dell'utente
int dati[5];
for (int i = 0; i < 5; i++) {
    printf("Inserisci il valore %d: ", i + 1);
    scanf("%d", &dati[i]);
}
```

### 2. Accesso e Modifica

L'accesso e la modifica degli elementi di un array avvengono tramite l'operatore di indicizzazione `[]`:

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Accesso a un elemento
int terzo_elemento = numeri[2]; // terzo_elemento = 30

// Modifica di un elemento
numeri[1] = 25; // Ora l'array è {10, 25, 30, 40, 50}
```

### 3. Iterazione

L'iterazione su un array è una delle operazioni più comuni, tipicamente realizzata con un ciclo for:

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Iterazione in avanti
for (int i = 0; i < 5; i++) {
    printf("%d ", numeri[i]);
}

// Iterazione all'indietro
for (int i = 4; i >= 0; i--) {
    printf("%d ", numeri[i]);
}
```

## Operazioni Statistiche

### 1. Calcolo della Somma

```c
int numeri[5] = {10, 20, 30, 40, 50};
int somma = 0;

for (int i = 0; i < 5; i++) {
    somma += numeri[i];
}

printf("Somma: %d\n", somma); // Somma: 150
```

### 2. Calcolo della Media

```c
int numeri[5] = {10, 20, 30, 40, 50};
int somma = 0;

for (int i = 0; i < 5; i++) {
    somma += numeri[i];
}

float media = (float)somma / 5;
printf("Media: %.2f\n", media); // Media: 30.00
```

### 3. Trovare il Valore Massimo e Minimo

```c
int numeri[5] = {30, 10, 50, 20, 40};

// Trovare il massimo
int massimo = numeri[0];
for (int i = 1; i < 5; i++) {
    if (numeri[i] > massimo) {
        massimo = numeri[i];
    }
}
printf("Massimo: %d\n", massimo); // Massimo: 50

// Trovare il minimo
int minimo = numeri[0];
for (int i = 1; i < 5; i++) {
    if (numeri[i] < minimo) {
        minimo = numeri[i];
    }
}
printf("Minimo: %d\n", minimo); // Minimo: 10
```

## Operazioni di Ricerca

### 1. Ricerca Lineare

La ricerca lineare è un algoritmo semplice che controlla ogni elemento dell'array fino a trovare quello cercato:

```c
int numeri[5] = {30, 10, 50, 20, 40};
int valore_cercato = 20;
int indice = -1; // -1 indica che il valore non è stato trovato

for (int i = 0; i < 5; i++) {
    if (numeri[i] == valore_cercato) {
        indice = i;
        break; // Interrompe il ciclo una volta trovato il valore
    }
}

if (indice != -1) {
    printf("Valore %d trovato all'indice %d\n", valore_cercato, indice);
} else {
    printf("Valore %d non trovato nell'array\n", valore_cercato);
}
```

### 2. Ricerca Binaria (per array ordinati)

La ricerca binaria è molto più efficiente della ricerca lineare, ma richiede che l'array sia ordinato:

```c
int numeri[5] = {10, 20, 30, 40, 50}; // Array ordinato
int valore_cercato = 30;

int sinistra = 0;
int destra = 4;
int indice = -1;

while (sinistra <= destra) {
    int medio = sinistra + (destra - sinistra) / 2;
    
    if (numeri[medio] == valore_cercato) {
        indice = medio;
        break;
    }
    
    if (numeri[medio] < valore_cercato) {
        sinistra = medio + 1;
    } else {
        destra = medio - 1;
    }
}

if (indice != -1) {
    printf("Valore %d trovato all'indice %d\n", valore_cercato, indice);
} else {
    printf("Valore %d non trovato nell'array\n", valore_cercato);
}
```

## Operazioni di Ordinamento

### 1. Bubble Sort

Il Bubble Sort è un algoritmo di ordinamento semplice ma non molto efficiente per array di grandi dimensioni:

```c
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Scambio degli elementi
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numeri[5] = {30, 10, 50, 20, 40};
    
    printf("Array originale: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    
    bubble_sort(numeri, 5);
    
    printf("\nArray ordinato: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    
    return 0;
}
```

### 2. Selection Sort

Il Selection Sort è un altro algoritmo di ordinamento semplice:

```c
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indice_minimo = i;
        
        // Trova l'indice del valore minimo nel resto dell'array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }
        
        // Scambia l'elemento corrente con il minimo trovato
        if (indice_minimo != i) {
            int temp = arr[i];
            arr[i] = arr[indice_minimo];
            arr[indice_minimo] = temp;
        }
    }
}
```

## Operazioni di Manipolazione

### 1. Inversione di un Array

```c
void inverti_array(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

int main() {
    int numeri[5] = {10, 20, 30, 40, 50};
    
    printf("Array originale: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    
    inverti_array(numeri, 5);
    
    printf("\nArray invertito: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    
    return 0;
}
```

### 2. Rotazione di un Array

```c
// Rotazione a sinistra di k posizioni
void ruota_sinistra(int arr[], int n, int k) {
    k = k % n; // Gestisce il caso in cui k > n
    
    if (k == 0) return; // Nessuna rotazione necessaria
    
    // Crea un array temporaneo per i primi k elementi
    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    
    // Sposta gli elementi rimanenti a sinistra
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }
    
    // Copia gli elementi temporanei alla fine dell'array
    for (int i = 0; i < k; i++) {
        arr[n - k + i] = temp[i];
    }
}
```

### 3. Rimozione di Duplicati

```c
// Rimuove i duplicati da un array ordinato
int rimuovi_duplicati(int arr[], int n) {
    if (n <= 1) return n; // Nessun duplicato possibile
    
    int indice = 0; // Indice per il nuovo array senza duplicati
    
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[indice]) {
            indice++;
            arr[indice] = arr[i];
        }
    }
    
    return indice + 1; // Nuova dimensione dell'array
}

int main() {
    int numeri[] = {10, 20, 20, 30, 30, 30, 40, 50, 50};
    int n = sizeof(numeri) / sizeof(numeri[0]);
    
    printf("Array originale: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numeri[i]);
    }
    
    int nuova_dimensione = rimuovi_duplicati(numeri, n);
    
    printf("\nArray senza duplicati: ");
    for (int i = 0; i < nuova_dimensione; i++) {
        printf("%d ", numeri[i]);
    }
    
    return 0;
}
```

## Operazioni su Array Multidimensionali

### 1. Somma di Righe e Colonne in una Matrice

```c
#include <stdio.h>

int main() {
    int matrice[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Calcolo della somma per ogni riga
    for (int i = 0; i < 3; i++) {
        int somma_riga = 0;
        for (int j = 0; j < 4; j++) {
            somma_riga += matrice[i][j];
        }
        printf("Somma della riga %d: %d\n", i, somma_riga);
    }
    
    // Calcolo della somma per ogni colonna
    for (int j = 0; j < 4; j++) {
        int somma_colonna = 0;
        for (int i = 0; i < 3; i++) {
            somma_colonna += matrice[i][j];
        }
        printf("Somma della colonna %d: %d\n", j, somma_colonna);
    }
    
    return 0;
}
```

### 2. Trasposta di una Matrice

```c
#include <stdio.h>

int main() {
    int matrice[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int trasposta[3][3];
    
    // Calcolo della trasposta
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            trasposta[j][i] = matrice[i][j];
        }
    }
    
    // Stampa della matrice originale
    printf("Matrice originale:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Stampa della matrice trasposta
    printf("\nMatrice trasposta:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", trasposta[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

## Operazioni Avanzate

### 1. Fusione di Due Array Ordinati

```c
void fondi_array(int arr1[], int n1, int arr2[], int n2, int risultato[]) {
    int i = 0, j = 0, k = 0;
    
    // Confronta elementi di entrambi gli array e inserisce il minore nel risultato
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            risultato[k++] = arr1[i++];
        } else {
            risultato[k++] = arr2[j++];
        }
    }
    
    // Copia gli elementi rimanenti del primo array
    while (i < n1) {
        risultato[k++] = arr1[i++];
    }
    
    // Copia gli elementi rimanenti del secondo array
    while (j < n2) {
        risultato[k++] = arr2[j++];
    }
}

int main() {
    int arr1[] = {10, 20, 30, 40, 50};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {15, 25, 35, 45};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int risultato[n1 + n2];
    
    fondi_array(arr1, n1, arr2, n2, risultato);
    
    printf("Array fuso: ");
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", risultato[i]);
    }
    
    return 0;
}
```

### 2. Implementazione di una Pila (Stack) con Array

```c
#define MAX_SIZE 100

typedef struct {
    int elementi[MAX_SIZE];
    int top;
} Pila;

void inizializza(Pila *p) {
    p->top = -1;
}

int e_vuota(Pila *p) {
    return p->top == -1;
}

int e_piena(Pila *p) {
    return p->top == MAX_SIZE - 1;
}

void push(Pila *p, int valore) {
    if (e_piena(p)) {
        printf("Errore: pila piena\n");
        return;
    }
    p->elementi[++(p->top)] = valore;
}

int pop(Pila *p) {
    if (e_vuota(p)) {
        printf("Errore: pila vuota\n");
        return -1; // Valore di errore
    }
    return p->elementi[(p->top)--];
}

int peek(Pila *p) {
    if (e_vuota(p)) {
        printf("Errore: pila vuota\n");
        return -1; // Valore di errore
    }
    return p->elementi[p->top];
}
```

## Best Practices per le Operazioni con Array

1. **Controllo dei limiti**: Verificare sempre che gli indici utilizzati siano all'interno dei limiti dell'array per evitare accessi non validi.

2. **Passaggio della dimensione**: Quando si passa un array a una funzione, passare anche la sua dimensione.

3. **Evitare la copia di interi array**: In C, non è possibile copiare direttamente un array con l'operatore di assegnazione. Utilizzare cicli o funzioni come `memcpy()`.

4. **Preferire algoritmi efficienti**: Per operazioni come la ricerca e l'ordinamento, scegliere algoritmi appropriati in base alla dimensione dell'array e alle caratteristiche dei dati.

5. **Considerare l'allocazione dinamica**: Per array di grandi dimensioni o quando la dimensione è determinata a runtime, utilizzare l'allocazione dinamica della memoria.

6. **Documentare le funzioni**: Documentare chiaramente le funzioni che operano su array, specificando i parametri, i valori di ritorno e gli eventuali effetti collaterali.

## Domande di Autovalutazione

1. Qual è la differenza tra la ricerca lineare e la ricerca binaria? Quando è preferibile utilizzare l'una rispetto all'altra?

2. Come si può implementare efficacemente la rimozione di un elemento da un array in C?

3. Quali sono i vantaggi e gli svantaggi del Bubble Sort rispetto ad altri algoritmi di ordinamento?

4. Come si può verificare se due array contengono gli stessi elementi (indipendentemente dall'ordine)?

5. Quali sono le considerazioni da tenere presenti quando si implementa una struttura dati come una pila o una coda utilizzando un array?

## Esercizi Proposti

1. Implementa una funzione che unisca due array non ordinati in un unico array ordinato, eliminando i duplicati.

2. Scrivi un programma che implementi l'algoritmo di ordinamento Quick Sort per ordinare un array di interi.

3. Crea una funzione che, dato un array di interi, restituisca un nuovo array contenente solo i numeri pari dell'array originale.

4. Implementa una coda (FIFO - First In, First Out) utilizzando un array circolare.

5. Scrivi un programma che, data una matrice quadrata, verifichi se è simmetrica rispetto alla diagonale principale.