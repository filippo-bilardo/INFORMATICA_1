/**
 * SOLUZIONE ESERCIZIO B.2 - Algoritmi di Ordinamento
 * 
 * Implementazione completa dei tre algoritmi di ordinamento
 * con analisi delle prestazioni e della complessità.
 * 
 * @author Docente
 * @version 1.0
 */
public class Esercizio02_AlgoritmiOrdinamento_Soluzione {
    
    // Contatori per analisi della complessità
    private static long confronti = 0;
    private static long scambi = 0;
    
    /**
     * SOLUZIONE: Implementa l'algoritmo Bubble Sort
     * Complessità: O(n²) tempo, O(1) spazio
     */
    public static int[] bubbleSort(int[] array) {
        int[] arr = array.clone();
        int n = arr.length;
        
        // Ciclo esterno: n-1 passaggi
        for (int i = 0; i < n - 1; i++) {
            boolean scambiato = false;
            
            // Ciclo interno: confronta elementi adiacenti
            for (int j = 0; j < n - i - 1; j++) {
                if (maggiore(arr[j], arr[j + 1])) {
                    scambia(arr, j, j + 1);
                    scambiato = true;
                }
            }
            
            // Ottimizzazione: se non ci sono scambi, l'array è ordinato
            if (!scambiato) {
                break;
            }
        }
        
        return arr;
    }
    
    /**
     * SOLUZIONE: Implementa l'algoritmo Selection Sort
     * Complessità: O(n²) tempo, O(1) spazio
     */
    public static int[] selectionSort(int[] array) {
        int[] arr = array.clone();
        int n = arr.length;
        
        // Ciclo esterno: per ogni posizione
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            // Ciclo interno: trova l'elemento minimo
            for (int j = i + 1; j < n; j++) {
                if (maggiore(arr[minIndex], arr[j])) {
                    minIndex = j;
                }
            }
            
            // Scambia solo se necessario
            if (minIndex != i) {
                scambia(arr, i, minIndex);
            }
        }
        
        return arr;
    }
    
    /**
     * SOLUZIONE: Implementa l'algoritmo Insertion Sort
     * Complessità: O(n²) tempo peggiore, O(n) tempo migliore, O(1) spazio
     */
    public static int[] insertionSort(int[] array) {
        int[] arr = array.clone();
        int n = arr.length;
        
        // Inizia dal secondo elemento
        for (int i = 1; i < n; i++) {
            int chiave = arr[i];
            int j = i - 1;
            
            // Sposta gli elementi maggiori verso destra
            while (j >= 0 && maggiore(arr[j], chiave)) {
                arr[j + 1] = arr[j];
                scambi++; // Conta come scambio
                j--;
            }
            
            // Inserisce la chiave nella posizione corretta
            arr[j + 1] = chiave;
        }
        
        return arr;
    }
    
    /**
     * Metodo di utilità per scambiare due elementi
     */
    private static void scambia(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        scambi++;
    }
    
    /**
     * Metodo di utilità per confrontare due elementi
     */
    private static boolean maggiore(int a, int b) {
        confronti++;
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
     * Testa un algoritmo e stampa le statistiche
     */
    private static void testaAlgoritmo(String nome, int[] array, String tipo) {
        resetContatori();
        long startTime = System.nanoTime();
        
        int[] risultato = null;
        switch (nome) {
            case "Bubble Sort":
                risultato = bubbleSort(array);
                break;
            case "Selection Sort":
                risultato = selectionSort(array);
                break;
            case "Insertion Sort":
                risultato = insertionSort(array);
                break;
        }
        
        long endTime = System.nanoTime();
        long tempo = (endTime - startTime) / 1_000_000; // Converti in millisecondi
        
        System.out.println(nome + " (" + tipo + "):");
        System.out.println("✅ Ordinato correttamente: " + isOrdinato(risultato));
        System.out.println("📊 Confronti: " + confronti);
        System.out.println("🔄 Scambi: " + scambi);
        System.out.println("⏱️ Tempo: " + tempo + " ms\n");
    }
    
    /**
     * Test completo degli algoritmi di ordinamento
     */
    public static void main(String[] args) {
        System.out.println("=== SOLUZIONE ESERCIZIO B.2 - ALGORITMI DI ORDINAMENTO ===\n");
        
        // Test con array piccolo
        int[] testPiccolo = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("=== TEST CON ARRAY PICCOLO ===");
        stampaArray(testPiccolo, "Array originale");
        System.out.println();
        
        // Test tutti gli algoritmi
        testaAlgoritmo("Bubble Sort", testPiccolo, "Array piccolo");
        testaAlgoritmo("Selection Sort", testPiccolo, "Array piccolo");
        testaAlgoritmo("Insertion Sort", testPiccolo, "Array piccolo");
        
        // Analisi prestazioni con array grandi
        System.out.println("=== ANALISI PRESTAZIONI (Array di 1000 elementi) ===\n");
        
        // Array casuale
        int[] arrayCasuale = generaArrayCasuale(1000, 1000);
        System.out.println("🎲 ARRAY CASUALE:");
        testaAlgoritmo("Bubble Sort", arrayCasuale, "Casuale");
        testaAlgoritmo("Selection Sort", arrayCasuale, "Casuale");
        testaAlgoritmo("Insertion Sort", arrayCasuale, "Casuale");
        
        // Array già ordinato
        int[] arrayOrdinato = generaArrayOrdinato(1000);
        System.out.println("📈 ARRAY GIÀ ORDINATO:");
        testaAlgoritmo("Bubble Sort", arrayOrdinato, "Ordinato");
        testaAlgoritmo("Selection Sort", arrayOrdinato, "Ordinato");
        testaAlgoritmo("Insertion Sort", arrayOrdinato, "Ordinato");
        
        // Array ordinato al contrario
        int[] arrayInverso = generaArrayInverso(1000);
        System.out.println("📉 ARRAY ORDINATO AL CONTRARIO:");
        testaAlgoritmo("Bubble Sort", arrayInverso, "Inverso");
        testaAlgoritmo("Selection Sort", arrayInverso, "Inverso");
        testaAlgoritmo("Insertion Sort", arrayInverso, "Inverso");
        
        // Conclusioni
        System.out.println("=== CONCLUSIONI E ANALISI ===");
        System.out.println();
        System.out.println("📊 COMPLESSITÀ TEMPORALE:");
        System.out.println("• Bubble Sort:    O(n²) peggiore, O(n) migliore");
        System.out.println("• Selection Sort: O(n²) sempre");
        System.out.println("• Insertion Sort: O(n²) peggiore, O(n) migliore");
        System.out.println();
        System.out.println("💾 COMPLESSITÀ SPAZIALE:");
        System.out.println("• Tutti gli algoritmi: O(1) - spazio costante");
        System.out.println();
        System.out.println("🏆 QUANDO USARE OGNI ALGORITMO:");
        System.out.println("• Bubble Sort: Mai in produzione (solo didattico)");
        System.out.println("• Selection Sort: Array piccoli, memoria limitata");
        System.out.println("• Insertion Sort: Array piccoli, dati quasi ordinati");
        System.out.println();
        System.out.println("✨ CARATTERISTICHE SPECIALI:");
        System.out.println("• Bubble Sort: Può terminare prima se l'array è ordinato");
        System.out.println("• Selection Sort: Numero minimo di scambi O(n)");
        System.out.println("• Insertion Sort: Stabile, adattivo, online");
        System.out.println();
        System.out.println("🎯 RACCOMANDAZIONE:");
        System.out.println("Per array piccoli (<50 elementi): Insertion Sort");
        System.out.println("Per array grandi: Usa QuickSort, MergeSort o Arrays.sort()");
    }
}
