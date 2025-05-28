# 01 - Setup Completo Git su Windows

## 🎯 Obiettivo

Guida step-by-step per installare e configurare Git su Windows con tutti i tool necessari per iniziare a sviluppare.

## 📋 Prerequisiti

- Windows 10/11
- Connessione internet
- Diritti di amministratore (per installazione)

## ⏱️ Tempo Richiesto

**45-60 minuti** (installazione + configurazione + test)

---

## 📥 Parte 1: Download e Installazione

### Step 1: Download Git for Windows

1. **Vai su** [git-scm.com](https://git-scm.com)
2. **Clicca** "Download for Windows"
3. **Scarica** `Git-2.xx.x-64-bit.exe`

### Step 2: Esecuzione Installer

```cmd
:: Esegui come amministratore
Git-2.xx.x-64-bit.exe
```

### Step 3: Opzioni di Installazione Consigliate

#### 🔧 **Schermata "Select Components"**
```
✅ Windows Explorer integration
✅ Git Bash Here
✅ Git GUI Here
✅ Associate .git* configuration files with the default text editor
✅ Associate .sh files to be run with Bash
✅ Use a TrueType font in all console windows
✅ Check daily for Git for Windows updates
```

#### 📝 **Schermata "Choosing the default editor"**
```
🎯 Scegli: "Use Visual Studio Code as Git's default editor"
   (Se VS Code non è installato, scegli "Use Nano")
```

#### 🛤️ **Schermata "Adjusting your PATH environment"**
```
✅ Git from the command line and also from 3rd-party software
   (Opzione raccomandata)
```

#### 🔐 **Schermata "Choosing HTTPS transport backend"**
```
✅ Use the OpenSSL library
   (Più sicuro e compatibile)
```

#### 📄 **Schermata "Configuring the line ending conversions"**
```
✅ Checkout Windows-style, commit Unix-style line endings
   (Raccomandato per Windows)
```

#### 💻 **Schermata "Configuring the terminal emulator"**
```
✅ Use MinTTY (the default terminal of MSYS2)
   (Migliore esperienza terminal)
```

#### 🔄 **Schermata "Choose the default behavior of 'git pull'"**
```
✅ Default (fast-forward or merge)
   (Comportamento standard)
```

#### 🔑 **Schermata "Choose a credential helper"**
```
✅ Git Credential Manager
   (Gestisce automaticamente credenziali GitHub)
```

### Step 4: Completamento Installazione

```
✅ Enable experimental support for pseudo consoles (opzionale)
✅ Enable experimental built-in file system monitor (opzionale)
```

---

## ⚙️ Parte 2: Configurazione Base

### Step 1: Verifica Installazione

```cmd
:: Apri Command Prompt o PowerShell
cmd

:: Verifica versione Git
git --version
:: Output atteso: git version 2.xx.x.windows.x

:: Verifica percorso installazione
where git
:: Output: C:\Program Files\Git\cmd\git.exe
```

### Step 2: Configurazione Identità

```cmd
:: Configura nome (sostituisci con il tuo nome)
git config --global user.name "Mario Rossi"

:: Configura email (sostituisci con la tua email)
git config --global user.email "mario.rossi@example.com"

:: Verifica configurazione
git config --global user.name
git config --global user.email
```

### Step 3: Configurazioni Windows-Specifiche

```cmd
:: Configurazione line endings per Windows
git config --global core.autocrlf true

:: Configurazione case sensitivity
git config --global core.ignorecase true

:: Configurazione file permissions (disabilita per Windows)
git config --global core.filemode false

:: Abilita cache file system
git config --global core.fscache true
```

---

## 🛠️ Parte 3: Configurazione Editor e Tool

### Option A: VS Code (Raccomandato)

#### 1. Installa VS Code
```cmd
:: Scarica da https://code.visualstudio.com/
:: Esegui installer VSCodeUserSetup-x64-x.xx.x.exe
```

#### 2. Configura VS Code per Git
```cmd
:: Configura VS Code come editor Git
git config --global core.editor "code --wait"

:: Configura come diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd "code --wait --diff $LOCAL $REMOTE"
git config --global difftool.prompt false

:: Configura come merge tool
git config --global merge.tool vscode
git config --global mergetool.vscode.cmd "code --wait $MERGED"
git config --global mergetool.prompt false
```

### Option B: Notepad++ (Alternativa)

#### 1. Installa Notepad++
```cmd
:: Scarica da https://notepad-plus-plus.org/
:: Esegui npp.x.x.x.Installer.x64.exe
```

#### 2. Configura Notepad++ per Git
```cmd
git config --global core.editor "'C:/Program Files/Notepad++/notepad++.exe' -multiInst -notabbar -nosession -noPlugin"
```

---

## 🎨 Parte 4: Personalizzazione

### Configurazioni di Comfort

```cmd
:: Abilita colori nell'output
git config --global color.ui auto

:: Default branch name
git config --global init.defaultBranch main

:: Configurazioni push
git config --global push.default simple
git config --global push.followTags true

:: Alias utili
git config --global alias.st "status"
git config --global alias.co "checkout"
git config --global alias.br "branch"
git config --global alias.ci "commit"
git config --global alias.lg "log --oneline --decorate --graph --all"
```

### Configurazione Credential Manager

```cmd
:: Verifica che Credential Manager sia attivo
git config --global credential.helper
:: Output atteso: manager

:: Test con repository remoto (opzionale)
:: git clone https://github.com/user/repo.git
:: Ti chiederà credenziali solo la prima volta
```

---

## 🖥️ Parte 5: Setup Terminal

### PowerShell con Git

#### 1. Configura PowerShell Profile
```powershell
# Apri PowerShell come amministratore
# Crea profile se non esiste
if (!(Test-Path -Path $PROFILE)) {
    New-Item -ItemType File -Path $PROFILE -Force
}

# Aggiungi funzioni Git al profile
Add-Content -Path $PROFILE -Value @"
# Git aliases per PowerShell
function gs { git status }
function ga { git add . }
function gc { git commit -m `$args[0] }
function gp { git push }
function gl { git log --oneline }
function gco { git checkout `$args[0] }

# Prompt con branch Git
function prompt {
    `$gitBranch = git branch --show-current 2>`$null
    if (`$gitBranch) {
        Write-Host "`$(Get-Location) [" -NoNewline
        Write-Host `$gitBranch -ForegroundColor Yellow -NoNewline
        Write-Host "]> " -NoNewline
    } else {
        Write-Host "`$(Get-Location)> " -NoNewline
    }
    return " "
}
"@

# Ricarica profile
. $PROFILE
```

### Git Bash Setup

```bash
# Git Bash include già un prompt con branch
# Aggiungi alias al ~/.bashrc (se esiste)
echo 'alias ll="ls -la"' >> ~/.bashrc
echo 'alias gs="git status"' >> ~/.bashrc
echo 'alias ga="git add"' >> ~/.bashrc
echo 'alias gc="git commit"' >> ~/.bashrc

# Ricarica configurazione
source ~/.bashrc
```

---

## 🧪 Parte 6: Test Setup Completo

### Test 1: Comandi Base

```cmd
:: Crea cartella di test
mkdir C:\temp\git-test
cd C:\temp\git-test

:: Inizializza repository
git init
:: Output: Initialized empty Git repository in C:/temp/git-test/.git/

:: Controlla status
git status
:: Output: On branch main, No commits yet...
```

### Test 2: Primo Commit

```cmd
:: Crea file di test
echo "# Test Repository" > README.md

:: Aggiungi file
git add README.md

:: Verifica status
git status
:: Output: Changes to be committed: new file: README.md

:: Commit (dovrebbe aprire l'editor configurato)
git commit -m "Initial commit"
:: Output: [main (root-commit) abc1234] Initial commit
```

### Test 3: Test Editor

```cmd
:: Test editor con commit vuoto
echo "Test content" > test.txt
git add test.txt

:: Questo dovrebbe aprire l'editor configurato
git commit
:: Scrivi messaggio di commit, salva e chiudi
```

### Test 4: Test Diff Tool

```cmd
:: Modifica file esistente
echo "Modified content" >> test.txt

:: Test diff tool
git difftool test.txt
:: Dovrebbe aprire l'editor configurato in modalità diff
```

---

## 🔧 Troubleshooting Windows

### Problema: Git non trovato dopo installazione

```cmd
:: Aggiungi manualmente al PATH
:: Vai in: Sistema > Proprietà avanzate > Variabili d'ambiente
:: Aggiungi: C:\Program Files\Git\cmd

:: Oppure da PowerShell (come amministratore)
$env:PATH += ";C:\Program Files\Git\cmd"
setx PATH "$env:PATH" /M
```

### Problema: VS Code non si apre da Git

```cmd
:: Verifica che VS Code sia nel PATH
code --version

:: Se non funziona, usa percorso completo
git config --global core.editor "'C:/Users/%USERNAME%/AppData/Local/Programs/Microsoft VS Code/Code.exe' --wait"
```

### Problema: Errori line endings

```cmd
:: Reset configurazione line endings
git config --global core.autocrlf true
git config --global core.safecrlf false

:: Per repository esistenti
git add . && git commit -m "Normalize line endings"
```

### Problema: Credential Manager non funziona

```cmd
:: Reset credential helper
git config --global --unset credential.helper
git config --global credential.helper manager

:: Cancella credenziali salvate (Pannello di Controllo > Credential Manager)
:: O da PowerShell
cmdkey /list | findstr git
cmdkey /delete:target=git:https://github.com
```

---

## 📋 Checklist Setup Windows

### Installazione Base
- [ ] Git for Windows installato con opzioni corrette
- [ ] `git --version` funziona
- [ ] Git disponibile da Command Prompt e PowerShell
- [ ] Git Bash installato e funzionante

### Configurazione
- [ ] Nome e email configurati
- [ ] Editor configurato e testato
- [ ] Configurazioni Windows (autocrlf, ignorecase) applicate
- [ ] Alias base configurati

### Tool e Editor
- [ ] VS Code/Notepad++ installato e configurato
- [ ] Diff tool configurato e testato
- [ ] Merge tool configurato e testato
- [ ] Credential Manager funzionante

### Test Funzionali
- [ ] Repository di test creato
- [ ] Primo commit completato
- [ ] Editor si apre correttamente per commit
- [ ] Diff tool funziona

---

## 🎯 Risultato Finale

Al termine di questo setup avrai:

✅ **Git completamente installato** su Windows
✅ **Configurazione ottimizzata** per sviluppo Windows
✅ **Editor integrato** per commit e diff
✅ **Terminal personalizzato** con info Git
✅ **Credential management** automatico
✅ **Setup testato** e funzionante

---

## 🔗 Prossimi Passi

✅ **Completato**: Setup Windows
🎯 **Prossimo**: [Primo Repository](../../03-Primo-Repository-Git/README.md)

---

## 📚 Risorse Windows-Specifiche

- [Git for Windows Documentation](https://gitforwindows.org/)
- [Windows Credential Manager](https://docs.microsoft.com/en-us/windows/security/identity-protection/credential-guard/)
- [PowerShell Git Integration](https://docs.microsoft.com/en-us/powershell/scripting/dev-cross-plat/vscode/using-vscode)
