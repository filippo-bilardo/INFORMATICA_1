# 03 - Code Review e Best Practices

## 🎯 Obiettivi del Modulo

In questa guida imparerai:
- Principi del code review efficace
- Come strutturare e fornire feedback costruttivo
- Tool e workflow per code review
- Automatizzazione del processo di quality assurance

## 🔍 Fondamenti del Code Review

### 1. 🎨 Filosofia del Code Review

**Obiettivi Primari:**
- ✅ **Qualità del codice**: Identificare bug e miglioramenti
- ✅ **Knowledge sharing**: Diffondere conoscenza nel team
- ✅ **Mentoring**: Supportare crescita degli sviluppatori
- ✅ **Conformità**: Verificare aderenza agli standard
- ✅ **Security**: Identificare vulnerabilità

**Mindset Costruttivo:**
```markdown
❌ Approccio Negativo:
"Questo codice è sbagliato"
"Non capisco perché hai fatto così"
"Devi rifare tutto"

✅ Approccio Costruttivo:
"Considera questa alternativa per migliorare la performance"
"Potresti spiegare la logica dietro questa scelta?"
"Questo pattern potrebbe essere più manutenibile"
```

### 2. 📋 Checklist di Code Review

**Aspetti Funzionali:**
```markdown
□ Il codice funziona come descritto nei requisiti?
□ I casi edge sono gestiti correttamente?
□ Gli errori sono gestiti appropriatamente?
□ Le performance sono accettabili?
□ Il codice è testabile e ha test adeguati?
```

**Aspetti di Qualità:**
```markdown
□ Il codice è leggibile e autodocumentante?
□ Le variabili e funzioni hanno nomi significativi?
□ La complessità è mantenuta sotto controllo?
□ Non ci sono duplicazioni evidenti?
□ I commenti spiegano il "perché", non il "cosa"?
```

**Aspetti di Sicurezza:**
```markdown
□ Input validation è presente dove necessaria?
□ Non ci sono hardcoded secrets o credentials?
□ I permessi e autorizzazioni sono verificati?
□ I dati sensibili sono gestiti correttamente?
□ Non ci sono vulnerabilità evidenti (XSS, SQL injection, etc.)?
```

**Aspetti di Architettura:**
```markdown
□ Il codice rispetta i pattern architetturali del progetto?
□ Le dipendenze sono gestite correttamente?
□ L'interfaccia è ben definita e stabile?
□ Il codice è modulare e riusabile?
□ Non introduce coupling eccessivo?
```

## 🗣️ Comunicazione Efficace nel Code Review

### 1. 💬 Feedback Framework

**Struttura "SBI" (Situation-Behavior-Impact):**
```markdown
📍 Situation: Linea 45, funzione validateUser()
🔍 Behavior: Uso di == invece di === per confronto
💡 Impact: Potrebbe causare comparazioni inaspettate con type coercion

💡 Suggerimento: Usa === per comparazioni strict
```

**Linguaggio Positivo e Specifico:**
```markdown
❌ Vago e negativo:
"Questo non va bene"
"Codice confuso"
"Fix this"

✅ Specifico e costruttivo:
"Considera l'uso di const invece di let per questa variabile che non cambia"
"Questo pattern factory potrebbe semplificare la creazione degli oggetti"
"Aggiungi un test per il caso quando data è null"
```

### 2. 🏷️ Sistema di Tag per Feedback

**Tag Standardizzati:**
```markdown
[MUST] - Deve essere corretto prima del merge
[SHOULD] - Fortemente raccomandato
[CONSIDER] - Suggerimento per miglioramento
[NITPICK] - Preferenza stilistica minore
[QUESTION] - Richiesta di chiarimento
[PRAISE] - Riconoscimento di buon codice
```

**Esempi Pratici:**
```markdown
[MUST] Questa funzione non gestisce il caso null, potrebbe causare crash
[SHOULD] Considera l'uso di async/await invece di .then() per maggiore leggibilità
[CONSIDER] Potresti estrarre questa logica in una funzione helper riusabile
[NITPICK] Spazio mancante dopo la virgola (automaticamente fixabile con linter)
[QUESTION] Perché usi setTimeout qui invece di requestAnimationFrame?
[PRAISE] Ottima gestione degli errori con try-catch specifici!
```

### 3. 📝 Templates per Review Comments

**Template per Bug/Issue:**
```markdown
## 🐛 Issue Identificato

**Problema**: [Descrizione chiara del problema]
**Impatto**: [Conseguenze potenziali]
**Suggerimento**: [Come risolvere]

**Esempio**:
```javascript
// Codice problematico
if (user.role == 'admin') { ... }

// Suggerimento
if (user.role === 'admin') { ... }
```

**Riferimenti**: [Link a documentazione/standard]
```

**Template per Miglioramento:**
```markdown
## 💡 Opportunità di Miglioramento

**Area**: [Performance/Maintainability/Readability]
**Dettaglio**: [Spiegazione specifica]
**Beneficio**: [Perché è importante]

**Alternative**:
1. [Opzione 1 con pro/contro]
2. [Opzione 2 con pro/contro]

**Raccomandazione**: [Quale scegliere e perché]
```

## 🛠️ Tool e Workflow per Code Review

### 1. 🔧 Setup GitHub per Code Review

**Branch Protection Configuration:**
```yaml
# Repository Settings > Branches
Branch protection rules for 'main':
  Require pull request reviews before merging:
    - Required approving reviews: 2
    - Dismiss stale reviews when new commits are pushed: ✅
    - Require review from code owners: ✅
    - Restrict reviews to code owners: ❌
    
  Require status checks to pass before merging:
    - Require branches to be up to date before merging: ✅
    - Status checks that are required:
      - ✅ ci/tests-passing
      - ✅ code-quality/sonarqube
      - ✅ security/snyk-scan
      - ✅ performance/lighthouse
      
  Require conversation resolution before merging: ✅
  Require signed commits: ✅
  Include administrators: ✅
```

**Pull Request Template:**
```markdown
<!-- .github/pull_request_template.md -->

## 📋 Summary
Brief description of changes and motivation

## 🔄 Type of Change
- [ ] 🐛 Bug fix (non-breaking change which fixes an issue)
- [ ] ✨ New feature (non-breaking change which adds functionality)
- [ ] 💥 Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] 📚 Documentation update
- [ ] 🔧 Refactoring (no functional changes)
- [ ] ⚡ Performance improvement
- [ ] 🧪 Test coverage improvement

## 🧪 Testing
- [ ] Unit tests added/updated
- [ ] Integration tests added/updated
- [ ] Manual testing completed
- [ ] Performance impact assessed

## 📸 Screenshots (if applicable)
[Add screenshots for UI changes]

## 🔗 Related Issues
Closes #[issue number]

## 👀 Review Focus Areas
Please pay special attention to:
- [ ] Security implications
- [ ] Performance impact
- [ ] Error handling
- [ ] API contract changes

## 📝 Additional Notes
[Any additional context for reviewers]

---

### 🔍 Review Checklist
#### For Reviewers:
- [ ] Code follows project conventions
- [ ] All tests are passing
- [ ] Documentation is updated
- [ ] No obvious security issues
- [ ] Performance impact is acceptable
- [ ] Changes are backwards compatible (or breaking changes are documented)
```

### 2. 🤖 Automated Code Quality

**CI/CD Pipeline per Quality Gates:**
```yaml
# .github/workflows/code-review.yml
name: Code Review Quality Gates

on:
  pull_request:
    types: [opened, synchronize, reopened]

jobs:
  code-quality:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
      with:
        fetch-depth: 0  # Shallow clones should be disabled for better analysis
        
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
        
    - name: Install dependencies
      run: npm ci
      
    - name: Run linter
      run: |
        npm run lint
        npm run lint:report || true  # Generate report even if issues found
        
    - name: Run tests with coverage
      run: |
        npm run test:coverage
        
    - name: Run type checking
      run: npm run type-check
      
    - name: Run security audit
      run: |
        npm audit --audit-level moderate
        npx audit-ci --moderate
        
    - name: SonarQube analysis
      uses: sonarqube-quality-gate-action@master
      env:
        SONAR_TOKEN: ${{ secrets.SONAR_TOKEN }}
        
    - name: Performance testing
      run: |
        npm run build
        npx lighthouse-ci assert
        
    - name: Bundle size analysis
      uses: andresz1/size-limit-action@v1
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        
    - name: Comment PR with quality report
      uses: actions/github-script@v6
      with:
        script: |
          const fs = require('fs');
          
          // Read quality reports
          const lintReport = fs.readFileSync('lint-report.json', 'utf8');
          const coverageReport = fs.readFileSync('coverage/coverage-summary.json', 'utf8');
          
          // Generate comment
          const comment = `## 🔍 Code Quality Report
          
          ### 📊 Test Coverage
          ${JSON.parse(coverageReport).total.lines.pct}% lines covered
          
          ### 🔧 Lint Issues
          ${JSON.parse(lintReport).length} issues found
          
          ### 🔗 Full Reports
          - [SonarQube Analysis](${process.env.SONAR_URL})
          - [Performance Report](${process.env.LIGHTHOUSE_URL})
          `;
          
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: comment
          });
```

### 3. 🎨 Code Review Tools Integration

**ESLint Configuration per Code Review:**
```javascript
// .eslintrc.js
module.exports = {
  extends: [
    'eslint:recommended',
    '@typescript-eslint/recommended',
    'plugin:security/recommended',
    'plugin:import/recommended'
  ],
  
  rules: {
    // Code quality rules for review
    'complexity': ['error', { max: 10 }],
    'max-depth': ['error', 4],
    'max-lines-per-function': ['error', 50],
    'max-params': ['error', 4],
    
    // Security rules
    'security/detect-sql-injection': 'error',
    'security/detect-object-injection': 'error',
    'security/detect-unsafe-regex': 'error',
    
    // Best practices
    'prefer-const': 'error',
    'no-var': 'error',
    'eqeqeq': ['error', 'always'],
    'curly': ['error', 'all'],
    
    // Documentation
    'require-jsdoc': ['error', {
      require: {
        FunctionDeclaration: true,
        MethodDefinition: true,
        ClassDeclaration: true
      }
    }]
  },
  
  // Custom rules for team standards
  overrides: [
    {
      files: ['**/*.test.js', '**/*.spec.js'],
      rules: {
        'max-lines-per-function': 'off' // Allow longer test functions
      }
    }
  ]
};
```

**Prettier Configuration:**
```javascript
// .prettierrc.js
module.exports = {
  semi: true,
  trailingComma: 'es5',
  singleQuote: true,
  printWidth: 80,
  tabWidth: 2,
  useTabs: false,
  
  // Enforce consistency for review
  bracketSpacing: true,
  arrowParens: 'avoid',
  endOfLine: 'lf',
  
  // Custom formatting for readability
  overrides: [
    {
      files: '*.md',
      options: {
        printWidth: 120,
        proseWrap: 'always'
      }
    }
  ]
};
```

## 📊 Metriche e Analytics per Code Review

### 1. 📈 KPI per Code Review Process

**Metriche di Efficienza:**
```javascript
// review-metrics.js
class CodeReviewMetrics {
  static calculateMetrics(pullRequests) {
    return {
      // Time metrics
      averageReviewTime: this.calculateAverageReviewTime(pullRequests),
      averageTimeToMerge: this.calculateAverageTimeToMerge(pullRequests),
      
      // Quality metrics
      changesRequestedRate: this.calculateChangesRequestedRate(pullRequests),
      averageCommentsPerPR: this.calculateAverageComments(pullRequests),
      
      // Participation metrics
      reviewParticipationRate: this.calculateParticipationRate(pullRequests),
      codeOwnerCoverage: this.calculateCodeOwnerCoverage(pullRequests),
      
      // Size metrics
      averagePRSize: this.calculateAveragePRSize(pullRequests),
      oversizedPRRate: this.calculateOversizedPRRate(pullRequests)
    };
  }
  
  static generateReport(metrics) {
    return `
# 📊 Code Review Health Report

## ⏱️ Time Metrics
- **Average Review Time**: ${metrics.averageReviewTime} hours
- **Average Time to Merge**: ${metrics.averageTimeToMerge} hours

## 🎯 Quality Metrics  
- **Changes Requested Rate**: ${metrics.changesRequestedRate}%
- **Average Comments per PR**: ${metrics.averageCommentsPerPR}

## 👥 Participation
- **Review Participation Rate**: ${metrics.reviewParticipationRate}%
- **Code Owner Coverage**: ${metrics.codeOwnerCoverage}%

## 📏 Size Analysis
- **Average PR Size**: ${metrics.averagePRSize} lines
- **Oversized PR Rate**: ${metrics.oversizedPRRate}%

## 💡 Recommendations
${this.generateRecommendations(metrics)}
    `;
  }
  
  static generateRecommendations(metrics) {
    const recommendations = [];
    
    if (metrics.averageReviewTime > 24) {
      recommendations.push("📅 Consider setting review SLA or reminder system");
    }
    
    if (metrics.oversizedPRRate > 20) {
      recommendations.push("📦 Encourage smaller, more focused pull requests");
    }
    
    if (metrics.reviewParticipationRate < 80) {
      recommendations.push("👥 Improve review assignment and team engagement");
    }
    
    return recommendations.join('\n');
  }
}
```

### 2. 🎯 Review Quality Assessment

**Quality Scoring System:**
```javascript
// review-quality.js
class ReviewQualityAssessment {
  static scoreReview(review) {
    let score = 0;
    const weights = {
      thoroughness: 0.3,
      constructiveness: 0.25,
      timeliness: 0.2,
      specificity: 0.15,
      mentoring: 0.1
    };
    
    // Thoroughness (covers multiple aspects)
    const thoroughnessScore = this.assessThoroughness(review);
    score += thoroughnessScore * weights.thoroughness;
    
    // Constructiveness (helpful, actionable feedback)
    const constructivenessScore = this.assessConstructiveness(review);
    score += constructivenessScore * weights.constructiveness;
    
    // Timeliness (review done promptly)
    const timelinessScore = this.assessTimeliness(review);
    score += timelinessScore * weights.timeliness;
    
    // Specificity (detailed, specific comments)
    const specificityScore = this.assessSpecificity(review);
    score += specificityScore * weights.specificity;
    
    // Mentoring (knowledge sharing)
    const mentoringScore = this.assessMentoring(review);
    score += mentoringScore * weights.mentoring;
    
    return {
      overallScore: Math.round(score * 100),
      breakdown: {
        thoroughness: thoroughnessScore,
        constructiveness: constructivenessScore,
        timeliness: timelinessScore,
        specificity: specificityScore,
        mentoring: mentoringScore
      }
    };
  }
  
  static assessThoroughness(review) {
    const aspects = [
      'functionality', 'security', 'performance', 
      'maintainability', 'testing', 'documentation'
    ];
    
    const coveredAspects = aspects.filter(aspect => 
      this.reviewCoversAspect(review, aspect)
    );
    
    return coveredAspects.length / aspects.length;
  }
  
  static assessConstructiveness(review) {
    const positivePatterns = [
      /consider/i, /suggest/i, /recommend/i, 
      /might want to/i, /could be improved/i
    ];
    
    const negativePatterns = [
      /this is wrong/i, /bad code/i, /fix this/i
    ];
    
    const positiveCount = positivePatterns.filter(pattern => 
      pattern.test(review.body)
    ).length;
    
    const negativeCount = negativePatterns.filter(pattern => 
      pattern.test(review.body)
    ).length;
    
    return Math.max(0, (positiveCount - negativeCount) / positiveCount || 1);
  }
}
```

## 🎓 Code Review Training e Mentoring

### 1. 📚 Training Program Structure

**Level 1: Code Review Basics (Junior Developers)**
```markdown
## Week 1: Understanding Code Review
- What is code review and why it matters
- Different types of review (formal, informal, pair)
- Basic review checklist and common issues
- Practice: Review simple bug fixes

## Week 2: Giving Constructive Feedback  
- How to write helpful comments
- Using positive language and tag system
- When to approve vs request changes
- Practice: Review feature implementations

## Week 3: Receiving and Acting on Feedback
- How to respond to review comments
- When to push back on feedback
- Iterating on code based on reviews
- Practice: Submit PRs and incorporate feedback
```

**Level 2: Advanced Review Skills (Mid-level Developers)**
```markdown
## Week 1: Architecture and Design Review
- Evaluating architectural decisions
- Identifying design patterns and anti-patterns
- Security and performance considerations
- Practice: Review complex feature PRs

## Week 2: Cross-team and Domain Review
- Reviewing code outside your expertise
- When to involve domain experts
- Documentation and knowledge transfer
- Practice: Review PRs from different teams

## Week 3: Leading Review Culture
- Setting team review standards
- Mentoring junior developers
- Facilitating review discussions
- Practice: Lead team review retrospectives
```

### 2. 🎯 Mentoring Through Code Review

**Mentoring Feedback Templates:**
```markdown
## 🎓 Learning Opportunity

**Concept**: [Design pattern/principle]
**Current approach**: [What the mentee did]
**Alternative approach**: [Better way with explanation]
**Why it matters**: [Long-term benefits]

**Resources for learning**:
- [Article/documentation link]
- [Code example in codebase]
- [Team member to ask for more info]

**Practice suggestion**: 
Try implementing this pattern in your next PR and let's review it together.
```

**Progressive Skill Building:**
```markdown
# Developer Review Progression Plan

## Stage 1: Observer (Weeks 1-2)
- [ ] Add mentee as reviewer to learn observation skills
- [ ] Mentee provides summary of what they learned
- [ ] Focus on understanding team standards

## Stage 2: Co-reviewer (Weeks 3-4)  
- [ ] Mentee reviews alongside senior developer
- [ ] Compare findings and discuss differences
- [ ] Focus on developing eye for issues

## Stage 3: Primary Reviewer (Weeks 5-6)
- [ ] Mentee does primary review with senior backup
- [ ] Senior provides feedback on review quality
- [ ] Focus on confidence building

## Stage 4: Independent Reviewer (Week 7+)
- [ ] Mentee reviews independently
- [ ] Periodic review quality assessment
- [ ] Focus on consistency and growth
```

## 🧪 Quiz di Autovalutazione

### Domanda 1
Quale feedback è più costruttivo per un code review?

A) "Questo codice è confuso"  
B) "Risolvi questo problema"  
C) "[CONSIDER] Potresti usare un Map invece di un oggetto per lookup più efficienti?"  
D) "Non mi piace questo approccio"  

<details>
<summary>🔍 Risposta</summary>

**C) "[CONSIDER] Potresti usare un Map invece di un oggetto per lookup più efficienti?"**

È specifico, usa un tag che indica la priorità, spiega il beneficio e suggerisce una soluzione concreta.
</details>

### Domanda 2
Quanti reviewer dovrebbero approvare una PR per un branch critico come main?

A) 1 reviewer è sufficiente  
B) 2+ reviewer per maggiore sicurezza  
C) Tutti i team member devono approvare  
D) Dipende dalla dimensione della PR  

<details>
<summary>🔍 Risposta</summary>

**B) 2+ reviewer per maggiore sicurezza**

Per branch critici, almeno 2 reviewer indipendenti riducono significativamente il rischio di bug e migliorano la qualità del codice.
</details>

### Domanda 3
Cosa NON dovrebbe essere automatizzato nel processo di code review?

A) Controlli di stile e formattazione  
B) Test di sicurezza automatici  
C) Valutazione dell'architettura e design  
D) Analisi della coverage dei test  

<details>
<summary>🔍 Risposta</summary>

**C) Valutazione dell'architettura e design**

La valutazione di architettura e design richiede comprensione del contesto, esperienza e giudizio umano che non può essere automatizzato.
</details>

### Domanda 4
Quale metrica NON è utile per valutare l'efficacia del code review?

A) Tempo medio per completare una review  
B) Numero di linee di codice reviewate al giorno  
C) Percentuale di PR che richiedono modifiche  
D) Numero di bug trovati in produzione  

<details>
<summary>🔍 Risposta</summary>

**B) Numero di linee di codice reviewate al giorno**

Questa metrica può incentivare review superficiali per aumentare il volume. La qualità è più importante della quantità.
</details>

### Domanda 5
Quando è appropriato approvare una PR anche se hai dei piccoli nitpick?

A) Mai, tutti i problemi devono essere risolti  
B) Quando i nitpick sono puramente stilistici e non bloccanti  
C) Solo se il PR è urgente  
D) Quando lo sviluppatore è senior  

<details>
<summary>🔍 Risposta</summary>

**B) Quando i nitpick sono puramente stilistici e non bloccanti**

Piccoli nitpick stilistici non dovrebbero bloccare PR funzionalmente corretti. Possono essere taggati come [NITPICK] e risolti later.
</details>

## 🎯 Punti Chiave da Ricordare

### 🔑 Concetti Essenziali
1. **Code review è collaborazione**, non giudizio
2. **Feedback costruttivo** migliora team e codice
3. **Automatizzazione** per controlli meccanici
4. **Human insight** per architettura e design
5. **Continuous improvement** del processo

### ⚡ Best Practices
```markdown
✅ DO:
- Usa tag per prioritizzare feedback ([MUST], [SHOULD], [CONSIDER])
- Spiega il "perché" dei tuoi suggerimenti
- Riconosci il buon codice con [PRAISE]
- Review tempestivamente (entro 24h)
- Automatizza controlli meccanici

❌ DON'T:
- Usare linguaggio negativo o personale
- Bloccare PR per preferenze stilistiche minori
- Review troppo grandi (>400 linee)
- Ignorare il contesto e i requisiti
- Dare feedback vago senza esempi
```

### 🛠️ Tools Essenziali
- **GitHub PR reviews** con templates
- **Automated quality gates** (CI/CD)
- **Static analysis tools** (ESLint, SonarQube)
- **Review metrics dashboard**
- **Team communication tools** (Slack, Teams)

---

## 🔄 Navigazione

- [📑 Indice Modulo](../README.md)
- [⬅️ 02-Gestione-Branch-Collaborativi](./02-gestione-branch-collaborativi.md)
- [➡️ Esempi Pratici](../esempi/01-team-collaboration-workflow.md)

---

*Prossimo: Vedi esempi pratici di collaborazione in team!* 🤝
