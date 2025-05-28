# Esempi Pratici - Risoluzione Conflitti

## 📚 Panoramica

Questa sezione contiene esempi pratici e interattivi per imparare la risoluzione dei conflitti di merge in Git. Ogni esempio è progettato per fornire esperienza hands-on con scenari reali.

## 🎯 Struttura degli Esempi

### 1. [Conflitto Semplice](./01-conflitto-semplice.md)
**Livello**: Principiante  
**Durata**: 15-20 minuti  
**Scenario**: Due sviluppatori modificano la stessa funzione
- Conflitto in singolo file
- Risoluzione manuale con editor
- Verifica e commit finale

### 2. [Conflitti Multi-File](./02-conflitti-multi-file.md)
**Livello**: Intermedio  
**Durata**: 30-40 minuti  
**Scenario**: Refactoring che tocca multipli componenti
- Conflitti in CSS, JavaScript e HTML
- Coordinate decision making
- Testing post-risoluzione

### 3. [Risoluzione con VS Code](./03-risoluzione-vscode.md)
**Livello**: Intermedio  
**Durata**: 25-30 minuti  
**Scenario**: Uso di merge tool grafico
- Configurazione VS Code merge tool
- Interfaccia point-and-click
- Workflow ottimizzato

### 4. [Conflitti Complessi](./04-conflitti-complessi.md)
**Livello**: Avanzato  
**Durata**: 45-60 minuti  
**Scenario**: Merge di feature major con architettura changes
- Risoluzione multi-step
- Strategia di integrazione
- Team coordination

## 🛠️ Setup Comune

Prima di iniziare qualsiasi esempio, assicurati di avere:

### Strumenti Necessari
```bash
# Git (versione 2.20+)
git --version

# Editor di testo (VS Code consigliato)
code --version

# Node.js per esempi JavaScript
node --version
npm --version
```

### Configurazione Base
```bash
# Configura informazioni utente
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Configura merge tool (opzionale)
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
git config --global mergetool.keepBackup false
```

### Directory di Lavoro
```bash
# Crea directory per gli esempi
mkdir git-conflict-examples
cd git-conflict-examples
```

## 📋 Come Utilizzare gli Esempi

### 1. Preparazione
- Leggi l'introduzione dell'esempio
- Prepara l'ambiente di lavoro
- Clona o inizializza il repository di esempio

### 2. Esecuzione
- Segui i passaggi step-by-step
- Non aver fretta: comprendi ogni operazione
- Usa i comandi diagnostici per verificare lo stato

### 3. Verifica
- Controlla che la risoluzione sia corretta
- Esegui test se presenti
- Confronta con la soluzione proposta

### 4. Sperimentazione
- Modifica l'esempio per creare varianti
- Prova strategie di risoluzione alternative
- Discuti con il team le decisioni prese

## 🔍 Comando di Debugging Utili

Durante gli esempi, usa questi comandi per capire lo stato:

```bash
# Stato generale del repository
git status

# Storia dei commit  
git log --oneline --graph

# Differenze durante conflitto
git diff

# File in conflitto
git diff --name-only --diff-filter=U

# Visualizza marker di conflitto
grep -n "<<<<<<\|======\|>>>>>>" filename.js
```

## 📚 Risorse Aggiuntive

### Cheat Sheet
```bash
# Durante un conflitto
git status                    # Vedi file in conflitto
git diff                      # Mostra differenze
git mergetool                 # Apri merge tool
git add <file>               # Mark come risolto
git commit                   # Completa merge

# Emergenza
git merge --abort            # Annulla merge
git reset --hard HEAD       # Reset completo (ATTENZIONE!)
```

### File di Supporto
- **conflict-markers.txt**: Esempi di marker Git
- **resolution-template.md**: Template per documentare risoluzioni
- **test-scripts/**: Script per validare risoluzioni

## ⚠️ Note Importanti

### Backup
Gli esempi possono essere distruttivi. Sempre:
```bash
# Crea backup prima di iniziare
git branch backup-$(date +%Y%m%d-%H%M%S)
```

### Repository Pulito
Inizia sempre con repository pulito:
```bash
git status  # Deve mostrare "working tree clean"
```

### Non Aver Paura
- I conflitti sono normali nello sviluppo
- Ogni errore è un'opportunità di apprendimento
- Si può sempre tornare indietro con `git merge --abort`

## 🎯 Obiettivi di Apprendimento

Al termine degli esempi sarai in grado di:

- ✅ Riconoscere immediatamente i marker di conflitto
- ✅ Scegliere la strategia di risoluzione appropriata
- ✅ Usare merge tools grafici con confidenza
- ✅ Gestire conflitti in progetti multi-file
- ✅ Prevenire conflitti futuri con best practices
- ✅ Documentare e comunicare decisioni di risoluzione

## 🔄 Sequenza Consigliata

1. **Inizia** con l'esempio semplice per familiarizzare
2. **Progredisci** agli esempi multi-file
3. **Sperimenta** con VS Code merge tool
4. **Affronta** i conflitti complessi quando ti senti sicuro
5. **Revisita** gli esempi per rinforzare l'apprendimento

## 📞 Aiuto e Supporto

Se rimani bloccato:
- Controlla la documentazione Git ufficiale
- Consulta Stack Overflow per scenari simili
- Usa `git help merge` per riferimento comandi
- Chiedi aiuto al team o mentor

---

**Pronto?** Inizia con il [primo esempio pratico](./01-conflitto-semplice.md)!
