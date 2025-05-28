# Tracciamento File e Directory

## Concetti Fondamentali

### Cos'è il Tracciamento dei File
Git traccia i file attraverso tre stati principali:
- **Untracked**: File non ancora sotto controllo di versione
- **Tracked**: File già conosciuti da Git
- **Ignored**: File esplicitamente esclusi dal tracciamento

### Come Git Monitora i Cambiamenti

Git monitora i file attraverso:
1. **Contenuto del file**: Calcola hash SHA-1 per ogni file
2. **Metadata**: Permessi, timestamp, dimensione
3. **Percorsi**: Posizione e nome del file nel filesystem

## Comandi Principali

### `git add` - Aggiungere File al Tracciamento

```bash
# Aggiungere un singolo file
git add nomefile.txt

# Aggiungere tutti i file di una directory
git add cartella/

# Aggiungere tutti i file modificati
git add .

# Aggiungere file con pattern
git add *.html
git add docs/*.md
```

### `git rm` - Rimuovere File dal Tracciamento

```bash
# Rimuovere file dal repository e dal filesystem
git rm file.txt

# Rimuovere solo dal tracciamento, mantenere nel filesystem
git rm --cached file.txt

# Rimuovere directory ricorsivamente
git rm -r cartella/

# Forzare la rimozione di file modificati
git rm -f file.txt
```

### `git status` - Verificare Stato dei File

```bash
# Stato completo
git status

# Stato conciso
git status -s

# Ignorare file non tracciati
git status --ignored
```

## Gestione Avanzata

### File con Spazi nei Nomi
```bash
# Usare virgolette per file con spazi
git add "file con spazi.txt"

# Usare escape per caratteri speciali
git add file\ con\ spazi.txt
```

### Aggiunta Interattiva
```bash
# Modalità interattiva per scegliere cosa aggiungere
git add -i

# Aggiungere parti specifiche di un file
git add -p file.txt
```

## Casi d'Uso Pratici

### 1. Nuovo Progetto
```bash
# Inizializzare repository
git init

# Aggiungere tutti i file del progetto
git add .

# Primo commit
git commit -m "Initial commit"
```

### 2. Aggiungere Nuove Features
```bash
# Creare nuovi file
touch feature.js
touch feature.css

# Aggiungere al tracciamento
git add feature.js feature.css

# Verificare stato
git status
```

### 3. Pulizia File Temporanei
```bash
# Rimuovere file temporanei dal tracciamento
git rm --cached *.tmp
git rm --cached *.log

# Aggiungere al .gitignore per il futuro
echo "*.tmp" >> .gitignore
echo "*.log" >> .gitignore
```

## Errori Comuni e Soluzioni

### ❌ Problema: File aggiunto per errore
```bash
# Errore
git add password.txt
```

**✅ Soluzione:**
```bash
# Rimuovere dal staging prima del commit
git reset HEAD password.txt

# Se già committato, rimuovere dal tracciamento
git rm --cached password.txt
git commit -m "Remove sensitive file"
```

### ❌ Problema: Directory vuota non tracciata
```bash
# Le directory vuote non vengono tracciate da Git
mkdir empty-folder
git add empty-folder/  # Non funziona
```

**✅ Soluzione:**
```bash
# Aggiungere file placeholder
touch empty-folder/.gitkeep
git add empty-folder/.gitkeep
```

### ❌ Problema: File con caratteri speciali
```bash
# Errore con caratteri Unicode o speciali
git add file_with_émojis_🚀.txt  # Può causare problemi
```

**✅ Soluzione:**
```bash
# Usare virgolette
git add "file_with_émojis_🚀.txt"

# Verificare encoding del sistema
git config core.quotepath false
```

## Best Practices

### ✅ Consigli per il Tracciamento Efficace

1. **Aggiungi file logicamente correlati insieme**
   ```bash
   git add feature.js feature.css feature.html
   git commit -m "Add new feature X"
   ```

2. **Usa .gitignore proattivamente**
   ```bash
   # Creare .gitignore prima di aggiungere file
   echo "node_modules/" > .gitignore
   echo "*.log" >> .gitignore
   git add .gitignore
   ```

3. **Verifica sempre prima del commit**
   ```bash
   git status
   git diff --cached  # Mostra cosa verrà committato
   ```

4. **Organizza la struttura logicamente**
   ```
   project/
   ├── src/           # Codice sorgente
   ├── docs/          # Documentazione
   ├── tests/         # Test
   └── assets/        # Risorse statiche
   ```

## Quiz di Autovalutazione

### Domanda 1
Quale comando rimuove un file dal tracciamento Git mantenendolo nel filesystem?
- a) `git rm file.txt`
- b) `git rm --cached file.txt` ✅
- c) `git delete file.txt`
- d) `git remove file.txt`

### Domanda 2
Come aggiungere tutti i file con estensione .js?
- a) `git add *.js` ✅
- b) `git add all .js`
- c) `git add --js`
- d) `git add files .js`

### Domanda 3
Quale file viene comunemente usato per le directory vuote?
- a) `.empty`
- b) `.placeholder`
- c) `.gitkeep` ✅
- d) `.folder`

### Domanda 4
Come forzare la rimozione di un file modificato?
- a) `git rm file.txt`
- b) `git rm -f file.txt` ✅
- c) `git rm --force file.txt` ✅
- d) Entrambe b e c ✅

### Domanda 5
Quale comando mostra lo stato in formato conciso?
- a) `git status`
- b) `git status -s` ✅
- c) `git status --short` ✅
- d) Entrambe b e c ✅

## Esercizi Pratici

### Esercizio 1: Organizzazione Base
1. Crea un nuovo repository
2. Aggiungi file di diversi tipi (.txt, .js, .css)
3. Verifica lo stato e traccia tutti i file
4. Fai il primo commit

### Esercizio 2: Gestione Errori
1. Aggiungi accidentalmente un file sensibile
2. Rimuovilo dal staging
3. Aggiungilo al .gitignore
4. Verifica che non venga più tracciato

### Esercizio 3: Struttura Complessa
1. Crea una struttura con directory annidate
2. Aggiungi file in ogni directory
3. Usa pattern per aggiungere file specifici
4. Verifica che tutto sia tracciato correttamente

## Navigazione del Corso
- [📑 Indice](../../README.md)
- [⬅️ 05 - Area di Staging](../../05-Area-di-Staging/)
- [➡️ Rinominare e Spostare File](./02-rinominare-spostare.md)
