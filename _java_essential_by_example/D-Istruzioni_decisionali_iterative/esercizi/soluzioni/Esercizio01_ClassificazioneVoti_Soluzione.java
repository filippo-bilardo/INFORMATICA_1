/**
 * SOLUZIONE ESERCIZIO D.1 - Sistema di Classificazione Voti Scolastici
 * 
 * Questa soluzione completa dimostra l'implementazione di un sistema avanzato
 * per la classificazione e analisi di voti scolastici utilizzando:
 * - Strutture condizionali if-else annidate
 * - Istruzione switch-case con enum
 * - Operatori logici e relazionali
 * - Validazione input completa
 * - Logica decisionale multi-livello
 * 
 * @author Docente
 * @version 1.0 - Soluzione Completa
 */

import java.util.Scanner;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class Esercizio01_ClassificazioneVoti_Soluzione {
    
    // Costanti per la classificazione dei voti
    private static final double SOGLIA_INSUFFICIENTE = 6.0;
    private static final double SOGLIA_SUFFICIENTE = 7.0;
    private static final double SOGLIA_BUONO = 8.0;
    private static final double SOGLIA_OTTIMO = 9.0;
    
    // Formattatori per output
    private static final DecimalFormat formattoVoto = new DecimalFormat("#0.0");
    private static final DecimalFormat formattoPercentuale = new DecimalFormat("#0.0%");
    
    private static Scanner scanner = new Scanner(System.in);
    private static List<Double> votiInseriti = new ArrayList<>();
    
    /**
     * Enum per rappresentare le classificazioni dei voti
     */
    enum ClassificazioneVoto {
        GRAVEMENTE_INSUFFICIENTE("Gravemente Insufficiente", "🔴", 0.0, 4.0),
        INSUFFICIENTE("Insufficiente", "🟠", 4.0, 6.0),
        SUFFICIENTE("Sufficiente", "🟡", 6.0, 7.0),
        BUONO("Buono", "🟢", 7.0, 8.0),
        DISTINTO("Distinto", "🔵", 8.0, 9.0),
        OTTIMO("Ottimo", "🟣", 9.0, 10.0);
        
        private final String descrizione;
        private final String emoji;
        private final double min;
        private final double max;
        
        ClassificazioneVoto(String descrizione, String emoji, double min, double max) {
            this.descrizione = descrizione;
            this.emoji = emoji;
            this.min = min;
            this.max = max;
        }
        
        public String getDescrizione() { return descrizione; }
        public String getEmoji() { return emoji; }
        public double getMin() { return min; }
        public double getMax() { return max; }
    }
    
    /**
     * Menu principale del sistema
     */
    public static void main(String[] args) {
        System.out.println("╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║           SISTEMA CLASSIFICAZIONE VOTI SCOLASTICI           ║");
        System.out.println("║         Esercizio D.1 - Istruzioni Decisionali             ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");
        System.out.println();
        
        boolean continua = true;
        while (continua) {
            mostraMenu();
            int scelta = leggiIntero("👉 Inserisci la tua scelta: ");
            
            switch (scelta) {
                case 1:
                    classificaVotoSingolo();
                    break;
                case 2:
                    analisiVotiMultipli();
                    break;
                case 3:
                    calcolaMediaClasse();
                    break;
                case 4:
                    simulatoreEsame();
                    break;
                case 5:
                    analisiStatistica();
                    break;
                case 0:
                    continua = false;
                    System.out.println("👋 Grazie per aver usato il sistema!");
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
     * Mostra il menu principale
     */
    private static void mostraMenu() {
        System.out.println("\n╔════════════════════════════════════════════╗");
        System.out.println("║               MENU PRINCIPALE              ║");
        System.out.println("╠════════════════════════════════════════════╣");
        System.out.println("║ 1. 📊 Classifica voto singolo             ║");
        System.out.println("║ 2. 📈 Analisi voti multipli               ║");
        System.out.println("║ 3. 🧮 Calcola media classe                ║");
        System.out.println("║ 4. 🎯 Simulatore esame                    ║");
        System.out.println("║ 5. 📋 Analisi statistica completa         ║");
        System.out.println("║ 0. 🚪 Esci dal programma                   ║");
        System.out.println("╚════════════════════════════════════════════╝");
    }
    
    /**
     * SOLUZIONE 1: Implementazione classificazione di un voto singolo
     * Dimostra l'uso di if-else annidate e switch con enum
     */
    private static void classificaVotoSingolo() {
        System.out.println("\n=== 📊 CLASSIFICAZIONE VOTO SINGOLO ===");
        
        double voto = leggiVoto("Inserisci il voto da classificare (0-10): ");
        
        // Classificazione usando if-else annidate
        ClassificazioneVoto classificazione = classificaVoto(voto);
        
        // Mostra risultato dettagliato
        System.out.println("\n┌─────────────────────────────────────────┐");
        System.out.println("│           RISULTATO CLASSIFICAZIONE      │");
        System.out.println("├─────────────────────────────────────────┤");
        System.out.printf("│ Voto inserito: %s%-25s │%n", formattoVoto.format(voto), "");
        System.out.printf("│ Classificazione: %s %-20s │%n", 
                          classificazione.getEmoji(), classificazione.getDescrizione());
        System.out.printf("│ Range: %.1f - %.1f%-23s │%n", 
                          classificazione.getMin(), classificazione.getMax(), "");
        System.out.println("└─────────────────────────────────────────┘");
        
        // Consigli personalizzati basati sul voto
        String consiglio = generaConsiglio(voto, classificazione);
        System.out.println("\n💡 " + consiglio);
        
        // Analisi dettagliata usando switch
        analizzaDettaglio(classificazione);
    }
    
    /**
     * Classifica un voto utilizzando if-else annidate
     */
    private static ClassificazioneVoto classificaVoto(double voto) {
        if (voto < 0 || voto > 10) {
            throw new IllegalArgumentException("Voto non valido");
        }
        
        // Utilizzo di if-else annidate per classificazione precisa
        if (voto < 4.0) {
            return ClassificazioneVoto.GRAVEMENTE_INSUFFICIENTE;
        } else if (voto < 6.0) {
            return ClassificazioneVoto.INSUFFICIENTE;
        } else if (voto < 7.0) {
            return ClassificazioneVoto.SUFFICIENTE;
        } else if (voto < 8.0) {
            return ClassificazioneVoto.BUONO;
        } else if (voto < 9.0) {
            return ClassificazioneVoto.DISTINTO;
        } else {
            return ClassificazioneVoto.OTTIMO;
        }
    }
    
    /**
     * Genera consigli personalizzati usando operatori logici complessi
     */
    private static String generaConsiglio(double voto, ClassificazioneVoto classificazione) {
        // Uso di operatori logici && e || per logica complessa
        if (voto < 4.0) {
            return "È necessario un recupero immediato. Studia i concetti base e chiedi aiuto.";
        } else if (voto >= 4.0 && voto < 6.0) {
            return "Servono più esercizi e ripasso. Concentrati sui punti deboli.";
        } else if (voto >= 6.0 && voto < 7.0) {
            return "Risultato accettabile. Continua a migliorare con costanza.";
        } else if (voto >= 7.0 && voto < 8.0) {
            return "Buon lavoro! Punta a risultati ancora migliori.";
        } else if (voto >= 8.0 && voto < 9.0) {
            return "Ottima preparazione! Mantieni questo livello.";
        } else if (voto >= 9.0 && voto <= 10.0) {
            return "Eccellente! Sei un esempio per gli altri.";
        }
        return "Valutazione completata.";
    }
    
    /**
     * Analisi dettagliata usando switch con enum
     */
    private static void analizzaDettaglio(ClassificazioneVoto classificazione) {
        System.out.println("\n🔍 ANALISI DETTAGLIATA:");
        
        // Uso di switch con enum per analisi strutturata
        switch (classificazione) {
            case GRAVEMENTE_INSUFFICIENTE:
                System.out.println("• Situazione critica che richiede intervento immediato");
                System.out.println("• Necessario piano di recupero personalizzato");
                System.out.println("• Contattare i genitori e organizzare supporto extra");
                break;
                
            case INSUFFICIENTE:
                System.out.println("• Preparazione inadeguata ma recuperabile");
                System.out.println("• Programmare sessioni di ripasso mirate");
                System.out.println("• Verificare comprensione dei prerequisiti");
                break;
                
            case SUFFICIENTE:
                System.out.println("• Obiettivi minimi raggiunti");
                System.out.println("• Incoraggiare a puntare più in alto");
                System.out.println("• Consolidare le basi prima di procedere");
                break;
                
            case BUONO:
                System.out.println("• Buona preparazione generale");
                System.out.println("• Approfondire alcuni aspetti specifici");
                System.out.println("• Sviluppare maggiore sicurezza nell'esposizione");
                break;
                
            case DISTINTO:
                System.out.println("• Preparazione solida e completa");
                System.out.println("• Capacità di collegare concetti diversi");
                System.out.println("• Pronto per argomenti più complessi");
                break;
                
            case OTTIMO:
                System.out.println("• Eccellente padronanza della materia");
                System.out.println("• Capacità di analisi critica sviluppata");
                System.out.println("• Può essere tutor per altri studenti");
                break;
                
            default:
                System.out.println("• Classificazione non riconosciuta");
        }
    }
    
    /**
     * SOLUZIONE 2: Analisi di voti multipli con statistiche
     */
    private static void analisiVotiMultipli() {
        System.out.println("\n=== 📈 ANALISI VOTI MULTIPLI ===");
        
        List<Double> voti = new ArrayList<>();
        System.out.println("Inserisci i voti (termina con -1):");
        
        double voto;
        do {
            voto = leggiVoto("Voto: ");
            if (voto != -1) {
                voti.add(voto);
                System.out.println("✅ Voto " + formattoVoto.format(voto) + " aggiunto");
            }
        } while (voto != -1 && voti.size() < 50);
        
        if (voti.isEmpty()) {
            System.out.println("❌ Nessun voto inserito!");
            return;
        }
        
        // Calcolo statistiche usando cicli e condizioni
        double somma = 0;
        double minimo = voti.get(0);
        double massimo = voti.get(0);
        int sufficienti = 0;
        
        for (double v : voti) {
            somma += v;
            if (v < minimo) minimo = v;
            if (v > massimo) massimo = v;
            if (v >= SOGLIA_INSUFFICIENTE) sufficienti++;
        }
        
        double media = somma / voti.size();
        double percentualeSufficienti = (double) sufficienti / voti.size();
        
        // Distribuzione per classificazione
        int[] distribuzione = new int[ClassificazioneVoto.values().length];
        for (double v : voti) {
            ClassificazioneVoto classif = classificaVoto(v);
            distribuzione[classif.ordinal()]++;
        }
        
        // Report statistico
        System.out.println("\n╔════════════════════════════════════════════╗");
        System.out.println("║           REPORT STATISTICO                ║");
        System.out.println("╠════════════════════════════════════════════╣");
        System.out.printf("║ Numero voti: %-29d ║%n", voti.size());
        System.out.printf("║ Media: %-35s ║%n", formattoVoto.format(media));
        System.out.printf("║ Voto minimo: %-28s ║%n", formattoVoto.format(minimo));
        System.out.printf("║ Voto massimo: %-27s ║%n", formattoVoto.format(massimo));
        System.out.printf("║ Sufficienti: %d/%d (%s)%-14s ║%n", 
                          sufficienti, voti.size(), 
                          formattoPercentuale.format(percentualeSufficienti), "");
        System.out.println("╚════════════════════════════════════════════╝");
        
        // Distribuzione dettagliata
        System.out.println("\n📊 DISTRIBUZIONE PER CLASSIFICAZIONE:");
        for (ClassificazioneVoto classif : ClassificazioneVoto.values()) {
            int count = distribuzione[classif.ordinal()];
            double percentuale = (double) count / voti.size();
            System.out.printf("%s %-20s: %2d (%s)%n", 
                              classif.getEmoji(), classif.getDescrizione(), 
                              count, formattoPercentuale.format(percentuale));
        }
        
        // Valutazione classe
        valutazioneClasse(media, percentualeSufficienti);
    }
    
    /**
     * Valutazione generale della classe usando condizioni multiple
     */
    private static void valutazioneClasse(double media, double percentualeSufficienti) {
        System.out.println("\n🎯 VALUTAZIONE GENERALE CLASSE:");
        
        // Logica complessa con operatori && e ||
        if (media >= 8.0 && percentualeSufficienti >= 0.9) {
            System.out.println("🟣 CLASSE ECCELLENTE - Risultati straordinari!");
        } else if (media >= 7.0 && percentualeSufficienti >= 0.8) {
            System.out.println("🔵 CLASSE MOLTO BUONA - Ottimo livello generale");
        } else if (media >= 6.5 && percentualeSufficienti >= 0.7) {
            System.out.println("🟢 CLASSE BUONA - Preparazione soddisfacente");
        } else if (media >= 6.0 || percentualeSufficienti >= 0.6) {
            System.out.println("🟡 CLASSE SUFFICIENTE - Necessari miglioramenti");
        } else {
            System.out.println("🟠 CLASSE INSUFFICIENTE - Intervento necessario");
        }
    }
    
    /**
     * SOLUZIONE 3: Calcolo media classe con pesi diversi
     */
    private static void calcolaMediaClasse() {
        System.out.println("\n=== 🧮 CALCOLA MEDIA CLASSE ===");
        
        System.out.println("Inserisci i voti per il calcolo della media ponderata:");
        
        double scritto = leggiVoto("Voto scritto: ");
        double orale = leggiVoto("Voto orale: ");
        double pratico = leggiVoto("Voto pratico: ");
        
        // Pesi per diverse tipologie di valutazione
        double pesoScritto = 0.4;
        double pesoOrale = 0.3;
        double pesoPratico = 0.3;
        
        double mediaPonderata = (scritto * pesoScritto) + 
                               (orale * pesoOrale) + 
                               (pratico * pesoPratico);
        
        ClassificazioneVoto classificazione = classificaVoto(mediaPonderata);
        
        System.out.println("\n📊 RISULTATO MEDIA PONDERATA:");
        System.out.println("┌─────────────────────────────────────────┐");
        System.out.printf("│ Scritto:  %.1f (peso %.0f%%)%-19s │%n", 
                          scritto, pesoScritto * 100, "");
        System.out.printf("│ Orale:    %.1f (peso %.0f%%)%-19s │%n", 
                          orale, pesoOrale * 100, "");
        System.out.printf("│ Pratico:  %.1f (peso %.0f%%)%-19s │%n", 
                          pratico, pesoPratico * 100, "");
        System.out.println("├─────────────────────────────────────────┤");
        System.out.printf("│ Media:    %-29s │%n", formattoVoto.format(mediaPonderata));
        System.out.printf("│ Esito:    %s %-22s │%n", 
                          classificazione.getEmoji(), classificazione.getDescrizione());
        System.out.println("└─────────────────────────────────────────┘");
        
        // Analisi componenti con condizioni
        analizzaComponenti(scritto, orale, pratico, mediaPonderata);
    }
    
    /**
     * Analizza le componenti del voto con condizioni multiple
     */
    private static void analizzaComponenti(double scritto, double orale, double pratico, double media) {
        System.out.println("\n🔍 ANALISI COMPONENTI:");
        
        // Identificazione punti di forza e debolezza
        double[] voti = {scritto, orale, pratico};
        String[] tipi = {"Scritto", "Orale", "Pratico"};
        
        double minimo = Math.min(Math.min(scritto, orale), pratico);
        double massimo = Math.max(Math.max(scritto, orale), pratico);
        
        for (int i = 0; i < voti.length; i++) {
            if (voti[i] == massimo && voti[i] > media) {
                System.out.printf("✅ %s: Punto di forza (%.1f)%n", tipi[i], voti[i]);
            } else if (voti[i] == minimo && voti[i] < media) {
                System.out.printf("⚠️ %s: Area di miglioramento (%.1f)%n", tipi[i], voti[i]);
            } else {
                System.out.printf("📝 %s: In linea con la media (%.1f)%n", tipi[i], voti[i]);
            }
        }
        
        // Consigli specifici usando condizioni
        if (Math.abs(massimo - minimo) > 2.0) {
            System.out.println("\n💡 CONSIGLIO: Grande differenza tra le valutazioni.");
            System.out.println("   Concentrarsi sull'area più debole per equilibrare il profilo.");
        } else if (media >= 8.0) {
            System.out.println("\n💡 CONSIGLIO: Eccellente preparazione generale.");
            System.out.println("   Mantenere questo livello e puntare all'eccellenza.");
        } else if (media < 6.0) {
            System.out.println("\n💡 CONSIGLIO: Necessario piano di recupero mirato.");
            System.out.println("   Rivedere i metodi di studio e chiedere supporto.");
        }
    }
    
    /**
     * SOLUZIONE 4: Simulatore di esame con domande multiple
     */
    private static void simulatoreEsame() {
        System.out.println("\n=== 🎯 SIMULATORE ESAME ===");
        
        int numDomande = leggiIntero("Numero di domande (max 10): ");
        if (numDomande > 10) numDomande = 10;
        
        double[] votiDomande = new double[numDomande];
        double somma = 0;
        
        System.out.println("\nInserisci i voti per ogni domanda:");
        for (int i = 0; i < numDomande; i++) {
            votiDomande[i] = leggiVoto("Domanda " + (i + 1) + ": ");
            somma += votiDomande[i];
        }
        
        double mediaEsame = somma / numDomande;
        ClassificazioneVoto esitoEsame = classificaVoto(mediaEsame);
        
        // Simulazione esito finale con condizioni
        boolean promosso = mediaEsame >= SOGLIA_INSUFFICIENTE;
        String esitoFinale = promosso ? "PROMOSSO" : "NON PROMOSSO";
        String emojiEsito = promosso ? "✅" : "❌";
        
        System.out.println("\n🎓 RISULTATO SIMULAZIONE ESAME:");
        System.out.println("╔════════════════════════════════════════════╗");
        System.out.println("║              ESITO FINALE                  ║");
        System.out.println("╠════════════════════════════════════════════╣");
        System.out.printf("║ Media esame: %-29s ║%n", formattoVoto.format(mediaEsame));
        System.out.printf("║ Classificazione: %s %-20s ║%n", 
                          esitoEsame.getEmoji(), esitoEsame.getDescrizione());
        System.out.printf("║ Esito: %s %-31s ║%n", emojiEsito, esitoFinale);
        System.out.println("╚════════════════════════════════════════════╝");
        
        // Analisi performance per domanda
        System.out.println("\n📋 DETTAGLIO PER DOMANDA:");
        for (int i = 0; i < numDomande; i++) {
            ClassificazioneVoto classifDomanda = classificaVoto(votiDomande[i]);
            System.out.printf("Domanda %d: %s %s (%s)%n", 
                              i + 1, 
                              classifDomanda.getEmoji(),
                              formattoVoto.format(votiDomande[i]),
                              classifDomanda.getDescrizione());
        }
        
        // Consigli post-esame
        if (promosso && mediaEsame >= 8.0) {
            System.out.println("\n🎉 Ottima performance! Continua così!");
        } else if (promosso) {
            System.out.println("\n👍 Esame superato. Lavora sui punti deboli per migliorare.");
        } else {
            System.out.println("\n💪 Non scoraggiarti. Analizza gli errori e ripeti la preparazione.");
        }
    }
    
    /**
     * SOLUZIONE 5: Analisi statistica completa
     */
    private static void analisiStatistica() {
        System.out.println("\n=== 📋 ANALISI STATISTICA COMPLETA ===");
        
        if (votiInseriti.isEmpty()) {
            System.out.println("❌ Nessun dato disponibile per l'analisi.");
            System.out.println("💡 Usa prima le altre funzioni per inserire dei voti.");
            return;
        }
        
        // Statistiche descrittive
        double media = calcolaMedia(votiInseriti);
        double mediana = calcolaMediana(votiInseriti);
        double varianza = calcolaVarianza(votiInseriti, media);
        double deviazioneStandard = Math.sqrt(varianza);
        
        System.out.println("\n📊 STATISTICHE DESCRITTIVE:");
        System.out.println("┌─────────────────────────────────────────┐");
        System.out.printf("│ Campione: %-29d │%n", votiInseriti.size());
        System.out.printf("│ Media: %-32s │%n", formattoVoto.format(media));
        System.out.printf("│ Mediana: %-30s │%n", formattoVoto.format(mediana));
        System.out.printf("│ Varianza: %-29s │%n", formattoVoto.format(varianza));
        System.out.printf("│ Dev. Standard: %-23s │%n", formattoVoto.format(deviazioneStandard));
        System.out.println("└─────────────────────────────────────────┘");
        
        // Analisi distribuzione normale
        if (deviazioneStandard > 0) {
            analisiDistribuzioneNormale(votiInseriti, media, deviazioneStandard);
        }
        
        // Confronto con standard nazionali (simulato)
        confrontoStandardNazionali(media);
    }
    
    /**
     * Calcola la media aritmetica
     */
    private static double calcolaMedia(List<Double> voti) {
        return voti.stream().mapToDouble(Double::doubleValue).average().orElse(0.0);
    }
    
    /**
     * Calcola la mediana
     */
    private static double calcolaMediana(List<Double> voti) {
        List<Double> votiOrdinati = new ArrayList<>(voti);
        votiOrdinati.sort(Double::compareTo);
        
        int n = votiOrdinati.size();
        if (n % 2 == 0) {
            return (votiOrdinati.get(n/2 - 1) + votiOrdinati.get(n/2)) / 2.0;
        } else {
            return votiOrdinati.get(n/2);
        }
    }
    
    /**
     * Calcola la varianza
     */
    private static double calcolaVarianza(List<Double> voti, double media) {
        double sommaQuadrati = 0;
        for (double voto : voti) {
            sommaQuadrati += Math.pow(voto - media, 2);
        }
        return sommaQuadrati / voti.size();
    }
    
    /**
     * Analizza la distribuzione secondo la curva normale
     */
    private static void analisiDistribuzioneNormale(List<Double> voti, double media, double devStandard) {
        System.out.println("\n🔔 ANALISI DISTRIBUZIONE NORMALE:");
        
        int dentroUnaSigma = 0;
        int dentroDueSigma = 0;
        int dentroTreSigma = 0;
        
        for (double voto : voti) {
            double distanza = Math.abs(voto - media);
            if (distanza <= devStandard) dentroUnaSigma++;
            if (distanza <= 2 * devStandard) dentroDueSigma++;
            if (distanza <= 3 * devStandard) dentroTreSigma++;
        }
        
        System.out.printf("• Entro 1σ: %d/%d (%.1f%%) - Atteso ~68%%%n",
                          dentroUnaSigma, voti.size(), 
                          (double)dentroUnaSigma/voti.size()*100);
        System.out.printf("• Entro 2σ: %d/%d (%.1f%%) - Atteso ~95%%%n",
                          dentroDueSigma, voti.size(), 
                          (double)dentroDueSigma/voti.size()*100);
        System.out.printf("• Entro 3σ: %d/%d (%.1f%%) - Atteso ~99.7%%%n",
                          dentroTreSigma, voti.size(), 
                          (double)dentroTreSigma/voti.size()*100);
    }
    
    /**
     * Confronto con standard nazionali simulati
     */
    private static void confrontoStandardNazionali(double media) {
        double mediaNazionale = 6.8; // Valore simulato
        
        System.out.println("\n🇮🇹 CONFRONTO STANDARD NAZIONALI:");
        System.out.printf("• Media nazionale: %.1f%n", mediaNazionale);
        System.out.printf("• Media locale: %.1f%n", media);
        
        double differenza = media - mediaNazionale;
        if (differenza > 0.5) {
            System.out.printf("✅ Sopra la media nazionale (+%.1f)%n", differenza);
        } else if (differenza < -0.5) {
            System.out.printf("⚠️ Sotto la media nazionale (%.1f)%n", differenza);
        } else {
            System.out.println("📊 In linea con la media nazionale");
        }
    }
    
    /**
     * Utility: Legge un voto con validazione completa
     */
    private static double leggiVoto(String messaggio) {
        double voto;
        do {
            System.out.print(messaggio);
            try {
                voto = Double.parseDouble(scanner.nextLine());
                if (voto == -1) return -1; // Valore speciale per uscita
                
                if (voto < 0 || voto > 10) {
                    System.out.println("❌ Errore: Il voto deve essere compreso tra 0 e 10!");
                    continue;
                }
                
                // Aggiunge alla lista globale per statistiche
                if (voto != -1) {
                    votiInseriti.add(voto);
                }
                
                return voto;
            } catch (NumberFormatException e) {
                System.out.println("❌ Errore: Inserisci un numero valido!");
            }
        } while (true);
    }
    
    /**
     * Utility: Legge un intero con validazione
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
}
