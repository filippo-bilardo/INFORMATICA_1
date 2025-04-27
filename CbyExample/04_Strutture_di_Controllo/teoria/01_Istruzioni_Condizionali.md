# Istruzioni condizionali in C

Le istruzioni condizionali sono fondamentali nella programmazione perché permettono di eseguire blocchi di codice diversi in base a determinate condizioni. In C, le principali istruzioni condizionali sono `if-else`, `switch-case` e l'operatore ternario.

## Istruzione if-else

L'istruzione `if-else` è la forma più comune di controllo condizionale. Permette di eseguire un blocco di codice se una condizione è vera, e opzionalmente un altro blocco se la condizione è falsa.

### Sintassi di base

```c
if (condizione) {
    // Codice eseguito se la condizione è vera
} else {
    // Codice eseguito se la condizione è falsa
}
```

### Esempio semplice

```c
#include <stdio.h>

int main() {
    int numero = 10;
    
    if (numero > 0) {
        printf("Il numero è positivo\n");
    } else {
        printf("Il numero è negativo o zero\n");
    }
    
    return 0;
}
```

### Istruzione if-else if-else

Per verificare più condizioni in sequenza, si può utilizzare la struttura `if-else if-else`:

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

### Istruzioni if annidate

È possibile inserire un'istruzione `if` all'interno di un'altra istruzione `if` o `else`:

```c
#include <stdio.h>

int main() {
    int eta = 25;
    int reddito = 30000;
    
    if (eta >= 18) {
        printf("Sei maggiorenne\n");
        
        if (reddito > 25000) {
            printf("Hai un reddito superiore alla media\n");
        } else {
            printf("Hai un reddito nella media o inferiore\n");
        }
    } else {
        printf("Sei minorenne\n");
    }
    
    return 0;
}
```

### Blocchi if senza parentesi graffe

Se il blocco di codice da eseguire contiene una sola istruzione, le parentesi graffe possono essere omesse (ma è generalmente sconsigliato per motivi di leggibilità e manutenibilità):

```c
if (numero > 0)
    printf("Il numero è positivo\n");
else
    printf("Il numero è negativo o zero\n");
```

## Istruzione switch-case

L'istruzione `switch-case` è un'alternativa all'istruzione `if-else if-else` quando si devono confrontare una variabile con diversi valori costanti.

### Sintassi di base

```c
switch (espressione) {
    case valore1:
        // Codice eseguito se espressione == valore1
        break;
    case valore2:
        // Codice eseguito se espressione == valore2
        break;
    // Altri casi...
    default:
        // Codice eseguito se nessun caso corrisponde
}
```

### Esempio di switch-case

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

### Caratteristiche importanti di switch-case

1. **L'espressione deve essere di tipo intero** (char, int, enum, ma non float o string).
2. **I valori dei case devono essere costanti** (non variabili o espressioni che si valutano a runtime).
3. **L'istruzione `break` è fondamentale** per uscire dallo switch dopo l'esecuzione di un caso. Se omessa, l'esecuzione continua con il caso successivo (comportamento noto come "fall-through").
4. **Il caso `default` è opzionale** e viene eseguito se nessun altro caso corrisponde.

### Esempio di fall-through (senza break)

```c
#include <stdio.h>

int main() {
    int giorno = 3;  // 1 = Lunedì, 7 = Domenica
    
    switch (giorno) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Giorno lavorativo\n");
            break;
        case 6:
        case 7:
            printf("Weekend\n");
            break;
        default:
            printf("Giorno non valido\n");
    }
    
    return 0;
}
```

In questo esempio, il fall-through è utilizzato intenzionalmente per raggruppare casi che condividono lo stesso comportamento.

## Operatore ternario

L'operatore ternario (`? :`) è una forma compatta di istruzione condizionale che può essere utilizzata per assegnazioni semplici o espressioni.

### Sintassi di base

```c
condizione ? espressione_se_vera : espressione_se_falsa
```

### Esempio di operatore ternario

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;
    int max;
    
    // Equivalente a:
    // if (a > b) {
    //     max = a;
    // } else {
    //     max = b;
    // }
    max = (a > b) ? a : b;
    
    printf("Il valore massimo è: %d\n", max);
    
    // L'operatore ternario può essere utilizzato direttamente in un'espressione
    printf("Il numero %d è %s\n", a, (a % 2 == 0) ? "pari" : "dispari");
    
    return 0;
}
```

### Operatori ternari annidati

Gli operatori ternari possono essere annidati, ma questo può rendere il codice difficile da leggere:

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 15;
    int max;
    
    // Trova il massimo tra tre numeri
    max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    
    printf("Il valore massimo è: %d\n", max);
    
    return 0;
}
```

In casi come questo, è generalmente preferibile utilizzare istruzioni `if-else` per maggiore chiarezza.

## Confronto tra le diverse istruzioni condizionali

| Istruzione | Vantaggi | Svantaggi | Uso consigliato |
|------------|----------|-----------|----------------|
| `if-else` | Flessibile, può valutare qualsiasi espressione | Può diventare verboso con molte condizioni | Per condizioni generiche e logica complessa |
| `switch-case` | Chiaro e leggibile per confronti multipli con una singola variabile | Limitato a confronti di uguaglianza con costanti intere | Per confrontare una variabile con molti valori costanti |
| Operatore ternario | Conciso, ideale per assegnazioni semplici | Può diventare illeggibile se annidato o complesso | Per condizioni semplici e assegnazioni brevi |

## Best practice

1. **Utilizzare le parentesi graffe anche per blocchi di una sola istruzione**:
   ```c
   // Preferibile
   if (condizione) {
       istruzione;
   }
   
   // Evitare
   if (condizione)
       istruzione;
   ```

2. **Evitare if-else troppo annidati**:
   - Utilizzare funzioni separate per logica complessa
   - Considerare l'uso di variabili booleane intermedie
   - Utilizzare il return anticipato quando possibile

3. **Utilizzare sempre `break` in switch-case** a meno che il fall-through non sia intenzionale e documentato.

4. **Limitare l'uso dell'operatore ternario a espressioni semplici** per mantenere il codice leggibile.

5. **Indentare correttamente il codice** per rendere chiara la struttura delle condizioni.

## Esempi pratici

### Calcolo dell'importo di uno sconto

```c
#include <stdio.h>

int main() {
    float importo, sconto, importo_finale;
    
    printf("Inserisci l'importo: ");
    scanf("%f", &importo);
    
    if (importo > 1000) {
        sconto = importo * 0.15;  // 15% di sconto
    } else if (importo > 500) {
        sconto = importo * 0.10;  // 10% di sconto
    } else if (importo > 100) {
        sconto = importo * 0.05;  // 5% di sconto
    } else {
        sconto = 0;  // Nessuno sconto
    }
    
    importo_finale = importo - sconto;
    
    printf("Importo originale: %.2f\n", importo);
    printf("Sconto applicato: %.2f\n", sconto);
    printf("Importo finale: %.2f\n", importo_finale);
    
    return 0;
}
```

### Menu di selezione con switch-case

```c
#include <stdio.h>

int main() {
    int scelta;
    
    printf("Menu:\n");
    printf("1. Visualizza dati\n");
    printf("2. Inserisci nuovo dato\n");
    printf("3. Modifica dato esistente\n");
    printf("4. Elimina dato\n");
    printf("5. Esci\n");
    printf("Inserisci la tua scelta (1-5): ");
    scanf("%d", &scelta);
    
    switch (scelta) {
        case 1:
            printf("Hai scelto: Visualizza dati\n");
            // Codice per visualizzare i dati
            break;
        case 2:
            printf("Hai scelto: Inserisci nuovo dato\n");
            // Codice per inserire un nuovo dato
            break;
        case 3:
            printf("Hai scelto: Modifica dato esistente\n");
            // Codice per modificare un dato
            break;
        case 4:
            printf("Hai scelto: Elimina dato\n");
            // Codice per eliminare un dato
            break;
        case 5:
            printf("Uscita dal programma...\n");
            break;
        default:
            printf("Scelta non valida. Inserisci un numero da 1 a 5.\n");
    }
    
    return 0;
}
```

### Validazione dell'input con operatore ternario

```c
#include <stdio.h>

int main() {
    int eta;
    
    printf("Inserisci la tua età: ");
    scanf("%d", &eta);
    
    printf("Input %s\n", (eta >= 0 && eta <= 120) ? "valido" : "non valido");
    
    // Se l'input è valido, verifica se la persona è maggiorenne
    if (eta >= 0 && eta <= 120) {
        printf("Sei %s\n", (eta >= 18) ? "maggiorenne" : "minorenne");
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza principale tra `if-else if-else` e `switch-case`?

2. Cosa succede se si omette l'istruzione `break` in un caso di `switch`?

3. In quali situazioni è preferibile utilizzare l'operatore ternario invece di `if-else`?

4. Come si può implementare un controllo di intervallo (ad esempio, verificare se un numero è compreso tra 1 e 10) utilizzando le istruzioni condizionali?

5. Quali sono i vantaggi e gli svantaggi dell'annidamento di istruzioni condizionali?

## Esercizi proposti

1. Scrivi un programma che legga tre numeri e li stampi in ordine crescente utilizzando solo istruzioni `if-else`.

2. Implementa una calcolatrice semplice che accetti due numeri e un operatore (+, -, *, /, %) e mostri il risultato utilizzando `switch-case`.

3. Scrivi un programma che determini se un anno inserito dall'utente è bisestile utilizzando le istruzioni condizionali appropriate.

4. Implementa un programma che converta un voto numerico (0-100) in un voto letterale (A, B, C, D, F) utilizzando sia `if-else if-else` che `switch-case`. Confronta le due implementazioni.

5. Scrivi un programma che simuli un semplice sistema di autenticazione: chiedi all'utente di inserire un nome utente e una password, e verifica se corrispondono a valori predefiniti. Utilizza l'operatore ternario per fornire un messaggio appropriato.