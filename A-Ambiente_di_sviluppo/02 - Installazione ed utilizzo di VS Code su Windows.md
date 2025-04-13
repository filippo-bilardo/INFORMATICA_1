### **2. Installazione ed utilizzo di Visual Studio Code su Windows**

Visual Studio Code (VS Code) è un editor di codice leggero ma potente, sviluppato da Microsoft, che supporta numerosi linguaggi di programmazione, inclusi C e C++. Questo documento guida l'utente attraverso il processo di installazione e configurazione di VS Code su Windows, fino alla creazione, compilazione ed esecuzione di programmi in C e C++.

---

### **Installazione di Visual Studio Code**

#### **1. Download del software**

1. Visita il sito ufficiale di Visual Studio Code: [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Clicca sul pulsante "Download for Windows" per scaricare l'installer.
3. È possibile scegliere tra la versione User Installer (installazione solo per l'utente corrente) o System Installer (installazione per tutti gli utenti del sistema).

#### **2. Procedura di installazione**

1. Esegui il file di installazione scaricato (es. `VSCodeUserSetup-x64-1.xx.x.exe`).
2. Se appare un avviso di sicurezza di Windows, clicca su "Esegui" o "Sì" per procedere.
3. Accetta i termini della licenza e clicca su "Avanti".
4. Scegli la cartella di destinazione (si consiglia di lasciare quella predefinita) e clicca su "Avanti".
5. Nella schermata "Seleziona attività aggiuntive", si consiglia di selezionare:
   - Crea un'icona sul desktop
   - Aggiungi a PATH (disponibile dalla riga di comando)
   - Registra come editor per i tipi di file supportati
6. Clicca su "Avanti" e poi su "Installa" per avviare l'installazione.
7. Al termine dell'installazione, clicca su "Fine" per completare il processo.

---

### **Configurazione per lo sviluppo in C/C++**

#### **1. Installazione del compilatore MinGW-w64**

Per compilare programmi C/C++ su Windows, è necessario installare un compilatore. MinGW-w64 è una buona scelta per iniziare:

1. Visita il sito di MinGW-w64: [https://winlibs.com/](https://winlibs.com/) o [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/)
2. Scarica la versione più recente per Windows (preferibilmente la versione a 64 bit con POSIX threads e SEH).
3. Estrai il contenuto dell'archivio scaricato in una cartella semplice da ricordare, ad esempio `C:\mingw64`.
4. Aggiungi il percorso della cartella `bin` di MinGW alle variabili d'ambiente di Windows:
   - Cerca "Variabili d'ambiente" nel menu Start
   - Seleziona "Modifica le variabili d'ambiente di sistema"
   - Clicca su "Variabili d'ambiente"
   - Nella sezione "Variabili di sistema", seleziona "Path" e clicca su "Modifica"
   - Clicca su "Nuovo" e aggiungi il percorso alla cartella bin (es. `C:\mingw64\bin`)
   - Clicca su "OK" per chiudere tutte le finestre
5. Verifica l'installazione aprendo un prompt dei comandi (cmd) e digitando:
   ```
   gcc --version
   ```
   Se l'installazione è avvenuta correttamente, vedrai informazioni sulla versione del compilatore.

#### **2. Installazione delle estensioni necessarie in VS Code**

1. Avvia Visual Studio Code.
2. Clicca sull'icona delle estensioni nella barra laterale sinistra (o premi `Ctrl+Shift+X`).
3. Cerca e installa le seguenti estensioni:
   - **C/C++** di Microsoft: fornisce funzionalità come IntelliSense, debugging e navigazione del codice.
   - **C/C++ Extension Pack** (opzionale): include un insieme di estensioni utili per lo sviluppo C/C++.
   - **Code Runner** (opzionale): permette di eseguire frammenti di codice o file direttamente dall'editor.

---

### **Creazione e compilazione di un programma C**

#### **1. Creazione di una cartella di progetto**

1. Crea una nuova cartella sul tuo computer per il tuo progetto (es. `C:\Progetti\HelloC`).
2. Avvia VS Code e seleziona "File" > "Apri cartella..." (o premi `Ctrl+K Ctrl+O`).
3. Naviga fino alla cartella creata e selezionala.

#### **2. Creazione del file sorgente**

1. Nella barra laterale sinistra, clicca con il tasto destro sulla cartella del progetto e seleziona "Nuovo file".
2. Nomina il file `hello.c` e premi Invio.
3. Inserisci il seguente codice:

```c
#include <stdio.h>

int main() {
    // Stampa un messaggio di benvenuto
    printf("Hello, World!\n");
    
    // Termina il programma
    return 0;
}
```

4. Salva il file premendo `Ctrl+S`.

#### **3. Compilazione ed esecuzione**

**Metodo 1: Utilizzando il terminale integrato**

1. Apri il terminale integrato in VS Code premendo `Ctrl+` ` (accento grave) o selezionando "Terminal" > "New Terminal" dal menu.
2. Nel terminale, assicurati di essere nella cartella del progetto e digita:
   ```
   gcc hello.c -o hello
   ```
   Questo comando compila il file `hello.c` e crea un eseguibile chiamato `hello.exe`.
3. Per eseguire il programma, digita:
   ```
   .\hello
   ```
   Dovresti vedere il messaggio "Hello, World!" stampato nel terminale.

**Metodo 2: Utilizzando Code Runner (se installato)**

1. Apri il file `hello.c`.
2. Clicca con il tasto destro all'interno dell'editor e seleziona "Run Code" o premi `Ctrl+Alt+N`.
3. L'output del programma apparirà nel pannello "OUTPUT" nella parte inferiore dell'editor.

---

### **Creazione e compilazione di un programma C++**

#### **1. Creazione del file sorgente**

1. Nella barra laterale sinistra, clicca con il tasto destro sulla cartella del progetto e seleziona "Nuovo file".
2. Nomina il file `hello.cpp` e premi Invio.
3. Inserisci il seguente codice:

```cpp
#include <iostream>

int main() {
    // Stampa un messaggio di benvenuto
    std::cout << "Hello, World from C++!" << std::endl;
    
    // Termina il programma
    return 0;
}
```

4. Salva il file premendo `Ctrl+S`.

#### **2. Compilazione ed esecuzione**

**Metodo 1: Utilizzando il terminale integrato**

1. Apri il terminale integrato in VS Code.
2. Nel terminale, assicurati di essere nella cartella del progetto e digita:
   ```
   g++ hello.cpp -o hello_cpp
   ```
   Questo comando compila il file `hello.cpp` e crea un eseguibile chiamato `hello_cpp.exe`.
3. Per eseguire il programma, digita:
   ```
   .\hello_cpp
   ```
   Dovresti vedere il messaggio "Hello, World from C++!" stampato nel terminale.

**Metodo 2: Utilizzando Code Runner (se installato)**

1. Apri il file `hello.cpp`.
2. Clicca con il tasto destro all'interno dell'editor e seleziona "Run Code" o premi `Ctrl+Alt+N`.
3. L'output del programma apparirà nel pannello "OUTPUT".

---

### **Configurazione avanzata: tasks.json e launch.json**

Per un'esperienza di sviluppo più integrata, puoi configurare VS Code per compilare ed eseguire i tuoi programmi con semplici comandi:

#### **1. Configurazione di tasks.json per la compilazione**

1. Premi `Ctrl+Shift+P` per aprire la palette dei comandi.
2. Digita "Configure Default Build Task" e seleziona l'opzione corrispondente.
3. Seleziona "Create tasks.json file from template".
4. Seleziona "Others" per creare un task personalizzato.
5. Sostituisci il contenuto del file `tasks.json` con il seguente:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compila C",
            "type": "shell",
            "command": "gcc",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "Compila C++",
            "type": "shell",
            "command": "g++",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}"
            ],
            "group": "build",
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

6. Salva il file.

#### **2. Configurazione di launch.json per il debugging**

1. Premi `Ctrl+Shift+P` per aprire la palette dei comandi.
2. Digita "Debug: Open launch.json" e seleziona l'opzione corrispondente.
3. Seleziona "C++ (GDB/LLDB)" o "C++ (Windows)".
4. Modifica il file `launch.json` come segue:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug C/C++",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "Compila C"
        }
    ]
}
```

5. Assicurati di modificare il percorso `miDebuggerPath` in base alla posizione effettiva di GDB sul tuo sistema.
6. Salva il file.

#### **3. Utilizzo delle configurazioni**

1. Per compilare un programma C, apri il file `.c` e premi `Ctrl+Shift+B`.
2. Per compilare un programma C++, apri il file `.cpp`, premi `Ctrl+Shift+P`, digita "Run Task" e seleziona "Compila C++".
3. Per eseguire il debug di un programma, apri il file sorgente, posiziona un punto di interruzione facendo clic a sinistra del numero di riga, e premi `F5`.

---

### **Consigli e trucchi**

1. **Formattazione automatica del codice**: Premi `Shift+Alt+F` per formattare il codice secondo le convenzioni standard.

2. **Navigazione rapida**: Usa `Ctrl+P` per aprire rapidamente i file, `Ctrl+G` per andare a una riga specifica, e `F12` per andare alla definizione di una funzione o variabile.

3. **Personalizzazione dell'editor**: VS Code è altamente personalizzabile. Esplora le impostazioni (`Ctrl+,`) per adattare l'editor alle tue preferenze.

4. **Utilizzo di snippet**: VS Code include snippet predefiniti per C/C++. Digita `for` e premi Tab per inserire automaticamente un ciclo for completo.

5. **Controllo versione integrato**: VS Code ha un supporto integrato per Git. Clicca sull'icona del controllo versione nella barra laterale per gestire i tuoi repository.

---

### **Risoluzione dei problemi comuni**

1. **Il compilatore non viene trovato**: Assicurati che il percorso di MinGW sia stato aggiunto correttamente alle variabili d'ambiente di sistema.

2. **Errori di compilazione**: Verifica che tutte le librerie necessarie siano incluse e che il codice sia sintatticamente corretto.

3. **Problemi con IntelliSense**: Se IntelliSense non funziona correttamente, prova a rigenerare la cache di IntelliSense premendo `Ctrl+Shift+P` e digitando "C/C++: Reset IntelliSense Database".

4. **Errori di percorso nei file di configurazione**: Assicurati che tutti i percorsi nei file `tasks.json` e `launch.json` utilizzino la doppia barra rovesciata (`\\`) per i percorsi Windows.

---

Con questa guida, dovresti essere in grado di installare e configurare Visual Studio Code per lo sviluppo in C e C++ su Windows, e iniziare a creare, compilare ed eseguire i tuoi programmi. VS Code offre un ambiente di sviluppo potente e flessibile che può essere adattato alle tue esigenze specifiche man mano che acquisisci familiarità con esso.