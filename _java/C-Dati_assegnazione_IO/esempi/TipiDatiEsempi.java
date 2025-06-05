/**
 * Esempi pratici sui tipi di dati primitivi in Java
 * 
 * Questo file dimostra:
 * - Uso di tutti i tipi primitivi
 * - Conversioni e casting
 * - Valori limite e overflow
 * - Best practices per tipi di dati
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class TipiDatiEsempi {
    
    public static void main(String[] args) {
        System.out.println("=== ESEMPI TIPI DATI PRIMITIVI ===\n");
        
        // Esegui tutti gli esempi
        esempiTipiInteri();
        esempiTipiDecimali();
        esempiCaratteri();
        esempiBoolean();
        esempiConversioni();
        esempiValoriLimite();
        esempiOverflow();
        esempiBestPractices();
    }
    
    /**
     * Dimostra l'uso dei tipi numerici interi
     */
    public static void esempiTipiInteri() {
        System.out.println("--- TIPI INTERI ---");
        
        // byte: -128 a 127
        byte etaGatto = 12;
        byte temperaturaMinima = -40;
        
        // short: -32,768 a 32,767  
        short altitudineMetri = 8848; // Monte Everest
        short profondita = -11034;    // Fossa delle Marianne
        
        // int: tipo standard per interi
        int popolazione = 60_000_000;  // Italia (con separatori per leggibilità)
        int distanzaLuna = 384_400;    // km dalla Terra
        
        // long: per valori molto grandi
        long distanzaSole = 149_597_870_700L; // km dalla Terra (nota la L)
        long millisecondiAnno = 365L * 24 * 60 * 60 * 1000; // calcolo
        
        System.out.printf("Età gatto: %d anni%n", etaGatto);
        System.out.printf("Altitudine Everest: %,d metri%n", altitudineMetri);
        System.out.printf("Popolazione Italia: %,d abitanti%n", popolazione);
        System.out.printf("Distanza Sole: %,d km%n", distanzaSole);
        System.out.printf("Millisecondi in un anno: %,d%n", millisecondiAnno);
        System.out.println();
    }
    
    /**
     * Dimostra l'uso dei tipi decimali
     */
    public static void esempiTipiDecimali() {
        System.out.println("--- TIPI DECIMALI ---");
        
        // float: precisione singola (raramente usato)
        float temperaturaCorpo = 36.6f;     // Nota la 'f'
        float piGreco = 3.14159f;
        
        // double: tipo standard per decimali
        double costanteGravita = 9.80665;   // m/s²
        double numeroEuler = 2.718281828459045;
        double prezzoAzione = 127.89;
        
        // Notazione scientifica
        double velocitaLuce = 2.99792458e8;  // m/s
        double massaElettrone = 9.109e-31;   // kg
        
        System.out.printf("Temperatura corporea: %.1f°C%n", temperaturaCorpo);
        System.out.printf("Pi greco (float): %.5f%n", piGreco);
        System.out.printf("Costante di gravità: %.5f m/s²%n", costanteGravita);
        System.out.printf("Numero di Euler: %.15f%n", numeroEuler);
        System.out.printf("Velocità della luce: %.2e m/s%n", velocitaLuce);
        System.out.printf("Massa elettrone: %.3e kg%n", massaElettrone);
        System.out.println();
    }
    
    /**
     * Dimostra l'uso del tipo carattere
     */
    public static void esempiCaratteri() {
        System.out.println("--- TIPO CARATTERE ---");
        
        // Caratteri letterali
        char iniziale = 'M';
        char simbolo = '@';
        char cifra = '7';
        
        // Caratteri Unicode
        char euro = '\u20AC';        // €
        char cuore = '\u2665';       // ♥
        char alfa = '\u03B1';        // α
        
        // Caratteri di escape
        char tab = '\t';
        char newline = '\n';
        char virgolette = '\"';
        char apostrofo = '\'';
        char backslash = '\\';
        
        // Caratteri come numeri
        char A = 65;                 // Codice ASCII di 'A'
        char zero = 48;              // Codice ASCII di '0'
        
        System.out.printf("Iniziale: %c%n", iniziale);
        System.out.printf("Simbolo euro: %c (Unicode: \\u20AC)%n", euro);
        System.out.printf("Cuore: %c (Unicode: \\u2665)%n", cuore);
        System.out.printf("Alfa greco: %c (Unicode: \\u03B1)%n", alfa);
        System.out.printf("Carattere A da numero: %c (ASCII: %d)%n", A, (int)A);
        System.out.printf("Carattere 0 da numero: %c (ASCII: %d)%n", zero, (int)zero);
        
        // Operazioni aritmetiche con char
        char letteraSuccessiva = (char)(iniziale + 1);
        System.out.printf("Lettera dopo %c: %c%n", iniziale, letteraSuccessiva);
        System.out.println();
    }
    
    /**
     * Dimostra l'uso del tipo boolean
     */
    public static void esempiBoolean() {
        System.out.println("--- TIPO BOOLEAN ---");
        
        // Valori letterali
        boolean vero = true;
        boolean falso = false;
        
        // Da espressioni
        int eta = 25;
        boolean maggiorenne = eta >= 18;
        boolean minorenne = !maggiorenne;
        
        // Da confronti
        String password = "secret123";
        boolean passwordLunga = password.length() >= 8;
        boolean contieneCifre = password.matches(".*\\d.*");
        boolean passwordValida = passwordLunga && contieneCifre;
        
        System.out.printf("Maggiorenne (età %d): %b%n", eta, maggiorenne);
        System.out.printf("Password lunga: %b%n", passwordLunga);
        System.out.printf("Contiene cifre: %b%n", contieneCifre);
        System.out.printf("Password valida: %b%n", passwordValida);
        
        // Boolean in condizioni
        if (passwordValida) {
            System.out.println("✓ Password accettata");
        } else {
            System.out.println("✗ Password rifiutata");
        }
        System.out.println();
    }
    
    /**
     * Dimostra le conversioni tra tipi
     */
    public static void esempiConversioni() {
        System.out.println("--- CONVERSIONI DI TIPO ---");
        
        // Conversioni implicite (widening)
        System.out.println("Conversioni implicite (automatiche):");
        byte b = 100;
        short s = b;        // byte → short
        int i = s;          // short → int
        long l = i;         // int → long
        float f = l;        // long → float (possibile perdita precisione!)
        double d = f;       // float → double
        
        System.out.printf("byte %d → short %d → int %d → long %d → float %.1f → double %.1f%n",
                         b, s, i, l, f, d);
        
        // Conversioni esplicite (narrowing)
        System.out.println("\nConversioni esplicite (cast richiesto):");
        double prezzo = 19.99;
        float prezzoFloat = (float) prezzo;     // double → float
        long prezzoLong = (long) prezzo;        // double → long (troncamento!)
        int prezzoInt = (int) prezzo;           // double → int
        
        System.out.printf("Prezzo originale: %.2f%n", prezzo);
        System.out.printf("Come float: %.2f%n", prezzoFloat);
        System.out.printf("Come long: %d (parte decimale persa!)%n", prezzoLong);
        System.out.printf("Come int: %d (parte decimale persa!)%n", prezzoInt);
        
        // Conversioni char ↔ int
        System.out.println("\nConversioni char ↔ int:");
        char carattere = 'A';
        int codiceAscii = carattere;            // char → int (implicita)
        char nuovoCarattere = (char) (codiceAscii + 1); // int → char (esplicita)
        
        System.out.printf("Carattere '%c' ha codice ASCII %d%n", carattere, codiceAscii);
        System.out.printf("Carattere successivo: '%c'%n", nuovoCarattere);
        System.out.println();
    }
    
    /**
     * Dimostra i valori limite dei tipi primitivi
     */
    public static void esempiValoriLimite() {
        System.out.println("--- VALORI LIMITE ---");
        
        // Valori limite per interi
        System.out.println("Limiti tipi interi:");
        System.out.printf("byte: da %d a %d%n", Byte.MIN_VALUE, Byte.MAX_VALUE);
        System.out.printf("short: da %,d a %,d%n", Short.MIN_VALUE, Short.MAX_VALUE);
        System.out.printf("int: da %,d a %,d%n", Integer.MIN_VALUE, Integer.MAX_VALUE);
        System.out.printf("long: da %,d a %,d%n", Long.MIN_VALUE, Long.MAX_VALUE);
        
        // Valori limite per decimali
        System.out.println("\nLimiti tipi decimali:");
        System.out.printf("float: da %e a %e%n", Float.MIN_VALUE, Float.MAX_VALUE);
        System.out.printf("double: da %e a %e%n", Double.MIN_VALUE, Double.MAX_VALUE);
        
        // Valori speciali per float/double
        System.out.println("\nValori speciali:");
        double positiveInfinity = Double.POSITIVE_INFINITY;
        double negativeInfinity = Double.NEGATIVE_INFINITY;
        double notANumber = Double.NaN;
        
        System.out.printf("Infinito positivo: %f%n", positiveInfinity);
        System.out.printf("Infinito negativo: %f%n", negativeInfinity);
        System.out.printf("Not a Number: %f%n", notANumber);
        
        // Test dei valori speciali
        System.out.printf("1.0/0.0 = %f%n", 1.0/0.0);
        System.out.printf("Math.sqrt(-1) = %f%n", Math.sqrt(-1));
        System.out.println();
    }
    
    /**
     * Dimostra i problemi di overflow
     */
    public static void esempiOverflow() {
        System.out.println("--- PROBLEMI DI OVERFLOW ---");
        
        // Overflow con byte
        byte maxByte = Byte.MAX_VALUE;          // 127
        byte overflowByte = (byte)(maxByte + 1); // Overflow! Diventa -128
        
        System.out.printf("byte massimo: %d%n", maxByte);
        System.out.printf("byte massimo + 1: %d (overflow!)%n", overflowByte);
        
        // Overflow con int
        int maxInt = Integer.MAX_VALUE;         // 2,147,483,647
        int overflowInt = maxInt + 1;           // Overflow! Diventa -2,147,483,648
        
        System.out.printf("int massimo: %,d%n", maxInt);
        System.out.printf("int massimo + 1: %,d (overflow!)%n", overflowInt);
        
        // Prevenire overflow
        try {
            int safe = Math.addExact(maxInt, 1); // Lancia ArithmeticException
        } catch (ArithmeticException e) {
            System.out.println("✓ Overflow rilevato e gestito con Math.addExact()");
        }
        
        // Overflow con moltiplicazione
        int a = 100_000;
        int b = 50_000;
        long prodotto = (long) a * b;           // Cast per evitare overflow
        
        System.out.printf("Prodotto sicuro: %,d × %,d = %,d%n", a, b, prodotto);
        System.out.println();
    }
    
    /**
     * Dimostra le best practices per i tipi di dati
     */
    public static void esempiBestPractices() {
        System.out.println("--- BEST PRACTICES ---");
        
        // 1. Scelta del tipo appropriato
        System.out.println("1. Scelta del tipo appropriato:");
        int contatore = 0;                      // ✓ int per contatori normali
        long timestamp = System.currentTimeMillis(); // ✓ long per timestamp
        double prezzoEsatto = 19.99;            // ✓ double per calcoli precisi
        boolean attivo = false;                 // ✓ boolean per flag
        
        System.out.printf("   Timestamp: %,d ms%n", timestamp);
        System.out.printf("   Prezzo: %.2f€%n", prezzoEsatto);
        
        // 2. Uso delle costanti
        System.out.println("2. Uso delle costanti:");
        final double IVA = 0.22;                // ✓ Costante per valori fissi
        final int MAX_TENTATIVI = 3;            // ✓ Evita numeri magici
        final String VALUTA = "EUR";            // ✓ Costanti stringa
        
        double prezzoBase = 100.0;
        double prezzoConIva = prezzoBase * (1 + IVA);
        
        System.out.printf("   Prezzo base: %.2f %s%n", prezzoBase, VALUTA);
        System.out.printf("   Prezzo con IVA (%.0f%%): %.2f %s%n", IVA * 100, prezzoConIva, VALUTA);
        
        // 3. Inizializzazione esplicita
        System.out.println("3. Inizializzazione esplicita:");
        int somma = 0;                          // ✓ Sempre inizializzare
        double totale = 0.0;                    // ✓ Valore di default chiaro
        boolean trovato = false;                // ✓ Stato iniziale esplicito
        
        System.out.printf("   Valori iniziali: somma=%d, totale=%.1f, trovato=%b%n",
                         somma, totale, trovato);
        
        // 4. Naming conventions
        System.out.println("4. Naming conventions:");
        int numeroStudenti = 25;                // ✓ camelCase per variabili
        final double PI_GRECO = 3.14159;        // ✓ UPPER_CASE per costanti
        boolean isValidEmail = true;            // ✓ is/has per boolean
        
        System.out.printf("   Studenti: %d, Pi: %.5f, Email valida: %b%n",
                         numeroStudenti, PI_GRECO, isValidEmail);
        
        System.out.println("\n✓ Esempi completati con successo!");
    }
}
