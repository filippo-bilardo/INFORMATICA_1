import java.util.Scanner;

/**
 * SOLUZIONE ESERCIZIO 3: Calcolatrice Base
 */
public class Esercizio03_CalcolatriceBase_SOLUZIONE {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Intestazione
        System.out.println("🧮 CALCOLATRICE JAVA AVANZATA 🧮");
        System.out.println("=".repeat(35));
        System.out.println("Esegue operazioni matematiche tra due numeri");
        System.out.println();
        
        // Input numeri
        System.out.print("📊 Inserisci il primo numero: ");
        double numero1 = scanner.nextDouble();
        
        System.out.print("📊 Inserisci il secondo numero: ");
        double numero2 = scanner.nextDouble();
        
        // Operazioni matematiche base
        double somma = numero1 + numero2;
        double sottrazione = numero1 - numero2;
        double moltiplicazione = numero1 * numero2;
        double resto = numero1 % numero2;
        
        // Output risultati
        System.out.println("\n" + "=".repeat(35));
        System.out.println("         RISULTATI OPERAZIONI");
        System.out.println("=".repeat(35));
        
        System.out.printf("➕ %.2f + %.2f = %.2f%n", numero1, numero2, somma);
        System.out.printf("➖ %.2f - %.2f = %.2f%n", numero1, numero2, sottrazione);
        System.out.printf("✖️  %.2f × %.2f = %.2f%n", numero1, numero2, moltiplicazione);
        
        // Gestione divisione per zero
        if (numero2 != 0) {
            double divisione = numero1 / numero2;
            System.out.printf("➗ %.2f ÷ %.2f = %.2f%n", numero1, numero2, divisione);
            System.out.printf("📐 %.2f %% %.2f = %.2f (resto)%n", numero1, numero2, resto);
        } else {
            System.out.println("➗ Divisione per zero non possibile! ⚠️");
            System.out.println("📐 Resto: operazione non valida ⚠️");
        }
        
        // Operazioni matematiche avanzate
        System.out.println("\n" + "=".repeat(35));
        System.out.println("      OPERAZIONI AVANZATE");
        System.out.println("=".repeat(35));
        
        // Potenza
        double potenza = Math.pow(numero1, numero2);
        System.out.printf("🔢 %.2f ^ %.2f = %.2f%n", numero1, numero2, potenza);
        
        // Radici quadrate (solo per numeri positivi)
        if (numero1 >= 0) {
            double radice1 = Math.sqrt(numero1);
            System.out.printf("√  √%.2f = %.2f%n", numero1, radice1);
        } else {
            System.out.printf("√  √%.2f = Non definita (numero negativo)%n", numero1);
        }
        
        if (numero2 >= 0) {
            double radice2 = Math.sqrt(numero2);
            System.out.printf("√  √%.2f = %.2f%n", numero2, radice2);
        } else {
            System.out.printf("√  √%.2f = Non definita (numero negativo)%n", numero2);
        }
        
        // Valore assoluto
        double abs1 = Math.abs(numero1);
        double abs2 = Math.abs(numero2);
        System.out.printf("📏 |%.2f| = %.2f%n", numero1, abs1);
        System.out.printf("📏 |%.2f| = %.2f%n", numero2, abs2);
        
        // Massimo e minimo
        double massimo = Math.max(numero1, numero2);
        double minimo = Math.min(numero1, numero2);
        System.out.printf("📈 max(%.2f, %.2f) = %.2f%n", numero1, numero2, massimo);
        System.out.printf("📉 min(%.2f, %.2f) = %.2f%n", numero1, numero2, minimo);
        
        // Funzioni trigonometriche (per il primo numero)
        System.out.println("\n" + "=".repeat(35));
        System.out.println("    FUNZIONI TRIGONOMETRICHE");
        System.out.println("    (applicate al primo numero)");
        System.out.println("=".repeat(35));
        
        double radianti = Math.toRadians(numero1);
        double seno = Math.sin(radianti);
        double coseno = Math.cos(radianti);
        double tangente = Math.tan(radianti);
        
        System.out.printf("🔄 %.2f° in radianti = %.4f%n", numero1, radianti);
        System.out.printf("📐 sin(%.2f°) = %.4f%n", numero1, seno);
        System.out.printf("📐 cos(%.2f°) = %.4f%n", numero1, coseno);
        System.out.printf("📐 tan(%.2f°) = %.4f%n", numero1, tangente);
        
        // Statistiche sui numeri
        System.out.println("\n" + "=".repeat(35));
        System.out.println("         ANALISI NUMERI");
        System.out.println("=".repeat(35));
        
        // Media aritmetica
        double media = (numero1 + numero2) / 2;
        System.out.printf("📊 Media aritmetica: %.2f%n", media);
        
        // Distanza
        double distanza = Math.abs(numero1 - numero2);
        System.out.printf("📏 Distanza tra i numeri: %.2f%n", distanza);
        
        // Controllo parità
        boolean num1Pari = (numero1 % 2 == 0);
        boolean num2Pari = (numero2 % 2 == 0);
        System.out.printf("🔢 %.0f è %s%n", numero1, num1Pari ? "pari" : "dispari");
        System.out.printf("🔢 %.0f è %s%n", numero2, num2Pari ? "pari" : "dispari");
        
        // Messaggio finale
        System.out.println("\n" + "=".repeat(35));
        System.out.println("✅ Calcoli completati con successo!");
        System.out.println("🚀 Grazie per aver usato la calcolatrice Java!");
        System.out.println("=".repeat(35));
        
        scanner.close();
    }
}
