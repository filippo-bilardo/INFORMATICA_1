#!/bin/bash

# Esempio 01 - Workflow Base Git: init, add, commit
# Questo script dimostra il workflow fondamentale di Git

echo "🚀 Esempio 01: Workflow Base Git"
echo "================================="

# Creiamo una cartella per l'esempio
echo "📁 Creazione cartella progetto..."
mkdir -p git-workflow-example
cd git-workflow-example

# 1. Inizializzazione repository
echo ""
echo "1️⃣ Inizializzazione repository Git"
git init
echo "✅ Repository Git inizializzato"

# 2. Configurazione utente (se non già fatto)
echo ""
echo "2️⃣ Configurazione utente Git"
git config user.name "Studente Git"
git config user.email "studente@example.com"
echo "✅ Configurazione utente completata"

# 3. Creazione primo file
echo ""
echo "3️⃣ Creazione primo file"
cat > README.md << 'EOF'
# Il Mio Primo Progetto Git

Questo è un esempio di progetto per imparare Git.

## Funzionalità
- [ ] Homepage
- [ ] Login utente  
- [ ] Dashboard
EOF
echo "✅ File README.md creato"

# 4. Verifica status
echo ""
echo "4️⃣ Verifica status repository"
git status
echo ""

# 5. Aggiunta file al staging
echo "5️⃣ Aggiunta file al staging"
git add README.md
echo "✅ File aggiunto al staging"

# 6. Verifica status dopo add
echo ""
echo "6️⃣ Status dopo git add"
git status
echo ""

# 7. Primo commit
echo "7️⃣ Primo commit"
git commit -m "Initial commit: add README with project description"
echo "✅ Primo commit completato"

# 8. Verifica storia commit
echo ""
echo "8️⃣ Storia dei commit"
git log --oneline
echo ""

# 9. Aggiunta di più file
echo "9️⃣ Creazione file aggiuntivi"

# File HTML
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Sito</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <h1>Benvenuto nel Mio Sito</h1>
    </header>
    <main>
        <p>Questo sito è gestito con Git!</p>
        <button id="clickMe">Clicca qui</button>
    </main>
    <script src="script.js"></script>
</body>
</html>
EOF

# File CSS
cat > style.css << 'EOF'
/* Stili per il mio sito web */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: Arial, sans-serif;
    line-height: 1.6;
    color: #333;
    background-color: #f4f4f4;
}

header {
    background: #2c3e50;
    color: white;
    text-align: center;
    padding: 2rem;
}

main {
    max-width: 800px;
    margin: 2rem auto;
    padding: 0 1rem;
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 5px rgba(0,0,0,0.1);
}

button {
    background: #3498db;
    color: white;
    border: none;
    padding: 10px 20px;
    border-radius: 4px;
    cursor: pointer;
    font-size: 16px;
}

button:hover {
    background: #2980b9;
}
EOF

# File JavaScript
cat > script.js << 'EOF'
// Script interattivo per il sito
document.addEventListener('DOMContentLoaded', function() {
    const button = document.getElementById('clickMe');
    
    button.addEventListener('click', function() {
        alert('Hai cliccato il bottone! 🎉\nQuesto sito usa Git per il controllo versione.');
    });
    
    // Animazione semplice
    button.addEventListener('mouseover', function() {
        this.style.transform = 'scale(1.05)';
        this.style.transition = 'transform 0.2s';
    });
    
    button.addEventListener('mouseout', function() {
        this.style.transform = 'scale(1)';
    });
});
EOF

echo "✅ File HTML, CSS e JavaScript creati"

# 10. Status con più file
echo ""
echo "🔟 Status con più file non tracciati"
git status
echo ""

# 11. Add di file specifici
echo "1️⃣1️⃣ Aggiunta file HTML"
git add index.html
git status
echo ""

echo "1️⃣2️⃣ Commit del file HTML"
git commit -m "Add homepage HTML structure

- Create semantic HTML layout
- Add header and main sections
- Include links to CSS and JS files"

# 12. Add di file per tipo
echo ""
echo "1️⃣3️⃣ Aggiunta file CSS"
git add *.css
git commit -m "Add responsive CSS styling

- Implement modern design with flexbox
- Add button hover effects
- Use consistent color scheme"

# 13. Add di tutto il resto
echo ""
echo "1️⃣4️⃣ Aggiunta file JavaScript"
git add .
git commit -m "Add interactive JavaScript functionality

- Implement button click handler
- Add hover animations
- Include DOM ready event listener"

# 14. Storia finale
echo ""
echo "1️⃣5️⃣ Storia completa dei commit"
git log --oneline --graph
echo ""

# 15. Dettagli ultimo commit
echo "1️⃣6️⃣ Dettagli ultimo commit"
git show --stat
echo ""

echo "🎉 Esempio completato!"
echo ""
echo "📝 Cosa abbiamo imparato:"
echo "   - git init: inizializzare repository"
echo "   - git add: aggiungere file al staging"  
echo "   - git commit: salvare modifiche permanentemente"
echo "   - git status: verificare stato repository"
echo "   - git log: visualizzare storia commit"
echo ""
echo "💡 Suggerimento: Prova a modificare i file e ripetere il workflow!"
echo "   1. Modifica un file"
echo "   2. git status (vedi le modifiche)"
echo "   3. git add [file]"
echo "   4. git commit -m 'messaggio'"
