# 10 - Annullare Modifiche

## 📖 Descrizione

Gli errori fanno parte dello sviluppo software. Questa esercitazione ti insegnerà tutti i modi per correggere errori, annullare modifiche indesiderate e recuperare da situazioni problematiche in Git.

## 🎯 Obiettivi di Apprendimento

Al termine di questa esercitazione sarai in grado di:

- ✅ Annullare modifiche in working directory con `git restore`
- ✅ Rimuovere file dall'area di staging
- ✅ Modificare l'ultimo commit con `git commit --amend`
- ✅ Utilizzare `git revert` per annullamenti sicuri
- ✅ Applicare `git reset` con le sue modalità
- ✅ Recuperare file cancellati
- ✅ Distinguere quando usare revert vs reset
- ✅ Gestire situazioni di emergenza

## 📋 Prerequisiti

- **Padronanza area di staging** (esercitazione 05)
- **Esperienza con commit e log**
- **Repository con cronologia per testing**

## ⏱️ Durata Stimata

**90-120 minuti** (teoria critica + pratica attenta)

## 🎯 Risultato Finale

Avrai confidenza nel correggere errori e annullare modifiche senza paura di perdere lavoro importante, sapendo scegliere il metodo giusto per ogni situazione.

![Git Undo Operations](./esempi/immagini/git-undo-operations.png)

## 📚 Indice degli Argomenti

### Guide Teoriche
1. [01 - Tipi di Annullamenti](./guide/01-tipi-annullamenti.md)
2. [02 - Git Restore (Moderno)](./guide/02-git-restore.md)
3. [03 - Git Reset Spiegato](./guide/03-git-reset.md)
4. [04 - Git Revert vs Reset](./guide/04-revert-vs-reset.md)
5. [05 - Modificare Commit (Amend)](./guide/05-modificare-commit.md)
6. [06 - Recupero File](./guide/06-recupero-file.md)

### Esempi Pratici
1. [01 - Annullamenti Base](./esempi/01-annullamenti-base.md)
2. [02 - Scenari di Emergenza](./esempi/02-scenari-emergenza.md)
3. [03 - Correzioni Sicure](./esempi/03-correzioni-sicure.md)
4. [04 - Recupero Avanzato](./esempi/04-recupero-avanzato.md)

### Esercizi di Consolidamento
1. [01 - Simulazione Errori](./esercizi/01-simulazione-errori.md)
2. [02 - Recupero Dati](./esercizi/02-recupero-dati.md)
3. [03 - Emergency Response](./esercizi/03-emergency-response.md)
4. [04 - Undo Operations Mastery](./esercizi/04-undo-operations-mastery.md)

## 🚀 Come Procedere

1. **IMPORTANTE**: Crea backup prima degli esercizi
2. **Comprendi le differenze** tra i vari metodi
3. **Pratica in ambiente sicuro** prima di applicare a progetti reali
4. **Testa ogni scenario** gradualmente

## 🔍 Punti Chiave da Ricordare

- `git restore` per modifiche non committate
- `git commit --amend` solo per ultimo commit non pushato
- `git revert` è sicuro per cronologia pubblica
- `git reset --hard` è potente ma pericoloso
- `git reflog` è il tuo salvavita

## 🆘 Situazioni di Emergenza

### Ho cancellato file importanti
```bash
git restore <filename>  # Se non committato
git show HEAD:<filename> > <filename>  # Da ultimo commit
```

### Ho fatto commit sbagliato
```bash
git commit --amend  # Se non ancora pushato
git revert HEAD     # Se già pushato
```

### Ho fatto reset sbagliato
```bash
git reflog  # Trova hash commit perso
git reset --hard <hash>  # Recupera
```

## ⚠️ Avvertenze Critiche

- **MAI** usare `git reset --hard` su repository condivisi
- **SEMPRE** fare backup prima di operazioni distruttive
- **VERIFICA** due volte prima di `--force` push
- **USA** `git revert` per cronologia pubblica

## 📚 Risorse Aggiuntive

- [Atlassian - Undoing Changes](https://www.atlassian.com/git/tutorials/undoing-changes)
- [Oh Shit, Git!?!](https://ohshitgit.com/)

## 🔄 Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ 10-Navigare-tra-Commit](../10-Navigare-tra-Commit/README.md)
- [➡️ 12-Concetti-di-Branching](../12-Concetti-di-Branching/README.md)

---

**Prossimo passo**: [12-Concetti-di-Branching](../12-Concetti-di-Branching/README.md) - Iniziamo con i branch Git
