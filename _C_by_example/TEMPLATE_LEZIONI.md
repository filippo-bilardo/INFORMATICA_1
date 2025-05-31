# Template per Lezioni - C by Example

Questo documento fornisce un template standardizzato per creare nuove lezioni o aggiornare quelle esistenti nel corso "C by Example".

## Struttura Cartella Lezione

```
XX_Nome_Argomento/
├── README.md                 # File principale della lezione
├── teoria/                   # Materiale teorico approfondito
│   ├── 01_concetti_base.md
│   ├── 02_esempi_pratici.md
│   ├── 03_best_practices.md
│   └── 04_common_mistakes.md
├── esempi/                   # Codice di esempio commentato
│   ├── esempio_base.c
│   ├── esempio_avanzato.c
│   ├── Makefile
│   └── README.md
├── esercizi/                 # Esercizi da svolgere
│   ├── esercizio1.c          # Template con TODO
│   ├── esercizio2.c
│   ├── README.md             # Istruzioni esercizi
│   └── soluzioni/            # Soluzioni degli esercizi
│       ├── esercizio1_soluzione.c
│       └── esercizio2_soluzione.c
├── test/                     # Test automatici (opzionale)
│   ├── test_runner.c
│   ├── test_examples.sh
│   └── expected_output.txt
└── risorse/                  # Risorse aggiuntive
    ├── immagini/
    ├── diagrammi/
    └── riferimenti.md
```

## Template README.md per Lezione

```markdown
# Lezione XX: [Nome Argomento]

## 🎯 Obiettivi di Apprendimento

Al termine di questa lezione sarai in grado di:
- [ ] Obiettivo 1
- [ ] Obiettivo 2
- [ ] Obiettivo 3

## 📚 Prerequisiti

- Conoscenza di [argomenti precedenti]
- Completamento delle lezioni [numeri lezioni]

## ⏱️ Tempo Stimato

- **Teoria:** 45 minuti
- **Esempi:** 30 minuti
- **Esercizi:** 60 minuti
- **Totale:** ~2.5 ore

## 📖 Indice degli Argomenti Teorici

1. [Concetti Base](./teoria/01_concetti_base.md)
   - Introduzione all'argomento
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

### Esempio Base
```c
// Codice di esempio con commenti dettagliati
```

### Esempio Avanzato
```c
// Esempio più complesso che dimostra concetti avanzati
```

## 🔧 Esercizi Pratici

### Esercizio 1: [Nome Esercizio]
**Difficoltà:** 🟢 Principiante | 🟡 Intermedio | 🟠 Avanzato

**Descrizione:** Breve descrizione dell'esercizio

**File:** `esercizi/esercizio1.c`

### Esercizio 2: [Nome Esercizio]
**Difficoltà:** 🟡 Intermedio

**Descrizione:** Descrizione del secondo esercizio

**File:** `esercizi/esercizio2.c`

## ❓ Quiz di Autovalutazione

1. **Domanda teorica**
   - [ ] Opzione A
   - [ ] Opzione B
   - [x] Opzione C (corretta)
   - [ ] Opzione D

2. **Domanda pratica**
   ```c
   // Codice con errore
   ```
   Qual è l'errore nel codice sopra?

## 🔗 Collegamenti

**Lezioni Precedenti:**
- [Lezione XX-1: Nome](../XX-1_Nome/)

**Lezioni Successive:**
- [Lezione XX+1: Nome](../XX+1_Nome/)

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
```

## Template per File Teoria

```markdown
# [Titolo Argomento]

## Introduzione

Paragrafo introduttivo che spiega il concetto e perché è importante.

## Definizione

> **[Termine Tecnico]**: Definizione precisa del concetto

## Sintassi

```c
// Sintassi generale
tipo nome(parametri) {
    // implementazione
}
```

## Parametri

| Parametro | Tipo | Descrizione |
|-----------|------|-------------|
| param1    | int  | Descrizione del parametro |
| param2    | char*| Descrizione del parametro |

## Valore di Ritorno

Descrizione di cosa ritorna la funzione/operazione.

## Esempi

### Esempio Base
```c
// Codice semplice e ben commentato
#include <stdio.h>

int main() {
    // Spiegazione passo passo
    return 0;
}
```

**Output:**
```
Risultato atteso
```

### Esempio Avanzato
```c
// Esempio più complesso
```

## Best Practices

- ✅ **DO:** Cosa fare
- ❌ **DON'T:** Cosa non fare

## Errori Comuni

### Errore 1: [Nome Errore]
```c
// Codice errato
```
**Problema:** Spiegazione del problema

**Soluzione:**
```c
// Codice corretto
```

## Considerazioni sulla Performance

- Impatto sulla memoria
- Complessità temporale
- Ottimizzazioni possibili

## Riferimenti

- Standard C (ISO/IEC 9899)
- Libri di riferimento
- Documentazione online
```

## Template Makefile

```makefile
# Makefile per Lezione XX - Nome Argomento

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
LDFLAGS = 

# Directory
SRC_DIR = .
BUILD_DIR = build
EXAMPLES_DIR = esempi
EXERCISES_DIR = esercizi

# Target principali
.PHONY: all examples exercises clean test help

all: examples exercises

# Compila tutti gli esempi
examples:
	@echo "🔨 Compilando esempi..."
	@mkdir -p $(BUILD_DIR)
	@for file in $(EXAMPLES_DIR)/*.c; do \
		if [ -f "$$file" ]; then \
			echo "  - $$file"; \
			$(CC) $(CFLAGS) "$$file" -o $(BUILD_DIR)/$$(basename "$$file" .c); \
		fi \
	done

# Compila tutti gli esercizi
exercises:
	@echo "🔨 Compilando esercizi..."
	@mkdir -p $(BUILD_DIR)
	@for file in $(EXERCISES_DIR)/*.c; do \
		if [ -f "$$file" ]; then \
			echo "  - $$file"; \
			$(CC) $(CFLAGS) "$$file" -o $(BUILD_DIR)/$$(basename "$$file" .c); \
		fi \
	done

# Esegue i test
test:
	@echo "🧪 Eseguendo test..."
	@if [ -d "test" ]; then \
		cd test && bash test_runner.sh; \
	else \
		echo "Nessun test disponibile per questa lezione"; \
	fi

# Pulisce i file compilati
clean:
	@echo "🧹 Pulizia file compilati..."
	@rm -rf $(BUILD_DIR)

# Mostra help
help:
	@echo "📖 Comandi disponibili:"
	@echo "  make all       - Compila esempi ed esercizi"
	@echo "  make examples  - Compila solo gli esempi"
	@echo "  make exercises - Compila solo gli esercizi"
	@echo "  make test      - Esegue i test automatici"
	@echo "  make clean     - Rimuove i file compilati"
	@echo "  make help      - Mostra questo messaggio"
```

## Script di Test Template

```bash
#!/bin/bash
# test_runner.sh - Script per test automatici

echo "🧪 Inizio test per la lezione..."

PASSED=0
FAILED=0
BUILD_DIR="../build"

# Funzione per eseguire un test
run_test() {
    local test_name="$1"
    local executable="$2"
    local expected_output="$3"
    
    echo -n "🔍 Test: $test_name... "
    
    if [ ! -f "$BUILD_DIR/$executable" ]; then
        echo "❌ FALLITO (eseguibile non trovato)"
        ((FAILED++))
        return
    fi
    
    local actual_output
    actual_output=$("$BUILD_DIR/$executable" 2>&1)
    
    if [ "$actual_output" = "$expected_output" ]; then
        echo "✅ PASSATO"
        ((PASSED++))
    else
        echo "❌ FALLITO"
        echo "   Atteso: '$expected_output'"
        echo "   Ottenuto: '$actual_output'"
        ((FAILED++))
    fi
}

# Test per gli esempi
if [ -f "../esempi/esempio_base.c" ]; then
    run_test "Esempio Base" "esempio_base" "Output atteso"
fi

# Test per gli esercizi (se compilati)
if [ -f "../esercizi/soluzioni/esercizio1_soluzione.c" ]; then
    run_test "Esercizio 1" "esercizio1_soluzione" "Output esercizio 1"
fi

# Riepilogo
echo ""
echo "📊 Risultati test:"
echo "  ✅ Passati: $PASSED"
echo "  ❌ Falliti: $FAILED"
echo "  📈 Totali: $((PASSED + FAILED))"

if [ $FAILED -eq 0 ]; then
    echo "🎉 Tutti i test sono passati!"
    exit 0
else
    echo "⚠️  Alcuni test sono falliti"
    exit 1
fi
```

Questo template fornisce una struttura standardizzata che può essere utilizzata per:

1. **Uniformare** tutte le lezioni del corso
2. **Migliorare** l'esperienza di apprendimento
3. **Automatizzare** la compilazione e i test
4. **Facilitare** la manutenzione del corso

Ogni nuovo argomento può essere sviluppato seguendo questo template, garantendo coerenza e qualità in tutto il corso.
