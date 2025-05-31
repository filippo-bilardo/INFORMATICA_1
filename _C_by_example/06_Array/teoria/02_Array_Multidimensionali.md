# Array Multidimensionali in C

Gli array multidimensionali sono strutture dati che estendono il concetto di array a più dimensioni. In C, è possibile creare array con due, tre o più dimensioni, anche se gli array bidimensionali (matrici) sono i più comuni. Questa guida esplora in dettaglio gli array multidimensionali in C.

## Concetto di Array Multidimensionale

Un array multidimensionale può essere visto come un "array di array". Ad esempio, un array bidimensionale è un array i cui elementi sono a loro volta array monodimensionali.

In termini di memoria, gli array multidimensionali in C sono memorizzati in modo contiguo utilizzando l'ordinamento per righe (row-major order), il che significa che gli elementi di una riga sono memorizzati uno dopo l'altro.

## Dichiarazione di Array Bidimensionali

La sintassi per dichiarare un array bidimensionale in C è:

```c
tipo nome_array[righe][colonne];
```

Dove:
- `tipo` è il tipo di dato degli elementi dell'array
- `nome_array` è l'identificatore dell'array
- `righe` è il numero di righe
- `colonne` è il numero di colonne

Esempi di dichiarazione:

```c
int matrice[3][4];         // Matrice 3x4 (3 righe, 4 colonne)
float temperature[7][24];  // 7 giorni, 24 ore per giorno
char scacchiera[8][8];     // Scacchiera 8x8
```

## Inizializzazione di Array Bidimensionali

Esistono diversi modi per inizializzare un array bidimensionale in C:

### 1. Inizializzazione al momento della dichiarazione

```c
int matrice[3][4] = {
    {1, 2, 3, 4},   // Prima riga
    {5, 6, 7, 8},   // Seconda riga
    {9, 10, 11, 12} // Terza riga
};
```

### 2. Inizializzazione senza parentesi graffe interne

```c
int matrice[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
```

In questo caso, gli elementi vengono assegnati riga per riga. Questo è equivalente all'esempio precedente.

### 3. Inizializzazione parziale

Se si forniscono meno valori di inizializzazione rispetto alla dimensione dell'array, gli elementi rimanenti vengono inizializzati a zero:

```c
int matrice[3][4] = {
    {1, 2},        // Gli elementi mancanti sono 0
    {5},           // Gli elementi mancanti sono 0
    {9, 10, 11}    // L'elemento mancante è 0
};
```

### 4. Inizializzazione con dimensione implicita

È possibile omettere la prima dimensione se si inizializza l'array al momento della dichiarazione:

```c
int matrice[][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
}; // La prima dimensione sarà 3
```

Non è possibile omettere le dimensioni successive alla prima.

## Accesso agli Elementi di un Array Bidimensionale

Gli elementi di un array bidimensionale sono accessibili utilizzando due indici:

```c
int matrice[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Accesso in lettura
int elemento = matrice[1][2]; // elemento = 7 (riga 1, colonna 2)

// Accesso in scrittura
matrice[0][3] = 100; // Modifica l'elemento nella riga 0, colonna 3
```

## Iterazione su Array Bidimensionali

Per elaborare tutti gli elementi di un array bidimensionale, si utilizzano tipicamente due cicli for annidati:

```c
int matrice[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Iterazione su tutti gli elementi
for (int i = 0; i < 3; i++) {      // Ciclo sulle righe
    for (int j = 0; j < 4; j++) {  // Ciclo sulle colonne
        printf("%d ", matrice[i][j]);
    }
    printf("\n"); // Nuova riga dopo ogni riga della matrice
}
```

## Passaggio di Array Bidimensionali alle Funzioni

Quando si passa un array bidimensionale a una funzione, è necessario specificare tutte le dimensioni tranne la prima:

```c
void stampa_matrice(int mat[][4], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", mat[i][j]);
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
    
    stampa_matrice(matrice, 3);
    
    return 0;
}
```

È necessario specificare la seconda dimensione (e tutte le successive) perché il compilatore ha bisogno di sapere come calcolare l'offset in memoria per accedere agli elementi.

## Array Tridimensionali e Oltre

È possibile estendere il concetto a tre o più dimensioni:

```c
// Array tridimensionale (3D)
int cubo[2][3][4];

// Inizializzazione
int cubo[2][3][4] = {
    { // Primo "piano"
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    },
    { // Secondo "piano"
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
    }
};

// Accesso agli elementi
int valore = cubo[1][0][2]; // valore = 15
```

L'accesso e l'iterazione seguono lo stesso principio degli array bidimensionali, ma con un ciclo aggiuntivo per ogni dimensione.

## Applicazioni Pratiche degli Array Multidimensionali

### 1. Elaborazione di Immagini

Le immagini possono essere rappresentate come array bidimensionali, dove ogni elemento rappresenta un pixel:

```c
// Immagine in scala di grigi (0-255)
unsigned char immagine[1024][768];

// Immagine a colori RGB
unsigned char immagine_rgb[1024][768][3]; // 3 canali: R, G, B
```

### 2. Giochi da Tavolo

I giochi da tavolo come scacchi, dama o tris possono essere rappresentati utilizzando array bidimensionali:

```c
// Scacchiera (0 = vuoto, valori positivi = pezzi bianchi, valori negativi = pezzi neri)
int scacchiera[8][8];

// Tris (0 = vuoto, 1 = X, 2 = O)
int tris[3][3] = {0}; // Inizializza tutti a zero
```

### 3. Dati Tabellari

Gli array bidimensionali sono ideali per rappresentare dati in formato tabellare:

```c
// Temperature giornaliere per una settimana (7 giorni, 24 ore)
float temperature[7][24];

// Tabella di vendite per 12 mesi e 5 prodotti
int vendite[12][5];
```

### 4. Sistemi di Equazioni Lineari

Le matrici sono utilizzate per rappresentare e risolvere sistemi di equazioni lineari:

```c
// Matrice dei coefficienti per un sistema di 3 equazioni con 3 incognite
float coefficienti[3][3] = {
    {2.0, 1.0, -1.0},
    {-3.0, -1.0, 2.0},
    {-2.0, 1.0, 2.0}
};

// Vettore dei termini noti
float termini_noti[3] = {8.0, -11.0, -3.0};
```

## Limitazioni e Considerazioni

1. **Consumo di memoria**: Gli array multidimensionali possono consumare molta memoria, specialmente quelli con molte dimensioni o di grandi dimensioni.

2. **Allocazione contigua**: In C, gli array multidimensionali sono allocati in modo contiguo, il che può limitare la dimensione massima a causa dei vincoli di memoria.

3. **Passaggio alle funzioni**: Il passaggio di array multidimensionali alle funzioni richiede la specifica di tutte le dimensioni tranne la prima.

4. **Nessun controllo dei limiti**: Come per gli array monodimensionali, C non verifica se gli indici utilizzati sono validi.

## Best Practices

1. **Utilizzare costanti simboliche per le dimensioni**: Rende il codice più manutenibile.

```c
#define RIGHE 3
#define COLONNE 4

int matrice[RIGHE][COLONNE];
```

2. **Considerare l'allocazione dinamica per array di grandi dimensioni**: Per array molto grandi o quando le dimensioni sono determinate a runtime, è preferibile utilizzare l'allocazione dinamica.

3. **Inizializzare gli array**: Inizializzare sempre gli array per evitare valori casuali.

4. **Verificare i limiti**: Controllare sempre che gli indici utilizzati siano all'interno dei limiti dell'array.

## Domande di Autovalutazione

1. Come viene memorizzato un array bidimensionale in memoria in C?

2. Perché è necessario specificare la seconda dimensione (e le successive) quando si passa un array multidimensionale a una funzione?

3. Qual è la differenza tra `int a[2][3]` e `int a[3][2]`?

4. Come si può calcolare la somma di tutti gli elementi di una matrice?

5. Quali sono i vantaggi e gli svantaggi degli array multidimensionali rispetto ad altre strutture dati?

## Esercizi Proposti

1. Scrivi un programma che crei una matrice 3x3, la riempia con valori inseriti dall'utente e poi calcoli e visualizzi la somma di ogni riga e di ogni colonna.

2. Implementa un programma che moltiplichi due matrici di dimensioni compatibili.

3. Crea un programma che implementi il gioco del tris (tic-tac-toe) utilizzando un array bidimensionale per rappresentare la griglia di gioco.

4. Scrivi una funzione che prenda una matrice quadrata come input e calcoli la sua trasposta (scambiando righe e colonne).

5. Implementa un programma che utilizzi un array tridimensionale per memorizzare le temperature di 5 città per 7 giorni della settimana e 24 ore al giorno, e poi calcoli la temperatura media per ogni città e per ogni giorno.