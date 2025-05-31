# Lezione 01: Introduzione al linguaggio C

## 🎯 Obiettivi di Apprendimento

Al termine di questa lezione sarai in grado di:
- [x] Conoscere la storia e l'evoluzione del linguaggio C
- [x] Comprendere le caratteristiche fondamentali del C
- [x] Configurare un ambiente di sviluppo C
- [x] Scrivere, compilare ed eseguire il tuo primo programma
- [x] Comprendere la struttura base di un programma C

## 📚 Prerequisiti

- Conoscenze di base di informatica
- Familiarità con l'uso del computer e del terminale
- Nessuna esperienza di programmazione richiesta

## ⏱️ Tempo Stimato

- **Teoria:** 45 minuti
- **Esempi:** 30 minuti
- **Esercizi:** 60 minuti
- **Totale:** ~2.5 ore

## Indice degli argomenti teorici

1. [Storia del linguaggio C](./teoria/01_Storia_del_C.md)
   - Origini e sviluppo del C
   - Standard del linguaggio (K&R, ANSI C, C99, C11, C17, C23)
   - Influenza su altri linguaggi

2. [Caratteristiche del linguaggio C](./teoria/02_Caratteristiche_del_C.md)
   - Vantaggi e limitazioni
   - Ambiti di utilizzo
   - Confronto con altri linguaggi

3. [Ambiente di sviluppo](./teoria/03_Ambiente_di_Sviluppo.md)
   - Compilatori (GCC, Clang, MSVC)
   - Editor e IDE
   - Installazione e configurazione

4. [Il primo programma](./teoria/04_Primo_Programma.md)
   - Struttura di un programma C
   - Il programma "Hello, World!"
   - Processo di compilazione ed esecuzione

## 💻 Esempi di Codice

I file di esempio si trovano nella cartella `esempi/`. Per compilarli:

```bash
cd esempi/
make all
```

## 🔧 Esercizi Pratici

### Esercizio 1.1: Hello, World!
**Difficoltà:** 🟢 Principiante

**Descrizione:** Scrivi un programma che stampi a schermo la frase "Hello, World!".

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### Esercizio 1.2: Informazioni personali
**Difficoltà:** 🟢 Principiante

**Descrizione:** Modifica il programma precedente per stampare il tuo nome, la tua età e il tuo corso di studi su righe separate.

### Esercizio 1.3: ASCII Art
**Difficoltà:** 🟡 Intermedio

**Descrizione:** Crea un programma che stampi un disegno semplice (come una faccia sorridente o una casa) utilizzando caratteri ASCII.

## ❓ Quiz di Autovalutazione

1. **Chi ha sviluppato il linguaggio C?**
   - [ ] Ken Thompson
   - [x] Dennis Ritchie
   - [ ] Brian Kernighan
   - [ ] Linus Torvalds

2. **Quale di questi NON è un compilatore C?**
   - [ ] GCC
   - [ ] Clang
   - [x] Python
   - [ ] MSVC

3. **Qual è l'estensione standard per i file sorgente C?**
   - [x] .c
   - [ ] .cpp
   - [ ] .cc
   - [ ] .h

## 🔗 Collegamenti

**Lezioni Successive:**
- [Lezione 02: Variabili e Tipi](../02_Variabili_e_Tipi/)

**Risorse Esterne:**
- [Standard C17 (ISO/IEC 9899:2018)](https://www.iso.org/standard/74528.html)
- [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language) di Brian Kernighan e Dennis Ritchie
- [Learn C Programming](https://www.programiz.com/c-programming) su Programiz

## 📝 Note Aggiuntive

- Se hai problemi con la configurazione dell'ambiente, consulta la [guida dettagliata](./teoria/03_Ambiente_di_Sviluppo.md)
- Per chi viene da altri linguaggi: il C è più "vicino al metallo" rispetto a linguaggi di alto livello
- Consiglio: inizia sempre con programmi semplici e aumenta gradualmente la complessità

## ✅ Checklist di Completamento

- [ ] Ho letto tutto il materiale teorico
- [ ] Ho configurato l'ambiente di sviluppo
- [ ] Ho compilato ed eseguito il primo programma
- [ ] Ho completato tutti gli esercizi
- [ ] Ho superato il quiz di autovalutazione

---

[⬅️ Indice del corso](../README.md) | [➡️ Prossima lezione](../02_Variabili_e_Tipi/README.md)