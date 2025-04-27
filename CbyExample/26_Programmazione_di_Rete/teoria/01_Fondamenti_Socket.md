# Fondamenti di Socket Programming in C

## Introduzione ai Socket

I socket rappresentano un'interfaccia di programmazione che consente la comunicazione tra processi, sia sulla stessa macchina che attraverso una rete. In C, la programmazione con i socket è implementata attraverso un insieme di API che permettono di stabilire connessioni, inviare e ricevere dati.

## Tipi di Socket

### Socket TCP (Stream Socket)

I socket TCP forniscono un flusso di dati affidabile, ordinato e con controllo degli errori:

- **Orientati alla connessione**: richiedono una connessione stabilita prima dello scambio di dati
- **Affidabili**: garantiscono la consegna dei dati senza errori e nell'ordine corretto
- **Stream-based**: i dati vengono trattati come un flusso continuo di byte

### Socket UDP (Datagram Socket)

I socket UDP forniscono un servizio di datagrammi non affidabile:

- **Senza connessione**: non richiedono una connessione stabilita
- **Non affidabili**: non garantiscono la consegna dei dati o l'ordine
- **Message-based**: i dati vengono trattati come messaggi discreti

## Creazione di un Socket

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

Parametri:
- `domain`: specifica la famiglia di protocolli (AF_INET per IPv4, AF_INET6 per IPv6)
- `type`: specifica il tipo di socket (SOCK_STREAM per TCP, SOCK_DGRAM per UDP)
- `protocol`: specifica il protocollo (solitamente 0 per il protocollo predefinito)

Esempio:

```c
// Creazione di un socket TCP IPv4
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("Errore nella creazione del socket");
    exit(EXIT_FAILURE);
}
```

## Binding di un Socket

Il binding associa un socket a un indirizzo specifico (indirizzo IP e porta):

```c
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Esempio:

```c
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Accetta connessioni da qualsiasi interfaccia
server_addr.sin_port = htons(8080); // Porta 8080

if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Errore nel binding del socket");
    exit(EXIT_FAILURE);
}
```

## Ascolto di Connessioni (solo TCP)

Per i socket TCP, è necessario mettersi in ascolto di connessioni in entrata:

```c
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

Dove `backlog` è il numero massimo di connessioni in attesa.

Esempio:

```c
if (listen(sockfd, 5) < 0) {
    perror("Errore nell'ascolto");
    exit(EXIT_FAILURE);
}
```

## Accettazione di Connessioni (solo TCP)

Per accettare una connessione in entrata:

```c
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

Esempio:

```c
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);

int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
if (client_sockfd < 0) {
    perror("Errore nell'accettazione della connessione");
    exit(EXIT_FAILURE);
}
```

## Connessione a un Server (solo TCP)

Per connettersi a un server:

```c
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Esempio:

```c
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);

// Converti l'indirizzo IP da stringa a formato binario
if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    perror("Errore nella conversione dell'indirizzo");
    exit(EXIT_FAILURE);
}

if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Errore nella connessione");
    exit(EXIT_FAILURE);
}
```

## Invio e Ricezione di Dati

### Per Socket TCP

```c
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

Esempio:

```c
char buffer[1024];
const char *message = "Hello, server!";

// Invio dati
if (send(sockfd, message, strlen(message), 0) < 0) {
    perror("Errore nell'invio dei dati");
    exit(EXIT_FAILURE);
}

// Ricezione dati
int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
if (bytes_received < 0) {
    perror("Errore nella ricezione dei dati");
    exit(EXIT_FAILURE);
}
buffer[bytes_received] = '\0'; // Termina la stringa
```

### Per Socket UDP

```c
#include <sys/socket.h>

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
```

Esempio:

```c
char buffer[1024];
const char *message = "Hello, server!";
struct sockaddr_in server_addr;

// Configurazione dell'indirizzo del server
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

// Invio dati
if (sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Errore nell'invio dei dati");
    exit(EXIT_FAILURE);
}

// Ricezione dati
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);
int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                             (struct sockaddr *)&client_addr, &client_len);
if (bytes_received < 0) {
    perror("Errore nella ricezione dei dati");
    exit(EXIT_FAILURE);
}
buffer[bytes_received] = '\0'; // Termina la stringa
```

## Chiusura di un Socket

```c
#include <unistd.h>

int close(int fd);
```

Esempio:

```c
close(sockfd);
```

## Gestione di Connessioni Multiple

Per gestire più connessioni contemporaneamente, si possono utilizzare diverse tecniche:

### Utilizzo di select()

```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

Esempio:

```c
fd_set read_fds;
int max_fd = sockfd;

FD_ZERO(&read_fds);
FD_SET(sockfd, &read_fds);

struct timeval timeout;
timeout.tv_sec = 5;
timeout.tv_usec = 0;

int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
if (activity < 0) {
    perror("Errore in select");
    exit(EXIT_FAILURE);
}

if (FD_ISSET(sockfd, &read_fds)) {
    // Nuova connessione in arrivo
    // ...
}
```

## Considerazioni sulla Portabilità

La programmazione di socket in C presenta alcune differenze tra sistemi operativi:

- **Windows**: utilizza la libreria Winsock e richiede l'inizializzazione con `WSAStartup()`
- **Unix/Linux**: utilizza le API socket standard POSIX

Per scrivere codice portabile, è consigliabile utilizzare macro condizionali:

```c
#ifdef _WIN32
    // Codice specifico per Windows
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    // Codice specifico per Unix/Linux
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif
```

## Conclusione

La programmazione di socket in C fornisce un potente strumento per lo sviluppo di applicazioni di rete. Comprendere i fondamenti dei socket è essenziale per implementare protocolli di comunicazione efficienti e affidabili. Nei prossimi capitoli, esploreremo esempi più complessi e tecniche avanzate per la programmazione di rete in C.