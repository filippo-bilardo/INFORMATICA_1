# 02 - Configurazione Identità Git

## 🎯 Obiettivo

Configurare correttamente la tua identità Git per assicurare che ogni commit sia attribuito a te e che le informazioni siano consistenti in tutti i tuoi progetti.

## 📚 Contenuti

### 1. Importanza dell'Identità Git

#### 🔑 **Perché Configurare l'Identità**
- **Tracciabilità**: Ogni commit deve essere attribuito a un autore
- **Collaborazione**: I colleghi sanno chi ha fatto cosa
- **Storia del progetto**: Mantiene un record accurato delle modifiche
- **GitHub/GitLab**: Collega i commit al tuo profilo

#### ⚠️ **Cosa Succede Senza Configurazione**
```bash
# Errore tipico
*** Please tell me who you are.

Run
  git config --global user.name "Your Name"
  git config --global user.email "you@example.com"
```

---

## 🔧 Configurazione Base dell'Identità

### 1. Nome Utente

```bash
# Configura il tuo nome (globalmente)
git config --global user.name "Mario Rossi"

# Verifica configurazione
git config --global user.name
# Output: Mario Rossi
```

#### 📝 **Linee Guida per il Nome**
- Usa il tuo **nome reale** (preferibile)
- **Evita** spazi extra o caratteri speciali
- **Consistenza** con il profilo GitHub/GitLab
- **Esempi validi**: "Mario Rossi", "M. Rossi", "MarioRossi"

### 2. Email

```bash
# Configura la tua email (globalmente)
git config --global user.email "mario.rossi@example.com"

# Verifica configurazione
git config --global user.email
# Output: mario.rossi@example.com
```

#### 📧 **Linee Guida per l'Email**
- **Stessa email** del tuo account GitHub/GitLab
- **Email valida** e che controlli regolarmente
- **Considera privacy**: GitHub può nascondere la tua email

---

## 🎚️ Livelli di Configurazione

Git ha tre livelli di configurazione con priorità diversa:

### 1. Sistema (--system)
```bash
# Configurazione per tutti gli utenti del sistema
sudo git config --system user.name "Default User"

# File: /etc/gitconfig (Linux/macOS)
#       C:\Program Files\Git\etc\gitconfig (Windows)
```

### 2. Globale (--global) - **Raccomandato**
```bash
# Configurazione per l'utente corrente
git config --global user.name "Mario Rossi"
git config --global user.email "mario@example.com"

# File: ~/.gitconfig (Linux/macOS)
#       C:\Users\username\.gitconfig (Windows)
```

### 3. Locale (--local o default)
```bash
# Configurazione per il repository corrente
cd /path/to/repository
git config user.name "Mario Rossi (Lavoro)"
git config user.email "mario@azienda.com"

# File: .git/config (nella cartella del repository)
```

### 🔄 **Priorità delle Configurazioni**
```
Local (repository) > Global (utente) > System (tutti)
```

---

## 🏢 Configurazioni Multiple (Lavoro vs Personale)

### Scenario: Email Diverse per Diversi Progetti

#### 1. Configurazione Globale di Default
```bash
# Email personale come default
git config --global user.name "Mario Rossi"
git config --global user.email "mario.personale@gmail.com"
```

#### 2. Override per Progetti Lavorativi
```bash
# Entra nella cartella del progetto lavorativo
cd ~/progetti-lavoro/app-aziendale

# Configura email lavorativa per questo repository
git config user.email "mario.rossi@azienda.com"
```

#### 3. Verifica Configurazioni
```bash
# Da qualsiasi parte (globale)
git config --global --list

# Da un repository specifico (tutte le config applicate)
git config --list
```

---

## 🔍 Gestione delle Configurazioni

### Visualizzare Configurazioni

```bash
# Tutte le configurazioni correnti
git config --list

# Solo configurazioni globali
git config --global --list

# Configurazione specifica
git config user.name
git config user.email

# Con informazioni su dove è definita
git config --show-origin user.name
```

### Modificare Configurazioni

```bash
# Modifica con editor
git config --global --edit

# Modifica valore specifico
git config --global user.name "Nuovo Nome"

# Rimuovi configurazione
git config --global --unset user.name
```

---

## 🔐 Configurazioni di Sicurezza e Privacy

### GitHub Email Privacy

GitHub offre email private per proteggere la privacy:

```bash
# Ottieni la tua email privata da GitHub
# Settings > Emails > "Keep my email addresses private"

# Esempio email privata GitHub
git config --global user.email "123456+username@users.noreply.github.com"
```

### Firma GPG (Avanzato)

```bash
# Lista chiavi GPG disponibili
gpg --list-secret-keys --keyid-format LONG

# Configura firma
git config --global user.signingkey YOUR_GPG_KEY_ID
git config --global commit.gpgsign true
```

---

## 🚨 Problemi Comuni e Soluzioni

### 1. Email Non Riconosciuta da GitHub

**Problema**: I commit non appaiono nel profilo GitHub
```bash
# Verifica email configurata
git config user.email

# Deve corrispondere a una delle email del tuo account GitHub
# GitHub Settings > Emails
```

### 2. Nome con Caratteri Speciali

**Problema**: Caratteri speciali nell'output Git
```bash
# Soluzione: Configura encoding
git config --global core.quotepath false
git config --global i18n.logoutputencoding utf-8
```

### 3. Configurazioni Inconsistenti

**Problema**: Diversi nomi/email in progetti diversi
```bash
# Audit di tutti i repository
find ~ -name ".git" -type d -exec dirname {} \; | while read repo; do
  echo "Repository: $repo"
  cd "$repo"
  echo "  Name: $(git config user.name)"
  echo "  Email: $(git config user.email)"
  echo
done
```

---

## 📋 Configurazione Raccomandata

### Setup Iniziale Completo

```bash
# Identità base
git config --global user.name "Il Tuo Nome"
git config --global user.email "tua@email.com"

# Editor (scegli uno)
git config --global core.editor "code --wait"    # VS Code
git config --global core.editor "nano"           # Nano (semplice)
git config --global core.editor "vim"            # Vim (avanzato)

# Comportamento line endings
git config --global core.autocrlf input          # Linux/macOS
git config --global core.autocrlf true           # Windows

# Colori nell'output
git config --global color.ui auto

# Default branch name
git config --global init.defaultBranch main
```

### Verifica Finale

```bash
# Controlla tutto
git config --list --show-origin

# Test pratico
cd /tmp
mkdir test-git && cd test-git
git init
echo "test" > file.txt
git add file.txt
git commit -m "Test commit"

# Verifica che il commit abbia i tuoi dati
git log --oneline --pretty=format:"%h %an <%ae> %s"
```

---

## 📋 Checklist Configurazione Identità

- [ ] Nome configurato (`git config user.name`)
- [ ] Email configurata (`git config user.email`)
- [ ] Email corrisponde al profilo GitHub/GitLab
- [ ] Test commit completato con successo
- [ ] Configurazioni verificate con `git config --list`

---

## 🔗 Prossimi Passi

✅ **Completato**: Configurazione identità base
🎯 **Prossimo**: [Configurazioni Avanzate](./03-configurazioni-avanzate.md)

---

## 📚 Risorse Aggiuntive

- [Git Configuration Docs](https://git-scm.com/docs/git-config)
- [GitHub Email Settings](https://docs.github.com/en/account-and-profile/setting-up-and-managing-your-github-user-account/managing-email-preferences)
- [Git Config Best Practices](https://git-scm.com/book/en/v2/Customizing-Git-Git-Configuration)
