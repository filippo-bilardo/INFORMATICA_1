# Staging Interattivo: Controllo Granulare delle Modifiche

## 🎯 Obiettivi di Apprendimento
- Padroneggiare il staging interattivo con `git add -p`
- Utilizzare il patch mode per commit atomici precisi
- Gestire hunk splitting e editing manuale
- Implementare workflow professionali con staging granulare

## 🎭 Introduzione al Staging Interattivo

Il **staging interattivo** permette di selezionare esattamente quali parti di un file committare, offrendo un controllo granulare che va oltre il semplice file-by-file staging.

### Perché Usare Staging Interattivo?
- **Commit atomici**: Una sola modifica logica per commit
- **Code review migliore**: Commit più piccoli e focalizzati
- **Debugging facilitato**: Più facile identificare quando è stato introdotto un bug
- **Cronologia pulita**: Storia del progetto più leggibile

## 🚀 Comando Base: `git add -p`

### Sintassi e Varianti
```bash
git add -p [<file>...]           # Staging interattivo per file specificati
git add --patch [<file>...]      # Forma estesa
git add -p                       # Tutti i file modificati tracciati
```

### Primo Esempio Pratico
```bash
# Modifica un file con diverse modifiche
echo "function newFeature() { return 'feature'; }" >> app.js
echo "console.log('debug info');" >> app.js
echo "function anotherFeature() { return 'another'; }" >> app.js

# Staging interattivo
git add -p app.js
```

## 🧩 Anatomia di un Hunk

### Cosa Sono gli Hunk?
Un **hunk** è un blocco di modifiche contigue che Git può identificare e gestire autonomamente.

### Struttura di un Hunk
```diff
@@ -1,4 +1,8 @@
 function existingFunction() {
     return 'existing';
 }
+
+function newFeature() {
+    return 'feature';
+}
```

#### Interpretazione Header
- `@@` - Delimitatori dell'header
- `-1,4` - File originale: inizia dalla riga 1, 4 righe di contesto
- `+1,8` - File nuovo: inizia dalla riga 1, 8 righe totali
- Righe con ` ` (spazio) - Contesto non modificato
- Righe con `+` - Aggiunte
- Righe con `-` - Rimozioni

## 🎛️ Opzioni del Patch Mode

### Menu Completo delle Opzioni
```
Stage this hunk [y,n,q,a,d,/,j,J,k,K,s,e,?]?
```

| Comando | Nome | Funzione | Quando Usare |
|---------|------|----------|--------------|
| `y` | Yes | Aggiungi questo hunk | Modifica da committare |
| `n` | No | Salta questo hunk | Modifica da non committare |
| `q` | Quit | Esci dal patch mode | Finito con le decisioni |
| `a` | Add all | Aggiungi tutti gli hunk rimanenti | Tutte le altre modifiche sono OK |
| `d` | Don't add | Salta tutti gli hunk rimanenti | Nessuna delle altre modifiche |
| `s` | Split | Dividi hunk in parti più piccole | Hunk contiene modifiche diverse |
| `e` | Edit | Modifica manualmente l'hunk | Controllo granulare estremo |
| `j` | Jump next | Vai al prossimo hunk non deciso | Navigazione in file grandi |
| `J` | Jump next | Vai al prossimo hunk | Navigazione forzata |
| `k` | Jump previous | Vai all'hunk precedente non deciso | Tornare indietro |
| `K` | Jump previous | Vai all'hunk precedente | Navigazione all'indietro |
| `/` | Search | Cerca hunk con pattern | File molto grandi |
| `?` | Help | Mostra questo menu | Quando sei confuso |

## 🎨 Workflow Pratici di Staging Interattivo

### Scenario 1: Feature + Bug Fix nel Stesso File

#### File con Modifiche Miste
```javascript
// utils.js - Modifiche multiple
function validateEmail(email) {
    // ✅ FEATURE: Nuova validazione email (da committare)
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(email)) {
        return false;
    }
    return true;
}

function formatDate(date) {
    // ❌ DEBUG: Log temporaneo (NON committare)
    console.log('DEBUG: formatting date', date);
    
    // ✅ BUG FIX: Gestione null date (da committare)
    if (!date) {
        return 'Invalid date';
    }
    return date.toLocaleDateString();
}

function calculateTotal(items) {
    // ❌ TEMP: Test di performance (NON committare)
    console.time('calculateTotal');
    
    // ✅ FEATURE: Nuovo calcolo con tasse (da committare)
    const subtotal = items.reduce((sum, item) => sum + item.price, 0);
    const tax = subtotal * 0.1;
    
    // ❌ TEMP: Test di performance (NON committare)
    console.timeEnd('calculateTotal');
    
    return subtotal + tax;
}
```

#### Sessione di Staging Interattivo
```bash
$ git add -p utils.js

# Hunk 1: validateEmail function
@@ -1,3 +1,8 @@
 function validateEmail(email) {
+    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
+    if (!emailRegex.test(email)) {
+        return false;
+    }
+    return true;
 }

Stage this hunk [y,n,q,a,d,/,s,e,?]? y  # ✅ Commit la feature

# Hunk 2: formatDate function con debug log
@@ -5,2 +10,8 @@
 function formatDate(date) {
+    console.log('DEBUG: formatting date', date);
+    
+    if (!date) {
+        return 'Invalid date';
+    }
     return date.toLocaleDateString();
 }

Stage this hunk [y,n,q,a,d,/,s,e,?]? s  # ✅ Split l'hunk

# Hunk 2a: Solo debug log
@@ -5,2 +10,4 @@
 function formatDate(date) {
+    console.log('DEBUG: formatting date', date);
+    
     return date.toLocaleDateString();

Stage this hunk [y,n,q,a,d,/,s,e,?]? n  # ❌ Non committare debug

# Hunk 2b: Solo bug fix
@@ -8,1 +13,4 @@
     
+    if (!date) {
+        return 'Invalid date';
+    }
     return date.toLocaleDateString();

Stage this hunk [y,n,q,a,d,/,s,e,?]? y  # ✅ Commit il bug fix
```

### Scenario 2: Refactoring Graduali

#### File da Refactorare Progressivamente
```python
# api.py - Refactoring step-by-step
class UserAPI:
    def __init__(self):
        # ✅ REFACTOR: Nuovo pattern di inizializzazione (commit)
        self.db = Database()
        self.validator = Validator()
        
    def get_user(self, user_id):
        # ❌ OLD: Vecchio codice da rimuovere dopo (non commit)
        # if not user_id:
        #     return None
            
        # ✅ REFACTOR: Nuova validazione (commit)
        if not self.validator.validate_id(user_id):
            raise ValueError("Invalid user ID")
            
        return self.db.get(user_id)
    
    def create_user(self, data):
        # ✅ REFACTOR: Nuovo pattern di creazione (commit)
        validated_data = self.validator.validate_user_data(data)
        
        # ❌ TEMP: Log per testing (non commit)
        print(f"Creating user: {validated_data}")
        
        return self.db.create(validated_data)
```

#### Strategia di Staging
```bash
# Commit solo le parti refactored, non i commenti old/temp
git add -p api.py

# Risultato: commit pulito con solo il nuovo codice
git commit -m "refactor: improve user API with better validation

- Add proper input validation for user operations
- Implement new initialization pattern
- Improve error handling with meaningful exceptions"
```

## 🔧 Tecniche Avanzate di Staging Interattivo

### Splitting di Hunk Complessi

#### Quando Git Non Riesce a Splittare
```bash
# Se 's' non funziona, usa edit mode
Stage this hunk [y,n,q,a,d,/,s,e,?]? e
```

#### Edit Mode Manuale
Quando selezioni `e`, Git apre l'editor con l'hunk:

```diff
# To remove lines, delete them.
# Lines starting with # will be removed.
#
# If the patch applies cleanly, the edited hunk will immediately be
# marked for staging.
# If it does not apply cleanly, you will be given an opportunity to
# edit again. If all lines of the hunk are removed, then the edit is
# aborted and the hunk is left unchanged.
@@ -1,8 +1,12 @@
 function process(data) {
+    // New validation
+    if (!data) return null;
+    
     console.log('processing');
+    
+    // New feature
+    const result = transform(data);
     return data;
 }
```

#### Tecniche di Edit Mode
```diff
# Per mantenere solo alcune righe, aggiungi # alle altre:
@@ -1,8 +1,12 @@
 function process(data) {
+    // New validation
+    if (!data) return null;
+    
# console.log('processing');  # ← Linea commentata = non verrà committata
+    
+    // New feature
+    const result = transform(data);
     return data;
 }
```

### Search e Navigation in File Grandi

#### Uso della Search (`/`)
```bash
# In un file con molti hunk
Stage this hunk [y,n,q,a,d,/,s,e,?]? /

# Git chiede il pattern di ricerca
search for regex: function.*test

# Git salta al prossimo hunk che matcha il pattern
```

#### Navigation Avanzata
```bash
# Saltare hunk senza decidere
j  # Prossimo hunk non deciso
J  # Prossimo hunk (anche se già deciso)
k  # Hunk precedente non deciso  
K  # Hunk precedente (anche se già deciso)
```

## 🧪 Laboratorio Pratico Avanzato

### Esercizio 1: Feature Development Multi-Fase
```bash
# Setup complesso
mkdir staging-advanced-lab
cd staging-advanced-lab
git init

# Crea file con modifiche multiple
cat > service.js << 'EOF'
class DataService {
    constructor() {
        this.cache = new Map();
    }
    
    // Feature 1: Caching mechanism
    getData(id) {
        if (this.cache.has(id)) {
            return this.cache.get(id);
        }
        
        // Debug log (remove later)
        console.log(`Fetching data for ${id}`);
        
        const data = this.fetchFromAPI(id);
        this.cache.set(id, data);
        return data;
    }
    
    // Feature 2: Batch operations
    getBatch(ids) {
        console.log('DEBUG: batch operation');  // Remove this
        return ids.map(id => this.getData(id));
    }
    
    // Bug fix: Clear cache method
    clearCache() {
        console.log('Clearing cache');  // Keep for monitoring
        this.cache.clear();
    }
}
EOF

# Staging strategy
git add -p service.js
# Commit 1: Solo caching mechanism (no debug)
# Commit 2: Solo batch operations (no debug) 
# Commit 3: Bug fix con monitoring log
```

### Esercizio 2: Code Review Preparation
```bash
# Scenario: Preparing clean commits for review
cat > component.vue << 'EOF'
<template>
  <div class="user-profile">
    <!-- Feature: New header layout -->
    <header class="profile-header">
      <img :src="user.avatar" alt="Avatar">
      <h1>{{ user.name }}</h1>
    </header>
    
    <!-- Debug: Remove this div -->
    <div style="border: 1px solid red;">DEBUG CONTAINER</div>
    
    <!-- Feature: Enhanced user info -->
    <section class="user-info">
      <p>Email: {{ user.email }}</p>
      <p>Joined: {{ formatDate(user.joinDate) }}</p>
    </section>
    
    <!-- Bug fix: Proper error handling -->
    <div v-if="error" class="error-message">
      {{ error }}
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      user: null,
      error: null,
      debugMode: true  // Remove this
    }
  },
  
  methods: {
    // Feature: Date formatting
    formatDate(date) {
      return new Intl.DateTimeFormat('en-US').format(new Date(date));
    },
    
    // Debug method (remove)
    debugLog(msg) {
      if (this.debugMode) console.log(msg);
    }
  }
}
</script>
EOF

# Challenge: Create 3 clean commits
# 1. Header layout feature
# 2. Enhanced user info feature  
# 3. Error handling bug fix
# (No debug code in any commit)
```

## 🎯 Strategie di Staging per Team

### 1. Feature Branch Workflow
```bash
# Branch per feature complessa
git checkout -b feature/user-dashboard

# Sviluppo iterativo con staging granulare
# Session 1: Core structure
git add -p
git commit -m "feat: add dashboard core structure"

# Session 2: Data integration  
git add -p
git commit -m "feat: integrate user data in dashboard"

# Session 3: Polish and optimization
git add -p
git commit -m "perf: optimize dashboard rendering"
```

### 2. Code Review Optimization
```bash
# Preparazione per review
# Commit logici separati facilitano il review

# Commit 1: Tests
git add tests/
git commit -m "test: add comprehensive user tests"

# Commit 2: Implementation (con staging selettivo)
git add -p src/
git commit -m "feat: implement user management system"

# Commit 3: Documentation
git add docs/ README.md
git commit -m "docs: add user management documentation"
```

### 3. Hotfix con Context Preservation
```bash
# Scenario: Bug critico con work-in-progress
git stash push -m "WIP: feature development"
git checkout main

# Fix con staging preciso
git add -p
git commit -m "hotfix: resolve critical authentication bug"

# Ritorna al lavoro
git checkout feature-branch
git stash pop
```

## 🛡️ Best Practices per Staging Interattivo

### 1. Preparazione Pre-Staging
```bash
# Review completa prima del staging
git diff                    # Vedere tutte le modifiche
git status                  # Stato generale
git diff --name-only        # Lista file modificati
```

### 2. Staging Strategy Planning
- **Raggruppa per logica**: Modifiche correlate insieme
- **Separa concerns**: Feature, bug fix, refactoring in commit diversi
- **Documenta decisioni**: Note nei commit messages del perché

### 3. Quality Gates
```bash
# Dopo ogni staging session
git diff --cached          # Review staging area
git status                 # Conferma stato
# Test del codice in staging prima del commit
```

## 🔍 Troubleshooting Staging Interattivo

### Problema: "Hunk troppo grande per split"
```bash
# Soluzione: Edit mode manuale
Stage this hunk [y,n,q,a,d,/,s,e,?]? e
# Rimuovi righe non volute con # prefix
```

### Problema: "Perso in sessione lunga"
```bash
# Soluzione: Quit sicuro e restart
Stage this hunk [y,n,q,a,d,/,s,e,?]? q
git status                 # Vedere cosa è già in staging
git diff --cached          # Review staging corrente
git add -p                 # Ripartire da dove eri rimasto
```

### Problema: "Edit mode non applica cleanly"
```bash
# Errore comune: formato diff malformato
# Soluzione: Cancella tutto e ricomincia
# In edit mode: cancella tutto il contenuto e salva
# Git aborterà l'edit e manterrà l'hunk originale
```

## 📚 Comandi Correlati

### Staging Interattivo per Altri Comandi
```bash
git reset -p               # Unstaging interattivo
git checkout -p            # Restore interattivo
git stash -p               # Stash interattivo
```

### Integration con Altri Tools
```bash
# Con commit amend
git add -p && git commit --amend

# Con rebase interattivo
git add -p && git rebase -i HEAD~3

# Con stash
git stash -p               # Stash solo parti di modifiche
```

## 🔗 Collegamenti e Risorse

### Link Interni
- [📖 Git Add Avanzato](./03-git-add-avanzato.md) - Prerequisiti per staging avanzato
- [📖 Git Reset Staging](./04-git-reset-staging.md) - Unstaging e correzioni
- [📖 Tre Aree Git](./02-tre-aree-git.md) - Comprensione fondamentale

### Best Practices Correlate
- **Atomic Commits**: Ogni commit una sola idea logica
- **Clean History**: Cronologia leggibile e significativa
- **Code Review**: Commit organizzati facilitano la review

---

> **💡 Filosofia del Staging Interattivo**: Non si tratta solo di tecnologia, ma di disciplina. Ogni decisione di staging è una decisione di design della cronologia del progetto. Staging interattivo trasforma il chaos delle modifiche daily in una storia coerente e professionale.
