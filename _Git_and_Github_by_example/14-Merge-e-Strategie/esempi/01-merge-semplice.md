# Esempio 1: Merge Semplice - Fast Forward

## Scenario
Sviluppo lineare di una feature senza conflitti, dimostrando il merge fast-forward.

## Setup Iniziale

```bash
# Crea repository di esempio
mkdir merge-semplice-example
cd merge-semplice-example
git init

# Commit iniziale
echo "# Simple Merge Example" > README.md
git add README.md
git commit -m "Initial commit"

echo "body { margin: 0; }" > styles.css
git add styles.css
git commit -m "Add basic styles"
```

## Sviluppo Feature (Fast-Forward)

### Crea Branch Feature
```bash
# Crea branch per nuova feature
git checkout -b feature/add-navigation

# Verifica stato
git log --oneline --graph
```

### Sviluppo Sequenziale
```bash
# Commit 1: Struttura base
cat > navigation.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Navigation Example</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <nav>
        <ul>
            <li><a href="#home">Home</a></li>
        </ul>
    </nav>
</body>
</html>
EOF

git add navigation.html
git commit -m "Add basic navigation structure"

# Commit 2: Aggiungi più link
sed -i '/Home/a\            <li><a href="#about">About</a></li>' navigation.html
git add navigation.html
git commit -m "Add About link to navigation"

# Commit 3: Styling navigation
cat >> styles.css << 'EOF'

/* Navigation Styles */
nav ul {
    list-style: none;
    padding: 0;
    display: flex;
}

nav li {
    margin-right: 20px;
}

nav a {
    text-decoration: none;
    color: #333;
}
EOF

git add styles.css
git commit -m "Add navigation styling"
```

### Visualizza Storia Pre-Merge
```bash
# Mostra storia grafica
git log --oneline --graph --all

# Output atteso:
# * 4f8a2b3 (HEAD -> feature/add-navigation) Add navigation styling
# * 7e5c1d9 Add About link to navigation  
# * 2a9f4b8 Add basic navigation structure
# * 1c7e9a5 (main) Add basic styles
# * 8b2d4f6 Initial commit
```

## Fast-Forward Merge

### Verifica Possibilità Fast-Forward
```bash
# Torna su main
git checkout main

# Verifica se è possibile fast-forward
git merge --ff-only feature/add-navigation --dry-run
```

### Esegui Merge Fast-Forward
```bash
# Merge con fast-forward (default)
git merge feature/add-navigation

# Verifica risultato
git log --oneline --graph
```

### Risultato Fast-Forward
```
* 4f8a2b3 (HEAD -> main, feature/add-navigation) Add navigation styling
* 7e5c1d9 Add About link to navigation
* 2a9f4b8 Add basic navigation structure  
* 1c7e9a5 Add basic styles
* 8b2d4f6 Initial commit
```

**Osservazione**: Non c'è commit di merge! Il puntatore `main` è semplicemente avanzato.

## Cleanup
```bash
# Elimina branch feature (non più necessario)
git branch -d feature/add-navigation

# Verifica branches
git branch
```

## Esempio Alternativo: No Fast-Forward

### Reset per Dimostrare No-FF
```bash
# Reset a commit precedente per demo
git reset --hard 1c7e9a5

# Ricrea feature branch
git checkout -b feature/add-navigation-no-ff

# Stesso sviluppo...
cat > navigation.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>Navigation Example</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <nav>
        <ul>
            <li><a href="#home">Home</a></li>
            <li><a href="#about">About</a></li>
            <li><a href="#contact">Contact</a></li>
        </ul>
    </nav>
</body>
</html>
EOF

git add navigation.html
git commit -m "Add complete navigation"
```

### Merge No Fast-Forward
```bash
# Torna su main
git checkout main

# Merge forzando commit di merge
git merge --no-ff feature/add-navigation-no-ff -m "Merge feature: Add navigation system"

# Visualizza differenza
git log --oneline --graph
```

### Risultato No Fast-Forward
```
*   a8c4e7f (HEAD -> main) Merge feature: Add navigation system
|\  
| * 9d2f5b1 (feature/add-navigation-no-ff) Add complete navigation
|/  
* 1c7e9a5 Add basic styles
* 8b2d4f6 Initial commit
```

**Osservazione**: C'è un commit di merge esplicito!

## Confronto Fast-Forward vs No Fast-Forward

### Fast-Forward
**Vantaggi:**
- Storia lineare e pulita
- Meno rumore nei log
- Semplice da seguire

**Svantaggi:**
- Perde traccia dei branch feature
- Difficile capire raggruppamenti di commit

### No Fast-Forward
**Vantaggi:**
- Mantiene struttura dei branch
- Chiaro quando inizia/finisce una feature
- Facilita revert di intere feature

**Svantaggi:**
- Storia più complessa
- Più commit di merge

## Configurazione Comportamento Default

### Configura Fast-Forward Policy
```bash
# Solo fast-forward (fallisce se non possibile)
git config merge.ff only

# No fast-forward mai
git config merge.ff false

# Default (fast-forward quando possibile)
git config merge.ff true
```

### Per Branch Specifici
```bash
# Configura branch main per no-ff
git config branch.main.mergeoptions "--no-ff"
```

## Casi d'Uso Pratici

### Quando Usare Fast-Forward
- Feature semplici e lineari
- Hotfix urgenti
- Aggiornamenti documentazione
- Sviluppo individuale

### Quando Evitare Fast-Forward
- Feature complesse multi-commit
- Sviluppo team
- Quando serve tracciabilità
- Release branches

## Script Automatico per Dimostrazione

```bash
#!/bin/bash
# demo-fast-forward.sh

echo "=== Demo Fast-Forward Merge ==="

# Setup
rm -rf ff-demo
mkdir ff-demo && cd ff-demo
git init

# Initial commits
echo "main content" > file.txt
git add file.txt
git commit -m "Initial commit"

echo "more content" >> file.txt
git add file.txt
git commit -m "Add more content"

# Feature branch
git checkout -b feature/enhancement
echo "enhanced content" >> file.txt
git add file.txt
git commit -m "Enhance content"

echo "final enhancement" >> file.txt
git add file.txt
git commit -m "Final enhancement"

# Show before merge
echo "Before merge:"
git log --oneline --graph --all

# Fast-forward merge
git checkout main
git merge feature/enhancement

echo -e "\nAfter fast-forward merge:"
git log --oneline --graph

# Cleanup
git branch -d feature/enhancement

echo -e "\nDemo complete!"
```

## Esercizi Pratici

1. **Crea scenario fast-forward** con 3 commit sequenziali
2. **Confronta FF vs No-FF** sullo stesso scenario
3. **Configura policy** del tuo repository preferito
4. **Analizza progetti esistenti** per vedere strategie usate

---

Il fast-forward merge è il tipo più semplice ma è importante capire quando è appropriato usarlo!
