# Git Log Fondamentali

## 📖 Concetti Base

### Cos'è Git Log
`git log` è il comando fondamentale per visualizzare la cronologia dei commit in un repository Git. Mostra la storia lineare delle modifiche, permettendo di esplorare chi ha fatto cosa e quando.

### Il Comando Base
```bash
git log
```

Questo comando mostra:
- **Hash SHA-1** del commit (identificatore univoco)
- **Autore** e email
- **Data e ora** del commit
- **Messaggio** del commit

## 🔧 Sintassi Essenziale

### Formato Completo (Default)
```bash
git log

# Output tipico:
commit a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0
Author: Mario Rossi <mario.rossi@email.com>
Date:   Mon Jan 15 14:30:25 2024 +0100

    Aggiunta funzionalità di login
    
    - Implementata autenticazione utente
    - Aggiunta validazione password
    - Creato sistema di sessioni
```

### Opzioni Base Più Utilizzate

#### Formato Compatto
```bash
# Una riga per commit
git log --oneline

# Output:
a1b2c3d Aggiunta funzionalità di login
b2c3d4e Correzione bug nel form
c3d4e5f Inizializzazione progetto
```

#### Limitare il Numero di Commit
```bash
# Ultimi 5 commit
git log -5

# Ultimo commit
git log -1
```

#### Mostrare le Modifiche
```bash
# Mostra le modifiche (patch) per ogni commit
git log -p

# Mostra solo statistiche delle modifiche
git log --stat
```

## 🎯 Casi d'Uso Comuni

### 1. Vista Rapida della Cronologia
```bash
# Per avere una panoramica veloce
git log --oneline --graph --decorate

# Output con grafico ASCII:
* a1b2c3d (HEAD -> main, origin/main) Aggiunta funzionalità di login
* b2c3d4e Correzione bug nel form
* c3d4e5f (tag: v1.0) Inizializzazione progetto
```

### 2. Cronologia Dettagliata
```bash
# Per analisi approfondita
git log --pretty=format:"%h - %an, %ar : %s"

# Output personalizzato:
a1b2c3d - Mario Rossi, 2 hours ago : Aggiunta funzionalità di login
b2c3d4e - Luigi Verdi, 1 day ago : Correzione bug nel form
c3d4e5f - Anna Blu, 2 days ago : Inizializzazione progetto
```

### 3. Cronologia con Contesto
```bash
# Mostra branch e merge nella cronologia
git log --graph --all --decorate --oneline
```

## 📊 Opzioni di Visualizzazione

### Informazioni di Base
| Opzione | Descrizione | Esempio |
|---------|-------------|---------|
| `--oneline` | Una riga per commit | `git log --oneline` |
| `--graph` | Mostra grafico ASCII | `git log --graph` |
| `--decorate` | Mostra reference (branch, tag) | `git log --decorate` |
| `--all` | Mostra tutti i branch | `git log --all` |

### Dettagli delle Modifiche
| Opzione | Descrizione | Utilizzo |
|---------|-------------|----------|
| `-p, --patch` | Mostra le modifiche complete | Revisione codice |
| `--stat` | Statistiche delle modifiche | Overview cambiamenti |
| `--shortstat` | Statistiche compatte | Summary veloce |
| `--name-only` | Solo nomi file modificati | Lista file |
| `--name-status` | File con stato (A/M/D) | Tracking modifiche |

### Controllo Output
```bash
# Paginazione automatica
git log | less

# Disabilitare pager
git --no-pager log --oneline

# Limitare righe output
git log --oneline -10
```

## 💡 Pattern di Utilizzo

### 1. Sviluppo Quotidiano
```bash
# Check rapido delle ultime modifiche
git log --oneline -10

# Vedere cosa è cambiato oggi
git log --since="1 day ago" --oneline

# Verificare le mie modifiche
git log --author="$(git config user.name)" --oneline
```

### 2. Revisione Codice
```bash
# Analisi completa di un commit
git log -1 -p <commit-hash>

# Vedere tutti i file modificati
git log --name-status --oneline -5

# Statistiche delle modifiche
git log --stat --oneline -3
```

### 3. Debug e Troubleshooting
```bash
# Cronologia di un file specifico
git log --follow -- filename.js

# Ricerca per messaggio
git log --grep="bug fix"

# Cronologia in un intervallo di date
git log --since="2024-01-01" --until="2024-01-31"
```

## 🚀 Esempi Pratici

### Scenario: Analisi Bug
```bash
# 1. Vedere gli ultimi commit
git log --oneline -10

# 2. Cercare commit relativi al bug
git log --grep="login" --oneline

# 3. Analizzare le modifiche specifiche
git log -p --since="1 week ago" -- src/auth/

# 4. Vedere chi ha modificato il file problematico
git log --follow -- src/auth/login.js
```

### Scenario: Preparazione Release
```bash
# 1. Cronologia dall'ultimo tag
git log v1.0..HEAD --oneline

# 2. Statistiche delle modifiche
git log v1.0..HEAD --stat

# 3. Elenco autori contributori
git log v1.0..HEAD --pretty=format:"%an" | sort | uniq

# 4. Cronologia formattata per changelog
git log v1.0..HEAD --pretty=format:"- %s (%h)"
```

## 🎨 Personalizzazione Base

### Alias Utili
```bash
# Configurare alias globali
git config --global alias.lg "log --oneline --graph --decorate"
git config --global alias.hist "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short"

# Utilizzo degli alias
git lg
git hist
```

### Format Personalizzati
```bash
# Log con colori e formattazione
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(green)(%cr)%C(reset) %s %C(blue)<%an>%C(reset)"

# Log con informazioni complete
git log --pretty=format:"%C(bold blue)%h%C(reset) - %C(bold green)%s%C(reset) %C(yellow)(%cr) %C(bold blue)<%an>%C(reset)%C(bold yellow)%d%C(reset)"
```

## ⚠️ Limitazioni e Considerazioni

### Performance con Repository Grandi
```bash
# Per repository con molti commit, limita l'output
git log --oneline -50

# Usa filtri per migliorare performance
git log --since="1 month ago"
```

### Output Leggibile
```bash
# Per output più leggibile in terminale
git log --color=always --graph --pretty=format:'%C(auto)%h%d %s %C(black)%C(bold)%cr'
```

### Navigazione Sicura
```bash
# Usa il pager per output lunghi
git config --global core.pager 'less -R'

# O disabilita per output brevi
git config --global pager.log false
```

## 🧪 Quiz di Verifica

### Domanda 1
Quale comando mostra una vista compatta della cronologia con grafico ASCII?
- A) `git log --stat`
- B) `git log --oneline --graph`
- C) `git log -p`
- D) `git log --decorate`

<details>
<summary>Risposta</summary>
**B) `git log --oneline --graph`**

L'opzione `--oneline` compatta ogni commit in una riga, mentre `--graph` aggiunge il grafico ASCII per visualizzare branch e merge.
</details>

### Domanda 2
Come vedere le modifiche effettive introdotte da ogni commit?
- A) `git log --stat`
- B) `git log --name-only`
- C) `git log -p`
- D) `git log --oneline`

<details>
<summary>Risposta</summary>
**C) `git log -p`**

L'opzione `-p` (o `--patch`) mostra le modifiche complete (diff) per ogni commit nella cronologia.
</details>

### Domanda 3
Quale comando limita la cronologia agli ultimi 3 commit?
- A) `git log --max-count=3`
- B) `git log -3`
- C) `git log --limit=3`
- D) Tutte le precedenti

<details>
<summary>Risposta</summary>
**B) `git log -3`**

Anche se tecnicamente `--max-count=3` funziona, la forma abbreviata `-3` è la più comune e concisa per limitare il numero di commit.
</details>

## 🔄 Prossimi Passi

Dopo aver appreso i fondamentali di `git log`, potrai:
1. **Esplorare opzioni di formattazione** avanzate
2. **Applicare filtri** per ricerche specifiche
3. **Utilizzare git show** per analisi dettagliate
4. **Creare alias personalizzati** per i tuoi workflow

---

**Continua con**: [02-Opzioni-Formattazione](./02-opzioni-formattazione.md) - Personalizzare l'output di git log
