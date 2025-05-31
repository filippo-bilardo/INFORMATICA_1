# Code Review Checklist

## 📋 Panoramica

La code review è un processo critico per mantenere la qualità del codice, condividere conoscenza e prevenire bug. Questa checklist fornisce una guida strutturata per condurre review efficaci.

## 🎯 Obiettivi della Code Review

### Qualità del Codice
- ✅ Verificare correttezza logica
- ✅ Assicurare leggibilità e manutenibilità
- ✅ Controllare aderenza agli standard
- ✅ Identificare potenziali bug

### Condivisione Conoscenza
- ✅ Trasferire best practices
- ✅ Educare su nuove tecniche
- ✅ Allineare architettura
- ✅ Mentoring team members

### Prevenzione Problemi
- ✅ Identificare vulnerabilità sicurezza
- ✅ Prevenire regressioni
- ✅ Validare performance
- ✅ Verificare scalabilità

## 🔍 Checklist Review Completa

### 1. Funzionalità e Logica

#### ✅ Correttezza Implementazione
- [ ] Il codice implementa correttamente i requisiti
- [ ] La logica è corretta e completa
- [ ] I casi limite sono gestiti appropriatamente
- [ ] Le condizioni di errore sono gestite
- [ ] Gli edge cases sono considerati

#### ✅ Validazione Business Logic
- [ ] Le regole di business sono implementate correttamente
- [ ] I workflow sono logici e completi
- [ ] Le validazioni sono appropriate
- [ ] I permessi e autorizzazioni sono corretti

### 2. Qualità del Codice

#### ✅ Leggibilità
- [ ] Il codice è auto-documentante
- [ ] I nomi di variabili/funzioni sono descrittivi
- [ ] La struttura è chiara e logica
- [ ] La complessità è gestibile
- [ ] I commenti spiegano il "perché", non il "cosa"

#### ✅ Manutenibilità  
- [ ] Il codice segue principi SOLID
- [ ] Non ci sono duplicazioni (DRY principle)
- [ ] Le funzioni hanno responsabilità singola
- [ ] Le astrazioni sono appropriate
- [ ] Il codice è facilmente estendibile

#### ✅ Stile e Convenzioni
- [ ] Segue le convenzioni del progetto
- [ ] Formatting consistente
- [ ] Naming conventions rispettate
- [ ] Struttura file appropriata
- [ ] Import/export organizzati

### 3. Sicurezza

#### ✅ Input Validation
- [ ] Tutti gli input utente sono validati
- [ ] Sanitizzazione dati implementata
- [ ] Type checking appropriato
- [ ] Range validation presente
- [ ] SQL injection prevention

#### ✅ Autorizzazione e Autenticazione
- [ ] Controlli di autorizzazione implementati
- [ ] Session management sicuro
- [ ] Token validation corretta
- [ ] Role-based access control
- [ ] Data privacy rispettata

#### ✅ Vulnerabilità Comuni
- [ ] XSS prevention implementata
- [ ] CSRF protection presente
- [ ] Secrets non hardcoded
- [ ] Logging sicuro (no sensitive data)
- [ ] Error handling non espone info sensibili

### 4. Performance

#### ✅ Efficienza Algoritmica
- [ ] Algoritmi ottimali utilizzati
- [ ] Complessità temporale accettabile
- [ ] Complessità spaziale appropriata
- [ ] Nessun loop infinito potenziale
- [ ] Ricorsione gestita appropriatamente

#### ✅ Database e I/O
- [ ] Query database ottimizzate
- [ ] Indici appropriati utilizzati
- [ ] N+1 query problem evitato
- [ ] Connessioni gestite correttamente
- [ ] Caching implementato dove appropriato

#### ✅ Frontend Performance
- [ ] Bundle size considerato
- [ ] Lazy loading implementato
- [ ] Image optimization presente
- [ ] Render performance ottimizzata
- [ ] Memory leaks prevenute

### 5. Testing

#### ✅ Copertura Test
- [ ] Unit tests per nuove funzionalità
- [ ] Integration tests dove necessari
- [ ] Edge cases testati
- [ ] Error scenarios coperti
- [ ] Copertura minima 80% raggiunta

#### ✅ Qualità Test
- [ ] Test names sono descrittivi
- [ ] Test sono indipendenti
- [ ] Setup/teardown appropriati
- [ ] Mock utilizzati correttamente
- [ ] Test sono deterministici (no flaky tests)

#### ✅ Test Structure
```javascript
// ✅ Good test structure
describe('TaskService', () => {
  describe('createTask', () => {
    it('should create task with valid data', () => {
      // Arrange
      const taskData = { title: 'Test Task', description: 'Test Desc' };
      
      // Act
      const result = taskService.createTask(taskData);
      
      // Assert
      expect(result.id).toBeDefined();
      expect(result.title).toBe('Test Task');
    });

    it('should throw error for invalid data', () => {
      // Arrange
      const invalidData = {};
      
      // Act & Assert
      expect(() => taskService.createTask(invalidData))
        .toThrow('Title is required');
    });
  });
});
```

### 6. Documentazione

#### ✅ Code Documentation
- [ ] Funzioni pubbliche documentate (JSDoc)
- [ ] API endpoints documentati
- [ ] Complex algorithms spiegati
- [ ] Configuration options documentate
- [ ] Breaking changes evidenziate

#### ✅ Update Documentation
- [ ] README aggiornato se necessario
- [ ] API docs aggiornate
- [ ] Changelog aggiornato
- [ ] Migration guides se breaking changes
- [ ] Examples aggiornati

### 7. Architecture e Design

#### ✅ Design Patterns
- [ ] Pattern appropriati utilizzati
- [ ] Separation of concerns rispettata
- [ ] Dependency injection utilizzata
- [ ] Interface segregation applicata
- [ ] Open/closed principle seguito

#### ✅ Scalabilità
- [ ] Soluzione scala con growth
- [ ] Resource usage ottimizzato
- [ ] Bottlenecks identificati
- [ ] Monitoring implementato
- [ ] Error handling robusto

## 🎨 Review Process

### 1. Preparazione Review

#### Prima di Iniziare
```bash
# Checkout del branch
git fetch origin
git checkout feature/branch-name
git pull origin feature/branch-name

# Build e test locali
npm install
npm run build
npm run test
npm run lint
```

#### Contesto Review
- [ ] Leggi la descrizione della PR
- [ ] Comprendi l'issue collegata
- [ ] Rivedi i file modificati
- [ ] Identifica il scope delle modifiche

### 2. Conduzione Review

#### Strategia di Lettura
1. **Overview**: Comprendi il big picture
2. **Architecture**: Valuta design decisions
3. **Implementation**: Esamina dettagli del codice
4. **Testing**: Verifica copertura e qualità test
5. **Documentation**: Controlla aggiornamenti docs

#### Approccio Sistematico
```markdown
# File per file review
- Start with tests (understand expected behavior)
- Review main implementation files
- Check configuration/setup files
- Verify documentation updates
```

### 3. Tipi di Feedback

#### ✅ Positive Feedback
```markdown
Great use of the Strategy pattern here! This makes the code much more 
maintainable and testable.

Nice error handling - the user will get clear feedback about what went wrong.

Love the comprehensive test coverage for the edge cases.
```

#### 🔄 Constructive Suggestions
```markdown
Consider extracting this logic into a separate function for better testability:

```javascript
// Instead of:
if (user.age >= 18 && user.hasValidId && user.country === 'US') {
  // complex logic here
}

// Consider:
if (isEligibleUser(user)) {
  // complex logic here
}
```

This would make the code more readable and easier to test.
```

#### ⚠️ Critical Issues
```markdown
🚨 Security Issue: This endpoint doesn't validate user authorization.
An authenticated user could access other users' data.

Suggest adding:
```javascript
if (req.user.id !== targetUserId && !req.user.isAdmin) {
  throw new UnauthorizedError('Access denied');
}
```
```

#### 💡 Suggestions
```markdown
💡 Performance suggestion: Consider using a Map instead of an Object 
for this lookup table. With large datasets, Map provides better 
performance for frequent lookups.

Not blocking for this PR, but could be a good optimization for the future.
```

### 4. Review Tools e Shortcuts

#### GitHub Review Tools
```markdown
# Inline comments
Line-specific feedback for precise suggestions

# Review summary  
Overall assessment with approval/changes/comments

# Suggested changes
Direct code suggestions that can be applied with one click

# Review requests
Specific questions for the author
```

#### VS Code Extensions
- **GitHub Pull Requests**: Review directly in IDE
- **GitLens**: Enhanced git integration
- **Code Spell Checker**: Catch typos
- **ESLint**: Real-time linting feedback

## 📊 Review Best Practices

### Per i Reviewer

#### 1. Mindset
- **Assume good intent**: Il codice è stato scritto per risolvere un problema
- **Be constructive**: Suggerisci soluzioni, non solo problemi
- **Explain why**: Dai contesto per le tue suggestions
- **Learn and teach**: Usa la review come opportunità di crescita

#### 2. Communication
```markdown
# ✅ Good feedback
This function is doing quite a lot. Consider breaking it down into 
smaller functions for better testability and readability. For example,
the validation logic could be extracted into `validateUserInput()`.

# ❌ Poor feedback
This function is too long.
```

#### 3. Prioritization
- **🔴 Must Fix**: Security issues, bugs, breaking changes
- **🟡 Should Fix**: Performance, maintainability, standards
- **🟢 Nice to Have**: Optimizations, style preferences

### Per gli Autori

#### 1. Risposta ai Feedback
```markdown
Thanks for the review! I've addressed the feedback:

✅ Extracted validation logic into separate function
✅ Added error handling for the edge case you mentioned  
✅ Updated tests to cover the new validation scenarios

For the performance suggestion about using Map - great idea! 
I've created issue #123 to track this optimization.
```

#### 2. Self-Review
Prima di richiedere review:
- [ ] Leggi ogni riga di codice modificato
- [ ] Verifica che i test passino
- [ ] Controlla la documentazione
- [ ] Valuta impatti su altre parti del sistema

## 🔧 Automazione Review

### Pre-commit Hooks
```javascript
// .husky/pre-commit
#!/bin/sh
npm run lint:staged
npm run test:changed
npm run type-check
```

### GitHub Actions
```yaml
name: PR Review Automation
on:
  pull_request:
    types: [opened, synchronize]

jobs:
  automated-review:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Code Quality Checks
        run: |
          npm ci
          npm run lint -- --format=json > lint-results.json
          npm run test:coverage -- --json > test-results.json
          
      - name: Comment PR
        uses: actions/github-script@v6
        with:
          script: |
            // Post automated feedback based on results
```

### Review Reminders
```yaml
name: Review Reminders
on:
  schedule:
    - cron: '0 10 * * 1-5'  # Daily at 10 AM, weekdays

jobs:
  remind-reviewers:
    runs-on: ubuntu-latest
    steps:
      - name: Find Stale PRs
        run: |
          # Find PRs without review after 24h
          # Send Slack notification to reviewers
```

## 📈 Metriche Review

### KPI da Tracciare
- **Time to First Review**: < 24 ore per standard PR
- **Review Iterations**: Media 2-3 round per PR
- **Defect Escape Rate**: Bug trovati dopo merge
- **Review Coverage**: % di linee riviste

### Dashboard Review
```markdown
### Weekly Review Stats
- 📊 PRs Reviewed: 15
- ⏱️ Avg Time to Review: 18 hours  
- 🔄 Avg Review Rounds: 2.3
- ✅ First-time Approval Rate: 65%
- 🐛 Bugs Caught in Review: 8
```

## 🆘 Troubleshooting Review

### Common Issues

#### Review Fatigue
- **Problema**: Review di bassa qualità per troppe PR
- **Soluzione**: Limite di 3-4 PR per reviewer per giorno

#### Superficial Reviews
- **Problema**: Review focalizzate solo su stile
- **Soluzione**: Checklist prioritizzata, training su critical areas

#### Slow Review Process  
- **Problema**: PR ferme per giorni
- **Soluzione**: SLA definiti, automated reminders, pair reviewing

#### Conflict Resolution
```markdown
Quando reviewer e autore non sono d'accordo:

1. **Discussion**: Spiega le ragioni di entrambe le parti
2. **Escalation**: Coinvolgi team lead se necessario
3. **Documentation**: Documenta la decisione per future reference
4. **Learning**: Usa come opportunità di crescita team
```

---

*Una review efficace richiede tempo e attenzione, ma è un investimento fondamentale nella qualità del prodotto e nella crescita del team.*
