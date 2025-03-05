#include <iostream>
using namespace std;

int main() {
    // Array di domande e risposte corrette
    string domande[3] = {"Qual è la capitale dell'Italia?", "Quanto fa 2 + 2?", "Quanti giorni ha un anno bisestile?"};
    string risposteCorrette[3] = {"Roma", "4", "366"};

    int punteggio = 0;

    for (int i = 0; i < 3; i++) {
        cout << "Domanda " << (i + 1) << ": " << domande[i] << endl;
        string rispostaUtente;
        cin >> rispostaUtente;

        if (rispostaUtente == risposteCorrette[i]) {
            cout << "Corretto!" << endl;
            punteggio++;
        } else {
            cout << "Sbagliato. La risposta corretta era: " << risposteCorrette[i] << endl;
        }
    }

    cout << "\nPunteggio finale: " << punteggio << "/3" << endl;

    return 0;
}