# Esercizi: Creare e Gestire Branch

## 🎯 Obiettivi
Al completamento di questi esercizi, sarai in grado di:
- Creare branch con nomi appropriati
- Navigare tra branch diversi
- Gestire il ciclo di vita dei branch
- Applicare best practices per naming e workflow

## 📋 Prerequisiti
- Git installato e configurato
- Conoscenza base di comandi Git (add, commit)
- Familiarità con il terminale

---

## 🏃‍♂️ Esercizio 1: Creazione Branch Base

### Obiettivo
Impara a creare branch con diversi metodi.

### Istruzioni
1. Crea un nuovo repository locale chiamato `branch-exercise-1`
2. Fai un commit iniziale con un file README.md
3. Crea i seguenti branch usando metodi diversi:
   - `feature-homepage` usando `git branch`
   - `feature-login` usando `git checkout -b`
   - `feature-dashboard` usando `git switch -c` (se disponibile)

### Verifica
```bash
git branch
# Dovresti vedere:
#   feature-dashboard
#   feature-homepage
#   feature-login
# * main
```

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Creazione repository
mkdir branch-exercise-1
cd branch-exercise-1
git init
git config user.name "Tu Nome"
git config user.email "tua@email.com"

# 2. Commit iniziale
echo "# Branch Exercise 1" > README.md
git add README.md
git commit -m "Initial commit"

# 3. Creazione branch
git branch feature-homepage
git checkout -b feature-login
git switch main
git switch -c feature-dashboard  # o git checkout -b se switch non disponibile

# Verifica
git branch
```
</details>

---

## 🏃‍♂️ Esercizio 2: Naming Conventions

### Obiettivo
Pratica le convenzioni di naming per i branch.

### Istruzioni
Crea branch con nomi appropriati per i seguenti scenari:
1. Una feature per aggiungere un sistema di commenti
2. Un bug fix per errore di validazione email
3. Un hotfix per una vulnerabilità di sicurezza critica
4. Un branch di release per la versione 2.1.0
5. Un branch personale per sperimentare con una nuova UI

### Criteri di Valutazione
- Usa prefissi appropriati
- Nomi descrittivi e chiari
- Usa trattini invece di spazi
- Lunghezza ragionevole

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Feature per commenti
git switch -c feature/comment-system

# 2. Bug fix validazione email
git switch -c bugfix/email-validation-error

# 3. Hotfix sicurezza
git switch -c hotfix/security-vulnerability-patch

# 4. Release branch
git switch -c release/v2.1.0

# 5. Branch personale sperimentale
git switch -c personal/experimental-ui-redesign
```
</details>

---

## 🏃‍♂️ Esercizio 3: Workflow Feature Branch

### Obiettivo
Simula un workflow completo di feature branch.

### Scenario
Stai sviluppando una feature "user profile" per un'applicazione web.

### Istruzioni
1. Parti dal branch `main`
2. Crea un branch `feature/user-profile`
3. Aggiungi i seguenti file:
   - `profile.html` con contenuto base
   - `profile.css` con stili base
   - `profile.js` con funzionalità base
4. Fai commit incrementali per ogni file
5. Torna a `main`
6. Simula che altri hanno lavorato aggiungendo un file `other-work.txt` su main
7. Merge la tua feature
8. Elimina il branch feature

### Verifica
- La feature deve essere integrata in main
- I file della feature devono essere presenti
- Il branch feature deve essere eliminato
- La storia deve essere pulita

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Parte da main
git switch main

# 2. Crea feature branch
git switch -c feature/user-profile

# 3-4. Aggiungi file con commit incrementali
echo "<div>User Profile Page</div>" > profile.html
git add profile.html
git commit -m "feat: add basic profile HTML structure"

echo ".profile { margin: 20px; }" > profile.css
git add profile.css
git commit -m "feat: add basic profile styles"

echo "function loadProfile() { console.log('Loading...'); }" > profile.js
git add profile.js
git commit -m "feat: add basic profile functionality"

# 5. Torna a main
git switch main

# 6. Simula altro lavoro
echo "Other team work" > other-work.txt
git add other-work.txt
git commit -m "feat: add other team contributions"

# 7. Merge feature
git merge feature/user-profile

# 8. Elimina branch
git branch -d feature/user-profile

# Verifica
git log --oneline -5
git branch
ls -la
```
</details>

---

## 🏃‍♂️ Esercizio 4: Gestione Branch Multipli

### Obiettivo
Gestisci multiple feature in sviluppo simultaneo.

### Scenario
Stai lavorando su tre feature contemporaneamente e devi passare tra di esse.

### Istruzioni
1. Crea tre branch:
   - `feature/shopping-cart`
   - `feature/user-authentication`
   - `feature/payment-system`
2. Per ogni branch:
   - Aggiungi file specifici
   - Fai almeno 2 commit
3. Naviga tra i branch e verifica che i file cambino
4. Completa una feature (shopping-cart) e mergela
5. Continua lo sviluppo delle altre due
6. Lista i branch completed vs in-progress

### Comandi Utili
```bash
git branch --merged      # branch mergeati
git branch --no-merged   # branch in sviluppo
git switch -             # torna al branch precedente
```

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Crea i branch
git switch main
git switch -c feature/shopping-cart
git switch main
git switch -c feature/user-authentication
git switch main
git switch -c feature/payment-system

# 2. Sviluppa shopping-cart
git switch feature/shopping-cart
echo "class ShoppingCart {}" > cart.js
git add cart.js
git commit -m "feat: add shopping cart class"

echo "cart { border: 1px solid #ccc; }" > cart.css
git add cart.css
git commit -m "feat: add shopping cart styles"

# Sviluppa user-authentication
git switch feature/user-authentication
echo "class Auth {}" > auth.js
git add auth.js
git commit -m "feat: add authentication class"

echo ".login-form { width: 300px; }" > auth.css
git add auth.css
git commit -m "feat: add authentication styles"

# Sviluppa payment-system
git switch feature/payment-system
echo "class Payment {}" > payment.js
git add payment.js
git commit -m "feat: add payment class"

echo ".payment-form { padding: 20px; }" > payment.css
git add payment.css
git commit -m "feat: add payment styles"

# 3. Verifica navigazione
git switch feature/shopping-cart
ls *.js *.css  # solo cart files

git switch feature/user-authentication
ls *.js *.css  # solo auth files

# 4. Completa shopping-cart
git switch main
git merge feature/shopping-cart
git branch -d feature/shopping-cart

# 5. Verifica status
echo "Branch completati:"
git branch --merged

echo "Branch in sviluppo:"
git branch --no-merged
```
</details>

---

## 🏃‍♂️ Esercizio 5: Switch vs Checkout

### Obiettivo
Confronta e pratica l'uso di git switch vs git checkout.

### Istruzioni
1. Verifica quale versione di Git hai installata
2. Se hai Git 2.23+, pratica entrambi i metodi
3. Se hai Git < 2.23, usa solo checkout ma studia la sintassi switch
4. Crea uno script che dimostri le differenze

### Operazioni da Testare
- Creazione branch
- Cambio branch
- Gestione errori (branch inesistente)
- Ripristino file

### Template Script
```bash
#!/bin/bash
echo "Git version: $(git --version)"

# Test checkout approach
echo "=== CHECKOUT APPROACH ==="
git checkout -b test-checkout-branch
echo "Created with checkout"

# Test switch approach (se disponibile)
if git switch --help >/dev/null 2>&1; then
    echo "=== SWITCH APPROACH ==="
    git switch -c test-switch-branch
    echo "Created with switch"
fi

# Il tuo codice qui...
```

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
#!/bin/bash
echo "=== CONFRONTO SWITCH VS CHECKOUT ==="
echo "Git version: $(git --version)"

# Setup repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    git init switch-vs-checkout-test
    cd switch-vs-checkout-test
    echo "Initial file" > test.txt
    git add test.txt
    git commit -m "Initial commit"
fi

echo
echo "=== TEST CHECKOUT ==="
git checkout -b test-checkout
echo "Modified with checkout" >> test.txt
git add test.txt
git commit -m "Commit from checkout branch"

echo
echo "=== TEST SWITCH ==="
if git switch --help >/dev/null 2>&1; then
    git switch -c test-switch
    echo "Modified with switch" >> test.txt
    git add test.txt
    git commit -m "Commit from switch branch"
    
    echo
    echo "=== CONFRONTO NAVIGAZIONE ==="
    echo "Con checkout:"
    git checkout test-checkout
    echo "Branch attuale: $(git branch | grep '*' | cut -c3-)"
    
    echo "Con switch:"
    git switch test-switch
    echo "Branch attuale: $(git branch | grep '*' | cut -c3-)"
    
    echo
    echo "=== TEST ERRORI ==="
    echo "Checkout con branch inesistente:"
    git checkout nonexistent 2>&1 || echo "Errore gestito"
    
    echo "Switch con branch inesistente:"
    git switch nonexistent 2>&1 || echo "Errore gestito"
    
else
    echo "git switch non disponibile in questa versione"
    echo "Aggiorna a Git 2.23+ per usare switch"
fi

echo
echo "=== RIEPILOGO ==="
git branch
echo "Test completato!"
```
</details>

---

## 🧠 Esercizio 6: Pulizia Branch (Avanzato)

### Obiettivo
Impara a mantenere pulito il repository eliminando branch obsoleti.

### Scenario
Hai un repository con molti branch, alcuni mergeati e altri no. Devi fare pulizia.

### Setup Iniziale
```bash
# Esegui questo per creare lo scenario
git init cleanup-exercise
cd cleanup-exercise
echo "main file" > main.txt
git add main.txt
git commit -m "Initial commit"

# Crea vari branch con diversi stati
git checkout -b feature-completed-1
echo "completed feature 1" > feature1.txt
git add feature1.txt
git commit -m "Complete feature 1"
git checkout main
git merge feature-completed-1

git checkout -b feature-completed-2
echo "completed feature 2" > feature2.txt
git add feature2.txt
git commit -m "Complete feature 2"
git checkout main
git merge feature-completed-2

git checkout -b feature-in-progress
echo "work in progress" > wip.txt
git add wip.txt
git commit -m "WIP: feature in progress"

git checkout -b feature-experimental
echo "experimental work" > experimental.txt
git add experimental.txt
git commit -m "Experimental feature"

git checkout main
```

### Istruzioni
1. Identifica branch mergeati
2. Identifica branch non mergeati
3. Elimina branch mergeati in modo sicuro
4. Decidi cosa fare con branch non mergeati
5. Crea uno script di pulizia automatica

### Soluzione
<details>
<summary>Clicca per vedere la soluzione</summary>

```bash
# 1. Identifica branch mergeati
echo "Branch mergeati:"
git branch --merged main

# 2. Identifica branch non mergeati
echo "Branch NON mergeati:"
git branch --no-merged main

# 3. Elimina branch mergeati (escluso main)
echo "Eliminazione branch mergeati..."
git branch --merged main | grep -v "main" | xargs -r git branch -d

# 4. Gestisci branch non mergeati
echo "Branch non mergeati rimanenti:"
git branch --no-merged main

# Per feature-in-progress: mantieni
echo "Mantengo feature-in-progress (lavoro attivo)"

# Per feature-experimental: elimina se necessario
echo "Elimino feature-experimental (sperimento fallito)"
git branch -D feature-experimental

# 5. Script di pulizia automatica
cat > cleanup-branches.sh << 'EOF'
#!/bin/bash
echo "=== PULIZIA BRANCH AUTOMATICA ==="

echo "Branch prima della pulizia:"
git branch

echo
echo "Branch mergeati da eliminare:"
MERGED_BRANCHES=$(git branch --merged main | grep -v "main" | tr -d ' ')

if [ -n "$MERGED_BRANCHES" ]; then
    echo "$MERGED_BRANCHES"
    echo "Procedo con eliminazione? (y/n)"
    read -p "> " CONFIRM
    
    if [ "$CONFIRM" = "y" ]; then
        echo "$MERGED_BRANCHES" | xargs git branch -d
        echo "✅ Branch mergeati eliminati"
    else
        echo "❌ Eliminazione annullata"
    fi
else
    echo "Nessun branch mergeato da eliminare"
fi

echo
echo "Branch rimanenti:"
git branch

echo
echo "Branch non mergeati (richiedono attenzione manuale):"
git branch --no-merged main
EOF

chmod +x cleanup-branches.sh
echo "Script di pulizia creato: cleanup-branches.sh"
```
</details>

---

## 🎯 Progetto Finale: Sistema di Gestione Task

### Obiettivo
Applica tutte le competenze acquisite in un progetto realistico.

### Scenario
Stai sviluppando un sistema di gestione task. Devi implementare multiple feature usando un workflow professionale con branch.

### Requisiti
1. **Feature 1**: Sistema di autenticazione utenti
2. **Feature 2**: CRUD operazioni per task
3. **Feature 3**: Sistema di notifiche
4. **Hotfix**: Correzione bug critico
5. **Release**: Preparazione versione 1.0

### Struttura Progetto
```
task-manager/
├── src/
│   ├── auth/
│   ├── tasks/
│   ├── notifications/
│   └── utils/
├── tests/
├── docs/
└── README.md
```

### Workflow Richiesto
1. **Inizializzazione**: Setup repository e commit iniziale
2. **Feature Branch**: Una feature per volta
3. **Code Review**: Simula review prima del merge
4. **Integration**: Merge ordinato in main
5. **Hotfix**: Gestione emergenza
6. **Release**: Tag e documentazione

### Deliverable
- Repository Git completo
- Storia commit pulita
- Branch strategy documentata
- README con istruzioni

### Valutazione
- ✅ Naming conventions seguiti
- ✅ Workflow branch corretto
- ✅ Commit message significativi
- ✅ Merge strategy appropriata
- ✅ Cleanup branch completato

---

## 📝 Checklist Competenze

Al completamento degli esercizi, dovresti essere in grado di:

### Creazione Branch
- [ ] Creare branch con `git branch`
- [ ] Creare e cambiare con `git checkout -b`
- [ ] Creare e cambiare con `git switch -c`
- [ ] Creare branch da commit specifico

### Gestione Branch
- [ ] Listare branch locali e remoti
- [ ] Cambiare branch attivo
- [ ] Rinominare branch
- [ ] Eliminare branch locali

### Naming Conventions
- [ ] Usare prefissi appropriati (feature/, bugfix/, hotfix/)
- [ ] Creare nomi descrittivi
- [ ] Evitare caratteri problematici
- [ ] Seguire standard team

### Workflow
- [ ] Implementare feature branch workflow
- [ ] Gestire multiple feature contemporaneamente
- [ ] Eseguire merge puliti
- [ ] Mantenere repository ordinato

### Troubleshooting
- [ ] Gestire errori comuni
- [ ] Risolvere conflitti di naming
- [ ] Recuperare branch eliminati per errore
- [ ] Pulire branch obsoleti

---

## 🔗 Risorse Aggiuntive

### Documentazione
- [Git Branch Documentation](https://git-scm.com/docs/git-branch)
- [Git Switch Documentation](https://git-scm.com/docs/git-switch)
- [Atlassian Git Tutorials](https://www.atlassian.com/git/tutorials/using-branches)

### Best Practices
- [Git Flow](https://nvie.com/posts/a-successful-git-branching-model/)
- [GitHub Flow](https://guides.github.com/introduction/flow/)
- [Branch Naming Conventions](https://deepsource.io/blog/git-branch-naming-conventions/)

### Strumenti
- [Git GUI Tools](https://git-scm.com/downloads/guis)
- [IDE Integration](https://code.visualstudio.com/docs/editor/versioncontrol)

---

**Prossimo modulo**: [Merge e Strategie](../../14-Merge-e-Strategie/README.md)
