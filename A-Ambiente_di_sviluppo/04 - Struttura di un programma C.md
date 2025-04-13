### **2.2 Struttura di un programma C**

Un programma in linguaggio **C** segue una struttura ben definita che lo rende leggibile, modulare e facile da comprendere. Questa struttura è composta da diverse sezioni, alcune obbligatorie e altre opzionali, che consentono di scrivere codice organizzato e facilmente manutenibile.

---

### **Struttura Generale di un Programma C**

Un programma tipico in C è organizzato come segue:

```c
#include <header_files> // (1) Sezione degli header (opzionale)
#define CONSTANTS       // (2) Definizione delle costanti simboliche (opzionale)

// Dichiarazioni globali di variabili e funzioni
// (3) Variabili globali e prototipi di funzione (opzionale)

int main() {            // (4) Funzione principale obbligatoria
    // Corpo del programma
    return 0;           // Fine del programma
}

// Altre funzioni definite dall'utente
// (5) Funzioni definite dall'utente (opzionale)
```

---

### **Dettagli delle Sezioni**

#### **1. Sezione degli Header (opzionale)**
Questa sezione contiene le direttive `#include`, utilizzate per includere librerie standard o personalizzate che offrono funzionalità predefinite.

- **Librerie Standard:** Utilizzate per funzioni comuni come input/output, operazioni matematiche, manipolazione di stringhe, ecc.
  - Esempio:
    ```c
    #include <stdio.h>  // Per printf e scanf
    #include <math.h>   // Per funzioni matematiche come sqrt
    ```

- **Librerie Personalizzate:** Create dall'utente per modularizzare il programma.
  - Esempio:
    ```c
    #include "mialibreria.h"
    ```

---

#### **2. Definizione delle Costanti Simboliche (opzionale)**
Permette di definire valori costanti che rimangono invariati durante l'esecuzione del programma. Queste costanti migliorano la leggibilità e la manutenibilità del codice.

- Esempio:
  ```c
  #define PI 3.14159   // Costante per il valore di pi greco
  #define MAX 100      // Dimensione massima di un array
  ```

---

#### **3. Variabili Globali e Prototipi di Funzione (opzionale)**
Questa sezione viene utilizzata per:
- **Dichiarare variabili globali**: Variabili accessibili da tutte le funzioni del programma.
  - Esempio:
    ```c
    int contatore = 0; // Variabile globale
    ```

- **Dichiarare prototipi di funzione**: Dichiarazioni che specificano il nome, il tipo di ritorno e i parametri delle funzioni definite successivamente.
  - Esempio:
    ```c
    int somma(int a, int b); // Prototipo di funzione
    ```

---

#### **4. Funzione Principale `main()` (obbligatoria)**
La funzione `main` è il punto di ingresso del programma. È qui che inizia e termina l'esecuzione.

- **Struttura base della funzione `main`:**
  ```c
  int main() {
      // Dichiarazioni di variabili locali
      // Istruzioni
      return 0; // Segnala al sistema operativo che il programma è terminato correttamente
  }
  ```

- Esempio:
  ```c
  int main() {
      printf("Ciao, Mondo!\n"); // Stampa un messaggio
      return 0;                 // Fine del programma
  }
  ```

---

#### **5. Funzioni Definite dall'Utente (opzionale)**
Le funzioni definite dall'utente sono utilizzate per suddividere il programma in moduli più piccoli e riutilizzabili.

- **Definizione di una funzione:**
  ```c
  int somma(int a, int b) { // Funzione che calcola la somma di due numeri
      return a + b;
  }
  ```

- **Chiamata della funzione:**
  ```c
  int main() {
      int risultato = somma(3, 4);
      printf("Risultato: %d\n", risultato);
      return 0;
  }
  ```

---

### **Esempio Completo: Un Programma C Ben Strutturato**
Di seguito un esempio che combina tutte le sezioni principali:

```c
#include <stdio.h>  // Sezione degli header
#define MAX 100     // Definizione di costanti simboliche

int somma(int a, int b); // Prototipo di funzione

// Variabile globale
int contatore = 0;

int main() {
    int num1 = 10, num2 = 20;  // Variabili locali
    int risultato = somma(num1, num2); // Chiamata alla funzione

    printf("Somma: %d\n", risultato);
    return 0;
}

// Definizione della funzione
int somma(int a, int b) {
    contatore++;
    return a + b;
}
```

---

### **Analisi Dettagliata di un Programma "Hello World"**

Per comprendere meglio la struttura di un programma C, analizziamo in dettaglio un classico esempio "Hello World":

```c
#include <stdio.h> //printf

int main(void) 
{
  //stampiamo a schermo un messaggio di benvenuto
  printf("Ciao Mondo!");
 
  //terminiamo il programma
  return 0;
}
```

#### **Analisi Riga per Riga**

1. **`#include <stdio.h> //printf`**
   - **Direttiva al preprocessore**: Questa riga dice al preprocessore di includere il file di intestazione `stdio.h`, che contiene le dichiarazioni per le funzioni di input/output standard, come `printf`.
   - **Commento**: Il commento `//printf` spiega brevemente che `stdio.h` contiene la definizione della funzione `printf`.

2. **`int main(void)`**
   - **Definizione della funzione principale**: `main` è la funzione principale che il sistema operativo esegue all'avvio del programma. Restituisce un valore intero (`int`).
   - **Parametro `void`**: Indica che la funzione `main` non accetta argomenti.

3. **`{`**
   - **Inizio del blocco di codice**: Segna l'inizio del corpo della funzione `main`.

4. **`//stampiamo a schermo un messaggio di benvenuto`**
   - **Commento**: Spiega cosa fa l'istruzione successiva, migliorando la leggibilità del codice.

5. **`printf("Ciao Mondo!");`**
   - **Funzione `printf`**: Utilizzata per stampare testo sullo schermo. In questo caso, stampa "Ciao Mondo!".
   - **Punto e virgola `;`**: Ogni istruzione in C deve terminare con un punto e virgola.

6. **`//terminiamo il programma`**
   - **Commento**: Indica la funzione dell'istruzione successiva.

7. **`return 0;`**
   - **Restituzione del valore di uscita**: Restituire `0` indica che il programma è terminato con successo. Altri valori possono indicare errori.

8. **`}`**
   - **Fine del blocco di codice**: Indica la fine del corpo della funzione `main`.

#### **Riassunto del Funzionamento**

- Il programma include la libreria `stdio.h` per usare la funzione `printf`.
- Definisce una funzione principale `main`, che è il punto di partenza dell'esecuzione.
- Usa `printf` per stampare "Ciao Mondo!" sullo schermo.
- Restituisce `0` per indicare che il programma è terminato con successo.
- I commenti migliorano la leggibilità spiegando cosa fanno le singole istruzioni.

---

### **Punti Chiave**
- La funzione `main` è obbligatoria: senza di essa, il programma non può essere eseguito.
- Le sezioni opzionali, come le variabili globali e i prototipi di funzione, sono utili per migliorare la modularità e la leggibilità.
- Un programma ben strutturato facilita il debugging, il testing e la manutenzione.
- L'uso appropriato di commenti migliora la comprensione del codice.
- Ogni istruzione in C deve terminare con un punto e virgola (`;`).

La comprensione di questa struttura è il primo passo per scrivere programmi efficienti e leggibili in linguaggio C.