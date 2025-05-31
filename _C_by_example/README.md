# C by Example: Corso Completo sul Linguaggio C

## Introduzione

Benvenuti a "C by Example", un corso completo progettato per esplorare gradualmente tutte le caratteristiche del linguaggio C. Questo corso è strutturato in 30 esercitazioni progressive che vi guideranno dal livello principiante fino a concetti avanzati, permettendovi di acquisire una solida padronanza del linguaggio.

Ogni esercitazione è accompagnata da materiale teorico approfondito, esempi pratici, best practice, suggerimenti utili, domande di autovalutazione e proposte di esercizi per consolidare l'apprendimento.

## Struttura del Corso

Il corso è organizzato in cartelle numerate, ciascuna contenente:
- Un file README.md con la descrizione dell'esercitazione e un indice agli argomenti teorici correlati
- Una sottocartella "teoria" con guide dettagliate sugli argomenti teorici
- Codice sorgente commentato e file di esempio

## Indice delle Esercitazioni

1. [Introduzione al linguaggio C](./01_Introduzione/)
   - Storia e caratteristiche del C
   - Ambiente di sviluppo e primo programma

2. [Variabili e Tipi di Dato](./02_Variabili_e_Tipi/)
   - Tipi di dato fondamentali
   - Dichiarazione e inizializzazione delle variabili

3. [Operatori](./03_Operatori/)
   - Operatori aritmetici, relazionali e logici
   - Precedenza degli operatori

4. [Input e Output](./04_Input_Output/)
   - Funzioni printf e scanf
   - Formattazione dell'output

5. [Strutture di Controllo](./04_Strutture_di_Controllo/)
   - If, else, switch, cicli for/while/do-while
   - Break, continue e operatore ternario

6. [Funzioni](./05_Funzioni/)
   - Dichiarazione e definizione
   - Passaggio di parametri e ricorsione

7. [Array](./06_Array/)
   - Array monodimensionali e multidimensionali
   - Operazioni sugli array

8. [Stringhe](./07_Stringhe/)
   - Manipolazione delle stringhe
   - Funzioni della libreria string.h

9. [Puntatori](./08_Puntatori/)
   - Concetti base dei puntatori
   - Aritmetica dei puntatori

10. [Strutture e Unioni](./09_Strutture_Unioni/)
    - Strutture, unioni ed enumerazioni
    - Array di strutture

11. [File I/O](./10_File_IO/)
    - Operazioni di base e avanzate sui file
    - File di testo e binari

12. [Memoria Dinamica](./11_Memoria_Dinamica/)
    - Allocazione dinamica della memoria
    - Funzioni malloc, calloc, realloc e free

13. [Preprocessore](./12_Preprocessore/)
    - Direttive #include, #define
    - Macro e compilazione condizionale

14. [Puntatori e Array](./13_Puntatori_Array/)
    - Relazione tra puntatori e array
    - Passaggio di array alle funzioni

15. [Puntatori e Stringhe](./14_Puntatori_Stringhe/)
    - Manipolazione di stringhe con puntatori
    - Funzioni avanzate

16. [Allocazione Dinamica](./15_Allocazione_Dinamica/)
    - Gestione avanzata della memoria
    - Tecniche di debugging

17. [Strutture](./16_Strutture/)
    - Strutture avanzate e nested
    - Puntatori a strutture

18. [Unioni ed Enumerazioni](./17_Unioni_Enumerazioni/)
    - Unioni: definizione e utilizzo
    - Enumerazioni: definizione e utilizzo

19. [Typedef](./18_Typedef/)
    - Creazione di alias per i tipi
    - Tipi personalizzati

20. [File: Operazioni di Base](./19_File_Base/)
    - Apertura, chiusura e manipolazione di file
    - Lettura e scrittura di testo

21. [File: Operazioni Avanzate](./20_File_Avanzati/)
    - Accesso casuale ai file
    - File binari

22. [Gestione degli Errori](./21_Gestione_Errori/)
    - Tecniche di gestione degli errori
    - Funzioni della libreria errno.h

23. [Direttive del Preprocessore](./22_Direttive_Preprocessore/)
    - Macro avanzate
    - Compilazione condizionale

24. [Librerie Standard](./23_Librerie_Standard/)
    - Panoramica delle librerie standard del C
    - Utilizzo delle funzioni più comuni

25. [Programmazione Modulare](./24_Programmazione_Modulare/)
    - Organizzazione del codice in moduli
    - Header files e file di implementazione

26. [Programmazione Avanzata](./25_Programmazione_Avanzata/)
    - Tecniche avanzate di programmazione
    - Pattern e best practices

27. [Programmazione di Rete](./26_Programmazione_di_Rete/)
    - Socket e comunicazione di rete
    - Client-server programming

28. [Programmazione di Sistema](./27_Programmazione_di_Sistema/)
    - System calls e interfacce di sistema
    - Gestione processi

29. [Multithreading](./28_Multithreading/)
    - Thread in C
    - Sincronizzazione e mutex

30. [Progetti Pratici](./29_Progetti_Pratici/)
    - Sistema di gestione biblioteca
    - Server multi-client
    - Editor di testo

31. [Tecniche Avanzate](./30_Tecniche_Avanzate/)
    - Ottimizzazione del codice
    - Profiling e debugging avanzato

## Prerequisiti

Prima di iniziare questo corso, è consigliabile avere:
- Conoscenze di base di informatica e logica di programmazione
- Familiarità con l'uso del terminale/linea di comando
- Un computer con sistema operativo Linux, macOS o Windows con WSL
- Almeno 2GB di spazio libero su disco

## Configurazione dell'Ambiente

### Compilatori Consigliati

**Linux/macOS:**
```bash
# Installazione GCC su Ubuntu/Debian
sudo apt update && sudo apt install build-essential

# Installazione GCC su macOS (tramite Xcode)
xcode-select --install
```

**Windows:**
- Installare WSL (Windows Subsystem for Linux) oppure
- Utilizzare MinGW-w64 oppure
- Installare Visual Studio Community con supporto C/C++

### Editor e IDE Consigliati

- **VS Code** con estensioni C/C++
- **CLion** (IDE completo)
- **Code::Blocks** (gratuito e multipiattaforma)
- **Dev-C++** (Windows)

## Livelli di Difficoltà

Le esercitazioni sono organizzate per livelli progressivi:

- 🟢 **Principiante** (Lezioni 1-10): Concetti base del linguaggio
- 🟡 **Intermedio** (Lezioni 11-20): Puntatori, strutture e file
- 🟠 **Avanzato** (Lezioni 21-25): Tecniche avanzate e modulari
- 🔴 **Esperto** (Lezioni 26-31): Programmazione di sistema e progetti

## Come Utilizzare Questo Corso

Si consiglia di seguire le esercitazioni nell'ordine proposto, poiché ogni lezione si basa sulle conoscenze acquisite nelle precedenti. Per ogni esercitazione:

1. Leggere il materiale teorico nella cartella "teoria"
2. Studiare gli esempi di codice forniti
3. Completare gli esercizi proposti
4. Verificare la comprensione con le domande di autovalutazione

Buono studio e buon divertimento con il linguaggio C!