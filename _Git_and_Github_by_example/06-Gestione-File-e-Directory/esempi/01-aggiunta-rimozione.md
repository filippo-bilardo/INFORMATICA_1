# Aggiunta e Rimozione File

Questo esempio mostra come gestire l'aggiunta e rimozione di file in Git con diversi scenari pratici.

## Scenario: Gestione File di un Progetto Web

### Setup Iniziale

```bash
# Creare directory di progetto
mkdir gestione-file-esempio
cd gestione-file-esempio
git init

# Creare struttura iniziale
mkdir -p {src,assets,docs}
touch src/index.html assets/style.css docs/README.md

# Aggiungere contenuto ai file
cat > src/index.html << 'EOL'
<!DOCTYPE html>
<html>
<head>
    <title>Progetto Demo</title>
    <link rel="stylesheet" href="../assets/style.css">
</head>
<body>
    <h1>Benvenuto</h1>
    <p>Questo è un progetto demo per Git.</p>
</body>
</html>
EOL

cat > assets/style.css << 'EOL'
body {
    font-family: Arial, sans-serif;
    margin: 20px;
    background-color: #f5f5f5;
}

h1 {
    color: #333;
    text-align: center;
}

p {
    color: #666;
    line-height: 1.6;
}
EOL

cat > docs/README.md << 'EOL'
# Progetto Demo

Questo è un progetto dimostrativo per imparare Git.

## Struttura
- src/ - File sorgente
- assets/ - Risorse CSS/JS/immagini  
- docs/ - Documentazione
EOL
```

### 1. Aggiunta File Singoli

```bash
# Verificare stato iniziale
git status

# Aggiungere file uno alla volta
git add src/index.html
git status

git add assets/style.css
git status

git add docs/README.md
git status

# Committare
git commit -m "Add initial project files"
```

**Output atteso:**
```
On branch main
Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
    new file:   assets/style.css
    new file:   docs/README.md
    new file:   src/index.html
```

### 2. Aggiunta con Pattern

```bash
# Creare nuovi file
touch src/app.js src/utils.js
touch assets/reset.css assets/components.css
touch docs/installation.md docs/usage.md

# Aggiungere file JavaScript
git add src/*.js
git status

# Aggiungere file CSS
git add assets/*.css
git status  

# Aggiungere file Markdown
git add docs/*.md
git status

# Committare
git commit -m "Add JavaScript, CSS and documentation files"
```

### 3. Aggiunta Interattiva

```bash
# Modificare file esistente
cat >> src/index.html << 'EOL'
    <script src="app.js"></script>
    <script src="utils.js"></script>
EOL

# Creare file misto (da aggiungere parzialmente)
cat > src/config.js << 'EOL'
// Configurazione di produzione
const config = {
    apiUrl: 'https://api.production.com',
    debug: false
};

// Configurazione di development (NON committare)
const devConfig = {
    apiUrl: 'http://localhost:3000',
    debug: true,
    secretKey: 'dev-secret-123'  // Sensibile!
};

export { config };
EOL

# Aggiunta interattiva
echo "Usare git add -p per aggiungere solo parti del file:"
echo "git add -p src/config.js"
echo ""
echo "Rispondere 'y' alle parti di produzione, 'n' alle parti di development"
```

### 4. Rimozione File

```bash
# Creare file temporaneo da rimuovere
touch temp-file.txt
echo "File temporaneo da eliminare" > temp-file.txt
git add temp-file.txt
git commit -m "Add temporary file"

# Rimuovere file con git rm
git rm temp-file.txt
git status

# Committare la rimozione
git commit -m "Remove temporary file"

# Verificare che il file sia sparito
ls -la | grep temp || echo "File eliminato correttamente"
```

### 5. Rimozione dal Tracciamento (Mantiene File Locale)

```bash
# Creare file di configurazione locale
cat > .env << 'EOL'
DATABASE_URL=postgresql://localhost:5432/mydb
API_SECRET=super-secret-key-123
DEBUG=true
EOL

# Aggiungere accidentalmente
git add .env
git commit -m "Add environment config (ERRORE!)"

# Rimuovere dal tracciamento mantenendo locale
git rm --cached .env
git status

# Aggiungere al .gitignore
echo ".env" >> .gitignore
git add .gitignore

# Committare la correzione
git commit -m "Remove .env from tracking and add to gitignore"

# Verificare che il file esista ancora
ls -la .env && echo "File .env ancora presente localmente"
```

### 6. Gestione File con Spazi nei Nomi

```bash
# Creare file con spazi nei nomi
touch "file con spazi.txt"
touch "another file.html"
mkdir "directory con spazi"
touch "directory con spazi/file interno.css"

# Aggiungere usando virgolette
git add "file con spazi.txt"
git add "another file.html"
git add "directory con spazi/"

# O usare escape
# git add file\ con\ spazi.txt

git commit -m "Add files with spaces in names"
```

### 7. Bulk Operations

```bash
# Creare molti file per test bulk
for i in {1..5}; do
    touch "test-file-$i.txt"
    echo "Content of test file $i" > "test-file-$i.txt"
done

# Aggiungere tutti insieme
git add test-file-*.txt
git commit -m "Add test files in bulk"

# Rimuovere tutti insieme
git rm test-file-*.txt
git commit -m "Remove test files in bulk"
```

### 8. Gestione Errori Comuni

```bash
# Simulare file modificato che non si vuole eliminare
echo "Contenuto importante" > important.txt
git add important.txt
git commit -m "Add important file"

# Modificare file
echo "Modifica importante" >> important.txt

# Tentare di rimuovere (darà errore)
echo "Questo comando darà errore:"
echo "git rm important.txt"
echo ""

# Soluzioni possibili:
echo "Soluzioni:"
echo "1. Committare prima: git add important.txt && git commit"
echo "2. Forzare rimozione: git rm -f important.txt" 
echo "3. Rimuovere solo dal tracking: git rm --cached important.txt"
```

## Script Completo di Esempio

```bash
#!/bin/bash
# demo-gestione-file.sh

set -e  # Exit on error

echo "=== Demo Gestione File Git ==="

# Setup
rm -rf gestione-file-demo 2>/dev/null || true
mkdir gestione-file-demo
cd gestione-file-demo
git init --quiet

echo "✓ Repository inizializzato"

# Creare struttura
mkdir -p {src,assets,docs,tests}
touch src/{index.html,app.js} assets/{style.css,app.css} docs/README.md

echo "✓ Struttura directory creata"

# Aggiungere tutto
git add .
git commit -m "Initial commit" --quiet

echo "✓ File iniziali committati"

# Aggiungere nuovi file
touch {feature.js,styles.css,config.json}
git add *.js *.css
git status --porcelain

echo "✓ Nuovi file aggiunti selettivamente"

# Rimuovere file
git rm config.json --quiet 2>/dev/null || true
touch secret.txt
git add secret.txt
git commit -m "Add secret file" --quiet
git rm --cached secret.txt --quiet
echo "secret.txt" > .gitignore

echo "✓ Gestione rimozione file completata"

# Stato finale
git status --porcelain
echo "✓ Demo completata con successo!"
```

## Comandi Rapidi di Riferimento

```bash
# Aggiunta
git add file.txt                    # Singolo file
git add .                          # Tutti i file
git add *.js                       # File per estensione
git add directory/                 # Directory intera
git add -A                         # Tutto incluse eliminazioni

# Rimozione
git rm file.txt                    # Rimuovi file e dal tracking
git rm --cached file.txt           # Rimuovi solo dal tracking
git rm -r directory/               # Rimuovi directory ricorsivamente  
git rm -f modified-file.txt        # Forza rimozione file modificato

# Verifica
git status                         # Stato completo
git status -s                      # Stato conciso
git diff --cached                  # Mostra cosa verrà committato
git ls-files                       # Lista file tracciati
```

## Output di Esempio

### git status dopo aggiunta selettiva:
```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    new file:   feature.js
    new file:   styles.css

Untracked files:
  (use "git add <file>..." to include in what will be committed)
    config.json
```

### git status dopo rimozione:
```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    deleted:    temp-file.txt
```

## Note per l'Apprendimento

1. **Sempre verificare con `git status`** prima di committare
2. **Usare `git add -p`** per controllo granulare
3. **File con spazi** richiedono virgolette o escape
4. **`--cached`** rimuove dal tracking ma mantiene il file locale
5. **Pattern globbing** funziona con git add (*.js, *.css, etc.)

Questo esempio copre tutti i casi comuni di gestione file che incontrerai nel lavoro quotidiano con Git.
