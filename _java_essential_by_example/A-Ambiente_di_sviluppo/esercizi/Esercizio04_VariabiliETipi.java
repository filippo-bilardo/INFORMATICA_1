/**
 * ESERCIZIO 4: Gestione Variabili e Tipi
 * 
 * OBIETTIVO:
 * Sperimentare con diversi tipi di dati Java e operazioni
 * per comprendere meglio il sistema di tipi.
 * 
 * REQUISITI:
 * 1. Dichiarare variabili di tutti i tipi primitivi
 * 2. Dimostrare il casting tra tipi
 * 3. Mostrare overflow e underflow
 * 4. Sperimentare con operatori
 * 5. Gestire stringhe e caratteri
 * 
 * @author Il tuo nome
 * @version 1.0
 */
public class Esercizio04_VariabiliETipi {
    
    public static void main(String[] args) {
        System.out.println("🔢 ESPERIMENTI CON TIPI DI DATI 🔢");
        System.out.println("=".repeat(40));
        
        // TODO: SEZIONE 1 - Tipi numerici interi
        System.out.println("\n📊 TIPI INTERI:");
        
        // TODO: Dichiara e stampa variabili byte, short, int, long
        // Mostra i valori massimi e minimi
        // Hint: Byte.MAX_VALUE, Byte.MIN_VALUE, etc.
        
        // TODO: SEZIONE 2 - Tipi decimali
        System.out.println("\n🔢 TIPI DECIMALI:");
        
        // TODO: Dichiara float e double
        // Mostra la differenza di precisione
        // Esempio: calcola 1.0/3.0 con float e double
        
        // TODO: SEZIONE 3 - Casting (conversione tipi)
        System.out.println("\n🔄 CASTING:");
        
        // TODO: Esempi di casting implicito ed esplicito
        // int a = 10;
        // double b = a;        // Casting implicito
        // int c = (int) 3.14;  // Casting esplicito
        
        // TODO: SEZIONE 4 - Overflow
        System.out.println("\n⚠️ OVERFLOW:");
        
        // TODO: Dimostra overflow con byte
        // byte maxByte = Byte.MAX_VALUE;
        // System.out.println("Max byte: " + maxByte);
        // maxByte++; // Questo causa overflow!
        // System.out.println("Max byte + 1: " + maxByte);
        
        // TODO: SEZIONE 5 - Operatori e precedenza
        System.out.println("\n🧮 OPERATORI:");
        
        // TODO: Testa precedenza operatori
        // int risultato1 = 2 + 3 * 4;     // Cosa viene prima?
        // int risultato2 = (2 + 3) * 4;   // Con parentesi
        
        // TODO: Operatori di incremento/decremento
        // int x = 5;
        // System.out.println("x++ = " + x++);  // Post-incremento
        // System.out.println("++x = " + ++x);  // Pre-incremento
        
        // TODO: SEZIONE 6 - Stringhe e caratteri
        System.out.println("\n📝 STRINGHE E CARATTERI:");
        
        // TODO: Esperimenti con caratteri Unicode
        // char euro = '\u20AC';  // Simbolo Euro
        // char heart = '♥';
        
        // TODO: Concatenazione di stringhe vs addizione
        // String parte1 = "Java";
        // String parte2 = "Programming";
        // System.out.println(parte1 + " " + parte2);
        // System.out.println("Risultato: " + 5 + 3);      // "Risultato: 53"
        // System.out.println("Risultato: " + (5 + 3));    // "Risultato: 8"
        
        // TODO: SEZIONE 7 - Costanti
        System.out.println("\n📌 COSTANTI:");
        
        // TODO: Dichiara costanti con final
        // final double PI = 3.14159;
        // final int GIORNI_SETTIMANA = 7;
        
        System.out.println("\n✅ Esperimenti completati!");
    }
}
