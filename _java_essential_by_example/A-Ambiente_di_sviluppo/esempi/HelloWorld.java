/**
 * HelloWorld.java - Il classico primo programma Java
 * 
 * Questo è il tradizionale "Hello World" che introduce:
 * - Struttura base di una classe Java
 * - Il metodo main come punto di ingresso
 * - Output su console con System.out.println
 * 
 * @author Java Essential by Example
 * @version 1.0
 */
public class HelloWorld {
    
    /**
     * Metodo main - punto di ingresso dell'applicazione
     * Viene chiamato automaticamente dalla JVM quando si esegue il programma
     * 
     * @param args Array di stringhe contenente gli argomenti da linea di comando
     */
    public static void main(String[] args) {
        // Stampa il messaggio di saluto sulla console
        System.out.println("Hello, World!");
        
        // Esempi di output aggiuntivi
        System.out.println("Benvenuto nel mondo Java!");
        System.out.println("Questo è il mio primo programma Java.");
        
        // Stampa informazioni sul sistema
        System.out.println("Versione Java: " + System.getProperty("java.version"));
        System.out.println("Sistema operativo: " + System.getProperty("os.name"));
    }
}

/*
 * ISTRUZIONI PER COMPILARE ED ESEGUIRE:
 * 
 * 1. Salvare questo file come "HelloWorld.java" 
 *    IMPORTANTE: Il nome del file DEVE essere identico al nome della classe!
 * 
 * 2. Aprire terminale/prompt dei comandi nella cartella contenente il file
 * 
 * 3. Compilare con: javac HelloWorld.java
 *    Questo creerà un file HelloWorld.class
 * 
 * 4. Eseguire con: java HelloWorld
 *    NON includere l'estensione .class nel comando!
 * 
 * 5. Dovresti vedere l'output del programma nella console
 */
