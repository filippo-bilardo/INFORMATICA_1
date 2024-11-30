/**
 * @file const.c
 * Esempio di utilizzo di costanti
 */

#include <stdio.h>

// Costante con define
#define PI 3.14159

int main()
{
    float raggio = 5.0;
    float area;

    // Costante con define
    area = PI * raggio * raggio;
    printf("L'area del cerchio di raggio %f è %f\n", raggio, area);

    // Costante con const
    const float PIGRECO = 3.14159;
    printf("Il valore di PI è %f\n", PIGRECO);

    return 0;
}