import java.util.Scanner;

/**
 * SOLUZIONE ESERCIZIO 2: Hello World Personalizzato
 */
public class Esercizio02_HelloWorldPersonalizzato_SOLUZIONE {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Banner di benvenuto
        System.out.println("╔════════════════════════════════════╗");
        System.out.println("║        BENVENUTO IN JAVA! 🚀       ║");
        System.out.println("║     Programma di Saluto Personale  ║");
        System.out.println("╚════════════════════════════════════╝");
        System.out.println();
        
        // Raccolta informazioni
        System.out.print("📝 Inserisci il tuo nome: ");
        String nome = scanner.nextLine();
        
        System.out.print("📝 Inserisci il tuo cognome: ");
        String cognome = scanner.nextLine();
        
        System.out.print("🎂 Inserisci la tua età: ");
        int eta = scanner.nextInt();
        
        // Consuma il newline dopo nextInt()
        scanner.nextLine();
        
        System.out.print("🏠 Inserisci la tua città: ");
        String citta = scanner.nextLine();
        
        // Elaborazione dati
        String nomeCompleto = nome + " " + cognome;
        int annoNascita = 2025 - eta;
        String categoria = (eta >= 18) ? "maggiorenne" : "minorenne";
        String emoji = (eta >= 18) ? "🎉" : "👶";
        
        // Output personalizzato
        System.out.println("\n" + "=".repeat(45));
        System.out.println("          RIEPILOGO PERSONALE");
        System.out.println("=".repeat(45));
        
        // Saluto principale
        System.out.println("👋 Ciao " + nomeCompleto + "!");
        System.out.printf("🎂 Hai %d anni e vieni da %s%n", eta, citta);
        System.out.printf("📅 Sei nato/a circa nel %d%n", annoNascita);
        System.out.printf("📊 Sei %s! %s%n", categoria, emoji);
        
        // Messaggi condizionali
        if (eta < 13) {
            System.out.println("🎈 Sei ancora un bambino/a! Divertiti!");
        } else if (eta < 18) {
            System.out.println("🎓 Sei un/a teenager! Studia e divertiti!");
        } else if (eta < 65) {
            System.out.println("💼 Sei in età lavorativa! Buona carriera!");
        } else {
            System.out.println("🎯 Complimenti per la tua saggezza!");
        }
        
        // Messaggio sulla programmazione
        System.out.println("\n🚀 Benvenuto/a nel fantastico mondo della programmazione Java!");
        System.out.println("💻 Con Java potrai creare applicazioni incredibili!");
        
        // Statistiche divertenti
        System.out.println("\n📊 STATISTICHE DIVERTENTI:");
        int giorniVissuti = eta * 365;
        int oreVissute = giorniVissuti * 24;
        System.out.printf("   Hai vissuto circa %,d giorni%n", giorniVissuti);
        System.out.printf("   Equivalenti a circa %,d ore%n", oreVissute);
        
        // Messaggio finale personalizzato
        char inizialeNome = nome.charAt(0);
        System.out.println("\n" + "=".repeat(45));
        System.out.printf("✅ Ciao %c.! Il tuo viaggio Java inizia ora! 🌟%n", inizialeNome);
        System.out.println("=".repeat(45));
        
        scanner.close();
    }
}
