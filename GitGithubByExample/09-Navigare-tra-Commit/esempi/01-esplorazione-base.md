# 01 - Esplorazione Base: Viaggio nella Storia del Progetto

## 📖 Scenario

Sei appena entrato nel team di sviluppo di **EcoShop**, un'applicazione e-commerce eco-sostenibile. Il repository ha una ricca cronologia di 6 mesi e devi familiarizzare con l'evoluzione del progetto. In questo esempio imparerai a navigare in modo sicuro nella cronologia per comprendere come si è sviluppato il sistema.

## 🎯 Obiettivi dell'Esempio

- ✅ Navigazione sicura tra commit storici
- ✅ Esplorazione dell'evoluzione del codice
- ✅ Uso pratico di detached HEAD
- ✅ Ritorno sicuro al presente
- ✅ Comprensione dell'architettura storica

## 📋 Prerequisiti

- Repository Git con cronologia significativa
- Conoscenza base di git log
- Comprensione di HEAD e commit

## ⏱️ Durata Stimata

**30-40 minuti**

---

## 🚀 Setup del Scenario

### 1. Preparazione dell'Ambiente

```bash
# Clona il repository di esempio (o usa il tuo)
cd ~/progetti
mkdir ecoshop-exploration
cd ecoshop-exploration
git init

# Crea una cronologia di esempio realistica
echo "# EcoShop - E-commerce Sostenibile" > README.md
echo "node_modules/" > .gitignore
git add .
git commit -m "Initial commit: Setup base del progetto"

# Simula sviluppo iniziale
mkdir src tests
echo '{"name": "ecoshop", "version": "1.0.0"}' > package.json
echo "console.log('EcoShop avviato');" > src/app.js
git add .
git commit -m "feat: Struttura base dell'applicazione"

# Aggiunge sistema utenti
echo "class User { constructor(name) { this.name = name; } }" > src/user.js
echo "const express = require('express');" >> src/app.js
git add .
git commit -m "feat: Sistema di gestione utenti"

# Bug fix critico
echo "// Validazione sicurezza aggiunta" >> src/user.js
git add .
git commit -m "fix: Vulnerabilità SQL injection in login"

# Feature importante
mkdir src/payment
echo "class PaymentProcessor { process() { return 'OK'; } }" > src/payment/processor.js
git add .
git commit -m "feat: Integrazione sistema di pagamento"

# Refactoring
echo "// Codice ottimizzato per performance" >> src/app.js
git add .
git commit -m "refactor: Ottimizzazione performance sistema"

# Release tag
git tag v1.0.0

# Sviluppo continuo
mkdir src/cart
echo "class ShoppingCart { addItem(item) { /* logic */ } }" > src/cart/cart.js
git add .
git commit -m "feat: Carrello della spesa avanzato"

echo "Simulazione repository EcoShop creata!"
```

### 2. Verifica Iniziale

```bash
# Controlla la cronologia
git log --oneline --graph

# Output atteso:
# * a1b2c3d feat: Carrello della spesa avanzato
# * e4f5g6h refactor: Ottimizzazione performance sistema
# * i7j8k9l feat: Integrazione sistema di pagamento
# * m1n2o3p fix: Vulnerabilità SQL injection in login
# * q4r5s6t feat: Sistema di gestione utenti
# * u7v8w9x feat: Struttura base dell'applicazione
# * y1z2a3b Initial commit: Setup base del progetto

# Vedi i tag
git tag
# v1.0.0
```

---

## 🗺️ Navigazione Guidata

### Fase 1: Preparazione Sicura

```bash
# 1. Verifica stato pulito
git status

# 2. Salva posizione attuale
CURRENT_BRANCH=$(git branch --show-current)
echo "Branch attuale: $CURRENT_BRANCH"

# 3. Crea checkpoint di sicurezza
git tag checkpoint-exploration-$(date +%Y%m%d-%H%M%S)

# 4. (Opzionale) Stash se ci sono modifiche
git stash push -m "Prima di esplorazione cronologia"
```

### Fase 2: Esplorazione dell'Inizio

```bash
# Torna ai primi commit
git log --oneline | tail -3

# Naviga al primo commit
FIRST_COMMIT=$(git log --oneline | tail -1 | cut -d' ' -f1)
echo "Navigando al primo commit: $FIRST_COMMIT"
git checkout $FIRST_COMMIT

# Esplora stato iniziale
echo "=== STATO INIZIALE DEL PROGETTO ==="
echo "File presenti:"
ls -la

echo "Contenuto README:"
cat README.md

echo "Struttura del progetto:"
find . -name ".git" -prune -o -type f -print | head -10
```

### Fase 3: Evoluzione della Struttura

```bash
# Naviga al commit della struttura base
git log --oneline --all | grep "Struttura base"
STRUCTURE_COMMIT=$(git log --oneline --all | grep "Struttura base" | cut -d' ' -f1)
git checkout $STRUCTURE_COMMIT

echo "=== DOPO SETUP STRUTTURA ==="
echo "Nuovi file aggiunti:"
ls -la src/
cat package.json
cat src/app.js

echo "Confronto con versione precedente:"
git show --name-only HEAD
```

### Fase 4: Milestone Importante (Sistema Utenti)

```bash
# Vai al commit del sistema utenti
USER_COMMIT=$(git log --oneline --all | grep "gestione utenti" | cut -d' ' -f1)
git checkout $USER_COMMIT

echo "=== INTRODUZIONE SISTEMA UTENTI ==="
echo "File del sistema utenti:"
cat src/user.js

echo "Modifiche nell'app principale:"
cat src/app.js

echo "Diff con commit precedente:"
git show --stat HEAD
git show HEAD -- src/user.js
```

### Fase 5: Momento Critico (Security Fix)

```bash
# Vai al fix di sicurezza
SECURITY_COMMIT=$(git log --oneline --all | grep "SQL injection" | cut -d' ' -f1)
git checkout $SECURITY_COMMIT

echo "=== FIX SICUREZZA CRITICO ==="
echo "Modifica di sicurezza:"
git show $SECURITY_COMMIT

echo "File modificato:"
cat src/user.js

echo "Dettagli del problema risolto:"
git log --oneline -p $SECURITY_COMMIT | head -20
```

### Fase 6: Release Version (v1.0.0)

```bash
# Vai al tag v1.0.0
git checkout v1.0.0

echo "=== RELEASE v1.0.0 ==="
echo "Stato alla release:"
git log --oneline | head -5

echo "File nella release:"
find . -name ".git" -prune -o -type f -print

echo "Funzionalità incluse:"
git log --oneline v1.0.0 | grep -E "(feat|fix):"

echo "Statistiche release:"
git show --stat v1.0.0
```

---

## 🔍 Analisi Comparativa

### Confronto Tra Versioni

```bash
# Torna al presente
git switch $CURRENT_BRANCH

echo "=== ANALISI EVOLUZIONE PROGETTO ==="

# Confronta primo commit vs ora
echo "Crescita del progetto:"
git diff --stat $FIRST_COMMIT..HEAD

# File aggiunti nel tempo
echo "File aggiunti dalla v1.0.0:"
git diff --name-only v1.0.0..HEAD

# Linee di codice
echo "Linee di codice totali ora:"
find . -name "*.js" -exec wc -l {} + | tail -1

# Storia dei commit per categoria
echo "Commit per tipo:"
git log --oneline | grep -E "feat:" | wc -l | xargs echo "Features:"
git log --oneline | grep -E "fix:" | wc -l | xargs echo "Fixes:"
git log --oneline | grep -E "refactor:" | wc -l | xargs echo "Refactoring:"
```

### Timeline del Progetto

```bash
# Crea timeline dettagliata
echo "=== TIMELINE PROGETTO ECOSHOP ==="
git log --pretty=format:"📅 %ad | 👤 %an | 📝 %s" --date=short

# Visualizzazione grafica
echo -e "\n=== GRAFICO CRONOLOGIA ==="
git log --graph --pretty=format:"%C(yellow)%h%C(reset) %C(green)%ad%C(reset) | %s" --date=short
```

---

## 🧪 Esperimenti Sicuri

### Test 1: Modifica in Detached HEAD (Scenario Pericoloso)

```bash
# Vai a un commit storico
git checkout $USER_COMMIT

echo "=== ESPERIMENTO: MODIFICA IN DETACHED HEAD ==="
echo "Stato attuale:"
git status

# Simula modifica accidentale
echo "// Modifica di test" >> src/user.js

echo "Dopo modifica:"
git status

echo "⚠️  ATTENZIONE: Siamo in detached HEAD con modifiche!"
echo "Come risolvere..."
```

### Soluzione Sicura

```bash
# Opzione 1: Scarta modifiche
git checkout -- src/user.js
git status

# Opzione 2: Se volessimo salvare (DEMO)
echo "// Modifica importante" >> src/user.js
git add .
git commit -m "fix: Modifica sperimentale"

# Salva il commit in un branch
NEW_COMMIT=$(git rev-parse HEAD)
git switch $CURRENT_BRANCH
git branch experiment-branch $NEW_COMMIT

echo "Commit salvato nel branch 'experiment-branch'"
git log --oneline experiment-branch | head -3
```

### Test 2: Navigazione Rapida

```bash
echo "=== TEST NAVIGAZIONE RAPIDA ==="

# Ultimo commit
git log --oneline -1

# 3 commit fa
git checkout HEAD~3
git log --oneline -1

# 2 commit fa dal primo
git checkout HEAD~2
git log --oneline -1

# Torna al futuro
git switch $CURRENT_BRANCH
git log --oneline -1
```

---

## 📊 Report dell'Esplorazione

### Genera Report Automatico

```bash
#!/bin/bash
# exploration-report.sh

echo "# 📊 Report Esplorazione Repository EcoShop"
echo "**Data**: $(date)"
echo "**Esploratore**: $(git config user.name)"
echo ""

echo "## 📈 Statistiche Generali"
echo "- **Commit totali**: $(git rev-list --count HEAD)"
echo "- **Branch**: $(git branch -a | wc -l)"
echo "- **Tag**: $(git tag | wc -l)"
echo "- **Contribuitori**: $(git log --format='%an' | sort -u | wc -l)"
echo ""

echo "## 🏷️ Milestone Principali"
git tag | while read tag; do
    echo "- **$tag**: $(git log -1 --format='%s (%ad)' --date=short $tag)"
done
echo ""

echo "## 📝 Commit Recenti"
git log --oneline -5
echo ""

echo "## 📂 Struttura Attuale"
find . -name ".git" -prune -o -type f -print | head -10
echo ""

echo "## 🎯 Prossimi Passi Suggeriti"
echo "- [ ] Analizzare branch feature attivi"
echo "- [ ] Controllare issue aperti"
echo "- [ ] Verificare test coverage"
echo "- [ ] Documentare architettura"
```

---

## 🧹 Cleanup e Ritorno Sicuro

### Fase di Pulizia

```bash
echo "=== CLEANUP ESPLORAZIONE ==="

# Verifica dove siamo
git log --oneline -1

# Torna al branch principale
git switch $CURRENT_BRANCH

# Recupera eventuali stash
if [ "$(git stash list | wc -l)" -gt 0 ]; then
    echo "Stash disponibili:"
    git stash list
    # git stash pop  # Se necessario
fi

# Rimuovi branch temporanei
git branch -D experiment-branch

# Rimuovi tag di checkpoint
git tag -d $(git tag | grep checkpoint-exploration)

# Verifica stato finale pulito
git status
```

### Verifica Finale

```bash
echo "=== VERIFICA FINALE ==="
echo "Branch attuale: $(git branch --show-current)"
echo "Ultimo commit: $(git log --oneline -1)"
echo "Stato repository: $(git status --porcelain | wc -l) file modificati"
echo "Stash disponibili: $(git stash list | wc -l)"

echo ""
echo "✅ Esplorazione completata con successo!"
echo "📚 Hai imparato a navigare sicuramente nella cronologia Git"
```

---

## 💡 Lezioni Apprese

### Best Practices Confermate

1. **Sempre checkpoint prima**: Tag o stash preventivi
2. **Detached HEAD è sicuro**: Per esplorazione read-only
3. **Salva modifiche importanti**: Con branch dedicati
4. **Usa comandi di orientamento**: git status, git log
5. **Torna sempre al presente**: git switch per sicurezza

### Pattern Utili Scoperti

```bash
# Pattern di esplorazione sicura
safe_explore() {
    local target=$1
    git stash push -m "Exploration backup"
    git checkout "$target"
    echo "Esplora pure. Per tornare: git switch - && git stash pop"
}

# Pattern di confronto temporale
compare_evolution() {
    local old=$1
    local new=${2:-HEAD}
    git diff --stat $old..$new
    git log --oneline $old..$new
}

# Pattern di timeline
project_timeline() {
    git log --graph --pretty=format:"%C(yellow)%h%C(reset) %C(green)%ad%C(reset) | %s" --date=short --all
}
```

---

## 🎯 Riepilogo e Prossimi Passi

### Cosa Hai Imparato

- ✅ Navigazione sicura nella cronologia Git
- ✅ Esplorazione di stati storici del codice
- ✅ Gestione sicura di detached HEAD
- ✅ Tecniche di confronto tra versioni
- ✅ Recovery da situazioni problematiche

### Competenze Acquisite

- **Archeologo del Codice**: Sapere esplorare la storia
- **Navigator Sicuro**: Muoversi senza perdere lavoro
- **Analista dell'Evoluzione**: Capire come cresce un progetto
- **Problem Solver**: Recuperare da situazioni complesse

### Prossimi Passi

1. **Pratica con repository reali** dei tuoi progetti
2. **Sperimenta scenari complessi** (merge, conflitti)
3. **Automatizza workflow** di esplorazione
4. **Integra con strumenti** di analisi del codice

---

## 🔗 Riferimenti Rapidi

### Comandi Essenziali Usati
```bash
git checkout <commit>     # Naviga a commit specifico
git switch -              # Torna al branch precedente  
git log --oneline         # Cronologia condensata
git show <commit>         # Dettagli commit
git tag <name>            # Crea checkpoint
git stash push -m "msg"   # Salva lavoro temporaneo
```

### Risorse Aggiuntive
- [Git Checkout Manual](https://git-scm.com/docs/git-checkout)
- [Detached HEAD Guide](https://git-scm.com/docs/git-checkout#_detached_head)

---

## 🔄 Navigazione

- [🏠 Modulo 09](../README.md)
- [📚 Guide](../guide/01-concetti-navigazione.md)
- [➡️ 02 - Debug Temporale](./02-debug-temporale.md)
- [📑 Indice Corso](../../README.md)

---

**Prossimo esempio**: [02 - Debug Temporale](./02-debug-temporale.md) - Utilizzo della navigazione per debugging e risoluzione problemi
