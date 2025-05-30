# 12 - Creare e Gestire Branch

## 📖 Descrizione

Ora è il momento di mettere in pratica i concetti di branching! Questa esercitazione ti insegnerà tutti i comandi necessari per creare, gestire, e navigare tra branch in modo efficace e sicuro.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Creare nuovi branch con `git branch` e `git checkout -b`
- ✅ Spostarti tra branch con `git switch`
- ✅ Rinominare e cancellare branch
- ✅ Vedere tutti i branch esistenti
- ✅ Creare branch da commit specifici
- ✅ Gestire branch remoti
- ✅ Utilizzare `git switch` e `git checkout` appropriatamente
- ✅ Implementare workflow di branching efficaci

## 📋 Prerequisiti

- **Comprensione concetti di branching** (esercitazione precedente)
- **Repository Git attivo** con alcuni commit
- **Familiarità con comandi Git base**

## ⏱️ Durata Stimata

**90-120 minuti** (pratica intensiva + workflow)

## 🎯 Risultato Finale

Padroneggerai completamente la gestione dei branch e sarai pronto per implementare workflow di branching professionali.

![Branch Management](./esempi/immagini/branch-management.png)

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Creazione Branch](./guide/01-creazione-branch.md)
2. [02 - Navigazione tra Branch](./guide/02-navigazione-branch.md)
3. [03 - Gestione Branch](./guide/03-gestione-branch.md)
4. [04 - Branch Remoti](./guide/04-branch-remoti.md)
5. [05 - Best Practices](./guide/05-best-practices.md)
6. [06 - Troubleshooting](./guide/06-troubleshooting.md)

### Esempi Pratici
1. [01 - Branch Feature](./esempi/01-branch-feature.md)
2. [02 - Hotfix Workflow](./esempi/02-hotfix-workflow.md)
3. [03 - Sperimentazione](./esempi/03-sperimentazione.md)
4. [04 - Gestione Remoti](./esempi/04-gestione-remoti.md)

### Esercizi di Consolidamento
1. [01 - Feature Development](./esercizi/01-feature-development.md)
2. [02 - Multi-Branch Project](./esercizi/02-multi-branch-project.md)
3. [03 - Team Simulation](./esercizi/03-team-simulation.md)

## 🚀 Come Procedere

1. **Inizia con branch semplici** per feature isolate
2. **Pratica navigazione** frequente tra branch
3. **Sperimenta** con branch temporanei
4. **Implementa** un workflow realistico

## 🔍 Comandi Essenziali

### Creazione Branch
```bash
git branch <nome-branch>        # Crea branch (non cambia)
git checkout -b <nome-branch>   # Crea e cambia
git switch -c <nome-branch>     # Metodo moderno
```

### Navigazione
```bash
git switch <nome-branch>        # Cambia branch (moderno)
git checkout <nome-branch>      # Cambia branch (tradizionale)
git switch -                    # Torna al branch precedente
```

### Gestione
```bash
git branch                      # Lista branch locali
git branch -a                   # Lista tutti i branch
git branch -d <nome-branch>     # Cancella branch (safe)
git branch -D <nome-branch>     # Cancella branch (force)
```

## 🔍 Punti Chiave da Ricordare

- Nome branch descrittivi: `feature/login-page`
- Sempre commit prima di cambiare branch
- `git switch` è il comando moderno per navigazione
- Branch cancellati possono essere recuperati (con reflog)
- Branch remoti richiedono push esplicito

## 🆘 Problemi Comuni

- **Modifiche non salvate**: Commit o stash prima di switch
- **Branch già esistente**: Controlla con `git branch`
- **Non riesci a cancellare**: Assicurati di non essere nel branch
- **Confuso su branch corrente**: Usa `git status`

## 💡 Best Practices

### Naming Convention
```
feature/descrizione-breve
bugfix/nome-bug
hotfix/correzione-urgente
release/v1.2.0
```

### Workflow Consigliato
1. Sempre inizia da `main` aggiornato
2. Crea branch per ogni feature/bugfix
3. Commit frequenti con messaggi chiari
4. Merge quando feature è completa
5. Cancella branch dopo merge

## 📚 Risorse Aggiuntive

- [Git Branch Documentation](https://git-scm.com/docs/git-branch)
- [Git Switch Documentation](https://git-scm.com/docs/git-switch)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 12-Concetti-di-Branching](../12-Concetti-di-Branching/README.md)
- [➡️ 14-Merge-e-Strategie](../14-Merge-e-Strategie/README.md)

---

**Prossimo passo**: [14-Merge-e-Strategie](../14-Merge-e-Strategie/README.md) - Unire il lavoro dei branch
