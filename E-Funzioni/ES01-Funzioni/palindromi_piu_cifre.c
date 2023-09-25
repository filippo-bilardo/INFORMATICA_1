#include <stdio.h>

void stampa_numeri_palindromi(int limite_inferiore, int limite_superiore) {
    for (int i = limite_inferiore; i <= limite_superiore; i++) {
        int numero = i;
        int numero_invertito = 0;

        while (numero > 0) {
            int cifra = numero % 10;
            numero_invertito = numero_invertito * 10 + cifra;
            numero /= 10;
        }

        if (numero_invertito == i) {
            printf("%d\n", i);
        }
    }
}

int main() {
    stampa_numeri_palindromi(10, 9999);
    return 0;
}
