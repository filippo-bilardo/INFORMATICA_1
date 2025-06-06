/**
 * SOLUZIONE ESERCIZIO B.1 - Secondo Elemento Massimo
 * 
 * Questa è la soluzione completa dell'esercizio.
 * Confronta la tua implementazione con questa soluzione.
 * 
 * @author Docente
 * @version 1.0
 */
public class Esercizio01_SecondoMassimo_Soluzione {
    
    /**
     * Trova il secondo elemento più grande nell'array
     * 
     * @param numeri Array di numeri interi (minimo 2 elementi)
     * @return Il secondo numero più grande
     * @throws IllegalArgumentException se l'array ha meno di 2 elementi
     */
    public static int trovaSecondoMassimo(int[] numeri) {
        // SOLUZIONE TODO 1: Validare l'input
        if (numeri == null || numeri.length < 2) {
            throw new IllegalArgumentException("L'array deve contenere almeno 2 elementi");
        }
        
        // SOLUZIONE TODO 2: Inizializzare le variabili
        int massimo = Integer.MIN_VALUE;
        int secondoMassimo = Integer.MIN_VALUE;
        
        // SOLUZIONE TODO 3: Scorrere l'array e aggiornare massimo e secondoMassimo
        for (int i = 0; i < numeri.length; i++) {
            int elemento = numeri[i];
            
            if (elemento > massimo) {
                // Nuovo massimo trovato: aggiorna entrambi
                secondoMassimo = massimo;
                massimo = elemento;
            } else if (elemento > secondoMassimo && elemento != massimo) {
                // Nuovo secondo massimo (diverso dal massimo)
                secondoMassimo = elemento;
            }
        }
        
        // SOLUZIONE TODO 4: Gestire il caso in cui tutti gli elementi sono uguali
        if (secondoMassimo == Integer.MIN_VALUE) {
            // Tutti gli elementi sono uguali, il secondo massimo è uguale al massimo
            secondoMassimo = massimo;
        }
        
        // SOLUZIONE TODO 5: Ritornare il secondo massimo
        return secondoMassimo;
    }
    
    /**
     * Metodo di utilità per stampare l'array
     */
    public static void stampaArray(int[] array) {
        System.out.print("[");
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]);
            if (i < array.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }
    
    /**
     * Metodo main per testare la soluzione
     */
    public static void main(String[] args) {
        System.out.println("=== SOLUZIONE ESERCIZIO B.1 - SECONDO ELEMENTO MASSIMO ===\n");
        
        // Test Case 1: Array normale
        int[] test1 = {5, 2, 8, 1, 9, 3};
        System.out.print("Test 1 - Array: ");
        stampaArray(test1);
        try {
            int risultato1 = trovaSecondoMassimo(test1);
            System.out.println("Secondo massimo: " + risultato1);
            System.out.println("✅ Test superato (atteso: 8)\n");
        } catch (Exception e) {
            System.out.println("❌ Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 2: Array con duplicati
        int[] test2 = {3, 3, 5, 5, 1, 1};
        System.out.print("Test 2 - Array con duplicati: ");
        stampaArray(test2);
        try {
            int risultato2 = trovaSecondoMassimo(test2);
            System.out.println("Secondo massimo: " + risultato2);
            System.out.println("✅ Test superato (atteso: 3)\n");
        } catch (Exception e) {
            System.out.println("❌ Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 3: Array con tutti elementi uguali
        int[] test3 = {7, 7, 7, 7};
        System.out.print("Test 3 - Tutti elementi uguali: ");
        stampaArray(test3);
        try {
            int risultato3 = trovaSecondoMassimo(test3);
            System.out.println("Secondo massimo: " + risultato3);
            System.out.println("✅ Test superato (atteso: 7)\n");
        } catch (Exception e) {
            System.out.println("❌ Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 4: Array con numeri negativi
        int[] test4 = {-1, -5, -2, -8, -3};
        System.out.print("Test 4 - Numeri negativi: ");
        stampaArray(test4);
        try {
            int risultato4 = trovaSecondoMassimo(test4);
            System.out.println("Secondo massimo: " + risultato4);
            System.out.println("✅ Test superato (atteso: -2)\n");
        } catch (Exception e) {
            System.out.println("❌ Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 5: Array con solo 2 elementi
        int[] test5 = {10, 20};
        System.out.print("Test 5 - Solo 2 elementi: ");
        stampaArray(test5);
        try {
            int risultato5 = trovaSecondoMassimo(test5);
            System.out.println("Secondo massimo: " + risultato5);
            System.out.println("✅ Test superato (atteso: 10)\n");
        } catch (Exception e) {
            System.out.println("❌ Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 6: Array vuoto (dovrebbe lanciare eccezione)
        int[] test6 = {};
        System.out.print("Test 6 - Array vuoto: ");
        stampaArray(test6);
        try {
            int risultato6 = trovaSecondoMassimo(test6);
            System.out.println("❌ Dovrebbe lanciare eccezione!");
        } catch (Exception e) {
            System.out.println("✅ Eccezione gestita correttamente: " + e.getMessage() + "\n");
        }
        
        System.out.println("=== ANALISI DELLA COMPLESSITÀ ===");
        System.out.println("• Complessità temporale: O(n) - un singolo passaggio");
        System.out.println("• Complessità spaziale: O(1) - spazio costante");
        System.out.println("• Algoritmo ottimale per questo problema!");
    }
}
