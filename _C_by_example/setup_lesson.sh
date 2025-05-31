#!/bin/bash
# setup_lesson.sh - Script per configurare una nuova lezione o aggiornare una esistente

set -e

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Funzione per stampare messaggi colorati
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Funzione di help
show_help() {
    echo "📚 Setup Script per Lezioni C by Example"
    echo ""
    echo "Uso: $0 [OPZIONI] NUMERO_LEZIONE NOME_LEZIONE"
    echo ""
    echo "Opzioni:"
    echo "  -n, --new      Crea una nuova lezione da zero"
    echo "  -u, --update   Aggiorna una lezione esistente"
    echo "  -t, --template Copia solo i template senza contenuto"
    echo "  -h, --help     Mostra questo messaggio"
    echo ""
    echo "Esempi:"
    echo "  $0 -n 05 Funzioni"
    echo "  $0 -u 01 Introduzione"
    echo "  $0 -t 08 Puntatori"
}

# Variabili
MODE=""
LESSON_NUM=""
LESSON_NAME=""
LESSON_DIR=""

# Parse degli argomenti
while [[ $# -gt 0 ]]; do
    case $1 in
        -n|--new)
            MODE="new"
            shift
            ;;
        -u|--update)
            MODE="update"
            shift
            ;;
        -t|--template)
            MODE="template"
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            if [ -z "$LESSON_NUM" ]; then
                LESSON_NUM="$1"
            elif [ -z "$LESSON_NAME" ]; then
                LESSON_NAME="$1"
            else
                print_error "Troppi argomenti"
                show_help
                exit 1
            fi
            shift
            ;;
    esac
done

# Validazione argomenti
if [ -z "$MODE" ]; then
    print_error "Specificare una modalità (-n, -u, o -t)"
    show_help
    exit 1
fi

if [ -z "$LESSON_NUM" ] || [ -z "$LESSON_NAME" ]; then
    print_error "Specificare numero e nome della lezione"
    show_help
    exit 1
fi

# Formatta il numero della lezione (aggiungi zero se necessario)
LESSON_NUM=$(printf "%02d" "$LESSON_NUM")
LESSON_DIR="${LESSON_NUM}_${LESSON_NAME}"

print_status "Configurazione lezione: $LESSON_DIR"

# Funzione per creare la struttura delle cartelle
create_structure() {
    local base_dir="$1"
    
    print_status "Creando struttura cartelle..."
    
    mkdir -p "$base_dir"/{teoria,esempi,esercizi/soluzioni,test,risorse/{immagini,diagrammi}}
    
    print_success "Struttura cartelle creata"
}

# Funzione per creare il README principale
create_main_readme() {
    local base_dir="$1"
    local lesson_num="$2"
    local lesson_name="$3"
    
    cat > "$base_dir/README.md" << EOF
# Lezione $lesson_num: $lesson_name

## 🎯 Obiettivi di Apprendimento

Al termine di questa lezione sarai in grado di:
- [ ] Obiettivo 1 - da definire
- [ ] Obiettivo 2 - da definire
- [ ] Obiettivo 3 - da definire

## 📚 Prerequisiti

- Conoscenza di [argomenti precedenti]
- Completamento delle lezioni [numeri lezioni precedenti]

## ⏱️ Tempo Stimato

- **Teoria:** 45 minuti
- **Esempi:** 30 minuti
- **Esercizi:** 60 minuti
- **Totale:** ~2.5 ore

## 📖 Indice degli Argomenti Teorici

1. [Concetti Base](./teoria/01_concetti_base.md)
   - Introduzione a $lesson_name
   - Definizioni e terminologia
   
2. [Esempi Pratici](./teoria/02_esempi_pratici.md)
   - Applicazioni comuni
   - Casi d'uso reali
   
3. [Best Practices](./teoria/03_best_practices.md)
   - Linee guida per un codice pulito
   - Pattern consigliati
   
4. [Errori Comuni](./teoria/04_common_mistakes.md)
   - Problemi frequenti
   - Come evitarli

## 💻 Esempi di Codice

I file di esempio si trovano nella cartella \`esempi/\`. Per compilarli:

\`\`\`bash
cd esempi/
make all
\`\`\`

## 🔧 Esercizi Pratici

### Esercizio 1: [Nome Esercizio]
**Difficoltà:** 🟢 Principiante

**Descrizione:** Descrizione dell'esercizio da completare

**File:** \`esercizi/esercizio1.c\`

### Esercizio 2: [Nome Esercizio]
**Difficoltà:** 🟡 Intermedio

**Descrizione:** Descrizione del secondo esercizio

**File:** \`esercizi/esercizio2.c\`

## ❓ Quiz di Autovalutazione

1. **Domanda teorica su $lesson_name**
   - [ ] Opzione A
   - [ ] Opzione B
   - [x] Opzione C (corretta)
   - [ ] Opzione D

2. **Domanda pratica**
   \`\`\`c
   // Codice con problema da identificare
   \`\`\`
   Qual è il problema nel codice sopra?

## 🔗 Collegamenti

**Lezioni Precedenti:**
$([ "$lesson_num" -gt 1 ] && echo "- [Lezione $(printf "%02d" $((10#$lesson_num - 1))): Nome](../$(printf "%02d" $((10#$lesson_num - 1)))_Nome/)" || echo "- Questa è la prima lezione")

**Lezioni Successive:**
- [Lezione $(printf "%02d" $((10#$lesson_num + 1))): Nome](../$(printf "%02d" $((10#$lesson_num + 1)))_Nome/)

**Risorse Esterne:**
- [Documentazione ufficiale](link)
- [Tutorial approfondito](link)

## 📝 Note Aggiuntive

- Suggerimenti per chi ha difficoltà
- Approfondimenti per chi vuole saperne di più
- Riferimenti a materiale esterno

## ✅ Checklist di Completamento

- [ ] Ho letto tutto il materiale teorico
- [ ] Ho eseguito tutti gli esempi
- [ ] Ho completato tutti gli esercizi
- [ ] Ho superato il quiz di autovalutazione
- [ ] Ho verificato la mia comprensione
EOF

    print_success "README principale creato"
}

# Funzione per creare i file teorici
create_theory_files() {
    local base_dir="$1"
    local lesson_name="$2"
    
    # File 1: Concetti Base
    cat > "$base_dir/teoria/01_concetti_base.md" << EOF
# Concetti Base di $lesson_name

## Introduzione

Paragrafo introduttivo che spiega il concetto e perché è importante nel contesto della programmazione C.

## Definizione

> **$lesson_name**: Definizione precisa del concetto

## Sintassi

\`\`\`c
// Sintassi generale
tipo nome(parametri) {
    // implementazione
}
\`\`\`

## Esempi Introduttivi

### Esempio Semplice
\`\`\`c
#include <stdio.h>

int main() {
    // Codice di esempio per $lesson_name
    printf("Esempio di $lesson_name\\n");
    return 0;
}
\`\`\`

## Punti Chiave

- Punto importante 1
- Punto importante 2
- Punto importante 3

## Prossimi Passi

In questo capitolo hai imparato i concetti base. Nel prossimo approfondiremo gli esempi pratici.
EOF

    # File 2: Esempi Pratici
    cat > "$base_dir/teoria/02_esempi_pratici.md" << EOF
# Esempi Pratici di $lesson_name

## Casi d'Uso Comuni

### Caso d'Uso 1: [Nome Caso]
Descrizione del primo caso d'uso pratico.

\`\`\`c
// Esempio pratico 1
\`\`\`

### Caso d'Uso 2: [Nome Caso]
Descrizione del secondo caso d'uso.

\`\`\`c
// Esempio pratico 2
\`\`\`

## Applicazioni nel Mondo Reale

- Applicazione 1
- Applicazione 2
- Applicazione 3

## Esercizi di Consolidamento

1. Modifica l'esempio 1 per...
2. Crea una variante dell'esempio 2 che...
3. Combina i concetti degli esempi per...
EOF

    # File 3: Best Practices
    cat > "$base_dir/teoria/03_best_practices.md" << EOF
# Best Practices per $lesson_name

## Linee Guida Generali

### ✅ Cosa Fare

- **Regola 1**: Spiegazione della regola
- **Regola 2**: Spiegazione della regola
- **Regola 3**: Spiegazione della regola

### ❌ Cosa Evitare

- **Anti-pattern 1**: Perché evitarlo
- **Anti-pattern 2**: Perché evitarlo
- **Anti-pattern 3**: Perché evitarlo

## Esempi di Codice Pulito

### Esempio Corretto
\`\`\`c
// Codice che segue le best practices
\`\`\`

### Esempio da Evitare
\`\`\`c
// Codice che non segue le best practices
\`\`\`

## Checklist di Qualità

- [ ] Il codice è leggibile?
- [ ] Le variabili hanno nomi significativi?
- [ ] La logica è chiara?
- [ ] Ci sono commenti appropriati?
EOF

    # File 4: Errori Comuni
    cat > "$base_dir/teoria/04_common_mistakes.md" << EOF
# Errori Comuni con $lesson_name

## Errore 1: [Nome Errore]

### Descrizione
Descrizione dettagliata dell'errore.

### Codice Errato
\`\`\`c
// Esempio di codice che contiene l'errore
\`\`\`

### Problema
Spiegazione di cosa non va nel codice.

### Soluzione
\`\`\`c
// Codice corretto
\`\`\`

### Come Evitarlo
- Suggerimento 1
- Suggerimento 2

## Errore 2: [Nome Errore]

### Descrizione
Descrizione del secondo errore comune.

### Codice Errato
\`\`\`c
// Altro esempio di errore
\`\`\`

### Soluzione
\`\`\`c
// Codice corretto
\`\`\`

## Debug Tips

- **Tip 1**: Come identificare questo tipo di errori
- **Tip 2**: Strumenti utili per il debugging
- **Tip 3**: Tecniche di prevenzione
EOF

    print_success "File teorici creati"
}

# Funzione per creare esempi e Makefile
create_examples() {
    local base_dir="$1"
    local lesson_name="$2"
    
    # Esempio base
    cat > "$base_dir/esempi/esempio_base.c" << EOF
/**
 * Esempio Base di $lesson_name
 * 
 * Questo esempio dimostra i concetti fondamentali di $lesson_name
 * in modo semplice e comprensibile.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Esempio Base di $lesson_name ===\\n");
    
    // TODO: Implementare esempio base
    printf("Questo è un esempio placeholder.\\n");
    printf("Implementare il codice specifico per $lesson_name\\n");
    
    return 0;
}
EOF

    # Esempio avanzato
    cat > "$base_dir/esempi/esempio_avanzato.c" << EOF
/**
 * Esempio Avanzato di $lesson_name
 * 
 * Questo esempio mostra un uso più complesso e realistico 
 * dei concetti di $lesson_name.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Esempio Avanzato di $lesson_name ===\\n");
    
    // TODO: Implementare esempio avanzato
    printf("Esempio avanzato placeholder.\\n");
    printf("Implementare funzionalità più complesse per $lesson_name\\n");
    
    return 0;
}
EOF

    # Makefile per esempi
    cat > "$base_dir/esempi/Makefile" << EOF
# Makefile per Esempi di $lesson_name

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
BUILD_DIR = build

# Lista degli esempi
EXAMPLES = esempio_base esempio_avanzato

.PHONY: all clean help

all: \$(EXAMPLES)

# Regola generica per compilare esempi
%: %.c
	@mkdir -p \$(BUILD_DIR)
	@echo "🔨 Compilando \$<..."
	\$(CC) \$(CFLAGS) \$< -o \$(BUILD_DIR)/\$@

clean:
	@echo "🧹 Pulizia file compilati..."
	@rm -rf \$(BUILD_DIR)

help:
	@echo "📖 Comandi disponibili:"
	@echo "  make all    - Compila tutti gli esempi"
	@echo "  make clean  - Rimuove i file compilati"
	@echo "  make help   - Mostra questo messaggio"
	@echo ""
	@echo "📁 Esempi disponibili:"
	@echo "  \$(EXAMPLES)"
EOF

    # README per esempi
    cat > "$base_dir/esempi/README.md" << EOF
# Esempi di $lesson_name

Questa cartella contiene esempi pratici per illustrare i concetti di $lesson_name.

## Come Compilare

\`\`\`bash
make all
\`\`\`

## Come Eseguire

\`\`\`bash
# Eseguire l'esempio base
./build/esempio_base

# Eseguire l'esempio avanzato
./build/esempio_avanzato
\`\`\`

## Esempi Inclusi

### esempio_base.c
Dimostra i concetti fondamentali di $lesson_name.

### esempio_avanzato.c
Mostra applicazioni più complesse e realistiche.

## Note

- Tutti gli esempi sono ampiamente commentati
- Modificare il codice per sperimentare
- Consultare la teoria per approfondimenti
EOF

    print_success "Esempi e Makefile creati"
}

# Funzione per creare esercizi
create_exercises() {
    local base_dir="$1"
    local lesson_name="$2"
    
    # Esercizio 1
    cat > "$base_dir/esercizi/esercizio1.c" << EOF
/**
 * Esercizio 1: Introduzione a $lesson_name
 * 
 * Difficoltà: 🟢 Principiante
 * 
 * Obiettivo: Implementare un esempio base che utilizza i concetti 
 *           fondamentali di $lesson_name.
 * 
 * Istruzioni:
 * 1. Completare le parti marcate con TODO
 * 2. Seguire i commenti per le indicazioni
 * 3. Testare il programma per verificare la correttezza
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Esercizio 1: $lesson_name ===\\n");
    
    // TODO: Implementare la soluzione dell'esercizio 1
    // Suggerimento: Iniziare con un caso semplice
    
    printf("TODO: Completare questo esercizio\\n");
    
    return 0;
}
EOF

    # Esercizio 2
    cat > "$base_dir/esercizi/esercizio2.c" << EOF
/**
 * Esercizio 2: Applicazione Pratica di $lesson_name
 * 
 * Difficoltà: 🟡 Intermedio
 * 
 * Obiettivo: Creare un'applicazione più complessa che integra
 *           i concetti di $lesson_name con quelli precedenti.
 * 
 * Istruzioni:
 * 1. Analizzare il problema descritto nei commenti
 * 2. Progettare una soluzione efficiente
 * 3. Implementare seguendo le best practices
 * 4. Testare con diversi casi d'uso
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Esercizio 2: $lesson_name Avanzato ===\\n");
    
    // TODO: Implementare la soluzione dell'esercizio 2
    // Questo esercizio richiede più ragionamento
    
    printf("TODO: Completare questo esercizio avanzato\\n");
    
    return 0;
}
EOF

    # README esercizi
    cat > "$base_dir/esercizi/README.md" << EOF
# Esercizi di $lesson_name

## 📋 Lista Esercizi

### Esercizio 1: Introduzione
- **File:** \`esercizio1.c\`
- **Difficoltà:** 🟢 Principiante
- **Tempo stimato:** 15-20 minuti
- **Obiettivo:** Familiarizzare con i concetti base

### Esercizio 2: Applicazione Pratica
- **File:** \`esercizio2.c\`
- **Difficoltà:** 🟡 Intermedio
- **Tempo stimato:** 30-40 minuti
- **Obiettivo:** Applicare i concetti in modo pratico

## 🔨 Come Procedere

1. **Leggi** attentamente i commenti nel codice
2. **Completa** le parti marcate con TODO
3. **Compila** usando: \`gcc -Wall -Wextra esercizio1.c -o esercizio1\`
4. **Testa** il programma con diversi input
5. **Confronta** con le soluzioni nella cartella \`soluzioni/\`

## 💡 Suggerimenti

- Non guardare le soluzioni subito
- Prova diversi approcci
- Usa il debugger se necessario
- Chiedi aiuto se sei bloccato per più di 30 minuti

## ✅ Criteri di Valutazione

- [ ] Il codice compila senza errori
- [ ] Il programma produce l'output corretto
- [ ] Il codice è leggibile e ben commentato
- [ ] Sono seguite le best practices
EOF

    print_success "Esercizi creati"
}

# Esecuzione principale
case $MODE in
    "new")
        if [ -d "$LESSON_DIR" ]; then
            print_warning "La cartella $LESSON_DIR esiste già"
            read -p "Vuoi sovrascriverla? (y/N): " -n 1 -r
            echo
            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                print_error "Operazione annullata"
                exit 1
            fi
            rm -rf "$LESSON_DIR"
        fi
        
        print_status "Creando nuova lezione: $LESSON_DIR"
        create_structure "$LESSON_DIR"
        create_main_readme "$LESSON_DIR" "$LESSON_NUM" "$LESSON_NAME"
        create_theory_files "$LESSON_DIR" "$LESSON_NAME"
        create_examples "$LESSON_DIR" "$LESSON_NAME"
        create_exercises "$LESSON_DIR" "$LESSON_NAME"
        print_success "Nuova lezione creata con successo!"
        ;;
        
    "update")
        if [ ! -d "$LESSON_DIR" ]; then
            print_error "La cartella $LESSON_DIR non esiste"
            exit 1
        fi
        
        print_status "Aggiornando lezione esistente: $LESSON_DIR"
        # Backup dei file esistenti
        backup_dir="${LESSON_DIR}_backup_$(date +%Y%m%d_%H%M%S)"
        cp -r "$LESSON_DIR" "$backup_dir"
        print_status "Backup creato in: $backup_dir"
        
        # Aggiorna solo i template senza sovrascrivere contenuto esistente
        if [ ! -f "$LESSON_DIR/esempi/Makefile" ]; then
            create_examples "$LESSON_DIR" "$LESSON_NAME"
        fi
        print_success "Lezione aggiornata!"
        ;;
        
    "template")
        print_status "Creando template per: $LESSON_DIR"
        create_structure "$LESSON_DIR"
        create_main_readme "$LESSON_DIR" "$LESSON_NUM" "$LESSON_NAME"
        print_success "Template creato!"
        ;;
esac

print_success "Operazione completata! 🎉"
print_status "Prossimi passi:"
echo "  1. Personalizza il contenuto nei file teorici"
echo "  2. Implementa gli esempi pratici"
echo "  3. Crea esercizi significativi"
echo "  4. Testa tutto il materiale"
