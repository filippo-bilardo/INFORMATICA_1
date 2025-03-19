## Progetto Arduino con Wokwi - Riconoscitore di Sequenza

**Descrizione del Progetto:**
Crea un sistema di riconoscimento sequenza utilizzando Arduino e Wokwi. L'utente inserisce una sequenza continua di caratteri (numeri o lettere) tramite la linea seriale. La sequenza viene memorizzata in un array e, quando l'array è completo, i valori vengono shiftati a sinistra per fare spazio al nuovo carattere letto. Se la sequenza inserita corrisponde a una sequenza predefinita, un LED verde lampeggia e rimane acceso, indicando che l'allarme è attivato. Se la sequenza viene reinserita, un LED rosso lampeggia e rimane acceso, indicando che l'allarme è disattivato, e così via.

## Analisi dei Requisiti

### 1. Requisiti Funzionali

#### 1.1 Gestione dell'Input
- Il sistema deve ricevere caratteri in ingresso tramite la porta seriale (9600 baud)
- Ogni carattere ricevuto deve essere visualizzato sulla porta seriale
- I caratteri ricevuti devono essere memorizzati in un array di lunghezza predefinita (6 caratteri)
- Quando l'array è pieno, i valori devono essere shiftati a sinistra per fare spazio al nuovo carattere

#### 1.2 Riconoscimento della Sequenza
- Il sistema deve confrontare la sequenza inserita con una sequenza di caratteri predefinita ("abc456")
- Il confronto deve avvenire dopo ogni nuovo carattere inserito
- Il sistema deve riconoscere quando la sequenza inserita corrisponde esattamente alla sequenza predefinita

#### 1.3 Gestione dello Stato dell'Allarme
- Il sistema deve alternare lo stato dell'allarme (attivo/disattivo) ogni volta che la sequenza corretta viene riconosciuta
- Lo stato corrente dell'allarme deve essere visualizzato tramite i LED
- Il cambio di stato deve essere comunicato anche tramite la porta seriale

#### 1.4 Feedback Visivo
- Un LED verde deve lampeggiare 3 volte e poi rimanere acceso quando l'allarme viene attivato
- Un LED rosso deve lampeggiare 3 volte e poi rimanere acceso quando l'allarme viene disattivato
- Entrambi i LED devono lampeggiare brevemente (50ms) quando viene ricevuto un carattere

### 2. Requisiti Non Funzionali

#### 2.1 Prestazioni
- Il sistema deve rispondere immediatamente all'input dell'utente
- Il feedback visivo deve essere immediato e chiaramente distinguibile

#### 2.2 Usabilità
- L'interfaccia seriale deve fornire messaggi chiari sullo stato del sistema
- Il sistema deve mostrare la sequenza corrente dopo ogni carattere inserito

#### 2.3 Affidabilità
- Il sistema deve funzionare in modo continuo senza interruzioni
- Il sistema deve gestire correttamente l'input seriale anche in caso di inserimento rapido di caratteri

### 3. Requisiti Hardware

#### 3.1 Componenti Necessari
- Arduino Uno
- LED verde (collegato al pin 8)
- LED rosso (collegato al pin 13)
- Resistenze da 220 ohm (2)
- Breadboard e cavi di collegamento

### 4. Requisiti Software

#### 4.1 Ambiente di Sviluppo
- Arduino IDE per la programmazione
- Wokwi per la simulazione del circuito

#### 4.2 Struttura del Codice
- Utilizzo di funzioni modulari per la gestione dei LED
- Implementazione di funzioni per la manipolazione dell'array
- Implementazione di funzioni per il confronto delle sequenze

**Componenti Necessari:**
- Arduino Uno
- LED verde
- LED rosso
- Resistenze da 220 ohm (2)
- Breadboard e cavi di collegamento

**Codice Arduino:**
scrivere il codice di Arduino riconoscitore.ino
scrivere il file wokwi diagram.json

**Obiettivo Didattico:**
Questo progetto aiuta gli studenti a comprendere l'uso degli array, la gestione della linea seriale e il controllo dei LED con Arduino.

