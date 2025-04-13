# Strutture algoritmiche fondamentali: sequenza, selezione, iterazione

Le strutture algoritmiche fondamentali sono i blocchi di base utilizzati per costruire algoritmi. Queste strutture controllano il flusso di esecuzione di un programma e sono presenti in tutti i linguaggi di programmazione, indipendentemente dalla loro sintassi specifica.

## 1. Struttura sequenziale

La struttura sequenziale è la più semplice delle strutture algoritmiche. Consiste nell'esecuzione di istruzioni una dopo l'altra, in ordine, dall'alto verso il basso.

### Caratteristiche della struttura sequenziale

- Le istruzioni vengono eseguite nell'ordine in cui sono scritte
- Ogni istruzione viene eseguita esattamente una volta
- Il flusso di controllo passa direttamente da un'istruzione alla successiva
- Non ci sono decisioni o ripetizioni

### Rappresentazione in diagramma di flusso

In un diagramma di flusso, la struttura sequenziale è rappresentata da una serie di blocchi collegati da frecce che indicano il flusso di esecuzione dall'alto verso il basso.

### Esempio in pseudocodice

```
INIZIO
    Leggi numero1
    Leggi numero2
    somma = numero1 + numero2
    Scrivi somma
FINE
```

### Applicazioni

La struttura sequenziale è utilizzata per operazioni che devono essere eseguite in un ordine specifico, come:
- Calcoli matematici semplici
- Operazioni di input/output di base
- Inizializzazione di variabili

## 2. Struttura di selezione (condizionale)

La struttura di selezione permette di eseguire diverse istruzioni in base al verificarsi di determinate condizioni. Consente al programma di prendere decisioni.

### Tipi di strutture di selezione

#### a. Selezione semplice (if)

Esegue un blocco di istruzioni solo se una condizione è vera.

**Pseudocodice**:
```
SE condizione ALLORA
    istruzioni
FINE SE
```

#### b. Selezione doppia (if-else)

Esegue un blocco di istruzioni se una condizione è vera, altrimenti esegue un blocco alternativo.

**Pseudocodice**:
```
SE condizione ALLORA
    istruzioni1
ALTRIMENTI
    istruzioni2
FINE SE
```

#### c. Selezione multipla (if-else if-else)

Permette di verificare più condizioni in sequenza.

**Pseudocodice**:
```
SE condizione1 ALLORA
    istruzioni1
ALTRIMENTI SE condizione2 ALLORA
    istruzioni2
ALTRIMENTI SE condizione3 ALLORA
    istruzioni3
ALTRIMENTI
    istruzioni4
FINE SE
```

#### d. Switch-case

Una forma specializzata di selezione multipla che verifica il valore di una singola espressione contro più costanti.

**Pseudocodice**:
```
SWITCH espressione
    CASE valore1: istruzioni1; BREAK
    CASE valore2: istruzioni2; BREAK
    CASE valore3: istruzioni3; BREAK
    DEFAULT: istruzioni_default
FINE SWITCH
```

### Rappresentazione in diagramma di flusso

In un diagramma di flusso, la struttura di selezione è rappresentata da un rombo (simbolo di decisione) con due o più percorsi di uscita, ciascuno corrispondente a un possibile risultato della condizione.

### Applicazioni

Le strutture di selezione sono utilizzate quando il programma deve prendere decisioni, come:
- Validazione dell'input utente
- Implementazione di regole di business
- Gestione di casi speciali
- Controllo del flusso di esecuzione

## 3. Struttura iterativa (cicli)

La struttura iterativa permette di ripetere un blocco di istruzioni più volte, fino a quando una condizione specifica è soddisfatta o per un numero predeterminato di volte.

### Tipi di strutture iterative

#### a. Ciclo con controllo in testa (while)

Verifica la condizione prima di eseguire il blocco di istruzioni. Se la condizione è falsa all'inizio, il blocco potrebbe non essere mai eseguito.

**Pseudocodice**:
```
MENTRE condizione ESEGUI
    istruzioni
FINE MENTRE
```

#### b. Ciclo con controllo in coda (do-while)

Esegue il blocco di istruzioni almeno una volta, poi verifica la condizione per decidere se continuare.

**Pseudocodice**:
```
ESEGUI
    istruzioni
FINCHÉ condizione
```

#### c. Ciclo con contatore (for)

Utilizza una variabile contatore che viene inizializzata, verificata e aggiornata ad ogni iterazione.

**Pseudocodice**:
```
PER variabile DA valore_iniziale A valore_finale PASSO incremento ESEGUI
    istruzioni
FINE PER
```

### Rappresentazione in diagramma di flusso

In un diagramma di flusso, la struttura iterativa è rappresentata da un rombo (simbolo di decisione) con un percorso che ritorna a un punto precedente nel diagramma, creando un ciclo.

### Applicazioni

Le strutture iterative sono utilizzate quando è necessario ripetere operazioni, come:
- Elaborazione di collezioni di dati (array, liste)
- Calcoli che richiedono ripetizione
- Validazione dell'input con richiesta ripetuta
- Operazioni che devono continuare fino a un evento specifico

## Combinazione delle strutture fondamentali

Le tre strutture algoritmiche fondamentali possono essere combinate in vari modi per creare algoritmi complessi:

1. **Nidificazione**: Inserire una struttura all'interno di un'altra (ad esempio, un ciclo all'interno di una condizione)

2. **Sequenza di strutture**: Utilizzare diverse strutture una dopo l'altra

3. **Strutture ibride**: Combinare elementi di diverse strutture (ad esempio, cicli con condizioni di uscita multiple)

### Esempio di combinazione

**Pseudocodice**:
```
INIZIO
    Leggi n
    somma = 0
    
    PER i DA 1 A n ESEGUI
        Leggi numero
        
        SE numero > 0 ALLORA
            somma = somma + numero
        FINE SE
    FINE PER
    
    Scrivi "La somma dei numeri positivi è: " + somma
FINE
```

Questo esempio combina una struttura sequenziale generale, un ciclo for e una condizione if all'interno del ciclo.

## Importanza delle strutture algoritmiche fondamentali

Comprendere e padroneggiare queste strutture fondamentali è essenziale per la programmazione perché:

1. **Universalità**: Sono presenti in tutti i linguaggi di programmazione

2. **Espressività**: Qualsiasi algoritmo può essere espresso utilizzando queste strutture

3. **Modularità**: Permettono di scomporre problemi complessi in componenti gestibili

4. **Leggibilità**: Forniscono un modo standardizzato per esprimere la logica del programma

Le strutture algoritmiche fondamentali costituiscono il vocabolario di base della programmazione, e la loro padronanza è il primo passo verso lo sviluppo di algoritmi efficaci ed efficienti.