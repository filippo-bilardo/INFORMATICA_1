# Esplorazione delle Features di GitHub

## Obiettivo
Esplorare in modo pratico le principali funzionalità di GitHub attraverso esempi concreti e interattivi.

## Scenario
Dopo aver configurato il tuo account GitHub, è tempo di esplorare tutte le features che la piattaforma mette a disposizione per sviluppatori e team.

## Passi dell'Esplorazione

### 1. Navigazione del Repository
```bash
# Esempio di repository con molte features
# Visita: https://github.com/microsoft/vscode
```

**Elementi da osservare:**
- **README.md**: Come è strutturato e presentato
- **Issues**: Tipologie e organizzazione
- **Pull Requests**: Processo di review
- **Actions**: Workflows automatizzati
- **Wiki**: Documentazione estesa
- **Projects**: Gestione del lavoro
- **Insights**: Analytics del repository

### 2. Esplorazione Issues
```markdown
# Esempio di Issue ben strutturata
**Tipo**: Bug Report
**Labels**: bug, high-priority, needs-investigation
**Assignees**: @developer-team
**Milestone**: v2.1.0

## Descrizione
Descrizione dettagliata del problema...

## Passi per Riprodurre
1. Passo 1
2. Passo 2
3. Passo 3

## Comportamento Atteso
...

## Comportamento Attuale
...

## Environment
- OS: Windows 10
- Browser: Chrome 96
- Versione: 2.0.1
```

### 3. Code Navigation Features
```javascript
// Esempio di navigazione del codice
// Hover sui simboli per vedere definizioni
function getUserData(userId) {
    // GitHub mostra:
    // - Definizione della funzione
    // - Riferimenti nel codebase
    // - Documentazione inline
    return database.users.find(user => user.id === userId);
}
```

**Features da provare:**
- **Go to definition** (Ctrl+Click)
- **Find references**
- **Symbol search** (t key)
- **Code search** (s key)
- **File finder** (/ key)

### 4. GitHub Codespaces
```yaml
# .devcontainer/devcontainer.json
{
    "name": "Development Container",
    "image": "mcr.microsoft.com/vscode/devcontainers/javascript-node:16",
    "features": {
        "ghcr.io/devcontainers/features/docker-in-docker:1": {}
    },
    "postCreateCommand": "npm install",
    "customizations": {
        "vscode": {
            "extensions": [
                "ms-vscode.vscode-typescript-next",
                "esbenp.prettier-vscode"
            ]
        }
    }
}
```

### 5. GitHub CLI Exploration
```bash
# Installazione GitHub CLI
# Windows (con chocolatey)
choco install gh

# macOS (con homebrew)
brew install gh

# Linux (debian/ubuntu)
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
sudo apt update
sudo apt install gh

# Autenticazione
gh auth login

# Esempi di utilizzo
gh repo list                    # Lista repositories
gh issue list                   # Lista issues
gh pr create --title "New feature" --body "Description"
gh workflow run deploy.yml     # Esegui workflow
gh release create v1.0.0       # Crea release
```

### 6. GitHub Mobile Features
```markdown
# Features disponibili su GitHub Mobile:
- Notifiche in tempo reale
- Code review on-the-go
- Issue e PR management
- Repository browsing
- Merge di Pull Request
- Commenti e discussioni
```

### 7. Security Features
```yaml
# .github/dependabot.yml
version: 2
updates:
  - package-ecosystem: "npm"
    directory: "/"
    schedule:
      interval: "weekly"
    open-pull-requests-limit: 10
    reviewers:
      - "@security-team"
```

**Security tab exploration:**
- **Dependabot alerts**: Vulnerabilità nelle dipendenze
- **Code scanning**: Analisi automatica del codice
- **Secret scanning**: Rilevamento di credenziali
- **Security advisories**: Advisory di sicurezza

### 8. Marketplace e Integrations
```yaml
# Esempi di GitHub Apps utili:
- CodeClimate: Analisi qualità codice
- Slack: Notifiche e integrazioni
- Jira: Gestione progetti
- Netlify: Deploy automatico
- Heroku: Hosting e deploy
```

### 9. Advanced Search
```
# Sintassi di ricerca avanzata GitHub
user:microsoft language:typescript stars:>1000
org:google created:2023-01-01..2023-12-31
is:issue is:open label:bug assignee:@me
```

**Filtri disponibili:**
- **Repository**: `repo:owner/name`
- **Linguaggio**: `language:javascript`
- **Utente/Org**: `user:username` o `org:orgname`
- **Data**: `created:2023-01-01..2023-12-31`
- **Dimensione**: `size:>1000`
- **Stars**: `stars:>100`
- **Forks**: `forks:>50`

### 10. Collaboration Features
```markdown
# Team mention in issues/PR
@team-frontend please review this UI change
@security-team this needs security review

# Code suggestions in reviews
```suggestion
const result = await processData(input);
return result.formatted;
```

# Discussions for Q&A
Discussions tab per:
- Q&A community
- Announcements
- Feature requests
- Show and tell
```

## Esercizio Pratico

### Task 1: Repository Exploration
1. Visita un repository open source famoso (es. React, Vue, Angular)
2. Esplora tutti i tab disponibili
3. Leggi almeno 3 issues diverse
4. Guarda 2 Pull Request (una aperta, una chiusa)
5. Controlla la sezione Actions

### Task 2: Code Navigation
1. Apri un file JavaScript/Python in un repository
2. Prova tutte le scorciatoie da tastiera
3. Usa la ricerca per trovare una funzione specifica
4. Naviga attraverso i riferimenti di una funzione

### Task 3: GitHub CLI
1. Installa GitHub CLI
2. Autentica il tuo account
3. Lista i tuoi repository
4. Crea un issue da command line
5. Clona un repository usando gh

### Task 4: Mobile Experience
1. Installa GitHub Mobile
2. Configura le notifiche
3. Esplora un repository dal mobile
4. Commenta su un issue esistente

## Checklist di Completamento

- [ ] Navigato almeno 3 repository diversi
- [ ] Provato tutte le features di code navigation
- [ ] Installato e testato GitHub CLI
- [ ] Esplorato GitHub Mobile
- [ ] Compreso le security features
- [ ] Testato la ricerca avanzata
- [ ] Verificato le integrazioni disponibili
- [ ] Capito il processo di code review
- [ ] Esplorato GitHub Discussions
- [ ] Compreso GitHub Projects

## Tips e Trucchi

### Scorciatoie da Tastiera
```
t - Attiva file finder
s - Focus sulla search bar
/ - Search nel repository
? - Mostra tutte le scorciatoie
. - Apri in github.dev (VS Code web)
```

### URLs Utili
```
# Per esplorare
https://github.com/trending
https://github.com/explore
https://github.com/marketplace
https://docs.github.com
https://education.github.com
```

### Best Practices per l'Esplorazione
1. **Bookmarks**: Salva repository interessanti
2. **Watch**: Segui progetti che ti interessano
3. **Stars**: Usa le star per organizzare repository
4. **Following**: Segui sviluppatori influenti
5. **Notifications**: Configura notifiche intelligenti

## Risorse Aggiuntive

- [GitHub Docs](https://docs.github.com)
- [GitHub Skills](https://skills.github.com)
- [GitHub Blog](https://github.blog)
- [GitHub CLI Manual](https://cli.github.com/manual)
- [GitHub Mobile Docs](https://docs.github.com/en/get-started/using-github/github-mobile)

## Conclusione
GitHub è molto più di un semplice hosting per repository Git. È una piattaforma completa per il development moderno che include strumenti per collaborazione, automazione, sicurezza e deployment. L'esplorazione di tutte queste features ti darà una base solida per utilizzare GitHub professionalmente.
