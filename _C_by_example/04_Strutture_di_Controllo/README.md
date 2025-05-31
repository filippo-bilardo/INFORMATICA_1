# 🔄 Lezione 04: Strutture di Controllo

## 📋 Panoramica
Le **strutture di controllo** sono i mattoni fondamentali per costruire la logica dei programmi. Permettono di decidere quale codice eseguire, quando ripeterlo e come gestire diverse situazioni. Sono essenziali per creare programmi interattivi e intelligenti.

---

## 🎯 Obiettivi di Apprendimento
Al termine di questa lezione sarai in grado di:
- ✅ Utilizzare **istruzioni condizionali** (`if`, `else`, `switch`) per decisioni
- ✅ Implementare **cicli** (`while`, `for`, `do-while`) per ripetizioni
- ✅ Controllare il flusso con **istruzioni di salto** (`break`, `continue`)
- ✅ Progettare **algoritmi** combinando strutture diverse
- ✅ Gestire **input utente** e **validazione dati**
- ✅ Ottimizzare codice con scelte appropriate di strutture

---

## 📚 Argomenti Trattati

### 🔸 1. Istruzioni Condizionali
- **`if-else`**: Decisioni binarie e multiple
- **`switch-case`**: Scelte multiple efficienti  
- **Operatore ternario**: Condizioni concise
- **Nesting**: Condizioni annidate
- **Best practices**: Quando usare quale struttura

### 🔸 2. Cicli (Loops)
- **`while`**: Ripetizioni con condizione iniziale
- **`do-while`**: Ripetizioni con condizione finale
- **`for`**: Contatori e iterazioni strutturate
- **Cicli infiniti**: Gestione e debugging
- **Performance**: Ottimizzazione cicli

### 🔸 3. Istruzioni di Salto
- **`break`**: Uscita anticipata da cicli/switch
- **`continue`**: Salta iterazione corrente
- **`return`**: Ritorno da funzioni
- **`goto`**: Salti incondizionati (uso limitato)

### 🔸 4. Algoritmi Pratici
- **Validazione input**: Controllo dati utente
- **Menu interattivi**: Interfacce testuali
- **Elaborazione dati**: Calcoli su sequenze
- **Pattern matching**: Ricerca e filtri

---

## 🗂️ Struttura della Lezione

```
04_Strutture_di_Controllo/
├── 📖 README.md                          # Questa guida
├── 📁 esempi/                            # Codice dimostrativo
│   ├── 🔹 decisioni_semplici.c           # if-else fondamentali
│   ├── 🔹 menu_interattivo.c             # switch-case avanzato
│   ├── 🔹 cicli_numerici.c               # for e while pratici
│   └── 🔹 validazione_input.c            # Combinazione strutture
├── 📁 esercizi/                          # Sfide pratiche
│   ├── 📝 esercizio1.c                   # Sistema voti (facile)
│   ├── 📝 esercizio2.c                   # Gioco indovina numero (medio)
│   ├── 📝 esercizio3.c                   # Analizzatore testo (difficile)
│   └── 📁 soluzioni/                     # Soluzioni complete
└── 📊 QUIZ.md                            # Valutazione interattiva
```

---

## 🚀 Quick Start

### ⚡ Compilazione Rapida
```bash
# Compila tutti gli esempi
cd esempi/
make all

# Esegui demo interattiva
make demo

# Test soluzioni esercizi
cd esercizi/soluzioni/
make run-all
```

### 🧪 Test Immediato
```bash
# Prova il menu interattivo
./esempi/menu_interattivo

# Testa validazione input
./esempi/validazione_input

# Esperimento con cicli
./esempi/cicli_numerici
```

---

## 📖 Come Studiare Questa Lezione

### 📅 Piano di Studio Consigliato (3-4 ore)

#### ⏰ **Sessione 1: Fondamenti (60 min)**
1. **Leggi README.md completo** (15 min)
2. **Studia esempi base** (30 min)
   - `decisioni_semplici.c` - Logica if-else
   - `menu_interattivo.c` - Switch-case
3. **Test rapidi** (15 min)

#### ⏰ **Sessione 2: Cicli e Ripetizioni (60 min)**
1. **Analizza `cicli_numerici.c`** (20 min)
2. **Esperimenti con for/while** (25 min)
3. **Debug cicli infiniti** (15 min)

#### ⏰ **Sessione 3: Progetti Pratici (90 min)**
1. **Studio `validazione_input.c`** (30 min)
2. **Esercizio 1 - Sistema voti** (30 min)
3. **Esercizio 2 - Gioco numeri** (30 min)

#### ⏰ **Sessione 4: Avanzato (60 min)**
1. **Esercizio 3 - Analizzatore** (40 min)
2. **Quiz finale** (20 min)

### 🎯 **Percorsi Alternativi**

#### 🏃‍♂️ **Percorso Veloce (90 min)**
→ README + esempi base + esercizio 1 + quiz

#### 🎓 **Percorso Approfondito (6 ore)**
→ Studio completo + tutti esercizi + progetti extra

#### 🔧 **Percorso Pratico (3 ore)**
→ Solo esempi + esercizi + sperimentazione

---

## 💡 Concetti Chiave da Padroneggiare

### 🧠 **Logica Condizionale**
```c
// Scegli la struttura giusta per ogni situazione
if (condizione_semplice) {        // Decisioni binarie
    // azione
}

switch (valore) {                 // Scelte multiple
    case 1: /* azione 1 */ break;
    case 2: /* azione 2 */ break;
    default: /* default */
}
```

### 🔄 **Controllo Iterativo**
```c
// Tipi di cicli per diverse esigenze
for (int i = 0; i < n; i++) {     // Contatori definiti
    // iterazione
}

while (condizione) {              // Condizione variabile
    // ripetizione
}

do {                              // Almeno una esecuzione
    // azione
} while (condizione);
```

### ⚡ **Controllo Flusso**
```c
// Gestione avanzata dell'esecuzione
break;       // Esce dal ciclo/switch
continue;    // Salta alla prossima iterazione
return val;  // Ritorna da funzione
```

---

## 🛠️ Tools e Comandi Utili

### 📊 **Analisi e Debug**
```bash
# Compila con debug info
make debug

# Profiling performance
make benchmark

# Validazione codice
make validate

# Test automatici
make test
```

### 🎮 **Demo Interattive**
```bash
# Menu principale
make demo

# Test specifici
make run-decisions    # Solo decisioni
make run-loops        # Solo cicli  
make run-validation   # Solo validazione
```

---

## 🌟 Esempi in Evidenza

### 🔥 **Menu Interattivo Completo**
Sistema di navigazione con switch-case, validazione input e gestione errori.

### 🔥 **Validatore Input Avanzato**
Combinazione di cicli e condizioni per input robusto e user-friendly.

### 🔥 **Analizzatore Testo**
Progetto complesso che dimostra l'integrazione di tutte le strutture di controllo.

---

## ❓ Supporto e Risorse

### 🆘 **Se hai Difficoltà**
1. **Rivedere esempi base** - Parti dai concetti semplici
2. **Debug step-by-step** - Usa printf per tracciare l'esecuzione  
3. **Confronta con soluzioni** - Analizza approcci diversi
4. **Sperimenta variazioni** - Modifica gli esempi per capire

### 📚 **Risorse Extra**
- [C Control Structures Reference](https://en.cppreference.com/w/c/language/statements)
- [Algorithm Design Patterns](https://www.algorithmist.com/index.php/Main_Page)
- [Interactive C Debugger](https://www.onlinegdb.com/online_c_compiler)

### 🔗 **Collegamenti Rapidi**
- ⬅️ **[Lezione 03: Operatori](../03_Operatori/README.md)**
- ➡️ **[Lezione 05: Funzioni](../05_Funzioni/README.md)**
- 🏠 **[Indice Corso](../README.md)**

---

## 🎯 Sfide e Progetti Extra

### 🏆 **Sfida 1: Calcolatrice Avanzata**
Crea una calcolatrice con menu, operazioni multiple e gestione errori.

### 🏆 **Sfida 2: Gioco Battaglia Navale**
Implementa una versione semplice usando matrici e strutture di controllo.

### 🏆 **Sfida 3: Sistema Inventario**
Gestione magazzino con CRUD operations e validazione completa.

---

## ✅ Checklist Completamento

Prima di passare alla lezione successiva, assicurati di:

- [ ] **Compreso quando usare if vs switch**
- [ ] **Padroneggiato tutti i tipi di ciclo**
- [ ] **Gestito input utente correttamente**
- [ ] **Completato almeno 2 esercizi**
- [ ] **Superato il quiz con >80%**
- [ ] **Sperimentato con variazioni degli esempi**

---

**🎉 Pronto per costruire programmi intelligenti e interattivi!**

*Le strutture di controllo sono il cuore della programmazione - padroneggiale e potrai creare qualsiasi algoritmo!*

---

*Lezione 04 del corso "C by Example" - Strutture di Controllo*  
*Versione 2.0 - Aggiornata per massima interattività ed efficacia didattica*