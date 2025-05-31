/*
 * ===============================================
 * ESEMPIO: Cicli Numerici
 * ===============================================
 * 
 * Questo programma dimostra l'uso dei diversi
 * tipi di cicli per elaborazioni numeriche,
 * calcoli matematici e algoritmi iterativi.
 * 
 * CONCETTI DIMOSTRATI:
 * - Cicli for con contatori
 * - Cicli while con condizioni
 * - Cicli do-while per validazione
 * - Cicli annidati (nested loops)
 * - Controllo flusso con break/continue
 * - Algoritmi numerici classici
 * - Ottimizzazione e performance
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// ===== PROTOTIPI FUNZIONI =====
void esempio_ciclo_for_base(void);
void esempio_ciclo_while(void);
void esempio_ciclo_do_while(void);
void esempio_cicli_annidati(void);
void esempio_break_continue(void);
void esempio_algoritmi_numerici(void);
void esempio_performance_cicli(void);

void calcola_fattoriale(void);
void calcola_fibonacci(void);
void trova_numeri_primi(void);
void calcola_pi_greco(void);
void analizza_sequenza_numeri(void);
void gioco_matematico(void);

void stampa_separatore(const char* titolo);
void stampa_barra_progresso(int attuale, int totale);
bool is_primo(int n);
double cronometra_esecuzione(void (*funzione)(void));

// ===== FUNZIONE PRINCIPALE =====
int main() {
    printf("🔢 ESEMPI: Cicli Numerici e Algoritmi\n");
    printf("=====================================\n\n");
    
    srand(time(NULL));
    
    // Esempi progressivi dei cicli
    esempio_ciclo_for_base();
    esempio_ciclo_while();
    esempio_ciclo_do_while();
    esempio_cicli_annidati();
    esempio_break_continue();
    esempio_algoritmi_numerici();
    esempio_performance_cicli();
    
    printf("🎉 Esempi completati! Ora conosci tutti i tipi di cicli in C.\n");
    return 0;
}

// ===== ESEMPI BASE DEI CICLI =====

/**
 * Dimostra l'uso del ciclo for con diverse varianti
 */
void esempio_ciclo_for_base(void) {
    stampa_separatore("CICLI FOR - ESEMPI BASE");
    
    // Ciclo for classico - conteggio crescente
    printf("🔢 Conteggio da 1 a 10:\n");
    for (int i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // Ciclo for decrescente
    printf("⬇️ Countdown da 10 a 1:\n");
    for (int i = 10; i >= 1; i--) {
        printf("%d ", i);
        if (i == 1) printf("🚀 Partenza!\n");
    }
    printf("\n");
    
    // Ciclo for con step personalizzato
    printf("⚡ Numeri pari da 0 a 20:\n");
    for (int i = 0; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // Ciclo for con calcoli
    printf("🧮 Tabellina del 7:\n");
    for (int i = 1; i <= 10; i++) {
        printf("7 × %2d = %2d\n", i, 7 * i);
    }
    printf("\n");
    
    // Ciclo for per somme
    int somma = 0;
    printf("📊 Somma dei primi 100 numeri naturali:\n");
    for (int i = 1; i <= 100; i++) {
        somma += i;
    }
    printf("Risultato: 1 + 2 + 3 + ... + 100 = %d\n", somma);
    printf("📐 Formula di Gauss: n(n+1)/2 = %d\n\n", (100 * 101) / 2);
}

/**
 * Dimostra l'uso del ciclo while
 */
void esempio_ciclo_while(void) {
    stampa_separatore("CICLI WHILE - CONDIZIONI DINAMICHE");
    
    // While per dimezzamenti successivi
    printf("➗ Dimezzamenti successivi di 1000:\n");
    double numero = 1000.0;
    int iterazioni = 0;
    
    while (numero > 1.0) {
        printf("Iterazione %d: %.2f\n", ++iterazioni, numero);
        numero /= 2.0;
    }
    printf("Valore finale: %.6f (dopo %d iterazioni)\n\n", numero, iterazioni);
    
    // While per approssimazione
    printf("🎯 Approssimazione della radice quadrata di 50:\n");
    double target = 50.0;
    double guess = target / 2.0;  // Prima approssimazione
    double precisione = 0.0001;
    int passi = 0;
    
    while (fabs(guess * guess - target) > precisione) {
        guess = (guess + target / guess) / 2.0;  // Metodo di Newton
        passi++;
        printf("Passo %d: %.6f (errore: %.6f)\n", 
               passi, guess, fabs(guess * guess - target));
    }
    printf("🎉 Radice trovata: %.6f (√50 ≈ %.6f)\n\n", guess, sqrt(50));
    
    // While per generazione numeri casuali
    printf("🎲 Generazione numeri fino ad ottenere un 6:\n");
    int dado;
    int lanci = 0;
    
    while ((dado = rand() % 6 + 1) != 6) {
        printf("Lancio %d: %d\n", ++lanci, dado);
    }
    printf("🎯 Finalmente un 6! (dopo %d lanci)\n\n", lanci + 1);
}

/**
 * Dimostra l'uso del ciclo do-while
 */
void esempio_ciclo_do_while(void) {
    stampa_separatore("CICLI DO-WHILE - ESECUZIONE GARANTITA");
    
    // Do-while per validazione input (simulata)
    printf("🔒 Simulazione validazione password:\n");
    char passwords[][20] = {"123", "password", "admin", "secret", "12345"};
    char* password_corretta = "secret";
    int tentativi = 0;
    int indice_tentativo;
    
    do {
        indice_tentativo = rand() % 5;
        tentativi++;
        printf("Tentativo %d: '%s' - ", tentativi, passwords[indice_tentativo]);
        
        if (strcmp(passwords[indice_tentativo], password_corretta) == 0) {
            printf("✅ Accesso consentito!\n");
            break;
        } else {
            printf("❌ Password errata\n");
        }
    } while (tentativi < 3);
    
    if (tentativi >= 3 && strcmp(passwords[indice_tentativo], password_corretta) != 0) {
        printf("🔒 Accesso bloccato dopo 3 tentativi!\n");
    }
    printf("\n");
    
    // Do-while per menu semplice
    printf("📋 Simulazione menu con do-while:\n");
    int scelta;
    int iterazione = 0;
    
    do {
        iterazione++;
        scelta = rand() % 5;  // Simula scelta utente
        
        printf("Iterazione %d - Scelta simulata: %d\n", iterazione, scelta);
        
        switch (scelta) {
            case 1:
                printf("   ➤ Opzione 1 eseguita\n");
                break;
            case 2:
                printf("   ➤ Opzione 2 eseguita\n");
                break;
            case 3:
                printf("   ➤ Opzione 3 eseguita\n");
                break;
            case 0:
                printf("   ➤ Uscita dal menu\n");
                break;
            default:
                printf("   ➤ Opzione non valida\n");
                break;
        }
    } while (scelta != 0 && iterazione < 5);
    
    printf("\n");
}

/**
 * Dimostra l'uso di cicli annidati
 */
void esempio_cicli_annidati(void) {
    stampa_separatore("CICLI ANNIDATI - STRUTTURE COMPLESSE");
    
    // Tabella di moltiplicazione
    printf("📊 Tabella di moltiplicazione (1-5):\n");
    printf("    ");
    for (int j = 1; j <= 5; j++) {
        printf("%4d", j);
    }
    printf("\n");
    
    for (int i = 1; i <= 5; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= 5; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }
    printf("\n");
    
    // Triangolo di asterischi
    printf("⭐ Triangolo di asterischi:\n");
    for (int i = 1; i <= 7; i++) {
        // Spazi iniziali per centrare
        for (int j = 0; j < 7 - i; j++) {
            printf(" ");
        }
        // Asterischi
        for (int j = 0; j < i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");
    
    // Matrice con pattern
    printf("🎨 Matrice con pattern:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 0) {
                printf("■ ");
            } else {
                printf("□ ");
            }
        }
        printf("\n");
    }
    printf("\n");
    
    // Ricerca in matrice
    printf("🔍 Ricerca elemento in matrice 4x4:\n");
    int matrice[4][4];
    int target = 42;
    bool trovato = false;
    int pos_i = -1, pos_j = -1;
    
    // Riempi matrice con numeri casuali
    printf("Matrice generata:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrice[i][j] = rand() % 100;
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Inserisci il target in una posizione casuale
    int rand_i = rand() % 4;
    int rand_j = rand() % 4;
    matrice[rand_i][rand_j] = target;
    
    printf("\nMatrice modificata (inserito %d):\n", target);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Ricerca elemento
    printf("\n🔍 Ricerca elemento %d:\n", target);
    for (int i = 0; i < 4 && !trovato; i++) {
        for (int j = 0; j < 4; j++) {
            printf("Controllo posizione [%d,%d]: %d... ", i, j, matrice[i][j]);
            if (matrice[i][j] == target) {
                trovato = true;
                pos_i = i;
                pos_j = j;
                printf("✅ TROVATO!\n");
                break;
            } else {
                printf("❌\n");
            }
        }
    }
    
    if (trovato) {
        printf("🎯 Elemento %d trovato in posizione [%d,%d]\n", target, pos_i, pos_j);
    }
    
    printf("\n");
}

/**
 * Dimostra l'uso di break e continue
 */
void esempio_break_continue(void) {
    stampa_separatore("CONTROLLO FLUSSO - BREAK E CONTINUE");
    
    // Esempio con break
    printf("🛑 Ricerca primo numero divisibile per 17 tra 100-200:\n");
    for (int i = 100; i <= 200; i++) {
        printf("Controllo %d... ", i);
        if (i % 17 == 0) {
            printf("✅ Trovato! %d è divisibile per 17\n", i);
            break;  // Esce dal ciclo
        } else {
            printf("❌\n");
        }
    }
    printf("\n");
    
    // Esempio con continue
    printf("⏭️ Numeri da 1 a 20, saltando i multipli di 3:\n");
    for (int i = 1; i <= 20; i++) {
        if (i % 3 == 0) {
            continue;  // Salta il resto dell'iterazione
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // Esempio combinato break e continue
    printf("🎯 Elaborazione numeri con condizioni speciali:\n");
    int elaborati = 0;
    int saltati = 0;
    
    for (int i = 1; i <= 50; i++) {
        // Salta numeri pari
        if (i % 2 == 0) {
            saltati++;
            continue;
        }
        
        // Ferma se trova un numero > 30 divisibile per 7
        if (i > 30 && i % 7 == 0) {
            printf("🛑 Fermato al numero %d (>30 e divisibile per 7)\n", i);
            break;
        }
        
        printf("Elaborato: %d\n", i);
        elaborati++;
    }
    
    printf("📊 Statistiche: %d elaborati, %d saltati\n\n", elaborati, saltati);
    
    // Break e continue in cicli annidati
    printf("🔄 Break e continue in cicli annidati:\n");
    for (int i = 1; i <= 5; i++) {
        printf("Gruppo %d: ", i);
        
        for (int j = 1; j <= 10; j++) {
            if (j % 3 == 0) {
                continue;  // Salta multipli di 3
            }
            
            if (j > 7) {
                break;  // Esce dal ciclo interno
            }
            
            printf("%d ", j);
        }
        printf("\n");
    }
    
    printf("\n");
}

/**
 * Dimostra algoritmi numerici classici
 */
void esempio_algoritmi_numerici(void) {
    stampa_separatore("ALGORITMI NUMERICI CLASSICI");
    
    calcola_fattoriale();
    calcola_fibonacci();
    trova_numeri_primi();
    calcola_pi_greco();
    analizza_sequenza_numeri();
    
    printf("\n");
}

/**
 * Calcola fattoriali con diverse implementazioni
 */
void calcola_fattoriale(void) {
    printf("🔢 CALCOLO FATTORIALI:\n");
    
    int numeri[] = {5, 8, 10, 12};
    int count = sizeof(numeri) / sizeof(numeri[0]);
    
    for (int k = 0; k < count; k++) {
        int n = numeri[k];
        long long fattoriale = 1;
        
        printf("%d! = ", n);
        
        // Calcolo iterativo
        for (int i = 1; i <= n; i++) {
            fattoriale *= i;
            printf("%d", i);
            if (i < n) printf(" × ");
        }
        
        printf(" = %lld\n", fattoriale);
    }
    printf("\n");
}

/**
 * Genera sequenza di Fibonacci
 */
void calcola_fibonacci(void) {
    printf("🌀 SEQUENZA DI FIBONACCI:\n");
    printf("I primi 15 numeri di Fibonacci:\n");
    
    long long a = 0, b = 1, c;
    printf("F(0) = %lld\n", a);
    printf("F(1) = %lld\n", b);
    
    for (int i = 2; i < 15; i++) {
        c = a + b;
        printf("F(%d) = %lld\n", i, c);
        a = b;
        b = c;
    }
    
    // Rapporto aureo approssimato
    double rapporto = (double)b / a;
    printf("\n📐 Rapporto aureo approssimato: %.6f\n", rapporto);
    printf("📐 Rapporto aureo matematico: %.6f\n\n", (1.0 + sqrt(5)) / 2.0);
}

/**
 * Trova numeri primi con crivello
 */
void trova_numeri_primi(void) {
    printf("🔍 NUMERI PRIMI FINO A 100:\n");
    
    int limite = 100;
    bool primi[101];  // Array per marcare i primi
    
    // Inizializza tutti come primi
    for (int i = 0; i <= limite; i++) {
        primi[i] = true;
    }
    
    primi[0] = primi[1] = false;  // 0 e 1 non sono primi
    
    // Crivello di Eratostene
    for (int i = 2; i * i <= limite; i++) {
        if (primi[i]) {
            // Marca tutti i multipli di i come non primi
            for (int j = i * i; j <= limite; j += i) {
                primi[j] = false;
            }
        }
    }
    
    // Stampa i primi trovati
    int contatore = 0;
    for (int i = 2; i <= limite; i++) {
        if (primi[i]) {
            printf("%3d ", i);
            contatore++;
            if (contatore % 10 == 0) printf("\n");
        }
    }
    
    printf("\n📊 Totale numeri primi fino a %d: %d\n\n", limite, contatore);
}

/**
 * Calcola π con metodo di Leibniz
 */
void calcola_pi_greco(void) {
    printf("🥧 CALCOLO DI π (Pi Greco):\n");
    printf("Metodo di Leibniz: π/4 = 1 - 1/3 + 1/5 - 1/7 + ...\n\n");
    
    double pi_approssimato = 0.0;
    int iterazioni[] = {100, 1000, 10000, 100000};
    int count = sizeof(iterazioni) / sizeof(iterazioni[0]);
    
    for (int k = 0; k < count; k++) {
        pi_approssimato = 0.0;
        int n = iterazioni[k];
        
        for (int i = 0; i < n; i++) {
            double termine = 1.0 / (2 * i + 1);
            if (i % 2 == 0) {
                pi_approssimato += termine;
            } else {
                pi_approssimato -= termine;
            }
        }
        
        pi_approssimato *= 4;  // Moltiplica per 4
        
        printf("Con %6d iterazioni: π ≈ %.10f (errore: %.10f)\n", 
               n, pi_approssimato, fabs(M_PI - pi_approssimato));
    }
    
    printf("Valore matematico:      π = %.10f\n\n", M_PI);
}

/**
 * Analizza una sequenza di numeri
 */
void analizza_sequenza_numeri(void) {
    printf("📊 ANALISI SEQUENZA NUMERICA:\n");
    
    // Genera sequenza casuale
    int sequenza[20];
    printf("Sequenza generata: ");
    for (int i = 0; i < 20; i++) {
        sequenza[i] = rand() % 100 + 1;
        printf("%d ", sequenza[i]);
    }
    printf("\n\n");
    
    // Calcola statistiche
    int somma = 0;
    int massimo = sequenza[0];
    int minimo = sequenza[0];
    int posizione_max = 0, posizione_min = 0;
    
    for (int i = 0; i < 20; i++) {
        somma += sequenza[i];
        
        if (sequenza[i] > massimo) {
            massimo = sequenza[i];
            posizione_max = i;
        }
        
        if (sequenza[i] < minimo) {
            minimo = sequenza[i];
            posizione_min = i;
        }
    }
    
    double media = (double)somma / 20;
    
    printf("📈 Statistiche:\n");
    printf("   • Somma: %d\n", somma);
    printf("   • Media: %.2f\n", media);
    printf("   • Massimo: %d (posizione %d)\n", massimo, posizione_max);
    printf("   • Minimo: %d (posizione %d)\n", minimo, posizione_min);
    
    // Conta elementi sopra/sotto media
    int sopra_media = 0, sotto_media = 0;
    for (int i = 0; i < 20; i++) {
        if (sequenza[i] > media) {
            sopra_media++;
        } else if (sequenza[i] < media) {
            sotto_media++;
        }
    }
    
    printf("   • Sopra media: %d elementi\n", sopra_media);
    printf("   • Sotto media: %d elementi\n", sotto_media);
    
    printf("\n");
}

/**
 * Dimostra considerazioni di performance
 */
void esempio_performance_cicli(void) {
    stampa_separatore("PERFORMANCE E OTTIMIZZAZIONE");
    
    printf("⚡ Confronto performance diversi approcci:\n\n");
    
    // Test 1: Calcolo somma con for vs while
    printf("🔄 Test 1: Somma primi 1.000.000 numeri\n");
    
    clock_t start, end;
    long long somma;
    
    // Approccio con for
    start = clock();
    somma = 0;
    for (int i = 1; i <= 1000000; i++) {
        somma += i;
    }
    end = clock();
    double tempo_for = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("   For loop: Somma = %lld, Tempo = %.6f secondi\n", somma, tempo_for);
    
    // Approccio con while
    start = clock();
    somma = 0;
    int i = 1;
    while (i <= 1000000) {
        somma += i;
        i++;
    }
    end = clock();
    double tempo_while = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("   While loop: Somma = %lld, Tempo = %.6f secondi\n", somma, tempo_while);
    
    // Formula matematica
    start = clock();
    somma = (long long)1000000 * 1000001 / 2;
    end = clock();
    double tempo_formula = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("   Formula Gauss: Somma = %lld, Tempo = %.6f secondi\n", somma, tempo_formula);
    
    printf("\n💡 La formula matematica è circa %.0fx più veloce!\n\n", 
           tempo_for / tempo_formula);
    
    // Test 2: Cicli annidati vs. ottimizzati
    printf("🔄 Test 2: Moltiplicazione matrici 200x200\n");
    printf("   (Simulazione con contatori per semplicità)\n");
    
    start = clock();
    long long operazioni = 0;
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            for (int k = 0; k < 200; k++) {
                operazioni++;  // Simula moltiplicazione
            }
        }
    }
    end = clock();
    double tempo_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("   Approccio base: %lld operazioni in %.6f secondi\n", 
           operazioni, tempo_naive);
    
    // Versione con ottimizzazioni minori
    start = clock();
    operazioni = 0;
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            int temp = 200;  // Evita calcolo ripetuto
            for (int k = 0; k < temp; k++) {
                operazioni++;
            }
        }
    }
    end = clock();
    double tempo_ottimizzato = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("   Approccio ottimizzato: %lld operazioni in %.6f secondi\n", 
           operazioni, tempo_ottimizzato);
    
    if (tempo_ottimizzato < tempo_naive) {
        printf("   💚 Miglioramento: %.2f%% più veloce\n", 
               ((tempo_naive - tempo_ottimizzato) / tempo_naive) * 100);
    }
    
    printf("\n");
}

// ===== FUNZIONI UTILITY =====

/**
 * Stampa separatore con titolo
 */
void stampa_separatore(const char* titolo) {
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("🔹 %s\n", titolo);
    printf("═══════════════════════════════════════════════════════════════\n");
}

/**
 * Stampa barra di progresso
 */
void stampa_barra_progresso(int attuale, int totale) {
    int larghezza = 30;
    int progresso = (attuale * larghezza) / totale;
    
    printf("\r[");
    for (int i = 0; i < progresso; i++) {
        printf("█");
    }
    for (int i = progresso; i < larghezza; i++) {
        printf("░");
    }
    printf("] %d/%d (%.1f%%)", attuale, totale, (float)attuale * 100 / totale);
    fflush(stdout);
}

/**
 * Verifica se un numero è primo
 */
bool is_primo(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
