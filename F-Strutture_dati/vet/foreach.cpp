/**
 * Stampa del contenuto di un vettore di 10 elementi 
 * utilizzando il ciclo for each
 */

#include <iostream>
using namespace std;

int main() {
    int vettore[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Stampa del contenuto del vettore
    for (int i : vettore) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
