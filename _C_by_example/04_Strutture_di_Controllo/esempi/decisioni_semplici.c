/*
 * ===============================================
 * ESEMPIO: Decisioni Semplici con if-else
 * ===============================================
 * 
 * Questo programma dimostra l'uso delle strutture
 * condizionali fondamentali per prendere decisioni
 * basate su diverse condizioni.
 * 
 * CONCETTI DIMOSTRATI:
 * - if semplice
 * - if-else
 * - if-else if-else (catena)
 * - Operatore ternario
 * - switch-case
 * - Operatori logici nelle condizioni
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ===== PROTOTIPI FUNZIONI =====
void esempio_if_semplice(void);
void esempio_if_else(void);
void esempio_catena_if_else(void);
void esempio_operatore_ternario(void);
void esempio_switch_case(void);
void esempio_condizioni_complesse(void);
void stampa_separatore(const char* titolo);

// ===== FUNZIONE PRINCIPALE =====
int main() {
    printf("🔄 ESEMPI: Strutture di Controllo - Decisioni Semplici\n");
    printf("======================================================\n\n");
    
    // Inizializza generatore numeri casuali
    srand(time(NULL));
    
    // Esempi progressivi delle strutture condizionali
    esempio_if_semplice();
    esempio_if_else();
    esempio_catena_if_else();
    esempio_operatore_ternario();
    esempio_switch_case();
    esempio_condizioni_complesse();
    
    printf("🎉 Esempi completati! Ora sai usare le decisioni in C.\n");
    return 0;
}

// ===== IMPLEMENTAZIONE FUNZIONI =====

/**
 * Dimostra l'uso dell'if semplice
 */
void esempio_if_semplice(void) {
    stampa_separatore("IF SEMPLICE");
    
    int numero = rand() % 100 + 1;  // Numero casuale 1-100
    printf("🎲 Numero generato: %d\n", numero);
    
    // If semplice - esegue solo se condizione è vera
    if (numero > 50) {
        printf("✅ Il numero è maggiore di 50\n");
    }
    
    if (numero % 2 == 0) {
        printf("✅ Il numero è pari\n");
    }
    
    if (numero < 10) {
        printf("✅ Il numero ha una sola cifra\n");
    }
    
    printf("\n");
}

/**
 * Dimostra l'uso dell'if-else
 */
void esempio_if_else(void) {
    stampa_separatore("IF-ELSE");
    
    int eta = rand() % 80 + 1;  // Età casuale 1-80
    printf("👤 Età generata: %d anni\n", eta);
    
    // If-else binario
    if (eta >= 18) {
        printf("✅ Persona maggiorenne - può votare\n");
    } else {
        printf("❌ Persona minorenne - non può votare\n");
    }
    
    // Altro esempio if-else
    if (eta >= 65) {
        printf("👴 Età pensionabile\n");
    } else {
        printf("💼 Età lavorativa\n");
    }
    
    printf("\n");
}

/**
 * Dimostra la catena if-else if-else
 */
void esempio_catena_if_else(void) {
    stampa_separatore("CATENA IF-ELSE IF-ELSE");
    
    int voto = rand() % 101;  // Voto 0-100
    printf("📝 Voto esame: %d/100\n", voto);
    
    // Catena if-else if per classificare il voto
    if (voto >= 90) {
        printf("🌟 ECCELLENTE - Ottimo lavoro!\n");
    } else if (voto >= 80) {
        printf("😊 BUONO - Bravo!\n");
    } else if (voto >= 70) {
        printf("👍 DISCRETO - Bene!\n");
    } else if (voto >= 60) {
        printf("😐 SUFFICIENTE - Promosso\n");
    } else {
        printf("😞 INSUFFICIENTE - Riprova\n");
    }
    
    // Esempio con temperature
    float temperatura = (rand() % 60) - 10;  // Temperatura -10 a +49
    printf("🌡️  Temperatura: %.1f°C\n", temperatura);
    
    if (temperatura >= 30) {
        printf("🔥 Molto caldo - Accendi l'aria condizionata\n");
    } else if (temperatura >= 20) {
        printf("☀️ Piacevole - Perfetto per uscire\n");
    } else if (temperatura >= 10) {
        printf("🧥 Fresco - Metti una giacca\n");
    } else if (temperatura >= 0) {
        printf("❄️ Freddo - Vestiti pesante\n");
    } else {
        printf("🧊 Gelido - Rimani al caldo!\n");
    }
    
    printf("\n");
}

/**
 * Dimostra l'operatore ternario (? :)
 */
void esempio_operatore_ternario(void) {
    stampa_separatore("OPERATORE TERNARIO");
    
    int a = rand() % 100 + 1;
    int b = rand() % 100 + 1;
    
    printf("🔢 Numeri: a = %d, b = %d\n", a, b);
    
    // Operatore ternario per trovare il massimo
    int max = (a > b) ? a : b;
    printf("📊 Il maggiore è: %d\n", max);
    
    // Operatore ternario per parità
    printf("🔍 %d è %s\n", a, (a % 2 == 0) ? "pari" : "dispari");
    printf("🔍 %d è %s\n", b, (b % 2 == 0) ? "pari" : "dispari");
    
    // Operatore ternario per segno
    int numero = (rand() % 201) - 100;  // Numero -100 a +100
    printf("➕➖ %d è %s\n", numero, 
           (numero > 0) ? "positivo" : 
           (numero < 0) ? "negativo" : "zero");
    
    printf("\n");
}

/**
 * Dimostra l'uso dello switch-case
 */
void esempio_switch_case(void) {
    stampa_separatore("SWITCH-CASE");
    
    int giorno = rand() % 7 + 1;  // Giorno 1-7
    printf("📅 Giorno della settimana: %d\n", giorno);
    
    // Switch per giorni della settimana
    printf("📅 ");
    switch (giorno) {
        case 1:
            printf("Lunedì - Inizio settimana 💼\n");
            break;
        case 2:
            printf("Martedì - Ancora all'inizio 📚\n");
            break;
        case 3:
            printf("Mercoledì - Metà settimana ⚡\n");
            break;
        case 4:
            printf("Giovedì - Quasi weekend 😊\n");
            break;
        case 5:
            printf("Venerdì - Ultimo giorno! 🎉\n");
            break;
        case 6:
            printf("Sabato - Weekend! 🏖️\n");
            break;
        case 7:
            printf("Domenica - Relax 😴\n");
            break;
        default:
            printf("Giorno non valido ❌\n");
            break;
    }
    
    // Switch per operazioni matematiche
    char operatore;
    char operatori[] = {'+', '-', '*', '/', '%'};
    operatore = operatori[rand() % 5];
    
    int x = rand() % 20 + 1;
    int y = rand() % 10 + 1;
    
    printf("🧮 Operazione: %d %c %d = ", x, operatore, y);
    
    switch (operatore) {
        case '+':
            printf("%d\n", x + y);
            break;
        case '-':
            printf("%d\n", x - y);
            break;
        case '*':
            printf("%d\n", x * y);
            break;
        case '/':
            printf("%.2f\n", (float)x / y);
            break;
        case '%':
            printf("%d\n", x % y);
            break;
        default:
            printf("Operatore non supportato\n");
            break;
    }
    
    printf("\n");
}

/**
 * Dimostra condizioni complesse con operatori logici
 */
void esempio_condizioni_complesse(void) {
    stampa_separatore("CONDIZIONI COMPLESSE");
    
    int eta = rand() % 80 + 1;
    int reddito = rand() % 50000 + 10000;  // Reddito 10k-60k
    int anni_lavoro = rand() % 40;
    
    printf("👤 Profilo: %d anni, €%d reddito, %d anni lavoro\n", 
           eta, reddito, anni_lavoro);
    
    // Condizione complessa per prestito bancario
    if ((eta >= 25 && eta <= 65) && 
        (reddito >= 25000) && 
        (anni_lavoro >= 2)) {
        printf("✅ PRESTITO APPROVATO - Soddisfa tutti i criteri\n");
    } else {
        printf("❌ PRESTITO NEGATO - Non soddisfa i criteri:\n");
        
        if (eta < 25 || eta > 65) {
            printf("   • Età non nel range 25-65 anni\n");
        }
        if (reddito < 25000) {
            printf("   • Reddito insufficiente (minimo €25.000)\n");
        }
        if (anni_lavoro < 2) {
            printf("   • Esperienza lavorativa insufficiente (minimo 2 anni)\n");
        }
    }
    
    // Condizione per sconto fedeltà
    int acquisti = rand() % 50;
    int cliente_premium = rand() % 2;
    
    printf("\n🛒 Cliente: %d acquisti, %s\n", 
           acquisti, cliente_premium ? "Premium" : "Standard");
    
    if ((acquisti >= 10 && cliente_premium) || (acquisti >= 20)) {
        float sconto = cliente_premium ? 15.0 : 10.0;
        printf("🎁 SCONTO %.0f%% applicato!\n", sconto);
    } else {
        printf("💰 Nessuno sconto disponibile\n");
    }
    
    printf("\n");
}

/**
 * Stampa un separatore decorativo con titolo
 */
void stampa_separatore(const char* titolo) {
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🔹 %s\n", titolo);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}
