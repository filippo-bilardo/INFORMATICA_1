# 02 - Remote Repository: Gestione Repository Remoti

## 📖 Spiegazione Concettuale

I **repository remoti** sono versioni del tuo progetto ospitate su server esterni come GitHub, GitLab, o server privati. Capire come gestire questi collegamenti è fondamentale per la collaborazione e il backup del codice.

### Cosa sono i Remote

Un **remote** è semplicemente un **collegamento nominato** a un repository Git che si trova altrove. Di default, quando cloni un repository, Git crea automaticamente un remote chiamato `origin` che punta al repository originale.

```
Repository Locale                Repository Remoto
├── .git/                        
├── config                       
│   └── [remote "origin"]        ←→  https://github.com/user/repo.git
│       url = https://...             ├── main branch
│       fetch = +refs/heads/*         ├── develop branch
└── refs/remotes/origin/              └── feature branches
    ├── main
    └── develop
```

### Perché Servono i Remote

- **Backup**: Proteggere il codice su server esterni
- **Collaborazione**: Condividere con altri sviluppatori
- **Sincronizzazione**: Mantenere allineate versioni diverse
- **Deployment**: Deploy automatico da repository

## 🌐 Tipi di Remote

### 1. Origin (Default)
```bash
# Creato automaticamente con git clone
git clone https://github.com/user/repo.git
# Crea remote "origin" automaticamente
```

### 2. Upstream (Fork workflow)
```bash
# Per contribuire a progetti open source
git remote add upstream https://github.com/original/repo.git
# upstream = repository originale
# origin = tuo fork
```

### 3. Deploy/Production
```bash
# Per deployment
git remote add production git@server.com:/var/www/app.git
git remote add staging git@staging.com:/var/www/app.git
```

### 4. Mirror/Backup
```bash
# Per backup su server diversi
git remote add backup git@backup-server.com:projects/repo.git
git remote add gitlab git@gitlab.com:user/repo.git
```

## ⚙️ Sintassi e Comandi

### Visualizzare Remote
```bash
# Lista remote configurati
git remote
# Output: origin

# Lista con URL completi
git remote -v
# Output:
# origin  https://github.com/user/repo.git (fetch)
# origin  https://github.com/user/repo.git (push)

# Dettagli specifici di un remote
git remote show origin
```

### Aggiungere Remote
```bash
# Sintassi base
git remote add <nome> <url>

# Esempi pratici
git remote add origin https://github.com/user/repo.git
git remote add upstream https://github.com/original/repo.git
git remote add backup git@backup.com:user/repo.git

# Con SSH
git remote add origin git@github.com:user/repo.git
```

### Modificare Remote
```bash
# Cambiare URL di un remote esistente
git remote set-url origin https://github.com/newuser/repo.git

# Aggiungere URL di push separato
git remote set-url --add --push origin git@github.com:user/repo.git

# Rinominare un remote
git remote rename origin oldorigin
git remote rename upstream origin
```

### Rimuovere Remote
```bash
# Rimuovere remote
git remote remove backup
git remote rm staging

# Verificare rimozione
git remote -v
```

## 🔄 Workflow con Multiple Remote

### Fork Workflow (Open Source)
```bash
# 1. Fork su GitHub (tramite web interface)
# 2. Clone del tuo fork
git clone https://github.com/tuo-username/progetto.git
cd progetto

# 3. Aggiungi upstream (originale)
git remote add upstream https://github.com/autore-originale/progetto.git

# 4. Verifica configurazione
git remote -v
# origin    https://github.com/tuo-username/progetto.git (fetch)
# origin    https://github.com/tuo-username/progetto.git (push)  
# upstream  https://github.com/autore-originale/progetto.git (fetch)
# upstream  https://github.com/autore-originale/progetto.git (push)

# 5. Mantieni aggiornato il fork
git fetch upstream
git checkout main
git merge upstream/main
git push origin main
```

### Multi-Environment Deployment
```bash
# Setup per deploy su ambienti diversi
git remote add origin https://github.com/team/app.git
git remote add staging deploy@staging.server.com:/var/www/app
git remote add production deploy@prod.server.com:/var/www/app

# Deploy su staging
git push staging main

# Deploy su production  
git push production main

# Verifica stato
git remote -v
```

### Team Collaboration
```bash
# Team member workflow
git clone https://github.com/company/project.git
cd project

# Aggiungi remote personali per collaboratori
git remote add alice https://github.com/alice/project.git  
git remote add bob https://github.com/bob/project.git

# Fetch lavoro di un collaboratore
git fetch alice
git checkout -b review-alice-feature alice/feature-branch

# Merge dopo review
git checkout main
git merge review-alice-feature
git push origin main
```

## 🔍 Casi d'Uso Avanzati

### 1. Mirroring tra Servizi
```bash
# Sync tra GitHub e GitLab
git remote add github git@github.com:user/repo.git
git remote add gitlab git@gitlab.com:user/repo.git

# Push su entrambi
git push github main
git push gitlab main

# Script per sync automatico
#!/bin/bash
git push --all github
git push --all gitlab
git push --tags github  
git push --tags gitlab
```

### 2. Repository con Submoduli
```bash
# Progetto principale
git clone https://github.com/company/main-app.git
cd main-app

# Submoduli con remote separati
git submodule add https://github.com/company/auth-module.git modules/auth
git submodule add https://github.com/company/ui-components.git modules/ui

# Update tutti i submoduli
git submodule update --remote --recursive
```

> 📖 **Approfondimento**: Per una guida completa sui submoduli, consulta [06 - Git Submodules](./06-git-submodules.md)

### 3. Repository Monorepo con Subtree
```bash
# Setup per monorepo con team separati
git remote add origin https://github.com/company/monorepo.git
git remote add frontend-team https://github.com/company/frontend-only.git
git remote add backend-team https://github.com/company/backend-only.git

# Push subtree a team specifici
git subtree push --prefix=frontend frontend-team main
git subtree push --prefix=backend backend-team main
```

> 📖 **Approfondimento**: Per una guida completa sui subtree, consulta [07 - Git Subtree](./07-git-subtree.md)

## ⚠️ Errori Comuni e Soluzioni

### 1. Remote Origin Non Configurato
```bash
# ❌ ERRORE: Tentare push senza remote
git push
# fatal: No configured push destination

# ✅ SOLUZIONE: Aggiungi remote
git remote add origin https://github.com/user/repo.git
git push -u origin main
```

### 2. URL Remote Errato
```bash
# ❌ ERRORE: URL non raggiungibile
git push origin main
# fatal: repository 'https://github.com/user/wrong-repo.git/' not found

# ✅ SOLUZIONE: Verifica e correggi URL
git remote -v  # Verifica URL attuale
git remote set-url origin https://github.com/user/correct-repo.git
```

### 3. Conflitti tra HTTPS e SSH
```bash
# ❌ ERRORE: Mix di protocolli
git remote -v
# origin  https://github.com/user/repo.git (fetch)
# origin  git@github.com:user/repo.git (push)

# ✅ SOLUZIONE: Uniforma protocollo
git remote set-url origin git@github.com:user/repo.git
git remote set-url --push origin git@github.com:user/repo.git
```

### 4. Remote Upstream Obsoleto
```bash
# ❌ ERRORE: Upstream non aggiornato in fork
git fetch upstream
# Fetch vecchia versione

# ✅ SOLUZIONE: Verifica e aggiorna URL upstream
git remote -v
git remote set-url upstream https://github.com/new-owner/repo.git
git fetch upstream
```

## 💡 Best Practices

### 1. Naming Conventions
```bash
# ✅ NOMI CHIARI e CONSISTENTI
origin      # Il tuo repository principale
upstream    # Repository originale (per fork)
backup      # Repository di backup
staging     # Server di staging
production  # Server di produzione

# ❌ EVITA nomi generici
git remote add repo1 https://...
git remote add server https://...
git remote add test https://...
```

### 2. Security e URLs
```bash
# ✅ USA SSH per push frequenti
git remote set-url origin git@github.com:user/repo.git

# ✅ USA HTTPS per clone pubblici
git clone https://github.com/user/public-repo.git

# ✅ Verifica URLs prima di push sensibili
git remote -v
```

### 3. Documentation
```bash
# ✅ DOCUMENTA remote personalizzati
# README.md
## Development Setup
```bash
git clone https://github.com/company/project.git
git remote add staging deploy@staging.company.com:/apps/project
git remote add production deploy@prod.company.com:/apps/project
```

### 4. Automation
```bash
# ✅ SCRIPT per setup automatico
#!/bin/bash
# setup-remotes.sh
git remote add origin git@github.com:${USER}/$(basename $(pwd)).git
git remote add upstream git@github.com:company/$(basename $(pwd)).git
echo "✅ Remotes configured:"
git remote -v
```

## 🧪 Quiz di Verifica

### Domanda 1
**Qual è la differenza tra `origin` e `upstream` in un fork workflow?**

<details>
<summary>Risposta</summary>

**Origin** è il tuo fork personale dove hai permessi di push. **Upstream** è il repository originale da cui hai fatto il fork - lo usi per ricevere aggiornamenti ma generalmente non hai permessi di push diretto.
</details>

### Domanda 2
**Come configuri un remote per deploy automatico?**

<details>
<summary>Risposta</summary>

```bash
git remote add production deploy@server.com:/var/www/app.git
git push production main
```
Il server deve avere configurato un bare repository e hook post-receive per il deploy automatico.
</details>

### Domanda 3
**Cosa succede se fai `git push` senza specificare il remote?**

<details>
<summary>Risposta</summary>

Git usa il remote configurato come upstream per il branch corrente. Se non è configurato, prova con `origin`. Se neanche quello esiste, restituisce errore. Puoi impostare l'upstream con `git push -u origin branch-name`.
</details>

### Domanda 4
**Come sincronizzi il tuo fork con l'upstream?**

<details>
<summary>Risposta</summary>

```bash
git fetch upstream
git checkout main  
git merge upstream/main
git push origin main
```
Questo aggiorna il tuo fork locale e poi lo sincronizza con il tuo fork remoto.
</details>

## 🛠️ Esercizio Pratico: Gestione Remote Completa

### Parte 1: Setup Base
```bash
# 1. Crea repository di test
mkdir remote-test && cd remote-test
git init
echo "# Remote Test Project" > README.md
git add README.md
git commit -m "Initial commit"

# 2. Aggiungi remote origin (simula con repo esistente)
git remote add origin https://github.com/your-username/test-repo.git

# 3. Verifica configurazione
git remote -v
```

### Parte 2: Multiple Remote Setup
```bash
# 1. Simula fork workflow
git remote add upstream https://github.com/original-owner/test-repo.git

# 2. Aggiungi remote per deployment
git remote add staging user@staging.server.com:/var/www/test.git

# 3. Lista tutti i remote
git remote -v

# 4. Mostra dettagli di origin
git remote show origin
```

### Parte 3: Modifiche e Sync
```bash
# 1. Modifica URL remote
git remote set-url origin git@github.com:your-username/test-repo.git

# 2. Simula fetch da upstream
# (questo fallirà se URL non esiste, ma è per pratica)
git fetch upstream 2>/dev/null || echo "Upstream fetch failed (expected)"

# 3. Rimuovi remote staging
git remote remove staging

# 4. Verifica configurazione finale
git remote -v
```

### Parte 4: Cleanup e Best Practices
```bash
# 1. Rinomina remote per chiarezza
git remote rename origin github

# 2. Aggiungi remote con nome descrittivo
git remote add backup-server git@backup.com:user/test-repo.git

# 3. Documenta la configurazione
echo "## Remote Configuration" >> README.md
echo "\`\`\`bash" >> README.md
git remote -v >> README.md
echo "\`\`\`" >> README.md

git add README.md
git commit -m "docs: add remote configuration documentation"
```

## 🔗 Navigazione

**Precedente:** [01 - Git Clone](./01-git-clone.md)  
**Successivo:** [03 - Git Push](./03-git-push.md)  
**Torna all'Indice:** [README del Modulo](../README.md)  
**Corso Principale:** [Git e GitHub by Example](../../README.md)

## 📚 Risorse Aggiuntive

- [Git Remote Documentation](https://git-scm.com/docs/git-remote)
- [GitHub Fork Workflow](https://docs.github.com/en/get-started/quickstart/fork-a-repo)
- [Atlassian Remote Repositories](https://www.atlassian.com/git/tutorials/syncing)
- [Pro Git Book - Remote Repositories](https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes)
