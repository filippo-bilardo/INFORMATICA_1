# Cicli in C

I cicli sono strutture fondamentali nella programmazione che permettono di eseguire ripetutamente un blocco di codice fino a quando una condizione specificata rimane vera. In C, esistono tre tipi principali di cicli: `while`, `do-while` e `for`.

## Ciclo while

Il ciclo `while` esegue un blocco di codice fintanto che una condizione specificata è vera. La condizione viene valutata prima di ogni iterazione, quindi se la condizione è falsa fin dall'inizio, il blocco di codice non verrà mai eseguito.

### Sintassi di base

```c
while (condizione) {
    // Blocco di codice da eseguire ripetutamente
    // finché la condizione è vera
}
```

### Esempio semplice

```c
#include <stdio.h>

int main() {
    int contatore = 1;
    
    while (contatore <= 5) {
        printf("Contatore: %d\n", contatore);
        contatore++;
    }
    
    printf("Fine del ciclo\n");
    return 0;
}
```

Output:
```
Contatore: 1
Contatore: 2
Contatore: 3
Contatore: 4
Contatore: 5
Fine del ciclo
```

### Ciclo while con condizione complessa

```c
#include <stdio.h>

int main() {
    int numero = 1;
    int somma = 0;
    
    while (somma < 100 && numero <= 20) {
        somma += numero;
        printf("Numero: %d, Somma: %d\n", numero, somma);
        numero++;
    }
    
    printf("Somma finale: %d\n", somma);
    return 0;
}
```

### Ciclo infinito

Un ciclo `while` con una condizione che è sempre vera creerà un ciclo infinito. Questo può essere intenzionale in alcuni casi, ma generalmente richiede un meccanismo di uscita all'interno del ciclo.

```c
#include <stdio.h>

int main() {
    int numero;
    
    while (1) {  // Condizione sempre vera (ciclo infinito)
        printf("Inserisci un numero (0 per uscire): ");
        scanf("%d", &numero);
        
        if (numero == 0) {
            printf("Uscita dal ciclo\n");
            break;  // Esce dal ciclo
        }
        
        printf("Hai inserito: %d\n", numero);
    }
    
    return 0;
}
```

## Ciclo do-while

Il ciclo `do-while` è simile al ciclo `while`, ma con una differenza importante: la condizione viene valutata dopo l'esecuzione del blocco di codice. Questo garantisce che il blocco di codice venga eseguito almeno una volta, anche se la condizione è falsa fin dall'inizio.

### Sintassi di base

```c
do {
    // Blocco di codice da eseguire ripetutamente
    // (eseguito almeno una volta)
} while (condizione);
```

### Esempio semplice

```c
#include <stdio.h>

int main() {
    int contatore = 1;
    
    do {
        printf("Contatore: %d\n", contatore);
        contatore++;
    } while (contatore <= 5);
    
    printf("Fine del ciclo\n");
    return 0;
}
```

Output (identico all'esempio `while`):
```
Contatore: 1
Contatore: 2
Contatore: 3
Contatore: 4
Contatore: 5
Fine del ciclo
```

### Esempio con condizione inizialmente falsa

```c
#include <stdio.h>

int main() {
    int numero = 10;
    
    // Il blocco viene eseguito una volta anche se la condizione è falsa
    do {
        printf("Numero: %d\n", numero);
        numero++;
    } while (numero < 10);
    
    printf("Valore finale: %d\n", numero);
    return 0;
}
```

Output:
```
Numero: 10
Valore finale: 11
```

### Validazione dell'input con do-while

Un uso comune del ciclo `do-while` è la validazione dell'input dell'utente:

```c
#include <stdio.h>

int main() {
    int numero;
    
    do {
        printf("Inserisci un numero positivo: ");
        scanf("%d", &numero);
        
        if (numero <= 0) {
            printf("Errore: il numero deve essere positivo!\n");
        }
    } while (numero <= 0);
    
    printf("Hai inserito il numero positivo: %d\n", numero);
    return 0;
}
```

## Ciclo for

Il ciclo `for` è progettato per situazioni in cui si conosce in anticipo il numero di iterazioni o quando si desidera un controllo più preciso sull'inizializzazione, la condizione e l'incremento.

### Sintassi di base

```c
for (inizializzazione; condizione; incremento) {
    // Blocco di codice da eseguire ripetutamente
}
```

Dove:
- **inizializzazione**: espressione eseguita una sola volta all'inizio del ciclo
- **condizione**: valutata prima di ogni iterazione; il ciclo continua finché è vera
- **incremento**: espressione eseguita alla fine di ogni iterazione

### Esempio semplice

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        printf("Iterazione: %d\n", i);
    }
    
    printf("Fine del ciclo\n");
    return 0;
}
```

Output:
```
Iterazione: 1
Iterazione: 2
Iterazione: 3
Iterazione: 4
Iterazione: 5
Fine del ciclo
```

### Ciclo for con decremento

```c
#include <stdio.h>

int main() {
    for (int i = 10; i > 0; i--) {
        printf("Conto alla rovescia: %d\n", i);
    }
    
    printf("Partenza!\n");
    return 0;
}
```

### Ciclo for con incremento personalizzato

```c
#include <stdio.h>

int main() {
    for (int i = 0; i <= 20; i += 2) {
        printf("Numero pari: %d\n", i);
    }
    
    return 0;
}
```

### Parti opzionali del ciclo for

Tutte e tre le parti del ciclo `for` sono opzionali:

```c
#include <stdio.h>

int main() {
    int i = 1;  // Inizializzazione fuori dal ciclo
    
    for (; i <= 5; ) {  // Condizione senza inizializzazione né incremento
        printf("Valore: %d\n", i);
        i++;  // Incremento all'interno del ciclo
    }
    
    // Ciclo infinito (equivalente a while(1))
    // for (;;) {
    //     printf("Ciclo infinito\n");
    // }
    
    return 0;
}
```

### Cicli for annidati

I cicli `for` possono essere annidati uno dentro l'altro, il che è utile per lavorare con strutture dati multidimensionali come matrici:

```c
#include <stdio.h>

int main() {
    int righe = 3;
    int colonne = 4;
    
    printf("Tabella %d x %d:\n", righe, colonne);
    
    for (int i = 1; i <= righe; i++) {
        for (int j = 1; j <= colonne; j++) {
            printf("%3d", i * j);  // %3d riserva 3 spazi per ogni numero
        }
        printf("\n");  // Nuova riga dopo ogni riga della tabella
    }
    
    return 0;
}
```

Output:
```
Tabella 3 x 4:
  1  2  3  4
  2  4  6  8
  3  6  9 12
```

### Dichiarazione di variabili nel ciclo for

In C99 e versioni successive, è possibile dichiarare variabili direttamente nell'inizializzazione del ciclo `for`. Queste variabili hanno un ambito limitato al ciclo stesso:

```c
#include <stdio.h>

int main() {
    // La variabile 'i' esiste solo all'interno del ciclo
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }
    
    // Errore: 'i' non è più accessibile qui
    // printf("Valore finale di i: %d\n", i);
    
    return 0;
}
```

## Confronto tra i diversi tipi di cicli

| Ciclo | Quando usarlo | Caratteristiche |
|-------|--------------|----------------|
| `while` | Quando il numero di iterazioni non è noto in anticipo e la condizione deve essere verificata prima di ogni iterazione | - Condizione verificata all'inizio<br>- Potrebbe non eseguire mai il blocco di codice |
| `do-while` | Quando il blocco di codice deve essere eseguito almeno una volta | - Condizione verificata alla fine<br>- Esegue sempre il blocco di codice almeno una volta |
| `for` | Quando il numero di iterazioni è noto o quando è necessario un controllo preciso sull'inizializzazione e l'incremento | - Sintassi compatta<br>- Tutte le parti del controllo del ciclo sono in un unico posto |

## Equivalenza tra i cicli

Ogni tipo di ciclo può essere riscritto utilizzando gli altri tipi. Ad esempio:

### Equivalenza tra for e while

```c
// Ciclo for
for (int i = 1; i <= 5; i++) {
    printf("%d\n", i);
}

// Equivalente con while
int i = 1;
while (i <= 5) {
    printf("%d\n", i);
    i++;
}
```

### Equivalenza tra while e do-while

```c
// Ciclo while
int i = 1;
while (i <= 5) {
    printf("%d\n", i);
    i++;
}

// Equivalente con do-while (con controllo aggiuntivo per la prima iterazione)
int i = 1;
if (i <= 5) {  // Questo controllo simula il comportamento del while
    do {
        printf("%d\n", i);
        i++;
    } while (i <= 5);
}
```

## Best practice

1. **Scegliere il ciclo appropriato** per il compito specifico:
   - `for` per cicli con un numero noto di iterazioni
   - `while` per cicli basati su condizioni che potrebbero non essere mai soddisfatte
   - `do-while` quando il blocco deve essere eseguito almeno una volta

2. **Evitare modifiche alla variabile di controllo** all'interno del ciclo `for` (a meno che non sia intenzionale):
   ```c
   // Evitare
   for (int i = 0; i < 10; i++) {
       // ...
       i++;  // Modifica non intenzionale che altera il flusso del ciclo
   }
   ```

3. **Utilizzare nomi di variabili significativi** per i contatori dei cicli:
   ```c
   // Invece di
   for (int i = 0; i < n; i++) { ... }
   
   // Considerare
   for (int indice = 0; indice < numero_elementi; indice++) { ... }
   ```

4. **Evitare cicli infiniti non intenzionali** assicurandosi che la condizione possa diventare falsa:
   ```c
   // Potenziale ciclo infinito se x è sempre maggiore di 0
   while (x > 0) {
       // Codice che non modifica x
   }
   ```

5. **Utilizzare le parentesi graffe** anche per blocchi di una sola istruzione:
   ```c
   // Preferibile
   for (int i = 0; i < 5; i++) {
       printf("%d\n", i);
   }
   
   // Evitare
   for (int i = 0; i < 5; i++)
       printf("%d\n", i);
   ```

6. **Limitare la complessità** dei cicli annidati; considerare l'estrazione in funzioni separate se diventano troppo complessi.

## Esempi pratici

### Calcolo del fattoriale

```c
#include <stdio.h>

int main() {
    int numero, fattoriale = 1;
    
    printf("Inserisci un numero intero positivo: ");
    scanf("%d", &numero);
    
    if (numero < 0) {
        printf("Il fattoriale non è definito per numeri negativi\n");
    } else {
        for (int i = 1; i <= numero; i++) {
            fattoriale *= i;
        }
        printf("%d! = %d\n", numero, fattoriale);
    }
    
    return 0;
}
```

### Stampa di un triangolo di asterischi

```c
#include <stdio.h>

int main() {
    int altezza;
    
    printf("Inserisci l'altezza del triangolo: ");
    scanf("%d", &altezza);
    
    for (int i = 1; i <= altezza; i++) {
        // Stampa spazi
        for (int j = 1; j <= altezza - i; j++) {
            printf(" ");
        }
        
        // Stampa asterischi
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        
        printf("\n");
    }
    
    return 0;
}
```

### Ricerca del massimo comune divisore (MCD) con l'algoritmo di Euclide

```c
#include <stdio.h>

int main() {
    int a, b, temp;
    
    printf("Inserisci due numeri interi positivi: ");
    scanf("%d %d", &a, &b);
    
    // Assicuriamoci che a e b siano positivi
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    
    // Algoritmo di Euclide con ciclo while
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    printf("Il massimo comune divisore è: %d\n", a);
    
    return 0;
}
```

### Verifica di un numero primo

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main() {
    int numero;
    bool primo = true;
    
    printf("Inserisci un numero intero positivo: ");
    scanf("%d", &numero);
    
    if (numero <= 1) {
        primo = false;
    } else if (numero <= 3) {
        primo = true;  // 2 e 3 sono primi
    } else if (numero % 2 == 0 || numero % 3 == 0) {
        primo = false;  // Divisibile per 2 o 3
    } else {
        // Verifica divisibilità per numeri della forma 6k±1
        for (int i = 5; i * i <= numero; i += 6) {
            if (numero % i == 0 || numero % (i + 2) == 0) {
                primo = false;
                break;
            }
        }
    }
    
    if (primo) {
        printf("%d è un numero primo\n", numero);
    } else {
        printf("%d non è un numero primo\n", numero);
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza principale tra un ciclo `while` e un ciclo `do-while`?

2. In quali situazioni è preferibile utilizzare un ciclo `for` rispetto a un ciclo `while`?

3. Come si può creare un ciclo infinito con ciascuno dei tre tipi di cicli?

4. Cosa succede se si modifica la variabile di controllo all'interno di un ciclo `for`?

5. Come si può uscire anticipatamente da un ciclo quando si verifica una determinata condizione?

## Esercizi proposti

1. Scrivi un programma che calcoli la somma dei primi n numeri naturali, dove n è inserito dall'utente.

2. Implementa un programma che stampi la tavola pitagorica (tabella di moltiplicazione) fino a 10×10 utilizzando cicli annidati.

3. Scrivi un programma che legga una sequenza di numeri interi (terminata da 0) e calcoli la media dei numeri positivi e la media dei numeri negativi.

4. Implementa l'algoritmo di Newton-Raphson per calcolare la radice quadrata di un numero con una precisione specificata dall'utente.

5. Scrivi un programma che generi e stampi i primi n numeri della sequenza di Fibonacci, dove n è inserito dall'utente.