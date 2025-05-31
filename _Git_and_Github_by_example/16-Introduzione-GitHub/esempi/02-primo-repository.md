# 02 - Creazione del Primo Repository su GitHub

## 🎯 Obiettivo

Creare il tuo primo repository su GitHub utilizzando l'interfaccia web e comprendere le opzioni di configurazione disponibili.

## 📋 Prerequisiti

- Account GitHub attivo
- Browser web
- Idee per il contenuto del repository

## 🚀 Procedura Passo-Passo

### Passo 1: Accesso e Navigazione

1. **Effettua il login** su [GitHub.com](https://github.com)
2. **Clicca sul pulsante verde "New"** o sull'icona "+" in alto a destra
3. **Seleziona "New repository"**

### Passo 2: Configurazione Repository

#### Informazioni Base
```
Repository name: il-mio-primo-repo
Description: Il mio primo repository GitHub per imparare Git
```

**Campi da compilare**:
- **Repository name**: `il-mio-primo-repo` (senza spazi!)
- **Description**: "Il mio primo repository GitHub per imparare Git"
- **Visibility**: 
  - ✅ **Public**: Visibile a tutti (consigliato per iniziare)
  - ❌ **Private**: Solo tu puoi vederlo

#### Inizializzazione Repository

**Opzioni disponibili**:
- ✅ **Add a README file**: Crea automaticamente README.md
- ✅ **Add .gitignore**: Seleziona template per il tuo linguaggio
- ✅ **Choose a license**: Importante per progetti open source

**Configurazione consigliata per principianti**:
```
☑️ Add a README file
☑️ Add .gitignore (template: "None" per ora)
☑️ Choose a license: MIT License
```

### Passo 3: Creazione

1. **Verifica tutte le impostazioni**
2. **Clicca "Create repository"**
3. **Congratulazioni!** Hai creato il tuo primo repository

## 📝 Esplorazione del Repository Creato

### Struttura Iniziale
```
il-mio-primo-repo/
├── README.md         # Documentazione principale
├── LICENSE           # Licenza MIT
└── .git/            # Cartella Git (nascosta)
```

### Interfaccia Repository

**Header del repository**:
```
tuonome / il-mio-primo-repo    [Watch] [Star] [Fork]
                                  👁️     ⭐     🍴
Public repository • 0 commits • 1 branch
```

**Elementi visibili**:
- **URL del repository**: `https://github.com/tuonome/il-mio-primo-repo`
- **Clone buttons**: HTTPS/SSH/GitHub CLI
- **Branch attivo**: `main` (branch principale)
- **File listing**: README.md e LICENSE

## ✏️ Primi Contenuti

### Passo 1: Modifica il README

1. **Clicca sul file `README.md`**
2. **Clicca sull'icona matita** per modificare
3. **Sostituisci il contenuto** con:

```markdown
# Il Mio Primo Repository

Benvenuto nel mio primo repository GitHub! 🎉

## Descrizione

Questo repository è stato creato per imparare a utilizzare Git e GitHub.

## Cosa sto imparando

- ✅ Creare repository su GitHub
- ✅ Modificare file tramite interfaccia web
- ✅ Fare commit delle modifiche
- 🔄 Clonare repository localmente
- 🔄 Push e pull tra locale e remoto

## Progetti futuri

- [ ] Aggiungere un progetto HTML/CSS
- [ ] Creare una pagina web personale
- [ ] Collaborare con altri sviluppatori

## Contatti

- GitHub: [@tuonome](https://github.com/tuonome)
- Email: tua.email@esempio.com

---

*Repository creato come parte del corso Git e GitHub by Example*
```

4. **Scorri in basso** alla sezione "Commit changes"

### Passo 2: Primo Commit

**Compilazione commit**:
```
Commit title: Aggiorna README con informazioni personali

Extended description (opzionale):
- Aggiunta descrizione del repository
- Aggiunta lista obiettivi di apprendimento  
- Aggiunta sezione contatti
```

**Opzioni commit**:
- ✅ **Commit directly to the `main` branch**
- ❌ **Create a new branch** (per ora)

5. **Clicca "Commit changes"**

## 📁 Aggiungere Nuovi File

### Passo 1: Creare un File HTML

1. **Clicca "Add file" > "Create new file"**
2. **Nome file**: `index.html`
3. **Contenuto**:

```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Primo Sito</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
            text-align: center;
        }
        .github-link {
            text-align: center;
            margin-top: 20px;
        }
        .github-link a {
            color: #0366d6;
            text-decoration: none;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Benvenuto nel Mio Primo Sito! 🚀</h1>
        <p>Questo è il mio primo progetto hosting su GitHub.</p>
        <p>Sto imparando:</p>
        <ul>
            <li>HTML e CSS</li>
            <li>Git e GitHub</li>
            <li>Web Development</li>
        </ul>
        <div class="github-link">
            <a href="https://github.com/tuonome/il-mio-primo-repo">
                Vedi il codice su GitHub
            </a>
        </div>
    </div>
</body>
</html>
```

4. **Commit message**: `Aggiungi pagina HTML iniziale`
5. **Clicca "Commit new file"**

### Passo 2: Aggiungere CSS Esterno

1. **Crea nuovo file**: `style.css`
2. **Contenuto**:

```css
/* Style aggiuntivo per il sito */
.highlight {
    background-color: #ffeb3b;
    padding: 2px 4px;
    border-radius: 3px;
}

.progress-bar {
    background-color: #e0e0e0;
    border-radius: 10px;
    padding: 3px;
    margin: 10px 0;
}

.progress-fill {
    background-color: #4caf50;
    height: 20px;
    border-radius: 8px;
    text-align: center;
    line-height: 20px;
    color: white;
    font-weight: bold;
    font-size: 12px;
}
```

3. **Commit message**: `Aggiungi file CSS per stili aggiuntivi`

## 🌐 Visualizzazione del Sito

### Abilitare GitHub Pages

1. **Vai nelle Settings** del repository
2. **Scorri fino a "Pages"** nella sidebar sinistra
3. **Seleziona Source**: Deploy from a branch
4. **Branch**: main / (root)
5. **Clicca "Save"**

Dopo qualche minuto, il sito sarà disponibile su:
`https://tuonome.github.io/il-mio-primo-repo`

## 📊 Riepilogo Risultati

Dopo aver completato questo esempio, avrai:

### Repository con Struttura:
```
il-mio-primo-repo/
├── README.md         # Documentazione aggiornata
├── LICENSE           # Licenza MIT
├── index.html        # Pagina web principale
└── style.css         # Fogli di stile
```

### Competenze Acquisite:
- ✅ Creazione repository su GitHub
- ✅ Configurazione repository (README, licenza, visibilità)
- ✅ Modifica file tramite interfaccia web
- ✅ Creazione di commit meaningful
- ✅ Aggiunta di nuovi file
- ✅ Attivazione GitHub Pages
- ✅ Struttura base di un progetto web

### Link Utili del Tuo Repository:
- **Repository**: `https://github.com/tuonome/il-mio-primo-repo`
- **Clone HTTPS**: `https://github.com/tuonome/il-mio-primo-repo.git`
- **Sito GitHub Pages**: `https://tuonome.github.io/il-mio-primo-repo`

## 🔄 Prossimi Passi

1. **Personalizza ulteriormente** il contenuto
2. **Sperimenta** con altri file (JavaScript, immagini)
3. **Invita amici** a vedere il tuo repository
4. **Impara a clonare** il repository localmente
5. **Esplora** le statistiche nella tab "Insights"

## 💡 Pro Tips

- **Commit frequenti**: Meglio tanti piccoli commit che uno grande
- **Messaggi descrittivi**: Spiega cosa hai cambiato e perché
- **README aggiornato**: È la prima cosa che vedono i visitatori
- **Licenza appropriata**: MIT è buona per progetti di apprendimento
- **GitHub Pages**: Ottimo per hosting gratuito di siti statici

---

**Prossimo**: [GitHub Desktop vs Web Interface](03-github-desktop-vs-web.md) | [Torna agli esempi](README.md)
