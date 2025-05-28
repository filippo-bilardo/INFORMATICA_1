# 01 - Clone: Copiare Repository Remoti

## 📖 Spiegazione Concettuale

Il **clone** è l'operazione che crea una copia locale completa di un repository remoto. È il primo passo per iniziare a lavorare su un progetto esistente ospitato su GitHub, GitLab, o altri servizi Git.

### Cosa Succede Durante un Clone

```
Repository Remoto (GitHub)     →     Repository Locale
├── .git/ (storia completa)          ├── .git/ (copia completa)
├── main branch                      ├── main branch (checkout)
├── altri branch                     ├── riferimenti a branch remoti
└── tag e release                    └── tag e release
```

### Differenza Clone vs Download

| Clone Git | Download ZIP |
|-----------|--------------|
| ✅ Storia completa | ❌ Solo snapshot |
| ✅ Branch disponibili | ❌ Solo branch principale |
| ✅ Collegamento al remoto | ❌ Nessun collegamento |
| ✅ Possibilità di contribuire | ❌ Solo lettura |

## 🔧 Sintassi del Clone

### Comando Base

```bash
# Sintassi generale
git clone <url-repository>

# Clone con HTTPS
git clone https://github.com/username/repository-name.git

# Clone con SSH
git clone git@github.com:username/repository-name.git
```

### Opzioni Avanzate

```bash
# Clone in directory specifica
git clone <url> <nome-directory>
git clone https://github.com/user/repo.git my-project

# Clone solo branch specifico
git clone --branch <branch-name> <url>
git clone --branch develop https://github.com/user/repo.git

# Clone shallow (solo ultimi commit)
git clone --depth 1 <url>

# Clone senza checkout automatico
git clone --no-checkout <url>
```

## 🎯 Metodi di Clone

### 1. Clone HTTPS

```bash
# Metodo più comune e universale
git clone https://github.com/octocat/Hello-World.git

# Vantaggi:
# ✅ Funziona ovunque
# ✅ Non richiede configurazione SSH
# ✅ Attraversa firewall aziendali

# Svantaggi:
# ❌ Richiede username/password per push
# ❌ Può essere più lento
```

### 2. Clone SSH

```bash
# Metodo preferito per sviluppatori attivi
git clone git@github.com:octocat/Hello-World.git

# Vantaggi:
# ✅ Autenticazione automatica con chiavi
# ✅ Più veloce e sicuro
# ✅ Non richiede credenziali ad ogni push

# Svantaggi:
# ❌ Richiede configurazione SSH
# ❌ Può essere bloccato da alcuni firewall
```

### 3. Clone GitHub CLI

```bash
# Usando GitHub CLI (se installato)
gh repo clone username/repository-name

# Vantaggi:
# ✅ Integrazione diretta con GitHub
# ✅ Gestione automatica dell'autenticazione
# ✅ Comandi aggiuntivi disponibili
```

## 🚀 Esempi Pratici

### Scenario 1: Clone Repository Pubblico

```bash
# Clone di un progetto open source
git clone https://github.com/microsoft/vscode.git

# Verifica clone riuscito
cd vscode
git status
git log --oneline -5

# Verifica remote configurato
git remote -v
# origin  https://github.com/microsoft/vscode.git (fetch)
# origin  https://github.com/microsoft/vscode.git (push)
```

### Scenario 2: Clone con Nome Personalizzato

```bash
# Clone in directory con nome diverso
git clone https://github.com/facebook/react.git my-react-project

cd my-react-project
pwd
# /path/to/my-react-project

# Repository è lo stesso, ma directory è personalizzata
git remote -v
# origin  https://github.com/facebook/react.git (fetch)
# origin  https://github.com/facebook/react.git (push)
```

### Scenario 3: Clone Branch Specifico

```bash
# Clone solo branch di sviluppo
git clone --branch develop https://github.com/user/project.git

# Verifica branch attivo
git branch
# * develop

# Branch remoti disponibili
git branch -r
# origin/develop
# origin/main
# origin/feature-xyz
```

### Scenario 4: Clone Shallow per Risparmiare Spazio

```bash
# Clone solo ultimo commit (per CI/CD o analisi)
git clone --depth 1 https://github.com/tensorflow/tensorflow.git

# Verifica dimensione ridotta
cd tensorflow
git log --oneline
# Solo 1 commit visibile

# Per ottenere storia completa se necessario
git fetch --unshallow
```

## ⚙️ Configurazione Post-Clone

### 1. Verifica Configurazione

```bash
# Dopo il clone, verifica setup
git config --list --show-origin

# Configura identità se necessario
git config user.name "Il Tuo Nome"
git config user.email "tua@email.com"
```

### 2. Setup Branch Tracking

```bash
# Verifica branch tracking
git branch -vv

# Setup tracking per branch locali
git branch --set-upstream-to=origin/main main
```

### 3. Configurazione Remote Aggiuntivi

```bash
# Aggiungere upstream per fork
git remote add upstream https://github.com/original/repository.git

# Verifica remote configurati
git remote -v
# origin    https://github.com/tuofork/repository.git (fetch)
# origin    https://github.com/tuofork/repository.git (push)
# upstream  https://github.com/original/repository.git (fetch)
# upstream  https://github.com/original/repository.git (push)
```

## ⚠️ Problemi Comuni e Soluzioni

### 1. Errore di Autenticazione

```bash
# Problema: clone fallisce per autenticazione
$ git clone https://github.com/private/repo.git
fatal: Authentication failed

# Soluzioni:
# A) Usa token di accesso personale
git clone https://token@github.com/private/repo.git

# B) Configura credential helper
git config --global credential.helper store

# C) Usa SSH se configurato
git clone git@github.com:private/repo.git
```

### 2. Repository Troppo Grande

```bash
# Problema: repository molto grande
# Soluzione: clone shallow
git clone --depth 1 --single-branch https://github.com/large/repo.git

# O clone specifico di una sottocartella (Git 2.25+)
git clone --filter=blob:none https://github.com/large/repo.git
cd repo
git sparse-checkout init --cone
git sparse-checkout set folder/you/want
```

### 3. Nome Directory Conflitto

```bash
# Problema: directory già esistente
$ git clone https://github.com/user/project.git
fatal: destination path 'project' already exists

# Soluzioni:
# A) Nome diverso
git clone https://github.com/user/project.git project-new

# B) Clone in directory esistente vuota
rmdir project  # se vuota
git clone https://github.com/user/project.git

# C) Clone e merge se directory contiene file
git clone https://github.com/user/project.git temp-clone
cp -r temp-clone/* project/
rm -rf temp-clone
```

## 💡 Best Practices

### 1. Organizzazione Directory

```bash
# Struttura organizzata per progetti
mkdir -p ~/projects/github
mkdir -p ~/projects/gitlab
mkdir -p ~/projects/work

# Clone in directory appropriate
cd ~/projects/github
git clone https://github.com/user/personal-project.git

cd ~/projects/work
git clone https://gitlab.company.com/team/work-project.git
```

### 2. Verifica Prima del Clone

```bash
# Controlla repository online prima di clonare
# - README per capire il progetto
# - License per termini di utilizzo
# - Issues per problemi noti
# - Attività recente

# Verifica dimensione repository
curl -s https://api.github.com/repos/user/repo | grep size
```

### 3. Sicurezza e Privacy

```bash
# Per progetti privati: usa sempre SSH o token
# Per progetti pubblici: HTTPS va bene
# Non clonare mai in directory pubbliche
# Usa .gitignore per file sensibili
```

## 🧪 Esercizi Pratici

### Esercizio 1: Clone Base

```bash
# 1. Clona questo repository pubblico
git clone https://github.com/octocat/Hello-World.git

# 2. Esplora la struttura
cd Hello-World
ls -la
git log --oneline -5

# 3. Verifica remote
git remote -v
```

### Esercizio 2: Clone con Opzioni

```bash
# 1. Clone shallow
git clone --depth 1 https://github.com/microsoft/vscode.git vscode-shallow

# 2. Clone branch specifico
git clone --branch release/1.70 https://github.com/microsoft/vscode.git vscode-release

# 3. Confronta dimensioni
du -sh vscode-shallow vscode-release
```

### Esercizio 3: Setup Completo

```bash
# 1. Clone un progetto
git clone https://github.com/expressjs/express.git

# 2. Configura identità
cd express
git config user.name "Tuo Nome"
git config user.email "tua@email.com"

# 3. Aggiungi upstream (simula fork)
git remote add upstream https://github.com/expressjs/express.git

# 4. Verifica configurazione
git config --list --local
git remote -v
```

## 🧠 Quiz di Verifica

### Domanda 1
Quale comando clona solo l'ultimo commit?
- A) `git clone --single`
- B) `git clone --depth 1`
- C) `git clone --shallow`
- D) `git clone --last`

### Domanda 2
Qual è la differenza principale tra clone HTTPS e SSH?
- A) SSH è più veloce, HTTPS più sicuro
- B) HTTPS richiede configurazione, SSH no
- C) SSH usa chiavi, HTTPS username/password
- D) Non c'è differenza

### Domanda 3
Cosa succede se la directory di destinazione già esiste?
- A) Il clone procede normalmente
- B) Git sovrascrive la directory
- C) Git restituisce un errore
- D) Git chiede conferma

### Risposte
1. B - `--depth 1` crea un clone shallow con solo l'ultimo commit
2. C - SSH usa chiavi per l'autenticazione, HTTPS username/password
3. C - Git restituisce errore se la directory esiste già

## 📚 Approfondimenti

### Clone e Bandwidth

```bash
# Per connessioni lente: clone con filtri
git clone --filter=blob:limit=1m https://github.com/large/repo.git

# Per CI/CD: clone minimal
git clone --depth 1 --single-branch https://github.com/user/repo.git
```

### Troubleshooting Avanzato

```bash
# Debug clone problems
GIT_CURL_VERBOSE=1 git clone https://github.com/user/repo.git

# Clone con proxy
git config --global http.proxy http://proxy:8080
git clone https://github.com/user/repo.git
```

## 🔗 Collegamenti

### Link Interni
- [📑 Indice Modulo](../README.md)
- [⬅️ Modulo Precedente](../../15-Introduzione-GitHub/README.md)
- [➡️ Prossima Guida](./02-push-repository.md)

### Risorse Esterne
- [Git Clone Documentation](https://git-scm.com/docs/git-clone)
- [GitHub Cloning Guide](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

---

**Prossimo passo**: [Push Repository](./02-push-repository.md) - Impara a inviare le modifiche al repository remoto
