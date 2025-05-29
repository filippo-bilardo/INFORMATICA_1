# Esempio 2: Repository per Documentazione

## 📋 Scenario
Creiamo un repository Git per gestire la documentazione di un progetto software, dimostrando come Git può essere utilizzato per tracciare non solo codice ma anche documenti.

## 🎯 Obiettivi di Apprendimento
- Utilizzare Git per tracciare documenti Markdown
- Gestire strutture di directory organizzate
- Comprendere l'importanza del version control per la documentazione

## 🛠️ Implementazione Pratica

### Passo 1: Inizializzazione del Repository

```bash
# Creiamo la directory del progetto
mkdir docs-progetto-alpha
cd docs-progetto-alpha

# Inizializziamo il repository Git
git init

# Verifichiamo che tutto sia in ordine
git status
```

**Output atteso:**
```
On branch main

No commits yet

nothing to commit (create/copy files and run "git add" to track)
```

### Passo 2: Struttura della Documentazione

```bash
# Creiamo la struttura delle directory
mkdir -p {user-guide,api-docs,tutorials,assets/images}

# Creiamo i file di documentazione
touch README.md
touch user-guide/getting-started.md
touch user-guide/installation.md
touch api-docs/authentication.md
touch api-docs/endpoints.md
touch tutorials/first-steps.md
```

### Passo 3: Contenuto dei Documenti

Aggiungiamo contenuto al README.md:

```markdown
# Progetto Alpha - Documentazione

## 📖 Panoramica
Documentazione completa per il Progetto Alpha, una piattaforma innovativa per la gestione dei contenuti.

## 📚 Struttura
- `user-guide/` - Guide per gli utenti finali
- `api-docs/` - Documentazione API per sviluppatori
- `tutorials/` - Tutorial passo-passo
- `assets/` - Risorse multimediali

## 🚀 Quick Start
Per iniziare, consulta la [Guida di Installazione](user-guide/installation.md).

## 📧 Contatti
- Team Documentation: docs@progetto-alpha.com
- Support: support@progetto-alpha.com
```

### Passo 4: Tracciamento dei File

```bash
# Aggiungiamo tutti i file al tracking
git add .

# Verifichiamo lo stato
git status
```

**Output atteso:**
```
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   README.md
        new file:   api-docs/authentication.md
        new file:   api-docs/endpoints.md
        new file:   tutorials/first-steps.md
        new file:   user-guide/getting-started.md
        new file:   user-guide/installation.md
```

### Passo 5: Primo Commit

```bash
# Creiamo il primo commit
git commit -m "📚 Initial documentation structure

- Add README with project overview
- Create user-guide directory structure
- Set up API documentation framework
- Initialize tutorial templates"
```

### Passo 6: Evoluzione della Documentazione

Aggiungiamo contenuto a `user-guide/getting-started.md`:

```markdown
# Getting Started

## 🎯 Benvenuto in Progetto Alpha!

### Prerequisiti
- Account utente attivo
- Browser web moderno
- Connessione internet

### Primo Accesso
1. Visita https://progetto-alpha.com
2. Clicca su "Accedi"
3. Inserisci le tue credenziali
4. Completa il tutorial introduttivo

### Prossimi Passi
- [Installazione dettagliata](installation.md)
- [Tutorial base](../tutorials/first-steps.md)
```

```bash
# Tracciamo le modifiche
git add user-guide/getting-started.md
git commit -m "📝 Add getting started guide

- Complete user onboarding process
- Add prerequisites and first access steps
- Include navigation links to related docs"
```

## 🔍 Analisi dello Stato del Repository

```bash
# Visualizziamo la cronologia
git log --oneline --graph

# Controlliamo lo stato attuale
git status

# Vediamo la struttura del repository
tree . # o ls -la se tree non è disponibile
```

## 💡 Best Practices Dimostrate

### 1. **Struttura Organizzata**
```
docs-progetto-alpha/
├── README.md                 # Punto di ingresso
├── user-guide/              # Documentazione utenti
│   ├── getting-started.md
│   └── installation.md
├── api-docs/                # Documentazione tecnica
│   ├── authentication.md
│   └── endpoints.md
├── tutorials/               # Guide pratiche
│   └── first-steps.md
└── assets/                  # Risorse multimediali
    └── images/
```

### 2. **Commit Messages Descrittivi**
```bash
# ✅ Buono - Descrive il contenuto e l'impatto
git commit -m "📚 Initial documentation structure"

# ✅ Molto buono - Include dettagli nel corpo
git commit -m "📝 Add getting started guide

- Complete user onboarding process
- Add prerequisites and first access steps
- Include navigation links to related docs"

# ❌ Evitare - Troppo generico
git commit -m "Add files"
```

### 3. **Tracking Selettivo**
```bash
# Traccia solo file rilevanti
git add README.md user-guide/

# Evita file temporanei
echo "*.tmp" >> .gitignore
echo ".DS_Store" >> .gitignore
git add .gitignore
```

## 🎯 Risultati Attesi

Dopo questo esempio dovresti avere:

1. **Repository ben strutturato** con documentazione organizzata
2. **Cronologia pulita** con commit significativi
3. **Comprensione** di come Git gestisce file non-codice
4. **Best practices** per messaggi di commit

## 🔧 Troubleshooting Comune

### Problema: File non tracciati
```bash
# Soluzione: Verificare che i file esistano
ls -la
git add <file-specifico>
```

### Problema: Messaggi di commit poco chiari
```bash
# Soluzione: Modificare l'ultimo commit
git commit --amend -m "Nuovo messaggio più descrittivo"
```

## 🚀 Prossimi Passi

1. **Sperimenta** aggiungendo più contenuti alla documentazione
2. **Pratica** commit atomici (una modifica logica per commit)
3. **Esplora** `git log` con diverse opzioni di formattazione
4. **Prova** a modificare file esistenti e osserva come Git traccia le modifiche

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ Esempio Precedente](01-progetto-sito-web.md)
- [➡️ Esempio Successivo](03-tracking-file-diversi.md)
- [📝 Esercizi](../esercizi/README.md)
