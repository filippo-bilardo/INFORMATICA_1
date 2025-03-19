// Sketch base per buzzer attivo
const int buzzerPin = 8;  // Pin a cui è collegato il buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Imposta il pin del buzzer come output
}

void loop() {
  digitalWrite(buzzerPin, HIGH);  // Attiva il buzzer
  delay(1000);                    // Mantieni attivo per 1 secondo
  digitalWrite(buzzerPin, LOW);   // Disattiva il buzzer
  delay(1000);                    // Pausa di 1 secondo
}