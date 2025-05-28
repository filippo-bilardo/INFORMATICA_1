# 02 - Setup Account GitHub e Configurazione

## 📖 Spiegazione Concettuale

La configurazione corretta di GitHub è fondamentale per un workflow efficiente e sicuro. Include la creazione dell'account, la configurazione dell'autenticazione, l'impostazione del profilo e la connessione con il Git locale.

### Perché è Importante una Configurazione Corretta?

- **Sicurezza**: Protezione account e codice
- **Produttività**: Workflow fluido senza interruzioni
- **Professionalità**: Profilo attraente per recruiter
- **Collaborazione**: Facile identificazione nei progetti team

## 🚀 Creazione Account GitHub

### Step 1: Registrazione Base
```
1. Vai su github.com
2. Click "Sign up"
3. Inserisci:
   - Username (scegli con cura, rappresenta la tua identità)
   - Email (usa email professionale)
   - Password (forte e sicura)
4. Verifica email
5. Completa survey iniziale
```

### Scelta Username Strategica
```bash
# ✅ BUONI esempi:
john-smith-dev
maria.rossi
alex_codes
frontend-ninja

# ❌ CATTIVI esempi:
xXcoder123Xx
pizza_lover_42
temp_account
anonymous_user
```

### Step 2: Piano Account
```
GitHub Free (Consigliato per iniziare):
✅ Repository pubblici illimitati
✅ Repository privati illimitati (3 collaboratori max)
✅ GitHub Actions (2000 minuti/mese)
✅ Packages storage (500MB)
✅ Community support

GitHub Pro ($4/mese):
✅ Tutto di Free +
✅ Repository privati con collaboratori illimitati
✅ GitHub Actions (3000 minuti/mese)
✅ Protected branches
✅ Code owners
✅ Draft pull requests
```

## 🔐 Configurazione Autenticazione

### Metodo 1: Personal Access Token (PAT)

#### Creazione Token
```
1. GitHub → Settings → Developer settings
2. Personal access tokens → Tokens (classic)
3. Generate new token (classic)
4. Scopes da selezionare:
   ✅ repo (accesso completo ai repository)
   ✅ workflow (GitHub Actions)
   ✅ write:packages (per npm, Docker packages)
   ✅ delete_repo (se necessario)
5. Copia token (non lo vedrai più!)
```

#### Uso del Token
```bash
# Clone con token
git clone https://ghp_xxxxxxxxxxxx@github.com/username/repo.git

# Configure Git per usare token
git config --global credential.helper store
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# First push chiederà credenziali:
# Username: your-github-username
# Password: ghp_your_personal_access_token
```

### Metodo 2: SSH Keys (Raccomandato)

#### Generazione Chiave SSH
```bash
# 1. Genera nuova chiave SSH
ssh-keygen -t ed25519 -C "your.email@example.com"

# Quando chiede il file, premi Enter per default
# Quando chiede passphrase, inserisci una sicura (opzionale)

# 2. Avvia ssh-agent
eval "$(ssh-agent -s)"

# 3. Aggiungi chiave all'agent
ssh-add ~/.ssh/id_ed25519
```

#### Aggiunta Chiave a GitHub
```bash
# 1. Copia chiave pubblica
cat ~/.ssh/id_ed25519.pub
# Copy output to clipboard

# 2. Su GitHub:
# Settings → SSH and GPG keys → New SSH key
# Title: "My Laptop" (descrittivo)
# Key: paste your public key
# Add SSH key

# 3. Test connessione
ssh -T git@github.com
# Should see: "Hi username! You've successfully authenticated"
```

#### Clone con SSH
```bash
# Clone usando SSH (raccomandato)
git clone git@github.com:username/repository.git

# Change existing repo to SSH
git remote set-url origin git@github.com:username/repository.git
```

## 👤 Configurazione Profilo

### Profilo Base
```
Profile → Edit profile:

📸 Profile picture: Foto professionale (evita avatar, meme)
📝 Name: Nome reale o professionale
📍 Company: Azienda attuale o "Freelancer"
🌍 Location: Città, Paese
🔗 Website: Portfolio personale, LinkedIn
🐦 Twitter: Handle se professionale
📧 Email: Può essere nascosta
📄 Bio: Breve descrizione (160 caratteri max)
```

### Esempio Bio Efficace
```
🚀 Full Stack Developer | React & Node.js
🌱 Learning: TypeScript, AWS
💼 Open to collaboration
📍 Milan, Italy
```

### README Profilo Speciale
```bash
# Crea repository speciale username/username
# File README.md sarà mostrato nel tuo profilo

mkdir your-username
cd your-username
git init
```

```markdown
# README.md esempio
# 👋 Ciao, sono [Your Name]!

## 🚀 Chi sono
Sono uno sviluppatore appassionato con focus su tecnologie web moderne.

## 🛠️ Tecnologie che uso
![JavaScript](https://img.shields.io/badge/-JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black)
![React](https://img.shields.io/badge/-React-61DAFB?style=flat-square&logo=react&logoColor=black)
![Node.js](https://img.shields.io/badge/-Node.js-339933?style=flat-square&logo=node.js&logoColor=white)
![Git](https://img.shields.io/badge/-Git-F05032?style=flat-square&logo=git&logoColor=white)

## 📊 Le mie statistiche GitHub
![Your GitHub stats](https://github-readme-stats.vercel.app/api?username=yourusername&show_icons=true&theme=radical)

## 🌱 Sto imparando
- TypeScript
- AWS Cloud Services
- Docker & Kubernetes

## 📫 Come contattarmi
- 📧 Email: your.email@example.com
- 💼 LinkedIn: [Your LinkedIn](https://linkedin.com/in/yourprofile)
- 🌐 Portfolio: [yourwebsite.com](https://yourwebsite.com)

## ⚡ Fun fact
Adoro risolvere problemi complessi con soluzioni eleganti!
```

## ⚙️ Configurazione Git Locale

### Configurazione Base
```bash
# Configurazione globale Git
git config --global user.name "Your Real Name"
git config --global user.email "your.github.email@example.com"
git config --global init.defaultBranch main

# Editor preferito (opzionale)
git config --global core.editor "code --wait"  # VS Code
git config --global core.editor vim             # Vim
git config --global core.editor nano            # Nano

# Configurazioni utili
git config --global pull.rebase false  # Merge strategy for pull
git config --global push.default simple
git config --global core.autocrlf input  # Line endings (Mac/Linux)
git config --global core.autocrlf true   # Line endings (Windows)
```

### Verifica Configurazione
```bash
# Verifica tutte le configurazioni
git config --global --list

# Verifica configurazioni specifiche
git config --global user.name
git config --global user.email

# Test autenticazione GitHub
git ls-remote https://github.com/yourusername/yourrepo.git
```

### Configurazione Avanzata
```bash
# Aliases utili
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.cm commit
git config --global alias.lg "log --oneline --graph --all"

# Configurazione colori
git config --global color.ui auto

# Configurazione merge tool (opzionale)
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
```

## 🔧 Setup IDE e Strumenti

### VS Code Extensions
```json
// Extensions consigliate per Git/GitHub
{
  "recommendations": [
    "ms-vscode.vscode-git-graph",
    "eamodio.gitlens",
    "github.vscode-pull-request-github",
    "ms-vscode.github-browser",
    "github.copilot"
  ]
}
```

### GitHub CLI (gh)
```bash
# Installazione GitHub CLI
# macOS
brew install gh

# Windows
winget install GitHub.cli

# Ubuntu/Debian
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
sudo apt update
sudo apt install gh

# Autenticazione
gh auth login
# Scegli GitHub.com
# Scegli HTTPS o SSH
# Autenticati tramite browser
```

### Uso GitHub CLI
```bash
# Comandi utili gh
gh repo create my-new-repo --public
gh repo clone username/repository
gh pr list
gh pr create --title "My feature" --body "Description"
gh issue list
gh issue create --title "Bug report" --body "Bug description"
```

## 📱 GitHub Mobile App

### Setup App Mobile
```
1. Download GitHub app (iOS/Android)
2. Login con stesso account
3. Attiva notifiche per:
   ✅ Issues assigned to you
   ✅ Pull request reviews
   ✅ Mentions
   ❌ All repository activity (troppo noise)
```

### Funzionalità Mobile Utili
```
📱 Review e approve Pull Request
📝 Rispondere a commenti Issues
👀 Browse codice repository
🔔 Notifiche real-time
⭐ Star repository interessanti
```

## ⚠️ Errori Comuni Setup

### 1. **Email Configuration Mismatch**
```bash
# ❌ ERRORE: Email Git diversa da GitHub
git config --global user.email "different@email.com"
# Commit non saranno associati al tuo account

# ✅ SOLUZIONE: Stessa email di GitHub
git config --global user.email "your.github.email@example.com"
```

### 2. **Token con Permessi Insufficienti**
```bash
# ❌ ERRORE: Token senza scope necessari
# "remote: Permission to username/repo.git denied"

# ✅ SOLUZIONE: Rigenera token con scope corretti
# repo, workflow, write:packages
```

### 3. **SSH Key non Aggiunta all'Agent**
```bash
# ❌ ERRORE: "Permission denied (publickey)"
ssh -T git@github.com

# ✅ SOLUZIONE: Aggiungi key all'agent
ssh-add ~/.ssh/id_ed25519
```

### 4. **Nome Repository Case Sensitive**
```bash
# ❌ ERRORE: Clone case mismatch
git clone https://github.com/User/Repository.git  # U e R maiuscole
cd repository  # r minuscola

# ✅ ATTENZIONE: GitHub è case-sensitive per URL
```

## 🎯 Best Practices Setup

### 1. **Sicurezza Account**
```bash
# Abilita 2FA (Two-Factor Authentication)
# GitHub → Settings → Account security → Two-factor authentication
# Usa app come Authy, Google Authenticator

# Backup codes di recupero
# Salva in password manager sicuro
```

### 2. **Organizzazione Repository**
```bash
# Struttura directory locale
~/Development/
├── personal/          # Progetti personali
│   ├── portfolio/
│   └── learning/
├── work/             # Progetti lavoro
│   ├── company-app/
│   └── client-website/
└── opensource/       # Contributi open source
    ├── fork-project1/
    └── fork-project2/
```

### 3. **Convenzioni Naming**
```bash
# Repository naming
my-awesome-project     # kebab-case (raccomandato)
MyAwesomeProject      # PascalCase (ok per librerie)
my_awesome_project    # snake_case (evita)

# Branch naming
feature/user-authentication
bugfix/header-responsive
hotfix/security-patch
```

## 🧪 Quiz di Autovalutazione

**1. Quale metodo di autenticazione è più sicuro?**
- a) Username e password
- b) Personal Access Token
- c) SSH Keys con passphrase
- d) Sono tutti uguali

**2. Dove viene mostrato il README del repository username/username?**
- a) Solo nella pagina del repository
- b) Nel profilo GitHub dell'utente
- c) In tutti i repository
- d) Da nessuna parte

**3. Qual è il comando per testare l'autenticazione SSH?**
- a) `git test ssh`
- b) `ssh -T git@github.com`
- c) `github auth test`
- d) `git ssh --test`

**4. Cosa succede se l'email Git è diversa da quella GitHub?**
- a) Git non funziona
- b) I commit non vengono associati al profilo GitHub
- c) GitHub blocca i push
- d) Niente, funziona normalmente

<details>
<summary>🔍 Risposte</summary>

1. **c)** SSH Keys con passphrase
2. **b)** Nel profilo GitHub dell'utente
3. **b)** `ssh -T git@github.com`
4. **b)** I commit non vengono associati al profilo GitHub

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Setup Completo
1. Crea account GitHub (se non hai)
2. Genera SSH key e aggiungila a GitHub
3. Configura Git locale con nome ed email
4. Testa autenticazione

### Esercizio 2: Profilo Professionale
1. Completa profilo GitHub con foto e bio
2. Crea repository username/username
3. Scrivi README profilo accattivante
4. Aggiungi badges e statistiche

### Esercizio 3: Primo Repository
1. Crea nuovo repository "hello-github"
2. Clonalo localmente
3. Aggiungi file README.md
4. Commit e push

### Esercizio 4: GitHub CLI
1. Installa GitHub CLI
2. Autenticati con `gh auth login`
3. Crea repository da command line
4. Clona repository esistente

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [03 - Navigazione Interfaccia GitHub](03-navigazione-interfaccia.md)
- **Guida precedente**: [01 - GitHub Overview](01-github-overview.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 14-Risoluzione-Conflitti](../../14-Risoluzione-Conflitti/README.md)
- [➡️ 16-Clone-Push-Pull](../../16-Clone-Push-Pull/README.md)
