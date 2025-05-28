# Tipi di Annullamenti in Git

## 📖 Introduzione

Git offre diversi meccanismi per annullare modifiche, ognuno adatto a situazioni specifiche. La chiave per un uso efficace è comprendere **quando e come** usare ciascun metodo.

## 🎯 Obiettivi

- Comprendere i diversi stati delle modifiche in Git
- Identificare il metodo corretto per ogni situazione
- Distinguere tra annullamenti sicuri e pericolosi
- Costruire un framework mentale per la gestione degli errori

## 📊 Diagramma degli Stati Git

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│  Working Dir    │    │   Staging Area  │    │ Local Repository│    │Remote Repository│
│   (Untracked)   │    │    (Staged)     │    │   (Committed)   │    │    (Pushed)     │
└─────────────────┘    └─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │                     │
         ▼                       ▼                       ▼                     ▼
    git restore            git restore         git commit --amend          git revert
    git clean              git reset                git reset              (cronologia
                                                   git revert              pubblica)
```

## 🛠️ Classificazione dei Metodi di Annullamento

### 1. **Annullamenti Non Distruttivi (Sicuri)**

#### 🔵 git revert
- **Scopo**: Crea un nuovo commit che annulla modifiche precedenti
- **Sicurezza**: ✅ Completamente sicuro
- **Cronologia**: Preserva la cronologia esistente
- **Uso consigliato**: Repository condivisi, cronologia pubblica

```bash
# Annulla l'ultimo commit
git revert HEAD

# Annulla un commit specifico
git revert abc123

# Annulla senza creare commit immediatamente
git revert --no-commit HEAD
```

#### 🔵 git restore (Git 2.23+)
- **Scopo**: Ripristina file da versioni precedenti
- **Sicurezza**: ✅ Sicuro per working directory
- **Cronologia**: Non modifica la cronologia
- **Uso consigliato**: Modifiche non committate

```bash
# Ripristina file modificato
git restore file.txt

# Ripristina da staging
git restore --staged file.txt

# Ripristina da commit specifico
git restore --source=HEAD~1 file.txt
```

### 2. **Annullamenti Distruttivi (Rischiosi)**

#### 🔴 git reset
- **Scopo**: Sposta HEAD e modifica cronologia
- **Sicurezza**: ⚠️ Potenzialmente distruttivo
- **Cronologia**: Può modificare/cancellare cronologia
- **Uso consigliato**: Solo su repository locali non condivisi

```bash
# Modalità Soft - mantiene modifiche in staging
git reset --soft HEAD~1

# Modalità Mixed (default) - mantiene modifiche in working dir
git reset HEAD~1

# Modalità Hard - cancella tutto
git reset --hard HEAD~1
```

#### 🔴 git commit --amend
- **Scopo**: Modifica l'ultimo commit
- **Sicurezza**: ⚠️ Riscrive cronologia
- **Cronologia**: Modifica l'ultimo commit
- **Uso consigliato**: Solo se non ancora pushato

```bash
# Modifica messaggio ultimo commit
git commit --amend -m "Nuovo messaggio"

# Aggiungi file all'ultimo commit
git add forgotten-file.txt
git commit --amend --no-edit
```

## 🎯 Matrice Decisionale

| Situazione | Metodo Consigliato | Sicurezza | Note |
|------------|-------------------|-----------|------|
| File modificato non staged | `git restore` | ✅ Sicuro | Perdita modifiche |
| File in staging | `git restore --staged` | ✅ Sicuro | Rimuove da staging |
| Ultimo commit (locale) | `git commit --amend` | ⚠️ Moderato | Solo se non pushato |
| Commit precedenti (locale) | `git reset` | ⚠️ Rischioso | Backup consigliato |
| Commit pubblici | `git revert` | ✅ Sicuro | Crea nuovo commit |
| File cancellati | `git restore` o `git show` | ✅ Sicuro | Recupero rapido |

## 📝 Scenari Pratici

### Scenario 1: Modifiche Accidentali
```bash
# Situazione: Ho modificato file.txt per errore
# Soluzione: Ripristina dalla HEAD
git restore file.txt

# Verifica
git status  # Dovrebbe essere clean
```

### Scenario 2: Staged per Errore
```bash
# Situazione: Ho aggiunto file sbagliato allo staging
# Soluzione: Rimuovi da staging
git restore --staged wrong-file.txt

# Verifica
git status  # File torna a modified
```

### Scenario 3: Commit con Messaggio Sbagliato
```bash
# Situazione: Messaggio commit errato (non ancora pushato)
# Soluzione: Modifica l'ultimo commit
git commit --amend -m "Messaggio corretto"

# ⚠️ SOLO se non hai ancora fatto git push!
```

### Scenario 4: Commit da Annullare (Pubblico)
```bash
# Situazione: Commit pubblico da annullare
# Soluzione: Usa revert (sicuro)
git revert HEAD

# Questo crea un nuovo commit che annulla il precedente
```

## 🧠 Framework Mentale per la Scelta

### Domande da Porsi:

1. **Le modifiche sono state committate?**
   - No → `git restore`
   - Sì → Vai al punto 2

2. **Il commit è stato pushato?**
   - No → `git commit --amend` o `git reset`
   - Sì → `git revert`

3. **Stai lavorando da solo o in team?**
   - Solo → Più libertà con reset
   - Team → Preferisci revert

4. **Quanto è importante preservare la cronologia?**
   - Molto → `git revert`
   - Poco → `git reset` (con cautela)

## ⚠️ Principi di Sicurezza

### Regola d'Oro
> **Mai modificare cronologia già condivisa**

### Checklist di Sicurezza
- [ ] Hai fatto backup del repository?
- [ ] Stai lavorando su un branch separato?
- [ ] Hai verificato lo stato con `git status`?
- [ ] Sei sicuro che il commit non sia stato pushato?
- [ ] Hai considerato l'impatto sui collaboratori?

### Comandi di Emergenza
```bash
# Vedi cronologia delle operazioni
git reflog

# Recupera commit "perso"
git reset --hard HEAD@{1}

# Vedi cosa contiene un commit
git show <hash>

# Backup rapido
git branch backup-$(date +%Y%m%d-%H%M%S)
```

## 🎓 Quiz di Verifica

### Domanda 1
Hai modificato `config.js` ma non hai ancora fatto `git add`. Come annulli le modifiche?

<details>
<summary>Risposta</summary>

```bash
git restore config.js
```
</details>

### Domanda 2
Hai fatto `git add database.sql` per errore. Come lo rimuovi dall'area di staging?

<details>
<summary>Risposta</summary>

```bash
git restore --staged database.sql
```
</details>

### Domanda 3
Hai fatto un commit con messaggio sbagliato ma NON hai ancora pushato. Cosa fai?

<details>
<summary>Risposta</summary>

```bash
git commit --amend -m "Messaggio corretto"
```
</details>

### Domanda 4
Un commit pushato ieri ha introdotto un bug critico. Come lo gestisci?

<details>
<summary>Risposta</summary>

```bash
git revert <hash-commit-problematico>
```
Non usare reset perché il commit è già pubblico!
</details>

## 🔗 Connessioni con Altri Concetti

- **Area di Staging**: Base per capire dove annullare
- **Cronologia Git**: Determina quale metodo usare
- **Branch**: Ambiente sicuro per sperimentare
- **Remote Repository**: Limita le opzioni di annullamento

## 📚 Approfondimenti

### Per Principianti
- Inizia sempre con `git restore`
- Usa `git status` frequentemente
- Fai backup prima di operazioni rischiose

### Per Intermedi
- Sperimenta con `git reset` su branch di test
- Impara a leggere `git reflog`
- Pratica scenari di emergenza

### Per Avanzati
- Combina metodi per situazioni complesse
- Automatizza backup con script
- Insegna ai colleghi i principi di sicurezza

## 💡 Suggerimenti Pro

1. **Alias Utili**:
```bash
git config --global alias.undo 'restore'
git config --global alias.unstage 'restore --staged'
git config --global alias.last 'log -1 HEAD'
```

2. **Script di Backup**:
```bash
#!/bin/bash
git branch backup-$(date +%Y%m%d-%H%M%S)
echo "Backup creato: backup-$(date +%Y%m%d-%H%M%S)"
```

3. **Controllo Pre-Reset**:
```bash
git status && git log --oneline -5
```

## 🔄 Prossimi Passi

Ora che comprendi i tipi di annullamento, approfondirai:
- [02 - Git Restore (Moderno)](./02-git-restore.md)
- [03 - Git Reset Spiegato](./03-git-reset.md)
- [04 - Git Revert vs Reset](./04-revert-vs-reset.md)

---

**Ricorda**: La maestria negli annullamenti Git arriva con la pratica e la comprensione profonda degli stati del repository. Inizia sempre con i metodi più sicuri!
