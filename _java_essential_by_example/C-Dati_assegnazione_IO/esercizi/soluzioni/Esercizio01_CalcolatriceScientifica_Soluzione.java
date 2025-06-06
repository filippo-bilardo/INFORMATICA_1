/**
 * SOLUZIONE ESERCIZIO C.1 - Calcolatrice Scientifica
 * 
 * Implementazione completa della calcolatrice con tutti i tipi di dati
 * primitivi, operatori e conversioni.
 * 
 * @author Docente
 * @version 1.0
 */

import java.util.Scanner;
import java.text.DecimalFormat;

public class Esercizio01_CalcolatriceScientifica_Soluzione {
    
    private static final double PI = Math.PI;
    private static final double E = Math.E;
    private static final DecimalFormat df = new DecimalFormat("#.####");
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        System.out.println("=== CALCOLATRICE SCIENTIFICA - SOLUZIONE ===");
        System.out.println("Esercizio C.1 - Tipi di Dati e Operatori\n");
        
        boolean continua = true;
        while (continua) {
            mostraMenu();
            int scelta = leggiIntero("Inserisci la tua scelta: ");
            
            switch (scelta) {
                case 1: operazioniBase(); break;
                case 2: operazioniAvanzate(); break;
                case 3: conversioniTipo(); break;
                case 4: operazioniLogiche(); break;
                case 5: testTipiDati(); break;
                case 0: continua = false; System.out.println("Arrivederci!"); break;
                default: System.out.println("❌ Scelta non valida!");
            }
            System.out.println();
        }
        scanner.close();
    }
    
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
     * SOLUZIONE: Operazioni aritmetiche base complete
     */
    private static void operazioniBase() {
        System.out.println("=== OPERAZIONI ARITMETICHE BASE ===");
        
        double a = leggiDouble("Inserisci il primo numero: ");
        double b = leggiDouble("Inserisci il secondo numero: ");
        
        System.out.println("\n📊 RISULTATI:");
        
        // Addizione
        double somma = a + b;
        System.out.println("➕ " + a + " + " + b + " = " + df.format(somma));
        
        // Sottrazione
        double differenza = a - b;
        System.out.println("➖ " + a + " - " + b + " = " + df.format(differenza));
        
        // Moltiplicazione
        double prodotto = a * b;
        System.out.println("✖️ " + a + " * " + b + " = " + df.format(prodotto));
        
        // Divisione con controllo divisione per zero
        if (b != 0) {
            double quoziente = a / b;
            System.out.println("➗ " + a + " / " + b + " = " + df.format(quoziente));
        } else {
            System.out.println("➗ " + a + " / " + b + " = ❌ ERRORE: Divisione per zero!");
        }
        
        // Modulo (solo se b != 0)
        if (b != 0) {
            double resto = a % b;
            System.out.println("📐 " + a + " % " + b + " = " + df.format(resto));
        } else {
            System.out.println("📐 " + a + " % " + b + " = ❌ ERRORE: Modulo per zero!");
        }
        
        // Confronto con operazioni su interi
        System.out.println("\n🔢 CONFRONTO CON INTERI:");
        int intA = (int) a;
        int intB = (int) b;
        System.out.println("Come interi: " + intA + " e " + intB);
        
        if (intB != 0) {
            int sommaInt = intA + intB;
            int differenzaInt = intA - intB;
            int prodottoInt = intA * intB;
            int quozienteInt = intA / intB;
            int restoInt = intA % intB;
            
            System.out.println("Somma interi: " + sommaInt + " (vs double: " + df.format(somma) + ")");
            System.out.println("Divisione interi: " + quozienteInt + " (vs double: " + df.format(a/b) + ")");
            System.out.println("Resto interi: " + restoInt + " (vs double: " + df.format(a%b) + ")");
        }
    }
    
    /**
     * SOLUZIONE: Operazioni matematiche avanzate complete
     */
    private static void operazioniAvanzate() {
        System.out.println("=== OPERAZIONI MATEMATICHE AVANZATE ===");
        
        double numero = leggiDouble("Inserisci un numero: ");
        
        System.out.println("\n📐 RISULTATI AVANZATI per " + df.format(numero) + ":");
        
        // Potenze
        System.out.println("Quadrato: " + df.format(Math.pow(numero, 2)));
        System.out.println("Cubo: " + df.format(Math.pow(numero, 3)));
        
        // Radici
        if (numero >= 0) {
            System.out.println("Radice quadrata: " + df.format(Math.sqrt(numero)));
        } else {
            System.out.println("Radice quadrata: ❌ Non definita per numeri negativi");
        }
        
        // Logaritmi
        if (numero > 0) {
            System.out.println("Logaritmo naturale: " + df.format(Math.log(numero)));
            System.out.println("Logaritmo base 10: " + df.format(Math.log10(numero)));
        } else {
            System.out.println("Logaritmi: ❌ Non definiti per numeri ≤ 0");
        }
        
        // Funzioni trigonometriche (numero in radianti)
        System.out.println("Seno: " + df.format(Math.sin(numero)));
        System.out.println("Coseno: " + df.format(Math.cos(numero)));
        System.out.println("Tangente: " + df.format(Math.tan(numero)));
        
        // Conversione gradi-radianti
        double gradi = Math.toDegrees(numero);
        double radianti = Math.toRadians(numero);
        System.out.println(df.format(numero) + " radianti = " + df.format(gradi) + " gradi");
        System.out.println(df.format(numero) + " gradi = " + df.format(radianti) + " radianti");
        
        // Operazioni con due numeri
        System.out.println("\n🔄 OPERAZIONI CON DUE NUMERI:");
        double secondo = leggiDouble("Inserisci il secondo numero: ");
        
        System.out.println("Potenza: " + df.format(numero) + " ^ " + df.format(secondo) + " = " + df.format(Math.pow(numero, secondo)));
        System.out.println("Massimo: max(" + df.format(numero) + ", " + df.format(secondo) + ") = " + df.format(Math.max(numero, secondo)));
        System.out.println("Minimo: min(" + df.format(numero) + ", " + df.format(secondo) + ") = " + df.format(Math.min(numero, secondo)));
        
        // Valore assoluto e arrotondamenti
        System.out.println("\n🔢 ARROTONDAMENTI:");
        System.out.println("Valore assoluto di " + df.format(numero) + ": " + df.format(Math.abs(numero)));
        System.out.println("Arrotondato: " + Math.round(numero));
        System.out.println("Parte intera (floor): " + Math.floor(numero));
        System.out.println("Parte intera sup (ceil): " + Math.ceil(numero));
    }
    
    /**
     * SOLUZIONE: Conversioni di tipo complete
     */
    private static void conversioniTipo() {
        System.out.println("=== CONVERSIONI DI TIPO ===");
        
        System.out.println("🔄 ESEMPI DI CASTING:");
        
        // Casting implicito (widening)
        System.out.println("\n1. CASTING IMPLICITO (Widening):");
        byte valoreByte = 100;
        short valoreShort = valoreByte;
        int valoreInt = valoreShort;
        long valoreLong = valoreInt;
        float valoreFloat = valoreLong;
        double valoreDouble = valoreFloat;
        
        System.out.println("byte(" + valoreByte + ") -> short(" + valoreShort + 
                          ") -> int(" + valoreInt + ") -> long(" + valoreLong + 
                          ") -> float(" + valoreFloat + ") -> double(" + valoreDouble + ")");
        
        // Casting esplicito (narrowing)
        System.out.println("\n2. CASTING ESPLICITO (Narrowing):");
        double numeroGrande = 1234.5678;
        float daDouble = (float) numeroGrande;
        long daFloat = (long) daDouble;
        int daLong = (int) daLong;
        short daInt = (short) daInt;
        byte daShort = (byte) daShort;
        
        System.out.println("double(" + numeroGrande + ") -> float(" + daDouble + 
                          ") -> long(" + daFloat + ") -> int(" + daLong + 
                          ") -> short(" + daInt + ") -> byte(" + daShort + ")");
        System.out.println("⚠️ Nota la perdita di precisione ad ogni conversione!");
        
        // Overflow
        System.out.println("\n3. OVERFLOW/UNDERFLOW:");
        int maxInt = Integer.MAX_VALUE;
        System.out.println("int MAX_VALUE: " + maxInt);
        System.out.println("MAX_VALUE + 1: " + (maxInt + 1) + " (OVERFLOW!)");
        
        byte maxByte = Byte.MAX_VALUE;
        System.out.println("byte MAX_VALUE: " + maxByte);
        byte overflow = (byte)(maxByte + 1);
        System.out.println("(byte)(MAX_VALUE + 1): " + overflow + " (OVERFLOW!)");
        
        // Conversioni stringa-numero
        System.out.println("\n4. CONVERSIONI STRINGA-NUMERO:");
        String numeroStringa = "12345";
        System.out.println("Stringa originale: \"" + numeroStringa + "\"");
        
        int daStringa = Integer.parseInt(numeroStringa);
        long stringToLong = Long.parseLong(numeroStringa);
        double stringToDouble = Double.parseDouble(numeroStringa + ".67");
        
        System.out.println("parseInt: " + daStringa);
        System.out.println("parseLong: " + stringToLong);
        System.out.println("parseDouble: " + stringToDouble);
        
        // Numero a stringa
        System.out.println("Numero a stringa: " + String.valueOf(123.456));
    }
    
    /**
     * SOLUZIONE: Operazioni logiche e bit-wise complete
     */
    private static void operazioniLogiche() {
        System.out.println("=== OPERAZIONI LOGICHE E BIT-WISE ===");
        
        // Operatori logici
        boolean a = true;
        boolean b = false;
        
        System.out.println("🔍 OPERATORI LOGICI:");
        System.out.println("a = " + a + ", b = " + b);
        System.out.println("a && b (AND): " + (a && b));
        System.out.println("a || b (OR): " + (a || b));
        System.out.println("!a (NOT): " + (!a));
        System.out.println("!b (NOT): " + (!b));
        System.out.println("a ^ b (XOR): " + (a ^ b));
        
        // Operatori di confronto
        System.out.println("\n📊 OPERATORI DI CONFRONTO:");
        int x = leggiIntero("Inserisci primo numero intero: ");
        int y = leggiIntero("Inserisci secondo numero intero: ");
        
        System.out.println("x = " + x + ", y = " + y);
        System.out.println("x == y: " + (x == y));
        System.out.println("x != y: " + (x != y));
        System.out.println("x < y: " + (x < y));
        System.out.println("x > y: " + (x > y));
        System.out.println("x <= y: " + (x <= y));
        System.out.println("x >= y: " + (x >= y));
        
        // Operatori bit-wise
        System.out.println("\n💻 OPERATORI BIT-WISE:");
        System.out.println("x = " + x + " (binario: " + Integer.toBinaryString(x) + ")");
        System.out.println("y = " + y + " (binario: " + Integer.toBinaryString(y) + ")");
        
        System.out.println("x & y (AND): " + (x & y) + " (binario: " + Integer.toBinaryString(x & y) + ")");
        System.out.println("x | y (OR): " + (x | y) + " (binario: " + Integer.toBinaryString(x | y) + ")");
        System.out.println("x ^ y (XOR): " + (x ^ y) + " (binario: " + Integer.toBinaryString(x ^ y) + ")");
        System.out.println("~x (NOT): " + (~x) + " (binario: " + Integer.toBinaryString(~x) + ")");
        System.out.println("x << 1 (LEFT SHIFT): " + (x << 1) + " (binario: " + Integer.toBinaryString(x << 1) + ")");
        System.out.println("x >> 1 (RIGHT SHIFT): " + (x >> 1) + " (binario: " + Integer.toBinaryString(x >> 1) + ")");
    }
    
    /**
     * SOLUZIONE: Test completo tipi di dati
     */
    private static void testTipiDati() {
        System.out.println("=== TEST TIPI DI DATI PRIMITIVI ===");
        
        // Range dei tipi
        System.out.println("📏 RANGE DEI TIPI NUMERICI:");
        System.out.println("byte: " + Byte.MIN_VALUE + " to " + Byte.MAX_VALUE + " (" + Byte.SIZE + " bit)");
        System.out.println("short: " + Short.MIN_VALUE + " to " + Short.MAX_VALUE + " (" + Short.SIZE + " bit)");
        System.out.println("int: " + Integer.MIN_VALUE + " to " + Integer.MAX_VALUE + " (" + Integer.SIZE + " bit)");
        System.out.println("long: " + Long.MIN_VALUE + " to " + Long.MAX_VALUE + " (" + Long.SIZE + " bit)");
        System.out.println("float: " + Float.MIN_VALUE + " to " + Float.MAX_VALUE + " (" + Float.SIZE + " bit)");
        System.out.println("double: " + Double.MIN_VALUE + " to " + Double.MAX_VALUE + " (" + Double.SIZE + " bit)");
        
        // Test pratici
        System.out.println("\n🧪 TEST PRATICI:");
        
        // Test byte
        System.out.println("\n1. TEST BYTE:");
        int valoreTentativo = leggiIntero("Inserisci un valore per byte (-128 a 127): ");
        if (valoreTentativo >= Byte.MIN_VALUE && valoreTentativo <= Byte.MAX_VALUE) {
            byte valoreByte = (byte) valoreTentativo;
            System.out.println("✅ Valore valido! byte = " + valoreByte);
        } else {
            System.out.println("❌ Valore fuori range! Con casting forzato: " + (byte)valoreTentativo);
        }
        
        // Test char
        System.out.println("\n2. TEST CHAR:");
        System.out.print("Inserisci un carattere: ");
        String input = scanner.nextLine();
        if (input.length() > 0) {
            char carattere = input.charAt(0);
            System.out.println("Carattere: '" + carattere + "' -> Valore Unicode: " + (int)carattere);
            System.out.println("È una cifra? " + Character.isDigit(carattere));
            System.out.println("È una lettera? " + Character.isLetter(carattere));
            System.out.println("È maiuscola? " + Character.isUpperCase(carattere));
        }
        
        // Test boolean
        System.out.println("\n3. TEST BOOLEAN:");
        int numero1 = leggiIntero("Inserisci primo numero: ");
        int numero2 = leggiIntero("Inserisci secondo numero: ");
        
        boolean maggiore = numero1 > numero2;
        boolean pari1 = (numero1 % 2) == 0;
        boolean pari2 = (numero2 % 2) == 0;
        boolean entrambiPari = pari1 && pari2;
        
        System.out.println(numero1 + " > " + numero2 + ": " + maggiore);
        System.out.println(numero1 + " è pari: " + pari1);
        System.out.println(numero2 + " è pari: " + pari2);
        System.out.println("Entrambi pari: " + entrambiPari);
        
        // Esempi di precisione
        System.out.println("\n4. PRECISIONE FLOATING POINT:");
        float f1 = 0.1f;
        float f2 = 0.2f;
        float sommaFloat = f1 + f2;
        
        double d1 = 0.1;
        double d2 = 0.2;
        double sommaDouble = d1 + d2;
        
        System.out.println("float: 0.1f + 0.2f = " + sommaFloat);
        System.out.println("double: 0.1 + 0.2 = " + sommaDouble);
        System.out.println("⚠️ Nota gli errori di arrotondamento!");
    }
    
    private static int leggiIntero(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextInt()) {
            System.out.print("❌ Inserisci un numero intero valido: ");
            scanner.next();
        }
        int numero = scanner.nextInt();
        scanner.nextLine();
        return numero;
    }
    
    private static double leggiDouble(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextDouble()) {
            System.out.print("❌ Inserisci un numero valido: ");
            scanner.next();
        }
        double numero = scanner.nextDouble();
        scanner.nextLine();
        return numero;
    }
}
