# 01 - Inizializzazione Repository

## 📖 Spiegazione Concettuale

L'**inizializzazione di un repository Git** è il primo passo per iniziare a tracciare le modifiche di un progetto. Con il comando `git init`, Git crea una cartella nascosta `.git` che contiene tutti i metadati necessari per il controllo versione.

### Perché è Importante?

- **Punto di partenza**: Ogni progetto Git inizia con `git init`
- **Controllo locale**: Non serve connessione internet o server
- **Flessibilità**: Puoi inizializzare qualsiasi cartella
- **Tracciamento immediato**: Subito pronto per committare

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git init
```

### Inizializzazione con Nome Directory
```bash
git init nome-progetto
```

### Parametri Utili
```bash
# Specifica il branch principale
git init --initial-branch=main

# Repository "bare" (solo per server)
git init --bare

# Template directory personalizzata
git init --template=/path/to/template
```

## 🎯 Casi d'Uso Pratici

### 1. **Nuovo Progetto da Zero**
```bash
# Crea e inizializza nuovo progetto
mkdir mio-progetto
cd mio-progetto
git init
```

### 2. **Progetto Esistente**
```bash
# Naviga nel progetto esistente
cd progetto-esistente
git init
```

### 3. **Branch Principale Personalizzato**
```bash
# Inizializza con branch "main" invece di "master"
git init --initial-branch=main
```

## 🧐 Cosa Succede Durante `git init`

### Struttura Creata
```
.git/
├── HEAD                 # Punta al branch corrente
├── config              # Configurazione repository
├── description         # Descrizione repository
├── hooks/              # Script automatici
├── info/               # File di informazioni
├── objects/            # Database oggetti Git
└── refs/               # Riferimenti branch e tag
```

### File Principali
- **HEAD**: Contiene riferimento al branch corrente
- **config**: Configurazioni specifiche del repository
- **objects/**: Database dove Git salva tutti i dati
- **refs/**: Riferimenti a branch, tag e remote

## ⚠️ Errori Comuni

### 1. **Doppia Inizializzazione**
```bash
# ERRORE: Inizializzare repository già esistente
cd progetto-con-git
git init  # ⚠️ Sovrascrive configurazione esistente
```

### 2. **Permessi Insufficienti**
```bash
# ERRORE: Directory senza permessi di scrittura
cd /protected-directory
git init  # ❌ Permission denied
```

### 3. **Posizione Sbagliata**
```bash
# ERRORE: Inizializzare nella directory sbagliata
cd /
git init  # ⚠️ Trasforma tutto il sistema in repo Git!
```

## ✅ Best Practices

### 1. **Verifica Prima di Inizializzare**
```bash
# Controlla se esiste già un repository
ls -la | grep .git
# o
git status  # Se dà errore, non c'è repository
```

### 2. **Usa Branch Principale Moderno**
```bash
# Configura globalmente il branch predefinito
git config --global init.defaultBranch main
# Poi semplicemente
git init
```

### 3. **Documentazione Immediata**
```bash
git init
echo "# Mio Progetto" > README.md
git add README.md
git commit -m "Initial commit: Add README"
```

### 4. **Gitignore Preventivo**
```bash
git init
# Crea .gitignore prima del primo commit
echo "node_modules/" > .gitignore
echo "*.log" >> .gitignore
```

## 🧪 Quiz di Autovalutazione

1. **Cosa crea il comando `git init`?**
   - A) Un file di configurazione
   - B) Una cartella `.git` con metadati
   - C) Un backup del progetto
   - D) Una connessione a GitHub

2. **Dove dovresti eseguire `git init`?**
   - A) Nella home directory
   - B) Nella root del sistema
   - C) Nella cartella del progetto
   - D) Ovunque va bene

3. **Cosa succede se esegui `git init` in un repository esistente?**
   - A) Niente, viene ignorato
   - B) Crea un errore
   - C) Reinizializza il repository
   - D) Elimina la cronologia

4. **Quale comando mostra se una directory è un repository Git?**
   - A) `git show`
   - B) `git status`
   - C) `git log`
   - D) `git info`

**Risposte:** 1-B, 2-C, 3-C, 4-B

## 🏋️ Esercizi Pratici

### Esercizio 1: Inizializzazione Base
```bash
# 1. Crea una cartella di test
mkdir test-init
cd test-init

# 2. Inizializza repository
git init

# 3. Verifica creazione
ls -la
git status
```

### Esercizio 2: Confronto Pre/Post Inizializzazione
```bash
# Prima dell'inizializzazione
mkdir confronto
cd confronto
ls -la          # Nota cosa c'è
git status      # Nota l'errore

# Dopo l'inizializzazione
git init
ls -la          # Nota la differenza
git status      # Nota il cambiamento
```

### Esercizio 3: Repository con Contenuto
```bash
# 1. Crea progetto con file
mkdir mio-sito
cd mio-sito
echo "<h1>Il Mio Sito</h1>" > index.html

# 2. Inizializza e verifica stato
git init
git status      # Nota i file "untracked"
```

## 🔗 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 02 - Installazione e Configurazione Git](../../02-Installazione-e-Configurazione-Git/README.md)
- [➡️ 02 - Stati dei File in Git](./02-stati-file-git.md)
