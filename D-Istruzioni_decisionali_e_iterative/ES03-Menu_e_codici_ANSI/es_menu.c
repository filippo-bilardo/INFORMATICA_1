/*
scrivere un programma C che richiami la funzione menushow. La funzione menushow utilizza un ciclo do-while per visualizzare un menu e chiedere all'utente di inserire una voce del menu fino a quando non sceglie 0=uscita. Stampare a schermo la scelta effettuata dall’utente e richiamare la funzione menurun(scelta). Visualizzare le voci di menu in blu. Dopo ogni scelta cancellare lo schermo e visualizzare nuovamente il menu. La funzione menurun(int scelta) esegue la funzione richiesta 
*/

#include <stdio.h>

int main() {
    int scelta;

    // Pulisce lo schermo
    printf("\033[2J\033[1;1H");

    // Visualizza il menu
    printf("\033[43m\033[31m*** Menu ***\n\033[0m");
    printf("\033[1;34m1. Opzione 1\n");
    printf("2. Opzione 2\n");
    printf("3. Opzione 3\n");
    printf("0. Uscita\n\033[0m");

    // Richiede all'utente di inserire una voce del menu
    printf("Inserisci la tua scelta: ");
    scanf("%d", &scelta);

    // Stampa la scelta effettuata
    printf("\nHai scelto l'opzione: %d\n", scelta);

    return 0;
}
