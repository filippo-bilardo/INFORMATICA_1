# Introduzione alle Librerie Standard in C

## Cos'è una Libreria Standard?

Le librerie standard in C sono collezioni di funzioni, macro, tipi di dati e costanti predefinite che estendono le funzionalità del linguaggio base. Queste librerie sono parte integrante dello standard C e sono disponibili in tutti gli ambienti di sviluppo conformi allo standard.

Le librerie standard forniscono soluzioni per operazioni comuni come:
- Input/output
- Manipolazione di stringhe
- Allocazione di memoria
- Operazioni matematiche
- Gestione del tempo
- E molto altro

## Evoluzione delle Librerie Standard

Le librerie standard C si sono evolute nel tempo con le diverse versioni dello standard:

- **C89/C90**: Prima standardizzazione ufficiale, introdusse le librerie di base
- **C99**: Aggiunse nuove librerie come `complex.h`, `stdbool.h`, e `tgmath.h`
- **C11**: Introdusse librerie per il multithreading (`threads.h`) e funzioni di sicurezza
- **C17/C18**: Principalmente correzioni di bug e chiarimenti

## Principali Librerie Standard

Ecco una panoramica delle librerie standard più utilizzate:

### stdio.h

Fornisce funzioni per l'input/output standard:

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");  // Output su console
    
    FILE *file = fopen("test.txt", "w");  // Apertura file
    if (file != NULL) {
        fprintf(file, "Testo nel file\n");  // Scrittura su file
        fclose(file);  // Chiusura file
    }
    
    return 0;
}
```

### stdlib.h

Fornisce funzioni di utilità generale:

```c
#include <stdlib.h>

int main() {
    // Allocazione dinamica della memoria
    int *array = (int*)malloc(10 * sizeof(int));
    if (array != NULL) {
        // Utilizzo dell'array
        for (int i = 0; i < 10; i++) {
            array[i] = i * 2;
        }
        
        // Liberazione della memoria
        free(array);
    }
    
    // Conversione di stringhe in numeri
    const char *str = "123";
    int num = atoi(str);  // num = 123
    
    // Generazione di numeri casuali
    int random_num = rand() % 100;  // Numero casuale tra 0 e 99
    
    return 0;
}
```

### string.h

Fornisce funzioni per la manipolazione delle stringhe:

```c
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[50] = " World";
    
    // Concatenazione di stringhe
    strcat(str1, str2);  // str1 diventa "Hello World"
    
    // Lunghezza di una stringa
    size_t len = strlen(str1);  // len = 11
    
    // Copia di stringhe
    char str3[50];
    strcpy(str3, str1);  // str3 diventa "Hello World"
    
    // Confronto di stringhe
    if (strcmp(str1, str3) == 0) {
        printf("Le stringhe sono uguali\n");
    }
    
    return 0;
}
```

### math.h

Fornisce funzioni matematiche:

```c
#include <math.h>

int main() {
    double x = 2.0;
    
    // Funzioni di potenza e radice
    double square = pow(x, 2);  // square = 4.0
    double sq_root = sqrt(square);  // sq_root = 2.0
    
    // Funzioni trigonometriche
    double angle = M_PI / 4;  // 45 gradi in radianti
    double sin_val = sin(angle);  // sin(45°) ≈ 0.7071
    
    // Arrotondamento
    double y = 3.7;
    double y_ceil = ceil(y);  // y_ceil = 4.0
    double y_floor = floor(y);  // y_floor = 3.0
    double y_round = round(y);  // y_round = 4.0
    
    return 0;
}
```

### time.h

Fornisce funzioni per la gestione del tempo:

```c
#include <time.h>
#include <stdio.h>

int main() {
    // Tempo corrente
    time_t now = time(NULL);
    printf("Secondi dall'epoca: %ld\n", now);
    
    // Conversione in formato leggibile
    char *time_str = ctime(&now);
    printf("Data e ora: %s", time_str);
    
    // Misura del tempo di esecuzione
    clock_t start = clock();
    // Operazione da misurare
    for (int i = 0; i < 1000000; i++) {
        // Operazione intensiva
    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo di esecuzione: %f secondi\n", cpu_time_used);
    
    return 0;
}
```

## Come Includere le Librerie

Per utilizzare una libreria standard, è necessario includerla nel codice sorgente utilizzando la direttiva `#include`:

```c
#include <nome_libreria.h>
```

Le parentesi angolari `< >` indicano al preprocessore di cercare il file header nei percorsi standard del sistema.

## Vantaggi dell'Utilizzo delle Librerie Standard

1. **Portabilità**: Le librerie standard sono disponibili su tutti i sistemi conformi allo standard C.
2. **Affidabilità**: Le funzioni sono ampiamente testate e ottimizzate.
3. **Efficienza**: Molte implementazioni sono ottimizzate per le prestazioni.
4. **Standardizzazione**: Interfacce coerenti e ben documentate.
5. **Risparmio di tempo**: Non è necessario reinventare soluzioni per problemi comuni.

## Best Practices

1. **Controllo degli errori**: Verificare sempre i valori di ritorno delle funzioni per gestire gli errori.

   ```c
   FILE *file = fopen("dati.txt", "r");
   if (file == NULL) {
       perror("Errore nell'apertura del file");
       return 1;
   }
   ```

2. **Funzioni sicure**: Utilizzare versioni sicure delle funzioni quando disponibili.

   ```c
   // Meno sicuro
   char dest[10];
   strcpy(dest, "stringa troppo lunga");  // Rischio di buffer overflow
   
   // Più sicuro
   char dest[10];
   strncpy(dest, "stringa troppo lunga", 9);
   dest[9] = '\0';  // Assicura la terminazione della stringa
   ```

3. **Gestione della memoria**: Liberare sempre la memoria allocata dinamicamente.

   ```c
   int *array = (int*)malloc(10 * sizeof(int));
   if (array != NULL) {
       // Utilizzo dell'array
       free(array);  // Importante: libera la memoria
   }
   ```

4. **Documentazione**: Consultare la documentazione ufficiale per comprendere il comportamento esatto delle funzioni.

## Librerie Standard Meno Conosciute

Oltre alle librerie più comuni, ci sono altre librerie standard utili:

- **ctype.h**: Funzioni per la classificazione e manipolazione dei caratteri
- **assert.h**: Macro per il debugging
- **signal.h**: Gestione dei segnali
- **setjmp.h**: Funzioni per salti non locali
- **locale.h**: Supporto per la localizzazione
- **float.h** e **limits.h**: Costanti dei limiti dei tipi di dati

## Esercizi Pratici

1. Scrivi un programma che utilizzi funzioni da almeno tre librerie standard diverse per risolvere un problema pratico.

2. Implementa un programma che legga un file di testo, conti le occorrenze di ogni parola e scriva i risultati in un nuovo file.

3. Crea un'applicazione che generi numeri casuali, li ordini e calcoli statistiche come media, mediana e deviazione standard.

4. Sviluppa un programma che misuri il tempo di esecuzione di diversi algoritmi di ordinamento e confronti le loro prestazioni.

## Domande di Autovalutazione

1. Quali sono le principali librerie standard del C e quali funzionalità offrono?

2. Perché è importante controllare i valori di ritorno delle funzioni delle librerie standard?

3. Quali sono le differenze tra le funzioni di manipolazione delle stringhe sicure e non sicure?

4. Come si può utilizzare la libreria time.h per misurare le prestazioni di un algoritmo?

5. Quali librerie standard introdurrebbero gli standard C99 e C11 rispetto al C89/C90?