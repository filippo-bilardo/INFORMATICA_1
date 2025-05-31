/**
 * Client per Server Multi-client
 * 
 * Questo programma implementa un client che si connette al server multi-client
 * e permette all'utente di inviare e ricevere messaggi in una chat condivisa.
 * 
 * Concetti applicati:
 * - Programmazione di rete con socket
 * - Multithreading per gestire invio e ricezione simultanei
 * - Gestione degli errori
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
    // Librerie Windows per socket
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET socket_t;
    #define SOCKET_ERROR_VALUE INVALID_SOCKET
    #define close_socket closesocket
#else
    // Librerie Unix/Linux per socket
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    typedef int socket_t;
    #define SOCKET_ERROR_VALUE -1
    #define close_socket close
#endif

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 8888
#define DEFAULT_SERVER "127.0.0.1"

// Variabile globale per il socket
socket_t client_socket;

// Flag per indicare se il client è in esecuzione
int running = 1;

// Funzione per gestire gli errori
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Thread per ricevere messaggi dal server
void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    int read_size;
    
    while (running && (read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        printf("%s", buffer);
    }
    
    if (read_size == 0) {
        printf("\nServer disconnesso\n");
    } else if (read_size == -1) {
        printf("\nErrore nella ricezione dei messaggi\n");
    }
    
    running = 0;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    pthread_t receive_thread;
    char buffer[BUFFER_SIZE];
    char *server_ip = DEFAULT_SERVER;
    int port = DEFAULT_PORT;
    
    // Controlla gli argomenti della riga di comando
    if (argc >= 2) {
        server_ip = argv[1];
    }
    
    if (argc >= 3) {
        port = atoi(argv[2]);
    }
    
#ifdef _WIN32
    // Inizializza Winsock
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        error("Errore nell'inizializzazione di Winsock");
    }
#endif
    
    // Crea il socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == SOCKET_ERROR_VALUE) {
        error("Errore nella creazione del socket");
    }
    
    // Configura l'indirizzo del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    // Converti l'indirizzo IP da stringa a formato binario
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        error("Indirizzo IP non valido");
    }
    
    // Connetti al server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Errore nella connessione al server");
    }
    
    printf("Connesso al server %s:%d\n", server_ip, port);
    
    // Crea un thread per ricevere messaggi
    if (pthread_create(&receive_thread, NULL, receive_messages, NULL) != 0) {
        error("Errore nella creazione del thread");
    }
    
    // Loop principale per inviare messaggi
    while (running) {
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        // Invia il messaggio al server
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            printf("Errore nell'invio del messaggio\n");
            break;
        }
        
        // Controlla se l'utente vuole uscire
        buffer[strcspn(buffer, "\n")] = '\0'; // Rimuovi il newline
        if (strcmp(buffer, "exit") == 0) {
            printf("Disconnessione dal server...\n");
            running = 0;
            break;
        }
    }
    
    // Attendi che il thread di ricezione termini
    if (pthread_join(receive_thread, NULL) != 0) {
        printf("Errore nell'attesa del thread\n");
    }
    
    // Chiudi il socket
    close_socket(client_socket);
    
#ifdef _WIN32
    // Pulisci Winsock
    WSACleanup();
#endif
    
    return 0;
}

/**
 * Compilazione ed esecuzione:
 * 
 * Su sistemi Linux/Unix:
 *   gcc -o client client.c -lpthread
 *   ./client [server_ip] [port]
 * 
 * Su Windows con MinGW:
 *   gcc -o client client.c -lws2_32 -lpthread
 *   client.exe [server_ip] [port]
 * 
 * Note:
 * - Se non specificati, l'indirizzo IP predefinito è 127.0.0.1 (localhost) e la porta è 8888
 * - Per disconnettersi, digitare "exit" e premere Invio
 * - Il client gestisce sia l'invio che la ricezione di messaggi in modo asincrono
 */