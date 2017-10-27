#include <stdio.h>
#include "dbg.h"
#include <SDL2/SDL.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *demo_screen;
    int posX = 100, posY = 100, width = 320, height = 240;
    
    check(SDL_Init(SDL_INIT_VIDEO) >= 0, "Could not initialize SDL");

    check(window = SDL_CreateWindow("Hello World", posX, posY, width, height, 0), "Could not create window: %s\n", SDL_GetError());
    

    return 0;


error:
    SDL_Quit();
    log_err("SDL Shutdown");
}


