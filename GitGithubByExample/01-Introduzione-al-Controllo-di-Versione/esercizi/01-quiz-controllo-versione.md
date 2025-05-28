# 01 - Quiz Controllo di Versione

## 🧠 Test di Comprensione

Questo quiz ti aiuterà a verificare la comprensione dei concetti fondamentali del controllo di versione. Ogni domanda ha una sola risposta corretta.

## 📝 Domande a Scelta Multipla

### Domanda 1
**Cos'è il controllo di versione?**

A) Un software per scrivere codice più velocemente  
B) Un sistema che registra le modifiche ai file nel tempo  
C) Un programma per aumentare la velocità del computer  
D) Un metodo per organizzare i file in cartelle  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: B**

Il controllo di versione è un sistema che registra le modifiche apportate ai file nel tempo, permettendo di richiamare versioni specifiche in seguito.

**Perché le altre sono sbagliate:**
- A) Non influisce sulla velocità di scrittura del codice
- C) Non è un programma per ottimizzazione del sistema
- D) È molto più di una semplice organizzazione file
</details>

---

### Domanda 2
**Quale di questi NON è un vantaggio del controllo di versione?**

A) Backup automatico delle modifiche  
B) Collaborazione sicura tra sviluppatori  
C) Possibilità di tornare a versioni precedenti  
D) Aumento della velocità di esecuzione del codice  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: D**

Il controllo di versione non influisce sulla velocità di esecuzione del codice - questo dipende dall'ottimizzazione del codice stesso.

**I veri vantaggi sono:**
- A) ✅ Ogni commit è un backup automatico
- B) ✅ Permette a più persone di lavorare sullo stesso progetto
- C) ✅ Comando per recuperare qualsiasi versione precedente
</details>

---

### Domanda 3
**Qual è la principale differenza tra sistemi centralizzati (come SVN) e distribuiti (come Git)?**

A) I sistemi centralizzati sono più veloci  
B) I sistemi distribuiti richiedono sempre una connessione internet  
C) Nei sistemi distribuiti ogni repository è completo e indipendente  
D) I sistemi centralizzati sono più sicuri  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: C**

Nei sistemi distribuiti come Git, ogni repository contiene la cronologia completa del progetto ed è indipendente dal server.

**Confronto:**
- **Centralizzato (SVN)**: Un solo repository centrale, i client hanno solo la versione corrente
- **Distribuito (Git)**: Ogni clone è un repository completo con tutta la storia
</details>

---

### Domanda 4
**In che anno è stato creato Git e da chi?**

A) 2003, da Microsoft  
B) 2005, da Linus Torvalds  
C) 2008, da GitHub  
D) 2010, da Google  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: B**

Git è stato creato nel 2005 da Linus Torvalds (lo stesso creatore di Linux) per gestire lo sviluppo del kernel Linux.

**Timeline importante:**
- 2005: Nasce Git
- 2008: Nasce GitHub (la piattaforma)
- Oggi: Git è lo standard dell'industria
</details>

---

### Domanda 5
**Cosa succederebbe se 3 sviluppatori modificassero lo stesso file contemporaneamente senza controllo di versione?**

A) Il computer si bloccherebbe  
B) Solo il primo che salva mantiene le modifiche, gli altri perdono il lavoro  
C) Le modifiche si unirebbero automaticamente  
D) Verrebbe creato un backup automatico  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: B**

Senza controllo di versione, l'ultimo che salva il file sovrascrive il lavoro degli altri. È esattamente il problema che il VCS risolve!

**Scenario tipico:**
1. Marco modifica `file.js`
2. Laura modifica `file.js` (stessa versione iniziale)
3. Marco salva → file contiene le modifiche di Marco
4. Laura salva → file contiene solo le modifiche di Laura
5. Il lavoro di Marco è perso! 😱
</details>

---

### Domanda 6
**Quali di questi file NON dovrebbero mai essere tracciati da Git?**

A) File di codice sorgente (.js, .html, .css)  
B) File di configurazione (config.json)  
C) Password e chiavi API  
D) Documentazione del progetto  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: C**

Password, chiavi API e dati sensibili NON devono mai essere committati in Git per motivi di sicurezza.

**Best practice:**
- ✅ Traccia: codice, configurazioni (senza segreti), documentazione
- ❌ Non tracciare: password, chiavi API, file temporanei, file generati
- 💡 Usa file `.env` e `.gitignore` per gestire i segreti
</details>

---

### Domanda 7
**Cosa rappresenta un "commit" in Git?**

A) Un backup completo di tutti i file del computer  
B) Una snapshot (istantanea) del progetto in un momento specifico  
C) Un commento sul codice  
D) Un branch del progetto  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: B**

Un commit è una snapshot completa del progetto in un momento specifico, con informazioni su chi, cosa, quando e perché.

**Struttura di un commit:**
```
- Hash univoco (identificatore)
- Autore e data
- Messaggio descrittivo  
- Snapshot completo di tutti i file tracciati
- Riferimento al commit precedente (parent)
```
</details>

---

### Domanda 8
**Qual è il workflow corretto per fare modifiche sicure in Git?**

A) Modificare direttamente sul branch main  
B) Creare un branch, modificare, testare, fare merge  
C) Fare backup manuali prima di ogni modifica  
D) Modificare e sperare che funzioni  

<details>
<summary>💡 Clicca per la risposta</summary>

**Risposta corretta: B**

Il workflow sicuro prevede:
1. `git checkout -b feature/nuova-funzione` (crea branch)
2. Modifiche + testing
3. `git add` e `git commit`
4. `git checkout main` e `git merge`

**Vantaggi:**
- ✅ Branch main sempre stabile
- ✅ Possibilità di abbandonare modifiche senza conseguenze
- ✅ Cronologia pulita e organizzata
</details>

---

## 📊 Valutazione

**Conta le risposte corrette:**

- **8/8**: 🏆 **Esperto!** Hai compreso perfettamente i concetti
- **6-7/8**: 🎯 **Ottimo!** Solo qualche dettaglio da ripassare  
- **4-5/8**: 📚 **Bene!** Rileggi le guide teoriche
- **0-3/8**: 🔄 **Riparti!** Torna alle basi e riprova

## 🔍 Analisi Errori Comuni

### Se hai sbagliato le domande 1-3:
**Focus sui concetti base**
- Rileggi: [01 - Cos'è il Controllo di Versione](../guide/01-controllo-versione.md)
- Rileggi: [02 - Storia e Evoluzione](../guide/02-storia-evoluzione.md)

### Se hai sbagliato le domande 4-6:
**Focus sulla storia e best practices**
- Rileggi: [03 - Git vs Altri Sistemi](../guide/03-git-vs-altri.md)
- Approfondisci la security in Git

### Se hai sbagliato le domande 7-8:
**Focus sui concetti Git specifici**
- Rileggi: [04 - Concetti Fondamentali](../guide/04-concetti-fondamentali.md)
- Prepararti per le esercitazioni pratiche

## 💡 Suggerimenti per Migliorare

### Metodo di Studio Consigliato

1. **Teoria + Pratica**: Non limitarti alla teoria, sperimenta
2. **Esempi reali**: Pensa a situazioni del tuo lavoro/studio
3. **Ripetizione**: I concetti Git diventano naturali con la pratica
4. **Community**: Discuti con altri sviluppatori

### Risorse Extra

- 📖 [Pro Git Book](https://git-scm.com/book) - Gratuito e completo
- 🎮 [Learn Git Branching](https://learngitbranching.js.org/) - Interattivo
- 🎥 [Git & GitHub Tutorial](https://www.youtube.com/watch?v=RGOj5yH7evk) - Video

## ✅ Prossimo Passo

Complimenti per aver completato il quiz! 

Se hai ottenuto un buon punteggio, sei pronto per:

➡️ **[02 - Analisi Scenario](02-analisi-scenario.md)**

Se invece vuoi ripassare:

↩️ **[Guide Teoriche](../guide/)**

---

💪 **Ricorda**: Non c'è fretta! È meglio capire bene i concetti ora che avere confusione nelle esercitazioni pratiche.
