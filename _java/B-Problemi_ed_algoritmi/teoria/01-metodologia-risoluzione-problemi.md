# Metodologia di Risoluzione dei Problemi

## 📚 **Indice**
- [Introduzione](#introduzione)
- [Il Processo di Problem Solving](#il-processo-di-problem-solving)
- [Analisi del Problema](#analisi-del-problema)
- [Progettazione della Soluzione](#progettazione-della-soluzione)
- [Pseudocodice](#pseudocodice)
- [Diagrammi di Flusso](#diagrammi-di-flusso)
- [Validazione e Test](#validazione-e-test)

---

## 🎯 **Introduzione**

La **risoluzione sistematica dei problemi** è una competenza fondamentale per ogni programmatore. Prima di scrivere anche una sola riga di codice, è essenziale comprendere completamente il problema e progettare una soluzione efficace.

### **Perché è Importante?**
- ✅ **Evita errori** nella fase di implementazione
- ✅ **Riduce i tempi** di sviluppo
- ✅ **Migliora la qualità** del codice finale
- ✅ **Facilita la manutenzione** e le modifiche future

---

## 🔄 **Il Processo di Problem Solving**

### **1. Comprensione del Problema**
```
📝 DOMANDE CHIAVE:
- Cosa deve fare esattamente il programma?
- Quali sono gli input richiesti?
- Quali sono gli output attesi?
- Ci sono vincoli o limitazioni?
- Esistono casi particolari da considerare?
```

### **2. Analisi e Scomposizione**
```
🧩 STRATEGIE:
- Divide et Impera: scomponi in sottoproblemi
- Identifica pattern ricorrenti
- Cerca analogie con problemi noti
- Definisci chiaramente i dati in input/output
```

### **3. Progettazione della Soluzione**
```
🎨 FASI:
1. Algoritmo generale (alto livello)
2. Raffinamento progressivo
3. Pseudocodice dettagliato
4. Verifica logica
```

### **4. Implementazione**
```
💻 BEST PRACTICES:
- Scrivi codice leggibile
- Documenta le scelte implementative
- Testa frequentemente durante lo sviluppo
- Usa nomi significativi per variabili
```

### **5. Test e Validazione**
```
🧪 APPROCCI:
- Test con casi normali
- Test con casi limite
- Test con input non validi
- Verifica delle prestazioni
```

---

## 🔍 **Analisi del Problema**

### **Esempio Pratico: Calcolo dell'Area di un Triangolo**

#### **📋 Specifica del Problema:**
*"Scrivere un programma che calcoli l'area di un triangolo date le lunghezze dei tre lati."*

#### **🤔 Domande di Analisi:**
1. **Input**: Tre numeri rappresentanti le lunghezze dei lati
2. **Output**: Un numero rappresentante l'area
3. **Vincoli**: I lati devono formare un triangolo valido
4. **Formula**: Useremo la formula di Erone

#### **⚠️ Casi Speciali:**
- Triangolo degenerato (area = 0)
- Valori negativi o nulli
- Triangolo impossibile (violazione disuguaglianza triangolare)

---

## 🎨 **Progettazione della Soluzione**

### **Algoritmo Alto Livello:**
```
1. LEGGI i tre lati del triangolo
2. VERIFICA che formino un triangolo valido
3. CALCOLA l'area usando la formula di Erone
4. MOSTRA il risultato
```

### **Raffinamento Dettagliato:**
```
1. INPUT:
   - Leggi lato1, lato2, lato3
   - Verifica che siano > 0

2. VALIDAZIONE:
   - Verifica: lato1 + lato2 > lato3
   - Verifica: lato1 + lato3 > lato2  
   - Verifica: lato2 + lato3 > lato1

3. CALCOLO:
   - semiperimetro = (lato1 + lato2 + lato3) / 2
   - area = √(s × (s-lato1) × (s-lato2) × (s-lato3))

4. OUTPUT:
   - Mostra l'area calcolata
```

---

## 📝 **Pseudocodice**

### **Cos'è il Pseudocodice?**
Il **pseudocodice** è una rappresentazione informale di un algoritmo che usa:
- Linguaggio naturale strutturato
- Costrutti logici chiari
- Indentazione per mostrare la struttura

### **Convenzioni Standard:**
```
INIZIO
    istruzione1
    istruzione2
    
    SE condizione ALLORA
        istruzione_se_vera
    ALTRIMENTI
        istruzione_se_falsa
    FINE_SE
    
    MENTRE condizione FAI
        istruzioni_ripetute
    FINE_MENTRE
    
    PER i DA 1 A n FAI
        istruzioni_ripetute
    FINE_PER
FINE
```

### **Esempio Completo - Area Triangolo:**
```
INIZIO CalcolaAreaTriangolo
    
    // Input dei dati
    SCRIVI "Inserisci il primo lato: "
    LEGGI lato1
    SCRIVI "Inserisci il secondo lato: "
    LEGGI lato2  
    SCRIVI "Inserisci il terzo lato: "
    LEGGI lato3
    
    // Validazione input
    SE (lato1 <= 0 O lato2 <= 0 O lato3 <= 0) ALLORA
        SCRIVI "Errore: i lati devono essere positivi"
        TERMINA
    FINE_SE
    
    // Verifica triangolo valido
    SE (lato1 + lato2 <= lato3 O 
        lato1 + lato3 <= lato2 O 
        lato2 + lato3 <= lato1) ALLORA
        SCRIVI "Errore: i lati non formano un triangolo valido"
        TERMINA
    FINE_SE
    
    // Calcolo area (Formula di Erone)
    semiperimetro ← (lato1 + lato2 + lato3) / 2
    area ← RADICE_QUADRATA(semiperimetro × (semiperimetro - lato1) × 
                           (semiperimetro - lato2) × (semiperimetro - lato3))
    
    // Output risultato
    SCRIVI "L'area del triangolo è: ", area
    
FINE CalcolaAreaTriangolo
```

---

## 📊 **Diagrammi di Flusso**

### **Simboli Standard:**
```
🟢 OVALE     → Inizio/Fine
🔷 ROMBO     → Decisione (Se/Altrimenti)
📦 RETTANGOLO → Processo/Istruzione
📄 PARALLELOGRAMMA → Input/Output
🔗 FRECCE    → Flusso di controllo
```

### **Regole di Buona Progettazione:**
1. **Un solo punto di inizio** e **un solo punto di fine**
2. **Flusso chiaro** dall'alto verso il basso
3. **Decisioni binarie** (Sì/No, Vero/Falso)
4. **Nessun flusso che si incrocia**
5. **Etichette descrittive** per ogni blocco

---

## 🧪 **Validazione e Test**

### **Tipi di Test:**

#### **1. Test Funzionali**
```
✅ Caso Standard:
   Input: lati = 3, 4, 5
   Output atteso: area = 6.0

✅ Caso Limite:
   Input: lati = 1, 1, 1 (triangolo equilatero)
   Output atteso: area ≈ 0.433

❌ Caso Errore:
   Input: lati = 1, 2, 5 (triangolo impossibile)
   Output atteso: messaggio di errore
```

#### **2. Test di Robustezza**
```
❌ Input Negativi:
   Input: lati = -1, 3, 4
   Comportamento atteso: gestione errore

❌ Input Non Numerici:
   Input: lati = "abc", 3, 4  
   Comportamento atteso: gestione errore

❌ Input Nulli:
   Input: lati = 0, 3, 4
   Comportamento atteso: gestione errore
```

### **Strategia di Test:**
1. **Test Black Box**: verifica input/output senza conoscere l'implementazione
2. **Test White Box**: verifica tutti i percorsi del codice
3. **Test di Regressione**: verifica che le modifiche non rompano funzionalità esistenti

---

## 📈 **Miglioramento Iterativo**

### **Ciclo di Raffinamento:**
```
1. ANALIZZA i risultati dei test
2. IDENTIFICA punti di miglioramento
3. RIPROGETTA parti problematiche  
4. REIMPLEMENTA le modifiche
5. TESTA nuovamente
6. RIPETI fino a soddisfazione completa
```

### **Metriche di Qualità:**
- ✅ **Correttezza**: produce risultati giusti
- ✅ **Completezza**: gestisce tutti i casi
- ✅ **Robustezza**: gestisce input non validi
- ✅ **Efficienza**: tempo e memoria ragionevoli
- ✅ **Leggibilità**: codice comprensibile
- ✅ **Manutenibilità**: facilmente modificabile

---

## 🎯 **Riepilogo Best Practices**

### **Prima di Programmare:**
1. **Comprendi** completamente il problema
2. **Identifica** tutti i casi d'uso
3. **Progetta** l'algoritmo su carta
4. **Valida** la logica prima di implementare

### **Durante la Programmazione:**
1. **Implementa** un pezzo alla volta
2. **Testa** frequentemente
3. **Documenta** le scelte implementative
4. **Usa nomi** significativi per variabili e metodi

### **Dopo la Programmazione:**
1. **Testa** tutti i casi limite
2. **Verifica** le prestazioni
3. **Documenta** l'utilizzo
4. **Revisiona** il codice per miglioramenti

---

## 🔗 **Collegamenti**

- **[⬅️ Torna al Modulo B](../README.md)**
- **[➡️ Algoritmi Fondamentali](02-algoritmi-fondamentali.md)**
- **[📝 Esempi Pratici](../esempi/)**
- **[✏️ Esercizi](../esercizi/)**

---

*Ricorda: Un buon programmatore spende più tempo a pensare che a scrivere codice!*
