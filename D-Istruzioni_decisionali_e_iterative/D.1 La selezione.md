# D.1. La selezione

Le istruzioni di selezione, o istruzioni condizionali, permettono di eseguire blocchi di codice solo quando determinate condizioni sono soddisfatte. Queste istruzioni sono fondamentali per creare programmi che possano prendere decisioni in base ai dati di input o allo stato del programma.

## Istruzione `if`

L'istruzione `if` è la forma più semplice di selezione. Esegue un blocco di codice solo se la condizione specificata è vera.

### Sintassi

```c
if (condizione) {
    // Blocco di codice da eseguire se la condizione è vera
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    int numero = 10;
    
    if (numero > 0) {
        printf("Il numero è positivo\n");
    }
    
    return 0;
}
```

In questo esempio, il messaggio "Il numero è positivo" viene stampato solo se `numero` è maggiore di zero.

## Istruzione `if-else`

L'istruzione `if-else` estende l'istruzione `if` aggiungendo un blocco di codice da eseguire quando la condizione è falsa.

### Sintassi

```c
if (condizione) {
    // Blocco di codice da eseguire se la condizione è vera
} else {
    // Blocco di codice da eseguire se la condizione è falsa
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    int numero = -5;
    
    if (numero >= 0) {
        printf("Il numero è positivo o zero\n");
    } else {
        printf("Il numero è negativo\n");
    }
    
    return 0;
}
```

In questo esempio, se `numero` è maggiore o uguale a zero, viene stampato il primo messaggio; altrimenti, viene stampato il secondo messaggio.

## Istruzione `else if`

L'istruzione `else if` permette di verificare più condizioni in sequenza. Viene utilizzata quando si hanno più di due possibili percorsi di esecuzione.

### Sintassi

```c
if (condizione1) {
    // Blocco di codice da eseguire se condizione1 è vera
} else if (condizione2) {
    // Blocco di codice da eseguire se condizione1 è falsa e condizione2 è vera
} else {
    // Blocco di codice da eseguire se tutte le condizioni precedenti sono false
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    int voto = 85;
    
    if (voto >= 90) {
        printf("Ottimo\n");
    } else if (voto >= 80) {
        printf("Buono\n");
    } else if (voto >= 70) {
        printf("Discreto\n");
    } else if (voto >= 60) {
        printf("Sufficiente\n");
    } else {
        printf("Insufficiente\n");
    }
    
    return 0;
}
```

In questo esempio, il programma valuta il voto e stampa un giudizio appropriato in base al valore.

## Istruzione `switch`

L'istruzione `switch` è un'alternativa all'istruzione `if-else if-else` quando si deve confrontare una variabile con diversi valori costanti.

### Sintassi

```c
switch (espressione) {
    case valore1:
        // Codice da eseguire se espressione == valore1
        break;
    case valore2:
        // Codice da eseguire se espressione == valore2
        break;
    // Altri casi...
    default:
        // Codice da eseguire se nessun caso corrisponde
}
```

### Esempio

```c
#include <stdio.h>

int main() {
    char operatore = '+';
    int a = 10, b = 5, risultato;
    
    switch (operatore) {
        case '+':
            risultato = a + b;
            printf("Somma: %d\n", risultato);
            break;
        case '-':
            risultato = a - b;
            printf("Sottrazione: %d\n", risultato);
            break;
        case '*':
            risultato = a * b;
            printf("Moltiplicazione: %d\n", risultato);
            break;
        case '/':
            if (b != 0) {
                risultato = a / b;
                printf("Divisione: %d\n", risultato);
            } else {
                printf("Errore: divisione per zero\n");
            }
            break;
        default:
            printf("Operatore non valido\n");
    }
    
    return 0;
}
```

In questo esempio, il programma esegue un'operazione aritmetica diversa in base al valore della variabile `operatore`.

## Operatore ternario

L'operatore ternario `? :` è una forma compatta dell'istruzione `if-else` che può essere utilizzata per assegnare un valore a una variabile in base a una condizione.

### Sintassi

```c
variabile = (condizione) ? valore_se_vero : valore_se_falso;
```

### Esempio

```c
#include <stdio.h>

int main() {
    int a = 10, b = 5;
    int max = (a > b) ? a : b;
    
    printf("Il valore massimo è: %d\n", max);
    
    return 0;
}
```

In questo esempio, la variabile `max` viene assegnata al valore di `a` se `a > b` è vero, altrimenti viene assegnata al valore di `b`.

## Istruzioni condizionali annidate

È possibile annidare istruzioni condizionali all'interno di altre istruzioni condizionali per creare logiche più complesse.

### Esempio

```c
#include <stdio.h>

int main() {
    int numero = 15;
    
    if (numero > 0) {
        if (numero % 2 == 0) {
            printf("Il numero è positivo e pari\n");
        } else {
            printf("Il numero è positivo e dispari\n");
        }
    } else if (numero < 0) {
        printf("Il numero è negativo\n");
    } else {
        printf("Il numero è zero\n");
    }
    
    return 0;
}
```

In questo esempio, il programma prima verifica se il numero è positivo, negativo o zero, e poi, se è positivo, verifica se è pari o dispari.

## Il problema dell'else pendente

Quando si annidano istruzioni `if` senza utilizzare le parentesi graffe `{}`, può verificarsi il problema dell'else pendente. In questo caso, l'istruzione `else` viene associata all'`if` più vicino, che potrebbe non essere quello desiderato.

### Esempio del problema

```c
if (condizione1)
    if (condizione2)
        printf("Entrambe le condizioni sono vere\n");
else
    printf("La condizione1 è falsa\n"); // In realtà, questo else è associato a if (condizione2)
```

### Soluzione

Utilizzare sempre le parentesi graffe `{}` per delimitare i blocchi di codice, anche quando contengono una sola istruzione:

```c
if (condizione1) {
    if (condizione2) {
        printf("Entrambe le condizioni sono vere\n");
    }
} else {
    printf("La condizione1 è falsa\n"); // Ora l'else è associato correttamente a if (condizione1)
}
```

Per approfondimenti su questo argomento, consultare il documento [Problema dell'else pendente](Problema%20dell'else%20pendente.md).

## Casi d'uso comuni

1. **Validazione dell'input**: Verificare che i dati inseriti dall'utente siano validi prima di elaborarli.
2. **Controllo del flusso del programma**: Decidere quale percorso di esecuzione seguire in base a determinate condizioni.
3. **Gestione degli errori**: Verificare se un'operazione ha avuto successo e gestire eventuali errori.
4. **Implementazione di menu**: Permettere all'utente di scegliere tra diverse opzioni.
5. **Calcoli condizionali**: Eseguire calcoli diversi in base a determinate condizioni.

## Esercizi pratici

1. Scrivere un programma che legga un numero intero e determini se è pari o dispari.
2. Scrivere un programma che legga tre numeri e li stampi in ordine crescente.
3. Implementare una calcolatrice semplice che accetti due numeri e un operatore (+, -, *, /) e restituisca il risultato dell'operazione.
4. Scrivere un programma che determini se un anno è bisestile o meno.
5. Implementare un programma che converta un voto numerico (0-100) in un voto letterale (A, B, C, D, F).