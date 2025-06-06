/**
 * ESERCIZIO B.2 - Implementazione Algoritmi di Ordinamento
 * 
 * OBIETTIVO:
 * Implementare e confrontare diversi algoritmi di ordinamento,
 * analizzando la loro complessità computazionale.
 * 
 * ALGORITMI DA IMPLEMENTARE:
 * 1. Bubble Sort (O(n²))
 * 2. Selection Sort (O(n²))
 * 3. Insertion Sort (O(n²))
 * 
 * ANALISI RICHIESTA:
 * - Confrontare il numero di operazioni per ogni algoritmo
 * - Misurare i tempi di esecuzione
 * - Identificare il migliore per diversi tipi di input
 * 
 * METODOLOGIA APPLICATA:
 * 1. Comprensione: Ordinare array con diversi algoritmi
 * 2. Analisi: Confrontare efficienza e prestazioni
 * 3. Progettazione: Implementazione pulita e misurabile
 * 4. Implementazione: Codice modulare e testabile
 * 5. Test: Diversi scenari (ordinato, inverso, casuale)
 * 6. Ottimizzazione: Identificare il migliore per ogni caso
 * 
 * @author Studente
 * @version 1.0
 */
public class Esercizio02_AlgoritmiOrdinamento {
    
    // Contatori per analisi della complessità
    private static long confronti = 0;
    private static long scambi = 0;
    
    /**
     * Implementa l'algoritmo Bubble Sort
     * 
     * @param array Array da ordinare
     * @return Array ordinato
     */
    public static int[] bubbleSort(int[] array) {
        // TODO 1: Implementare Bubble Sort
        // ALGORITMO:
        // 1. Per ogni elemento dall'inizio alla fine
        // 2. Confronta elementi adiacenti
        // 3. Se sono nell'ordine sbagliato, scambiali
        // 4. Ripeti finché non ci sono più scambi
        
        int[] arr = array.clone(); // Copia per non modificare l'originale
        int n = arr.length;
        
        // Implementare qui l'algoritmo
        // SUGGERIMENTO: Usare due cicli annidati
        // Esterno: da 0 a n-1
        // Interno: da 0 a n-i-1
        
        return arr;
    }
    
    /**
     * Implementa l'algoritmo Selection Sort
     * 
     * @param array Array da ordinare
     * @return Array ordinato
     */
    public static int[] selectionSort(int[] array) {
        // TODO 2: Implementare Selection Sort
        // ALGORITMO:
        // 1. Trova l'elemento minimo nella parte non ordinata
        // 2. Scambialo con il primo elemento della parte non ordinata
        // 3. Ripeti per il resto dell'array
        
        int[] arr = array.clone();
        int n = arr.length;
        
        // Implementare qui l'algoritmo
        // SUGGERIMENTO: 
        // Esterno: da 0 a n-1
        // Interno: trova il minimo da i+1 a n-1
        
        return arr;
    }
    
    /**
     * Implementa l'algoritmo Insertion Sort
     * 
     * @param array Array da ordinato
     * @return Array ordinato
     */
    public static int[] insertionSort(int[] array) {
        // TODO 3: Implementare Insertion Sort
        // ALGORITMO:
        // 1. Inizia dal secondo elemento
        // 2. Confronta con gli elementi precedenti
        // 3. Inserisci nella posizione corretta
        // 4. Ripeti per tutti gli elementi
        
        int[] arr = array.clone();
        int n = arr.length;
        
        // Implementare qui l'algoritmo
        // SUGGERIMENTO:
        // Esterno: da 1 a n-1
        // Interno: sposta elementi verso destra finché trova la posizione
        
        return arr;
    }
    
    /**
     * Metodo di utilità per scambiare due elementi
     */
    private static void scambia(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        scambi++; // Incrementa contatore scambi
    }
    
    /**
     * Metodo di utilità per confrontare due elementi
     */
    private static boolean maggiore(int a, int b) {
        confronti++; // Incrementa contatore confronti
        return a > b;
    }
    
    /**
     * Resetta i contatori per le statistiche
     */
    private static void resetContatori() {
        confronti = 0;
        scambi = 0;
    }
    
    /**
     * Stampa le statistiche dell'algoritmo
     */
    private static void stampaStatistiche(String algoritmo, long tempo) {
        System.out.println("--- " + algoritmo + " ---");
        System.out.println("Confronti: " + confronti);
        System.out.println("Scambi: " + scambi);
        System.out.println("Tempo: " + tempo + " ms");
        System.out.println();
    }
    
    /**
     * Verifica se un array è ordinato
     */
    public static boolean isOrdinato(int[] array) {
        for (int i = 0; i < array.length - 1; i++) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }
    
    /**
     * Stampa un array
     */
    public static void stampaArray(int[] array, String nome) {
        System.out.print(nome + ": ");
        if (array.length <= 20) {
            System.out.print("[");
            for (int i = 0; i < array.length; i++) {
                System.out.print(array[i]);
                if (i < array.length - 1) System.out.print(", ");
            }
            System.out.println("]");
        } else {
            System.out.println("Array di " + array.length + " elementi");
        }
    }
    
    /**
     * Genera un array casuale
     */
    public static int[] generaArrayCasuale(int dimensione, int maxValore) {
        int[] array = new int[dimensione];
        for (int i = 0; i < dimensione; i++) {
            array[i] = (int) (Math.random() * maxValore);
        }
        return array;
    }
    
    /**
     * Genera un array già ordinato
     */
    public static int[] generaArrayOrdinato(int dimensione) {
        int[] array = new int[dimensione];
        for (int i = 0; i < dimensione; i++) {
            array[i] = i + 1;
        }
        return array;
    }
    
    /**
     * Genera un array ordinato in modo inverso
     */
    public static int[] generaArrayInverso(int dimensione) {
        int[] array = new int[dimensione];
        for (int i = 0; i < dimensione; i++) {
            array[i] = dimensione - i;
        }
        return array;
    }
    
    /**
     * Test degli algoritmi di ordinamento
     */
    public static void main(String[] args) {
        System.out.println("=== ESERCIZIO B.2 - ALGORITMI DI ORDINAMENTO ===\n");
        
        // Test con array piccolo
        int[] testPiccolo = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("=== TEST CON ARRAY PICCOLO ===");
        stampaArray(testPiccolo, "Array originale");
        
        // Test Bubble Sort
        resetContatori();
        long startTime = System.currentTimeMillis();
        int[] risultatoBubble = bubbleSort(testPiccolo);
        long endTime = System.currentTimeMillis();
        stampaArray(risultatoBubble, "Bubble Sort");
        System.out.println("Ordinato correttamente: " + isOrdinato(risultatoBubble));
        stampaStatistiche("BUBBLE SORT", endTime - startTime);
        
        // Test Selection Sort
        resetContatori();
        startTime = System.currentTimeMillis();
        int[] risultatoSelection = selectionSort(testPiccolo);
        endTime = System.currentTimeMillis();
        stampaArray(risultatoSelection, "Selection Sort");
        System.out.println("Ordinato correttamente: " + isOrdinato(risultatoSelection));
        stampaStatistiche("SELECTION SORT", endTime - startTime);
        
        // Test Insertion Sort
        resetContatori();
        startTime = System.currentTimeMillis();
        int[] risultatoInsertion = insertionSort(testPiccolo);
        endTime = System.currentTimeMillis();
        stampaArray(risultatoInsertion, "Insertion Sort");
        System.out.println("Ordinato correttamente: " + isOrdinato(risultatoInsertion));
        stampaStatistiche("INSERTION SORT", endTime - startTime);
        
        // TODO 4: Test prestazioni con array grandi
        System.out.println("=== ANALISI PRESTAZIONI (Array di 1000 elementi) ===");
        
        // Array casuale
        int[] arrayCasuale = generaArrayCasuale(1000, 1000);
        System.out.println("\n--- ARRAY CASUALE ---");
        // Testare tutti e tre gli algoritmi e confrontare le prestazioni
        
        // Array già ordinato
        int[] arrayOrdinato = generaArrayOrdinato(1000);
        System.out.println("\n--- ARRAY GIÀ ORDINATO ---");
        // Testare tutti e tre gli algoritmi
        
        // Array ordinato al contrario
        int[] arrayInverso = generaArrayInverso(1000);
        System.out.println("\n--- ARRAY ORDINATO AL CONTRARIO ---");
        // Testare tutti e tre gli algoritmi
        
        // TODO 5: Conclusioni
        System.out.println("=== CONCLUSIONI ===");
        System.out.println("Completa l'implementazione e analizza i risultati:");
        System.out.println("1. Quale algoritmo è più efficiente in generale?");
        System.out.println("2. Quale si comporta meglio con array già ordinati?");
        System.out.println("3. Quale ha il minor numero di scambi?");
        System.out.println("4. Come varia la complessità con la dimensione?");
    }
}
