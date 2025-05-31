# Pull Request Guidelines

## 📋 Panoramica

Le Pull Request (PR) sono il cuore della collaborazione nel nostro progetto. Questa guida definisce gli standard per creare, revisionare e gestire PR efficaci.

## 🎯 Prima di Creare una PR

### Pre-requisiti
- [ ] Branch feature creato da `develop`
- [ ] Tutti i test passano localmente
- [ ] Codice formattato secondo gli standard
- [ ] Documentazione aggiornata se necessario
- [ ] Issue correlata collegata

### Preparazione del Codice
```bash
# Verifica dello stato
git status
git log --oneline -5

# Test locali
npm run test
npm run lint
npm run build

# Sincronizzazione con develop
git fetch origin
git rebase origin/develop

# Push finale
git push origin feature/nome-feature
```

## 📝 Template Pull Request

### Titolo della PR
```
<type>(<scope>): <description>

Esempi:
feat(auth): implement JWT authentication
fix(ui): resolve mobile layout issues
docs(readme): update setup instructions
test(api): add integration test coverage
```

### Descrizione della PR

```markdown
## 📖 Descrizione
Breve descrizione delle modifiche e della motivazione.

## 🔄 Tipo di Modifica
- [ ] 🐛 Bug fix (non-breaking change che risolve un issue)
- [ ] ✨ Nuova feature (non-breaking change che aggiunge funzionalità)
- [ ] 💥 Breaking change (fix o feature che causa malfunzionamenti in funzionalità esistenti)
- [ ] 📚 Aggiornamento documentazione
- [ ] 🔧 Refactoring (nessun cambiamento funzionale)
- [ ] 🧪 Miglioramento test
- [ ] 🎨 Miglioramenti UI/UX

## 🧪 Testing
- [ ] Test unitari passano localmente
- [ ] Test di integrazione passano localmente
- [ ] Test manuali completati
- [ ] Copertura test mantenuta/migliorata

### Test Scenarios
Descrivi gli scenari di test principali:
1. **Scenario 1**: Descrizione e risultato atteso
2. **Scenario 2**: Descrizione e risultato atteso

## 📱 Screenshots/GIFs (se applicabile)
<!-- Aggiungi evidence visuale delle modifiche UI -->

### Prima
![Before](link-to-before-screenshot)

### Dopo  
![After](link-to-after-screenshot)

## 🔗 Issue Correlate
- Closes #123
- Related to #456
- Fixes #789

## 🚀 Note di Deployment
- [ ] Database migrations richieste
- [ ] Environment variables aggiornate
- [ ] Configurazione servizi terzi necessaria
- [ ] Cache clearing richiesto
- [ ] Documentazione deployment aggiornata

## ✅ Checklist Sviluppatore
- [ ] Codice segue le linee guida di stile del team
- [ ] Self-review completata
- [ ] Commenti aggiunti per logica complessa
- [ ] Documentazione aggiornata
- [ ] Nessun codice di debug rimasto (console.log, etc.)
- [ ] Considerazioni performance valutate
- [ ] Implicazioni sicurezza considerate

## 🤔 Domande per i Reviewer
- Ci sono preoccupazioni sull'approccio utilizzato?
- Dovremmo considerare implementazioni alternative?
- Ci sono implicazioni di performance?
- La soluzione è scalabile?

## 📋 Checklist Review
- [ ] Funzionalità implementata correttamente
- [ ] Codice leggibile e manutenibile
- [ ] Test adeguati e significativi
- [ ] Documentazione appropriata
- [ ] Nessun problema di sicurezza
- [ ] Performance accettabile
```

## 🔍 Processo di Review

### 1. Assegnazione Reviewer
- **Feature PR**: Almeno 1 reviewer del team
- **Critical PR**: 2+ reviewer incluso tech lead
- **Hotfix PR**: Review accelerata ma obbligatoria

### 2. Review Checklist

#### Funzionalità
- [ ] La PR risolve il problema descritto nell'issue
- [ ] La logica è corretta e completa
- [ ] I casi limite sono gestiti
- [ ] Le condizioni di errore sono gestite appropriatamente

#### Qualità del Codice
- [ ] Il codice è leggibile e auto-documentante
- [ ] Segue le convenzioni del progetto
- [ ] Non ci sono duplicazioni di codice
- [ ] Le astrazioni sono appropriate
- [ ] I nomi di variabili/funzioni sono descrittivi

#### Testing
- [ ] Copertura test adeguata (minimo 80%)
- [ ] Test sono significativi e stabili
- [ ] Nomi test sono descrittivi
- [ ] Nessun test eliminato senza motivo

#### Sicurezza
- [ ] Input validation implementata
- [ ] Nessuna informazione sensibile nel codice
- [ ] Controlli di autorizzazione appropriati
- [ ] Vulnerabilità note evitate

#### Performance
- [ ] Nessun impatto negativo significativo
- [ ] Query database ottimizzate
- [ ] Bundle size considerato
- [ ] Lazy loading dove appropriato

### 3. Tipi di Feedback

#### ✅ Approve
```
Looks good! Great work on the implementation.
Particularly liked the error handling approach.
```

#### 🔄 Request Changes
```
The logic looks good overall, but please address:
1. Add input validation for the email field
2. Consider extracting the validation logic into a utility function
3. Add test coverage for the error scenarios
```

#### 💬 Comment
```
Consider using a Map instead of an Object for better performance
with large datasets. Not blocking, but could be a future optimization.
```

### 4. Risposta ai Feedback
```
Thanks for the review! I've addressed the feedback:

1. ✅ Added email validation with regex and error messages
2. ✅ Extracted validation to `utils/validation.js`
3. ✅ Added test coverage - now at 95%

The Map suggestion is great - created issue #456 to track this optimization.
```

## 🚀 Merge Strategies

### Feature Branches → Develop
- **Strategy**: Squash and Merge
- **Rationale**: Storia pulita, commit atomici
- **Message**: `feat: implement user authentication (#123)`

### Release Branches → Main
- **Strategy**: Merge Commit
- **Rationale**: Preserva storia della release
- **Message**: `Merge release/1.2.0 into main`

### Hotfix Branches → Main
- **Strategy**: Merge Commit
- **Rationale**: Tracciabilità completa del fix
- **Message**: `Merge hotfix/critical-security-fix into main`

## 🔒 Branch Protection Rules

### Develop Branch
```yaml
protection_rules:
  required_status_checks:
    - continuous-integration
    - unit-tests
    - lint-check
  required_pull_request_reviews:
    required_approving_review_count: 1
    dismiss_stale_reviews: true
    require_code_owner_reviews: false
  restrictions: []
  enforce_admins: false
```

### Main Branch
```yaml
protection_rules:
  required_status_checks:
    - continuous-integration
    - security-scan
    - e2e-tests
  required_pull_request_reviews:
    required_approving_review_count: 2
    dismiss_stale_reviews: true
    require_code_owner_reviews: true
  restrictions:
    users: []
    teams: [admin]
  enforce_admins: true
```

## 🎯 Best Practices

### Per gli Sviluppatori

#### 1. Dimensione della PR
- **Ideale**: 200-400 linee di codice
- **Massimo**: 800 linee (eccezioni rare)
- **Strategia**: Spezzare feature grandi in PR multiple

#### 2. Commit nella PR
```bash
# Buoni esempi
feat: add user registration form
test: add user registration validation tests
docs: update user management documentation

# Evitare
Fix stuff
WIP
Commit 1, 2, 3...
```

#### 3. Self-Review
Prima di richiedere review:
1. Leggi ogni riga di codice modificato
2. Verifica che i test coprano le modifiche
3. Controlla che la documentazione sia aggiornata
4. Valuta impatti su altre parti del sistema

### Per i Reviewer

#### 1. Tempistiche
- **Standard PR**: Review entro 24 ore
- **Hotfix PR**: Review entro 2 ore
- **Draft PR**: Review quando richiesto

#### 2. Stile di Review
```markdown
# ✅ Costruttivo
Consider using const instead of let here since the value doesn't change.
This improves code clarity and prevents accidental reassignment.

# ❌ Non costruttivo  
This is wrong, use const.
```

#### 3. Focus Areas
1. **Logica e Correttezza** (priorità alta)
2. **Sicurezza** (priorità alta)
3. **Performance** (priorità media)
4. **Stile e Convenzioni** (priorità bassa)

## 🔧 Automazioni GitHub

### PR Template Automatico
```markdown
<!-- .github/pull_request_template.md -->
[Template content from above]
```

### Auto-Assignment
```yaml
# .github/CODEOWNERS
# Global owners
* @team-lead @senior-dev

# Frontend specific
/src/components/ @frontend-team
/src/styles/ @ui-team

# Backend specific  
/src/api/ @backend-team
/src/database/ @database-team

# Documentation
*.md @docs-team
```

### Status Checks
```yaml
# .github/workflows/pr-checks.yml
name: PR Checks
on:
  pull_request:
    branches: [develop, main]

jobs:
  lint:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run ESLint
        run: npm run lint

  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run Tests
        run: npm run test:coverage

  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Build Project
        run: npm run build
```

## 📊 Metriche e Miglioramento

### Metriche da Tracciare
- **Time to Review**: Media tempo prima review
- **Review Iterations**: Numero medio di round di review
- **PR Size**: Distribuzione dimensioni PR
- **Merge Rate**: Percentuale PR merged vs. closed

### Retrospettive Mensili
1. **Cosa funziona bene** nel processo PR?
2. **Quali bottleneck** stiamo riscontrando?
3. **Come migliorare** l'efficienza senza sacrificare qualità?
4. **Feedback su tools** e automazioni?

## 🆘 Troubleshooting

### PR Bloccata
```bash
# Conflict resolution
git fetch origin
git rebase origin/develop
# Risolvi conflitti
git add .
git rebase --continue
git push --force-with-lease origin feature/branch
```

### Failed Checks
```bash
# Lint failures
npm run lint:fix
git add .
git commit -m "fix: resolve linting issues"

# Test failures
npm run test:watch
# Fix tests
git add .
git commit -m "test: fix failing unit tests"
```

### Large PR Breakdown
1. Identifica componenti indipendenti
2. Crea branch separati per ogni componente
3. Submetti PR separate in ordine di dipendenza
4. Collega le PR nelle descrizioni

---

*Seguendo queste linee guida, manteniamo un alto standard di qualità del codice e facilitiamo la collaborazione efficace del team.*
