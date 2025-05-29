# Problemi di Autenticazione Git e GitHub

## Introduzione

L'autenticazione è uno degli ostacoli più comuni che gli sviluppatori incontrano lavorando con Git e GitHub. Questo documento fornisce soluzioni complete per tutti i problemi di autenticazione più frequenti.

## Categoria 1: Problemi HTTPS Authentication

### Problema 1.1: Password Authentication Removed

**Sintomi**:
```bash
git push origin main
# Username for 'https://github.com': username
# Password for 'https://username@github.com': 
# remote: Support for password authentication was removed on August 13, 2021.
# remote: Please use a personal access token instead.
```

**Causa**: GitHub ha rimosso il supporto per l'autenticazione tramite password per motivi di sicurezza.

**Soluzione Completa**:

```bash
# Metodo 1: Personal Access Token (PAT)
# 1. Crea un PAT su GitHub
# Settings > Developer settings > Personal access tokens > Generate new token

# 2. Configura il token nel repository
git remote set-url origin https://USERNAME:TOKEN@github.com/USERNAME/REPOSITORY.git

# 3. Oppure usa Git Credential Manager
git config --global credential.helper store
git push origin main
# Inserisci USERNAME e TOKEN quando richiesto

# Metodo 2: Switch to SSH (raccomandato)
# Vedi sezione SSH più avanti
```

### Problema 1.2: Token Scaduto o Invalido

**Sintomi**:
```bash
git push origin main
# remote: Invalid username or password.
# fatal: Authentication failed for 'https://github.com/...'
```

**Soluzione**:

```bash
# 1. Verifica validità token
curl -H "Authorization: token YOUR_TOKEN" https://api.github.com/user

# 2. Se scaduto, genera nuovo token su GitHub
# 3. Aggiorna credential store
git config --global --unset credential.helper
git config --global credential.helper store

# 4. Rimuovi credential cached
# macOS
git credential-osxkeychain erase
# Windows
git credential-manager-core erase
# Linux
rm ~/.git-credentials

# 5. Push di nuovo (inserisci nuovo token)
git push origin main
```

### Problema 1.3: Credential Helper Issues

**Sintomi**:
```bash
# Continua a chiedere credenziali ogni volta
git push
# Username for 'https://github.com': ...
```

**Diagnosi e Soluzione**:

```bash
# 1. Verifica configurazione corrente
git config --list | grep credential
git config --global --list | grep credential

# 2. Configura credential helper appropriato

# Per macOS:
git config --global credential.helper osxkeychain

# Per Windows:
git config --global credential.helper manager-core

# Per Linux:
git config --global credential.helper store
# oppure
git config --global credential.helper cache --timeout=3600

# 3. Test configurazione
git ls-remote origin
```

## Categoria 2: Problemi SSH Authentication

### Problema 2.1: SSH Key Non Configurata

**Sintomi**:
```bash
git clone git@github.com:user/repo.git
# Cloning into 'repo'...
# git@github.com: Permission denied (publickey).
# fatal: Could not read from remote repository.
```

**Soluzione Step-by-Step**:

```bash
# 1. Verifica chiavi SSH esistenti
ls -la ~/.ssh/
# Cerca file come id_rsa.pub, id_ed25519.pub

# 2. Se non esistono, crea nuova chiave SSH
ssh-keygen -t ed25519 -C "your_email@example.com"
# Premi Enter per default location
# Inserisci passphrase (opzionale ma raccomandato)

# 3. Avvia SSH agent
eval "$(ssh-agent -s)"

# 4. Aggiungi chiave all'agent
ssh-add ~/.ssh/id_ed25519

# 5. Copia chiave pubblica
# macOS:
pbcopy < ~/.ssh/id_ed25519.pub
# Linux:
cat ~/.ssh/id_ed25519.pub | xclip -selection clipboard
# Windows:
cat ~/.ssh/id_ed25519.pub | clip

# 6. Aggiungi chiave su GitHub
# Settings > SSH and GPG keys > New SSH key
# Incolla il contenuto e salva

# 7. Testa connessione
ssh -T git@github.com
# Hi username! You've successfully authenticated...
```

### Problema 2.2: Wrong SSH Host Key

**Sintomi**:
```bash
ssh -T git@github.com
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```

**Soluzione**:

```bash
# 1. Verifica se è GitHub legittimo
ssh-keygen -lf ~/.ssh/known_hosts | grep github.com

# 2. Se necessario, rimuovi vecchia entry
ssh-keygen -R github.com

# 3. Riconnetti e verifica fingerprint
ssh -T git@github.com
# Verifica che il fingerprint corrisponda a GitHub:
# SHA256:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8

# 4. Se corretto, accetta connessione
```

### Problema 2.3: Multiple SSH Keys Management

**Sintomi**: Hai più account GitHub (personale/lavoro) e le chiavi si confondono.

**Soluzione Avanzata**:

```bash
# 1. Crea SSH config file
touch ~/.ssh/config
chmod 600 ~/.ssh/config

# 2. Configura host separati
cat >> ~/.ssh/config << 'EOF'
# Personal GitHub account
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_personal
    IdentitiesOnly yes

# Work GitHub account
Host github-work
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_work
    IdentitiesOnly yes
EOF

# 3. Crea chiavi separate
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519_personal -C "personal@email.com"
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519_work -C "work@email.com"

# 4. Aggiungi chiavi all'agent
ssh-add ~/.ssh/id_ed25519_personal
ssh-add ~/.ssh/id_ed25519_work

# 5. Configura repository per usare host specifico
# Per repository personali:
git remote set-url origin git@github.com:username/repo.git

# Per repository di lavoro:
git remote set-url origin git@github-work:company/repo.git

# 6. Testa entrambe le connessioni
ssh -T git@github.com
ssh -T git@github-work
```

## Categoria 3: Problemi Permission e Access

### Problema 3.1: Repository Access Denied

**Sintomi**:
```bash
git clone https://github.com/private-org/private-repo.git
# Cloning into 'private-repo'...
# remote: Repository not found.
# fatal: repository 'https://github.com/...' not found
```

**Diagnosi e Soluzioni**:

```bash
# 1. Verifica esistenza repository
curl -s https://api.github.com/repos/owner/repo
# Se 404: repository non esiste o non hai accesso

# 2. Verifica il tuo accesso
curl -H "Authorization: token YOUR_TOKEN" \
     https://api.github.com/repos/owner/repo

# 3. Verifica collaborator status
curl -H "Authorization: token YOUR_TOKEN" \
     https://api.github.com/repos/owner/repo/collaborators/YOUR_USERNAME

# 4. Se sei collaboratore, assicurati di usare credenziali corrette
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 5. Per repository di organizzazioni, verifica SSO
# GitHub > Settings > Applications > Authorized OAuth Apps
# Trova e autorizza l'applicazione se necessario
```

### Problema 3.2: Organization SSO Requirements

**Sintomi**:
```bash
git push origin main
# remote: The `your-org` organization has enabled or enforced SAML SSO.
# remote: To access this repository, you must use the HTTPS clone URL and a personal access token with SSO enabled.
```

**Soluzione**:

```bash
# 1. Crea PAT con SSO enabled
# GitHub > Settings > Developer settings > Personal access tokens
# Generate new token > Enable SSO for organization

# 2. Autorizza il token per l'organizzazione
# Nel token settings, clicca "Enable SSO" per l'org specifica

# 3. Usa HTTPS con token
git remote set-url origin https://username:token@github.com/org/repo.git

# 4. Oppure configura SSH key per SSO
# Settings > SSH and GPG keys > Configure SSO per la chiave SSH
```

### Problema 3.3: Branch Protection Rules

**Sintomi**:
```bash
git push origin main
# remote: error: GH006: Protected branch update failed for refs/heads/main.
# remote: error: Required status check "ci/tests" is expected.
```

**Soluzione e Workaround**:

```bash
# 1. Verifica branch protection rules
curl -H "Authorization: token YOUR_TOKEN" \
     https://api.github.com/repos/owner/repo/branches/main/protection

# 2. Opzioni disponibili:
# a) Push to different branch e crea PR
git checkout -b feature/your-changes
git push origin feature/your-changes
# Poi crea Pull Request su GitHub

# b) Se hai admin access, bypass temporaneo
# (Solo per emergenze, non raccomandato)

# c) Soddisfa i requirements (status checks)
# Assicurati che CI/tests passino prima del push
```

## Categoria 4: Problemi Corporate e Firewall

### Problema 4.1: Corporate Firewall/Proxy

**Sintomi**:
```bash
git clone https://github.com/user/repo.git
# fatal: unable to access 'https://github.com/...': Failed to connect to github.com port 443
```

**Soluzione Completa**:

```bash
# 1. Configura proxy HTTP
git config --global http.proxy http://proxy.company.com:8080
git config --global https.proxy https://proxy.company.com:8080

# 2. Se proxy richiede autenticazione
git config --global http.proxy http://username:password@proxy.company.com:8080

# 3. Per SSL certificates issues
git config --global http.sslVerify false  # Solo per test, non produzione!

# 4. Alternative: SSH over HTTPS port
# Modifica ~/.ssh/config:
cat >> ~/.ssh/config << 'EOF'
Host github.com
    Hostname ssh.github.com
    Port 443
    User git
EOF

# 5. Test connessione SSH
ssh -T -p 443 git@ssh.github.com
```

### Problema 4.2: VPN/Network Changes

**Sintomi**: Autenticazione funziona a casa ma non in ufficio o viceversa.

**Soluzione**:

```bash
# 1. Verifica DNS resolution
nslookup github.com
dig github.com

# 2. Test connettività diretta
curl -I https://github.com
telnet github.com 443

# 3. Configura DNS alternativi se necessario
# macOS/Linux: /etc/resolv.conf
# Windows: Network settings

# 4. Flush DNS cache
# macOS:
sudo dscacheutil -flushcache
# Windows:
ipconfig /flushdns
# Linux:
sudo systemctl restart systemd-resolved

# 5. Se VPN interferisce con SSH
# Configura split tunneling o route specifiche
```

## Categoria 5: Advanced Authentication Issues

### Problema 5.1: Git Credential Manager Issues

**Sintomi**: Credenziali non salvate o credential manager non funziona.

**Diagnosi e Riparazione**:

```bash
# 1. Verifica installazione GCM
git credential-manager-core --version

# 2. Se non installato, scarica da GitHub releases
# https://github.com/microsoft/Git-Credential-Manager-Core/releases

# 3. Reinstalla configurazione
git config --global --unset-all credential.helper
git config --global credential.helper manager-core

# 4. Configura provider specifico
git config --global credential.https://github.com.provider github

# 5. Test e reset se necessario
git credential-manager-core erase
git credential-manager-core store
```

### Problema 5.2: Two-Factor Authentication Problems

**Sintomi**: 2FA abilitato ma git push fallisce.

**Soluzione**:

```bash
# Per HTTPS: usa PAT invece di password
# 1. Genera Personal Access Token
# 2. Usa token come password:
git push
# Username: your-username
# Password: your-personal-access-token

# Per SSH: nessun problema, SSH bypassa 2FA

# Per Git operations via API:
curl -H "Authorization: token YOUR_PAT" https://api.github.com/user
```

## Script di Diagnosi Automatica

### Comprehensive Auth Diagnostics

```bash
cat > ~/bin/git-auth-doctor << 'EOF'
#!/bin/bash

echo "🔍 Git Authentication Doctor"
echo "============================"
echo

# 1. Basic Git configuration
echo "📋 Git Configuration:"
echo "User: $(git config user.name) <$(git config user.email)>"
echo "Credential helper: $(git config credential.helper)"
echo

# 2. SSH configuration
echo "🔑 SSH Configuration:"
if [ -d ~/.ssh ]; then
    echo "SSH directory exists: ✅"
    echo "SSH keys found:"
    ls -la ~/.ssh/*.pub 2>/dev/null || echo "  No public keys found"
    
    # Test SSH to GitHub
    echo "Testing GitHub SSH connection..."
    if ssh -T git@github.com 2>&1 | grep -q "successfully authenticated"; then
        echo "GitHub SSH: ✅ Connected"
    else
        echo "GitHub SSH: ❌ Failed"
    fi
else
    echo "SSH directory: ❌ Not found"
fi
echo

# 3. HTTPS testing
echo "🌐 HTTPS Testing:"
if curl -s https://github.com >/dev/null; then
    echo "GitHub HTTPS: ✅ Accessible"
else
    echo "GitHub HTTPS: ❌ Failed"
fi

# 4. Repository specific tests
if git rev-parse --git-dir >/dev/null 2>&1; then
    echo
    echo "📁 Repository Tests:"
    echo "Current repository: $(basename $(pwd))"
    
    # Test remote access
    if git ls-remote origin >/dev/null 2>&1; then
        echo "Remote access: ✅ Working"
    else
        echo "Remote access: ❌ Failed"
        echo "Remote URL: $(git remote get-url origin 2>/dev/null || echo 'No remote configured')"
    fi
fi

echo
echo "🏥 Diagnostic complete"
EOF

chmod +x ~/bin/git-auth-doctor
```

### Authentication Repair Tool

```bash
cat > ~/bin/git-auth-repair << 'EOF'
#!/bin/bash

echo "🔧 Git Authentication Repair Tool"
echo "=================================="

echo "Select authentication method to repair:"
echo "1. HTTPS with Personal Access Token"
echo "2. SSH Key Setup"
echo "3. Corporate/Proxy Setup"
echo "4. Multiple Account Setup"
echo "5. Reset All Authentication"

read -p "Enter choice (1-5): " choice

case $choice in
    1)
        echo "🔐 Setting up HTTPS with PAT..."
        read -p "Enter GitHub username: " username
        read -s -p "Enter Personal Access Token: " token
        echo
        
        # Configure credential helper
        git config --global credential.helper store
        
        # Update remote URL if in repository
        if git rev-parse --git-dir >/dev/null 2>&1; then
            current_url=$(git remote get-url origin)
            new_url="https://$username:$token@${current_url#*://*/}"
            git remote set-url origin "$new_url"
            echo "✅ Repository remote updated"
        fi
        ;;
        
    2)
        echo "🗝️  Setting up SSH key..."
        read -p "Enter email for SSH key: " email
        
        # Generate SSH key
        ssh-keygen -t ed25519 -C "$email" -f ~/.ssh/id_ed25519_github
        
        # Start SSH agent and add key
        eval "$(ssh-agent -s)"
        ssh-add ~/.ssh/id_ed25519_github
        
        # Display public key
        echo "📋 Add this public key to GitHub:"
        cat ~/.ssh/id_ed25519_github.pub
        
        echo "🌐 Visit: https://github.com/settings/ssh/new"
        read -p "Press Enter after adding the key to GitHub..."
        
        # Test connection
        ssh -T git@github.com
        ;;
        
    3)
        echo "🏢 Setting up corporate/proxy configuration..."
        read -p "Enter proxy URL (e.g., http://proxy.company.com:8080): " proxy
        
        git config --global http.proxy "$proxy"
        git config --global https.proxy "$proxy"
        
        echo "✅ Proxy configured"
        ;;
        
    4)
        echo "👥 Setting up multiple account support..."
        # SSH config setup for multiple accounts
        # (Implementation would go here)
        ;;
        
    5)
        echo "🧹 Resetting all authentication..."
        git config --global --unset credential.helper
        git config --global --unset http.proxy
        git config --global --unset https.proxy
        
        # Clear credential stores
        rm -f ~/.git-credentials 2>/dev/null
        
        echo "✅ Authentication settings reset"
        ;;
esac

echo "🎉 Repair completed"
EOF

chmod +x ~/bin/git-auth-repair
```

---

## Best Practices per Evitare Problemi di Autenticazione

### Setup Sicuro Raccomandato

1. **Usa SSH invece di HTTPS quando possibile**
   - Più sicuro e conveniente
   - Non richiede inserimento credenziali
   - Supporta chiavi multiple

2. **Personal Access Token per HTTPS**
   - Usa scope minimi necessari
   - Imposta scadenza ragionevole
   - Non condividere mai i token

3. **Credential Manager configurato correttamente**
   - Evita inserimento credenziali ripetuto
   - Maggiore sicurezza

4. **Backup delle chiavi SSH**
   - Tieni backup sicuro delle chiavi private
   - Documenta quale chiave va con quale account

### Monitoraggio Sicurezza

```bash
# Controlla accessi SSH regolarmente
ssh-add -l

# Monitora token attivi su GitHub
# GitHub > Settings > Developer settings > Personal access tokens

# Controlla sessioni attive
# GitHub > Settings > Sessions
```

---

**🔒 Ricorda**: La sicurezza dell'autenticazione è fondamentale. Non compromettere mai la sicurezza per comodità, e aggiorna regolarmente le tue credenziali.
