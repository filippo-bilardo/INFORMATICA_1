# Esempi di Introduzione al C

Questa cartella contiene esempi pratici per illustrare i concetti fondamentali del linguaggio C.

## 🚀 Come Iniziare

### Compilazione Rapida
```bash
make all
```

### Esecuzione di Tutti gli Esempi
```bash
make run-all
```

### Esecuzione di un Esempio Specifico
```bash
make run-hello_world
make run-info_sistema
```

## 📁 Esempi Inclusi

### 🌟 hello_world.c
**Livello:** Principiante  
**Concetti:** Struttura base, printf(), commenti

Il classico "Hello, World!" con annotazioni dettagliate per spiegare ogni componente del programma.

**Cosa imparerai:**
- Struttura base di un programma C
- Uso di `#include <stdio.h>`
- Funzione `main()` e valore di ritorno
- Funzione `printf()` per l'output
- Commenti nel codice

### 🎨 info_sistema.c
**Livello:** Intermedio  
**Concetti:** Formattazione avanzata, caratteri speciali, organizzazione codice

Un esempio più elaborato che mostra informazioni sul linguaggio C con output formattato.

**Cosa imparerai:**
- Formattazione avanzata dell'output
- Uso di caratteri speciali e Unicode
- Organizzazione logica del codice
- Best practices per la leggibilità

## 🔧 Compilazione Manuale

Se preferisci compilare manualmente senza usare il Makefile:

```bash
# Compilazione base
gcc hello_world.c -o hello_world

# Compilazione con flag di debugging e warning
gcc -Wall -Wextra -std=c99 -pedantic -g hello_world.c -o hello_world

# Esecuzione
./hello_world
```

## 🏃‍♂️ Output Atteso

### hello_world
```
Hello, World!
```

### info_sistema
```
╔══════════════════════════════════╗
║       INFORMAZIONI SISTEMA       ║
╚══════════════════════════════════╝

🔧 Linguaggio: C
📅 Anno di creazione: 1972
👨‍💻 Creatore: Dennis Ritchie
🏢 Luogo: Bell Labs

✨ CARATTERISTICHE PRINCIPALI:
   • Linguaggio di basso livello
   • Gestione diretta della memoria
   • Portabilità tra sistemi
   • Efficienza nell'esecuzione
   • Base per molti altri linguaggi

🎯 UTILIZZATO PER:
   → Sistemi operativi (Unix, Linux)
   → Drivers di dispositivi
   → Software embedded
   → Compilatori e interpreti
   → Applicazioni ad alte prestazioni

🎉 Benvenuto nel mondo della programmazione C!
💪 Preparati per un viaggio affascinante!
```

## 💡 Suggerimenti per lo Studio

1. **Leggi i commenti**: Ogni file è ricco di commenti esplicativi
2. **Sperimenta**: Modifica il codice e vedi cosa succede
3. **Compila sempre**: Usa i flag di warning per imparare le best practices
4. **Confronta**: Nota le differenze tra i due esempi

## 🚨 Problemi Comuni

### Errore di Compilazione
```
error: 'printf' undeclared
```
**Soluzione:** Aggiungi `#include <stdio.h>` all'inizio del file

### Caratteri Unicode Non Visualizzati
Se vedi caratteri strani invece di emoji, il tuo terminale potrebbe non supportare Unicode. È normale e non influisce sulla logica del programma.

### Permessi di Esecuzione
Se ricevi "Permission denied":
```bash
chmod +x nome_programma
```

## 📚 Riferimenti

- [Tutorial printf()](https://en.cppreference.com/w/c/io/fprintf)
- [Standard C Library](https://en.cppreference.com/w/c/header)
- [GCC Compiler Flags](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
