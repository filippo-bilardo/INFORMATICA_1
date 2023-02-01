/*
220 e 284 sono numeri amici
1184 e 1210 sono numeri amici
2620 e 2924 sono numeri amici
*/

#include <stdio.h>
#include <math.h>

int somma_divisori(int n) {
    int i, somma = 0;
    for (i = 1; i < n; i++) {
        if (n % i == 0) {
            somma += i;
        }
    }
    return somma;
}

int main() {
    int i, j;
    for (i = 1; i <= 3000; i++) {
        for (j = i + 1; j <= 3000; j++) {
            int somma_i = somma_divisori(i);
            int somma_j = somma_divisori(j);
            if (somma_i == j && somma_j == i) {
                printf("%d e %d sono numeri amici\n", i, j);
            }
        }
    }
    return 0;
}
