/**
 * EsempioVariabili.java - Dimostrazione tipi di dati e variabili
 * 
 * Questo esempio mostra:
 * - Dichiarazione e inizializzazione di variabili
 * - Diversi tipi di dati primitivi Java
 * - Operazioni matematiche base
 * - Concatenazione di stringhe
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class EsempioVariabili {
    
    public static void main(String[] args) {
        System.out.println("=== ESEMPIO: Variabili e Tipi di Dati ===\n");
        
        // --- TIPI NUMERICI INTERI ---
        System.out.println("📊 TIPI NUMERICI INTERI:");
        
        byte piccoloNumero = 127;           // -128 a 127
        short numeroMedio = 32000;          // -32,768 a 32,767  
        int numeroStandard = 2000000;       // -2^31 a 2^31-1
        long numeroGrande = 9000000000L;    // -2^63 a 2^63-1 (nota la L)
        
        System.out.println("byte:  " + piccoloNumero + " (range: -128 a 127)");
        System.out.println("short: " + numeroMedio + " (range: -32,768 a 32,767)");
        System.out.println("int:   " + numeroStandard + " (tipo più usato)");
        System.out.println("long:  " + numeroGrande + " (nota la 'L' finale)\n");
        
        // --- TIPI NUMERICI DECIMALI ---
        System.out.println("🔢 TIPI NUMERICI DECIMALI:");
        
        float decimaleCorto = 3.14159f;     // Precisione singola (nota la f)
        double decimaleStandard = 3.141592653589793; // Precisione doppia
        
        System.out.println("float:  " + decimaleCorto + " (precisione singola)");
        System.out.println("double: " + decimaleStandard + " (precisione doppia)\n");
        
        // --- TIPI CARATTERE E BOOLEANO ---
        System.out.println("📝 CARATTERE E BOOLEANO:");
        
        char lettera = 'A';                 // Singolo carattere Unicode
        char simbolo = '🚀';               // Supporta emoji!
        boolean veroFalso = true;           // true o false
        boolean condizione = (5 > 3);       // Risultato di espressione
        
        System.out.println("char (lettera): " + lettera);
        System.out.println("char (simbolo): " + simbolo);
        System.out.println("boolean: " + veroFalso);
        System.out.println("boolean (espressione): " + condizione + "\n");
        
        // --- STRINGHE ---
        System.out.println("🔤 STRINGHE:");
        
        String saluto = "Ciao";             // Stringa letterale
        String nome = "Java";               // Altra stringa
        String frase = saluto + " " + nome + "!"; // Concatenazione
        
        System.out.println("Stringa 1: " + saluto);
        System.out.println("Stringa 2: " + nome);
        System.out.println("Concatenazione: " + frase);
        System.out.println("Lunghezza frase: " + frase.length() + " caratteri\n");
        
        // --- OPERAZIONI MATEMATICHE ---
        System.out.println("🧮 OPERAZIONI MATEMATICHE:");
        
        int a = 15;
        int b = 4;
        
        System.out.println("a = " + a + ", b = " + b);
        System.out.println("a + b = " + (a + b) + " (addizione)");
        System.out.println("a - b = " + (a - b) + " (sottrazione)");
        System.out.println("a * b = " + (a * b) + " (moltiplicazione)");
        System.out.println("a / b = " + (a / b) + " (divisione intera)");
        System.out.println("a % b = " + (a % b) + " (resto della divisione)");
        
        // Divisione con decimali
        double divisione = (double) a / b;  // Cast per divisione decimale
        System.out.println("a / b (decimale) = " + divisione + "\n");
        
        // --- COSTANTI ---
        System.out.println("📌 COSTANTI:");
        
        final double PI = 3.14159;          // Costante (final = non modificabile)
        final int MAX_STUDENTI = 30;        // Convenzione: UPPER_CASE
        
        System.out.println("PI (costante): " + PI);
        System.out.println("MAX_STUDENTI: " + MAX_STUDENTI);
        
        // PI = 3.0; // ❌ ERRORE! Non si può modificare una costante
        
        System.out.println("\n✅ Esempio completato con successo!");
    }
}
