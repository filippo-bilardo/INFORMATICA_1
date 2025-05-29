# Esercizio 01 - Contribuzione Open Source Reale

## 🎯 Obiettivo

Completare il **primo contributo reale** a un progetto open source seguendo l'intero workflow Fork & Pull Request, dalla ricerca del progetto al merge finale.

## 📋 Requisiti Tecnici

- **Git installato** e configurato
- **Account GitHub** attivo
- **Editor di testo** preferito
- **Conoscenza base** di un linguaggio di programmazione

## ⏱️ Durata Stimata

**90-120 minuti** (inclusa ricerca progetto)

## 🎬 Scenario dell'Esercizio

Diventerai un **contributor open source** seguendo il processo completo di contribuzione a un progetto reale della community GitHub.

## 📋 Fasi dell'Esercizio

### Fase 1: Ricerca e Selezione Progetto (20 min)

#### Step 1.1: Identifica Area di Interesse

Scegli **UNA** delle seguenti categorie:

**📚 Documentazione & Tutorial**
- Progetti educational con buona documentation
- Guide e tutorial per developer
- Traduzioni di contenuti

**🔧 Developer Tools**
- CLI tools e utilities
- VS Code extensions
- GitHub Actions

**🌐 Web Development**
- Frontend libraries/components
- CSS frameworks
- JavaScript utilities

**📱 Mobile & Desktop**
- React Native components
- Electron apps
- Cross-platform tools

#### Step 1.2: Criteri di Selezione

Cerca repository che abbiano:

✅ **Good First Issue Label**
```
label:"good first issue" is:open
```

✅ **Active Maintenance**
- Ultimo commit < 30 giorni
- Issues/PR gestite regolarmente
- Maintainer responsive

✅ **Welcoming Community**
- Contributor guidelines chiari
- Code of conduct presente
- Template per issue/PR

✅ **Size appropriata**
- 100-5000 stars (né troppo piccolo né troppo grande)
- 10-100 contributors
- Codebase comprensibile

#### Step 1.3: Repository Suggeriti

**Per Principianti:**

1. **[first-contributions](https://github.com/firstcontributions/first-contributions)**
   - Specificamente per primi contributor
   - Tutorial guidato
   - Multilingue

2. **[awesome-for-beginners](https://github.com/MunGell/awesome-for-beginners)**
   - Lista progetti beginner-friendly
   - Categorizzati per linguaggio
   - Issues ben etichettate

3. **[Public APIs](https://github.com/public-apis/public-apis)**
   - Documentazione APIs pubbliche
   - Contribuzioni semplici
   - Community molto attiva

**Per Intermedi:**

1. **[freeCodeCamp](https://github.com/freeCodeCamp/freeCodeCamp)**
   - Educational platform
   - Molte opportunità contribuzione
   - Community supportiva

2. **[OpenAPI Generator](https://github.com/OpenAPITools/openapi-generator)**
   - Tool generation codice
   - Template e esempi
   - Buona documentazione

#### Step 1.4: Valutazione Finale

Completa questa **checklist** per il repository scelto:

```markdown
## Repository Evaluation

**Nome:** _____________________
**URL:** ______________________
**Stars:** ____________________

### Checks
- [ ] Ha "good first issue" label attivi
- [ ] Ultimo commit < 30 giorni
- [ ] CONTRIBUTING.md presente e chiaro
- [ ] Issue template ben definiti
- [ ] Maintainer attivi nelle discussioni
- [ ] Codebase di dimensione gestibile
- [ ] Tecnologie che conosco/voglio imparare

### Good First Issues Disponibili
1. ________________________________
2. ________________________________
3. ________________________________

**Issue Selezionata:** #______
**Motivazione:** ________________
```

### Fase 2: Setup e Fork (15 min)

#### Step 2.1: Analisi Repository

Prima di forkare, **studia** il repository:

```bash
# Clona per esplorare (temporaneo)
git clone https://github.com/OWNER/REPOSITORY.git temp-exploration
cd temp-exploration

# Esplora struttura
find . -name "*.md" | head -10
ls -la
cat CONTRIBUTING.md
cat README.md
```

#### Step 2.2: Leggi Documentation

**Documenti chiave da studiare:**

1. **README.md**
   - Overview del progetto
   - Setup instructions
   - Usage examples

2. **CONTRIBUTING.md**
   - Contribution workflow
   - Code standards
   - Testing requirements

3. **CODE_OF_CONDUCT.md**
   - Community guidelines
   - Behavior expectations

4. **Issue/PR Templates**
   - Required information
   - Format expectations

#### Step 2.3: Fork Repository

```bash
# 1. Fork via GitHub UI
# Vai su GitHub repository page
# Click "Fork" button
# Scegli account destination

# 2. Clone il TUO fork
git clone https://github.com/YOUR-USERNAME/REPOSITORY.git
cd REPOSITORY

# 3. Setup upstream remote
git remote add upstream https://github.com/ORIGINAL-OWNER/REPOSITORY.git

# 4. Verifica remote setup
git remote -v
# Output dovrebbe mostrare:
# origin    https://github.com/YOUR-USERNAME/REPOSITORY.git (fetch)
# origin    https://github.com/YOUR-USERNAME/REPOSITORY.git (push)
# upstream  https://github.com/ORIGINAL-OWNER/REPOSITORY.git (fetch)
# upstream  https://github.com/ORIGINAL-OWNER/REPOSITORY.git (push)
```

### Fase 3: Ambiente di Sviluppo (15 min)

#### Step 3.1: Setup Progetto

Segui le **exact instructions** dal README:

```bash
# Tipici setup commands (variano per progetto)

# Node.js projects
npm install
# oppure
yarn install

# Python projects
pip install -r requirements.txt
# oppure
pip install -e .

# Rust projects
cargo build

# Go projects
go mod download
```

#### Step 3.2: Verifica Setup

**Testa che tutto funzioni:**

```bash
# Run tests
npm test           # Node.js
python -m pytest   # Python
cargo test         # Rust
go test ./...      # Go

# Run development build
npm run dev        # Node.js web projects
python manage.py runserver  # Django
cargo run          # Rust

# Check linting
npm run lint       # Node.js
flake8 .          # Python
cargo clippy       # Rust
```

#### Step 3.3: Branch Strategy

```bash
# Sync with upstream prima di iniziare
git fetch upstream
git checkout main
git merge upstream/main

# Crea feature branch per il tuo lavoro
git checkout -b fix/issue-123-description
# Esempio: git checkout -b fix/typo-in-readme
# Esempio: git checkout -b feature/add-new-api-endpoint
```

### Fase 4: Implementazione (30 min)

#### Step 4.1: Comprendi il Issue

**Analisi dettagliata:**

```markdown
## Issue Analysis

**Issue Number:** #____
**Title:** _______________
**Type:** [bug fix / feature / documentation / refactor]

### Problem Description
_Cosa il issue sta chiedendo esattamente?_

### Acceptance Criteria
_Come saprai che è completo?_

### Files Probably Affected
_Quali file probabilmente dovrai modificare?_

### Related Issues/PRs
_Ci sono issue o PR collegati?_
```

#### Step 4.2: Implementa Soluzione

**Approccio sistematico:**

1. **Start Small**
   ```bash
   # Fai cambiamenti minimi necessari
   # Test frequenti durante sviluppo
   # Commit incrementali se necessario
   ```

2. **Follow Project Standards**
   ```bash
   # Rispetta code style del progetto
   # Usa naming conventions esistenti
   # Mantieni consistenza con codebase
   ```

3. **Test Your Changes**
   ```bash
   # Run existing tests
   npm test
   
   # Test manually se appropriato
   # Verifica che non hai rotto nulla
   ```

#### Step 4.3: Esempi di Contribuzioni Tipiche

**Tipo 1: Documentation Fix**
```markdown
# File: README.md
# Fix typo o miglioramento docs

PRIMA:
This libary provides utilities...

DOPO:
This library provides utilities...
```

**Tipo 2: Code Improvement**
```javascript
// File: src/utils.js
// Rimuovi codice dead o migliora performance

// PRIMA
function slowFunction(data) {
  return data.map(item => item).filter(item => item.active === true);
}

// DOPO
function optimizedFunction(data) {
  return data.filter(item => item.active);
}
```

**Tipo 3: Add Feature**
```python
# File: src/helpers.py
# Aggiungi utility function richiesta

def format_currency(amount, currency='USD'):
    """
    Format amount as currency string.
    
    Args:
        amount (float): Amount to format
        currency (str): Currency code (default: USD)
    
    Returns:
        str: Formatted currency string
    """
    symbols = {'USD': '$', 'EUR': '€', 'GBP': '£'}
    symbol = symbols.get(currency, currency)
    return f"{symbol}{amount:.2f}"
```

### Fase 5: Quality Assurance (15 min)

#### Step 5.1: Pre-commit Checks

```bash
# 1. Run tests
npm test
# Tutti i test devono passare ✅

# 2. Run linting
npm run lint
# Fix tutti i linting errors

# 3. Check formatting
npm run format
# Usa project formatter (Prettier, Black, etc.)

# 4. Manual testing
# Testa la tua feature/fix manualmente

# 5. Check for unintended changes
git diff
# Review ogni singola modifica
```

#### Step 5.2: Documentation

**Aggiorna documentazione se necessario:**

```markdown
# Se hai aggiunto feature, aggiungi examples:

## New Feature: Currency Formatting

\```python
from helpers import format_currency

# Basic usage
formatted = format_currency(123.45)
print(formatted)  # Output: $123.45

# With different currency
formatted = format_currency(123.45, 'EUR')
print(formatted)  # Output: €123.45
\```
```

#### Step 5.3: Commit Message

**Segui project commit conventions:**

```bash
# Most projects use conventional commits
git add .
git commit -m "fix: correct typo in README.md

- Fixed 'libary' to 'library' in introduction
- Improves readability for new contributors

Fixes #123"

# Alternative formats:
# "docs: update API documentation for new endpoint"
# "feat: add currency formatting utility function"
# "refactor: optimize data filtering performance"
```

### Fase 6: Pull Request Creation (15 min)

#### Step 6.1: Push to Fork

```bash
# Push your branch to your fork
git push origin fix/issue-123-description

# Se è il primo push di questo branch:
git push -u origin fix/issue-123-description
```

#### Step 6.2: Create Pull Request

**Via GitHub UI:**

1. **Vai al tuo fork** su GitHub
2. **Vedrai banner** "Compare & pull request"
3. **Click del banner** o vai a "Pull requests" → "New pull request"

**Setup PR:**
- **Base repository**: `ORIGINAL-OWNER/REPOSITORY`
- **Base branch**: `main` (or `master`)
- **Head repository**: `YOUR-USERNAME/REPOSITORY`
- **Compare branch**: `fix/issue-123-description`

#### Step 6.3: Write PR Description

**Usa il template del progetto o questo formato:**

```markdown
## Description
Brief description of changes made.

## Type of Change
- [ ] Bug fix (non-breaking change which fixes an issue)
- [ ] New feature (non-breaking change which adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update

## Related Issue
Fixes #123

## Changes Made
- Fixed typo in README.md introduction
- Updated example code to use correct spelling
- Added test case for edge case

## Testing Performed
- [ ] Ran existing test suite
- [ ] Manual testing completed
- [ ] Checked for linting errors
- [ ] Verified documentation accuracy

## Screenshots (if applicable)
[Add screenshots of UI changes if relevant]

## Checklist
- [ ] My code follows the style guidelines of this project
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] New and existing unit tests pass locally with my changes
```

### Fase 7: Review Process (15 min)

#### Step 7.1: Automatic Checks

**Attendi CI/CD risultati:**

```yaml
# Tipici automatic checks:
✅ Tests passed
✅ Linting passed
✅ Build successful
✅ Coverage maintained
❌ Security scan failed
```

**Se checks falliscono:**
```bash
# Fix issue locally
git add .
git commit -m "fix: address CI feedback"
git push origin fix/issue-123-description
# PR si aggiorna automaticamente
```

#### Step 7.2: Respond to Feedback

**When maintainer reviews:**

1. **Read carefully** tutti i commenti
2. **Ask questions** se non capisci
3. **Make requested changes** promptly
4. **Push updates** al same branch
5. **Reply to comments** quando fixato

**Esempio risposta:**
```markdown
@maintainer Thanks for the feedback! 

> Could you add a test case for the edge case?

Great point! I've added a test case in `test_helpers.py` that covers the scenario when amount is zero. The test ensures we still return a properly formatted string.

> The variable name could be more descriptive.

Agreed! I've renamed `x` to `formatted_amount` for better clarity.

All feedback addressed and tests are passing. Ready for another review! 🚀
```

#### Step 7.3: Final Steps

**Quando PR è approvata:**

1. **Maintainer mergerà** (o ti darà permesso)
2. **Celebra!** 🎉 Hai completato la tua prima contribuzione
3. **Cleanup local branches:**
   ```bash
   git checkout main
   git pull upstream main
   git branch -d fix/issue-123-description
   ```

## 📊 Delivery & Valutazione

### Deliverable Richiesti

1. **Screenshot del PR merged** o review feedback ricevuto
2. **Link al PR** che hai creato
3. **Reflection report** (template sotto)

### Template Reflection Report

```markdown
# Open Source Contribution - Reflection Report

## Contributor Information
**Nome:** ___________________
**GitHub Username:** ________
**Data:** ___________________

## Project Details
**Repository:** https://github.com/OWNER/REPO
**Issue Addressed:** #____
**PR Created:** #____
**PR Status:** [Merged / Under Review / Changes Requested]

## Contribution Summary
**Type:** [Bug Fix / Feature / Documentation / Other]
**Files Modified:** 
- file1.ext
- file2.ext

**Description:** 
Brief description of what you implemented...

## Technical Challenges
### What was difficult?
1. 
2. 
3. 

### How did you solve them?
1. 
2. 
3. 

## Learning Outcomes
### New Skills Acquired
- 
- 
- 

### Git/GitHub Concepts Reinforced
- 
- 
- 

### Project-Specific Learning
- 
- 
- 

## Community Interaction
### Maintainer Feedback Quality
**Rating:** ⭐⭐⭐⭐⭐ (1-5 stars)
**Comments:** 

### Community Welcoming
**Rating:** ⭐⭐⭐⭐⭐ (1-5 stars)
**Comments:** 

### Documentation Quality
**Rating:** ⭐⭐⭐⭐⭐ (1-5 stars)
**What could be improved:** 

## Time Investment
**Setup Time:** ___ minutes
**Development Time:** ___ minutes
**Review Cycle:** ___ minutes
**Total Time:** ___ minutes

## Future Contributions
**Will you contribute again to this project?** [Yes/No]
**Why?** 

**Other projects you'd like to contribute to:**
1. 
2. 
3. 

## Recommendations for Other Students
### Dos
- 
- 
- 

### Don'ts
- 
- 
- 

### Tips
- 
- 
- 

## Overall Experience Rating
**Rating:** ⭐⭐⭐⭐⭐ (1-5 stars)

**Most valuable part:** 

**Most challenging part:** 

**Would you recommend this exercise?** [Yes/No]
**Comments:** 
```

## 🏆 Criteri di Successo

### Obiettivi Minimi (Sufficiente)
- ✅ **Fork repository** correttamente configurato
- ✅ **Issue selezionata** appropriata per livello
- ✅ **PR creata** con descrizione adeguata
- ✅ **Feedback ricevuto** e gestito appropriatamente

### Obiettivi Standard (Buono)
- ✅ Tutti obiettivi minimi +
- ✅ **Implementazione pulita** seguendo project standards
- ✅ **Test aggiunti** se richiesti
- ✅ **Comunicazione efficace** con maintainer

### Obiettivi Avanzati (Eccellente)
- ✅ Tutti obiettivi standard +
- ✅ **PR merged** successfully
- ✅ **Contribuzione significativa** al progetto
- ✅ **Feedback positivo** da maintainer
- ✅ **Follow-up contributions** discusse

## 🎯 Estensioni Avanzate

### Per Studenti Veloci

1. **Multiple Contributions**
   - Trova e risolvi secondo issue nello stesso repository
   - Contribuisci a repository diverso

2. **Community Involvement**
   - Partecipa a discussioni in issues
   - Help altri contributor in difficoltà
   - Review PR di altri (se permesso)

3. **Documentation Contribution**
   - Migliora README del repository
   - Aggiorna tutorial o guide
   - Traduce documentazione

### Per Studenti Esperti

1. **Advanced Features**
   - Implementa feature più complessa
   - Contribuisci a core functionality
   - Fix performance issues

2. **Maintenance Tasks**
   - Aiuta con issue triage
   - Review PR di altri contributor
   - Improve CI/CD pipeline

## 🚨 Troubleshooting Comune

### Problem: CI Checks Failing

**Sintomi:**
```
❌ Tests failing
❌ Linting errors
❌ Build issues
```

**Soluzioni:**
```bash
# 1. Run checks locally first
npm test
npm run lint
npm run build

# 2. Fix errors one by one
# 3. Commit fixes
git add .
git commit -m "fix: address CI feedback"
git push origin feature-branch
```

### Problem: Merge Conflicts

**Sintomi:**
```
This branch has conflicts that must be resolved
```

**Soluzioni:**
```bash
# 1. Sync with upstream
git fetch upstream
git checkout main
git merge upstream/main

# 2. Rebase your branch
git checkout your-feature-branch
git rebase main

# 3. Resolve conflicts manually
# Edit files to fix conflicts
git add .
git rebase --continue

# 4. Force push (se necessario)
git push --force-with-lease origin your-feature-branch
```

### Problem: No Response from Maintainer

**Cosa fare:**
1. **Wait 7-14 days** (maintainer possono essere busy)
2. **Gently ping** con comment educato
3. **Check project activity** - è ancora mantenuto?
4. **Consider alternative** repository se inattivo

### Problem: PR Rejected

**Non scoraggiarti!**
1. **Read feedback carefully**
2. **Learn from rejection** - cosa può essere migliorato?
3. **Try different issue** nello stesso repository
4. **Find more beginner-friendly** project

## 📚 Risorse Aggiuntive

### Finding Good Projects
- [Good First Issues](https://goodfirstissues.com/)
- [First Timers Only](https://www.firsttimersonly.com/)
- [Awesome for Beginners](https://github.com/MunGell/awesome-for-beginners)
- [Up For Grabs](https://up-for-grabs.net/)

### Learning Resources
- [How to Contribute to Open Source](https://opensource.guide/how-to-contribute/)
- [GitHub's Git Handbook](https://guides.github.com/introduction/git-handbook/)
- [Open Source Guides](https://opensource.guide/)

### Community
- [GitHub Community Forum](https://github.community/)
- [Dev.to Open Source](https://dev.to/t/opensource)
- [Hacktoberfest](https://hacktoberfest.digitalocean.com/)

---

## 🔗 Navigazione Esercizi

- [🏠 Modulo 19 - Fork e Pull Request](../README.md)
- [➡️ Esercizio 02 - PR Management](./02-pr-management.md)
- [📚 Esempi Pratici](../esempi/)
- [📖 Guide Teoriche](../guide/)

---

*Buona fortuna con la tua prima contribuzione open source! Ricorda: ogni expert developer ha iniziato esattamente come te. La community open source è generalmente molto welcoming verso chi mostra buona volontà di imparare e contribuire.* 🚀
