/*
 * Arduino Temperature Sensor Project with DS18B20
 * 
 * This sketch reads temperature from a DS18B20 sensor every 3 seconds,
 * stores readings in a circular buffer of 10 elements,
 * and calculates/displays the average temperature.
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Circular buffer for temperature readings
#define BUFFER_SIZE 10
float tempBuffer[BUFFER_SIZE];
int bufferIndex = 0;
int bufferCount = 0;

// Timing variables
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 3000; // 3 seconds in milliseconds

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println("DS18B20 Temperature Sensor with Circular Buffer");
  
  // Start up the Dallas Temperature library
  sensors.begin();
  
  // Initialize the buffer with zeros
  for (int i = 0; i < BUFFER_SIZE; i++) {
    tempBuffer[i] = 0.0;
  }
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check if it's time to read the temperature
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    // Read temperature from sensor
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    
    // Store temperature in circular buffer
    tempBuffer[bufferIndex] = temperature;
    
    // Update buffer index and count
    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
    if (bufferCount < BUFFER_SIZE) {
      bufferCount++;
    }
    
    // Calculate average temperature
    float sum = 0.0;
    for (int i = 0; i < bufferCount; i++) {
      sum += tempBuffer[i];
    }
    float average = sum / bufferCount;
    
    // Display results
    Serial.print("Current temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    Serial.print("Average temperature (last ");
    Serial.print(bufferCount);
    Serial.print(" readings): ");
    Serial.print(average);
    Serial.println(" °C");
    
    Serial.println("-----------------------");
  }
}