#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Plus besoin de extern "C", on inclut directement les fonctions
typedef uint64_t u64;

void gfxInitDefault(void);
void gfxExit(void);
void consoleInit(void*);
void consoleUpdate(void*);
void hidScanInput(void);
u64 hidKeysDown(int);
bool appletMainLoop(void);

void launchMinecraft() {
    printf("\x1b[1;32m[MEKANISM]\x1b[0m Mode: C Natif\n");
    printf("Lancement de Minecraft 1.16.5...\n");
}

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(NULL);

    launchMinecraft();

    while(appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(10);
        if (kDown & (1 << 10)) break; // Touche (+)
        
        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
