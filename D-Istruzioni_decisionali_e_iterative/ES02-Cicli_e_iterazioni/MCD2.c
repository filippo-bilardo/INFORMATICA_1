/**
 * @file MCDc
 * @date 05/11/2023
 * 
 * @brief Calcola il Massimo Comune Divisore (MCD) di due numeri interi positivi utilizzando l'algoritmo di Euclide.
 * Il Massimo Comune Divisore (MCD) di due numeri interi positivi è il più grande numero intero positivo che divide
 * esattamente entrambi i numeri. Ad esempio, il MCD di 32 e 24 è 8, perché 8 divide esattamente 32 e 24, mentre il MCD
 * di 32 e 23 è 1, perché 1 è l'unico numero intero positivo che divide esattamente 32 e 23.
 * 
 * L'algoritmo di Euclide è il seguente:
 * 1. Si assegnano alle variabili num1 e num2 i due numeri interi positivi da analizzare.
 * 2. Si calcola il resto della divisione intera di num1 per num2 e si assegna il risultato alla variabile resto.
 * 3. Se resto è uguale a 0, il MCD è num2.
 * 4. Altrimenti, si assegna il valore di num2 alla variabile num1 e il valore di resto alla variabile num2, e si
 *   ritorna al passo 2.
 */
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
/*
@startuml
|Inizio|
start

:Inizializza a = 48;
:Inizializza b = 12;

while (a != b) is (a diverso da b?)

if (a > b) then (si)
  :a = a - b;
else (no)
  :b = b - a;
endif

endwhile (fine ciclo)

:Stampa "Il MCD è: " + a;

stop
@enduml

*/