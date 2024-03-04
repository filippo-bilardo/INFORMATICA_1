/**
 * esempio di inizializzazione vettore 
 * con numeri casuali
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vet_rand();
void vet_rand_2();
void vet_rand_3(int vet[], int min, int max);

int main() {
    int vet[100];

    // inizializzazione del generatore di numeri casuali
    // altrimenti i numeri generati saranno sempre gli stessi
    srand(time(NULL)); 

    vet_rand();
    printf("\n");   
    printf("\n");   
    vet_rand_2();
    printf("\n");   
    vet_rand_3(vet, 45, 55);
    printf("\n");
}

void vet_rand() {
    int vet[10];

    for (int i = 0; i < 10; i++) {
        //generiamo un numero random tra 0 e 9 compresi
        vet[i] = rand() % 10;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void vet_rand_2() {
    int vet[100];
    int i;

    // Generiamo un numero random tra 10 e 100 compresi
    for (i = 0; i < 100; i++) {
        vet[i] = rand() % 91 + 10;
    }
    for (i = 0; i < 100; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

/**
 * Inizializzo un vettore di 100 elementi con numeri casuali
 * compresi tra i parametri min e max.
 * Stampiamo il vettore
 * @param vet il vettore da inizializzare
 * @param min il valore minimo
 * @param max il valore massimo
 * @return none
 */
void vet_rand_3(int vet[], int min, int max) {
    int i;

    for (i = 0; i < 100; i++) {
        vet[i] = rand() % (max - min + 1) + min;
    }

    for (i = 0; i < 100; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}