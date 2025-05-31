# 🧪 QUIZ INTERATTIVO - Lezione 03: Operatori

## 📊 Informazioni Quiz
- **Argomento**: Operatori in C (Aritmetici, Logici, Bit a Bit)
- **Difficoltà**: ⭐⭐⭐ Intermedio
- **Tempo stimato**: 20-30 minuti
- **Domande**: 15 domande progressive
- **Tipologie**: Scelta multipla, Vero/Falso, Codice da completare

---

## 🎯 Obiettivi di Apprendimento
Al termine di questo quiz saprai:
- ✅ Utilizzare correttamente tutti gli operatori C
- ✅ Applicare la precedenza degli operatori
- ✅ Manipolare dati con operatori bit a bit
- ✅ Combinare operatori logici per condizioni complesse
- ✅ Risolvere espressioni matematiche e logiche

---

## ❓ DOMANDE

### 📝 Domanda 1: Precedenza Operatori Aritmetici
Quale è il risultato dell'espressione: `5 + 3 * 2`?

**A)** 16  
**B)** 11  
**C)** 10  
**D)** 8  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) 11**

**Spiegazione:**
- La moltiplicazione (`*`) ha precedenza maggiore dell'addizione (`+`)
- Quindi: `5 + 3 * 2` = `5 + (3 * 2)` = `5 + 6` = `11`
- Per ottenere 16 servirebbe: `(5 + 3) * 2`

**💡 Regola da ricordare:** 
Precedenza operatori: `()` > `* / %` > `+ -`
</details>

---

### 📝 Domanda 2: Operatori di Incremento/Decremento
Dato il codice:
```c
int a = 5;
int result = ++a + a--;
```
Quali sono i valori finali di `a` e `result`?

**A)** a = 5, result = 10  
**B)** a = 5, result = 11  
**C)** a = 5, result = 12  
**D)** a = 4, result = 12  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: C) a = 5, result = 12**

**Spiegazione passo per passo:**
1. `++a`: pre-incremento → a diventa 6, si usa 6
2. `a--`: post-decremento → si usa 6, poi a diventa 5
3. `result = 6 + 6 = 12`
4. Valore finale: a = 5, result = 12

**💡 Differenza cruciale:**
- `++a`: incrementa PRIMA di usare
- `a++`: usa PRIMA di incrementare
</details>

---

### 📝 Domanda 3: Operatore Ternario
Cosa stampa questo codice?
```c
int x = 10, y = 20;
printf("%d", x > y ? x * 2 : y / 2);
```

**A)** 10  
**B)** 20  
**C)** 40  
**D)** 5  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: A) 10**

**Spiegazione:**
- Condizione: `x > y` → `10 > 20` → `false`
- Operatore ternario: `condizione ? valore_se_vero : valore_se_falso`
- Dato che la condizione è falsa, si esegue: `y / 2` = `20 / 2` = `10`

**💡 Sintassi ternario:** `(condizione) ? espressione1 : espressione2`
</details>

---

### 📝 Domanda 4: Operatori Logici - Vero o Falso?
**Affermazione:** In C, l'espressione `(1 && 0) || (5 > 3)` restituisce `true` (valore diverso da 0).

**A)** Vero  
**B)** Falso  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: A) Vero**

**Spiegazione:**
- `(1 && 0)` = `false` (AND logico: entrambi devono essere veri)
- `(5 > 3)` = `true` (5 è maggiore di 3)
- `false || true` = `true` (OR logico: almeno uno deve essere vero)

**💡 Short-circuit evaluation:**
- In `A && B`: se A è falso, B non viene valutato
- In `A || B`: se A è vero, B non viene valutato
</details>

---

### 📝 Domanda 5: Operatori Bit a Bit - AND
Qual è il risultato di `0x5A & 0x3C` in esadecimale?

**A)** 0x7E  
**B)** 0x18  
**C)** 0x66  
**D)** 0x42  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) 0x18**

**Spiegazione bit per bit:**
```
0x5A = 01011010
0x3C = 00111100
       --------  AND (&)
       00011000 = 0x18
```

**💡 Operatore AND (&):**
- 1 & 1 = 1
- 1 & 0 = 0
- 0 & 1 = 0
- 0 & 0 = 0
</details>

---

### 📝 Domanda 6: Operatori Bit a Bit - OR
Cosa restituisce `0xF0 | 0x0F`?

**A)** 0x00  
**B)** 0xFF  
**C)** 0xF0  
**D)** 0x0F  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) 0xFF**

**Spiegazione:**
```
0xF0 = 11110000
0x0F = 00001111
       --------  OR (|)
       11111111 = 0xFF
```

**💡 Operatore OR (|):**
Restituisce 1 se almeno un bit è 1, quindi combina i pattern.
</details>

---

### 📝 Domanda 7: Shift Operations
Qual è il risultato di `8 << 2`?

**A)** 2  
**B)** 16  
**C)** 32  
**D)** 4  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: C) 32**

**Spiegazione:**
- `8` in binario: `1000`
- `8 << 2`: sposta 2 posizioni a sinistra → `100000` = 32
- Ogni shift a sinistra moltiplica per 2
- `8 << 2` = `8 * 2² = 8 * 4 = 32`

**💡 Shift left (<<):** Moltiplicazione efficiente per potenze di 2
</details>

---

### 📝 Domanda 8: Operatore Modulo
Cosa stampa `printf("%d", 17 % 5)`?

**A)** 3  
**B)** 2  
**C)** 4  
**D)** 5  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) 2**

**Spiegazione:**
- L'operatore modulo (%) restituisce il resto della divisione
- `17 ÷ 5 = 3` con resto `2`
- Quindi `17 % 5 = 2`

**💡 Uso comune:** Verificare parità con `n % 2` (0=pari, 1=dispari)
</details>

---

### 📝 Domanda 9: Precedenza Complessa
Qual è l'ordine di valutazione in: `a + b * c && d > e`?

**A)** `((a + b) * c) && (d > e)`  
**B)** `(a + (b * c)) && (d > e)`  
**C)** `a + ((b * c) && (d > e))`  
**D)** `(a + b) * (c && d) > e`  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) `(a + (b * c)) && (d > e)`**

**Spiegazione della precedenza:**
1. `*` (moltiplicazione) - più alta
2. `+` (addizione)
3. `>` (relazionale)
4. `&&` (AND logico) - più bassa

**💡 Precedenza operatori (alta → bassa):**
`() > ++ -- > * / % > + - > < > <= >= > == != > && > ||`
</details>

---

### 📝 Domanda 10: XOR Operation
Cosa succede con `a ^= a` dove `a` è qualsiasi valore?

**A)** `a` raddoppia  
**B)** `a` diventa 0  
**C)** `a` rimane uguale  
**D)** `a` diventa -1  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) `a` diventa 0**

**Spiegazione:**
- `a ^= a` è equivalente a `a = a ^ a`
- XOR di un numero con se stesso è sempre 0
- Esempio: `5 ^ 5 = 101 ^ 101 = 000 = 0`

**💡 Proprietà XOR:**
- `a ^ 0 = a` (identità)
- `a ^ a = 0` (annullamento)
- `a ^ b ^ b = a` (usato per swap senza variabile temp)
</details>

---

### 📝 Domanda 11: Operatori di Assegnazione Composti
Se `x = 10`, qual è il valore di `x` dopo `x *= 3 + 2`?

**A)** 32  
**B)** 50  
**C)** 15  
**D)** 35  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) 50**

**Spiegazione:**
- `x *= 3 + 2` è equivalente a `x = x * (3 + 2)`
- Prima si valuta `3 + 2 = 5`
- Poi: `x = 10 * 5 = 50`

**💡 Operatori composti:** `+=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=`
</details>

---

### 📝 Domanda 12: Manipolazione Pixel RGB
Per estrarre il canale rosso da un pixel RGB (formato 0xRRGGBB), quale operazione usi?

**A)** `pixel & 0xFF`  
**B)** `(pixel >> 16) & 0xFF`  
**C)** `pixel | 0xFF0000`  
**D)** `pixel << 16`  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) `(pixel >> 16) & 0xFF`**

**Spiegazione:**
- In formato 0xRRGGBB, il rosso occupa i bit 23-16
- `>> 16`: sposta il rosso nelle posizioni 7-0
- `& 0xFF`: maschera per tenere solo gli 8 bit meno significativi

**💡 Estrazione canali RGB:**
- Rosso: `(pixel >> 16) & 0xFF`
- Verde: `(pixel >> 8) & 0xFF`
- Blu: `pixel & 0xFF`
</details>

---

### 📝 Domanda 13: Controllo Condizioni Multiple
Per verificare che un numero sia nell'intervallo [10, 20], quale espressione è corretta?

**A)** `10 <= x <= 20`  
**B)** `x >= 10 && x <= 20`  
**C)** `x >= 10 || x <= 20`  
**D)** `!(x < 10 || x > 20)`  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) `x >= 10 && x <= 20` (e anche D!)**

**Spiegazione:**
- L'opzione A non è valida in C (non si possono concatenare confronti)
- L'opzione B: entrambe le condizioni devono essere vere (AND)
- L'opzione C: sarebbe sempre vera (OR)
- L'opzione D: usando De Morgan, è equivalente alla B

**💡 Leggi di De Morgan:**
- `!(A && B) = !A || !B`
- `!(A || B) = !A && !B`
</details>

---

### 📝 Domanda 14: Codice da Completare
Completa il codice per scambiare due variabili usando XOR:
```c
void swap_xor(int *a, int *b) {
    *a = *a ^ *b;
    *b = _____;
    *a = _____;
}
```

**A)** `*b = *a ^ *b; *a = *a ^ *b;`  
**B)** `*b = *b ^ *a; *a = *b ^ *a;`  
**C)** `*b = *a ^ *b; *a = *b ^ *a;`  
**D)** Tutte le precedenti sono corrette  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: A), B) e C) - Tutte corrette!**

**Spiegazione della tecnica XOR swap:**
```c
// Stato iniziale: a=A, b=B
*a = *a ^ *b;  // a = A^B, b = B
*b = *a ^ *b;  // a = A^B, b = (A^B)^B = A
*a = *a ^ *b;  // a = (A^B)^A = B, b = A
```

**💡 Vantaggio:** Nessuna variabile temporanea necessaria
**⚠️ Attenzione:** Non funziona se a e b puntano alla stessa locazione!
</details>

---

### 📝 Domanda 15: Ottimizzazione con Operatori Bit
Quale è il modo più efficiente per verificare se un numero è pari?

**A)** `n % 2 == 0`  
**B)** `(n & 1) == 0`  
**C)** `n / 2 * 2 == n`  
**D)** `!(n % 2)`  

<details>
<summary>🔍 <strong>Risposta e Spiegazione</strong></summary>

**Risposta corretta: B) `(n & 1) == 0`**

**Spiegazione:**
- L'operazione AND con 1 controlla solo l'ultimo bit
- Se l'ultimo bit è 0 → numero pari
- Se l'ultimo bit è 1 → numero dispari
- È più veloce del modulo (%) che richiede divisione

**💡 Ottimizzazioni comuni con bit:**
- Parità: `n & 1`
- Potenza di 2: `(n & (n-1)) == 0`
- Moltiplicazione per 2^k: `n << k`
- Divisione per 2^k: `n >> k`
</details>

---

## 🏆 VALUTAZIONE FINALE

### 📊 Calcola il tuo punteggio:
- **13-15 risposte corrette**: 🥇 **ECCELLENTE** - Maestria completa degli operatori!
- **10-12 risposte corrette**: 🥈 **MOLTO BUONO** - Ottima conoscenza, piccoli dettagli da rivedere
- **7-9 risposte corrette**: 🥉 **BUONO** - Base solida, continua a praticare
- **4-6 risposte corrette**: 📚 **SUFFICIENTE** - Rivedere i concetti fondamentali
- **0-3 risposte corrette**: 🔄 **DA RIVEDERE** - Studiare di nuovo la lezione

---

## 🎯 PROSSIMI PASSI

### ✅ Se hai ottenuto un buon punteggio:
- Passa alla **Lezione 04: Strutture di Controllo**
- Prova gli esercizi avanzati sui bit manipulation
- Sperimenta con progetti di image processing

### 📚 Se devi migliorare:
- Rileggi la teoria sugli operatori
- Pratica con gli esempi interattivi
- Rifai gli esercizi con focus su aree deboli
- Consulta la documentazione di riferimento

### 💡 Suggerimenti per il consolidamento:
1. **Pratica quotidiana**: 15 minuti al giorno con operatori bit
2. **Progetti pratici**: Crea una calcolatrice o un editor di immagini semplice
3. **Code review**: Analizza codice esistente per riconoscere pattern
4. **Debugging**: Usa il debugger per vedere step-by-step le operazioni

---

## 📖 RISORSE AGGIUNTIVE

### 🔗 Link Utili:
- [Precedenza Operatori C - Reference](https://en.cppreference.com/w/c/language/operator_precedence)
- [Bit Manipulation Techniques](https://graphics.stanford.edu/~seander/bithacks.html)
- [Visual Bit Operations](https://bits.stephan-brumme.com/)

### 📱 Tools Online:
- Convertitore binario/hex/decimale
- Simulatore operazioni bit a bit
- Calcolatore precedenza operatori

---

**🎉 Congratulazioni per aver completato il quiz!**  
*Continua così e diventerai un esperto programmatore C!*

---

*Quiz creato per il corso "C by Example" - Lezione 03: Operatori*  
*Versione 1.0 - © 2024*
