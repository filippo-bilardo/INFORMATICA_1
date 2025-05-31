# 02 - Pull Request Lifecycle

## 📖 Spiegazione Concettuale

Il **Pull Request Lifecycle** descrive il percorso completo di una proposta di modifica: dalla creazione iniziale fino al merge o alla chiusura. Comprendere questo processo è essenziale per collaborare efficacemente.

### Cos'è un Pull Request?

Un **Pull Request (PR)** è una richiesta formale di incorporare le tue modifiche nel repository principale. È molto più di un semplice merge: è uno strumento di:

- **Comunicazione**: Discussione delle modifiche
- **Review**: Valutazione qualità del codice
- **Testing**: Verifica automatica e manuale
- **Documentazione**: Storia delle decisioni

## 🔄 Le Fasi del Pull Request Lifecycle

### Fase 1: **Creation** (Creazione)

#### 1.1 Preparazione Pre-PR

```bash
# Assicurati che il branch sia aggiornato
git checkout main
git pull upstream main
git checkout feature/awesome-feature
git rebase main  # O merge se preferisci

# Verifica che tutto funzioni
npm test        # O il tuo comando di test
npm run lint    # Verifica code style
```

#### 1.2 Push del Branch

```bash
# Push del branch al tuo fork
git push origin feature/awesome-feature

# Se hai fatto rebase, potrebbe servire force push
git push --force-with-lease origin feature/awesome-feature
```

#### 1.3 Creazione PR su GitHub

**Informazioni essenziali:**

```markdown
# Title: Conciso ma descrittivo
Add user authentication with OAuth2

# Description template:
## What does this PR do?
Adds OAuth2 authentication using Google and GitHub providers.

## Type of change
- [x] New feature
- [ ] Bug fix
- [ ] Breaking change
- [ ] Documentation update

## How to test
1. Set up OAuth credentials in .env
2. Run `npm start`
3. Click "Login with Google"
4. Verify user session is created

## Screenshots
[Include if UI changes]

## Checklist
- [x] My code follows the project's style guidelines
- [x] I have performed a self-review
- [x] My changes generate no new warnings
- [x] I have added tests that prove my fix is effective
- [x] New and existing unit tests pass
- [x] I have commented my code in hard-to-understand areas

## Related Issues
Closes #123
References #456
```

### Fase 2: **Review** (Revisione)

#### 2.1 Automated Checks

```yaml
# Esempio GitHub Actions che vengono triggered
name: PR Checks
on: [pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Run tests
        run: npm test
      - name: Code coverage
        run: npm run coverage
      - name: Lint check
        run: npm run lint
      - name: Security scan
        run: npm audit
```

#### 2.2 Human Review Process

**Per Reviewers:**

```bash
# Checkout del PR per test locali
gh pr checkout 123  # GitHub CLI

# O manualmente:
git fetch origin pull/123/head:pr-123
git checkout pr-123

# Test delle modifiche
npm install
npm test
npm start  # Test funzionalità
```

**Tipi di Feedback:**

1. **Approve** ✅: Codice pronto per merge
2. **Request Changes** ❌: Modifiche necessarie
3. **Comment** 💬: Suggerimenti senza blocking

#### 2.3 Review Comments Best Practices

**Per Reviewers:**

```markdown
# Feedback costruttivo
❌ "This is wrong"
✅ "Consider using Array.map() instead of forEach for better functional style"

# Suggerimenti specifici
❌ "Fix the bug"
✅ "Line 42: null check missing. Try: if (user && user.email) {"

# Apprezzamento
✅ "Great solution for handling edge cases!"
✅ "Nice clean implementation"
```

### Fase 3: **Iteration** (Iterazione)

#### 3.1 Addressing Feedback

```bash
# Dopo ricevere feedback, fai modifiche
git checkout feature/awesome-feature

# Implementa i cambiamenti richiesti
# Edita file secondo feedback

# Commit delle modifiche
git add .
git commit -m "Refactor: use Array.map() instead of forEach"

# Push aggiornamenti
git push origin feature/awesome-feature
```

#### 3.2 Managing Multiple Rounds

```bash
# Esempio di storia iterativa
git log --oneline
a1b2c3d Fix: add null checks for user validation
d4e5f6g Refactor: use Array.map() instead of forEach  
g7h8i9j Style: fix linting issues
j0k1l2m Add: user authentication with OAuth2
```

#### 3.3 Responding to Reviews

```markdown
# Su GitHub, rispondi ai commenti specifici
@reviewer-name Thanks for the feedback! I've implemented the suggested 
null checks and updated the tests accordingly. 

The Array.map() approach is much cleaner - great suggestion!

Ready for another review when you have time.
```

### Fase 4: **Testing** (Test)

#### 4.1 Continuous Integration

```yaml
# CI Pipeline per PR
on:
  pull_request:
    branches: [main]

jobs:
  test-multiple-envs:
    strategy:
      matrix:
        node-version: [14, 16, 18]
        os: [ubuntu-latest, windows-latest, macos-latest]
    runs-on: ${{ matrix.os }}
    steps:
      - uses: actions/checkout@v2
      - uses: actions/setup-node@v2
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm ci
      - run: npm test
```

#### 4.2 Manual Testing Checklist

```markdown
## Testing Checklist for Reviewers

### Functional Testing
- [ ] New feature works as described
- [ ] No regression in existing features
- [ ] Error handling works correctly
- [ ] Edge cases covered

### Performance Testing
- [ ] No significant performance degradation
- [ ] Memory usage acceptable
- [ ] Database queries optimized

### Security Testing
- [ ] No sensitive data exposed
- [ ] Input validation proper
- [ ] Authentication/authorization correct

### UX Testing
- [ ] User interface intuitive
- [ ] Responsive design working
- [ ] Accessibility requirements met
```

### Fase 5: **Approval** (Approvazione)

#### 5.1 Approval Requirements

```markdown
# Typical approval requirements:
✅ At least 2 approvals from code owners
✅ All automated checks passing
✅ No merge conflicts
✅ Branch up to date with main
✅ Documentation updated (if needed)
```

#### 5.2 Final Pre-Merge Checks

```bash
# Maintainer final check
git checkout main
git pull origin main
git checkout feature/awesome-feature
git rebase main  # Ensure up to date

# Verify everything still works
npm test
npm run build
```

### Fase 6: **Merge** (Incorporazione)

#### 6.1 Merge Strategies

**1. Merge Commit** (preserva storia)
```bash
git checkout main
git merge --no-ff feature/awesome-feature
# Crea: Merge pull request #123 from user/feature
```

**2. Squash and Merge** (storia pulita)
```bash
git checkout main
git merge --squash feature/awesome-feature
git commit -m "Add user authentication with OAuth2 (#123)"
```

**3. Rebase and Merge** (storia lineare)
```bash
git checkout feature/awesome-feature
git rebase main
git checkout main
git merge --ff-only feature/awesome-feature
```

#### 6.2 Post-Merge Cleanup

```bash
# Dopo merge, cleanup
git branch -d feature/awesome-feature           # Local branch
git push origin --delete feature/awesome-feature # Remote branch

# Update main
git checkout main
git pull origin main
```

### Fase 7: **Post-Merge** (Dopo il Merge)

#### 7.1 Deployment Tracking

```bash
# Tag per release se necessario
git tag -a v1.2.0 -m "Release v1.2.0: Add OAuth2 authentication"
git push origin v1.2.0
```

#### 7.2 Follow-up Actions

```markdown
## Post-merge checklist:
- [ ] Feature deployed to staging
- [ ] Smoke tests passed
- [ ] Documentation updated
- [ ] Stakeholders notified
- [ ] Monitoring for issues
- [ ] User feedback collection
```

## 📊 PR Lifecycle Metrics

### Timing Benchmarks

| Phase | Good | Acceptable | Needs Improvement |
|-------|------|------------|-------------------|
| Creation to First Review | < 24h | < 72h | > 72h |
| Review to Approval | < 48h | < 1 week | > 1 week |
| Approval to Merge | < 4h | < 24h | > 24h |
| Total PR Lifecycle | < 1 week | < 2 weeks | > 2 weeks |

### Quality Indicators

```markdown
✅ High Quality PR:
- Clear description and testing instructions
- Small, focused changes
- Good test coverage
- Minimal back-and-forth in reviews
- Quick automated checks

❌ Low Quality PR:
- Vague description
- Large, unfocused changes
- Missing tests
- Multiple review cycles
- Failing automated checks
```

## 🚨 Common Lifecycle Issues

### Issue 1: PR Stalled in Review

**Symptoms:**
- No reviewer activity for days
- Author waiting indefinitely

**Solutions:**
```bash
# Gentle ping after reasonable time
@maintainer-name Friendly ping on this PR when you have a moment!

# Provide more context if needed
Added more details to the description and testing instructions.

# Split large PR if too complex
This PR was getting large, so I split it into smaller focused PRs:
- #124: Database schema changes
- #125: API endpoints  
- #126: Frontend integration
```

### Issue 2: Merge Conflicts

**Prevention:**
```bash
# Keep branch updated regularly
git fetch upstream
git rebase upstream/main

# Before creating PR
git checkout main
git pull upstream main
git checkout feature-branch
git rebase main
```

**Resolution:**
```bash
# When conflicts arise
git fetch upstream
git rebase upstream/main

# Resolve conflicts in editor
# git add resolved-files
git rebase --continue

# Force push (safely)
git push --force-with-lease origin feature-branch
```

### Issue 3: Failing CI/CD

**Common causes and fixes:**
```bash
# Linting issues
npm run lint -- --fix
git add .
git commit -m "Fix: resolve linting issues"

# Test failures  
npm test                    # Run locally first
npm test -- --verbose      # See detailed output
npm test -- --coverage     # Check coverage requirements

# Build failures
npm run build              # Test build locally
npm ci                     # Clean install dependencies
```

## 🎯 Advanced PR Patterns

### Pattern 1: Draft PRs

```bash
# Create draft for early feedback
gh pr create --draft --title "WIP: User authentication system"

# Convert to ready when complete
gh pr ready 123
```

### Pattern 2: Dependent PRs

```bash
# PR chain for complex features
feature/step1 -> main
feature/step2 -> feature/step1  
feature/step3 -> feature/step2

# Merge order: step1, then step2, then step3
```

### Pattern 3: Emergency Hotfixes

```bash
# Fast-track for critical fixes
git checkout main
git checkout -b hotfix/security-patch

# Minimal changes, fast review
git commit -m "Security: patch XSS vulnerability"

# Expedited review process
# Label: priority:critical
# Request immediate review
```

## 🧭 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Fork Workflow](01-fork-workflow.md)
- [➡️ Code Review](03-code-review.md)
