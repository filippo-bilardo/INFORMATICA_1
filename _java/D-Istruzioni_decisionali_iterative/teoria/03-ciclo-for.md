# Ciclo For in Java

## 📋 Panoramica
Il ciclo `for` è una delle strutture iterative più utilizzate in Java. Permette di ripetere un blocco di codice per un numero determinato di volte o di iterare attraverso collezioni di dati. È particolarmente utile quando si conosce in anticipo il numero di iterazioni necessarie.

## 🎯 Obiettivi
- Padroneggiare la sintassi del for classico
- Comprendere il for-each (enhanced for)
- Implementare cicli annidati efficacemente
- Ottimizzare performance con for appropriati
- Evitare errori comuni nei cicli

---

## 🔍 For Classico

### Sintassi Base
```java
for (inizializzazione; condizione; incremento) {
    // codice da ripetere
}
```

**Componenti:**
- **Inizializzazione**: Eseguita una sola volta all'inizio
- **Condizione**: Valutata prima di ogni iterazione
- **Incremento**: Eseguito alla fine di ogni iterazione

### Esempio Fondamentale
```java
// Stampa numeri da 1 a 10
for (int i = 1; i <= 10; i++) {
    System.out.println("Numero: " + i);
}

// Stampa numeri pari da 2 a 20
for (int i = 2; i <= 20; i += 2) {
    System.out.printf("Numero pari: %d%n", i);
}

// Conto alla rovescia
for (int i = 10; i >= 1; i--) {
    System.out.printf("Conto alla rovescia: %d%n", i);
    if (i == 1) {
        System.out.println("🚀 LANCIO!");
    }
}
```

---

## 🔄 Varianti del For

### For con Multiple Variabili
```java
// Multiple inizializzazioni e incrementi
for (int i = 0, j = 10; i < j; i++, j--) {
    System.out.printf("i=%d, j=%d, somma=%d%n", i, j, i + j);
}

// Output:
// i=0, j=10, somma=10
// i=1, j=9, somma=10
// i=2, j=8, somma=10
// ...
```

### For Infinito (con break)
```java
// Ciclo infinito controllato
for (;;) {
    System.out.print("Inserisci un numero (0 per uscire): ");
    int numero = scanner.nextInt();
    
    if (numero == 0) {
        break; // Esce dal ciclo
    }
    
    System.out.println("Quadrato: " + (numero * numero));
}
```

### For con Condizioni Complesse
```java
// Condizioni elaborate
for (int i = 1; i <= 100 && i * i < 50; i += 2) {
    System.out.printf("i=%d, i²=%d%n", i, i * i);
}
```

---

## 🚀 For-Each (Enhanced For)

### Sintassi
```java
for (Tipo elemento : collezione) {
    // usa elemento
}
```

### Con Array
```java
int[] numeri = {10, 20, 30, 40, 50};

// ✅ For-each - più leggibile
for (int numero : numeri) {
    System.out.println("Numero: " + numero);
}

// vs For classico
for (int i = 0; i < numeri.length; i++) {
    System.out.println("Numero: " + numeri[i]);
}
```

### Con Stringhe
```java
String[] nomi = {"Mario", "Luigi", "Peach", "Bowser"};

for (String nome : nomi) {
    System.out.printf("Ciao %s! 👋%n", nome);
    
    if (nome.length() > 5) {
        System.out.println("  → Nome lungo!");
    }
}
```

---

## 💻 Esempi Pratici Completi

### Esempio 1: Tabella delle Moltiplicazioni
```java
/**
 * Genera e visualizza la tabella delle moltiplicazioni
 */
import java.util.Scanner;

public class TabellaMoltiplicazioni {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("🧮 TABELLA DELLE MOLTIPLICAZIONI");
        System.out.println("=".repeat(50));
        
        System.out.print("Fino a quale numero? (1-20): ");
        int max = scanner.nextInt();
        
        if (max < 1 || max > 20) {
            System.out.println("❌ Numero non valido! Usando 10 come default.");
            max = 10;
        }
        
        // Header della tabella
        System.out.printf("%4s", "");
        for (int j = 1; j <= max; j++) {
            System.out.printf("%4d", j);
        }
        System.out.println();
        System.out.println("  " + "─".repeat(max * 4 + 2));
        
        // Righe della tabella
        for (int i = 1; i <= max; i++) {
            System.out.printf("%2d│", i); // Numero di riga
            
            for (int j = 1; j <= max; j++) {
                int prodotto = i * j;
                
                // Colorazione per pattern interessanti
                if (prodotto == i * i) {
                    System.out.printf("*%2d*", prodotto); // Quadrati perfetti
                } else if (prodotto % 10 == 0) {
                    System.out.printf("[%2d]", prodotto); // Multipli di 10
                } else {
                    System.out.printf("%4d", prodotto);
                }
            }
            System.out.println();
        }
        
        System.out.println("\nLegenda:");
        System.out.println("*n* = Quadrati perfetti");
        System.out.println("[n] = Multipli di 10");
        
        // Statistiche
        int totaleCelle = max * max;
        int quadratiPerfetti = max;
        System.out.printf("\n📊 Statistiche:%n");
        System.out.printf("Celle totali: %d%n", totaleCelle);
        System.out.printf("Quadrati perfetti: %d%n", quadratiPerfetti);
        System.out.printf("Numero più grande: %d%n", max * max);
        
        scanner.close();
    }
}
```

### Esempio 2: Analizzatore di Array
```java
/**
 * Analizza un array di numeri e produce statistiche complete
 */
import java.util.Scanner;

public class AnalizzatoreArray {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("📊 ANALIZZATORE DI ARRAY");
        System.out.println("=".repeat(40));
        
        System.out.print("Quanti numeri vuoi analizzare? ");
        int dimensione = scanner.nextInt();
        
        if (dimensione <= 0 || dimensione > 1000) {
            System.out.println("❌ Dimensione non valida!");
            return;
        }
        
        double[] numeri = new double[dimensione];
        
        // Input dei numeri
        System.out.println("\n📝 Inserisci i numeri:");
        for (int i = 0; i < numeri.length; i++) {
            System.out.printf("Numero %d: ", i + 1);
            numeri[i] = scanner.nextDouble();
        }
        
        // Analisi statistica
        System.out.println("\n" + "=".repeat(40));
        System.out.println("           📈 RISULTATI ANALISI");
        System.out.println("=".repeat(40));
        
        // 1. Visualizzazione array
        System.out.print("Array: [");
        for (int i = 0; i < numeri.length; i++) {
            System.out.printf("%.1f", numeri[i]);
            if (i < numeri.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
        
        // 2. Calcolo statistiche base
        double somma = 0;
        double minimo = numeri[0];
        double massimo = numeri[0];
        int indiceMinimo = 0;
        int indiceMassimo = 0;
        
        for (int i = 0; i < numeri.length; i++) {
            somma += numeri[i];
            
            if (numeri[i] < minimo) {
                minimo = numeri[i];
                indiceMinimo = i;
            }
            
            if (numeri[i] > massimo) {
                massimo = numeri[i];
                indiceMassimo = i;
            }
        }
        
        double media = somma / numeri.length;
        
        // 3. Calcolo deviazione standard
        double sommaScartiQuadrati = 0;
        for (double numero : numeri) {
            double scarto = numero - media;
            sommaScartiQuadrati += scarto * scarto;
        }
        double deviazioneStandard = Math.sqrt(sommaScartiQuadrati / numeri.length);
        
        // 4. Conteggio categorie
        int positivi = 0, negativi = 0, zeri = 0;
        int pari = 0, dispari = 0;
        
        for (double numero : numeri) {
            if (numero > 0) positivi++;
            else if (numero < 0) negativi++;
            else zeri++;
            
            if ((int)numero % 2 == 0) pari++;
            else dispari++;
        }
        
        // 5. Output risultati
        System.out.printf("\n📊 STATISTICHE DESCRITTIVE:%n");
        System.out.printf("├─ Somma: %.2f%n", somma);
        System.out.printf("├─ Media: %.2f%n", media);
        System.out.printf("├─ Minimo: %.2f (posizione %d)%n", minimo, indiceMinimo + 1);
        System.out.printf("├─ Massimo: %.2f (posizione %d)%n", massimo, indiceMassimo + 1);
        System.out.printf("├─ Range: %.2f%n", massimo - minimo);
        System.out.printf("└─ Deviazione Standard: %.2f%n", deviazioneStandard);
        
        System.out.printf("\n🏷️ CLASSIFICAZIONE:%n");
        System.out.printf("├─ Numeri positivi: %d (%.1f%%)%n", 
            positivi, (positivi * 100.0) / numeri.length);
        System.out.printf("├─ Numeri negativi: %d (%.1f%%)%n", 
            negativi, (negativi * 100.0) / numeri.length);
        System.out.printf("├─ Zeri: %d (%.1f%%)%n", 
            zeri, (zeri * 100.0) / numeri.length);
        System.out.printf("├─ Pari: %d (%.1f%%)%n", 
            pari, (pari * 100.0) / numeri.length);
        System.out.printf("└─ Dispari: %d (%.1f%%)%n", 
            dispari, (dispari * 100.0) / numeri.length);
        
        // 6. Pattern e tendenze
        System.out.printf("\n🔍 PATTERN:%n");
        
        // Controllo se ordinato
        boolean crescente = true, decrescente = true;
        for (int i = 1; i < numeri.length; i++) {
            if (numeri[i] < numeri[i-1]) crescente = false;
            if (numeri[i] > numeri[i-1]) decrescente = false;
        }
        
        if (crescente) {
            System.out.println("├─ Array ordinato crescente ↗️");
        } else if (decrescente) {
            System.out.println("├─ Array ordinato decrescente ↘️");
        } else {
            System.out.println("├─ Array non ordinato 🔀");
        }
        
        // Controllo elementi uguali
        boolean tuttiUguali = true;
        for (int i = 1; i < numeri.length; i++) {
            if (numeri[i] != numeri[0]) {
                tuttiUguali = false;
                break;
            }
        }
        
        if (tuttiUguali) {
            System.out.println("└─ Tutti gli elementi sono uguali 🟰");
        } else {
            System.out.println("└─ Elementi vari 🎲");
        }
        
        scanner.close();
    }
}
```

### Esempio 3: Generatore di Pattern
```java
/**
 * Genera pattern grafici usando cicli for annidati
 */
import java.util.Scanner;

public class GeneratorePattern {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("🎨 GENERATORE DI PATTERN");
        System.out.println("=".repeat(40));
        
        System.out.println("Scegli un pattern:");
        System.out.println("1. Triangolo rettangolo");
        System.out.println("2. Triangolo isoscele");
        System.out.println("3. Diamante");
        System.out.println("4. Scacchiera");
        System.out.println("5. Spirale numerica");
        System.out.println("6. Albero di Natale");
        
        System.out.print("\nScelta (1-6): ");
        int scelta = scanner.nextInt();
        
        System.out.print("Dimensione: ");
        int n = scanner.nextInt();
        
        System.out.println("\n" + "─".repeat(50));
        
        switch (scelta) {
            case 1 -> triangoloRettangolo(n);
            case 2 -> triangoloIsoscele(n);
            case 3 -> diamante(n);
            case 4 -> scacchiera(n);
            case 5 -> spiraleNumerica(n);
            case 6 -> alberoNatale(n);
            default -> System.out.println("❌ Scelta non valida!");
        }
        
        scanner.close();
    }
    
    private static void triangoloRettangolo(int n) {
        System.out.println("📐 TRIANGOLO RETTANGOLO:");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print("⭐ ");
            }
            System.out.println();
        }
    }
    
    private static void triangoloIsoscele(int n) {
        System.out.println("🔺 TRIANGOLO ISOSCELE:");
        for (int i = 1; i <= n; i++) {
            // Spazi iniziali
            for (int j = 1; j <= n - i; j++) {
                System.out.print("  ");
            }
            // Stelle
            for (int j = 1; j <= 2 * i - 1; j++) {
                System.out.print("⭐ ");
            }
            System.out.println();
        }
    }
    
    private static void diamante(int n) {
        System.out.println("💎 DIAMANTE:");
        
        // Parte superiore (triangolo)
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i; j++) {
                System.out.print("  ");
            }
            for (int j = 1; j <= 2 * i - 1; j++) {
                System.out.print("💎 ");
            }
            System.out.println();
        }
        
        // Parte inferiore (triangolo rovesciato)
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 1; j <= n - i; j++) {
                System.out.print("  ");
            }
            for (int j = 1; j <= 2 * i - 1; j++) {
                System.out.print("💎 ");
            }
            System.out.println();
        }
    }
    
    private static void scacchiera(int n) {
        System.out.println("♟️ SCACCHIERA:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i + j) % 2 == 0) {
                    System.out.print("⬜ ");
                } else {
                    System.out.print("⬛ ");
                }
            }
            System.out.println();
        }
    }
    
    private static void spiraleNumerica(int n) {
        System.out.println("🌀 SPIRALE NUMERICA:");
        int[][] matrice = new int[n][n];
        
        int valore = 1;
        int top = 0, bottom = n - 1;
        int left = 0, right = n - 1;
        
        while (top <= bottom && left <= right) {
            // Riga superiore (da sinistra a destra)
            for (int i = left; i <= right; i++) {
                matrice[top][i] = valore++;
            }
            top++;
            
            // Colonna destra (dall'alto in basso)
            for (int i = top; i <= bottom; i++) {
                matrice[i][right] = valore++;
            }
            right--;
            
            // Riga inferiore (da destra a sinistra)
            if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    matrice[bottom][i] = valore++;
                }
                bottom--;
            }
            
            // Colonna sinistra (dal basso in alto)
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    matrice[i][left] = valore++;
                }
                left++;
            }
        }
        
        // Stampa la matrice
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%3d ", matrice[i][j]);
            }
            System.out.println();
        }
    }
    
    private static void alberoNatale(int n) {
        System.out.println("🎄 ALBERO DI NATALE:");
        
        // Chioma dell'albero
        for (int sezione = 0; sezione < 3; sezione++) {
            int altezza = n / 3 + sezione;
            for (int i = 1; i <= altezza; i++) {
                // Spazi
                for (int j = 1; j <= n - i; j++) {
                    System.out.print(" ");
                }
                // Foglie
                for (int j = 1; j <= 2 * i - 1; j++) {
                    if (Math.random() < 0.1) {
                        System.out.print("🔴"); // Decorazioni occasionali
                    } else {
                        System.out.print("🌲");
                    }
                }
                System.out.println();
            }
        }
        
        // Tronco
        int larghezzaTronco = Math.max(1, n / 8);
        int altezzaTronco = Math.max(2, n / 6);
        
        for (int i = 0; i < altezzaTronco; i++) {
            for (int j = 1; j <= n - larghezzaTronco; j++) {
                System.out.print(" ");
            }
            for (int j = 0; j < larghezzaTronco * 2; j++) {
                System.out.print("🟫");
            }
            System.out.println();
        }
        
        // Base
        for (int i = 0; i < n / 4; i++) {
            System.out.print("🟤");
        }
        System.out.println(" 🎁");
    }
}
```

---

## 🔗 Cicli Annidati

### Principi Base
```java
// Cicli annidati per tabelle bidimensionali
for (int riga = 0; riga < righe; riga++) {
    for (int colonna = 0; colonna < colonne; colonna++) {
        // Elabora elemento [riga][colonna]
        System.out.printf("(%d,%d) ", riga, colonna);
    }
    System.out.println(); // Nuova riga
}
```

### Esempio: Moltiplicazione Matrici
```java
/**
 * Moltiplicazione di due matrici
 */
public static int[][] moltiplicaMatrici(int[][] A, int[][] B) {
    int righeA = A.length;
    int colonneA = A[0].length;
    int colonneB = B[0].length;
    
    int[][] risultato = new int[righeA][colonneB];
    
    // Triplo ciclo annidato per moltiplicazione
    for (int i = 0; i < righeA; i++) {
        for (int j = 0; j < colonneB; j++) {
            risultato[i][j] = 0;
            for (int k = 0; k < colonneA; k++) {
                risultato[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return risultato;
}
```

---

## 💡 Ottimizzazioni e Best Practices

### 1. Minimizzare Calcoli nel Ciclo
```java
// ❌ Inefficiente - calcolo ripetuto
for (int i = 0; i < array.length; i++) {
    if (array[i] > Math.sqrt(array.length * 1000)) {
        // ...
    }
}

// ✅ Efficiente - calcolo una volta
double soglia = Math.sqrt(array.length * 1000);
for (int i = 0; i < array.length; i++) {
    if (array[i] > soglia) {
        // ...
    }
}
```

### 2. Preferire For-Each quando Possibile
```java
int[] numeri = {1, 2, 3, 4, 5};

// ✅ For-each - più leggibile e sicuro
for (int numero : numeri) {
    System.out.println(numero * numero);
}

// vs For classico (solo se serve l'indice)
for (int i = 0; i < numeri.length; i++) {
    System.out.printf("numeri[%d] = %d%n", i, numeri[i]);
}
```

### 3. Evitare Modifiche alla Variabile di Controllo
```java
// ❌ Confusionario e error-prone
for (int i = 0; i < 10; i++) {
    if (someCondition) {
        i += 2; // Modifica la variabile di controllo!
    }
    // ...
}

// ✅ Più chiaro con while
int i = 0;
while (i < 10) {
    if (someCondition) {
        i += 3; // Incremento controllato
    } else {
        i++;
    }
    // ...
}
```

---

## ⚠️ Errori Comuni

### 1. Off-by-One Error
```java
int[] array = new int[10];

// ❌ ERRORE - ArrayIndexOutOfBoundsException
for (int i = 0; i <= array.length; i++) {
    array[i] = i; // i=10 è fuori bounds!
}

// ✅ CORRETTO
for (int i = 0; i < array.length; i++) {
    array[i] = i;
}
```

### 2. Variabile Fuori Scope
```java
// ❌ ERRORE - i non esiste fuori dal for
for (int i = 0; i < 10; i++) {
    // ...
}
System.out.println(i); // Errore di compilazione!

// ✅ CORRETTO - dichiara fuori se serve
int i;
for (i = 0; i < 10; i++) {
    // ...
}
System.out.println(i); // OK, i=10
```

### 3. Modifica di Collection durante Iterazione
```java
List<String> lista = new ArrayList<>();
lista.add("A");
lista.add("B");
lista.add("C");

// ❌ PERICOLOSO - può causare ConcurrentModificationException
for (String elemento : lista) {
    if (elemento.equals("B")) {
        lista.remove(elemento); // Modifica durante iterazione!
    }
}

// ✅ SICURO - usa Iterator o for classico inverso
for (int i = lista.size() - 1; i >= 0; i--) {
    if (lista.get(i).equals("B")) {
        lista.remove(i);
    }
}
```

---

## 🧪 Esercizi di Verifica

### Esercizio 1: Serie di Fibonacci
Genera i primi n numeri della serie di Fibonacci usando un for.

### Esercizio 2: Numeri Primi
Trova tutti i numeri primi fino a n usando il Crivello di Eratostene.

### Esercizio 3: Pattern Personalizzato
Crea un pattern che combini numeri e simboli in modo creativo.

---

## 🔗 Collegamenti

- **Precedente**: [Switch Statement](02-switch-statement.md)
- **Prossimo**: [Cicli While](04-cicli-while.md)
- **Pratica**: [Esempi Cicli](../esempi/CicliDemo.java)

---

*Il for è il motore dei cicli! Padroneggialo per controllare qualsiasi iterazione.* 🚀
