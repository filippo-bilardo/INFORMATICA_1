# Complessità Computazionale

## 📚 **Obiettivi di Apprendimento**

Al termine di questa sezione, sarete in grado di:
- Comprendere i concetti di complessità temporale e spaziale
- Utilizzare la notazione asintotica (Big O, Omega, Theta)
- Analizzare la complessità di algoritmi iterativi e ricorsivi
- Ottimizzare algoritmi basandosi sull'analisi della complessità

---

## ⏱️ **Complessità Temporale**

La **complessità temporale** misura il tempo di esecuzione di un algoritmo in funzione della dimensione dell'input.

### **Definizione Formale**

Per una funzione f(n), diciamo che un algoritmo ha complessità temporale O(f(n)) se esiste una costante c > 0 e un valore n₀ tale che per tutti n ≥ n₀:

**T(n) ≤ c × f(n)**

dove T(n) è il tempo di esecuzione per input di dimensione n.

---

## 📈 **Notazioni Asintotiche**

### **1. Big O (O) - Limite Superiore**
- Rappresenta il **caso peggiore**
- f(n) = O(g(n)) significa che f cresce al massimo come g

### **2. Big Omega (Ω) - Limite Inferiore**  
- Rappresenta il **caso migliore**
- f(n) = Ω(g(n)) significa che f cresce almeno come g

### **3. Big Theta (Θ) - Limite Stretto**
- Rappresenta sia limite superiore che inferiore
- f(n) = Θ(g(n)) significa che f cresce esattamente come g

### **Esempio Pratico**

```java
/**
 * Analisi della ricerca lineare
 */
public static int linearSearch(int[] array, int target) {
    for (int i = 0; i < array.length; i++) {  // Loop eseguito al massimo n volte
        if (array[i] == target) {
            return i;  // Caso migliore: O(1)
        }
    }
    return -1;  // Caso peggiore: O(n)
}
```

**Analisi:**
- **Caso migliore**: Ω(1) - elemento trovato alla prima posizione
- **Caso peggiore**: O(n) - elemento non presente o nell'ultima posizione  
- **Caso medio**: Θ(n) - in media esaminiamo n/2 elementi

---

## 🔢 **Classificazione delle Complessità**

### **Dal Più Efficiente al Meno Efficiente:**

| Complessità | Nome | Esempio | Note |
|-------------|------|---------|------|
| O(1) | Costante | Accesso array | Ideale |
| O(log n) | Logaritmica | Ricerca binaria | Molto efficiente |
| O(n) | Lineare | Ricerca lineare | Efficiente |
| O(n log n) | Linearitmica | Merge sort | Buona |
| O(n²) | Quadratica | Bubble sort | Accettabile per n piccolo |
| O(n³) | Cubica | Moltiplicazione matrici naive | Lenta |
| O(2ⁿ) | Esponenziale | Sottoinsiemi | Molto lenta |
| O(n!) | Fattoriale | Permutazioni | Intrattabile |

### **Grafico Comparativo** (per n = 1000):

```
O(1)        : 1 operazione
O(log n)    : ~10 operazioni  
O(n)        : 1.000 operazioni
O(n log n)  : ~10.000 operazioni
O(n²)       : 1.000.000 operazioni
O(2ⁿ)       : 2^1000 operazioni (impossibile!)
```

---

## 🧮 **Calcolo della Complessità**

### **Regole Fondamentali:**

1. **Operazioni elementari**: O(1)
2. **Sequenza**: somma delle complessità
3. **Annidamento**: prodotto delle complessità  
4. **Selezione**: massimo tra le complessità

### **Esempi di Calcolo:**

```java
// Esempio 1: O(n)
public static int sum(int[] array) {
    int total = 0;                    // O(1)
    for (int i = 0; i < array.length; i++) {  // O(n) - loop n volte
        total += array[i];            // O(1) - eseguito n volte
    }
    return total;                     // O(1)
}
// Complessità totale: O(1) + O(n×1) + O(1) = O(n)
```

```java
// Esempio 2: O(n²)
public static void printMatrix(int[][] matrix) {
    for (int i = 0; i < matrix.length; i++) {        // O(n)
        for (int j = 0; j < matrix[i].length; j++) {  // O(n) - annidato
            System.out.print(matrix[i][j] + " ");     // O(1)
        }
        System.out.println();                         // O(1)
    }
}
// Complessità totale: O(n × n × 1) = O(n²)
```

```java
// Esempio 3: O(n log n)
public static void example(int[] array) {
    for (int i = 0; i < array.length; i++) {     // O(n)
        int j = array.length;
        while (j > 1) {                           // O(log n)
            j = j / 2;
            // operazioni O(1)
        }
    }
}
// Complessità totale: O(n × log n) = O(n log n)
```

---

## 🔄 **Analisi di Algoritmi Ricorsivi**

### **Metodo delle Ricorrenze**

Per algoritmi ricorsivi, usiamo le **relazioni di ricorrenza**.

#### **Esempio: Fibonacci Ricorsivo**

```java
public static long fibonacci(int n) {
    if (n <= 1) return n;                    // Caso base: O(1)
    return fibonacci(n-1) + fibonacci(n-2);  // Due chiamate ricorsive
}
```

**Relazione di ricorrenza:**
- T(n) = T(n-1) + T(n-2) + O(1)  
- T(0) = T(1) = O(1)

**Soluzione:** T(n) = O(2ⁿ) - molto inefficiente!

#### **Esempio: Ricerca Binaria Ricorsiva**

```java
public static int binarySearch(int[] array, int target, int left, int right) {
    if (left > right) return -1;             // Caso base: O(1)
    
    int mid = left + (right - left) / 2;     // O(1)
    
    if (array[mid] == target) return mid;    // O(1)
    
    if (array[mid] > target) {
        return binarySearch(array, target, left, mid - 1);     // Una chiamata
    } else {
        return binarySearch(array, target, mid + 1, right);    // Una chiamata
    }
}
```

**Relazione di ricorrenza:**
- T(n) = T(n/2) + O(1)
- T(1) = O(1)

**Soluzione:** T(n) = O(log n)

---

## 💾 **Complessità Spaziale**

La **complessità spaziale** misura la quantità di memoria aggiuntiva utilizzata dall'algoritmo.

### **Tipi di Spazio:**

1. **Spazio fisso**: variabili e costanti
2. **Spazio variabile**: strutture dati che crescono con l'input
3. **Spazio ausiliario**: spazio extra escluso l'input

### **Esempi:**

```java
// Spazio O(1) - costante
public static int findMax(int[] array) {
    int max = array[0];  // Una variabile aggiuntiva
    for (int i = 1; i < array.length; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}
```

```java
// Spazio O(n) - lineare  
public static int[] copyArray(int[] array) {
    int[] copy = new int[array.length];  // Array di dimensione n
    for (int i = 0; i < array.length; i++) {
        copy[i] = array[i];
    }
    return copy;
}
```

```java
// Spazio O(n) - ricorsione
public static long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // n chiamate nello stack
}
```

---

## ⚡ **Tecniche di Ottimizzazione**

### **1. Memoization (Programmazione Dinamica)**

```java
// Fibonacci inefficiente: O(2ⁿ)
public static long fibonacciSlow(int n) {
    if (n <= 1) return n;
    return fibonacciSlow(n-1) + fibonacciSlow(n-2);
}

// Fibonacci con memoization: O(n)
private static Map<Integer, Long> memo = new HashMap<>();

public static long fibonacciFast(int n) {
    if (n <= 1) return n;
    
    if (memo.containsKey(n)) {
        return memo.get(n);  // Risultato già calcolato
    }
    
    long result = fibonacciFast(n-1) + fibonacciFast(n-2);
    memo.put(n, result);  // Memorizza il risultato
    return result;
}
```

### **2. Ottimizzazione dello Spazio**

```java
// Fibonacci iterativo: O(n) tempo, O(1) spazio
public static long fibonacciOptimal(int n) {
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

## 📊 **Analisi Ammortizzata**

L'**analisi ammortizzata** considera il costo medio di una sequenza di operazioni.

### **Esempio: Dynamic Array (ArrayList)**

```java
// Inserimento in ArrayList
public void add(E element) {
    if (size == capacity) {
        resize();  // O(n) occasionalmente
    }
    array[size++] = element;  // O(1) normalmente
}

private void resize() {
    capacity *= 2;
    // copia tutti gli elementi: O(n)
}
```

**Analisi:**
- Operazione singola: O(1) o O(n)
- Costo ammortizzato: O(1) - il ridimensionamento è raro

---

## 🎯 **Confronto tra Algoritmi**

### **Esempio: Ordinamento**

| Algoritmo | Tempo Medio | Tempo Peggiore | Spazio | Stabile |
|-----------|-------------|----------------|--------|---------|
| Bubble Sort | O(n²) | O(n²) | O(1) | Sì |
| Selection Sort | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n²) | O(n²) | O(1) | Sì |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Sì |
| Quick Sort | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(1) | No |

### **Quando Usare Quale Algoritmo:**

- **Array piccoli (n < 50)**: Insertion Sort
- **Array medi**: Quick Sort  
- **Stabilità richiesta**: Merge Sort
- **Spazio limitato**: Heap Sort
- **Dati quasi ordinati**: Insertion Sort

---

## ✅ **Checklist di Competenze**

Dopo aver studiato questa sezione, dovreste saper:

- [ ] Definire complessità temporale e spaziale
- [ ] Utilizzare le notazioni Big O, Omega, Theta
- [ ] Calcolare la complessità di algoritmi iterativi
- [ ] Analizzare algoritmi ricorsivi con relazioni di ricorrenza
- [ ] Confrontare algoritmi basandosi sulla loro complessità
- [ ] Riconoscere opportunità di ottimizzazione
- [ ] Applicare tecniche come memoization
- [ ] Scegliere l'algoritmo appropriato per diversi scenari

---

## 🔗 **Collegamenti**

- **Lezione precedente**: [Algoritmi Fondamentali](02-algoritmi-fondamentali.md)
- **Esempi pratici**: [Analisi di Complessità](../esempi/)
- **Esercizi**: [Calcolo Complessità](../esercizi/)

---

*Questa sezione fornisce gli strumenti teorici per analizzare e confrontare l'efficienza degli algoritmi.*
