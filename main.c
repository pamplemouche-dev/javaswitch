#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv) {
    // Initialisation graphique
    gfxInitDefault();
    consoleInit(NULL);

    printf("\n\x1b[1;32m[MEKANISM NATIVE NSP]\x1b[0m\n");
    printf("Application installee en memoire.\n");
    printf("------------------------------------\n");

    // Scan de la carte SD
    DIR* dir = opendir("sdmc:/MekanismLauncher/mods");
    if (dir) {
        struct dirent* ent;
        printf("Mods detectes :\n");
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') printf(" - %s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        printf("\x1b[1;31m[!] Erreur: sdmc:/MekanismLauncher/mods introuvable.\x1b[0m\n");
    }

    printf("\nAppuyez sur (+) pour quitter.\n");

    while (appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        if (kDown & KEY_PLUS) break;
        consoleUpdate(NULL);
    }

    gfxExit();
    return 0;
}
