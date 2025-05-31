# 03 - Primo Repository Git

## 📖 Descrizione

In questa esercitazione metterai finalmente le mani su Git! Creerai il tuo primo repository, imparerai a tracciare file, fare i primi commit e navigare nella cronologia. È il momento di trasformare la teoria in pratica.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Inizializzare un nuovo repository Git
- ✅ Comprendere la struttura della cartella `.git`
- ✅ Aggiungere file al tracking di Git
- ✅ Creare i tuoi primi commit con messaggi significativi
- ✅ Visualizzare lo stato del repository
- ✅ Navigare nella cronologia dei commit
- ✅ Capire gli stati dei file in Git

## 📋 Prerequisiti

- **Git installato e configurato** (esercitazione precedente)
- **Conoscenza base del terminale** Linux/bash
- **Editor di testo** configurato (VS Code, vim, nano)

## ⏱️ Durata Stimata

**60-90 minuti** (pratica + sperimentazione)

## 🎯 Risultato Finale

Avrai creato un repository Git funzionante con una cronologia di commit, e comprenderai il workflow base di Git.

```bash
$ git log --oneline
a1b2c3d (HEAD -> main) Add: pagina contatti con form
d4e5f6g Update: migliorata homepage con CSS
h7i8j9k Initial commit: struttura base progetto
```

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Inizializzare Repository](./guide/01-inizializzare-repository.md)
2. [02 - Anatomia Directory Git](./guide/02-anatomia-directory-git.md)
3. [03 - Stati dei File](./guide/03-stati-file.md)
4. [04 - Primo Commit](./guide/04-primo-commit.md)
5. [05 - Visualizzare Cronologia](./guide/05-visualizzare-cronologia.md)

### Esempi Pratici
1. [01 - Progetto Sito Web](./esempi/01-progetto-sito-web.md)
2. [02 - Repository Documentazione](./esempi/02-repository-documentazione.md)
3. [03 - Tracking File Diversi](./esempi/03-tracking-file-diversi.md)
4. [04 - Repository Collaborativo Multi-Developer](./esempi/04-repository-collaborativo-multi-developer.md) ⭐⭐⭐⭐⭐

### Esercizi di Consolidamento
1. [01 - Crea il Tuo Primo Repo](./esercizi/01-primo-repo.md)
2. [02 - Gestione Stati File](./esercizi/02-gestione-stati-file.md)
3. [03 - Commit Message Best Practices](./esercizi/03-commit-messages.md)
4. [04 - Laboratorio Repository Completo](./esercizi/04-laboratorio-repository.md)

## 🚀 Quick Start - I Tuoi Primi Comandi

```bash
# 1. Crea una nuova cartella progetto
mkdir mio-primo-progetto
cd mio-primo-progetto

# 2. Inizializza Git repository
git init

# 3. Crea un file
echo "# Il Mio Primo Progetto" > README.md

# 4. Aggiungi al tracking
git add README.md

# 5. Primo commit!
git commit -m "Initial commit: aggiunge README"

# 6. Verifica
git status
git log
```

## 💡 Concetti Chiave da Ricordare

### Il Workflow Base
```
Working Directory → Staging Area → Repository
      ↓                ↓             ↓
   git add         git commit    cronologia
```

### Comandi Essenziali
- `git init` - Inizializza repository
- `git status` - Mostra stato corrente
- `git add` - Aggiungi file allo staging
- `git commit` - Crea snapshot del progetto
- `git log` - Mostra cronologia

## ⚠️ Errori Comuni da Evitare

1. **Dimenticare `git add`** prima del commit
2. **Messaggi commit vaghi** come "fix" o "update"
3. **Committare file sensibili** (password, chiavi API)
4. **Non verificare `git status`** prima del commit

## ➡️ Prossimo Passo

Una volta che hai il tuo primo repository funzionante, procedi con:
**[04-Comandi-Base-Git](../04-Comandi-Base-Git/)**

---

**Motivazione**: Congratulazioni! Stai per fare il tuo primo commit - un momento storico nel tuo percorso Git! 🎉
