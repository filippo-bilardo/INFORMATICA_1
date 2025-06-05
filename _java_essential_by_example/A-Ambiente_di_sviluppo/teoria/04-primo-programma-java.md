# 4. Il Primo Programma Java

## 🎯 **Obiettivi del Capitolo**

- Comprendere la struttura di base di un programma Java
- Analizzare riga per riga il codice "Hello World"
- Imparare il processo di compilazione ed esecuzione
- Personalizzare il primo programma con input/output

**⏱️ Tempo stimato:** 30-45 minuti

---

## 📝 **Anatomia di un Programma Java**

### **Il Classico "Hello World"**

```java
/**
 * Il mio primo programma Java
 * Dimostra la struttura base di una classe Java
 * 
 * @author Il tuo nome
 * @version 1.0
 * @since 2025-06-05
 */
public class HelloWorld {
    
    /**
     * Metodo principale - punto di ingresso del programma
     * Viene eseguito quando avvii il programma
     * 
     * @param args argomenti passati da linea di comando
     */
    public static void main(String[] args) {
        // Stampa un messaggio nella console
        System.out.println("Hello, World!");
        System.out.println("Benvenuto in Java! 🚀");
    }
}
```

### **Analisi Riga per Riga**

#### **1. Commenti Javadoc (righe 1-7)**
```java
/**
 * Il mio primo programma Java
 * @author Il tuo nome
 * @version 1.0
 */
```
- `/**` e `*/` delimitano commenti di documentazione
- `@author`, `@version`, `@since` sono **tag Javadoc**
- Generano documentazione HTML automatica
- **Best Practice:** Sempre documentare le classi pubbliche

#### **2. Dichiarazione della Classe (riga 8)**
```java
public class HelloWorld {
```
- `public`: la classe è accessibile da altri package
- `class`: parola chiave per definire una classe
- `HelloWorld`: nome della classe (deve iniziare con maiuscola)
- `{`: inizio del corpo della classe

#### **3. Metodo main (righe 15-18)**
```java
public static void main(String[] args) {
```
- `public`: accessibile dall'esterno
- `static`: appartiene alla classe, non a un'istanza
- `void`: non restituisce nessun valore
- `main`: nome speciale - punto di ingresso del programma
- `String[] args`: parametri da linea di comando

#### **4. Istruzioni (righe 16-17)**
```java
System.out.println("Hello, World!");
System.out.println("Benvenuto in Java! 🚀");
```
- `System.out`: oggetto per output sulla console
- `println()`: metodo che stampa e va a capo
- `"..."`: stringa letterale
- `;`: ogni istruzione termina con punto e virgola

#### **5. Chiusura delle Parentesi Graffe**
```java
    }  // Fine metodo main
}      // Fine classe HelloWorld
```

---

## ⚙️ **Processo di Compilazione ed Esecuzione**

### **1. Compilazione (javac)**

```bash
# Compila il file sorgente .java in bytecode .class
javac HelloWorld.java

# Verifica che sia stato creato il file .class
ls -la
# Output: HelloWorld.class
```

**Cosa succede:**
- `javac` (Java Compiler) legge `HelloWorld.java`
- Controlla sintassi e semantica
- Genera `HelloWorld.class` (bytecode)
- Il bytecode è platform-independent

### **2. Esecuzione (java)**

```bash
# Esegue il bytecode sulla JVM
java HelloWorld

# Output:
# Hello, World!
# Benvenuto in Java! 🚀
```

**Cosa succede:**
- `java` avvia la Java Virtual Machine (JVM)
- Carica la classe `HelloWorld`
- Cerca il metodo `main(String[] args)`
- Esegue le istruzioni nel metodo main

### **Diagramma del Processo**

```
HelloWorld.java  →  [javac]  →  HelloWorld.class  →  [java]  →  Output
(sorgente)          (compiler)   (bytecode)         (JVM)      (console)
```

---

## 🎨 **Variazioni del Programma Base**

### **Versione con Variabili**

```java
/**
 * Hello World con variabili e calcoli
 */
public class HelloWorldVariabili {
    public static void main(String[] args) {
        // Dichiarazione e inizializzazione variabili
        String nome = "Mario";
        String cognome = "Rossi";
        int eta = 25;
        double altezza = 1.75;
        
        // Output formattato
        System.out.println("=== INFORMAZIONI PERSONALI ===");
        System.out.println("Nome completo: " + nome + " " + cognome);
        System.out.println("Età: " + eta + " anni");
        System.out.println("Altezza: " + altezza + " metri");
        
        // Calcoli semplici
        int annoNascita = 2025 - eta;
        System.out.println("Anno di nascita: " + annoNascita);
        
        // Concatenazione vs addizione
        System.out.println("Test concatenazione: " + 5 + 3);      // "53"
        System.out.println("Test addizione: " + (5 + 3));         // "8"
    }
}
```

### **Versione con Input Utente**

```java
import java.util.Scanner;  // Import necessario per input

/**
 * Hello World interattivo con input utente
 */
public class HelloWorldInterattivo {
    public static void main(String[] args) {
        // Crea oggetto Scanner per leggere input
        Scanner input = new Scanner(System.in);
        
        // Banner di benvenuto
        System.out.println("╔════════════════════════════════╗");
        System.out.println("║     BENVENUTO IN JAVA! 🚀      ║");
        System.out.println("╚════════════════════════════════╝");
        System.out.println();
        
        // Richiedi informazioni utente
        System.out.print("Come ti chiami? ");
        String nome = input.nextLine();
        
        System.out.print("Quanti anni hai? ");
        int eta = input.nextInt();
        
        System.out.print("Qual è la tua città? ");
        input.nextLine();  // Consuma il newline rimasto
        String citta = input.nextLine();
        
        // Elabora e mostra risultati
        System.out.println("\n" + "=".repeat(40));
        System.out.println("Ciao " + nome + "! 👋");
        System.out.println("Hai " + eta + " anni e vivi a " + citta);
        
        if (eta >= 18) {
            System.out.println("Sei maggiorenne! 🎉");
        } else {
            System.out.println("Sei ancora minorenne 👶");
        }
        
        System.out.println("Benvenuto nel mondo della programmazione Java!");
        System.out.println("=".repeat(40));
        
        // Chiudi lo Scanner
        input.close();
    }
}
```

### **Versione con Metodi Personalizzati**

```java
/**
 * Hello World con metodi personalizzati
 * Dimostra organizzazione del codice in metodi
 */
public class HelloWorldMetodi {
    
    public static void main(String[] args) {
        // Chiamata ai metodi personalizzati
        stampaBanner();
        mostraInformazioniJava();
        calcolaEsempi();
        stampaFooter();
    }
    
    /**
     * Stampa un banner di benvenuto colorato
     */
    public static void stampaBanner() {
        System.out.println("╔══════════════════════════════════════╗");
        System.out.println("║           HELLO JAVA WORLD!         ║");
        System.out.println("║              🌟☕🚀                  ║");
        System.out.println("╚══════════════════════════════════════╝");
        System.out.println();
    }
    
    /**
     * Mostra informazioni sulla versione Java
     */
    public static void mostraInformazioniJava() {
        System.out.println("📋 INFORMAZIONI SISTEMA:");
        System.out.println("   Java Version: " + System.getProperty("java.version"));
        System.out.println("   Java Vendor: " + System.getProperty("java.vendor"));
        System.out.println("   OS: " + System.getProperty("os.name"));
        System.out.println("   User: " + System.getProperty("user.name"));
        System.out.println();
    }
    
    /**
     * Dimostra calcoli matematici base
     */
    public static void calcolaEsempi() {
        System.out.println("🧮 ESEMPI DI CALCOLO:");
        
        // Operazioni matematiche
        int a = 15;
        int b = 4;
        
        System.out.println("   a = " + a + ", b = " + b);
        System.out.println("   a + b = " + (a + b));
        System.out.println("   a - b = " + (a - b));
        System.out.println("   a * b = " + (a * b));
        System.out.println("   a / b = " + (a / b));
        System.out.println("   a % b = " + (a % b) + " (resto divisione)");
        
        // Operazioni con decimali
        double x = 10.5;
        double y = 3.2;
        System.out.printf("   %.1f + %.1f = %.1f%n", x, y, (x + y));
        System.out.println();
    }
    
    /**
     * Stampa footer con messaggio di chiusura
     */
    public static void stampaFooter() {
        System.out.println("✅ Primo programma Java eseguito con successo!");
        System.out.println("🚀 Sei pronto per il prossimo livello!");
        System.out.println("\n" + "=".repeat(50));
    }
}
```

---

## 🔧 **Errori Comuni e Soluzioni**

### **1. Errore: "public class X must be declared in a file named X.java"**

**❌ Problema:**
```java
// File: MioFile.java
public class ProgrammaTest {  // Nome classe diverso dal file!
    public static void main(String[] args) {
        System.out.println("Hello");
    }
}
```

**✅ Soluzione:**
```java
// File: ProgrammaTest.java
public class ProgrammaTest {  // Nome classe = nome file
    public static void main(String[] args) {
        System.out.println("Hello");
    }
}
```

### **2. Errore: "Cannot find symbol"**

**❌ Problema:**
```java
public class Test {
    public static void main(String[] args) {
        System.out.println(messaggio);  // Variabile non dichiarata!
    }
}
```

**✅ Soluzione:**
```java
public class Test {
    public static void main(String[] args) {
        String messaggio = "Hello World";  // Dichiara la variabile
        System.out.println(messaggio);
    }
}
```

### **3. Errore: Missing ";"**

**❌ Problema:**
```java
public class Test {
    public static void main(String[] args) {
        System.out.println("Hello")  // Manca punto e virgola!
        System.out.println("World")  // Manca punto e virgola!
    }
}
```

**✅ Soluzione:**
```java
public class Test {
    public static void main(String[] args) {
        System.out.println("Hello");  // Punto e virgola aggiunto
        System.out.println("World");  // Punto e virgola aggiunto
    }
}
```

### **4. Errore di Runtime: "Could not find or load main class"**

**❌ Cause possibili:**
- Nome file diverso dal nome classe
- File .class non presente (non compilato)
- Errore di CLASSPATH

**✅ Soluzioni:**
```bash
# 1. Ricompila
javac HelloWorld.java

# 2. Verifica file .class presente
ls *.class

# 3. Esegui con nome classe corretto
java HelloWorld  # NON HelloWorld.java
```

---

## 🎯 **Esercizi Pratici**

### **Esercizio 1: Personalizza il Saluto**
Modifica HelloWorld per:
- Chiedere nome e cognome dell'utente
- Mostrare un saluto personalizzato
- Calcolare l'anno di nascita dall'età

**Starter Code:**
```java
import java.util.Scanner;

public class SalutoPersonalizzato {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        // TODO: Implementa la logica
        
        input.close();
    }
}
```

### **Esercizio 2: Calcolatrice Base**
Crea un programma che:
- Chiede due numeri all'utente
- Mostra il risultato di tutte le operazioni base (+, -, *, /, %)

### **Esercizio 3: Informazioni Sistema**
Crea un programma che mostra:
- Tutte le proprietà di sistema Java
- Data e ora corrente
- Informazioni sulla JVM

**Hint:** Usa `System.getProperty()` e `java.time.LocalDateTime`

---

## 📚 **Concetti Chiave da Ricordare**

### **✅ Struttura Program Java**
1. **Classe pubblica** con nome = nome file
2. **Metodo main** come punto di ingresso
3. **Importazioni** all'inizio del file
4. **Commenti** per documentazione

### **✅ Naming Conventions**
- **Classi:** PascalCase (`HelloWorld`, `MiaClasse`)
- **Metodi:** camelCase (`main`, `stampaMessaggio`)
- **Variabili:** camelCase (`nomeUtente`, `numeroTelefono`)
- **Costanti:** UPPER_CASE (`MAX_SIZE`, `DEFAULT_VALUE`)

### **✅ Compilazione ed Esecuzione**
```bash
javac NomeClasse.java    # Compila → crea .class
java NomeClasse          # Esegue (senza .java)
```

### **✅ Output Formattato**
```java
// Concatenazione stringhe
System.out.println("Valore: " + variabile);

// Printf stile C
System.out.printf("Nome: %s, Età: %d%n", nome, eta);

// Text blocks (Java 15+)
String messaggio = """
    Messaggio
    multiriga
    """;
```

---

## ✅ **Checklist di Completamento**

Prima di procedere, assicurati di saper:

- [ ] ✅ Creare una classe Java con metodo main
- [ ] ✅ Compilare con `javac` ed eseguire con `java`
- [ ] ✅ Usare `System.out.println()` per output
- [ ] ✅ Dichiarare e usare variabili base
- [ ] ✅ Gestire input utente con Scanner
- [ ] ✅ Organizzare codice in metodi separati
- [ ] ✅ Riconoscere e correggere errori comuni
- [ ] ✅ Seguire le naming conventions Java

---

## 🧭 **Navigazione**

- [⬅️ Capitolo Precedente: Installazione IDE](03-installazione-ide.md)
- [➡️ Modulo Successivo: Problemi ed Algoritmi](../../B-Problemi_ed_algoritmi/README.md)
- [🏠 Torna al Modulo A](../README.md)
- [📑 Indice Generale](../../README.md)

---

*Congratulazioni! Hai completato il Modulo A. Ora sei pronto per esplorare il mondo degli algoritmi nel [Modulo B](../../B-Problemi_ed_algoritmi/README.md)! 🚀*
