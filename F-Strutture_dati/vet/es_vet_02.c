/**
 * file: es_vet_02.c
 * 
 * Il programma inizializza un vettore di 5 elementi con i valori 0, 1, 2, 3, 4
 * 
 * data: 
*/
#include <stdio.h>

int main(void)
{
	int i, t[5];

	t[4] = 0;
	for (i = 3; i >= 0; i--)
	{
		t[i] = t[i + 1] + i;
		printf("t[%d]=%d; ", i, t[i]);
	}
	printf("\nt[0]=%d; \n", t[0]);
}
