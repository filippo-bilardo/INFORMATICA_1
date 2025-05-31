#!/bin/bash

# ==============================================
# 📥 DEMO AVANZATA: Strategie di Pull
# ==============================================
# Questo script dimostra le diverse strategie
# di pull e come gestire situazioni complesse

echo "🔄 Demo: Strategie di Pull Avanzate"
echo "==================================="

# Pulizia ambiente di test
echo "🧹 Pulizia ambiente di test..."
rm -rf pull-demo-remote pull-demo-local pull-demo-dev 2>/dev/null

# ==============================================
# SETUP: Repository di Test
# ==============================================
echo -e "\n📦 SETUP: Creazione Repository di Test"
echo "======================================"

# Repository remoto simulato
mkdir pull-demo-remote
cd pull-demo-remote
git init --bare
cd ..

# Repository locale principale
git clone pull-demo-remote pull-demo-local
cd pull-demo-local

git config user.name "Main Developer"
git config user.email "main@example.com"

# Setup iniziale
echo "# Demo Pull Strategies" > README.md
echo "Repository per testare strategie di pull" >> README.md

cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World!")
    
if __name__ == "__main__":
    main()
EOF

git add .
git commit -m "Initial: Add README and basic app"
git push origin main

cd ..

# Clone per secondo sviluppatore
git clone pull-demo-remote pull-demo-dev
cd pull-demo-dev
git config user.name "Second Developer"
git config user.email "dev@example.com"
cd ..

echo "✅ Setup completato"

# ==============================================
# SCENARIO 1: Pull Fast-Forward
# ==============================================
echo -e "\n🚀 SCENARIO 1: Pull Fast-Forward"
echo "================================"

cd pull-demo-local

echo -e "\n📝 Main Developer aggiunge feature:"
echo "def add_numbers(a, b):" >> app.py
echo "    return a + b" >> app.py
echo "" >> app.py

git add app.py
git commit -m "Add: add_numbers function"
git push origin main

cd ..

echo -e "\n📥 Second Developer fa pull (fast-forward):"
cd pull-demo-dev

echo "📊 Stato prima del pull:"
git log --oneline --graph -2

echo -e "\n⏩ Eseguendo git pull..."
git pull origin main

echo -e "\n📊 Stato dopo il pull:"
git log --oneline --graph -3

echo "✅ Fast-forward completato - storia lineare mantenuta"

cd ..

# ==============================================
# SCENARIO 2: Pull con Merge
# ==============================================
echo -e "\n🔀 SCENARIO 2: Pull con Merge"
echo "============================="

# Main Developer aggiunge modifiche
cd pull-demo-local
echo -e "\n📝 Main Developer aggiunge documentazione:"
cat >> README.md << 'EOF'

## Funzioni Disponibili
- main(): Funzione principale
- add_numbers(a, b): Somma due numeri
EOF

git add README.md
git commit -m "Docs: Add function documentation"
git push origin main

cd ..

# Second Developer fa modifiche locali
cd pull-demo-dev
echo -e "\n📝 Second Developer aggiunge test:"
cat > test_app.py << 'EOF'
import app

def test_add_numbers():
    result = app.add_numbers(2, 3)
    assert result == 5
    print("Test passed!")

if __name__ == "__main__":
    test_add_numbers()
EOF

git add test_app.py
git commit -m "Add: Basic tests for app"

echo -e "\n📊 Stato locale prima del pull:"
git log --oneline --graph -3

echo -e "\n🔀 Eseguendo git pull (creerà merge commit)..."
git pull origin main

echo -e "\n📊 Stato dopo il pull con merge:"
git log --oneline --graph -5

echo "✅ Pull con merge completato - merge commit creato"

cd ..

# ==============================================
# SCENARIO 3: Pull con Rebase
# ==============================================
echo -e "\n📈 SCENARIO 3: Pull con Rebase"
echo "=============================="

# Main Developer aggiunge altra funzionalità
cd pull-demo-local
git pull origin main  # Sincronizza prima

echo -e "\n📝 Main Developer aggiunge moltiplicazione:"
echo "def multiply_numbers(a, b):" >> app.py
echo "    return a * b" >> app.py

git add app.py
git commit -m "Add: multiply_numbers function"
git push origin main

cd ..

# Second Developer fa modifiche locali che farà rebase
cd pull-demo-dev
echo -e "\n📝 Second Developer migliora i test:"
cat >> test_app.py << 'EOF'

def test_main():
    # Test che main() non crashi
    try:
        app.main()
        print("Main function test passed!")
    except Exception as e:
        print(f"Main function test failed: {e}")

if __name__ == "__main__":
    test_add_numbers()
    test_main()
EOF

git add test_app.py
git commit -m "Improve: Add test for main function"

echo -e "\n📊 Stato prima del pull con rebase:"
git log --oneline --graph -4

echo -e "\n📈 Eseguendo git pull --rebase..."
git pull --rebase origin main

echo -e "\n📊 Stato dopo il pull con rebase:"
git log --oneline --graph -6

echo "✅ Pull con rebase completato - storia lineare"

cd ..

# ==============================================
# SCENARIO 4: Pull con Conflitti
# ==============================================
echo -e "\n⚔️  SCENARIO 4: Pull con Conflitti"
echo "================================="

# Main Developer modifica app.py
cd pull-demo-local
git pull origin main  # Sincronizza

echo -e "\n📝 Main Developer modifica main function:"
# Sovrascrivi app.py con una versione modificata
cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World! Welcome to our app!")
    print("This app demonstrates Git pull strategies")
    
def add_numbers(a, b):
    return a + b

def multiply_numbers(a, b):
    return a * b
EOF

git add app.py
git commit -m "Enhance: Improve main function output"
git push origin main

cd ..

# Second Developer modifica la stessa parte
cd pull-demo-dev
echo -e "\n📝 Second Developer modifica ANCHE main function:"

# Crea una versione conflittuale
cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World!")
    print("Starting application...")
    
def add_numbers(a, b):
    return a + b

def multiply_numbers(a, b):
    return a * b
EOF

git add app.py
git commit -m "Update: Add startup message to main"

echo -e "\n📊 Stato prima del pull (che causerà conflitto):"
git log --oneline --graph -3

echo -e "\n⚔️  Eseguendo git pull (causerà conflitto)..."
if git pull origin main 2>&1 | grep -q "CONFLICT"; then
    echo "🚨 Conflitto rilevato!"
    echo -e "\n📄 File in conflitto:"
    git status --porcelain | grep "^UU"
    
    echo -e "\n📝 Contenuto del conflitto in app.py:"
    echo "=====================================Automaticamente risolvendo il conflitto..."
    
    # Risoluzione automatica per la demo (in realtà dovrebbe essere manuale)
    cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World! Welcome to our app!")
    print("Starting application...")
    print("This app demonstrates Git pull strategies")
    
def add_numbers(a, b):
    return a + b

def multiply_numbers(a, b):
    return a * b
EOF
    
    echo "✅ Conflitto risolto manualmente"
    git add app.py
    git commit -m "Merge: Resolve conflict in main function"
    
    echo -e "\n📊 Stato dopo risoluzione conflitto:"
    git log --oneline --graph -5
else
    echo "⚠️  Nessun conflitto - merge automatico riuscito"
fi

cd ..

# ==============================================
# SCENARIO 5: Pull --ff-only
# ==============================================
echo -e "\n⏩ SCENARIO 5: Pull --ff-only (Solo Fast-Forward)"
echo "=============================================="

cd pull-demo-local
git pull origin main  # Sincronizza

echo -e "\n📝 Main Developer aggiunge utility:"
cat > utils.py << 'EOF'
def divide_numbers(a, b):
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

def subtract_numbers(a, b):
    return a - b
EOF

git add utils.py
git commit -m "Add: Utility functions"
git push origin main

cd ..

cd pull-demo-dev
echo -e "\n📝 Second Developer fa modifiche locali:"
echo "# Test utilities" > test_utils.py
git add test_utils.py
git commit -m "Add: Placeholder for utility tests"

echo -e "\n⏩ Tentativo di pull --ff-only (fallirà):"
if git pull --ff-only origin main 2>&1 | grep -q "fatal"; then
    echo "❌ Pull --ff-only fallito - divergenza rilevata"
    echo "💡 Necessario merge o rebase"
    
    echo -e "\n🔄 Facendo pull normale invece:"
    git pull origin main
    echo "✅ Pull normale completato"
else
    echo "✅ Fast-forward riuscito"
fi

cd ..

# ==============================================
# SCENARIO 6: Configurazioni Pull
# ==============================================
echo -e "\n⚙️  SCENARIO 6: Configurazioni Pull"
echo "=================================="

cd pull-demo-dev

echo -e "\n📋 Configurazioni pull correnti:"
echo "pull.rebase: $(git config pull.rebase || echo 'non impostato')"
echo "pull.ff: $(git config pull.ff || echo 'non impostato')"

echo -e "\n⚙️  Impostando configurazioni diverse:"

# Test configurazione rebase
echo "🔸 Configurando pull.rebase = true"
git config pull.rebase true

echo "🔸 Configurando rebase.autoStash = true"
git config rebase.autoStash true

echo -e "\n📋 Nuove configurazioni:"
echo "pull.rebase: $(git config pull.rebase)"
echo "rebase.autoStash: $(git config rebase.autoStash)"

cd ..

# ==============================================
# SCENARIO 7: Pull con Stash Automatico
# ==============================================
echo -e "\n💾 SCENARIO 7: Pull con Stash Automatico"
echo "======================================="

cd pull-demo-local
echo -e "\n📝 Main Developer aggiunge config:"
cat > config.json << 'EOF'
{
  "app_name": "Pull Demo",
  "version": "1.0.0",
  "debug": false
}
EOF

git add config.json
git commit -m "Add: Application configuration"
git push origin main

cd ..

cd pull-demo-dev
echo -e "\n📝 Second Developer fa modifiche NON committate:"
echo "print('Debug mode enabled')" >> app.py

echo -e "\n📊 Stato con modifiche non committate:"
git status --porcelain

echo -e "\n💾 Pull con autostash (grazie alla configurazione):"
git pull origin main

echo -e "\n📊 Stato dopo pull con autostash:"
git status --porcelain

if git status --porcelain | grep -q "app.py"; then
    echo "✅ Modifiche locali preservate automaticamente"
else
    echo "⚠️  Modifiche locali potrebbero essere in stash"
    echo "📦 Stash list:"
    git stash list
fi

cd ..

# ==============================================
# RIEPILOGO E PULIZIA
# ==============================================
echo -e "\n📊 RIEPILOGO STRATEGIE TESTATE"
echo "=============================="
echo "✅ Fast-Forward Pull    - Storia lineare, nessun merge commit"
echo "✅ Merge Pull          - Crea merge commit, preserva branching"
echo "✅ Rebase Pull         - Riapplica commit, storia lineare"
echo "✅ Conflitti           - Risoluzione manuale necessaria"
echo "✅ FF-Only Pull        - Sicuro ma può fallire"
echo "✅ Auto-Stash Pull     - Gestione automatica modifiche"

echo -e "\n🎯 QUALE STRATEGIA USARE?"
echo "========================"
echo "🔸 Fast-Forward: Quando il locale è indietro"
echo "🔸 Merge: Per preservare la storia di branching"
echo "🔸 Rebase: Per mantenere storia lineare"
echo "🔸 FF-Only: Per evitare merge indesiderati"

echo -e "\n⚙️  CONFIGURAZIONI CONSIGLIATE"
echo "=============================="
echo "# Per principianti (default sicuro):"
echo "git config pull.rebase false"
echo ""
echo "# Per storia lineare:"
echo "git config pull.rebase true"
echo "git config rebase.autoStash true"
echo ""
echo "# Per massima sicurezza:"
echo "git config pull.ff only"

echo -e "\n🧹 Pulizia"
echo "=========="
echo "Per pulire: rm -rf pull-demo-remote pull-demo-local pull-demo-dev"

echo -e "\n✨ Demo delle strategie di pull completata!"
