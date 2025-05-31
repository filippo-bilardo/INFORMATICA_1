# Makefile per Esercizi - Introduzione al C

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
BUILD_DIR = build
SOL_DIR = soluzioni

# Lista degli esercizi
EXERCISES = esercizio1 esercizio2 esercizio3
SOLUTIONS = esercizio1_soluzione

.PHONY: all exercises solutions clean help test run-esercizio1 run-esercizio2 run-esercizio3

all: exercises solutions

# Compila tutti gli esercizi
exercises:
	@echo "🔨 Compilando esercizi..."
	@mkdir -p $(BUILD_DIR)
	@for ex in $(EXERCISES); do \
		if [ -f "$$ex.c" ]; then \
			echo "  - $$ex.c"; \
			$(CC) $(CFLAGS) "$$ex.c" -o $(BUILD_DIR)/$$ex 2>/dev/null || \
			echo "    ⚠️  $$ex.c ha errori di compilazione (normale se non completato)"; \
		fi \
	done
	@echo "✅ Compilazione esercizi completata!"

# Compila le soluzioni
solutions:
	@echo "🔨 Compilando soluzioni..."
	@mkdir -p $(BUILD_DIR)
	@for sol in $(SOLUTIONS); do \
		if [ -f "$(SOL_DIR)/$$sol.c" ]; then \
			echo "  - $$sol.c"; \
			$(CC) $(CFLAGS) "$(SOL_DIR)/$$sol.c" -o $(BUILD_DIR)/$$sol; \
		fi \
	done
	@echo "✅ Compilazione soluzioni completata!"

# Compila un esercizio specifico
%: %.c
	@mkdir -p $(BUILD_DIR)
	@echo "🔨 Compilando $<..."
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@
	@echo "✅ $@ compilato con successo!"

# Esegue un esercizio
run-%:
	@if [ -f "$(BUILD_DIR)/$*" ]; then \
		echo "▶️  Eseguendo $*:"; \
		echo "----------------------------------------"; \
		./$(BUILD_DIR)/$*; \
		echo "----------------------------------------"; \
	else \
		echo "❌ $* non trovato. Compila prima con: make $*"; \
	fi

# Test degli esercizi (controlla solo che compilino)
test:
	@echo "🧪 Testando compilazione degli esercizi..."
	@passed=0; failed=0; \
	for ex in $(EXERCISES); do \
		if $(CC) $(CFLAGS) "$$ex.c" -o /tmp/test_$$ex 2>/dev/null; then \
			echo "✅ $$ex.c compila correttamente"; \
			rm -f /tmp/test_$$ex; \
			passed=$$((passed + 1)); \
		else \
			echo "❌ $$ex.c ha errori di compilazione"; \
			failed=$$((failed + 1)); \
		fi \
	done; \
	echo ""; \
	echo "📊 Risultati: ✅ $$passed passati, ❌ $$failed falliti"

clean:
	@echo "🧹 Pulizia file compilati..."
	@rm -rf $(BUILD_DIR)
	@echo "✅ Pulizia completata!"

help:
	@echo "📖 Comandi disponibili:"
	@echo "  make all              - Compila tutti gli esercizi e soluzioni"
	@echo "  make exercises        - Compila solo gli esercizi"
	@echo "  make solutions        - Compila solo le soluzioni"
	@echo "  make <nome>           - Compila un esercizio specifico"
	@echo "  make run-<nome>       - Esegue un esercizio specifico"
	@echo "  make test             - Testa la compilazione di tutti gli esercizi"
	@echo "  make clean            - Rimuove i file compilati"
	@echo "  make help             - Mostra questo messaggio"
	@echo ""
	@echo "📁 Esercizi disponibili:"
	@echo "  $(EXERCISES)"
	@echo ""
	@echo "💡 Esempi di utilizzo:"
	@echo "  make esercizio1           # Compila esercizio1.c"
	@echo "  make run-esercizio1       # Esegue esercizio1"
	@echo "  make test                 # Verifica tutti gli esercizi"
