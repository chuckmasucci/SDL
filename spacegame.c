#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"

int running = 1;

int main(int argc, char *argv[])
{
    // Start graphics
    initializeGfx();

    // Initialize player
    initializePlayer();

    while(running) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            move(-1);
                            break;
                        case SDLK_RIGHT:
                            move(1);
                            break;
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
                    break;
            }

            if(event.type == SDL_QUIT) {
                break;
            }
        }
    }
}
