# QUIZ MODULO C - Dati, Assegnazione e Input/Output

**Obiettivo**: Verificare la comprensione dei concetti di gestione dati, operatori, conversioni e input/output in Java.

**Istruzioni**: 
- Leggi attentamente ogni domanda
- Scegli la risposta più corretta tra quelle proposte
- Ogni domanda vale 1 punto
- Punteggio minimo per superare il quiz: 15/20

---

## 1. Tipi di Dati Primitivi

**Quale dei seguenti è il range corretto per il tipo `int` in Java?**

A) -128 a 127
B) -32,768 a 32,767
C) -2,147,483,648 a 2,147,483,647
D) -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807

<details>
<summary>Risposta</summary>
**C)** -2,147,483,648 a 2,147,483,647

Il tipo `int` in Java è a 32 bit con segno, quindi il range è da -2^31 a 2^31-1.
</details>

---

## 2. Dichiarazione e Inizializzazione

**Quale delle seguenti dichiarazioni è CORRETTA?**

A) `int numero = 3.14;`
B) `double prezzo = 19.99;`
C) `boolean attivo = 1;`
D) `char lettera = "A";`

<details>
<summary>Risposta</summary>
**B)** `double prezzo = 19.99;`

È l'unica dichiarazione sintatticamente corretta. A) assegna un double a un int, C) assegna un int a un boolean, D) assegna una String a un char.
</details>

---

## 3. Operatori Aritmetici

**Qual è il risultato di `17 % 5` in Java?**

A) 3
B) 2
C) 3.4
D) 0

<details>
<summary>Risposta</summary>
**B)** 2

L'operatore modulo (%) restituisce il resto della divisione intera: 17 ÷ 5 = 3 con resto 2.
</details>

---

## 4. Precedenza degli Operatori

**Qual è il risultato dell'espressione `2 + 3 * 4`?**

A) 20
B) 14
C) 12
D) 10

<details>
<summary>Risposta</summary>
**B)** 14

La moltiplicazione ha precedenza maggiore dell'addizione: 2 + (3 * 4) = 2 + 12 = 14.
</details>

---

## 5. Operatori di Incremento

**Qual è la differenza tra `++i` e `i++`?**

A) Non c'è differenza
B) `++i` incrementa prima di usare il valore, `i++` incrementa dopo
C) `++i` incrementa di 2, `i++` incrementa di 1
D) `++i` è per int, `i++` è per double

<details>
<summary>Risposta</summary>
**B)** `++i` incrementa prima di usare il valore, `i++` incrementa dopo

`++i` è pre-incremento (incrementa e poi usa il valore), `i++` è post-incremento (usa il valore e poi incrementa).
</details>

---

## 6. Conversioni di Tipo (Casting)

**Quale conversione richiede un cast esplicito?**

A) `int` a `double`
B) `byte` a `int`
C) `double` a `int`
D) `char` a `int`

<details>
<summary>Risposta</summary>
**C)** `double` a `int`

La conversione da `double` a `int` è una conversione narrowing che può causare perdita di dati e richiede un cast esplicito.
</details>

---

## 7. Operatori Logici

**Qual è il risultato di `true && false || true`?**

A) true
B) false
C) Errore di compilazione
D) Dipende dall'implementazione

<details>
<summary>Risposta</summary>
**A)** true

L'operatore && ha precedenza maggiore di ||: (true && false) || true = false || true = true.
</details>

---

## 8. Operatori di Confronto

**Quale espressione è sempre `true`?**

A) `5 == 5.0`
B) `"Java" == "Java"`
C) `'A' == 65`
D) Tutte le precedenti

<details>
<summary>Risposta</summary>
**C)** `'A' == 65`

Il carattere 'A' ha valore ASCII 65. A) può essere true ma dipende dalla conversione, B) confronta riferimenti, non contenuto.
</details>

---

## 9. Scanner e Input

**Quale metodo Scanner è corretto per leggere un numero intero?**

A) `scanner.readInt()`
B) `scanner.nextInt()`
C) `scanner.getInt()`
D) `scanner.inputInt()`

<details>
<summary>Risposta</summary>
**B)** `scanner.nextInt()`

Il metodo corretto della classe Scanner per leggere un intero è `nextInt()`.
</details>

---

## 10. Gestione Input con Scanner

**Cosa succede se l'utente inserisce "abc" quando il programma chiama `scanner.nextInt()`?**

A) Viene restituito 0
B) Viene lanciata una `InputMismatchException`
C) Il programma si blocca
D) Viene restituito -1

<details>
<summary>Risposta</summary>
**B)** Viene lanciata una `InputMismatchException`

Scanner lancia questa eccezione quando il token di input non corrisponde al tipo richiesto.
</details>

---

## 11. Formattazione Output

**Quale specifier printf stampa un numero decimale con 2 cifre decimali?**

A) `%d`
B) `%.2f`
C) `%2f`
D) `%f.2`

<details>
<summary>Risposta</summary>
**B)** `%.2f`

Il formato `%.2f` specifica un numero floating-point con 2 cifre decimali.
</details>

---

## 12. DecimalFormat

**Quale pattern DecimalFormat formatta un numero come "€1,234.56"?**

A) `"€#,##0.00"`
B) `"€###,###.##"`
C) `"€#.###,00"`
D) `"€0,000.00"`

<details>
<summary>Risposta</summary>
**A)** `"€#,##0.00"`

Questo pattern assicura sempre 2 cifre decimali e separatori delle migliaia quando necessario.
</details>

---

## 13. Variabili e Scope

**Quale delle seguenti affermazioni sul scope delle variabili è CORRETTA?**

A) Le variabili locali sono visibili in tutto il programma
B) Le variabili dichiarate in un blocco sono visibili solo in quel blocco
C) Le variabili static non hanno scope
D) Tutte le variabili hanno lo stesso scope

<details>
<summary>Risposta</summary>
**B)** Le variabili dichiarate in un blocco sono visibili solo in quel blocco

Il scope di una variabile è limitato al blocco in cui è dichiarata (delimitato da {}).
</details>

---

## 14. Costanti

**Come si dichiara correttamente una costante in Java?**

A) `const double PI = 3.14159;`
B) `final double PI = 3.14159;`
C) `constant double PI = 3.14159;`
D) `readonly double PI = 3.14159;`

<details>
<summary>Risposta</summary>
**B)** `final double PI = 3.14159;`

In Java si usa la keyword `final` per dichiarare costanti.
</details>

---

## 15. Operatori di Assegnazione

**Qual è il valore di `x` dopo `int x = 10; x += 5; x *= 2;`?**

A) 20
B) 25
C) 30
D) 40

<details>
<summary>Risposta</summary>
**C)** 30

x = 10, poi x += 5 → x = 15, poi x *= 2 → x = 30.
</details>

---

## 16. Overflow e Underflow

**Cosa succede quando si verifica un overflow in un `int`?**

A) Viene lanciata un'eccezione
B) Il valore diventa 0
C) Il valore "wrappa" al valore minimo
D) Il programma si interrompe

<details>
<summary>Risposta</summary>
**C)** Il valore "wrappa" al valore minimo

In Java, l'overflow di un int causa un "wrap-around" al valore minimo del tipo.
</details>

---

## 17. Tipo char

**Quale delle seguenti è una dichiarazione valida per una variabile char?**

A) `char c = 'AB';`
B) `char c = "A";`
C) `char c = '\n';`
D) `char c = 256;`

<details>
<summary>Risposta</summary>
**C)** `char c = '\n';`

Un char può contenere un singolo carattere, inclusi caratteri di escape come '\n'.
</details>

---

## 18. Conversioni Automatiche

**In quale situazione Java effettua una conversione automatica (widening)?**

A) `double` a `float`
B) `int` a `byte`
C) `byte` a `int`
D) `long` a `int`

<details>
<summary>Risposta</summary>
**C)** `byte` a `int`

Java effettua conversioni automatiche solo quando non c'è perdita di dati (widening conversion).
</details>

---

## 19. Input/Output con File

**Quale classe è più appropriata per leggere testo da un file?**

A) `FileInputStream`
B) `FileReader`
C) `BufferedReader`
D) `Scanner`

<details>
<summary>Risposta</summary>
**D)** `Scanner`

Scanner è versatile e può leggere da file con metodi convenienti per diversi tipi di dati.
</details>

---

## 20. Best Practices

**Quale delle seguenti è considerata una best practice per la gestione dell'input dell'utente?**

A) Non validare mai l'input
B) Assumere sempre che l'input sia corretto
C) Validare sempre l'input e gestire gli errori
D) Usare solo input hardcoded

<details>
<summary>Risposta</summary>
**C)** Validare sempre l'input e gestire gli errori

È fondamentale validare l'input dell'utente per evitare errori e comportamenti inaspettati del programma.
</details>

---

## Valutazione

**Punteggio**: ___/20

**Scala di valutazione**:
- 18-20: Eccellente - Ottima comprensione dei concetti
- 15-17: Buono - Buona comprensione con alcune lacune minori
- 12-14: Sufficiente - Comprensione base, necessario ripasso
- 9-11: Insufficiente - Ripasso approfondito necessario
- 0-8: Gravemente insufficiente - Studio completo del modulo necessario

---

## Note per il Docente

**Obiettivi di Apprendimento Valutati**:
1. **Tipi di dati primitivi**: Comprensione range, dichiarazione, uso appropriato
2. **Operatori**: Aritmetici, logici, di confronto, precedenza
3. **Conversioni**: Casting esplicito e implicito, gestione overflow
4. **Input/Output**: Scanner, formattazione, validazione
5. **Best practices**: Gestione errori, validazione input, coding standards

**Suggerimenti per il Recupero**:
- **Punteggio basso**: Rivedere teoria e ripetere esercizi base
- **Errori su operatori**: Focus su precedenza e valutazione espressioni
- **Errori su I/O**: Praticare con Scanner e formattazione
- **Errori su casting**: Rivedere regole di conversione Java

**Attività di Rinforzo Consigliate**:
1. Esercizi pratici su calcolatrice scientifica
2. Progetti di gestione dati con input/output
3. Debugging di programmi con errori di casting
4. Implementazione di sistemi di validazione input
