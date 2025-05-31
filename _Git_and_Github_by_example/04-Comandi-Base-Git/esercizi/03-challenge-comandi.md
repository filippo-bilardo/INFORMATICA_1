# Esercizio 03: Challenge Comandi Git - Test delle Competenze

## 🎯 Obiettivi della Challenge
- Testare la padronanza dei comandi Git fondamentali
- Risolvere scenari problematici realistici
- Dimostrare comprensione delle tre aree Git
- Applicare best practices in situazioni complesse

## ⏱️ Modalità Challenge
- **Tempo limite**: 90 minuti
- **Modalità**: Individuale
- **Valutazione**: Auto-valutazione con checklist
- **Prerequisiti**: Completamento esercizi 01 e 02

## 🎮 Struttura della Challenge

### Livello 1: Diagnostica Veloce (15 minuti)
### Livello 2: Correzione Errori (25 minuti)  
### Livello 3: Workflow Complesso (30 minuti)
### Livello 4: Emergenza Repository (20 minuti)

---

## 🚀 LIVELLO 1: Diagnostica Veloce

### Scenario 1.1: Repository Misterioso
Ti è stato dato accesso a un repository esistente ma non sai cosa contiene.

**Setup:**
```bash
mkdir git-challenge
cd git-challenge
git init
echo "Progetto misterioso" > README.md
echo "function hello() { console.log('Hello!'); }" > app.js
echo "body { margin: 0; }" > style.css
mkdir docs
echo "# Documentazione" > docs/guide.md
git add .
git commit -m "Initial commit"
echo "Modifica non committata" >> README.md
echo "File temporaneo" > temp.txt
```

**Missioni (5 minuti ciascuna):**

**1.1.1 - Ispettore del Repository**
Usa SOLO comandi Git per rispondere:
- Quanti file sono tracciati?
- Quanti file sono modificati ma non in staging?
- Quanti file sono untracked?
- Qual è l'ultimo messaggio di commit?

**Comando di verifica:**
```bash
# Scrivi qui i comandi usati e le risposte trovate
```

**1.1.2 - Detective delle Modifiche**
- Mostra esattamente cosa è cambiato nel file README.md
- Identifica tutti i file nella working directory
- Determina lo stato di ogni file nelle tre aree Git

**1.1.3 - Cronologia Explorer**
- Visualizza la cronologia in formato oneline
- Mostra i dettagli dell'ultimo commit incluso le statistiche
- Identifica l'hash del commit corrente

### ✅ Verifica Livello 1
```bash
# Controllo risposte
git status --porcelain | wc -l  # Conta file modificati
git ls-files | wc -l            # Conta file tracciati
git log --oneline -1            # Ultimo commit
```

---

## 🔧 LIVELLO 2: Correzione Errori

### Scenario 2.1: Staging Disordinato
Hai file in staging che non dovrebbero esserci e file non in staging che dovrebbero esserci.

**Setup problematico:**
```bash
echo "Feature importante" > feature.js
echo "Test temporaneo" > test_temp.js
echo "Configurazione" > config.json
echo "Log di debug" > debug.log
echo "Cache file" > cache.tmp

# Aggiungi tutto per errore
git add .
```

**Missione 2.1**: Correggere la situazione (10 minuti)
- Rimuovi da staging: `test_temp.js`, `debug.log`, `cache.tmp`
- Mantieni in staging: `feature.js`, `config.json`
- Non eliminare nessun file fisicamente
- Committa solo i file corretti con messaggio appropriato

### Scenario 2.2: Commit Sbagliato
Hai appena fatto un commit ma hai dimenticato un file importante.

**Setup:**
```bash
echo "export default class Utils {}" > utils.js
git add utils.js
git commit -m "Add utility class"

# Ti accorgi di aver dimenticato i test
echo "describe('Utils', () => { test('should work', () => {}) });" > utils.test.js
```

**Missione 2.2**: Aggiusta il commit (8 minuti)
- Aggiungi il file test al commit precedente
- Il messaggio finale deve essere: "Add utility class with tests"
- Non creare un nuovo commit
- Verifica che la cronologia sia pulita

### Scenario 2.3: File Rinominato Problematico
Hai rinominato un file manualmente e Git non se n'è accorto.

**Setup:**
```bash
echo "const API_URL = 'https://api.example.com';" > config.js
git add config.js
git commit -m "Add configuration"

# Rinomini manualmente
mv config.js settings.js
echo "const API_URL = 'https://api-v2.example.com';" > settings.js
```

**Missione 2.3**: Gestisci la rinominazione (7 minuti)
- Fai in modo che Git riconosca la rinominazione
- Applica anche la modifica del contenuto
- Committa con messaggio appropriato
- Verifica con `git log --follow` che la cronologia sia mantenuta

### ✅ Verifica Livello 2
```bash
# Verifica staging pulito
git status

# Verifica cronologia corretta
git log --oneline -5

# Verifica tracking rinominazione
git log --follow settings.js
```

---

## 🌟 LIVELLO 3: Workflow Complesso

### Scenario 3.1: Progetto Multi-Componente
Stai sviluppando un'applicazione web con diversi componenti che devono essere committati separatamente.

**Setup:**
```bash
# Frontend
mkdir frontend
echo "<html><body><h1>App</h1></body></html>" > frontend/index.html
echo "body { font-family: Arial; }" > frontend/style.css
echo "console.log('App loaded');" > frontend/app.js

# Backend  
mkdir backend
echo "from flask import Flask; app = Flask(__name__)" > backend/server.py
echo "def get_users(): return []" > backend/users.py
echo "import unittest" > backend/test_users.py

# Database
mkdir database
echo "CREATE TABLE users (id INT PRIMARY KEY);" > database/schema.sql
echo "INSERT INTO users VALUES (1);" > database/seed.sql

# Documentazione
echo "# API Documentation" > API.md
echo "# User Guide" > USER_GUIDE.md

# File di configurazione
echo "DEBUG=True" > .env
echo "node_modules/" > .gitignore
```

**Missione 3.1**: Commit Strategici (15 minuti)
Crea esattamente 4 commit nell'ordine specifico:

1. **Commit 1**: Solo la struttura frontend (HTML, CSS, JS) 
   - Messaggio: "feat: implement frontend user interface"

2. **Commit 2**: Solo il backend API
   - Messaggio: "feat: add backend API endpoints"

3. **Commit 3**: Solo database schema e setup
   - Messaggio: "feat: setup database structure"

4. **Commit 4**: Documentazione e configurazione
   - Messaggio: "docs: add API documentation and configuration"

**Vincoli:**
- Usa staging selettivo per ogni commit
- Non usare `git add .` mai
- Verifica ogni commit prima di procedere al successivo

### Scenario 3.2: Debug della Cronologia
Nel progetto precedente qualcosa non funziona. Devi investigare la cronologia per capire quando è stato introdotto un problema.

**Setup del problema:**
```bash
# Simula modifiche nel tempo
echo "console.log('Version 1.0');" >> frontend/app.js
git add frontend/app.js
git commit -m "Update app version to 1.0"

echo "console.log('Version 1.1 - Added bug!');" >> frontend/app.js  
git add frontend/app.js
git commit -m "Update app version to 1.1"

echo "console.log('Version 1.2');" >> frontend/app.js
git add frontend/app.js
git commit -m "Update app version to 1.2"
```

**Missione 3.2**: Investigazione (15 minuti)
1. Identifica in quale commit è stata aggiunta la parola "bug"
2. Mostra le differenze esatte tra la versione 1.0 e 1.2
3. Visualizza la cronologia in formato grafico con decorazioni
4. Trova l'hash completo del commit che ha introdotto il bug
5. Mostra solo le righe modificate nel commit problematico

### ✅ Verifica Livello 3
```bash
# Verifica numero commit (dovrebbero essere 7 totali)
git rev-list --count HEAD

# Verifica struttura commit
git log --oneline --grep="feat:"
git log --oneline --grep="docs:"

# Verifica investigazione
git log --grep="bug" --oneline
```

---

## 🚨 LIVELLO 4: Emergenza Repository

### Scenario 4.1: Disastro Recovery
Il tuo collega ha fatto un pasticcio nel repository e ti chiede aiuto urgentemente.

**Setup del disastro:**
```bash
# Situazione caotica
echo "File importante modificato male" > important.txt
echo "File da non committare" > secret.key
echo "Log debug enorme" > debug.log
echo "Cache temporanea" > .cache
echo "Backup corrotto" > backup.bak

# Tutto in staging per errore
git add .

# Modifiche aggiuntive non in staging
echo "Modifica non salvata importante" >> important.txt
echo "// TODO: implementare feature critica" >> frontend/app.js

# File eliminato per errore
rm frontend/style.css
```

**Missione 4.1**: Salvataggio Emergenza (10 minuti)
**Obiettivi:**
1. Rimuovi da staging tutti i file eccetto `important.txt`
2. Recupera il file `frontend/style.css` eliminato per errore
3. Committa solo `important.txt` con messaggio "fix: recover important configuration"
4. Salva le modifiche non committate di `frontend/app.js` senza commitare
5. Pulisci tutti i file temporanei (secret.key, debug.log, .cache, backup.bak)

### Scenario 4.2: Commit Message Disaster
Il repository ha una cronologia con messaggi di commit terribili che devi interpretare.

**Setup messaggi disastrosi:**
```bash
git commit --allow-empty -m "asdf"
git commit --allow-empty -m "fix stuff"  
git commit --allow-empty -m "work"
git commit --allow-empty -m "blah blah blah"
git commit --allow-empty -m "final version maybe"
```

**Missione 4.2**: Interpretazione e Pulizia (10 minuti)
1. Elenca tutti i commit degli ultimi 5 messaggi
2. Identifica quale potrebbe essere stato l'ultimo commit di "lavoro reale"
3. Mostra la differenza tra HEAD e HEAD~5
4. Proponi come dovevano essere scritti i messaggi di commit seguendo convention

### ✅ Verifica Livello 4
```bash
# Verifica pulizia
git status
ls -la | grep -E "\.(key|log|cache|bak)$" | wc -l  # Dovrebbe essere 0

# Verifica recovery
test -f frontend/style.css && echo "File recuperato!" || echo "File ancora mancante!"

# Verifica ultimo commit
git log -1 --pretty=format:"%s"
```

---

## 🏆 VALUTAZIONE FINALE

### Scoring System
| Livello | Punti Massimi | Criteri |
|---------|---------------|---------|
| Livello 1 | 30 punti | Diagnostica accurata (10 punti per scenario) |
| Livello 2 | 30 punti | Correzione completa (10 punti per scenario) |
| Livello 3 | 25 punti | Workflow professionale (15 + 10 punti) |
| Livello 4 | 15 punti | Gestione emergenze (7.5 punti per scenario) |
| **TOTALE** | **100 punti** | |

### Grading Scale
- **90-100 punti**: 🥇 Git Master - Eccellente padronanza
- **75-89 punti**: 🥈 Git Expert - Buona competenza
- **60-74 punti**: 🥉 Git Practitioner - Competenza base
- **40-59 punti**: 📚 Git Learner - Necessita studio aggiuntivo  
- **< 40 punti**: 🔄 Git Beginner - Ripetere esercizi precedenti

### Checklist Auto-Valutazione

#### Competenze Tecniche
- [ ] So utilizzare `git status` per diagnosticare lo stato del repository
- [ ] Uso correttamente `git add` per staging selettivo
- [ ] Scrivo messaggi di commit chiari e informativi
- [ ] Uso `git diff` per analizzare le modifiche
- [ ] Gestisco correttamente file rinominati e eliminati
- [ ] Uso `git log` con opzioni avanzate per investigare la cronologia
- [ ] Applico correttamente `git commit --amend` per correzioni
- [ ] Gestisco situazioni di emergenza con calma e metodo

#### Competenze Professionali
- [ ] Seguo un workflow Git logico e strutturato
- [ ] Mantengo la cronologia del repository pulita
- [ ] Uso staging strategico per commit atomici
- [ ] Gestisco file temporanei e sensibili correttamente
- [ ] Documento le modifiche con commit messages descrittivi
- [ ] Risolvo problemi complessi con approccio sistematico

## 🎯 Sfide Bonus

### Bonus 1: Speed Run (5 punti extra)
Ripeti l'intera challenge in 60 minuti mantenendo la stessa qualità.

### Bonus 2: Scripting Challenge (10 punti extra)
Crea uno script bash che automatizzi la verifica di una delle missioni.

### Bonus 3: Documentation Master (5 punti extra)
Crea un documento che spiega ogni comando utilizzato e perché.

## 📚 Risorse per il Recovery

Se hai difficoltà con qualche livello:

### Per Livello 1-2:
- Ripassa: Guide 01-03 del modulo
- Esercizio: Ripeti esercizio 01 "Workflow Base"

### Per Livello 3:
- Ripassa: Guide 04-06 del modulo  
- Esercizio: Completa l'esercizio 02 "Portfolio"

### Per Livello 4:
- Ripassa: Tutte le guide del modulo
- Studia: Modulo 11 "Annullare Modifiche"

## 🔄 Ripetizione Challenge

Questa challenge può essere ripetuta con variazioni:
- Diversi linguaggi di programmazione
- Progetti di team simulation
- Scenari di repository legacy
- Integrazione con GitHub workflow

---

**Tempo totale**: 90 minuti  
**Difficoltà**: Avanzato  
**Tipo**: Challenge competitiva  
**Prerequisiti**: Completamento moduli 01-04
