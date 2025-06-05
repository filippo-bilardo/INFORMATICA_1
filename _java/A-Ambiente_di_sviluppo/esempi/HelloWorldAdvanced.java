/**
 * HelloWorldAdvanced.java - Versione avanzata del "Hello World"
 * 
 * Questo esempio mostra:
 * - Documentazione JavaDoc completa
 * - Uso di variabili e costanti
 * - Formattazione dell'output
 * - Gestione degli argomenti da linea di comando
 * - Buone pratiche di programmazione
 * 
 * @author Java Essential by Example
 * @version 2.0
 * @since 1.8
 */
public class HelloWorldAdvanced {
    
    // Costante di classe (final static)
    private static final String PROGRAM_NAME = "HelloWorld Advanced";
    private static final String VERSION = "2.0";
    
    /**
     * Metodo main - punto di ingresso dell'applicazione
     * 
     * Esempi di esecuzione:
     * - java HelloWorldAdvanced
     * - java HelloWorldAdvanced Mario
     * - java HelloWorldAdvanced Mario Rossi
     * 
     * @param args Array degli argomenti da linea di comando
     */
    public static void main(String[] args) {
        // Banner di apertura
        printBanner();
        
        // Saluto personalizzato basato sugli argomenti
        if (args.length == 0) {
            // Nessun argomento fornito
            System.out.println("Ciao, mondo!");
            System.out.println("Suggerimento: prova a eseguire con il tuo nome come argomento.");
        } else if (args.length == 1) {
            // Un solo argomento (presumibilmente il nome)
            String nome = args[0];
            System.out.println("Ciao, " + nome + "!");
            System.out.println("Benvenuto nel mondo della programmazione Java!");
        } else {
            // Multipli argomenti (nome e cognome)
            String nomeCompleto = String.join(" ", args);
            System.out.println("Ciao, " + nomeCompleto + "!");
            System.out.println("È un piacere conoscerti!");
        }
        
        // Separatore
        System.out.println("-".repeat(50));
        
        // Informazioni tecniche
        printSystemInfo();
        
        // Messaggio di chiusura
        System.out.println("\nGrazie per aver utilizzato " + PROGRAM_NAME + "!");
    }
    
    /**
     * Stampa il banner di apertura del programma
     */
    private static void printBanner() {
        System.out.println("=".repeat(50));
        System.out.println("    " + PROGRAM_NAME + " v" + VERSION);
        System.out.println("    Java Essential by Example");
        System.out.println("=".repeat(50));
        System.out.println();
    }
    
    /**
     * Stampa informazioni sul sistema e sulla JVM
     */
    private static void printSystemInfo() {
        System.out.println("INFORMAZIONI SISTEMA:");
        System.out.println("- Versione Java: " + System.getProperty("java.version"));
        System.out.println("- Venditore JVM: " + System.getProperty("java.vendor"));
        System.out.println("- Sistema operativo: " + System.getProperty("os.name"));
        System.out.println("- Architettura: " + System.getProperty("os.arch"));
        System.out.println("- Utente corrente: " + System.getProperty("user.name"));
        System.out.println("- Directory di lavoro: " + System.getProperty("user.dir"));
    }
}

/*
 * CONCETTI DIMOSTRATI IN QUESTO ESEMPIO:
 * 
 * 1. COSTANTI DI CLASSE:
 *    - private static final per valori immutabili
 *    - Convenzione di naming: MAIUSCOLO_CON_UNDERSCORE
 * 
 * 2. METODI STATICI:
 *    - printBanner() e printSystemInfo()
 *    - Possono essere chiamati senza creare un'istanza della classe
 * 
 * 3. GESTIONE ARGOMENTI:
 *    - args.length per contare gli argomenti
 *    - String.join() per concatenare array di stringhe
 * 
 * 4. PROPRIETÀ DI SISTEMA:
 *    - System.getProperty() per ottenere info sul sistema
 * 
 * 5. BUONE PRATICHE:
 *    - Documentazione JavaDoc
 *    - Metodi privati per organizzare il codice
 *    - Nomi di variabili descrittivi
 *    - Output formattato e leggibile
 * 
 * COMPILAZIONE ED ESECUZIONE:
 * javac HelloWorldAdvanced.java
 * java HelloWorldAdvanced
 * java HelloWorldAdvanced Mario
 * java HelloWorldAdvanced Mario Rossi
 */
