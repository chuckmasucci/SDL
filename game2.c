#include <stdio.h>
#include <SDL2/SDL.h>
#include "dbg.h"

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Surface *background;
SDL_Surface *ship;

int main(int argc, char *argv)
{
    check(SDL_Init(SDL_INIT_VIDEO) >= 0, "Could not initialize SDL: %s", SDL_GetError());
    check(window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0), "Could not create window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ship = SDL_LoadBMP("wship1.bmp");
    SDL_BlitSurface(ship, NULL, background, NULL);

    while(1) {
        SDL_Event e;
        if(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                break;
            }
        }

    }


error:
    SDL_Quit();
    log_err("SDL Error: Shutdown");
}
