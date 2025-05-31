# 02 - Analisi Scenario

## 🎯 Obiettivo dell'Esercizio

Questo esercizio ti aiuterà a sviluppare il **pensiero critico** nell'analizzare situazioni reali e identificare quando e come il controllo di versione può risolvere problemi specifici.

## 📖 Istruzioni

Per ogni scenario presentato, dovrai:

1. **Identificare i problemi** causati dalla mancanza di controllo versione
2. **Proporre soluzioni** usando Git
3. **Valutare i benefici** dell'implementazione

> 💡 **Suggerimento**: Non ci sono risposte "perfette" - l'importante è il ragionamento!

---

## 🏢 Scenario 1: Startup E-commerce

### Situazione
**TechShop** è una startup con 4 sviluppatori che stanno costruendo un e-commerce. Attualmente usano una cartella condivisa su Google Drive per sincronizzare il codice.

**Team:**
- Alex (Frontend - React)
- Sara (Backend - Node.js)  
- Luigi (Mobile - React Native)
- Maria (DevOps - Deploy e server)

**Problemi attuali:**
- Ogni sviluppatore ha la sua cartella "version_X"
- Le modifiche vengono condivise tramite zip via Slack
- Spesso il codice di uno sviluppatore non funziona con quello di un altro
- Nessuno sa quale sia la "versione di produzione" corrente
- Il deploy è manuale e spesso rompe il sito

### 🤔 Le Tue Analisi

#### Domanda 1.1: Problemi Identificati
Elenca almeno 5 problemi specifici causati dal loro approccio attuale:

```
1. ________________________________
2. ________________________________  
3. ________________________________
4. ________________________________
5. ________________________________
```

<details>
<summary>💡 Esempio di risposta</summary>

**Possibili problemi:**
1. **Sincronizzazione caotica** - zip via Slack non è scalabile
2. **Conflitti nascosti** - modifiche sovrascritte senza accorgersene
3. **Nessun backup sistematico** - perdita di lavoro se si cancella per errore
4. **Impossibile tornare indietro** - se una versione non funziona, panico
5. **Deploy incontrollato** - non si sa quale codice è in produzione
6. **Collaborazione inefficiente** - tempo perso in sync manuali
7. **Nessuna cronologia** - impossibile vedere chi ha fatto cosa e quando
</details>

#### Domanda 1.2: Workflow Git Proposto
Progetta un workflow Git per TechShop. Considera:

```
Branch Strategy:
- Branch principale: ________________
- Branch per features: ______________
- Branch per hotfix: ________________

Processo di sviluppo:
1. _________________________________
2. _________________________________
3. _________________________________
4. _________________________________
5. _________________________________

Deploy process:
- Development: ______________________
- Staging: __________________________
- Production: _______________________
```

<details>
<summary>💡 Esempio di soluzione</summary>

**Branch Strategy:**
- Branch principale: `main` (sempre deployabile)
- Branch per features: `feature/nome-feature`
- Branch per hotfix: `hotfix/bug-critico`

**Processo di sviluppo:**
1. `git checkout -b feature/carrello-shopping` (Alex crea feature)
2. Sviluppo + commit frequenti con messaggi descrittivi
3. `git push origin feature/carrello-shopping`
4. Pull Request per code review (team controlla)
5. Merge su `main` dopo approvazione

**Deploy process:**
- Development: Auto-deploy da branch `feature/*` su env di test
- Staging: Auto-deploy da `main` per testing finale
- Production: Deploy manuale/automatico da tag (es. `v1.2.3`)
</details>

#### Domanda 1.3: Benefici Attesi
Calcola i benefici dell'implementazione Git:

```
Tempo risparmiato settimanalmente:
- Sincronizzazione manuale: _____ ore → _____ ore
- Risoluzione conflitti: _____ ore → _____ ore  
- Ricerca versioni: _____ ore → _____ ore
- Deploy e rollback: _____ ore → _____ ore

TOTALE: _____ ore/settimana risparmiate

Benefici qualitativi:
1. _________________________________
2. _________________________________
3. _________________________________
```

---

## 🎓 Scenario 2: Università - Progetto di Gruppo

### Situazione
**Progetto "Sistema Biblioteca"** - 6 studenti di Informatica devono consegnare un progetto finale entro 8 settimane.

**Team:**
- Marco e Anna (Database - MySQL)
- Laura e Davide (Frontend - Vue.js)
- Roberto e Chiara (Backend - Python Flask)

**Approccio attuale:**
- Condivisione tramite WhatsApp e email
- Ognuno lavora nella sua cartella locale
- Integration ogni venerdì in presenza (spesso caotica)
- Backup su USB di Marco (unico)

**Problemi emersi:**
- Week 3: Roberto cancella per errore tutto il backend
- Week 5: Database di Marco incompatibile con frontend di Laura
- Week 6: Due versioni diverse del progetto, nessuno sa quale è corretta
- Week 7: Panico totale - USB di Marco si corrompe

### 🤔 Le Tue Analisi

#### Domanda 2.1: Disaster Recovery
Roberto ha cancellato tutto il backend. Con Git, come si risolverebbe?

```
Scenario senza Git:
Azione: _________________________________
Tempo per risolvere: ____________________
Lavoro perso: ___________________________

Scenario con Git:
Comando: ________________________________
Tempo per risolvere: ____________________
Lavoro perso: ___________________________
```

<details>
<summary>💡 Risposta</summary>

**Senza Git:**
- Azione: Chiedere a tutti se hanno backup, ricostruire da zero o da vecchie versioni
- Tempo: 2-3 giorni
- Lavoro perso: Tutto il lavoro recente di Roberto

**Con Git:**
- Comando: `git checkout HEAD~1` o `git revert commit-hash` 
- Tempo: 30 secondi
- Lavoro perso: Zero (tutto è nella cronologia)
</details>

#### Domanda 2.2: Integration Strategy
Progetta la strategia di integrazione settimanale:

```
Processo attuale (caotico):
1. _________________________________
2. _________________________________
3. _________________________________

Processo con Git (organizzato):
1. _________________________________
2. _________________________________  
3. _________________________________
4. _________________________________
5. _________________________________
```

#### Domanda 2.3: Collaboration Plan
Come organizzeresti la collaborazione tra i sottogruppi?

```
Database Team (Marco + Anna):
- Repository: ___________________________
- Branch strategy: ______________________
- Sync con altri team: ___________________

Frontend Team (Laura + Davide):  
- Dependency: ___________________________
- Testing: ______________________________
- Integration: __________________________

Backend Team (Roberto + Chiara):
- API versioning: _______________________
- Documentation: ________________________
- Deployment: ___________________________
```

---

## 🏥 Scenario 3: Settore Medico - App Salute

### Situazione
**MedApp** sviluppa un'app per monitoraggio pazienti. Il settore medico ha requisiti stricti di **compliance** e **auditabilità**.

**Requisiti specifici:**
- Tracciabilità completa di ogni modifica al codice
- Possibilità di dimostrare chi ha modificato cosa e quando
- Capacità di tornare a versioni certificate precedenti
- Audit trail per regolamentazioni FDA/EU

**Team:**
- 8 sviluppatori senior
- 3 team di testing  
- 2 compliance officer
- 1 security auditor

### 🤔 Le Tue Analisi

#### Domanda 3.1: Compliance Requirements
Come Git supporta i requisiti di compliance?

```
Tracciabilità:
Git feature: ____________________________
Beneficio: ______________________________

Auditabilità:  
Git feature: ____________________________
Beneficio: ______________________________

Immutabilità:
Git feature: ____________________________
Beneficio: ______________________________

Signing (firma digitale):
Git feature: ____________________________
Beneficio: ______________________________
```

<details>
<summary>💡 Risposta</summary>

**Tracciabilità:**
- Git feature: Ogni commit ha hash SHA-1, autore, data, messaggio
- Beneficio: Storia completa e immodificabile

**Auditabilità:**
- Git feature: `git log`, `git blame`, `git show`
- Beneficio: Report dettagliati per auditor

**Immutabilità:**
- Git feature: Hash crittografici, modifica = nuovo hash
- Beneficio: Impossibile alterare cronologia senza detection

**Signing:**
- Git feature: `git commit -S` (GPG signatures)
- Beneficio: Prove crittografiche di autenticità
</details>

#### Domanda 3.2: Audit Report
Crea un template per report di audit usando comandi Git:

```
MEDICAL APP AUDIT REPORT
========================

1. Modifiche nel periodo [DATA-DA] - [DATA-A]:
   Comando: _________________________________

2. Sviluppatori attivi nel periodo:
   Comando: _________________________________

3. File critici modificati:
   Comando: _________________________________
   
4. Verifiche integrità:
   Comando: _________________________________

5. Rollback disponibili:
   Comando: _________________________________
```

---

## 🎮 Scenario 4: Gaming Studio - Asset Grandi

### Situazione
**PixelGames** sviluppa un gioco AAA con asset enormi:
- Modelli 3D: 500MB-2GB ciascuno
- Texture 4K: 100-500MB
- Video cutscene: 1-5GB
- Audio non compresso: 50-200MB

**Problema Git standard:**
- Repository diventa gigantesco (50GB+)
- Clone iniziale richiede ore
- Ogni commit è lento
- Bandwidth problematico per team remoto

### 🤔 Le Tue Analisi

#### Domanda 4.1: Problemi Specifici
Identifica i problemi di Git con file grandi:

```
Performance:
Problema: _______________________________
Causa: __________________________________

Storage:  
Problema: _______________________________
Causa: __________________________________

Bandwidth:
Problema: _______________________________  
Causa: __________________________________

Workflow:
Problema: _______________________________
Causa: __________________________________
```

#### Domanda 4.2: Soluzioni Alternative
Ricerca e proponi soluzioni:

```
Git LFS (Large File Storage):
Come funziona: __________________________
Pro: ____________________________________
Contro: _________________________________

Perforce:
Come funziona: __________________________  
Pro: ____________________________________
Contro: _________________________________

Git + Cloud Storage:
Come funziona: __________________________
Pro: ____________________________________
Contro: _________________________________

Soluzione ibrida:
Descrizione: ____________________________
Implementazione: ________________________
```

---

## 📊 Valutazione Finale

### Calcola il Tuo Punteggio

Per ogni scenario completato:
- **Analisi completa**: 25 punti
- **Analisi parziale**: 15 punti  
- **Solo identificazione problemi**: 10 punti

**Punteggio totale: ___/100**

### Interpretazione

- **90-100**: 🏆 **Analyst Expert** - Hai un'ottima comprensione strategica
- **75-89**: 🎯 **Strategic Thinker** - Molto buona analisi dei problemi
- **60-74**: 📚 **Problem Solver** - Buona identificazione, migliorabile nelle soluzioni
- **<60**: 🔄 **Ripassa i Concetti** - Torna alle guide teoriche

## 🚀 Prossimi Passi

### Se hai ottenuto un buon punteggio:
Sei pronto per le esercitazioni pratiche!

➡️ **[02-Installazione-e-Configurazione-Git](../../02-Installazione-e-Configurazione-Git/)**

### Se vuoi migliorare:
- Rileggi gli esempi pratici
- Studia casi reali di implementazione Git
- Discuti con colleghi/compagni le loro esperienze

### Risorse per Approfondire:
- [Git Case Studies](https://git-scm.com/about)
- [GitHub Stories](https://github.com/about/stories)
- [Atlassian Git Workflows](https://www.atlassian.com/git/tutorials/comparing-workflows)

---

💡 **Ricorda**: L'obiettivo non è la perfezione, ma sviluppare la capacità di **pensare in termini di controllo versione** per risolvere problemi reali!
