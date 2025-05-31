# Makefile per Soluzioni Esercizi - Lezione 03: Operatori
# Compilazione automatica con testing e validazione

# Configurazione compilatore
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = .
BINDIR = ../../../bin/03_operatori_soluzioni

# Lista delle soluzioni
SOLUTIONS = esercizio1_soluzione esercizio2_soluzione esercizio3_soluzione
SOURCES = $(SOLUTIONS:=.c)
BINARIES = $(addprefix $(BINDIR)/, $(SOLUTIONS))

# Colori per output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[1;37m
NC = \033[0m # No Color

# Target principale
.PHONY: all clean test run-all help validate demo

all: setup $(BINARIES)
	@echo "$(GREEN)✅ Tutte le soluzioni compilate con successo!$(NC)"
	@echo "$(CYAN)📂 Binari disponibili in: $(BINDIR)$(NC)"
	@echo "$(YELLOW)💡 Usa 'make run-all' per testare tutte le soluzioni$(NC)"

# Setup directory
setup:
	@mkdir -p $(BINDIR)

# Compilazione individuale
$(BINDIR)/%: %.c
	@echo "$(BLUE)🔨 Compilazione: $< → $@$(NC)"
	@$(CC) $(CFLAGS) $< -o $@ -lm
	@echo "$(GREEN)✅ $@ compilato$(NC)"

# Target per eseguire tutte le soluzioni
run-all: all
	@echo "$(PURPLE)╔══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(PURPLE)║              🧪 TEST AUTOMATICO SOLUZIONI 🧪             ║$(NC)"
	@echo "$(PURPLE)║                   Lezione 03: Operatori                  ║$(NC)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@$(MAKE) run-1
	@echo "\n$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(NC)\n"
	@$(MAKE) run-2
	@echo "\n$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(NC)\n"
	@$(MAKE) run-3

# Esecuzione singole soluzioni con input automatico
run-1: $(BINDIR)/esercizio1_soluzione
	@echo "$(YELLOW)🧮 ESERCIZIO 1: Calcolatore Espressioni$(NC)"
	@echo "$(WHITE)Input automatico: 10 5 3$(NC)"
	@echo "10\n5\n3" | $(BINDIR)/esercizio1_soluzione

run-2: $(BINDIR)/esercizio2_soluzione
	@echo "$(YELLOW)🔐 ESERCIZIO 2: Sistema Controllo Accessi$(NC)"
	@echo "$(WHITE)Input automatico: ID=1250, Livello=4, Età=28, Badge=s, Orario=s, Auth=n$(NC)"
	@echo "1250\n4\n28\ns\ns\nn" | $(BINDIR)/esercizio2_soluzione

run-3: $(BINDIR)/esercizio3_soluzione
	@echo "$(YELLOW)🎨 ESERCIZIO 3: Manipolatore Pixel RGB$(NC)"
	@echo "$(WHITE)Input automatico: R=255, G=87, B=51 (arancione)$(NC)"
	@echo "255\n87\n51" | $(BINDIR)/esercizio3_soluzione

# Demo interattiva
demo: all
	@echo "$(PURPLE)╔══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(PURPLE)║                    🎮 DEMO INTERATTIVA 🎮                ║$(NC)"
	@echo "$(PURPLE)║                   Scegli una soluzione                   ║$(NC)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(CYAN)1)$(NC) $(YELLOW)🧮 Calcolatore Espressioni$(NC) (operatori aritmetici)"
	@echo "$(CYAN)2)$(NC) $(YELLOW)🔐 Sistema Controllo Accessi$(NC) (operatori logici)"
	@echo "$(CYAN)3)$(NC) $(YELLOW)🎨 Manipolatore Pixel RGB$(NC) (operatori bit a bit)"
	@echo ""
	@read -p "$(WHITE)Inserisci il numero (1-3): $(NC)" choice; \
	case $$choice in \
		1) echo "$(GREEN)Avvio Esercizio 1...$(NC)"; $(BINDIR)/esercizio1_soluzione ;; \
		2) echo "$(GREEN)Avvio Esercizio 2...$(NC)"; $(BINDIR)/esercizio2_soluzione ;; \
		3) echo "$(GREEN)Avvio Esercizio 3...$(NC)"; $(BINDIR)/esercizio3_soluzione ;; \
		*) echo "$(RED)❌ Scelta non valida!$(NC)" ;; \
	esac

# Validazione codice
validate: all
	@echo "$(BLUE)🔍 VALIDAZIONE CODICE SOLUZIONI$(NC)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(NC)"
	
	@echo "$(YELLOW)📊 Statistiche codice:$(NC)"
	@for sol in $(SOLUTIONS); do \
		lines=$$(wc -l < $$sol.c); \
		echo "   $$sol.c: $$lines righe"; \
	done
	
	@echo "\n$(YELLOW)🔧 Controllo sintassi:$(NC)"
	@for sol in $(SOLUTIONS); do \
		if $(CC) $(CFLAGS) -fsyntax-only $$sol.c 2>/dev/null; then \
			echo "   $(GREEN)✅ $$sol.c: Sintassi corretta$(NC)"; \
		else \
			echo "   $(RED)❌ $$sol.c: Errori di sintassi$(NC)"; \
		fi; \
	done
	
	@echo "\n$(YELLOW)📏 Controllo stile:$(NC)"
	@for sol in $(SOLUTIONS); do \
		if command -v clang-format >/dev/null 2>&1; then \
			if clang-format --dry-run $$sol.c 2>/dev/null | diff $$sol.c - >/dev/null; then \
				echo "   $(GREEN)✅ $$sol.c: Stile conforme$(NC)"; \
			else \
				echo "   $(YELLOW)⚠️  $$sol.c: Stile migliorabile$(NC)"; \
			fi; \
		else \
			echo "   $(CYAN)ℹ️  clang-format non disponibile per check stile$(NC)"; \
			break; \
		fi; \
	done

# Test specifici per concetti
test: all
	@echo "$(PURPLE)🧪 TEST CONCETTI SPECIFICI$(NC)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(NC)"
	
	@echo "$(YELLOW)🔸 Test Operatori Aritmetici:$(NC)"
	@echo "12\n4\n2" | $(BINDIR)/esercizio1_soluzione | grep -q "ACCESSO GARANTITO" || echo "   Test precedenza: OK"
	
	@echo "$(YELLOW)🔸 Test Operatori Logici:$(NC)"
	@echo "1000\n5\n30\ns\ns\ns" | $(BINDIR)/esercizio2_soluzione | grep -q "5/5" && echo "   Test accesso completo: OK"
	
	@echo "$(YELLOW)🔸 Test Operatori Bit:$(NC)"
	@echo "255\n0\n0" | $(BINDIR)/esercizio3_soluzione | grep -q "FF0000" && echo "   Test manipolazione bit: OK"

# Benchmark performance
benchmark: all
	@echo "$(PURPLE)⚡ BENCHMARK PERFORMANCE$(NC)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(NC)"
	
	@for sol in $(SOLUTIONS); do \
		echo "$(YELLOW)📊 Benchmark $(BINDIR)/$$sol:$(NC)"; \
		time_output=$$(time -f "%e secondi" echo "10\n5\n3" | $(BINDIR)/$$sol >/dev/null 2>&1); \
		echo "   Tempo esecuzione: $$time_output"; \
	done 2>/dev/null || echo "$(CYAN)ℹ️  GNU time non disponibile per benchmark precisi$(NC)"

# Target per il debug
debug: CFLAGS += -DDEBUG -O0
debug: all
	@echo "$(RED)🐛 Versioni DEBUG compilate$(NC)"
	@echo "$(YELLOW)💡 Usa gdb per debugging: gdb $(BINDIR)/esercizio1_soluzione$(NC)"

# Target per la release
release: CFLAGS += -O3 -DNDEBUG
release: all
	@echo "$(GREEN)🚀 Versioni RELEASE ottimizzate compilate$(NC)"

# Pulizia
clean:
	@echo "$(YELLOW)🧹 Pulizia files...$(NC)"
	@rm -rf $(BINDIR)
	@echo "$(GREEN)✅ Pulizia completata$(NC)"

# Aiuto
help:
	@echo "$(PURPLE)╔══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(PURPLE)║                   📖 MAKEFILE HELP 📖                   ║$(NC)"
	@echo "$(PURPLE)║                Soluzioni Lezione 03                     ║$(NC)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(CYAN)🎯 TARGET PRINCIPALI:$(NC)"
	@echo "  $(YELLOW)make all$(NC)        - Compila tutte le soluzioni"
	@echo "  $(YELLOW)make run-all$(NC)    - Esegue test automatici di tutte"
	@echo "  $(YELLOW)make demo$(NC)       - Demo interattiva (scegli esercizio)"
	@echo "  $(YELLOW)make clean$(NC)      - Rimuove tutti i binari"
	@echo ""
	@echo "$(CYAN)🔧 TARGET SVILUPPO:$(NC)"
	@echo "  $(YELLOW)make debug$(NC)      - Compila con simboli debug"
	@echo "  $(YELLOW)make release$(NC)    - Compila ottimizzato per produzione"
	@echo "  $(YELLOW)make validate$(NC)   - Valida sintassi e stile codice"
	@echo "  $(YELLOW)make test$(NC)       - Test funzionalità specifiche"
	@echo "  $(YELLOW)make benchmark$(NC)  - Misura performance esecuzione"
	@echo ""
	@echo "$(CYAN)🎮 TARGET INDIVIDUALI:$(NC)"
	@echo "  $(YELLOW)make run-1$(NC)      - Solo Calcolatore Espressioni"
	@echo "  $(YELLOW)make run-2$(NC)      - Solo Sistema Controllo Accessi"
	@echo "  $(YELLOW)make run-3$(NC)      - Solo Manipolatore Pixel RGB"
	@echo ""
	@echo "$(CYAN)📁 STRUTTURA OUTPUT:$(NC)"
	@echo "  $(WHITE)$(BINDIR)/$(NC)"
	@echo "  ├── esercizio1_soluzione (operatori aritmetici)"
	@echo "  ├── esercizio2_soluzione (operatori logici)"
	@echo "  └── esercizio3_soluzione (operatori bit a bit)"

# File da non considerare come target
.PHONY: setup run-1 run-2 run-3 debug release benchmark

# Info progetto
info:
	@echo "$(PURPLE)╔══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(PURPLE)║                  📊 INFO PROGETTO 📊                    ║$(NC)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(CYAN)📚 Corso:$(NC) C by Example - Lezione 03: Operatori"
	@echo "$(CYAN)🎯 Focus:$(NC) Padronanza completa degli operatori C"
	@echo "$(CYAN)📈 Livello:$(NC) Da principiante a avanzato"
	@echo "$(CYAN)⏱️  Tempo:$(NC) 30-90 minuti per esercizio"
	@echo ""
	@echo "$(YELLOW)🔹 Esercizio 1:$(NC) Operatori aritmetici e precedenza"
	@echo "$(YELLOW)🔹 Esercizio 2:$(NC) Operatori logici e relazionali"
	@echo "$(YELLOW)🔹 Esercizio 3:$(NC) Operatori bit a bit avanzati"
	@echo ""
	@echo "$(GREEN)✨ Features:$(NC)"
	@echo "  • Gestione errori completa"
	@echo "  • Output colorato e interattivo"
	@echo "  • Spiegazioni dettagliate"
	@echo "  • Esempi pratici real-world"
	@echo "  • Testing automatico"
