# Rebase vs Merge: Guida Completa

## 📖 Introduzione al Confronto

La scelta tra rebase e merge è una delle decisioni più importanti nel workflow Git. Entrambi i metodi permettono di integrare modifiche da un branch all'altro, ma con filosofie, risultati e implicazioni completamente diverse. Questa guida ti aiuterà a scegliere l'approccio giusto per ogni situazione.

## 🎯 Cosa Imparerai

- Differenze concettuali tra rebase e merge
- Vantaggi e svantaggi di ciascun approccio
- Matrice decisionale per scegliere la strategia
- Impact sulla cronologia e sulla collaborazione
- Hybrid workflows e strategie combinate
- Caso studio su progetti reali

## 🔄 Confronto Visuale

### Merge: Preserva la Cronologia

```
Prima del merge:
    A---B---C feature
   /
  D---E---F main

Dopo git merge feature:
    A---B---C feature
   /         \
  D---E---F---G main
              ^
              merge commit
```

### Rebase: Cronologia Lineare

```
Prima del rebase:
    A---B---C feature
   /
  D---E---F main

Dopo git rebase main:
              A'--B'--C' feature
             /
  D---E---F main
```

## 📊 Confronto Dettagliato

| Aspetto | Merge | Rebase |
|---------|-------|--------|
| **Cronologia** | Ramificata, preserva contesto | Lineare, semplificata |
| **Commit Hash** | Mantiene originali | Crea nuovi hash |
| **Collaborazione** | Sicuro per branch condivisi | Solo per branch locali |
| **Tracciabilità** | Storia completa | Storia semplificata |
| **Conflitti** | Una volta sola | Potenzialmente multipli |
| **Reversibilità** | Facile da annullare | Più complesso |
| **Complessità** | Semplice | Richiede esperienza |

## 🎯 Quando Usare Merge

### ✅ Scenari Ideali per Merge

1. **Branch Feature Completi**
   ```bash
   # Feature branch con logica complessa
   git checkout main
   git merge feature/user-authentication
   ```

2. **Branch Condivisi**
   ```bash
   # Branch su cui lavorano più sviluppatori
   git checkout develop
   git merge feature/shared-component
   ```

3. **Release Branch**
   ```bash
   # Merge di release branch in main
   git checkout main
   git merge release/v2.1.0
   ```

4. **Tracciabilità Importante**
   ```bash
   # Quando serve sapere esattamente quando è stata integrata una feature
   git merge --no-ff feature/critical-security-fix
   ```

### 🏆 Vantaggi del Merge

- **Sicurezza**: Non modifica commit esistenti
- **Tracciabilità**: Preserva quando e come è stata integrata una feature
- **Semplicità**: Operazione sicura e reversibile
- **Collaborazione**: Funziona sempre con branch condivisi
- **Context**: Mantiene il contesto di sviluppo parallelo

### ⚠️ Svantaggi del Merge

- **Cronologia complessa**: Può diventare difficile da leggere
- **Merge commit**: Commit aggiuntivi che "inquinano" la storia
- **Debugging difficile**: Più difficile seguire il flusso logico
- **Bisect problematico**: `git bisect` meno efficace

## 🔄 Quando Usare Rebase

### ✅ Scenari Ideali per Rebase

1. **Aggiornamento Branch Feature**
   ```bash
   # Incorpora ultime modifiche di main
   git checkout feature/new-ui
   git rebase main
   ```

2. **Pulizia Pre-Merge**
   ```bash
   # Pulisci la cronologia prima del merge finale
   git rebase -i HEAD~5
   git checkout main
   git merge feature/clean-history
   ```

3. **Sincronizzazione Fork**
   ```bash
   # Aggiorna fork con upstream
   git rebase upstream/main
   ```

4. **Branch Personali**
   ```bash
   # Riorganizza il proprio lavoro
   git rebase -i main
   ```

### 🏆 Vantaggi del Rebase

- **Cronologia pulita**: Storia lineare e leggibile
- **Debugging efficace**: Facile seguire il flusso logico
- **Bisect efficiente**: `git bisect` molto più efficace
- **Commit atomici**: Ogni commit rappresenta un'unità logica completa
- **Review migliori**: Code review più facili da seguire

### ⚠️ Svantaggi del Rebase

- **Modifica cronologia**: Cambia hash dei commit esistenti
- **Conflitti multipli**: Possibili conflitti su ogni commit
- **Complessità**: Richiede maggiore esperienza
- **Perdita contesto**: Non preserva il timeline di sviluppo parallelo
- **Rischio collaborazione**: Pericoloso su branch condivisi

## 🧭 Matrice Decisionale

### Domande per la Scelta

```bash
#!/bin/bash
# decision-matrix.sh

echo "🧭 MATRICE DECISIONALE: MERGE vs REBASE"
echo "========================================"

score_merge=0
score_rebase=0

# Domanda 1: Tipo di branch
echo "1️⃣ Che tipo di branch stai integrando?"
echo "   a) Feature branch personale"
echo "   b) Branch condiviso con altri"
echo "   c) Release branch"
read q1

case $q1 in
    a) ((score_rebase += 2)) ;;
    b) ((score_merge += 3)) ;;
    c) ((score_merge += 2)) ;;
esac

# Domanda 2: Importanza cronologia
echo "2️⃣ Quanto è importante preservare la cronologia completa?"
echo "   a) Molto importante (audit, compliance)"
echo "   b) Moderatamente importante"
echo "   c) Preferisco cronologia pulita"
read q2

case $q2 in
    a) ((score_merge += 3)) ;;
    b) ((score_merge += 1)) ;;
    c) ((score_rebase += 2)) ;;
esac

# Domanda 3: Numero di commit
echo "3️⃣ Quanti commit ha il branch?"
echo "   a) Pochi commit (1-3)"
echo "   b) Numero moderato (4-10)"
echo "   c) Molti commit (10+)"
read q3

case $q3 in
    a) ((score_rebase += 1)) ;;
    b) ((score_rebase += 2)) ;;
    c) ((score_merge += 1)) ;;
esac

# Domanda 4: Qualità commit
echo "4️⃣ Come descrivi la qualità dei commit?"
echo "   a) Commit ben strutturati e atomici"
echo "   b) Mix di commit buoni e WIP"
echo "   c) Molti commit temporanei/sperimentali"
read q4

case $q4 in
    a) ((score_merge += 1)) ;;
    b) ((score_rebase += 2)) ;;
    c) ((score_rebase += 3)) ;;
esac

# Risultato
echo ""
echo "📊 RISULTATO:"
echo "Merge score: $score_merge"
echo "Rebase score: $score_rebase"

if [ $score_merge -gt $score_rebase ]; then
    echo "🔀 RACCOMANDAZIONE: Usa MERGE"
    echo "   git checkout main && git merge feature-branch"
elif [ $score_rebase -gt $score_merge ]; then
    echo "🔄 RACCOMANDAZIONE: Usa REBASE"
    echo "   git checkout feature-branch && git rebase main"
else
    echo "⚖️ EQUILIBRIO: Entrambi sono validi, scegli in base al contesto"
fi
```

## 🔄 Strategie Ibride

### 1. Rebase + Merge (Workflow Consigliato)

```bash
#!/bin/bash
# hybrid-workflow.sh

FEATURE_BRANCH=$(git branch --show-current)
MAIN_BRANCH="main"

echo "🔄 HYBRID WORKFLOW: Rebase + Merge"
echo "=================================="

# Step 1: Pulizia con rebase interattivo
echo "1️⃣ Pulizia cronologia locale..."
git rebase -i "$MAIN_BRANCH"

if [ $? -ne 0 ]; then
    echo "❌ Problemi durante rebase interattivo"
    exit 1
fi

# Step 2: Aggiornamento con main
echo "2️⃣ Aggiornamento con main..."
git checkout "$MAIN_BRANCH"
git pull origin "$MAIN_BRANCH"
git checkout "$FEATURE_BRANCH"
git rebase "$MAIN_BRANCH"

if [ $? -ne 0 ]; then
    echo "❌ Conflitti durante rebase con main"
    echo "🛠️ Risolvi conflitti e riprova"
    exit 1
fi

# Step 3: Merge in main
echo "3️⃣ Merge finale in main..."
git checkout "$MAIN_BRANCH"
git merge --no-ff "$FEATURE_BRANCH"

echo "✅ Hybrid workflow completato!"
echo "🧹 Pulisci branch: git branch -d $FEATURE_BRANCH"
```

### 2. Merge con Squash

```bash
# Combina vantaggi di entrambi
git checkout main
git merge --squash feature-branch
git commit -m "feat: add complete user authentication system

- Implement login/logout functionality  
- Add password validation
- Create user session management
- Add comprehensive tests

Closes #123"
```

### 3. Conditional Workflow

```bash
#!/bin/bash
# conditional-workflow.sh

FEATURE_BRANCH=$(git branch --show-current)
COMMIT_COUNT=$(git rev-list --count main.."$FEATURE_BRANCH")
WIP_COMMITS=$(git log --oneline main.."$FEATURE_BRANCH" --grep="wip\|temp\|fixup" | wc -l)

echo "📊 ANALISI BRANCH: $FEATURE_BRANCH"
echo "Commit totali: $COMMIT_COUNT"
echo "Commit WIP: $WIP_COMMITS"

if [ "$COMMIT_COUNT" -eq 1 ]; then
    echo "🔀 STRATEGIA: Merge diretto (single commit)"
    git checkout main && git merge "$FEATURE_BRANCH"
elif [ "$WIP_COMMITS" -gt 0 ]; then
    echo "🔄 STRATEGIA: Rebase interattivo + Merge"
    echo "💡 Prima pulisci con: git rebase -i main"
elif [ "$COMMIT_COUNT" -gt 10 ]; then
    echo "🔀 STRATEGIA: Merge con squash"
    git checkout main && git merge --squash "$FEATURE_BRANCH"
else
    echo "🔄 STRATEGIA: Rebase + Merge"
    git rebase main && git checkout main && git merge "$FEATURE_BRANCH"
fi
```

## 📈 Impact sui Workflow Aziendali

### Git Flow + Rebase

```bash
# Git Flow modificato con rebase
git checkout develop
git pull origin develop

git checkout feature/new-feature
git rebase develop  # Invece di merge

# Merge finale preserva milestone
git checkout develop
git merge --no-ff feature/new-feature
```

### GitHub Flow + Rebase

```bash
# GitHub Flow con rebase per pulizia
git checkout main
git pull origin main

git checkout feature-branch
git rebase -i main  # Pulisci commit
git push --force-with-lease origin feature-branch

# PR merge viene fatto tramite GitHub UI
```

### GitLab Flow + Selective Strategy

```bash
#!/bin/bash
# gitlab-flow-enhanced.sh

BRANCH_TYPE=$(echo "$CI_COMMIT_REF_NAME" | cut -d'/' -f1)

case "$BRANCH_TYPE" in
    "feature")
        echo "🔄 Feature branch: using rebase"
        git rebase main
        ;;
    "release")
        echo "🔀 Release branch: using merge"
        git merge --no-ff main
        ;;
    "hotfix")
        echo "🚨 Hotfix: using direct merge"
        git merge main
        ;;
esac
```

## 🔍 Debugging e Analisi

### Analisi Cronologia Post-Integrazione

```bash
#!/bin/bash
# history-analyzer.sh

echo "📊 ANALISI CRONOLOGIA POST-INTEGRAZIONE"
echo "======================================="

# Identifica tipo di integrazione
last_commit=$(git log -1 --pretty=format:"%H")
parent_count=$(git cat-file -p "$last_commit" | grep "^parent" | wc -l)

if [ "$parent_count" -eq 2 ]; then
    echo "🔀 Ultima integrazione: MERGE"
    merge_commit="$last_commit"
    
    echo "📝 Messaggio merge:"
    git log -1 --pretty=format:"%s" "$merge_commit"
    
    echo -e "\n🌲 Branch mergiati:"
    git show --pretty=format:"" --name-only "$merge_commit"
    
    echo -e "\n📊 Statistiche merge:"
    git show --stat "$merge_commit"
    
elif [ "$parent_count" -eq 1 ]; then
    echo "🔄 Ultima integrazione: probabile REBASE"
    
    echo "📈 Commit lineari recenti:"
    git log --oneline -10 --graph
    
    echo -e "\n🔍 Verifica rebase (cerca commit duplicati):"
    git log --pretty=format:"%s" -20 | sort | uniq -d
fi

# Analisi generale della cronologia
echo -e "\n📊 METRICHE CRONOLOGIA:"
total_commits=$(git rev-list --count HEAD)
merge_commits=$(git rev-list --count --merges HEAD)
echo "Total commits: $total_commits"
echo "Merge commits: $merge_commits"
echo "Merge ratio: $(( merge_commits * 100 / total_commits ))%"

# Complessità cronologia
echo -e "\n🌲 COMPLESSITÀ CRONOLOGIA:"
git log --graph --oneline -20
```

### Verifica Integrità Post-Rebase

```bash
#!/bin/bash
# integrity-check.sh

echo "🔍 VERIFICA INTEGRITÀ POST-REBASE"
echo "=================================="

# 1. Verifica repository
echo "1️⃣ Verifica integrità repository..."
git fsck --full --strict

# 2. Verifica che non ci siano commit duplicati
echo "2️⃣ Cerca commit duplicati..."
duplicate_messages=$(git log --pretty=format:"%s" | sort | uniq -d)
if [ -n "$duplicate_messages" ]; then
    echo "⚠️ Possibili commit duplicati trovati:"
    echo "$duplicate_messages"
else
    echo "✅ Nessun commit duplicato"
fi

# 3. Verifica che i test passino
echo "3️⃣ Verifica test..."
if [ -f "package.json" ] && npm test; then
    echo "✅ Test passati"
elif [ -f "Makefile" ] && make test; then
    echo "✅ Test passati"
else
    echo "⚠️ Test non eseguiti o falliti"
fi

# 4. Verifica consistenza con remote
echo "4️⃣ Verifica consistenza con remote..."
current_branch=$(git branch --show-current)
if git ls-remote --exit-code origin "$current_branch" >/dev/null 2>&1; then
    local_hash=$(git rev-parse HEAD)
    remote_hash=$(git rev-parse "origin/$current_branch")
    
    if [ "$local_hash" = "$remote_hash" ]; then
        echo "✅ Sincronizzato con remote"
    else
        echo "⚠️ Diverso da remote - potrebbe essere necessario force push"
    fi
else
    echo "📍 Branch non presente su remote"
fi
```

## 🎓 Casi Studio Reali

### Caso Studio 1: Startup Agile

**Scenario**: Team di 5 sviluppatori, release frequenti

**Strategia Adottata**:
```bash
# Per feature piccole (1-2 commit)
git rebase main && git merge --ff-only

# Per feature grandi
git rebase -i main  # pulizia
git merge --no-ff  # preserve context
```

**Risultati**:
- ✅ Cronologia pulita e leggibile
- ✅ Deploy confidence migliorata
- ⚠️ Curva di apprendimento iniziale

### Caso Studio 2: Enterprise Software

**Scenario**: Team di 50 sviluppatori, compliance rigorosa

**Strategia Adottata**:
```bash
# Sempre merge per preservare audit trail
git merge --no-ff feature-branch

# Rebase solo per branch personali
git rebase -i develop  # solo prima del merge
```

**Risultati**:
- ✅ Audit trail completo
- ✅ Tracciabilità totale
- ⚠️ Cronologia complessa

### Caso Studio 3: Open Source Project

**Scenario**: Contributori globali, maintainer-driven

**Strategia Adottata**:
```bash
# Contributor prepara con rebase
git rebase -i main
git push --force-with-lease origin feature

# Maintainer decide strategia finale
# Small PR: rebase + merge
# Large PR: merge commit
```

**Risultati**:
- ✅ Flessibilità per diverse situazioni
- ✅ Cronologia adattiva
- ✅ Contributor education

## 📊 Metriche e KPI

### Metriche per Valutare la Strategia

```bash
#!/bin/bash
# strategy-metrics.sh

echo "📊 METRICHE STRATEGIA MERGE/REBASE"
echo "=================================="

# 1. Complessità cronologia
merge_ratio=$(git rev-list --count --merges HEAD)
total_commits=$(git rev-list --count HEAD)
complexity_score=$(( merge_ratio * 100 / total_commits ))

echo "🌲 Complessità cronologia: $complexity_score%"
if [ $complexity_score -lt 20 ]; then
    echo "   ✅ Cronologia molto pulita"
elif [ $complexity_score -lt 40 ]; then
    echo "   👍 Cronologia accettabile"
else
    echo "   ⚠️ Cronologia complessa"
fi

# 2. Frequenza rebase/merge
recent_merges=$(git log --merges --since="1 month ago" --oneline | wc -l)
recent_rebases=$(git log --grep="rebase\|cherry-pick" --since="1 month ago" --oneline | wc -l)

echo "📈 Ultimo mese:"
echo "   Merge: $recent_merges"
echo "   Rebase/Cherry-pick: $recent_rebases"

# 3. Dimensione media PR
avg_pr_size=$(git log --merges --pretty=format:"" --stat --since="1 month ago" | \
              grep "files changed" | \
              awk '{sum += $1; count++} END {if(count > 0) print sum/count; else print 0}')

echo "📏 Dimensione media PR: $avg_pr_size file per PR"

# 4. Time to merge
echo "⏱️ Time to merge (ultimo 10 PR):"
git log --merges -10 --pretty=format:"%cr %s"
```

## 🎯 Raccomandazioni Finali

### Per Team Principianti
```bash
# Strategia conservativa
git merge --no-ff feature-branch
# Pros: Sicura, tracciabile
# Cons: Cronologia più complessa
```

### Per Team Esperti
```bash
# Strategia ibrida
git rebase -i main     # pulizia locale
git merge --no-ff      # integrazione formale
# Pros: Pulita ma tracciabile
# Cons: Richiede disciplina
```

### Per Progetti Open Source
```bash
# Strategia flessibile
if [ $commit_count -eq 1 ]; then
    git rebase main && git merge --ff-only
else
    git merge --no-ff
fi
# Pros: Adattiva
# Cons: Richiede automazione
```

---

## 🔄 Navigazione

**Precedente**: [03 - Cherry-Pick Guide](./03-cherry-pick-guide.md)  
**Successivo**: [01 - Simple Rebase](../esempi/01-simple-rebase.md)  
**Indice**: [README del modulo](../README.md)
