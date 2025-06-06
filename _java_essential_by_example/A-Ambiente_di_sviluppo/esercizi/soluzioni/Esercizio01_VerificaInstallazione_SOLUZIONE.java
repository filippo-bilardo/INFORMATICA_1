import java.util.Scanner;

/**
 * SOLUZIONE ESERCIZIO 1: Verifica Installazione
 */
public class Esercizio01_VerificaInstallazione_SOLUZIONE {
    
    public static void main(String[] args) {
        System.out.println("=== VERIFICA INSTALLAZIONE JAVA ===");
        System.out.println();
        
        // Informazioni Java
        System.out.println("☕ INFORMAZIONI JAVA:");
        System.out.println("   Versione: " + System.getProperty("java.version"));
        System.out.println("   Vendor: " + System.getProperty("java.vendor"));
        System.out.println("   Java Home: " + System.getProperty("java.home"));
        System.out.println("   Specifica: " + System.getProperty("java.specification.version"));
        System.out.println();
        
        // Informazioni Sistema Operativo  
        System.out.println("💻 SISTEMA OPERATIVO:");
        System.out.println("   Nome: " + System.getProperty("os.name"));
        System.out.println("   Versione: " + System.getProperty("os.version"));
        System.out.println("   Architettura: " + System.getProperty("os.arch"));
        System.out.println();
        
        // Informazioni Utente
        System.out.println("👤 INFORMAZIONI UTENTE:");
        System.out.println("   Nome utente: " + System.getProperty("user.name"));
        System.out.println("   Directory home: " + System.getProperty("user.home"));
        System.out.println("   Directory corrente: " + System.getProperty("user.dir"));
        System.out.println();
        
        // Test funzionalità base
        System.out.println("🧮 TEST FUNZIONALITÀ:");
        int a = 10;
        int b = 5;
        int somma = a + b;
        double divisione = (double) a / b;
        
        System.out.println("   Test matematico: " + a + " + " + b + " = " + somma);
        System.out.println("   Test divisione: " + a + " / " + b + " = " + divisione);
        
        // Test stringa
        String messaggio = "Java funziona!";
        System.out.println("   Test stringa: " + messaggio);
        System.out.println("   Lunghezza stringa: " + messaggio.length() + " caratteri");
        
        // Test array semplice
        String[] linguaggi = {"Java", "Python", "JavaScript"};
        System.out.print("   Test array: ");
        for (String linguaggio : linguaggi) {
            System.out.print(linguaggio + " ");
        }
        System.out.println();
        
        // Informazioni memoria (bonus)
        Runtime runtime = Runtime.getRuntime();
        long maxMemory = runtime.maxMemory() / (1024 * 1024); // MB
        long totalMemory = runtime.totalMemory() / (1024 * 1024); // MB
        long freeMemory = runtime.freeMemory() / (1024 * 1024); // MB
        
        System.out.println("\n💾 INFORMAZIONI MEMORIA JVM:");
        System.out.println("   Memoria massima: " + maxMemory + " MB");
        System.out.println("   Memoria totale: " + totalMemory + " MB");
        System.out.println("   Memoria libera: " + freeMemory + " MB");
        
        System.out.println("\n✅ Se vedi questo messaggio, Java funziona correttamente!");
        System.out.println("🚀 Sei pronto per iniziare a programmare!");
    }
}
