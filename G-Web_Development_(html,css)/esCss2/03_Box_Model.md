# Il Box Model

## Cos'è il Box Model
Descrive la struttura di ogni elemento HTML come un rettangolo composto da content, padding, border e margin.

## Proprietà principali
- `width`, `height`
- `padding`
- `border`
- `margin`
- `box-sizing`

## Esempi
```css
div {
  width: 200px;
  padding: 10px;
  border: 2px solid black;
  margin: 20px;
  box-sizing: border-box;
}
```

## Best Practice
- Usare `box-sizing: border-box` per semplificare il calcolo delle dimensioni.

## Tips and Tricks
- Utilizzare margini automatici per centrare elementi.

## Domande di Autovalutazione
1. Quale proprietà include il bordo nel calcolo della larghezza?
   - A) `box-sizing: content-box`
   - B) `box-sizing: border-box`
   - C) `margin`
   - D) `padding`

2. Cosa rappresenta il padding?
   - A) Spazio tra bordo e margine
   - B) Spazio tra contenuto e bordo
   - C) Spazio esterno all'elemento
   - D) Nessuna delle precedenti

## Esercizi Proposti
1. Crea un box con bordo rosso, padding di 20px e margine di 30px.
2. Centra orizzontalmente un div usando il box model.

### Risposte alle Domande di Autovalutazione
1. B) `box-sizing: border-box`
2. B) Spazio tra contenuto e bordo

---
- [📑 Indice](<../README.md>)
- [⬅️ Selettori e Specificità](<02_Selettori_e_Specificita.md>)
- [➡️ Colori, Sfondi e Immagini](<04_Colori_Sfondi_Immagini.md>)
