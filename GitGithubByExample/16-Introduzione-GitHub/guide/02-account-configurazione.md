# Guida 2: Setup Account e Configurazione

## Creazione Account GitHub

### Registrazione Base
1. **Vai su [github.com](https://github.com)**
2. **Clicca "Sign up"**
3. **Compila form**:
   - Username (scegli con cura, difficile cambiare)
   - Email (usane una professionale)
   - Password (forte e sicura)

### Scelta Username
**Buone pratiche:**
```
✅ Usa nome reale: john-smith, maria-rossi
✅ Consistente con altri social: @johnsmith everywhere
✅ Professionale: no "xXcoderXx" o "hackerman123"
✅ Breve e memorabile: max 20 caratteri

❌ Evita: numeri casuali, caratteri speciali eccessivi
❌ Non usare: nomi temporanei o scherzosi
```

### Verifica Email
```bash
# Importante per:
- Push su repository
- Notifiche GitHub
- Password recovery
- Two-factor authentication
```

## Configurazione Profilo

### Informazioni Base
```markdown
Profile essenziale:
- Nome completo
- Bio professionale (160 caratteri)
- Location (città o "Remote")
- Website/portfolio link
- Social media links
- Company/università
```

### Esempio Bio Professionale
```
Full-stack developer specializing in JavaScript and Python. 
Open source contributor. Building web apps that make a difference.
```

### Immagine Profilo
- **Dimensioni**: 420x420px minimo
- **Formato**: JPG, PNG, GIF
- **Tipo**: Foto professionale o avatar consistente
- **Evita**: Foto casuali, logo aziendali

## Impostazioni Account

### Account Settings
```
Settings > Account:
- Change username (attenzione!)
- Delete account
- Export account data
```

### Notification Settings
```markdown
Configura notifiche per:
- Watching repositories: Solo importante
- Participating and @mentions: Sempre
- Email notifications: Settimanali
- Web notifications: Instant per @mentions
```

### Privacy Settings
```markdown
Profile privacy:
- Private email: Nascondi email nei commit
- Private contributions: Nasconde attività private
- Profile README: Crea repository username/username
```

## Autenticazione e Sicurezza

### Two-Factor Authentication (2FA)
**Setup obbligatorio per sicurezza:**

1. **Settings > Password and authentication**
2. **Scegli metodo**:
   - App authenticator (Google Authenticator, Authy)
   - SMS (meno sicuro)
   - Security keys (più sicuro)

3. **Salva recovery codes** in luogo sicuro

### Personal Access Tokens
**Per accesso programmatico:**

```bash
# Crea token per sostituire password
Settings > Developer settings > Personal access tokens

# Scopes comuni:
repo          # Accesso repository privati
public_repo   # Accesso repository pubblici  
read:user     # Lettura profilo
admin:repo_hook # Gestione webhooks
```

**Esempio uso token:**
```bash
# Clone con token invece di password
git clone https://token@github.com/user/repo.git

# O configura credential helper
git config --global credential.helper store
```

### SSH Keys Setup
**Metodo preferito per sviluppatori:**

```bash
# 1. Genera chiave SSH
ssh-keygen -t ed25519 -C "your_email@example.com"

# 2. Aggiungi chiave a ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# 3. Copia chiave pubblica
cat ~/.ssh/id_ed25519.pub

# 4. Aggiungi su GitHub
# Settings > SSH and GPG keys > New SSH key
```

**Test connessione:**
```bash
ssh -T git@github.com
# Should return: Hi username! You've successfully authenticated
```

## Configurazione Git Locale

### User Configuration
```bash
# Configura identità (importante per commit)
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Verifica configurazione
git config --list --global
```

### Email Privacy
```bash
# Usa no-reply email GitHub per privacy
git config --global user.email "username@users.noreply.github.com"

# Trova tua no-reply email in Settings > Emails
```

### GPG Commit Signing
**Per commit verificati:**

```bash
# 1. Genera GPG key
gpg --full-generate-key

# 2. Lista keys
gpg --list-secret-keys --keyid-format=long

# 3. Esporta public key
gpg --armor --export KEY_ID

# 4. Aggiungi su GitHub (Settings > SSH and GPG keys)

# 5. Configura Git
git config --global user.signingkey KEY_ID
git config --global commit.gpgsign true
```

## Organizzazioni e Team

### Creare Organizzazione
```
Settings > Organizations > New organization

Utile per:
- Progetti aziendali
- Team development
- Repository condivisi
- Billing centralizzato
```

### Gestione Team
```markdown
Organization settings:
- Member privileges
- Base permissions
- Two-factor requirements
- Outside collaborators
- Security settings
```

## GitHub CLI Setup

### Installazione
```bash
# macOS
brew install gh

# Windows
winget install GitHub.cli

# Linux
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
```

### Autenticazione
```bash
# Login con browser
gh auth login

# Verifica status
gh auth status

# Configura git to use gh
gh auth setup-git
```

## Configurazioni Avanzate

### Default Repository Settings
```markdown
Settings > Repository defaults:
- Default branch name (main vs master)
- Repository template
- .gitignore template
- License template
```

### Billing e Piani
```markdown
Settings > Billing and plans:
- Current plan
- Usage tracking
- Payment methods
- Invoices
- Spending limits
```

### GitHub Apps
```markdown
Settings > Applications:
- Authorized GitHub Apps
- Authorized OAuth Apps
- Personal access tokens
- SSH keys
```

## Best Practices Setup

### Professional Profile
```markdown
Checklist profilo professionale:
- [ ] Username professionale
- [ ] Bio descrittiva
- [ ] Foto professionale
- [ ] Email verificata
- [ ] 2FA abilitato
- [ ] SSH keys configurate
- [ ] GPG signing (opzionale)
- [ ] README profilo creato
```

### Security Checklist
```markdown
Sicurezza account:
- [ ] Password forte e unica
- [ ] Two-factor authentication
- [ ] SSH keys invece di password
- [ ] Personal access tokens rotati
- [ ] Recovery codes salvati
- [ ] Email notifications attive
- [ ] Login sessions monitorate
```

### Development Setup
```markdown
Setup sviluppo:
- [ ] Git configurato localmente
- [ ] SSH keys per tutti i dispositivi
- [ ] GitHub CLI installato
- [ ] Editor configurato con GitHub
- [ ] Backup chiavi private
```

## Troubleshooting Comune

### Problemi Autenticazione
```bash
# SSH connection issues
ssh -vT git@github.com

# Token not working
git config --global --unset credential.helper
gh auth login

# Email not verified
# Check Settings > Emails
```

### Profile Issues
```bash
# Username change issues
# Note: Breaks existing links!
# Redirect only for 1 week

# 2FA recovery
# Use saved recovery codes
# Contact GitHub support as last resort
```

### Permission Problems
```bash
# Repository access denied
# Check: Repository permissions
# Check: Organization membership
# Check: SSH key configuration
```

## Migrazione da Altri Servizi

### Da GitLab
```bash
# GitHub provides migration tools
# Settings > Import repository
# Or use gh CLI:
gh repo create newrepo --source=gitlab.com/user/oldrepo
```

### Da Bitbucket
```bash
# Similar import process
# May need to manually migrate:
# - Issues
# - Pull requests  
# - Webhooks
```

## Prossimi Passi

Dopo setup iniziale:
1. **Crea primo repository** pubblico
2. **Fork repository** interessante
3. **Esplora GitHub** features
4. **Segui sviluppatori** interessanti
5. **Configura notifiche** appropriatamente

---

Un setup corretto è fondamentale per un'esperienza GitHub produttiva e sicura!
