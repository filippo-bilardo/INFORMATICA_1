
const int LED_PIN = 4;  // Pin a cui è collegato il LED

void led_configura() {
  pinMode(LED_PIN, OUTPUT);
}
void led_accendi() {
  digitalWrite(LED_PIN, HIGH);
}
void led_spegni() {
  digitalWrite(LED_PIN, LOW);
}
void led_lampeggia(int nr) {
  for(int i=0; i< nr; i++) {
    led_accendi();
    delay(200);
    led_spegni();
    delay(200);
  }
}

void setup() {
  led_configura();
  led_lampeggia(4);
}

void loop() {
  // put your main code here, to run repeatedly:
}
