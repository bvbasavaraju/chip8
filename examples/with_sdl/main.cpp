#include <iostream>
#include <SDL3/SDL.h>

// Chip8 games to be executed! https://github.com/kripod/chip8-roms 

int main() {
    std::cout << "Hello World\n";

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Failed to initialize the SDL library\n";
        return -1;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    if(!SDL_CreateWindowAndRenderer("Hello From SDL3", 640, 480, SDL_WINDOW_ALWAYS_ON_TOP, &window, &renderer)) {
        std::cout << "Creating the Window or rendering failed\n";
    }

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
