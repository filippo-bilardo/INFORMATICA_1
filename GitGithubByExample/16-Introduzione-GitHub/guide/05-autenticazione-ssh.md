# Guida: Autenticazione SSH

## Introduzione
L'autenticazione SSH (Secure Shell) permette di connettersi a GitHub in modo sicuro senza dover inserire username e password ad ogni operazione Git.

## Perché Usare SSH

### Vantaggi
- **Sicurezza**: Crittografia a chiave pubblica/privata
- **Convenienza**: Nessuna password da digitare
- **Automazione**: Ideale per script e CI/CD
- **Performance**: Connessioni più veloci
- **2FA Compatible**: Funziona anche con autenticazione a due fattori

### HTTPS vs SSH
```bash
# HTTPS (richiede autenticazione ogni volta)
git clone https://github.com/username/repo.git

# SSH (autenticazione automatica con chiavi)
git clone git@github.com:username/repo.git
```

## Verifica Chiavi Esistenti

### Controllo Chiavi Presenti
```bash
# Lista chiavi SSH esistenti
ls -la ~/.ssh

# File tipici:
# id_rsa         (chiave privata RSA)
# id_rsa.pub     (chiave pubblica RSA)
# id_ed25519     (chiave privata Ed25519 - più moderna)
# id_ed25519.pub (chiave pubblica Ed25519)
# known_hosts    (server verificati)
# config         (configurazione SSH)
```

### Test Connessione GitHub
```bash
# Testa se SSH già configurato
ssh -T git@github.com

# Output atteso se configurato:
# Hi username! You've successfully authenticated, but GitHub does not provide shell access.

# Se non configurato:
# Permission denied (publickey).
```

## Generazione Nuove Chiavi SSH

### Chiave Ed25519 (Raccomandato)
```bash
# Genera nuova chiave Ed25519
ssh-keygen -t ed25519 -C "your_email@example.com"

# Prompt interattivi:
# Enter file in which to save the key (/home/user/.ssh/id_ed25519): [ENTER]
# Enter passphrase (empty for no passphrase): [PASSWORD_OPZIONALE]
# Enter same passphrase again: [CONFERMA_PASSWORD]
```

### Chiave RSA (Alternative)
```bash
# Se sistema non supporta Ed25519
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

# -t rsa: tipo RSA
# -b 4096: dimensione chiave 4096 bit
# -C: commento (solitamente email)
```

### Con Passphrase Personalizzata
```bash
# Specifica file e passphrase
ssh-keygen -t ed25519 -f ~/.ssh/github_key -C "github@mycompany.com"

# Per progetti specifici
ssh-keygen -t ed25519 -f ~/.ssh/project_specific_key
```

## Aggiunta Chiave all'SSH Agent

### Avvio SSH Agent
```bash
# Avvia SSH agent in background
eval "$(ssh-agent -s)"

# Output: Agent pid 12345
```

### Aggiunta Chiave Privata
```bash
# Aggiunge chiave Ed25519
ssh-add ~/.ssh/id_ed25519

# Aggiunge chiave RSA
ssh-add ~/.ssh/id_rsa

# Aggiunge con passphrase prompt
ssh-add ~/.ssh/github_key

# Lista chiavi caricate
ssh-add -l
```

### Configurazione macOS
```bash
# macOS: aggiorna ~/.ssh/config
touch ~/.ssh/config
nano ~/.ssh/config

# Contenuto:
Host *
  AddKeysToAgent yes
  UseKeychain yes
  IdentityFile ~/.ssh/id_ed25519
```

## Aggiunta Chiave a GitHub

### Via Interfaccia Web
1. **Copia chiave pubblica**:
   ```bash
   # Ed25519
   cat ~/.ssh/id_ed25519.pub
   
   # RSA
   cat ~/.ssh/id_rsa.pub
   
   # Output sarà simile a:
   # ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIGqe... your_email@example.com
   ```

2. **GitHub Settings**:
   - Vai su GitHub.com → Settings
   - Click "SSH and GPG keys"
   - Click "New SSH key"
   - Title: "My Development Machine"
   - Key: [INCOLLA_CHIAVE_PUBBLICA]
   - Click "Add SSH key"

### Via GitHub CLI
```bash
# Installa GitHub CLI se non presente
# macOS: brew install gh
# Windows: scoop install gh

# Login
gh auth login

# Aggiunge chiave corrente
gh ssh-key add ~/.ssh/id_ed25519.pub --title "Development Machine"

# Lista chiavi
gh ssh-key list
```

## Test Configurazione

### Verifica Connessione
```bash
# Test completo
ssh -T git@github.com

# Con debug verboso
ssh -vT git@github.com

# Specifica chiave specifica
ssh -T -i ~/.ssh/specific_key git@github.com
```

### Output di Successo
```bash
$ ssh -T git@github.com
Hi username! You've successfully authenticated, but GitHub does not provide shell access.
```

### Troubleshooting Test
```bash
# Se errori, debug verbose
ssh -vvv git@github.com

# Controlla agent
ssh-add -l

# Verifica permessi file
ls -la ~/.ssh/
# Chiavi private: 600 (rw-------)
# Chiavi pubbliche: 644 (rw-r--r--)
# Directory .ssh: 700 (rwx------)
```

## Configurazione Multipla

### File ~/.ssh/config
```bash
# Configurazione per account multipli
nano ~/.ssh/config

# Account personale
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519

# Account lavoro
Host github-work
    HostName github.com
    User git
    IdentityFile ~/.ssh/work_key

# Account cliente specifico
Host github-client
    HostName github.com
    User git
    IdentityFile ~/.ssh/client_key
    IdentitiesOnly yes
```

### Utilizzo Account Multipli
```bash
# Clone con account default
git clone git@github.com:username/repo.git

# Clone con account lavoro
git clone git@github-work:company/repo.git

# Clone con account cliente
git clone git@github-client:client/repo.git

# Configura repository esistente
git remote set-url origin git@github-work:company/repo.git
```

## Gestione Chiavi Avanzata

### Rotazione Chiavi
```bash
# Genera nuova chiave
ssh-keygen -t ed25519 -C "new_email@example.com" -f ~/.ssh/id_ed25519_new

# Aggiunge a GitHub (via web o CLI)
gh ssh-key add ~/.ssh/id_ed25519_new.pub --title "New Key 2024"

# Testa nuova chiave
ssh -T -i ~/.ssh/id_ed25519_new git@github.com

# Rimuovi vecchia chiave da GitHub
gh ssh-key delete [OLD_KEY_ID]

# Sostituisci file chiave
mv ~/.ssh/id_ed25519_new ~/.ssh/id_ed25519
mv ~/.ssh/id_ed25519_new.pub ~/.ssh/id_ed25519.pub
```

### Backup Chiavi
```bash
# Backup sicuro chiavi
tar -czf ssh_backup_$(date +%Y%m%d).tar.gz ~/.ssh/
gpg -c ssh_backup_$(date +%Y%m%d).tar.gz

# Store in secure location (not in git repo!)
```

### Expiry e Automazione
```bash
# Chiave con scadenza (using OpenSSH 8.2+)
ssh-keygen -t ed25519 -V +52w -C "expires_in_1_year@example.com"

# Script di rotazione automatica
#!/bin/bash
# rotate_ssh_key.sh

KEY_PATH="$HOME/.ssh/id_ed25519"
BACKUP_PATH="$HOME/.ssh/backup"

# Backup old key
mkdir -p $BACKUP_PATH
cp $KEY_PATH $BACKUP_PATH/id_ed25519_$(date +%Y%m%d)

# Generate new key
ssh-keygen -t ed25519 -f $KEY_PATH -N "" -C "auto_generated_$(date +%Y%m%d)"

# Add to agent
ssh-add $KEY_PATH

echo "New SSH key generated. Update GitHub manually."
```

## Sicurezza Best Practices

### Protezione Chiavi
```bash
# Permessi corretti
chmod 700 ~/.ssh
chmod 600 ~/.ssh/id_ed25519
chmod 644 ~/.ssh/id_ed25519.pub
chmod 600 ~/.ssh/config

# Mai condividere chiave privata
# Mai committare chiavi in repository
echo "/.ssh/" >> ~/.gitignore_global
```

### Passphrase Sicure
```bash
# Usa passphrase robuste per chiavi
# Minimum 12 caratteri, misto
# Esempio: "MyGitHub2024!SSH"

# Cambio passphrase esistente
ssh-keygen -p -f ~/.ssh/id_ed25519
```

### Monitoraggio
```bash
# Controlla usage chiavi su GitHub
# Settings → SSH keys → View usage history

# Alert per nuove chiavi
# Settings → Security → Enable notifications
```

## Troubleshooting Comune

### Permission Denied
```bash
# Verifica chiave corretta
ssh-add -l

# Ricarica chiave
ssh-add ~/.ssh/id_ed25519

# Verifica configurazione
ssh -T git@github.com
```

### Agent Non Risponde
```bash
# Restart SSH agent
pkill ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
```

### Chiave Non Accettata
```bash
# Verifica formato chiave
file ~/.ssh/id_ed25519.pub

# Rigenera se corrotta
ssh-keygen -t ed25519 -C "your_email@example.com"
```

### Host Key Verification Failed
```bash
# Reset known_hosts per GitHub
ssh-keygen -R github.com

# Riconnetti e accetta nuova chiave
ssh -T git@github.com
```

## Migrazione da HTTPS a SSH

### Repository Esistenti
```bash
# Verifica remote corrente
git remote -v

# Cambia da HTTPS a SSH
git remote set-url origin git@github.com:username/repository.git

# Verifica cambio
git remote -v

# Test con fetch
git fetch origin
```

### Script di Migrazione
```bash
#!/bin/bash
# migrate_to_ssh.sh

for repo in $(find . -name ".git" -type d); do
    cd $(dirname $repo)
    
    # Get current remote URL
    HTTPS_URL=$(git remote get-url origin)
    
    # Convert to SSH
    if [[ $HTTPS_URL == https://github.com/* ]]; then
        SSH_URL=$(echo $HTTPS_URL | sed 's/https:\/\/github\.com\//git@github.com:/')
        git remote set-url origin $SSH_URL
        echo "Migrated: $(pwd) → $SSH_URL"
    fi
    
    cd - > /dev/null
done
```

## Prossimi Passi

Ora che hai configurato SSH:

1. **Testa la configurazione** con un repository
2. **Esplora l'ecosistema** GitHub - [Ecosistema GitHub](./06-ecosistema-github.md)
3. **Pratica con esempi** - [Configurazione SSH](../esempi/03-configurazione-ssh.md)
4. **Impara Git workflow** - [Clone Push Pull](../../17-Clone-Push-Pull/README.md)

## Risorse Aggiuntive

- [GitHub SSH Documentation](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
- [OpenSSH Manual](https://www.openssh.com/manual.html)
- [SSH Key Management Best Practices](https://goteleport.com/blog/how-to-ssh-properly/)
