# Librerie Statiche e Dinamiche in C

Le librerie sono collezioni di codice precompilato che possono essere riutilizzate in diversi programmi. In C, esistono due tipi principali di librerie: statiche e dinamiche. Comprendere le differenze e sapere quando utilizzare ciascun tipo è fondamentale per lo sviluppo di software modulare ed efficiente.

## Librerie Statiche

Le librerie statiche (`.a` su Unix/Linux, `.lib` su Windows) sono collezioni di file oggetto che vengono incorporate direttamente nell'eseguibile durante la fase di linking.

### Vantaggi delle Librerie Statiche

1. **Eseguibile Autonomo**: L'applicazione non dipende da librerie esterne a runtime
2. **Prestazioni**: Nessun overhead di caricamento delle librerie durante l'esecuzione
3. **Versioning**: Non ci sono problemi di compatibilità con diverse versioni della libreria
4. **Distribuzione**: Più semplice, poiché non è necessario distribuire librerie separate

### Svantaggi delle Librerie Statiche

1. **Dimensione dell'Eseguibile**: Gli eseguibili sono più grandi perché includono tutto il codice della libreria
2. **Utilizzo della Memoria**: Se più programmi utilizzano la stessa libreria, ogni programma ha la propria copia
3. **Aggiornamenti**: Per aggiornare la libreria, è necessario ricompilare l'intero programma

### Creazione di una Libreria Statica

1. **Compilare i File Sorgente in File Oggetto**:

```bash
gcc -c matematica.c -o matematica.o
gcc -c geometria.c -o geometria.o
```

2. **Creare la Libreria Statica**:

```bash
# Su Unix/Linux
ar rcs libmatematica.a matematica.o geometria.o

# Su Windows (con MinGW)
ar rcs libmatematica.a matematica.o geometria.o
```

3. **Utilizzare la Libreria Statica**:

```bash
gcc main.c -L. -lmatematica -o programma
```

L'opzione `-L.` indica al linker di cercare le librerie nella directory corrente, mentre `-lmatematica` indica di utilizzare la libreria `libmatematica.a`.

## Librerie Dinamiche

Le librerie dinamiche (`.so` su Unix/Linux, `.dll` su Windows) sono caricate in memoria a runtime, quando il programma viene eseguito.

### Vantaggi delle Librerie Dinamiche

1. **Dimensione dell'Eseguibile**: Gli eseguibili sono più piccoli perché non includono il codice della libreria
2. **Condivisione della Memoria**: Più programmi possono condividere la stessa copia della libreria in memoria
3. **Aggiornamenti**: Le librerie possono essere aggiornate senza ricompilare i programmi che le utilizzano
4. **Plugin**: Permettono di estendere le funzionalità di un programma senza modificare il codice principale

### Svantaggi delle Librerie Dinamiche

1. **Dipendenze**: L'applicazione dipende dalla disponibilità delle librerie a runtime
2. **Versioning**: Possono verificarsi problemi di compatibilità con diverse versioni della libreria ("DLL hell")
3. **Distribuzione**: Più complessa, poiché è necessario distribuire anche le librerie
4. **Prestazioni**: Leggero overhead per il caricamento delle librerie durante l'esecuzione

### Creazione di una Libreria Dinamica

1. **Compilare i File Sorgente con l'Opzione `-fPIC` (Position Independent Code)**:

```bash
gcc -fPIC -c matematica.c -o matematica.o
gcc -fPIC -c geometria.c -o geometria.o
```

2. **Creare la Libreria Dinamica**:

```bash
# Su Unix/Linux
gcc -shared -o libmatematica.so matematica.o geometria.o

# Su Windows (con MinGW)
gcc -shared -o libmatematica.dll matematica.o geometria.o -Wl,--out-implib,libmatematica.a
```

3. **Utilizzare la Libreria Dinamica**:

```bash
# Compilazione
gcc main.c -L. -lmatematica -o programma

# Esecuzione (su Unix/Linux)
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./programma
```

Su Windows, la DLL deve essere nella stessa directory dell'eseguibile o in una directory nel PATH.

## Caricamento Dinamico a Runtime

Oltre al linking dinamico, C permette anche di caricare librerie dinamiche a runtime utilizzando le funzioni della libreria `dlfcn.h` su Unix/Linux o le funzioni di Windows API su Windows.

### Esempio su Unix/Linux

```c
#include <stdio.h>
#include <dlfcn.h>

typedef int (*funzione_somma)(int, int);

int main() {
    void* handle = dlopen("./libmatematica.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    
    funzione_somma somma = (funzione_somma)dlsym(handle, "somma");
    if (!somma) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    
    printf("Somma: %d\n", somma(10, 5));
    
    dlclose(handle);
    return 0;
}
```

Compilazione:

```bash
gcc main_dinamico.c -ldl -o programma_dinamico
```

## Quando Usare Librerie Statiche o Dinamiche?

### Usa Librerie Statiche Quando:

- L'applicazione deve essere autonoma e non dipendere da librerie esterne
- La libreria è piccola e utilizzata solo da pochi programmi
- Le prestazioni sono critiche e vuoi evitare l'overhead del caricamento dinamico
- Vuoi evitare problemi di compatibilità con diverse versioni della libreria

### Usa Librerie Dinamiche Quando:

- Più programmi utilizzano la stessa libreria e vuoi risparmiare memoria
- La libreria è grande e utilizzata da molti programmi
- Vuoi poter aggiornare la libreria senza ricompilare i programmi che la utilizzano
- Vuoi implementare un sistema di plugin per estendere le funzionalità dell'applicazione

## Gestione delle Dipendenze

Per gestire le dipendenze delle librerie, è possibile utilizzare strumenti come:

- **pkg-config**: Fornisce informazioni sulle librerie installate
- **CMake**: Sistema di build cross-platform che semplifica la gestione delle dipendenze
- **Autotools**: Suite di strumenti per la creazione di pacchetti software portabili

## Conclusione

Le librerie statiche e dinamiche sono strumenti potenti per la programmazione modulare in C. La scelta tra i due tipi dipende dalle specifiche esigenze del progetto, considerando fattori come la dimensione dell'eseguibile, l'utilizzo della memoria, la facilità di aggiornamento e la distribuzione.

Comprendere come creare e utilizzare entrambi i tipi di librerie è essenziale per sviluppare software modulare, efficiente e manutenibile in C.