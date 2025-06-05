# Quiz - Modulo B: Problemi ed Algoritmi

## 📚 **Informazioni Generali**

- **Modulo**: B - Problemi ed Algoritmi  
- **Tempo stimato**: 45 minuti
- **Domande totali**: 20
- **Tipologie**: Scelta multipla, Vero/Falso, Completamento, Analisi di codice
- **Punteggio**: 100 punti (5 punti per domanda)

---

## ❓ **SEZIONE 1: Metodologia di Risoluzione dei Problemi** (25 punti)

### **Domanda 1** (5 punti)
Quali sono i **6 passi** della metodologia di risoluzione dei problemi studiata?

**A)** Analisi → Progettazione → Implementazione → Testing → Documentazione → Manutenzione  
**B)** Comprensione → Specifiche → Progettazione → Implementazione → Testing → Documentazione  
**C)** Input → Elaborazione → Output → Verifica → Ottimizzazione → Deployment  
**D)** Problema → Algoritmo → Codice → Test → Debug → Rilascio  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

I 6 passi della metodologia sono:
1. **Comprensione del problema** - Capire cosa viene richiesto
2. **Specifiche di input/output** - Definire dati in ingresso e risultati attesi  
3. **Progettazione dell'algoritmo** - Creare la strategia risolutiva
4. **Implementazione** - Tradurre l'algoritmo in codice
5. **Testing** - Verificare la correttezza con casi di test
6. **Documentazione** - Spiegare il funzionamento e l'utilizzo

</details>

---

### **Domanda 2** (5 punti)
Nel passo di **analisi del problema**, cosa è più importante identificare **per primo**?

**A)** La complessità computazionale dell'algoritmo  
**B)** Il linguaggio di programmazione da utilizzare  
**C)** Gli input, output e vincoli del problema  
**D)** Le strutture dati più appropriate  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: C**

Prima di progettare qualsiasi soluzione, è fondamentale capire:
- **Input**: Che dati ricevo in ingresso?
- **Output**: Che risultato devo produrre?  
- **Vincoli**: Quali limitazioni o condizioni speciali esistono?

Solo dopo aver chiarito questi aspetti si può procedere con la progettazione dell'algoritmo.

</details>

---

### **Domanda 3** (5 punti)
**Vero o Falso**: È sempre necessario implementare la soluzione più efficiente possibile, anche se più complessa.

**A)** Vero  
**B)** Falso  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B (Falso)**

Non sempre la soluzione più efficiente è la migliore scelta. Fattori da considerare:
- **Leggibilità** e manutenibilità del codice
- **Tempo di sviluppo** disponibile
- **Dimensione dei dati** effettivamente elaborati
- **Frequenza di utilizzo** dell'algoritmo

A volte una soluzione semplice e chiara è preferibile a una complessa ma marginalmente più veloce.

</details>

---

### **Domanda 4** (5 punti)
Qual è il **principale beneficio** della fase di testing sistematico?

**A)** Misurare le prestazioni dell'algoritmo  
**B)** Verificare la correttezza su diversi casi, inclusi quelli limite  
**C)** Ottimizzare l'uso della memoria  
**D)** Migliorare la leggibilità del codice  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

Il testing sistematico serve principalmente a **verificare la correttezza** dell'implementazione attraverso:
- **Casi normali**: Input tipici e situazioni standard
- **Casi limite**: Valori minimi, massimi, array vuoti, ecc.
- **Casi di errore**: Input non validi o situazioni eccezionali

Questo garantisce che l'algoritmo funzioni correttamente in tutte le situazioni previste.

</details>

---

### **Domanda 5** (5 punti)
Completare la frase: "Un algoritmo deve sempre essere _____, _____ e _____."

**Risposta**:
1. ________________
2. ________________  
3. ________________

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposte corrette** (in ordine variabile):
1. **Finito** - deve terminare in un numero finito di passi
2. **Definito** - ogni passo deve essere precisamente specificato  
3. **Efficace** - ogni operazione deve essere eseguibile

Altre proprietà accettabili: deterministico, corretto, generale.

</details>

---

## ❓ **SEZIONE 2: Algoritmi di Ordinamento** (25 punti)

### **Domanda 6** (5 punti)
Qual è la **complessità temporale nel caso peggiore** del Bubble Sort?

**A)** O(n)  
**B)** O(n log n)  
**C)** O(n²)  
**D)** O(2ⁿ)  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: C**

Bubble Sort ha complessità **O(n²)** nel caso peggiore perché:
- Loop esterno: n-1 iterazioni
- Loop interno: fino a n-1 confronti per iterazione
- Totale: (n-1) × (n-1) ≈ n² operazioni

Questo accade quando l'array è ordinato al contrario.

</details>

---

### **Domanda 7** (5 punti)
Quale algoritmo di ordinamento è **stabile**?

**A)** Selection Sort  
**B)** Quick Sort  
**C)** Heap Sort  
**D)** Bubble Sort  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: D**

Un algoritmo è **stabile** se mantiene l'ordine relativo di elementi con lo stesso valore.

- **Bubble Sort**: ✅ Stabile - scambia solo se elementi sono in ordine stretto (>)
- **Selection Sort**: ❌ Non stabile - può alterare l'ordine di elementi uguali
- **Quick Sort**: ❌ Generalmente non stabile  
- **Heap Sort**: ❌ Non stabile

</details>

---

### **Domanda 8** (5 punti)
**Analisi di codice**: Cosa fa questo frammento di Insertion Sort?

```java
int key = array[i];
int j = i - 1;
while (j >= 0 && array[j] > key) {
    array[j + 1] = array[j];
    j--;
}
array[j + 1] = key;
```

**A)** Trova l'elemento minimo nell'array  
**B)** Scambia elementi adiacenti se non ordinati  
**C)** Inserisce l'elemento corrente nella posizione corretta nella parte già ordinata  
**D)** Divide l'array in due parti  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: C**

Questo codice implementa il **cuore dell'Insertion Sort**:
1. `key = array[i]` - salva l'elemento da inserire
2. `j = i - 1` - inizia dalla posizione precedente  
3. `while (j >= 0 && array[j] > key)` - sposta elementi maggiori a destra
4. `array[j + 1] = key` - inserisce l'elemento nella posizione corretta

L'elemento viene inserito nella posizione giusta all'interno della parte già ordinata dell'array.

</details>

---

### **Domanda 9** (5 punti)
Quale algoritmo di ordinamento ha la **migliore complessità nel caso peggiore**?

**A)** Bubble Sort: O(n²)  
**B)** Quick Sort: O(n²)  
**C)** Merge Sort: O(n log n)  
**D)** Selection Sort: O(n²)  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: C**

**Merge Sort** garantisce sempre **O(n log n)** anche nel caso peggiore perché:
- Divide sempre l'array esattamente a metà
- Il numero di livelli è sempre log n
- Ogni livello richiede O(n) operazioni per il merge
- Totale: O(n log n) garantito

Gli altri algoritmi hanno O(n²) nel caso peggiore.

</details>

---

### **Domanda 10** (5 punti)
**Vero o Falso**: Selection Sort effettua sempre lo stesso numero di confronti, indipendentemente dall'ordinamento iniziale dell'array.

**A)** Vero  
**B)** Falso  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: A (Vero)**

Selection Sort ha **sempre** la stessa complessità O(n²) perché:
- Cerca sempre l'elemento minimo in tutta la parte non ordinata
- Non si ferma mai anticipatamente
- Indipendentemente dai dati, fa sempre n×(n-1)/2 confronti

A differenza del Bubble Sort ottimizzato, non può terminare prima.

</details>

---

## ❓ **SEZIONE 3: Algoritmi di Ricerca** (25 punti)

### **Domanda 11** (5 punti)
Qual è il **prerequisito fondamentale** per utilizzare la ricerca binaria?

**A)** L'array deve contenere solo numeri positivi  
**B)** L'array deve essere ordinato  
**C)** L'array deve avere dimensione potenza di 2  
**D)** L'array non deve contenere duplicati  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

La **ricerca binaria** funziona solo su array **ordinati** perché:
- Si basa sul principio di scartare metà dell'array ad ogni passo
- Confronta l'elemento centrale per decidere in quale metà cercare
- Questo è possibile solo se gli elementi sono in ordine

Senza ordinamento, non si può decidere quale metà esplorare.

</details>

---

### **Domanda 12** (5 punti)
Quanti confronti **al massimo** effettua la ricerca binaria in un array di 1000 elementi?

**A)** 1000  
**B)** 500  
**C)** 100  
**D)** 10  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: D**

La ricerca binaria effettua al massimo **⌊log₂(n)⌋ + 1** confronti.

Per n = 1000:
- log₂(1000) ≈ 9.97
- ⌊9.97⌋ + 1 = 10 confronti

Ad ogni passo dimezza lo spazio di ricerca: 1000 → 500 → 250 → 125 → 62 → 31 → 15 → 7 → 3 → 1

</details>

---

### **Domanda 13** (5 punti)
**Analisi di codice**: Questo frammento di ricerca binaria ha un errore. Quale?

```java
int mid = (left + right) / 2;
```

**A)** Dovrebbe essere (left + right) * 2  
**B)** Può causare overflow per valori grandi di left e right  
**C)** Non considera il caso left > right  
**D)** Non c'è nessun errore  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

Il calcolo `(left + right) / 2` può causare **overflow** se left e right sono molto grandi e la loro somma supera il valore massimo degli interi.

**Soluzione corretta**:
```java
int mid = left + (right - left) / 2;
```

Questo evita l'overflow calcolando la distanza e aggiungendola a left.

</details>

---

### **Domanda 14** (5 punti)
In quale scenario la **ricerca lineare** è preferibile alla ricerca binaria?

**A)** Mai, la ricerca binaria è sempre migliore  
**B)** Quando l'array non è ordinato  
**C)** Quando l'array è molto grande  
**D)** Quando cerchiamo sempre l'ultimo elemento  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

La **ricerca lineare** è preferibile quando:
- L'array **non è ordinato** (ricerca binaria impossibile)
- Il costo di ordinamento supera il beneficio della ricerca più veloce
- Si effettuano poche ricerche su dati che cambiano spesso
- Si cerca il primo elemento che soddisfa una condizione generica

</details>

---

### **Domanda 15** (5 punti)
Completare il confronto delle complessità:

| Algoritmo | Complessità |
|-----------|-------------|
| Ricerca Lineare | O(____) |
| Ricerca Binaria | O(____) |
| Ricerca in Hash Table | O(____) |

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposte corrette**:

| Algoritmo | Complessità |
|-----------|-------------|
| Ricerca Lineare | **O(n)** |
| Ricerca Binaria | **O(log n)** |
| Ricerca in Hash Table | **O(1)** medio |

- **Lineare**: Controlla ogni elemento sequenzialmente
- **Binaria**: Dimezza lo spazio ad ogni passo  
- **Hash Table**: Accesso diretto tramite funzione hash

</details>

---

## ❓ **SEZIONE 4: Complessità Computazionale** (25 punti)

### **Domanda 16** (5 punti)
Ordina le seguenti complessità dalla **più efficiente** alla **meno efficiente**:

1. O(n²)
2. O(1) 
3. O(n log n)
4. O(n)
5. O(log n)

**Ordine**: _____ → _____ → _____ → _____ → _____

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Ordine corretto**: **2 → 5 → 4 → 3 → 1**

Dal più efficiente al meno efficiente:
1. **O(1)** - Costante
2. **O(log n)** - Logaritmica  
3. **O(n)** - Lineare
4. **O(n log n)** - Linearitmica
5. **O(n²)** - Quadratica

Ogni livello cresce significativamente più velocemente del precedente.

</details>

---

### **Domanda 17** (5 punti)
Qual è la complessità di questo codice?

```java
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (array[i] == array[j]) {
            System.out.println("Duplicato trovato");
        }
    }
}
```

**A)** O(n)  
**B)** O(n log n)  
**C)** O(n²)  
**D)** O(2ⁿ)  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: C**

Il codice ha complessità **O(n²)** perché:
- Loop esterno: n iterazioni (i da 0 a n-1)
- Loop interno: n iterazioni per ogni i (j da 0 a n-1)  
- Operazione interna: O(1) - confronto semplice
- Totale: n × n × O(1) = O(n²)

</details>

---

### **Domanda 18** (5 punti)
**Vero o Falso**: Un algoritmo O(n²) è sempre più lento di uno O(n log n) per qualsiasi valore di n.

**A)** Vero  
**B)** Falso  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B (Falso)**

Per **valori piccoli di n**, un algoritmo O(n²) può essere più veloce di uno O(n log n) a causa:
- **Costanti moltiplicative** diverse
- **Overhead** minore nell'implementazione semplice
- **Dimensioni ridotte** dove la differenza asintotica non è evidente

Esempio: Insertion Sort O(n²) è spesso più veloce di Merge Sort O(n log n) per array sotto 50 elementi.

</details>

---

### **Domanda 19** (5 punti)
Cosa significa che un algoritmo ha complessità spaziale O(1)?

**A)** Usa sempre 1 byte di memoria  
**B)** Usa memoria costante, indipendente dalla dimensione dell'input  
**C)** Esegue sempre in 1 millisecondo  
**D)** Ha sempre 1 operazione  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

**Complessità spaziale O(1)** significa che l'algoritmo usa una quantità **costante** di memoria aggiuntiva, indipendentemente dalla dimensione dell'input.

Esempi:
- **Bubble Sort in-place**: O(1) spazio (solo variabili per scambi)
- **Ricerca lineare**: O(1) spazio (solo indici e variabili temporanee)

Non significa letteralmente 1 byte, ma una quantità fissa che non cresce con n.

</details>

---

### **Domanda 20** (5 punti)
Quale tecnica può trasformare un algoritmo ricorsivo O(2ⁿ) in uno O(n)?

**A)** Iterazione invece di ricorsione  
**B)** Memoization (memorizzazione dei risultati)  
**C)** Uso di strutture dati più efficienti  
**D)** Parallelizzazione  

<details>
<summary>💡 <b>Risposta e Spiegazione</b></summary>

**Risposta corretta: B**

La **memoization** evita di ricalcolare gli stessi sottoproblemi memorizzando i risultati già calcolati.

Esempio con Fibonacci:
- **Ricorsivo naive**: O(2ⁿ) - ricalcola gli stessi valori molte volte
- **Con memoization**: O(n) - calcola ogni valore solo una volta

Questa è la base della **programmazione dinamica**.

</details>

---

## 📊 **Tabella dei Punteggi**

| Sezione | Domande | Punteggio Totale |
|---------|---------|------------------|
| Metodologia | 1-5 | 25 punti |
| Ordinamento | 6-10 | 25 punti |
| Ricerca | 11-15 | 25 punti |
| Complessità | 16-20 | 25 punti |
| **TOTALE** | **20** | **100 punti** |

### **Livelli di Valutazione**:
- **90-100 punti**: Eccellente 🏆
- **80-89 punti**: Buono 🥈  
- **70-79 punti**: Sufficiente ✅
- **60-69 punti**: Da rivedere ⚠️
- **< 60 punti**: Insufficiente ❌

---

## 🎯 **Suggerimenti per lo Studio**

1. **Rivedere teoria**: Concentrarsi sui concetti fondamentali
2. **Praticare implementazioni**: Scrivere algoritmi da zero
3. **Analizzare complessità**: Esercitarsi nel calcolo di Big O
4. **Testare algoritmi**: Verificare comportamento su casi diversi
5. **Confrontare prestazioni**: Misurare tempi di esecuzione empirici

---

## 🔗 **Prossimi Passi**

- **Se punteggio ≥ 80**: Procedere al [Modulo C](../../C-Dati_assegnazione_IO/)
- **Se punteggio < 80**: Rivedere [teoria](../teoria/) ed [esempi](../esempi/)
- **Per approfondimenti**: Svolgere [esercizi avanzati](../esercizi/)

---

*Questo quiz valuta la comprensione teorica e pratica degli algoritmi fondamentali e della loro analisi.*
