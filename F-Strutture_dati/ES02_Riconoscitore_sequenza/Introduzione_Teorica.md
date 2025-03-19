# Introduzione Teorica al Riconoscitore di Sequenza con Arduino

## 1. Concetti Fondamentali degli Array in C/C++

Gli array rappresentano una struttura dati fondamentale nella programmazione, permettendo di memorizzare una collezione di elementi dello stesso tipo in una singola variabile. Nel contesto del riconoscitore di sequenza, gli array sono utilizzati per memorizzare e manipolare sequenze di caratteri.

### Caratteristiche principali degli array:

- **Accesso diretto**: Gli elementi di un array sono accessibili tramite indici (posizioni) che iniziano da 0.
- **Dimensione fissa**: Una volta dichiarato, la dimensione dell'array rimane costante.
- **Memoria contigua**: Gli elementi sono memorizzati in locazioni di memoria adiacenti.

Nel progetto, utilizziamo due array principali:
```c
char sequenzaInput[LUNGHEZZA_SEQUENZA] = {'9', '9', '9', '9', '9', '9'}; // Array per memorizzare l'input dell'utente
char sequenzaCorretta[] = {'a', '2', '3', '4', '5', 'z'};                // Array con la sequenza da riconoscere
```

## 2. Il Concetto di Buffer

Un buffer è un'area di memoria temporanea utilizzata per memorizzare dati durante il trasferimento da una parte di un sistema a un'altra. Nel contesto della programmazione, i buffer sono spesso implementati utilizzando array e svolgono un ruolo cruciale nella gestione di flussi di dati continui.

### Caratteristiche e funzioni dei buffer:

- **Memorizzazione temporanea**: I buffer immagazzinano dati in transito prima che vengano elaborati.
- **Gestione di velocità diverse**: Permettono di gestire situazioni in cui la velocità di produzione dei dati è diversa dalla velocità di consumo.
- **Prevenzione della perdita di dati**: Catturano dati che altrimenti potrebbero essere persi durante l'elaborazione.

### Tipi di buffer:

- **Buffer circolari**: Permettono di riutilizzare lo spazio quando il buffer si riempie, sovrascrivendo i dati più vecchi.
- **Buffer FIFO (First-In-First-Out)**: I dati vengono elaborati nell'ordine in cui sono stati ricevuti.
- **Buffer a dimensione fissa**: Hanno una capacità predefinita e non possono espandersi.

Nel nostro riconoscitore di sequenza, l'array `sequenzaInput` funziona come un buffer a dimensione fissa che mantiene gli ultimi N caratteri inseriti dall'utente. Quando il buffer è pieno e arriva un nuovo carattere, utilizziamo la tecnica dello shift a sinistra per fare spazio al nuovo elemento, mantenendo sempre gli input più recenti.

```c
// Esempio di utilizzo del buffer nel riconoscitore di sequenza
if (Serial.available() > 0)
{
    char carattereRicevuto = Serial.read();
    
    // Shift a sinistra per fare spazio al nuovo carattere
    ArrayShiftSinistra(sequenzaInput, LUNGHEZZA_SEQUENZA);
    
    // Inserimento del nuovo carattere nell'ultima posizione del buffer
    sequenzaInput[LUNGHEZZA_SEQUENZA - 1] = carattereRicevuto;
    
    // Verifica se la sequenza nel buffer corrisponde a quella corretta
    if (ArrayConfronta(sequenzaInput, sequenzaCorretta, LUNGHEZZA_SEQUENZA))
    {
        // Sequenza riconosciuta
    }
}
```

## 3. Tecniche di Shift a Sinistra

Lo shift a sinistra è una tecnica fondamentale per gestire sequenze di dati in un buffer di dimensione fissa. Quando un nuovo elemento deve essere aggiunto a un array già pieno, gli elementi esistenti vengono spostati di una posizione verso sinistra, eliminando il primo elemento e creando spazio per il nuovo elemento alla fine.

### Implementazione dello shift a sinistra:

```c
void ArrayShiftSinistra(char array[], int dimensione);
```

Questa tecnica permette di mantenere una "finestra scorrevole" sugli ultimi N caratteri inseriti, essenziale per il riconoscimento di sequenze in un flusso continuo di input.

## 3. Confronto tra Sequenze di Caratteri

Il confronto tra sequenze è il cuore del sistema di riconoscimento. Il programma confronta la sequenza di input con una sequenza predefinita per determinare se l'utente ha inserito la combinazione corretta.

### Algoritmo di confronto:

```c
bool ArrayConfronta(char array1[], char array2[], int dimensione);
```

Questo algoritmo confronta ogni elemento delle due sequenze e restituisce `false` alla prima differenza trovata. Se tutti gli elementi corrispondono, restituisce `true`.

## 4. Comunicazione Seriale in Arduino

La comunicazione seriale è il metodo utilizzato per ricevere input dall'utente. Arduino fornisce una libreria `Serial` che semplifica l'invio e la ricezione di dati attraverso la porta USB.

### Componenti principali:

- **Inizializzazione**: `Serial.begin(9600)` imposta la velocità di comunicazione (baud rate).
- **Lettura**: `Serial.available()` verifica se ci sono dati disponibili, mentre `Serial.read()` legge un byte alla volta.
- **Scrittura**: `Serial.print()` e `Serial.println()` inviano dati al computer.

Nel progetto, la comunicazione seriale permette all'utente di inserire caratteri che vengono poi elaborati per formare la sequenza da verificare.

## 5. Controllo dei LED per Feedback Visivo

I LED sono utilizzati per fornire un feedback visivo all'utente sullo stato del sistema. Nel progetto sono utilizzati due LED:

- **LED Verde**: Indica che l'allarme è attivo.
- **LED Rosso**: Indica che l'allarme è disattivo.

Il controllo dei LED avviene attraverso funzioni dedicate che configurano i pin, accendono, spengono o fanno lampeggiare i LED in base allo stato del sistema.

### Esempio di controllo LED:

```c
void LedVerdeLampeggia(int volte, int ritardoMs)
{
    for (int i = 0; i < volte; i++)
    {
        LedVerdeAccendi();
        delay(ritardoMs);
        LedVerdeSpegni();
        delay(ritardoMs);
    }
}
```

## 6. Macchina a Stati per la Gestione dell'Allarme

Il sistema implementa una semplice macchina a stati per gestire l'attivazione e la disattivazione dell'allarme. Lo stato dell'allarme è rappresentato da una variabile booleana:

```c
bool allarmeAttivo = false; // Stato dell'allarme (attivo/disattivo)
```

Quando la sequenza corretta viene riconosciuta, lo stato dell'allarme viene invertito:

```c
AllarmeImpostaStato(!allarmeAttivo);
```

Questo approccio permette di alternare tra i due stati (attivo/disattivo) ogni volta che la sequenza corretta viene inserita, implementando un semplice meccanismo di toggle.

## 7. Modularità del Codice

Il progetto è strutturato in modo modulare, con funzioni dedicate per ogni operazione specifica. Questo approccio migliora la leggibilità, la manutenibilità e il riutilizzo del codice.

Le funzioni sono organizzate in categorie logiche:
- Funzioni per il controllo dei LED
- Funzioni per la gestione dell'array
- Funzioni per la gestione dell'allarme
- Funzioni per la comunicazione seriale

Questa organizzazione modulare facilita la comprensione del flusso del programma e permette di modificare o estendere facilmente specifiche parti del sistema.

## Conclusione

Il riconoscitore di sequenza è un esempio pratico di come concetti fondamentali di programmazione (array, confronto di stringhe, comunicazione seriale) possano essere combinati con elementi hardware (LED) per creare un sistema interattivo. Il progetto dimostra l'importanza della modularità del codice e dell'uso efficiente delle strutture dati per risolvere problemi pratici.

La comprensione di questi concetti teorici è essenziale per implementare correttamente il sistema e per estenderlo con funzionalità aggiuntive, come l'uso di sequenze più complesse o l'integrazione con altri componenti hardware.