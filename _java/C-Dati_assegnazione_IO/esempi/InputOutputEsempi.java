/**
 * Esempi pratici di Input e Output in Java
 * 
 * Questo file dimostra:
 * - Uso completo della classe Scanner
 * - Formattazione avanzata con printf
 * - Gestione robusta degli errori di input
 * - Validazione dell'input utente
 * - I/O con file (base)
 * - Best practices per l'interazione utente
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.util.Scanner;
import java.util.InputMismatchException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class InputOutputEsempi {
    
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        System.out.println("=== ESEMPI INPUT E OUTPUT ===\n");
        
        // Menu interattivo per gli esempi
        while (true) {
            mostraMenu();
            int scelta = leggiScelta();
            
            switch (scelta) {
                case 1: esempiInputBase(); break;
                case 2: esempiOutputFormattato(); break;
                case 3: esempiValidazioneInput(); break;
                case 4: esempiGestioneErrori(); break;
                case 5: esempiInputOutputFile(); break;
                case 6: calcolatriceInterattiva(); break;
                case 7: registroStudentiCompleto(); break;
                case 0: 
                    System.out.println("Arrivederci!");
                    scanner.close();
                    return;
                default:
                    System.out.println("Scelta non valida!");
            }
            
            System.out.println("\nPremi INVIO per continuare...");
            scanner.nextLine();
        }
    }
    
    /**
     * Mostra il menu principale
     */
    public static void mostraMenu() {
        System.out.println("\n" + "=".repeat(50));
        System.out.println("           MENU ESEMPI I/O");
        System.out.println("=".repeat(50));
        System.out.println("1. Input Base (Scanner)");
        System.out.println("2. Output Formattato (printf)");
        System.out.println("3. Validazione Input");
        System.out.println("4. Gestione Errori");
        System.out.println("5. I/O con File");
        System.out.println("6. Calcolatrice Interattiva");
        System.out.println("7. Registro Studenti Completo");
        System.out.println("0. Esci");
        System.out.println("=".repeat(50));
    }
    
    /**
     * Legge la scelta dell'utente con validazione
     */
    public static int leggiScelta() {
        while (true) {
            System.out.print("Scegli un'opzione (0-7): ");
            if (scanner.hasNextInt()) {
                int scelta = scanner.nextInt();
                scanner.nextLine(); // Consuma il newline
                if (scelta >= 0 && scelta <= 7) {
                    return scelta;
                } else {
                    System.out.println("Errore: inserisci un numero tra 0 e 7");
                }
            } else {
                System.out.println("Errore: inserisci un numero valido");
                scanner.next(); // Consuma input invalido
            }
        }
    }
    
    /**
     * Dimostra gli esempi di input base con Scanner
     */
    public static void esempiInputBase() {
        System.out.println("\n--- ESEMPI INPUT BASE ---");
        
        // Input di tipi primitivi
        System.out.print("Inserisci il tuo nome: ");
        String nome = scanner.nextLine();
        
        System.out.print("Inserisci la tua età: ");
        int eta = scanner.nextInt();
        
        System.out.print("Inserisci la tua altezza (m): ");
        double altezza = scanner.nextDouble();
        
        System.out.print("Sei studente? (true/false): ");
        boolean studente = scanner.nextBoolean();
        
        scanner.nextLine(); // Pulisce il buffer
        
        System.out.print("Inserisci la tua iniziale: ");
        char iniziale = scanner.nextLine().charAt(0);
        
        // Output dei dati raccolti
        System.out.println("\n--- DATI INSERITI ---");
        System.out.printf("Nome: %s%n", nome);
        System.out.printf("Età: %d anni%n", eta);
        System.out.printf("Altezza: %.2f m%n", altezza);
        System.out.printf("Studente: %s%n", studente ? "Sì" : "No");
        System.out.printf("Iniziale: %c%n", iniziale);
        
        // Controllo disponibilità input
        System.out.println("\nVerifica input disponibile:");
        System.out.println("Scrivi qualcosa e premi INVIO:");
        
        if (scanner.hasNext()) {
            String input = scanner.nextLine();
            System.out.printf("Hai scritto: \"%s\"%n", input);
        }
    }
    
    /**
     * Dimostra l'output formattato con printf
     */
    public static void esempiOutputFormattato() {
        System.out.println("\n--- ESEMPI OUTPUT FORMATTATO ---");
        
        // Dati di esempio
        String nome = "Alice Rossi";
        int eta = 28;
        double stipendio = 35750.75;
        double altezza = 1.68;
        boolean manager = true;
        
        // Formattazione base
        System.out.println("1. Formattazione base:");
        System.out.printf("Nome: %s%n", nome);
        System.out.printf("Età: %d anni%n", eta);
        System.out.printf("Stipendio: %.2f€%n", stipendio);
        System.out.printf("Manager: %b%n", manager);
        
        // Controllo larghezza e allineamento
        System.out.println("\n2. Controllo larghezza:");
        System.out.printf("|%-15s|%5d|%10.2f|%n", "Alice", 28, 1234.56);
        System.out.printf("|%-15s|%5d|%10.2f|%n", "Bob", 35, 987.65);
        System.out.printf("|%-15s|%5d|%10.2f|%n", "Charlie", 42, 2345.67);
        
        // Padding con zeri
        System.out.println("\n3. Padding con zeri:");
        System.out.printf("ID: %06d%n", 123);
        System.out.printf("Codice: %08d%n", 456);
        
        // Formati numerici speciali
        System.out.println("\n4. Formati numerici:");
        int numero = 255;
        System.out.printf("Decimale: %d%n", numero);
        System.out.printf("Esadecimale: %x%n", numero);
        System.out.printf("Esadecimale maiuscolo: %X%n", numero);
        System.out.printf("Ottale: %o%n", numero);
        
        // Notazione scientifica
        double grande = 1234567.89;
        System.out.printf("Scientifico: %e%n", grande);
        System.out.printf("Scientifico maiuscolo: %E%n", grande);
        System.out.printf("Compatto: %g%n", grande);
        
        // Percentuali
        double percentuale = 0.856;
        System.out.printf("Percentuale: %.1f%%%n", percentuale * 100);
        
        // Tabella formattata
        System.out.println("\n5. Tabella dipendenti:");
        String formato = "| %-12s | %3s | %8s | %-8s |%n";
        String separatore = "+" + "-".repeat(14) + "+" + "-".repeat(5) + "+" + "-".repeat(10) + "+" + "-".repeat(10) + "+%n";
        
        System.out.printf(separatore);
        System.out.printf(formato, "Nome", "Età", "Stipendio", "Ruolo");
        System.out.printf(separatore);
        System.out.printf(formato, "Alice", "28", "35750€", "Manager");
        System.out.printf(formato, "Bob", "35", "28000€", "Developer");
        System.out.printf(formato, "Charlie", "42", "42000€", "Senior");
        System.out.printf(separatore);
        
        // Formattazione data/ora
        System.out.println("6. Data e ora:");
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
        System.out.printf("Timestamp: %s%n", now.format(formatter));
    }
    
    /**
     * Dimostra la validazione robusta dell'input
     */
    public static void esempiValidazioneInput() {
        System.out.println("\n--- VALIDAZIONE INPUT ---");
        
        // Validazione età
        int eta = leggiInteroConRange("Inserisci la tua età: ", 0, 150);
        System.out.printf("✓ Età valida: %d anni%n", eta);
        
        // Validazione email
        String email = leggiEmail();
        System.out.printf("✓ Email valida: %s%n", email);
        
        // Validazione stringa non vuota
        String nome = leggiStringaNonVuota("Inserisci il tuo nome: ");
        System.out.printf("✓ Nome valido: %s%n", nome);
        
        // Validazione double
        double altezza = leggiDoubleConRange("Inserisci la tua altezza (m): ", 0.5, 3.0);
        System.out.printf("✓ Altezza valida: %.2f m%n", altezza);
        
        // Validazione scelta multipla
        String[] opzioni = {"Rosso", "Verde", "Blu", "Giallo"};
        int scelta = leggiSceltaMultipla("Scegli un colore:", opzioni);
        System.out.printf("✓ Colore scelto: %s%n", opzioni[scelta]);
        
        // Validazione password
        String password = leggiPassword();
        System.out.printf("✓ Password valida: %s%n", "*".repeat(password.length()));
    }
    
    /**
     * Legge un intero con validazione del range
     */
    public static int leggiInteroConRange(String messaggio, int min, int max) {
        while (true) {
            System.out.print(messaggio + String.format("(%d-%d): ", min, max));
            if (scanner.hasNextInt()) {
                int valore = scanner.nextInt();
                scanner.nextLine(); // Pulisce buffer
                if (valore >= min && valore <= max) {
                    return valore;
                } else {
                    System.out.printf("❌ Errore: il valore deve essere tra %d e %d%n", min, max);
                }
            } else {
                System.out.println("❌ Errore: inserisci un numero intero valido");
                scanner.next(); // Consuma input invalido
            }
        }
    }
    
    /**
     * Legge un double con validazione del range
     */
    public static double leggiDoubleConRange(String messaggio, double min, double max) {
        while (true) {
            System.out.print(messaggio + String.format("(%.1f-%.1f): ", min, max));
            if (scanner.hasNextDouble()) {
                double valore = scanner.nextDouble();
                scanner.nextLine(); // Pulisce buffer
                if (valore >= min && valore <= max) {
                    return valore;
                } else {
                    System.out.printf("❌ Errore: il valore deve essere tra %.1f e %.1f%n", min, max);
                }
            } else {
                System.out.println("❌ Errore: inserisci un numero decimale valido");
                scanner.next();
            }
        }
    }
    
    /**
     * Legge una stringa non vuota
     */
    public static String leggiStringaNonVuota(String messaggio) {
        while (true) {
            System.out.print(messaggio);
            String input = scanner.nextLine().trim();
            if (!input.isEmpty()) {
                return input;
            } else {
                System.out.println("❌ Errore: la stringa non può essere vuota");
            }
        }
    }
    
    /**
     * Legge un'email con validazione base
     */
    public static String leggiEmail() {
        while (true) {
            System.out.print("Inserisci la tua email: ");
            String email = scanner.nextLine().trim();
            if (email.contains("@") && email.contains(".") && email.length() > 5) {
                return email;
            } else {
                System.out.println("❌ Errore: formato email non valido");
            }
        }
    }
    
    /**
     * Legge una scelta da opzioni multiple
     */
    public static int leggiSceltaMultipla(String messaggio, String[] opzioni) {
        System.out.println(messaggio);
        for (int i = 0; i < opzioni.length; i++) {
            System.out.printf("%d. %s%n", i + 1, opzioni[i]);
        }
        
        while (true) {
            System.out.printf("Scegli (1-%d): ", opzioni.length);
            if (scanner.hasNextInt()) {
                int scelta = scanner.nextInt();
                scanner.nextLine();
                if (scelta >= 1 && scelta <= opzioni.length) {
                    return scelta - 1; // Ritorna indice 0-based
                } else {
                    System.out.printf("❌ Errore: scegli un numero tra 1 e %d%n", opzioni.length);
                }
            } else {
                System.out.println("❌ Errore: inserisci un numero valido");
                scanner.next();
            }
        }
    }
    
    /**
     * Legge una password con validazione
     */
    public static String leggiPassword() {
        while (true) {
            System.out.print("Inserisci password (min 8 caratteri, con numero): ");
            String password = scanner.nextLine();
            
            boolean lunghezzaOk = password.length() >= 8;
            boolean haCifre = password.matches(".*\\d.*");
            
            if (lunghezzaOk && haCifre) {
                return password;
            } else {
                System.out.println("❌ Password non valida:");
                if (!lunghezzaOk) System.out.println("   - Deve avere almeno 8 caratteri");
                if (!haCifre) System.out.println("   - Deve contenere almeno un numero");
            }
        }
    }
    
    /**
     * Dimostra la gestione degli errori di input
     */
    public static void esempiGestioneErrori() {
        System.out.println("\n--- GESTIONE ERRORI ---");
        
        // Gestione InputMismatchException
        System.out.println("1. Gestione InputMismatchException:");
        int numero = leggiInteroSicuro("Inserisci un numero intero: ");
        System.out.printf("✓ Numero inserito: %d%n", numero);
        
        // Gestione divisione per zero
        System.out.println("\n2. Gestione divisione per zero:");
        calcolaDivisione();
        
        // Gestione array index out of bounds
        System.out.println("\n3. Gestione accesso array:");
        accessoArraySicuro();
    }
    
    /**
     * Legge un intero con gestione robusta degli errori
     */
    public static int leggiInteroSicuro(String messaggio) {
        while (true) {
            try {
                System.out.print(messaggio);
                return scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("❌ Errore: devi inserire un numero intero!");
                scanner.next(); // Consuma l'input errato
            } finally {
                scanner.nextLine(); // Pulisce sempre il buffer
            }
        }
    }
    
    /**
     * Dimostra la gestione della divisione per zero
     */
    public static void calcolaDivisione() {
        try {
            System.out.print("Inserisci il dividendo: ");
            double dividendo = scanner.nextDouble();
            System.out.print("Inserisci il divisore: ");
            double divisore = scanner.nextDouble();
            scanner.nextLine();
            
            if (divisore == 0) {
                throw new ArithmeticException("Divisione per zero non consentita");
            }
            
            double risultato = dividendo / divisore;
            System.out.printf("✓ Risultato: %.2f / %.2f = %.4f%n", dividendo, divisore, risultato);
            
        } catch (InputMismatchException e) {
            System.out.println("❌ Errore: inserisci numeri validi");
            scanner.nextLine();
        } catch (ArithmeticException e) {
            System.out.println("❌ Errore: " + e.getMessage());
        }
    }
    
    /**
     * Dimostra l'accesso sicuro agli array
     */
    public static void accessoArraySicuro() {
        String[] nomi = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
        
        System.out.printf("Array disponibile con %d elementi (indici 0-%d)%n", 
                         nomi.length, nomi.length - 1);
        
        try {
            System.out.print("Inserisci l'indice da visualizzare: ");
            int indice = scanner.nextInt();
            scanner.nextLine();
            
            if (indice >= 0 && indice < nomi.length) {
                System.out.printf("✓ Elemento %d: %s%n", indice, nomi[indice]);
            } else {
                System.out.printf("❌ Indice %d fuori range [0-%d]%n", indice, nomi.length - 1);
            }
            
        } catch (InputMismatchException e) {
            System.out.println("❌ Errore: inserisci un numero intero valido");
            scanner.nextLine();
        }
    }
    
    /**
     * Dimostra I/O con file
     */
    public static void esempiInputOutputFile() {
        System.out.println("\n--- I/O CON FILE ---");
        
        String nomeFile = "esempio_output.txt";
        
        // Scrittura su file
        try (PrintWriter writer = new PrintWriter(nomeFile)) {
            writer.println("=== FILE DI ESEMPIO ===");
            writer.printf("Data/ora: %s%n", LocalDateTime.now());
            writer.println("Questo è un file di test creato da Java");
            writer.printf("Numero casuale: %.3f%n", Math.random());
            writer.println("Fine del file");
            
            System.out.printf("✓ File '%s' scritto con successo%n", nomeFile);
            
        } catch (IOException e) {
            System.out.println("❌ Errore nella scrittura: " + e.getMessage());
            return;
        }
        
        // Lettura da file
        try (Scanner fileScanner = new Scanner(new File(nomeFile))) {
            System.out.println("\n--- CONTENUTO DEL FILE ---");
            int lineNumber = 1;
            
            while (fileScanner.hasNextLine()) {
                String riga = fileScanner.nextLine();
                System.out.printf("%2d: %s%n", lineNumber++, riga);
            }
            
            System.out.printf("✓ File '%s' letto con successo%n", nomeFile);
            
        } catch (FileNotFoundException e) {
            System.out.println("❌ File non trovato: " + e.getMessage());
        }
    }
    
    /**
     * Calcolatrice interattiva completa
     */
    public static void calcolatriceInterattiva() {
        System.out.println("\n--- CALCOLATRICE INTERATTIVA ---");
        
        while (true) {
            try {
                System.out.print("Primo numero (o 'q' per uscire): ");
                String input = scanner.nextLine().trim();
                
                if (input.equalsIgnoreCase("q")) {
                    System.out.println("Uscita dalla calcolatrice");
                    break;
                }
                
                double num1 = Double.parseDouble(input);
                
                System.out.print("Operatore (+, -, *, /, %, ^): ");
                String operatore = scanner.nextLine().trim();
                
                if (operatore.length() != 1 || "+-*/%^".indexOf(operatore) == -1) {
                    System.out.println("❌ Operatore non valido!");
                    continue;
                }
                
                System.out.print("Secondo numero: ");
                double num2 = Double.parseDouble(scanner.nextLine().trim());
                
                double risultato = 0;
                boolean operazioneValida = true;
                
                switch (operatore.charAt(0)) {
                    case '+': risultato = num1 + num2; break;
                    case '-': risultato = num1 - num2; break;
                    case '*': risultato = num1 * num2; break;
                    case '/': 
                        if (num2 != 0) {
                            risultato = num1 / num2;
                        } else {
                            System.out.println("❌ Errore: divisione per zero!");
                            operazioneValida = false;
                        }
                        break;
                    case '%': 
                        if (num2 != 0) {
                            risultato = num1 % num2;
                        } else {
                            System.out.println("❌ Errore: modulo per zero!");
                            operazioneValida = false;
                        }
                        break;
                    case '^': risultato = Math.pow(num1, num2); break;
                }
                
                if (operazioneValida) {
                    System.out.printf("✓ %.3f %s %.3f = %.6f%n", num1, operatore, num2, risultato);
                }
                
            } catch (NumberFormatException e) {
                System.out.println("❌ Errore: formato numero non valido!");
            }
            
            System.out.println();
        }
    }
    
    /**
     * Registro studenti completo con file
     */
    public static void registroStudentiCompleto() {
        System.out.println("\n--- REGISTRO STUDENTI COMPLETO ---");
        
        java.util.List<String> nomi = new java.util.ArrayList<>();
        java.util.List<Double> voti = new java.util.ArrayList<>();
        
        // Input studenti
        while (true) {
            String nome = leggiStringaNonVuota("Nome studente (vuoto per terminare): ");
            if (nome.isEmpty()) break;
            
            double voto = leggiDoubleConRange("Voto di " + nome, 0.0, 10.0);
            
            nomi.add(nome);
            voti.add(voto);
            
            System.out.printf("✓ Aggiunto: %s - %.1f%n", nome, voto);
        }
        
        if (nomi.isEmpty()) {
            System.out.println("Nessuno studente inserito.");
            return;
        }
        
        // Statistiche
        double somma = voti.stream().mapToDouble(Double::doubleValue).sum();
        double media = somma / voti.size();
        double max = voti.stream().mapToDouble(Double::doubleValue).max().orElse(0);
        double min = voti.stream().mapToDouble(Double::doubleValue).min().orElse(0);
        long promossi = voti.stream().mapToLong(v -> v >= 6 ? 1 : 0).sum();
        
        // Stampa riepilogo
        System.out.println("\n" + "=".repeat(60));
        System.out.println("                    RIEPILOGO CLASSE");
        System.out.println("=".repeat(60));
        System.out.printf("| %-20s | %8s | %12s |%n", "Nome", "Voto", "Esito");
        System.out.println("+" + "-".repeat(22) + "+" + "-".repeat(10) + "+" + "-".repeat(14) + "+");
        
        for (int i = 0; i < nomi.size(); i++) {
            String nome = nomi.get(i);
            double voto = voti.get(i);
            String esito = voto >= 6 ? "✓ Promosso" : "✗ Bocciato";
            System.out.printf("| %-20s | %8.1f | %12s |%n", nome, voto, esito);
        }
        
        System.out.println("+" + "-".repeat(22) + "+" + "-".repeat(10) + "+" + "-".repeat(14) + "+");
        System.out.printf("| %-20s | %8.1f | %12s |%n", "MEDIA CLASSE", media, "");
        System.out.println("=".repeat(60));
        
        // Statistiche dettagliate
        System.out.printf("Studenti totali: %d%n", nomi.size());
        System.out.printf("Promossi: %d (%.1f%%)%n", promossi, (double)promossi/nomi.size()*100);
        System.out.printf("Bocciati: %d (%.1f%%)%n", nomi.size()-promossi, (double)(nomi.size()-promossi)/nomi.size()*100);
        System.out.printf("Voto massimo: %.1f%n", max);
        System.out.printf("Voto minimo: %.1f%n", min);
        
        // Salvataggio su file
        try (PrintWriter writer = new PrintWriter("registro_studenti.txt")) {
            writer.println("REGISTRO STUDENTI - " + LocalDateTime.now().format(
                DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm")));
            writer.println("=".repeat(50));
            
            for (int i = 0; i < nomi.size(); i++) {
                writer.printf("%-20s: %.1f (%s)%n", nomi.get(i), voti.get(i), 
                             voti.get(i) >= 6 ? "Promosso" : "Bocciato");
            }
            
            writer.println("-".repeat(50));
            writer.printf("Media classe: %.2f%n", media);
            writer.printf("Promossi: %d/%d (%.1f%%)%n", promossi, nomi.size(), 
                         (double)promossi/nomi.size()*100);
            
            System.out.println("✓ Registro salvato in 'registro_studenti.txt'");
            
        } catch (IOException e) {
            System.out.println("❌ Errore nel salvataggio: " + e.getMessage());
        }
    }
}
