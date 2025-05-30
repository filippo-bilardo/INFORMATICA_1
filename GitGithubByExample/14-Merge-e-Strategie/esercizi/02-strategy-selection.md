# Esercizio: Selezione delle Strategie di Merge

## Obiettivo
Imparare a scegliere la strategia di merge più appropriata in base al contesto del progetto e agli obiettivi del team.

## Prerequisiti
- Conoscenza dei tipi di merge (fast-forward, recursive, squash)
- Comprensione dei branch e workflow Git
- Familiarità con i comandi di merge base

## Scenario Base
Sei il Git Master di un team di sviluppo e devi decidere quale strategia di merge utilizzare per diverse situazioni.

## Parte 1: Analisi delle Situazioni

### Situazione 1: Feature Branch Semplice
```
main: A---B---C
           \
feature:    D---E
```

**Contesto:**
- Feature sviluppata da un singolo developer
- Nessun commit su main durante lo sviluppo
- 2 commit puliti e ben documentati

**Domande:**
1. Quale strategia consiglieresti?
2. Perché questa scelta?
3. Quale comando useresti?

### Situazione 2: Feature Branch con Storia Lunga
```
main: A---B---C---F---G
           \
feature:    D---E---H---I---J---K---L
```

**Contesto:**
- Feature complessa sviluppata in 2 settimane
- 7 commit inclusi WIP, fix typo, debug temporaneo
- Team preferisce cronologia pulita

**Domande:**
1. Quale strategia consiglieresti?
2. Come prepareresti il branch prima del merge?
3. Quali commit elimineresti?

### Situazione 3: Hotfix Critico
```
main: A---B---C (PRODUZIONE)
           \
hotfix:     D (fix critico)
```

**Contesto:**
- Bug critico in produzione
- Fix di una sola riga
- Deploy immediato necessario

**Domande:**
1. Quale strategia useresti?
2. Considereresti un tag?
3. Come gestiresti develop branch?

## Parte 2: Implementazione Pratica

### Setup Repository
```bash
# Crea repository di test
mkdir merge-strategy-practice
cd merge-strategy-practice
git init

# Setup iniziale
echo "# Progetto Test" > README.md
git add README.md
git commit -m "initial: project setup"

echo "console.log('app started');" > app.js
git add app.js
git commit -m "feat: basic app structure"

echo "function utils() {}" > utils.js
git add utils.js
git commit -m "feat: add utilities"
```

### Esercizio 1: Fast-Forward Merge

```bash
# Crea feature branch
git checkout -b feature/user-login

# Implementa feature
echo "function login() { return true; }" >> app.js
git add app.js
git commit -m "feat: implement user login"

echo "function validateUser() {}" >> utils.js
git add utils.js
git commit -m "feat: add user validation"

# Torna a main
git checkout main

# TASK: Esegui merge appropriato
# Scrivi qui il comando:
# git merge _______________
```

**Domande di Verifica:**
1. La cronologia è lineare?
2. Quanti commit vedi in `git log --oneline`?
3. È possibile identificare quando è iniziata la feature?

### Esercizio 2: No-Fast-Forward Merge

```bash
# Continua dal precedente
git checkout -b feature/user-dashboard

# Simula sviluppo parallelo su main
git checkout main
echo "const VERSION = '1.1.0';" >> app.js
git add app.js
git commit -m "bump: version to 1.1.0"

# Torna alla feature
git checkout feature/user-dashboard
echo "function dashboard() {}" >> app.js
git add app.js
git commit -m "feat: create dashboard"

echo "// Dashboard styles" > dashboard.css
git add dashboard.css
git commit -m "style: dashboard CSS"

# Torna a main
git checkout main

# TASK: Esegui merge mantenendo merge commit
# Scrivi qui il comando:
# git merge _______________
```

### Esercizio 3: Squash Merge

```bash
# Crea feature con storia "sporca"
git checkout -b feature/messy-development

# Simula sviluppo disordinato
echo "function feature() {}" >> app.js
git add app.js
git commit -m "wip: starting feature"

echo "function feature() { console.log('test'); }" > temp.js
git add temp.js
git commit -m "debug: temporary logging"

echo "function feature() { return 'done'; }" >> app.js
git add app.js
git commit -m "fix: correct implementation"

rm temp.js
git add .
git commit -m "cleanup: remove debug files"

echo "// TODO: add tests" >> app.js
git add app.js
git commit -m "todo: need tests"

# Torna a main
git checkout main

# TASK: Squash merge per pulire la storia
# Scrivi qui il comando:
# git merge _______________
```

## Parte 3: Decision Tree

Crea un diagramma di decisione per il tuo team:

```
Merge Strategy Decision Tree

Feature pronta per merge?
├─ NO → Continue development
└─ YES
   ├─ È un hotfix critico?
   │  └─ YES → Fast-forward merge
   └─ NO
      ├─ Storia del branch pulita?
      │  ├─ YES
      │  │  ├─ Team preferisce cronologia lineare?
      │  │  │  ├─ YES → Fast-forward merge
      │  │  │  └─ NO → No-fast-forward merge
      │  │  └─ 
      │  └─ NO → Squash merge
      └─
```

## Parte 4: Scenari Avanzati

### Scenario A: Release Branch
```bash
# Setup release branch
git checkout -b release/v2.0.0
echo "const VERSION = '2.0.0';" >> version.js
git add version.js
git commit -m "bump: version to 2.0.0"

# Minor fixes durante release
echo "// Fix minor bug" >> app.js
git add app.js
git commit -m "fix: minor bug in release"
```

**Task:** Come mergeresti questo branch in main?

### Scenario B: Long-Running Feature
```bash
# Feature che vive per mesi
git checkout -b feature/major-refactor

# Simula molti commit nel tempo
for i in {1..10}; do
    echo "// Refactor step $i" >> refactor-$i.js
    git add refactor-$i.js
    git commit -m "refactor: step $i of major refactor"
done
```

**Task:** Come integreresti questa feature?

## Parte 5: Policy del Team

Scrivi una policy di merge per il tuo team:

```markdown
# Team Merge Policy

## Feature Branches
- [ ] Durata < 1 settimana: Fast-forward preferred
- [ ] Durata > 1 settimana: No-fast-forward
- [ ] Storia sporca (>5 WIP commits): Squash merge

## Hotfix Branches
- [ ] Sempre fast-forward
- [ ] Tag immediato dopo merge
- [ ] Backport in develop obbligatorio

## Release Branches
- [ ] No-fast-forward merge
- [ ] Tag della release
- [ ] Merge back in develop

## Quality Gates
- [ ] Tests passati
- [ ] Code review approvato
- [ ] Documentazione aggiornata
```

## Domande di Riflessione

1. **Cronologia vs Velocità**: Quando sacrificheresti una cronologia pulita per velocità di merge?

2. **Team Size**: Come cambia la strategia con un team di 2 vs 10 developers?

3. **Release Frequency**: Team con release giornaliere vs mensili dovrebbero usare strategie diverse?

4. **Debugging**: Quale strategia rende più facile trovare bug storici?

5. **Compliance**: In ambienti regolamentati, quale strategia preferiresti?

## Best Practices da Ricordare

### Fast-Forward
- ✅ Cronologia lineare
- ✅ Storia semplice
- ❌ Perde contesto di feature

### No-Fast-Forward
- ✅ Mantiene contesto
- ✅ Facile rollback
- ❌ Cronologia più complessa

### Squash
- ✅ Storia pulita
- ✅ Un commit per feature
- ❌ Perde storia dettagliata

## Consegna

Crea un documento che includa:

1. **Analisi delle Situazioni**: Risposte ragionate per ogni scenario
2. **Comandi Utilizzati**: Screenshot dei comandi eseguiti
3. **Decision Tree**: Tuo diagramma personalizzato
4. **Team Policy**: Policy scritta per il tuo team
5. **Riflessioni**: Risposte alle domande di riflessione

## Risorse Aggiuntive

- [Git Merge Documentation](https://git-scm.com/docs/git-merge)
- [Atlassian Merge Strategies](https://www.atlassian.com/git/tutorials/using-branches/merge-strategy)
- [Pro Git Book - Basic Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging)

## Prossimi Passi

1. Applica queste strategie in [Complex Integration](./03-complex-integration.md)
2. Studia [Risoluzione Conflitti](../../15-Risoluzione-Conflitti/README.md)
3. Pratica con [Git Flow](../../23-Git-Flow-e-Strategie/README.md)
