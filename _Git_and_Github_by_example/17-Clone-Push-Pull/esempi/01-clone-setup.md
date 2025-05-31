# Esempio 01: Clone e Setup Completo

## 📋 Scenario
Sei un nuovo sviluppatore che deve contribuire a un progetto esistente. Devi clonare il repository, configurarlo correttamente e prepararlo per il lavoro collaborativo.

## 🎯 Obiettivi
- Clonare un repository esistente
- Configurare remote correttamente
- Verificare la configurazione
- Preparare l'ambiente di lavoro

## 🚀 Implementazione Pratica

### Fase 1: Clone Iniziale

```bash
# 1. Clonare repository pubblico di esempio
git clone https://github.com/octocat/Hello-World.git
cd Hello-World

# 2. Verificare stato dopo clone
git status
git branch -a
git remote -v

# 3. Ispezionare cronologia
git log --oneline -5
```

**Output atteso:**
```
origin  https://github.com/octocat/Hello-World.git (fetch)
origin  https://github.com/octocat/Hello-World.git (push)
```

### Fase 2: Clone con Configurazione Personalizzata

```bash
# 1. Clone in directory specifica
git clone https://github.com/github/gitignore.git mio-progetto-gitignore
cd mio-progetto-gitignore

# 2. Clone solo branch specifico (shallow clone)
git clone --branch main --single-branch --depth 1 \
  https://github.com/github/gitignore.git gitignore-light

# 3. Clone con nome remote personalizzato
git clone -o upstream https://github.com/torvalds/linux.git
cd linux
git remote -v
```

### Fase 3: Configurazione Post-Clone

```bash
# 1. Aggiungere remote aggiuntivo (fork personale)
git remote add origin https://github.com/tuousername/Hello-World.git
git remote add upstream https://github.com/octocat/Hello-World.git

# 2. Verificare configurazione remote
git remote -v
# Risultato:
# origin    https://github.com/tuousername/Hello-World.git (fetch)
# origin    https://github.com/tuousername/Hello-World.git (push)
# upstream  https://github.com/octocat/Hello-World.git (fetch)
# upstream  https://github.com/octocat/Hello-World.git (push)

# 3. Configurare branch tracking
git branch --set-upstream-to=origin/main main
```

### Fase 4: Scenario Fork Workflow

```bash
# Simulazione setup per contribuzione open source

# 1. Clone del tuo fork
git clone https://github.com/tuousername/awesome-project.git
cd awesome-project

# 2. Aggiungere upstream originale
git remote add upstream https://github.com/maintainer/awesome-project.git

# 3. Verificare e sincronizzare
git fetch upstream
git checkout main
git merge upstream/main

# 4. Creare branch per feature
git checkout -b feature/nuovo-readme
git push -u origin feature/nuovo-readme
```

## 🔧 Configurazioni Avanzate

### Setup SSH per Clone

```bash
# 1. Clone con SSH (più sicuro)
git clone git@github.com:username/repository.git

# 2. Cambiare HTTPS in SSH su repository esistente
git remote set-url origin git@github.com:username/repository.git
git remote -v
```

### Clone Parziale (Git 2.19+)

```bash
# 1. Partial clone - solo metadata
git clone --filter=blob:none https://github.com/large-repo/project.git

# 2. Treeless clone - senza tree objects
git clone --filter=tree:0 https://github.com/large-repo/project.git

# 3. Blobless clone - senza blob objects
git clone --filter=blob:limit=1k https://github.com/large-repo/project.git
```

### Setup per Team Workflow

```bash
# 1. Clone del repository team
git clone git@github.com:company/main-project.git
cd main-project

# 2. Configurazione branch di sviluppo
git checkout -b develop origin/develop
git checkout -b feature/user-auth

# 3. Setup pre-commit hooks
cp .githooks/pre-commit .git/hooks/
chmod +x .git/hooks/pre-commit

# 4. Configurare git per il team
git config user.name "Mario Rossi"
git config user.email "mario.rossi@company.com"
git config core.autocrlf false  # Per team misti Windows/Linux
```

## 📊 Verifiche e Troubleshooting

### Script di Verifica Setup

```bash
#!/bin/bash
# verify-git-setup.sh

echo "🔍 VERIFICA CONFIGURAZIONE GIT"
echo "================================"

echo "📍 Remote configurati:"
git remote -v

echo -e "\n🌿 Branch disponibili:"
git branch -a

echo -e "\n👤 Configurazione utente:"
git config user.name
git config user.email

echo -e "\n📡 Tracking branches:"
git branch -vv

echo -e "\n🔄 Ultimo fetch:"
stat .git/FETCH_HEAD 2>/dev/null || echo "Mai eseguito fetch"

echo -e "\n✅ Setup verificato!"
```

### Problemi Comuni e Soluzioni

```bash
# Problema: Clone lento
# Soluzione: Shallow clone
git clone --depth 1 https://github.com/large-repo/project.git

# Problema: Autenticazione fallita
# Soluzione: Verificare credenziali
git config --global credential.helper cache
git credential fill  # Test credenziali

# Problema: Remote URL sbagliato
# Soluzione: Correggere URL
git remote set-url origin https://github.com/correct/url.git

# Problema: Permission denied (SSH)
# Soluzione: Verificare chiavi SSH
ssh -T git@github.com
ssh-add -l  # Lista chiavi caricate
```

## 🎯 Best Practices

### 1. **Naming Convention Remote**
```bash
# Repository fork
origin    -> il tuo fork
upstream  -> repository originale

# Repository aziendale
origin    -> repository principale
personal  -> tuo fork personale
```

### 2. **Clone Sicuro**
```bash
# Sempre verificare URL prima del clone
echo "Clonando da: $REPO_URL"
git clone "$REPO_URL"

# Verificare autenticità dopo clone
cd repository
git remote -v
git log --oneline -3
```

### 3. **Setup Standardizzato**
```bash
# Script di setup team
#!/bin/bash
REPO_URL=$1
PROJECT_NAME=$(basename "$REPO_URL" .git)

git clone "$REPO_URL" "$PROJECT_NAME"
cd "$PROJECT_NAME"

# Configurazione standard team
git config user.name "$(git config --global user.name)"
git config user.email "$(git config --global user.email)"
git config core.autocrlf false
git config pull.rebase true

# Setup hooks
if [ -d ".githooks" ]; then
    cp .githooks/* .git/hooks/
    chmod +x .git/hooks/*
fi

echo "✅ Setup completato per $PROJECT_NAME"
```

## 💡 Tips e Trucchi

### Clone Multipli Intelligenti

```bash
# 1. Clonare con reference locale (risparmia spazio)
git clone --reference /path/to/local/repo https://github.com/user/repo.git

# 2. Clone mirror per backup
git clone --mirror https://github.com/user/repo.git repo-backup.git

# 3. Clone worktree per sviluppo parallelo
git clone https://github.com/user/repo.git main-work
cd main-work
git worktree add ../feature-work feature-branch
```

### Automazione Clone

```bash
# Script per clone automatico progetti team
#!/bin/bash
# auto-clone-team-repos.sh

TEAM_REPOS=(
    "git@github.com:company/project-a.git"
    "git@github.com:company/project-b.git"
    "git@github.com:company/shared-tools.git"
)

for repo in "${TEAM_REPOS[@]}"; do
    project_name=$(basename "$repo" .git)
    if [ ! -d "$project_name" ]; then
        echo "📥 Clonando $project_name..."
        git clone "$repo"
        cd "$project_name"
        git config user.email "$(git config --global user.email)"
        cd ..
    else
        echo "⏭️  $project_name già presente"
    fi
done

echo "✅ Setup team repositories completato!"
```

## 🔄 Prossimi Passi

Dopo aver padroneggiato il clone e setup:

1. **[02-Push-Workflow](./02-push-workflow.md)** - Inviare modifiche
2. **[03-Pull-Sync](./03-pull-sync.md)** - Sincronizzare cambiamenti
3. **[04-Remote-Management](./04-remote-management.md)** - Gestire remote avanzati

## 📚 Risorse Aggiuntive

- [Git Clone Documentation](https://git-scm.com/docs/git-clone)
- [SSH Key Setup GitHub](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
- [Git Remote Documentation](https://git-scm.com/docs/git-remote)
