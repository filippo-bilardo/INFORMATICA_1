# 27 - Troubleshooting Comune

## 📖 Descrizione

Risoluzione dei problemi più comuni in Git e GitHub. Questa esercitazione fornisce soluzioni pratiche a situazioni di emergenza e errori frequenti che incontrerai nel lavoro quotidiano.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Diagnosticare problemi comuni Git
- ✅ Recuperare da situazioni di emergenza
- ✅ Risolvere errori di push/pull
- ✅ Gestire repository corrotti
- ✅ Recuperare lavoro perso
- ✅ Risolvere problemi di autenticazione
- ✅ Ottimizzare repository lenti
- ✅ Utilizzare git reflog per recovery

## 📋 Prerequisiti

- **Esperienza generale con Git**
- **Familiarità con comandi base**
- **Accesso a repository di test**

## ⏱️ Durata Stimata

**120-150 minuti** (simulazione problemi + risoluzione)

## 🆘 **EMERGENCY REFERENCE**

### Recupero Commit Persi
```bash
git reflog                    # Trova commit perduti
git reset --hard <hash>       # Recupera stato precedente
```

### Annullare Operazioni
```bash
git merge --abort             # Annulla merge in corso
git rebase --abort            # Annulla rebase in corso
git reset --hard HEAD~1       # Annulla ultimo commit (ATTENZIONE!)
```

### Problemi Push
```bash
git push --force-with-lease   # Force push sicuro
git pull --rebase            # Risolvi divergenze
```

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Diagnostica Problemi](./guide/01-diagnostica-problemi.md)
2. [02 - Recovery Strategies](./guide/02-recovery-strategies.md)
3. [03 - Authentication Issues](./guide/03-authentication-issues.md)
4. [04 - Performance Problems](./guide/04-performance-problems.md)
5. [05 - Emergency Procedures](./guide/05-emergency-procedures.md)

### Esempi Pratici
1. [01 - Common Scenarios](./esempi/01-common-scenarios.md)
2. [02 - Emergency Recovery](./esempi/02-emergency-recovery.md)
3. [03 - Prevention Strategies](./esempi/03-prevention-strategies.md)

### Esercizi di Consolidamento
1. [01 - Problem Simulation](./esercizi/01-problem-simulation.md)
2. [02 - Recovery Practice](./esercizi/02-recovery-practice.md)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 26-Best-Practices](../26-Best-Practices/README.md)
- [➡️ 28-Progetto-Finale](../28-Progetto-Finale/README.md)
