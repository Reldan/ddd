#define SDL_DISABLE_IMMINTRIN_H 1  // Disable x86 specific headers
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define GAME_TITLE "Doom Clone"

// Global variables for our window and renderer
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Initialize SDL and create window/renderer
bool initialize() {
    // Initialize SDL with required subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    // Set up hint for Metal rendering
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");

    // Create window
    window = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer optimized for Metal
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Cleanup function
void cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // Initialize game
    if (!initialize()) {
        cleanup();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // Main game loop
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderClear(renderer);

        // TODO: Add game rendering code here

        // Present renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    cleanup();
    return 0;
}