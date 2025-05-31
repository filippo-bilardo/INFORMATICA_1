#!/bin/bash

# Script di Setup per "C by Example"
# Questo script aiuta a configurare l'ambiente di sviluppo e verifica i prerequisiti

set -e  # Esce se ci sono errori

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Banner di benvenuto
echo -e "${PURPLE}"
echo "╔══════════════════════════════════════════════════════════════╗"
echo "║                                                              ║"
echo "║                   🚀 C BY EXAMPLE 🚀                        ║"
echo "║                                                              ║"
echo "║              Setup dell'Ambiente di Sviluppo                ║"
echo "║                                                              ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo -e "${NC}"
echo

# Funzione per log colorati
log_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

log_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

log_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

log_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Verifica sistema operativo
echo -e "${CYAN}🔍 VERIFICA SISTEMA${NC}"
echo "────────────────────────"

OS_NAME=$(uname -s)
log_info "Sistema operativo: $OS_NAME"

case "$OS_NAME" in
    "Linux")
        log_success "Linux rilevato - Ottimo per lo sviluppo C!"
        DISTRO=$(lsb_release -si 2>/dev/null || echo "Sconosciuta")
        log_info "Distribuzione: $DISTRO"
        ;;
    "Darwin")
        log_success "macOS rilevato - Perfetto per lo sviluppo C!"
        ;;
    "MINGW"*|"CYGWIN"*|"MSYS"*)
        log_success "Windows con ambiente Unix rilevato"
        ;;
    *)
        log_warning "Sistema operativo non riconosciuto: $OS_NAME"
        ;;
esac

echo

# Verifica prerequisiti
echo -e "${CYAN}🔧 VERIFICA PREREQUISITI${NC}"
echo "──────────────────────────"

# Verifica GCC
if command -v gcc >/dev/null 2>&1; then
    GCC_VERSION=$(gcc --version | head -n1)
    log_success "GCC trovato: $GCC_VERSION"
else
    log_error "GCC non trovato!"
    log_info "Installazione suggerita:"
    case "$OS_NAME" in
        "Linux")
            echo "  sudo apt update && sudo apt install build-essential  # Ubuntu/Debian"
            echo "  sudo yum groupinstall 'Development Tools'           # CentOS/RHEL"
            echo "  sudo pacman -S base-devel                           # Arch Linux"
            ;;
        "Darwin")
            echo "  xcode-select --install"
            echo "  # oppure installa Xcode dall'App Store"
            ;;
    esac
    echo
fi

# Verifica Make
if command -v make >/dev/null 2>&1; then
    MAKE_VERSION=$(make --version | head -n1)
    log_success "Make trovato: $MAKE_VERSION"
else
    log_warning "Make non trovato - verrà installato con build-essential"
fi

# Verifica Git
if command -v git >/dev/null 2>&1; then
    GIT_VERSION=$(git --version)
    log_success "Git trovato: $GIT_VERSION"
else
    log_warning "Git non trovato - utile per il version control"
fi

# Verifica editor
echo
log_info "Editor consigliati disponibili:"
editors=("code" "vim" "nano" "emacs" "gedit")
found_editors=()

for editor in "${editors[@]}"; do
    if command -v "$editor" >/dev/null 2>&1; then
        found_editors+=("$editor")
    fi
done

if [ ${#found_editors[@]} -gt 0 ]; then
    log_success "Editor trovati: ${found_editors[*]}"
else
    log_warning "Nessun editor comune trovato"
fi

echo

# Test di compilazione
echo -e "${CYAN}🧪 TEST DI COMPILAZIONE${NC}"
echo "────────────────────────"

# Crea un file di test temporaneo
cat > /tmp/test_c_setup.c << 'EOF'
#include <stdio.h>

int main() {
    printf("Setup test completato con successo!\n");
    return 0;
}
EOF

if gcc -o /tmp/test_c_setup /tmp/test_c_setup.c 2>/dev/null; then
    log_success "Compilazione di test riuscita"
    if /tmp/test_c_setup 2>/dev/null; then
        log_success "Esecuzione di test riuscita"
    else
        log_error "Esecuzione di test fallita"
    fi
    rm -f /tmp/test_c_setup /tmp/test_c_setup.c
else
    log_error "Compilazione di test fallita"
    rm -f /tmp/test_c_setup.c
fi

echo

# Struttura del corso
echo -e "${CYAN}📚 STRUTTURA DEL CORSO${NC}"
echo "───────────────────────"

COURSE_DIR="/home/git-projects/INFORMATICA_1/_C_by_example"
if [ -d "$COURSE_DIR" ]; then
    log_success "Directory del corso trovata: $COURSE_DIR"
    
    # Conta le lezioni
    lesson_count=$(find "$COURSE_DIR" -maxdepth 1 -type d -name "[0-9]*" | wc -l)
    log_info "Lezioni disponibili: $lesson_count"
    
    # Verifica struttura prima lezione
    if [ -d "$COURSE_DIR/01_Introduzione" ]; then
        log_success "Prima lezione configurata correttamente"
        
        # Test Makefile esempi
        if [ -f "$COURSE_DIR/01_Introduzione/esempi/Makefile" ]; then
            log_success "Makefile esempi presente"
        fi
        
        # Test Makefile esercizi
        if [ -f "$COURSE_DIR/01_Introduzione/esercizi/Makefile" ]; then
            log_success "Makefile esercizi presente"
        fi
    fi
else
    log_error "Directory del corso non trovata: $COURSE_DIR"
fi

echo

# Configurazione consigliata
echo -e "${CYAN}⚙️  CONFIGURAZIONE CONSIGLIATA${NC}"
echo "────────────────────────────────"

log_info "Configurazione Git (se non già fatto):"
echo "  git config --global user.name \"Il Tuo Nome\""
echo "  git config --global user.email \"tuo@email.com\""
echo

log_info "Alias utili per bash/zsh (~/.bashrc o ~/.zshrc):"
echo "  alias ccompile='gcc -Wall -Wextra -std=c99 -pedantic -g'"
echo "  alias crun='gcc -Wall -Wextra -std=c99 -pedantic -g -o temp && ./temp && rm temp'"
echo

# Primo test pratico
echo -e "${CYAN}🎯 PRIMO TEST PRATICO${NC}"
echo "────────────────────────"

log_info "Prova a compilare ed eseguire il primo esempio:"
echo "  cd $COURSE_DIR/01_Introduzione/esempi"
echo "  make hello_world"
echo "  make run-hello_world"
echo

# Riepilogo finale
echo -e "${PURPLE}"
echo "╔══════════════════════════════════════════════════════════════╗"
echo "║                        🎉 SETUP COMPLETATO! 🎉               ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo -e "${NC}"

log_success "L'ambiente è pronto per iniziare il corso C by Example!"
log_info "Prossimi passi:"
echo "  1. Leggi il README.md principale"
echo "  2. Inizia con la Lezione 01: Introduzione"
echo "  3. Studia la teoria, prova gli esempi, fai gli esercizi"
echo "  4. Usa il quiz per verificare la comprensione"
echo

log_info "Comandi utili:"
echo "  make help          # In ogni cartella esempi/esercizi"
echo "  make all           # Compila tutti gli esempi"
echo "  make test          # Testa la compilazione"
echo

echo -e "${GREEN}Buono studio e buon divertimento con il C! 🚀${NC}"
echo
