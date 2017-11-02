#include <stdio.h>
#include "dbg.h"
#include <SDL2/SDL.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *demo_screen;
    SDL_Renderer *renderer;
    SDL_Surface *bitmapSurface;
    SDL_Texture *bitmapTex;
    int posX = 100, posY = 100, width = 320, height = 240;
    
    check(SDL_Init(SDL_INIT_VIDEO) >= 0, "Could not initialize SDL");

    check(window = SDL_CreateWindow("Hello World", posX, posY, width, height, 0), "Could not create window: %s\n", SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bitmapSurface = SDL_LoadBMP("wship1.bmp");
    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);

    while(1) {
        SDL_Event e;
        if(SDL_PollEvent(&e)) {
             if(e.type == SDL_QUIT) {
                 break;
             }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;


error:
    SDL_Quit();
    log_err("SDL Shutdown");
}


