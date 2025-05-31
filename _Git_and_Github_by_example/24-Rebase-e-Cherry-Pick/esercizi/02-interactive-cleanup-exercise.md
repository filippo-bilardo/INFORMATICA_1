# Esercizio 2: Interactive Rebase e Cleanup

## 🎯 Obiettivo
Masterizzare l'uso dell'interactive rebase per pulire una cronologia di commit disordinata, utilizzando tutte le operazioni disponibili (squash, fixup, reword, edit, drop).

## 📋 Scenario
Hai lavorato su una feature per implementare un sistema di commenti. Durante lo sviluppo hai creato molti commit di debug, correzioni di typo, esperimenti e commit temporanei. Prima del merge finale, devi pulire la cronologia per renderla professionale.

## 🏗️ Setup Iniziale

```bash
#!/bin/bash
# Creazione ambiente disordinato per l'esercizio
mkdir interactive-rebase-exercise && cd interactive-rebase-exercise
git init
git config user.name "Student Developer"
git config user.email "student@dev.com"

echo "🏗️ Creazione cronologia disordinata..."

# Setup progetto base
mkdir -p src/components src/services tests
echo "# Comment System" > README.md
echo '{"name": "comment-system", "version": "1.0.0"}' > package.json
git add .
git commit -m "Initial project setup"

# Branch per la feature
git checkout -b feature/comments-system

# Simulazione sviluppo disordinato (commit che dovrai pulire)
echo "// Comment component placeholder" > src/components/Comment.js
git add .
git commit -m "WIP: starting comment component"

echo "console.log('debug: component loaded');" >> src/components/Comment.js
git add .
git commit -m "add debug log"

cat > src/components/Comment.js << 'EOF'
import React from 'react';

const Comment = ({ text, author, timestamp }) => {
  console.log('debug: component loaded');
  return (
    <div className="comment">
      <p>{text}</p>
      <small>By {author} on {timestamp}</small>
    </div>
  );
};

export default Comment;
EOF
git add .
git commit -m "implement basic comment component"

echo "/* TODO: add css styles */" > src/components/Comment.css
git add .
git commit -m "add css file"

# Typo fix
cat > src/components/Comment.js << 'EOF'
import React from 'react';

const Comment = ({ text, author, timestamp }) => {
  console.log('debug: component loaded');
  return (
    <div className="comment">
      <p>{text}</p>
      <small>By {author} on {timestamp}</small>
    </div>
  );
};

export default Comment;
EOF
git add .
git commit -m "fix typo in import"

# Service implementation
cat > src/services/commentService.js << 'EOF'
const API_BASE = '/api/comments';

export const fetchComments = async () => {
  console.log('fetching comments...');
  const response = await fetch(API_BASE);
  return response.json();
};

export const createComment = async (commentData) => {
  console.log('creating comment...', commentData);
  const response = await fetch(API_BASE, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(commentData)
  });
  return response.json();
};
EOF
git add .
git commit -m "add comment service with debug logs"

# Remove debug logs
cat > src/services/commentService.js << 'EOF'
const API_BASE = '/api/comments';

export const fetchComments = async () => {
  const response = await fetch(API_BASE);
  return response.json();
};

export const createComment = async (commentData) => {
  const response = await fetch(API_BASE, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(commentData)
  });
  return response.json();
};
EOF
git add .
git commit -m "remove debug logs from service"

# Another debug addition
echo "console.log('Service module loaded');" >> src/services/commentService.js
git add .
git commit -m "oops forgot to remove this debug log"

# Remove it again
cat > src/services/commentService.js << 'EOF'
const API_BASE = '/api/comments';

export const fetchComments = async () => {
  const response = await fetch(API_BASE);
  return response.json();
};

export const createComment = async (commentData) => {
  const response = await fetch(API_BASE, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(commentData)
  });
  return response.json();
};
EOF
git add .
git commit -m "really remove debug log this time"

# CSS implementation
cat > src/components/Comment.css << 'EOF'
.comment {
  border: 1px solid #ddd;
  padding: 10px;
  margin: 5px 0;
  border-radius: 4px;
}

.comment p {
  margin: 0 0 8px 0;
  font-size: 14px;
}

.comment small {
  color: #666;
  font-size: 12px;
}
EOF
git add .
git commit -m "implement comment styles"

# Test file
cat > tests/Comment.test.js << 'EOF'
import { render, screen } from '@testing-library/react';
import Comment from '../src/components/Comment';

describe('Comment Component', () => {
  it('renders comment text', () => {
    render(<Comment text="Test comment" author="John" timestamp="2024-01-01" />);
    expect(screen.getByText('Test comment')).toBeInTheDocument();
  });

  it('renders author and timestamp', () => {
    render(<Comment text="Test" author="Jane" timestamp="2024-01-02" />);
    expect(screen.getByText(/By Jane on 2024-01-02/)).toBeInTheDocument();
  });
});
EOF
git add .
git commit -m "add comprehensive tests for comment component"

# Documentation
cat > README.md << 'EOF'
# Comment System

A React-based comment system with full CRUD operations.

## Features

- Display comments with author and timestamp
- Add new comments
- Responsive design
- Comprehensive test coverage

## Installation

```bash
npm install
```

## Usage

```jsx
import Comment from './components/Comment';

<Comment 
  text="Great article!" 
  author="John Doe" 
  timestamp="2024-01-01" 
/>
```

## API

- `fetchComments()` - Retrieve all comments
- `createComment(data)` - Create new comment

## Testing

```bash
npm test
```
EOF
git add .
git commit -m "update documentation with full api and usage"

echo "✅ Cronologia disordinata creata!"
echo "📊 Stato attuale:"
git log --oneline
```

## 📝 Compiti da Svolgere

### Parte 1: Analisi della Cronologia Attuale

1. **Esamina la cronologia corrente:**
   ```bash
   git log --oneline
   git log --oneline --graph
   ```

2. **Identifica i problemi nella cronologia:**
   - Commit di debug
   - Commit che annullano commit precedenti
   - Messaggi non descrittivi
   - Commit troppo piccoli che dovrebbero essere combinati

### Parte 2: Pianificazione del Cleanup

3. **Pianifica le operazioni di cleanup necessarie:**
   
   **Operazioni da applicare:**
   - **SQUASH**: Combina commit correlati
   - **FIXUP**: Incorpora correzioni nei commit originali
   - **REWORD**: Migliora messaggi di commit
   - **DROP**: Elimina commit inutili
   - **EDIT**: Modifica contenuto di commit specifici

### Parte 3: Esecuzione Interactive Rebase

4. **Avvia interactive rebase:**
   ```bash
   # Conta quanti commit hai fatto sul branch feature
   git log --oneline main..HEAD
   
   # Avvia interactive rebase (sostituisci N con il numero di commit)
   git rebase -i HEAD~N
   ```

5. **Applica le seguenti trasformazioni:**

   **Obiettivo finale - Cronologia pulita:**
   ```
   * Add comprehensive comment system with tests and documentation
   * Implement comment component with styling  
   * Add comment service API
   * Initial project setup
   ```

   **Suggerimenti per l'editor:**
   ```
   # Esempio di quello che dovresti fare nell'editor:
   pick abc1234 Initial project setup
   squash def5678 WIP: starting comment component
   squash ghi9012 implement basic comment component
   drop jkl3456 add debug log
   fixup mno7890 fix typo in import
   squash pqr2468 add css file
   squash stu1357 implement comment styles
   pick vwx9753 add comment service with debug logs
   fixup yza4680 remove debug logs from service
   drop bcd8024 oops forgot to remove this debug log
   drop efg1357 really remove debug log this time
   squash hij9864 add comprehensive tests for comment component
   squash klm2468 update documentation with full api and usage
   reword nop1357 (cambieremo il messaggio durante il rebase)
   ```

### Parte 4: Gestione del Processo Interattivo

6. **Durante il rebase interattivo:**
   
   **Per REWORD:**
   - Cambia il messaggio in qualcosa di più descrittivo
   - Esempio: "Add comprehensive comment system with tests and documentation"

   **Per SQUASH:**
   - Combina i messaggi in modo significativo
   - Rimuovi riferimenti a debug e lavori temporanei

   **Se ci sono conflitti:**
   ```bash
   # Risolvi i conflitti manualmente, poi:
   git add .
   git rebase --continue
   ```

### Parte 5: Verifica Risultato

7. **Verifica la cronologia finale:**
   ```bash
   git log --oneline --graph
   git log --stat
   ```

8. **Testa che tutto funzioni:**
   ```bash
   # Verifica che tutti i file siano presenti
   ls -la src/components/
   ls -la src/services/
   ls -la tests/
   
   # Controlla il contenuto dei file principali
   cat src/components/Comment.js
   cat src/services/commentService.js
   ```

## ✅ Risultati Attesi

### Cronologia Prima del Cleanup:
```
* update documentation with full api and usage
* add comprehensive tests for comment component  
* implement comment styles
* add css file
* really remove debug log this time
* oops forgot to remove this debug log
* remove debug logs from service
* add comment service with debug logs
* fix typo in import
* add debug log
* implement basic comment component
* WIP: starting comment component
* Initial project setup
```

### Cronologia Dopo il Cleanup:
```
* Add comprehensive comment system with tests and documentation
* Implement comment component with styling
* Add comment service API  
* Initial project setup
```

## 🤔 Domande di Riflessione

1. **Vantaggi del cleanup:**
   - Come migliorano la leggibilità della cronologia?
   - Perché è importante per il code review?

2. **Quando fare cleanup:**
   - Prima del merge in main?
   - Durante lo sviluppo?
   - Mai su commit già pushati?

3. **Rischi del rebase:**
   - Cosa succede se qualcun altro ha basato lavoro sui tuoi commit?
   - Come evitare problemi di collaborazione?

## 🚨 Safety Tips

1. **Backup prima del rebase:**
   ```bash
   git branch backup-before-rebase
   ```

2. **Solo su branch locali:**
   - Non fare rebase di commit già pushati e condivisi

3. **Usa reflog per recovery:**
   ```bash
   git reflog
   git reset --hard HEAD@{n}
   ```

## 🎉 Challenge Avanzato

Una volta completato l'esercizio base:

1. **Crea più scenari disordinati** con diversi tipi di commit da pulire
2. **Pratica l'operazione EDIT** per modificare il contenuto di commit esistenti
3. **Combina rebase con cherry-pick** per riorganizzare commit tra branch diversi
4. **Automatizza il processo** con script di pre-commit hooks

## 📚 Riferimenti

- [Guida Interactive Rebase](../guide/02-interactive-rebase.md)
- [Esempio Interactive Cleanup](../esempi/02-interactive-cleanup.md)
- [Rebase vs Merge](../guide/04-rebase-vs-merge.md)
