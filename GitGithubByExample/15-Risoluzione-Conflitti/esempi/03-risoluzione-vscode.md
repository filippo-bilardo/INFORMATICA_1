# Esempio 3: Risoluzione Conflitti con VS Code

## Scenario
Utilizzo dell'editor VS Code per risolvere conflitti di merge con interfaccia grafica intuitiva e strumenti integrati.

## Preparazione

### Setup Repository
```bash
# Crea repository con conflitto programmato
mkdir conflict-vscode-demo
cd conflict-vscode-demo
git init

# File iniziale
echo "# Progetto Collaborativo
Versione: 1.0
Autore: Team Alpha" > README.md

git add README.md
git commit -m "Initial commit"

# Branch per feature
git checkout -b feature/update-info
```

### Creazione Conflitto
```bash
# Modifica su feature branch
cat > README.md << 'EOF'
# Progetto Collaborativo
Versione: 2.0-beta
Autore: Team Alpha
Descrizione: Sistema di gestione avanzato

## Nuove Funzionalità
- Interface migliorata
- Performance ottimizzate
- Sicurezza rafforzata
EOF

git add README.md
git commit -m "feat: update project info and add features"

# Torna a main e modifica la stessa sezione
git checkout main

cat > README.md << 'EOF'
# Progetto Collaborativo
Versione: 2.0-stable
Autore: Team Alpha e Team Beta
Descrizione: Sistema di gestione enterprise

## Caratteristiche
- Stabilità garantita
- Supporto 24/7
- Documentazione completa
EOF

git add README.md
git commit -m "docs: update to stable version with enterprise features"
```

## Merge e Risoluzione in VS Code

### Tentativo di Merge
```bash
# Questo genererà un conflitto
git merge feature/update-info
```

**Output:**
```
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Automatic merge failed; fix conflicts and then commit the result.
```

### Apertura in VS Code
```bash
# Apri il progetto in VS Code
code .
```

## Interfaccia VS Code per Conflitti

### Visualizzazione Conflitto
VS Code mostra automaticamente:

1. **Source Control Panel** - File in conflitto evidenziati
2. **Editor con marker speciali**:
   - `<<<<<<< HEAD` (Current Change)
   - `=======` (Separatore)
   - `>>>>>>> feature/update-info` (Incoming Change)

3. **Action Buttons**:
   - "Accept Current Change"
   - "Accept Incoming Change"  
   - "Accept Both Changes"
   - "Compare Changes"

### File con Conflitto in VS Code
```markdown
# Progetto Collaborativo
<<<<<<< HEAD
Versione: 2.0-stable
Autore: Team Alpha e Team Beta
Descrizione: Sistema di gestione enterprise

## Caratteristiche
- Stabilità garantita
- Supporto 24/7
- Documentazione completa
=======
Versione: 2.0-beta
Autore: Team Alpha
Descrizione: Sistema di gestione avanzato

## Nuove Funzionalità
- Interface migliorata
- Performance ottimizzate
- Sicurezza rafforzata
>>>>>>> feature/update-info
```

## Strategie di Risoluzione

### 1. Accept Current Change
Mantiene solo la versione del branch `main`:
```markdown
# Progetto Collaborativo
Versione: 2.0-stable
Autore: Team Alpha e Team Beta
Descrizione: Sistema di gestione enterprise

## Caratteristiche
- Stabilità garantita
- Supporto 24/7
- Documentazione completa
```

### 2. Accept Incoming Change
Mantiene solo la versione del branch `feature/update-info`:
```markdown
# Progetto Collaborativo
Versione: 2.0-beta
Autore: Team Alpha
Descrizione: Sistema di gestione avanzato

## Nuove Funzionalità
- Interface migliorata
- Performance ottimizzate
- Sicurezza rafforzata
```

### 3. Risoluzione Personalizzata
Combina il meglio di entrambe le versioni:
```markdown
# Progetto Collaborativo
Versione: 2.0-stable
Autore: Team Alpha e Team Beta
Descrizione: Sistema di gestione enterprise avanzato

## Caratteristiche Enterprise
- Stabilità garantita
- Supporto 24/7
- Documentazione completa

## Nuove Funzionalità
- Interface migliorata
- Performance ottimizzate
- Sicurezza rafforzata
```

## Workflow VS Code Completo

### Passo 1: Identifica Conflitti
```bash
# Nel terminale integrato di VS Code
git status
```

### Passo 2: Risolvi Visualmente
1. Clicca sui bottoni di azione sopra ogni conflitto
2. Oppure modifica manualmente rimuovendo i marker
3. Salva il file (Ctrl+S)

### Passo 3: Verifica Risoluzione
```bash
# Controlla che non ci siano più marker
grep -n "<<<\|===\|>>>" README.md
# Output vuoto = nessun marker rimasto
```

### Passo 4: Stage e Commit
```bash
# In VS Code Source Control o terminale
git add README.md
git commit -m "resolve: merge conflict between stable and beta versions"
```

## Funzionalità Avanzate VS Code

### 1. 3-Way Merge Editor
```bash
# Abilita l'editor 3-way merge avanzato
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
```

### 2. Confronto Side-by-Side
- **Command Palette** (Ctrl+Shift+P)
- Digita: "Git: Compare"
- Seleziona branch da confrontare

### 3. GitLens Extension
```bash
# Installa GitLens per funzionalità avanzate
code --install-extension eamodio.gitlens
```

**Funzionalità GitLens per conflitti:**
- Blame inline per vedere chi ha modificato cosa
- History dei file per capire l'evoluzione
- Compare con branch precedenti

## Best Practices VS Code

### 1. Configurazione Merge Tool
```bash
# Imposta VS Code come merge tool predefinito
git config --global merge.tool vscode
git config --global mergetool.keepBackup false
```

### 2. Estensioni Utili
- **GitLens** - Git supercharged
- **Git Graph** - Visualizzazione grafica
- **Merge Conflict** - Evidenziazione syntax

### 3. Keyboard Shortcuts
- `F7` - Conflitto successivo
- `Shift+F7` - Conflitto precedente
- `Ctrl+Shift+P` - Command Palette per comandi Git

## Scenario Complesso

### File Multi-sezione
```javascript
// package.json con conflitti multipli
{
<<<<<<< HEAD
  "name": "project-stable",
  "version": "2.0.0",
=======
  "name": "project-beta", 
  "version": "2.0.0-beta.1",
>>>>>>> feature/update-info
  "description": "Enterprise management system",
  "dependencies": {
<<<<<<< HEAD
    "express": "^4.18.0",
    "mongoose": "^6.10.0"
=======
    "express": "^4.19.0",
    "mongoose": "^7.0.0",
    "socket.io": "^4.6.0"
>>>>>>> feature/update-info
  }
}
```

### Risoluzione Intelligente
1. **Nome progetto**: Mantieni "project-stable"
2. **Versione**: Usa "2.0.0" (stabile)
3. **Dipendenze**: Combina versioni sicure + nuova dipendenza

```javascript
{
  "name": "project-stable",
  "version": "2.0.0", 
  "description": "Enterprise management system",
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^6.10.0",
    "socket.io": "^4.6.0"
  }
}
```

## Testing Post-Risoluzione

### Verifica Syntax
```bash
# Per file JSON
node -e "console.log('JSON valid:', JSON.parse(require('fs').readFileSync('package.json')))"

# Per file JavaScript  
node --check app.js

# Per file Markdown
markdownlint README.md
```

### Test Funzionale
```bash
# Installa dipendenze se package.json modificato
npm install

# Esegui test se presenti
npm test

# Verifica build
npm run build
```

## Risoluzione Rapida

### Command Palette Shortcuts
1. `Ctrl+Shift+P` → "Git: Accept All Current"
2. `Ctrl+Shift+P` → "Git: Accept All Incoming"
3. `Ctrl+Shift+P` → "Git: Compare with Branch"

### File Explorer
- File in conflitto hanno icona speciale `!`
- Click destro → "Open Changes" per diff
- Source Control panel mostra conteggio conflitti

## 🎯 Risultato

Con VS Code hai un ambiente visuale potente per:
- Identificare rapidamente conflitti
- Risolvere con click o editing manuale
- Verificare risoluzione in tempo reale
- Mantenere traccia delle modifiche

L'interfaccia grafica rende la risoluzione conflitti meno intimidatoria e più efficiente per sviluppatori di tutti i livelli.

## 📝 Note Pratiche

- **Sempre** testa dopo la risoluzione
- **Usa** preview per capire l'impatto
- **Salva** frequentemente durante la risoluzione
- **Communica** con il team sulle decisioni prese

---

[⬅️ Esempio Precedente](./02-conflitti-multi-file.md) | [➡️ Esempio Successivo](./04-conflitti-complessi.md)

[🏠 Torna al README](../README.md)
