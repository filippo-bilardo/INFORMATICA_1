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
    int num1, num2;
    int mcd, resto;

    // Input dei due numeri dall'utente
    printf("Inserisci il primo numero diverso da 0: ");
    scanf("%d", &num1);

    printf("Inserisci il secondo numero diverso da 0: ");
    scanf("%d", &num2);

    // Stampare il MCD
    printf("Il Massimo Comune Divisore (MCD) di %d e %d ", num1, num2);

    // Calcola il MCD utilizzando l'algoritmo di Euclide
    while (num2 != 0) {
        resto = num1 % num2;
        num1 = num2;
        num2 = resto;
    }
    mcd = num1;
    
    // Stampare il MCD
    printf("è: %d\n", mcd);

    return 0;
}

/*
@startuml
|Inizio|
start

:Inserisci il primo numero diverso da 0;
:Inserisci il secondo numero diverso da 0;

while (num2 != 0) is (num2 è diverso da 0?)
  :Calcola il resto della divisione di num1 per num2;
  :Assegna il valore di num2 a num1;
  :Assegna il valore di resto a num2;
endwhile (fine ciclo)

:Il MCD è num1;

stop
@enduml
*/