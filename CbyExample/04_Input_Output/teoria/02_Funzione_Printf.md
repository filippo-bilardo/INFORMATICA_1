# La funzione printf

## Sintassi e utilizzo

La funzione `printf()` è una delle funzioni più utilizzate in C per l'output formattato. Il suo nome deriva da "print formatted" e permette di visualizzare dati sullo stream di output standard (stdout), generalmente il monitor.

La sintassi base della funzione è:

```c
int printf(const char *format, ...);
```

Dove:
- `format` è una stringa di formato che specifica come i dati successivi devono essere visualizzati
- `...` rappresenta un numero variabile di argomenti che corrispondono ai specificatori di formato nella stringa

La funzione restituisce il numero di caratteri scritti con successo, o un valore negativo in caso di errore.

Esempio di utilizzo base:

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

## Specificatori di formato

Gli specificatori di formato sono segnaposto all'interno della stringa di formato che indicano dove e come inserire i valori delle variabili. Ogni specificatore inizia con il carattere `%` seguito da un carattere che indica il tipo di dato.

I principali specificatori di formato sono:

| Specificatore | Tipo di dato | Esempio |
|--------------|--------------|----------|
| `%d` o `%i` | Intero con segno (int) | `printf("%d", 42);` |
| `%u` | Intero senza segno (unsigned int) | `printf("%u", 42u);` |
| `%o` | Intero in base ottale | `printf("%o", 42);` |
| `%x` o `%X` | Intero in base esadecimale (minuscolo o maiuscolo) | `printf("%x", 42);` |
| `%f` | Numero in virgola mobile (float o double) | `printf("%f", 3.14);` |
| `%e` o `%E` | Notazione scientifica (minuscolo o maiuscolo) | `printf("%e", 3.14);` |
| `%g` o `%G` | Usa %f o %e a seconda di quale sia più compatto | `printf("%g", 3.14);` |
| `%c` | Carattere | `printf("%c", 'A');` |
| `%s` | Stringa di caratteri | `printf("%s", "Hello");` |
| `%p` | Puntatore (indirizzo di memoria) | `printf("%p", &variabile);` |
| `%%` | Stampa il carattere % | `printf("50%%");` |

Esempio di utilizzo di vari specificatori:

```c
#include <stdio.h>

int main() {
    int intero = 42;
    float decimale = 3.14159;
    char carattere = 'A';
    char stringa[] = "Hello, C!";
    
    printf("Intero: %d\n", intero);
    printf("Decimale: %f\n", decimale);
    printf("Carattere: %c\n", carattere);
    printf("Stringa: %s\n", stringa);
    printf("Esadecimale: %x\n", intero);
    printf("Indirizzo di intero: %p\n", &intero);
    
    return 0;
}
```

## Modificatori di formato

I modificatori di formato permettono di controllare ulteriormente come i dati vengono visualizzati. Si inseriscono tra il carattere `%` e il carattere del tipo di dato.

### Modificatori di larghezza e precisione

- `%Nd`: specifica una larghezza minima di N caratteri (es. `%5d`)
- `%.Nf`: specifica N cifre dopo la virgola per i numeri decimali (es. `%.2f`)
- `%N.Mf`: combina larghezza minima e precisione (es. `%8.2f`)

### Flag di formattazione

- `-`: allinea a sinistra (es. `%-10s`)
- `+`: mostra sempre il segno (es. `%+d`)
- `0`: riempie con zeri invece che spazi (es. `%05d`)
- ` ` (spazio): lascia uno spazio per il segno nei numeri positivi (es. `% d`)
- `#`: forma alternativa per alcuni formati (es. `%#x` aggiunge 0x)

### Modificatori di lunghezza

- `h`: short int (es. `%hd`)
- `l`: long int (es. `%ld`)
- `ll`: long long int (es. `%lld`)
- `L`: long double (es. `%Lf`)

## Esempi pratici

### Formattazione di numeri interi

```c
#include <stdio.h>

int main() {
    int num = 42;
    
    printf("Normale: %d\n", num);
    printf("Larghezza 5: '%5d'\n", num);  // Allineato a destra
    printf("Allineato a sinistra: '%-5d'\n", num);
    printf("Riempito con zeri: '%05d'\n", num);
    printf("Con segno: '%+d'\n", num);
    
    return 0;
}
```

Output:
```
Normale: 42
Larghezza 5: '   42'
Allineato a sinistra: '42   '
Riempito con zeri: '00042'
Con segno: '+42'
```

### Formattazione di numeri decimali

```c
#include <stdio.h>

int main() {
    double num = 3.14159265359;
    
    printf("Normale: %f\n", num);
    printf("Due decimali: %.2f\n", num);
    printf("Larghezza 10, 2 decimali: '%10.2f'\n", num);
    printf("Notazione scientifica: %e\n", num);
    printf("Formato compatto: %g\n", num);
    
    return 0;
}
```

Output:
```
Normale: 3.141593
Due decimali: 3.14
Larghezza 10, 2 decimali: '      3.14'
Notazione scientifica: 3.141593e+00
Formato compatto: 3.14159
```

### Formattazione di stringhe

```c
#include <stdio.h>

int main() {
    char nome[] = "Mario";
    
    printf("Normale: %s\n", nome);
    printf("Larghezza 10: '%10s'\n", nome);  // Allineato a destra
    printf("Allineato a sinistra: '%-10s'\n", nome);
    printf("Solo primi 3 caratteri: '%.3s'\n", nome);
    
    return 0;
}
```

Output:
```
Normale: Mario
Larghezza 10: '     Mario'
Allineato a sinistra: 'Mario     '
Solo primi 3 caratteri: 'Mar'
```

## Considerazioni sulla sicurezza

È importante assicurarsi che il numero e il tipo degli argomenti corrispondano esattamente agli specificatori di formato nella stringa. Un mancato allineamento può causare comportamenti imprevedibili o vulnerabilità di sicurezza.

Ad esempio, il seguente codice è pericoloso:

```c
char input[100];
scanf("%s", input);
printf(input);  // Pericoloso! Se input contiene specificatori di formato
```

Se l'utente inserisce una stringa contenente specificatori di formato come `%s` o `%n`, potrebbero verificarsi crash o vulnerabilità di sicurezza. La forma corretta è:

```c
printf("%s", input);  // Sicuro
```

Nelle prossime sezioni, esploreremo la funzione `scanf()` per l'input formattato e tecniche avanzate di formattazione dell'output.