# Opzioni di Formattazione

## 📖 Personalizzazione dell'Output

La formattazione dell'output di `git log` è fondamentale per adattare le informazioni alle tue esigenze specifiche. Git offre numerose opzioni per personalizzare cosa vedere e come visualizzarlo.

## 🎨 Pretty Format

### Formati Predefiniti
Git fornisce alcuni formati predefiniti pronti all'uso:

```bash
# Formato predefinito completo
git log --pretty=full

# Formato più compatto
git log --pretty=short

# Una sola riga (equivale a --oneline)
git log --pretty=oneline

# Formato con più dettagli
git log --pretty=fuller

# Formato raw (per parsing automatico)
git log --pretty=raw
```

### Confronto Formati Predefiniti
```bash
# Format: short
commit a1b2c3d4e5f6
Author: Mario Rossi <mario@email.com>

    Aggiunta funzionalità login

# Format: full
commit a1b2c3d4e5f6
Author: Mario Rossi <mario@email.com>
Commit: Mario Rossi <mario@email.com>

    Aggiunta funzionalità login

# Format: fuller
commit a1b2c3d4e5f6
Author:     Mario Rossi <mario@email.com>
AuthorDate: Mon Jan 15 14:30:25 2024 +0100
Commit:     Mario Rossi <mario@email.com>
CommitDate: Mon Jan 15 14:30:25 2024 +0100

    Aggiunta funzionalità login
```

## 🔧 Format Personalizzati

### Sintassi del Format String
```bash
git log --pretty=format:"<format-string>"
```

### Placeholder Essenziali

#### Informazioni Commit
| Placeholder | Descrizione | Esempio |
|-------------|-------------|---------|
| `%H` | Hash completo commit | `a1b2c3d4e5f6g7h8...` |
| `%h` | Hash abbreviato commit | `a1b2c3d` |
| `%T` | Hash albero | `4b825dc642cb6...` |
| `%t` | Hash albero abbreviato | `4b825dc` |
| `%P` | Hash parent | `1234567890abcdef...` |
| `%p` | Hash parent abbreviato | `1234567` |

#### Informazioni Autore
| Placeholder | Descrizione | Esempio |
|-------------|-------------|---------|
| `%an` | Nome autore | `Mario Rossi` |
| `%ae` | Email autore | `mario@email.com` |
| `%ad` | Data autore | `Mon Jan 15 14:30:25 2024` |
| `%ar` | Data autore relativa | `2 hours ago` |
| `%ai` | Data autore ISO | `2024-01-15 14:30:25 +0100` |

#### Informazioni Committer
| Placeholder | Descrizione | Esempio |
|-------------|-------------|---------|
| `%cn` | Nome committer | `Luigi Verdi` |
| `%ce` | Email committer | `luigi@email.com` |
| `%cd` | Data commit | `Mon Jan 15 14:35:00 2024` |
| `%cr` | Data commit relativa | `2 hours ago` |
| `%ci` | Data commit ISO | `2024-01-15 14:35:00 +0100` |

#### Contenuto e Metadati
| Placeholder | Descrizione | Utilizzo |
|-------------|-------------|----------|
| `%s` | Oggetto (prima riga messaggio) | Titolo commit |
| `%f` | Oggetto sanitized per filename | Per automazione |
| `%b` | Corpo messaggio | Descrizione dettagliata |
| `%B` | Messaggio completo (raw) | Tutto il messaggio |
| `%d` | Ref names (branch, tag) | `(HEAD -> main, origin/main)` |
| `%D` | Ref names senza wrapping | `HEAD -> main, origin/main` |

## 🌈 Colori e Styling

### Codici Colore Base
```bash
# Colori disponibili
%C(red)     # Rosso
%C(green)   # Verde
%C(blue)    # Blu
%C(yellow)  # Giallo
%C(magenta) # Magenta
%C(cyan)    # Ciano
%C(white)   # Bianco
%C(black)   # Nero
%C(reset)   # Reset al colore default
```

### Stili di Testo
```bash
%C(bold)      # Grassetto
%C(dim)       # Attenuato
%C(ul)        # Sottolineato
%C(blink)     # Lampeggiante
%C(reverse)   # Invertito
```

### Colori Automatici
```bash
%C(auto)      # Git sceglie il colore appropriato
%C(always)    # Forza sempre i colori
%C(never)     # Mai i colori
```

## 🎯 Esempi di Formattazione

### 1. Format Compatto e Colorato
```bash
git log --pretty=format:"%C(yellow)%h%C(reset) - %C(green)(%cr)%C(reset) %s %C(blue)<%an>%C(reset)"

# Output:
a1b2c3d - (2 hours ago) Aggiunta funzionalità login <Mario Rossi>
b2c3d4e - (1 day ago) Correzione bug form <Luigi Verdi>
```

### 2. Format Dettagliato per Revisioni
```bash
git log --pretty=format:"%C(bold blue)%h%C(reset) - %C(bold green)%s%C(reset)%n%C(white)Author: %an <%ae>%C(reset)%n%C(white)Date: %ad%C(reset)%n" --date=short

# Output:
a1b2c3d - Aggiunta funzionalità login
Author: Mario Rossi <mario@email.com>
Date: 2024-01-15
```

### 3. Format Stile GitHub
```bash
git log --pretty=format:"%C(bold yellow)%h%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset) %C(green)(%cr)%C(reset)%C(auto)%d%C(reset)"

# Output simile a GitHub
a1b2c3d Aggiunta funzionalità login - Mario Rossi (2 hours ago) (HEAD -> main)
```

### 4. Format per Changelog
```bash
git log --pretty=format:"- %s (%h) - %an, %ar"

# Output per documenti
- Aggiunta funzionalità login (a1b2c3d) - Mario Rossi, 2 hours ago
- Correzione bug form (b2c3d4e) - Luigi Verdi, 1 day ago
```

## 📊 Opzioni di Data

### Formati Data Disponibili
```bash
# Data relativa (default)
git log --date=relative
# Output: 2 hours ago, 3 days ago

# Data breve
git log --date=short
# Output: 2024-01-15

# Data ISO
git log --date=iso
# Output: 2024-01-15 14:30:25 +0100

# Data RFC
git log --date=rfc
# Output: Mon, 15 Jan 2024 14:30:25 +0100

# Data raw (timestamp)
git log --date=raw
# Output: 1705327825 +0100

# Data locale
git log --date=local
# Output: Mon Jan 15 14:30:25 2024

# Data formato custom
git log --date=format:'%Y-%m-%d %H:%M'
# Output: 2024-01-15 14:30
```

### Data Custom con strftime
```bash
# Formato europeo
git log --date=format:'%d/%m/%Y %H:%M' --pretty=format:"%h - %s (%ad)"

# Formato americano
git log --date=format:'%m/%d/%Y %I:%M %p' --pretty=format:"%h - %s (%ad)"

# Solo data
git log --date=format:'%A, %B %d, %Y' --pretty=format:"%h - %s (%ad)"
# Output: Monday, January 15, 2024
```

## 🎭 Combinazioni Avanzate

### 1. Log con Grafico e Colori
```bash
git log --graph --pretty=format:'%C(red)%h%C(reset) -%C(yellow)%d%C(reset) %s %C(green)(%cr) %C(bold blue)<%an>%C(reset)' --abbrev-commit --all
```

### 2. Format per Debugging
```bash
git log --pretty=format:"%C(yellow)%h%C(reset) %C(bold)%s%C(reset)%n%C(blue)Author: %an <%ae>%C(reset)%n%C(green)Date: %ad%C(reset)%n%C(red)Files changed:%C(reset)" --stat --date=short
```

### 3. One-liner Informativo
```bash
git log --pretty=format:"%C(cyan)%h%C(reset) %C(bold)%s%C(reset) %C(yellow)- %an%C(reset) %C(green)(%ar)%C(reset)%C(auto)%d%C(reset)" --oneline
```

## ⚙️ Configurazione Permanente

### Alias per Formati Personalizzati
```bash
# Configurare alias globali
git config --global alias.lg1 "log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --all"

git config --global alias.lg2 "log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(bold yellow)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)' --all"

# Uso degli alias
git lg1
git lg2
```

### Configurazione Pretty Format Default
```bash
# Impostare formato default per log
git config --global format.pretty "format:%C(yellow)%h%C(reset) - %C(green)(%cr)%C(reset) %s %C(blue)<%an>%C(reset)"
```

## 📱 Adattamento per Terminali

### Per Terminali con Colori Limitati
```bash
# Formato senza colori per compatibilità
git log --pretty=format:"%h - (%cr) %s <%an>"

# Controllo automatico dei colori
git config --global color.ui auto
```

### Per Output su File
```bash
# Rimuovere colori per redirezione
git --no-pager log --pretty=format:"%h - %s - %an, %ar" > changelog.txt

# O disabilitare colori specificamente
git log --no-color --pretty=format:"%h - %s - %an, %ar"
```

## 🧩 Template Completi

### Template Sviluppo
```bash
# Per uso quotidiano
git config --global alias.dev "log --oneline --graph --decorate --color=always --pretty=format:'%C(auto)%h%d %s %C(black)%C(bold)%cr'"
```

### Template Review
```bash
# Per revisioni codice
git config --global alias.review "log --stat --pretty=format:'%C(bold yellow)commit %H%C(reset)%nAuthor: %an <%ae>%nDate: %ad%n%n%w(80,4,4)%s%n%n%b' --date=short"
```

### Template Release
```bash
# Per note di rilascio
git config --global alias.release "log --pretty=format:'- %s (%h)' --reverse"
```

## 🧪 Quiz di Verifica

### Domanda 1
Quale placeholder mostra la data del commit in formato relativo?
- A) `%ad`
- B) `%cr`
- C) `%cd`
- D) `%ar`

<details>
<summary>Risposta</summary>
**B) `%cr`**

`%cr` mostra la data del commit in formato relativo (es. "2 hours ago"), mentre `%ar` è per la data dell'autore.
</details>

### Domanda 2
Come si resetta il colore al default in un format string?
- A) `%C(default)`
- B) `%C(reset)`
- C) `%C(normal)`
- D) `%C(clear)`

<details>
<summary>Risposta</summary>
**B) `%C(reset)`**

`%C(reset)` riporta il colore alle impostazioni di default del terminale.
</details>

### Domanda 3
Quale comando crea un formato che mostra hash, messaggio e autore colorati?
- A) `git log --pretty=format:"%h - %s <%an>"`
- B) `git log --pretty=format:"%C(yellow)%h%C(reset) - %s %C(blue)<%an>%C(reset)"`
- C) `git log --color --oneline`
- D) Entrambe A e B

<details>
<summary>Risposta</summary>
**B) `git log --pretty=format:"%C(yellow)%h%C(reset) - %s %C(blue)<%an>%C(reset)"`**

La opzione B include i codici colore per evidenziare hash in giallo e autore in blu, mentre A non ha colori.
</details>

## 🔄 Prossimi Passi

Ora che conosci le opzioni di formattazione, puoi:
1. **Applicare filtri** per cercare commit specifici
2. **Combinare formattazione con git show** per analisi dettagliate
3. **Creare alias personalizzati** per i tuoi workflow
4. **Utilizzare strumenti grafici** per visualizzazioni avanzate

---

**Continua con**: [03-Filtri-Ricerche](./03-filtri-ricerche.md) - Filtrare e cercare nella cronologia
