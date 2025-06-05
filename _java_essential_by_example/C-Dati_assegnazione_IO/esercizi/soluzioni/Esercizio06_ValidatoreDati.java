/**
 * Esercizio 6: Validatore di Dati
 * 
 * Sistema di registrazione con validazione completa dei dati utente.
 * Dimostra l'importanza della validazione input e gestione errori.
 * 
 * Concetti dimostrati:
 * - Input validation avanzata
 * - Regular expressions (pattern matching)
 * - Cicli di controllo (do-while)
 * - Metodi di utility per validazione
 * - Gestione eccezioni con try-catch
 * - String manipulation
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Scanner;
import java.util.regex.Pattern;

public class Esercizio06_ValidatoreDati {
    
    // Pattern per validazione email
    private static final Pattern EMAIL_PATTERN = Pattern.compile(
        "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
    );
    
    // Pattern per validazione codice fiscale (semplificato)
    private static final Pattern CODICE_FISCALE_PATTERN = Pattern.compile(
        "^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$"
    );
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Banner del programma
        System.out.println("=".repeat(60));
        System.out.println("           SISTEMA DI REGISTRAZIONE UTENTE");
        System.out.println("=".repeat(60));
        System.out.println("Tutti i campi sono obbligatori e saranno validati");
        System.out.println();
        
        // Raccolta e validazione dati
        String nome = inputNomeValido(scanner);
        String cognome = inputCognomeValido(scanner);
        String email = inputEmailValida(scanner);
        int eta = inputEtaValida(scanner);
        String codiceFiscale = inputCodiceFiscaleValido(scanner);
        String telefono = inputTelefonoValido(scanner);
        
        // Conferma registrazione
        System.out.println("\n" + "=".repeat(60));
        System.out.println("           RIEPILOGO REGISTRAZIONE");
        System.out.println("=".repeat(60));
        
        System.out.printf("👤 Nome completo: %s %s%n", nome, cognome);
        System.out.printf("📧 Email: %s%n", email);
        System.out.printf("🎂 Età: %d anni%n", eta);
        System.out.printf("🆔 Codice Fiscale: %s%n", codiceFiscale);
        System.out.printf("📞 Telefono: %s%n", telefono);
        
        System.out.println("\n" + "-".repeat(60));
        System.out.print("Confermi la registrazione? (s/n): ");
        String conferma = scanner.nextLine().trim().toLowerCase();
        
        if (conferma.equals("s") || conferma.equals("si") || conferma.equals("sì")) {
            System.out.println("\n✅ REGISTRAZIONE COMPLETATA CON SUCCESSO!");
            System.out.println("Benvenuto nel nostro sistema, " + nome + "! 🎉");
            
            // Informazioni aggiuntive
            System.out.println("\n📋 Informazioni account:");
            System.out.printf("• Categoria età: %s%n", categoriaEta(eta));
            System.out.printf("• Dominio email: %s%n", estraiDominioEmail(email));
            System.out.printf("• Prefisso telefono: %s%n", estraiPrefissoTelefono(telefono));
        } else {
            System.out.println("\n❌ Registrazione annullata.");
            System.out.println("I tuoi dati non sono stati salvati.");
        }
        
        scanner.close();
    }
    
    /**
     * Input nome con validazione
     */
    private static String inputNomeValido(Scanner scanner) {
        String nome;
        do {
            System.out.print("📝 Nome (solo lettere, min 2 caratteri): ");
            nome = scanner.nextLine().trim();
            
            if (nome.length() < 2) {
                System.out.println("❌ Il nome deve contenere almeno 2 caratteri!");
                continue;
            }
            
            if (!nome.matches("^[a-zA-ZÀ-ÿ\\s'\\-]+$")) {
                System.out.println("❌ Il nome può contenere solo lettere, spazi, apostrofi e trattini!");
                continue;
            }
            
            break;
        } while (true);
        
        return capitalizzaParole(nome);
    }
    
    /**
     * Input cognome con validazione
     */
    private static String inputCognomeValido(Scanner scanner) {
        String cognome;
        do {
            System.out.print("📝 Cognome (solo lettere, min 2 caratteri): ");
            cognome = scanner.nextLine().trim();
            
            if (cognome.length() < 2) {
                System.out.println("❌ Il cognome deve contenere almeno 2 caratteri!");
                continue;
            }
            
            if (!cognome.matches("^[a-zA-ZÀ-ÿ\\s'\\-]+$")) {
                System.out.println("❌ Il cognome può contenere solo lettere, spazi, apostrofi e trattini!");
                continue;
            }
            
            break;
        } while (true);
        
        return capitalizzaParole(cognome);
    }
    
    /**
     * Input email con validazione completa
     */
    private static String inputEmailValida(Scanner scanner) {
        String email;
        do {
            System.out.print("📧 Email (formato: utente@dominio.com): ");
            email = scanner.nextLine().trim().toLowerCase();
            
            if (email.isEmpty()) {
                System.out.println("❌ L'email non può essere vuota!");
                continue;
            }
            
            if (!EMAIL_PATTERN.matcher(email).matches()) {
                System.out.println("❌ Formato email non valido!");
                System.out.println("   Deve contenere @ e un dominio valido (es: mario.rossi@gmail.com)");
                continue;
            }
            
            if (email.length() > 100) {
                System.out.println("❌ L'email è troppo lunga (max 100 caratteri)!");
                continue;
            }
            
            break;
        } while (true);
        
        return email;
    }
    
    /**
     * Input età con validazione (18-120 anni)
     */
    private static int inputEtaValida(Scanner scanner) {
        int eta;
        do {
            System.out.print("🎂 Età (18-120 anni): ");
            
            try {
                String input = scanner.nextLine().trim();
                eta = Integer.parseInt(input);
                
                if (eta < 18) {
                    System.out.println("❌ Devi essere maggiorenne per registrarti (min 18 anni)!");
                    continue;
                }
                
                if (eta > 120) {
                    System.out.println("❌ Età non valida (max 120 anni)!");
                    continue;
                }
                
                break;
            } catch (NumberFormatException e) {
                System.out.println("❌ Inserisci un numero valido per l'età!");
            }
        } while (true);
        
        return eta;
    }
    
    /**
     * Input codice fiscale con validazione
     */
    private static String inputCodiceFiscaleValido(Scanner scanner) {
        String codiceFiscale;
        do {
            System.out.print("🆔 Codice Fiscale (16 caratteri - AAABBB00A00A000A): ");
            codiceFiscale = scanner.nextLine().trim().toUpperCase();
            
            if (codiceFiscale.length() != 16) {
                System.out.println("❌ Il codice fiscale deve essere di esattamente 16 caratteri!");
                continue;
            }
            
            if (!CODICE_FISCALE_PATTERN.matcher(codiceFiscale).matches()) {
                System.out.println("❌ Formato codice fiscale non valido!");
                System.out.println("   Formato corretto: 6 lettere + 2 cifre + 1 lettera + 2 cifre + 1 lettera + 3 cifre + 1 lettera");
                continue;
            }
            
            break;
        } while (true);
        
        return codiceFiscale;
    }
    
    /**
     * Input telefono con validazione
     */
    private static String inputTelefonoValido(Scanner scanner) {
        String telefono;
        do {
            System.out.print("📞 Telefono (formato: +39 123 456 7890 o 3331234567): ");
            telefono = scanner.nextLine().trim();
            
            // Rimuove spazi e caratteri speciali per validazione
            String telefonoCleanup = telefono.replaceAll("[\\s\\-\\(\\)]", "");
            
            if (telefonoCleanup.length() < 8) {
                System.out.println("❌ Il numero di telefono è troppo corto!");
                continue;
            }
            
            if (telefonoCleanup.length() > 15) {
                System.out.println("❌ Il numero di telefono è troppo lungo!");
                continue;
            }
            
            // Verifica che contenga solo cifre e eventualmente +
            if (!telefonoCleanup.matches("^\\+?[0-9]+$")) {
                System.out.println("❌ Il telefono può contenere solo cifre e il prefisso +!");
                continue;
            }
            
            break;
        } while (true);
        
        return telefono;
    }
    
    /**
     * Utility: capitalizza ogni parola
     */
    private static String capitalizzaParole(String testo) {
        String[] parole = testo.toLowerCase().split("\\s+");
        StringBuilder risultato = new StringBuilder();
        
        for (int i = 0; i < parole.length; i++) {
            if (i > 0) risultato.append(" ");
            
            if (parole[i].length() > 0) {
                risultato.append(Character.toUpperCase(parole[i].charAt(0)));
                if (parole[i].length() > 1) {
                    risultato.append(parole[i].substring(1));
                }
            }
        }
        
        return risultato.toString();
    }
    
    /**
     * Utility: determina categoria età
     */
    private static String categoriaEta(int eta) {
        if (eta < 25) return "Giovane adulto";
        else if (eta < 40) return "Adulto";
        else if (eta < 65) return "Adulto maturo";
        else return "Senior";
    }
    
    /**
     * Utility: estrae dominio da email
     */
    private static String estraiDominioEmail(String email) {
        int indiceAt = email.indexOf('@');
        return email.substring(indiceAt + 1);
    }
    
    /**
     * Utility: estrae prefisso da telefono
     */
    private static String estraiPrefissoTelefono(String telefono) {
        if (telefono.startsWith("+")) {
            int spazio = telefono.indexOf(' ');
            return spazio > 0 ? telefono.substring(0, spazio) : telefono.substring(0, Math.min(5, telefono.length()));
        }
        return "Non specificato";
    }
}
