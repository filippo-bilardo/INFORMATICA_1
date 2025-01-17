### 10. Strutture, Unioni, Manipolazione di Bit e Enumerazioni

#### 10.1 Introduzione
Le strutture, chiamate talvolta "aggregati" nello standard C, sono collezioni di variabili correlate raggruppate sotto un unico nome. Le strutture possono contenere variabili di diversi tipi di dati, a differenza degli array che contengono elementi di un solo tipo di dato. Le strutture sono comunemente utilizzate per definire record da memorizzare nei file. Puntatori e strutture facilitano la creazione di strutture dati più complesse come liste collegate, code, pile e alberi.

In questo capitolo, trattiamo i seguenti argomenti:

- **typedef**: per creare alias per nomi di tipo esistenti.
- **Unioni**: simili alle strutture, ma i membri condividono lo stesso spazio di memoria.
- **Operatori bitwise**: per manipolare i bit degli operandi interi.
- **Campi di bit**: membri di tipo `unsigned int` o `int` nelle strutture o unioni che specificano il numero di bit in cui sono memorizzati, permettendo di impacchettare i dati in modo compatto.
- **Enumerazioni**: insiemi di costanti intere rappresentati da identificatori.

#### 10.2 Definizione delle strutture
Le strutture sono tipi di dati derivati, costruite utilizzando oggetti di altri tipi. Consideriamo la seguente definizione di una struttura:

```c
struct card {
   char *face;
   char *suit;
};
```

Questa struttura definisce una carta da gioco che ha due membri: `face` (faccia) e `suit` (seme), entrambi di tipo puntatore a carattere.


Proseguendo con la traduzione del capitolo 10, ecco le prossime sezioni:

---

#### 10.2.1 Strutture Auto-referenziali
Le **strutture auto-referenziali** sono strutture che contengono un puntatore ad una struttura dello stesso tipo. Questo permette di costruire strutture dati complesse come liste collegate e alberi binari.

Esempio di struttura auto-referenziale:
```c
struct node {
    int data;
    struct node *next;
};
```
In questo esempio, `struct node` ha un membro `next` che è un puntatore ad un'altra struttura `node`.

---

#### 10.2.2 Definizione di Variabili di Tipi di Struttura
Dopo aver definito una struttura, è possibile dichiarare variabili del tipo struttura nello stesso modo in cui si dichiarano variabili di tipi predefiniti.

Esempio:
```c
struct card aCard;
```

---

#### 10.2.3 Nomi dei Tag della Struttura
Nelle strutture, un **tag della struttura** è il nome che segue la parola chiave `struct`. Questo tag può essere utilizzato per dichiarare altre variabili dello stesso tipo senza dover ridichiarare la struttura.

---

#### 10.2.4 Operazioni Che Si Possono Eseguire Sulle Strutture
Le operazioni che possono essere eseguite su una struttura includono:
- **Assegnazione**: una struttura può essere assegnata a un'altra struttura dello stesso tipo.
- **Accesso ai membri**: è possibile accedere ai membri di una struttura utilizzando l'operatore `.`.
- **Passaggio a funzioni**: le strutture possono essere passate a funzioni sia per valore che per riferimento.

---

#### 10.3 Inizializzazione delle Strutture
Le strutture possono essere inizializzate al momento della dichiarazione, specificando i valori dei membri nell'ordine in cui sono dichiarati nella struttura. Se non si forniscono tutti i valori, i membri rimanenti vengono inizializzati a zero (o `NULL` per i puntatori).

---

#### 10.4 Accesso ai Membri delle Strutture con `.` e `->`
Il **punto** (`.`) viene utilizzato per accedere ai membri di una struttura. Quando si lavora con puntatori a strutture, si utilizza l'operatore freccia `->` per accedere ai membri della struttura a cui il puntatore fa riferimento.

Esempio:
```c
struct card *cardPtr = &aCard;
printf("%s", cardPtr->suit);
```

### 10.3 Inizializzazione delle Strutture

Le strutture possono essere inizializzate quando vengono dichiarate, specificando i valori dei membri nell'ordine in cui sono definiti nella struttura. Ecco un esempio di inizializzazione di una struttura:

```c
struct card {
   char *face;
   char *suit;
};

struct card aCard = { "Asso", "Cuori" };
```

In questo esempio, la variabile `aCard` viene dichiarata come di tipo `struct card` e inizializzata con la stringa `"Asso"` per il membro `face` e la stringa `"Cuori"` per il membro `suit`.

#### Inizializzazione Parziale

Se si desidera inizializzare solo alcuni membri di una struttura, è possibile specificare un numero inferiore di valori durante l'inizializzazione. In tal caso, i membri non specificati vengono automaticamente inizializzati a zero o a `NULL` nel caso di puntatori.

Esempio:

```c
struct card anotherCard = { "Re" }; // solo face viene inizializzato
```

In questo esempio, il membro `face` della struttura `anotherCard` viene inizializzato con `"Re"`, mentre il membro `suit` viene inizializzato a `NULL`.

#### Inizializzazione con Designatori

Dal C99 in poi, è possibile utilizzare i **designatori** per inizializzare specifici membri della struttura senza preoccuparsi dell'ordine. I designatori specificano il nome del membro che si desidera inizializzare.

Esempio:

```c
struct card anotherCard = { .suit = "Fiori", .face = "Donna" };
```

In questo esempio, il membro `suit` viene inizializzato con `"Fiori"` e il membro `face` con `"Donna"`, anche se sono stati specificati in un ordine diverso rispetto alla dichiarazione originale della struttura.

# esempio senza puntatori

Ecco un esempio di utilizzo delle strutture senza puntatori, con l'inizializzazione e l'accesso ai membri della struttura:

### Esempio: Inizializzazione e Accesso a Membri di una Struttura Senza Puntatori

Definiamo una struttura `Person` che contiene i membri `nome`, `età` e `altezza`:

```c
#include <stdio.h>

struct Person {
    char nome[50];
    int eta;
    float altezza;
};

int main() {
    // Inizializzazione di una variabile di tipo struct Person
    struct Person persona1 = { "Mario Rossi", 30, 1.75 };

    // Accesso ai membri della struttura
    printf("Nome: %s\n", persona1.nome);
    printf("Età: %d\n", persona1.eta);
    printf("Altezza: %.2f metri\n", persona1.altezza);

    return 0;
}
```

### Output:
```
Nome: Mario Rossi
Età: 30
Altezza: 1.75 metri
```

#### Spiegazione:

1. **Definizione della struttura**: La struttura `Person` ha tre membri: `nome` (una stringa di massimo 50 caratteri), `eta` (un intero) e `altezza` (un numero in virgola mobile).
2. **Inizializzazione**: Nel blocco `main`, dichiariamo la variabile `persona1` di tipo `struct Person` e la inizializziamo con i valori `"Mario Rossi"`, `30` e `1.75`.
3. **Accesso ai membri**: Usiamo l'operatore `.` per accedere ai membri della struttura e stampiamo i valori con `printf`.

In questo esempio, non utilizziamo puntatori per accedere ai membri della struttura, ma ci limitiamo a lavorare direttamente sulla variabile `persona1` dichiarata.

Ecco la traduzione della sezione successiva del capitolo 10.

### 10.5 Utilizzo delle Strutture con le Funzioni

Le strutture possono essere passate alle funzioni in diversi modi:

- **Passaggio di singoli membri della struttura.**
- **Passaggio di un'intera struttura.**
- **Passaggio di un puntatore a una struttura.**

Quando una struttura o i suoi singoli membri vengono passati a una funzione, essi vengono passati **per valore**. Di conseguenza, i membri della struttura nel chiamante non possono essere modificati dalla funzione chiamata. Se si desidera modificare i membri della struttura nella funzione chiamata, è necessario passare un **puntatore** alla struttura, cioè passarla **per riferimento**.

Gli array di strutture, come tutti gli altri array, vengono passati automaticamente per riferimento. Questo significa che le modifiche apportate agli elementi di un array all'interno di una funzione avranno effetto anche al di fuori di essa.

#### 10.5.1 Passaggio di Singoli Membri

Ecco un esempio di passaggio di singoli membri di una struttura a una funzione:

```c
#include <stdio.h>

struct card {
    char *face;
    char *suit;
};

void printCard(char *face, char *suit) {
    printf("%s di %s\n", face, suit);
}

int main() {
    struct card aCard = { "Asso", "Cuori" };
    printCard(aCard.face, aCard.suit);
    return 0;
}
```

In questo esempio, i membri `face` e `suit` della struttura `aCard` vengono passati individualmente alla funzione `printCard`.

#### 10.5.2 Passaggio di una Struttura Intera

Un'intera struttura può essere passata a una funzione, come illustrato di seguito:

```c
#include <stdio.h>

struct card {
    char *face;
    char *suit;
};

void printCard(struct card aCard) {
    printf("%s di %s\n", aCard.face, aCard.suit);
}

int main() {
    struct card aCard = { "Asso", "Cuori" };
    printCard(aCard);
    return 0;
}
```

In questo esempio, l'intera struttura `aCard` viene passata alla funzione `printCard`.

#### 10.5.3 Passaggio di un Puntatore a una Struttura

Se si vuole modificare una struttura all'interno di una funzione, è necessario passare un puntatore alla struttura. Ecco un esempio:

```c
#include <stdio.h>

struct card {
    char *face;
    char *suit;
};

void printCard(struct card *cardPtr) {
    printf("%s di %s\n", cardPtr->face, cardPtr->suit);
}

int main() {
    struct card aCard = { "Asso", "Cuori" };
    printCard(&aCard);
    return 0;
}
```

In questo caso, la funzione `printCard` riceve un puntatore alla struttura `aCard`. All'interno della funzione, i membri della struttura vengono acceduti usando l'operatore freccia (`->`), che viene utilizzato per accedere ai membri di una struttura puntata da un puntatore.

### 10.6 `typedef`

La parola chiave `typedef` fornisce un meccanismo per creare sinonimi (o alias) per tipi di dati già definiti. È spesso utilizzata per semplificare nomi di tipo complessi e rendere il codice più leggibile.

Un esempio comune è l'uso di `typedef` per rinominare un tipo di struttura. Considera il seguente esempio:

```c
typedef struct {
    char titolo[100];
    char autore[50];
    int pagine;
} Libro;
```

In questo caso, viene creato un nuovo tipo chiamato `Libro`, che è un sinonimo della struttura senza la necessità di utilizzare la parola chiave `struct` ogni volta che si dichiara una variabile di quel tipo.

### 10.7 Esempio: Simulazione di Mescolamento e Distribuzione di Carte

Questo programma rappresenta un mazzo di carte come un array di strutture e utilizza `typedef` per facilitare la gestione delle carte. Nell'esempio seguente, mescoliamo e distribuiamo le carte usando strutture:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES 13

typedef struct {
    char *face;
    char *suit;
} Carta;

void riempiMazzo(Carta * const mazzo, const char * facce[], const char * semi[]);
void mescola(Carta * const mazzo);
void distribuisci(const Carta * const mazzo);

int main(void) {
    const char *facce[] = { "Asso", "Due", "Tre", "Quattro", "Cinque",
                            "Sei", "Sette", "Otto", "Nove", "Dieci",
                            "Jack", "Regina", "Re" };
    const char *semi[] = { "Cuori", "Quadri", "Fiori", "Picche" };

    Carta mazzo[CARDS];
    
    srand(time(NULL));  // inizializza il generatore di numeri casuali
    riempiMazzo(mazzo, facce, semi);
    mescola(mazzo);
    distribuisci(mazzo);

    return 0;
}

void riempiMazzo(Carta * const mazzo, const char * facce[], const char * semi[]) {
    for (size_t i = 0; i < CARDS; ++i) {
        mazzo[i].face = facce[i % FACES];
        mazzo[i].suit = semi[i / FACES];
    }
}

void mescola(Carta * const mazzo) {
    for (size_t i = 0; i < CARDS; ++i) {
        size_t j = rand() % CARDS;
        Carta temp = mazzo[i];
        mazzo[i] = mazzo[j];
        mazzo[j] = temp;
    }
}

void distribuisci(const Carta * const mazzo) {
    for (size_t i = 0; i < CARDS; ++i) {
        printf("%5s di %-8s%s", mazzo[i].face, mazzo[i].suit, (i + 1) % 4 ? "  " : "\n");
    }
}
```

### Spiegazione del Codice

1. **Tipi `typedef`**: La struttura `Carta` rappresenta ogni singola carta del mazzo, contenente due stringhe, una per la faccia e una per il seme.
   
2. **Funzioni**:
   - `riempiMazzo`: Popola il mazzo con tutte le 52 carte, associando facce e semi.
   - `mescola`: Mescola casualmente le carte nel mazzo usando l'algoritmo di Fisher-Yates.
   - `distribuisci`: Stampa le carte in un formato leggibile, quattro carte per riga.

---

Questo esempio illustra come utilizzare strutture, `typedef`, e funzioni per simulare un classico problema di programmazione, rendendo il codice più modulare e leggibile grazie all'uso di `typedef`.

# altro esempio
Ecco un altro esempio, questa volta modelliamo una **struttura Studente** per memorizzare informazioni di base su uno studente, come il nome, l'età e la media dei voti. Successivamente, creeremo una funzione per calcolare e aggiornare la media dei voti:

### Esempio: Gestione dei Dati di uno Studente

```c
#include <stdio.h>

typedef struct {
    char nome[50];
    int eta;
    float voti[5];
    float media;
} Studente;

void calcolaMedia(Studente *studente) {
    float somma = 0.0;
    for (int i = 0; i < 5; i++) {
        somma += studente->voti[i];
    }
    studente->media = somma / 5;
}

void stampaStudente(Studente studente) {
    printf("Nome: %s\n", studente.nome);
    printf("Età: %d\n", studente.eta);
    printf("Media Voti: %.2f\n", studente.media);
}

int main() {
    // Inizializzazione di uno studente
    Studente studente1 = { "Luca Bianchi", 20, {28.5, 30, 27, 29, 26}, 0 };

    // Calcolo della media dei voti
    calcolaMedia(&studente1);

    // Stampa dei dati dello studente
    stampaStudente(studente1);

    return 0;
}
```

### Spiegazione del Codice:

1. **Definizione della struttura `Studente`**: 
   - Contiene i seguenti membri:
     - `nome`: una stringa per il nome dello studente.
     - `eta`: un intero per l'età.
     - `voti`: un array di 5 numeri in virgola mobile per i voti ottenuti.
     - `media`: un numero in virgola mobile per la media dei voti.

2. **Funzione `calcolaMedia`**: 
   - Questa funzione riceve un puntatore alla struttura `Studente`, somma i voti presenti nell'array e aggiorna il campo `media`.

3. **Funzione `stampaStudente`**:
   - Stampa le informazioni dello studente, inclusi nome, età e media dei voti.

4. **Inizializzazione e utilizzo**:
   - Lo studente `studente1` viene inizializzato con nome, età e voti.
   - Viene chiamata la funzione `calcolaMedia` per aggiornare la media.
   - Infine, `stampaStudente` mostra i dati dello studente.

### Output:
```
Nome: Luca Bianchi
Età: 20
Media Voti: 28.20
```

### Cosa Apprendiamo:

- **Modellazione con Strutture**: Questo esempio mostra come raccogliere più informazioni correlate in una singola struttura.
- **Uso di `typedef`**: L'uso di `typedef` rende il codice più pulito, evitando di dover specificare ripetutamente `struct`.
- **Manipolazione tramite Funzioni**: Le funzioni `calcolaMedia` e `stampaStudente` mostrano come passare una struttura e come modificarne i membri usando puntatori.

### 10.8 Le Unioni

Le **unioni** sono simili alle strutture, ma i membri di un'unione condividono lo stesso spazio di memoria. Le unioni sono utili quando diverse variabili sono usate in momenti diversi e possono condividere lo stesso spazio di memoria, ottimizzando l'uso dello spazio. Solo un membro di un'unione può essere utilizzato in un dato momento, e l'utente è responsabile di assicurarsi che l'accesso ai dati avvenga con il tipo corretto.

#### 10.8.1 Dichiarazioni di Unioni

Una dichiarazione di unione segue la stessa sintassi delle strutture. Ad esempio:

```c
union numero {
   int x;
   double y;
};
```

Questo crea un tipo `union numero` con due membri: un intero `x` e un doppio `y`. Solo uno di questi può essere utilizzato alla volta, poiché condividono lo stesso spazio di memoria. L'unione viene tipicamente definita in un header e inclusa nei file sorgente che la utilizzano.

#### 10.8.2 Operazioni su Unioni

Le operazioni che si possono eseguire sulle unioni includono:

- **Assegnazione** di un'unione a un'altra dello stesso tipo.
- **Accesso ai membri** tramite l'operatore punto (`.`) o l'operatore freccia (`->`) con un puntatore a un'unione.
- **Prendere l'indirizzo** (`&`) di una variabile di tipo unione.

Le unioni non possono essere confrontate utilizzando gli operatori di uguaglianza (`==`) o disuguaglianza (`!=`) per motivi analoghi a quelli delle strutture.

#### 10.8.3 Inizializzazione delle Unioni

In una dichiarazione, un'unione può essere inizializzata con un valore dello stesso tipo del suo primo membro. Ad esempio:

```c
union numero val = { 10 };  // valido, il primo membro è un int
```

Se si tenta di inizializzare con un tipo diverso dal primo membro, come un `double` in questo esempio, il compilatore potrebbe segnalare un avviso o troncare il valore.

#### 10.8.4 Esempio di Utilizzo delle Unioni

Il seguente programma dimostra l'uso delle unioni:

```c
#include <stdio.h>

union numero {
   int x;
   double y;
};

int main() {
   union numero val = { 100 };
   printf("Int: %d\n", val.x);
   printf("Double: %f\n", val.y);

   val.y = 100.0;
   printf("Int: %d\n", val.x);
   printf("Double: %f\n", val.y);
   
   return 0;
}
```

In questo esempio, l'unione `val` viene inizialmente valorizzata con un intero `100`. Successivamente, viene riassegnato un valore in virgola mobile a `val.y`. Questo mostra come l'uso improprio di un tipo può portare a comportamenti imprevisti, poiché l'unione condivide la memoria tra i membri.

---

### 10.9 Operatori Bitwise

Gli **operatori bitwise** vengono utilizzati per manipolare direttamente i singoli bit di numeri interi. Questi operatori includono:

- **AND bitwise** (`&`)
- **OR inclusivo bitwise** (`|`)
- **OR esclusivo bitwise** (`^`)
- **Complemento bitwise** (`~`)
- **Shift a sinistra** (`<<`)
- **Shift a destra** (`>>`)

#### 10.9.1 Visualizzare un Intero in Forma Binaria

Quando si utilizzano gli operatori bitwise, può essere utile visualizzare il valore di una variabile in forma binaria per comprendere meglio l'effetto degli operatori. Il seguente programma stampa un intero non negativo in binario:

```c
#include <stdio.h>

void visualizzaBit(unsigned int valore) {
    unsigned int maschera = 1 << 31;  // Maschera iniziale

    for (int i = 0; i < 32; ++i) {
        putchar(valore & maschera ? '1' : '0');
        valore <<= 1;

        if ((i + 1) % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int main() {
    unsigned int numero;
    printf("Inserisci un numero intero non negativo: ");
    scanf("%u", &numero);

    visualizzaBit(numero);
    return 0;
}
```

Questo programma utilizza l'operatore **AND bitwise** per confrontare bit per bit un valore con una maschera, che viene spostata a sinistra per visualizzare ciascun bit.

Ecco alcuni esempi pratici che mostrano diversi usi delle **unioni** in C.

### 1. **Uso di unioni per risparmiare memoria**

Le unioni permettono di risparmiare memoria quando variabili diverse condividono lo stesso spazio di memoria, poiché solo una di esse sarà utilizzata alla volta. Vediamo un esempio in cui un'unione viene utilizzata per rappresentare un valore numerico che può essere di tipo intero o floating-point.

#### Esempio 1: Unione per numeri interi e floating-point

```c
#include <stdio.h>

union Numero {
    int intero;
    float floating_point;
};

int main() {
    union Numero numero;

    // Memorizza un numero intero
    numero.intero = 10;
    printf("Numero intero: %d\n", numero.intero);

    // Memorizza un numero floating-point
    numero.floating_point = 10.5;
    printf("Numero floating-point: %.2f\n", numero.floating_point);

    // Attenzione: dopo aver scritto su floating_point, il valore intero non è più valido
    printf("Dopo floating-point, intero: %d (valore corrotto)\n", numero.intero);

    return 0;
}
```

### Spiegazione:
- L'unione `Numero` può contenere sia un intero che un numero in virgola mobile, ma non contemporaneamente. Quando memorizziamo un valore in `floating_point`, il valore in `intero` viene sovrascritto, portando a risultati imprevedibili se si tenta di accedere ad esso.

### Output:
```
Numero intero: 10
Numero floating-point: 10.50
Dopo floating-point, intero: 1092616192 (valore corrotto)
```

---

### 2. **Unioni per rappresentare tipi di dati diversi (es. per la gestione di dati eterogenei)**

Unioni possono essere utili quando si devono gestire dati eterogenei che possono avere diversi tipi, ad esempio in strutture dati come variabili `union` in un linguaggio di scripting o gestione di valori generici in un interprete.

#### Esempio 2: Unione per tipi di dati eterogenei

```c
#include <stdio.h>

union Dato {
    int intero;
    float floating_point;
    char stringa[20];
};

int main() {
    union Dato dato;

    // Memorizza un intero
    dato.intero = 42;
    printf("Intero: %d\n", dato.intero);

    // Memorizza un numero floating-point
    dato.floating_point = 3.14;
    printf("Floating-point: %.2f\n", dato.floating_point);

    // Memorizza una stringa
    sprintf(dato.stringa, "Hello");
    printf("Stringa: %s\n", dato.stringa);

    return 0;
}
```

### Spiegazione:
- La stessa unione `Dato` può contenere un intero, un numero floating-point o una stringa di massimo 20 caratteri. Come nell'esempio precedente, una volta che un membro viene scritto, gli altri perdono il loro valore.

### Output:
```
Intero: 42
Floating-point: 3.14
Stringa: Hello
```

---

### 3. **Uso di Unioni in una Struttura**

Le unioni possono essere combinate con le strutture per creare tipi dati più complessi. Ecco un esempio di come un'unione può essere utilizzata all'interno di una struttura per rappresentare un attributo di dati che può avere più tipi.

#### Esempio 3: Struttura con unione

```c
#include <stdio.h>

struct Valore {
    char tipo;  // 'i' per int, 'f' per float
    union {
        int intero;
        float floating_point;
    } dato;
};

int main() {
    struct Valore v1, v2;

    // Inizializza v1 come intero
    v1.tipo = 'i';
    v1.dato.intero = 100;
    printf("Valore intero: %d\n", v1.dato.intero);

    // Inizializza v2 come floating-point
    v2.tipo = 'f';
    v2.dato.floating_point = 99.99;
    printf("Valore floating-point: %.2f\n", v2.dato.floating_point);

    return 0;
}
```

### Spiegazione:
- La struttura `Valore` ha un membro `tipo` che indica il tipo di dato contenuto nell'unione, e l'unione stessa contiene o un intero o un numero floating-point. In questo modo, la struttura può gestire entrambi i tipi di dati con un solo membro.

### Output:
```
Valore intero: 100
Valore floating-point: 99.99
```

---

### 4. **Unione per l'accesso a dati di basso livello (interpretazione dei bit)**

Le unioni possono essere utilizzate per accedere a diversi tipi di dati nello stesso spazio di memoria, il che è utile quando si lavora a livello di bit o si devono manipolare dati a basso livello.

#### Esempio 4: Interpretazione di bit con un'unione

```c
#include <stdio.h>

union Byte {
    unsigned char byte;
    struct {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
    } bitfield;
};

int main() {
    union Byte byteValue;
    byteValue.byte = 0b10101100;

    printf("Byte: 0x%X\n", byteValue.byte);
    printf("Bit0: %d\n", byteValue.bitfield.bit0);
    printf("Bit7: %d\n", byteValue.bitfield.bit7);

    return 0;
}
```

### Spiegazione:
- L'unione `Byte` permette di interpretare un byte sia come un singolo valore che come una serie di bit. Questo è utile quando è necessario manipolare direttamente i bit di un dato.

### Output:
```
Byte: 0xAC
Bit0: 0
Bit7: 1
```

