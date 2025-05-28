# Esercizio 1: Correzione Commit Base

## Obiettivo
Imparare le tecniche base per correggere commit utilizzando `git commit --amend`, gestire errori nei messaggi e piccole modifiche ai file.

## Scenario
Stai lavorando su un progetto di gestione biblioteca e hai fatto alcuni commit con errori che devono essere corretti.

## Setup Iniziale

```bash
# Creare nuovo repository
mkdir biblioteca-app && cd biblioteca-app
git init

# Creare struttura progetto
mkdir -p {src,tests,docs}
touch README.md

# Primo commit
echo "# Biblioteca App" > README.md
git add README.md
git commit -m "feat: add README file"
```

## Parte 1: Correzione Messaggio Commit

### Task 1.1: Messaggio Incompleto
```bash
# Creare file con errore nel messaggio
cat > src/book.js << 'EOF'
class Book {
  constructor(title, author, isbn) {
    this.title = title;
    this.author = author;
    this.isbn = isbn;
    this.isAvailable = true;
  }

  checkout() {
    if (!this.isAvailable) {
      throw new Error('Book is not available');
    }
    this.isAvailable = false;
  }

  return() {
    this.isAvailable = true;
  }
}

module.exports = Book;
EOF

# Commit con messaggio incompleto
git add src/book.js
git commit -m "add book class"

# ❌ Problema: messaggio non segue conventional commits
```

**Compito**: Correggi il messaggio del commit utilizzando `git commit --amend` per seguire il formato conventional commits.

**Soluzione Attesa**:
```bash
git commit --amend -m "feat(core): add Book class with checkout/return functionality

Implement Book class with:
- Constructor for title, author, ISBN
- Checkout method with availability check
- Return method to mark book as available"
```

### Task 1.2: Dimenticato File
```bash
# Aggiungere test che doveva essere nel commit precedente
cat > tests/book.test.js << 'EOF'
const Book = require('../src/book');

describe('Book', () => {
  let book;

  beforeEach(() => {
    book = new Book('The Great Gatsby', 'F. Scott Fitzgerald', '978-0-7432-7356-5');
  });

  test('should create book with correct properties', () => {
    expect(book.title).toBe('The Great Gatsby');
    expect(book.author).toBe('F. Scott Fitzgerald');
    expect(book.isbn).toBe('978-0-7432-7356-5');
    expect(book.isAvailable).toBe(true);
  });

  test('should checkout book successfully', () => {
    book.checkout();
    expect(book.isAvailable).toBe(false);
  });

  test('should throw error when checking out unavailable book', () => {
    book.checkout();
    expect(() => book.checkout()).toThrow('Book is not available');
  });

  test('should return book successfully', () => {
    book.checkout();
    book.return();
    expect(book.isAvailable).toBe(true);
  });
});
EOF
```

**Compito**: Aggiungi il file test al commit precedente utilizzando `git commit --amend`.

**Soluzione Attesa**:
```bash
git add tests/book.test.js
git commit --amend --no-edit
```

## Parte 2: Correzione Contenuto File

### Task 2.1: Bug nel Codice
```bash
# Creare librarian class con bug
cat > src/librarian.js << 'EOF'
const Book = require('./book');

class Librarian {
  constructor(name) {
    this.name = name;
    this.books = [];
  }

  addBook(title, author, isbn) {
    const book = new Book(title, author, isbn);
    this.books.push(book);
    return book;
  }

  findBook(isbn) {
    // Bug: usa == invece di ===
    return this.books.find(book => book.isbn == isbn);
  }

  checkoutBook(isbn) {
    const book = this.findBook(isbn);
    if (!book) {
      throw new Error('Book not found');
    }
    book.checkout();
    return book;
  }
}

module.exports = Librarian;
EOF

git add src/librarian.js
git commit -m "feat(core): add Librarian class for book management"
```

**Compito**: Correggi il bug nella funzione `findBook` (usa `===` invece di `==`) e ammenda il commit.

**Soluzione Attesa**:
```bash
# Correggere il bug
sed -i 's/book.isbn == isbn/book.isbn === isbn/g' src/librarian.js

# Ammendare commit
git add src/librarian.js
git commit --amend --no-edit
```

### Task 2.2: Miglioramento Sicurezza
```bash
# Aggiungere validazione che mancava
cat >> src/librarian.js << 'EOF'

  // Metodi di validazione
  validateBookData(title, author, isbn) {
    if (!title || !author || !isbn) {
      throw new Error('Title, author, and ISBN are required');
    }
    
    // Validazione formato ISBN
    const isbnRegex = /^(?:ISBN(?:-1[03])?:? )?(?=[0-9X]{10}$|(?=(?:[0-9]+[- ]){3})[0-9]{1,5}[- ][0-9]+[- ][0-9]+[- ][0-9X]$|97[89][0-9]{10}$|(?=(?:[0-9]+[- ]){4})[- 0-9]{17}$)/;
    if (!isbnRegex.test(isbn.replace(/[- ]/g, ''))) {
      throw new Error('Invalid ISBN format');
    }
  }
EOF

# Modificare addBook per usare validazione
cat > src/librarian.js << 'EOF'
const Book = require('./book');

class Librarian {
  constructor(name) {
    this.name = name;
    this.books = [];
  }

  addBook(title, author, isbn) {
    this.validateBookData(title, author, isbn);
    const book = new Book(title, author, isbn);
    this.books.push(book);
    return book;
  }

  findBook(isbn) {
    return this.books.find(book => book.isbn === isbn);
  }

  checkoutBook(isbn) {
    const book = this.findBook(isbn);
    if (!book) {
      throw new Error('Book not found');
    }
    book.checkout();
    return book;
  }

  validateBookData(title, author, isbn) {
    if (!title || !author || !isbn) {
      throw new Error('Title, author, and ISBN are required');
    }
    
    // Validazione formato ISBN
    const isbnRegex = /^(?:ISBN(?:-1[03])?:? )?(?=[0-9X]{10}$|(?=(?:[0-9]+[- ]){3})[0-9]{1,5}[- ][0-9]+[- ][0-9]+[- ][0-9X]$|97[89][0-9]{10}$|(?=(?:[0-9]+[- ]){4})[- 0-9]{17}$)/;
    if (!isbnRegex.test(isbn.replace(/[- ]/g, ''))) {
      throw new Error('Invalid ISBN format');
    }
  }
}

module.exports = Librarian;
EOF
```

**Compito**: Ammenda il commit precedente per includere la validazione migliorata.

**Soluzione Attesa**:
```bash
git add src/librarian.js
git commit --amend -m "feat(core): add Librarian class with input validation

Implement Librarian class with:
- Book management (add, find, checkout)
- ISBN format validation
- Required fields validation
- Strict equality comparisons for security"
```

## Parte 3: Verifica e Documentazione

### Task 3.1: Verifica Stato
**Compito**: Controlla lo stato del repository e verifica che tutti i commit siano corretti.

**Comandi da utilizzare**:
```bash
# Verificare log commit
git log --oneline -5

# Verificare ultimo commit in dettaglio
git show

# Verificare differenze working directory
git status
```

### Task 3.2: Documentazione
**Compito**: Crea un file `CONTRIBUTING.md` con le regole per i commit message.

**Contenuto atteso**:
```bash
cat > CONTRIBUTING.md << 'EOF'
# Contributing Guidelines

## Commit Message Format

Usa il formato Conventional Commits:

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types
- feat: nuova funzionalità
- fix: correzione bug
- docs: solo documentazione
- style: formattazione, no logic changes
- refactor: refactoring codice
- test: aggiunta test
- chore: manutenzione

### Scope
- core: funzionalità principali
- ui: interfaccia utente
- api: API endpoints
- db: database
- config: configurazione

### Examples
```
feat(core): add book reservation system
fix(api): handle empty response in book search
docs(readme): update installation instructions
```

## Amending Commits

Se devi correggere l'ultimo commit:

```bash
# Solo messaggio
git commit --amend -m "nuovo messaggio"

# Aggiungere file
git add file.js
git commit --amend --no-edit

# Modificare e messaggio
git add file.js
git commit --amend -m "messaggio corretto"
```
EOF

git add CONTRIBUTING.md
git commit -m "docs: add contributing guidelines for commit messages"
```

## Risultati Attesi

Al termine dell'esercizio dovresti avere:

1. **Repository pulito** con commit ben formattati
2. **Messaggi conventional** seguendo lo standard
3. **Codice corretto** senza bug di sintassi
4. **Validazione robusta** per input utente
5. **Documentazione** delle pratiche di contribuzione

### Verifica Finale
```bash
# Log deve mostrare:
git log --oneline

# Output atteso:
# abc1234 docs: add contributing guidelines for commit messages
# def5678 feat(core): add Librarian class with input validation
# ghi9012 feat(core): add Book class with checkout/return functionality
# jkl3456 feat: add README file
```

## Domande di Riflessione

1. **Quando usare --amend**: In quali situazioni è appropriato ammendare un commit?
2. **Rischi**: Quali sono i rischi dell'ammending in un team?
3. **Alternative**: Che alternative esistono all'ammending per correggere errori?
4. **Best Practices**: Come prevenire la necessità di ammendare commit?

## Estensioni Opzionali

### Livello Avanzato
- Implementa pre-commit hooks per validare messaggi
- Crea script per automatizzare il format checking
- Aggiungi template per commit messages

### Integrazione
- Configura editor per template commit
- Imposta alias Git per ammending rapido
- Crea checklist pre-commit
