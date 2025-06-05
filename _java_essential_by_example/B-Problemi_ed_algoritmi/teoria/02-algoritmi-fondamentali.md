# Algoritmi Fondamentali

## 📚 **Obiettivi di Apprendimento**

Al termine di questa sezione, sarete in grado di:
- Comprendere cos'è un algoritmo e le sue proprietà
- Identificare algoritmi fondamentali di ordinamento e ricerca
- Analizzare la complessità temporale e spaziale
- Implementare algoritmi di base in Java

---

## 🔍 **Definizione di Algoritmo**

Un **algoritmo** è una sequenza finita di istruzioni, non ambigue ed eseguibili, che risolve un problema computazionale in un tempo finito.

### **Proprietà di un Algoritmo:**

1. **Finitezza**: deve terminare dopo un numero finito di passi
2. **Definitezza**: ogni passo deve essere precisamente definito
3. **Input**: deve avere zero o più input
4. **Output**: deve produrre almeno un output
5. **Efficacia**: ogni operazione deve essere eseguibile

---

## 🔄 **Algoritmi di Ordinamento**

### **1. Bubble Sort (Ordinamento a Bolle)**

**Principio**: Confronta elementi adiacenti e li scambia se sono nell'ordine sbagliato.

```java
/**
 * Implementazione del Bubble Sort
 * Complessità: O(n²)
 */
public static void bubbleSort(int[] array) {
    int n = array.length;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Scambia elementi
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
```

**Caratteristiche:**
- **Complessità temporale**: O(n²) nel caso peggiore
- **Complessità spaziale**: O(1)
- **Stabile**: mantiene l'ordine relativo di elementi uguali

### **2. Selection Sort (Ordinamento per Selezione)**

**Principio**: Trova l'elemento minimo e lo sposta in posizione corretta.

```java
/**
 * Implementazione del Selection Sort
 * Complessità: O(n²)
 */
public static void selectionSort(int[] array) {
    int n = array.length;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // Scambia l'elemento minimo con il primo
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}
```

### **3. Insertion Sort (Ordinamento per Inserimento)**

**Principio**: Costruisce l'array ordinato un elemento alla volta.

```java
/**
 * Implementazione dell'Insertion Sort
 * Complessità: O(n²) caso peggiore, O(n) caso migliore
 */
public static void insertionSort(int[] array) {
    for (int i = 1; i < array.length; i++) {
        int key = array[i];
        int j = i - 1;
        
        // Sposta gli elementi maggiori di key
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}
```

---

## 🔍 **Algoritmi di Ricerca**

### **1. Ricerca Lineare (Linear Search)**

**Principio**: Controlla ogni elemento sequenzialmente.

```java
/**
 * Ricerca lineare in un array
 * Complessità: O(n)
 */
public static int linearSearch(int[] array, int target) {
    for (int i = 0; i < array.length; i++) {
        if (array[i] == target) {
            return i; // Elemento trovato, restituisce indice
        }
    }
    return -1; // Elemento non trovato
}
```

### **2. Ricerca Binaria (Binary Search)**

**Principio**: Divide l'array ordinato a metà ad ogni passo.

```java
/**
 * Ricerca binaria in un array ordinato
 * Complessità: O(log n)
 */
public static int binarySearch(int[] array, int target) {
    int left = 0;
    int right = array.length - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (array[mid] == target) {
            return mid; // Elemento trovato
        }
        
        if (array[mid] < target) {
            left = mid + 1; // Cerca nella metà destra
        } else {
            right = mid - 1; // Cerca nella metà sinistra
        }
    }
    
    return -1; // Elemento non trovato
}
```

---

## 📊 **Analisi della Complessità**

### **Notazione Big O**

La notazione Big O descrive il comportamento asintotico di un algoritmo:

| Notazione | Nome | Descrizione | Esempio |
|-----------|------|-------------|---------|
| O(1) | Costante | Tempo fisso | Accesso array |
| O(log n) | Logaritmica | Divide per 2 | Ricerca binaria |
| O(n) | Lineare | Proporzionale a n | Ricerca lineare |
| O(n log n) | Linearitmica | n volte log n | Merge sort |
| O(n²) | Quadratica | n volte n | Bubble sort |
| O(2ⁿ) | Esponenziale | 2 elevato a n | Alcuni algoritmi ricorsivi |

### **Esempio di Analisi**

```java
// O(1) - Tempo costante
public static int getFirst(int[] array) {
    return array[0]; // Una sola operazione
}

// O(n) - Tempo lineare  
public static int sum(int[] array) {
    int total = 0;
    for (int num : array) { // n iterazioni
        total += num;
    }
    return total;
}

// O(n²) - Tempo quadratico
public static void printPairs(int[] array) {
    for (int i = 0; i < array.length; i++) {     // n iterazioni
        for (int j = 0; j < array.length; j++) { // n iterazioni per ogni i
            System.out.println(array[i] + ", " + array[j]);
        }
    }
}
```

---

## 🧮 **Algoritmi Matematici Fondamentali**

### **1. Calcolo del Massimo Comun Divisore (MCD)**

```java
/**
 * Algoritmo di Euclide per il calcolo del MCD
 * Complessità: O(log min(a,b))
 */
public static int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### **2. Verifica Numero Primo**

```java
/**
 * Verifica se un numero è primo
 * Complessità: O(√n)
 */
public static boolean isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
```

### **3. Sequenza di Fibonacci**

```java
/**
 * Calcolo iterativo del numero di Fibonacci
 * Complessità: O(n)
 */
public static long fibonacci(int n) {
    if (n <= 1) return n;
    
    long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

---

## 🎯 **Strategie Algoritmiche**

### **1. Divide et Impera (Divide and Conquer)**
- Dividere il problema in sottoproblemi più piccoli
- Risolvere ricorsivamente i sottoproblemi  
- Combinare le soluzioni

**Esempio**: Merge Sort, Quick Sort

### **2. Programmazione Dinamica**
- Risolve problemi ottimizzando sottoproblemi sovrapposti
- Memorizza i risultati per evitare ricalcoli

**Esempio**: Fibonacci con memoization

### **3. Algoritmi Greedy (Avidi)**
- Fa sempre la scelta localmente ottima
- Non garantisce sempre la soluzione globale ottima

**Esempio**: Cambio monete con denominazioni standard

---

## ✅ **Checklist di Competenze**

Dopo aver studiato questa sezione, dovreste saper:

- [ ] Definire cos'è un algoritmo e le sue proprietà
- [ ] Implementare algoritmi di ordinamento base (bubble, selection, insertion)
- [ ] Implementare algoritmi di ricerca (lineare, binaria)
- [ ] Analizzare la complessità temporale di un algoritmo
- [ ] Riconoscere la notazione Big O comune
- [ ] Implementare algoritmi matematici fondamentali
- [ ] Scegliere l'algoritmo appropriato per un problema dato

---

## 🔗 **Approfondimenti**

- **Prossima lezione**: [Complessità Computazionale](03-complessita-computazionale.md)
- **Esempi pratici**: [Esempi di Algoritmi](../esempi/)
- **Esercizi**: [Esercizi su Algoritmi](../esercizi/)

---

*Questa sezione fornisce le basi teoriche necessarie per comprendere e implementare algoritmi fondamentali in Java.*
