# Esercizio 02: Pratica con Amend e Reset

## Obiettivo
Acquisire esperienza pratica con i comandi `git commit --amend` e `git reset` attraverso scenari realistici di correzione commit.

## Durata Stimata
45-60 minuti

## Setup Iniziale

### Preparazione Repository
```bash
# Creare directory di lavoro
mkdir commit-practice
cd commit-practice

# Inizializzare repository
git init

# Configurazione base (se necessario)
git config user.name "Your Name"
git config user.email "your.email@example.com"

# Creare file iniziale
echo "# Progetto di Pratica Commit" > README.md
echo "Questo è un progetto per praticare commit avanzati." >> README.md
git add README.md
git commit -m "init: create project README"
```

## Parte 1: Pratica con Git Commit --amend

### Scenario 1.1: Correzione Messaggio Commit
**Situazione**: Hai fatto un commit con un messaggio poco chiaro.

```bash
# Creare un file con un "bug"
echo "function calculateTotal() {" > calculator.js
echo "  return price * quantity;" >> calculator.js
echo "}" >> calculator.js

git add calculator.js
git commit -m "add function"
```

**Compito**: Modifica il messaggio per seguire le best practices.

<details>
<summary>📋 Soluzione</summary>

```bash
# Modificare il messaggio dell'ultimo commit
git commit --amend -m "feat(calc): add calculateTotal function

- Implement basic price calculation
- Accept price and quantity parameters
- Return total cost calculation"

# Verificare la modifica
git log --oneline -1
```
</details>

### Scenario 1.2: Aggiungere File Dimenticato
**Situazione**: Hai fatto un commit ma hai dimenticato di includere un file importante.

```bash
# Creare file test correlato
echo "// Test per calculator.js" > calculator.test.js
echo "describe('calculateTotal', () => {" >> calculator.test.js
echo "  // TODO: implementare test" >> calculator.test.js
echo "});" >> calculator.test.js

# Il file test doveva essere incluso nel commit precedente
```

**Compito**: Aggiungi il file test al commit precedente.

<details>
<summary>📋 Soluzione</summary>

```bash
# Aggiungere il file mancante
git add calculator.test.js

# Amend per includere nel commit precedente
git commit --amend --no-edit

# Verificare che entrambi i file siano nel commit
git show --name-only HEAD
```
</details>

### Scenario 1.3: Correzione Contenuto e Messaggio
**Situazione**: Il commit precedente ha sia un errore nel codice che nel messaggio.

```bash
# Simulare un errore nel codice (correggere il file esistente)
echo "function calculateTotal(price, quantity) {" > calculator.js
echo "  // Fix: aggiunta validazione parametri" >> calculator.js
echo "  if (price < 0 || quantity < 0) return 0;" >> calculator.js
echo "  return price * quantity;" >> calculator.js
echo "}" >> calculator.js
```

**Compito**: Correggi il codice e migliora il messaggio del commit.

<details>
<summary>📋 Soluzione</summary>

```bash
# Aggiungere le correzioni
git add calculator.js

# Amend con nuovo messaggio
git commit --amend -m "feat(calc): add calculateTotal function with validation

- Implement basic price calculation
- Add parameter validation for negative values
- Accept price and quantity parameters
- Return total cost calculation
- Include comprehensive test file"

# Verificare le modifiche
git show HEAD
```
</details>

## Parte 2: Pratica con Git Reset

### Scenario 2.1: Reset Soft (Mantenere Modifiche)
**Situazione**: Hai fatto 3 commit consecutivi che vuoi unire in uno solo.

```bash
# Creare 3 commit separati
echo "const TAX_RATE = 0.1;" > config.js
git add config.js
git commit -m "add tax rate"

echo "const DISCOUNT_RATE = 0.05;" >> config.js
git add config.js
git commit -m "add discount rate"

echo "const SHIPPING_COST = 5.99;" >> config.js
git add config.js
git commit -m "add shipping cost"
```

**Compito**: Usa reset soft per unire i 3 commit in uno solo.

<details>
<summary>📋 Soluzione</summary>

```bash
# Reset soft per mantenere le modifiche ma rimuovere i commit
git reset --soft HEAD~3

# Verificare che le modifiche siano in staging
git status

# Creare un nuovo commit unificato
git commit -m "feat(config): add pricing configuration constants

- Add TAX_RATE constant (10%)
- Add DISCOUNT_RATE constant (5%)
- Add SHIPPING_COST constant ($5.99)
- Centralize pricing configuration"

# Verificare il risultato
git log --oneline -5
```
</details>

### Scenario 2.2: Reset Mixed (Default)
**Situazione**: Hai aggiunto file all'area di staging ma vuoi riorganizzarli.

```bash
# Creare diversi file
echo "User authentication logic" > auth.js
echo "Database connection logic" > database.js
echo "Email sending logic" > email.js

# Aggiungere tutti insieme
git add .
```

**Compito**: Usa reset per rimuovere tutto dallo staging e poi aggiungi in modo selettivo.

<details>
<summary>📋 Soluzione</summary>

```bash
# Reset mixed per rimuovere tutto dallo staging
git reset

# Verificare stato
git status

# Aggiungere in modo selettivo per commit logici
git add auth.js
git commit -m "feat(auth): add user authentication module"

git add database.js
git commit -m "feat(db): add database connection module"

git add email.js
git commit -m "feat(email): add email sending module"

# Verificare la cronologia
git log --oneline -5
```
</details>

### Scenario 2.3: Reset Hard (Attenzione!)
**Situazione**: Hai fatto modifiche che vuoi completamente eliminare.

```bash
# Creare modifiche indesiderate
echo "// Codice temporaneo da rimuovere" >> calculator.js
echo "console.log('DEBUG: temporary code');" >> calculator.js

# Aggiungerle per errore
git add calculator.js
git commit -m "temp: debug code"
```

**Compito**: Usa reset hard per eliminare completamente l'ultimo commit.

<details>
<summary>📋 Soluzione</summary>

```bash
# ATTENZIONE: Salvare una copia se necessario
git log --oneline -2  # Vedere cosa stiamo eliminando

# Reset hard per eliminare commit e modifiche
git reset --hard HEAD~1

# Verificare che le modifiche siano scomparse
git log --oneline -5
cat calculator.js  # Dovrebbe essere tornato alla versione precedente
```
</details>

## Parte 3: Scenari Avanzati

### Scenario 3.1: Combinazione Amend e Reset
**Situazione**: Commit complesso che necessita riorganizzazione.

```bash
# Creare una situazione complessa
echo "// Utility functions" > utils.js
echo "export function formatPrice(price) {" >> utils.js
echo "  return '$' + price.toFixed(2);" >> utils.js
echo "}" >> utils.js

git add utils.js
git commit -m "add utils"

# Aggiungere più funzioni
echo "" >> utils.js
echo "export function formatDate(date) {" >> utils.js
echo "  return date.toLocaleDateString();" >> utils.js
echo "}" >> utils.js

git add utils.js
git commit -m "add more utils"
```

**Compito**: Unisci i commit e migliora il messaggio.

<details>
<summary>📋 Soluzione</summary>

```bash
# Approccio 1: Reset e ricommit
git reset --soft HEAD~2
git commit -m "feat(utils): add utility functions module

- Add formatPrice function for currency formatting
- Add formatDate function for date formatting
- Export functions for external use"

# Approccio 2: Amend iterativo (alternativo)
# git reset --soft HEAD~1
# git commit --amend -m "miglior messaggio per secondo commit"
# git rebase -i HEAD~2  # Per unire (avanzato)
```
</details>

### Scenario 3.2: Recupero da Reset Accidentale
**Situazione**: Hai fatto un reset hard per errore.

```bash
# Creare contenuto importante
echo "// Importante: non eliminare!" > important.js
echo "const CRITICAL_CONFIG = 'important value';" >> important.js
git add important.js
git commit -m "feat: add critical configuration"

# Simulare reset accidentale
git reset --hard HEAD~1
```

**Compito**: Recupera il commit "perso".

<details>
<summary>📋 Soluzione</summary>

```bash
# Trovare il commit perso con reflog
git reflog

# Identificare l'hash del commit perso (sarà simile a qualcosa come 'HEAD@{1}')
# Recuperare il commit
git cherry-pick <hash-del-commit-perso>

# Oppure reset al commit perso
git reset --hard <hash-del-commit-perso>

# Verificare il recupero
git log --oneline -3
ls -la  # Verificare che important.js sia tornato
```
</details>

## Verifica e Test

### Checklist Completamento
- [ ] Hai completato tutti i 6 scenari principali
- [ ] Hai compreso la differenza tra `--soft`, `--mixed`, e `--hard`
- [ ] Sai quando usare `--amend` vs `reset`
- [ ] Hai praticato il recupero da errori
- [ ] Hai verificato ogni operazione con `git log` e `git status`

### Comandi di Verifica Finale
```bash
# Verificare la cronologia finale
git log --oneline --graph -10

# Verificare stato attuale
git status

# Verificare contenuto file principali
ls -la
cat calculator.js
cat utils.js
```

## Domande di Riflessione

1. **Quando preferiresti `--amend` rispetto a `reset --soft`?**
2. **Quali sono i rischi dell'uso di `reset --hard`?**
3. **Come verificheresti sempre le tue operazioni prima di eseguirle?**
4. **Quando è appropriato modificare la cronologia Git?**

## Risorse per Approfondimento

- [Guida 01: Commit Amend](../guide/01-commit-amend.md)
- [Guida 02: Reset vs Revert](../guide/02-reset-vs-revert.md)
- [Esempio 01: Correzione Errori](../esempi/01-correzione-errori.md)

## Troubleshooting Comune

### Se il comando amend non funziona:
```bash
git status  # Verificare stato
git log --oneline -3  # Verificare cronologia
```

### Se reset sembra non funzionare:
```bash
git reflog  # Vedere cronologia completa
git status  # Verificare working directory
```

### Per annullare un'operazione:
```bash
git reflog  # Trovare stato precedente
git reset --hard HEAD@{n}  # Tornare indietro
```

---
[⬅️ Esercizio 01](./01-quiz-commit.md) | [🏠 Modulo 09](../README.md) | [➡️ Esercizio 03](./03-conventional-commits.md)
