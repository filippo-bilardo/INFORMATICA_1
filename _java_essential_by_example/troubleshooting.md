# 🔧 Troubleshooting - Risoluzione Problemi Comuni

## 🚨 **Problemi di Installazione Java**

### **Problema: "java command not found"**
**Sintomi:** Il terminale non riconosce il comando `java` o `javac`

**Soluzioni:**
```bash
# 1. Verifica installazione
java -version
javac -version

# 2. Controlla JAVA_HOME (Linux/Mac)
echo $JAVA_HOME
export JAVA_HOME=/path/to/your/java

# 3. Controlla JAVA_HOME (Windows)
echo %JAVA_HOME%
set JAVA_HOME=C:\path\to\your\java

# 4. Aggiorna PATH
export PATH=$JAVA_HOME/bin:$PATH  # Linux/Mac
set PATH=%JAVA_HOME%\bin;%PATH%   # Windows
```

### **Problema: "Unsupported major.minor version"**
**Sintomi:** Errore durante l'esecuzione di file .class

**Causa:** Tentativo di eseguire codice compilato con una versione Java più recente

**Soluzione:**
1. Verifica versioni Java:
   ```bash
   java -version    # JRE version
   javac -version   # JDK version
   ```
2. Ricompila il codice con la versione corrente
3. Aggiorna Java se necessario

---

## 🖥️ **Problemi con IDE**

### **IntelliJ IDEA**

**Problema: "Project SDK not defined"**
```
1. File → Project Structure → Project
2. Project SDK → Add SDK → Download JDK
3. Seleziona versione Java (11, 17, o 21)
4. Apply → OK
```

**Problema: "Cannot resolve symbol"**
```
1. File → Invalidate Caches → Invalidate and Restart
2. Verifica import necessari
3. Controlla Project Structure → Modules
```

### **VS Code**

**Problema: Estensione Java non funziona**
```
1. Installa "Extension Pack for Java"
2. Ctrl+Shift+P → "Java: Reload Projects"
3. Verifica JAVA_HOME nelle settings
```

### **Eclipse**

**Problema: "Build path is incomplete"**
```
1. Right-click project → Properties
2. Java Build Path → Libraries
3. Add Library → JRE System Library
```

---

## 💻 **Errori di Compilazione Comuni**

### **"public class X must be declared in a file named X.java"**
**Causa:** Nome classe non corrisponde al nome file

**Esempio Problema:**
```java
// File: MioFile.java
public class AltroNome {  // ❌ ERRORE!
    public static void main(String[] args) {
        System.out.println("Hello");
    }
}
```

**Soluzione:**
```java
// File: AltroNome.java
public class AltroNome {  // ✅ CORRETTO
    public static void main(String[] args) {
        System.out.println("Hello");
    }
}
```

### **"Cannot find symbol"**
**Cause comuni:**
1. Variabile non dichiarata
2. Errore di spelling
3. Import mancante
4. Scope errato

**Esempi e Soluzioni:**
```java
// ❌ Variabile non dichiarata
public class Test {
    public static void main(String[] args) {
        System.out.println(messaggio);  // ERRORE!
    }
}

// ✅ Variabile dichiarata
public class Test {
    public static void main(String[] args) {
        String messaggio = "Hello World";
        System.out.println(messaggio);  // CORRETTO
    }
}

// ❌ Import mancante
public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);  // ERRORE!
    }
}

// ✅ Con import
import java.util.Scanner;
public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);  // CORRETTO
    }
}
```

### **"Missing return statement"**
**Causa:** Metodo con tipo di ritorno non-void senza return

```java
// ❌ Manca return
public int somma(int a, int b) {
    int risultato = a + b;
    // Manca return!
}

// ✅ Con return
public int somma(int a, int b) {
    int risultato = a + b;
    return risultato;
}
```

---

## ⚠️ **Errori Runtime Frequenti**

### **NullPointerException**
**Il più comune degli errori runtime**

**Esempio Problema:**
```java
String nome = null;
int lunghezza = nome.length();  // ❌ NullPointerException!
```

**Soluzioni:**
```java
// ✅ Controllo null
String nome = null;
if (nome != null) {
    int lunghezza = nome.length();
}

// ✅ Inizializzazione
String nome = "";  // o altro valore default
int lunghezza = nome.length();

// ✅ Operatore ternario
String nome = null;
int lunghezza = (nome != null) ? nome.length() : 0;
```

### **ArrayIndexOutOfBoundsException**
**Tentativo di accesso a indice non valido**

```java
// ❌ Indice oltre il limite
int[] numeri = {1, 2, 3};
System.out.println(numeri[5]);  // ERRORE! Array ha solo 3 elementi

// ✅ Controllo indici
int[] numeri = {1, 2, 3};
int indice = 5;
if (indice >= 0 && indice < numeri.length) {
    System.out.println(numeri[indice]);
} else {
    System.out.println("Indice non valido");
}
```

### **NumberFormatException**
**Conversione stringa-numero non valida**

```java
// ❌ Stringa non numerica
String testo = "abc";
int numero = Integer.parseInt(testo);  // ERRORE!

// ✅ Con gestione errore
String testo = "abc";
try {
    int numero = Integer.parseInt(testo);
    System.out.println(numero);
} catch (NumberFormatException e) {
    System.out.println("Formato numero non valido: " + testo);
}
```

---

## 🔄 **Problemi di Logica Comuni**

### **Loop Infiniti**
```java
// ❌ Loop infinito
int i = 0;
while (i < 10) {
    System.out.println(i);
    // Manca i++!
}

// ✅ Corretto
int i = 0;
while (i < 10) {
    System.out.println(i);
    i++;  // Incremento essenziale
}
```

### **Condizioni Errate**
```java
// ❌ Assegnazione invece di confronto
int x = 5;
if (x = 3) {  // ERRORE! Assegnazione, non confronto
    System.out.println("x è 3");
}

// ✅ Confronto corretto
int x = 5;
if (x == 3) {  // Confronto con ==
    System.out.println("x è 3");
}
```

---

## 🚀 **Tips per il Debug**

### **1. Uso di System.out.println()**
```java
public void metodoComplesso(int x, int y) {
    System.out.println("Debug: x=" + x + ", y=" + y);  // ← Debug print
    
    int risultato = x * y + 5;
    System.out.println("Debug: risultato=" + risultato);  // ← Debug print
    
    if (risultato > 10) {
        System.out.println("Debug: risultato > 10");  // ← Debug print
        // fare qualcosa
    }
}
```

### **2. Breakpoint nell'IDE**
- **IntelliJ/Eclipse:** Click sul margine sinistro della riga
- **VS Code:** F9 sulla riga desiderata
- Esegui in modalità Debug (icona bug)

### **3. Step-by-Step Execution**
- **F8:** Step Over (esegui riga senza entrare nei metodi)
- **F7:** Step Into (entra nei metodi chiamati)
- **F9:** Continue (continua fino al prossimo breakpoint)

### **4. Watch Variables**
Negli IDE puoi "osservare" le variabili durante il debug per vedere come cambiano i loro valori.

---

## 🛠️ **Strumenti di Debug Avanzati**

### **JVisualVM** (Monitoring JVM)
```bash
# Avvia con Java
jvisualvm
```

### **JConsole** (Monitoring applicazioni)
```bash
jconsole
```

### **Logger invece di System.out**
```java
import java.util.logging.Logger;

public class MiaClasse {
    private static final Logger logger = Logger.getLogger(MiaClasse.class.getName());
    
    public void mioMetodo() {
        logger.info("Inizio metodo");
        logger.warning("Attenzione: valore inaspettato");
        logger.severe("Errore critico!");
    }
}
```

---

## 📋 **Checklist per Debugging**

Quando hai un errore, segui questa checklist:

### **✅ Errori di Compilazione**
- [ ] Controlla sintassi (parentesi, punti e virgola)
- [ ] Verifica spelling di variabili e metodi
- [ ] Assicurati che gli import siano corretti
- [ ] Controlla che i tipi di dati siano compatibili
- [ ] Verifica che tutti i path e return siano presenti

### **✅ Errori Runtime**
- [ ] Controlla input/output per valori null
- [ ] Verifica indici array/liste
- [ ] Controlla divisioni per zero
- [ ] Assicurati che le conversioni di tipo siano valide
- [ ] Verifica le condizioni dei loop

### **✅ Errori di Logica**
- [ ] Testa con input semplici
- [ ] Usa debug prints per tracciare il flusso
- [ ] Controlla le condizioni if/while
- [ ] Verifica i valori delle variabili nei punti chiave
- [ ] Assicurati che i loop abbiano condizioni di uscita

---

## 📞 **Quando Chiedere Aiuto**

Se hai provato tutto e non riesci a risolvere:

1. **Prepara le informazioni:**
   - Codice che causa il problema
   - Messaggio di errore completo
   - Cosa stavi cercando di fare
   - Cosa hai già provato

2. **Dove chiedere:**
   - Stack Overflow (in inglese)
   - Forum Java italiani
   - Community GitHub del progetto
   - Gruppi di studio universitari

3. **Come formulare la domanda:**
   - Titolo chiaro e specifico
   - Codice formattato correttamente
   - Passi per riprodurre il problema
   - Cosa ti aspettavi vs cosa è successo

---

## 📖 **Navigazione**
- [🏠 Torna al README Principale](README.md)
- [❓ FAQ](FAQ.md)
- [📖 Glossario](glossario.md)

---

*Ultimo aggiornamento: Giugno 2025*
