/**
 * Riconoscitore di Sequenza
 *
 * Questo programma implementa un sistema di riconoscimento di sequenza utilizzando Arduino.
 * L'utente inserisce una sequenza continua di caratteri tramite la linea seriale.
 * La sequenza viene memorizzata in un array e, quando l'array è completo, i valori vengono
 * shiftati a sinistra per fare spazio al nuovo carattere letto.
 *
 * Se la sequenza inserita corrisponde a una sequenza predefinita, un LED verde lampeggia
 * e rimane acceso, indicando che l'allarme è attivato.
 * Se la sequenza viene reinserita, un LED rosso lampeggia e rimane acceso, indicando
 * che l'allarme è disattivato, e così via.
 *
 * https://wokwi.com/projects/419596014187366401
 *
 * @author Filippo Bilardo
 * @version 1.0 17/03/25 - Versione iniziale
 */
#include <Arduino.h>

const int PIN_LED_VERDE = 8;                                             // Pin per il LED verde
const int PIN_LED_ROSSO = 13;                                            // Pin per il LED rosso
const int LUNGHEZZA_SEQUENZA = 6;                                        // Lunghezza della sequenza da riconoscere
char sequenzaInput[LUNGHEZZA_SEQUENZA] = {'9', '9', '9', '9', '9', '9'}; // Inizializza l'array
char sequenzaCorretta[] = {'3','3','3','4','5','6'};                     // Sequenza predefinita da riconoscere
bool allarmeAttivo = false;                                              // Stato dell'allarme (attivo/disattivo)

// Prototipi delle funzioni
void LedVerdeConfigura();
void LedVerdeAccendi();
void LedVerdeSpegni();
void LedVerdeLampeggia(int volte, int ritardoMs);
void LedRossoConfigura();
void LedRossoAccendi();
void LedRossoSpegni();
void LedRossoLampeggia(int volte, int ritardoMs);
void SerialeMostraRicezione(char carattereInput);
void AllarmeMostraStato();
void AllarmeImpostaStato(bool attivo);
void ArrayShiftSinistra(char array[], int dimensione);
void ArrayImpostaValoreElemento(char array[], char valore, int posizione);
bool ArrayConfronta(char array1[], char array2[], int dimensione);
void ArrayStampa();


void setup()
{
    Serial.begin(9600); // Inizializza la comunicazione seriale
    LedVerdeConfigura(); // Configura il pin del LED verde
    LedRossoConfigura(); // Configura il pin del LED rosso
    
    // Messaggio iniziale
    Serial.println("Sistema di riconoscimento sequenza avviato");
    Serial.println("Inserisci caratteri per formare la sequenza");
}

void loop()
{
    // Controlla se è disponibile un carattere da leggere dalla linea seriale
    if (Serial.available() > 0)
    {
        // Legge il carattere ricevuto dalla linea seriale
        char carattereInput = Serial.read();

        // Ignora il carattere di ritorno a capo
        if (carattereInput != '\n') {
            
            // Indica la ricezione di un carattere
            SerialeMostraRicezione(carattereInput);

            // Aggiorna la sequenza
            ArrayShiftSinistra(sequenzaInput, LUNGHEZZA_SEQUENZA);
            // Aggiunge il nuovo carattere alla fine dell'array
            ArrayImpostaValoreElemento(sequenzaInput, carattereInput, LUNGHEZZA_SEQUENZA - 1);
            // Stampa la sequenza corrente
            ArrayStampa();

            // Verifica se la sequenza corrisponde a quella corretta
            if (ArrayConfronta(sequenzaInput, sequenzaCorretta, LUNGHEZZA_SEQUENZA))
            {
                Serial.println("Sequenza riconosciuta!");

                // Cambia lo stato dell'allarme (attiva/disattiva)
                AllarmeImpostaStato(!allarmeAttivo);
            }
        }
    }
}


/**
 * Imposta il valore di un elemento dell'array
 * @param array L'array da modificare
 * @param valore Il valore da impostare
 * @param posizione La posizione dell'elemento da modificare
 */
void ArrayImpostaValoreElemento(char array[], char valore, int posizione)
{
}

/**
 * Sposta tutti gli elementi dell'array di una posizione a sinistra
 * @param array L'array da modificare
 * @param dimensione La dimensione dell'array
 */
void ArrayShiftSinistra(char array[], int dimensione)
{
}

/**
 * Verifica se due array sono identici
 * @param array1 Il primo array da confrontare
 * @param array2 Il secondo array da confrontare
 * @param dimensione La dimensione degli array
 * @return true se gli array sono identici, false altrimenti
 */
bool ArrayConfronta(char array1[], char array2[], int dimensione)
{
}

/**
 * Stampa il contenuto dell'array
 */
void ArrayStampa()
{
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
/**
 * Configura il pin del LED verde
 */
void LedVerdeConfigura()
{
    pinMode(PIN_LED_VERDE, OUTPUT);
    LedVerdeSpegni();
}

/**
 * Accende il LED verde
 */
void LedVerdeAccendi()
{
    digitalWrite(PIN_LED_VERDE, HIGH);
}

/**
 * Spegne il LED verde
 */
void LedVerdeSpegni()
{
    digitalWrite(PIN_LED_VERDE, LOW);
}

/**
 * Fa lampeggiare il LED verde per un determinato numero di volte
 * @param volte Il numero di volte che il LED deve lampeggiare
 * @param ritardoMs Il tempo di attesa tra un lampeggio e l'altro in millisecondi
 */
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


/**
 * Configura il pin del LED rosso
 */
void LedRossoConfigura()
{
    pinMode(PIN_LED_ROSSO, OUTPUT);
    LedRossoSpegni();
}
/**
 * Accende il LED rosso
 */
void LedRossoAccendi()
{
    digitalWrite(PIN_LED_ROSSO, HIGH);
}

/**
 * Spegne il LED rosso
 */
void LedRossoSpegni()
{
    digitalWrite(PIN_LED_ROSSO, LOW);
}
/**
 * Fa lampeggiare il LED rosso per un determinato numero di volte
 * @param volte Il numero di volte che il LED deve lampeggiare
 * @param ritardoMs Il tempo di attesa tra un lampeggio e l'altro in millisecondi
 */
void LedRossoLampeggia(int volte, int ritardoMs)
{
    for (int i = 0; i < volte; i++)
    {
        LedRossoAccendi();
        delay(ritardoMs);
        LedRossoSpegni();
        delay(ritardoMs);
    }
}

/**
 * Indica la ricezione di un carattere facendo lampeggiare brevemente entrambi i LED
 * @param carattereInput Il carattere ricevuto
 */
void SerialeMostraRicezione(char carattereInput)
{
    LedVerdeAccendi();
    LedRossoAccendi();
    Serial.print("Ricevuto: ");
    Serial.println(carattereInput);
    delay(50);

    // Mostra lo stato dell'allarme
    AllarmeMostraStato();
}

/**
 * Mostra lo stato dell'allarme (attivo/disattivo)
 */
void AllarmeMostraStato()
{
    if (allarmeAttivo)
    {
        LedVerdeAccendi();
        LedRossoSpegni();
    }
    else
    {
        LedVerdeSpegni();
        LedRossoAccendi();
    }
}

/**
 * Imposta lo stato dell'allarme (attivo/disattivo)
 * @param attivo true per attivare l'allarme, false per disattivarlo
 */
void AllarmeImpostaStato(bool attivo)
{
    allarmeAttivo = attivo;

    if (attivo)
    {
        // Attiva l'allarme
        Serial.println("Allarme attivato");
        LedVerdeLampeggia(3, 200);
        LedVerdeAccendi();
        LedRossoSpegni();
    }
    else
    {
        // Disattiva l'allarme
        Serial.println("Allarme disattivato");
        LedRossoLampeggia(3, 200);
        LedRossoAccendi();
        LedVerdeSpegni();
    }
}

