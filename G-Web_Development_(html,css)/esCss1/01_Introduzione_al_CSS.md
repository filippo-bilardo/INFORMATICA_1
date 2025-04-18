# Introduzione al CSS

## Indice dei contenuti

- [Storia e evoluzione del CSS](#storia-e-evoluzione-del-css)
  - [Le origini](#le-origini)
  - [L'era moderna](#lera-moderna)
  - [Tendenze attuali](#tendenze-attuali)
- [Come collegare CSS a HTML](#come-collegare-css-a-html)
  - [1. CSS Inline](#1-css-inline)
  - [2. CSS Interno (Internal)](#2-css-interno-internal)
  - [3. CSS Esterno (External)](#3-css-esterno-external)
- [Sintassi di base e regole](#sintassi-di-base-e-regole)
  - [Struttura di base](#struttura-di-base)
  - [Componenti di una regola CSS](#componenti-di-una-regola-css)
  - [Esempi di regole CSS](#esempi-di-regole-css)
  - [Tipi di selettori di base](#tipi-di-selettori-di-base)
- [Commenti e organizzazione del codice](#commenti-e-organizzazione-del-codice)
  - [Commenti in CSS](#commenti-in-css)
  - [Organizzazione del codice CSS](#organizzazione-del-codice-css)
- [Domande di autovalutazione](#domande-di-autovalutazione)
- [Esercizi pratici](#esercizi-pratici)
- [Risorse aggiuntive](#risorse-aggiuntive)

## Storia e evoluzione del CSS

Il CSS (Cascading Style Sheets) è nato dalla necessità di separare il contenuto dalla presentazione nelle pagine web. Ecco le tappe fondamentali della sua evoluzione:

### Le origini
- **1994**: Håkon Wium Lie propone il concetto di CSS mentre lavorava al CERN.
- **1996**: Viene pubblicata la prima specifica ufficiale, CSS1, dal W3C (World Wide Web Consortium).
- **1998**: CSS2 introduce posizionamento, z-index, media types e supporto per fogli di stile specifici.

### L'era moderna
- **CSS2.1** (2011): Correzione di errori e standardizzazione delle implementazioni.
- **CSS3**: Suddiviso in moduli indipendenti che possono evolversi separatamente:
  - Selettori
  - Box Model
  - Backgrounds and Borders
  - Text Effects
  - Animations
  - Flexbox
  - Grid

### Tendenze attuali
- **CSS Custom Properties** (variabili CSS)
- **CSS Grid Layout** per layout bidimensionali complessi
- **CSS Flexbox** per layout unidimensionali flessibili
- **CSS Animations e Transitions** per effetti dinamici
- **Media Queries** per design responsive

> **Suggerimento**: Conoscere l'evoluzione del CSS aiuta a comprendere perché alcune proprietà hanno prefissi specifici per browser (come `-webkit-`, `-moz-`) e perché esistono diverse tecniche per ottenere lo stesso risultato visivo.

## Come collegare CSS a HTML

Esistono tre metodi principali per applicare stili CSS a un documento HTML:

### 1. CSS Inline
Gli stili vengono applicati direttamente agli elementi HTML utilizzando l'attributo `style`.

```html
<p style="color: blue; font-size: 16px;">Questo è un paragrafo con stile inline.</p>
```

**Vantaggi**:
- Priorità massima nella cascata
- Utile per override puntuali
- Non richiede file aggiuntivi

**Svantaggi**:
- Difficile da mantenere
- Mescola contenuto e presentazione
- Non riutilizzabile

### 2. CSS Interno (Internal)
Gli stili vengono definiti all'interno del documento HTML utilizzando il tag `<style>` nella sezione `<head>`.

```html
<!DOCTYPE html>
<html>
<head>
  <style>
    p {
      color: blue;
      font-size: 16px;
    }
    .highlight {
      background-color: yellow;
    }
  </style>
</head>
<body>
  <p>Questo è un paragrafo blu.</p>
  <p class="highlight">Questo è un paragrafo evidenziato.</p>
</body>
</html>
```

**Vantaggi**:
- Non richiede file aggiuntivi
- Stili riutilizzabili all'interno della stessa pagina

**Svantaggi**:
- Non condivisibile tra pagine diverse
- Aumenta la dimensione del documento HTML

### 3. CSS Esterno (External)
Gli stili vengono definiti in un file separato con estensione `.css` e collegati al documento HTML utilizzando il tag `<link>` o la regola `@import`.

**Utilizzo con tag `<link>`**:
```html
<!DOCTYPE html>
<html>
<head>
  <link rel="stylesheet" href="styles.css">
</head>
<body>
  <p>Questo è un paragrafo stilizzato dal file esterno.</p>
</body>
</html>
```

**Utilizzo con `@import`** (all'interno di un altro foglio di stile o in un tag `<style>`):
```html
<style>
  @import url('styles.css');
  /* Altri stili */
</style>
```

Contenuto di `styles.css`:
```css
p {
  color: blue;
  font-size: 16px;
}
.highlight {
  background-color: yellow;
}
```

**Vantaggi**:
- Separazione completa tra contenuto e presentazione
- Riutilizzabile su più pagine
- Facilita la manutenzione
- Riduce il peso delle pagine HTML
- Permette la memorizzazione nella cache del browser

**Svantaggi**:
- Richiede una richiesta HTTP aggiuntiva (mitigabile con HTTP/2)

> **Best Practice**: Il CSS esterno è generalmente il metodo preferito per progetti di qualsiasi dimensione. Usa CSS inline solo per override specifici o stili dinamici generati da JavaScript.

## Sintassi di base e regole

La sintassi CSS è composta da selettori e dichiarazioni che definiscono come gli elementi HTML devono essere visualizzati.

### Struttura di base

```css
selettore {
  proprietà: valore;
  altra-proprietà: altro-valore;
}
```

### Componenti di una regola CSS

1. **Selettore**: Indica a quale elemento HTML si applica lo stile
2. **Blocco di dichiarazione**: Racchiuso tra parentesi graffe `{}`
3. **Dichiarazioni**: Coppie proprietà-valore separate da punto e virgola `;`
4. **Proprietà**: Aspetto che si desidera modificare
5. **Valore**: Specifica come modificare la proprietà

### Esempi di regole CSS

```css
/* Stile per tutti i paragrafi */
p {
  color: #333333;
  font-size: 16px;
  line-height: 1.5;
}

/* Stile per elementi con classe 'button' */
.button {
  background-color: #4CAF50;
  color: white;
  padding: 10px 15px;
  border: none;
  border-radius: 4px;
}

/* Stile per elemento con ID 'header' */
#header {
  background-color: #f1f1f1;
  padding: 20px;
  text-align: center;
}
```

### Tipi di selettori di base

- **Selettore di elemento**: Seleziona tutti gli elementi di un tipo specifico
  ```css
  p { color: blue; }
  ```

- **Selettore di classe**: Seleziona elementi con una specifica classe
  ```css
  .button { background-color: green; }
  ```

- **Selettore di ID**: Seleziona un elemento con uno specifico ID
  ```css
  #header { height: 100px; }
  ```

- **Selettore universale**: Seleziona tutti gli elementi
  ```css
  * { margin: 0; padding: 0; }
  ```

- **Selettore di attributo**: Seleziona elementi con un attributo specifico
  ```css
  input[type="text"] { border: 1px solid gray; }
  ```

> **Suggerimento**: Mantieni le regole CSS semplici e specifiche. Troppi selettori annidati possono rendere il codice difficile da mantenere e possono causare problemi di specificità.

## Commenti e organizzazione del codice

Un CSS ben organizzato e commentato è più facile da mantenere e comprendere, sia per te che per altri sviluppatori.

### Commenti in CSS

I commenti in CSS sono racchiusi tra `/*` e `*/` e possono estendersi su più righe.

```css
/* Questo è un commento CSS */

/*
 Questo è un commento
 su più righe
 */

p { color: blue; } /* Commento inline */
```

### Organizzazione del codice CSS

#### 1. Raggruppamento logico

Organizza il CSS in sezioni logiche:

```css
/* ==========================================================================
   RESET
   ========================================================================== */
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

/* ==========================================================================
   TIPOGRAFIA
   ========================================================================== */
body {
  font-family: Arial, sans-serif;
  line-height: 1.6;
}

h1, h2, h3 {
  font-weight: bold;
}

/* ==========================================================================
   LAYOUT
   ========================================================================== */
.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 0 15px;
}

/* ==========================================================================
   COMPONENTI
   ========================================================================== */
.button {
  display: inline-block;
  padding: 10px 15px;
  background-color: #4CAF50;
  color: white;
  text-decoration: none;
  border-radius: 4px;
}
```

#### 2. Convenzioni di denominazione

Utilizza convenzioni di denominazione coerenti per classi e ID. Alcune metodologie popolari includono:

- **BEM (Block Element Modifier)**:
  ```css
  .block {}
  .block__element {}
  .block--modifier {}
  ```

- **SMACSS (Scalable and Modular Architecture for CSS)**:
  ```css
  /* Base */
  body, p, h1 {}
  
  /* Layout */
  .l-header, .l-sidebar {}
  
  /* Module */
  .btn, .card {}
  
  /* State */
  .is-active, .is-hidden {}
  ```

#### 3. Indentazione e formattazione

Mantieni uno stile di formattazione coerente:

```css
/* Stile su una riga per regole semplici */
.simple { display: block; margin: 0; }

/* Stile multi-riga per regole complesse */
.complex {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  padding: 20px;
  background-color: #f5f5f5;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}
```

#### 4. Uso di variabili CSS

Utilizza le variabili CSS (custom properties) per valori riutilizzabili:

```css
:root {
  --primary-color: #4CAF50;
  --secondary-color: #2196F3;
  --text-color: #333;
  --spacing-unit: 8px;
  --font-family: Arial, sans-serif;
}

.button {
  background-color: var(--primary-color);
  color: white;
  padding: calc(var(--spacing-unit) * 2);
  font-family: var(--font-family);
}
```

> **Best Practice**: Commenta il tuo CSS per spiegare il "perché" dietro determinate scelte di stile, non solo il "cosa". Questo è particolarmente utile per hack o soluzioni non intuitive.

---

## Domande di autovalutazione

1. Quali sono i tre modi principali per collegare CSS a HTML? Quali sono i vantaggi e gli svantaggi di ciascuno?
2. Spiega la differenza tra selettori di classe, ID ed elemento in CSS.
3. Perché è importante organizzare il codice CSS? Descrivi almeno due metodologie di organizzazione.
4. Come si è evoluto il CSS nel tempo e quali sono le principali caratteristiche introdotte con CSS3?
5. Scrivi una regola CSS che applichi un colore di sfondo rosso a tutti gli elementi con classe "error" e un bordo nero di 1px.

## Esercizi pratici

1. **Esercizio base**: Crea una pagina HTML con tre paragrafi e applica stili diversi utilizzando i tre metodi di collegamento CSS (inline, interno ed esterno).

2. **Esercizio intermedio**: Crea un pulsante stilizzato utilizzando CSS. Il pulsante deve cambiare aspetto quando si passa sopra con il mouse (hover).

3. **Esercizio avanzato**: Organizza un foglio di stile per un sito web semplice seguendo una delle metodologie di organizzazione CSS discusse (BEM o SMACSS). Il sito dovrebbe includere un'intestazione, una barra laterale, un contenuto principale e un piè di pagina.

## Risorse aggiuntive

- [MDN Web Docs: CSS](https://developer.mozilla.org/it/docs/Web/CSS)
- [CSS-Tricks](https://css-tricks.com/)
- [W3C CSS Validation Service](https://jigsaw.w3.org/css-validator/)
- [Can I Use](https://caniuse.com/) - Per verificare il supporto delle funzionalità CSS nei browser

---

- [📑 Indice](README.md)
- [➡️ Selettori e Specificità](02_Selettori_e_Specificita.md)