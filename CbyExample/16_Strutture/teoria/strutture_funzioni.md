# Strutture e Funzioni in C

## Introduzione

L'interazione tra strutture e funzioni è un aspetto fondamentale della programmazione in C. In questo capitolo, esploreremo come passare strutture alle funzioni, restituire strutture dalle funzioni e implementare funzioni che operano su strutture.

## Passaggio di Strutture alle Funzioni

In C, le strutture possono essere passate alle funzioni in tre modi principali:

1. Passaggio per valore
2. Passaggio per indirizzo (riferimento)
3. Passaggio di singoli membri

### Passaggio per Valore

Quando una struttura viene passata per valore, viene creata una copia completa della struttura. Questo significa che le modifiche apportate alla struttura all'interno della funzione non influenzano la struttura originale.

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che riceve una struttura per valore
void stampaPersona(Persona p) {
    printf("Nome: %s, Cognome: %s, Età: %d\n", p.nome, p.cognome, p.eta);
    
    // Questa modifica non influenzerà la struttura originale
    p.eta = 100;
}

int main() {
    Persona persona1 = {"Mario", "Rossi", 30};
    
    stampaPersona(persona1);
    
    // L'età rimane invariata
    printf("Età dopo la chiamata: %d\n", persona1.eta);  // Output: 30
    
    return 0;
}
```

**Vantaggi**:
- Semplice da implementare
- La struttura originale è protetta da modifiche accidentali

**Svantaggi**:
- Inefficiente per strutture grandi (copia completa)
- Non permette di modificare la struttura originale

### Passaggio per Indirizzo (Riferimento)

Passare una struttura per indirizzo significa passare un puntatore alla struttura. Questo è più efficiente e permette di modificare la struttura originale.

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che riceve un puntatore a struttura
void invecchiaPersona(Persona *p) {
    // Accesso ai membri tramite l'operatore freccia
    p->eta += 1;
    printf("%s %s ha ora %d anni\n", p->nome, p->cognome, p->eta);
}

int main() {
    Persona persona1 = {"Mario", "Rossi", 30};
    
    printf("Età prima: %d\n", persona1.eta);  // Output: 30
    
    // Passaggio dell'indirizzo della struttura
    invecchiaPersona(&persona1);
    
    // L'età è stata modificata
    printf("Età dopo: %d\n", persona1.eta);  // Output: 31
    
    return 0;
}
```

**Vantaggi**:
- Efficiente (nessuna copia della struttura)
- Permette di modificare la struttura originale

**Svantaggi**:
- Potenziali modifiche accidentali alla struttura originale
- Sintassi leggermente più complessa (uso dell'operatore `->`)

### Passaggio di Singoli Membri

In alcuni casi, potrebbe essere necessario passare solo alcuni membri specifici di una struttura:

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che riceve solo l'età
void verificaEtaPensione(int eta) {
    if (eta >= 67) {
        printf("Età pensionabile raggiunta\n");
    } else {
        printf("Mancano %d anni alla pensione\n", 67 - eta);
    }
}

int main() {
    Persona persona1 = {"Mario", "Rossi", 30};
    
    // Passaggio di un singolo membro
    verificaEtaPensione(persona1.eta);
    
    return 0;
}
```

## Restituzione di Strutture dalle Funzioni

Le funzioni in C possono anche restituire strutture. Ci sono due approcci principali:

1. Restituzione per valore
2. Restituzione per indirizzo

### Restituzione per Valore

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che restituisce una struttura per valore
Persona creaPersona(const char *nome, const char *cognome, int eta) {
    Persona nuova;
    strcpy(nuova.nome, nome);
    strcpy(nuova.cognome, cognome);
    nuova.eta = eta;
    return nuova;
}

int main() {
    // La funzione restituisce una struttura completa
    Persona persona1 = creaPersona("Mario", "Rossi", 30);
    
    printf("Persona creata: %s %s, %d anni\n", 
           persona1.nome, persona1.cognome, persona1.eta);
    
    return 0;
}
```

**Vantaggi**:
- Semplice da implementare e utilizzare
- Non richiede gestione della memoria dinamica

**Svantaggi**:
- Inefficiente per strutture grandi (copia completa)

### Restituzione per Indirizzo

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che restituisce un puntatore a una struttura allocata dinamicamente
Persona* creaPersonaDinamica(const char *nome, const char *cognome, int eta) {
    Persona *nuova = (Persona*)malloc(sizeof(Persona));
    if (nuova != NULL) {
        strcpy(nuova->nome, nome);
        strcpy(nuova->cognome, cognome);
        nuova->eta = eta;
    }
    return nuova;
}

int main() {
    // La funzione restituisce un puntatore a una struttura
    Persona *persona1 = creaPersonaDinamica("Mario", "Rossi", 30);
    
    if (persona1 != NULL) {
        printf("Persona creata: %s %s, %d anni\n", 
               persona1->nome, persona1->cognome, persona1->eta);
        
        // Importante: liberare la memoria allocata dinamicamente
        free(persona1);
    }
    
    return 0;
}
```

**Vantaggi**:
- Efficiente (nessuna copia della struttura)
- Utile per strutture grandi o quando la struttura deve sopravvivere alla funzione

**Svantaggi**:
- Richiede gestione manuale della memoria (chiamata a `free()`)
- Potenziali memory leak se non gestita correttamente

## Funzioni che Operano su Array di Strutture

Spesso è necessario implementare funzioni che operano su array di strutture, ad esempio per cercare, ordinare o filtrare elementi.

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTI 100

typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} Studente;

// Funzione che cerca uno studente per matricola
Studente* cercaStudentePerMatricola(Studente studenti[], int n, int matricola) {
    for (int i = 0; i < n; i++) {
        if (studenti[i].matricola == matricola) {
            return &studenti[i];
        }
    }
    return NULL;  // Studente non trovato
}

// Funzione che calcola la media dei voti di tutti gli studenti
float calcolaMediaClasse(Studente studenti[], int n) {
    if (n <= 0) return 0.0;
    
    float somma = 0.0;
    for (int i = 0; i < n; i++) {
        somma += studenti[i].media_voti;
    }
    return somma / n;
}

// Funzione che ordina gli studenti per media voti (bubble sort)
void ordinaStudentiPerMedia(Studente studenti[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (studenti[j].media_voti < studenti[j+1].media_voti) {
                // Scambio delle strutture
                Studente temp = studenti[j];
                studenti[j] = studenti[j+1];
                studenti[j+1] = temp;
            }
        }
    }
}

int main() {
    Studente classe[MAX_STUDENTI] = {
        {"Mario", "Rossi", 12345, 27.5},
        {"Laura", "Bianchi", 67890, 29.0},
        {"Giovanni", "Verdi", 54321, 26.0},
        {"Anna", "Neri", 98765, 28.5}
    };
    int num_studenti = 4;
    
    // Ricerca di uno studente
    int matricola_da_cercare = 54321;
    Studente *trovato = cercaStudentePerMatricola(classe, num_studenti, matricola_da_cercare);
    
    if (trovato != NULL) {
        printf("Studente trovato: %s %s, Media: %.2f\n", 
               trovato->nome, trovato->cognome, trovato->media_voti);
    } else {
        printf("Studente con matricola %d non trovato\n", matricola_da_cercare);
    }
    
    // Calcolo della media della classe
    float media_classe = calcolaMediaClasse(classe, num_studenti);
    printf("Media della classe: %.2f\n", media_classe);
    
    // Ordinamento degli studenti per media
    ordinaStudentiPerMedia(classe, num_studenti);
    
    // Stampa degli studenti ordinati
    printf("\nStudenti ordinati per media:\n");
    for (int i = 0; i < num_studenti; i++) {
        printf("%d. %s %s: %.2f\n", i+1, 
               classe[i].nome, classe[i].cognome, classe[i].media_voti);
    }
    
    return 0;
}
```

## Strutture come Campi di Altre Strutture

Le strutture possono essere utilizzate come campi di altre strutture, creando relazioni complesse tra i dati:

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char via[50];
    char citta[30];
    char provincia[3];
    int cap;
} Indirizzo;

typedef struct {
    char nome[50];
    char cognome[50];
    Data data_nascita;
    Indirizzo residenza;
    Indirizzo domicilio;
} Persona;

// Funzione che calcola l'età di una persona
int calcolaEta(const Data *data_nascita, const Data *data_attuale) {
    int eta = data_attuale->anno - data_nascita->anno;
    
    // Controllo se il compleanno è già passato quest'anno
    if (data_attuale->mese < data_nascita->mese || 
        (data_attuale->mese == data_nascita->mese && 
         data_attuale->giorno < data_nascita->giorno)) {
        eta--;
    }
    
    return eta;
}

// Funzione che verifica se due indirizzi sono uguali
int indirizziUguali(const Indirizzo *ind1, const Indirizzo *ind2) {
    return (strcmp(ind1->via, ind2->via) == 0 &&
            strcmp(ind1->citta, ind2->citta) == 0 &&
            strcmp(ind1->provincia, ind2->provincia) == 0 &&
            ind1->cap == ind2->cap);
}

int main() {
    Persona persona;
    
    // Inizializzazione dei dati
    strcpy(persona.nome, "Mario");
    strcpy(persona.cognome, "Rossi");
    
    persona.data_nascita.giorno = 15;
    persona.data_nascita.mese = 5;
    persona.data_nascita.anno = 1990;
    
    strcpy(persona.residenza.via, "Via Roma 123");
    strcpy(persona.residenza.citta, "Milano");
    strcpy(persona.residenza.provincia, "MI");
    persona.residenza.cap = 20100;
    
    // Copiamo l'indirizzo di residenza come domicilio
    persona.domicilio = persona.residenza;
    
    // Data attuale
    Data oggi = {10, 6, 2023};
    
    // Calcolo dell'età
    int eta = calcolaEta(&persona.data_nascita, &oggi);
    printf("%s %s ha %d anni\n", persona.nome, persona.cognome, eta);
    
    // Verifica se residenza e domicilio coincidono
    if (indirizziUguali(&persona.residenza, &persona.domicilio)) {
        printf("Residenza e domicilio coincidono\n");
    } else {
        printf("Residenza e domicilio sono diversi\n");
    }
    
    return 0;
}
```

## Best Practices

Quando si utilizzano strutture con funzioni, è importante seguire alcune best practices:

1. **Passaggio per valore vs. per indirizzo**:
   - Passa le strutture per valore solo se sono piccole o se vuoi garantire che non vengano modificate
   - Passa le strutture per indirizzo (puntatore) se sono grandi o se devono essere modificate

2. **Documentazione**:
   - Documenta chiaramente se una funzione modifica o meno la struttura passata
   - Usa `const` per indicare che una struttura o un suo membro non verrà modificato

3. **Gestione della memoria**:
   - Se una funzione alloca dinamicamente una struttura, documenta chi è responsabile di liberare la memoria
   - Considera l'uso di funzioni di "cleanup" o "destroy" per strutture complesse

4. **Incapsulamento**:
   - Considera di creare funzioni specifiche per operare su strutture (simile all'approccio orientato agli oggetti)
   - Ad esempio, invece di manipolare direttamente i campi, usa funzioni come `setNome()`, `getNome()`, ecc.

## Esempio di Incapsulamento

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    char *cognome;
    int eta;
} Persona;

// Funzione per creare una nuova persona
Persona* Persona_crea(const char *nome, const char *cognome, int eta) {
    Persona *p = (Persona*)malloc(sizeof(Persona));
    if (p == NULL) return NULL;
    
    p->nome = strdup(nome);       // Alloca e copia la stringa
    p->cognome = strdup(cognome); // Alloca e copia la stringa
    p->eta = eta;
    
    return p;
}

// Funzione per liberare la memoria di una persona
void Persona_distruggi(Persona *p) {
    if (p != NULL) {
        free(p->nome);
        free(p->cognome);
        free(p);
    }
}

// Funzioni di accesso (getter)
const char* Persona_getNome(const Persona *p) {
    return p->nome;
}

const char* Persona_getCognome(const Persona *p) {
    return p->cognome;
}

int Persona_getEta(const Persona *p) {
    return p->eta;
}

// Funzioni di modifica (setter)
void Persona_setEta(Persona *p, int eta) {
    p->eta = eta;
}

// Funzione per stampare una persona
void Persona_stampa(const Persona *p) {
    printf("%s %s, %d anni\n", p->nome, p->cognome, p->eta);
}

int main() {
    // Creazione di una persona
    Persona *p1 = Persona_crea("Mario", "Rossi", 30);
    if (p1 == NULL) {
        printf("Errore nell'allocazione della memoria\n");
        return 1;
    }
    
    // Utilizzo delle funzioni di accesso
    printf("Nome: %s\n", Persona_getNome(p1));
    printf("Cognome: %s\n", Persona_getCognome(p1));
    printf("Età: %d\n", Persona_getEta(p1));
    
    // Modifica dell'età
    Persona_setEta(p1, 31);
    
    // Stampa della persona
    Persona_stampa(p1);
    
    // Liberazione della memoria
    Persona_distruggi(p1);
    
    return 0;
}
```

## Conclusione

L'interazione tra strutture e funzioni è un aspetto fondamentale della programmazione in C che permette di creare codice modulare, riutilizzabile e ben organizzato. Scegliere il metodo appropriato per passare e restituire strutture, implementare funzioni che operano su strutture e seguire le best practices sono competenze essenziali per scrivere programmi C efficaci ed efficienti.

Nel prossimo capitolo, esploreremo le unioni ed enumerazioni, altri tipi di dati personalizzati che, insieme alle strutture, forniscono potenti strumenti per modellare dati complessi in C.