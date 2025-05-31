# Esempio 04 - Setup Enterprise e Configurazione Professionale

## 📋 Scenario

Una software house necessita di standardizzare la configurazione Git per tutti i suoi sviluppatori, inclusi ambienti aziendali con proxy, server Git interni, e policy di sicurezza specifiche.

## 🎯 Obiettivo

Configurare Git per un ambiente enterprise con:
- **Configurazioni proxy aziendali**
- **Certificati SSL personalizzati**
- **Server Git interni**
- **Policy di sicurezza e compliance**
- **Configurazioni team standardizzate**

---

## ⚙️ Configurazione Enterprise Completa

### 1. Setup Base con Proxy Aziendale

```bash
# Configurazione proxy HTTP/HTTPS
git config --global http.proxy http://username:password@proxy.company.com:8080
git config --global https.proxy https://username:password@proxy.company.com:8080

# Configurazione proxy per domini specifici
git config --global http.https://github.com.proxy ""
git config --global http.https://gitlab.company.com.proxy http://proxy.company.com:8080

# Bypass proxy per server interni
git config --global http.https://git.internal.company.com.proxy ""
```

### 2. Configurazione SSL e Certificati

```bash
# Configurazione certificati SSL aziendali
git config --global http.sslCAInfo /path/to/company-ca-bundle.crt
git config --global http.sslCert /path/to/client-cert.pem
git config --global http.sslKey /path/to/client-key.pem

# Configurazione per server interni con certificati self-signed
git config --global http.https://git.internal.company.com.sslVerify false

# Configurazione timeout per connessioni lente
git config --global http.lowSpeedLimit 1000
git config --global http.lowSpeedTime 300
```

### 3. Identità e Configurazioni Team

```bash
# Configurazione identità aziendale
git config --global user.name "Mario Rossi"
git config --global user.email "mario.rossi@company.com"

# Configurazione GPG per firma commit (compliance)
git config --global user.signingkey 0A46826A
git config --global commit.gpgsign true
git config --global gpg.program gpg2

# Configurazione editor aziendale standard
git config --global core.editor "code --wait"
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd 'code --wait $MERGED'
```

### 4. Policy di Sicurezza e Compliance

```bash
# Prevenzione push accidentali su branch protetti
git config --global branch.main.pushRemote no-pushing
git config --global branch.master.pushRemote no-pushing

# Configurazione commit template aziendale
cat > ~/.gitmessage << 'EOF'
# [TIPO] Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento (max 72 caratteri per riga)
#
# Ticket: #XXXX
# Reviewer: @username
# Testing: [unit/integration/manual]
EOF

git config --global commit.template ~/.gitmessage

# Configurazione push sicuro
git config --global push.default simple
git config --global push.followTags true
```

### 5. Configurazioni Performance Enterprise

```bash
# Ottimizzazioni per repository grandi
git config --global core.preloadindex true
git config --global core.fscache true
git config --global gc.auto 256

# Configurazione per file system di rete
git config --global core.trustctime false
git config --global core.checkstat minimal

# Configurazioni per Windows enterprise
git config --global core.autocrlf true
git config --global core.safecrlf warn
```

---

## 🔧 Script di Setup Automatico

### Script PowerShell per Windows Enterprise

```powershell
# setup-git-enterprise.ps1
param(
    [Parameter(Mandatory=$true)]
    [string]$UserName,
    
    [Parameter(Mandatory=$true)]
    [string]$UserEmail,
    
    [string]$ProxyServer = "proxy.company.com:8080",
    [string]$ProxyUser = $env:USERNAME
)

Write-Host "🚀 Configurazione Git Enterprise per $UserName" -ForegroundColor Green

# Configurazione identità
git config --global user.name $UserName
git config --global user.email $UserEmail

# Configurazione proxy se fornito
if ($ProxyServer) {
    $ProxyUrl = "http://${ProxyUser}@${ProxyServer}"
    git config --global http.proxy $ProxyUrl
    git config --global https.proxy $ProxyUrl
    Write-Host "✅ Proxy configurato: $ProxyUrl" -ForegroundColor Yellow
}

# Configurazioni aziendali standard
git config --global core.autocrlf true
git config --global core.editor "code --wait"
git config --global init.defaultBranch main
git config --global pull.rebase false

# Configurazione template commit
$templatePath = "$env:USERPROFILE\.gitmessage"
@"
# [TIPO] Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento
#
# Ticket: #XXXX
# Reviewer: @username
"@ | Out-File -FilePath $templatePath -Encoding UTF8

git config --global commit.template $templatePath

Write-Host "✅ Setup completato con successo!" -ForegroundColor Green
Write-Host "📝 Verificare configurazione con: git config --list --global" -ForegroundColor Cyan
```

### Script Bash per Linux/macOS Enterprise

```bash
#!/bin/bash
# setup-git-enterprise.sh

set -e

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Funzione per log colorati
log() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Parametri
USER_NAME=${1:-""}
USER_EMAIL=${2:-""}
COMPANY_DOMAIN=${3:-"company.com"}

if [[ -z "$USER_NAME" || -z "$USER_EMAIL" ]]; then
    error "Uso: $0 'Nome Cognome' 'email@company.com' [domain]"
    exit 1
fi

log "🚀 Configurazione Git Enterprise per $USER_NAME"

# Configurazione identità
git config --global user.name "$USER_NAME"
git config --global user.email "$USER_EMAIL"
log "✅ Identità configurata"

# Configurazioni sicurezza
git config --global init.defaultBranch main
git config --global pull.rebase false
git config --global push.default simple
git config --global push.followTags true
log "✅ Policy di sicurezza applicate"

# Configurazione editor e tool
if command -v code >/dev/null 2>&1; then
    git config --global core.editor "code --wait"
    git config --global merge.tool vscode
    git config --global mergetool.vscode.cmd 'code --wait $MERGED'
    log "✅ VS Code configurato come editor"
elif command -v vim >/dev/null 2>&1; then
    git config --global core.editor "vim"
    log "✅ Vim configurato come editor"
fi

# Template commit aziendale
TEMPLATE_FILE="$HOME/.gitmessage"
cat > "$TEMPLATE_FILE" << 'EOF'
# [TIPO] Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento (max 72 caratteri per riga)
#
# Ticket: #XXXX
# Reviewer: @username
# Testing: [unit/integration/manual]
#
# Tipi comuni: feat, fix, docs, style, refactor, test, chore
EOF

git config --global commit.template "$TEMPLATE_FILE"
log "✅ Template commit configurato"

# Ottimizzazioni performance
git config --global core.preloadindex true
git config --global gc.auto 256
log "✅ Ottimizzazioni performance applicate"

# Verifica configurazione
log "📋 Configurazione finale:"
echo -e "${CYAN}$(git config --list --global | grep -E '(user\.|core\.|push\.|pull\.)')${NC}"

log "🎉 Setup enterprise completato con successo!"
warn "💡 Ricorda di configurare proxy e certificati SSL se necessario"
```

---

## 🔐 Configurazione GPG per Firma Commit

### 1. Generazione Chiave GPG Aziendale

```bash
# Generazione chiave GPG
gpg --full-generate-key

# Selezioni durante la generazione:
# (1) RSA and RSA (default)
# Keysize: 4096
# Valid for: 2y (2 anni)
# Real name: Mario Rossi
# Email: mario.rossi@company.com
# Comment: Company Developer Key

# Lista chiavi generate
gpg --list-secret-keys --keyid-format LONG

# Output esempio:
# sec   rsa4096/0A46826A 2023-01-01 [SC] [expires: 2025-01-01]
#       A1B2C3D4E5F6G7H8I9J0K1L2M3N4O5P6Q7R8S9T0
# uid                   Mario Rossi (Company Developer Key) <mario.rossi@company.com>
# ssb   rsa4096/1B57936B 2023-01-01 [E] [expires: 2025-01-01]
```

### 2. Configurazione Git con GPG

```bash
# Configurazione chiave firma
git config --global user.signingkey 0A46826A
git config --global commit.gpgsign true
git config --global tag.gpgsign true

# Configurazione programma GPG (se necessario)
git config --global gpg.program gpg2

# Export chiave pubblica per GitHub/GitLab
gpg --armor --export 0A46826A
```

---

## 📊 Verifica e Testing Configurazione

### Script di Verifica Completa

```bash
#!/bin/bash
# verify-git-setup.sh

echo "🔍 VERIFICA CONFIGURAZIONE GIT ENTERPRISE"
echo "=========================================="

# Test connettività di base
echo -e "\n📡 Test Connettività:"
git ls-remote https://github.com/octocat/Hello-World.git > /dev/null 2>&1 && \
    echo "✅ GitHub raggiungibile" || echo "❌ GitHub non raggiungibile"

# Verifica configurazioni critiche
echo -e "\n⚙️ Configurazioni Critiche:"
echo "👤 Utente: $(git config --global user.name)"
echo "📧 Email: $(git config --global user.email)"
echo "🔑 Firma GPG: $(git config --global commit.gpgsign)"
echo "📝 Editor: $(git config --global core.editor)"

# Test proxy (se configurato)
if git config --global http.proxy > /dev/null 2>&1; then
    echo "🌐 Proxy: $(git config --global http.proxy)"
fi

# Test repository temporaneo
echo -e "\n🧪 Test Repository Temporaneo:"
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

git init test-repo
cd test-repo

echo "Test file" > test.txt
git add test.txt
git commit -m "test: Verifica configurazione enterprise" && \
    echo "✅ Commit test riuscito" || echo "❌ Commit test fallito"

# Verifica firma GPG (se abilitata)
if git config --global commit.gpgsign | grep -q true; then
    git log --show-signature -1 > /dev/null 2>&1 && \
        echo "✅ Firma GPG verificata" || echo "❌ Problema firma GPG"
fi

# Cleanup
cd /
rm -rf "$TEMP_DIR"

echo -e "\n✅ Verifica completata"
```

---

## 🏢 Configurazioni per Diversi Ambienti

### Ambiente di Sviluppo

```bash
# Configurazioni development-friendly
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual '!gitk'

# Configurazioni per debug
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
```

### Ambiente di Produzione

```bash
# Configurazioni più conservative
git config --global push.default nothing
git config --global receive.denyCurrentBranch refuse
git config --global receive.denyNonFastForwards true

# Logging più dettagliato
git config --global core.logAllRefUpdates true
git config --global log.showSignature true
```

---

## 📚 Template di Configurazione Aziendale

### File `.gitconfig` Template

```ini
[user]
    name = Nome Cognome
    email = nome.cognome@company.com
    signingkey = 0A46826A

[core]
    editor = code --wait
    autocrlf = true
    trustctime = false
    preloadindex = true

[init]
    defaultBranch = main

[push]
    default = simple
    followTags = true

[pull]
    rebase = false

[commit]
    gpgsign = true
    template = ~/.gitmessage

[http]
    proxy = http://proxy.company.com:8080
    sslCAInfo = /path/to/company-ca.crt

[alias]
    st = status
    co = checkout
    br = branch
    ci = commit
    lg = log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
```

---

## 🎯 Punti Chiave per l'Ambiente Enterprise

### ✅ Checklist Completamento Setup

- [ ] **Proxy configurato** per connessioni esterne
- [ ] **Certificati SSL** per server interni configurati
- [ ] **GPG setup** per firma commit (se richiesto)
- [ ] **Template commit** con standard aziendali
- [ ] **Editor standardizzato** per il team
- [ ] **Policy di push** configurate per sicurezza
- [ ] **Alias comuni** per produttività team
- [ ] **Test connettività** completato
- [ ] **Documentazione** configurazioni per nuovi membri

### 🚨 Considerazioni di Sicurezza

1. **Mai salvare password** in configurazioni Git
2. **Utilizzare token** invece di password per autenticazione
3. **Configurare 2FA** su tutti gli account Git
4. **Rotazione regolare** delle chiavi GPG
5. **Audit periodico** delle configurazioni

### 💡 Best Practices Enterprise

- **Standardizzazione** configurazioni tra tutti i membri del team
- **Documentazione** di tutte le configurazioni specifiche
- **Script automatici** per setup nuovi sviluppatori
- **Monitoraggio** dell'uso delle configurazioni di sicurezza
- **Training** regolare su policy e configurazioni Git

---

*Questa configurazione enterprise assicura che tutti gli sviluppatori abbiano un ambiente Git sicuro, standardizzato e conforme alle policy aziendali.*
