# 10 - Navigare tra Commit

## 📖 Descrizione

Imparare a spostarsi nella cronologia Git è fondamentale per debugging, testing e comprensione dell'evoluzione del codice. Questa esercitazione ti insegnerà a viaggiare nel tempo del tuo repository in modo sicuro ed efficace.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Utilizzare `git checkout` per spostarti tra commit
- ✅ Comprendere lo stato "detached HEAD"
- ✅ Navigare usando hash, tag e riferimenti
- ✅ Tornare a branch specifici dopo l'esplorazione
- ✅ Creare branch da commit storici
- ✅ Utilizzare `git switch` (Git moderno)
- ✅ Esplorare in modo sicuro senza perdere lavoro

## 📋 Prerequisiti

- **Repository con cronologia significativa** (almeno 5-10 commit)
- **Conoscenza di `git log`** (esercitazione precedente)
- **Familiarità con concetti base Git**

## ⏱️ Durata Stimata

**75-90 minuti** (navigazione + sperimentazione)

## 🎯 Risultato Finale

Sarai in grado di navigare confidentemente nella cronologia Git per debugging, testing di versioni precedenti, e comprensione dell'evoluzione del codice.

![Git Navigation](./esempi/immagini/git-navigation.png)

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Concetti di Navigazione](./guide/01-concetti-navigazione.md)
2. [02 - Git Checkout vs Switch](./guide/02-checkout-vs-switch.md)
3. [03 - Detached HEAD State](./guide/03-detached-head.md)
4. [04 - Riferimenti e Hash](./guide/04-riferimenti-hash.md)
5. [05 - Navigazione Sicura](./guide/05-navigazione-sicura.md)

### Esempi Pratici
1. [01 - Esplorazione Base](./esempi/01-esplorazione-base.md)
2. [02 - Debug Temporale](./esempi/02-debug-temporale.md)
3. [03 - Testing Versioni](./esempi/03-testing-versioni.md)
4. [04 - Recupero da Detached HEAD](./esempi/04-recupero-detached-head.md)

### Esercizi di Consolidamento
1. [01 - Viaggio nel Tempo](./esercizi/01-viaggio-nel-tempo.md)
2. [02 - Detective Bug](./esercizi/02-detective-bug.md)
3. [03 - Gestione Sicura](./esercizi/03-gestione-sicura.md)
4. [04 - Time Travel Mastery Forensics](./esercizi/04-time-travel-mastery-forensics.md)

## 🚀 Come Procedere

1. **Comprendi i concetti** di HEAD e checkout
2. **Pratica navigazione base** con commit recenti
3. **Sperimenta detached HEAD** in modo controllato
4. **Applica a scenari reali** di debugging

## 🔍 Punti Chiave da Ricordare

- `git checkout <hash>` ti porta al commit specifico
- Detached HEAD è normale durante esplorazione
- `git switch -` torna al branch precedente
- Sempre fare backup prima di navigazioni complesse
- `git reflog` mostra tutta la cronologia di navigazione

## 🆘 Problemi Comuni

- **Perso in detached HEAD**: Usa `git switch <branch-name>`
- **Modifiche non salvate**: Commit o stash prima di navigare
- **Hash sbagliato**: Controlla con `git log --oneline`

## ⚠️ Avvertenze Importanti

- Non fare commit in detached HEAD senza creare branch
- Salva sempre il lavoro prima di navigare
- Usa `git reflog` se ti perdi

## 📚 Risorse Aggiuntive

- [Git Checkout Documentation](https://git-scm.com/docs/git-checkout)
- [Git Switch Documentation](https://git-scm.com/docs/git-switch)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 08-Visualizzare-Storia-Commit](../08-Visualizzare-Storia-Commit/README.md)
- [➡️ 11-Annullare-Modifiche](../11-Annullare-Modifiche/README.md)

---

**Prossimo passo**: [11-Annullare-Modifiche](../11-Annullare-Modifiche/README.md) - Correggere errori e annullare cambiamenti
