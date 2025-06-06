/**
 * PROGETTO MODULO C - Sistema di Gestione Budget Personale
 * 
 * DESCRIZIONE PROGETTO:
 * Sviluppare un sistema completo per la gestione del budget personale che permetta
 * di tracciare entrate e uscite, calcolare bilanci, generare report e fornire
 * consigli di risparmio. Il sistema deve dimostrare padronanza completa di:
 * - Tutti i tipi di dati primitivi e loro uso appropriato
 * - Operatori aritmetici, logici e di confronto
 * - Conversioni di tipo e gestione precision
 * - Input/Output formattato professionale
 * - Validazione robusta dell'input utente
 * - Calcoli finanziari accurati
 * 
 * SPECIFICHE TECNICHE:
 * - Menu interattivo multilivello
 * - Gestione di multiple categorie di spesa
 * - Calcoli con precision decimal per evitare errori floating-point
 * - Report formattati con tabelle ASCII
 * - Sistema di allerte e consigli automatici
 * - Persistenza dati in memoria durante l'esecuzione
 * - Interfaccia utente intuitiva con emoji e formattazione
 * 
 * VALUTAZIONE:
 * Il progetto vale 40 punti totali e viene valutato su:
 * - Correttezza implementazione (15 punti)
 * - Qualità del codice e commenti (10 punti)
 * - Gestione errori e validazione (10 punti)
 * - Interfaccia utente e usabilità (5 punti)
 * 
 * TEMPO STIMATO: 4-6 ore
 * 
 * @author [Nome Studente]
 * @version 1.0
 * @date [Data consegna]
 */

import java.util.Scanner;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Locale;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class ProgettoGestioneBudget {
    
    // ==================== COSTANTI DI CONFIGURAZIONE ====================
    
    /** Numero massimo di transazioni memorizzabili */
    private static final int MAX_TRANSAZIONI = 200;
    
    /** Numero massimo di categorie personalizzate */
    private static final int MAX_CATEGORIE = 20;
    
    /** Soglia percentuale per allerta spesa elevata */
    private static final double SOGLIA_ALLERTA_SPESA = 0.80; // 80% del budget
    
    /** Obiettivo di risparmio raccomandato (% del reddito) */
    private static final double OBIETTIVO_RISPARMIO = 0.20; // 20%
    
    // ==================== STRUTTURE DATI PRINCIPALI ====================
    
    // Array paralleli per memorizzare le transazioni
    private static double[] importi = new double[MAX_TRANSAZIONI];
    private static String[] descrizioni = new String[MAX_TRANSAZIONI];
    private static String[] categorie = new String[MAX_TRANSAZIONI];
    private static String[] tipi = new String[MAX_TRANSAZIONI]; // "ENTRATA" o "USCITA"
    private static LocalDate[] date = new LocalDate[MAX_TRANSAZIONI];
    private static boolean[] attive = new boolean[MAX_TRANSAZIONI];
    
    // Array per gestire budget per categoria
    private static String[] categoriePersonalizzate = new String[MAX_CATEGORIE];
    private static double[] budgetCategorie = new double[MAX_CATEGORIE];
    private static int numCategorie = 0;
    
    // Contatori e variabili di stato
    private static int numTransazioni = 0;
    private static double budgetMensile = 0.0;
    private static double obiettivoRisparmio = 0.0;
    
    // ==================== FORMATTATORI E UTILITY ====================
    
    private static final DecimalFormat formattoEuro = new DecimalFormat("#,##0.00 €");
    private static final DecimalFormat formattoPercentuale = new DecimalFormat("#0.0%");
    private static final NumberFormat formattoValuta = NumberFormat.getCurrencyInstance(Locale.ITALY);
    private static final DateTimeFormatter formattoData = DateTimeFormatter.ofPattern("dd/MM/yyyy");
    
    private static Scanner scanner = new Scanner(System.in);
    
    // ==================== MENU PRINCIPALE ====================
    
    /**
     * TODO 1: Implementare il menu principale del sistema
     * REQUISITI:
     * - Mostrare stato attuale del budget (entrate, uscite, saldo)
     * - Menu con tutte le opzioni principali
     * - Gestione input utente con validazione
     * - Loop principale fino all'uscita
     * - Gestione errori per input non validi
     */
    public static void main(String[] args) {
        System.out.println("╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║               SISTEMA GESTIONE BUDGET PERSONALE              ║");
        System.out.println("║                    Progetto Modulo C                        ║");
        System.out.println("║              Dati, Assegnazione e Input/Output              ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");
        System.out.println();
        
        // TODO: Inizializzare il sistema con dati di esempio (opzionale)
        inizializzaSistema();
        
        boolean continua = true;
        while (continua) {
            // TODO: Mostrare stato attuale
            mostraStatoAttuale();
            
            // TODO: Mostrare menu principale
            mostraMenuPrincipale();
            
            // TODO: Gestire scelta utente
            int scelta = leggiInteroConValidazione("👉 Inserisci la tua scelta: ", 0, 9);
            
            switch (scelta) {
                case 1:
                    // TODO: Implementare inserimento transazione
                    inserisciTransazione();
                    break;
                case 2:
                    // TODO: Implementare visualizzazione transazioni
                    visualizzaTransazioni();
                    break;
                case 3:
                    // TODO: Implementare gestione budget
                    gestioneBudget();
                    break;
                case 4:
                    // TODO: Implementare analisi spese
                    analisiSpese();
                    break;
                case 5:
                    // TODO: Implementare report mensile
                    generaReportMensile();
                    break;
                case 6:
                    // TODO: Implementare consigli risparmio
                    consigliRisparmio();
                    break;
                case 7:
                    // TODO: Implementare gestione categorie
                    gestioneCategorie();
                    break;
                case 8:
                    // TODO: Implementare importazione/esportazione dati
                    gestioneDati();
                    break;
                case 9:
                    // TODO: Implementare impostazioni sistema
                    impostazioniSistema();
                    break;
                case 0:
                    continua = false;
                    chiudiSistema();
                    break;
            }
            
            if (continua) {
                System.out.println("\\n⏸️ Premi INVIO per continuare...");
                scanner.nextLine();
            }
        }
        
        scanner.close();
    }
    
    /**
     * TODO 2: Implementare visualizzazione stato attuale del budget
     * REQUISITI:
     * - Calcolare e mostrare totale entrate del mese corrente
     * - Calcolare e mostrare totale uscite del mese corrente
     * - Calcolare saldo (entrate - uscite)
     * - Mostrare percentuale budget utilizzato
     * - Alert colorati per situazioni critiche
     * - Formattazione professionale con tabelle
     */
    private static void mostraStatoAttuale() {
        System.out.println("\\n💰 STATO ATTUALE BUDGET - " + LocalDate.now().format(formattoData));
        System.out.println("═".repeat(60));
        
        // TODO: Calcolare totali per il mese corrente
        LocalDate oggi = LocalDate.now();
        LocalDate inizioMese = oggi.withDayOfMonth(1);
        LocalDate fineMese = oggi.withDayOfMonth(oggi.lengthOfMonth());
        
        double totaleEntrate = calcolaTotalePerPeriodo("ENTRATA", inizioMese, fineMese);
        double totaleUscite = calcolaTotalePerPeriodo("USCITA", inizioMese, fineMese);
        double saldo = totaleEntrate - totaleUscite;
        
        // TODO: Formattare e mostrare i dati
        System.out.println("┌─────────────────────────────┬─────────────────┐");
        System.out.println("│ CATEGORIA                   │      IMPORTO    │");
        System.out.println("├─────────────────────────────┼─────────────────┤");
        System.out.printf("│ 📈 Entrate del mese         │ %15s │%n", formattoEuro.format(totaleEntrate));
        System.out.printf("│ 📉 Uscite del mese          │ %15s │%n", formattoEuro.format(totaleUscite));
        System.out.println("├─────────────────────────────┼─────────────────┤");
        
        // TODO: Colorare il saldo in base al valore (positivo/negativo)
        String simboloSaldo = saldo >= 0 ? "💚" : "🔴";
        String testoSaldo = saldo >= 0 ? "Saldo positivo" : "Saldo negativo";
        System.out.printf("│ %s %-18s │ %15s │%n", simboloSaldo, testoSaldo, formattoEuro.format(saldo));
        System.out.println("└─────────────────────────────┴─────────────────┘");
        
        // TODO: Mostrare alert se necessario
        if (budgetMensile > 0) {
            double percentualeUtilizzata = totaleUscite / budgetMensile;
            System.out.printf("📊 Budget utilizzato: %s di %s (%s)%n", 
                             formattoEuro.format(totaleUscite),
                             formattoEuro.format(budgetMensile),
                             formattoPercentuale.format(percentualeUtilizzata));
            
            if (percentualeUtilizzata >= SOGLIA_ALLERTA_SPESA) {
                System.out.println("⚠️ ALLERTA: Hai superato l'80% del budget mensile!");
            }
        }
    }
    
    /**
     * TODO 3: Implementare menu principale con interfaccia grafica ASCII
     */
    private static void mostraMenuPrincipale() {
        System.out.println("\\n╔════════════════════════════════════════════════╗");
        System.out.println("║                 MENU PRINCIPALE                ║");
        System.out.println("╠════════════════════════════════════════════════╣");
        System.out.println("║ 1. 💳 Inserisci nuova transazione             ║");
        System.out.println("║ 2. 📋 Visualizza transazioni                  ║");
        System.out.println("║ 3. 🎯 Gestione budget e obiettivi             ║");
        System.out.println("║ 4. 📊 Analisi spese per categoria             ║");
        System.out.println("║ 5. 📄 Genera report mensile                   ║");
        System.out.println("║ 6. 💡 Consigli per il risparmio               ║");
        System.out.println("║ 7. 📂 Gestione categorie                      ║");
        System.out.println("║ 8. 💾 Gestione dati (import/export)           ║");
        System.out.println("║ 9. ⚙️ Impostazioni sistema                     ║");
        System.out.println("║ 0. 🚪 Esci dal programma                       ║");
        System.out.println("╚════════════════════════════════════════════════╝");
    }
    
    /**
     * TODO 4: Implementare inserimento transazione con validazione completa
     * REQUISITI:
     * - Scegliere tipo transazione (ENTRATA/USCITA)
     * - Inserire importo con validazione (positivo, formato corretto)
     * - Inserire descrizione (non vuota, lunghezza ragionevole)
     * - Scegliere categoria da lista predefinita + personalizzate
     * - Inserire data (default oggi, validazione formato)
     * - Confermare prima di salvare
     * - Gestire array pieno
     */
    private static void inserisciTransazione() {
        System.out.println("\\n=== 💳 INSERIMENTO NUOVA TRANSAZIONE ===");
        
        // TODO: Verificare spazio disponibile
        if (numTransazioni >= MAX_TRANSAZIONI) {
            System.out.println("❌ Impossibile inserire nuove transazioni: memoria piena!");
            System.out.printf("📊 Massimo transazioni supportate: %d%n", MAX_TRANSAZIONI);
            return;
        }
        
        // TODO 4.1: Scegliere tipo transazione
        System.out.println("\\n💰 TIPO DI TRANSAZIONE:");
        System.out.println("1. 📈 Entrata (stipendio, bonus, vendita, etc.)");
        System.out.println("2. 📉 Uscita (spesa, acquisto, bolletta, etc.)");
        System.out.println("0. 🔙 Annulla");
        
        int tipoScelta = leggiInteroConValidazione("👉 Scegli tipo: ", 0, 2);
        if (tipoScelta == 0) {
            System.out.println("❌ Inserimento annullato.");
            return;
        }
        
        String tipo = tipoScelta == 1 ? "ENTRATA" : "USCITA";
        String emojiTipo = tipoScelta == 1 ? "📈" : "📉";
        
        // TODO 4.2: Inserire e validare importo
        double importo;
        do {
            System.out.printf("\\n%s Inserisci importo (€): ", emojiTipo);
            try {
                String inputImporto = scanner.nextLine().trim().replace(",", ".");
                importo = Double.parseDouble(inputImporto);
                
                if (importo <= 0) {
                    System.out.println("❌ L'importo deve essere positivo!");
                    continue;
                }
                
                if (importo > 1000000) {
                    System.out.println("❌ Importo troppo elevato! Massimo €1,000,000");
                    continue;
                }
                
                // TODO: Validazione precision decimale (max 2 cifre)
                BigDecimal bd = BigDecimal.valueOf(importo).setScale(2, RoundingMode.HALF_UP);
                importo = bd.doubleValue();
                break;
                
            } catch (NumberFormatException e) {
                System.out.println("❌ Formato non valido! Usa formato: 123.45");
            }
        } while (true);
        
        // TODO 4.3: Inserire descrizione
        String descrizione;
        do {
            System.out.print("\\n📝 Descrizione transazione: ");
            descrizione = scanner.nextLine().trim();
            
            if (descrizione.isEmpty()) {
                System.out.println("❌ La descrizione non può essere vuota!");
                continue;
            }
            
            if (descrizione.length() < 3) {
                System.out.println("❌ Descrizione troppo corta! Minimo 3 caratteri.");
                continue;
            }
            
            if (descrizione.length() > 100) {
                System.out.println("❌ Descrizione troppo lunga! Massimo 100 caratteri.");
                descrizione = descrizione.substring(0, 100);
                System.out.printf("✂️ Descrizione accorciata a: %s%n", descrizione);
            }
            
            break;
        } while (true);
        
        // TODO 4.4: Scegliere categoria
        String categoria = scegliCategoria(tipo);
        
        // TODO 4.5: Inserire data (default oggi)
        LocalDate dataTransazione = inserisciData();
        
        // TODO 4.6: Riepilogo e conferma
        System.out.println("\\n📋 RIEPILOGO TRANSAZIONE:");
        System.out.println("─".repeat(40));
        System.out.printf("Tipo: %s %s%n", emojiTipo, tipo);
        System.out.printf("Importo: %s%n", formattoEuro.format(importo));
        System.out.printf("Descrizione: %s%n", descrizione);
        System.out.printf("Categoria: %s%n", categoria);
        System.out.printf("Data: %s%n", dataTransazione.format(formattoData));
        System.out.println("─".repeat(40));
        
        System.out.print("\\n✅ Confermi il salvataggio? (s/N): ");
        String conferma = scanner.nextLine().trim().toLowerCase();
        
        if (conferma.equals("s") || conferma.equals("si")) {
            // TODO: Salvare la transazione negli array
            importi[numTransazioni] = importo;
            descrizioni[numTransazioni] = descrizione;
            categorie[numTransazioni] = categoria;
            tipi[numTransazioni] = tipo;
            date[numTransazioni] = dataTransazione;
            attive[numTransazioni] = true;
            
            numTransazioni++;
            
            System.out.println("\\n🎉 Transazione salvata con successo!");
            System.out.printf("📊 Totale transazioni: %d%n", numTransazioni);
            
            // TODO: Controllare budget se è un'uscita
            if (tipo.equals("USCITA")) {
                controllaAlertBudget(categoria, importo);
            }
            
        } else {
            System.out.println("❌ Transazione annullata.");
        }
    }
    
    /**
     * TODO 5: Implementare visualizzazione transazioni con filtri
     * REQUISITI:
     * - Mostrare tutte le transazioni in formato tabellare
     * - Filtri per: tipo, categoria, periodo, importo
     * - Ordinamento per data, importo, categoria
     * - Paginazione se troppe transazioni
     * - Totali e statistiche
     */
    private static void visualizzaTransazioni() {
        System.out.println("\\n=== 📋 VISUALIZZAZIONE TRANSAZIONI ===");
        
        if (numTransazioni == 0) {
            System.out.println("📭 Nessuna transazione registrata.");
            System.out.println("💡 Usa l'opzione 1 per inserire la prima transazione.");
            return;
        }
        
        // TODO: Menu filtri
        System.out.println("\\n🔍 OPZIONI DI VISUALIZZAZIONE:");
        System.out.println("1. 📋 Tutte le transazioni");
        System.out.println("2. 📈 Solo entrate");
        System.out.println("3. 📉 Solo uscite");
        System.out.println("4. 📅 Filtra per periodo");
        System.out.println("5. 📂 Filtra per categoria");
        System.out.println("0. 🔙 Torna indietro");
        
        int filtro = leggiInteroConValidazione("👉 Scegli visualizzazione: ", 0, 5);
        
        switch (filtro) {
            case 0:
                return;
            case 1:
                mostraTransazioni(null, null, null, null);
                break;
            case 2:
                mostraTransazioni("ENTRATA", null, null, null);
                break;
            case 3:
                mostraTransazioni("USCITA", null, null, null);
                break;
            case 4:
                filtraPerPeriodo();
                break;
            case 5:
                filtraPerCategoria();
                break;
        }
    }
    
    /**
     * TODO 6: Implementare gestione budget e obiettivi
     * REQUISITI:
     * - Impostare budget mensile globale
     * - Impostare budget per singole categorie
     * - Definire obiettivi di risparmio
     * - Monitorare progresso verso obiettivi
     * - Alert automatici per superamento budget
     */
    private static void gestioneBudget() {
        System.out.println("\\n=== 🎯 GESTIONE BUDGET E OBIETTIVI ===");
        
        System.out.println("\\n📊 BUDGET ATTUALE:");
        System.out.printf("💰 Budget mensile: %s%n", 
                         budgetMensile > 0 ? formattoEuro.format(budgetMensile) : "Non impostato");
        System.out.printf("🎯 Obiettivo risparmio: %s%n", 
                         obiettivoRisparmio > 0 ? formattoEuro.format(obiettivoRisparmio) : "Non impostato");
        
        System.out.println("\\n🛠️ OPZIONI GESTIONE:");
        System.out.println("1. 💰 Imposta budget mensile");
        System.out.println("2. 🎯 Imposta obiettivo risparmio");
        System.out.println("3. 📂 Budget per categorie");
        System.out.println("4. 📊 Monitoraggio obiettivi");
        System.out.println("5. ⚙️ Calcola budget automatico");
        System.out.println("0. 🔙 Torna indietro");
        
        int scelta = leggiInteroConValidazione("👉 Scegli azione: ", 0, 5);
        
        switch (scelta) {
            case 1:
                impostaBudgetMensile();
                break;
            case 2:
                impostaObiettivoRisparmio();
                break;
            case 3:
                gestioneBudgetCategorie();
                break;
            case 4:
                monitoraggioObiettivi();
                break;
            case 5:
                calcolaBudgetAutomatico();
                break;
        }
    }
    
    /**
     * TODO 7: Implementare analisi spese dettagliata
     * REQUISITI:
     * - Raggruppamento spese per categoria
     * - Calcolo percentuali su totale
     * - Grafici ASCII per visualizzazione
     * - Confronto con periodi precedenti
     * - Identificazione categorie di spesa maggiori
     */
    private static void analisiSpese() {
        System.out.println("\\n=== 📊 ANALISI SPESE PER CATEGORIA ===");
        
        // TODO: Implementare analisi completa
        // Calcolare totali per categoria
        // Creare grafici ASCII
        // Mostrare trend e confronti
    }
    
    /**
     * TODO 8: Implementare generazione report mensile completo
     * REQUISITI:
     * - Report formattato con intestazione
     * - Riepilogo entrate e uscite
     * - Analisi per categoria
     * - Grafici e statistiche
     * - Consigli personalizzati
     * - Possibilità di salvare/stampare
     */
    private static void generaReportMensile() {
        System.out.println("\\n=== 📄 REPORT MENSILE ===");
        
        // TODO: Implementare report completo
    }
    
    /**
     * TODO 9: Implementare sistema consigli risparmio
     * REQUISITI:
     * - Analisi pattern di spesa
     * - Identificazione sprechi
     * - Suggerimenti personalizzati
     * - Calcolo potenziale risparmio
     * - Tips generali di gestione finanziaria
     */
    private static void consigliRisparmio() {
        System.out.println("\\n=== 💡 CONSIGLI PER IL RISPARMIO ===");
        
        // TODO: Implementare sistema consigli intelligente
    }
    
    // ==================== METODI DI SUPPORTO E UTILITÀ ====================
    
    /**
     * TODO 10: Implementare tutti i metodi di supporto necessari
     * Includere:
     * - Validazione input
     * - Calcoli finanziari
     * - Formattazione output
     * - Gestione date
     * - Utility varie
     */
    
    /**
     * Legge un intero con validazione del range
     */
    private static int leggiInteroConValidazione(String messaggio, int min, int max) {
        int numero;
        do {
            System.out.print(messaggio);
            try {
                numero = Integer.parseInt(scanner.nextLine().trim());
                if (numero < min || numero > max) {
                    System.out.printf("❌ Inserisci un numero tra %d e %d!%n", min, max);
                    continue;
                }
                return numero;
            } catch (NumberFormatException e) {
                System.out.println("❌ Inserisci un numero valido!");
            }
        } while (true);
    }
    
    /**
     * Calcola il totale delle transazioni per tipo e periodo
     */
    private static double calcolaTotalePerPeriodo(String tipo, LocalDate inizio, LocalDate fine) {
        double totale = 0;
        for (int i = 0; i < numTransazioni; i++) {
            if (attive[i] && 
                (tipo == null || tipi[i].equals(tipo)) &&
                !date[i].isBefore(inizio) && 
                !date[i].isAfter(fine)) {
                totale += importi[i];
            }
        }
        return totale;
    }
    
    /**
     * Sceglie una categoria da lista predefinita + personalizzate
     */
    private static String scegliCategoria(String tipoTransazione) {
        // TODO: Implementare selezione categoria
        String[] categorieBase;
        
        if (tipoTransazione.equals("ENTRATA")) {
            categorieBase = new String[]{"STIPENDIO", "BONUS", "VENDITA", "INVESTIMENTI", "REGALO", "ALTRO"};
        } else {
            categorieBase = new String[]{"ALIMENTARI", "TRASPORTI", "CASA", "SALUTE", "SVAGO", "ABBIGLIAMENTO", 
                                       "TECNOLOGIA", "SPORT", "VIAGGI", "EDUCAZIONE", "ALTRO"};
        }
        
        System.out.printf("\\n📂 CATEGORIE %s:%n", tipoTransazione);
        for (int i = 0; i < categorieBase.length; i++) {
            System.out.printf("%d. %s%n", i + 1, categorieBase[i]);
        }
        
        // TODO: Aggiungere categorie personalizzate
        
        int scelta = leggiInteroConValidazione("👉 Scegli categoria: ", 1, categorieBase.length);
        return categorieBase[scelta - 1];
    }
    
    /**
     * Inserisce e valida una data
     */
    private static LocalDate inserisciData() {
        System.out.print("\\n📅 Data transazione (dd/mm/yyyy, invio per oggi): ");
        String inputData = scanner.nextLine().trim();
        
        if (inputData.isEmpty()) {
            return LocalDate.now();
        }
        
        try {
            return LocalDate.parse(inputData, formattoData);
        } catch (Exception e) {
            System.out.println("⚠️ Data non valida, uso data odierna.");
            return LocalDate.now();
        }
    }
    
    /**
     * Controlla alert budget per categoria
     */
    private static void controllaAlertBudget(String categoria, double importo) {
        // TODO: Implementare controllo budget per categoria
        
        if (budgetMensile > 0) {
            LocalDate oggi = LocalDate.now();
            LocalDate inizioMese = oggi.withDayOfMonth(1);
            LocalDate fineMese = oggi.withDayOfMonth(oggi.lengthOfMonth());
            
            double totaleUsciteMese = calcolaTotalePerPeriodo("USCITA", inizioMese, fineMese);
            double percentualeUtilizzata = totaleUsciteMese / budgetMensile;
            
            if (percentualeUtilizzata >= SOGLIA_ALLERTA_SPESA) {
                System.out.printf("\\n⚠️ ALLERTA BUDGET: Hai utilizzato %s del budget mensile!%n", 
                                formattoPercentuale.format(percentualeUtilizzata));
                
                double rimanente = budgetMensile - totaleUsciteMese;
                if (rimanente > 0) {
                    System.out.printf("💰 Budget rimanente: %s%n", formattoEuro.format(rimanente));
                } else {
                    System.out.printf("🔴 Budget superato di: %s%n", formattoEuro.format(-rimanente));
                }
            }
        }
    }
    
    /**
     * Metodi placeholder da implementare
     */
    private static void inizializzaSistema() {
        System.out.println("🔧 Inizializzazione sistema...");
        
        // TODO: Caricare dati di esempio (opzionale)
        // Inizializzare categorie predefinite
        // Impostazioni di default
        
        System.out.println("✅ Sistema pronto!");
    }
    
    private static void chiudiSistema() {
        System.out.println("\\n👋 Chiusura sistema...");
        System.out.printf("💾 Transazioni elaborate: %d%n", numTransazioni);
        System.out.println("📊 Grazie per aver utilizzato il sistema di gestione budget!");
        System.out.println("💡 I tuoi dati finanziari sono al sicuro!");
    }
    
    // TODO: Implementare tutti gli altri metodi necessari
    private static void mostraTransazioni(String tipoFiltro, String categoriaFiltro, 
                                        LocalDate dataInizio, LocalDate dataFine) {
        // TODO: Implementare visualizzazione filtrata
    }
    
    private static void filtraPerPeriodo() {
        // TODO: Implementare filtro periodo
    }
    
    private static void filtraPerCategoria() {
        // TODO: Implementare filtro categoria
    }
    
    private static void impostaBudgetMensile() {
        // TODO: Implementare impostazione budget
    }
    
    private static void impostaObiettivoRisparmio() {
        // TODO: Implementare obiettivo risparmio
    }
    
    private static void gestioneBudgetCategorie() {
        // TODO: Implementare budget categorie
    }
    
    private static void monitoraggioObiettivi() {
        // TODO: Implementare monitoraggio
    }
    
    private static void calcolaBudgetAutomatico() {
        // TODO: Implementare calcolo automatico
    }
    
    private static void gestioneCategorie() {
        // TODO: Implementare gestione categorie personalizzate
    }
    
    private static void gestioneDati() {
        // TODO: Implementare import/export
    }
    
    private static void impostazioniSistema() {
        // TODO: Implementare impostazioni
    }
}

/*
 * ==================== ISTRUZIONI PER LO STUDENTE ====================
 * 
 * COME PROCEDERE:
 * 1. Leggi attentamente tutti i TODO commentati nel codice
 * 2. Implementa i metodi uno alla volta, testando frequentemente
 * 3. Inizia dalle funzionalità base (menu, inserimento transazione)
 * 4. Aggiungi gradualmente le funzionalità avanzate
 * 5. Testa ogni funzione con dati diversi
 * 6. Gestisci tutti i casi di errore possibili
 * 7. Commenta il tuo codice adeguatamente
 * 
 * SUGGERIMENTI:
 * - Usa BigDecimal per calcoli monetari precisi
 * - Valida sempre l'input dell'utente
 * - Gestisci le eccezioni appropriatamente
 * - Formatta l'output in modo professionale
 * - Testa con casi limite (array pieni, date invalide, etc.)
 * 
 * VALUTAZIONE:
 * - Correttezza funzionale: 15 punti
 * - Qualità del codice: 10 punti
 * - Gestione errori: 10 punti
 * - Interfaccia utente: 5 punti
 * 
 * BONUS (5 punti extra):
 * - Implementare persistenza dati su file
 * - Aggiungere grafici ASCII per le statistiche
 * - Sistema di backup automatico
 * - Interfaccia multilingua
 * 
 * TEMPO STIMATO: 4-6 ore
 * DATA CONSEGNA: [Da definire dal docente]
 */
