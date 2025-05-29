# 07 - Workflow Comuni

## 📖 Spiegazione Concettuale

I **workflow di branching** sono metodologie standardizzate che definiscono come team e progetti utilizzano i branch per organizzare lo sviluppo. Ogni workflow ha vantaggi specifici e si adatta a diverse situazioni di team, progetti e frequenze di release.

### Perché Servono Workflow Standardizzati?

Senza un workflow definito:
- **Caos**: Ogni sviluppatore lavora diversamente
- **Conflitti**: Merge complessi e problematici
- **Rischi**: Codice instabile in produzione
- **Inefficienza**: Tempo perso in coordinamento

Con un workflow strutturato:
- **Organizzazione**: Tutti sanno cosa fare e quando
- **Qualità**: Processi di review e testing sistematici
- **Sicurezza**: Controllo delle release
- **Efficienza**: Sviluppo parallelo coordinato

## 🌊 Workflow Principali

### 1. Centralized Workflow
**Ideale per:** Team piccoli, progetti semplici, migrazioni da SVN

```
main: A---B---C---D---E---F
      (tutti lavorano su main)
```

**Caratteristiche:**
- Tutti lavorano sul branch `main`
- No branch di feature
- Sincronizzazione frequente
- Conflitti risolti durante merge

```bash
# Workflow tipico
git pull origin main
# ... lavoro ...
git add .
git commit -m "Add feature"
git pull origin main  # risolvi conflitti se necessario
git push origin main
```

### 2. Feature Branch Workflow
**Ideale per:** Team medi, sviluppo strutturato, code review

```
main:    A---B-------E-------H
              \     /       /
feature-1:     C---D       /
                    \     /
feature-2:           F---G
```

**Caratteristiche:**
- Branch separati per ogni feature
- Main sempre stabile
- Pull Request per integration
- Code review obbligatorio

```bash
# Ciclo tipico
git checkout main
git pull origin main
git checkout -b feature/user-login
# ... sviluppo ...
git push origin feature/user-login
# Pull Request su GitHub
# Dopo approval: merge in main
```

### 3. Git Flow
**Ideale per:** Progetti grandi, release pianificate, team strutturati

```
main:     A---E-------I---K
          |   |       |   |
develop:  B---C---F---G---H---J
              |   |       |
feature:      D   |       |
                  |       |
release:          |   H---I
                  |   |
hotfix:           F---G
```

**Branch Permanenti:**
- `main`: Codice in produzione
- `develop`: Integrazione features

**Branch Temporanei:**
- `feature/*`: Nuove funzionalità
- `release/*`: Preparazione release
- `hotfix/*`: Fix urgenti

```bash
# Inizializzazione Git Flow
git flow init

# Feature workflow
git flow feature start user-profile
# ... sviluppo ...
git flow feature finish user-profile

# Release workflow
git flow release start 1.2.0
# ... testing, bug fixes ...
git flow release finish 1.2.0

# Hotfix workflow
git flow hotfix start critical-bug
# ... fix ...
git flow hotfix finish critical-bug
```

### 4. GitHub Flow
**Ideale per:** Deployment continuo, team agili, web applications

```
main: A---B---E---F---I---J
       \     /   /   /   /
feature: C---D   /   /   /
              \ /   /   /
bugfix:        G---H   /
                    \ /
hotfix:              K
```

**Principi:**
- Solo branch `main` permanente
- Deploy diretto da `main`
- Feature branch + Pull Request
- Testing automatico

```bash
# Workflow GitHub Flow
git checkout main
git pull origin main
git checkout -b feature-description
# ... sviluppo ...
git push origin feature-description
# Pull Request
# Deploy da main dopo merge
```

### 5. GitLab Flow
**Ideale per:** Ambienti multipli, CI/CD avanzato

```
main:        A---B---C---D---E
              \     \     \
production:    \     F     G
                \     |     |
staging:         H----I-----J
```

**Caratteristiche:**
- Branch per ambienti (`staging`, `production`)
- Promotion tra ambienti
- Feature flags
- Environment-specific branches

## 🎯 Scegliere il Workflow Giusto

### Fattori di Decisione

| Fattore | Centralized | Feature Branch | Git Flow | GitHub Flow | GitLab Flow |
|---------|-------------|----------------|----------|-------------|-------------|
| **Team Size** | 1-3 | 3-10 | 5-20+ | 3-15 | 5-25+ |
| **Release** | Continuo | Pianificato | Strutturato | Continuo | Multi-env |
| **Complessità** | Bassa | Media | Alta | Bassa | Media-Alta |
| **CI/CD** | Basic | Medio | Complesso | Avanzato | Molto Avanzato |

### Domande Guida

1. **Quanto è grande il team?**
   - Piccolo (1-5): GitHub Flow o Feature Branch
   - Grande (10+): Git Flow o GitLab Flow

2. **Che tipo di release avete?**
   - Continue: GitHub Flow
   - Pianificate: Git Flow
   - Multiple environments: GitLab Flow

3. **Quanto è critica la stabilità?**
   - Alta: Git Flow
   - Media: Feature Branch
   - Gestibile: GitHub Flow

## 🔄 Esempi Pratici per Team

### Scenario 1: Startup Web App
**Team:** 4 sviluppatori  
**Release:** Deploy continui  
**Workflow:** GitHub Flow

```bash
# Developer A: Nuova feature
git checkout main
git pull origin main
git checkout -b add-payment-system
# ... sviluppo 2 giorni ...
git push origin add-payment-system
# Pull Request + Review
# Merge in main
# Deploy automatico

# Developer B: Bug fix (parallelo)
git checkout main
git pull origin main
git checkout -b fix-login-error
# ... fix 30 minuti ...
git push origin fix-login-error
# Pull Request rapido
# Merge in main
# Deploy automatico
```

### Scenario 2: Software Enterprise
**Team:** 15 sviluppatori  
**Release:** Mensili con hotfix  
**Workflow:** Git Flow

```bash
# Preparation release 2.1.0
git checkout develop
git pull origin develop
git flow release start 2.1.0

# Testing e bug fixes
git add .
git commit -m "Fix validation bug"

# Release completata
git flow release finish 2.1.0
# Merge in main e develop, tag creato

# Hotfix urgente
git flow hotfix start security-patch
# ... fix critico ...
git flow hotfix finish security-patch
# Deploy immediato in produzione
```

### Scenario 3: Progetto Open Source
**Team:** Vario (contributors esterni)  
**Release:** Quando pronto  
**Workflow:** Feature Branch + Fork

```bash
# Contributor esterno
git fork original-repo
git clone your-fork
git checkout -b feature/new-algorithm
# ... implementazione ...
git push origin feature/new-algorithm
# Pull Request cross-repository

# Maintainer
# Review codice
# Test automatici
# Merge se approvato
```

## ⚠️ Problemi Comuni e Soluzioni

### 1. Troppi Branch Attivi
```bash
# ❌ PROBLEMA: 20+ feature branch aperti
git branch -r | wc -l  # Troppi!

# ✅ SOLUZIONE: Limitare WIP (Work In Progress)
# Policy: max 3 feature per sviluppatore
# Review regolari branch abbandonati
```

### 2. Merge Hell
```bash
# ❌ PROBLEMA: Conflitti costanti
git merge feature/big-refactor
# CONFLICT in 50 files!

# ✅ SOLUZIONE: Branch piccoli e frequenti
# Feature branch < 1 settimana
# Rebase regolare su main/develop
git rebase main
```

### 3. Main Instabile
```bash
# ❌ PROBLEMA: Build rotte in main
# CI/CD fails dopo merge

# ✅ SOLUZIONE: Protezione branch
# Branch protection rules
# Status checks obbligatori
# Review requirements
```

### 4. Workflow Inconsistente
```bash
# ❌ PROBLEMA: Ognuno fa come vuole
# Mix di workflows diversi

# ✅ SOLUZIONE: Documentazione e training
# Workflow documentation
# Onboarding checklist
# Git hooks per enforcement
```

## 💡 Best Practices Universali

### 1. Documentazione del Workflow
```markdown
# CONTRIBUTING.md
## Workflow del Progetto

1. Fork/Clone repository
2. Crea feature branch: `git checkout -b feature/description`
3. Sviluppa e testa localmente
4. Push: `git push origin feature/description`
5. Crea Pull Request
6. Review e approval
7. Merge in main
8. Delete feature branch
```

### 2. Automazione
```yaml
# .github/workflows/pr-checks.yml
name: PR Checks
on: [pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Run tests
        run: npm test
      - name: Check formatting
        run: npm run lint
```

### 3. Branch Protection
```bash
# Settings via GitHub/GitLab UI
- Require pull request reviews
- Require status checks
- Require branches to be up to date
- Restrict pushes to main
- Require signed commits
```

### 4. Comunicazione
```bash
# ✅ Commit messages descrittivi
git commit -m "feat: add user authentication system

- Implement JWT token validation
- Add password hashing with bcrypt
- Create login/logout endpoints
- Add user session management

Closes #123"
```

## 🧪 Quiz di Verifica

### Domanda 1
**Quale workflow è migliore per un team di 3 persone che fa deploy continui?**

<details>
<summary>Risposta</summary>

GitHub Flow è ideale per team piccoli con deploy continui. È semplice (solo main + feature branches), supporta deploy rapidi e ha overhead minimo per team piccoli.
</details>

### Domanda 2
**Quando useresti Git Flow invece di GitHub Flow?**

<details>
<summary>Risposta</summary>

Git Flow è meglio per progetti con release pianificate, team grandi, e quando serve alta stabilità. Se hai bisogno di branch di release, hotfix separati, e processo di QA strutturato.
</details>

### Domanda 3
**Qual è il vantaggio principale del Feature Branch Workflow?**

<details>
<summary>Risposta</summary>

Il vantaggio principale è l'isolamento: ogni feature viene sviluppata in isolamento, permettendo code review, testing separato, e mantenendo main sempre stabile.
</details>

### Domanda 4
**Come scegli il workflow giusto per il tuo team?**

<details>
<summary>Risposta</summary>

Considera: dimensione team, frequenza release, complessità progetto, requisiti di stabilità, e cultura del team. Inizia semplice (GitHub Flow) e aggiungi complessità solo se necessario.
</details>

## 🛠️ Esercizio Pratico: Implementare GitHub Flow

### Setup Progetto
```bash
# 1. Crea repository di test
mkdir workflow-test
cd workflow-test
git init
echo "# Workflow Test Project" > README.md
git add README.md
git commit -m "Initial commit"

# 2. Simula remote (se necessario)
# git remote add origin your-repo-url
# git push -u origin main
```

### Simulazione Team Workflow
```bash
# Developer 1: Feature A
git checkout -b feature/add-header
echo "<header>My Site</header>" > header.html
git add header.html
git commit -m "Add site header"
git push origin feature/add-header

# Simula Pull Request e merge

# Developer 2: Feature B (parallelo)
git checkout main
git pull origin main
git checkout -b feature/add-footer
echo "<footer>Copyright 2025</footer>" > footer.html
git add footer.html
git commit -m "Add site footer"
git push origin feature/add-footer

# Merge delle features
git checkout main
git merge feature/add-header
git merge feature/add-footer
git push origin main

# Cleanup
git branch -d feature/add-header
git branch -d feature/add-footer
```

### Simulazione Hotfix
```bash
# Problema critico scoperto
git checkout main
git checkout -b hotfix/fix-header-typo
sed -i 's/My Site/My Website/' header.html
git add header.html
git commit -m "Fix header typo"
git push origin hotfix/fix-header-typo

# Merge rapido
git checkout main
git merge hotfix/fix-header-typo
git push origin main
git branch -d hotfix/fix-header-typo

# Verifica risultato
git log --oneline --graph
```

## 🔗 Navigazione

**Precedente:** [06 - Strategie di Branching](./05-strategie-branching.md)  
**Torna all'Indice:** [README del Modulo](../README.md)  
**Corso Principale:** [Git e GitHub by Example](../../README.md)

## 📚 Risorse Aggiuntive

- [Git Flow Documentation](https://nvie.com/posts/a-successful-git-branching-model/)
- [GitHub Flow Guide](https://guides.github.com/introduction/flow/)
- [GitLab Flow Documentation](https://docs.gitlab.com/ee/topics/gitlab_flow.html)
- [Atlassian Git Workflows](https://www.atlassian.com/git/tutorials/comparing-workflows)
