# Esercizio 01: Analisi Repository e Struttura Branch

## Obiettivo
Analizzare repository esistenti per comprendere strategie di branching e strutture Git attraverso l'esplorazione pratica di progetti reali.

## Durata Stimata
45-60 minuti

## Prerequisiti
- Conoscenza dei comandi Git base
- Comprensione teorica dei branch
- Accesso a internet per clonare repository

## Parte 1: Analisi Repository Open Source

### Setup Iniziale
```bash
# Creare directory di lavoro
mkdir branch-analysis
cd branch-analysis

# Repository da analizzare (scegli uno o più)
REPOS=(
  "https://github.com/facebook/react.git"
  "https://github.com/microsoft/vscode.git" 
  "https://github.com/vuejs/vue.git"
  "https://github.com/angular/angular.git"
)
```

### Esercizio 1.1: Clonazione e Prima Analisi
Clona un repository e analizza la struttura dei branch:

```bash
# Clonare il primo repository
git clone --depth=50 ${REPOS[0]} react-analysis
cd react-analysis

# Analisi immediata
echo "=== ANALISI REPOSITORY REACT ==="
echo "URL: $(git remote get-url origin)"
echo "Ultimo commit: $(git log -1 --oneline)"
echo "Branch attuale: $(git branch --show-current)"
```

**Compito 1.1**: Rispondi alle seguenti domande:

1. Qual è il branch principale del progetto?
2. Quanti branch remoti esistono?
3. Qual è l'ultimo commit e quando è stato fatto?

<details>
<summary>📋 Comandi per l'analisi</summary>

```bash
# 1. Branch principale
git symbolic-ref refs/remotes/origin/HEAD
# oppure
git remote show origin | grep "HEAD branch"

# 2. Contare branch remoti
git branch -r | wc -l
git branch -r | head -10  # Primi 10 per vedere pattern

# 3. Ultimo commit con dettagli
git log -1 --format="%h - %an, %ar : %s"
```
</details>

### Esercizio 1.2: Mappatura Branch Attivi
Identifica i branch più importanti e attivi:

```bash
# Vedere tutti i branch con ultima modifica
git for-each-ref --format='%(refname:short) %(committerdate) %(authorname)' refs/remotes | sort -k2 -r | head -20

# Branch più recenti (ultimi 30 giorni)
git for-each-ref --format='%(refname:short) %(committerdate:relative)' refs/remotes | grep -E "(days?|weeks?|hours?|minutes?) ago" | head -10
```

**Compito 1.2**: Crea una tabella dei branch principali:

| Nome Branch | Ultimo Commit | Scopo/Descrizione |
|-------------|---------------|-------------------|
| main/master | [data] | Branch principale |
| develop | [data] | Sviluppo attivo |
| feature/* | [data] | Nuove funzionalità |

<details>
<summary>📋 Script per analisi automatica</summary>

```bash
# Script per generare tabella automaticamente
cat << 'EOF' > analyze-branches.sh
#!/bin/bash
echo "| Nome Branch | Ultimo Commit | Autore | Descrizione |"
echo "|-------------|---------------|---------|-------------|"

git for-each-ref --format='%(refname:short)|%(committerdate:short)|%(authorname)|%(subject)' refs/remotes/origin | 
head -10 | 
while IFS='|' read branch date author subject; do
  echo "| $branch | $date | $author | $subject |"
done
EOF

chmod +x analyze-branches.sh
./analyze-branches.sh
```
</details>

### Esercizio 1.3: Analisi Strategia di Branching
Determina che strategia di branching usa il progetto:

```bash
# Cercare pattern nei nomi dei branch
git branch -r | grep -E "(feature|feat|dev|develop|release|hotfix|main|master)" | head -20

# Vedere cronologia dei merge
git log --oneline --merges --graph -20

# Analizzare tag e release
git tag --sort=-creatordate | head -10
```

**Compito 1.3**: Identifica la strategia utilizzata:

- [ ] **Git Flow**: main + develop + feature/* + release/* + hotfix/*
- [ ] **GitHub Flow**: main + feature/* (semplificato)
- [ ] **GitLab Flow**: main + environment branches
- [ ] **Custom Strategy**: [descrivi]

<details>
<summary>📋 Indicatori per riconoscere le strategie</summary>

**Git Flow Indicators:**
```bash
# Cerca questi pattern
git branch -r | grep -E "develop|release/|hotfix/"
```

**GitHub Flow Indicators:**
```bash
# Solo main/master e feature branches
git branch -r | grep -v -E "develop|release/|hotfix/" | grep -E "feature/|main|master"
```

**Analisi Merge Strategy:**
```bash
# Vedere se usano merge commit o squash
git log --oneline --merges | head -5
git log --oneline --no-merges | head -5
```
</details>

## Parte 2: Analisi Struttura Commit e Merge

### Esercizio 2.1: Cronologia e Pattern di Merge
Analizza come vengono integrati i cambiamenti:

```bash
# Visualizzazione grafica avanzata
git log --oneline --graph --decorate --all -20

# Analisi merge vs squash
echo "=== MERGE COMMITS ==="
git log --merges --oneline -10

echo "=== COMMIT DIRETTI ==="
git log --no-merges --oneline -10 | head -5
```

**Compito 2.1**: Determina:
1. Usano merge commit o squash and merge?
2. I branch feature vengono eliminati dopo il merge?
3. Qual è la frequenza dei merge nel branch principale?

<details>
<summary>📋 Analisi dettagliata merge</summary>

```bash
# Conta tipi di commit
total_commits=$(git rev-list --count HEAD)
merge_commits=$(git rev-list --merges --count HEAD)
direct_commits=$((total_commits - merge_commits))

echo "Totale commit: $total_commits"
echo "Merge commit: $merge_commits"
echo "Commit diretti: $direct_commits"
echo "Percentuale merge: $(echo "scale=2; $merge_commits * 100 / $total_commits" | bc)%"

# Pattern nei messaggi di merge
git log --merges --pretty=format:"%s" -20 | head -10
```
</details>

### Esercizio 2.2: Analisi Autori e Contributori
Studia i pattern di collaborazione:

```bash
# Top contributori
git shortlog -sn | head -10

# Attività negli ultimi mesi
git log --since="3 months ago" --pretty=format:"%an" | sort | uniq -c | sort -nr | head -10

# Contributori per branch
git log develop --since="1 month ago" --pretty=format:"%an" | sort | uniq -c | sort -nr 2>/dev/null || echo "No develop branch"
```

**Compito 2.2**: Crea un profilo del team:
- Numero di contributori attivi
- Chi sono i maintainer principali
- Frequenza dei contributi

## Parte 3: Creazione Repository di Test

### Esercizio 3.1: Simulazione Strategia Identificata
Crea un nuovo repository che replica la strategia osservata:

```bash
# Tornare alla directory principale
cd ../
mkdir test-strategy
cd test-strategy
git init

# Setup iniziale
echo "# Test Repository Strategy" > README.md
echo "Simulazione della strategia osservata nel repository analizzato" >> README.md
git add README.md
git commit -m "Initial commit"

# Creare branch secondo la strategia identificata
# Esempio per Git Flow:
git checkout -b develop
echo "Development version" >> README.md
git add README.md
git commit -m "Setup development branch"
```

**Compito 3.1**: Replica la struttura dei branch osservata nel repository analizzato.

<details>
<summary>📋 Template Git Flow</summary>

```bash
# Se hai identificato Git Flow
git checkout -b develop
git checkout -b feature/user-auth
echo "User authentication feature" > auth.md
git add auth.md
git commit -m "Add user authentication"

# Merge feature in develop
git checkout develop
git merge feature/user-auth --no-ff -m "Merge feature: user authentication"

# Creare release branch
git checkout -b release/1.0.0
echo "version: 1.0.0" > version.txt
git add version.txt
git commit -m "Bump version to 1.0.0"

# Merge in main
git checkout main
git merge release/1.0.0 --no-ff -m "Release version 1.0.0"
git tag -a v1.0.0 -m "Version 1.0.0"

# Merge back in develop
git checkout develop
git merge release/1.0.0 --no-ff -m "Merge release back to develop"
```
</details>

### Esercizio 3.2: Test della Strategia
Simula diversi scenari di sviluppo:

```bash
# Scenario 1: Sviluppo parallelo
git checkout develop
git checkout -b feature/payment-system
echo "Payment integration" > payment.md
git add payment.md
git commit -m "Add payment system"

# Nel frattempo, altro sviluppo
git checkout develop
git checkout -b feature/user-profile
echo "User profile management" > profile.md
git add profile.md
git commit -m "Add user profile"

# Merge entrambi
git checkout develop
git merge feature/payment-system --no-ff
git merge feature/user-profile --no-ff
```

**Compito 3.2**: Testa questi scenari:
1. Sviluppo di 2 feature parallele
2. Hotfix urgente sul branch main
3. Release con cherry-pick selective

## Parte 4: Comparazione Strategie

### Esercizio 4.1: Analisi Comparativa
Confronta diversi approcci analizzando più repository:

```bash
# Ritorna alla directory principale
cd ../

# Analizza brevemente altri repository
for repo in "${REPOS[@]:1:2}"; do
  name=$(basename "$repo" .git)
  echo "=== Analizzando $name ==="
  git clone --depth=10 "$repo" "${name}-analysis"
  cd "${name}-analysis"
  
  echo "Branch principale: $(git symbolic-ref refs/remotes/origin/HEAD 2>/dev/null || echo 'main/master')"
  echo "Numero branch: $(git branch -r | wc -l)"
  echo "Ultimo commit: $(git log -1 --oneline)"
  echo "Top 3 contributori:"
  git shortlog -sn | head -3
  echo ""
  
  cd ../
done
```

**Compito 4.1**: Completa questa tabella comparativa:

| Repository | Strategia | Branch Principale | Num Branch | Attività |
|------------|-----------|-------------------|------------|----------|
| React | [?] | [?] | [?] | [alta/media/bassa] |
| VSCode | [?] | [?] | [?] | [alta/media/bassa] |
| Vue | [?] | [?] | [?] | [alta/media/bassa] |

### Esercizio 4.2: Raccomandazioni
Basandoti sull'analisi, fornisci raccomandazioni:

**Compito 4.2**: Per ogni scenario, quale strategia consiglieresti?

1. **Startup con 3 sviluppatori:**
   - Strategia: ________________
   - Motivo: ___________________

2. **Enterprise con 50+ sviluppatori:**
   - Strategia: ________________
   - Motivo: ___________________

3. **Progetto open source con molti contributori occasionali:**
   - Strategia: ________________
   - Motivo: ___________________

<details>
<summary>📋 Considerazioni per le raccomandazioni</summary>

**Fattori da considerare:**
- Dimensione del team
- Frequenza di release
- Complessità del progetto
- Necessità di hotfix
- Livello di esperienza del team
- Automazione disponibile

**GitHub Flow**: Semplice, veloce, adatto a team piccoli e deployment continuo
**Git Flow**: Strutturato, adatto a release pianificate e team grandi
**GitLab Flow**: Bilanciato, buono per ambienti multipli
</details>

## Parte 5: Documentazione Analisi

### Report Finale
Crea un report completo della tua analisi:

```bash
# Creare report template
cat > branch-analysis-report.md << 'EOF'
# Analisi Strategie di Branching

## Repository Analizzati
- [Nome repository 1]: [URL]
- [Nome repository 2]: [URL]

## Strategie Identificate
### Repository 1
- **Strategia**: [Git Flow/GitHub Flow/Custom]
- **Branch principale**: [main/master]
- **Pattern**: [descrizione]
- **Pro**: [vantaggi osservati]
- **Contro**: [svantaggi osservati]

## Raccomandazioni
[Le tue conclusioni]

## Lessons Learned
[Cosa hai imparato]
EOF
```

**Compito Finale**: Completa il report con le tue osservazioni e conclusioni.

## Criteri di Valutazione

### Checklist Completamento
- [ ] Analizzato almeno 2 repository diversi
- [ ] Identificato strategia di branching per ogni repository
- [ ] Compreso pattern di merge e collaborazione
- [ ] Creato repository di test con strategia replicata
- [ ] Comparato diverse strategie
- [ ] Fornito raccomandazioni basate su scenari
- [ ] Documentato analisi in report finale

### Competenze Sviluppate
- ✅ **Analisi**: Capacità di analizzare repository esistenti
- ✅ **Identificazione**: Riconoscere strategie di branching
- ✅ **Comparazione**: Confrontare pro/contro di diverse strategie
- ✅ **Applicazione**: Implementare strategie identificate
- ✅ **Raccomandazione**: Suggerire strategie appropriate

## Approfondimenti Consigliati

Se vuoi approfondire ulteriormente:

### Per migliorare l'analisi:
- [Guida 06: Strategie Branching](../guide/06-strategie-branching.md)
- [Guida 07: Workflow Comuni](../guide/07-workflow-comuni.md)

### Per esplorare di più:
- Analizza repository nei tuoi linguaggi preferiti
- Studia progetti con diverse dimensioni di team
- Esamina progetti con cicli di release diversi

## Troubleshooting

### Se il clone è troppo lento:
```bash
# Usa shallow clone
git clone --depth=10 [url]
```

### Se hai problemi con branch remoti:
```bash
# Refresh branch remoti
git fetch origin
git remote prune origin
```

### Per repository molto grandi:
```bash
# Clone parziale
git clone --filter=blob:none [url]
```

---
[⬅️ Guide](../guide/README.md) | [🏠 Modulo 12](../README.md) | [➡️ Esercizio 02](./02-progettazione-branch.md)
