# 🚀 Quick Start Guide - Git Rebase & Cherry-Pick

Benvenuto nella sezione più avanzata del corso Git! Questa guida ti aiuterà a iniziare subito con i concetti avanzati di rebase e cherry-pick.

## 🎯 Percorso di Apprendimento Consigliato

### 1. 📺 **Demo Completa** (15-20 minuti)
Prima di iniziare gli esercizi, esegui la demo interattiva completa:

```bash
cd 24-Rebase-e-Cherry-Pick
./comprehensive-demo.sh
```

**Cosa vedrai:**
- ✅ Setup ambiente multi-team realistico
- ✅ Sviluppo parallelo su feature branches
- ✅ Gestione hotfix critici con cherry-pick
- ✅ Interactive rebase per cleanup professionale
- ✅ Confronto diretto rebase vs merge
- ✅ Scenari avanzati di cherry-pick selettivo

### 2. 📚 **Studio delle Guide** (30-45 minuti)
Studia le guide teoriche nell'ordine:

1. **[Rebase Fundamentals](./guide/01-rebase-fundamentals.md)**
   - Concetti base e differenze con merge
   - Quando usare rebase vs merge

2. **[Interactive Rebase](./guide/02-interactive-rebase.md)**
   - Operazioni avanzate: squash, fixup, reword, drop
   - Cleanup professionale della cronologia

3. **[Cherry-Pick Guide](./guide/03-cherry-pick-guide.md)**
   - Applicazione selettiva di commit
   - Gestione hotfix e backporting

4. **[Rebase vs Merge](./guide/04-rebase-vs-merge.md)**
   - Analisi comparativa dettagliata
   - Decision framework per team

### 3. 👀 **Esempi Pratici** (20-30 minuti)
Esamina gli esempi step-by-step:

- **[Simple Rebase](./esempi/01-simple-rebase.md)** - Scenario base realistico
- **[Interactive Cleanup](./esempi/02-interactive-cleanup.md)** - Cleanup avanzato

### 4. 🏋️ **Esercizi Pratici** (3-6 ore totali)

**Segui questo ordine per la massima efficacia:**

#### 🟢 **Livello Base** (45 minuti)
**[Esercizio 1: Basic Rebase](./esercizi/01-basic-rebase-exercise.md)**
- Prima esperienza hands-on con rebase
- Risoluzione conflitti base
- Foundation per esercizi avanzati

#### 🟡 **Livello Intermedio** (2-3 ore)
**[Esercizio 2: Interactive Cleanup](./esercizi/02-interactive-cleanup-exercise.md)**
- Utilizzo completo dell'interactive rebase
- Tutte le operazioni: squash, fixup, reword, edit, drop
- Trasformazione cronologia disordinata in professionale

**[Esercizio 3: Cherry-Pick Mastery](./esercizi/03-cherry-pick-mastery-exercise.md)**
- Gestione ambiente multi-versione
- Hotfix critici e backporting
- Scenari complessi di cherry-pick

#### 🔴 **Livello Avanzato** (2-3 ore)
**[Esercizio 4: Rebase vs Merge Decision](./esercizi/04-rebase-vs-merge-decision-exercise.md)**
- Simulazione team multi-developer
- Analisi comparativa approfondita
- Sviluppo policy di team

## ⚡ Quick Commands Reference

### Setup Veloce
```bash
# Configurazione raccomandata per gli esercizi
git config --global alias.lg "log --oneline --graph --all"
git config --global alias.st "status --short"
git config --global alias.co "checkout"
git config --global alias.br "branch"
```

### Comandi Essenziali

#### Rebase
```bash
# Rebase semplice
git rebase main

# Interactive rebase (ultimi 3 commit)
git rebase -i HEAD~3

# Continuare dopo risoluzione conflitti
git add .
git rebase --continue

# Abbandonare rebase
git rebase --abort
```

#### Cherry-Pick
```bash
# Cherry-pick singolo commit
git cherry-pick <commit-hash>

# Cherry-pick range di commit
git cherry-pick <start-hash>..<end-hash>

# Cherry-pick con risoluzione conflitti
git cherry-pick <commit-hash>
# Risolvi conflitti manualmente
git add .
git cherry-pick --continue
```

#### Safety & Recovery
```bash
# Backup prima di operazioni rischiose
git branch backup-before-rebase

# Vedere cronologia reflog per recovery
git reflog

# Tornare a stato precedente
git reset --hard HEAD@{n}
```

## 🎯 Obiettivi di Competenza

Al completamento di questa sezione saprai:

### 🛠️ **Competenze Tecniche**
- ✅ Eseguire rebase semplici e interattivi
- ✅ Pulire cronologie di sviluppo disordinate
- ✅ Applicare cherry-pick per hotfix e backporting
- ✅ Risolvere conflitti complessi durante rebase/cherry-pick
- ✅ Scegliere strategicamente tra rebase e merge

### 🧠 **Competenze Strategiche**
- ✅ Pianificare workflow Git per team
- ✅ Gestire release multi-versione
- ✅ Implementare best practices per collaborazione
- ✅ Sviluppare policy di branching e merging

### 🚀 **Competenze Professionali**
- ✅ Mantenere cronologie pulite e leggibili
- ✅ Facilitare code review efficaci
- ✅ Ottimizzare workflow per CI/CD
- ✅ Gestire emergency hotfix in produzione

## 🆘 Troubleshooting Rapido

### Problemi Comuni e Soluzioni

**🚨 "Sono nel mezzo di un rebase e sono confuso"**
```bash
# Vedi lo stato attuale
git status

# Se vuoi abbandonare tutto
git rebase --abort

# Se vuoi continuare dopo aver risolto conflitti
git add .
git rebase --continue
```

**🚨 "Ho fatto rebase ma voglio tornare indietro"**
```bash
# Trova il commit precedente
git reflog

# Torna allo stato precedente
git reset --hard HEAD@{n}
```

**🚨 "Cherry-pick non funziona - conflitti ovunque"**
```bash
# Verifica che il commit esista
git log --oneline --all | grep "pattern"

# Usa strategia di merge specifica
git cherry-pick -X theirs <commit-hash>

# O abbandona e prova approccio diverso
git cherry-pick --abort
```

## 📈 Monitoraggio Progressi

### Checklist di Completamento

- [ ] ✅ Demo completa eseguita e compresa
- [ ] 📚 Guide teoriche studiate
- [ ] 👀 Esempi pratici esaminati
- [ ] 🟢 Esercizio 1 completato (Basic Rebase)
- [ ] 🟡 Esercizio 2 completato (Interactive Cleanup)
- [ ] 🟡 Esercizio 3 completato (Cherry-Pick Mastery)
- [ ] 🔴 Esercizio 4 completato (Decision Framework)
- [ ] 📋 Policy di team documentata
- [ ] 🧪 Tecniche applicate a progetto reale

### Auto-Valutazione

**Domande di controllo:**
1. Quando useresti rebase invece di merge?
2. Come gestiresti un hotfix critico su 3 versioni di produzione?
3. Qual è il rischio principale del rebase di commit condivisi?
4. Come pianificheresti un workflow Git per un team di 10 sviluppatori?

## 🎉 Progetti Avanzati

Dopo aver completato tutti gli esercizi, sfidati con:

1. **Automazione Workflow**
   - Script per rebase automatico con testing
   - Hook pre-commit per validazione cronologia
   - Integrazione con pipeline CI/CD

2. **Git Policy Documentation**
   - Guida completa per il tuo team
   - Decision tree per rebase vs merge
   - Template per commit messages

3. **Training Program**
   - Workshop per colleghi
   - Assessment e certificazione interna
   - Mentoring per junior developers

## 📞 Support & Community

- **Issues**: Segnala problemi o ambiguità nelle guide
- **Improvements**: Suggerisci miglioramenti o nuovi scenari
- **Sharing**: Condividi la tua esperienza e casi d'uso reali

---

**Pronto per diventare un Git expert? Inizia con la demo completa! 🚀**

```bash
./comprehensive-demo.sh
```
