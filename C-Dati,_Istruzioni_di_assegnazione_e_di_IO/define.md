La direttiva `#define` in C viene utilizzata per creare macro, che sono semplici sostituzioni di testo effettuate dal **preprocessore** prima che il codice venga compilato. È uno degli strumenti più potenti del preprocessore di C e può essere utilizzato per definire **costanti**, **macro** semplici o più complesse, che semplificano la scrittura del codice.

### Sintassi di base

La sintassi di una direttiva `#define` è la seguente:

```c
#define NOME_VALORE valore
```

Dove:
- `NOME_VALORE` è il nome della macro.
- `valore` è il valore o l'espressione che sostituisce `NOME_VALORE` nel codice.

### Esempio 1: Definire una costante

```c
#include <stdio.h>

#define PI 3.14159

int main() {
    printf("Il valore di PI è: %.2f\n", PI);
    return 0;
}
```

In questo esempio, ovunque venga scritto `PI`, il preprocessore sostituisce `PI` con `3.14159` prima della compilazione.

### Esempio 2: Definire una macro con argomenti

È possibile utilizzare `#define` per definire macro che accettano argomenti, simili a delle funzioni:

```c
#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int main() {
    int numero = 5;
    printf("Il quadrato di %d è: %d\n", numero, SQUARE(numero));
    return 0;
}
```

In questo caso, `SQUARE(x)` è una macro che calcola il quadrato di un numero. Quando il preprocessore trova `SQUARE(numero)`, sostituisce questa parte con `((numero) * (numero))`.

### Attenzione agli effetti collaterali

Le macro possono avere comportamenti inattesi se non utilizzate con attenzione. Ad esempio, se non si utilizzano le parentesi correttamente:

```c
#define DOUBLE(x) x + x

int main() {
    int risultato = DOUBLE(3) * 2; // Risultato inatteso: 3 + 3 * 2 = 3 + 6 = 9
    return 0;
}
```

In questo caso, l'espressione diventa `3 + 3 * 2`, che secondo la precedenza degli operatori aritmetici viene valutata come `3 + (3 * 2)`, risultando in `9` anziché `12`. Per evitare questo tipo di problemi, è sempre buona norma racchiudere l'intera macro e i suoi argomenti tra parentesi:

```c
#define DOUBLE(x) ((x) + (x))
```

### Utilizzi comuni di `#define`

1. **Definire costanti**: È spesso utilizzato per definire costanti simboliche, evitando così di utilizzare "numeri magici" nel codice.
2. **Compilazione condizionale**: Viene utilizzato insieme a direttive come `#ifdef`, `#ifndef`, `#endif` per includere o escludere porzioni di codice in base a determinate condizioni.
3. **Macro semplici e complesse**: Può essere utilizzato per scrivere macro che semplificano il codice e migliorano la leggibilità.

### Esempio di compilazione condizionale
```c
#include <stdio.h>

#define DEBUG

int main() {
#ifdef DEBUG
    printf("Modalità di debug attiva\n");
#endif
    printf("Programma principale\n");
    return 0;
}
```

In questo esempio, se la macro `DEBUG` è definita, verrà stampato "Modalità di debug attiva", altrimenti questa parte del codice verrà ignorata.

### Conclusione

`#define` è una funzionalità potente ma anche delicata. Le macro vengono sostituite direttamente nel codice dal preprocessore e non vengono controllate dal compilatore come le funzioni o le variabili. Per questo motivo, è importante utilizzarle con cura per evitare errori difficili da individuare.