# Gestione dei File e I/O di Basso Livello in C

La gestione dei file e le operazioni di I/O di basso livello sono componenti fondamentali della programmazione di sistema. In C, abbiamo accesso a diverse API che ci permettono di interagire direttamente con il filesystem e gestire le operazioni di input/output a livello di sistema operativo. Questo capitolo esplora i concetti chiave e le tecniche per lavorare con file e I/O in ambiente UNIX/Linux e Windows.

## Concetti Fondamentali sull'I/O di Basso Livello

L'I/O di basso livello in C si basa sul concetto di descrittori di file (file descriptors) in UNIX/Linux o handle di file in Windows. Questi sono identificatori numerici che rappresentano risorse aperte dal sistema operativo. Le operazioni principali includono:

- Apertura e chiusura di file
- Lettura e scrittura di dati
- Posizionamento all'interno di un file
- Controllo delle proprietà dei file
- Gestione delle directory

## File Descriptors in UNIX/Linux

In ambiente UNIX/Linux, ogni processo ha una tabella di descrittori di file. I primi tre descrittori sono riservati:

- 0: Standard Input (stdin)
- 1: Standard Output (stdout)
- 2: Standard Error (stderr)

### Apertura e Chiusura di File

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // Apre un file in modalità lettura/scrittura, lo crea se non esiste
    fd = open("esempio.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File aperto con successo, descrittore: %d\n", fd);
    
    // Chiude il file
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }
    
    printf("File chiuso con successo\n");
    return 0;
}
```

I flag più comuni per `open()` includono:

- `O_RDONLY`: Apre in sola lettura
- `O_WRONLY`: Apre in sola scrittura
- `O_RDWR`: Apre in lettura e scrittura
- `O_CREAT`: Crea il file se non esiste
- `O_TRUNC`: Tronca il file a lunghezza zero
- `O_APPEND`: Aggiunge dati alla fine del file

### Lettura e Scrittura di File

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read, bytes_written;
    const char *message = "Questo è un test di scrittura su file.\n";
    
    // Apre (o crea) un file per scrittura
    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Scrive nel file
    bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    
    printf("Scritti %zd bytes nel file\n", bytes_written);
    
    // Riposiziona il puntatore all'inizio del file
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }
    
    // Legge dal file
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    
    // Aggiunge terminatore di stringa
    buffer[bytes_read] = '\0';
    printf("Letti %zd bytes dal file: %s", bytes_read, buffer);
    
    close(fd);
    return 0;
}
```

### Posizionamento all'interno di un File

La funzione `lseek()` permette di posizionare il puntatore di lettura/scrittura all'interno di un file:

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Posiziona il puntatore alla fine del file
    off_t position = lseek(fd, 0, SEEK_END);
    if (position == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }
    
    printf("Dimensione del file: %ld bytes\n", position);
    
    // Posiziona il puntatore a 10 bytes dall'inizio
    lseek(fd, 10, SEEK_SET);
    
    // Posiziona il puntatore 5 bytes indietro dalla posizione corrente
    lseek(fd, -5, SEEK_CUR);
    
    close(fd);
    return 0;
}
```

## File Handling in Windows

In Windows, si utilizzano le funzioni della Win32 API per l'I/O di basso livello:

```c
#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile;
    DWORD bytesWritten, bytesRead;
    char buffer[100];
    const char *message = "Questo è un test di scrittura su file in Windows.\r\n";
    
    // Crea o apre un file
    hFile = CreateFile(
        "test.txt",                  // Nome del file
        GENERIC_READ | GENERIC_WRITE, // Accesso in lettura e scrittura
        0,                           // Nessuna condivisione
        NULL,                        // Attributi di sicurezza predefiniti
        CREATE_ALWAYS,               // Crea sempre, sovrascrive se esiste
        FILE_ATTRIBUTE_NORMAL,       // Attributi normali
        NULL                         // Nessun template
    );
    
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    // Scrive nel file
    if (!WriteFile(hFile, message, (DWORD)strlen(message), &bytesWritten, NULL)) {
        printf("WriteFile fallito (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    
    printf("Scritti %lu bytes nel file\n", bytesWritten);
    
    // Riposiziona il puntatore all'inizio del file
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    
    // Legge dal file
    if (!ReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        printf("ReadFile fallito (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    
    // Aggiunge terminatore di stringa
    buffer[bytesRead] = '\0';
    printf("Letti %lu bytes dal file: %s", bytesRead, buffer);
    
    CloseHandle(hFile);
    return 0;
}
```

## Operazioni su Directory

### In UNIX/Linux

```c
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    
    // Crea una directory
    if (mkdir("nuova_directory", 0755) == -1) {
        perror("mkdir");
        return 1;
    }
    
    printf("Directory creata con successo\n");
    
    // Apre una directory esistente
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    // Legge il contenuto della directory
    printf("Contenuto della directory corrente:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    closedir(dir);
    
    // Rimuove la directory creata
    if (rmdir("nuova_directory") == -1) {
        perror("rmdir");
        return 1;
    }
    
    printf("Directory rimossa con successo\n");
    return 0;
}
```

### In Windows

```c
#include <windows.h>
#include <stdio.h>

int main() {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    
    // Crea una directory
    if (!CreateDirectory("nuova_directory", NULL)) {
        printf("CreateDirectory fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Directory creata con successo\n");
    
    // Elenca i file nella directory corrente
    hFind = FindFirstFile("*.*", &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("FindFirstFile fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Contenuto della directory corrente:\n");
    do {
        printf("%s\n", findData.cFileName);
    } while (FindNextFile(hFind, &findData));
    
    FindClose(hFind);
    
    // Rimuove la directory creata
    if (!RemoveDirectory("nuova_directory")) {
        printf("RemoveDirectory fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Directory rimossa con successo\n");
    return 0;
}
```

## Informazioni sui File

### In UNIX/Linux

```c
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int main() {
    struct stat file_info;
    
    if (stat("test.txt", &file_info) == -1) {
        perror("stat");
        return 1;
    }
    
    printf("Informazioni sul file 'test.txt':\n");
    printf("Dimensione: %ld bytes\n", file_info.st_size);
    printf("Permessi: %o\n", file_info.st_mode & 0777);
    printf("Ultimo accesso: %s", ctime(&file_info.st_atime));
    printf("Ultima modifica: %s", ctime(&file_info.st_mtime));
    
    // Verifica se è un file regolare
    if (S_ISREG(file_info.st_mode)) {
        printf("È un file regolare\n");
    }
    
    // Verifica se è una directory
    if (S_ISDIR(file_info.st_mode)) {
        printf("È una directory\n");
    }
    
    return 0;
}
```

### In Windows

```c
#include <windows.h>
#include <stdio.h>
#include <time.h>

int main() {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stCreate, stAccess, stWrite;
    
    if (!GetFileAttributesEx("test.txt", GetFileExInfoStandard, &fileInfo)) {
        printf("GetFileAttributesEx fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Informazioni sul file 'test.txt':\n");
    printf("Dimensione: %llu bytes\n", 
           ((ULONGLONG)fileInfo.nFileSizeHigh << 32) | fileInfo.nFileSizeLow);
    
    // Converte i tempi di file in tempi locali
    FileTimeToLocalFileTime(&fileInfo.ftCreationTime, &ftCreate);
    FileTimeToLocalFileTime(&fileInfo.ftLastAccessTime, &ftAccess);
    FileTimeToLocalFileTime(&fileInfo.ftLastWriteTime, &ftWrite);
    
    // Converte i tempi di file in tempi di sistema
    FileTimeToSystemTime(&ftCreate, &stCreate);
    FileTimeToSystemTime(&ftAccess, &stAccess);
    FileTimeToSystemTime(&ftWrite, &stWrite);
    
    printf("Data di creazione: %02d/%02d/%d %02d:%02d:%02d\n",
           stCreate.wDay, stCreate.wMonth, stCreate.wYear,
           stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
    
    printf("Ultimo accesso: %02d/%02d/%d %02d:%02d:%02d\n",
           stAccess.wDay, stAccess.wMonth, stAccess.wYear,
           stAccess.wHour, stAccess.wMinute, stAccess.wSecond);
    
    printf("Ultima modifica: %02d/%02d/%d %02d:%02d:%02d\n",
           stWrite.wDay, stWrite.wMonth, stWrite.wYear,
           stWrite.wHour, stWrite.wMinute, stWrite.wSecond);
    
    // Verifica gli attributi
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        printf("È una directory\n");
    } else {
        printf("È un file regolare\n");
    }
    
    return 0;
}
```

## Operazioni Avanzate sui File

### Memory-Mapped Files in UNIX/Linux

```c
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd;
    struct stat sb;
    char *mapped_data;
    
    // Apre il file
    fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Ottiene la dimensione del file
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }
    
    // Mappa il file in memoria
    mapped_data = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }
    
    // Ora possiamo accedere al file come se fosse un array in memoria
    printf("Contenuto del file: %.*s\n", (int)sb.st_size, mapped_data);
    
    // Modifica il contenuto (se il file è stato aperto in scrittura)
    if (sb.st_size >= 10) {
        memcpy(mapped_data, "MODIFICATO", 10);
    }
    
    // Sincronizza le modifiche con il file su disco
    if (msync(mapped_data, sb.st_size, MS_SYNC) == -1) {
        perror("msync");
    }
    
    // Rilascia la mappatura
    if (munmap(mapped_data, sb.st_size) == -1) {
        perror("munmap");
    }
    
    close(fd);
    return 0;
}
```

### Memory-Mapped Files in Windows

```c
#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile, hMapping;
    LPVOID lpMapView;
    DWORD fileSize;
    
    // Apre il file
    hFile = CreateFile(
        "test.txt",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    // Ottiene la dimensione del file
    fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        printf("GetFileSize fallito (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    
    // Crea un oggetto di mapping del file
    hMapping = CreateFileMapping(
        hFile,
        NULL,
        PAGE_READWRITE,
        0,
        0,
        NULL
    );
    
    if (hMapping == NULL) {
        printf("CreateFileMapping fallito (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    
    // Mappa il file in memoria
    lpMapView = MapViewOfFile(
        hMapping,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        0
    );
    
    if (lpMapView == NULL) {
        printf("MapViewOfFile fallito (%lu)\n", GetLastError());
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return 1;
    }
    
    // Ora possiamo accedere al file come se fosse in memoria
    printf("Contenuto del file: %.*s\n", fileSize, (char*)lpMapView);
    
    // Modifica il contenuto
    if (fileSize >= 10) {
        memcpy(lpMapView, "MODIFICATO", 10);
    }
    
    // Rilascia le risorse
    UnmapViewOfFile(lpMapView);
    CloseHandle(hMapping);
    CloseHandle(hFile);
    
    return 0;
}
```

## File Locking

### In UNIX/Linux

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    struct flock lock;
    
    fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Imposta un lock esclusivo (scrittura) sull'intero file
    lock.l_type = F_WRLCK;    // Lock in scrittura
    lock.l_whence = SEEK_SET; // Offset relativo all'inizio del file
    lock.l_start = 0;         // Inizia dall'offset 0
    lock.l_len = 0;           // Blocca fino alla fine del file (0 = tutto)
    
    printf("Tentativo di acquisire un lock esclusivo...\n");
    
    // Tenta di acquisire il lock (bloccante)
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }
    
    printf("Lock acquisito. Premi Invio per rilasciare...\n");
    getchar();
    
    // Rilascia il lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
    } else {
        printf("Lock rilasciato\n");
    }
    
    close(fd);
    return 0;
}
```

### In Windows

```c
#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile;
    OVERLAPPED ol = {0};
    
    hFile = CreateFile(
        "test.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile fallito (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Tentativo di acquisire un lock esclusivo...\n");
    
    // Blocca l'intero file
    if (!LockFileEx(
            hFile,
            LOCKFILE_EXCLUSIVE_LOCK, // Lock esclusivo
            0,
            MAXDWORD, // Lunghezza bassa (tutto il file)
            MAXDWORD, // Lunghezza alta
            &ol)) {
        printf("LockFileEx fallito (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    
    printf("Lock acquisito. Premi Invio per rilasciare...\n");
    getchar();
    
    // Rilascia il lock
    if (!UnlockFileEx(hFile, 0, MAXDWORD, MAXDWORD, &ol)) {
        printf("UnlockFileEx fallito (%lu)\n", GetLastError());
    } else {
        printf("Lock rilasciato\n");
    }
    
    CloseHandle(hFile);
    return 0;
}
```

## Best Practices nella Gestione dei File

1. **Controllare sempre i valori di ritorno** delle funzioni di I/O per gestire gli errori
2. **Chiudere sempre i file** dopo l'uso per evitare perdite di risorse
3. **Utilizzare buffer di dimensioni appropriate** per ottimizzare le operazioni di I/O
4. **Gestire correttamente i permessi dei file** per garantire la sicurezza
5. **Utilizzare i lock sui file** quando più processi accedono allo stesso file
6. **Preferire le operazioni non bloccanti** quando appropriato
7. **Sincronizzare i dati su disco** quando necessario con funzioni come `fsync()` o `FlushFileBuffers()`
8. **Gestire correttamente i path dei file** considerando le differenze tra sistemi operativi

## Conclusione

La gestione dei file e l'I/O di basso livello sono componenti essenziali della programmazione di sistema. Comprendere come interagire direttamente con il filesystem e gestire le operazioni di I/O a livello di sistema operativo è fondamentale per sviluppare applicazioni di sistema robuste ed efficienti. Nel prossimo capitolo, esploreremo la programmazione multi-thread, un'altra componente fondamentale della programmazione di sistema moderna.