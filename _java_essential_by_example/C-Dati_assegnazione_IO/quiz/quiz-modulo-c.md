# Quiz - Modulo C: Dati, Assegnazione e I/O

## Informazioni sul Quiz
- **Durata suggerita**: 45 minuti
- **Punteggio totale**: 100 punti
- **Soglia superamento**: 60 punti
- **Domande**: 25 (multiple choice, vero/falso, codice)
- **Difficoltà**: Progressiva (base → intermedio → avanzato)

---

## 📝 Istruzioni
1. Leggi attentamente ogni domanda
2. Per domande di codice, considera la sintassi Java corretta
3. Alcune domande hanno più risposte corrette
4. Il tempo è orientativo, lavora con calma

---

## 🎯 Sezione A: Tipi di Dati Primitivi (25 punti)

### Domanda 1 (3 punti)
Quale dei seguenti **NON** è un tipo di dato primitivo in Java?

a) `int`  
b) `String`  
c) `boolean`  
d) `double`

<details>
<summary>💡 Risposta</summary>
<b>b) String</b> - String è una classe, non un tipo primitivo
</details>

---

### Domanda 2 (4 punti)
Qual è il valore di default per una variabile `boolean` non inizializzata in una classe?

a) `true`  
b) `false`  
c) `null`  
d) Errore di compilazione

<details>
<summary>💡 Risposta</summary>
<b>b) false</b> - I boolean hanno valore default false
</details>

---

### Domanda 3 (4 punti)
Quale conversione è **implicita** (non richiede cast)?

a) `double` → `int`  
b) `int` → `double`  
c) `long` → `int`  
d) `float` → `int`

<details>
<summary>💡 Risposta</summary>
<b>b) int → double</b> - Conversione widening automatica
</details>

---

### Domanda 4 (5 punti)
Cosa stampa il seguente codice?
```java
int a = 5;
int b = 2;
double risultato = a / b;
System.out.println(risultato);
```

a) `2.5`  
b) `2.0`  
c) `2`  
d) Errore di compilazione

<details>
<summary>💡 Risposta</summary>
<b>b) 2.0</b> - Divisione intera (5/2=2) poi convertita a double
</details>

---

### Domanda 5 (4 punti)
Qual è il range del tipo `byte` in Java?

a) 0 a 255  
b) -127 a 128  
c) -128 a 127  
d) -256 a 255

<details>
<summary>💡 Risposta</summary>
<b>c) -128 a 127</b> - Byte è signed a 8 bit
</details>

---

### Domanda 6 (5 punti)
**VERO o FALSO**: Il seguente codice compila senza errori:
```java
final int MAX = 100;
MAX = 200;
```

**Risposta**: ______

<details>
<summary>💡 Risposta</summary>
<b>FALSO</b> - Le variabili final non possono essere riassegnate
</details>

---

## 🔧 Sezione B: Variabili, Costanti e Operatori (30 punti)

### Domanda 7 (4 punti)
Quale operatore ha la **precedenza più alta**?

a) `+` (addizione)  
b) `*` (moltiplicazione)  
c) `++` (incremento)  
d) `=` (assegnazione)

<details>
<summary>💡 Risposta</summary>
<b>c) ++</b> - Gli operatori unari hanno precedenza massima
</details>

---

### Domanda 8 (5 punti)
Cosa stampa il seguente codice?
```java
int x = 5;
int y = ++x + x++;
System.out.println("x=" + x + ", y=" + y);
```

a) `x=6, y=11`  
b) `x=7, y=11`  
c) `x=7, y=12`  
d) `x=6, y=12`

<details>
<summary>💡 Risposta</summary>
<b>c) x=7, y=12</b> - ++x incrementa prima (6), x++ dopo (6), risultato: 6+6=12, x finale=7
</details>

---

### Domanda 9 (4 punti)
Quale dichiarazione di costante è **corretta**?

a) `const int MAX = 100;`  
b) `final int MAX = 100;`  
c) `static int MAX = 100;`  
d) `readonly int MAX = 100;`

<details>
<summary>💡 Risposta</summary>
<b>b) final int MAX = 100;</b> - In Java si usa 'final' per le costanti
</details>

---

### Domanda 10 (6 punti)
Analizza questo codice e indica il risultato:
```java
boolean a = true;
boolean b = false;
boolean result = a && b || !a && !b;
System.out.println(result);
```

a) `true`  
b) `false`  
c) Errore di compilazione  
d) Dipende dall'ordine di valutazione

<details>
<summary>💡 Risposta</summary>
<b>b) false</b> - (true && false) || (!true && !false) = false || false = false
</details>

---

### Domanda 11 (5 punti)
Qual è la differenza tra `=` e `==`?

a) Nessuna differenza  
b) `=` è assegnazione, `==` è confronto  
c) `=` è confronto, `==` è assegnazione  
d) `==` funziona solo con numeri

<details>
<summary>💡 Risposta</summary>
<b>b) = è assegnazione, == è confronto</b>
</details>

---

### Domanda 12 (6 punti)
**Completa il codice** per calcolare la media di tre numeri:
```java
int a = 10, b = 20, c = 30;
double media = _________________;
```

<details>
<summary>💡 Risposta</summary>
<b>(a + b + c) / 3.0</b> o <b>(double)(a + b + c) / 3</b>
</details>

---

## 🖥️ Sezione C: Input/Output (25 punti)

### Domanda 13 (4 punti)
Quale classe si usa principalmente per l'input da tastiera?

a) `BufferedReader`  
b) `Scanner`  
c) `System.in`  
d) `InputStreamReader`

<details>
<summary>💡 Risposta</summary>
<b>b) Scanner</b> - È la più comune per input semplice
</details>

---

### Domanda 14 (5 punti)
Cosa stampa `System.out.printf("%.2f", 3.14159)`?

a) `3.14159`  
b) `3.14`  
c) `3.1`  
d) `3`

<details>
<summary>💡 Risposta</summary>
<b>b) 3.14</b> - %.2f formatta con 2 decimali
</details>

---

### Domanda 15 (6 punti)
**VERO o FALSO**: Il seguente codice può generare un'eccezione:
```java
Scanner scanner = new Scanner(System.in);
int numero = scanner.nextInt();
```

**Risposta**: ______ **Perché**: _________________

<details>
<summary>💡 Risposta</summary>
<b>VERO</b> - Può generare InputMismatchException se l'utente non inserisce un intero
</details>

---

### Domanda 16 (5 punti)
Quale metodo di `Scanner` **NON** consume il carattere di newline?

a) `nextLine()`  
b) `nextInt()`  
c) `next()`  
d) `nextDouble()`

<details>
<summary>💡 Risposta</summary>
<b>a) nextLine()</b> - nextLine() consuma il newline, gli altri no
<i>Nota: La domanda è trabocchetto - nextLine() È quello che consuma il newline</i>
<b>Risposta corretta: b, c, d</b> - nextInt(), next(), nextDouble() NON consumano newline
</details>

---

### Domanda 17 (5 punti)
**Scrivi il codice** per leggere una stringa che può contenere spazi:

```java
Scanner scanner = new Scanner(System.in);
String frase = ________________________;
```

<details>
<summary>💡 Risposta</summary>
<b>scanner.nextLine()</b>
</details>

---

## 🧠 Sezione D: Problemi Integrati (20 punti)

### Domanda 18 (6 punti)
**Trova l'errore** nel seguente codice:
```java
Scanner input = new Scanner(System.in);
System.out.print("Età: ");
byte eta = input.nextByte();
if (eta >= 18)
    System.out.println("Maggiorenne");
    System.out.println("Benvenuto!");
```

<details>
<summary>💡 Risposta</summary>
<b>Mancano le parentesi graffe nell'if</b> - "Benvenuto!" viene sempre stampato
</details>

---

### Domanda 19 (7 punti)
**Completa** il programma per convertire Celsius in Fahrenheit:
```java
Scanner scanner = new Scanner(System.in);
System.out.print("Temperatura in Celsius: ");
double celsius = scanner.nextDouble();
double fahrenheit = ______________________;
System.out.printf("%.1f°C = %.1f°F%n", celsius, fahrenheit);
```

<details>
<summary>💡 Risposta</summary>
<b>celsius * 9.0 / 5.0 + 32</b> o <b>(celsius * 9 / 5) + 32</b>
</details>

---

### Domanda 20 (7 punts)
**Analizza** questo codice e spiega cosa fa:
```java
int numero = 1234;
int somma = 0;
while (numero > 0) {
    somma += numero % 10;
    numero /= 10;
}
System.out.println(somma);
```

**Cosa stampa**: ______  
**Cosa fa il programma**: ________________________________

<details>
<summary>💡 Risposta</summary>
<b>Stampa: 10</b><br>
<b>Cosa fa: Calcola la somma delle cifre di un numero</b> (1+2+3+4=10)
</details>

---

## 🏆 Sezione E: Domande Avanzate (Bonus: 10 punti)

### Domanda 21 (5 punti)
**Quale problema** può verificarsi con questo codice?
```java
float prezzo = 0.1f;
float totale = 0.0f;
for (int i = 0; i < 10; i++) {
    totale += prezzo;
}
System.out.println(totale == 1.0f);
```

<details>
<summary>💡 Risposta</summary>
<b>Errori di precisione in virgola mobile</b> - Il risultato potrebbe non essere esattamente 1.0
</details>

---

### Domanda 22 (5 punti)
**Vero o Falso**: È buona pratica chiudere sempre lo Scanner?

**Risposta**: ______  
**Motivazione**: _________________________________

<details>
<summary>💡 Risposta</summary>
<b>VERO</b> - Per liberare risorse di sistema, anche se System.in raramente causa problemi
</details>

---

## 📊 Tabella Valutazione

| Punteggio | Valutazione | Commento |
|-----------|-------------|----------|
| 90-100    | Eccellente  | Padronanza completa dei concetti |
| 80-89     | Molto Buono | Comprensione solida con piccole lacune |
| 70-79     | Buono       | Comprensione adeguata, da approfondire |
| 60-69     | Sufficiente | Concetti base acquisiti, serve pratica |
| < 60      | Insufficiente | Necessario ripasso approfondito |

---

## 🎓 Soluzioni e Spiegazioni Dettagliate

### Analisi Errori Comuni:

1. **Confusione tra tipi**: `String` non è primitivo
2. **Casting necessario**: Conversioni narrowing richiedono cast esplicito
3. **Precedenza operatori**: Ricordare che unari > moltiplicativi > additivi > relazionali > logici > assegnazione
4. **Input validation**: Scanner può generare eccezioni
5. **Newline problems**: Mixing nextInt() e nextLine()

### Suggerimenti per il Ripasso:

- **Se punteggio < 70 in Sezione A**: Ripassa [Teoria Tipi Dati](../teoria/01-tipi-dati-primitivi.md)
- **Se punteggio < 70 in Sezione B**: Ripassa [Teoria Operatori](../teoria/02-variabili-costanti-operatori.md)  
- **Se punteggio < 70 in Sezione C**: Ripassa [Teoria I/O](../teoria/03-input-output.md)
- **Se errori nelle sezioni integrate**: Pratica con [Esercizi](../esercizi/README.md)

---

## 🔄 Prossimi Passi

**Se hai superato il quiz (≥60 punti)**: Procedi al [Modulo D - Controllo del Flusso](../../D-Controllo_flusso/README.md)

**Se non hai superato il quiz**: 
1. Rivedi gli argomenti problematici
2. Completa gli esercizi mancanti  
3. Riprova il quiz dopo il ripasso

**Per migliorare ulteriormente**:
- Completa tutti gli esercizi del modulo
- Sperimenta con variazioni dei codici
- Cerca di capire il "perché" delle regole Java

---

**🎯 Ricorda**: Il vero apprendimento avviene attraverso la pratica! Non limitarti al quiz, sperimenta sempre con il codice.

---

**Prossimo**: [Modulo D](../../D-Controllo_flusso/README.md) | **Indietro**: [Esercizi Modulo C](../esercizi/README.md)
