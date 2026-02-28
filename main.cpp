#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Empêche le C++ de modifier les noms des fonctions pour le Linker
#ifdef __cplusplus
extern "C" {
#endif

    typedef uint64_t u64;
    void gfxInitDefault(void);
    void gfxExit(void);
    void consoleInit(void*);
    void consoleUpdate(void*);
    void hidScanInput(void);
    u64 hidKeysDown(int);
    bool appletMainLoop(void);

#ifdef __cplusplus
}
#endif

void launchMinecraft() {
    printf("Lancement Mekanism 1.16.5...\n");
}

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(NULL);

    launchMinecraft();

    while(appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(10); // CONTROLLER_P1_AUTO
        if (kDown & (1 << 10)) break; // KEY_PLUS
        
        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
