# Formattazione avanzata dell'output

## Controllo della larghezza e precisione

In C, è possibile controllare con precisione come i dati vengono visualizzati nell'output, specificando la larghezza del campo e la precisione dei numeri decimali.

### Larghezza del campo

La larghezza del campo determina il numero minimo di caratteri che verranno utilizzati per visualizzare un valore. Se il valore richiede meno caratteri della larghezza specificata, verrà aggiunto del padding (generalmente spazi).

Sintassi: `%Nd` dove N è la larghezza desiderata.

```c
#include <stdio.h>

int main() {
    int a = 42;
    int b = 5;
    int c = 1234;
    
    printf("|%d|\n", a);      // Output: |42|
    printf("|%5d|\n", a);     // Output: |   42|  (allineato a destra)
    printf("|%-5d|\n", a);    // Output: |42   |  (allineato a sinistra)
    printf("|%5d|\n", b);     // Output: |    5|
    printf("|%5d|\n", c);     // Output: | 1234|
    
    return 0;
}
```

### Precisione dei numeri decimali

La precisione specifica il numero di cifre dopo la virgola per i numeri in virgola mobile.

Sintassi: `%.Nf` dove N è il numero di cifre decimali desiderato.

```c
#include <stdio.h>

int main() {
    float pi = 3.14159265359;
    
    printf("%f\n", pi);       // Output: 3.141593 (precisione predefinita)
    printf("%.2f\n", pi);     // Output: 3.14 (2 decimali)
    printf("%.4f\n", pi);     // Output: 3.1416 (4 decimali, con arrotondamento)
    printf("%.0f\n", pi);     // Output: 3 (nessun decimale)
    
    return 0;
}
```

### Combinazione di larghezza e precisione

È possibile combinare larghezza e precisione per un controllo ancora più preciso:

Sintassi: `%N.Mf` dove N è la larghezza totale e M è il numero di cifre decimali.

```c
#include <stdio.h>

int main() {
    float num = 3.14159;
    
    printf("|%f|\n", num);       // Output: |3.141590|
    printf("|%10f|\n", num);     // Output: |  3.141590|
    printf("|%10.2f|\n", num);   // Output: |      3.14|
    printf("|%-10.2f|\n", num);  // Output: |3.14      |
    
    return 0;
}
```

## Allineamento del testo

Come visto negli esempi precedenti, è possibile controllare l'allineamento del testo all'interno di un campo di larghezza specificata:

- **Allineamento a destra** (predefinito): `%Nd`
- **Allineamento a sinistra**: `%-Nd`

Questo è particolarmente utile quando si creano tabelle o si desidera un output ben formattato:

```c
#include <stdio.h>

int main() {
    printf("|%-15s|%10s|%8s|\n", "Prodotto", "Prezzo", "Quantità");
    printf("|%-15s|%10.2f|%8d|\n", "Mela", 0.99, 10);
    printf("|%-15s|%10.2f|%8d|\n", "Banana", 1.29, 5);
    printf("|%-15s|%10.2f|%8d|\n", "Arancia", 0.89, 8);
    
    return 0;
}
```

Output:
```
|Prodotto        |    Prezzo|Quantità|
|Mela            |      0.99|      10|
|Banana          |      1.29|       5|
|Arancia         |      0.89|       8|
```

## Formattazione di numeri e valute

### Visualizzazione di numeri con separatori di migliaia

C non fornisce direttamente un modo per visualizzare numeri con separatori di migliaia, ma è possibile utilizzare la libreria `locale.h` per ottenere questo risultato:

```c
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");  // Imposta il locale del sistema
    
    int numero = 1234567;
    printf("Numero: %'d\n", numero);  // Output: Numero: 1.234.567 (dipende dal locale)
    
    return 0;
}
```

### Formattazione di valute

Per formattare valute, è comune utilizzare la precisione a due decimali e aggiungere manualmente il simbolo della valuta:

```c
#include <stdio.h>

int main() {
    float prezzo = 1234.56;
    
    printf("Prezzo: €%.2f\n", prezzo);  // Output: Prezzo: €1234.56
    printf("Prezzo: $%'.2f\n", prezzo); // Con separatore di migliaia (richiede locale)
    
    return 0;
}
```

## Caratteri di escape

I caratteri di escape sono sequenze speciali che iniziano con il carattere backslash (`\`) e rappresentano caratteri che altrimenti sarebbero difficili o impossibili da includere direttamente in una stringa.

I principali caratteri di escape in C sono:

| Sequenza | Significato |
|----------|-------------|
| `\n` | Nuova riga |
| `\t` | Tabulazione orizzontale |
| `\r` | Ritorno a capo (carriage return) |
| `\\` | Backslash |
| `\'` | Apostrofo |
| `\"` | Virgolette doppie |
| `\b` | Backspace |
| `\f` | Avanzamento pagina (form feed) |
| `\v` | Tabulazione verticale |
| `\a` | Allarme (beep) |
| `\0` | Carattere nullo (terminatore di stringa) |
| `\xhh` | Carattere con codice esadecimale hh |
| `\ooo` | Carattere con codice ottale ooo |

Esempio di utilizzo:

```c
#include <stdio.h>

int main() {
    printf("Prima riga\nSeconda riga\n");  // Output su due righe
    printf("Colonna1\tColonna2\tColonna3\n");  // Output con tabulazioni
    printf("Questo è un \"esempio\" di testo con virgolette\n");  // Virgolette in una stringa
    printf("Percorso file: C:\\Documenti\\file.txt\n");  // Backslash in una stringa
    printf("Suono di allarme: \a\n");  // Produce un beep
    
    return 0;
}
```

## Esempi pratici di formattazione avanzata

### Creazione di una tabella ben formattata

```c
#include <stdio.h>

int main() {
    // Intestazione della tabella
    printf("+---------------+----------+----------+\n");
    printf("| %-13s | %-8s | %-8s |\n", "Prodotto", "Prezzo", "Quantità");
    printf("+---------------+----------+----------+\n");
    
    // Dati della tabella
    printf("| %-13s | %8.2f | %8d |\n", "Mela", 0.99, 10);
    printf("| %-13s | %8.2f | %8d |\n", "Banana", 1.29, 5);
    printf("| %-13s | %8.2f | %8d |\n", "Arancia", 0.89, 8);
    printf("| %-13s | %8.2f | %8d |\n", "Kiwi", 2.49, 3);
    
    // Piè di pagina della tabella
    printf("+---------------+----------+----------+\n");
    
    return 0;
}
```

### Visualizzazione di dati scientifici

```c
#include <stdio.h>
#include <math.h>

int main() {
    // Costanti fisiche
    double c = 299792458;       // Velocità della luce (m/s)
    double h = 6.62607015e-34;  // Costante di Planck (J·s)
    double G = 6.67430e-11;     // Costante gravitazionale (m³/kg/s²)
    
    printf("Costanti fisiche fondamentali:\n");
    printf("%-25s = %15.8e m/s\n", "Velocità della luce", c);
    printf("%-25s = %15.8e J·s\n", "Costante di Planck", h);
    printf("%-25s = %15.8e m³/kg/s²\n", "Costante gravitazionale", G);
    
    return 0;
}
```

## Esercizi proposti

1. Scrivi un programma che visualizzi una tabella di conversione da gradi Celsius a Fahrenheit, con temperature da 0°C a 100°C con incrementi di 10°C. Formatta la tabella in modo che i numeri siano allineati correttamente.

2. Crea un programma che generi una fattura con elenco di prodotti, quantità, prezzo unitario e totale. Assicurati che i numeri decimali siano formattati con due cifre dopo la virgola e che le colonne siano allineate correttamente.

3. Implementa un programma che visualizzi un calendario mensile, formattando correttamente i giorni della settimana e i numeri dei giorni.

4. Scrivi un programma che legga un importo in euro e lo visualizzi in diversi formati (con e senza simbolo della valuta, con e senza separatori delle migliaia, ecc.).

5. Crea un programma che visualizzi un grafico a barre orizzontale utilizzando caratteri ASCII, dove la lunghezza di ciascuna barra è proporzionale al valore numerico associato.

## Domande di autovalutazione

1. Qual è la differenza tra `%f`, `%e` e `%g` nella funzione printf?

2. Come si può formattare un numero in modo che abbia sempre due cifre decimali?

3. Quale carattere di escape si utilizza per inserire un tab in una stringa?

4. Come si può allineare a sinistra un testo all'interno di un campo di larghezza fissa?

5. Qual è il modo corretto per visualizzare il carattere '%' nell'output?

6. Come si può formattare un numero con separatori delle migliaia?

7. Quale modificatore si usa per specificare sia la larghezza totale che la precisione decimale di un numero?

8. Come si può formattare un numero in notazione scientifica?