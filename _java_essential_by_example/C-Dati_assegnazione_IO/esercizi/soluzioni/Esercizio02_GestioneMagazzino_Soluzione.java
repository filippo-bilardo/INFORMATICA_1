/**
 * SOLUZIONE ESERCIZIO C.2 - Sistema di Gestione Magazzino
 * 
 * OBIETTIVO:
 * Sistema completo per gestire un magazzino di prodotti che dimostra
 * l'uso avanzato di input/output, formattazione e gestione dati.
 * 
 * FUNZIONALITÀ IMPLEMENTATE:
 * 1. Inserimento prodotti con validazione input completa
 * 2. Calcolo automatico di prezzi e sconti con precision decimal
 * 3. Gestione inventario con quantità e soglie di allerta
 * 4. Report formattati con tabelle e statistiche dettagliate
 * 5. Input/Output da tastiera con menu interattivo
 * 6. Ricerca avanzata con multipli criteri
 * 7. Sistema di carico/scarico merci
 * 
 * CONCETTI APPLICATI:
 * - Input/Output formattato con printf e DecimalFormat
 * - Validazione robusta e gestione errori input
 * - Calcoli con precision decimal per evitare errori floating-point
 * - Formattazione professionale di valute e percentuali
 * - Strutture dati semplici ottimizzate (array paralleli)
 * - Logica di business con controlli e validazioni
 * - Pattern di menu navigation con switch-case
 * - Gestione stato applicazione
 * 
 * @author Soluzione Ufficiale
 * @version 1.0
 */

import java.util.Scanner;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Locale;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class Esercizio02_GestioneMagazzino_Soluzione {
    
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
    
    // Formattatori per output professionale
    private static final DecimalFormat formattoPrezzo = new DecimalFormat("#,##0.00 €");
    private static final DecimalFormat formattoPercentuale = new DecimalFormat("#0.0%");
    private static final NumberFormat formattoValuta = NumberFormat.getCurrencyInstance(Locale.ITALY);
    private static final DateTimeFormatter formattoData = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
    
    private static Scanner scanner = new Scanner(System.in);
    
    /**
     * Menu principale del sistema
     */
    public static void main(String[] args) {
        System.out.println("╔════════════════════════════════════════╗");
        System.out.println("║     SISTEMA GESTIONE MAGAZZINO         ║");
        System.out.println("║   Esercizio C.2 - I/O e Formattazione  ║");
        System.out.println("╚════════════════════════════════════════╝");
        System.out.println();
        
        // Carica dati di esempio per il testing
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
                    System.out.println("\n👋 Grazie per aver utilizzato il sistema!");
                    System.out.println("💾 Tutti i dati sono stati salvati in memoria.");
                    break;
                default:
                    System.out.println("❌ Scelta non valida! Riprova.");
            }
            
            if (continua) {
                System.out.println("\n⏸️ Premi INVIO per continuare...");
                scanner.nextLine();
            }
        }
        
        scanner.close();
    }
    
    /**
     * Mostra il menu principale con interfaccia grafica ASCII
     */
    private static void mostraMenu() {
        System.out.println("\n╔══════════════════════════════════════╗");
        System.out.println("║            MENU PRINCIPALE           ║");
        System.out.println("╠══════════════════════════════════════╣");
        System.out.println("║ 1. 📦 Inserisci nuovo prodotto      ║");
        System.out.println("║ 2. 📋 Visualizza prodotti           ║");
        System.out.println("║ 3. ✏️  Modifica prodotto             ║");
        System.out.println("║ 4. 💰 Calcola valore magazzino      ║");
        System.out.println("║ 5. 📊 Gestione inventario           ║");
        System.out.println("║ 6. 📄 Genera report completo        ║");
        System.out.println("║ 7. 🔍 Ricerca prodotti              ║");
        System.out.println("║ 0. 🚪 Esci dal sistema              ║");
        System.out.println("╚══════════════════════════════════════╝");
    }
    
    /**
     * SOLUZIONE 1: Inserimento nuovo prodotto con validazione completa
     */
    private static void inserisciProdotto() {
        System.out.println("\n=== 📦 INSERIMENTO NUOVO PRODOTTO ===");
        
        if (numProdotti >= MAX_PRODOTTI) {
            System.out.println("❌ Magazzino pieno! Impossibile aggiungere altri prodotti.");
            System.out.printf("📊 Capacità massima: %d prodotti%n", MAX_PRODOTTI);
            return;
        }
        
        // 1. Validazione codice prodotto (formato: PRD-XXXX)
        String codice;
        do {
            System.out.print("📝 Codice prodotto (formato PRD-XXXX): ");
            codice = scanner.nextLine().trim().toUpperCase();
            
            if (!validaCodice(codice)) {
                System.out.println("❌ Formato codice non valido! Usa: PRD-XXXX (dove X sono cifre)");
                continue;
            }
            
            if (esisteCodice(codice)) {
                System.out.println("❌ Codice già esistente! Scegli un codice diverso.");
                continue;
            }
            
            break;
        } while (true);
        
        // 2. Validazione nome prodotto
        String nome;
        do {
            System.out.print("📝 Nome prodotto: ");
            nome = scanner.nextLine().trim();
            
            if (nome.isEmpty()) {
                System.out.println("❌ Il nome non può essere vuoto!");
                continue;
            }
            
            if (nome.length() < 3) {
                System.out.println("❌ Il nome deve essere di almeno 3 caratteri!");
                continue;
            }
            
            break;
        } while (true);
        
        // 3. Scelta categoria
        String categoria = scegliCategoria();
        
        // 4. Validazione prezzo unitario
        double prezzo;
        do {
            prezzo = leggiDouble("💰 Prezzo unitario (€): ");
            
            if (prezzo <= 0) {
                System.out.println("❌ Il prezzo deve essere positivo!");
                continue;
            }
            
            if (prezzo > 100000) {
                System.out.println("❌ Prezzo troppo alto! Massimo €100,000");
                continue;
            }
            
            break;
        } while (true);
        
        // 5. Validazione quantità iniziale
        int qta;
        do {
            qta = leggiIntero("📦 Quantità iniziale: ");
            
            if (qta < 0) {
                System.out.println("❌ La quantità non può essere negativa!");
                continue;
            }
            
            if (qta > 10000) {
                System.out.println("❌ Quantità troppo alta! Massimo 10,000 unità");
                continue;
            }
            
            break;
        } while (true);
        
        // 6. Validazione sconto (opzionale)
        double sconto = 0;
        System.out.print("🏷️ Sconto % (0-100, invio per saltare): ");
        String scontoStr = scanner.nextLine().trim();
        if (!scontoStr.isEmpty()) {
            try {
                sconto = Double.parseDouble(scontoStr);
                if (sconto < 0 || sconto > 100) {
                    System.out.println("⚠️ Sconto non valido (range 0-100%), impostato a 0%");
                    sconto = 0;
                }
            } catch (NumberFormatException e) {
                System.out.println("⚠️ Sconto non valido, impostato a 0%");
                sconto = 0;
            }
        }
        
        // Salvataggio del prodotto negli array
        codici[numProdotti] = codice;
        nomi[numProdotti] = nome;
        categorie[numProdotti] = categoria;
        prezziUnitari[numProdotti] = prezzo;
        quantita[numProdotti] = qta;
        sconti[numProdotti] = sconto;
        attivi[numProdotti] = true;
        
        numProdotti++;
        
        System.out.println("\n✅ Prodotto inserito con successo!");
        System.out.println("📦 DETTAGLI PRODOTTO INSERITO:");
        stampaProdotto(numProdotti - 1);
        
        // Alert se quantità bassa
        if (qta <= SOGLIA_SCORTE_BASSE) {
            System.out.println("⚠️ ATTENZIONE: Scorte basse per questo prodotto!");
        }
    }
    
    /**
     * SOLUZIONE 2: Visualizzazione prodotti in formato tabellare professionale
     */
    private static void visualizzaProdotti() {
        System.out.println("\n=== 📋 LISTA PRODOTTI ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto presente nel magazzino.");
            System.out.println("💡 Usa l'opzione 1 per inserire il primo prodotto.");
            return;
        }
        
        int prodottiAttivi = contaProdottiAttivi();
        if (prodottiAttivi == 0) {
            System.out.println("📭 Tutti i prodotti sono stati disattivati.");
            return;
        }
        
        // Intestazione tabella con formattazione professionale
        System.out.println("\n┌──────────┬────────────────────┬─────────────┬───────────┬─────────┬─────────┬─────────────┐");
        System.out.println("│  CODICE  │        NOME        │  CATEGORIA  │   PREZZO  │   QTÀ   │ SCONTO  │    VALORE   │");
        System.out.println("├──────────┼────────────────────┼─────────────┼───────────┼─────────┼─────────┼─────────────┤");
        
        // Visualizzazione di tutti i prodotti attivi
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                double valoreTotale = calcolaValoreProdotto(i);
                String statusQuantita = quantita[i] <= SOGLIA_SCORTE_BASSE ? "⚠️" : "✅";
                
                System.out.printf("│ %-8s │ %-18s │ %-11s │ %9s │ %4d %s │ %6s  │ %11s │%n",
                    codici[i],
                    limitaStringa(nomi[i], 18),
                    limitaStringa(categorie[i], 11),
                    formattoPrezzo.format(prezziUnitari[i]),
                    quantita[i],
                    statusQuantita,
                    formattoPercentuale.format(sconti[i] / 100),
                    formattoPrezzo.format(valoreTotale)
                );
            }
        }
        
        System.out.println("└──────────┴────────────────────┴─────────────┴───────────┴─────────┴─────────┴─────────────┘");
        
        // Statistiche riassuntive
        double valoreTotale = calcolaValoreTotale();
        int prodottiBasse = contaScorteBasse();
        
        System.out.println("\n📊 STATISTICHE MAGAZZINO:");
        System.out.printf("📦 Prodotti attivi: %d su %d totali%n", prodottiAttivi, numProdotti);
        System.out.printf("💰 Valore totale magazzino: %s%n", formattoPrezzo.format(valoreTotale));
        System.out.printf("⚠️ Prodotti con scorte basse: %d%n", prodottiBasse);
        
        if (prodottiBasse > 0) {
            System.out.println("🔔 SUGGERIMENTO: Controlla l'inventario (opzione 5) per rifornire i prodotti.");
        }
    }
    
    /**
     * SOLUZIONE 3: Modifica prodotto esistente con menu completo
     */
    private static void modificaProdotto() {
        System.out.println("\n=== ✏️ MODIFICA PRODOTTO ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto da modificare.");
            return;
        }
        
        // Ricerca prodotto per codice
        System.out.print("🔍 Inserisci codice prodotto da modificare: ");
        String codice = scanner.nextLine().trim().toUpperCase();
        
        int indice = trovaProdotto(codice);
        if (indice == -1) {
            System.out.println("❌ Prodotto non trovato!");
            System.out.println("💡 Suggerimento: Usa l'opzione 2 per vedere tutti i codici disponibili.");
            return;
        }
        
        // Mostra prodotto corrente
        System.out.println("\n📦 PRODOTTO CORRENTE:");
        stampaProdotto(indice);
        
        // Menu per scegliere cosa modificare
        System.out.println("\n🛠️ COSA VUOI MODIFICARE?");
        System.out.println("1. 📝 Nome prodotto");
        System.out.println("2. 📂 Categoria");
        System.out.println("3. 💰 Prezzo unitario");
        System.out.println("4. 📦 Quantità");
        System.out.println("5. 🏷️ Sconto");
        System.out.println("6. ❌ Disattiva prodotto");
        System.out.println("7. ✅ Riattiva prodotto");
        System.out.println("0. 🚫 Annulla modifica");
        
        int scelta = leggiIntero("👉 Scelta: ");
        
        switch (scelta) {
            case 1: // Modifica nome
                System.out.printf("📝 Nome attuale: %s%n", nomi[indice]);
                String nuovoNome;
                do {
                    System.out.print("📝 Nuovo nome: ");
                    nuovoNome = scanner.nextLine().trim();
                    if (nuovoNome.isEmpty() || nuovoNome.length() < 3) {
                        System.out.println("❌ Nome non valido! Minimo 3 caratteri.");
                        continue;
                    }
                    break;
                } while (true);
                nomi[indice] = nuovoNome;
                break;
                
            case 2: // Modifica categoria
                System.out.printf("📂 Categoria attuale: %s%n", categorie[indice]);
                categorie[indice] = scegliCategoria();
                break;
                
            case 3: // Modifica prezzo
                System.out.printf("💰 Prezzo attuale: %s%n", formattoPrezzo.format(prezziUnitari[indice]));
                double nuovoPrezzo;
                do {
                    nuovoPrezzo = leggiDouble("💰 Nuovo prezzo (€): ");
                    if (nuovoPrezzo <= 0) {
                        System.out.println("❌ Il prezzo deve essere positivo!");
                        continue;
                    }
                    break;
                } while (true);
                prezziUnitari[indice] = nuovoPrezzo;
                break;
                
            case 4: // Modifica quantità
                System.out.printf("📦 Quantità attuale: %d%n", quantita[indice]);
                int nuovaQuantita;
                do {
                    nuovaQuantita = leggiIntero("📦 Nuova quantità: ");
                    if (nuovaQuantita < 0) {
                        System.out.println("❌ La quantità non può essere negativa!");
                        continue;
                    }
                    break;
                } while (true);
                quantita[indice] = nuovaQuantita;
                if (nuovaQuantita <= SOGLIA_SCORTE_BASSE) {
                    System.out.println("⚠️ ATTENZIONE: Scorte basse!");
                }
                break;
                
            case 5: // Modifica sconto
                System.out.printf("🏷️ Sconto attuale: %s%n", formattoPercentuale.format(sconti[indice] / 100));
                double nuovoSconto = leggiDouble("🏷️ Nuovo sconto % (0-100): ");
                if (nuovoSconto < 0 || nuovoSconto > 100) {
                    System.out.println("⚠️ Sconto non valido, mantenuto valore precedente.");
                } else {
                    sconti[indice] = nuovoSconto;
                }
                break;
                
            case 6: // Disattiva prodotto
                if (!attivi[indice]) {
                    System.out.println("⚠️ Il prodotto è già disattivato.");
                } else {
                    System.out.print("⚠️ Confermi la disattivazione? (s/N): ");
                    String conferma = scanner.nextLine().trim().toLowerCase();
                    if (conferma.equals("s") || conferma.equals("si")) {
                        attivi[indice] = false;
                        System.out.println("✅ Prodotto disattivato.");
                    } else {
                        System.out.println("❌ Disattivazione annullata.");
                        return;
                    }
                }
                break;
                
            case 7: // Riattiva prodotto
                if (attivi[indice]) {
                    System.out.println("⚠️ Il prodotto è già attivo.");
                } else {
                    attivi[indice] = true;
                    System.out.println("✅ Prodotto riattivato.");
                }
                break;
                
            case 0: // Annulla
                System.out.println("❌ Modifica annullata.");
                return;
                
            default:
                System.out.println("❌ Scelta non valida!");
                return;
        }
        
        System.out.println("\n✅ Prodotto modificato con successo!");
        System.out.println("📦 PRODOTTO AGGIORNATO:");
        stampaProdotto(indice);
    }
    
    /**
     * SOLUZIONE 4: Calcolo valore magazzino con dettagli finanziari completi
     */
    private static void calcolaValore() {
        System.out.println("\n=== 💰 CALCOLO VALORE MAGAZZINO ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto nel magazzino.");
            return;
        }
        
        int prodottiAttivi = contaProdottiAttivi();
        if (prodottiAttivi == 0) {
            System.out.println("📭 Tutti i prodotti sono disattivati.");
            return;
        }
        
        // Variabili per calcoli finanziari
        BigDecimal valoreLordo = BigDecimal.ZERO;
        BigDecimal valoreConSconti = BigDecimal.ZERO;
        BigDecimal totaleSconti = BigDecimal.ZERO;
        
        System.out.println("\n📊 DETTAGLIO CALCOLI PER PRODOTTO:");
        System.out.println("┌──────────┬─────────────┬─────────────┬─────────────┬─────────────┐");
        System.out.println("│  CODICE  │ VAL. LORDO  │   SCONTO    │ VAL. SCONTO │ VAL. FINALE │");
        System.out.println("├──────────┼─────────────┼─────────────┼─────────────┼─────────────┤");
        
        // Calcolo per ogni prodotto attivo
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                // Uso BigDecimal per precisione nei calcoli monetari
                BigDecimal prezzo = BigDecimal.valueOf(prezziUnitari[i]);
                BigDecimal qta = BigDecimal.valueOf(quantita[i]);
                BigDecimal percentualeSconto = BigDecimal.valueOf(sconti[i] / 100);
                
                BigDecimal valLordo = prezzo.multiply(qta);
                BigDecimal valSconto = valLordo.multiply(percentualeSconto);
                BigDecimal valFinale = valLordo.subtract(valSconto);
                
                // Accumula totali
                valoreLordo = valoreLordo.add(valLordo);
                totaleSconti = totaleSconti.add(valSconto);
                valoreConSconti = valoreConSconti.add(valFinale);
                
                // Stampa riga
                System.out.printf("│ %-8s │ %11s │ %11s │ %11s │ %11s │%n",
                    codici[i],
                    formattoPrezzo.format(valLordo.doubleValue()),
                    formattoPrezzo.format(valSconto.doubleValue()),
                    formattoPrezzo.format(valFinale.doubleValue()),
                    formattoPrezzo.format(valFinale.doubleValue())
                );
            }
        }
        
        System.out.println("└──────────┴─────────────┴─────────────┴─────────────┴─────────────┘");
        
        // Calcoli finali con IVA
        BigDecimal ivaPercentuale = BigDecimal.valueOf(IVA_STANDARD);
        BigDecimal iva = valoreConSconti.multiply(ivaPercentuale);
        BigDecimal valoreTotaleConIVA = valoreConSconti.add(iva);
        
        // Report finanziario dettagliato
        System.out.println("\n💰 RIEPILOGO FINANZIARIO DETTAGLIATO:");
        System.out.println("┌─────────────────────────────────┬─────────────────┐");
        System.out.println("│ DESCRIZIONE                     │      IMPORTO    │");
        System.out.println("├─────────────────────────────────┼─────────────────┤");
        System.out.printf("│ 💸 Valore lordo magazzino       │ %15s │%n", 
                         formattoPrezzo.format(valoreLordo.doubleValue()));
        System.out.printf("│ 🏷️ Totale sconti applicati      │ %15s │%n", 
                         formattoPrezzo.format(totaleSconti.doubleValue()));
        System.out.printf("│ 💵 Valore netto (con sconti)    │ %15s │%n", 
                         formattoPrezzo.format(valoreConSconti.doubleValue()));
        System.out.printf("│ 🏛️ IVA (%s)                    │ %15s │%n", 
                         formattoPercentuale.format(IVA_STANDARD),
                         formattoPrezzo.format(iva.doubleValue()));
        System.out.println("├─────────────────────────────────┼─────────────────┤");
        System.out.printf("│ 💎 VALORE TOTALE CON IVA        │ %15s │%n", 
                         formattoPrezzo.format(valoreTotaleConIVA.doubleValue()));
        System.out.println("└─────────────────────────────────┴─────────────────┘");
        
        // Analisi percentuali
        if (valoreLordo.compareTo(BigDecimal.ZERO) > 0) {
            double percentualeSconti = totaleSconti.divide(valoreLordo, 4, RoundingMode.HALF_UP).doubleValue();
            System.out.printf("\n📈 ANALISI PERCENTUALI:%n");
            System.out.printf("🏷️ Incidenza sconti sul totale: %s%n", 
                             formattoPercentuale.format(percentualeSconti));
            System.out.printf("🏛️ Incidenza IVA sul netto: %s%n", 
                             formattoPercentuale.format(IVA_STANDARD));
        }
        
        // Statistiche aggiuntive
        System.out.printf("\n📊 STATISTICHE AGGIUNTIVE:%n");
        System.out.printf("📦 Prodotti inclusi nel calcolo: %d%n", prodottiAttivi);
        System.out.printf("💰 Valore medio per prodotto: %s%n", 
                         formattoPrezzo.format(valoreConSconti.divide(BigDecimal.valueOf(prodottiAttivi), 2, RoundingMode.HALF_UP).doubleValue()));
    }
    
    /**
     * SOLUZIONE 5: Gestione inventario completa
     */
    private static void gestioneInventario() {
        System.out.println("\n=== 📊 GESTIONE INVENTARIO ===");
        
        System.out.println("1. 🔍 Visualizza scorte basse");
        System.out.println("2. 📦 Carico merce");
        System.out.println("3. 📤 Scarico merce");
        System.out.println("4. 📋 Report inventario completo");
        System.out.println("0. 🔙 Torna al menu principale");
        
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
            case 0:
                return;
            default:
                System.out.println("❌ Scelta non valida!");
        }
    }
    
    /**
     * SOLUZIONE 6: Generazione report completo professionale
     */
    private static void generaReport() {
        System.out.println("\n=== 📄 GENERAZIONE REPORT COMPLETO ===");
        
        LocalDateTime ora = LocalDateTime.now();
        
        System.out.println("╔════════════════════════════════════════════════════════════════════════╗");
        System.out.println("║                           REPORT MAGAZZINO                            ║");
        System.out.println("║                         SISTEMA GESTIONALE                            ║");
        System.out.println("╠════════════════════════════════════════════════════════════════════════╣");
        System.out.printf("║ 📅 Data generazione: %-47s ║%n", ora.format(formattoData));
        System.out.printf("║ 🏢 Sistema: Gestione Magazzino v1.0 %-33s ║%n", "");
        System.out.println("╚════════════════════════════════════════════════════════════════════════╝");
        
        // Sezione 1: Riepilogo generale
        System.out.println("\n📊 1. RIEPILOGO GENERALE");
        System.out.println("─".repeat(50));
        System.out.printf("📦 Prodotti totali inseriti: %d%n", numProdotti);
        System.out.printf("✅ Prodotti attivi: %d%n", contaProdottiAttivi());
        System.out.printf("❌ Prodotti disattivati: %d%n", numProdotti - contaProdottiAttivi());
        System.out.printf("⚠️ Prodotti con scorte basse: %d%n", contaScorteBasse());
        System.out.printf("💰 Valore totale magazzino: %s%n", formattoPrezzo.format(calcolaValoreTotale()));
        
        // Sezione 2: Analisi per categoria
        System.out.println("\n📂 2. ANALISI PER CATEGORIA");
        System.out.println("─".repeat(50));
        analisiPerCategoria();
        
        // Sezione 3: Prodotti con scorte critiche
        System.out.println("\n⚠️ 3. SCORTE CRITICHE");
        System.out.println("─".repeat(50));
        reportScorteCritiche();
        
        // Sezione 4: Top prodotti per valore
        System.out.println("\n🏆 4. TOP PRODOTTI PER VALORE");
        System.out.println("─".repeat(50));
        topProdottiPerValore();
        
        // Sezione 5: Calcoli finanziari dettagliati
        System.out.println("\n💰 5. ANALISI FINANZIARIA");
        System.out.println("─".repeat(50));
        analisiFinanziaria();
        
        System.out.println("\n" + "═".repeat(70));
        System.out.println("📄 FINE REPORT - Generato automaticamente dal sistema");
        System.out.println("═".repeat(70));
    }
    
    /**
     * SOLUZIONE 7: Ricerca prodotti con criteri multipli
     */
    private static void ricercaProdotti() {
        System.out.println("\n=== 🔍 RICERCA PRODOTTI ===");
        
        if (numProdotti == 0) {
            System.out.println("📭 Nessun prodotto da cercare.");
            return;
        }
        
        System.out.println("🔎 CRITERI DI RICERCA DISPONIBILI:");
        System.out.println("1. 🔤 Ricerca per codice esatto");
        System.out.println("2. 📝 Ricerca per nome (parziale)");
        System.out.println("3. 📂 Ricerca per categoria");
        System.out.println("4. 💰 Ricerca per range di prezzo");
        System.out.println("5. 📦 Ricerca per quantità");
        System.out.println("0. 🔙 Torna al menu principale");
        
        int criterio = leggiIntero("👉 Criterio di ricerca: ");
        
        switch (criterio) {
            case 1: // Ricerca per codice
                ricercaPerCodice();
                break;
            case 2: // Ricerca per nome
                ricercaPerNome();
                break;
            case 3: // Ricerca per categoria
                ricercaPerCategoria();
                break;
            case 4: // Ricerca per range prezzo
                ricercaPerRangePrezzo();
                break;
            case 5: // Ricerca per quantità
                ricercaPerQuantita();
                break;
            case 0:
                return;
            default:
                System.out.println("❌ Criterio non valido!");
        }
    }
    
    // ==================== METODI DI UTILITÀ E SUPPORTO ====================
    
    /**
     * Valida il formato del codice prodotto (PRD-XXXX)
     */
    private static boolean validaCodice(String codice) {
        if (codice == null || codice.length() != 8) {
            return false;
        }
        
        if (!codice.startsWith("PRD-")) {
            return false;
        }
        
        String numero = codice.substring(4);
        try {
            Integer.parseInt(numero);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
    
    /**
     * Verifica se un codice esiste già
     */
    private static boolean esisteCodice(String codice) {
        for (int i = 0; i < numProdotti; i++) {
            if (codici[i].equals(codice)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Metodo per scegliere una categoria da una lista predefinita
     */
    private static String scegliCategoria() {
        String[] categorie = {"ELETTRONICA", "ABBIGLIAMENTO", "CASA", "SPORT", "LIBRI", "ALIMENTARI", "ALTRO"};
        
        System.out.println("📂 CATEGORIE DISPONIBILI:");
        for (int i = 0; i < categorie.length; i++) {
            System.out.printf("%d. %s%n", i + 1, categorie[i]);
        }
        
        int scelta;
        do {
            scelta = leggiIntero("👉 Categoria (1-" + categorie.length + "): ");
            if (scelta < 1 || scelta > categorie.length) {
                System.out.println("❌ Scelta non valida!");
            }
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
     * Conta prodotti con scorte basse
     */
    private static int contaScorteBasse() {
        int count = 0;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && quantita[i] <= SOGLIA_SCORTE_BASSE) {
                count++;
            }
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
        String status = attivi[indice] ? "✅ ATTIVO" : "❌ DISATTIVATO";
        String alertScorte = quantita[indice] <= SOGLIA_SCORTE_BASSE ? " ⚠️ SCORTE BASSE" : "";
        
        System.out.printf("🏷️ %s - %s (%s) %s%s%n", 
                         codici[indice], nomi[indice], categorie[indice], status, alertScorte);
        System.out.printf("   💰 Prezzo: %s | 📦 Quantità: %d | 🏷️ Sconto: %s%n",
                         formattoPrezzo.format(prezziUnitari[indice]),
                         quantita[indice],
                         formattoPercentuale.format(sconti[indice] / 100));
        System.out.printf("   💎 Valore totale: %s%n", formattoPrezzo.format(calcolaValoreProdotto(indice)));
    }
    
    /**
     * Implementazione metodi per gestione inventario
     */
    private static void visualizzaScorteBasse() {
        System.out.println("\n⚠️ PRODOTTI CON SCORTE BASSE");
        System.out.printf("(Soglia critica: %.0f unità)%n%n", SOGLIA_SCORTE_BASSE);
        
        boolean trovati = false;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && quantita[i] <= SOGLIA_SCORTE_BASSE) {
                if (!trovati) {
                    System.out.println("┌──────────┬────────────────────┬─────────────┬─────────┐");
                    System.out.println("│  CODICE  │        NOME        │  CATEGORIA  │   QTÀ   │");
                    System.out.println("├──────────┼────────────────────┼─────────────┼─────────┤");
                    trovati = true;
                }
                
                System.out.printf("│ %-8s │ %-18s │ %-11s │ %7d │%n",
                    codici[i],
                    limitaStringa(nomi[i], 18),
                    limitaStringa(categorie[i], 11),
                    quantita[i]
                );
            }
        }
        
        if (trovati) {
            System.out.println("└──────────┴────────────────────┴─────────────┴─────────┘");
            System.out.println("💡 Suggerimento: Usa 'Carico merce' per rifornire questi prodotti.");
        } else {
            System.out.println("✅ Tutti i prodotti hanno scorte sufficienti!");
        }
    }
    
    private static void caricoMerce() {
        System.out.println("\n📦 CARICO MERCE");
        
        System.out.print("🔍 Codice prodotto da rifornire: ");
        String codice = scanner.nextLine().trim().toUpperCase();
        
        int indice = trovaProdotto(codice);
        if (indice == -1) {
            System.out.println("❌ Prodotto non trovato!");
            return;
        }
        
        System.out.printf("📦 Quantità attuale: %d%n", quantita[indice]);
        int qtaCarico = leggiIntero("📦 Quantità da caricare: ");
        
        if (qtaCarico <= 0) {
            System.out.println("❌ La quantità deve essere positiva!");
            return;
        }
        
        int vecchiaQta = quantita[indice];
        quantita[indice] += qtaCarico;
        
        System.out.println("✅ Carico completato!");
        System.out.printf("📊 %s: %d → %d (+%d)%n", nomi[indice], vecchiaQta, quantita[indice], qtaCarico);
        
        if (vecchiaQta <= SOGLIA_SCORTE_BASSE && quantita[indice] > SOGLIA_SCORTE_BASSE) {
            System.out.println("🎉 Prodotto non è più in scorte basse!");
        }
    }
    
    private static void scaricoMerce() {
        System.out.println("\n📤 SCARICO MERCE");
        
        System.out.print("🔍 Codice prodotto da scaricare: ");
        String codice = scanner.nextLine().trim().toUpperCase();
        
        int indice = trovaProdotto(codice);
        if (indice == -1) {
            System.out.println("❌ Prodotto non trovato!");
            return;
        }
        
        System.out.printf("📦 Quantità disponibile: %d%n", quantita[indice]);
        int qtaScarico = leggiIntero("📤 Quantità da scaricare: ");
        
        if (qtaScarico <= 0) {
            System.out.println("❌ La quantità deve essere positiva!");
            return;
        }
        
        if (qtaScarico > quantita[indice]) {
            System.out.printf("❌ Quantità insufficiente! Disponibili: %d%n", quantita[indice]);
            return;
        }
        
        int vecchiaQta = quantita[indice];
        quantita[indice] -= qtaScarico;
        
        System.out.println("✅ Scarico completato!");
        System.out.printf("📊 %s: %d → %d (-%d)%n", nomi[indice], vecchiaQta, quantita[indice], qtaScarico);
        
        if (quantita[indice] <= SOGLIA_SCORTE_BASSE) {
            System.out.println("⚠️ ATTENZIONE: Il prodotto è ora in scorte basse!");
        }
    }
    
    private static void reportInventario() {
        System.out.println("\n📋 REPORT INVENTARIO COMPLETO");
        System.out.println("═".repeat(60));
        
        // Statistiche generali
        int totaleUnita = 0;
        double valoreTotale = 0;
        
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                totaleUnita += quantita[i];
                valoreTotale += calcolaValoreProdotto(i);
            }
        }
        
        System.out.printf("📊 Unità totali in magazzino: %d%n", totaleUnita);
        System.out.printf("💰 Valore totale inventario: %s%n", formattoPrezzo.format(valoreTotale));
        System.out.printf("📦 Prodotti diversi: %d%n", contaProdottiAttivi());
        System.out.printf("⚠️ Prodotti sotto soglia: %d%n", contaScorteBasse());
        
        System.out.println("\n📈 DISTRIBUZIONE SCORTE:");
        System.out.println("┌─────────────────┬────────────────┐");
        System.out.println("│   CATEGORIA     │   UNITÀ TOTALI │");
        System.out.println("├─────────────────┼────────────────┤");
        
        // Analisi per categoria
        String[] categorieLista = {"ELETTRONICA", "ABBIGLIAMENTO", "CASA", "SPORT", "LIBRI", "ALIMENTARI", "ALTRO"};
        for (String cat : categorieLista) {
            int unitaCategoria = 0;
            for (int i = 0; i < numProdotti; i++) {
                if (attivi[i] && categorie[i].equals(cat)) {
                    unitaCategoria += quantita[i];
                }
            }
            if (unitaCategoria > 0) {
                System.out.printf("│ %-15s │ %14d │%n", cat, unitaCategoria);
            }
        }
        System.out.println("└─────────────────┴────────────────┘");
    }
    
    /**
     * Implementazione metodi per ricerca
     */
    private static void ricercaPerCodice() {
        System.out.print("🔤 Inserisci codice da cercare: ");
        String codice = scanner.nextLine().trim().toUpperCase();
        
        int indice = trovaProdotto(codice);
        if (indice == -1) {
            System.out.println("❌ Nessun prodotto trovato con questo codice.");
        } else {
            System.out.println("\n✅ PRODOTTO TROVATO:");
            stampaProdotto(indice);
        }
    }
    
    private static void ricercaPerNome() {
        System.out.print("📝 Inserisci parte del nome: ");
        String ricerca = scanner.nextLine().trim().toLowerCase();
        
        if (ricerca.isEmpty()) {
            System.out.println("❌ Testo di ricerca vuoto!");
            return;
        }
        
        System.out.println("\n🔍 RISULTATI RICERCA:");
        boolean trovato = false;
        
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && nomi[i].toLowerCase().contains(ricerca)) {
                if (!trovato) {
                    System.out.println("─".repeat(40));
                    trovato = true;
                }
                stampaProdotto(i);
                System.out.println();
            }
        }
        
        if (!trovato) {
            System.out.println("❌ Nessun prodotto trovato con questo nome.");
        }
    }
    
    private static void ricercaPerCategoria() {
        String categoria = scegliCategoria();
        
        System.out.printf("\n🔍 PRODOTTI CATEGORIA: %s%n", categoria);
        System.out.println("─".repeat(40));
        
        boolean trovato = false;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && categorie[i].equals(categoria)) {
                stampaProdotto(i);
                System.out.println();
                trovato = true;
            }
        }
        
        if (!trovato) {
            System.out.printf("❌ Nessun prodotto trovato nella categoria %s.%n", categoria);
        }
    }
    
    private static void ricercaPerRangePrezzo() {
        double prezzoMin = leggiDouble("💰 Prezzo minimo (€): ");
        double prezzoMax = leggiDouble("💰 Prezzo massimo (€): ");
        
        if (prezzoMin > prezzoMax) {
            System.out.println("❌ Il prezzo minimo non può essere maggiore del massimo!");
            return;
        }
        
        System.out.printf("\n🔍 PRODOTTI NEL RANGE €%.2f - €%.2f:%n", prezzoMin, prezzoMax);
        System.out.println("─".repeat(40));
        
        boolean trovato = false;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && prezziUnitari[i] >= prezzoMin && prezziUnitari[i] <= prezzoMax) {
                stampaProdotto(i);
                System.out.println();
                trovato = true;
            }
        }
        
        if (!trovato) {
            System.out.println("❌ Nessun prodotto trovato in questo range di prezzo.");
        }
    }
    
    private static void ricercaPerQuantita() {
        int qtaMin = leggiIntero("📦 Quantità minima: ");
        int qtaMax = leggiIntero("📦 Quantità massima: ");
        
        if (qtaMin > qtaMax) {
            System.out.println("❌ La quantità minima non può essere maggiore della massima!");
            return;
        }
        
        System.out.printf("\n🔍 PRODOTTI CON QUANTITÀ %d - %d:%n", qtaMin, qtaMax);
        System.out.println("─".repeat(40));
        
        boolean trovato = false;
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && quantita[i] >= qtaMin && quantita[i] <= qtaMax) {
                stampaProdotto(i);
                System.out.println();
                trovato = true;
            }
        }
        
        if (!trovato) {
            System.out.println("❌ Nessun prodotto trovato in questo range di quantità.");
        }
    }
    
    /**
     * Metodi per analisi avanzate nel report
     */
    private static void analisiPerCategoria() {
        String[] categorieLista = {"ELETTRONICA", "ABBIGLIAMENTO", "CASA", "SPORT", "LIBRI", "ALIMENTARI", "ALTRO"};
        
        System.out.println("┌─────────────────┬──────────┬─────────────────┐");
        System.out.println("│   CATEGORIA     │ PRODOTTI │ VALORE TOTALE   │");
        System.out.println("├─────────────────┼──────────┼─────────────────┤");
        
        for (String cat : categorieLista) {
            int conteggio = 0;
            double valore = 0;
            
            for (int i = 0; i < numProdotti; i++) {
                if (attivi[i] && categorie[i].equals(cat)) {
                    conteggio++;
                    valore += calcolaValoreProdotto(i);
                }
            }
            
            if (conteggio > 0) {
                System.out.printf("│ %-15s │ %8d │ %15s │%n", 
                                cat, conteggio, formattoPrezzo.format(valore));
            }
        }
        System.out.println("└─────────────────┴──────────┴─────────────────┘");
    }
    
    private static void reportScorteCritiche() {
        boolean haScorteCritiche = false;
        
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i] && quantita[i] <= SOGLIA_SCORTE_BASSE) {
                if (!haScorteCritiche) {
                    System.out.printf("⚠️ Soglia critica: %.0f unità%n%n", SOGLIA_SCORTE_BASSE);
                    haScorteCritiche = true;
                }
                System.out.printf("🔴 %s (%s) - Quantità: %d%n", 
                                nomi[i], codici[i], quantita[i]);
            }
        }
        
        if (!haScorteCritiche) {
            System.out.println("✅ Nessun prodotto in scorte critiche.");
        }
    }
    
    private static void topProdottiPerValore() {
        if (numProdotti == 0) return;
        
        // Creiamo array di indici ordinati per valore
        int[] indiciOrdinati = new int[numProdotti];
        int count = 0;
        
        for (int i = 0; i < numProdotti; i++) {
            if (attivi[i]) {
                indiciOrdinati[count++] = i;
            }
        }
        
        // Ordinamento bubble sort per valore decrescente
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (calcolaValoreProdotto(indiciOrdinati[j]) < calcolaValoreProdotto(indiciOrdinati[j + 1])) {
                    int temp = indiciOrdinati[j];
                    indiciOrdinati[j] = indiciOrdinati[j + 1];
                    indiciOrdinati[j + 1] = temp;
                }
            }
        }
        
        // Mostra top 5
        int limite = Math.min(5, count);
        for (int i = 0; i < limite; i++) {
            int idx = indiciOrdinati[i];
            System.out.printf("🏆 #%d: %s - %s%n", 
                            i + 1, nomi[idx], formattoPrezzo.format(calcolaValoreProdotto(idx)));
        }
    }
    
    private static void analisiFinanziaria() {
        double valoreTotale = calcolaValoreTotale();
        double iva = valoreTotale * IVA_STANDARD;
        
        System.out.printf("💵 Valore netto magazzino: %s%n", formattoPrezzo.format(valoreTotale));
        System.out.printf("🏛️ IVA da versare: %s%n", formattoPrezzo.format(iva));
        System.out.printf("💎 Valore lordo con IVA: %s%n", formattoPrezzo.format(valoreTotale + iva));
        
        if (contaProdottiAttivi() > 0) {
            double valoremedio = valoreTotale / contaProdottiAttivi();
            System.out.printf("📊 Valore medio per prodotto: %s%n", formattoPrezzo.format(valoremedio));
        }
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
        scanner.nextLine(); // Consuma il newline
        return numero;
    }
    
    private static double leggiDouble(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextDouble()) {
            System.out.print("❌ Inserisci un numero valido: ");
            scanner.next();
        }
        double numero = scanner.nextDouble();
        scanner.nextLine(); // Consuma il newline
        return numero;
    }
    
    /**
     * Carica dati di esempio per il testing e dimostrazione
     */
    private static void caricaDatiEsempio() {
        // Prodotto 1 - Elettronica
        codici[0] = "PRD-0001";
        nomi[0] = "Smartphone XYZ Pro";
        categorie[0] = "ELETTRONICA";
        prezziUnitari[0] = 299.99;
        quantita[0] = 15;
        sconti[0] = 10.0;
        attivi[0] = true;
        
        // Prodotto 2 - Abbigliamento (scorte basse)
        codici[1] = "PRD-0002";
        nomi[1] = "T-Shirt Cotone Bio";
        categorie[1] = "ABBIGLIAMENTO";
        prezziUnitari[1] = 19.90;
        quantita[1] = 5; // Scorte basse
        sconti[1] = 0.0;
        attivi[1] = true;
        
        // Prodotto 3 - Casa
        codici[2] = "PRD-0003";
        nomi[2] = "Lampada LED Smart";
        categorie[2] = "CASA";
        prezziUnitari[2] = 45.50;
        quantita[2] = 25;
        sconti[2] = 15.0;
        attivi[2] = true;
        
        // Prodotto 4 - Sport (scorte critiche)
        codici[3] = "PRD-0004";
        nomi[3] = "Scarpe Running Pro";
        categorie[3] = "SPORT";
        prezziUnitari[3] = 89.99;
        quantita[3] = 3; // Scorte critiche
        sconti[3] = 5.0;
        attivi[3] = true;
        
        numProdotti = 4;
        
        System.out.printf("✅ Sistema inizializzato con %d prodotti di esempio%n", numProdotti);
        System.out.printf("💰 Valore iniziale magazzino: %s%n", formattoPrezzo.format(calcolaValoreTotale()));
        System.out.printf("⚠️ Prodotti con scorte basse: %d%n", contaScorteBasse());
        System.out.println("📚 Pronto per l'utilizzo!");
    }
}
