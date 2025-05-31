# 01 - Commit Amend: Modificare l'Ultimo Commit

## 📖 Spiegazione Concettuale

`git commit --amend` è uno dei comandi più utili di Git per correggere errori nell'ultimo commit. Ti permette di modificare il messaggio, aggiungere file dimenticati, o correggere piccoli errori senza creare un nuovo commit nella cronologia.

⚠️ **ATTENZIONE**: Usa `--amend` solo su commit che **non hai ancora pushato**. Modificare commit pubblici può causare problemi ai collaboratori.

## 🔧 Sintassi e Parametri

### Sintassi Base
```bash
git commit --amend
```

### Parametri Principali
```bash
# Modifica solo il messaggio del commit
git commit --amend -m "Nuovo messaggio"

# Modifica il messaggio senza aprire l'editor
git commit --amend --no-edit

# Modifica l'autore del commit
git commit --amend --author="Nome Cognome <email@example.com>"

# Modifica la data del commit
git commit --amend --date="2023-12-25 10:30:00"

# Modifica senza aprire l'editor e mantiene il messaggio
git commit --amend --no-edit
```

## 🎯 Casi d'Uso Pratici

### Caso 1: Correggere un Messaggio di Commit
```bash
# Hai fatto un commit con un typo nel messaggio
git commit -m "Fix bgu in login system"

# Correggi il messaggio
git commit --amend -m "Fix bug in login system"
```

### Caso 2: Aggiungere File Dimenticato
```bash
# Hai committato ma hai dimenticato un file
git commit -m "Add user authentication"

# Ti accorgi di aver dimenticato un file
git add forgot_this_file.js

# Aggiungi il file all'ultimo commit
git commit --amend --no-edit
```

### Caso 3: Rimuovere File dall'Ultimo Commit
```bash
# Hai aggiunto un file per errore
git reset HEAD~1 file_da_rimuovere.txt
git commit --amend
```

### Caso 4: Modificare Autore e Data
```bash
# Correggere informazioni dell'autore
git commit --amend --author="Mario Rossi <mario@example.com>"

# Correggere la data (formato ISO)
git commit --amend --date="2023-12-25T10:30:00"
```

## 💼 Workflow Professionale

### Scenario Completo: Correzione Pre-Push
```bash
# 1. Lavori su una feature
echo "console.log('Hello World');" > app.js
git add app.js
git commit -m "Add hello world featrue"  # Typo nel messaggio!

# 2. Ti accorgi del typo e di aver dimenticato un file
echo "body { margin: 0; }" > styles.css
git add styles.css

# 3. Correggi tutto in un'unica operazione
git commit --amend -m "Add hello world feature with styles"

# 4. Verifica il risultato
git log --oneline -1
# Output: abc1234 Add hello world feature with styles

# 5. Ora puoi pushare tranquillamente
git push origin feature/hello-world
```

### Best Practice per Team
```bash
# Prima di fare amend, verifica di non aver già pushato
git log --oneline origin/main..HEAD

# Se ci sono commit, significa che non hai ancora pushato
# È sicuro usare --amend

# Se non ci sono commit, significa che hai già pushato
# NON usare --amend!
```

## ⚠️ Errori Comuni

### 1. **Amend su Commit Pubblici**
```bash
# ❌ SBAGLIATO - Il commit è già stato pushato
git push origin main
git commit --amend -m "New message"  # Pericoloso!

# ✅ CORRETTO - Usa revert o un nuovo commit
git revert HEAD
# oppure
git commit -m "Fix previous commit message typo"
```

### 2. **Perdere Modifiche Durante Amend**
```bash
# ❌ SBAGLIATO - Modifiche non staginate perse
echo "new content" > file.txt
git commit --amend  # file.txt non sarà incluso!

# ✅ CORRETTO - Aggiungi prima al staging
echo "new content" > file.txt
git add file.txt
git commit --amend
```

### 3. **Confondere Hash dopo Amend**
```bash
# Il comando amend crea un NUOVO commit con hash diverso
git log --oneline -1
# Output: abc1234 Original message

git commit --amend -m "New message"
git log --oneline -1
# Output: def5678 New message  # Hash cambiato!
```

## 💡 Best Practices

### 1. **Verifica Prima di Amend**
```bash
# Script per verificare se è sicuro fare amend
check_amend_safety() {
    if git log --oneline origin/$(git branch --show-current)..HEAD | grep -q .; then
        echo "✅ Sicuro fare amend - commit non ancora pushato"
        return 0
    else
        echo "⚠️  Attenzione - commit già pushato"
        return 1
    fi
}

# Uso
check_amend_safety && git commit --amend
```

### 2. **Amend con Controllo Qualità**
```bash
# Template per amend sicuro
safe_amend() {
    echo "=== Pre-amend Check ==="
    echo "Current commit:"
    git log --oneline -1
    echo "Files to be amended:"
    git diff --cached --name-only
    echo "Continue? (y/N)"
    read -r response
    if [[ "$response" =~ ^[Yy]$ ]]; then
        git commit --amend
    else
        echo "Amend cancelled"
    fi
}
```

### 3. **Amend con Backup**
```bash
# Crea un tag di backup prima di amend pericolosi
git tag backup/pre-amend-$(date +%s)
git commit --amend -m "New message"

# Se qualcosa va storto, puoi recuperare
git reset --hard backup/pre-amend-[timestamp]
```

## 🧠 Quiz di Autovalutazione

### Domanda 1
Quando è sicuro usare `git commit --amend`?
- a) Solo su commit privati (non pushati)
- b) Sempre, Git gestisce automaticamente i conflitti
- c) Solo su repository personali
- d) Mai, è sempre pericoloso

<details>
<summary>Risposta</summary>
**a) Solo su commit privati (non pushati)**

L'amend riscrive la storia cambiando l'hash del commit. Se il commit è già stato pushato e altri hanno fatto pull, causerai conflitti.
</details>

### Domanda 2
Cosa succede all'hash del commit quando usi `--amend`?
- a) Rimane identico
- b) Viene cambiato solo il messaggio
- c) Viene generato un nuovo hash
- d) Viene concatenato al vecchio hash

<details>
<summary>Risposta</summary>
**c) Viene generato un nuovo hash**

Ogni commit ha un hash basato su contenuto, messaggio, timestamp, ecc. Modificando qualsiasi elemento, l'hash cambia completamente.
</details>

### Domanda 3
Come aggiungi un file dimenticato all'ultimo commit?
- a) `git add file.js && git commit`
- b) `git add file.js && git commit --amend --no-edit`
- c) `git commit --amend file.js`
- d) `git add --amend file.js`

<details>
<summary>Risposta</summary>
**b) `git add file.js && git commit --amend --no-edit`**

Devi prima stageare il file con `git add`, poi fare amend. `--no-edit` mantiene il messaggio esistente.
</details>

## 🏋️ Esercizi Pratici

### Esercizio 1: Amend Base
```bash
# Setup
mkdir test-amend && cd test-amend
git init
echo "Hello" > file1.txt
git add file1.txt
git commit -m "Add file with typo in mesage"

# Compito: Correggi il typo nel messaggio usando --amend
```

### Esercizio 2: Aggiungere File Dimenticato
```bash
# Setup (continua da esercizio 1)
echo "World" > file2.txt
# Hai dimenticato di aggiungere file2.txt al commit precedente

# Compito: Aggiungi file2.txt all'ultimo commit senza cambiare il messaggio
```

### Esercizio 3: Modifica Autore
```bash
# Setup (continua da esercizio 2)
# Il commit precedente ha l'autore sbagliato

# Compito: Cambia l'autore in "Mario Rossi <mario@test.com>"
```

## 📖 Approfondimenti

### Internals: Come Funziona Amend
```bash
# L'amend sotto il cofano fa questo:
# 1. Prende il parent del commit corrente
# 2. Crea un nuovo commit con stesso parent
# 3. Include tutte le modifiche del vecchio commit + staging area
# 4. Usa il nuovo messaggio (se fornito)
# 5. Aggiorna HEAD al nuovo commit
# 6. Il vecchio commit diventa orphaned (verrà garbage collected)
```

### Integrazione con Git Hooks
```bash
# .git/hooks/pre-commit
#!/bin/sh
# Previeni amend accidentali su commit pubblici
if git rev-parse --verify HEAD >/dev/null 2>&1; then
    if git merge-base --is-ancestor HEAD origin/$(git branch --show-current) 2>/dev/null; then
        echo "⚠️ Warning: This commit has been pushed. Consider using revert instead."
        echo "Continue anyway? (y/N)"
        exec < /dev/tty
        read -r response
        if [[ ! "$response" =~ ^[Yy]$ ]]; then
            exit 1
        fi
    fi
fi
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Visualizzare Storia Commit](../../08-Visualizzare-Storia-Commit/)
- [➡️ Reset vs Revert](02-reset-vs-revert.md)
