/** ****************************************************************************************
* \mainpage divisori.c
*
* @brief Scrivere un programma che, richiesto un numero intero, visualizzi tutti i 
*        suoi divisori
* <specifiche del progetto>
* <specifiche del collaudo>
* 
* @author Filippo Bilardo
* @date 02/12/22 
* @version 1.0 02/12/22 Versione iniziale
*/
#include <stdio.h> //printf, scanf

int main() {

	int num, cont;
	
	printf("Calcolo dei divisori. Inserici un numero: ");
	scanf("%d",&num);
	
	for(cont=1; cont<num; cont++) {
        if(num%cont  == 0) {
	        printf("%d e' divisore di %d\n", cont, num);	
	    }
    }
	
	return 0;
}