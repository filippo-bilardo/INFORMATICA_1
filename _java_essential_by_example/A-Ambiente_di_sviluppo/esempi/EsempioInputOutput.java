import java.util.Scanner;

/**
 * EsempioInputOutput.java - Input utente e output formattato
 * 
 * Questo esempio dimostra:
 * - Lettura input da tastiera con Scanner
 * - Diversi metodi di input (nextLine, nextInt, etc.)
 * - Output formattato con printf
 * - Gestione dei caratteri speciali
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class EsempioInputOutput {
    
    public static void main(String[] args) {
        // Crea oggetto Scanner per leggere input dalla console
        Scanner input = new Scanner(System.in);
        
        // Banner di benvenuto
        stampaBanner();
        
        // --- RACCOLTA DATI UTENTE ---
        System.out.println("📋 RACCOLTA INFORMAZIONI:\n");
        
        // Input stringa (con spazi)
        System.out.print("Inserisci il tuo nome completo: ");
        String nomeCompleto = input.nextLine();
        
        // Input numero intero
        System.out.print("Inserisci la tua età: ");
        int eta = input.nextInt();
        
        // Input numero decimale
        System.out.print("Inserisci la tua altezza (es. 1.75): ");
        double altezza = input.nextDouble();
        
        // Pulizia buffer dopo nextInt/nextDouble
        input.nextLine(); // Consuma il newline rimasto
        
        // Input stringa dopo numeri
        System.out.print("Inserisci la tua città: ");
        String citta = input.nextLine();
        
        // Input carattere
        System.out.print("Inserisci l'iniziale del tuo nome: ");
        char iniziale = input.nextLine().charAt(0); // Prende primo carattere
        
        // Input booleano (simulato)
        System.out.print("Ti piace la programmazione? (si/no): ");
        String risposta = input.nextLine();
        boolean piaceProgrammazione = risposta.equalsIgnoreCase("si") || 
                                    risposta.equalsIgnoreCase("sì") ||
                                    risposta.equalsIgnoreCase("yes");
        
        // --- ELABORAZIONE DATI ---
        int annoNascita = 2025 - eta;
        String categoria = (eta >= 18) ? "Maggiorenne" : "Minorenne";
        double altezzaCm = altezza * 100;
        
        // --- OUTPUT FORMATTATO ---
        System.out.println("\n" + "=".repeat(50));
        System.out.println("           RIEPILOGO INFORMAZIONI");
        System.out.println("=".repeat(50));
        
        // Output con concatenazione
        System.out.println("👤 Nome: " + nomeCompleto);
        System.out.println("🎂 Età: " + eta + " anni");
        System.out.println("📏 Altezza: " + altezza + " metri");
        System.out.println("🏠 Città: " + citta);
        System.out.println("🔤 Iniziale: " + iniziale);
        
        // Output con printf (formattazione avanzata)
        System.out.printf("📅 Anno di nascita: %d%n", annoNascita);
        System.out.printf("📊 Categoria: %s%n", categoria);
        System.out.printf("📐 Altezza in cm: %.0f cm%n", altezzaCm);
        System.out.printf("💻 Piace programmare: %s%n", 
                         piaceProgrammazione ? "Sì! 🚀" : "Non ancora 😅");
        
        // --- ESEMPI DI FORMATTAZIONE PRINTF ---
        System.out.println("\n" + "=".repeat(50));
        System.out.println("        ESEMPI DI FORMATTAZIONE");
        System.out.println("=".repeat(50));
        
        double numero = 123.456789;
        int intero = 42;
        String testo = "Java";
        
        System.out.println("🔢 FORMATTAZIONE NUMERI:");
        System.out.printf("   Numero originale: %f%n", numero);
        System.out.printf("   2 decimali: %.2f%n", numero);
        System.out.printf("   0 decimali: %.0f%n", numero);
        System.out.printf("   Larghezza 10: %10.2f%n", numero);
        System.out.printf("   Con zeri: %08.2f%n", numero);
        
        System.out.println("\n🔤 FORMATTAZIONE STRINGHE:");
        System.out.printf("   Stringa: '%s'%n", testo);
        System.out.printf("   Larghezza 10: '%10s'%n", testo);
        System.out.printf("   Allineata sx: '%-10s'%n", testo);
        
        System.out.println("\n🔢 FORMATTAZIONE INTERI:");
        System.out.printf("   Intero: %d%n", intero);
        System.out.printf("   Esadecimale: %x%n", intero);
        System.out.printf("   Ottale: %o%n", intero);
        System.out.printf("   Con segno: %+d%n", intero);
        
        // --- CARATTERI SPECIALI ---
        System.out.println("\n" + "=".repeat(50));
        System.out.println("         CARATTERI SPECIALI");
        System.out.println("=".repeat(50));
        
        System.out.println("🎨 ESEMPI DI ESCAPE SEQUENCES:");
        System.out.println("   Nuova riga: Riga 1\\nRiga 2");
        System.out.println("Nuova riga: Riga 1\nRiga 2");
        
        System.out.println("   Tab: Colonna1\\tColonna2");
        System.out.println("Tab: Colonna1\tColonna2");
        
        System.out.println("   Virgolette: \"Testo tra virgolette\"");
        System.out.println("   Backslash: C:\\\\Users\\\\Nome");
        System.out.println("   Unicode: \\u2764 → \u2764 (cuore)");
        
        // --- MESSAGGIO FINALE ---
        System.out.println("\n" + "=".repeat(50));
        System.out.printf("✅ Ciao %s! Benvenuto/a nel mondo Java! 🚀%n", 
                         nomeCompleto.split(" ")[0]); // Prende solo il nome
        System.out.println("=".repeat(50));
        
        // Chiudi lo Scanner (buona pratica)
        input.close();
    }
    
    /**
     * Stampa un banner di benvenuto decorativo
     */
    private static void stampaBanner() {
        System.out.println("╔════════════════════════════════════════════════╗");
        System.out.println("║              ESEMPIO INPUT/OUTPUT              ║");
        System.out.println("║                    🎯📝💻                     ║");
        System.out.println("║        Impariamo a gestire input e output      ║");
        System.out.println("╚════════════════════════════════════════════════╝");
        System.out.println();
    }
}
