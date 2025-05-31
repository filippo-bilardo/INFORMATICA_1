# 01 - Esercizio: Staging Selettivo Guidato

## 📖 Descrizione

In questo esercizio metterai in pratica le tecniche di staging selettivo su un progetto realistico. Dovrai organizzare modifiche complesse in commit logici e atomici.

## 🎯 Obiettivi

- Applicare `git add -p` in scenari realistici
- Creare commit logici e atomici
- Gestire staging area in modo professionale
- Dimostrare comprensione dei workflow di staging

## 📋 Prerequisiti

- Aver completato le guide teoriche del modulo
- Conoscenza base di JavaScript (per comprendere il codice)
- Git installato e configurato

## ⏱️ Durata Stimata

**45-60 minuti**

## 🚀 Setup dell'Esercizio

### Step 1: Crea il Progetto
```bash
# Crea directory
mkdir staging-exercise
cd staging-exercise
git init

# Crea struttura
mkdir src tests docs
mkdir src/components src/utils src/api
```

### Step 2: File Iniziale
```bash
# Crea file base: src/blog-manager.js
cat > src/blog-manager.js << 'EOF'
class BlogManager {
    constructor() {
        this.posts = [];
        this.users = [];
    }

    addPost(post) {
        this.posts.push(post);
    }

    getPost(id) {
        return this.posts.find(p => p.id === id);
    }

    addUser(user) {
        this.users.push(user);
    }

    getUser(id) {
        return this.users.find(u => u.id === id);
    }
}

module.exports = BlogManager;
EOF

# Commit iniziale
git add .
git commit -m "Initial blog manager implementation"
```

## 📝 Esercizio Parte 1: Modifiche Multiple

### Task 1: Implementa le Modifiche

Ora devi modificare il file `src/blog-manager.js` per includere TUTTE queste modifiche insieme:

```bash
cat > src/blog-manager.js << 'EOF'
class BlogManager {
    constructor() {
        this.blogPosts = [];        // REFACTOR: renamed from 'posts'
        this.registeredUsers = [];  // REFACTOR: renamed from 'users'
        this.categories = [];       // FEATURE: new categories system
        this.nextId = 1;           // FEATURE: auto-incrementing IDs
    }

    // FEATURE: Enhanced post creation with validation
    addPost(postData) {
        // INPUT VALIDATION
        if (!postData.title || postData.title.trim() === '') {
            throw new Error('Post title is required');
        }
        if (!postData.content || postData.content.trim() === '') {
            throw new Error('Post content is required');
        }
        if (!postData.authorId) {
            throw new Error('Author ID is required');
        }

        // BUGFIX: Check if author exists
        const author = this.getUser(postData.authorId);
        if (!author) {
            throw new Error('Author not found');
        }

        // FEATURE: Auto-generate ID and timestamp
        const post = {
            id: this.nextId++,
            title: postData.title.trim(),
            content: postData.content.trim(),
            authorId: postData.authorId,
            categoryId: postData.categoryId || null,
            createdAt: new Date().toISOString(),
            published: false
        };

        this.blogPosts.push(post);
        return post;
    }

    getPost(postId) {  // REFACTOR: renamed parameter for clarity
        return this.blogPosts.find(post => post.id === postId);
    }

    // FEATURE: New method - publish post
    publishPost(postId) {
        const post = this.getPost(postId);
        if (!post) {
            throw new Error('Post not found');
        }
        post.published = true;
        post.publishedAt = new Date().toISOString();
        return post;
    }

    // FEATURE: Get published posts only
    getPublishedPosts() {
        return this.blogPosts.filter(post => post.published);
    }

    // FEATURE: Enhanced user registration with validation
    addUser(userData) {
        // INPUT VALIDATION
        if (!userData.username || userData.username.trim() === '') {
            throw new Error('Username is required');
        }
        if (!userData.email || userData.email.trim() === '') {
            throw new Error('Email is required');
        }

        // BUGFIX: Check for duplicate username
        const existingUser = this.registeredUsers.find(u => u.username === userData.username);
        if (existingUser) {
            throw new Error('Username already exists');
        }

        // BUGFIX: Basic email validation
        if (!userData.email.includes('@')) {
            throw new Error('Invalid email format');
        }

        const user = {
            id: this.nextId++,
            username: userData.username.trim(),
            email: userData.email.trim(),
            createdAt: new Date().toISOString(),
            active: true
        };

        this.registeredUsers.push(user);
        return user;
    }

    getUser(userId) {  // REFACTOR: renamed parameter for clarity
        return this.registeredUsers.find(user => user.id === userId);
    }

    // FEATURE: New categories management
    addCategory(categoryData) {
        if (!categoryData.name || categoryData.name.trim() === '') {
            throw new Error('Category name is required');
        }

        const category = {
            id: this.nextId++,
            name: categoryData.name.trim(),
            description: categoryData.description || '',
            createdAt: new Date().toISOString()
        };

        this.categories.push(category);
        return category;
    }

    getCategory(categoryId) {
        return this.categories.find(cat => cat.id === categoryId);
    }

    getPostsByCategory(categoryId) {
        return this.blogPosts.filter(post => post.categoryId === categoryId);
    }

    // FEATURE: Search functionality
    searchPosts(query) {
        const searchTerm = query.toLowerCase();
        return this.blogPosts.filter(post => 
            post.title.toLowerCase().includes(searchTerm) ||
            post.content.toLowerCase().includes(searchTerm)
        );
    }

    // PERFORMANCE: Get statistics (might be slow for large datasets)
    getStatistics() {
        return {
            totalPosts: this.blogPosts.length,
            publishedPosts: this.getPublishedPosts().length,
            totalUsers: this.registeredUsers.length,
            activeUsers: this.registeredUsers.filter(u => u.active).length,
            totalCategories: this.categories.length
        };
    }
}

module.exports = BlogManager;
EOF
```

## 🎯 Task 2: Staging Selettivo

Ora devi organizzare queste modifiche in commit logici usando `git add -p`. Crea esattamente questi 5 commit nell'ordine specificato:

### Commit 1: "Fix user and post validation issues"
Deve includere solo:
- Validazione input per `addPost()`
- Check se author esiste in `addPost()`
- Validazione input per `addUser()`
- Check per username duplicato
- Validazione email base

**Comando da usare:**
```bash
git add -p src/blog-manager.js
# Accetta solo le righe di validazione e controlli errori
# Rifiuta refactoring, features nuove, etc.
```

### Commit 2: "Add automatic ID generation system"
Deve includere solo:
- Proprietà `nextId = 1` nel constructor
- Uso di `this.nextId++` in tutti i metodi che creano oggetti

### Commit 3: "Implement category management system"
Deve includere solo:
- Proprietà `categories = []` nel constructor  
- Tutti i metodi category: `addCategory()`, `getCategory()`, `getPostsByCategory()`
- Campo `categoryId` negli oggetti post

### Commit 4: "Add publishing and search features"
Deve includere solo:
- `publishPost()` method
- `getPublishedPosts()` method
- `searchPosts()` method
- Campi `published`, `publishedAt` negli oggetti post

### Commit 5: "Refactor variable names for consistency"
Deve includere solo:
- `posts` → `blogPosts`
- `users` → `registeredUsers`  
- Rinominazione parametri: `id` → `postId`, `id` → `userId`

**Non committare** il metodo `getStatistics()` - lascialo come modifica unstaged.

## 📊 Verifica dei Risultati

### Controlla i Tuoi Commit
```bash
git log --oneline
```

Dovresti vedere esattamente:
```
abc1234 Refactor variable names for consistency
def5678 Add publishing and search features  
ghi9012 Implement category management system
jkl3456 Add automatic ID generation system
mno7890 Fix user and post validation issues
pqr1234 Initial blog manager implementation
```

### Controlla cosa Rimane
```bash
git status
```

Dovresti vedere solo:
```
Changes not staged for commit:
    modified:   src/blog-manager.js
```

```bash
git diff src/blog-manager.js
```

Dovrebbe mostrare solo il metodo `getStatistics()` non committato.

## 💡 Suggerimenti per il Successo

### 1. Strategia di Approccio
```bash
# Prima di iniziare, analizza tutte le modifiche
git diff src/blog-manager.js | less

# Identifica i "blocchi logici" di modifiche
# Pianifica l'ordine dei commit
```

### 2. Uso Efficace di git add -p
```bash
# Quando un hunk è troppo grande:
Stage this hunk [y,n,q,a,d,s,e,?]? s  # Split in parti più piccole

# Per controllo totale:
Stage this hunk [y,n,q,a,d,s,e,?]? e  # Edit manualmente
```

### 3. Verifica Continua
```bash
# Dopo ogni add -p, controlla cosa hai staged:
git diff --staged

# Dopo ogni commit, controlla la progressione:
git log --oneline -5
git status
```

### 4. Recovery da Errori
```bash
# Se sbagli staging:
git reset src/blog-manager.js    # Rimuovi dalla staging
git add -p src/blog-manager.js   # Ricomincia

# Se commit sbagliato:
git reset --soft HEAD~1          # Annulla commit, mantieni staging
```

## 🔍 Criteri di Valutazione

### ✅ Commit Corretti (80 punti)
- [ ] 5 commit nell'ordine giusto
- [ ] Ogni commit contiene solo le modifiche specificate
- [ ] Messaggi commit chiari e descrittivi
- [ ] `getStatistics()` rimane unstaged

### ✅ Tecnica (15 punti)  
- [ ] Uso appropriato di `git add -p`
- [ ] Nessuna modifica estranea nei commit
- [ ] Cronologia pulita e logica

### ✅ Best Practices (5 punti)
- [ ] Commit atomici (ogni commit funziona indipendentemente)
- [ ] Separazione logica delle preoccupazioni
- [ ] Commit order facilita code review

## 🎯 Sfide Bonus (Opzionali)

### Sfida 1: Interactive Rebase
Dopo aver completato l'esercizio base:
```bash
git rebase -i HEAD~5
# Riordina i commit in ordine cronologico di sviluppo
# (validation → refactor → features → categories → publishing)
```

### Sfida 2: Commit Message Enhancement
Migliora i messaggi commit seguendo conventional commits:
```bash
git rebase -i HEAD~5
# Cambia i messaggi in:
# fix: user and post validation issues
# refactor: add automatic ID generation system  
# feat: implement category management system
# feat: add publishing and search features
# refactor: variable names for consistency
```

### Sfida 3: Tests e Docs
Aggiungi test e documentazione per ogni commit:
```bash
# Per ogni commit, aggiungi:
echo "test for feature X" > tests/test-feature-x.js
git add tests/test-feature-x.js
git commit --amend --no-edit  # Includi nel commit esistente
```

## 📱 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ Esempi Pratici](../esempi/03-team-workflow.md)
- [➡️ Prossimo Esercizio](./02-conflitti-staging.md)

---

**Prossimo passo**: [Esercizio Conflitti](./02-conflitti-staging.md) - Gestisci situazioni complesse
