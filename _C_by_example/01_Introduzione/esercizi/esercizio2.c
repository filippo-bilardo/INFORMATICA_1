/**
 * ESERCIZIO 2: Informazioni Personali
 * 
 * OBIETTIVO:
 * Creare un programma che stampi una "carta d'identità" virtuale
 * con le tue informazioni personali formattate in modo elegante.
 * 
 * ISTRUZIONI:
 * 1. Completa tutti i campi TODO con le tue informazioni
 * 2. Usa la formattazione per creare un output ordinato
 * 3. Aggiungi almeno 3 hobby o interessi
 * 4. Includi una citazione o motto personale
 * 
 * ESEMPIO DI OUTPUT:
 * ╔═══════════════════════════════════╗
 * ║        CARTA D'IDENTITÀ           ║
 * ╠═══════════════════════════════════╣
 * ║ Nome: Mario Rossi                 ║
 * ║ Età: 20 anni                      ║
 * ║ Città: Roma                       ║
 * ║ Professione: Studente             ║
 * ╠═══════════════════════════════════╣
 * ║ HOBBY:                            ║
 * ║ • Programmazione                  ║
 * ║ • Calcio                          ║
 * ║ • Lettura                         ║
 * ╠═══════════════════════════════════╣
 * ║ MOTTO: "Code, learn, repeat!"     ║
 * ╚═══════════════════════════════════╝
 */

#include <stdio.h>

int main() {
    // Intestazione della carta
    printf("╔═══════════════════════════════════╗\n");
    printf("║        CARTA D'IDENTITÀ           ║\n");
    printf("╠═══════════════════════════════════╣\n");
    
    // TODO: Completa con le tue informazioni personali
    printf("║ Nome: [Il tuo nome completo]      ║\n");
    printf("║ Età: [la tua età] anni            ║\n");
    printf("║ Città: [la tua città]             ║\n");
    printf("║ Professione: [studente/lavoro]    ║\n");
    
    // Sezione hobby
    printf("╠═══════════════════════════════════╣\n");
    printf("║ HOBBY:                            ║\n");
    
    // TODO: Aggiungi i tuoi hobby (almeno 3)
    printf("║ • [Hobby 1]                       ║\n");
    printf("║ • [Hobby 2]                       ║\n");
    printf("║ • [Hobby 3]                       ║\n");
    
    // TODO: Aggiungi il tuo motto o citazione preferita
    printf("╠═══════════════════════════════════╣\n");
    printf("║ MOTTO: \"[La tua citazione]\"       ║\n");
    
    // Chiusura della carta
    printf("╚═══════════════════════════════════╝\n");
    
    return 0;
}

/*
 * 💡 SUGGERIMENTI:
 * 
 * 1. Caratteri per bordi:
 *    ╔ ╗ ╚ ╝ ║ ═ ╠ ╣
 * 
 * 2. Caratteri per liste:
 *    • → ★ ♦ ♠ ♥ ♣
 * 
 * 3. Prova a mantenere l'allineamento modificando gli spazi
 * 
 * 🎯 SFIDA EXTRA:
 * - Aggiungi più sezioni (linguaggi parlati, skills, ecc.)
 * - Usa emoji per rendere più colorato l'output
 * - Crea una versione "business card" più compatta
 */
