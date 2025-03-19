/*
 * Progetto Sensore di Temperatura Arduino con DS18B20 - Versione 2
 * 
 * Questo sketch legge la temperatura da un sensore DS18B20 ogni 3 secondi,
 * memorizza le letture in un buffer circolare di 10 elementi,
 * e calcola/visualizza la temperatura media.
 * 
 * v1.2 17/03/25 - utilizza funzioni e delay() invece di millis() per la temporizzazione.
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Prototipi delle funzioni
void inizializzaBuffer();
float leggiTemperatura();
void memorizzaTemperatura(float temperatura);
float calcolaTemperaturaMedia();
void visualizzaRisultati(float temperatura, float media);

// Il filo dati è collegato al pin digitale 2
#define BUS_ONE_WIRE 2
// Configurazione di un'istanza oneWire per comunicare con qualsiasi dispositivo OneWire
OneWire oneWire(BUS_ONE_WIRE);
// Passa il nostro riferimento oneWire al sensore di temperatura Dallas
DallasTemperature sensori(&oneWire);

// Buffer circolare per le letture di temperatura
#define DIMENSIONE_BUFFER 10
float bufferTemperatura[DIMENSIONE_BUFFER];
int indiceBuffer = 0;
int conteggioBuffer = 0;

// Costante di temporizzazione
const unsigned long INTERVALLO_LETTURA = 3000; // 3 secondi in millisecondi

void setup() {
  // Inizializza la porta seriale
  Serial.begin(9600);
  Serial.println("Sensore di Temperatura DS18B20 con Buffer Circolare - Versione 2");
  
  // Avvia la libreria Dallas Temperature
  sensori.begin();
  
  // Inizializza il buffer
  inizializzaBuffer();
}

void loop() {
  // Leggi la temperatura dal sensore
  float temperatura = leggiTemperatura();
  
  // Memorizza la temperatura nel buffer circolare
  memorizzaTemperatura(temperatura);
  
  // Calcola la temperatura media
  float media = calcolaTemperaturaMedia();
  
  // Visualizza i risultati
  visualizzaRisultati(temperatura, media);
  
  // Attendi prima della prossima lettura
  delay(INTERVALLO_LETTURA);
}

// Inizializza il buffer con zeri
void inizializzaBuffer() {
  for (int i = 0; i < DIMENSIONE_BUFFER; i++) {
    bufferTemperatura[i] = 0.0;
  }
}

// Leggi la temperatura dal sensore DS18B20
float leggiTemperatura() {
  sensori.requestTemperatures();
  return sensori.getTempCByIndex(0);
}

// Memorizza la temperatura nel buffer circolare
void memorizzaTemperatura(float temperatura) {
  bufferTemperatura[indiceBuffer] = temperatura;
  
  // Aggiorna l'indice e il conteggio del buffer
  indiceBuffer = (indiceBuffer + 1) % DIMENSIONE_BUFFER;
  if (conteggioBuffer < DIMENSIONE_BUFFER) {
    conteggioBuffer++;
  }
}

// Calcola la temperatura media dai valori del buffer
float calcolaTemperaturaMedia() {
  float somma = 0.0;
  for (int i = 0; i < conteggioBuffer; i++) {
    somma += bufferTemperatura[i];
  }
  return somma / conteggioBuffer;
}

// Visualizza la temperatura corrente e media
void visualizzaRisultati(float temperatura, float media) {
  Serial.print("Temperatura corrente: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  Serial.print("Temperatura media (ultime ");
  Serial.print(conteggioBuffer);
  Serial.print(" letture): ");
  Serial.print(media);
  Serial.println(" °C");
  
  Serial.println("-----------------------");
}