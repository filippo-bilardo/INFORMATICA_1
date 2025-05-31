# Esercizi di Consolidamento - Risoluzione Conflitti

## 📚 Panoramica

Questi esercizi ti permetteranno di praticare la risoluzione dei conflitti in scenari progressivamente più complessi e realistici. Ogni esercizio simula situazioni comuni nello sviluppo software collaborativo.

## 🎯 Struttura degli Esercizi

### 1. [Simulazione Conflitti](./01-simulazione-conflitti.md)
**Livello**: Principiante-Intermedio  
**Durata**: 45-60 minuti  
**Focus**: Creare e risolvere conflitti controllati
- Setup di conflitti multipli
- Pratica con diversi tipi di conflitto
- Workflow di risoluzione sistematico

### 2. [Team Conflict Resolution](./02-team-conflict-resolution.md)
**Livello**: Intermedio-Avanzato  
**Durata**: 60-90 minuti  
**Focus**: Simulazione collaborazione team
- Conflitti da sviluppo parallelo
- Comunicazione e coordinamento
- Strategie di prevenzione

### 3. [Emergency Fixes](./03-emergency-fixes.md)
**Livello**: Avanzato  
**Durata**: 60-75 minuti  
**Focus**: Gestione conflitti in situazioni critiche
- Hotfix durante release
- Risoluzione sotto pressione
- Recovery da errori

## 📋 Prerequisiti Generali

### Conoscenze Richieste
- [x] Comandi Git base (commit, branch, merge)
- [x] Comprensione marker di conflitto
- [x] Familiarità con editor di testo
- [x] Concetti di collaborazione Git

### Setup Ambiente
```bash
# Verifica versione Git
git --version  # >= 2.20

# Crea directory per esercizi
mkdir git-conflict-exercises
cd git-conflict-exercises

# Configura Git se necessario
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

## 🎮 Modalità di Esecuzione

### Individuale
- Segui le istruzioni step-by-step
- Sperimenta con varianti
- Documenta le tue decisioni

### Team/Coppia
- Alterna i ruoli (Developer A/B)
- Discuti le strategie di risoluzione
- Confronta approcci diversi

### Classe/Workshop
- Presenta soluzioni al gruppo
- Dibatti decision rationale
- Condividi best practices scoperte

## 📊 Sistema di Valutazione

### Criteri di Successo
- ✅ **Completamento**: Tutti i conflitti risolti
- ✅ **Correttezza**: Codice funzionante post-merge
- ✅ **Efficienza**: Processo di risoluzione ottimale
- ✅ **Documentazione**: Decisioni ben motivate

### Autovalutazione
Dopo ogni esercizio, rispondi:
1. Ho compreso la causa del conflitto?
2. La mia risoluzione è la migliore possibile?
3. Ho testato il risultato?
4. Potevo prevenire questo conflitto?
5. Cosa ho imparato di nuovo?

## 🛠️ Strumenti di Supporto

### Script di Diagnostic
```bash
#!/bin/bash
# conflict-diagnostic.sh
echo "🔍 Git Conflict Diagnostic"
echo "=========================="

echo "📍 Current Status:"
git status --porcelain

echo -e "\n📊 Unmerged Files:"
git diff --name-only --diff-filter=U

echo -e "\n🔗 Current Branch:"
git branch --show-current

echo -e "\n📜 Recent Commits:"
git log --oneline -5

echo -e "\n⚡ Conflicts in Files:"
for file in $(git diff --name-only --diff-filter=U); do
  echo "📄 $file:"
  grep -n "<<<<<<\|======\|>>>>>>" "$file" || echo "  No conflicts found"
done
```

### Template Risoluzione
```markdown
# Conflict Resolution Report

**Date**: $(date)
**Exercise**: [Nome Esercizio]
**Files**: [Lista file in conflitto]

## Analisi Conflitto
- **Causa**: 
- **Tipo**: [Content/Rename/Delete]
- **Complessità**: [Bassa/Media/Alta]

## Strategia Risoluzione
- [ ] Manual merge
- [ ] Accept ours
- [ ] Accept theirs
- [ ] Custom solution

## Decisioni Prese
1. **File 1**: [Rationale]
2. **File 2**: [Rationale]

## Testing
- [ ] Syntax check
- [ ] Unit tests
- [ ] Manual testing

## Lessons Learned
- 
- 
```

## 📈 Progressione Consigliata

### Settimana 1: Fondamentali
1. Completa tutti gli esempi pratici
2. Esercizio 1: Simulazione Conflitti
3. Review e documentazione

### Settimana 2: Collaborazione
1. Esercizio 2: Team Conflict Resolution
2. Sperimentazione con merge tools
3. Setup workflow preventivi

### Settimana 3: Scenari Avanzati
1. Esercizio 3: Emergency Fixes
2. Creazione casi studio personali
3. Ottimizzazione processo team

## 🎯 Obiettivi di Apprendimento

Al termine degli esercizi sarai in grado di:

### Competenze Tecniche
- ✅ Riconoscere tipi di conflitto immediatamente
- ✅ Scegliere strategia di risoluzione ottimale
- ✅ Usare merge tools efficacemente
- ✅ Gestire conflitti multi-file complessi
- ✅ Applicare tecniche di prevenzione

### Competenze Collaborative
- ✅ Comunicare decisioni di risoluzione
- ✅ Coordinare merge in team
- ✅ Documentare risoluzioni complesse
- ✅ Trainare altri membri del team
- ✅ Stabilire workflow preventivi

### Competenze di Problem Solving
- ✅ Analizzare conflitti sistematicamente
- ✅ Valutare impatto delle decisioni
- ✅ Gestire situazioni di emergenza
- ✅ Ottimizzare processi esistenti
- ✅ Anticipare problemi futuri

## 📚 Risorse di Supporto

### Durante gli Esercizi
- [Git Documentation](https://git-scm.com/docs/git-merge)
- [Atlassian Git Tutorials](https://www.atlassian.com/git/tutorials/using-branches/merge-conflicts)
- [GitHub Conflict Resolution](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts)

### Emergency Commands
```bash
# Se rimani bloccato
git merge --abort        # Annulla merge
git status              # Vedi stato corrente
git log --oneline -10   # Storia recente
git diff HEAD           # Vedi modifiche non committate
```

## ⚠️ Note Importanti

### Prima di Iniziare
- Crea sempre backup: `git branch backup-$(date +%Y%m%d)`
- Lavora in repository di test, non in progetti reali
- Leggi completamente le istruzioni prima di iniziare

### Durante gli Esercizi
- Non aver fretta: comprendi ogni passaggio
- Sperimenta con varianti e alternative
- Documenta decisioni non ovvie

### Dopo il Completamento
- Rivedi le soluzioni proposte
- Confronta con approcci alternativi
- Condividi learning con il team

## 🎊 Riconoscimenti

### Badge di Competenza
- 🥉 **Conflict Resolver**: Completa tutti gli esercizi base
- 🥈 **Merge Master**: Risolve conflitti complessi efficientemente
- 🥇 **Conflict Preventer**: Implementa strategie preventive efficaci

### Portfolio Showcase
Documenta i tuoi migliori esempi di risoluzione per:
- Colloqui tecnici
- Code review con il team
- Training di nuovi colleghi
- Contributi open source

---

**Pronto per iniziare?** Passa al [primo esercizio](./01-simulazione-conflitti.md) e inizia a padroneggiare l'arte della risoluzione dei conflitti!
