/**
 * ESERCIZIO 3: Manipolatore di Pixel RGB
 * 
 * DIFFICOLTÀ: ⭐⭐⭐⭐ Difficile
 * TEMPO: 60-90 minuti
 * 
 * OBIETTIVO:
 * Creare un programma che manipoli pixel RGB usando operatori bit a bit
 * per implementare filtri di immagine e compressione di dati.
 */

#include <stdio.h>
#include <stdint.h>

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  ESERCIZIO 3 - TO DO                     ║\n");
    printf("║              Manipolatore Pixel RGB                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    /* 
     * 🎯 COMPITO AVANZATO:
     * 
     * Implementa un sistema di manipolazione pixel RGB che utilizzi
     * operatori bit a bit per gestire colori e applicare filtri.
     * 
     * 📋 FORMATO PIXEL:
     * Un pixel RGB a 24 bit è rappresentato come:
     * - Bit 23-16: Rosso (R)
     * - Bit 15-8:  Verde (G) 
     * - Bit 7-0:   Blu (B)
     * 
     * Esempio: 0xFF5733 = RGB(255, 87, 51) = arancione
     * 
     * 🛠️ FUNZIONALITÀ DA IMPLEMENTARE:
     * 
     * 1. CREAZIONE PIXEL:
     *    - Chiedi valori R, G, B (0-255)
     *    - Componi un uint32_t usando operatori bit a bit
     *    - Mostra rappresentazione esadecimale e binaria
     * 
     * 2. ESTRAZIONE COMPONENTI:
     *    - Da un pixel RGB, estrai R, G, B separatamente
     *    - Usa shift e maschere bit
     * 
     * 3. FILTRI COLORE (usando bit a bit):
     *    
     *    a) FILTRO ROSSO:
     *       - Mantieni solo il canale rosso (azzera G e B)
     *       - Usa maschere: pixel & 0xFF0000
     *    
     *    b) FILTRO NEGATIVO:
     *       - Inverti tutti i bit dei colori
     *       - Usa: ~pixel & 0xFFFFFF
     *    
     *    c) FILTRO GRIGIO:
     *       - Media = (R + G + B) / 3
     *       - Imposta tutti i canali al valore medio
     *    
     *    d) FILTRO LUMINOSITÀ:
     *       - Moltiplica ogni canale per un fattore
     *       - Controlla overflow (max 255)
     * 
     * 4. COMPRESSIONE COLORE:
     *    - Riduci da 24 bit (8-8-8) a 15 bit (5-5-5)
     *    - Usa shift per ridurre precisione
     *    - Riconverti a 24 bit per confronto
     * 
     * 5. OPERAZIONI SPECIALI:
     *    
     *    a) ALPHA BLENDING:
     *       - Mescola due pixel con trasparenza
     *       - Formula: C = (alpha * C1 + (255-alpha) * C2) / 255
     *    
     *    b) CONTRASTO:
     *       - Aumenta/diminuisci contrasto per ogni canale
     *       - Se > 128: aumenta, se < 128: diminuisci
     *    
     *    c) SWAP CANALI:
     *       - Scambia due canali (es: R ↔ B)
     *       - Usa XOR per swap senza variabili temporanee
     * 
     * 6. ANALISI PIXEL:
     *    - Calcola luminosità percepita: 0.299*R + 0.587*G + 0.114*B
     *    - Determina se il colore è "caldo" o "freddo"
     *    - Trova il canale dominante
     * 
     * ESEMPIO OUTPUT:
     * 
     * 🎨 CREAZIONE PIXEL:
     * Inserisci R (0-255): 255
     * Inserisci G (0-255): 87  
     * Inserisci B (0-255): 51
     * 
     * Pixel creato: 0xFF5733
     * Binario: 11111111 01010111 00110011
     * RGB(255, 87, 51) - Arancione
     * 
     * 🔍 ESTRAZIONE COMPONENTI:
     * R = (0xFF5733 >> 16) & 0xFF = 255
     * G = (0xFF5733 >> 8) & 0xFF = 87
     * B = 0xFF5733 & 0xFF = 51
     * 
     * 🎭 APPLICAZIONE FILTRI:
     * Originale:    0xFF5733 RGB(255, 87, 51)
     * Solo Rosso:   0xFF0000 RGB(255, 0, 0)
     * Negativo:     0x00A8CC RGB(0, 168, 204)
     * Grigio:       0x7B7B7B RGB(123, 123, 123)
     * +50% Luce:    0xFF803F RGB(255, 128, 63)
     * 
     * 💾 COMPRESSIONE 15-BIT:
     * Originale 24-bit: RGB(255, 87, 51)
     * Compresso 15-bit: RGB(248, 80, 48)
     * Perdita qualità: 2.3%
     * 
     * 🔀 OPERAZIONI SPECIALI:
     * Alpha blend 50%: RGB(191, 118, 89)
     * Contrasto +20%: RGB(255, 104, 61)
     * Swap R↔B: RGB(51, 87, 255)
     */
    
    // 🚧 IL TUO CODICE QUI SOTTO 🚧
    
    
    
    return 0;
}

/*
 * 💡 AIUTI TECNICI AVANZATI:
 * 
 * 🔸 Creazione pixel da componenti:
 *    uint32_t pixel = (r << 16) | (g << 8) | b;
 * 
 * 🔸 Estrazione componenti:
 *    uint8_t r = (pixel >> 16) & 0xFF;
 *    uint8_t g = (pixel >> 8) & 0xFF;
 *    uint8_t b = pixel & 0xFF;
 * 
 * 🔸 Maschere utili:
 *    #define MASK_RED   0xFF0000
 *    #define MASK_GREEN 0x00FF00
 *    #define MASK_BLUE  0x0000FF
 * 
 * 🔸 Controllo overflow:
 *    if (valore > 255) valore = 255;
 *    // Oppure: valore = valore > 255 ? 255 : valore;
 * 
 * 🔸 Stampa esadecimale:
 *    printf("0x%06X", pixel);
 * 
 * 🔸 Stampa binario (funzione):
 *    void print_binary(uint32_t n, int bits) {
 *        for(int i = bits-1; i >= 0; i--) {
 *            printf("%d", (n >> i) & 1);
 *            if(i % 8 == 0 && i > 0) printf(" ");
 *        }
 *    }
 * 
 * 🔸 XOR swap (senza variabile temp):
 *    a = a ^ b;
 *    b = a ^ b;  // b ora ha il valore originale di a
 *    a = a ^ b;  // a ora ha il valore originale di b
 * 
 * 📚 CONCETTI FOCUS:
 * - Operatori bit a bit: & | ^ ~ << >>
 * - Maschere di bit per isolare/modificare
 * - Shifting per posizionamento bit
 * - Compressione/decompressione dati
 * - Manipolazione bit a livello pixel
 * - Ottimizzazione con operatori bit
 * 
 * 🎯 CHALLENGE EXTRA:
 * - Implementa un dithering Floyd-Steinberg
 * - Crea una palette di 16 colori ottimizzata
 * - Implementa compressione RLE sui pixel
 */
