# Modello Client-Server nella Programmazione di Rete

## Introduzione

Il modello client-server è un paradigma fondamentale nella programmazione di rete che definisce come le applicazioni comunicano tra loro attraverso una rete. Questo modello divide le responsabilità tra due tipi di entità: i client, che richiedono servizi, e i server, che forniscono tali servizi.

## Concetti Fondamentali

### Definizione di Client e Server

- **Server**: Un'applicazione che fornisce servizi o risorse ad altre applicazioni. Il server è passivo, nel senso che attende le richieste dai client.
- **Client**: Un'applicazione che richiede servizi o risorse da un server. Il client è attivo, nel senso che inizia la comunicazione.

### Caratteristiche del Modello Client-Server

1. **Separazione delle responsabilità**: Il client e il server hanno ruoli ben definiti e separati.
2. **Comunicazione bidirezionale**: Sebbene il client inizi la comunicazione, sia il client che il server possono inviare dati all'altro.
3. **Indipendenza**: Client e server possono essere sviluppati indipendentemente, purché rispettino il protocollo di comunicazione concordato.
4. **Scalabilità**: Un singolo server può servire più client contemporaneamente.

## Implementazione in C

### Struttura di Base di un Server

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Creazione del socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creazione socket fallita");
        exit(EXIT_FAILURE);
    }
    
    // Configurazione del socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Binding del socket all'indirizzo e porta specificati
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind fallito");
        exit(EXIT_FAILURE);
    }
    
    // Messa in ascolto del socket
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server in ascolto sulla porta %d...\n", PORT);
    
    // Accettazione di una connessione in entrata
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Lettura del messaggio dal client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Messaggio dal client: %s\n", buffer);
    
    // Invio di una risposta al client
    char *message = "Messaggio ricevuto dal server";
    send(new_socket, message, strlen(message), 0);
    printf("Risposta inviata al client\n");
    
    // Chiusura del socket
    close(new_socket);
    close(server_fd);
    
    return 0;
}
```

### Struttura di Base di un Client

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Creazione del socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Creazione socket fallita");
        exit(EXIT_FAILURE);
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Conversione dell'indirizzo IP da stringa a formato binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Indirizzo non valido / non supportato");
        exit(EXIT_FAILURE);
    }
    
    // Connessione al server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connessione fallita");
        exit(EXIT_FAILURE);
    }
    
    // Invio di un messaggio al server
    char *message = "Messaggio dal client";
    send(sock, message, strlen(message), 0);
    printf("Messaggio inviato al server\n");
    
    // Lettura della risposta dal server
    read(sock, buffer, BUFFER_SIZE);
    printf("Risposta dal server: %s\n", buffer);
    
    // Chiusura del socket
    close(sock);
    
    return 0;
}
```

## Modelli Avanzati di Client-Server

### Server Multi-Client

Un server può gestire più client contemporaneamente utilizzando diverse tecniche:

1. **Multi-threading**: Creazione di un nuovo thread per ogni client connesso.
2. **Multi-processing**: Creazione di un nuovo processo per ogni client connesso.
3. **I/O Multiplexing**: Utilizzo di funzioni come `select()`, `poll()` o `epoll()` per gestire più connessioni in un singolo thread.

### Server Concorrenti vs Server Iterativi

- **Server Iterativo**: Gestisce un client alla volta, completando il servizio per un client prima di passare al successivo.
- **Server Concorrente**: Gestisce più client contemporaneamente, utilizzando tecniche come multi-threading o I/O multiplexing.

## Protocolli di Comunicazione

La comunicazione tra client e server avviene secondo protocolli ben definiti. Questi protocolli possono essere standard (come HTTP, FTP, SMTP) o personalizzati per l'applicazione specifica.

Un protocollo di comunicazione definisce:

1. **Formato dei messaggi**: Come sono strutturati i dati scambiati.
2. **Sequenza di messaggi**: L'ordine in cui i messaggi vengono scambiati.
3. **Gestione degli errori**: Come vengono gestiti gli errori di comunicazione.

## Best Practices

1. **Validazione dei dati**: Validare sempre i dati ricevuti dal client per prevenire vulnerabilità di sicurezza.
2. **Gestione degli errori**: Implementare una robusta gestione degli errori per garantire la stabilità dell'applicazione.
3. **Timeout**: Implementare timeout per evitare blocchi indefiniti in caso di problemi di comunicazione.
4. **Logging**: Registrare le attività del server per facilitare il debugging e il monitoraggio.
5. **Sicurezza**: Implementare meccanismi di sicurezza come l'autenticazione e la crittografia quando necessario.

## Conclusione

Il modello client-server è un paradigma fondamentale nella programmazione di rete che permette di sviluppare applicazioni distribuite. La comprensione di questo modello e delle sue implementazioni in C è essenziale per lo sviluppo di applicazioni di rete robuste ed efficienti.

Nei prossimi capitoli, esploreremo in dettaglio i protocolli TCP e UDP e come implementarli in applicazioni client-server in C.