#!/bin/bash

# ==============================================
# 📥 DEMO COMPLETA: Clone, Push, Pull
# ==============================================
# Questo script dimostra le operazioni fondamentali
# per lavorare con repository remoti

echo "🚀 Demo: Clone, Push, Pull - Workflow Completo"
echo "=============================================="

# Pulizia ambiente di test
echo "🧹 Pulizia ambiente di test..."
rm -rf demo-remote demo-local1 demo-local2 2>/dev/null

# ==============================================
# PARTE 1: Simulazione Repository Remoto
# ==============================================
echo -e "\n📦 PARTE 1: Creazione Repository 'Remoto'"
echo "----------------------------------------"

# Crea un repository che simula quello remoto
mkdir demo-remote
cd demo-remote
git init --bare
echo "✅ Repository 'remoto' creato (bare repository)"
cd ..

# ==============================================
# PARTE 2: Clone e Setup Iniziale
# ==============================================
echo -e "\n📋 PARTE 2: Clone del Repository"
echo "--------------------------------"

# Clone del repository
git clone demo-remote demo-local1
cd demo-local1

echo "✅ Repository clonato in demo-local1"

# Configura utente per questo repository
git config user.name "Developer 1"
git config user.email "dev1@example.com"

# Crea file iniziale
echo "# Progetto Demo Clone/Push/Pull" > README.md
echo "Questo è un progetto di esempio per dimostrare Git" >> README.md
echo "Creato da: Developer 1" >> README.md

git add README.md
git commit -m "Initial commit: Add README"

echo "✅ Primo commit creato"

# Push iniziale
git push origin main
echo "✅ Push iniziale completato"

cd ..

# ==============================================
# PARTE 3: Secondo Clone (Simula altro sviluppatore)
# ==============================================
echo -e "\n👥 PARTE 3: Secondo Clone (Developer 2)"
echo "--------------------------------------"

# Clone da parte di un secondo sviluppatore
git clone demo-remote demo-local2
cd demo-local2

git config user.name "Developer 2"
git config user.email "dev2@example.com"

echo "✅ Secondo clone completato"

# Verifica stato
echo -e "\n📊 Stato repository Developer 2:"
git log --oneline --graph
git remote -v

cd ..

# ==============================================
# PARTE 4: Modifiche Parallele e Push
# ==============================================
echo -e "\n🔄 PARTE 4: Modifiche Parallele"
echo "------------------------------"

# Developer 1 fa modifiche
echo -e "\n👤 Developer 1 - Aggiunge documentazione"
cd demo-local1

echo -e "\n## Installazione" >> README.md
echo "1. Clone del repository" >> README.md
echo "2. Installazione dipendenze" >> README.md

# Crea nuovo file
echo "console.log('Hello World!');" > app.js

git add .
git commit -m "Add: Installation docs and basic app.js"

# Push delle modifiche
git push origin main
echo "✅ Developer 1 - Push completato"

cd ..

# Developer 2 fa modifiche (contemporaneamente)
echo -e "\n👤 Developer 2 - Aggiunge configurazione"
cd demo-local2

# Crea file di configurazione
cat > config.json << EOF
{
  "name": "demo-project",
  "version": "1.0.0",
  "description": "Progetto demo per Git"
}
EOF

git add config.json
git commit -m "Add: Project configuration file"

echo "✅ Developer 2 - Commit locale creato"

# ==============================================
# PARTE 5: Pull e Gestione Aggiornamenti
# ==============================================
echo -e "\n📥 PARTE 5: Pull e Sincronizzazione"
echo "----------------------------------"

# Developer 2 prova a fare push (fallirà)
echo -e "\n🚨 Developer 2 tenta push (che fallirà):"
if git push origin main 2>&1 | grep -q "rejected"; then
    echo "❌ Push respinto - repository remoto più avanti"
else
    echo "⚠️  Push riuscito inaspettatamente"
fi

# Developer 2 fa pull per sincronizzare
echo -e "\n📥 Developer 2 fa pull per sincronizzare:"
git pull origin main

echo "✅ Pull completato, ora il push dovrebbe funzionare"

# Ora Developer 2 può fare push
git push origin main
echo "✅ Developer 2 - Push completato dopo pull"

cd ..

# ==============================================
# PARTE 6: Pull da parte di Developer 1
# ==============================================
echo -e "\n🔄 PARTE 6: Developer 1 Sincronizza"
echo "----------------------------------"

cd demo-local1

echo -e "\n📊 Stato prima del pull:"
git log --oneline --graph -3

echo -e "\n📥 Developer 1 fa pull:"
git pull origin main

echo -e "\n📊 Stato dopo il pull:"
git log --oneline --graph -5

cd ..

# ==============================================
# PARTE 7: Scenario con Conflitti
# ==============================================
echo -e "\n⚔️  PARTE 7: Simulazione Conflitto"
echo "---------------------------------"

# Developer 1 modifica README
cd demo-local1
echo -e "\n## Contributi" >> README.md
echo "Contributi di Developer 1" >> README.md
git add README.md
git commit -m "Add: Contributions section by Dev1"

cd ..

# Developer 2 modifica lo stesso file
cd demo-local2
# Prima fa pull per avere l'ultima versione
git pull origin main

# Poi aggiunge le sue modifiche alla fine
echo "Contributi di Developer 2" >> README.md
git add README.md
git commit -m "Add: Contributions by Dev2"

cd ..

# Developer 1 fa push prima
cd demo-local1
git push origin main
echo "✅ Developer 1 - Push completato"

cd ..

# Developer 2 prova a fare push (conflitto)
cd demo-local2
echo -e "\n🚨 Developer 2 tenta push (può generare conflitto):"

if git push origin main 2>&1 | grep -q "rejected"; then
    echo "❌ Push respinto - necessario pull"
    
    echo -e "\n📥 Developer 2 fa pull (può causare conflitto):"
    # Se c'è conflitto, mostra come risolverlo
    if ! git pull origin main; then
        echo "⚔️  Conflitto rilevato! Risoluzione manuale necessaria"
        echo "📝 In una situazione reale, dovresti:"
        echo "   1. Aprire i file in conflitto"
        echo "   2. Risolvere manualmente i conflitti"
        echo "   3. git add <file-risolti>"
        echo "   4. git commit"
    else
        echo "✅ Pull completato automaticamente (merge commit)"
        git push origin main
        echo "✅ Push completato dopo pull"
    fi
else
    echo "✅ Push riuscito"
fi

cd ..

# ==============================================
# PARTE 8: Stato Finale e Riepilogo
# ==============================================
echo -e "\n📊 PARTE 8: Stato Finale"
echo "========================"

echo -e "\n📦 Repository Remoto (simulato):"
cd demo-remote
echo "Repository bare - contiene tutta la storia"

cd ..

echo -e "\n👤 Repository Developer 1:"
cd demo-local1
echo "Branch: $(git branch --show-current)"
echo "Commit totali: $(git rev-list --count HEAD)"
git log --oneline --graph -5

cd ..

echo -e "\n👤 Repository Developer 2:"
cd demo-local2
echo "Branch: $(git branch --show-current)"
echo "Commit totali: $(git rev-list --count HEAD)"
git log --oneline --graph -5

cd ..

# ==============================================
# RIEPILOGO COMANDI UTILIZZATI
# ==============================================
echo -e "\n📚 RIEPILOGO COMANDI UTILIZZATI"
echo "==============================="
echo "🔸 git clone <url> <directory>  - Clona repository"
echo "🔸 git push origin <branch>     - Invia commit al remoto"
echo "🔸 git pull origin <branch>     - Scarica e unisce cambiamenti"
echo "🔸 git remote -v                - Mostra repository remoti"
echo "🔸 git log --oneline --graph    - Storia visualizzata"

echo -e "\n💡 LEZIONI APPRESE"
echo "=================="
echo "✅ Clone crea una copia completa del repository"
echo "✅ Push invia i commit locali al repository remoto"
echo "✅ Pull scarica e integra i cambiamenti remoti"
echo "✅ Sempre fare pull prima di push se il remoto è avanti"
echo "⚠️  I conflitti si risolvono manualmente dopo il pull"

echo -e "\n🎯 WORKFLOW CONSIGLIATO"
echo "======================="
echo "1. git status           (verifica stato)"
echo "2. git add .            (prepara modifiche)"
echo "3. git commit -m '...'  (salva modifiche)"
echo "4. git pull origin main (sincronizza)"
echo "5. git push origin main (condividi)"

echo -e "\n🧹 Pulizia"
echo "=========="
echo "Per pulire i file demo: rm -rf demo-remote demo-local1 demo-local2"

echo -e "\n✨ Demo completata!"
