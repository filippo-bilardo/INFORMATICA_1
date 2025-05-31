# Makefile per le Soluzioni degli Esercizi - Lezione 02
# Compilazione automatica e test delle soluzioni

# 🎯 Configurazione
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

# 📁 Definizione dei target
TARGETS = esercizio1_soluzione esercizio2_soluzione esercizio3_soluzione

# 🎨 Colori per output
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

.PHONY: all clean run test help info

# 🚀 Target principale
all: $(TARGETS)
	@echo "$(GREEN)✅ Tutte le soluzioni compilate con successo!$(RESET)"
	@echo "$(CYAN)💡 Usa 'make run' per eseguire tutte le soluzioni$(RESET)"

# 📝 Compilazione delle singole soluzioni
esercizio1_soluzione: esercizio1_soluzione.c
	@echo "$(YELLOW)🔨 Compilazione Esercizio 1...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)✅ Esercizio 1 compilato$(RESET)"

esercizio2_soluzione: esercizio2_soluzione.c
	@echo "$(YELLOW)🔨 Compilazione Esercizio 2...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)✅ Esercizio 2 compilato$(RESET)"

esercizio3_soluzione: esercizio3_soluzione.c
	@echo "$(YELLOW)🔨 Compilazione Esercizio 3...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)✅ Esercizio 3 compilato$(RESET)"

# 🏃 Esecuzione
run: all
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                    ESECUZIONE SOLUZIONI                    ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)🔸 Esecuzione Esercizio 1: Tipi di Dato$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	./esercizio1_soluzione
	@echo ""
	@echo "$(CYAN)🔸 Esecuzione Esercizio 2: Calcolatore Area$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(YELLOW)💡 Input di esempio: lunghezza=5.5, larghezza=3.2$(RESET)"
	echo -e "5.5\n3.2" | ./esercizio2_soluzione
	@echo ""
	@echo "$(CYAN)🔸 Esecuzione Esercizio 3: Convertitore Temperature$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(YELLOW)💡 Input di esempio: 1 (Celsius), 25.5°C$(RESET)"
	echo -e "1\n25.5" | ./esercizio3_soluzione

# 🔍 Test con valori predefiniti
test: all
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                       TEST AUTOMATICI                      ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(BLUE)🧪 Test Esercizio 1: Dimostrazione tipi di dato$(RESET)"
	@./esercizio1_soluzione
	@echo ""
	@echo "$(BLUE)🧪 Test Esercizio 2: Calcolo area rettangolo 10x5$(RESET)"
	@echo -e "10\n5" | ./esercizio2_soluzione
	@echo ""
	@echo "$(BLUE)🧪 Test Esercizio 3: Conversione 0°C$(RESET)"
	@echo -e "1\n0" | ./esercizio3_soluzione
	@echo ""
	@echo "$(BLUE)🧪 Test Esercizio 3: Conversione 100°F$(RESET)"
	@echo -e "2\n100" | ./esercizio3_soluzione
	@echo ""
	@echo "$(GREEN)✅ Tutti i test completati!$(RESET)"

# 🧹 Pulizia
clean:
	@echo "$(RED)🧹 Pulizia file compilati...$(RESET)"
	rm -f $(TARGETS)
	@echo "$(GREEN)✅ Pulizia completata!$(RESET)"

# 📊 Informazioni sui file sorgente
info:
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                   INFORMAZIONI SOLUZIONI                   ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)📂 File Sorgente:$(RESET)"
	@ls -la *.c 2>/dev/null | awk '{print "$(YELLOW)  🔸 " $$9 " $(WHITE)(" $$5 " bytes)$(RESET)"}' || echo "$(RED)❌ Nessun file .c trovato$(RESET)"
	@echo ""
	@echo "$(CYAN)🎯 Eseguibili:$(RESET)"
	@ls -la $(TARGETS) 2>/dev/null | awk '{print "$(GREEN)  ✅ " $$9 " $(WHITE)(" $$5 " bytes)$(RESET)"}' || echo "$(RED)❌ Nessun eseguibile trovato$(RESET)"
	@echo ""
	@echo "$(CYAN)📏 Statistiche Codice:$(RESET)"
	@for file in *.c; do \
		if [ -f "$$file" ]; then \
			lines=$$(wc -l < "$$file"); \
			echo "$(WHITE)  📄 $$file: $$lines righe$(RESET)"; \
		fi; \
	done

# 📋 Aiuto
help:
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                        AIUTO MAKEFILE                      ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)🎯 Target disponibili:$(RESET)"
	@echo "$(WHITE)  make all          $(YELLOW)- Compila tutte le soluzioni$(RESET)"
	@echo "$(WHITE)  make esercizio1   $(YELLOW)- Compila solo esercizio 1$(RESET)"
	@echo "$(WHITE)  make esercizio2   $(YELLOW)- Compila solo esercizio 2$(RESET)"
	@echo "$(WHITE)  make esercizio3   $(YELLOW)- Compila solo esercizio 3$(RESET)"
	@echo "$(WHITE)  make run          $(YELLOW)- Esegue tutte le soluzioni$(RESET)"
	@echo "$(WHITE)  make test         $(YELLOW)- Esegue test automatici$(RESET)"
	@echo "$(WHITE)  make clean        $(YELLOW)- Rimuove file compilati$(RESET)"
	@echo "$(WHITE)  make info         $(YELLOW)- Mostra informazioni sui file$(RESET)"
	@echo "$(WHITE)  make help         $(YELLOW)- Mostra questo aiuto$(RESET)"
	@echo ""
	@echo "$(CYAN)🔧 Esempi di utilizzo:$(RESET)"
	@echo "$(WHITE)  make && make run              $(YELLOW)# Compila ed esegue tutto$(RESET)"
	@echo "$(WHITE)  make esercizio1_soluzione     $(YELLOW)# Compila solo esercizio 1$(RESET)"
	@echo "$(WHITE)  ./esercizio1_soluzione        $(YELLOW)# Esegue esercizio 1$(RESET)"
