## Progetto Battaglia Navale

Questo progetto è un'implementazione graduale del gioco "Battaglia Navale" in linguaggio C, divisa in 5 step incrementali.

## Descrizione

Il progetto è stato sviluppato come esercizio didattico per il corso di Informatica 1, con l'obiettivo di mettere in pratica concetti fondamentali come:
- Utilizzo di matrici bidimensionali
- Funzioni
- Controllo di flusso
- Generazione di numeri casuali
- Interazione con l'utente
- Colorazione del testo in console (ANSI)

### Specifiche del Gioco

1. **Campo di Gioco**: Matrice 5x5 dove posizionare una nave e tenere traccia dei colpi.
2. **Rappresentazione**:
   - `~` rappresenta il mare (acqua non colpita)
   - `O` rappresenta un colpo in acqua (mancato)
   - `X` rappresenta un colpo sulla nave (colpito)
   - `#` rappresenta una parte di nave (visibile solo durante l'inizializzazione)

3. **Nave**: Una nave occupa 3 caselle consecutive, disposte orizzontalmente o verticalmente.

4. **Svolgimento del gioco**:
   - Il programma posiziona casualmente una nave di 3 caselle
   - Il giocatore inserisce le coordinate dove sparare (riga e colonna)
   - Il programma comunica se il colpo è andato a segno o meno
   - Il gioco continua finché tutte le parti della nave non sono state colpite

### Concetti chiave da applicare

- Manipolazione di array bidimensionali
- Generazione di numeri casuali
- Controllo di input utente
- Logica di gioco
- Visualizzazione di dati strutturati

## File di esercizio per gli studenti

Questi sono i file template per gli esercizi. Contengono solo i prototipi delle funzioni e i commenti, senza implementazione:

1. [Step 1: Inizializzazione e visualizzazione del campo](/home/git-projects/INFORMATICA_1_MY/F-Strutture_dati/batt_nav/es_battaglia_navale_step1.c)
2. [Step 2: Posizionamento casuale della nave](/home/git-projects/INFORMATICA_1_MY/F-Strutture_dati/batt_nav/es_battaglia_navale_step2.c)
3. [Step 3: Implementazione del meccanismo di sparo](/home/git-projects/INFORMATICA_1_MY/F-Strutture_dati/batt_nav/es_battaglia_navale_step3.c)
4. [Step 4: Completamento del gioco](/home/git-projects/INFORMATICA_1_MY/F-Strutture_dati/batt_nav/es_battaglia_navale_step4.c)
5. [Step 5: Aggiunta di colori](/home/git-projects/INFORMATICA_1_MY/F-Strutture_dati/batt_nav/es_battaglia_navale_step5.c)


## Come usare questi esercizi
Implementare le funzioni indicate nei commenti

### Esercizi aggiuntivi proposti

1. **Modifica Base**: Aggiungi un contatore dei tentativi e mostra al giocatore quanti colpi ha impiegato per affondare la nave.

2. **Difficoltà Media**: Aggiungi più navi di diverse dimensioni e tieni traccia di quante navi rimangono da affondare.

3. **Avanzato**: Implementa una modalità a due giocatori dove ciascuno posiziona le proprie navi e tenta di colpire quelle dell'avversario.

4. **Extra**: Aggiungi la possibilità di ruotare le navi durante il posizionamento e visualizza il campo con coordinate alfanumeriche (A-E per le colonne).

