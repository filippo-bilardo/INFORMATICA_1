# 🧠 QUIZ INTERATTIVO - Lezione 02: Variabili e Tipi di Dato

> **Obiettivo**: Verificare la comprensione dei tipi di dato fondamentali in C
> **Tempo stimato**: 15-20 minuti
> **Difficoltà**: ⭐⭐⭐ Intermedio

---

## 📝 ISTRUZIONI

1. **Leggi attentamente** ogni domanda
2. **Pensa** alla risposta prima di guardare le opzioni
3. **Segna** la tua risposta mentalmente
4. **Controlla** la soluzione spiegata alla fine
5. **Ripassa** gli argomenti su cui hai difficoltà

---

## ❓ DOMANDE

### **1. Dimensioni dei Tipi di Dato**
Qual è la dimensione tipica di un `int` su un sistema a 64 bit?

**A)** 2 byte  
**B)** 4 byte  
**C)** 8 byte  
**D)** Dipende dal compilatore  

---

### **2. Dichiarazione e Inizializzazione**
Quale delle seguenti dichiarazioni è **CORRETTA**?

**A)** `int numero = 42.5;`  
**B)** `float pi = 3.14;`  
**C)** `char lettera = 'AB';`  
**D)** `double prezzo = 19.99;`  

---

### **3. Tipi Unsigned**
Qual è il valore massimo che può contenere un `unsigned char`?

**A)** 127  
**B)** 128  
**C)** 255  
**D)** 256  

---

### **4. Conversioni di Tipo**
Cosa stampa il seguente codice?
```c
int a = 7, b = 3;
float risultato = a / b;
printf("%.2f", risultato);
```

**A)** 2.33  
**B)** 2.00  
**C)** 2.30  
**D)** Errore di compilazione  

---

### **5. Caratteri e ASCII**
Qual è il valore ASCII del carattere '0' (zero)?

**A)** 0  
**B)** 30  
**C)** 48  
**D)** 57  

---

### **6. Overflow di Variabili**
Cosa succede se si assegna il valore 300 a una variabile `char`?

**A)** Il valore viene troncato  
**B)** Si verifica un errore di compilazione  
**C)** Il programma si blocca  
**D)** Il valore diventa negativo  

---

### **7. Formattazione printf()**
Quale specificatore di formato è corretto per stampare un `long`?

**A)** `%d`  
**B)** `%l`  
**C)** `%ld`  
**D)** `%lg`  

---

### **8. Precisione dei Float**
Perché è sconsigliato confrontare due `float` con l'operatore `==`?

**A)** È sintatticamente errato  
**B)** I float hanno precisione limitata  
**C)** È troppo lento  
**D)** Non funziona con numeri negativi  

---

### **9. Costanti Letterali**
Come si dichiara una costante `float` con valore 3.14?

**A)** `3.14`  
**B)** `3.14f`  
**C)** `3.14F`  
**D)** Entrambe B e C sono corrette  

---

### **10. Operatore sizeof**
Cosa restituisce l'operatore `sizeof(char)`?

**A)** Il numero di bit  
**B)** Il numero di byte  
**C)** Sempre 1  
**D)** Dipende dal sistema  

---

### **11. Casting Esplicito**
Qual è il risultato di `(int)3.9`?

**A)** 3  
**B)** 4  
**C)** 3.0  
**D)** Errore  

---

### **12. Variabili Locali**
Quale valore ha una variabile `int` locale non inizializzata?

**A)** 0  
**B)** -1  
**C)** NULL  
**D)** Valore indeterminato  

---

## ✅ RISPOSTE E SPIEGAZIONI

<details>
<summary><strong>📋 Clicca qui per vedere le risposte</strong></summary>

### **1. Risposta: B) 4 byte**
**Spiegazione**: Su sistemi a 64 bit, un `int` è tipicamente 4 byte (32 bit). La dimensione può variare, ma 4 byte è lo standard.

### **2. Risposta: D) `double prezzo = 19.99;`**
**Spiegazione**: 
- A) Errore: assegna float a int (troncamento)
- B) Warning: dovrebbe essere `3.14f` per float
- C) Errore: char può contenere solo un carattere
- D) ✅ Corretto: double può contenere decimali

### **3. Risposta: C) 255**
**Spiegazione**: `unsigned char` usa 8 bit, range 0-255 (2^8 - 1 = 255).

### **4. Risposta: B) 2.00**
**Spiegazione**: La divisione 7/3 tra interi dà 2 (divisione intera), poi convertito a float 2.00.

### **5. Risposta: C) 48**
**Spiegazione**: Il carattere '0' ha valore ASCII 48. I caratteri '0'-'9' vanno da 48 a 57.

### **6. Risposta: A) Il valore viene troncato**
**Spiegazione**: 300 (binario: 100101100) viene troncato a 8 bit → 44 (00101100).

### **7. Risposta: C) `%ld`**
**Spiegazione**: `%ld` è lo specificatore corretto per `long`. `%d` è per `int`.

### **8. Risposta: B) I float hanno precisione limitata**
**Spiegazione**: I float hanno errori di approssimazione, quindi `0.1 + 0.2` potrebbe non essere esattamente `0.3`.

### **9. Risposta: D) Entrambe B e C sono corrette**
**Spiegazione**: Sia `3.14f` che `3.14F` indicano letterali float (minuscola e maiuscola).

### **10. Risposta: C) Sempre 1**
**Spiegazione**: Per definizione C, `sizeof(char)` è sempre 1 byte (unità base).

### **11. Risposta: A) 3**
**Spiegazione**: Il casting (int) tronca la parte decimale, non arrotonda. 3.9 → 3.

### **12. Risposta: D) Valore indeterminato**
**Spiegazione**: Le variabili locali non inizializzate contengono "spazzatura" (valori casuali in memoria).

</details>

---

## 📊 VALUTAZIONE

**Calcola il tuo punteggio:**
- ✅ **11-12 corrette**: Eccellente! Padroneggi i tipi di dato
- ✅ **9-10 corrette**: Molto bene! Qualche piccola lacuna
- ⚠️ **7-8 corrette**: Buono, ma studia ancora
- ❌ **< 7 corrette**: Ripassa la teoria e riprova

---

## 🎯 AREE DI MIGLIORAMENTO

Se hai sbagliato domande su:

**🔢 Dimensioni e Range** (Dom. 1, 3, 10)
→ Studia la tabella dei tipi di dato e usa `sizeof()`

**🔄 Conversioni** (Dom. 2, 4, 11)
→ Pratica con casting esplicito e implicito

**📝 Formattazione** (Dom. 7, 9)
→ Memorizza gli specificatori printf() corretti

**⚠️ Comportamenti Critici** (Dom. 6, 8, 12)
→ Attenzione a overflow, precisione e inizializzazione

---

## 🚀 PROSSIMI PASSI

1. **✅ Se hai fatto bene**: Passa alla Lezione 03 (Operatori)
2. **📖 Se hai difficoltà**: Rileggi la teoria e rifai gli esercizi
3. **🔄 Per approfondire**: Sperimenta con programmi che usano tutti i tipi

---

## 💡 SUGGERIMENTI PER LO STUDIO

- 🧪 **Sperimenta**: Prova diverse combinazioni di tipi
- 📏 **Misura**: Usa `sizeof()` per vedere le dimensioni reali
- ⚠️ **Testa i limiti**: Prova valori estremi per capire overflow
- 🔍 **Debug**: Usa printf() per vedere cosa contengono le variabili

---

> **💪 Ricorda**: La programmazione si impara praticando!  
> **🎯 Obiettivo**: Non memorizzare, ma capire i concetti!
