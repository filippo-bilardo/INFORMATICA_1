# Tecniche Avanzate di Elaborazione delle Stringhe in C

Oltre alle operazioni di base e alle funzioni della libreria standard, esistono numerose tecniche avanzate per l'elaborazione delle stringhe in C. Questa guida esplora alcune di queste tecniche, fornendo esempi pratici e consigli utili.

## Tokenizzazione e Parsing

### 1. Tokenizzazione Avanzata

La tokenizzazione è il processo di suddivisione di una stringa in "token" o parti più piccole. Sebbene `strtok()` sia utile, presenta alcune limitazioni. Ecco un approccio più flessibile:

```c
#include <stdio.h>
#include <string.h>

// Funzione di tokenizzazione avanzata che preserva la stringa originale
void tokenizza(const char *str, const char *delimitatori) {
    // Crea una copia della stringa originale
    char copia[strlen(str) + 1];
    strcpy(copia, str);
    
    char *token = strtok(copia, delimitatori);
    int indice = 0;
    
    while (token != NULL) {
        printf("Token %d: %s\n", indice++, token);
        token = strtok(NULL, delimitatori);
    }
}

int main() {
    const char *testo = "Questa è una,stringa:di esempio;per tokenizzazione";
    const char *delimitatori = " ,;:";
    
    printf("Stringa originale: %s\n\n", testo);
    printf("Tokenizzazione:\n");
    tokenizza(testo, delimitatori);
    
    // La stringa originale rimane intatta
    printf("\nStringa originale dopo tokenizzazione: %s\n", testo);
    
    return 0;
}
```

### 2. Parsing di Stringhe Strutturate

Il parsing di stringhe strutturate (come CSV, JSON semplificato, ecc.) richiede un approccio più sofisticato:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struttura per memorizzare i dati di una persona
typedef struct {
    char nome[50];
    int eta;
    float altezza;
} Persona;

// Funzione per parsare una riga CSV nel formato "nome,età,altezza"
Persona *parse_csv_line(const char *line) {
    Persona *p = malloc(sizeof(Persona));
    if (!p) return NULL;
    
    // Crea una copia della riga
    char copia[strlen(line) + 1];
    strcpy(copia, line);
    
    // Estrae il nome
    char *token = strtok(copia, ",");
    if (token) strncpy(p->nome, token, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0'; // Assicura terminazione
    
    // Estrae l'età
    token = strtok(NULL, ",");
    if (token) p->eta = atoi(token);
    
    // Estrae l'altezza
    token = strtok(NULL, ",");
    if (token) p->altezza = atof(token);
    
    return p;
}

int main() {
    const char *csv_line = "Mario Rossi,35,1.78";
    
    Persona *persona = parse_csv_line(csv_line);
    if (persona) {
        printf("Dati parsati:\n");
        printf("Nome: %s\n", persona->nome);
        printf("Età: %d\n", persona->eta);
        printf("Altezza: %.2f m\n", persona->altezza);
        
        free(persona); // Libera la memoria allocata
    }
    
    return 0;
}
```

## Conversione tra Stringhe e Altri Tipi di Dati

### 1. Conversioni Numeriche Avanzate

Oltre alle funzioni base come `atoi()` e `atof()`, C offre funzioni più potenti per la conversione:

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main() {
    const char *numeri[] = {
        "42",           // Numero valido
        "   -123.45",   // Numero con spazi e segno
        "0xFF",         // Esadecimale
        "0b1010",       // Binario (non standard in C)
        "123abc",       // Numero seguito da lettere
        "non_un_numero" // Non un numero
    };
    
    for (int i = 0; i < 6; i++) {
        printf("Conversione di \"%s\":\n", numeri[i]);
        
        // Reset errno prima della conversione
        errno = 0;
        
        // Conversione a long int
        char *endptr;
        long valore = strtol(numeri[i], &endptr, 0); // Base 0 per auto-rilevamento
        
        if (errno == ERANGE) {
            printf("  Errore: valore fuori range\n");
        } else if (endptr == numeri[i]) {
            printf("  Errore: nessun carattere convertito\n");
        } else if (*endptr != '\0') {
            printf("  Conversione parziale: %ld (caratteri non convertiti: \"%s\")\n", 
                   valore, endptr);
        } else {
            printf("  Conversione completa: %ld\n", valore);
        }
        
        printf("\n");
    }
    
    return 0;
}
```

### 2. Conversione di Numeri in Stringhe

Per convertire numeri in stringhe, si possono utilizzare funzioni come `sprintf()` o `snprintf()` (più sicura):

```c
#include <stdio.h>

int main() {
    int numero_intero = 12345;
    double numero_decimale = 123.456789;
    
    char buffer[50];
    
    // Conversione di un intero in stringa
    snprintf(buffer, sizeof(buffer), "%d", numero_intero);
    printf("Intero come stringa: \"%s\"\n", buffer);
    
    // Conversione di un double in stringa con formattazione
    snprintf(buffer, sizeof(buffer), "%.2f", numero_decimale);
    printf("Double con 2 decimali: \"%s\"\n", buffer);
    
    // Formattazione più complessa
    snprintf(buffer, sizeof(buffer), "Valore: %+08.3f", numero_decimale);
    printf("Formattazione avanzata: \"%s\"\n", buffer);
    
    return 0;
}
```

## Gestione di Stringhe Dinamiche

### 1. Allocazione Dinamica di Stringhe

Per gestire stringhe di lunghezza variabile, è utile allocare memoria dinamicamente:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione che crea una nuova stringa dinamica
char *crea_stringa(const char *testo) {
    if (!testo) return NULL;
    
    // Alloca memoria per la stringa (lunghezza + terminatore null)
    char *nuova_stringa = malloc(strlen(testo) + 1);
    if (!nuova_stringa) return NULL;
    
    // Copia il testo nella nuova stringa
    strcpy(nuova_stringa, testo);
    
    return nuova_stringa;
}

// Funzione che concatena due stringhe dinamicamente
char *concatena_stringhe(const char *str1, const char *str2) {
    if (!str1 || !str2) return NULL;
    
    // Alloca memoria per la stringa risultante
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *risultato = malloc(len1 + len2 + 1);
    if (!risultato) return NULL;
    
    // Copia e concatena
    strcpy(risultato, str1);
    strcat(risultato, str2);
    
    return risultato;
}

int main() {
    // Crea stringhe dinamiche
    char *str1 = crea_stringa("Hello, ");
    char *str2 = crea_stringa("World!");
    
    if (str1 && str2) {
        printf("Stringa 1: %s\n", str1);
        printf("Stringa 2: %s\n", str2);
        
        // Concatena le stringhe
        char *str_combinata = concatena_stringhe(str1, str2);
        if (str_combinata) {
            printf("Stringa combinata: %s\n", str_combinata);
            free(str_combinata); // Libera la memoria
        }
        
        // Libera la memoria delle stringhe originali
        free(str1);
        free(str2);
    }
    
    return 0;
}
```

### 2. Implementazione di una Stringa Dinamica Ridimensionabile

Una struttura più avanzata per gestire stringhe che possono crescere dinamicamente:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struttura per una stringa dinamica
typedef struct {
    char *testo;      // Puntatore al buffer
    size_t lunghezza; // Lunghezza attuale della stringa
    size_t capacita;  // Capacità totale del buffer
} StringaDinamica;

// Inizializza una nuova stringa dinamica
StringaDinamica *inizializza_stringa(const char *testo_iniziale) {
    StringaDinamica *sd = malloc(sizeof(StringaDinamica));
    if (!sd) return NULL;
    
    size_t len_iniziale = testo_iniziale ? strlen(testo_iniziale) : 0;
    size_t capacita_iniziale = len_iniziale > 0 ? len_iniziale * 2 : 10;
    
    sd->testo = malloc(capacita_iniziale);
    if (!sd->testo) {
        free(sd);
        return NULL;
    }
    
    if (testo_iniziale) {
        strcpy(sd->testo, testo_iniziale);
        sd->lunghezza = len_iniziale;
    } else {
        sd->testo[0] = '\0';
        sd->lunghezza = 0;
    }
    
    sd->capacita = capacita_iniziale;
    return sd;
}

// Assicura che la stringa abbia abbastanza capacità
int assicura_capacita(StringaDinamica *sd, size_t capacita_minima) {
    if (!sd || capacita_minima <= sd->capacita) return 1;
    
    // Calcola la nuova capacità (doppia della richiesta)
    size_t nuova_capacita = capacita_minima * 2;
    
    // Ridimensiona il buffer
    char *nuovo_buffer = realloc(sd->testo, nuova_capacita);
    if (!nuovo_buffer) return 0;
    
    sd->testo = nuovo_buffer;
    sd->capacita = nuova_capacita;
    return 1;
}

// Aggiunge testo alla stringa dinamica
int aggiungi_testo(StringaDinamica *sd, const char *testo) {
    if (!sd || !testo) return 0;
    
    size_t len_testo = strlen(testo);
    size_t nuova_lunghezza = sd->lunghezza + len_testo;
    
    // Assicura che ci sia abbastanza spazio
    if (!assicura_capacita(sd, nuova_lunghezza + 1)) return 0;
    
    // Aggiunge il nuovo testo
    strcat(sd->testo, testo);
    sd->lunghezza = nuova_lunghezza;
    
    return 1;
}

// Libera la memoria della stringa dinamica
void libera_stringa(StringaDinamica *sd) {
    if (sd) {
        free(sd->testo);
        free(sd);
    }
}

int main() {
    // Crea una stringa dinamica
    StringaDinamica *sd = inizializza_stringa("Ciao ");
    if (!sd) {
        printf("Errore nell'inizializzazione della stringa\n");
        return 1;
    }
    
    printf("Stringa iniziale: %s\n", sd->testo);
    printf("Lunghezza: %zu, Capacità: %zu\n\n", sd->lunghezza, sd->capacita);
    
    // Aggiunge testo alla stringa
    aggiungi_testo(sd, "Mondo! ");
    printf("Dopo prima aggiunta: %s\n", sd->testo);
    printf("Lunghezza: %zu, Capacità: %zu\n\n", sd->lunghezza, sd->capacita);
    
    // Aggiunge altro testo
    aggiungi_testo(sd, "Questa è una stringa dinamica che può crescere automaticamente.");
    printf("Dopo seconda aggiunta: %s\n", sd->testo);
    printf("Lunghezza: %zu, Capacità: %zu\n", sd->lunghezza, sd->capacita);
    
    // Libera la memoria
    libera_stringa(sd);
    
    return 0;
}
```

## Algoritmi di Elaborazione delle Stringhe

### 1. Ricerca di Pattern con l'Algoritmo di Boyer-Moore Semplificato

Un algoritmo efficiente per la ricerca di sottostringhe:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 256

// Funzione che implementa una versione semplificata dell'algoritmo di Boyer-Moore
int *cerca_pattern(const char *testo, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(testo);
    
    if (m > n) return NULL;
    
    // Alloca memoria per l'array dei risultati
    // Il primo elemento conterrà il numero di occorrenze trovate
    int *risultati = calloc(n + 1, sizeof(int));
    if (!risultati) return NULL;
    
    // Preprocessing: tabella degli spostamenti
    int spostamento[MAX_CHAR];
    for (int i = 0; i < MAX_CHAR; i++) {
        spostamento[i] = m; // Spostamento di default
    }
    
    // Popola la tabella degli spostamenti per i caratteri nel pattern
    for (int i = 0; i < m - 1; i++) {
        spostamento[(unsigned char)pattern[i]] = m - 1 - i;
    }
    
    // Ricerca del pattern
    int num_trovati = 0;
    int i = m - 1;
    
    while (i < n) {
        int j = m - 1;
        int k = i;
        
        // Confronta il pattern da destra a sinistra
        while (j >= 0 && pattern[j] == testo[k]) {
            j--;
            k--;
        }
        
        // Pattern trovato
        if (j < 0) {
            risultati[++num_trovati] = k + 1; // Salva la posizione
            i++; // Sposta di una posizione
        } else {
            // Calcola lo spostamento
            i += spostamento[(unsigned char)testo[i]];
        }
    }
    
    risultati[0] = num_trovati; // Salva il numero di occorrenze
    return risultati;
}

int main() {
    const char *testo = "Questo è un testo di esempio. Questo testo contiene ripetizioni.";
    const char *pattern = "testo";
    
    printf("Testo: %s\n", testo);
    printf("Pattern da cercare: %s\n\n", pattern);
    
    int *risultati = cerca_pattern(testo, pattern);
    if (risultati) {
        int num_trovati = risultati[0];
        printf("Trovate %d occorrenze:\n", num_trovati);
        
        for (int i = 1; i <= num_trovati; i++) {
            printf("  Posizione %d: ", risultati[i]);
            
            // Stampa il contesto
            int inizio = risultati[i] > 10 ? risultati[i] - 10 : 0;
            int fine = risultati[i] + strlen(pattern) + 10 < strlen(testo) ? 
                      risultati[i] + strlen(pattern) + 10 : strlen(testo);
            
            for (int j = inizio; j < fine; j++) {
                if (j == risultati[i]) printf("[");
                printf("%c", testo[j]);
                if (j == risultati[i] + strlen(pattern) - 1) printf("]");
            }
            printf("\n");
        }
        
        free(risultati);
    } else {
        printf("Pattern non trovato o errore di allocazione memoria\n");
    }
    
    return 0;
}
```

### 2. Compressione e Decompressione di Stringhe

Un semplice algoritmo di compressione Run-Length Encoding (RLE):

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per comprimere una stringa usando RLE
char *comprimi_rle(const char *input) {
    if (!input || strlen(input) == 0) return NULL;
    
    size_t len = strlen(input);
    // Nel caso peggiore, la stringa compressa è più lunga dell'originale
    char *output = malloc(len * 2 + 1);
    if (!output) return NULL;
    
    size_t out_index = 0;
    for (size_t i = 0; i < len; i++) {
        char current = input[i];
        int count = 1;
        
        // Conta caratteri consecutivi uguali
        while (i + 1 < len && input[i + 1] == current) {
            count++;
            i++;
        }
        
        // Aggiungi il carattere e il conteggio alla stringa compressa
        if (count > 1) {
            out_index += sprintf(output + out_index, "%c%d", current, count);
        } else {
            output[out_index++] = current;
        }
    }
    
    output[out_index] = '\0';
    return output;
}

// Funzione per decomprimere una stringa RLE
char *decomprimi_rle(const char *input) {
    if (!input || strlen(input) == 0) return NULL;
    
    size_t len = strlen(input);
    // Allocazione iniziale (potrebbe essere necessario ridimensionare)
    size_t max_size = len * 10; // Stima generosa
    char *output = malloc(max_size);
    if (!output) return NULL;
    
    size_t out_index = 0;
    for (size_t i = 0; i < len; i++) {
        char current = input[i];
        
        // Controlla se il carattere successivo è un numero
        if (i + 1 < len && input[i + 1] >= '0' && input[i + 1] <= '9') {
            // Estrai il numero di ripetizioni
            int count = 0;
            size_t j = i + 1;
            while (j < len && input[j] >= '0' && input[j] <= '9') {
                count = count * 10 + (input[j] - '0');
                j++;
            }
            
            // Ripeti il carattere 'count' volte
            for (int k = 0; k < count; k++) {
                output[out_index++] = current;
                if (out_index >= max_size - 1) {
                    // Ridimensiona se necessario
                    max_size *= 2;
                    char *temp = realloc(output, max_size);
                    if (!temp) {
                        free(output);
                        return NULL;
                    }
                    output = temp;
                }
            }
            
            i = j - 1; // Aggiorna l'indice
        } else {
            // Carattere singolo
            output[out_index++] = current;
        }
    }
    
    output[out_index] = '\0';
    return output;
}

int main() {
    const char *originale = "AAABBBCCDEEEEEFGGG";
    printf("Stringa originale: %s\n", originale);
    
    char *compressa = comprimi_rle(originale);
    if (compressa) {
        printf("Stringa compressa: %s\n", compressa);
        
        char *decompressa = decomprimi_rle(compressa);
        if (decompressa) {
            printf("Stringa decompressa: %s\n", decompressa);
            printf("Verifica correttezza: %s\n", 
                   strcmp(originale, decompressa) == 0 ? "OK" : "ERRORE");
            
            free(decompressa);
        }
        
        free(compressa);
    }
    
    return 0;
}
```

## Considerazioni sulla Sicurezza

### 1. Prevenzione di Buffer Overflow

I buffer overflow sono una delle vulnerabilità più comuni nei programmi C. Ecco un esempio di come prevenirli:

```c
#include <stdio.h>
#include <string.h>

// Funzione non sicura
void funzione_non_sicura(const char *input) {
    char buffer[10];
    strcpy(buffer, input); // Pericoloso: nessun controllo della dimensione
    printf("Buffer: %s\n", buffer);
}

// Funzione sicura
void funzione_sicura(const char *input) {
    char buffer[10];
    size_t buffer_size = sizeof(buffer);
    
    // Copia sicura con controllo della dimensione
    strncpy(buffer, input, buffer_size - 1);
    buffer[buffer_size - 1] = '\0'; // Assicura la terminazione
    
    printf("Buffer: %s\n", buffer);
}

int main() {
    const char *input_corto = "Ciao";
    const char *input_lungo = "Questa è una stringa molto lunga che causerà un buffer overflow";
    
    printf("Input corto:\n");
    funzione_sicura(input_corto);
    
    printf("\nInput lungo (potenzialmente pericoloso):\n");
    funzione_sicura(input_lungo); // Sicura: tronca l'input
    // funzione_non_sicura(input_lungo); // Non sicura: causerebbe buffer overflow
    
    return 0;
}
```

### 2. Validazione dell'Input

La validazione dell'input è essenziale per prevenire vulnerabilità di sicurezza:

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Funzione che verifica se una stringa contiene solo caratteri alfanumerici
int e_alfanumerico(const char *str) {
    if (!str) return 0;
    
    while (*str) {
        if (!isalnum((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    
    return 1;
}

// Funzione che sanitizza una stringa rimuovendo caratteri non alfanumerici
void sanitizza_stringa(char *str) {
    if (!str) return;
    
    char *src = str;
    char *dst = str;
    
    while (*src) {
        if (isalnum((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    
    *dst = '\0';
}

int main() {
    char input1[] = "Testo123";
    char input2[] = "Testo<script>alert('XSS')</script>";
    
    printf("Input 1: %s\n", input1);
    printf("È alfanumerico? %s\n\n", e_alfanumerico(input1) ? "Sì" : "No");
    
    printf("Input 2 (potenzialmente pericoloso): %s\n", input2);
    printf("È alfanumerico? %s\n", e_alfanumerico(input2) ? "Sì" : "No");
    
    sanitizza_stringa(input2);
    printf("Input 2 dopo sanitizzazione: %s\n", input2);
    
    return 0;
}
```

## Domande di Autovalutazione

1. Quali sono i vantaggi e gli svantaggi dell'allocazione dinamica di stringhe rispetto agli array di caratteri statici?

2. Come si può implementare una funzione di ricerca di sottostringhe che sia insensibile alle maiuscole/minuscole?

3. Quali precauzioni bisogna prendere quando si implementa un parser per stringhe strutturate come CSV o JSON?

4. Quali sono le tecniche più efficaci per prevenire i buffer overflow nelle applicazioni C?

5. Come si può ottimizzare l'elaborazione delle stringhe in applicazioni che gestiscono grandi volumi di dati testuali?

## Esercizi Proposti

1. Implementa una funzione che converta una stringa in formato "camelCase" (es. "questoÈUnEsempio") in formato "snake_case" (es. "questo_è_un_esempio").

2. Crea un parser semplice per stringhe in formato JSON che estragga valori di tipo stringa, numero e booleano.

3. Implementa un algoritmo di ricerca fuzzy che trovi parole simili a una data parola di input (ad esempio, utilizzando la distanza di Levenshtein).

4. Scrivi una funzione che comprima una stringa utilizzando l'algoritmo di compressione Huffman.

5. Crea una libreria di funzioni per la gestione sicura delle stringhe che includa versioni sicure di `strcat`, `strcpy` e altre funzioni comuni, con controlli integrati per prevenire buffer overflow.