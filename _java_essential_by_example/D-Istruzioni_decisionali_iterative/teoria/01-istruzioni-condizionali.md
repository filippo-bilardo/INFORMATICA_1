# Istruzioni Condizionali in Java

## 📋 Panoramica
Le istruzioni condizionali permettono al programma di prendere decisioni e eseguire blocchi di codice diversi in base a condizioni specifiche. Sono il fondamento della logica di controllo in programmazione.

## 🎯 Obiettivi
- Padroneggiare if, if-else, if-else-if
- Comprendere l'ordine di valutazione delle condizioni
- Imparare best practices per condizioni leggibili
- Evitare errori comuni nelle strutture condizionali

---

## 🔍 Tipi di Istruzioni Condizionali

### 1. If Semplice

L'istruzione `if` più basilare esegue un blocco di codice solo se la condizione è vera.

```java
// Sintassi base
if (condizione) {
    // codice da eseguire se condizione è true
}

// Esempio pratico
int eta = 20;
if (eta >= 18) {
    System.out.println("Sei maggiorenne!");
}
```

**Caratteristiche:**
- La condizione deve essere un'espressione boolean
- Le parentesi graffe `{}` sono consigliate sempre, anche per un'istruzione
- Se la condizione è false, il blocco viene saltato

### 2. If-Else

Permette di eseguire un blocco di codice alternativo quando la condizione è falsa.

```java
// Sintassi
if (condizione) {
    // blocco se condizione è true
} else {
    // blocco se condizione è false
}

// Esempio pratico
double voto = 7.5;
if (voto >= 6.0) {
    System.out.println("Promosso! 🎉");
    System.out.println("Complimenti per il risultato!");
} else {
    System.out.println("Non promosso 😞");
    System.out.println("Riprova la prossima volta!");
}
```

### 3. If-Else-If (Cascata)

Per gestire multiple condizioni in sequenza.

```java
// Sintassi completa
if (condizione1) {
    // blocco 1
} else if (condizione2) {
    // blocco 2
} else if (condizione3) {
    // blocco 3
} else {
    // blocco di default (opzionale)
}

// Esempio pratico: sistema di voti
double media = 8.2;

if (media >= 9.0) {
    System.out.println("Eccellente! 🏆");
    System.out.println("Sei tra i migliori della classe!");
} else if (media >= 8.0) {
    System.out.println("Ottimo! 👍");
    System.out.println("Continua così!");
} else if (media >= 7.0) {
    System.out.println("Buono! 😊");
    System.out.println("Stai andando bene!");
} else if (media >= 6.0) {
    System.out.println("Sufficiente 👌");
    System.out.println("Puoi migliorare!");
} else {
    System.out.println("Insufficiente 😔");
    System.out.println("Serve più impegno!");
}
```

---

## 🧠 Condizioni e Operatori Logici

### Operatori di Confronto
```java
int a = 10, b = 20;

// Uguaglianza e disuguaglianza
if (a == b) { /* uguale */ }
if (a != b) { /* diverso */ }

// Confronti numerici
if (a < b)  { /* minore */ }
if (a <= b) { /* minore o uguale */ }
if (a > b)  { /* maggiore */ }
if (a >= b) { /* maggiore o uguale */ }
```

### Operatori Logici
```java
int eta = 25;
boolean haLicenza = true;
double salario = 2500.0;

// AND logico (&&) - tutte le condizioni devono essere vere
if (eta >= 18 && haLicenza) {
    System.out.println("Può guidare");
}

// OR logico (||) - almeno una condizione deve essere vera
if (salario > 3000.0 || eta < 30) {
    System.out.println("Candidato interessante");
}

// NOT logico (!) - nega la condizione
if (!(eta < 18)) {
    System.out.println("Non è minorenne");
}
```

### Combinazioni Complesse
```java
// Esempio: controllo accesso VIP
int eta = 28;
boolean haInvito = true;
double quota = 150.0;
String tipoCarta = "GOLD";

if ((eta >= 21 && haInvito) || 
    (quota >= 100.0 && tipoCarta.equals("GOLD"))) {
    System.out.println("Accesso VIP consentito! ✨");
} else if (eta >= 18 && quota >= 50.0) {
    System.out.println("Accesso standard consentito");
} else {
    System.out.println("Accesso negato");
}
```

---

## 🎯 Esempi Pratici Completi

### Esempio 1: Calcolatore di Tasse
```java
/**
 * Calcola le tasse in base al reddito
 */
public class CalcolatoreTasse {
    public static void main(String[] args) {
        double reddito = 45000.0;
        double tasse = 0.0;
        double aliquota = 0.0;
        
        if (reddito <= 15000) {
            aliquota = 0.23; // 23%
            tasse = reddito * aliquota;
        } else if (reddito <= 28000) {
            // Scaglione base + eccedenza
            tasse = 15000 * 0.23;
            tasse += (reddito - 15000) * 0.27; // 27%
            aliquota = 0.27;
        } else if (reddito <= 55000) {
            tasse = 15000 * 0.23;
            tasse += 13000 * 0.27; // (28000-15000)
            tasse += (reddito - 28000) * 0.38; // 38%
            aliquota = 0.38;
        } else {
            tasse = 15000 * 0.23;
            tasse += 13000 * 0.27;
            tasse += 27000 * 0.38; // (55000-28000)
            tasse += (reddito - 55000) * 0.41; // 41%
            aliquota = 0.41;
        }
        
        System.out.printf("💰 Reddito: €%.2f%n", reddito);
        System.out.printf("📊 Aliquota massima: %.0f%%%n", aliquota * 100);
        System.out.printf("💸 Tasse da pagare: €%.2f%n", tasse);
        System.out.printf("💵 Reddito netto: €%.2f%n", reddito - tasse);
    }
}
```

### Esempio 2: Sistema di Login
```java
/**
 * Sistema di autenticazione con tentativi limitati
 */
import java.util.Scanner;

public class SistemaLogin {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Credenziali corrette (in un'app reale sarebbero criptate)
        String usernameCorretto = "admin";
        String passwordCorretta = "password123";
        
        int tentativiMassimi = 3;
        int tentativiEffettuati = 0;
        boolean loginRiuscito = false;
        
        System.out.println("🔐 SISTEMA DI LOGIN");
        System.out.println("=".repeat(30));
        
        while (tentativiEffettuati < tentativiMassimi && !loginRiuscito) {
            System.out.print("👤 Username: ");
            String username = scanner.nextLine();
            
            System.out.print("🔑 Password: ");
            String password = scanner.nextLine();
            
            tentativiEffettuati++;
            
            if (username.equals(usernameCorretto) && password.equals(passwordCorretta)) {
                loginRiuscito = true;
                System.out.println("\n✅ LOGIN RIUSCITO!");
                System.out.println("Benvenuto nel sistema! 🎉");
            } else {
                int tentativiRimasti = tentativiMassimi - tentativiEffettuati;
                
                if (tentativiRimasti > 0) {
                    System.out.printf("❌ Credenziali errate! Tentativi rimasti: %d%n%n", 
                                    tentativiRimasti);
                } else {
                    System.out.println("\n🚫 ACCESSO BLOCCATO!");
                    System.out.println("Troppi tentativi falliti. Contatta l'amministratore.");
                }
            }
        }
        
        scanner.close();
    }
}
```

### Esempio 3: Convertitore di Voti
```java
/**
 * Converte voti numerici in lettere (sistema americano)
 */
import java.util.Scanner;

public class ConvertitoreVoti {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("📚 CONVERTITORE VOTI (0-100 → A-F)");
        System.out.print("Inserisci il voto numerico: ");
        
        if (scanner.hasNextDouble()) {
            double voto = scanner.nextDouble();
            
            if (voto < 0 || voto > 100) {
                System.out.println("❌ Voto non valido! Deve essere tra 0 e 100.");
            } else {
                String letteraVoto;
                String descrizione;
                
                if (voto >= 97) {
                    letteraVoto = "A+";
                    descrizione = "Eccellente";
                } else if (voto >= 93) {
                    letteraVoto = "A";
                    descrizione = "Ottimo";
                } else if (voto >= 90) {
                    letteraVoto = "A-";
                    descrizione = "Molto buono";
                } else if (voto >= 87) {
                    letteraVoto = "B+";
                    descrizione = "Buono";
                } else if (voto >= 83) {
                    letteraVoto = "B";
                    descrizione = "Discreto";
                } else if (voto >= 80) {
                    letteraVoto = "B-";
                    descrizione = "Sufficiente più";
                } else if (voto >= 77) {
                    letteraVoto = "C+";
                    descrizione = "Sufficiente";
                } else if (voto >= 73) {
                    letteraVoto = "C";
                    descrizione = "Appena sufficiente";
                } else if (voto >= 70) {
                    letteraVoto = "C-";
                    descrizione = "Quasi sufficiente";
                } else if (voto >= 67) {
                    letteraVoto = "D+";
                    descrizione = "Insufficiente lieve";
                } else if (voto >= 65) {
                    letteraVoto = "D";
                    descrizione = "Insufficiente";
                } else {
                    letteraVoto = "F";
                    descrizione = "Gravemente insufficiente";
                }
                
                System.out.printf("%n📊 RISULTATO:%n");
                System.out.printf("Voto numerico: %.1f%n", voto);
                System.out.printf("Voto lettera: %s%n", letteraVoto);
                System.out.printf("Descrizione: %s%n", descrizione);
                
                // Consigli basati sulla fascia
                if (voto >= 90) {
                    System.out.println("🏆 Eccellente lavoro! Continua così!");
                } else if (voto >= 80) {
                    System.out.println("👍 Buon lavoro! Piccoli miglioramenti ti porteranno all'eccellenza!");
                } else if (voto >= 70) {
                    System.out.println("👌 Risultato accettabile, ma c'è margine di miglioramento!");
                } else {
                    System.out.println("📚 Serve più studio! Non arrenderti!");
                }
            }
        } else {
            System.out.println("❌ Input non valido! Inserisci un numero.");
        }
        
        scanner.close();
    }
}
```

---

## ⚠️ Errori Comuni e Come Evitarli

### 1. Assegnazione invece di Confronto
```java
// ❌ SBAGLIATO - assegnazione
if (eta = 18) { // Errore di compilazione
    // ...
}

// ✅ CORRETTO - confronto
if (eta == 18) {
    // ...
}
```

### 2. Confronto di String con ==
```java
String nome1 = "Mario";
String nome2 = scanner.nextLine();

// ❌ SBAGLIATO - confronta riferimenti
if (nome1 == nome2) {
    // ...
}

// ✅ CORRETTO - confronta contenuto
if (nome1.equals(nome2)) {
    // ...
}
```

### 3. Condizioni Non Esclusive
```java
int voto = 85;

// ❌ PROBLEMA - controlli ridondanti
if (voto >= 90) {
    System.out.println("A");
}
if (voto >= 80) { // Verrà eseguito anche per voti >= 90!
    System.out.println("B");
}

// ✅ CORRETTO - usa else if
if (voto >= 90) {
    System.out.println("A");
} else if (voto >= 80) {
    System.out.println("B");
}
```

### 4. Mancanza di Parentesi Graffe
```java
// ❌ PERICOLOSO - ambiguo
if (eta >= 18)
    System.out.println("Maggiorenne");
    System.out.println("Benvenuto!"); // Sempre eseguito!

// ✅ CORRETTO - sempre usare {}
if (eta >= 18) {
    System.out.println("Maggiorenne");
    System.out.println("Benvenuto!");
}
```

---

## 💡 Best Practices

### 1. Condizioni Leggibili
```java
// ❌ Difficile da leggere
if (!(a < 18 || b > 100 && c != 0)) {
    // ...
}

// ✅ Più chiaro
boolean maggiorenne = a >= 18;
boolean valoreValido = b <= 100;
boolean denominatoreNonZero = c != 0;

if (maggiorenne && valoreValido && denominatoreNonZero) {
    // ...
}
```

### 2. Evitare Condizioni Troppo Profonde
```java
// ❌ Troppo annidato
if (utente != null) {
    if (utente.eta >= 18) {
        if (utente.haLicenza) {
            if (utente.credito > 100) {
                // azione
            }
        }
    }
}

// ✅ Early return o condizioni combinate
if (utente == null || utente.eta < 18 || 
    !utente.haLicenza || utente.credito <= 100) {
    return; // o gestisci l'errore
}
// azione
```

### 3. Costanti per Valori Magici
```java
// ❌ Numeri magici
if (eta >= 18 && credito > 1000) {
    // ...
}

// ✅ Costanti denominate
final int ETA_MAGGIORENNE = 18;
final double CREDITO_MINIMO = 1000.0;

if (eta >= ETA_MAGGIORENNE && credito > CREDITO_MINIMO) {
    // ...
}
```

---

## 🧪 Esercizi di Verifica

### Esercizio 1: Debug
Trova e correggi gli errori in questo codice:
```java
int voto = 75;
if (voto = 100) {
    System.out.println("Perfetto!");
} else if voto >= 90 {
    System.out.println("Eccellente!");
} else if (voto >= 80)
    System.out.println("Ottimo!");
    System.out.println("Complimenti!");
else if (voto >= 70) {
    System.out.println("Buono!");
else {
    System.out.println("Da migliorare!");
}
```

<details>
<summary>💡 Soluzione</summary>

```java
int voto = 75;
if (voto == 100) { // == invece di =
    System.out.println("Perfetto!");
} else if (voto >= 90) { // mancavano parentesi
    System.out.println("Eccellente!");
} else if (voto >= 80) {
    System.out.println("Ottimo!");
    System.out.println("Complimenti!"); // ora dentro le graffe
} else if (voto >= 70) {
    System.out.println("Buono!");
} // mancava la graffa di chiusura
else {
    System.out.println("Da migliorare!");
}
```
</details>

### Esercizio 2: Logica
Scrivi una condizione che sia vera quando:
- L'età è tra 25 e 65 anni (inclusi)
- E il salario è superiore a 30,000
- Oppure la persona ha più di 5 anni di esperienza

<details>
<summary>💡 Soluzione</summary>

```java
if ((eta >= 25 && eta <= 65 && salario > 30000) || 
    (esperienza > 5)) {
    // condizione soddisfatta
}
```
</details>

---

## 🔗 Collegamenti

- **Prossimo**: [Switch Statement](02-switch-statement.md)
- **Pratica**: [Esempi Condizioni](../esempi/CondizioniDemo.java)
- **Esercizi**: [Condizioni Base](../esercizi/README.md#condizioni)

---

*Ricorda: Le condizioni sono il cuore della logica di programmazione. Prenditi il tempo per comprenderle bene!* 🎯
