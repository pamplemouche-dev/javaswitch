#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// On définit les types manuellement pour être 100% autonome
typedef uint32_t u32;
typedef uint64_t u64;

// Prototypes indispensables
void gfxInitDefault(void);
void gfxExit(void);
void consoleInit(void*);
void consoleUpdate(void*);
void hidScanInput(void);
u64 hidKeysDown(u32);
bool appletMainLoop(void);

// Inclusion du JSON interne
extern const uint8_t _binary_config_default_json_start[];
extern const uint8_t _binary_config_default_json_end[];

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(NULL);

    printf("\x1b[1;32m[MEKANISM AUTO-BOOT]\x1b[0m\n");
    
    // Lecture de la config intégrée
    size_t size = _binary_config_default_json_end - _binary_config_default_json_start;
    printf("Config interne chargee (%zu octets)\n\n", size);

    printf("Action: Microsoft Auth Verification...\n");
    printf("Target: Minecraft 1.16.5 + Mekanism\n\n");
    printf("Appuyez sur (+) pour quitter.\n");

    while (appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(10); 
        if (kDown & (1 << 10)) break; 

        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
