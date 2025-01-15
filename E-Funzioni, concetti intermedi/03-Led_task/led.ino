const int LED_PIN = 4;  // Pin a cui è collegato il LED
int led_stato=0; // Led spento

void led_configura() {
  pinMode(LED_PIN, OUTPUT);
}
void led_accendi() {
  digitalWrite(LED_PIN, HIGH);
  led_stato=HIGH;
}
void led_spegni() {
  digitalWrite(LED_PIN, LOW);
  led_stato=LOW;
}
void led_inverti() {
  (led_stato == LOW) ? led_accendi() : led_spegni();
}

//Funzione per far lampeggiare un LED
void led_lampeggiaTask(int durata_ms) {
  static unsigned long timerStart = millis(); //Valore all'avvio

  unsigned long timerNow = millis(); //Tempo corrente in millisecondi
  //Se è trascorso il tempo specificato, cambia lo stato del LED
  if (timerNow - timerStart >= durata_ms) {
    //Cambia lo stato del LED (accendi se era spento, spegni se era acceso)
    led_inverti();
    timerStart = timerNow;  //Aggiorna il timer al valore attuale
  }
}

void setup() {
  led_configura();  // Imposta il pin del LED come output
}
void loop() {
  led_lampeggiaTask(200); // Fai lampeggiare il LED ogni 200
  // Altro task ...
  // Altro task ...
}

