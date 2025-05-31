# Esercizio: Setup Account GitHub

## Obiettivo
Completare la configurazione di un account GitHub professionale con tutte le impostazioni necessarie per un utilizzo ottimale.

## Prerequisiti
- Connessione internet
- Email valida
- Conoscenza base di Git

## Parte 1: Creazione Account

### Step 1: Registrazione
1. Vai su [github.com](https://github.com)
2. Clicca su "Sign up"
3. Inserisci i dati richiesti:
   ```
   Username: [scegli un nome professionale]
   Email: [usa email principale]
   Password: [password sicura]
   ```

### Step 2: Verifica Email
1. Controlla la tua email
2. Clicca sul link di verifica
3. Completa la verifica del profilo

### Criteri per Username Professionale
```
✅ Buoni esempi:
- marco-rossi
- m.rossi.dev
- marcorossi92
- rossi-marco

❌ Evitare:
- xXdragon_killer99Xx
- coolguy2023
- hackerman_elite
```

## Parte 2: Configurazione Profilo

### Step 1: Foto Profilo
```markdown
Linee guida:
- Usa una foto professionale
- Risoluzione minima: 300x300px
- Formato: JPG, PNG, GIF
- Dimensione max: 1MB
```

### Step 2: Bio e Informazioni
```markdown
# Esempio di bio efficace:
🚀 Full Stack Developer | JavaScript & Python
📍 Milano, Italy
🔧 React, Node.js, Docker
📚 Always learning new technologies
🌐 Portfolio: https://yoursite.com

# Template da personalizzare:
[Emoji role] [Title] | [Main Technologies]
📍 [Location]
🔧 [Tech Stack]
📚 [Current Focus]
🌐 [Website/Portfolio]
```

### Step 3: Informazioni Dettagliate
Compila i seguenti campi nel profilo:
- **Company**: La tua azienda o "Freelancer"
- **Location**: Città, Paese
- **Website**: Portfolio o LinkedIn
- **Twitter**: Se hai un account professionale

## Parte 3: Impostazioni Security

### Step 1: Two-Factor Authentication
```bash
# Installa app authenticator (scegli una):
- Google Authenticator
- Microsoft Authenticator
- Authy
- 1Password

# Steps in GitHub:
1. Settings → Account security
2. Two-factor authentication → Enable
3. Scan QR code con app
4. Salva recovery codes in luogo sicuro!
```

### Step 2: SSH Keys Setup
```bash
# Genera nuova SSH key
ssh-keygen -t ed25519 -C "your-email@example.com"

# Windows/Linux/macOS
# Quando richiesto, premi ENTER per default location
# Inserisci passphrase sicura

# Aggiungi chiave a ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# Copia chiave pubblica
# macOS:
pbcopy < ~/.ssh/id_ed25519.pub

# Linux:
cat ~/.ssh/id_ed25519.pub | xclip -selection clipboard

# Windows:
type .ssh/id_ed25519.pub | clip
```

### Step 3: Aggiungere SSH Key a GitHub
1. Settings → SSH and GPG keys
2. New SSH key
3. Title: "Nome del tuo computer"
4. Incolla la chiave pubblica
5. Add SSH key

### Step 4: Test SSH Connection
```bash
ssh -T git@github.com

# Output atteso:
# Hi username! You've successfully authenticated, but GitHub does not provide shell access.
```

## Parte 4: Configurazione Notifiche

### Step 1: Email Notifications
```
Settings → Notifications

Configurazione consigliata:
✅ Participating: Email + Web
✅ Watching: Web only
❌ Email for your own updates: Disabilitato
✅ Actions workflow notifications: Email
```

### Step 2: GitHub Mobile
```bash
# Installa GitHub Mobile:
- iOS: App Store
- Android: Google Play Store

# Configura:
1. Login con il tuo account
2. Abilita notifiche push selettive
3. Configura Quick Actions
```

## Parte 5: Personalizzazione Avanzata

### Step 1: GitHub Themes
```
Settings → Appearance

Opzioni disponibili:
- Light default
- Light high contrast
- Dark default
- Dark high contrast
- Dark dimmed
```

### Step 2: Profile README
```bash
# Crea repository speciale
1. Nuovo repository con nome uguale al tuo username
2. Aggiungi README.md
3. Questo apparirà nel tuo profilo!
```

Esempio di Profile README:
```markdown
# Ciao! 👋 Sono [Il Tuo Nome]

## 🚀 About Me
Sono uno sviluppatore appassionato di tecnologie web moderne...

## 🛠️ Tech Stack
![JavaScript](https://img.shields.io/badge/-JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black)
![React](https://img.shields.io/badge/-React-61DAFB?style=flat-square&logo=react&logoColor=black)
![Node.js](https://img.shields.io/badge/-Node.js-339933?style=flat-square&logo=node.js&logoColor=white)

## 📊 GitHub Stats
![Your GitHub stats](https://github-readme-stats.vercel.app/api?username=yourusername&show_icons=true&theme=radical)

## 🌱 Currently Learning
- TypeScript avanzato
- Microservices architecture
- Kubernetes

## 📫 Come contattarmi
- LinkedIn: [link]
- Email: your-email@example.com
- Portfolio: [link]
```

### Step 3: Badges e Achievements
GitHub mostra automaticamente:
- Anni di contribuzione
- Streak di commit
- Pull request mergiate
- Issues risolte

## Parte 6: Organizzazioni e Team

### Step 1: Crea Organizzazione (Opzionale)
```
Se hai progetti di team:
1. Vai a github.com/organizations/new
2. Scegli nome organizzazione
3. Configura billing (gratuito per pubblico)
4. Invita membri team
```

### Step 2: Team Management
```markdown
Best practices per organizzazioni:
- Usa team per raggruppare sviluppatori
- Configura permessi granulari
- Usa repository templates
- Imposta branch protection rules
```

## Checklist di Completamento

### Account Base
- [ ] Account creato e email verificata
- [ ] Username professionale scelto
- [ ] Foto profilo caricata
- [ ] Bio completata con informazioni pertinenti
- [ ] Informazioni di contatto aggiunte

### Sicurezza
- [ ] Two-Factor Authentication abilitato
- [ ] Recovery codes salvati in luogo sicuro
- [ ] SSH key generata e aggiunta
- [ ] Connessione SSH testata con successo
- [ ] Password robusta impostata

### Configurazione
- [ ] Notifiche email configurate
- [ ] GitHub Mobile installato e configurato
- [ ] Tema preferito impostato
- [ ] Profile README creato (opzionale)
- [ ] Impostazioni privacy configurate

### Primi Passi
- [ ] Primo repository creato
- [ ] Profilo GitHub esploratore
- [ ] Almeno 3 repository interessanti seguiti
- [ ] GitHub CLI installato (opzionale)

## Troubleshooting Comune

### Problema: SSH non funziona
```bash
# Verifica chiave SSH
ls -la ~/.ssh

# Verifica ssh-agent
ssh-add -l

# Re-add chiave se necessario
ssh-add ~/.ssh/id_ed25519

# Test verbose per debug
ssh -vT git@github.com
```

### Problema: 2FA non funziona
```
Soluzioni:
1. Verifica sincronizzazione orario
2. Usa recovery codes se app non disponibile
3. Genera nuovo QR code se necessario
4. Contatta GitHub support in caso estremo
```

### Problema: Notifiche troppo frequenti
```
Settings → Notifications → Custom routing

Configura regole specifiche:
- Solo mention dirette via email
- Watching solo per repository critici
- Disabilita notifiche per fork
```

## Risorse Aggiuntive

### Link Utili
- [GitHub Docs](https://docs.github.com)
- [SSH Key Tutorial](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
- [2FA Setup](https://docs.github.com/en/authentication/securing-your-account-with-two-factor-authentication-2fa)
- [Profile README Examples](https://github.com/abhisheknaiidu/awesome-github-profile-readme)

### Tool Consigliati
- **GitHub CLI**: Gestione da terminale
- **GitHub Desktop**: GUI ufficiale
- **GitKraken**: GUI avanzata
- **VS Code GitHub Extension**: Integrazione IDE

## Conclusione
Un account GitHub ben configurato è la base per una carriera di successo nello sviluppo software. Prenditi il tempo necessario per impostare tutto correttamente: ne trarrai beneficio per anni!
