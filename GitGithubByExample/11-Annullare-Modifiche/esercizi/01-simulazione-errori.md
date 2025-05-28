# Esercizio: Simulazione e Gestione Errori Git

## 📚 Obiettivo dell'Esercizio

Imparare a gestire errori comuni in Git attraverso simulazioni pratiche e sicure. Questo esercizio ti guiderà attraverso la creazione controllata di problemi e la loro risoluzione.

## 🎯 Competenze Sviluppate

- Riconoscere situazioni problematiche
- Applicare tecniche di recovery appropriate
- Utilizzare reflog e fsck per diagnosi
- Gestire situazioni di emergenza con calma
- Documentare soluzioni per futuri riferimenti

## ⚙️ Setup Iniziale

### Fase 1: Creazione Repository di Test

```bash
# Creare directory di lavoro
mkdir git-error-simulation
cd git-error-simulation

# Inizializzare repository
git init

# Configurazione per l'esercizio
git config user.name "Test User"
git config user.email "test@example.com"

# Creare struttura base del progetto
mkdir src tests docs
echo "# Git Error Simulation Project" > README.md
echo "console.log('Hello, Git!');" > src/main.js
echo "/* CSS styles */" > src/style.css
echo "<!DOCTYPE html><html><head><title>Test</title></head><body></body></html>" > src/index.html
echo "# Test Documentation" > docs/guide.md
echo "test('should work', () => {});" > tests/main.test.js

# Primo commit
git add .
git commit -m "Initial project setup"

# Creare alcuni branch per l'esercizio
git checkout -b feature/authentication
echo "function login() { return true; }" >> src/main.js
git add .
git commit -m "Add basic authentication"

git checkout -b feature/ui-improvements  
echo "body { margin: 0; padding: 20px; }" >> src/style.css
git add .
git commit -m "Improve UI styling"

git checkout main
echo "Updated main README" >> README.md
git add .
git commit -m "Update main documentation"

# Creare tag per riferimento
git tag v1.0.0

echo "✅ Setup completato! Repository pronto per simulazioni."
```

### Fase 2: Verifica Setup
```bash
# Verificare la struttura creata
git log --oneline --all --graph
git branch -a
git tag
git status

# Dovrebbe mostrare:
# - 3 branch (main, feature/authentication, feature/ui-improvements)
# - 4 commit totali
# - 1 tag (v1.0.0)
# - Working directory pulito
```

## 🎮 Esercizi di Simulazione

### Esercizio 1: "Reset Accidentale"

#### Situazione da Simulare
Hai fatto reset accidentale perdendo commit importanti.

```bash
# Passaggio 1: Creare nuovo lavoro
git checkout main
echo "Important new feature code" > src/feature.js
echo "Critical bug fix" >> src/main.js
git add .
git commit -m "Important work - DO NOT LOSE"

# Passaggio 2: Simulare il disastro
echo "Simulating accidental reset..."
git reset --hard HEAD~2  # ❌ Perdendo commit importante!

# Passaggio 3: Verificare il danno
git log --oneline
# Il commit "Important work" è sparito!
```

#### 🎯 Tuo Compito
1. **Diagnosi**: Usa `git reflog` per trovare il commit perso
2. **Recovery**: Recupera il commit usando reflog
3. **Verifica**: Conferma che tutto il lavoro è tornato
4. **Documentazione**: Scrivi cosa hai imparato

#### 💡 Suggerimenti
- Usa `git reflog` per vedere la cronologia completa
- Cerca il commit con messaggio "Important work"
- Usa `git reset --hard SHA1` per recuperare
- Verifica con `git log` e `git status`

#### ✅ Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Diagnosi
git reflog
# Cerca: SHA1 HEAD@{1}: commit: Important work - DO NOT LOSE

# 2. Recovery
git reset --hard HEAD@{1}
# oppure git reset --hard SHA1-DEL-COMMIT

# 3. Verifica
git log --oneline
git status
```
</details>

### Esercizio 2: "Branch Cancellato per Errore"

#### Situazione da Simulare
```bash
# Passaggio 1: Creare branch con lavoro importante
git checkout -b critical-feature
echo "Critical feature implementation" > src/critical.js
echo "Important tests" > tests/critical.test.js
git add .
git commit -m "Implement critical feature"
git commit --allow-empty -m "Add documentation for critical feature"

# Passaggio 2: Tornare a main
git checkout main

# Passaggio 3: Simulare eliminazione accidentale
git branch -D critical-feature  # ❌ Branch eliminato!

# Passaggio 4: Verificare danno
git branch
# critical-feature non c'è più!
```

#### 🎯 Tuo Compito
1. **Trova il commit**: Usa reflog per trovare l'ultimo commit del branch
2. **Ricreare branch**: Ricostruisci il branch dal commit trovato
3. **Verifica contenuto**: Controlla che tutti i file siano presenti
4. **Prevenzione**: Imposta alias per rendere cancellazione più sicura

#### ✅ Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Trova commit del branch
git reflog | grep "critical-feature"
# oppure git reflog --all

# 2. Ricreare branch
git branch critical-feature SHA1-TROVATO
# oppure git checkout -b critical-feature SHA1-TROVATO

# 3. Verifica
git checkout critical-feature
ls src/  # Deve contenere critical.js
git log --oneline

# 4. Prevenzione
git config --global alias.safe-delete '!git checkout main && git branch -d'
```
</details>

### Esercizio 3: "File Importanti Eliminati"

#### Situazione da Simulare
```bash
# Passaggio 1: Simulare sviluppo normale
git checkout main
echo "Database configuration" > config/database.yml
echo "API endpoints" > config/api.yml
mkdir config
mv config/database.yml config/
mv config/api.yml config/
git add config/
git commit -m "Add configuration files"

# Passaggio 2: Continuare sviluppo
echo "New feature" > src/new-feature.js
git add .
git commit -m "Add new feature"

# Passaggio 3: Simulare eliminazione accidentale
git rm config/database.yml
git commit -m "Clean up old files"  # ❌ File importante eliminato!

# Passaggio 4: Rendersi conto dell'errore
echo "Oh no! I need that database config file!"
```

#### 🎯 Tuo Compito
1. **Trova quando esisteva**: Usa `git log` per trovare quando il file esisteva
2. **Recupera file**: Recupera il file da un commit precedente
3. **Ripristina**: Aggiungi il file recuperato e committa
4. **Impara**: Configura .gitignore per prevenire eliminazioni accidentali

#### ✅ Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Trova quando il file esisteva
git log --oneline --follow -- config/database.yml

# 2. Recupera dal commit precedente  
git checkout HEAD~1 -- config/database.yml

# 3. Ripristina
git add config/database.yml
git commit -m "Restore database configuration file"

# 4. Prevenzione
echo "config/*.yml" >> .gitignore-important
echo "Usa .gitignore-important come riferimento"
```
</details>

### Esercizio 4: "Merge Conflict Disastroso"

#### Situazione da Simulare
```bash
# Passaggio 1: Creare situazione di conflitto
git checkout feature/authentication
echo "function login(user, pass) { /* auth logic */ }" > src/auth.js
git add .
git commit -m "Implement authentication logic"

git checkout main
echo "function login(email, password) { /* different logic */ }" > src/auth.js
git add .
git commit -m "Add login with email"

# Passaggio 2: Tentare merge con conflitti
git merge feature/authentication
# Automatic merge failed; fix conflicts and then commit the result.

# Passaggio 3: Risolvere male i conflitti
# Editare src/auth.js manualmente e introdurre errori di sintassi
echo "function login(user, pass, email) { broken syntax here" > src/auth.js
git add .
git commit -m "Resolve merge conflicts"  # ❌ Risoluzione sbagliata!

# Passaggio 4: Accorgersi del problema
echo "The code is now broken due to bad conflict resolution!"
```

#### 🎯 Tuo Compito
1. **Analizza situazione**: Usa `git log` per capire cosa è successo
2. **Estrategia recovery**: Scegli tra revert del merge o reset
3. **Esegui correzione**: Applica la strategia scelta
4. **Rifare correttamente**: Ripeti il merge risolvendo correttamente i conflitti

#### ✅ Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Analizza
git log --oneline --graph -5

# 2. Revert del merge (opzione sicura)
git revert -m 1 HEAD

# 3. Rifare merge correttamente
git merge feature/authentication
# Risolvere i conflitti correttamente in src/auth.js
git add .
git commit -m "Properly resolve merge conflicts"

# Alternativa con reset (se non pushato):
# git reset --hard HEAD~1
# git merge feature/authentication
```
</details>

## 🔧 Esercizi di Approfondimento

### Esercizio 5: "Repository Corruption Simulation"

#### Setup Sicuro per Corruzione
```bash
# Creare backup prima della simulazione
cp -r .git .git-backup

# Simulare corruzione oggetti (ATTENZIONE: solo per test!)
# Trova un oggetto e corrompi il contenuto
OBJECT=$(find .git/objects -name "*.tmp" -o -name "*" | head -1)
echo "corrupted" > "$OBJECT"

# Testare diagnosi
git fsck --full
```

#### 🎯 Tuo Compito
1. Diagnosticare il problema con `git fsck`
2. Tentare recovery automatico con `git gc`
3. Recuperare da backup se necessario
4. Documentare il processo di recovery

### Esercizio 6: "Working Directory Disaster"

#### Situazione
```bash
# Simulare perdita working directory
rm -rf src/
rm README.md

# Ma .git è intatto
ls -la  # Solo .git rimane
```

#### 🎯 Tuo Compito
1. Ripristinare tutti i file dalla storia Git
2. Verificare che tutto sia tornato normale
3. Aggiungere modifiche che hai perso
4. Creare strategia di backup per il futuro

## 📝 Journal di Apprendimento

Durante ogni esercizio, mantieni un journal con:

### Template di Entry
```markdown
## Esercizio [N]: [Nome]
**Data**: [Data/Ora]
**Situazione**: [Descrizione del problema]
**Sintomi osservati**: [Cosa hai notato di sbagliato]
**Comandi utilizzati per diagnosi**: 
- comando1
- comando2
**Soluzione applicata**: [Strategia usata]
**Comandi di recovery**: 
- step1
- step2
**Lezioni apprese**: [Cosa hai imparato]
**Prevenzione futura**: [Come evitarlo]
```

## 🎯 Sfide Bonus

### Sfida 1: Recovery Speed
- Simula 5 problemi diversi
- Cronometra quanto tempo impieghi per risolverli
- Obiettivo: sotto 2 minuti per problema semplice

### Sfida 2: Blind Recovery
- Chiedi a un collega di creare un problema
- Risolvi senza sapere cosa è stato fatto
- Documenta il processo di investigazione

### Sfida 3: Script di Automazione
```bash
# Crea script che automatizza recovery comuni
#!/bin/bash
# auto-recovery.sh

case "$1" in
    "reset-accident")
        git reflog | head -5
        echo "Select commit to recover to:"
        ;;
    "deleted-branch")
        git reflog --all | grep "checkout.*moving from"
        ;;
    "deleted-file")
        echo "Enter filename:"
        read filename
        git log --oneline --follow -- "$filename"
        ;;
esac
```

## ✅ Checklist di Completamento

- [ ] Setup repository completato
- [ ] Esercizio 1 (Reset) completato e documentato
- [ ] Esercizio 2 (Branch) completato e documentato  
- [ ] Esercizio 3 (File) completato e documentato
- [ ] Esercizio 4 (Merge) completato e documentato
- [ ] Journal mantenuto per ogni esercizio
- [ ] Almeno 1 sfida bonus tentata
- [ ] Script di prevenzione configurati
- [ ] Lezioni apprese documentate

## 🎖️ Certificazione di Competenza

Al completamento, dovresti essere capace di:
- Diagnosticare rapidamente problemi Git comuni
- Utilizzare reflog efficacemente per recovery
- Scegliere la strategia di recovery appropriata
- Prevenire problemi futuri con configurazioni e workflow
- Mantenere calma durante emergenze Git

**Prossimo passo**: Esercizio 2 - "Recupero Dati Complessi"
