//gcc pow.c -lm

#include <stdio.h>
#include <math.h>

int main()
{
    double base, power, result;

    printf("Inserisci la base: ");
    scanf("%lf", &base);

    printf("Inserisci l'esponente: ");
    scanf("%lf",&power);

    result = pow(base,power);

    printf("%.1lf^%.1lf = %.2lf\n\n", base, power, result);

    return 0;
}