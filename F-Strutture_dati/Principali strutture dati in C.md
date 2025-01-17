In C, ci sono diverse strutture dati che vengono utilizzate per organizzare e gestire i dati in modo efficiente. Ecco le principali strutture dati disponibili nel linguaggio C:

### 1. **Array**
   - **Descrizione**: Un array è una collezione di elementi dello stesso tipo memorizzati in memoria contigua. Gli array in C hanno dimensione fissa e sono indicizzati a partire da 0.
   - **Utilizzo**: È utile quando si devono memorizzare molti dati dello stesso tipo, come una lista di numeri o una serie di stringhe.
   - **Sintassi**:
     ```c
     int numeri[5] = {1, 2, 3, 4, 5};
     ```
   
### 2. **Struct (Struttura)**
   - **Descrizione**: Una struct permette di raggruppare diversi tipi di dati sotto un unico nome. Può contenere variabili di diversi tipi, chiamate membri.
   - **Utilizzo**: Utilizzata per creare tipi di dati complessi, come rappresentare una "persona" che ha nome, età e altezza.
   - **Sintassi**:
     ```c
     struct Persona {
         char nome[50];
         int eta;
         float altezza;
     };

     struct Persona p1 = {"Mario", 25, 1.75};
     ```

### 3. **Pointer (Puntatori)**
   - **Descrizione**: Un puntatore è una variabile che memorizza l'indirizzo di memoria di un'altra variabile. Sono essenziali per la gestione dinamica della memoria e per lavorare con array e strutture dati complesse.
   - **Utilizzo**: Utilizzati per passare grandi strutture a funzioni senza copiarle, o per la gestione della memoria dinamica.
   - **Sintassi**:
     ```c
     int a = 10;
     int *p = &a;
     ```

### 4. **Linked List (Lista collegata)**
   - **Descrizione**: Una lista collegata è una struttura dati lineare composta da nodi, dove ogni nodo contiene un dato e un puntatore al nodo successivo.
   - **Utilizzo**: Utilizzata quando non si conosce la dimensione dei dati in anticipo e si ha bisogno di una struttura dati dinamica.
   - **Sintassi**:
     ```c
     struct Nodo {
         int dato;
         struct Nodo* successivo;
     };
     ```

### 5. **Stack (Pila)**
   - **Descrizione**: Una pila è una struttura dati che segue il principio LIFO (Last In, First Out), ovvero l'ultimo elemento inserito è il primo a essere rimosso.
   - **Utilizzo**: Utilizzata nelle operazioni di backtracking, per la gestione delle chiamate ricorsive e per l'implementazione di funzionalità come l'annullamento.
   - **Operazioni principali**:
     - `push`: Aggiungi un elemento in cima alla pila.
     - `pop`: Rimuovi l'elemento in cima alla pila.
   - **Implementazione**: Le pile possono essere implementate tramite array o liste collegate.

### 6. **Queue (Coda)**
   - **Descrizione**: Una coda è una struttura dati che segue il principio FIFO (First In, First Out), ovvero il primo elemento inserito è il primo a essere rimosso.
   - **Utilizzo**: Utilizzata nei sistemi di elaborazione in background, nei buffer di dati e negli algoritmi di ricerca in ampiezza (BFS).
   - **Operazioni principali**:
     - `enqueue`: Aggiungi un elemento alla fine della coda.
     - `dequeue`: Rimuovi l'elemento dall'inizio della coda.
   - **Implementazione**: Anche le code possono essere implementate tramite array o liste collegate.

### 7. **Heap (Monticello)**
   - **Descrizione**: Un heap è una struttura dati ad albero binario che soddisfa la proprietà di heap, ovvero in un **Max-Heap**, il valore del nodo genitore è maggiore o uguale a quello dei figli, mentre in un **Min-Heap** è minore o uguale.
   - **Utilizzo**: Utilizzato per implementare code con priorità e per eseguire l'ordinamento con l'algoritmo heapsort.
   - **Implementazione**: Gli heap possono essere implementati tramite array.

### 8. **Hash Table (Tabella hash)**
   - **Descrizione**: Una hash table memorizza coppie chiave-valore e utilizza una funzione hash per determinare l'indice di archiviazione in cui ogni valore è memorizzato.
   - **Utilizzo**: Utilizzata per la ricerca, l'inserimento e la cancellazione rapida di dati. Le hash table sono comunemente utilizzate per implementare dizionari e set.
   - **Implementazione**: Si utilizzano array con gestione delle collisioni (tramite concatenamento o indirizzamento aperto).

### 9. **Tree (Albero)**
   - **Descrizione**: Un albero è una struttura dati gerarchica costituita da nodi, in cui ogni nodo ha zero o più nodi figli. Un albero binario è un albero in cui ogni nodo ha al massimo due figli.
   - **Utilizzo**: Utilizzato per rappresentare strutture gerarchiche e implementare strutture dati come heap, alberi di ricerca binaria, AVL e B-trees.
   - **Sintassi**:
     ```c
     struct Nodo {
         int dato;
         struct Nodo* sinistro;
         struct Nodo* destro;
     };
     ```

### 10. **Graph (Grafo)**
   - **Descrizione**: Un grafo è una struttura dati costituita da nodi (o vertici) e archi (o collegamenti) che connettono i nodi.
   - **Utilizzo**: Utilizzati per rappresentare reti complesse come reti sociali, reti di trasporto o percorsi nei videogiochi.
   - **Implementazione**: I grafi possono essere implementati con matrici di adiacenza o liste di adiacenza.

---

### Esempio di utilizzo di alcune strutture dati:

- **Array**:
  ```c
  int arr[5] = {1, 2, 3, 4, 5};
  printf("Elemento 3: %d\n", arr[2]);
  ```

- **Struct**:
  ```c
  struct Persona {
      char nome[50];
      int eta;
  };
  struct Persona p1 = {"Luca", 30};
  printf("Nome: %s, Età: %d\n", p1.nome, p1.eta);
  ```

- **Lista collegata**:
  ```c
  struct Nodo {
      int dato;
      struct Nodo* successivo;
  };

  struct Nodo* testa = NULL;  // Lista vuota
  ```

Queste strutture dati formano la base per molte altre strutture e algoritmi complessi, rendendo il linguaggio C estremamente flessibile e potente nella gestione dei dati.