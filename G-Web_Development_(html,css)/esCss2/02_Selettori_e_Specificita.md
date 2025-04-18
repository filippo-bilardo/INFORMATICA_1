# Selettori e Specificità

## Selettori di base
- Elemento (`p`)
- Classe (`.classe`)
- ID (`#id`)

## Selettori avanzati
- Discendente, figlio, fratello
- Pseudo-classi e pseudo-elementi

## Specificità
Regole per determinare quale stile viene applicato in caso di conflitto.

## Esempi
```css
p { color: blue; }
#titolo { font-size: 2em; }
.menu li:hover { background: yellow; }
```

## Best Practice
- Evitare l'uso eccessivo di ID nei selettori.
- Preferire classi per la riusabilità.

## Tips and Tricks
- Usare `:not()` per escludere elementi.
- Combinare selettori per maggiore precisione.

## Domande di Autovalutazione
1. Quale selettore ha la specificità più alta?
   - A) `.classe`
   - B) `#id`
   - C) `p`
   - D) `*`

2. Cosa seleziona `ul > li`?
   - A) Tutti i `li` discendenti di `ul`
   - B) Solo i `li` figli diretti di `ul`
   - C) Tutti i `ul` figli di `li`
   - D) Nessuno

## Esercizi Proposti
1. Scrivi un selettore che selezioni tutti i paragrafi con classe "importante".
2. Crea una regola che evidenzi il primo elemento di una lista.

### Risposte alle Domande di Autovalutazione
1. B) `#id`
2. B) Solo i `li` figli diretti di `ul`

---
- [📑 Indice](<../README.md>)
- [⬅️ Introduzione al CSS](<01_Introduzione_al_CSS.md>)
- [➡️ Il Box Model](<03_Box_Model.md>)
