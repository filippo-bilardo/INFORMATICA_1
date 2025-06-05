/**
 * Esempi pratici su variabili, costanti e operatori in Java
 * 
 * Questo file dimostra:
 * - Dichiarazione e scope delle variabili
 * - Uso corretto delle costanti
 * - Tutti gli operatori Java con esempi pratici
 * - Precedenza e associatività
 * - Best practices e errori comuni
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class VariabiliOperatoriEsempi {
    
    // Variabili di classe (statiche)
    private static int contatore = 0;
    public static final String NOME_APPLICAZIONE = "Esempi Java";
    public static final double VERSIONE = 1.0;
    
    // Variabili di istanza
    private String nome;
    private int eta;
    private final long id; // Costante di istanza
    
    // Costruttore
    public VariabiliOperatoriEsempi(String nome, int eta) {
        this.nome = nome;
        this.eta = eta;
        this.id = ++contatore; // Assegnazione una sola volta
    }
    
    public static void main(String[] args) {
        System.out.println("=== ESEMPI VARIABILI E OPERATORI ===\n");
        
        // Esegui tutti gli esempi
        esempiVariabiliLocali();
        esempiCostanti();
        esempiOperatoriAritmetici();
        esempiOperatoriConfronto();
        esempiOperatoriLogici();
        esempiOperatoriBitwise();
        esempiOperatoriSpeciali();
        esempiPrecedenza();
        esempiScope();
        esempiBestPractices();
        esempiErroriComuni();
    }
    
    /**
     * Dimostra l'uso delle variabili locali
     */
    public static void esempiVariabiliLocali() {
        System.out.println("--- VARIABILI LOCALI ---");
        
        // Dichiarazione e inizializzazione
        int numero = 42;                    // Dichiarazione + inizializzazione
        String messaggio;                   // Solo dichiarazione
        messaggio = "Ciao mondo!";          // Inizializzazione successiva
        
        // Dichiarazioni multiple dello stesso tipo
        int x = 10, y = 20, z = 30;
        double altezza = 1.75, peso = 70.5;
        
        // Variabili in blocchi
        if (true) {
            int variabileBlocco = 100;      // Visibile solo nel blocco if
            System.out.printf("Nel blocco: %d%n", variabileBlocco);
        }
        // variabileBlocco non accessibile qui
        
        // Variabili nel ciclo for
        for (int i = 0; i < 3; i++) {       // i ha scope solo nel for
            int temp = i * 2;               // temp ha scope solo nel for
            System.out.printf("Ciclo %d: temp = %d%n", i, temp);
        }
        // i e temp non accessibili qui
        
        System.out.printf("Numero: %d, Messaggio: %s%n", numero, messaggio);
        System.out.printf("Coordinate: x=%d, y=%d, z=%d%n", x, y, z);
        System.out.printf("Dati fisici: altezza=%.2f, peso=%.1f%n", altezza, peso);
        System.out.println();
    }
    
    /**
     * Dimostra l'uso delle costanti
     */
    public static void esempiCostanti() {
        System.out.println("--- COSTANTI ---");
        
        // Costanti locali
        final double PI = 3.14159265359;
        final int GIORNI_SETTIMANA = 7;
        final String SALUTO = "Benvenuto";
        
        // Costanti di classe (definite sopra)
        System.out.printf("Applicazione: %s v%.1f%n", NOME_APPLICAZIONE, VERSIONE);
        
        // Uso delle costanti
        double raggio = 5.0;
        double area = PI * raggio * raggio;
        double circonferenza = 2 * PI * raggio;
        
        System.out.printf("Cerchio con raggio %.1f:%n", raggio);
        System.out.printf("  Area: %.2f%n", area);
        System.out.printf("  Circonferenza: %.2f%n", circonferenza);
        
        // Costanti per configurazione
        final int MAX_TENTATIVI = 3;
        final double SOGLIA_ERRORE = 0.001;
        final boolean DEBUG_MODE = true;
        
        if (DEBUG_MODE) {
            System.out.printf("Debug: MAX_TENTATIVI=%d, SOGLIA_ERRORE=%.3f%n", 
                            MAX_TENTATIVI, SOGLIA_ERRORE);
        }
        
        // Costanti per collections (il riferimento è final, non il contenuto)
        final java.util.List<String> COLORI = java.util.Arrays.asList("rosso", "verde", "blu");
        System.out.printf("Colori primari: %s%n", COLORI);
        // COLORI = new ArrayList<>(); // ERRORE! Non posso riassegnare
        // COLORI.add("giallo");       // OK! Posso modificare il contenuto
        
        System.out.println();
    }
    
    /**
     * Dimostra gli operatori aritmetici
     */
    public static void esempiOperatoriAritmetici() {
        System.out.println("--- OPERATORI ARITMETICI ---");
        
        int a = 17, b = 5;
        
        // Operatori base
        System.out.printf("a = %d, b = %d%n", a, b);
        System.out.printf("a + b = %d%n", a + b);       // 22
        System.out.printf("a - b = %d%n", a - b);       // 12
        System.out.printf("a * b = %d%n", a * b);       // 85
        System.out.printf("a / b = %d%n", a / b);       // 3 (divisione intera!)
        System.out.printf("a %% b = %d%n", a % b);      // 2 (resto/modulo)
        
        // Divisione con decimali
        double divisione = (double) a / b;
        System.out.printf("a / b (decimale) = %.3f%n", divisione); // 3.400
        
        // Incremento e decremento
        int x = 10;
        System.out.printf("x iniziale: %d%n", x);
        System.out.printf("x++ (post): %d, x ora: %d%n", x++, x);   // 10, 11
        System.out.printf("++x (pre): %d, x ora: %d%n", ++x, x);    // 12, 12
        System.out.printf("x-- (post): %d, x ora: %d%n", x--, x);   // 12, 11
        System.out.printf("--x (pre): %d, x ora: %d%n", --x, x);    // 10, 10
        
        // Operatori di assegnazione composta
        int y = 100;
        System.out.printf("y iniziale: %d%n", y);
        y += 50;    System.out.printf("y += 50: %d%n", y);      // 150
        y -= 30;    System.out.printf("y -= 30: %d%n", y);      // 120
        y *= 2;     System.out.printf("y *= 2: %d%n", y);       // 240
        y /= 3;     System.out.printf("y /= 3: %d%n", y);       // 80
        y %= 7;     System.out.printf("y %%= 7: %d%n", y);      // 3
        
        // Operatori unari
        int positivo = 42;
        int negativo = -positivo;
        int positivoAgain = +negativo; // Raramente usato
        
        System.out.printf("Unari: +%d = %d, -%d = %d%n", positivo, positivo, positivo, negativo);
        
        System.out.println();
    }
    
    /**
     * Dimostra gli operatori di confronto
     */
    public static void esempiOperatoriConfronto() {
        System.out.println("--- OPERATORI DI CONFRONTO ---");
        
        int a = 10, b = 20, c = 10;
        
        System.out.printf("a = %d, b = %d, c = %d%n", a, b, c);
        System.out.printf("a == b: %b%n", a == b);      // false
        System.out.printf("a == c: %b%n", a == c);      // true
        System.out.printf("a != b: %b%n", a != b);      // true
        System.out.printf("a < b: %b%n", a < b);        // true
        System.out.printf("a <= c: %b%n", a <= c);      // true
        System.out.printf("b > a: %b%n", b > a);        // true
        System.out.printf("a >= c: %b%n", a >= c);      // true
        
        // Confronti con decimali
        double x = 3.14, y = 3.14;
        System.out.printf("%.2f == %.2f: %b%n", x, y, x == y); // true
        
        // ⚠️ Attenzione con i confronti di double!
        double risultato = 0.1 + 0.2;
        boolean uguale = risultato == 0.3;
        System.out.printf("0.1 + 0.2 == 0.3: %b (%.17f)%n", uguale, risultato);
        
        // Metodo corretto per confrontare double
        double epsilon = 1e-10;
        boolean ugualeCorretto = Math.abs(risultato - 0.3) < epsilon;
        System.out.printf("Confronto corretto: %b%n", ugualeCorretto);
        
        // Confronti con String (IMPORTANTE!)
        String str1 = "ciao";
        String str2 = "ciao";
        String str3 = new String("ciao");
        
        System.out.printf("\"%s\" == \"%s\": %b%n", str1, str2, str1 == str2);     // true (pool stringhe)
        System.out.printf("\"%s\" == \"%s\": %b%n", str1, str3, str1 == str3);     // false (oggetti diversi!)
        System.out.printf("\"%s\".equals(\"%s\"): %b%n", str1, str3, str1.equals(str3)); // true (contenuto)
        
        System.out.println();
    }
    
    /**
     * Dimostra gli operatori logici
     */
    public static void esempiOperatoriLogici() {
        System.out.println("--- OPERATORI LOGICI ---");
        
        boolean a = true, b = false;
        
        // Operatori logici base
        System.out.printf("a = %b, b = %b%n", a, b);
        System.out.printf("a && b: %b%n", a && b);      // false (AND)
        System.out.printf("a || b: %b%n", a || b);      // true (OR)
        System.out.printf("!a: %b%n", !a);             // false (NOT)
        System.out.printf("!b: %b%n", !b);             // true (NOT)
        
        // XOR (OR esclusivo)
        System.out.printf("a ^ b: %b%n", a ^ b);        // true (XOR)
        
        // Short-circuit evaluation
        System.out.println("\nShort-circuit evaluation:");
        int x = 0;
        
        // && - Se il primo è false, il secondo non viene valutato
        boolean risultato1 = (x != 0) && (10 / x > 2);
        System.out.printf("(x != 0) && (10 / x > 2): %b (nessuna divisione per zero!)%n", risultato1);
        
        // || - Se il primo è true, il secondo non viene valutato
        boolean risultato2 = (x == 0) || (10 / x > 2);
        System.out.printf("(x == 0) || (10 / x > 2): %b (nessuna divisione per zero!)%n", risultato2);
        
        // Esempio pratico con null
        String testo = null;
        boolean testoValido = (testo != null) && (testo.length() > 0);
        System.out.printf("Testo valido: %b (nessuna NullPointerException!)%n", testoValido);
        
        // Operatori bitwise vs logici (NON short-circuit)
        System.out.println("\nOperatori bitwise (NON short-circuit):");
        try {
            // boolean risultato3 = false & (10 / 0 > 2); // Causerebbe ArithmeticException!
            System.out.println("Gli operatori & e | valutano sempre entrambi gli operandi");
        } catch (ArithmeticException e) {
            System.out.println("Divisione per zero rilevata!");
        }
        
        System.out.println();
    }
    
    /**
     * Dimostra gli operatori bitwise
     */
    public static void esempiOperatoriBitwise() {
        System.out.println("--- OPERATORI BITWISE ---");
        
        int a = 12;  // 1100 in binario
        int b = 10;  // 1010 in binario
        
        System.out.printf("a = %d (%s)%n", a, Integer.toBinaryString(a));
        System.out.printf("b = %d (%s)%n", b, Integer.toBinaryString(b));
        
        // Operatori bitwise
        int and = a & b;    // 1000 = 8
        int or = a | b;     // 1110 = 14
        int xor = a ^ b;    // 0110 = 6
        int not = ~a;       // Inverte tutti i bit
        
        System.out.printf("a & b = %d (%s)%n", and, Integer.toBinaryString(and));
        System.out.printf("a | b = %d (%s)%n", or, Integer.toBinaryString(or));
        System.out.printf("a ^ b = %d (%s)%n", xor, Integer.toBinaryString(xor));
        System.out.printf("~a = %d%n", not);
        
        // Operatori di shift
        int leftShift = a << 2;     // Shift a sinistra di 2 posizioni
        int rightShift = a >> 2;    // Shift a destra di 2 posizioni (con segno)
        int unsignedShift = a >>> 2; // Shift a destra senza segno
        
        System.out.printf("a << 2 = %d (moltiplicazione per 4)%n", leftShift);
        System.out.printf("a >> 2 = %d (divisione per 4)%n", rightShift);
        System.out.printf("a >>> 2 = %d%n", unsignedShift);
        
        // Usi pratici
        System.out.println("\nUsi pratici:");
        
        // Controllo se un numero è pari
        int numero = 17;
        boolean isPari = (numero & 1) == 0;
        System.out.printf("%d è pari: %b%n", numero, isPari);
        
        // Moltiplicazione/divisione veloce per potenze di 2
        int veloce4x = numero << 2;     // numero * 4
        int veloceDiv8 = numero >> 3;   // numero / 8
        System.out.printf("%d * 4 = %d (shift), %d / 8 = %d (shift)%n", 
                         numero, veloce4x, numero, veloceDiv8);
        
        // Operazioni con flag/permessi
        final int READ = 1;      // 001
        final int WRITE = 2;     // 010
        final int EXECUTE = 4;   // 100
        
        int permissions = READ | WRITE;  // 011 = 3
        System.out.printf("Permessi: %d (%s)%n", permissions, Integer.toBinaryString(permissions));
        
        boolean canRead = (permissions & READ) != 0;
        boolean canWrite = (permissions & WRITE) != 0;
        boolean canExecute = (permissions & EXECUTE) != 0;
        
        System.out.printf("Può leggere: %b, scrivere: %b, eseguire: %b%n", 
                         canRead, canWrite, canExecute);
        
        System.out.println();
    }
    
    /**
     * Dimostra gli operatori speciali
     */
    public static void esempiOperatoriSpeciali() {
        System.out.println("--- OPERATORI SPECIALI ---");
        
        // Operatore ternario
        int eta = 25;
        String categoria = (eta >= 18) ? "Adulto" : "Minorenne";
        System.out.printf("Età %d: %s%n", eta, categoria);
        
        // Operatore ternario annidato (sconsigliato per leggibilità)
        String fascia = (eta < 13) ? "Bambino" : 
                       (eta < 18) ? "Adolescente" : 
                       (eta < 65) ? "Adulto" : "Senior";
        System.out.printf("Fascia età: %s%n", fascia);
        
        // Operatore ternario con espressioni
        int a = 10, b = 20;
        int max = (a > b) ? a : b;
        int min = (a < b) ? a : b;
        String confronto = (a == b) ? "uguali" : (a > b) ? "a > b" : "a < b";
        
        System.out.printf("Max(%d, %d) = %d%n", a, b, max);
        System.out.printf("Min(%d, %d) = %d%n", a, b, min);
        System.out.printf("Confronto: %s%n", confronto);
        
        // Operatore instanceof
        Object obj1 = "Ciao";
        Object obj2 = 42;
        Object obj3 = 3.14;
        
        System.out.printf("\"%s\" instanceof String: %b%n", obj1, obj1 instanceof String);
        System.out.printf("%s instanceof Integer: %b%n", obj2, obj2 instanceof Integer);
        System.out.printf("%s instanceof Double: %b%n", obj3, obj3 instanceof Double);
        System.out.printf("%s instanceof Number: %b%n", obj2, obj2 instanceof Number);
        
        // Uso sicuro di instanceof con cast
        if (obj1 instanceof String) {
            String str = (String) obj1;
            System.out.printf("Lunghezza stringa: %d%n", str.length());
        }
        
        System.out.println();
    }
    
    /**
     * Dimostra la precedenza degli operatori
     */
    public static void esempiPrecedenza() {
        System.out.println("--- PRECEDENZA OPERATORI ---");
        
        // Aritmetici
        int risultato1 = 2 + 3 * 4;         // 14, non 20 (* ha precedenza su +)
        int risultato2 = (2 + 3) * 4;       // 20 (parentesi forzano precedenza)
        
        System.out.printf("2 + 3 * 4 = %d%n", risultato1);
        System.out.printf("(2 + 3) * 4 = %d%n", risultato2);
        
        // Confronto e logici
        boolean test1 = 5 > 3 && 2 < 4;     // true (prima i confronti, poi &&)
        boolean test2 = true || false && false; // true (&& ha precedenza su ||)
        
        System.out.printf("5 > 3 && 2 < 4 = %b%n", test1);
        System.out.printf("true || false && false = %b%n", test2);
        
        // Assegnazione (precedenza più bassa)
        int x, y, z;
        x = y = z = 10;                     // Assegnazione da destra a sinistra
        System.out.printf("x = y = z = 10: x=%d, y=%d, z=%d%n", x, y, z);
        
        // Espressioni complesse
        int a = 5, b = 3, c = 2;
        boolean complesso = a > b && b > c || a == 5;
        // Equivale a: ((a > b) && (b > c)) || (a == 5)
        System.out.printf("Espressione complessa: %b%n", complesso);
        
        // Con parentesi per chiarezza
        boolean chiaroE = (a > b) && (b > c);
        boolean chiaroO = chiaroE || (a == 5);
        System.out.printf("Con parentesi: %b%n", chiaroO);
        
        System.out.println();
    }
    
    /**
     * Dimostra lo scope delle variabili
     */
    public static void esempiScope() {
        System.out.println("--- SCOPE VARIABILI ---");
        
        // Variabile locale del metodo
        int variabileMetodo = 100;
        
        // Accesso a variabili di classe
        System.out.printf("Contatore (classe): %d%n", contatore);
        System.out.printf("Applicazione (classe): %s%n", NOME_APPLICAZIONE);
        
        // Blocco if
        if (true) {
            int variabileBlocco = 200;
            System.out.printf("Nel blocco if: %d%n", variabileBlocco);
            System.out.printf("Accesso variabile metodo: %d%n", variabileMetodo);
        }
        // variabileBlocco non accessibile qui
        
        // Ciclo for
        for (int i = 0; i < 3; i++) {
            int variabileCiclo = i * 10;
            System.out.printf("Ciclo %d: variabile = %d%n", i, variabileCiclo);
        }
        // i e variabileCiclo non accessibili qui
        
        // Shadowing (nascondere variabili)
        {
            int variabileMetodo = 300; // Nasconde la variabile del metodo
            System.out.printf("Variabile nascosta: %d%n", variabileMetodo);
        }
        System.out.printf("Variabile originale: %d%n", variabileMetodo);
        
        // Esempio con istanza
        VariabiliOperatoriEsempi esempio = new VariabiliOperatoriEsempi("Alice", 25);
        System.out.printf("Istanza creata: %s%n", esempio);
        
        System.out.println();
    }
    
    /**
     * Dimostra le best practices
     */
    public static void esempiBestPractices() {
        System.out.println("--- BEST PRACTICES ---");
        
        // 1. Inizializzazione esplicita
        int contatore = 0;              // ✓ Sempre inizializzare
        double totale = 0.0;            // ✓ Valore di default chiaro
        boolean completato = false;     // ✓ Stato iniziale esplicito
        
        // 2. Nomi descrittivi
        int numeroStudenti = 25;        // ✓ Nome descrittivo
        boolean isEmailValida = true;   // ✓ is/has per boolean
        final double TASSO_IVA = 0.22;  // ✓ UPPER_CASE per costanti
        
        // 3. Uso delle parentesi per chiarezza
        boolean condizione = (numeroStudenti > 20) && (isEmailValida || completato);
        double prezzo = (totale + TASSO_IVA) * 1.1; // Parentesi non necessarie ma chiare
        
        // 4. Evitare espressioni troppo complesse
        // ❌ Difficile da leggere
        // boolean complex = a > b && c < d || e == f && g != h;
        
        // ✓ Spezzare in parti più semplici
        boolean primaCondizione = numeroStudenti > 20;
        boolean secondaCondizione = isEmailValida || completato;
        boolean risultatoFinale = primaCondizione && secondaCondizione;
        
        System.out.printf("Studenti: %d, Condizioni: %b && %b = %b%n",
                         numeroStudenti, primaCondizione, secondaCondizione, risultatoFinale);
        
        // 5. Uso appropriato delle costanti
        final int MAX_RETRY = 3;
        final String ERROR_MESSAGE = "Operazione fallita";
        
        for (int tentativo = 1; tentativo <= MAX_RETRY; tentativo++) {
            if (tentativo == MAX_RETRY) {
                System.out.println(ERROR_MESSAGE);
            } else {
                System.out.printf("Tentativo %d di %d%n", tentativo, MAX_RETRY);
            }
        }
        
        System.out.println();
    }
    
    /**
     * Dimostra errori comuni e come evitarli
     */
    public static void esempiErroriComuni() {
        System.out.println("--- ERRORI COMUNI ---");
        
        // 1. Confronto di riferimenti vs contenuto
        System.out.println("1. Confronto String:");
        String str1 = new String("ciao");
        String str2 = new String("ciao");
        
        System.out.printf("str1 == str2: %b (confronta riferimenti!)%n", str1 == str2);
        System.out.printf("str1.equals(str2): %b (confronta contenuto)%n", str1.equals(str2));
        
        // 2. Divisione intera inaspettata
        System.out.println("\n2. Divisione intera:");
        int a = 5, b = 2;
        double risultatoSbagliato = a / b;          // 2.0 invece di 2.5!
        double risultatoCorretto = (double) a / b;  // 2.5
        
        System.out.printf("int/int: %.1f (sbagliato!)%n", risultatoSbagliato);
        System.out.printf("(double)int/int: %.1f (corretto)%n", risultatoCorretto);
        
        // 3. Overflow silenzioso
        System.out.println("\n3. Overflow:");
        int max = Integer.MAX_VALUE;
        int overflow = max + 1;                     // Overflow silenzioso!
        
        System.out.printf("Max int: %,d%n", max);
        System.out.printf("Max + 1: %,d (overflow!)%n", overflow);
        
        // Controllo overflow
        try {
            int safe = Math.addExact(max, 1);
        } catch (ArithmeticException e) {
            System.out.println("✓ Overflow rilevato con Math.addExact()");
        }
        
        // 4. Confronto floating point
        System.out.println("\n4. Confronto floating point:");
        double risultato = 0.1 + 0.2;
        boolean sbagliato = risultato == 0.3;      // false!
        boolean corretto = Math.abs(risultato - 0.3) < 1e-10;
        
        System.out.printf("0.1 + 0.2 == 0.3: %b (sbagliato!)%n", sbagliato);
        System.out.printf("Confronto con epsilon: %b (corretto)%n", corretto);
        
        // 5. Variabili non inizializzate
        System.out.println("\n5. Variabili non inizializzate:");
        int valore = 0; // ✓ Sempre inizializzare le variabili locali
        // int valore; // ❌ Causerebbe errore di compilazione se usata
        System.out.printf("Valore inizializzato: %d%n", valore);
        
        System.out.println("\n✓ Esempi di errori comuni completati!");
    }
    
    @Override
    public String toString() {
        return String.format("Persona{id=%d, nome='%s', eta=%d}", id, nome, eta);
    }
}
