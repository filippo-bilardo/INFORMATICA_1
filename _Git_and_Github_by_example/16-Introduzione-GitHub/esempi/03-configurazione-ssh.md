# Esempio: Configurazione SSH per GitHub

## Obiettivo
Guida pratica step-by-step per configurare l'autenticazione SSH con GitHub, inclusi scenari avanzati e troubleshooting.

## Scenario
Sei uno sviluppatore che vuole configurare l'accesso SSH sicuro a GitHub per evitare di inserire credenziali ad ogni operazione Git.

## Parte 1: Verifica Stato Attuale

### Check Configurazione Esistente
```bash
# Verifica se SSH già configurato
ssh -T git@github.com

# Possibili output:
# 1. "Hi username! You've successfully authenticated" ✅ GIÀ CONFIGURATO
# 2. "Permission denied (publickey)" ❌ NON CONFIGURATO
# 3. "Could not resolve hostname" ❌ PROBLEMI RETE
```

### Verifica Chiavi Esistenti
```bash
# Lista chiavi SSH presenti
ls -la ~/.ssh/

# File tipici che potresti vedere:
# id_rsa, id_rsa.pub        (RSA keys)
# id_ed25519, id_ed25519.pub (Ed25519 keys - preferite)
# config                     (SSH configuration)
# known_hosts               (Host verificati)

# Se directory non esiste
mkdir -p ~/.ssh
chmod 700 ~/.ssh
```

### Test Connessione Dettagliato
```bash
# Test con output verboso per debugging
ssh -vT git@github.com

# Output normale per GitHub:
# "Hi username! You've successfully authenticated, but GitHub does not
# provide shell access."
```

## Parte 2: Generazione Nuove Chiavi

### Chiave Ed25519 (Moderna e Sicura)
```bash
# Genera chiave Ed25519 - RACCOMANDATO
ssh-keygen -t ed25519 -C "your.email@example.com"

# Prompts interattivi:
# Enter file in which to save the key (/home/user/.ssh/id_ed25519): 
# [PREMI ENTER per default]

# Enter passphrase (empty for no passphrase): 
# [INSERISCI PASSWORD SICURA - raccomandato]

# Enter same passphrase again: 
# [CONFERMA PASSWORD]

# Output:
# Your identification has been saved in /home/user/.ssh/id_ed25519
# Your public key has been saved in /home/user/.ssh/id_ed25519.pub
```

### Chiave RSA (Se Ed25519 non supportato)
```bash
# Solo se sistema non supporta Ed25519
ssh-keygen -t rsa -b 4096 -C "your.email@example.com"

# Parametri:
# -t rsa: tipo RSA
# -b 4096: dimensione 4096 bit (più sicuro di 2048)
# -C: commento identificativo
```

### Chiavi Multiple per Account Diversi
```bash
# Chiave per account personale
ssh-keygen -t ed25519 -f ~/.ssh/github_personal -C "personal@email.com"

# Chiave per account lavoro
ssh-keygen -t ed25519 -f ~/.ssh/github_work -C "work@company.com"

# Chiave per progetti specifici
ssh-keygen -t ed25519 -f ~/.ssh/github_client -C "freelance@client.com"
```

## Parte 3: Configurazione SSH Agent

### Avvio SSH Agent
```bash
# Avvia SSH agent in background
eval "$(ssh-agent -s)"

# Output atteso:
# Agent pid 12345

# Verifica agent attivo
echo $SSH_AGENT_PID
```

### Aggiunta Chiavi all'Agent
```bash
# Aggiunge chiave principale
ssh-add ~/.ssh/id_ed25519

# Per chiavi con nomi personalizzati
ssh-add ~/.ssh/github_personal
ssh-add ~/.ssh/github_work

# Lista chiavi caricate
ssh-add -l

# Output esempio:
# 256 SHA256:abc123... your.email@example.com (ED25519)
```

### Configurazione Persistente macOS
```bash
# macOS: configura per caricare automaticamente
touch ~/.ssh/config
nano ~/.ssh/config

# Aggiungi:
Host *
    AddKeysToAgent yes
    UseKeychain yes
    IdentityFile ~/.ssh/id_ed25519

# Salva in keychain (solo macOS)
ssh-add --apple-use-keychain ~/.ssh/id_ed25519
```

### Configurazione Linux/WSL
```bash
# Script per avvio automatico SSH agent
echo 'eval "$(ssh-agent -s)"' >> ~/.bashrc
echo 'ssh-add ~/.ssh/id_ed25519' >> ~/.bashrc

# O crea script dedicato
nano ~/.ssh/start-agent.sh

#!/bin/bash
if [ -z "$SSH_AGENT_PID" ]; then
    eval "$(ssh-agent -s)"
    ssh-add ~/.ssh/id_ed25519
fi

chmod +x ~/.ssh/start-agent.sh
echo 'source ~/.ssh/start-agent.sh' >> ~/.bashrc
```

## Parte 4: Aggiunta Chiave a GitHub

### Copia Chiave Pubblica
```bash
# Ed25519
cat ~/.ssh/id_ed25519.pub

# RSA
cat ~/.ssh/id_rsa.pub

# Output simile a:
# ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIGqG8X... your.email@example.com

# Copia TUTTO l'output (incluso il commento finale)
```

### Via Interfaccia Web GitHub
1. **Login su GitHub.com**
2. **Settings** (click avatar → Settings)
3. **SSH and GPG keys** (sidebar sinistra)
4. **New SSH key** (pulsante verde)
5. **Compila form**:
   ```
   Title: Development Machine 2024
   Key type: Authentication Key
   Key: [INCOLLA_CHIAVE_PUBBLICA_COMPLETA]
   ```
6. **Add SSH key**
7. **Conferma con password** (se richiesto)

### Via GitHub CLI
```bash
# Installa GitHub CLI se non presente
# Ubuntu: sudo apt install gh
# macOS: brew install gh
# Windows: winget install GitHub.cli

# Login
gh auth login

# Aggiunge chiave corrente
gh ssh-key add ~/.ssh/id_ed25519.pub --title "Development Machine $(date +%Y-%m)"

# Lista chiavi presenti
gh ssh-key list

# Verifica chiave aggiunta
gh ssh-key view --web
```

## Parte 5: Test e Verifica

### Test Base
```bash
# Test connessione SSH
ssh -T git@github.com

# Output di successo:
# Hi username! You've successfully authenticated, but GitHub does not
# provide shell access.
```

### Test Dettagliato
```bash
# Test con debug verboso
ssh -vT git@github.com

# Cerca questi elementi nell'output:
# debug1: Offering public key: /home/user/.ssh/id_ed25519 RSA SHA256:...
# debug1: Server accepts key: pkalg rsa-sha2-512 blen 279
# debug1: Authentication succeeded (publickey)
```

### Test con Chiave Specifica
```bash
# Testa chiave specifica
ssh -T -i ~/.ssh/github_work git@github.com

# Verifica quale chiave viene usata
ssh -v git@github.com 2>&1 | grep "Offering public key"
```

## Parte 6: Configurazione Account Multipli

### File ~/.ssh/config Avanzato
```bash
nano ~/.ssh/config

# Account personale (default)
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519
    IdentitiesOnly yes

# Account lavoro
Host github-work
    HostName github.com
    User git
    IdentityFile ~/.ssh/github_work
    IdentitiesOnly yes

# Account cliente
Host github-client
    HostName github.com
    User git
    IdentityFile ~/.ssh/github_client
    IdentitiesOnly yes

# Configurazioni globali
Host *
    AddKeysToAgent yes
    UseKeychain yes  # Solo macOS
    ServerAliveInterval 60
    ServerAliveCountMax 30
```

### Utilizzo Account Multipli
```bash
# Clone con account default (personale)
git clone git@github.com:username/personal-repo.git

# Clone con account lavoro
git clone git@github-work:company/work-repo.git

# Clone con account cliente
git clone git@github-client:client/project-repo.git

# Verifica configurazione repository
cd work-repo
git remote -v
# origin  git@github-work:company/work-repo.git (fetch)
# origin  git@github-work:company/work-repo.git (push)
```

### Configurazione Git per Account Multipli
```bash
# Repository lavoro - configura email aziendale
cd work-repo
git config user.email "john.smith@company.com"
git config user.name "John Smith"

# Repository personale - email privata
cd personal-repo
git config user.email "john@personal.com"
git config user.name "John Smith"

# Verifica configurazione
git config user.email
```

## Parte 7: Troubleshooting Comune

### Permission Denied
```bash
# Problema: ssh -T git@github.com → Permission denied (publickey)

# Soluzioni:
# 1. Verifica SSH agent
ssh-add -l

# 2. Se "The agent has no identities"
ssh-add ~/.ssh/id_ed25519

# 3. Verifica chiave su GitHub
gh ssh-key list

# 4. Test con chiave specifica
ssh -T -i ~/.ssh/id_ed25519 git@github.com
```

### Chiave Non Accettata
```bash
# Problema: Chiave presente ma non funziona

# 1. Verifica formato file
file ~/.ssh/id_ed25519.pub
# Output: ASCII text

# 2. Verifica contenuto
head -c 50 ~/.ssh/id_ed25519.pub
# Deve iniziare con: ssh-ed25519 AAAAC3Nz...

# 3. Verifica permessi
ls -la ~/.ssh/id_ed25519*
# -rw------- id_ed25519      (600)
# -rw-r--r-- id_ed25519.pub  (644)

# 4. Correggi permessi se necessario
chmod 600 ~/.ssh/id_ed25519
chmod 644 ~/.ssh/id_ed25519.pub
```

### SSH Agent Issues
```bash
# Problema: Agent non risponde o non mantiene chiavi

# 1. Restart SSH agent
pkill ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# 2. Verifica configurazione
ssh-add -l

# 3. Per Ubuntu/Linux - installa keychain
sudo apt install keychain
echo 'eval `keychain --eval id_ed25519`' >> ~/.bashrc
```

### Host Key Verification Failed
```bash
# Problema: Host key verification failed

# 1. Reset known hosts per GitHub
ssh-keygen -R github.com

# 2. Riconnetti e accetta nuovo host key
ssh -T git@github.com
# Type 'yes' quando richiesto

# 3. Verifica fingerprint GitHub
# SHA256:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8 (RSA)
# SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM (ECDSA)
# SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU (Ed25519)
```

## Parte 8: Migrazione da HTTPS a SSH

### Repository Esistenti
```bash
# Verifica URL corrente
git remote -v

# Output possibile:
# origin  https://github.com/username/repo.git (fetch)
# origin  https://github.com/username/repo.git (push)

# Cambia a SSH
git remote set-url origin git@github.com:username/repo.git

# Verifica cambio
git remote -v
# origin  git@github.com:username/repo.git (fetch)
# origin  git@github.com:username/repo.git (push)

# Test con fetch
git fetch origin
```

### Script di Migrazione Automatica
```bash
#!/bin/bash
# migrate-to-ssh.sh

echo "🔄 Migrating repositories from HTTPS to SSH..."

# Trova tutti i repository Git
find . -name ".git" -type d | while read gitdir; do
    repo_dir=$(dirname "$gitdir")
    echo "Processing: $repo_dir"
    
    cd "$repo_dir"
    
    # Get current remote URL
    current_url=$(git remote get-url origin 2>/dev/null)
    
    if [[ $current_url == https://github.com/* ]]; then
        # Convert HTTPS to SSH
        ssh_url=$(echo "$current_url" | sed 's|https://github\.com/|git@github.com:|')
        git remote set-url origin "$ssh_url"
        echo "  ✅ Migrated: $ssh_url"
    else
        echo "  ⏭️  Skipped: $current_url"
    fi
    
    cd - > /dev/null
done

echo "✅ Migration complete!"
```

```bash
# Rendi eseguibile e lancia
chmod +x migrate-to-ssh.sh
./migrate-to-ssh.sh
```

## Parte 9: Best Practices Security

### Gestione Chiavi Sicura
```bash
# 1. Usa passphrase robuste
# Minimum 12 caratteri, caratteri misti
# Esempio: "MyGitHub2024!SSH#Key"

# 2. Rotazione chiavi periodica (ogni 1-2 anni)
# Genera nuova chiave
ssh-keygen -t ed25519 -C "rotation_2024@email.com"

# Aggiungi a GitHub
gh ssh-key add ~/.ssh/id_ed25519.pub --title "Key Rotation 2024"

# Rimuovi vecchia chiave
gh ssh-key delete [OLD_KEY_ID]

# 3. Backup sicuro chiavi
tar -czf ssh-backup-$(date +%Y%m%d).tar.gz ~/.ssh/
gpg -c ssh-backup-$(date +%Y%m%d).tar.gz
rm ssh-backup-$(date +%Y%m%d).tar.gz
# Store encrypted backup in secure location
```

### Monitoring e Audit
```bash
# 1. Verifica usage chiavi su GitHub
# GitHub.com → Settings → SSH keys → View usage

# 2. Log SSH connections (opzionale)
echo "LogLevel DEBUG1" >> ~/.ssh/config

# 3. Regular audit delle chiavi
gh ssh-key list
```

## Parte 10: Automation e Scripts

### Script di Verifica Giornaliera
```bash
#!/bin/bash
# ssh-health-check.sh

echo "🔍 SSH GitHub Health Check"
echo "=========================="

# Test connessione
if ssh -T git@github.com &>/dev/null; then
    echo "✅ SSH connection: OK"
else
    echo "❌ SSH connection: FAILED"
    echo "Run: ssh -T git@github.com"
fi

# Verifica agent
if ssh-add -l &>/dev/null; then
    echo "✅ SSH Agent: OK"
    echo "   Keys loaded: $(ssh-add -l | wc -l)"
else
    echo "❌ SSH Agent: No keys loaded"
    echo "Run: ssh-add ~/.ssh/id_ed25519"
fi

# Verifica permessi
key_perms=$(stat -c "%a" ~/.ssh/id_ed25519 2>/dev/null)
if [ "$key_perms" = "600" ]; then
    echo "✅ Key permissions: OK"
else
    echo "⚠️  Key permissions: $key_perms (should be 600)"
    echo "Run: chmod 600 ~/.ssh/id_ed25519"
fi

echo ""
echo "🔧 Quick fixes:"
echo "  SSH connection failed: ssh-add ~/.ssh/id_ed25519"
echo "  Agent not running: eval \"\$(ssh-agent -s)\""
echo "  Permission issues: chmod 600 ~/.ssh/id_ed25519"
```

### Setup Automatico per Nuove Macchine
```bash
#!/bin/bash
# github-ssh-setup.sh

set -e

echo "🚀 GitHub SSH Setup Automation"
echo "=============================="

# Variabili
EMAIL=${1:-"your.email@example.com"}
KEY_NAME="id_ed25519"
KEY_PATH="$HOME/.ssh/$KEY_NAME"

echo "📧 Email: $EMAIL"
echo "🔑 Key path: $KEY_PATH"

# Crea directory SSH
mkdir -p ~/.ssh
chmod 700 ~/.ssh

# Genera chiave se non esiste
if [ ! -f "$KEY_PATH" ]; then
    echo "🔑 Generating SSH key..."
    ssh-keygen -t ed25519 -f "$KEY_PATH" -C "$EMAIL" -N ""
    chmod 600 "$KEY_PATH"
    chmod 644 "$KEY_PATH.pub"
else
    echo "✅ SSH key already exists"
fi

# Avvia SSH agent
echo "🔧 Starting SSH agent..."
eval "$(ssh-agent -s)"
ssh-add "$KEY_PATH"

# Mostra chiave pubblica
echo ""
echo "📋 Your public key (copy this to GitHub):"
echo "========================================"
cat "$KEY_PATH.pub"
echo ""

# Apri GitHub settings se possibile
if command -v xdg-open &> /dev/null; then
    echo "🌐 Opening GitHub SSH settings..."
    xdg-open "https://github.com/settings/ssh/new"
elif command -v open &> /dev/null; then
    echo "🌐 Opening GitHub SSH settings..."
    open "https://github.com/settings/ssh/new"
fi

echo ""
echo "✅ Setup complete! Next steps:"
echo "1. Copy the public key above"
echo "2. Add it to GitHub SSH settings"
echo "3. Test with: ssh -T git@github.com"
```

## Checklist Finale

### Setup Completato ✅
- [ ] Chiave SSH generata (Ed25519 preferita)
- [ ] SSH agent configurato e attivo
- [ ] Chiave pubblica aggiunta a GitHub
- [ ] Test connessione SSH eseguito con successo
- [ ] Repository esistenti migrati da HTTPS a SSH

### Security ✅
- [ ] Passphrase robusta configurata
- [ ] Permessi file corretti (600 per private, 644 per public)
- [ ] SSH config file configurato appropriatamente
- [ ] Account multipli configurati (se necessario)

### Automation ✅
- [ ] SSH agent si avvia automaticamente
- [ ] Script di health check configurato
- [ ] Backup sicuro delle chiavi creato
- [ ] Plan di rotazione chiavi stabilito

## Prossimi Passi

Ora che hai configurato SSH:

1. **Esplora GitHub features** - [Esplorazione Features](./04-esplorazione-features.md)
2. **Crea primo repository** - [Repository Creation](../esercizi/02-repository-creation.md)
3. **Impara Git workflow** - [Clone Push Pull](../../17-Clone-Push-Pull/README.md)
4. **Setup GitHub Actions** - [GitHub Actions](../../21-GitHub-Actions-Intro/README.md)

## Risorse Aggiuntive

- [GitHub SSH Documentation](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
- [OpenSSH Configuration](https://www.openssh.com/manual.html)
- [SSH Security Best Practices](https://infosec.mozilla.org/guidelines/openssh)
