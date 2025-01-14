const int LED_PIN = 4;  // Pin a cui è collegato il LED
const int P1_PIN = 2;   // Pin a cui è collegato il pulsante P1
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

void P1_configura() {
  pinMode(P1_PIN, INPUT_PULLUP);
}
bool P1_Press() {
  return !digitalRead(P1_PIN);
}

void setup() {
  led_configura();  // Imposta il pin del LED come output
  P1_configura();   // Imposta il pin di P1 come input
}
void loop() {

  //P1_Press() ? led_accendi() : led_spegni();
 
}
