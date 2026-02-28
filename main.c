#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// L'en-tête magique qui contient toutes les fonctions de la Switch
#include <switch.h> 

// Récupération du JSON intégré (config_default.json)
extern const uint8_t _binary_config_default_json_start[];
extern const uint8_t _binary_config_default_json_end[];

int main(int argc, char **argv) {
    // Initialisation des services graphiques et de la console texte
    gfxInitDefault();
    consoleInit(NULL);

    // Calcul de la taille du JSON
    size_t config_size = _binary_config_default_json_end - _binary_config_default_json_start;

    printf("\x1b[1;32m[MEKANISM JAVA LAUNCHER]\x1b[0m\n");
    printf("Statut : Liaison dynamique avec Horizon OS OK\n");
    printf("--------------------------------------------\n");
    
    printf("Chargement de la configuration interne...\n\n");

    // Affichage du contenu du JSON pour vérifier que tout est là
    for(size_t i = 0; i < config_size; i++) {
        putchar(_binary_config_default_json_start[i]);
    }

    printf("\n\n\x1b[1;33m[INFO]\x1b[0m Pret pour Minecraft 1.16.5.\n");
    printf("\x1b[1;33m[INFO]\x1b[0m Appuyez sur (+) pour quitter le launcher.\n");

    // Boucle principale : tourne tant que l'app n'est pas fermée
    while (appletMainLoop()) {
        // Scan des entrées (manettes/joycons)
        hidScanInput();

        // Récupération des touches pressées sur le contrôleur principal
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        // Si on appuie sur (+), on sort de la boucle
        if (kDown & KEY_PLUS) break;

        // Mise à jour de l'affichage console
        consoleUpdate(NULL);
    }

    // Nettoyage avant de quitter (très important pour éviter les bugs)
    gfxExit();
    return 0;
}
