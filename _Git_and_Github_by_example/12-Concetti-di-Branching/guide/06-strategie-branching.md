# 02 - Strategie di Branching

## 📖 Spiegazione Concettuale

Le **strategie di branching** sono metodologie organizzative che definiscono come e quando creare, utilizzare e integrare i branch in un progetto. La scelta della strategia giusta dipende dalla dimensione del team, frequenza di release e complessità del progetto.

### Perché Servono Strategie?

Senza una strategia chiara:
- **Caos**: Branch ovunque senza logica
- **Conflitti**: Merge complessi e difficili
- **Rischi**: Codice instabile in produzione
- **Confusione**: Chi lavora su cosa?

Con una strategia ben definita:
- **Organizzazione**: Workflow chiaro e prevedibile
- **Qualità**: Controllo qualità sistematico
- **Efficienza**: Release rapide e sicure
- **Collaborazione**: Team coordinato

## 🌊 Git Flow (Strategia Complessa)

### Struttura Branch
```
main ──────●────●────●────●─── (produzione stabile)
            \         /
develop ────●─●─●─●─●─●─●─●─── (integrazione sviluppo)
             \     /   \
feature ──────●───●     ●───── (nuove funzionalità)
                  |
hotfix ───────────●─────────── (fix critici)
                  |
release ──────────●─────────── (preparazione release)
```

### Branch Permanenti
- **main/master**: Codice in produzione, sempre stabile
- **develop**: Branch di integrazione, dove confluisce lo sviluppo

### Branch Temporanei
- **feature/**: Sviluppo nuove funzionalità
- **release/**: Preparazione nuove versioni
- **hotfix/**: Correzioni urgenti produzione

### Workflow Tipico
```bash
# 1. Nuova feature
git checkout develop
git checkout -b feature/user-profile

# 2. Sviluppo e commit
git add .
git commit -m "Add user profile form"

# 3. Merge in develop
git checkout develop
git merge feature/user-profile
git branch -d feature/user-profile

# 4. Preparazione release
git checkout -b release/v1.2.0
# Bug fix minori, no nuove feature

# 5. Release in produzione
git checkout main
git merge release/v1.2.0
git tag v1.2.0

# 6. Merge back in develop
git checkout develop
git merge release/v1.2.0
```

### Vantaggi Git Flow
- **Stabilità**: Main sempre stabile
- **Organizzazione**: Ruoli chiari per ogni branch
- **Release strutturate**: Processo ben definito
- **Hotfix rapidi**: Canale dedicato per emergenze

### Svantaggi Git Flow
- **Complessità**: Molti branch da gestire
- **Overhead**: Process pesante per team piccoli
- **Merge conflicts**: Più probabili con branch longevi
- **Learning curve**: Richiede esperienza

## 🚀 GitHub Flow (Strategia Semplice)

### Struttura Branch
```
main ──●────●────●────●─── (produzione + sviluppo)
        \  /    /    /
feature  ●●    ●●   ●●─── (feature branch + PR)
```

### Principi Fondamentali
1. **main è sempre deployabile**
2. **Branch feature per ogni modifica**
3. **Pull Request per integrazione**
4. **Deploy frequenti**

### Workflow Tipico
```bash
# 1. Crea branch da main
git checkout main
git pull origin main
git checkout -b feature/add-search

# 2. Sviluppa e push
git add .
git commit -m "Add search functionality"
git push origin feature/add-search

# 3. Crea Pull Request su GitHub
# 4. Code review e discussione
# 5. Merge e deploy automatico
# 6. Cancella branch
```

### Vantaggi GitHub Flow
- **Semplicità**: Solo main + feature branch
- **Velocità**: Deploy rapidi e frequenti
- **Collaborazione**: Pull Request centralizzate
- **CI/CD friendly**: Si integra bene con automazione

### Svantaggi GitHub Flow
- **Rischio instabilità**: Errori vanno in produzione
- **Richiede disciplina**: Team deve essere molto attento
- **Testing**: Deve essere molto robusto
- **Rollback**: Più complesso senza branch stabili

## 🍴 GitLab Flow (Strategia Ibrida)

### Variante Environment-based
```
main ──●────●────●────●─── (sviluppo)
        \    \    \    \
pre-prod ●────●────●────●─ (staging)
          \    \    \    \
production ●────●────●────● (produzione)
```

### Variante Release-based
```
main ──●────●────●────●─── (sviluppo)
        \         \
2.3-stable ●──────●─────── (release stabile)
            \      \
2.2-stable   ●──────●───── (release precedente)
```

### Workflow Environment-based
```bash
# 1. Sviluppo su main
git checkout main
git checkout -b feature/new-api

# 2. Merge in main tramite MR
git checkout main
git merge feature/new-api

# 3. Deploy automatico su staging
# Cherry-pick o merge in pre-production

# 4. Dopo testing, promote a production
git checkout production
git merge pre-production
```

## 🔀 Forking Workflow

### Struttura
```
Original Repo ──●────●────●──
                 \    \    \
Fork Developer A  ●────●────●──
Fork Developer B  ●────●────●──
Fork Developer C  ●────●────●──
```

### Workflow Tipico
```bash
# 1. Fork del repository originale
# (tramite interfaccia GitHub)

# 2. Clone del fork
git clone https://github.com/tuoaccount/progetto.git
cd progetto

# 3. Configura upstream
git remote add upstream https://github.com/originale/progetto.git

# 4. Crea feature branch
git checkout -b feature/mia-feature

# 5. Sviluppa e push nel tuo fork
git push origin feature/mia-feature

# 6. Crea Pull Request verso repository originale

# 7. Mantieni fork aggiornato
git fetch upstream
git checkout main
git merge upstream/main
```

### Vantaggi Forking
- **Sicurezza**: Repository principale protetto
- **Contributi open source**: Chiunque può contribuire
- **Isolamento**: Ogni contributor lavora nel proprio fork
- **Review centralizzata**: PR verso repository principale

## 📊 Confronto Strategie

| Aspetto | Git Flow | GitHub Flow | GitLab Flow | Forking |
|---------|----------|-------------|-------------|---------|
| **Complessità** | Alta | Bassa | Media | Media |
| **Team Size** | Grande | Piccolo-Medio | Medio-Grande | Qualsiasi |
| **Release Frequency** | Pianificate | Continue | Flessibile | Variabile |
| **Stabilità** | Massima | Rischiosa | Bilanciata | Alta |
| **Learning Curve** | Ripida | Facile | Media | Media |
| **CI/CD** | Complesso | Ottimo | Buono | Buono |

## 💡 Casi d'Uso per Strategia

### Usa Git Flow quando:
- **Team grande** (10+ sviluppatori)
- **Release programmate** (mensili/trimestrali)
- **Prodotto enterprise** con alta stabilità richiesta
- **Multiple versioni** da mantenere contemporaneamente

```bash
# Esempio: Software bancario
git checkout develop
git checkout -b feature/new-transaction-type
# Sviluppo rigoroso, testing estensivo
git checkout develop
git merge feature/new-transaction-type
# Release programmata ogni trimestre
```

### Usa GitHub Flow quando:
- **Team piccolo** (2-8 sviluppatori)
- **Deploy continuo** (più volte al giorno)
- **Startup/SaaS** con rilasci rapidi
- **Cultura DevOps** consolidata

```bash
# Esempio: App web startup
git checkout main
git checkout -b feature/improve-signup
# Deploy automatico dopo merge
```

### Usa GitLab Flow quando:
- **Environment multipli** (dev/staging/prod)
- **Release controllate** ma frequenti
- **Team medio-grande** con process definiti
- **Compliance requirements**

```bash
# Esempio: E-commerce enterprise
git checkout main
git merge feature/new-payment-gateway
# Auto-deploy su staging
# Manual promote a production dopo testing
```

### Usa Forking quando:
- **Open source projects**
- **Team distribuito** senza accesso diretto
- **Contributi esterni** da community
- **Revisione rigorosa** del codice

```bash
# Esempio: Libreria open source
git fork original/project
git clone your-fork/project
git checkout -b feature/performance-improvement
# PR verso progetto originale
```

## 🎯 Best Practices Generali

### 1. **Scelta Strategia**
```bash
# Domande da porsi:
# - Quanto è grande il team?
# - Quanto spesso rilasciamo?
# - Quanto è critica la stabilità?
# - Quanto è esperto il team con Git?
```

### 2. **Documentazione**
```markdown
# README.md del progetto
## Branching Strategy

Questo progetto usa GitHub Flow:
1. main è sempre deployabile
2. Crea feature branch per ogni modifica
3. Usa Pull Request per review
4. Deploy automatico dopo merge
```

### 3. **Automazione**
```bash
# GitHub Actions esempio
name: CI/CD
on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Run tests
      run: npm test
    
  deploy:
    if: github.ref == 'refs/heads/main'
    runs-on: ubuntu-latest
    steps:
    - name: Deploy to production
      run: ./deploy.sh
```

### 4. **Branch Protection**
```bash
# Impostazioni GitHub per main:
# ✅ Require pull request reviews
# ✅ Require status checks to pass
# ✅ Require branches to be up to date
# ✅ Include administrators
# ❌ Allow force pushes
```

## 🧪 Quiz di Autovalutazione

**1. Quale strategia è meglio per un team di 3 sviluppatori con deploy giornalieri?**
- a) Git Flow
- b) GitHub Flow
- c) Forking Workflow
- d) Nessuna strategia

**2. In Git Flow, dove mergi le feature?**
- a) Direttamente in main
- b) In develop
- c) In release branch
- d) In hotfix branch

**3. Quale strategia è migliore per progetti open source?**
- a) Git Flow
- b) GitHub Flow
- c) Forking Workflow
- d) GitLab Flow

**4. In GitHub Flow, main deve essere:**
- a) Sempre stabile e deployabile
- b) Usato solo per release
- c) Mai modificato direttamente
- d) Sincronizzato settimanalmente

<details>
<summary>🔍 Risposte</summary>

1. **b)** GitHub Flow
2. **b)** In develop
3. **c)** Forking Workflow
4. **a)** Sempre stabile e deployabile

</details>

## 💻 Esercizi Pratici

### Esercizio 1: Simula Git Flow
1. Crea repository con branch main e develop
2. Crea feature branch da develop
3. Sviluppa feature e merge in develop
4. Crea release branch
5. Merge release in main e tag

### Esercizio 2: Simula GitHub Flow
1. Crea repository con solo main
2. Crea feature branch da main
3. Simula Pull Request (merge feature in main)
4. Ripeti processo per altra feature

### Esercizio 3: Confronta Strategie
1. Implementa stesso scenario con Git Flow e GitHub Flow
2. Nota differenze in numero di branch e complessità
3. Documenta pro/contro di ogni approccio

## 🔗 Collegamenti Rapidi

- **Guida successiva**: [03 - Branch Protection e Policies](03-branch-protection.md)
- **Guida precedente**: [01 - Concetti Fondamentali](01-concetti-fondamentali.md)

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ 10-Annullare-Modifiche](../../10-Annullare-Modifiche/README.md)
- [➡️ 12-Creare-e-Gestire-Branch](../../12-Creare-e-Gestire-Branch/README.md)
