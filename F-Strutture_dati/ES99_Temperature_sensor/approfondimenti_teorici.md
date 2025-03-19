# Approfondimenti Teorici - Progetto Sensore di Temperatura Arduino

## 1. Il Sensore di Temperatura DS18B20

### 1.1 Caratteristiche Generali
Il DS18B20 è un sensore di temperatura digitale prodotto da Dallas Semiconductor (ora parte di Maxim Integrated). Offre diverse caratteristiche che lo rendono ideale per progetti Arduino:

- **Range di misurazione**: da -55°C a +125°C
- **Precisione**: ±0.5°C nel range da -10°C a +85°C
- **Risoluzione**: configurabile da 9 a 12 bit (da 0.5°C a 0.0625°C)
- **Alimentazione**: può funzionare in modalità parassita (2 fili) o con alimentazione esterna (3 fili)
- **Indirizzo univoco**: ogni sensore ha un indirizzo a 64 bit, permettendo di collegare più sensori sullo stesso bus

### 1.2 Principio di Funzionamento
Il DS18B20 utilizza un elemento sensibile alla temperatura integrato con un convertitore analogico-digitale. La temperatura viene misurata e convertita in un valore digitale a 12 bit che viene memorizzato in un registro interno. Il sensore include anche una memoria non volatile per la configurazione e una ROM con un indirizzo univoco a 64 bit.

### 1.3 Modalità di Alimentazione

#### Modalità Standard (3 fili)
In questa modalità, il sensore è alimentato direttamente con una tensione esterna (3.0V-5.5V):
- VDD: alimentazione positiva
- GND: massa
- DQ: linea dati

#### Modalità Parassita (2 fili)
In questa modalità, il sensore preleva l'energia dalla linea dati quando questa è alta:
- GND: massa
- DQ: linea dati e alimentazione
- VDD: collegato a GND

Questa modalità richiede un pull-up più forte durante le conversioni di temperatura, tipicamente implementato con un MOSFET controllato dal microcontrollore.

## 2. Il Protocollo OneWire

### 2.1 Principi Fondamentali
OneWire è un protocollo di comunicazione seriale sviluppato da Dallas Semiconductor che permette di comunicare con più dispositivi utilizzando un solo filo di dati (più un filo di massa comune). Le caratteristiche principali sono:

- **Comunicazione bidirezionale**: un singolo filo per trasmettere e ricevere dati
- **Topologia a bus**: più dispositivi possono essere collegati in parallelo sullo stesso filo
- **Indirizzamento**: ogni dispositivo ha un indirizzo univoco a 64 bit
- **Velocità**: tipicamente 15.4 kbps (standard speed) o 125 kbps (overdrive)

### 2.2 Segnali e Temporizzazione
Il protocollo OneWire utilizza impulsi di durata variabile per rappresentare i bit:

- **Reset**: il master abbassa la linea per 480+ μs, poi la rilascia; i dispositivi presenti rispondono abbassando la linea
- **Bit 0**: il master abbassa la linea per 60-120 μs, poi la rilascia
- **Bit 1**: il master abbassa la linea per 1-15 μs, poi la rilascia
- **Lettura**: il master abbassa la linea brevemente, poi la rilascia e legge il valore entro 15 μs

### 2.3 Comunicazione con Arduino
La libreria OneWire per Arduino gestisce la temporizzazione precisa richiesta dal protocollo. La sequenza tipica di comunicazione con un DS18B20 è:

1. Reset del bus e rilevamento dei dispositivi
2. Selezione del dispositivo tramite indirizzo (o comando Skip ROM per un singolo dispositivo)
3. Invio del comando (es. Convert T per avviare una conversione)
4. Attesa del completamento dell'operazione
5. Lettura dei dati (es. registro della temperatura)

## 3. Buffer Circolari

### 3.1 Concetto e Implementazione
Un buffer circolare (o ring buffer) è una struttura dati di dimensione fissa che si comporta come se gli estremi fossero connessi. Quando il buffer è pieno, i nuovi dati sovrascrivono quelli più vecchi. Nel progetto del sensore di temperatura, viene utilizzato per memorizzare le ultime N letture.

#### Componenti principali:
- **Array di dati**: memorizza i valori (temperature)
- **Indice di scrittura**: indica la posizione in cui inserire il prossimo valore
- **Contatore**: tiene traccia del numero di elementi inseriti (fino alla capacità massima)

### 3.2 Vantaggi nel Progetto
- **Memoria limitata**: utilizza uno spazio fisso indipendentemente dal tempo di esecuzione
- **Calcolo della media mobile**: permette di calcolare facilmente la media delle ultime N letture
- **Implementazione efficiente**: operazioni di inserimento e accesso in tempo O(1)

### 3.3 Implementazione in C/C++
L'implementazione di un buffer circolare nel progetto utilizza:

```cpp
#define DIMENSIONE_BUFFER 10
float bufferTemperatura[DIMENSIONE_BUFFER];
int indiceBuffer = 0;
int conteggioBuffer = 0;

// Inserimento di un nuovo valore
void memorizzaTemperatura(float temperatura) {
  bufferTemperatura[indiceBuffer] = temperatura;
  
  // Aggiorna l'indice e il conteggio del buffer
  indiceBuffer = (indiceBuffer + 1) % DIMENSIONE_BUFFER;
  if (conteggioBuffer < DIMENSIONE_BUFFER) {
    conteggioBuffer++;
  }
}
```

L'operazione `(indiceBuffer + 1) % DIMENSIONE_BUFFER` è la chiave dell'implementazione circolare, facendo "avvolgere" l'indice quando raggiunge la fine dell'array.

## 4. Medie Mobili e Filtri

### 4.1 Media Mobile Semplice
La media mobile semplice (SMA - Simple Moving Average) calcola la media aritmetica degli ultimi N valori. Nel progetto, viene utilizzata per calcolare la temperatura media delle ultime letture:

```cpp
float calcolaTemperaturaMedia() {
  float somma = 0.0;
  for (int i = 0; i < conteggioBuffer; i++) {
    somma += bufferTemperatura[i];
  }
  return somma / conteggioBuffer;
}
```

### 4.2 Vantaggi del Filtraggio
- **Riduzione del rumore**: le fluttuazioni casuali vengono attenuate
- **Identificazione del trend**: evidenzia la tendenza generale della temperatura
- **Stabilità delle letture**: valori più stabili per sistemi di controllo

### 4.3 Alternative di Filtraggio
Oltre alla media mobile semplice, esistono altre tecniche che potrebbero essere implementate:

- **Media mobile esponenziale (EMA)**: dà più peso ai valori recenti
- **Filtro di Kalman**: ottimale per sistemi con modello noto e rumore gaussiano
- **Filtro mediano**: utile per eliminare outlier (valori anomali)

## 5. Tecniche di Temporizzazione in Arduino

### 5.1 Utilizzo di delay()

#### Principio di funzionamento
La funzione `delay(ms)` blocca l'esecuzione del programma per il numero specificato di millisecondi. Internamente, utilizza un ciclo di attesa attiva che conta i cicli di clock.

#### Vantaggi
- **Semplicità**: facile da implementare e comprendere
- **Precisione**: temporizzazione relativamente precisa

#### Svantaggi
- **Blocco dell'esecuzione**: impedisce l'esecuzione di altre operazioni durante l'attesa
- **Non multitasking**: non permette di gestire più attività contemporaneamente

### 5.2 Utilizzo di millis()

#### Principio di funzionamento
La funzione `millis()` restituisce il numero di millisecondi trascorsi dall'avvio del programma. Confrontando questo valore con un timestamp memorizzato, è possibile determinare se è trascorso un certo intervallo senza bloccare l'esecuzione.

```cpp
unsigned long ultimaLettura = 0;
const unsigned long INTERVALLO = 3000; // 3 secondi

void loop() {
  unsigned long tempoCorrente = millis();
  
  if (tempoCorrente - ultimaLettura >= INTERVALLO) {
    // Esegui le operazioni periodiche
    ultimaLettura = tempoCorrente;
  }
  
  // Altre operazioni che vengono eseguite continuamente
}
```

#### Vantaggi
- **Non bloccante**: permette l'esecuzione di altre operazioni durante l'attesa
- **Multitasking cooperativo**: consente di gestire più attività con temporizzazioni diverse
- **Efficienza**: utilizza meglio le risorse del microcontrollore

#### Svantaggi
- **Complessità**: richiede una struttura del codice più elaborata
- **Overflow**: il contatore di `millis()` va in overflow dopo circa 50 giorni

### 5.3 Confronto tra le Due Versioni del Progetto

#### Versione 1 (con millis())
- Più efficiente in termini di utilizzo della CPU
- Permette di aggiungere altre funzionalità senza modificare la temporizzazione
- Adatta per sistemi che devono gestire più operazioni contemporaneamente

#### Versione 2 (con delay())
- Codice più semplice e lineare
- Più facile da comprendere per i principianti
- Adatta per sistemi con un'unica funzione

## 6. Considerazioni Pratiche

### 6.1 Precisione e Accuratezza delle Misurazioni

#### Fattori che influenzano la precisione
- **Auto-riscaldamento**: il sensore stesso genera calore durante il funzionamento
- **Dissipazione termica**: il calore generato da Arduino può influenzare le letture
- **Interferenze elettriche**: i campi elettromagnetici possono introdurre rumore

#### Miglioramento della precisione
- Utilizzare un'alimentazione stabile
- Posizionare il sensore lontano da fonti di calore
- Implementare tecniche di filtraggio come la media mobile

### 6.2 Ottimizzazione del Codice

#### Efficienza energetica
- Utilizzare la modalità sleep di Arduino quando possibile
- Ridurre la frequenza di campionamento se non è necessaria un'alta risoluzione temporale

#### Gestione della memoria
- Utilizzare tipi di dati appropriati (es. float vs double)
- Evitare l'allocazione dinamica di memoria su microcontrollori con RAM limitata

### 6.3 Estensioni del Progetto

#### Aggiunta di più sensori
Grazie all'indirizzamento univoco del protocollo OneWire, è possibile collegare più sensori DS18B20 allo stesso pin:

```cpp
// Esempio di lettura da più sensori
void leggiTuttiSensori() {
  sensori.requestTemperatures(); // Richiede la temperatura a tutti i sensori
  
  for (int i = 0; i < numeroSensori; i++) {
    float temperatura = sensori.getTempCByIndex(i);
    // Elabora la temperatura di ciascun sensore
  }
}
```

#### Registrazione dei dati
Il progetto potrebbe essere esteso per registrare i dati su una scheda SD o inviarli a un server tramite WiFi/Ethernet:

```cpp
// Pseudocodice per la registrazione su SD
#include <SD.h>

void registraDati(float temperatura) {
  File dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.println(temperatura);
    dataFile.close();
  }
}
```

## 7. Risorse e Riferimenti

### 7.1 Documentazione Tecnica
- [Datasheet DS18B20](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)
- [Specifiche del protocollo OneWire](https://www.maximintegrated.com/en/design/technical-documents/app-notes/1/1796.html)

### 7.2 Librerie Arduino
- [OneWire](https://www.pjrc.com/teensy/td_libs_OneWire.html)
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)

### 7.3 Tutorial e Guide
- [Arduino - DS18B20 Temperature Sensor](https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806)
- [Adafruit DS18B20 Guide](https://learn.adafruit.com/adafruit-1-wire-thermal-sensor/overview)