# Guida: Conflict Resolution e Gestione Conflitti

## Introduzione

I conflitti sono una parte naturale del lavoro collaborativo in sviluppo software. Questa guida copre sia i conflitti tecnici (merge conflicts) che quelli interpersonali, fornendo strategie e strumenti per risolverli efficacemente e mantenere un ambiente di lavoro produttivo.

## Tipi di Conflitti

### 1. Conflitti di Codice (Merge Conflicts)

```bash
# Situazioni che causano merge conflicts
- Due sviluppatori modificano la stessa riga
- Un file viene rinominato da una parte e modificato dall'altra
- Modifiche in file con whitespace differences
- Refactoring simultaneo di stessa funzione
- Branch divergenti con history complesse
```

### 2. Conflitti di Processo

```yaml
Common Issues:
  - Different coding standards
  - Disagreement on architecture decisions
  - Conflicting priorities on features
  - Different approaches to testing
  - Inconsistent review criteria

Impact:
  - Delayed releases
  - Code quality issues
  - Team frustration
  - Reduced productivity
  - Technical debt accumulation
```

### 3. Conflitti Interpersonali

```yaml
Sources:
  - Communication style differences
  - Cultural and timezone challenges
  - Differing experience levels
  - Personality clashes
  - Stress and deadline pressure

Signs:
  - Heated PR discussions
  - Passive-aggressive comments
  - Avoiding collaboration
  - Reduced code review quality
  - Team morale issues
```

## Risoluzione Conflitti Tecnici

### 1. Preparazione per Merge Conflicts

```bash
# Setup per minimizzare conflicts
git config merge.tool vimdiff  # Configure merge tool
git config --global merge.conflictstyle diff3  # Show common ancestor

# Pre-merge checks
git fetch origin
git log --oneline --graph origin/main..HEAD  # See divergence
git diff origin/main...HEAD  # Preview changes

# Regular sync per ridurre conflicts
git checkout main
git pull origin main
git checkout feature-branch
git rebase main  # Keep feature branch updated
```

### 2. Risoluzione Step-by-Step

```bash
# Scenario: Merge conflict durante pull request
git checkout main
git pull origin main
git checkout feature-branch
git merge main

# Conflict detected
# Auto-merging src/utils/validation.js
# CONFLICT (content): Merge conflict in src/utils/validation.js
# Automatic merge failed; fix conflicts and then commit the result.

# Step 1: Identificare files in conflict
git status
# On branch feature-branch
# You have unmerged paths.
# Unmerged paths:
#   (use "git add <file>..." to mark resolution)
#         both modified:   src/utils/validation.js

# Step 2: Aprire file e analizzare conflict
cat src/utils/validation.js
```

### 3. Anatomia di un Merge Conflict

```javascript
// File con conflict markers
function validateEmail(email) {
<<<<<<< HEAD
  // Current branch version
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email) && email.length > 5;
||||||| merged common ancestors
  // Original version (with diff3)
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
=======
  // Incoming branch version
  const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
  return emailPattern.test(email) && email.trim().length > 0;
>>>>>>> main
}
```

### 4. Strategie di Risoluzione

```javascript
// Opzione 1: Accettare versione corrente (HEAD)
git checkout --ours src/utils/validation.js

// Opzione 2: Accettare versione incoming (main)
git checkout --theirs src/utils/validation.js

// Opzione 3: Risoluzione manuale (preferita)
function validateEmail(email) {
  // Combine both approaches for robust validation
  const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
  return emailPattern.test(email) && 
         email.trim().length > 5 && 
         email.length < 254; // RFC 5321 limit
}

// Step finale: mark risolto e commit
git add src/utils/validation.js
git commit -m "resolve: merge conflict in email validation

- Combined regex patterns for better validation
- Added length checks per RFC standards
- Maintained trim() for input sanitization"
```

### 5. Tools per Risoluzione Conflicts

```bash
# Visual merge tools
git mergetool  # Use configured merge tool

# Popular merge tools
- VSCode (built-in Git support)
- IntelliJ IDEA / WebStorm
- Sourcetree
- GitKraken
- Meld (Linux)
- P4Merge (cross-platform)

# Command line tools
git diff --conflict=diff3 file.js  # Show 3-way diff
git log --merge  # Show commits that conflict
git diff --name-only --diff-filter=U  # List conflicted files
```

## Prevenzione Conflitti

### 1. Best Practices per Branch Management

```bash
# Small, focused branches
git checkout -b feature/user-avatar  # Specific feature
# Avoid: git checkout -b big-refactor  # Too broad

# Regular sync con main branch
git fetch origin main
git rebase origin/main  # Keep branch updated

# Short-lived branches
# Target: merge within 2-3 days
# Avoid: long-running feature branches

# Clear branch naming
feature/auth-login
bugfix/email-validation  
hotfix/security-patch
chore/update-dependencies
```

### 2. Code Organization Strategies

```javascript
// ✅ Good: Minimize overlapping changes
// File 1: user-service.js (authentication logic)
class UserService {
  authenticate(credentials) { /* ... */ }
  validateUser(user) { /* ... */ }
}

// File 2: user-controller.js (API endpoints) 
class UserController {
  login(req, res) { /* ... */ }
  register(req, res) { /* ... */ }
}

// ❌ Bad: Everything in one file
// File: user.js (multiple responsibilities)
class User {
  authenticate() { /* ... */ }
  validateUser() { /* ... */ }
  login() { /* ... */ }
  register() { /* ... */ }
  // ... many other methods
}
```

### 3. Communication Patterns

```yaml
# Proactive communication
Before Starting:
  - Check who's working on related areas
  - Coordinate on shared files
  - Discuss architecture changes in advance

During Development:
  - Share work-in-progress early
  - Communicate blocking changes
  - Use draft PRs for visibility

Before Merging:
  - Notify team of large merges
  - Coordinate merge timing
  - Update shared documentation
```

## Risoluzione Conflitti di Processo

### 1. Technical Decision Framework

```markdown
# Decision Record Template

## Context
What is the technical challenge we're facing?

## Options Considered
1. **Option A**: REST API
   - Pros: Team familiar, good tooling
   - Cons: Over-fetching, versioning complexity

2. **Option B**: GraphQL  
   - Pros: Flexible queries, strong typing
   - Cons: Learning curve, complexity

## Decision
We choose Option A (REST API) because:
- Immediate productivity gain
- Lower risk for MVP timeline
- Can be evolved incrementally

## Consequences
- Accept some over-fetching for now
- Plan GraphQL evaluation for v2.0
- Document API design patterns

## Review Date
Re-evaluate this decision in 6 months
```

### 2. Code Style Conflicts

```javascript
// Solution: Automated enforcement
// .eslintrc.js
module.exports = {
  extends: ['@company/eslint-config'],
  rules: {
    'indent': ['error', 2],
    'quotes': ['error', 'single'],
    'semi': ['error', 'always'],
    'max-line-length': ['error', { code: 100 }]
  }
};

// .prettierrc
{
  "singleQuote": true,
  "tabWidth": 2,
  "semi": true,
  "printWidth": 100
}

// package.json
{
  "scripts": {
    "lint": "eslint src/",
    "format": "prettier --write src/",
    "precommit": "lint-staged"
  },
  "lint-staged": {
    "*.js": ["eslint --fix", "prettier --write"]
  }
}
```

### 3. Review Standards Alignment

```yaml
# Team Review Checklist
Functionality:
  - [ ] Code does what it's supposed to do
  - [ ] Edge cases handled appropriately  
  - [ ] Error handling is comprehensive

Code Quality:
  - [ ] Follows team coding standards
  - [ ] No code duplication
  - [ ] Functions are single-purpose
  - [ ] Variable names are descriptive

Testing:
  - [ ] Unit tests for new functionality
  - [ ] Tests cover edge cases
  - [ ] Integration tests for API changes

Documentation:
  - [ ] README updated if needed
  - [ ] API docs updated
  - [ ] Complex logic commented

Security:
  - [ ] No hardcoded secrets
  - [ ] Input validation present
  - [ ] Authentication checks in place
```

## Gestione Conflitti Interpersonali

### 1. Early Warning Signs

```yaml
Communication Red Flags:
  - Sarcastic or dismissive comments
  - Personal attacks in code reviews
  - Ignoring or avoiding team members
  - Escalating arguments in public channels
  - Passive-aggressive behavior

Technical Red Flags:
  - Rejecting all suggestions without explanation
  - Making changes without team consultation
  - Reverting others' work without discussion
  - Blocking PRs for non-technical reasons
  - Creating competing implementations
```

### 2. De-escalation Techniques

```markdown
# LISTEN Framework

## L - Listen Actively
- Give full attention to the other person
- Don't interrupt or prepare counterarguments
- Ask clarifying questions
- Summarize what you heard

## I - Identify Core Issues
- Separate technical from personal concerns
- Find the root cause, not just symptoms
- Distinguish between preferences and requirements
- Focus on project impact

## S - Seek Common Ground  
- Identify shared goals and values
- Acknowledge valid points from all sides
- Build on areas of agreement
- Focus on team/project success

## T - Take Responsibility
- Own your part in the conflict
- Admit mistakes or oversights
- Apologize for miscommunication
- Commit to behavior changes

## E - Explore Solutions Together
- Brainstorm multiple options
- Consider creative compromises
- Agree on trial periods
- Define success criteria

## N - Next Steps and Follow-up
- Document agreed solutions
- Set review checkpoints
- Establish ongoing communication
- Monitor relationship health
```

### 3. Mediation Process

```yaml
# When to Involve Mediator
- Direct conversation hasn't worked
- Conflict affects team productivity
- Personal attacks have occurred
- Multiple attempts at resolution failed

# Mediation Steps
1. Pre-mediation:
   - Separate conversations with each party
   - Identify core issues and positions
   - Set ground rules for discussion

2. Joint Session:
   - Neutral facilitator guides discussion
   - Each party states their perspective
   - Focus on interests, not positions
   - Generate potential solutions

3. Agreement:
   - Document agreed solutions
   - Set implementation timeline
   - Establish success metrics
   - Plan follow-up sessions

4. Follow-up:
   - Check progress regularly
   - Address new issues quickly
   - Celebrate improvements
   - Adjust agreements as needed
```

## Conflict Prevention Culture

### 1. Psychological Safety

```yaml
Creating Safe Environment:
  - Encourage questions and learning
  - Treat mistakes as learning opportunities
  - Value diverse perspectives and approaches
  - Separate people from their ideas
  - Model vulnerability and growth mindset

Team Agreements:
  - Assume positive intent
  - Challenge ideas, not people
  - Give specific, actionable feedback
  - Ask for help when stuck
  - Celebrate team successes
```

### 2. Regular Check-ins

```markdown
# Weekly Team Health Check

## What's Working Well?
- Code review process improvements
- Good collaboration on Feature X
- Clear communication in standup

## What Could Be Better?
- Too many meetings interrupting flow
- Need clearer acceptance criteria
- Deploy process still manual

## Team Dynamics
- Any tensions or concerns?
- Communication feedback needed?
- Support required for anyone?

## Action Items
- Reduce meeting frequency
- Template for acceptance criteria
- Investigate automated deployments
```

### 3. Proactive Measures

```yaml
# Conflict Prevention Strategies
Team Building:
  - Regular informal interactions
  - Pair programming sessions
  - Shared learning activities
  - Cross-functional project work

Clear Processes:
  - Documented decision-making process
  - Escalation procedures
  - Role and responsibility clarity
  - Communication protocols

Continuous Improvement:
  - Regular retrospectives
  - Feedback culture development
  - Process experimentation
  - Learning from other teams
```

## Tools e Resources

### 1. Technical Conflict Tools

```bash
# Git tools
git rerere  # Reuse recorded resolution
git mergetool  # Visual merge resolution
git diff --name-only --diff-filter=U  # List conflicts

# GitHub features
- Protected branches
- Required reviews
- Status checks
- Merge queue

# IDE integrations
- VSCode Git integration
- IntelliJ merge tools
- Vim fugitive plugin
```

### 2. Communication Tools

```yaml
# For technical discussions
- GitHub Discussions
- Team wiki/documentation
- Architecture Decision Records (ADRs)
- Technical RFCs

# For process improvement  
- Retrospective tools (Retrium, FunRetro)
- Survey tools (Google Forms, Typeform)
- Meeting facilitation (Miro, Mural)

# For conflict resolution
- Private channels (Slack DMs)
- Video calls for complex issues
- HR/management escalation paths
```

## Measuring Success

### 1. Technical Metrics

```yaml
Merge Conflict Metrics:
  - Frequency of conflicts
  - Time to resolve conflicts
  - Number of failed merges
  - Branch lifetime duration

Code Quality Metrics:
  - Review approval time
  - Number of review iterations
  - Code coverage trends
  - Bug rate post-merge
```

### 2. Team Health Metrics

```yaml
Communication Metrics:
  - Team satisfaction scores
  - Response time to reviews
  - Participation in discussions
  - Quality of feedback given

Collaboration Metrics:
  - Cross-team contributions
  - Knowledge sharing frequency
  - Pair programming sessions
  - Mentoring relationships
```

## Quiz di Verifica

### Domande

1. **Quali sono i tre tipi principali di conflitti in team development?**

2. **Come si risolve manualmente un merge conflict con conflict markers?**

3. **Qual è il LISTEN framework per de-escalation?**

4. **Come si prevengono merge conflicts attraverso branch management?**

5. **Quando è appropriato coinvolgere un mediator per conflitti interpersonali?**

### Risposte

1. **Tipi di Conflitti**: Tecnici (merge conflicts), di processo (decisions/standards), interpersonali (communication/relationships)

2. **Merge Conflict Resolution**: Identify conflict markers (<<<<<<< ======= >>>>>>>), analyze versions, choose or combine solutions, remove markers, test, commit

3. **LISTEN Framework**: Listen actively, Identify core issues, Seek common ground, Take responsibility, Explore solutions, Next steps

4. **Conflict Prevention**: Small focused branches, regular sync with main, short-lived branches, clear naming, proactive communication

5. **Mediation Timing**: When direct conversation fails, affects team productivity, personal attacks occur, multiple resolution attempts failed

## Esercizi Pratici

### Esercizio 1: Merge Conflict Simulation

```bash
# Obiettivo: Praticare risoluzione merge conflicts

# Setup scenario
git init conflict-practice
cd conflict-practice
echo "function greet(name) { return 'Hello ' + name; }" > utils.js
git add utils.js
git commit -m "initial: add greeting function"

# Create two conflicting branches
git checkout -b feature-validation
# Modify utils.js: add validation
git add utils.js
git commit -m "feat: add input validation"

git checkout main
git checkout -b feature-internationalization  
# Modify same function: add i18n
git add utils.js
git commit -m "feat: add internationalization"

# Merge and resolve conflict
git checkout main
git merge feature-validation
git merge feature-internationalization
# Resolve conflict combining both features
```

### Esercizio 2: Conflict Resolution Scenario

```bash
# Obiettivo: Practice interpersonal conflict resolution

# Scenario: 
# Developer A wants to use TypeScript for new features
# Developer B prefers to stick with JavaScript
# Team lead needs to make a decision

# Role-play exercise:
# 1. Each person presents their case
# 2. Identify underlying concerns and goals
# 3. Explore compromise solutions
# 4. Document decision with reasoning
# 5. Agree on evaluation criteria
```

## Risorse Aggiuntive

### Documentazione Tecnica
- [Git Merge Conflict Resolution](https://git-scm.com/docs/git-merge)
- [GitHub Conflict Resolution](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts)
- [Merge vs Rebase Strategies](https://www.atlassian.com/git/tutorials/merging-vs-rebasing)

### Soft Skills Resources
- "Crucial Conversations" by Kerry Patterson
- "Nonviolent Communication" by Marshall Rosenberg
- "The Five Dysfunctions of a Team" by Patrick Lencioni

### Tools e Training
- Conflict resolution workshops
- Team communication training
- Mediation certification programs

---

[⬅️ Comunicazione Efficace](./04-comunicazione-efficace.md) | [➡️ Indice](../README.md)
