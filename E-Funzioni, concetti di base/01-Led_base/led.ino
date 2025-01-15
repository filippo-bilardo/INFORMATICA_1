/** ****************************************************************************************
* \mainpage "Led base"
* @brief funzioni di base per la gestione di un led 
* collegato ad Arduino
* 
* @author Filippo Bilardo
* @version 1.0 01/01/22 versione iniziale
* @version 1.1 14/01/25 aggiunti commenti doxygen
*/

//------------------------------------------------------------------------------------------
//=== LOCAL FUNCTION PROTOTYPES ============================================================
//------------------------------------------------------------------------------------------
/** ****************************************************************************************
* @brief Configurazione del pin dove è collegato il led
* @author <autore>
* @version 1.0 01/01/22 versione iniziale
*/
void led_configura();

/** ****************************************************************************************
* @brief Accensione del led
* @author <autore>
* @version 1.0 01/01/22 versione iniziale
*/
void led_accendi();
void led_spegni();

/** ****************************************************************************************
* @brief Lampeggio del led
*
* @param  int nr: numero di lampeggi
* @retval nessuno
* @see led_accendi(), led_spegni()
* @author <autore>
* @version 1.0 01/01/22 versione iniziale
*/
void led_lampeggia(int nr);

//------------------------------------------------------------------------------------------
//=== LOCAL CONSTANTS ======================================================================
//------------------------------------------------------------------------------------------
const int LED_PIN = 4;  // Pin a cui è collegato il LED

//------------------------------------------------------------------------------------------
//=== ARDUINO MAIN PROGRAM (setup e loop) ==================================================
//------------------------------------------------------------------------------------------
void setup() {
  led_configura();
  led_lampeggia(4);
}

void loop() {
  // inserisci qui il tuo codice principale, per eseguirlo ripetutamente:
}

//------------------------------------------------------------------------------------------
//=== FUNCTIONS DEFINITIONS ================================================================
//------------------------------------------------------------------------------------------
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

