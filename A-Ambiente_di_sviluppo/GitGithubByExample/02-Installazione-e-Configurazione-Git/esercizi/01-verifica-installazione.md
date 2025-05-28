# 01 - Verifica Installazione Git

## 🎯 Obiettivo

Verificare che Git sia correttamente installato e configurato attraverso una serie di test pratici e controlli sistematici.

## ⏱️ Durata

**15-20 minuti**

## 📋 Prerequisiti

- Git installato su Windows, macOS o Linux
- Accesso al terminale/prompt dei comandi
- Configurazione identità completata

---

## ✅ Test 1: Verifica Installazione Base

### 1.1 Test Versione

```bash
# Controlla versione Git installata
git --version

# ✅ Risultato atteso:
# git version 2.xx.x (dove xx >= 25)

# ❌ Se ottieni errore:
# 'git' is not recognized as an internal or external command (Windows)
# command not found: git (macOS/Linux)
```

**🔧 Risoluzione problemi:**
- **Windows**: Verifica PATH o reinstalla Git for Windows
- **macOS**: Installa Xcode Command Line Tools o Homebrew
- **Linux**: Installa con package manager della distribuzione

### 1.2 Test Percorso Installazione

```bash
# Windows (Command Prompt)
where git

# macOS/Linux
which git

# ✅ Risultati attesi:
# Windows: C:\Program Files\Git\cmd\git.exe
# macOS: /usr/local/bin/git o /opt/homebrew/bin/git
# Linux: /usr/bin/git o /usr/local/bin/git
```

### 1.3 Test Help System

```bash
# Verifica che il sistema di help funzioni
git help

# ✅ Risultato atteso: Lista dei comandi Git principali
# ❌ Se non funziona: Problema con installazione o documentazione
```

---

## ✅ Test 2: Verifica Configurazione

### 2.1 Test Identità

```bash
# Controlla configurazione nome
git config --global user.name

# Controlla configurazione email
git config --global user.email

# ✅ Risultato atteso: 
# Tuo nome e email configurati correttamente
# ❌ Se vuoto: Configura con git config --global user.name/email
```

### 2.2 Test Lista Configurazioni

```bash
# Mostra tutte le configurazioni attive
git config --list

# Mostra configurazioni globali specifiche
git config --global --list

# ✅ Verifica che siano presenti almeno:
# user.name=Il Tuo Nome
# user.email=tua@email.com
```

### 2.3 Test Editor

```bash
# Controlla editor configurato
git config --global core.editor

# ✅ Risultati tipici:
# code --wait (VS Code)
# nano (Nano)
# vim (Vim)
# ❌ Se vuoto: Configura con git config --global core.editor
```

---

## ✅ Test 3: Test Funzionalità Base

### 3.1 Creazione Repository Test

```bash
# Crea cartella di test
mkdir ~/git-verification-test
cd ~/git-verification-test

# Inizializza repository Git
git init

# ✅ Risultato atteso:
# Initialized empty Git repository in .../git-verification-test/.git/

# Verifica creazione cartella .git
ls -la
# Dovrebbe mostrare cartella .git/
```

### 3.2 Test Primo Commit

```bash
# Crea file di test
echo "# Test di Verifica Git" > README.md
echo "Data: $(date)" >> README.md
echo "Sistema: $(uname -s 2>/dev/null || echo 'Windows')" >> README.md

# Aggiungi file all'area di staging
git add README.md

# Verifica status
git status

# ✅ Risultato atteso:
# Changes to be committed:
#   new file:   README.md

# Effettua commit
git commit -m "Test commit di verifica"

# ✅ Risultato atteso:
# [main (root-commit) xxxxxxx] Test commit di verifica
# 1 file changed, 3 insertions(+)
```

### 3.3 Test Log

```bash
# Verifica cronologia commit
git log --oneline

# ✅ Risultato atteso:
# xxxxxxx Test commit di verifica

# Log dettagliato
git log

# ✅ Verifica che mostri:
# Author: Il Tuo Nome <tua@email.com>
# Date: data/ora corrente
# Message: Test commit di verifica
```

---

## ✅ Test 4: Test Editor Integration

### 4.1 Test Commit con Editor

```bash
# Crea altro file
echo "File di test per editor" > test-editor.txt
git add test-editor.txt

# Commit senza messaggio (dovrebbe aprire editor)
git commit

# ✅ Test riuscito se:
# - L'editor configurato si apre
# - Puoi scrivere messaggio di commit
# - Salvando e chiudendo, il commit viene completato

# ❌ Se l'editor non si apre o ci sono errori:
# Riconfigura: git config --global core.editor "nano"
```

### 4.2 Test Amend

```bash
# Test modifica ultimo commit
echo "Linea aggiuntiva" >> test-editor.txt
git add test-editor.txt

# Modifica ultimo commit
git commit --amend

# ✅ Test riuscito se l'editor si apre con il messaggio precedente
```

---

## ✅ Test 5: Test Configurazioni Avanzate

### 5.1 Test Alias

```bash
# Configura alcuni alias di test
git config --global alias.st "status"
git config --global alias.lg "log --oneline"

# Testa alias
git st
git lg

# ✅ Test riuscito se i comandi funzionano come abbreviazioni
```

### 5.2 Test Diff

```bash
# Modifica file esistente
echo "Modifica per test diff" >> README.md

# Test diff
git diff README.md

# ✅ Risultato atteso: mostra differenze tra versione staged e working
# ❌ Se non mostra nulla o errori: problema con configurazione diff
```

### 5.3 Test Branch

```bash
# Crea e testa branch
git branch test-branch
git branch

# ✅ Risultato atteso:
#   main
# * test-branch (se hai fatto checkout)
# oppure
# * main
#   test-branch
```

---

## ✅ Test 6: Test Sistema Operativo Specifici

### Windows-Specific Tests

```cmd
# Test Git Bash
# Apri Git Bash e verifica che funzioni

# Test from PowerShell
powershell -c "git --version"

# Test Credential Manager
git config --global credential.helper
# ✅ Risultato atteso: manager
```

### macOS-Specific Tests

```bash
# Test keychain integration
git config --global credential.helper
# ✅ Risultato atteso: osxkeychain

# Test Homebrew installation (se usato)
brew list | grep git
# ✅ Dovrebbe mostrare git se installato via Homebrew
```

### Linux-Specific Tests

```bash
# Test credential helper
git config --global credential.helper
# ✅ Risultato atteso: store, cache, o libsecret

# Test case sensitivity
touch TestFile.txt testfile.txt
ls -la Test* test*
# ✅ Su Linux dovrebbe mostrare entrambi i file (case-sensitive)
```

---

## 📊 Checklist di Verifica Completa

### ✅ Installazione Base
- [ ] `git --version` mostra versione 2.25 o superiore
- [ ] `which git` / `where git` mostra percorso corretto
- [ ] `git help` funziona correttamente
- [ ] Sistema di documentazione accessibile

### ✅ Configurazione Identità
- [ ] `git config --global user.name` configurato
- [ ] `git config --global user.email` configurato
- [ ] Email corrisponde al profilo GitHub/GitLab (se applicabile)
- [ ] Configurazioni salvate correttamente

### ✅ Editor e Tool
- [ ] `git config --global core.editor` configurato
- [ ] Editor si apre correttamente per commit
- [ ] Editor salva e chiude correttamente
- [ ] Diff tool configurato (opzionale)

### ✅ Funzionalità Base
- [ ] `git init` crea repository
- [ ] `git add` aggiunge file allo staging
- [ ] `git commit` crea commit
- [ ] `git status` mostra stato repository
- [ ] `git log` mostra cronologia

### ✅ Funzionalità Avanzate
- [ ] Alias configurati e funzionanti
- [ ] Branch creation e navigation
- [ ] Diff visualization
- [ ] Commit amend funzionante

### ✅ Integrazioni Sistema
- [ ] Credential helper configurato
- [ ] PATH correttamente impostato
- [ ] Terminal integration attiva
- [ ] Line endings configurati per OS

---

## 🚨 Risoluzione Problemi Comuni

### Problema: Comando git non trovato
```bash
# Verifica installazione
# Windows: Reinstalla Git for Windows
# macOS: xcode-select --install o brew install git
# Linux: sudo apt install git (o equivalente)
```

### Problema: Editor non si apre
```bash
# Riconfigura editor
git config --global core.editor "nano"    # Semplice
git config --global core.editor "code --wait"  # VS Code
```

### Problema: Configurazioni non salvate
```bash
# Verifica permessi file configurazione
ls -la ~/.gitconfig

# Ricrea configurazione se necessario
git config --global user.name "Tuo Nome"
git config --global user.email "tua@email.com"
```

### Problema: Repository di test non funziona
```bash
# Pulisci e ricrea
cd ~
rm -rf git-verification-test
mkdir git-verification-test
cd git-verification-test
git init
```

---

## 🎯 Risultato Atteso

Al termine di tutti i test dovresti avere:

✅ **Git funzionante** con tutte le funzionalità base
✅ **Configurazione completa** e personalizzata
✅ **Editor integrato** per commit e modifiche
✅ **Repository di test** creato e funzionante
✅ **Confidenza** nell'uso dei comandi base Git

---

## 📝 Report di Verifica

Usa questo template per documentare i risultati:

```
REPORT VERIFICA INSTALLAZIONE GIT
================================

Data: ___________
Sistema Operativo: ___________
Versione Git: ___________

RISULTATI TEST:
[ ] Installazione Base - OK/FAIL
[ ] Configurazione Identità - OK/FAIL  
[ ] Editor Integration - OK/FAIL
[ ] Funzionalità Base - OK/FAIL
[ ] Test Avanzati - OK/FAIL

PROBLEMI RISCONTRATI:
_________________________
_________________________

SOLUZIONI APPLICATE:
_________________________
_________________________

SETUP COMPLETATO: SI/NO
```

---

## 🔗 Prossimi Passi

✅ **Completato**: Verifica installazione
🎯 **Prossimo**: [Configurazione Personalizzata](./02-configurazione-personalizzata.md)

---

## 📚 Risorse per Debug

- [Git Installation Guide](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- [Git Configuration Documentation](https://git-scm.com/docs/git-config)
- [Troubleshooting Git Setup](https://docs.github.com/en/get-started/quickstart/set-up-git)
