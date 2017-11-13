#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"

#define FRAMERATE 5

int running = 1;

int main(int argc, char *argv[])
{
    // Initialize movement variables
    int isLeftKeyDown = 0;
    int isRightKeyDown = 0;
    int moveDirection = 10;

    // Initialize timing variables
    Uint64 freq;
    Uint64 now;
    Uint64 lastTime = SDL_GetPerformanceCounter();
    Uint64 secs;
    Uint64 delay;

    // Start graphics
    initializeGfx();

    // Initialize player
    initializePlayer();

    // The loop
    while(running) {
        // Timing variables
        freq = SDL_GetPerformanceFrequency();
        now = SDL_GetPerformanceCounter();
        secs = (now - lastTime) / freq;
        delay = FRAMERATE - secs * 1000;
        SDL_Delay(delay);

        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            isLeftKeyDown = 1;
                            moveDirection = -1;
                            break;
                        case SDLK_RIGHT:
                            isRightKeyDown = 1;
                            moveDirection = 1;
                            break;
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            isLeftKeyDown = 0;
                            break;
                        case SDLK_RIGHT:
                            isRightKeyDown = 0;
                            break;
                    }
                    break;
            }

            if(event.type == SDL_QUIT) {
                break;
            }
        }

        // Update the timing variable
        lastTime = now;

        // Determine if movement key is pressed and move the player
        if(isLeftKeyDown) {
            move(moveDirection);
        } else if(isRightKeyDown) {
            move(moveDirection);
        }
    }

    return 0;
}
