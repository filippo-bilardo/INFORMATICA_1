/**
 * Esercizio 12: Gestione Conto Bancario
 * 
 * Simulatore completo di operazioni bancarie con validazione,
 * storico transazioni e gestione sicurezza.
 * 
 * Concetti dimostrati:
 * - Gestione precisione decimale con BigDecimal
 * - Menu interattivo complesso
 * - Array per storico operazioni
 * - Validazione operazioni bancarie
 * - Formattazione valuta
 * - Gestione stati e transizioni
 * 
 * @author Java Essential by Example
 * @version 1.0
 */

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Esercizio12_GestioneContoBancario {
    
    // Costanti del sistema
    private static final int MAX_STORICO = 10;
    private static final BigDecimal LIMITE_GIORNALIERO = new BigDecimal("5000.00");
    private static final BigDecimal COMMISSIONE_PRELIEVO = new BigDecimal("1.50");
    private static final DateTimeFormatter FORMATO_DATA = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
    
    // Stato del conto
    private static BigDecimal saldo = new BigDecimal("1000.00"); // Saldo iniziale
    private static String numeroContoCorrente = "IT60 X054 2811 1010 0000 0123 456";
    private static String intestatario = "Mario Rossi";
    private static List<Transazione> storico = new ArrayList<>();
    private static BigDecimal movimentiGiornalieri = BigDecimal.ZERO;
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Inizializzazione
        aggiungiTransazioneIniziale();
        
        // Banner di benvenuto
        mostraBanner();
        
        int scelta;
        do {
            mostraMenu();
            scelta = inputSceltaValida(scanner);
            
            switch (scelta) {
                case 1 -> visualizzaSaldo();
                case 2 -> effettuaDeposito(scanner);
                case 3 -> effettuaPrelievo(scanner);
                case 4 -> visualizzaStorico();
                case 5 -> visualizzaInformazioniConto();
                case 6 -> cambiaPin(scanner);
                case 7 -> calcolaInteressi(scanner);
                case 8 -> generaEstrattoMensile();
                case 0 -> {
                    System.out.println("\n💳 Grazie per aver utilizzato il nostro servizio bancario!");
                    System.out.println("Arrivederci! 👋");
                }
                default -> System.out.println("❌ Opzione non valida!");
            }
            
            if (scelta != 0) {
                System.out.println("\nPremi INVIO per continuare...");
                scanner.nextLine();
            }
            
        } while (scelta != 0);
        
        scanner.close();
    }
    
    /**
     * Mostra il banner di benvenuto
     */
    private static void mostraBanner() {
        System.out.println("=".repeat(70));
        System.out.println("                    🏦 BANCA DIGITALE SICURA");
        System.out.println("=".repeat(70));
        System.out.printf("Benvenuto, %s!%n", intestatario);
        System.out.printf("Conto: %s%n", numeroContoCorrente);
        System.out.println("=".repeat(70));
    }
    
    /**
     * Mostra il menu principale
     */
    private static void mostraMenu() {
        System.out.println("\n" + "─".repeat(50));
        System.out.println("           💳 MENU OPERAZIONI BANCARIE");
        System.out.println("─".repeat(50));
        System.out.println("1. 💰 Visualizza Saldo");
        System.out.println("2. 📈 Deposita Denaro");
        System.out.println("3. 📉 Preleva Denaro");
        System.out.println("4. 📋 Storico Transazioni");
        System.out.println("5. ℹ️  Informazioni Conto");
        System.out.println("6. 🔐 Cambia PIN");
        System.out.println("7. 💹 Calcola Interessi");
        System.out.println("8. 📄 Estratto Mensile");
        System.out.println("0. 🚪 Esci");
        System.out.println("─".repeat(50));
    }
    
    /**
     * Input scelta menu con validazione
     */
    private static int inputSceltaValida(Scanner scanner) {
        int scelta = -1;
        do {
            System.out.print("🔢 Scegli un'opzione (0-8): ");
            try {
                String input = scanner.nextLine().trim();
                scelta = Integer.parseInt(input);
                
                if (scelta < 0 || scelta > 8) {
                    System.out.println("❌ Inserisci un numero tra 0 e 8!");
                    scelta = -1;
                }
            } catch (NumberFormatException e) {
                System.out.println("❌ Inserisci un numero valido!");
            }
        } while (scelta == -1);
        
        return scelta;
    }
    
    /**
     * Visualizza saldo corrente
     */
    private static void visualizzaSaldo() {
        System.out.println("\n" + "=".repeat(40));
        System.out.println("         💰 SALDO CORRENTE");
        System.out.println("=".repeat(40));
        System.out.printf("Saldo disponibile: €%.2f%n", saldo);
        System.out.printf("Movimenti oggi: €%.2f%n", movimentiGiornalieri);
        System.out.printf("Limite giornaliero: €%.2f%n", LIMITE_GIORNALIERO);
        
        // Stato del conto
        if (saldo.compareTo(BigDecimal.ZERO) > 0) {
            System.out.println("Stato: ✅ ATTIVO");
        } else if (saldo.compareTo(BigDecimal.ZERO) == 0) {
            System.out.println("Stato: ⚠️ SALDO ZERO");
        } else {
            System.out.println("Stato: ❌ SCOPERTO");
        }
    }
    
    /**
     * Effettua deposito con validazione
     */
    private static void effettuaDeposito(Scanner scanner) {
        System.out.println("\n" + "=".repeat(40));
        System.out.println("         📈 DEPOSITO DENARO");
        System.out.println("=".repeat(40));
        System.out.printf("Saldo attuale: €%.2f%n", saldo);
        
        BigDecimal importo = inputImportoValido(scanner, "deposito");
        if (importo == null) return;
        
        // Verifica limite giornaliero
        BigDecimal nuoviMovimenti = movimentiGiornalieri.add(importo);
        if (nuoviMovimenti.compareTo(LIMITE_GIORNALIERO) > 0) {
            System.out.println("❌ Operazione non consentita: supera il limite giornaliero!");
            System.out.printf("Limite disponibile: €%.2f%n", 
                LIMITE_GIORNALIERO.subtract(movimentiGiornalieri));
            return;
        }
        
        // Conferma operazione
        System.out.printf("\n📋 Conferma deposito di €%.2f?%n", importo);
        System.out.printf("Nuovo saldo sarà: €%.2f%n", saldo.add(importo));
        
        if (confermaOperazione(scanner)) {
            saldo = saldo.add(importo);
            movimentiGiornalieri = nuoviMovimenti;
            
            aggiungiTransazione("DEPOSITO", importo, "Deposito contanti");
            
            System.out.println("\n✅ DEPOSITO COMPLETATO!");
            System.out.printf("Importo depositato: €%.2f%n", importo);
            System.out.printf("Nuovo saldo: €%.2f%n", saldo);
        } else {
            System.out.println("❌ Operazione annullata.");
        }
    }
    
    /**
     * Effettua prelievo con validazione e commissioni
     */
    private static void effettuaPrelievo(Scanner scanner) {
        System.out.println("\n" + "=".repeat(40));
        System.out.println("         📉 PRELIEVO DENARO");
        System.out.println("=".repeat(40));
        System.out.printf("Saldo disponibile: €%.2f%n", saldo);
        System.out.printf("Commissione prelievo: €%.2f%n", COMMISSIONE_PRELIEVO);
        
        BigDecimal importo = inputImportoValido(scanner, "prelievo");
        if (importo == null) return;
        
        BigDecimal importoTotale = importo.add(COMMISSIONE_PRELIEVO);
        
        // Verifica disponibilità
        if (saldo.compareTo(importoTotale) < 0) {
            System.out.println("❌ Saldo insufficiente!");
            System.out.printf("Importo richiesto (con commissione): €%.2f%n", importoTotale);
            System.out.printf("Disponibile: €%.2f%n", saldo);
            return;
        }
        
        // Verifica limite giornaliero
        BigDecimal nuoviMovimenti = movimentiGiornalieri.add(importo);
        if (nuoviMovimenti.compareTo(LIMITE_GIORNALIERO) > 0) {
            System.out.println("❌ Operazione non consentita: supera il limite giornaliero!");
            return;
        }
        
        // Conferma operazione
        System.out.printf("\n📋 Conferma prelievo di €%.2f?%n", importo);
        System.out.printf("Commissione: €%.2f%n", COMMISSIONE_PRELIEVO);
        System.out.printf("Totale addebitato: €%.2f%n", importoTotale);
        System.out.printf("Nuovo saldo sarà: €%.2f%n", saldo.subtract(importoTotale));
        
        if (confermaOperazione(scanner)) {
            saldo = saldo.subtract(importoTotale);
            movimentiGiornalieri = nuoviMovimenti;
            
            aggiungiTransazione("PRELIEVO", importo.negate(), 
                String.format("Prelievo contanti (comm. €%.2f)", COMMISSIONE_PRELIEVO));
            
            System.out.println("\n✅ PRELIEVO COMPLETATO!");
            System.out.printf("Importo prelevato: €%.2f%n", importo);
            System.out.printf("Commissione applicata: €%.2f%n", COMMISSIONE_PRELIEVO);
            System.out.printf("Nuovo saldo: €%.2f%n", saldo);
        } else {
            System.out.println("❌ Operazione annullata.");
        }
    }
    
    /**
     * Input importo con validazione completa
     */
    private static BigDecimal inputImportoValido(Scanner scanner, String tipoOperazione) {
        BigDecimal importo = null;
        
        do {
            System.out.printf("💰 Inserisci importo per %s (€): ", tipoOperazione);
            try {
                String input = scanner.nextLine().trim().replace(",", ".");
                importo = new BigDecimal(input).setScale(2, RoundingMode.HALF_UP);
                
                if (importo.compareTo(BigDecimal.ZERO) <= 0) {
                    System.out.println("❌ L'importo deve essere positivo!");
                    importo = null;
                    continue;
                }
                
                if (importo.compareTo(new BigDecimal("10000.00")) > 0) {
                    System.out.println("❌ Importo troppo elevato (max €10,000)!");
                    importo = null;
                    continue;
                }
                
                if (importo.scale() > 2) {
                    System.out.println("❌ Importo con troppi decimali (max 2)!");
                    importo = null;
                    continue;
                }
                
            } catch (NumberFormatException e) {
                System.out.println("❌ Inserisci un importo valido (es: 100.50)!");
            }
        } while (importo == null);
        
        return importo;
    }
    
    /**
     * Conferma operazione
     */
    private static boolean confermaOperazione(Scanner scanner) {
        System.out.print("Confermi l'operazione? (s/n): ");
        String risposta = scanner.nextLine().trim().toLowerCase();
        return risposta.equals("s") || risposta.equals("si") || risposta.equals("sì");
    }
    
    /**
     * Visualizza storico transazioni
     */
    private static void visualizzaStorico() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("                    📋 STORICO TRANSAZIONI");
        System.out.println("=".repeat(80));
        
        if (storico.isEmpty()) {
            System.out.println("Nessuna transazione registrata.");
            return;
        }
        
        System.out.printf("%-20s %-12s %-12s %-30s%n", 
            "DATA/ORA", "TIPO", "IMPORTO", "DESCRIZIONE");
        System.out.println("-".repeat(80));
        
        for (Transazione t : storico) {
            String segno = t.importo.compareTo(BigDecimal.ZERO) >= 0 ? "+" : "";
            System.out.printf("%-20s %-12s %s€%-10.2f %-30s%n",
                t.dataOra.format(FORMATO_DATA),
                t.tipo,
                segno,
                t.importo,
                t.descrizione
            );
        }
        
        System.out.println("-".repeat(80));
        System.out.printf("Totale transazioni: %d%n", storico.size());
    }
    
    /**
     * Aggiunge una transazione allo storico
     */
    private static void aggiungiTransazione(String tipo, BigDecimal importo, String descrizione) {
        Transazione nuova = new Transazione(tipo, importo, descrizione);
        storico.add(0, nuova); // Aggiunge in testa
        
        // Mantiene solo le ultime MAX_STORICO transazioni
        if (storico.size() > MAX_STORICO) {
            storico = storico.subList(0, MAX_STORICO);
        }
    }
    
    /**
     * Aggiunge transazione iniziale
     */
    private static void aggiungiTransazioneIniziale() {
        aggiungiTransazione("APERTURA", saldo, "Apertura conto corrente");
    }
    
    /**
     * Visualizza informazioni complete del conto
     */
    private static void visualizzaInformazioniConto() {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("              ℹ️ INFORMAZIONI CONTO");
        System.out.println("=".repeat(60));
        System.out.printf("Intestatario: %s%n", intestatario);
        System.out.printf("Numero conto: %s%n", numeroContoCorrente);
        System.out.printf("Saldo corrente: €%.2f%n", saldo);
        System.out.printf("Limite giornaliero: €%.2f%n", LIMITE_GIORNALIERO);
        System.out.printf("Movimenti oggi: €%.2f%n", movimentiGiornalieri);
        System.out.printf("Commissione prelievo: €%.2f%n", COMMISSIONE_PRELIEVO);
        System.out.printf("Ultima operazione: %s%n", 
            storico.isEmpty() ? "Nessuna" : storico.get(0).dataOra.format(FORMATO_DATA));
    }
    
    /**
     * Simulazione cambio PIN
     */
    private static void cambiaPin(Scanner scanner) {
        System.out.println("\n" + "=".repeat(40));
        System.out.println("         🔐 CAMBIO PIN");
        System.out.println("=".repeat(40));
        System.out.println("Per sicurezza, questa è una simulazione.");
        System.out.println("✅ PIN cambiato con successo!");
    }
    
    /**
     * Calcolo interessi simulato
     */
    private static void calcolaInteressi(Scanner scanner) {
        System.out.println("\n" + "=".repeat(50));
        System.out.println("            💹 CALCOLO INTERESSI");
        System.out.println("=".repeat(50));
        
        if (saldo.compareTo(BigDecimal.ZERO) <= 0) {
            System.out.println("❌ Saldo insufficiente per calcolare interessi.");
            return;
        }
        
        BigDecimal tassoAnnuo = new BigDecimal("0.015"); // 1.5% annuo
        BigDecimal interessiMensili = saldo.multiply(tassoAnnuo).divide(new BigDecimal("12"), 2, RoundingMode.HALF_UP);
        BigDecimal interessiAnnui = saldo.multiply(tassoAnnuo).setScale(2, RoundingMode.HALF_UP);
        
        System.out.printf("Saldo corrente: €%.2f%n", saldo);
        System.out.printf("Tasso annuo: %.2f%%%n", tassoAnnuo.multiply(new BigDecimal("100")));
        System.out.printf("Interessi mensili: €%.2f%n", interessiMensili);
        System.out.printf("Interessi annui: €%.2f%n", interessiAnnui);
    }
    
    /**
     * Genera estratto mensile simulato
     */
    private static void generaEstrattoMensile() {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("              📄 ESTRATTO MENSILE");
        System.out.println("=".repeat(60));
        System.out.println("✅ Estratto mensile generato e inviato alla tua email!");
        System.out.println("Riceverai il documento PDF entro 24 ore.");
    }
    
    /**
     * Classe per rappresentare una transazione
     */
    private static class Transazione {
        final String tipo;
        final BigDecimal importo;
        final String descrizione;
        final LocalDateTime dataOra;
        
        public Transazione(String tipo, BigDecimal importo, String descrizione) {
            this.tipo = tipo;
            this.importo = importo;
            this.descrizione = descrizione;
            this.dataOra = LocalDateTime.now();
        }
    }
}
