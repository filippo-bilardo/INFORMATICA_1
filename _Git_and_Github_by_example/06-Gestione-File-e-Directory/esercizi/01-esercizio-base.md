# Esercizio 1: Gestione Base dei File

## 🎯 Obiettivo
Imparare a gestire i file in un repository Git attraverso operazioni di aggiunta, modifica e rimozione.

## 📋 Prerequisiti
- Repository Git inizializzato
- Configurazione Git di base completata

## 🔧 Scenario
Stai iniziando un nuovo progetto web e devi organizzare i file di base.

## 📝 Istruzioni

### Passo 1: Preparazione del Repository
```bash
mkdir esercizio-gestione-file
cd esercizio-gestione-file
git init
git config user.name "Il Tuo Nome"
git config user.email "tuo.email@example.com"
```

### Passo 2: Creazione Struttura Base
Crea i seguenti file:

**index.html**
```html
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Sito</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Benvenuto nel mio sito</h1>
    <p>Questo è il mio primo progetto Git!</p>
</body>
</html>
```

**style.css**
```css
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 20px;
    background-color: #f0f0f0;
}

h1 {
    color: #333;
    text-align: center;
}

p {
    font-size: 16px;
    line-height: 1.5;
}
```

### Passo 3: Tracking dei File
1. Aggiungi i file al repository:
```bash
git add index.html
git add style.css
```

2. Verifica lo stato:
```bash
git status
```

3. Fai il primo commit:
```bash
git commit -m "Aggiunta struttura base del sito"
```

### Passo 4: Modifica e Aggiornamento
1. Modifica il file `index.html` aggiungendo un paragrafo:
```html
<!-- Aggiungi dopo il primo paragrafo -->
<p>Sto imparando Git e GitHub!</p>
```

2. Crea un nuovo file `script.js`:
```javascript
document.addEventListener('DOMContentLoaded', function() {
    console.log('Sito caricato con successo!');
});
```

3. Aggiungi il link al JavaScript nell'HTML:
```html
<!-- Aggiungi prima della chiusura del body -->
<script src="script.js"></script>
```

### Passo 5: Staging Selettivo
1. Visualizza le modifiche:
```bash
git status
git diff
```

2. Aggiungi solo il file JavaScript:
```bash
git add script.js
```

3. Aggiungi le modifiche all'HTML:
```bash
git add index.html
```

4. Fai il commit:
```bash
git commit -m "Aggiunta interattività JavaScript"
```

### Passo 6: Rimozione di File
1. Crea un file temporaneo:
```bash
echo "File di test" > temp.txt
git add temp.txt
git commit -m "Aggiunto file temporaneo"
```

2. Rimuovi il file dal repository e dal filesystem:
```bash
git rm temp.txt
git commit -m "Rimosso file temporaneo"
```

## ✅ Verifiche
Controlla che:
- [ ] Il repository contenga `index.html`, `style.css`, `script.js`
- [ ] La cronologia mostri almeno 3 commit
- [ ] Il file `temp.txt` non sia più presente
- [ ] `git status` mostri "working tree clean"

## 🧪 Test di Verifica
```bash
# Verifica i file nel repository
ls -la

# Verifica la cronologia
git log --oneline

# Verifica lo stato
git status
```

## 🤔 Domande di Riflessione
1. Qual è la differenza tra `git add` e `git commit`?
2. Perché è utile verificare `git status` prima di fare commit?
3. Cosa succede se modifichi un file già committato?

## 🎯 Risultato Atteso
```
esercizio-gestione-file/
├── index.html
├── style.css
└── script.js
```

Con cronologia Git pulita e file correttamente tracciati.

---
[← Torna alla Panoramica](../README.md) | [Esercizio Successivo →](./02-esercizio-intermedio.md)
