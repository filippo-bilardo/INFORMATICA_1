/* FB 06/2023
   determinare minore */
#include <stdio.h>

int main()
{
	int num1, num2;    //dichiararazione dell variabili
	
	printf("Inserisci il valore del primo numero\n");
	scanf("%d", &num1);  
	
	printf("Inserisci il valore del secondo numero\n");
	scanf("%d", &num2);
	
	printf("il numero minore e': ");
	if(num1>num2)   //verifichiamo se num1 è maggiore di num2
	{
		//se la condizione è vera
		printf("%d", num2);
	}
	else 
	{
		//se la condizione è falsa
		printf("%d", num1);
	}

	return 0;
}