# Guida all'utilizzo del Buzzer con Arduino

## Parte 1: Le basi

### Cos'è un Buzzer?
Un buzzer è un componente elettronico che converte un segnale elettrico in un suono. Esistono principalmente due tipi di buzzer:
- **Buzzer passivi**: richiedono un segnale oscillante per produrre suono
- **Buzzer attivi**: hanno un oscillatore interno e producono un tono fisso quando alimentati

### Componenti necessari
- Arduino (qualsiasi modello)
- Buzzer (attivo o passivo)
- Resistore da 100Ω (opzionale, per limitare la corrente)
- Breadboard
- Cavi di collegamento

### Schema di collegamento base
1. Collega il pin positivo del buzzer a un pin digitale di Arduino (es. pin 8)
2. Collega il pin negativo del buzzer a GND
3. Opzionalmente, inserisci un resistore da 100Ω in serie per limitare la corrente

### Primo sketch: Tono semplice

```cpp
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

```

### Utilizzo di un buzzer passivo
Se usi un buzzer passivo, puoi generare diverse frequenze utilizzando la funzione `tone()`:

```cpp
// Sketch base per buzzer passivo
const int buzzerPin = 8;  // Pin a cui è collegato il buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Imposta il pin del buzzer come output
}

void loop() {
  tone(buzzerPin, 1000);  // Genera un tono a 1000 Hz
  delay(1000);            // Mantieni il tono per 1 secondo
  noTone(buzzerPin);      // Ferma il tono
  delay(1000);            // Pausa di 1 secondo
}

```

## Parte 2: Funzionalità intermedie

### Suonare una melodia semplice

```cpp
// Riproduzione di una melodia semplice
const int buzzerPin = 8;

// Definizione delle note (frequenze in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Melodia: Array di note
int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

// Durata delle note (in ms)
int noteDurations[] = {
  250, 250, 250, 250, 250, 250, 250, 500
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Riproduci una volta la melodia
  for (int i = 0; i < 8; i++) {
    tone(buzzerPin, melody[i]);
    delay(noteDurations[i]);
    noTone(buzzerPin);
    delay(50);  // Breve pausa tra le note
  }
  
  delay(2000);  // Pausa prima di ripetere
}

```

### Controllo del volume (PWM)
Per i buzzer passivi, puoi simulare diversi livelli di volume utilizzando il PWM (Pulse Width Modulation):

```cpp
// Controllo del volume tramite PWM
const int buzzerPin = 9;  // Usa un pin che supporti PWM (es. 3, 5, 6, 9, 10, 11)

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Volume crescente
  for (int volume = 0; volume <= 255; volume += 5) {
    analogWrite(buzzerPin, volume);  // Imposta il "volume" tramite duty cycle
    delay(30);
  }
  
  // Volume decrescente
  for (int volume = 255; volume >= 0; volume -= 5) {
    analogWrite(buzzerPin, volume);
    delay(30);
  }
  
  delay(1000);  // Pausa prima di ripetere
}

```

## Parte 3: Applicazioni avanzate

### Sistema di allarme con sensore di movimento (PIR)

```cpp
// Sistema di allarme con sensore PIR
const int buzzerPin = 8;
const int pirPin = 2;     // Pin del sensore PIR
const int ledPin = 13;    // LED integrato

// Parametri allarme
const int alarmDuration = 3000;  // Durata dell'allarme in ms
boolean alarmActive = false;     // Stato dell'allarme

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema di allarme attivo");
}

void loop() {
  int motionDetected = digitalRead(pirPin);
  
  if (motionDetected == HIGH) {
    Serial.println("Movimento rilevato!");
    triggerAlarm();
  }
}

void triggerAlarm() {
  // Attiva l'allarme
  alarmActive = true;
  unsigned long startTime = millis();
  
  // Suona per la durata impostata
  while (millis() - startTime < alarmDuration) {
    // Suono di allarme modulato
    for (int freq = 800; freq < 2000; freq += 10) {
      tone(buzzerPin, freq);
      digitalWrite(ledPin, HIGH);
      delay(5);
    }
    for (int freq = 2000; freq > 800; freq -= 10) {
      tone(buzzerPin, freq);
      digitalWrite(ledPin, LOW);
      delay(5);
    }
  }
  
  // Disattiva l'allarme
  noTone(buzzerPin);
  digitalWrite(ledPin, LOW);
  alarmActive = false;
}

```

### Comunicazione in codice Morse

```cpp
// Comunicazione in codice Morse
const int buzzerPin = 8;

// Parametri temporali del codice Morse (in ms)
const int dotDuration = 200;
const int dashDuration = dotDuration * 3;
const int symbolPause = dotDuration;
const int letterPause = dotDuration * 3;
const int wordPause = dotDuration * 7;

// Dizionario Morse per lettere e numeri
String morseDict[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",  // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                         // U-Z
  "-----", ".----", "..---", "...--", "....-",                          // 0-4
  ".....", "-....", "--...", "---..", "----."                           // 5-9
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema di comunicazione Morse attivo");
  Serial.println("Inserisci il messaggio da convertire:");
}

void loop() {
  // Controlla se ci sono dati disponibili dalla seriale
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    Serial.print("Messaggio ricevuto: ");
    Serial.println(message);
    Serial.print("Codice Morse: ");
    
    // Converte e riproduce il messaggio
    for (int i = 0; i < message.length(); i++) {
      char c = toupper(message.charAt(i));
      
      if (c == ' ') {
        // Pausa tra parole
        Serial.print("   ");
        delay(wordPause);
      } else if (c >= 'A' && c <= 'Z') {
        // Lettere
        String morse = morseDict[c - 'A'];
        Serial.print(morse + " ");
        playMorseCode(morse);
        delay(letterPause);
      } else if (c >= '0' && c <= '9') {
        // Numeri
        String morse = morseDict[26 + (c - '0')];
        Serial.print(morse + " ");
        playMorseCode(morse);
        delay(letterPause);
      }
    }
    
    Serial.println("\nMessaggio completato!");
  }
}

void playMorseCode(String code) {
  for (int i = 0; i < code.length(); i++) {
    if (code.charAt(i) == '.') {
      // Punto
      tone(buzzerPin, 1000);
      delay(dotDuration);
    } else if (code.charAt(i) == '-') {
      // Linea
      tone(buzzerPin, 1000);
      delay(dashDuration);
    }
    
    // Ferma il tono e attendi prima del prossimo simbolo
    noTone(buzzerPin);
    delay(symbolPause);
  }
}

```

### Theremin digitale con sensore a ultrasuoni HC-SR04

```cpp
// Theremin digitale con sensore ad ultrasuoni
const int buzzerPin = 8;
const int trigPin = 9;    // Trigger del sensore HC-SR04
const int echoPin = 10;   // Echo del sensore HC-SR04

// Parametri del theremin
const int minFreq = 100;   // Frequenza minima (Hz)
const int maxFreq = 2000;  // Frequenza massima (Hz)
const int minDist = 5;     // Distanza minima (cm)
const int maxDist = 50;    // Distanza massima (cm)

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Theremin digitale attivo");
}

void loop() {
  // Misura la distanza
  long duration, distance;
  
  // Invia impulso ultrasonico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calcola la distanza
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;  // Conversione in cm
  
  // Limita la distanza nell'intervallo definito
  distance = constrain(distance, minDist, maxDist);
  
  // Mappa la distanza alla frequenza
  int frequency = map(distance, minDist, maxDist, maxFreq, minFreq);
  
  // Mostra i valori sulla seriale
  Serial.print("Distanza: ");
  Serial.print(distance);
  Serial.print(" cm | Frequenza: ");
  Serial.print(frequency);
  Serial.println(" Hz");
  
  // Genera il tono corrispondente
  tone(buzzerPin, frequency);
  
  // Se la mano è troppo lontana, ferma il suono
  if (distance >= maxDist) {
    noTone(buzzerPin);
  }
  
  delay(50);  // Piccolo ritardo per stabilità
}

```

### Sintetizzatore MIDI

```cpp
// Sintetizzatore MIDI base
const int buzzerPin = 8;

// Note MIDI (frequenze in Hz)
const int notes[] = {
  262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 
  523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988
};

// Nomi delle note
const String noteNames[] = {
  "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
  "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5"
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sintetizzatore MIDI attivo");
  Serial.println("Inserisci un numero da 1 a 24 per suonare una nota:");
  printNoteTable();
}

void loop() {
  if (Serial.available() > 0) {
    int noteIndex = Serial.parseInt();
    
    if (noteIndex >= 1 && noteIndex <= 24) {
      // Indice valido (1-24)
      noteIndex--;  // Converti in indice array (0-23)
      
      Serial.print("Riproduzione nota: ");
      Serial.print(noteNames[noteIndex]);
      Serial.print(" (");
      Serial.print(notes[noteIndex]);
      Serial.println(" Hz)");
      
      // Suona la nota
      tone(buzzerPin, notes[noteIndex]);
      delay(500);
      noTone(buzzerPin);
    } else {
      Serial.println("Nota non valida. Inserisci un numero da 1 a 24.");
      printNoteTable();
    }
    
    // Svuota il buffer seriale
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}

void printNoteTable() {
  Serial.println("\nTabella delle note disponibili:");
  for (int i = 0; i < 24; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(noteNames[i]);
    Serial.print(" (");
    Serial.print(notes[i]);
    Serial.println(" Hz)");
  }
  Serial.println();
}

```

## Esercizi proposti

1. **Base**: Modifica lo sketch del buzzer attivo per creare un pattern sonoro più complesso alternando periodi di suono brevi e lunghi.

2. **Intermedio**: Crea un sistema di notifica sonora che utilizzi diverse sequenze di suoni per indicare stati diversi (es. una sequenza per "tutto OK", una per "attenzione" e una per "emergenza").

3. **Avanzato**: Implementa un riproduttore di file RTTTL (Ring Tone Text Transfer Language) che possa suonare suonerie di telefoni Nokia classici tramite il buzzer.

4. **Sfida**: Combina un buzzer con un display LCD e un sensore di temperatura per creare un sistema di monitoraggio che emetta allarmi sonori quando vengono superate determinate soglie di temperatura.

## Domande di autovalutazione

1. Qual è la differenza principale tra un buzzer attivo e uno passivo?
   - A) Il buzzer attivo è più grande
   - B) Il buzzer passivo richiede un segnale oscillante per funzionare
   - C) Il buzzer attivo può produrre suoni più acuti
   - D) Non c'è differenza funzionale tra i due tipi

2. Quale funzione di Arduino si utilizza per generare toni con un buzzer passivo?
   - A) `sound()`
   - B) `beep()`
   - C) `tone()`
   - D) `playSound()`

3. Per controllare il volume di un buzzer tramite PWM, quale pin di Arduino dovresti utilizzare?
   - A) Qualsiasi pin digitale
   - B) Solo i pin analogici (A0-A5)
   - C) Un pin che supporti PWM (es. 3, 5, 6, 9, 10, 11)
   - D) Solo i pin di comunicazione seriale

4. Nel codice Morse, il rapporto di durata tra una linea e un punto è:
   - A) 2:1
   - B) 3:1
   - C) 4:1
   - D) 5:1

## Risposte alle domande di autovalutazione

1. B) Il buzzer passivo richiede un segnale oscillante per funzionare
2. C) `tone()`
3. C) Un pin che supporti PWM (es. 3, 5, 6, 9, 10, 11)
4. B) 3:1