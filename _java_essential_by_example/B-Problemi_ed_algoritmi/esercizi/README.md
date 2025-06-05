# Esercizi - Modulo B: Problemi ed Algoritmi

## 📚 **Panoramica degli Esercizi**

Questa sezione contiene esercizi progressivi per consolidare i concetti di:
- Metodologia di risoluzione dei problemi
- Algoritmi fondamentali (ordinamento e ricerca)
- Analisi della complessità computazionale
- Implementazione e ottimizzazione di algoritmi

---

## 🎯 **Livello Base (⭐)**

### **Esercizio B.1 - Analisi di Problema**
**Obiettivo**: Applicare la metodologia di risoluzione dei problemi

**Problema**: 
Dato un array di numeri interi, trovare il secondo elemento più grande.

**Compiti**:
1. Analizzare il problema seguendo i 6 passi della metodologia
2. Identificare input, output e vincoli
3. Progettare l'algoritmo in pseudocodice
4. Implementare la soluzione in Java
5. Testare con diversi casi

**File**: `Esercizio01-SecondoMassimo.java`

---

### **Esercizio B.2 - Bubble Sort Modificato**
**Obiettivo**: Comprendere e modificare algoritmi di ordinamento

**Problema**: 
Implementare una versione ottimizzata del Bubble Sort che:
- Si fermi se l'array è già ordinato
- Conti il numero di scambi effettuati
- Mostri i passi dell'ordinamento

**Compiti**:
1. Implementare Bubble Sort con ottimizzazioni
2. Aggiungere contatori e output di debug
3. Testare con array già ordinati, invertiti e casuali
4. Confrontare le prestazioni

**File**: `Esercizio02-BubbleSortOttimizzato.java`

---

### **Esercizio B.3 - Ricerca con Statistiche**
**Obiettivo**: Implementare algoritmi di ricerca e raccogliere statistiche

**Problema**: 
Creare un programma che confronti ricerca lineare e binaria:
- Conta il numero di confronti effettuati
- Misura il tempo di esecuzione
- Genera grafici delle prestazioni

**Compiti**:
1. Implementare entrambi gli algoritmi con contatori
2. Testare su array di diverse dimensioni
3. Raccogliere e presentare statistiche
4. Verificare la teoria con i risultati empirici

**File**: `Esercizio03-RicercaConStatistiche.java`

---

## 🎯 **Livello Intermedio (⭐⭐)**

### **Esercizio B.4 - Algoritmi di Ordinamento Avanzati**
**Obiettivo**: Implementare algoritmi più efficienti

**Problema**: 
Implementare e confrontare Selection Sort, Insertion Sort e Quick Sort.

**Compiti**:
1. Implementare tutti e tre gli algoritmi
2. Creare un framework di test comune
3. Confrontare prestazioni su diversi tipi di dati
4. Analizzare quando usare quale algoritmo

**File**: `Esercizio04-OrdinamentoAvanzato.java`

---

### **Esercizio B.5 - Ricerca in Array 2D**
**Obiettivo**: Estendere algoritmi di ricerca a strutture più complesse

**Problema**: 
Dato un array 2D ordinato per righe e colonne, implementare una ricerca efficiente.

**Compiti**:
1. Comprendere la struttura dell'array 2D ordinato
2. Progettare un algoritmo di ricerca O(m + n)
3. Implementare e testare la soluzione
4. Confrontare con ricerca lineare naive

**File**: `Esercizio05-Ricerca2D.java`

---

### **Esercizio B.6 - Analisi Complessità Empirica**
**Obiettivo**: Verificare empiricamente la complessità teorica

**Problema**: 
Creare un tool che misuri e visualizzi la complessità di algoritmi.

**Compiti**:
1. Implementare diversi algoritmi con complessità note
2. Misurare tempi di esecuzione per input crescenti
3. Calcolare e confrontare le curve di crescita
4. Visualizzare i risultati in formato tabellare

**File**: `Esercizio06-MisurazioneComplessita.java`

---

## 🎯 **Livello Avanzato (⭐⭐⭐)**

### **Esercizio B.7 - Merge Sort Iterativo**
**Obiettivo**: Implementare versioni alternative di algoritmi classici

**Problema**: 
Implementare Merge Sort in versione iterativa (bottom-up) invece che ricorsiva.

**Compiti**:
1. Comprendere la differenza tra approccio ricorsivo e iterativo
2. Implementare Merge Sort iterativo
3. Confrontare prestazioni e uso della memoria
4. Analizzare vantaggi e svantaggi

**File**: `Esercizio07-MergeSortIterativo.java`

---

### **Esercizio B.8 - Algoritmo di Ricerca Ternaria**
**Obiettivo**: Sviluppare varianti di algoritmi esistenti

**Problema**: 
Implementare la ricerca ternaria (divide l'array in 3 parti invece di 2).

**Compiti**:
1. Progettare l'algoritmo di ricerca ternaria
2. Analizzare la complessità teorica
3. Implementare e testare
4. Confrontare con ricerca binaria

**File**: `Esercizio08-RicercaTernaria.java`

---

### **Esercizio B.9 - Ottimizzazione con Memoization**
**Obiettivo**: Applicare tecniche di ottimizzazione avanzate

**Problema**: 
Ottimizzare algoritmi ricorsivi utilizzando memoization.

**Compiti**:
1. Implementare algoritmi ricorsivi inefficienti (es. Fibonacci, Fattoriale)
2. Applicare memoization per ottimizzare
3. Confrontare prestazioni prima e dopo
4. Analizzare il trade-off tempo-spazio

**File**: `Esercizio09-Memoization.java`

---

## 🎯 **Progetti Pratici (⭐⭐⭐⭐)**

### **Progetto B.1 - Libreria di Algoritmi**
**Obiettivo**: Creare una libreria completa di algoritmi

**Descrizione**: 
Sviluppare una libreria Java che implementi i principali algoritmi di ordinamento e ricerca con:
- Interfacce standardizzate
- Documentazione completa
- Test di unità
- Benchmarking integrato

**Componenti**:
1. Interfacce per algoritmi di ordinamento e ricerca
2. Implementazioni multiple con diverse caratteristiche
3. Framework di testing e benchmarking
4. Documentazione e esempi d'uso

**File**: `progetto-libreria-algoritmi/`

---

### **Progetto B.2 - Analizzatore di Performance**
**Obiettivo**: Tool per analisi automatica delle prestazioni

**Descrizione**: 
Creare un'applicazione che analizzi automaticamente la complessità di algoritmi:
- Esecuzione automatica di test
- Generazione di grafici di prestazioni
- Stima della complessità Big O
- Report dettagliati

**Componenti**:
1. Engine per esecuzione automatica di test
2. Sistema di misurazione delle prestazioni
3. Algoritmi per stima della complessità
4. Generatore di report

**File**: `progetto-analizzatore-performance/`

---

## ✅ **Criteri di Valutazione**

### **Per ogni esercizio**:
- [ ] **Correttezza**: L'algoritmo produce risultati corretti
- [ ] **Efficienza**: Rispetta la complessità richiesta
- [ ] **Codice**: Pulito, commentato e ben strutturato
- [ ] **Test**: Include casi di test significativi
- [ ] **Documentazione**: Spiega scelte implementative

### **Livelli di competenza**:
- **Base (⭐)**: Comprende e implementa algoritmi semplici
- **Intermedio (⭐⭐)**: Analizza e confronta algoritmi diversi
- **Avanzato (⭐⭐⭐)**: Ottimizza e sviluppa varianti
- **Esperto (⭐⭐⭐⭐)**: Progetta soluzioni complete e complesse

---

## 🔗 **Risorse e Collegamenti**

- **Teoria**: [Cartella teoria/](../teoria/)
- **Esempi**: [Cartella esempi/](../esempi/)
- **Soluzioni**: [Cartella soluzioni/](./soluzioni/)
- **Materiale extra**: [Appendici](../../appendici/)

---

## 📝 **Note per lo Studio**

1. **Progressione**: Completare gli esercizi in ordine di difficoltà
2. **Pratica**: Implementare ogni algoritmo almeno una volta da zero
3. **Analisi**: Sempre verificare la complessità teorica con misurazioni empiriche
4. **Documentazione**: Mantenere note sui pattern e tecniche apprese
5. **Revisione**: Rivedere periodicamente gli algoritmi fondamentali

---

*Gli esercizi sono progettati per consolidare progressivamente le competenze algoritmiche e preparare per scenari di programmazione reali.*
