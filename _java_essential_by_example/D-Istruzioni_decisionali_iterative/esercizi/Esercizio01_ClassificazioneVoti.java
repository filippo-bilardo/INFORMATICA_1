/**
 * ESERCIZIO D.1 - Sistema di Classificazione Voti Scolastici
 * 
 * OBIETTIVO:
 * Creare un sistema interattivo per la classificazione e analisi di voti scolastici
 * che dimostri l'uso completo di istruzioni decisionali (if-else, switch) e 
 * strutture di controllo per la validazione e l'elaborazione dati.
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 1. Input e validazione voti (0-10 con decimali)
 * 2. Classificazione automatica (Insufficiente, Sufficiente, Buono, Ottimo)
 * 3. Calcolo media e statistiche
 * 4. Analisi distribuzione voti
 * 5. Consigli di miglioramento personalizzati
 * 6. Report finale con dettagli completi
 * 
 * CONCETTI APPLICATI:
 * - Strutture condizionali if-else annidate
 * - Istruzione switch-case con enum
 * - Operatori logici complessi (&&, ||, !)
 * - Operatori di confronto e relazionali
 * - Validazione input con controlli multipli
 * - Logica decisionale a più livelli
 * - Pattern di classificazione e categorizzazione
 * 
 * @author Studente
 * @version 1.0
 */

import java.util.Scanner;
import java.text.DecimalFormat;

public class Esercizio01_ClassificazioneVoti {
    
    // Costanti per la classificazione dei voti
    private static final double SOGLIA_INSUFFICIENTE = 6.0;
    private static final double SOGLIA_SUFFICIENTE = 7.0;
    private static final double SOGLIA_BUONO = 8.0;
    private static final double SOGLIA_OTTIMO = 9.0;
    
    // Formattatori per output
    private static final DecimalFormat formattoVoto = new DecimalFormat("#0.0");
    private static final DecimalFormat formattoPercentuale = new DecimalFormat("#0.0%");
    
    private static Scanner scanner = new Scanner(System.in);
    
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
     * TODO 1: Implementare classificazione di un voto singolo
     * REQUISITI:
     * - Input voto con validazione (0-10, decimali ammessi)
     * - Classificazione usando if-else o switch
     * - Mostrare categoria, descrizione, emoji
     * - Consigli personalizzati basati sul voto
     * - Gestione casi limite (0, 10, valori non validi)
     */
    private static void classificaVotoSingolo() {
        System.out.println("\n=== 📊 CLASSIFICAZIONE VOTO SINGOLO ===");
        
        // TODO: Richiedere input del voto
        double voto = richiedeVoto("📝 Inserisci il voto da classificare (0-10): ");
        
        // TODO: Classificare il voto usando strutture condizionali
        ClassificazioneVoto classificazione = classificaVoto(voto);
        
        // TODO: Mostrare risultato formattato
        System.out.println("\n📋 RISULTATO CLASSIFICAZIONE:");
        System.out.println("═".repeat(50));
        System.out.printf("📊 Voto: %s%n", formattoVoto.format(voto));
        System.out.printf("%s Classificazione: %s%n", 
                         classificazione.getEmoji(), 
                         classificazione.getDescrizione());
        
        // TODO: Aggiungere analisi dettagliata del voto
        analizzaVotoDettagliato(voto, classificazione);
        
        // TODO: Fornire consigli personalizzati
        fornsciConsigli(voto, classificazione);
    }
    
    /**
     * TODO 2: Implementare analisi di voti multipli
     * REQUISITI:
     * - Input di più voti (fino a che l'utente non inserisce -1)
     * - Classificazione di ogni voto
     * - Calcolo statistiche: media, voto più alto, più basso
     * - Distribuzione per categoria
     * - Report finale con grafici ASCII
     */
    private static void analisiVotiMultipli() {
        System.out.println("\n=== 📈 ANALISI VOTI MULTIPLI ===");
        System.out.println("💡 Inserisci i voti uno alla volta. Digita -1 per terminare.\n");
        
        // TODO: Array per memorizzare i voti
        double[] voti = new double[100]; // Massimo 100 voti
        int numeroVoti = 0;
        
        // TODO: Loop per input voti multipli
        while (numeroVoti < 100) {
            System.out.printf("📝 Voto #%d (o -1 per terminare): ", numeroVoti + 1);
            double voto = leggiDouble();
            
            // TODO: Condizione di uscita
            if (voto == -1) {
                if (numeroVoti == 0) {
                    System.out.println("⚠️ Nessun voto inserito!");
                    return;
                }
                break;
            }
            
            // TODO: Validazione voto
            if (validaVoto(voto)) {
                voti[numeroVoti] = voto;
                numeroVoti++;
                System.out.printf("✅ Voto %s registrato (%s)%n", 
                                formattoVoto.format(voto),
                                classificaVoto(voto).getDescrizione());
            } else {
                System.out.println("❌ Voto non valido! Deve essere tra 0 e 10.");
            }
        }
        
        // TODO: Analisi statistica dei voti
        analizzaStatistiche(voti, numeroVoti);
        
        // TODO: Distribuzione per categoria
        analizzaDistribuzione(voti, numeroVoti);
        
        // TODO: Consigli basati sui risultati
        consigliaBasatoSuMedia(voti, numeroVoti);
    }
    
    /**
     * TODO 3: Implementare calcolo media classe
     * REQUISITI:
     * - Input numero studenti
     * - Input voti per ogni studente con nome
     * - Calcolo media classe
     * - Classificazione della media
     * - Studenti sopra e sotto media
     * - Report completo classe
     */
    private static void calcolaMediaClasse() {
        System.out.println("\n=== 🧮 CALCOLO MEDIA CLASSE ===");
        
        // TODO: Richiedere numero studenti
        int numeroStudenti = leggiInteroConRange("👥 Inserisci numero studenti (1-50): ", 1, 50);
        
        // TODO: Array per memorizzare dati studenti
        String[] nomiStudenti = new String[numeroStudenti];
        double[] votiStudenti = new double[numeroStudenti];
        
        // TODO: Input dati per ogni studente
        for (int i = 0; i < numeroStudenti; i++) {
            System.out.printf("\n📚 STUDENTE #%d:%n", i + 1);
            
            // Nome studente
            System.out.print("👤 Nome studente: ");
            nomiStudenti[i] = scanner.nextLine().trim();
            
            // TODO: Validazione nome non vuoto
            while (nomiStudenti[i].isEmpty()) {
                System.out.print("❌ Nome non valido! Inserisci nome studente: ");
                nomiStudenti[i] = scanner.nextLine().trim();
            }
            
            // Voto studente
            votiStudenti[i] = richiedeVoto("📊 Voto di " + nomiStudenti[i] + ": ");
            
            // TODO: Feedback immediato
            ClassificazioneVoto classificazione = classificaVoto(votiStudenti[i]);
            System.out.printf("✅ %s: %s %s%n", 
                             nomiStudenti[i], 
                             formattoVoto.format(votiStudenti[i]),
                             classificazione.getEmoji());
        }
        
        // TODO: Calcolo e analisi media classe
        analizzaMediaClasse(nomiStudenti, votiStudenti, numeroStudenti);
    }
    
    /**
     * TODO 4: Implementare simulatore esame
     * REQUISITI:
     * - Simulazione di un esame con voti parziali
     * - Pesi diversi per diverse prove (scritto, orale, pratico)
     * - Calcolo voto finale ponderato
     * - Classificazione e consigli
     * - Simulazione "cosa succederebbe se..."
     */
    private static void simulatoreEsame() {
        System.out.println("\n=== 🎯 SIMULATORE ESAME ===");
        System.out.println("📚 Simula il calcolo del voto finale di un esame complesso.\n");
        
        // TODO: Configurazione pesi prove
        System.out.println("⚖️ CONFIGURAZIONE PESI PROVE:");
        System.out.println("1. 📝 Prova scritta: 40%");
        System.out.println("2. 🗣️ Prova orale: 35%");
        System.out.println("3. 💻 Prova pratica: 25%");
        System.out.println();
        
        // TODO: Input voti delle prove
        double votoScritto = richiedeVoto("📝 Voto prova scritta (0-10): ");
        double votoOrale = richiedeVoto("🗣️ Voto prova orale (0-10): ");
        double votoPratico = richiedeVoto("💻 Voto prova pratica (0-10): ");
        
        // TODO: Calcolo voto ponderato
        double votoFinale = calcolaVotoPonderato(votoScritto, votoOrale, votoPratico);
        
        // TODO: Analisi risultato
        analizzaRisultatoEsame(votoScritto, votoOrale, votoPratico, votoFinale);
        
        // TODO: Simulazione miglioramenti
        simulaMiglioramenti(votoScritto, votoOrale, votoPratico, votoFinale);
    }
    
    /**
     * TODO 5: Implementare analisi statistica completa
     * REQUISITI:
     * - Analisi di un dataset completo di voti
     * - Statistiche descrittive (media, mediana, moda)
     * - Distribuzione normale e outliers
     * - Grafici ASCII per visualizzazione
     * - Report professionale completo
     */
    private static void analisiStatistica() {
        System.out.println("\n=== 📋 ANALISI STATISTICA COMPLETA ===");
        
        // TODO: Implementare analisi completa
        // Questo è il metodo più avanzato che combina tutti i concetti
    }
    
    // ==================== METODI DI UTILITÀ ====================
    
    /**
     * TODO 6: Implementare classificazione voto con if-else o switch
     * REQUISITI:
     * - Usare if-else annidate O switch per classificare
     * - Gestire tutti i range di voti
     * - Restituire classificazione appropriata
     */
    private static ClassificazioneVoto classificaVoto(double voto) {
        // TODO: Implementare logica di classificazione
        
        // Esempio con if-else:
        if (voto < 0 || voto > 10) {
            throw new IllegalArgumentException("Voto non valido");
        } else if (voto < 4.0) {
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
        
        // TODO: Alternativa con switch (più complessa con range)
    }
    
    /**
     * TODO 7: Implementare validazione voto
     */
    private static boolean validaVoto(double voto) {
        // TODO: Implementare validazione completa
        return voto >= 0.0 && voto <= 10.0;
    }
    
    /**
     * TODO 8: Implementare analisi dettagliata del voto
     */
    private static void analizzaVotoDettagliato(double voto, ClassificazioneVoto classificazione) {
        System.out.println("\n🔍 ANALISI DETTAGLIATA:");
        
        // TODO: Analizzare posizione nel range
        double rangeMin = classificazione.getMin();
        double rangeMax = classificazione.getMax();
        double posizioneRange = (voto - rangeMin) / (rangeMax - rangeMin);
        
        System.out.printf("📏 Range categoria: %.1f - %.1f%n", rangeMin, rangeMax);
        System.out.printf("📍 Posizione nel range: %s%n", formattoPercentuale.format(posizioneRange));
        
        // TODO: Distanza dalla sufficienza
        if (voto < SOGLIA_INSUFFICIENTE) {
            double distanzaSufficienza = SOGLIA_INSUFFICIENTE - voto;
            System.out.printf("⬆️ Punti per la sufficienza: %.1f%n", distanzaSufficienza);
        } else {
            double margineSuccesso = voto - SOGLIA_INSUFFICIENTE;
            System.out.printf("✅ Margine oltre sufficienza: %.1f%n", margineSuccesso);
        }
        
        // TODO: Aggiungere altri dettagli analitici
    }
    
    /**
     * TODO 9: Implementare sistema consigli personalizzati
     */
    private static void fornsciConsigli(double voto, ClassificazioneVoto classificazione) {
        System.out.println("\n💡 CONSIGLI PERSONALIZZATI:");
        
        // TODO: Consigli basati sulla classificazione
        switch (classificazione) {
            case GRAVEMENTE_INSUFFICIENTE:
                System.out.println("🔴 ATTENZIONE: Risultato critico!");
                System.out.println("   • Rivedere completamente i fondamenti");
                System.out.println("   • Considerare lezioni di recupero");
                System.out.println("   • Dedicare più tempo allo studio");
                break;
                
            case INSUFFICIENTE:
                System.out.println("🟠 Necessario miglioramento:");
                System.out.println("   • Concentrarsi sui punti deboli");
                System.out.println("   • Aumentare le ore di studio");
                System.out.println("   • Chiedere aiuto al docente");
                break;
                
            case SUFFICIENTE:
                System.out.println("🟡 Risultato nella media:");
                System.out.println("   • Buona base, puntare a migliorare");
                System.out.println("   • Approfondire gli argomenti");
                System.out.println("   • Esercitarsi di più");
                break;
                
            case BUONO:
                System.out.println("🟢 Ottimo lavoro!");
                System.out.println("   • Risultato soddisfacente");
                System.out.println("   • Continuare con costanza");
                System.out.println("   • Puntare all'eccellenza");
                break;
                
            case DISTINTO:
                System.out.println("🔵 Risultato eccellente!");
                System.out.println("   • Preparazione molto buona");
                System.out.println("   • Mantenere il livello");
                System.out.println("   • Ambire al massimo");
                break;
                
            case OTTIMO:
                System.out.println("🟣 COMPLIMENTI! Risultato eccezionale!");
                System.out.println("   • Preparazione eccellente");
                System.out.println("   • Continua così!");
                System.out.println("   • Sei un esempio per altri");
                break;
        }
        
        // TODO: Consigli specifici basati sul voto numerico
        if (voto == 10.0) {
            System.out.println("🏆 PERFETTO! Hai raggiunto il massimo!");
        } else if (voto >= 9.5) {
            System.out.printf("🎯 Sei a %.1f punti dalla perfezione!%n", 10.0 - voto);
        }
    }
    
    /**
     * TODO 10: Implementare metodi di supporto per input/output
     */
    private static double richiedeVoto(String messaggio) {
        double voto;
        do {
            System.out.print(messaggio);
            voto = leggiDouble();
            
            if (!validaVoto(voto)) {
                System.out.println("❌ Voto non valido! Deve essere tra 0.0 e 10.0");
            }
        } while (!validaVoto(voto));
        
        return voto;
    }
    
    private static int leggiIntero(String messaggio) {
        System.out.print(messaggio);
        while (!scanner.hasNextInt()) {
            System.out.print("❌ Inserisci un numero intero valido: ");
            scanner.next();
        }
        int numero = scanner.nextInt();
        scanner.nextLine(); // Consuma newline
        return numero;
    }
    
    private static double leggiDouble() {
        while (!scanner.hasNextDouble()) {
            System.out.print("❌ Inserisci un numero valido: ");
            scanner.next();
        }
        double numero = scanner.nextDouble();
        scanner.nextLine(); // Consuma newline
        return numero;
    }
    
    private static int leggiInteroConRange(String messaggio, int min, int max) {
        int numero;
        do {
            numero = leggiIntero(messaggio);
            if (numero < min || numero > max) {
                System.out.printf("❌ Il numero deve essere tra %d e %d!%n", min, max);
            }
        } while (numero < min || numero > max);
        return numero;
    }
    
    // ==================== METODI DA IMPLEMENTARE ====================
    
    /**
     * TODO 11: Implementare tutti i metodi di analisi avanzata
     */
    
    private static void analizzaStatistiche(double[] voti, int numero) {
        // TODO: Implementare calcolo statistiche base
    }
    
    private static void analizzaDistribuzione(double[] voti, int numero) {
        // TODO: Implementare analisi distribuzione per categoria
    }
    
    private static void consigliaBasatoSuMedia(double[] voti, int numero) {
        // TODO: Implementare consigli basati su analisi multipla
    }
    
    private static void analizzaMediaClasse(String[] nomi, double[] voti, int numero) {
        // TODO: Implementare analisi completa classe
    }
    
    private static double calcolaVotoPonderato(double scritto, double orale, double pratico) {
        // TODO: Implementare calcolo ponderato
        return (scritto * 0.4) + (orale * 0.35) + (pratico * 0.25);
    }
    
    private static void analizzaRisultatoEsame(double scritto, double orale, double pratico, double finale) {
        // TODO: Implementare analisi risultato esame
    }
    
    private static void simulaMiglioramenti(double scritto, double orale, double pratico, double finale) {
        // TODO: Implementare simulazione "what-if"
    }
}
