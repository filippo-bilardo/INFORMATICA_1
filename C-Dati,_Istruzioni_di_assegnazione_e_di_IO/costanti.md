## Le costanti in C

Le **costanti** in C sono valori che non possono essere modificati durante l'esecuzione del programma. Esse sono utilizzate per rappresentare dati che rimangono invariati, migliorando la leggibilità del codice e prevenendo errori derivanti dalla modifica accidentale di valori critici. In C, esistono vari modi per dichiarare le costanti.

### Tipi di costanti in C

1. **Costanti letterali**:
   Le costanti letterali sono valori costanti che vengono scritti direttamente nel codice. Ad esempio:
   
   - Costante intera: `42`
   - Costante float: `3.14`
   - Costante carattere: `'A'`
   - Costante stringa: `"Ciao"`

   Esempio:
   ```c
   printf("%d", 42);       // Stampa il valore 42
   printf("%f", 3.14);     // Stampa il valore 3.14
   ```

2. **Costanti simboliche con `#define`**:
   Il preprocessore C consente di definire costanti tramite la direttiva `#define`. Questa direttiva sostituisce tutte le occorrenze della costante simbolica nel codice con il valore specificato durante la compilazione.

   Esempio:
   ```c
   #define PI 3.14159
   #define MAX_LUNGHEZZA 100

   int main() {
       printf("Il valore di PI è: %f\n", PI);
       printf("La lunghezza massima è: %d\n", MAX_LUNGHEZZA);
       return 0;
   }
   ```

   In questo esempio, ogni volta che viene utilizzato `PI` o `MAX_LUNGHEZZA`, il preprocessore sostituisce tali nomi con i rispettivi valori. Le costanti `#define` non hanno un tipo specifico.

3. **Costanti con `const`**:
   La parola chiave `const` permette di dichiarare variabili costanti, che non possono essere modificate dopo l'inizializzazione. A differenza delle costanti definite con `#define`, le costanti `const` sono veri e propri valori con un tipo di dato associato, come `int`, `float`, o `char`.

   Esempio:
   ```c
   int main() {
       const int MAX_ETA = 100;
       const float GRAVITA = 9.81;

       printf("L'età massima è: %d\n", MAX_ETA);
       printf("L'accelerazione di gravità è: %f\n", GRAVITA);

       // MAX_ETA = 200;  // Errore: non si può modificare una variabile const
       return 0;
   }
   ```

   In questo caso, `MAX_ETA` e `GRAVITA` sono costanti che non possono essere modificate successivamente. Se si tenta di cambiare il loro valore, il compilatore genererà un errore.

4. **Costanti di enumerazione**:
   Le costanti possono essere definite anche tramite **enumerazioni** (`enum`), che assegnano nomi simbolici a una sequenza di valori interi. Le enumerazioni vengono utilizzate per rappresentare insiemi di valori fissi, come i giorni della settimana o i mesi dell'anno.

   Esempio:
   ```c
   enum Giorno { LUNEDI = 1, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI };

   int main() {
       enum Giorno oggi = MARTEDI;
       printf("Il giorno di oggi è il numero: %d\n", oggi); // Stampa 2
       return 0;
   }
   ```

   In questo esempio, i giorni della settimana sono associati a valori interi costanti, con `LUNEDI` che vale 1, `MARTEDI` 2, e così via.

### Vantaggi dell'uso delle costanti

- **Maggiore leggibilità**: L'uso di nomi simbolici al posto di numeri o valori letterali aiuta a rendere il codice più comprensibile. Ad esempio, scrivere `#define PI 3.14159` è molto più leggibile di scrivere `3.14159` ovunque sia richiesto il valore del pi greco.
- **Manutenibilità del codice**: Se un valore cambia, ad esempio la lunghezza massima di un array, basta modificare la costante in un solo punto del codice (nella definizione), senza dover cercare e sostituire manualmente ogni occorrenza.
- **Prevenzione degli errori**: Le costanti evitano la modifica accidentale di valori critici. Se una variabile è definita come `const`, il compilatore impedirà eventuali tentativi di alterarne il valore, migliorando la robustezza del programma.

In sintesi, le costanti in C sono fondamentali per scrivere codice più chiaro, sicuro e facile da mantenere.