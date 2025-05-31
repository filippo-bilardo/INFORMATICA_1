# Makefile per Esempi - Lezione 03: Operatori
# Compilazione e esecuzione automatica degli esempi

# 🎯 Configurazione
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGETS = calcolatrice_base confronti_avanzati manipolazione_bit

# 🎨 Colori per output
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

.PHONY: all clean run demo help info

# 🚀 Target principale
all: $(TARGETS)
	@echo "$(GREEN)✅ Tutti gli esempi compilati con successo!$(RESET)"
	@echo "$(CYAN)💡 Usa 'make run' per eseguire tutti gli esempi$(RESET)"

# 📝 Compilazione singoli esempi
calcolatrice_base: calcolatrice_base.c
	@echo "$(YELLOW)🔨 Compilazione Calcolatrice Base...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "$(GREEN)✅ Calcolatrice Base compilata$(RESET)"

confronti_avanzati: confronti_avanzati.c
	@echo "$(YELLOW)🔨 Compilazione Confronti Avanzati...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "$(GREEN)✅ Confronti Avanzati compilato$(RESET)"

manipolazione_bit: manipolazione_bit.c
	@echo "$(YELLOW)🔨 Compilazione Manipolazione Bit...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "$(GREEN)✅ Manipolazione Bit compilata$(RESET)"

# 🏃 Esecuzione con input automatici
run: all
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                    ESECUZIONE ESEMPI                       ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)🔸 Esempio 1: Calcolatrice Base$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(YELLOW)💡 Input automatico: 15.5, 4.2, opzione 7 (tutte le operazioni)$(RESET)"
	echo -e "15.5\n4.2\n7" | ./calcolatrice_base
	@echo ""
	@echo "$(CYAN)🔸 Esempio 2: Confronti Avanzati$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(YELLOW)💡 Input automatico: voti 8,7,9 - assenze 15 - debiti recuperati$(RESET)"
	echo -e "8\n7\n9\n15\ns" | ./confronti_avanzati
	@echo ""
	@echo "$(CYAN)🔸 Esempio 3: Manipolazione Bit$(RESET)"
	@echo "$(WHITE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	./manipolazione_bit

# 🎭 Dimostrazione interattiva
demo: all
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                    DEMO INTERATTIVA                        ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(BLUE)🎯 Seleziona l'esempio da eseguire:$(RESET)"
	@echo "$(WHITE)1) Calcolatrice Base$(RESET)"
	@echo "$(WHITE)2) Confronti Avanzati$(RESET)"
	@echo "$(WHITE)3) Manipolazione Bit$(RESET)"
	@echo ""
	@read -p "$(CYAN)Inserisci la tua scelta (1-3): $(RESET)" choice; \
	case $$choice in \
		1) echo "$(GREEN)🚀 Avvio Calcolatrice Base...$(RESET)"; ./calcolatrice_base ;; \
		2) echo "$(GREEN)🚀 Avvio Confronti Avanzati...$(RESET)"; ./confronti_avanzati ;; \
		3) echo "$(GREEN)🚀 Avvio Manipolazione Bit...$(RESET)"; ./manipolazione_bit ;; \
		*) echo "$(RED)❌ Scelta non valida!$(RESET)" ;; \
	esac

# 🧹 Pulizia
clean:
	@echo "$(RED)🧹 Pulizia file compilati...$(RESET)"
	rm -f $(TARGETS)
	@echo "$(GREEN)✅ Pulizia completata!$(RESET)"

# 📊 Informazioni sui file
info:
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                    INFORMAZIONI ESEMPI                     ║$(RESET)"
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
	@echo ""
	@echo "$(CYAN)🎯 Concetti Dimostrati:$(RESET)"
	@echo "$(WHITE)  📄 calcolatrice_base.c: Operatori aritmetici, incremento/decremento$(RESET)"
	@echo "$(WHITE)  📄 confronti_avanzati.c: Operatori relazionali, logici, short-circuit$(RESET)"
	@echo "$(WHITE)  📄 manipolazione_bit.c: Operatori bit a bit, flags, ottimizzazioni$(RESET)"

# 📋 Aiuto
help:
	@echo "$(MAGENTA)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(MAGENTA)║                        AIUTO MAKEFILE                      ║$(RESET)"
	@echo "$(MAGENTA)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)🎯 Target disponibili:$(RESET)"
	@echo "$(WHITE)  make all                    $(YELLOW)- Compila tutti gli esempi$(RESET)"
	@echo "$(WHITE)  make calcolatrice_base      $(YELLOW)- Compila solo la calcolatrice$(RESET)"
	@echo "$(WHITE)  make confronti_avanzati     $(YELLOW)- Compila solo i confronti$(RESET)"
	@echo "$(WHITE)  make manipolazione_bit      $(YELLOW)- Compila solo i bit$(RESET)"
	@echo "$(WHITE)  make run                    $(YELLOW)- Esegue tutti gli esempi$(RESET)"
	@echo "$(WHITE)  make demo                   $(YELLOW)- Demo interattiva$(RESET)"
	@echo "$(WHITE)  make clean                  $(YELLOW)- Rimuove file compilati$(RESET)"
	@echo "$(WHITE)  make info                   $(YELLOW)- Mostra informazioni$(RESET)"
	@echo "$(WHITE)  make help                   $(YELLOW)- Mostra questo aiuto$(RESET)"
	@echo ""
	@echo "$(CYAN)🔧 Esempi di utilizzo:$(RESET)"
	@echo "$(WHITE)  make && make run            $(YELLOW)# Compila ed esegue tutto$(RESET)"
	@echo "$(WHITE)  make calcolatrice_base      $(YELLOW)# Solo calcolatrice$(RESET)"
	@echo "$(WHITE)  ./calcolatrice_base         $(YELLOW)# Esegue calcolatrice$(RESET)"
	@echo "$(WHITE)  make demo                   $(YELLOW)# Scegli esempio da eseguire$(RESET)"
	@echo ""
	@echo "$(CYAN)📚 Ordine di studio consigliato:$(RESET)"
	@echo "$(WHITE)  1️⃣  calcolatrice_base       $(YELLOW)# Operatori aritmetici base$(RESET)"
	@echo "$(WHITE)  2️⃣  confronti_avanzati      $(YELLOW)# Logica e confronti$(RESET)"
	@echo "$(WHITE)  3️⃣  manipolazione_bit       $(YELLOW)# Operatori bit a bit$(RESET)"
