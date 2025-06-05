# Esercizi Modulo A - Ambiente di Sviluppo

## 🎯 **Obiettivi degli Esercizi**

Questi esercizi ti permetteranno di:
- Verificare che l'installazione Java sia corretta
- Praticare la compilazione ed esecuzione di programmi
- Familiarizzare con l'ambiente di sviluppo
- Sperimentare con le basi della sintassi Java

---

## 📋 **Lista Esercizi**

### **Esercizio 1: Verifica Installazione** ⚡
**Obiettivo:** Verificare che Java sia installato e configurato correttamente

### **Esercizio 2: Hello World Personalizzato** 👋
**Obiettivo:** Creare e modificare il programma Hello World

### **Esercizio 3: Informazioni Sistema** 💻
**Obiettivo:** Visualizzare informazioni sul sistema e sulla JVM

### **Esercizio 4: Calcolatrice Base** 🧮
**Obiettivo:** Creare un programma che esegue operazioni matematiche

### **Esercizio 5: Gestione Argomenti** 📝
**Obiettivo:** Creare un programma che usa argomenti da linea di comando

---

## 💻 **Esercizio 1: Verifica Installazione**

### **Descrizione:**
Verifica che Java sia installato correttamente e che tutti gli strumenti funzionino.

### **Istruzioni:**
1. Apri terminale/prompt dei comandi
2. Esegui i seguenti comandi e prendi nota dell'output:

```bash
java -version
javac -version
echo $JAVA_HOME  # Su Linux/Mac
echo %JAVA_HOME% # Su Windows
```

### **Risultato Atteso:**
- `java -version` dovrebbe mostrare Java 8 o superiore
- `javac -version` dovrebbe mostrare la stessa versione di java
- `JAVA_HOME` dovrebbe puntare alla directory di installazione Java

### **Soluzione:**
Se i comandi non funzionano, consulta la [guida installazione](../teoria/02-installazione-jdk.md).

---

## 👋 **Esercizio 2: Hello World Personalizzato**

### **Descrizione:**
Modifica il programma Hello World per mostrare informazioni personalizzate.

### **Requisiti:**
Crea un programma `HelloPersonalizzato.java` che:
1. Stampi il tuo nome e cognome
2. Mostri la data e ora corrente
3. Visualizzi un messaggio di benvenuto personalizzato
4. Includa almeno 3 emoji nel output

### **Esempio Output:**
```
🎉 Benvenuto nel mondo Java!
👤 Nome: Mario Rossi
📅 Data: 2025-06-05
⏰ Ora: 14:30:15
🚀 Iniziamo questa avventura di programmazione!
```

### **Template di Partenza:**
```java
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class HelloPersonalizzato {
    public static void main(String[] args) {
        // Il tuo codice qui
    }
}
```

### **Suggerimenti:**
- Usa `LocalDateTime.now()` per ottenere data e ora
- Usa `DateTimeFormatter.ofPattern()` per formattare la data
- Usa `System.out.println()` per stampare ogni riga

**[📝 Vedi Soluzione](soluzioni/Esercizio02-HelloPersonalizzato.java)**

---

## 💻 **Esercizio 3: Informazioni Sistema**

### **Descrizione:**
Crea un programma che visualizza informazioni dettagliate sul sistema.

### **Requisiti:**
Crea `InfoSistema.java` che mostri:
1. Informazioni sulla JVM (versione, venditore, home)
2. Informazioni sul sistema operativo
3. Informazioni sull'utente corrente
4. Informazioni sulla memoria disponibile
5. Lista delle proprietà di sistema più interessanti

### **Proprietà da Utilizzare:**
```java
System.getProperty("java.version")
System.getProperty("java.vendor")
System.getProperty("java.home")
System.getProperty("os.name")
System.getProperty("os.version")
System.getProperty("os.arch")
System.getProperty("user.name")
System.getProperty("user.home")
System.getProperty("user.dir")
```

### **Esempio Output:**
```
=== INFORMAZIONI SISTEMA ===
JVM:
  Versione: 17.0.1
  Venditore: Eclipse Adoptium
  Home: /usr/lib/jvm/java-17-openjdk

Sistema Operativo:
  Nome: Linux
  Versione: 5.15.0
  Architettura: amd64

Utente:
  Nome: mario
  Home: /home/mario
  Directory corrente: /home/mario/java-projects

Memoria:
  Massima: 4096 MB
  Totale: 256 MB
  Libera: 200 MB
  Usata: 56 MB
```

**[📝 Vedi Soluzione](soluzioni/Esercizio03-InfoSistema.java)**

---

## 🧮 **Esercizio 4: Calcolatrice Base**

### **Descrizione:**
Crea una calcolatrice che esegue operazioni matematiche di base.

### **Requisiti:**
Crea `CalcolatriceBase.java` che:
1. Definisca due numeri come variabili
2. Esegua tutte le operazioni matematiche base (+, -, *, /, %)
3. Calcoli potenza e radice quadrata
4. Mostri i risultati formattati

### **Template di Partenza:**
```java
public class CalcolatriceBase {
    public static void main(String[] args) {
        // Definisci due numeri
        double numero1 = 25.0;
        double numero2 = 4.0;
        
        // Il tuo codice qui
    }
}
```

### **Operazioni da Implementare:**
- Addizione: `numero1 + numero2`
- Sottrazione: `numero1 - numero2`
- Moltiplicazione: `numero1 * numero2`
- Divisione: `numero1 / numero2`
- Modulo: `numero1 % numero2`
- Potenza: `Math.pow(numero1, numero2)`
- Radice quadrata: `Math.sqrt(numero1)`

### **Esempio Output:**
```
🧮 CALCOLATRICE JAVA
==================
Numero 1: 25.0
Numero 2: 4.0

OPERAZIONI:
25.0 + 4.0 = 29.0
25.0 - 4.0 = 21.0
25.0 * 4.0 = 100.0
25.0 / 4.0 = 6.25
25.0 % 4.0 = 1.0

FUNZIONI MATEMATICHE:
25.0 ^ 4.0 = 390625.0
√25.0 = 5.0
```

**[📝 Vedi Soluzione](soluzioni/Esercizio04-CalcolatriceBase.java)**

---

## 📝 **Esercizio 5: Gestione Argomenti**

### **Descrizione:**
Crea un programma che elabora argomenti da linea di comando.

### **Requisiti:**
Crea `GestoreArgomenti.java` che:
1. Controlli se sono stati forniti argomenti
2. Mostri il numero totale di argomenti
3. Visualizzi ogni argomento con il suo indice
4. Calcoli la lunghezza totale di tutti gli argomenti
5. Gestisca correttamente il caso di nessun argomento

### **Comportamenti Attesi:**

#### **Senza argomenti:**
```bash
java GestoreArgomenti
```
```
⚠️  Nessun argomento fornito!
💡 Prova con: java GestoreArgomenti arg1 arg2 arg3
```

#### **Con argomenti:**
```bash
java GestoreArgomenti Java Python JavaScript
```
```
📝 GESTIONE ARGOMENTI
=====================
Numero di argomenti: 3

LISTA ARGOMENTI:
[0] Java (lunghezza: 4)
[1] Python (lunghezza: 6)
[2] JavaScript (lunghezza: 10)

STATISTICHE:
- Lunghezza totale: 20 caratteri
- Lunghezza media: 6.67 caratteri
- Argomento più lungo: JavaScript (10 caratteri)
- Argomento più corto: Java (4 caratteri)
```

### **Suggerimenti:**
- Usa `args.length` per contare gli argomenti
- Usa un ciclo for per iterare sugli argomenti
- Usa `String.length()` per ottenere la lunghezza di una stringa
- Tieni traccia dell'argomento più lungo e più corto durante l'iterazione

**[📝 Vedi Soluzione](soluzioni/Esercizio05-GestoreArgomenti.java)**

---

## ✅ **Esercizi Bonus (Opzionali)**

### **Bonus 1: Generatore di Saluti**
Crea un programma che genera saluti in diverse lingue basati sull'ora del giorno.

### **Bonus 2: Converter Unità**
Crea un programma che converte tra diverse unità (temperatura, lunghezza, peso).

### **Bonus 3: ASCII Art Generator**
Crea un programma che stampa il tuo nome usando ASCII art.

---

## 📊 **Checklist di Completamento**

Prima di procedere al modulo successivo, assicurati di aver:

- [ ] Completato tutti e 5 gli esercizi principali
- [ ] Verificato che ogni programma compili senza errori
- [ ] Testato ogni programma con diversi input
- [ ] Compreso il funzionamento di ogni parte del codice
- [ ] Sperimentato con modifiche personali ai programmi

---

## 🚀 **Prossimi Passi**

Una volta completati questi esercizi:
1. Completa il [quiz del modulo](../quiz/quiz-modulo-a.md)
2. Procedi al [Modulo B - Problemi ed Algoritmi](../../B-Problemi_ed_algoritmi/README.md)

---

## 🔗 **Risorse Utili**

- **[Esempi del Modulo](../esempi/)** - Codice di riferimento
- **[Teoria del Modulo](../teoria/)** - Concetti teorici
- **[Troubleshooting](../teoria/02-installazione-jdk.md#troubleshooting)** - Risoluzione problemi comuni

---

*💡 **Ricorda:** L'obiettivo di questi esercizi è familiarizzare con l'ambiente Java. Non preoccuparti se non capisci tutto il codice - approfondiremo ogni concetto nei moduli successivi!*
