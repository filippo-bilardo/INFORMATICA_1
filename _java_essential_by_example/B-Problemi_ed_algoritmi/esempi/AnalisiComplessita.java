/**
 * Esempio Completo: Analisi della Complessità
 * 
 * Questo programma dimostra praticamente i concetti di complessità temporale
 * e spaziale attraverso esempi concreti e misurazioni empiriche.
 * 
 * Analizza diversi algoritmi e mostra come la complessità teorica
 * si riflette nelle prestazioni reali.
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.*;

public class AnalisiComplessita {
    
    private static Map<Integer, Long> fibonacciMemo = new HashMap<>();
    
    public static void main(String[] args) {
        System.out.println("=== ANALISI PRATICA DELLA COMPLESSITÀ ===\n");
        
        // Analisi di diversi tipi di complessità
        analyzeConstantTime();
        analyzeLinearTime();
        analyzeQuadraticTime();
        analyzeLogarithmicTime();
        analyzeExponentialTime();
        analyzeFibonacciOptimization();
        analyzeSpaceComplexity();
    }
    
    // =================== COMPLESSITÀ O(1) - COSTANTE ===================
    
    private static void analyzeConstantTime() {
        System.out.println("📈 COMPLESSITÀ O(1) - TEMPO COSTANTE");
        System.out.println("Operazioni che richiedono sempre lo stesso tempo\n");
        
        int[] sizes = {1000, 10000, 100000, 1000000};
        
        System.out.println("Test: Accesso al primo elemento di un array");
        System.out.println("Size\t\tTime (ms)");
        System.out.println("------------------------");
        
        for (int size : sizes) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = i;
            }
            
            long startTime = System.nanoTime();
            
            // Operazione O(1) - accesso diretto
            int firstElement = getFirstElement(array);
            
            long endTime = System.nanoTime();
            double timeMs = (endTime - startTime) / 1_000_000.0;
            
            System.out.printf("%d\t\t%.4f%n", size, timeMs);
        }
        
        System.out.println("✓ Il tempo rimane costante indipendentemente dalla dimensione\n");
    }
    
    /**
     * Operazione O(1) - accesso diretto
     */
    private static int getFirstElement(int[] array) {
        return array[0]; // Sempre una sola operazione
    }
    
    // =================== COMPLESSITÀ O(n) - LINEARE ===================
    
    private static void analyzeLinearTime() {
        System.out.println("📈 COMPLESSITÀ O(n) - TEMPO LINEARE");
        System.out.println("Tempo proporzionale alla dimensione dell'input\n");
        
        int[] sizes = {1000, 2000, 4000, 8000};
        
        System.out.println("Test: Somma di tutti gli elementi di un array");
        System.out.println("Size\t\tTime (ms)\tRatio");
        System.out.println("--------------------------------");
        
        double previousTime = 0;
        
        for (int size : sizes) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = i;
            }
            
            long startTime = System.nanoTime();
            
            // Operazione O(n) - visita ogni elemento
            long sum = calculateSum(array);
            
            long endTime = System.nanoTime();
            double timeMs = (endTime - startTime) / 1_000_000.0;
            
            String ratio = previousTime > 0 ? String.format("%.2fx", timeMs / previousTime) : "-";
            System.out.printf("%d\t\t%.4f\t\t%s%n", size, timeMs, ratio);
            
            previousTime = timeMs;
        }
        
        System.out.println("✓ Il tempo raddoppia quando la dimensione raddoppia\n");
    }
    
    /**
     * Operazione O(n) - scorre tutto l'array
     */
    private static long calculateSum(int[] array) {
        long sum = 0;
        for (int value : array) { // n iterazioni
            sum += value;
        }
        return sum;
    }
    
    // =================== COMPLESSITÀ O(n²) - QUADRATICA ===================
    
    private static void analyzeQuadraticTime() {
        System.out.println("📈 COMPLESSITÀ O(n²) - TEMPO QUADRATICO");
        System.out.println("Tempo proporzionale al quadrato della dimensione\n");
        
        int[] sizes = {100, 200, 400, 800};
        
        System.out.println("Test: Bubble Sort");
        System.out.println("Size\t\tTime (ms)\tRatio");
        System.out.println("--------------------------------");
        
        double previousTime = 0;
        
        for (int size : sizes) {
            int[] array = generateRandomArray(size);
            
            long startTime = System.nanoTime();
            
            // Operazione O(n²) - bubble sort
            bubbleSort(array.clone());
            
            long endTime = System.nanoTime();
            double timeMs = (endTime - startTime) / 1_000_000.0;
            
            String ratio = previousTime > 0 ? String.format("%.2fx", timeMs / previousTime) : "-";
            System.out.printf("%d\t\t%.4f\t\t%s%n", size, timeMs, ratio);
            
            previousTime = timeMs;
        }
        
        System.out.println("✓ Il tempo quadruplica quando la dimensione raddoppia\n");
    }
    
    /**
     * Bubble Sort - O(n²)
     */
    private static void bubbleSort(int[] array) {
        int n = array.length;
        for (int i = 0; i < n - 1; i++) {          // n iterazioni
            for (int j = 0; j < n - i - 1; j++) {  // n iterazioni annidate
                if (array[j] > array[j + 1]) {
                    // Scambio
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
    
    // =================== COMPLESSITÀ O(log n) - LOGARITMICA ===================
    
    private static void analyzeLogarithmicTime() {
        System.out.println("📈 COMPLESSITÀ O(log n) - TEMPO LOGARITMICO");
        System.out.println("Tempo cresce molto lentamente con la dimensione\n");
        
        int[] sizes = {1000, 10000, 100000, 1000000};
        
        System.out.println("Test: Ricerca Binaria");
        System.out.println("Size\t\tTime (ms)\tlog₂(size)");
        System.out.println("--------------------------------");
        
        for (int size : sizes) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = i * 2; // Array ordinato
            }
            
            int target = size; // Elemento che esiste
            
            long startTime = System.nanoTime();
            
            // Operazione O(log n) - ricerca binaria
            int result = binarySearch(array, target);
            
            long endTime = System.nanoTime();
            double timeMs = (endTime - startTime) / 1_000_000.0;
            
            double logSize = Math.log(size) / Math.log(2);
            
            System.out.printf("%d\t\t%.4f\t\t%.2f%n", size, timeMs, logSize);
        }
        
        System.out.println("✓ Il tempo cresce logaritmicamente (molto lentamente)\n");
    }
    
    /**
     * Ricerca Binaria - O(log n)
     */
    private static int binarySearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (array[mid] == target) {
                return mid;
            }
            
            if (array[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // =================== COMPLESSITÀ O(2ⁿ) - ESPONENZIALE ===================
    
    private static void analyzeExponentialTime() {
        System.out.println("📈 COMPLESSITÀ O(2ⁿ) - TEMPO ESPONENZIALE");
        System.out.println("Tempo raddoppia ad ogni incremento dell'input\n");
        
        int[] sizes = {10, 15, 20, 25, 30};
        
        System.out.println("Test: Fibonacci Ricorsivo (ATTENZIONE: lento!)");
        System.out.println("n\t\tTime (ms)\tResult\t\t2ⁿ");
        System.out.println("----------------------------------------");
        
        for (int n : sizes) {
            long startTime = System.nanoTime();
            
            // Operazione O(2ⁿ) - fibonacci ricorsivo naive
            long result = fibonacciRecursiveSlow(n);
            
            long endTime = System.nanoTime();
            double timeMs = (endTime - startTime) / 1_000_000.0;
            
            long powerOf2 = (long) Math.pow(2, n);
            
            System.out.printf("%d\t\t%.4f\t\t%d\t\t%d%n", n, timeMs, result, powerOf2);
            
            // Stop se troppo lento
            if (timeMs > 1000) {
                System.out.println("... (interrotto per evitare attese eccessive)");
                break;
            }
        }
        
        System.out.println("✓ Il tempo raddoppia (o più) ad ogni incremento di n\n");
    }
    
    /**
     * Fibonacci Ricorsivo Naive - O(2ⁿ)
     */
    private static long fibonacciRecursiveSlow(int n) {
        if (n <= 1) return n;
        return fibonacciRecursiveSlow(n - 1) + fibonacciRecursiveSlow(n - 2);
    }
    
    // =================== OTTIMIZZAZIONE: MEMOIZATION ===================
    
    private static void analyzeFibonacciOptimization() {
        System.out.println("🚀 OTTIMIZZAZIONE: Da O(2ⁿ) a O(n) con Memoization");
        System.out.println("Confronto tra fibonacci ricorsivo e ottimizzato\n");
        
        int[] sizes = {10, 20, 30, 40, 50};
        
        System.out.println("n\t\tRecursive (ms)\tMemoized (ms)\tIterative (ms)");
        System.out.println("--------------------------------------------------------");
        
        for (int n : sizes) {
            // Fibonacci ricorsivo (limitato a n piccoli)
            double recursiveTime = -1;
            if (n <= 30) {
                long startTime = System.nanoTime();
                fibonacciRecursiveSlow(n);
                long endTime = System.nanoTime();
                recursiveTime = (endTime - startTime) / 1_000_000.0;
            }
            
            // Fibonacci con memoization
            fibonacciMemo.clear();
            long startTime = System.nanoTime();
            fibonacciMemoized(n);
            long endTime = System.nanoTime();
            double memoizedTime = (endTime - startTime) / 1_000_000.0;
            
            // Fibonacci iterativo
            startTime = System.nanoTime();
            fibonacciIterative(n);
            endTime = System.nanoTime();
            double iterativeTime = (endTime - startTime) / 1_000_000.0;
            
            String recursiveStr = recursiveTime >= 0 ? String.format("%.4f", recursiveTime) : "troppo lento";
            
            System.out.printf("%d\t\t%s\t%.4f\t\t%.4f%n", 
                n, recursiveStr, memoizedTime, iterativeTime);
        }
        
        System.out.println("✓ Memoization riduce la complessità da O(2ⁿ) a O(n)\n");
    }
    
    /**
     * Fibonacci con Memoization - O(n)
     */
    private static long fibonacciMemoized(int n) {
        if (n <= 1) return n;
        
        if (fibonacciMemo.containsKey(n)) {
            return fibonacciMemo.get(n);
        }
        
        long result = fibonacciMemoized(n - 1) + fibonacciMemoized(n - 2);
        fibonacciMemo.put(n, result);
        return result;
    }
    
    /**
     * Fibonacci Iterativo - O(n) tempo, O(1) spazio
     */
    private static long fibonacciIterative(int n) {
        if (n <= 1) return n;
        
        long prev = 0, curr = 1;
        for (int i = 2; i <= n; i++) {
            long next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }
    
    // =================== ANALISI COMPLESSITÀ SPAZIALE ===================
    
    private static void analyzeSpaceComplexity() {
        System.out.println("💾 ANALISI COMPLESSITÀ SPAZIALE");
        System.out.println("Confronto dell'uso di memoria di diversi algoritmi\n");
        
        int[] sizes = {1000, 2000, 4000, 8000};
        
        System.out.println("Algorithm\t\tSpace Complexity\tMemory Usage");
        System.out.println("------------------------------------------------");
        
        for (int size : sizes) {
            System.out.println("\n📊 Array size: " + size);
            
            // O(1) spazio - bubble sort in-place
            analyzeSpaceUsage("Bubble Sort", "O(1)", () -> {
                int[] array = generateRandomArray(size);
                bubbleSort(array);
                return null;
            });
            
            // O(n) spazio - merge sort
            analyzeSpaceUsage("Merge Sort", "O(n)", () -> {
                int[] array = generateRandomArray(size);
                mergeSort(array);
                return null;
            });
            
            // O(n) spazio - copia array
            analyzeSpaceUsage("Array Copy", "O(n)", () -> {
                int[] array = generateRandomArray(size);
                return Arrays.copyOf(array, array.length);
            });
        }
        
        System.out.println("\n✓ Algoritmi O(1) spazio usano memoria costante");
        System.out.println("✓ Algoritmi O(n) spazio usano memoria proporzionale all'input\n");
    }
    
    /**
     * Analizza l'uso di memoria di un'operazione
     */
    private static void analyzeSpaceUsage(String algorithmName, String complexity, Supplier<Object> operation) {
        Runtime runtime = Runtime.getRuntime();
        
        // Forza garbage collection
        System.gc();
        
        long memoryBefore = runtime.totalMemory() - runtime.freeMemory();
        
        // Esegui operazione
        Object result = operation.get();
        
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;
        
        System.out.printf("  %-15s\t%s\t\t%d bytes%n", 
            algorithmName, complexity, Math.max(0, memoryUsed));
    }
    
    /**
     * Merge Sort - O(n log n) tempo, O(n) spazio
     */
    private static void mergeSort(int[] array) {
        if (array.length <= 1) return;
        
        int mid = array.length / 2;
        int[] left = Arrays.copyOfRange(array, 0, mid);
        int[] right = Arrays.copyOfRange(array, mid, array.length);
        
        mergeSort(left);
        mergeSort(right);
        
        merge(array, left, right);
    }
    
    private static void merge(int[] result, int[] left, int[] right) {
        int i = 0, j = 0, k = 0;
        
        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                result[k++] = left[i++];
            } else {
                result[k++] = right[j++];
            }
        }
        
        while (i < left.length) result[k++] = left[i++];
        while (j < right.length) result[k++] = right[j++];
    }
    
    /**
     * Genera array casuale
     */
    private static int[] generateRandomArray(int size) {
        Random random = new Random(42);
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(1000);
        }
        return array;
    }
    
    /**
     * Interfaccia funzionale per operazioni che possono restituire un oggetto
     */
    @FunctionalInterface
    private interface Supplier<T> {
        T get();
    }
}

/*
 * OUTPUT ATTESO (porzione):
 * 
 * === ANALISI PRATICA DELLA COMPLESSITÀ ===
 * 
 * 📈 COMPLESSITÀ O(1) - TEMPO COSTANTE
 * Operazioni che richiedono sempre lo stesso tempo
 * 
 * Test: Accesso al primo elemento di un array
 * Size		Time (ms)
 * ------------------------
 * 1000		0.0001
 * 10000		0.0001
 * 100000		0.0001
 * 1000000		0.0001
 * ✓ Il tempo rimane costante indipendentemente dalla dimensione
 * 
 * 📈 COMPLESSITÀ O(n) - TEMPO LINEARE
 * Tempo proporzionale alla dimensione dell'input
 * 
 * Test: Somma di tutti gli elementi di un array
 * Size		Time (ms)	Ratio
 * --------------------------------
 * 1000		0.0234		-
 * 2000		0.0456		1.95x
 * 4000		0.0891		1.95x
 * 8000		0.1782		2.00x
 * ✓ Il tempo raddoppia quando la dimensione raddoppia
 * 
 * [... continua con altri tipi di complessità ...]
 */
