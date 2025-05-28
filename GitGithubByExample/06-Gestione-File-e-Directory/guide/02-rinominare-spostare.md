# Rinominare e Spostare File

## Concetti Fondamentali

### Come Git Gestisce Rinominazioni e Spostamenti
Git non traccia esplicitamente le rinominazioni, ma le rileva attraverso:
1. **Similarità del contenuto**: Confronta il contenuto dei file
2. **Algoritmi di rilevamento**: Identifica quando un file è stato spostato/rinominato
3. **Soglia di similarità**: Default 50% per considerare un file "rinominato"

### Differenza tra Move e Rename
- **Move**: Spostamento in directory diversa
- **Rename**: Cambio di nome nella stessa directory
- **Move + Rename**: Combinazione di entrambi

## Comandi Principali

### `git mv` - Rinominare e Spostare File

```bash
# Rinominare un file
git mv vecchio-nome.txt nuovo-nome.txt

# Spostare un file in altra directory
git mv file.txt cartella/

# Spostare e rinominare simultaneamente
git mv file.txt cartella/nuovo-nome.txt

# Spostare directory intera
git mv vecchia-cartella/ nuova-cartella/
```

### Operazioni Manuali con `mv` + `git add/rm`

```bash
# Metodo manuale (sconsigliato ma funzionale)
mv vecchio.txt nuovo.txt
git rm vecchio.txt
git add nuovo.txt

# Git riconoscerà automaticamente la rinominazione
```

### Verificare Rinominazioni

```bash
# Mostrare rinominazioni nel log
git log --follow file.txt

# Mostrare rinominazioni nei diff
git diff --find-renames

# Mostrare statistiche di rinominazione
git diff --stat --find-renames
```

## Gestione Avanzata

### Configurare Soglia di Rilevamento
```bash
# Impostare soglia di similarità per rinominazioni (0-100%)
git config diff.renames 50

# Abilitare rilevamento rinominazioni nei merge
git config merge.renames true

# Mostrare rinominazioni con soglia personalizzata
git diff --find-renames=80%
```

### Rinominazioni Case-Sensitive
```bash
# Su sistemi case-insensitive (Windows, macOS)
# Problema: rinominare da file.txt a File.txt

# Soluzione 1: Rinominazione in due passi
git mv file.txt temp-file.txt
git mv temp-file.txt File.txt

# Soluzione 2: Forzare case sensitivity
git config core.ignorecase false
```

### Gestione Conflitti nelle Rinominazioni
```bash
# Quando due branch rinominano lo stesso file diversamente
# Git mostrerà un conflitto di rinominazione

# Risolvere manualmente
git add nuovo-nome-scelto.txt
git rm nome-alternativo.txt
```

## Casi d'Uso Pratici

### 1. Refactoring Struttura Progetto
```bash
# Ristrutturare progetto web
git mv styles.css assets/css/main.css
git mv script.js assets/js/app.js
git mv images/ assets/img/

# Aggiornare riferimenti nei file HTML
# Committare le modifiche
git commit -m "Restructure project assets"
```

### 2. Convenzioni di Naming
```bash
# Rinominare seguendo convenzioni
git mv HomePage.js home-page.js
git mv UserProfile.css user-profile.css
git mv CONSTANTS.js constants.js

git commit -m "Apply consistent naming conventions"
```

### 3. Organizzazione per Componenti
```bash
# Organizzare file per componenti
mkdir -p components/header
git mv header.js components/header/
git mv header.css components/header/
git mv header.html components/header/

git commit -m "Organize header component files"
```

### 4. Migrazioni di Architettura
```bash
# Spostare da architettura MVC a modular
git mv models/ src/data/
git mv views/ src/components/
git mv controllers/ src/services/

git commit -m "Migrate to modular architecture"
```

## Pattern di Rinominazione Comuni

### Batch Rename con Script
```bash
#!/bin/bash
# Script per rinominare file in batch

for file in *.component.js; do
    new_name="${file%.component.js}.js"
    git mv "$file" "components/$new_name"
done
```

### Rinominazione con Pattern
```bash
# Rinominare tutti i file seguendo pattern
for file in test_*.py; do
    new_name="${file/test_/}"
    git mv "$file" "tests/$new_name"
done
```

## Errori Comuni e Soluzioni

### ❌ Problema: File rinominato non riconosciuto
```bash
# Git non riconosce la rinominazione
mv file.txt nuovo.txt
git add nuovo.txt
git status  # Mostra nuovo file, non rinominazione
```

**✅ Soluzione:**
```bash
# Usare git mv invece di mv
git mv file.txt nuovo.txt

# O aggiungere esplicitamente la rimozione
git rm file.txt
git add nuovo.txt
```

### ❌ Problema: Conflitto case-sensitivity
```bash
# Su macOS/Windows
git mv readme.txt README.txt  # Potrebbe non funzionare
```

**✅ Soluzione:**
```bash
# Rinominazione in due passi
git mv readme.txt temp.txt
git mv temp.txt README.txt
```

### ❌ Problema: Perdita della storia
```bash
# Storia del file interrotta dopo rinominazione
git log file.txt  # Non mostra storia completa
```

**✅ Soluzione:**
```bash
# Usare --follow per seguire rinominazioni
git log --follow file.txt

# O mostrare tutte le rinominazioni
git log --stat --follow file.txt
```

### ❌ Problema: Directory con file non tracciati
```bash
git mv directory/ new-location/  # Errore se ci sono file untracked
```

**✅ Soluzione:**
```bash
# Prima aggiungere tutti i file
git add directory/
git mv directory/ new-location/

# O spostare solo file tracciati
git mv directory/*.tracked new-location/
```

## Best Practices

### ✅ Consigli per Rinominazioni Efficaci

1. **Usa sempre `git mv`**
   ```bash
   # Corretto
   git mv old.txt new.txt
   
   # Evita operazioni manuali quando possibile
   ```

2. **Pianifica le ristrutturazioni**
   ```bash
   # Fai un commit prima di ristrutturare
   git commit -m "Save current state before restructuring"
   
   # Poi procedi con le rinominazioni
   git mv file1.txt new-location/file1.txt
   git mv file2.txt new-location/file2.txt
   git commit -m "Restructure file organization"
   ```

3. **Mantieni la storia**
   ```bash
   # Usa --follow nei log
   git log --follow --stat file.txt
   
   # Configura Git per rilevare meglio le rinominazioni
   git config diff.renames true
   ```

4. **Testa prima in branch separato**
   ```bash
   # Crea branch per ristrutturazione
   git checkout -b restructure
   
   # Fai tutte le rinominazioni
   git mv old-structure/ new-structure/
   
   # Testa che tutto funzioni
   # Poi merge nel branch principale
   ```

## Scenari di Rinominazione Complessi

### Scenario 1: Refactoring Completo
```bash
# Ristrutturazione completa di un progetto
git mv src/components/old-name.js src/components/feature/new-name.js
git mv src/styles/old-name.css src/components/feature/new-name.css
git mv tests/old-name.test.js tests/feature/new-name.test.js

# Aggiornare import nei file
# Committare tutto insieme
git commit -m "Refactor: reorganize feature components"
```

### Scenario 2: Migrazione Framework
```bash
# Da Vue 2 a Vue 3 - rinominare file di configurazione
git mv vue.config.js vite.config.js
git mv .babelrc babel.config.js
git mv src/main.js src/main.ts

git commit -m "Migrate configuration files to Vue 3"
```

## Quiz di Autovalutazione

### Domanda 1
Quale comando rinomina un file mantenendo la storia?
- a) `mv old.txt new.txt`
- b) `git mv old.txt new.txt` ✅
- c) `git rename old.txt new.txt`
- d) `git move old.txt new.txt`

### Domanda 2
Come vedere la storia completa di un file rinominato?
- a) `git log file.txt`
- b) `git log --follow file.txt` ✅
- c) `git history file.txt`
- d) `git trace file.txt`

### Domanda 3
Quale soglia di similarità usa Git di default per rilevare rinominazioni?
- a) 25%
- b) 50% ✅
- c) 75%
- d) 100%

### Domanda 4
Come risolvere problemi di case-sensitivity su macOS?
- a) Usare git mv direttamente
- b) Rinominare in due passi ✅
- c) Cambiare file system
- d) Non è possibile

### Domanda 5
Quale opzione mostra le rinominazioni nei diff?
- a) `git diff --renames`
- b) `git diff --find-renames` ✅
- c) `git diff --show-renames`
- d) `git diff --track-renames`

## Esercizi Pratici

### Esercizio 1: Rinominazione Base
1. Crea un file `test.txt`
2. Rinominalo in `example.txt` usando git mv
3. Verifica che Git riconosca la rinominazione
4. Controlla la storia con `git log --follow`

### Esercizio 2: Ristrutturazione Directory
1. Crea struttura: `app/main.js`, `app/style.css`
2. Sposta tutto in `src/` mantenendo la struttura
3. Verifica che la storia sia preservata
4. Fai commit delle modifiche

### Esercizio 3: Refactoring Complesso
1. Crea progetto con file in directory diverse
2. Riorganizza seguendo nuova architettura
3. Aggiorna tutti i riferimenti interni
4. Verifica che tutto funzioni correttamente

## Navigazione del Corso
- [📑 Indice](../../README.md)
- [⬅️ Tracciamento File e Directory](./01-tracciamento-file.md)
- [➡️ Eliminazione File e Directory](./03-eliminazione-file.md)
