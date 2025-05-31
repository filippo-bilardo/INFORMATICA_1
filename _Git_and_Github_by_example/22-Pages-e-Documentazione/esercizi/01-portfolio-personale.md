# Esercizio 1: Portfolio Personale con GitHub Pages

## 🎯 Obiettivo
Creare un portfolio personale professionale utilizzando GitHub Pages, personalizzandolo completamente con le tue informazioni e progetti.

## 📋 Requisiti

### Requisiti Tecnici
- [ ] Repository GitHub pubblico
- [ ] GitHub Pages configurato e funzionante
- [ ] Sito responsive (mobile, tablet, desktop)
- [ ] HTML5 semantico e valido
- [ ] CSS3 moderno con variabili e grid/flexbox
- [ ] JavaScript per interattività
- [ ] Immagini ottimizzate (WebP quando possibile)
- [ ] Meta tag SEO completi
- [ ] Favicon personalizzato

### Contenuti Richiesti
- [ ] **Sezione Hero**: Nome, titolo professionale, breve descrizione
- [ ] **Chi Sono**: Biografia dettagliata (min. 200 parole)
- [ ] **Competenze**: Almeno 12 skill organizzate per categoria
- [ ] **Progetti**: Minimo 4 progetti con descrizioni e link
- [ ] **Esperienze**: Timeline delle esperienze lavorative/formative
- [ ] **Contatti**: Form funzionante e link social
- [ ] **CV Scaricabile**: Link per download PDF del curriculum

## 🚀 Fasi di Sviluppo

### Fase 1: Setup e Struttura (Tempo: 30 minuti)

1. **Creazione Repository**
   ```bash
   # Crea un nuovo repository su GitHub
   # Nome: tuonome.github.io (per sito personale) 
   # Oppure: portfolio (per progetto specifico)
   
   git clone https://github.com/tuousername/tuonome.github.io.git
   cd tuonome.github.io
   ```

2. **Struttura File**
   ```
   portfolio/
   ├── index.html
   ├── assets/
   │   ├── css/
   │   │   └── style.css
   │   ├── js/
   │   │   └── main.js
   │   ├── images/
   │   │   ├── profile.jpg
   │   │   ├── projects/
   │   │   └── icons/
   │   └── files/
   │       └── cv.pdf
   ├── favicon.ico
   └── README.md
   ```

3. **Configurazione GitHub Pages**
   - Vai su Settings > Pages
   - Source: Deploy from a branch
   - Branch: main / (root)
   - Salva e annota l'URL generato

### Fase 2: Contenuto e Design (Tempo: 90 minuti)

1. **HTML Semantico**
   ```html
   <!DOCTYPE html>
   <html lang="it">
   <head>
       <!-- Meta tag richiesti -->
       <meta charset="UTF-8">
       <meta name="viewport" content="width=device-width, initial-scale=1.0">
       <title>Tuo Nome - Portfolio</title>
       <meta name="description" content="Descrizione professionale">
       
       <!-- SEO e Social -->
       <meta property="og:title" content="Tuo Nome - Portfolio">
       <meta property="og:description" content="Descrizione">
       <meta property="og:image" content="URL_immagine">
       <meta property="og:url" content="URL_sito">
       
       <!-- CSS -->
       <link rel="stylesheet" href="assets/css/style.css">
       <link rel="icon" href="favicon.ico">
   </head>
   <body>
       <!-- Implementa tutte le sezioni richieste -->
   </body>
   </html>
   ```

2. **CSS Responsive**
   ```css
   :root {
       /* Definisci variabili per colori, font, spacing */
       --primary-color: #your-color;
       --secondary-color: #your-color;
       /* ... */
   }
   
   /* Mobile First Approach */
   @media (min-width: 768px) {
       /* Tablet styles */
   }
   
   @media (min-width: 1024px) {
       /* Desktop styles */
   }
   ```

3. **JavaScript Interattivo**
   - Navigazione smooth scroll
   - Menu mobile hamburger
   - Form validation
   - Animazioni al scroll
   - Typing effect (opzionale)

### Fase 3: Contenuti Personalizzati (Tempo: 60 minuti)

1. **Informazioni Personali**
   - Scrivi una biografia autentica
   - Elenca le tue competenze reali
   - Descrivi i tuoi progetti (anche scolastici)
   - Aggiungi le tue esperienze

2. **Progetti Showcase**
   Per ogni progetto includi:
   - Screenshot o video demo
   - Descrizione tecnica
   - Tecnologie utilizzate
   - Link a repository GitHub
   - Link demo (se disponibile)
   - Sfide affrontate e soluzioni

3. **Immagini e Media**
   - Foto profilo professionale
   - Screenshot progetti
   - Icone per le tecnologie
   - Ottimizza tutte le immagini

### Fase 4: Form di Contatto (Tempo: 30 minuti)

1. **Integrazione Formspree**
   ```html
   <form action="https://formspree.io/f/YOUR_ID" method="POST">
       <input type="text" name="name" required>
       <input type="email" name="email" required>
       <textarea name="message" required></textarea>
       <button type="submit">Invia</button>
   </form>
   ```

2. **Validazione JavaScript**
   ```javascript
   function validateForm() {
       // Implementa validazione lato client
   }
   ```

### Fase 5: Ottimizzazione e Test (Tempo: 30 minuti)

1. **Performance**
   - Comprimi immagini
   - Minifica CSS/JS
   - Test velocità con PageSpeed Insights

2. **SEO**
   - Verifica meta tag
   - Test con strumenti SEO
   - Sitemap.xml (opzionale)

3. **Accessibility**
   - Alt text per immagini
   - Contrasto colori adeguato
   - Navigazione da tastiera
   - ARIA labels dove necessario

4. **Cross-browser Testing**
   - Chrome, Firefox, Safari, Edge
   - Test su dispositivi mobile

## ✅ Criteri di Valutazione

### Tecnico (40 punti)
- **HTML Semantico** (10 pts): Uso corretto di tag semantici
- **CSS Responsive** (10 pts): Layout che funziona su tutti i dispositivi
- **JavaScript** (10 pts): Interattività e user experience
- **Performance** (10 pts): Velocità di caricamento e ottimizzazione

### Design (30 punti)
- **Estetica** (15 pts): Design moderno e professionale
- **UX/UI** (15 pts): Navigazione intuitiva e accessibilità

### Contenuto (30 punti)
- **Completezza** (15 pts): Tutte le sezioni richieste presenti
- **Qualità** (15 pts): Contenuti ben scritti e rilevanti

## 🎯 Bonus Points (max +10)
- [ ] **Animazioni Avanzate**: CSS animations o biblioteca come AOS
- [ ] **Dark Mode Toggle**: Implementazione tema scuro/chiaro
- [ ] **Multi-lingua**: Supporto italiano/inglese
- [ ] **Blog Section**: Sezione blog con almeno 3 post
- [ ] **Analytics**: Integrazione Google Analytics
- [ ] **PWA Features**: Service Worker per funzionalità offline

## 📤 Consegna

### Cosa Consegnare
1. **URL del sito live**: https://tuonome.github.io
2. **Repository GitHub**: Link al codice sorgente
3. **README.md** dettagliato con:
   - Descrizione del progetto
   - Tecnologie utilizzate
   - Istruzioni per eseguire localmente
   - Screenshot
   - Licenza

### Formato Consegna
Crea un file `CONSEGNA.md` con:
```markdown
# Portfolio Personale - [Tuo Nome]

## 🔗 Link
- **Sito Live**: [URL]
- **Repository**: [URL]

## 📋 Checklist Completamento
- [x] Tutte le sezioni richieste
- [x] Design responsive
- [x] Form di contatto funzionante
- [x] SEO ottimizzato
- [x] Performance accettabile

## 🛠️ Tecnologie Utilizzate
- HTML5
- CSS3 (Grid, Flexbox, Variables)
- JavaScript ES6+
- GitHub Pages
- [Altre tecnologie]

## 🎯 Sfide Affrontate
[Descrivi le principali sfide e come le hai risolte]

## 🚀 Miglioramenti Futuri
[Lista di miglioramenti che vorresti implementare]
```

## 💡 Suggerimenti

### Design Inspiration
- Dribbble, Behance per ispirazioni
- Portfolio di sviluppatori famosi
- Template gratuiti come riferimento (non copiare!)

### Risorse Utili
- **Font**: Google Fonts
- **Icone**: Font Awesome, Feather Icons
- **Immagini**: Unsplash, Pexels
- **Colori**: Coolors.co, Adobe Color

### Best Practices
- Mantieni il design semplice e pulito
- Usa massimo 2-3 font
- Limita la palette colori
- Racconta una storia attraverso il portfolio
- Mostra il processo, non solo il risultato

### Errori da Evitare
- Portfolio troppo generico
- Mancanza di progetti reali
- Design non responsive
- Tempi di caricamento lunghi
- Informazioni di contatto mancanti

## 🆘 Troubleshooting

### Problemi Comuni
1. **Sito non si aggiorna**: Cache del browser, aspetta deploy
2. **Immagini non caricano**: Percorsi relativi, case sensitivity
3. **CSS non funziona**: Verifica collegamenti, sintassi
4. **Form non invia**: Controlla configurazione Formspree

### Risorse di Aiuto
- Documentazione GitHub Pages
- MDN Web Docs per HTML/CSS/JS
- Stack Overflow per problemi specifici
- Community Discord/Slack per supporto

---

**Tempo stimato totale: 4-5 ore**  
**Difficoltà: ⭐⭐⭐ (Intermedio)**

Buona fortuna! Ricorda che questo portfolio rappresenta te come professionista, quindi investi tempo e passione per renderlo unico e memorabile. 🚀
