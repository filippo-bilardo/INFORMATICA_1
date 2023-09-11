/*
Scrivere una funzione che ricerca i primi due numeri amicabili e li visualizzi sullo schermo.
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

int is_amicable(int n) {
    int m = sum_divisors(n);
    return m != n && sum_divisors(m) == n;
}

int main() {
    printf("Ricerca numeri amicabili tra 0 e 10.000\n");

    for(int num=0; num<10000; num++) {
        if (is_amicable(num)) {
            printf("Il numero %d è un numero amico\n", num);
        }
    }
    return 0;
}
