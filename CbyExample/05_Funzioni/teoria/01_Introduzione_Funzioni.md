# Introduzione alle funzioni

## Concetto di funzione

In programmazione, una **funzione** è un blocco di codice che esegue un compito specifico e può essere richiamato (o "chiamato") da altre parti del programma. Le funzioni sono uno dei concetti fondamentali della programmazione strutturata e rappresentano un modo per organizzare il codice in unità logiche e riutilizzabili.

Una funzione in C è composta da:

- Un **nome** che identifica la funzione
- Una lista di **parametri** (opzionali) che la funzione può accettare
- Un **tipo di ritorno** che specifica il tipo di dato che la funzione restituisce
- Un **corpo** che contiene le istruzioni da eseguire

La sintassi generale di una funzione in C è:

```c
tipo_ritorno nome_funzione(lista_parametri) {
    // corpo della funzione
    // istruzioni da eseguire
    return valore; // opzionale, dipende dal tipo di ritorno
}
```

Esempio di una semplice funzione che calcola il quadrato di un numero:

```c
int quadrato(int numero) {
    return numero * numero;
}
```

## Vantaggi dell'uso delle funzioni

L'utilizzo delle funzioni offre numerosi vantaggi nella programmazione:

### 1. Modularità e riutilizzo del codice

Le funzioni permettono di suddividere un programma complesso in moduli più piccoli e gestibili. Ogni funzione si occupa di un compito specifico, rendendo il codice più organizzato e comprensibile. Inoltre, una volta definita, una funzione può essere richiamata più volte in diverse parti del programma, evitando la duplicazione del codice.

```c
// Funzione riutilizzabile per calcolare l'area di un rettangolo
float area_rettangolo(float base, float altezza) {
    return base * altezza;
}

int main() {
    // Riutilizzo della stessa funzione per calcolare diverse aree
    float area1 = area_rettangolo(5.0, 3.0);
    float area2 = area_rettangolo(7.5, 2.0);
    float area3 = area_rettangolo(10.0, 4.5);
    
    // Resto del codice...
    return 0;
}
```

### 2. Astrazione e semplificazione

Le funzioni permettono di nascondere i dettagli implementativi di un'operazione, fornendo un'interfaccia semplice per utilizzarla. Chi utilizza la funzione non deve conoscere come essa è implementata internamente, ma solo come chiamarla e quali risultati aspettarsi.

```c
// L'utente della funzione non deve conoscere l'algoritmo di ordinamento
void ordina_array(int arr[], int dimensione) {
    // Implementazione dell'algoritmo di ordinamento (es. bubble sort)
    // ...
}

int main() {
    int numeri[5] = {5, 2, 9, 1, 7};
    
    // Chiamata semplice, senza preoccuparsi dei dettagli implementativi
    ordina_array(numeri, 5);
    
    // Resto del codice...
    return 0;
}
```

### 3. Leggibilità e manutenibilità

Suddividere il codice in funzioni con nomi significativi migliora notevolmente la leggibilità del programma. Inoltre, se è necessario modificare un particolare comportamento del programma, è sufficiente modificare la funzione corrispondente, senza dover cercare e cambiare il codice in più punti.

```c
// Funzioni con nomi significativi migliorano la leggibilità
void leggi_dati_utente();
void elabora_dati();
void visualizza_risultati();

int main() {
    leggi_dati_utente();
    elabora_dati();
    visualizza_risultati();
    return 0;
}
```

### 4. Facilità di debug e testing

Le funzioni permettono di isolare e testare singole parti del programma, facilitando l'individuazione e la correzione degli errori. È possibile verificare il corretto funzionamento di una funzione indipendentemente dal resto del programma.

```c
// Funzione che può essere testata isolatamente
int calcola_fattoriale(int n) {
    if (n <= 1) return 1;
    return n * calcola_fattoriale(n - 1);
}

// Funzione di test
void test_fattoriale() {
    if (calcola_fattoriale(0) != 1) printf("Test fallito per n=0\n");
    if (calcola_fattoriale(1) != 1) printf("Test fallito per n=1\n");
    if (calcola_fattoriale(5) != 120) printf("Test fallito per n=5\n");
    printf("Test completati\n");
}
```

## Struttura di un programma C con funzioni

Un programma C ben strutturato è tipicamente organizzato in più funzioni, ciascuna con un compito specifico. La funzione `main()` è il punto di ingresso del programma e coordina le chiamate alle altre funzioni.

Ecco un esempio di struttura di un programma C che utilizza funzioni:

```c
#include <stdio.h>

// Prototipi delle funzioni
void benvenuto();
int leggi_numero();
int calcola_quadrato(int n);
void visualizza_risultato(int numero, int quadrato);

// Funzione principale
int main() {
    benvenuto();
    
    int numero = leggi_numero();
    int risultato = calcola_quadrato(numero);
    
    visualizza_risultato(numero, risultato);
    
    return 0;
}

// Definizioni delle funzioni
void benvenuto() {
    printf("Benvenuto nel programma di calcolo del quadrato!\n");
}

int leggi_numero() {
    int n;
    printf("Inserisci un numero intero: ");
    scanf("%d", &n);
    return n;
}

int calcola_quadrato(int n) {
    return n * n;
}

void visualizza_risultato(int numero, int quadrato) {
    printf("Il quadrato di %d è %d\n", numero, quadrato);
}
```

In questo esempio:

1. All'inizio del programma sono dichiarati i **prototipi delle funzioni**, che informano il compilatore dell'esistenza delle funzioni prima che vengano effettivamente definite.

2. La funzione `main()` coordina il flusso del programma, chiamando le altre funzioni nell'ordine appropriato.

3. Ogni funzione ha un compito specifico e ben definito:
   - `benvenuto()` visualizza un messaggio di benvenuto
   - `leggi_numero()` si occupa dell'input dell'utente
   - `calcola_quadrato()` esegue il calcolo matematico
   - `visualizza_risultato()` mostra il risultato all'utente

Questa struttura modulare rende il programma più leggibile, manutenibile e facilita la collaborazione tra più sviluppatori.

## Esempi pratici di utilizzo delle funzioni

### Esempio 1: Calcolo del massimo tra due numeri

```c
#include <stdio.h>

// Funzione che restituisce il massimo tra due numeri
int massimo(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    int num1, num2;
    
    printf("Inserisci due numeri: ");
    scanf("%d %d", &num1, &num2);
    
    int max = massimo(num1, num2);
    printf("Il massimo tra %d e %d è %d\n", num1, num2, max);
    
    return 0;
}
```

### Esempio 2: Conversione di temperatura

```c
#include <stdio.h>

// Funzione per convertire da Celsius a Fahrenheit
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Funzione per convertire da Fahrenheit a Celsius
float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main() {
    float temperatura;
    char scelta;
    
    printf("Vuoi convertire da Celsius a Fahrenheit (C) o viceversa (F)? ");
    scanf(" %c", &scelta);
    
    printf("Inserisci la temperatura: ");
    scanf("%f", &temperatura);
    
    if (scelta == 'C' || scelta == 'c') {
        float fahrenheit = celsius_to_fahrenheit(temperatura);
        printf("%.2f°C equivale a %.2f°F\n", temperatura, fahrenheit);
    } else if (scelta == 'F' || scelta == 'f') {
        float celsius = fahrenheit_to_celsius(temperatura);
        printf("%.2f°F equivale a %.2f°C\n", temperatura, celsius);
    } else {
        printf("Scelta non valida!\n");
    }
    
    return 0;
}
```

### Esempio 3: Calcolo del fattoriale

```c
#include <stdio.h>

// Funzione per calcolare il fattoriale di un numero
unsigned long fattoriale(int n) {
    unsigned long risultato = 1;
    
    for (int i = 1; i <= n; i++) {
        risultato *= i;
    }
    
    return risultato;
}

int main() {
    int numero;
    
    printf("Inserisci un numero intero non negativo: ");
    scanf("%d", &numero);
    
    if (numero < 0) {
        printf("Il fattoriale è definito solo per numeri non negativi!\n");
    } else {
        printf("%d! = %lu\n", numero, fattoriale(numero));
    }
    
    return 0;
}
```

## Esercizi proposti

1. Scrivi una funzione che calcoli e restituisca l'area di un cerchio, dato il raggio come parametro.

2. Implementa una funzione che verifichi se un numero è primo e restituisca 1 se è primo, 0 altrimenti.

3. Crea una funzione che calcoli la potenza di un numero (base^esponente), dove sia la base che l'esponente sono interi.

4. Scrivi un programma che utilizzi funzioni separate per calcolare il perimetro e l'area di diverse figure geometriche (rettangolo, triangolo, cerchio).

5. Implementa una funzione che conti il numero di cifre in un numero intero.

## Domande di autovalutazione

1. Quali sono i principali vantaggi dell'utilizzo delle funzioni nella programmazione?

2. Qual è la differenza tra una funzione che restituisce un valore e una funzione void?

3. Perché è importante dare nomi significativi alle funzioni?

4. Come si può strutturare un programma complesso utilizzando le funzioni?

5. Quali sono le componenti principali di una funzione in C?

6. In che modo le funzioni migliorano la manutenibilità del codice?

7. Qual è il ruolo della funzione main() in un programma C?

8. Come si può determinare se un compito dovrebbe essere implementato come una funzione separata o incluso nel codice principale?