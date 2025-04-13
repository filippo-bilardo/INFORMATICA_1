# D.2. Cicli ed iterazioni

I cicli sono strutture di controllo che permettono di eseguire ripetutamente un blocco di codice fino a quando una condizione specificata rimane vera o per un numero predefinito di volte. Sono fondamentali per automatizzare compiti ripetitivi e per elaborare collezioni di dati.

## Ciclo `while`

Il ciclo `while` esegue un blocco di codice fintanto che una condizione specificata è vera. La condizione viene valutata prima di ogni iterazione.

### Sintassi

```c
while (condizione) {
    // Blocco di codice da eseguire finché la condizione è vera
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    int contatore = 1;
    
    while (contatore <= 5) {
        printf("%d ", contatore);
        contatore++;
    }
    
    return 0;
}
```

Output:
```
1 2 3 4 5
```

In questo esempio, il ciclo `while` stampa i numeri da 1 a 5. La variabile `contatore` viene incrementata ad ogni iterazione, e il ciclo continua finché `contatore` è minore o uguale a 5.

## Ciclo `do-while`

Il ciclo `do-while` è simile al ciclo `while`, ma la condizione viene valutata dopo l'esecuzione del blocco di codice. Questo garantisce che il blocco di codice venga eseguito almeno una volta, anche se la condizione è inizialmente falsa.

### Sintassi

```c
do {
    // Blocco di codice da eseguire
} while (condizione);
```

### Esempio

```c
#include <stdio.h>

int main() {
    int numero;
    
    do {
        printf("Inserisci un numero positivo: ");
        scanf("%d", &numero);
    } while (numero <= 0);
    
    printf("Hai inserito: %d\n", numero);
    
    return 0;
}
```

In questo esempio, il programma chiede all'utente di inserire un numero positivo. Se l'utente inserisce un numero non positivo, il ciclo continua a chiedere un nuovo input finché non viene inserito un numero positivo.

## Ciclo `for`

Il ciclo `for` è utilizzato quando si conosce in anticipo il numero di iterazioni da eseguire. È composto da tre parti: inizializzazione, condizione e incremento/decremento.

### Sintassi

```c
for (inizializzazione; condizione; incremento/decremento) {
    // Blocco di codice da eseguire
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    
    return 0;
}
```

Output:
```
0 1 2 3 4
```

In questo esempio, il ciclo `for` stampa i numeri da 0 a 4. La variabile `i` viene inizializzata a 0, il ciclo continua finché `i` è minore di 5, e `i` viene incrementato di 1 ad ogni iterazione.

## Istruzioni `break` e `continue`

Le istruzioni `break` e `continue` sono utilizzate per controllare il flusso di esecuzione all'interno dei cicli.

### Istruzione `break`

L'istruzione `break` termina immediatamente il ciclo in cui si trova, indipendentemente dalla condizione del ciclo.

#### Esempio

```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break; // Esce dal ciclo quando i è uguale a 5
        }
        printf("%d ", i);
    }
    
    return 0;
}
```

Output:
```
0 1 2 3 4
```

In questo esempio, il ciclo `for` dovrebbe stampare i numeri da 0 a 9, ma l'istruzione `break` fa uscire dal ciclo quando `i` è uguale a 5, quindi vengono stampati solo i numeri da 0 a 4.

### Istruzione `continue`

L'istruzione `continue` salta il resto del blocco di codice nell'iterazione corrente e passa direttamente alla prossima iterazione.

#### Esempio

```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue; // Salta l'iterazione corrente se i è pari
        }
        printf("%d ", i);
    }
    
    return 0;
}
```

Output:
```
1 3 5 7 9
```

In questo esempio, l'istruzione `continue` fa sì che il ciclo salti la stampa quando `i` è pari, quindi vengono stampati solo i numeri dispari da 1 a 9.

## Cicli annidati

I cicli possono essere annidati uno dentro l'altro per creare strutture più complesse.

### Esempio

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("%d,%d ", i, j);
        }
        printf("\n");
    }
    
    return 0;
}
```

Output:
```
1,1 1,2 1,3 
2,1 2,2 2,3 
3,1 3,2 3,3 
```

In questo esempio, il ciclo esterno itera da 1 a 3, e per ogni iterazione del ciclo esterno, il ciclo interno itera anch'esso da 1 a 3, stampando le coppie di valori (i, j).

## Tecniche per ottimizzare i cicli

### 1. Evitare calcoli ripetuti

Se un calcolo all'interno di un ciclo non cambia tra le iterazioni, è meglio calcolarlo una sola volta prima del ciclo.

#### Esempio non ottimizzato

```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        array[i][j] = i * j * sqrt(n); // sqrt(n) viene calcolato n*n volte
    }
}
```

#### Esempio ottimizzato

```c
double sqrtN = sqrt(n); // Calcola sqrt(n) una sola volta
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        array[i][j] = i * j * sqrtN;
    }
}
```

### 2. Ridurre le operazioni all'interno del ciclo

Spostare le operazioni che non dipendono dalla variabile di iterazione fuori dal ciclo.

#### Esempio non ottimizzato

```c
for (int i = 0; i < n; i++) {
    array[i] = i * 2 + 5; // 5 viene aggiunto n volte
}
```

#### Esempio ottimizzato

```c
for (int i = 0; i < n; i++) {
    array[i] = i * 2;
}
for (int i = 0; i < n; i++) {
    array[i] += 5; // Operazione separata
}
```

### 3. Utilizzare variabili di accumulo

Per operazioni di somma o prodotto, utilizzare variabili di accumulo per evitare di ricalcolare l'intera espressione ad ogni iterazione.

#### Esempio non ottimizzato

```c
int somma = 0;
for (int i = 1; i <= n; i++) {
    somma = 0;
    for (int j = 1; j <= i; j++) {
        somma += j;
    }
    printf("Somma fino a %d: %d\n", i, somma);
}
```

#### Esempio ottimizzato

```c
int somma = 0;
for (int i = 1; i <= n; i++) {
    somma += i; // Accumula la somma
    printf("Somma fino a %d: %d\n", i, somma);
}
```

### 4. Utilizzare l'unrolling dei cicli

L'unrolling dei cicli consiste nell'eseguire più iterazioni in un singolo passo del ciclo, riducendo il numero totale di iterazioni.

#### Esempio non ottimizzato

```c
for (int i = 0; i < n; i++) {
    array[i] = i * 2;
}
```

#### Esempio ottimizzato (unrolling)

```c
int i;
for (i = 0; i < n - 3; i += 4) {
    array[i] = i * 2;
    array[i+1] = (i+1) * 2;
    array[i+2] = (i+2) * 2;
    array[i+3] = (i+3) * 2;
}
// Gestione degli elementi rimanenti
for (; i < n; i++) {
    array[i] = i * 2;
}
```

## Esercizi di laboratorio sui cicli

1. **Calcolo del fattoriale**: Scrivere un programma che calcoli il fattoriale di un numero utilizzando un ciclo.

```c
#include <stdio.h>

int main() {
    int n, fattoriale = 1;
    
    printf("Inserisci un numero: ");
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        fattoriale *= i;
    }
    
    printf("Il fattoriale di %d è %d\n", n, fattoriale);
    
    return 0;
}
```

2. **Sequenza di Fibonacci**: Scrivere un programma che generi i primi n numeri della sequenza di Fibonacci.

```c
#include <stdio.h>

int main() {
    int n, a = 0, b = 1, c;
    
    printf("Quanti numeri della sequenza di Fibonacci vuoi generare? ");
    scanf("%d", &n);
    
    printf("Sequenza di Fibonacci: ");
    
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
    
    return 0;
}
```

3. **Calcolo del MCD**: Scrivere un programma che calcoli il Massimo Comune Divisore di due numeri utilizzando l'algoritmo di Euclide.

```c
#include <stdio.h>

int main() {
    int a, b, temp;
    
    printf("Inserisci due numeri: ");
    scanf("%d %d", &a, &b);
    
    // Assicuriamoci che a sia maggiore o uguale a b
    if (a < b) {
        temp = a;
        a = b;
        b = temp;
    }
    
    // Algoritmo di Euclide
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    printf("Il MCD è %d\n", a);
    
    return 0;
}
```

4. **Stampa di un triangolo di asterischi**: Scrivere un programma che stampi un triangolo di asterischi utilizzando cicli annidati.

```c
#include <stdio.h>

int main() {
    int n;
    
    printf("Inserisci l'altezza del triangolo: ");
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    return 0;
}
```

5. **Verifica di un numero primo**: Scrivere un programma che verifichi se un numero è primo.

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main() {
    int n;
    bool isPrime = true;
    
    printf("Inserisci un numero: ");
    scanf("%d", &n);
    
    if (n <= 1) {
        isPrime = false;
    } else {
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
    }
    
    if (isPrime) {
        printf("%d è un numero primo\n", n);
    } else {
        printf("%d non è un numero primo\n", n);
    }
    
    return 0;
}
```

Questi esercizi coprono diversi aspetti dei cicli e delle iterazioni, fornendo una base solida per comprendere e applicare questi concetti in situazioni pratiche.