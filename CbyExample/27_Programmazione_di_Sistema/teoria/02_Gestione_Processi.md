# Gestione dei Processi in C

La gestione dei processi è un aspetto fondamentale della programmazione di sistema. In C, possiamo creare, controllare e terminare processi utilizzando specifiche API di sistema. Questo capitolo esplora i concetti chiave e le tecniche per lavorare con i processi in ambiente UNIX/Linux e Windows.

## Concetti Fondamentali sui Processi

Un processo è un'istanza di un programma in esecuzione. Ogni processo ha:

- Uno spazio di indirizzamento proprio
- Un identificatore di processo (PID)
- Risorse allocate dal sistema operativo
- Almeno un thread di esecuzione (thread principale)
- Variabili di ambiente e argomenti della linea di comando

## Creazione di Processi in UNIX/Linux

In ambiente UNIX/Linux, i processi vengono creati principalmente utilizzando le chiamate di sistema `fork()` ed `exec()`.

### La Chiamata di Sistema `fork()`

`fork()` crea un nuovo processo duplicando il processo chiamante:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        // Errore nella creazione del processo
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Codice eseguito dal processo figlio
        printf("Processo figlio (PID: %d)\n", getpid());
    } else {
        // Codice eseguito dal processo padre
        printf("Processo padre (PID: %d), figlio creato con PID: %d\n", getpid(), pid);
    }
    
    return 0;
}
```

### La Famiglia di Funzioni `exec()`

Le funzioni `exec()` sostituiscono l'immagine del processo corrente con un nuovo programma:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Il processo figlio esegue un altro programma
        execl("/bin/ls", "ls", "-l", NULL);
        
        // Se execl() ritorna, c'è stato un errore
        perror("execl");
        return 1;
    } else {
        printf("Processo padre ha creato un figlio con PID: %d\n", pid);
    }
    
    return 0;
}
```

## Creazione di Processi in Windows

In Windows, i processi vengono creati utilizzando la funzione `CreateProcess()`:

```c
#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Crea un nuovo processo
    if (!CreateProcess(
        "C:\\Windows\\System32\\notepad.exe", // Applicazione da eseguire
        NULL,                   // Parametri della linea di comando
        NULL,                   // Attributi di sicurezza del processo
        NULL,                   // Attributi di sicurezza del thread
        FALSE,                  // Ereditarietà degli handle
        0,                      // Flag di creazione
        NULL,                   // Ambiente
        NULL,                   // Directory corrente
        &si,                    // Informazioni di startup
        &pi)                    // Informazioni sul processo
    ) {
        printf("CreateProcess fallito (%d).\n", GetLastError());
        return 1;
    }
    
    printf("Processo creato con PID: %lu\n", pi.dwProcessId);
    
    // Chiudi gli handle quando non sono più necessari
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return 0;
}
```

## Attesa di Processi

### In UNIX/Linux

La funzione `wait()` e le sue varianti permettono a un processo padre di attendere la terminazione di un processo figlio:

```c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Processo figlio
        printf("Figlio (PID: %d) in esecuzione...\n", getpid());
        sleep(2);  // Simula un'operazione
        printf("Figlio termina\n");
        return 42;  // Codice di uscita
    } else {
        // Processo padre
        int status;
        printf("Padre (PID: %d) attende il figlio (PID: %d)...\n", getpid(), pid);
        
        // Attende la terminazione del figlio
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Figlio terminato con codice: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Figlio terminato dal segnale: %d\n", WTERMSIG(status));
        }
    }
    
    return 0;
}
```

### In Windows

In Windows, si utilizza `WaitForSingleObject()` o `WaitForMultipleObjects()`:

```c
#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    if (!CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL,
                      FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess fallito (%d).\n", GetLastError());
        return 1;
    }
    
    printf("Processo creato, in attesa della terminazione...\n");
    
    // Attende che il processo termini
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Processo terminato con codice: %lu\n", exitCode);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return 0;
}
```

## Comunicazione tra Processi (IPC)

I processi possono comunicare tra loro utilizzando vari meccanismi di IPC:

1. **Pipe**: Canali unidirezionali per la comunicazione tra processi correlati
2. **FIFO (Named Pipe)**: Simili alle pipe ma accessibili da processi non correlati
3. **Code di messaggi**: Permettono lo scambio di messaggi strutturati
4. **Memoria condivisa**: Consente a più processi di accedere alla stessa area di memoria
5. **Socket**: Permettono la comunicazione tra processi anche su macchine diverse

### Esempio di Pipe in UNIX/Linux

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    // Crea una pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {  // Processo figlio
        close(pipefd[1]);  // Chiude l'estremità di scrittura
        
        // Legge dalla pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Figlio ha ricevuto: %s\n", buffer);
        
        close(pipefd[0]);
    } else {  // Processo padre
        close(pipefd[0]);  // Chiude l'estremità di lettura
        
        // Scrive nella pipe
        const char *message = "Messaggio dal processo padre";
        write(pipefd[1], message, strlen(message) + 1);
        
        close(pipefd[1]);
    }
    
    return 0;
}
```

## Terminazione dei Processi

### In UNIX/Linux

I processi possono terminare in vari modi:

1. **Terminazione normale**: Il processo ritorna dal `main()` o chiama `exit()`
2. **Terminazione per segnale**: Il processo riceve un segnale che causa la terminazione
3. **Chiamata a `abort()`**: Genera un segnale SIGABRT

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Terminazione normale con exit()\n");
    exit(0);  // Termina il processo con codice 0
    
    // Questo codice non verrà mai eseguito
    return 1;
}
```

### In Windows

In Windows, i processi possono terminare chiamando `ExitProcess()` o `TerminateProcess()`:

```c
#include <windows.h>
#include <stdio.h>

int main() {
    printf("Terminazione con ExitProcess()\n");
    ExitProcess(0);  // Termina il processo con codice 0
    
    // Questo codice non verrà mai eseguito
    return 1;
}
```

## Best Practices nella Gestione dei Processi

1. **Gestire sempre gli errori** nelle chiamate di sistema relative ai processi
2. **Evitare processi zombie** in UNIX/Linux attendendo sempre i processi figli
3. **Chiudere gli handle** in Windows per evitare perdite di risorse
4. **Utilizzare codici di uscita significativi** per comunicare lo stato di terminazione
5. **Gestire correttamente i segnali** per una terminazione pulita
6. **Limitare il numero di processi** creati per evitare sovraccarichi del sistema

## Conclusione

La gestione dei processi è una componente essenziale della programmazione di sistema. Comprendere come creare, controllare e terminare processi è fondamentale per sviluppare applicazioni di sistema robuste ed efficienti. Nel prossimo capitolo, esploreremo la programmazione multi-thread, un'alternativa più leggera ai processi per ottenere concorrenza all'interno di un'applicazione.