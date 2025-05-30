# 14 - Risoluzione Conflitti

## 📖 Descrizione

I conflitti di merge sono normali nello sviluppo collaborativo. Questa esercitazione ti insegnerà a riconoscere, comprendere e risolvere conflitti in modo efficace, trasformando una situazione potenzialmente stressante in un'operazione di routine.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Comprendere cosa causa i conflitti di merge
- ✅ Riconoscere i marker di conflitto in Git
- ✅ Utilizzare strumenti per risolvere conflitti
- ✅ Eseguire merge manuali con editor
- ✅ Utilizzare merge tool grafici (VS Code, GitKraken)
- ✅ Prevenire conflitti con best practices
- ✅ Gestire conflitti complessi multi-file
- ✅ Testare risoluzione prima di finalizzare

## 📋 Prerequisiti

- **Esperienza con merge** (esercitazione precedente)
- **Familiarità con editor di testo**
- **Repository con branch divergenti**

## ⏱️ Durata Stimata

**120-150 minuti** (pratica intensiva + scenari complessi)

## 🎯 Risultato Finale

Avrai confidenza nella risoluzione di conflitti e saprai utilizzare sia strumenti da linea di comando che interfacce grafiche per gestire situazioni complesse.

![Merge Conflict Resolution](./esempi/immagini/conflict-resolution.png)

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Cosa Sono i Conflitti](./guide/01-cosa-sono-conflitti.md)
2. [02 - Marker di Conflitto](./guide/02-marker-conflitto.md)
3. [03 - Risoluzione Manuale](./guide/03-risoluzione-manuale.md)
4. [04 - Merge Tools](./guide/04-merge-tools.md)
5. [05 - Prevenzione Conflitti](./guide/05-prevenzione-conflitti.md)
6. [06 - Strategie Avanzate](./guide/06-strategie-avanzate.md)

### Esempi Pratici
1. [01 - Conflitto Semplice](./esempi/01-conflitto-semplice.md)
2. [02 - Conflitti Multi-File](./esempi/02-conflitti-multi-file.md)
3. [03 - Risoluzione con VS Code](./esempi/03-risoluzione-vscode.md)
4. [04 - Conflitti Complessi](./esempi/04-conflitti-complessi.md)

### Esercizi di Consolidamento
1. [01 - Simulazione Conflitti](./esercizi/01-simulazione-conflitti.md)
2. [02 - Team Conflict Resolution](./esercizi/02-team-conflict-resolution.md)
3. [03 - Emergency Fixes](./esercizi/03-emergency-fixes.md)

## 🚀 Come Procedere

1. **Crea conflitti controllati** per praticare
2. **Impara i marker** di conflitto di Git
3. **Pratica risoluzione manuale** prima degli strumenti
4. **Sperimenta con merge tools** diversi

## 🔍 Anatomia di un Conflitto

### Marker di Conflitto Git
```
<<<<<<< HEAD
Contenuto del branch corrente
=======
Contenuto del branch che stai mergendo
>>>>>>> nome-branch
```

### Processo di Risoluzione
1. **Identifica** i file in conflitto
2. **Apri** file con editor
3. **Risolvi** manualmente o con tool
4. **Rimuovi** marker di conflitto
5. **Testa** la risoluzione
6. **Commit** il merge

## 🔍 Punti Chiave da Ricordare

- I conflitti sono normali in sviluppo collaborativo
- Git non può risolvere modifiche alle stesse righe
- Sempre testare dopo risoluzione conflitti
- Comunicare con team su conflitti complessi
- `git status` mostra file in conflitto

## 🛠️ Strumenti per Risoluzione

### Editor di Testo
- **VS Code**: Interfaccia intuitiva con bottoni
- **Vim**: Potente ma richiede conoscenza
- **Nano**: Semplice per principianti

### Merge Tools Grafici
- **GitKraken**: Interfaccia visual completa
- **Meld**: Tool gratuito per Linux
- **Beyond Compare**: Professionale per Windows

### Comandi Git Utili
```bash
git status                    # Vedi file in conflitto
git diff                      # Mostra differenze
git merge --abort             # Annulla merge
git mergetool                 # Apri merge tool
```

## 🆘 Situazioni di Emergenza

### Merge Andato Male
```bash
git merge --abort             # Torna allo stato pre-merge
git reset --hard HEAD~1       # Se merge già committato (ATTENZIONE!)
```

### Conflitto Non Risolto
```bash
git status                    # Controlla tutti i file
git add .                     # Aggiungi file risolti
git commit                    # Completa merge
```

### Risoluzione Sbagliata
```bash
git reset --soft HEAD~1       # Mantieni modifiche, annulla commit
# Risolvi di nuovo
git commit                    # Nuovo commit merge
```

## 💡 Prevenzione Conflitti

### Best Practices
1. **Commit frequenti** e piccoli
2. **Pull regolare** da main/develop
3. **Comunicazione team** su aree di lavoro
4. **Feature branch** ben definiti
5. **Code review** prima del merge

### Workflow Consigliato
```bash
# Prima di iniziare feature
git checkout main
git pull origin main
git checkout -b feature/nuova-feature

# Durante sviluppo (regolarmente)
git checkout main
git pull origin main
git checkout feature/nuova-feature
git merge main  # o rebase
```

## ⚠️ Avvertenze

- Non ignorare mai i conflitti
- Testa sempre dopo risoluzione
- Non fare force push dopo merge conflitti
- Chiedi aiuto per conflitti complessi

## 📚 Risorse Aggiuntive

- [Atlassian - Merge Conflicts](https://www.atlassian.com/git/tutorials/using-branches/merge-conflicts)
- [VS Code - Git Integration](https://code.visualstudio.com/docs/editor/versioncontrol)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 14-Merge-e-Strategie](../14-Merge-e-Strategie/README.md)
- [➡️ 16-Introduzione-GitHub](../16-Introduzione-GitHub/README.md)

---

**Prossimo passo**: [16-Introduzione-GitHub](../16-Introduzione-GitHub/README.md) - Dal Git locale alla collaborazione online
