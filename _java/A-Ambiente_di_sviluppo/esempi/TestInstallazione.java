/**
 * TestInstallazione.java - Programma di verifica dell'installazione Java
 * 
 * Questo programma testa:
 * - Corretta installazione e configurazione di Java
 * - Funzionamento del compilatore javac
 * - Funzionamento dell'interprete java
 * - Accesso alle proprietà di sistema
 * - Operazioni base di I/O
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class TestInstallazione {
    
    /**
     * Metodo main che esegue una serie di test di verifica
     * 
     * @param args Argomenti da linea di comando (non utilizzati)
     */
    public static void main(String[] args) {
        System.out.println("🔧 TEST INSTALLAZIONE JAVA");
        System.out.println("=" + "=".repeat(40));
        
        // Test 1: Informazioni JVM
        testJVM();
        
        // Test 2: Operazioni matematiche
        testOperazioniMatematiche();
        
        // Test 3: Gestione stringhe
        testGestioneStringhe();
        
        // Test 4: Array e cicli
        testArrayECicli();
        
        // Test 5: Gestione eccezioni base
        testGestioneEccezioni();
        
        // Riepilogo finale
        printRiepilogo();
    }
    
    /**
     * Test delle informazioni della JVM
     */
    private static void testJVM() {
        System.out.println("\n✅ TEST 1: Informazioni JVM");
        System.out.println("   Versione Java: " + System.getProperty("java.version"));
        System.out.println("   Runtime: " + System.getProperty("java.runtime.name"));
        System.out.println("   Venditore: " + System.getProperty("java.vendor"));
        System.out.println("   Home Directory: " + System.getProperty("java.home"));
    }
    
    /**
     * Test delle operazioni matematiche di base
     */
    private static void testOperazioniMatematiche() {
        System.out.println("\n✅ TEST 2: Operazioni Matematiche");
        
        int a = 15;
        int b = 7;
        
        System.out.println("   " + a + " + " + b + " = " + (a + b));
        System.out.println("   " + a + " - " + b + " = " + (a - b));
        System.out.println("   " + a + " * " + b + " = " + (a * b));
        System.out.println("   " + a + " / " + b + " = " + (a / b));
        System.out.println("   " + a + " % " + b + " = " + (a % b));
        
        // Test con numeri decimali
        double x = 3.14159;
        System.out.println("   π ≈ " + x);
        System.out.println("   Area cerchio (r=5): " + (x * 5 * 5));
    }
    
    /**
     * Test della gestione delle stringhe
     */
    private static void testGestioneStringhe() {
        System.out.println("\n✅ TEST 3: Gestione Stringhe");
        
        String messaggio = "Java Essential by Example";
        System.out.println("   Stringa originale: " + messaggio);
        System.out.println("   Lunghezza: " + messaggio.length());
        System.out.println("   Maiuscolo: " + messaggio.toUpperCase());
        System.out.println("   Minuscolo: " + messaggio.toLowerCase());
        System.out.println("   Contiene 'Java': " + messaggio.contains("Java"));
        System.out.println("   Inizia con 'Java': " + messaggio.startsWith("Java"));
    }
    
    /**
     * Test di array e cicli
     */
    private static void testArrayECicli() {
        System.out.println("\n✅ TEST 4: Array e Cicli");
        
        // Array di numeri
        int[] numeri = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        System.out.print("   Array: ");
        for (int numero : numeri) {
            System.out.print(numero + " ");
        }
        System.out.println();
        
        // Calcolo somma e media
        int somma = 0;
        for (int numero : numeri) {
            somma += numero;
        }
        
        System.out.println("   Somma: " + somma);
        System.out.println("   Media: " + (somma / (double) numeri.length));
        
        // Array di stringhe
        String[] linguaggi = {"Java", "Python", "JavaScript", "C++", "Go"};
        System.out.print("   Linguaggi: ");
        for (String linguaggio : linguaggi) {
            System.out.print(linguaggio + " ");
        }
        System.out.println();
    }
    
    /**
     * Test base della gestione delle eccezioni
     */
    private static void testGestioneEccezioni() {
        System.out.println("\n✅ TEST 5: Gestione Eccezioni");
        
        try {
            // Operazione che potrebbe causare un'eccezione
            int risultato = 10 / 2;
            System.out.println("   10 / 2 = " + risultato + " (OK)");
            
            // Test con divisione per zero (commentato per evitare l'eccezione)
            // int errore = 10 / 0; // Causerebbe ArithmeticException
            
            // Test accesso array
            int[] array = {1, 2, 3};
            System.out.println("   array[1] = " + array[1] + " (OK)");
            
        } catch (Exception e) {
            System.out.println("   Eccezione gestita: " + e.getMessage());
        }
        
        System.out.println("   Gestione eccezioni: FUNZIONANTE");
    }
    
    /**
     * Stampa il riepilogo finale dei test
     */
    private static void printRiepilogo() {
        System.out.println("\n" + "=".repeat(50));
        System.out.println("🎉 RIEPILOGO TEST INSTALLAZIONE");
        System.out.println("=".repeat(50));
        System.out.println("✅ JVM: FUNZIONANTE");
        System.out.println("✅ Operazioni matematiche: FUNZIONANTI");
        System.out.println("✅ Gestione stringhe: FUNZIONANTE");
        System.out.println("✅ Array e cicli: FUNZIONANTI");
        System.out.println("✅ Gestione eccezioni: FUNZIONANTE");
        System.out.println("\n🚀 La tua installazione Java è COMPLETA e FUNZIONANTE!");
        System.out.println("   Sei pronto per iniziare il tuo viaggio in Java!");
        
        // Informazioni per principianti
        System.out.println("\n💡 PROSSIMI PASSI:");
        System.out.println("   1. Installa un IDE (IntelliJ IDEA, Eclipse, VS Code)");
        System.out.println("   2. Crea il tuo primo progetto Java");
        System.out.println("   3. Continua con il Modulo B - Problemi ed Algoritmi");
        
        System.out.println("\n📚 Buono studio con Java Essential by Example!");
    }
}

/*
 * COME UTILIZZARE QUESTO PROGRAMMA:
 * 
 * 1. Compilare: javac TestInstallazione.java
 * 2. Eseguire: java TestInstallazione
 * 3. Verificare che tutti i test mostrino "FUNZIONANTE"
 * 
 * SE QUALCOSA NON FUNZIONA:
 * - Verificare che Java sia installato correttamente
 * - Controllare le variabili d'ambiente JAVA_HOME e PATH
 * - Assicurarsi di usare una versione Java 8 o superiore
 * 
 * QUESTO PROGRAMMA DIMOSTRA:
 * - Metodi statici e organizzazione del codice
 * - Operazioni con diversi tipi di dati
 * - Cicli for e for-each
 * - Gestione base delle eccezioni
 * - Formattazione dell'output
 * - Uso delle proprietà di sistema
 */
