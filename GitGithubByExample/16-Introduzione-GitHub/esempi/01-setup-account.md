# Esempio: Setup Account GitHub

## Obiettivo
Guida pratica completa per creare e configurare un account GitHub professionale, ottimizzato per sviluppo e collaborazione.

## Parte 1: Creazione Account

### Registrazione Base
1. **Vai su GitHub.com**
2. **Click "Sign up"**
3. **Compila i dati**:
   ```
   Username: scegli-username-professionale
   Email: your.professional@email.com
   Password: password-sicura-12-caratteri+
   ```
4. **Verifica email**
5. **Completa setup iniziale**

### Scelta Username Strategica
```bash
# ✅ BUONI esempi:
john-smith-dev
sarah-johnson
alex-martinez-js
maria-rossi-frontend

# ❌ EVITA:
coolcoder123
xXx_hacker_xXx
temporary-name
user12345
```

### Piano Account
```bash
# Free Account include:
✅ Repository pubblici illimitati
✅ Repository privati illimitati  
✅ GitHub Actions (2000 minuti/mese)
✅ GitHub Packages (500MB storage)
✅ Community support

# Pro Account ($4/mese) aggiunge:
✅ GitHub Copilot incluso
✅ Advanced Insights
✅ Protezioni branch avanzate
✅ Multiple reviewers
✅ Support prioritario
```

## Parte 2: Configurazione Profilo

### Informazioni Base
```bash
# Profile → Edit profile

Name: "John Smith"
Bio: "Full-Stack Developer | JavaScript, Python, React | Open Source Enthusiast"
Company: "Tech Company Inc."
Location: "Milan, Italy"
Website: "https://johnsmith.dev"
Twitter: "@johnsmith_dev"
```

### Avatar Professionale
- **Upload foto professionale** (non avatar/cartoon)
- **Risoluzione**: Minimum 400x400px
- **Formato**: JPG, PNG, GIF
- **Dimensione**: Max 1MB

### Profile README
```bash
# Crea repository speciale con tuo username
# Repository name: johnsmith (stesso del tuo username)
# File: README.md
```

**Esempio Profile README:**
```markdown
# Hi there! 👋 I'm John Smith

## About Me
🚀 Full-Stack Developer with 5+ years experience  
💼 Currently working at Tech Company Inc.  
🌱 Learning Rust and WebAssembly  
⚡ Fun fact: I love contributing to open source!

## 🛠️ Tech Stack
```javascript
const skills = {
    frontend: ['React', 'Vue.js', 'TypeScript', 'Tailwind CSS'],
    backend: ['Node.js', 'Python', 'Django', 'Express'],
    database: ['PostgreSQL', 'MongoDB', 'Redis'],
    tools: ['Docker', 'AWS', 'GitHub Actions', 'Jest']
};
```

## 📊 GitHub Stats
![John's GitHub stats](https://github-readme-stats.vercel.app/api?username=johnsmith&show_icons=true&theme=radical)

## 🤝 Let's Connect!
- 💼 [LinkedIn](https://linkedin.com/in/johnsmith)
- 🐦 [Twitter](https://twitter.com/johnsmith_dev)
- 🌐 [Portfolio](https://johnsmith.dev)
- 📧 [Email](mailto:john@example.com)
```

## Parte 3: Configurazione Security

### Two-Factor Authentication (2FA)
```bash
# Settings → Account security → Two-factor authentication

# Opzioni disponibili:
1. Authenticator app (Google Authenticator, Authy)
2. SMS (meno sicuro)
3. Security keys (YubiKey, etc.)

# Setup con Authenticator:
1. Download Google Authenticator
2. Scan QR code
3. Enter 6-digit code
4. Save recovery codes in posto sicuro!
```

### Security Keys (Raccomandato)
```bash
# Hardware security keys
- YubiKey 5 NFC (~$50)
- Google Titan Security Key (~$30)
- Feitian FIDO2 Keys (~$20)

# Setup:
Settings → Account security → Security keys
→ Register new security key
→ Insert key and touch when prompted
```

### Personal Access Tokens
```bash
# Per accesso API e CLI
Settings → Developer settings → Personal access tokens → Tokens (classic)

# Scopes necessari:
✅ repo (repository access)
✅ workflow (GitHub Actions)
✅ write:packages (GitHub Packages)
✅ read:user (user profile)
✅ user:email (email address)

# Genera token e salvalo sicuramente!
```

### SSH Keys Setup
```bash
# Genera SSH key (se non presente)
ssh-keygen -t ed25519 -C "your.email@example.com"

# Aggiungi a SSH agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# Copia chiave pubblica
cat ~/.ssh/id_ed25519.pub

# Aggiungi a GitHub
Settings → SSH and GPG keys → New SSH key
Title: "Development Machine 2024"
Key: [PASTE_PUBLIC_KEY]
```

## Parte 4: Configurazione Email

### Email Settings
```bash
Settings → Emails

# Configurazioni consigliate:
✅ Keep my email addresses private
✅ Block command line pushes that expose my email
✅ Receive all emails except those I unsubscribe from

# Email per commits:
Primary email: your.public@email.com
Noreply email: username@users.noreply.github.com
```

### Commit Email Privacy
```bash
# Configura Git per usare noreply email
git config --global user.email "username@users.noreply.github.com"

# Verifica configurazione
git config --global user.email
```

## Parte 5: Notification Settings

### Configurazione Notifications
```bash
Settings → Notifications

# Participating:
✅ Email ✅ Web
- When mentioned
- When involved in conversation
- When state changes

# Watching:
⚠️ Email ❌ Web ✅ 
- Per repository che segui attivamente

# Custom routing (opzionale):
Different email for different organizations
```

### GitHub Mobile App
```bash
# Download GitHub Mobile
- iOS: App Store
- Android: Google Play

# Setup notifications:
- Push notifications per mentions
- PR reviews
- Issue assignments
- Actions failures
```

## Parte 6: Organizazioni e Team

### Creare Organization
```bash
# Per team o aziende
Settings → Organizations → New organization

# Configurazione:
Organization name: "my-company-dev"
Billing email: "billing@company.com"
Plan: Free/Team/Enterprise

# Invita membri:
People → Invite member → username o email
```

### Team Management
```bash
# Crea team
Organization → Teams → New team

Team name: "Frontend Developers"
Description: "React and Vue.js development team"
Privacy: Visible/Secret

# Aggiungi membri e repository
Members → Add members
Repositories → Add repositories
```

## Parte 7: GitHub CLI Setup

### Installazione
```bash
# macOS
brew install gh

# Ubuntu/Debian
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
sudo apt update && sudo apt install gh

# Windows
winget install --id GitHub.cli
```

### Autenticazione
```bash
# Login interattivo
gh auth login

# Scegli:
1. GitHub.com
2. HTTPS
3. Authenticate Git with GitHub credentials: Yes
4. How to authenticate: Login with web browser

# Verifica
gh auth status
```

### Configurazione Base
```bash
# Set default editor
gh config set editor "code --wait"

# Set default protocol
gh config set git_protocol https

# View configuration
gh config list
```

## Parte 8: Repository Template

### Crea Repository Template Personale
```bash
# Repository per progetti standard
gh repo create my-project-template --public

cd my-project-template

# Struttura base
mkdir -p {src,tests,docs,.github/workflows}

# README template
echo "# {{PROJECT_NAME}}

## Description
{{PROJECT_DESCRIPTION}}

## Installation
\`\`\`bash
npm install
npm start
\`\`\`

## Usage
{{USAGE_INSTRUCTIONS}}

## Contributing
1. Fork the project
2. Create feature branch
3. Commit changes
4. Push to branch
5. Open Pull Request

## License
MIT License" > README.md

# .gitignore template
echo "node_modules/
.env
.env.local
.DS_Store
*.log
dist/
build/" > .gitignore

# GitHub Actions template
echo "name: CI

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    - uses: actions/setup-node@v3
      with:
        node-version: '18'
    - run: npm ci
    - run: npm test" > .github/workflows/ci.yml

# Commit e push
git add .
git commit -m "initial: project template setup"
git push origin main

# Converti in template
# Repository Settings → Template repository ✓
```

## Parte 9: Best Practices

### Profile Optimization
```markdown
✅ Professional username
✅ Real profile photo
✅ Complete bio with skills
✅ Contact information
✅ Pinned repositories showcase
✅ Regular contribution activity
✅ Descriptive commit messages
```

### Security Checklist
```markdown
✅ 2FA enabled (preferibilmente security key)
✅ SSH keys configured
✅ Email privacy enabled
✅ Personal access tokens restricted scope
✅ Regular security audit
✅ Strong, unique password
✅ Recovery codes backed up
```

### Professional Presence
```markdown
✅ Consistent branding across platforms
✅ Professional repository naming
✅ Clear README files
✅ Open source contributions
✅ Code quality focus
✅ Community engagement
✅ Documentation maintenance
```

## Parte 10: Advanced Configuration

### Git Global Config
```bash
# Nome e email
git config --global user.name "John Smith"
git config --global user.email "username@users.noreply.github.com"

# Editor e tool
git config --global core.editor "code --wait"
git config --global merge.tool "vscode"

# Aliases utili
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.cm commit
git config --global alias.pl pull
git config --global alias.ps push

# Line ending (Windows)
git config --global core.autocrlf true

# Line ending (Mac/Linux)  
git config --global core.autocrlf input
```

### GitHub CLI Aliases
```bash
# Shortcuts personalizzati
gh alias set pv 'pr view'
gh alias set pc 'pr create'
gh alias set pm 'pr merge'
gh alias set iv 'issue view'
gh alias set ic 'issue create'

# Workflow complex
gh alias set release 'release create --generate-notes'
gh alias set deploy 'workflow run deploy.yml'
```

## Troubleshooting Comune

### Authentication Issues
```bash
# Reset credentials
gh auth logout
gh auth login

# SSH key problems
ssh -T git@github.com
ssh-add -l

# Token permissions
# Rigenera token con scope corretti
```

### Profile Issues
```bash
# README non appare
# Verifica repository name = username
# Verifica file si chiama README.md
# Verifica repository è pubblico

# Stats non aggiornati
# GitHub aggiorna stats ogni 24h
# Verifica attività recente
```

## Checklist Finale

### Account Setup ✅
- [ ] Account creato con username professionale
- [ ] Profile photo professionale caricato
- [ ] Bio completo con skills e contatti
- [ ] Profile README creato e ottimizzato

### Security ✅
- [ ] 2FA abilitato (preferibilmente hardware key)
- [ ] SSH keys configurate e testate
- [ ] Email privacy abilitata
- [ ] Personal access tokens creati

### Tools ✅
- [ ] GitHub CLI installato e configurato
- [ ] Git global config impostato
- [ ] GitHub Mobile app installato
- [ ] VS Code extensions installate

### Professional Setup ✅
- [ ] Template repository creato
- [ ] Organizations/Teams configurati (se necessario)
- [ ] Notification settings ottimizzate
- [ ] Primo repository creato e pushato

## Prossimi Passi

Ora che hai configurato il tuo account GitHub:

1. **Configura SSH** per accesso sicuro - [Configurazione SSH](./03-configurazione-ssh.md)
2. **Esplora le features** - [Esplorazione Features](./04-esplorazione-features.md)
3. **Crea il primo repository** - [Repository Creation](../esercizi/02-repository-creation.md)
4. **Impara Git workflow** - [Clone Push Pull](../../17-Clone-Push-Pull/README.md)

## Risorse Aggiuntive

- [GitHub Profile Guide](https://docs.github.com/en/account-and-profile/setting-up-and-managing-your-github-profile)
- [GitHub Security Best Practices](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure)
- [GitHub CLI Documentation](https://cli.github.com/manual/)
