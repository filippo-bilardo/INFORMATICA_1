# Array in C

Benvenuto alla sesta esercitazione del corso "C by Example". In questa sezione, esploreremo gli array in C, una struttura dati fondamentale che permette di memorizzare e manipolare collezioni di elementi dello stesso tipo.

## Indice dei contenuti

1. [Introduzione agli Array](#introduzione-agli-array)
2. [Dichiarazione e Inizializzazione](#dichiarazione-e-inizializzazione)
3. [Accesso agli Elementi](#accesso-agli-elementi)
4. [Array Multidimensionali](#array-multidimensionali)
5. [Array e Funzioni](#array-e-funzioni)
6. [Esercizi Pratici](#esercizi-pratici)

## Introduzione agli Array

Gli array sono strutture dati che consentono di memorizzare più valori dello stesso tipo sotto un unico nome di variabile. Sono particolarmente utili quando si deve gestire un grande numero di valori correlati, come un elenco di voti, temperature giornaliere o coordinate di punti.

In C, gli array hanno le seguenti caratteristiche:

- Sono a dimensione fissa (determinata al momento della dichiarazione)
- Tutti gli elementi sono dello stesso tipo di dato
- Gli elementi sono memorizzati in posizioni di memoria contigue
- L'indice del primo elemento è 0 (zero-based indexing)

## Dichiarazione e Inizializzazione

Per dichiarare un array in C, si specifica il tipo di dato degli elementi, seguito dal nome dell'array e dalla sua dimensione tra parentesi quadre.

```c
tipo nome_array[dimensione];
```

Esempio:

```c
int numeri[5]; // Dichiara un array di 5 interi
```

Gli array possono essere inizializzati al momento della dichiarazione:

```c
int numeri[5] = {10, 20, 30, 40, 50};
```

Se si forniscono meno valori di inizializzazione rispetto alla dimensione dell'array, gli elementi rimanenti vengono inizializzati a zero:

```c
int numeri[5] = {10, 20}; // Equivalente a {10, 20, 0, 0, 0}
```

È possibile omettere la dimensione se si inizializza l'array al momento della dichiarazione:

```c
int numeri[] = {10, 20, 30, 40, 50}; // La dimensione sarà 5
```

## Accesso agli Elementi

Gli elementi di un array sono accessibili tramite il loro indice, che parte da 0 per il primo elemento:

```c
int numeri[5] = {10, 20, 30, 40, 50};

printf("%d\n", numeri[0]); // Stampa 10 (primo elemento)
printf("%d\n", numeri[4]); // Stampa 50 (ultimo elemento)

numeri[2] = 35; // Modifica il terzo elemento
```

**Attenzione**: In C non c'è controllo automatico dei limiti dell'array. Accedere a un indice al di fuori dei limiti dell'array può causare comportamenti imprevedibili o crash del programma.

## Array Multidimensionali

In C è possibile creare array con più dimensioni, come matrici (array bidimensionali):

```c
int matrice[3][4]; // Matrice 3x4 (3 righe, 4 colonne)
```

Inizializzazione di un array bidimensionale:

```c
int matrice[3][4] = {
    {1, 2, 3, 4},   // Prima riga
    {5, 6, 7, 8},   // Seconda riga
    {9, 10, 11, 12} // Terza riga
};
```

Accesso agli elementi:

```c
int valore = matrice[1][2]; // Accede all'elemento nella riga 1, colonna 2 (valore 7)
```

## Array e Funzioni

Quando si passa un array a una funzione, in realtà si passa un puntatore al primo elemento dell'array. Questo significa che le modifiche apportate all'array all'interno della funzione si riflettono sull'array originale.

```c
void modifica_array(int arr[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        arr[i] *= 2; // Raddoppia ogni elemento
    }
}

int main() {
    int numeri[5] = {1, 2, 3, 4, 5};
    
    modifica_array(numeri, 5);
    
    // L'array originale è stato modificato
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]); // Stampa: 2 4 6 8 10
    }
    
    return 0;
}
```

Quando si passa un array multidimensionale a una funzione, è necessario specificare tutte le dimensioni tranne la prima:

```c
void stampa_matrice(int mat[][4], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
```

## Esercizi Pratici

1. Scrivi un programma che calcoli la somma e la media degli elementi di un array di interi.

2. Implementa un algoritmo di ordinamento (ad esempio, bubble sort) per ordinare un array di numeri in ordine crescente.

3. Crea un programma che trovi il valore massimo e minimo in un array.

4. Scrivi una funzione che inverta l'ordine degli elementi in un array.

5. Implementa un programma che utilizzi una matrice per rappresentare e risolvere un problema reale (ad esempio, un gioco del tris o una tabella di dati).

## Prossimi passi

Dopo aver completato questa esercitazione, potrai passare alla sezione successiva che tratta le stringhe in C, che sono essenzialmente array di caratteri con alcune caratteristiche speciali.

Buon apprendimento!