/**
 * File: 05_ffi_python_integration.c
 * Descrizione: Esempio di interoperabilità tra C e Python usando FFI
 * 
 * Questo esempio dimostra come creare una libreria condivisa in C che può essere
 * chiamata da Python utilizzando il modulo ctypes, illustrando i concetti di
 * Foreign Function Interface (FFI) e marshalling dei dati.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funzione che calcola la somma di un array di interi
 * Questa funzione sarà esposta a Python
 * 
 * @param arr Puntatore all'array di interi
 * @param size Dimensione dell'array
 * @return La somma degli elementi dell'array
 */
int sum_array(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

/**
 * Funzione che calcola la media di un array di double
 * Questa funzione sarà esposta a Python
 * 
 * @param arr Puntatore all'array di double
 * @param size Dimensione dell'array
 * @return La media degli elementi dell'array
 */
double average_array(double* arr, int size) {
    if (size <= 0) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

/**
 * Struttura che sarà condivisa tra C e Python
 */
typedef struct {
    int id;
    char name[50];
    double value;
} SharedStruct;

/**
 * Funzione che modifica una struttura
 * Questa funzione sarà esposta a Python
 * 
 * @param data Puntatore alla struttura da modificare
 * @param new_value Nuovo valore da assegnare
 */
void modify_struct(SharedStruct* data, double new_value) {
    data->value = new_value;
    strcat(data->name, " (modificato)");
}

/**
 * Funzione che alloca e restituisce una nuova struttura
 * Questa funzione sarà esposta a Python
 * 
 * @param id ID da assegnare alla struttura
 * @param name Nome da assegnare alla struttura
 * @param value Valore da assegnare alla struttura
 * @return Puntatore alla nuova struttura allocata
 */
SharedStruct* create_struct(int id, const char* name, double value) {
    SharedStruct* data = (SharedStruct*)malloc(sizeof(SharedStruct));
    if (data == NULL) return NULL;
    
    data->id = id;
    strncpy(data->name, name, sizeof(data->name) - 1);
    data->name[sizeof(data->name) - 1] = '\0'; // Assicura terminazione
    data->value = value;
    
    return data;
}

/**
 * Funzione che libera la memoria di una struttura
 * Questa funzione sarà esposta a Python
 * 
 * @param data Puntatore alla struttura da liberare
 */
void free_struct(SharedStruct* data) {
    free(data);
}

/**
 * Funzione che stampa informazioni sulla struttura
 * Questa funzione sarà esposta a Python
 * 
 * @param data Puntatore alla struttura da stampare
 */
void print_struct(SharedStruct* data) {
    printf("Struttura [ID: %d, Nome: %s, Valore: %.2f]\n", 
           data->id, data->name, data->value);
}

/**
 * Callback function type che sarà chiamata da C ma implementata in Python
 */
typedef void (*CallbackFunc)(int, const char*);

/**
 * Funzione che accetta una callback e la chiama
 * Questa funzione sarà esposta a Python
 * 
 * @param callback Funzione di callback da chiamare
 * @param times Numero di volte da chiamare la callback
 */
void call_callback(CallbackFunc callback, int times) {
    for (int i = 0; i < times; i++) {
        char message[100];
        sprintf(message, "Chiamata %d dalla funzione C", i + 1);
        callback(i, message);
    }
}

/**
 * Istruzioni per la compilazione della libreria condivisa:
 * 
 * Linux:
 *   gcc -Wall -fPIC -shared 05_ffi_python_integration.c -o libcexample.so
 * 
 * macOS:
 *   gcc -Wall -fPIC -dynamiclib 05_ffi_python_integration.c -o libcexample.dylib
 * 
 * Windows (con MinGW):
 *   gcc -Wall -shared 05_ffi_python_integration.c -o cexample.dll
 */

/**
 * Esempio di script Python per utilizzare questa libreria:
 * 
 * ```python
 * import ctypes
 * import os
 * import platform
 * 
 * # Carica la libreria condivisa
 * if platform.system() == "Windows":
 *     lib = ctypes.CDLL("./cexample.dll")
 * elif platform.system() == "Darwin":
 *     lib = ctypes.CDLL("./libcexample.dylib")
 * else:
 *     lib = ctypes.CDLL("./libcexample.so")
 * 
 * # Definisci i tipi di ritorno e i parametri delle funzioni
 * lib.sum_array.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
 * lib.sum_array.restype = ctypes.c_int
 * 
 * lib.average_array.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]
 * lib.average_array.restype = ctypes.c_double
 * 
 * # Definisci la struttura in Python
 * class SharedStruct(ctypes.Structure):
 *     _fields_ = [
 *         ("id", ctypes.c_int),
 *         ("name", ctypes.c_char * 50),
 *         ("value", ctypes.c_double)
 *     ]
 * 
 * lib.modify_struct.argtypes = [ctypes.POINTER(SharedStruct), ctypes.c_double]
 * lib.modify_struct.restype = None
 * 
 * lib.create_struct.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_double]
 * lib.create_struct.restype = ctypes.POINTER(SharedStruct)
 * 
 * lib.free_struct.argtypes = [ctypes.POINTER(SharedStruct)]
 * lib.free_struct.restype = None
 * 
 * lib.print_struct.argtypes = [ctypes.POINTER(SharedStruct)]
 * lib.print_struct.restype = None
 * 
 * # Definisci il tipo di callback
 * CALLBACK_FUNC = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_char_p)
 * 
 * lib.call_callback.argtypes = [CALLBACK_FUNC, ctypes.c_int]
 * lib.call_callback.restype = None
 * 
 * # Test della funzione sum_array
 * arr = (ctypes.c_int * 5)(1, 2, 3, 4, 5)
 * result = lib.sum_array(arr, 5)
 * print(f"Somma dell'array: {result}")
 * 
 * # Test della funzione average_array
 * arr_double = (ctypes.c_double * 3)(1.5, 2.5, 3.5)
 * avg = lib.average_array(arr_double, 3)
 * print(f"Media dell'array: {avg}")
 * 
 * # Test delle funzioni per la struttura
 * struct_ptr = lib.create_struct(42, b"Test", 3.14)
 * print("Struttura creata:")
 * lib.print_struct(struct_ptr)
 * 
 * lib.modify_struct(struct_ptr, 2.71)
 * print("\nStruttura modificata:")
 * lib.print_struct(struct_ptr)
 * 
 * # Test della callback
 * @CALLBACK_FUNC
 * def py_callback(index, message):
 *     print(f"Callback Python - Indice: {index}, Messaggio: {message.decode()}")
 * 
 * print("\nTest della callback:")
 * lib.call_callback(py_callback, 3)
 * 
 * # Libera la memoria
 * lib.free_struct(struct_ptr)
 * print("\nMemoria liberata.")
 * ```
 */