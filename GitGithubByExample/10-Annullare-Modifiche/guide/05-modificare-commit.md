# Modificare Commit con Git Amend

## 📚 Introduzione

Git offre diverse modalità per modificare commit già creati. La più comune e sicura è `git commit --amend`, che permette di modificare l'ultimo commit senza creare nuovi commit nella storia.

## 🎯 Obiettivi di Apprendimento

- Comprendere quando e come usare `git commit --amend`
- Modificare messaggi di commit
- Aggiungere file dimenticati all'ultimo commit
- Comprendere le implicazioni di sicurezza dell'amend
- Gestire situazioni con repository remoti

## 📖 Teoria: Git Commit --Amend

### Cosa fa `git commit --amend`

Il comando `git commit --amend` sostituisce completamente l'ultimo commit con un nuovo commit che include:
- Le modifiche nello staging area (se presenti)
- Un nuovo messaggio di commit (se specificato)

```
Prima dell'amend:
A --- B --- C (HEAD)

Dopo l'amend:
A --- B --- C' (HEAD, nuovo commit che sostituisce C)
```

### Scenari d'Uso Comuni

1. **Correggere il messaggio dell'ultimo commit**
2. **Aggiungere file dimenticati**
3. **Rimuovere file aggiunti per errore**
4. **Modificare i contenuti dell'ultimo commit**

## 🛠️ Sintassi e Comandi

### Modificare Solo il Messaggio

```bash
# Aprire l'editor per modificare il messaggio
git commit --amend

# Specificare direttamente il nuovo messaggio
git commit --amend -m "Nuovo messaggio di commit"
```

### Aggiungere File all'Ultimo Commit

```bash
# Aggiungere file dimenticati
git add file-dimenticato.txt
git commit --amend --no-edit

# Con nuovo messaggio
git add file-dimenticato.txt
git commit --amend -m "Aggiunto file dimenticato al commit"
```

### Modificare Autore dell'Ultimo Commit

```bash
# Cambiare autore
git commit --amend --author="Nuovo Nome <nuovo@email.com>"

# Usare la configurazione corrente
git commit --amend --reset-author
```

### Opzioni Avanzate

```bash
# Amend senza aprire l'editor
git commit --amend --no-edit

# Amend con data corrente
git commit --amend --date="now"

# Amend con data specifica
git commit --amend --date="2024-01-15 10:30:00"
```

## 📋 Esempi Pratici

### Esempio 1: Correggere un Messaggio di Commit

```bash
# Situazione: hai appena fatto un commit con messaggio sbagliato
git commit -m "Fix bug in logn function"

# Correggere il messaggio
git commit --amend -m "Fix bug in login function"
```

### Esempio 2: Aggiungere File Dimenticato

```bash
# Commit iniziale
git add main.py
git commit -m "Implement user authentication"

# Ti accorgi di aver dimenticato un file
git add tests/test_auth.py
git commit --amend --no-edit

# Risultato: il commit include sia main.py che test_auth.py
```

### Esempio 3: Rimuovere File dall'Ultimo Commit

```bash
# Hai aggiunto un file per errore
git add .
git commit -m "Update documentation"

# Rimuovere il file e rifare il commit
git reset HEAD~1
git add docs/
git commit -m "Update documentation"
```

### Esempio 4: Modificare Contenuto di File

```bash
# Commit con bug
git add calculator.py
git commit -m "Add multiplication function"

# Correggere il bug
# Modifica calculator.py per correggere l'errore
git add calculator.py
git commit --amend --no-edit
```

## ⚠️ Regole di Sicurezza

### ✅ Quando è Sicuro Usare Amend

```bash
# ✅ Su commit locali non ancora pushati
git log --oneline -3
# a1b2c3d (HEAD) Work in progress
# d4e5f6g Previous commit
# g7h8i9j Older commit

git commit --amend -m "Complete feature implementation"
```

### ❌ Quando NON Usare Amend

```bash
# ❌ Su commit già pushati e condivisi
git log --oneline -3
# a1b2c3d (HEAD, origin/main) Shared commit ← NON MODIFICARE
# d4e5f6g Previous commit
# g7h8i9j Older commit

# Questo creerà problemi per altri collaboratori!
git commit --amend -m "Modified shared commit" # ❌ PERICOLOSO
```

### 🔧 Workflow Sicuro per Repository Condivisi

```bash
# Se devi modificare un commit già pushato
# 1. Creare un nuovo commit di correzione
git add corrections.txt
git commit -m "Fix typo in previous commit"

# 2. Oppure usare revert se necessario
git revert HEAD~1
git commit -m "Revert problematic commit"
```

## 🚨 Gestione Situazioni Critiche

### Recupero da Amend Accidentale

```bash
# Visualizzare il reflog per trovare il commit originale
git reflog
# a1b2c3d HEAD@{0}: commit (amend): Messaggio modificato
# d4e5f6g HEAD@{1}: commit: Messaggio originale ← questo vogliamo recuperare

# Tornare al commit originale
git reset --hard HEAD@{1}

# Oppure creare un nuovo branch dal commit originale
git branch backup-commit HEAD@{1}
```

### Amend dopo Push Accidentale

```bash
# Se hai fatto amend di un commit già pushato
git log --oneline -2
# a1b2c3d (HEAD) Commit modificato
# d4e5f6g (origin/main) Commit originale pushato

# Opzione 1: Force push (SOLO se sei sicuro che nessun altro abbia pullato)
git push --force-with-lease origin main

# Opzione 2: Revert e ricominciare (SICURO)
git revert HEAD
git push origin main
# Poi ricreare le modifiche corrette in un nuovo commit
```

## 📊 Decision Matrix: Quando Usare Amend

| Situazione | Commit Pushato? | Altri Collaboratori? | Azione Consigliata |
|------------|----------------|---------------------|---------------------|
| Correggere messaggio | ❌ No | - | ✅ `git commit --amend` |
| Aggiungere file | ❌ No | - | ✅ `git commit --amend` |
| Correggere messaggio | ✅ Sì | ❌ No | ⚠️ `git push --force-with-lease` |
| Correggere messaggio | ✅ Sì | ✅ Sì | ❌ Nuovo commit di correzione |
| Correggere bug | ❌ No | - | ✅ `git commit --amend` |
| Correggere bug | ✅ Sì | ✅ Sì | ❌ `git revert` + nuovo commit |

## 🔄 Workflow Completo

### Workflow Standard per Modifiche Locali

```bash
# 1. Verifica stato corrente
git status
git log --oneline -3

# 2. Prepara modifiche se necessarie
git add files-to-modify

# 3. Esegui amend
git commit --amend --no-edit  # o con nuovo messaggio

# 4. Verifica risultato
git log --oneline -3
git show HEAD
```

### Workflow per Repository Condivisi

```bash
# 1. Verifica se il commit è stato pushato
git log --oneline --branches --remotes -5

# 2a. Se NON pushato: amend sicuro
if [ "$(git rev-parse HEAD)" != "$(git rev-parse origin/main)" ]; then
    git commit --amend
fi

# 2b. Se pushato: usa alternativa sicura
git add corrections
git commit -m "Fix issue in previous commit"
```

## 🎯 Checklist Pre-Amend

Prima di usare `git commit --amend`, verifica:

- [ ] Il commit NON è stato ancora pushato
- [ ] Nessun altro collaboratore ha basato lavoro su questo commit
- [ ] Hai preparato tutte le modifiche necessarie nello staging
- [ ] Il nuovo messaggio di commit è chiaro e descrittivo
- [ ] Hai fatto backup se necessario (branch o reflog)

## 💡 Tips e Best Practices

### 1. Uso dell'Editor
```bash
# Configurare editor predefinito per messaggi lunghi
git config --global core.editor "code --wait"
git commit --amend  # Aprirà VS Code
```

### 2. Template per Messaggi
```bash
# Usare template predefiniti
git config --global commit.template ~/.gitmessage
git commit --amend  # Userà il template
```

### 3. Alias Utili
```bash
# Configurare alias per operazioni comuni
git config --global alias.amend 'commit --amend --no-edit'
git config --global alias.amendit 'commit --amend'

# Uso degli alias
git amend      # Amend senza modificare messaggio
git amendit    # Amend aprendo editor
```

### 4. Verifica Pre-Push
```bash
# Script per verificare commit prima del push
#!/bin/bash
if git diff --quiet origin/main..HEAD; then
    echo "Nessuna modifica da pushare"
else
    echo "Commit da pushare:"
    git log --oneline origin/main..HEAD
    echo "Vuoi procedere con il push? (y/n)"
fi
```

## 🔗 Comandi Correlati

- `git reset --soft HEAD~1` - Unfare ultimo commit mantenendo modifiche
- `git revert HEAD` - Creare commit che annulla l'ultimo
- `git reflog` - Visualizzare storia completa delle modifiche
- `git show HEAD` - Mostrare dettagli ultimo commit
- `git log --amend` - Non esiste, ma `git log -1 --oneline` mostra l'ultimo

## 📝 Riassunto

`git commit --amend` è uno strumento potente per perfezionare i commit locali, ma richiede attenzione quando lavori con repository condivisi. Usalo liberamente sui commit non ancora pushati, ma considera alternative più sicure per commit già condivisi con altri collaboratori.

La chiave è sempre verificare lo stato del repository e la presenza di collaboratori prima di modificare la storia dei commit.
