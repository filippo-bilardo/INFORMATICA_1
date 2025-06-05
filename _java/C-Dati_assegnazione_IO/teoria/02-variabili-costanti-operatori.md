# Variabili, Costanti e Operatori in Java

## 🎯 Obiettivi di Apprendimento

Alla fine di questa sezione, saprai:
- Dichiarare e inizializzare variabili correttamente
- Utilizzare costanti e modificatori di accesso
- Padroneggiare tutti gli operatori Java
- Comprendere precedenza e associatività degli operatori
- Gestire lo scope delle variabili

---

## 📦 Variabili in Java

### Dichiarazione e Inizializzazione

```java
// Dichiarazione
int numero;              // Variabile dichiarata ma non inizializzata
String nome;             // Riferimento a null

// Inizializzazione
numero = 42;             // Assegnazione di valore
nome = "Mario";          // Assegnazione di riferimento

// Dichiarazione + Inizializzazione
int eta = 25;            // In una sola riga
double altezza = 1.75, peso = 70.5; // Multipla (stesso tipo)
```

### Tipi di Variabili

#### 1. **Variabili Locali**
```java
public void metodo() {
    int variabileLocale = 10;    // Visibile solo nel metodo
    // Deve essere inizializzata prima dell'uso
    if (true) {
        int altraVariabile = 20; // Visibile solo nel blocco if
    }
    // altraVariabile non accessibile qui
}
```

#### 2. **Variabili di Istanza (Campi)**
```java
public class Persona {
    private String nome;         // Campo di istanza
    private int eta = 0;         // Inizializzato con valore default
    
    // Ogni oggetto ha la sua copia di questi campi
}
```

#### 3. **Variabili di Classe (Statiche)**
```java
public class Contatore {
    private static int count = 0;    // Condivisa tra tutte le istanze
    public static final String VERSIONE = "1.0"; // Costante di classe
}
```

---

## 🔒 Costanti e Modificatori

### Parola Chiave `final`

#### Variabili Final
```java
final int NUMERO_FISSO = 100;        // Costante locale
final String messaggio;              // Deve essere inizializzata
messaggio = "Ciao";                  // OK, prima assegnazione
// messaggio = "Altro";              // ERRORE! Già assegnata

// Costanti di classe
public static final double PI = 3.14159;
public static final int MAX_SIZE = 1000;
```

#### Oggetti Final
```java
final List<String> lista = new ArrayList<>();
lista.add("elemento");               // OK, modifica il contenuto
// lista = new ArrayList<>();        // ERRORE! Non può riassegnare il riferimento

final StringBuilder sb = new StringBuilder("Hello");
sb.append(" World");                 // OK, modifica il contenuto
```

### Naming Conventions per Costanti
```java
// ✅ Corretto: UPPER_SNAKE_CASE
public static final int MAX_RETRY_COUNT = 3;
public static final String DEFAULT_FILE_PATH = "/tmp/app.log";
public static final double CONVERSION_RATE = 1.609344;

// ❌ Scorretto
public static final int maxRetryCount = 3;    // dovrebbe essere maiuscolo
public static final String defaultfilepath = "/tmp/app.log"; // underscore mancanti
```

---

## ⚡ Operatori Aritmetici

### Operatori Base
```java
int a = 10, b = 3;

int somma = a + b;          // 13
int differenza = a - b;     // 7
int prodotto = a * b;       // 30
int quoziente = a / b;      // 3 (divisione intera!)
int resto = a % b;          // 1 (modulo)

// Divisione con decimali
double divisione = (double) a / b;  // 3.333...
double divisioneExact = 10.0 / 3.0; // 3.333...
```

### Operatori Unari
```java
int x = 5;
int y = -x;                 // -5 (negazione)
int z = +x;                 // 5 (positivo, raramente usato)

// Pre-incremento e post-incremento
int a = 5;
int b = ++a;                // a = 6, b = 6 (pre-incremento)
int c = a++;                // c = 6, a = 7 (post-incremento)

// Pre-decremento e post-decremento
int d = 7;
int e = --d;                // d = 6, e = 6 (pre-decremento)
int f = d--;                // f = 6, d = 5 (post-decremento)
```

### Operatori di Assegnazione Composta
```java
int x = 10;
x += 5;     // x = x + 5;  → x = 15
x -= 3;     // x = x - 3;  → x = 12
x *= 2;     // x = x * 2;  → x = 24
x /= 4;     // x = x / 4;  → x = 6
x %= 5;     // x = x % 5;  → x = 1

// Funziona anche con altri tipi
String testo = "Hello";
testo += " World";          // "Hello World"

double prezzo = 100.0;
prezzo *= 1.22;             // Applica IVA del 22%
```

---

## ⚖️ Operatori di Confronto

```java
int a = 10, b = 20;

boolean uguale = (a == b);          // false
boolean diverso = (a != b);         // true
boolean minore = (a < b);           // true
boolean minoreUguale = (a <= b);    // true
boolean maggiore = (a > b);         // false
boolean maggioreUguale = (a >= b);  // false

// ⚠️ Attenzione con i tipi di riferimento!
String str1 = new String("ciao");
String str2 = new String("ciao");
boolean confronto1 = (str1 == str2);       // false! (confronta riferimenti)
boolean confronto2 = str1.equals(str2);    // true (confronta contenuto)
```

---

## 🧠 Operatori Logici

### Operatori Base
```java
boolean a = true, b = false;

boolean and = a && b;           // false (AND logico)
boolean or = a || b;            // true (OR logico)
boolean not = !a;               // false (NOT logico)

// Operatori non short-circuit (valutano sempre entrambi gli operandi)
boolean andBit = a & b;         // false
boolean orBit = a | b;          // true
boolean xor = a ^ b;            // true (XOR - OR esclusivo)
```

### Short-Circuit Evaluation
```java
boolean risultato;

// && - Se il primo è false, il secondo non viene valutato
risultato = false && (5/0 == 0);    // OK! Non divide per zero

// || - Se il primo è true, il secondo non viene valutato
risultato = true || (5/0 == 0);     // OK! Non divide per zero

// Utilizzo pratico
String testo = null;
if (testo != null && testo.length() > 0) {
    // Sicuro: testo.length() non viene chiamato se testo è null
    System.out.println(testo);
}
```

---

## 🔧 Operatori Bitwise

### Operatori sui Bit
```java
int a = 12;     // 1100 in binario
int b = 10;     // 1010 in binario

int and = a & b;        // 1000 = 8 (AND bitwise)
int or = a | b;         // 1110 = 14 (OR bitwise)
int xor = a ^ b;        // 0110 = 6 (XOR bitwise)
int not = ~a;           // Inverte tutti i bit

// Shift operators
int leftShift = a << 2;     // 110000 = 48 (moltiplicazione per 2^2)
int rightShift = a >> 2;    // 11 = 3 (divisione intera per 2^2)
int unsignedShift = a >>> 2; // Shift senza segno
```

### Usi Pratici degli Operatori Bitwise
```java
// Controllo se un numero è pari
boolean isPari = (numero & 1) == 0;

// Moltiplicazione/divisione veloce per potenze di 2
int moltiplicaPer4 = numero << 2;   // numero * 4
int dividiPer8 = numero >> 3;       // numero / 8

// Operazioni su flag/permessi
int READ = 1;       // 001
int WRITE = 2;      // 010
int EXECUTE = 4;    // 100

int permissions = READ | WRITE;         // 011 (read + write)
boolean canRead = (permissions & READ) != 0;    // true
boolean canExecute = (permissions & EXECUTE) != 0; // false
```

---

## 🎯 Operatori Speciali

### Operatore Ternario (Condizionale)
```java
// Sintassi: condizione ? valoreSeVero : valoreSeFalso
int max = (a > b) ? a : b;
String messaggio = (eta >= 18) ? "Adulto" : "Minorenne";

// Può essere annidato (ma meglio evitare per leggibilità)
String categoria = (eta < 13) ? "Bambino" : 
                   (eta < 18) ? "Adolescente" : "Adulto";

// Equivale a:
String categoria2;
if (eta < 13) {
    categoria2 = "Bambino";
} else if (eta < 18) {
    categoria2 = "Adolescente";
} else {
    categoria2 = "Adulto";
}
```

### Operatore instanceof
```java
Object obj = "Ciao";
boolean isString = obj instanceof String;      // true
boolean isInteger = obj instanceof Integer;    // false

// Uso sicuro con cast
if (obj instanceof String) {
    String str = (String) obj;  // Cast sicuro
    System.out.println(str.length());
}
```

---

## 📊 Precedenza degli Operatori

### Tabella di Precedenza (dal più alto al più basso)

| Precedenza | Operatori | Descrizione |
|------------|-----------|-------------|
| 1 | `[]` `.` `()` | Accesso array, membri, chiamate metodo |
| 2 | `++` `--` `+` `-` `!` `~` | Unari (post/pre-fix, unari, logico, bitwise) |
| 3 | `new` `(type)` | Creazione oggetti, cast |
| 4 | `*` `/` `%` | Moltiplicazione, divisione, modulo |
| 5 | `+` `-` | Addizione, sottrazione |
| 6 | `<<` `>>` `>>>` | Shift bitwise |
| 7 | `<` `<=` `>` `>=` `instanceof` | Confronto relazionale |
| 8 | `==` `!=` | Uguaglianza |
| 9 | `&` | AND bitwise |
| 10 | `^` | XOR bitwise |
| 11 | `|` | OR bitwise |
| 12 | `&&` | AND logico |
| 13 | `||` | OR logico |
| 14 | `?:` | Operatore ternario |
| 15 | `=` `+=` `-=` `*=` `/=` `%=` etc. | Assegnazione |

### Esempi di Precedenza
```java
// Senza parentesi
int risultato = 2 + 3 * 4;      // 14, non 20 (* ha precedenza su +)
boolean test = 5 > 3 && 2 < 4;  // true (prima i confronti, poi &&)

// Con parentesi per chiarezza
int risultato2 = (2 + 3) * 4;   // 20
boolean test2 = (5 > 3) && (2 < 4); // Più chiaro anche se non necessario
```

---

## 🏠 Scope delle Variabili

### Scope Lessicale (Statico)
```java
public class ScopeExample {
    private int campoIstanza = 1;           // Scope: intera classe
    private static int campoStatico = 2;    // Scope: classe + istanze
    
    public void metodo(int parametro) {     // Scope: tutto il metodo
        int variabileLocale = 3;            // Scope: tutto il metodo
        
        if (parametro > 0) {
            int variabileBlocco = 4;        // Scope: solo blocco if
            System.out.println(variabileLocale);    // OK
            System.out.println(campoIstanza);       // OK
        }
        
        // System.out.println(variabileBlocco);    // ERRORE! Fuori scope
        
        for (int i = 0; i < 10; i++) {      // i ha scope solo nel for
            int temp = i * 2;               // temp ha scope solo nel for
        }
        
        // System.out.println(i);           // ERRORE! i fuori scope
    }
}
```

### Shadowing (Nascondere Variabili)
```java
public class ShadowingExample {
    private int x = 1;          // Campo di istanza
    
    public void metodo(int x) { // Parametro nasconde il campo
        int y = x;              // Usa il parametro, non il campo
        int z = this.x;         // Usa il campo con 'this'
        
        if (true) {
            int x = 3;          // ERRORE! Non può ridichiarare parametro
            // int y = 4;       // ERRORE! Non può ridichiarare variabile locale
        }
    }
    
    public static void metodoStatico() {
        int x = 5;              // OK, non c'è conflitto con campo istanza
    }
}
```

---

## 🎨 Best Practices

### 1. **Inizializzazione delle Variabili**
```java
// ✅ Inizializza sempre le variabili locali
int count = 0;
String message = "";
List<String> items = new ArrayList<>();

// ✅ Usa valori di default sensati
boolean isActive = false;
double total = 0.0;

// ❌ Evita variabili non inizializzate
int count; // Può causare errori se usata prima dell'assegnazione
```

### 2. **Uso delle Costanti**
```java
// ✅ Usa costanti per valori magici
public static final int MAX_ATTEMPTS = 3;
public static final double PI = 3.14159265359;
public static final String CONFIG_FILE = "app.properties";

// ❌ Evita numeri magici
if (attempts > 3) { ... }               // Cosa significa 3?
double area = radius * radius * 3.14159; // Usa la costante PI
```

### 3. **Naming e Leggibilità**
```java
// ✅ Nomi descrittivi
int numberOfStudents = 25;
boolean isValidEmail = checkEmail(email);
double monthlyInterestRate = annualRate / 12.0;

// ❌ Nomi criptici
int n = 25;         // Cosa rappresenta n?
boolean b = check(email); // Cosa significa b?
double r = ar / 12.0;     // Cosa sono r e ar?
```

### 4. **Operatori e Parentesi**
```java
// ✅ Usa parentesi per chiarezza
boolean isInRange = (value >= min) && (value <= max);
int average = (sum + count - 1) / count; // Evita divisione per 0

// ✅ Evita espressioni troppo complesse
// ❌ Difficile da leggere
boolean complex = a > b && c < d || e == f && g != h;

// ✅ Spezzare in parti più semplici
boolean firstCondition = (a > b) && (c < d);
boolean secondCondition = (e == f) && (g != h);
boolean result = firstCondition || secondCondition;
```

---

## ⚠️ Errori Comuni e Come Evitarli

### 1. **Confronto di Riferimenti vs Contenuto**
```java
// ❌ Errore comune
String str1 = new String("ciao");
String str2 = new String("ciao");
if (str1 == str2) { /* false! */ }

// ✅ Corretto
if (str1.equals(str2)) { /* true */ }
if (Objects.equals(str1, str2)) { /* Gestisce anche null */ }
```

### 2. **Divisione Intera Inaspettata**
```java
// ❌ Risultato inaspettato
int a = 5, b = 2;
double result = a / b;          // 2.0, non 2.5!

// ✅ Corretto
double result = (double) a / b; // 2.5
double result2 = a / (double) b; // 2.5
double result3 = 5.0 / 2;       // 2.5
```

### 3. **Overflow Numerico**
```java
// ❌ Overflow silenzioso
int max = Integer.MAX_VALUE;
int overflow = max + 1;         // -2147483648 (overflow!)

// ✅ Controllo overflow
try {
    int safe = Math.addExact(max, 1); // Lancia ArithmeticException
} catch (ArithmeticException e) {
    System.out.println("Overflow detected!");
}
```

---

## 📝 Esercizi di Verifica

1. **Dichiara le seguenti variabili con i tipi appropriati:**
   - Età di una persona
   - Prezzo di un prodotto
   - Nome di un utente
   - Se un utente è attivo
   - Numero di telefono (lungo)

2. **Calcola il risultato delle seguenti espressioni:**
   ```java
   int a = 7, b = 3;
   // a) a + b * 2
   // b) (a + b) * 2
   // c) a % b + 1
   // d) ++a - b--
   ```

3. **Correggi gli errori nel seguente codice:**
   ```java
   public class Example {
       int value = 100;
       
       public void method() {
           final int CONSTANT;
           int result = value / 0;
           String text1 = "Hello";
           String text2 = "Hello";
           if (text1 == text2) {
               System.out.println("Equal");
           }
       }
   }
   ```

---

## 🚀 Prossimi Passi

Nel prossimo capitolo vedremo:
- **Input e Output** - Scanner, System.out, printf
- **Formattazione** - Numeri, date, stringhe
- **Gestione degli errori** - Try-catch per I/O

---

## 🔗 Link Utili

- [Java Language Specification - Variables](https://docs.oracle.com/javase/specs/jls/se11/html/jls-4.html#jls-4.12)
- [Oracle Tutorial - Variables](https://docs.oracle.com/javase/tutorial/java/nutsandbolts/variables.html)
- [Java Operator Precedence](https://docs.oracle.com/javase/tutorial/java/nutsandbolts/operators.html)
