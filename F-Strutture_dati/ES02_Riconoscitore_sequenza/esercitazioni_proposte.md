# Esercitazioni Proposte - Riconoscitore di Sequenza

Questo documento contiene una serie di esercitazioni e progetti proposti per estendere e migliorare il sistema di riconoscimento di sequenza. Le attività sono organizzate per livello di difficoltà e area di interesse.

## Esercitazioni Base

### 1. Personalizzazione della Sequenza
**Obiettivo**: Modificare la sequenza da riconoscere.

**Attività**:
- Cambiare la sequenza predefinita con una personalizzata
- Aggiungere la possibilità di modificare la lunghezza della sequenza
- Implementare un sistema per cambiare la sequenza durante l'esecuzione

### 2. Contatore di Tentativi
**Obiettivo**: Implementare un contatore che tenga traccia dei tentativi effettuati.

**Attività**:
- Aggiungere una variabile per contare i tentativi di inserimento della sequenza
- Visualizzare il numero di tentativi sulla porta seriale
- Implementare un limite massimo di tentativi prima di bloccare il sistema

### 3. Feedback Sonoro
**Obiettivo**: Aggiungere feedback sonoro al sistema.

**Attività**:
- Collegare un buzzer al circuito
- Implementare suoni diversi per sequenza corretta e errata
- Creare melodie diverse per l'attivazione e la disattivazione dell'allarme

## Esercitazioni Intermedie

### 4. Modalità Sensibile alle Maiuscole
**Obiettivo**: Implementare una modalità in cui il riconoscimento è sensibile alle maiuscole/minuscole.

**Attività**:
- Aggiungere un flag per attivare/disattivare la sensibilità alle maiuscole
- Implementare una funzione per il confronto case-sensitive
- Permettere all'utente di cambiare modalità tramite un comando seriale

### 5. Sequenze Multiple
**Obiettivo**: Implementare il riconoscimento di più sequenze con effetti diversi.

**Attività**:
- Aggiungere un array di sequenze predefinite
- Implementare azioni diverse per ogni sequenza riconosciuta
- Creare un sistema di priorità tra le sequenze

### 6. Timeout di Inserimento
**Obiettivo**: Implementare un timeout per l'inserimento della sequenza.

**Attività**:
- Aggiungere un timer che si resetta ad ogni carattere inserito
- Se il timer supera un certo valore, resettare la sequenza inserita
- Visualizzare un avviso quando il timeout è prossimo alla scadenza

## Esercitazioni Avanzate

### 7. Strutture Dati Alternative
**Obiettivo**: Implementare il riconoscitore utilizzando strutture dati diverse dagli array.

**Attività**:
- Reimplementare il sistema utilizzando una lista concatenata
- Creare una versione che utilizza una coda circolare
- Confrontare le prestazioni delle diverse implementazioni

### 8. Modalità di Apprendimento
**Obiettivo**: Implementare una modalità in cui il sistema può apprendere nuove sequenze.

**Attività**:
- Aggiungere un comando per entrare in modalità di apprendimento
- Permettere all'utente di inserire una nuova sequenza da riconoscere
- Salvare la nuova sequenza in memoria

### 9. Persistenza dei Dati
**Obiettivo**: Implementare la persistenza delle sequenze e delle configurazioni.

**Attività**:
- Utilizzare la EEPROM di Arduino per salvare le sequenze
- Implementare funzioni per leggere/scrivere configurazioni
- Aggiungere un sistema di backup e ripristino

## Progetti Completi

### 10. Sistema di Controllo Accessi
**Obiettivo**: Trasformare il riconoscitore in un sistema di controllo accessi.

**Attività**:
- Aggiungere un display LCD per le istruzioni e i feedback
- Implementare un sistema di utenti con sequenze diverse
- Collegare un servo motore o un relè per simulare l'apertura di una porta
- Aggiungere un log degli accessi

### 11. Sistema di Allarme Avanzato
**Obiettivo**: Creare un sistema di allarme completo.

**Attività**:
- Aggiungere sensori (PIR, reed switch, ecc.) per rilevare intrusioni
- Implementare diverse zone di allarme
- Creare un sistema di notifica (buzzer, LED lampeggianti)
- Aggiungere un timer per l'attivazione/disattivazione automatica

### 12. Gioco di Memoria
**Obiettivo**: Trasformare il sistema in un gioco di memoria.

**Attività**:
- Implementare un gioco in cui il sistema mostra una sequenza (tramite LED o display) e l'utente deve ripeterla
- Aumentare progressivamente la difficoltà (lunghezza della sequenza)
- Implementare un sistema di punteggio e record
- Aggiungere effetti sonori e visivi per rendere il gioco più coinvolgente

## Suggerimenti per l'Implementazione

1. **Gestione della Memoria**: Prestare sempre attenzione alla gestione della memoria, specialmente quando si utilizzano strutture dati dinamiche su Arduino.

2. **Modularità**: Organizzare il codice in moduli ben definiti per facilitare le modifiche e le estensioni.

3. **Documentazione**: Documentare adeguatamente il codice con commenti e una descrizione generale del funzionamento.

4. **Test**: Testare accuratamente ogni modifica per assicurarsi che il sistema funzioni correttamente in tutte le condizioni.

5. **Ottimizzazione**: Considerare le limitazioni hardware di Arduino e ottimizzare il codice di conseguenza.

---

[Torna all'indice](../README.md)