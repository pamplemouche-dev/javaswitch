#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <switch.h>

// On définit les couleurs style Minecraft
#define COLOR_BG_RED 34
#define COLOR_BG_GREEN 34
#define COLOR_BG_BLUE 34

int main(int argc, char* argv[]) {
    // 1. Initialisation des services Switch
    romfsInit(); // Pour charger des images internes plus tard
    
    // 2. Initialisation SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        return -1;
    }

    // Création de la fenêtre "Plein écran" Switch
    SDL_Window* window = SDL_CreateWindow("Mekanism Launcher", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 3. Test d'accès à la Carte SD
    // On essaie d'ouvrir un fichier texte sur la SD
    FILE *sdCard = fopen("sdmc:/MekanismLauncher/mods_list.txt", "r");
    int sd_ok = (sdCard != NULL);
    if (sdCard) fclose(sdCard);

    // 4. Boucle de "Jeu"
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            
            // Gestion des boutons de la manette
            if (event.type == SDL_JOYBUTTONDOWN) {
                if (event.jbutton.button == 10) running = 0; // Bouton (+) pour quitter
            }
        }

        // --- DESSIN DE L'INTERFACE ---
        // Fond gris foncé
        SDL_SetRenderDrawColor(renderer, COLOR_BG_RED, COLOR_BG_GREEN, COLOR_BG_BLUE, 255);
        SDL_RenderClear(renderer);

        // Si la SD est détectée, on dessine un rectangle vert
        if (sd_ok) {
            SDL_Rect rect = { 100, 100, 50, 50 };
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    romfsExit();
    
    return 0;
}
