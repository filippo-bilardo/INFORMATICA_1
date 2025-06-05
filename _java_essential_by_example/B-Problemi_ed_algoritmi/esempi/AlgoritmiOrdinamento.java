/**
 * Esempio Completo: Algoritmi di Ordinamento
 * 
 * Questo programma implementa e confronta diversi algoritmi di ordinamento,
 * mostrando le differenze in termini di prestazioni e complessità.
 * 
 * Algoritmi implementati:
 * - Bubble Sort: O(n²)
 * - Selection Sort: O(n²) 
 * - Insertion Sort: O(n²)
 * - Merge Sort: O(n log n)
 * - Quick Sort: O(n log n) medio, O(n²) peggiore
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Arrays;
import java.util.Random;

public class AlgoritmiOrdinamento {
    
    public static void main(String[] args) {
        System.out.println("=== CONFRONTO ALGORITMI DI ORDINAMENTO ===\n");
        
        // Test con array di diverse dimensioni
        int[] sizes = {100, 1000, 5000};
        
        for (int size : sizes) {
            System.out.println("📊 Test con array di " + size + " elementi:");
            testAlgorithms(size);
            System.out.println();
        }
        
        // Dimostrazione visiva con array piccolo
        System.out.println("🔍 DIMOSTRAZIONE VISIVA (Array piccolo):");
        demonstrateVisually();
    }
    
    /**
     * Testa tutti gli algoritmi di ordinamento con un array della dimensione specificata
     */
    private static void testAlgorithms(int size) {
        // Genera array casuale
        int[] originalArray = generateRandomArray(size);
        
        // Test di ogni algoritmo
        testSingleAlgorithm("Bubble Sort", originalArray.clone(), AlgoritmiOrdinamento::bubbleSort);
        testSingleAlgorithm("Selection Sort", originalArray.clone(), AlgoritmiOrdinamento::selectionSort);
        testSingleAlgorithm("Insertion Sort", originalArray.clone(), AlgoritmiOrdinamento::insertionSort);
        testSingleAlgorithm("Merge Sort", originalArray.clone(), AlgoritmiOrdinamento::mergeSort);
        testSingleAlgorithm("Quick Sort", originalArray.clone(), AlgoritmiOrdinamento::quickSort);
    }
    
    /**
     * Testa un singolo algoritmo e misura il tempo di esecuzione
     */
    private static void testSingleAlgorithm(String name, int[] array, SortingAlgorithm algorithm) {
        long startTime = System.nanoTime();
        algorithm.sort(array);
        long endTime = System.nanoTime();
        
        double timeMs = (endTime - startTime) / 1_000_000.0;
        
        // Verifica che l'array sia ordinato correttamente
        boolean isSorted = isSorted(array);
        String status = isSorted ? "✅" : "❌";
        
        System.out.printf("  %-15s: %8.2f ms %s%n", name, timeMs, status);
    }
    
    /**
     * Genera un array di numeri casuali
     */
    private static int[] generateRandomArray(int size) {
        Random random = new Random(42); // Seed fisso per risultati riproducibili
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(1000);
        }
        return array;
    }
    
    /**
     * Verifica se un array è ordinato
     */
    private static boolean isSorted(int[] array) {
        for (int i = 1; i < array.length; i++) {
            if (array[i] < array[i - 1]) {
                return false;
            }
        }
        return true;
    }
    
    // =================== ALGORITMI DI ORDINAMENTO ===================
    
    /**
     * Bubble Sort - Ordinamento a bolle
     * Complessità: O(n²) tempo, O(1) spazio
     * 
     * Principio: Confronta elementi adiacenti e li scambia se necessario.
     * Il più grande "bolla" verso la fine ad ogni iterazione.
     */
    public static void bubbleSort(int[] array) {
        int n = array.length;
        boolean swapped;
        
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            
            // Ultimi i elementi sono già ordinati
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    // Scambia gli elementi
                    swap(array, j, j + 1);
                    swapped = true;
                }
            }
            
            // Se non ci sono stati scambi, l'array è ordinato
            if (!swapped) {
                break;
            }
        }
    }
    
    /**
     * Selection Sort - Ordinamento per selezione
     * Complessità: O(n²) tempo, O(1) spazio
     * 
     * Principio: Trova l'elemento minimo e lo mette nella posizione corretta.
     */
    public static void selectionSort(int[] array) {
        int n = array.length;
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            // Trova l'elemento minimo nel resto dell'array
            for (int j = i + 1; j < n; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            
            // Scambia l'elemento minimo con il primo non ordinato
            if (minIndex != i) {
                swap(array, i, minIndex);
            }
        }
    }
    
    /**
     * Insertion Sort - Ordinamento per inserimento
     * Complessità: O(n²) peggiore, O(n) migliore, O(1) spazio
     * 
     * Principio: Costruisce l'array ordinato un elemento alla volta.
     * Efficiente per array piccoli o quasi ordinati.
     */
    public static void insertionSort(int[] array) {
        for (int i = 1; i < array.length; i++) {
            int key = array[i];
            int j = i - 1;
            
            // Sposta elementi maggiori di key una posizione avanti
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            
            array[j + 1] = key;
        }
    }
    
    /**
     * Merge Sort - Ordinamento per fusione
     * Complessità: O(n log n) tempo, O(n) spazio
     * 
     * Principio: Divide et impera. Divide l'array a metà ricorsivamente,
     * ordina le parti e le fonde insieme.
     */
    public static void mergeSort(int[] array) {
        if (array.length <= 1) return;
        
        mergeSortRecursive(array, 0, array.length - 1);
    }
    
    private static void mergeSortRecursive(int[] array, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            // Ordina ricorsivamente le due metà
            mergeSortRecursive(array, left, mid);
            mergeSortRecursive(array, mid + 1, right);
            
            // Fonde le due metà ordinate
            merge(array, left, mid, right);
        }
    }
    
    private static void merge(int[] array, int left, int mid, int right) {
        // Crea array temporanei per le due metà
        int[] leftArray = Arrays.copyOfRange(array, left, mid + 1);
        int[] rightArray = Arrays.copyOfRange(array, mid + 1, right + 1);
        
        int i = 0, j = 0, k = left;
        
        // Fonde i due array temporanei nell'array originale
        while (i < leftArray.length && j < rightArray.length) {
            if (leftArray[i] <= rightArray[j]) {
                array[k++] = leftArray[i++];
            } else {
                array[k++] = rightArray[j++];
            }
        }
        
        // Copia elementi rimanenti
        while (i < leftArray.length) {
            array[k++] = leftArray[i++];
        }
        while (j < rightArray.length) {
            array[k++] = rightArray[j++];
        }
    }
    
    /**
     * Quick Sort - Ordinamento rapido
     * Complessità: O(n log n) medio, O(n²) peggiore, O(log n) spazio
     * 
     * Principio: Sceglie un pivot, partiziona l'array intorno al pivot,
     * ordina ricorsivamente le partizioni.
     */
    public static void quickSort(int[] array) {
        if (array.length <= 1) return;
        
        quickSortRecursive(array, 0, array.length - 1);
    }
    
    private static void quickSortRecursive(int[] array, int low, int high) {
        if (low < high) {
            // Partiziona l'array e ottieni l'indice del pivot
            int pivotIndex = partition(array, low, high);
            
            // Ordina ricorsivamente le due partizioni
            quickSortRecursive(array, low, pivotIndex - 1);
            quickSortRecursive(array, pivotIndex + 1, high);
        }
    }
    
    private static int partition(int[] array, int low, int high) {
        int pivot = array[high]; // Sceglie l'ultimo elemento come pivot
        int i = low - 1; // Indice dell'elemento più piccolo
        
        for (int j = low; j < high; j++) {
            // Se l'elemento corrente è minore o uguale al pivot
            if (array[j] <= pivot) {
                i++;
                swap(array, i, j);
            }
        }
        
        swap(array, i + 1, high);
        return i + 1;
    }
    
    /**
     * Scambia due elementi nell'array
     */
    private static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    /**
     * Dimostra visivamente come funziona il Bubble Sort con un array piccolo
     */
    private static void demonstrateVisually() {
        int[] array = {64, 34, 25, 12, 22, 11, 90};
        
        System.out.println("Array iniziale: " + Arrays.toString(array));
        System.out.println("\nPassi del Bubble Sort:");
        
        bubbleSortVisual(array);
        
        System.out.println("Array finale: " + Arrays.toString(array));
    }
    
    /**
     * Versione di Bubble Sort che mostra ogni passo
     */
    private static void bubbleSortVisual(int[] array) {
        int n = array.length;
        
        for (int i = 0; i < n - 1; i++) {
            System.out.println("\n--- Passata " + (i + 1) + " ---");
            boolean swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                System.out.printf("Confronto %d e %d: ", array[j], array[j + 1]);
                
                if (array[j] > array[j + 1]) {
                    swap(array, j, j + 1);
                    System.out.println("Scambio! → " + Arrays.toString(array));
                    swapped = true;
                } else {
                    System.out.println("Nessuno scambio");
                }
            }
            
            if (!swapped) {
                System.out.println("Array ordinato! Uscita anticipata.");
                break;
            }
        }
    }
    
    /**
     * Interfaccia funzionale per gli algoritmi di ordinamento
     */
    @FunctionalInterface
    private interface SortingAlgorithm {
        void sort(int[] array);
    }
}

/*
 * OUTPUT ATTESO:
 * 
 * === CONFRONTO ALGORITMI DI ORDINAMENTO ===
 * 
 * 📊 Test con array di 100 elementi:
 *   Bubble Sort    :     0.45 ms ✅
 *   Selection Sort :     0.12 ms ✅
 *   Insertion Sort :     0.08 ms ✅
 *   Merge Sort     :     0.15 ms ✅
 *   Quick Sort     :     0.10 ms ✅
 * 
 * 📊 Test con array di 1000 elementi:
 *   Bubble Sort    :    15.23 ms ✅
 *   Selection Sort :     3.45 ms ✅
 *   Insertion Sort :     2.12 ms ✅
 *   Merge Sort     :     1.23 ms ✅
 *   Quick Sort     :     0.89 ms ✅
 * 
 * [... e così via ...]
 */
