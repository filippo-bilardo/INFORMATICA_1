# Puntatori a Funzioni in C

I puntatori a funzioni sono un concetto avanzato in C che permette di trattare le funzioni come dati, consentendo di passarle come argomenti ad altre funzioni, restituirle da funzioni o memorizzarle in array. Questa guida esplora i concetti fondamentali dei puntatori a funzioni, fornendo esempi pratici e consigli utili.

## Cos'è un Puntatore a Funzione?

Un puntatore a funzione è una variabile che memorizza l'indirizzo di una funzione. Proprio come un puntatore a un dato memorizza l'indirizzo di una variabile, un puntatore a funzione memorizza l'indirizzo di una funzione nel codice eseguibile.

### Dichiarazione di un Puntatore a Funzione

La sintassi per dichiarare un puntatore a funzione può sembrare complessa all'inizio:

```c
#include <stdio.h>

// Dichiarazione di una funzione normale
int somma(int a, int b) {
    return a + b;
}

int main() {
    // Dichiarazione di un puntatore a funzione
    int (*ptr_funzione)(int, int);
    
    // Assegnazione dell'indirizzo della funzione al puntatore
    ptr_funzione = somma;
    
    // Chiamata della funzione tramite puntatore
    int risultato = ptr_funzione(5, 3);
    
    printf("Risultato: %d\n", risultato);
    
    return 0;
}
```

La dichiarazione `int (*ptr_funzione)(int, int);` indica che `ptr_funzione` è un puntatore a una funzione che accetta due parametri di tipo `int` e restituisce un valore di tipo `int`.

### Sintassi Alternativa

È possibile utilizzare anche una sintassi alternativa con `typedef` per rendere il codice più leggibile:

```c
#include <stdio.h>

// Definizione di un tipo per puntatore a funzione
typedef int (*FunzioneOperazione)(int, int);

// Funzioni di esempio
int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

int moltiplicazione(int a, int b) {
    return a * b;
}

int divisione(int a, int b) {
    if (b != 0) return a / b;
    return 0; // Gestione semplificata della divisione per zero
}

int main() {
    // Dichiarazione di un puntatore a funzione usando il typedef
    FunzioneOperazione operazione;
    
    int a = 10, b = 5;
    
    // Utilizzo di diversi puntatori a funzione
    operazione = somma;
    printf("%d + %d = %d\n", a, b, operazione(a, b));
    
    operazione = sottrazione;
    printf("%d - %d = %d\n", a, b, operazione(a, b));
    
    operazione = moltiplicazione;
    printf("%d * %d = %d\n", a, b, operazione(a, b));
    
    operazione = divisione;
    printf("%d / %d = %d\n", a, b, operazione(a, b));
    
    return 0;
}
```

## Passaggio di Funzioni come Parametri

Uno degli usi più comuni dei puntatori a funzioni è il passaggio di funzioni come parametri ad altre funzioni. Questo permette di implementare strategie come le callback o l'iniezione di comportamenti.

```c
#include <stdio.h>

// Definizione del tipo per il puntatore a funzione
typedef int (*Comparatore)(int, int);

// Funzioni di confronto
int crescente(int a, int b) {
    return a - b; // Positivo se a > b, negativo se a < b, zero se a == b
}

int decrescente(int a, int b) {
    return b - a; // Positivo se b > a, negativo se b < a, zero se a == b
}

// Funzione di ordinamento che accetta un puntatore a funzione come criterio
void bubble_sort(int arr[], int n, Comparatore confronta) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Usa la funzione di confronto passata come parametro
            if (confronta(arr[j], arr[j + 1]) > 0) {
                // Scambia gli elementi
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Funzione per stampare un array
void stampa_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int numeri[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(numeri) / sizeof(numeri[0]);
    
    printf("Array originale: ");
    stampa_array(numeri, n);
    
    // Ordinamento crescente
    bubble_sort(numeri, n, crescente);
    printf("Ordinamento crescente: ");
    stampa_array(numeri, n);
    
    // Ordinamento decrescente
    bubble_sort(numeri, n, decrescente);
    printf("Ordinamento decrescente: ");
    stampa_array(numeri, n);
    
    return 0;
}
```

## Array di Puntatori a Funzioni

È possibile creare array di puntatori a funzioni, utili quando si vuole selezionare dinamicamente una funzione da un insieme predefinito.

```c
#include <stdio.h>

// Funzioni di esempio
float addizione(float a, float b) { return a + b; }
float sottrazione(float a, float b) { return a - b; }
float moltiplicazione(float a, float b) { return a * b; }
float divisione(float a, float b) { return b != 0 ? a / b : 0; }

int main() {
    // Array di puntatori a funzioni
    float (*operazioni[4])(float, float) = {
        addizione,
        sottrazione,
        moltiplicazione,
        divisione
    };
    
    // Nomi delle operazioni per l'output
    const char *nomi_operazioni[] = {
        "Addizione",
        "Sottrazione",
        "Moltiplicazione",
        "Divisione"
    };
    
    float a = 10.5f, b = 5.2f;
    
    // Esegui tutte le operazioni nell'array
    for (int i = 0; i < 4; i++) {
        float risultato = operazioni[i](a, b);
        printf("%s: %.2f %s %.2f = %.2f\n", 
               nomi_operazioni[i], 
               a, 
               i == 0 ? "+" : i == 1 ? "-" : i == 2 ? "*" : "/", 
               b, 
               risultato);
    }
    
    // Selezione dinamica di una funzione
    int scelta;
    do {
        printf("\nScegli un'operazione (0-3) o -1 per uscire: ");
        scanf("%d", &scelta);
        
        if (scelta >= 0 && scelta < 4) {
            float risultato = operazioni[scelta](a, b);
            printf("%s: %.2f %s %.2f = %.2f\n", 
                   nomi_operazioni[scelta], 
                   a, 
                   scelta == 0 ? "+" : scelta == 1 ? "-" : scelta == 2 ? "*" : "/", 
                   b, 
                   risultato);
        }
    } while (scelta >= 0 && scelta < 4);
    
    return 0;
}
```

## Puntatori a Funzioni come Valore di Ritorno

Una funzione può anche restituire un puntatore a un'altra funzione:

```c
#include <stdio.h>

// Definizione del tipo per il puntatore a funzione
typedef int (*Operazione)(int, int);

// Funzioni di operazione
int somma(int a, int b) { return a + b; }
int sottrazione(int a, int b) { return a - b; }
int moltiplicazione(int a, int b) { return a * b; }
int divisione(int a, int b) { return b != 0 ? a / b : 0; }

// Funzione che restituisce un puntatore a funzione in base al carattere dell'operazione
Operazione seleziona_operazione(char operatore) {
    switch (operatore) {
        case '+':
            return somma;
        case '-':
            return sottrazione;
        case '*':
            return moltiplicazione;
        case '/':
            return divisione;
        default:
            return NULL; // Operazione non supportata
    }
}

int main() {
    int a = 10, b = 5;
    char operatori[] = {'+', '-', '*', '/'};
    
    for (int i = 0; i < 4; i++) {
        // Ottieni il puntatore a funzione appropriato
        Operazione op = seleziona_operazione(operatori[i]);
        
        if (op != NULL) {
            int risultato = op(a, b);
            printf("%d %c %d = %d\n", a, operatori[i], b, risultato);
        } else {
            printf("Operazione non supportata\n");
        }
    }
    
    return 0;
}
```

## Callback e Funzioni di Ordine Superiore

I puntatori a funzioni sono fondamentali per implementare callback e funzioni di ordine superiore in C.

### Esempio di Callback

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definizione del tipo per la funzione di callback
typedef void (*Callback)(int, void*);

// Funzione che esegue un'operazione e chiama la callback per ogni risultato
void processa_dati(int dati[], int n, Callback callback, void *contesto) {
    for (int i = 0; i < n; i++) {
        // Esegue qualche elaborazione sui dati
        int risultato = dati[i] * 2;
        
        // Chiama la callback con il risultato
        callback(risultato, contesto);
    }
}

// Funzione di callback che stampa i risultati
void stampa_risultato(int risultato, void *contesto) {
    printf("Risultato: %d\n", risultato);
}

// Funzione di callback che accumula i risultati
void accumula_risultato(int risultato, void *contesto) {
    int *somma = (int*)contesto;
    *somma += risultato;
}

int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    // Crea un array di dati casuali
    int dati[10];
    for (int i = 0; i < 10; i++) {
        dati[i] = rand() % 100;
        printf("Dato %d: %d\n", i, dati[i]);
    }
    
    printf("\nElaborazione con callback di stampa:\n");
    processa_dati(dati, 10, stampa_risultato, NULL);
    
    // Accumula i risultati
    int somma = 0;
    processa_dati(dati, 10, accumula_risultato, &somma);
    printf("\nSomma dei risultati: %d\n", somma);
    
    return 0;
}
```

### Funzioni di Ordine Superiore

```c
#include <stdio.h>

// Definizione dei tipi per i puntatori a funzione
typedef int (*Trasformazione)(int);
typedef int (*Predicato)(int);
typedef void (*Consumatore)(int);

// Funzioni di trasformazione
int raddoppia(int x) { return x * 2; }
int quadrato(int x) { return x * x; }

// Funzioni predicato
int e_pari(int x) { return x % 2 == 0; }
int e_positivo(int x) { return x > 0; }

// Funzione di ordine superiore: map
void map(int arr[], int n, Trasformazione f, int risultato[]) {
    for (int i = 0; i < n; i++) {
        risultato[i] = f(arr[i]);
    }
}

// Funzione di ordine superiore: filter
int filter(int arr[], int n, Predicato p, int risultato[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (p(arr[i])) {
            risultato[count++] = arr[i];
        }
    }
    return count;
}

// Funzione di ordine superiore: forEach
void forEach(int arr[], int n, Consumatore c) {
    for (int i = 0; i < n; i++) {
        c(arr[i]);
    }
}

// Funzione consumatore di esempio
void stampa(int x) {
    printf("%d ", x);
}

int main() {
    int numeri[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    int n = sizeof(numeri) / sizeof(numeri[0]);
    int risultato[n];
    
    printf("Array originale: ");
    forEach(numeri, n, stampa);
    printf("\n\n");
    
    // Esempio di map
    map(numeri, n, raddoppia, risultato);
    printf("Dopo map(raddoppia): ");
    forEach(risultato, n, stampa);
    printf("\n");
    
    map(numeri, n, quadrato, risultato);
    printf("Dopo map(quadrato): ");
    forEach(risultato, n, stampa);
    printf("\n\n");
    
    // Esempio di filter
    int count = filter(numeri, n, e_pari, risultato);
    printf("Dopo filter(e_pari): ");
    forEach(risultato, count, stampa);
    printf("\n");
    
    count = filter(numeri, n, e_positivo, risultato);
    printf("Dopo filter(e_positivo): ");
    forEach(risultato, count, stampa);
    printf("\n");
    
    return 0;
}
```

## Considerazioni sulla Sicurezza

I puntatori a funzioni, come tutti i puntatori in C, richiedono attenzione per evitare problemi di sicurezza:

1. **Verifica dei Puntatori Nulli**: Controlla sempre che un puntatore a funzione non sia NULL prima di chiamarlo.

2. **Validazione delle Funzioni**: Assicurati che le funzioni chiamate tramite puntatori siano valide e sicure.

3. **Controllo dei Tipi**: Assicurati che i tipi dei parametri e del valore di ritorno corrispondano a quelli attesi.

```c
#include <stdio.h>

typedef int (*Operazione)(int, int);

int esegui_operazione_sicura(Operazione op, int a, int b) {
    // Verifica che il puntatore a funzione non sia NULL
    if (op == NULL) {
        fprintf(stderr, "Errore: puntatore a funzione NULL\n");
        return 0;
    }
    
    // Esegui l'operazione
    return op(a, b);
}

int main() {
    Operazione op = NULL;  // Puntatore a funzione non inizializzato
    
    // Tentativo di esecuzione sicura
    int risultato = esegui_operazione_sicura(op, 10, 5);
    printf("Risultato: %d\n", risultato);
    
    return 0;
}
```

## Best Practices

1. **Usa typedef**: Utilizza `typedef` per rendere le dichiarazioni di puntatori a funzioni più leggibili.

2. **Verifica i Puntatori Nulli**: Controlla sempre che un puntatore a funzione non sia NULL prima di chiamarlo.

3. **Documentazione Chiara**: Documenta chiaramente i parametri attesi e il comportamento delle funzioni passate come puntatori.

4. **Evita Cast Pericolosi**: Evita di convertire puntatori a funzioni tra tipi incompatibili.

5. **Preferisci Funzioni Statiche**: Quando possibile, utilizza funzioni statiche per limitare la visibilità delle funzioni utilizzate con i puntatori.

## Domande di Autovalutazione

1. Qual è la differenza tra un puntatore a funzione e una chiamata di funzione diretta?

2. Come si dichiara un puntatore a una funzione che accetta un intero e restituisce un double?

3. Quali sono i vantaggi dell'utilizzo dei puntatori a funzioni nelle callback?

4. Come si può implementare un sistema di plugin semplice utilizzando puntatori a funzioni?

5. Quali sono i rischi principali nell'utilizzo dei puntatori a funzioni e come mitigarli?

## Esercizi Proposti

1. Implementa una funzione `qsort` personalizzata che utilizzi un puntatore a funzione come comparatore.

2. Crea un sistema di gestione degli eventi semplice utilizzando array di puntatori a funzioni.

3. Implementa una funzione `map` che applichi una trasformazione a tutti gli elementi di un array di double.

4. Scrivi un programma che utilizzi puntatori a funzioni per implementare una calcolatrice con operazioni personalizzabili.

5. Crea una libreria di funzioni di ordinamento che permetta di selezionare dinamicamente l'algoritmo di ordinamento da utilizzare.