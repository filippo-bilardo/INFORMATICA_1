# Protocolli TCP e UDP nella Programmazione di Rete

## Introduzione

I protocolli TCP (Transmission Control Protocol) e UDP (User Datagram Protocol) sono due dei protocolli di trasporto più utilizzati nella programmazione di rete. Questi protocolli operano al livello di trasporto del modello OSI e forniscono metodi diversi per la trasmissione dei dati attraverso una rete.

## TCP - Transmission Control Protocol

### Caratteristiche Principali

1. **Orientato alla connessione**: Prima di scambiare dati, client e server stabiliscono una connessione attraverso un processo di "handshake" a tre vie.
2. **Affidabile**: Garantisce che tutti i pacchetti arrivino a destinazione nell'ordine corretto.
3. **Controllo di flusso**: Regola la velocità di trasmissione per evitare di sovraccaricare il ricevente.
4. **Controllo della congestione**: Adatta la velocità di trasmissione in base alle condizioni della rete.
5. **Overhead maggiore**: A causa dei meccanismi di affidabilità, TCP ha un overhead maggiore rispetto a UDP.

### Quando Usare TCP

- Quando è necessaria una trasmissione affidabile dei dati.
- Per applicazioni che richiedono che tutti i dati arrivino intatti e nell'ordine corretto.
- Esempi: trasferimento di file, email, navigazione web.

### Implementazione di un Server TCP in C

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
    
    // Creazione del socket TCP
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
    
    printf("Server TCP in ascolto sulla porta %d...\n", PORT);
    
    // Accettazione di una connessione in entrata
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Lettura del messaggio dal client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Messaggio dal client: %s\n", buffer);
    
    // Invio di una risposta al client
    char *message = "Messaggio ricevuto dal server TCP";
    send(new_socket, message, strlen(message), 0);
    printf("Risposta inviata al client\n");
    
    // Chiusura del socket
    close(new_socket);
    close(server_fd);
    
    return 0;
}
```

### Implementazione di un Client TCP in C

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
    
    // Creazione del socket TCP
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
    char *message = "Messaggio dal client TCP";
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

## UDP - User Datagram Protocol

### Caratteristiche Principali

1. **Senza connessione**: Non richiede una connessione stabilita prima di inviare dati.
2. **Non affidabile**: Non garantisce la consegna dei pacchetti né l'ordine di arrivo.
3. **Nessun controllo di flusso o congestione**: Non regola la velocità di trasmissione.
4. **Overhead minore**: A causa della mancanza di meccanismi di affidabilità, UDP ha un overhead minore rispetto a TCP.
5. **Velocità maggiore**: La mancanza di controlli di affidabilità rende UDP più veloce di TCP.

### Quando Usare UDP

- Quando la velocità è più importante dell'affidabilità.
- Per applicazioni che possono tollerare la perdita occasionale di dati.
- Esempi: streaming video, giochi online, VoIP.

### Implementazione di un Server UDP in C

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
    int server_fd;
    struct sockaddr_in address, client_addr;
    int addrlen = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};
    
    // Creazione del socket UDP
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Creazione socket fallita");
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
    
    printf("Server UDP in ascolto sulla porta %d...\n", PORT);
    
    // Ricezione di un messaggio dal client
    int len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);
    buffer[len] = '\0';
    printf("Messaggio dal client: %s\n", buffer);
    
    // Invio di una risposta al client
    char *message = "Messaggio ricevuto dal server UDP";
    sendto(server_fd, message, strlen(message), 0, (struct sockaddr *)&client_addr, addrlen);
    printf("Risposta inviata al client\n");
    
    // Chiusura del socket
    close(server_fd);
    
    return 0;
}
```

### Implementazione di un Client UDP in C

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
    int addrlen = sizeof(serv_addr);
    char buffer[BUFFER_SIZE] = {0};
    
    // Creazione del socket UDP
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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
    
    // Invio di un messaggio al server
    char *message = "Messaggio dal client UDP";
    sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Messaggio inviato al server\n");
    
    // Lettura della risposta dal server
    int len = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen);
    buffer[len] = '\0';
    printf("Risposta dal server: %s\n", buffer);
    
    // Chiusura del socket
    close(sock);
    
    return 0;
}
```

## Confronto tra TCP e UDP

| Caratteristica | TCP | UDP |
|---------------|-----|-----|
| Connessione | Orientato alla connessione | Senza connessione |
| Affidabilità | Garantisce la consegna dei pacchetti | Non garantisce la consegna |
| Ordine dei pacchetti | Mantiene l'ordine dei pacchetti | Non mantiene l'ordine |
| Controllo di flusso | Sì | No |
| Controllo della congestione | Sì | No |
| Overhead | Maggiore | Minore |
| Velocità | Più lento | Più veloce |
| Uso tipico | Trasferimento file, email, web | Streaming, giochi, VoIP |

## Implementazione di Protocolli Personalizzati

Oltre a utilizzare TCP e UDP direttamente, è possibile implementare protocolli personalizzati su di essi. Ad esempio:

1. **Protocollo di richiesta-risposta**: Un semplice protocollo in cui il client invia una richiesta e il server risponde.
2. **Protocollo di streaming**: Un protocollo per lo streaming continuo di dati dal server al client.
3. **Protocollo di notifica**: Un protocollo in cui il server invia notifiche ai client quando si verificano determinati eventi.

### Esempio di Protocollo Personalizzato su TCP

```c
// Definizione del formato del messaggio
typedef struct {
    uint32_t type;        // Tipo di messaggio (richiesta, risposta, notifica, ecc.)
    uint32_t length;      // Lunghezza del payload
    char payload[1024];   // Payload del messaggio
} Message;

// Funzione per inviare un messaggio
int send_message(int socket, uint32_t type, const char *payload) {
    Message msg;
    msg.type = htonl(type);  // Conversione in network byte order
    msg.length = htonl(strlen(payload));
    strncpy(msg.payload, payload, sizeof(msg.payload));
    
    return send(socket, &msg, sizeof(msg), 0);
}

// Funzione per ricevere un messaggio
int receive_message(int socket, Message *msg) {
    int bytes_received = recv(socket, msg, sizeof(*msg), 0);
    
    if (bytes_received > 0) {
        msg->type = ntohl(msg->type);      // Conversione da network byte order
        msg->length = ntohl(msg->length);
    }
    
    return bytes_received;
}
```

## Best Practices

1. **Scelta del protocollo**: Scegliere il protocollo più adatto alle esigenze dell'applicazione.
2. **Gestione degli errori**: Implementare una robusta gestione degli errori per entrambi i protocolli.
3. **Timeout**: Implementare timeout per evitare blocchi indefiniti, specialmente con UDP.
4. **Ritrasmissione**: Per UDP, implementare meccanismi di ritrasmissione se è necessaria l'affidabilità.
5. **Dimensione dei pacchetti**: Considerare la dimensione massima dei pacchetti per evitare la frammentazione.

## Conclusione

TCP e UDP sono due protocolli fondamentali nella programmazione di rete, ciascuno con i propri punti di forza e debolezze. La scelta tra TCP e UDP dipende dalle esigenze specifiche dell'applicazione. In molti casi, le applicazioni utilizzano entrambi i protocolli per diverse funzionalità.

Nei prossimi capitoli, esploreremo tecniche avanzate per la gestione di connessioni multiple e la sicurezza nelle comunicazioni di rete.