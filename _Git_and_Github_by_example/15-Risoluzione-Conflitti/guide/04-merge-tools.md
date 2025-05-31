# Merge Tools per Risoluzione Conflitti

## 🎯 Obiettivi
- Configurare e usare merge tools grafici
- Confrontare opzioni disponibili
- Ottimizzare il workflow di risoluzione

## 🛠️ Introduzione ai Merge Tools

I **merge tools** sono applicazioni che forniscono un'interfaccia grafica per risolvere conflitti, rendendo il processo più intuitivo e visuale rispetto alla modifica manuale.

### Vantaggi dei Merge Tools
- **Visualizzazione chiara** delle differenze
- **Interfaccia point-and-click**
- **Anteprima del risultato**
- **Navigazione rapida** tra conflitti
- **Backup automatico** delle versioni

## 🖥️ Merge Tools Popolari

### 1. VS Code (Gratuito)
**Integrato nell'editor più popolare**

#### Configurazione
```bash
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
```

#### Utilizzo
```bash
git mergetool
# Si apre VS Code con interfaccia di merge
```

#### Caratteristiche
- ✅ Gratuito e ampiamente usato
- ✅ Integrazione perfetta con sviluppo
- ✅ Sintassi highlighting
- ✅ Bottoni intuitivi: "Accept Current", "Accept Incoming", "Accept Both"
- ❌ Funzionalità di merge basic

### 2. GitKraken (Freemium)
**Client Git completo con merge avanzato**

#### Installazione
```bash
# Download da https://www.gitkraken.com/
# Configurazione automatica
```

#### Caratteristiche
- ✅ Interfaccia visuale eccellente
- ✅ Vista a 3 pannelli (Base, Current, Incoming)
- ✅ Drag & drop per risoluzioni
- ✅ Timeline visiva dei commit
- ❌ A pagamento per repo privati

### 3. Beyond Compare (A Pagamento)
**Tool professionale per Windows/Mac/Linux**

#### Configurazione
```bash
git config --global merge.tool bc3
git config --global mergetool.bc3.path "C:/Program Files/Beyond Compare 4/bcomp.exe"
```

#### Caratteristiche
- ✅ Funzionalità avanzatissime
- ✅ Supporto molti formati file
- ✅ Merge a 3 vie perfetto
- ✅ Regole di merge personalizzabili
- ❌ Costo licenza

### 4. Meld (Gratuito - Linux)
**Merge tool nativo per sistemi Linux**

#### Installazione Ubuntu/Debian
```bash
sudo apt install meld
git config --global merge.tool meld
```

#### Caratteristiche
- ✅ Completamente gratuito
- ✅ Interfaccia pulita
- ✅ Buona per utenti Linux
- ❌ Solo Linux/alcune distribuzioni

### 5. P4Merge (Gratuito)
**Tool di Perforce, multipiattaforma**

#### Configurazione
```bash
git config --global merge.tool p4merge
git config --global mergetool.p4merge.path "/Applications/p4merge.app/Contents/MacOS/p4merge"
```

## 🔧 Configurazione Dettagliata

### Configurazione VS Code
```bash
# Imposta VS Code come merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait --merge $REMOTE $LOCAL $BASE $MERGED'

# Non creare file .orig
git config --global mergetool.keepBackup false

# Trust dell'exit code
git config --global mergetool.vscode.trustExitCode true
```

### Configurazione GitKraken
```bash
# GitKraken si configura automaticamente quando installato
# Verifica configurazione
git config --global --list | grep merge
```

### Configurazione Personalizzata
```bash
# Per tool custom
git config --global merge.tool mytool
git config --global mergetool.mytool.cmd '/path/to/tool $LOCAL $BASE $REMOTE $MERGED'
git config --global mergetool.mytool.trustExitCode true
```

## 📋 Workflow con Merge Tools

### 1. Inizio Merge Tool
```bash
# Dopo un merge con conflitti
git merge feature-branch
# Auto-merging file.txt
# CONFLICT (content): Merge conflict in file.txt

# Avvia merge tool
git mergetool
```

### 2. Interfaccia VS Code
```text
╭─────────────── VS Code Merge Interface ───────────────╮
│                                                        │
│  [Accept Current Change] [Accept Incoming Change]     │
│  [Accept Both Changes]   [Compare Changes]            │
│                                                        │
│  <<<<<<< HEAD                                         │
│  Current branch content                               │
│  =======                                              │
│  Incoming branch content                              │
│  >>>>>>> feature-branch                              │
│                                                        │
╰────────────────────────────────────────────────────────╯
```

### 3. Processo in GitKraken
```text
╭─── GitKraken 3-Way Merge ───╮
│                              │
│ [Local]  [Base]  [Remote]   │
│    │        │        │      │
│    └────────┼────────┘      │
│             │               │
│         [Result]            │
│                              │
╰──────────────────────────────╯
```

## 🎮 Operazioni Comuni

### VS Code - Operazioni con Bottoni
```text
Accept Current Change    → Mantieni versione HEAD
Accept Incoming Change   → Mantieni versione incoming
Accept Both Changes      → Combina entrambe
Compare Changes         → Vista side-by-side
```

### GitKraken - Drag & Drop
```text
1. Visualizza 3 pannelli: Local | Base | Remote
2. Trascina blocchi di codice nel pannello Result
3. Modifica manualmente se necessario
4. Salva e conferma
```

### Beyond Compare - Regole Avanzate
```text
1. Imposta regole di merge automatiche
2. Usa filtri per ignorare whitespace
3. Configura merge templates
4. Salva configurazioni per progetti
```

## 📝 Esempio Pratico

### Scenario: Conflitto in React Component
```jsx
// File: src/components/Header.jsx
import React from 'react';

function Header() {
  return (
<<<<<<< HEAD
    <header className="header-main">
      <h1>My App</h1>
      <nav>
        <a href="/home">Home</a>
        <a href="/about">About</a>
      </nav>
    </header>
=======
    <header className="app-header">
      <h1>My Application</h1>
      <nav className="navigation">
        <a href="/">Home</a>
        <a href="/about">About</a>
        <a href="/contact">Contact</a>
      </nav>
    </header>
>>>>>>> feature/navigation-update
  );
}

export default Header;
```

### Risoluzione con VS Code
1. **Apri** `git mergetool`
2. **VS Code mostra** interfaccia con bottoni
3. **Analizza** le differenze:
   - HEAD: `header-main`, "My App", 2 link
   - Incoming: `app-header`, "My Application", 3 link
4. **Decisione**: Combina il meglio di entrambi
5. **Click** "Accept Both Changes" come base
6. **Modifica manuale** per ottimizzare:

```jsx
<header className="app-header">
  <h1>My Application</h1>
  <nav className="navigation">
    <a href="/">Home</a>
    <a href="/about">About</a>
    <a href="/contact">Contact</a>
  </nav>
</header>
```

## ⚙️ Configurazioni Avanzate

### 1. Merge Tool per Tipo File
```bash
# Diversi tool per diversi file
git config --global merge.tool p4merge

# Per file specifici
echo "*.xlsx diff=binary" >> .gitattributes
echo "*.xlsx merge=binary" >> .gitattributes
```

### 2. Script Personalizzati
```bash
#!/bin/bash
# merge-wrapper.sh
echo "Merging: $4"
code --wait --merge "$1" "$2" "$3" "$4"
exit $?
```

### 3. Configurazione Progetto
```bash
# Nel progetto specifico
git config merge.tool vscode
git config mergetool.vscode.cmd 'code --wait $MERGED'
```

## 🔍 Debugging Merge Tools

### Verifica Configurazione
```bash
# Mostra configurazione merge
git config --list | grep merge

# Testa merge tool
git mergetool --tool-help
```

### Problemi Comuni

#### VS Code Non Si Apre
```bash
# Verifica path di VS Code
which code

# Su Windows
git config --global mergetool.vscode.cmd '"C:\Users\User\AppData\Local\Programs\Microsoft VS Code\bin\code" --wait $MERGED'
```

#### Tool Non Riconosciuto
```bash
# Lista tool disponibili
git mergetool --tool-help

# Forza un tool specifico
git mergetool --tool=vimdiff
```

## 💡 Best Practices

### 1. Preparazione
- **Configura** tool prima dei conflitti
- **Testa** configurazione su conflitti semplici
- **Mantieni** backup delle configurazioni

### 2. Durante Risoluzione
- **Comprendi** sempre il contesto
- **Testa** risultato prima di salvare
- **Non** fare merge automatici ciechi

### 3. Team Setup
```bash
# Script di setup team
#!/bin/bash
echo "Configurazione Git per il team..."
git config --global merge.tool vscode
git config --global mergetool.keepBackup false
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
echo "Configurazione completata!"
```

## ➡️ Prossimo Passo

Nel prossimo modulo impareremo le **strategie di prevenzione** per ridurre al minimo i conflitti di merge.
