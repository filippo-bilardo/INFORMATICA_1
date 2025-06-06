/**
 * ESERCIZIO B.1 - Secondo Elemento Massimo
 * 
 * OBIETTIVO:
 * Applicare la metodologia di risoluzione dei problemi per trovare
 * il secondo elemento più grande in un array di numeri interi.
 * 
 * ANALISI DEL PROBLEMA:
 * 1. INPUT: Array di numeri interi (minimo 2 elementi)
 * 2. OUTPUT: Il secondo numero più grande
 * 3. VINCOLI: 
 *    - Array deve avere almeno 2 elementi
 *    - Gestire duplicati (se tutti uguali, ritornare il valore stesso)
 * 4. CASI SPECIALI:
 *    - Array con tutti elementi uguali
 *    - Array con solo 2 elementi
 *    - Array con elementi negativi
 * 
 * METODOLOGIA APPLICATA:
 * 1. Comprensione: Trovare il secondo valore più alto
 * 2. Analisi: Scorrere l'array tenendo traccia di max e secondo_max
 * 3. Progettazione: Un singolo passaggio O(n)
 * 4. Implementazione: Variabili per max e secondoMax
 * 5. Test: Diversi casi d'uso
 * 6. Ottimizzazione: Algoritmo già ottimale
 * 
 * ISTRUZIONI:
 * 1. Completare il metodo trovaSecondoMassimo()
 * 2. Implementare la logica seguendo i commenti TODO
 * 3. Testare con gli esempi forniti nel main
 * 4. Aggiungere test cases aggiuntivi
 * 
 * @author Studente
 * @version 1.0
 */
public class Esercizio01_SecondoMassimo {
    
    /**
     * Trova il secondo elemento più grande nell'array
     * 
     * @param numeri Array di numeri interi (minimo 2 elementi)
     * @return Il secondo numero più grande
     * @throws IllegalArgumentException se l'array ha meno di 2 elementi
     */
    public static int trovaSecondoMassimo(int[] numeri) {
        // TODO 1: Validare l'input
        // Verificare che l'array non sia null e abbia almeno 2 elementi
        
        
        // TODO 2: Inizializzare le variabili per il massimo e secondo massimo
        // SUGGERIMENTO: Utilizzare Integer.MIN_VALUE per l'inizializzazione
        int massimo = Integer.MIN_VALUE;
        int secondoMassimo = Integer.MIN_VALUE;
        
        // TODO 3: Scorrere l'array e aggiornare massimo e secondoMassimo
        // LOGICA:
        // - Se elemento > massimo: aggiorna secondoMassimo = massimo, massimo = elemento
        // - Altrimenti se elemento > secondoMassimo e elemento != massimo: aggiorna secondoMassimo
        for (int i = 0; i < numeri.length; i++) {
            int elemento = numeri[i];
            
            // Implementare la logica qui
            
        }
        
        // TODO 4: Gestire il caso in cui tutti gli elementi sono uguali
        // Se secondoMassimo è ancora Integer.MIN_VALUE, tutti gli elementi sono uguali
        
        
        // TODO 5: Ritornare il secondo massimo
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
        System.out.println("=== ESERCIZIO B.1 - SECONDO ELEMENTO MASSIMO ===\n");
        
        // Test Case 1: Array normale
        int[] test1 = {5, 2, 8, 1, 9, 3};
        System.out.print("Test 1 - Array: ");
        stampaArray(test1);
        try {
            int risultato1 = trovaSecondoMassimo(test1);
            System.out.println("Secondo massimo: " + risultato1);
            System.out.println("Atteso: 8\n");
        } catch (Exception e) {
            System.out.println("Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 2: Array con duplicati
        int[] test2 = {3, 3, 5, 5, 1, 1};
        System.out.print("Test 2 - Array con duplicati: ");
        stampaArray(test2);
        try {
            int risultato2 = trovaSecondoMassimo(test2);
            System.out.println("Secondo massimo: " + risultato2);
            System.out.println("Atteso: 3\n");
        } catch (Exception e) {
            System.out.println("Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 3: Array con tutti elementi uguali
        int[] test3 = {7, 7, 7, 7};
        System.out.print("Test 3 - Tutti elementi uguali: ");
        stampaArray(test3);
        try {
            int risultato3 = trovaSecondoMassimo(test3);
            System.out.println("Secondo massimo: " + risultato3);
            System.out.println("Atteso: 7\n");
        } catch (Exception e) {
            System.out.println("Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 4: Array con numeri negativi
        int[] test4 = {-1, -5, -2, -8, -3};
        System.out.print("Test 4 - Numeri negativi: ");
        stampaArray(test4);
        try {
            int risultato4 = trovaSecondoMassimo(test4);
            System.out.println("Secondo massimo: " + risultato4);
            System.out.println("Atteso: -2\n");
        } catch (Exception e) {
            System.out.println("Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 5: Array con solo 2 elementi
        int[] test5 = {10, 20};
        System.out.print("Test 5 - Solo 2 elementi: ");
        stampaArray(test5);
        try {
            int risultato5 = trovaSecondoMassimo(test5);
            System.out.println("Secondo massimo: " + risultato5);
            System.out.println("Atteso: 10\n");
        } catch (Exception e) {
            System.out.println("Errore: " + e.getMessage() + "\n");
        }
        
        // Test Case 6: Array vuoto (dovrebbe lanciare eccezione)
        int[] test6 = {};
        System.out.print("Test 6 - Array vuoto: ");
        stampaArray(test6);
        try {
            int risultato6 = trovaSecondoMassimo(test6);
            System.out.println("Secondo massimo: " + risultato6);
        } catch (Exception e) {
            System.out.println("Errore (atteso): " + e.getMessage() + "\n");
        }
        
        System.out.println("=== COMPLETA L'IMPLEMENTAZIONE PER PASSARE TUTTI I TEST ===");
    }
}
