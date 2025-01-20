#include <stdio.h>

double fattoriale(int n) {
    double res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

int main() {
    int n;
 
    printf("Inserisci un numero intero: ");
    scanf("%d", &n);

    printf("Il fattoriale di %d e' %f\n", n, fattoriale(n));
    return 0;
}


