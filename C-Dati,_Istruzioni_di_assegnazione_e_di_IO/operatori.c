/**
 * Programma che mostra l'utilizzo degli operatori aritmetici
 * 
 */

#include <stdio.h> // printf, scanf

int main(void) {
    int a=10, b=3;
    float x;
    int y;

    // Operazioni aritmetiche
    x = (float)a / b; // 10 / 3 = 3.33
    y = a / b; // 10 / 3 = 3
    printf("a / b = %.2f\n", x);
    printf("a / b = %d\n", y);

    x = a % b; // 10 % 3 = 1
    printf("a %% b = %.2f\n", x);

    return 0;
}