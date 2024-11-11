#include <stdio.h>
int main() {
    int numero;
    
    do {
        printf("Inserisci un numero maggiore di 10: ");
        scanf("%d", &numero);
    } while (numero <= 10);
    printf("Hai inserito un numero valido: %d\n", numero);

    return 0;
}
