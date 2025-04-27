# Ottimizzazione delle Prestazioni in C

## Introduzione

L'ottimizzazione delle prestazioni è un aspetto fondamentale della programmazione in C, soprattutto per applicazioni che richiedono elevata efficienza. Questo documento esplora varie tecniche di ottimizzazione che consentono di migliorare la velocità di esecuzione e ridurre l'utilizzo delle risorse.

## Tecniche di Ottimizzazione a Livello di Algoritmo

### Complessità Algoritmica

La scelta dell'algoritmo giusto è spesso il fattore più importante per l'ottimizzazione:

```c
// Esempio: Ricerca in un array
// Approccio non ottimizzato: O(n)
int ricerca_lineare(int arr[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

// Approccio ottimizzato (per array ordinati): O(log n)
int ricerca_binaria(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2; // Evita overflow
        
        if (arr[m] == x)
            return m;
        
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
```

### Ottimizzazione dei Cicli

```c
// Non ottimizzato
for (int i = 0; i < n; i++) {
    // Calcolo costoso ripetuto ad ogni iterazione
    int limite = calcola_limite_costoso();
    for (int j = 0; j < limite; j++) {
        // Operazioni
    }
}

// Ottimizzato
int limite = calcola_limite_costoso(); // Calcolo eseguito una sola volta
for (int i = 0; i < n; i++) {
    for (int j = 0; j < limite; j++) {
        // Operazioni
    }
}
```

### Evitare Calcoli Ridondanti

```c
// Non ottimizzato
for (int i = 0; i < n; i++) {
    risultato[i] = pow(base, i); // Ricalcola ogni potenza da zero
}

// Ottimizzato
double potenza = 1.0;
for (int i = 0; i < n; i++) {
    risultato[i] = potenza;
    potenza *= base; // Usa il risultato precedente
}
```

## Ottimizzazione della Memoria e Cache-Friendly Programming

### Allineamento dei Dati

```c
// Struttura non ottimizzata (possibile padding)
struct Esempio1 {
    char a;       // 1 byte
    double b;     // 8 byte
    char c;       // 1 byte
}; // Dimensione probabile: 24 byte a causa del padding

// Struttura ottimizzata
struct Esempio2 {
    double b;     // 8 byte
    char a;       // 1 byte
    char c;       // 1 byte
}; // Dimensione probabile: 16 byte
```

### Accesso Sequenziale alla Memoria

```c
// Non ottimizzato (accesso non sequenziale)
for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
        matrice[i][j] = i + j; // Accesso per colonne in C
    }
}

// Ottimizzato (accesso sequenziale)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        matrice[i][j] = i + j; // Accesso per righe in C
    }
}
```

### Località dei Dati

```c
// Struttura di array (non ottimizzata per cache)
struct Punto {
    double x, y, z;
};
struct Punto punti[1000];

// Array di strutture (ottimizzata per cache)
double x[1000], y[1000], z[1000];

// Esempio di elaborazione ottimizzata
for (int i = 0; i < 1000; i++) {
    x[i] = x[i] * 2; // Migliore località dei dati
}
```

## Profiling e Benchmarking del Codice

### Strumenti di Profiling

- **gprof**: Analizza il tempo di esecuzione delle funzioni
- **Valgrind/Callgrind**: Analizza l'utilizzo della memoria e della cache
- **perf**: Strumento di profiling a basso livello per Linux

### Esempio di Benchmarking

```c
#include <stdio.h>
#include <time.h>

double benchmark_function(void (*func)(void), int iterations) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    for (int i = 0; i < iterations; i++) {
        func();
    }
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

void test_function1(void) {
    // Implementazione della funzione da testare
}

void test_function2(void) {
    // Implementazione alternativa
}

int main() {
    int iterations = 1000000;
    
    double time1 = benchmark_function(test_function1, iterations);
    double time2 = benchmark_function(test_function2, iterations);
    
    printf("Funzione 1: %f secondi\n", time1);
    printf("Funzione 2: %f secondi\n", time2);
    printf("Rapporto: %f\n", time1 / time2);
    
    return 0;
}
```

## Ottimizzazioni Specifiche per l'Architettura

### Istruzioni SIMD (Single Instruction, Multiple Data)

```c
#include <immintrin.h> // Per istruzioni AVX

// Somma vettoriale senza SIMD
void somma_vettori(float* a, float* b, float* risultato, int n) {
    for (int i = 0; i < n; i++) {
        risultato[i] = a[i] + b[i];
    }
}

// Somma vettoriale con AVX (per processori che lo supportano)
void somma_vettori_avx(float* a, float* b, float* risultato, int n) {
    int i = 0;
    for (; i <= n - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&risultato[i], vr);
    }
    // Gestione elementi rimanenti
    for (; i < n; i++) {
        risultato[i] = a[i] + b[i];
    }
}
```

### Ottimizzazione della Branch Prediction

```c
// Difficile da predire (dipende dai dati)
for (int i = 0; i < n; i++) {
    if (dati[i] > soglia) { // Branch imprevedibile
        somma += dati[i];
    }
}

// Più prevedibile (ordinando i dati)
// Ordinare i dati prima del ciclo
qsort(dati, n, sizeof(int), compare_func);
for (int i = 0; i < n; i++) {
    if (dati[i] > soglia) { // Branch più prevedibile
        somma += dati[i];
    }
}
```

## Best Practices

1. **Misurare prima di ottimizzare**: Utilizzare strumenti di profiling per identificare i colli di bottiglia reali.
2. **Ottimizzare gli algoritmi prima del codice**: Un algoritmo migliore supera sempre le micro-ottimizzazioni.
3. **Considerare i compromessi**: L'ottimizzazione spesso comporta compromessi tra velocità, memoria e leggibilità.
4. **Documentare le ottimizzazioni**: Le ottimizzazioni complesse dovrebbero essere ben documentate.
5. **Testare su diverse architetture**: Le prestazioni possono variare significativamente tra diverse CPU.

## Esercizi Pratici

1. Implementare un algoritmo di ordinamento e ottimizzarlo per diversi tipi di input.
2. Confrontare le prestazioni di diverse strutture dati (array, liste collegate, alberi) per operazioni specifiche.
3. Ottimizzare un'applicazione esistente utilizzando tecniche di profiling per identificare i colli di bottiglia.
4. Implementare una versione cache-friendly di un algoritmo di elaborazione matriciale.

## Domande di Autovalutazione

1. Quali sono i principali fattori che influenzano le prestazioni di un programma C?
2. Come si può determinare quale parte del codice necessita di ottimizzazione?
3. Quali sono i compromessi tipici nelle decisioni di ottimizzazione?
4. Come influisce l'architettura della CPU sulle strategie di ottimizzazione?
5. In che modo la gestione della memoria può influenzare le prestazioni di un'applicazione?

## Conclusione

L'ottimizzazione delle prestazioni in C richiede una comprensione approfondita sia del linguaggio che dell'hardware sottostante. Applicando le tecniche discusse in questo documento, è possibile sviluppare applicazioni C che sfruttano al massimo le risorse disponibili, mantenendo al contempo la correttezza e la manutenibilità del codice.