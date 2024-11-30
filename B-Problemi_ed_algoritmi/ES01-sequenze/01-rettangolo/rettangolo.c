/* FB 06/2023
	gcc minore.c
	./a.out
   determinare il minore tra due numeri */
#include <stdio.h>

int main()
{
    float base, altezza;
    float perimetro, area;

    scanf("%f", &base);
    scanf("%f", &altezza);

    perimetro = base*2 + altezza*2;
    area = base*altezza;
    
    printf("Perimetro = %f\n", perimetro);
    printf("Area = %f\n", area);

	return 0;
}