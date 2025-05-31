# 📐 Lezione 03: Operatori in C

> **🎯 Obiettivo**: Padroneggiare tutti i tipi di operatori del linguaggio C  
> **⏱️ Tempo stimato**: 2-3 ore  
> **📊 Difficoltà**: ⭐⭐⭐ Intermedio  
> **🔗 Prerequisiti**: [Lezione 02 - Variabili e Tipi](../02_Variabili_e_Tipi)

---

## 🌟 Cosa Imparerai

Al termine di questa lezione sarai in grado di:

- ✅ **Utilizzare correttamente** tutti i tipi di operatori in C
- ✅ **Comprendere** la precedenza e l'associatività degli operatori  
- ✅ **Scrivere espressioni complesse** con operatori multipli
- ✅ **Evitare errori comuni** nell'uso degli operatori
- ✅ **Ottimizzare il codice** con operatori bit a bit
- ✅ **Applicare** operatori in situazioni pratiche

---

## 📚 Teoria e Concetti

### 🔗 Link Rapidi
- 📖 [Teoria Completa](./teoria/) 
- 💻 [Esempi Pratici](./esempi/)
- 🏋️ [Esercizi](./esercizi/)
- 🧠 [Quiz Interattivo](./QUIZ.md)

---

### 🗂️ Contenuti Teorici

| 📝 Argomento | 🎯 Concetti Chiave | ⏱️ Tempo |
|---------------|-------------------|----------|
| **[🧮 Operatori Aritmetici](./teoria/01_Operatori_Aritmetici.md)** | `+` `-` `*` `/` `%` `++` `--` | 25 min |
| **[⚖️ Operatori Relazionali](./teoria/02_Operatori_Relazionali.md)** | `>` `<` `>=` `<=` `==` `!=` | 20 min |
| **[🔗 Operatori Logici](./teoria/03_Operatori_Logici.md)** | `&&` `\|\|` `!` Short-circuit | 30 min |
| **[📝 Operatori di Assegnazione](./teoria/04_Operatori_Assegnazione.md)** | `=` `+=` `-=` `*=` `/=` `%=` | 20 min |
| **[🔢 Operatori Bit a Bit](./teoria/05_Operatori_Bit_a_Bit.md)** | `&` `\|` `^` `~` `<<` `>>` | 35 min |
| **[🎭 Altri Operatori](./teoria/06_Altri_Operatori.md)** | `?:` `,` `sizeof` `&` `*` | 25 min |
| **[📊 Precedenza e Associatività](./teoria/07_Precedenza_Associativita.md)** | Tabelle e regole | 20 min |

**💡 Totale tempo teoria**: ~3 ore

---

## 💻 Esempi Pratici

| 🔧 Esempio | 📝 Descrizione | 🎯 Operatori |
|------------|-----------------|--------------|
| **[calcolatrice_base.c](./esempi/calcolatrice_base.c)** | Calcolatrice con operatori aritmetici | `+` `-` `*` `/` `%` |
| **[confronti_avanzati.c](./esempi/confronti_avanzati.c)** | Comparazioni e logica | `==` `!=` `&&` `\|\|` |
| **[manipolazione_bit.c](./esempi/manipolazione_bit.c)** | Operazioni bit a bit | `&` `\|` `^` `<<` `>>` |

🔨 **Compila ed esegui**: `cd esempi && make run`

---

## 🏋️ Esercizi Pratici

| 📋 Esercizio | 💪 Difficoltà | 🎯 Focus |
|--------------|---------------|----------|
| **[Esercizio 1](./esercizi/esercizio1.c)** | ⭐⭐ Facile | Operatori aritmetici base |
| **[Esercizio 2](./esercizi/esercizio2.c)** | ⭐⭐⭐ Medio | Logica e confronti |
| **[Esercizio 3](./esercizi/esercizio3.c)** | ⭐⭐⭐⭐ Difficile | Operatori bit a bit |

**✅ Soluzioni disponibili**: [./esercizi/soluzioni/](./esercizi/soluzioni/)

🔨 **Testa le soluzioni**: `cd esercizi && make test`

---

## 🧠 Autovalutazione

📝 **[Quiz Interattivo](./QUIZ.md)** - 15 domande sui operatori  
⏱️ **Tempo**: 20-25 minuti  
🎯 **Obiettivo**: Punteggio ≥ 80%

---

## 🎯 Progetti di Consolidamento

### 🔥 Progetto 1: Calcolatrice Scientifica
- **Obiettivo**: Implementare una calcolatrice con operatori avanzati
- **Concetti**: Precedenza, parentesi, funzioni matematiche
- **Difficoltà**: ⭐⭐⭐⭐

### 🔥 Progetto 2: Sistema di Permessi (Bit Flags)
- **Obiettivo**: Gestire permessi utente con operatori bit a bit
- **Concetti**: Maschere di bit, flag, operazioni logiche
- **Difficoltà**: ⭐⭐⭐⭐⭐

---

## 📊 Tabella di Precedenza Rapida

| 🥇 Livello | 🔧 Operatori | 📖 Descrizione |
|------------|--------------|-----------------|
| **1** (più alta) | `()` `[]` `->` `.` | Chiamate, accesso |
| **2** | `!` `~` `++` `--` `+` `-` `*` `&` | Unari |
| **3** | `*` `/` `%` | Moltiplicazione, divisione |
| **4** | `+` `-` | Addizione, sottrazione |
| **5** | `<<` `>>` | Shift bit a bit |
| **6** | `<` `<=` `>` `>=` | Relazionali |
| **7** | `==` `!=` | Uguaglianza |
| **8** | `&` | AND bit a bit |
| **9** | `^` | XOR bit a bit |
| **10** | `\|` | OR bit a bit |
| **11** | `&&` | AND logico |
| **12** | `\|\|` | OR logico |
| **13** | `?:` | Ternario |
| **14** | `=` `+=` `-=` ... | Assegnazione |
| **15** (più bassa) | `,` | Virgola |

---

## 💡 Tips e Best Practices

### ✅ Da Fare
- 🎯 **Usa parentesi** per chiarire la precedenza
- 🔍 **Attenzione alla divisione** tra interi
- ⚡ **Sfrutta short-circuit** evaluation
- 🛡️ **Valida gli input** prima delle operazioni

### ❌ Da Evitare
- 🚫 **Non confondere** `=` con `==`
- 🚫 **Evita** side effects complessi
- 🚫 **Non dividere** per zero
- 🚫 **Evita** operatori bit su signed int

---

## 🔗 Navigazione

**⬅️ Precedente**: [Lezione 02 - Variabili e Tipi](../02_Variabili_e_Tipi/)  
**➡️ Successiva**: [Lezione 04 - Strutture di Controllo](../04_Strutture_di_Controllo/)  
**🏠 Home**: [Indice Corso](../../README.md)

---

## 📈 Prossimi Passi

1. **📖 Studia la teoria** seguendo l'ordine consigliato
2. **💻 Sperimenta** con gli esempi forniti
3. **🏋️ Completa** tutti gli esercizi
4. **🧠 Fai il quiz** per verificare la comprensione
5. **🔥 Affronta** i progetti di consolidamento

---

> 💪 **Ricorda**: Gli operatori sono il cuore della programmazione!  
> 🎯 **Focus**: Comprendi la logica prima di memorizzare la sintassi!