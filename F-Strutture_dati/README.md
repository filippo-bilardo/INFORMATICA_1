## F - Strutture dati
### Esercitazioni
- [ES01 - Vettori](<https://docs.google.com/presentation/d/1dkbGl5zQ0Qj9Z-gyl33H6tjckeecTT85lrA9-WZp08c>)

---
### Teoria
#### **01 Array**
- [01.1 Concetti Fondamentali sugli Array](<01.1 Concetti Fondamentali sugli Array.md>)
- [01.3 Passaggio di Array alle funzioni](<01.3 Passaggio di Array alle funzioni.md>)
- [01.2 Operazioni sui Array](<01.2 Operazioni sui Array.md>)
- [01.4 Array multidimensionali](<01.4 Array multidimensionali.md>)
- [01.5 Esempi](<01.5 Esempi.md>)
- [01.6 Esercitazioni Pratiche](<01.6 Esercitazioni Pratiche3.md>)
- [01.7 Gestione della Memoria Dinamica per Array](<01.7 Gestione della Memoria Dinamica per Array.md>)
- [01.8 Definizioni](<01.8 Definizioni.md>)

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
