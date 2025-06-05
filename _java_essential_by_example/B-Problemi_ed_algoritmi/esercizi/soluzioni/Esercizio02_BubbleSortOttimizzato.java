/**
 * SOLUZIONE - Esercizio B.2: Bubble Sort Ottimizzato
 * 
 * Questo esercizio migliora l'algoritmo Bubble Sort classico con:
 * - Ottimizzazione per terminazione anticipata
 * - Conteggio degli scambi effettuati
 * - Visualizzazione dei passi dell'ordinamento
 * - Analisi delle prestazioni su diversi tipi di input
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Arrays;
import java.util.Random;

public class Esercizio02_BubbleSortOttimizzato {
    
    /**
     * Classe per contenere le statistiche dell'ordinamento
     */
    public static class SortingStats {
        public int comparisons = 0;
        public int swaps = 0;
        public int iterations = 0;
        public long timeNanos = 0;
        
        @Override
        public String toString() {
            return String.format("Confronti: %d, Scambi: %d, Iterazioni: %d, Tempo: %.3f ms", 
                comparisons, swaps, iterations, timeNanos / 1_000_000.0);
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== ESERCIZIO B.2: BUBBLE SORT OTTIMIZZATO ===\n");
        
        // Dimostrazione visiva con array piccolo
        demonstrateVisual();
        
        // Test di performance su diversi tipi di array
        performanceAnalysis();
        
        // Confronto con bubble sort classico
        compareVersions();
    }
    
    /**
     * BUBBLE SORT OTTIMIZZATO
     * 
     * Ottimizzazioni implementate:
     * 1. Terminazione anticipata se array già ordinato
     * 2. Riduzione dell'area di controllo ad ogni iterazione
     * 3. Raccolta di statistiche dettagliate
     */
    public static SortingStats bubbleSortOptimized(int[] array, boolean verbose) {
        SortingStats stats = new SortingStats();
        long startTime = System.nanoTime();
        
        int n = array.length;
        boolean swapped;
        
        if (verbose) {
            System.out.println("Array iniziale: " + Arrays.toString(array));
            System.out.println();
        }
        
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            stats.iterations++;
            
            if (verbose) {
                System.out.println("--- Iterazione " + (i + 1) + " ---");
                System.out.println("Controllo elementi da 0 a " + (n - i - 2));
            }
            
            // Controlla solo la parte non ancora ordinata
            for (int j = 0; j < n - i - 1; j++) {
                stats.comparisons++;
                
                if (verbose) {
                    System.out.printf("Confronto %d e %d: ", array[j], array[j + 1]);
                }
                
                if (array[j] > array[j + 1]) {
                    // Scambia elementi
                    swap(array, j, j + 1);
                    stats.swaps++;
                    swapped = true;
                    
                    if (verbose) {
                        System.out.println("SCAMBIO → " + Arrays.toString(array));
                    }
                } else {
                    if (verbose) {
                        System.out.println("OK");
                    }
                }
            }
            
            if (verbose) {
                System.out.println("Fine iterazione: " + Arrays.toString(array));
                System.out.println("Elemento " + array[n - i - 1] + " in posizione finale");
                System.out.println();
            }
            
            // OTTIMIZZAZIONE: Se non ci sono stati scambi, l'array è ordinato
            if (!swapped) {
                if (verbose) {
                    System.out.println("🎯 OTTIMIZZAZIONE: Nessuno scambio → Array ordinato!");
                    System.out.println("Terminazione anticipata all'iterazione " + (i + 1));
                }
                break;
            }
        }
        
        stats.timeNanos = System.nanoTime() - startTime;
        
        if (verbose) {
            System.out.println("\n✅ Ordinamento completato!");
            System.out.println("Array finale: " + Arrays.toString(array));
            System.out.println("Statistiche: " + stats);
        }
        
        return stats;
    }
    
    /**
     * BUBBLE SORT CLASSICO (per confronto)
     * Versione senza ottimizzazioni
     */
    public static SortingStats bubbleSortClassic(int[] array) {
        SortingStats stats = new SortingStats();
        long startTime = System.nanoTime();
        
        int n = array.length;
        
        // Sempre n-1 iterazioni, senza controllo di terminazione anticipata
        for (int i = 0; i < n - 1; i++) {
            stats.iterations++;
            
            for (int j = 0; j < n - 1; j++) { // Controlla sempre tutto l'array
                stats.comparisons++;
                
                if (array[j] > array[j + 1]) {
                    swap(array, j, j + 1);
                    stats.swaps++;
                }
            }
        }
        
        stats.timeNanos = System.nanoTime() - startTime;
        return stats;
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
     * Dimostrazione visiva del funzionamento
     */
    private static void demonstrateVisual() {
        System.out.println("🔍 DIMOSTRAZIONE VISIVA\n");
        
        int[] array = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("Vediamo come lavora Bubble Sort ottimizzato:");
        System.out.println();
        
        bubbleSortOptimized(array.clone(), true);
        System.out.println("\n" + "=".repeat(60) + "\n");
    }
    
    /**
     * Analisi delle prestazioni su diversi tipi di array
     */
    private static void performanceAnalysis() {
        System.out.println("📊 ANALISI PRESTAZIONI SU DIVERSI TIPI DI ARRAY\n");
        
        int size = 1000;
        
        // Array già ordinato
        int[] sortedArray = generateSortedArray(size);
        System.out.println("📈 Array GIÀ ORDINATO (" + size + " elementi):");
        SortingStats sortedStats = bubbleSortOptimized(sortedArray.clone(), false);
        System.out.println("   " + sortedStats);
        System.out.println("   🎯 Beneficio ottimizzazione: Terminazione dopo 1 iterazione!\n");
        
        // Array ordinato al contrario
        int[] reversedArray = generateReversedArray(size);
        System.out.println("📉 Array ORDINATO AL CONTRARIO (" + size + " elementi):");
        SortingStats reversedStats = bubbleSortOptimized(reversedArray.clone(), false);
        System.out.println("   " + reversedStats);
        System.out.println("   ⚠️  Caso peggiore: Massimo numero di confronti e scambi\n");
        
        // Array casuale
        int[] randomArray = generateRandomArray(size);
        System.out.println("🎲 Array CASUALE (" + size + " elementi):");
        SortingStats randomStats = bubbleSortOptimized(randomArray.clone(), false);
        System.out.println("   " + randomStats);
        System.out.println("   📊 Caso medio: Prestazioni intermedie\n");
        
        // Array quasi ordinato
        int[] nearlyOrderedArray = generateNearlyOrderedArray(size);
        System.out.println("🔄 Array QUASI ORDINATO (" + size + " elementi):");
        SortingStats nearlyStats = bubbleSortOptimized(nearlyOrderedArray.clone(), false);
        System.out.println("   " + nearlyStats);
        System.out.println("   ✨ Ottimizzazione efficace: Poche iterazioni necessarie\n");
    }
    
    /**
     * Confronto tra versione ottimizzata e classica
     */
    private static void compareVersions() {
        System.out.println("⚔️  CONFRONTO: OTTIMIZZATO vs CLASSICO\n");
        
        int[] sizes = {100, 500, 1000};
        
        System.out.println("Tipo Array\t\tSize\tOttimizzato\t\tClassico\t\tMiglioramento");
        System.out.println("=".repeat(85));
        
        for (int size : sizes) {
            // Test su array già ordinato
            testComparison("Già ordinato", generateSortedArray(size), size);
            
            // Test su array casuale  
            testComparison("Casuale", generateRandomArray(size), size);
            
            // Test su array invertito
            testComparison("Invertito", generateReversedArray(size), size);
            
            System.out.println();
        }
    }
    
    /**
     * Testa e confronta le due versioni dell'algoritmo
     */
    private static void testComparison(String type, int[] originalArray, int size) {
        // Test versione ottimizzata
        int[] array1 = originalArray.clone();
        SortingStats optimizedStats = bubbleSortOptimized(array1, false);
        
        // Test versione classica
        int[] array2 = originalArray.clone();
        SortingStats classicStats = bubbleSortClassic(array2);
        
        // Calcola miglioramento
        double timeImprovement = (double) classicStats.timeNanos / optimizedStats.timeNanos;
        double comparisonImprovement = (double) classicStats.comparisons / optimizedStats.comparisons;
        
        System.out.printf("%-12s\t%d\t%d/%d/%.1fms\t\t%d/%d/%.1fms\t%.1fx/%.1fx%n",
            type, size,
            optimizedStats.comparisons, optimizedStats.swaps, optimizedStats.timeNanos / 1_000_000.0,
            classicStats.comparisons, classicStats.swaps, classicStats.timeNanos / 1_000_000.0,
            comparisonImprovement, timeImprovement);
    }
    
    // =================== GENERATORI DI ARRAY DI TEST ===================
    
    /**
     * Genera array già ordinato
     */
    private static int[] generateSortedArray(int size) {
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        return array;
    }
    
    /**
     * Genera array ordinato al contrario
     */
    private static int[] generateReversedArray(int size) {
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = size - i - 1;
        }
        return array;
    }
    
    /**
     * Genera array casuale
     */
    private static int[] generateRandomArray(int size) {
        int[] array = new int[size];
        Random random = new Random(42); // Seed fisso per riproducibilità
        
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(size);
        }
        return array;
    }
    
    /**
     * Genera array quasi ordinato (pochi elementi fuori posto)
     */
    private static int[] generateNearlyOrderedArray(int size) {
        int[] array = generateSortedArray(size);
        Random random = new Random(42);
        
        // Scambia circa 5% degli elementi
        int swapsToMake = size / 20;
        for (int i = 0; i < swapsToMake; i++) {
            int pos1 = random.nextInt(size);
            int pos2 = random.nextInt(size);
            swap(array, pos1, pos2);
        }
        
        return array;
    }
}

/*
 * OUTPUT ATTESO (estratto):
 * 
 * === ESERCIZIO B.2: BUBBLE SORT OTTIMIZZATO ===
 * 
 * 🔍 DIMOSTRAZIONE VISIVA
 * 
 * Vediamo come lavora Bubble Sort ottimizzato:
 * 
 * Array iniziale: [64, 34, 25, 12, 22, 11, 90]
 * 
 * --- Iterazione 1 ---
 * Controllo elementi da 0 a 5
 * Confronto 64 e 34: SCAMBIO → [34, 64, 25, 12, 22, 11, 90]
 * Confronto 64 e 25: SCAMBIO → [34, 25, 64, 12, 22, 11, 90]
 * ...
 * Fine iterazione: [34, 25, 12, 22, 11, 64, 90]
 * Elemento 90 in posizione finale
 * 
 * [continua per tutte le iterazioni...]
 * 
 * ✅ Ordinamento completato!
 * Array finale: [11, 12, 22, 25, 34, 64, 90]
 * Statistiche: Confronti: 21, Scambi: 15, Iterazioni: 6, Tempo: 0.125 ms
 * 
 * 📊 ANALISI PRESTAZIONI SU DIVERSI TIPI DI ARRAY
 * 
 * 📈 Array GIÀ ORDINATO (1000 elementi):
 *    Confronti: 999, Scambi: 0, Iterazioni: 1, Tempo: 0.234 ms
 *    🎯 Beneficio ottimizzazione: Terminazione dopo 1 iterazione!
 * 
 * 📉 Array ORDINATO AL CONTRARIO (1000 elementi):
 *    Confronti: 499500, Scambi: 499500, Iterazioni: 999, Tempo: 15.678 ms
 *    ⚠️  Caso peggiore: Massimo numero di confronti e scambi
 * 
 * [... altri risultati ...]
 */
