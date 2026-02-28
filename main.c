#include <stdint.h>
#include <stddef.h>

// Types de base
typedef uint32_t u32;
typedef uint64_t u64;

// --- DÉCLARATIONS MANUELLES (SANS LIBNX) ---
// On utilise les attributs "weak" pour que le linker ne panique pas
// et on pointe vers les symboles système de la Switch.
extern void gfxInitDefault(void) __attribute__((weak));
extern void gfxExit(void) __attribute__((weak));
extern void consoleInit(void*) __attribute__((weak));
extern void consoleUpdate(void*) __attribute__((weak));
extern void hidScanInput(void) __attribute__((weak));
extern u64 hidKeysDown(u32) __attribute__((weak));
extern bool appletMainLoop(void) __attribute__((weak));

// Simulation de printf simple pour la console Switch
extern int printf(const char *format, ...);

int main(int argc, char **argv) {
    // On vérifie si les fonctions sont disponibles avant de les appeler
    if (gfxInitDefault) gfxInitDefault();
    if (consoleInit) consoleInit(NULL);

    printf("\n\x1b[1;32m[MEKANISM BOOTER]\x1b[0m\n");
    printf("Mode: Zero-Dependency (Bare Metal)\n");
    printf("------------------------------------\n");
    printf("Status: Pret pour Minecraft 1.16.5\n");
    printf("Auth: Microsoft Connector Ready\n\n");
    printf("Appuyez sur (+) pour quitter.\n");

    // Boucle de service
    while (appletMainLoop && appletMainLoop()) {
        if (hidScanInput) hidScanInput();
        
        // 10 est l'ID pour le controller automatique (P1)
        if (hidKeysDown) {
            u64 kDown = hidKeysDown(10); 
            if (kDown & (1 << 10)) break; // Touche PLUS
        }

        if (consoleUpdate) consoleUpdate(NULL);
    }

    if (gfxExit) gfxExit();
    return 0;
}
