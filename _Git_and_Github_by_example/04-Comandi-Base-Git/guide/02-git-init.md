# 02 - Git Init: Inizializzare un Repository

## 📖 Spiegazione Concettuale

Il comando `git init` è il primo passo per iniziare a utilizzare Git in un progetto. Questo comando trasforma una cartella ordinaria in un **repository Git**, creando tutte le strutture necessarie per il controllo di versione.

### Cos'è un Repository Git?

Un repository Git è una cartella che contiene:
- I tuoi file di progetto
- Una cartella nascosta `.git/` con tutta la storia delle modifiche
- Metadati per tracciare chi, quando e cosa è stato modificato

## 🔧 Sintassi e Parametri

### Sintassi Base
```bash
git init [directory]
```

### Parametri Principali

| Parametro | Descrizione | Esempio |
|-----------|-------------|---------|
| `[directory]` | Cartella da inizializzare (opzionale) | `git init mio-progetto` |
| `--bare` | Crea un repository "nudo" (per server) | `git init --bare` |
| `--template=<path>` | Usa template personalizzato | `git init --template=~/template` |

### Esempi Pratici

**1. Inizializzare repository nella cartella corrente:**
```bash
cd mio-progetto
git init
```

**2. Creare nuova cartella e inizializzare:**
```bash
git init nuovo-progetto
cd nuovo-progetto
```

**3. Verificare l'inizializzazione:**
```bash
ls -la  # Mostra la cartella .git nascosta
```

## 💡 Casi d'Uso Pratici

### Scenario 1: Nuovo Progetto da Zero
```bash
# Creo una nuova cartella per il progetto
mkdir sito-web-personale
cd sito-web-personale

# Inizializzo Git
git init

# Creo il primo file
echo "# Il Mio Sito Web" > README.md

# Verifico lo status
git status
```

### Scenario 2: Progetto Esistente
```bash
# Ho già una cartella con dei file
cd progetto-esistente
ls
# index.html  style.css  script.js

# Aggiungo il controllo versione
git init

# Ora posso tracciare i file esistenti
git add .
git commit -m "Primo commit: progetto esistente"
```

### Scenario 3: Repository Condiviso (Server)
```bash
# Sul server (repository bare)
git init --bare progetto-condiviso.git

# I collaboratori possono clonare
git clone user@server:progetto-condiviso.git
```

## ⚠️ Errori Comuni

### 1. **Doppia Inizializzazione**
```bash
# ERRORE: Git è già inizializzato
$ git init
Reinitialized existing Git repository in /path/to/repo/.git/
```
**Soluzione**: Verifica sempre con `git status` prima di `git init`

### 2. **Permessi Insufficienti**
```bash
# ERRORE: Non posso scrivere nella cartella
$ git init
fatal: cannot mkdir .git
```
**Soluzione**: Verifica i permessi della cartella

### 3. **Confondere Repository Bare e Normali**
```bash
# ERRORE: Cercare di lavorare in un repo bare
$ git init --bare
$ echo "test" > file.txt
$ git add file.txt
fatal: this operation must be run in a work tree
```

## 🎯 Best Practices

### 1. **Organizzazione Progetti**
```bash
# Struttura consigliata
progetti/
├── sito-web/          ← git init qui
├── app-mobile/        ← git init qui  
└── documentazione/    ← git init qui
```

### 2. **Naming Convention**
```bash
# Buoni nomi per repository
git init e-commerce-website
git init user-management-api
git init data-analysis-scripts

# Evita spazi e caratteri speciali
git init "progetto con spazi"  # ❌
git init progetto-con-trattini  # ✅
```

### 3. **File .gitignore da Subito**
```bash
git init
echo "node_modules/" > .gitignore
echo "*.log" >> .gitignore
echo ".env" >> .gitignore
```

## 🧪 Quiz di Autovalutazione

**1. Cosa succede quando eseguo `git init` in una cartella?**
- a) Elimina tutti i file esistenti
- b) Crea la cartella `.git` per il controllo versione
- c) Carica automaticamente i file su GitHub
- d) Crea un backup dei file

**2. Qual è la differenza tra `git init` e `git init --bare`?**
- a) `--bare` crea repository più piccoli
- b) `--bare` è per repository server senza working directory
- c) `--bare` è più veloce
- d) Non c'è differenza

**3. Dove vengono salvate le informazioni di Git dopo `git init`?**
- a) In una cartella `git/`
- b) In una cartella `.git/`
- c) In un file `git.config`
- d) Nel cloud automaticamente

<details>
<summary>🔍 Risposte</summary>

1. **b)** Crea la cartella `.git` per il controllo versione
2. **b)** `--bare` è per repository server senza working directory  
3. **b)** In una cartella `.git/`

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Primo Repository
1. Crea una cartella chiamata `primo-repo`
2. Inizializza Git nella cartella
3. Verifica che sia stato creato correttamente
4. Crea un file `hello.txt` con il testo "Hello Git!"

### Esercizio 2: Repository da Progetto Esistente
1. Crea una cartella `progetto-web` con questi file:
   - `index.html` con contenuto HTML base
   - `style.css` con qualche regola CSS
   - `script.js` con un alert JavaScript
2. Inizializza Git nella cartella
3. Controlla lo status dei file

### Esercizio 3: Esplorazione Struttura
1. Dopo aver inizializzato un repository, esplora il contenuto di `.git/`
2. Identifica le cartelle principali: `objects/`, `refs/`, `hooks/`
3. Leggi il file `.git/config`

## 🔗 Collegamenti Rapidi

- **Comando successivo**: [03 - Git Add](03-git-add.md)
- **Comando precedente**: [01 - Git Status](01-git-status.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 03-Primo-Repository-Git](../../03-Primo-Repository-Git/README.md)
- [➡️ 05-Area-di-Staging](../../05-Area-di-Staging/README.md)
