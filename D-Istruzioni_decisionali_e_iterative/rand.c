/**
 * Esempio di utilizzo della funzione rand() 
 * per generare numeri casuali
 * 
 * gcc rand.c -o rand
 * ./rand
 * 
 * (c) FB 13/11/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));

    //Genera un numero casuale tra 0 e RAND_MAX
    //RAND_MAX è una costante definita in stdlib.h
    //che rappresenta il massimo valore che può essere generato
    //RAND_MAX è 32767 su sistemi a 16 bit
    //RAND_MAX è 2147483647 su sistemi a 32 bit
    //RAND_MAX è 9223372036854775807 su sistemi a 64 bit
    int n = rand();
    printf("Numero casuale tra 0 e RAND_MAX: %d\n", n);


    //Per generare un numero casuale tra 0 e 99
    //divido il numero generato per 100 e prendo il resto
    //otteniamo così un numero casuale tra 0 e 99
    n = rand() % 100;
    printf("Numero casuale tra 0 e 99: %d\n", n);

    //Per generare un numero casuale tra 0 e 27
    //divido il numero generato per 28 e prendo il resto
    //otteniamo così un numero casuale tra 0 e 27
    n = rand() % 28;
    printf("Numero casuale tra 0 e 27: %d\n", n);

    //Per generare un numero casuale tra 51 e 100
    //divido il numero generato per 50 e aggiungo 51
    //otteniamo così un numero casuale tra 51 e 100
    n = rand() % 50 + 51;
    printf("Numero casuale tra 51 e 100: %d\n", n);

    //Per generare un numero casuale tra 1 e 6
    //divido il numero generato per 6 e aggiungo 1
    //otteniamo così un numero casuale tra 1 e 6
    n = rand() % 6 + 1;
    printf("Numero casuale tra 1 e 6: %d\n", n);

    //Per generare un numero casuale tra 1 e 1000
    //divido il numero generato per 1000 e aggiungo 1
    //otteniamo così un numero casuale tra 1 e 1000
    n = rand() % 1000 + 1;
    printf("Numero casuale tra 1 e 1000: %d\n", n);

    // Stampa di 10 numeri casuali
    // Compresi tra 0 e 9
    printf("10 numeri casuali tra 0 e 9: [ ");
    for(int i = 0 ; i < 10 ; i++ )
    {
        printf("%d ", rand()%10);
    }
    printf("]\n");

    return(0);
}