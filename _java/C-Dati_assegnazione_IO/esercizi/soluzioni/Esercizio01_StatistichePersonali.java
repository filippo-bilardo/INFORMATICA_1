/**
 * Esercizio 1: Calcolatore di Statistiche Personali
 * 
 * Questo programma raccoglie dati personali dell'utente e calcola
 * statistiche come l'IMC (Indice di Massa Corporea) e verifica
 * la maggiore età.
 * 
 * Concetti dimostrati:
 * - Input/Output con Scanner
 * - Tipi di dati primitivi (int, double)
 * - Operazioni aritmetiche
 * - Operatori logici e condizionali
 * - Formattazione output con printf
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Scanner;
import java.time.LocalDate;

public class Esercizio01_StatistichePersonali {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Banner del programma
        System.out.println("=".repeat(50));
        System.out.println("    CALCOLATORE STATISTICHE PERSONALI");
        System.out.println("=".repeat(50));
        
        // Raccolta dati personali
        System.out.println("\n📝 Inserisci i tuoi dati personali:");
        
        System.out.print("Nome: ");
        String nome = scanner.nextLine();
        
        // Input età con validazione
        int eta = inputEtaValida(scanner);
        
        // Input altezza con validazione
        double altezza = inputAltezzaValida(scanner);
        
        // Input peso con validazione
        double peso = inputPesoValido(scanner);
        
        // Calcoli e statistiche
        System.out.println("\n" + "=".repeat(50));
        System.out.println("    RISULTATI STATISTICHE");
        System.out.println("=".repeat(50));
        
        // Visualizzazione dati inseriti
        System.out.printf("👤 Nome: %s%n", nome);
        System.out.printf("🎂 Età: %d anni%n", eta);
        System.out.printf("📏 Altezza: %.1f cm%n", altezza);
        System.out.printf("⚖️  Peso: %.1f kg%n", peso);
        
        // Calcolo IMC
        double altezzaInMetri = altezza / 100.0;
        double imc = peso / (altezzaInMetri * altezzaInMetri);
        
        System.out.println("\n📊 ANALISI SALUTE:");
        System.out.printf("• IMC (Indice Massa Corporea): %.2f%n", imc);
        System.out.printf("• Categoria: %s%n", categoriaIMC(imc));
        
        // Verifica maggiore età
        System.out.println("\n📋 INFORMAZIONI LEGALI:");
        boolean maggiorenne = eta >= 18;
        System.out.printf("• Maggiorenne: %s%n", maggiorenne ? "Sì ✅" : "No ❌");
        
        if (maggiorenne) {
            System.out.printf("• Anni da maggiorenne: %d%n", eta - 18);
        } else {
            System.out.printf("• Anni alla maggiore età: %d%n", 18 - eta);
        }
        
        // Anno di nascita approssimativo
        int annoCorrente = LocalDate.now().getYear();
        int annoNascita = annoCorrente - eta;
        System.out.printf("• Anno di nascita (circa): %d%n", annoNascita);
        
        // Statistiche aggiuntive interessanti
        System.out.println("\n🎯 CURIOSITÀ:");
        System.out.printf("• Peso in once: %.1f oz%n", peso * 35.274);
        System.out.printf("• Altezza in piedi: %.2f ft%n", altezza / 30.48);
        System.out.printf("• Giorni vissuti (circa): %,d%n", eta * 365);
        
        System.out.println("\n" + "=".repeat(50));
        System.out.println("Grazie per aver utilizzato il calcolatore! 👋");
        
        scanner.close();
    }
    
    /**
     * Input età con validazione (0-150 anni)
     */
    private static int inputEtaValida(Scanner scanner) {
        int eta;
        do {
            System.out.print("Età (0-150): ");
            while (!scanner.hasNextInt()) {
                System.out.print("❌ Inserisci un numero valido per l'età: ");
                scanner.next();
            }
            eta = scanner.nextInt();
            
            if (eta < 0 || eta > 150) {
                System.out.println("❌ L'età deve essere tra 0 e 150 anni!");
            }
        } while (eta < 0 || eta > 150);
        
        return eta;
    }
    
    /**
     * Input altezza con validazione (50-300 cm)
     */
    private static double inputAltezzaValida(Scanner scanner) {
        double altezza;
        do {
            System.out.print("Altezza in cm (50-300): ");
            while (!scanner.hasNextDouble()) {
                System.out.print("❌ Inserisci un numero valido per l'altezza: ");
                scanner.next();
            }
            altezza = scanner.nextDouble();
            
            if (altezza < 50 || altezza > 300) {
                System.out.println("❌ L'altezza deve essere tra 50 e 300 cm!");
            }
        } while (altezza < 50 || altezza > 300);
        
        return altezza;
    }
    
    /**
     * Input peso con validazione (1-500 kg)
     */
    private static double inputPesoValido(Scanner scanner) {
        double peso;
        do {
            System.out.print("Peso in kg (1-500): ");
            while (!scanner.hasNextDouble()) {
                System.out.print("❌ Inserisci un numero valido per il peso: ");
                scanner.next();
            }
            peso = scanner.nextDouble();
            
            if (peso <= 0 || peso > 500) {
                System.out.println("❌ Il peso deve essere tra 1 e 500 kg!");
            }
        } while (peso <= 0 || peso > 500);
        
        return peso;
    }
    
    /**
     * Determina la categoria IMC secondo gli standard WHO
     */
    private static String categoriaIMC(double imc) {
        if (imc < 16.0) {
            return "Grave magrezza 🔴";
        } else if (imc < 17.0) {
            return "Magrezza moderata 🟠";
        } else if (imc < 18.5) {
            return "Magrezza lieve 🟡";
        } else if (imc < 25.0) {
            return "Peso normale 🟢";
        } else if (imc < 30.0) {
            return "Sovrappeso 🟡";
        } else if (imc < 35.0) {
            return "Obesità classe I 🟠";
        } else if (imc < 40.0) {
            return "Obesità classe II 🔴";
        } else {
            return "Obesità classe III 🆘";
        }
    }
}
