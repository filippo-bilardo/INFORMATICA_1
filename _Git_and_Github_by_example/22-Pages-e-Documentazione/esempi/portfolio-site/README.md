# Portfolio Site - Esempio GitHub Pages

Questo esempio mostra come creare un portfolio personale professionale utilizzando GitHub Pages con HTML, CSS e JavaScript puri.

## 🎯 Caratteristiche

- **Design Moderno e Responsive**: Layout professionale che si adatta a tutti i dispositivi
- **Animazioni Fluide**: Effetti di scroll e transizioni CSS moderne
- **SEO Ottimizzato**: Meta tag completi per motori di ricerca e social media
- **Performance**: Codice ottimizzato per caricamento veloce
- **Accessibilità**: Conforme agli standard WCAG
- **Form di Contatto**: Integrazione con Formspree per gestire i messaggi

## 📁 Struttura File

```
portfolio-site/
├── index.html              # Pagina principale
├── assets/
│   ├── css/
│   │   └── style.css       # Stili CSS principali
│   ├── js/
│   │   └── main.js         # JavaScript per interattività
│   └── images/
│       ├── profile.jpg     # Foto profilo
│       ├── project1.jpg    # Screenshot progetto 1
│       ├── project2.jpg    # Screenshot progetto 2
│       ├── project3.jpg    # Screenshot progetto 3
│       ├── favicon.ico     # Icona del sito
│       └── og-image.jpg    # Immagine per social media
└── README.md               # Questa documentazione
```

## 🚀 Come Utilizzare

### 1. Setup Iniziale

1. **Fork del Repository**: Fai il fork di questo progetto
2. **Rinomina Repository**: Cambia il nome in `tuonome.github.io` per un sito personale
3. **Abilita GitHub Pages**: Vai in Settings > Pages e seleziona la branch main

### 2. Personalizzazione

#### Informazioni Personali
Modifica il file `index.html` per aggiornare:
- Nome e titolo nella sezione hero
- Biografia nella sezione "Chi Sono"
- Competenze nella sezione skills
- Progetti nella sezione portfolio
- Informazioni di contatto

#### Stili e Design
Nel file `assets/css/style.css` puoi:
- Modificare i colori nelle variabili CSS (`:root`)
- Personalizzare font e dimensioni
- Aggiungere nuove animazioni

#### Immagini
Sostituisci le immagini nella cartella `assets/images/`:
- `profile.jpg`: La tua foto profilo (400x400px consigliato)
- `project*.jpg`: Screenshot dei tuoi progetti (800x600px consigliato)
- `favicon.ico`: Icona del tuo sito (32x32px)
- `og-image.jpg`: Immagine per social media (1200x630px)

### 3. Configurazione Form di Contatto

Per far funzionare il form di contatto:

1. **Registrati su Formspree**: Vai su [formspree.io](https://formspree.io)
2. **Crea un nuovo form**: Ottieni l'endpoint del form
3. **Aggiorna l'HTML**: Sostituisci l'action del form:
   ```html
   <form class="contact-form" action="https://formspree.io/f/YOUR-FORM-ID" method="POST">
   ```

### 4. SEO e Analytics

#### Meta Tag
Il template include già:
- Meta description ottimizzata
- Open Graph per social media
- Twitter Cards
- Structured data

#### Google Analytics (Opzionale)
Aggiungi questo codice prima della chiusura di `</head>`:
```html
<!-- Google Analytics -->
<script async src="https://www.googletagmanager.com/gtag/js?id=GA_TRACKING_ID"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());
  gtag('config', 'GA_TRACKING_ID');
</script>
```

## 🎨 Personalizzazione Avanzata

### Colori del Brand
Modifica le variabili CSS in `style.css`:
```css
:root {
    --primary-color: #6366f1;      /* Colore principale */
    --secondary-color: #8b5cf6;    /* Colore secondario */
    --accent-color: #06b6d4;       /* Colore accent */
}
```

### Nuove Sezioni
Per aggiungere nuove sezioni:
1. Aggiungi la sezione nel HTML
2. Crea gli stili CSS corrispondenti
3. Aggiorna la navigazione
4. Aggiungi gli script JavaScript se necessario

### Animazioni
Il template include animazioni al scroll. Per aggiungerne:
```javascript
// Esempio di nuova animazione
const newElements = document.querySelectorAll('.new-element');
observer.observe(newElements);
```

## 🔧 Troubleshooting

### Problemi Comuni

1. **Immagini Non Caricano**
   - Verifica i percorsi delle immagini
   - Controlla che i file siano nel repository
   - Usa nomi senza spazi o caratteri speciali

2. **Form Non Funziona**
   - Verifica l'endpoint Formspree
   - Controlla che l'action sia corretto
   - Testa su un dominio pubblico (non localhost)

3. **Sito Non Aggiornato**
   - Aspetta qualche minuto per il deploy
   - Controlla lo stato in Settings > Pages
   - Svuota la cache del browser

### Debug JavaScript
Apri la console del browser (F12) per vedere eventuali errori JavaScript.

## 📱 Test Responsive

Testa il sito su diversi dispositivi:
- Desktop (1920px+)
- Laptop (1366px-1920px)
- Tablet (768px-1366px)
- Mobile (320px-768px)

## 🌟 Funzionalità Avanzate

### Tema Scuro
Il template include il supporto per il tema scuro:
```javascript
// Attiva/disattiva tema scuro
toggleTheme();
```

### Lazy Loading
Per migliorare le performance, aggiungi lazy loading alle immagini:
```html
<img src="image.jpg" loading="lazy" alt="Descrizione">
```

### PWA (Progressive Web App)
Per trasformare il sito in una PWA, aggiungi:
1. Service Worker
2. Web App Manifest
3. Icone per diverse dimensioni

## 📈 Ottimizzazione Performance

1. **Compressione Immagini**: Usa WebP quando possibile
2. **Minificazione**: Minifica CSS e JavaScript per produzione
3. **CDN**: Usa CDN per librerie esterne
4. **Caching**: Configura header di cache appropriati

## 🤝 Contributi

Per migliorare questo template:
1. Fai un fork del progetto
2. Crea un branch per la tua feature
3. Fai commit delle modifiche
4. Apri una Pull Request

## 📄 Licenza

Questo progetto è rilasciato sotto licenza MIT. Puoi usarlo liberamente per i tuoi progetti personali e commerciali.

## 🆘 Supporto

Se hai problemi o domande:
1. Controlla la documentazione GitHub Pages
2. Cerca in Stack Overflow
3. Apri un issue nel repository
4. Consulta la community GitHub

---

**Buona fortuna con il tuo portfolio! 🚀**
