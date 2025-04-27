# Istruzioni di salto in C

Le istruzioni di salto in C permettono di alterare il normale flusso di esecuzione di un programma. Queste istruzioni consentono di saltare parti di codice, uscire da cicli o funzioni, o trasferire il controllo a un'altra parte del programma. Le principali istruzioni di salto in C sono `break`, `continue`, `goto` e `return`.

## Istruzione break

L'istruzione `break` termina immediatamente l'esecuzione del ciclo (`for`, `while`, `do-while`) o dello `switch` più interno in cui si trova, trasferendo il controllo alla prima istruzione che segue il blocco terminato.

### Utilizzo di break nei cicli

```c
#include <stdio.h>

int main() {
    int i;
    
    for (i = 1; i <= 10; i++) {
        if (i == 5) {
            printf("Interruzione del ciclo a i = %d\n", i);
            break;  // Esce dal ciclo quando i è 5
        }
        printf("i = %d\n", i);
    }
    
    printf("Dopo il ciclo, i = %d\n", i);
    return 0;
}
```

Output:
```
i = 1
i = 2
i = 3
i = 4
Interruzione del ciclo a i = 5
Dopo il ciclo, i = 5
```

### Utilizzo di break in switch-case

```c
#include <stdio.h>

int main() {
    char scelta = 'B';
    
    switch (scelta) {
        case 'A':
            printf("Hai selezionato A\n");
            break;  // Esce dallo switch
        case 'B':
            printf("Hai selezionato B\n");
            break;  // Esce dallo switch
        case 'C':
            printf("Hai selezionato C\n");
            break;  // Esce dallo switch
        default:
            printf("Scelta non valida\n");
    }
    
    printf("Dopo lo switch\n");
    return 0;
}
```

Output:
```
Hai selezionato B
Dopo lo switch
```

### Break in cicli annidati

L'istruzione `break` interrompe solo il ciclo più interno in cui si trova. Per uscire da cicli annidati, è necessario utilizzare altre tecniche, come variabili di controllo o l'istruzione `goto`.

```c
#include <stdio.h>

int main() {
    int i, j;
    int trovato = 0;  // Variabile di controllo
    
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("i = %d, j = %d\n", i, j);
            
            if (i == 2 && j == 2) {
                printf("Trovato il valore cercato!\n");
                trovato = 1;  // Imposta la variabile di controllo
                break;  // Esce solo dal ciclo interno
            }
        }
        
        if (trovato) {
            break;  // Esce dal ciclo esterno se trovato è vero
        }
    }
    
    printf("Dopo i cicli: i = %d, j = %d\n", i, j);
    return 0;
}
```

Output:
```
i = 1, j = 1
i = 1, j = 2
i = 1, j = 3
i = 2, j = 1
i = 2, j = 2
Trovato il valore cercato!
Dopo i cicli: i = 2, j = 2
```

## Istruzione continue

L'istruzione `continue` salta il resto del corpo del ciclo più interno in cui si trova e passa direttamente alla prossima iterazione del ciclo.

### Esempio di continue in un ciclo for

```c
#include <stdio.h>

int main() {
    int i;
    
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {  // Se i è pari
            continue;  // Salta il resto del ciclo e passa alla prossima iterazione
        }
        printf("%d ", i);  // Stampa solo i numeri dispari
    }
    
    printf("\nFine del ciclo\n");
    return 0;
}
```

Output:
```
1 3 5 7 9 
Fine del ciclo
```

### Esempio di continue in un ciclo while

```c
#include <stdio.h>

int main() {
    int i = 0;
    
    while (i < 10) {
        i++;
        
        if (i % 3 == 0) {  // Se i è divisibile per 3
            continue;  // Salta il resto del ciclo
        }
        
        printf("%d ", i);  // Stampa solo i numeri non divisibili per 3
    }
    
    printf("\nFine del ciclo\n");
    return 0;
}
```

Output:
```
1 2 4 5 7 8 10 
Fine del ciclo
```

### Differenza tra break e continue

- `break` termina completamente il ciclo e passa all'istruzione successiva dopo il ciclo
- `continue` salta solo il resto dell'iterazione corrente e passa alla prossima iterazione del ciclo

```c
#include <stdio.h>

int main() {
    int i;
    
    printf("Esempio con continue:\n");
    for (i = 1; i <= 5; i++) {
        if (i == 3) {
            printf("  (saltando il resto dell'iterazione per i = %d)\n", i);
            continue;
        }
        printf("  i = %d\n", i);
    }
    
    printf("\nEsempio con break:\n");
    for (i = 1; i <= 5; i++) {
        if (i == 3) {
            printf("  (uscendo dal ciclo a i = %d)\n", i);
            break;
        }
        printf("  i = %d\n", i);
    }
    
    return 0;
}
```

Output:
```
Esempio con continue:
  i = 1
  i = 2
  (saltando il resto dell'iterazione per i = 3)
  i = 4
  i = 5

Esempio con break:
  i = 1
  i = 2
  (uscendo dal ciclo a i = 3)
```

## Istruzione goto

L'istruzione `goto` trasferisce incondizionatamente il controllo a un'altra parte del programma contrassegnata da un'etichetta. Sebbene `goto` sia disponibile in C, il suo uso è generalmente sconsigliato nella programmazione moderna perché può rendere il codice difficile da leggere, comprendere e mantenere.

### Sintassi di base

```c
goto etichetta;
// ...
etichetta: istruzione;
```

### Esempio di goto

```c
#include <stdio.h>

int main() {
    int i = 1;
    
inizio_ciclo:
    if (i <= 5) {
        printf("%d\n", i);
        i++;
        goto inizio_ciclo;  // Torna all'etichetta
    }
    
    printf("Fine del ciclo\n");
    return 0;
}
```

Output:
```
1
2
3
4
5
Fine del ciclo
```

### Utilizzo accettabile di goto

Nonostante sia generalmente sconsigliato, ci sono alcuni casi in cui `goto` può essere utile, come per uscire da cicli annidati o per gestire errori in modo centralizzato:

```c
#include <stdio.h>

int main() {
    int i, j;
    
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("i = %d, j = %d\n", i, j);
            
            if (i == 2 && j == 2) {
                printf("Trovato il valore cercato!\n");
                goto fine_cicli;  // Esce da entrambi i cicli
            }
        }
    }
    
fine_cicli:
    printf("Dopo i cicli: i = %d, j = %d\n", i, j);
    return 0;
}
```

Output:
```
i = 1, j = 1
i = 1, j = 2
i = 1, j = 3
i = 2, j = 1
i = 2, j = 2
Trovato il valore cercato!
Dopo i cicli: i = 2, j = 2
```

### Gestione degli errori con goto

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1 = NULL, *file2 = NULL;
    int *array = NULL;
    
    // Apertura del primo file
    file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        printf("Errore nell'apertura di file1.txt\n");
        goto cleanup;
    }
    
    // Apertura del secondo file
    file2 = fopen("file2.txt", "r");
    if (file2 == NULL) {
        printf("Errore nell'apertura di file2.txt\n");
        goto cleanup;
    }
    
    // Allocazione di memoria
    array = (int*)malloc(10 * sizeof(int));
    if (array == NULL) {
        printf("Errore nell'allocazione di memoria\n");
        goto cleanup;
    }
    
    // Codice principale
    printf("Tutte le operazioni sono state completate con successo\n");
    
    // Pulizia delle risorse
cleanup:
    if (file1 != NULL) fclose(file1);
    if (file2 != NULL) fclose(file2);
    if (array != NULL) free(array);
    
    return 0;
}
```

### Alternative a goto

Nella maggior parte dei casi, è possibile e preferibile riscrivere il codice che utilizza `goto` utilizzando altre strutture di controllo:

```c
// Invece di goto per uscire da cicli annidati
int trovato = 0;
for (i = 1; i <= 3 && !trovato; i++) {
    for (j = 1; j <= 3 && !trovato; j++) {
        if (condizione) {
            trovato = 1;  // Imposta una variabile di controllo
        }
    }
}

// Invece di goto per gestire errori
int funzione() {
    // Allocazione risorse
    if (errore1) {
        // Gestione errore
        return CODICE_ERRORE1;
    }
    
    if (errore2) {
        // Pulizia risorse allocate prima
        // Gestione errore
        return CODICE_ERRORE2;
    }
    
    // Codice principale
    
    // Pulizia risorse
    return SUCCESSO;
}
```

## Istruzione return

L'istruzione `return` termina l'esecuzione della funzione corrente e restituisce il controllo alla funzione chiamante. Opzionalmente, può anche restituire un valore.

### Sintassi di base

```c
return; // Senza valore di ritorno (per funzioni void)
return espressione; // Con valore di ritorno
```

### Esempio di return in una funzione void

```c
#include <stdio.h>

void stampa_numeri(int limite) {
    int i;
    
    if (limite <= 0) {
        printf("Il limite deve essere positivo\n");
        return;  // Termina la funzione senza restituire un valore
    }
    
    for (i = 1; i <= limite; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    stampa_numeri(-5);  // Limite non valido
    stampa_numeri(3);   // Limite valido
    
    return 0;
}
```

Output:
```
Il limite deve essere positivo
1 2 3 
```

### Esempio di return con valore di ritorno

```c
#include <stdio.h>

int somma(int a, int b) {
    return a + b;  // Restituisce la somma di a e b
}

int massimo(int a, int b, int c) {
    if (a >= b && a >= c) {
        return a;
    } else if (b >= a && b >= c) {
        return b;
    } else {
        return c;
    }
}

int main() {
    int risultato1 = somma(5, 3);
    int risultato2 = massimo(5, 8, 3);
    
    printf("Somma: %d\n", risultato1);
    printf("Massimo: %d\n", risultato2);
    
    return 0;  // Restituisce 0 al sistema operativo
}
```

Output:
```
Somma: 8
Massimo: 8
```

### Return anticipato

L'istruzione `return` può essere utilizzata per uscire anticipatamente da una funzione quando si verifica una determinata condizione, semplificando la logica del codice:

```c
#include <stdio.h>

int è_primo(int n) {
    int i;
    
    // Gestione casi speciali
    if (n <= 1) {
        return 0;  // Non è primo
    }
    
    if (n <= 3) {
        return 1;  // 2 e 3 sono primi
    }
    
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;  // Divisibile per 2 o 3
    }
    
    // Verifica divisibilità per numeri della forma 6k±1
    for (i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;  // Non è primo
        }
    }
    
    return 1;  // È primo
}

int main() {
    int numero = 17;
    
    if (è_primo(numero)) {
        printf("%d è un numero primo\n", numero);
    } else {
        printf("%d non è un numero primo\n", numero);
    }
    
    return 0;
}
```

Output:
```
17 è un numero primo
```

### Return nella funzione main

La funzione `main` in C restituisce un valore intero al sistema operativo. Per convenzione:

- `0` indica esecuzione completata con successo
- Valori diversi da zero indicano errori

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        printf("Errore: impossibile aprire il file\n");
        return 1;  // Restituisce un codice di errore
    }
    
    // Operazioni sul file
    fclose(file);
    
    printf("Operazione completata con successo\n");
    return 0;  // Esecuzione completata con successo
}
```

## Confronto tra le istruzioni di salto

| Istruzione | Scopo | Utilizzo |
|------------|-------|----------|
| `break` | Uscire da un ciclo o switch | All'interno di cicli o switch per terminare l'esecuzione |
| `continue` | Saltare alla prossima iterazione | All'interno di cicli per saltare il resto dell'iterazione corrente |
| `goto` | Saltare a un'etichetta | Raramente utilizzato, principalmente per gestione errori o uscita da cicli annidati |
| `return` | Uscire da una funzione | In qualsiasi punto di una funzione per terminare l'esecuzione e opzionalmente restituire un valore |

## Best practice

1. **Utilizzare `break` e `continue` con moderazione**:
   - Usare `break` quando è necessario uscire anticipatamente da un ciclo
   - Usare `continue` quando è necessario saltare alcune iterazioni
   - Evitare di utilizzarli eccessivamente, poiché possono rendere il flusso del programma difficile da seguire

2. **Evitare l'uso di `goto` quando possibile**:
   - Preferire altre strutture di controllo come cicli, condizioni e funzioni
   - Utilizzare `goto` solo in casi specifici come la gestione centralizzata degli errori

3. **Utilizzare `return` in modo efficace**:
   - Utilizzare return anticipati per semplificare la logica del codice
   - Assicurarsi che tutte le funzioni non void restituiscano un valore in ogni percorso di esecuzione
   - Utilizzare valori di ritorno significativi per indicare successo o errore

4. **Mantenere il flusso di controllo chiaro e leggibile**:
   - Evitare salti complicati che rendono difficile seguire il flusso del programma
   - Commentare adeguatamente il codice che utilizza istruzioni di salto
   - Considerare la ristrutturazione del codice se richiede molti salti

## Esempi pratici

### Ricerca in un array

```c
#include <stdio.h>

int trova_elemento(int array[], int dimensione, int elemento) {
    int i;
    
    for (i = 0; i < dimensione; i++) {
        if (array[i] == elemento) {
            return i;  // Restituisce l'indice dell'elemento trovato
        }
    }
    
    return -1;  // Elemento non trovato
}

int main() {
    int numeri[] = {10, 25, 8, 14, 3, 56, 42};
    int dimensione = sizeof(numeri) / sizeof(numeri[0]);
    int elemento = 14;
    int posizione;
    
    posizione = trova_elemento(numeri, dimensione, elemento);
    
    if (posizione != -1) {
        printf("L'elemento %d è stato trovato alla posizione %d\n", elemento, posizione);
    } else {
        printf("L'elemento %d non è stato trovato nell'array\n", elemento);
    }
    
    return 0;
}
```

### Elaborazione di input con validazione

```c
#include <stdio.h>

int main() {
    int numero;
    int somma = 0;
    int contatore = 0;
    
    printf("Inserisci numeri positivi (0 o negativo per terminare):\n");
    
    while (1) {  // Ciclo infinito
        printf("Numero %d: ", contatore + 1);
        scanf("%d", &numero);
        
        if (numero <= 0) {
            break;  // Esce dal ciclo se il numero è 0 o negativo
        }
        
        somma += numero;
        contatore++;
    }
    
    if (contatore == 0) {
        printf("Nessun numero valido inserito\n");
        return 1;  // Termina il programma con codice di errore
    }
    
    printf("Hai inserito %d numeri\n", contatore);
    printf("La somma è %d\n", somma);
    printf("La media è %.2f\n", (float)somma / contatore);
    
    return 0;
}
```

### Gestione di errori in una funzione di allocazione

```c
#include <stdio.h>
#include <stdlib.h>

int* crea_array(int dimensione) {
    int *array;
    
    if (dimensione <= 0) {
        printf("Errore: dimensione non valida\n");
        return NULL;  // Restituisce NULL in caso di errore
    }
    
    array = (int*)malloc(dimensione * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione di memoria fallita\n");
        return NULL;  // Restituisce NULL in caso di errore
    }
    
    // Inizializza l'array
    for (int i = 0; i < dimensione; i++) {
        array[i] = i * 10;
    }
    
    return array;  // Restituisce il puntatore all'array allocato
}

int main() {
    int *numeri;
    int dimensione = 5;
    
    numeri = crea_array(dimensione);
    
    if (numeri == NULL) {
        printf("Impossibile creare l'array\n");
        return 1;  // Termina il programma con codice di errore
    }
    
    printf("Array creato con successo:\n");
    for (int i = 0; i < dimensione; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    free(numeri);  // Libera la memoria allocata
    return 0;
}
```

### Implementazione di un menu con switch e break

```c
#include <stdio.h>

int main() {
    int scelta;
    int esci = 0;
    
    while (!esci) {
        printf("\nMenu:\n");
        printf("1. Opzione 1\n");
        printf("2. Opzione 2\n");
        printf("3. Opzione 3\n");
        printf("4. Esci\n");
        printf("Inserisci la tua scelta (1-4): ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                printf("Hai selezionato l'Opzione 1\n");
                // Codice per l'opzione 1
                break;
            case 2:
                printf("Hai selezionato l'Opzione 2\n");
                // Codice per l'opzione 2
                break;
            case 3:
                printf("Hai selezionato l'Opzione 3\n");
                // Codice per l'opzione 3
                break;
            case 4:
                printf("Uscita dal programma...\n");
                esci = 1;  // Imposta la variabile per uscire dal ciclo while
                break;
            default:
                printf("Scelta non valida. Inserisci un numero da 1 a 4.\n");
        }
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza principale tra `break` e `continue`?

2. In quali situazioni l'uso di `goto` potrebbe essere giustificato in C moderno?

3. Cosa succede se una funzione non void termina senza un'istruzione `return`?

4. Come si può utilizzare `break` per uscire da cicli annidati?

5. Quali sono i valori di ritorno convenzionali della funzione `main` e cosa significano?

## Esercizi proposti

1. Scrivi un programma che legga una sequenza di numeri interi (terminata da 0) e calcoli la somma dei numeri pari e la somma dei numeri dispari, utilizzando `continue` per saltare i numeri non necessari.

2. Implementa una funzione che cerchi un elemento in una matrice bidimensionale e restituisca le coordinate (riga e colonna) dell'elemento se trovato, o un valore speciale se non trovato.

3. Scrivi un programma che simuli un semplice sistema di login con un numero limitato di tentativi, utilizzando `break` per uscire dal ciclo quando l'utente inserisce le credenziali corrette o esaurisce i tentativi.

4. Implementa una funzione che verifichi se una stringa è un palindromo (si legge allo stesso modo da sinistra a destra e da destra a sinistra), utilizzando `return` per gestire casi speciali e ottimizzare il codice.

5. Scrivi un programma che simuli un semplice sistema di gestione degli errori per operazioni di file, utilizzando codici di errore appropriati e gestendo correttamente le risorse.