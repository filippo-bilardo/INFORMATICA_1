/*
Scrivere una funzione che prende in input un numero intero e restituisce la sua sequenza 
di Fibonacci corrispondente stampandola a schermo.

In questo esempio, la funzione fibonacci calcola e stampa la sequenza di Fibonacci per 
un numero intero specificato. La sequenza viene calcolata utilizzando un ciclo for che parte
dal terzo elemento (2), poiché i primi due elementi sono fissati a 0 e 1. Ad ogni iterazione, 
l'elemento successivo viene calcolato come somma dei due precedenti.

Infine, il codice principale nella funzione main legge un numero intero da tastiera e utilizza 
la funzione fibonacci per stampare la sequenza di Fibonacci corrispondente.
*/
#include <stdio.h>

void fibonacci(int num) {
    int prev = 0;
    int curr = 1;
    int next;
    printf("Sequenza di Fibonacci per il numero %d: %d %d", num, prev, curr);
    for (int i = 2; i < num; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
        printf(" %d", curr);
    }
    printf("\n");
}

int main() {
    int num;
    printf("Inserisci un numero: ");
    scanf("%d", &num);

    fibonacci(num);

    return 0;
}
