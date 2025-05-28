# 07 - Git Ignore e File Tracking

## 📖 Descrizione

Questa esercitazione copre l'uso del file `.gitignore` per controllare quali file e directory Git deve tracciare o ignorare, una competenza fondamentale per mantenere repository puliti e sicuri.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Creare e configurare file `.gitignore` efficaci
- ✅ Comprendere i pattern di esclusione e inclusione
- ✅ Gestire file già tracciati che vuoi ignorare
- ✅ Utilizzare `.gitignore` globali e locali
- ✅ Gestire file sensibili e temporanei
- ✅ Configurare ignore per diversi tipi di progetto

## 📋 Prerequisiti

- **Completamento** del [Modulo 06 - Gestione File e Directory](../06-Gestione-File-e-Directory/)
- **Conoscenza** dei comandi base di Git
- **Familiarità** con i pattern glob e regex

## ⏱️ Durata Stimata

**45-60 minuti** (teoria + esercizi pratici)

## 🎯 Risultato Finale

Al termine avrai padronanza completa del sistema `.gitignore`, sapendo come proteggere il tuo repository da file indesiderati e sensibili.

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [📖 Introduzione a .gitignore](./guide/01-introduzione-gitignore.md)
2. [📖 Pattern e Sintassi](./guide/02-pattern-sintassi.md)
3. [📖 Gitignore Globale e Locale](./guide/03-globale-locale.md)
4. [📖 Gestione File Già Tracciati](./guide/04-file-tracciati.md)
5. [📖 Template per Progetti Comuni](./guide/05-template-progetti.md)

### Esempi Pratici
1. [💻 Setup Progetto Node.js](./esempi/01-setup-nodejs.md)
2. [💻 Progetto Python](./esempi/02-progetto-python.md)
3. [💻 Ambiente di Sviluppo Completo](./esempi/03-ambiente-completo.md)

### Esercizi
1. [🎯 Configurazione Base](./esercizi/01-configurazione-base.md)
2. [🎯 Progetto Multi-linguaggio](./esercizi/02-progetto-multi-linguaggio.md)
3. [🎯 Sicurezza e Best Practices](./esercizi/03-sicurezza-best-practices.md)

## 🎮 Esercitazione Pratica

### Scenario: Configurazione Repository Multi-progetto

Lavorerai con un repository che contiene progetti in diversi linguaggi e dovrai configurare un sistema di `.gitignore` completo e sicuro.

**Cosa imparerai:**
- Creazione di pattern di esclusione complessi
- Gestione di configurazioni sensibili
- Ottimizzazione per diversi ambienti di sviluppo

## 💡 Concetti Chiave

### File da Ignorare Tipicamente
- **Build artifacts** (build/, dist/, target/)
- **Dipendenze** (node_modules/, vendor/, __pycache__/)
- **File di configurazione** (.env, config.local.js)
- **File temporanei** (*.tmp, *.log, *.cache)
- **File IDE** (.vscode/, .idea/, *.swp)
- **File di sistema** (.DS_Store, Thumbs.db)

### Pattern Comuni
```gitignore
# Directory
node_modules/
build/

# Estensioni
*.log
*.tmp

# File specifici
.env
config.json

# Eccezioni
!important.log
```

## 🚨 Problemi Comuni e Soluzioni

### Problema: File già tracciato
```bash
# Il file è già nel repository
git rm --cached file-da-ignorare.txt
echo "file-da-ignorare.txt" >> .gitignore
```

### Problema: .gitignore non funziona
```bash
# Pulisci la cache e riapplica
git rm -r --cached .
git add .
```

## 🔗 Collegamenti Utili

- [gitignore.io](https://www.toptal.com/developers/gitignore) - Generator di .gitignore
- [GitHub gitignore templates](https://github.com/github/gitignore) - Template ufficiali
- [Git documentation](https://git-scm.com/docs/gitignore) - Documentazione ufficiale

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 06 - Gestione File e Directory](../06-Gestione-File-e-Directory/)
- [➡️ 08 - Branching Base](../08-Branching-Base/)
