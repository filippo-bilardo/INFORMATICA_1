# Analisi dei Requisiti - Progetto Sensore di Temperatura Arduino

## 1. Descrizione del Progetto

Il progetto consiste in un sistema di monitoraggio della temperatura basato su Arduino che utilizza un sensore di temperatura digitale DS18B20. Il sistema è in grado di leggere la temperatura ambiente a intervalli regolari, memorizzare le letture in un buffer circolare e calcolare la temperatura media delle ultime letture.

Sono state sviluppate due versioni del software:
- **Versione 1**: Utilizza la funzione `millis()` per la temporizzazione non bloccante
- **Versione 2**: Utilizza funzioni separate e `delay()` per la temporizzazione

## 2. Requisiti Funzionali

### 2.1 Acquisizione Dati
- Il sistema deve leggere la temperatura dal sensore DS18B20 ogni 3 secondi
- La temperatura deve essere misurata in gradi Celsius
- La lettura deve essere visualizzata sulla porta seriale

### 2.2 Elaborazione Dati
- Le letture di temperatura devono essere memorizzate in un buffer circolare di 10 elementi
- Il sistema deve calcolare la temperatura media delle letture memorizzate nel buffer
- La temperatura media deve essere visualizzata sulla porta seriale insieme al numero di letture utilizzate per il calcolo

### 2.3 Interfaccia Utente
- I dati devono essere visualizzati sulla porta seriale con una velocità di 9600 baud
- Il formato di visualizzazione deve includere:
  - Temperatura corrente in °C
  - Temperatura media delle ultime letture in °C
  - Numero di letture utilizzate per il calcolo della media
  - Separatore visivo tra le letture

## 3. Requisiti Hardware

### 3.1 Componenti Necessari
- Arduino Uno o compatibile
- Sensore di temperatura digitale DS18B20
- Resistenza pull-up da 4.7kΩ
- Cavi di collegamento

### 3.2 Schema di Collegamento
- Il pin DQ (Data) del DS18B20 deve essere collegato al pin digitale 2 dell'Arduino
- È necessaria una resistenza pull-up da 4.7kΩ tra il pin DQ e VCC
- Il pin VCC del sensore deve essere collegato al pin 5V dell'Arduino
- Il pin GND del sensore deve essere collegato al pin GND dell'Arduino

## 4. Requisiti Software

### 4.1 Librerie Necessarie
- OneWire: per la comunicazione con dispositivi che utilizzano il protocollo 1-Wire
- DallasTemperature: per l'interfacciamento con il sensore DS18B20

### 4.2 Struttura del Codice

#### Versione 1 (temperature_sensor.ino)
- Utilizza `millis()` per la temporizzazione non bloccante
- Implementa la logica in un'unica funzione `loop()`
- Adatto per sistemi che necessitano di eseguire altre operazioni in parallelo

#### Versione 2 (temperature_sensor_v2.ino)
- Utilizza funzioni separate per ogni operazione:
  - `inizializzaBuffer()`: inizializza il buffer circolare
  - `leggiTemperatura()`: legge la temperatura dal sensore
  - `memorizzaTemperatura()`: memorizza la temperatura nel buffer
  - `calcolaTemperaturaMedia()`: calcola la temperatura media
  - `visualizzaRisultati()`: visualizza i risultati sulla porta seriale
- Utilizza `delay()` per la temporizzazione
- Codice più modulare e facile da comprendere

### 4.3 Parametri Configurabili
- Dimensione del buffer circolare (attualmente 10 elementi)
- Intervallo di lettura (attualmente 3000 ms)
- Pin di collegamento del sensore (attualmente pin digitale 2)

## 5. Considerazioni Aggiuntive

### 5.1 Prestazioni
- La versione 1 è più efficiente in termini di utilizzo della CPU, poiché non blocca l'esecuzione durante l'attesa
- La versione 2 è più semplice da comprendere e modificare, ma blocca l'esecuzione durante l'attesa

### 5.2 Estensibilità
- Il sistema potrebbe essere esteso per supportare più sensori di temperatura
- Potrebbe essere aggiunta una funzionalità di registrazione dei dati su SD card
- Potrebbe essere implementata un'interfaccia web o Bluetooth per la visualizzazione remota dei dati

### 5.3 Limitazioni
- Il buffer circolare ha una dimensione fissa di 10 elementi
- Il sistema non memorizza i dati in modo permanente
- Non sono implementati meccanismi di gestione degli errori per sensori difettosi o scollegati