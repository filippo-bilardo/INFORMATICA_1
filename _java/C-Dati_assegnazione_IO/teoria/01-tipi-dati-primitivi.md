# Tipi di Dati Primitivi in Java

## 🎯 Obiettivi di Apprendimento

Alla fine di questa sezione, saprai:
- Distinguere tra tipi primitivi e tipi riferimento
- Utilizzare correttamente tutti i tipi primitivi Java
- Comprendere il casting e le conversioni di tipo
- Gestire le costanti e le best practices per i tipi di dati

---

## 📊 Introduzione ai Tipi di Dati

Java è un linguaggio **fortemente tipizzato**, il che significa che:
- Ogni variabile deve avere un tipo dichiarato
- I tipi vengono controllati a compile-time
- Le conversioni tra tipi devono essere esplicite o compatibili

### Classificazione dei Tipi in Java

```
Tipi Java
├── Tipi Primitivi (8 tipi)
│   ├── Interi: byte, short, int, long
│   ├── Decimali: float, double
│   ├── Carattere: char
│   └── Booleano: boolean
└── Tipi Riferimento
    ├── Classi (String, Integer, etc.)
    ├── Array
    └── Interfacce
```

---

## 🔢 Tipi Numerici Interi

### 1. **byte** - Intero a 8 bit
```java
byte valoreByte = 100;
// Range: -128 a 127 (2^7)
// Uso: Risparmio memoria per grandi quantità di dati
```

**Caratteristiche:**
- **Dimensione:** 8 bit (1 byte)
- **Range:** -128 ≤ valore ≤ 127
- **Valore default:** 0
- **Uso tipico:** Array di grandi dimensioni, protocolli di rete

### 2. **short** - Intero a 16 bit
```java
short valoreShort = 30000;
// Range: -32,768 a 32,767 (2^15)
// Uso: Risparmio memoria, raramente utilizzato
```

**Caratteristiche:**
- **Dimensione:** 16 bit (2 byte)
- **Range:** -32,768 ≤ valore ≤ 32,767
- **Valore default:** 0
- **Uso tipico:** Sistemi embedded, ottimizzazione memoria

### 3. **int** - Intero a 32 bit (TIPO STANDARD)
```java
int valoreInt = 2147483647;
// Range: -2,147,483,648 a 2,147,483,647 (2^31)
// Tipo più utilizzato per numeri interi
```

**Caratteristiche:**
- **Dimensione:** 32 bit (4 byte)
- **Range:** -2,147,483,648 ≤ valore ≤ 2,147,483,647
- **Valore default:** 0
- **Uso tipico:** Contatori, indici, calcoli generali

### 4. **long** - Intero a 64 bit
```java
long valoreLong = 9223372036854775807L; // Nota la 'L' finale
// Range: -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807 (2^63)
// Uso: Valori molto grandi, timestamp
```

**Caratteristiche:**
- **Dimensione:** 64 bit (8 byte)
- **Range:** -2^63 ≤ valore ≤ 2^63-1
- **Valore default:** 0L
- **Uso tipico:** Timestamp, ID univoci, calcoli scientifici

---

## 🌊 Tipi Numerici Decimali (Virgola Mobile)

### 1. **float** - Decimale a singola precisione
```java
float valoreFloat = 3.14159f; // Nota la 'f' finale
// Precisione: ~7 cifre decimali
// IEEE 754 single precision
```

**Caratteristiche:**
- **Dimensione:** 32 bit (4 byte)
- **Precisione:** ~7 cifre decimali significative
- **Range:** ±1.4E-45 a ±3.4028235E+38
- **Valore default:** 0.0f
- **Uso tipico:** Grafica 3D, calcoli dove la precisione non è critica

### 2. **double** - Decimale a doppia precisione (TIPO STANDARD)
```java
double valoreDouble = 3.141592653589793;
// Precisione: ~15-17 cifre decimali
// IEEE 754 double precision
```

**Caratteristiche:**
- **Dimensione:** 64 bit (8 byte)
- **Precisione:** ~15-17 cifre decimali significative
- **Range:** ±4.9E-324 a ±1.7976931348623157E+308
- **Valore default:** 0.0
- **Uso tipico:** Calcoli scientifici, finanziari, matematici

---

## 📝 Tipo Carattere

### **char** - Carattere Unicode
```java
char carattere = 'A';           // Carattere letterale
char unicode = '\u0041';        // Codice Unicode (A)
char numero = 65;               // Valore numerico (A)
char carattereSpeciale = '\n';  // Carattere di escape
```

**Caratteristiche:**
- **Dimensione:** 16 bit (2 byte)
- **Range:** 0 a 65,535 (caratteri Unicode)
- **Valore default:** '\u0000' (carattere nullo)
- **Codifica:** UTF-16

**Sequenze di Escape Comuni:**
```java
char tab = '\t';          // Tabulazione
char newline = '\n';      // A capo
char carriageReturn = '\r'; // Ritorno carrello
char backslash = '\\';    // Backslash
char singleQuote = '\'';  // Apice singolo
char doubleQuote = '"';   // Virgolette (non serve escape in char)
```

---

## ✅ Tipo Booleano

### **boolean** - Valore logico
```java
boolean vero = true;
boolean falso = false;
boolean risultato = (5 > 3); // true
```

**Caratteristiche:**
- **Valori possibili:** `true` o `false`
- **Dimensione:** Non specificata (dipende dalla JVM)
- **Valore default:** `false`
- **Uso tipico:** Condizioni, flag, controllo flusso

---

## 🔄 Conversioni di Tipo (Casting)

### Conversioni Implicite (Widening)
```java
// Automatiche, sicure (nessuna perdita di dati)
byte b = 100;
short s = b;    // byte → short
int i = s;      // short → int
long l = i;     // int → long
float f = l;    // long → float
double d = f;   // float → double
```

### Conversioni Esplicite (Narrowing)
```java
// Richiede cast esplicito, possibile perdita di dati
double d = 123.456;
float f = (float) d;    // Possibile perdita di precisione
long l = (long) f;      // Parte decimale troncata
int i = (int) l;        // Possibile overflow
short s = (short) i;    // Possibile overflow
byte b = (byte) s;      // Possibile overflow
```

### ⚠️ Attenzione agli Overflow
```java
// Esempio di overflow
byte maxByte = 127;
byte overflow = (byte) (maxByte + 1); // Risultato: -128!

// Controllo overflow per int
int a = Integer.MAX_VALUE;
int b = 1;
// a + b causa overflow!
long result = (long) a + b; // Sicuro
```

---

## 📚 Letterali e Notazioni Speciali

### Letterali Numerici
```java
// Interi
int decimale = 42;
int esadecimale = 0x2A;     // Base 16
int ottale = 052;           // Base 8 (deprecated)
int binario = 0b101010;     // Base 2 (Java 7+)

// Separatori per leggibilità (Java 7+)
int million = 1_000_000;
long creditCard = 1234_5678_9012_3456L;
float pi = 3.14_15_92F;

// Notazione scientifica
double avogadro = 6.022e23;
float planck = 6.626e-34f;
```

### Valori Speciali per float/double
```java
double positiveInfinity = Double.POSITIVE_INFINITY;
double negativeInfinity = Double.NEGATIVE_INFINITY;
double notANumber = Double.NaN;

// Controlli
boolean isInfinite = Double.isInfinite(positiveInfinity);
boolean isNaN = Double.isNaN(notANumber);
```

---

## 🎨 Best Practices

### 1. **Scelta del Tipo Appropriato**
```java
// ✅ Corretto
int contatore = 0;              // Per contatori normali
long timestamp = System.currentTimeMillis(); // Per timestamp
double prezzo = 19.99;          // Per valori monetari approssimativi
boolean attivo = true;          // Per flag

// ❌ Evitare
byte contatore = 0;             // Troppo limitato
float prezzo = 19.99f;          // Precisione insufficiente per denaro
```

### 2. **Inizializzazione Esplicita**
```java
// ✅ Sempre inizializzare le variabili locali
int count = 0;
double total = 0.0;
boolean found = false;

// ❌ Le variabili locali non inizializzate causano errori
int count; // Errore di compilazione se usata prima dell'inizializzazione
```

### 3. **Naming Conventions**
```java
// ✅ Convenzioni Java
int numeroStudenti = 25;        // camelCase
final double PI = 3.14159;      // UPPER_CASE per costanti
boolean isValid = true;         // is/has per boolean
```

### 4. **Uso delle Costanti**
```java
// ✅ Definire costanti per valori magici
public static final int MAX_ATTEMPTS = 3;
public static final double TAX_RATE = 0.22;
public static final String DEFAULT_ENCODING = "UTF-8";

// ❌ Evitare numeri magici
if (attempts > 3) { ... } // Cosa significa 3?
```

---

## 📋 Riepilogo Tipi Primitivi

| Tipo    | Dimensione | Range                    | Default | Wrapper Class |
|---------|------------|--------------------------|---------|---------------|
| byte    | 8 bit      | -128 a 127               | 0       | Byte          |
| short   | 16 bit     | -32,768 a 32,767         | 0       | Short         |
| int     | 32 bit     | -2^31 a 2^31-1           | 0       | Integer       |
| long    | 64 bit     | -2^63 a 2^63-1           | 0L      | Long          |
| float   | 32 bit     | ±1.4E-45 a ±3.4E+38     | 0.0f    | Float         |
| double  | 64 bit     | ±4.9E-324 a ±1.8E+308   | 0.0     | Double        |
| char    | 16 bit     | 0 a 65,535 (Unicode)     | '\u0000'| Character     |
| boolean | N/A        | true o false             | false   | Boolean       |

---

## 🚀 Prossimi Passi

Nel prossimo capitolo vedremo:
- **Variabili e Costanti** - Dichiarazione, inizializzazione, scope
- **Operatori** - Aritmetici, logici, di confronto
- **Espressioni** - Precedenza operatori, valutazione

---

## 🔗 Link Utili

- [Java Language Specification - Primitive Types](https://docs.oracle.com/javase/specs/jls/se11/html/jls-4.html#jls-4.2)
- [Oracle Tutorial - Primitive Data Types](https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html)
- [IEEE 754 Standard](https://en.wikipedia.org/wiki/IEEE_754) - Standard per numeri in virgola mobile
