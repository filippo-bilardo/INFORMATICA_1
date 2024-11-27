/**
 * esempio di inizializzazione vettore 
 * con numeri casuali
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vet_rand(int vet[], int n);
void vet_rand_2(int vet[], int n);
void vet_rand_3(int vet[], int min, int max);
void vet_stampa(int vet[], int n);

/**
 * Stampa un vettore di interi
 * @param vet il vettore da stampare
 * @param n il numero di elementi del vettore
 */
void vet_stampa(int vet[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

/**
 * Inizializzo un vettore di n elementi con numeri casuali
 * compresi tra 0 e 9.
 * @param vet il vettore da inizializzare
 * @param n il numero di elementi del vettore
 * @return none
 */
void vet_rand(int vet[], int n) {
    for (int i = 0; i < n; i++) {
        //generiamo un numero random tra 0 e 9 compresi
        vet[i] = rand() % 10;
    }
}

/**
 * Inizializzo un vettore di n elementi con numeri casuali
 * compresi tra 10 e 100 compresi.
 * @param vet il vettore da inizializzare
 * @param n il numero di elementi del vettore
 * @return none
 */
void vet_rand_2(int vet[], int n) {
    for (int i = 0; i < n; i++) {
        //generiamo un numero random tra 10 e 100 compresi
        vet[i] = rand() % 91 + 10;
    }
}

/**
 * Inizializzo un vettore di n elementi con numeri casuali
 * compresi tra min e max compresi.
 * @param vet il vettore da inizializzare
 * @param n il numero di elementi del vettore
 * @param min il valore minimo
 * @param max il valore massimo
 * @return none
 */
void vet_rand_3(int vet[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        //generiamo un numero random tra min e max compresi
        vet[i] = rand() % (max - min + 1) + min;
    }
}



int main() {
    int vet[100];

    // inizializzazione del generatore di numeri casuali
    // altrimenti i numeri generati saranno sempre gli stessi
    srand(time(NULL)); 

    // inizializzo il vettore con numeri casuali
    vet_rand(vet, 100);
    vet_stampa(vet, 100);
    printf("\n");   
    
    // inizializzo il vettore con numeri casuali
    // con valori tra 10 e 100 compresi
    vet_rand_2(vet, 100);
    vet_stampa(vet, 100);
    printf("\n");

    // inizializzo il vettore con numeri casuali
    // con valori tra 33 e 55 compresi
    vet_rand_3(vet, 100, 33, 55);
    vet_stampa(vet, 100);
    printf("\n");
}