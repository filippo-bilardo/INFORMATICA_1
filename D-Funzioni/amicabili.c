/*
Scrivere una funzione che ricerca i primi due numeri amicabili e li visualizzi sullo schermo.

In questo esempio, la funzione sum_divisors calcola la somma dei divisori di un numero. 
La funzione find_amicable_numbers cerca i numeri amicabili confrontando la somma dei divisori 
dei due numeri n1 e n2 e, se sono amicabili, li visualizza sullo schermo.

Infine, il codice principale nella funzione main utilizza un doppio ciclo for per cercare 
i primi due numeri amicabili tra 1 e 10.000. Questo può essere modificato per cercare numeri 
amicabili in un intervallo più ampio o più piccolo.
*/

#include <stdio.h>

int sum_divisors(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

void find_amicable_numbers(int n1, int n2) {
    int sum1 = sum_divisors(n1);
    int sum2 = sum_divisors(n2);
    if (sum1 == n2 && sum2 == n1) {
        printf("I numeri amicabili sono %d e %d\n", n1, n2);
    }
}

int main() {
    for (int i = 1; i < 10000; i++) {
        for (int j = i + 1; j < 10000; j++) {
            find_amicable_numbers(i, j);
        }
    }
    return 0;
}
