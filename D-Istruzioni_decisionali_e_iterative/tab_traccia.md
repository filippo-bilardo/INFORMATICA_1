Ecco un esempio di codice C che calcola il massimo comune divisore (MCD) tra due numeri (in questo caso 48 e 12) utilizzando l'**algoritmo delle sottrazioni successive**. La tabella di traccia corrispondente mostrerà ogni passaggio dell'algoritmo, il valore corrente delle variabili e la riga di codice eseguita.

### Codice C per calcolare il MCD usando sottrazioni successive

```c
#include <stdio.h>

int main() {
    int a = 48;  // Inizializza il primo numero
    int b = 12;  // Inizializza il secondo numero

    while (a != b) {     // 3
        if (a > b) {     // 4
            a = a - b;   // 5
        } else {         // 6
            b = b - a;   // 7
        }
    }

    printf("Il MCD è: %d\n", a); // 8
    return 0;                   // 9
}
```

### Spiegazione dell'Algoritmo

L'algoritmo delle sottrazioni successive per trovare il MCD si basa sull'idea che:
- Se `a` è maggiore di `b`, allora `a - b` mantiene lo stesso MCD di `a` e `b`.
- Continuando a sottrarre il numero più piccolo dal più grande, i valori di `a` e `b` si avvicinano finché diventano uguali.
- Quando `a` e `b` sono uguali, quel valore è il MCD.

### Tabella di Traccia

Questa tabella traccia ogni passaggio dell'algoritmo, mostrando i valori delle variabili `a` e `b`, e la riga del codice in esecuzione in ogni passaggio.

| Passaggio | `a`  | `b`  | Riga Istruzione Corrente | Descrizione               |
|-----------|------|------|--------------------------|---------------------------|
| 1         | 48   | 12   | 3                        | Inizia il ciclo `while` con `a != b`. |
| 2         | 48   | 12   | 4                        | Verifica `if (a > b)`, vero. |
| 3         | 36   | 12   | 5                        | Esegui `a = a - b`, quindi `a = 36`. |
| 4         | 36   | 12   | 3                        | Ritorna all'inizio del ciclo `while`. |
| 5         | 36   | 12   | 4                        | Verifica `if (a > b)`, vero. |
| 6         | 24   | 12   | 5                        | Esegui `a = a - b`, quindi `a = 24`. |
| 7         | 24   | 12   | 3                        | Ritorna all'inizio del ciclo `while`. |
| 8         | 24   | 12   | 4                        | Verifica `if (a > b)`, vero. |
| 9         | 12   | 12   | 5                        | Esegui `a = a - b`, quindi `a = 12`. |
| 10        | 12   | 12   | 3                        | Ritorna all'inizio del ciclo `while`. |
| 11        | 12   | 12   | 8                        | `a` è uguale a `b`, quindi esce dal ciclo e stampa il risultato.|

### Descrizione dei Passaggi della Tabella di Traccia

1. **Passaggio 1**: Inizializza `a = 48` e `b = 12`. La condizione `a != b` è vera, quindi entra nel ciclo `while`.
2. **Passaggio 2-3**: Verifica la condizione `a > b` (48 > 12), che è vera. Esegue `a = a - b`, portando `a` a 36.
3. **Passaggi successivi**: Continua a sottrarre `b` da `a` ogni volta che `a > b`, riducendo progressivamente `a` (36 → 24 → 12).
4. **Passaggio 9**: Alla fine, `a` diventa uguale a `b` (entrambi valgono 12), quindi il ciclo `while` termina.
5. **Passaggio 11**: Stampa il valore di `a` come MCD, che è `12`.

### Output

```
Il MCD è: 12
```

### Conclusione

La tabella di traccia permette di visualizzare chiaramente il flusso di esecuzione del programma, evidenziando:
- Come si evolve il valore delle variabili `a` e `b` a ogni iterazione.
- Quale istruzione viene eseguita a ogni passaggio e come cambia il programma in base alle condizioni (`if (a > b)` o `else`).
- Quando il programma esce dal ciclo e produce il risultato finale. 

Questo approccio consente di comprendere meglio il funzionamento dell'algoritmo e di verificare la correttezza delle operazioni.