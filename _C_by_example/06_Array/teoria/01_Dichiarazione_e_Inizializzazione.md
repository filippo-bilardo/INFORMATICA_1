# Dichiarazione e Inizializzazione degli Array in C

Gli array sono strutture dati fondamentali in C che permettono di memorizzare più valori dello stesso tipo sotto un unico nome di variabile. Questa guida esplora in dettaglio come dichiarare, inizializzare e utilizzare gli array in C.

## Concetto di Array

Un array è una collezione di elementi dello stesso tipo, memorizzati in posizioni di memoria contigue. Ogni elemento dell'array è accessibile tramite un indice, che in C inizia sempre da 0.

Caratteristiche principali degli array in C:

- Dimensione fissa (determinata al momento della dichiarazione)
- Elementi omogenei (tutti dello stesso tipo)
- Memorizzazione contigua in memoria
- Indicizzazione a base zero (il primo elemento ha indice 0)

## Dichiarazione di un Array

La sintassi per dichiarare un array in C è:

```c
tipo nome_array[dimensione];
```

Dove:
- `tipo` è il tipo di dato degli elementi dell'array
- `nome_array` è l'identificatore dell'array
- `dimensione` è il numero di elementi che l'array può contenere

Esempi di dichiarazione:

```c
int numeri[10];         // Array di 10 interi
float temperature[7];   // Array di 7 numeri in virgola mobile
char caratteri[26];     // Array di 26 caratteri
```

**Importante**: La dimensione dell'array deve essere una costante o un'espressione costante (valutabile al momento della compilazione).

```c
// Corretto
const int DIMENSIONE = 10;
int array[DIMENSIONE];

// Errato (in C standard)
int n;
scanf("%d", &n);
int array[n]; // Errore in C89/C90, valido in C99 come VLA (Variable Length Array)
```

## Inizializzazione degli Array

Esistono diversi modi per inizializzare un array in C:

### 1. Inizializzazione al momento della dichiarazione

```c
int numeri[5] = {10, 20, 30, 40, 50};
```

### 2. Inizializzazione parziale

Se si forniscono meno valori di inizializzazione rispetto alla dimensione dell'array, gli elementi rimanenti vengono inizializzati a zero:

```c
int numeri[5] = {10, 20}; // Equivalente a {10, 20, 0, 0, 0}
```

### 3. Inizializzazione con dimensione implicita

È possibile omettere la dimensione se si inizializza l'array al momento della dichiarazione:

```c
int numeri[] = {10, 20, 30, 40, 50}; // La dimensione sarà 5
```

### 4. Inizializzazione con zero

Per inizializzare tutti gli elementi a zero:

```c
int numeri[5] = {0}; // Tutti gli elementi sono inizializzati a 0
```

### 5. Inizializzazione di elementi specifici (C99)

In C99, è possibile inizializzare elementi specifici utilizzando i designatori:

```c
int numeri[10] = {[0] = 1, [5] = 50, [9] = 100};
// Equivalente a {1, 0, 0, 0, 0, 50, 0, 0, 0, 100}
```

## Accesso agli Elementi dell'Array

Gli elementi di un array sono accessibili tramite il loro indice, che parte da 0 per il primo elemento:

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Accesso in lettura
int primo = numeri[0];   // primo = 10
int ultimo = numeri[4];  // ultimo = 50

// Accesso in scrittura
numeri[2] = 35;          // Modifica il terzo elemento
```

**Attenzione**: In C non c'è controllo automatico dei limiti dell'array. Accedere a un indice al di fuori dei limiti dell'array è un errore che può causare comportamenti imprevedibili o crash del programma.

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Accesso fuori dai limiti - PERICOLOSO!
int valore = numeri[10];  // Comportamento indefinito
numeri[-1] = 100;         // Comportamento indefinito
```

## Dimensione di un Array

Per calcolare il numero di elementi in un array, si può utilizzare l'operatore `sizeof`:

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Calcolo della dimensione dell'array
int dimensione = sizeof(numeri) / sizeof(numeri[0]);
printf("L'array contiene %d elementi\n", dimensione); // Stampa: 5
```

Questa tecnica funziona solo quando l'array è accessibile direttamente, non quando viene passato a una funzione (dove decade a puntatore).

## Iterazione sugli Elementi di un Array

Il modo più comune per elaborare tutti gli elementi di un array è utilizzare un ciclo:

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Iterazione con ciclo for
for (int i = 0; i < 5; i++) {
    printf("%d: %d\n", i, numeri[i]);
}

// Calcolo della somma degli elementi
int somma = 0;
for (int i = 0; i < 5; i++) {
    somma += numeri[i];
}
printf("Somma: %d\n", somma);
```

## Array di Caratteri e Stringhe

Un caso speciale di array è l'array di caratteri, che può essere utilizzato per rappresentare stringhe:

```c
char nome[10] = {'M', 'a', 'r', 'i', 'o', '\0'};
```

In C, le stringhe sono array di caratteri terminati dal carattere nullo ('\0'). C fornisce una sintassi più conveniente per inizializzare le stringhe:

```c
char nome[10] = "Mario"; // Il compilatore aggiunge automaticamente '\0'
```

## Limitazioni degli Array in C

1. **Dimensione fissa**: Una volta dichiarato, la dimensione dell'array non può essere modificata (eccetto per i VLA in C99).

2. **Nessun controllo dei limiti**: C non verifica se gli indici utilizzati sono validi.

3. **Nessuna operazione integrata**: Non ci sono operazioni integrate per confrontare o copiare interi array.

4. **Nessuna informazione sulla dimensione quando passati a funzioni**: Quando un array viene passato a una funzione, la dimensione deve essere passata separatamente.

## Best Practices

1. **Inizializzare sempre gli array**: Gli array non inizializzati contengono valori casuali.

2. **Verificare i limiti**: Controllare sempre che gli indici utilizzati siano all'interno dei limiti dell'array.

3. **Utilizzare costanti simboliche per le dimensioni**: Rende il codice più manutenibile.

```c
#define DIMENSIONE_MAX 100

int main() {
    int dati[DIMENSIONE_MAX];
    // ...
    return 0;
}
```

4. **Evitare array troppo grandi sullo stack**: Gli array di grandi dimensioni dovrebbero essere allocati dinamicamente (con `malloc`) per evitare overflow dello stack.

## Domande di Autovalutazione

1. Qual è la differenza tra `int a[5] = {0};` e `int a[5];`?

2. Come si può calcolare la dimensione di un array in C?

3. Cosa succede se si tenta di accedere a un elemento oltre i limiti di un array?

4. Come si può inizializzare un array con valori non consecutivi?

5. Perché è importante il carattere nullo ('\0') negli array di caratteri?

## Esercizi Proposti

1. Scrivi un programma che chieda all'utente di inserire 10 numeri interi, li memorizzi in un array e poi calcoli e visualizzi la somma, la media, il valore massimo e il valore minimo.

2. Crea un programma che generi 100 numeri casuali tra 1 e 10, li memorizzi in un array e poi conti quante volte appare ciascun numero.

3. Implementa un programma che legga una sequenza di caratteri dall'utente, la memorizzi in un array e poi la visualizzi al contrario.

4. Scrivi una funzione che prenda un array di interi e la sua dimensione come parametri e rimuova tutti i duplicati, restituendo la nuova dimensione dell'array.

5. Crea un programma che utilizzi un array per implementare una coda (FIFO - First In, First Out) con operazioni di inserimento (enqueue) e rimozione (dequeue).