/**
 * File: unioni_base.c
 * Descrizione: Esempi base di definizione e utilizzo delle unioni in C
 */

#include <stdio.h>

// Definizione di un'unione semplice
union Numero {
    int i;
    float f;
    double d;
};

// Definizione di un'unione con array
union Dati {
    int numeri[10];
    char caratteri[40]; // Stessa area di memoria di numeri, ma interpretata come caratteri
    float valori[10];
};

int main() {
    // Esempio 1: Utilizzo base di un'unione
    printf("\n=== Esempio 1: Utilizzo base di un'unione ===\n");
    
    union Numero num;
    
    // Assegnazione di un intero
    num.i = 42;
    printf("num.i = %d\n", num.i);
    printf("num.f = %f\n", num.f); // Accesso non valido, ma legale in C
    printf("num.d = %lf\n", num.d); // Accesso non valido, ma legale in C
    
    // Assegnazione di un float (sovrascrive l'intero)
    num.f = 3.14159f;
    printf("\nDopo l'assegnazione di num.f = 3.14159f:\n");
    printf("num.i = %d\n", num.i); // Accesso non valido, ma legale in C
    printf("num.f = %f\n", num.f);
    printf("num.d = %lf\n", num.d); // Accesso non valido, ma legale in C
    
    // Assegnazione di un double (sovrascrive il float)
    num.d = 2.71828;
    printf("\nDopo l'assegnazione di num.d = 2.71828:\n");
    printf("num.i = %d\n", num.i); // Accesso non valido, ma legale in C
    printf("num.f = %f\n", num.f); // Accesso non valido, ma legale in C
    printf("num.d = %lf\n", num.d);
    
    // Esempio 2: Dimensione di un'unione
    printf("\n=== Esempio 2: Dimensione di un'unione ===\n");
    
    printf("Dimensione di int: %zu byte\n", sizeof(int));
    printf("Dimensione di float: %zu byte\n", sizeof(float));
    printf("Dimensione di double: %zu byte\n", sizeof(double));
    printf("Dimensione di union Numero: %zu byte\n", sizeof(union Numero));
    // La dimensione dell'unione è pari alla dimensione del suo membro più grande (double)
    
    // Esempio 3: Unione con array
    printf("\n=== Esempio 3: Unione con array ===\n");
    
    union Dati dati;
    
    // Inizializzazione dell'array di interi
    for (int i = 0; i < 10; i++) {
        dati.numeri[i] = i * 10;
    }
    
    // Stampa dei valori come interi
    printf("Valori come interi:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", dati.numeri[i]);
    }
    printf("\n");
    
    // Stampa dei valori come caratteri
    printf("Valori come caratteri:\n");
    for (int i = 0; i < 40; i++) {
        // Stampa solo caratteri stampabili
        if (dati.caratteri[i] >= 32 && dati.caratteri[i] <= 126) {
            printf("%c ", dati.caratteri[i]);
        } else {
            printf(". ");
        }
    }
    printf("\n");
    
    // Esempio 4: Inizializzazione di un'unione
    printf("\n=== Esempio 4: Inizializzazione di un'unione ===\n");
    
    // Inizializzazione del primo membro
    union Numero num1 = {100};
    printf("num1.i = %d\n", num1.i);
    
    // In C99 e successivi, è possibile specificare quale membro inizializzare
    union Numero num2 = {.f = 3.14159f};
    printf("num2.f = %f\n", num2.f);
    
    return 0;
}