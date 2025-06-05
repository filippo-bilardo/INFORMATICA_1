# 5. Controllo del Flusso di Esecuzione

## 5.1 Introduzione al Controllo del Flusso

Il controllo del flusso permette di modificare l'esecuzione normale (sequenziale) di un programma attraverso istruzioni speciali che possono:
- Interrompere cicli prematuramente
- Saltare iterazioni specifiche
- Uscire da metodi
- Gestire situazioni eccezionali

## 5.2 L'Istruzione Break

L'istruzione `break` termina immediatamente l'esecuzione del ciclo più interno in cui si trova.

### Break in Cicli For

```java
// Ricerca del primo numero pari
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        System.out.println("Primo numero pari trovato: " + i);
        break; // Esce dal ciclo
    }
    System.out.println("Numero dispari: " + i);
}
System.out.println("Ciclo terminato");

// Output:
// Numero dispari: 1
// Primo numero pari trovato: 2
// Ciclo terminato
```

### Break in Cicli While

```java
Scanner scanner = new Scanner(System.in);
int somma = 0;

while (true) { // Ciclo apparentemente infinito
    System.out.print("Inserisci un numero (0 per uscire): ");
    int numero = scanner.nextInt();
    
    if (numero == 0) {
        break; // Termina il ciclo
    }
    
    somma += numero;
    System.out.println("Somma parziale: " + somma);
}

System.out.println("Somma finale: " + somma);
```

### Break in Switch (già visto)

```java
int giorno = 3;
switch (giorno) {
    case 1:
        System.out.println("Lunedì");
        break; // Previene il fall-through
    case 2:
        System.out.println("Martedì");
        break;
    case 3:
        System.out.println("Mercoledì");
        break; // Senza questo, eseguirebbe anche case 4
    default:
        System.out.println("Altro giorno");
}
```

## 5.3 L'Istruzione Continue

L'istruzione `continue` salta il resto dell'iterazione corrente e passa alla successiva.

### Continue in Cicli For

```java
// Stampa solo numeri dispari
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue; // Salta i numeri pari
    }
    System.out.println("Numero dispari: " + i);
}

// Output: 1, 3, 5, 7, 9
```

### Continue in Cicli While

```java
Scanner scanner = new Scanner(System.in);
int conteggio = 0;
int sommaPositivi = 0;

while (conteggio < 5) {
    System.out.print("Inserisci un numero: ");
    int numero = scanner.nextInt();
    conteggio++;
    
    if (numero <= 0) {
        System.out.println("Numero ignorato (non positivo)");
        continue; // Salta alla prossima iterazione
    }
    
    sommaPositivi += numero;
    System.out.println("Numero aggiunto alla somma");
}

System.out.println("Somma dei numeri positivi: " + sommaPositivi);
```

## 5.4 Break e Continue con Cicli Annidati

### Comportamento Standard

```java
// Break esce solo dal ciclo più interno
for (int i = 1; i <= 3; i++) {
    System.out.println("Ciclo esterno: " + i);
    
    for (int j = 1; j <= 3; j++) {
        if (j == 2) {
            break; // Esce solo dal ciclo interno
        }
        System.out.println("  Ciclo interno: " + j);
    }
}

// Output:
// Ciclo esterno: 1
//   Ciclo interno: 1
// Ciclo esterno: 2
//   Ciclo interno: 1
// Ciclo esterno: 3
//   Ciclo interno: 1
```

### Labeled Break e Continue

Per controllare cicli esterni, Java supporta le etichette (labels):

```java
// Break con etichetta
esterno: for (int i = 1; i <= 3; i++) {
    System.out.println("Ciclo esterno: " + i);
    
    for (int j = 1; j <= 3; j++) {
        if (i == 2 && j == 2) {
            break esterno; // Esce dal ciclo etichettato
        }
        System.out.println("  Ciclo interno: " + j);
    }
}
System.out.println("Fine programma");

// Output:
// Ciclo esterno: 1
//   Ciclo interno: 1
//   Ciclo interno: 2
//   Ciclo interno: 3
// Ciclo esterno: 2
//   Ciclo interno: 1
// Fine programma
```

```java
// Continue con etichetta
esterno: for (int i = 1; i <= 3; i++) {
    System.out.println("Ciclo esterno: " + i);
    
    for (int j = 1; j <= 3; j++) {
        if (i == 2 && j == 2) {
            continue esterno; // Continua dal ciclo etichettato
        }
        System.out.println("  Ciclo interno: " + j);
    }
    System.out.println("Fine ciclo interno per i=" + i);
}

// Output:
// Ciclo esterno: 1
//   Ciclo interno: 1
//   Ciclo interno: 2
//   Ciclo interno: 3
// Fine ciclo interno per i=1
// Ciclo esterno: 2
//   Ciclo interno: 1
// Ciclo esterno: 3
//   Ciclo interno: 1
//   Ciclo interno: 2
//   Ciclo interno: 3
// Fine ciclo interno per i=3
```

## 5.5 L'Istruzione Return

L'istruzione `return` termina immediatamente l'esecuzione di un metodo.

### Return in Metodi void

```java
public static void verificaEta(int eta) {
    if (eta < 0) {
        System.out.println("Età non valida!");
        return; // Esce dal metodo
    }
    
    if (eta >= 18) {
        System.out.println("Maggiorenne");
    } else {
        System.out.println("Minorenne");
    }
    
    System.out.println("Controllo completato");
}
```

### Return con Valore

```java
public static int calcolaMassimo(int a, int b) {
    if (a > b) {
        return a; // Esce e restituisce a
    } else {
        return b; // Esce e restituisce b
    }
    // Codice dopo return non raggiungibile
}
```

### Return in Cicli

```java
public static boolean cercaNumero(int[] array, int numero) {
    for (int i = 0; i < array.length; i++) {
        if (array[i] == numero) {
            return true; // Trovato! Esce dal metodo
        }
    }
    return false; // Non trovato
}
```

## 5.6 Esempi Pratici Complessi

### Esempio 1: Validazione Input Complessa

```java
public static int leggiInteroValidato(Scanner scanner, int min, int max) {
    while (true) {
        System.out.printf("Inserisci un numero tra %d e %d: ", min, max);
        
        if (!scanner.hasNextInt()) {
            System.out.println("Errore: inserisci un numero valido!");
            scanner.next(); // Consuma input non valido
            continue; // Riprova
        }
        
        int numero = scanner.nextInt();
        
        if (numero < min || numero > max) {
            System.out.printf("Errore: il numero deve essere tra %d e %d!%n", min, max);
            continue; // Riprova
        }
        
        return numero; // Input valido, esci dal metodo
    }
}
```

### Esempio 2: Ricerca in Matrice

```java
public static boolean cercaInMatrice(int[][] matrice, int valore) {
    for (int i = 0; i < matrice.length; i++) {
        for (int j = 0; j < matrice[i].length; j++) {
            if (matrice[i][j] == valore) {
                System.out.printf("Valore %d trovato alla posizione [%d][%d]%n", 
                                valore, i, j);
                return true; // Trovato, esci da tutto
            }
        }
    }
    return false; // Non trovato
}
```

### Esempio 3: Menu Gerarchico

```java
public static void menuPrincipale() {
    Scanner scanner = new Scanner(System.in);
    
    while (true) {
        System.out.println("\n=== MENU PRINCIPALE ===");
        System.out.println("1. Sottomenu Calcoli");
        System.out.println("2. Sottomenu Giochi");
        System.out.println("0. Esci");
        System.out.print("Scelta: ");
        
        int scelta = scanner.nextInt();
        
        switch (scelta) {
            case 1:
                sottomenuCalcoli();
                break;
            case 2:
                sottomenuGiochi();
                break;
            case 0:
                System.out.println("Arrivederci!");
                return; // Esce dal metodo e termina il programma
            default:
                System.out.println("Opzione non valida!");
                continue; // Mostra di nuovo il menu
        }
    }
}

private static void sottomenuCalcoli() {
    Scanner scanner = new Scanner(System.in);
    
    while (true) {
        System.out.println("\n--- Sottomenu Calcoli ---");
        System.out.println("1. Addizione");
        System.out.println("2. Moltiplicazione");
        System.out.println("0. Torna al menu principale");
        System.out.print("Scelta: ");
        
        int scelta = scanner.nextInt();
        
        switch (scelta) {
            case 1:
                System.out.println("Funzione addizione eseguita");
                break;
            case 2:
                System.out.println("Funzione moltiplicazione eseguita");
                break;
            case 0:
                return; // Torna al menu principale
            default:
                System.out.println("Opzione non valida!");
        }
    }
}
```

## 5.7 Algoritmi con Controllo del Flusso

### Algoritmo di Ricerca Lineare Ottimizzato

```java
public static int ricercaLineare(int[] array, int elemento) {
    for (int i = 0; i < array.length; i++) {
        if (array[i] == elemento) {
            return i; // Trovato! Termina immediatamente
        }
    }
    return -1; // Non trovato
}
```

### Algoritmo Primo più Efficiente

```java
public static boolean isPrimo(int numero) {
    if (numero < 2) {
        return false;
    }
    
    if (numero == 2) {
        return true;
    }
    
    if (numero % 2 == 0) {
        return false; // Pari, quindi non primo
    }
    
    // Controlla solo divisori dispari fino alla radice quadrata
    for (int i = 3; i * i <= numero; i += 2) {
        if (numero % i == 0) {
            return false; // Trovato divisore, non è primo
        }
    }
    
    return true; // Nessun divisore trovato, è primo
}
```

### Elaborazione di Array con Condizioni

```java
public static void elaboraArray(int[] array) {
    for (int i = 0; i < array.length; i++) {
        // Salta elementi negativi
        if (array[i] < 0) {
            System.out.println("Saltato elemento negativo: " + array[i]);
            continue;
        }
        
        // Ferma se trova uno zero
        if (array[i] == 0) {
            System.out.println("Trovato zero, elaborazione interrotta");
            break;
        }
        
        // Elabora elemento valido
        array[i] = array[i] * 2;
        System.out.println("Elemento elaborato: " + array[i]);
    }
}
```

## 5.8 Best Practices e Linee Guida

### Quando Usare Break

✅ **Buoni casi d'uso:**
- Uscita da cicli di ricerca quando l'elemento è trovato
- Implementazione di menu con opzione "esci"
- Validazione input con retry
- Terminazione anticipata per condizioni di errore

❌ **Da evitare:**
- Break multipli nello stesso ciclo (rende il codice confuso)
- Break come sostituto per condizioni del ciclo ben progettate

### Quando Usare Continue

✅ **Buoni casi d'uso:**
- Saltare elementi non validi in un array
- Filtri di elaborazione dati
- Validazione input con richiesta di nuovo input

❌ **Da evitare:**
- Continue eccessivi che rendono difficile seguire la logica
- Continue invece di condizioni if ben strutturate

### Quando Usare Return

✅ **Buoni casi d'uso:**
- Validazione parametri all'inizio dei metodi
- Uscita anticipata quando il risultato è determinato
- Evitare nidificazione eccessiva di if

❌ **Da evitare:**
- Return multipli che rendono difficile il debugging
- Return nel mezzo di logica complessa

## 5.9 Errori Comuni

### Errore 1: Break nel Posto Sbagliato

```java
// SBAGLIATO
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        System.out.println("Cinque trovato!");
    }
    break; // Esce sempre alla prima iterazione!
}

// CORRETTO
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        System.out.println("Cinque trovato!");
        break; // Esce solo quando trova 5
    }
}
```

### Errore 2: Continue Malposizionato

```java
// SBAGLIATO - il contatore non viene incrementato
int i = 0;
while (i < 10) {
    if (i % 2 == 0) {
        continue; // ERRORE: i non viene mai incrementato per numeri pari
    }
    System.out.println(i);
    i++;
}

// CORRETTO
int i = 0;
while (i < 10) {
    if (i % 2 == 0) {
        i++; // Incrementa prima di continue
        continue;
    }
    System.out.println(i);
    i++;
}
```

### Errore 3: Return Irraggiungibile

```java
// SBAGLIATO - codice morto
public static int calcolaValore(int x) {
    return x * 2;
    System.out.println("Mai eseguito"); // ERRORE: codice irraggiungibile!
}

// CORRETTO
public static int calcolaValore(int x) {
    int risultato = x * 2;
    System.out.println("Calcolo completato");
    return risultato;
}
```

## 5.10 Esercizi di Verifica

### Esercizio 1
Cosa stampa questo codice?

```java
for (int i = 1; i <= 5; i++) {
    if (i == 3) {
        continue;
    }
    if (i == 4) {
        break;
    }
    System.out.print(i + " ");
}
```

**Risposta**: `1 2 `

### Esercizio 2
Il seguente metodo compila correttamente?

```java
public static int metodoTest(int x) {
    if (x > 0) {
        return x;
    } else if (x < 0) {
        return -x;
    }
    // Manca return per x == 0
}
```

**Risposta**: No, errore di compilazione. Manca il return per il caso x == 0.

Il controllo del flusso è uno strumento potente che, usato correttamente, rende i programmi più efficienti e leggibili. La chiave è usare queste istruzioni con parsimonia e solo quando migliorano realmente la chiarezza del codice.
