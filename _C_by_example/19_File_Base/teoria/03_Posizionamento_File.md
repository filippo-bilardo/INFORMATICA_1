# Posizionamento all'Interno dei File in C

## Introduzione

Oltre alle operazioni di lettura e scrittura, è spesso necessario posizionarsi in punti specifici all'interno di un file. Il linguaggio C offre diverse funzioni per controllare la posizione corrente all'interno di un file, permettendo operazioni di lettura e scrittura non sequenziali.

## Il Concetto di File Pointer

In C, ogni file aperto ha un indicatore di posizione (file pointer) che indica dove avverrà la prossima operazione di lettura o scrittura. Quando si apre un file, questo indicatore è posizionato:
- All'inizio del file per le modalità `"r"` e `"w"`
- Alla fine del file per la modalità `"a"`

## Funzioni di Posizionamento

### fseek()

La funzione `fseek()` permette di spostare l'indicatore di posizione a un punto specifico del file:

```c
int fseek(FILE *stream, long offset, int whence);
```

Parametri:
- `stream`: puntatore al file
- `offset`: spostamento in byte (può essere positivo o negativo)
- `whence`: punto di riferimento per lo spostamento

Il parametro `whence` può assumere uno dei seguenti valori:
- `SEEK_SET`: inizio del file
- `SEEK_CUR`: posizione corrente
- `SEEK_END`: fine del file

La funzione restituisce 0 in caso di successo, o un valore diverso da zero in caso di errore.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("dati.txt", "r");
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    // Posiziona l'indicatore 10 byte dopo l'inizio del file
    fseek(fp, 10, SEEK_SET);
    
    // Posiziona l'indicatore 5 byte dopo la posizione corrente
    fseek(fp, 5, SEEK_CUR);
    
    // Posiziona l'indicatore 15 byte prima della fine del file
    fseek(fp, -15, SEEK_END);
    
    fclose(fp);
    return 0;
}
```

### ftell()

La funzione `ftell()` restituisce la posizione corrente dell'indicatore nel file:

```c
long ftell(FILE *stream);
```

Questa funzione è utile per salvare la posizione corrente e potervi tornare in seguito.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("dati.txt", "r");
    long pos;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    // Legge alcuni dati...
    
    // Salva la posizione corrente
    pos = ftell(fp);
    printf("Posizione corrente: %ld byte\n", pos);
    
    // Continua a leggere...
    
    // Torna alla posizione salvata
    fseek(fp, pos, SEEK_SET);
    
    fclose(fp);
    return 0;
}
```

### rewind()

La funzione `rewind()` riposiziona l'indicatore all'inizio del file:

```c
void rewind(FILE *stream);
```

È equivalente a `fseek(stream, 0, SEEK_SET)`, ma resetta anche l'indicatore di errore del file.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("dati.txt", "r");
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    // Legge alcuni dati...
    
    // Torna all'inizio del file
    rewind(fp);
    
    // Rilegge gli stessi dati dall'inizio
    
    fclose(fp);
    return 0;
}
```

## Accesso Casuale ai File

Le funzioni di posizionamento permettono l'accesso casuale (random access) ai file, consentendo di leggere o scrivere dati in qualsiasi punto senza dover scorrere sequenzialmente tutto il contenuto precedente.

Questo è particolarmente utile quando si lavora con file binari strutturati, come database o file contenenti record di dimensione fissa.

### Esempio: Accesso a Record in un File Binario

```c
#include <stdio.h>
#include <stdlib.h>

#define RECORD_SIZE 20

int main() {
    FILE *fp = fopen("database.bin", "rb");
    char record[RECORD_SIZE];
    int record_num;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    printf("Inserisci il numero del record da leggere: ");
    scanf("%d", &record_num);
    
    // Posiziona l'indicatore all'inizio del record desiderato
    fseek(fp, record_num * RECORD_SIZE, SEEK_SET);
    
    // Legge il record
    if (fread(record, RECORD_SIZE, 1, fp) != 1) {
        if (feof(fp)) {
            printf("Record non trovato (fine del file)\n");
        } else {
            printf("Errore nella lettura del record\n");
        }
    } else {
        printf("Record %d: ", record_num);
        for (int i = 0; i < RECORD_SIZE; i++) {
            printf("%c", record[i]);
        }
        printf("\n");
    }
    
    fclose(fp);
    return 0;
}
```

## Limitazioni

È importante notare alcune limitazioni delle funzioni di posizionamento:

1. `fseek()` e `ftell()` utilizzano il tipo `long` per rappresentare la posizione, il che può limitare la dimensione massima del file su alcuni sistemi.

2. Per file molto grandi, è preferibile utilizzare le funzioni `fseeko()` e `ftello()` (se disponibili), che utilizzano il tipo `off_t` invece di `long`.

3. Il posizionamento può essere meno efficiente nei file aperti in modalità testo su sistemi Windows, a causa della traduzione dei caratteri di nuova riga.

## Best Practices

1. **Utilizzare la modalità binaria** (`"rb"`, `"wb"`, ecc.) quando si prevede di utilizzare le funzioni di posizionamento, per evitare problemi con la traduzione dei caratteri di nuova riga.

2. **Verificare sempre il valore restituito da `fseek()`** per assicurarsi che l'operazione sia avvenuta con successo.

3. **Fare attenzione quando si utilizza `SEEK_END`** con file aperti in modalità append, poiché alcune implementazioni potrebbero non gestirlo correttamente.

4. **Salvare le posizioni importanti** utilizzando `ftell()` per potervi tornare in seguito.

## Conclusione

Le funzioni di posizionamento sono strumenti potenti che permettono di accedere ai dati in modo non sequenziale, rendendo possibili operazioni complesse sui file. La capacità di spostarsi liberamente all'interno di un file è particolarmente utile quando si lavora con file strutturati o quando è necessario modificare dati specifici senza riscrivere l'intero file.

## Esercizi

1. Scrivi un programma che legga un file di testo e ne stampi le righe in ordine inverso, utilizzando le funzioni di posizionamento.

2. Implementa un semplice database di record a lunghezza fissa, che permetta di aggiungere, visualizzare, modificare ed eliminare record utilizzando l'accesso casuale al file.

3. Crea un programma che divida un file di grandi dimensioni in più parti di dimensione specificata dall'utente, utilizzando le funzioni di posizionamento per leggere i blocchi di dati appropriati.