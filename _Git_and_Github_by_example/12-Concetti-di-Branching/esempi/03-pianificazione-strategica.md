# 03 - Pianificazione Strategica del Branching

## 🎯 Obiettivo
Sviluppare competenze per pianificare e implementare strategie di branching efficaci basate sulle caratteristiche specifiche del progetto e del team.

## 📋 Framework di Decisione

### Fase 1: Analisi del Contesto Progetto

#### Matrice di Valutazione del Progetto
```bash
# Creiamo un repository per testare diverse strategie
mkdir branching-strategy-lab
cd branching-strategy-lab
git init

# Documentazione della strategia scelta
cat > BRANCHING_STRATEGY.md << 'EOF'
# Branching Strategy Decision Matrix

## Project Context Analysis

### Team Size: [1-3 | 4-10 | 10+]
### Release Frequency: [Continuous | Weekly | Monthly | Quarterly]
### Environment Complexity: [Single | Staging+Prod | Multi-env]
### Compliance Requirements: [None | Medium | High]
### Team Experience: [Junior | Mixed | Senior]

## Strategy Selection Criteria

| Criteria | Weight | Git Flow | GitHub Flow | Feature Branch | Trunk-based |
|----------|--------|----------|-------------|----------------|-------------|
| Team Size | High | Large | Small-Med | Medium | Any |
| Release Freq | High | Scheduled | Continuous | Flexible | Continuous |
| Complexity | Medium | High | Low | Medium | Low |
| Compliance | High | High | Low | Medium | Medium |

## Decision: [Strategy Name]
## Rationale: [Explanation]
EOF

git add BRANCHING_STRATEGY.md
git commit -m "Add branching strategy documentation template"
```

### Fase 2: Strategie per Diversi Contesti

#### Strategia 1: Startup MVP (GitHub Flow)
```bash
# Scenario: Team 3 persone, deploy continuo, MVP veloce
git checkout -b demo/startup-strategy

cat > startup-workflow.md << 'EOF'
# Startup MVP Strategy: GitHub Flow

## Characteristics
- Single main branch
- Feature branches short-lived (1-3 days)
- Direct deployment from main
- Minimal overhead

## Workflow Example
main ──●──●──●──●──●──► (always deployable)
       │  │  │  │  │
    feat1─┘  │  │  │
          feat2─┘  │
              feat3─┘
EOF

# Implementazione pratica
echo "// MVP Core Feature" > core.js
git add .
git commit -m "MVP: Core functionality"

# Feature veloce
git checkout -b feature/user-login
echo "function login() { /* quick implementation */ }" >> core.js
git add core.js
git commit -m "Add quick login feature"

# Merge immediato dopo review
git checkout main
git merge feature/user-login --no-ff
git branch -d feature/user-login

# Deploy automatico (simulated)
echo "Deployed to production: $(git rev-parse --short HEAD)" >> deployment.log
git add deployment.log
git commit -m "Deploy: User login feature"
```

#### Strategia 2: Enterprise Product (Git Flow)
```bash
git checkout main
git checkout -b demo/enterprise-strategy

cat > enterprise-workflow.md << 'EOF'
# Enterprise Strategy: Git Flow

## Branch Structure
- main: Production releases only
- develop: Integration branch
- feature/*: Feature development
- release/*: Release preparation
- hotfix/*: Production fixes

## Timeline Example
Week 1-2: Feature development
Week 3: Release branch + testing
Week 4: Release + hotfix if needed

## Compliance Integration
- All merges require review
- Automated testing on all branches
- Audit trail for all changes
EOF

# Setup enterprise structure
git checkout -b develop
echo "const VERSION = '1.0.0-dev';" > version.js
git add .
git commit -m "Setup development branch"

# Multiple parallel features
git checkout -b feature/advanced-analytics
echo "function analytics() { /* complex implementation */ }" > analytics.js
git add analytics.js
git commit -m "Implement advanced analytics"

git checkout develop
git checkout -b feature/user-management
echo "function userManagement() { /* enterprise features */ }" > users.js
git add users.js
git commit -m "Implement user management system"

# Feature integration
git checkout develop
git merge feature/advanced-analytics --no-ff
git merge feature/user-management --no-ff

# Release preparation
git checkout -b release/v1.1.0
echo "const VERSION = '1.1.0-rc1';" > version.js
git add version.js
git commit -m "Prepare v1.1.0 release candidate"
```

#### Strategia 3: Open Source Project (Fork & Pull)
```bash
git checkout main
git checkout -b demo/opensource-strategy

cat > opensource-workflow.md << 'EOF'
# Open Source Strategy: Fork & Pull Request

## Community Management
- Contributor onboarding process
- Clear contribution guidelines
- Maintainer review process
- Community governance

## Quality Gates
- Automated testing (CI/CD)
- Code review by maintainers
- Documentation requirements
- License compliance
EOF

# Simulazione contribuzione esterna
git checkout -b contributor/external-feature
echo "function communityContribution() { /* external dev work */ }" > community.js
echo "## Community Contribution" >> README.md
echo "Added community-requested feature for better accessibility" >> README.md
git add .
git commit -m "Community: Add accessibility features"

# Simulazione review process
git checkout main
git checkout -b review/external-feature
git merge contributor/external-feature --no-ff --no-commit
# Review phase (simulated)
echo "// Reviewed and approved by maintainer" >> community.js
git add .
git commit -m "Review: Approve accessibility features with minor fixes"
```

### Fase 3: Hybrid Strategies per Scenari Complessi

#### Strategia Ibrida: Microservizi Team
```bash
git checkout main
git checkout -b demo/microservices-strategy

cat > microservices-workflow.md << 'EOF'
# Microservices Strategy: Hybrid Approach

## Per Service Repository
- GitHub Flow per servizi semplici
- Feature Branch per servizi complessi
- Shared libraries use Git Flow

## Cross-service Coordination
- Dependency management branch
- Integration testing branch
- Coordinated release tags

## Service Independence
- Each service can deploy independently
- Backward compatibility requirements
- API versioning strategy
EOF

# Simulazione multi-service setup
mkdir -p services/{auth,payment,notification}
echo "// Auth Service v1.0" > services/auth/main.js
echo "// Payment Service v1.0" > services/payment/main.js  
echo "// Notification Service v1.0" > services/notification/main.js
git add services/
git commit -m "Setup microservices architecture"

# Cross-service feature
git checkout -b feature/cross-service-logging
echo "// Centralized logging" > services/shared/logging.js
git add services/shared/
git commit -m "Add centralized logging across services"
```

## 🔧 Tool per Pianificazione

### Template di Valutazione
```bash
# Creiamo template per decision-making
cat > .github/BRANCHING_DECISION.md << 'EOF'
# Branching Strategy Decision Template

## Project Assessment

### Team Factors
- [ ] Team size: ___
- [ ] Git experience level: ___
- [ ] Geographic distribution: ___
- [ ] Working hours overlap: ___

### Technical Factors  
- [ ] Deployment frequency: ___
- [ ] Testing automation level: ___
- [ ] Code review requirements: ___
- [ ] Integration complexity: ___

### Business Factors
- [ ] Release predictability needs: ___
- [ ] Quality requirements: ___
- [ ] Compliance requirements: ___
- [ ] Risk tolerance: ___

## Strategy Options Evaluation

### Option 1: [Strategy Name]
**Pros:**
- 
- 

**Cons:**
- 
- 

**Fit Score:** ___/10

### Option 2: [Strategy Name]
**Pros:**
- 
- 

**Cons:**
- 
- 

**Fit Score:** ___/10

## Final Decision
**Selected Strategy:** ___
**Rationale:** ___
**Implementation Timeline:** ___
**Success Metrics:** ___
EOF

git add .github/
git commit -m "Add branching strategy decision template"
```

### Metriche di Monitoraggio
```bash
# Script per monitorare effectiveness della strategia
cat > monitor-strategy.sh << 'EOF'
#!/bin/bash

echo "=== Branching Strategy Metrics ==="
echo

echo "Branch Count:"
git branch -a | wc -l

echo "Average Branch Lifetime:"
# Calcola età media dei branch
git for-each-ref --format='%(refname:short) %(committerdate)' refs/heads/ | \
  while read branch date; do
    echo "Branch: $branch, Age: $(( $(date +%s) - $(date -d "$date" +%s) )) seconds"
  done

echo "Merge Frequency:"
git log --oneline --merges --since="1 month ago" | wc -l

echo "Hotfix Frequency:"
git log --oneline --grep="hotfix" --since="1 month ago" | wc -l

echo "Feature Delivery Time:"
# Tempo medio da feature branch a main
git log --oneline --grep="feature" --since="1 month ago" --format="%s %cr"
EOF

chmod +x monitor-strategy.sh
git add monitor-strategy.sh
git commit -m "Add strategy monitoring script"
```

## 🏃‍♂️ Esercizio Pratico: Strategy Design Workshop

### Scenario di Pianificazione

#### Contesto del Cliente
**Azienda:** FinTech startup  
**Team:** 8 sviluppatori (4 senior, 4 junior)  
**Prodotto:** App mobile banking  
**Compliance:** Elevata (settore finanziario)  
**Deploy:** Settimanale con possibilità hotfix  

#### Task di Progettazione
1. **Analisi dei Requisiti**
   ```bash
   # Documenta analisi
   cat > fintech-analysis.md << 'EOF'
   # FinTech Branching Strategy Analysis
   
   ## Critical Factors
   - High compliance requirements
   - Mixed team experience
   - Weekly release cycle
   - Financial sector regulations
   - Mobile app store approval process
   
   ## Risk Assessment
   - Production bugs = financial risk
   - Regulatory audit requirements
   - App store rejection impact
   - Customer trust implications
   EOF
   ```

2. **Strategy Design**
   - Scegli strategia appropriata
   - Definisci branch naming conventions
   - Pianifica review process
   - Crea compliance checkpoints

3. **Implementation Plan**
   - Timeline di rollout
   - Training necessario
   - Tool requirements
   - Success metrics

### Deliverable Attesi
1. Documento strategia completo
2. Workflow diagram
3. Implementation timeline
4. Monitoring setup

## 🎯 Risultati Attesi

Dopo questo esempio dovresti:
- ✅ Saper valutare fattori critici per strategia branching
- ✅ Progettare strategie ibride per casi complessi
- ✅ Creare template riutilizzabili per decision-making
- ✅ Implementare metriche per monitoraggio efficacia
- ✅ Adattare strategie a contesti specifici

## 💡 Framework di Valutazione Rapida

### Quick Decision Tree
```
1. Team size?
   1-3: GitHub Flow
   4-10: Feature Branch Workflow
   10+: Git Flow

2. Deployment frequency?
   Daily: Trunk-based
   Weekly: Feature Branch
   Monthly: Git Flow

3. Compliance requirements?
   High: Git Flow + strict review
   Medium: Feature Branch + review
   Low: GitHub Flow

4. Team experience?
   Junior: Simple workflow (GitHub Flow)
   Mixed: Feature Branch
   Senior: Any workflow appropriate
```

## 🔗 Prossimi Passi

- [04 - Team Workflow](./04-team-workflow.md)
- [Esercizio: Strategy Implementation](../esercizi/01-strategy-selection.md)

---

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 02-Scenari Branching](./02-scenari-branching.md)
- [➡️ 04-Team Workflow](./04-team-workflow.md)
