/**
 * ESERCIZIO C.1 - Calcolatrice Scientifica
 * 
 * OBIETTIVO:
 * Creare una calcolatrice che gestisce diversi tipi di dati primitivi
 * e dimostra l'uso corretto di operatori e conversioni di tipo.
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 1. Operazioni aritmetiche base (+, -, *, /, %)
 * 2. Operazioni matematiche avanzate (potenza, radice, trigonometria)
 * 3. Conversioni tra diversi tipi numerici
 * 4. Gestione dell'input utente con validazione
 * 5. Formattazione dell'output per diversi tipi
 * 
 * CONCETTI APPLICATI:
 * - Tutti i tipi di dati primitivi numerici
 * - Casting esplicito e implicito
 * - Operatori aritmetici e di assegnazione
 * - Input/Output formattato
 * - Gestione degli errori di input
 * 
 * @author Studente
 * @version 1.0
 */

import java.util.Scanner;
import java.text.DecimalFormat;

public class Esercizio01_CalcolatriceScientifica {
    
    // Costanti matematiche
    private static final double PI = Math.PI;
    private static final double E = Math.E;
    
    // Formatter per l'output
    private static final DecimalFormat df = new DecimalFormat("#.####");
    
    private static Scanner scanner = new Scanner(System.in);
    
    /**
     * Menu principale della calcolatrice
     */
    public static void main(String[] args) {
        System.out.println("=== CALCOLATRICE SCIENTIFICA ===");
        System.out.println("Esercizio C.1 - Tipi di Dati e Operatori\n");
        
        boolean continua = true;
        while (continua) {
            mostraMenu();
            int scelta = leggiIntero("Inserisci la tua scelta: ");
            
            switch (scelta) {
                case 1:
                    operazioniBase();
                    break;
                case 2:
                    operazioniAvanzate();
                    break;
                case 3:
                    conversioniTipo();
                    break;
                case 4:
                    operazioniLogiche();
                    break;
                case 5:
                    testTipiDati();
                    break;
                case 0:
                    continua = false;
                    System.out.println("Arrivederci!");
                    break;
                default:
                    System.out.println("❌ Scelta non valida!");
            }
            System.out.println();
        }
        
        scanner.close();
    }
    
    /**
     * Mostra il menu delle operazioni
     */
    private static void mostraMenu() {
        System.out.println("=== MENU CALCOLATRICE ===");
        System.out.println("1. Operazioni base (+, -, *, /, %)");
        System.out.println("2. Operazioni avanzate (potenza, radice, trig)");
        System.out.println("3. Conversioni di tipo");
        System.out.println("4. Operazioni logiche e bit");
        System.out.println("5. Test tipi di dati");
        System.out.println("0. Esci");
        System.out.println("========================");
    }
    
    /**
     * TODO 1: Implementare operazioni aritmetiche base
     * OPERAZIONI DA GESTIRE:
     * - Addizione, sottrazione, moltiplicazione
     * - Divisione (gestire divisione per zero)
     * - Modulo
     * - Gestire overflow e underflow
     */
    private static void operazioniBase() {
        System.out.println("=== OPERAZIONI ARITMETICHE BASE ===");
        
        // TODO: Leggere due numeri (double per precisione)
        double a = leggiDouble("Inserisci il primo numero: ");
        double b = leggiDouble("Inserisci il secondo numero: ");
        
        System.out.println("\n📊 RISULTATI:");
        
        // TODO: Implementare e visualizzare tutte le operazioni
        // Addizione
        double somma = a + b;
        System.out.println("➕ " + a + " + " + b + " = " + df.format(somma));
        
        // TODO: Completare con sottrazione, moltiplicazione, divisione, modulo
        // Gestire il caso di divisione per zero
        
        // TODO: Mostrare anche risultati con tipi interi per confronto
        System.out.println("\n🔢 CONFRONTO CON INTERI:");
        int intA = (int) a;
        int intB = (int) b;
        System.out.println("Come interi: " + intA + " e " + intB);
        // Mostrare differenze nei risultati
    }
    
    /**
     * TODO 2: Implementare operazioni matematiche avanzate
     * OPERAZIONI DA IMPLEMENTARE:
     * - Potenza (Math.pow)
     * - Radice quadrata (Math.sqrt)
     * - Logaritmi (Math.log, Math.log10)
     * - Funzioni trigonometriche (sin, cos, tan)
     */
    private static void operazioniAvanzate() {
        System.out.println("=== OPERAZIONI MATEMATICHE AVANZATE ===");
        
        double numero = leggiDouble("Inserisci un numero: ");
        
        System.out.println("\n📐 RISULTATI AVANZATI per " + df.format(numero) + ":");
        
        // TODO: Implementare tutte le operazioni avanzate
        // Potenza
        double quadrato = Math.pow(numero, 2);
        double cubo = Math.pow(numero, 3);
        System.out.println("Quadrato: " + df.format(quadrato));
        System.out.println("Cubo: " + df.format(cubo));
        
        // TODO: Aggiungere radice quadrata, logaritmi, trigonometria
        // Gestire numeri negativi dove appropriato
        
        // TODO: Operazioni con due numeri
        System.out.println("\n🔄 OPERAZIONI CON DUE NUMERI:");
        double secondo = leggiDouble("Inserisci il secondo numero: ");
        
        // Potenza personalizzata
        double potenza = Math.pow(numero, secondo);
        System.out.println(df.format(numero) + " ^ " + df.format(secondo) + " = " + df.format(potenza));
        
        // TODO: Aggiungere altre operazioni a due operandi
    }
    
    /**
     * TODO 3: Implementare esempi di conversioni di tipo
     * CONVERSIONI DA DIMOSTRARE:
     * - Casting implicito (widening)
     * - Casting esplicito (narrowing)
     * - Perdita di precisione
     * - Overflow e underflow
     */
    private static void conversioniTipo() {
        System.out.println("=== CONVERSIONI DI TIPO ===");
        
        System.out.println("🔄 ESEMPI DI CASTING:");
        
        // TODO: Dimostrare casting implicito
        System.out.println("\n1. CASTING IMPLICITO (Widening):");
        byte valoreByte = 100;
        short valoreShort = valoreByte; // byte -> short
        int valoreInt = valoreShort;    // short -> int
        long valoreLong = valoreInt;    // int -> long
        float valoreFloat = valoreLong; // long -> float
        double valoreDouble = valoreFloat; // float -> double
        
        System.out.println("byte(" + valoreByte + ") -> short(" + valoreShort + 
                          ") -> int(" + valoreInt + ") -> long(" + valoreLong + 
                          ") -> float(" + valoreFloat + ") -> double(" + valoreDouble + ")");
        
        // TODO: Dimostrare casting esplicito e perdita di precisione
        System.out.println("\n2. CASTING ESPLICITO (Narrowing):");
        double numeroGrande = 1234.5678;
        // TODO: Convertire step by step verso tipi più piccoli
        // Mostrare la perdita di precisione ad ogni passo
        
        // TODO: Esempi di overflow
        System.out.println("\n3. OVERFLOW/UNDERFLOW:");
        // Dimostrare overflow con byte, short, int
        
        // TODO: Conversioni stringa-numero
        System.out.println("\n4. CONVERSIONI STRINGA-NUMERO:");
        String numeroStringa = "12345";
        // Convertire in diversi tipi numerici
    }
    
    /**
     * TODO 4: Implementare operazioni logiche e bit-wise
     * OPERAZIONI DA IMPLEMENTARE:
     * - Operatori logici (&&, ||, !)
     * - Operatori di confronto (<, >, ==, !=, <=, >=)
     * - Operatori bit-wise (&, |, ^, ~, <<, >>)
     */
    private static void operazioniLogiche() {
        System.out.println("=== OPERAZIONI LOGICHE E BIT-WISE ===");
        
        // TODO: Operazioni logiche con boolean
        boolean a = true;
        boolean b = false;
        
        System.out.println("🔍 OPERATORI LOGICI:");
        System.out.println("a = " + a + ", b = " + b);
        // TODO: Mostrare tutti gli operatori logici
        
        // TODO: Operazioni di confronto
        System.out.println("\n📊 OPERATORI DI CONFRONTO:");
        int x = leggiIntero("Inserisci primo numero intero: ");
        int y = leggiIntero("Inserisci secondo numero intero: ");
        
        // TODO: Mostrare tutti i confronti possibili
        
        // TODO: Operazioni bit-wise
        System.out.println("\n💻 OPERATORI BIT-WISE:");
        System.out.println("x = " + x + " (binario: " + Integer.toBinaryString(x) + ")");
        System.out.println("y = " + y + " (binario: " + Integer.toBinaryString(y) + ")");
        
        // TODO: Implementare tutte le operazioni bit-wise
    }
    
    /**
     * TODO 5: Test completo di tutti i tipi di dati primitivi
     * TIPI DA TESTARE:
     * - byte, short, int, long
     * - float, double
     * - char
     * - boolean
     */
    private static void testTipiDati() {
        System.out.println("=== TEST TIPI DI DATI PRIMITIVI ===");
        
        // TODO: Mostrare range e caratteristiche di ogni tipo
        System.out.println("📏 RANGE DEI TIPI NUMERICI:");
        
        // byte
        System.out.println("byte: " + Byte.MIN_VALUE + " to " + Byte.MAX_VALUE);
        // TODO: Completare per tutti i tipi
        
        // TODO: Test pratici con input utente
        System.out.println("\n🧪 TEST PRATICI:");
        
        // Test byte
        System.out.println("\n1. TEST BYTE:");
        int valoreTentativo = leggiIntero("Inserisci un valore per byte (-128 a 127): ");
        // TODO: Verificare se il valore rientra nel range di byte
        // Se sì, convertire e mostrare; se no, spiegare il problema
        
        // TODO: Ripetere per short, int, long
        
        // TODO: Test char
        System.out.println("\n5. TEST CHAR:");
        System.out.print("Inserisci un carattere: ");
        String input = scanner.nextLine();
        if (input.length() > 0) {
            char carattere = input.charAt(0);
            System.out.println("Carattere: '" + carattere + "' -> Valore ASCII: " + (int)carattere);
        }
        
        // TODO: Test boolean
        System.out.println("\n6. TEST BOOLEAN:");
        // Esempi di operazioni che restituiscono boolean
    }
    
    /**
     * Metodo di utilità per leggere un intero con gestione errori
     */
    private static int leggiIntero(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextInt()) {
            System.out.print("❌ Inserisci un numero intero valido: ");
            scanner.next();
        }
        int numero = scanner.nextInt();
        scanner.nextLine(); // Consuma newline
        return numero;
    }
    
    /**
     * Metodo di utilità per leggere un double con gestione errori
     */
    private static double leggiDouble(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextDouble()) {
            System.out.print("❌ Inserisci un numero valido: ");
            scanner.next();
        }
        double numero = scanner.nextDouble();
        scanner.nextLine(); // Consuma newline
        return numero;
    }
    
    /**
     * TODO BONUS: Funzionalità aggiuntive da implementare
     * 
     * 1. CALCOLATRICE CON MEMORIA:
     *    - Variabili per memorizzare risultati
     *    - Operazioni su memoria (M+, M-, MR, MC)
     * 
     * 2. CONVERSIONI NUMERICHE:
     *    - Binario, ottale, esadecimale
     *    - Conversioni tra basi numeriche
     * 
     * 3. OPERAZIONI SU ARRAY:
     *    - Calcolo media, somma, min, max
     *    - Operazioni elemento per elemento
     * 
     * 4. FORMATTAZIONE AVANZATA:
     *    - Notazione scientifica
     *    - Valute e percentuali
     *    - Localizzazione numerica
     * 
     * 5. VALIDAZIONE ROBUSTA:
     *    - Gestione eccezioni
     *    - Input da file
     *    - Cronologia operazioni
     */
}
