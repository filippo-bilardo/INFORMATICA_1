#include <iostream>
using namespace std;

int main() {
    int size;
    cout << "Inserisci la dimensione dell'array: ";
    cin >> size;

    // Allocazione dinamica dell'array
    int* numeri = new int[size];

    // Lettura dei valori dall'utente
    cout << "Inserisci " << size << " numeri:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> numeri[i];
    }

    // Stampa degli elementi
    cout << "Array inserito:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numeri[i] << " ";
    }
    cout << endl;

    // Deallocazione della memoria
    delete[] numeri;

    return 0;
}