/**
 * ESERCIZIO D.2 - Sistema di Gestione Biblioteca con Strutture Iterative
 * 
 * OBIETTIVO:
 * Sviluppare un sistema completo per la gestione di una biblioteca che utilizzi
 * principalmente strutture iterative (for, while, do-while) insieme alle
 * istruzioni decisionali per creare un'applicazione complessa e realistica.
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 1. Gestione catalogo libri con ricerca e filtraggio
 * 2. Sistema prestiti con calcolo scadenze e multe
 * 3. Statistiche e report automatici
 * 4. Generazione codici ISBN e validazione
 * 5. Backup e ripristino dati
 * 6. Menu interattivo con navigazione complessa
 * 
 * CONCETTI APPLICATI:
 * - Cicli for con contatori e iteratori
 * - Cicli while per condizioni dinamiche
 * - Cicli do-while per menu e validazioni
 * - Cicli annidati per elaborazioni complesse
 * - Break e continue per controllo flusso
 * - Combinazione cicli + condizioni
 * - Pattern di ricerca e ordinamento
 * - Elaborazione batch di dati
 * 
 * @author Studente
 * @version 1.0
 */

import java.util.Scanner;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.text.DecimalFormat;

public class Esercizio02_GestioneBiblioteca {
    
    // Costanti del sistema
    private static final int MAX_LIBRI = 1000;
    private static final int MAX_PRESTITI = 500;
    private static final int GIORNI_PRESTITO = 14;
    private static final double MULTA_GIORNALIERA = 0.50;
    private static final DecimalFormat formattoMoneta = new DecimalFormat("#0.00€");
    private static final DateTimeFormatter formattoData = DateTimeFormatter.ofPattern("dd/MM/yyyy");
    
    // Arrays per simulare database
    private static String[] titoli = new String[MAX_LIBRI];
    private static String[] autori = new String[MAX_LIBRI];
    private static String[] isbn = new String[MAX_LIBRI];
    private static boolean[] disponibili = new boolean[MAX_LIBRI];
    private static int numeroLibri = 0;
    
    // Prestiti attivi
    private static String[] prestiti_isbn = new String[MAX_PRESTITI];
    private static String[] prestiti_utente = new String[MAX_PRESTITI];
    private static LocalDate[] prestiti_data = new LocalDate[MAX_PRESTITI];
    private static int numeroPrestiti = 0;
    
    private static Scanner scanner = new Scanner(System.in);
    
    /**
     * Menu principale con navigazione iterativa
     */
    public static void main(String[] args) {
        // Inizializzazione dati di esempio
        inizializzaDatiEsempio();
        
        System.out.println("╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║              SISTEMA GESTIONE BIBLIOTECA                     ║");
        System.out.println("║         Esercizio D.2 - Strutture Iterative                 ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");
        
        // Ciclo principale del programma (do-while)
        boolean continua;
        do {
            mostraMenuPrincipale();
            int scelta = leggiIntero("👉 Seleziona un'opzione: ");
            continua = processaSceltaPrincipale(scelta);
            
            if (continua) {
                System.out.println("\n⏸️ Premi INVIO per continuare...");
                scanner.nextLine();
            }
        } while (continua);
        
        System.out.println("👋 Grazie per aver utilizzato il Sistema Biblioteca!");
        scanner.close();
    }
    
    /**
     * TODO 1: Implementare il menu principale con do-while
     * REQUISITI:
     * - Mostrare opzioni in formato tabellare
     * - Gestire input non validi con ciclo di validazione
     * - Implementare sottomenu per ogni categoria
     * - Contare e mostrare statistiche in tempo reale
     * - Permettere navigazione avanti/indietro
     */
    private static void mostraMenuPrincipale() {
        System.out.println("\n╔═══════════════════════════════════════════════════════════════╗");
        System.out.println("║                    MENU PRINCIPALE                           ║");
        System.out.println("╠═══════════════════════════════════════════════════════════════╣");
        System.out.printf("║ 📚 CATALOGO           │ 🔄 PRESTITI          │ 📊 REPORT    ║%n");
        System.out.println("║ 1. Aggiungi libro     │ 5. Nuovo prestito    │ 9. Statistiche║");
        System.out.println("║ 2. Cerca libri        │ 6. Restituisci libro │10. Report     ║");
        System.out.println("║ 3. Lista completa     │ 7. Lista prestiti    │11. Backup     ║");
        System.out.println("║ 4. Modifica libro     │ 8. Calcola multe     │12. Ripristina ║");
        System.out.println("╠═══════════════════════════════════════════════════════════════╣");
        System.out.printf("║ 📖 Libri totali: %-3d │ 🔄 Prestiti attivi: %-3d │ 0. Esci   ║%n", 
                          numeroLibri, numeroPrestiti);
        System.out.println("╚═══════════════════════════════════════════════════════════════╝");
    }
    
    /**
     * TODO 2: Processare scelta menu con switch e cicli
     * REQUISITI:
     * - Switch completo per tutte le opzioni
     * - Cicli while per operazioni ripetitive
     * - Gestione errori con continue/break
     * - Validazione input con cicli di controllo
     * - Sottomenu con logica iterativa
     */
    private static boolean processaSceltaPrincipale(int scelta) {
        // TODO: Implementare switch con tutti i casi
        // TODO: Ogni caso deve gestire la propria logica iterativa
        // TODO: Restituire false solo per uscita (caso 0)
        
        System.out.println("⚠️ Funzione da implementare: processaSceltaPrincipale()");
        return true; // Placeholder
    }
    
    /**
     * TODO 3: Implementare aggiunta libro con validazione iterativa
     * REQUISITI:
     * - Ciclo do-while per input con validazione
     * - Controllo duplicati ISBN con ciclo for
     * - Generazione automatica ISBN se richiesto
     * - Validazione formato dati con while
     * - Conferma finale prima dell'inserimento
     */
    private static void aggiungiLibro() {
        System.out.println("\n=== 📚 AGGIUNGI NUOVO LIBRO ===");
        
        // TODO: Implementare controllo spazio disponibile
        
        // TODO: Input titolo con validazione (non vuoto, lunghezza min/max)
        String titolo = "";
        
        // TODO: Input autore con validazione
        String autore = "";
        
        // TODO: Input/generazione ISBN con controllo duplicati
        String codiceFsbn = "";
        
        // TODO: Conferma e salvataggio
        
        System.out.println("⚠️ Funzione da implementare: aggiungiLibro()");
    }
    
    /**
     * TODO 4: Implementare ricerca libri con cicli multipli
     * REQUISITI:
     * - Menu scelta tipo ricerca (titolo/autore/ISBN)
     * - Ciclo for per scansione completa catalogo
     * - Ricerca parziale case-insensitive
     * - Ordinamento risultati con cicli annidati
     * - Paginazione risultati con while
     * - Opzioni filtraggio avanzato
     */
    private static void cercaLibri() {
        System.out.println("\n=== 🔍 RICERCA LIBRI ===");
        
        // TODO: Sottomenu tipo ricerca
        
        // TODO: Input termine di ricerca
        
        // TODO: Esecuzione ricerca con cicli
        
        // TODO: Visualizzazione risultati paginati
        
        System.out.println("⚠️ Funzione da implementare: cercaLibri()");
    }
    
    /**
     * TODO 5: Implementare lista completa con paginazione
     * REQUISITI:
     * - Ordinamento alfabetico con bubble sort (cicli annidati)
     * - Paginazione con controlli avanti/indietro
     * - Filtri stato (disponibile/prestato)
     * - Contatori e statistiche in tempo reale
     * - Formattazione tabellare professionale
     */
    private static void listaCompleta() {
        System.out.println("\n=== 📋 CATALOGO COMPLETO ===");
        
        if (numeroLibri == 0) {
            // TODO: Gestire caso catalogo vuoto
            System.out.println("📚 Il catalogo è vuoto. Aggiungi alcuni libri!");
            return;
        }
        
        // TODO: Implementare ordinamento
        
        // TODO: Implementare paginazione
        
        // TODO: Mostrare statistiche
        
        System.out.println("⚠️ Funzione da implementare: listaCompleta()");
    }
    
    /**
     * TODO 6: Implementare sistema prestiti con date
     * REQUISITI:
     * - Ricerca libro disponibile con ciclo
     * - Input utente con validazione
     * - Calcolo data scadenza
     * - Aggiornamento stato libro
     * - Registrazione prestito
     * - Conferma con riepilogo
     */
    private static void nuovoPrestito() {
        System.out.println("\n=== 🔄 NUOVO PRESTITO ===");
        
        // TODO: Controllo disponibilità slot prestiti
        
        // TODO: Ricerca e selezione libro
        
        // TODO: Input dati utente
        
        // TODO: Registrazione prestito
        
        System.out.println("⚠️ Funzione da implementare: nuovoPrestito()");
    }
    
    /**
     * TODO 7: Implementare restituzione con calcolo multe
     * REQUISITI:
     * - Ricerca prestito attivo con cicli
     * - Calcolo giorni ritardo
     * - Calcolo multe automatico
     * - Aggiornamento stati con cicli
     * - Report restituzione
     * - Gestione pagamento multa
     */
    private static void restituisciLibro() {
        System.out.println("\n=== 📤 RESTITUZIONE LIBRO ===");
        
        if (numeroPrestiti == 0) {
            System.out.println("📋 Nessun prestito attivo al momento.");
            return;
        }
        
        // TODO: Lista prestiti attivi
        
        // TODO: Selezione prestito da restituire
        
        // TODO: Calcolo multa se in ritardo
        
        // TODO: Processare restituzione
        
        System.out.println("⚠️ Funzione da implementare: restituisciLibro()");
    }
    
    /**
     * TODO 8: Implementare calcolo multe con cicli
     * REQUISITI:
     * - Scansione tutti i prestiti attivi
     * - Calcolo giorni ritardo per ciascuno
     * - Applicazione tariffe progressive
     * - Raggruppamento per utente
     * - Report dettagliato multe
     * - Totali e statistiche
     */
    private static void calcolaMulte() {
        System.out.println("\n=== 💰 CALCOLO MULTE ===");
        
        if (numeroPrestiti == 0) {
            System.out.println("📋 Nessun prestito attivo per il calcolo multe.");
            return;
        }
        
        // TODO: Scansione prestiti con calcolo ritardi
        
        // TODO: Calcolo multe progressive
        
        // TODO: Raggruppamento per utente
        
        // TODO: Report dettagliato
        
        System.out.println("⚠️ Funzione da implementare: calcolaMulte()");
    }
    
    /**
     * TODO 9: Implementare statistiche avanzate
     * REQUISITI:
     * - Contatori con cicli for
     * - Calcoli percentuali
     * - Identificazione trend con cicli
     * - Top libri/autori più prestati
     * - Analisi temporale prestiti
     * - Grafici ASCII con cicli annidati
     */
    private static void mostraStatistiche() {
        System.out.println("\n=== 📊 STATISTICHE SISTEMA ===");
        
        // TODO: Statistiche generali catalogo
        
        // TODO: Statistiche prestiti
        
        // TODO: Analisi temporale
        
        // TODO: Top rankings
        
        System.out.println("⚠️ Funzione da implementare: mostraStatistiche()");
    }
    
    /**
     * TODO 10: Implementare generazione report
     * REQUISITI:
     * - Cicli per elaborazione dati
     * - Formattazione tabellare complessa
     * - Export su "file" (simulato con output)
     * - Report personalizzabili
     * - Totali e riepiloghi
     * - Grafici ASCII
     */
    private static void generaReport() {
        System.out.println("\n=== 📋 GENERAZIONE REPORT ===");
        
        // TODO: Menu selezione tipo report
        
        // TODO: Elaborazione dati con cicli
        
        // TODO: Formattazione output
        
        // TODO: Simulazione export
        
        System.out.println("⚠️ Funzione da implementare: generaReport()");
    }
    
    /**
     * Utility: Inizializza alcuni dati di esempio
     */
    private static void inizializzaDatiEsempio() {
        // Alcuni libri di esempio
        aggiungiLibroEsempio("Il Nome della Rosa", "Umberto Eco", "978-8845292613");
        aggiungiLibroEsempio("1984", "George Orwell", "978-8804706038");
        aggiungiLibroEsempio("Il Piccolo Principe", "Antoine de Saint-Exupéry", "978-8807901034");
        aggiungiLibroEsempio("Cento Anni di Solitudine", "Gabriel García Márquez", "978-8804677021");
        aggiungiLibroEsempio("Il Signore degli Anelli", "J.R.R. Tolkien", "978-8845292804");
        
        // Alcuni prestiti di esempio
        aggiungiPrestitoEsempio("978-8845292613", "Mario Rossi", LocalDate.now().minusDays(10));
        aggiungiPrestitoEsempio("978-8804706038", "Laura Bianchi", LocalDate.now().minusDays(20));
    }
    
    /**
     * Utility: Aggiunge libro di esempio
     */
    private static void aggiungiLibroEsempio(String titolo, String autore, String isbnCode) {
        if (numeroLibri < MAX_LIBRI) {
            titoli[numeroLibri] = titolo;
            autori[numeroLibri] = autore;
            isbn[numeroLibri] = isbnCode;
            disponibili[numeroLibri] = true;
            numeroLibri++;
        }
    }
    
    /**
     * Utility: Aggiunge prestito di esempio
     */
    private static void aggiungiPrestitoEsempio(String isbnCode, String utente, LocalDate data) {
        if (numeroPrestiti < MAX_PRESTITI) {
            prestiti_isbn[numeroPrestiti] = isbnCode;
            prestiti_utente[numeroPrestiti] = utente;
            prestiti_data[numeroPrestiti] = data;
            
            // Segna libro come non disponibile
            for (int i = 0; i < numeroLibri; i++) {
                if (isbn[i].equals(isbnCode)) {
                    disponibili[i] = false;
                    break;
                }
            }
            
            numeroPrestiti++;
        }
    }
    
    /**
     * TODO 11: Implementare generazione ISBN automatica
     * REQUISITI:
     * - Algoritmo checksum ISBN-13
     * - Validazione formato con cicli
     * - Controllo unicità con ricerca
     * - Generazione sequenziale o random
     * - Formattazione standard
     */
    private static String generaISBN() {
        // TODO: Implementare generazione ISBN-13 valido
        return "978-XXXXXXXXX"; // Placeholder
    }
    
    /**
     * TODO 12: Implementare validazione ISBN
     * REQUISITI:
     * - Controllo formato con regex o cicli
     * - Verifica checksum
     * - Controllo duplicati nel catalogo
     * - Gestione errori specifici
     */
    private static boolean validaISBN(String isbnCode) {
        // TODO: Implementare validazione completa
        return isbnCode != null && isbnCode.length() > 10; // Placeholder
    }
    
    /**
     * Utility: Legge intero con validazione
     */
    private static int leggiIntero(String messaggio) {
        int numero;
        do {
            System.out.print(messaggio);
            try {
                numero = Integer.parseInt(scanner.nextLine());
                return numero;
            } catch (NumberFormatException e) {
                System.out.println("❌ Errore: Inserisci un numero intero valido!");
            }
        } while (true);
    }
    
    /**
     * Utility: Legge stringa non vuota con validazione
     */
    private static String leggiStringa(String messaggio) {
        String input;
        do {
            System.out.print(messaggio);
            input = scanner.nextLine().trim();
            if (!input.isEmpty()) {
                return input;
            }
            System.out.println("❌ Errore: Il campo non può essere vuoto!");
        } while (true);
    }
    
    /**
     * TODO 13: Implementare ordinamento bubble sort
     * REQUISITI:
     * - Cicli annidati for classici
     * - Confronto lessicografico stringhe
     * - Scambio elementi multipli (titolo, autore, isbn, disponibilità)
     * - Ottimizzazione con flag early termination
     * - Contatore operazioni per statistiche
     */
    private static void ordinaPerTitolo() {
        // TODO: Implementare bubble sort completo per ordinamento alfabetico
        System.out.println("⚠️ Funzione da implementare: ordinaPerTitolo()");
    }
    
    /**
     * TODO 14: Implementare ricerca binaria (dopo ordinamento)
     * REQUISITI:
     * - Prerequisito: array ordinato
     * - Ciclo while con calcolo mid
     * - Confronto case-insensitive
     * - Restituzione indice o -1
     * - Contatore iterazioni per analisi performance
     */
    private static int ricercaBinaria(String termineRicerca) {
        // TODO: Implementare ricerca binaria efficiente
        return -1; // Placeholder
    }
}
