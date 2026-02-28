#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Ces symboles sont créés automatiquement par objcopy
extern const uint8_t _binary_config_default_json_start[];
extern const uint8_t _binary_config_default_json_end[];

typedef uint64_t u64;
void gfxInitDefault(void);
void gfxExit(void);
void consoleInit(void*);
void consoleUpdate(void*);
void hidScanInput(void);
u64 hidKeysDown(uint32_t);
bool appletMainLoop(void);

int main(int argc, char **argv) {
    if (gfxInitDefault) gfxInitDefault();
    if (consoleInit) consoleInit(NULL);

    // Calcul de la taille du fichier intégré
    size_t config_size = _binary_config_default_json_end - _binary_config_default_json_start;

    printf("\x1b[1;32m[MEKANISM INTERNAL]\x1b[0m\n");
    printf("Extraction de la configuration integree...\n");
    
    // On affiche le contenu du JSON qui est DANS le NRO
    printf("Configuration detectee :\n");
    for(size_t i = 0; i < config_size; i++) {
        putchar(_binary_config_default_json_start[i]);
    }

    printf("\n\n\x1b[1;33m[SYSTEM]\x1b[0m Pret a lancer avec Microsoft Auth.\n");
    printf("Appuyez sur (+) pour quitter.\n");

    while (appletMainLoop && appletMainLoop()) {
        if (hidScanInput) hidScanInput();
        if (hidKeysDown && (hidKeysDown(10) & (1 << 10))) break;
        if (consoleUpdate) consoleUpdate(NULL);
    }

    if (gfxExit) gfxExit();
    return 0;
}
