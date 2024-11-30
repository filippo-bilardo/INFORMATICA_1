#include <stdio.h>
  

int main() {
    int divisore = 10;
    int dividendo = 3;
    int quoziente, resto;

    quoziente = divisore / dividendo;
    printf("Il quoziente è %d\n", quoziente);
    resto = divisore % dividendo;
    printf("Il resto è %d\n", resto);

    divisore = 100;
    dividendo = 16;
    quoziente = divisore / dividendo;
    printf("Il quoziente è %d\n", quoziente);
    resto = divisore % dividendo;
    printf("Il resto è %d\n", resto);
    printf("verica divisore = dividendo * quoziente + resto = %d\n", dividendo * quoziente + resto);

    return 0;
}
    