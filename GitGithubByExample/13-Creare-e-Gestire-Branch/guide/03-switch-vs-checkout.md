# 03 - Git Switch vs Git Checkout

## 📖 Spiegazione Concettuale

Con **Git 2.23** (2019), sono stati introdotti due nuovi comandi: `git switch` e `git restore`. Questi comandi dividono le responsabilità di `git checkout`, rendendo le operazioni più intuitive e sicure.

### Evoluzione dei Comandi

```
Git < 2.23:
git checkout → Fa tutto (branch, file, commit)

Git ≥ 2.23:
git switch   → Solo operazioni su branch
git restore  → Solo operazioni su file
git checkout → Ancora disponibile (retrocompatibilità)
```

## 🔧 Confronto Dettagliato

### Operazioni sui Branch

| Operazione | git checkout | git switch |
|------------|--------------|------------|
| Cambiare branch | `git checkout main` | `git switch main` |
| Creare e cambiare | `git checkout -b feature` | `git switch -c feature` |
| Creare da remoto | `git checkout -b local origin/remote` | `git switch -c local origin/remote` |
| Tornare al precedente | `git checkout -` | `git switch -` |

### Sintassi a Confronto

```bash
# === CAMBIARE BRANCH ===

# Metodo tradizionale
git checkout main
git checkout feature-branch

# Metodo moderno
git switch main
git switch feature-branch

# === CREARE NUOVO BRANCH ===

# Metodo tradizionale
git checkout -b feature-login

# Metodo moderno
git switch -c feature-login

# === CREARE DA BRANCH REMOTO ===

# Metodo tradizionale
git checkout -b local-feature origin/feature

# Metodo moderno
git switch -c local-feature origin/feature
# O semplicemente (se nomi coincidono):
git switch feature  # Git capisce automaticamente
```

## 🎯 Vantaggi di Git Switch

### 1. Chiarezza di Intenti

```bash
# ❌ Confuso: cosa fa checkout qui?
git checkout HEAD~2          # Naviga a commit
git checkout main            # Cambia branch
git checkout -- file.txt    # Ripristina file

# ✅ Chiaro: switch solo per branch
git switch main              # Ovviamente cambia branch
git switch feature-branch    # Ovviamente cambia branch
```

### 2. Protezione da Errori

```bash
# ❌ Con checkout: errore facile
git checkout mian  # typo nel nome branch
# Potrebbe creare un nuovo branch invece di errore!

# ✅ Con switch: più sicuro
git switch mian   # Errore chiaro se branch non esiste
```

### 3. Autocompletamento Migliore

```bash
# Switch suggerisce solo branch
git switch <TAB>
# main
# feature-login
# develop

# Checkout suggerisce tutto (branch, file, commit)
git checkout <TAB>
# main, feature-login, file.txt, HEAD~2, etc.
```

## 🎯 Quando Usare Cosa

### Usa `git switch` per:

```bash
# ✅ Operazioni sui branch
git switch main
git switch -c feature-new
git switch -

# ✅ Tracking branch remoti
git switch -c local-branch origin/remote-branch
```

### Usa `git checkout` per:

```bash
# ✅ Navigazione a commit specifici
git checkout HEAD~2
git checkout a1b2c3d

# ✅ Ripristino file (per ora, meglio git restore)
git checkout -- file.txt
git checkout HEAD file.txt

# ✅ Operazioni avanzate legacy
git checkout -p  # Partial checkout
```

### Usa `git restore` per:

```bash
# ✅ Ripristinare file modificati
git restore file.txt

# ✅ Unstage file
git restore --staged file.txt

# ✅ Ripristinare da commit specifico
git restore --source=HEAD~2 file.txt
```

## 🔧 Migrazione da Checkout a Switch

### Script di Conversione Mentale

```bash
# === PATTERN COMUNI ===

# Vecchio → Nuovo
git checkout main              → git switch main
git checkout -b feature        → git switch -c feature
git checkout -                 → git switch -
git checkout origin/branch     → git switch origin/branch

# === OPERAZIONI MISTE ===

# Se fai questo spesso:
git checkout -b feature && git push -u origin feature

# Convertilo in:
git switch -c feature && git push -u origin feature
```

### Alias per Transizione

```bash
# Aggiungi al tuo .gitconfig per facilitare transizione
[alias]
    sw = switch
    swc = switch -c
    co = checkout  # Mantieni per operazioni speciali
```

## 🧪 Esempi Pratici Comparativi

### Scenario 1: Workflow Feature Branch

```bash
# === CON CHECKOUT ===
git checkout main
git pull origin main
git checkout -b feature-authentication
# ... sviluppo ...
git checkout main
git merge feature-authentication

# === CON SWITCH ===
git switch main
git pull origin main
git switch -c feature-authentication
# ... sviluppo ...
git switch main
git merge feature-authentication
```

### Scenario 2: Branch Tracking

```bash
# === CON CHECKOUT ===
git checkout -b local-feature origin/remote-feature

# === CON SWITCH ===
git switch -c local-feature origin/remote-feature
# O semplicemente:
git switch remote-feature  # Auto-tracking
```

### Scenario 3: Operazioni Miste

```bash
# Operazione complessa che richiede entrambi
git switch main                    # Cambia branch
git restore file.txt               # Ripristina file
git checkout HEAD~2 -- old.txt    # Prende file da commit vecchio
git switch feature-branch          # Torna al lavoro
```

## ⚠️ Errori e Migrazioni

### Errori Comuni con Switch

```bash
# ❌ Tentare di usare switch per file
$ git switch file.txt
fatal: a branch is expected, got 'file.txt'

# ✅ Usa restore invece
git restore file.txt
```

### Abitudini da Cambiare

```bash
# ❌ Vecchia abitudine
git checkout .  # Ripristina tutti i file

# ✅ Nuova abitudine
git restore .   # Più chiaro e specifico
```

## 💡 Best Practices

### 1. Adotta Gradualmente

```bash
# Settimana 1: Solo switch per branch
git switch main
git switch -c feature

# Settimana 2: Aggiungi restore
git restore file.txt

# Mantieni checkout per casi speciali
git checkout HEAD~2
```

### 2. Configura Editor/IDE

```bash
# VSCode: configura comandi preferiti
# Aggiungi snippet per:
git switch -c $BRANCH_NAME
git restore $FILE_NAME
```

### 3. Team Guidelines

```bash
# Stabilisci regole del team:
# - switch per branch (obbligatorio nei nuovi progetti)
# - restore per file (dove supportato)  
# - checkout per navigazione commit
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale comando dovresti usare per creare un nuovo branch in Git moderno?
- A) `git checkout -b branch-name`
- B) `git switch -c branch-name`
- C) `git branch branch-name && git switch branch-name`
- D) Tutte le opzioni funzionano

### Domanda 2
Qual è il comando più appropriato per ripristinare un file modificato?
- A) `git checkout -- file.txt`
- B) `git switch file.txt`
- C) `git restore file.txt`
- D) `git reset file.txt`

### Domanda 3
Da quale versione di Git sono disponibili `switch` e `restore`?
- A) Git 2.20
- B) Git 2.23
- C) Git 2.25
- D) Git 3.0

### Risposte
1. D - Tutte funzionano, ma `switch -c` è il metodo moderno preferito
2. C - `git restore` è il comando specifico per ripristinare file
3. B - Introdotti in Git 2.23 (agosto 2019)

## 📚 Approfondimenti

### Controllo Versione Git

```bash
# Verifica se hai Git 2.23+
git --version

# Se hai versione più vecchia, aggiorna per usare switch
# Su Ubuntu/Debian:
sudo add-apt-repository ppa:git-core/ppa
sudo apt update
sudo apt install git
```

### Configurazione Avanzata

```bash
# Abilita autocompletamento intelligente per switch
git config --global completion.commands switch

# Abilita consigli per comandi moderni
git config --global advice.detachedHead true
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Guida Precedente](./02-gestire-branch.md)
- [➡️ Prossima Guida](./04-branch-workflow.md)

### Risorse Esterne
- [Git 2.23 Release Notes](https://github.com/git/git/blob/master/Documentation/RelNotes/2.23.0.txt)
- [Git Switch Documentation](https://git-scm.com/docs/git-switch)
- [Git Restore Documentation](https://git-scm.com/docs/git-restore)

---

**Prossimo passo**: [Branch Workflow](./04-branch-workflow.md) - Impara i pattern di workflow con i branch
