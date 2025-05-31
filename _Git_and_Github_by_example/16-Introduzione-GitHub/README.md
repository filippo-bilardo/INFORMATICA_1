# 16 - Introduzione GitHub

## 📖 Descrizione

GitHub è la piattaforma più popolare per hosting di repository Git e collaborazione nel sviluppo software. Questa esercitazione ti introduce al mondo di GitHub e ti prepara per la collaborazione professionale online.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Comprendere cos'è GitHub e come funziona
- ✅ Creare un account GitHub e configurarlo
- ✅ Navigare l'interfaccia web di GitHub
- ✅ Creare repository su GitHub
- ✅ Comprendere repository pubblici vs privati
- ✅ Configurare SSH e autenticazione
- ✅ Collegare repository locali a GitHub
- ✅ Comprendere l'ecosistema GitHub (Issues, Wiki, Actions)

## 📋 Prerequisiti

- **Padronanza Git locale** (moduli precedenti)
- **Account email attivo**
- **Connessione internet stabile**

## ⏱️ Durata Stimata

**75-90 minuti** (setup + esplorazione piattaforma)

## 🎯 Risultato Finale

Avrai un account GitHub configurato correttamente e comprenderai come GitHub estende le funzionalità di Git per la collaborazione professionale.

![GitHub Overview](./esempi/immagini/github-overview.png)

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Cos'è GitHub](./guide/01-cos-e-github.md)
2. [02 - Account e Configurazione](./guide/02-account-configurazione.md)
3. [03 - Interfaccia Web](./guide/03-interfaccia-web.md)
4. [04 - Repository su GitHub](./guide/04-repository-github.md)
5. [05 - Autenticazione SSH](./guide/05-autenticazione-ssh.md)
6. [06 - Ecosistema GitHub](./guide/06-ecosistema-github.md)

### Esempi Pratici
1. [01 - Setup Account](./esempi/01-setup-account.md)
2. [02 - Primo Repository](./esempi/02-primo-repository.md)
3. [03 - Configurazione SSH](./esempi/03-configurazione-ssh.md)
4. [04 - Esplorazione Features](./esempi/04-esplorazione-features.md)

### Esercizi di Consolidamento
1. [01 - Account Setup](./esercizi/01-account-setup.md)
2. [02 - Repository Creation](./esercizi/02-repository-creation.md)
3. [03 - Platform Exploration](./esercizi/03-platform-exploration.md)

## 🚀 Come Procedere

1. **Crea account GitHub** se non ce l'hai
2. **Configura profilo** professionale
3. **Imposta autenticazione** SSH
4. **Esplora** repository esistenti per familiarizzare

## 🔍 Cos'è GitHub?

### Hosting Git
- Repository Git nel cloud
- Backup automatico
- Accesso da qualsiasi dispositivo

### Collaborazione
- Team e organizzazioni
- Permissions e access control
- Code review integrato

### Strumenti Sviluppo
- Issue tracking
- Project management
- CI/CD con GitHub Actions
- Documentation con Wiki

## 🔍 Punti Chiave da Ricordare

- GitHub != Git (GitHub usa Git)
- Repository pubblici sono visibili a tutti
- SSH è più sicuro di HTTPS per autenticazione
- README.md è il biglietto da visita del repository
- GitHub offre molti strumenti oltre al hosting

## 🛠️ Setup Essenziale

### 1. **Account GitHub**
- Username professionale
- Email verificata
- Profilo completo con bio

### 2. **Autenticazione SSH**
```bash
ssh-keygen -t ed25519 -C "tua-email@example.com"
# Aggiungi chiave pubblica a GitHub
ssh -T git@github.com  # Test connessione
```

### 3. **Configurazione Git Locale**
```bash
git config --global user.name "Tuo Nome"
git config --global user.email "tua-email@example.com"
```

## 📊 Tipi di Repository

### Repository Pubblici
- ✅ Visibili a tutti
- ✅ Gratis
- ✅ Ottimi per portfolio
- ❌ Codice aperto a tutti

### Repository Privati
- ✅ Solo collaboratori invitati
- ✅ Codice protetto
- ✅ Gratis per account personali (limiti)
- ❌ Non contribuiscono al profilo pubblico

## 💡 Best Practices GitHub

### Profilo Professionale
- Username appropriato
- Foto profilo professionale
- Bio che descrive competenze
- Contribuzioni regolari

### Repository
- README.md descrittivo
- License appropriata
- .gitignore corretto
- Commit message chiari

## 🆘 Problemi Comuni

- **Autenticazione fallita**: Verifica SSH key
- **Repository non trovato**: Controlla URL e permissions
- **Push negato**: Verifica di essere collaboratore
- **URL wrong**: HTTPS vs SSH format

## 🔗 Alternative a GitHub

### Altre Piattaforme
- **GitLab**: Self-hosted o cloud
- **Bitbucket**: Integrazione Atlassian
- **SourceForge**: Per progetti open source
- **Codeberg**: No-profit, privacy-focused

## 📚 Risorse Aggiuntive

- [GitHub Docs](https://docs.github.com/)
- [GitHub Skills](https://skills.github.com/)
- [GitHub Community](https://github.community/)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 15-Risoluzione-Conflitti](../15-Risoluzione-Conflitti/README.md)
- [➡️ 17-Clone-Push-Pull](../17-Clone-Push-Pull/README.md)

---

**Prossimo passo**: [17-Clone-Push-Pull](../17-Clone-Push-Pull/README.md) - Sincronizzazione con repository remoti
