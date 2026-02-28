#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Types de base pour la Switch
typedef uint32_t u32;
typedef uint64_t u64;

// --- DÉFINITIONS AUTO-PORTÉES ---
// On utilise 'weak' pour dire au compilateur de ne pas paniquer s'il ne les voit pas maintenant
__attribute__((weak)) void gfxInitDefault(void);
__attribute__((weak)) void gfxExit(void);
__attribute__((weak)) void consoleInit(void*);
__attribute__((weak)) void consoleUpdate(void*);
__attribute__((weak)) void hidScanInput(void);
__attribute__((weak)) u64 hidKeysDown(u32);
__attribute__((weak)) bool appletMainLoop(void);

// Données intégrées (le JSON)
extern const uint8_t _binary_config_default_json_start[];
extern const uint8_t _binary_config_default_json_end[];

int main(int argc, char **argv) {
    // Initialisation sécurisée
    if (gfxInitDefault) gfxInitDefault();
    if (consoleInit) consoleInit(NULL);

    printf("\n\x1b[1;32m[MEKANISM INTERNAL BOOT]\x1b[0m\n");
    
    // Affichage de la config intégrée
    size_t config_size = _binary_config_default_json_end - _binary_config_default_json_start;
    printf("Extraction de la config (%zu octets)...\n", config_size);
    
    printf("\n--- CONFIG DETECTEE ---\n");
    for(size_t i = 0; i < config_size; i++) {
        putchar(_binary_config_default_json_start[i]);
    }
    printf("\n-----------------------\n");

    printf("\nPret pour Minecraft 1.16.5 + Microsoft Auth.\n");
    printf("Appuyez sur (+) pour quitter.\n");

    while (appletMainLoop && appletMainLoop()) {
        if (hidScanInput) hidScanInput();
        
        if (hidKeysDown) {
            u64 kDown = hidKeysDown(10); // P1 Auto
            if (kDown & (1 << 10)) break; // Touche PLUS
        }

        if (consoleUpdate) consoleUpdate(NULL);
    }

    if (gfxExit) gfxExit();
    return 0;
}
