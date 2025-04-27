/**
 * File: 02_generic_data_structures.c
 * Descrizione: Esempio di programmazione generica in C
 * 
 * Questo esempio dimostra come implementare strutture dati generiche in C
 * utilizzando macro e void pointers per creare una lista collegata che può
 * contenere qualsiasi tipo di dato.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definizione di una struttura nodo generica
 * Utilizza void* per memorizzare qualsiasi tipo di dato
 */
typedef struct Node {
    void* data;          // Puntatore ai dati (tipo generico)
    size_t data_size;    // Dimensione dei dati in bytes
    struct Node* next;   // Puntatore al prossimo nodo
} Node;

/**
 * Definizione di una lista collegata generica
 */
typedef struct {
    Node* head;          // Puntatore al primo nodo
    size_t count;        // Numero di elementi nella lista
} GenericList;

/**
 * Inizializza una nuova lista generica
 */
void list_init(GenericList* list) {
    list->head = NULL;
    list->count = 0;
}

/**
 * Aggiunge un elemento alla lista
 * @param list Lista a cui aggiungere l'elemento
 * @param data Puntatore ai dati da aggiungere
 * @param data_size Dimensione dei dati in bytes
 * @return 1 se l'operazione ha successo, 0 altrimenti
 */
int list_add(GenericList* list, void* data, size_t data_size) {
    // Allocazione del nuovo nodo
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0; // Fallimento nell'allocazione
    }
    
    // Allocazione dello spazio per i dati
    new_node->data = malloc(data_size);
    if (new_node->data == NULL) {
        free(new_node);
        return 0; // Fallimento nell'allocazione
    }
    
    // Copia dei dati nel nodo
    memcpy(new_node->data, data, data_size);
    new_node->data_size = data_size;
    
    // Inserimento in testa alla lista
    new_node->next = list->head;
    list->head = new_node;
    list->count++;
    
    return 1; // Successo
}

/**
 * Macro per semplificare l'aggiunta di elementi alla lista
 * Questa macro deduce automaticamente la dimensione del tipo
 */
#define LIST_ADD(list, value) \
    do { \
        typeof(value) temp = value; \
        list_add(list, &temp, sizeof(temp)); \
    } while(0)

/**
 * Funzione per applicare una funzione a ogni elemento della lista
 * @param list Lista su cui operare
 * @param func Funzione da applicare a ogni elemento
 */
typedef void (*ProcessFunc)(void* data, size_t data_size);

void list_foreach(GenericList* list, ProcessFunc func) {
    Node* current = list->head;
    while (current != NULL) {
        func(current->data, current->data_size);
        current = current->next;
    }
}

/**
 * Libera la memoria occupata dalla lista
 */
void list_free(GenericList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->count = 0;
}

/**
 * Funzioni di esempio per processare diversi tipi di dati
 */
void print_int(void* data, size_t size) {
    int* value = (int*)data;
    printf("%d\n", *value);
}

void print_float(void* data, size_t size) {
    float* value = (float*)data;
    printf("%f\n", *value);
}

void print_string(void* data, size_t size) {
    char* value = (char*)data;
    printf("%s\n", value);
}

/**
 * Funzione principale che dimostra l'uso della lista generica
 */
int main() {
    GenericList int_list;
    GenericList float_list;
    GenericList string_list;
    
    // Inizializzazione delle liste
    list_init(&int_list);
    list_init(&float_list);
    list_init(&string_list);
    
    // Aggiunta di interi
    int a = 10, b = 20, c = 30;
    LIST_ADD(&int_list, a);
    LIST_ADD(&int_list, b);
    LIST_ADD(&int_list, c);
    
    // Aggiunta di float
    float x = 1.1f, y = 2.2f, z = 3.3f;
    LIST_ADD(&float_list, x);
    LIST_ADD(&float_list, y);
    LIST_ADD(&float_list, z);
    
    // Aggiunta di stringhe
    char* s1 = "Hello";
    char* s2 = "Generic";
    char* s3 = "Programming";
    
    // Per le stringhe, dobbiamo usare list_add direttamente
    // poiché vogliamo copiare il contenuto, non il puntatore
    list_add(&string_list, s1, strlen(s1) + 1);
    list_add(&string_list, s2, strlen(s2) + 1);
    list_add(&string_list, s3, strlen(s3) + 1);
    
    // Stampa dei risultati
    printf("Lista di interi:\n");
    list_foreach(&int_list, print_int);
    
    printf("\nLista di float:\n");
    list_foreach(&float_list, print_float);
    
    printf("\nLista di stringhe:\n");
    list_foreach(&string_list, print_string);
    
    // Liberazione della memoria
    list_free(&int_list);
    list_free(&float_list);
    list_free(&string_list);
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall 02_generic_data_structures.c -o 02_generic_data_structures
 * ./02_generic_data_structures
 * 
 * Nota: Questo esempio utilizza l'estensione GNU C 'typeof' che potrebbe
 * non essere disponibile in tutti i compilatori. Se si utilizza un compilatore
 * non GNU, potrebbe essere necessario modificare la macro LIST_ADD.
 */