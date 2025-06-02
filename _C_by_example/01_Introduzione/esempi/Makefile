# Makefile per Esempi di Introduzione al C

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
BUILD_DIR = build

# Lista degli esempi
EXAMPLES = hello_world info_sistema

.PHONY: all clean help run-all

all: $(EXAMPLES)

# Regola generica per compilare esempi
%: %.c
	@mkdir -p $(BUILD_DIR)
	@echo "🔨 Compilando $<..."
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@
	@echo "✅ $@ compilato con successo!"

# Esegue tutti gli esempi
run-all: all
	@echo ""
	@echo "🚀 Eseguendo tutti gli esempi..."
	@echo ""
	@for example in $(EXAMPLES); do \
		echo "▶️  Eseguendo $$example:"; \
		echo "----------------------------------------"; \
		./$(BUILD_DIR)/$$example; \
		echo "----------------------------------------"; \
		echo ""; \
	done

# Esegue un esempio specifico
run-%: %
	@echo "▶️  Eseguendo $*:"
	@echo "----------------------------------------"
	@./$(BUILD_DIR)/$*
	@echo "----------------------------------------"

clean:
	@echo "🧹 Pulizia file compilati..."
	@rm -rf $(BUILD_DIR)
	@echo "✅ Pulizia completata!"

help:
	@echo "📖 Comandi disponibili:"
	@echo "  make all        - Compila tutti gli esempi"
	@echo "  make <nome>     - Compila un esempio specifico"
	@echo "  make run-all    - Compila ed esegue tutti gli esempi"
	@echo "  make run-<nome> - Compila ed esegue un esempio specifico"
	@echo "  make clean      - Rimuove i file compilati"
	@echo "  make help       - Mostra questo messaggio"
	@echo ""
	@echo "📁 Esempi disponibili:"
	@echo "  $(EXAMPLES)"
	@echo ""
	@echo "💡 Esempi di utilizzo:"
	@echo "  make hello_world         # Compila hello_world.c"
	@echo "  make run-hello_world     # Compila ed esegue hello_world"
	@echo "  make run-all             # Esegue tutti gli esempi"
