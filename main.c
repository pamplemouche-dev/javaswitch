#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <switch.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialisation de la Switch et de la Vidéo
    romfsInit();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    
    SDL_Window* window = SDL_CreateWindow("Mekanism Launcher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // --- ACCÈS CARTE SD ---
    FILE *file = fopen("sdmc:/MekanismLauncher/launcher.json", "r");
    if (file) {
        // Code pour lire tes mods ici
        fclose(file);
    }

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_JOYBUTTONDOWN) {
                if (event.jbutton.button == 10) running = 0; // Touche (+)
            }
        }

        // --- DESSIN DE L'INTERFACE ---
        SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255); // Gris foncé Minecraft
        SDL_RenderClear(renderer);
        
        // Ici on pourra ajouter : SDL_RenderCopy(renderer, texture_bouton, NULL, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    romfsExit();
    return 0;
}
