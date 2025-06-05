/**
 * Esempio Completo: Algoritmi di Ricerca
 * 
 * Questo programma implementa e confronta diversi algoritmi di ricerca,
 * mostrando le differenze in termini di prestazioni e applicabilità.
 * 
 * Algoritmi implementati:
 * - Ricerca Lineare: O(n)
 * - Ricerca Binaria: O(log n)
 * - Ricerca Binaria Ricorsiva: O(log n)
 * - Ricerca con Interpolazione: O(log log n) medio
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Arrays;
import java.util.Random;

public class AlgoritmiRicerca {
    
    public static void main(String[] args) {
        System.out.println("=== CONFRONTO ALGORITMI DI RICERCA ===\n");
        
        // Test con array di diverse dimensioni
        int[] sizes = {1000, 10000, 100000};
        
        for (int size : sizes) {
            System.out.println("📊 Test con array di " + size + " elementi:");
            testSearchAlgorithms(size);
            System.out.println();
        }
        
        // Dimostrazione visiva con array piccolo
        System.out.println("🔍 DIMOSTRAZIONE VISIVA:");
        demonstrateVisually();
    }
    
    /**
     * Testa tutti gli algoritmi di ricerca
     */
    private static void testSearchAlgorithms(int size) {
        // Genera array ordinato (necessario per ricerca binaria)
        int[] array = generateSortedArray(size);
        
        // Elemento da cercare (garantito che esista)
        int target = array[size / 2];
        int targetNotExist = -1; // Elemento che non esiste
        
        System.out.println("  Ricerca elemento esistente (" + target + "):");
        testSingleSearch("Ricerca Lineare", array, target, AlgoritmiRicerca::linearSearch);
        testSingleSearch("Ricerca Binaria", array, target, AlgoritmiRicerca::binarySearch);
        testSingleSearch("Ricerca Bin. Ricorsiva", array, target, 
            (arr, val) -> binarySearchRecursive(arr, val, 0, arr.length - 1));
        testSingleSearch("Ricerca Interpolazione", array, target, AlgoritmiRicerca::interpolationSearch);
        
        System.out.println("  Ricerca elemento NON esistente (" + targetNotExist + "):");
        testSingleSearch("Ricerca Lineare", array, targetNotExist, AlgoritmiRicerca::linearSearch);
        testSingleSearch("Ricerca Binaria", array, targetNotExist, AlgoritmiRicerca::binarySearch);
    }
    
    /**
     * Testa un singolo algoritmo di ricerca
     */
    private static void testSingleSearch(String name, int[] array, int target, SearchAlgorithm algorithm) {
        long startTime = System.nanoTime();
        int result = algorithm.search(array, target);
        long endTime = System.nanoTime();
        
        double timeMs = (endTime - startTime) / 1_000_000.0;
        String status = result != -1 ? "✅ Trovato all'indice " + result : "❌ Non trovato";
        
        System.out.printf("    %-20s: %8.3f ms %s%n", name, timeMs, status);
    }
    
    /**
     * Genera un array ordinato di numeri
     */
    private static int[] generateSortedArray(int size) {
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = i * 2; // Numeri pari: 0, 2, 4, 6, ...
        }
        return array;
    }
    
    // =================== ALGORITMI DI RICERCA ===================
    
    /**
     * Ricerca Lineare (Sequential Search)
     * Complessità: O(n) tempo, O(1) spazio
     * 
     * Principio: Esamina ogni elemento sequenzialmente fino a trovare il target.
     * Funziona su array ordinati e non ordinati.
     */
    public static int linearSearch(int[] array, int target) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] == target) {
                return i; // Elemento trovato, restituisce l'indice
            }
        }
        return -1; // Elemento non trovato
    }
    
    /**
     * Ricerca Binaria Iterativa
     * Complessità: O(log n) tempo, O(1) spazio
     * 
     * Principio: Divide l'array ordinato a metà ad ogni passo,
     * scartando la metà che non può contenere il target.
     * PREREQUISITO: Array deve essere ordinato!
     */
    public static int binarySearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;
        
        while (left <= right) {
            // Calcola il punto medio evitando overflow
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
    
    /**
     * Ricerca Binaria Ricorsiva
     * Complessità: O(log n) tempo, O(log n) spazio (stack delle chiamate)
     * 
     * Stessa logica della versione iterativa ma implementata ricorsivamente.
     */
    public static int binarySearchRecursive(int[] array, int target, int left, int right) {
        // Caso base: sottoarray vuoto
        if (left > right) {
            return -1;
        }
        
        int mid = left + (right - left) / 2;
        
        if (array[mid] == target) {
            return mid; // Elemento trovato
        }
        
        if (array[mid] < target) {
            // Cerca ricorsivamente nella metà destra
            return binarySearchRecursive(array, target, mid + 1, right);
        } else {
            // Cerca ricorsivamente nella metà sinistra
            return binarySearchRecursive(array, target, left, mid - 1);
        }
    }
    
    /**
     * Ricerca per Interpolazione
     * Complessità: O(log log n) medio, O(n) peggiore
     * 
     * Principio: Stima la posizione del target basandosi sui valori.
     * Più efficiente della ricerca binaria per dati uniformemente distribuiti.
     * PREREQUISITO: Array ordinato con valori uniformemente distribuiti.
     */
    public static int interpolationSearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;
        
        while (left <= right && target >= array[left] && target <= array[right]) {
            // Se l'array ha un solo elemento
            if (left == right) {
                return array[left] == target ? left : -1;
            }
            
            // Calcola la posizione stimata usando interpolazione lineare
            int pos = left + ((target - array[left]) * (right - left)) / (array[right] - array[left]);
            
            if (array[pos] == target) {
                return pos; // Elemento trovato
            }
            
            if (array[pos] < target) {
                left = pos + 1; // Cerca nella parte destra
            } else {
                right = pos - 1; // Cerca nella parte sinistra
            }
        }
        
        return -1; // Elemento non trovato
    }
    
    /**
     * Ricerca del primo elemento maggiore o uguale al target
     * (Lower Bound - utilizzata in algoritmi avanzati)
     */
    public static int lowerBound(int[] array, int target) {
        int left = 0;
        int right = array.length;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (array[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left; // Indice del primo elemento >= target
    }
    
    /**
     * Ricerca del primo elemento maggiore del target
     * (Upper Bound - utilizzata in algoritmi avanzati)
     */
    public static int upperBound(int[] array, int target) {
        int left = 0;
        int right = array.length;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (array[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left; // Indice del primo elemento > target
    }
    
    /**
     * Ricerca in array con elementi duplicati
     * Trova tutte le occorrenze del target
     */
    public static int[] findAllOccurrences(int[] array, int target) {
        int first = lowerBound(array, target);
        int last = upperBound(array, target);
        
        if (first == last) {
            return new int[0]; // Elemento non trovato
        }
        
        // Crea array con tutti gli indici delle occorrenze
        int[] occurrences = new int[last - first];
        for (int i = 0; i < occurrences.length; i++) {
            occurrences[i] = first + i;
        }
        
        return occurrences;
    }
    
    /**
     * Dimostra visivamente come funziona la ricerca binaria
     */
    private static void demonstrateVisually() {
        int[] array = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
        int target = 23;
        
        System.out.println("Array: " + Arrays.toString(array));
        System.out.println("Ricerca di: " + target);
        System.out.println("\nPassi della Ricerca Binaria:");
        
        binarySearchVisual(array, target);
        
        System.out.println("\n--- Test con elementi duplicati ---");
        int[] arrayWithDuplicates = {1, 2, 2, 2, 3, 4, 4, 5, 6, 7};
        int duplicateTarget = 2;
        
        System.out.println("Array: " + Arrays.toString(arrayWithDuplicates));
        System.out.println("Ricerca di: " + duplicateTarget);
        
        int[] allOccurrences = findAllOccurrences(arrayWithDuplicates, duplicateTarget);
        System.out.println("Tutte le occorrenze agli indici: " + Arrays.toString(allOccurrences));
    }
    
    /**
     * Versione di ricerca binaria che mostra ogni passo
     */
    private static void binarySearchVisual(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;
        int step = 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            System.out.printf("Passo %d: left=%d, right=%d, mid=%d (valore=%d)%n", 
                step, left, right, mid, array[mid]);
            
            if (array[mid] == target) {
                System.out.println("🎯 Elemento trovato all'indice " + mid + "!");
                return;
            }
            
            if (array[mid] < target) {
                System.out.println("  " + array[mid] + " < " + target + " → cerca a destra");
                left = mid + 1;
            } else {
                System.out.println("  " + array[mid] + " > " + target + " → cerca a sinistra");
                right = mid - 1;
            }
            
            step++;
        }
        
        System.out.println("❌ Elemento non trovato");
    }
    
    /**
     * Interfaccia funzionale per gli algoritmi di ricerca
     */
    @FunctionalInterface
    private interface SearchAlgorithm {
        int search(int[] array, int target);
    }
}

/*
 * OUTPUT ATTESO:
 * 
 * === CONFRONTO ALGORITMI DI RICERCA ===
 * 
 * 📊 Test con array di 1000 elementi:
 *   Ricerca elemento esistente (1000):
 *     Ricerca Lineare    :    0.015 ms ✅ Trovato all'indice 500
 *     Ricerca Binaria    :    0.002 ms ✅ Trovato all'indice 500
 *     Ricerca Bin. Ricorsiva:  0.003 ms ✅ Trovato all'indice 500
 *     Ricerca Interpolazione:  0.001 ms ✅ Trovato all'indice 500
 * 
 *   Ricerca elemento NON esistente (-1):
 *     Ricerca Lineare    :    0.025 ms ❌ Non trovato
 *     Ricerca Binaria    :    0.002 ms ❌ Non trovato
 * 
 * [... continua con dimensioni maggiori ...]
 */
