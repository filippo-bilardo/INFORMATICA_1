# Switch Statement in Java

## 📋 Panoramica
Il `switch` statement è una struttura di controllo che permette di eseguire diverse azioni basate sul valore di una variabile. È un'alternativa più pulita a lunghe catene di `if-else` quando si deve confrontare una variabile con multipli valori costanti.

## 🎯 Obiettivi
- Padroneggiare la sintassi del switch tradizionale
- Comprendere quando preferire switch a if-else
- Imparare il nuovo switch expression (Java 14+)
- Evitare il fall-through non intenzionale
- Ottimizzare il codice con switch efficaci

---

## 🔍 Switch Tradizionale

### Sintassi Base
```java
switch (variabile) {
    case valore1:
        // azioni per valore1
        break;
    case valore2:
        // azioni per valore2
        break;
    case valore3:
        // azioni per valore3
        break;
    default:
        // azione di default (opzionale)
        break;
}
```

### Tipi Supportati
Il switch supporta:
- `byte`, `short`, `int`, `char`
- `String` (da Java 7)
- `enum`
- Wrapper classes: `Byte`, `Short`, `Integer`, `Character`

```java
// Switch con int
int giorno = 3;
switch (giorno) {
    case 1:
        System.out.println("Lunedì");
        break;
    case 2:
        System.out.println("Martedì");
        break;
    case 3:
        System.out.println("Mercoledì");
        break;
    default:
        System.out.println("Giorno non valido");
}

// Switch con String
String mese = "gennaio";
switch (mese.toLowerCase()) {
    case "gennaio":
    case "febbraio":
    case "dicembre":
        System.out.println("Inverno");
        break;
    case "marzo":
    case "aprile":
    case "maggio":
        System.out.println("Primavera");
        break;
    case "giugno":
    case "luglio":
    case "agosto":
        System.out.println("Estate");
        break;
    case "settembre":
    case "ottobre":
    case "novembre":
        System.out.println("Autunno");
        break;
    default:
        System.out.println("Mese non riconosciuto");
}
```

---

## 🔄 Fall-Through e Break

### Il Comportamento Fall-Through
Senza `break`, l'esecuzione continua nel caso successivo:

```java
int numero = 2;
System.out.println("Numero: " + numero);

switch (numero) {
    case 1:
        System.out.println("Uno");
        // ATTENZIONE: manca break!
    case 2:
        System.out.println("Due");
        // ATTENZIONE: manca break!
    case 3:
        System.out.println("Tre");
        break;
    default:
        System.out.println("Altro");
}

// Output:
// Numero: 2
// Due
// Tre
```

### Fall-Through Intenzionale
A volte il fall-through è utile:

```java
char carattere = 'A';
switch (carattere) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        System.out.println("Vocale");
        break;
    default:
        System.out.println("Consonante");
}
```

---

## 💻 Esempi Pratici Completi

### Esempio 1: Calcolatore Semplice
```java
/**
 * Calcolatore con menu switch
 */
import java.util.Scanner;

public class CalcolatoreSwitch {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("🧮 CALCOLATORE SEMPLICE");
        System.out.println("=".repeat(30));
        
        System.out.print("Primo numero: ");
        double num1 = scanner.nextDouble();
        
        System.out.print("Secondo numero: ");
        double num2 = scanner.nextDouble();
        
        System.out.println("\nOperazioni disponibili:");
        System.out.println("+ : Addizione");
        System.out.println("- : Sottrazione");
        System.out.println("* : Moltiplicazione");
        System.out.println("/ : Divisione");
        System.out.println("% : Modulo");
        System.out.println("^ : Potenza");
        
        System.out.print("\nScegli operazione: ");
        char operazione = scanner.next().charAt(0);
        
        double risultato = 0;
        boolean operazioneValida = true;
        
        switch (operazione) {
            case '+':
                risultato = num1 + num2;
                System.out.printf("%.2f + %.2f = %.2f%n", num1, num2, risultato);
                break;
                
            case '-':
                risultato = num1 - num2;
                System.out.printf("%.2f - %.2f = %.2f%n", num1, num2, risultato);
                break;
                
            case '*':
                risultato = num1 * num2;
                System.out.printf("%.2f × %.2f = %.2f%n", num1, num2, risultato);
                break;
                
            case '/':
                if (num2 != 0) {
                    risultato = num1 / num2;
                    System.out.printf("%.2f ÷ %.2f = %.2f%n", num1, num2, risultato);
                } else {
                    System.out.println("❌ Errore: Divisione per zero!");
                    operazioneValida = false;
                }
                break;
                
            case '%':
                if (num2 != 0) {
                    risultato = num1 % num2;
                    System.out.printf("%.2f %% %.2f = %.2f%n", num1, num2, risultato);
                } else {
                    System.out.println("❌ Errore: Modulo di zero!");
                    operazioneValida = false;
                }
                break;
                
            case '^':
                risultato = Math.pow(num1, num2);
                System.out.printf("%.2f ^ %.2f = %.2f%n", num1, num2, risultato);
                break;
                
            default:
                System.out.println("❌ Operazione non riconosciuta: " + operazione);
                operazioneValida = false;
        }
        
        if (operazioneValida) {
            // Informazioni aggiuntive sul risultato
            if (risultato == (int) risultato) {
                System.out.println("ℹ️ Il risultato è un numero intero");
            }
            if (risultato < 0) {
                System.out.println("ℹ️ Il risultato è negativo");
            }
            if (risultato > 1000000) {
                System.out.println("ℹ️ Il risultato è molto grande!");
            }
        }
        
        scanner.close();
    }
}
```

### Esempio 2: Sistema di Voti con Switch
```java
/**
 * Convertitore di voti numerici in lettere
 */
import java.util.Scanner;

public class SistemaVotiSwitch {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("📚 SISTEMA DI VALUTAZIONE");
        System.out.println("=".repeat(30));
        
        System.out.print("Inserisci il voto (0-10): ");
        
        if (scanner.hasNextInt()) {
            int voto = scanner.nextInt();
            
            if (voto < 0 || voto > 10) {
                System.out.println("❌ Voto non valido! Deve essere tra 0 e 10.");
            } else {
                String lettera;
                String descrizione;
                String consigli;
                
                switch (voto) {
                    case 10:
                        lettera = "A+";
                        descrizione = "Eccellente";
                        consigli = "Perfetto! Sei un esempio per tutti! 🏆";
                        break;
                        
                    case 9:
                        lettera = "A";
                        descrizione = "Ottimo";
                        consigli = "Eccellente lavoro! Continua così! 🌟";
                        break;
                        
                    case 8:
                        lettera = "B+";
                        descrizione = "Molto buono";
                        consigli = "Molto bene! Piccoli perfezionamenti per l'eccellenza! 👍";
                        break;
                        
                    case 7:
                        lettera = "B";
                        descrizione = "Buono";
                        consigli = "Buon lavoro! Continua a impegnarti! 😊";
                        break;
                        
                    case 6:
                        lettera = "C";
                        descrizione = "Sufficiente";
                        consigli = "Sufficiente, ma puoi fare di meglio! 💪";
                        break;
                        
                    case 5:
                        lettera = "D";
                        descrizione = "Insufficiente";
                        consigli = "Serve più studio! Non mollare! 📚";
                        break;
                        
                    case 4:
                    case 3:
                    case 2:
                    case 1:
                    case 0:
                        lettera = "F";
                        descrizione = "Gravemente insufficiente";
                        consigli = "È necessario un impegno maggiore. Chiedi aiuto! 🆘";
                        break;
                        
                    default:
                        lettera = "?";
                        descrizione = "Errore";
                        consigli = "Errore di sistema";
                }
                
                // Output formattato
                System.out.println("\n" + "─".repeat(40));
                System.out.println("📊 RISULTATO VALUTAZIONE");
                System.out.println("─".repeat(40));
                System.out.printf("Voto numerico: %d/10%n", voto);
                System.out.printf("Voto lettera: %s%n", lettera);
                System.out.printf("Descrizione: %s%n", descrizione);
                System.out.printf("💬 %s%n", consigli);
                
                // Statistiche aggiuntive
                System.out.println("\n📈 STATISTICHE:");
                System.out.printf("Percentuale: %d%%%n", voto * 10);
                
                if (voto >= 6) {
                    System.out.println("✅ PROMOSSO");
                } else {
                    System.out.println("❌ NON PROMOSSO");
                }
                
                // Suggerimenti per migliorare
                System.out.println("\n💡 SUGGERIMENTI:");
                switch (voto / 2) { // Raggruppamento intelligente
                    case 5: // voto 10
                        System.out.println("• Mantieni questo livello di eccellenza");
                        System.out.println("• Aiuta i compagni in difficoltà");
                        break;
                    case 4: // voti 8-9
                        System.out.println("• Continua con costanza");
                        System.out.println("• Cerca di perfezionare i dettagli");
                        break;
                    case 3: // voti 6-7
                        System.out.println("• Aumenta le ore di studio");
                        System.out.println("• Chiedi chiarimenti sui punti difficili");
                        break;
                    case 2: // voti 4-5
                    case 1: // voti 2-3
                    case 0: // voti 0-1
                        System.out.println("• Rivedi i concetti fondamentali");
                        System.out.println("• Chiedi supporto al docente");
                        System.out.println("• Organizza meglio il tempo di studio");
                        break;
                }
            }
        } else {
            System.out.println("❌ Input non valido! Inserisci un numero intero.");
        }
        
        scanner.close();
    }
}
```

---

## 🆕 Switch Expression (Java 14+)

### Sintassi Moderna
```java
// Switch expression con frecce
String stagione = switch (mese) {
    case 12, 1, 2 -> "Inverno";
    case 3, 4, 5 -> "Primavera";
    case 6, 7, 8 -> "Estate";
    case 9, 10, 11 -> "Autunno";
    default -> "Mese non valido";
};

// Con blocchi di codice
String messaggio = switch (voto) {
    case 10 -> {
        System.out.println("Registrando eccellenza...");
        yield "Eccellente! 🏆";
    }
    case 8, 9 -> "Ottimo! 👍";
    case 6, 7 -> "Buono! 😊";
    default -> "Da migliorare 📚";
};
```

### Vantaggi del Switch Expression
```java
// ❌ Switch tradizionale - verboso
String tipoGiorno;
switch (giorno) {
    case 1:
    case 7:
        tipoGiorno = "Weekend";
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        tipoGiorno = "Feriale";
        break;
    default:
        tipoGiorno = "Errore";
        break;
}

// ✅ Switch expression - conciso
String tipoGiorno = switch (giorno) {
    case 1, 7 -> "Weekend";
    case 2, 3, 4, 5, 6 -> "Feriale";
    default -> "Errore";
};
```

---

## 🆚 Switch vs If-Else

### Quando Usare Switch
✅ **Switch è preferibile quando:**
- Confronti una variabile con valori costanti
- Hai molti case (>3-4)
- I valori sono discreti e ben definiti
- Vuoi codice più leggibile e performante

```java
// ✅ Perfetto per switch
switch (comandoMenu) {
    case 1 -> aggiungiUtente();
    case 2 -> rimuoviUtente();
    case 3 -> modificaUtente();
    case 4 -> visualizzaUtenti();
    case 0 -> esci();
    default -> comandoNonValido();
}
```

### Quando Usare If-Else
✅ **If-else è preferibile quando:**
- Hai condizioni complesse o range
- Confronti multiple variabili
- Usi operatori logici
- Hai espressioni booleane complesse

```java
// ✅ Meglio con if-else
if (eta >= 18 && eta <= 65 && salario > 30000) {
    // logica complessa
} else if (esperienza > 10 || certificazioni >= 3) {
    // altra logica
} else {
    // default
}
```

---

## ⚠️ Errori Comuni e Soluzioni

### 1. Dimenticare il Break
```java
// ❌ SBAGLIATO - fall-through non intenzionale
switch (voto) {
    case 10:
        System.out.println("Eccellente!");
        // manca break - continua al caso successivo!
    case 9:
        System.out.println("Ottimo!");
        break;
}

// ✅ CORRETTO
switch (voto) {
    case 10:
        System.out.println("Eccellente!");
        break; // ✅
    case 9:
        System.out.println("Ottimo!");
        break;
}
```

### 2. Case Non Costanti
```java
int valore = 10;

// ❌ SBAGLIATO - valore non è una costante
switch (numero) {
    case valore: // Errore di compilazione!
        System.out.println("Match");
        break;
}

// ✅ CORRETTO - usa costante
final int VALORE_COSTANTE = 10;
switch (numero) {
    case VALORE_COSTANTE: // ✅
        System.out.println("Match");
        break;
}
```

### 3. Tipi Non Supportati
```java
// ❌ SBAGLIATO - double non supportato
double prezzo = 19.99;
switch (prezzo) { // Errore di compilazione!
    case 19.99:
        System.out.println("Sconto!");
        break;
}

// ✅ ALTERNATIVA con if-else
if (prezzo == 19.99) {
    System.out.println("Sconto!");
}
```

---

## 💡 Best Practices

### 1. Sempre Includere Default
```java
// ✅ Sempre fornire un caso default
switch (scelta) {
    case 1:
        // azione 1
        break;
    case 2:
        // azione 2
        break;
    default:
        System.out.println("Scelta non valida!");
        break;
}
```

### 2. Raggruppare Case Correlati
```java
// ✅ Raggruppa logicamente
switch (carattere) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
    case 'A': case 'E': case 'I': case 'O': case 'U':
        System.out.println("Vocale");
        break;
    default:
        System.out.println("Consonante");
        break;
}
```

### 3. Usare Enums per Switch
```java
enum Stagione {
    PRIMAVERA, ESTATE, AUTUNNO, INVERNO
}

// ✅ Switch con enum è type-safe
switch (stagione) {
    case PRIMAVERA:
        System.out.println("Tempo di semina");
        break;
    case ESTATE:
        System.out.println("Tempo di vacanze");
        break;
    case AUTUNNO:
        System.out.println("Tempo di raccolta");
        break;
    case INVERNO:
        System.out.println("Tempo di riposo");
        break;
}
```

---

## 🧪 Esercizi di Verifica

### Esercizio 1: Menu Ristorante
Crea un sistema di ordinazione con switch che:
- Mostri menu con 5 piatti
- Calcoli il prezzo totale
- Applichi sconti in base alla quantità

<details>
<summary>💡 Traccia</summary>

```java
switch (sceltaPiatto) {
    case 1: // Pizza Margherita - €8.50
    case 2: // Pasta Carbonara - €9.00
    case 3: // Insalata Caesar - €7.50
    // ... implementa la logica
}
```
</details>

### Esercizio 2: Convertitore Romano
Converti numeri (1-10) in numeri romani usando switch.

### Esercizio 3: Debug Switch
Trova l'errore:
```java
String giorno = "lunedì";
switch (giorno) {
    case "lunedì":
        System.out.println("Inizio settimana");
    case "venerdì":
        System.out.println("Fine settimana");
        break;
    default:
        System.out.println("Giorno normale");
}
```

---

## 🔗 Collegamenti

- **Precedente**: [Istruzioni Condizionali](01-istruzioni-condizionali.md)
- **Prossimo**: [Ciclo For](03-ciclo-for.md)
- **Pratica**: [Menu Interattivo](../esempi/MenuInterattivo.java)

---

*Il switch è uno strumento potente per codice pulito e leggibile. Usalo saggiamente!* 🎯
