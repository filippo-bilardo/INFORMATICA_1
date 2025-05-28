# Git Checkout vs Switch: Navigazione Moderna

## 📖 Obiettivi
- Comprendere l'evoluzione dei comandi Git
- Imparare la differenza tra `checkout` e `switch`
- Scegliere il comando giusto per ogni situazione
- Adottare best practices moderne

## 📚 Prerequisiti
- Conoscenza di base di Git
- Familiarità con concetti di branch e commit
- Comprensione di HEAD

## ⏱️ Durata Stimata
15-20 minuti

---

## 🔄 L'Evoluzione di Git

### Il Problema di `git checkout`

`git checkout` è storicamente un comando "Swiss Army knife" che fa troppe cose:

```bash
# Cambia branch
git checkout main

# Naviga a commit
git checkout abc123

# Crea e cambia branch
git checkout -b new-feature

# Ripristina file
git checkout -- file.txt

# Cambia a tag
git checkout v1.0
```

**Problema**: Un solo comando per operazioni molto diverse!

### La Soluzione Moderna

Git 2.23 (2019) ha introdotto comandi specializzati:

- **`git switch`**: Per cambiare branch e navigare
- **`git restore`**: Per ripristinare file
- **`git checkout`**: Mantiene compatibilità, ma uso sconsigliato

---

## 🆚 Confronto Dettagliato

### Cambio Branch

#### Metodo Classico (checkout)

```bash
# Cambia a branch esistente
git checkout main

# Crea e cambia a nuovo branch
git checkout -b feature/new-login

# Torna al branch precedente
git checkout -
```

#### Metodo Moderno (switch)

```bash
# Cambia a branch esistente
git switch main

# Crea e cambia a nuovo branch
git switch -c feature/new-login

# Torna al branch precedente
git switch -
```

### Navigazione Commit

#### Metodo Classico (checkout)

```bash
# Vai a commit specifico
git checkout abc123

# Vai a commit relativo
git checkout HEAD~2

# Vai a tag
git checkout v1.0.0
```

#### Metodo Moderno (switch)

```bash
# Vai a commit specifico
git switch --detach abc123

# Vai a commit relativo
git switch --detach HEAD~2

# Vai a tag
git switch --detach v1.0.0
```

### Ripristino File

#### Metodo Classico (checkout)

```bash
# Ripristina file dal ultimo commit
git checkout HEAD -- file.txt

# Ripristina da commit specifico
git checkout abc123 -- file.txt
```

#### Metodo Moderno (restore)

```bash
# Ripristina file dal ultimo commit
git restore file.txt

# Ripristina da commit specifico
git restore --source=abc123 file.txt
```

---

## 🎯 Quando Usare Cosa

### Usa `git switch` per:

✅ **Cambio branch normale**
```bash
git switch main
git switch develop
git switch feature/authentication
```

✅ **Creazione nuovi branch**
```bash
git switch -c feature/new-dashboard
git switch -c hotfix/critical-bug
```

✅ **Navigazione esplicita a commit**
```bash
git switch --detach abc123
git switch --detach HEAD~5
```

### Usa `git restore` per:

✅ **Ripristino file modificati**
```bash
git restore file.txt
git restore src/components/
```

✅ **Ripristino da commit specifici**
```bash
git restore --source=HEAD~2 config.js
git restore --staged file.txt  # unstage
```

### Usa `git checkout` quando:

⚠️ **Script legacy** (per compatibilità)
⚠️ **Versioni Git < 2.23**
❓ **Comando complesso** che non ha equivalente diretto

---

## 🆕 Vantaggi di Switch

### 1. Chiarezza Semantica

```bash
# Chiaro: sto cambiando branch
git switch main

# Meno chiaro: cosa sto facendo?
git checkout main
```

### 2. Protezione da Errori

```bash
# Switch richiede --detach per commit
git switch abc123           # ❌ ERRORE
git switch --detach abc123  # ✅ CHIARO

# Checkout lo fa silenziosamente
git checkout abc123         # ⚠️ Detached HEAD senza avviso
```

### 3. Operazioni Più Sicure

```bash
# Switch controlla modifiche non salvate
git switch main
# warning: your local changes would be overwritten
# hint: commit your changes or stash them

# Checkout spesso sovrascrive silenziosamente
```

### 4. Messaggi Migliori

```bash
# Switch dà feedback chiaro
$ git switch feature/auth
Switched to branch 'feature/auth'

# Switch con detach è esplicito
$ git switch --detach HEAD~2
HEAD is now at abc123 Previous commit
```

---

## 🔧 Esempi Pratici Avanzati

### Scenario 1: Sviluppo Feature

```bash
# Moderno workflow con switch
git switch main
git pull origin main
git switch -c feature/user-dashboard

# ... lavoro ...
git add .
git commit -m "Add user dashboard"

# Test su main
git switch main
git switch --detach HEAD~1  # test versione precedente
git switch main              # torna a main

# Torna alla feature
git switch feature/user-dashboard
```

### Scenario 2: Bug Investigation

```bash
# Investigazione bug con switch detach
git switch --detach HEAD~10
# ... test ...

git switch --detach v1.2.0
# ... test versione stabile ...

# Crea branch se hai trovato qualcosa
git switch -c investigation/bug-analysis

# Oppure torna a lavoro normale
git switch main
```

### Scenario 3: Emergency Hotfix

```bash
# Hotfix urgente
git switch main
git switch -c hotfix/critical-security

# ... fix ...
git add .
git commit -m "Fix critical security issue"

# Deploy
git switch main
git merge hotfix/critical-security
git tag v1.2.1
```

---

## 📋 Cheat Sheet Comandi

### Switch vs Checkout - Quick Reference

| Operazione | Checkout | Switch | Note |
|------------|----------|--------|------|
| Cambia branch | `git checkout main` | `git switch main` | Switch più chiaro |
| Crea branch | `git checkout -b feature` | `git switch -c feature` | `-c` invece di `-b` |
| Torna indietro | `git checkout -` | `git switch -` | Identico |
| Vai a commit | `git checkout abc123` | `git switch --detach abc123` | Switch richiede `--detach` |
| Vai a tag | `git checkout v1.0` | `git switch --detach v1.0` | Switch più esplicito |

### Restore vs Checkout File

| Operazione | Checkout | Restore | Note |
|------------|----------|---------|------|
| Ripristina file | `git checkout HEAD file.txt` | `git restore file.txt` | Restore più semplice |
| Da commit specifico | `git checkout abc123 file.txt` | `git restore --source=abc123 file.txt` | Restore più esplicito |
| Unstage file | `git checkout HEAD --staged file.txt` | `git restore --staged file.txt` | Restore più chiaro |

---

## ⚠️ Considerazioni di Migrazione

### Compatibilità

```bash
# Verifica versione Git
git --version

# Se < 2.23, usa checkout
if [ $(git --version | cut -d' ' -f3 | cut -d'.' -f1-2 | tr -d '.') -lt 223 ]; then
    echo "Usa git checkout"
else
    echo "Puoi usare git switch"
fi
```

### Script e Automation

```bash
# In script, considera compatibilità
# Invece di:
git switch main

# Usa:
git checkout main  # Funziona ovunque

# Oppure controlla e adatta:
if git switch --help >/dev/null 2>&1; then
    git switch main
else
    git checkout main
fi
```

### Team e Documentazione

1. **Stabilisci convenzioni** team su quale comando usare
2. **Aggiorna documentazione** per riflettere comandi moderni
3. **Forma il team** sui nuovi comandi
4. **Considera periodo di transizione** misto

---

## 🎯 Best Practices Moderne

### Workflow Consigliato

```bash
# 1. Navigazione branch (switch)
git switch main
git switch develop
git switch -c feature/new-thing

# 2. Navigazione commit (switch --detach)
git switch --detach HEAD~5
git switch --detach v1.0.0

# 3. Ripristino file (restore)
git restore file.txt
git restore --staged file.txt

# 4. Operazioni complesse (checkout solo se necessario)
# git checkout rimane per casi edge
```

### Configurazione Alias

```bash
# Alias per transizione graduale
git config --global alias.sw switch
git config --global alias.rs restore

# Alias per operazioni comuni
git config --global alias.main 'switch main'
git config --global alias.last 'switch -'
git config --global alias.new 'switch -c'
```

---

## 🧪 Esercizio Pratico

### Setup Repository

```bash
mkdir switch-vs-checkout-test
cd switch-vs-checkout-test
git init

# Crea cronologia
echo "Initial" > file.txt
git add file.txt
git commit -m "Initial commit"

echo "Version 2" >> file.txt
git add file.txt
git commit -m "Add version 2"

echo "Version 3" >> file.txt
git add file.txt
git commit -m "Add version 3"

git tag v1.0 HEAD~2
git tag v2.0 HEAD~1
git tag v3.0 HEAD
```

### Test Comando Switch

```bash
# 1. Test switch normale
git switch --detach HEAD~1
git log --oneline -3

# 2. Test switch con protezione
echo "Modified" >> file.txt
git switch main  # Dovrebbe avvisare delle modifiche

# 3. Stash e switch
git stash
git switch main
git stash pop

# 4. Crea branch da posizione specifica
git switch --detach v1.0
git switch -c from-v1
git log --oneline -1
```

### Confronto con Checkout

```bash
# Stesso test con checkout
git checkout HEAD~1
git log --oneline -3

# Checkout spesso meno verboso
echo "Modified" >> file.txt
git checkout main  # Comportamento diverso

git checkout v1.0   # Meno esplicito di switch --detach
```

---

## 📊 Vantaggi Comparativi

### Git Switch

| ✅ Pro | ❌ Contro |
|--------|-----------|
| Semantica chiara | Comando nuovo (Git 2.23+) |
| Protezioni integrate | Richiede apprendimento |
| Messaggi migliori | Non in script legacy |
| Operazioni sicure | Team deve allinearsi |

### Git Checkout

| ✅ Pro | ❌ Contro |
|--------|-----------|
| Universalmente disponibile | Semantica confusa |
| Script esistenti funzionano | Meno protezioni |
| Comando singolo per tutto | Facile fare errori |
| Documentazione estesa | Meno feedback |

---

## 🎯 Quiz di Autovalutazione

### Domanda 1
**Quale comando è più sicuro per navigare a un commit precedente?**

A) `git checkout abc123`  
B) `git switch abc123`  
C) `git switch --detach abc123`  
D) `git reset abc123`  

<details>
<summary>Risposta</summary>
<strong>C) `git switch --detach abc123`</strong>

`git switch` richiede esplicitamente `--detach` per navigare a commit, rendendo l'operazione più chiara e intenzionale.
</details>

### Domanda 2
**Da quale versione di Git è disponibile `git switch`?**

A) Git 2.20  
B) Git 2.23  
C) Git 2.25  
D) Git 3.0  

<details>
<summary>Risposta</summary>
<strong>B) Git 2.23</strong>

`git switch` e `git restore` sono stati introdotti in Git 2.23 (agosto 2019) per separare le funzionalità di `git checkout`.
</details>

### Domanda 3
**Come si crea un nuovo branch con `git switch`?**

A) `git switch -b new-branch`  
B) `git switch -c new-branch`  
C) `git switch --create new-branch`  
D) `git switch new new-branch`  

<details>
<summary>Risposta</summary>
<strong>B) `git switch -c new-branch`</strong>

L'opzione `-c` (create) è l'equivalente di `-b` in `git checkout` per creare e cambiare a un nuovo branch.
</details>

---

## 📝 Riassunto

### Conclusioni Chiave

1. **`git switch` è il futuro** per navigazione branch e commit
2. **`git restore` sostituisce `git checkout`** per file
3. **Comandi separati = operazioni più chiare**
4. **Maggiore sicurezza** con controlli automatici
5. **Transizione graduale** raccomandabile

### Raccomandazioni

- **Usa `git switch`** per nuovi progetti
- **Mantieni `git checkout`** per compatibilità script
- **Forma il team** sui nuovi comandi
- **Aggiorna alias** e documentazione

---

## 🔗 Navigazione del Corso

- [📑 Indice](../../README.md)
- [⬅️ Concetti di Navigazione](./01-concetti-navigazione.md)
- [➡️ Detached HEAD State](./03-detached-head.md)

---

*🚀 Prossimo: Comprenderai cos'è e come gestire il detached HEAD state in modo sicuro e produttivo.*
