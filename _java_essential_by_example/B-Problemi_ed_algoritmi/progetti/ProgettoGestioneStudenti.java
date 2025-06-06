/**
 * PROGETTO MODULO B - Sistema di Gestione Studenti
 * 
 * DESCRIZIONE PROGETTO:
 * Sviluppare un sistema completo per la gestione di studenti che dimostri
 * l'applicazione pratica dei concetti di problem solving e algoritmi.
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 1. Gestione studenti (inserimento, ricerca, eliminazione)
 * 2. Calcolo statistiche (media voti, migliore studente, ecc.)
 * 3. Ordinamento studenti per diversi criteri
 * 4. Ricerca efficiente studenti
 * 5. Esportazione dati e report
 * 
 * OBIETTIVI DIDATTICI:
 * - Applicare la metodologia di problem solving
 * - Implementare algoritmi di ordinamento e ricerca
 * - Analizzare e ottimizzare la complessità
 * - Gestire strutture dati complesse
 * - Progettare interfaccia utente semplice
 * 
 * COMPETENZE SVILUPPATE:
 * - Decomposizione di problemi complessi
 * - Implementazione algoritmi efficienti
 * - Gestione input/output
 * - Validazione dati
 * - Testing e debugging
 * 
 * @author Studente
 * @version 1.0
 */

import java.util.Scanner;

public class ProgettoGestioneStudenti {
    
    // Costanti per la configurazione
    private static final int MAX_STUDENTI = 100;
    private static final int MAX_VOTI = 10;
    
    // Array per memorizzare i dati degli studenti
    private static String[] nomi = new String[MAX_STUDENTI];
    private static String[] cognomi = new String[MAX_STUDENTI];
    private static int[] matricole = new int[MAX_STUDENTI];
    private static double[][] voti = new double[MAX_STUDENTI][MAX_VOTI]; // [studente][voto]
    private static int[] numVoti = new int[MAX_STUDENTI]; // numero di voti per studente
    private static int numStudenti = 0; // numero totale di studenti
    
    private static Scanner scanner = new Scanner(System.in);
    
    /**
     * Metodo principale - Menu del programma
     */
    public static void main(String[] args) {
        System.out.println("=== SISTEMA GESTIONE STUDENTI ===");
        System.out.println("Progetto Modulo B - Problemi ed Algoritmi\n");
        
        // Carica dati di esempio per testing
        caricaDatiEsempio();
        
        boolean continua = true;
        while (continua) {
            mostraMenu();
            int scelta = leggiIntero("Inserisci la tua scelta: ");
            
            switch (scelta) {
                case 1:
                    inserisciStudente();
                    break;
                case 2:
                    cercaStudente();
                    break;
                case 3:
                    visualizzaStudenti();
                    break;
                case 4:
                    ordinaStudenti();
                    break;
                case 5:
                    calcolaStatistiche();
                    break;
                case 6:
                    gestisciVoti();
                    break;
                case 7:
                    generaReport();
                    break;
                case 0:
                    continua = false;
                    System.out.println("Arrivederci!");
                    break;
                default:
                    System.out.println("Scelta non valida!");
            }
            System.out.println();
        }
        
        scanner.close();
    }
    
    /**
     * Mostra il menu principale
     */
    private static void mostraMenu() {
        System.out.println("=== MENU PRINCIPALE ===");
        System.out.println("1. Inserisci nuovo studente");
        System.out.println("2. Cerca studente");
        System.out.println("3. Visualizza tutti gli studenti");
        System.out.println("4. Ordina studenti");
        System.out.println("5. Calcola statistiche");
        System.out.println("6. Gestisci voti");
        System.out.println("7. Genera report");
        System.out.println("0. Esci");
        System.out.println("========================");
    }
    
    /**
     * TODO 1: Implementare inserimento nuovo studente
     * FUNZIONALITÀ:
     * - Leggere nome, cognome e matricola
     * - Validare che la matricola non esista già
     * - Aggiungere lo studente agli array
     * - Gestire il caso di array pieno
     */
    private static void inserisciStudente() {
        System.out.println("=== INSERIMENTO NUOVO STUDENTE ===");
        
        if (numStudenti >= MAX_STUDENTI) {
            System.out.println("❌ Impossibile aggiungere altri studenti (limite raggiunto)");
            return;
        }
        
        // TODO: Implementare la logica di inserimento
        // 1. Leggere nome e cognome
        // 2. Leggere matricola e verificare unicità
        // 3. Aggiungere agli array
        // 4. Incrementare numStudenti
        
        System.out.println("✅ Studente inserito con successo!");
    }
    
    /**
     * TODO 2: Implementare ricerca studente
     * ALGORITMI DA CONSIDERARE:
     * - Ricerca lineare per nome/cognome
     * - Ricerca binaria per matricola (se ordinato)
     */
    private static void cercaStudente() {
        System.out.println("=== RICERCA STUDENTE ===");
        System.out.println("1. Cerca per nome");
        System.out.println("2. Cerca per cognome"); 
        System.out.println("3. Cerca per matricola");
        
        int criterio = leggiIntero("Scegli criterio di ricerca: ");
        
        // TODO: Implementare i diversi tipi di ricerca
        switch (criterio) {
            case 1:
                // Ricerca per nome
                break;
            case 2:
                // Ricerca per cognome
                break;
            case 3:
                // Ricerca per matricola
                break;
            default:
                System.out.println("Criterio non valido!");
        }
    }
    
    /**
     * TODO 3: Implementare visualizzazione studenti
     * FUNZIONALITÀ:
     * - Mostrare tutti gli studenti in formato tabellare
     * - Includere media voti per ogni studente
     * - Gestire il caso di nessuno studente
     */
    private static void visualizzaStudenti() {
        System.out.println("=== LISTA STUDENTI ===");
        
        if (numStudenti == 0) {
            System.out.println("Nessuno studente inserito.");
            return;
        }
        
        // TODO: Implementare visualizzazione in formato tabella
        System.out.printf("%-20s %-20s %-10s %-10s%n", "NOME", "COGNOME", "MATRICOLA", "MEDIA");
        System.out.println("----------------------------------------------------------------");
        
        // Ciclo per mostrare tutti gli studenti
    }
    
    /**
     * TODO 4: Implementare ordinamento studenti
     * ALGORITMI DA IMPLEMENTARE:
     * - Ordinamento per cognome (alfabetico)
     * - Ordinamento per matricola (numerico)
     * - Ordinamento per media voti (decrescente)
     */
    private static void ordinaStudenti() {
        System.out.println("=== ORDINAMENTO STUDENTI ===");
        System.out.println("1. Ordina per cognome");
        System.out.println("2. Ordina per matricola");
        System.out.println("3. Ordina per media voti");
        
        int criterio = leggiIntero("Scegli criterio di ordinamento: ");
        
        long startTime = System.currentTimeMillis();
        
        switch (criterio) {
            case 1:
                // TODO: Ordinamento per cognome usando uno degli algoritmi studiati
                break;
            case 2:
                // TODO: Ordinamento per matricola
                break;
            case 3:
                // TODO: Ordinamento per media voti
                break;
            default:
                System.out.println("Criterio non valido!");
                return;
        }
        
        long endTime = System.currentTimeMillis();
        System.out.println("✅ Ordinamento completato in " + (endTime - startTime) + " ms");
    }
    
    /**
     * TODO 5: Implementare calcolo statistiche
     * STATISTICHE DA CALCOLARE:
     * - Media generale di tutti i voti
     * - Studente con media più alta
     * - Studente con media più bassa
     * - Numero di studenti per fascia di voto
     */
    private static void calcolaStatistiche() {
        System.out.println("=== STATISTICHE ===");
        
        if (numStudenti == 0) {
            System.out.println("Nessuno studente presente.");
            return;
        }
        
        // TODO: Implementare calcoli statistici
        double mediaGenerale = 0;
        int miglioreStudente = -1;
        int peggioreStudente = -1;
        
        // Calcolare le statistiche richieste
        
        System.out.println("📊 STATISTICHE GENERALI:");
        System.out.printf("• Media generale: %.2f%n", mediaGenerale);
        // Mostrare altre statistiche
    }
    
    /**
     * TODO 6: Implementare gestione voti
     * FUNZIONALITÀ:
     * - Aggiungere voto a uno studente
     * - Modificare voto esistente
     * - Eliminare voto
     * - Visualizzare voti di uno studente
     */
    private static void gestisciVoti() {
        System.out.println("=== GESTIONE VOTI ===");
        System.out.println("1. Aggiungi voto");
        System.out.println("2. Visualizza voti studente");
        System.out.println("3. Modifica voto");
        System.out.println("4. Elimina voto");
        
        int operazione = leggiIntero("Scegli operazione: ");
        
        // TODO: Implementare le operazioni sui voti
        switch (operazione) {
            case 1:
                // Aggiungere voto
                break;
            case 2:
                // Visualizzare voti
                break;
            case 3:
                // Modificare voto
                break;
            case 4:
                // Eliminare voto
                break;
        }
    }
    
    /**
     * TODO 7: Implementare generazione report
     * REPORT DA GENERARE:
     * - Report completo di tutti gli studenti
     * - Report studenti per fascia di voto
     * - Report statistiche dettagliate
     */
    private static void generaReport() {
        System.out.println("=== GENERAZIONE REPORT ===");
        
        // TODO: Implementare generazione di diversi tipi di report
        
        System.out.println("📋 REPORT STUDENTI - " + java.time.LocalDate.now());
        System.out.println("=====================================");
        
        // Generare report dettagliato
    }
    
    /**
     * Metodo di utilità per leggere un intero con gestione errori
     */
    private static int leggiIntero(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextInt()) {
            System.out.print("Inserisci un numero valido: ");
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
            System.out.print("Inserisci un numero valido: ");
            scanner.next();
        }
        double numero = scanner.nextDouble();
        scanner.nextLine(); // Consuma newline
        return numero;
    }
    
    /**
     * Metodo di utilità per calcolare la media voti di uno studente
     */
    private static double calcolaMedia(int indiceStudente) {
        if (numVoti[indiceStudente] == 0) {
            return 0.0;
        }
        
        double somma = 0;
        for (int i = 0; i < numVoti[indiceStudente]; i++) {
            somma += voti[indiceStudente][i];
        }
        
        return somma / numVoti[indiceStudente];
    }
    
    /**
     * Metodo per caricare dati di esempio per il testing
     */
    private static void caricaDatiEsempio() {
        // Studente 1
        nomi[0] = "Mario";
        cognomi[0] = "Rossi";
        matricole[0] = 12345;
        voti[0][0] = 8.5;
        voti[0][1] = 7.0;
        voti[0][2] = 9.0;
        numVoti[0] = 3;
        
        // Studente 2
        nomi[1] = "Laura";
        cognomi[1] = "Bianchi";
        matricole[1] = 12346;
        voti[1][0] = 9.5;
        voti[1][1] = 8.5;
        numVoti[1] = 2;
        
        // Studente 3
        nomi[2] = "Giuseppe";
        cognomi[2] = "Verdi";
        matricole[2] = 12347;
        voti[2][0] = 6.0;
        voti[2][1] = 7.5;
        voti[2][2] = 8.0;
        voti[2][3] = 7.0;
        numVoti[2] = 4;
        
        numStudenti = 3;
        
        System.out.println("✅ Dati di esempio caricati (3 studenti)");
        System.out.println("Puoi testare tutte le funzionalità!\n");
    }
    
    /**
     * TODO BONUS: Implementare funzionalità avanzate
     * 
     * 1. PERSISTENZA DATI:
     *    - Salvare/caricare dati da file
     *    - Backup automatico
     * 
     * 2. ALGORITMI AVANZATI:
     *    - Quick Sort per ordinamento veloce
     *    - Binary Search per ricerca veloce
     * 
     * 3. INTERFACCIA MIGLIORATA:
     *    - Colori nel terminale
     *    - Progress bar per operazioni lunghe
     *    - Menu dinamici
     * 
     * 4. VALIDAZIONE AVANZATA:
     *    - Controllo formato matricola
     *    - Validazione nome/cognome
     *    - Range voti configurabile
     * 
     * 5. ANALISI PRESTAZIONI:
     *    - Benchmark algoritmi
     *    - Profiling memoria
     *    - Statistiche d'uso
     */
}
