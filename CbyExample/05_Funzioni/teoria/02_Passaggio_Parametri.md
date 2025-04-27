# Passaggio di parametri nelle funzioni in C

Il passaggio di parametri è un meccanismo fondamentale che permette alle funzioni di ricevere dati dall'esterno e di operare su di essi. In C, esistono diversi modi per passare i parametri alle funzioni, ciascuno con caratteristiche e utilizzi specifici.

## Passaggio per valore

In C, il metodo predefinito per passare i parametri è il **passaggio per valore**. Quando un parametro viene passato per valore, la funzione riceve una copia del valore originale. Questo significa che qualsiasi modifica apportata al parametro all'interno della funzione non influisce sul valore originale.

### Esempio di passaggio per valore

```c
#include <stdio.h>

// Funzione che tenta di modificare il valore del parametro
void modifica_valore(int numero) {
    numero = numero * 2;  // Modifica solo la copia locale
    printf("Valore all'interno della funzione: %d\n", numero);
}

int main() {
    int x = 10;
    
    printf("Valore prima della chiamata: %d\n", x);
    modifica_valore(x);
    printf("Valore dopo la chiamata: %d\n", x);  // Il valore rimane invariato
    
    return 0;
}
```

Output:
```
Valore prima della chiamata: 10
Valore all'interno della funzione: 20
Valore dopo la chiamata: 10
```

Come si può notare, il valore di `x` non cambia dopo la chiamata alla funzione, perché la funzione ha operato su una copia del valore originale.

### Vantaggi del passaggio per valore

1. **Sicurezza**: I dati originali sono protetti da modifiche accidentali
2. **Isolamento**: La funzione opera su una copia locale, senza effetti collaterali
3. **Semplicità**: È il metodo più intuitivo e facile da comprendere

### Svantaggi del passaggio per valore

1. **Overhead di memoria**: Per dati di grandi dimensioni, creare una copia può essere costoso
2. **Impossibilità di modificare i dati originali**: Se si desidera che la funzione modifichi i dati originali, il passaggio per valore non è adatto

## Passaggio per riferimento (tramite puntatori)

In C, non esiste un vero e proprio passaggio per riferimento come in altri linguaggi, ma è possibile ottenere un effetto simile utilizzando i **puntatori**. Passando l'indirizzo di una variabile (anziché il suo valore), la funzione può accedere e modificare il valore originale.

### Esempio di passaggio per riferimento

```c
#include <stdio.h>

// Funzione che modifica il valore tramite puntatore
void modifica_valore_ptr(int *numero_ptr) {
    *numero_ptr = *numero_ptr * 2;  // Modifica il valore originale
    printf("Valore all'interno della funzione: %d\n", *numero_ptr);
}

int main() {
    int x = 10;
    
    printf("Valore prima della chiamata: %d\n", x);
    modifica_valore_ptr(&x);  // Passa l'indirizzo di x
    printf("Valore dopo la chiamata: %d\n", x);  // Il valore è stato modificato
    
    return 0;
}
```

Output:
```
Valore prima della chiamata: 10
Valore all'interno della funzione: 20
Valore dopo la chiamata: 20
```

In questo caso, il valore di `x` viene effettivamente modificato dalla funzione, perché la funzione ha accesso diretto alla variabile originale tramite il suo indirizzo.

### Vantaggi del passaggio per riferimento

1. **Efficienza**: Non viene creata una copia dei dati, solo l'indirizzo viene passato
2. **Possibilità di modificare i dati originali**: La funzione può modificare i valori delle variabili chiamanti
3. **Restituzione di più valori**: Permette a una funzione di restituire più valori modificando variabili passate per riferimento

### Svantaggi del passaggio per riferimento

1. **Rischio di modifiche indesiderate**: I dati originali possono essere modificati accidentalmente
2. **Complessità**: L'uso dei puntatori può rendere il codice più difficile da leggere e mantenere
3. **Potenziali problemi di sicurezza**: Se non gestiti correttamente, i puntatori possono causare accessi a memoria non valida

## Passaggio di array

In C, gli array sono sempre passati per riferimento, anche se non si utilizza esplicitamente la sintassi dei puntatori. Quando si passa un array a una funzione, ciò che viene effettivamente passato è l'indirizzo del primo elemento dell'array.

### Esempio di passaggio di array

```c
#include <stdio.h>

// Funzione che modifica un array
void raddoppia_elementi(int arr[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        arr[i] = arr[i] * 2;  // Modifica l'array originale
    }
}

// Funzione alternativa che usa la notazione dei puntatori
void raddoppia_elementi_ptr(int *arr, int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        *(arr + i) = *(arr + i) * 2;  // Equivalente a arr[i] = arr[i] * 2
    }
}

int main() {
    int numeri[5] = {1, 2, 3, 4, 5};
    
    printf("Array originale: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    raddoppia_elementi(numeri, 5);
    
    printf("Array dopo la modifica: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    return 0;
}
```

Output:
```
Array originale: 1 2 3 4 5 
Array dopo la modifica: 2 4 6 8 10 
```

### Importante: passaggio della dimensione

Quando si passa un array a una funzione, è necessario passare anche la sua dimensione, poiché l'informazione sulla dimensione dell'array viene persa durante il passaggio.

```c
void funzione_array(int arr[], int dimensione) {
    // La dimensione deve essere passata esplicitamente
    for (int i = 0; i < dimensione; i++) {
        // Operazioni sull'array
    }
}
```

## Passaggio di strutture

Le strutture in C possono essere passate sia per valore che per riferimento.

### Passaggio di strutture per valore

```c
#include <stdio.h>

// Definizione di una struttura
typedef struct {
    int x;
    int y;
} Punto;

// Passaggio per valore
void sposta_punto(Punto p, int dx, int dy) {
    p.x += dx;  // Modifica solo la copia locale
    p.y += dy;
    printf("Coordinate all'interno della funzione: (%d, %d)\n", p.x, p.y);
}

int main() {
    Punto punto = {10, 20};
    
    printf("Coordinate originali: (%d, %d)\n", punto.x, punto.y);
    sposta_punto(punto, 5, 5);
    printf("Coordinate dopo la chiamata: (%d, %d)\n", punto.x, punto.y);  // Non cambiano
    
    return 0;
}
```

Output:
```
Coordinate originali: (10, 20)
Coordinate all'interno della funzione: (15, 25)
Coordinate dopo la chiamata: (10, 20)
```

### Passaggio di strutture per riferimento

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Punto;

// Passaggio per riferimento
void sposta_punto_ptr(Punto *p, int dx, int dy) {
    p->x += dx;  // Modifica la struttura originale
    p->y += dy;
    printf("Coordinate all'interno della funzione: (%d, %d)\n", p->x, p->y);
}

int main() {
    Punto punto = {10, 20};
    
    printf("Coordinate originali: (%d, %d)\n", punto.x, punto.y);
    sposta_punto_ptr(&punto, 5, 5);
    printf("Coordinate dopo la chiamata: (%d, %d)\n", punto.x, punto.y);  // Cambiano
    
    return 0;
}
```

Output:
```
Coordinate originali: (10, 20)
Coordinate all'interno della funzione: (15, 25)
Coordinate dopo la chiamata: (15, 25)
```

### Considerazioni sul passaggio di strutture

1. **Dimensione**: Le strutture possono essere grandi, quindi il passaggio per valore può essere inefficiente
2. **Convenzione**: È comune passare strutture per riferimento per evitare copie inutili
3. **Immutabilità**: Se si desidera garantire che la struttura non venga modificata, è possibile passarla per valore o utilizzare `const` con un puntatore

## Parametri di tipo array bidimensionale

Il passaggio di array bidimensionali richiede una sintassi speciale, poiché è necessario specificare almeno la dimensione della seconda dimensione.

```c
#include <stdio.h>

// Passaggio di un array bidimensionale
void stampa_matrice(int matrice[][3], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrice[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    stampa_matrice(matrice, 2);
    
    return 0;
}
```

Output:
```
1 2 3 
4 5 6 
```

## Passaggio di parametri alla funzione main

La funzione `main` può ricevere parametri dalla linea di comando attraverso i parametri `argc` e `argv`.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Numero di argomenti: %d\n", argc);
    
    printf("Argomenti:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    
    return 0;
}
```

Se il programma viene compilato come `programma.exe` e eseguito con `programma.exe arg1 arg2`, l'output sarà:

```
Numero di argomenti: 3
Argomenti:
argv[0]: programma.exe
argv[1]: arg1
argv[2]: arg2
```

## Parametri di tipo funzione (puntatori a funzione)

In C, è possibile passare funzioni come parametri ad altre funzioni utilizzando i puntatori a funzione.

```c
#include <stdio.h>

// Definizione di due funzioni di esempio
int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

// Funzione che accetta un puntatore a funzione come parametro
int applica_operazione(int x, int y, int (*operazione)(int, int)) {
    return operazione(x, y);  // Chiamata alla funzione tramite puntatore
}

int main() {
    int a = 10, b = 5;
    
    // Passaggio di funzioni come parametri
    int risultato_somma = applica_operazione(a, b, somma);
    int risultato_sottrazione = applica_operazione(a, b, sottrazione);
    
    printf("%d + %d = %d\n", a, b, risultato_somma);
    printf("%d - %d = %d\n", a, b, risultato_sottrazione);
    
    return 0;
}
```

Output:
```
10 + 5 = 15
10 - 5 = 5
```

## Best practice per il passaggio di parametri

1. **Scegliere il metodo appropriato**: Utilizzare il passaggio per valore per parametri semplici e il passaggio per riferimento per dati complessi o quando è necessario modificare i valori originali.

2. **Utilizzare const per i puntatori**: Quando si passa un puntatore ma non si intende modificare i dati, utilizzare `const` per indicare questa intenzione.
   ```c
   void stampa_array(const int *arr, int dimensione) {
       // Il compilatore impedirà modifiche all'array
   }
   ```

3. **Documentare il comportamento**: Indicare chiaramente nei commenti se una funzione modifica i parametri passati.

4. **Evitare effetti collaterali nascosti**: Le funzioni dovrebbero essere trasparenti riguardo alle modifiche che apportano ai dati.

5. **Considerare l'efficienza**: Per strutture dati di grandi dimensioni, preferire il passaggio per riferimento per evitare copie inutili.

## Domande di autovalutazione

1. Qual è la differenza principale tra il passaggio per valore e il passaggio per riferimento in C?

2. Perché è necessario passare la dimensione di un array quando lo si passa a una funzione?

3. Come si può impedire a una funzione di modificare un parametro passato per riferimento?

4. Quali sono i vantaggi del passaggio di strutture per riferimento rispetto al passaggio per valore?

5. Come si può passare un array bidimensionale a una funzione in C?

## Esercizi proposti

1. Scrivi una funzione `scambia` che scambi il valore di due variabili intere utilizzando il passaggio per riferimento.

2. Implementa una funzione `ordina_array` che ordini un array di interi in ordine crescente.

3. Crea una funzione `modifica_struttura` che accetti una struttura `Persona` (con campi nome, età e altezza) e ne modifichi i valori.

4. Scrivi un programma che utilizzi i puntatori a funzione per applicare diverse operazioni matematiche (somma, sottrazione, moltiplicazione, divisione) a due numeri inseriti dall'utente.

5. Implementa una funzione che accetti una matrice (array bidimensionale) e ne calcoli la trasposta.