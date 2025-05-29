# 05 - Merge vs Rebase: Scegliere la Strategia Giusta

## 📖 Il Grande Dilemma: Merge o Rebase?

Una delle decisioni più dibattute nel mondo Git è quando usare merge vs rebase. Entrambi integrano modifiche da branch diversi, ma con filosofie e risultati molto differenti. Comprendere quando usare quale strategia è fondamentale per mantenere una cronologia progetto efficace.

## ⚖️ Confronto Filosofico

### Merge Philosophy: "Preserva la Storia"
> *"La cronologia deve riflettere quello che è realmente successo"*

- ✅ Preserva il contesto temporale originale
- ✅ Mantiene la traccia dei branch e delle collaborazioni
- ✅ Non riscrive mai la cronologia esistente
- ❌ Può creare cronologie complesse e difficili da leggere

### Rebase Philosophy: "Costruisci una Storia Pulita"
> *"La cronologia deve essere comprensibile e lineare"*

- ✅ Crea cronologie lineari e facili da leggere
- ✅ Elimina merge commit "noise"
- ✅ Migliora la leggibilità del git log
- ❌ Riscrive la cronologia (potenzialmente pericoloso)

## 🔄 Confronto Tecnico

### Scenario Base
```bash
# Situazione iniziale
main:     A---B---C---F
               \
feature:        D---E
```

### Risultato con Merge
```bash
git checkout main
git merge feature

# Risultato:
main:     A---B---C---F---M
               \         /
feature:        D---E---/
```

### Risultato con Rebase
```bash
git checkout feature
git rebase main
git checkout main
git merge feature  # Fast-forward

# Risultato:
main:     A---B---C---F---D'---E'
```

## 📊 Matrice Decisionale

| Situazione | Merge | Rebase | Perché |
|------------|-------|--------|---------|
| **Feature branch personale** | ❌ | ✅ | Cronologia pulita senza perdita di context |
| **Feature branch collaborativo** | ✅ | ❌ | Preserva lavoro di multiple persone |
| **Hotfix urgente** | ✅ | ❌ | Velocità e sicurezza |
| **Long-running feature** | ✅ | ❌ | Troppo rischio di conflitti |
| **Public branch** | ✅ | ❌ | Mai riscrivere cronologia pubblica |
| **Cleanup pre-merge** | ❌ | ✅ | Organizza commit prima dell'integrazione |
| **Release integration** | ✅ | ❌ | Audit trail importante |
| **Daily sync con main** | ❌ | ✅ | Mantieni feature branch aggiornato |

## 🎯 Quando Usare Merge

### ✅ Scenari Ideali per Merge

**1. Feature Branch Collaborative**
```bash
# Multiple developer hanno contribuito
git log --pretty="%an %s" feature/payment-system
# Alice Initial payment service
# Bob Add validation layer
# Charlie Integrate with Stripe
# Alice Add tests and documentation

# Merge preserva tutte le contribuzioni
git checkout main
git merge --no-ff feature/payment-system
```

**2. Integration di Branch Pubblici**
```bash
# Branch già pushato e condiviso
git checkout main
git merge feature/public-api
# Mai rebase su branch pubblici!
```

**3. Release e Milestone**
```bash
# Merge per release tracking
git checkout main
git merge --no-ff release/v2.0 -m "Release v2.0

- Payment system integration
- User authentication overhaul  
- Performance improvements
- Security enhancements

Closes milestone v2.0"
```

**4. Audit e Compliance**
```bash
# Quando cronologia dettagliata è richiesta per audit
git merge --no-ff feature/security-compliance -m "Add GDPR compliance

Audit trail preserved for:
- Data encryption implementation
- User consent management
- Data retention policies
- Privacy controls

Reviewed-by: Security Team
Approved-by: Legal Team"
```

### ✅ Vantaggi del Merge

**1. Cronologia Autentica**
```bash
# Vedi esattamente quando e come è stato integrato il lavoro
git log --graph --oneline
* 7a8b9c2 Merge feature/auth
|\
| * 3e4f5a6 Add password validation
| * 1c2d3e4 Add login component  
* | 9f8e7d6 Update dependencies
* | 5c4b3a2 Fix homepage bug
|/
* 0a1b2c3 Initial commit
```

**2. Rollback Granulare**
```bash
# Rollback di una feature specifica
git revert -m 1 7a8b9c2  # Reverte tutto il merge
# Oppure
git revert 3e4f5a6      # Reverte solo un commit specifico
```

**3. Blame Accuracy**
```bash
# git blame mostra l'autore originale e il timestamp corretto
git blame auth.js
# 3e4f5a6 (Alice 2024-01-15) function validatePassword() {
# 1c2d3e4 (Bob   2024-01-14)   return password.length > 8;
```

## 🎯 Quando Usare Rebase

### ✅ Scenari Ideali per Rebase

**1. Feature Branch Personale**
```bash
# Lavoro personale su feature branch
git checkout feature/my-component
git rebase main  # Metti i miei commit sopra main aggiornato

# Cronologia lineare risultante
git log --oneline
# f9e8d7c Add component tests
# 3c4d5e6 Add component styling  
# 1a2b3c4 Add basic component
# 9e8f7d6 (main) Latest main commit
```

**2. Cleanup Pre-Integration**
```bash
# Interactive rebase per cleanup
git rebase -i HEAD~5
# Squash, reorder, edit commit messages prima del merge
```

**3. Sync Branch con Main**
```bash
# Mantieni feature branch aggiornato
git checkout feature/long-running
git rebase main  # Invece di merge main into feature
```

**4. Linear History Requirement**
```bash
# Progetti che richiedono cronologia lineare
git checkout feature/clean-history
git rebase main
git checkout main
git merge feature/clean-history  # Fast-forward
```

### ✅ Vantaggi del Rebase

**1. Cronologia Pulita e Lineare**
```bash
# Storia facile da leggere
git log --oneline
# f9e8d7c Add user dashboard
# 3c4d5e6 Add user authentication
# 1a2b3c4 Add user registration
# 9e8f7d6 Add homepage
# 5e4d3c2 Initial commit
```

**2. Bisect Efficace**
```bash
# git bisect più efficace con cronologia lineare
git bisect start
git bisect bad HEAD
git bisect good v1.0
# Ogni step è più significativo
```

**3. Cherry-Pick Semplificato**
```bash
# Più facile identificare e cherry-pick commit specifici
git cherry-pick 3c4d5e6  # Commit ben identificabile
```

## ⚠️ I Pericoli del Rebase

### 🚨 Golden Rule of Rebase
> **"Never rebase public branches"**

```bash
# ❌ PERICOLOSO - Non fare mai questo!
git checkout main
git rebase feature  # Riscrive cronologia di main pubblico

# ✅ SICURO - Fai sempre così
git checkout feature
git rebase main    # Riscrive solo cronologia locale
```

### 🔥 Scenari Catastrofici

**1. Rebase di Branch Condiviso**
```bash
# Team member A
git checkout shared-feature
git push origin shared-feature

# Team member B  
git checkout shared-feature
git rebase main         # ❌ DISASTER!
git push origin shared-feature --force

# Team member A (next day)
git pull origin shared-feature
# Error: Your branch has diverged... WTF?
```

**2. Force Push Accidentale**
```bash
# ❌ Dopo rebase, force push distrugge lavoro altrui
git rebase main
git push origin feature --force  # ⚠️ DANGEROUS se altri hanno pull

# ✅ Usa force-with-lease per safety
git push origin feature --force-with-lease
```

## 🛠️ Strategie Ibride

### 1. Rebase + Merge (Best of Both Worlds)

```bash
# 1. Cleanup locale con rebase
git checkout feature/my-work
git rebase -i main  # Cleanup commits

# 2. Integration con merge
git checkout main
git merge --no-ff feature/my-work -m "Add my feature

Clean commits from feature branch:
- Well-organized implementation
- Comprehensive tests
- Updated documentation"
```

### 2. Merge Workflow con Rebase Interno

```bash
# Workflow team consigliato
# 1. Develop su feature branch
git checkout -b feature/new-api

# 2. Sync periodico con rebase (mantieni aggiornato)
git fetch origin
git rebase origin/main

# 3. Cleanup finale prima dell'integration
git rebase -i origin/main

# 4. Integration finale con merge
git checkout main
git merge --no-ff feature/new-api
```

### 3. Squash Workflow Alternativo

```bash
# Alternativa che combina vantaggi
# 1. Develop liberamente
git checkout -b feature/complex
# ... molti commit di sviluppo ...

# 2. Squash merge finale
git checkout main
git merge --squash feature/complex
git commit -m "Comprehensive commit message"
```

## 🔧 Configurazioni e Automazioni

### 1. Git Aliases per Workflow

```bash
# .gitconfig aliases
[alias]
    # Safe rebase workflow
    sync = !git fetch origin && git rebase origin/main
    
    # Interactive cleanup
    cleanup = rebase -i HEAD~10
    
    # Safe merge workflow
    feature-merge = !git checkout main && git merge --no-ff
    
    # Combined workflow
    integrate = !git sync && git cleanup && git feature-merge
```

### 2. Branch Protection Rules

```bash
# GitHub/GitLab branch protection
# 1. Protect main branch from force push
# 2. Require pull request reviews
# 3. Require status checks (tests)
# 4. Prohibit rebase on main
```

### 3. Pre-Push Hook per Safety

```bash
# .git/hooks/pre-push
#!/bin/bash

protected_branch='main'
current_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')

if [ $protected_branch = $current_branch ]; then
    echo "❌ Direct push to main branch blocked"
    echo "Use pull request workflow"
    exit 1
fi

# Warn about force push
if [[ "$*" == *"--force"* ]]; then
    echo "⚠️  WARNING: Force push detected"
    read -p "Are you sure? (y/n): " confirm
    if [ "$confirm" != "y" ]; then
        exit 1
    fi
fi
```

## 📈 Esempi Pratici Dettagliati

### Esempio 1: Personal Feature Development

```bash
# 1. Setup feature branch
git checkout -b feature/user-settings
echo "User settings page" > settings.js
git add . && git commit -m "Add basic settings page"

echo "Settings validation" >> settings.js
git add . && git commit -m "Add form validation"

# 2. Main evolve mentre lavori
git checkout main
echo "Main evolution" > other.js
git add . && git commit -m "Other team work"

# 3. Sync feature branch con rebase
git checkout feature/user-settings
git rebase main  # Linear history

# 4. Merge pulito
git checkout main
git merge feature/user-settings  # Fast-forward

# Risultato: cronologia lineare
git log --oneline
# a1b2c3d Add form validation
# 9e8f7d6 Add basic settings page  
# 3c4d5e6 Other team work
# 7f8e9a0 Previous main work
```

### Esempio 2: Team Collaboration Scenario

```bash
# Team working on payment system
git checkout -b feature/payment-team

# Alice starts
echo "Payment service" > payment.js
git add . && git commit -m "Initial payment service (Alice)"

# Bob joins (pulls branch)
git pull origin feature/payment-team
echo "Validation layer" >> payment.js
git add . && git commit -m "Add validation (Bob)"
git push origin feature/payment-team

# Alice continues
git pull origin feature/payment-team
echo "Stripe integration" >> payment.js
git add . && git commit -m "Integrate Stripe (Alice)"
git push origin feature/payment-team

# Integration time - use MERGE to preserve collaboration
git checkout main
git merge --no-ff feature/payment-team -m "Merge payment system

Team collaboration between Alice and Bob:
- Initial payment service foundation
- Input validation and error handling
- Stripe payment gateway integration

Tested and reviewed by both developers"

# Result preserves team collaboration context
git log --graph --oneline
* a1b2c3d Merge payment system
|\
| * 9e8f7d6 Integrate Stripe (Alice)
| * 3c4d5e6 Add validation (Bob)  
| * 7f8e9a0 Initial payment service (Alice)
|/
* 5d4c3b2 Previous main work
```

### Esempio 3: Release Integration Workflow

```bash
# Complex release with multiple features
git checkout -b release/v2.0

# Integrate feature 1 (personal branch - rebase first)
git checkout feature/dashboard
git rebase main
git checkout release/v2.0
git merge feature/dashboard

# Integrate feature 2 (team branch - merge directly)  
git merge --no-ff feature/payment-system

# Integrate feature 3 (external contribution - squash)
git merge --squash feature/external-contrib
git commit -m "Add external contribution: advanced search"

# Final release merge
git checkout main
git merge --no-ff release/v2.0 -m "Release v2.0

Major features:
- User dashboard with analytics  
- Payment system with Stripe
- Advanced search functionality

Release notes:
- 15 new features
- 23 bug fixes
- Performance improvements
- Security enhancements

Tested across all supported platforms"
```

## 🚨 Recovery e Troubleshooting

### 1. Undo Rebase Disastroso

```bash
# Trova il commit prima del rebase
git reflog
# a1b2c3d HEAD@{0}: rebase finished
# 9e8f7d6 HEAD@{1}: rebase: pick commit  
# 3c4d5e6 HEAD@{2}: checkout: moving from main to feature
# 7f8e9a0 HEAD@{3}: commit: my important work

# Reset al punto prima del rebase
git reset --hard HEAD@{3}

# Oppure usa ORIG_HEAD (disponibile subito dopo rebase)
git reset --hard ORIG_HEAD
```

### 2. Fix Force Push Disaster

```Bash
# Scenario: qualcuno ha fatto force push che ha cancellato lavoro
# 1. Find lost commits
git reflog --all
git fsck --lost-found

# 2. Recover specific commits
git cherry-pick <lost-commit-hash>

# 3. Recreate branch from lost work
git checkout -b recovery-branch <lost-commit-hash>
```

### 3. Merge vs Rebase Decision Recovery

```bash
# Se hai fatto merge ma volevi rebase
git reset --hard HEAD~1  # Undo merge
git checkout feature
git rebase main
git checkout main  
git merge feature  # Now fast-forward

# Se hai fatto rebase ma volevi preservare merge commits
# (Più difficile - richiede ricostruzione)
git checkout feature-backup  # Hopefully you have backup
git checkout main
git merge --no-ff feature-backup
```

## 📚 Best Practices Finali

### 1. **Team Guidelines**

```markdown
# Team Git Workflow Guidelines

## Default Strategy: Rebase for Personal, Merge for Team

### Personal Feature Branches
- Rebase regularly to stay current with main
- Interactive rebase to cleanup before integration
- Fast-forward merge to main

### Collaborative Feature Branches  
- Never rebase shared branches
- Use merge commits to preserve collaboration
- Include team context in merge messages

### Special Cases
- Hotfix: Direct merge to main
- Experimental: Squash merge
- External contributions: Squash merge with attribution
```

### 2. **Automation Rules**

```bash
# Branch naming conventions
# personal/username/feature-name  → rebase workflow
# team/feature-name               → merge workflow  
# hotfix/issue-name              → direct merge
# experiment/test-name           → squash merge
```

### 3. **Code Review Integration**

```bash
# Pull request workflow
# 1. Feature development with rebase sync
git checkout feature/my-work
git rebase main

# 2. PR with clean commits
git push origin feature/my-work

# 3. Merge via PR (preserves review context)
# GitHub/GitLab handles merge strategy
```

---

## 🔗 Link Correlati

- **[01 - Tipi di Merge](01-tipi-merge.md)** - Panoramica generale
- **[02 - Fast-Forward Merge](02-fast-forward.md)** - Merge lineari
- **[03 - Recursive Merge](03-recursive-merge.md)** - Merge con conflitti
- **[04 - Squash Merge](04-squash-merge.md)** - Cleanup cronologia
- **[06 - Strategie Avanzate](06-strategie-avanzate.md)** - Tecniche specializzate

---

**💡 Ricorda**: Non esiste una strategia universalmente migliore. La scelta tra merge e rebase dipende dal contesto: collaborazione vs pulizia, audit vs leggibilità, sicurezza vs ottimizzazione. Quando in dubbio, merge è più sicuro!
