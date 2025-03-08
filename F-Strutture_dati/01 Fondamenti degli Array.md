

Ecco il **Capitolo 1: Fondamenti degli Array** del libro *"Array in C"*, strutturato secondo le tue indicazioni:

---

### **Capitolo 1: Fondamenti degli Array**  
**Obiettivi**:  
- Comprendere cos'è un array e come rappresentarlo in memoria.  
- Imparare a dichiarare, inizializzare e accedere agli elementi.  
- Evitare errori comuni come l'accesso fuori dai limiti.  

---

#### **1.1 Cos'è un Array?**  
Un **array** è una collezione di elementi dello stesso tipo, memorizzati in modo contiguo nella memoria.  
- **Caratteristiche**:  
  - Dimensione fissa (decisa in fase di compilazione in C standard).  
  - Accesso diretto tramite indice (a partire da 0).  
- **Esempio**:  
  ```c  
  int numeri[5]; // Array di 5 interi  
  ```  

---

#### **1.2 Dichiarazione e Inizializzazione**  
**Dichiarazione**:  
```c  
tipo nome_array[dimensione];  
```  
**Inizializzazione**:  
```c  
int voti[3] = {8, 9, 7}; // Inizializzazione completa  
int matrice[2][3] = {{1, 2, 3}, {4, 5, 6}}; // Array 2D  
```  
- **Casi particolari**:  
  - Se la dimensione è omessa, il compilatore la deduce dagli elementi:  
    ```c  
    int numeri[] = {10, 20, 30}; // Dimensione 3  
    ```  
  - Inizializzazione parziale (gli elementi non specificati sono posti a 0):  
    ```c  
    int valori[5] = {1, 2}; // {1, 2, 0, 0, 0}  
    ```  

---

#### **1.3 Accesso agli Elementi**  
Gli elementi sono accessibili tramite indice:  
```c  
int primo_voto = voti[0]; // 8  
voti[1] = 10; // Modifica il secondo elemento  
```  
- **Attenzione**:  
  - L'accesso a un indice fuori range (**buffer overflow**) causa comportamenti imprevedibili.  

---

#### **1.4 Array e Memoria**  
Gli array sono memorizzati in blocchi contigui:  
```
Indirizzo: 0x100 | 0x104 | 0x108 | 0x10C | 0x110  
Valore:      8     |   9   |   7   |   0   |   0  
```  
- **Esempio di calcolo dell'indirizzo**:  
  ```c  
  int arr[5];  
  printf("%p", &arr[2]); // Equivale a: (arr + 2)  
  ```  

---

### **Best Practice**  
1. **Evitare array dinamici in C standard**: Usare dimensioni fisse o `malloc`/`calloc` per array dinamici.  
2. **Preferire inizializzazioni complete**:  
   ```c  
   int arr[5] = {0}; // Inizializza tutti gli elementi a 0  
   ```  
3. **Usare costanti per dimensioni**:  
   ```c  
   #define N 10  
   int dati[N];  
   ```  

---

### **Tip & Tricks**  
- **Calcolare la lunghezza di un array**:  
  ```c  
  int len = sizeof(arr) / sizeof(arr[0]); // Solo per array statici!  
  ```  
- **Inizializzazione con designators (C99)**:  
  ```c  
  int giorni[] = {[0] = 31, [1] = 28, [2] = 31}; // {31, 28, 31}  
  ```  

---

### **Domande di Autovalutazione**  
1. Qual è l'indice del primo elemento di un array?  
   a) 1  
   b) 0  
   c) Dipende dal tipo  

2. Cosa succede se si scrive `int arr[];`?  
   a) Errore di compilazione  
   b) Viene creato un array di dimensione 0  
   c) Viene allocato automaticamente un array di 10 elementi  

3. Quale codice inizializza correttamente un array 2D 3x2?  
   a) `int mat[3][2] = {{1, 2}, {3, 4}, {5, 6}};`  
   b) `int mat[3][2] = {1, 2, 3, 4, 5, 6};`  
   c) Entrambe le opzioni sono valide  

**Risposte**:  
1. b) 0  
2. a) Errore di compilazione  
3. c) Entrambe le opzioni sono valide  

---

### **Esercizi**  
1. **Array di caratteri**: Crea un array di caratteri contenente il tuo nome e stampalo.  
2. **Inversione elementi**: Scrivi una funzione per invertire gli elementi di un array.  
3. **Media con array**: Calcola la media di un array di numeri float.  

**Esempio di soluzione per l'esercizio 2**:  
```c  
#include <stdio.h>  

void inverti(int arr[], int len) {  
    for (int i = 0; i < len / 2; i++) {  
        int temp = arr[i];  
        arr[i] = arr[len - 1 - i];  
        arr[len - 1 - i] = temp;  
    }  
}  

int main() {  
    int numeri[] = {1, 2, 3, 4, 5};  
    inverti(numeri, 5);  
    for (int i = 0; i < 5; i++) {  
        printf("%d ", numeri[i]); // Output: 5 4 3 2 1  
    }  
    return 0;  
}  
```  
