# Esempio Pratico: Git Submodules

## Scenario
Creiamo un progetto web che utilizza una libreria comune come submodulo.

## Struttura dell'Esempio
```
webapp-main/          # Repository principale
├── src/
├── assets/
└── libs/
    └── ui-components/  # Submodulo
```

## Setup Iniziale

### 1. Creare il Repository della Libreria
```bash
# Creare directory per la libreria
mkdir ui-components
cd ui-components
git init

# Creare alcuni file di esempio
cat > button.js << 'EOF'
class Button {
    constructor(text, color = 'blue') {
        this.text = text;
        this.color = color;
    }
    
    render() {
        return `<button class="btn btn-${this.color}">${this.text}</button>`;
    }
}

export default Button;
EOF

cat > modal.js << 'EOF'
class Modal {
    constructor(title, content) {
        this.title = title;
        this.content = content;
    }
    
    show() {
        return `
        <div class="modal">
            <h2>${this.title}</h2>
            <p>${this.content}</p>
        </div>`;
    }
}

export default Modal;
EOF

cat > package.json << 'EOF'
{
  "name": "ui-components",
  "version": "1.0.0",
  "description": "Libreria di componenti UI riusabili",
  "main": "index.js",
  "author": "Team UI"
}
EOF

# Commit iniziale
git add .
git commit -m "Initial UI components library"
git tag v1.0.0

cd ..
```

### 2. Creare il Repository Principale
```bash
# Creare il progetto principale
mkdir webapp-main
cd webapp-main
git init

# Struttura del progetto
mkdir -p src assets libs

cat > src/app.js << 'EOF'
import Button from '../libs/ui-components/button.js';
import Modal from '../libs/ui-components/modal.js';

class App {
    constructor() {
        this.initComponents();
    }
    
    initComponents() {
        const saveBtn = new Button('Salva', 'green');
        const cancelBtn = new Button('Annulla', 'red');
        const helpModal = new Modal('Aiuto', 'Questa è la guida utente');
        
        document.body.innerHTML = `
            ${saveBtn.render()}
            ${cancelBtn.render()}
            ${helpModal.show()}
        `;
    }
}

new App();
EOF

cat > index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>WebApp con Submoduli</title>
    <style>
        .btn { padding: 10px 20px; margin: 5px; border: none; border-radius: 4px; }
        .btn-blue { background: #007bff; color: white; }
        .btn-green { background: #28a745; color: white; }
        .btn-red { background: #dc3545; color: white; }
        .modal { border: 1px solid #ccc; padding: 20px; margin: 20px; }
    </style>
</head>
<body>
    <h1>WebApp Example</h1>
    <script type="module" src="src/app.js"></script>
</body>
</html>
EOF

cat > README.md << 'EOF'
# WebApp Main

Applicazione web che utilizza la libreria ui-components come submodulo.

## Setup
```bash
git submodule update --init --recursive
```

## Componenti
- Libreria UI: `libs/ui-components/`
- Codice app: `src/`
EOF

git add .
git commit -m "Initial webapp structure"
```

## Aggiungere il Submodulo

```bash
# Aggiungere la libreria come submodulo
git submodule add ../ui-components libs/ui-components

# Verificare l'aggiunta
git status
git diff --cached

# Commit del submodulo
git commit -m "Add ui-components submodule"

# Verificare la configurazione
cat .gitmodules
```

## Workflow di Sviluppo

### Scenario 1: Aggiornare la Libreria

```bash
# Entrare nel submodulo
cd libs/ui-components

# Aggiungere una nuova funzionalità
cat > card.js << 'EOF'
class Card {
    constructor(title, content, image = null) {
        this.title = title;
        this.content = content;
        this.image = image;
    }
    
    render() {
        const imgTag = this.image ? `<img src="${this.image}" alt="${this.title}">` : '';
        return `
        <div class="card">
            ${imgTag}
            <h3>${this.title}</h3>
            <p>${this.content}</p>
        </div>`;
    }
}

export default Card;
EOF

# Aggiornare il package.json
sed -i 's/"version": "1.0.0"/"version": "1.1.0"/' package.json

git add .
git commit -m "Add Card component"
git tag v1.1.0

# Tornare al repository principale
cd ../..

# Il repository principale mostra modifiche
git status
git diff

# Aggiornare il riferimento al submodulo
git add libs/ui-components
git commit -m "Update ui-components to v1.1.0"
```

### Scenario 2: Clonare con Submoduli

```bash
# Simulare un nuovo sviluppatore
cd ..
git clone webapp-main webapp-clone

cd webapp-clone
# I submoduli sono vuoti!
ls libs/ui-components/

# Inizializzare i submoduli
git submodule init
git submodule update

# Oppure in un comando
git submodule update --init --recursive

# Ora i file sono presenti
ls libs/ui-components/
```

### Scenario 3: Aggiornamenti Coordinati

```bash
cd webapp-main

# Aggiornare il submodulo alla versione più recente
cd libs/ui-components
git pull origin main

# Aggiornare l'app principale per usare il nuovo componente
cd ../..
cat >> src/app.js << 'EOF'

// Utilizzare il nuovo componente Card
import Card from '../libs/ui-components/card.js';

const newsCard = new Card(
    'Novità', 
    'La nostra libreria UI è stata aggiornata!',
    'assets/news.jpg'
);
document.body.innerHTML += newsCard.render();
EOF

# Aggiornare gli stili
sed -i '/\.modal/a\
.card { border: 1px solid #eee; padding: 15px; margin: 10px; border-radius: 8px; }\
.card img { max-width: 100%; height: auto; }' index.html

git add .
git commit -m "Use new Card component from updated ui-components"
```

## Automazione con Script

Creare uno script per semplificare la gestione:

```bash
cat > update-submodules.sh << 'EOF'
#!/bin/bash

echo "🔄 Updating all submodules..."

# Aggiornare tutti i submoduli
git submodule foreach 'git pull origin main'

# Mostrare lo stato
echo "📊 Submodule status:"
git submodule status

# Chiedere conferma per il commit
echo "💾 Commit submodule updates? (y/n)"
read -r response
if [[ $response =~ ^[Yy]$ ]]; then
    git add .
    git commit -m "Update submodules to latest versions"
    echo "✅ Submodules updated and committed"
else
    echo "⏸️  Updates staged but not committed"
fi
EOF

chmod +x update-submodules.sh
```

## Verifica Pratica

Eseguire questi comandi per verificare la comprensione:

1. **Controllo dello stato:**
   ```bash
   git submodule status
   git submodule summary
   ```

2. **Navigazione nei submoduli:**
   ```bash
   git submodule foreach 'echo "In submodule: $name"'
   git submodule foreach 'git log --oneline -3'
   ```

3. **Risoluzione di conflitti:**
   ```bash
   # Se ci sono divergenze
   git submodule update --remote --merge
   ```

## Risultato Atteso

Al termine dell'esempio dovreste avere:
- Un repository principale che utilizza una libreria esterna
- Comprensione di come aggiornare e sincronizzare i submoduli
- Esperienza pratica con i workflow di sviluppo coordinato
- Script di automazione per la gestione quotidiana

## Note per l'Istruttore

- Questo esempio può essere esteso con più submoduli
- Si può simulare il lavoro in team con repository remoti reali
- È utile mostrare anche gli errori comuni e come risolverli
