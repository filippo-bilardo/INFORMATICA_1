/**
 * SOLUZIONE ESERCIZIO 3: Manipolatore di Pixel RGB
 * 
 * DIFFICOLTÀ: ⭐⭐⭐⭐ Difficile
 * TEMPO COMPLETAMENTO: 60-90 minuti
 * 
 * OBIETTIVO RAGGIUNTO:
 * ✅ Implementato manipolatore pixel RGB completo
 * ✅ Utilizzati tutti gli operatori bit a bit
 * ✅ Creati filtri immagine avanzati
 * ✅ Implementata compressione colore
 * ✅ Sviluppate operazioni speciali (alpha blending, contrasto)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Definizione maschere utili per manipolazione bit
#define MASK_RED   0xFF0000    // 11111111 00000000 00000000
#define MASK_GREEN 0x00FF00    // 00000000 11111111 00000000
#define MASK_BLUE  0x0000FF    // 00000000 00000000 11111111
#define MASK_ALL   0xFFFFFF    // 11111111 11111111 11111111

// Funzioni di utilità
void print_binary(uint32_t n, int bits) {
    for(int i = bits-1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if(i % 8 == 0 && i > 0) printf(" ");
    }
}

void print_pixel_info(uint32_t pixel, const char* description) {
    uint8_t r = (pixel >> 16) & 0xFF;
    uint8_t g = (pixel >> 8) & 0xFF;
    uint8_t b = pixel & 0xFF;
    
    printf("   %s\n", description);
    printf("   📋 Hex: 0x%06X | RGB(%d, %d, %d)\n", pixel & 0xFFFFFF, r, g, b);
    printf("   📋 Bin: ");
    print_binary(pixel, 24);
    printf("\n");
}

uint8_t clamp_byte(int value) {
    return (value > 255) ? 255 : (value < 0) ? 0 : value;
}

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               🎨 MANIPOLATORE PIXEL RGB 🎨               ║\n");
    printf("║                       SOLUZIONE                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Variabili per componenti colore
    int r_input, g_input, b_input;
    uint32_t pixel_originale;
    
    // === 1. CREAZIONE PIXEL ===
    printf("🎨 FASE 1: CREAZIONE PIXEL RGB\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("Inserisci i valori RGB (0-255):\n");
    printf("   🔴 Rosso (R): ");
    scanf("%d", &r_input);
    printf("   🟢 Verde (G): ");
    scanf("%d", &g_input);
    printf("   🔵 Blu (B): ");
    scanf("%d", &b_input);
    
    // Validazione e clamp dei valori
    uint8_t r = clamp_byte(r_input);
    uint8_t g = clamp_byte(g_input);
    uint8_t b = clamp_byte(b_input);
    
    if (r != r_input || g != g_input || b != b_input) {
        printf("   ⚠️  Alcuni valori sono stati corretti al range 0-255\n");
    }
    
    // Creazione pixel usando operatori bit a bit
    pixel_originale = (r << 16) | (g << 8) | b;
    
    printf("\n📦 PIXEL CREATO:\n");
    print_pixel_info(pixel_originale, "Pixel originale");
    
    printf("   🔧 Processo di creazione bit a bit:\n");
    printf("      R << 16: 0x%02X → 0x%06X\n", r, r << 16);
    printf("      G << 8:  0x%02X → 0x%06X\n", g, g << 8);
    printf("      B << 0:  0x%02X → 0x%06X\n", b, b);
    printf("      OR (|):  0x%06X | 0x%06X | 0x%06X = 0x%06X\n", 
           r << 16, g << 8, b, pixel_originale);
    
    // === 2. ESTRAZIONE COMPONENTI ===
    printf("\n🔍 FASE 2: ESTRAZIONE COMPONENTI\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    uint8_t r_estratto = (pixel_originale >> 16) & 0xFF;
    uint8_t g_estratto = (pixel_originale >> 8) & 0xFF;
    uint8_t b_estratto = pixel_originale & 0xFF;
    
    printf("🔧 Processo di estrazione bit a bit:\n");
    printf("   R = (0x%06X >> 16) & 0xFF = 0x%02X = %d\n", 
           pixel_originale, r_estratto, r_estratto);
    printf("   G = (0x%06X >> 8) & 0xFF = 0x%02X = %d\n", 
           pixel_originale, g_estratto, g_estratto);
    printf("   B = 0x%06X & 0xFF = 0x%02X = %d\n", 
           pixel_originale, b_estratto, b_estratto);
    
    // === 3. FILTRI COLORE ===
    printf("\n🎭 FASE 3: APPLICAZIONE FILTRI\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // a) Filtro Solo Rosso
    uint32_t filtro_rosso = pixel_originale & MASK_RED;
    print_pixel_info(filtro_rosso, "🔴 FILTRO ROSSO (pixel & 0xFF0000)");
    
    // b) Filtro Solo Verde
    uint32_t filtro_verde = pixel_originale & MASK_GREEN;
    print_pixel_info(filtro_verde, "🟢 FILTRO VERDE (pixel & 0x00FF00)");
    
    // c) Filtro Solo Blu
    uint32_t filtro_blu = pixel_originale & MASK_BLUE;
    print_pixel_info(filtro_blu, "🔵 FILTRO BLU (pixel & 0x0000FF)");
    
    // d) Filtro Negativo
    uint32_t filtro_negativo = (~pixel_originale) & MASK_ALL;
    print_pixel_info(filtro_negativo, "🎭 FILTRO NEGATIVO (~pixel & 0xFFFFFF)");
    
    // e) Filtro Grigio
    uint8_t media = (r + g + b) / 3;
    uint32_t filtro_grigio = (media << 16) | (media << 8) | media;
    print_pixel_info(filtro_grigio, "⚪ FILTRO GRIGIO (media componenti)");
    printf("   📊 Media calcolata: (%d + %d + %d) / 3 = %d\n", r, g, b, media);
    
    // f) Filtro Luminosità +50%
    int luminosita_fattore = 150; // 150% = +50%
    uint8_t r_lum = clamp_byte((r * luminosita_fattore) / 100);
    uint8_t g_lum = clamp_byte((g * luminosita_fattore) / 100);
    uint8_t b_lum = clamp_byte((b * luminosita_fattore) / 100);
    uint32_t filtro_luminoso = (r_lum << 16) | (g_lum << 8) | b_lum;
    print_pixel_info(filtro_luminoso, "💡 FILTRO LUMINOSITÀ +50%");
    
    // === 4. COMPRESSIONE COLORE ===
    printf("\n💾 FASE 4: COMPRESSIONE COLORE (24-bit → 15-bit)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Compressione da 8-8-8 a 5-5-5 bit
    uint8_t r_5bit = r >> 3;  // Da 8 bit a 5 bit (divide per 8)
    uint8_t g_5bit = g >> 3;
    uint8_t b_5bit = b >> 3;
    
    // Pixel compresso in formato 15-bit (ma memorizzato in 16-bit)
    uint16_t pixel_15bit = (r_5bit << 10) | (g_5bit << 5) | b_5bit;
    
    // Decompressione per confronto (riporta a 8-bit)
    uint8_t r_decompresso = (r_5bit << 3) | (r_5bit >> 2);  // Replica bit per riempire
    uint8_t g_decompresso = (g_5bit << 3) | (g_5bit >> 2);
    uint8_t b_decompresso = (b_5bit << 3) | (b_5bit >> 2);
    uint32_t pixel_decompresso = (r_decompresso << 16) | (g_decompresso << 8) | b_decompresso;
    
    printf("🗜️  COMPRESSIONE:\n");
    print_pixel_info(pixel_originale, "Originale 24-bit");
    printf("   📦 Compresso 15-bit: 0x%04X (R:%d G:%d B:%d in 5-bit ciascuno)\n", 
           pixel_15bit, r_5bit, g_5bit, b_5bit);
    print_pixel_info(pixel_decompresso, "Decompresso 24-bit");
    
    // Calcolo perdita qualità
    int perdita_r = abs(r - r_decompresso);
    int perdita_g = abs(g - g_decompresso);
    int perdita_b = abs(b - b_decompresso);
    float perdita_percentuale = ((perdita_r + perdita_g + perdita_b) * 100.0) / (3 * 255);
    printf("   📊 Perdita qualità: R:%d G:%d B:%d (%.1f%% totale)\n", 
           perdita_r, perdita_g, perdita_b, perdita_percentuale);
    
    // === 5. OPERAZIONI SPECIALI ===
    printf("\n🔀 FASE 5: OPERAZIONI SPECIALI\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // a) Alpha Blending con colore fisso (blu cielo)
    uint32_t colore2 = 0x87CEEB;  // Sky blue
    uint8_t alpha = 128;  // 50% trasparenza
    
    uint8_t r2 = (colore2 >> 16) & 0xFF;
    uint8_t g2 = (colore2 >> 8) & 0xFF;
    uint8_t b2 = colore2 & 0xFF;
    
    uint8_t r_blend = (alpha * r + (255 - alpha) * r2) / 255;
    uint8_t g_blend = (alpha * g + (255 - alpha) * g2) / 255;
    uint8_t b_blend = (alpha * b + (255 - alpha) * b2) / 255;
    uint32_t pixel_blended = (r_blend << 16) | (g_blend << 8) | b_blend;
    
    printf("ALPHA BLENDING (50%% con blu cielo):\n");
    print_pixel_info(pixel_originale, "Pixel 1 (tuo colore)");
    print_pixel_info(colore2, "Pixel 2 (blu cielo)");
    print_pixel_info(pixel_blended, "Risultato blending");
    
    // b) Contrasto (aumenta se > 128, diminuisce se < 128)
    int contrasto_fattore = 120;  // +20%
    uint8_t r_contrasto = clamp_byte(((r - 128) * contrasto_fattore / 100) + 128);
    uint8_t g_contrasto = clamp_byte(((g - 128) * contrasto_fattore / 100) + 128);
    uint8_t b_contrasto = clamp_byte(((b - 128) * contrasto_fattore / 100) + 128);
    uint32_t pixel_contrasto = (r_contrasto << 16) | (g_contrasto << 8) | b_contrasto;
    
    print_pixel_info(pixel_contrasto, "🔆 CONTRASTO +20%");
    
    // c) Swap canali R ↔ B usando XOR
    printf("\n🔄 SWAP CANALI R ↔ B (usando XOR):\n");
    uint32_t pixel_swap = pixel_originale;
    uint8_t temp_r = (pixel_swap >> 16) & 0xFF;
    uint8_t temp_b = pixel_swap & 0xFF;
    
    // XOR swap senza variabile temporanea
    temp_r = temp_r ^ temp_b;
    temp_b = temp_r ^ temp_b;  // temp_b ora ha il valore originale di temp_r
    temp_r = temp_r ^ temp_b;  // temp_r ora ha il valore originale di temp_b
    
    pixel_swap = (temp_r << 16) | (g << 8) | temp_b;
    print_pixel_info(pixel_swap, "Canali R ↔ B scambiati");
    
    printf("   🔧 XOR Swap Process:\n");
    printf("      r = r ^ b, b = r ^ b, r = r ^ b\n");
    printf("      Originale: R=%d B=%d → Swappato: R=%d B=%d\n", 
           r, b, temp_r, temp_b);
    
    // === 6. ANALISI PIXEL ===
    printf("\n📊 FASE 6: ANALISI PIXEL AVANZATA\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Luminosità percepita (standard ITU-R BT.709)
    float luminosita_percepita = 0.299 * r + 0.587 * g + 0.114 * b;
    printf("💡 Luminosità percepita: %.1f/255 (%.1f%%)\n", 
           luminosita_percepita, (luminosita_percepita / 255) * 100);
    
    // Canale dominante
    char canale_dominante;
    int valore_dominante = r;
    canale_dominante = 'R';
    
    if (g > valore_dominante) {
        valore_dominante = g;
        canale_dominante = 'G';
    }
    if (b > valore_dominante) {
        valore_dominante = b;
        canale_dominante = 'B';
    }
    
    printf("🎯 Canale dominante: %c (%d/255)\n", canale_dominante, valore_dominante);
    
    // Temperatura colore (caldo vs freddo)
    bool colore_caldo = (r + g) > (b * 1.5);  // Rosso/giallo vs blu
    printf("🌡️  Temperatura: %s\n", colore_caldo ? "🔥 CALDO (dominanza rosso/giallo)" : "❄️ FREDDO (dominanza blu)");
    
    // Saturazione (distanza dal grigio)
    int max_comp = (r > g) ? (r > b ? r : b) : (g > b ? g : b);
    int min_comp = (r < g) ? (r < b ? r : b) : (g < b ? g : b);
    float saturazione = max_comp > 0 ? (float)(max_comp - min_comp) / max_comp : 0;
    printf("🎨 Saturazione: %.1f%% %s\n", saturazione * 100, 
           saturazione > 0.7 ? "(molto vivace)" : 
           saturazione > 0.3 ? "(moderata)" : "(tenue/grigio)");
    
    // === 7. DIMOSTRAZIONE OPERATORI BIT ===
    printf("\n🔧 FASE 7: DIMOSTRAZIONE OPERATORI BIT\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    uint32_t demo = pixel_originale;
    printf("🔹 Operatori bit a bit applicati al pixel 0x%06X:\n\n", demo);
    
    // AND (&) - Mascheratura
    printf("   & (AND) - Mascheratura:\n");
    printf("     0x%06X & 0x%06X = 0x%06X (isola rosso)\n", demo, MASK_RED, demo & MASK_RED);
    printf("     0x%06X & 0x%06X = 0x%06X (isola verde)\n", demo, MASK_GREEN, demo & MASK_GREEN);
    
    // OR (|) - Combinazione
    printf("\n   | (OR) - Combinazione:\n");
    printf("     0x%06X | 0x%06X = 0x%06X (aggiunge blu)\n", demo & 0xFFFF00, 0x0000FF, (demo & 0xFFFF00) | 0x0000FF);
    
    // XOR (^) - Inversione selettiva
    printf("\n   ^ (XOR) - Inversione selettiva:\n");
    printf("     0x%06X ^ 0x%06X = 0x%06X (inverte solo rosso)\n", demo, MASK_RED, demo ^ MASK_RED);
    
    // NOT (~) - Inversione completa
    printf("\n   ~ (NOT) - Inversione completa:\n");
    printf("     ~0x%06X & 0x%06X = 0x%06X (negativo)\n", demo, MASK_ALL, (~demo) & MASK_ALL);
    
    // Shift left (<<) - Moltiplicazione
    printf("\n   << (Shift left) - Spostamento bit:\n");
    printf("     0x%02X << 16 = 0x%06X (sposta R in posizione)\n", r, r << 16);
    printf("     0x%02X << 8  = 0x%06X (sposta G in posizione)\n", g, g << 8);
    
    // Shift right (>>) - Divisione
    printf("\n   >> (Shift right) - Estrazione:\n");
    printf("     0x%06X >> 16 = 0x%02X (estrae R)\n", demo, (demo >> 16) & 0xFF);
    printf("     0x%06X >> 8  = 0x%02X (estrae G)\n", demo, (demo >> 8) & 0xFF);
    
    // === RIEPILOGO FINALE ===
    printf("\n🎉 RIEPILOGO OPERAZIONI COMPLETATE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   ✅ Creazione pixel da componenti RGB\n");
    printf("   ✅ Estrazione componenti con shift e maschere\n");
    printf("   ✅ Applicazione filtri colore (rosso, negativo, grigio, luminosità)\n");
    printf("   ✅ Compressione 24-bit → 15-bit con calcolo perdita\n");
    printf("   ✅ Alpha blending per trasparenza\n");
    printf("   ✅ Regolazione contrasto\n");
    printf("   ✅ Swap canali con XOR\n");
    printf("   ✅ Analisi colore avanzata (luminosità, saturazione, temperatura)\n");
    printf("   ✅ Dimostrazione di tutti gli operatori bit a bit\n");
    
    printf("\n🎯 OPERATORI BIT A BIT MASTERIZZATI:\n");
    printf("   🔸 & (AND): Mascheratura e isolamento bit\n");
    printf("   🔸 | (OR): Combinazione e impostazione bit\n");
    printf("   🔸 ^ (XOR): Inversione selettiva e swap\n");
    printf("   🔸 ~ (NOT): Inversione completa di tutti i bit\n");
    printf("   🔸 << (Shift left): Moltiplicazione per potenze di 2\n");
    printf("   🔸 >> (Shift right): Divisione per potenze di 2\n");
    
    printf("\n🚀 Manipolatore pixel RGB completato con successo!\n");
    printf("   Hai padroneggiato gli operatori bit più avanzati del linguaggio C.\n\n");
    
    return 0;
}

/*
 * 📊 ANALISI DELLA SOLUZIONE AVANZATA:
 * 
 * ✅ OBIETTIVI RAGGIUNTI:
 * - Manipolazione completa pixel RGB a livello bit
 * - Utilizzo di tutti gli operatori bit a bit (&, |, ^, ~, <<, >>)
 * - Implementazione filtri immagine realistici
 * - Sistema di compressione colore con calcolo perdita
 * - Operazioni avanzate (alpha blending, contrasto, swap XOR)
 * - Analisi colore con algoritmi standard (ITU-R BT.709)
 * 
 * 🎓 CONCETTI AVANZATI INSEGNATI:
 * - Rappresentazione colori in memoria (RGB 24-bit)
 * - Maschere di bit per isolamento componenti
 * - Shifting per posizionamento e estrazione
 * - Compressione lossy con perdita qualità
 * - Algoritmi di computer graphics
 * - Manipolazione dati a basso livello
 * 
 * 💪 SKILLS SVILUPPATE:
 * - Programmazione grafica e multimedia
 * - Ottimizzazione performance con operatori bit
 * - Algoritmi di image processing
 * - Gestione memoria e rappresentazione dati
 * - Matematica applicata ai colori
 * 
 * 🔧 TECNICHE AVANZATE:
 * - Bit masking per isolamento selettivo
 * - XOR swap senza variabili temporanee
 * - Clamping per overflow prevention
 * - Fixed-point arithmetic per blend
 * - Color space conversion
 * - Dithering e quantization concepts
 * 
 * 🚀 APPLICAZIONI REALI:
 * - Engine di rendering grafico
 * - Software di image editing
 * - Codec video e compressione
 * - Driver grafici hardware
 * - Filtri real-time per streaming
 * - Computer vision e AI
 * 
 * 📈 PERFORMANCE BENEFITS:
 * - Operazioni bit > 10x più veloci di divisioni
 * - Memory efficient color storage
 * - SIMD-friendly data layout
 * - Cache-optimal pixel processing
 * - Hardware acceleration ready
 */
