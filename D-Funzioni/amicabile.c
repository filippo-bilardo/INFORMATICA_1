/*
In questo esempio, la funzione sum_divisors calcola la somma dei divisori di un numero. 
La funzione is_amicable determina se un numero è amico confrontando la somma dei divisori 
del numero con un altro numero e verificando che la somma dei divisori del secondo numero 
sia uguale al primo numero.

Infine, il codice principale nella funzione main legge un numero intero da tastiera e 
utilizza la funzione is_amicable per determinare se il numero inserito è un numero amico.
*/

#include <stdio.h>

int sum_divisors(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int is_amicable(int n) {
    int m = sum_divisors(n);
    return m != n && sum_divisors(m) == n;
}

int main() {
    int num;
    printf("Inserisci un numero: ");
    scanf("%d", &num);

    if (is_amicable(num)) {
        printf("Il numero %d è un numero amico\n", num);
    } else {
        printf("Il numero %d non è un numero amico\n", num);
    }

    return 0;
}
