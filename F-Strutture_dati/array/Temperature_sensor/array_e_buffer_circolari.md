# Array e Buffer Circolari in C/C++

## 1. Introduzione agli Array

Gli array sono strutture dati fondamentali che consentono di memorizzare una collezione di elementi dello stesso tipo in posizioni di memoria contigue. Rappresentano uno dei costrutti più utilizzati nella programmazione, permettendo di gestire in modo efficiente grandi quantità di dati.

### 1.1 Dichiarazione e Inizializzazione

#### Dichiarazione semplice
```c
// Dichiarazione di un array di 10 interi
int numeri[10];

// Dichiarazione di un array di caratteri
char lettere[26];

// Dichiarazione di un array di float
float temperature[24];
```

#### Inizializzazione diretta
```c
// Inizializzazione con valori specifici
int numeri[5] = {10, 20, 30, 40, 50};

// Inizializzazione parziale (gli elementi rimanenti sono inizializzati a 0)
int parziale[10] = {1, 2, 3};

// Inizializzazione di un array di caratteri (stringa)
char nome[6] = {'M', 'a', 'r', 'i', 'o', '\0'};
// oppure più semplicemente
char nome[] = "Mario";
```

#### Inizializzazione implicita
```c
// Il compilatore determina la dimensione in base ai valori forniti
int numeri[] = {5, 10, 15, 20, 25};

// Array di caratteri con dimensione implicita
char vocali[] = {'a', 'e', 'i', 'o', 'u'};
```

### 1.2 Accesso agli Elementi

Gli elementi di un array sono indicizzati a partire da 0.

```c
int numeri[5] = {10, 20, 30, 40, 50};

// Accesso al primo elemento (indice 0)
int primo = numeri[0];  // primo = 10

// Accesso al terzo elemento (indice 2)
int terzo = numeri[2];  // terzo = 30

// Modifica del quinto elemento (indice 4)
numeri[4] = 55;  // ora numeri = {10, 20, 30, 40, 55}
```

### 1.3 Iterazione sugli Array

#### Utilizzo del ciclo for
```c
int numeri[5] = {10, 20, 30, 40, 50};
int somma = 0;

// Somma di tutti gli elementi
for (int i = 0; i < 5; i++) {
    somma += numeri[i];
}
// somma = 150
```

#### Utilizzo del ciclo for-each (C++11 e successivi)
```cpp
int numeri[] = {10, 20, 30, 40, 50};
int somma = 0;

// Somma con for-each
for (int numero : numeri) {
    somma += numero;
}
// somma = 150
```

### 1.4 Array Multidimensionali

#### Array bidimensionali (matrici)
```c
// Dichiarazione di una matrice 3x3
int matrice[3][3];

// Inizializzazione di una matrice 2x3
int griglia[2][3] = {
    {1, 2, 3},  // prima riga
    {4, 5, 6}   // seconda riga
};

// Accesso agli elementi
int elemento = griglia[1][2];  // elemento = 6 (seconda riga, terza colonna)
```

#### Iterazione su array bidimensionali
```c
int matrice[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Stampa di tutti gli elementi
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        printf("%d ", matrice[i][j]);
    }
    printf("\n");
}
```

#### Array tridimensionali e oltre
```c
// Array tridimensionale 2x3x4
int cubo[2][3][4];

// Inizializzazione di un elemento
cubo[1][2][3] = 42;
```

### 1.5 Passaggio di Array alle Funzioni

#### Passaggio di array monodimensionali
```c
// Dichiarazione della funzione
void elaboraArray(int arr[], int dimensione);
// oppure
void elaboraArray(int* arr, int dimensione);

// Implementazione
void elaboraArray(int arr[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        arr[i] *= 2;  // Raddoppia ogni elemento
    }
}

// Utilizzo
int numeri[5] = {1, 2, 3, 4, 5};
elaboraArray(numeri, 5);
// Ora numeri = {2, 4, 6, 8, 10}
```

#### Passaggio di array bidimensionali
```c
// Per array bidimensionali, è necessario specificare almeno la seconda dimensione
void elaboraMatrice(int matrice[][3], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < 3; j++) {
            matrice[i][j]++;
        }
    }
}

// Utilizzo
int griglia[2][3] = {{1, 2, 3}, {4, 5, 6}};
elaboraMatrice(griglia, 2);
// Ora griglia = {{2, 3, 4}, {5, 6, 7}}
```

### 1.6 Array Dinamici

#### Allocazione dinamica in C
```c
// Allocazione di un array di 10 interi
int* numeri = (int*)malloc(10 * sizeof(int));

// Inizializzazione
for (int i = 0; i < 10; i++) {
    numeri[i] = i * 10;
}

// Liberazione della memoria
free(numeri);
```

#### Allocazione dinamica in C++
```cpp
// Allocazione di un array di 10 interi
int* numeri = new int[10];

// Inizializzazione
for (int i = 0; i < 10; i++) {
    numeri[i] = i * 10;
}

// Liberazione della memoria
delete[] numeri;
```

#### Utilizzo di std::vector in C++
```cpp
#include <vector>

// Creazione di un vector
std::vector<int> numeri = {10, 20, 30, 40, 50};

// Aggiunta di elementi
numeri.push_back(60);

// Accesso agli elementi
int terzo = numeri[2];  // terzo = 30

// Iterazione
for (int numero : numeri) {
    std::cout << numero << " ";
}
```

## 2. Buffer Circolari

### 2.1 Concetto e Principi

Un buffer circolare (o ring buffer) è una struttura dati di dimensione fissa che si comporta come se gli estremi fossero connessi. Quando il buffer è pieno, i nuovi dati sovrascrivono quelli più vecchi. Questa struttura è particolarmente utile per applicazioni di streaming, gestione di dati in tempo reale e implementazione di code FIFO (First-In-First-Out) con memoria limitata.

#### Caratteristiche principali:
- **Dimensione fissa**: occupa uno spazio di memoria predefinito
- **Comportamento circolare**: quando si raggiunge la fine, si ricomincia dall'inizio
- **Efficienza**: operazioni di inserimento e rimozione in tempo O(1)
- **Gestione della memoria**: sovrascrittura automatica dei dati più vecchi

### 2.2 Componenti di un Buffer Circolare Semplice

Un buffer circolare semplice basato su array richiede solo pochi componenti essenziali:

- **Array di dati**: memorizza i valori
- **Indice**: indica la posizione in cui inserire il prossimo elemento
- **Contatore**: tiene traccia del numero di elementi presenti

### 2.3 Implementazione Semplice con Array

```c
// Definizione della dimensione del buffer
#define DIMENSIONE_BUFFER 10

// Array per memorizzare i dati
float buffer[DIMENSIONE_BUFFER];

// Indice corrente per l'inserimento
int indice = 0;

// Contatore degli elementi presenti
int conteggio = 0;

// Inizializzazione del buffer
void inizializzaBuffer() {
    for (int i = 0; i < DIMENSIONE_BUFFER; i++) {
        buffer[i] = 0.0;
    }
    indice = 0;
    conteggio = 0;
}

// Inserimento di un elemento nel buffer
void inserisciElemento(float valore) {
    // Memorizza il valore nella posizione corrente
    buffer[indice] = valore;
    
    // Aggiorna l'indice in modo circolare
    indice = (indice + 1) % DIMENSIONE_BUFFER;
    
    // Aggiorna il conteggio degli elementi
    if (conteggio < DIMENSIONE_BUFFER) {
        conteggio++;
    }
}

// Calcolo della media dei valori nel buffer
float calcolaMedia() {
    if (conteggio == 0) {
        return 0.0; // Buffer vuoto
    }
    
    float somma = 0.0;
    for (int i = 0; i < conteggio; i++) {
        somma += buffer[i];
    }
    return somma / conteggio;
}
```

Questa implementazione è semplice ma efficace per molti casi d'uso. Quando il buffer è pieno (conteggio = DIMENSIONE_BUFFER), i nuovi valori sovrascrivono automaticamente quelli più vecchi grazie all'operazione modulo sull'indice.

### 2.4 Esempio Pratico: Buffer di Letture di Temperatura

Un caso d'uso comune per i buffer circolari è la memorizzazione di letture di sensori, come in un sistema di monitoraggio della temperatura:

```c
#define DIMENSIONE_BUFFER 10
float bufferTemperatura[DIMENSIONE_BUFFER];
int indiceBuffer = 0;
int conteggioBuffer = 0;

// Inserimento di un nuovo valore di temperatura
void memorizzaTemperatura(float temperatura) {
  bufferTemperatura[indiceBuffer] = temperatura;
  
  // Aggiorna l'indice e il conteggio del buffer
  indiceBuffer = (indiceBuffer + 1) % DIMENSIONE_BUFFER;
  if (conteggioBuffer < DIMENSIONE_BUFFER) {
    conteggioBuffer++;
  }
}

// Calcolo della temperatura media
float calcolaTemperaturaMedia() {
  if (conteggioBuffer == 0) {
    return 0.0; // Nessuna lettura disponibile
  }
  
  float somma = 0.0;
  for (int i = 0; i < conteggioBuffer; i++) {
    somma += bufferTemperatura[i];
  }
  return somma / conteggioBuffer;
}
```

Questo esempio mostra come un buffer circolare possa essere utilizzato per calcolare la media mobile delle ultime N letture di temperatura.

### 2.5 Vantaggi e Svantaggi

#### Vantaggi
- **Memoria limitata**: utilizza uno spazio fisso indipendentemente dal tempo di esecuzione
- **Efficienza**: operazioni di inserimento e rimozione in tempo O(1)
- **Sovrascrittura automatica**: i dati più vecchi vengono automaticamente sostituiti
- **Ideale per streaming**: perfetto per applicazioni di elaborazione continua dei dati

#### Svantaggi
- **Dimensione fissa**: non può crescere dinamicamente come altre strutture dati
- **Perdita di dati**: i dati più vecchi vengono persi quando il buffer è pieno

### 2.6 Considerazioni di Implementazione

#### Gestione dell'Indice
L'operazione modulo `%` è fondamentale per l'implementazione di un buffer circolare. Essa permette di "avvolgere" l'indice quando raggiunge la fine dell'array:

```c
// Avanzamento dell'indice con wrap-around
indice = (indice + 1) % DIMENSIONE_BUFFER;
```

#### Ottimizzazione per Microcontrollori
Su sistemi embedded con risorse limitate, è possibile ottimizzare l'implementazione:

```c
// Utilizzo di dimensioni che sono potenze di 2
#define DIMENSIONE_BUFFER 16

// Sostituzione dell'operazione modulo con AND bit a bit
// (funziona solo se DIMENSIONE_BUFFER è una potenza di 2)
indice = (indice + 1) & (DIMENSIONE_BUFFER - 1);
```

## 3. Conclusioni

Gli array sono strutture dati fondamentali che offrono accesso diretto agli elementi e memoria contigua, rendendoli efficienti per molte applicazioni. I buffer circolari, basati su array, forniscono un meccanismo elegante per gestire flussi di dati continui con memoria limitata.

La comprensione approfondita di queste strutture dati e delle loro implementazioni è essenziale per sviluppare software efficiente, specialmente in contesti con risorse limitate come i sistemi embedded.

## 4. Riferimenti

- Kernighan, B. W., & Ritchie, D. M. (1988). *The C Programming Language*.
- Stroustrup, B. (2013). *The C++ Programming Language*.
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms*.
- McConnell, S. (2004). *Code Complete: A Practical Handbook of Software Construction*.