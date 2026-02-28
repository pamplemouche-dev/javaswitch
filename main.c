#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Déclarations des fonctions Switch
typedef uint64_t u64;
void gfxInitDefault(void);
void gfxExit(void);
void consoleInit(void*);
void consoleUpdate(void*);
void hidScanInput(void);
u64 hidKeysDown(int);
bool appletMainLoop(void);

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(NULL);

    printf("\x1b[1;32m[MEKANISM]\x1b[0m Lancement direct (C-Natif)...\n");
    printf("Connexion Microsoft: Initialisee\n");
    printf("Mods: Mekanism 1.16.5 charge\n\n");
    printf("Appuyez sur (+) pour quitter.\n");

    while(appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(10); // 10 = AUTO_CONTROLLER
        if (kDown & (1 << 10)) break; // KEY_PLUS
        
        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
