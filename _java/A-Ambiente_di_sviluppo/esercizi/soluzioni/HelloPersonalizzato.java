/**
 * Esercizio02-HelloPersonalizzato.java
 * Soluzione dell'Esercizio 2: Hello World Personalizzato
 * 
 * Questo programma dimostra:
 * - Uso di classi per data e ora (LocalDateTime)
 * - Formattazione di date e stringhe
 * - Output formattato con emoji
 * - Organizzazione del codice in metodi
 * 
 * @author Java Essential by Example - Soluzioni
 * @version 1.0
 */

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class HelloPersonalizzato {
    
    // Costanti per la personalizzazione
    private static final String NOME = "Mario";
    private static final String COGNOME = "Rossi";
    private static final String CORSO = "Java Essential by Example";
    
    /**
     * Metodo main - punto di ingresso del programma
     */
    public static void main(String[] args) {
        // Stampa banner di benvenuto
        stampaBanner();
        
        // Stampa informazioni personali
        stampaInfoPersonali();
        
        // Stampa data e ora
        stampaDataOra();
        
        // Messaggio di chiusura
        stampaMessaggioChiusura();
    }
    
    /**
     * Stampa il banner di benvenuto
     */
    private static void stampaBanner() {
        System.out.println("🎉 Benvenuto nel mondo Java!");
        System.out.println("=" + "=".repeat(30));
    }
    
    /**
     * Stampa informazioni personali
     */
    private static void stampaInfoPersonali() {
        System.out.println("👤 Nome: " + NOME + " " + COGNOME);
        System.out.println("📚 Corso: " + CORSO);
    }
    
    /**
     * Stampa data e ora corrente
     */
    private static void stampaDataOra() {
        // Ottieni data e ora corrente
        LocalDateTime adesso = LocalDateTime.now();
        
        // Formatta data e ora
        DateTimeFormatter formatoData = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        DateTimeFormatter formatoOra = DateTimeFormatter.ofPattern("HH:mm:ss");
        
        String dataFormattata = adesso.format(formatoData);
        String oraFormattata = adesso.format(formatoOra);
        
        System.out.println("📅 Data: " + dataFormattata);
        System.out.println("⏰ Ora: " + oraFormattata);
    }
    
    /**
     * Stampa messaggio di chiusura motivazionale
     */
    private static void stampaMessaggioChiusura() {
        System.out.println("=" + "=".repeat(30));
        System.out.println("🚀 Iniziamo questa avventura di programmazione!");
        System.out.println("💻 Ogni grande sviluppatore ha iniziato da qui!");
        System.out.println("⭐ Buono studio e buona programmazione!");
        
        // Messaggio bonus basato sull'ora
        LocalDateTime adesso = LocalDateTime.now();
        int ora = adesso.getHour();
        
        String messaggioOra;
        if (ora < 12) {
            messaggioOra = "🌅 Buongiorno! Perfetto momento per imparare!";
        } else if (ora < 18) {
            messaggioOra = "☀️ Buon pomeriggio! Continua così!";
        } else {
            messaggioOra = "🌙 Buonasera! Studiare di sera è molto produttivo!";
        }
        
        System.out.println(messaggioOra);
    }
}

/*
 * SPIEGAZIONE DELLA SOLUZIONE:
 * 
 * 1. IMPORTS:
 *    - LocalDateTime: per ottenere data e ora corrente
 *    - DateTimeFormatter: per formattare data e ora
 * 
 * 2. COSTANTI:
 *    - final static per valori che non cambiano
 *    - Convenzione: MAIUSCOLO_CON_UNDERSCORE
 * 
 * 3. ORGANIZZAZIONE CODICE:
 *    - Metodi privati per organizzare le funzionalità
 *    - Ogni metodo ha una responsabilità specifica
 * 
 * 4. FORMATTAZIONE DATE:
 *    - "dd/MM/yyyy" = giorno/mese/anno (es: 05/06/2025)
 *    - "HH:mm:ss" = ora:minuti:secondi (es: 14:30:15)
 * 
 * 5. LOGICA CONDIZIONALE:
 *    - if/else per messaggi diversi basati sull'ora
 *    - Dimostra uso base delle condizioni
 * 
 * 6. STRING OPERATIONS:
 *    - "=".repeat(30) crea una stringa di 30 "="
 *    - Concatenazione con + per unire stringhe
 * 
 * COMPILAZIONE ED ESECUZIONE:
 * javac HelloPersonalizzato.java
 * java HelloPersonalizzato
 * 
 * OUTPUT ATTESO:
 * 🎉 Benvenuto nel mondo Java!
 * ==============================
 * 👤 Nome: Mario Rossi
 * 📚 Corso: Java Essential by Example
 * 📅 Data: 05/06/2025
 * ⏰ Ora: 14:30:15
 * ==============================
 * 🚀 Iniziamo questa avventura di programmazione!
 * 💻 Ogni grande sviluppatore ha iniziato da qui!
 * ⭐ Buono studio e buona programmazione!
 * ☀️ Buon pomeriggio! Continua così!
 */
