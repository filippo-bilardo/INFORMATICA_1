# La funzione scanf

## Sintassi e utilizzo

La funzione `scanf()` è la controparte di `printf()` per l'input formattato in C. Permette di leggere dati dallo stream di input standard (stdin), generalmente la tastiera, e di convertirli nei tipi di dati appropriati.

La sintassi base della funzione è:

```c
int scanf(const char *format, ...);
```

Dove:
- `format` è una stringa di formato che specifica come interpretare i dati in input
- `...` rappresenta un numero variabile di argomenti che sono puntatori alle variabili dove verranno memorizzati i dati letti

La funzione restituisce il numero di elementi letti con successo, o EOF in caso di errore o fine del file.

Esempio di utilizzo base:

```c
#include <stdio.h>

int main() {
    int numero;
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    printf("Hai inserito: %d\n", numero);
    return 0;
}
```

È importante notare che `scanf()` richiede gli indirizzi delle variabili (usando l'operatore `&`), a differenza di `printf()` che utilizza i valori delle variabili.

## Specificatori di formato

Gli specificatori di formato per `scanf()` sono simili a quelli di `printf()`, ma con alcune differenze importanti nel comportamento:

| Specificatore | Tipo di dato | Esempio |
|--------------|--------------|----------|
| `%d` o `%i` | Intero con segno (int) | `scanf("%d", &intero);` |
| `%u` | Intero senza segno (unsigned int) | `scanf("%u", &u_intero);` |
| `%o` | Intero in base ottale | `scanf("%o", &ottale);` |
| `%x` o `%X` | Intero in base esadecimale | `scanf("%x", &esadecimale);` |
| `%f`, `%e`, `%g` | Numero in virgola mobile (float) | `scanf("%f", &float_num);` |
| `%lf`, `%le`, `%lg` | Numero in virgola mobile (double) | `scanf("%lf", &double_num);` |
| `%c` | Carattere | `scanf("%c", &carattere);` |
| `%s` | Stringa di caratteri | `scanf("%s", stringa);` |
| `%[...]` | Set di caratteri | `scanf("%[0-9]", numeri);` |
| `%n` | Numero di caratteri letti finora | `scanf("%d%n", &num, &count);` |

Nota: Per le stringhe, non è necessario l'operatore `&` perché il nome dell'array è già un puntatore al primo elemento.

## Gestione dell'input

### Lettura di diversi tipi di dati

```c
#include <stdio.h>

int main() {
    int intero;
    float decimale;
    char carattere;
    char stringa[50];
    
    printf("Inserisci un intero, un decimale, un carattere e una parola: ");
    scanf("%d %f %c %s", &intero, &decimale, &carattere, stringa);
    
    printf("Hai inserito: %d, %.2f, %c, %s\n", intero, decimale, carattere, stringa);
    return 0;
}
```

In questo esempio, l'utente deve inserire i valori separati da spazi o invio.

### Lettura di stringhe con spazi

Un problema comune con `scanf("%s", stringa)` è che legge solo fino al primo spazio. Per leggere una riga intera, inclusi gli spazi, si possono usare queste alternative:

```c
// Usando scanf con set di caratteri
scanf(" %[^\n]", stringa);  // Legge tutti i caratteri fino a newline

// Usando fgets (più sicuro)
fgets(stringa, sizeof(stringa), stdin);
// Nota: fgets include il carattere newline nella stringa
```

## Problemi comuni e soluzioni

### 1. Buffer di input non svuotato

Uno dei problemi più comuni con `scanf()` è che può lasciare caratteri nel buffer di input, in particolare il carattere newline (`\n`). Questo può causare problemi quando si alternano letture di numeri e caratteri.

Esempio problematico:

```c
#include <stdio.h>

int main() {
    int numero;
    char carattere;
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    printf("Inserisci un carattere: ");
    scanf("%c", &carattere);  // Leggerà il '\n' rimasto nel buffer!
    
    printf("Numero: %d, Carattere: '%c'\n", numero, carattere);
    return 0;
}
```

Soluzioni:

```c
// Soluzione 1: Aggiungere uno spazio prima di %c
scanf(" %c", &carattere);  // Lo spazio consuma whitespace, incluso '\n'

// Soluzione 2: Svuotare il buffer manualmente
scanf("%d", &numero);
while(getchar() != '\n');  // Consuma tutti i caratteri fino a newline
scanf("%c", &carattere);
```

### 2. Overflow del buffer con stringhe

`scanf("%s", stringa)` non controlla la dimensione del buffer, quindi può causare overflow se l'input è più lungo del buffer allocato.

Soluzione:

```c
// Limitare il numero di caratteri letti
scanf("%49s", stringa);  // Per un buffer di 50 caratteri

// Alternativa più sicura con fgets
fgets(stringa, sizeof(stringa), stdin);
```

### 3. Gestione degli errori

È importante controllare il valore restituito da `scanf()` per verificare se la lettura è avvenuta con successo:

```c
#include <stdio.h>

int main() {
    int numero;
    int risultato;
    
    printf("Inserisci un numero: ");
    risultato = scanf("%d", &numero);
    
    if(risultato == 1) {
        printf("Hai inserito: %d\n", numero);
    } else {
        printf("Input non valido!\n");
    }
    
    return 0;
}
```

## Tecniche avanzate

### Lettura con set di caratteri

Lo specificatore `%[...]` permette di leggere solo caratteri specifici:

```c
#include <stdio.h>

int main() {
    char numeri[50];
    char lettere[50];
    
    printf("Inserisci una stringa mista: ");
    
    // Legge solo cifre
    scanf("%[0-9]", numeri);
    
    // Legge solo lettere (maiuscole e minuscole)
    scanf("%[a-zA-Z]", lettere);
    
    printf("Numeri: %s\nLettere: %s\n", numeri, lettere);
    return 0;
}
```

Si può anche usare `%[^...]` per leggere tutti i caratteri TRANNE quelli specificati:

```c
// Legge fino al primo spazio o newline
scanf("%[^ \n]", stringa);
```

### Lettura formattata con larghezza massima

Si può limitare il numero di caratteri letti per evitare overflow:

```c
// Legge al massimo 10 caratteri in una stringa
scanf("%10s", stringa);

// Legge al massimo 5 cifre in un intero
scanf("%5d", &numero);
```

## Considerazioni sulla sicurezza

`scanf()` è notoriamente soggetto a problemi di sicurezza, in particolare per quanto riguarda l'overflow del buffer con le stringhe. Per applicazioni critiche per la sicurezza, è consigliabile utilizzare alternative più sicure come:

- `fgets()` per leggere stringhe
- `strtol()`, `strtod()` per convertire stringhe in numeri
- Funzioni specifiche delle librerie di sicurezza come `scanf_s()` (disponibile in alcuni compilatori)

Nelle prossime sezioni, esploreremo tecniche avanzate di formattazione dell'output per creare interfacce utente più sofisticate nei programmi C.