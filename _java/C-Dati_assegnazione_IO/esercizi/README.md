# Esercizi - Modulo C: Dati, Assegnazione e I/O

## Panoramica
Questa sezione contiene esercizi progressivi per consolidare i concetti del Modulo C:
- Tipi di dati primitivi e conversioni
- Variabili, costanti e operatori
- Input/Output e validazione dati

## Struttura degli Esercizi

### 🏃‍♂️ Livello Base (Esercizi 1-5)
**Obiettivo**: Familiarizzare con tipi di dati e operazioni base

### 🚶‍♀️ Livello Intermedio (Esercizi 6-10)
**Obiettivo**: Applicare conversioni e operatori complessi

### 🏋️‍♂️ Livello Avanzato (Esercizi 11-15)
**Obiettivo**: Integrare I/O, validazione e logica complessa

---

## 📚 Esercizi Base (1-5)

### Esercizio 1: Calcolatore di Statistiche Personali
**Difficoltà**: ⭐
**Concetti**: Tipi primitivi, input base, operazioni aritmetiche

**Descrizione**: 
Creare un programma che richieda all'utente i suoi dati personali e calcoli alcune statistiche.

**Specifiche**:
- Nome (String)
- Età (int)
- Altezza in cm (double)
- Peso in kg (double)
- Calcolare e mostrare l'IMC (Indice di Massa Corporea)
- Determinare se l'utente è maggiorenne

**File**: `Esercizio01_StatistichePersonali.java`

---

### Esercizio 2: Convertitore di Temperature
**Difficoltà**: ⭐
**Concetti**: Conversioni tra tipi, operazioni matematiche, formattazione output

**Descrizione**: 
Creare un convertitore che trasformi temperature tra Celsius, Fahrenheit e Kelvin.

**Specifiche**:
- Input: temperatura e unità di partenza
- Output: temperatura nelle altre due unità
- Formule: C = (F-32) * 5/9; K = C + 273.15
- Utilizzare `printf` per formattazione

**File**: `Esercizio02_ConvertitoreTemperature.java`

---

### Esercizio 3: Calcolatore di Sconto
**Difficoltà**: ⭐⭐
**Concetti**: Operatori aritmetici, condizioni, casting

**Descrizione**: 
Sistema per calcolare sconti su acquisti con diverse percentuali.

**Specifiche**:
- Prezzo originale (double)
- Percentuale sconto (int)
- Calcolare prezzo scontato e risparmio
- Usare casting appropriato per visualizzazione

**File**: `Esercizio03_CalcolatoreSconto.java`

---

### Esercizio 4: Analizzatore di Caratteri
**Difficoltà**: ⭐⭐
**Concetti**: Tipo char, ASCII, operatori logici

**Descrizione**: 
Programma che analizza un carattere inserito dall'utente.

**Specifiche**:
- Input: un carattere
- Determinare se è:
  - Lettera (maiuscola/minuscola)
  - Cifra numerica
  - Carattere speciale
- Mostrare il valore ASCII

**File**: `Esercizio04_AnalizzatoreCaratteri.java`

---

### Esercizio 5: Calcolatore di Tempo
**Difficoltà**: ⭐⭐
**Concetti**: Operatori aritmetici e modulo, conversioni

**Descrizione**: 
Convertire secondi in ore, minuti e secondi rimanenti.

**Specifiche**:
- Input: numero di secondi (long)
- Output: formato HH:MM:SS
- Gestire valori grandi (oltre 24 ore)

**File**: `Esercizio05_CalcolatoreTempo.java`

---

## 🚶‍♀️ Esercizi Intermedi (6-10)

### Esercizio 6: Validatore di Dati
**Difficoltà**: ⭐⭐⭐
**Concetti**: Input validation, cicli, operatori logici

**Descrizione**: 
Sistema di registrazione con validazione completa dei dati.

**Specifiche**:
- Email (deve contenere @ e .)
- Età (18-120)
- Codice fiscale (16 caratteri alfanumerici)
- Continuare finché i dati non sono validi

**File**: `Esercizio06_ValidatoreDati.java`

---

### Esercizio 7: Sistema di Voti
**Difficoltà**: ⭐⭐⭐
**Concetti**: Array, media, casting, formattazione

**Descrizione**: 
Gestire voti di uno studente e calcolare statistiche.

**Specifiche**:
- Inserire 5 voti (double)
- Calcolare media, voto massimo e minimo
- Determinare se promosso (media >= 6.0)
- Formattare output con 2 decimali

**File**: `Esercizio07_SistemaVoti.java`

---

### Esercizio 8: Convertitore di Valute
**Difficoltà**: ⭐⭐⭐
**Concetti**: Switch, operazioni matematiche, precisione decimale

**Descrizione**: 
Convertitore multi-valuta con menu di selezione.

**Specifiche**:
- Menu per scegliere conversione
- Tassi di cambio fissi (EUR, USD, GBP, JPY)
- Gestire arrotondamento a 2 decimali
- Opzione per multiple conversioni

**File**: `Esercizio08_ConvertitoreValute.java`

---

### Esercizio 9: Analizzatore di Stringa
**Difficoltà**: ⭐⭐⭐
**Concetti**: String manipulation, char operations, contatori

**Descrizione**: 
Analizzare una stringa e produrre statistiche dettagliate.

**Specifiche**:
- Input: frase dell'utente
- Contare: caratteri totali, lettere, cifre, spazi, punteggiatura
- Trovare carattere più frequente
- Determinare se palindromo (bonus)

**File**: `Esercizio09_AnalizzatoreStringa.java`

---

### Esercizio 10: Calcolatore Scientifico Base
**Difficoltà**: ⭐⭐⭐
**Concetti**: Math class, operatori, menu, error handling

**Descrizione**: 
Calcolatore con operazioni matematiche avanzate.

**Specifiche**:
- Menu con operazioni: +, -, *, /, %, potenza, radice, log
- Gestire divisione per zero
- Utilizzare Math class appropriatamente
- Continuare finché utente non esce

**File**: `Esercizio10_CalcolatoreScientificoBase.java`

---

## 🏋️‍♂️ Esercizi Avanzati (11-15)

### Esercizio 11: Sistema di Login
**Difficoltà**: ⭐⭐⭐⭐
**Concetti**: String comparison, tentativi limitati, sicurezza base

**Descrizione**: 
Sistema di autenticazione con tentativi limitati.

**Specifiche**:
- Username e password predefiniti
- Massimo 3 tentativi
- Bloccare account dopo tentativi falliti
- Messaggi di errore specifici

**File**: `Esercizio11_SistemaLogin.java`

---

### Esercizio 12: Gestione Conto Bancario
**Difficoltà**: ⭐⭐⭐⭐
**Concetti**: Operazioni su double, precisione, menu complesso

**Descrizione**: 
Simulatore di conto bancario con operazioni multiple.

**Specifiche**:
- Saldo iniziale
- Operazioni: deposito, prelievo, controllo saldo
- Validazione importi (non negativi, non superiori al saldo)
- Storico ultime 5 operazioni

**File**: `Esercizio12_GestioneContoBancario.java`

---

### Esercizio 13: Generatore di Password
**Difficoltà**: ⭐⭐⭐⭐
**Concetti**: Random, char manipulation, criteri complessi

**Descrizione**: 
Generare password sicure secondo criteri specifici.

**Specifiche**:
- Lunghezza configurabile (8-50 caratteri)
- Includere: maiuscole, minuscole, numeri, simboli
- Almeno uno di ogni tipo richiesto
- Validatore di forza password

**File**: `Esercizio13_GeneratorePassword.java`

---

### Esercizio 14: Sistema di Prenotazioni
**Difficoltà**: ⭐⭐⭐⭐⭐
**Concetti**: Input complesso, validazione date, logica business

**Descrizione**: 
Sistema per prenotare posti in un cinema.

**Specifiche**:
- Griglia posti 10x10 (char array)
- Visualizzare posti disponibili/occupati
- Prenotare posto specificando fila e numero
- Calcolare prezzo in base alla posizione
- Riepilogo prenotazione

**File**: `Esercizio14_SistemaPrenotazioni.java`

---

### Esercizio 15: Analizzatore di File Log
**Difficoltà**: ⭐⭐⭐⭐⭐
**Concetti**: File I/O, parsing, statistiche, exception handling

**Descrizione**: 
Analizzare un file di log e produrre report statistici.

**Specifiche**:
- Leggere file con log (formato: timestamp, livello, messaggio)
- Contare occorrenze per livello (ERROR, WARN, INFO)
- Trovare periodo con più errori
- Generare report formattato
- Gestire file non esistente

**File**: `Esercizio15_AnalizzatoreFileLog.java`

---

## 📝 Note per la Risoluzione

### Suggerimenti Generali:
1. **Sempre validare l'input**: Non assumere che l'utente inserisca dati corretti
2. **Gestire le eccezioni**: Utilizzare try-catch dove necessario
3. **Formattare l'output**: Utilizzare `printf` per output professionale
4. **Commentare il codice**: JavaDoc per metodi pubblici
5. **Testare edge cases**: Valori limite, stringhe vuote, numeri negativi

### Pattern Comuni:
```java
// Input validation pattern
Scanner scanner = new Scanner(System.in);
int valore = -1;
do {
    System.out.print("Inserisci valore (1-100): ");
    if (scanner.hasNextInt()) {
        valore = scanner.nextInt();
        if (valore < 1 || valore > 100) {
            System.out.println("Valore fuori range!");
            valore = -1;
        }
    } else {
        System.out.println("Input non valido!");
        scanner.next(); // consume invalid input
    }
} while (valore == -1);
```

---

## 🎯 Criteri di Valutazione

### Completezza (40%)
- Tutti i requisiti implementati
- Gestione di tutti i casi d'uso

### Correttezza (30%)
- Logica corretta
- Gestione errori appropriata
- Output formattato correttamente

### Qualità del Codice (20%)
- Variabili con nomi significativi
- Codice ben strutturato
- Commenti appropriati

### Robustezza (10%)
- Input validation
- Gestione eccezioni
- Test di edge cases

---

## 📂 Soluzioni
Le soluzioni complete sono disponibili nella cartella `soluzioni/` con spiegazioni dettagliate e varianti alternative.

**Prossimo**: [Quiz Modulo C](../quiz/quiz-modulo-c.md) | **Indietro**: [Esempi Modulo C](../esempi/)
