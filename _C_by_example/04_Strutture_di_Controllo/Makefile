# ================================================================
# MAKEFILE AUTOMATIZZATO - LEZIONE 04: STRUTTURE DI CONTROLLO
# ================================================================
# 
# Sistema di build completo per esempi, esercizi e soluzioni
# Caratteristiche:
# - Compilazione automatica con ottimizzazioni
# - Testing automatizzato con input predefiniti
# - Validazione codice e controllo errori
# - Benchmarking performance
# - Sistema di pulizia e manutenzione
# - Supporto debug e profiling
# - Generazione documentazione
#
# Autore: Sistema Educativo C by Example
# Data: Maggio 2025
# Versione: 2.0 - Sistema Professionale

# ==================== CONFIGURAZIONE ====================

# Compilatore e flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -pedantic
CFLAGS_DEBUG := $(CFLAGS) -g -O0 -DDEBUG
CFLAGS_RELEASE := $(CFLAGS) -O2 -DNDEBUG
CFLAGS_PROFILE := $(CFLAGS_DEBUG) -pg -fprofile-arcs -ftest-coverage
LDFLAGS := -lm

# Directory
ESEMPI_DIR := esempi
ESERCIZI_DIR := esercizi
SOLUZIONI_DIR := esercizi/soluzioni
BUILD_DIR := build
DOCS_DIR := docs
TESTS_DIR := tests

# File sorgenti
ESEMPI_SRC := $(wildcard $(ESEMPI_DIR)/*.c)
ESERCIZI_SRC := $(wildcard $(ESERCIZI_DIR)/*.c)
SOLUZIONI_SRC := $(wildcard $(SOLUZIONI_DIR)/*.c)

# Eseguibili
ESEMPI_BIN := $(ESEMPI_SRC:$(ESEMPI_DIR)/%.c=$(BUILD_DIR)/esempio_%)
ESERCIZI_BIN := $(ESERCIZI_SRC:$(ESERCIZI_DIR)/%.c=$(BUILD_DIR)/esercizio_%)
SOLUZIONI_BIN := $(SOLUZIONI_SRC:$(SOLUZIONI_DIR)/%.c=$(BUILD_DIR)/soluzione_%)

# Colori ANSI per output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[1;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[1;37m
RESET := \033[0m
BOLD := \033[1m

# ==================== TARGET PRINCIPALI ====================

.PHONY: all clean help esempi esercizi soluzioni test benchmark demo
.DEFAULT_GOAL := help

# Target di aiuto con descrizioni colorate
help:
	@echo "$(BOLD)$(CYAN)🏗️  SISTEMA BUILD LEZIONE 04 - STRUTTURE DI CONTROLLO$(RESET)"
	@echo "$(CYAN)════════════════════════════════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(BOLD)📋 TARGET PRINCIPALI:$(RESET)"
	@echo "  $(GREEN)all$(RESET)           - Compila tutti i file (esempi, esercizi, soluzioni)"
	@echo "  $(GREEN)esempi$(RESET)        - Compila solo gli esempi"
	@echo "  $(GREEN)esercizi$(RESET)      - Compila solo gli esercizi"
	@echo "  $(GREEN)soluzioni$(RESET)     - Compila solo le soluzioni"
	@echo ""
	@echo "$(BOLD)🧪 TESTING E VALIDAZIONE:$(RESET)"
	@echo "  $(YELLOW)test$(RESET)          - Esegue tutti i test automatici"
	@echo "  $(YELLOW)test-esempi$(RESET)   - Testa solo gli esempi"
	@echo "  $(YELLOW)test-soluzioni$(RESET) - Testa solo le soluzioni"
	@echo "  $(YELLOW)validate$(RESET)      - Validazione completa del codice"
	@echo ""
	@echo "$(BOLD)⚡ PERFORMANCE E DEBUG:$(RESET)"
	@echo "  $(MAGENTA)benchmark$(RESET)     - Benchmark performance delle soluzioni"
	@echo "  $(MAGENTA)profile$(RESET)       - Compila con profiling abilitato"
	@echo "  $(MAGENTA)debug$(RESET)         - Compila versione debug"
	@echo "  $(MAGENTA)memory-check$(RESET)  - Controllo memory leaks con Valgrind"
	@echo ""
	@echo "$(BOLD)🎮 DEMO E PRESENTAZIONE:$(RESET)"
	@echo "  $(BLUE)demo$(RESET)          - Esegue demo interattiva di tutte le soluzioni"
	@echo "  $(BLUE)demo-auto$(RESET)     - Demo automatica con input predefiniti"
	@echo "  $(BLUE)showcase$(RESET)      - Presentazione completa delle funzionalità"
	@echo ""
	@echo "$(BOLD)📚 DOCUMENTAZIONE:$(RESET)"
	@echo "  $(WHITE)docs$(RESET)          - Genera documentazione HTML"
	@echo "  $(WHITE)coverage$(RESET)      - Report copertura codice"
	@echo "  $(WHITE)stats$(RESET)         - Statistiche del progetto"
	@echo ""
	@echo "$(BOLD)🧹 MANUTENZIONE:$(RESET)"
	@echo "  $(RED)clean$(RESET)         - Rimuove file compilati"
	@echo "  $(RED)clean-all$(RESET)     - Pulizia completa (include docs e cache)"
	@echo "  $(RED)reset$(RESET)         - Reset completo del progetto"
	@echo ""

# Compila tutto
all: $(BUILD_DIR) esempi esercizi soluzioni
	@echo "$(GREEN)✅ Compilazione completa terminata con successo!$(RESET)"

# ==================== COMPILAZIONE ====================

# Crea directory di build
$(BUILD_DIR):
	@echo "$(BLUE)📁 Creazione directory di build...$(RESET)"
	@mkdir -p $(BUILD_DIR) $(DOCS_DIR) $(TESTS_DIR)

# Esempi
esempi: $(BUILD_DIR) $(ESEMPI_BIN)
	@echo "$(GREEN)✅ Esempi compilati: $(words $(ESEMPI_BIN)) file$(RESET)"

$(BUILD_DIR)/esempio_%: $(ESEMPI_DIR)/%.c
	@echo "$(YELLOW)🔨 Compilazione esempio: $< → $@$(RESET)"
	@$(CC) $(CFLAGS_RELEASE) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)  ✓ $@ creato$(RESET)"

# Esercizi
esercizi: $(BUILD_DIR) $(ESERCIZI_BIN)
	@echo "$(GREEN)✅ Esercizi compilati: $(words $(ESERCIZI_BIN)) file$(RESET)"

$(BUILD_DIR)/esercizio_%: $(ESERCIZI_DIR)/%.c
	@echo "$(YELLOW)🔨 Compilazione esercizio: $< → $@$(RESET)"
	@$(CC) $(CFLAGS_RELEASE) -o $@ $<
	@echo "$(GREEN)  ✓ $@ creato$(RESET)"

# Soluzioni
soluzioni: $(BUILD_DIR) $(SOLUZIONI_BIN)
	@echo "$(GREEN)✅ Soluzioni compilate: $(words $(SOLUZIONI_BIN)) file$(RESET)"

$(BUILD_DIR)/soluzione_%: $(SOLUZIONI_DIR)/%.c
	@echo "$(YELLOW)🔨 Compilazione soluzione: $< → $@$(RESET)"
	@$(CC) $(CFLAGS_RELEASE) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)  ✓ $@ creato$(RESET)"

# ==================== VERSIONI SPECIALI ====================

# Versione debug
debug: CFLAGS := $(CFLAGS_DEBUG)
debug: $(BUILD_DIR)
	@echo "$(MAGENTA)🐛 Compilazione versione DEBUG...$(RESET)"
	@$(MAKE) all CFLAGS="$(CFLAGS_DEBUG)"
	@echo "$(GREEN)✅ Versione debug creata$(RESET)"

# Versione con profiling
profile: CFLAGS := $(CFLAGS_PROFILE)
profile: $(BUILD_DIR)
	@echo "$(MAGENTA)📊 Compilazione con PROFILING...$(RESET)"
	@$(MAKE) all CFLAGS="$(CFLAGS_PROFILE)"
	@echo "$(GREEN)✅ Versione profiling creata$(RESET)"

# ==================== TESTING AUTOMATICO ====================

# Test completi
test: soluzioni test-esempi test-soluzioni
	@echo "$(GREEN)🎉 Tutti i test completati con successo!$(RESET)"

# Test esempi
test-esempi: esempi
	@echo "$(BOLD)$(BLUE)🧪 TESTING ESEMPI$(RESET)"
	@echo "$(BLUE)═══════════════════$(RESET)"
	@for exe in $(ESEMPI_BIN); do \
		echo "$(YELLOW)🔬 Test: $$exe$(RESET)"; \
		if [ -f "$$exe" ]; then \
			echo "1\n2\n3\n0" | timeout 10s $$exe > /dev/null 2>&1 && \
			echo "$(GREEN)  ✓ $$exe - PASS$(RESET)" || \
			echo "$(RED)  ✗ $$exe - FAIL$(RESET)"; \
		fi; \
	done

# Test soluzioni con input automatici
test-soluzioni: soluzioni
	@echo "$(BOLD)$(BLUE)🧪 TESTING SOLUZIONI$(RESET)"
	@echo "$(BLUE)═══════════════════════$(RESET)"
	@# Test Semaforo
	@if [ -f "$(BUILD_DIR)/soluzione_esercizio1_semaforo" ]; then \
		echo "$(YELLOW)🚦 Test Simulatore Semaforo...$(RESET)"; \
		echo "1\n3\n6\n2\n5\n0" | timeout 15s $(BUILD_DIR)/soluzione_esercizio1_semaforo > /dev/null 2>&1 && \
		echo "$(GREEN)  ✓ Semaforo - PASS$(RESET)" || \
		echo "$(RED)  ✗ Semaforo - FAIL$(RESET)"; \
	fi
	@# Test Gestione Voti
	@if [ -f "$(BUILD_DIR)/soluzione_esercizio2_gestione_voti" ]; then \
		echo "$(YELLOW)📚 Test Gestione Voti...$(RESET)"; \
		echo "1\nMario Rossi\nmario@test.it\n01/01/2000\n8.5\n9.0\n7.5\n-1\n5\n0" | timeout 20s $(BUILD_DIR)/soluzione_esercizio2_gestione_voti > /dev/null 2>&1 && \
		echo "$(GREEN)  ✓ Gestione Voti - PASS$(RESET)" || \
		echo "$(RED)  ✗ Gestione Voti - FAIL$(RESET)"; \
	fi
	@# Test Ascensore
	@if [ -f "$(BUILD_DIR)/soluzione_esercizio3_simulatore_ascensore" ]; then \
		echo "$(YELLOW)🏢 Test Simulatore Ascensore...$(RESET)"; \
		echo "1\n5\n0\n0\n2\n1\n6" | timeout 25s $(BUILD_DIR)/soluzione_esercizio3_simulatore_ascensore > /dev/null 2>&1 && \
		echo "$(GREEN)  ✓ Ascensore - PASS$(RESET)" || \
		echo "$(RED)  ✗ Ascensore - FAIL$(RESET)"; \
	fi

# Validazione completa del codice
validate: 
	@echo "$(BOLD)$(CYAN)🔍 VALIDAZIONE CODICE$(RESET)"
	@echo "$(CYAN)═══════════════════════$(RESET)"
	@# Controllo sintassi
	@echo "$(YELLOW)📝 Controllo sintassi...$(RESET)"
	@for src in $(SOLUZIONI_SRC); do \
		$(CC) -fsyntax-only $(CFLAGS) $$src && \
		echo "$(GREEN)  ✓ $$src - Sintassi OK$(RESET)" || \
		echo "$(RED)  ✗ $$src - Errori sintassi$(RESET)"; \
	done
	@# Controllo warning
	@echo "$(YELLOW)⚠️  Controllo warning...$(RESET)"
	@for src in $(SOLUZIONI_SRC); do \
		$(CC) -Wall -Wextra -c $$src -o /dev/null 2>/dev/null && \
		echo "$(GREEN)  ✓ $$src - Nessun warning$(RESET)" || \
		echo "$(YELLOW)  ⚠ $$src - Warning presenti$(RESET)"; \
	done

# ==================== PERFORMANCE E PROFILING ====================

# Benchmark delle soluzioni
benchmark: soluzioni
	@echo "$(BOLD)$(MAGENTA)⚡ BENCHMARK PERFORMANCE$(RESET)"
	@echo "$(MAGENTA)══════════════════════════$(RESET)"
	@# Crea file di test
	@mkdir -p $(TESTS_DIR)
	@echo "4\n1\n2\n3\n4\n0" > $(TESTS_DIR)/benchmark_input.txt
	@for exe in $(SOLUZIONI_BIN); do \
		if [ -f "$$exe" ]; then \
			echo "$(YELLOW)⏱️  Benchmark: $$exe$(RESET)"; \
			start_time=$$(date +%s.%N); \
			timeout 10s $$exe < $(TESTS_DIR)/benchmark_input.txt > /dev/null 2>&1; \
			end_time=$$(date +%s.%N); \
			runtime=$$(echo "$$end_time - $$start_time" | bc -l 2>/dev/null || echo "N/A"); \
			echo "$(CYAN)  📊 Tempo esecuzione: $$runtime secondi$(RESET)"; \
		fi; \
	done

# Controllo memory leaks
memory-check: debug
	@echo "$(BOLD)$(MAGENTA)🔍 CONTROLLO MEMORY LEAKS$(RESET)"
	@echo "$(MAGENTA)════════════════════════════$(RESET)"
	@if command -v valgrind >/dev/null 2>&1; then \
		for exe in $(SOLUZIONI_BIN); do \
			if [ -f "$$exe" ]; then \
				echo "$(YELLOW)🧠 Memory check: $$exe$(RESET)"; \
				echo "1\n0" | timeout 15s valgrind --leak-check=full --show-leak-kinds=all $$exe 2>&1 | grep -E "(ERROR SUMMARY|definitely lost)" && \
				echo "$(GREEN)  ✓ Memory check completato$(RESET)" || \
				echo "$(RED)  ✗ Problemi di memoria rilevati$(RESET)"; \
			fi; \
		done; \
	else \
		echo "$(RED)❌ Valgrind non installato$(RESET)"; \
	fi

# ==================== DEMO E PRESENTAZIONE ====================

# Demo interattiva
demo: soluzioni
	@echo "$(BOLD)$(BLUE)🎮 DEMO INTERATTIVA SOLUZIONI$(RESET)"
	@echo "$(BLUE)════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(GREEN)Seleziona la soluzione da testare:$(RESET)"
	@echo "1. 🚦 Simulatore Semaforo"
	@echo "2. 📚 Gestione Voti Studenti"
	@echo "3. 🏢 Simulatore Ascensore"
	@echo "4. 🎯 Demo automatica di tutte"
	@echo "0. ❌ Esci"
	@echo ""
	@read -p "Scelta: " choice; \
	case $$choice in \
		1) echo "$(CYAN)🚦 Avvio Simulatore Semaforo...$(RESET)"; \
		   [ -f "$(BUILD_DIR)/soluzione_esercizio1_semaforo" ] && $(BUILD_DIR)/soluzione_esercizio1_semaforo || echo "$(RED)File non trovato$(RESET)";; \
		2) echo "$(CYAN)📚 Avvio Gestione Voti...$(RESET)"; \
		   [ -f "$(BUILD_DIR)/soluzione_esercizio2_gestione_voti" ] && $(BUILD_DIR)/soluzione_esercizio2_gestione_voti || echo "$(RED)File non trovato$(RESET)";; \
		3) echo "$(CYAN)🏢 Avvio Simulatore Ascensore...$(RESET)"; \
		   [ -f "$(BUILD_DIR)/soluzione_esercizio3_simulatore_ascensore" ] && $(BUILD_DIR)/soluzione_esercizio3_simulatore_ascensore || echo "$(RED)File non trovato$(RESET)";; \
		4) $(MAKE) demo-auto;; \
		0) echo "$(GREEN)👋 Demo terminata$(RESET)";; \
		*) echo "$(RED)❌ Scelta non valida$(RESET)";; \
	esac

# Demo automatica con input predefiniti
demo-auto: soluzioni
	@echo "$(BOLD)$(BLUE)🎬 DEMO AUTOMATICA$(RESET)"
	@echo "$(BLUE)══════════════════$(RESET)"
	@mkdir -p $(TESTS_DIR)
	@# Demo Semaforo
	@echo "$(CYAN)🚦 Demo Semaforo (15 secondi)...$(RESET)"
	@echo "1\n3\n6\n2\n5\n0" | timeout 15s $(BUILD_DIR)/soluzione_esercizio1_semaforo 2>/dev/null || echo "$(YELLOW)Demo semaforo completata$(RESET)"
	@sleep 2
	@# Demo Gestione Voti
	@echo "$(CYAN)📚 Demo Gestione Voti (20 secondi)...$(RESET)"
	@echo "1\nTest Student\ntest@demo.it\n01/01/2000\n8.5\n9.0\n7.5\n-1\n2\n5\n0" | timeout 20s $(BUILD_DIR)/soluzione_esercizio2_gestione_voti 2>/dev/null || echo "$(YELLOW)Demo gestione voti completata$(RESET)"
	@sleep 2
	@# Demo Ascensore
	@echo "$(CYAN)🏢 Demo Ascensore (25 secondi)...$(RESET)"
	@echo "4\n6" | timeout 25s $(BUILD_DIR)/soluzione_esercizio3_simulatore_ascensore 2>/dev/null || echo "$(YELLOW)Demo ascensore completata$(RESET)"
	@echo "$(GREEN)🎉 Demo automatica completata!$(RESET)"

# Showcase completo
showcase: all
	@echo "$(BOLD)$(WHITE)🌟 SHOWCASE LEZIONE 04 - STRUTTURE DI CONTROLLO$(RESET)"
	@echo "$(WHITE)═══════════════════════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(BOLD)📋 CONTENUTI LEZIONE:$(RESET)"
	@echo "  🔹 $(words $(ESEMPI_SRC)) esempi pratici"
	@echo "  🔹 $(words $(ESERCIZI_SRC)) esercizi progressivi"
	@echo "  🔹 $(words $(SOLUZIONI_SRC)) soluzioni complete"
	@echo ""
	@$(MAKE) stats
	@echo ""
	@echo "$(GREEN)✨ Lezione 04 pronta per l'utilizzo!$(RESET)"

# ==================== DOCUMENTAZIONE ====================

# Genera documentazione
docs: 
	@echo "$(BOLD)$(WHITE)📚 GENERAZIONE DOCUMENTAZIONE$(RESET)"
	@echo "$(WHITE)══════════════════════════════$(RESET)"
	@mkdir -p $(DOCS_DIR)
	@# Crea indice
	@echo "# Documentazione Lezione 04 - Strutture di Controllo" > $(DOCS_DIR)/README.md
	@echo "" >> $(DOCS_DIR)/README.md
	@echo "## Esempi Disponibili" >> $(DOCS_DIR)/README.md
	@for src in $(ESEMPI_SRC); do \
		basename=$$( basename $$src .c ); \
		echo "- **$$basename**: " >> $(DOCS_DIR)/README.md; \
		head -10 $$src | grep -E "^\s*\*|/\*|//" | sed 's/^[[:space:]]*[*\/]*[[:space:]]*//' >> $(DOCS_DIR)/README.md; \
		echo "" >> $(DOCS_DIR)/README.md; \
	done
	@echo "$(GREEN)✅ Documentazione generata in $(DOCS_DIR)/$(RESET)"

# Report copertura codice
coverage: profile
	@echo "$(BOLD)$(WHITE)📊 REPORT COPERTURA CODICE$(RESET)"
	@echo "$(WHITE)════════════════════════════$(RESET)"
	@if command -v gcov >/dev/null 2>&1; then \
		for src in $(SOLUZIONI_SRC); do \
			gcov $$src 2>/dev/null && \
			echo "$(GREEN)✓ Coverage generata per $$src$(RESET)" || \
			echo "$(YELLOW)⚠ Coverage non disponibile per $$src$(RESET)"; \
		done; \
		mv *.gcov $(BUILD_DIR)/ 2>/dev/null || true; \
	else \
		echo "$(RED)❌ gcov non disponibile$(RESET)"; \
	fi

# Statistiche progetto
stats:
	@echo "$(BOLD)$(CYAN)📈 STATISTICHE PROGETTO$(RESET)"
	@echo "$(CYAN)═══════════════════════$(RESET)"
	@echo "$(YELLOW)📁 File sorgenti:$(RESET)"
	@echo "  🔹 Esempi: $(words $(ESEMPI_SRC))"
	@echo "  🔹 Esercizi: $(words $(ESERCIZI_SRC))"
	@echo "  🔹 Soluzioni: $(words $(SOLUZIONI_SRC))"
	@total_lines=0; \
	for src in $(ESEMPI_SRC) $(ESERCIZI_SRC) $(SOLUZIONI_SRC); do \
		lines=$$(wc -l < $$src 2>/dev/null || echo 0); \
		total_lines=$$((total_lines + lines)); \
	done; \
	echo "$(YELLOW)📊 Linee di codice totali: $$total_lines$(RESET)"
	@echo "$(YELLOW)🔨 Eseguibili compilati:$(RESET)"
	@compiled=0; \
	for exe in $(ESEMPI_BIN) $(ESERCIZI_BIN) $(SOLUZIONI_BIN); do \
		[ -f "$$exe" ] && compiled=$$((compiled + 1)); \
	done; \
	echo "  🔹 Compilati: $$compiled"
	@echo "$(YELLOW)💾 Dimensione build:$(RESET)"
	@[ -d "$(BUILD_DIR)" ] && du -sh $(BUILD_DIR) 2>/dev/null | cut -f1 | xargs echo "  🔹 Directory build:" || echo "  🔹 Directory build: N/A"

# ==================== PULIZIA ====================

# Pulizia base
clean:
	@echo "$(RED)🧹 Pulizia file compilati...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@rm -f *.o *.gch *.gcov *.gcda *.gcno
	@echo "$(GREEN)✅ Pulizia completata$(RESET)"

# Pulizia completa
clean-all: clean
	@echo "$(RED)🧹 Pulizia completa...$(RESET)"
	@rm -rf $(DOCS_DIR) $(TESTS_DIR)
	@rm -f gmon.out *.log core.*
	@echo "$(GREEN)✅ Pulizia completa terminata$(RESET)"

# Reset completo
reset: clean-all
	@echo "$(RED)🔄 Reset completo del progetto...$(RESET)"
	@echo "$(YELLOW)Questo rimuoverà tutti i file generati. Continuare? [y/N]$(RESET)"
	@read -r confirm; \
	if [ "$$confirm" = "y" ] || [ "$$confirm" = "Y" ]; then \
		echo "$(RED)🗑️  Reset in corso...$(RESET)"; \
		find . -name "*.tmp" -delete 2>/dev/null || true; \
		find . -name "*.bak" -delete 2>/dev/null || true; \
		echo "$(GREEN)✅ Reset completato$(RESET)"; \
	else \
		echo "$(YELLOW)❌ Reset annullato$(RESET)"; \
	fi

# ==================== TARGET AVANZATI ====================

# Installa dipendenze di sviluppo
install-deps:
	@echo "$(BOLD)$(BLUE)📦 INSTALLAZIONE DIPENDENZE$(RESET)"
	@echo "$(BLUE)════════════════════════════$(RESET)"
	@if command -v apt-get >/dev/null 2>&1; then \
		echo "$(YELLOW)🔧 Installazione via apt-get...$(RESET)"; \
		sudo apt-get update && sudo apt-get install -y gcc valgrind gcov doxygen; \
	elif command -v yum >/dev/null 2>&1; then \
		echo "$(YELLOW)🔧 Installazione via yum...$(RESET)"; \
		sudo yum install -y gcc valgrind gcov doxygen; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "$(YELLOW)🔧 Installazione via brew...$(RESET)"; \
		brew install gcc valgrind doxygen; \
	else \
		echo "$(RED)❌ Gestore pacchetti non riconosciuto$(RESET)"; \
	fi

# Controllo qualità codice
quality-check: validate
	@echo "$(BOLD)$(MAGENTA)🔍 CONTROLLO QUALITÀ CODICE$(RESET)"
	@echo "$(MAGENTA)═══════════════════════════$(RESET)"
	@# Controllo complessità ciclomatica (simulato)
	@for src in $(SOLUZIONI_SRC); do \
		complexity=$$(grep -c -E "(if|while|for|switch|case)" $$src); \
		echo "$(YELLOW)📊 $$src: Complessità $$complexity$(RESET)"; \
		if [ $$complexity -gt 50 ]; then \
			echo "$(RED)  ⚠ Complessità elevata$(RESET)"; \
		else \
			echo "$(GREEN)  ✓ Complessità accettabile$(RESET)"; \
		fi; \
	done

# ==================== INFORMAZIONI SISTEMA ====================

# Informazioni ambiente
env-info:
	@echo "$(BOLD)$(CYAN)🖥️  INFORMAZIONI AMBIENTE$(RESET)"
	@echo "$(CYAN)══════════════════════════$(RESET)"
	@echo "$(YELLOW)💻 Sistema:$(RESET) $$(uname -s -r)"
	@echo "$(YELLOW)🔧 Compilatore:$(RESET) $$($(CC) --version | head -1)"
	@echo "$(YELLOW)📁 Directory:$(RESET) $$(pwd)"
	@echo "$(YELLOW)👤 Utente:$(RESET) $$(whoami)"
	@echo "$(YELLOW)📅 Data:$(RESET) $$(date)"

# Verifica requisiti
check-requirements:
	@echo "$(BOLD)$(BLUE)✅ VERIFICA REQUISITI$(RESET)"
	@echo "$(BLUE)══════════════════════$(RESET)"
	@command -v $(CC) >/dev/null 2>&1 && echo "$(GREEN)✓ GCC disponibile$(RESET)" || echo "$(RED)✗ GCC mancante$(RESET)"
	@command -v make >/dev/null 2>&1 && echo "$(GREEN)✓ Make disponibile$(RESET)" || echo "$(RED)✗ Make mancante$(RESET)"
	@command -v valgrind >/dev/null 2>&1 && echo "$(GREEN)✓ Valgrind disponibile$(RESET)" || echo "$(YELLOW)⚠ Valgrind opzionale$(RESET)"
	@command -v gcov >/dev/null 2>&1 && echo "$(GREEN)✓ Gcov disponibile$(RESET)" || echo "$(YELLOW)⚠ Gcov opzionale$(RESET)"

# ==================== FINE MAKEFILE ====================
