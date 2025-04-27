# Introduzione all'Allocazione Dinamica

## Memoria Statica vs Memoria Dinamica

In C, la memoria può essere allocata in due modi principali: staticamente o dinamicamente.

### Memoria Statica

La memoria statica viene allocata durante la compilazione del programma. Le variabili dichiarate globalmente o con la parola chiave `static` utilizzano memoria statica. Anche gli array e le strutture di dimensione fissa dichiarati all'interno delle funzioni utilizzano memoria allocata staticamente (sebbene tecnicamente si tratti di memoria automatica sullo stack).

```c
int array_statico[100]; // Dimensione fissa, determinata a tempo di compilazione
```

Limitazioni della memoria statica:
- La dimensione deve essere conosciuta a tempo di compilazione
- Non può essere ridimensionata durante l'esecuzione
- Può portare a spreco di memoria se la dimensione allocata è maggiore di quella effettivamente necessaria
- Può causare problemi se la dimensione allocata è insufficiente

### Memoria Dinamica

La memoria dinamica viene allocata durante l'esecuzione del programma, utilizzando funzioni specifiche della libreria standard C. Questa memoria viene allocata nell'area di memoria chiamata "heap" (o "free store").

```c
int *array_dinamico = (int *)malloc(n * sizeof(int)); // Dimensione determinata a runtime
```

Vantaggi della memoria dinamica:
- La dimensione può essere determinata a runtime
- Può essere ridimensionata durante l'esecuzione
- Permette di utilizzare esattamente la quantità di memoria necessaria
- Consente la creazione di strutture dati la cui dimensione non è nota a priori

## L'Heap e lo Stack

Per comprendere l'allocazione dinamica, è importante conoscere la differenza tra heap e stack.

### Stack

Lo stack è un'area di memoria gestita automaticamente dal sistema:
- Utilizzato per variabili locali e informazioni di chiamata delle funzioni
- Gestione LIFO (Last In, First Out)
- Allocazione e deallocazione automatica
- Dimensione limitata (può causare stack overflow)
- Accesso molto veloce

### Heap

L'heap è un'area di memoria più grande e flessibile:
- Utilizzato per l'allocazione dinamica
- Gestione manuale (il programmatore deve allocare e liberare la memoria)
- Dimensione limitata solo dalla memoria disponibile nel sistema
- Accesso leggermente più lento rispetto allo stack
- Può diventare frammentato con l'uso

## Quando Usare l'Allocazione Dinamica

L'allocazione dinamica è particolarmente utile nei seguenti casi:

1. **Dimensione dei dati non nota a priori**:
   ```c
   // Leggi la dimensione dell'array dall'utente
   int n;
   printf("Inserisci la dimensione dell'array: ");
   scanf("%d", &n);
   int *array = (int *)malloc(n * sizeof(int));
   ```

2. **Strutture dati che crescono o si riducono**:
   ```c
   // Ridimensionamento di un array
   array = (int *)realloc(array, nuovo_n * sizeof(int));
   ```

3. **Evitare limiti di dimensione dello stack**:
   ```c
   // Array molto grande che potrebbe causare stack overflow
   int *grande_array = (int *)malloc(1000000 * sizeof(int));
   ```

4. **Persistenza dei dati oltre lo scope della funzione**:
   ```c
   int *crea_array(int dimensione) {
       int *arr = (int *)malloc(dimensione * sizeof(int));
       // Inizializza l'array
       return arr; // L'array persiste anche dopo la fine della funzione
   }
   ```

5. **Strutture dati complesse** come liste collegate, alberi, grafi:
   ```c
   struct Nodo {
       int valore;
       struct Nodo *successivo;
   };
   
   struct Nodo *nuovo_nodo = (struct Nodo *)malloc(sizeof(struct Nodo));
   ```

## Vantaggi e Svantaggi dell'Allocazione Dinamica

### Vantaggi

- **Flessibilità**: la memoria può essere allocata esattamente quando necessario
- **Efficienza**: si utilizza solo la memoria effettivamente necessaria
- **Adattabilità**: le strutture dati possono crescere o ridursi in base alle esigenze
- **Persistenza**: i dati possono esistere oltre lo scope della funzione che li ha creati

### Svantaggi

- **Complessità**: richiede una gestione manuale della memoria
- **Rischi**: può causare memory leak, dangling pointers, e altri problemi
- **Overhead**: l'allocazione dinamica ha un costo in termini di prestazioni
- **Frammentazione**: l'uso ripetuto di allocazione e deallocazione può frammentare l'heap

## Problemi Comuni nell'Allocazione Dinamica

### Memory Leak (Perdita di Memoria)

Si verifica quando la memoria allocata non viene mai liberata, causando un consumo progressivo di memoria:

```c
void funzione_con_leak() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10;
    // Manca free(p) - Memory leak!
}
```

### Dangling Pointer (Puntatore Pendente)

Si verifica quando si accede a memoria che è stata liberata:

```c
int *p = (int *)malloc(sizeof(int));
*p = 10;
free(p);
*p = 20; // Errore: accesso a memoria liberata!
```

### Double Free (Doppia Liberazione)

Si verifica quando si tenta di liberare la stessa memoria più volte:

```c
int *p = (int *)malloc(sizeof(int));
free(p);
free(p); // Errore: doppia liberazione!
```

### Buffer Overflow

Si verifica quando si scrive oltre i limiti della memoria allocata:

```c
int *p = (int *)malloc(5 * sizeof(int));
for (int i = 0; i <= 5; i++) { // Nota: i <= 5 invece di i < 5
    p[i] = i; // Overflow quando i = 5!
}
```

## Conclusione

L'allocazione dinamica della memoria è uno strumento potente che permette di creare programmi più flessibili ed efficienti. Tuttavia, richiede una gestione attenta per evitare problemi come memory leak e dangling pointers. Nei prossimi capitoli, esploreremo in dettaglio le funzioni di allocazione e liberazione della memoria e le best practices per una gestione sicura ed efficiente della memoria dinamica.