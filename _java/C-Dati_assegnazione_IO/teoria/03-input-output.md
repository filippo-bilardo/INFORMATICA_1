# Input e Output in Java

## 🎯 Obiettivi di Apprendimento

Alla fine di questa sezione, saprai:
- Utilizzare Scanner per l'input da tastiera
- Gestire diversi tipi di input (numeri, stringhe, caratteri)
- Formattare l'output con System.out e printf
- Gestire errori di input/output
- Lavorare con file di testo (base)

---

## 📥 Input da Tastiera - Classe Scanner

### Importazione e Creazione
```java
import java.util.Scanner;

public class InputExample {
    public static void main(String[] args) {
        // Creazione dello scanner collegato all'input standard (tastiera)
        Scanner scanner = new Scanner(System.in);
        
        // Non dimenticare di chiudere lo scanner alla fine
        scanner.close();
    }
}
```

### Lettura di Tipi Primitivi

#### Numeri Interi
```java
Scanner scanner = new Scanner(System.in);

System.out.print("Inserisci la tua età: ");
int eta = scanner.nextInt();

System.out.print("Inserisci un numero lungo: ");
long numeroLungo = scanner.nextLong();

System.out.print("Inserisci un numero byte: ");
byte numeroByte = scanner.nextByte();

System.out.print("Inserisci un numero short: ");
short numeroShort = scanner.nextShort();
```

#### Numeri Decimali
```java
System.out.print("Inserisci la tua altezza (m): ");
double altezza = scanner.nextDouble();

System.out.print("Inserisci il prezzo: ");
float prezzo = scanner.nextFloat();

// ⚠️ Attenzione alle impostazioni locali!
// In Italia si usa la virgola: 1,75
// In sistemi US si usa il punto: 1.75
```

#### Altri Tipi
```java
System.out.print("Sei maggiorenne? (true/false): ");
boolean maggiorenne = scanner.nextBoolean();

// Per caratteri singoli (non esiste nextChar())
System.out.print("Inserisci un carattere: ");
char carattere = scanner.next().charAt(0);
```

### Lettura di Stringhe

```java
Scanner scanner = new Scanner(System.in);

// next() - legge fino al primo spazio
System.out.print("Inserisci il tuo nome: ");
String nome = scanner.next();           // "Mario" (se input è "Mario Rossi")

// nextLine() - legge l'intera riga
System.out.print("Inserisci nome e cognome: ");
String nomeCompleto = scanner.nextLine(); // "Mario Rossi"

// ⚠️ Problema comune: mix di nextInt() e nextLine()
System.out.print("Età: ");
int eta = scanner.nextInt();
scanner.nextLine(); // Consuma il \n rimasto nel buffer!

System.out.print("Nome completo: ");
String nome = scanner.nextLine(); // Ora funziona correttamente
```

### Controllo dell'Input Disponibile
```java
Scanner scanner = new Scanner(System.in);

// Verifica se ci sono dati del tipo richiesto
if (scanner.hasNextInt()) {
    int numero = scanner.nextInt();
    System.out.println("Numero inserito: " + numero);
} else {
    System.out.println("Input non valido per un numero intero");
    String input = scanner.next(); // Consuma l'input invalido
}

// Altri metodi has...()
boolean hasDouble = scanner.hasNextDouble();
boolean hasBoolean = scanner.hasNextBoolean();
boolean hasNext = scanner.hasNext();        // C'è qualche token?
boolean hasNextLine = scanner.hasNextLine(); // C'è un'altra riga?
```

---

## 📤 Output Formattato

### System.out - Metodi Base
```java
// println() - stampa e va a capo
System.out.println("Ciao mondo!");
System.out.println(42);
System.out.println(true);

// print() - stampa senza andare a capo
System.out.print("Nome: ");
System.out.print("Mario");
System.out.print(" ");
System.out.println("Rossi"); // Risultato: "Nome: Mario Rossi"

// printf() - output formattato
System.out.printf("Nome: %s, Età: %d%n", "Mario", 25);
```

### printf() - Formattazione Avanzata

#### Specificatori di Formato Base
```java
String nome = "Alice";
int eta = 28;
double altezza = 1.65;
boolean sposata = true;

// %s - String
System.out.printf("Nome: %s%n", nome);

// %d - decimale (int, long, byte, short)
System.out.printf("Età: %d anni%n", eta);

// %f - float/double
System.out.printf("Altezza: %f m%n", altezza);        // 1.650000 m
System.out.printf("Altezza: %.2f m%n", altezza);      // 1.65 m

// %b - boolean
System.out.printf("Sposata: %b%n", sposata);

// %c - carattere
System.out.printf("Iniziale: %c%n", nome.charAt(0));  // A

// %% - carattere % letterale
System.out.printf("Sconto del 20%%");                 // Sconto del 20%
```

#### Controllo Larghezza e Allineamento
```java
// Larghezza minima
System.out.printf("|%10s|%n", "ciao");      // |      ciao|
System.out.printf("|%-10s|%n", "ciao");     // |ciao      | (allineato a sinistra)

// Numeri con larghezza
System.out.printf("|%5d|%n", 42);           // |   42|
System.out.printf("|%05d|%n", 42);          // |00042| (padding con zeri)

// Decimali
System.out.printf("|%8.2f|%n", 123.456);    // |  123.46|
System.out.printf("|%-8.2f|%n", 123.456);   // |123.46  |
```

#### Formati Numerici Speciali
```java
int numero = 255;

System.out.printf("Decimale: %d%n", numero);        // 255
System.out.printf("Esadecimale: %x%n", numero);     // ff
System.out.printf("Esadecimale maiuscolo: %X%n", numero); // FF
System.out.printf("Ottale: %o%n", numero);          // 377

// Notazione scientifica
double grande = 1234567.89;
System.out.printf("Scientifico: %e%n", grande);     // 1.234568e+06
System.out.printf("Scientifico: %E%n", grande);     // 1.234568E+06

// Formato più compatto tra f ed e
System.out.printf("Compatto: %g%n", grande);        // 1.23457e+06
System.out.printf("Compatto: %g%n", 123.45);        // 123.450
```

#### Esempio Completo di Formattazione
```java
public class FormattazioneCompleta {
    public static void main(String[] args) {
        // Dati di esempio
        String[] nomi = {"Alice", "Bob", "Charlie"};
        int[] eta = {25, 30, 35};
        double[] stipendi = {35000.50, 42000.75, 38500.25};
        
        // Intestazione tabella
        System.out.printf("%-10s %5s %12s%n", "Nome", "Età", "Stipendio");
        System.out.println("-----------------------------");
        
        // Righe dati
        for (int i = 0; i < nomi.length; i++) {
            System.out.printf("%-10s %5d %12.2f€%n", 
                            nomi[i], eta[i], stipendi[i]);
        }
    }
}

/* Output:
Nome       Età    Stipendio
-----------------------------
Alice       25    35000.50€
Bob         30    42000.75€
Charlie     35    38500.25€
*/
```

---

## 🛠️ Gestione degli Errori di Input

### InputMismatchException
```java
import java.util.InputMismatchException;
import java.util.Scanner;

public class GestioneErrori {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numero = 0;
        boolean inputValido = false;
        
        while (!inputValido) {
            try {
                System.out.print("Inserisci un numero intero: ");
                numero = scanner.nextInt();
                inputValido = true;
            } catch (InputMismatchException e) {
                System.out.println("Errore: devi inserire un numero intero!");
                scanner.next(); // Consuma l'input errato
            }
        }
        
        System.out.println("Numero inserito: " + numero);
        scanner.close();
    }
}
```

### Validazione Input con Metodi Personalizzati
```java
public class ValidazioneInput {
    private static Scanner scanner = new Scanner(System.in);
    
    public static int leggiIntero(String messaggio, int min, int max) {
        int valore;
        while (true) {
            System.out.print(messaggio);
            if (scanner.hasNextInt()) {
                valore = scanner.nextInt();
                if (valore >= min && valore <= max) {
                    return valore;
                } else {
                    System.out.printf("Errore: inserisci un valore tra %d e %d%n", min, max);
                }
            } else {
                System.out.println("Errore: inserisci un numero intero valido");
                scanner.next(); // Consuma input invalido
            }
        }
    }
    
    public static double leggiDouble(String messaggio) {
        while (true) {
            System.out.print(messaggio);
            if (scanner.hasNextDouble()) {
                return scanner.nextDouble();
            } else {
                System.out.println("Errore: inserisci un numero decimale valido");
                scanner.next();
            }
        }
    }
    
    public static String leggiStringa(String messaggio, boolean nonVuota) {
        String input;
        while (true) {
            System.out.print(messaggio);
            input = scanner.nextLine().trim();
            if (!nonVuota || !input.isEmpty()) {
                return input;
            } else {
                System.out.println("Errore: la stringa non può essere vuota");
            }
        }
    }
    
    public static void main(String[] args) {
        int eta = leggiIntero("Inserisci la tua età (0-120): ", 0, 120);
        double altezza = leggiDouble("Inserisci la tua altezza (m): ");
        String nome = leggiStringa("Inserisci il tuo nome: ", true);
        
        System.out.printf("%nDati inseriti:%n");
        System.out.printf("Nome: %s%n", nome);
        System.out.printf("Età: %d anni%n", eta);
        System.out.printf("Altezza: %.2f m%n", altezza);
        
        scanner.close();
    }
}
```

---

## 📁 Input/Output con File (Introduzione)

### Lettura da File
```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class LetturaFile {
    public static void main(String[] args) {
        try {
            File file = new File("dati.txt");
            Scanner fileScanner = new Scanner(file);
            
            while (fileScanner.hasNextLine()) {
                String riga = fileScanner.nextLine();
                System.out.println("Letto: " + riga);
            }
            
            fileScanner.close();
            
        } catch (FileNotFoundException e) {
            System.out.println("File non trovato: " + e.getMessage());
        }
    }
}
```

### Scrittura su File
```java
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class ScritturaFile {
    public static void main(String[] args) {
        try {
            PrintWriter writer = new PrintWriter(new FileWriter("output.txt"));
            
            writer.println("Prima riga");
            writer.printf("Numero: %d%n", 42);
            writer.printf("Decimale: %.2f%n", 3.14159);
            
            writer.close();
            System.out.println("File scritto con successo!");
            
        } catch (IOException e) {
            System.out.println("Errore nella scrittura: " + e.getMessage());
        }
    }
}
```

---

## 🎨 Best Practices per I/O

### 1. **Gestione delle Risorse**
```java
// ✅ Usa try-with-resources (Java 7+)
try (Scanner scanner = new Scanner(System.in)) {
    String input = scanner.nextLine();
    // Scanner si chiude automaticamente
}

// ✅ Per file
try (Scanner fileScanner = new Scanner(new File("data.txt"));
     PrintWriter writer = new PrintWriter("output.txt")) {
    
    // Lavora con scanner e writer
    // Si chiudono automaticamente
}
```

### 2. **Validazione Input Robusta**
```java
public class InputRobust {
    public static String leggiEmail() {
        Scanner scanner = new Scanner(System.in);
        String email;
        
        while (true) {
            System.out.print("Inserisci email: ");
            email = scanner.nextLine().trim();
            
            if (email.contains("@") && email.contains(".")) {
                return email;
            } else {
                System.out.println("Email non valida. Riprova.");
            }
        }
    }
    
    public static int leggiEta() {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.print("Inserisci età (0-150): ");
            
            if (scanner.hasNextInt()) {
                int eta = scanner.nextInt();
                if (eta >= 0 && eta <= 150) {
                    return eta;
                }
                System.out.println("Età deve essere tra 0 e 150");
            } else {
                System.out.println("Inserisci un numero valido");
                scanner.next(); // Consuma input invalido
            }
        }
    }
}
```

### 3. **Formattazione Consistente**
```java
public class FormattazioneConsistente {
    // Costanti per formattazione
    private static final String FORMATO_PREZZO = "%.2f€";
    private static final String FORMATO_DATA = "%02d/%02d/%04d";
    private static final String SEPARATORE = "=" .repeat(50);
    
    public static void stampaPrezzo(double prezzo) {
        System.out.printf(FORMATO_PREZZO + "%n", prezzo);
    }
    
    public static void stampaData(int giorno, int mese, int anno) {
        System.out.printf(FORMATO_DATA + "%n", giorno, mese, anno);
    }
    
    public static void stampaSeparatore() {
        System.out.println(SEPARATORE);
    }
}
```

### 4. **Messaggi Utente Chiari**
```java
// ✅ Messaggi descrittivi
System.out.print("Inserisci la tua età (numero intero da 0 a 120): ");
System.out.println("Errore: l'età deve essere un numero tra 0 e 120");

// ✅ Feedback positivo
System.out.println("✓ Dati salvati correttamente!");
System.out.println("✓ Email valida inserita");

// ❌ Messaggi criptici
System.out.print("Input: ");
System.out.println("Error");
```

---

## 🧪 Esempi Pratici Completi

### Esempio 1: Calcolatrice Semplice
```java
import java.util.Scanner;

public class CalcolatriceSemplice {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("=== CALCOLATRICE SEMPLICE ===");
        
        try {
            System.out.print("Primo numero: ");
            double num1 = scanner.nextDouble();
            
            System.out.print("Operatore (+, -, *, /): ");
            char operatore = scanner.next().charAt(0);
            
            System.out.print("Secondo numero: ");
            double num2 = scanner.nextDouble();
            
            double risultato = 0;
            boolean operazioneValida = true;
            
            switch (operatore) {
                case '+':
                    risultato = num1 + num2;
                    break;
                case '-':
                    risultato = num1 - num2;
                    break;
                case '*':
                    risultato = num1 * num2;
                    break;
                case '/':
                    if (num2 != 0) {
                        risultato = num1 / num2;
                    } else {
                        System.out.println("Errore: divisione per zero!");
                        operazioneValida = false;
                    }
                    break;
                default:
                    System.out.println("Operatore non valido!");
                    operazioneValida = false;
            }
            
            if (operazioneValida) {
                System.out.printf("Risultato: %.2f %c %.2f = %.2f%n", 
                                num1, operatore, num2, risultato);
            }
            
        } catch (Exception e) {
            System.out.println("Errore nell'input: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
```

### Esempio 2: Registro Studenti
```java
import java.util.ArrayList;
import java.util.Scanner;

public class RegistroStudenti {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<String> nomi = new ArrayList<>();
        ArrayList<Double> voti = new ArrayList<>();
        
        System.out.println("=== REGISTRO STUDENTI ===");
        System.out.println("Inserisci i dati degli studenti (nome vuoto per terminare)");
        
        while (true) {
            System.out.print("Nome studente: ");
            String nome = scanner.nextLine().trim();
            
            if (nome.isEmpty()) {
                break;
            }
            
            double voto = 0;
            boolean votoValido = false;
            
            while (!votoValido) {
                System.out.print("Voto (0-10): ");
                if (scanner.hasNextDouble()) {
                    voto = scanner.nextDouble();
                    if (voto >= 0 && voto <= 10) {
                        votoValido = true;
                    } else {
                        System.out.println("Il voto deve essere tra 0 e 10");
                    }
                } else {
                    System.out.println("Inserisci un numero valido");
                    scanner.next();
                }
            }
            scanner.nextLine(); // Consuma il newline
            
            nomi.add(nome);
            voti.add(voto);
            
            System.out.printf("✓ Aggiunto: %s - %.1f%n%n", nome, voto);
        }
        
        // Stampa riepilogo
        if (!nomi.isEmpty()) {
            System.out.println("\n=== RIEPILOGO STUDENTI ===");
            System.out.printf("%-20s %8s %10s%n", "Nome", "Voto", "Esito");
            System.out.println("-".repeat(40));
            
            double sommaVoti = 0;
            for (int i = 0; i < nomi.size(); i++) {
                String nome = nomi.get(i);
                double voto = voti.get(i);
                String esito = voto >= 6 ? "Promosso" : "Bocciato";
                
                System.out.printf("%-20s %8.1f %10s%n", nome, voto, esito);
                sommaVoti += voto;
            }
            
            double media = sommaVoti / nomi.size();
            System.out.println("-".repeat(40));
            System.out.printf("Media classe: %.2f%n", media);
        }
        
        scanner.close();
    }
}
```

---

## ❓ Quiz di Autovalutazione

1. **Quale metodo Scanner useresti per leggere una riga completa?**
   - a) `next()`
   - b) `nextLine()`
   - c) `nextString()`
   - d) `readLine()`

2. **Cosa stampa questo codice?**
   ```java
   System.out.printf("%5d", 42);
   ```

3. **Come gestiresti l'input "abc" quando il programma si aspetta un int?**

4. **Qual è la differenza tra `print()` e `println()`?**

---

## 🚀 Prossimi Passi

Nel prossimo modulo vedremo:
- **Strutture Condizionali** - if, else, switch
- **Operatori Logici Avanzati** - Combinazioni complesse
- **Cicli** - for, while, do-while

---

## 🔗 Link Utili

- [Scanner Class Documentation](https://docs.oracle.com/javase/8/docs/api/java/util/Scanner.html)
- [printf Format Specifiers](https://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html)
- [Java I/O Tutorial](https://docs.oracle.com/javase/tutorial/essential/io/)
