#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Déclarations manuelles pour le Linker
typedef uint64_t u64;
void gfxInitDefault(void);
void gfxExit(void);
void consoleInit(void*);
void consoleUpdate(void*);
void hidScanInput(void);
u64 hidKeysDown(int);
bool appletMainLoop(void);

int main(int argc, char **argv) {
    // Initialisation
    gfxInitDefault();
    consoleInit(NULL);

    printf("\x1b[1;32m[MEKANISM]\x1b[0m Booting Minecraft...\n");
    printf("Auth: Microsoft Integration\n");
    printf("Appuyez sur (+) pour quitter.\n");

    // Boucle principale
    while(appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(10); // 10 = CONTROLLER_P1_AUTO

        if (kDown & (1 << 10)) break; // (1 << 10) = KEY_PLUS

        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
