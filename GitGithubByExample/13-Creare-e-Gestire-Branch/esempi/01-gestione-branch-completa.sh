#!/bin/bash

# ===================================================================
# GESTIONE BRANCH - ESEMPI PRATICI
# ===================================================================
# Questo script dimostra le operazioni fondamentali sui branch in Git
# Autore: Corso Git & GitHub
# Data: 2024

echo "🌿 === GESTIONE BRANCH IN GIT ==="
echo

# ===================================================================
# PREPARAZIONE REPOSITORY DI ESEMPIO
# ===================================================================

# Verifica se siamo in un repository Git
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "📁 Inizializzazione repository di esempio..."
    git init branch-example
    cd branch-example
    
    # Setup iniziale
    git config user.name "Demo User"
    git config user.email "demo@example.com"
    
    # Primo commit
    echo "# Branch Management Demo" > README.md
    echo "Questo repository dimostra la gestione dei branch" >> README.md
    git add README.md
    git commit -m "Initial commit: setup repository"
    
    echo "✅ Repository inizializzato con successo!"
    echo
fi

# ===================================================================
# 1. VISUALIZZAZIONE BRANCH
# ===================================================================

echo "📋 === VISUALIZZAZIONE BRANCH ==="
echo

echo "📌 Branch locali:"
git branch

echo
echo "📌 Branch con dettagli (-v):"
git branch -v

echo
echo "📌 Tutti i branch (locali e remoti):"
git branch -a

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 2. CREAZIONE BRANCH
# ===================================================================

echo
echo "🌱 === CREAZIONE BRANCH ==="
echo

echo "📌 Creazione branch 'feature-user-auth':"
git branch feature-user-auth
git branch

echo
echo "📌 Creazione e switch a 'feature-shopping-cart':"
git switch -c feature-shopping-cart

echo "Branch attuale:"
git branch

echo
echo "📌 Creazione branch da commit specifico:"
# Torniamo a main per avere un punto di riferimento
git switch main

# Aggiungiamo un commit per avere storia
echo "Feature: Basic authentication" > auth.md
git add auth.md
git commit -m "Add basic authentication docs"

# Creiamo branch dal commit precedente
PREV_COMMIT=$(git rev-parse HEAD~1)
echo "Creazione 'hotfix-from-previous' dal commit: $PREV_COMMIT"
git branch hotfix-from-previous $PREV_COMMIT

git branch -v

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 3. NAVIGAZIONE TRA BRANCH
# ===================================================================

echo
echo "🔄 === NAVIGAZIONE TRA BRANCH ==="
echo

echo "📌 Switch tra branch diversi:"
echo "Passaggio a feature-user-auth..."
git switch feature-user-auth

echo "Branch attuale:"
git branch | grep "*"

echo
echo "📌 Aggiunta contenuto al branch feature:"
echo "class UserAuth {}" > user-auth.js
echo "Authentication module" > user-auth.md
git add .
git commit -m "Add UserAuth class and documentation"

echo "📌 Passaggio a feature-shopping-cart:"
git switch feature-shopping-cart

echo "📌 Aggiunta contenuto al branch shopping-cart:"
echo "class ShoppingCart {}" > shopping-cart.js
echo "Shopping cart module" > cart.md
git add .
git commit -m "Add ShoppingCart class and documentation"

echo
echo "📌 Visualizzazione file diversi per branch:"
echo "File nel branch feature-shopping-cart:"
ls -la *.js *.md

git switch feature-user-auth
echo
echo "File nel branch feature-user-auth:"
ls -la *.js *.md

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 4. RINOMINARE BRANCH
# ===================================================================

echo
echo "✏️ === RINOMINAZIONE BRANCH ==="
echo

git switch feature-user-auth

echo "📌 Branch prima della rinominazione:"
git branch

echo
echo "📌 Rinominazione del branch corrente:"
echo "Rinomino 'feature-user-auth' in 'feature-authentication'..."
git branch -m feature-authentication

echo "📌 Branch dopo la rinominazione:"
git branch

echo
echo "📌 Rinominazione di un altro branch:"
echo "Rinomino 'feature-shopping-cart' in 'feature-cart-management'..."
git branch -m feature-shopping-cart feature-cart-management

git branch

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 5. MERGE E CLEANUP
# ===================================================================

echo
echo "🔀 === MERGE E PULIZIA BRANCH ==="
echo

echo "📌 Merge di feature-authentication in main:"
git switch main
git merge feature-authentication

echo
echo "📌 Verifica del merge:"
git log --oneline -5

echo
echo "📌 Branch mergeati:"
git branch --merged

echo
echo "📌 Branch non mergeati:"
git branch --no-merged

echo
echo "📌 Eliminazione branch mergeato:"
echo "Elimino 'feature-authentication' (già mergeato)..."
git branch -d feature-authentication

echo "📌 Branch rimanenti:"
git branch

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 6. GESTIONE BRANCH REMOTI (SIMULAZIONE)
# ===================================================================

echo
echo "🌐 === SIMULAZIONE BRANCH REMOTI ==="
echo

# Creiamo un "remote" locale per simulare
echo "📌 Setup remote di test (simulazione)..."
git remote add origin https://github.com/example/branch-demo.git 2>/dev/null || echo "Remote già esistente"

echo
echo "📌 Push di branch locale (simulazione):"
echo "git push -u origin feature-cart-management"
echo "(In uno scenario reale, questo pushrebbe su GitHub/GitLab)"

echo
echo "📌 Creazione branch da remoto (simulazione):"
echo "git switch -c local-feature origin/remote-feature"
echo "(Questo creerebbe un branch locale che traccia uno remoto)"

echo
echo "📌 Eliminazione branch remoto (simulazione):"
echo "git push origin --delete old-feature-branch"
echo "(Questo eliminerebbe il branch dal server remoto)"

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 7. BEST PRACTICES DEMO
# ===================================================================

echo
echo "💡 === BEST PRACTICES DIMOSTRATE ==="
echo

echo "📌 1. Naming Convention Examples:"
echo "   ✅ feature/user-authentication"
echo "   ✅ bugfix/login-validation-error"
echo "   ✅ hotfix/security-patch-2024"
echo "   ✅ release/v1.2.0"
echo "   ❌ temp, fix, my-branch, test123"

echo
echo "📌 2. Workflow Example:"
git switch main
echo "   - Sempre iniziare da main aggiornato"

git switch -c feature-payment-integration
echo "   - Creare branch con nome descrittivo"

echo "   - Sviluppare feature..."
echo "Payment integration module" > payment.js
git add payment.js
git commit -m "feat: add payment integration module"

git switch main
echo "   - Tornare a main per merge"

git merge feature-payment-integration
echo "   - Merge della feature"

git branch -d feature-payment-integration
echo "   - Cleanup: eliminare branch mergeato"

echo
echo "📌 3. Branch Status Check:"
git branch -v
echo
echo "📌 4. Storia del repository:"
git log --oneline --graph -10

echo
read -p "Premi INVIO per continuare..."

# ===================================================================
# 8. COMANDI MODERNI VS TRADIZIONALI
# ===================================================================

echo
echo "🆕 === COMANDI MODERNI VS TRADIZIONALI ==="
echo

echo "📌 Confronto Checkout vs Switch:"
echo
echo "   TRADIZIONALE (checkout):"
echo "   git checkout main              # cambia branch"
echo "   git checkout -b new-feature    # crea e cambia"
echo "   git checkout -- file.txt       # ripristina file"
echo
echo "   MODERNO (switch + restore):"
echo "   git switch main                # cambia branch"
echo "   git switch -c new-feature      # crea e cambia"
echo "   git restore file.txt           # ripristina file"

echo
echo "📌 Dimostrazione switch vs checkout:"

# Verifica versione Git
GIT_VERSION=$(git --version | cut -d' ' -f3)
echo "Versione Git corrente: $GIT_VERSION"

if git switch --help >/dev/null 2>&1; then
    echo "✅ Git Switch disponibile - usa comandi moderni!"
    
    echo "Demo con git switch:"
    git switch -c demo-modern-branch
    echo "File per demo moderno" > modern.txt
    git add modern.txt
    git commit -m "Demo: modern git commands"
    git switch main
    git branch -d demo-modern-branch
else
    echo "⚠️ Git Switch non disponibile - aggiorna Git alla versione 2.23+"
    echo "Usando git checkout (metodo tradizionale):"
    git checkout -b demo-traditional-branch
    echo "File per demo tradizionale" > traditional.txt
    git add traditional.txt
    git commit -m "Demo: traditional git commands"
    git checkout main
    git branch -d demo-traditional-branch
fi

echo
read -p "Premi INVIO per il riepilogo finale..."

# ===================================================================
# RIEPILOGO FINALE
# ===================================================================

echo
echo "📊 === RIEPILOGO OPERAZIONI ESEGUITE ==="
echo

echo "✅ Operazioni completate:"
echo "   1. ✓ Creazione repository di esempio"
echo "   2. ✓ Visualizzazione branch (locale e remoto)"
echo "   3. ✓ Creazione branch multipli"
echo "   4. ✓ Navigazione tra branch"
echo "   5. ✓ Aggiunta contenuti specifici per branch"
echo "   6. ✓ Rinominazione branch"
echo "   7. ✓ Merge e eliminazione branch"
echo "   8. ✓ Dimostrazione best practices"
echo "   9. ✓ Confronto comandi moderni vs tradizionali"

echo
echo "📈 Stato finale del repository:"
git branch -v

echo
echo "📜 Storia del repository:"
git log --oneline --graph -8

echo
echo "📚 Concetti dimostrati:"
echo "   • Creazione e gestione branch"
echo "   • Workflow feature branch"
echo "   • Naming conventions"
echo "   • Operazioni di merge e cleanup"
echo "   • Differenze tra git switch e git checkout"
echo "   • Best practices per la gestione branch"

echo
echo "🎯 Prossimi passi suggeriti:"
echo "   1. Pratica con repository reale"
echo "   2. Configura alias per comandi frequenti"
echo "   3. Studia workflow avanzati (Git Flow, GitHub Flow)"
echo "   4. Impara gestione conflitti di merge"

echo
echo "✨ Demo completata! Repository di esempio creato in: $(pwd)"
echo "   Puoi esplorare ulteriormente con: git log --graph --all --oneline"
