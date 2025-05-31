#!/bin/bash

# ==============================================
# 🔀 DEMO COMPLETA: Merge e Strategie
# ==============================================
# Questo script dimostra tutti i tipi di merge
# e le situazioni più comuni che si possono incontrare

echo "🔀 Demo: Merge e Strategie Complete"
echo "=================================="

# Pulizia ambiente di test
echo "🧹 Pulizia ambiente di test..."
rm -rf merge-demo 2>/dev/null

# ==============================================
# SETUP: Repository di Test
# ==============================================
echo -e "\n📦 SETUP: Creazione Repository"
echo "============================="

mkdir merge-demo
cd merge-demo
git init

# Configura utente
git config user.name "Merge Demo"
git config user.email "demo@example.com"

# Commit iniziale
echo "# Progetto Demo Merge" > README.md
echo "Repository per dimostrare i tipi di merge" >> README.md

cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World!")

if __name__ == "__main__":
    main()
EOF

git add .
git commit -m "Initial commit: Basic project setup"

echo "✅ Repository inizializzato"

# ==============================================
# SCENARIO 1: Fast-Forward Merge
# ==============================================
echo -e "\n🚀 SCENARIO 1: Fast-Forward Merge"
echo "================================="

echo -e "\n📊 Stato iniziale:"
git log --oneline --graph

# Crea branch per feature
git checkout -b feature/add-greeting
echo "✅ Creato branch feature/add-greeting"

# Sviluppa feature su branch separato
echo -e "\n📝 Sviluppo feature greeting:"
cat >> app.py << 'EOF'

def greet(name):
    return f"Hello, {name}!"

def greet_multiple(names):
    return [greet(name) for name in names]
EOF

git add app.py
git commit -m "Add: greeting functions"

# Aggiungi documentazione
cat >> README.md << 'EOF'

## Funzioni
- `greet(name)`: Saluta una persona
- `greet_multiple(names)`: Saluta più persone
EOF

git add README.md
git commit -m "Docs: Add function documentation"

echo -e "\n📊 Stato del branch feature:"
git log --oneline --graph

# Torna a main e fai merge
echo -e "\n🔄 Tornando a main per merge:"
git checkout main

echo -e "\n📊 Stato main prima del merge:"
git log --oneline --graph

echo -e "\n⏩ Eseguendo Fast-Forward merge:"
git merge feature/add-greeting

echo -e "\n📊 Stato dopo Fast-Forward merge:"
git log --oneline --graph
echo "✅ Fast-Forward merge completato - storia lineare"

# Cleanup
git branch -d feature/add-greeting

# ==============================================
# SCENARIO 2: Three-Way Merge (True Merge)
# ==============================================
echo -e "\n🔀 SCENARIO 2: Three-Way Merge"
echo "=============================="

# Crea modifiche su main
echo -e "\n📝 Modifiche su main (master):"
cat > config.py << 'EOF'
# Configuration file
DEBUG = False
VERSION = "1.0.0"
EOF

git add config.py
git commit -m "Add: configuration file"

# Crea branch per nuova feature
git checkout -b feature/add-math
echo "✅ Creato branch feature/add-math"

# Sviluppa feature matematica
echo -e "\n📝 Sviluppo feature math:"
cat > math_utils.py << 'EOF'
def add(a, b):
    return a + b

def multiply(a, b):
    return a * b

def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n - 1)
EOF

git add math_utils.py
git commit -m "Add: mathematical utility functions"

# Aggiorna main app per usare math
cat >> app.py << 'EOF'

# Import math utilities
try:
    from math_utils import add, multiply
    
    def demo_math():
        print(f"2 + 3 = {add(2, 3)}")
        print(f"4 * 5 = {multiply(4, 5)}")
        
except ImportError:
    def demo_math():
        print("Math utilities not available")
EOF

git add app.py
git commit -m "Integrate: math utilities in main app"

echo -e "\n📊 Stato branch feature/add-math:"
git log --oneline --graph

# Torna a main e fai altre modifiche (per forzare three-way merge)
echo -e "\n🔄 Tornando a main per modifiche parallele:"
git checkout main

echo -e "\n📝 Modifiche parallele su main:"
cat >> config.py << 'EOF'

# App settings
APP_NAME = "Merge Demo App"
LOG_LEVEL = "INFO"
EOF

git add config.py
git commit -m "Extend: configuration with app settings"

echo -e "\n📊 Stato main con modifiche parallele:"
git log --oneline --graph

echo -e "\n🔀 Eseguendo Three-Way merge:"
git merge feature/add-math -m "Merge: Add mathematical utilities

This merge brings mathematical functions:
- add(a, b): Addition
- multiply(a, b): Multiplication  
- factorial(n): Factorial calculation

The integration is complete and tested."

echo -e "\n📊 Stato dopo Three-Way merge:"
git log --oneline --graph --all

echo "✅ Three-Way merge completato - merge commit creato"

# Cleanup
git branch -d feature/add-math

# ==============================================
# SCENARIO 3: Merge con Conflitti
# ==============================================
echo -e "\n⚔️  SCENARIO 3: Merge con Conflitti"
echo "=================================="

# Crea branch per feature che causerà conflitto
git checkout -b feature/improve-app
echo "✅ Creato branch feature/improve-app"

# Modifica app.py sul branch
echo -e "\n📝 Modifiche su feature branch:"
cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Welcome to Merge Demo App!")
    print("This is an improved version")
    demo_math()
    interactive_demo()

def greet(name):
    return f"Hello, {name}! Welcome to our app!"

def greet_multiple(names):
    return [greet(name) for name in names]

def interactive_demo():
    name = input("What's your name? ")
    print(greet(name))

# Import math utilities
try:
    from math_utils import add, multiply
    
    def demo_math():
        print("=== Math Demo ===")
        print(f"2 + 3 = {add(2, 3)}")
        print(f"4 * 5 = {multiply(4, 5)}")
        
except ImportError:
    def demo_math():
        print("Math utilities not available")

if __name__ == "__main__":
    main()
EOF

git add app.py
git commit -m "Improve: Enhanced main app with interactive features"

# Torna a main e fai modifiche conflittuali
echo -e "\n🔄 Tornando a main per modifiche conflittuali:"
git checkout main

echo -e "\n📝 Modifiche conflittuali su main:"
cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Hello, World! - Production Version")
    print("Version 1.0.0")
    demo_math()
    show_config()

def greet(name):
    return f"Hello, {name}!"

def greet_multiple(names):
    return [greet(name) for name in names]

def show_config():
    try:
        import config
        print(f"App: {config.APP_NAME}")
        print(f"Version: {config.VERSION}")
    except ImportError:
        print("Configuration not available")

# Import math utilities
try:
    from math_utils import add, multiply
    
    def demo_math():
        print("Math functions available:")
        print(f"Example: 2 + 3 = {add(2, 3)}")
        print(f"Example: 4 * 5 = {multiply(4, 5)}")
        
except ImportError:
    def demo_math():
        print("Math utilities not available")

if __name__ == "__main__":
    main()
EOF

git add app.py
git commit -m "Production: Stable version with config integration"

echo -e "\n📊 Stato prima del merge conflittuale:"
git log --oneline --graph --all -5

echo -e "\n⚔️  Tentando merge che causerà conflitto:"
if git merge feature/improve-app; then
    echo "⚠️  Merge riuscito inaspettatamente"
else
    echo "🚨 Conflitto rilevato come previsto!"
    
    echo -e "\n📄 File in conflitto:"
    git status --porcelain
    
    echo -e "\n🔍 Contenuto del conflitto:"
    echo "=========================="
    head -20 app.py
    echo "... [conflitto continua] ..."
    
    echo -e "\n🛠️  Risoluzione automatica del conflitto per la demo:"
    cat > app.py << 'EOF'
#!/usr/bin/env python3

def main():
    print("Welcome to Merge Demo App! - Production Version")
    print("Version 1.0.0 - Enhanced Edition")
    demo_math()
    show_config()
    interactive_demo()

def greet(name):
    return f"Hello, {name}! Welcome to our app!"

def greet_multiple(names):
    return [greet(name) for name in names]

def show_config():
    try:
        import config
        print(f"App: {config.APP_NAME}")
        print(f"Version: {config.VERSION}")
    except ImportError:
        print("Configuration not available")

def interactive_demo():
    try:
        name = input("What's your name? ")
        print(greet(name))
    except KeyboardInterrupt:
        print("\nDemo interrupted")

# Import math utilities
try:
    from math_utils import add, multiply
    
    def demo_math():
        print("=== Math Demo ===")
        print(f"2 + 3 = {add(2, 3)}")
        print(f"4 * 5 = {multiply(4, 5)}")
        
except ImportError:
    def demo_math():
        print("Math utilities not available")

if __name__ == "__main__":
    main()
EOF
    
    echo "✅ Conflitto risolto combinando le migliori caratteristiche"
    git add app.py
    git commit -m "Merge: Resolve conflict in app.py

Combined the best features from both branches:
- Kept production stability from main
- Added interactive features from feature branch
- Maintained backward compatibility
- Enhanced user experience"
    
    echo -e "\n📊 Stato dopo risoluzione conflitto:"
    git log --oneline --graph --all -6
fi

# Cleanup
git branch -d feature/improve-app

# ==============================================
# SCENARIO 4: Merge Squash
# ==============================================
echo -e "\n🗜️  SCENARIO 4: Merge Squash"
echo "=========================="

# Crea branch con multiple commit
git checkout -b feature/add-tests
echo "✅ Creato branch feature/add-tests"

echo -e "\n📝 Sviluppo con multiple commit:"

# Primo commit: setup test
cat > test_app.py << 'EOF'
import app

def test_greet():
    result = app.greet("Test")
    expected = "Hello, Test! Welcome to our app!"
    assert result == expected, f"Expected {expected}, got {result}"
    print("✅ test_greet passed")

if __name__ == "__main__":
    test_greet()
EOF

git add test_app.py
git commit -m "Add: basic test for greet function"

# Secondo commit: test matematici
cat >> test_app.py << 'EOF'

def test_math():
    try:
        from math_utils import add, multiply
        assert add(2, 3) == 5
        assert multiply(4, 5) == 20
        print("✅ test_math passed")
    except ImportError:
        print("⚠️  Math utilities not available for testing")

if __name__ == "__main__":
    test_greet()
    test_math()
EOF

git add test_app.py
git commit -m "Add: mathematical function tests"

# Terzo commit: test runner
cat > run_tests.py << 'EOF'
#!/usr/bin/env python3

import test_app

def run_all_tests():
    print("🧪 Running all tests...")
    print("=" * 30)
    
    try:
        test_app.test_greet()
        test_app.test_math()
        print("=" * 30)
        print("✅ All tests passed!")
    except Exception as e:
        print(f"❌ Test failed: {e}")
        return False
    return True

if __name__ == "__main__":
    run_all_tests()
EOF

git add run_tests.py
git commit -m "Add: test runner script"

# Quarto commit: documentazione test
cat >> README.md << 'EOF'

## Testing
Per eseguire i test:
```bash
python run_tests.py
```

### Test disponibili:
- `test_greet()`: Testa la funzione di saluto
- `test_math()`: Testa le funzioni matematiche
EOF

git add README.md
git commit -m "Docs: Add testing documentation"

echo -e "\n📊 Storia del branch feature (4 commit):"
git log --oneline --graph -4

echo -e "\n🔄 Tornando a main per squash merge:"
git checkout main

echo -e "\n🗜️  Eseguendo merge --squash:"
git merge --squash feature/add-tests

echo -e "\n📊 Stato dopo squash (modifiche staged):"
git status

echo -e "\n📝 Creando commit squashed:"
git commit -m "Add: Complete test suite

Features added:
- Basic test for greet function
- Mathematical function tests  
- Test runner script
- Testing documentation

All tests are working and documented.
This squashes 4 commits into a single clean commit."

echo -e "\n📊 Storia dopo squash merge:"
git log --oneline --graph -5

echo "✅ Squash merge completato - 4 commit compattati in 1"

# Cleanup
git branch -d feature/add-tests

# ==============================================
# SCENARIO 5: Merge --no-ff (No Fast-Forward)
# ==============================================
echo -e "\n🚫 SCENARIO 5: Merge --no-ff"
echo "=========================="

# Crea branch semplice che normalmente farebbe fast-forward
git checkout -b feature/add-license
echo "✅ Creato branch feature/add-license"

echo -e "\n📝 Aggiunta semplice (normalmente fast-forward):"
cat > LICENSE << 'EOF'
MIT License

Copyright (c) 2024 Merge Demo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
EOF

git add LICENSE
git commit -m "Add: MIT license file"

echo -e "\n🔄 Tornando a main:"
git checkout main

echo -e "\n📊 Stato prima di merge --no-ff:"
git log --oneline --graph --all -3

echo -e "\n🚫 Eseguendo merge --no-ff (forza merge commit):"
git merge --no-ff feature/add-license -m "Merge: Add MIT license

This merge adds the MIT license to the project.
Using --no-ff to explicitly show this feature integration
in the project history."

echo -e "\n📊 Stato dopo merge --no-ff:"
git log --oneline --graph --all -5

echo "✅ Merge --no-ff completato - merge commit creato anche per fast-forward"

# Cleanup
git branch -d feature/add-license

# ==============================================
# SCENARIO 6: Merge Abort
# ==============================================
echo -e "\n❌ SCENARIO 6: Merge Abort"
echo "========================"

# Crea branch che causerà conflitto
git checkout -b feature/conflicting-config
echo "✅ Creato branch feature/conflicting-config"

echo -e "\n📝 Modifiche che causeranno conflitto:"
cat > config.py << 'EOF'
# Configuration file - Development Version
DEBUG = True
VERSION = "2.0.0-dev"

# App settings
APP_NAME = "Merge Demo App - Development"
LOG_LEVEL = "DEBUG"

# Development specific settings
DEV_MODE = True
MOCK_DATA = True
EOF

git add config.py
git commit -m "Config: Development version with debug settings"

echo -e "\n🔄 Tornando a main per conflitto:"
git checkout main

echo -e "\n📝 Modifiche conflittuali su main:"
cat > config.py << 'EOF'
# Configuration file - Production Version
DEBUG = False
VERSION = "1.1.0"

# App settings  
APP_NAME = "Merge Demo App - Production"
LOG_LEVEL = "ERROR"

# Production specific settings
PROD_MODE = True
SECURITY_ENABLED = True
EOF

git add config.py
git commit -m "Config: Production version with security settings"

echo -e "\n⚔️  Iniziando merge che causerà conflitto:"
if git merge feature/conflicting-config; then
    echo "⚠️  Merge riuscito inaspettatamente"
else
    echo "🚨 Conflitto rilevato!"
    
    echo -e "\n📊 Stato durante conflitto:"
    git status
    
    echo -e "\n❌ Decidendo di abortire il merge:"
    git merge --abort
    
    echo -e "\n📊 Stato dopo abort:"
    git status
    
    echo -e "\n📊 Log dopo abort:"
    git log --oneline --graph -3
    
    echo "✅ Merge abortito - repository tornato allo stato precedente"
fi

# Cleanup
git branch -d feature/conflicting-config

# ==============================================
# RIEPILOGO FINALE
# ==============================================
echo -e "\n📊 RIEPILOGO FINALE"
echo "=================="

echo -e "\n📈 Storia completa del repository:"
git log --oneline --graph --all

echo -e "\n📁 File finali nel repository:"
ls -la

echo -e "\n🎯 TIPI DI MERGE DIMOSTRATI"
echo "=========================="
echo "✅ Fast-Forward      - Merge lineare senza commit di merge"
echo "✅ Three-Way         - Merge con commit di merge"
echo "✅ Conflitto         - Merge con risoluzione manuale"
echo "✅ Squash            - Compattazione di multiple commit"
echo "✅ No-FF             - Merge forzato con commit"
echo "✅ Abort             - Annullamento di merge problematico"

echo -e "\n💡 QUANDO USARE OGNI STRATEGIA"
echo "=============================="
echo "🔸 Fast-Forward: Feature lineari senza sovrapposizioni"
echo "🔸 Three-Way: Sviluppo parallelo su branch diversi"
echo "🔸 Squash: Compattare storia di sviluppo feature"
echo "🔸 No-FF: Preservare evidenza di feature branch"
echo "🔸 Abort: Quando il merge è troppo complesso"

echo -e "\n⚙️  CONFIGURAZIONI MERGE"
echo "======================"
echo "# Per sempre creare merge commit:"
echo "git config merge.ff false"
echo ""
echo "# Per preferire fast-forward quando possibile:"
echo "git config merge.ff true"
echo ""
echo "# Per solo fast-forward (fallisce altrimenti):"
echo "git config merge.ff only"

echo -e "\n🧹 Pulizia"
echo "=========="
echo "Per pulire: rm -rf merge-demo"

echo -e "\n✨ Demo completa dei tipi di merge terminata!"
