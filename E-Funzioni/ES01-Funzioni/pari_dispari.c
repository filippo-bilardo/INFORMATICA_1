/*
Scrivere la funzione int pari_dispari(in numero), attraverso sottrazioni successive 
determinare se il numero passato alla funzione è pari o dispari, restituire 0 se il 
numero è pari, 1 se dispari.

In questo esempio, la funzione pari_dispari determina se un numero è pari o dispari 
utilizzando sottrazioni successive. Se il numero passato alla funzione è pari, il
risultato finale sarà 0, altrimenti sarà 1.

Infine, il codice principale nella funzione main legge un numero intero da tastiera 
e utilizza la funzione pari_dispari per determinare se il numero inserito è pari o dispari.
*/
#include <stdio.h>

int pari_dispari(int numero) {
    int result = numero;
    while (result >= 2) {
        result -= 2;
    }
    return result;
}

int main() {
    int num;
    printf("Inserisci un numero: ");
    scanf("%d", &num);

    int risultato = pari_dispari(num);
    if (risultato == 0) {
        printf("Il numero %d è pari\n", num);
    } else {
        printf("Il numero %d è dispari\n", num);
    }

    return 0;
}
