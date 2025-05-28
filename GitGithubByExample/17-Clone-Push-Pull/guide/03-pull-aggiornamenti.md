# 📥 Git Pull - Aggiornare Repository Locali

## 🎯 Obiettivi del Modulo
- Comprendere il funzionamento di `git pull`
- Gestire gli aggiornamenti dal repository remoto
- Risolvere conflitti durante il pull
- Utilizzare strategie di pull avanzate

---

## 📚 Concetti Fondamentali

### Cosa è Git Pull?
`git pull` è un comando che **combina** due operazioni:
1. **`git fetch`** - Scarica le modifiche dal repository remoto
2. **`git merge`** - Unisce le modifiche al branch locale

```bash
# Equivalente a:
git fetch origin
git merge origin/main
```

### 🔄 Il Flusso di Pull

```
Repository Remoto     Repository Locale
      main                 main
       |                    |
   [A]-[B]-[C]         [A]-[B]
                            |
                     git pull origin main
                            ↓
                       [A]-[B]-[C]
```

---

## 🚀 Sintassi e Comandi Base

### Pull Standard
```bash
# Pull dal branch corrente
git pull

# Pull da un branch specifico
git pull origin main

# Pull da un repository specifico
git pull upstream develop
```

### Pull con Opzioni
```bash
# Pull con rebase invece di merge
git pull --rebase

# Pull forzato (attenzione!)
git pull --force

# Pull senza commit automatico
git pull --no-commit

# Pull di tutti i branch
git pull --all
```

---

## 🛠️ Scenari Pratici

### Scenario 1: Pull Semplice (Fast-Forward)
```bash
# Situazione: il repository remoto ha commit più recenti
git status
# Your branch is behind 'origin/main' by 2 commits

git pull origin main
# Updating abc123..def456
# Fast-forward
#  file1.txt | 2 ++
#  file2.txt | 1 +
#  2 files changed, 3 insertions(+)
```

### Scenario 2: Pull con Merge
```bash
# Situazione: hai commit locali E il remoto ha nuovi commit
git log --oneline --graph
# * 456def (HEAD -> main) Local commit
# * 123abc Initial commit

git pull origin main
# Merge made by the 'recursive' strategy
#  remote-file.txt | 1 +
#  1 file changed, 1 insertion(+)

git log --oneline --graph
# *   789ghi (HEAD -> main) Merge branch 'main' of origin/main
# |\
# | * 654fed (origin/main) Remote commit
# * | 456def Local commit
# |/
# * 123abc Initial commit
```

### Scenario 3: Pull con Conflitti
```bash
git pull origin main
# Auto-merging file.txt
# CONFLICT (content): Merge conflict in file.txt
# Automatic merge failed; fix conflicts and then commit the result.

# Risolvi i conflitti manualmente
git status
# Unmerged paths:
#   both modified:   file.txt

# Dopo aver risolto i conflitti
git add file.txt
git commit -m "Risolti conflitti durante pull"
```

---

## 🔧 Strategie di Pull Avanzate

### 1. Pull con Rebase
```bash
# Invece di creare un merge commit, riapplica i tuoi commit
git pull --rebase origin main

# Configura rebase come default per pull
git config pull.rebase true
```

**Differenza tra Pull normale e Pull con Rebase:**
```
Pull normale (merge):           Pull con rebase:
* Merge commit                  * 456def Local commit (riapplicato)
|\                              * 654fed Remote commit  
| * Remote commit               * 123abc Initial commit
* | Local commit
|/
* Initial commit
```

### 2. Pull Only Fast-Forward
```bash
# Fallisce se non è possibile un fast-forward
git pull --ff-only origin main

# Configura come default
git config pull.ff only
```

### 3. Pull con Stash Automatico
```bash
# Salva automaticamente le modifiche non committate
git pull --autostash origin main
```

---

## 🚨 Gestione Errori e Problemi

### Errore: "Your local changes would be overwritten"
```bash
# Problema: hai modifiche non committate che confliggono
error: Your local changes to the following files would be overwritten by merge:
    file.txt
Please commit your changes or stash them before you merge.

# Soluzioni:
# 1. Committa le modifiche
git add .
git commit -m "Salva modifiche locali"
git pull

# 2. Stash le modifiche
git stash
git pull
git stash pop
```

### Errore: "Divergent branches"
```bash
# Git 2.27+ richiede di specificare la strategia
hint: You have divergent branches and need to specify how to reconcile them.

# Opzioni:
git config pull.rebase false  # merge (default)
git config pull.rebase true   # rebase
git config pull.ff only       # fast-forward only
```

### Recuperare da un Pull Sbagliato
```bash
# Annulla l'ultimo pull (se era un merge)
git reset --hard HEAD~1

# Oppure usa ORIG_HEAD
git reset --hard ORIG_HEAD
```

---

## 📊 Tabella Comparativa Strategie

| Strategia | Comando | Quando Usare | Pro | Contro |
|-----------|---------|--------------|-----|---------|
| **Merge** | `git pull` | Branch condivisi | Preserva storia | Merge commit |
| **Rebase** | `git pull --rebase` | Sviluppo locale | Storia lineare | Riscrive storia |
| **Fast-Forward** | `git pull --ff-only` | Aggiornamenti semplici | Storia pulita | Fallisce con divergenze |

---

## 🎓 Best Practices

### ✅ Cosa Fare
1. **Controlla sempre lo stato** prima del pull
2. **Committa o stash** le modifiche locali
3. **Usa pull con rebase** per feature branch
4. **Verifica i cambiamenti** dopo il pull
5. **Testa il codice** dopo ogni pull

### ❌ Cosa Evitare
1. **Non fare pull** con modifiche non committate
2. **Non usare --force** senza necessità
3. **Non ignorare** i conflitti
4. **Non fare pull** su branch condivisi con rebase

### 🔧 Configurazione Consigliata
```bash
# Configura strategia di pull
git config --global pull.rebase false

# Abilita autostash per rebase
git config --global rebase.autoStash true

# Abilita rerere per conflitti ricorrenti
git config --global rerere.enabled true
```

---

## 🧪 Workflow Consigliato

### Pull Sicuro
```bash
# 1. Controlla lo stato
git status

# 2. Stash se necessario
git stash

# 3. Pull
git pull origin main

# 4. Recupera stash se usato
git stash pop

# 5. Verifica i cambiamenti
git log --oneline -5
git diff HEAD~1
```

### Pull per Feature Branch
```bash
# 1. Vai al branch principale
git switch main

# 2. Pull degli ultimi cambiamenti
git pull origin main

# 3. Torna al feature branch
git switch feature-branch

# 4. Rebase sul main aggiornato
git rebase main
```

---

## 🎯 Quiz di Verifica

### Domanda 1
Cosa fa il comando `git pull --rebase origin main`?
- a) Scarica e fa merge dei cambiamenti
- b) Scarica e riapplica i commit locali sopra quelli remoti
- c) Scarica solo i cambiamenti senza applicarli
- d) Forza il download sovrascrivendo tutto

<details>
<summary>Risposta</summary>
<strong>b)</strong> Scarica e riapplica i commit locali sopra quelli remoti, creando una storia lineare.
</details>

### Domanda 2
Quando ricevi l'errore "Your local changes would be overwritten", cosa dovresti fare?
- a) Usare git pull --force
- b) Committare o fare stash delle modifiche locali
- c) Eliminare i file modificati
- d) Cambiare branch

<details>
<summary>Risposta</summary>
<strong>b)</strong> Committare o fare stash delle modifiche locali prima di fare pull.
</details>

### Domanda 3
Qual è la differenza tra `git fetch` e `git pull`?
- a) Sono identici
- b) fetch scarica, pull scarica e applica
- c) fetch è più veloce
- d) pull è più sicuro

<details>
<summary>Risposta</summary>
<strong>b)</strong> fetch solo scarica i cambiamenti, pull scarica e li applica (merge/rebase).
</details>

---

## 🏋️ Esercizi Pratici

### Esercizio 1: Pull Base
1. Crea un repository con alcuni commit
2. Simula cambiamenti remoti
3. Esegui un pull standard
4. Analizza il risultato

### Esercizio 2: Gestione Conflitti
1. Crea modifiche locali e remote allo stesso file
2. Esegui pull
3. Risolvi i conflitti
4. Completa il merge

### Esercizio 3: Pull con Rebase
1. Configura pull con rebase
2. Crea commit locali e remoti
3. Esegui pull --rebase
4. Confronta con pull normale

---

## 🔗 Link di Approfondimento

- **Prossimo:** [17-Fork-Pull-Request](../../17-Fork-Pull-Request/guide/01-fork-repository.md)
- **Precedente:** [02-push-repository.md](./02-push-repository.md)
- **Indice Modulo:** [README.md](../README.md)
- **Corso Principale:** [GitGithubByExample](../../README.md)

---

## 📝 Note Aggiuntive

### Differenza con altri VCS
A differenza di SVN o CVS, Git pull può comportare operazioni complesse come merge o rebase. È importante capire cosa succede "sotto il cofano".

### Automazione
Molti IDE moderni offrono integrazione Git che semplifica le operazioni di pull, ma è importante conoscere i comandi per situazioni complesse.

---

*💡 **Suggerimento:** Usa sempre `git status` e `git log` dopo un pull per verificare cosa è cambiato nel repository.*
