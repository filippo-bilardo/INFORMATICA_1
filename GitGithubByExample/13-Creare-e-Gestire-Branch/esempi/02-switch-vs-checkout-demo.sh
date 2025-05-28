#!/bin/bash

# ===================================================================
# SWITCH VS CHECKOUT - DIMOSTRAZIONE PRATICA
# ===================================================================
# Questo script confronta i comandi git switch e git checkout
# mostrando le differenze pratiche e i vantaggi del nuovo approccio
# Autore: Corso Git & GitHub
# Data: 2024

echo "🔄 === SWITCH VS CHECKOUT - DIMOSTRAZIONE ==="
echo

# ===================================================================
# VERIFICA VERSIONE GIT E SUPPORTO
# ===================================================================

echo "📋 === VERIFICA AMBIENTE ==="
echo

GIT_VERSION=$(git --version | cut -d' ' -f3)
echo "Versione Git corrente: $GIT_VERSION"

# Controlla se git switch è disponibile
if git switch --help >/dev/null 2>&1; then
    SWITCH_AVAILABLE=true
    echo "✅ git switch disponibile (Git 2.23+)"
else
    SWITCH_AVAILABLE=false
    echo "❌ git switch NON disponibile (Git < 2.23)"
    echo "💡 Aggiorna Git per usare i comandi moderni"
fi

# Controlla se git restore è disponibile
if git restore --help >/dev/null 2>&1; then
    RESTORE_AVAILABLE=true
    echo "✅ git restore disponibile (Git 2.23+)"
else
    RESTORE_AVAILABLE=false
    echo "❌ git restore NON disponibile (Git < 2.23)"
fi

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# PREPARAZIONE REPOSITORY
# ===================================================================

if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "📁 Inizializzazione repository demo..."
    git init switch-vs-checkout-demo
    cd switch-vs-checkout-demo
    
    git config user.name "Demo User"
    git config user.email "demo@example.com"
    
    # Setup iniziale con alcuni file
    echo "# Switch vs Checkout Demo" > README.md
    echo "app.js" > app.js
    echo "style.css" > style.css
    git add .
    git commit -m "Initial commit: setup demo project"
    
    echo "✅ Repository demo creato!"
    echo
fi

# ===================================================================
# 1. CONFRONTO CREAZIONE BRANCH
# ===================================================================

echo
echo "🌱 === CONFRONTO: CREAZIONE BRANCH ==="
echo

echo "📌 METODO TRADIZIONALE (checkout):"
echo "$ git checkout -b feature-checkout-demo"
git checkout -b feature-checkout-demo
echo "✅ Branch creato e attivato con checkout"

echo
echo "📌 Current branch:"
git branch | grep "*"

echo
echo "📌 METODO MODERNO (switch):"
if [ "$SWITCH_AVAILABLE" = true ]; then
    echo "$ git switch -c feature-switch-demo"
    git switch -c feature-switch-demo
    echo "✅ Branch creato e attivato con switch"
else
    echo "⚠️ git switch non disponibile, usando checkout"
    git checkout -b feature-switch-demo
fi

echo
echo "📌 Current branch:"
git branch | grep "*"

echo
echo "📌 Tutti i branch creati:"
git branch

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 2. CONFRONTO CAMBIO BRANCH
# ===================================================================

echo
echo "🔄 === CONFRONTO: CAMBIO BRANCH ==="
echo

echo "📌 METODO TRADIZIONALE (checkout):"
echo "$ git checkout main"
git checkout main
echo "Current branch: $(git branch | grep "*" | cut -c3-)"

echo
echo "$ git checkout feature-checkout-demo"
git checkout feature-checkout-demo
echo "Current branch: $(git branch | grep "*" | cut -c3-)"

echo
echo "📌 METODO MODERNO (switch):"
if [ "$SWITCH_AVAILABLE" = true ]; then
    echo "$ git switch main"
    git switch main
    echo "Current branch: $(git branch | grep "*" | cut -c3-)"
    
    echo
    echo "$ git switch feature-switch-demo"
    git switch feature-switch-demo
    echo "Current branch: $(git branch | grep "*" | cut -c3-)"
else
    echo "⚠️ git switch non disponibile, usando checkout"
    git checkout main
    git checkout feature-switch-demo
fi

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 3. DIMOSTRAZIONE ERRORI E SICUREZZA
# ===================================================================

echo
echo "⚠️ === SICUREZZA E GESTIONE ERRORI ==="
echo

echo "📌 Test: nome branch inesistente"
echo

echo "Con checkout (comportamento tradizionale):"
echo "$ git checkout nonexistent-branch"
if git checkout nonexistent-branch 2>/dev/null; then
    echo "😱 Checkout potrebbe aver creato il branch!"
    git branch -d nonexistent-branch 2>/dev/null
else
    echo "✅ Errore gestito correttamente"
fi

echo
if [ "$SWITCH_AVAILABLE" = true ]; then
    echo "Con switch (comportamento moderno):"
    echo "$ git switch nonexistent-branch"
    if git switch nonexistent-branch 2>/dev/null; then
        echo "😱 Questo non dovrebbe succedere!"
    else
        echo "✅ Switch fallisce in modo più prevedibile"
    fi
fi

echo
echo "📌 Test: autocompletamento e suggerimenti"
echo "checkout suggerisce: branch, file, commit, tag..."
echo "switch suggerisce: solo branch"
echo "(Prova nel tuo terminale: git checkout <TAB> vs git switch <TAB>)"

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 4. OPERAZIONI SU FILE: CHECKOUT VS RESTORE
# ===================================================================

echo
echo "📁 === OPERAZIONI SU FILE: CHECKOUT VS RESTORE ==="
echo

# Modifichiamo alcuni file
echo
echo "📌 Modifico alcuni file per la dimostrazione..."
echo "Modified content" >> app.js
echo "Modified styles" >> style.css
echo "New file" > temp.txt

echo "File modificati:"
git status --porcelain

echo
echo "📌 METODO TRADIZIONALE (checkout per file):"
echo "$ git checkout -- app.js"
git checkout -- app.js
echo "✅ app.js ripristinato"

echo "Status dopo checkout:"
git status --porcelain

echo
echo "📌 METODO MODERNO (restore):"
if [ "$RESTORE_AVAILABLE" = true ]; then
    echo "$ git restore style.css"
    git restore style.css
    echo "✅ style.css ripristinato"
else
    echo "⚠️ git restore non disponibile, usando checkout"
    git checkout -- style.css
fi

echo "Status finale:"
git status --porcelain

# Cleanup temp file
rm -f temp.txt 2>/dev/null

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 5. STAGING AREA: CHECKOUT VS RESTORE
# ===================================================================

echo
echo "📦 === STAGING AREA: OPERAZIONI ==="
echo

echo "📌 Aggiungo file alla staging area..."
echo "Staged content" > staged-file.txt
git add staged-file.txt

echo "Staging area:"
git status --porcelain

echo
echo "📌 METODO TRADIZIONALE (checkout per unstage):"
echo "$ git checkout HEAD -- staged-file.txt"
# Nota: questo non unstage, ma sovrascrive
echo "(checkout HEAD non è il modo migliore per unstage)"

echo
echo "📌 METODO MODERNO (restore per unstage):"
if [ "$RESTORE_AVAILABLE" = true ]; then
    echo "$ git restore --staged staged-file.txt"
    git restore --staged staged-file.txt
    echo "✅ File rimosso dalla staging area"
else
    echo "⚠️ git restore non disponibile, usando reset"
    git reset HEAD staged-file.txt
fi

echo "Status dopo unstage:"
git status --porcelain

# Cleanup
rm -f staged-file.txt 2>/dev/null

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 6. WORKFLOW COMPARISON
# ===================================================================

echo
echo "🔄 === CONFRONTO WORKFLOW COMPLETO ==="
echo

echo "📌 WORKFLOW TRADIZIONALE (tutto con checkout):"
echo "1. git checkout main                    # cambia branch"
echo "2. git checkout -b feature-traditional  # crea e cambia"
echo "3. # ... sviluppo ..."
echo "4. git checkout -- file.txt             # ripristina file"
echo "5. git checkout main                    # torna a main"
echo "6. git merge feature-traditional        # merge"
echo "7. git branch -d feature-traditional    # cleanup"

echo
echo "📌 WORKFLOW MODERNO (comandi specifici):"
echo "1. git switch main                      # cambia branch"
echo "2. git switch -c feature-modern         # crea e cambia"  
echo "3. # ... sviluppo ..."
echo "4. git restore file.txt                 # ripristina file"
echo "5. git switch main                      # torna a main"
echo "6. git merge feature-modern             # merge"
echo "7. git branch -d feature-modern         # cleanup"

echo
echo "📌 DIMOSTRAZIONE PRATICA:"

echo
echo "Workflow tradizionale:"
git switch main 2>/dev/null || git checkout main
git checkout -b demo-traditional
echo "Traditional workflow" > demo.txt
git add demo.txt
git commit -m "Demo: traditional workflow"
git checkout main
git merge demo-traditional
git branch -d demo-traditional

echo
echo "Workflow moderno:"
if [ "$SWITCH_AVAILABLE" = true ]; then
    git switch -c demo-modern
    echo "Modern workflow" > demo2.txt
    git add demo2.txt
    git commit -m "Demo: modern workflow"
    git switch main
    git merge demo-modern
    git branch -d demo-modern
else
    echo "⚠️ Usando metodo tradizionale (git switch non disponibile)"
fi

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 7. CONFIGURAZIONE E MIGRAZIONE
# ===================================================================

echo
echo "⚙️ === CONFIGURAZIONE E MIGRAZIONE ==="
echo

echo "📌 Alias suggeriti per facilitare transizione:"
echo
echo "git config --global alias.sw 'switch'"
echo "git config --global alias.swc 'switch -c'"
echo "git config --global alias.co 'checkout'   # mantieni per casi speciali"
echo "git config --global alias.rs 'restore'"

echo
echo "📌 Controllo configurazione attuale:"
echo "Alias switch: $(git config --global alias.sw 2>/dev/null || echo 'non configurato')"
echo "Alias checkout: $(git config --global alias.co 2>/dev/null || echo 'non configurato')"

echo
echo "📌 Vuoi configurare gli alias? (y/n)"
read -p "> " SETUP_ALIASES

if [ "$SETUP_ALIASES" = "y" ] || [ "$SETUP_ALIASES" = "Y" ]; then
    git config --global alias.sw 'switch'
    git config --global alias.swc 'switch -c'
    git config --global alias.rs 'restore'
    echo "✅ Alias configurati!"
    echo "Ora puoi usare: git sw, git swc, git rs"
fi

echo
read -p "Premi INVIO per il riepilogo..."

# ===================================================================
# RIEPILOGO E RACCOMANDAZIONI
# ===================================================================

echo
echo "📊 === RIEPILOGO E RACCOMANDAZIONI ==="
echo

echo "✅ Caratteristiche dimostrate:"
echo "   🔄 Creazione branch: checkout -b vs switch -c"
echo "   🔄 Cambio branch: checkout vs switch"
echo "   📁 Ripristino file: checkout -- vs restore"
echo "   📦 Unstaging: checkout HEAD vs restore --staged"
echo "   ⚠️ Gestione errori e sicurezza"
echo "   🔧 Configurazione alias"

echo
echo "💡 RACCOMANDAZIONI:"
echo

if [ "$SWITCH_AVAILABLE" = true ]; then
    echo "✅ Git 2.23+ disponibile - USA I COMANDI MODERNI:"
    echo "   • git switch per operazioni sui branch"
    echo "   • git restore per operazioni sui file"
    echo "   • git checkout solo per navigazione commit"
else
    echo "⚠️ Git < 2.23 - AGGIORNA QUANDO POSSIBILE:"
    echo "   • Continua con git checkout per ora"
    echo "   • Pianifica aggiornamento a Git 2.23+"
    echo "   • Preparati alla transizione"
fi

echo
echo "📈 PIANO DI MIGRAZIONE SUGGERITO:"
echo "   1. Settimana 1: Usa switch solo per cambiare branch"
echo "   2. Settimana 2: Usa switch -c per creare branch"
echo "   3. Settimana 3: Introduci restore per file"
echo "   4. Settimana 4: Configura alias e workflow completo"

echo
echo "🎯 CHEAT SHEET:"
echo "   Cambiare branch:     git switch branch-name"
echo "   Creare branch:       git switch -c new-branch"
echo "   Ripristinare file:   git restore file.txt"
echo "   Unstage file:        git restore --staged file.txt"
echo "   Navigare commit:     git checkout commit-hash"

echo
echo "✨ Demo completata!"
echo "Repository demo: $(pwd)"
echo "Esplora ulteriormente con: git log --oneline --graph --all"
