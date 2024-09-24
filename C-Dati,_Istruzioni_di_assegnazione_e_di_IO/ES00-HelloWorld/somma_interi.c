/** 
 * file: somma_interi.c 
 * autore: Mario Rossi 
 * classe: 
 * data: 21/09/2022 
 * 
 * Somma di due numeri interi letti da tastiera e stampa 
 * a schermo del risultato 
 * 
 * Input: due numeri interi 
 * Elaborazione: somma 
 * Output: un numero intero
 */
#include <stdio.h> //printf, scanf

int main() { 
    //dichiariamo Le due variabili input 
    int num1, num2; 
    //e output 
    int ris; 
    
    //Input: due numeri interi 
    printf("Iserisci il primo numero "); 
    scanf("%d", &num1); 
    printf("Iserisci il secondo numero "); 
    scanf("%d", &num2); 
    
    //Elaborazione: somma 
    //assegna alla variabile ris 
    //il risultato della espressione num1 + num2 
    ris = num1 + num2; 
    
    //output: un numero intero 
    printf("La somma dei due numeri e' %d\n", ris); 
    
    //termino il programma 
    return 0; 
}
