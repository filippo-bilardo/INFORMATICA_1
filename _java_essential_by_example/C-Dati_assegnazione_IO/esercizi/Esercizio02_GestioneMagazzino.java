/**
 * ESERCIZIO C.2 - Sistema di Gestione Magazzino
 * 
 * OBIETTIVO:
 * Creare un sistema per gestire un magazzino di prodotti che dimostri
 * l'uso avanzato di input/output, formattazione e gestione dati.
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 1. Inserimento prodotti con validazione input
 * 2. Calcolo automatico di prezzi e sconti
 * 3. Gestione inventario con quantità e soglie
 * 4. Report formattati con tabelle e statistiche
 * 5. Input/Output da tastiera con menu interattivo
 * 
 * CONCETTI APPLICATI:
 * - Input/Output formattato con printf
 * - Validazione e gestione errori input
 * - Calcoli con precision decimal
 * - Formattazione valute e percentuali
 * - Strutture dati semplici (array paralleli)
 * - Logica di business con controlli
 * 
 * @author Studente
 * @version 1.0
 */

import java.util.Scanner;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Locale;

public class Esercizio02_GestioneMagazzino {
    
    // Costanti per la configurazione del sistema
    private static final int MAX_PRODOTTI = 50;
    private static final double IVA_STANDARD = 0.22; // 22%
    private static final double SOGLIA_SCORTE_BASSE = 10;
    
    // Array paralleli per memorizzare i dati dei prodotti
    private static String[] codici = new String[MAX_PRODOTTI];
    private static String[] nomi = new String[MAX_PRODOTTI];
    private static String[] categorie = new String[MAX_PRODOTTI];
    private static double[] prezziUnitari = new double[MAX_PRODOTTI];
    private static int[] quantita = new int[MAX_PRODOTTI];
    private static double[] sconti = new double[MAX_PRODOTTI]; // Percentuale sconto
    private static boolean[] attivi = new boolean[MAX_PRODOTTI];
    
    private static int numProdotti = 0;
    
    // Formattatori per output
    private static final DecimalFormat formattoPrezzo = new DecimalFormat("#,##0.00 €");
    private static final DecimalFormat formattoPercentuale = new DecimalFormat("#0.0%");
    private static final NumberFormat formattoValuta = NumberFormat.getCurrencyInstance(Locale.ITALY);
    
    private static Scanner scanner = new Scanner(System.in);
    
    /**
     * Menu principale del sistema
     */
    public static void main(String[] args) {
        System.out.println("=== SISTEMA GESTIONE MAGAZZINO ===");
        System.out.println("Esercizio C.2 - Input/Output e Formattazione\n");
        
        // Carica dati di esempio
        caricaDatiEsempio();
        
        boolean continua = true;
        while (continua) {
            mostraMenu();
            int scelta = leggiIntero("👉 Inserisci la tua scelta: ");
            
            switch (scelta) {
                case 1:
                    inserisciProdotto();
                    break;
                case 2:
                    visualizzaProdotti();
                    break;
                case 3:
                    modificaProdotto();
                    break;
                case 4:
                    calcolaValore();
                    break;
                case 5:
                    gestioneInventario();
                    break;
                case 6:
                    generaReport();
                    break;
                case 7:
                    ricercaProdotti();
                    break;
                case 0:
                    continua = false;
                    System.out.println("👋 Arrivederci!");
                    break;
                default:
                    System.out.println("❌ Scelta non valida!");
            }
            System.out.println();
        }
        
        scanner.close();
    }
    
    /**
     * Mostra il menu principale
     */
    private static void mostraMenu() {
        System.out.println("╔══════════════════════════════════╗");
        System.out.println("║         MENU PRINCIPALE          ║");
        System.out.println("╠══════════════════════════════════╣");
        System.out.println("║ 1. 📦 Inserisci nuovo prodotto  ║");
        System.out.println("║ 2. 📋 Visualizza prodotti       ║");
        System.out.println("║ 3. ✏️  Modifica prodotto         ║");
        System.out.println("║ 4. 💰 Calcola valore magazzino  ║");
        System.out.println("║ 5. 📊 Gestione inventario       ║");
        System.out.println("║ 6. 📄 Genera report             ║");
        System.out.println("║ 7. 🔍 Ricerca prodotti          ║");
        System.out.println("║ 0. 🚪 Esci                       ║");
        System.out.println("╚══════════════════════════════════╝");
    }
    
    /**
     * TODO 1: Implementare inserimento nuovo prodotto
     * VALIDAZIONI RICHIESTE:
     * - Codice univoco e formato corretto
     * - Nome non vuoto
     * - Prezzo positivo
     * - Quantità non negativa
     * - Sconto tra 0 e 100%
     */
    private static void inserisciProdotto() {
        System.out.println("=== 📦 INSERIMENTO NUOVO PRODOTTO ===");
        
        if (numProdotti >= MAX_PRODOTTI) {
            System.out.println("❌ Magazzino pieno! Impossibile aggiungere altri prodotti.");
            return;
        }
        
        // TODO: Implementare raccolta e validazione dati
        
        // 1. Codice prodotto (formato: PRD-XXXX)
        String codice;
        do {
            System.out.print("📝 Codice prodotto (formato PRD-XXXX): ");
            codice = scanner.nextLine().trim().toUpperCase();
            
            // TODO: Validare formato e unicità del codice
            
        } while (false); // Sostituire con condizione di validazione
        
        // 2. Nome prodotto
        String nome;
        do {
            System.out.print("📝 Nome prodotto: ");
            nome = scanner.nextLine().trim();
            
            // TODO: Validare nome non vuoto
            
        } while (false); // Sostituire con condizione di validazione
        
        // 3. Categoria
        String categoria = scegliCategoria();
        
        // 4. Prezzo unitario
        double prezzo;
        do {
            prezzo = leggiDouble("💰 Prezzo unitario (€): ");
            
            // TODO: Validare prezzo positivo
            
        } while (false); // Sostituire con condizione di validazione
        
        // 5. Quantità iniziale
        int qta;
        do {
            qta = leggiIntero("📦 Quantità iniziale: ");
            
            // TODO: Validare quantità non negativa
            
        } while (false); // Sostituire con condizione di validazione
        
        // 6. Sconto (opzionale)
        double sconto = 0;
        System.out.print("🏷️ Sconto % (0-100, invio per saltare): ");
        String scontoStr = scanner.nextLine().trim();
        if (!scontoStr.isEmpty()) {
            try {
                sconto = Double.parseDouble(scontoStr);
                // TODO: Validare sconto nel range 0-100
            } catch (NumberFormatException e) {
                System.out.println("⚠️ Sconto non valido, impostato a 0%");
                sconto = 0;
            }
        }
        
        // TODO: Salvare il prodotto negli array
        
        System.out.println("✅ Prodotto inserito con successo!");
        stampaProdotto(numProdotti - 1); // Mostra il prodotto appena inserito
    }
    
    /**
     * TODO 2: Implementare visualizzazione prodotti in formato tabellare
     * FORMATO RICHIESTO:
     * - Tabella con bordi e allineamento
     * - Colonne: Codice, Nome, Categoria, Prezzo, Quantità, Sconto, Valore
     * - Prezzi formattati come valuta
     * - Percentuali formattate correttamente
     */
    private static void visualizzaProdotti() {
        System.out.println("=== 📋 LISTA PRODOTTI ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto presente nel magazzino.");
            return;
        }
        
        // TODO: Implementare visualizzazione tabellare
        System.out.println("┌──────────┬────────────────────┬─────────────┬───────────┬─────────┬─────────┬─────────────┐");
        System.out.println("│  CODICE  │        NOME        │  CATEGORIA  │   PREZZO  │   QTÀ   │ SCONTO  │    VALORE   │");
        System.out.println("├──────────┼────────────────────┼─────────────┼───────────┼─────────┼─────────┼─────────────┤");
        
        // TODO: Ciclo per mostrare tutti i prodotti
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                // TODO: Formattare e stampare ogni riga
                double valoreTotale = calcolaValoreProdotto(i);
                
                System.out.printf("│ %-8s │ %-18s │ %-11s │ %9s │ %7d │ %6s  │ %11s │%n",
                    codici[i],
                    limitaStringa(nomi[i], 18),
                    limitaStringa(categorie[i], 11),
                    formattoPrezzo.format(prezziUnitari[i]),
                    quantita[i],
                    formattoPercentuale.format(sconti[i] / 100),
                    formattoPrezzo.format(valoreTotale)
                );
            }
        }
        
        System.out.println("└──────────┴────────────────────┴─────────────┴───────────┴─────────┴─────────┴─────────────┘");
        
        // TODO: Mostrare statistiche riassuntive
        System.out.printf("📊 Totale prodotti: %d | Valore totale magazzino: %s%n", 
                         contaProdottiAttivi(), formattoPrezzo.format(calcolaValoreTotale()));
    }
    
    /**
     * TODO 3: Implementare modifica prodotto esistente
     * FUNZIONALITÀ:
     * - Ricerca prodotto per codice
     * - Menu per scegliere campo da modificare
     * - Validazione nuovi valori
     * - Conferma modifiche
     */
    private static void modificaProdotto() {
        System.out.println("=== ✏️ MODIFICA PRODOTTO ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto da modificare.");
            return;
        }
        
        // TODO: Implementare ricerca e modifica
        System.out.print("🔍 Inserisci codice prodotto da modificare: ");
        String codice = scanner.nextLine().trim().toUpperCase();
        
        int indice = trovaProdotto(codice);
        if (indice == -1) {
            System.out.println("❌ Prodotto non trovato!");
            return;
        }
        
        // Mostra prodotto corrente
        System.out.println("\n📦 PRODOTTO CORRENTE:");
        stampaProdotto(indice);
        
        // TODO: Menu per scegliere cosa modificare
        System.out.println("\n🛠️ COSA VUOI MODIFICARE?");
        System.out.println("1. Nome");
        System.out.println("2. Categoria");
        System.out.println("3. Prezzo");
        System.out.println("4. Quantità");
        System.out.println("5. Sconto");
        System.out.println("6. Disattiva prodotto");
        System.out.println("0. Annulla");
        
        int scelta = leggiIntero("👉 Scelta: ");
        
        // TODO: Implementare le modifiche in base alla scelta
        switch (scelta) {
            case 1:
                // Modifica nome
                break;
            case 2:
                // Modifica categoria
                break;
            case 3:
                // Modifica prezzo
                break;
            case 4:
                // Modifica quantità
                break;
            case 5:
                // Modifica sconto
                break;
            case 6:
                // Disattiva prodotto
                break;
            case 0:
                System.out.println("❌ Modifica annullata.");
                return;
            default:
                System.out.println("❌ Scelta non valida!");
                return;
        }
        
        System.out.println("✅ Prodotto modificato con successo!");
        System.out.println("\n📦 PRODOTTO AGGIORNATO:");
        stampaProdotto(indice);
    }
    
    /**
     * TODO 4: Implementare calcolo valore magazzino
     * CALCOLI RICHIESTI:
     * - Valore lordo (prezzo × quantità)
     * - Valore con sconti applicati
     * - IVA totale
     * - Valore finale
     * - Statistiche per categoria
     */
    private static void calcolaValore() {
        System.out.println("=== 💰 CALCOLO VALORE MAGAZZINO ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto nel magazzino.");
            return;
        }
        
        // TODO: Implementare calcoli dettagliati
        double valoreLordo = 0;
        double valoreConSconti = 0;
        double totaleSconti = 0;
        
        System.out.println("📊 DETTAGLIO CALCOLI:");
        System.out.println("┌──────────┬─────────────┬─────────────┬─────────────┬─────────────┐");
        System.out.println("│  CODICE  │ VAL. LORDO  │   SCONTO    │ VAL. SCONTO │ VAL. FINALE │");
        System.out.println("├──────────┼─────────────┼─────────────┼─────────────┼─────────────┤");
        
        // TODO: Ciclo per calcolare ogni prodotto
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                // TODO: Calcolare valori per ogni prodotto
                double valLordo = prezziUnitari[i] * quantita[i];
                double valSconto = valLordo * (sconti[i] / 100);
                double valFinale = valLordo - valSconto;
                
                valoreLordo += valLordo;
                totaleSconti += valSconto;
                valoreConSconti += valFinale;
                
                System.out.printf("│ %-8s │ %11s │ %11s │ %11s │ %11s │%n",
                    codici[i],
                    formattoPrezzo.format(valLordo),
                    formattoPrezzo.format(valSconto),
                    formattoPrezzo.format(valFinale),
                    formattoPrezzo.format(valFinale)
                );
            }
        }
        
        System.out.println("└──────────┴─────────────┴─────────────┴─────────────┴─────────────┘");
        
        // TODO: Calcoli finali con IVA
        double iva = valoreConSconti * IVA_STANDARD;
        double valoreTotaleConIVA = valoreConSconti + iva;
        
        System.out.println("\n💰 RIEPILOGO FINANZIARIO:");
        System.out.printf("💸 Valore lordo magazzino: %s%n", formattoPrezzo.format(valoreLordo));
        System.out.printf("🏷️ Totale sconti applicati: %s (%s)%n", 
                         formattoPrezzo.format(totaleSconti),
                         formattoPercentuale.format(totaleSconti / valoreLordo));
        System.out.printf("💵 Valore netto (con sconti): %s%n", formattoPrezzo.format(valoreConSconti));
        System.out.printf("🏛️ IVA (%s): %s%n", 
                         formattoPercentuale.format(IVA_STANDARD),
                         formattoPrezzo.format(iva));
        System.out.printf("💎 VALORE TOTALE CON IVA: %s%n", formattoPrezzo.format(valoreTotaleConIVA));
    }
    
    /**
     * TODO 5: Implementare gestione inventario
     * FUNZIONALITÀ:
     * - Visualizzare prodotti con scorte basse
     * - Aggiornare quantità (carico/scarico)
     * - Calcolare movimenti inventario
     * - Alert automatici
     */
    private static void gestioneInventario() {
        System.out.println("=== 📊 GESTIONE INVENTARIO ===");
        
        System.out.println("1. 🔍 Visualizza scorte basse");
        System.out.println("2. 📦 Carico merce");
        System.out.println("3. 📤 Scarico merce");
        System.out.println("4. 📋 Report inventario");
        
        int scelta = leggiIntero("👉 Scelta: ");
        
        switch (scelta) {
            case 1:
                visualizzaScorteBasse();
                break;
            case 2:
                caricoMerce();
                break;
            case 3:
                scaricoMerce();
                break;
            case 4:
                reportInventario();
                break;
            default:
                System.out.println("❌ Scelta non valida!");
        }
    }
    
    /**
     * TODO 6: Implementare generazione report completo
     * SEZIONI REPORT:
     * - Intestazione con data/ora
     * - Lista prodotti completa
     * - Statistiche per categoria
     * - Analisi scorte
     * - Riepilogo finanziario
     */
    private static void generaReport() {
        System.out.println("=== 📄 GENERAZIONE REPORT ===");
        
        // TODO: Implementare report completo
        System.out.println("╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║                    REPORT MAGAZZINO                         ║");
        System.out.println("║                  " + java.time.LocalDateTime.now().format(
                          java.time.format.DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm")) + "                      ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");
        
        // TODO: Aggiungere tutte le sezioni del report
    }
    
    /**
     * TODO 7: Implementare ricerca prodotti
     * CRITERI DI RICERCA:
     * - Per codice (esatto)
     * - Per nome (parziale)
     * - Per categoria
     * - Per range di prezzo
     */
    private static void ricercaProdotti() {
        System.out.println("=== 🔍 RICERCA PRODOTTI ===");
        
        System.out.println("1. 🔤 Ricerca per codice");
        System.out.println("2. 📝 Ricerca per nome");
        System.out.println("3. 📂 Ricerca per categoria");
        System.out.println("4. 💰 Ricerca per range prezzo");
        
        int criterio = leggiIntero("👉 Criterio di ricerca: ");
        
        // TODO: Implementare i diversi tipi di ricerca
        switch (criterio) {
            case 1:
                // Ricerca per codice
                break;
            case 2:
                // Ricerca per nome
                break;
            case 3:
                // Ricerca per categoria
                break;
            case 4:
                // Ricerca per range prezzo
                break;
            default:
                System.out.println("❌ Criterio non valido!");
        }
    }
    
    // ==================== METODI DI UTILITÀ ====================
    
    /**
     * Metodo per scegliere una categoria da una lista predefinita
     */
    private static String scegliCategoria() {
        String[] categorie = {"ELETTRONICA", "ABBIGLIAMENTO", "CASA", "SPORT", "LIBRI", "ALTRO"};
        
        System.out.println("📂 Scegli categoria:");
        for (int i = 0; i < categorie.length; i++) {
            System.out.println((i + 1) + ". " + categorie[i]);
        }
        
        int scelta;
        do {
            scelta = leggiIntero("👉 Categoria (1-" + categorie.length + "): ");
        } while (scelta < 1 || scelta > categorie.length);
        
        return categorie[scelta - 1];
    }
    
    /**
     * Trova un prodotto per codice
     */
    private static int trovaProdotto(String codice) {
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && codici[i].equals(codice)) {
                return i;
            }
        }
        return -1;
    }
    
    /**
     * Calcola il valore totale di un prodotto (prezzo × quantità - sconto)
     */
    private static double calcolaValoreProdotto(int indice) {
        double valoreLordo = prezziUnitari[indice] * quantita[indice];
        double sconto = valoreLordo * (sconti[indice] / 100);
        return valoreLordo - sconto;
    }
    
    /**
     * Calcola il valore totale del magazzino
     */
    private static double calcolaValoreTotale() {
        double totale = 0;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                totale += calcolaValoreProdotto(i);
            }
        }
        return totale;
    }
    
    /**
     * Conta i prodotti attivi
     */
    private static int contaProdottiAttivi() {
        int count = 0;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) count++;
        }
        return count;
    }
    
    /**
     * Limita la lunghezza di una stringa per la formattazione tabellare
     */
    private static String limitaStringa(String str, int maxLength) {
        if (str.length() <= maxLength) {
            return str;
        }
        return str.substring(0, maxLength - 3) + "...";
    }
    
    /**
     * Stampa i dettagli di un singolo prodotto
     */
    private static void stampaProdotto(int indice) {
        System.out.printf("🏷️ %s - %s (%s)%n", codici[indice], nomi[indice], categorie[indice]);
        System.out.printf("   💰 Prezzo: %s | 📦 Quantità: %d | 🏷️ Sconto: %s%n",
                         formattoPrezzo.format(prezziUnitari[indice]),
                         quantita[indice],
                         formattoPercentuale.format(sconti[indice] / 100));
        System.out.printf("   💎 Valore totale: %s%n", formattoPrezzo.format(calcolaValoreProdotto(indice)));
    }
    
    /**
     * TODO: Implementare metodi di utilità per scorte basse
     */
    private static void visualizzaScorteBasse() {
        // TODO: Implementare
    }
    
    private static void caricoMerce() {
        // TODO: Implementare
    }
    
    private static void scaricoMerce() {
        // TODO: Implementare
    }
    
    private static void reportInventario() {
        // TODO: Implementare
    }
    
    /**
     * Metodi di utilità per input validato
     */
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
    
    /**
     * Carica dati di esempio per il testing
     */
    private static void caricaDatiEsempio() {
        // Prodotto 1
        codici[0] = "PRD-0001";
        nomi[0] = "Smartphone XYZ";
        categorie[0] = "ELETTRONICA";
        prezziUnitari[0] = 299.99;
        quantita[0] = 15;
        sconti[0] = 10.0;
        attivi[0] = true;
        
        // Prodotto 2
        codici[1] = "PRD-0002";
        nomi[1] = "T-Shirt Cotone";
        categorie[1] = "ABBIGLIAMENTO";
        prezziUnitari[1] = 19.90;
        quantita[1] = 5; // Scorte basse
        sconti[1] = 0.0;
        attivi[1] = true;
        
        // Prodotto 3
        codici[2] = "PRD-0003";
        nomi[2] = "Lampada LED";
        categorie[2] = "CASA";
        prezziUnitari[2] = 45.50;
        quantita[2] = 25;
        sconti[2] = 15.0;
        attivi[2] = true;
        
        numProdotti = 3;
        
        System.out.println("✅ Dati di esempio caricati (3 prodotti)");
        System.out.printf("💰 Valore magazzino: %s%n%n", formattoPrezzo.format(calcolaValoreTotale()));
    }
}
