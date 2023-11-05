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

    // Input dei due numeri dall'utente
    printf("Inserisci il primo numero: ");
    scanf("%d", &num1);

    printf("Inserisci il secondo numero: ");
    scanf("%d", &num2);

    int mcd, resto;

    // Calcola il MCD utilizzando l'algoritmo di Euclide
    if (num1 == 0 || num2 == 0) {
        mcd = 0;
    } else {
        while (num2 != 0) {
            resto = num1 % num2;
            num1 = num2;
            num2 = resto;
        }
        mcd = num1;
    }

    // Stampare il MCD
    printf("Il Massimo Comune Divisore (MCD) di %d e %d è: %d\n", num1, num2, mcd);

    return 0;
}
