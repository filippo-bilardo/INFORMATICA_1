## F - Strutture dati
### Esercitazioni
- [ES01 - Vettori](<https://docs.google.com/presentation/d/1dkbGl5zQ0Qj9Z-gyl33H6tjckeecTT85lrA9-WZp08c>)

---
### Teoria
#### **01 Array**
- [01.1 Gli array monodimensionali in C](<01.1 Gli array monodimensionali in C.md>)
- [01.2 Gli array monodimensionali in C](<01.1 Gli array monodimensionali in C.md>)
- [01.1 Esercitazioni pratiche](<01.1 Esercitazioni pratiche.md>)
- [01.2 Gli array monodimensionali, Differenze tra C e C++](<01.2 Gli array monodimensionali, Differenze tra C e C++.md>)
- [01.3 Array Multidimensionali in C](<01.3 Array Multidimensionali in C.md>)
- [01.1 Concetti Fondamentali sugli Array](<01.1 Concetti Fondamentali sugli Array.md>)
- [01.3 Passaggio di Array alle funzioni in C](<01.3 Passaggio di Array alle funzioni in C.md>)
- [01.2 Operazioni sui Array](<01.2 Operazioni sui Array.md>)
- [01.4 Array multidimensionali](<01.4 Array multidimensionali.md>)
- [01.5 Esempi](<01.5 Esempi.md>)
- [01.6 Esercitazioni Pratiche](<01.6 Esercitazioni Pratiche3.md>)
- [01.7 Gestione della Memoria Dinamica per Array](<01.7 Gestione della Memoria Dinamica per Array.md>)
- [01.8 Definizioni](<01.8 Definizioni.md>)
- [01.9 Relazione tra array e puntatori in C](<01.9 Relazione tra array e puntatori in C.md>)

#### **02 Struct**
- [02.1 Struct](<02.1 Struct.md>)

#### **03 Union**
- [03.1 Union](<03.1 Union.md>)

#### **04 Enum**

---

F.2. Puntatori
  - Introduzione ai puntatori e loro utilizzo.
  - Puntatori e array.
  - Puntatori a funzioni.
  - Allocazione dinamica della memoria (`malloc`, `free`).
  - Esercizi pratici sui puntatori.

F.3. Stringhe
  - Manipolazione di stringhe con librerie standard (`<string.h>`).
  - Operazioni comuni: concatenazione, ricerca, lunghezza.
  - Esercitazioni pratiche con stringhe.

F.4. Strutture
  - Definizione e utilizzo delle strutture.
  - Array di strutture e strutture annidate.
  - Unioni e enumerazioni.
  - Esercitazioni con dati complessi.

---
[Corso INF1](../README.md)

---
## Array 
### **Sezione 3: Array Multidimensionali**
- **Che cos'è un array multidimensionale?**
  - Definizione e utilizzo di array bidimensionali e tridimensionali.
  - Rappresentazione di matrici e cubi.
- **Dichiarazione e inizializzazione:**
  - Sintassi per dichiarare array multidimensionali.
  - Inizializzazione riga per riga o colonna per colonna.
- **Accesso agli elementi:**
  - Utilizzo di indici multipli per accedere agli elementi.
  - Iterazione su matrici e cubi.
- **Esempio pratico:** Implementare una matrice quadrata e calcolarne la traccia (somma degli elementi sulla diagonale principale).

### **Sezione 5: Puntatori e Array**
- **Relazione tra puntatori e array:**
  - Come un array viene trattato come un puntatore al primo elemento.
  - Utilizzo di puntatori per iterare sugli elementi di un array.
- **Passaggio di array a funzioni:**
  - Passaggio di array tramite puntatori.
  - Dimensione dell'array come parametro aggiuntivo.
- **Puntatori a matrici:**
  - Dichiarazione e utilizzo di puntatori a matrici.
  - Accesso agli elementi tramite puntatori.
- **Esempio pratico:** Scrivere una funzione che accetta un array di stringhe e restituisce la più lunga.

### **Sezione 6: Innovazioni delle Ultime Versioni di C++**
- **Inizializzazione con `{}` (C++11):**
  - Utilizzo di liste di inizializzazione uniforme per array.
  - Esempio:
    ```cpp
    int arr[] = {1, 2, 3, 4, 5};
    ```
- **Range-based for loop (C++11):**
  - Iterazione semplificata su array usando `for (auto elemento : array)`.
  - Esempio:
    ```cpp
    for (auto num : arr) {
        std::cout << num << " ";
    }
    ```
- **`std::array` (C++11):**
  - Introduzione della classe `std::array` come alternativa sicura agli array C-style.
  - Vantaggi: dimensione nota a compile-time, interoperabilità con STL.
  - Esempio:
    ```cpp
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    ```
- **`std::span` (C++20):**
  - Introduzione di `std::span` per rappresentare viste leggere su array o contenitori.
  - Utilizzo per passare array a funzioni senza copiarli.
  - Esempio:
    ```cpp
    void print_span(std::span<int> span) {
        for (auto num : span) {
            std::cout << num << " ";
        }
    }

    int main() {
        int arr[] = {1, 2, 3, 4, 5};
        print_span(arr); // Passa una vista sull'array
    }
    ```
- **Constexpr arrays (C++11 e successive):**
  - Creazione di array a tempo di compilazione con `constexpr`.
  - Esempio:
    ```cpp
    constexpr int arr[] = {1, 2, 3, 4, 5};
    static_assert(arr[2] == 3, "Errore nella costante!");
    ```

- **Designated initializers (C23):**
  - Introduzione di initializer designati per array in C23 (non disponibili in C++).
  - Esempio:
    ```c
    int arr[5] = {[2] = 42, [4] = 99}; // Inizializza solo gli elementi specificati
    ```

### **Sezione 7: Tecniche Avanzate**

- **Array di strutture:**
  - Creazione di array contenenti oggetti complessi (es. strutture o classi).
  - Accesso ai membri delle strutture all'interno dell'array.

- **Algoritmi STL per array:**
  - Funzioni utili come `std::copy`, `std::transform`, `std::accumulate`.
  - Filtraggio e trasformazione di array con lambda.

- **Esempio pratico:** Usare `std::transform` per applicare una funzione a tutti gli elementi di un array.

### **Sezione 8: Progetti Pratici**

- **Progetto 1: Elaborazione di voti:**
  - Creare un programma che legga un array di voti e calcoli la media, il voto minimo e il voto massimo.

- **Progetto 2: Matrice sparsa:**
  - Implementare una matrice sparsa utilizzando un array dinamico per memorizzare solo gli elementi non nulli.

- **Progetto 3: Simulazione di un quiz:**
  - Creare un array di domande e risposte corrette. Chiedere all'utente di rispondere e calcolare il punteggio finale.

- **Progetto 4: Utilizzo di `std::span`:**
  - Scrivere una funzione generica che accetti un `std::span` e calcoli la somma degli elementi.

### **Esercizi**

1. Scrivere un programma che inverta gli elementi di un array utilizzando un ciclo `for` e `std::swap`.
2. Implementare una funzione `constexpr` che controlli se un array contiene duplicati.
3. Creare un array dinamico di dimensione specificata dall'utente e popolarlo con numeri casuali. Utilizzare `std::vector` o `std::unique_ptr`.
4. Utilizzare `std::span` per passare una vista su un array a una funzione che calcola la media dei valori.

---
## Array 2
---
### **Parte 1: Array in C**  

### **Introduzione**  
- Perché gli array sono fondamentali in C  
- Breve storia degli array nel linguaggio C  
- Convenzioni utilizzate nel libro  

---

### [01 Fondamenti degli Array](<01 Fondamenti degli Array.md>)

### **Capitolo 2: Array Multidimensionali**  
2.1 Array 2D (matrici)  
2.2 Array 3D e oltre  
2.3 Inizializzazione e accesso a elementi multidimensionali  
- **Esempi**: Matrici di numeri, immagini in scala di grigi  
- **Best Practice**: Evitare sprechi di memoria con array "sparse"  
- **Tip & Tricks**: Rappresentazione a righe vs. colonne  
- **Domande di autovalutazione**  
- **Esercizi**: Calcolo della trasposta di una matrice, ricerca in array 3D  

---

### **Capitolo 3: Array e Puntatori**  
3.1 Relazione tra array e puntatori in C  
3.2 Aritmetica dei puntatori per navigare gli array  
3.3 Array come parametri di funzioni  
- **Esempi**: Passaggio di array a funzioni, puntatori a array multidimensionali  
- **Best Practice**: Usare `const` per proteggere gli array in input  
- **Tip & Tricks**: Simulare array dinamici con puntatori  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare `strlen` con puntatori, copia di array  

---

### **Capitolo 4: Operazioni Comuni sugli Array**  
4.1 Ricerca lineare e binaria  
4.2 Ordinamento (bubble sort, selection sort, qsort)  
4.3 Manipolazione: inserimento, cancellazione, fusione  
- **Esempi**: Codice per algoritmi di ordinamento  
- **Best Practice**: Ottimizzare la ricerca con indici ordinati  
- **Tip & Tricks**: Usare la libreria `<stdlib.h>` per `qsort`  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare ricerca binaria, ordinare array di strutture  

---

### **Capitolo 5: Array Dinamici e Allocazione di Memoria**  
5.1 `malloc`, `calloc`, `realloc`, `free`  
5.2 Array dinamici: vantaggi e svantaggi  
5.3 Gestione degli errori di allocazione  
- **Esempi**: Creare un array dinamico di dimensione variabile  
- **Best Practice**: Sempre controllare il risultato di `malloc`  
- **Tip & Tricks**: Ridimensionare array in modo efficiente  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare un vettore dinamico (simile a `std::vector`)  

---

### **Capitolo 6: Stringhe come Array di Caratteri**  
6.1 Stringhe in C: null-termination  
6.2 Funzioni standard: `strcpy`, `strlen`, `strcat`, `strcmp`  
6.3 Array di stringhe (es: menu, elenchi)  
- **Esempi**: Copia sicura di stringhe con buffer overflow prevention  
- **Best Practice**: Usare `strncpy` al posto di `strcpy`  
- **Tip & Tricks**: Convertire stringhe in numeri con `atoi`/`strtol`  
- **Domande di autovalutazione**  
- **Esercizi**: Contare le vocali in una stringa, invertire parole  

---

### **Capitolo 7: Array di Struct e Struct con Array**  
7.1 Array di strutture (es: database di studenti)  
7.2 Struct contenenti array (es: buffer circolari)  
7.3 Serializzazione di dati complessi  
- **Esempi**: Gestione di un inventario con array di struct  
- **Best Practice**: Allineamento della memoria e padding  
- **Tip & Tricks**: Usare typedef per semplificare le dichiarazioni  
- **Domande di autovalutazione**  
- **Esercizi**: Creare un registro di voti, implementare una coda  

---

### **Capitolo 8: Casi d'Uso Avanzati e Real-World**  
8.1 Array in algoritmi di crittografia  
8.2 Array per elaborazione di immagini (es: filtri)  
8.3 Array in giochi (es: griglie, mappe)  
- **Esempi**: Applicare un filtro gaussiano a una matrice di pixel  
- **Best Practice**: Ottimizzare l'accesso alla memoria per prestazioni  
- **Tip & Tricks**: Usare array per memoization in ricorsione  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare un semplice motore 2D  

---

### **Capitolo 9: Errori Comuni e Debugging**  
9.1 Buffer overflow e underflow  
9.2 Accesso a indici fuori range  
9.3 Memory leak e dangling pointers  
- **Esempi**: Cattive pratiche e loro conseguenze  
- **Best Practice**: Usare strumenti come Valgrind  
- **Tip & Tricks**: Validare gli indici in fase di sviluppo  
- **Domande di autovalutazione**  
- **Esercizi**: Correggere codici con errori di memoria  

---

### **Appendice A: Riferimenti Utili**  
- Sintassi completa degli array in C  
- Funzioni standard della libreria `<string.h>`  
- Tabella di confronto tra array statici e dinamici  

---

### **Appendice B: Soluzioni alle Domande di Autovalutazione**  
- Risposte dettagliate per ogni capitolo  

---

### **Appendice C: Progetti Completi**  
- Progetto 1: Calcolatrice matriciale  
- Progetto 2: Gioco del tris (Tic-Tac-Toe) con array 2D  
- Progetto 3: Analizzatore di dati CSV  

---

### **Parte 2: Array in C++**  

#### **Capitolo 10: Introduzione agli Array in C++**  
10.1 Differenze tra array in C e C++  
10.2 Array built-in vs. oggetti STL  
10.3 Introduzione a `std::array` (header `<array>`)  
- **Esempi**: Dichiarazione e utilizzo di `std::array`  
- **Best Practice**: Preferire `std::array` agli array raw in C++  
- **Tip & Tricks**: Accesso con `at()` per controlli di bounds  
- **Domande di autovalutazione**  
- **Esercizi**: Convertire array C in `std::array`  

---

#### **Capitolo 11: Vettori Dinamici con `std::vector`**  
11.1 Il contenitore `std::vector` (header `<vector>`)  
11.2 Metodi chiave: `push_back()`, `resize()`, `capacity()`  
11.3 Ottimizzazione della memoria e ridimensionamento automatico  
- **Esempi**: Creare un vettore dinamico di oggetti  
- **Best Practice**: Usare `reserve()` per evitare reallocazioni frequenti  
- **Tip & Tricks**: Iterare con range-based for loop (`for (auto x : v)`)  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare un buffer circolare con `std::vector`  

---

#### **Capitolo 12: Iteratori e Algoritmi STL**  
12.1 Iteratori per navigare array e container  
12.2 Algoritmi STL: `sort()`, `find()`, `accumulate()`  
12.3 Lambda expressions per operazioni custom  
- **Esempi**: Ordinare un array con `std::sort` e criteri personalizzati  
- **Best Practice**: Preferire algoritmi STL ai cicli manuali  
- **Tip & Tricks**: Usare `std::begin()`/`std::end()` con array raw  
- **Domande di autovalutazione**  
- **Esercizi**: Filtrare elementi con `std::copy_if`  

---

#### **Capitolo 13: Array Multidimensionali in C++**  
13.1 `std::array` e `std::vector` per matrici  
13.2 Array di array vs. classi personalizzate per matrici  
13.3 Librerie esterne (es: Eigen per algebra lineare)  
- **Esempi**: Matrice dinamica con `std::vector<std::vector<int>>`  
- **Best Practice**: Evitare array multidimensionali raw in C++  
- **Tip & Tricks**: Usare `typedef` o `using` per semplificare dichiarazioni  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare una classe `Matrix` con operatori sovraccaricati  

---

#### **Capitolo 14: Gestione Avanzata della Memoria**  
14.1 `new`/`delete` vs. allocazione automatica  
14.2 Smart pointers (`std::unique_ptr`, `std::shared_ptr`) per array  
14.3 RAII e gestione automatica delle risorse  
- **Esempi**: Array dinamico con `std::unique_ptr<int[]>`  
- **Best Practice**: Evitare `new[]`/`delete[]` in favore di container STL  
- **Tip & Tricks**: Usare `std::make_unique` per array (C++14+)  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare una classe wrapper per array con RAII  

---

#### **Capitolo 15: Stringhe in C++ (`std::string` e `std::string_view`)**  
15.1 `std::string` vs. array di char  
15.2 Operazioni avanzate: concatenazione, ricerca, sottostringhe  
15.3 `std::string_view` per ottimizzare le prestazioni (C++17+)  
- **Esempi**: Parsing di stringhe con `find()` e `substr()`  
- **Best Practice**: Preferire `std::string_view` per parametri di sola lettura  
- **Tip & Tricks**: Usare `std::stringstream` per la serializzazione  
- **Domande di autovalutazione**  
- **Esercizi**: Contare le parole in una stringa con algoritmi STL  

---

#### **Capitolo 16: Array e Programmazione Generica (Template)**  
16.1 Template per funzioni e classi che gestiscono array  
16.2 Specializzazione di template per array di tipi specifici  
16.3 Concetti (C++20) per vincolare i tipi  
- **Esempi**: Funzione template per stampare array di qualsiasi tipo  
- **Best Practice**: Usare `std::span` (C++20) per passare array generici  
- **Tip & Tricks**: Combinare `std::array` e template per codice riutilizzabile  
- **Domande di autovalutazione**  
- **Esercizi**: Implementare un algoritmo di ordinamento generico  

---

#### **Capitolo 17: Casi d'Uso Moderni in C++**  
17.1 Array in applicazioni real-time e giochi (es: buffer di rendering)  
17.2 Array per elaborazione dati scientifici (es: tensori con Eigen)  
17.3 Serializzazione con librerie moderne (es: JSON, Boost.Serialization)  
- **Esempi**: Implementare un semplice motore 3D con array di vertici  
- **Best Practice**: Usare `noexcept` e `constexpr` per ottimizzare  
- **Tip & Tricks**: Integrare `std::array` con librerie esterne  
- **Domande di autovalutazione**  
- **Esercizi**: Creare un'applicazione CLI per analisi dati  

---

### **Appendice D: Confronto C vs. C++**  
- Gestione degli array nei due linguaggi  
- Vantaggi del C++ per progetti moderni  

---

### **Appendice E: Progetti Completi in C++**  
- Progetto 1: Applicazione di machine learning leggero con array  
- Progetto 2: Gioco di strategia con matrici dinamiche  
- Progetto 3: Analizzatore di dati con `std::vector` e algoritmi STL  

---
