/*
Scrivere una funzione che prende in input un numero intero e determina se è un numero 
amico. Un numero amico è un numero intero per il quale la somma dei divisori propri 
(escluso il numero stesso) è uguale ad un altro numero intero, chiamato numero amico. 
Ad esempio, i numeri 220 e 284 sono amici perché la somma dei divisori propri di 220 è 
1 + 2 + 4 + 5 + 10 + 11 + 20 + 22 + 44 + 55 + 110 = 284 e la somma dei divisori propri 
di 284 è 1 + 2 + 4 + 71 + 142 = 220.

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
    printf("Ricerca numeri amicabili tra 0 e 10.000\n");

    for(int num=0; num<10000; num++) {
        if (is_amicable(num)) {
            printf("Il numero %d è un numero amico\n", num);
        }
    }
    return 0;
}
