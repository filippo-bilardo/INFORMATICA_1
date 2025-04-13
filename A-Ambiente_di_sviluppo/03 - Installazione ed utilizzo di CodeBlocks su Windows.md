### **3. Installazione ed utilizzo di CodeBlocks su Windows**

CodeBlocks è un ambiente di sviluppo integrato (IDE) open source e multipiattaforma progettato specificamente per la programmazione in C e C++. Questo documento guida l'utente attraverso il processo di installazione e configurazione di CodeBlocks su Windows, fino alla creazione ed esecuzione del primo programma.

---

### **Installazione di CodeBlocks**

![CodeBlocks](https://wiki.codeblocks.org/images/c/c7/Cb_splash.png)

#### **1. Download del software**

1. Visita il sito ufficiale di CodeBlocks: [https://www.codeblocks.org/](https://www.codeblocks.org/)
2. Clicca sulla sezione "Downloads" nel menu principale.
3. Nella pagina dei download, cerca la versione per Windows.
4. **Importante**: Scarica la versione che include il compilatore MinGW (es. `codeblocks-20.03mingw-setup.exe`). Questa versione contiene sia l'IDE che il compilatore GCC necessario per compilare i programmi C/C++.

#### **2. Procedura di installazione**

1. Esegui il file di installazione scaricato (es. `codeblocks-20.03mingw-setup.exe`).
2. Se appare un avviso di sicurezza di Windows, clicca su "Esegui" o "Sì" per procedere.
3. Nella schermata di benvenuto dell'installazione, clicca su "Next".
4. Leggi e accetta i termini della licenza, quindi clicca su "Next".
5. Nella schermata di selezione dei componenti, assicurati che siano selezionati:
   - CodeBlocks IDE
   - MinGW Compiler Suite
   - Tutti i plugin di base

   ![Selezione componenti](https://www.codeblocks.org/images/start-here/installer-components.png)

6. Scegli la cartella di destinazione (si consiglia di lasciare quella predefinita) e clicca su "Next".
7. Clicca su "Install" per avviare l'installazione.
8. Al termine dell'installazione, seleziona "Yes, launch CodeBlocks now" e clicca su "Finish".

#### **3. Configurazione iniziale**

Al primo avvio, CodeBlocks potrebbe chiedere di selezionare il compilatore predefinito:

1. Nella finestra di dialogo "Compiler auto-detection", seleziona "GNU GCC Compiler" dalla lista.
2. Clicca su "Set as default" e poi su "OK".

![Configurazione del compilatore](https://www.codeblocks.org/images/start-here/compiler-detection.png)

---

### **Creazione del primo progetto**

#### **1. Creare un nuovo progetto**

1. Avvia CodeBlocks.
2. Dal menu principale, seleziona "File" > "New" > "Project...".
3. Nella finestra "New from template", seleziona "Console application" e clicca su "Go".
4. Nella schermata successiva, seleziona "C" come linguaggio di programmazione e clicca su "Next".
5. Inserisci un nome per il progetto (es. "HelloWorld") e scegli una cartella dove salvarlo.
6. Clicca su "Next" e poi su "Finish" per completare la creazione del progetto.

![Creazione nuovo progetto](https://www.codeblocks.org/images/start-here/new-project.png)

#### **2. Struttura del progetto**

Dopo aver creato il progetto, CodeBlocks mostrerà la struttura del progetto nel pannello "Management" a sinistra. Il progetto contiene già un file sorgente `main.c` con un codice di esempio "Hello World".

![Struttura del progetto](https://www.codeblocks.org/images/start-here/project-structure.png)

#### **3. Il primo programma: "Hello, World!"**

Il file `main.c` generato automaticamente contiene già un programma "Hello World" di base. Il codice dovrebbe apparire così:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}
```

Questo semplice programma:
1. Include le librerie standard `stdio.h` e `stdlib.h`
2. Definisce la funzione `main()`, punto di ingresso di ogni programma C
3. Utilizza la funzione `printf()` per stampare il messaggio "Hello world!" sulla console
4. Restituisce 0 per indicare che il programma è terminato con successo

---

### **Compilazione ed esecuzione del programma**

#### **1. Compilare il programma**

1. Per compilare il programma, clicca sul pulsante "Build" (icona di un ingranaggio) nella barra degli strumenti, oppure premi F9.
2. CodeBlocks compilerà il codice sorgente e mostrerà i messaggi di compilazione nel pannello "Build log" in basso.
3. Se non ci sono errori, vedrai il messaggio "Build successful".

![Compilazione del programma](https://www.codeblocks.org/images/start-here/build-program.png)

#### **2. Eseguire il programma**

1. Per eseguire il programma compilato, clicca sul pulsante "Run" (icona di un ingranaggio con una freccia verde) nella barra degli strumenti, oppure premi Ctrl+F10.
2. Si aprirà una finestra della console che mostrerà l'output del programma: "Hello world!".
3. La console si chiuderà automaticamente dopo l'esecuzione. Per mantenerla aperta e vedere l'output, puoi modificare il codice aggiungendo una pausa:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    printf("Premi un tasto per continuare...");
    getchar(); // Attende l'input dell'utente
    return 0;
}
```

![Esecuzione del programma](https://www.codeblocks.org/images/start-here/run-program.png)

---

### **Funzionalità principali di CodeBlocks**

#### **1. Editor di codice**

- **Evidenziazione della sintassi**: Colora automaticamente le parole chiave, i commenti e le stringhe per migliorare la leggibilità.
- **Completamento automatico**: Suggerisce nomi di funzioni e variabili mentre si digita.
- **Indentazione automatica**: Mantiene il codice ben formattato.

#### **2. Debugging**

1. Per avviare il debug, clicca sul pulsante "Debug" (icona di un insetto) o premi F8.
2. Puoi impostare punti di interruzione (breakpoints) facendo clic sul margine sinistro dell'editor.
3. Durante il debug, puoi:
   - Eseguire il codice passo-passo (F7)
   - Ispezionare i valori delle variabili
   - Visualizzare lo stack delle chiamate

#### **3. Gestione dei progetti**

- **Organizzazione in workspace**: Puoi gestire più progetti contemporaneamente.
- **Configurazioni di build**: Puoi creare configurazioni diverse (Debug, Release) con opzioni di compilazione specifiche.

---

### **Consigli utili**

1. **Salvare frequentemente**: Usa Ctrl+S per salvare il file corrente o Ctrl+Shift+S per salvare tutti i file.
2. **Personalizzare l'ambiente**: Da "Settings" > "Editor", puoi personalizzare font, colori e comportamento dell'editor.
3. **Utilizzare i template**: CodeBlocks offre vari template per diversi tipi di progetti (GUI, librerie, ecc.).
4. **Esplorare i plugin**: Puoi estendere le funzionalità di CodeBlocks installando plugin aggiuntivi da "Plugins" > "Manage plugins".

---

### **Risoluzione dei problemi comuni**

1. **Errore "Compiler not found"**:
   - Verifica di aver installato la versione con MinGW incluso.
   - Ricontrolla la configurazione del compilatore in "Settings" > "Compiler".

2. **Problemi con i percorsi dei file**:
   - Evita spazi e caratteri speciali nei nomi dei file e delle cartelle.
   - Usa percorsi relativamente brevi per i progetti.

3. **Errori di compilazione**:
   - Leggi attentamente i messaggi di errore nel pannello "Build log".
   - Controlla la sintassi e verifica che tutte le librerie necessarie siano incluse.

---

### **Creazione ed esecuzione di programmi C++**

CodeBlocks è un IDE eccellente anche per lo sviluppo in C++. Ecco come creare ed eseguire un programma C++:

#### **1. Creare un nuovo progetto C++**

1. Avvia CodeBlocks.
2. Dal menu principale, seleziona "File" > "New" > "Project...".
3. Nella finestra "New from template", seleziona "Console application" e clicca su "Go".
4. Nella schermata successiva, seleziona "C++" (invece di "C") come linguaggio di programmazione e clicca su "Next".
5. Inserisci un nome per il progetto (es. "HelloCpp") e scegli una cartella dove salvarlo.
6. Clicca su "Next" e poi su "Finish" per completare la creazione del progetto.

![Creazione progetto C++](https://www.codeblocks.org/images/start-here/new-cpp-project.png)

#### **2. Struttura del progetto C++**

Dopo aver creato il progetto, CodeBlocks mostrerà la struttura del progetto nel pannello "Management" a sinistra. Il progetto contiene già un file sorgente `main.cpp` con un codice di esempio "Hello World" in C++.

#### **3. Il primo programma C++: "Hello, World!"**

Il file `main.cpp` generato automaticamente contiene già un programma "Hello World" di base in C++. Il codice dovrebbe apparire così:

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
```

Questo semplice programma:
1. Include la libreria standard `iostream` per l'input/output
2. Utilizza il namespace `std` per accedere facilmente agli oggetti standard come `cout`
3. Definisce la funzione `main()`, punto di ingresso di ogni programma C++
4. Utilizza l'oggetto `cout` e l'operatore di inserimento `<<` per stampare il messaggio "Hello world!" sulla console
5. Utilizza `endl` per inserire un carattere di nuova riga e svuotare il buffer
6. Restituisce 0 per indicare che il programma è terminato con successo

#### **4. Differenze principali tra C e C++**

Quando si lavora con C++ in CodeBlocks, è importante notare alcune differenze rispetto al C:

- **Estensione dei file**: I file C++ utilizzano estensioni `.cpp`, `.cxx` o `.cc` (il più comune è `.cpp`), mentre i file C utilizzano `.c`.
- **Librerie**: C++ utilizza librerie come `<iostream>`, `<string>`, `<vector>` invece delle librerie C come `<stdio.h>`.
- **Input/Output**: C++ utilizza gli stream (`cout`, `cin`) invece delle funzioni (`printf`, `scanf`) del C.
- **Namespace**: C++ utilizza i namespace (come `std`) per organizzare il codice e evitare conflitti di nomi.

#### **5. Compilazione ed esecuzione del programma C++**

La compilazione e l'esecuzione di un programma C++ in CodeBlocks seguono gli stessi passaggi di un programma C:

1. Per compilare, clicca sul pulsante "Build" o premi F9.
2. Per eseguire, clicca sul pulsante "Run" o premi Ctrl+F10.

Se desideri mantenere aperta la console dopo l'esecuzione, puoi modificare il codice aggiungendo una pausa:

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    cout << "Premi un tasto per continuare..." << endl;
    cin.get(); // Attende l'input dell'utente
    return 0;
}
```

#### **6. Debugging di programmi C++**

Il debugging di programmi C++ funziona esattamente come per i programmi C:

1. Imposta punti di interruzione facendo clic sul margine sinistro dell'editor.
2. Avvia il debug cliccando sul pulsante "Debug" o premendo F8.
3. Utilizza i comandi di debug per eseguire il codice passo-passo e ispezionare le variabili.

---

Con questa guida, dovresti essere in grado di installare CodeBlocks, creare i tuoi progetti in C e C++ e iniziare a programmare. CodeBlocks offre un ambiente completo e potente per lo sviluppo, adatto sia ai principianti che agli sviluppatori esperti.