# Esempio 03: Correzione Staging

## 📖 Descrizione

Questo esempio dimostra come correggere errori comuni nell'area di staging, incluso come rimuovere file aggiunti per errore, modificare la selezione di file, e gestire situazioni complesse dove si sono fatti errori nel processo di staging.

## 🎯 Obiettivi

- Rimuovere file dall'area di staging
- Correggere staging parziali errati
- Gestire file rinominati incorrettamente
- Recuperare da errori di staging
- Utilizzare strategie di correzione sicure

## 🛠️ Scenario di Partenza

Supponiamo di lavorare su un progetto e-commerce dove abbiamo fatto diversi errori di staging:

```bash
# Creiamo il scenario con errori comuni
mkdir correzione-staging-demo && cd correzione-staging-demo
git init

# Creiamo diversi file
echo "const API_KEY = 'secret-key-123'" > config.js
echo "# TODO List" > todo.txt
echo "console.log('Debug info')" > debug.js
echo "# Shopping Cart Component" > cart.md
echo "function calculate() {}" > calculator.js

# File temporanei che non dovrebbero essere tracciati
echo "temp data" > temp.log
echo "cache" > .cache
```

## 🚨 Problemi Comuni e Soluzioni

### Problema 1: File Sensibili Aggiunti per Errore

```bash
# ERRORE: Aggiungiamo tutto senza controllo
git add .
git status
# Ops! Abbiamo aggiunto config.js con API keys!
```

**Soluzione 1: Rimuovere File Specifici**
```bash
# Rimuoviamo file sensibili dall'area di staging
git reset HEAD config.js

# Verifichiamo che sia stato rimosso
git status
# config.js ora è "untracked" di nuovo

# Aggiungiamo config.js al .gitignore per prevenire futuri errori
echo "config.js" >> .gitignore
echo "*.log" >> .gitignore
echo ".cache" >> .gitignore
```

**Soluzione 2: Reset Completo e Ricostruzione**
```bash
# Se abbiamo fatto troppi errori, resettiamo tutto
git reset HEAD .

# Ora aggiungiamo selettivamente solo i file giusti
git add cart.md calculator.js .gitignore
git status
```

### Problema 2: Staging Parziale Errato

```bash
# Modifichiamo un file con cambiamenti misti
cat > calculator.js << 'EOF'
// Funzione principale di calcolo
function calculate(a, b) {
    console.log("DEBUG: calculating", a, b); // Debug temporaneo
    return a + b;
}

// TODO: Aggiungere validazione input
function validate(input) {
    return typeof input === 'number';
}

console.log("TEMP: testing"); // Da rimuovere
EOF

# Aggiungiamo tutto per errore
git add calculator.js
```

**Soluzione: Correzione con Staging Interattivo**
```bash
# Rimuoviamo dall'area di staging
git reset HEAD calculator.js

# Ora usiamo staging interattivo per selezionare solo le parti corrette
git add -p calculator.js
# Sceglieremo 'y' per le funzioni principali
# Sceglieremo 'n' per le righe di debug e TODO
```

### Problema 3: File Rinominato Incorrettamente

```bash
# Rinominiamo un file ma Git non lo riconosce correttamente
mv cart.md shopping-cart.md
git add .
git status
# Git vede questo come "cart.md deleted" e "shopping-cart.md new file"
```

**Soluzione: Gestione Corretta dei Rename**
```bash
# Rimuoviamo tutto dallo staging
git reset HEAD .

# Diciamo a Git che è un rename
git mv cart.md shopping-cart.md
# OPPURE, se abbiamo già rinominato manualmente:
git add shopping-cart.md
git rm cart.md

git status
# Ora Git riconosce correttamente: "renamed: cart.md -> shopping-cart.md"
```

## 🔄 Workflow di Correzione Completo

### Situazione Complessa con Multipli Errori

```bash
# Creiamo una situazione complessa
echo "sensitive data" > passwords.txt
echo "more debug" >> calculator.js
echo "important fix" >> shopping-cart.md
echo "temp notes" > notes.tmp

# Aggiungiamo tutto per errore
git add .
git status
```

### Strategia di Correzione Passo-Passo

**Passo 1: Analisi della Situazione**
```bash
# Vediamo cosa abbiamo nello staging
git status --porcelain
# A  calculator.js
# A  notes.tmp
# A  passwords.txt
# A  shopping-cart.md

# Vediamo le differenze per capire cosa abbiamo aggiunto
git diff --cached
```

**Passo 2: Reset Strategico**
```bash
# Opzione A: Reset completo se tutto è sbagliato
git reset HEAD .

# Opzione B: Reset selettivo per file specifici
git reset HEAD passwords.txt notes.tmp
```

**Passo 3: Ricostruzione Corretta**
```bash
# Aggiungiamo file sicuri
git add shopping-cart.md

# Per calculator.js usiamo staging interattivo
git add -p calculator.js
# Selezioniamo solo le parti che vogliamo committare

# Aggiungiamo file temporanei al .gitignore
echo "*.tmp" >> .gitignore
echo "passwords.txt" >> .gitignore
git add .gitignore
```

## 🔍 Comandi di Verifica e Debug

### Visualizzare Differenze tra Aree

```bash
# Differenze working directory vs staging
git diff

# Differenze staging vs ultimo commit
git diff --cached

# Differenze working directory vs ultimo commit
git diff HEAD

# Stato dettagliato
git status -s
```

### Verificare il Contenuto dello Staging

```bash
# Lista file nello staging
git diff --cached --name-only

# Vedere esattamente cosa c'è nello staging
git diff --cached --stat

# Vedere il contenuto completo dei file staged
git show :filename
```

## 🧰 Comandi di Emergenza

### Reset di Sicurezza

```bash
# Salvare lavoro in stash prima di correzioni drastiche
git stash push -m "backup before staging fix"

# Reset completo mantenendo modifiche nel working directory
git reset HEAD .

# Se necessario, recuperare dal stash
git stash pop
```

### Correzione di Commit già Fatto

```bash
# Se abbiamo già fatto commit, possiamo modificarlo
git commit --amend

# O usare reset soft per tornare a staging
git reset --soft HEAD~1
# Ora possiamo correggere lo staging e rifare il commit
```

## 📚 Best Practices per Prevenire Errori

### 1. Sempre Verificare Prima di Aggiungere
```bash
# Vedere cosa stiamo per aggiungere
git status
git diff

# Aggiungere selettivamente
git add filename1 filename2
# NON: git add .
```

### 2. Usare .gitignore Proattivamente
```bash
# Creare .gitignore all'inizio del progetto
echo "*.log" > .gitignore
echo "*.tmp" >> .gitignore
echo "config.js" >> .gitignore
echo ".env" >> .gitignore
git add .gitignore
```

### 3. Staging Interattivo per File Complessi
```bash
# Per file con modifiche miste
git add -p filename

# Per revisione completa
git add -i
```

## 🎯 Esercizio Pratico

Prova questo scenario di correzione:

```bash
# 1. Crea diversi file con contenuto misto
# 2. Aggiungi tutto per errore con git add .
# 3. Rimuovi file sensibili dallo staging
# 4. Usa staging interattivo per file con modifiche miste
# 5. Verifica con git status e git diff --cached
# 6. Fai commit solo delle modifiche corrette
```

## 📋 Riepilogo

- **git reset HEAD file**: Rimuove file specifici dallo staging
- **git reset HEAD .**: Rimuove tutto dallo staging
- **git add -p**: Staging interattivo per correzioni precise
- **git status** e **git diff --cached**: Verifica sempre prima del commit
- **.gitignore**: Prevenzione è meglio della correzione

## 🔄 Link Correlati

- [01-Staging Selettivo](./01-staging-selettivo.md) - Fondamenti di staging preciso
- [02-Commit Parziali](./02-commit-parziali.md) - Tecniche avanzate di commit
- [04-Workflow Complesso](./04-workflow-complesso.md) - Gestione di progetti complessi

---

**Prossimo**: [04-Workflow-Complesso](./04-workflow-complesso.md) - Gestione di workflow di staging in progetti complessi
