#include <stdio.h>

void stampa_palindromi(void) {
    int numero;
    for (numero = 10; numero <= 99; numero++) {
        int decina = numero / 10;
        int unita = numero % 10;
        if (decina == unita) {
            printf("%d\n", numero);
        }
    }
}

int is_palindrome(int num) {
    int reversed = 0, n = num;
    while (n > 0) {
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n /= 10;
    }
    return reversed == num;
}

void print_palindrome_numbers() {
    int i;
    for (i = 1000; i <= 9999; i++) {
        if (is_palindrome(i)) {
            printf("%d\n", i);
        }
    }
}

int palindromo_tre_cifre(int numero) {
    int cifra1 = numero / 100;
    int cifra3 = numero % 10;
    if (cifra1 == cifra3) {
        int cifra2 = (numero / 10) % 10;
        int numero_inv = cifra3 * 100 + cifra2 * 10 + cifra1;
        if (numero_inv == numero) {
            return 1;
        }
    }
    return 0;
}

void stampa_palindromi_tre_cifre() {
    int i;
    for (i = 100; i <= 999; i++) {
        if (palindromo_tre_cifre(i)) {
            printf("%d\n", i);
        }
    }
}


int main(void) {
    printf("I numeri palindromi a 2 cifre sono:\n");
    stampa_palindromi();
    printf("I numeri palindromi a 3 cifre sono:\n");
    stampa_palindromi_tre_cifre();
    printf("I numeri palindromi a 4 cifre sono:\n");
    print_palindrome_numbers();
    return 0;
}
