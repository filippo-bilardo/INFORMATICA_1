# D. Soluzioni agli esercizi

## Esercizi sui fondamenti di HTML5

Questa sezione presenta le soluzioni agli esercizi relativi ai fondamenti di HTML5, fornendo esempi pratici di implementazione corretta degli elementi base e delle buone pratiche di codifica.

### Soluzione: Struttura base di una pagina HTML5

Esercizio: Creare la struttura base di una pagina HTML5 con titolo, meta tag appropriati e un contenuto minimo.

```html
<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>La mia prima pagina HTML5</title>
  <meta name="description" content="Una semplice pagina HTML5 di esempio">
  <link rel="stylesheet" href="stile.css">
</head>
<body>
  <header>
    <h1>Benvenuti nella mia pagina</h1>
    <nav>
      <ul>
        <li><a href="#">Home</a></li>
        <li><a href="#">Chi sono</a></li>
        <li><a href="#">Contatti</a></li>
      </ul>
    </nav>
  </header>
  
  <main>
    <section>
      <h2>Chi sono</h2>
      <p>Questa è una sezione che parla di me e delle mie competenze.</p>
    </section>
    
    <section>
      <h2>I miei progetti</h2>
      <p>Qui presento alcuni dei progetti su cui ho lavorato.</p>
    </section>
  </main>
  
  <footer>
    <p>&copy; 2023 Il mio sito. Tutti i diritti riservati.</p>
  </footer>
</body>
</html>
```

### Soluzione: Implementazione di elementi e tag

Esercizio: Utilizzare correttamente i tag semantici per strutturare un articolo di blog.

```html
<article>
  <header>
    <h1>Come utilizzare i tag semantici in HTML5</h1>
    <p>Pubblicato il <time datetime="2023-06-15">15 Giugno 2023</time> da <a href="#">Mario Rossi</a></p>
  </header>
  
  <section>
    <h2>Introduzione</h2>
    <p>HTML5 ha introdotto numerosi elementi semantici che migliorano la struttura delle pagine web...</p>
  </section>
  
  <section>
    <h2>Vantaggi del markup semantico</h2>
    <p>Utilizzare tag semantici offre numerosi vantaggi:</p>
    <ul>
      <li>Migliore accessibilità</li>
      <li>SEO potenziato</li>
      <li>Codice più manutenibile</li>
    </ul>
  </section>
  
  <section>
    <h2>Esempi pratici</h2>
    <p>Vediamo alcuni esempi di utilizzo dei tag semantici più comuni:</p>
    
    <h3>L'elemento header</h3>
    <p>Il tag <code>&lt;header&gt;</code> viene utilizzato per...</p>
    
    <h3>L'elemento footer</h3>
    <p>Il tag <code>&lt;footer&gt;</code> viene utilizzato per...</p>
  </section>
  
  <footer>
    <p>Tags: <a href="#">HTML5</a>, <a href="#">Semantica</a>, <a href="#">Web Development</a></p>
    <section>
      <h3>Commenti</h3>
      <p>Lascia un commento qui sotto...</p>
    </section>
  </footer>
</article>
```

### Soluzione: Utilizzo dei caratteri speciali

Esercizio: Creare un paragrafo che utilizza correttamente i caratteri speciali e le entità HTML.

```html
<p>
  In HTML, alcuni caratteri speciali devono essere codificati utilizzando entità HTML:
  <ul>
    <li>Il simbolo minore (&lt;) si scrive come <code>&amp;lt;</code></li>
    <li>Il simbolo maggiore (&gt;) si scrive come <code>&amp;gt;</code></li>
    <li>La e commerciale (&amp;) si scrive come <code>&amp;amp;</code></li>
    <li>Le virgolette doppie (&quot;) si scrivono come <code>&amp;quot;</code></li>
    <li>L'apostrofo (&#39;) si scrive come <code>&amp;#39;</code></li>
  </ul>
  Altri caratteri speciali comuni includono:
  <ul>
    <li>Il simbolo del copyright (&copy;) si scrive come <code>&amp;copy;</code></li>
    <li>Il simbolo del marchio registrato (&reg;) si scrive come <code>&amp;reg;</code></li>
    <li>Il simbolo del trademark (&trade;) si scrive come <code>&amp;trade;</code></li>
    <li>La lettera è maiuscola accentata (&Egrave;) si scrive come <code>&amp;Egrave;</code></li>
    <li>Lo spazio non divisibile si scrive come <code>&amp;nbsp;</code></li>
  </ul>
</p>
```

## Esercizi su testo e formattazione

Questa sezione presenta le soluzioni agli esercizi relativi alla gestione del testo, elementi inline e block-level, collegamenti ipertestuali, immagini e tabelle.

### Soluzione: Gestione del testo

Esercizio: Creare una pagina con diversi livelli di intestazione, paragrafi e liste.

```html
<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Gestione del testo in HTML5</title>
</head>
<body>
  <h1>Guida alla formattazione del testo in HTML5</h1>
  
  <p>Questa pagina dimostra l'utilizzo di vari elementi per la formattazione del testo in HTML5.</p>
  
  <h2>Intestazioni</h2>
  <p>HTML5 supporta sei livelli di intestazioni, da h1 a h6:</p>
  
  <h1>Intestazione di livello 1</h1>
  <h2>Intestazione di livello 2</h2>
  <h3>Intestazione di livello 3</h3>
  <h4>Intestazione di livello 4</h4>
  <h5>Intestazione di livello 5</h5>
  <h6>Intestazione di livello 6</h6>
  
  <h2>Liste non ordinate</h2>
  <p>Le liste non ordinate utilizzano il tag ul:</p>
  
  <ul>
    <li>Elemento 1</li>
    <li>Elemento 2</li>
    <li>Elemento 3
      <ul>
        <li>Sottoelemento 3.1</li>
        <li>Sottoelemento 3.2</li>
      </ul>
    </li>
  </ul>
  
  <h2>Liste ordinate</h2>
  <p>Le liste ordinate utilizzano il tag ol:</p>
  
  <ol>
    <li>Primo passo</li>
    <li>Secondo passo</li>
    <li>Terzo passo
      <ol type="a">
        <li>Sottopasso a</li>
        <li>Sottopasso b</li>
      </ol>
    </li>
  </ol>
  
  <h2>Liste di definizioni</h2>
  <p>Le liste di definizioni utilizzano i tag dl, dt e dd:</p>
  
  <dl>
    <dt>HTML</dt>
    <dd>HyperText Markup Language, il linguaggio standard per le pagine web</dd>
    
    <dt>CSS</dt>
    <dd>Cascading Style Sheets, utilizzato per definire lo stile delle pagine HTML</dd>
    
    <dt>JavaScript</dt>
    <dd>Un linguaggio di programmazione che permette di creare contenuti dinamici</dd>
  </dl>
</body>
</html>
```

### Soluzione: Implementazione di collegamenti ipertestuali

Esercizio: Creare una pagina con diversi tipi di collegamenti ipertestuali.

```html
<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Collegamenti ipertestuali in HTML5</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      line-height: 1.6;
      max-width: 800px;
      margin: 0 auto;
      padding: 20px;
    }
    section {
      margin-bottom: 30px;
    }
    .button-link {
      display: inline-block;
      padding: 10px 20px;
      background-color: #4CAF50;
      color: white;
      text-decoration: none;
      border-radius: 4px;
    }
    .button-link:hover {
      background-color: #45a049;
    }
  </style>
</head>
<body>
  <h1>Esempi di collegamenti ipertestuali</h1>
  
  <section id="link-esterni">
    <h2>Collegamenti esterni</h2>
    <p>
      <a href="https://www.example.com" target="_blank" rel="noopener noreferrer">Visita Example.com</a> - 
      Questo link si apre in una nuova scheda e utilizza gli attributi di sicurezza appropriati.
    </p>
  </section>
  
  <section id="link-interni">
    <h2>Collegamenti interni</h2>
    <p>
      <a href="pagina2.html">Vai alla pagina 2</a> - 
      Questo è un collegamento relativo a una pagina nello stesso sito.
    </p>
    <p>
      <a href="/cartella/pagina.html">Vai alla pagina nella cartella</a> - 
      Questo è un collegamento a partire dalla root del sito.
    </p>
    <p>
      <a href="../altra-cartella/pagina.html">Vai alla pagina in un'altra cartella</a> - 
      Questo è un collegamento che risale di un livello nella gerarchia.
    </p>
  </section>
  
  <section id="ancore">
    <h2>Collegamenti a sezioni della pagina (ancore)</h2>
    <p>Indice:</p>
    <ul>
      <li><a href="#link-esterni">Collegamenti esterni</a></li>
      <li><a href="#link-interni">Collegamenti interni</a></li>
      <li><a href="#ancore">Ancore</a></li>
      <li><a href="#risorse">Collegamenti a risorse</a></li>
      <li><a href="#email">Collegamenti email</a></li>
    </ul>
  </section>
  
  <section id="risorse">
    <h2>Collegamenti a risorse non HTML</h2>
    <p>
      <a href="documento.pdf" download="nome-personalizzato.pdf">Scarica il PDF</a> - 
      Questo link scarica un file PDF con un nome personalizzato.
    </p>
    <p>
      <a href="immagine.jpg">Visualizza l'immagine</a> - 
      Questo link apre un'immagine.
    </p>
  </section>
  
  <section id="email">
    <h2>Collegamenti per email e protocolli speciali</h2>
    <p>
      <a href="mailto:info@esempio.it">Invia un'email</a> - 
      Questo link apre il client di posta elettronica.
    </p>
    <p>
      <a href="mailto:info@esempio.it?subject=Richiesta%20informazioni&body=Buongiorno%2C%0A%0AVorrei%20ricevere%20maggiori%20informazioni%20sui%20vostri%20servizi.">Invia un'email precompilata</a> - 
      Questo link apre il client di posta con oggetto e corpo precompilati.
    </p>
    <p>
      <a href="tel:+390123456789">+39 0123 456789</a> - 
      Questo link permette di effettuare una chiamata (utile su dispositivi mobili).
    </p>
  </section>
  
  <section>
    <h2>Collegamenti stilizzati</h2>
    <p>
      <a href="#" class="button-link">Pulsante</a> - 
      Questo è un collegamento stilizzato per apparire come un pulsante.
    </p>
  </section>
</body>
</html>
```

### Soluzione: Inserimento e gestione delle immagini

Esercizio: Creare una galleria di immagini responsive con didascalie.

```html
<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Galleria immagini responsive</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      line-height: 1.6;
      max-width: 1200px;
      margin: 0 auto;
      padding: 20px;
    }
    .gallery {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
      gap: 20px;
    }
    figure {
      margin: 0;
      border: 1px solid #ddd;
      border-radius: 4px;
      overflow: hidden;
    }
    figure img {
      width: 100%;
      height: auto;
      display: block;
    }
    figcaption {
      padding: 10px;
      background-color: #f8f8f8;
      text-align: center;
    }
    .responsive-image {