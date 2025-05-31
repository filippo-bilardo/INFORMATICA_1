/**
 * Server Multi-client con Socket
 * 
 * Questo programma implementa un server che può gestire connessioni simultanee
 * da più client utilizzando socket e thread. Il server riceve messaggi dai client
 * e li rispedisce a tutti i client connessi (broadcast).
 * 
 * Concetti applicati:
 * - Programmazione di rete con socket
 * - Multithreading per gestire connessioni parallele
 * - Sincronizzazione tra thread con mutex
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

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define PORT 8888

// Struttura per rappresentare un client connesso
typedef struct {
    socket_t socket;
    struct sockaddr_in address;
    int id;
    char name[50];
} client_t;

// Array di client connessi
client_t *clients[MAX_CLIENTS];

// Mutex per proteggere l'accesso all'array dei client
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Funzione per gestire gli errori
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Funzione per inviare un messaggio a tutti i client tranne il mittente
void send_message_to_all(char *message, int sender_id) {
    pthread_mutex_lock(&clients_mutex);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != NULL && clients[i]->id != sender_id) {
            if (send(clients[i]->socket, message, strlen(message), 0) < 0) {
                printf("Errore nell'invio del messaggio al client %d\n", clients[i]->id);
                break;
            }
        }
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

// Funzione per aggiungere un client all'array
void add_client(client_t *client) {
    pthread_mutex_lock(&clients_mutex);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == NULL) {
            clients[i] = client;
            break;
        }
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

// Funzione per rimuovere un client dall'array
void remove_client(int id) {
    pthread_mutex_lock(&clients_mutex);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != NULL && clients[i]->id == id) {
            close_socket(clients[i]->socket);
            free(clients[i]);
            clients[i] = NULL;
            break;
        }
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

// Funzione eseguita da ciascun thread per gestire un client
void *handle_client(void *arg) {
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE + 50];
    int read_size;
    client_t *client = (client_t *)arg;
    
    // Richiedi il nome del client
    if (send(client->socket, "Inserisci il tuo nome: ", 23, 0) < 0) {
        printf("Errore nell'invio della richiesta del nome\n");
        goto cleanup;
    }
    
    // Ricevi il nome del client
    read_size = recv(client->socket, buffer, BUFFER_SIZE, 0);
    if (read_size <= 0) {
        printf("Client disconnesso senza fornire un nome\n");
        goto cleanup;
    }
    
    buffer[read_size] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0'; // Rimuovi il newline se presente
    strncpy(client->name, buffer, sizeof(client->name) - 1);
    client->name[sizeof(client->name) - 1] = '\0'; // Assicura terminazione
    
    // Notifica a tutti che un nuovo client si è connesso
    sprintf(message, "%s si è unito alla chat!\n", client->name);
    printf("%s", message);
    send_message_to_all(message, client->id);
    
    // Loop principale per ricevere e inviare messaggi
    while ((read_size = recv(client->socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        
        // Controlla se il client vuole disconnettersi
        if (strcmp(buffer, "exit") == 0) {
            break;
        }
        
        // Formatta il messaggio con il nome del mittente
        sprintf(message, "%s: %s\n", client->name, buffer);
        printf("%s", message);
        
        // Invia il messaggio a tutti gli altri client
        send_message_to_all(message, client->id);
    }
    
    // Notifica a tutti che il client si è disconnesso
    sprintf(message, "%s ha lasciato la chat.\n", client->name);
    printf("%s", message);
    send_message_to_all(message, client->id);
    
cleanup:
    // Rimuovi il client e libera le risorse
    remove_client(client->id);
    
    pthread_exit(NULL);
}

int main() {
    socket_t server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread_id;
    int opt = 1;
    int client_count = 0;
    socklen_t client_addr_len = sizeof(client_addr);
    
#ifdef _WIN32
    // Inizializza Winsock
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        error("Errore nell'inizializzazione di Winsock");
    }
#endif
    
    // Crea il socket del server
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == SOCKET_ERROR_VALUE) {
        error("Errore nella creazione del socket");
    }
    
    // Imposta le opzioni del socket
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        error("Errore nell'impostazione delle opzioni del socket");
    }
    
    // Configura l'indirizzo del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Associa il socket all'indirizzo e alla porta
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Errore nel binding del socket");
    }
    
    // Metti il socket in ascolto
    if (listen(server_socket, 5) < 0) {
        error("Errore nell'ascolto del socket");
    }
    
    printf("Server avviato sulla porta %d\n", PORT);
    printf("In attesa di connessioni...\n");
    
    // Inizializza l'array dei client a NULL
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = NULL;
    }
    
    // Loop principale per accettare connessioni
    while (1) {
        // Accetta una nuova connessione
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == SOCKET_ERROR_VALUE) {
            error("Errore nell'accettazione della connessione");
            continue;
        }
        
        // Verifica se abbiamo raggiunto il limite di client
        if (client_count >= MAX_CLIENTS) {
            printf("Limite di client raggiunto. Connessione rifiutata.\n");
            close_socket(client_socket);
            continue;
        }
        
        // Crea una nuova struttura client
        client_t *client = (client_t *)malloc(sizeof(client_t));
        if (client == NULL) {
            error("Errore nell'allocazione della memoria per il client");
            close_socket(client_socket);
            continue;
        }
        
        // Inizializza la struttura client
        client->socket = client_socket;
        client->address = client_addr;
        client->id = client_count++;
        strcpy(client->name, "Anonimo"); // Nome predefinito
        
        // Aggiungi il client all'array
        add_client(client);
        
        printf("Nuova connessione accettata: %s:%d (ID: %d)\n", 
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client->id);
        
        // Crea un nuovo thread per gestire il client
        if (pthread_create(&thread_id, NULL, handle_client, (void *)client) != 0) {
            printf("Errore nella creazione del thread\n");
            remove_client(client->id);
            client_count--;
            continue;
        }
        
        // Imposta il thread come detached
        pthread_detach(thread_id);
    }
    
    // Chiudi il socket del server
    close_socket(server_socket);
    
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
 *   gcc -o server_multi_client server_multi_client.c -lpthread
 *   ./server_multi_client
 * 
 * Su Windows con MinGW:
 *   gcc -o server_multi_client server_multi_client.c -lws2_32 -lpthread
 *   server_multi_client.exe
 * 
 * Note:
 * - Il server ascolta sulla porta 8888 (modificabile cambiando la costante PORT)
 * - Supporta fino a 10 client simultanei (modificabile cambiando MAX_CLIENTS)
 * - Per testare il server, è possibile utilizzare telnet o un client TCP personalizzato
 * - Per disconnettersi, un client può inviare il messaggio "exit"
 */