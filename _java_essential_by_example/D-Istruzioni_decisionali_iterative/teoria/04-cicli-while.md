# 4. Cicli While e Do-While

## 4.1 Il Ciclo While

Il ciclo `while` è una struttura iterativa che ripete un blocco di codice finché una condizione booleana rimane vera.

### Sintassi di Base

```java
while (condizione) {
    // blocco di codice da ripetere
}
```

### Caratteristiche Principali

- **Controllo Pre-esecuzione**: La condizione viene valutata prima di ogni iterazione
- **Zero o più iterazioni**: Se la condizione è falsa dall'inizio, il corpo non viene mai eseguito
- **Rischio di cicli infiniti**: È fondamentale che la condizione diventi falsa ad un certo punto

### Esempio Fondamentale

```java
int contatore = 1;
while (contatore <= 5) {
    System.out.println("Iterazione: " + contatore);
    contatore++; // IMPORTANTE: modificare la variabile di controllo
}
```

## 4.2 Esempi Pratici di While

### Esempio 1: Lettura Input con Validazione

```java
Scanner scanner = new Scanner(System.in);
int numero = -1;

while (numero < 0 || numero > 100) {
    System.out.print("Inserisci un numero tra 0 e 100: ");
    numero = scanner.nextInt();
    
    if (numero < 0 || numero > 100) {
        System.out.println("Numero non valido!");
    }
}

System.out.println("Numero valido inserito: " + numero);
```

### Esempio 2: Calcolo della Somma

```java
Scanner scanner = new Scanner(System.in);
int somma = 0;
int numero;

System.out.println("Inserisci numeri (0 per terminare):");

while ((numero = scanner.nextInt()) != 0) {
    somma += numero;
    System.out.println("Somma parziale: " + somma);
}

System.out.println("Somma totale: " + somma);
```

### Esempio 3: Ricerca in una Stringa

```java
String testo = "Java è fantastico";
char carattere = 'a';
int posizione = 0;
boolean trovato = false;

while (posizione < testo.length() && !trovato) {
    if (testo.charAt(posizione) == carattere) {
        trovato = true;
        System.out.println("Carattere '" + carattere + "' trovato alla posizione: " + posizione);
    } else {
        posizione++;
    }
}

if (!trovato) {
    System.out.println("Carattere non trovato");
}
```

## 4.3 Il Ciclo Do-While

Il ciclo `do-while` è simile al `while`, ma garantisce almeno un'esecuzione del blocco di codice.

### Sintassi

```java
do {
    // blocco di codice da ripetere
} while (condizione);
```

### Caratteristiche Distintive

- **Controllo Post-esecuzione**: La condizione viene valutata dopo ogni iterazione
- **Almeno una iterazione**: Il corpo viene sempre eseguito almeno una volta
- **Ideale per menu e validazioni**: Quando serve almeno un'esecuzione

### Confronto While vs Do-While

```java
// WHILE - potrebbe non eseguire mai
int x = 10;
while (x < 5) {
    System.out.println("Questo non verrà mai stampato");
    x++;
}

// DO-WHILE - esegue almeno una volta
int y = 10;
do {
    System.out.println("Questo verrà stampato una volta: " + y);
    y++;
} while (y < 5);
```

## 4.4 Esempi Pratici di Do-While

### Esempio 1: Menu Interattivo

```java
Scanner scanner = new Scanner(System.in);
int scelta;

do {
    System.out.println("\n=== MENU PRINCIPALE ===");
    System.out.println("1. Opzione A");
    System.out.println("2. Opzione B");
    System.out.println("3. Opzione C");
    System.out.println("0. Esci");
    System.out.print("Scegli un'opzione: ");
    
    scelta = scanner.nextInt();
    
    switch (scelta) {
        case 1:
            System.out.println("Hai scelto l'Opzione A");
            break;
        case 2:
            System.out.println("Hai scelto l'Opzione B");
            break;
        case 3:
            System.out.println("Hai scelto l'Opzione C");
            break;
        case 0:
            System.out.println("Arrivederci!");
            break;
        default:
            System.out.println("Opzione non valida!");
    }
} while (scelta != 0);
```

### Esempio 2: Gioco "Indovina il Numero"

```java
Random random = new Random();
Scanner scanner = new Scanner(System.in);
int numeroSegreto = random.nextInt(100) + 1;
int tentativo;
int numeroTentativi = 0;

System.out.println("Indovina il numero tra 1 e 100!");

do {
    System.out.print("Inserisci il tuo tentativo: ");
    tentativo = scanner.nextInt();
    numeroTentativi++;
    
    if (tentativo < numeroSegreto) {
        System.out.println("Troppo basso!");
    } else if (tentativo > numeroSegreto) {
        System.out.println("Troppo alto!");
    } else {
        System.out.println("Complimenti! Hai indovinato in " + numeroTentativi + " tentativi!");
    }
} while (tentativo != numeroSegreto);
```

## 4.5 Pattern Comuni con While

### Pattern 1: Elaborazione File/Stream

```java
Scanner fileScanner = new Scanner(new File("dati.txt"));

while (fileScanner.hasNextLine()) {
    String linea = fileScanner.nextLine();
    // elabora la linea
    System.out.println("Elaborando: " + linea);
}

fileScanner.close();
```

### Pattern 2: Ricerca con Flag

```java
boolean trovato = false;
int indice = 0;
int[] array = {5, 2, 8, 1, 9};
int valore = 8;

while (indice < array.length && !trovato) {
    if (array[indice] == valore) {
        trovato = true;
        System.out.println("Valore trovato all'indice: " + indice);
    } else {
        indice++;
    }
}
```

### Pattern 3: Accumulo con Condizione

```java
Scanner scanner = new Scanner(System.in);
double somma = 0;
int conteggio = 0;
double numero;

System.out.println("Inserisci numeri positivi (numero negativo per terminare):");

while ((numero = scanner.nextDouble()) >= 0) {
    somma += numero;
    conteggio++;
}

if (conteggio > 0) {
    double media = somma / conteggio;
    System.out.printf("Media di %d numeri: %.2f%n", conteggio, media);
} else {
    System.out.println("Nessun numero valido inserito");
}
```

## 4.6 Errori Comuni e Best Practices

### Errori da Evitare

```java
// ERRORE 1: Ciclo infinito
int i = 0;
while (i < 10) {
    System.out.println(i);
    // Dimenticato i++; - CICLO INFINITO!
}

// ERRORE 2: Condizione sempre falsa
int j = 10;
while (j < 5) { // Condizione sempre falsa
    System.out.println("Mai eseguito");
    j++;
}

// ERRORE 3: Modifiche scorrette alla variabile di controllo
int k = 0;
while (k < 10) {
    System.out.println(k);
    k += 2; // Potrebbe saltare la condizione di terminazione
}
```

### Best Practices

```java
// BUONA PRATICA 1: Variabile di controllo chiara
int tentativiRimasti = 3;
while (tentativiRimasti > 0) {
    // logica del gioco
    tentativiRimasti--;
}

// BUONA PRATICA 2: Condizioni di sicurezza
int maxIterazioni = 1000;
int iterazioni = 0;
while (condizione && iterazioni < maxIterazioni) {
    // elaborazione
    iterazioni++;
}

// BUONA PRATICA 3: Uso di flag booleani
boolean continuaElaborazione = true;
while (continuaElaborazione) {
    // elaborazione
    if (condizioneUscita) {
        continuaElaborazione = false;
    }
}
```

## 4.7 When to Use: While vs Do-While vs For

### Usa WHILE quando:
- Non sai quante iterazioni servono
- La condizione potrebbe essere falsa dall'inizio
- Stai leggendo da un input stream
- Implementi algoritmi di ricerca

### Usa DO-WHILE quando:
- Serve almeno un'esecuzione
- Implementi menu interattivi
- Fai validazione dell'input
- Il controllo avviene alla fine del ciclo

### Usa FOR quando:
- Sai il numero di iterazioni
- Lavori con indici o contatori
- Elabori array o collezioni
- Hai bisogno di inizializzazione e incremento

## 4.8 Esercizi di Comprensione

### Esercizio Mentale 1
Cosa stampa questo codice?

```java
int x = 1;
while (x <= 3) {
    System.out.print(x + " ");
    x++;
}
```

**Risposta**: `1 2 3 `

### Esercizio Mentale 2
Quante volte viene eseguito questo ciclo?

```java
int y = 5;
do {
    System.out.println(y);
    y--;
} while (y > 5);
```

**Risposta**: 1 volta (stampa `5`)

### Esercizio Mentale 3
Questo codice termina?

```java
int z = 0;
while (z != 10) {
    System.out.println(z);
    z += 3;
}
```

**Risposta**: No, ciclo infinito (z passa da 9 a 12, saltando 10)

## 4.9 Applicazioni Avanzate

### Simulazione Processo
```java
Random random = new Random();
boolean processoCompletato = false;
int progresso = 0;

while (!processoCompletato) {
    // Simula avanzamento casuale
    int avanzamento = random.nextInt(10) + 1;
    progresso += avanzamento;
    
    System.out.println("Progresso: " + Math.min(progresso, 100) + "%");
    
    if (progresso >= 100) {
        processoCompletato = true;
        System.out.println("Processo completato!");
    }
    
    // Pausa per simulare tempo di elaborazione
    try {
        Thread.sleep(500);
    } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
    }
}
```

I cicli while e do-while sono strumenti potenti per creare programmi interattivi e algoritmi robusti. La chiave è scegliere il tipo giusto per ogni situazione e prestare sempre attenzione alle condizioni di terminazione.
