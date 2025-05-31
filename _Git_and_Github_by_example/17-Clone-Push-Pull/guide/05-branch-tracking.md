# Branch Tracking

## 📖 Introduzione

Il **branch tracking** è un meccanismo fondamentale di Git che stabilisce una relazione tra un branch locale e un branch remoto. Questa relazione permette di sincronizzare facilmente le modifiche e di utilizzare comandi semplificati come `git push` e `git pull` senza specificare ogni volta il remote e il branch di destinazione.

Quando un branch locale "traccia" un branch remoto, Git sa automaticamente:
- Dove inviare le modifiche con `git push`
- Da dove scaricare gli aggiornamenti con `git pull`
- Come confrontare lo stato locale con quello remoto

## 🎯 Concetti Fondamentali

### Upstream Branch

Un **upstream branch** (o tracking branch) è il branch remoto che un branch locale segue. Questa relazione viene stabilita:

- **Automaticamente** quando cloni un repository
- **Automaticamente** quando fai checkout di un branch remoto
- **Manualmente** con il comando `git branch --set-upstream-to`

### Tracking Information

Git memorizza le informazioni di tracking in `.git/config`:

```ini
[branch "main"]
    remote = origin
    merge = refs/heads/main
```

## 🛠️ Configurazione del Tracking

### Visualizzare Branch Tracking

```bash
# Mostra tutti i branch con informazioni di tracking
git branch -vv

# Output esempio:
# * main    a1b2c3d [origin/main] Ultimo commit
#   feature f4e5d6c [origin/feature: ahead 2] Feature branch
#   local   g7h8i9j Non tracking branch
```

### Stabilire Tracking per Branch Esistente

```bash
# Collega branch locale a branch remoto
git branch --set-upstream-to=origin/main main

# Forma abbreviata
git branch -u origin/main main

# Se sei già sul branch
git branch -u origin/main
```

### Tracking durante Push

```bash
# Crea branch remoto e stabilisce tracking
git push -u origin feature-branch

# Equivale a:
git push origin feature-branch
git branch -u origin/feature-branch feature-branch
```

## 📊 Stati di Sincronizzazione

### Ahead (In Avanti)

Il branch locale ha commit che non sono ancora sul remoto:

```bash
git status
# Output: Your branch is ahead of 'origin/main' by 2 commits.

# Visualizza i commit in anticipo
git log origin/main..HEAD --oneline
```

### Behind (Indietro)

Il branch remoto ha commit che non sono ancora nel locale:

```bash
git status
# Output: Your branch is behind 'origin/main' by 1 commit.

# Visualizza i commit mancanti
git log HEAD..origin/main --oneline
```

### Diverged (Divergente)

Entrambi i branch hanno commit unici:

```bash
git status
# Output: Your branch and 'origin/main' have diverged,
# and have 2 and 1 different commits each.
```

## 🔄 Operazioni con Tracking

### Push Semplificato

Con tracking configurato:

```bash
# Invece di specificare remote e branch
git push origin main

# Puoi usare semplicemente
git push
```

### Pull Semplificato

```bash
# Git sa da dove scaricare
git pull

# Equivale a (con tracking):
git pull origin main
```

### Fetch e Confronto

```bash
# Aggiorna riferimenti remoti
git fetch

# Confronta con upstream
git diff @{upstream}

# Log delle differenze
git log --oneline @{upstream}..HEAD  # Commit locali
git log --oneline HEAD..@{upstream}  # Commit remoti
```

## ⚙️ Configurazioni Avanzate

### Multiple Remote

Gestire più remote con tracking:

```bash
# Aggiungi un secondo remote
git remote add upstream https://github.com/original/repo.git

# Configura tracking verso upstream
git branch -u upstream/main main

# Push verso origin, pull da upstream
git push origin main
git pull upstream main
```

### Unset Tracking

```bash
# Rimuovi relazione di tracking
git branch --unset-upstream main

# Verifica
git branch -vv
# * main a1b2c3d Ultimo commit (no upstream)
```

### Default Push Behavior

```bash
# Configura comportamento push
git config push.default simple    # Solo branch con tracking
git config push.default current   # Branch attuale su remote omonimo
git config push.default upstream  # Solo verso upstream configurato
```

## 🚨 Problemi Comuni e Soluzioni

### Branch Non Traccia Remote

**Problema**: `git push` richiede sempre remote e branch

**Soluzione**:
```bash
# Verifica stato tracking
git branch -vv

# Configura tracking se mancante
git branch -u origin/main
```

### Remote Branch Eliminato

**Problema**: Branch locale traccia branch remoto inesistente

**Soluzione**:
```bash
# Pulisci riferimenti obsoleti
git remote prune origin

# Rimuovi tracking se necessario
git branch --unset-upstream feature-old
```

### Tracking Branch Errato

**Problema**: Branch traccia remote sbagliato

**Soluzione**:
```bash
# Cambia upstream
git branch -u origin/develop feature-branch

# O rimuovi e riconfigura
git branch --unset-upstream feature-branch
git push -u origin feature-branch
```

## 📋 Best Practices

### 1. Usa -u per Nuovi Branch

```bash
# Sempre con -u per nuovi branch
git push -u origin feature-new

# Evita push "nudi" senza tracking
git push origin feature-new  # ❌ No tracking
```

### 2. Verifica Tracking Regolarmente

```bash
# Controlla stato prima di operazioni importanti
git branch -vv
git status
```

### 3. Configurazione Consistente

```bash
# Imposta default ragionevoli
git config --global push.default simple
git config --global pull.rebase false
```

### 4. Documentazione Branch

```bash
# Usa nomi descriptivi per branch remoti
git push -u origin feature/user-authentication
git push -u origin bugfix/login-validation
```

## 🧪 Quiz di Verifica

### Domanda 1
**Cosa significa che un branch locale è "ahead" di 3 commit rispetto al suo upstream?**

<details>
<summary>Risposta</summary>

Il branch locale ha 3 commit che non sono ancora presenti nel branch remoto corrispondente. Questi commit devono essere inviati con `git push` per sincronizzare il remote.

</details>

### Domanda 2
**Quale comando usi per collegare un branch locale esistente a un branch remoto?**

<details>
<summary>Risposta</summary>

```bash
git branch -u origin/branch-name local-branch-name
# o se sei già sul branch:
git branch -u origin/branch-name
```

</details>

### Domanda 3
**Come puoi vedere quali branch hanno configurato il tracking e verso quale remote?**

<details>
<summary>Risposta</summary>

```bash
git branch -vv
```

Questo comando mostra tutti i branch con le informazioni di tracking tra parentesi quadre.

</details>

## 🛠️ Esercizio Pratico

### Obiettivo
Configurare e gestire branch tracking in uno scenario realistico.

### Passi

1. **Setup Repository**:
   ```bash
   # Clona repository di test
   git clone https://github.com/user/test-repo.git
   cd test-repo
   
   # Verifica tracking esistente
   git branch -vv
   ```

2. **Crea Branch Senza Tracking**:
   ```bash
   # Crea branch locale
   git checkout -b feature-testing
   
   # Crea commit
   echo "Test feature" > feature.txt
   git add feature.txt
   git commit -m "Add test feature"
   
   # Verifica stato (no tracking)
   git branch -vv
   ```

3. **Configura Tracking**:
   ```bash
   # Push con tracking
   git push -u origin feature-testing
   
   # Verifica tracking configurato
   git branch -vv
   git status
   ```

4. **Test Sincronizzazione**:
   ```bash
   # Crea altro commit
   echo "More changes" >> feature.txt
   git commit -am "Update feature"
   
   # Push semplificato (grazie al tracking)
   git push
   
   # Verifica stato
   git status
   ```

5. **Gestione Multiple Remote**:
   ```bash
   # Aggiungi secondo remote (se possibile)
   git remote add upstream https://github.com/original/test-repo.git
   git fetch upstream
   
   # Cambia tracking
   git branch -u upstream/main
   git branch -vv
   ```

### Verifica Risultati

Il completamento dell'esercizio dimostra:
- ✅ Comprensione del tracking automatico vs manuale
- ✅ Capacità di configurare tracking per branch esistenti
- ✅ Utilizzo efficace di comandi semplificati
- ✅ Gestione di scenari con multiple remote

## 🔗 Link Correlati

- [01 - Git Clone](./01-git-clone.md) - Clonazione e tracking automatico
- [02 - Remote Repository](./02-remote-repository.md) - Gestione remote
- [03 - Git Push](./03-git-push.md) - Push e upstream
- [04 - Git Pull vs Fetch](./04-pull-vs-fetch.md) - Sincronizzazione

---

### 🧭 Navigazione

- **⬅️ Precedente**: [04 - Git Pull vs Fetch](./04-pull-vs-fetch.md)
- **🏠 Home Modulo**: [README.md](../README.md)
- **➡️ Successivo**: [Esempi Pratici](../esempi/01-clone-setup.md)
