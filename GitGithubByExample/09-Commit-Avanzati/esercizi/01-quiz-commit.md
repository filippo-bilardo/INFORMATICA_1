# Esercizio 01: Quiz sui Commit Avanzati

## Obiettivo
Verificare la comprensione dei concetti fondamentali sui commit avanzati attraverso un quiz interattivo con domande teoriche e pratiche.

## Durata Stimata
20-30 minuti

## Prerequisiti
- Completamento delle guide del modulo
- Conoscenza base dei comandi Git
- Comprensione del workflow Git

## Quiz Teorico

### Sezione A: Concetti Fondamentali

**Domanda 1: Git Commit --amend**
Quale delle seguenti affermazioni su `git commit --amend` è CORRETTA?

a) Crea un nuovo commit senza modificare quello precedente
b) Modifica l'ultimo commit aggiungendo nuove modifiche o cambiando il messaggio
c) Annulla completamente l'ultimo commit
d) Può essere usato solo per cambiare il messaggio di commit

<details>
<summary>Risposta</summary>
**b) Modifica l'ultimo commit aggiungendo nuove modifiche o cambiando il messaggio**

`git commit --amend` sostituisce completamente l'ultimo commit con uno nuovo che può includere modifiche aggiuntive e/o un messaggio diverso.
</details>

**Domanda 2: Conventional Commits**
Qual è il formato corretto per un conventional commit che introduce una nuova funzionalità?

a) `add: new user authentication system`
b) `feat: add user authentication system`
c) `feature: user authentication system`
d) `new: user authentication system added`

<details>
<summary>Risposta</summary>
**b) feat: add user authentication system**

Il formato conventional commit richiede un tipo specifico seguito da due punti e una descrizione. "feat" è il tipo corretto per nuove funzionalità.
</details>

**Domanda 3: Git Reset vs Git Revert**
Qual è la differenza principale tra `git reset` e `git revert`?

a) Non c'è differenza, fanno la stessa cosa
b) Reset modifica la cronologia, revert crea un nuovo commit
c) Revert è più veloce di reset
d) Reset funziona solo con file, revert con commit

<details>
<summary>Risposta</summary>
**b) Reset modifica la cronologia, revert crea un nuovo commit**

`git reset` riscrive la cronologia rimuovendo commit, mentre `git revert` mantiene la cronologia creando un nuovo commit che annulla le modifiche.
</details>

### Sezione B: Scenari Pratici

**Domanda 4: Correzione Messaggio**
Hai appena fatto un commit con il messaggio "fix bug", ma vuoi essere più specifico. Quale comando usi?

a) `git commit --message "fix: resolve login validation bug"`
b) `git commit --amend -m "fix: resolve login validation bug"`
c) `git reset --soft HEAD~1 && git commit -m "fix: resolve login validation bug"`
d) `git revert HEAD && git commit -m "fix: resolve login validation bug"`

<details>
<summary>Risposta</summary>
**b) git commit --amend -m "fix: resolve login validation bug"**

Il comando `--amend` con `-m` permette di modificare il messaggio dell'ultimo commit in modo diretto.
</details>

**Domanda 5: Commit Atomici**
Hai modificato 3 file diversi per 3 funzionalità separate. Qual è l'approccio migliore?

a) Un singolo commit con tutti i file: "update multiple features"
b) Tre commit separati, uno per funzionalità
c) Due commit: uno per i file più importanti, uno per il resto
d) Non importa, purché il codice funzioni

<details>
<summary>Risposta</summary>
**b) Tre commit separati, uno per funzionalità**

I commit atomici facilitano il debug, il review e il rollback. Ogni commit dovrebbe rappresentare una singola modifica logica.
</details>

### Sezione C: Conventional Commits Avanzati

**Domanda 6: Breaking Changes**
Come si indica un breaking change nei conventional commits?

a) `BREAKING: change API endpoint structure`
b) `feat!: change API endpoint structure`
c) `break: change API endpoint structure`
d) `major: change API endpoint structure`

<details>
<summary>Risposta</summary>
**b) feat!: change API endpoint structure**

Il punto esclamativo dopo il tipo indica un breaking change nei conventional commits.
</details>

**Domanda 7: Scope nei Conventional Commits**
Quale commit message è più preciso?

a) `feat: add new feature`
b) `feat(auth): add two-factor authentication`
c) `feature: authentication improvements`
d) `add: 2FA support`

<details>
<summary>Risposta</summary>
**b) feat(auth): add two-factor authentication**

Include il tipo corretto, lo scope tra parentesi e una descrizione chiara e specifica.
</details>

## Quiz Pratico

### Scenario 1: Correzione Urgente
Hai fatto un commit con un typo nel codice. Il commit è l'ultimo della cronologia e non è stato ancora condiviso. Scrivi i comandi per:

1. Correggere il file
2. Aggiungere la correzione al commit precedente
3. Verificare che il commit sia stato modificato

<details>
<summary>Soluzione</summary>
```bash
# 1. Correggere il file (con editor)
nano/vim filename.js

# 2. Aggiungere al commit precedente
git add filename.js
git commit --amend --no-edit

# 3. Verificare la modifica
git log --oneline -1
git show HEAD
```
</details>

### Scenario 2: Messaggio Commit Professionale
Hai aggiunto una nuova funzionalità di validazione email al modulo di registrazione utenti. Scrivi 3 versioni del messaggio di commit:

1. Versione base
2. Versione conventional commit
3. Versione conventional commit con scope e dettagli

<details>
<summary>Soluzione</summary>
```bash
# 1. Versione base
git commit -m "Add email validation"

# 2. Versione conventional commit
git commit -m "feat: add email validation to user registration"

# 3. Versione con scope e dettagli
git commit -m "feat(auth): add email validation to user registration

- Add email format validation using regex
- Display error message for invalid emails
- Update registration form with validation feedback
- Add unit tests for email validation logic"
```
</details>

### Scenario 3: Gestione Commit Multipli
Hai fatto 3 commit consecutivi:
- "add file1"
- "add file2" 
- "fix typo in file1"

Vuoi unire il primo e il terzo commit. Quale strategia usi?

<details>
<summary>Soluzione</summary>
**Strategia 1: Reset e ricommit**
```bash
git reset --soft HEAD~3
git add file1 file2
git commit -m "feat: add file1 and file2 with corrections"
```

**Strategia 2: Interactive rebase (più avanzato)**
```bash
git rebase -i HEAD~3
# Seguire le istruzioni per squash/fixup
```

**Strategia 3: Commit separati ma descrittivi**
```bash
git commit --amend -m "feat: add file1 with typo corrections"
# Mantenere commit separati ma con messaggi chiari
```
</details>

## Valutazione

### Criteri di Successo
- **18-21 risposte corrette**: Eccellente comprensione
- **15-17 risposte corrette**: Buona comprensione
- **12-14 risposte corrette**: Comprensione sufficiente
- **< 12 risposte corrette**: Necessario rivedere il materiale

### Punteggio
- Sezione A (teorica): 3 punti x 3 domande = 9 punti
- Sezione B (scenari): 3 punti x 2 domande = 6 punti
- Sezione C (conventional): 3 punti x 2 domande = 6 punti
- Quiz pratico: 3 punti x 3 scenari = 9 punti

**Totale**: 30 punti

## Approfondimenti Consigliati

Se hai avuto difficoltà con alcune domande, rivedi questi argomenti:

### Per punteggi bassi (< 15):
- [Guida 01: Commit Amend](../guide/01-commit-amend.md)
- [Guida 02: Reset vs Revert](../guide/02-reset-vs-revert.md)

### Per migliorare ulteriormente (15-20):
- [Guida 05: Conventional Commits](../guide/05-conventional-commits.md)
- [Esempio 02: Workflow Professionale](../esempi/02-workflow-professionale.md)

### Per perfezionare (> 20):
- [Esercizio 02: Pratica Amend Reset](./02-pratica-amend-reset.md)
- [Esercizio 03: Conventional Commits](./03-conventional-commits.md)

## Note per l'Istruttore

### Obiettivi Didattici
- Verificare comprensione teorica dei commit avanzati
- Testare capacità di applicazione pratica
- Identificare aree che necessitano approfondimento

### Suggerimenti per la Revisione
- Discutere le risposte più comuni agli errori
- Fornire esempi aggiuntivi per concetti complessi
- Incoraggiare discussione su best practices

---
[⬅️ Esempi](../esempi/README.md) | [🏠 Modulo 09](../README.md) | [➡️ Esercizio 02](./02-pratica-amend-reset.md)
